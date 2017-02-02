/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : CnasXsmsDecode.c
  �� �� ��   : ����
  ��    ��   : j00304117
  ��������   : 2014��10��31��
  ��������   : 1X SMS(Short Message Service)����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXsmsDecode.h"
#include "TafXsmsCtx.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_DECODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*��Ҫ���¶���*/

/*��ͬ��TL�� parameter ID ��Ӧ��ͬ�ĺ����ӿ�*/
TAF_XSMS_PARM_DECODE_FUNC_STRU   g_astTLParmDecodeFuncList[] =
{
    { TAF_XSMS_TL_TELESERVICE_ID,       TAF_XSMS_TL_DecodeTeleSrvId        },
    { TAF_XSMS_TL_SERVICR_CATEGORY,     TAF_XSMS_TL_DecodeSrvCategory      },
    { TAF_XSMS_TL_ORIGIN_ADDR,          TAF_XSMS_TL_DecodeAddr             },
    { TAF_XSMS_TL_ORIGIN_SUBADDR,       TAF_XSMS_TL_DecodeSubAddr          },
    { TAF_XSMS_TL_DEST_ADDR,            TAF_XSMS_TL_DecodeAddr             },
    { TAF_XSMS_TL_DEST_SUBADDR,         TAF_XSMS_TL_DecodeSubAddr          },
    { TAF_XSMS_TL_BEARER_REPLY_OPTION,  TAF_XSMS_TL_DecodeBearReplyOption  },
    { TAF_XSMS_TL_CAUSE_CODE,           TAF_XSMS_TL_DecodeCauseCode        },
    { TAF_XSMS_TL_BERAER_DATA,          TAF_XSMS_TL_DecodeBearData         },
};
/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_UnpackByteToBit
 ��������  : ��ָ����VOS_UINT8���͵������е�ȡ��ָ��λ�õ�ָ��bit����
 �������  : pucBuffer         VOS_UINT8���͵�����ָ��
             usBitPos          ��Ҫȡ����BIT�������е�bit ��λ��
             ucBitNum          ��Ҫȡ����bit��
 �������  : *pucValue         ��ȡ����ֵ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   :j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_TL_UnpackByteToBit (
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                          *pucValue,
    VOS_UINT16                          usBitPos,
    VOS_UINT8                           ucBitNum
)
{
    VOS_UINT8                           ucResult;
    VOS_UINT8                           ucBytePos;
    VOS_UINT16                          usPosInByte;
    VOS_INT8                            cShiftSt;
    VOS_UINT8                           ucMask;
    VOS_UINT16                          usTmpResult;

    /* ������ȡ��bit�ڵڼ����ֽڣ��ڼ����ֽڵĵڼ���Bit */
    ucBytePos     = (VOS_UINT8)(usBitPos / TAF_XSMS_BIT_NUMBER_OF_BYTE);
    usPosInByte   = (VOS_UINT16)(usBitPos % TAF_XSMS_BIT_NUMBER_OF_BYTE);
    cShiftSt      = (VOS_INT8)(TAF_XSMS_BIT_NUMBER_OF_BYTE - (usPosInByte + ucBitNum));

    /* ����ȡ�õ������Ƿ�����һ���ֽ����� */
    if (cShiftSt > 0)
    {
        /* ��ȡ��bit��ͬһ���ֽ��� */
        ucMask    = 0xff >> (TAF_XSMS_BIT_NUMBER_OF_BYTE - ucBitNum);
        ucResult  = (VOS_INT8)((pucBuffer[ucBytePos] >> cShiftSt) & ucMask);
    }
    else
    {
        /* ��ȡ��bit�������ֽ��� */
        usTmpResult = (pucBuffer[ucBytePos] << 8) | (pucBuffer[ucBytePos + 1]);
        ucMask      = (VOS_UINT8)(0xff >> (TAF_XSMS_BIT_NUMBER_OF_BYTE - ucBitNum));
        ucResult    = (VOS_UINT8)(usTmpResult >> (8 + cShiftSt));
        ucResult   &= ucMask;
    }

    *pucValue     = ucResult;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_FillCauseCode
 ��������  : �Ѵ�����������д��TL��ṹ���Cause Code�ֶ�
 �������  : enErrorClass       �����Ĵ�������
             enCauseCode        ���������ԭ��
             ucReplySeq         �ظ�ʱ��Ҫ��Reply SEQ
 �������  : pstTLStru          TL��ṹ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ  :
  1.��    ��   : 2014��10��31��
    ��    ��   :j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_TL_FillCauseCode(
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass,
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    VOS_UINT8                           ucReplySeq,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

)
{
    /* �ж�����е�ErrorClass�������Ƿ��д� */
    if (TAF_XSMS_TL_CAUSECODE_NONE == enErrorClass)
    {
        /* û�г�����������Ϊ1 */
        pstTLStru->stCauseCode.ucParameterLen                               = 1;
        pstTLStru->stCauseCode.ucReplySeq                                   = ucReplySeq;
        pstTLStru->stCauseCode.enErrorClass                                 = enErrorClass;
        pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent   = VOS_FALSE;
    }
    else
    {
        /* ������������Ϊ2 */
        if (TAF_XSMS_TL_CAUSECODE_RESERVED != enErrorClass)
        {
            pstTLStru->stCauseCode.ucParameterLen                             = 2;
            pstTLStru->stCauseCode.ucReplySeq                                 = ucReplySeq;
            pstTLStru->stCauseCode.enErrorClass                               = enErrorClass;
            pstTLStru->stCauseCode.enCauseCode                                = enCauseCode;
            pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_FillCauseCodeSeq
 ��������  : ���ڽ���ʱ���ܷ���Bearer Reply Option�ֶε�ReplySEQ��û������ͳ���
             �������֮ǰ��д��ֵ�����Ǵ���ģ���������һ��
 �������  : pstTLStru         TL��ṹ��
 �������  : pstTLStru         TL��ṹ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_TL_FillCauseCodeSeq(
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

)
{

    /* ����н������Bear Reply Option����д��Cause Code�ֶ� */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent)
    {
        pstTLStru->stCauseCode.ucReplySeq = pstTLStru->ucBearReplySeqNum;
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_DecodeTeleSrvId
 ��������  : �ҵ�tpdu �е�Teleservice ID��д��TL��ṹ����
 �������  : pucData        TL������
             pucBytePos     �������������е�λ��
 �������  : pstTLStru      TL��ṹ��
 �� �� ֵ  : VOS_OK -- ����ɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :
 ��    ��  :
                    �ṹ
      -----------------------------------------------
     |       Field       |   Length (bits)          |
     |   PARAMETER_ID    |       8                  |
     |   PARAMETER_LEN   |       8                  |
     |   IDENTIFIER      |       16                 |
      ----------------------------------------------

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   :j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeTeleSrvId(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTeleSrvIdHighByte = 0;
    VOS_UINT16                          usTeleSrvIdLowByte  = 0;
    VOS_UINT16                          usTmp               = 0;

    usTmp = *pucBytePos;

    /* ����������Ѿ����� ��Ҫ���� */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsTelesrvIdPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeTeleSrvId:Parameter Teleservice ID is repeated");

        return VOS_OK;
    }

    /* ������Ȳ��Է��ش��� */
    if (2 != pucData[usTmp + 1])
    {
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru );
        }

        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeTeleSrvId:Parameter length of Teleservice ID is invalid");

        return VOS_ERR;
    }

    /* ���뿪ʼ�ο�Э��C.S0015 �½�3.4.3.1 */

    usTeleSrvIdHighByte = pucData[usTmp + 2];
    usTeleSrvIdHighByte = (VOS_UINT16)(usTeleSrvIdHighByte << 8);
    usTeleSrvIdLowByte  = pucData[usTmp + 3];
    pstTLStru->stMessage.ulTeleserviceID = usTeleSrvIdHighByte + usTeleSrvIdLowByte;

    /* �ò����ֶ���TL��������ռ4��byte�����ֽ�����Ϊ4 */
    *pucBytePos += 4;

    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsTelesrvIdPresent = VOS_TRUE;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeTeleSrvId: Decode successed");

    return VOS_OK;

}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_DecodeSrvCategory
 ��������  : ��tpdu ת�����ڲ�Ӧ�õĴ��������SrvCategory
 �������  : pucData        TL������
             pucBytePos     �������������е�λ��
 �������  : pstTLStru      TL��ṹ��
 �� �� ֵ  : VOS_OK -- ����ɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :
 ��    ��  :
                    �ṹ
      ----------------------------------------------
     |       Field       |   Length (bits)          |
     |   PARAMETER_ID    |       8                  |
     |   PARAMETER_LEN   |       8                  |
     |   IDENTIFIER      |       16                 |
      ----------------------------------------------
 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   :j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeSrvCategory(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usSrvCateHighByte = 0;
    VOS_UINT16                          usSrvCateLowByte  = 0;
    VOS_UINT16                          usTmp             = 0;

    usTmp = *pucBytePos;

    /* ����˲����ظ����֣���Ҫ���� */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIspSrvCategoryPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSrvCategory:Parameter ServiceCategory is repeated");

        return VOS_OK;
    }

    /* ������Ȳ��Է��ش��� */
    if (2 != pucData[usTmp + 1])
    {
        /* ���֮ǰ����Ĺ�����û�з��������� */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            /* ��д cause code �ֶ� */
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeSrvCategory:Parameter length of ServiceCategory is invalid");

        return VOS_ERR;
    }

    /* ���뿪ʼ�ο�Э��C.S0015 �½�3.4.3.2 */
    usSrvCateHighByte = pucData[usTmp + 2];
    usSrvCateHighByte = (VOS_UINT16)(usSrvCateHighByte << 8);
    usSrvCateLowByte  = pucData[usTmp + 3];
    pstTLStru->stMessage.ulServiceCategory = usSrvCateHighByte | usSrvCateLowByte;
    pstTLStru->stMessage.bIsServicePresent = 1;

    /* �ò����ֶ���TL��������ռ4��byte�����ֽ�����Ϊ4 */
    *pucBytePos += 4;

    /* ��λ�ֶδ��ڱ�־λ */
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIspSrvCategoryPresent = VOS_TRUE;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSrvCategory: Decode successed");

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_DecodeAddr
 ��������  : ��tpduת�����ڲ�Ӧ�õĴ�������ݵĵ�ַ��Ϣ
 �������  : pucData        TL������
             pucBytePos     �������������е�λ��
 �������  : pstTLStru      TL��ṹ��
 �� �� ֵ  : VOS_OK -- ����ɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :
 ��    ��  :
                    ��ַ�����Ľṹ
     -------------------------------------------
    |    Field          |   Length (bits)       |
    |    PARAMETER_ID   |       8               |
    |    PARAMETER_LEN  |       8               |
    |    DIGIT_MODE     |       1               |
    |    NUMBER_MODE    |       1               |
    |    NUMBER_TYPE    |     0 or 3            |
    |    NUMBER_PLAN    |     0 or 4            |
    |    NUM_FIELDS     |       8               |
     -------------------------------------------
        NUM_FIELDS occurrences of the following field:
     ------------------------------------------
    |    CHARi          |     4 or 8            |
     ------------------------------------------
        The parameter ends with the following field:
     -------------------------------------------
    |    RESERVED       |     0-7               |
     -------------------------------------------
 �޸���ʷ      :
  1.��    ��   : 2014��11��05��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT32                          i;
    VOS_UINT16                          usBitPos = 0;
    VOS_UINT8                           ucDigitMode;
    VOS_UINT8                           ucAddrLen;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           ucOffset;
    TAF_XSMS_ADDR_STRU                 *pstAddr;

    pstAddr = &pstTLStru->stMessage.stAddr;
    ucOffset = *pucBytePos;

   /* ����������Ѿ����� , �������β��� */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpOrigAddrPresent)
    {
        *pucBytePos += pucData[ucOffset + 1] + 2;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeAddr:Parameter Address is repeated");

        return VOS_OK;
    }

    ucAddrLen = pucData[ucOffset + 1];

    usBitPos  = 2 * TAF_XSMS_BIT_NUMBER_OF_BYTE;

    /* ����digit mode�ֶ� */
    TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enDigitMode, usBitPos, 1);
    usBitPos++;

    /* ����number mode�ֶ� */
    TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enNumberMode, usBitPos, 1);
    usBitPos++;

    /* ����number type��number plan�ֶ� */
    if (TAF_XSMS_DIGIT_MODE_8_BIT == pstAddr->enDigitMode)
    {
        ucDigitMode = 8;

        TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enNumberType, usBitPos, 3);
        usBitPos += 3;

        if(TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK == pstAddr->enNumberMode)
        {
            TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->enNumberPlan, usBitPos, 4);
            usBitPos += 4;
        }
        else
        {
            pstAddr->enNumberPlan = TAF_XSMS_NUMBER_PLAN_UNKNOWN;
        }
    }
    else
    {
        ucDigitMode = 4;
        pstAddr->enNumberType = TAF_XSMS_NUMBER_TYPE_UNKNOWN;
        pstAddr->enNumberPlan = TAF_XSMS_NUMBER_PLAN_UNKNOWN;
    }

    /* ����address numbers�ֶ� */
    TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &ucTmp, usBitPos, 8);
    pstAddr->ulNumberOfDigits = ucTmp;
    usBitPos += 8;

    /* ����address digits�ֶ� */
    for (i = 0; i < pstAddr->ulNumberOfDigits; i++)
    {
        TAF_XSMS_TL_UnpackByteToBit(pucData + ucOffset, &pstAddr->aucDigits[i], usBitPos, ucDigitMode);
        usBitPos += ucDigitMode;
    }

    if (usBitPos > (VOS_UINT32)((ucAddrLen + 2) * TAF_XSMS_BIT_NUMBER_OF_BYTE))
    {
        *pucBytePos = ucOffset + ucAddrLen + 2;
        return VOS_ERR;
    }

    *pucBytePos = ucOffset + ucAddrLen + 2;

    /* ��λ�ֶδ��ڱ�־λ */
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpOrigAddrPresent = VOS_TRUE;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeAddr:Decode successed");

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_DecodeSubAddr
 ��������  : ��TPDU ת�����ڲ�Ӧ�õĴ�������ݵ��ӵ�ַ��Ϣ
 �������  : pucData        TL������
             pucBytePos     �������������е�λ��
 �������  : pstTLStru      TL��ṹ��
 �� �� ֵ  : VOS_OK -- ����ɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :
 ��    ��  :
                    �ӵ�ַ�����Ľṹ
      -----------------------------------------------
     |       Field       |   Length (bits)          |
     |   PARAMETER_ID    |       8                  |
     |   PARAMETER_LEN   |       8                  |
     |   TYPE            |       3                  |
     |   ODD             |       1                  |
     |   NUM_FIELDS      |       8                  |
      -----------------------------------------------
        NUM_FIELDS instances of the following field:
      ----------------------------------------------
     |   CHARi           |       8                  |
      ----------------------------------------------
         The parameter ends with the following field:
      ----------------------------------------------
     |   RESERVED        |       4                  |
      ----------------------------------------------
 �޸���ʷ      :
  1.��    ��   : 2014��11��05��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeSubAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT16                          usTmp;
    VOS_UINT16                          usBitPos;

    usTmp       = 0;
    usBitPos    = 0;
    usTmp       = *pucBytePos;

    /* ����������Ѿ����� , �������β��� */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpOrigSubAddrPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSubAddr:Parameter SubAddress is repeated");

        return VOS_OK;
    }

    /* ������Ȳ��Է��ش��� */
    if ((0 == pucData[usTmp + 1])
        || (TAF_XSMS_MAX_SUBADDRESS_PARAM_LEN < pucData[usTmp + 1]))
    {
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeSubAddr:Parameter length of SubAddress is invalid");

        return VOS_ERR;
    }

    /*����Э�� C.S0015 �½�3.4.3.3 */
    usBitPos        = 2 * TAF_XSMS_BIT_NUMBER_OF_BYTE;
    TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                &pstTLStru->stMessage.stSubAddr.enSubAddrType,
                                usBitPos,  /* Type�ڵ������ֽ�bit7��ʼ��bit5���� */
                                3);

    usBitPos += 3;
    TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                &pstTLStru->stMessage.stSubAddr.ucOdd,
                                usBitPos,      /* Type�ڵ������ֽ�bit4 */
                                1);
    usBitPos += 1;

    TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                &pstTLStru->stMessage.stSubAddr.ucNumberOfDigits,
                                usBitPos,     /* Type�ڵ������ֽ�bit3 */
                                8);
    usBitPos += 8;

    ucIndex = 0;
    while(ucIndex < pstTLStru->stMessage.stSubAddr.ucNumberOfDigits)
    {
        /* �Ѻ����������ȥ */
        TAF_XSMS_TL_UnpackByteToBit(pucData + usTmp,
                                    &pstTLStru->stMessage.stSubAddr.aucDigits[ucIndex++],
                                    usBitPos,
                                    8);
        usBitPos += 8;
    }
    *pucBytePos += pucData[usTmp + 1] + 2;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeSubAddr:Decode successed");

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_DecodeBearReplyOption
 ��������  : ��tpdu ת�����ڲ�Ӧ�õĴ��������BearReplyOption
 �������  : pucData        TL������
             pucBytePos     �������������е�λ��
 �������  : pstTLStru      TL��ṹ��
 �� �� ֵ  : VOS_OK -- ����ɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :
 ��    ��  :
               Bearer Reply Option �ṹ
         ---------------------------------------
        |   Field           |    Length (bits)  |
        |   PARAMETER_ID    |       8           |
        |   PARAMETER_LEN   |       8           |
        |   REPLY_SEQ       |       6           |
        |   RESERVED        |       2           |
         ---------------------------------------

 �޸���ʷ      :
  1.��    ��   : 2014��11��05��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeBearReplyOption(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTmp = 0;

    usTmp = *pucBytePos;

    /* ����������Ѿ����� , �������β��� */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearReplyOption:Parameter Bear Reply Option is repeated");

        return VOS_OK;
    }

    /* ������Ȳ��Է��ش��� */
    if (1 != pucData[usTmp + 1])
    {
        /* ���֮ǰ����Ĺ�����û�з��������� */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        *pucBytePos += pucData[usTmp + 1] + 2;
        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeBearReplyOption:Parameter length of Bear Reply Option is invalid");

        return VOS_ERR;
    }

    pstTLStru->ucBearReplySeqNum = (pucData[usTmp + 2] >> 2) & 0x3f;
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent = 1;
    *pucBytePos += 3;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearReplyOption:Decode Parameter Bear Reply Option successed");

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_DecodeCauseCode
 ��������  : ��TPDU ������ת�����ڲ�Ӧ�õĴ�������ݵ�CauseCode
 �������  : pucData        TL������
             pucBytePos     �������������е�λ��
 �������  : pstTLStru      TL��ṹ��
 �� �� ֵ  : VOS_OK -- ����ɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :
 ��    ��  :
               Cause Code �ṹ
         ---------------------------------------
        |   Field           |    Length (bits)  |
        |   PARAMETER_ID    |       8           |
        |   PARAMETER_LEN   |       8           |
        |   REPLY_SEQ       |       6           |
        |   ERROR_CLASS     |       2           |
        |   CAUSE_CODE      |     0 or 8        |
         ---------------------------------------

 �޸���ʷ      :
  1.��    ��   : 2014��11��05��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeCauseCode(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTmp = 0;

    /* CauseCode�Ѿ����� */
    if ((VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        && (TAF_XSMS_TL_ACK_MSG == pstTLStru->enMessageType))
    {
        /* ���� */
        *pucBytePos += 3;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeCauseCode:Parameter Cause Code is repeated");

        return VOS_ERR;
    }

    usTmp = *pucBytePos;

    /* ������Ȳ��Է��ش��� */
    if ((1 != pucData[usTmp + 1])
        && (2 != pucData[usTmp + 1]))
    {
        /* ���֮ǰ����Ĺ�����û�з��������� */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeCauseCode:Parameter length of Cause Code is invalid");

        return VOS_ERR;

    }

    /* ��дCauseCode�ֶ� */
    pstTLStru->stCauseCode.ucParameterLen   = pucData[usTmp + 1];
    pstTLStru->stCauseCode.ucReplySeq       = (pucData[usTmp + 2] >> 2) & 0x3f;
    pstTLStru->stCauseCode.enErrorClass     = pucData[usTmp + 2] & 0x03;

    /* �Ƿ��д��д�����д */
    if (pstTLStru->stCauseCode.ucParameterLen == 2)
    {
        pstTLStru->stCauseCode.enCauseCode  = pucData[usTmp + 3];
    }

    /*  �����ʵ�ʵ�Bear Data�ˣ��滻�����ܴ����Bear Data */
    TAF_XSMS_TL_FillCauseCodeSeq(pstTLStru);
    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = 1;
    *pucBytePos += pstTLStru->stCauseCode.ucParameterLen + 2;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeCauseCode:Decode Parameter Cause Code successed");

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_TL_DecodeBearData
 ��������  : ��TPDU ������ת�����ڲ�Ӧ�õĴ��������BearData
 �������  : pucData

 �������  : ��
 �� �� ֵ  :Error_type
 ���ú���  :
 ��������  :
 ��    ��  :
                Bearer  Data �ṹ
         ---------------------------------------
        |   Field           |    Length (bits)  |
        |   PARAMETER_ID    |       8           |
        |   PARAMETER_LEN   |       8           |
         ---------------------------------------
         One or more occurrences of the following subparameter record:
         ---------------------------------------
        |   SUBPARAMETER_ID |       8           |
        |   SUBPARAM_LEN    |       8           |
        | Subparameter Data |  8*SUBPARAM_LEN   |
         ---------------------------------------

 �޸���ʷ      :
  1.��    ��   : 2014��11��05��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_TL_DecodeBearData(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
)
{
    VOS_UINT16                          usTmp             = 0;

    usTmp = *pucBytePos;

    /* ����������Ѿ����� , �������β��� */
    if (VOS_TRUE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearDataPresent)
    {
        *pucBytePos += pucData[usTmp + 1] + 2;

        TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearData:Parameter Bear Data is repeated");

        return VOS_OK;
    }

    /* �жϲ��������Ƿ���ȷ */
    if (0 == pucData[usTmp + 1])
    {
        /* ���֮ǰ����Ĺ�����û�з��������� */
        if (VOS_FALSE == pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
        {
            TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                      TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                      pstTLStru->ucBearReplySeqNum,
                                      pstTLStru);
        }

        TAF_XSMS_ERROR_LOG("TAF_XSMS_TL_DecodeBearData:Parameter length of Bear Data is invalid");

        return VOS_ERR;

    }

    /* ����Bearer Data���ݵ��ṹ���� */
    PS_MEM_CPY(pstTLStru->stMessage.aucBearerData, pucData + usTmp + 2, pucData[usTmp + 1]);

    pstTLStru->stMessage.ulBearerDataLen = pucData[usTmp + 1];

    pstTLStru->unPresentFlag.stTLBitPresentFlag.bIsOpBearDataPresent = 1;
    *pucBytePos += pucData[usTmp + 1] + 2;

    TAF_XSMS_INFO_LOG("TAF_XSMS_TL_DecodeBearData:Decode Parameter Bear Data successed");

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_DecodeTLRawToTLStru
 ��������  : Transport Layer����ת����TL��ṹ�壬�����PRL���ţ�����Bear Data����
             ����λ��
 �������  : ucTLRawLen           TL����������
            *pucTLRaw             TL������
 �������  : *pstTLMsg             TL��ṹ��
 �� �� ֵ  : VOS_OK -- ����ɹ�
             VOS_ERR -- ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_DecodeTLRawToTLStru(
    VOS_UINT8                           ucTLRawLen,
    VOS_UINT8                          *pucTLRaw,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg
)
{
    VOS_UINT8                          *pucBuffer;
    VOS_UINT8                           ucBytePos;
    VOS_UINT8                           ucErrCnt;
    VOS_UINT8                           i;
    VOS_UINT32                          ulResult;

    ucErrCnt    = 0;
    ucBytePos   = 1;
    pucBuffer   = pucTLRaw;


    /* ��������ڱ�־λ */
    pstTLMsg->unPresentFlag.ausValue[0] = 0;

    /* ��ȡ��Ϣ���� */
    pstTLMsg->enMessageType = pucBuffer[0];

    /* ��Ϣ���Ͳ���ȷ������ʧ�� */
    if (pstTLMsg->enMessageType >= TAF_XSMS_TL_MSG_TYPE_BUTT)
    {
        pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
        TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                  TAF_XSMS_TL_UNRECOGNIZED_PARM_VALUE,
                                  pstTLMsg->ucBearReplySeqNum,
                                  pstTLMsg);

        TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeTLRawToTLStru:Unsupported message type");

        return VOS_ERR;
    }

    /* ���������ﲻͬ��Parameter ID���벻ͬ�Ĵ������ */
    while (ucBytePos < ucTLRawLen)
    {
        for (i = 0; i < TAF_XSMS_TL_PARAMETER_MAX; i++)
        {
            if (pucBuffer[ucBytePos] == g_astTLParmDecodeFuncList[i].enParaId)
            {
                /* �жϽ�������Ƿ���� */
                if (VOS_OK != g_astTLParmDecodeFuncList[i].pstParaDecodeFunc(pucBuffer, &ucBytePos, pstTLMsg))
                {
                    ucErrCnt++;
                }
                break;
            }
        }

        if (TAF_XSMS_TL_PARAMETER_MAX == i)
        {
            ucBytePos += pucBuffer[ucBytePos + 1] + 2;
        }
    }

    /* �жϽ�������������Ƿ����õ�����֪���������ȣ�������ǣ����ؽ������ */
    if (ucBytePos != ucTLRawLen)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeTLRawToTLStru:Decode failed");

        return VOS_ERR;
    }

    /* �жϳ��Ѿ����� */
    if (0 != ucErrCnt)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeTLRawToTLStru:Decode failed");

        return VOS_ERR;
    }

    ulResult = TAF_XSMS_CheckFields(pstTLMsg);

    return ulResult;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_CheckFields
 ��������  : �жϱ�Ҫ�����Ƿ�ȱʧ
 �������  : pstTLMsg:TL��ṹ��
 �������  : ��
 �� �� ֵ  : VOS_ERR:ȱʧ��Ҫ���������ش���
             VOS_OK:��ȱʧ��Ҫ������������ȷ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��05��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_XSMS_CheckFields(TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg)
{
    /* ����Э�����Ҫ�����Ƿ�ȱʧ��ȱʧ�����ʧ�� */
    switch(pstTLMsg->enMessageType)
    {
        case TAF_XSMS_TL_P2P_MSG:

            /* �ж����ȱ��Teleservice ID���� */
            if ((VOS_FALSE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsTelesrvIdPresent)
                || (VOS_FALSE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpOrigAddrPresent))
            {
                /* ֮ǰ����Ĺ�����û�з��������� */
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
                TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                          TAF_XSMS_TL_MISSING_MANDATORY_PARM,
                                          pstTLMsg->ucBearReplySeqNum,
                                          pstTLMsg);

                TAF_XSMS_ERROR_LOG("TAF_XSMS_CheckFields:Point to point message missing mandatory paramter");

                return VOS_ERR;

            }
            else
            {
                /* ����ɹ����ж��Ƿ�ΪPRL���ţ������PRL������Bear Data����˳�� */
                TAF_XSMS_IsPRL(pstTLMsg);

            }
            break;


        case TAF_XSMS_TL_ACK_MSG:
            if (VOS_FALSE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent)
            {
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpCauseCodePresent = VOS_TRUE;
                TAF_XSMS_TL_FillCauseCode(TAF_XSMS_TL_CAUSECODE_TMP,
                                          TAF_XSMS_TL_MISSING_MANDATORY_PARM,
                                          pstTLMsg->ucBearReplySeqNum,
                                          pstTLMsg);

                TAF_XSMS_ERROR_LOG("TAF_XSMS_CheckFields:Ack message missing mandatory paramter");

                return VOS_ERR;
            }

            break;

        default:

            TAF_XSMS_ERROR_LOG("TAF_XSMS_CheckFields:Unsopported message type");

            return VOS_ERR;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_FillBDShortStru
 ��������  : ��BearerDate����Ӳ�����д���Զ��ṹ����
 �������  : pucBuffer              Bearer Data������
             pucBytePos             Bearer Data��ĳһ���Ӳ�����ʼλ��
 �������  : pstBDParamStru         ��ʱ�ṹ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��05��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/

VOS_VOID TAF_XSMS_FillBDShortStru(
    VOS_UINT8                                              *pucBuffer,
    VOS_UINT8                                              *pucBytePos,
    TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU                  *pstBDParamStru
)
{
    VOS_UINT8                           ucOffset;

    ucOffset                        = *pucBytePos;
    pstBDParamStru->enParamHeader   = pucBuffer[ucOffset];
    pstBDParamStru->ucLen           = pucBuffer[ucOffset + 1];
    pstBDParamStru->ucBytePos       = *pucBytePos;
    ucOffset                       += (pstBDParamStru->ucLen + 2);
    *pucBytePos                     = ucOffset;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_IsPRL
 ��������  : �ж��Ƿ�ΪPRL���¶��ţ�����ǣ����͵���Bear Data�������Ӳ�����λ��
 �������  : ucBDRawLen            TL����������
             *pstTLMsg             TL��ṹ��
 �������  : *pstTLMsg             TL��ṹ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XSMS_IsPRL(TAF_XSMS_TRANSPORT_MESSAGE_STRU *pstTLMsg)
{
    VOS_UINT32                                              ulPresentFlag;
    VOS_UINT8                                               ucBDRaw[MAX_BD_BYTE_LENGTH];
    VOS_UINT8                                               ucBytePos;
    VOS_UINT8                                               ucIndex;
    TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU                   astBDParamShort[20];
    TAF_XSMS_BD_MSG_DISPLAY_MODE_STRU                       stBDDisplayMode;

    ucBytePos           = 0;
    ucIndex             = 0;
    ulPresentFlag       = 0;
    PS_MEM_SET(astBDParamShort, 0, 20 * sizeof(TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU));

    /* �������� */
    PS_MEM_CPY(ucBDRaw, pstTLMsg->stMessage.aucBearerData, pstTLMsg->stMessage.ulBearerDataLen);

    /* ����Bearer Data���Ӳ������벻ͬ�Ĵ������ */
    while (ucBytePos < pstTLMsg->stMessage.ulBearerDataLen)
    {
        /* �ж��Ƿ�ΪDisplay Mode�ֶ� */
        if (TAF_XSMS_BD_MESSAGE_DISPLAY_MODE == ucBDRaw[ucBytePos])
        {
            stBDDisplayMode.enParamHeader           = TAF_XSMS_BD_MESSAGE_DISPLAY_MODE;
            stBDDisplayMode.ucLen                   = ucBDRaw[ucBytePos + 1];
            stBDDisplayMode.ucMsgDisplayMode        = ucBDRaw[ucBytePos + 2] >> 6;
            stBDDisplayMode.ucMsgReserverd          = ucBDRaw[ucBytePos + 2] & 0x3f;

            /* �ж��Ƿ�ΪPRL���¶��� */
            if ((0x03 == stBDDisplayMode.ucMsgDisplayMode)
                && (0x10 == stBDDisplayMode.ucMsgReserverd))
            {
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpIsPRL = VOS_TRUE;
            }
            /* �ж��Ƿ�ΪPP DOWNLOAD���¶��� */
            if ((0x03 == stBDDisplayMode.ucMsgDisplayMode)
             && (0x20 == stBDDisplayMode.ucMsgReserverd))
            {
                pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpIsPPDownload = VOS_TRUE;
            }
        }

        /* �ж��Ƿ�����Ƿ񲻺Ϸ� */
        if (ucBDRaw[ucBytePos] > TAF_XSMS_BD_MESSAGE_STATUS)
        {
            ucBytePos += (ucBDRaw[ucBytePos + 1] + 2);
            continue;
        }

        ulPresentFlag |= (1 << ucBDRaw[ucBytePos]);
        TAF_XSMS_FillBDShortStru(ucBDRaw, &ucBytePos, &astBDParamShort[ucBDRaw[ucBytePos]]);


    }

    if (VOS_TRUE == pstTLMsg->unPresentFlag.stTLBitPresentFlag.bIsOpIsPRL)
    {
        /* ����BD�������λ�� */
        ucBytePos = 0;

        /* дMessage�ֶ� */
        PS_MEM_CPY(pstTLMsg->stMessage.aucBearerData,
                   ucBDRaw+astBDParamShort[TAF_XSMS_BD_MESSAGE_IDENTIFIER].ucBytePos,
                   astBDParamShort[TAF_XSMS_BD_MESSAGE_IDENTIFIER].ucLen + 2);
        ucBytePos += astBDParamShort[TAF_XSMS_BD_MESSAGE_IDENTIFIER].ucLen + 2;

        /* дDisplay Mode�ֶ� */
        PS_MEM_CPY(pstTLMsg->stMessage.aucBearerData+ucBytePos,
                   ucBDRaw+astBDParamShort[TAF_XSMS_BD_MESSAGE_DISPLAY_MODE].ucBytePos,
                   astBDParamShort[TAF_XSMS_BD_MESSAGE_DISPLAY_MODE].ucLen + 2);
        ucBytePos += astBDParamShort[TAF_XSMS_BD_MESSAGE_DISPLAY_MODE].ucLen + 2;

        for (ucIndex = 1;ucIndex<20;ucIndex++)
        {
            /* ����Display Mode�ֶ� */
            if (TAF_XSMS_BD_MESSAGE_DISPLAY_MODE == ucIndex)
            {
                continue;
            }

            if ((ulPresentFlag & (1 << ucIndex)) == (1 << ucIndex))
            {
                PS_MEM_CPY(pstTLMsg->stMessage.aucBearerData + ucBytePos,
                           ucBDRaw+astBDParamShort[ucIndex].ucBytePos,
                           astBDParamShort[ucIndex].ucLen + 2);
                ucBytePos += astBDParamShort[ucIndex].ucLen + 2;
                continue;
            }
        }
    }

    return;
}


VOS_VOID TAF_XSMS_DecodeUserDataInBearerData(
    VOS_UINT32                          ulBearDataLen,  /* in */
    VOS_UINT8                          *pucBearerData,  /* in */
    VOS_UINT16                         *pusUserDataStartByte,   /* out */
    VOS_UINT16                         *pusUserDataLen, /* out ��BearerData�еĳ��ȣ���������ʵ�ʳ��� */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData     /* out */
)
{
    VOS_UINT16                          usBytePos = 0;
    VOS_UINT16                          usParaLen = 0;
    VOS_UINT32                          ulBitPos  = 0;
    VOS_UINT32                          ulIndex   = 0;
    VOS_UINT32                          ulRet     = 0;
    VOS_UINT8                           ucBitsNumOfChari = 0;

    *pusUserDataLen = 0;

    /* ����Bearer Data���Ӳ������벻ͬ�Ĵ������ */
    while (usBytePos < ulBearDataLen)
    {
        usParaLen   =  pucBearerData[usBytePos + 1];
        ulBitPos    =  8 * (usBytePos + 2);

        if (TAF_XSMS_BD_USER_DATA == pucBearerData[usBytePos])
        {
            /* PARA ID      8BITS
               PARA LEN     8BITS
               MSG_ENCODING 5BITS
               MSG_TYPE     0 OR 8BITS
               NUM_FIELD    8 BITS */

            *pusUserDataStartByte = usBytePos;
            *pusUserDataLen       = pucBearerData[usBytePos + 1] + 2;

            pstUserData->enMsgCodeType = (pucBearerData[usBytePos + 2] & 0xF8) >> 3 ;

            ulBitPos += 5;

            if (TAF_XSMS_USER_DATA_MSG_ENCODE_EPM == pstUserData->enMsgCodeType)
            {
                TAF_XSMS_TL_UnpackByteToBit(pucBearerData,
                                            &pstUserData->ucMsgType,
                                            (VOS_UINT16)ulBitPos,
                                            8);
                ulBitPos  += 8;
            }

            TAF_XSMS_TL_UnpackByteToBit(pucBearerData,
                                        &pstUserData->ucNumFields,
                                        (VOS_UINT16)ulBitPos,
                                        8);
            ulBitPos  += 8;

            /* ���ݱ����ʽ���õ�ÿ�����ݵ�bit���� 7,8 ����16bit */
            ulRet = TAF_XSMS_GetUserDataCodeBitsByMsgCode(pstUserData->enMsgCodeType,
                                                          &ucBitsNumOfChari);

            ucBitsNumOfChari = 8;

            /* Ĭ��ȫ��8BITS */
            if (VOS_OK == ulRet)
            {
                /* ��USER DATA�� data�ֶ� NUM_FIELDS��ʱ�򲻷������� */
                for (ulIndex = 0;
                      (((ulBitPos < (usBytePos + usParaLen + 2) * 8)) && (TAF_XSMS_BD_USER_DATA_MAX_LEN > ulIndex));
                       ulIndex++)
                {

                    TAF_XSMS_TL_UnpackByteToBit(pucBearerData,
                                                &pstUserData->aucUserData[ulIndex],
                                                (VOS_UINT16)(ulBitPos),
                                                ucBitsNumOfChari);
                    ulBitPos  += ucBitsNumOfChari;

                }

            }

            /* Ҫ��Ҫ�˳�ѭ��  */
            break;
        }

        /* �ж��Ƿ�����Ƿ񲻺Ϸ� */
        if (pucBearerData[usBytePos] > TAF_XSMS_BD_MESSAGE_STATUS)
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_DecodeUserDataInBearerData : ERROR PARA ID");
        }

        usBytePos += (usParaLen + 2);
        ulBitPos   = 0;
    }

    return;

}
VOS_UINT32 TAF_XSMS_GetUserDataCodeBitsByMsgCode(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT8                          *pucBitNum
)
{
    switch (enMsgCodeType)
    {
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_ASCII_7:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_IA5:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_GSM_7:
            *pucBitNum = 7;
            return VOS_OK;

        case    TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_HEBREW:
        case    TAF_XSMS_USER_DATA_MSG_ENCODE_LATIN:
            *pucBitNum = 8;
            return VOS_OK;

        case    TAF_XSMS_USER_DATA_MSG_ENCODE_UNICODE:
            *pucBitNum = 16;
            return VOS_OK;

        default:
            /* �������뷽ʽ�й����Ų�֧�� */
            TAF_XSMS_ERROR_LOG("TAF_XSMS_GetUserDataCodeBitsByMsgCode : MSG_CODE NOT RIGHT");
            *pucBitNum = 0;
            return VOS_ERR;

    }

}
VOS_VOID TAF_XSMS_PressUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData
)
{
    VOS_UINT32                          ulIndex     = 0;
    VOS_UINT8                           aucUserData[256] = {0};
    VOS_UINT8                           ucNumOfFields = 0;
    VOS_UINT8                           ucOffset = 0;
    VOS_UINT8                           ucIndexInOldUserData = 0;
    VOS_UINT8                           ucNumOfLowBits = 0;

    //pstUserData->enMsgCodeType = TAF_XSMS_USER_DATA_MSG_ENCODE_ASCII_7; /* ��Ҫȷ�� */
    ucNumOfFields    =  (VOS_UINT8)VOS_StrLen((VOS_CHAR*)pstUserData->aucUserData);

    if ((pstUserData->ucNumFields > ucNumOfFields)
     || (0 == pstUserData->ucNumFields))
    {
        pstUserData->ucNumFields = ucNumOfFields;
    }

    for (ulIndex = 0; ulIndex <  (pstUserData->ucNumFields / 8 * 7 + pstUserData->ucNumFields % 8); ulIndex++)
    {
       ucOffset = ulIndex % 7 + 1;
       /* ��һ��byte �� �ڶ���byte  ���һλ + ��һ��byte�� ��� 7λ
          �ڶ���byte �� ������byte  ���2λ + ��2��byte��   ��� 6λ
       */

       ucIndexInOldUserData = (VOS_UINT8)((ulIndex / 7) * 8 + ulIndex % 7);

       if (ucIndexInOldUserData + 1 >= ucNumOfFields)
       {
            break;
       }

       ucNumOfLowBits       = TAF_XSMS_GetLowBits(8 - ucOffset);

       aucUserData[ulIndex] = (pstUserData->aucUserData[ucIndexInOldUserData] & ucNumOfLowBits)
                               + (VOS_UINT8)(pstUserData->aucUserData[ucIndexInOldUserData + 1] << (8 - ucOffset));

       pstUserData->aucUserData[ucIndexInOldUserData + 1] = pstUserData->aucUserData[ucIndexInOldUserData + 1] >> ucOffset;
    }

    PS_MEM_CPY(pstUserData->aucUserData, aucUserData, 256);

    return;
}

VOS_UINT8 TAF_XSMS_GetLowBits(VOS_UINT8 ucOffset)
{
    VOS_UINT8               ucOutPut = 0;
    VOS_UINT8               ucIndex  = 0;

    if (8  < ucOffset)
    {
        return 0;
    }

    for (ucIndex = 1; ucIndex <= ucOffset; ucIndex++)
    {
        ucOutPut += (VOS_UINT8)(0x01 << (ucIndex - 1));
    }

    return ucOutPut;

}

VOS_VOID TAF_XSMS_EncodeUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,    /* in */
    VOS_UINT8                          *pucUserDataLen, /* out */
    VOS_UINT8                          *paucUserData    /* out */
)
{
    VOS_UINT8                           ucIndex     = 0;
    VOS_UINT16                          usBitpos    = 0;
    VOS_UINT8                           ucBitNumInChar = 0;

    /* PARA ID      8BITS
    PARA LEN     8BITS
    MSG_ENCODING 5BITS
    MSG_TYPE     0 OR 8BITS
    NUM_FIELD    8 BITS */
    TAF_XSMS_PackBitToByte(paucUserData,
                           TAF_XSMS_BD_USER_DATA,
                           8,
                           (VOS_UINT16)usBitpos);

    usBitpos += 8;

    /* PARA LEN �Ȳ���д */
    usBitpos += 8;

    /* MSG_CODE */
    TAF_XSMS_PackBitToByte(paucUserData,
                           pstUserData->enMsgCodeType,
                           5,
                           (VOS_UINT16)usBitpos);

    usBitpos += 5;

    /* MSG_TYPE */
    if (TAF_XSMS_USER_DATA_MSG_ENCODE_EPM == pstUserData->enMsgCodeType)
    {
        TAF_XSMS_PackBitToByte(paucUserData,
                       pstUserData->ucMsgType,
                       8,
                       (VOS_UINT16)usBitpos);

        usBitpos += 8;
    }

    /* NUM FIELDS  */
    TAF_XSMS_PackBitToByte(paucUserData,
                           pstUserData->ucNumFields,
                           8,
                           (VOS_UINT16)usBitpos);

    usBitpos += 8;

    if (VOS_OK != TAF_XSMS_GetUserDataCodeBitsByMsgCode(pstUserData->enMsgCodeType,
                                                        &ucBitNumInChar))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeUserData: unkown msg_code ");
        return;
    }
    /* CHAR I */
    if (16 == ucBitNumInChar)
    {
        for (ucIndex = 0; ucIndex < pstUserData->ucNumFields; ucIndex++)
        {
            TAF_XSMS_PackBitToByte(paucUserData,
                                   pstUserData->aucUserData[2 * ucIndex],
                                   8,
                                   (VOS_UINT16)usBitpos);
            usBitpos += 8;

            TAF_XSMS_PackBitToByte(paucUserData,
                                   pstUserData->aucUserData[2 * ucIndex + 1],
                                   8,
                                   (VOS_UINT16)usBitpos);
            usBitpos += 8;


        }
    }
    else
    {
        for (ucIndex = 0; (ucIndex < (pstUserData->ucNumFields * ucBitNumInChar + 7) / 8) && (ucIndex < 255) ; ucIndex++)
        {

            TAF_XSMS_PackBitToByte(paucUserData,
                                   pstUserData->aucUserData[ucIndex],
                                   8,
                                   (VOS_UINT16)usBitpos);
            usBitpos += 8;
        }

    }

    *pucUserDataLen = (VOS_UINT8)((usBitpos + 7) / 8);

    /* PARA LEN = �ܳ��� - (PARA ID + PARA LEN ռ�õ��ֽ�) */
    paucUserData[1] = *pucUserDataLen - 2;

    return;
}



