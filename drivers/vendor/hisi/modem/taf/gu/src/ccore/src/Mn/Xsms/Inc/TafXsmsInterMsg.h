

#ifndef _TAF_XSMS_MSG_INTER_MSG_H_
#define _TAF_XSMS_MSG_INTER_MSG_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "TafAppXsmsInterface.h"
#include  "TafXsmsCtx.h"
#include  "TafXsmsDecode.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
  2 �궨��
*****************************************************************************/

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : TAF_XSMS_HOOK_MSG_TYPE_ENUM
 ö��˵��  : �ڲ���ά�ɲ���Ϣ����
*****************************************************************************/
enum TAF_XSMS_HOOK_MSG_TYPE_ENUM
{
    TAF_XSMS_HOOK_MSG_TYPE_3RD_PARTY    = 0x00,     /* _H2ASN_MsgChoice TAF_XSMS_INT_3RD_PARTY_ERR_STRU*/ /***< @sa TAF_XSMS_INT_3RD_PARTY_ERR_STRU */
    TAF_XSMS_HOOK_MSG_TYPE_MO_FSM       = 0x01,     /* _H2ASN_MsgChoice TAF_XSMS_INT_CUR_MO_FSM_STRU*/ /***< @sa TAF_XSMS_INT_CUR_MO_FSM_STRU */
    TAF_XSMS_HOOK_MSG_TYPE_MT_FSM       = 0x02,     /* _H2ASN_MsgChoice TAF_XSMS_INT_CUR_MT_FSM_STRU*/ /***< @sa TAF_XSMS_INT_CUR_MT_FSM_STRU */
    TAF_XSMS_HOOK_MSG_TYPE_RCV_SMS      = 0x03,     /* _H2ASN_MsgChoice TAF_XSMS_INT_SMS_CONTENT_STRU*/ /***< @sa TAF_XSMS_INT_SMS_CONTENT_STRU */
    TAF_XSMS_HOOK_MSG_TYPE_SND_SMS      = 0x04,     /* _H2ASN_MsgChoice TAF_XSMS_INT_SMS_CONTENT_STRU*/ /***< @sa TAF_XSMS_INT_SMS_CONTENT_STRU */
    TAF_XSMS_HOOK_MSG_TYPE_RCV_TL_ACK   = 0x05,     /* _H2ASN_MsgChoice TAF_XSMS_INT_TL_ACK_STRU*/ /***< @sa TAF_XSMS_INT_TL_ACK_STRU */
    TAF_XSMS_HOOK_MSG_TYPE_SND_TL_ACK   = 0x06,     /* _H2ASN_MsgChoice TAF_XSMS_INT_TL_ACK_STRU*/ /***< @sa TAF_XSMS_INT_TL_ACK_STRU */

    TAF_XSMS_HOOK_MSG_TYPE_BUTT
};

typedef VOS_UINT32 TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32;

/*****************************************************************************
  4 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  6 ��Ϣ����
*****************************************************************************/
/* ASN������Ҫ�Ķ��� */
#define     ASN_CREAT   (0)
#if ASN_CREAT

#define     TAF_XSMS_ADDRESS_MAX        36
#define     TAF_XSMS_BEARER_DATA_MAX    255
enum TAF_XSMS_MT_FSM_ID_ENUM
{
    TAF_XSMS_MT_IDLE_STATE                     = 0,
    TAF_XSMS_MT_WAITING_XCC_CALL_CONN_STATE    = 1,
    TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE     = 2,
    TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE       = 3,
    TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE    = 4,
    TAF_XSMS_MT_WAITING_UIM_WRITE_CNF_STATE    = 5,
    TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE     = 6,
    TAF_XSMS_MT_WAITING_AS_CNF_STATE           = 7,
    TAF_XSMS_MT_WAITING_XCC_DISCONNECT_STATE   = 8,

    TAF_XSMS_MT_STATE_BUTT

};
typedef VOS_UINT32 TAF_XSMS_MT_FSM_ID_ENUM_UINT32;


enum TAF_XSMS_MO_FSM_ID_ENUM
{
    TAF_XSMS_MO_IDLE_STATE                     = 0,
    TAF_XSMS_MO_WAITING_FDN_CNF                = 1,
    TAF_XSMS_MO_WAITING_CC_CNF                 = 2,
    TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF      = 3,
    TAF_XSMS_MO_WAITING_XCC_SO_IND             = 4,
    TAF_XSMS_MO_WAITING_AS_CNF                 = 5,
    TAF_XSMS_MO_WAITING_TL_ACK                 = 6,
    TAF_XSMS_MO_WAITING_XCC_END_CALL_CNF       = 7,
    TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND      = 8,

    TAF_XSMS_MO_STATE_BUTT
};
typedef VOS_UINT32 TAF_XSMS_MO_FSM_ID_ENUM_UINT32;

