
/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
#include "SysNvId.h"
#include "nvim_internalfunc.h"
#include "nvim_fileoperateinterface.h"
#include "XMLDecode.h"
#include "mdrv.h"
#include "product_config.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_XML_C

/*****************************************************************************
2 ȫ�ֱ�������
*****************************************************************************/
/* ��ǰxml�ļ��ڵ����ļ�ϵͳ��·��  */
#if (VOS_OS_VER == VOS_WIN32)       /* PC Stub */
XML_PATH_STRU g_astXMLFilePath[2] = {{".\\yaffs0\\NvimUse\\xnv.xml",         ".\\yaffs0\\NvimUse\\cust.xml"},
                                    {".\\yaffs0\\NvimUse\\xnvnotexist.xml", ".\\yaffs0\\NvimUse\\xnvnotexist.xml"}};

XML_MAP_PATH_STRU g_astMapFilePath[2] = {{".\\yaffs0\\NvimUse\\xnv.map"}, {".\\yaffs0\\NvimUse\\xnv1.map"}};

#else
#if ( FEATURE_MULTI_MODEM == FEATURE_ON )

XML_PATH_STRU g_astXMLFilePath[MODEM_ID_BUTT] = {{"/mnvm2:0/NvimUse/xnv.xml",    "/mnvm2:0/NvimUse/cust.xml"},
                                                {"/mnvm2:0/NvimUse/xnv1.xml",   "/mnvm2:0/NvimUse/cust1.xml"}};

XML_MAP_PATH_STRU  g_astMapFilePath[MODEM_ID_BUTT] = {{"/mnvm2:0/NvimUse/xnv.map"}, {"/mnvm2:0/NvimUse/xnv1.map"}};

#else   /*( FEATURE_MULTI_MODEM == FEATURE_OFF )*/


XML_PATH_STRU g_astXMLFilePath[MODEM_ID_BUTT] = {"/mnvm2:0/NvimUse/xnv.xml",  "/mnvm2:0/NvimUse/cust.xml"};
XML_MAP_PATH_STRU  g_astMapFilePath[MODEM_ID_BUTT] = {"/mnvm2:0/NvimUse/xnv.map"};

#endif  /*( FEATURE_MULTI_MODEM == FEATURE_ON )*/
#endif  /*OAM_UT_DEBUG*/

#define XML_NAME_MAX_LEN                (24)

/* ��ǰ������Modem ID��ֵ  */
VOS_UINT16 g_enXMLCurModemID;


/* ��ͨ�ڵ�����                         */
VOS_CHAR g_acNodeLabelCommon[]               = "common_NvInfo";

/* Product�ڵ�����                      */
VOS_CHAR g_acNodeLabelProduct[]              = "product";

/* NV�ڵ�����                           */
VOS_CHAR g_acNodeLabelNv[]                   = "nv";

/* Cust�ڵ�����                         */
VOS_CHAR g_acNodeLabelCust[]                 = "cust";

/* �ڵ�ʮ������ֵ֮��ķָ���           */
VOS_CHAR g_cSeparator                        = ',';

/* XML�ļ�����ʱ��״̬                  */
XML_ANALYSE_STATUS_ENUM_UINT32 g_ulXMLStatus = XML_ANASTT_ORIGINAL;

/* ��ǰ�ڵ�                             */
XML_NODE_STRU g_stXMLCurrentNode;

/* ��¼��Ч��Product�ڵ���Ϣ            */
XML_PRODUCT_STRU g_stXMLProductInfo;

/* ���NV Item��ֵ                      */
VOS_UINT8 *g_pucNVItem                       = VOS_NULL_PTR;

/* ��ȡ�ļ����ݵĻ�����                 */
VOS_CHAR  *g_pcFileReadBuff                  = VOS_NULL_PTR;

/* ��¼��ȡXML�ļ�������                */
VOS_UINT32 g_ulLineNo                        = VOS_NULL_LONG;

/*  xnv.xml�ļ�������                   */
FILE*      g_lEnvFile                        = VOS_NULL_PTR;

/*  cust.xml�ļ�������                  */
FILE*      g_lCustFile                       = VOS_NULL_PTR;

/* XML������Ϣ */
XML_ERROR_INFO_STRU g_stXmlErrorInfo;

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
/* ֧�ֲ�Ʒ������xnv.xml����״̬ */
XML_PRODUCT_DECODE_STATUS_ENUM_UINT32 g_enProductDecodeStatus = XML_PRODUCT_ANALYZE_START;

/* Product�ڵ�����                      */
VOS_CHAR g_acNodeLabelProductCat[]              = "product_NvInfo";
#endif

/* XML�ؼ���,������0-9,a-z,A-Z */
VOS_CHAR   g_acXMLKeyWordTbl[] = { '<', '>', '/', '=', '"',
                                   ' ', '!', '?', '_', '-',
                                   ',' };

/*****************************************************************************
3 ��������
*****************************************************************************/
#if (VOS_OS_VER == VOS_WIN32)
extern VOS_VOID XML_SendMsg(VOS_UINT32 ulRet);
#endif


VOS_VOID XML_WriteErrorLog(VOS_UINT32 ulErrLine, VOS_UINT16 ulNvId,
                                VOS_UINT32 ulResult)
{
    g_stXmlErrorInfo.ulXMLLine  = g_ulLineNo;
    g_stXmlErrorInfo.ulStatus   = g_ulXMLStatus;
    g_stXmlErrorInfo.ulCodeLine = ulErrLine;
    g_stXmlErrorInfo.usNvId     = ulNvId;
    g_stXmlErrorInfo.ulResult   = ulResult;

    return ;
}


XML_RESULT_ENUM_UINT32 XML_CheckXMLKeyWord(VOS_CHAR cCurrentChar)
{
    VOS_UINT32 lCount;

    if ((('0' <= cCurrentChar) && ('9' >= cCurrentChar))   /* ��Ч�ַ���0-9  */
        ||(('a' <= cCurrentChar) && ('z' >= cCurrentChar)) /* ��Ч�ַ���a-z  */
        ||(('A' <= cCurrentChar) && ('Z' >= cCurrentChar)))/* ��Ч�ַ���A-Z  */
    {
        return XML_RESULT_SUCCEED;
    }

    /* �� 0-9,a-z,A-Z ֮��� XML�ؼ��� */
    for (lCount=0; lCount<sizeof(g_acXMLKeyWordTbl); lCount++)
    {
        if (cCurrentChar == g_acXMLKeyWordTbl[lCount])
        {
            return XML_RESULT_SUCCEED;
        }
    }

    return XML_RESULT_FALIED_BAD_CHAR;
}



