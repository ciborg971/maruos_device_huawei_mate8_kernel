

/*****************************************************************************
1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"
#include "OamXmlComm.h"


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_VSIM_XML_C

/*****************************************************************************
2 ȫ�ֱ�������
*****************************************************************************/
typedef VOS_UINT32 (*OAM_XML_ANALYSE_FUNC)(OAM_XML_CTX_INNER_STRU *pstXmlCtxInner);

/*****************************************************************************
3 ��������
*****************************************************************************/
#if (FEATURE_VSIM == FEATURE_ON)

VOS_INT32 OAM_XML_GetChildCount(OAM_XML_NODE_STRU *pstNode)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetChildCount: pstNode is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    lCounter = 0;

    /* �ӳ�������ͷ��ʼ, ���������ӽڵ� */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        lCounter++;
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return lCounter;
}


OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lChildIndex)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetChildNodeByIndex: pstNode is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    lCounter = 0;

    /* �ӳ�������ͷ��ʼ,���������ӽڵ� */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        if (lCounter == lChildIndex)
        {
            return pstTmpNode;
        }
        lCounter++;
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return VOS_NULL_PTR;
}


OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByLabel(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcLabel)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    VOS_UINT32                          ulLabelLength;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcLabel))
    {
        XML_WARNING_LOG("OAM_XML_GetChildNodeByLabel: pstNode or pcLabel is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* �ӳ�������ͷ��ʼ,���������ӽڵ� */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        ulLabelLength   = pstTmpNode->ulLabelLength;
        if (VOS_StrLen(pcLabel) == ulLabelLength)
        {
            if (0 == VOS_MemCmp(pstTmpNode->pcNodeLabel, pcLabel, ulLabelLength))
            {
                return pstTmpNode;
            }
        }
        pstTmpNode = pstTmpNode->pstNexBrother;
    }

    return VOS_NULL_PTR;
}


OAM_XML_NODE_STRU* OAM_XML_GetChildNodeByAttributeValue(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribValue)
{
    OAM_XML_NODE_STRU                 *pstTmpNode;
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_UINT32                          ulValueLength;
    VOS_CHAR                          *pcContent;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcAttribValue))
    {
        XML_WARNING_LOG("OAM_XML_GetChildNodeByAttributeValue: pstNode or pcAttribValue is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* �ӳ�������ͷ��ʼ,���������ӽڵ� */
    pstTmpNode = pstNode->pstFirstChild;
    while (VOS_NULL_PTR != pstTmpNode)
    {
        pstTmpAttribute = pstTmpNode->pstFirstAttrib;
        if(VOS_NULL_PTR == pstTmpAttribute)
        {
            XML_WARNING_LOG("OAM_XML_GetChildNodeByAttributeValue: pstTmpAttribute is VOS_NULL_PTR!");
            return VOS_NULL_PTR;
        }

        pcContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstTmpAttribute->ulValueLength);

        if(VOS_NULL_PTR == pcContent)
        {
            XML_WARNING_LOG("OAM_XML_GetChildNodeByAttributeValue: The VOS_MemAlloc is NULL ");

            return VOS_NULL_PTR;
        }

        OAM_XML_GetStrContent(pstTmpAttribute->pcAttribValue,pstTmpAttribute->ulValueLength,pcContent,&ulValueLength);

        if (VOS_StrLen(pcAttribValue) == ulValueLength)
        {
            if (0 == VOS_MemCmp(pcContent, pcAttribValue, ulValueLength))
            {
                /*lint -e534*/
                VOS_MemFree(WUEPS_PID_USIM, pcContent);
                /*lint +e534*/
                return pstTmpNode;
            }
        }
        pstTmpNode = pstTmpNode->pstNexBrother;
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcContent);
        /*lint +e534*/
    }

    return VOS_NULL_PTR;
}


