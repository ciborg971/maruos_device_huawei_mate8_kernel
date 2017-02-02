


#ifndef __IMSA_IMS_EVENT_H__
#define __IMSA_IMS_EVENT_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
#pragma pack(*)    �����ֽڶ��뷽ʽ
*****************************************************************************/
#if (VOS_OS_VER != VOS_WIN32)
#pragma pack(4)
#else
#pragma pack(push, 4)
#endif

/*****************************************************************************
  2 macro
*****************************************************************************/
#ifdef HW_VOLTE
#ifndef VOS_CHAR
#define VOS_CHAR       char
#endif


#ifndef VOS_UINT8
#define VOS_UINT8      unsigned char
#endif

#ifndef VOS_INT16
#define VOS_INT16      short
#endif

#ifndef VOS_UINT16
#define VOS_UINT16     unsigned short
#endif

#ifndef VOS_INT32
#define VOS_INT32      long
#endif

#ifndef VOS_UINT32
#define VOS_UINT32     unsigned long
#endif
#endif
#define IMSA_IMS_EVENT_STRING_SZ             (128)
#define IMSA_IMS_EVENT_MAX_CALL_LIST_SIZE    (6)
#define IMSA_IMS_NUMBER_STRING_SZ            (80)
#define IMSA_IMS_ALPHA_STRING_SZ             (128)
#define IMSA_IMS_SMS_STRING_SZ               (254)

#define IMSA_IMS_AKA_RAND_STRING_SZ          (16)
#define IMSA_IMS_AKA_AUTN_STRING_SZ          (16)
#define IMSA_IMS_AKA_RESP_STRING_SZ          (16)
#define IMSA_IMS_AKA_IK_STRING_SZ            (16)
#define IMSA_IMS_AKA_CK_STRING_SZ            (16)
#define IMSA_IMS_AKA_AUTS_STRING_SZ          (14)

#define IMSA_IMS_IP_ADDRESS_STRING_SZ        (46)
#define IMSA_IMS_HISTORY_INDEX_STRING_SZ     (8)
#define IMSA_IMS_HISTORY_MAX_LIST_SIZE       (3)
#define IMSA_IMS_IMEI_LEN                    (15)
#define IMSA_IMS_MCC_LEN                     (3)
#define IMSA_IMS_MNC_MAX_LEN                 (3)


#define IMSA_IMS_USSD_STRING_SZ               (182*2)

#define IMSA_IMS_ECONF_CALLED_MAX_NUM           (5)
/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/


/*
 **************************************
 * CSM input event Reason enumeration
 **************************************
*/

/* Reason for this call event. */
enum IMSA_IMS_INPUT_CALL_REASON_ENUM{
    /*
     * The following events are commands from AT interface send as input to IMS
     */
    IMSA_IMS_INPUT_CALL_REASON_DIAL = 0,        /* ATD 'Dial' Command. */
    IMSA_IMS_INPUT_CALL_REASON_REPORT,          /* AT+CLCC 'call list' command. */
    IMSA_IMS_INPUT_CALL_REASON_ANSWER,          /* ATA 'answer' command. */
    IMSA_IMS_INPUT_CALL_REASON_HANGUP,             /* ATH 'Hangup' or reject a single call. */
    IMSA_IMS_INPUT_CALL_REASON_SWAP,            /* AT+CHLD=2.  Swap calls or accept a call waiting. */
    IMSA_IMS_INPUT_CALL_REASON_REL_ACTIVE_AND_ACCEPT_OTH,  /* AT+CHLD=1. End all active calls and accept held or call waiting. */
    IMSA_IMS_INPUT_CALL_REASON_REL_HELD_OR_WAITING, /* AT+CHLD=0. Release all held calls or reject a call waiting. */
    IMSA_IMS_INPUT_CALL_REASON_HOLD_ALL_EXCEPT_X, /* AT+CHLD=2x Request private consultation.  Hold all calls except the one referenced by 'x' (index) */
    IMSA_IMS_INPUT_CALL_REASON_DTMF,           /* AT+VTS genereate a digit tone on the line, */
    IMSA_IMS_INPUT_CALL_REASON_RELEASE_AT_X,    /* AT+CHLD=1x release the call referenced at 'x' (index). */
    IMSA_IMS_INPUT_CALL_REASON_CONFERENCE,      /* AT+CHLD=3 merge in all held calls to current call. */
    IMSA_IMS_INPUT_CALL_REASON_SRVCC_START,     /* +CIREPH:0 SRVCC handover is starting. */
    IMSA_IMS_INPUT_CALL_REASON_SRVCC_SUCCESS,   /* +CIREPH:1 SRVCC handover is successful, call need to release. */
    IMSA_IMS_INPUT_CALL_REASON_SRVCC_FAILED,    /* +CIREPH:2 SRVCC handover is failed or canceled, call need to re-invite. */
    IMSA_IMS_INPUT_CALL_REASON_SRVCC_CANCELED,    /* +CIREPH:3 SRVCC handover is failed or canceled, call need to re-invite. */
    /*
     * Call resource reservation event.
     */
    IMSA_IMS_INPUT_CALL_REASON_RESOURCE_READY,
    IMSA_IMS_INPUT_CALL_REASON_RESOURCE_FAILED,
    /*xiongxianghui00253310 add for conference 20140210 begin */
    IMSA_IMS_INPUT_CALL_REASON_CONFERENCE_INVITE_NEW_PARTICIPANT,
    /*xiongxianghui00253310 add for conference 20140210 end */
    IMSA_IMS_INPUT_CALL_REASON_MODIFY,         /* modify the callType (audio<->video) */
    IMSA_IMS_INPUT_CALL_REASON_ANSWER_REMOTE_MODIFY,    /* answer remote modify req */

    IMSA_IMS_INPUT_CALL_REASON_CREAT_NEW_ECONFERENCE,
    IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_INVITE_NEW_PARTICIPANT,
    IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_MERGER_NEW_PARTICIPANT,
    IMSA_IMS_INPUT_CALL_REASON_ECONFERENCE_KICK_PARTICIPANT,                /* �ͷ�ĳ���û� */
    IMSA_IMS_INPUT_CALL_REASON_RESOURCE_ONLY_VOICE_READY,
    IMSA_IMS_INPUT_CALL_REASON_BUTT
} ;
typedef VOS_UINT32 IMSA_IMS_INPUT_CALL_REASON_ENUM_UINT32;

