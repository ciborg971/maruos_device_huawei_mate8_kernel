

#ifndef __IMSAENTITY_H__
#define __IMSAENTITY_H__

/*****************************************************************************
  1 Include Headfile
*****************************************************************************/
#include "vos.h"
#include "product_config.h"
#include "ImsaIntraInterface.h"
#include "ImsaMsccInterface.h"
#include "TafApsApi.h"
#include "SpmImsaInterface.h"
#include "ImsaInterface.h"
#include "ImsaImsEvent.h"
#include "AtImsaInterface.h"
#include "ImsaNvInterface.h"
#include "CallImsaInterface.h"
#include "TafNvInterface.h"

#include "ImsaMtcInterface.h"
#if (FEATURE_ON == FEATURE_PTM)
#include "ImsaErrlogInterface.h"
#include "omringbuffer.h"
#endif

/* zhaochen 00308719 begin for FIFI mailbox full reset 2015-11-09 */
#include "ImsCodecInterface.h"
/* zhaochen 00308719 end for FIFI mailbox full reset 2015-11-09 */
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
#define IMSA_CALL_MAX_NUM               (7)
#define IMSA_CALL_NUMBER_MAX_NUM        (MN_CALL_MAX_BCD_NUM_LEN * 2)
#define IMSA_CALLED_NUMBER_MAX_NUM      (MN_CALL_MAX_CALLED_ASCII_NUM_LEN)
#define IMSA_REG_ADDR_PAIR_MAX_NUM      (4)     /*2����ͬ����UE IP��ַ��Ӧ2��PCSCF��ַ*/

#define IMSA_PCSCF_MAX_NUM              (6)

#define IMSA_IPV6_ADDR_STRING_LEN       (46)
#define IMSA_IPV4_ADDR_STRING_LEN       (15)

/* "a1.a2.a3.a4 " */
#define IMSA_IPV4_ADDR_LEN              (4)

/* "a1...a16" */
#define IMSA_IPV6_ADDR_LEN              (16)

#define IMSA_MAX_APN_LEN                (99)

#define IMSA_MAX_PF_NUM                 (16)

#define IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM (2)
#define IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM  (2)
#define IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM     (2)

#define IMSA_MAX_UEID_BUF_SIZE                  (10)
#define IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN       (128)
#define IMSA_MAX_IMPI_LEN                       (128)
#define IMSA_MAX_TIMPU_LEN                      (128)
#define IMSA_CONN_ILLEGAL_OPID                  (0)
#define IMSA_CONN_NORMAL_CONN_MIN_OPID_VALUE    (1)
#define IMSA_CONN_NORMAL_CONN_MAX_OPID_VALUE    (200)
#define IMSA_CONN_EMC_CONN_MIN_OPID_VALUE       (201)
#define IMSA_CONN_EMC_CONN_MAX_OPID_VALUE       (255)
#define IMSA_MAX_SUBSCRIPTION_NUM               (6)
#define IMSA_MAX_PASSWORD_LEN                   (32)

#define IMSA_SMS_TRUE                           1
#define IMSA_SMS_FALSE                          0

/* retrans define */
#define IMSA_SMR_RETRANS_PERMIT                 0
#define IMSA_SMR_RETRANS_NO_PERMIT              1
#define IMSA_SMR_RETRANS_PROCESS                2
#define IMSA_SMR_RETRANS_ABORT                  3

/* RP ERROR CAUSE */
#define  IMSA_SMR_ERR_CAUSE_MTI_MO_RP_ERROR                     4
#define  IMSA_SMR_ERR_CAUSE_NET_OUT_OF_ORDER                    38
#define  IMSA_SMR_ERR_CAUSE_TEMP_FAILURE                        41
#define  IMSA_SMR_ERR_CAUSE_CONGESTION                          42
#define  IMSA_SMR_ERR_CAUSE_RES_UNAVAIL                         47
#define  IMSA_SMR_ERR_CAUSE_VALUE_INVALID_MR                    81
#define  IMSA_SMR_ERR_CAUSE_MSG_INVALID_INFO_ERROR              96
#define  IMSA_SMR_ERR_CAUSE_VALUE_MSG_TYPE_NON_EXIST            97
#define  IMSA_SMR_ERR_CAUSE_VALUE_MSG_NOT_COMPA_STATE           98
#define  IMSA_SMR_ERR_CAUSE_MSG_PROTOCOL_ERROR                  111
#define  IMSA_SMR_MSG_CHK_SUCCESS                               255
#define  IMSA_SMR_MSG_TOO_SHORT_ERROR                           254
#define  IMSA_SMR_ERR_UPPER_ABORT                               253

#define  IMSA_CALL_DTMF_BUF_MAX_NUM            (16)        /* ��໺��DTMF��Ϣ���� */

#define  IMSA_CONN_MAX_NIC_PDP_NUM              (3)

#define IMSA_VOICE_QCI                          (1)
#define IMSA_VIDEO_QCI                          (2)

/*****************************************************************************
  3 Massage Declare
*****************************************************************************/



/*****************************************************************************
  4 Enum
*****************************************************************************/
/* wangchen : v7r2 diff from v9r1 because struct is diff 2014-06-18 */
typedef MN_CALL_DIR_ENUM_U8 MN_CALL_DIR_ENUM_UINT8;
typedef MN_CALL_MPTY_STATE_ENUM_U8 MN_CALL_MPTY_STATE_ENUM_UINT8;
typedef MN_CALL_MODE_ENUM_U8 MN_CALL_MODE_ENUM_UINT8;
typedef MN_CALL_EVENT_ENUM_U32 MN_CALL_EVENT_ENUM_UINT32;
typedef MN_CALL_TYPE_ENUM_U8 MN_CALL_TYPE_ENUM_UINT8;
typedef MN_CALL_CLIR_CFG_ENUM_U8 MN_CALL_CLIR_CFG_ENUM_UINT8;


/*****************************************************************************
    ö����    : IMSA_CALL_STATUS_ENUM
    ö��˵��  : ����״̬
*****************************************************************************/
enum    IMSA_CALL_STATUS_ENUM
{
    IMSA_CALL_STATUS_IDLE,
    IMSA_CALL_STATUS_DIALING,
    IMSA_CALL_STATUS_TRYING,
    IMSA_CALL_STATUS_ALERTING,
    IMSA_CALL_STATUS_ACTIVE,
    IMSA_CALL_STATUS_INCOMING,
    IMSA_CALL_STATUS_HELD,
    IMSA_CALL_STATUS_WAITING,
    IMSA_CALL_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_CALL_STATUS_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8
    ö��˵��  : ��ԴԤ��״̬
*****************************************************************************/
enum    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM
{
    IMSA_CALL_CALL_REASON_RESOURCE_READY,
    IMSA_CALL_CALL_REASON_RESOURCE_ONLY_VOICE,
    IMSA_CALL_CALL_REASON_RESOURCE_FAILED,
    IMSA_CALL_CALL_REASON_RESOURCE_RESULT_BUTT
};
typedef VOS_UINT8 IMSA_CALL_CALL_REASON_RESOURCE_RESULT_ENUM_UINT8;


/*****************************************************************************
    ö����    : IMSA_CALL_MODE_ENUM
    ö��˵��  : ���з���
*****************************************************************************/
enum    IMSA_CALL_MODE_ENUM
{
    IMSA_CALL_MODE_VOICE,
    IMSA_CALL_MODE_DATA,
    IMSA_CALL_MODE_BUTT
};
typedef VOS_UINT8 IMSA_CALL_MODE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_CALL_NUM_TYPE_ENUM
    ö��˵��  : ���к�������
*****************************************************************************/
// TODO: ����������Ҳ������SMS/USSD��������ȥ��CALL���ǰ׺
enum    IMSA_CALL_NUM_TYPE_ENUM
{
    IMSA_CALL_NUM_NATIONAL,
    IMSA_CALL_NUM_INTERNATIONAL,
    IMSA_CALL_NUM_BUTT
};
typedef VOS_UINT8 IMSA_CALL_NUM_TYPE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_REG_STATUS_ENUM
    ö��˵��  : IMSע��״̬
*****************************************************************************/
enum    IMSA_REG_STAUTS_ENUM
{
    IMSA_REG_STATUS_NOT_REGISTER,       /**< δע��״̬ */
    IMSA_REG_STATUS_REGISTERING,        /**< ����ע��״̬ */
    IMSA_REG_STATUS_REGISTERED,         /**< ��ע��״̬ */
    IMSA_REG_STATUS_DEREGING,           /**< ����ȥע״̬ */
    IMSA_REG_STATUS_WAIT_RETRY,         /**< ���ڵȴ����³���ע�� */
    IMSA_REG_STATUS_PENDING,
    IMSA_REG_STATUS_ROLLING_BACK,
    IMSA_REG_STATUS_WAIT_PERIOD_TRY,    /**< ���ڵȴ����ڳ���IMSע�� */
    IMSA_REG_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_REG_STAUTS_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_CAMPED_RAT_TYPE_ENUM
    ö��˵��  : UEפ������������
*****************************************************************************/
enum    IMSA_CAMPED_RAT_TYPE_ENUM
{
    IMSA_CAMPED_RAT_TYPE_NULL                   = 0,
    IMSA_CAMPED_RAT_TYPE_GSM,
    IMSA_CAMPED_RAT_TYPE_UTRAN,
    IMSA_CAMPED_RAT_TYPE_EUTRAN,
    IMSA_CAMPED_RAT_TYPE_BUTT
};
typedef VOS_UINT8 IMSA_CAMPED_RAT_TYPE_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_PS_SERVICE_STATUS_ENUM
    ö��˵��  : ��ǰפ������PS�����״̬
*****************************************************************************/
enum    IMSA_PS_SERVICE_STATUS_ENUM
{
    IMSA_PS_SERVICE_STATUS_NORMAL_SERVICE       = 0,
    IMSA_PS_SERVICE_STATUS_LIMITED_SERVICE,
    IMSA_PS_SERVICE_STATUS_NO_SERVICE,
    IMSA_PS_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_PS_SERVICE_STATUS_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_IMS_VOPS_STATUS_ENUM
    ö��˵��  : ��ǰ�����Ƿ�֧��IMS voice over PS session
*****************************************************************************/
enum    IMSA_IMS_VOPS_STATUS_ENUM
{
    IMSA_IMS_VOPS_STATUS_NOT_SUPPORT            = 0,
    IMSA_IMS_VOPS_STATUS_SUPPORT,
    IMSA_IMS_VOPS_STATUS_BUTT
};
typedef VOS_UINT8 IMSA_IMS_VOPS_STATUS_ENUM_UINT8;

/*****************************************************************************
    ö����    : IMSA_IMS_VOPS_STATUS_ENUM
    ö��˵��  : ��ǰ�����Ƿ�֧��EMS
*****************************************************************************/
enum    IMSA_EMS_STAUTS_ENUM
{
    IMSA_EMS_STAUTS_NOT_SUPPORT                 = 0,
    IMSA_EMS_STAUTS_SUPPORT,
    IMSA_EMS_STAUTS_BUTT
};
typedef VOS_UINT8 IMSA_EMS_STAUTS_ENUM_UINT8;



enum IMSA_PDP_TYPE_ENUM
{
    IMSA_PDP_TYPE_DEFAULT               = 0,                /**< ȱʡ���� */
    IMSA_PDP_TYPE_DEDICATED             = 1,                /**< ר�г��� */
    IMSA_PDP_TYPE_EMERGENCY             = 2,                /**< �������� */

