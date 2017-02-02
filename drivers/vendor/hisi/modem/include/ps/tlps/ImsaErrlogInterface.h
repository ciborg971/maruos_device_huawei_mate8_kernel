

#ifndef __IMSAERRLOGINTERFACE_H__
#define __IMSAERRLOGINTERFACE_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include    "omerrorlog.h"

#pragma  pack(4)

/*****************************************************************************
  2 macro
*****************************************************************************/
#define IMSA_ERR_LOG_IPV6_STRING_LEN                      (46)

#define IMSA_RING_BUFFER_SIZE                           (1024)              /* IMSA��Ļ���buffer�Ĵ�С */

#define IMSA_ERR_LOG_CTRL_LEVEL_NULL                     (0)                     /* ErrLog�ȼ�δ����*/
#define IMSA_ERR_LOG_CTRL_LEVEL_CRITICAL                 (1)                     /* ErrLog�ȼ����� */
#define IMSA_ERR_LOG_CTRL_LEVEL_MAJOR                    (2)                     /* ErrLog�ȼ���Ҫ */
#define IMSA_ERR_LOG_CTRL_LEVEL_MINOR                    (3)                     /* ErrLog�ȼ���Ҫ */
#define IMSA_ERR_LOG_CTRL_LEVEL_WARNING                  (4)                     /* ErrLog�ȼ���ʾ */



/*****************************************************************************
  3 Massage Declare
*****************************************************************************/


/*****************************************************************************
  4 Enum
*****************************************************************************/
enum IMSA_USIM_STATUS_ENUM
{
    IMSA_USIM_STATUS_UNAVAILABLE        = 0x01,            /**< �������ã�������ȡ���뿨����ʧ�ܡ�PS����Ч�� */
    IMSA_USIM_STATUS_AVAILABLE          = 0x02,            /**< ����Ч���� */

    IMSA_USIM_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_USIM_STATUS_ENUM_UINT8;


enum IMSA_OM_ERR_LOG_MSG_TYPE_ENUM
{
    ID_IMSA_OM_REG_ERROR_LOG_IND                    = 0x01, /* _H2ASN_MsgChoice IMSA_REG_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_CALL_ERROR_LOG_IND                   = 0x02, /* _H2ASN_MsgChoice IMSA_CALL_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_NOT_INIT_REG_ERR_LOG_IND             = 0x03, /* _H2ASN_MsgChoice IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_PDN_CONN_REJ_ERR_LOG_IND        = 0x04, /* _H2ASN_MsgChoice IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_REG_FAIL_ERR_LOG_IND            = 0x05, /* _H2ASN_MsgChoice IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_INIT_DEREG_ERR_LOG_IND          = 0x06, /* _H2ASN_MsgChoice IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU*/
    ID_IMSA_OM_NORM_CALL_FAIL_ERR_LOG_IND           = 0x07, /* _H2ASN_MsgChoice IMSA_NORM_CALL_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_EMC_CALL_FAIL_ERR_LOG_IND            = 0x08, /* _H2ASN_MsgChoice IMSA_EMC_CALL_ERROR_LOG_INFO_STRU */
    ID_IMSA_OM_MODIFY_CALL_TYPE_FAIL_ERR_LOG_IND    = 0x09, /* _H2ASN_MsgChoice IMSA_MODIFY_CALL_TYPE_ERROR_LOG_INFO_STRU*/

    ID_IMSA_OM_ERR_LOG_MSG_TYPE_BUTT
};
typedef VOS_UINT32    IMSA_OM_ERR_LOG_MSG_TYPE_ENUM_UINT32;


enum IMSA_ERR_LOG_MSG_TYPE_ENUM
{
    IMSA_ERR_LOG_MSG_SET_ERR_REPORT = 0x01, /* �ϲ㴥�������ϱ� */
    IMSA_ERR_LOG_MSG_ERR_REPORT_END = 0x02, /* �����ϱ����� */
    IMSA_ERR_LOG_MSG_ON_OFF         = 0x03, /* ���������Ϳ��� */
    IMSA_ERR_LOG_MSG_ERR_REPORT     = 0x04, /* �����ϱ� */
    IMSA_ERR_LOG_MSG_FTM_REPORT     = 0x05, /* ����ģʽ�����ϱ� */
    IMSA_ERR_LOG_MSG_RESULT         = 0x06, /* �ϱ�Result */
    IMSA_ERR_LOG_MSG_FTM_REQ        = 0x07, /* ����ģʽ���� */
    IMSA_ERR_LOG_MSG_FTM_CNF        = 0x08, /* ����ģʽ��Ӧ */


    IMSA_ERR_LOG_MSG_TYPE_BUTT
};
typedef VOS_UINT32    IMSA_ERR_LOG_MSG_TYPE_ENUM_UINT32;
enum IMSA_ERR_LOG_ALARM_TYPE_ENUM
{
    IMSA_ERR_LOG_ALARM_TYPE_COMMUNICATION               = 0x01,         /* ��ʾͨ�� */
    IMSA_ERR_LOG_ALARM_TYPE_TRANSACTION_QULITY          = 0x02,         /* ��ʾҵ������ */
    IMSA_ERR_LOG_ALARM_TYPE_PROCESS_ERROR               = 0x03,         /* ��ʾ������� */
    IMSA_ERR_LOG_ALARM_TYPE_EQIPMENT_ERROR              = 0x04,         /* ��ʾ�豸���� */
    IMSA_ERR_LOG_ALARM_TYPE_ENVIR_ERROR                 = 0x05,         /* ��ʾ�������� */

    IMSA_ERR_LOG_ALARM_TYPE_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_ALARM_TYPE_ENUM_UINT16;

/*****************************************************************************
 ö����    :   IMSA_ERR_LOG_ERRLOG_PROCESS_EVENT_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  ��ʾ��ǰIMSA��������һ������
*****************************************************************************/
enum IMSA_ERR_LOG_ALM_ID_ENUM
{
    IMSA_ERR_LOG_ALM_CALL_FAIL_EVENT        = 0x01,    /* volte�������� */
    IMSA_ERR_LOG_ALM_REG_FAIL_EVENT         = 0x02,    /* IMSע��ʧ�� */
    IMSA_ERR_LOG_ALM_MNTN                   = 0x03,    /* ������� */