XML_RESULT_ENUM_UINT32 XML_CheckCharValidity(VOS_CHAR cCurrentChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    if (('\r' == cCurrentChar)       /* ���Իس�   */
        || ('\t' == cCurrentChar))   /* �����Ʊ�� */
    {
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    if ('\n' == cCurrentChar)    /* ���Ի���   */
    {
        g_ulLineNo++;
        return XML_RESULT_SUCCEED_IGNORE_CHAR;
    }

    /* ��ע���е��ַ�������� */
    if ( XML_ANASTT_IGNORE == g_ulXMLStatus)
    {
        return XML_RESULT_SUCCEED;
    }

    /* ���XML�Ĺؼ��� */
    ulReturnVal = XML_CheckXMLKeyWord(cCurrentChar);
    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        XML_WriteErrorLog(__LINE__, 0, ulReturnVal);

        return ulReturnVal;
    }

    return XML_RESULT_SUCCEED;
}
XML_RESULT_ENUM_UINT32 XML_StringToNvId(VOS_CHAR  *pcBuff,
                                            VOS_UINT16 *pusRetVal)
{
    VOS_UINT32 ulTemp = 0;  /* �ַ���ת������ʱ���м���� */
    VOS_CHAR   cCurrentChar;
    VOS_CHAR  *pcSrc;

    pcSrc = pcBuff;

    /* ���NV ID�ǿյģ��򷵻ش��� */
    if (0 == *pcSrc)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_NV_ID_IS_NULL);

        return XML_RESULT_FALIED_NV_ID_IS_NULL;
    }

    /* ���ַ���ת��ʮ���Ƶĸ�ʽ */
    while (0 != *pcSrc)
    {
        cCurrentChar = *pcSrc;

        /* �Բ���0��9֮����ַ����������� */
        if ((cCurrentChar < '0') || (cCurrentChar > '9'))
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_9);

            return XML_RESULT_FALIED_OUT_OF_0_9;
        }

        /* ת��ʮ���Ƹ�ʽ */
        cCurrentChar -= '0';
        ulTemp = (ulTemp*10) + (VOS_UINT8)cCurrentChar;

        /* ����NV ID�����ֵ */
        if (VOS_NULL_WORD < ulTemp)
        {
            XML_WriteErrorLog(__LINE__, (VOS_UINT16)ulTemp, XML_RESULT_FALIED_OUT_OF_MAX_VALUE);

            return XML_RESULT_FALIED_OUT_OF_MAX_VALUE;
        }

        pcSrc++;
    }

    /* ��� ת�����ֵ */
    *pusRetVal = (VOS_UINT16)ulTemp;

    return XML_RESULT_SUCCEED;
}
XML_RESULT_ENUM_UINT32 XML_StringToHex(VOS_UINT8 *pucSrc, VOS_UINT8 *pucDest)
{
    VOS_UINT8  ucCurrent;
    VOS_UINT8  ucTemp  = 0;
    VOS_UINT16 usCount = 0;

    /* pucSrc�ĳ���һ����ż��,������Ĳ�����֤ */
    while (0 != *pucSrc)
    {
        ucCurrent = *pucSrc;

        if ((ucCurrent >= 'a') && (ucCurrent <= 'f'))
        {
            /* ��Сд�ַ�ת�ɴ�д*/
            ucCurrent -= 'a'-'A';
        }

        /* ת��ʮ�����Ƹ�ʽ */
        if ((ucCurrent >= 'A') && (ucCurrent <= 'F'))
        {
            usCount++;
            ucTemp = (VOS_UINT8)(ucTemp * 16) + (VOS_UINT8)(ucCurrent - 'A') + 10;
        }
        else if ((ucCurrent >= '0') && (ucCurrent <= '9'))
        {
            usCount++;
            ucTemp = (VOS_UINT8)(ucTemp * 16) + (VOS_UINT8)(ucCurrent - '0');
        }
        else
        {
            /* �Բ���0-9,a-f,A-F֮����ַ����������� */
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_0_F);

            return XML_RESULT_FALIED_OUT_OF_0_F;
        } /* end of if ((ucCurrent >= 'a') && (ucCurrent <= 'f')) */

        /* ��2���ַ�ת����һ��ʮ�����ƺ�,���浽Ŀ�껺������ */
        if (2 == usCount)
        {
            *pucDest++ = ucTemp;
            ucTemp = 0;
            usCount = 0;
        }

        pucSrc++;
    }

    /* �����ַ���������'\0' */
    *pucDest = 0;

    return XML_RESULT_SUCCEED;
}
XML_RESULT_ENUM_UINT32 XML_StringToNvValue(VOS_UINT8  *pucBuff,
                                                 VOS_UINT8  *pucRetBuff,
                                                 VOS_UINT32 *pulRetBuffLen)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;
    VOS_UINT32 ulCount = 0;    /* �ж��Ƿ񱣴浱ǰת�����ֵ */
    VOS_UINT8 *pcSrc;
    VOS_UINT8 *pcDest;

    pcSrc  = pucBuff;
    pcDest = pucBuff;

     /* ���NV VALUE�ǿյģ��򷵻ش��� */
    if (0 == *pcSrc)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_NV_VALUE_IS_NULL);

        return XML_RESULT_FALIED_NV_VALUE_IS_NULL;
    }

    /* �Ȱ�ԭ�ַ����еķָ���ȥ�� */
    while (0 != *pcSrc)
    {
        /* �����ǰ�ַ��Ƿָ��� */
        if (g_cSeparator == *pcSrc)
        {
            /* �����2���ָ���֮��ֻ��һ���ַ�,������ǰ�����һ��'0' */
            if (1 == ulCount)
            {
                *pcDest = *(pcDest-1);
                *(pcDest-1) = '0';
                pcDest++;
            }

            ulCount = 0;
            pcSrc++;

            continue;
        }

        /* �����һ��NV���2���ַ�,������.��<nv id="1">A3E</nvs> */
        if (2 <= ulCount)
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_2_CHAR);

            return XML_RESULT_FALIED_OUT_OF_2_CHAR;
        }

        *pcDest++ = *pcSrc++;
        ulCount++;    /* ��¼�ָ���֮���ַ��ĸ��� */
    }

    /* ������һ���ָ�����ֻ��һ���ַ�,������ǰ�����һ��'0' */
    if (1 == ulCount)
    {
        *pcDest = *(pcDest-1);
        *(pcDest-1) = '0';
        pcDest++;
    }

    /* �����ַ���������'\0' */
    *pcDest = 0;

    /* ��¼ת��������ݳ��� */
    *pulRetBuffLen = (VOS_UINT32)(pcDest - pucBuff)/2;

    /* ת��ʮ�����Ƹ�ʽ */
    pcSrc  = pucBuff;
    pcDest = pucRetBuff;
    ulReturnVal =  XML_StringToHex(pcSrc, pcDest);

    return ulReturnVal;
}
XML_RESULT_ENUM_UINT32 XML_WriteNVItem(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32              ulReturnVal;
    VOS_UINT16                          usNVItemId  = 0;
    VOS_UINT32                          ulNVItemLen = 0;
    VOS_INT                             lIsNV       = 0;
    VOS_INT                             lIsCust     = 0;
    VOS_UINT32                          ulRet;

    /* �����ǰ�ڵ㲻����Ч�Ľڵ�,�����κδ��� */
    if (XML_PRODUCT_NODE_STATUS_INVALID == g_stXMLProductInfo.enValidNode)
    {
        return XML_RESULT_SUCCEED;
    }

    /* �������ֵΪ��,���ҽڵ�ֵΪ��,�����κδ���, ��<cust/> */
    g_stXMLCurrentNode.stProperty.pcPropertyValue[
                        g_stXMLCurrentNode.stProperty.ulValueLength] = '\0';

    g_stXMLCurrentNode.pcNodeValue[g_stXMLCurrentNode.ulValueLength] = '\0';

    if ((0 == *g_stXMLCurrentNode.stProperty.pcPropertyValue)
        && (0 == *g_stXMLCurrentNode.pcNodeValue))
    {
        return XML_RESULT_SUCCEED;
    }

    /* ֻ��nv��cust�ڵ�д��NV�� */
    g_stXMLCurrentNode.pcNodeLabel[g_stXMLCurrentNode.ulLabelLength] = '\0';

    lIsNV   = VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel, g_acNodeLabelNv);

    lIsCust = VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel, g_acNodeLabelCust);

    if ((0 != lIsNV) && (0 != lIsCust))
    {
        return XML_RESULT_SUCCEED;
    }

    /* ������ֵת��NV ID */
    ulReturnVal = XML_StringToNvId(g_stXMLCurrentNode.stProperty.pcPropertyValue,
                                &usNVItemId);

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* �ѽڵ�ֵת��NV Value */
    ulNVItemLen = 0;

    ulReturnVal = XML_StringToNvValue((VOS_UINT8 *)g_stXMLCurrentNode.pcNodeValue,
                                  g_pucNVItem,
                                  &ulNVItemLen);

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* д��NV�� */
    ulRet = NV_WriteDirect(g_enXMLCurModemID, usNVItemId,(VOS_VOID *)(g_pucNVItem),ulNVItemLen);
    if ((NV_OK != ulRet) && (NV_WRITE_SECURE_FAIL != ulRet))
    {
        /* ��¼�����NV ID */
        XML_WriteErrorLog(__LINE__, usNVItemId, ulRet);

        return XML_RESULT_FALIED_WRITE_NV;
    }

    return XML_RESULT_SUCCEED;
}
VOS_VOID XML_NodeReset(VOS_VOID)
{
    /* �ڵ��ǩ��λ,��ʹ�õĳ���Ϊ0  */
    g_stXMLCurrentNode.ulLabelLength = 0;

    /* �ڵ�ֵ��λ,��ʹ�õĳ���Ϊ0 */
    g_stXMLCurrentNode.ulValueLength = 0;

    /* �ڵ������ǩ��λ,��ʹ�õĳ���Ϊ0 */
    g_stXMLCurrentNode.ulLabelEndLength = 0;

    /* �ڵ���������λ,��ʹ�õĳ���Ϊ0 */
    g_stXMLCurrentNode.stProperty.ulNameLength = 0;

    /* �ڵ�����ֵ��λ,��ʹ�õĳ���Ϊ0 */
    g_stXMLCurrentNode.stProperty.ulValueLength = 0;

    return ;
}
XML_RESULT_ENUM_UINT32 XML_AddACharToBuff(VOS_CHAR   cNowChar,
                                                 VOS_CHAR   *pcStrBuff,
                                                 VOS_UINT32 *plBuffLength,
                                                 VOS_BOOL   ulIsNodeValue)
{
    /* ���Կո� */
    if (' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* ����ﵽ��Node Value����󳤶� */
    if ((VOS_TRUE == ulIsNodeValue)
        && (*plBuffLength >= XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }

    /* ����ﵽ��Node Lable����󳤶� */
    if ((VOS_FALSE == ulIsNodeValue)
        && (*plBuffLength >= XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OUT_OF_BUFF_LEN);

        return XML_RESULT_FALIED_OUT_OF_BUFF_LEN;
    }

    /* �����ַ��ӽ������� */
    *(pcStrBuff + *plBuffLength) = cNowChar;

    /* ���������ȼ�1 */
    (*plBuffLength)++;

    return XML_RESULT_SUCCEED;
}
XML_RESULT_ENUM_UINT32 XML_CheckNodeLabelValid(VOS_VOID)
{
    /* �жϸñ�ǩ�Ƿ���Ч */
    g_stXMLCurrentNode.pcNodeLabel[g_stXMLCurrentNode.ulLabelLength] = '\0';

    if (XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* �ڽڵ�Ϊ��Ч״̬�£���Product�ڵ㣬Ҫ��¼<product>�ڵ���ֵĴ��� */
        if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                            g_acNodeLabelProduct))
        {
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
            /* ֧�ֲ�Ʒ��ʱ��product cat��������nv�������������� */
            if (XML_PRODUCT_CAT_ANALYZE_START == g_enProductDecodeStatus)
            {
                g_enProductDecodeStatus = XML_PRODUCT_CAT_ANALYZE_FINISH;
                g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
            }
#endif
            g_stXMLProductInfo.ulNodeLevel++;
        }

        return XML_RESULT_SUCCEED;
    }

    /* �����ǰ�ڵ�Ϊ��Ч״̬,��Ҫ����ǩ�Ƿ�Ϊ��Ч�ڵ� */
    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                        g_acNodeLabelCommon))
    {
        /* �����<Common_NvInfo>��ǩ,�����ýڵ�Ϊ��Ч״̬ */
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }

    /* �����<Cust>��ǩ,�����ýڵ�Ϊ��Ч״̬ */
    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                             g_acNodeLabelCust))
    {
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;

        return XML_RESULT_SUCCEED;
    }

    /* �����<product>��ǩ��Product id�뵱ǰ������ͬ,�����ýڵ�Ϊ��Ч״̬ */
    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                             g_acNodeLabelProduct))
    {
        g_stXMLCurrentNode.stProperty.pcPropertyValue[
                      g_stXMLCurrentNode.stProperty.ulValueLength] = '\0';

        if (0 == VOS_StrCmp(g_stXMLCurrentNode.stProperty.pcPropertyValue,
                            g_stXMLProductInfo.acProductId))
        {
            g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;
            g_stXMLProductInfo.ulNodeLevel++;
        }
    }

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    /* ���product cat��ʼ��ǩ�Ƿ���ȷ */
    if (XML_PRODUCT_CAT_ANALYZE_START == g_enProductDecodeStatus)
    {
        if (0 != VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                                 g_acNodeLabelProductCat))
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

            return XML_RESULT_FALIED_BAD_FILE;
        }

        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_VALID;
    }