/* Reason for this SMS event. */
enum IMSA_IMS_INPUT_SMS_REASON_ENUM{
    IMSA_IMS_INPUT_SMS_REASON_SEND_MESSAGE,
    IMSA_IMS_INPUT_SMS_REASON_TR1M_EXP,
    IMSA_IMS_INPUT_SMS_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_INPUT_SMS_REASON_ENUM_UINT32;


/* Reason for this Service event. */
enum IMSA_IMS_INPUT_SERVICE_REASON_ENUM{
    IMSA_IMS_INPUT_SERVICE_REASON_REGISTER ,
    IMSA_IMS_INPUT_SERVICE_REASON_REGISTER_EMERGENCY,
    IMSA_IMS_INPUT_SERVICE_REASON_DEREGISTER ,
    IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER,
    IMSA_IMS_INPUT_SERVICE_REASON_LOCAL_DEREGISTER_EMERGENCY,
    IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SUCCESS,
    IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_NETWORK_FAILURE,
    IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SYNC_FAILURE,
    IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SUCCESS_EMERGENCY,
    IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_NETWORK_FAILURE_EMERGENCY,
    IMSA_IMS_INPUT_SERVICE_REASON_AKA_RESPONSE_SYNC_FAILURE_EMERGENCY,
    IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_NRM_SRV,
    IMSA_IMS_INPUT_SERVICE_REASON_RESUME_NRM_SRV,
    IMSA_IMS_INPUT_SERVICE_REASON_SUSPEND_EMC_SRV,
    IMSA_IMS_INPUT_SERVICE_REASON_RESUME_EMC_SRV,
    IMSA_IMS_INPUT_SERVICE_REASON_BUTT
} ;
typedef VOS_UINT32 IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32;

enum IMSA_IMS_AUTH_TYPE_ENUM{
    IMSA_IMS_AUTH_TYPE_AKA,
    IMSA_IMS_AUTH_TYPE_DIGIST,
    IMSA_IMS_AUTH_TYPE_AKA_IPSEC,
    IMSA_IMS_AUTH_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_IMS_AUTH_TYPE_ENUM_UINT8;

enum IMAS_IMS_INPUT_PARA_REASON_ENUM{
    IMAS_IMS_INPUT_PARA_REASON_SET_CGI,
    IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_IP,
    IMAS_IMS_INPUT_PARA_REASON_SET_EMC_IP,
    IMAS_IMS_INPUT_PARA_REASON_SET_PORTS,
    IMAS_IMS_INPUT_PARA_REASON_SET_IPSEC,
    IMAS_IMS_INPUT_PARA_REASON_SET_NORMAL_ACCOUNT,
    IMAS_IMS_INPUT_PARA_REASON_SET_EMC_ACCOUNT,
    IMAS_IMS_INPUT_PARA_REASON_SET_UE_CAPABILITIES,
    IMAS_IMS_INPUT_PARA_REASON_SET_NETWORK_CAPABILITIES,
    IMAS_IMS_INPUT_PARA_REASON_SET_TIMER_LENGTH,
    IMAS_IMS_INPUT_PARA_REASON_SET_IMEI,
    IMAS_IMS_INPUT_PARA_REASON_SET_CALL_WAITING,
    IMAS_IMS_INPUT_PARA_REASON_SET_ERR_LOG_CTRL_INFO,
    IMAS_IMS_INPUT_PARA_REASON_QUERY_IMPU  = 0x100,
    IMAS_IMS_INPUT_PARA_REASON_BUTT
};
typedef VOS_UINT32   IMAS_IMS_INPUT_PARA_REASON_ENUM_UINT32;

enum IMSA_IMS_INPUT_SYSTEM_REASON_ENUM{
    IMSA_IMS_INPUT_SYSTEM_REASON_START,
    IMSA_IMS_INPUT_SYSTEM_REASON_STOP,
    IMSA_IMS_INPUT_SYSTEM_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_INPUT_SYSTEM_REASON_ENUM_UINT32;

enum IMSA_IMS_INPUT_USSD_REASON_ENUM{
    IMSA_IMS_INPUT_USSD_REASON_AT_CMD_SEND = 0,
    IMSA_IMS_INPUT_USSD_REASON_AT_CMD_DISCONNECT,
    IMSA_IMS_INPUT_USSD_REASON_EVT_SEND_ERROR,/*ʲôʱ��ʹ��*/
    IMSA_IMS_INPUT_USSD_REASON_EVT_SENT_USSD,/*ʲôʱ��ʹ��*/
    IMSA_IMS_INPUT_USSD_REASON_EVT_REQUEST_USSD,/*ʲôʱ��ʹ��*/
    IMSA_IMS_INPUT_USSD_REASON_EVT_NOTIFY_USSD,/*ʲôʱ��ʹ��*/
    IMSA_IMS_INPUT_USSD_REASON_EVT_DISCONNECT_USSD,/*ʲôʱ��ʹ��*/

    IMSA_IMS_INPUT_USSD_REASON_EVT_BUTT
};
typedef VOS_UINT32 IMSA_IMS_INPUT_USSD_REASON_ENUM_UINT32;

enum IMSA_IMS_INPUT_NV_INFO_REASON_ENUM{
    IMSA_IMS_INPUT_NV_INFO_REASON_SIP,
    IMSA_IMS_INPUT_NV_INFO_REASON_VOIP,
    IMSA_IMS_INPUT_NV_INFO_REASON_CODE,
    IMSA_IMS_INPUT_NV_INFO_REASON_SS_CONF,
    IMSA_IMS_INPUT_NV_INFO_REASON_SECURITY,
    IMSA_IMS_INPUT_NV_INFO_REASON_MEDIA,
    IMSA_IMS_INPUT_NV_INFO_REASON_CAPABILITY,
    
    IMSA_IMS_INPUT_NV_INFO_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_INPUT_NV_INFO_REASON_ENUM_UINT32;


/*
 **************************************
 * CSM output response reason enumeration
 **************************************
 */
enum IMSA_IMS_OUTPUT_CALL_REASON_ENUM{
    IMSA_IMS_OUTPUT_CALL_REASON_OK,        /* '0' or 'OK' response to a command. */
    IMSA_IMS_OUTPUT_CALL_REASON_ERROR,     /* +CME ERROR response to a command. The error code will be in the payload. */
    IMSA_IMS_OUTPUT_CALL_REASON_CALL_LIST, /* +CLCC response to a AT+CLCC command. */
    IMSA_IMS_OUTPUT_CALL_REASON_DISCONNECT_EVENT, /* Event indicating that a remote party has disconnected. */
    IMSA_IMS_OUTPUT_CALL_REASON_INCOMING_EVENT, /* Event indicating that a new incoming call is being requested. */
    IMSA_IMS_OUTPUT_CALL_REASON_WAITING_EVENT,  /* Event indicating that a call is waiting. */
    IMSA_IMS_OUTPUT_CALL_REASON_INITIALIZING_EVENT, /*
                                           * Event indicating that a new incoming
                                           * call is initializing but the
                                           * resource is not ready yet.
                                           */
    IMSA_IMS_OUTPUT_CALL_REASON_SRVCC_CALL_LIST,
    IMSA_IMS_OUTPUT_CALL_REASON_EARLY_MEDIA, /* Event indicating that there is early media for outgoing call. */
    IMSA_IMS_OUTPUT_CALL_REASON_EMERGENCY_INDICATION, /* Event to indicate the outgoing call is an emergency call. */
    IMSA_IMS_OUTPUT_CALL_REASON_EXTRA_INFO, /* extra info for forwarded call history */

    IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_IND,   /* Event indicating the modify callType request is coming*/
    IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_BEGIN, /* Event to start modifying */
    IMSA_IMS_OUTPUT_CALL_REASON_MODIFY_END,   /* Event to end modifying */

    IMSA_IMS_OUTPUT_CALL_REASON_ECONF_NOTIFY_IND,   /* �ϱ���ǿ�Ͷ෽ͨ���Ĳ����ߵ�״̬ */

    IMSA_IMS_OUTPUT_CALL_REASON_MT_BEGIN,
    IMSA_IMS_OUTPUT_CALL_REASON_BUTT
 } ;
typedef VOS_UINT32 IMSA_IMS_OUTPUT_CALL_REASON_ENUM_UINT32;


enum IMSA_IMS_OUTPUT_SMS_REASON_ENUM{
    IMSA_IMS_OUTPUT_SMS_REASON_OK,        /* '0' or 'OK' response to a command. */
    IMSA_IMS_OUTPUT_SMS_REASON_ERROR,     /* +CME ERROR response to a command. The error code will be in the payload. */
    IMSA_IMS_OUTPUT_SMS_REASON_SMS_RECEIVED,  /* Event indicating that a SMS was received. */
    IMSA_IMS_OUTPUT_SMS_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_OUTPUT_SMS_REASON_ENUM_UINT32;


enum IMSA_IMS_OUTPUT_SEVICE_REASON_ENUM{
    IMSA_IMS_OUTPUT_SEVICE_REASON_OK,
    IMSA_IMS_OUTPUT_SEVICE_REASON_ERROR,
    IMSA_IMS_OUTPUT_SEVICE_REASON_STATE, /* Event indicating a network registration state change */
    IMSA_IMS_OUTPUT_SEVICE_REASON_AUTH_CHALLENGE,  /* AKA Auth Challenge to isim app */
    IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_SETUP,    /* IPSec ports and SPIs information when IPSec setup */
    IMSA_IMS_OUTPUT_SEVICE_REASON_IPSEC_RELEASE,  /* IPSec ports and SPIs information when IPSec release */
    IMSA_IMS_OUTPUT_SEVICE_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_OUTPUT_SEVICE_REASON_ENUM_UINT32;

enum IMSA_IMS_OUTPUT_PARA_REASON_ENUM{
    IMSA_IMS_OUTPUT_PARA_REASON_SET_OK,
    IMSA_IMS_OUTPUT_PARA_REASON_SET_PORTS_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_CGI_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_NORMAL_IP_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_EMC_IP_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_IPSEC_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_NORMAL_ACCOUNT_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_EMC_ACCOUNT_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_TIMER_LENGTH_ERROR,
    IMAS_IMS_OUTPUT_PARA_REASON_SET_REG_CAPABILITIES_ERROR,