    IMSA_ERR_LOG_ALM_NORM_NOT_INIT_REG_EVENT    = 0x04, /* δ����ע������ */
    IMSA_ERR_LOG_ALM_NORM_PDN_CONN_REJ_EVENT    = 0x05, /* PND������������ */
    IMSA_ERR_LOG_ALM_NORM_REG_FAIL_EVENT        = 0x06, /* ��ͨע��ʧ�� */
    IMSA_ERR_LOG_ALM_NORM_INIT_DEREG_EVENT      = 0x07, /* ��������ȥע������ */
    IMSA_ERR_LOG_ALM_NORM_CALL_FAIL_EVENT       = 0x08, /* ��ͨ����ʧ������ */
    IMSA_ERR_LOG_ALM_EMC_CALL_FAIL_EVENT        = 0x09, /* ��������ʧ������ */
    IMSA_ERR_LOG_ALM_MODIFY_CALL_TYPE_FAIL_EVENT= 0x0a, /* �л���������ʧ������ */

    IMSA_ERR_LOG_ALM_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_ALM_ID_ENUM_UINT16;

/*****************************************************************************
 ö����    :   IMSA_ERR_LOG_VOPS_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  �����Ƿ�߱�IMS over PS����
*****************************************************************************/
enum IMSA_ERR_LOG_VOPS_STATUS_ENUM
{
    IMSA_ERR_LOG_VOPS_STATUS_NOT_SUPPORT            = 0x01,         /* ֧�� */
    IMSA_ERR_LOG_VOPS_STATUS_SUPPORT                = 0x02,         /* ��֧�� */
    IMSA_ERR_LOG_VOPS_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    :   IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  ��ǰ����PS����״̬
*****************************************************************************/
enum IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM
{
    IMSA_ERR_LOG_PS_SERVICE_STATUS_NORMAL_SERVICE       = 0x01,     /* �������� */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_LIMITED_SERVICE      = 0x02,     /* ���޷��� */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_NO_SERVICE           = 0x03,     /* �޷��� */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8;


/*****************************************************************************
 ö����    :   IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  PDN����״̬
*****************************************************************************/
enum IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM
{
    IMSA_ERR_LOG_PDN_CONN_STATUS_IDLE               = 0x01,         /* ���������� */
    IMSA_ERR_LOG_PDN_CONN_STATUS_CONNING            = 0x02,         /* ���ڽ������� */
    IMSA_ERR_LOG_PDN_CONN_STATUS_RELEASING          = 0x03,         /* �����ͷ����� */
    IMSA_ERR_LOG_PDN_CONN_STATUS_CONN               = 0x04,         /* �������� */
    IMSA_ERR_LOG_PDN_CONN_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    :   IMSA_ERR_LOG_REG_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  IMSע��״̬
*****************************************************************************/
enum IMSA_ERR_LOG_REG_STATUS_ENUM
{
    IMSA_ERR_LOG_REG_STATUS_NOT_REGISTER            = 0x01,     /* δע��״̬ */
    IMSA_ERR_LOG_REG_STATUS_REGISTERING             = 0x02,     /* ����ע��״̬ */
    IMSA_ERR_LOG_REG_STATUS_REGISTERED              = 0x03,     /* ��ע��״̬ */
    IMSA_ERR_LOG_REG_STATUS_DEREGING                = 0x04,     /* ����ȥע��״̬ */
    IMSA_ERR_LOG_REG_STATUS_WAIT_RETRY              = 0x05,     /* ���ڵȴ����³���״̬ */
    IMSA_ERR_LOG_REG_STATUS_PENDING                 = 0x06,     /* PENDING״̬ */
    IMSA_ERR_LOG_REG_STATUS_ROLLING_BACK            = 0x07,     /* ROLLINGBACK״̬ */
    IMSA_ERR_LOG_REG_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8
 �ṹ˵��  : service״̬ö��
*****************************************************************************/
enum IMSA_ERR_LOG_SRV_STATUS_ENUM
{
   IMSA_ERR_LOG_SRV_STATUS_IDLE_DEREG           = 0x00,    /**< IDLE&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONNING_DEREG        = 0x10,    /**< CONNING&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONNING_REG          = 0x13,    /**< CONNING&REG */
   IMSA_ERR_LOG_SRV_STATUS_RELEASING_DEREG      = 0x20,    /**< RELEASING&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONN_DEREG           = 0x30,    /**< CONN&DEREG */
   IMSA_ERR_LOG_SRV_STATUS_CONN_REGING          = 0x31,    /**< CONN&REGING */
   IMSA_ERR_LOG_SRV_STATUS_CONN_DEREGING        = 0x32,    /**< CONN&DEREGING */
   IMSA_ERR_LOG_SRV_STATUS_CONN_REG             = 0x33,    /**< CONN&REG */