#endif

    return XML_RESULT_SUCCEED;
}



XML_RESULT_ENUM_UINT32 XML_CheckNodeEndLabelValid(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    if (XML_PRODUCT_NODE_STATUS_VALID != g_stXMLProductInfo.enValidNode)
    {
        /* �����ǰ�ڵ�Ϊ��Ч״̬�������κδ��� */
        return XML_RESULT_SUCCEED;
    }

    /* д�ڵ���Ϣ��NV�� */
    ulReturnVal = XML_WriteNVItem();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    g_stXMLCurrentNode.pcNodeLabelEnd[g_stXMLCurrentNode.ulLabelEndLength]='\0';

    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd,
                        g_acNodeLabelProduct))
    {
        g_stXMLProductInfo.ulNodeLevel--;

        if (0 == g_stXMLProductInfo.ulNodeLevel)
        {
            /* ���һ����Ч��</product>��ǩ����ʱ����������XML�ļ��Ľ��� */
            g_stXMLProductInfo.enXMLDecodeState=XML_DECODE_STATUS_FINISHED;
            g_stXMLProductInfo.enValidNode=XML_PRODUCT_NODE_STATUS_INVALID;
        }
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /* ���һ����Ч��</product>��ǩ����ʱ����������XML�ļ��Ľ��� */
        g_stXMLProductInfo.enXMLDecodeState=XML_DECODE_STATUS_FINISHED;
        g_stXMLProductInfo.enValidNode=XML_PRODUCT_NODE_STATUS_INVALID;
        g_enProductDecodeStatus = XML_PRODUCT_ID_ANALYZE_FINISH;
#endif
    }
    else if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd,
                             g_acNodeLabelCommon))
    {
        /* </Common_NvInfo>��ǩ����ʱ,�ѽڵ�״̬��Ϊ��Ч */
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /* ֧�ֲ�Ʒ��ʱ��common nv�������������� */
        g_enProductDecodeStatus = XML_PRODUCT_COMMON_ANALYZE_FINISH;
#endif
    }
    else if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd,
                             g_acNodeLabelCust))
    {
        /* </Cust>��ǩ����ʱ,�ѽڵ�״̬��Ϊ��Ч */
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
    }
    else
    {
        /* Do nothing */

    } /* end of if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabelEnd, */

    /* </xx>��ǩ����ʱ����սڵ���Ϣ */
    XML_NodeReset();

    return XML_RESULT_SUCCEED;
}


XML_RESULT_ENUM_UINT32 XML_CreateAProperty( VOS_VOID )
{
    /* �����������ڴ�,+1Ϊ�����ַ����������� */
    g_stXMLCurrentNode.stProperty.ulNameLength = 0; /* ��ʹ�õĳ��� */

    g_stXMLCurrentNode.stProperty.pcPropertyName
                                = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                   DYNAMIC_MEM_PT,
                                   XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR == g_stXMLCurrentNode.stProperty.pcPropertyName)
    {
         XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* ��������ֵ�ڴ�,+1Ϊ�����ַ����������� */
    g_stXMLCurrentNode.stProperty.ulValueLength = 0; /* ��ʹ�õĳ��� */

    g_stXMLCurrentNode.stProperty.pcPropertyValue
                                = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                   DYNAMIC_MEM_PT,
                                   XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR == g_stXMLCurrentNode.stProperty.pcPropertyValue)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    return XML_RESULT_SUCCEED;
}



