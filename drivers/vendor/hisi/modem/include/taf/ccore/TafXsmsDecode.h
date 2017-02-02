/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsDecode.h
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : TafXsmsDecode.cͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

#ifndef _TAF_XSMS_DECODE_H_
#define _TAF_XSMS_DECODE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafAppXsmsInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)


/*****************************************************************************
  2 �궨��
*****************************************************************************/

#define TAF_XSMS_MAX_DBM_SIZE                   (255)         /* DBM������󳤶ȣ�������ͷ */
#define MAX_BD_BYTE_LENGTH                      (253)
#define TAF_XSMS_MAX_SUBADDRESS_PARAM_LEN       (38)
#define TAF_XSMS_BIT_NUMBER_OF_BYTE             (8)
#define TAF_XSMS_TPDU_LEN_MAX                   (253)
#define DBM_SMS_TYPE                            (3)
#define DIGITS_OF_AUTN                          (6)
#define TAF_XSMS_VOICE_NOTIFICATION             (0x1003)
#define TAF_XSMS_TELESERVICE_CATPT              (4103) /* TIA */
#define TAF_XSMS_TELESERVICE_AGPS_NI_SMS        (65001)
#define TAF_XSMS_BD_USER_DATA_MAX_LEN           (238)
#define TAF_XSMS_BD_PURE_CONTEXT_MAX_LEN_8      (140)
#define TAF_XSMS_BD_USER_DATA_ENCODE_BIT_7      (7)
#define TAF_XSMS_BD_USER_DATA_ENCODE_BIT_8      (8)
#define TAF_XSMS_BD_USER_DATA_ENCODE_BIT_16     (16)
#define TAF_XSMS_BD_LANGUAGE_INDICATOR_ENGLISH  (0x01)
#define TAF_XSMS_BD_LANGUAGE_INDICATOR_CHINESE  (0x06)





/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 ö����    : TAF_XSMS_TL_MSG_TYPE_ENUM8
 ö��˵��  : �յ��Ķ��ŵ�����
*****************************************************************************/
enum TAF_XSMS_TL_MSG_TYPE_ENUM
{
    TAF_XSMS_TL_P2P_MSG            = 0,
    TAF_XSMS_TL_BROADCAST_MSG      = 1,
    TAF_XSMS_TL_ACK_MSG            = 2,
    TAF_XSMS_TL_MSG_TYPE_BUTT      = 3,
};

typedef VOS_UINT8 TAF_XSMS_TL_MSG_TYPE_ENUM8;

/*****************************************************************************
 ö����    : TAF_XSMS_TL_PARAMETER_ID_ENUM32
 ö��˵��  : TL���Parameter ID
*****************************************************************************/
enum TAF_XSMS_TL_PARAMETER_ID_ENUM
{

    TAF_XSMS_TL_TELESERVICE_ID         = 0,
    TAF_XSMS_TL_SERVICR_CATEGORY       = 1,
    TAF_XSMS_TL_ORIGIN_ADDR            = 2,
    TAF_XSMS_TL_ORIGIN_SUBADDR         = 3,
    TAF_XSMS_TL_DEST_ADDR              = 4,
    TAF_XSMS_TL_DEST_SUBADDR           = 5,
    TAF_XSMS_TL_BEARER_REPLY_OPTION    = 6,
    TAF_XSMS_TL_CAUSE_CODE             = 7,
    TAF_XSMS_TL_BERAER_DATA            = 8,
    TAF_XSMS_TL_PARAMETER_MAX          = 9,
    TAF_XSMS_TL_PARAMETER_ID_BUTT         = 0xff,
};

typedef VOS_UINT32 TAF_XSMS_TL_PARAMETER_ID_ENUM32;

/*****************************************************************************
 ö����    : TAF_XSMS_TL_ERROR_CLASS_ENUM8
 ö��˵��  : TL��Cause code������Error Class
*****************************************************************************/
enum TAF_XSMS_TL_ERROR_CLASS_ENUM
{
    TAF_XSMS_TL_CAUSECODE_NONE         = 0,
    TAF_XSMS_TL_CAUSECODE_RESERVED     = 1,
    TAF_XSMS_TL_CAUSECODE_TMP          = 2,
    TAF_XSMS_TL_CAUSECODE_PERMANENT    = 3,
    TAF_XSMS_TL_CAUSECODE_BUTT         = 4,
};