    IMSA_IMS_OUTPUT_PARA_REASON_QUERY_OK  = 0x100,
    IMSA_IMS_OUTPUT_PARA_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_OUTPUT_PARA_REASON_ENUM_UINT32;


enum IMSA_IMS_OUTPUT_SYSTM_REASON_ENUM{
    IMSA_IMS_OUTPUT_SYSTM_REASON_OK,
    IMSA_IMS_OUTPUT_SYSTM_REASON_ERROR,
    IMSA_IMS_OUTPUT_SYSTM_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_OUTPUT_SYSTM_REASON_ENUM_UINT32;


enum IMSA_IMS_OUTPUT_USSD_REASON_ENUM{
    IMSA_IMS_OUTPUT_USSD_REASON_OK,        /* '0' or 'OK' response to a command. */
    IMSA_IMS_OUTPUT_USSD_REASON_ERROR,
    IMSA_IMS_OUTPUT_USSD_REASON_NOTIFY_EVENT, /* Event indicating a new USSD connection.*/
    IMSA_IMS_OUTPUT_USSD_REASON_REQUEST_EVENT, /*Event indicating a USSD request.*/
    IMSA_IMS_OUTPUT_USSD_REASON_DISCONNECT_EVENT, /*Disconnect USSD connection.*/
    IMSA_IMS_OUTPUT_USSD_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_OUTPUT_USSD_REASON_ENUM_UINT32;


enum IMSA_IMS_USSD_ENCTYPE_ENUM{
    IMSA_IMS_USSD_ENCTYPE_UNSPECIFIED   = 0x0f,
    IMSA_IMS_USSD_ENCTYPE_8bit          = 0x44,
    IMSA_IMS_USSD_ENCTYPE_UCS2          = 0x48,

    IMSA_IMS_USSD_ENCTYPE_BUTT
} ;
typedef VOS_UINT8 IMSA_IMS_USSD_ENCTYPE_ENUM_UINT8;

enum IMSA_IMS_OUTPUT_NV_INFO_REASON_ENUM{
    IMSA_IMS_OUTPUT_NV_INFO_REASON_OK,
    IMSA_IMS_OUTPUT_NV_INFO_REASON_ERROR,
    IMSA_IMS_OUTPUT_NV_INFO_REASON_BUTT
};
typedef VOS_UINT32 IMSA_IMS_OUTPUT_NV_INFO_REASON_ENUM_UINT32;


/*
 ******************
 * Call enumeration
 ******************
 */

enum IMSA_IMS_CALL_CLIR_TYPE_ENUM{
    IMSA_IMS_CALL_CLIR_TYPE_NONE = 0,        /* CLIR:????CLIR????? */
    IMSA_IMS_CALL_CLIR_TYPE_INVOCATION,      /* CLIR:?? */
    IMSA_IMS_CALL_CLIR_TYPE_SUPPRESSION,     /* CLIR:?? */
    IMSA_IMS_CALL_CLIR_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_IMS_CALL_CLIR_TYPE_ENUM_UINT8;

enum IMSA_IMS_EMERGENCY_TYPE_ENUM{
    IMSA_IMS_EMERGENCY_SUB_TYPE_NONE = 0,
    IMSA_IMS_EMERGENCY_SUB_TYPE_GENERIC,
    IMSA_IMS_EMERGENCY_SUB_TYPE_AMBULANCE,
    IMSA_IMS_EMERGENCY_SUB_TYPE_POLICE,
    IMSA_IMS_EMERGENCY_SUB_TYPE_FIRE,
    IMSA_IMS_EMERGENCY_SUB_TYPE_MARINE,
    IMSA_IMS_EMERGENCY_SUB_TYPE_MOUNTAIN,
    IMSA_IMS_EMERGENCY_SUB_TYPE_EXTENSION,
    IMSA_IMS_EMERGENCY_SUB_TYPE_BUTT
} ;
typedef VOS_UINT8 IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8;

enum IMSA_IMS_CALL_DIRECTION_ENUM{
    IMSA_IMS_CALL_DIR_MOBILE_ORIGINATED = 0,
    IMSA_IMS_CALL_DIR_MOBILE_TERMINATED,
    IMSA_IMS_CALL_DIR_MOBILE_BUTT
} ;
typedef VOS_UINT8 IMSA_IMS_CALL_DIRECTION_ENUM_UINT8;

enum IMSA_IMS_CALL_STATE_ENUM{
    IMSA_IMS_CALL_STATE_INVALID = 0,
    IMSA_IMS_CALL_STATE_ACTIVE,
    IMSA_IMS_CALL_STATE_HOLD,
    IMSA_IMS_CALL_STATE_TRYING,
    IMSA_IMS_CALL_STATE_DIALING,
    IMSA_IMS_CALL_STATE_ALERTING,
    IMSA_IMS_CALL_STATE_INCOMING,
    IMSA_IMS_CALL_STATE_WAITING,
    IMSA_IMS_CALL_STATE_INITIALIZING,
    IMSA_IMS_CALL_STATE_ACTIVING,   /*�û��������е�״̬δת��ACTIVE��
                                      ����SRVCC���̣���CS��CC��Ҫ��connect��Ϣ*/
    IMSA_IMS_CALL_STATE_BUTT
} ;
typedef VOS_UINT8 IMSA_IMS_CALL_STATE_ENUM_UINT8;

enum IMSA_IMS_ECONF_CALLER_STATE_ENUM{
    IMSA_IMS_ECONF_CALLER_STATE_BOOK = 0,
    IMSA_IMS_ECONF_CALLER_STATE_PREDIALING,
    IMSA_IMS_ECONF_CALLER_STATE_DIALING,
    IMSA_IMS_ECONF_CALLER_STATE_HOLD,
    IMSA_IMS_ECONF_CALLER_STATE_AVTIVE,
    IMSA_IMS_ECONF_CALLER_STATE_DISCONNECT,