XML_RESULT_ENUM_UINT32 XML_CreateANode(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* ����һ�������� */
    ulReturnVal = XML_CreateAProperty();

    if(XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* ����ڵ��ǩ�ڴ�,+1Ϊ�����ַ�����������*/
    g_stXMLCurrentNode.ulLabelLength = 0; /* ��ʹ�õĳ��� */

    g_stXMLCurrentNode.pcNodeLabel = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                      DYNAMIC_MEM_PT,
                                      XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR ==  g_stXMLCurrentNode.pcNodeLabel)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* ����ڵ��β������ǩ�ڴ�,+1Ϊ�����ַ����������� */
    g_stXMLCurrentNode.ulLabelEndLength = 0; /* ��ʹ�õĳ��� */

    g_stXMLCurrentNode.pcNodeLabelEnd = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                        DYNAMIC_MEM_PT,
                                        XML_NODE_LABEL_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR ==  g_stXMLCurrentNode.pcNodeLabelEnd)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* ����ڵ�ֵ�ڴ�,+1Ϊ�����ַ����������� */
    g_stXMLCurrentNode.ulValueLength = 0; /* ��ʹ�õĳ��� */

    g_stXMLCurrentNode.pcNodeValue = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                      DYNAMIC_MEM_PT,
                                      XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);

    if (VOS_NULL_PTR == g_stXMLCurrentNode.pcNodeValue)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    return ulReturnVal;
}
XML_RESULT_ENUM_UINT32 XML_ProcXmlOrinigal(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* ����<�����״̬ */
    if ('<' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_ENTER_LABLE;
        return XML_RESULT_SUCCEED;
    }

    /* ����>,/,",=���ʾXML�﷨���� */
    if (('>' == cNowChar)
         ||('/' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    if (XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
        ulReturnVal = XML_AddACharToBuff(cNowChar,
                                     g_stXMLCurrentNode.pcNodeValue,
                                     &(g_stXMLCurrentNode.ulValueLength),
                                     VOS_TRUE);
    }

    return ulReturnVal;
}
XML_RESULT_ENUM_UINT32 XML_ProcXmlIgnore(VOS_CHAR cNowChar)
{
    /* ֱ��������ǩ��β������һֱ���� */
    if ('>' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;
    }

    return XML_RESULT_SUCCEED;
}
XML_RESULT_ENUM_UINT32 XML_ProcXmlSingleEndLabel(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    ulReturnVal = XML_RESULT_SUCCEED;

    /* ����<�����״̬ */
    if ('>' == cNowChar)
    {
        /* ���״̬ */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* ������������ǩ�Ƿ���Ч */
        ulReturnVal = XML_CheckNodeEndLabelValid();

        return ulReturnVal;
    }

    /* ����<,/,",=���ʾXML�﷨���� */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('/' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    if(XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
        ulReturnVal = XML_AddACharToBuff(cNowChar,
                                      g_stXMLCurrentNode.pcNodeLabelEnd,
                                      &(g_stXMLCurrentNode.ulLabelEndLength),
                                      VOS_FALSE);
    }

    return ulReturnVal;
}

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
VOS_VOID XML_ProductCatNullNodeProc(VOS_VOID)
{
    g_stXMLCurrentNode.pcNodeLabel[g_stXMLCurrentNode.ulLabelLength] = '\0';

    if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                        g_acNodeLabelCommon))
    {
        g_enProductDecodeStatus = XML_PRODUCT_COMMON_ANALYZE_FINISH;
        g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
    }

    if (XML_PRODUCT_CAT_ANALYZE_START == g_enProductDecodeStatus)
    {
        if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                            g_acNodeLabelProduct))
        {
            g_enProductDecodeStatus = XML_PRODUCT_CAT_ANALYZE_FINISH;
            g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
        }
    }

    if (XML_PRODUCT_ID_ANALYZE_START == g_enProductDecodeStatus)
    {
        if (0 == VOS_StrCmp(g_stXMLCurrentNode.pcNodeLabel,
                            g_acNodeLabelProduct))
        {
            g_enProductDecodeStatus = XML_PRODUCT_ID_ANALYZE_FINISH;
            g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_FINISHED;
            g_stXMLProductInfo.enValidNode = XML_PRODUCT_NODE_STATUS_INVALID;
        }
    }

    return;
}
#endif