    IMSA_PDP_TYPE_BUTT
};
typedef VOS_UINT8  IMSA_PDP_TYPE_ENUM_UINT8;


enum IMSA_PDP_STATE_ENUM
{
    IMSA_PDP_STATE_INACTIVE  = 0,             /**< ������ȥ����̬ */
    IMSA_PDP_STATE_ACTIVE,                    /**< �����ļ���״̬ */

    IMSA_PDP_STATE_BUTT
};
typedef VOS_UINT8  IMSA_PDP_STATE_ENUM_UINT8;

enum IMSA_CONN_STATUS_ENUM
{
    IMSA_CONN_STATUS_IDLE               = 0,            /**< ���������� */
    IMSA_CONN_STATUS_CONNING            = 1,            /**< ���ڽ������� */
    IMSA_CONN_STATUS_RELEASING          = 2,            /**< �����ͷ����� */
    IMSA_CONN_STATUS_CONN               = 3,            /**< �������� */

    IMSA_CONN_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_CONN_STATUS_ENUM_UINT8;


enum IMSA_STATUS_ENUM
{
    IMSA_STATUS_NULL                    = 0,            /**< δ���� */
    IMSA_STATUS_STARTING                = 1,            /**< ������ */
    IMSA_STATUS_STOPING                 = 2,            /**< �ػ��� */
    IMSA_STATUS_STARTED                 = 3,            /**< �ѿ��� */

    IMSA_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_STATUS_ENUM_UINT8;

enum IMSA_ISIM_STATUS_ENUM
{
    IMSA_ISIM_STATUS_ABSENT             = 0,            /**< �޿� */
    IMSA_ISIM_STATUS_UNAVAILABLE        = 1,            /**< �������ã�������ȡ���뿨����ʧ�ܡ�PS����Ч�� */
    IMSA_ISIM_STATUS_AVAILABLE          = 2,            /**< ����Ч���� */

    IMSA_ISIM_STATUS_BUTT
};
typedef VOS_UINT8  IMSA_ISIM_STATUS_ENUM_UINT8;

/*****************************************************************************
 ö����    : IMSA_VOICE_DOMAIN_ENUM
 �ṹ˵��  : UE��Voice Domain����
*****************************************************************************/
enum IMSA_VOICE_DOMAIN_ENUM
{
   IMSA_VOICE_DOMAIN_CS_ONLY         = 0,    /**< CS voice only */
   IMSA_VOICE_DOMAIN_IMS_PS_ONLY     = 1,    /**< IMS PS voice only */
   IMSA_VOICE_DOMAIN_CS_PREFERRED    = 2,    /**< CS voice preferred, IMS PS Voice as secondary */
   IMSA_VOICE_DOMAIN_IMS_PS_PREFERRED= 3,    /**< IMS PS voice preferred, CS Voice as secondary */

   IMSA_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32   IMSA_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 ö����    : IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM
 �ṹ˵��  : ��ȡIMS��ͨ���������״��
*****************************************************************************/
enum IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM
{
   IMSA_NRM_SRV_CON_SAT_STATUE_SUCC                     = 0,    /**< �����ȡ��ͨ��������� */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_RAT_NOT_SUPPORT     = 1,    /**< �������ȡ��ͨ�����������ԭ��Ϊ���뼼����֧�� */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_ROAM_NOT_SUPPORT    = 2,    /**< �������ȡ��ͨ�����������ԭ��Ϊ��֧������ע�� */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_USIM_NOT_SUPPORT    = 3,    /**< �������ȡ��ͨ�����������ԭ��ΪUSIM����֧�� */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_VOICE_NOT_SUPPORT   = 4,    /**< �������ȡ��ͨ�����������ԭ��ΪIMS������֧�� */
   IMSA_NRM_SRV_CON_SAT_STATUE_FAIL_OTHERS              = 5,    /**< �������ȡ��ͨ�����������ԭ��Ϊ���� */

   IMSA_NRM_SRV_CON_SAT_STATUE_BUTT
};
typedef VOS_UINT32   IMSA_NRM_SRV_CON_SAT_STATUE_ENMUM_UINT32;


/*****************************************************************************
 ö����    : IMSA_SRV_STATUS_ENUM
 �ṹ˵��  : service״̬ö��
*****************************************************************************/
enum IMSA_SRV_STATUS_ENUM
{
   IMSA_SRV_STATUS_IDLE_DEREG           = 0x00,    /**< IDLE&DEREG */
   IMSA_SRV_STATUS_CONNING_DEREG        = 0x10,    /**< CONNING&DEREG */
   IMSA_SRV_STATUS_CONNING_REG          = 0x13,    /**< CONNING&REG */
   IMSA_SRV_STATUS_RELEASING_DEREG      = 0x20,    /**< RELEASING&DEREG */
   IMSA_SRV_STATUS_CONN_DEREG           = 0x30,    /**< CONN&DEREG */
   IMSA_SRV_STATUS_CONN_REGING          = 0x31,    /**< CONN&REGING */
   IMSA_SRV_STATUS_CONN_DEREGING        = 0x32,    /**< CONN&DEREGING */
   IMSA_SRV_STATUS_CONN_REG             = 0x33,    /**< CONN&REG */

   IMSA_SRV_STATUS_BUTT                 = 0xff
};
typedef VOS_UINT8   IMSA_SRV_STATUS_ENUM_UINT8;

enum IMSA_SRV_DEREG_CAUSE_ENUM
{
    IMSA_SRV_DEREG_CAUSE_MSCC_DEREG_REQ      = 0x0000,

    IMSA_SRV_DEREG_CAUSE_BUTT
};
typedef VOS_UINT32  IMSA_SRV_DEREG_CAUSE_ENUM_UINT32;

enum IMSA_SMS_SMR_STATE_ENUM
{
    IMSA_SMS_SMR_STATE_IDLE,
    IMSA_SMS_SMR_STATE_WAIT_FOR_RP_ACK,
    IMSA_SMS_SMR_STATE_WAIT_TO_SND_RP_ACK,
    IMSA_SMS_SMR_STATE_WAIT_FOR_RETRANS_TIMER,
    IMSA_SMS_SMR_STATE_BUTT
};
typedef VOS_UINT8 IMSA_SMS_SMR_STATE_ENUM_UINT8;

enum IMSA_CALL_DTMF_STATE_ENUM
{
    IMSA_CALL_DTMF_IDLE                  = 0,                                    /* ��ǰDTMF���� */
    IMSA_CALL_DTMF_WAIT_START_CNF,                                               /* ������START�����ȴ��ظ� */
    IMSA_CALL_DTMF_WAIT_STOP_CNF,                                                /* ������STOP�����ȴ��ظ� */
    IMSA_CALL_DTMF_WAIT_AUTO_STOP_CNF,                                           /* ��ʱ����ʱ�Զ�����STOP�����ȴ��ظ� */
    IMSA_CALL_DTMF_WAIT_TIME_OUT,                                                /* ����DTMF��ʱ����ȴ���ʱ */

    IMSA_CALL_DTMF_STATE_BUTT
};
typedef VOS_UINT8 IMSA_CALL_DTMF_STATE_ENUM_UINT8;

enum
{
    IMSA_USSD_IDLE_STATE               = 0, /* IDLE̬ */
    IMSA_USSD_MO_CONN_STATE            = 1, /* UE�������������״̬ */
    IMSA_USSD_MT_CONN_STATE            = 2, /* �����������������״̬ */

    IMSA_USSD_BUTT_STATE                    /* ��Чֵ */
};
typedef VOS_UINT8   IMSA_USSD_STATE_ENUM_UINT8;


typedef struct
{

    HTIMER                              phTimer;            /* Timer��� */
    VOS_UINT16                          usName;             /* �� IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT16                          usPara;             /* �� IMSA_TIMER_ID_ENUM_UINT16*/
    VOS_UINT8                           ucMode;             /* timer work mode
                                                               VOS_RELTIMER_LOOP   -- start periodically
                                                               VOS_RELTIMER_NOLOOP -- start once time */
    VOS_UINT8                           ucResv[3];
    VOS_UINT32                          ulTimerLen;         /* Timerʱ��(UNIT: ms) */
}IMSA_TIMER_STRU;

/*****************************************************************************
    ö����    : IMSA_TIMER_RUN_STA_ENUM
    ö��˵��  : ��ʱ����״̬:��������,ֹͣ
*****************************************************************************/
enum    IMSA_TIMER_RUN_STA_ENUM
{
    IMSA_TIMER_RUNNING                = 0x00,
    IMSA_TIMER_STOPED,
    IMSA_TIMER_INVALID,

    IMSA_TIMER_BUTT
};
typedef VOS_UINT32   IMSA_TIMER_RUN_STA_ENUM_UINT32;



typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                              ulMsgId;
    IMSA_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus;   /* ��ʱ��״̬*/

    VOS_UINT16                               usTimerId;       /* ��ʱ��ID*/
    VOS_UINT16                               usRsv;
    VOS_UINT32                               ulTimerRemainLen;/* ��ʱ����ʱ�� */
}IMSA_TIMER_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_REG_ADDR_PAIR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ַ�Խṹ����
*****************************************************************************/
typedef struct
{
    VOS_UINT8                   ucCid;                  /**< �洢�ͷų��ص�CID */
    IMSA_IP_TYPE_ENUM_UINT8     enIpType;               /**< �洢�ͷų��ص�PDN���� */
    VOS_UINT8                   acRsv1[2];

    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];        /**< UE��ַ */
    VOS_UINT8                   ucRsv2;

    VOS_CHAR                    acPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];     /**< P-CSCF��ַ */
    VOS_UINT8                   ucRsv3;
}IMSA_REG_PARA_INFO_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_REG_ADDR_PAIR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ַ�Խṹ����
*****************************************************************************/
typedef struct tag_IMSA_REG_ADDR_PAIR_STRU
{
    struct tag_IMSA_REG_ADDR_PAIR_STRU *pstNext;

    VOS_UINT8                   ucPriority;                                     /**< �ĵ�ַ�Ե����ȼ�������ʱ���� */

    VOS_UINT8                   ucHasTryed;                                     /**< �õ�ַ���Ƿ񱻳��Թ� */
    IMSA_IP_TYPE_ENUM_UINT8     enIpType;                                       /**< ��ַ���ͣ� IPv4 ���� IPv6 */
    VOS_UINT8                   ucRsv1;

    VOS_CHAR                    acUeAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];        /**< UE��ַ */
    VOS_UINT8                   ucRsv2;