VOS_VOID TAF_XSMS_ReplaceUserData(
    TAF_XSMS_MESSAGE_STRU              *pstMessage,
    VOS_UINT8                          *paucPressedUserData,
    VOS_UINT32                          ulPressedUserDataLen,
    VOS_UINT16                          usOldUserDataStartByte,
    VOS_UINT16                          usOldUserDataLen
)
{
    if (usOldUserDataLen < ulPressedUserDataLen)
    {
        return;
    }

    PS_MEM_CPY(pstMessage->aucBearerData + usOldUserDataStartByte,
               paucPressedUserData,
               ulPressedUserDataLen);

    PS_MEM_SET(pstMessage->aucBearerData + usOldUserDataStartByte + ulPressedUserDataLen,
               0,
               usOldUserDataLen - ulPressedUserDataLen);

    if (usOldUserDataStartByte + usOldUserDataLen < pstMessage->ulBearerDataLen)
    {

        VOS_MemMove(pstMessage->aucBearerData   + usOldUserDataStartByte    + ulPressedUserDataLen,/* ��ǰUSER DATA �Ľ�β */
                    pstMessage->aucBearerData   + usOldUserDataStartByte    + usOldUserDataStartByte,/* ԭ��USER DATA �Ľ�β */
                    pstMessage->ulBearerDataLen - (usOldUserDataStartByte   + usOldUserDataLen));/* USER DATA֮������ݳ��� */
    }

    pstMessage->ulBearerDataLen = pstMessage->ulBearerDataLen - (usOldUserDataLen - ulPressedUserDataLen);

    return;
}
VOS_VOID TAF_XSMS_DevideLongCdmaSms(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,         /* USER DATA */
    VOS_UINT16                          usUserDataStartByte, /* in ��ԭ����BEARER DATA �п�ʼλ�� */
    VOS_UINT16                          usUserDataLen,       /* in ��ԭ����BEARER DATA �г���*/
    TAF_XSMS_MESSAGE_STRU              *pstFirstMessage,     /* ��һ����Ϣ*/
    TAF_XSMS_MESSAGE_STRU              *pstSecondMessage    /* �ڶ�����Ϣ */
)
{
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stSecondUserData;
    VOS_UINT8                           ucFirstUserDataLenInBearData    = 0;
    VOS_UINT8                           ucSecondUserDataLenInBearData   = 0;
    VOS_UINT8                           aucFirstUserData[200]   = {0};
    VOS_UINT8                           aucSecondUserData[200]  = {0};

    /* USER DATA ��ֳ����� */
    TAF_XSMS_DevideUserData(pstUserData,
                            &stSecondUserData);
    /* ENCODE USER DATA */
    TAF_XSMS_EncodeUserData(pstUserData,
                            &ucFirstUserDataLenInBearData,
                            aucFirstUserData);

    TAF_XSMS_EncodeUserData(&stSecondUserData,
                            &ucSecondUserDataLenInBearData,
                            aucSecondUserData);

    /* REPLACEÿһ����USER DATA �ֶ� (��Ҫȷ���Ƿ���Ҫ����1/2 2/2���ֶ��Ŵ���) */

    TAF_XSMS_ReplaceUserData(pstFirstMessage,
                             aucFirstUserData,
                             ucFirstUserDataLenInBearData,
                             usUserDataStartByte,
                             usUserDataLen);

    TAF_XSMS_ReplaceUserData(pstSecondMessage,
                             aucSecondUserData,
                             ucSecondUserDataLenInBearData,
                             usUserDataStartByte,
                             usUserDataLen);

}