XML_RESULT_ENUM_UINT32 XML_ProcXmlEndMustBeRight(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* ���Կո� */
    if (' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* ��������>,���ʾXML�﷨���� */
    if ('>' != cNowChar)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    XML_ProductCatNullNodeProc();
#endif

    /* ���״̬ */
    g_ulXMLStatus = XML_ANASTT_ORIGINAL;

    if (XML_PRODUCT_NODE_STATUS_VALID == g_stXMLProductInfo.enValidNode)
    {
        /* д�ڵ���Ϣ��NV�� */
        ulReturnVal = XML_WriteNVItem();

        if (XML_RESULT_SUCCEED != ulReturnVal)
        {
            return ulReturnVal;
        }

        /* <xx/>��ǩ����ʱ����սڵ���Ϣ */
        XML_NodeReset();
    }

    return XML_RESULT_SUCCEED;
}
XML_RESULT_ENUM_UINT32 XML_ProcXmlNodeLabel(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* ����/����>���߿ո�˵��Node�����ֽ����� */
    if ('/' == cNowChar)
    {
        /* ��������β�����ڵ�,�¸��ֽ�һ����> */
        g_ulXMLStatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* ��ǩ���� */
    if ('>' == cNowChar)
    {
        /* ���״̬ */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* ��鵱ǰ�ڵ�����Ч�ڵ� */
        ulReturnVal = XML_CheckNodeLabelValid();

        return ulReturnVal;
    }

    /* ��ǩ���ֽ���,�������Խ���״̬ */
    if (' ' == cNowChar)
    {
        /* ���״̬ */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_START;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,",=���ʾXML�﷨���� */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0,XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
    ulReturnVal = XML_AddACharToBuff(cNowChar,
                                     g_stXMLCurrentNode.pcNodeLabel,
                                     &(g_stXMLCurrentNode.ulLabelLength),
                                     VOS_FALSE);

    return ulReturnVal;
}
XML_RESULT_ENUM_UINT32 XML_ProcXmlEnterLabel(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* �������а汾��Ϣ */
    if ('?' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* �������� */
    if ('!' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_IGNORE;

        return XML_RESULT_SUCCEED;
    }

    /* ����β�ڵ��ǩ */
    if ('/' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_SINGLE_ENDS_LABLE;

        return XML_RESULT_SUCCEED;
    }

    /* ������ǩ���� */
    if ('>' == cNowChar)
    {
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,",=���ʾXML�﷨���� */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* �����ո� */
    if (' ' != cNowChar)
    {
        /* д�ڵ���Ϣ��NV�� */
        ulReturnVal = XML_WriteNVItem();

        if (XML_RESULT_SUCCEED != ulReturnVal)
        {
            return ulReturnVal;
        }

        /* ����һ���½ڵ�ʱ������սڵ���Ϣ */
        XML_NodeReset();

        /* ���״̬����ʾ����һ���½ڵ� */
        g_ulXMLStatus = XML_ANASTT_NODE_LABLE;

        /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
        ulReturnVal = XML_AddACharToBuff(cNowChar,
                                         g_stXMLCurrentNode.pcNodeLabel,
                                         &(g_stXMLCurrentNode.ulLabelLength),
                                         VOS_FALSE);
    }

    return ulReturnVal;
}



XML_RESULT_ENUM_UINT32 XML_ProcXmlPropertyStart(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* ����β�ڵ��ǩ */
    if ('/' == cNowChar)
    {
        /* ���״̬ */
        g_ulXMLStatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* ��ǩ���� */
    if ('>' == cNowChar)
    {
        /* ���״̬ */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* ��鵱ǰ�ڵ���Ч */
        ulReturnVal = XML_CheckNodeLabelValid();

        return ulReturnVal;
    }

    /* ����<,",=���ʾXML�﷨���� */
    if (('<' == cNowChar)
         ||('"' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* ����״̬ */
    g_ulXMLStatus = XML_ANASTT_PROPERTY_NAME_START;

    ulReturnVal = XML_AddACharToBuff(cNowChar,
                  g_stXMLCurrentNode.stProperty.pcPropertyName,
                  &(g_stXMLCurrentNode.stProperty.ulNameLength),
                  VOS_FALSE);

    return ulReturnVal;
}
XML_RESULT_ENUM_UINT32 XML_ProcXmlPropertyName(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* �ȴ�=��������ֵ���� */
    if ('=' == cNowChar)
    {
        /* ��״̬ */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_NAME_END;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,>,/,"���ʾXML�﷨���� */
    if (('<' == cNowChar)||('>' == cNowChar)
        ||('/' == cNowChar)||('"' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* �����������еĿո����, �� <nv i d="123"> */
    ulReturnVal = XML_AddACharToBuff(cNowChar,
                  g_stXMLCurrentNode.stProperty.pcPropertyName,
                  &(g_stXMLCurrentNode.stProperty.ulNameLength),
                  VOS_FALSE);

    return ulReturnVal;
}



XML_RESULT_ENUM_UINT32 XML_ProcXmlPropertyNameTail(VOS_CHAR cNowChar)
{
    /* �����ո� */
    if ( ' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* �ȴ�" */
    if ('"' == cNowChar)
    {
        /* ����״̬ */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_VALUE_START;

        return XML_RESULT_SUCCEED;
    }

    /* ��������"�����ʾXML�﷨���� */
    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

    return XML_RESULT_FALIED_BAD_SYNTAX;
}



XML_RESULT_ENUM_UINT32 XML_ProcXmlValueStart(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal = XML_RESULT_SUCCEED;

    /* ����" */
    if ('"' == cNowChar)
    {
        /* ��״̬,���ؿ�ʼ�������Ե�״̬ */
        g_ulXMLStatus = XML_ANASTT_PROPERTY_VALUE_END;

        return XML_RESULT_SUCCEED;
    }

    /* ����<,>,/,=���ʾXML�﷨���� */
    if (('<' == cNowChar)
         ||('>' == cNowChar)
         ||('/' == cNowChar)
         ||('=' == cNowChar))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

        return XML_RESULT_FALIED_BAD_SYNTAX;
    }

    /* �ѵ�ǰ�ַ��ӵ�����ֵ�� */
    ulReturnVal = XML_AddACharToBuff(cNowChar,
                  g_stXMLCurrentNode.stProperty.pcPropertyValue,
                  &(g_stXMLCurrentNode.stProperty.ulValueLength),
                  VOS_FALSE);

    return ulReturnVal;
}



XML_RESULT_ENUM_UINT32 XML_ProcXmlValueTail(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* ���Կո� */
    if (' ' == cNowChar)
    {
        return XML_RESULT_SUCCEED;
    }

    /* ����'/' */
    if ('/' == cNowChar)
    {
        /* ���״̬ */
        g_ulXMLStatus = XML_ANASTT_LABLE_END_MUST_RIGHT;

        return XML_RESULT_SUCCEED;
    }

    /* ����'>' */
    if ('>' == cNowChar)
    {
        /* ���״̬,���ؿ�ʼ�������Ե�״̬ */
        g_ulXMLStatus = XML_ANASTT_ORIGINAL;

        /* ��鵱ǰ�ڵ���Ч */
        ulReturnVal = XML_CheckNodeLabelValid();

        return ulReturnVal;
    }

    /* ��������>,/���ʾXML�﷨���� */
    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_SYNTAX);

    return XML_RESULT_FALIED_BAD_SYNTAX;
}
/*Global map table used to find the function according the xml analyse status.*/
XML_FUN g_ulXmlAnalyseFunTbl[] =
{
    XML_ProcXmlOrinigal,         /* ��ʼ״̬�µĴ���                  */
    XML_ProcXmlEnterLabel,       /* ����Lable��Ĵ���                 */
    XML_ProcXmlIgnore,           /* ���Ի�ע��״̬��ֱ������">"����   */
    XML_ProcXmlNodeLabel,        /* ��ǩ���ֿ�ʼ                      */
    XML_ProcXmlSingleEndLabel,   /* ��׼�Ľ�β��ǩ</XXX>              */
    XML_ProcXmlEndMustBeRight,   /* ���� <XXX/>�ı�ǩ,�ڽ�����/��״̬ */
    XML_ProcXmlPropertyStart,    /* ��ʼ��������                      */
    XML_ProcXmlPropertyName,     /* ��ʼ������������                  */
    XML_ProcXmlPropertyNameTail, /* �������ֽ������ȴ�"������ֵ��ʼ   */
    XML_ProcXmlValueStart,       /* ����ֵ��ʼ                        */
    XML_ProcXmlValueTail,        /* ����ֵ����                        */
};

XML_RESULT_ENUM_UINT32 XML_Analyse(VOS_CHAR cNowChar)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* ��鵱ǰ�ַ�����Ч�� */
    ulReturnVal = XML_CheckCharValidity(cNowChar);

    if (XML_RESULT_SUCCEED_IGNORE_CHAR == ulReturnVal)
    {
        /* ����������ԣ����������ַ� */
        return XML_RESULT_SUCCEED;
    }

    if (XML_RESULT_FALIED_BAD_CHAR == ulReturnVal)
    {
        /* ��������Ƿ��ַ�����ֹͣ���� */
        return XML_RESULT_FALIED_BAD_CHAR;
    }

    /* ����XML����ʱ����Ӧ״̬�Ķ�Ӧ���� */
    ulReturnVal = g_ulXmlAnalyseFunTbl[g_ulXMLStatus](cNowChar);

    return ulReturnVal;
}

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)

XML_RESULT_ENUM_UINT32 XML_CalcXmlMd5Value(VOS_CHAR *pcXmlFileReadBuf, VOS_CHAR *pcSaveHashValueBuf, FILE *pfXmlFile, VOS_CHAR *pucHash, VOS_INT32 *plHlen)
{
    VOS_INT32           lReaded = 0;       /* �������ֽ��� */
    VOS_INT32           lHlen = XML_MAP_MD5_HASH_LEN;
    VOS_INT32           lHashBufLen = 0;

    /* ��32K���ݵ������� */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)pcXmlFileReadBuf, sizeof(VOS_CHAR), XML_CHECK_BUFF_SIZE, pfXmlFile);

    /*��ȡ�ļ����ִ���*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while (0 != lReaded)    /* �������ֽ������� 0 */
    {
        lHlen = XML_MAP_MD5_HASH_LEN;

        /* ���õ���ĺ�������ֶ�hashֵ */
        if (MDRV_OK != mdrv_crypto_hash(pcXmlFileReadBuf, lReaded, CRYPTO_ALGORITHM_MD5, pcSaveHashValueBuf + lHashBufLen, (VOS_INT *)&lHlen))
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

            return XML_RESULT_FALIED_BAD_FILE;
        }

        lHashBufLen += lHlen;

        /* ��32K���ݵ������� */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)pcXmlFileReadBuf, sizeof(VOS_CHAR), XML_CHECK_BUFF_SIZE, pfXmlFile);

        /*��ȡ�ļ����ִ���*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }

    /* ���õ���ĺ�����������hashֵ */
    if (MDRV_OK != mdrv_crypto_hash(pcSaveHashValueBuf, lHashBufLen, CRYPTO_ALGORITHM_MD5, pucHash, (VOS_INT *)plHlen))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }

    return XML_RESULT_SUCCEED;
}


XML_RESULT_ENUM_UINT32 XML_CalcXmlCheckValue(VOS_CHAR *pcXmlFilePath, VOS_CHAR *pucHash, VOS_INT32 *plHlen)
{
    VOS_CHAR                    *pcXmlFileReadBuf = VOS_NULL_PTR;
    VOS_CHAR                    *pcSaveHashValueBuf = VOS_NULL_PTR;
    VOS_INT32                   lFileSize;
    FILE                        *pfXmlFile = VOS_NULL_PTR;
    XML_RESULT_ENUM_UINT32      ulReturnVal;

    /* �ж�xnv.xml�ļ��Ƿ���� */
    pfXmlFile = NV_File_Open(pcXmlFilePath, NV_FILE_OPEN_MODE_R);

    if (VOS_NULL_PTR == pfXmlFile)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OPEN_FILE);

        return XML_RESULT_FALIED_OPEN_FILE;
    }

    NV_File_Seek(pfXmlFile, 0, NV_FILE_SEEK_END);

    lFileSize = NV_File_Tell(pfXmlFile);

    NV_File_Seek(pfXmlFile, 0, NV_FILE_SEEK_SET);

    if (lFileSize > XML_MAX_FILE_SIZE)
    {
        NV_File_Close(pfXmlFile);

        /* xml�ļ����󣬴���64M */
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_FILE_TOO_BIG);

        return XML_RESULT_FALIED_FILE_TOO_BIG;
    }

    /* �����ȡ�ļ����ݵĻ����� */
    pcXmlFileReadBuf = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                         DYNAMIC_MEM_PT, XML_CHECK_BUFF_SIZE);

    if (VOS_NULL_PTR == pcXmlFileReadBuf)
    {
        NV_File_Close(pfXmlFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* ����洢�ֶε�xmlУ��hashֵ�Ļ����� */
    pcSaveHashValueBuf = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                         DYNAMIC_MEM_PT, XML_CHECK_BUFF_SIZE);

    if (VOS_NULL_PTR == pcSaveHashValueBuf)
    {
        NV_File_Close(pfXmlFile);

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_OM, pcXmlFileReadBuf);
        /*lint +e534*/

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    ulReturnVal = XML_CalcXmlMd5Value(pcXmlFileReadBuf, pcSaveHashValueBuf, pfXmlFile, pucHash, plHlen);

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_OM, pcSaveHashValueBuf);

    VOS_MemFree(WUEPS_PID_OM, pcXmlFileReadBuf);
    /*lint +e534*/

    NV_File_Close(pfXmlFile);

    return  ulReturnVal;
}