    VOS_CHAR                    acPcscfAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];     /**< P-CSCF��ַ */
    VOS_UINT8                   ucRsv3;
}IMSA_REG_ADDR_PAIR_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_REG_PCSCF_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : P-CSCF��ַ�ṹ����
*****************************************************************************/
typedef struct
{
    IMSA_IP_TYPE_ENUM_UINT8     enIpType;                                       /**< P-CSCF��ַ���ͣ�IPv4����IPv6 */
    IMSA_PCSCF_SRC_TYPE_UINT8   enSrcType;                                      /**< P-CSCF��ַ��Դ */
    VOS_UINT8                   aucRsv[2];

    VOS_CHAR                    acIpAddr[IMSA_IPV6_ADDR_STRING_LEN + 1];        /**< P-CSCF��ַ���� */
    VOS_UINT8                   ucRsv;
}IMSA_REG_PCSCF_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_REG_ADDR_PAIR_MGR_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ��ַ�Թ���ģ��ṹ����
*****************************************************************************/
typedef struct
{
    VOS_CHAR                    acUeAddrIpv4[IMSA_IPV4_ADDR_STRING_LEN + 1];    /**< UE��IPv4��ַ */

    VOS_CHAR                    acUeAddrIpv6[IMSA_IPV6_ADDR_STRING_LEN + 1];    /**< UE��IPv6��ַ */
    VOS_UINT8                   ucRsv;

    IMSA_REG_PCSCF_STRU         astPcscfs[IMSA_PCSCF_MAX_NUM];                   /**< UE��ȡ��������P-CSCF��ַ */

    IMSA_REG_ADDR_PAIR_STRU    *pstCurrent;                                     /**< ��ǰ��ַ�� */

    IMSA_REG_ADDR_PAIR_STRU    *pstIpv6List;                                    /**< IPv6��ַ���б� */
    IMSA_REG_ADDR_PAIR_STRU    *pstIpv4List;                                    /**< IPv4��ַ���б� */
}IMSA_REG_ADDR_PAIR_MGR_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_SAVED_IMS_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���л�ע�����ģ�鱣��ĵ�ǰ����ִ�е�IMS����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpImsMsg:1;      /**< �Ƿ��б����IMS��Ϣ */
    VOS_UINT32                          bitOpRsv   :31;

    VOS_UINT32                          ulCsmReason;        /**< ���浱ǰ����ִ�е�D2 IMSָ�� */
    VOS_UINT32                          ulCsmId;            /**< ���浱ǰ����ִ�е�D2 IMSָ��opid*/
}IMSA_SAVED_IMS_MSG_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_REG_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ע��ʵ��ṹ����
*****************************************************************************/
typedef struct
{
    IMSA_REG_STAUTS_ENUM_UINT8          enStatus;           /**< ע��״̬ */
    VOS_UINT8                           ucRetryCnt;         /**< ʧ�����Դ��� */
    IMSA_REG_TYPE_ENUM_UINT8            enRegType;          /**< ע������ */

    IMSA_REG_STAUTS_ENUM_UINT8          enExceptedStatus;

    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enPendingRegParam;

    VOS_UINT32                          ulPendingDeregParam;

    VOS_UINT32                          ulRetryTimes;       /**< ���Դ��� */

    IMSA_TIMER_STRU                     stRetryTimer;       /**< ʧ�����Զ�ʱ�� */

    IMSA_TIMER_STRU                     stProtectTimer;     /**< ������ʱ�� */

    IMSA_REG_ADDR_PAIR_MGR_STRU         stPairMgrCtx;       /**< ע���ַ����Ϣ */
    VOS_UINT8                           ucImsaUsimNormOpid;
    VOS_UINT8                           ucImsaUsimEmcOpid;
    VOS_UINT8                           aucRsv[1];
    VOS_UINT8                           ucTryRegTimes;       /**< ���ڳ���IMSע����� */
    IMSA_TIMER_STRU                     stPeriodTryRegTimer; /**< �������ڳ���IMSע�ᶨʱ�� */
}IMSA_REG_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_REG_MANAGER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ע�������Ϣ������
*****************************************************************************/
typedef struct
{
    IMSA_REG_RETRY_POLICY_ENUM_UINT32   enRetryPolicy;      /**< ע��ʧ�ܺ�����Բ��� */

    VOS_UINT32                          ulMaxTime;          /**< RFC5626��������ʱ��ʱ��maxtime����λ�� */
    VOS_UINT32                          ulBaseTime;         /**< RFC5626��������ʱ��ʱ��basetime����λ�� */
    VOS_UINT32                          ulReregPeriod;      /**< SIPˢ��ע��ʱ�䣬��λ�� */
    VOS_UINT32                          ulRetryPeriod;      /**< ע��ʧ�ܺ�����������ʱ��������λ�� */

    VOS_UINT32                          ulSaveRetryTimes;   /**< ����NV���õ�IMSע��ʧ�����³��Դ��� */

    IMSA_REG_ENTITY_STRU                stNormalRegEntity;  /**< ��ͨע��ʵ�� */
    IMSA_REG_ENTITY_STRU                stEmcRegEntity;     /**< ����ע��ʵ�� */

    IMSA_SAVED_IMS_MSG_STRU             stImsMsg;           /**< IMS����ִ����Ϣ */
} IMSA_REG_MANAGER_STRU;


typedef struct
{
    VOS_UINT16                          usImsMinPort;           /* IMS�˿ںŷ�Χ���� */
    VOS_UINT16                          usImsMaxPort;           /* IMS�˿ںŷ�Χ���� */

}IMSA_IMS_PORT_CONFIG_STRU;


typedef IMSA_NV_IMS_REDIAL_CFG_STRU IMSA_IMS_REDIAL_CFG_STRU;

typedef IMSA_NV_CMCC_CUSTOM_REQ_STRU IMSA_CMCC_CUSTOM_REQ_STRU;

typedef struct
{
    VOS_UINT8                           ucGsmImsSupportFlag;    /**< GSM IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUtranImsSupportFlag; /**< UNTRAN IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucGsmEmsSupportFlag;    /**< GSM EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */

    VOS_UINT8                           ucRoamingImsNotSupportFlag; /**< ����������IMSʹ���VOS_TRUE:֧�� VOS_FALSE:��֧�� */
    VOS_UINT8                           aucReserved[3];

    VOS_UINT8                           ucUtranEmsSupportFlag; /**< UNTRAN EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucVoiceCallOnImsSupportFlag;    /**< IMS����ʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucVideoCallOnImsSupportFlag;        /**< IMS��Ƶʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */

    VOS_UINT8                           ucSmsOnImsSupportFlag;          /**< IMS����ʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucSrvccOnImsSupportFlag;            /**< IMS Srvccʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucSrvccMidCallOnImsSupportFlag;     /**< IMS SrvccMidCallʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucSrvccAlertingOnImsSupportFlag;    /**< IMS SrvccAlertingʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */

    VOS_UINT8                           ucSrvccPreAlertingOnImsSupportFlag; /**< IMS SrvccPreAlertingʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucSrvccTiFlag;                      /**< IMS SrvccPreAlerting,VOS_TRUE :0 R10�汾,VOS_FALSE R11֮��汾 */
    VOS_UINT8                           ucNoCardEmcCallSupportFlag;/**< �޿�������ʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUeRelMediaPdpFLag;    /**< UE�����ͷ�ý����ر�ʶ */

    VOS_UINT8                           ucImsLocDeregSigPdpRelFlag;/**< IMS��ͨ������ͷź󱾵�IMSȥע���ʶ */
    VOS_UINT8                           ucAuthType;  /**< IMS ucAuthType,0 :AKA,1:DIGIST */
    VOS_CHAR                            aucPassWord[IMSA_PASSWORD_LEN]; /**< DIGIST��Ȩʱ��ʹ�õ����� */
    VOS_UINT8                           ucUserInfoFlag;/**< 0:��USIM��IMPI��IMPU,DOMAIN   1:��NV��ȡIMPI��IMPU,DOMAIN */

    IMSA_VOICE_DOMAIN_ENUM_UINT32       enVoiceDomain;          /**< voice domain preferrece */
    IMSA_IMS_PORT_CONFIG_STRU           stImsPortConfig;        /**< IMS �˿�������Ϣ */

    IMSA_IMS_REDIAL_CFG_STRU            stImsRedialCfg;         /**< IMS�����ز����� */
    IMSA_CMCC_CUSTOM_REQ_STRU           stCMCCCustomReq;        /**< �й��ƶ��������� */
}IMSA_CONFIG_PARA_STRU;

typedef struct
{
    IMSA_CAMPED_RAT_TYPE_ENUM_UINT8     enImsaCampedRatType;        /**< ��ǰפ������,NULL,2G,3G,LTE */
    IMSA_IMS_VOPS_STATUS_ENUM_UINT8     enImsaImsVoPsStatus;        /**< ��ǰ�����Ƿ�֧��IMS voice over PS session */
    IMSA_EMS_STAUTS_ENUM_UINT8          enImsaEmsStatus;            /**< ��ǰ�����Ƿ�֧��EMS */
    IMSA_PS_SERVICE_STATUS_ENUM_UINT8   enImsaPsServiceStatus;      /**< ��ǰ�����PS����״̬:�޷���,���޷���,�������� */
    VOS_UINT8                           ucImsaRoamingFlg;           /**< VOS_TRUE :���Σ�VOS_FALSE :������ */
    MSCC_IMSA_ACCESS_TYPE_ENUM_UINT8    enAccessType;
    VOS_UINT8                           aucReserved[2];
    VOS_UINT16                          usLac;
    VOS_UINT16                          usTac;
    MSCC_IMSA_PLMN_ID_STRU              stPlmnId;
    VOS_UINT32                          ulCellId;
}IMSA_NETWORK_INFO_STRU;

/*****************************************************************************
 �ṹ����: IMSA_IMPI_STRU
 �ṹ˵��: Private User Identity�ṹ���μ�23.003 13.3
           "<IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acImpi[IMSA_MAX_IMPI_LEN + 1]; /**< Ĭ��49�ֽ� */
    VOS_UINT8                           aucReserved[3];
}IMSA_IMPI_STRU;

/*****************************************************************************
 �ṹ����: IMSA_TIMPU_STRU
 �ṹ˵��: Tempory Public User Identity�ṹ���μ�23.003 13.4B
           "sip:<IMSI>@ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acTImpu[IMSA_MAX_TIMPU_LEN + 1]; /**< Ĭ��53�ֽ� */
    VOS_UINT8                           aucReserved[3];
}IMSA_TIMPU_STRU;


/*==============================================================================
�ṹ����    : IMSA_UEID_STRU
ʹ��˵��    :
              1)IMEI, IMEISV�Ĵ�Ÿ�ʽ���� 31.102 4.2.2ִ��
              2)IMPI,IMPU����23.003 13.3��12.4B
==============================================================================*/
typedef struct
{
    VOS_UINT32                          bitOpImei     :1;
    VOS_UINT32                          bitOpImpi     :1;
    VOS_UINT32                          bitOpTImpu    :1;
    VOS_UINT32                          bitOpRsv      :29;

    VOS_CHAR                            acImei[IMSA_IMS_IMEI_LEN + 1];          /**< IMEI */
    IMSA_IMPI_STRU                      stImpi;                                 /**< IMPI */
    IMSA_TIMPU_STRU                     stTImpu;
}IMSA_UEID_STRU;