   IMSA_ERR_LOG_SRV_STATUS_BUTT                 = 0xff
};
typedef VOS_UINT8   IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_CALL_STATUS_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  ����״̬
*****************************************************************************/
enum IMSA_ERR_LOG_CALL_STATUS_ENUM
{
    IMSA_ERR_LOG_CALL_STATUS_IDLE                   = 0x01,     /* IDLE״̬     */
    IMSA_ERR_LOG_CALL_STATUS_DIALING                = 0x02,     /* DIALING״̬  */
    IMSA_ERR_LOG_CALL_STATUS_TRYING                 = 0x03,     /* TRYING״̬   */
    IMSA_ERR_LOG_CALL_STATUS_ALERTING               = 0x04,     /* ALERTING״̬ */
    IMSA_ERR_LOG_CALL_STATUS_ACTIVE                 = 0x05,     /* ACTIVE״̬   */
    IMSA_ERR_LOG_CALL_STATUS_INCOMING               = 0x06,     /* INCOMING״̬ */
    IMSA_ERR_LOG_CALL_STATUS_HELD                   = 0x07,     /* HELD״̬     */
    IMSA_ERR_LOG_CALL_STATUS_WAITING                = 0x08,     /* WAITING״̬  */
    IMSA_ERR_LOG_CALL_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_MPTY_STATE_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  �Ƿ�෽����
*****************************************************************************/
enum IMSA_ERR_LOG_MPTY_STATE_ENUM
{
    IMSA_ERR_LOG_CALL_NOT_IN_MPTY                   = 0x01,     /* ���Ƕ෽���� */
    IMSA_ERR_LOG_CALL_IN_MPTY                       = 0x02,     /* �Ƕ෽���� */
    IMSA_ERR_LOG_CALL_MPYT_STATE_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_REGISTER_REASON_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  �Ƿ�෽����
*****************************************************************************/
enum IMSA_ERR_LOG_REGISTER_REASON_ENUM
{
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_NEW         = 0x01,    /* ʹ���µĵ�ַ�ӷ���ע�� */
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_SAME        = 0x02,  /* ʹ�õ�ǰ��ַ�ӷ���ע�� */
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_NEXT        = 0x03,    /* ʹ���¸���ַ�ӷ���ע�� */
    IMSA_ERR_LOG_REGISTER_REASON_ADDR_PARAM_RESTORATION = 0x04,  /* �����������ַ�ӣ���ʹ��������ַ�Է���ע�ᣬ����ʹ�õ�ǰ��ַ�Է���ע�� */
    IMSA_ERR_LOG_REGISTER_REASON_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :  ע��ʧ�ܵ�ԭ��ֵ
*****************************************************************************/
enum IMSA_ERR_LOG_REG_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_REG_FAIL_REASON_REMOTE                 = 0x01,     /**< ���������ܾ�������ܾ�ԭ��ֵ�����Ӧ���ݽṹ�е�Status Code�����ݲ�ͬ��ԭ��ֵ���ܻ�Я��һЩ������ͷ�� */
    IMSA_ERR_LOG_REG_FAIL_REASON_TIMEOUT                = 0x02,     /**< ���ͻ����SIP���ĳ�ʱ�����峬ʱ�Ķ�ʱ�������Ӧ���ݽṹ�е� Timer Id */
    IMSA_ERR_LOG_REG_FAIL_REASON_TRANSPORT              = 0x03,     /**< ���ͻ����SIP����ʱ���ײ㴫�䷢������ */
    IMSA_ERR_LOG_REG_FAIL_REASON_NO_ADDR_PAIR           = 0x04,     /**< û�п�����ʹ�õ�ע���ַ�� */
    IMSA_ERR_LOG_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT= 0x05,     /**< ע��������ƶ�����֧��VOLTE�Ľ��뼼���� */

    IMSA_ERR_LOG_REG_FAIL_REASON_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8;
enum IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM
{
    /* IMSA�ڲ����� */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_PARA_ERR                              = 1,    /**< CONNģ������ִ��ʧ�ܣ����ڲ������� */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_TIMER_EXP                             = 2,    /**< CONNģ������ִ��ʧ�ܣ����ڶ�ʱ����ʱ */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_CONN_RELEASING                        = 3,    /**< CONNģ������ִ��ʧ�ܣ����������ͷ����� */
    IMSA_ERR_LOG_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT                         = 4,    /**< CONNģ������ִ��ʧ�ܣ����������ͷ����� */
    IMSA_ERR_LOG_PDNREJ_CAUSE_SAME_APN_OPERATING                         = 5,    /**< CONNģ������ִ��ʧ�ܣ����������ͷ����� */
    IMSA_ERR_LOG_PDNREJ_CAUSE_IMSA_OTHERS                                = 6,    /**< CONNģ������ִ��ʧ�ܣ���������ԭ�� */

    /*----------------------------------------------------------------------
       TAF�ϱ���SM����ԭ��ֵ, ȡֵ��Χ[0x0100, 0x01FF]
       ����3GPPЭ���Ѿ������˾����(E)SM����ԭ��ֵ, (E)SM�ϱ���ȡֵΪЭ��
       �����ԭ��ֵ����ƫ����(0x100)
       (1) SM Cause : Refer to TS 24.008 section 10.5.6.6
       (2) ESM Cause: Refer to TS 24.301 section 9.9.4.4
    *---------------------------------------------------------------------*/
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_OPERATOR_DETERMINED_BARRING          =  8,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MBMS_BC_INSUFFICIENT                 =  24,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE                 =  25,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INSUFFICIENT_RESOURCES               =  26,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MISSING_OR_UKNOWN_APN                =  27,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNKNOWN_PDP_ADDR_OR_TYPE             =  28,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_USER_AUTHENTICATION_FAIL             =  29,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_BY_GGSN          =  30,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_ACTIVATION_REJECTED_UNSPECIFIED      =  31,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_NOT_SUPPORTED         =  32,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUESTED_SERVICE_NOT_SUBSCRIBED     =  33,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SERVICE_OPTION_TEMP_OUT_ORDER        =  34,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NSAPI_ALREADY_USED                   =  35,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REGULAR_DEACTIVATION                 =  36,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_QOS_NOT_ACCEPTED                     =  37,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_NETWORK_FAILURE                      =  38,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REACTIVATION_REQUESTED               =  39,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_FEATURE_NOT_SUPPORT                  =  40,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_TFT                  =  41,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNTACTIC_ERR_IN_TFT                 =  42,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UKNOWN_PDP_CONTEXT                   =  43,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTIC_ERR_IN_PACKET_FILTER        =  44,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SYNCTACTIC_ERR_IN_PACKET_FILTER      =  45,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    =  46,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT =  47,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_REQUEST_REJECTED_BCM_VIOLATION       =  48,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_LAST_PDN_DISCONN_NOT_ALLOWED         =  49,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV4_ONLY_ALLOWED           =  50,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDP_TYPE_IPV6_ONLY_ALLOWED           =  51,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     =  52,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INFORMATION_NOT_RECEIVED             =  53,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PDN_CONNECTION_DOES_NOT_EXIST        =  54,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED =  55,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_COLLISION_WITH_NW_INITIATED_REQUEST  =  56,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_UNSUPPORTED_QCI_VALUE                =  59,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_BEARER_HANDLING_NOT_SUPPORTED        =  60,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_TI                           =  81,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_SEMANTICALLY_INCORRECT_MESSAGE       =  95,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_INVALID_MANDATORY_INFO               =  96,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NON_EXISTENT                =  97,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_TYPE_NOT_COMPATIBLE              =  98,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_IE_NON_EXISTENT                      =  99,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_CONDITIONAL_IE_ERR                   =  100,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_MSG_NOT_COMPATIBLE                   =  101,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED             =  111,
    IMSA_ERR_LOG_PDNREJ_CAUSE_SM_NW_APN_RESTRICTION_INCOMPATIBLE         =  112,