XML_RESULT_ENUM_UINT32 XML_GetProductOffset(XML_XNV_PRDT_OFFSET_STRU *pstOffset, VOS_UINT32 ulNum, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    VOS_UINT32                          ulLow;
    VOS_UINT32                          ulHigh;
    VOS_UINT32                          ulMid;
    VOS_UINT32                          ulOffset;
    XML_XNV_PRDT_OFFSET_STRU            *pstTempOffset;

    ulHigh = ulNum;
    ulLow  = 1;

    /* Binary Search */
    while(ulLow <= ulHigh)
    {
        ulMid = (ulLow + ulHigh)/2;

        ulOffset = ulMid-1;

        pstTempOffset = pstOffset + ulOffset;

        if(pstPrdtOffset->ulPrdtID < pstTempOffset->ulPrdtID)
        {
            ulHigh = ulMid - 1;
        }
        else if(pstPrdtOffset->ulPrdtID > pstTempOffset->ulPrdtID)
        {
            ulLow = ulMid + 1;
        }
        else
        {
            /* �ҵ��˲�ƷID����ȡ��Ӧƫ���� */
            pstPrdtOffset->ulCatNodeOffset  = pstTempOffset->ulCatNodeOffset;
            pstPrdtOffset->ulPrdtNodeOffset = pstTempOffset->ulPrdtNodeOffset;

            return XML_RESULT_SUCCEED;
        }
    }

    pstPrdtOffset->ulCatNodeOffset  = VOS_NULL_DWORD;
    pstPrdtOffset->ulPrdtNodeOffset = VOS_NULL_DWORD;

    return XML_RESULT_FALIED_GET_PRODUCT_OFFSET;
}


XML_RESULT_ENUM_UINT32 XML_SearchProductInfo(FILE* pfMapFile, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    VOS_INT32                   lReaded = 0;       /* �������ֽ��� */
    VOS_UINT32                  ulNum;
    VOS_INT                     lProductId;
    XML_XNV_PRDT_OFFSET_STRU    *pstOffset = VOS_NULL_PTR;
    XML_RESULT_ENUM_UINT32      ulReturnVal;

    /* ȡ�õ�ǰ�����Product id */
    lProductId = (mdrv_ver_get_info()->sthwverinfo).hwindex;

    if(VOS_ERROR == lProductId)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_GET_PRODUCTID);

        return XML_RESULT_FALIED_GET_PRODUCTID;
    }

    /* �����ƷID */
    pstPrdtOffset->ulPrdtID = (VOS_UINT32)lProductId;

    if(VOS_OK != NV_File_Seek(pfMapFile, sizeof(XML_XNV_MAP_HEAD_STRU), NV_FILE_SEEK_SET))
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_SEEK_FILE);

        return XML_RESULT_FALIED_SEEK_FILE;
    }

    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff,
                                      sizeof(VOS_CHAR),
                                     (XML_FILE_READ_BUFF_SIZE / sizeof(XML_XNV_PRDT_OFFSET_STRU)) * sizeof(XML_XNV_PRDT_OFFSET_STRU),
                                      pfMapFile);

    /*��ȡ�ļ����ִ���*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while(0 != lReaded)
    {
        ulNum = (VOS_UINT32)lReaded / sizeof(XML_XNV_PRDT_OFFSET_STRU);

        pstOffset = (XML_XNV_PRDT_OFFSET_STRU *)g_pcFileReadBuff;

        /* ��ǰ��ƷID�ȶ����������е�id��Сֵ��С�������ʧ�� */
        if (pstPrdtOffset->ulPrdtID < pstOffset->ulPrdtID)
        {
            pstPrdtOffset->ulCatNodeOffset  = VOS_NULL_DWORD;
            pstPrdtOffset->ulPrdtNodeOffset = VOS_NULL_DWORD;

            return XML_RESULT_FALIED_GET_PRODUCT_OFFSET;
        }

        /* ��ǰ��ƷID�ȶ����������е�id���ֵС�����ڱ��ζ����������ж��ַ����� */
        if (pstPrdtOffset->ulPrdtID <= (pstOffset + (ulNum -1))->ulPrdtID)
        {
            /* ���ַ����� */
            ulReturnVal = XML_GetProductOffset(pstOffset, ulNum, pstPrdtOffset);

            return ulReturnVal;
        }

        /* ���ζ�����������û�е�ǰ��Ʒ��Ϣ�������� */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff,
                                          sizeof(VOS_CHAR),
                                         (XML_FILE_READ_BUFF_SIZE / sizeof(XML_XNV_PRDT_OFFSET_STRU)) * sizeof(XML_XNV_PRDT_OFFSET_STRU),
                                          pfMapFile);


        /*��ȡ�ļ����ִ���*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }

    /* �����Ҳ����û�ҵ���Ӧ��product id */
    pstPrdtOffset->ulCatNodeOffset  = VOS_NULL_DWORD;
    pstPrdtOffset->ulPrdtNodeOffset = VOS_NULL_DWORD;

    return XML_RESULT_FALIED_GET_PRODUCT_OFFSET;
}


XML_RESULT_ENUM_UINT32 XML_DecodeMapFile(VOS_CHAR *pcMapFilePath, VOS_CHAR *pcXmlFilePath, VOS_UINT32  *pulProductNum, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    XML_RESULT_ENUM_UINT32      ulReturnVal;
    XML_XNV_MAP_HEAD_STRU       stMapHeader;
    VOS_INT32                   lReaded = 0;       /* �������ֽ��� */
#ifdef XML_CHECK_MD5
    VOS_CHAR                    aucHash[XML_MAP_MD5_HASH_LEN] = {0};
    VOS_INT32                   lHlen = XML_MAP_MD5_HASH_LEN;
#endif
    FILE                        *pfMapFile = VOS_NULL_PTR;
    VOS_UINT32                  ulFileLen;

    /*lint -e534*/
    VOS_MemSet(&stMapHeader, 0, sizeof(stMapHeader));
    /*lint +e534*/

    /* �������ļ� */
    /* �ж�xnv.map�ļ��Ƿ���� */
    pfMapFile = NV_File_Open(pcMapFilePath, NV_FILE_OPEN_MODE_R);

    if (VOS_NULL_PTR == pfMapFile)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_OPEN_FILE);

        return XML_RESULT_FALIED_OPEN_FILE;
    }

    /* ��ȡ�ļ���С */
    NV_File_Seek(pfMapFile, 0, NV_FILE_SEEK_END);

    ulFileLen = (VOS_UINT32)NV_File_Tell(pfMapFile);

    NV_File_Seek(pfMapFile, 0, NV_FILE_SEEK_SET);

    /* ��MAP�ļ�ͷ24���ֽ����ݵ������� */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)&stMapHeader, sizeof(VOS_CHAR), sizeof(XML_XNV_MAP_HEAD_STRU), pfMapFile);

    /*��ȡ�ļ����ִ���*/
    if (MDRV_ERROR == lReaded)
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    /* �ж��ļ���ʶ�� */
    if (XML_MAP_FILE_MAGIC_NUM != stMapHeader.ulMagNumber)
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_MAGIC_NUM);

        return XML_RESULT_FALIED_BAD_MAGIC_NUM;
    }

    /* �ж��ļ���С��product id�����Ƿ�ƥ�� */
    if (sizeof(XML_XNV_MAP_HEAD_STRU) + stMapHeader.ulProductNum * sizeof(XML_XNV_PRDT_OFFSET_STRU) != ulFileLen)
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }

/* �Ƿ�Ҫ����MD5У�� */
#ifdef XML_CHECK_MD5
    /* �ж�xnv.xmlУ���Ƿ�ok */
    if (XML_RESULT_SUCCEED != XML_CalcXmlCheckValue(pcXmlFilePath, aucHash, &lHlen))
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }

    /* �Ƚ�У��ֵ */
    if (VOS_OK != VOS_MemCmp(aucHash, (VOS_CHAR *)stMapHeader.aulXnvMD5, (VOS_UINT32)lHlen))
    {
        NV_File_Close(pfMapFile);

        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_BAD_FILE);

        return XML_RESULT_FALIED_BAD_FILE;
    }
#endif

    *pulProductNum = stMapHeader.ulProductNum;

    /* ���Ҳ�Ʒ��xml�ļ��е�ƫ���� */
    ulReturnVal = XML_SearchProductInfo(pfMapFile, pstPrdtOffset);

    NV_File_Close(pfMapFile);

    return ulReturnVal;
}