typedef VOS_UINT8 TAF_XSMS_TL_ERROR_CLASS_ENUM8;

/*****************************************************************************
 ö����    : TAF_XSMS_BD_MSG_TYPE_ENUM8
 ö��˵��  : BEARER DATA�����MSG_TYPE
*****************************************************************************/
enum TAF_XSMS_BD_MSG_TYPE_ENUM
{
    TAF_XSMS_BD_MSG_TYPE_DELIVER            = 1,
    TAF_XSMS_BD_MSG_TYPE_SUBMIT             = 2,
    TAF_XSMS_BD_MSG_TYPE_CANCELL            = 3,
    TAF_XSMS_BD_MSG_TYPE_DELIBER_ACK        = 4,
    TAF_XSMS_BD_MSG_TYPE_USER_ACK           = 5,
    TAF_XSMS_BD_MSG_TYPE_READ_ACK           = 6,

    TAF_XSMS_BD_MSG_TYPE_BUTTS
};

typedef VOS_UINT8 TAF_XSMS_BD_MSG_TYPE_ENUM8;


/*****************************************************************************
 ö����    : TAF_XSMS_TL_CAUSE_CODE_ENUM8
 ö��˵��  :  TL��Cause code�����ķ����Ĵ����ԭ�����
*****************************************************************************/
enum TAF_XSMS_TL_CAUSE_CODE_ENUM
{
  /* 1.��������:  */
    TAF_XSMS_TL_ADDRESS_VACANT                        = 0, /* �������⣬�ٵ�ַ.        */
    TAF_XSMS_TL_ADDRESS_TRANSLATION_FAILURE           = 1, /* �������⣬��ַ�������   */
    TAF_XSMS_TL_NETWORK_RESOURCE_SHORTAGE             = 2, /* �������⣬������Դ��ȱ   */
    TAF_XSMS_TL_NETWORK_FAILURE                       = 3, /* �������⣬����ʧ��       */
    TAF_XSMS_TL_INVALID_TELESERVICE_ID                = 4, /* �������⣬����ȷ��Teleservice ID*/
    TAF_XSMS_TL_OTHER_NETWORK_PROBLEM                 = 5, /* ������������.            */
    TAF_XSMS_TL_OTHER_NETWORK_PROBLEM_MORE_FIRST      = 6, /* ��������������ʼֵ.      */


  /* 6 �� 31 ֮���ֵ������ TAF_XSMS_TL_OTHER_NETWORK_PROBLEM. */

    TAF_XSMS_TL_OTHER_NETWORK_PROBLEM_MORE_LAST       = 31, /* ��������������ʼֵ����ֵ. */

  /* 2. �ն�����:  */
    TAF_XSMS_TL_NO_PAGE_RESPONSE                      = 32, /* �ն����⣬Ѱ��û��Ӧ��      */
    TAF_XSMS_TL_DESTINATION_BUSY                      = 33, /* �ն�����, Ŀ��æ            */
    TAF_XSMS_TL_NO_ACK                                = 34, /* �ն�����, û��ACK           */
    TAF_XSMS_TL_DESTINATION_RESOURCE_SHORTAGE         = 35, /* �ն�����, Ŀ����Դ��ȱ      */
    TAF_XSMS_TL_SMS_DELIVERY_POSTPONED                = 36, /* �ն�����, �����ӳ�Ͷ��      */
    TAF_XSMS_TL_DESTINATION_OUT_OF_SERVICE            = 37, /* �ն�����, Ŀ���޷���        */
    TAF_XSMS_TL_DESTINATION_NO_LONGER_AT_THIS_ADDRESS = 38, /* �ն�����, Ŀ���ն��ǿպ�?  */
    TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM                = 39, /* �ն�����, ����              */
    TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM_MORE_FIRST     = 40, /* �ն�����, ������ʼֵ        */

  /* 40��47֮���ֵ������ TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM. */

    TAF_XSMS_TL_OTHER_TERMINAL_PROBLEM_MORE_LAST      = 47, /* �ն�����, ��������ֵ        */
    TAF_XSMS_TL_SMS_DELIVERY_POSTPONED_MORE_FIRST     = 48, /* �ն�����, �ӳ�Ͷ����ʼֵ    */
    TAF_XSMS_TL_SMS_DELIVERY_POSTPONED_MORE_LAST      = 63, /* �ն�����, �ӳ�Ͷ�ݽ���ֵ    */