VOS_INT32 OAM_XML_GetAttributeCount(OAM_XML_NODE_STRU *pstNode)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetAttributeCount: pstNode is VOS_NULL_PTR!");
        return VOS_ERROR;
    }

    lCounter = 0;

    /* �ӳ�������ͷ��ʼ,���������ӽڵ� */
    pstTmpAttribute = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttribute)
    {
        lCounter++;
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return lCounter;
}


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByIndex(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_INT32                           lAttribIndex)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;
    VOS_INT32                           lCounter;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstNode)
    {
        XML_WARNING_LOG("OAM_XML_GetAttributeByIndex: pstNode is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    lCounter = 0;

    /* ������ͷ��ʼ,���������ӽڵ� */
    pstTmpAttribute = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttribute)
    {
        if (lCounter == lAttribIndex)
        {
            return pstTmpAttribute;
        }
        lCounter++;
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return VOS_NULL_PTR;
}


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetAttributeByAttributeName(
    OAM_XML_NODE_STRU                 *pstNode,
    VOS_CHAR                           *pcAttribName)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;
    VOS_UINT32                          ulNameLength;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pcAttribName))
    {
        XML_WARNING_LOG("OAM_XML_GetAttributeByAttributeName: pstNode or pcAttribName is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* ������ͷ��ʼ,������������ */
    pstTmpAttrib = pstNode->pstFirstAttrib;
    while (VOS_NULL_PTR != pstTmpAttrib)
    {
        ulNameLength = pstTmpAttrib->ulNameLength;
        if (VOS_StrLen(pcAttribName) == ulNameLength)
        {
            if (0 == VOS_MemCmp(pstTmpAttrib->pcAttribName, pcAttribName, ulNameLength))
            {
                return pstTmpAttrib;
            }
        }
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    XML_WARNING_LOG("OAM_XML_GetAttributeByAttributeName: Can't find the Attribute!");
    return VOS_NULL_PTR;
}


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_GetLastAttribute(
    OAM_XML_NODE_STRU                 *pstNode)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttribute;

    pstTmpAttribute = pstNode->pstFirstAttrib;

    /* �ڵ���������ֱ�ӷ��ؿ�ָ�� */
    if (VOS_NULL_PTR == pstTmpAttribute)
    {
        return VOS_NULL_PTR;
    }

    /* ������ͷ��ʼ, ���������ӽڵ�, ֱ�����һ������ */
    while (VOS_NULL_PTR != pstTmpAttribute->pstNexBrother)
    {
        pstTmpAttribute = pstTmpAttribute->pstNexBrother;
    }

    return pstTmpAttribute;
}


OAM_XML_RESULT_ENUM_UINT32 OAM_XML_InitMemory(OAM_XML_CTX_STRU *pstXmlCtx)
{
    /* ���������ڴ��ַΪ��, ������ڴ沢��ʼ�� */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
    {
        pstXmlCtx->ulXMLBuffSize    = OAM_XML_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffer     = (VOS_UINT8*)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT,pstXmlCtx->ulXMLBuffSize);
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;

        /* �����ڴ�ʧ�� */
        if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffer)
        {
            XML_ERROR_LOG("OAM_XML_InitMemory: Malloc Failure!");
            return OAM_XML_RESULT_FALIED_MALLOC;
        }
    }
    /* �������ѷ����ڴ�ռ�, ��ֻ���ʼ�� */
    else
    {
        pstXmlCtx->ulXMLBuffSize    = OAM_XML_BUFF_SIZE;
        pstXmlCtx->pucXMLBuffCur    = pstXmlCtx->pucXMLBuffer;
    }

    /*lint -e534*/
    VOS_MemSet(pstXmlCtx->pucXMLBuffer, 0x00, pstXmlCtx->ulXMLBuffSize);
    /*lint +e534*/

    return OAM_XML_RESULT_SUCCEED;
}
VOS_VOID* OAM_XML_Malloc(
    OAM_XML_CTX_STRU                  *pstXmlCtx,
    VOS_UINT32                          ulSize)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;
    VOS_INT32                           iRemainMemSize;
    VOS_VOID                           *pReturn;

    pReturn     = VOS_NULL_PTR;
    ulReturnVal = OAM_XML_RESULT_SUCCEED;

    /* �ж��������еĵ�ǰ�ڴ�ָ���Ƿ����, ����������ó�ʼ���ڴ溯�� */
    if (VOS_NULL_PTR == pstXmlCtx->pucXMLBuffCur)
    {
        ulReturnVal = OAM_XML_InitMemory(pstXmlCtx);
    }

    if (OAM_XML_RESULT_SUCCEED == ulReturnVal)
    {
        /* �ж����������ڴ��Ƿ��� */
        iRemainMemSize = (pstXmlCtx->pucXMLBuffer
                       + pstXmlCtx->ulXMLBuffSize)
                       - pstXmlCtx->pucXMLBuffCur;
        if ((VOS_INT32)ulSize > iRemainMemSize)
        {
            pReturn = VOS_NULL_PTR;
        }
        else
        {
            pReturn = (VOS_VOID*)pstXmlCtx->pucXMLBuffCur;
            pstXmlCtx->pucXMLBuffCur += ulSize;
        }
    }

    return pReturn;
}


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_CreateAnAttribute(OAM_XML_CTX_STRU *pstXmlCtx)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstAttribute;
    VOS_UINT32                          ulAttribStruSize;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("OAM_XML_CreateAnAttribute: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstAttribute        = VOS_NULL_PTR;
    ulAttribStruSize    = sizeof(OAM_XML_NODE_ATTRIBUTE_STRU);

    /* ����XMLģ���ڴ���亯��������һ��ڵ��ڴ� */
    pstAttribute = (OAM_XML_NODE_ATTRIBUTE_STRU*)OAM_XML_Malloc(pstXmlCtx, ulAttribStruSize);

    return pstAttribute;
}