    IMSA_ERR_LOG_PDNREJ_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32;
/*****************************************************************************
    ö����    : IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8
    ö��˵��  : ��������
*****************************************************************************/
enum    IMSA_ERR_LOG_CALL_TYPE_ENUM
{
    IMSA_ERR_LOG_CALL_TYPE_VOICE    = 0,      /* Voice only call */
    IMSA_ERR_LOG_CALL_TYPE_VIDEO_TX = 1,      /* PS Video telephony call: one way TX video,Two way audio */
    IMSA_ERR_LOG_CALL_TYPE_VIDEO_RX = 2,      /* Video telephony call: ony way RX video,two way audio */
    IMSA_ERR_LOG_CALL_TYPE_VIDEO    = 3,      /* video call */
    IMSA_ERR_LOG_CALL_TYPE_EMC      = 9,      /* emergency call */
    IMSA_ERR_LOG_CALL_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_CAMPED_RAT_TYPE_ENUM
    ö��˵��  : UEפ������������
*****************************************************************************/
enum    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM
{
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_NULL                   = 0,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_GSM,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_UTRAN,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_EUTRAN,
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8;


enum IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM
{
    /* IMSA�ڲ����� */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_PARA_ERR                = 1,    /**< CONNģ������ִ��ʧ�ܣ����ڲ������� */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_TIMER_EXP               = 2,    /**< CONNģ������ִ��ʧ�ܣ����ڶ�ʱ����ʱ */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONN_RELEASING          = 3,    /**< CONNģ������ִ��ʧ�ܣ����������ͷ����� */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_PDP_ACTIVATE_LIMIT           = 4,    /**< CONNģ������ִ��ʧ�ܣ����������ͷ����� */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_SAME_APN_OPERATING           = 5,    /**< CONNģ������ִ��ʧ�ܣ����������ͷ����� */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_OTHERS                  = 6,    /**< CONNģ������ִ��ʧ�ܣ���������ԭ�� */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_IMSA_CONNING                 = 7,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NO_IMS_PDP_CONTXT            = 8,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_CONN_STATE_MISMATCH          = 9,
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_TIMER_WAIT_IPV6_INFO_EXP     = 10,   /**< �ȴ�IPV6��ʱ����ʱ */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_NW_REJ                       = 11,   /**< PDN����������ܾ� */
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ORIG_TIMER_EXP               = 12,   /**< �ȴ�SPM���ų�ʱ */

    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32;


enum IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM
{
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NONE                                 = 0,
    /*----------------------------------------------------------------------
       TAF�ϱ���SM����ԭ��ֵ, ȡֵ��Χ[0x0100, 0x01FF]
       ����3GPPЭ���Ѿ������˾����(E)SM����ԭ��ֵ, (E)SM�ϱ���ȡֵΪЭ��
       �����ԭ��ֵ����ƫ����(0x100)
       (1) SM Cause : Refer to TS 24.008 section 10.5.6.6
       (2) ESM Cause: Refer to TS 24.301 section 9.9.4.4
    *---------------------------------------------------------------------*/
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_OPERATOR_DETERMINED_BARRING          =  8,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MBMS_BC_INSUFFICIENT                 =  24,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_LLC_OR_SNDCP_FAILURE                 =  25,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INSUFFICIENT_RESOURCES               =  26,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MISSING_OR_UKNOWN_APN                =  27,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_UNKNOWN_PDP_ADDR_OR_TYPE             =  28,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_USER_AUTHENTICATION_FAIL             =  29,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ACTIVATION_REJECTED_BY_GGSN          =  30,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ACTIVATION_REJECTED_UNSPECIFIED      =  31,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SERVICE_OPTION_NOT_SUPPORTED         =  32,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REQUESTED_SERVICE_NOT_SUBSCRIBED     =  33,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SERVICE_OPTION_TEMP_OUT_ORDER        =  34,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NSAPI_ALREADY_USED                   =  35,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REGULAR_DEACTIVATION                 =  36,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_QOS_NOT_ACCEPTED                     =  37,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_NETWORK_FAILURE                      =  38,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REACTIVATION_REQUESTED               =  39,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_FEATURE_NOT_SUPPORT                  =  40,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SEMANTIC_ERR_IN_TFT                  =  41,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SYNTACTIC_ERR_IN_TFT                 =  42,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_UKNOWN_PDP_CONTEXT                   =  43,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SEMANTIC_ERR_IN_PACKET_FILTER        =  44,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SYNCTACTIC_ERR_IN_PACKET_FILTER      =  45,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDP_CONTEXT_WITHOUT_TFT_ACTIVATED    =  46,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MULTICAST_GROUP_MEMBERHHSHIP_TIMEOUT =  47,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_REQUEST_REJECTED_BCM_VIOLATION       =  48,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_LAST_PDN_DISCONN_NOT_ALLOWED         =  49,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDP_TYPE_IPV4_ONLY_ALLOWED           =  50,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDP_TYPE_IPV6_ONLY_ALLOWED           =  51,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SINGLE_ADDR_BEARERS_ONLY_ALLOWED     =  52,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INFORMATION_NOT_RECEIVED             =  53,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PDN_CONNECTION_DOES_NOT_EXIST        =  54,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SAME_APN_MULTI_PDN_CONNECTION_NOT_ALLOWED =  55,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_COLLISION_WITH_NW_INITIATED_REQUEST  =  56,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_UNSUPPORTED_QCI_VALUE                =  59,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_BEARER_HANDLING_NOT_SUPPORTED        =  60,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INVALID_TI                           =  81,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_SEMANTICALLY_INCORRECT_MESSAGE       =  95,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_INVALID_MANDATORY_INFO               =  96,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MSG_TYPE_NON_EXISTENT                =  97,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MSG_TYPE_NOT_COMPATIBLE              =  98,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_IE_NON_EXISTENT                      =  99,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_CONDITIONAL_IE_ERR                   =  100,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_MSG_NOT_COMPATIBLE                   =  101,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_PROTOCOL_ERR_UNSPECIFIED             =  111,
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_APN_RESTRICTION_INCOMPATIBLE         =  112,

    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_BUTT
};
typedef VOS_UINT16 IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_ENUM_UINT32
 Э����  :
 ASN.1���� :
 ö��˵��  :  UE��������ȥע���ԭ��
*****************************************************************************/
enum IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM
{
    IMSA_ERR_LOG_INIT_DEREG_REASON_PDN_LOST                 = 1,    /* PDN LOST�ؽ�ʧ�ܴ�����ȥע�� */
    IMSA_ERR_LOG_INIT_DEREG_REASON_RAT_OR_VOICE_NOT_SUPPORT = 2,    /* �ƶ�����֧��VOLTE�Ľ��뼼���� */
    IMSA_ERR_LOG_INIT_DEREG_REASON_ROAMING_NOT_SUPPORT_REG  = 3,    /* �ƶ������������£��Ҳ�֧������ע�� */
    IMSA_ERR_LOG_INIT_DEREG_REASON_NW_INIT                  = 4,    /* ����ȥ����IMS */