  /* 3. ��Ƶ�ӿ�����  */
    TAF_XSMS_TL_RADIO_IF_RESOURCE_SHORTAGE            = 64, /* ��Ƶ�ӿ����⣬�ӿ���Դ��ȱ  */
    TAF_XSMS_TL_RADIO_IF_INCOMPATIBLE                 = 65, /* ��Ƶ�ӿ����⣬��ƥ��        */
    TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM                = 66, /* ��Ƶ�ӿ����⣬����          */
    TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM_MORE_FIRST     = 67, /* ��Ƶ�ӿ����⣬������ʼֵ    */

  /* 67 �� 95 ������ TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM. */

    TAF_XSMS_TL_OTHER_RADIO_IF_PROBLEM_MORE_LAST      = 95, /* ��Ƶ�ӿ����⣬��������ֵ    */

  /* D. һ������  */
    TAF_XSMS_TL_UNEXPECTED_PARM_SIZE                  = 96,  /* ������С����               */
    TAF_XSMS_TL_SMS_ORIGINATION_DENIED                = 97,  /* ����Դ��ַ�ܾ�             */
    TAF_XSMS_TL_SMS_TERMINATION_DENIED                = 98,  /* �����ն˾ܾ�               */
    TAF_XSMS_TL_SUPPL_SERVICE_NOT_SUPPORTED           = 99,  /* ����֧��?               */
    TAF_XSMS_TL_SMS_NOT_SUPPORTED                     = 100, /* ��֧�ֶ���                 */
    TAF_XSMS_TL_RESERVED_101                          = 101, /* ������ֵΪ101              */
    TAF_XSMS_TL_MISSING_EXPECTED_PARM                 = 102, /* ȱ��ϣ���еĲ���           */
    TAF_XSMS_TL_MISSING_MANDATORY_PARM                = 103, /* ȱ�ٱ����еĲ���           */
    TAF_XSMS_TL_UNRECOGNIZED_PARM_VALUE               = 104, /* �޷�ʶ��Ĳ���ֵ           */
    TAF_XSMS_TL_UNEXPECTED_PARM_VALUE                 = 105, /* ����ֵ����ȷ               */
    TAF_XSMS_TL_USER_DATA_SIZE_ERROR                  = 106, /* User Data ��������ȷ       */
    TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS                = 107, /* ����һ������               */
    TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS_MORE_FIRST     = 108, /* ����һ�����⣬��ʼֵ       */

  /* 108 �� 255 ������ TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS */

    TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS_MORE_LAST      = 255, /* ����һ�����⣬����ֵ       */

} ;

typedef VOS_UINT8 TAF_XSMS_TL_CAUSE_CODE_ENUM8;

/*****************************************************************************
 ö����    : TAF_XSMS_BD_PARAMETER_ID_ENUM8
 ö��˵��  :  Bearer Data�� SubParameter ID
*****************************************************************************/
enum TAF_XSMS_BD_PARAMETER_ID_ENUM
{