VOS_VOID TAF_XSMS_DevideUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstFirstUserData,         /* USER DATA in and out */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstSecondUserData        /* USER DATA out*/
)
{
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stFirstUserData;
    VOS_UINT16                          usLenLimit      = 0;
    VOS_UINT8                           ucBitsInChari   = 0;

    PS_MEM_CPY(&stFirstUserData,    pstFirstUserData, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));
    PS_MEM_CPY(pstSecondUserData,   pstFirstUserData, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    /* ȷ�ϱ����ʽ ȷ�Ϸְ����� */
    TAF_XSMS_GetXsmsLimitLen(pstFirstUserData->enMsgCodeType,
                             &usLenLimit);

    if (0 == usLenLimit)
    {
        return;
    }

    if (VOS_ERR == TAF_XSMS_GetUserDataCodeBitsByMsgCode(pstFirstUserData->enMsgCodeType,
                                                      &ucBitsInChari))
    {
        return;
    }

    if (usLenLimit >= pstFirstUserData->ucNumFields)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_DevideUserData:ucNumFields < limit");
        return;
    }

    stFirstUserData.ucNumFields = (VOS_UINT8)usLenLimit;

    /* ��һ��BIT ���� 160 * 7 */
    PS_MEM_CPY(stFirstUserData.aucUserData,
               pstFirstUserData->aucUserData,
               140);

    pstSecondUserData->ucNumFields = pstFirstUserData->ucNumFields - (VOS_UINT8)usLenLimit;

    /* �ڶ���BIT ���� ��BIT - 160 * 7 */
    PS_MEM_CPY(pstSecondUserData->aucUserData,
               &pstFirstUserData->aucUserData[140],
               ((pstFirstUserData->ucNumFields - usLenLimit) * ucBitsInChari + 7) / 8);


    PS_MEM_CPY(pstFirstUserData, &stFirstUserData, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    return;

}
VOS_VOID TAF_XSMS_GetXsmsLimitLen(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT16                         *pusLenLimit
)
{
    VOS_UINT8                           ucBitNumInChari = 0;

    if (VOS_ERR == TAF_XSMS_GetUserDataCodeBitsByMsgCode(
                                        enMsgCodeType,
                                        &ucBitNumInChari))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetXsmsLimitLen : Wrong enMsgCodeType");
        return;
    }

    if (8 == ucBitNumInChari)
    {
        *pusLenLimit    = 140;
    }
    else if (16 == ucBitNumInChari)
    {
        *pusLenLimit    = 70;
    }
    else
    {
        *pusLenLimit    = 160;
    }

    return;

}