OAM_XML_NODE_STRU* OAM_XML_CreateANode(OAM_XML_CTX_STRU *pstXmlCtx)
{
    OAM_XML_NODE_STRU                 *pstNode;
    VOS_UINT32                          ulNodeStruSize;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("OAM_XML_CreateANode: pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    pstNode         = VOS_NULL_PTR;
    ulNodeStruSize  = sizeof(OAM_XML_NODE_STRU);

    /* ����XMLģ���ڴ���亯��������һ��ڵ��ڴ� */
    pstNode = (OAM_XML_NODE_STRU*)OAM_XML_Malloc(pstXmlCtx, ulNodeStruSize);

    return pstNode;
}




OAM_XML_RESULT_ENUM_UINT32 OAM_XML_AddAChildNode(
    OAM_XML_NODE_STRU                 *pstFather,
    OAM_XML_NODE_STRU                 *pstChild,
    OAM_XML_NODE_STRU                 *pstYoungBrother)
{
    OAM_XML_NODE_STRU                 *pstTmpChild;
    OAM_XML_NODE_STRU                 *pstLastChild;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstFather) || (VOS_NULL_PTR == pstChild))
    {
        XML_WARNING_LOG("OAM_XML_AddAChildNode: pstFather or pstChild is VOS_NULL_PTR!");
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �趨���� */
    pstChild->pstFather = pstFather;

    /* �趨���� */
    /* ����ýڵ㻹û�к��ӣ���Ѳ���Ľڵ���Ϊ�׽ڵ� */
    if (VOS_NULL_PTR == pstFather->pstFirstChild)
    {
        pstFather->pstFirstChild    = pstChild;

        /* ������ӵ�������ӵ������ϵ */
        pstChild->pstPreBrother     = VOS_NULL_PTR;
        pstChild->pstNexBrother     = VOS_NULL_PTR;

        return OAM_XML_RESULT_SUCCEED;
    }

    /* ����ʱ����pstTmpChild�����ӽڵ�����, ֱ���ҵ�����ָ�����ӽڵ�ĵܵ� */
    pstTmpChild     = pstFather->pstFirstChild; /* �ӳ��ӿ�ʼ */
    pstLastChild    = VOS_NULL_PTR;
    while (VOS_NULL_PTR != pstTmpChild)
    {
        pstLastChild = pstTmpChild;
        if (pstTmpChild == pstYoungBrother)
        {
            break;
        }
        pstTmpChild = pstTmpChild->pstNexBrother;
    }

    /* û���ҵ�ָ���ĵܵܣ�����㣩 */
    if (VOS_NULL_PTR == pstTmpChild )
    {
        if ( (VOS_NULL_PTR != pstYoungBrother)
          || (VOS_NULL_PTR == pstLastChild) )
        {
            return OAM_XML_RESULT_FAILED_NODE_NOT_FOUND;
        }
        else
        {
            pstLastChild->pstNexBrother = pstChild;
            pstChild->pstPreBrother     = pstLastChild;
            pstChild->pstNexBrother     = VOS_NULL_PTR;
            return OAM_XML_RESULT_SUCCEED;
        }
    }

    if (pstFather->pstFirstChild == pstTmpChild)
    {
        /* �ܵ�Ϊԭ���� */
        pstFather->pstFirstChild    = pstChild;
        pstChild ->pstPreBrother    = VOS_NULL_PTR;
        pstChild ->pstNexBrother    = pstTmpChild;
        pstTmpChild->pstPreBrother  = pstChild;
    }
    else
    {
        pstChild ->pstPreBrother    = pstTmpChild->pstPreBrother;
        pstChild ->pstNexBrother    = pstTmpChild;
        pstTmpChild->pstPreBrother  = pstChild;
        pstChild->pstPreBrother->pstNexBrother = pstChild;
    }

    return OAM_XML_RESULT_SUCCEED;
}
OAM_XML_RESULT_ENUM_UINT32 OAM_XML_AddAnAttribute(
    OAM_XML_NODE_STRU                 *pstNode,
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstAttribute,
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstYoungBrother)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pstNode) || (VOS_NULL_PTR == pstAttribute))
    {
        XML_WARNING_LOG("OAM_XML_AddAnAttribute: pstNode or pstAttribute is VOS_NULL_PTR!");
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* ����ýڵ㻹û�����ԣ����׸����Լ�ΪpstYoungBrother����Ѳ�������Ե����׸����� */
    if ( (VOS_NULL_PTR == pstNode->pstFirstAttrib)
      || (pstYoungBrother == pstNode->pstFirstAttrib) )
    {
        /* ������ӵ�������Ե������ϵ */
        pstAttribute->pstPreBrother         = VOS_NULL_PTR;
        pstAttribute->pstNexBrother         = pstNode->pstFirstAttrib;
        if (VOS_NULL_PTR != pstYoungBrother)
        {
            pstYoungBrother->pstPreBrother  = pstAttribute;
        }

        pstNode->pstFirstAttrib             = pstAttribute;

        return OAM_XML_RESULT_SUCCEED;
    }

    /* ����ʱ����pstAttribute������������,ֱ���ҵ�����ָ�������Ե�ǰһ�� */
    pstTmpAttrib = pstNode->pstFirstAttrib; /* �ӵ�һ�����Կ�ʼ */
    while ( (VOS_NULL_PTR != pstTmpAttrib)
         && (pstTmpAttrib->pstNexBrother != pstYoungBrother) )
    {
        pstTmpAttrib = pstTmpAttrib->pstNexBrother;
    }

    /* û���ҵ�ָ���Ĳ���� */
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return OAM_XML_RESULT_FAILED_ATTRIB_NOT_FOUND;
    }

    /* ��pstAttribute����pstTmpAttrib��pstYoungBrother֮�� */
    pstTmpAttrib->pstNexBrother     = pstAttribute;
    pstAttribute->pstPreBrother     = pstTmpAttrib;
    pstAttribute->pstNexBrother     = pstYoungBrother;
    if (VOS_NULL_PTR != pstYoungBrother)
    {
        pstYoungBrother->pstPreBrother = pstAttribute;
    }

    return OAM_XML_RESULT_SUCCEED;
}
VOS_UINT32 OAM_XML_IsSeparator(VOS_CHAR cCharacter)
{
    if ( ('\r' == cCharacter)       /* �ָ��������س�   */
      || ('\n' == cCharacter)       /* �ָ�����������   */
      || ('\t' == cCharacter)       /* �ָ��������Ʊ�� */
      || (' '  == cCharacter) )     /* �ָ��������ո�   */
    {
        return VOS_TRUE;
    }
    return VOS_FALSE;
}