    IMSA_IMS_ECONF_CALLER_STATE_BUTT
} ;
typedef VOS_UINT8 IMSA_IMS_ECONF_CALLER_STATE_ENUM_UINT8;

enum IMSA_IMS_CALL_ADDRESS_TYPE_ENUM{
    IMSA_IMS_CALL_ADDRESS_NATIONAL = 129,
    IMSA_IMS_CALL_ADDRESS_INTERNATIONAL = 145,
    IMSA_IMS_CALL_ADDRESS_TYPE_3
} ;
typedef VOS_UINT32 IMSA_IMS_CALL_ADDRESS_TYPE_ENUM_UINT32;

enum IMSA_IMS_CALL_MULTIPARTY_ENUM{
    IMSA_IMS_CALL_SINGLE_PARTY = 0,
    IMSA_IMS_CALL_CONFERENCE,
    IMSA_IMS_CALL_ECONFERENCT,
    IMSA_IMS_CALL_MULTIPARTY_BUTT
} ;
typedef VOS_UINT8 IMSA_IMS_CALL_MULTIPARTY_ENUM_UINT8;

enum IMSA_IMS_CALL_MODE_ENUM{
    IMSA_IMS_CALL_MODE_VOICE    = 0,        /* Voice only call */
	IMSA_IMS_CALL_MODE_VIDEO_TX = 1,        /* PS Video telephony call: one way TX video,Two way audio */
    IMSA_IMS_CALL_MODE_VIDEO_RX = 2,        /* Video telephony call: ony way RX video,two way audio */
    IMSA_IMS_CALL_MODE_VIDEO    = 3,        /* Video telephony call: two way Video,* two way audio */
    IMSA_IMS_CALL_TYPE_EMC      = 9,
    IMSA_IMS_CALL_MODE_BUTT
} ;
typedef VOS_UINT8 IMSA_IMS_CALL_MODE_ENUM_UINT8;

enum IMSA_IMS_CALL_CAUSE_CODE_ENUM{
    IMSA_IMS_CALL_CAUSE_CODE_NONE            = 0,
    IMSA_IMS_CALL_CAUSE_CODE_UNKNOWN         = 404,
    IMSA_IMS_CALL_CAUSE_CODE_BUSY            = 486,
    IMSA_IMS_CALL_CAUSE_CODE_NOREPLY         = 408,
    IMSA_IMS_CALL_CAUSE_CODE_UNCONDITIONAL   = 302,
    IMSA_IMS_CALL_CAUSE_CODE_NOTREACHABLE    = 503
} ;
typedef VOS_UINT32 IMSA_IMS_CALL_CAUSE_CODE_ENUM_UINT32;



/*
 ******************
 * Service enumeration
 ******************
 */

enum IMSA_IMS_SERVICE_STATE_ENUM{
    IMSA_IMS_SERVICE_STATE_INACTIVE = 0, // similar +CREG:0
    IMSA_IMS_SERVICE_STATE_ACTIVE,       // similar +CREG:1
    IMSA_IMS_SERVICE_STATE_REGISTERING,  // similar +CREG:2
    IMSA_IMS_SERVICE_STATE_FAILED,       // similar +CREG:3
    IMSA_IMS_SERVICE_STATE_UNKNOWN,      // similar +CREG:4
    IMSA_IMS_SERVICE_STATE_ROAMING,      // similar +CREG:5
    IMSA_IMS_SERVICE_STATE_DEREGISTERING, /* Specific state to indicte we are doing deregister. No mapping CREG value. */
    IMSA_IMS_SERVICE_STATE_BUTT
};
typedef VOS_UINT32  IMSA_IMS_SERVICE_STATE_ENUM_UINT32;



/*
 * CSSI/CSSU report supported code
 * +CSSI
 *      2 call has been forwarded
 *      3 call is waiting
 *      8 call has been deflected
 * +CSSU
 *      0 this is a forwarded call
 *      2 call has been put on hold
 *      3 call has been retrieved
 *      4 multiparty call entered
 *      7 Explicit Call Transfer (ECT) Supplementary Service
 *      9 this is a deflected call
 */
enum IMSA_IMS_SUPSRV_CALL_NOTICE_ENUM{
    IMSA_IMS_SUPSRV_CALL_NONE = 0,
    IMSA_IMS_SUPSRV_MO_CALL_BEING_FORWARDED,
    IMSA_IMS_SUPSRV_MO_CALL_IS_WAITING,
    IMSA_IMS_SUPSRV_MO_CALL_BE_DEFLECTED,
    IMSA_IMS_SUPSRV_MT_CALL_IS_FORWARDED,
    IMSA_IMS_SUPSRV_MT_CALL_IS_HELD,
    IMSA_IMS_SUPSRV_MT_CALL_IS_UNHELD,
    IMSA_IMS_SUPSRV_MT_CALL_JOINED_CONFCALL,
    IMSA_IMS_SUPSRV_MT_CALL_EXPLICIT_CALL_TRANSFER,
    IMSA_IMS_SUPSRV_MT_CALL_IS_DEFLECTED_CALL,
} ;
typedef VOS_UINT32 IMSA_IMS_SUPSRV_CALL_NOTICE_ENUM_UINT32;

enum IMSA_IMS_NW_ACCESS_TYPE_ENUM
{
    IMSA_IMS_NW_ACCESS_TYPE_3GPP_GERAN         = 0,
    IMSA_IMS_NW_ACCESS_TYPE_3GPP_UTRAN_FDD,
    IMSA_IMS_NW_ACCESS_TYPE_3GPP_UTRAN_TDD,
    IMSA_IMS_NW_ACCESS_TYPE_3GPP_EUTRAN_FDD,
    IMSA_IMS_NW_ACCESS_TYPE_3GPP_EUTRAN_TDD,

    IMSA_IMS_NW_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_IMS_NW_ACCESS_TYPE_ENUM_UINT8;

enum IMSA_IMS_RAT_TYPE_ENUM
{
    IMSA_IMS_RAT_TYPE_GSM              =0,
    IMSA_IMS_RAT_TYPE_UTRAN,
    IMSA_IMS_RAT_TYPE_LTE,
    IMSA_IMS_RAT_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_IMS_RAT_TYPE_ENUM_UINT8;

enum IMSA_IMS_EVENT_TYPE_ENUM
{
    IMSA_IMS_EVENT_TYPE_SYSTEM = 0,
    IMSA_IMS_EVENT_TYPE_PARA,
    IMSA_IMS_EVENT_TYPE_SERVICE,
    IMSA_IMS_EVENT_TYPE_SMS,
    IMSA_IMS_EVENT_TYPE_CALL,
    IMSA_IMS_EVENT_TYPE_USSD,
    IMSA_IMS_EVENT_TYPE_NV_INFO,

    IMSA_IMS_EVENT_TYPE_BUTT
};
typedef VOS_UINT32 IMSA_IMS_EVENT_TYPE_ENUM_UINT32;


enum IMSA_IMS_INT_ERROR_CODE_ENUM
{
    IMSA_IMS_INT_ERROR_CODE_UNKNOW         = 0,
    IMSA_IMS_INT_ERROR_CODE_INNER_ERROR,         /* sdk inner error */
    IMSA_IMS_INT_ERROR_CODE_TCP_ERROR,           /* tcp disconnect */
    IMSA_IMS_INT_ERROR_CODE_TIMERF_OUT,          /* timer f expire */
    IMSA_IMS_INT_ERROR_CODE_IPSEC_ERROR,         /* ipsec error */
    IMSA_IMS_INT_ERROR_CODE_UNKNOW_SESSION,      /* the session is not exit */

    IMSA_IMS_INT_ERROR_CODE_SMS_INCAPABILITY,    /* incapability to send sms */
    IMSA_IMS_INT_ERROR_CODE_SMS_NO_SMSC,         /* bitOpSmsc error when SMS RP type is RP data */
    IMSA_IMS_INT_ERROR_CODE_SMS_NO_IPSMGW,       /* no set IP-SM-GW */

    /* xiongxianghui00253310 add for conference 20140214 begin */
    IMSA_IMS_INT_ERROR_CODE_CONFERENCE_SRVCC,
    /* xiongxianghui00253310 add for conference 20140214 end */

    IMSA_IMS_INT_ERROR_CODE_MODIFY_TIMEA_OUT,

    IMSA_IMS_INT_ERROR_CODE_NOTIFY_DEREGISTER,  /* Notify sip message indicates user terminates.*/

    IMSA_IMS_INT_ERROR_CODE_REGISTER_TIMER_OUT,
    IMSA_IMS_INT_ERROR_CODE_STRM_RTP_BREAK,

    IMSA_IMS_INT_ERROR_CODE_BUTT
};
typedef VOS_UINT8 IMSA_IMS_INT_ERROR_CODE_ENUM_UINT8;

enum IMSA_IMS_3GPP_TYPE_ACTION_ENUM
{
    IMSA_IMS_3GPP_TYPE_ACTION_UNKNOW         = 0,
    IMSA_IMS_3GPP_TYPE_ACTION_RESTORATION,                  /* <type> restoration */

    IMSA_IMS_3GPP_TYPE_ACTION_RESTORATION_INIT_REG,         /* <type> restoration
                                                             * <action> initial-registration
                                                             */

    IMSA_IMS_3GPP_TYPE_ACTION_EMERGENCY,                    /* <type> emergency */

