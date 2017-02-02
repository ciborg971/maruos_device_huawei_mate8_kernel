/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : LnasLppEncode.c
  Description     :
  History         :
     1.HANLUFENG 41410       2013-8-8   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "vos.h"
#include  "NasLppAirMsg.h"
#include  "NasLppEncodeDecodePublic.h"
#include  "NasLppPublic.h"
#include  "NasLppEncode.h"
#include  "NasCommPrint.h"
//#include  "LPPLRrcInterface.h"

#define NAS_LPP_ENCODE_WARNING

#define    THIS_FILE_ID            PS_FILE_ID_NASLPPENCODE_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASLPPENCODE_C


/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/
#if (FEATURE_LPP == FEATURE_ON)

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUIdentifier
 Description     : ����LPP_EPDU_IDENTIFIER_STRU
 Input           : pstEPDUIBody               ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUBody
(
    LPP_EPDU_BODY_STRU                 *pstEPDUIBody,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT32                          ulTempCount         = 0;

    /*����OCTET STRING ����*/
    /*Э��û���޶����ȣ����Ǵ�������п��ٵ��ڴ�ռ�Ϊ256������256�ڴ�������������
    ������������ֱ�ӷ��ش���*/
    if(pstEPDUIBody->ulBodyLen > 256)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_EPDUBODY_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    /*�������Ϊ256����Ҫ����0x81,Ȼ�����0x00Ȼ�����BODY����*/
    if(pstEPDUIBody->ulBodyLen == 256)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0x81);
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0);
    }
    /*������ȴ��ڵ���128����Ҫռ�������ֽڣ���һ���ֽ�ֵΪ0x80���ڶ����ֽ�Ϊ����ֵ*/
    else if(pstEPDUIBody->ulBodyLen >= 128)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0x80);
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)(pstEPDUIBody->ulBodyLen));
    }
    /*�������С��128��ֱ�ӱ����λ����*/
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)(pstEPDUIBody->ulBodyLen));
    }



    /*����ṹ������*/
    for(ulTempCount = 0;ulTempCount < pstEPDUIBody->ulBodyLen;ulTempCount++)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, pstEPDUIBody->aucBodyData[ulTempCount]);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUIdentifier
 Description     : ����LPP_EPDU_IDENTIFIER_STRU
 Input           : pstEPDUIdentifier          ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUIdentifier
(
    LPP_EPDU_IDENTIFIER_STRU           *pstEPDUIdentifier,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucTempCount         = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);

    /* ����OPTIONAL��־λ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstEPDUIdentifier->bitOpEpduName));

    /*����ṹ������*/
    /*����EPDU-ID*/

    if((pstEPDUIdentifier->ulEpduId < 1) ||(pstEPDUIdentifier->ulEpduId > 256))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDUIDENTIFIER_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    ucTempCount = (VOS_UINT8)(pstEPDUIdentifier->ulEpduId - 1);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucTempCount);

    /*����EPDU-NAME,�����ѡ��*/
    if(NAS_LPP_NO_SLCT == pstEPDUIdentifier->bitOpEpduName)
    {
        return  NAS_LPP_ENCODE_SUCC;
    }

    /*����EPDU-NAME����*/
    if((pstEPDUIdentifier->ulEpduNameLength < 1)||(pstEPDUIdentifier->ulEpduNameLength > 32))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDUIDENTIFIER_ERROR, NAS_LPP_CHAR_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHAR_LEN_ERROR;
    }
    ucTempCount = (VOS_UINT8)(pstEPDUIdentifier->ulEpduNameLength - 1);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5, ucTempCount);

    /*����EPDU-NAMEֵ*/
    for(ucTempCount = 0; ucTempCount < (pstEPDUIdentifier->ulEpduNameLength);ucTempCount++)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, pstEPDUIdentifier->acEpduName[ucTempCount]);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDU
 Description     : ����pstEPDU
 Input           : pstEPDU                    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
                 EPDU ::= SEQUENCE {
                     ePDU-Identifier         EPDU-Identifier,
                     ePDU-Body               EPDU-Body
                 }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDU
(
    LPP_EPDU_STRU                      *pstEPDU,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt;


    /*����ṹ������*/
    /*����EPDU-Identifier*/
    usReturnReslt = NAS_LPP_EncodeEPDUIdentifier(&(pstEPDU->stEpduIdentifier),
                                                    pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return  usReturnReslt;
    }

    /*����EPDU-Body*/
    usReturnReslt = NAS_LPP_EncodeEPDUBody(&(pstEPDU->stEpduBody),
                                              pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return  usReturnReslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUSequence
 Description     : ����LPP_EPDU_SEQUENCE_STRU
 Input           : pstEPDUSequence            ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
                 EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

                 maxEPDU INTEGER ::= 16

                 EPDU ::= SEQUENCE {
                     ePDU-Identifier         EPDU-Identifier,
                     ePDU-Body               EPDU-Body
                 }

                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }

                 EPDU-ID ::= INTEGER (1..256)

                 EPDU-Name ::= VisibleString (SIZE (1..32))

                 EPDU-Body ::= OCTET STRING

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUSequence
(
    LPP_EPDU_SEQUENCE_STRU             *pstEPDUSequence,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt;
    VOS_UINT32                          ulCount             = 0;
    VOS_UINT32                          ulLoop              = 0;
    /*�ж����ȺϷ���*/
    if((pstEPDUSequence->ulEpduNum > 16)||(pstEPDUSequence->ulEpduNum < 1))
    {
        NAS_LPP_ENCODE_WARNING;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDUSEQUENCE_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*���볤��ֵ*/
    ulCount = pstEPDUSequence->ulEpduNum - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)ulCount);
    /*ѭ������EPDU����*/

    for(ulLoop = 0;ulLoop < pstEPDUSequence->ulEpduNum;ulLoop++)
    {
        usReturnReslt = NAS_LPP_EncodeEPDU(&(pstEPDUSequence->astEpduArray[ulLoop]),
                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
        {
            return  usReturnReslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeInitiator
(
    LPP_INITIATOR_TYPE_ENUM_UINT8      *pucInitiator,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    if( *pucInitiator > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_INITIATOR_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    /*����ö�������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����ö�����ʵ��ֵ*/
    /*����һ�£�����ö��ֻ���������ֻ��1��bit�Ϳ��Ա�ʾ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, *pucInitiator);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeTransactionId
(
    LPP_TRANSACTION_ID_STRU             *pstLppTranscationId,
    VOS_UINT16                          *pusBitPos,
    VOS_UINT8                           *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRelst             = 0;

    /*������չλ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����Initiator*/
    usRelst = NAS_LPP_EncodeInitiator(&(pstLppTranscationId->enInitiator),
                                         pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRelst)
    {
        return  usRelst;
    }

    /*�������ͱ���transactionNumber*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8,
                              pstLppTranscationId->ucTransactionNumber);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAcknowLedgement
(
    LPP_ACKNOWLEDGEMENT_STRU           *pstLppAcknowLedgement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstLppAcknowLedgement->bitOpAckIndicator));

    /*����ackRequested*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstLppAcknowLedgement->bAckRequested));

    /*����ackIndicator*/
    if(NAS_LPP_SLCT == pstLppAcknowLedgement->bitOpAckIndicator)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8,
                                  pstLppAcknowLedgement->stAckIndicator.ucSequenceNumber);
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeCommonIEsProvideCapabilities
(
    LPP_COMMON_IES_PROVIDE_CAP_STRU    *pstCommonIesProvideCap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չλ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGnssId
(
    LPP_GNSS_ID_STRU                   *pstGnssId,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չλ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����ö�������չ��, ��ʵ����չ������һ��bitΪ0����*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����ö�����ʵ��ֵ,ö�����ܹ�5�������3��bit��ʾ����*/
    /*���ö��ֵ������Χ���򷵻أ������׳��쳣*/
    if(4 < (pstGnssId->enGnssId))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSID_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, pstGnssId->enGnssId);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeSbasIds
(
    LPP_SBAS_IDS_STRU                  *pstSbasIds,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��, �����ֶα���
      ����ʵ�ʳ��ȼ�ȥ���ٽ磬Ȼ����Ч�����ݷŵ����λ*/
    /*��Ϊ�����Ч�ĳ���Ŀǰֻ��4��bit�����㳤����4-8֮�䣬Ҳ��Ϊ�Ǵ���*/
    if((pstSbasIds->ucSabsIdsLen < 1)
        || (pstSbasIds->ucSabsIdsLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SBASIDS_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstSbasIds->ucSabsIdsLen - 1));

    /*��������bit string*/
    /*����Ч�������Ƶ����λ��Ȼ�����ʵ�ʳ��ȵ�������buffer�м���*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstSbasIds->ucSabsIdsLen, pstSbasIds->ucSBASIDs);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodePositionMode
(
    LPP_POSITIONING_MODES_STRU         *pstPositionMode,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��, �����ֶα���
      ����ʵ�ʳ��ȼ�ȥ���ٽ磬Ȼ����Ч�����ݷŵ����λ*/
    if((pstPositionMode->ucPosModeLen < 1)
        || (pstPositionMode->ucPosModeLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POSITIONMODE_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstPositionMode->ucPosModeLen) - 1);

    /*��������bit string*/
    /*����Ч�������Ƶ����λ��Ȼ�����ʵ�ʳ��ȵ�������buffer�м���*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstPositionMode->ucPosModeLen,
                              pstPositionMode->ucPositioningModes);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGnssSignalIds
(
    LPP_GNSS_SIGNAL_IDS_STRU           *pstGnssSignalIds,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*��������bit string*, �̶��������賤���ֶ�*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, pstGnssSignalIds->ucGNSSSignalIds);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeAccessTypes
(
    LPP_ACCESS_TYPES_STRU                       *pstAccessTypes,
    VOS_UINT16                                  *pusBitPos,
    VOS_UINT8                                   *pucEncodeOutMsg)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��, �����ֶα���
      ����ʵ�ʳ��ȼ�ȥ���ٽ磬Ȼ����Ч�����ݷŵ����λ*/
    if((pstAccessTypes->ucAccessTypesCnt < 1)
        || (pstAccessTypes->ucAccessTypesCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ACCESSTYPES_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstAccessTypes->ucAccessTypesCnt) - 1);

    /*��������bit string*/
    /*����Ч�������Ƶ����λ��Ȼ�����ʵ�ʳ��ȵ�������buffer�м���*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstAccessTypes->ucAccessTypesCnt,
                              pstAccessTypes->ucAccessTypes);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeFtaMeasSupport
(
    LPP_FTA_MEAS_SUPPORT_STRU          *pstFtaMeasSupport,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt = 0;
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����AccessTypes*/
    usRslt = NAS_LPP_EncodeAccessTypes(&(pstFtaMeasSupport->stAccessTypes),
                                          pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����PositioningModes*/
    usRslt = NAS_LPP_EncodePositionMode(&(pstFtaMeasSupport->stPositioningModes),
                                           pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapGnssSupportElement
(
    LPP_GNSS_SUPPORT_ELEMENT_STRU      *pstAgnssSupporElement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucOption        = 0;
    VOS_UINT16                          usRslt          = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    ucOption = (VOS_UINT8)((((pstAgnssSupporElement->bitOpSbasIds) << 1))
                | (pstAgnssSupporElement->bitOpFtaMeasSupport));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, ucOption);

    /*����GNSS-ID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstAgnssSupporElement->stGnssId),
                                     pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����SBAS-IDs*/
    if(NAS_LPP_SLCT == pstAgnssSupporElement->bitOpSbasIds)
    {
        usRslt = NAS_LPP_EncodeSbasIds(&(pstAgnssSupporElement->stSbasIds),
                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����PositioningModes*/
    usRslt = NAS_LPP_EncodePositionMode(&(pstAgnssSupporElement->stAgnssModes),
                                           pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����GNSS-SignalIDs*/
    NAS_LPP_EncodeGnssSignalIds(&(pstAgnssSupporElement->stGnssSignals),
                                   pusBitPos, pucEncodeOutMsg);

    /*����fta-MeasSupport*/
    if(NAS_LPP_SLCT == pstAgnssSupporElement->bitOpFtaMeasSupport)
    {
        usRslt = NAS_LPP_EncodeFtaMeasSupport(&(pstAgnssSupporElement->stFtaMeasSupport),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����adr-Support*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssSupporElement->bSdrSupport));

    /*����velocityMeasurementSupport*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssSupporElement->bVelocityMeasurementSupport));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesGnssSupportList
(
    LPP_GNSS_SUPPORT_LIST_STRU         *pstAgnssSupportList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8   ucLoop = 0;
    VOS_UINT16  usRslt = 0;
    VOS_UINT8   ucGnssSupportNum = 0;

    /*����GnssSupport��������������Լ���Ľṹ�����飬���Գ��Ȳ�����Сbit����ԭ��
      �����ֵ�������λ�õ�ֵΪ׼,��Լ���ĳ�����16-1=15����ʾ15�����Ҫ4��bit
      ��ʾ�����Ա���Ҳֻ��Ҫ��4��bit����*/
    if((1 > (pstAgnssSupportList->ulSupportElementNum))
       || (16 < (pstAgnssSupportList->ulSupportElementNum)))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_AGNSSIESPROVIDECAPABILITIESGNSSSUPPORTLIST_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*����ṹ��ļ���*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4,
                             (VOS_UINT8)((pstAgnssSupportList->ulSupportElementNum) - 1));

    /*����ṹ������ľ����ԱGNSS-SupportElement*/
    ucGnssSupportNum = (VOS_UINT8)(pstAgnssSupportList->ulSupportElementNum);
    for(ucLoop = 0; ucLoop < ucGnssSupportNum; ucLoop++)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapGnssSupportElement(&(pstAgnssSupportList->astGnssSupportElementArray[ucLoop]),
                                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGnssSystemTime
(
    LPP_GNSS_ID_BITMAP_STRU            *pstGnssIdBitMap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��, �����ֶα���
      ����ʵ�ʳ��ȼ�ȥ���ٽ磬Ȼ����Ч�����ݷŵ����λ*/
    if((pstGnssIdBitMap->usGnssIdsCnt < 1)
        || (pstGnssIdBitMap->usGnssIdsCnt > 16))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSYSTEMTIME_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4,
                             (VOS_UINT8)((pstGnssIdBitMap->usGnssIdsCnt) - 1));
    /*��������bit map*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos,
                                  pstGnssIdBitMap->usGnssIdsCnt,
                                  (VOS_UINT32)(pstGnssIdBitMap->usGNSSIDs));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportRefTime
(
    LPP_GNSS_REFERENCE_TIME_SUPPORT_STRU                    *pstGnssRefTimeSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    VOS_UINT8                                                ucOption       = 0;
    VOS_UINT16                                               usRslt         = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    ucOption = (VOS_UINT8)(pstGnssRefTimeSupport->bitOpFtaSupport);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ucOption);

    /*����GNSS-SystemTime*/
    usRslt = NAS_LPP_EncodeGnssSystemTime(&(pstGnssRefTimeSupport->stGnssSystemTime),
                                             pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����FTA_Support*/
    if(NAS_LPP_SLCT == pstGnssRefTimeSupport->bitOpFtaSupport)
    {
        usRslt = NAS_LPP_EncodeAccessTypes(&(pstGnssRefTimeSupport->stFtaSupport),
                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportLocSupport
(
    LPP_GNSS_REFERENCE_LOCATION_SUPPORT_STRU                *pstGnssLocationSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    /*����Ƚ������ֻ��...��չλ������ֻ��Ҫ������չλ����*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportInonModelSupport
(
    LPP_GNSS_IONOSPHERIC_MODE_SUPPORT_STRU                  *pstGnssIonModeSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��, �����ֶα���
      ����ʵ�ʳ��ȼ�ȥ���ٽ磬Ȼ����Ч�����ݷŵ����λ*/
    if((pstGnssIonModeSupport->ucIonoModelLen < 1)
        || (pstGnssIonModeSupport->ucIonoModelLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSCOMMONASSISTANCEDATASUPPORTINONMODELSUPPORT_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, (pstGnssIonModeSupport->ucIonoModelLen) - 1);

    /*��������bit string*/
    /*����Ч�������Ƶ����λ��Ȼ�����ʵ�ʳ��ȵ�������buffer�м���*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstGnssIonModeSupport->ucIonoModelLen,
                              pstGnssIonModeSupport->ucIonoModel);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupportEarthOrientParaSupport
(
    LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_SUPPORT_STRU      *pstGnssEarthOrientParaSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    /*����Ƚ������ֻ��...��չλ������ֻ��Ҫ������չλ����*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGNSSCommonAssistanceDataSupport
(
    LPP_GNSS_COMMON_ASSISTANCE_DATA_SUPPORT_STRU            *pstCommonAssitDataSupport,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    VOS_UINT8                                                ucOption       = 0;
    VOS_UINT16                                               usRslt         = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    ucOption = (VOS_UINT8)(((pstCommonAssitDataSupport->bitOpGnssReferenceTimeSupport) << 3)
                | ((pstCommonAssitDataSupport->bitOpGnssReferenceLocationSupport) << 2)
                | ((pstCommonAssitDataSupport->bitOpGnssIonosphericModelSupport) << 1)
                | (pstCommonAssitDataSupport->bitOpGnssEarthOrientationParametersSupport));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, ucOption);

    /*����ReferenceTimeSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssReferenceTimeSupport)
    {
        usRslt = NAS_LPP_EncodeGNSSCommonAssistanceDataSupportRefTime(&(pstCommonAssitDataSupport->stGnssReferenceTimeSupport),
                                                                         pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����ReferenceLocationSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssReferenceLocationSupport)
    {
        NAS_LPP_EncodeGNSSCommonAssistanceDataSupportLocSupport(&(pstCommonAssitDataSupport->stGnssReferenceLocationSupport),
                                                                   pusBitPos, pucEncodeOutMsg);
    }

    /*����IonosphericModelSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssIonosphericModelSupport)
    {
        usRslt = NAS_LPP_EncodeGNSSCommonAssistanceDataSupportInonModelSupport(&(pstCommonAssitDataSupport->stGnssIonosphericModelSupport),
                                                                                  pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����EarthOrientationParametersSupport*/
    if(NAS_LPP_SLCT == pstCommonAssitDataSupport->bitOpGnssEarthOrientationParametersSupport)
    {
        NAS_LPP_EncodeGNSSCommonAssistanceDataSupportEarthOrientParaSupport(&(pstCommonAssitDataSupport->stGnssEarthOrientationParametersSupport),
                                                                               pusBitPos, pucEncodeOutMsg);
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeSbasId
(
    LPP_SBAS_ID_STRU                   *pstSbasId,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չλ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����ö����initiator*/
    /*����ö�������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����ö�����ʵ��ֵ, ��Ϊ��4�������Ҫ2��bit����ʾ*/
    if(pstSbasId->enLppSbasId > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SBASID_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, pstSbasId->enLppSbasId);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGnssTimeModelListSupport
(
    LPP_GNSS_TIME_MODE_LIST_SUPPORT_STRU                   *pstGnssTimeModeListSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGnssDifferentialCorrectionsSupport
(
    LPP_GNSS_DIFFERENTIAL_CORRECTIONS_SUPPORT_STRU         *pstGnssDiffCorrectSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����GnssSignals*/
    NAS_LPP_EncodeGnssSignalIds(&(pstGnssDiffCorrectSupport->stGnssSignalIDs), pusBitPos, pucEncodeOutMsg);

    /*����DGNSS-Validity*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssDiffCorrectSupport->bDgnssValidityTimeSup));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGnssNavigationModelSupport
(
    LPP_GNSS_NAVIGATION_MODE_SUPPORT_STRU                  *pstGnssNavigationModeSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8       ucOption = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    ucOption = (VOS_UINT8)(((pstGnssNavigationModeSupport->bitOpClockModel) << 1)
                | (pstGnssNavigationModeSupport->bitOpOrbitModel));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, ucOption);

    /*����ClockModel*/
    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��, �����ֶα���
      ����ʵ�ʳ��ȼ�ȥ���ٽ磬Ȼ����Ч�����ݷŵ����λ*/
    if(NAS_LPP_SLCT == pstGnssNavigationModeSupport->bitOpClockModel)
    {
        if((pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt < 1)
            || (pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSNAVIGATIONMODELSUPPORT_ERROR,
                                     NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        /*����L*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt) - 1);

        /*��������bit string*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                  pstGnssNavigationModeSupport->stClockModel.ucClockModelCnt,
                                  pstGnssNavigationModeSupport->stClockModel.ucClockModel);
    }

    if(NAS_LPP_SLCT == pstGnssNavigationModeSupport->bitOpOrbitModel)
    {
        if((pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt < 1)
            || (pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSNAVIGATIONMODELSUPPORT_ERROR,
                                     NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        /*����L*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt) - 1);

        /*��������bit string*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                  pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModelCnt,
                                  pstGnssNavigationModeSupport->stOrbitModel.ucOrbitModel);
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeRealTimeIntegritySupport
(
    LPP_GNSS_REAL_TIME_INTEGRITY_SUPPORT_STRU              *pstGnssRealTimeIntegritySupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeDataBitAssistanceSupport
(
    LPP_GNSS_DATA_BIT_ASSISTANCE_SUPPORT_STRU              *pstGnssDataBitAssitSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeAcquisitionAssistanceSupport
(
    LPP_GNSS_ACQUISITION_ASSISTANCE_SUPPORT_STRU           *pstGnssAcquistionAssitSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*�������һ�£�...ǰ�ã� ˵��...֮������չ���ô�ó���������չλ�ı���*/
    /*������չ��*/
    VOS_UINT8                                               ucExtIe             = 0;
    VOS_UINT8                                               ucExtOption         = 0;
    VOS_UINT8                                               ucConfidenceLV      = 0;
    VOS_UINT8                                               ucConfidenceFill    = 0;
    VOS_UINT8                                               ucDopplerLV         = 0;
    VOS_UINT8                                               ucDopplerSupportFill = 0;

    /*������չ��*/
    ucExtIe = (VOS_UINT8)(pstGnssAcquistionAssitSupport->bitOpGNSSAcquisitionAssistSupExt);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ucExtIe);

    if(NAS_LPP_NO_SLCT == pstGnssAcquistionAssitSupport->bitOpGNSSAcquisitionAssistSupExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*������չ���L-1, 2-1����1����չ���*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 1);

    /*������չ��Ŀ�ѡ��*/
    ucExtOption = (VOS_UINT8)(((pstGnssAcquistionAssitSupport->bitOpConfidenceSupportR10) << 1)
                | (pstGnssAcquistionAssitSupport->bitOpDopplerUncertaintyExtSupportR10));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, ucExtOption);

    if(NAS_LPP_SLCT == pstGnssAcquistionAssitSupport->bitOpConfidenceSupportR10)
    {
        /*����confidenceSupport ��L+V, ����ռ��һ��byte�� �������ݱ�ʾռ�ö��ٸ�byte*/
        ucConfidenceLV = 1;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucConfidenceLV);

        /*ע������ö����ֻ��һ���ռ��bit��Ҳ����ֻҪѡ�У��϶���ֵ�������������8�����λ����*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucConfidenceFill);
    }

    if(NAS_LPP_SLCT == pstGnssAcquistionAssitSupport->bitOpDopplerUncertaintyExtSupportR10)
    {
        /*����dopplerUncertaintyExtSupport ��L+V, ����ռ��һ��byte�� �������ݱ�ʾռ�ö��ٸ�byte*/
        ucDopplerLV = 1;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucDopplerLV);

        /*ע������ö����ֻ��һ���ռ��bit��Ҳ����ֻҪѡ�У��϶���ֵ*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucDopplerSupportFill);
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAlmanacSupport
(
    LPP_GNSS_ALMANAC_SUPPORT_STRU      *pstGnssAlanacSupport,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssAlanacSupport->bitOpAlmanacModel));

    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��*/
    if(NAS_LPP_SLCT == pstGnssAlanacSupport->bitOpAlmanacModel)
    {
        if((pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt < 1)
            ||(pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_ALMANACSUPPORT_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (VOS_UINT8)((pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt) - 1));

        /*��������bit string*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                 (VOS_UINT8)(pstGnssAlanacSupport->stAlmanacModel.ulAlmanacModelCnt),
                                  pstGnssAlanacSupport->stAlmanacModel.ucAlmanacModel);
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeUTCModelSupport
(
    LPP_GNSS_UTC_MODEL_SUPPORT_STRU    *pstGnssUtcModelSupport,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssUtcModelSupport->bitOpUtcModel));

    /*����bit string�ĳ����ֶΣ��������ٱ���ԭ��, �����ֶα���
      ����ʵ�ʳ��ȼ�ȥ���ٽ磬Ȼ����Ч�����ݷŵ����λ*/
    if(NAS_LPP_SLCT == pstGnssUtcModelSupport->bitOpUtcModel)
    {
        if((pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt < 1)
            || (pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt > 8))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTCMODELSUPPORT_ERROR,
                                     NAS_LPP_BIT_STRING_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
        }

        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (VOS_UINT8)((pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt) -1));

        /*��������bit string*/
        /*����Ч�������Ƶ����λ��Ȼ�����ʵ�ʳ��ȵ�������buffer�м���*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos,
                                 (VOS_UINT8)(pstGnssUtcModelSupport->stUtcModel.ulUtcModelCnt),
                                  pstGnssUtcModelSupport->stUtcModel.ucUTCModel);
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeAuxiliaryInformationSupport
(
    LPP_GNSS_AUXILIARY_INFORMATION_SUPPORT_STRU            *pstGnssAuxiliaryInfoSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapGenericAssitDataSupportList
(
    LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_ELEMENT_STRU   *pstGnssGenericAssitDataSupportElement,
    VOS_UINT16                                              *pusBitPos,
    VOS_UINT8                                               *pucEncodeOutMsg
)
{
    VOS_UINT16                                               usOption       = 0;
    VOS_UINT16                                               usRslt         = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    usOption = (VOS_UINT16)(((pstGnssGenericAssitDataSupportElement->bitOpSbasIds) << 9)
                | ((pstGnssGenericAssitDataSupportElement->bitOpGnssTimeModelListSupport) << 8)
                | ((pstGnssGenericAssitDataSupportElement->bitOpGnssDifferentialCorrectionsSupport) << 7)
                | ((pstGnssGenericAssitDataSupportElement->bitOpGnssNavigationModelSupport) << 6)
                | ((pstGnssGenericAssitDataSupportElement->bitOpRealTimeIntegritySupport) << 5)
                | ((pstGnssGenericAssitDataSupportElement->bitOpDataBitAssistanceSupport) << 4)
                | ((pstGnssGenericAssitDataSupportElement->bitOpAcquisitionAssistanceSupport) << 3)
                | ((pstGnssGenericAssitDataSupportElement->bitOpAlmanacSupport) << 2)
                | ((pstGnssGenericAssitDataSupportElement->bitOpUtcModelSupport) << 1)
                | (pstGnssGenericAssitDataSupportElement->bitOpAuxiliaryInformationSupport));

    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, usOption);

    /*����GNSS-ID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstGnssGenericAssitDataSupportElement->stGnssId),
                                     pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����SBAS-IDS*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpSbasIds)
    {
        usRslt = NAS_LPP_EncodeSbasId(&(pstGnssGenericAssitDataSupportElement->stSbasId), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����TimeModelListSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpGnssTimeModelListSupport)
    {
        NAS_LPP_EncodeGnssTimeModelListSupport(&(pstGnssGenericAssitDataSupportElement->stGnssTimeModelListSupport),
                                                  pusBitPos, pucEncodeOutMsg);
    }

    /*����DifferentialCorrectionsSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpGnssDifferentialCorrectionsSupport)
    {
        NAS_LPP_EncodeGnssDifferentialCorrectionsSupport(&(pstGnssGenericAssitDataSupportElement->stGnssDifferentialCorrectionsSupport),
                                                            pusBitPos, pucEncodeOutMsg);
    }

    /*����NavigationModelSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpGnssNavigationModelSupport)
    {
        usRslt = NAS_LPP_EncodeGnssNavigationModelSupport(&(pstGnssGenericAssitDataSupportElement->stGnssNavigationModelSupport),
                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����RealTimeIntegritySupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpRealTimeIntegritySupport)
    {
        NAS_LPP_EncodeRealTimeIntegritySupport(&(pstGnssGenericAssitDataSupportElement->stGnssRealTimeIntegritySupport),
                                                  pusBitPos, pucEncodeOutMsg);
    }

    /*����DataBitAssistanceSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpDataBitAssistanceSupport)
    {
        NAS_LPP_EncodeDataBitAssistanceSupport(&(pstGnssGenericAssitDataSupportElement->stGnssDataBitAssistanceSupport),
                                                  pusBitPos, pucEncodeOutMsg);
    }

    /*����AcquisitionAssistanceSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpAcquisitionAssistanceSupport)
    {
        usRslt = NAS_LPP_EncodeAcquisitionAssistanceSupport(&(pstGnssGenericAssitDataSupportElement->stGnssAcquisitionAssistanceSupport),
                                                               pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����AlmanacSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpAlmanacSupport)
    {
        usRslt = NAS_LPP_EncodeAlmanacSupport(&(pstGnssGenericAssitDataSupportElement->stGnssAlmanacSupport),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����UTC-ModelSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpUtcModelSupport)
    {
        usRslt = NAS_LPP_EncodeUTCModelSupport(&(pstGnssGenericAssitDataSupportElement->stGnssUtcModelSupport),
                                                  pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����AuxiliaryInformationSupport*/
    if(NAS_LPP_SLCT == pstGnssGenericAssitDataSupportElement->bitOpAuxiliaryInformationSupport)
    {
        NAS_LPP_EncodeAuxiliaryInformationSupport(&(pstGnssGenericAssitDataSupportElement->stGnssAuxiliaryInformationSupport),
                                                     pusBitPos, pucEncodeOutMsg);
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGNSSGenericAssistanceDataSupport
(
    LPP_GNSS_GENERIC_ASSISTANCE_DATA_SUPPORT_STRU          *pstGenericAssitDataSupport,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucGenericAssitDataSupportNum    = 0;
    VOS_UINT8                                               ucLoop                          = 0;
    VOS_UINT16                                              usReslt                         = 0;

    /*����GnssSupport��������������Լ���Ľṹ�����飬���Գ��Ȳ�����Сbit����ԭ��
      �����ֵ�������λ�õ�ֵΪ׼,��Լ���ĳ�����16-1=15����ʾ15�����Ҫ4��bit
      ��ʾ�����Ա���Ҳֻ��Ҫ��4��bit����*/
    if((1 > pstGenericAssitDataSupport->ulSupportElementNum)
        || (16 < pstGenericAssitDataSupport->ulSupportElementNum))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSGENERICASSISTANCEDATASUPPORT_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 4,
                                 (pstGenericAssitDataSupport->ulSupportElementNum) - 1);

    /*����ṹ������ľ����ԱGNSS-SupportElement*/
    ucGenericAssitDataSupportNum = (VOS_UINT8)(pstGenericAssitDataSupport->ulSupportElementNum);
    for(ucLoop = 0; ucLoop < ucGenericAssitDataSupportNum; ucLoop++)
    {
        usReslt = NAS_LPP_EncodeAGNSSIEsProvideCapGenericAssitDataSupportList(&(pstGenericAssitDataSupport->astSupportElementArray[ucLoop]),
                                                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usReslt)
        {
            return  usReslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesAssistanceDataSupportList
(
    LPP_ASSISTANCE_DATA_SUPPORT_LIST_STRU                  *pstAgnssAssitDataSupportList,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt             = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����GNSS-CommonAssistanceDataSupport*/
    usRslt = NAS_LPP_EncodeGNSSCommonAssistanceDataSupport(&(pstAgnssAssitDataSupportList->stGnssCommonAssistanceDataSupport),
                                                              pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����GNSS-CommonAssistanceDataSupport*/
    usRslt = NAS_LPP_EncodeGNSSGenericAssistanceDataSupport(&(pstAgnssAssitDataSupportList->stGnssGenericAssistanceDataSupport),
                                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationCoordinateTypes
(
    LPP_LOCATION_COORDINATE_TYPE_STRU                      *pstAgnssLocCoordinateType,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����ellipsoidPoint*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                 (VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPoint));

    /*����ellipsoidPointWithUncertaintyCircle*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithUncertaintyCircle)));

    /*����ellipsoidPointWithUncertaintyEllipse*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithUncertaintyEllipse)));

    /*����polygon*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bPolygon)));

    /*����ellipsoidPointWithAltitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithAltitude)));

    /*����ellipsoidPointWithAltitudeAndUncertaintyEllipsoid*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidPointWithAltitudeAndUncertaintyEllipsoid)));

    /*����ellipsoidArc*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocCoordinateType->bEllipsoidArc)));

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationVelocityTypes
(
    LPP_VELOCITY_TYPES_STRU                                *pstAgnssLocVelocityTypes,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����horizontalVelocity*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalVelocity)));

    /*����horizontalWithVerticalVelocity*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalWithVerticalVelocity)));

    /*����horizontalVelocityWithUncertainty*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalVelocityWithUncertainty)));

    /*����horizontalWithVerticalVelocityAndUncertainty*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 1,
                                ((VOS_UINT8)(pstAgnssLocVelocityTypes->bHorizontalWithVerticalVelocityAndUncertainty)));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAGNSSIEsProvideCapabilities
(
    LPP_AGNSS_PROVIDE_CAP_STRU                             *pstAGNSSIesProvideCap,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucOption        = 0;
    VOS_UINT16                                              usRslt          = 0;

    /*������չλ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);


    /*�����ѡ��*/
    ucOption = (VOS_UINT8)(((pstAGNSSIesProvideCap->bitOpGnssSupportList) << 3)
                | ((pstAGNSSIesProvideCap->bitOpAssistanceDataSupportList) << 2)
                | ((pstAGNSSIesProvideCap->bitOpLocationCoordinateTypes) << 1)
                | (pstAGNSSIesProvideCap->bitOpVelocityTypes));
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 4, ucOption);

    /*����GNSS-SupportList*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpGnssSupportList)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesGnssSupportList(&(pstAGNSSIesProvideCap->stGnssSupportList),
                                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����AssistanceDataSupportList*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpAssistanceDataSupportList)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesAssistanceDataSupportList(&(pstAGNSSIesProvideCap->stAssistanceDataSupportList),
                                                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����LocationCoordinateTypes*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpLocationCoordinateTypes)
    {
        NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationCoordinateTypes(&(pstAGNSSIesProvideCap->stLocationCoordinateTypes),
                                                                            pusBitPos, pucEncodeOutMsg);
    }

    /*����VelocityTypes*/
    if(NAS_LPP_SLCT == pstAGNSSIesProvideCap->bitOpVelocityTypes)
    {
        NAS_LPP_EncodeAGNSSIEsProvideCapabilitiesLocationVelocityTypes(&(pstAGNSSIesProvideCap->stVelocityTypes),
                                                                          pusBitPos, pucEncodeOutMsg);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeOTDOAMode
 Description     : ����LPP_OTDOA_MODE_STRU
 Input           : pstOTDOAIesProvideCap    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 otdoa-Mode      BIT STRING {    ue-assisted (0) } (SIZE (1..8)),

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOTDOAMode
(
    LPP_OTDOA_MODE_STRU                *pstOTDOAMode,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucLen               = 0;

    /*����bit string �ĳ���*/
    if((pstOTDOAMode->ucOTDOAModeLen < 1)||(pstOTDOAMode->ucOTDOAModeLen > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOAMODE_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    ucLen = pstOTDOAMode->ucOTDOAModeLen - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, ucLen);

    /*����bit string*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstOTDOAMode->ucOTDOAModeLen,
                              pstOTDOAMode->ucOTDOAMode);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandEUTRA
 Description     : ����LPP_SUPPORTED_BAND_EUTRA_STRU
 Input           : pstOTDOAIesProvideCap    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 SupportedBandEUTRA ::= SEQUENCE {
        bandEUTRA                           INTEGER (1..maxFBI)
    }

    maxFBI                          INTEGER::=64-- Maximum value of frequency band indicator

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandEUTRA
(
    LPP_SUPPORTED_BAND_EUTRA_STRU      *pstSupBandEUTRA,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT32  ucCount ;
    if((pstSupBandEUTRA->ulBandEutra < 1)||(pstSupBandEUTRA->ulBandEutra > 64))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDEUTRA_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    ucCount = pstSupBandEUTRA->ulBandEutra - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)ucCount);
    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandListEUTRA
 Description     : ����LPP_SUPPORTED_BAND_LIST_EUTRA_STRU
 Input           : pstOTDOAIesProvideCap    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 supportedBandListEUTRA      SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandListEUTRA
(
    LPP_SUPPORTED_BAND_LIST_EUTRA_STRU *pstSupBandListEUTRA,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          ulReturnReslt;
    VOS_UINT32                          ucCount ;
    VOS_UINT32                          ucTotalLen          = 0;
    VOS_UINT32                          ulByteCount         = 0;
    VOS_UINT32                          ulTempLen           = 0;

    /*���sequence of �ĳ���*/
    if((pstSupBandListEUTRA->ulSupportBandNum < 1)||(pstSupBandListEUTRA->ulSupportBandNum > 64))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDLISTEUTRA_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    /*����Ϊ��չ���Ҫ����L+VȻ�����L��V����Ҫ���м���,�����ӵ�6��Lռ��bit��*/
    ucTotalLen = 6 * (pstSupBandListEUTRA->ulSupportBandNum) + 6;
    if((ucTotalLen %8) == 0)
    {
        ulByteCount = ucTotalLen / 8 ;
        ulTempLen = 0;
    }
    else
    {
        ulByteCount = (ucTotalLen/8) +1;
        ulTempLen = 8 - (ucTotalLen % 8);
    }
    /*����L + V�ֶ�*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulByteCount);

    ucCount = pstSupBandListEUTRA->ulSupportBandNum - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)ucCount);

    /*ѭ������SEQUENCE*/
    for(ucCount = 0; ucCount < pstSupBandListEUTRA->ulSupportBandNum; ucCount++)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandEUTRA(&(pstSupBandListEUTRA->astSupportedBandArray[ucCount]),
                                                      pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*���뵽�ֽ�*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)ulTempLen, 0);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandEUTRAV9A0
 Description     : ����LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU
 Input           : pstOTDOAIesProvideCap    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
     SupportedBandEUTRA-v9a0 ::=     SEQUENCE {
        bandEUTRA-v9a0                      INTEGER (maxFBI-Plus1..maxFBI2)     OPTIONAL
    }

    maxFBI-Plus1                        INTEGER ::= 65  -- lowest value extended FBI range
    maxFBI2                             INTEGER ::= 256 -- highest value extended FBI range

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandEUTRAV9A0
(
    LPP_SUPPORTED_BAND_EUTRA_V9A0_STRU *pstSupBandEUTRAV9A0,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount             = 0;
    if((pstSupBandEUTRAV9A0->ulBandEutraV9A0 < 65)||(pstSupBandEUTRAV9A0->ulBandEutraV9A0 > 256))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDEUTRAV9A0_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*����һ����չ��־λ*/
    if(NAS_LPP_SLCT == pstSupBandEUTRAV9A0->bitOpBandEutraV9A0)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
        ucCount = (VOS_UINT8)(pstSupBandEUTRAV9A0->ulBandEutraV9A0 - 65);
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, ucCount);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeSupBandListEUTRAV9A0
 Description     : ����LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU
 Input           : pstOTDOAIesProvideCap    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 supportedBandListEUTRA-v9a0 SEQUENCE (SIZE (1..maxBands)) OF SupportedBandEUTRA-v9a0

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSupBandListEUTRAV9A0
(
    LPP_SUPPORTED_BAND_LIST_EUTRA_V9A0_STRU                *pstSupBandListEUTRAV9a0,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              ulReturnReslt   = 0;
    VOS_UINT32                                              ucCount         = 0;
    VOS_UINT32                                              ucTotalLen      = 0;
    VOS_UINT32                                              ulByteCount     = 0;
    VOS_UINT32                                              ulTempLen       = 0;

    /*���sequence of �ĳ���*/
    if((pstSupBandListEUTRAV9a0->ulSupportBandNum < 1)||(pstSupBandListEUTRAV9a0->ulSupportBandNum > LPP_MAX_SUPPORTED_BAND_EUTRA_NUM))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SUPBANDLISTEUTRAV9A0_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;

    }

    /*����Ϊ��չ���Ҫ����L+VȻ�����L��V����Ҫ���м���,�п�ѡ���ռ�þŸ�bit��û�е�ռ��һ��bit��L������Ҫ6��bit*/
    ucTotalLen = 0;
    for(ucCount = 0; ucCount < pstSupBandListEUTRAV9a0->ulSupportBandNum;ucCount++)
    {
        if(NAS_LPP_SLCT == pstSupBandListEUTRAV9a0->astSupportedBandArray[ucCount].bitOpBandEutraV9A0)
        {
            ucTotalLen += 9;
        }
        else
        {
            ucTotalLen +=1;
        }
    }
    ucTotalLen += 6;
    if((ucTotalLen % 8) == 0)
    {
        ulByteCount = ucTotalLen / 8;
        ulTempLen = 0;
    }
    else
    {
        ulByteCount = (ucTotalLen / 8 ) + 1;
        ulTempLen = 8 - ( ucTotalLen % 8);
    }
    /*����L + V�ֶ�*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulByteCount);

    /*����L�ֶ�*/
    ucCount = pstSupBandListEUTRAV9a0->ulSupportBandNum - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)ucCount);

    /*ѭ������SEQUENCE*/
    for(ucCount = 0; ucCount < pstSupBandListEUTRAV9a0->ulSupportBandNum;ucCount++)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandEUTRAV9A0(&(pstSupBandListEUTRAV9a0->astSupportedBandArray[ucCount]),
                                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }
    /*���뵽�ֽ�*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)ulTempLen, 0);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeFreqRSTDMeasurementR10
 Description     : ����LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_ENUM_UINT32
 Input           : pstOTDOAIesProvideCap    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 interFreqRSTDmeasurement-r10        ENUMERATED { supported }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeFreqRSTDMeasurementR10
(
    LPP_INTER_FREQ_RSTD_MEASUREMENT_R10_ENUM_UINT32        *pstFreqRSTDMeasurementR10,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*����ö��ֵ��û����չ���ֱ�ӱ�ֵ���ɣ�ֻ��һ��ö����*/
    /*��չ���е�ö�٣���Ҫ����L + V��Ȼ�����ö��ֵ�����0�����ֽ�*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 1);
    if(*pstFreqRSTDMeasurementR10 > 0)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_FREQRSTDMEASUREMENTR10_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAdNeighbourCellInfoListR10
 Description     : ����LPP_ADDITIONAL_NEIGH_CELL_INFO_LIST_R10_ENUM_UINT32
 Input           : pstOTDOAIesProvideCap    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 additionalNeighbourCellInfoList-r10 ENUMERATED { supported }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAdNeighbourCellInfoListR10
(
    LPP_ADDITIONAL_NEIGH_CELL_INFO_LIST_R10_ENUM_UINT32    *pstAdNeighbourCellInfoListR10,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*����ö��ֵ��û����չ���ֱ�ӱ�ֵ���ɣ�ֻ��һ��ö����*/

    /*��չ���е�ö�٣���Ҫ����L + V��Ȼ�����ö��ֵ�����0�����ֽ�*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 1);
    if(*pstAdNeighbourCellInfoListR10 > 0)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ADNEIGHBOURCELLINFOLISTR10_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, 0);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeOTDOAIEsProvideCapabilities
(
    LPP_OTDOA_PROVIDE_CAP_STRU                             *pstOTDOAIesProvideCap,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              ulReturnReslt;
    VOS_UINT8                                               ucExtObjectCount    = 0;

    /*������չ��,�ش��ڵ�,�����չ���б�ѡ����Ϊ1*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpOtdoaProvideCapExt)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*����OTDOA-Mode*/
    ulReturnReslt = NAS_LPP_EncodeOTDOAMode(&(pstOTDOAIesProvideCap->stOtdoaMode),
                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
    {
        return  ulReturnReslt;
    }

    if(NAS_LPP_NO_SLCT == pstOTDOAIesProvideCap->bitOpOtdoaProvideCapExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*������չ��bit-map�������L-1*/
    ucExtObjectCount = 3;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, ucExtObjectCount);

    /*������չ���־λbitOpSupportedBandListEutra*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutra)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*������չ���־λbitOpSupportedBandListEutraV9A0*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutraV9A0)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*������չ���־λbitOpInterFreqRSTDmeasurementR10*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpInterFreqRSTDmeasurementR10)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*������չ���־λbitOpAdditionalNeighbourCellInfoListR10*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpAdditionalNeighbourCellInfoListR10)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*�����չ�ѡ�У�������չ��*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutra)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandListEUTRA(&(pstOTDOAIesProvideCap->stSupportedBandListEutra),
                                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*�����չ�ѡ�У�������չ��*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpSupportedBandListEutraV9A0)
    {
        ulReturnReslt = NAS_LPP_EncodeSupBandListEUTRAV9A0(&(pstOTDOAIesProvideCap->stSupportedBandListEutraV9A0),
                                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*�����չ�ѡ�У�������չ��*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpInterFreqRSTDmeasurementR10)
    {
        ulReturnReslt = NAS_LPP_EncodeFreqRSTDMeasurementR10(&(pstOTDOAIesProvideCap->enInterFreqRSTDmeasurementR10),
                                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    /*�����չ�ѡ�У�������չ��*/
    if(NAS_LPP_SLCT == pstOTDOAIesProvideCap->bitOpAdditionalNeighbourCellInfoListR10)
    {
        ulReturnReslt = NAS_LPP_EncodeAdNeighbourCellInfoListR10(&(pstOTDOAIesProvideCap->enAdditionalNeighbourCellInfoListR10),
                                                                    pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != ulReturnReslt)
        {
            return  ulReturnReslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   : NAS_LPP_EncodeECIDMeasSupported
 Description     : ����LPP_ECID_MEAS_SUPPORTED_STRU
 Input           : pstEPDUIesProvideCap     ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 ecid-MeasSupported  BIT STRING {    rsrpSup     (0),
                                                  rsrqSup     (1),
                                                  ueRxTxSup   (2) } (SIZE(1..8))

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeECIDMeasSupported
(
    LPP_ECID_MEAS_SUPPORTED_STRU                           *pstECIDMeasSupported,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucCount         = 0;

    /*�жϳ��ȵĺϷ���*/
    if((pstECIDMeasSupported->ucEcidMeasSupCnt <1)||(pstECIDMeasSupported->ucEcidMeasSupCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECIDMEASSUPPORTED_ERROR,
                                 NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }

    /*���볤��*/
    ucCount = pstECIDMeasSupported->ucEcidMeasSupCnt - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3, ucCount);

    /*����BIT STRING*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, pstECIDMeasSupported->ucEcidMeasSupCnt,
                               pstECIDMeasSupported->ucEcidMeasSup);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeECIDIEsProvideCapabilities
 Description     : ����ECIDIesProvideCap
 Input           : pstECIDIesProvideCap     ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
         ECID-ProvideCapabilities ::= SEQUENCE {
             ecid-MeasSupported  BIT STRING {    rsrpSup     (0),
                                                 rsrqSup     (1),
                                                 ueRxTxSup   (2) } (SIZE(1..8)),
             ...
         }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng 00324863      2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeECIDIEsProvideCapabilities
(
    LPP_ECID_PROVIDE_CAP_STRU                              *pstECIDIesProvideCap,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16  usReturnReslt;

    /*������չ���־λ��û����չ��ֱ��Ϊ0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);


    /*����ṹ������*/
    usReturnReslt = NAS_LPP_EncodeECIDMeasSupported(&(pstECIDIesProvideCap->stEcidMeasSupported),
                                                       pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return      usReturnReslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeEPDUIEsProvideCapabilities
 Description     : ����EPDUIesProvideCap
 Input           : pstEPDUIesProvideCap     ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
                 EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

                 maxEPDU INTEGER ::= 16

                 EPDU ::= SEQUENCE {
                     ePDU-Identifier         EPDU-Identifier,
                     ePDU-Body               EPDU-Body
                 }

                 EPDU-Identifier ::= SEQUENCE {
                     ePDU-ID                 EPDU-ID,
                     ePDU-Name               EPDU-Name       OPTIONAL,
                     ...
                 }

                 EPDU-ID ::= INTEGER (1..256)

                 EPDU-Name ::= VisibleString (SIZE (1..32))

                 EPDU-Body ::= OCTET STRING

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-18  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEPDUIEsProvideCapabilities
(
    LPP_EPDU_SEQUENCE_STRU             *pstEPDUIesProvideCap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt;

    /*���ù������뺯��*/
    usReturnReslt = NAS_LPP_EncodeEPDUSequence(pstEPDUIesProvideCap, pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
    {
        return      usReturnReslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeProvideCapaBilityR9IEs
(
    LPP_PROVIDE_CAPABILITIES_R9_IES_STRU                   *pstProvideCapR9Ies,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucOption    = 0;
    VOS_UINT16                                              usRslt      = 0;

    /*������չλ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    ucOption = (VOS_UINT8)(((pstProvideCapR9Ies->bitOpCommonIEsProvideCapabilities) << 4)
                | ((pstProvideCapR9Ies->bitOpAGNSSProvideCapabilities) << 3)
                | ((pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities) << 2)
                | ((pstProvideCapR9Ies->bitOpECIDProvideCapabilities) << 1)
                | (pstProvideCapR9Ies->bitOpEPDUProvideCapabilities));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5, ucOption);

    /*����CommonIEsProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpCommonIEsProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeCommonIEsProvideCapabilities(&(pstProvideCapR9Ies->stCommonIEsProvideCapabilities),
                                                               pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����A-GNSS-ProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpAGNSSProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeAGNSSIEsProvideCapabilities(&(pstProvideCapR9Ies->stAGNSSProvideCapabilities),
                                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����OTDOA-ProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpOTDOAProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeOTDOAIEsProvideCapabilities(&(pstProvideCapR9Ies->stOTDOAProvideCapabilities),
                                                              pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    /*����ECID-ProvideCapabilities*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpECIDProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeECIDIEsProvideCapabilities(&(pstProvideCapR9Ies->stECIDProvideCapabilities),
                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    /*����EPDU-Sequence*/
    if(NAS_LPP_SLCT == pstProvideCapR9Ies->bitOpEPDUProvideCapabilities)
    {
        usRslt = NAS_LPP_EncodeEPDUIEsProvideCapabilities(&(pstProvideCapR9Ies->stEPDURequestCapabilities),
                                                             pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeProvideCapaBilityC1
(
    LPP_CRITI_EXT_PROVIDE_CAPABILITIES_STRU                *pstExtProvideCapability,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    /*����choice��*/
    if(pstExtProvideCapability->ulChoice > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PROVIDECAPABILITYC1_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*4��choice�������2��bit��ʾ����*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstExtProvideCapability->ulChoice));

    switch(pstExtProvideCapability->ulChoice)
    {
        case LPP_PROVIDE_CAPABILITIES_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideCapaBilityR9IEs(&(pstExtProvideCapability->u.stProvideCapabilitiesR9),
                                                             pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeProvideCapability
(
    LPP_MESSAGE_PROVIDE_CAPABILITIES_STRU                  *pstProvideCapabilty,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    /*����choice��*/
    if(pstProvideCapabilty->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PROVIDECAPABILITY_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*����choice�������һ��bit��ʾ����*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstProvideCapabilty->ulChoice));

    switch(pstProvideCapabilty->ulChoice)
    {
        case LPP_C1_CRITI_EXT_PROVIDE_CAPABILITIES_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideCapaBilityC1(&(pstProvideCapabilty->u.stC1),
                                                          pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;


        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeEpduReqAssistData
 Description     : ����LPP_EPDU_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 EPDU-Sequence ::= SEQUENCE (SIZE (1..maxEPDU)) OF EPDU

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEpduReqAssistData
(
    LPP_EPDU_REQ_ASSIST_DATA_STRU                          *pstEpduReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence(&(pstEpduReqAssistData->astReqAssistDataEpduSeq),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return      usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeOTDOAReqAssistData
 Description     : ����LPP_OTDOA_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 OTDOA-RequestAssistanceData ::= SEQUENCE {
         physCellId      INTEGER (0..503),
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOTDOAReqAssistData
(
    LPP_OTDOA_REQ_ASSIST_DATA_STRU                         *pstOTDOAReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    if(pstOTDOAReqAssistData->usPhyCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOAREQASSISTDATA_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*����ṹ������*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg, pusBitPos, 9, pstOTDOAReqAssistData->usPhyCellId);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssRefTimeReq
 Description     : ����LPP_GNSS_REFERENCE_TIME_REQ_STRU
 Input           :
 Asn             :
 GNSS-ReferenceTimeReq ::= SEQUENCE {
         gnss-TimeReqPrefList    SEQUENCE (SIZE (1..8)) OF GNSS-ID,
         gps-TOW-assistReq       BOOLEAN                             OPTIONAL, -- Cond gps
         notOfLeapSecReq         BOOLEAN                             OPTIONAL, -- Cond glonass
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssRefTimeReq
(
    LPP_GNSS_REFERENCE_TIME_REQ_STRU                       *pstGnssRefTimeReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16          usRslt = 0;
    VOS_UINT8           ucCount = 0;

    if((pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt < 1)||(pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSREFTIMEREQ_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����OPTIONAL���־λ*/
    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpGpsTowAssistReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpGpsTowAssistReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }


    /*����ṹ������*/

    /*����GNSSID-SEQUENCE OF*/
    ucCount = (VOS_UINT8)(pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 3, ucCount);
    /*ѭ������GNSSID��������*/
    for(ucCount = 0;ucCount < pstGnssRefTimeReq->ulGNSSTimeReqPrefListCnt;ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssId(&(pstGnssRefTimeReq->astGNSSTimeReqPrefListArray[ucCount]),
                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    /*����gps-TOW-assistReq*/
    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpGpsTowAssistReq)
    {
        if(TRUE == pstGnssRefTimeReq->bGpsTowAssistReq)
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
        }
    }

    /*����notofLeapSecReq*/
    if(NAS_LPP_SLCT == pstGnssRefTimeReq->bitOpNotOfLeapSecReq)
    {
        if(TRUE == pstGnssRefTimeReq->bNotOFLeapSecReq)
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
        }
    }



    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssRefLocatReq
 Description     : ����LPP_GNSS_REFERENCE_LOCATION_REQ_STRU
 Input           :
 Asn             :

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssRefLocatReq
(
    LPP_GNSS_REFERENCE_LOCATION_REQ_STRU                   *pstGnssRefLocatReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*�ṹ������Ϊ�գ�ֻ������չλ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssIonoModelReq
 Description     : ����LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU
 Input           :
 Asn             :
 GNSS-IonosphericModelReq ::=    SEQUENCE {
         klobucharModelReq       BIT STRING (SIZE(2))    OPTIONAL,   -- Cond klobuchar
         neQuickModelReq         NULL                    OPTIONAL,   -- Cond nequick
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssIonoModelReq
(
    LPP_GNSS_IONOSPHERIC_MODEL_REQ_STRU                    *pstGnssIonoModelReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg)
{
    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����OPTIONAL���־λ*/
    if(NAS_LPP_SLCT == pstGnssIonoModelReq->bitOpKlobucharModelReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }
    if(NAS_LPP_SLCT == pstGnssIonoModelReq->bitOpNeQuickModelReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*����ṹ������*/
    /*����BIT STRING*/
    if(NAS_LPP_SLCT == pstGnssIonoModelReq->bitOpKlobucharModelReq)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                                 (pstGnssIonoModelReq->ucKlobucharModelReq));
    }
    /*�ڶ���ΪNULL���ͣ�����Ҫ����*/

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssOrientParamReq
 Description     : ����LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU
 Input           :
 Asn             :
 GNSS-EarthOrientationParametersReq ::= SEQUENCE {
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssEarthOrientParamReq
(
    LPP_GNSS_EARTH_ORIENTATION_PARAMETERS_REQ_STRU         *pstGnssOrientParamReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��־λ���ṹ������Ϊ��*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeComReqAssistData
 Description     : ����LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU
 Input           :
 Asn             :
 GNSS-CommonAssistDataReq ::= SEQUENCE {
        gnss-ReferenceTimeReq               GNSS-ReferenceTimeReq
                                                                    OPTIONAL, -- Cond RefTimeReq
        gnss-ReferenceLocationReq           GNSS-ReferenceLocationReq
                                                                    OPTIONAL, -- Cond RefLocReq
        gnss-IonosphericModelReq            GNSS-IonosphericModelReq
                                                                    OPTIONAL, -- Cond IonoModReq
        gnss-EarthOrientationParametersReq  GNSS-EarthOrientationParametersReq
                                                                    OPTIONAL, -- Cond EOPReq
        ...
    }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssComReqAssistData
(
    LPP_GNSS_COMMON_ASSIST_DATA_REQ_STRU                   *pstComReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����OPTIONAL���־λ*/
    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefTimeReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefLocationReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSIonoModelReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSEarthOriParaReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*����OPTIONAL��ṹ����*/
    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefTimeReq)
    {
        usRslt = NAS_LPP_EncodeGnssRefTimeReq(&(pstComReqAssistData->stGNSSReferenceTimeReq),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSRefLocationReq)
    {
        usRslt = NAS_LPP_EncodeGnssRefLocatReq(&(pstComReqAssistData->stGNSSReferenceLocationReq),
                                                  pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSIonoModelReq)
    {
        usRslt = NAS_LPP_EncodeGnssIonoModelReq(&(pstComReqAssistData->stIonosphericModelReq),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if(NAS_LPP_SLCT == pstComReqAssistData->bitOpGNSSEarthOriParaReq)
    {
        usRslt = NAS_LPP_EncodeGnssEarthOrientParamReq(&(pstComReqAssistData->stEarthOrientationParametersReq),
                                                          pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssTimeModelElementReq
 Description     : ����LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU
 Input           :
 Asn             :
 GNSS-TimeModelElementReq ::= SEQUENCE {
        gnss-TO-IDsReq  INTEGER (1..15),
        deltaTreq       BOOLEAN,
        ...
    }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssTimeModelElementReq
(
    LPP_GNSS_TIME_MODEL_ELEMENT_REQ_STRU                   *pstGnssTimeModelElementReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucValue         = 0;

    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ṹ������*/
    if((pstGnssTimeModelElementReq->ucGNSSToIdsReq > 15)||(pstGnssTimeModelElementReq->ucGNSSToIdsReq < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTIMEMODELELEMENTREQ_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    ucValue = pstGnssTimeModelElementReq->ucGNSSToIdsReq - 1;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, ucValue);

    if(TRUE == pstGnssTimeModelElementReq->bdeltaTreq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }


    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssTimeModelListReq
 Description     : ����LPP_GNSS_TIME_MODEL_LIST_REQ_STRU
 Input           :
 Asn             :
 GNSS-TimeModelListReq ::= SEQUENCE (SIZE(1..15)) OF GNSS-TimeModelElementReq

     GNSS-TimeModelElementReq ::= SEQUENCE {
         gnss-TO-IDsReq  INTEGER (1..15),
         deltaTreq       BOOLEAN,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssTimeModelListReq
(
    LPP_GNSS_TIME_MODEL_LIST_REQ_STRU                      *pstGnssTimeModelListReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    VOS_UINT8                                               ucCount         = 0;
    /*�Ϸ��Լ��*/
    if((pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt > 15)||(pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSTIMEMODELLISTREQ_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*���볤��ֵ*/
    ucCount = (VOS_UINT8)(pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, ucCount);

    /*ѭ������ṹ��*/
    for(ucCount = 0;ucCount < pstGnssTimeModelListReq->ulGNSSTimeModelListReqCnt;ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssTimeModelElementReq(&(pstGnssTimeModelListReq->astGNSSTimeModelListElementReq[ucCount]),
                                                          pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDiffCorrectReq
 Description     : ����LPP_GNSS_DIFF_CORRECT_REQ_STRU
 Input           :
 Asn             :
 GNSS-DifferentialCorrectionsReq ::=     SEQUENCE {
         dgnss-SignalsReq            GNSS-SignalIDs,
         dgnss-ValidityTimeReq       BOOLEAN,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDiffCorrectReq
(
    LPP_GNSS_DIFF_CORRECT_REQ_STRU                         *pstGnssDiffCorrectReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ṹ������*/
    NAS_LPP_EncodeGnssSignalIds(&(pstGnssDiffCorrectReq->stDGNSSSignalReq),  pusBitPos,  pucEncodeOutMsg);

    if(TRUE == pstGnssDiffCorrectReq->bDGNSSValidityTimeReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,  1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,  0);
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeSVID
 Description     : ����LPP_SV_ID_STRU
 Input           :
 Asn             :
 SV-ID ::= SEQUENCE {
        satellite-id        INTEGER(0..63),
        ...
    }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSVID
(
    LPP_SV_ID_STRU                                         *pstSVID,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8           ucValue = 0;

    if(pstSVID->ucSatelliteId > 63)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SVID_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ṹ������*/
    ucValue = pstSVID->ucSatelliteId;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 6, ucValue);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeSatListRelatedDataListElement
 Description     : ����LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU
 Input           :
 Asn             :
 SatListRelatedDataElement ::= SEQUENCE {
         svID                SV-ID,
         iod                 BIT STRING (SIZE(11)),
         clockModelID        INTEGER (1..8)          OPTIONAL,
         orbitModelID        INTEGER (1..8)          OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSatListRelatedDataListElement
(
    LPP_SATLIST_RELATED_DATALIST_ELEMENT_STRU              *pstSatListRelatedDataListElement,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    VOS_UINT8                                               ucValue         = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����OPTIONAL��־λ*/
    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpClockModelId)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }


    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpOrbitModelId)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*����SV-ID*/
    usRslt = NAS_LPP_EncodeSVID(&(pstSatListRelatedDataListElement->stSvId),
                                   pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*iod*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos, 11, pstSatListRelatedDataListElement->usIod);

    /*����clockModelID*/
    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpClockModelId)
    {
        if((pstSatListRelatedDataListElement->ucClockModelId > 8)||(pstSatListRelatedDataListElement->ucClockModelId < 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_SATLISTRELATEDDATALISTELEMENT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        ucValue = pstSatListRelatedDataListElement->ucClockModelId - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }
    /*����orbitModelID*/
    if(NAS_LPP_SLCT == pstSatListRelatedDataListElement->bitOpOrbitModelId)
    {
        if((pstSatListRelatedDataListElement->ucOrbitModelId> 8)||(pstSatListRelatedDataListElement->ucOrbitModelId< 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_SATLISTRELATEDDATALISTELEMENT_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        ucValue = pstSatListRelatedDataListElement->ucOrbitModelId - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeSatlistRelatedDataList
 Description     : ����LPP_SATLIST_RELATED_DATALIST_STRU
 Input           :
 Asn             :
 SatListRelatedDataList ::= SEQUENCE (SIZE (1..64)) OF SatListRelatedDataElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeSatlistRelatedDataList
(
    LPP_SATLIST_RELATED_DATALIST_STRU                      *pstSatlistRelatedDataList,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucCount         = 0;
    VOS_UINT16                                              usRslt          = 0;
    /*����SEQUENCE OF ��ֵ*/
    if((pstSatlistRelatedDataList->ulSatListRelatedDataListCnt < 1)||(pstSatlistRelatedDataList->ulSatListRelatedDataListCnt > 64))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_SATLISTRELATEDDATALIST_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    ucCount = (VOS_UINT8)(pstSatlistRelatedDataList->ulSatListRelatedDataListCnt - 1);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 6,  ucCount);

    for(ucCount = 0; ucCount < (pstSatlistRelatedDataList->ulSatListRelatedDataListCnt);ucCount++)
    {
        usRslt = NAS_LPP_EncodeSatListRelatedDataListElement(&(pstSatlistRelatedDataList->astSatListRelatedDataListElementArray[ucCount]),
                                                                pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeStoreNavListInfo
 Description     : ����LPP_STORED_NAVLIST_STRU
 Input           :
 Asn             :
 StoredNavListInfo ::= SEQUENCE {
         gnss-WeekOrDay          INTEGER (0..4095),
         gnss-Toe                INTEGER (0..255),
         t-toeLimit              INTEGER (0..15),
         satListRelatedDataList  SatListRelatedDataList  OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeStoreNavListInfo
(
    LPP_STORED_NAVLIST_STRU                                *pstStoreNavListInfo,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16          usRslt = 0;

    /*������չ���־λ*/
    if((pstStoreNavListInfo->ucGNSSTToeLimit > 15) || (pstStoreNavListInfo->usGNSSWeekOrDay > 4095))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_STORENAVLISTINFO_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
    /*����OPTIONAL��־λ*/
    if(NAS_LPP_SLCT == pstStoreNavListInfo->bitOpSatListREalatedDataList)
    {
        NAS_LPP_EncodeBitsLess8(  pucEncodeOutMsg,  pusBitPos,  1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(  pucEncodeOutMsg,  pusBitPos,  1, 0);
    }

    /*����12��bit-gnss-WeekOrDay*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg, pusBitPos, 12, pstStoreNavListInfo->usGNSSWeekOrDay);

    /*����gnss-Toe*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,  pstStoreNavListInfo->ucGNSSToe);

    /*t-toeLimit*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, pstStoreNavListInfo->ucGNSSTToeLimit);

    /*����satListRelatedDataList*/
    if(NAS_LPP_SLCT == pstStoreNavListInfo->bitOpSatListREalatedDataList)
    {
        usRslt = NAS_LPP_EncodeSatlistRelatedDataList(&(pstStoreNavListInfo->stSatlistRelatedDataList),
                                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeOrbitModelID
 Description     : ����LPP_Orbit_MODEL_ID_STRU
 Input           :
 Asn             :
 orbitModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeOrbitModelID
(
    LPP_ORBIT_MODEL_ID_STRU            *pstOrbitModelID,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount         = 0;
    VOS_UINT8                           ucValue         = 0;

    /*��֤���Ⱥ�ֵ�ĺϷ���*/
    if((pstOrbitModelID->ucOrbitModelIDCount > 8)||(pstOrbitModelID->ucOrbitModelIDCount < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ORBITMODELID_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    for(ucCount = 0;ucCount < pstOrbitModelID->ucOrbitModelIDCount;ucCount++)
    {
        if((pstOrbitModelID->ucOrbitModelIDList[ucCount] > 8)||(pstOrbitModelID->ucOrbitModelIDList[ucCount] < 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_ORBITMODELID_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*���볤��ֵ*/
    ucValue = pstOrbitModelID->ucOrbitModelIDCount - 1;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);

    /*����ֵ*/
    for(ucCount = 0;ucCount < pstOrbitModelID->ucOrbitModelIDCount;ucCount++)
    {
        ucValue = pstOrbitModelID->ucOrbitModelIDList[ucCount] - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeClockModelID
 Description     : ����LPP_CLOCK_MODEL_ID_STRU
 Input           :
 Asn             :
 clockModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeClockModelID
(
    LPP_CLOCK_MODEL_ID_STRU            *pstClockModelID,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount             = 0;
    VOS_UINT8                           ucValue             = 0;

    /*��֤���Ⱥ�ֵ�ĺϷ���*/
    if((pstClockModelID->ucClockModelIDCount > 8)||(pstClockModelID->ucClockModelIDCount < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_CLOCKMODELID_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    for(ucCount = 0;ucCount < pstClockModelID->ucClockModelIDCount;ucCount++)
    {
        if((pstClockModelID->ucClockModelIDList[ucCount] > 8)||(pstClockModelID->ucClockModelIDList[ucCount] < 1))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_CLOCKMODELID_ERROR,
                                     NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
    }

    /*���볤��ֵ*/
    ucValue = pstClockModelID->ucClockModelIDCount - 1;
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);

    /*����ֵ*/
    for(ucCount = 0;ucCount < pstClockModelID->ucClockModelIDCount;ucCount++)
    {
        ucValue = pstClockModelID->ucClockModelIDList[ucCount] - 1;
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, ucValue);
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeReqNavListInfo
 Description     : ����LPP_REQ_NAVLIST_STRU
 Input           :
 Asn             :
 ReqNavListInfo ::=  SEQUENCE {
         svReqList               BIT STRING (SIZE (64)),
         clockModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)      OPTIONAL,
         orbitModelID-PrefList   SEQUENCE (SIZE (1..8)) OF   INTEGER (1..8)      OPTIONAL,
         addNavparamReq          BOOLEAN             OPTIONAL,   -- Cond orbitModelID-2
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeReqNavListInfo
(
    LPP_REQ_NAVLIST_STRU               *pstReqNavListInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt             = 0;
    VOS_UINT8                           ucCount            = 0;
    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����OPTIONAL���־λ*/
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpClockModelIDPrefList)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpOrbitModelIDPrefList)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpAddNavparamReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*����ṹ������*/
    /*svReqList��64��bit*/
    for(ucCount = 0; ucCount < 8;ucCount++)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 8, pstReqNavListInfo->aucSvReqList[ucCount]);
    }
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpClockModelIDPrefList)
    {
        usRslt = NAS_LPP_EncodeClockModelID( &(pstReqNavListInfo->stClockModelID),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpOrbitModelIDPrefList)
    {
        usRslt = NAS_LPP_EncodeOrbitModelID( &(pstReqNavListInfo->stOrbitModelID),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstReqNavListInfo->bitOpAddNavparamReq)
    {
        if(TRUE == pstReqNavListInfo->bAddNavparamReq)
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
        }
        else
        {
            NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssNavModelReq
 Description     : ����LPP_GNSS_NAVIGATION_MODEL_REQ_STRU
 Input           :
 Asn             :
 GNSS-NavigationModelReq ::=     CHOICE {
         storedNavList       StoredNavListInfo,
         reqNavList          ReqNavListInfo,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssNavModelReq
(
    LPP_GNSS_NAVIGATION_MODEL_REQ_STRU *pstGnssNavModelReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*����ṹ����չ���־λ*/
    if(pstGnssNavModelReq->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSNAVMODELREQ_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ṹ������*/
    /*����CHOICE�����*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstGnssNavModelReq->ulChoice));
    switch(pstGnssNavModelReq->ulChoice)
    {
        case LPP_STORED_NAVLIST_CHOSEN:
            usRslt = NAS_LPP_EncodeStoreNavListInfo(&(pstGnssNavModelReq->u.stStoredNavList),
                                                       pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeReqNavListInfo(&(pstGnssNavModelReq->u.stReqNavList),
                                                     pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDataBitReqSatElement
 Description     : ����LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU
 Input           :
 Asn             :
 GNSS-DataBitsReqSatElement ::= SEQUENCE {
         svID                SV-ID,s
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDataBitReqSatElement
(
    LPP_GNSS_DATA_BIT_REQ_SAT_ELEMENT_STRU                 *pstGnssDataBitReqSatElement,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16          usRslt = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ṹ������*/
    usRslt = NAS_LPP_EncodeSVID(&(pstGnssDataBitReqSatElement->stSvId),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDataBitReqSatList
 Description     : ����LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU
 Input           :
 Asn             :
 GNSS-DataBitsReqSatList ::= SEQUENCE (SIZE(1..64)) OF GNSS-DataBitsReqSatElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDataBitReqSatList
(
    LPP_GNSS_DATA_BIT_REQ_SAT_LIST_STRU                    *pstGnssDataBitReqSatList,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT8                                               ucCount     = 0;
    VOS_UINT16                                              usRslt      = 0;

    /* ���鳤�ȺϷ��ԣ������볤��ֵ*/
    if((pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt >64)||(pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSDATABITREQSATLIST_ERROR,
                                 NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    ucCount = (VOS_UINT8)(pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 6, ucCount);

    /*����ṹ������*/
    for(ucCount = 0;ucCount <pstGnssDataBitReqSatList->ulGNSSDataBitsReqListCnt; ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssDataBitReqSatElement(&(pstGnssDataBitReqSatList->astGNSSDataBitReqSatList[ucCount]),
                                                           pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssRealTimeIntReq
 Description     : ����LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU
 Input           :
 Asn             :
 Э��Ϊ��

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssRealTimeIntReq
(
    LPP_GNSS_REALTIME_INTERGRITY_REQ_STRU                  *pstGnssRealTimeIntReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssDataBitAssistReq
 Description     : ����LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU
 Input           :
 Asn             :
 GNSS-DataBitAssistanceReq ::=   SEQUENCE {
         gnss-TOD-Req        INTEGER (0..3599),
         gnss-TOD-FracReq    INTEGER (0..999)        OPTIONAL,
         dataBitInterval     INTEGER (0..15),
         gnss-SignalType     GNSS-SignalIDs,
         gnss-DataBitsReq    GNSS-DataBitsReqSatList OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-22  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssDataBitAssistReq
(
    LPP_GNSS_DATA_BIT_ASSIST_REQ_STRU                      *pstGnssDataBitAssistReq,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt      = 0;

    if((pstGnssDataBitAssistReq->ulGNSSTodReq > 3599) ||(pstGnssDataBitAssistReq->usGNSSTodFracReq > 999)||(pstGnssDataBitAssistReq->usDataBitInterval > 15))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSDATABITASSISTREQ_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);


    /*����OPTIONAL���־λ*/
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSTodFracREq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSDataBitsReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*����ṹ������*/
    /*GNSS-tod-req*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos, 12, pstGnssDataBitAssistReq->ulGNSSTodReq);

    /*GNSS-TOD-FRACrEQ*/
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSTodFracREq)
    {
        NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos, 10, pstGnssDataBitAssistReq->usGNSSTodFracReq);
    }

    /*dataBitInterval*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, (VOS_UINT8)(pstGnssDataBitAssistReq->usDataBitInterval));

    /*gnss-SignalType*/
    NAS_LPP_EncodeGnssSignalIds( &(pstGnssDataBitAssistReq->stGNSSSignalType), pusBitPos, pucEncodeOutMsg);

    /*gnss-DataBitsReq*/
    if(NAS_LPP_SLCT == pstGnssDataBitAssistReq->bitOpGNSSDataBitsReq)
    {
        usRslt = NAS_LPP_EncodeGnssDataBitReqSatList(&(pstGnssDataBitAssistReq->stGNSSDataBitsReqSatList),
                                                        pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssSignalID
 Description     : ����LPP_GNSS_SIGNAL_ID_STRU
 Input           :
 Asn             :
 GNSS-SignalID   ::= SEQUENCE {
         gnss-SignalID       INTEGER (0 .. 7),
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssSignalID
(
    LPP_GNSS_SIGNAL_ID_STRU                                *pstGnssSignalID,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    if(pstGnssSignalID->ucGNSSSignalId > 7)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSSIGNALID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, pstGnssSignalID->ucGNSSSignalId);



    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssAcqAssistReq
 Description     : ����LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU
 Input           :
 Asn             :
 GNSS-AcquisitionAssistanceReq ::=   SEQUENCE {
         gnss-SignalID-Req       GNSS-SignalID,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssAcqAssistReq
(
    LPP_GNSS_ACQUISIT_ASSIST_REQ_STRU  *pstGnssAcqAssistReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ṹ������*/
    usRslt = NAS_LPP_EncodeGnssSignalID(&(pstGnssAcqAssistReq->stGNSSSignalIdReq),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssAlmanacReq
 Description     : ����LPP_GNSS_ALMANAC_REQ_STRU
 Input           :
 Asn             :
 GNSS-AlmanacReq ::= SEQUENCE {
         modelID             INTEGER(1..8)   OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssAlmanacReq
(
    LPP_GNSS_ALMANAC_REQ_STRU          *pstGnssAlmanacReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8           ucTempValue = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    if ( NAS_LPP_SLCT == pstGnssAlmanacReq->bitOpModelId )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if ( (pstGnssAlmanacReq->ucModelId < 1) || (pstGnssAlmanacReq->ucModelId > 8) )
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSALMANACREQ_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    ucTempValue = pstGnssAlmanacReq->ucModelId - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 3, ucTempValue);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssUTCModelReq
 Description     : ����LPP_GNSS_UTC_MODEL_REQ_STRU
 Input           :
 Asn             :
 GNSS-UTC-ModelReq ::=   SEQUENCE {
         modelID             INTEGER(1..8)   OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssUTCModelReq
(
    LPP_GNSS_UTC_MODEL_REQ_STRU        *pstGnssUTCModelReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucTempValue         = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    if ( NAS_LPP_SLCT == pstGnssUTCModelReq->bitOpModelId )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if ( (pstGnssUTCModelReq->ucModelId < 1) || (pstGnssUTCModelReq->ucModelId > 8) )
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSUTCMODELREQ_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    ucTempValue = pstGnssUTCModelReq->ucModelId - 1;
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 3, ucTempValue);

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssAuxInfoReq
 Description     : ����LPP_GNSS_AUX_INFO_REQ_STRU
 Input           :
 Asn             :
 Э��Ϊ��

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssAuxInfoReq
(
    LPP_GNSS_AUX_INFO_REQ_STRU         *pstGnssAuxInfoReq,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGnssGenAssisDataReqElement
 Description     : ����LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU
 Input           :
 Asn             :
 GNSS-GenericAssistDataReqElement ::= SEQUENCE {
         gnss-ID                         GNSS-ID,
         sbas-ID                         SBAS-ID                         OPTIONAL, -- Cond GNSS-ID-SBAS
         gnss-TimeModelsReq              GNSS-TimeModelListReq           OPTIONAL, -- Cond TimeModReq
         gnss-DifferentialCorrectionsReq GNSS-DifferentialCorrectionsReq OPTIONAL, -- Cond DGNSS-Req
         gnss-NavigationModelReq         GNSS-NavigationModelReq         OPTIONAL, -- Cond NavModReq
         gnss-RealTimeIntegrityReq       GNSS-RealTimeIntegrityReq       OPTIONAL, -- Cond RTIReq
         gnss-DataBitAssistanceReq       GNSS-DataBitAssistanceReq       OPTIONAL, -- Cond DataBitsReq
         gnss-AcquisitionAssistanceReq   GNSS-AcquisitionAssistanceReq   OPTIONAL, -- Cond AcquAssistReq
         gnss-AlmanacReq                 GNSS-AlmanacReq                 OPTIONAL, -- Cond AlmanacReq
         gnss-UTCModelReq                GNSS-UTC-ModelReq               OPTIONAL, -- Cond UTCModReq
         gnss-AuxiliaryInformationReq    GNSS-AuxiliaryInformationReq    OPTIONAL, -- Cond AuxInfoReq
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssGenAssisDataReqElement
(
    LPP_GNSS_GENERIC_ASSIST_DATA_REQ_ELEMENT_STRU          *pstGnssGenAssisDataReqElement,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*����OPTIONAL���־λ*/
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpSbasId)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSTimeModelIsReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDiffCorrectionReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSNavigationModelReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSRealTimeIntegrityReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDataBitAssitReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAcqAssitReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAlmanacReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSUtcModelReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAuxInfoReq)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 0);
    }

    /*����GNSS-ID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstGnssGenAssisDataReqElement->stGNSSId),
                                     pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return  usRslt;
    }
    /*����SBAS-ID*/
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpSbasId)
    {
        usRslt = NAS_LPP_EncodeSbasId(&(pstGnssGenAssisDataReqElement->stSbasId),
                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    /*����GNSS_TimeModelListReq*/
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSTimeModelIsReq)
    {
        usRslt = NAS_LPP_EncodeGnssTimeModelListReq(&(pstGnssGenAssisDataReqElement->stGNSSTimeModelsReq),
                                                       pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDiffCorrectionReq)
    {
        usRslt = NAS_LPP_EncodeGnssDiffCorrectReq(&(pstGnssGenAssisDataReqElement->stGNSSDiffCorrectReq),
                                                     pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSNavigationModelReq)
    {
        usRslt = NAS_LPP_EncodeGnssNavModelReq(&(pstGnssGenAssisDataReqElement->stGNSSNavigationModelReq),
                                                  pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSRealTimeIntegrityReq)
    {
        usRslt = NAS_LPP_EncodeGnssRealTimeIntReq(&(pstGnssGenAssisDataReqElement->stGNSSRealTimeIntergrityReq),
                                                     pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSDataBitAssitReq)
    {
        usRslt = NAS_LPP_EncodeGnssDataBitAssistReq(&(pstGnssGenAssisDataReqElement->stGNSSDataBitAssistanceReq),
                                                       pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAcqAssitReq)
    {
        usRslt = NAS_LPP_EncodeGnssAcqAssistReq(&(pstGnssGenAssisDataReqElement->stGNSSAcquisitAssitReq),pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAlmanacReq)
    {
        usRslt = NAS_LPP_EncodeGnssAlmanacReq(&(pstGnssGenAssisDataReqElement->stGNSSAlmanacReq),
                                                 pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSUtcModelReq)
    {
        usRslt = NAS_LPP_EncodeGnssUTCModelReq(&(pstGnssGenAssisDataReqElement->stGNSSUtcModelReq),
                                                  pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if(NAS_LPP_SLCT == pstGnssGenAssisDataReqElement->bitOpGNSSAuxInfoReq)
    {
        usRslt = NAS_LPP_EncodeGnssAuxInfoReq(&(pstGnssGenAssisDataReqElement->stGNSSAuxInfoReq),
                                                 pusBitPos,pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeGenReqAssistData
 Description     : ����LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU
 Input           :
 Asn             :
 GNSS-GenericAssistDataReq ::= SEQUENCE (SIZE (1..16)) OF GNSS-GenericAssistDataReqElement

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeGnssGenReqAssistData
(
    LPP_GNSS_GENERIC_ASSIST_DATA_REQ_STRU                  *pstGenReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;
    VOS_UINT8                                               ucCount         = 0;

    /*���鳤�ȺϷ��ԣ�����Ϸ�����sequence of ����*/
    if ((pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt > LPP_MAX_GEN_ASSIT_DATA_ELEMENT_LEN) ||
                        (pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt < 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSGENREQASSISTDATA_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    ucCount = (VOS_UINT8)(pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt - 1);
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 4, ucCount);

    /*ѭ������ṹ��*/
    for(ucCount = 0;ucCount < pstGenReqAssistData->ulGNSSGenericAssistDataReqCnt;ucCount++)
    {
        usRslt = NAS_LPP_EncodeGnssGenAssisDataReqElement(&(pstGenReqAssistData->astGNSSGenericAssistDataReqElement[ucCount]),
                                                             pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC !=usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   :NAS_LPP_EncodeAGNSSReqAssistData
 Description     : ����LPP_AGNSS_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 A-GNSS-RequestAssistanceData ::= SEQUENCE {
         gnss-CommonAssistDataReq        GNSS-CommonAssistDataReq        OPTIONAL, -- Cond CommonADReq
         gnss-GenericAssistDataReq       GNSS-GenericAssistDataReq       OPTIONAL, -- Cond GenADReq
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAGNSSReqAssistData
(
    LPP_AGNSS_REQ_ASSIST_DATA_STRU     *pstAGNSSReqAssistData,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{

    VOS_UINT16                          usRslt             = 0;

    /* ������չ��־λ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����OPTIONAL��־λ*/
    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSCommAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSGenericAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*������ڵ�OPTIONAL��*/
    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSCommAssistData )
    {
        usRslt = NAS_LPP_EncodeGnssComReqAssistData(&(pstAGNSSReqAssistData->stGNSSCommonAssistDataReq),
                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    if ( NAS_LPP_SLCT == pstAGNSSReqAssistData->bitOpGNSSGenericAssistData )
    {
        usRslt = NAS_LPP_EncodeGnssGenReqAssistData(&(pstAGNSSReqAssistData->stGNSSGenericAssistDataReq),
                                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeCellIdentity
 Description     : ����BIT STRING
 Input           :
 Asn             :
         cellidentity    BIT STRING (SIZE (28))
     }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCellIdentity
(
    VOS_UINT32                         *pulCellIdentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����cellidentity*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg, pusBitPos, 28, *pulCellIdentity);

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodePrimaryCellID
 Description     : ����LPP_PLMN_IDENTITY_STRU
 Input           :
 Asn             :
 plmn-Identity       SEQUENCE {
                                 mcc     SEQUENCE (SIZE (3))     OF INTEGER (0..9),
                                 mnc     SEQUENCE (SIZE (2..3))  OF INTEGER (0..9)
                             },

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodePrimaryCellID
(
    LPP_PLMN_IDENTITY_STRU             *pstPlmnIdentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucCount            = 0;

    /*MCC�Ϸ��Լ��*/
    if ( (pstPlmnIdentity->aucMcc[0] > 9) || (pstPlmnIdentity->aucMcc[1] > 9) ||
                                        (pstPlmnIdentity->aucMcc[2] > 9))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLID_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }

    /*MNC���ݺϷ��Լ��*/
    if ((pstPlmnIdentity->aucMnc[0] > 9) || (pstPlmnIdentity->aucMnc[1] > 9) ||
                                            (pstPlmnIdentity->aucMnc[2] > 9))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLID_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    if ( (pstPlmnIdentity->ucMncNum < 2) || (pstPlmnIdentity->ucMncNum > 3))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLID_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }

    /*����MCC,integerֵ0-9��ֻ��Ҫ����4bit����3��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMcc[0]);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMcc[1]);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMcc[2]);

    /*����MNC�ĸ�������ֵ*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, pstPlmnIdentity->ucMncNum);

    /*����MNC,integerֵ0-9��ֻ��Ҫ����4bit����2-3��*/
    for(ucCount = 0; ucCount < (pstPlmnIdentity->ucMncNum) ;ucCount++)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 4, pstPlmnIdentity->aucMnc[ucCount]);
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeECGI
 Description     : ����LPP_ECGI_STRU
 Input           :
 Asn             :
     ECGI ::= SEQUENCE {
        mcc             SEQUENCE (SIZE (3))     OF INTEGER (0..9),
        mnc             SEQUENCE (SIZE (2..3))  OF INTEGER (0..9),
        cellidentity    BIT STRING (SIZE (28))

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeECGI
(
    LPP_ECGI_STRU                      *pstECGI,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt             = 0;

    /*����PLMN_IDENTIFY*/
    usRslt = NAS_LPP_EncodePrimaryCellID(&(pstECGI->stPlmnIdentity), pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����cellidentity TYPE:BIT STRING*/
    usRslt = NAS_LPP_EncodeCellIdentity(&(pstECGI->ulCellIdentity), pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeCommIEsAssistData
 Description     : ����LPP_COMMON_IES_REQ_ASSIST_DATA_STRU
 Input           :
 Asn             :
 CommonIEsRequestAssistanceData ::= SEQUENCE {
         primaryCellID       ECGI        OPTIONAL,   -- Cond EUTRA
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-21  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommIEsAssistData
(
    LPP_COMMON_IES_REQ_ASSIST_DATA_STRU                    *pstCommIEsAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*���OPNTIONAL����ڣ�����OPTIONAL��*/
    if(NAS_LPP_NO_SLCT == pstCommIEsAssistData->bitOpPrimaryCellID)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 0);
        return NAS_LPP_ENCODE_SUCC;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, 1);
    usRslt = NAS_LPP_EncodeECGI(&(pstCommIEsAssistData->stPrimaryCellID),  pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeReqAssistDataR9IEs
 Description     : ����LPP_REQUEST_ASSIST_DATA_R9_IES_STRU
 Input           :
 Asn             :
 RequestAssistanceData-r9-IEs ::= SEQUENCE {
         commonIEsRequestAssistanceData      CommonIEsRequestAssistanceData      OPTIONAL,
         a-gnss-RequestAssistanceData        A-GNSS-RequestAssistanceData        OPTIONAL,
         otdoa-RequestAssistanceData         OTDOA-RequestAssistanceData         OPTIONAL,
         epdu-RequestAssistanceData          EPDU-Sequence                       OPTIONAL,
         ...
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeReqAssistDataR9IEs
(
    LPP_REQUEST_ASSIST_DATA_R9_IES_STRU                    *pstReqAssistDataR9IEs,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;


    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*����OPTIONAL��bitOpCommonIEsRequestAssitData��־λ*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpCommonIEsRequestAssitData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*����OPTIONAL��bitOpAGNSSRequestAssistData��־λ*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpAGNSSRequestAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }
    /*����OPTIONAL��bitOpOTDOARequestAssistData��־λ*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpOTDOARequestAssistData )
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }
    /*����OPTIONAL��bitOpEPDUSequence��־λ*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpEPDUSequence)
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 1);
    }
    else
    {
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 1, 0);
    }

    /*����ṹ������*/
    /*�����ѡ����ڣ������*/
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpCommonIEsRequestAssitData )
    {
        usRslt = NAS_LPP_EncodeCommIEsAssistData(&(pstReqAssistDataR9IEs->stCommonIEsRequestAssistanceData),
                                                    pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpAGNSSRequestAssistData)
    {
        usRslt = NAS_LPP_EncodeAGNSSReqAssistData(&(pstReqAssistDataR9IEs->stAGNSSRequestAssistanceData),
                                                     pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpOTDOARequestAssistData)
    {
        usRslt = NAS_LPP_EncodeOTDOAReqAssistData(&(pstReqAssistDataR9IEs->stOTDOARequestAssistanceData),
                                                     pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    if ( NAS_LPP_SLCT == pstReqAssistDataR9IEs->bitOpEPDUSequence)
    {
        usRslt = NAS_LPP_EncodeEpduReqAssistData(&(pstReqAssistDataR9IEs->stEPDURequestAssistanceData),
                                                    pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}



/*****************************************************************************
 Function Name   : NAS_LPP_EncodeExtRequestAssistData
 Description     : ����LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU
 Input           :
 Asn             :
 c1                      CHOICE {
                 requestAssistanceData-r9    RequestAssistanceData-r9-IEs,
                 spare3 NULL, spare2 NULL, spare1 NULL
             },

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-20  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeExtRequestAssistData
(
    LPP_CRITI_EXT_REQUEST_ASSIST_DATA_STRU                 *pstExtReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*����choice��*/
    /*�ĸ�choice�����������bit��ʾ*/
    if(pstExtReqAssistData->ulChoice > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EXTREQUESTASSISTDATA_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstExtReqAssistData->ulChoice));

    switch(pstExtReqAssistData->ulChoice)
    {
        case LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeReqAssistDataR9IEs(&(pstExtReqAssistData->u.stRequestAssitDataR9),
                                                         pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeRequestAssistData
 Description     : ����LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU
 Input           : pstProvideCapabilty      ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeRequestAssistData
(
    LPP_MESSAGE_REQUEST_ASSIST_DATA_STRU                   *pstReqAssistData,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*����choice��*/
    /*����choice�������һ��bit��ʾ����*/
    if ( pstReqAssistData->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_REQUESTASSISTDATA_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstReqAssistData->ulChoice));

    switch(pstReqAssistData->ulChoice)
    {
        case LPP_C1_CRITI_EXT_REQUEST_ASSIST_DATA_CHOSEN:
            usRslt = NAS_LPP_EncodeExtRequestAssistData(&(pstReqAssistData->u.stC1),
                                                           pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_CRITI_EXT_FUTURE_REQUEST_ASSIST_DATA_CHOSEN:
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEllipsoidPoint
(
    LPP_ELLIPSOID_POINT_STRU           *pstEllipsoidPoint,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPoint->enLatitudeSign));

    /*����degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPoint->ulDegreeLatitude);

    /*����degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPoint->lDegreesLongitude + 8388608));

    return NAS_LPP_DECODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithUncertaintyCircle
(
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_STRU       *pstEllipsoidPointWithCircle,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipsoidPointWithCircle->enLatitudeSign));

    /*����degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipsoidPointWithCircle->ulDegreesLatitude);

    /*����degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstEllipsoidPointWithCircle->lDegreeLongitude + 8388608));

    /*����uncertainty*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipsoidPointWithCircle->ulUncretainty));

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithUncertaintyEllipse
(
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU      *pstEllipsoidPointWithUncertaintyEllipse,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg)
{
    LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_STRU      *pstTempStru = pstEllipsoidPointWithUncertaintyEllipse;

    if ( pstTempStru->enLatitudeSign > 1 )
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstTempStru->ulDegreesLatitude > 8388607) || (pstTempStru->ucUncertaintySemiMajor > 127) ||
         (pstTempStru->ucUncertaintySemiMinor > 127) || (pstTempStru->ucOrientationMajorAxis >179)
       ||(pstTempStru->ucConfidence >100)||((pstTempStru->lDegreesLongitude >8388607)
       ||(pstTempStru->lDegreesLongitude < -8388608)))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1,
                             (VOS_UINT8)(pstEllipsoidPointWithUncertaintyEllipse->enLatitudeSign));

    /*����degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPointWithUncertaintyEllipse->ulDegreesLatitude);

    /*����degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPointWithUncertaintyEllipse->lDegreesLongitude + 8388608));

    /*����uncertaintySemiMajor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMajor);

    /*����uncertaintySemiMinor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMinor);

    /*����orientationMajorAxis*/
    if(pstEllipsoidPointWithUncertaintyEllipse->ucUncertaintySemiMinor > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidPointWithUncertaintyEllipse->ucOrientationMajorAxis);

    /*����confidence*/
    if(pstEllipsoidPointWithUncertaintyEllipse->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHUNCERTAINTYELLIPSE_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7,
                              pstEllipsoidPointWithUncertaintyEllipse->ucConfidence);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodePolygonPoints
(
    LPP_POLYGON_POINTS_STRU            *pstPolygonPoints,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    if(pstPolygonPoints->enLatitudeSign >1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POLYGONPOINTS_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstPolygonPoints->lDegreesLatitude > 8388607)
       ||(pstPolygonPoints->lDegreesLatitude < -8388608)
       ||(pstPolygonPoints->ulDegreesLatitude > 8388607))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POLYGONPOINTS_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstPolygonPoints->enLatitudeSign));

    /*����degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstPolygonPoints->ulDegreesLatitude);

    /*����degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstPolygonPoints->lDegreesLatitude + 8388608));

    return NAS_LPP_DECODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodePolygon
(
    LPP_POLYGON_STRU                   *pstPolygon,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;

    /*����ṹ�����ֵ*/
    if ( ((pstPolygon->ulPolygonCnt) < 3) || ((pstPolygon->ulPolygonCnt) > 15))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_POLYGON_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 4, (VOS_UINT8)((pstPolygon->ulPolygonCnt) - 3));

    /*����ṹ��ʵ��*/
    for(ulLoop = 0; ulLoop < pstPolygon->ulPolygonCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodePolygonPoints(&(pstPolygon->astPolygonArray[ulLoop]),
                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithaltitude
(
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_STRU                 *pstEllipsoidPointWithAltitude,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    if((pstEllipsoidPointWithAltitude->enLatitudeSign >1)||(pstEllipsoidPointWithAltitude->enAltitudeDirection > 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstEllipsoidPointWithAltitude->lDegreesLatitude > 8388607)
       ||(pstEllipsoidPointWithAltitude->lDegreesLatitude < -8388608)
       ||(pstEllipsoidPointWithAltitude->ulDegreesLatitude > 8388607)
       ||(pstEllipsoidPointWithAltitude->usAltitude > 32767))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_INTEGER, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPointWithAltitude->enLatitudeSign));

    /*����degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23,
                                  pstEllipsoidPointWithAltitude->ulDegreesLatitude);

    /*����degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidPointWithAltitude->lDegreesLatitude + 8388608));

    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstEllipsoidPointWithAltitude->enAltitudeDirection));

    /*����tltitude*/
    NAS_LPP_EncodeEncodeLongData( pucEncodeOutMsg,  pusBitPos,  15,
                                   pstEllipsoidPointWithAltitude->usAltitude);

    return NAS_LPP_DECODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeEllipsoidPointWithAltitudeAndEllipoid
(
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    *pstEllipPointAndUncertEllip,
    VOS_UINT16                                                          *pusBitPos,
    VOS_UINT8                                                           *pucEncodeOutMsg
)
{
    LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_STRU    *pstTempStru = pstEllipPointAndUncertEllip;
    if((pstTempStru->enAltitudeDirection > 1)||(pstTempStru->enLatitudeSign > 1))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if ( (pstTempStru->ucConfidence > 100)
       ||(pstTempStru->ucOrientationMajorAxis > 179)
       ||(pstTempStru->ucUncertaintyAltitude > 127)
       ||(pstTempStru->ucUncertaintySemiMajor > 127)
       ||(pstTempStru->ucUncertaintySemiMinor > 127)
       ||(pstEllipPointAndUncertEllip->lDegreesLongtitude > 8388607)
       ||(pstEllipPointAndUncertEllip->lDegreesLongtitude < -8388608)
       ||(pstEllipPointAndUncertEllip->usAltitude > 32767))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipPointAndUncertEllip->enLatitudeSign));

    /*����degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipPointAndUncertEllip->ulDegreesLatitude);

    /*����degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24, (VOS_UINT32)(pstEllipPointAndUncertEllip->lDegreesLongtitude + 8388608));

    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipPointAndUncertEllip->enAltitudeDirection));

    /*����tltitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 15, pstEllipPointAndUncertEllip->usAltitude);

    /*����ucUncertaintySemiMajor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipPointAndUncertEllip->ucUncertaintySemiMajor));

    /*����uncertaintySemiMinor*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstEllipPointAndUncertEllip->ucUncertaintySemiMinor));

    /*����orientationMajorAxis*/
    if ( pstEllipPointAndUncertEllip->ucUncertaintySemiMinor > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipPointAndUncertEllip->ucOrientationMajorAxis);

    /*����uncertaintyAltitude*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipPointAndUncertEllip->ucUncertaintyAltitude);

    /*����confidence*/
    if ( pstEllipPointAndUncertEllip->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDPOINTWITHALTITUDEANDELLIPOID_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipPointAndUncertEllip->ucConfidence);

    return NAS_LPP_DECODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEllipsoidArc
(
    LPP_ELLIPSOIDARC_STRU              *pstEllipsoidArc,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    if(pstEllipsoidArc->enLatitudeSign > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    if((pstEllipsoidArc->lDegreesLongtitude > 8388607)
     || (pstEllipsoidArc->lDegreesLongtitude < -8388608)
     || (pstEllipsoidArc->ucConfidence > 100)
     || (pstEllipsoidArc->ucIncludedAngle > 179)
     || (pstEllipsoidArc->ucOffsetAngle > 179)
     || (pstEllipsoidArc->ucUncertaintyRadius > 127)
     || (pstEllipsoidArc->ulDegreesLatitude > 8388607)
     || (pstEllipsoidArc->ulInnerRadius > 65535))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    /*����latitudeSign*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstEllipsoidArc->enLatitudeSign));

    /*����degreesLatitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 23, pstEllipsoidArc->ulDegreesLatitude);

    /*����degreesLongitude*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 24,
                                 (VOS_UINT32)(pstEllipsoidArc->lDegreesLongtitude + 8388608));

    /*����innerRadius*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg,  pusBitPos, 16, pstEllipsoidArc->ulInnerRadius);

    /*����uncertaintyRadius*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipsoidArc->ucUncertaintyRadius);

    /*����offsetAngle*/
    if(pstEllipsoidArc->ucOffsetAngle > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidArc->ucOffsetAngle);

    /*����includedAngle*/
    if(pstEllipsoidArc->ucIncludedAngle > 179)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, pstEllipsoidArc->ucIncludedAngle);

    /*����confidence*/
    if(pstEllipsoidArc->ucConfidence > 100)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ELLIPSOIDARC_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, pstEllipsoidArc->ucConfidence);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeLoctionEstimate
(
    LPP_LOCATION_COORDINATE_STRU       *pstLocationCoordinate,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*����choice��*/
    if(pstLocationCoordinate->ulChoice > 6)
    {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCTIONESTIMATE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3, (VOS_UINT8)(pstLocationCoordinate->ulChoice));

    switch(pstLocationCoordinate->ulChoice)
    {
        case LPP_ELLIPSOID_POINT_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPoint(&(pstLocationCoordinate->u.stEllipsoidPoint),
                                                     pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithUncertaintyCircle(&(pstLocationCoordinate->u.stEllipsoidPointWithUncertaintyCircle),
                                                                          pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithUncertaintyEllipse(&(pstLocationCoordinate->u.stEllipsoidPointWithUncertaintyEllipse),
                                                                           pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_POLYGON_CHOSEN:
            usRslt = NAS_LPP_EncodePolygon(&(pstLocationCoordinate->u.stPolygon), pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;


        case LPP_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithaltitude(&(pstLocationCoordinate->u.stEllipsoidPointWithAltitude),
                                                                 pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN:
            usRslt = NAS_LPP_EncodeEllipsoidPointWithAltitudeAndEllipoid(&(pstLocationCoordinate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid),
                                                                            pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeEllipsoidArc(&(pstLocationCoordinate->u.stEllipsoidArc),
                                                   pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeHorizontalVelcoctiy
(
    LPP_HORIZONTAL_VELCOCTIY_STRU      *pstHorizontalVelcoctiy,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����bearing*/
    if(((pstHorizontalVelcoctiy->usBearing) > 359)||(pstHorizontalVelcoctiy->usHorizontalSpeed > 2047))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALVELCOCTIY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstHorizontalVelcoctiy->usBearing);

    /*����horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11, pstHorizontalVelcoctiy->usHorizontalSpeed);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeHorizontalWithVerticalVelocity
(
    LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_STRU             *pstHorizontalWithVelocity,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*����bearing*/
    if(((pstHorizontalWithVelocity->usBearing) > 359)
      ||(pstHorizontalWithVelocity->usHorizontalSpeed > 2047)
      ||(pstHorizontalWithVelocity->ulVerticalSpeed >2055))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVERTICALVELOCITY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    if(pstHorizontalWithVelocity->enVerticalDirection > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVERTICALVELOCITY_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstHorizontalWithVelocity->usBearing);

    /*����horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11, pstHorizontalWithVelocity->usHorizontalSpeed);

    /*����VerticalDirection*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1,
                             (VOS_UINT8)(pstHorizontalWithVelocity->enVerticalDirection));

    /*����verticalSpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                             (VOS_UINT8)(pstHorizontalWithVelocity->ulVerticalSpeed));

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeHorizontalWithUnceritanity
(
    LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_STRU          *pstHorizontalWithUncertainty,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*����bearing*/
    if(((pstHorizontalWithUncertainty->usBearing) > 359)
      ||(pstHorizontalWithUncertainty->ulUncertaintySpeed >255)
      ||(pstHorizontalWithUncertainty->usHorizontalSpeed > 2047))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHUNCERITANITY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstHorizontalWithUncertainty->usBearing);

    /*����horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11, pstHorizontalWithUncertainty->usHorizontalSpeed);

    /*����verticalSpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8, (VOS_UINT8)(pstHorizontalWithUncertainty->ulUncertaintySpeed));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeHorizontalWithVeloctiyAndUncertaainty
(
    LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_AND_UNCERTAINTY_STRU      *pstHorizontalWithVelocityAndUncerta,
    VOS_UINT16                                                      *pusBitPos,
    VOS_UINT8                                                       *pucEncodeOutMsg
)
{
    /*����bearing*/
    if (((pstHorizontalWithVelocityAndUncerta->usBearing) > 359)
       ||(pstHorizontalWithVelocityAndUncerta->usHorizontalSpeed > 2048))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVELOCTIYANDUNCERTAAINTY_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    if(pstHorizontalWithVelocityAndUncerta->enVerticalDirection > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_HORIZONTALWITHVELOCTIYANDUNCERTAAINTY_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,
                                  pstHorizontalWithVelocityAndUncerta->usBearing);

    /*����horizontalSpeed*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 11,
                                  pstHorizontalWithVelocityAndUncerta->usHorizontalSpeed);

    /*����VerticalDirection*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1,
                             (VOS_UINT8)(pstHorizontalWithVelocityAndUncerta->enVerticalDirection));

    /*����verticalSpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                              pstHorizontalWithVelocityAndUncerta->ucVerticalSpeed);

    /*����horizontalUncertaintySpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                              pstHorizontalWithVelocityAndUncerta->ucHorizontalUncertaintySpeed);

    /*����verticalUncertaintySpeed*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 8,
                              pstHorizontalWithVelocityAndUncerta->ucVerticalUncertaintySpeed);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeVelocityEstimate
(
    LPP_VELOCITY_STRU                  *pstVelocityCoordinate,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16 usRslt = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*����choice��*/
    if(pstVelocityCoordinate->ulChoice > 3)
    {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_VELOCITYESTIMATE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 2,
                              (VOS_UINT8)(pstVelocityCoordinate->ulChoice));

    switch(pstVelocityCoordinate->ulChoice)
    {
        case LPP_HORIZONTAL_VELCOCTIY_CHOSEN:
            usRslt = NAS_LPP_EncodeHorizontalVelcoctiy(&(pstVelocityCoordinate->u.stHorizontalVelocity),
                                                          pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_HORIZONTAL_WITH_VERTICAL_VELOCITY_CHOSEN:
            usRslt = NAS_LPP_EncodeHorizontalWithVerticalVelocity(&(pstVelocityCoordinate->u.stHorizontalWithVerticalVelocity),
                                                                     pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_HORIZONTAL_VELCCITY_WITH_UNCERTAINTY_CHOSEN:
            usRslt = NAS_LPP_EncodeHorizontalWithUnceritanity(&(pstVelocityCoordinate->u.stHorizontalVelocityWithUncertainty),
                                                                 pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeHorizontalWithVeloctiyAndUncertaainty(&(pstVelocityCoordinate->u.stHorizontalWithVerticalVelocityAndUncertainty),
                                                                            pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeLocatonFailureCause
(
    LPP_LOCATION_FAILURE_CAUSE_ENUM_UINT32                  enLocationFailureCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չλ*/
    if(enLocationFailureCause > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_LOCATONFAILURECAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����ö����*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)enLocationFailureCause);

    return NAS_LPP_DECODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeLocationError
(
    LPP_LOCATION_ERROR_STRU            *pstLocationError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
   VOS_UINT16                           usRslt              = 0;

    /*������չλ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);
    /*����ö����*/
    usRslt = NAS_LPP_EncodeLocatonFailureCause(pstLocationError->enLocationFailureCasue,
                                               pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeCommonIesProvideLocation
(
    LPP_COMMON_IES_PROVIDE_LOCATION_INFO_STRU              *pstcommonIesProvideLocInfo,
    VOS_UINT16                                             *pusPos,
    VOS_UINT8                                              *puEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusPos,  puEncodeOutMsg);

    /*����option*/
    NAS_LPP_EncodeBitsLess8(puEncodeOutMsg, pusPos, 1,
                             (VOS_UINT8)(pstcommonIesProvideLocInfo->bitOpLocationEstimate));
    NAS_LPP_EncodeBitsLess8(puEncodeOutMsg, pusPos, 1,
                             (VOS_UINT8)(pstcommonIesProvideLocInfo->bitOpVelocityEstimate));
    NAS_LPP_EncodeBitsLess8(puEncodeOutMsg, pusPos, 1,
                             (VOS_UINT8)(pstcommonIesProvideLocInfo->bitOpLocationError));

    /*����locationEstimate*/
    if(NAS_LPP_SLCT == pstcommonIesProvideLocInfo->bitOpLocationEstimate)
    {
        usRslt = NAS_LPP_EncodeLoctionEstimate(&(pstcommonIesProvideLocInfo->stLocationEstimate),
                                                  pusPos,  puEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����VelocityEstimate*/
    if(NAS_LPP_SLCT == pstcommonIesProvideLocInfo->bitOpVelocityEstimate)
    {
        usRslt = NAS_LPP_EncodeVelocityEstimate(&(pstcommonIesProvideLocInfo->stVelocityEstimate),
                                                   pusPos,  puEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����LocationError*/
    if(NAS_LPP_SLCT == pstcommonIesProvideLocInfo->bitOpLocationError)
    {
        usRslt = NAS_LPP_EncodeLocationError(&(pstcommonIesProvideLocInfo->stLocationError),
                                                pusPos,  puEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodePlmnIdentity
(
    LPP_PLMN_IDENTITY_STRU             *pstPlmnIndentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT32  ulLoop = 0;

    /*����MCC*/
    for(ulLoop = 0; ulLoop < 3; ulLoop++)
    {
        if(pstPlmnIndentity->aucMcc[ulLoop] > 9)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PLMNIDENTITY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)(pstPlmnIndentity->aucMcc[ulLoop]));
    }
    /*����MNC*/
    if((pstPlmnIndentity->ucMncNum < 2) || (pstPlmnIndentity->ucMncNum  > 3))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PLMNIDENTITY_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)((pstPlmnIndentity->ucMncNum) - 2));
    for(ulLoop = 0; ulLoop < pstPlmnIndentity->ucMncNum; ulLoop++)
    {
        if(pstPlmnIndentity->aucMnc[ulLoop] > 9)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PLMNIDENTITY_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)(pstPlmnIndentity->aucMnc[ulLoop]));
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeCellIdentityEtranAndUtran
(
    LPP_CELL_IDENTITY_STRU             *pstCellIdentity,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����choice*/
    if(pstCellIdentity->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_CELLIDENTITYETRANANDUTRAN_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstCellIdentity->ulChoice));

    switch(pstCellIdentity->ulChoice)
    {
        case LPP_EUTRA_CHOSEN:
            NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 28, pstCellIdentity->u.ulEutra);
            break;

        default:
            NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 32, pstCellIdentity->u.ulUtra);
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeCellGlobalIdEuranAndUtran
(
    LPP_CELL_GLO_EUTRA_UTRA_STRU       *pstCellGolablId,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����plmn-identity*/
    usRslt = NAS_LPP_EncodePlmnIdentity(&(pstCellGolablId->stPlmnIdentity),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*CellIdentity*/
    usRslt = NAS_LPP_EncodeCellIdentityEtranAndUtran(&(pstCellGolablId->stCellIdentity),
                                                        pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeEutra
(
    LPP_MEAS_REF_TIME_EUTRA            *pstNetWorkTimeEutan,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeEutan->bitCellGlobalId));

    /*����physCellId*/
    if(pstNetWorkTimeEutan->ulPhysCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EUTRA_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,  pstNetWorkTimeEutan->ulPhysCellId);

    /*����cellGloabalId*/
    if(NAS_LPP_SLCT == pstNetWorkTimeEutan->bitCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalIdEuranAndUtran(&(pstNetWorkTimeEutan->stCellGlobalId),
                                                            pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����systemFrameNumber*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10,  pstNetWorkTimeEutan->ulSystemFramNumber);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeUtranMode
(
    LPP_MODE_SELECT_STRU               *pstMode,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����choice*/
    if(pstMode->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTRANMODE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstMode->ulChoice));

    switch(pstMode->ulChoice)
    {
        case LPP_FDD_CHOSEN:
            /*������չ��־λ*/
            NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
            /*����primary-cpich-info*/
            if(pstMode->u.stFdd.ulPrimaryCpichInfo  > 511)
            {
                NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTRANMODE_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                        *pusBitPos, __LINE__, 0);
                return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
            }
            NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,  pstMode->u.stFdd.ulPrimaryCpichInfo);
            break;

        default:
            /*������չ��־λ*/
            NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
            /*����cellParametres*/
            if(pstMode->u.stTdd.ulCellParameters > 127)
            {
                NAS_LPP_ASN_FAIL_Message(NAS_LPP_UTRANMODE_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                        *pusBitPos, __LINE__, 0);
                return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
            }
            NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7,
                                     (VOS_UINT8)(pstMode->u.stTdd.ulCellParameters));
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeUtra
(
    LPP_MEAS_REF_TIME_UTRA             *pstNetWorkTimeUtan,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeUtan->bitCellGlobalId));

    /*����mode*/
    usRslt = NAS_LPP_EncodeUtranMode(&(pstNetWorkTimeUtan->stMode),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����cellGloabalId*/
    if(NAS_LPP_SLCT == pstNetWorkTimeUtan->bitCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalIdEuranAndUtran(&(pstNetWorkTimeUtan->stCellGlobalId),
                                                            pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����referenceSystemFrameNumber*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 12, pstNetWorkTimeUtan->ulRefSystemFramNumber);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeCellGlobalGeran
(
    LPP_CELL_GLO_ID_GERAN_STRU         *pstCellGlobalGeran,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����plmn-identity*/
    usRslt = NAS_LPP_EncodePlmnIdentity(&(pstCellGlobalGeran->stPlmnIdentity),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����locationAreaCode*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstCellGlobalGeran->usLocationAreaCode);

    /*����locationAreaCode*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstCellGlobalGeran->usCellIdentity);

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeRefFrame
(
    LPP_REF_FRAME_STRU                 *pstRefFrame,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
     /*������չ��־λ*/
     NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

     /*�����ѡ��*/
     NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstRefFrame->bitOpRefEnmsb));

     /*����refFn*/
     NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstRefFrame->usRefFn);

     /*����refFnmsb*/
     if(NAS_LPP_SLCT == pstRefFrame->bitOpRefEnmsb)
     {
        if(pstRefFrame->usRefFnmsn > 63)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_REFFRAME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstRefFrame->usRefFnmsn));
     }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGSM
(
    LPP_MEAS_REF_TIME_GSM              *pstNetWorkTimeGsm,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeGsm->bitCellGlobalId));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNetWorkTimeGsm->bitDelataGnssTod));

    /*����bcchCarrier*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, pstNetWorkTimeGsm->usBcchCarrier);

    /*����bsic*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstNetWorkTimeGsm->usBsic));

    /*����cellGlobalId*/
    if(NAS_LPP_SLCT == pstNetWorkTimeGsm->bitCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalGeran(&(pstNetWorkTimeGsm->stCellGlobalId),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����refFrame*/
    usRslt = NAS_LPP_EncodeRefFrame(&(pstNetWorkTimeGsm->stRefFrame),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����deltaGnssTod*/
    if(NAS_LPP_SLCT == pstNetWorkTimeGsm->bitDelataGnssTod)
    {
        if(pstNetWorkTimeGsm->ulDelaGnssTod > 127)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GSM_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, (VOS_UINT8)(pstNetWorkTimeGsm->ulDelaGnssTod));
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeNetWorkTime
(
    LPP_NET_WORK_TIME_MEAS_REF_STRU    *pstNetWorkTime,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*����choice��*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 2, (VOS_UINT8)(pstNetWorkTime->ulChoice));

    switch(pstNetWorkTime->ulChoice)
    {
        case LPP_NETTIME_EUTRA_CHOSEN:
            usRslt = NAS_LPP_EncodeEutra(&(pstNetWorkTime->u.stLppMeasRefTimeEutra),
                                            pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_NETTIME_UTRAN_CHOSEN:
            usRslt = NAS_LPP_EncodeUtra(&(pstNetWorkTime->u.stLppMeasRefTimeUtra),
                                           pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_NETTIME_GSM_CHOSEN:
            usRslt = NAS_LPP_EncodeGSM(&(pstNetWorkTime->u.stLppMeasRefTimeGsm),
                                          pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}



VOS_UINT16 NAS_LPP_EncodeMeasRefTime
(
    LPP_MEAS_REF_TIME_STRU             *pstMeasRefTime,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstMeasRefTime->bitOpGNSSTodFrac));
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstMeasRefTime->bitOpGNSSTodUnc));
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstMeasRefTime->bitOpNetWorkTime));

    /*����gnss-TOD-msec*/
    if((pstMeasRefTime->ulGNSSTodMsec > 35999)||((pstMeasRefTime->bitOpGNSSTodUnc == 1)&&(pstMeasRefTime->usGNSSTodUnc > 127)))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASREFTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 22, (VOS_UINT32)(pstMeasRefTime->ulGNSSTodMsec));

    /*���� gnss-TOD-frac*/
    if(NAS_LPP_SLCT == pstMeasRefTime->bitOpGNSSTodFrac)
    {
        if(pstMeasRefTime->usGNSSTodFrac > 3999)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASREFTIME_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 12, (VOS_UINT16)(pstMeasRefTime->usGNSSTodFrac));
    }

    /*����gnss-TOD-unc*/
    if(NAS_LPP_SLCT == pstMeasRefTime->bitOpGNSSTodUnc)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstMeasRefTime->usGNSSTodUnc));
    }

    /*����gnss-TimeID*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstMeasRefTime->stGNSSId),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����networkTime*/
    if(NAS_LPP_SLCT == pstMeasRefTime->bitOpNetWorkTime)
    {
        usRslt = NAS_LPP_EncodeNetWorkTime(&(pstMeasRefTime->stNetWorktime),  pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGnssSatMeasElment
(
    LPP_GNSS_SAT_MEAS_ELEMENT_STRU     *pstGnssSatMeasElment,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpCarrierQualityInd));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpIntegerCodePhase));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpDoppler));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstGnssSatMeasElment->bitOpAdr));


    /*����svid*/
    usRslt = NAS_LPP_EncodeSVID(&(pstGnssSatMeasElment->stSvId),  pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����cno*/
    if(pstGnssSatMeasElment->ulCNo > 63)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, pstGnssSatMeasElment->ulCNo);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstGnssSatMeasElment->ulCNo));

    /*����mpatchDet*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstGnssSatMeasElment->enMpathDet));

    /*����carrierqualityInd*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpCarrierQualityInd)
    {
        if(pstGnssSatMeasElment->ucCrrierQualityInd > 3)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstGnssSatMeasElment->ucCrrierQualityInd));
    }

    /*����codePhase*/
    if(pstGnssSatMeasElment->ulCodePhase > 2097151)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 21, pstGnssSatMeasElment->ulCodePhase);

    /*����integercodephase*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpIntegerCodePhase)
    {
        if(pstGnssSatMeasElment->ucIntgerCodePhase > 127)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, (VOS_UINT8)(pstGnssSatMeasElment->ucIntgerCodePhase));
    }

    /*����codephasepmserror*/
    if(pstGnssSatMeasElment->ucCodePhaseRmsError > 63)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstGnssSatMeasElment->ucCodePhaseRmsError));

    /*����dopploer*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpDoppler)
    {
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, (VOS_UINT16)((pstGnssSatMeasElment->sDoppler) + 32768));
    }

    /*����adr*/
    if(NAS_LPP_SLCT == pstGnssSatMeasElment->bitOpAdr)
    {
        if(pstGnssSatMeasElment->ulAdr > 33554431)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASELMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 25, pstGnssSatMeasElment->ulAdr);
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGnssSatMeasList
(
    LPP_GNSS_SAT_MEAS_LIST_STRU        *pstGnssSatMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt      = 0;
    VOS_UINT32                          ulLoop      = 0;

    /*�������ֵ*/
    if((pstGnssSatMeasList->ulGNSSSatMeasListCnt < 1)
    || (LPP_MAX_GNSS_SAT_MEAS_ELMENT_LEN < pstGnssSatMeasList->ulGNSSSatMeasListCnt))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSATMEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 6, (VOS_UINT8)((pstGnssSatMeasList->ulGNSSSatMeasListCnt) - 1));

    /*������Ϣʵ��*/
    for(ulLoop = 0; ulLoop < pstGnssSatMeasList->ulGNSSSatMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeGnssSatMeasElment(&(pstGnssSatMeasList->astGNSSSatMeasListArray[ulLoop]),
                                                    pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGnssSgnMeasElement
(
    LPP_GNSS_SGN_MEAS_ELEMENT_STRU     *pstGnssSgnMeasElement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos, pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstGnssSgnMeasElement->bitOpGNSSCodePhaseAmbiguity));

    /*����gnss-SignalID*/
    usRslt = NAS_LPP_EncodeGnssSignalID(&(pstGnssSgnMeasElement->stGNSSSignalId),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����codephaseAmbi*/
    if(NAS_LPP_SLCT == pstGnssSgnMeasElement->bitOpGNSSCodePhaseAmbiguity)
    {
        if(pstGnssSgnMeasElement->ulGNSSCodePhaseAmbiguity > 127)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSGNMEASELEMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 7, (VOS_UINT8)(pstGnssSgnMeasElement->ulGNSSCodePhaseAmbiguity));
    }

    /*����GNSS-SATMEASLIST*/
    usRslt = NAS_LPP_EncodeGnssSatMeasList(&(pstGnssSgnMeasElement->stGNSSSatMeasList),
                                              pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGnssSgnMeasList
(
    LPP_GNSS_SGN_LIST_STRU             *pstGnssSgnMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;

    /*�������ֵ*/
    if((pstGnssSgnMeasList->ulGNSSSgnMeasListCnt < 1) || (pstGnssSgnMeasList->ulGNSSSgnMeasListCnt > 8))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_GNSSSGNMEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 3,
                              (VOS_UINT8)((pstGnssSgnMeasList->ulGNSSSgnMeasListCnt) - 1));

    /*������Ϣʵ��*/
    for(ulLoop = 0; ulLoop < pstGnssSgnMeasList->ulGNSSSgnMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeGnssSgnMeasElement(&(pstGnssSgnMeasList->astGNSSSgnMeasListArray[ulLoop]),
                                                     pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeGnssMeasList
(
    LPP_GNSS_MEAS_FOR_ONE_GNSS_STRU    *pstGnssMeasForOneGnss,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt             = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit(pusBitPos, pucEncodeOutMsg);

    /*����gnss-id*/
    usRslt = NAS_LPP_EncodeGnssId(&(pstGnssMeasForOneGnss->stGNSSId), pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����gnss-SgnMeasList*/
    usRslt = NAS_LPP_EncodeGnssSgnMeasList(&(pstGnssMeasForOneGnss->stGNSSSgnMeasList),
                                              pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeMeasList
(
    LPP_GNSS_MEAS_LIST_STRU            *pstGnssMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;


    if((pstGnssMeasList->ulGNSSMeasListCnt < 1) ||(pstGnssMeasList->ulGNSSMeasListCnt > 16))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)pstGnssMeasList->ulGNSSMeasListCnt - 1);


    /*������Ϣʵ��*/
    for(ulLoop = 0; ulLoop < pstGnssMeasList->ulGNSSMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeGnssMeasList(&(pstGnssMeasList->astGNSSMeasListArray[ulLoop]),
                                               pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_Encdoe_AgnssSignalMeasInfo
(
    LPP_GNSS_SIGNAL_MEAS_INFO_STRU     *pstAgnssSignalMeasInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����measurementReferenceTime*/
    usRslt = NAS_LPP_EncodeMeasRefTime(&(pstAgnssSignalMeasInfo->stMeasRefTime),
                                          pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����MeasurementList*/
    usRslt = NAS_LPP_EncodeMeasList(&(pstAgnssSignalMeasInfo->stGNSSMeasList),
                                       pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeAgnssList
(
    LPP_GNSS_ID_BITMAP_STRU            *pstAgnssIdnBitmap,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö����ĳ����ֶ�*/
    if((pstAgnssIdnBitmap->usGnssIdsCnt < 1) || (pstAgnssIdnBitmap->usGnssIdsCnt > 16))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_AGNSSLIST_ERROR, NAS_LPP_BIT_STRING_LEN_ERROR,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_STRING_VALUE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)((pstAgnssIdnBitmap->usGnssIdsCnt) - 1));

    /*����ö����*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, pstAgnssIdnBitmap->usGnssIdsCnt,
                             (VOS_UINT8)(pstAgnssIdnBitmap->usGNSSIDs));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_Encdoe_AgnssLocationInfo
(
    LPP_GNSS_LOCATION_INFO_STRU        *pstAgnssLocationInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����measurementReferenceTime*/
    usRslt = NAS_LPP_EncodeMeasRefTime(&(pstAgnssLocationInfo->stMeasRefTime),
                                          pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    /*����agnss-List*/
    usRslt = NAS_LPP_EncodeAgnssList(&(pstAgnssLocationInfo->stAGNSSList),
                                        pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGnssLocationServerErrorCause
(
    LPP_GNSS_LOCATION_SERVER_ERROR_CAUSE_STRU              *pstAgnssLocationServerErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    if(pstAgnssLocationServerErrorCause->enGNSSLocationServerCause > 2)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_GNSSLOCATIONSERVERERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö�ٵ���չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö��ֵ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
    (VOS_UINT8)(pstAgnssLocationServerErrorCause->enGNSSLocationServerCause));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeGnssTargetDeviceErrorCause
(
    LPP_GNSS_TARGET_DEVICE_ERROR_CAUSE_STRU                *pstAgnsTargetDeviceErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    if(pstAgnsTargetDeviceErrorCause->enGNSSTargetDeviceErrorCause > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_GNSSTARGETDEVICEERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->bitOpFineTimeAssistMeasNotPossible));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->bitOpAdrMeasNotPossibleExt));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->bitOpMultiFreqMeasNotPossibleExt));

    /*����ö�ٵ���չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö��ֵ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstAgnsTargetDeviceErrorCause->enGNSSTargetDeviceErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_Encdoe_AgnssError
(
    LPP_GNSS_ERROR_STRU                *pstAgnssError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*����choice*/
    if(pstAgnssError->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_AGNSSERROR_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstAgnssError->ulChoice));

    switch(pstAgnssError->ulChoice)
    {
        case LPP_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
            usRslt = NAS_LPP_EncodeGnssLocationServerErrorCause(&(pstAgnssError->u.stLocationServerErrorCauses),
                                                                   pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeGnssTargetDeviceErrorCause(&(pstAgnssError->u.stTargetDeviceErrorCauses),
                                                                 pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeAgnssProvideLocation
(
    LPP_AGNSS_PROVIDE_LOCATION_INFO_STRU                   *pstAgnssProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                             usRslt = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssProvideLocation->bitOpGNSSSignalMeasInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssProvideLocation->bitOpGNSSLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstAgnssProvideLocation->bitOpGNSSError));

    /*����SignalMeasurementInformation*/
    if(NAS_LPP_SLCT == pstAgnssProvideLocation->bitOpGNSSSignalMeasInfo)
    {
        usRslt = NAS_LPP_Encdoe_AgnssSignalMeasInfo(&(pstAgnssProvideLocation->stGNSSsignalMeasInfo),
                                                      pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����LocationInformation*/
    if(NAS_LPP_SLCT == pstAgnssProvideLocation->bitOpGNSSLocationInfo)
    {
        usRslt = NAS_LPP_Encdoe_AgnssLocationInfo(&(pstAgnssProvideLocation->stGNSSLocationInfo),
                                                    pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����Error*/
    if(NAS_LPP_SLCT == pstAgnssProvideLocation->bitOpGNSSError)
    {
        usRslt = NAS_LPP_Encdoe_AgnssError(&(pstAgnssProvideLocation->stGNSSError),
                                             pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeEarfcnRefV9a0
(
    LPP_ARFCN_VALUE_EUTRA_V9A0_STRU    *pstArfcnValueEutranV9a0,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����ARFCN-ValueEUTRA-v9a0*/
    if((pstArfcnValueEutranV9a0->ulArfcnValueEUTRAv9a0 < 65536)
    || (pstArfcnValueEutranV9a0->ulArfcnValueEUTRAv9a0 > 262143))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EARFCNREFV9A0_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE, *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 18,
                                 (VOS_UINT32)((pstArfcnValueEutranV9a0->ulArfcnValueEUTRAv9a0) - 65536));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeArfcnValueEutran
(
    LPP_ARFCN_VALUE_EUTRA_STRU         *pstArfcnValueEutran,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����ARFCN-ValueEUTRA-v9a0*/
    if(pstArfcnValueEutran->ulArfcnValueEUTRA > 65535)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ARFCNVALUEEUTRAN_ERROR,
                                 NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 16, pstArfcnValueEutran->ulArfcnValueEUTRA);

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeReferenceQuality
(
    LPP_OTDOA_MEAS_QUALITY_STRU        *pstOtdoaRefQuality,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaRefQuality->bitOpErrorNumSampiles));

    /*����error-Resolution*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstOtdoaRefQuality->ucErrorResolution));

    /*����error-Value*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5,
                             (VOS_UINT8)(pstOtdoaRefQuality->ucErrorValuse));

    /*����error-NumSamples*/
    if(NAS_LPP_SLCT == pstOtdoaRefQuality->bitOpErrorNumSampiles)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                                 (VOS_UINT8)(pstOtdoaRefQuality->ucErrorNumSamples));
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeNeighbourMeasElement
(
    LPP_NEIGHBOUR_MEAS_ELEMENT_STRU    *pstNeighbourMeasElement,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt                  = 0;
    VOS_UINT32                          ulMeasInfoLV            = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpNeighbourMeasElementExt));

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpCellGlobalIdNeighbour));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpArfcnValueEutra));

    /*����physCellIdNeighbour*/
    if(pstNeighbourMeasElement->ulPhysCellIdNeighbor > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NEIGHBOURMEASELEMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9,
                                  pstNeighbourMeasElement->ulPhysCellIdNeighbor);

    /*����cellGlobalIdRef*/
    if(NAS_LPP_SLCT == pstNeighbourMeasElement->bitOpCellGlobalIdNeighbour)
    {
        usRslt = NAS_LPP_EncodeECGI(&(pstNeighbourMeasElement->stCellGlobalIdNeighbour),
                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����earfcnRef*/
    if(NAS_LPP_SLCT == pstNeighbourMeasElement->bitOpArfcnValueEutra)
    {
        usRslt = NAS_LPP_EncodeArfcnValueEutran(&(pstNeighbourMeasElement->stEarfcnNeighbour),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����rstd*/
    if(pstNeighbourMeasElement->ulRstd > 12711)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NEIGHBOURMEASELEMENT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 14, pstNeighbourMeasElement->ulRstd);

    /*����rstd-Quality*/
    usRslt = NAS_LPP_EncodeReferenceQuality(&(pstNeighbourMeasElement->stRstdQuality),
                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    if(NAS_LPP_NO_SLCT == pstNeighbourMeasElement->bitOpNeighbourMeasElementExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*������չ���L-1*/
    /*Ϊʲô����������0��ȥ�أ���Ϊ��ǰ��չ��ļ�����1������ֵ��L-1����0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 0);

    /*������չ���option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstNeighbourMeasElement->bitOpArfcnValueEutraV9a0));

    if(NAS_LPP_SLCT == pstNeighbourMeasElement->bitOpArfcnValueEutraV9a0)
    {
        /*����confidenceSupport ��L+V, ����ռ��3��byte�� �������ݱ�ʾռ�ö��ٸ�byte*/
        ulMeasInfoLV = 3;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulMeasInfoLV);
        /*����[[]]�е�option��*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstNeighbourMeasElement->stEarfcnNeighbourV9a0.bitOpARFCNValueEutraV9A0));
        usRslt = NAS_LPP_EncodeEarfcnRefV9a0(&(pstNeighbourMeasElement->stEarfcnNeighbourV9a0),
                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }

        /*�������λ*/
        /*���λ�ı����ܹ�ռ��24��bit����������ռ����18��bit�� 1��bit��option������5��bit������Ҫ����bit*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)(ulMeasInfoLV*8 - 18 - 1), 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeNeighbourMeasList
(
    LPP_NEIGHBOUR_MEAS_LIST_STRU       *pstNeighbourMeasList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16 usRslt = 0;
    VOS_UINT32 ulLoop = 0;

    /*�������ֵ*/
    if((pstNeighbourMeasList->ulNeighbourMeasListCnt < 1)
    || (pstNeighbourMeasList->ulNeighbourMeasListCnt > 24))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_NEIGHBOURMEASLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 5,
                              (VOS_UINT8)((pstNeighbourMeasList->ulNeighbourMeasListCnt) - 1));

    /*������Ϣʵ��*/
    for(ulLoop = 0; ulLoop < pstNeighbourMeasList->ulNeighbourMeasListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodeNeighbourMeasElement(&(pstNeighbourMeasList->astNeighbourMeasListArray[ulLoop]),
                                                       pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeOtdoaSignalMeasInfo
(
    LPP_OTDOA_SIGNAL_MEAS_INFO_STRU    *pstOtdoaSignalMeasInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulMeasInfoLV    = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpOtdoaSignalMeasInfoExt));

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpCellGlobalIdRef));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpArfcnValueEutra));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpRefQuality));

    /*����systemFrameNumber*/
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, pstOtdoaSignalMeasInfo->usSystemFrameNumber);

    /*����physCellIdRef*/
    if(pstOtdoaSignalMeasInfo->usPhysCellIdRef > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_OTDOASIGNALMEASINFO_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstOtdoaSignalMeasInfo->usPhysCellIdRef);

    /*����cellGlobalIdRef*/
    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpCellGlobalIdRef)
    {
        usRslt = NAS_LPP_EncodeECGI(&(pstOtdoaSignalMeasInfo->stCellGlobalIdRef),
                                       pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����earfcnRef*/
    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpArfcnValueEutra)
    {
        usRslt = NAS_LPP_EncodeArfcnValueEutran(&(pstOtdoaSignalMeasInfo->stEarfcnRef),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����referenceQuality*/
    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpRefQuality)
    {
        usRslt = NAS_LPP_EncodeReferenceQuality(&(pstOtdoaSignalMeasInfo->stReferenceQuality),
                                                   pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����neighbourMeasurementList*/
    usRslt = NAS_LPP_EncodeNeighbourMeasList(&(pstOtdoaSignalMeasInfo->stNeighbourMeasList),
                                                pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    if(NAS_LPP_NO_SLCT == pstOtdoaSignalMeasInfo->bitOpOtdoaSignalMeasInfoExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*������չ���L-1*/
    /*Ϊʲô����������0��ȥ�أ���Ϊ��ǰ��չ��ļ�����1������ֵ��L-1����0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 0);

    /*������չ���option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0));

    if(NAS_LPP_SLCT == pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0)
    {
        /*����confidenceSupport ��L+V, ����ռ��3��byte�� �������ݱ�ʾռ�ö��ٸ�byte*/
        ulMeasInfoLV = 3;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulMeasInfoLV);
        /*����[[]]�е�option��*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaSignalMeasInfo->bitOpArfcnValueEutraV9a0));
        usRslt = NAS_LPP_EncodeEarfcnRefV9a0(&(pstOtdoaSignalMeasInfo->stEarfcnRefV9a0),
                                                pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }


        /*�������λ*/
        /*���λ�ı����ܹ�ռ��24��bit����������ռ����18��bit�� 1��bit��option������5��bit������Ҫ����bit*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 5, 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeOtdoaLocationServerErrorCause
(
    LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_STRU             *pstOtdoaLocationServerErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    if(pstOtdoaLocationServerErrorCause->enOtdoaLocationServerErrorCause > 2)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_OTDOALOCATIONSERVERERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö�ٵ���չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö��ֵ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstOtdoaLocationServerErrorCause->enOtdoaLocationServerErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeOtdoaTargetDeviceErrorCause
(
    LPP_OTDOA_TARGET_DEVICE_ERROR_CAUSE_STRU               *pstOtdoaTargetDeviceErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    if(pstOtdoaTargetDeviceErrorCause->enOtoaTargetDeviceErrorCause > 4)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_OTDOATARGETDEVICEERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR, *pusBitPos, __LINE__,
                                 pstOtdoaTargetDeviceErrorCause->enOtoaTargetDeviceErrorCause);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö�ٵ���չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö��ֵ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 3,
                             (VOS_UINT8)(pstOtdoaTargetDeviceErrorCause->enOtoaTargetDeviceErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeOtdoaError
(
    LPP_OTDOA_ERROR_STRU               *pstOtdoaError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt      = 0;

    /*����choice*/
    if(pstOtdoaError->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_OTDOAERROR_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaError->ulChoice));

    switch(pstOtdoaError->ulChoice)
    {
        case LPP_OTDOA_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
            usRslt = NAS_LPP_EncodeOtdoaLocationServerErrorCause(&(pstOtdoaError->u.stLocationServerErrorCauses),
                                                                    pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeOtdoaTargetDeviceErrorCause(&(pstOtdoaError->u.stTargetDeviceErrorCauses),
                                                                  pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeOtdoaProvideLocation
(
    LPP_OTDOA_PROVIDE_LOCATION_INFO_STRU                   *pstOtdoaProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaProvideLocation->bitOpOtdoaSignalMeasInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstOtdoaProvideLocation->bitOpOtdoaError));

    /*����otdoaSignalMeasementInformation*/
    if(NAS_LPP_SLCT == pstOtdoaProvideLocation->bitOpOtdoaSignalMeasInfo)
    {
        usRslt = NAS_LPP_EncodeOtdoaSignalMeasInfo(&(pstOtdoaProvideLocation->stOtdoaSignalMeasInfo),
                                                      pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����otdoaerror*/
    if(NAS_LPP_SLCT == pstOtdoaProvideLocation->bitOpOtdoaError)
    {
        usRslt = NAS_LPP_EncodeOtdoaError(&(pstOtdoaProvideLocation->stOtdoaError),
                                             pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodePrimaryCellMeasuredRslt
(
    LPP_MEAS_RESULT_ELEMENT_STRU       *pstMeasRsltElment,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulMeasInfoLV    = 0;

    /*������չ��־λ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpMeasResultElementExt));

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpCellGlobalId));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpSystemFrameNumber));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpRsrpResult));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpRsrqResult));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstMeasRsltElment->bitOpUeRxTxTimeDiff));

    /*����physCellIdRef*/
    if(pstMeasRsltElment->ulPhyCellId > 503)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
    }
    NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 9, pstMeasRsltElment->ulPhyCellId);

    /*����cellGlobalId*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpCellGlobalId)
    {
        usRslt = NAS_LPP_EncodeCellGlobalIdEuranAndUtran(&(pstMeasRsltElment->stCellGloId),
                                                            pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����earfcnRef*/
    usRslt = NAS_LPP_EncodeArfcnValueEutran(&(pstMeasRsltElment->stArfcnEutra),
                                               pusBitPos, pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }


    /*����systemFrameNumber*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpSystemFrameNumber)
    {
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 10, pstMeasRsltElment->usSystemFrameNumber);
    }

    /*����rsrp-Result*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpRsrpResult)
    {
        if(pstMeasRsltElment->ucRsrpResult > 97)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, (VOS_UINT8)(pstMeasRsltElment->ucRsrpResult));
    }

    /*����rsrq-Result*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpRsrqResult)
    {
        if(pstMeasRsltElment->ucRsrqResult > 34)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 6, (VOS_UINT8)(pstMeasRsltElment->ucRsrqResult));
    }

    /*����ue-RxTxTimeDiff*/
    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpUeRxTxTimeDiff)
    {
        if(pstMeasRsltElment->ulUeRxTxTimeDiff > 4095)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_PRIMARYCELLMEASUREDRSLT_ERROR, NAS_LPP_INTEGER_VALUE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_VALUE_ERROR_INTEGER_VALUE_ERROR;
        }
        NAS_LPP_EncodeEncodeLongData(pucEncodeOutMsg, pusBitPos, 12, pstMeasRsltElment->ulUeRxTxTimeDiff);
    }

    if(NAS_LPP_NO_SLCT == pstMeasRsltElment->bitOpMeasResultElementExt)
    {
        return NAS_LPP_ENCODE_SUCC;
    }

    /*������չ���L-1*/
    /*Ϊʲô����������0��ȥ�أ���Ϊ��ǰ��չ��ļ�����1������ֵ��L-1����0*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 7, 0);

    /*������չ���option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstMeasRsltElment->bitOpArfcnEutraV9a0));

    if(NAS_LPP_SLCT == pstMeasRsltElment->bitOpArfcnEutraV9a0)
    {
        /*����confidenceSupport ��L+V, ����ռ��3��byte�� �������ݱ�ʾռ�ö��ٸ�byte*/
        ulMeasInfoLV = 3;
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, (VOS_UINT8)ulMeasInfoLV);
        /*����[[]]�е�option��*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstMeasRsltElment->bitOpArfcnEutraV9a0));
            usRslt = NAS_LPP_EncodeEarfcnRefV9a0(&(pstMeasRsltElment->stArfcnEutraV9a0),
                                                    pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

        /*�������λ*/
        /*���λ�ı����ܹ�ռ��24��bit����������ռ����18��bit�� 1��bit��option������5��bit������Ҫ����bit*/
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (VOS_UINT16)(ulMeasInfoLV*8 - 18 - 1), 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeMeasRsltList
(
    LPP_MEAS_RESULT_LIST_STRU          *pstMeasRsltList,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT32                          ulLoop          = 0;

    /*�������ֵ*/
    if((pstMeasRsltList->ulMeasResultsListCnt < 1) || (pstMeasRsltList->ulMeasResultsListCnt > 32))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_MEASRSLTLIST_ERROR, NAS_LPP_SEQUENCE_OF_NUM_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_SEQUENCE_OF_LEN_ERROR;
    }
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 5,
                              (VOS_UINT8)((pstMeasRsltList->ulMeasResultsListCnt) - 1));

    /*������Ϣʵ��*/
    for(ulLoop = 0; ulLoop < pstMeasRsltList->ulMeasResultsListCnt; ulLoop++)
    {
        usRslt = NAS_LPP_EncodePrimaryCellMeasuredRslt(&(pstMeasRsltList->astMeasResultsList[ulLoop]),
                                                          pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEcellIdSignalMeasInfo
(
    LPP_ECID_SIGNAL_MEAS_INFO_STRU     *pstEcellIdSignalMeasInfo,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstEcellIdSignalMeasInfo->bitOpPrimaryCellMeasRslt));

    /*����primaryCellMeasuredResults*/
    if(NAS_LPP_SLCT == pstEcellIdSignalMeasInfo->bitOpPrimaryCellMeasRslt)
    {
        usRslt = NAS_LPP_EncodePrimaryCellMeasuredRslt(&(pstEcellIdSignalMeasInfo->stPrimaryCellMeasResult),
                                                          pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����measuredResultsList*/
    usRslt = NAS_LPP_EncodeMeasRsltList(&(pstEcellIdSignalMeasInfo->stMeasResultList),
                                           pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEcellIdLocationServerErrorCause
(
    LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_STRU              *pstEcidLocationServerErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    if(pstEcidLocationServerErrorCause->enEcidLocatSerErrorCause > 0)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECELLIDLOCATIONSERVERERRORCAUSE_ERROR,
                                 NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö�ٵ���չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö��ֵ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstEcidLocationServerErrorCause->enEcidLocatSerErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeEcellIdTargetDeviceErrorCause
(
    LPP_ECID_TARGET_DEVICE_ERROR_CAUSE_STRU                *pstEcidTargetDeviceErrorCause,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    /*������չ��*/
    if(pstEcidTargetDeviceErrorCause->enEcidTargetDeviceErrorCause > 2)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECELLIDTARGETDEVICEERRORCAUSE_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcidTargetDeviceErrorCause->bitOpRsrpMeasNotPossible));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcidTargetDeviceErrorCause->bitOpRsrqMeasNotPossible));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcidTargetDeviceErrorCause->bitOpRxTxMeasNotPossible));

    /*����ö�ٵ���չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����ö��ֵ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                             (VOS_UINT8)(pstEcidTargetDeviceErrorCause->enEcidTargetDeviceErrorCause));

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEcellIdError
(
    LPP_ECID_ERROR_STRU                *pstEcellIdError,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*����choice*/
    if(pstEcellIdError->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ECELLIDERROR_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    /*������չ��־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstEcellIdError->ulChoice));

    switch(pstEcellIdError->ulChoice)
    {
        case LPP_ECID_LOCATION_SERVER_ERROR_CAUSE_CHOSEN:
            usRslt = NAS_LPP_EncodeEcellIdLocationServerErrorCause(&(pstEcellIdError->u.stLocationServerErrorCauses),
                                                                      pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            usRslt = NAS_LPP_EncodeEcellIdTargetDeviceErrorCause(&(pstEcellIdError->u.stTargetDeviceErrorCauses),
                                                                    pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }

            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEcellIdProvideLocation
(
    LPP_ECID_PROVIDE_LOCATION_INFO_STRU                    *pstEcellIdProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*������չ��*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*�����ѡ��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcellIdProvideLocation->bitOpEcidSignalMeasInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                                (VOS_UINT8)(pstEcellIdProvideLocation->bitOpEcidError));

    /*����ecid-SignalMeasurementInformation*/
    if(NAS_LPP_SLCT == pstEcellIdProvideLocation->bitOpEcidSignalMeasInfo)
    {
        usRslt = NAS_LPP_EncodeEcellIdSignalMeasInfo(&(pstEcellIdProvideLocation->stEcidSignalMeasInfo),
                                                        pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����ecid-Error*/
    if(NAS_LPP_SLCT == pstEcellIdProvideLocation->bitOpEcidError)
    {
        usRslt = NAS_LPP_EncodeEcellIdError(&(pstEcellIdProvideLocation->stEcidError),
                                                pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeEpduProvideLocation
(
    LPP_EPDU_PROVIDE_LOCATION_INFO_STRU                    *pstProvideLocation,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence((LPP_EPDU_SEQUENCE_STRU *)pstProvideLocation,
                                          pusBitPos,  pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return      usRslt;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeExtProvideLocationInfoR9
(
    LPP_PROVIDE_LOCATION_INFO_R9_IES_STRU                  *pstExtProLocInfoR9,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*������չ���־λ*/
    NAS_LPP_EncodeExtBit( pusBitPos,  pucEncodeOutMsg);

    /*����option*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpCommonIEsPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpAGNSSPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpOtdoaPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpEcidPRovideLocationInfo));
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1,
                             (VOS_UINT8)(pstExtProLocInfoR9->bitOpEpduSequence));

    /*����commonIesProvideLocation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpCommonIEsPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeCommonIesProvideLocation(&(pstExtProLocInfoR9->stCommonIEsPRovideLocationInfo),
                                                           pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*���� a-gnss-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpAGNSSPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeAgnssProvideLocation(&(pstExtProLocInfoR9->stAGNSSPRovideLocationInfo),
                                                       pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*���� otdoa-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpOtdoaPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeOtdoaProvideLocation(&(pstExtProLocInfoR9->stOtdoaPRovideLocationInfo),
                                                       pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*���� ecid-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpEcidPRovideLocationInfo)
    {
        usRslt = NAS_LPP_EncodeEcellIdProvideLocation(&(pstExtProLocInfoR9->stEcidPRovideLocationInfo),
                                                         pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*���� epdu-ProvideLocationInformation*/
    if(NAS_LPP_SLCT == pstExtProLocInfoR9->bitOpEpduSequence)
    {
        usRslt = NAS_LPP_EncodeEpduProvideLocation(&(pstExtProLocInfoR9->stEpduPRovideLocationInfo),
                                                      pusBitPos,  pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeExtProvideLocationInfo
(
    LPP_CRITI_EXT_PROVIDE_LOCATION_INFO_STRU               *pstExtProLocInfo,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*����choice��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2, (VOS_UINT8)(pstExtProLocInfo->ulChoice));

    switch(pstExtProLocInfo->ulChoice)
    {
        case LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeExtProvideLocationInfoR9(&(pstExtProLocInfo->u.stProLocationInfoR9),
                                                               pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}
VOS_UINT16 NAS_LPP_EncodeProvideLocInfo
(
    LPP_MESSAGE_PROVIDE_LOCATION_INFO_STRU                 *pstProLocInfo,
    VOS_UINT16                                             *pusBitPos,
    VOS_UINT8                                              *pucEncodeOutMsg
)
{
    VOS_UINT16                                              usRslt          = 0;

    /*����choice��*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstProLocInfo->ulChoice));

    switch(pstProLocInfo->ulChoice)
    {
        case LPP_C1_CRITI_EXT_PROVIDE_LOCATION_INFO_CHOSEN:
            usRslt = NAS_LPP_EncodeExtProvideLocationInfo(&(pstProLocInfo->u.stC1),
                                                             pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :
 Description     : ����
 Input           :       ��Ҫ�����LPP��Ϣ
                                     ����֮���������ܵ�BIT��
                               ����֮���ŵ�buf
 Asn             :
 CommonIEsAbort ::= SEQUENCE {
     abortCause          ENUMERATED {
         undefined,
         stopPeriodicReporting,
         targetDeviceAbort,
         networkAbort,
         ...
     }



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommonIEsAbort
(
    LPP_COMMON_IES_ABORT_STRU          *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
        /*����ö����չ��*/
        if((NAS_LPP_SLCT == pstAbortMessage->bitOpCommonIEsAbortExt)
         ||(pstAbortMessage->enCommonIesAbortCasue > 3))
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_COMMONIESABORT_ERROR,
                                     NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return      NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
        }
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, 0);
        /*����ö��ֵ*/
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 2,
                                  (VOS_UINT8)(pstAbortMessage->enCommonIesAbortCasue));
        return  NAS_LPP_ENCODE_SUCC;

}
/*****************************************************************************
 Function Name   :NAS_LPP_EncodeEpduAbort
 Description     : ����LPP_EPDU_SEQUENCE_STRU
 Input           :       ��Ҫ�����LPP��Ϣ
                                     ����֮���������ܵ�BIT��
                               ����֮���ŵ�buf
 Asn             :



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEpduAbort
(
    LPP_EPDU_SEQUENCE_STRU             *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence( pstAbortMessage, pusBitPos, pucEncodeOutMsg);
    return  usRslt;

}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeAbortR9IEs
 Description     : ����
 Input           : pstAbortMessage            ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
 Abort-r9-IEs ::= SEQUENCE {
     commonIEsAbort      CommonIEsAbort          OPTIONAL,   -- Need ON
     ...,
     epdu-Abort          EPDU-Sequence           OPTIONAL    -- Need ON
 }



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAbortR9IEs
(
    LPP_ABORT_R9_IES_STRU              *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt                  = 0;
    VOS_UINT16                          usEncodeTempLen         = 0;
    VOS_UINT16                          usCurrentBitPos         = 0;
    VOS_UINT8                           ucByteNum               = 0;
    VOS_UINT8                           ucAddtionalBitNum       = 0;

    /*������չ���־λ*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstAbortMessage->bitOpAbortR9IEsExt));

    /*����OPTIONAL���־λ*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstAbortMessage->bitOpCommonIesAbort));

    /*����ṹ������*/
    if(NAS_LPP_SLCT == pstAbortMessage->bitOpCommonIesAbort)
    {
        usRslt = NAS_LPP_EncodeCommonIEsAbort(&(pstAbortMessage->stCommonIesAbort),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstAbortMessage->bitOpAbortR9IEsExt)
    {
        return  NAS_LPP_ENCODE_SUCC;
    }
    /*������չ����� L-1*/
    /*L Ϊ 1*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 7, 0);

    /*������չ���־λ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstAbortMessage->bitOpEpduAbort));

    /*������L+V�ı��룬�ȱ������ݣ�Ȼ����㳤�ȣ��ٱ���L+V�ֽ���*/
    if(NAS_LPP_SLCT == pstAbortMessage->bitOpEpduAbort)
    {
        usCurrentBitPos = *pusBitPos;
        *pusBitPos +=8;
        usRslt = NAS_LPP_EncodeEpduAbort(&(pstAbortMessage->stEpduAbort), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        };
        usEncodeTempLen = *pusBitPos - usCurrentBitPos - 8;
        if(usEncodeTempLen / 8 > 128)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_EPDU_SEQUENCE, NAS_LPP_EPDU_SEQUENCE_LEN_ERROR, *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_EPDU_ERROR_VALUE_ERROR;
        }

        if((usEncodeTempLen % 8) == 0)
        {
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8);
        }
        else
        {
            ucAddtionalBitNum = 8 - (usEncodeTempLen % 8);
            NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, ucAddtionalBitNum, 0);
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8 + 1);
        }
        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, &(usCurrentBitPos), 8, ucByteNum);
    }

    return  NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeC1ExtAbortMessage
 Description     : ����LPP_C1_EXT_ABORT_STRU
 Input           : pstAbortMessage      ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :

 c1                      CHOICE {
                 abort-r9        Abort-r9-IEs,
                 spare3 NULL, spare2 NULL, spare1 NULL
             }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeC1ExtAbortMessage
(
    LPP_C1_EXT_ABORT_STRU              *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*����choice��*/
    /*����choice�������һ��bit��ʾ����*/
    if(pstAbortMessage->ulChoice > 3)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_C1EXTABORTMESSAGE_ERROR,
                                 NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 2,
                            ((VOS_UINT8)(pstAbortMessage->ulChoice)));

    switch(pstAbortMessage->ulChoice)
    {
        case LPP_C1_CRITI_EXT_ABORT_R9_CHOSEN:
            usRslt = NAS_LPP_EncodeAbortR9IEs(&(pstAbortMessage->u.stAbortR9),
                                                 pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeExtAbortMessage
 Description     : ����LPP_CRIT_EXT_ABORT_STRU
 Input           : pstAbortMessage      ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
         criticalExtensions      CHOICE {
                     c1                      CHOICE {
                         abort-r9        Abort-r9-IEs,
                         spare3 NULL, spare2 NULL, spare1 NULL
                     },
                     criticalExtensionsFuture    SEQUENCE {}
                 }
             }
 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeExtAbortMessage(
                                LPP_CRIT_EXT_ABORT_STRU                    *pstAbortMessage,
                                VOS_UINT16                                  *pusBitPos,
                                VOS_UINT8                                   *pucEncodeOutMsg)
{
    VOS_UINT16       usRslt = 0;

    /*����choice��*/
    /*����choice�������һ��bit��ʾ����*/
    if(pstAbortMessage->ulChoice > 1)
    {
        NAS_LPP_ENCODE_WARNING;
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_EXTABORTMESSAGE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ((VOS_UINT8)(pstAbortMessage->ulChoice)));

    switch(pstAbortMessage->ulChoice)
    {
        case LPP_CRITI_EXT_ABORT_CHOSEN:
            usRslt = NAS_LPP_EncodeC1ExtAbortMessage(&(pstAbortMessage->u.stAbortExtC1),
                                                        pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeAbortMessage
 Description     : ����LPP_MESSAGE_ABORT_STRU
 Input           : pstProvideCapabilty      ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :
         Abort ::= SEQUENCE {
                 criticalExtensions      CHOICE {
                     c1                      CHOICE {
                         abort-r9        Abort-r9-IEs,
                         spare3 NULL, spare2 NULL, spare1 NULL
                     },
                     criticalExtensionsFuture    SEQUENCE {}
                 }
             }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeAbortMessage
(
    LPP_MESSAGE_ABORT_STRU             *pstAbortMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    usRslt = NAS_LPP_EncodeExtAbortMessage(&(pstAbortMessage->stC1), pusBitPos,pucEncodeOutMsg);
    if(NAS_LPP_ENCODE_SUCC != usRslt)
    {
        return  usRslt;
    };
    return  NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :
 Description     : ����
 Input           :       ��Ҫ�����LPP��Ϣ
                                     ����֮���������ܵ�BIT��
                               ����֮���ŵ�buf
 Asn             :
 CommonIEsError ::= SEQUENCE {
     errorCause      ENUMERATED {
         undefined,
         lppMessageHeaderError,
         lppMessageBodyError,
         epduError,
         incorrectDataValue,
         ...
     }



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeCommonIEsError
(
    LPP_COMMON_IES_ERROR_STRU          *pstErrorMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    /*����ö����չ��*/
    if((NAS_LPP_SLCT == pstErrorMessage->bitOpCommonIEsErrorExt)
     ||(pstErrorMessage->enCommonIesErrorCasue > 4))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_COMMONIESERROR_ERROR, NAS_LPP_ENUM_OUT_OF_RANGE_ERROR,
                                *pusBitPos, __LINE__, 0);
        return      NAS_LPP_ENCODE_MSG_VALUE_ERROR_ENUM_VALUE_ERROR;
    }

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, 0);
    /*����ö��ֵ*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 3,
                              (VOS_UINT8)(pstErrorMessage->enCommonIesErrorCasue));
    return  NAS_LPP_ENCODE_SUCC;
}
/*****************************************************************************
 Function Name   :
 Description     : ����
 Input           :       ��Ҫ�����LPP��Ϣ
                                     ����֮���������ܵ�BIT��
                               ����֮���ŵ�buf
 Asn             :



 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeEpduError
(
    LPP_EPDU_SEQUENCE_STRU             *pstErrorMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    usRslt = NAS_LPP_EncodeEPDUSequence( pstErrorMessage, pusBitPos, pucEncodeOutMsg);
    return  usRslt;

}

/*****************************************************************************
 Function Name   :NAS_LPP_EncodeErrorR9IEs
 Description     : ����LPP_ERROR_R9_STRU
 Input           :       ��Ҫ�����LPP��Ϣ
                                     ����֮���������ܵ�BIT��
                               ����֮���ŵ�buf
 Asn             :

 Error-r9-IEs ::= SEQUENCE {
         commonIEsError      CommonIEsError          OPTIONAL,   -- Need ON
         ...,
         epdu-Error          EPDU-Sequence           OPTIONAL    -- Need ON
     }


 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeErrorR9IEs
(
    LPP_ERROR_R9_STRU                  *pstErrorMessage,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt              = 0;
    VOS_UINT16                          usEncodeTempLen     = 0;
    VOS_UINT16                          usCurrentBitPos     = 0;
    VOS_UINT8                           ucByteNum           = 0;
    VOS_UINT8                           ucAddtionalBitNum   = 0;

    /*������չ���־λ*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstErrorMessage->bitOpErrorR9IEsExt));

    /*����OPTIONAL���־λ*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg,  pusBitPos, 1,
                              (VOS_UINT8)(pstErrorMessage->bitOpCommonIesError));

    /*����ṹ������*/
    if(NAS_LPP_SLCT == pstErrorMessage->bitOpCommonIesError)
    {
        usRslt = NAS_LPP_EncodeCommonIEsError(&(pstErrorMessage->stCommonIesError),
                                                 pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        }
    }
    /*������չ��*/
    if(NAS_LPP_NO_SLCT == pstErrorMessage->bitOpErrorR9IEsExt)
    {
        return  NAS_LPP_ENCODE_SUCC;
    }
    /*������չ����� L-1*/
    /*L Ϊ 1*/
    NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, pusBitPos, 7, 0);

    /*������չ���־λ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg,  pusBitPos, 1, (VOS_UINT8)(pstErrorMessage->bitOpEpduError));

    /*������L+V�ı��룬�ȱ������ݣ�Ȼ����㳤�ȣ��ٱ���L+V�ֽ���*/
    if(NAS_LPP_SLCT == pstErrorMessage->bitOpEpduError)
    {
        usCurrentBitPos = *pusBitPos;
        *pusBitPos +=8;
        usRslt = NAS_LPP_EncodeEpduError(&(pstErrorMessage->stEpduError), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return  usRslt;
        };

        usEncodeTempLen = *pusBitPos - usCurrentBitPos - 8;
        if((usEncodeTempLen % 8) == 0)
        {
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8);
        }
        else
        {
            ucAddtionalBitNum = 8 - (usEncodeTempLen % 8);
            NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, ucAddtionalBitNum, 0);
            ucByteNum = (VOS_UINT8)(usEncodeTempLen / 8 + 1);
        }
        if(ucByteNum > 128)
        {
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_ERRORR9IES_ERROR, NAS_LPP_EPDU_SEQUENCE_LEN_ERROR,
                                    *pusBitPos, __LINE__, 0);
            return NAS_LPP_ENCODE_MSG_EPDU_ERROR_VALUE_ERROR;
        }

        NAS_LPP_EncodeBitsLess8( pucEncodeOutMsg, &(usCurrentBitPos), 8, ucByteNum);
    }
    return  NAS_LPP_ENCODE_SUCC;
}

/*****************************************************************************
 Function Name   : NAS_LPP_EncodeErrorMessage
 Description     : ����LPP_MESSAGE_ABORT_STRU
 Input           : pstProvideCapabilty      ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf
 Asn             :

 Error ::= CHOICE {
         error-r9                    Error-r9-IEs,
         criticalExtensionsFuture    SEQUENCE {}
     }

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.wangensheng     2015-05-15  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_EncodeErrorMessage
(
    LPP_MESSAGE_ERROR_STRU              *pstErrorMessage,
    VOS_UINT16                          *pusBitPos,
    VOS_UINT8                           *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt = 0;

    /*����choice��*/
    /*����choice�������һ��bit��ʾ����*/
    if(pstErrorMessage->ulChoice > 1)
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ERRORMESSAGE_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                *pusBitPos, __LINE__, 0);
        return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;
    }
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, ((VOS_UINT8)(pstErrorMessage->ulChoice)));

    switch(pstErrorMessage->ulChoice)
    {
        case LPP_ERROR_R9_IES_CHOSEN:
            usRslt = NAS_LPP_EncodeErrorR9IEs( &(pstErrorMessage->u.stErrorR9), pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC !=usRslt)
            {
                return  usRslt;
            }
            break;

        default:
            break;
    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeLppMsgC1
(
    LPP_SUPPORT_MESSAGE_BODY_STRU      *pstSupportLppMsgBody,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*����choice��*/
    /*16��choice�������Ҫ��4��bit��ʾ*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, (VOS_UINT8)(pstSupportLppMsgBody->ulChoice));
    /*������Ϣ��*/
    switch(pstSupportLppMsgBody->ulChoice)
    {
        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_CAPABILITIES_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideCapability(&(pstSupportLppMsgBody->u.stProvideCapabilities),
                                                        pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_PEQUEST_ASSISTANCE_DATA_CHOSEN:
            usRslt = NAS_LPP_EncodeRequestAssistData(&(pstSupportLppMsgBody->u.stRequestAssistanceData), pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_PROVIDE_LOCATION_INFO_CHOSEN:
            usRslt = NAS_LPP_EncodeProvideLocInfo(&(pstSupportLppMsgBody->u.stProvideLocationInformation),
                                                     pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ABORT_CHOSEN:
            usRslt = NAS_LPP_EncodeAbortMessage(&(pstSupportLppMsgBody->u.stAbort),
                                                   pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;
        case LPP_SUPPORT_MESSAGE_BODY_ERROR_CHOSEN:
            usRslt = NAS_LPP_EncodeErrorMessage(&(pstSupportLppMsgBody->u.stError),
                                                   pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

            /*FIXME:LIFUXIN ToDo����������������������*/

        default:
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_LPPMSGC1_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;

    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16 NAS_LPP_EncodeLppMsgBody
(
    LPP_MESSAGE_BODY_STRU              *pstLppMsgBody,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usRslt          = 0;

    /*����choice��*/
    /*����choice�������һ��bit��ʾ����*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstLppMsgBody->ulChoice));

    switch(pstLppMsgBody->ulChoice)
    {
        case LPP_C1_MESSAGE_BODY_CHOSEN:
            usRslt = NAS_LPP_EncodeLppMsgC1(&(pstLppMsgBody->u.stC1), pusBitPos, pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usRslt)
            {
                return usRslt;
            }
            break;

        case LPP_C1_MESSAGE_CLASS_EXTENSION:
            break;

        default:
            NAS_LPP_ASN_FAIL_Message(NAS_LPP_LPPMSGBODY_ERROR, NAS_LPP_CHOICE_OUT_OF_RANGE,
                                    *pusBitPos, __LINE__, 0);
            return  NAS_LPP_ENCODE_MSG_VALUE_ERROR_CHOICE_ERROR;

    }

    return NAS_LPP_ENCODE_SUCC;
}


VOS_UINT16  NAS_LPP_EncodeMessage
(
    LPP_MESSAGE_STRU                   *pstLppMsg,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT8                           ucOption        = 0;
    VOS_UINT16                          usRslt          = 0;
    VOS_UINT8                           ucAllignBit     = 0;

    if((NAS_LPP_NULL_PTR == pstLppMsg)
        || (NAS_LPP_NULL_PTR == pusBitPos)
        || (NAS_LPP_NULL_PTR == pucEncodeOutMsg))
    {
        NAS_LPP_ASN_FAIL_Message(NAS_LPP_ENCODE_MESSAGE_ERROR, NAS_LPP_EMPTY_POINT, 0, __LINE__, 0);
        return NAS_LPP_ENCODE_NULL_PTR;
    }

    /*�����������Ӽ���Ϊ0*/
    *pusBitPos = 0;

    /*�����ѡ��*/
    ucOption = (VOS_UINT8)(((pstLppMsg->bitOpLppTransactionId) << 3)
                | ((pstLppMsg->bitOpSequenceNumber) << 2)
                | ((pstLppMsg->bitOpAcknowledgement) << 1)
                | (pstLppMsg->bitOpLppMessageBody));

    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 4, ucOption);

    /*����transactionId*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpLppTransactionId)
    {
        usRslt = NAS_LPP_EncodeTransactionId(&(pstLppMsg->stTransactionId), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����endTransaction*/
    NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 1, (VOS_UINT8)(pstLppMsg->bEndTransaction));

    /*����SequenceNumber*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpSequenceNumber)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, 8, pstLppMsg->stSequenceNumber.ucSequenceNumber);
    }

    /*����acknowledgement*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpAcknowledgement)
    {
        usRslt = NAS_LPP_EncodeAcknowLedgement(&(pstLppMsg->stAcknowledgement), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*����LPP������Ϣ*/
    if(NAS_LPP_SLCT == pstLppMsg->bitOpLppMessageBody)
    {
        usRslt = NAS_LPP_EncodeLppMsgBody(&(pstLppMsg->stLppMessageBody), pusBitPos, pucEncodeOutMsg);
        if(NAS_LPP_ENCODE_SUCC != usRslt)
        {
            return usRslt;
        }
    }

    /*�������֮�󣬱�֤8bit����*/
    ucAllignBit = (*pusBitPos) % 8;
    if(0 != ucAllignBit)
    {
        NAS_LPP_EncodeBitsLess8(pucEncodeOutMsg, pusBitPos, (8 - ucAllignBit), 0);
    }

    return NAS_LPP_ENCODE_SUCC;
}


/*****************************************************************************
 Function Name   : NAS_LPP_LRrc_Encode_LocationCoordinates
 Description     : ����pstLocationCoordinates
 Input           : pstEPDU                    ��Ҫ�����LPP��Ϣ
                   pusBitPos                  ����֮���������ܵ�BIT��
                   pucEncodeOutMsg            ����֮���ŵ�buf

 Output          :
 Return          : VOS_UINT16:  NAS_LPP_CAUSE_ENCODE_CAUSE_ENUM_UINT16
 History         :
    1.WANGENSHENG      2015-07-1  Draft Enact
*****************************************************************************/
VOS_UINT16 NAS_LPP_Encode_LocationInfo
(
    MTA_LPP_LOCATION_COORDINATE_STRU   *pstLocationCoordinate,
    VOS_UINT16                         *pusBitPos,
    VOS_UINT8                          *pucEncodeOutMsg
)
{
    VOS_UINT16                          usReturnReslt;

    /*����ṹ������*/
    /*����EPDU-Identifier*/
    switch(pstLocationCoordinate->ulChoice)
    {
        case LPP_ELLIPSOID_POINT_CHOSEN:
            usReturnReslt  = NAS_LPP_EncodeEllipsoidPoint(&(pstLocationCoordinate->u.stEllipsoidPoint),
                                                             pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
            {
                return usReturnReslt;
            }
            break;

        case LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_CIRCLE_CHOSEN:
            usReturnReslt = NAS_LPP_EncodeEllipsoidPointWithUncertaintyCircle(&(pstLocationCoordinate->u.stEllipsoidPointWithUncertaintyCircle),
                                                                                 pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
            {
                return usReturnReslt;
            }
            break;

        case LPP_ELLIPSOID_POINT_WITH_UNCERTAINTY_ELLIPSE_CHOSEN:
            usReturnReslt = NAS_LPP_EncodeEllipsoidPointWithUncertaintyEllipse(&(pstLocationCoordinate->u.stEllipsoidPointWithUncertaintyEllipse),
                                                                                  pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
            {
                return usReturnReslt;
            }
            break;

        case LPP_POLYGON_CHOSEN:
            usReturnReslt = NAS_LPP_EncodePolygon(&(pstLocationCoordinate->u.stPolygon), pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
            {
                return usReturnReslt;
            }
            break;


        case LPP_ELLIPSOID_POINT_WITH_ALTITUDE_CHOSEN:
            usReturnReslt = NAS_LPP_EncodeEllipsoidPointWithaltitude(&(pstLocationCoordinate->u.stEllipsoidPointWithAltitude),
                                                                        pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
            {
                return usReturnReslt;
            }
            break;

        case LPP_ELLIPSOID_POINT_WITH_ALTITUDE_AND_UNCERTAINTY_ELLIPSOID_CHOSEN:
            usReturnReslt = NAS_LPP_EncodeEllipsoidPointWithAltitudeAndEllipoid(&(pstLocationCoordinate->u.stEllipsoidPointWithAltitudeAndUncertaintyEllipsoid), pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
            {
                return usReturnReslt;
            }
            break;

        default:
            usReturnReslt = NAS_LPP_EncodeEllipsoidArc(&(pstLocationCoordinate->u.stEllipsoidArc), pusBitPos,  pucEncodeOutMsg);
            if(NAS_LPP_ENCODE_SUCC != usReturnReslt)
            {
                return usReturnReslt;
            }
            break;
    }
    return  NAS_LPP_ENCODE_SUCC;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