/*****************************************************************************
 �ṹ����: IMSA_HOME_NET_DOMAIN_NAME_STRU
 �ṹ˵��: Home network domain name�ṹ���μ�23.003 13.2
           "ims.mnc<MNC>.mcc<MCC>.3gppnetwork.org"
*****************************************************************************/
typedef struct
{
    VOS_CHAR                            acHomeNetDomainName[IMSA_MAX_HOME_NET_DOMAIN_NAME_LEN + 1]; /**< Ĭ��33�ֽ� */
    VOS_UINT8                           aucReserved[3];
}IMSA_HOME_NET_DOMAIN_NAME_STRU;

typedef struct
{
    VOS_UINT32                          bitOpHomeNetDomainName  :1;
    VOS_UINT32                          bitOpRsv                :31;

    IMSA_UEID_STRU                      stImsaUeId;                 /**< ue id */
    IMSA_HOME_NET_DOMAIN_NAME_STRU      stHomeNetDomainName;        /**< Home network domain name */
}IMSA_COMMON_INFO_STRU;
/*****************************************************************************
 �ṹ��    : IMSA_CALL_SPM_MSG_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ģ�鱣��ĵ�ǰ���ڴ����SPM���͹����ĺ�����ص�����
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpSpmMsg:1;      /**< �Ƿ��б����SPM���� */
    VOS_UINT32                          bitOpRsv:31;

    VOS_UINT32                          ulSpmMsgId;         /**< SPM���� */

    VOS_UINT16                          usClientId;         /**< Client Id */
    VOS_UINT8                           aucRsv[2];
    VOS_UINT32                          ulOpId;             /**< SPM�����opid */
    VOS_UINT32                          ulCallId;           /**< ����Id */

    union
    {
        MN_CALL_ORIG_PARAM_STRU         stOrigParam;        /**< ���н�������Ĳ��� */
        MN_CALL_SUPS_PARAM_STRU         stSupsParam;        /**< ��ֵ��������Ĳ��� */
        TAF_CALL_ECONF_DIAL_REQ_STRU     stEconfDialParam;   /**< ��ǿ�Ͷ෽ͨ���Ĳ��� */
        TAF_CALL_ECONF_CALL_LIST_STRU    stEconfAddParam;    /**< ��ǿ�෽ͨ������û��Ĳ���*/
    } stParam;                                              /**< SPM�����Ӧ�Ĳ��� */
}IMSA_CALL_SPM_MSG_STRU;
/*****************************************************************************
 �ṹ��    : IMSA_CALL_NUMBER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʵ�嶨��
*****************************************************************************/
typedef struct
{
    IMSA_CALL_NUM_TYPE_ENUM_UINT8       enNumType;                             /**< ���к������� */
    VOS_UINT8                           aucRsv[2];
    VOS_CHAR                            aucNumber[IMSA_CALL_NUMBER_MAX_NUM + 1];   /**< ʵ�ʺ��� *//* FOR OVERFLOW 0831 */
}IMSA_CALL_NUMBER_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_CALLED_NUMBER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʵ�嶨��
*****************************************************************************/
typedef struct
{
    IMSA_CALL_NUM_TYPE_ENUM_UINT8       enNumType;                             /**< ���к������� */
    VOS_UINT8                           aucRsv[2];
    VOS_CHAR                            aucNumber[IMSA_CALLED_NUMBER_MAX_NUM+1]; /**< ʵ�ʺ��� *//* FOR OVERFLOW 0831 */
}IMSA_CALLED_NUMBER_STRU;
typedef struct {
    VOS_UINT32                              bitOpIsUsed      :1;
    VOS_UINT32                              bitOpErrorInfo   :1;    /**< �Ƿ����������Ϣ */
    VOS_UINT32                              bitOpRsv         :30;

    IMSA_IMS_ECONF_CALLER_STATE_ENUM_UINT8  enCallState;
    VOS_UINT8                               ucTi;
    VOS_CHAR                                acAlpha[IMSA_IMS_ALPHA_STRING_SZ + 1];
    VOS_UINT8                               aucRsv;
    IMSA_CALL_NUMBER_STRU                   stCallNumber;   /**< ���к��� */
    IMSA_CALLED_NUMBER_STRU                 stCalledNumber; /**< ���к��� */
    IMSA_CALL_NUMBER_STRU                   stConnectNumber;   /**< ���Ӻ��� */
    IMSA_CALL_NUMBER_STRU                   stRedirectNumber;   /**< ���Ӻ��� */
    IMSA_IMS_OUTPUT_ERROR_STRU              stErrorCode;
}IMSA_CALL_ECONF_SUMMARY_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_CALL_ENTITY_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ����ʵ�嶨��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpIsUsed             :1;    /**< ����ʵ���Ƿ�ʹ�� */
    VOS_UINT32                          bitOpRetryCsCall        :1;    /**< CS���Ƿ�����ٳ��� */
    VOS_UINT32                          bitOpLocalAlerting      :1;    /**< �Ƿ�ʹ�ñ������� */
    VOS_UINT32                          bitOpNeedSendResResult  :1;    /**< �Ƿ���Ҫ��IMS������ԴԤ�����, 1 Ϊ��Ҫ�� 0 ����Ҫ */
    VOS_UINT32                          bitOpErrorInfo          :1;    /**< �Ƿ����������Ϣ */
    VOS_UINT32                          bitOpTransToCs          :1;    /**< ��·�绰�Ƿ�ת��CS�� */
    VOS_UINT32                          bitOpRsv                :26;

    VOS_UINT8                           ucSpmcallId;           /**< IMSA��SPM�佻���ĺ���id */
    IMSA_CALL_STATUS_ENUM_UINT8         enStatus;       /**< ����״̬ */
    IMSA_CALL_TYPE_ENUM_UINT8           enType;         /**< �������� */

    MN_CALL_DIR_ENUM_UINT8              enDir;          /**< ���з��� */
    MN_CALL_MPTY_STATE_ENUM_UINT8       enMpty;         /**< �Ƿ�෽����  */
    MN_CALL_MODE_ENUM_UINT8             enMode;         /**< ����ģʽ */

    VOS_UINT16                          usClientId;         /**< Client Id */
    VOS_UINT32                          ulOpId;             /**< SPM�����opid */

    IMSA_EMC_CALL_TYPE_ENUM_UINT32      enEmcType;      /**< ���������� */

    IMSA_CALL_NUMBER_STRU               stCallNumber;   /**< ���к��� */
    IMSA_CALLED_NUMBER_STRU             stCalledNumber; /**< ���к��� */

    IMSA_CALL_NUMBER_STRU               stConnectNumber;   /**< ���Ӻ��� */
    IMSA_CALL_NUMBER_STRU               stRedirectNumber;   /**< ���Ӻ��� */

    VOS_UINT32                          ulResRspOpId;   /**< �ȴ���Դ�����opid����IMS���� */
    IMSA_CALL_SPM_MSG_STRU              stSpmMsg;       /**< MOʱ�����˺��е�SPM��Ϣ��������б�����380�ܾ�����Ҫ���·���������ͺ���ʱ�õ� */
    IMSA_IMS_CALL_ERROR_STRU            stImsError;
    MN_CALL_DISC_DIR                    stDiscDir;      /* �Ҷϵ绰�ķ��� */

    VOS_UINT8                           ucRedialTimes;  /* �ز����� */
    VOS_UINT8                           ucCallEntityIndex;      /* ʵ�������� */
    VOS_UINT8                           ucImscallId;           /**< IMSA��IMS�佻���ĺ���id */
    VOS_UINT8                           ucIsEconfFlag;  /**< �Ƿ�����ǿ�෽ͨ���ı�ʶ */
    VOS_UINT8                           ucMaxUserNum;
    VOS_UINT8                           ucCurUserNum;
    VOS_UINT8                           ucTqosExpFlag;
    VOS_UINT8                           aucRsv;

    IMSA_CALL_ECONF_SUMMARY_STRU        stEconfCalllist[IMSA_IMS_ECONF_CALLED_MAX_NUM];    /* ��ǿ�෽ͨ���ĳ�Ա�б� */
}IMSA_CALL_ENTITY_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_CALL_DTMF_INFO_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DTMF��Ϣ���
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallId;
    VOS_CHAR                            cKey;                                   /* DTMF Key */
    VOS_UINT16                          usOnLength;                             /* DTMF����ʱ�䣬0: ����ֹͣDTMF */
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucSpmOpId;
    VOS_UINT8                           ucRsv;
    VOS_UINT32                          ulImsOpid;
} IMSA_CALL_DTMF_INFO_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_CALL_DTMF_CTX_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : DTMF������
*****************************************************************************/
typedef struct
{
    IMSA_CALL_DTMF_STATE_ENUM_UINT8     enDtmfState;                            /**< dmtf ״̬ */
    VOS_UINT8                           ucDtmfCnt;                              /**< dtmf������� */
    VOS_UINT8                           aucRsv[2];
    IMSA_TIMER_STRU                     stDtmfDurationTimer;                    /**< dmtf duration��ʱ�� */
    IMSA_TIMER_STRU                     stDtmfProtectTimer;                     /**< dmtf ������ʱ�� */
    IMSA_CALL_DTMF_INFO_STRU            stCurrentDtmf;                          /**< Ϊ�˷�ֹCALL��DTMF����ͬʱ���У���˷ֿ��洢
                                                                                     ����DTMF duration��ʱ������IMSA��stop dtmf֮��Ϊ�յ�IMS��Ӧ֮ǰ����SWAP������ */

    IMSA_CALL_DTMF_INFO_STRU            stDtmfBufList[IMSA_CALL_DTMF_BUF_MAX_NUM];  /**< dtmf�������� */
}IMSA_CALL_DTMF_CTX_STRU;