    IMSA_IMS_3GPP_TYPE_ACTION_EMERGENCY_REG,                /* <type> emergency
                                                             * <action> emergency-registration
                                                             */
    IMSA_IMS_3GPP_TYPE_ACTION_BUTT
};
typedef VOS_UINT8 IMSA_IMS_3GPP_TYPE_ACTION_ENUM_UINT8;

enum IMSA_IMS_DTMF_KEY_ENUM
{
    IMSA_IMS_DTMF_KEY_0                     = 0,    /* character "0" */
    IMSA_IMS_DTMF_KEY_1                     = 1,    /* character "1" */
    IMSA_IMS_DTMF_KEY_2                     = 2,    /* character "2" */
    IMSA_IMS_DTMF_KEY_3                     = 3,    /* character "3" */
    IMSA_IMS_DTMF_KEY_4                     = 4,    /* character "4" */
    IMSA_IMS_DTMF_KEY_5                     = 5,    /* character "5" */
    IMSA_IMS_DTMF_KEY_6                     = 6,    /* character "6" */
    IMSA_IMS_DTMF_KEY_7                     = 7,    /* character "7" */
    IMSA_IMS_DTMF_KEY_8                     = 8,    /* character "8" */
    IMSA_IMS_DTMF_KEY_9                     = 9,    /* character "9" */
    IMSA_IMS_DTMF_KEY_STAR                  = 10,    /* character "*" */
    IMSA_IMS_DTMF_KEY_POUND                 = 11,    /* character "#" */
    IMSA_IMS_DTMF_KEY_A                     = 12,    /* character "A" */
    IMSA_IMS_DTMF_KEY_B                     = 13,    /* character "B" */
    IMSA_IMS_DTMF_KEY_C                     = 14,    /* character "C" */
    IMSA_IMS_DTMF_KEY_D                     = 15,    /* character "D" */

    IMSA_IMS_DTMF_KEY_BUTT
};
typedef VOS_UINT8 IMSA_IMS_DTMF_KEY_ENUM_UINT8;


enum IMSA_IMS_SERVICE_NOTIFY_EVENT_ENUM
{
    IMSA_IMS_SERVICE_NOTIFY_EVENT_UNKNOW    = 0,   /* unknown */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_REGED,           /* registered */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_CREATED,         /* created */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_REFRESHED,       /* refreshed */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_SHORTENED,       /* shortened */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_EXPIRED,         /* expired */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_DEACTED,         /* deactived */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_PROBATION,       /* probation */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_UNREGED,         /* unregistered */
    IMSA_IMS_SERVICE_NOTIFY_EVENT_REJED            /* rejected */
};
typedef VOS_UINT8 IMSA_IMS_SERVICE_NOTIFY_EVENT_ENUM_UINT8;


/*****************************************************************************
  5 STRUCT
*****************************************************************************/

/*
 **************************************
 *  IMSA_IMS input event structure
 **************************************
 */
/*****************************************************************************
 �ṹ��    : IMSA_IMS_CALLED_NUM_STRU
 �ṹ˵��  : IMSA����IMS�ı��к���Ľṹ��
*****************************************************************************/
typedef struct {
    VOS_CHAR                                aucRemoteAddress[IMSA_IMS_EVENT_STRING_SZ + 1];
    VOS_UINT8                               aucRsv[3];
} IMSA_IMS_CALLED_NUM_STRU;
/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_CALL_EVENT_STRU
 �ṹ˵��  : IMSA����IMS�ĺ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                              bitOpCallIndex:1;
    VOS_UINT32                              bitOpEmergencyType:1;
    VOS_UINT32                              bitOpRemoteAddress:1;
    VOS_UINT32                              bitOpClirType:1;
    VOS_UINT32                              bitOpDtmf:1;
    VOS_UINT32                              bitOpModify:1;
    VOS_UINT32                              bitOpEconfList:1;
    VOS_UINT32                              bitOpSpare:25;

    IMSA_IMS_INPUT_CALL_REASON_ENUM_UINT32  enInputCallReason;
    VOS_UINT32                              ulOpId;
    VOS_UINT32                              ulCallIndex;
    IMSA_IMS_CALL_MODE_ENUM_UINT8           enCallType;
    IMSA_IMS_EMERGENCY_TYPE_ENUM_UINT8      enEmergencyType;
    VOS_CHAR                                aucRemoteAddress[IMSA_IMS_EVENT_STRING_SZ + 1];

    IMSA_IMS_CALL_CLIR_TYPE_ENUM_UINT8      enClirCfg;
    struct{
        IMSA_IMS_DTMF_KEY_ENUM_UINT8        enDtmfKey;
        VOS_UINT8                           aucRsv[3];
        VOS_UINT32                          ulDuration;/*��λms*/
    } stDtmf;
    struct{
        IMSA_IMS_CALL_MODE_ENUM_UINT8       enSrcCallType;
        IMSA_IMS_CALL_MODE_ENUM_UINT8       enDstCallType;
        VOS_UINT8                           aucRsv[2];
    } stModify;
    struct{
        VOS_UINT8                           ucNumCalls;
        VOS_UINT8                           aucRsv[3];
        IMSA_IMS_CALLED_NUM_STRU            astEconfList[IMSA_IMS_ECONF_CALLED_MAX_NUM];
    } stEconfList;
} IMSA_IMS_INPUT_CALL_EVENT_STRU;
/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_SMS_EVENT_STRU
 �ṹ˵��  : IMSA����IMS�Ķ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                           bitOpPdu:1;
    VOS_UINT32                           bitOpSmsc:1;
    VOS_UINT32                           bitOpSpare:30;

    IMSA_IMS_INPUT_SMS_REASON_ENUM_UINT32 enInputSmsReason;
    VOS_UINT32                           ulOpId;
    VOS_UINT8                            ucPduLen;
    VOS_CHAR                             acPdu[IMSA_IMS_SMS_STRING_SZ + 1];
    VOS_CHAR                             acSmsc[IMSA_IMS_ALPHA_STRING_SZ + 1];
    VOS_UINT8                            aucRsv[3];
} IMSA_IMS_INPUT_SMS_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_SERVICE_EVENT_STRU
 �ṹ˵��  : IMSA����IMS�ķ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                                  bitOpAka:1;
    VOS_UINT32                                  bitOpSpare:31;