XML_RESULT_ENUM_UINT32 XML_DecodeProductCatXMLFile(FILE* pfFile, VOS_UINT32 ulProductNum, XML_XNV_PRDT_OFFSET_STRU *pstPrdtOffset)
{
    VOS_INT32                   lReaded = 0;       /* �������ֽ��� */
    VOS_INT32                   lCount;            /* ������������ */
    XML_RESULT_ENUM_UINT32      ulReturnVal;

    /* ��4K���ݵ������� */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR), XML_FILE_READ_BUFF_SIZE, pfFile);

    /*��ȡ�ļ����ִ���*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while (0 != lReaded)    /* �������ֽ������� 0 */
    {
        /* ����ַ����д��� */
        for (lCount = 0; lCount < lReaded; lCount++)
        {
            /* ��ʼ���� */
            ulReturnVal = XML_Analyse(*(g_pcFileReadBuff + lCount));

            if(XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* ��������������ֹͣ���� */
                return ulReturnVal;
            }

            /* �������ֽ�����ɺ�����ѭ�� */
            if (XML_PRODUCT_COMMON_ANALYZE_FINISH == g_enProductDecodeStatus)
            {
                if((0 == ulProductNum) || (VOS_NULL_DWORD == pstPrdtOffset->ulCatNodeOffset))
                {
                    g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_FINISHED;

                    return XML_RESULT_SUCCEED;
                }

                if(VOS_OK != NV_File_Seek(pfFile, (VOS_INT32)pstPrdtOffset->ulCatNodeOffset, NV_FILE_SEEK_SET))
                {
                    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_SEEK_FILE);

                    return XML_RESULT_FALIED_SEEK_FILE;
                }

                g_enProductDecodeStatus = XML_PRODUCT_CAT_ANALYZE_START;

                break;
            }

            if (XML_PRODUCT_CAT_ANALYZE_FINISH == g_enProductDecodeStatus)
            {
                if(VOS_NULL_DWORD == pstPrdtOffset->ulPrdtNodeOffset)
                {
                    g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_FINISHED;

                    return XML_RESULT_SUCCEED;
                }

                if(VOS_OK != NV_File_Seek(pfFile, (VOS_INT32)pstPrdtOffset->ulPrdtNodeOffset, NV_FILE_SEEK_SET))
                {
                    XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_SEEK_FILE);

                    return XML_RESULT_FALIED_SEEK_FILE;
                }

                g_enProductDecodeStatus = XML_PRODUCT_ID_ANALYZE_START;

                break;
            }

            /* �ж��Ƿ������� */
            if (XML_DECODE_STATUS_FINISHED == g_stXMLProductInfo.enXMLDecodeState)
            {
                return XML_RESULT_SUCCEED;
            }
        }

        /* ����һ������ */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR),
                                XML_FILE_READ_BUFF_SIZE, pfFile);

        /*��ȡ�ļ����ִ���*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__,0,XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }/* end of while (0 != lReaded) */

    return XML_RESULT_FALIED_BAD_FILE;
}
#endif
XML_RESULT_ENUM_UINT32 XML_DecodeXMLFile(FILE* pfFile)
{
    VOS_INT32               lReaded = 0;       /* �������ֽ��� */
    VOS_INT32               lCount;            /* ������������ */
    XML_RESULT_ENUM_UINT32  ulReturnVal;

    /* ��4K���ݵ������� */
    lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR), XML_FILE_READ_BUFF_SIZE, pfFile);

    /*��ȡ�ļ����ִ���*/
    if (MDRV_ERROR == lReaded)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_READ_FILE);

        return XML_RESULT_FALIED_READ_FILE;
    }

    while (0 != lReaded)    /* �������ֽ������� 0 */
    {
        /* ����ַ����д��� */
        for (lCount = 0; lCount < lReaded; lCount++)
        {
            /* ��ʼ���� */
            ulReturnVal = XML_Analyse(*(g_pcFileReadBuff + lCount));

            if(XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* ��������������ֹͣ���� */
                return ulReturnVal;
            }

            /* �ж��Ƿ������� */
            if (XML_DECODE_STATUS_FINISHED
                == g_stXMLProductInfo.enXMLDecodeState)
            {
                return XML_RESULT_SUCCEED;
            }
        }

        /* ����һ������ */
        lReaded = (VOS_INT32)NV_File_Read((VOS_VOID *)g_pcFileReadBuff, sizeof(VOS_CHAR),
                                XML_FILE_READ_BUFF_SIZE, pfFile);

        /*��ȡ�ļ����ִ���*/
        if (MDRV_ERROR == lReaded)
        {
            XML_WriteErrorLog(__LINE__,0,XML_RESULT_FALIED_READ_FILE);

            return XML_RESULT_FALIED_READ_FILE;
        }
    }/* end of while (0 != lReaded) */

    /* ���ulNodeLevel��Ϊ0��˵��<product>û���������� */
    if (0 != g_stXMLProductInfo.ulNodeLevel)
    {
        XML_WriteErrorLog(__LINE__,0,XML_RESULT_FALIED_PRODUCT_MATCH);

        return XML_RESULT_FALIED_PRODUCT_MATCH;
    }

    return XML_RESULT_SUCCEED;
}
XML_RESULT_ENUM_UINT32 XML_GetProductId(VOS_VOID)
{
    VOS_INT                             lProductId;

    /* ����ڴ� */
    /*lint -e534*/
    VOS_MemSet(g_stXMLProductInfo.acProductId, 0, XML_MAX_HARDWARE_LEN);
    /*lint +e534*/

    /* ȡ�õ�ǰ�����Product id */
    lProductId = (mdrv_ver_get_info()->sthwverinfo).hwindex;

#if (VOS_OS_VER == VOS_WIN32)
    /*lint -e534*/
    /* ��snprintf �� windows ������windows ���� "\0" ���� �ٴ�ӡһλ��*/
    _snprintf(g_stXMLProductInfo.acProductId, (sizeof(g_stXMLProductInfo.acProductId) - 1), "%d", lProductId);
    /*lint +e534*/

#else
    /*lint -e534*/
    snprintf(g_stXMLProductInfo.acProductId, sizeof(g_stXMLProductInfo.acProductId), "%d", lProductId);
    /*lint +e534*/
#endif

    NV_Printf("XML_GetProductId: Product id is :%s\r\n", g_stXMLProductInfo.acProductId);

    return XML_RESULT_SUCCEED;
}
VOS_VOID XML_InitGlobal(VOS_VOID)
{
    /* ��ʼ��Product�ڵ���Ϣ */
    g_stXMLProductInfo.enValidNode      = XML_PRODUCT_NODE_STATUS_INVALID;
    g_stXMLProductInfo.enXMLDecodeState = XML_DECODE_STATUS_DECODING;
    g_stXMLProductInfo.ulNodeLevel      = 0; /* ��¼product�ڵ���ֵĴ��� */

    /* ��ʼ����ǰ״̬ */
    g_ulXMLStatus = XML_ANASTT_ORIGINAL;

    /* ���ڼ�¼��ȡXML�ļ������� */
    g_ulLineNo    = 1;

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    g_enProductDecodeStatus = XML_PRODUCT_ANALYZE_START;
#endif

    return ;
}



XML_RESULT_ENUM_UINT32 XML_ProcInit(VOS_VOID)
{
    XML_RESULT_ENUM_UINT32 ulReturnVal;

    /* ��ʼ��ȫ�ֱ��� */
    XML_InitGlobal();

    /* ��õ�ǰ�����product id*/
    ulReturnVal = XML_GetProductId();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* �����ڵ���Ϣ */
    ulReturnVal = XML_CreateANode();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        return ulReturnVal;
    }

    /* ������NV Item��ֵ�Ļ�����,+1Ϊ�����ַ����������� */
    g_pucNVItem = (VOS_UINT8 *)VOS_MemAlloc(WUEPS_PID_OM,
                                         DYNAMIC_MEM_PT,
                                         XML_NODE_VALUE_BUFF_LENGTH_ORIGINAL+1);
    if (VOS_NULL_PTR == g_pucNVItem)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    /* �����ȡ�ļ����ݵĻ�����,+1Ϊ�����ַ����������� */
    g_pcFileReadBuff = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM,
                                                DYNAMIC_MEM_PT,
                                                XML_FILE_READ_BUFF_SIZE+1);
    if (VOS_NULL_PTR == g_pcFileReadBuff)
    {
        XML_WriteErrorLog(__LINE__, 0, XML_RESULT_FALIED_MALLOC);

        return XML_RESULT_FALIED_MALLOC;
    }

    g_stXmlErrorInfo.ulResult = XML_RESULT_SUCCEED;

    return XML_RESULT_SUCCEED;
}
VOS_VOID XML_FreeMem(VOS_VOID)
{
    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.stProperty.pcPropertyName);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.stProperty.pcPropertyValue);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.pcNodeLabel);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.pcNodeLabelEnd);

    VOS_MemFree(WUEPS_PID_OM, g_stXMLCurrentNode.pcNodeValue);

    VOS_MemFree(WUEPS_PID_OM, g_pucNVItem);

    VOS_MemFree(WUEPS_PID_OM, g_pcFileReadBuff);
    /*lint +e534*/
}