/*****************************************************************************
 �ṹ��    : IMSA_CALL_MANAGER_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : ���й���ģ��������
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucCallNum;              /**< ���и��� */
    VOS_UINT8                           aucRsv[3];
    IMSA_CALL_ENTITY_STRU               astCallEntity[IMSA_CALL_MAX_NUM];   /**< ���к���ʵ�� */

    IMSA_CALL_SPM_MSG_STRU              stSpmMsg;               /**< ���浱ǰ����ִ�е�SPM��Ϣ */
    IMSA_SAVED_IMS_MSG_STRU             stImsMsg;               /**< IMS����ִ����Ϣ */

    IMSA_TIMER_STRU                     stProctectTimer;        /**< ������ʱ�� */
    IMSA_TIMER_STRU                     stResReadyTimer;        /**< �ȴ���ԴReady�Ķ�ʱ�� */



    VOS_UINT8                           ucVoiceBearExistFlag;    /**< ��¼����ý������Ƿ���� */
    VOS_UINT8                           ucVideoBearExistFlag;    /**< ��¼��Ƶý������Ƿ���� */
    VOS_UINT8                           aucRsv2[2];

    VOS_UINT8                           ucRetryEmcRegFlag;      /**< ���������յ�#380�����·���ע��ı�ʶ */
    VOS_UINT8                           ucCallEntityIndex;      /**< ��һ�ν������У�ʹ�õĺ���ʵ���ID */
    VOS_UINT8                           ucId;                   /**< ��һ�ν������У�ʹ�õ�CALL ID */
    VOS_UINT8                           ucRsv2;

    VOS_UINT32                          ulLastResult;           /**< ���ʧ��ԭ�� */
    VOS_UINT32                          ulLastStatusCode;       /**< ���ʧ��ʱ��������ԭ��ֵ */

    VOS_UINT8                           ucIsTcallTimeOutProc;   /**< ��¼Tcall��ʱ����ʱ���� */
    VOS_UINT8                           aucReserve[3];

    VOS_UINT32                          ulSrvccFlag;            /**< ����Ƿ���SRVCC������ */
    VOS_UINT32                          ulNotReprotAllReleasedFlag;  /**< ��ǲ����ϱ�ALL RELEASED�¼� */
    IMSA_CALL_DTMF_CTX_STRU             stDtmfCtx;              /**< DTMF������ */

    IMSA_TIMER_STRU                     stBackOffTxTimer;       /*SSAC Tx��ʱ��*/
    IMSA_TIMER_STRU                     stBackOffTyTimer;       /*SSAC Ty��ʱ��*/

    IMSA_TIMER_STRU                     stRedialMaxTimer;       /* IMS�����ز����ʱ����ʱ�� */
    IMSA_TIMER_STRU                     stRedialIntervelTimer;  /* IMS�����ز������ʱ�� */

    IMSA_TIMER_STRU                     stNormalTcallTimer;     /* ��ͨ����Tcall��ʱ����������������Ƶ���� */
    IMSA_TIMER_STRU                     stEmcTcallTimer;        /* ��������Tcall��ʱ�� */
}IMSA_CALL_MANAGER_STRU;



typedef struct
{
                                        /*����SPM��Ϣ*/
    VOS_UINT32                          ulSpmOpId;/*SPM */
    /*���淢�͸�IMS����Ϣ*/
    VOS_UINT32                          ulImsOpId;
}IMSA_MSG_MANAGER_STRU;

typedef struct
{
    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32        enCireg;
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32          enReport;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    /* jiaguocai 00355737 begin amend for ccwa 2015-09-07*/
    VOS_UINT8                           enMode;
    /* jiaguocai 00355737 end  amend for ccwa 2015-09-07*/

}IMSA_AT_CONTROL_STRU;
typedef union
{
    SPM_IMSA_CALL_ORIG_REQ_STRU         stOrigReq;
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU     stSupsCmdReq;
    SPM_IMSA_CALL_START_DTMF_REQ_STRU   stStartDtmfReq;
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU    stStopDtmfReq;
    SPM_IMSA_PROCESS_USSD_REQ_STRU      stProcUssdReq;
} IMSA_SRVCC_BUFF_MSG_UNION;

typedef struct
{
    VOS_UINT8                           ucBuffMsgNum;
    VOS_UINT8                           aucReserved[3];
    IMSA_SRVCC_BUFF_MSG_UNION           aucBuffMsgArray[IMSA_CALL_MSG_SYNC_MAX_NUM];
}IMSA_SRVCC_BUFFER_STRU;

typedef IMSA_NV_PCSCF_DISCOVERY_POLICY_STRU IMSA_PCSCF_DISCOVERY_POLICY_INFO_STRU;


typedef struct
{
    IMSA_STATUS_ENUM_UINT8              enImsaStatus;       /**< IMSA״̬:δ���������������С��ѿ������ػ�������*/
    IMSA_ISIM_STATUS_ENUM_UINT8         enImsaIsimStatus;   /**< ISIM��״̬ */
    VOS_UINT8                           ucImsaUsimStatus;   /**< USIM��״̬ */
    IMSA_SRV_CONN_STATUS_EXIST_ENUM_UINT8  enIsImsSrvExist;    /**< �Ƿ�IMSҵ�����: 0��ʾ�����ڣ�1��ʾ����*/
    IMSA_TIMER_STRU                     stProtectTimer;     /**< ���ػ�������ʱ�� */
    IMSA_CONFIG_PARA_STRU               stImsaConfigPara;   /**< IMS���ò��� */
    IMSA_NETWORK_INFO_STRU              stImsaNetworkInfo;  /**< ���绷������ */
    IMSA_COMMON_INFO_STRU               stImsaCommonInfo;   /**< IMSA������Ϣ */
    IMSA_TIMER_STRU                     stPeriodImsSrvTryTimer;/**< �����Գ���IMS����ʱ�� */
    IMSA_TIMER_STRU                     stPeriodImsEmcSrvTryTimer;/**< �����Գ��Խ���IMS����ʱ�� */
    IMSA_SRV_STATUS_ENUM_UINT8          enNrmSrvStatus;     /**< ��ͨservice״̬ */
    IMSA_SRV_STATUS_ENUM_UINT8          enEmcSrvStatus;     /**< ����service״̬ */

    MTC_IMSA_MODEM_POWER_STATE_ENUM_UINT8  enPowerState;    /**< Modem1���ػ�״̬ */
    MSCC_IMSA_STOP_TYPE_ENUM_UINT32     enStopType;         /**< �ػ���������� */
    /* zhaochen 00308719 begin for card lock 2015-10-31 */
    VOS_UINT8                           ucIsCardLocked;     /**< SIM���Ƿ���: 0��ʾû�б�����1��ʾ���� */
    /* zhaochen 00308719 end for card lock 2015-10-31 */

    IMSA_SRV_DEREG_CAUSE_ENUM_UINT32    enDeregCause;           /**< ȥע������*/
    IMSA_INTRA_MSG_QUEUE_STRU           stImsaIntraMsgQueue;    /**< �ڲ���Ϣ���� */

    IMSA_AT_CONTROL_STRU                stAtControl;
    IMSA_SRVCC_BUFFER_STRU              stSrvccBuffer;          /**< SRVCC���̻��� */
    IMSA_SAVED_IMS_MSG_STRU             stImsMsg;               /**< IMS����ִ����Ϣ */

    IMSA_REG_PARA_INFO_STRU             stNrmRegParaInfo;          /**< �洢��ǰ��ͨע����Ϣ */
    IMSA_REG_PARA_INFO_STRU             stEmcRegParaInfo;          /**< �洢��ǰ����ע����Ϣ */

    IMSA_PCSCF_DISCOVERY_POLICY_INFO_STRU    stPcscfDiscoveryPolicyInfo;/**< �洢P-CSCF��ȡ���Լ���Ӧ�ĵ�ַ */

    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enNrmAddrType;  /**< ע��ʱʹ�õĵ�ַ������ */
    IMSA_REG_ADDR_PARAM_ENUM_UINT32     enEmcAddrType;  /**< ע��ʱʹ�õĵ�ַ������ */
    IMSA_ERR_LOG_REG_CONDITION_STATUS_STRU  stRegConditionStatus;
    #endif
}IMSA_CONTROL_MANAGER_STRU;

/*****************************************************************************
 �ṹ����: IMSA_PDP_IPV4_DNS_STRU
 �ṹ˵��: IPv4 DNS��ַ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns   : 1;
    VOS_UINT32                          bitOpSecDns   : 1;
    VOS_UINT32                          bitOpSpare    : 30;

    VOS_UINT8                           aucPriDns[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecDns[IMSA_IPV4_ADDR_LEN];
}IMSA_PDP_IPV4_DNS_STRU;

/*****************************************************************************
 �ṹ����: IMSA_PDP_IPV4_PCSCF_STRU
 �ṹ˵��: IPv4 P-CSCF��ַ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[IMSA_IPV4_ADDR_LEN];
} IMSA_PDP_IPV4_PCSCF_STRU;

/*****************************************************************************
 �ṹ����: IMSA_PDP_IPV6_PCSCF_STRU
 �ṹ˵��: IPv6 P-CSCF��ַ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPrimPcscfAddr  : 1;
    VOS_UINT32                          bitOpSecPcscfAddr   : 1;
    VOS_UINT32                          bitOpThiPcscfAddr   : 1;
    VOS_UINT32                          bitOpSpare          : 29;

    VOS_UINT8                           aucPrimPcscfAddr[IMSA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecPcscfAddr[IMSA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucThiPcscfAddr[IMSA_IPV6_ADDR_LEN];
} IMSA_PDP_IPV6_PCSCF_STRU;

/*****************************************************************************
 �ṹ����   : IMSA_PDP_IPV6_DNS_STRU
 �ṹ˵��   : IPv6 DNS��ַ�ṹ��
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          bitOpPriDns     : 1;
    VOS_UINT32                          bitOpSecDns     : 1;
    VOS_UINT32                          bitOpSpare      : 30;

    VOS_UINT8                           aucPriDns[IMSA_IPV6_ADDR_LEN];
    VOS_UINT8                           aucSecDns[IMSA_IPV6_ADDR_LEN];
} IMSA_PDP_IPV6_DNS_STRU;

/*****************************************************************************
 �ṹ��    : IMSA_IP_ADDRESS_STRU
 �ṹ˵��  : IP��ַ�Ľṹ��
*****************************************************************************/
typedef struct
{
    IMSA_IP_TYPE_ENUM_UINT8             enIpType;
    VOS_UINT8                           ucReserved[3];
    VOS_UINT8                           aucIpV4Addr[IMSA_IPV4_ADDR_LEN];
    VOS_UINT8                           aucIpV6Addr[IMSA_IPV6_ADDR_LEN];
}IMSA_IP_ADDRESS_STRU;