    IMSA_IMS_INPUT_SERVICE_REASON_ENUM_UINT32   enInputServeReason;
    VOS_UINT32                                  ulOpId;
    struct {
        VOS_UINT8      aucResponse[IMSA_IMS_AKA_RESP_STRING_SZ]; /* size is 16 */
        VOS_UINT8      aucAuts[IMSA_IMS_AKA_AUTS_STRING_SZ];     /* size is 14 */
        VOS_UINT8      aucIk[IMSA_IMS_AKA_IK_STRING_SZ];         /* size is 16 */
        VOS_UINT8      aucCk[IMSA_IMS_AKA_CK_STRING_SZ];         /* size is 16 */
        VOS_UINT8      aucRsv[2];
        VOS_UINT32     ulResLength;
    } stAka;
} IMSA_IMS_INPUT_SERVICE_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_SERVICE_EVENT_STRU
 �ṹ˵��  : IMSA����IMS�ķ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                                  ulOpId;
    IMSA_IMS_INPUT_NV_INFO_REASON_ENUM_UINT32    enInputNvInfoReason;
    VOS_UINT32                                  ulNvInfoLen; /* ��ȡ��NV�ṹ�峤�� */
    VOS_UINT8                                   aucNvInfo[4]; /* ��ȡ��NV���� */
}IMSA_IMS_INPUT_NV_INFO_EVENT_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_PARA_EVENT_STRU
 �ṹ˵��  : IMSA����IMS�Ĳ��������¼��ṹ
*****************************************************************************/
typedef struct{
    IMAS_IMS_INPUT_PARA_REASON_ENUM_UINT32  enInputParaReason;
    VOS_UINT32                              ulOpId;
    union {
        struct {
            IMSA_IMS_NW_ACCESS_TYPE_ENUM_UINT8      enNwAccessType;
            VOS_UINT8                               aucReserved[3];
            VOS_CHAR                                cMcc[IMSA_IMS_MCC_LEN + 1];/*��'\0����β */
            VOS_CHAR                                cMnc[IMSA_IMS_MNC_MAX_LEN + 1];/*��'\0����β */
            VOS_UINT16                              usLac;/*enNwAccessTypeֵΪ0-2ʱ��Ч*/
            VOS_UINT16                              usTac;/*enNwAccessTypeֵΪ3-4ʱ��Ч*/
            VOS_UINT32                              ulCellId;/*enNwAccessTypeֵΪ0ʱ����ЧֵΪ��16bit��enNwAccessTypeֵΪ1-4ʱ����ЧֵΪ��28bit */
        } stCgi;
        struct{
            VOS_CHAR      acPcscf[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acUeAddress[IMSA_IMS_IP_ADDRESS_STRING_SZ+1];
        }stNormalIp;
        struct{
            VOS_CHAR      acPcscf[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acUeAddress[IMSA_IMS_IP_ADDRESS_STRING_SZ+1];
        }stEmcIp;
        struct {
            VOS_CHAR      acDomain[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acImpi[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acImpu[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acPassword[IMSA_IMS_EVENT_STRING_SZ + 1];
            IMSA_IMS_AUTH_TYPE_ENUM_UINT8 enAuthType;
            VOS_UINT8     aucRsv[3];
        } stNormalAccount;
        struct {
            VOS_CHAR      acDomain[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acImpi[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acImpu[IMSA_IMS_EVENT_STRING_SZ + 1];
            VOS_CHAR      acPassword[IMSA_IMS_EVENT_STRING_SZ + 1];
            IMSA_IMS_AUTH_TYPE_ENUM_UINT8 enAuthType;
            VOS_UINT8     aucRsv[3];
        } stEmcAccount;
        struct {
            VOS_UINT16    usMinPort;
            VOS_UINT16    usMaxPort;
        } stPortInfo;
        struct {
            VOS_UINT32    ulProtectedPort;        /* protected port */
            VOS_UINT32    ulProtectedPortPoolSz;  /* protected port pool size */
            VOS_UINT32    ulSpi;                  /* SPI start */
            VOS_UINT32    ulSpiPoolSz;            /* spi pool size */
        } stIpSec;
        struct{
            VOS_UINT8     ucVoiceCall;            /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     ucVideoCall;            /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     ucSms;                  /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     ucSrvcc;                /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     ucSrvccMidCall;         /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     ucSrvccAlerting;        /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     ucSrvccPreAlerting;     /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     ucSrvccTiFlag;          /*0 R10�汾��1 R11֮��汾*/
            VOS_UINT8     ucCallWaiting;          /*0 ��֧�֣�1 ֧��*/
            VOS_UINT8     aucRsv[3];
        } stUeCapability;
        struct{
            VOS_UINT8                               ucVoice;                /*0 ��֧�֣�1 ֧��*/
            IMSA_IMS_RAT_TYPE_ENUM_UINT8            enNwRatType;
            VOS_UINT8                               aucRsv[2];
        } stNetworkCapability;
        struct{
            VOS_UINT32    ulRetryTimerLength;     /*����Ϊ0����ʾ����Ч*/
            VOS_UINT32    ulPeriodRergisterTimerLength;/*����Ϊ0����ʾ����Ч*/
        } stTimerLength;
        VOS_CHAR       cImei[IMSA_IMS_IMEI_LEN + 1];
        struct
        {
            VOS_UINT8     ucErrlogCtrlFlag;       /* �澯״̬��Ĭ��0:close;1:open */
            VOS_UINT8     ucReserved;
            VOS_UINT16    usAlmLevel;             /* ����&�澯����
                                                  Warning: 0x04������ʾ
                                                  Minor: 0x03�����Ҫ
                                                  Major: 0x02������Ҫ
                                                  Critical: 0x01�������(Ĭ��)
                                                  ˵����ֵΪ0x03�� 0x03/0x02/0x01���ϱ� */
        }stErrlogCtrlInfo;
    }u;

}IMSA_IMS_INPUT_PARA_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_SYSTEM_EVENT_STRU
 �ṹ˵��  : IMSA����IMS��ϵͳ�¼��ṹ
*****************************************************************************/
typedef struct{
    IMSA_IMS_INPUT_SYSTEM_REASON_ENUM_UINT32   enInputSysReason;
    VOS_UINT32                                 ulOpId;
}IMSA_IMS_INPUT_SYSTEM_EVENT_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_USSD_EVENT_STRU
 �ṹ˵��  : IMSA����IMS��USSD�¼��ṹ
*****************************************************************************/
typedef struct {
    IMSA_IMS_INPUT_USSD_REASON_ENUM_UINT32      enInputUssdReason;
    VOS_UINT32                                  ulOpId;
    IMSA_IMS_USSD_ENCTYPE_ENUM_UINT8            encType; /* CSM_USSD_ENCTYPE_ASCII: ASCII encoding. CSM_USSD_ENCTYPE_UCS2: UCS-2 encoding on message field */
    VOS_UINT8                                   ucRsv;
    VOS_UINT16                                  usMessageLen;
    VOS_UINT8                                   ucMessage[IMSA_IMS_USSD_STRING_SZ+1]; /*HexString encoding */
    VOS_UINT8                                   aucRsv[3];
} IMSA_IMS_INPUT_USSD_EVENT_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_IMS_INPUT_EVENT_STRU
 �ṹ˵��  : IMSA��IMS���¼��ṹ
*****************************************************************************/
typedef struct {
    IMSA_IMS_EVENT_TYPE_ENUM_UINT32          enEventType; /* Type of message */
    union {
        IMSA_IMS_INPUT_SYSTEM_EVENT_STRU     stInputSystemEvent;
        IMSA_IMS_INPUT_PARA_EVENT_STRU       stInputParaEvent;
        IMSA_IMS_INPUT_SERVICE_EVENT_STRU    stInputServiceEvent;
        IMSA_IMS_INPUT_SMS_EVENT_STRU        stInputSmsEvent;
        IMSA_IMS_INPUT_CALL_EVENT_STRU       stInputCallEvent;
        IMSA_IMS_INPUT_USSD_EVENT_STRU       stInputUssdEvent;
        IMSA_IMS_INPUT_NV_INFO_EVENT_STRU    stInputNvInfoEvent;
    } evt;
} IMSA_IMS_INPUT_EVENT_STRU;

/*
 **************************************
 *  IMSA_IMS output event struct
 **************************************
 */

/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_ERROR_STRU
 �ṹ˵��  : IMS����IMSA����Ӧ�¼��е�error�ṹ
*****************************************************************************/
typedef struct{
    VOS_UINT16      usSipStatusCode; /* sip status code
                                      * 1~255 means inner error < IMSA_IMS_INT_ERROR_CODE_ENUM >
                                      * 300~699 means SIP status code
                                      */
    VOS_UINT16      usIms3gppAction; /* IM CN subsystem XML body < IMSA_IMS_3GPP_TYPE_ACTION_ENUM >
                                      * <ims-3gpp>
                                      *     <alternative-service>
                                      *         <type>
                                      *         <action>
                                      */
    VOS_CHAR        acReason[128];   /* IM CN subsystem XML body
                                      * <ims-3gpp>
                                      *     <alternative-service>
                                      *         <reason>
                                      */
    VOS_UINT32      ulRetryAfter;    /* the retry-after header in SIP Oxx message,��λΪs,0��ʾ��Ч */
    VOS_UINT8       ucEmergencyType; /* the emergency service type <IMSA_IMS_EMERGENCY_TYPE_ENUM> */
    VOS_UINT8       ucServerNtyEvent;  /* @IMSA_IMS_SERVICE_NOTIFY_EVENT_ENUM_UINT8*/
    VOS_CHAR        acReserved[2];
}IMSA_IMS_OUTPUT_ERROR_STRU;

typedef struct {
    VOS_UINT32                              bitOpError:1;
    VOS_UINT32                              bitOpSpare:31;

    IMSA_IMS_ECONF_CALLER_STATE_ENUM_UINT8 enCallState;
    VOS_CHAR                               acNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_CHAR                               acConnectNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_CHAR                               acRedirectNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_UINT8                              ucTi;
    VOS_CHAR                               acAlpha[IMSA_IMS_ALPHA_STRING_SZ + 1];
    VOS_UINT8                               aucRsv[2];
    IMSA_IMS_CALL_ADDRESS_TYPE_ENUM_UINT32 enCallAddreeType; /* The 'type' of address. */
    IMSA_IMS_OUTPUT_ERROR_STRU             stErrorCode;
}IMSA_IMS_CALL_ECONF_SUMMARY_STRU;

/*
 * CLCC responses are of the form:
 *
 * +CLCC: <index>,<dir>,<state>,<mode>,<mpty>[,<number>,<type>[,<alpha>]]
 * <index> is the index of the call
 * <dir> is the direction of the mobile originated or terminated
 * <state> is the state of the call
 * <mode> is a number representing whether the call is voice, data, etc.
 * <mpty> is a flag indicating whether the call is multi-party
 * <number> is the phone number (address)
 * <type> is the type of phone number
 * <alpha> is the CID name associated with the number.
 *
 */
typedef struct {
    VOS_UINT32                             ulCallIndex; /* The 'identifier or index of the call. */
    IMSA_IMS_CALL_DIRECTION_ENUM_UINT8     enCallDirection; /* The direction of the call e.g. mobile originated or terminated. */
    IMSA_IMS_CALL_STATE_ENUM_UINT8         enCallState; /* The state of the call. */
    IMSA_IMS_CALL_MODE_ENUM_UINT8          enCallMode;
    IMSA_IMS_CALL_MULTIPARTY_ENUM_UINT8    enMultiParty; /* 0 = is a single call.  1 = is a multiparty call. */
    VOS_CHAR                               acNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_CHAR                               acConnectNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_CHAR                               acRedirectNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_UINT8                              ucIsLocalAlertingFlag; /* 0 = is early media. 1 = is local ring */
    IMSA_IMS_CALL_ADDRESS_TYPE_ENUM_UINT32 enCallAddreeType; /* The 'type' of address. */
    VOS_CHAR                               acAlpha[IMSA_IMS_ALPHA_STRING_SZ + 1];
    VOS_UINT8                              aucRsv2[3];
} IMSA_IMS_CALL_SUMMARY_STRU;
typedef struct {
    VOS_UINT32                              ulNumCalls;
    IMSA_IMS_CALL_SUMMARY_STRU              astCalls[IMSA_IMS_EVENT_MAX_CALL_LIST_SIZE];
} IMSA_IMS_CALL_REPORT_STRU;

typedef struct {
    VOS_UINT32                              ulCallIndex;
    IMSA_IMS_OUTPUT_ERROR_STRU              stErrorCode;
} IMSA_IMS_CALL_ERROR_STRU;

typedef struct{
    VOS_CHAR                                acNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_UINT8                               aucRsv[3];
    IMSA_IMS_CALL_ADDRESS_TYPE_ENUM_UINT32  enCallAddreeType;                             /* The 'type' of address. */
    VOS_CHAR                                acAlpha[IMSA_IMS_ALPHA_STRING_SZ + 1];
    VOS_UINT8                               aucRsv2[3];
}IMSA_IMS_CALL_CLIP_STRU;


typedef struct {
    VOS_UINT32                              ulCallIndex; /* The 'identifier or index of the call. */
    IMSA_IMS_CALL_STATE_ENUM_UINT8          enCallState; /* The state of the call. */
    VOS_UINT8                               ucTi;
    IMSA_IMS_CALL_MULTIPARTY_ENUM_UINT8     enMultiParty; /* 0 = is a single call.  1 = is a multiparty call. */
    VOS_UINT8                               ucRsv;
    IMSA_IMS_CALL_ADDRESS_TYPE_ENUM_UINT32  enCallAddreeType; /* The 'type' of address. */
    VOS_CHAR                                acNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the remote party. */
    VOS_UINT8                               aucRsv2[3];
} IMSA_IMS_SRVCC_CALL_INFO_STRU;


typedef struct {
    VOS_UINT32                              ulCallNum;
    IMSA_IMS_SRVCC_CALL_INFO_STRU           astCallInfo[IMSA_IMS_EVENT_MAX_CALL_LIST_SIZE];
    VOS_UINT8                               ucHifiStatus;   /* 0:�رգ� 1:�� */
    VOS_UINT8                               aucRsv[3];
}IMSA_IMS_SRVCC_CALL_LIST_STRU;


typedef struct {
    IMSA_IMS_CALL_CAUSE_CODE_ENUM_UINT32    enCause;
    VOS_CHAR                                acHiIndex[IMSA_IMS_HISTORY_INDEX_STRING_SZ]; /* hi-index, e.g. "1.1" */
    VOS_CHAR                                acNumber[IMSA_IMS_NUMBER_STRING_SZ + 1]; /* The address of the party. */
    VOS_UINT8                               aucRsv[3];
    IMSA_IMS_CALL_ADDRESS_TYPE_ENUM_UINT32  enCallAddreeType; /* The 'type' of address. */
    VOS_CHAR                                acAlpha[IMSA_IMS_ALPHA_STRING_SZ + 1];
    VOS_UINT8                               aucRsv2[3];
} IMSA_IMS_CALL_HISTORY_STRU;

typedef struct {
    VOS_UINT32                              ulCallIndex; /* The identifier or index of the main call */
    IMSA_IMS_SUPSRV_CALL_NOTICE_ENUM_UINT32 enSupsrvNotification; /* valid values: IMSA_IMS_SupsrvCallNotice */
    VOS_UINT32                              ulNumHistories;
    IMSA_IMS_CALL_HISTORY_STRU              astCallHistories[IMSA_IMS_HISTORY_MAX_LIST_SIZE];
} IMSA_IMS_CALL_SUPSRV_INFO_STRU;

typedef struct {
    VOS_UINT32                              bitOpErrorCode:1;
    VOS_UINT32                              bitOpSpare:31;

    VOS_UINT32                              ulCallIndex;

    IMSA_IMS_CALL_MODE_ENUM_UINT8           enSrcCallMode;  /* IMSA_IMS_CALL_MODE_ENUM_UINT8 */
    IMSA_IMS_CALL_MODE_ENUM_UINT8           enDstCallMode;  /* IMSA_IMS_CALL_MODE_ENUM_UINT8 */
    VOS_UINT8                               ucResult;       /* 0:succ   1:fail*/
    VOS_UINT8                               ucResver;
    IMSA_IMS_OUTPUT_ERROR_STRU              stErrorCode;    /* ����Modify״̬Ϊendʱ���ҽ��Ϊfailʱ����Ч */
}IMSA_IMS_CALL_MODIFY_STRU;
/*****************************************************************************
 �ṹ��    : IMSA_IMS_CALL_ECONF_NOTIFY_IND_STRU
 �ṹ˵��  : IMS����IMSA����ǿ�Ͷ෽ͨ��������״̬�Ľṹ��
*****************************************************************************/
typedef struct {
    VOS_UINT32                              ulCallConfId;
    VOS_UINT8                               ucMaxUserNum;
    VOS_UINT8                               ucCurUserNum;
    VOS_UINT8                               aucRsv[2];
    IMSA_IMS_CALL_ECONF_SUMMARY_STRU        astCalls[IMSA_IMS_ECONF_CALLED_MAX_NUM];
}IMSA_IMS_CALL_ECONF_NOTIFY_IND_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_CALL_EVENT_STRU
 �ṹ˵��  : IMS����IMSA�ĺ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                              bitOpReport:1;
    VOS_UINT32                              bitOpError:1;
    VOS_UINT32                              bitOpClip:1;
    VOS_UINT32                              bitOpSrvccList:1;
    VOS_UINT32                              bitOpSupsrvInfo:1;
    VOS_UINT32                              bitOpModify:1;
    VOS_UINT32                              bitOpEconfNotifyInd:1;
    VOS_UINT32                              bitOpSpare:25;

    IMSA_IMS_OUTPUT_CALL_REASON_ENUM_UINT32 enOutputCallReason;
    VOS_UINT32                              ulOpId;

    IMSA_IMS_CALL_REPORT_STRU               stCallReport;
    IMSA_IMS_CALL_ERROR_STRU                stCallError;
    IMSA_IMS_CALL_CLIP_STRU                 stClip;
    IMSA_IMS_SRVCC_CALL_LIST_STRU           stSrvccCallList;
    IMSA_IMS_CALL_SUPSRV_INFO_STRU          stSupsrvInfo;
    IMSA_IMS_CALL_MODIFY_STRU               stCallModify;
    IMSA_IMS_CALL_ECONF_NOTIFY_IND_STRU     stEconfNotifyInd;
} IMSA_IMS_OUTPUT_CALL_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_SMS_EVENT_STRU
 �ṹ˵��  : IMS����IMSA�Ķ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                              bitOpMessage:1;
    VOS_UINT32                              bitOpErrorCode:1;
    VOS_UINT32                              bitOpSpare:30;

    IMSA_IMS_OUTPUT_SMS_REASON_ENUM_UINT32  enOutputSmsReason;
    VOS_UINT32                              ulOpId;
    VOS_UINT8                               ucMessageLen;
    VOS_UINT8                               aucMessage[IMSA_IMS_SMS_STRING_SZ + 1];
    IMSA_IMS_OUTPUT_ERROR_STRU              stErrorCode;
} IMSA_IMS_OUTPUT_SMS_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU
 �ṹ˵��  : IMS����IMSA�ķ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                                  bitOpErrorCode:1;
    VOS_UINT32                                  bitOpState:1;
    VOS_UINT32                                  bitOpAka:1;
    VOS_UINT32                                  bitOpIpsec:1;
    VOS_UINT32                                  bitOpSpare:28;

    IMSA_IMS_OUTPUT_SEVICE_REASON_ENUM_UINT32   enOutputServiceReason;
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulIsEmergency;

    IMSA_IMS_OUTPUT_ERROR_STRU                  stErrorCode;
    IMSA_IMS_SERVICE_STATE_ENUM_UINT32          enServeState;
    struct {
        VOS_UINT8     ucAkaRand[IMSA_IMS_AKA_RAND_STRING_SZ];
        VOS_UINT8     ucAkaAutn[IMSA_IMS_AKA_AUTN_STRING_SZ];
    } stAkaPara;
    struct {
        VOS_CHAR      acLocalIpAddress[IMSA_IMS_IP_ADDRESS_STRING_SZ + 1];
        VOS_CHAR      acRemoteIpAddress[IMSA_IMS_IP_ADDRESS_STRING_SZ + 1];
        VOS_UINT8     aucRsv[2];
        VOS_INT32     ulPortUc;
        VOS_INT32     ulPortUs;
        VOS_INT32     ulPortPc;
        VOS_INT32     ulPortPs;
        VOS_INT32     ulSpiUc;
        VOS_INT32     ulSpiUs;
        VOS_INT32     ulSpiPc;  /*SPI for outbound SA to proxy client port.*/
        VOS_INT32     ulSpiPs;  /*SPI for outbound SA to proxy server port.*/
    } stIpSecInfo;
} IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_PARA_EVENT_STRU
 �ṹ˵��  : IMS����IMSA�Ĳ��������¼�����ṹ
*****************************************************************************/
typedef struct{
    VOS_UINT32                                  bitOpResult:1;
    VOS_UINT32                                  bitOpImpu:1;
    VOS_UINT32                                  bitOpSpare:30;

    IMSA_IMS_OUTPUT_PARA_REASON_ENUM_UINT32     enOutputParaReason;
    VOS_UINT32                                  ulOpId;
    VOS_UINT32                                  ulResult;              /* �ɹ�����VOS_OK��ʧ�ܷ���VOS_ERR */
    VOS_UINT32                                  ulImpuLen;  /* ���IMPU��Ч����Ҫ��дIMPU�ĳ��ȣ����򳤶�Ϊ0 */
    VOS_CHAR                                    aucImpu[IMSA_IMS_EVENT_STRING_SZ+1];/* ֻ���ڲ�ѯIMPUʱ������Ҫ��д */
    VOS_UINT8                                   aucRsv[3];
}IMSA_IMS_OUTPUT_PARA_EVENT_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_PARA_EVENT_STRU
 �ṹ˵��  : IMS����IMSA�Ĳ��������¼�����ṹ
*****************************************************************************/
typedef struct{
    IMSA_IMS_OUTPUT_NV_INFO_REASON_ENUM_UINT32  enOutputNvInfoReason;
    VOS_UINT32                                  ulOpId;
}IMSA_IMS_OUTPUT_NV_INFO_EVENT_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU
 �ṹ˵��  : IMS����IMSA��ϵͳ�¼��ṹ
*****************************************************************************/
typedef struct{
    IMSA_IMS_OUTPUT_SYSTM_REASON_ENUM_UINT32  enOutputSysReason;
    VOS_UINT32                                ulOpId;
}IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_SMS_EVENT_STRU
 �ṹ˵��  : IMS����IMSA�Ķ����¼��ṹ
*****************************************************************************/
typedef struct {
    VOS_UINT32                              bitOpMessage:1;
    VOS_UINT32                              bitOpErrorCode:1;
    VOS_UINT32                              bitOpSpare:30;

    IMSA_IMS_OUTPUT_USSD_REASON_ENUM_UINT32 enOutputUssdReason;
    VOS_UINT32                              ulOpId;
    IMSA_IMS_USSD_ENCTYPE_ENUM_UINT8        encType; /* always CSM_USSD_ENCTYPE_UCS2. UCS-2 encoding on message field */
    /*1.IMSA_IMS_OUTPUT_USSD_ENCTYPE_ENUM_UINT8��TAF_SS_DATA_CODING_SCHEME��ֵ����Ӧ
    2.��ֵӦ����bitOpMessage��Чʱ�Ŵ���*/

    VOS_UINT8                               ucRsv;
    VOS_UINT16                              usMessageLen;
    VOS_UINT8                               aucMessage[IMSA_IMS_USSD_STRING_SZ + 1];
    VOS_UINT8                               aucRsv[3];
    IMSA_IMS_OUTPUT_ERROR_STRU              stErrorCode;/*�����Ҫ����*/
} IMSA_IMS_OUTPUT_USSD_EVENT_STRU;



/*****************************************************************************
 �ṹ��    : IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU
 �ṹ˵��  : IMS��IMSA���¼��ṹ
*****************************************************************************/
typedef struct {
    IMSA_IMS_EVENT_TYPE_ENUM_UINT32          enEventType; /* Type of message */
    union {
        IMSA_IMS_OUTPUT_SYSTEM_EVENT_STRU    stOutputSystemEvent;
        IMSA_IMS_OUTPUT_PARA_EVENT_STRU      stOutputParaEvent;
        IMSA_IMS_OUTPUT_SERVICE_EVENT_STRU   stOutputServiceEvent;
        IMSA_IMS_OUTPUT_SMS_EVENT_STRU       stOutputSmsEvent;
        IMSA_IMS_OUTPUT_CALL_EVENT_STRU      stOutputCallEvent;
        IMSA_IMS_OUTPUT_USSD_EVENT_STRU      stOutputUssdEvent;
        IMSA_IMS_OUTPUT_NV_INFO_EVENT_STRU   stOutoutNvInfoEvent;
    } evt;
} IMSA_IMS_OUTPUT_EVENT_STRU;

/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/

/*****************************************************************************
  8 Fuction Extern
*****************************************************************************/


/*****************************************************************************
  9 OTHERS
*****************************************************************************/


#if (VOS_OS_VER != VOS_WIN32)
#pragma pack()
#else
#pragma pack(pop)
#endif



#ifdef __cplusplus
    #if __cplusplus
            }
    #endif
#endif


#endif //__IMSA_IMS_EVENT_H__