VOS_VOID TAF_XSMS_EncodeMsgID(
    TAF_XSMS_MSG_ID_STRU               *pstMsgId,           /* in */
    VOS_UINT8                          *pucMsgIdLen,        /* out */
    VOS_UINT8                          *paucMsfIdData       /* out */
)
{
    VOS_UINT8                           ucBitPos = 0;

    *pucMsgIdLen        = 5;

    paucMsfIdData[0]    = TAF_XSMS_BD_MESSAGE_IDENTIFIER;
    ucBitPos           += 8;

    paucMsfIdData[1]    = 3;
    ucBitPos           += 8;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           pstMsgId->enMsgType,
                           4,
                           ucBitPos);

    ucBitPos           += 4;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           pstMsgId->usMsgID & 0x00FF,
                           8,
                           ucBitPos);
    ucBitPos           += 8;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           (pstMsgId->usMsgID & 0xFF00)>>8,
                           8,
                           ucBitPos);
    ucBitPos           += 8;

    TAF_XSMS_PackBitToByte(paucMsfIdData,
                           pstMsgId->ucIsHeadIndExist,
                           1,
                           ucBitPos);
    ucBitPos           += 1;

    return;
}
VOS_VOID TAF_XSMS_EncodeUserRspCode(
    VOS_UINT8                           ucUserResponseCode, /* in */
    VOS_UINT8                          *pucRepCodeLen,      /* out */
    VOS_UINT8                          *pucRepCodeData      /* out */
)
{
    *pucRepCodeLen = 3;

    pucRepCodeData[0]   = TAF_XSMS_BD_USER_RESPONESE_CODE;
    pucRepCodeData[1]   = 1;
    pucRepCodeData[2]   = ucUserResponseCode;

    return;
}
VOS_VOID TAF_XSMS_DecodeMsgId(
    VOS_UINT32                          ulBearDataLen,
    VOS_UINT8                          *pucBearData,
    TAF_XSMS_MSG_ID_STRU               *pstMsgId
)
{
    /*
    para_id     8 bits
    para_len    8 bits
    msg_type    4 bits
    msg_id      16bits
    header_ind  1 bits
    rsv         3 bits
    */

    pstMsgId->enMsgType         = (TAF_XSMS_BD_MSG_TYPE_ENUM8)((pucBearData[2] & 0xf0) >> 4);
    pstMsgId->ucIsHeadIndExist  = VOS_FALSE;
    pstMsgId->usMsgID           = 0;
    pstMsgId->usMsgID          += ((pucBearData[2] & 0x0f) << 12);
    pstMsgId->usMsgID          += ( pucBearData[3]  << 4);
    pstMsgId->usMsgID          += ((pucBearData[4] & 0xf0) >> 4);

    return;
}



/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