typedef struct
{
    VOS_UINT32                          bitOpRmtIpv4AddrAndMask     : 1;
    VOS_UINT32                          bitOpRmtIpv6AddrAndMask     : 1;
    VOS_UINT32                          bitOpProtocolId             : 1;
    VOS_UINT32                          bitOpSingleLocalPort        : 1;
    VOS_UINT32                          bitOpLocalPortRange         : 1;
    VOS_UINT32                          bitOpSingleRemotePort       : 1;
    VOS_UINT32                          bitOpRemotePortRange        : 1;
    VOS_UINT32                          bitOpSecuParaIndex          : 1;
    VOS_UINT32                          bitOpTypeOfService          : 1;
    VOS_UINT32                          bitOpFlowLabelType          : 1;
    VOS_UINT32                          bitOpSpare                  : 22;

    VOS_UINT8                           ucPacketFilterId;
    VOS_UINT8                           ucNwPacketFilterId;
    IMSA_PF_TRANS_DIRECTION_ENUM_UINT8  enDirection;
    VOS_UINT8                           ucPrecedence;                           /* packet filter evaluation precedence */

    VOS_UINT32                          ulSecuParaIndex;                        /* SPI */
    VOS_UINT16                          usSingleLcPort;
    VOS_UINT16                          usLcPortHighLimit;
    VOS_UINT16                          usLcPortLowLimit;
    VOS_UINT16                          usSingleRmtPort;
    VOS_UINT16                          usRmtPortHighLimit;
    VOS_UINT16                          usRmtPortLowLimit;
    VOS_UINT8                           ucProtocolId;                           /* Э��� */
    VOS_UINT8                           ucTypeOfService;                        /* TOS */
    VOS_UINT8                           ucTypeOfServiceMask;                    /* TOS Mask */
    VOS_UINT8                           aucReserved[1];

    /* aucRmtIpv4Address[0]ΪIP��ַ���ֽ�λ
       aucRmtIpv4Address[3]Ϊ���ֽ�λ */
    VOS_UINT8                           aucRmtIpv4Address[IMSA_IPV4_ADDR_LEN];

    /* aucRmtIpv4Mask[0]ΪIP��ַ���ֽ�λ ,
       aucRmtIpv4Mask[3]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv4Mask[IMSA_IPV4_ADDR_LEN];

    /* ucRmtIpv6Address[0]ΪIPv6�ӿڱ�ʶ���ֽ�λ
       ucRmtIpv6Address[7]ΪIPv6�ӿڱ�ʶ���ֽ�λ */
    VOS_UINT8                           aucRmtIpv6Address[IMSA_IPV6_ADDR_LEN];

    /* ucRmtIpv6Mask[0]Ϊ���ֽ�λ
       ucRmtIpv6Mask[7]Ϊ���ֽ�λ*/
    VOS_UINT8                           aucRmtIpv6Mask[IMSA_IPV6_ADDR_LEN];

    VOS_UINT32                          ulFlowLabelType;                        /*FlowLabelType*/
}IMSA_PDP_TFT_STRU;
typedef struct
{
    VOS_UINT32                          ulPfNum;            /**< ���ع������� */
    IMSA_PDP_TFT_STRU                   astTftInfo[IMSA_MAX_PF_NUM];    /**< ���ع�������Ϣ */
}IMSA_PDP_TFT_INFO_STRU;

typedef struct
{
    VOS_UINT8               ucTrafficClass;                                     /**< UMTS���ط����Ż����� */
    VOS_UINT8               ucDeliverOrder;                                     /**< SDU�����Ƿ���UMTS���� */
    VOS_UINT8               ucDeliverErrSdu;                                    /**< SDU�����Ƿ��� */
    VOS_UINT8               aucRsv1[1];
    VOS_UINT16              usMaxSduSize;                                       /**< SDU��С���ֵ */
    VOS_UINT8               aucRsv2[2];
    VOS_UINT32              ulMaxBitUl;                                         /**< ����������� kbits/s */
    VOS_UINT32              ulMaxBitDl;                                         /**< ����������� kbits/s */
    VOS_UINT8               ucResidualBer;
    VOS_UINT8               ucSduErrRatio;                                      /**< SDU������ */
    VOS_UINT16              usTransDelay;                                       /**< ������ʱ, ��λ���� */
    VOS_UINT8               ucTraffHandlePrior;                                 /**< ����UMTS���ص�SDU�Ա��������ص�SDU */
    VOS_UINT8               aucRsv3[1];
    VOS_UINT8               ucSrcStatisticsDescriptor;
    VOS_UINT8               ucSignallingIndication;
    VOS_UINT32              ulGuarantBitUl;                                     /**< ��֤���д������� kbits/s */
    VOS_UINT32              ulGuarantBitDl;                                     /**< ��֤���д������� kbits/s */
}IMSA_PDP_UMTS_QOS_STRU;

typedef struct
{
    /* 0 QCI is selected by network
       [1 - 4]value range for guranteed bit rate Traffic Flows
       [5 - 9]value range for non-guarenteed bit rate Traffic Flows */
    VOS_UINT8                           ucQCI;

    VOS_UINT8                           aucReserved[3];

    /* DL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLGBR;

    /* UL GBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULGBR;

    /* DL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulDLMBR;

    /* UL MBR in case of GBR QCI, The value is in kbit/s */
    VOS_UINT32                          ulULMBR;
}IMSA_PDP_EPS_QOS_STRU;


/*****************************************************************************
 �ṹ����: IMSA_PDP_APN_STRU
 �ṹ˵��: APN�ṹ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucLength;
    VOS_UINT8                           aucValue[IMSA_MAX_APN_LEN];
} IMSA_PDP_APN_STRU;


typedef struct
{
    VOS_UINT32                          bitOpLinkedPdpId    : 1;
    VOS_UINT32                          bitOpPdpAddr        : 1;
    VOS_UINT32                          bitOpTft            : 1;
    /*VOS_UINT32                          bitOpApn            : 1;*/
    VOS_UINT32                          bitOpSpare          : 29;


    VOS_UINT8                           ucPdpId;            /**< ���غ� */
    VOS_UINT8                           ucLinkedPdpId;      /**< ��˳��ع�����ȱʡ���غ� ��������Ϊר��ʱ��Ч */
    VOS_UINT8                           ucCid;              /**< �˳��ض�Ӧ��CID */
    VOS_UINT8                           ucReserved1;

    IMSA_PDP_STATE_ENUM_UINT8           enPdpState;         /**< ����״̬ */
    IMSA_PDP_TYPE_ENUM_UINT8            enPdpType;          /**< �������� */
    VOS_UINT8                           aucReserved2[2];
    IMSA_IP_ADDRESS_STRU                stPdpAddr;          /**< ����IP��ַ */
    /*IMSA_PDP_APN_STRU                   stApn;*/              /**< ����APN��Ϣ */

    IMSA_PDP_IPV4_DNS_STRU              stPdpIpv4Dns;       /**< ����IPV4 DNS��Ϣ */
    IMSA_PDP_IPV4_PCSCF_STRU            stPdpIpv4Pcscf;     /**< ����IPV4 P-CSCF��Ϣ */
    IMSA_PDP_IPV6_DNS_STRU              stPdpIpv6Dns;       /**< ����IPV6 DNS��Ϣ */
    IMSA_PDP_IPV6_PCSCF_STRU            stPdpIpv6Pcscf;     /**< ����IPV6 P-CSCF��Ϣ */

    IMSA_PDP_EPS_QOS_STRU               stEpsQos;           /**< ����EPS QOS��Ϣ */
    IMSA_PDP_TFT_INFO_STRU              stTft;              /**< ����TFT��Ϣ */
}IMSA_PDP_CNTXT_INFO_STRU;

typedef struct
{
    VOS_UINT32                          bitOpLinkdCid       : 1;
    VOS_UINT32                          bitOpPdnType        : 1;
    VOS_UINT32                          bitOpApn            : 1;
    VOS_UINT32                          bitOpGwAuthInfo     : 1;
    VOS_UINT32                          bitOpEmergencyInd   : 1;
    VOS_UINT32                          bitOpIpv4AddrAllocType: 1;
    VOS_UINT32                          bitOpPcscfDiscovery : 1;
    VOS_UINT32                          bitOpImCnSignalFlg  : 1;
    VOS_UINT32                          bitOpImsSuppFlg     : 1;
    VOS_UINT32                          bitOpSpare          : 23;

    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucLinkdCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    TAF_PDP_IPV4_ADDR_ALLOC_TYPE_ENUM_UINT8 enIpv4AddrAllocType;

    TAF_PDP_EMC_IND_ENUM_UINT8          enEmergencyInd;
    TAF_PDP_PCSCF_DISCOVERY_ENUM_UINT8  enPcscfDiscovery;
    TAF_PDP_IM_CN_SIG_FLAG_ENUM_UINT8   enImCnSignalFlg;
    VOS_UINT8                           ucImsSuppFlg;
    VOS_UINT8                           ucReserved;

    TAF_PDP_APN_STRU                    stApnInfo;
    TAF_GW_AUTH_STRU                    stGwAuthInfo;
}IMSA_SEL_SDF_PARA_STRU;

typedef struct
{
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatus;   /**< ����״̬ */
    IMSA_IP_TYPE_ENUM_UINT8             enFirstReqPdnType;  /**< ��������PDN���� */
    IMSA_IP_TYPE_ENUM_UINT8             enCurReqPdnType;    /**< ��ǰ�����PDN���� */
    VOS_UINT8                           ucIsApnChanged;     /**< �����APN�ͳ��ؼ�����Ϣ�е�APN�Ƿ����仯 */


    IMSA_TIMER_STRU                     stProtectTimer;     /**< ������ʱ��,IMS���ź�ȥ���Ŷ�ʱ�� */
    VOS_UINT8                           ucOpid;             /**< ��ʶ���� */
    VOS_UINT8                           ucCurMaxOpid;       /**< ��ǰ�����ȥ�����OPID */

    IMSA_SEL_SDF_PARA_STRU              stSelSdfPara;       /**< ѡ�в��ŵ�SDF��Ϣ */

    VOS_UINT32                          ulSipSignalPdpNum;  /**< SIP��������� */
    IMSA_PDP_CNTXT_INFO_STRU            astSipSignalPdpArray[IMSA_CONN_MAX_NORMAL_SIP_SIGNAL_PDP_NUM];  /**< SIP���������Ϣ */

    VOS_UINT32                          ulSipMediaPdpNum;   /**< SIPý������� */
    IMSA_PDP_CNTXT_INFO_STRU            astSipMediaPdpArray[IMSA_CONN_MAX_NORMAL_SIP_MEDIA_PDP_NUM];    /**< SIPý�������Ϣ */
}IMSA_NORMAL_CONN_STRU;

typedef struct
{
    IMSA_CONN_STATUS_ENUM_UINT8         enImsaConnStatus;   /**< ����״̬ */
    IMSA_IP_TYPE_ENUM_UINT8             enFirstReqPdnType;  /**< ��������PDN���� */
    IMSA_IP_TYPE_ENUM_UINT8             enCurReqPdnType;    /**< ��ǰ�����PDN���� */
    VOS_UINT8                           ucIsApnChanged;     /**< �����APN�ͳ��ؼ�����Ϣ�е�APN�Ƿ����仯 */

    IMSA_TIMER_STRU                     stProtectTimer;     /**< ������ʱ��,IMS���ź�ȥ���Ŷ�ʱ�� */
    VOS_UINT8                           ucOpid;             /**< ��ʶ���� */
    VOS_UINT8                           ucCurMaxOpid;       /**< ��ǰ�����ȥ�����OPID */

    IMSA_SEL_SDF_PARA_STRU              stSelSdfPara;       /**< ѡ�в��ŵ�SDF��Ϣ */

    IMSA_PDP_CNTXT_INFO_STRU            stSipSignalPdp;     /**< SIP���������Ϣ */

    VOS_UINT32                          ulSipMediaPdpNum;   /**< SIPý������� */
    IMSA_PDP_CNTXT_INFO_STRU            astSipMediaPdpArray[IMSA_CONN_MAX_EMC_SIP_MEDIA_PDP_NUM];/**< SIPý�������Ϣ */
}IMSA_EMC_CONN_STRU;