static VOS_UINT32 OAM_XML_IsLetter(VOS_CHAR cCharacter)
{
    /* �ж��ַ��Ƿ���a~z֮�� */
    if ( ('a' <= cCharacter)
      && ('z' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��ַ��Ƿ���A~Z֮�� */
    else if ( ('A' <= cCharacter)
           && ('Z' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    else
    {
        if ('_' == cCharacter)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


static VOS_UINT32 OAM_XML_IsKeySymbol(VOS_CHAR cCharacter)
{
    /* XML��׼Լ���Ĺؼ����Ű���": . - _" */
    if ( (':' == cCharacter)
      || ('.' == cCharacter)
      || ('-' == cCharacter)
      || ('_' == cCharacter) )
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
static VOS_UINT32 OAM_XML_IsPunctuation(VOS_CHAR cCharacter)
{
    /* ����ASCII���, �����ж��Ƿ�Ϊ���±�����
       (�ո�) ! " # $ % & ' ( ) * + , - . / */
    if ( (' ' <= cCharacter)
      && ('/' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��Ƿ�Ϊ���±����� : ; < = > @ */
    else if ( (':' <= cCharacter)
           && ('@' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��Ƿ�Ϊ���±����� [ \ ] ^ _ ` */
    else if ( ('[' <= cCharacter)
           && ('`' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    /* �ж��Ƿ�Ϊ���±����� { | } ~ */
    else if ( ('{' <= cCharacter)
           && ('~' >= cCharacter) )
    {
        return VOS_TRUE;
    }
    else
    {
    }

    return VOS_FALSE;
}
static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlOriginal(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ����<�����״̬ */
    if ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ENTER_LABEL;
    }
    /* ��ǰ�ڵ�ָ��Ϊ��, ��Ϊû�н���ڵ�, ���Ը��ַ� */
    else if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode)
    {
        /* ��ʱ���û�и��ڵ㣬���ַ����ܺ�����Ҫ�����쳣 */
        if ( (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
          && (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode) )
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlOriginal: Unexpect charactor out of Root!");
            return OAM_XML_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
        }
    }
    /* ��ǰ�ڵ��ֵ��Ϊ��, ����Ϊ�ýڵ����ӽڵ�, ��ǰ�ַ����ڽڵ�ֵ */
    else if (VOS_NULL_PTR != pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue)
    {
        /* ��ǰ�ڵ��ֵ����+1 */
        pstXmlCtxInner->pstXMLCurrentNode->ulValueLength++;
    }
    else
    {
    }

    pstXmlCtxInner->pcXMLStrCurChar++;
    return OAM_XML_RESULT_SUCCEED;
}
static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlEnterLabel(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* �������а汾��Ϣ */
    if ('?' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_DECLARATION;
    }
    /* ����ע�� */
    else if ('!' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_COMMENT;
    }
    /* ����β�ڵ��ǩ */
    else if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_SINGLE_ENDS_LABEL;
    }
    /* ����һ���½ڵ� */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_NODE_LABEL_START;
    }

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlDeclaration(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ��ָ���Ƶ�"<?"�� */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* Ŀǰ�޽����汾��Ϣ�������ݲ�������, ֱ������"?>"���� */
    while ('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ( ('?' == *(pstXmlCtxInner->pcXMLStrCurChar++))
          && ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return OAM_XML_RESULT_SUCCEED;
        }
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlDeclaration: The declaration has no end!");
    return OAM_XML_RESULT_FALIED_DECLARATION_NO_END;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlComment(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ��ָ���Ƶ�"<!"�� */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* ��֧��DOCTYPE, ע�ͱ�����"<!--"��ͷ, �����﷨���� */
    if ( ('-' == *(pstXmlCtxInner->pcXMLStrCurChar++))
      && ('-' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
    {
        pstXmlCtxInner->pcXMLStrCurChar++;

        /* ֱ������������"-->"ǰ, �������е��ַ� */
        while (0 != *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            if ( ('-' == *(pstXmlCtxInner->pcXMLStrCurChar++))
              && ('-' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
            {
                pstXmlCtxInner->pcXMLStrCurChar++;
                if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar++))
                {
                    pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
                    return OAM_XML_RESULT_SUCCEED;
                }
                else
                {
                    XML_WARNING_LOG("OAM_XML_ProcXmlComment: The comment has syntax error!");
                    return OAM_XML_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
                }
            }
        }

        XML_WARNING_LOG("OAM_XML_ProcXmlComment: The comment has no end!");
        return OAM_XML_RESULT_FALIED_COMMENT_NO_END;
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlComment: The comment has syntax error!");
    return OAM_XML_RESULT_FALIED_COMMENT_SYNTAX_ERROR;
}
static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlSingleEndLabel(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ��ָ���Ƶ�"</"�� */
    pstXmlCtxInner->pcXMLStrCurChar++;

    /* ��ǩ������ĸ����Ϊ���ֻ������ */
    /* ��֧��˫�ֽڱ����ַ�, ��֧�������ռ�, �����Բ������� */
    if (VOS_TRUE != OAM_XML_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlSingleEndLabel: Illegal label name!");
        return OAM_XML_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* ���ڵ��ұ�ǩ����ֵ */
    pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd = pstXmlCtxInner->pcXMLStrCurChar++;
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == OAM_XML_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == OAM_XML_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength++;
    }

    /* �Ƚ��ұ�ǩ���Ƿ�����ǩ��һ�� */
    if (pstXmlCtxInner->pstXMLCurrentNode->ulLabelEndLength == pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength)
    {
        if (0 != VOS_MemCmp(pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabel,
                            pstXmlCtxInner->pstXMLCurrentNode->pcNodeLabelEnd,
                            pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength))
        {
            return OAM_XML_RESULT_FALIED_LABEL_NAMES_NOT_SAME;
        }
    }
    else
    {
        return OAM_XML_RESULT_FALIED_BAD_END_LABEL;
    }

    /* �ұ�ǩ�����ǩ������֮�������ָ��� */
    /* һֱ������>����������β��ǩ */
    while (0 != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode->pstFather)
            {
                /* ���ڵ�Ľ�β��ǩ, �������ڵ���������� */
                pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_AFTER_ROOT_NODE;
                pstXmlCtxInner->pcXMLStrCurChar++;
                return OAM_XML_RESULT_SUCCEED_ALL_ENDS;
            }
            break;
        }
        else if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlSingleEndLabel: Illegal label!");
            return OAM_XML_RESULT_FALIED_BAD_END_LABEL;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
        }
    }

    /* �սڵ㴦�� */
    if (0 == pstXmlCtxInner->pstXMLCurrentNode->ulValueLength)
    {
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = VOS_NULL_PTR;
    }

    /* ��ǰ�ڵ��˵����ڵ� */
    pstXmlCtxInner->pstXMLCurrentNode   = pstXmlCtxInner->pstXMLCurrentNode->pstFather;
    pstXmlCtxInner->enXMLAnalyseStatus  = OAM_XML_PARSE_ORIGINAL;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlLabelStart(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_STRU                 *pstNewNode;
    OAM_XML_RESULT_ENUM_UINT32         enXmlRslt;

    /* ��ǩ������ĸ����Ϊ���ֻ������ */
    /* ��֧��˫�ֽڱ����ַ�, ��֧�������ռ�, �����Բ������� */
    if (VOS_TRUE != OAM_XML_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlLabelStart: Illegal label name!");
        return OAM_XML_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* ����һ���½ڵ� */
    pstNewNode  = OAM_XML_CreateANode(pstXmlCtxInner->pstXMLCtx);
    if (VOS_NULL_PTR == pstNewNode)
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlLabelStart: Create Node Error!");
        return OAM_XML_RESULT_FALIED_CREATE_NODE_ERROR;
    }

    /* ���ڵ�Ϊ��, ��ζ�ŵ�ǰ�ڵ㼴���ڵ� */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLRootNode)
    {
        pstXmlCtxInner->pstXMLRootNode = pstNewNode;
    }

    /* �����뵽��ǰ�ڵ���ӽڵ�����ĩ�ˣ�������ǰ�ڵ�ָ��ָ������½ڵ� */
    if (VOS_NULL_PTR != pstXmlCtxInner->pstXMLCurrentNode)
    {
        enXmlRslt = OAM_XML_AddAChildNode(pstXmlCtxInner->pstXMLCurrentNode,
                               pstNewNode,
                               VOS_NULL_PTR);
        if (OAM_XML_RESULT_SUCCEED != enXmlRslt)
        {
            XML_WARNING_LOG("OAM_XML_AddAChildNode: Error!");
        }
        /* ��������ӽڵ�, ����սڵ�ֵ */
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue      = VOS_NULL_PTR;
        pstXmlCtxInner->pstXMLCurrentNode->ulValueLength    = 0;
    }
    pstXmlCtxInner->pstXMLCurrentNode = pstNewNode;

    /* ���ڵ�Label��ֵ */
    pstNewNode->pcNodeLabel = pstXmlCtxInner->pcXMLStrCurChar++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == OAM_XML_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == OAM_XML_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstNewNode->ulLabelLength++;
    }

    /* ����/����>���߷ָ���˵��Node�����ֽ����� */
    /* ����/��������β�����ڵ�, �¸��ֽ�һ����> */
    if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_LABEL_END_MUST_RIGHT;
    }
    /* ����>���ǩ���� */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = pstXmlCtxInner->pcXMLStrCurChar + 1;
    }
    /* ��ǩ���ֽ���, �������Խ���״̬ */
    else if (VOS_TRUE == OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_START;
    }
    else
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlLabelStart: Illegal label name!");
        return OAM_XML_RESULT_FALIED_BAD_LABEL_NAME;
    }

    /* ������ֽڷŽ���ǰ�ڵ�ֵ�Ļ������� */
    pstXmlCtxInner->pstXMLCurrentNode->ulLabelLength++;
    pstXmlCtxInner->pcXMLStrCurChar++;
    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlEndMustBeRight(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ������>������Ϊ�����ʽ */
    if ('>' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlEndMustBeRight: Illegal end label!");
        return OAM_XML_RESULT_FALIED_BAD_END_LABEL;
    }

    /* ����Ǹ��ڵ�Ľ�β��ǩ, �����������Խ����� */
    if (VOS_NULL_PTR == pstXmlCtxInner->pstXMLCurrentNode->pstFather)
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_AFTER_ROOT_NODE;
        return OAM_XML_RESULT_SUCCEED_ALL_ENDS;
    }

    /* ��ǰ�ڵ��˵����ڵ� */
    pstXmlCtxInner->pstXMLCurrentNode   = pstXmlCtxInner->pstXMLCurrentNode->pstFather;
    /* ���״̬ */
    pstXmlCtxInner->enXMLAnalyseStatus  = OAM_XML_PARSE_ORIGINAL;

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribStart(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ����Lable�еķָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* ����β�ڵ��ǩ */
    if ('/' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_LABEL_END_MUST_RIGHT;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* ���ǩ����, �ص���ʼ״̬ */
    else if ('>' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ORIGINAL;
        pstXmlCtxInner->pstXMLCurrentNode->pcNodeValue = pstXmlCtxInner->pcXMLStrCurChar + 1;
        pstXmlCtxInner->pcXMLStrCurChar++;
    }
    /* �����ǩ������ */
    else
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_NAME_START;
    }

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribNameStart(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstNewAttrib;

    /* ����������ĸ����Ϊ���ֻ������, ��֧��˫�ֽڱ����ַ� */
    if (VOS_TRUE != OAM_XML_IsLetter(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameStart: Illegal attribute name!");
        return OAM_XML_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    /* ����һ���½ڵ�, �����뵽��ǰ�ڵ����������ĩ�� */
    pstNewAttrib = OAM_XML_CreateAnAttribute(pstXmlCtxInner->pstXMLCtx);
    if (OAM_XML_RESULT_SUCCEED != OAM_XML_AddAnAttribute(pstXmlCtxInner->pstXMLCurrentNode,
                                                           pstNewAttrib,
                                                           VOS_NULL_PTR))
    {
        return OAM_XML_RESULT_FALIED_CREATE_ATTRIB_ERROR;
    }

    /* ����������ֵ */
    pstNewAttrib->pcAttribName = pstXmlCtxInner->pcXMLStrCurChar++;
    pstNewAttrib->ulNameLength++;
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE == OAM_XML_IsPunctuation(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            if (VOS_FALSE == OAM_XML_IsKeySymbol(*(pstXmlCtxInner->pcXMLStrCurChar)))
            {
                break;
            }
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
        pstNewAttrib->ulNameLength++;
    }

    /* ����=���߷ָ���˵�������������� */
    if ('=' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_NAME_END;
    }
    else if (VOS_TRUE == OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_NAME_END;
    }
    else
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameStart: Illegal attribute name!");
        return OAM_XML_RESULT_FALIED_BAD_ATTRIB_NAME;
    }

    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribNameEnd(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ������������, ������ڶ���ָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* ȥ���ָ�����, һ����'=' */
    if ('=' != *(pstXmlCtxInner->pcXMLStrCurChar++))
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameEnd: Lake of equal sign!");
        return OAM_XML_RESULT_FALIED_EXPECT_EQUAL_SIGN;
    }

    /* �Ⱥ�������ֵ֮���������ָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            break;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    /* ȥ���ָ�����, һ���ǵ����Ż�˫���� */
    if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_VALUE_SINGLE;
    }
    else if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_VALUE_DOUBLE;
    }
    else
    {
        XML_WARNING_LOG("OAM_XML_ProcXmlAttribNameEnd: Lake of quotation mark!");
        return OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK;
    }

    pstXmlCtxInner->pcXMLStrCurChar++;
    return OAM_XML_RESULT_SUCCEED;
}


static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribValueSingle(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* ����ǰ�ڵ����һ�����Ե�����ֵ�� */
    pstTmpAttrib = OAM_XML_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return OAM_XML_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* �ȴ������� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('\'' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* ����ֵ����, ���ؿ�ʼ�������Ե�״̬ */
            pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return OAM_XML_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueSingle: Unexpect Char!");
            return OAM_XML_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueSingle: Lake of end quotation mark!");
    return OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK;
}
static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAttribValueDouble(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_NODE_ATTRIBUTE_STRU       *pstTmpAttrib;

    /* ����ǰ�ڵ����һ�����Ե�����ֵ�� */
    pstTmpAttrib = OAM_XML_GetLastAttribute(pstXmlCtxInner->pstXMLCurrentNode);
    if (VOS_NULL_PTR == pstTmpAttrib)
    {
        return OAM_XML_RESULT_FALIED_UNKOWN_ERROR;
    }
    pstTmpAttrib->pcAttribValue = pstXmlCtxInner->pcXMLStrCurChar;

    /* �ȴ�˫���� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if ('"' == *(pstXmlCtxInner->pcXMLStrCurChar))
        {
            /* ����ֵ����, ���ؿ�ʼ�������Ե�״̬ */
            pstXmlCtxInner->enXMLAnalyseStatus = OAM_XML_PARSE_ATTRIB_START;
            pstXmlCtxInner->pcXMLStrCurChar++;
            return OAM_XML_RESULT_SUCCEED;
        }
        else if ( ('<' == *(pstXmlCtxInner->pcXMLStrCurChar))
               || ('>' == *(pstXmlCtxInner->pcXMLStrCurChar)) )
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueDouble: Unexpect Char!");
            return OAM_XML_RESULT_FALIED_CHAR_UNEXPECT;
        }
        else
        {
            pstXmlCtxInner->pcXMLStrCurChar++;
            pstTmpAttrib->ulValueLength++;
        }
    }

    XML_WARNING_LOG("OAM_XML_ProcXmlAttribValueDouble: Lake of end quotation mark!");
    return OAM_XML_RESULT_FALIED_NO_QUOTATION_MARK;
}
static OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ProcXmlAfterRootNode(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    /* ֱ������ĩβ����������ַָ��� */
    while('\0' != *(pstXmlCtxInner->pcXMLStrCurChar))
    {
        if (VOS_TRUE != OAM_XML_IsSeparator(*(pstXmlCtxInner->pcXMLStrCurChar)))
        {
            XML_WARNING_LOG("OAM_XML_ProcXmlAfterRootNode: Unexpect charactor out of Root!");
            return OAM_XML_RESULT_FALIED_ROOT_OUTSIDE_UNEXPECT;
        }
        pstXmlCtxInner->pcXMLStrCurChar++;
    }

    return OAM_XML_RESULT_SUCCEED_ALL_ENDS;
}
OAM_XML_RESULT_ENUM_UINT32 OAM_XML_Analyse(
    OAM_XML_CTX_INNER_STRU            *pstXmlCtxInner)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;
    OAM_XML_ANALYSE_FUNC               afucXmlAnalyseFucs[] =
    {
        OAM_XML_ProcXmlOriginal,
        OAM_XML_ProcXmlEnterLabel,
        OAM_XML_ProcXmlDeclaration,
        OAM_XML_ProcXmlComment,
        OAM_XML_ProcXmlLabelStart,
        OAM_XML_ProcXmlSingleEndLabel,
        OAM_XML_ProcXmlEndMustBeRight,
        OAM_XML_ProcXmlAttribStart,
        OAM_XML_ProcXmlAttribNameStart,
        OAM_XML_ProcXmlAttribNameEnd,
        OAM_XML_ProcXmlAttribValueSingle,
        OAM_XML_ProcXmlAttribValueDouble,
        OAM_XML_ProcXmlAfterRootNode
    };

    /* �жϽ���״̬�ĺϷ��� */
    if (pstXmlCtxInner->enXMLAnalyseStatus >= OAM_XML_RESULT_FALIED_UNKOWN_ERROR)
    {
        XML_WARNING_LOG("OAM_XML_Analyse: Invalid Analyse Status!");
        return OAM_XML_RESULT_FALIED_ANALYSE_STATUS_ERROR;
    }

    /* ͨ����������״̬�������� */
    ulReturnVal = afucXmlAnalyseFucs[pstXmlCtxInner->enXMLAnalyseStatus](pstXmlCtxInner);

    return ulReturnVal;
}


OAM_XML_RESULT_ENUM_UINT32 OAM_XML_InitXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;

    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        XML_WARNING_LOG("OAM_XML_InitXMLCtx: pstXmlCtx is VOS_NULL_PTR!");
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* ��ʼ���ڴ�ռ� */
    /*lint -e534*/
    VOS_MemSet(pstXmlCtx, 0x00, sizeof(OAM_XML_CTX_STRU));
    /*lint +e534*/
    ulReturnVal = OAM_XML_InitMemory(pstXmlCtx);

    return ulReturnVal;
}


OAM_XML_NODE_STRU* OAM_XML_BuildXMLTree(
    VOS_CHAR                           *pcXmlStr,
    OAM_XML_CTX_STRU                  *pstXmlCtx)
{
    OAM_XML_RESULT_ENUM_UINT32         ulReturnVal;
    OAM_XML_CTX_INNER_STRU             stXmlCtxInner;
    VOS_UINT32                          ulStrLen;

    /* �����Ϸ��Լ�� */
    if ((VOS_NULL_PTR == pcXmlStr) || (VOS_NULL_PTR == pstXmlCtx))
    {
        XML_WARNING_LOG("OAM_XML_BuildXMLTree: pcXmlStr or pstXmlCtx is VOS_NULL_PTR!");
        return VOS_NULL_PTR;
    }

    /* �Խ�����XML�����ĳ��Ƚ���Լ�� */
    ulStrLen = VOS_StrLen(pcXmlStr);
    if ( (0 == ulStrLen)
      || (ulStrLen > OAM_XML_MAX_STR_LEN) )
    {
        XML_WARNING_LOG("OAM_XML_BuildXMLTree: pcXmlStr Length Error!");
        return VOS_NULL_PTR;
    }

    /* ��ʼ���ڴ���� */
    ulReturnVal = OAM_XML_InitMemory(pstXmlCtx);
    if (OAM_XML_RESULT_SUCCEED != ulReturnVal)
    {
        return VOS_NULL_PTR;
    }

    stXmlCtxInner.pstXMLCtx             = pstXmlCtx;
    stXmlCtxInner.pstXMLRootNode        = VOS_NULL_PTR;
    stXmlCtxInner.pstXMLCurrentNode     = VOS_NULL_PTR;
    stXmlCtxInner.pcXMLStrCurChar       = pcXmlStr;
    stXmlCtxInner.enXMLAnalyseStatus    = OAM_XML_PARSE_ORIGINAL;

    /* ����XML��ʽ����������ΪXML���ṹ */
    while ('\0' != *(stXmlCtxInner.pcXMLStrCurChar))
    {
        ulReturnVal = OAM_XML_Analyse(&stXmlCtxInner);

        /* ����ʧ��ֱ���ж�ѭ������ */
        if ( (OAM_XML_RESULT_SUCCEED != ulReturnVal)
          && (OAM_XML_RESULT_SUCCEED_ALL_ENDS != ulReturnVal) )
        {
            break;
        }
    }

    /* ����������ɣ�����XML���ṹ���ڵ� */
    if (OAM_XML_RESULT_SUCCEED_ALL_ENDS == ulReturnVal)
    {
        return stXmlCtxInner.pstXMLRootNode;
    }

    /* �����쳣, �ͷ��������з�����ڴ�, ���ؿ�ָ�� */
    XML_WARNING1_LOG("OAM_XML_BuildXMLTree: Xml Analyse Failure, Error Code: ", ulReturnVal);
    (VOS_VOID)OAM_XML_ClearXMLCtx(pstXmlCtx);
    return VOS_NULL_PTR;
}
OAM_XML_RESULT_ENUM_UINT32 OAM_XML_ClearXMLCtx(OAM_XML_CTX_STRU *pstXmlCtx)
{
    /* �����Ϸ��Լ�� */
    if (VOS_NULL_PTR == pstXmlCtx)
    {
        return OAM_XML_RESULT_FALIED_PARA_NULL_POINTER;
    }

    /* �ͷ���������ռ�õ��ڴ� */
    if (VOS_NULL_PTR != pstXmlCtx->pucXMLBuffer)
    {
        /*lint -e534*/
        VOS_MemFree(MAPS_PIH_PID, pstXmlCtx->pucXMLBuffer);
        /*lint +e534*/
    }

    /*lint -e534*/
    VOS_MemSet(pstXmlCtx, 0x00, sizeof(OAM_XML_CTX_STRU));
    /*lint +e534*/
    return OAM_XML_RESULT_SUCCEED;
}

/*****************************************************************************
�� �� ��  : OAM_XML_GetStrContent
��������  : �����ַ����е������ַ�������ȡ���е���ĸ����������
�������  : pcSrc    Դ�ַ�������
            ulSrcLen Դ�ַ�������
�������  : pcDst    Ŀ���ַ�������
            pulDstLenĿ���ַ�������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ
1.��    ��  : 2013��3��28��
  ��    ��  : zhuli
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_VOID OAM_XML_GetStrContent(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32      i;
    VOS_UINT32      ulCharLen = 0;

    for(i=0; i<ulSrcLen; i++)
    {
        if((pcSrc[i] >= 'a')&&(pcSrc[i] <= 'z'))
        {
            pcDst[ulCharLen] = pcSrc[i]- ('a'-'A');
            ulCharLen++;
        }
        else if((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'Z'))
        {
            pcDst[ulCharLen] = pcSrc[i];
            ulCharLen++;
        }
        else if((pcSrc[i] >= '0')&&(pcSrc[i] <= '9'))
        {
            pcDst[ulCharLen] = pcSrc[i];
            ulCharLen++;
        }
        else
        {
        }

    }

    *pulDstLen = ulCharLen;

    return;
}


/*****************************************************************************
�� �� ��  : OAM_XML_FilterStrInvalidChar
��������  : �����ַ����е������ַ�������ȡ���е���ĸ����������(��ĸ���ı����Сд)
�������  : pcSrc    Դ�ַ�������
            ulSrcLen Դ�ַ�������
�������  : pcDst    Ŀ���ַ�������
            pulDstLenĿ���ַ�������
�� �� ֵ  : ��
���ú���  :
��������  :

�޸���ʷ
1.��    ��  : 2013��9��18��
  ��    ��  : zhuli
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_VOID OAM_XML_FilterStrInvalidChar(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_CHAR *pcDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32      i;
    VOS_UINT32      ulCharLen = 0;

    for(i=0; i<ulSrcLen; i++)
    {
        if( ((pcSrc[i] >= 'a')&&(pcSrc[i] <= 'z'))
          || ((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'Z'))
          || ((pcSrc[i] >= '0')&&(pcSrc[i] <= '9')) )
        {
            pcDst[ulCharLen] = pcSrc[i];
            ulCharLen++;
        }
        else
        {
        }

    }

    *pulDstLen = ulCharLen;

    return;
}


/*****************************************************************************
�� �� ��  : OAM_XML_GetIntArray
��������  : �����ַ����е������ַ�������ȡ���е���ĸ����������
�������  : pcSrc    Դ�ַ�������
            ulSrcLen Դ�ַ�������
�������  : pcDst    Ŀ��ASCII������
            pulDstLenĿ��ASCII������
�� �� ֵ  : VOS_ERR VOS_OK
���ú���  :
��������  :

�޸���ʷ
1.��    ��  : 2013��3��28��
  ��    ��  : zhuli
  �޸�����  : �����ɺ���
*****************************************************************************/
VOS_UINT32 OAM_XML_GetIntArray(VOS_CHAR *pcSrc, VOS_UINT32 ulSrcLen, VOS_UINT8 *pucDst, VOS_UINT32 *pulDstLen)
{
    VOS_UINT32      i;
    VOS_UINT32      j = 0;
    VOS_UINT32      ulLen = 0;
    VOS_CHAR        acTemp[2];

    for(i=0; i<ulSrcLen; i++)
    {
        if((pcSrc[i] >= '0')&&(pcSrc[i] <= '9'))            /*ת�������ַ�*/
        {
            acTemp[j] = pcSrc[i] - '0';

            j++;
        }
        else if((pcSrc[i] >= 'a')&&(pcSrc[i+j] <= 'f'))     /*ת��Сд�ַ�*/
        {
            acTemp[j] = (pcSrc[i] - 'a') + 10;              /*�ַ��������ϲ�ֵ�ָ�*/

            j++;
        }
        else if((pcSrc[i] >= 'A')&&(pcSrc[i] <= 'F'))       /*ת����д�ַ�*/
        {
            acTemp[j] = (pcSrc[i] - 'A') + 10;

            j++;
        }
        else if((pcSrc[i] == '\r')||(pcSrc[i] == '\n')||(pcSrc[i] == '\t')||(pcSrc[i] == ' '))    /*���������ַ�*/
        {
            continue;
        }
        else                                                /*����ת�����������ַ�*/
        {
            XML_WARNING1_LOG("OAM_XML_GetIntArray: Get Non Ascii Char ", pcSrc[i]);

            return VOS_ERR;
        }

        if (2 == j)                                         /*�Ѿ��չ������ַ�*/
        {
            pucDst[ulLen] = (VOS_UINT8)(((VOS_UINT8)acTemp[0]<<4)+acTemp[1]);

            ulLen++;

            j = 0;
        }
    }

    if(1 == j)                                              /*ת�����ַ���Ϊ����*/
    {
        XML_WARNING1_LOG("OAM_XML_GetIntArray: The Str Len is Odd ", ulSrcLen);

        return VOS_ERR;
    }

    *pulDstLen = ulLen;

    return VOS_OK;
}


OAM_XML_NODE_ATTRIBUTE_STRU* OAM_XML_SearchAttNodeByName(
                                    OAM_XML_NODE_ATTRIBUTE_STRU *pstFirstAttrNode,
                                    VOS_CHAR                    *pcAttribName)
{
    OAM_XML_NODE_ATTRIBUTE_STRU *pstAttr;
    VOS_CHAR                    *pcNameData;
    VOS_UINT32                  ulStrLen;
    VOS_INT                     lResult;

    if(VOS_NULL_PTR == pstFirstAttrNode)
    {
        XML_WARNING_LOG("OAM_XML_SearchAttributeNoteByName: The pstFirstAttrNode is NULL ");

        return VOS_NULL_PTR;
    }

    pstAttr = pstFirstAttrNode;

    while(VOS_NULL_PTR != pstAttr)
    {
        /*��ǰ�ڵ��������ƻ��߽ڵ�ֵ�����ڣ���������*/
        if ((VOS_NULL_PTR == pstAttr->pcAttribName)
            ||(VOS_NULL_PTR == pstAttr->pcAttribValue)
            ||(0 == pstAttr->ulNameLength)
            ||(0 == pstAttr->ulValueLength))
        {
            pstAttr = pstAttr->pstNexBrother;

            continue;
        }

        pcNameData = (VOS_CHAR *)VOS_MemAlloc(WUEPS_PID_USIM, DYNAMIC_MEM_PT, pstAttr->ulNameLength);

        if(VOS_NULL_PTR == pcNameData)
        {
            XML_WARNING_LOG("OAM_XML_SearchAttributeNoteByName: The VOS_MemAlloc is NULL ");

            return VOS_NULL_PTR;
        }

        /*�ڵ������ַ�����*/
        OAM_XML_GetStrContent(pstAttr->pcAttribName, pstAttr->ulNameLength, pcNameData, &ulStrLen);

/*lint -e418*/
        lResult = VOS_MemCmp(pcAttribName, pcNameData, ulStrLen);
/*lint +e418*/

        /*�ͷŽڵ������ڴ�*/
        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_USIM, pcNameData);
        /*lint +e534*/

        if(VOS_OK == lResult)
        {
            return pstAttr;
        }

        /*ָ����һ�����Խڵ�*/
        pstAttr = pstAttr->pstNexBrother;
    }

    XML_WARNING_LOG("OAM_XML_SearchAttributeNoteByName: Could Not Find Node ");

    return VOS_NULL_PTR;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