/*****************************************************************************
 ö����    : TAF_XSMS_DIGITMODE_ENUM_UINT8
 ö��˵��  : ��ַ��digit mode
*****************************************************************************/
enum TAF_XSMS_DIGITMODE_ENUM
{
    TAF_XSMS_DIGIT_MODE_4_BIT = 0,     /* DTMF digits */
    TAF_XSMS_DIGIT_MODE_8_BIT = 1,
    TAF_XSMS_DIGIT_MODE_BUTT  = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_DIGITMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_NUMBERMODE_ENUM_UINT8
 ö��˵��  : ��ַ��number mode
*****************************************************************************/
enum TAF_XSMS_NUMBERMODE_ENUM
{
    TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK = 0,
    TAF_XSMS_NUMBER_MODE_DATA_NETWORK     = 1,
    TAF_XSMS_NUMBER_MODE_BUFF             = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_NUMBERMODE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_NUMBERTYPE_ENUM_UINT8
 ö��˵��  : ��ַ��number type
*****************************************************************************/
enum TAF_XSMS_NUMBERTYPE_ENUM
{
    TAF_XSMS_NUMBER_TYPE_UNKNOWN                   = 0,
   /* INTERNATIONAL is used when number mode is not data network address.
    * DATA_IP is used when the number mode is data network address
    */
    TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP  = 1,
   /* NATIONAL is used when the number mode is not data network address.
    * INTERNET_MAIL is used when the number mode is data network address.
    * For INTERNET_MAIL, in the address data "digits", each byte contains
    * an ASCII character. Examples are "x@y.com,a@b.com - ref TIA/EIA-637A 3.4.3.3
    */
    TAF_XSMS_NUMBER_TYPE_NATIONAL_OR_INTERNET_MAIL = 2,
    TAF_XSMS_NUMBER_TYPE_NETWORK                   = 3,
    TAF_XSMS_NUMBER_TYPE_SUBSCRIBER                = 4,
    /* GSM SMS: address value is GSM 7-bit chars */
    TAF_XSMS_NUMBER_TYPE_ALPHANUMERIC              = 5,
    TAF_XSMS_NUMBER_TYPE_ABBREVIATED               = 6,
    TAF_XSMS_NUMBER_TYPE_RESERVED_7                = 7,
    TAF_XSMS_NUMBER_TYPE_BUFF                      = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_NUMBERTYPE_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_NUMBERPLAN_ENUM_UINT8
 ö��˵��  : ��ַ��number plan
*****************************************************************************/
enum TAF_XSMS_NUMBERPLAN_ENUM
{
    TAF_XSMS_NUMBER_PLAN_UNKNOWN     = 0,
    TAF_XSMS_NUMBER_PLAN_TELEPHONY   = 1,      /* CCITT E.164 and E.163, including ISDN plan */
    TAF_XSMS_NUMBER_PLAN_RESERVED_2  = 2,
    TAF_XSMS_NUMBER_PLAN_DATA        = 3,      /* CCITT X.121 */
    TAF_XSMS_NUMBER_PLAN_TELEX       = 4,      /* CCITT F.69 */
    TAF_XSMS_NUMBER_PLAN_RESERVED_5  = 5,
    TAF_XSMS_NUMBER_PLAN_RESERVED_6  = 6,
    TAF_XSMS_NUMBER_PLAN_RESERVED_7  = 7,
    TAF_XSMS_NUMBER_PLAN_RESERVED_8  = 8,
    TAF_XSMS_NUMBER_PLAN_PRIVATE     = 9,
    TAF_XSMS_NUMBER_PLAN_RESERVED_10 = 10,
    TAF_XSMS_NUMBER_PLAN_RESERVED_11 = 11,
    TAF_XSMS_NUMBER_PLAN_RESERVED_12 = 12,
    TAF_XSMS_NUMBER_PLAN_RESERVED_13 = 13,
    TAF_XSMS_NUMBER_PLAN_RESERVED_14 = 14,
    TAF_XSMS_NUMBER_PLAN_RESERVED_15 = 15,
    TAF_XSMS_NUMBER_PLAN_BUFF        = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_NUMBERPLAN_ENUM_UINT8;

/*****************************************************************************
 ö����    : TAF_XSMS_SUBADDR_TYPE_ENUM_UINT8
 ö��˵��  : �ӵ�ַ����
*****************************************************************************/
enum TAF_XSMS_SUBADDR_TYPE_ENUM
{
    TAF_XSMS_SUBADDRESS_TYPE_NSAP           = 0,    /* CCITT X.213 or ISO 8348 AD2 */
    TAF_XSMS_SUBADDRESS_TYPE_USER_SPECIFIED = 1,    /* e.g. X.25 */
    TAF_XSMS_SUBADDRESS_TYPE_MAX32          = 0xFF,
};

typedef VOS_UINT8 TAF_XSMS_SUBADDR_TYPE_ENUM_UINT8;

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
 �ṹ��    :TAF_XSMS_ADDR_STRU
 �ṹ˵��  :Ril�·��ĵ�ַ��Ϣ���ݽṹ
*****************************************************************************/
typedef struct
{
    /* Indicates 4-bit or 8-bit */
    TAF_XSMS_DIGITMODE_ENUM_UINT8       enDigitMode;
    /* Used only when digitMode is 8-bit */
    TAF_XSMS_NUMBERMODE_ENUM_UINT8      enNumberMode;
    /* Used only when digitMode is 8-bit.
     * To specify an international address, use the following:
     * digitMode = TAF_XSMS_DIGIT_MODE_8_BIT
     * numberMode = TAF_XSMS_NUMBER_MODE_NOT_DATA_NETWORK
     * numberType = TAF_XSMS_NUMBER_TYPE_INTERNATIONAL_OR_DATA_IP
     * numberPlan = TAF_XSMS_NUMBER_PLAN_TELEPHONY
     * numberOfDigits = number of digits
     * digits = ASCII digits, e.g. '1', '2', '3'3, '4', and '5'
     */
    TAF_XSMS_NUMBERTYPE_ENUM_UINT8      enNumberType;
    /* Used only when digitMode is 8-bit */
    TAF_XSMS_NUMBERPLAN_ENUM_UINT8      enNumberPlan;
    VOS_UINT32                          ulNumberOfDigits;
    VOS_UINT8                           aucDigits[TAF_XSMS_ADDRESS_MAX];
}TAF_XSMS_ADDR_STRU;


/*****************************************************************************
 �ṹ��    :TAF_XSMS_CAUSE_CODE_STRU
 �ṹ˵��  :TL��Cause Code�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucParameterLen;
    VOS_UINT8                           ucReplySeq;
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass;
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode;
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

#endif

/*****************************************************************************
  7 STRUCT����
*****************************************************************************/

/*****************************************************************************
 �ṹ��    : TAF_XSMS_INT_3RD_PARTY_ERR_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulErrorType;
}TAF_XSMS_INT_3RD_PARTY_ERR_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_INT_CUR_MO_FSM_STRU
 �ṹ˵��  : ��ǰMO STATE��״̬
*****************************************************************************/
typedef struct
{
    TAF_XSMS_MO_FSM_ID_ENUM_UINT32      enCurMoState;
}TAF_XSMS_INT_CUR_MO_FSM_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_INT_CUR_MO_FSM_STRU
 �ṹ˵��  : ��ǰMO STATE��״̬
*****************************************************************************/
typedef struct
{
    TAF_XSMS_MT_FSM_ID_ENUM_UINT32      enCurMtState;
}TAF_XSMS_INT_CUR_MT_FSM_STRU;


/*****************************************************************************
 �ṹ��    : TAF_XSMS_INT_SMS_CONTENT_STRU
 �ṹ˵��  : ���ŷ��ͻ��߽��յ����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulTeleserviceID;
    VOS_UINT32                          ulServiceCategory;
    VOS_UINT32                          ulReplySeq;
    TAF_XSMS_ADDR_STRU                  stAddr;
    VOS_UINT32                          ulBearerDataLen;
    VOS_UINT8                           aucBearerData[TAF_XSMS_BEARER_DATA_MAX + 1];
    TAF_XSMS_MSG_ID_STRU                stMsgId;
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;
}TAF_XSMS_INT_SMS_CONTENT_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_INT_TL_ACK_STRU
 �ṹ˵��  : ���ŷ��ͻ��߽��յ�TL_ACK���ݽṹ
*****************************************************************************/
typedef struct
{
    TAF_XSMS_CAUSE_CODE_STRU            stCauseCode;
}TAF_XSMS_INT_TL_ACK_STRU;

/*****************************************************************************
 �ṹ��    : TAF_XSMS_MSG_HOOK_STRU
 �ṹ˵��  :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER                                     /* _H2ASN_Skip */
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgId;       /* _H2ASN_Skip */
    VOS_UINT8                           aucMsg[4];
}TAF_XSMS_MSG_HOOK_STRU;


/** ****************************************************************************
 * Name        : TAF_XSMS_INTER_MSG_DATA
 *
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32  enMsgId;     /* _H2ASN_MsgChoice_Export TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32 */
    VOS_UINT8                           aucMsgBlock[4];

    /* _H2ASN_MsgChoice_When_Comment TAF_XSMS_HOOK_MSG_TYPE_ENUM_UINT32 */
}TAF_XSMS_INTER_MSG_DATA;

/* _H2ASN_Length UINT32*/
/** ****************************************************************************
 * Name        : TafXsmsInterMsg_MSG
 *
 * Description : H2ASN top level message structure definition
 *******************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    TAF_XSMS_INTER_MSG_DATA             stMsgData;
}TafXsmsInterMsg_MSG;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/

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