    TAF_XSMS_BD_MESSAGE_IDENTIFIER                 = 0,
    TAF_XSMS_BD_USER_DATA                          = 1,
    TAF_XSMS_BD_USER_RESPONESE_CODE                = 2,
    TAF_XSMS_BD_MESSAGE_CENTER_TIME_STAMP          = 3,
    TAF_XSMS_BD_VALIDITY_PERIOD_ABSOLUTE           = 4,
    TAF_XSMS_BD_VALIDITY_PERIOD_RELATIVE           = 5,
    TAF_XSMS_BD_DEFERRED_DELIVERY_TIME_ABSOLUTE    = 6,
    TAF_XSMS_BD_DEFERRED_DELIVERY_TIME_RELATIVE    = 7,
    TAF_XSMS_BD_PRIORITY_INDICATOR                 = 8,
    TAF_XSMS_BD_PRIVACY_INDICATOR                  = 9,
    TAF_XSMS_BD_REPLY_OPTION                       = 10,
    TAF_XSMS_BD_NUMBER_OF_MESSAGE                  = 11,
    TAF_XSMS_BD_ALERT_ON_MESSAGE_DELIVERY          = 12,
    TAF_XSMS_BD_LANGUAGE_INDICATOR                 = 13,
    TAF_XSMS_BD_CALL_BACK_NUMBER                   = 14,
    TAF_XSMS_BD_MESSAGE_DISPLAY_MODE               = 15,
    TAF_XSMS_BD_MULTIPLE_ENCODING_USER_DTAT        = 16,
    TAF_XSMS_BD_SERVICE_CATEFORY_PROGRAM_DATA      = 17,
    TAF_XSMS_BD_SERVICE_CATEFORY_PROGRAM_RESULTS   = 18,
    TAF_XSMS_BD_MESSAGE_STATUS                     = 19,
    TAF_XSMS_BD_PARAMETER_VALUE_MAX                = 19,
    TAF_XSMS_TL_PARAMETER_BUTT                     = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_BD_PARAMETER_ID_ENUM8;


/*****************************************************************************
 ö����    : TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM
 ö��˵��  : MSG_ENCODE ���� CR1001 Table 9.1-1
*****************************************************************************/
enum TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM
{
    TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET             = 0,
    TAF_XSMS_USER_DATA_MSG_ENCODE_EPM               = 1,
    TAF_XSMS_USER_DATA_MSG_ENCODE_ASCII_7           = 2,    /* 7 BITS*/
    TAF_XSMS_USER_DATA_MSG_ENCODE_IA5               = 3,    /* 7 BITS*/
    TAF_XSMS_USER_DATA_MSG_ENCODE_UNICODE           = 4,
    TAF_XSMS_USER_DATA_MSG_ENCODE_JIS               = 5,
    TAF_XSMS_USER_DATA_MSG_ENCODE_KOREAN            = 6,
    TAF_XSMS_USER_DATA_MSG_ENCODE_HEBREW            = 7,
    TAF_XSMS_USER_DATA_MSG_ENCODE_LATIN             = 8,
    TAF_XSMS_USER_DATA_MSG_ENCODE_GSM_7             = 9,    /* 7 BITS*/
    TAF_XSMS_USER_DATA_MSG_ENCODE_GSM_DCS           = 10,
    TAF_XSMS_USER_DATA_MSG_ENCODE_BUTT
};

typedef VOS_UINT8 TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  7 STRUCT����
*****************************************************************************/
/*****************************************************************************
 �ṹ��    :TAF_XSMS_CAUSE_CODE_STRU
 �ṹ˵��  :TL��Cause Code�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucParameterLen;
    VOS_UINT8                           ucReplySeq;
    TAF_XSMS_TL_ERROR_CLASS_ENUM8      enErrorClass;
    TAF_XSMS_TL_CAUSE_CODE_ENUM8       enCauseCode;
}TAF_XSMS_CAUSE_CODE_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_MSG_ID_STRU
 �ṹ˵��  :MSG_ID�ṹ��
*****************************************************************************/
typedef struct
{
    TAF_XSMS_BD_MSG_TYPE_ENUM8          enMsgType;
    VOS_UINT8                           ucIsHeadIndExist;
    VOS_UINT16                          usMsgID;
}TAF_XSMS_MSG_ID_STRU;


/*****************************************************************************
 �ṹ��    :TAF_XSMS_TL_FLAG_BIT_STRU
 �ṹ˵��  :TL��������ڱ�־λ��λ���ʾ
*****************************************************************************/
typedef struct
{
    VOS_UINT16                          bIsTelesrvIdPresent:1;
    VOS_UINT16                          bIspSrvCategoryPresent:1;
    VOS_UINT16                          bIsOpOrigAddrPresent:1;
    VOS_UINT16                          bIsOpOrigSubAddrPresent:1;
    VOS_UINT16                          bIsOpDstAddrPresent:1;
    VOS_UINT16                          bIsOpDstSubAddrPresent:1;
    VOS_UINT16                          bIsOpBearReplyOpPresent:1;
    VOS_UINT16                          bIsOpBearDataPresent:1;
    VOS_UINT16                          bIsOpCauseCodePresent:1;
    VOS_UINT16                          bIsOpIsPRL:1;
    VOS_UINT16                          bIsOpIsPPDownload:1;
    VOS_UINT16                          bIsOp_Reserved:5;
}TAF_XSMS_TL_FLAG_BIT_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_DATA_BURST_MSG_STRU
 �ṹ˵��  :Data Burst Message �ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucBurstType;
    VOS_UINT8                           ucMsgNum;
    VOS_UINT8                           ucNumFields;
    VOS_UINT8                           ucNumMsgs;
    VOS_UINT8                           aucData[255];
    VOS_UINT8                           ucRsv;
}TAF_XSMS_DATA_BURST_MSG_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_TRANSPORT_MESSAGE_STRU
 �ṹ˵��  :Transport Layer�ṹ��
*****************************************************************************/
typedef struct
{

    union
    {
        VOS_UINT16                      ausValue[1];
        TAF_XSMS_TL_FLAG_BIT_STRU      stTLBitPresentFlag;
    }unPresentFlag;
    VOS_UINT8                           ucBearReplySeqNum;
    TAF_XSMS_TL_MSG_TYPE_ENUM8         enMessageType;
    TAF_XSMS_MESSAGE_STRU              stMessage;
    TAF_XSMS_CAUSE_CODE_STRU           stCauseCode;

}TAF_XSMS_TRANSPORT_MESSAGE_STRU;


typedef VOS_UINT32 TAF_XSMS_PARAMETER_DECODE_FUNC(VOS_UINT8 *pucData, VOS_UINT8 *pucBytePos,TAF_XSMS_TRANSPORT_MESSAGE_STRU *pstTLStru);

/*����ID ��Ӧ��ͬ�ĺ���ָ��*/
typedef struct
{
    TAF_XSMS_TL_PARAMETER_ID_ENUM32     enParaId;           /*�������͵�ֵ*/
    TAF_XSMS_PARAMETER_DECODE_FUNC     *pstParaDecodeFunc;  /*�������͵Ľ��뺯��ָ��*/
}TAF_XSMS_PARM_DECODE_FUNC_STRU;


/*****************************************************************************
 �ṹ��    :TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU
 �ṹ˵��  :Bearer data �����ṹ�壬���ڵ���Bear Date�Ӳ���λ��
*****************************************************************************/
typedef struct
{
    TAF_XSMS_BD_PARAMETER_ID_ENUM8      enParamHeader;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucBytePos;
}TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU;


/*****************************************************************************
 �ṹ��    :TAF_XSMS_BD_MSG_DISPLAY_MODE_STRU
 �ṹ˵��  :Bearer data �Ӳ���Message Display Mode�Ľṹ��
*****************************************************************************/
typedef struct
{
    TAF_XSMS_BD_PARAMETER_ID_ENUM8      enParamHeader;
    VOS_UINT8                           ucLen;
    VOS_UINT8                           ucMsgDisplayMode;
    VOS_UINT8                           ucMsgReserverd;
}TAF_XSMS_BD_MSG_DISPLAY_MODE_STRU;

/*****************************************************************************
 �ṹ��    :TAF_XSMS_BD_MSG_USER_DATA_STRU
 �ṹ˵��  :Bearer data �Ӳ���user data�Ľṹ��
*****************************************************************************/
typedef struct
{
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType;
    VOS_UINT8                           ucMsgType;
    VOS_UINT8                           ucNumFields;
    VOS_UINT8                           ucRcv;
    VOS_UINT8                           aucUserData[256];
}TAF_XSMS_BD_MSG_USER_DATA_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_VOID TAF_XSMS_TL_UnpackByteToBit (
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                          *pucValue,
    VOS_UINT16                          usBitPos,
    VOS_UINT8                           ucBitNum
);

extern VOS_VOID TAF_XSMS_TL_FillCauseCode(
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass,
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    VOS_UINT8                           ucReplySeq,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

);

extern VOS_VOID TAF_XSMS_TL_FillCauseCodeSeq(
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru

);