typedef struct
{
    VOS_UINT8                           ucPdpId;            /**< ���غ� */
    VOS_UINT8                           ucIsUsed;           /**< ʹ�ñ�ʶ 1:ʹ��  0:δʹ�� */
    VOS_UINT8                           ucIsEmc;            /**< ������ʶ 1:����  0:�ǽ��� */
    VOS_UINT8                           ucResv;
    IMSA_IP_ADDRESS_STRU                stPdpAddr;          /**< ����IP��ַ */
}IMSA_CONN_NIC_PDP_INFO_STRU;

typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                          ulMsgId;
    IMSA_CONN_NIC_PDP_INFO_STRU         astNicPdpInfoArray[IMSA_CONN_MAX_NIC_PDP_NUM]; /* ���ø�NIC��PDP��Ϣ */

}IMSA_PRINT_NIC_PDP_INFO_STRU;

typedef struct
{
    VOS_UINT32                          ulCauseNum;
    TAF_PS_CAUSE_ENUM_UINT32            aenPsCause[TAF_NV_IPV6_FALLBACK_EXT_CAUSE_MAX_NUM];
}IMSA_IPV6_FALLBACK_EXT_CAUSE_STRU;

typedef struct
{
    IMSA_NORMAL_CONN_STRU               stNormalConn;       /**< ��ͨ���� */
    IMSA_EMC_CONN_STRU                  stEmcConn;          /**< �������� */

    IMSA_CONN_NIC_PDP_INFO_STRU         astNicPdpInfoArray[IMSA_CONN_MAX_NIC_PDP_NUM]; /* ���ø�NIC��PDP��Ϣ */

    IMSA_IPV6_FALLBACK_EXT_CAUSE_STRU   stIpv6FallBackExtCause;
}IMSA_CONN_MANAGER_STRU;

typedef struct
{
    IMSA_SMS_SMR_STATE_ENUM_UINT8       enState;                /* SMRʵ��״̬                              */
    VOS_UINT8                           ucMessageReference;     /* Message Reference                        */
    VOS_UINT8                           ucMemAvailFlg;          /* ��־�Ƿ���֪ͨ����                       */
    VOS_UINT8                           ucRetransFlg;           /* �Ƿ��ش���־                             */
    IMSA_TIMER_STRU                     stTR1MTimer;            /* TR1M TIMER��Ϣ                                */
    IMSA_TIMER_STRU                     stTRAMTimer;            /* TRAM TIMER��Ϣ                                */
}IMSA_SMS_SMR_MO_STRU;

typedef struct
{
    IMSA_SMS_SMR_STATE_ENUM_UINT8       enState;                                /* SMR MTʵ��״̬                              */
    VOS_UINT8                           ucMessageReference;                     /* Message Reference                        */
    VOS_UINT8                           aucReserved2[2];
    IMSA_TIMER_STRU                     stTimerInfo;                              /* TIMER��Ϣ                                */
}IMSA_SMS_SMR_MT_STRU;

typedef struct
{
    IMSA_SMS_SMR_MO_STRU                stImsaSmrMo;
    IMSA_SMS_SMR_MT_STRU                stImsaSmrMt;
}IMSA_SMS_MANAGER_STRU;


typedef struct
{
    AT_IMSA_IMS_REG_STATE_REPORT_ENUM_UINT32        enCireg;
    AT_IMSA_IMSVOPS_CAPABILITY_ENUM_UINT32          enReport;

}IMSA_AT_MANAGER_STRU;

typedef struct
{
    IMSA_USSD_STATE_ENUM_UINT8          enUssdState;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    IMSA_TIMER_STRU                     stUssdWaitNetRspTimer;
    IMSA_TIMER_STRU                     stUssdWaitAppRspTimer;
}IMSA_USSD_MANAGER_STRU;

#if (FEATURE_ON == FEATURE_PTM)
/*****************************************************************************
 �ṹ����   :IMSA_ERRLOG_CTRL_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMSA_ERRLOG_CTRL_INFO_STRU��Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucErrLogCtrlFlag;   /* ERRLOG���ر�ʶ */
    VOS_UINT8                           ucReserved;
    VOS_UINT16                          usAlmLevel;       /* �ȼ� */
}IMSA_ERRLOG_CTRL_INFO_STRU;
/*****************************************************************************
 �ṹ����   :IMSA_ERRLOG_BUFF_INFO_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : IMSA_ERRLOG_BUFF_INFO_STRU��Ϣ
*****************************************************************************/
typedef struct
{
    OM_RING_ID                          pstRingBuffer;  /* IMSA��buffer�ĵ�ַ */
    VOS_UINT32                          ulOverflowCnt;  /* Ringbuf����Ĵ��� */
}IMSA_ERRLOG_BUFF_INFO_STRU;
/*****************************************************************************
 �ṹ����   :IMSA_ERRORLOG_MANAGER_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : ERROR LOG�Ŀ�����Ϣ
*****************************************************************************/
typedef struct
{
    IMSA_ERRLOG_CTRL_INFO_STRU       stCtrlInfo;
    IMSA_ERRLOG_BUFF_INFO_STRU       stBuffInfo;
}IMSA_ERRORLOG_MANAGER_STRU;
#endif

/* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
/*****************************************************************************
 �ṹ����   :IMSA_HIFI_DATA_BUFFER_NODE_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : HIFI�������Ļ�����Ϣ
*****************************************************************************/
typedef struct tagIMSA_HIFI_DATA_BUFFER_NODE_STRU
{
    IMSA_VOICE_RX_DATA_IND_STRU               *pstRxDataInd;           /* ����ķ��͸�HIFI�������� */
    struct tagIMSA_HIFI_DATA_BUFFER_NODE_STRU *pstNextBufferData;      /* �������һ���ڵ� */
}IMSA_HIFI_DATA_BUFFER_NODE_STRU;
/*****************************************************************************
 �ṹ����   :IMSA_HIFI_DATA_MANAGER_STRU
 Э����   :
 ASN.1 ���� :
 �ṹ˵��   : HIFI�������Ŀ�����Ϣ
*****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHifiDataControlFlag;  /* �Ƿ���Hifi��Ϣ����: TRUE:������FALSE:�ر� */
    VOS_UINT8                           ucSentDataNum;          /* ��HIFI���͵����ݰ����� */
    VOS_UINT8                           ucBufferDataNum;        /* ���ػ�������ݰ����� */
    VOS_UINT8                           ucHifiDataNeedAckNum;   /* ������������Ϣ����ҪHifi�ظ� */
    VOS_UINT8                           ucHifiDatMaxBufferNum;  /* ��󻺴���Ϣ���� */
    VOS_UINT8                           ucRsv[3];               /* ���� */
    VOS_UINT32                          ulOpid;                 /* Opidֵ������ͬ����Ϣ */
    VOS_UINT32                          ulDataLoseNum;
    VOS_UINT32                          ulTotalDataLoseNum;
    VOS_UINT32                          ulDataBufferNum;
    VOS_UINT32                          ulTotalDataBufferNum;

    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstBufferDataHead;      /* ������Ϣ������ͷ */
    IMSA_HIFI_DATA_BUFFER_NODE_STRU    *pstBufferDataTail;      /* ��ǰ������Ϣ�Ľڵ� */
    IMSA_TIMER_STRU                     stHifiAckProtectTimer;  /* �ȴ�HIFI��ִ�ı�����ʱ�� */
}IMSA_HIFI_DATA_MANAGER_STRU;
/* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */
typedef struct
{
    IMSA_CONTROL_MANAGER_STRU           stImsaControlManager;   /**< �������Ĺ�����Ϣ */
    IMSA_REG_MANAGER_STRU               stImsaRegManager;       /**< ע�������Ϣ */
    IMSA_CONN_MANAGER_STRU              stImsaConnManager;      /**< ���ӹ�����Ϣ */
    IMSA_CALL_MANAGER_STRU              stImsaCallManager;      /**< ���й�����Ϣ */
    IMSA_SMS_MANAGER_STRU               stImsaSmsManager;       /**< SMS����ʵ��*/
    IMSA_USSD_MANAGER_STRU              stImsaUssdManager;
    /*USSD/SS����ʵ��*/
    #if (FEATURE_ON == FEATURE_PTM)
    IMSA_ERRORLOG_MANAGER_STRU          stImsaErrorlogManager;  /**< ERROR LOG������Ϣ */
    #endif
    /* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
    IMSA_HIFI_DATA_MANAGER_STRU         stImsaHifiDataManager;  /**< HIFI�������Ŀ�����Ϣ*/
    /* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */

} IMSA_ENTITY_STRU;

#if (FEATURE_ON == FEATURE_PTM)
typedef struct
{
    TAF_PS_CAUSE_ENUM_UINT32                enCause;    /* TAF REJ CAUSE */
    IMSA_ERR_LOG_PDNREJ_CAUSE_ENUM_UINT32   enImsaCnRejCause; /* IMSA REJ CAUSE */
}IMSA_CN_CAUSE_TRANS_STRU;
#endif



/*****************************************************************************
  6 UNION
*****************************************************************************/


/*****************************************************************************
  7 Extern Global Variable
*****************************************************************************/
extern    IMSA_ENTITY_STRU     *pgstImsaEntity;
extern    IMSA_ENTITY_STRU      g_stImsaEntity;