XML_RESULT_ENUM_UINT32 XML_OpenAndDecodeXMLFile(VOS_CHAR *pcFilePath)
{
    FILE                               *pFile  = VOS_NULL_PTR;
    XML_RESULT_ENUM_UINT32              ulReturnVal;

    pFile = NV_File_Open(pcFilePath, NV_FILE_OPEN_MODE_R);

    if (VOS_NULL_PTR == pFile)
    {
        NV_Printf("XML_OpenAndDecodeXMLFile: Open %s fail��\r\n ", pcFilePath);

        return XML_RESULT_FALIED_FILE_OPERATE;
    }

    /* ������һ��XML�ļ�����ʱ������ȫ�ֱ�����״̬ */
    XML_InitGlobal();

    ulReturnVal = XML_DecodeXMLFile(pFile);

    /* �ر��ļ� */
    /*lint -e534*/
    mdrv_file_close(pFile);
    /*lint +e534*/

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        /* �������ʧ��,�򵥰��쳣���� */
        mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                             (VOS_CHAR *)&g_stXmlErrorInfo,
                             sizeof(g_stXmlErrorInfo));
        NV_Printf("XML_OpenAndDecodeXMLFile: Decode  %s fail.\r\n", pcFilePath);

        return ulReturnVal;
    }

    return XML_RESULT_SUCCEED;
}
VOS_VOID XML_DecodeOperator(VOS_BOOL *pbIsDecodeXml)
{
#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};
    XML_RESULT_ENUM_UINT32              ulReturnVal;

    /* ��ȡoperator.xmlȫ·�� */
    if (VOS_OK != NV_SkuGetOperatorPath(acFilePath))
    {
        NV_Printf("XML_DecodeOperator: Get operator.xml file path fail.\r\n");
        return;
    }

    ulReturnVal = XML_OpenAndDecodeXMLFile(acFilePath);

    if((XML_RESULT_SUCCEED != ulReturnVal) && (XML_RESULT_FALIED_FILE_OPERATE != ulReturnVal))
    {
        NV_Printf("XML_DecodeOperator: xml decode fail %d", ulReturnVal);
        return;
    }

    *pbIsDecodeXml = VOS_TRUE;

#endif

    return;
}
VOS_VOID XML_DecodeMain(VOS_BOOL *pbIsDecodeXml)
{
    VOS_INT32                   lExistXNVFile  = VOS_FALSE;
    VOS_INT32                   lExistCUSTFile = VOS_FALSE;
    XML_RESULT_ENUM_UINT32      ulReturnVal;
    VOS_UINT32                  i;
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
    XML_XNV_PRDT_OFFSET_STRU    stPrdtOfffset;
    VOS_UINT32                  ulProductNum;
#endif

    /* ��ʱ����ģ��ȫ���������� */
    ulReturnVal = XML_ProcInit();

    if (XML_RESULT_SUCCEED != ulReturnVal)
    {
        /* �����ʼ��ʧ��,�򵥰��쳣���� */
        mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                             (VOS_CHAR *)&g_stXmlErrorInfo,
                             sizeof(g_stXmlErrorInfo));

        return;
    }

    for (i=0; i<(sizeof(g_astXMLFilePath)/sizeof(g_astXMLFilePath[0])); i++)
    {
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /*lint -e534*/
        VOS_MemSet(&stPrdtOfffset, 0, sizeof(stPrdtOfffset));
        /*lint +e534*/

        ulReturnVal = XML_DecodeMapFile(g_astMapFilePath[i].pcMapPath, g_astXMLFilePath[i].pcXNVPath, &ulProductNum, &stPrdtOfffset);

        if ((XML_RESULT_SUCCEED != ulReturnVal) && (XML_RESULT_FALIED_GET_PRODUCT_OFFSET != ulReturnVal))
        {
            continue;
        }
#endif
        lExistXNVFile  = VOS_FALSE;
        lExistCUSTFile = VOS_FALSE;

        /* �ж�xnv.XML�ļ��Ƿ���� */
        g_lEnvFile = mdrv_file_open(g_astXMLFilePath[i].pcXNVPath, NV_FILE_OPEN_MODE_R);

        if (VOS_NULL_PTR != g_lEnvFile)
        {
            lExistXNVFile = VOS_TRUE;
        }

        /* �ж�CUST.XML�ļ��Ƿ���� */
        g_lCustFile = mdrv_file_open(g_astXMLFilePath[i].pcCUSTPath, NV_FILE_OPEN_MODE_R);

        if (VOS_NULL_PTR != g_lCustFile)
        {
            lExistCUSTFile = VOS_TRUE;
        }

        /* ���ENV.xml��cust.xml��������,��ֱ�ӷ��� */
        if ((VOS_FALSE == lExistXNVFile) && (VOS_FALSE == lExistCUSTFile))
        {
            continue;
        }

        /* ���浱ǰ������modem ID */
        g_enXMLCurModemID   = (VOS_UINT16)i;

        /* ����xnv.xml�ļ�  */
        if (VOS_TRUE == lExistXNVFile)
        {
#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
            /* ����֧�ֲ�Ʒcat��xnv.xml*/
            ulReturnVal = XML_DecodeProductCatXMLFile(g_lEnvFile, ulProductNum, &stPrdtOfffset);
#else
            ulReturnVal = XML_DecodeXMLFile(g_lEnvFile);
#endif
            /* �ر��ļ� */
            /*lint -e534*/
            mdrv_file_close(g_lEnvFile);
            /*lint +e534*/

            g_lEnvFile = VOS_NULL_PTR;

            if (XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* �ͷ��ѷ�����ڴ� */
                XML_FreeMem();

                /* �������ʧ��,�򵥰��쳣���� */
                mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                                     (VOS_CHAR *)&g_stXmlErrorInfo,
                                     sizeof(g_stXmlErrorInfo));

                return;
            }

            *pbIsDecodeXml = VOS_TRUE;

        }

        /* ����cust.xml�ļ� */
        if (VOS_TRUE == lExistCUSTFile)
        {
            /* ������һ��XML�ļ�����ʱ������ȫ�ֱ�����״̬ */
            XML_InitGlobal();

            ulReturnVal = XML_DecodeXMLFile(g_lCustFile);

            /* �ر��ļ� */
            /*lint -e534*/
            mdrv_file_close(g_lCustFile);
            /*lint +e534*/

            g_lCustFile = VOS_NULL_PTR;

            if (XML_RESULT_SUCCEED != ulReturnVal)
            {
                /* �ͷ��ѷ�����ڴ� */
                XML_FreeMem();

                /* �������ʧ��,�򵥰��쳣���� */
                mdrv_om_system_error(FAIL_TO_DECODE_XML, VOS_FILE_ID, __LINE__,
                                     (VOS_CHAR *)&g_stXmlErrorInfo,
                                     sizeof(g_stXmlErrorInfo));

                return;
            }

            *pbIsDecodeXml = VOS_TRUE;

        }

        /* ������һ��XML�ļ�����ʱ������ȫ�ֱ�����״̬ */
        XML_InitGlobal();
    }

    /* operator.xml �ļ����� */
    XML_DecodeOperator(pbIsDecodeXml);

    /* �ͷ��ѷ�����ڴ� */
    XML_FreeMem();

    return;
}
VOS_VOID XML_DeleteFile(VOS_VOID)
{
    VOS_UINT32              i;

    if(XML_RESULT_SUCCEED != g_stXmlErrorInfo.ulResult)
    {
        /* xml�����쳣 */
        return;
    }

    for(i=0; i<(sizeof(g_astXMLFilePath)/sizeof(g_astXMLFilePath[0])); i++)
    {
        /* ɾ��xnv�ļ� */
        mdrv_file_remove(g_astXMLFilePath[i].pcXNVPath);

        /* ɾ��cust�ļ� */
        mdrv_file_remove(g_astXMLFilePath[i].pcCUSTPath);

#if (FEATURE_ON == FEATURE_XNV_SUPPORT_PRODUCT_CAT)
        /* ɾ��map�ļ� */
        mdrv_file_remove(g_astMapFilePath[i].pcMapPath);
#endif
    }
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

