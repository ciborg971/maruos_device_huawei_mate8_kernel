/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsEncode.c
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
#include  "TafXsmsEncode.h"
#include  "TafAppXsmsInterface.h"
#include  "TafXsmsCtx.h"
#include  "TafXsmsUimProc.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_ENCODE_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : TAF_XSMS_PackBitToByte
 ��������  : ������8��bit��ֵд��ָ�������ָ��bitλ����ȥ
 �������  : ucValue:      ��Ҫд���ֵ
             ucBitNum:     ��Ҫд���bit����1-8bit
             usBitPos:     д��bit���������е�λ��
 �������  : pucBuffer:    ��Ҫд�������ĵ�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

***************************************************************6**************/
VOS_VOID TAF_XSMS_PackBitToByte(
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                           ucValue,
    VOS_UINT8                           ucBitNum,
    VOS_UINT16                          usBitPos
)
{
    VOS_UINT16                          usTmpPos;
    VOS_UINT16                          usBits;
    VOS_UINT16                          usTmpData      = 0;
    VOS_UINT16                          usTmpOffset    = 0;
    VOS_UINT8                           aucTmpData[2]  = {0};

    /* ����Byte λ�� */
    usTmpOffset     = (usBitPos + ucBitNum - 1) / 8;

    /* ����bitλ�� */
    usTmpPos        = usBitPos % TAF_XSMS_BIT_NUMBER_OF_BYTE;
    usBits          = TAF_XSMS_BIT_NUMBER_OF_BYTE - usTmpPos;

    /* ��ȡ�����е�ֵ�ŵ���ʱ���� */
    aucTmpData[0]   = *(pucBuffer + usTmpOffset - 1);
    aucTmpData[1]   = *(pucBuffer + usTmpOffset);

    /* �ж��Ƿ���ͬһ���ֽ� */
    if (usBits >= ucBitNum)
    {
        usTmpData        = (0xff >> usTmpPos) & (0xff << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (usTmpPos + ucBitNum)));
        aucTmpData[1]   &= ~usTmpData;
        aucTmpData[1]   |= (VOS_UINT8)(usTmpData & (ucValue << (usBits - ucBitNum)));
        *(pucBuffer + usTmpOffset) = aucTmpData[1];
    }
    else
    {
        /* ����ͬһ���ֽڣ��������ֽ�д�� */
        usTmpData        = (0xff >> usTmpPos) & (0xff << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (usTmpPos + usBits)));
        aucTmpData[0]   &= ~usTmpData;
        aucTmpData[0]   |= (VOS_UINT8)(usTmpData & (ucValue >> (ucBitNum - usBits)));
        *(pucBuffer + usTmpOffset - 1) = aucTmpData[0];

        usTmpData        = (VOS_UINT16)(0xff << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (ucBitNum - usBits)));
        aucTmpData[1]   &= ~usTmpData;
        aucTmpData[1]   |= (VOS_UINT8)(usTmpData & (ucValue << (TAF_XSMS_BIT_NUMBER_OF_BYTE - (ucBitNum - usBits))));
        *(pucBuffer + usTmpOffset) = aucTmpData[1];
    }

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_ReplaceMessageID
 ��������  : �滻MessageID
 �������  : usMessageId:      �µ�MessageID��ֵ
 �������  : pucBDStru:        ��Ҫ���͵Ķ���Ϣ��Ril�ṹ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_ReplaceMessageID(
    TAF_XSMS_MESSAGE_STRU              *pucBDStru,
    VOS_UINT16                          usMessageId
)
{
    VOS_UINT8                           ucMsgIdHi;
    VOS_UINT8                           ucMsgIdLo;

    ucMsgIdHi = (VOS_UINT8)((usMessageId >> 8) & 0xff);
    ucMsgIdLo = (VOS_UINT8)(usMessageId & 0xff);

    TAF_XSMS_PackBitToByte(pucBDStru->aucBearerData, ucMsgIdHi, 8, 20);
    TAF_XSMS_PackBitToByte(pucBDStru->aucBearerData, ucMsgIdLo, 8, 28);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_FillTeleserviceID
 ��������  : ����TeleserviceID����
 �������  : pstBDStru:      ����������Ϣ�Ľṹ��ָ��
 �������  : pucPos:         �����ĵ�ַƫ��ֵ
             pucTLRawData:   �������׵�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_FillTeleserviceID(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                  = *pucPos;

    pucTLRawData[ucTmpPos++]  = TAF_XSMS_TL_TELESERVICE_ID;
    pucTLRawData[ucTmpPos++]  = 0x02;
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)((pstBDStru->ulTeleserviceID >> 8) & 0xff);
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)(pstBDStru->ulTeleserviceID & 0xff);
    *pucPos                   = ucTmpPos;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_FillServiceCategory
 ��������  : ����ServiceCategory����
 �������  : pstBDStru:      ����������Ϣ�Ľṹ��ָ��
 �������  : pucPos:         �����ĵ�ַƫ��ֵ
             pucTLRawData:   �������׵�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_FillServiceCategory(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                  = *pucPos;

    pucTLRawData[ucTmpPos++]  = TAF_XSMS_TL_SERVICR_CATEGORY;
    pucTLRawData[ucTmpPos++]  = 0x02;
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)((pstBDStru->ulServiceCategory >> 8) & 0xff);
    pucTLRawData[ucTmpPos++]  = (VOS_UINT8)pstBDStru->ulServiceCategory;
    *pucPos                   = ucTmpPos;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_FillAddress
 ��������  : ����Address����
 �������  : pstAddr:      ������ַ��Ϣ�Ľṹ��ָ��
 �������  : pucLen:       Address�����ĳ���
             pucTLRawData: �����ĵ�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_FillAddress(
    TAF_XSMS_ADDR_STRU                 *pstAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucLen
)
{
    VOS_UINT16                          ulBitPos = 0;
    VOS_UINT8                           ucDigitMode;
    VOS_UINT8                           ucReserveSize;
    VOS_UINT32                          i;

    /* д��Digit mode�ֶ� */
    TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enDigitMode, 1, ulBitPos);
    ulBitPos++;

    /* д��Number mode�ֶ� */
    TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enNumberMode, 1, ulBitPos);
    ulBitPos++;

    /* д��Number type��Number plan�ֶ� */
    if (TAF_XSMS_DIGIT_MODE_8_BIT == pstAddr->enDigitMode)
    {
        ucDigitMode = 8;

        TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enNumberType, 3, ulBitPos);
        ulBitPos += 3;

        if (TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK == pstAddr->enNumberMode)
        {
            TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->enNumberPlan, 4, ulBitPos);
            ulBitPos += 4;
        }
    }
    else
    {
        ucDigitMode = 4;
    }

    /* д��Address numbers�ֶ� */
    TAF_XSMS_PackBitToByte(pucTLRawData, (VOS_UINT8)pstAddr->ulNumberOfDigits, 8, ulBitPos);
    ulBitPos += 8;

    /* д��Address digits�ֶ� */
    for (i = 0; i < pstAddr->ulNumberOfDigits; i++)
    {
        TAF_XSMS_PackBitToByte(pucTLRawData, pstAddr->aucDigits[i],  ucDigitMode, ulBitPos);
        ulBitPos += ucDigitMode;
    }

    /* ��ȫ�ֽ� */
    if (0 != ulBitPos % 8)
    {
        ucReserveSize = (VOS_UINT8)(8 - (ulBitPos % 8));
        TAF_XSMS_PackBitToByte(pucTLRawData, 0, ucReserveSize, ulBitPos);
        ulBitPos += ucReserveSize;
    }

    /* д��������� */
    *pucLen = (VOS_UINT8)(ulBitPos / 8);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_FillSubAddress
 ��������  : ����SubAddress����
 �������  : pstSubAddr      �����ӵ�ַ��Ϣ�Ľṹ��ָ��
             enStates        ���ͻ��ǽ��յ���Ϣ
 �������  : pucPos          �����ĵ�ַƫ��ֵ
             pucTLRawData    �������׵�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_FillSubAddress(
    TAF_XSMS_SUB_ADDR_STRU             *pstSubAddr,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos,
    VOS_UINT8                           enStates
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTmpPos;
    VOS_UINT16                          usBitPos;

    ucTmpPos = *pucPos;

    /* �ж���дĿ�ĵ�ַ����Դ��ַ */
    if ((TAF_XSMS_STATUS_REC_UNREAD == enStates)
        || (TAF_XSMS_STATUS_REC_READ == enStates))
    {
        pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_ORIGIN_SUBADDR;
    }
    else
    {
        pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_DEST_SUBADDR;
    }
    pucTLRawData[ucTmpPos++]  = pstSubAddr->ucNumberOfDigits + 2;

    usBitPos  = 0;

    /* д��SubAddress type�ֶ� */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, pstSubAddr->enSubAddrType, 3, usBitPos);
    usBitPos += 3;

    /* д��Odd�ֶ� */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, pstSubAddr->ucOdd, 1, usBitPos);
    usBitPos += 1;

    /* д��Address numbers�ֶ� */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, pstSubAddr->ucNumberOfDigits, 8, usBitPos);
    usBitPos += 8;

    /* д��Address digits�ֶ� */
    for (ucIndex = 0; ucIndex < pstSubAddr->ucNumberOfDigits; ucIndex++)
    {
        TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos,
                                pstSubAddr->aucDigits[ucIndex], 8, usBitPos);
        usBitPos += 8;
    }

    /* ��ȫ�ֽ� */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, 0, 4, usBitPos);

    *pucPos  = ucTmpPos + pstSubAddr->ucNumberOfDigits + 2;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_FillBearerReplyOpiton
 ��������  : ����BearerReplyOpiton����
 �������  : ucBearReplySeqNum:               ReplyOpiton��ֵ
 �������  : pucPos:                          �����ĵ�ַƫ��ֵ
             pucTLRawData:                    �������׵�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_FillBearerReplyOpiton(
    VOS_UINT8                           ucBearReplySeqNum,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                 = *pucPos;
    pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_BEARER_REPLY_OPTION;
    pucTLRawData[ucTmpPos++] = 1;

    /* д��BearReplySeqNum�ֶ� */
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, ucBearReplySeqNum, 6, 0);
    TAF_XSMS_PackBitToByte(pucTLRawData + ucTmpPos, 0, 2, 6);
    *pucPos += 3;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_FillBearerData
 ��������  : ����BearerData����
 �������  : pstBDStru:             ����������Ϣ�Ľṹ��ָ��
 �������  : pucPos:                �����ĵ�ַƫ��ֵ
             pucTLRawData:          �������׵�ַ
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_FillBearerData(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucPos
)
{
    VOS_UINT8                           ucTmpPos;

    ucTmpPos                 = *pucPos;
    pucTLRawData[ucTmpPos++] = TAF_XSMS_TL_BERAER_DATA;
    pucTLRawData[ucTmpPos++] = (VOS_UINT8)pstBDStru->ulBearerDataLen;

    PS_MEM_CPY(pucTLRawData + ucTmpPos, pstBDStru->aucBearerData, pstBDStru->ulBearerDataLen);
    *pucPos = (VOS_UINT8)(pstBDStru->ulBearerDataLen & 0xff) + ucTmpPos;

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_GetP2PDBMStru
 ��������  : ����tpdu�õ���Ե�DMB�ṹ��(�ⲿ����)
 �������  : pstBDStru:                 ����������Ϣ�Ľṹ��ָ��
             usMessageIdentifier:       ��Ҫд��DBM�ṹ��Message Identifier
             ucBearerReplyOptionSeq:    ��Ҫд��DMB�ṹ���Bearer Reply OptionSeq
             enStates:                  ���ͻ��ǽ��յ���Ϣ
 �������  : pstDBMStru:                ��Ҫ�����DBM�ṹ��
 �� �� ֵ  : VOS_ERR                    ����ʧ��
             VOS_OK                     ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetP2PDBMStru(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                           enStates,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru,
    VOS_UINT32                          ulIsReplySeqNeed
)
{
    VOS_UINT8                           aucTLRawBuffer[TAF_XSMS_MAX_DBM_SIZE];
    VOS_UINT8                           ucNumFields;

    TAF_XSMS_TranslatePlusToNum(&pstBDStru->stAddr);

    if (VOS_ERR == TAF_XSMS_EncodeBearDataStruToP2PRaw(pstBDStru,
                                                       aucTLRawBuffer,
                                                       &ucNumFields,
                                                       ucBearerReplyOptionSeq,
                                                       usMessageIdentifier,
                                                       enStates,
                                                       ulIsReplySeqNeed))
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetP2PDBMStru:Data Burst Message encode failed");

        return VOS_ERR;
    }


    pstDBMStru->ucBurstType = DBM_SMS_TYPE;
    pstDBMStru->ucMsgNum    = 1;
    pstDBMStru->ucNumMsgs   = 1;
    pstDBMStru->ucNumFields = ucNumFields;
    PS_MEM_CPY(pstDBMStru->aucData, aucTLRawBuffer, ucNumFields);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_GetAckDBMStru
 ��������  : ����Ŀ�ĵ�ַ��Cause Code�õ�DBM�ṹ��(�ⲿ����)
 �������  : pstAddrStru:           ��Ҫд��DBM�ṹ��Ŀ�ĵ�ַ�ṹ��
             pstCauseCodeStru:      ��Ҫд��DBM�ṹ���pstCauseCode�ṹ��
 �������  : pstDBMStru:            ��Ҫ�����DBM�ṹ��
 �� �� ֵ  : VOS_ERR                ����ʧ��
             VOS_OK                 ����ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_GetAckDBMStru(
    TAF_XSMS_ADDR_STRU                 *pstAddrStru,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCodeStru,
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDBMStru
)
{
    VOS_UINT8                           aucTLRawBuffer[TAF_XSMS_MAX_DBM_SIZE];
    VOS_UINT8                           ucNumFields;

    if (VOS_ERR == TAF_XSMS_EncodeAckMsg(pstAddrStru,
                                         pstCauseCodeStru,
                                         aucTLRawBuffer,
                                         &ucNumFields))
    {

        TAF_XSMS_ERROR_LOG("TAF_XSMS_GetAckDBMStru:Ack message encode failed");

        return VOS_ERR;
    }

    pstDBMStru->ucBurstType = DBM_SMS_TYPE;
    pstDBMStru->ucMsgNum    = 1;
    pstDBMStru->ucNumMsgs   = 1;
    pstDBMStru->ucNumFields = ucNumFields;
    PS_MEM_CPY(pstDBMStru->aucData, aucTLRawBuffer, ucNumFields);

    return VOS_OK;
}
/*****************************************************************************
 �� �� ��  : TAF_XSMS_EncodeBearDataStruToP2PRaw
 ��������  : ��RIL�·��Ľṹ��ת���ɵ�Ե���ŵ�����(�ⲿ����)
 �������  : pstBDStru:                    �������TL�������Ľṹ��
             ucBearerReplyOptionSeq:       ������ʵ����Ҫʹ�õ�Bearer Reply Option Sequence
             usMessageIdentifier:          ������ʵ����Ҫʹ�õ�Message Identifier
             enStates:                     ���ͻ��ǽ��յ���Ϣ
 �������  : pucTLRawData:                 TL������ָ�룬����õ�����д�������
             pucEncodedLen:                ��������
 �� �� ֵ  : VOS_OK                        ����ɹ�
             VOS_ERR                       ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeBearDataStruToP2PRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT16                          usMessageIdentifier,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
)
{
    VOS_UINT8                           ucPos;

    TAF_XSMS_ReplaceMessageID(pstBDStru, usMessageIdentifier);
    if (VOS_ERR == (TAF_XSMS_EncodeBearDataStruToSimRaw(pstBDStru,
                                                        pucTLRawData,
                                                        ucBearerReplyOptionSeq,
                                                        &ucPos,
                                                        enStates,
                                                        ulIsReplySeqNeeded)))
    {

        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToP2PRaw:Point to point message encode failed");

        return VOS_ERR;
    }

    *pucEncodedLen = ucPos;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_EncodeBearDataStruToSimRaw
 ��������  : ��RIL�·��Ľṹ��ת������Ҫд��UIM���ĵ�Ե���ŵ�����(�ⲿ����)
 �������  : pstBDStru:                   �������TL�������Ľṹ��
             ucBearerReplyOptionSeq:      ������ʵ����Ҫʹ�õ�Bearer Reply Option Sequence
             usMessageIdentifier:         ������ʵ����Ҫʹ�õ�Message Identifier
             enStates:                    ���ͻ��ǽ��յ���Ϣ
 �������  : pucTLRawData:                TL������ָ�룬����õ�����д�������
             pucEncodedLen:               �ܹ�������˶����ֽ�
 �� �� ֵ  : VOS_OK                       ����ɹ�
             VOS_ERR                      ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeBearDataStruToSimRaw(
    TAF_XSMS_MESSAGE_STRU              *pstBDStru,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                           ucBearerReplyOptionSeq,
    VOS_UINT8                          *pucEncodedLen,
    VOS_UINT8                           enStates,
    VOS_UINT32                          ulIsReplySeqNeeded
)
{
    VOS_UINT8                           ucPos;
    VOS_UINT8                           ucLen;

    ucPos  = 0;

    /* дTELESERVICE_ID�ֶ� */
    pucTLRawData[ucPos++] = TAF_XSMS_TL_P2P_MSG;

    /* дTELESERVICE_ID�ֶ� */
    TAF_XSMS_FillTeleserviceID(pstBDStru, pucTLRawData, &ucPos);

    /* дServiceCategory�ֶ� */
    if (VOS_TRUE == pstBDStru->bIsServicePresent)
    {
        TAF_XSMS_FillServiceCategory(pstBDStru, pucTLRawData, &ucPos);
    }

    /* дDstAddr�ֶ� */
    if ((0 != pstBDStru->stAddr.ulNumberOfDigits)
    &&  (TAF_XSMS_ADDRESS_MAX > pstBDStru->stAddr.ulNumberOfDigits))
    {
        /* �ж���дĿ�ĵ�ַ����Դ��ַ */
        if ((TAF_XSMS_STATUS_REC_UNREAD == enStates)
            || (TAF_XSMS_STATUS_REC_READ == enStates))
        {
            pucTLRawData[ucPos++] = TAF_XSMS_TL_ORIGIN_ADDR;
        }
        else
        {
            pucTLRawData[ucPos++] = TAF_XSMS_TL_DEST_ADDR;
        }
        TAF_XSMS_FillAddress(&pstBDStru->stAddr, pucTLRawData + ucPos + 1, &ucLen);
        pucTLRawData[ucPos++] = ucLen;
        ucPos                += ucLen;
    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToSimRaw:Point to point message missing mandatory paramter");

        return VOS_ERR;
    }

    /* дDstSubAddr�ֶ� */
    if (TAF_XSMS_ADDRESS_MAX < pstBDStru->stSubAddr.ucNumberOfDigits)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToSimRaw:stSubAddr.ucNumberOfDigits > 36");

        return VOS_ERR;
    }

    if (0 != pstBDStru->stSubAddr.ucNumberOfDigits)
    {
        TAF_XSMS_FillSubAddress(&pstBDStru->stSubAddr, pucTLRawData, &ucPos, enStates);
    }

    /* дBearReplyOption�ֶ� */
    if (VOS_TRUE == ulIsReplySeqNeeded)
    {
        TAF_XSMS_FillBearerReplyOpiton(ucBearerReplyOptionSeq, pucTLRawData, &ucPos);
    }

    /* дBearData�ֶ� */
    if (TAF_XSMS_TPDU_LEN_MAX < (ucPos + pstBDStru->ulBearerDataLen))
    {

        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeBearDataStruToSimRaw:Point to point message Bear Data too long");

        return VOS_ERR;
    }

    /* дBearData�ֶ� */
    if (0 != pstBDStru->ulBearerDataLen)
    {
        TAF_XSMS_FillBearerData(pstBDStru, pucTLRawData, &ucPos);
    }

    *pucEncodedLen = ucPos;

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : TAF_XSMS_EncodeAckMsg
 ��������  : ����TL���ACK
 �������  : pstDestAddr:          ����Ŀ�ĵ�ַ��Ϣ�Ľṹ��ָ��
             pstCauseCode:         ����CauseCode��Ϣ�Ľṹ��ָ��
 �������  : pucTLRawData:         �����ĵ�ַ
             pucCodedLen:          �����ĳ���
 �� �� ֵ  : VOS_OK                ����ɹ�
             VOS_ERR               ����ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : x00306642
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeAckMsg(
    TAF_XSMS_ADDR_STRU                 *pstDestAddr,
    TAF_XSMS_CAUSE_CODE_STRU           *pstCauseCode,
    VOS_UINT8                          *pucTLRawData,
    VOS_UINT8                          *pucCodedLen
)
{
    VOS_UINT8                           ucPos = 0;
    VOS_UINT8                           ucLen;

    /* д��SMS ID�ֶ� */
    pucTLRawData[ucPos++] = TAF_XSMS_TL_ACK_MSG;

    /* д��DestAddr�ֶ� */
    if ((0 != pstDestAddr->ulNumberOfDigits)
    &&  (TAF_XSMS_ADDRESS_MAX > pstDestAddr->ulNumberOfDigits))
    {
        pucTLRawData[ucPos++] = TAF_XSMS_TL_DEST_ADDR;
        TAF_XSMS_FillAddress(pstDestAddr, pucTLRawData + ucPos + 1, &ucLen);
        pucTLRawData[ucPos++] = ucLen;
        ucPos                += ucLen;
    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeAckMsg:Ack message missing mandatory paramter");

        return VOS_ERR;
    }

    /* д��Cause code�ֶ� */
    pucTLRawData[ucPos++] = TAF_XSMS_TL_CAUSE_CODE;
    if (TAF_XSMS_TL_CAUSECODE_NONE != pstCauseCode->enErrorClass)
    {
        pucTLRawData[ucPos++] = 2;
    }
    else
    {
        pucTLRawData[ucPos++] = 1;
    }

    pucTLRawData[ucPos++] = ((pstCauseCode->ucReplySeq << 2) & 0xfc) | ((pstCauseCode->enErrorClass & 0x03));

    if (TAF_XSMS_TL_CAUSECODE_NONE != pstCauseCode->enErrorClass)
    {
        pucTLRawData[ucPos++] = pstCauseCode->enCauseCode;
    }

    /* д���������� */
    *pucCodedLen = ucPos;

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_EncodeAuth
 ��������  : �����Ȩ����
 �������  : pstDestinationAddr:    ��Ҫ������Ϣ���豸��Ŀ�ĵ�ַ
 �������  : pucAuthData:           ����ļ�Ȩ����
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��10��31��
    ��    ��   : j00304117
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_EncodeAuth(
    TAF_XSMS_ADDR_STRU                 *pstDestinationAddr,
    VOS_UINT8                          *pucAuthData
)
{
    VOS_UINT8                           aucISMS_S1[3];
    VOS_UINT8                           ucIndex;
    VOS_UINT8                           ucTmp;
    VOS_UINT8                           aucNum[6] = {0};
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAuth;


    pstInitCtrlInfoAuth = TAF_XSMS_GetInitCtrlInfoAddr();
    PS_MEM_CPY(aucISMS_S1, pstInitCtrlInfoAuth->aucImsi + 2, 3);

    for (ucIndex = 0; ucIndex < DIGITS_OF_AUTN; ucIndex++)
    {
        TAF_XSMS_TL_UnpackByteToBit(aucISMS_S1, aucNum + ucIndex, ucIndex * 4, 4);
    }

    /* �Ȱ�ISMI_S1��ֵ��pucAuthData */
    ucTmp = (VOS_UINT8)pstDestinationAddr->ulNumberOfDigits;

    /* ���ݺ���ı��뷽ʽд��ʱ�����ֵ */
    for (ucIndex = DIGITS_OF_AUTN; ucIndex != 0; ucIndex--)
    {
        /* 8bit���뷽ʽ */
        if (TAF_XSMS_DIGIT_MODE_8_BIT == pstDestinationAddr->enDigitMode)
        {
            /* 8bit���뷽ʽ��ֵ�����޷�������ȡ16�࣬Ȼ����DTMF���� */
            if (0 != (--ucTmp))
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp] % 16;
                if (0 == aucNum[ucIndex - 1])
                {
                    aucNum[ucIndex - 1] = 0x0a;
                }
            }
            else
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp] % 16;
                if (0 == aucNum[ucIndex - 1])
                {
                    aucNum[ucIndex - 1] = 0x0a;
                }
                break;

            }
        }
        else
        {
            /* 4bit  DTMF ���뷽ʽ */
            if (0 != (--ucTmp))
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp];
            }
            else
            {
                aucNum[ucIndex - 1] = pstDestinationAddr->aucDigits[ucTmp];
                break;
            }
        }
    }

    /* �Ѽ�Ȩ����д���Ȩ������ */
    for (ucIndex = 0; ucIndex < DIGITS_OF_AUTN; ucIndex++)
    {
        TAF_XSMS_PackBitToByte(pucAuthData, aucNum[ucIndex], 4, ucIndex * 4);
    }

}



#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