    IMSA_ERR_LOG_INIT_DEREG_REASON_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32;

/*****************************************************************************
    ö����    : IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8
    ö��˵��  : ��ԴԤ��״̬
*****************************************************************************/
enum    IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_ENUM
{
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_READY,
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_ONLY_VOICE,
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_FAILED,
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_BUTT
};
typedef VOS_UINT8 IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :  ����ʧ�ܵ�ԭ��ֵ
*****************************************************************************/
enum IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_CALL_FAIL_REASON_REMOTE                                             = 1,     /**< ���������ܾ�������ܾ�ԭ��ֵ�����Ӧ���ݽṹ�е�Status Code�����ݲ�ͬ��ԭ��ֵ���ܻ�Я��һЩ������ͷ�� */
    IMSA_ERR_LOG_CALL_FAIL_REASON_TIMEOUT                                            = 2,     /**< ���ͻ����SIP���ĳ�ʱ�����峬ʱ�Ķ�ʱ�������Ӧ���ݽṹ�е� Timer Id */
    IMSA_ERR_LOG_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE                            = 3,     /**< �������Ͳ�֧�� */
    IMSA_ERR_LOG_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL                                 = 4,     /**< ���������µĺ��� */
    IMSA_ERR_LOG_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE                              = 5,     /**< ��Ӧ�ķ��񲻿��� */
    IMSA_ERR_LOG_CALL_FAIL_REASON_RES_READY_FAIL                                     = 6,     /**< ��ԴԤ��ʧ�� */

    /* IMS�ϱ��Ĵ���*/
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MULTIPLE_CHOICES                               = 300,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MOVED_PERMANENTLY                              = 301,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MOVED_TEMPORARILY                              = 302,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_USE_PROXY                                      = 305,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_ALTERNATIVE_SERVICE                            = 380,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_REQUEST                                    = 400,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNAUTHORIZED                                   = 401,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PAYMENT_REQUIRED                               = 402,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_FORBIDDEN                                      = 403,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_FOUND                                      = 404,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_METHOD_NOT_ALLOWED                             = 405,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_ACCEPTABLE                                 = 406,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PROXY_AUTHENTICATION_REQUIRED                  = 407,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_TIMEOUT                                = 408,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CONFLICT_DEPRECATED                            = 409,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_GONE                                           = 410,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CONDITIONAL_REQUEST_FAILED                     = 412,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_ENTITY_TOO_LARGE                       = 413,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_URI_TOO_LONG                           = 414,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNSUPPORTED_MEDIA_TYPE                         = 415,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNSUPPORTED_URI_SCHEME                         = 416,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNKNOWN_RESOURCE_PRIORITY                      = 417,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_EXTENSION                                  = 420,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_EXTENSION_REQUIRED                             = 421,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SESSION_INTERVAL_TOO_SMALL                     = 422,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_INTERVAL_TOO_BRIEF                             = 423,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_LOCATION_INFORMATION                       = 424,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_USE_IDENTITY_HEADER                            = 428,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PROVIDE_REFERRER_IDENTITY                      = 429,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_FLOW_FAILED                                    = 430,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_ANONYMITY_DISALLOWED                           = 433,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_IDENTITY_INFO                              = 436,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNSUPPORTED_CERTIFICATE                        = 437,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_INVALID_IDENTITY_HEADER                        = 438,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_FIRST_HOP_LACKS_OUTBOUND_SUPPORT               = 439,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MAX_BREADTH_EXCEEDED                           = 440,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_INFO_PACKEAGE                              = 469,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CONSENT_NEEDED                                 = 470,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_TEMPORARILY_UNAVAILABLE                        = 480,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_CALL_TRANSACTION_DOES_NOT_EXIST                = 481,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_LOOP_DETECTED                                  = 482,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_TOO_MANY_HOPS                                  = 483,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_ADDRESS_INCOMPLETE                             = 484,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_AMBIGUOUS                                      = 485,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BUSY_HERE                                      = 486,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_TERMINATED                             = 487,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_ACCEPTABLE_HERE                            = 488,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_EVENT                                      = 489,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_REQUEST_PENDING                                = 491,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_UNDECIPHERABLE                                 = 493,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SECURITY_AGREEMENT_REQUIRED                    = 494,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SERVER_INTERNAL_ERROR                          = 500,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_NOT_IMPLEMENTED                                = 501,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BAD_GATEWAY                                    = 502,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SERVICE_UNAVAILABLE                            = 503,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_SERVER_TIME_OUT                                = 504,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_VERSION_NOT_SUPPORTED                          = 505,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_MESSAGE_TOO_LARGE                              = 513,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_PRECONDITION_FAILURE                           = 580,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_BUSY_EVERYWHERE                                = 600,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_DECLINE                                        = 603,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_DOES_NOT_EXIST_ANYWHERE                        = 604,
    IMSA_ERR_LOG_CALL_FAIL_REASON_IMS_GLOBAL_NOT_ACCEPTABLE                          = 606,