/* CONNʵ�����غ� */
#define IMSA_CONN_GetConnManagerAddr()      (&pgstImsaEntity->stImsaConnManager)
#define IMSA_CONN_GetNormalConnAddr()       (&pgstImsaEntity->stImsaConnManager.stNormalConn)
#define IMSA_CONN_GetEmcConnAddr()          (&pgstImsaEntity->stImsaConnManager.stEmcConn)
#define IMSA_CONN_GetNormalConnOpid()       (IMSA_CONN_GetNormalConnAddr()->ucOpid)
#define IMSA_CONN_GetEmcConnOpid()          (IMSA_CONN_GetEmcConnAddr()->ucOpid)
#define IMSA_CONN_SetNormalConnOpid(ucOpid) (IMSA_CONN_GetNormalConnOpid() = (ucOpid))
#define IMSA_CONN_SetEmcConnOpid(ucOpid)    (IMSA_CONN_GetEmcConnOpid() = (ucOpid))
#define IMSA_CONN_GetNormalConnCurMaxOpid() (IMSA_CONN_GetNormalConnAddr()->ucCurMaxOpid)
#define IMSA_CONN_GetEmcConnCurMaxOpid()    (IMSA_CONN_GetEmcConnAddr()->ucCurMaxOpid)
#define IMSA_CONN_SetNormalConnCurMaxOpid(ucCurMaxOpid) (IMSA_CONN_GetNormalConnCurMaxOpid() = (ucCurMaxOpid))
#define IMSA_CONN_SetEmcConnCurMaxOpid(ucCurMaxOpid)    (IMSA_CONN_GetEmcConnCurMaxOpid() = (ucCurMaxOpid))
#define IMSA_CONN_GetNormalConnStatus()     (IMSA_CONN_GetNormalConnAddr()->enImsaConnStatus)
#define IMSA_CONN_GetEmcConnStatus()        (IMSA_CONN_GetEmcConnAddr()->enImsaConnStatus)
#define IMSA_CONN_GetNormalConnSelSdfParaAddr()         (&(IMSA_CONN_GetNormalConnAddr()->stSelSdfPara))
#define IMSA_CONN_GetEmcConnSelSdfParaAddr()            (&(IMSA_CONN_GetEmcConnAddr()->stSelSdfPara))
#define IMSA_CONN_GetNormalConnProtectTimerAddr()       (&(IMSA_CONN_GetNormalConnAddr()->stProtectTimer))
#define IMSA_CONN_GetEmcConnProtectTimerAddr()          (&(IMSA_CONN_GetEmcConnAddr()->stProtectTimer))
#define IMSA_CONN_GetNormalConnFirstReqPdnType()        (IMSA_CONN_GetNormalConnAddr()->enFirstReqPdnType)
#define IMSA_CONN_GetEmcConnFirstReqPdnType()           (IMSA_CONN_GetEmcConnAddr()->enFirstReqPdnType)
#define IMSA_CONN_GetNormalConnCurReqPdnType()          (IMSA_CONN_GetNormalConnAddr()->enCurReqPdnType)
#define IMSA_CONN_GetEmcConnCurReqPdnType()             (IMSA_CONN_GetEmcConnAddr()->enCurReqPdnType)
#define IMSA_CONN_GetConnFirstReqPdnType(enConnType, enFirstReqPdnType)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                (enFirstReqPdnType) = IMSA_CONN_GetNormalConnFirstReqPdnType();\
            }\
            else\
            {\
                (enFirstReqPdnType) = IMSA_CONN_GetEmcConnFirstReqPdnType();\
            }\
        }

#define IMSA_CONN_GetConnCurReqPdnType(enConnType, enCurReqPdnType)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                (enCurReqPdnType) = IMSA_CONN_GetNormalConnCurReqPdnType();\
            }\
            else\
            {\
                (enCurReqPdnType) = IMSA_CONN_GetEmcConnCurReqPdnType();\
            }\
        }

#define IMSA_CONN_GetConnSelectedCid(enConnType, ucCid)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                (ucCid) = IMSA_CONN_GetNormalConnSelSdfParaAddr()->ucCid;\
            }\
            else\
            {\
                (ucCid) = IMSA_CONN_GetEmcConnSelSdfParaAddr()->ucCid;\
            }\
        }

#define IMSA_CONN_SetOpid(enConnType, ucOpid)\
        {\
            if (IMSA_CONN_TYPE_NORMAL == (enConnType))\
            {\
                IMSA_CONN_SetNormalConnOpid((ucOpid));\
            }\
            else\
            {\
                IMSA_CONN_SetEmcConnOpid((ucOpid));\
            }\
        }

/* Controlģ����غ� */
#define IMSA_GetControlManagerAddress()     (&pgstImsaEntity->stImsaControlManager)
#define IMSA_GetIntraMsgQueueAddress()      (&pgstImsaEntity->stImsaControlManager.stImsaIntraMsgQueue)
#define IMSA_GetCommonInfoAddress()         (&pgstImsaEntity->stImsaControlManager.stImsaCommonInfo)
#define IMSA_GetNetInfoAddress()            (&pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo)
#define IMSA_SRV_GetNormalSrvStatus()       (pgstImsaEntity->stImsaControlManager.enNrmSrvStatus)
#define IMSA_SRV_GetEmcSrvStatus()          (pgstImsaEntity->stImsaControlManager.enEmcSrvStatus)
#define IMSA_GetConfigParaAddress()         (&pgstImsaEntity->stImsaControlManager.stImsaConfigPara)
#define IMSA_GetCampedRat()                 (pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo.enImsaCampedRatType)
#define IMSA_GetVoiceDomain()               (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.enVoiceDomain)
#define IMSA_GetUeImsVoiceCap()             (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.ucVoiceCallOnImsSupportFlag)
#define IMSA_GetUeImsVideoCap()             (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.ucVideoCallOnImsSupportFlag)
#define IMSA_GetUeImsSmsCap()               (pgstImsaEntity->stImsaControlManager.stImsaConfigPara.ucSmsOnImsSupportFlag)
#define IMSA_GetNwImsVoiceCap()             (pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo.enImsaImsVoPsStatus)
#define IMSA_GetPsServiceStatus()           (pgstImsaEntity->stImsaControlManager.stImsaNetworkInfo.enImsaPsServiceStatus)
#define IMSA_GetIsimStatus()                (pgstImsaEntity->stImsaControlManager.enImsaIsimStatus)
#define IMSA_SetDeregCause(enDeregCause)    (pgstImsaEntity->stImsaControlManager.enDeregCause = (enDeregCause))
#define IMSA_GetDeregCause()                (pgstImsaEntity->stImsaControlManager.enDeregCause)
#define IMSA_GetAtControlAddress()          (&pgstImsaEntity->stImsaControlManager.stAtControl)
#define IMSA_GetSrvccBuffAddress()          (&pgstImsaEntity->stImsaControlManager.stSrvccBuffer)
#define IMSA_GetImsRedialCfgAddress()       (&pgstImsaEntity->stImsaControlManager.stImsaConfigPara.stImsRedialCfg)

#define IMSA_GetPowerState()                (pgstImsaEntity->stImsaControlManager.enPowerState)

#define IMSA_SetUsimNormOpid(ucOpid)        (pgstImsaEntity->stImsaRegManager.stNormalRegEntity.ucImsaUsimNormOpid = (ucOpid))
#define IMSA_GetUsimNormOpid()              (pgstImsaEntity->stImsaRegManager.stNormalRegEntity.ucImsaUsimNormOpid)
/* ��OPID�ĵڰ�λ���ֵ�ǰ�ǽ�����Ȩ������ͨ��Ȩ */
#define IMSA_SetUsimEmcOpid(ucOpid)         (pgstImsaEntity->stImsaRegManager.stEmcRegEntity.ucImsaUsimEmcOpid = (ucOpid | 0x80))
#define IMSA_GetUsimEmcOpid()               (pgstImsaEntity->stImsaRegManager.stEmcRegEntity.ucImsaUsimEmcOpid)


#define IMSA_SRV_SndCallSrvStatusInd(enSrvType, enCallSrvStatus,enNoSrvCause)\
    {\
        if (IMSA_SRV_TYPE_NORMAL == (enSrvType))\
        {\
            IMSA_SRV_SndNrmCallSrvStatusInd((enCallSrvStatus),(enNoSrvCause));\
        }\
        else\
        {\
            IMSA_SRV_SndEmcCallSrvStatusInd((enCallSrvStatus),(enNoSrvCause));\
        }\
    }

#define IMSA_SMS_GetSmrMoEntityAddress()    (&pgstImsaEntity->stImsaSmsManager.stImsaSmrMo)
#define IMSA_SMS_GetSmrMtEntityAddress()    (&pgstImsaEntity->stImsaSmsManager.stImsaSmrMt)

#define IMSA_USSD_GetEntityAddress()        (&pgstImsaEntity->stImsaUssdManager)


/* error log ������Ϣ */
#if (FEATURE_ON == FEATURE_PTM)
#define IMSA_GetErrorlogManagerAddress()        (&pgstImsaEntity->stImsaErrorlogManager)
#define IMSA_GetErrorLogRingBufAddr()           (pgstImsaEntity->stImsaErrorlogManager.stBuffInfo.pstRingBuffer)
#define IMSA_GetErrlogOverflowCnt()             (pgstImsaEntity->stImsaErrorlogManager.stBuffInfo.ulOverflowCnt)
#define IMSA_GetErrlogCtrlFlag()                (pgstImsaEntity->stImsaErrorlogManager.stCtrlInfo.ucErrLogCtrlFlag)
#define IMSA_GetErrlogAlmLevel()                (pgstImsaEntity->stImsaErrorlogManager.stCtrlInfo.usAlmLevel)

#define IMSA_SetErrorLogRingBufAddr(pRingBuffer)        (IMSA_GetErrorLogRingBufAddr() = pRingBuffer)
#define IMSA_SetErrlogOverflowCnt(ulOverflowCnt)        (IMSA_GetErrlogOverflowCnt() = ulOverflowCnt)
#define IMSA_SetErrlogCtrlFlag(ucFlag)                  (IMSA_GetErrlogCtrlFlag() = ucFlag)
#define IMSA_SetErrlogAlmLevel(usAlmLevel)              (IMSA_GetErrlogAlmLevel() = usAlmLevel)
#endif

/* zhaochen 00308719 begin for HIFI mailbox full reset 2015-11-09 */
/* HIFI������Ϣ������Ϣ */
#define IMSA_GetHifiDataManagerAddress()        (&pgstImsaEntity->stImsaHifiDataManager)
#define IMSA_GetHifiDataBufferDataHead()        (pgstImsaEntity->stImsaHifiDataManager.pstBufferDataHead)
#define IMSA_GetHifiDataBufferDataTail()        (pgstImsaEntity->stImsaHifiDataManager.pstBufferDataTail)
#define IMSA_GetHifiDataBufferDataNum()         (pgstImsaEntity->stImsaHifiDataManager.ucBufferDataNum)
#define IMSA_GetHifiDataSentDataNum()           (pgstImsaEntity->stImsaHifiDataManager.ucSentDataNum)
#define IMSA_GetHifiDataOpid()                  (pgstImsaEntity->stImsaHifiDataManager.ulOpid)
#define IMSA_GetHifiDataAckProtectTimer()       (pgstImsaEntity->stImsaHifiDataManager.stHifiAckProtectTimer)
#define IMSA_GetHifiDataControlFlag()           (pgstImsaEntity->stImsaHifiDataManager.ucHifiDataControlFlag)
#define IMSA_GetHifiDataNeedAckNum()            (pgstImsaEntity->stImsaHifiDataManager.ucHifiDataNeedAckNum)
#define IMSA_GetHifiDataMaxBufferNum()          (pgstImsaEntity->stImsaHifiDataManager.ucHifiDatMaxBufferNum)
#define IMSA_GetHifiDataDataLoseNum()           (pgstImsaEntity->stImsaHifiDataManager.ulDataLoseNum)
#define IMSA_GetHifiDataTotalDataLoseNum()      (pgstImsaEntity->stImsaHifiDataManager.ulTotalDataLoseNum)
#define IMSA_GetHifiDataDataBufferNum()         (pgstImsaEntity->stImsaHifiDataManager.ulDataBufferNum)
#define IMSA_GetHifiDataTotalDataBufferNum()    (pgstImsaEntity->stImsaHifiDataManager.ulTotalDataBufferNum)
/* zhaochen 00308719 end for HIFI mailbox full reset 2015-11-09 */
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

#endif /* end of ImsaEntity.h */