extern VOS_UINT32 TAF_XSMS_TL_DecodeTeleSrvId(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeSrvCategory(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU   *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeSubAddr(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU   *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeBearReplyOption(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);


extern VOS_UINT32 TAF_XSMS_TL_DecodeCauseCode(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_TL_DecodeBearData(
    VOS_UINT8                          *pucData,
    VOS_UINT8                          *pucBytePos,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLStru
);

extern VOS_UINT32 TAF_XSMS_DecodeTLRawToTLStru(
    VOS_UINT8                           ucTLRawLen,
    VOS_UINT8                          *pucTLRaw,
    TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg
);

extern VOS_UINT32  TAF_XSMS_CheckFields(TAF_XSMS_TRANSPORT_MESSAGE_STRU    *pstTLMsg);

extern VOS_VOID TAF_XSMS_FillBDShortStru(
    VOS_UINT8                                              *pucBuffer,
    VOS_UINT8                                              *pucBytePos,
    TAF_XSMS_BD_GENERAL_PARAMETER_8B_STRU                  *pstBDParamStru
);

extern VOS_VOID TAF_XSMS_IsPRL(TAF_XSMS_TRANSPORT_MESSAGE_STRU *pstTLMsg);

extern VOS_VOID TAF_XSMS_DecodeUserDataInBearerData(
    VOS_UINT32                          ulBearDataLen,  /* in */
    VOS_UINT8                          *pucBearerData,  /* in */
    VOS_UINT16                         *pusUserDataStartByte,   /* out */
    VOS_UINT16                         *pusUserDataLen, /* out ��BearerData�еĳ��ȣ���������ʵ�ʳ��� */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData     /* out */
);
extern VOS_UINT8 TAF_XSMS_GetLowBits(VOS_UINT8 ucOffset);

extern VOS_UINT32 TAF_XSMS_GetUserDataCodeBitsByMsgCode(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT8                          *pucBitNum
);

extern VOS_VOID TAF_XSMS_PressUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData
);

extern VOS_VOID TAF_XSMS_DevideLongCdmaSms(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,         /* USER DATA */
    VOS_UINT16                          usUserDataStartByte, /* in ��ԭ����BEARER DATA �п�ʼλ�� */
    VOS_UINT16                          usUserDataLen,       /* in ��ԭ����BEARER DATA �г���*/
    TAF_XSMS_MESSAGE_STRU              *pstFirstMessage,     /* ��һ����Ϣ*/
    TAF_XSMS_MESSAGE_STRU              *pstSecondMessage    /* �ڶ�����Ϣ */
);

extern VOS_VOID TAF_XSMS_DevideUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstFirstUserData,         /* USER DATA in and out */
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstSecondUserData        /* USER DATA out*/
);

extern VOS_VOID TAF_XSMS_ReplaceUserData(
    TAF_XSMS_MESSAGE_STRU              *pstMessage,
    VOS_UINT8                          *pucPressedUserData,
    VOS_UINT32                          ulPressedUserDataLen,
    VOS_UINT16                          usOldUserDataStartByte,
    VOS_UINT16                          usOldUserDataLen
);

extern VOS_VOID TAF_XSMS_GetXsmsLimitLen(
    TAF_XSMS_USER_DATA_MSG_ENCODE_ENUM8 enMsgCodeType,
    VOS_UINT16                         *pusLenLimit
);

extern VOS_VOID TAF_XSMS_EncodeMsgID(
    TAF_XSMS_MSG_ID_STRU               *pstMsgId,           /* in */
    VOS_UINT8                          *pucMsgIdLen,        /* out */
    VOS_UINT8                          *paucMsfIdData       /* out */
);

extern VOS_VOID TAF_XSMS_EncodeUserRspCode(
    VOS_UINT8                           ucUserResponseCode, /* in */
    VOS_UINT8                          *pucRepCodeLen,      /* out */
    VOS_UINT8                          *pucRepCodeData      /* out */
);

extern VOS_VOID TAF_XSMS_EncodeUserData(
    TAF_XSMS_BD_MSG_USER_DATA_STRU     *pstUserData,    /* in */
    VOS_UINT8                          *pucUserDataLen, /* out */
    VOS_UINT8                          *paucUserData    /* out */
);

extern VOS_VOID TAF_XSMS_PackBitToByte(
    VOS_UINT8                          *pucBuffer,
    VOS_UINT8                           ucValue,
    VOS_UINT8                           ucBitNum,
    VOS_UINT16                          usBitPos
);

VOS_VOID TAF_XSMS_DecodeMsgId(
    VOS_UINT32                          ulBearDataLen,
    VOS_UINT8                          *pucBearData,
    TAF_XSMS_MSG_ID_STRU               *pstMsgId
);

#endif

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