    IMSA_ERR_LOG_CALL_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT16;
/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :  ����ʧ�ܵ�ԭ��ֵ
*****************************************************************************/
enum IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NONE,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_REMOTE                        = 1,     /**< ���������ܾ�������ܾ�ԭ��ֵ�����Ӧ���ݽṹ�е�Status Code�����ݲ�ͬ��ԭ��ֵ���ܻ�Я��һЩ������ͷ�� */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TIMEOUT                       = 2,     /**< ���ͻ����SIP���ĳ�ʱ�����峬ʱ�Ķ�ʱ�������Ӧ���ݽṹ�е� Timer Id */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NOT_SUPPORTED_CALL_TYPE       = 3,     /**< �������Ͳ�֧�� */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL            = 4,     /**< ���������µĺ��� */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SERVICE_NOT_AVAILABLE         = 5,     /**< ��Ӧ�ķ��񲻿��� */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_RES_READY_FAIL                = 6,     /**< ��ԴԤ��ʧ�� */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_CANNOT_FIND_CALLENTITY        = 7,
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_NORM_SER_NOT_CONN_REG         = 8,    /**< ��ͨ����״̬����CONN+REG */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_VOICE_DOMAIN_CS_ONLY          = 9,    /**< ��������CS ONLY */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_IMS_VOPS_STATUS_NOT_SUPPORT   = 10,   /**< ���಻֧��VOPS */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_HIFI_START_ABNORMAL           = 11,   /**< HIFI�����쳣 */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL = 12,   /**< UE��������Ϊ��֧��VOICE CALL */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VIDEO_CALL = 13,   /**< UE��������Ϊ��֧��VIDEO CALL */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SSAC_BAR_FOR_VOICE_CALL       = 14,   /**< SSAC,�������������� */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_SSAC_BAR_FOR_VIDEO_CALL       = 15,   /**< SSAC,��������Ƶ���� */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TCALL_TIMEOUT                 = 16,   /**< TCALL��ʱ */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_TQOS_TIMEOUT                  = 17,   /**< TQOS��ʱ */

    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_CALL_TYPE_MODIFY_FAIL         = 18,   /**< ��Ƶ�л�ʧ�ܣ�����ԭ��ֵ��usSipStatusCode */

    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16;

/*****************************************************************************
 ö����    : IMSA_VOICE_DOMAIN_ENUM
 �ṹ˵��  : UE��Voice Domain����
*****************************************************************************/
enum IMSA_ERR_LOG_VOICE_DOMAIN_ENUM
{
   IMSA_ERR_LOG_VOICE_DOMAIN_CS_ONLY         = 0,    /**< CS voice only */
   IMSA_ERR_LOG_VOICE_DOMAIN_IMS_PS_ONLY     = 1,    /**< IMS PS voice only */
   IMSA_ERR_LOG_VOICE_DOMAIN_CS_PREFERRED    = 2,    /**< CS voice preferred, IMS PS Voice as secondary */
   IMSA_ERR_LOG_VOICE_DOMAIN_IMS_PS_PREFERRED= 3,    /**< IMS PS voice preferred, CS Voice as secondary */

   IMSA_ERR_LOG_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT8   IMSA_ERR_LOG_VOICE_DOMAIN_ENUM_UINT8;


/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8
 Э����  :
 ASN.1���� :
 ö��˵��  :  ע���ַ������
*****************************************************************************/
enum IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM
{
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_NEW         = 0x01,  /* ʹ���µĵ�ַ�ӷ���ע�� */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_SAME        = 0x02,  /* ʹ�õ�ǰ��ַ�ӷ���ע�� */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_NEXT        = 0x03,  /* ʹ���¸���ַ�ӷ���ע�� */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ADDR_PARAM_RESTORATION = 0x04,  /* �����������ַ�ӣ���ʹ��������ַ�Է���ע�ᣬ����ʹ�õ�ǰ��ַ�Է���ע�� */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_BUTT
};
typedef VOS_UINT8  IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8;


/*****************************************************************************
    ö����    : IMSA_ERR_LOG_EMC_CALL_TYPE_ENUM_UINT32
    ö��˵��  : ������������
*****************************************************************************/
enum    IMSA_ERR_LOG_EMC_CALL_TYPE_ENUM
{
    IMSA_ERR_LOG_EMC_CALL_TYPE_IN_NORMAL_SRV    = 0,                        /**< ����ͨ�����Ϸ�������� */
    IMSA_ERR_LOG_EMC_CALL_TYPE_NO_CARD          = 1,                        /**< �޿������� */
    IMSA_ERR_LOG_EMC_CALL_TYPE_EMC_CONN_EMC_REG = 2,                        /**< �н���ע��Ľ����� */
    IMSA_ERR_LOG_EMC_CALL_TYPE_BUTT
};
typedef VOS_UINT32 IMSA_ERR_LOG_EMC_CALL_TYPE_ENUM_UINT32;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16
 Э����  :
 ASN.1���� :
 ö��˵��  :  ����ע��ʧ�ܵ�ԭ��ֵ
*****************************************************************************/
enum IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NONE,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_EMC_PDP_CONTEXT,                /**< û�н�����PDP������ */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ORIG_REQ_FAIL,                     /**< ����TAF��ORIG_REQ APIʧ�� */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDP_ACTIVATE_LIMIT,
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SAME_APN_OPERATING,                /**< ��ͬ��APN���ڲ��� */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDP_CONTEXT_PARA_ERR,              /**< �������� */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_PDN_CONNECT_NW_REJ,                /**< ����������ܾ� */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_NO_REG_ADDR_PAIR,                  /**< û�з���ע��ĵ�ַ�� */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_TRANSPORT,                         /**< ���ͻ����SIP����ʱ���ײ㴫�䷢������*/
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REMOTE,                            /**< ע�ᱻ����ܾ� */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SIP_SIGAL_PDP_ORIG_TIMER_EXP,      /**< ���Ŷ�ʱ����ʱ */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_WAIT_IPV6_INFO_TIMER_EXP,          /**< ��IPV6ǰ׺��ʱ����ʱ */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_REG_PROTECT_TIMER_EXP,             /**< �ȴ�ע�ᱣ����ʱ����ʱ */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_SERVICE_STATUS_ERROR,              /**< ����״̬����ȷ */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_MOVE_TO_NOT_SUP_IMS_RAT,           /**< ע��������ƶ����˲�֧��IMS�Ľ��뼼���� */

    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16;

/*****************************************************************************
 ö����    :  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM
 Э����  :
 ASN.1���� :
 ö��˵��  :  ��������ʧ�ܵ�ԭ��ֵ
*****************************************************************************/
enum IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM
{
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NONE,
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_IMS        = 1,    /**< ��ǰ���뼼����֧��IMS���� */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_EMC_IMS    = 2,    /**< UE��֧�ֽ�����VOLTE */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NOT_ALLOW_NEW_CALL,                   /**< ���������µĺ��� */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_UE_CAP_NOT_SUPPORT_VOICE_CALL,        /**< UE��֧��VOICE CALL */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CANNOT_MAKE_NOCAR_EMC_CALL,           /**< ���ܴ��޿��������� */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_NW_NOT_SUPPORT_EMC_BEAR,              /**< ���಻֧�ֽ����������� */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_REMOTE,                               /**< ���������ܾ�������ܾ�ԭ��ֵ�����Ӧ���ݽṹ�е�Status Code�����ݲ�ͬ��ԭ��ֵ���ܻ�Я��һЩ������ͷ�� */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TIMEOUT,                              /**< ���ͻ����SIP���ĳ�ʱ�����峬ʱ�Ķ�ʱ�������Ӧ���ݽṹ�е� Timer Id */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_EMC_REG_FAIL,                         /**< ����ע��ʧ�� */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_IMS,              /**< ��ǰ���뼼����֧��IMS */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_CUR_RAT_NOT_SUPPORT_EMC_IMS,          /**< ��ǰ���뼼����֧�ֽ���IMS */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TCALL_TIMEOUT,                        /**< TCALL��ʱ */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_TQOS_TIMEOUT ,                        /**< TQOS��ʱ */

    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_BUTT
};
typedef VOS_UINT16  IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16;



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
   5 STRUCT
*****************************************************************************/

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_CALL_FAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : volte����ʧ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /*��Ϣͷ*/
    IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8              enNormRegStatus;        /* IMS��ͨע��ע��״̬ */
    IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8              enEmcRegStatus;         /* IMS����ע��״̬ */
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* �����Ƿ�߱�IMS over PS���� */
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus;           /* ����״̬ */
    IMSA_ERR_LOG_CALL_FAIL_REASON_ENUM_UINT16       enCallFailReason;       /* ����ʧ��ԭ��ֵ */
    VOS_UINT8                                       ucIsVoiceMediaExist;    /* �����Ƿ���ר�г��� */
    VOS_UINT8                                       ucIsVideoMediaExist;    /* �����Ƿ���ר�г��� */
    IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8              enMpty;                 /* �Ƿ�MPTY */
    IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8         enPdnConnStatus;        /* PDN����״̬ */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    VOS_UINT8                                       aucRsv[3];
} IMSA_ERR_LOG_CALL_FAIL_STRU;

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_NORM_CALL_FAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : volte����ʧ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /*��Ϣͷ*/
    IMSA_ERR_LOG_REG_STATUS_ENUM_UINT8              enNormRegStatus;        /* IMS��ͨע��ע��״̬ */
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* �����Ƿ�߱�IMS over PS���� */
    IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8               enCallType;             /* �������ͣ�����������������Ƶ */
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus;           /* ����״̬ */
    IMSA_ERR_LOG_NORM_CALL_FAIL_REASON_ENUM_UINT16  enCallFailReason;       /* ����ʧ��ԭ��ֵ */
    VOS_UINT16                                      usSipStatusCode;        /* IMS���Ĵ���ԭ��ֵ������enCallFailReasonΪremoteʱ��Ч */
    VOS_UINT8                                       ucIsVoiceMediaExist;    /* �����Ƿ���ר�г��� */
    VOS_UINT8                                       ucIsVideoMediaExist;    /* �����Ƿ���ר�г��� */
    IMSA_ERR_LOG_MPTY_STATE_ENUM_UINT8              enMpty;                 /* �Ƿ�MPTY */
    IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8         enPdnConnStatus;        /* PDN����״̬ */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    VOS_UINT8                                       ucRsv;
} IMSA_ERR_LOG_NORM_CALL_FAIL_STRU;

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_EMC_CALL_FAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : volte����ʧ����Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /*��Ϣͷ*/
    IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8              enNormSrvStatus;        /* IMS��ͨע��ע��״̬ */
    IMSA_ERR_LOG_SRV_STATUS_ENUM_UINT8              enEmcSrvStatus;         /* IMS����ע��״̬ */
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* �����Ƿ�߱�IMS over PS���� */
    IMSA_ERR_LOG_CALL_STATUS_ENUM_UINT8             enCallStatus;           /* ����״̬ */
    IMSA_ERR_LOG_EMC_CALL_FAIL_REASON_ENUM_UINT16   enCallFailReason;       /* ����ʧ��ԭ��ֵ */
    IMSA_ERR_LOG_EMC_REG_FAIL_REASON_ENUM_UINT16    enRegFailReason;        /* ע��ʧ��ԭ��ֵ */
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8      enRegisterAddrType;     /* ע��ʹ�õĵ�ַ������ */
    VOS_UINT8                                       ucRsv;
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enPdnConnNwRej;         /* ����������ܾ� */
    VOS_UINT16                                      usCallSipStatusCode;    /* IMS���Ĵ���ԭ��ֵ������enCallFailReasonΪremoteʱ��Ч */
    VOS_UINT16                                      usEmcRegSipStatusCode;  /* IMS���Ĵ���ԭ��ֵ������enCallFailReasonΪremoteʱ��Ч */

} IMSA_ERR_LOG_EMC_CALL_FAIL_STRU;

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_NOT_INIT_REG_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMS���ܷ���ע���ԭ��ֵ
*****************************************************************************/
typedef struct
{
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;           /* �����Ƿ�߱�IMS over PS���� */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8       enPsServiceStatus;      /* ��ǰ����PS����״̬ */
    IMSA_ERR_LOG_VOICE_DOMAIN_ENUM_UINT8            enVoiceDomain;          /* UE���õ��������� */
    VOS_UINT8                                       ucImsSupportFlag;       /* ��ǰ���뼼�����Ƿ�֧��IMS */
    VOS_UINT8                                       ucIsRoamingFlag;        /* ��ǰ�Ƿ����������� */
    VOS_UINT8                                       ucIsSupportRoamNotRegFlag; /* ���������²�����IMSע�Ὺ���Ƿ�� */
    IMSA_USIM_STATUS_ENUM_UINT8                     enUsimStatus;           /* ���Ƿ���Ч */
    VOS_UINT8                                       ucHomeNetDomainNameValid;   /* �����Ƿ���Ч */
    VOS_UINT8                                       ucImpiValid;                /* IMPI�Ƿ���Ч */
    VOS_UINT8                                       ucImpuValid;                /* IMPU�Ƿ���Ч */
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8         enImsaCampedRatType;        /**< ��ǰפ������,NULL,2G,3G,LTE */
    VOS_UINT8                                       ucRsv;
} IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU;


/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_NOT_INIT_REG_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMS���ܷ���ע���ԭ��ֵ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;               /* ��Ϣͷ*/
    IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU          stRegConditionStatus;   /* ����ע����Ҫ�����������״̬ */
} IMSA_ERR_LOG_NOT_INIT_REG_STRU;

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_PDN_CONN_FAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ����PDN��������ʧ�ܵĽṹ��
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;            /*��Ϣͷ*/
    IMSA_ERR_LOG_NORM_PDNREJ_CAUSE_ENUM_UINT32      enPdnConnRejCause;  /* IMS PDN���ӱ���ԭ��ֵ */
    IMSA_ERR_LOG_PDN_CONN_NW_REJ_CAUSE_ENUM_UINT16  enNwRejCause;       /* PDN������ܾ���ԭ��ֵ��ֻ����enPdnConnRejCauseΪCN REJʱ��Ч */
    VOS_UINT8                                       aucRsv[2];
} IMSA_ERR_LOG_PDN_CONN_FAIL_STRU;

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_REG_FAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMSע��ʧ�ܽṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;           /*��Ϣͷ*/
    IMSA_ERR_LOG_VOPS_STATUS_ENUM_UINT8             enVopsStatus;       /* �����Ƿ�߱�IMS over PS���� */
    IMSA_ERR_LOG_PS_SERVICE_STATUS_ENUM_UINT8       enPsServiceStatus;  /* ��ǰ����PS����״̬ */
    IMSA_ERR_LOG_PDN_CONN_STATUS_ENUM_UINT8         enPdnConnStatus;    /* PDN����״̬ */
    IMSA_ERR_LOG_REGISTER_REASON_ENUM_UINT8         enRegisterReason;   /* ע�ᷢ���ԭ�� */
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enRegFailReason;    /* ע��ʧ�ܵ�ԭ�� */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    IMSA_USIM_STATUS_ENUM_UINT8                     enUsimStatus;       /* ���Ƿ���Ч */
    VOS_UINT8                                       ausRsv[3];
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32           enPdnConnRejCause;  /* IMS PDN���ӱ���ԭ��ֵ */
} IMSA_ERR_LOG_REG_FAIL_STRU;

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_REG_FAIL_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMSע��ʧ�ܽṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                          stHeader;           /*��Ϣͷ*/
    IMSA_ERR_LOG_REGISTER_ADDR_TYPE_ENUM_UINT8      enRegisterAddrType; /* ע��ʹ�õĵ�ַ������ */
    IMSA_ERR_LOG_REG_FAIL_REASON_ENUM_UINT8         enRegFailReason;    /* ע��ʧ�ܵ�ԭ�� */
    VOS_UINT16                                      usSipStatusCode;    /* IMS�ϱ���ע���쳣ԭ��ֵ */
    VOS_CHAR                                        aucPcscfAddr[IMSA_ERR_LOG_IPV6_STRING_LEN+1];
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8         enImsaCampedRatType;/**< ��ǰפ������,NULL,2G,3G,LTE */
    VOS_UINT32                                      ulRetryTimerLen;    /* ע��ʧ�����Լ��ʱ�� */
    VOS_UINT8                                       ucIsApnChangeFlag;  /* APN�Ƿ����ı� */
    VOS_UINT8                                       aucRsv[3];
} IMSA_ERR_LOG_NORM_REG_FAIL_STRU;

/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ���ϱ���ͨ��ȥע���ԭ��ֵ��������û������
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;           /*��Ϣͷ*/
    IMSA_ERR_LOG_INIT_DEREG_REASON_ENUM_UINT32          enInitDeregCause;   /*  */
    IMSA_ERR_LOG_CAMPED_RAT_TYPE_ENUM_UINT8             enImsaCampedRatType;/**< ��ǰפ������,NULL,2G,3G,LTE */
    VOS_UINT8                                           aucRsv[3];
} IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU;


/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : �л�ʧ�ܣ��ϱ���ǰ�������ͺʹ���ԭ��ֵ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                              stHeader;           /*��Ϣͷ*/
    IMSA_ERR_LOG_CALL_TYPE_ENUM_UINT8                   enCurCallType;      /* ��ǰ�������� */
    IMSA_ERR_LOG_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8 enResStatus;        /* ��ԴԤ������״̬���ӿ����� */
    VOS_UINT16                                          usSipStatusCode;    /* ����ԭ��ֵ */
} IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU;


/*****************************************************************************
 �ṹ����   :IMSA_ERR_LOG_ERRLOG_IMS_REGISTER_FAILURE_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMSע��ʧ�ܽṹ
*****************************************************************************/
typedef struct
{
    OM_ERR_LOG_HEADER_STRU                      stHeader;           /*��Ϣͷ*/
    VOS_UINT32                                  ulCount;                            /* ������������� */
} IMSA_ERR_LOG_MNTN_EVENT_STRU;

/*****************************************************************************
 �ṹ����   : IMSA_ERR_LOG_REPORT_REQ_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : OM���͸�IMSA��ERROR REQ��Ϣ�ṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT16                          usModemID;
    VOS_UINT8                           aucRsv[2];
}IMSA_ERR_LOG_REPORT_REQ_STRU;

/*****************************************************************************
 �ṹ����   : IMSA_ERR_LOG_ERR_LOG_REPORT_CNF_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMSA�ظ�ERRLOGӦ�����ݽṹ
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgName;
    VOS_UINT32                          ulMsgType;
    VOS_UINT32                          ulMsgSN;
    VOS_UINT32                          ulRptlen;      /* �������ݳ���,���ulRptlenΪ0,aucContent���ݳ���ҲΪ0 */
    VOS_UINT8                           aucContent[4]; /* �������� */
} IMSA_ERR_LOG_REPORT_CNF_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_REG_FAIL_STRU          stImsaRegErrlog;
}IMSA_REG_ERROR_LOG_INFO_STRU;
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_CALL_FAIL_STRU         stImsaCallErrlog;
}IMSA_CALL_ERROR_LOG_INFO_STRU;


typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_NOT_INIT_REG_STRU      stImsaNotInitReg;
}IMSA_NOT_INIT_REG_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_PDN_CONN_FAIL_STRU     stImsaPdnConnFail;
}IMSA_NORM_PDN_CONN_FAIL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_NORM_REG_FAIL_STRU     stImsaNormRegFail;
}IMSA_NORM_REG_FAIL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_INIT_DEREG_CAUSE_STRU  stImsaInitDereg;
}IMSA_NORM_INIT_DEREG_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_NORM_CALL_FAIL_STRU    stImsaCallErrlog;
}IMSA_NORM_CALL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_ERR_LOG_EMC_CALL_FAIL_STRU     stImsaEmcCallErrlog;
}IMSA_EMC_CALL_ERROR_LOG_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_ERR_LOG_MODIFY_CALL_TYPE_FAIL_STRU stImsaModCallTypeFail;
}IMSA_MODIFY_CALL_TYPE_ERROR_LOG_INFO_STRU;


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/


/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/










#if (VOS_OS_VER == VOS_WIN32)
#pragma pack()
#else
#pragma pack(0)
#endif




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of LnasErrlogInterface.h */


