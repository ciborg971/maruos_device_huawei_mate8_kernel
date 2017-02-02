

#ifndef __NAS_MSCC_CTX_H__
#define __NAS_MSCC_CTX_H__

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "NasMsccTimerMgmt.h"
#include "NasMsccPifInterface.h"
#include "NasCommDef.h"
#include "VosPidDef.h"
#include "NasFsm.h"
#include "MsccMmcInterface.h"
#include "hsd_mscc_pif.h"
#include "MsccMmcInterface.h"
#include "NasMsccMlplMsplParse.h"

#include "ImsaMsccInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define NAS_MSCC_MAX_MSG_BUFFER_LEN                         (1600)    /* Maximum number of bytes for message buffer */

#define NAS_MSCC_MAX_MODULE_NUM                             (4)       /* Maximum number of modules that can be started*/

#define NAS_MSCC_MAX_FSM_STACK_DEPTH                        (4)       /* Maximum stack depth of the MSCC module */

#define NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM                    (8)       /* Maximum number of the Cache messages */

#define NAS_MSCC_MAX_INT_MSG_QUEUE_NUM                      (8)       /* Maximum number of internal messages */

#define NAS_MSCC_PLATFORM_MAX_RAT_NUM                       (7)       /* Maximum number of RATs supported */

#define NAS_MSCC_INVALID_MCC                                (0xFFFFFFFF) /* Used in the assignment of default MCC value */

#define NAS_MSCC_INVALID_MNC                                (0xFFFFFFFF) /* Used in the assignment of default MNC value */

#define NAS_MSCC_INVALID_RAC                                (0xFF)    /* Used in the assignment of default RAC value */

#define NAS_MSCC_INVALID_CELL_ID                            (0xFFFFFFFF) /* Used in the assignment of default Cell ID value */

#define NAS_MSCC_INVALID_LAC                                (0xFFFF)  /* Used in the assignment of default LAC value */

#define NAS_MSCC_SIM_RAT_E_UTRN                             (0x4000)

#define NAS_MSCC_BYTES_IN_SUBNET                            (16)

#define NAS_MSCC_WILDCARD_SID                               (0)

#define NAS_MSCC_WILDCARD_NID                               (65535)


#define NAS_MSCC_MAX_IMSI_LENGTH                            (9)

#define NAS_MSCC_SIM_FORMAT_PLMN_LEN                        (3)     /* Sim����ʽ��Plmn���� */

#define NAS_MSCC_BYTE_MASK                                  (0xFF)
#define NAS_MSCC_MAX_DIGIT_VALUE                            (9)
#define NAS_MSCC_LOW_BYTE_INVALID                           (0x0F)
#define NAS_MSCC_OCTET_LOW_FOUR_BITS                        (0x0f)  /* ��ȡһ���ֽ��еĵ�4λ */
#define NAS_MSCC_OCTET_HIGH_FOUR_BITS                       (0xf0)  /* ��ȡһ���ֽ��еĸ�4λ */
#define NAS_MSCC_OCTET_MOVE_FOUR_BITS                       (0x04)  /* ��һ���ֽ��ƶ�4λ */
#define NAS_MSCC_OCTET_MOVE_SIXTEEN_BITS                    (0x10)  /* ��һ���ֽ��ƶ�16λ */
#define NAS_MSCC_OCTET_MOVE_EIGHT_BITS                      (0x08)  /* ��һ���ֽ��ƶ�8λ */

#define NAS_MSCC_MAX_SYS_NUM_IN_ACQUIRE_LIST                (8)

#define NAS_MSCC_SYSCFG_MAX_MODULE_NUM                      (3)       /* Maximum number of mudules in system config request */



/* ��װOSA������Ϣ�ӿ� */
#define NAS_MSCC_ALLOC_MSG_WITH_HDR(ulMsgLen)\
            PS_ALLOC_MSG_WITH_HEADER_LEN(UEPS_PID_MSCC, (ulMsgLen))

/* ��װOSA��Ϣͷ */
#define NAS_MSCC_CFG_MSG_HDR(pstMsg, ulRecvPid, ulMsgId)\
           { \
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderCpuId   = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulSenderPid     = UEPS_PID_MSCC;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverCpuId = VOS_LOCAL_CPUID;\
            ((MSG_HEADER_STRU *)(pstMsg))->ulReceiverPid   = (ulRecvPid);\
            ((MSG_HEADER_STRU *)(pstMsg))->ulMsgName       = (ulMsgId); \
           }

/* ��װOSA��Ϣͷ(MSCC�ڲ���Ϣ) */
#define NAS_MSCC_CFG_INTRA_MSG_HDR(pstMsg, ulMsgId)\
            NAS_MSCC_CFG_MSG_HDR(pstMsg, UEPS_PID_MSCC, ulMsgId)

/* ��ȡOSA��Ϣ���� */
#define NAS_MSCC_GET_MSG_ENTITY(pstMsg)\
            ((VOS_VOID *)&(((MSG_HEADER_STRU *)(pstMsg))->ulMsgName))

/* ��ȡOSA��Ϣ���� */
#define NAS_MSCC_GET_MSG_LENGTH(pstMsg)\
            (((MSG_HEADER_STRU *)(pstMsg))->ulLength)

/* ��װOSA��Ϣ��ʼ����Ϣ���ݽӿ� */
#define NAS_MSCC_CLR_MSG_ENTITY(pstMsg)\
            PS_MEM_SET(NAS_MSCC_GET_MSG_ENTITY(pstMsg), 0x0, NAS_MSCC_GET_MSG_LENGTH(pstMsg))

/* ��װOSA������Ϣ�ӿ� */
#define NAS_MSCC_SEND_MSG(pstMsg)\
            PS_SEND_MSG(UEPS_PID_MSCC, pstMsg)

/* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
#define NAS_MSCC_MAX_LOG_MSG_STATE_NUM                      (100)
/* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/
/*****************************************************************************
 ö����    : NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8
 �ṹ˵��  : IMS voice capability
 1.��    ��   : 2015��1��26��
   ��    ��   : y0024524
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_NW_IMS_VOICE_CAP_ENUM
{
    NAS_MSCC_NW_IMS_VOICE_NOT_SUPPORTED    = 0,
    NAS_MSCC_NW_IMS_VOICE_SUPPORTED        = 1,

    NAS_MSCC_NW_IMS_VOICE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8;


enum NAS_MSCC_NW_EMC_BS_CAP_ENUM
{
    NAS_MSCC_NW_EMC_BS_NOT_SUPPORTED       = 0,
    NAS_MSCC_NW_EMC_BS_SUPPORTED           = 1,

    NAS_MSCC_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8;


enum NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM
{
    NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST = 0,
    NAS_MSCC_PERSISTENT_BEARER_STATE_EXIST     = 1,
    NAS_MSCC_PERSISTENT_BEARER_STATE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8;



enum NAS_MSCC_LTE_CS_CAPBILITY_ENUM
{
    NAS_MSCC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    NAS_MSCC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    NAS_MSCC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    NAS_MSCC_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    NAS_MSCC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 NAS_MSCC_LTE_CS_CAPBILITY_ENUM_UINT8;


enum NAS_MSCC_SYS_MODE_ENUM
{
    NAS_MSCC_SYS_MODE_GSM,
    NAS_MSCC_SYS_MODE_WCDMA,
    NAS_MSCC_SYS_MODE_LTE,

    NAS_MSCC_SYS_MODE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_SYS_MODE_ENUM_UINT8;



enum NAS_MSCC_SYS_SUBMODE_ENUM
{
    NAS_MSCC_SYS_SUBMODE_NONE                = 0,                                /* �޷��� */
    NAS_MSCC_SYS_SUBMODE_GSM                 = 1,                                /* GSMģʽ */
    NAS_MSCC_SYS_SUBMODE_GPRS                = 2,                                /* GPRSģʽ */
    NAS_MSCC_SYS_SUBMODE_EDGE                = 3,                                /* EDGEģʽ */
    NAS_MSCC_SYS_SUBMODE_WCDMA               = 4,                                /* WCDMAģʽ */
    NAS_MSCC_SYS_SUBMODE_HSDPA               = 5,                                /* HSDPAģʽ */
    NAS_MSCC_SYS_SUBMODE_HSUPA               = 6,                                /* HSUPAģʽ */
    NAS_MSCC_SYS_SUBMODE_HSDPA_HSUPA         = 7,                                /* HSDPA+HSUPAģʽ */
    NAS_MSCC_SYS_SUBMODE_TD_SCDMA            = 8,                                /* TD_SCDMAģʽ */
    NAS_MSCC_SYS_SUBMODE_HSPA_PLUS           = 9,                                /* HSPA+ģʽ */
    NAS_MSCC_SYS_SUBMODE_LTE                 = 10,                               /* LTEģʽ */
    NAS_MSCC_SYS_SUBMODE_DC_HSPA_PLUS        = 17,                               /* DC-HSPA+ģʽ */
    NAS_MSCC_SYS_SUBMODE_DC_MIMO             = 18,                               /* MIMO-HSPA+ģʽ */

    NAS_MSCC_SYS_SUBMODE_CDMA_1X             = 23,                               /* CDMA2000 1X*/
    NAS_MSCC_SYS_SUBMODE_BUTT
};
typedef VOS_UINT8  NAS_MSCC_SYS_SUBMODE_ENUM_UINT8;


enum NAS_MSCC_LMM_ACCESS_TYPE_ENUM
{
    NAS_MSCC_LMM_ACCESS_TYPE_EUTRAN_TDD      = 0,
    NAS_MSCC_LMM_ACCESS_TYPE_EUTRAN_FDD      = 1,

    NAS_MSCC_LMM_ACCESS_TYPE_BUTT
};
typedef VOS_UINT8 NAS_MSCC_LMM_ACCESS_TYPE_ENUM_UINT8;


enum NAS_MSCC_SERVICE_STATUS_ENUM
{
    NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE           = 0,                        /* �������� */
    NAS_MSCC_SERVICE_STATUS_LIMITED_SERVICE          = 1,                        /* ���Ʒ��� */
    NAS_MSCC_SERVICE_STATUS_NO_SERVICE               = 2,                        /* �޷��� */

    NAS_MSCC_SERVICE_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_SERVICE_STATUS_ENUM_UINT8;
enum NAS_MSCC_VOICE_DOMAIN_ENUM
{
    NAS_MSCC_VOICE_DOMAIN_CS_ONLY            = 0,                                /**< CS voice only */
    NAS_MSCC_VOICE_DOMAIN_IMS_PS_ONLY        = 1,                                /**< IMS PS voice only */
    NAS_MSCC_VOICE_DOMAIN_CS_PREFERRED       = 2,                                /**< CS voice preferred, IMS PS Voice as secondary */
    NAS_MSCC_VOICE_DOMAIN_IMS_PS_PREFERRED   = 3,                                /**< IMS PS voice preferred, CS Voice as secondary */

    NAS_MSCC_VOICE_DOMAIN_BUTT
};
typedef VOS_UINT32 NAS_MSCC_VOICE_DOMAIN_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_SYS_ACQ_SCENE_ENUM
 ö��˵��  : ����ϵͳ���񳡾��Ķ���
 1.��    ��   : 2015��04��03��
   ��    ��   : m00312079
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_SYS_ACQ_SCENE_ENUM
{
    NAS_MSCC_SYS_ACQ_SCENE_SWITCH_ON                 = 0,/* ���� */
    NAS_MSCC_SYS_ACQ_SCENE_AVAILABLE_TIMER_EXPIRED,      /* available��ʱ����ʱ*/
    NAS_MSCC_SYS_ACQ_SCENE_HRPD_LOST,                    /* hrpd ���� */
    NAS_MSCC_SYS_ACQ_SCENE_LTE_LOST,                     /* lte  ���� */
    NAS_MSCC_SYS_ACQ_SCENE_SLEEP_TIMER_EXPIRED,          /* sleep ��ʱ����ʱ */
    NAS_MSCC_SYS_ACQ_SCENE_SYS_CFG_SET,                  /* system configure���ô������� */
    NAS_MSCC_SYS_ACQ_SCENE_LTE_RF_AVAILABLE,             /* LTE RF��Դ���� */
    NAS_MSCC_SYS_ACQ_SCENE_HRPD_RF_AVAILABLE,            /* HRPD RF��Դ���� */
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, begin */
    NAS_MSCC_SYS_ACQ_SCENE_MO_TRIGGER,                   /* ���д��� */
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-16, end */

    NAS_MSCC_SYS_ACQ_SCENE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_SYS_ACQ_SCENE_ENUM_UINT32;

/*****************************************************************************
 ö����    : NAS_MSCC_PRIOR_SYS_ENUM
 ö��˵��  : CLģʽ��ϵͳ���ȼ�
 1.��    ��   : 2015��04��03��
   ��    ��   : m00312079
   �޸�����   : �½�
*****************************************************************************/
enum NAS_MSCC_PRIOR_SYS_ENUM
{
    NAS_MSCC_LTE_PRIOR                      = 0,  /* LTE���� */
    NAS_MSCC_HRPD_PRIOR                     = 1,  /* HRPD���� */

    NAS_MSCC_PRIOR_SYS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_PRIOR_SYS_ENUM_UINT8;


enum NAS_MSCC_FSM_ID_ENUM
{
    /* L1 Main FSM. This is the default FSM of the MSCC module */
    NAS_MSCC_FSM_L1_MAIN                                    =0x00,

    /* Switch ON FSM that is responsible for Start Process */
    NAS_MSCC_FSM_SWITCH_ON                                  =0x01,

    /* Power OFF FSM that is responsible for Start Process */
    NAS_MSCC_FSM_POWER_OFF                                  =0x02,

    /* Added by y00307564 for CDMA Iteration 10 2015-4-2 begin */
    /* system acquire state machine */
    NAS_MSCC_FSM_SYS_ACQ                                    =0x03,

    /* better system reselection(BSR) FSM that is responsible for Start Process */
    NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION                  =0x04,
    /* Added by y00307564 for CDMA Iteration 10 2015-4-2 end */

    /* system config FSM which deals with system config process in MSCC */
    NAS_MSCC_FSM_SYSTEM_CONFIG                              =0X05,

    /* Invalid FSM ID */
    NAS_MSCC_BUTT
};
typedef VOS_UINT32 NAS_MSCC_FSM_ID_ENUM_UINT32;
enum NAS_MSCC_LC_RAT_COMBINED_ENUM
{
    NAS_MSCC_LC_RAT_COMBINED_GUL,
    NAS_MSCC_LC_RAT_COMBINED_CL,

    NAS_MSCC_LC_RAT_COMBINED_BUTT
};
typedef VOS_UINT8 NAS_MSCC_LC_RAT_COMBINED_ENUM_UINT8;


enum NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM
{
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_INVALID,                  /* initial acquire location info is invalid */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_NO_SEARCH_MLPL,           /* initial acquire location info is valid but not used to search mlpl */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_FAIL,         /* initial acquire location info is valid but search mlpl failed */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_LTE_PRIO,     /* initial acquire location info is valid and search mlpl result is lte prio */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_SEARCH_MLPL_HRPD_PRIO,    /* initial acquire location info is valid and search mlpl result is hrpd prio */

    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8;
enum NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM
{
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_NULL                    = 0x00,
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MLPL                    = 0x01,
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_MSPL                    = 0x02,

    NAS_MSCC_WAIT_CARD_READ_CNF_FLG_BUTT
};
typedef VOS_UINT32 NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32;


enum NAS_MSCC_MLPL_MSPL_SOURCE_ENUM
{
    NAS_MSCC_MLPL_MSPL_SOURCE_NULL,
    NAS_MSCC_MLPL_MSPL_SOURCE_CARD,
    NAS_MSCC_MLPL_MSPL_SOURCE_NV,
    NAS_MSCC_MLPL_MSPL_SOURCE_DEFAULT,

    NAS_MSCC_MLPL_MSPL_SOURCE_BUTT
};
typedef VOS_UINT32 NAS_MSCC_MLPL_MSPL_SOURCE_ENUM_UINT32;


enum NAS_MSCC_SYS_PRIORITY_CLASS_ENUM
{
    NAS_MSCC_SYS_PRI_CLASS_HOME             = 0,    /* home or ehome plmn */
    NAS_MSCC_SYS_PRI_CLASS_PREF             = 1,    /* UPLMN or OPLMN */
    NAS_MSCC_SYS_PRI_CLASS_ANY              = 2,    /* Acceptable PLMN */
    NAS_MSCC_SYS_PRI_CLASS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8;

/* Added by y00307564 for CDMA Iteration 10 2015-4-11 begin */

enum NAS_MSCC_SYS_ACQ_STATUS_ENUM
{
    NAS_MSCC_SYS_ACQ_STATUS_NO_SEARCHED,                    /* the system is no searched */

    NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_REGISTERED,            /* the system is searched success and register succ */

    NAS_MSCC_SYS_ACQ_STATUS_SEARCHED_NO_EXIST,              /* the system is searched fail and no coveraged in this area */

    NAS_MSCC_SYS_ACQ_STATUS_BUTT
};
typedef VOS_UINT8 NAS_MSCC_SYS_ACQ_STATUS_ENUM_UINT8;

/* Added by y00307564 for CDMA Iteration 10 2015-4-11 end */


enum NAS_MSCC_INIT_CTX_TYPE_ENUM
{
    NAS_MSCC_INIT_CTX_STARTUP                               = 0,
    NAS_MSCC_INIT_CTX_POWEROFF                              = 1,
    NAS_MSCC_INIT_CTX_BUTT
};
typedef VOS_UINT8 NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8;



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

typedef struct
{
    VOS_UINT8                           ucGsmImsSupportFlag;    /**< GSM IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUtranImsSupportFlag;  /**< UNTRAN IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteImsSupportFlag;    /**< LTE IMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucGsmEmsSupportFlag;    /**< GSM EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucUtranEmsSupportFlag;  /**< UNTRAN EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           ucLteEmsSupportFlag;    /**< LTE EMSʹ����,VOS_TRUE :֧�֣�VOS_FALSE :��֧�� */
    VOS_UINT8                           aucReserved[2];
}NAS_MSCC_IMS_RAT_SUPPORT_STRU;


typedef struct
{
    NAS_MSCC_IMS_RAT_SUPPORT_STRU       stImsRatSupport;                        /* different RAT IMS support */
    NAS_MSCC_VOICE_DOMAIN_ENUM_UINT32   enVoiceDomain;
    VOS_UINT32                          ulWaitImsVoiceAvailTimerLen;            /* �ȴ�IMS VOICE ���õĶ�ʱ��ʱ�� */
}NAS_MSCC_IMS_CONFIG_PARA_STRU;


typedef struct
{
    NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8                    enNwImsVoCap;
    NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8                       enNwEmcBsCap;
    NAS_MSCC_LTE_CS_CAPBILITY_ENUM_UINT8                    enLteCsCap;
    VOS_UINT8                                               aucReserved[1];
}NAS_MSCC_NETWORK_CAP_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucCampOnFlg;
    NAS_MSCC_SYS_MODE_ENUM_UINT8        enSysMode;
    NAS_MSCC_LMM_ACCESS_TYPE_ENUM_UINT8 enLmmAccessType;
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enPrioClass;                    /* ��ǰϵͳ��Ӧ��prio class,Ŀǰֻ��CLģʽ����Ч��GUL��LTE�»ḳֵ,����ģʽ���Ժ��� */

    VOS_UINT32                          ulCellId;
    NAS_MSCC_PIF_PLMN_ID_STRU           stPlmnId;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucRoamFlag;                     /* ��ǰפ�������Ƿ����� VOS_TRUE:�������� VOS_FALSE:���������� */
}NAS_MSCC_3GPP_SYS_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucCampOnFlg;
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   en1xPrioClass;  /* sys_typeΪCDMA2000_1Xʱ��PRI class */
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enAIPrioClass;  /* sys_typeΪCDMA2000_AIʱ��PRI class */
    VOS_UINT8                           aucRsv[1];
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;
    VOS_UINT32                          ulMcc;  /* NAS��ʽ��MCC������461: 0x00010604 */
    VOS_UINT32                          ulMnc;  /* NAS��ʽ��MNC������03 : 0x000f0300 */
}NAS_MSCC_1X_SYS_INFO_STRU;


typedef struct
{
    VOS_UINT8                           ucCampOnFlg;
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enHrpdPrioClass;  /* sys_typeΪCDMA2000_HRPDʱ��PRI class */
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enAIPrioClass;    /* sys_typeΪCDMA2000_AIʱ��PRI class */
    VOS_UINT8                           ucSubNetMask;
    VOS_UINT32                          ulMcc;  /* NAS��ʽ��MCC������461: 0x00010604 */
    VOS_UINT8                           aucSectorId[NAS_MSCC_BYTES_IN_SUBNET];
}NAS_MSCC_HRPD_SYS_INFO_STRU;
typedef struct
{
    NAS_MSCC_1X_SYS_INFO_STRU           st1xSysInfo;
    NAS_MSCC_HRPD_SYS_INFO_STRU         stHrpdSysInfo;
}NAS_MSCC_3GPP2_SYS_INFO_STRU;


typedef struct
{
    NAS_MSCC_3GPP_SYS_INFO_STRU         st3gppSysInfo;      /* 3gpp��ǰפ��PLMN��Ϣ */
    NAS_MSCC_3GPP2_SYS_INFO_STRU        st3gpp2SysInfo;     /* 3gpp2��ǰפ��PLMN��Ϣ */
}NAS_MSCC_SYS_INFO_STRU;


typedef struct
{
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU   stEhPlmnInfo;                          /* EHPLMN�б���Ϣ */
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU stUserPlmnInfo;                        /* UPLMN�б���Ϣ */
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU stOperPlmnInfo;                        /* OPLMN�б���Ϣ */
}NAS_MSCC_SIM_PLMN_INFO_STRU;
typedef struct
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimStatus;
    VOS_UINT8                           ucSimCsRegStatus;    /* SIM��CS���ע�������µĿ��Ƿ���ЧVOS_TRUE:CS��Ŀ���Ч,VOS_FALSE:CS��Ŀ���Ч*/
    VOS_UINT8                           ucSimPsRegStatus;    /* SIM��PS���ע�������µĿ��Ƿ���ЧVOS_TRUE:PS��Ŀ���Ч,VOS_FALSE:PS��Ŀ���Ч*/
}NAS_MSCC_SIM_STATUS_STRU;


typedef struct
{
    NAS_MSCC_SIM_STATUS_STRU            stSimStatus;                            /* SIM��״̬ */
    NAS_MSCC_SIM_PLMN_INFO_STRU         stSimPlmnInfo;                          /* SIM���б����PLMN��Ϣ */
    VOS_UINT8                           ucIsCardChanged;                        /* SIM���Ƿ����ı� */
    VOS_UINT8                           aucReserved[3];                         /* ����λ */
}NAS_MSCC_SIM_INFO_STRU;


typedef struct
{
    VOS_UINT8                           uc1xActiveFlg;                 /* power save cnf, we consider this mode is deactived,while acquire
                                                                           system in this mode,we consider this mode is actived */
    VOS_UINT8                           ucHrpdActiveFlg;
    VOS_UINT8                           uc3gppActiveFlg;                /* in CL system acqruie flow, we only power save LTE, but for syscfg procedure,
                                                                           we maybe power save GSM or UTRAN or LTE, so this flag indicate the current
                                                                           active mode in 3GPP active or deacitve */
    VOS_UINT8                           ucPowerSaveReplyFlg;            /* VOS_TRUE:  need reply power save result to upplayer
                                                                           VOS_FALSE: need not reply power save result to upplayer */
}NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU;


typedef struct
{
    VOS_UINT16      usNum;                                                      /* Number of RATs supported */
    VOS_UINT16      usIndex;                                                    /* Current index of the Request sequence */
    VOS_UINT32      aulModuleID[NAS_MSCC_SYSCFG_MAX_MODULE_NUM];                /* List of Module IDs  */
}NAS_MSCC_PREF_ORDER_MODULE_LIST;
typedef struct
{
    VOS_UINT32                          ulCurrBsrTimerLen;         /* ��¼�������е�BSR Timer���� */
    VOS_RATMODE_ENUM_UINT32             enOrigBsrTimerStartRat;    /* ��¼�ϴ�����BSR Timer��ʱ����פ����ʽ */
    VOS_UINT8                           ucDataSrvSwitchTo1xFlg;    /* ����ҵ���л���1X�ϱ�� */
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU;

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, begin */
/****************************************************************************
Structure name  :   NAS_MSCC_SYS_ACQ_CALL_CTRL_CTX_STRU
Description     :   Structure definition the System Acquire and call CTRL context info.
Modify History:
    1)  Date    :   2015-07-09
        Author  :   y00314741
        Modify content :    Create

****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucSysAcqMoCallFlag;    /* ����ҵ���л���1X�ϱ�� */
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_SYS_ACQ_CALL_CTRL_CTX_STRU;
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, end */


typedef struct
{
    NAS_MSCC_PREF_ORDER_MODULE_LIST                         stSysCfgModuleOrder;
    NAS_MSCC_PREF_ORDER_MODULE_LIST                         stPowerSaveModuleOrder;
}NAS_MSCC_FSM_SYSCFG_CTX_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_SERVICE_STATUS_INFO_STRU
Description     :   Structure definition the service info for MSCC.
Modify History:
    1)  Date    :   2015-04-07
        Author  :   t00323010
        Modify content :    Create for Iteration 10
****************************************************************************/
typedef struct
{
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  en1xServiceStatus;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdServiceStatus;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  en3gppPsServiceStatus;
    VOS_UINT8                           aucRsv[1];
}NAS_MSCC_SERVICE_STATUS_INFO_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_CONN_STATUS_INFO_STRU
Description     :   Structure definition the connection status info for MSCC.
Modify History:
    1)  Date    :   2015-04-07
        Author  :   t00323010
        Modify content :    Create for Iteration 10
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHrpdConnExistFlg;
    VOS_UINT8                           ucLteEpsConnExistFlg;
    VOS_UINT8                           aucRsv[2];
}NAS_MSCC_CONN_STATUS_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;  /* NAS��ʽ��MCC������461: 0x00010604 */
    VOS_UINT32                          ulMnc;  /* NAS��ʽ��MNC������03 : 0x000f0300 */
    VOS_UINT16                          usSid;
    VOS_UINT16                          usNid;

    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   en1xPrioClass;  /* sys_typeΪCDMA2000_1Xʱ��PRI class */
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enAIPrioClass;  /* sys_typeΪCDMA2000_AIʱ��PRI class */
    VOS_UINT8                           aucRsv[2];
}NAS_MSCC_1X_LOC_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulMcc;
    VOS_UINT32                          ulMnc;
    NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8   enPrioClass;                    /* ��ǰϵͳ��Ӧ��prio class,Ŀǰֻ��CLģʽ����Ч��GUL��LTE�»ḳֵ,����ģʽ���Ժ��� */
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_LTE_LOC_INFO_STRU;
typedef struct
{
    VOS_UINT8                           ucIsLocInfoUsedInSwitchOn;
    NAS_MSCC_LC_RAT_COMBINED_ENUM_UINT8 enSysAcqMode;
    VOS_UINT8                           ucCdma1xActiveFlag;
    VOS_UINT8                           ucLteActiveFlag;
    NAS_MSCC_1X_LOC_INFO_STRU           st1xLocationInfo;
    NAS_MSCC_LTE_LOC_INFO_STRU          stLteLocationInfo;
}NAS_MSCC_MMSS_LOCATION_INFO_STRU;

typedef struct
{
    NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8             enPersistentBearerState;
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8                      enImsVoiceCap;
    VOS_UINT8                                               ucReserved[2];
}NAS_MSCC_IMS_DOMAIN_INFO_STRU;


typedef struct
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU                          stLteNwCapInfo;
    NAS_MSCC_NETWORK_CAP_INFO_STRU                          stGuNwCapInfo;
    NAS_MSCC_SYS_INFO_STRU                                  stSysInfo;
    NAS_MSCC_SERVICE_STATUS_INFO_STRU                       stServiceStatusInfo;
    NAS_MSCC_CONN_STATUS_INFO_STRU                          stConnStatusInfo;
    NAS_MSCC_IMS_DOMAIN_INFO_STRU                           stImsDomainInfo;
}NAS_MSCC_NW_INFO_STRU;


typedef struct
{
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           aucMsgBuffer[NAS_MSCC_MAX_MSG_BUFFER_LEN];
}NAS_MSCC_MSG_STRU;


typedef struct
{
    VOS_UINT32                                              ulWaitCardReadFlag;
}NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU;


typedef struct
{
    VOS_UINT16                                              usNum;  /* Number of RATs supported */
    VOS_UINT16                                              usIndex;    /* Current index of the Request sequence */
    VOS_UINT32                                              aulModuleID[NAS_MSCC_MAX_MODULE_NUM];   /* List of Module IDs  */

    NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU              stCardReadInfo;
}NAS_MSCC_FSM_SWITCH_ON_CTX_STRU;
typedef struct
{
    VOS_UINT16      usNum;                                                      /* Number of RATs supported */
    VOS_UINT16      usIndex;                                                    /* Current index of the Request sequence */
    VOS_UINT32      aulModuleID[NAS_MSCC_MAX_MODULE_NUM];                       /* List of Module IDs  */
}NAS_MSCC_FSM_POWER_OFF_CTX_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_SYS_ACQ_1X_INIT_LOC_STA_STRU
Description     :   Structure definition 1x intial location info
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucAcqFinishFlg;             /* initial acq finished flag VOS_TRUE:finish;VOS_FALSE:not finish */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enLocInfoStatus;            /* initial acquire location info status */
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_1X_LOC_INFO_STRU                               st1xLocInfo;
}NAS_MSCC_SYS_ACQ_1X_INIT_LOC_STA_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_LTE_LOCATION_INFO_STRU
Description     :   Structure definition LTE initial location info
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucAcqFinishFlg;             /* initial acq finished flag VOS_TRUE:finish;VOS_FALSE:not finish */
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enLocInfoStatus;            /* initial acquire location info status */
    VOS_UINT8                                               aucReserve[2];
    NAS_MSCC_LTE_LOC_INFO_STRU                              stLteLocInfo;
}NAS_MSCC_SYS_ACQ_LTE_INIT_LOC_STA_STRU;



typedef struct
{
    VOS_RATMODE_ENUM_UINT32             ulRatMode;
    NAS_MSCC_SYS_ACQ_STATUS_ENUM_UINT8  enAcqStatus;
    VOS_UINT8                           aucRsv[3];
}NAS_MSCC_SYS_ACQ_SYS_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucInitialAcqSysNum;                 /* initial acquire system num */
    VOS_UINT8                           ucNormalAcqSysNum;                  /* normal acquire system num */
    VOS_UINT8                           aucRsv[2];
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU      astInitialAcqSysList[NAS_MSCC_MAX_SYS_NUM_IN_ACQUIRE_LIST];
    NAS_MSCC_SYS_ACQ_SYS_INFO_STRU      astNormalAcqSysList[NAS_MSCC_MAX_SYS_NUM_IN_ACQUIRE_LIST];
}NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_FSM_SYS_ACQ_CTX_STRU
Description     :   Structure definition system acquire fsm ctx info
Modify History:
    1)  Date    :   2015-04-03
        Author  :   m00312079
        Modify content :    Create
****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucNeedReAcqLteFlg;
    VOS_UINT8                                               ucAbortFlg;
    VOS_UINT8                                               aucRsv[2];
    NAS_MSCC_SYS_ACQ_1X_INIT_LOC_STA_STRU                   st1xInitLocSta;
    NAS_MSCC_SYS_ACQ_LTE_INIT_LOC_STA_STRU                  stLteInitLocSta;
    NAS_MSCC_SYS_ACQ_SYS_LIST_INFO_STRU                     stSysAcqListInfo;
}NAS_MSCC_FSM_SYS_ACQ_CTX_STRU;


typedef struct
{
    VOS_UINT32                          ulAvailableTimerCount;                  /* current Available Timer start count */
}NAS_MSCC_FSM_L1_MAIN_CTX_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_BG_SEARCH_HRPD_INFO_STRU
Description     :   Structure definition containing the variables bg search reslut for BSR FSM.
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/
typedef struct
{
    VOS_UINT8                           ucHrpdSysNum;
    VOS_UINT8                           aucReserve[3];
    MSCC_MMC_HRPD_SYS_STRU              astHrpdSysList[MSCC_MMC_BG_HRPD_MAX_SYS_NUM];
}NAS_MSCC_BG_SEARCH_HRPD_INFO_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_HRPD_SYS_REC_ITEM_STRU
 �ṹ˵��  : ϵͳ����HRPD����Ϣ
 1.��    ��   : 2015��04��07��
   ��    ��   : y00307564
   �޸�����   : ����
*****************************************************************************/
typedef struct
{
    VOS_UINT16                                              usAcqIndex;         /* ��ϵͳ��¼ָ���ACQ���Index */
    VOS_UINT16                                              usSysIndex;         /* ��HRPDϵͳ��¼��ϵͳ���е�Index */
    VOS_UINT8                                               ucPrioLevel;        /* ָʾHRPD�����ȼ���ȡֵ��1��ʼ */
    NAS_MSCC_PIF_PREF_NEG_SYS_ENUM_UINT8                    enPrefNegSys;       /* ��ϵͳ�Ƿ�Ϊnegative��preferred */
    VOS_UINT8                                               aucRcv[2];
}NAS_MSCC_HRPD_SYS_REC_ITEM_STRU;

/*****************************************************************************
 �ṹ��    : NAS_MSCC_SYSTEM_ACQUIRE_FREQ_INFO_STRU
 �ṹ˵��  : �����ȼ�����Ƶ����Ϣ
 1.��    ��   : 2015��04��07��
   ��    ��   : y00307564
   �޸�����   : �½�

*****************************************************************************/
typedef struct
{
    NAS_MSCC_PIF_FREQENCY_CHANNEL_STRU  stFreq;              /* ���HRPD��Ƶ����Ϣ */
    NAS_MSCC_HRPD_SYS_REC_ITEM_STRU     stHrpdSysItem;       /* �����ȼ�����Ӧ��HRPDϵͳ��Ϣ */
} NAS_MSCC_SYSTEM_ACQUIRE_FREQ_INFO_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_BG_SEARCH_HRPD_INFO_STRU
Description     :   Structure definition containing the variables bg search reslut for BSR FSM.
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/
typedef struct
{
    VOS_UINT8                                               ucFreqNum;                          /* Ƶ����� */
    VOS_UINT8                                               aucReserved[3];
    NAS_MSCC_SYSTEM_ACQUIRE_FREQ_INFO_STRU                  astFreqInfo[MSCC_HSD_MAX_PREF_SUBNET_NUM];
}NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU;
typedef struct
{
    VOS_UINT8                      uc1XPowerSaveFlg;
    VOS_UINT8                      ucHrpdPowerSaveFlg;
    VOS_UINT8                      uc3GppPowerSaveFlg;
    VOS_UINT8                      aucReserved[1];
}NAS_MSCC_POWER_SAVE_OPERATION_STRU;

/****************************************************************************
Structure name  :   NAS_MSCC_BSR_HRPD_PRIORITY_INFO_STRU
Description     :   Structure definition containing the variables BSR CTXfor BSR(HRPD PRIORITY) FSM.
Modify History:
    1)  Date    :   2015-04-07
        Author  :   y00307564
        Modify content :    Create
****************************************************************************/
typedef struct
{
    NAS_MSCC_BG_SEARCH_HRPD_INFO_STRU                       stBgSearchHrpdInfo;
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                 stHighPriSysInfo;
}NAS_MSCC_BSR_HRPD_SYS_INFO_STRU;


typedef struct
{
    VOS_UINT8                                               ucAbortFlag;
    VOS_UINT8                                               ucOrigSysMsplIndex;
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enDestBsrSysPriClass;      /* ��Ҫ����BSR��ϵͳ��pri class */
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enDestBsrSysType;          /* ��Ҫ����BSR��ϵͳ��sys type */

    NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU               stPrefPlmnList;
    NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU                 stHighPriSysInfo;
}NAS_MSCC_FSM_BSR_CTX_STRU;


typedef union
{
    /* context structure storing L1 main ctx */
    NAS_MSCC_FSM_L1_MAIN_CTX_STRU       stL1MainCtx;

    /* Context structure storing the Switch On Module Order */
    NAS_MSCC_FSM_SWITCH_ON_CTX_STRU     stSwitchOnCtx;

    /* Context Structure storing the Power Off Module Order. */
    NAS_MSCC_FSM_POWER_OFF_CTX_STRU     stPowerOffCtx;

    NAS_MSCC_FSM_SYS_ACQ_CTX_STRU       stSysAcqCtx;

    NAS_MSCC_FSM_BSR_CTX_STRU           stBsrCtx;

    NAS_MSCC_FSM_SYSCFG_CTX_STRU        stSysCfgCtx;
}NAS_MSCC_FSM_EXTRA_CTX_UNION;

typedef struct
{
    NAS_MSCC_PIF_RAT_PRIO_STRU          stRatPrio;
}NAS_MSCC_MS_SYS_CFG_INFO_STRU;



typedef struct
{
    VOS_UINT8                           ucIsBsrTimerNvimActiveFlag;
    VOS_UINT8                           aucReserved[3];
    VOS_UINT32                          ulAvailableTimerLengthFirstSearch;
    VOS_UINT32                          ulAvailableTimerCountFirstSearch;
    VOS_UINT32                          ulAvailableTimerLengthDeepSearch;
    VOS_UINT32                          ulScanTimerLen;
    VOS_UINT32                          ulBsrTimerLen;
    VOS_UINT32                          ulSleepTimerLen;
}NAS_MSCC_SYSACQ_TIMER_CFG_STRU;


typedef struct
{
     VOS_UINT8                          ucReAcqLteOnHrpdSyncIndFlag;
     VOS_UINT8                          ucIs1xLocInfoPrefThanLte;
     VOS_UINT8                          aucReserved[2];
     NAS_MSCC_SYSACQ_TIMER_CFG_STRU     stSysAcqTimerCfg;

}NAS_MSCC_MMSS_SYSACQ_CFG_STRU;


typedef struct
{
    NAS_MSCC_MMSS_SYSACQ_CFG_STRU       stMmssSysAcqCfg;
    NAS_MSCC_MMSS_LOCATION_INFO_STRU    stMmssLastLocInfo;
}NAS_MSCC_MMSS_CFG_INFO_STRU;


typedef struct
{
    NAS_MSCC_MLPL_STRU                                      stMlplInfo;
    NAS_MSCC_MSPL_STRU                                      stMsplInfo;
    VOS_UINT8                                               ucMlplValid;
    VOS_UINT8                                               ucMsplValid;
    VOS_UINT8                                               ucRsv[2];
}NAS_MSCC_MLPL_MSPL_INFO_STRU;



typedef struct
{
    VOS_UINT8                                     ucRatNum;
    VOS_UINT8                                     aucReserved[3];
    VOS_RATMODE_ENUM_UINT32                       aenRatList[NAS_MSCC_PLATFORM_MAX_RAT_NUM];
}NAS_MSCC_PLATFORM_RAT_CAP_STRU;


typedef struct
{
    NAS_MSCC_PLATFORM_RAT_CAP_STRU      stPlatformRatCap;
    NAS_MSCC_IMS_CONFIG_PARA_STRU       stImsCfgInfo;
    NAS_MSCC_MMSS_CFG_INFO_STRU         stMmssNvimCfgInfo;
}NAS_MSCC_CUSTOM_CONFIG_STRU;




typedef struct
{
    /* FSM Descriptor containing the State table, init handle  */
    NAS_FSM_DESC_STRU                  *pstFsmDesc;

    /* Stores the ID of the current FSM */
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    /* Stores the ID of the parent FSM */
    NAS_MSCC_FSM_ID_ENUM_UINT32         enParentFsmId;

    /* Stores the Event type of the parent FSM */
    VOS_UINT32                          ulParentEventType;

    /* Stores the current state of the FSM */
    VOS_UINT32                          ulState;

    /* Stores the current entry message  */
    NAS_MSCC_MSG_STRU                   stEntryMsg;

    /* Stores Context details specific to FSM */
    NAS_MSCC_FSM_EXTRA_CTX_UNION        unFsmCtx;

}NAS_MSCC_FSM_CTX_STRU;
typedef struct
{
    VOS_UINT16                          usStackDepth;                           /* Stores the current Stack depth */
    VOS_UINT8                           aucReserved[2] ;                        /* Required for padding */
    NAS_MSCC_FSM_CTX_STRU               astFsmStack[NAS_MSCC_MAX_FSM_STACK_DEPTH];  /* Array of FSM contexts */
}NAS_MSCC_FSM_STACK_STRU;
typedef struct
{
    VOS_UINT8                           ucCacheMsgNum;                          /* Stores the number of Cache messages */
    VOS_UINT8                           aucReserve[3];                          /* Required for padding */
    NAS_MSCC_MSG_STRU                   astCacheMsg[NAS_MSCC_MAX_CACHE_MSG_QUEUE_NUM]; /* Queue of cache messages */
}NAS_MSCC_CACHE_MSG_QUEUE_STRU;
typedef struct
{
    VOS_UINT8                           ucIntMsgNum;                                /* Number of internal messages */
    VOS_UINT8                           aucReserve[3];
    VOS_UINT8                          *pastIntMsg[NAS_MSCC_MAX_INT_MSG_QUEUE_NUM]; /* Queue of internal messages */
}NAS_MSCC_INT_MSG_QUEUE_STRU;


typedef struct
{
    NAS_MSCC_CUSTOM_CONFIG_STRU         stCustomCfgInfo;
    NAS_MSCC_MS_SYS_CFG_INFO_STRU       stMsSysCfgInfo;                         /* syscfgex setting info */
}NAS_MSCC_MS_CFG_INFO_STRU;
/* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */

typedef struct
{
    VOS_UINT32                           ulModem0Pid;
    VOS_UINT32                           ulModem1Pid;
}NAS_MSCC_MODEM_PID_TAB_STRU;
/* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
/*****************************************************************************
 �ṹ��    : NAS_MSCC_EVENT_STATE_STRU
 �ṹ˵��  : ��Ϣ�ϱ��ṹ��

  1.��    ��   : 2015��7��12��
    ��    ��   : y00322978
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    VOS_UINT32                          ulReceiveTime;  //����ʱ��
    VOS_UINT32                          ulExitTime;     //����ʱ��
    VOS_UINT32                          ulSendPid;      //����PID
    VOS_UINT32                          ulReceivePid;   //����PID
    VOS_UINT16                          usMsgName;      //��Ϣ��
    VOS_UINT8                           aucReserve[2];
}NAS_MSCC_MSG_STATE_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_LOG_EVENT_STATUS_STRU
 �ṹ˵��  :  mscc ��ά�ɲ⹴ȡ���ͽ�����Ϣ

  1.��    ��   : 2015��7��12��
    ��    ��   : y00322978
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    NAS_MSCC_MSG_STATE_STRU             stMsgState[NAS_MSCC_MAX_LOG_MSG_STATE_NUM];
    VOS_UINT8                           ucLatestIndex;
    VOS_UINT8                           ucReserve[3];
}NAS_MSCC_LOG_MSG_STATUS_STRU;
/*****************************************************************************
 �ṹ��    : NAS_MSCC_MNTN_CTX_STRU
 �ṹ˵��  : mscc ��ά�ɲ⹴ȡ���ͽ�����Ϣ

  1.��    ��   : 2015��7��12��
    ��    ��   : y00322978
    �޸�����   : ������
*****************************************************************************/
typedef struct
{
    NAS_MSCC_LOG_MSG_STATUS_STRU        stLogMsgState;
}NAS_MSCC_MNTN_CTX_STRU;

/* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

typedef struct
{
    NAS_MSCC_FSM_CTX_STRU               stCurFsm;                               /* ״̬����ǰ��״̬������ */
    NAS_MSCC_FSM_STACK_STRU             stFsmStack;                             /* ״̬����״̬��ջ����   */
    NAS_MSCC_CACHE_MSG_QUEUE_STRU       stCacheMsgQueue;
    NAS_MSCC_INT_MSG_QUEUE_STRU         stIntMsgQueue;
    NAS_MSCC_SIM_INFO_STRU              stSimInfo;
    NAS_MSCC_MS_CFG_INFO_STRU           stMsCfgInfo;
    NAS_MSCC_TIMER_CTX_STRU             astMsccTimerCtx[TI_NAS_MSCC_TIMER_BUTT];/* MSCC��ǰ�������еĶ�ʱ����Դ */
    NAS_MSCC_NW_INFO_STRU               stNwInfo;
    NAS_MSCC_MLPL_MSPL_INFO_STRU        stMlplMsplInfo;
    NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU   stPowerSaveCtrl;                       /* power save���������� */
    NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU      stSysAcqCtrl;
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_MNTN_CTX_STRU              stMntnInfo;
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, begin */
    NAS_MSCC_SYS_ACQ_CALL_CTRL_CTX_STRU stSysAcqCallCtrl;
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, end */
}NAS_MSCC_CTX_STRU;

/*****************************************************************************
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/


/*****************************************************************************
  10 ��������
*****************************************************************************/
NAS_MSCC_CTX_STRU* NAS_MSCC_GetMsccCtxAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitCtx(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8 enInitType
);

VOS_VOID NAS_MSCC_InitNetworkInfo(
    NAS_MSCC_NW_INFO_STRU               *pstNwInfo
);

VOS_VOID NAS_MSCC_SetGuNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstGuNwCap);

NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetGuNwCapInfo(VOS_VOID);

VOS_VOID NAS_MSCC_SetLteNwCapInfo(NAS_MSCC_NETWORK_CAP_INFO_STRU *pstLteNwCap);

NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8  NAS_MSCC_GetPersistentBearerState(VOS_VOID);
VOS_VOID    NAS_MSCC_SetPersistentBearerState(
    NAS_MSCC_PERSISTENT_BEARER_STATE_ENUM_UINT8             enPersistentBearerState
);
MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8  NAS_MSCC_GetImsVoiceCapability(VOS_VOID);
VOS_VOID    NAS_MSCC_SetImsVoiceCapability(
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8             enImsVoiceCap
);
NAS_MSCC_NETWORK_CAP_INFO_STRU *NAS_MSCC_GetLteNwCapInfo(VOS_VOID);

NAS_MSCC_SYS_INFO_STRU *NAS_MSCC_GetCurrSysInfo(VOS_VOID);
NAS_MSCC_SERVICE_STATUS_INFO_STRU *NAS_MSCC_GetCurrServiceStatusInfo(VOS_VOID);

NAS_MSCC_TIMER_CTX_STRU *NAS_MSCC_GetTimerCtxAddr(VOS_VOID);

NAS_MSCC_IMS_CONFIG_PARA_STRU *NAS_MSCC_GetImsCfgInfo(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetWaitImsVoiceAvailTimerLen(VOS_VOID);

VOS_VOID  NAS_MSCC_LoadSubFsm(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId,
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm
);

VOS_VOID NAS_MSCC_InitFsmL2(
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId
);
VOS_VOID NAS_MSCC_PopFsm( VOS_VOID );

VOS_VOID NAS_MSCC_PushFsm(
    NAS_MSCC_FSM_STACK_STRU             *pstFsmStack,
    NAS_MSCC_FSM_CTX_STRU               *pstNewFsm
);

VOS_VOID NAS_MSCC_QuitFsmL2(VOS_VOID);

VOS_VOID  NAS_MSCC_SetCurrFsmState(
    VOS_UINT32                          ulCurrState
);

VOS_UINT32 NAS_MSCC_GetFsmTopState(VOS_VOID);

NAS_MSCC_CACHE_MSG_QUEUE_STRU* NAS_MSCC_GetCacheMsgAddr(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetCacheMsgNum(VOS_VOID);

VOS_UINT32  NAS_MSCC_SaveCacheMsg(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);
VOS_UINT32 NAS_MSCC_GetNextCachedMsg(
    NAS_MSCC_MSG_STRU                  *pstEntryMsg
);

NAS_MSCC_FSM_CTX_STRU* NAS_MSCC_GetCurFsmAddr(VOS_VOID);

NAS_FSM_DESC_STRU* NAS_MSCC_GetCurFsmDesc(VOS_VOID);

NAS_MSCC_FSM_ID_ENUM_UINT32 NAS_MSCC_GetCurrFsmId(VOS_VOID);

NAS_MSCC_MSG_STRU* NAS_MSCC_GetCurrFsmEntryMsgAddr(VOS_VOID);

VOS_UINT8* NAS_MSCC_GetCurrFsmEntryMsgBufferAddr(VOS_VOID);

NAS_MSCC_FSM_STACK_STRU* NAS_MSCC_GetFsmStackAddr(VOS_VOID);

VOS_UINT16 NAS_MSCC_GetFsmStackDepth(VOS_VOID);

NAS_MSCC_INT_MSG_QUEUE_STRU* NAS_MSCC_GetIntMsgQueueAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitInternalBuffer(
    NAS_MSCC_INT_MSG_QUEUE_STRU        *pstIntMsgQueue
);

VOS_VOID NAS_MSCC_PutMsgInIntMsgQueue(
    VOS_UINT8                          *pstMsg
);

VOS_UINT8 *NAS_MSCC_GetNextIntMsg(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetIntMsgNum(VOS_VOID);


VOS_VOID NAS_MSCC_ClearCacheMsg(
    VOS_UINT8                           ucIndex
);

VOS_VOID NAS_MSCC_SaveCacheMsgInMsgQueue(
    VOS_UINT32                          ulEventType,
    VOS_VOID                           *pstMsg
);

VOS_VOID NAS_MSCC_InitCacheMsgQueue(
    NAS_MSCC_CACHE_MSG_QUEUE_STRU      *pstCacheMsgQueue
);


VOS_VOID NAS_MSCC_SaveCurEntryMsg(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
);

NAS_MSCC_FSM_SWITCH_ON_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_SwitchOn(VOS_VOID);

VOS_VOID NAS_MSCC_SetModuleOrder_SwitchOn(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetNextModuleId_SwitchOn(
    VOS_UINT32                         *pulNextModuleId
);

VOS_UINT32 NAS_MSCC_IsModuleOrderValid_SwitchOn(VOS_VOID);

NAS_MSCC_FSM_POWER_OFF_CTX_STRU* NAS_MSCC_GetModuleOrderAddr_PowerOff(VOS_VOID);

VOS_VOID NAS_MSCC_SetModuleOrder_PowerOff(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetNextModuleId_PowerOff(
    VOS_UINT32                         *pulNextModuleId
);

VOS_UINT32 NAS_MSCC_IsModuleOrderValid_PowerOff(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupport3Gpp(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupportCdma1X(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformSupportCdmaEVDO(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetImsSupportFlag(VOS_VOID);

NAS_MSCC_PLATFORM_RAT_CAP_STRU*  NAS_MSCC_GetPlatformRatCap(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsPlatformRatCapNvimValid(
    PLATAFORM_RAT_CAPABILITY_STRU      *pstNvPlatformRatCap
);


VOS_VOID NAS_MSCC_InitCurrFsmCtx(
    NAS_MSCC_FSM_CTX_STRU              *pstCurrFsmCtx
);

VOS_VOID NAS_MSCC_InitFsmStackCtx(
    NAS_MSCC_FSM_STACK_STRU            *pstFsmStack
);

VOS_VOID NAS_MSCC_InitTimerCtx(
    NAS_MSCC_TIMER_CTX_STRU            *pstTimerCtx
);

NAS_MSCC_MS_CFG_INFO_STRU* NAS_MSCC_GetMsCfgInfoStruAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_SwitchOn(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_PowerOff(VOS_VOID);

NAS_MSCC_FSM_SYS_ACQ_CTX_STRU* NAS_MSCC_GetSysAcqFsmCtxAddr(VOS_VOID);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID NAS_MSCC_InitFsmCtx_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_BSR(VOS_VOID);

#endif

NAS_MSCC_SYSACQ_TIMER_CFG_STRU* NAS_MSCC_GetSysAcqTimerCfgAddr(VOS_VOID);

NAS_MSCC_MMSS_LOCATION_INFO_STRU* NAS_MSCC_GetMmssLastLocationInfoAddr(VOS_VOID);

NAS_MSCC_MMSS_CFG_INFO_STRU* NAS_MSCC_GetMmssNvimCfgInfoAddr(VOS_VOID);

NAS_MSCC_MMSS_SYSACQ_CFG_STRU* NAS_MSCC_GetMmssSysAcqCfgInfoAddr(VOS_VOID);

NAS_MSCC_3GPP_SYS_INFO_STRU* NAS_MSCC_Get3gppSysInfoAddr(VOS_VOID);

NAS_MSCC_1X_SYS_INFO_STRU* NAS_MSCC_Get1xSysInfoAddr(VOS_VOID);

NAS_MSCC_HRPD_SYS_INFO_STRU* NAS_MSCC_GetHrpdSysInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_Set1xCampOnFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_Get1xCampOnFlag(VOS_VOID);

VOS_VOID NAS_MSCC_SetHrpdCampOnFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_GetHrpdCampOnFlag(VOS_VOID);

VOS_VOID NAS_MSCC_Set3gppCampOnFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_GetLteCampOnFlag(VOS_VOID);

VOS_UINT8 NAS_MSCC_Get3gppCampOnFlag(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurr3gppRoamingFlg(
    VOS_UINT8                               ucRoamingFlg
);
VOS_UINT8 NAS_MSCC_GetCurr3gppRoamingFlg(VOS_VOID);
VOS_VOID NAS_MSCC_UpdateRoamFlag(
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
);

VOS_VOID NAS_MSCC_SetBsrTimerNvimActiveFlag(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_GetBsrTimerNvimActiveFlag(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetMlplMsplValidFlag(VOS_VOID);

VOS_VOID NAS_MSCC_SetMlplValidFlag(VOS_UINT8 ucValid);

VOS_VOID NAS_MSCC_SetMsplValidFlag(VOS_UINT8 ucValid);

NAS_MSCC_MLPL_MSPL_INFO_STRU* NAS_MSCC_GetMlplMsplInfoAddr(VOS_VOID);

NAS_MSCC_MLPL_STRU* NAS_MSCC_GetMlplInfoAddr(VOS_VOID);

NAS_MSCC_MSPL_STRU* NAS_MSCC_GetMsplInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_SetWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
);

VOS_VOID NAS_MSCC_ClearWaitCardReadCnfFlag_SwitchOn(
    NAS_MSCC_WAIT_CARD_READ_CNF_FLAG_ENUM_UINT32 enFlag
);

VOS_VOID NAS_MSCC_ResetWaitCardReadCnfFlg_SwitchOn(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetWaitCardReadCnfFlag_SwitchOn(VOS_VOID);

NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU* NAS_MSCC_GetEhPlmnInfoAddr(VOS_VOID);

NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU* NAS_MSCC_GetUserPlmnInfoAddr(VOS_VOID);

NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU* NAS_MSCC_GetOperPlmnInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_InitMlplMsplInfo(
    NAS_MSCC_INIT_CTX_TYPE_ENUM_UINT8                       enInitType,
    NAS_MSCC_MLPL_MSPL_INFO_STRU                           *pstMlplMsplInfo
);

VOS_VOID NAS_MSCC_InitSimInfo(
    NAS_MSCC_SIM_INFO_STRU                                 *pstSimInfo
);

VOS_VOID NAS_MSCC_InitCardReadInfor(
    NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU             *pstCardReadInfo
);

NAS_MSCC_FSM_SWITCH_ON_CARD_READ_INFO_STRU* NAS_MSCC_GetCardReadInforAddr(VOS_VOID);

VOS_VOID  NAS_MSCC_InitSimUserPlmnInfo(
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                    *pstUserPlmnInfo
);

VOS_VOID  NAS_MSCC_InitSimOperPlmnInfo(
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                    *pstOperPlmnInfo
);

VOS_UINT32 NAS_MSCC_GetAbortFlag_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SetAbortFlag_SysAcq(
    VOS_UINT8                           ucAbortFlg
);

VOS_UINT8 NAS_MSCC_GetLteInitialAcqFinishFlg_SysAcq(VOS_VOID);

VOS_UINT8 NAS_MSCC_Get1xInitialAcqFinishFlg_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_SetLteInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
);

VOS_VOID NAS_MSCC_Set1xInitialAcqLocInfoStatus_SysAcq(
    NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8            enStatus
);

NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_GetLteInitialAcqLocInfoStatus_SysAcq(VOS_VOID);

NAS_MSCC_INIT_ACQ_LOC_INFO_STATUS_ENUM_UINT8 NAS_MSCC_Get1xInitialAcqLocInfoStatus_SysAcq(VOS_VOID);

VOS_VOID NAS_MSCC_InitFsmCtx_L1Main(VOS_VOID);

VOS_UINT32  NAS_MSCC_GetNextAvailableTimerLength_L1Main(VOS_VOID);

VOS_UINT32  NAS_MSCC_GetCurAvailableTimerStartCount_L1Main(VOS_VOID);

VOS_VOID  NAS_MSCC_ResetCurAvailableTimerStartCount_L1Main(VOS_VOID);

VOS_VOID  NAS_MSCC_AddCurAvailableTimerStartCount_L1Main(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetScanTimerLength(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetSleepTimerLength(VOS_VOID);

VOS_UINT8  NAS_MSCC_GetHrpdConnExistFlg(VOS_VOID);

VOS_VOID  NAS_MSCC_SetHrpdConnExistFlg(
    VOS_UINT8                           ucFlg
);

VOS_UINT8  NAS_MSCC_GetLteEpsConnExistFlg(VOS_VOID);

VOS_VOID  NAS_MSCC_SetLteEpsConnExistFlg(
    VOS_UINT8                           ucFlg
);

NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8  NAS_MSCC_GetLtePriClass(VOS_VOID);
NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xPriClass(VOS_VOID);
NAS_MSCC_SYS_PRI_CLASS_ENUM_UINT8  NAS_MSCC_Get1xAIPriClass(VOS_VOID);

VOS_UINT32 NAS_MSCC_GetAbortFlag_BSR(VOS_VOID);

VOS_VOID NAS_MSCC_SetAbortFlag_BSR(
    VOS_UINT8                           ucAbortFlg
);

NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8 NAS_MSCC_GetDestBsrSysPriClass_BSR(VOS_VOID);
VOS_VOID NAS_MSCC_SetDestBsrSysPriClass_BSR(
    NAS_MSCC_MSPL_SYS_PRI_CLASS_ENUM_UINT8                  enSysPriClass
);
VOS_VOID NAS_MSCC_SetDestBsrSysType_BSR(
    NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8                  enSysType
);

VOS_VOID NAS_MSCC_SetOrigSysMsplIndex_BSR(
    VOS_UINT8                           ucOrigSysMsplIndex
);

VOS_UINT8 NAS_MSCC_GetOrigSysMsplIndex_BSR(VOS_VOID);

NAS_MSCC_MLPL_MSPL_SYS_TYPE_ENUM_UINT8 NAS_MSCC_GetDestBsrSysType_BSR(VOS_VOID);

NAS_MSCC_HIGH_PRIORITY_SYSTEM_INFO_STRU *NAS_MSCC_GetHrpdHighPrioSysInfo_BSR(VOS_VOID);

NAS_MSCC_PIF_SEARCHED_PLMN_LIST_INFO_STRU* NAS_MSCC_GetLtePrefPlmnListInfo_BSR(VOS_VOID);

VOS_VOID NAS_MSCC_SaveCardStatus(
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimStatus,
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimStatus
);

VOS_VOID NAS_MSCC_SaveIsCardChangedFlg(
    VOS_UINT8                           ucIsCardChanged
);

VOS_UINT8 NAS_MSCC_GetIsCardChangedFlg( VOS_VOID );

VOS_VOID  NAS_MSCC_SetSimCsRegStatus(
    VOS_UINT8                           ucSimCsRegStatus
);

VOS_VOID  NAS_MSCC_SetSimPsRegStatus(
    VOS_UINT8                           ucSimPsRegStatus
);

VOS_UINT8  NAS_MSCC_GetSimCsRegStatus(VOS_VOID);

VOS_UINT8  NAS_MSCC_GetSimPsRegStatus(VOS_VOID);

VOS_VOID NAS_MSCC_SavePrioRatList(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstRatPrio
);

NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetUsimCardStatus(VOS_VOID);

NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 NAS_MSCC_GetCsimCardStatus(VOS_VOID);

NAS_MSCC_PIF_RAT_PRIO_STRU* NAS_MSCC_GetRatPrioList(VOS_VOID);

VOS_UINT32 NAS_MSCC_IsSpecRatSupported(
    NAS_MSCC_PIF_NET_RAT_TYPE_ENUM_UINT8                    enRat
);

VOS_UINT32 NAS_MSCC_IsUserSysCfgRatCapSupport3Gpp(VOS_VOID);

NAS_MSCC_SYS_MODE_ENUM_UINT8 NAS_MSCC_Get3gppCurSysMode(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurr3gppPsServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr3gppPsServiceStatus(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurr1xServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurr1xServiceStatus(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurrHrpdServiceStatus(
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enSrvSt
);

NAS_MSCC_SERVICE_STATUS_ENUM_UINT8 NAS_MSCC_GetCurrHrpdServiceStatus(VOS_VOID);

VOS_UINT8 NAS_MSCC_GetHrpdActiveFlg(VOS_VOID);

VOS_VOID NAS_MSCC_SetHrpdActiveFlg(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_Get3gppActiveFlg(VOS_VOID);

VOS_VOID NAS_MSCC_Set3gppActiveFlg(
    VOS_UINT8                           ucFlag
);

VOS_UINT8 NAS_MSCC_Get1xActiveFlg(VOS_VOID);

VOS_VOID NAS_MSCC_Set1xActiveFlg(
    VOS_UINT8                           ucFlag
);

VOS_VOID  NAS_MSCC_SetPowerSaveReplyFlg(
    VOS_UINT8                           ucFlg
);

VOS_UINT8  NAS_MSCC_GetPowerSaveReplyFlg(VOS_VOID);


VOS_VOID NAS_MSCC_InitMsCfgInfo(
    NAS_MSCC_MS_CFG_INFO_STRU          *pstMsCfgInfo
);

VOS_VOID NAS_MSCC_InitCustomCfgInfo(
    NAS_MSCC_CUSTOM_CONFIG_STRU        *pstCustomCfgInfo
);

VOS_VOID NAS_MSCC_InitMsSysCfgInfo(
    NAS_MSCC_MS_SYS_CFG_INFO_STRU      *pstMsSysCfgInfo
);

VOS_VOID NAS_MSCC_InitPlatformRatCapInfo(
    NAS_MSCC_PLATFORM_RAT_CAP_STRU     *pstPlatformRatCap
);

VOS_VOID NAS_MSCC_InitImsCfgInfo(
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo
);

VOS_VOID NAS_MSCC_InitMmssCfgInfo(
    NAS_MSCC_MMSS_CFG_INFO_STRU        *pstMmssCfgInfo
);

VOS_VOID NAS_MSCC_InitMmssLastLocationInfo(
    NAS_MSCC_MMSS_LOCATION_INFO_STRU   *pstMmssLastLocationInfo
);

VOS_VOID NAS_MSCC_InitSysAcqTimerCfgInfo(
    NAS_MSCC_SYSACQ_TIMER_CFG_STRU     *pstSysAcqTimerCfg
);

VOS_VOID NAS_MSCC_InitPowerSaveCtrlInfo(
    NAS_MSCC_POWER_SAVE_CTRL_CTX_STRU  *pstPowerSaveCtrlInfo
);

VOS_VOID NAS_MSCC_InitSysAcqCtrlInfo(
    NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU     *pstSysAcqCtrlInfo
);

NAS_MSCC_SYS_ACQ_CTRL_CTX_STRU* NAS_MSCC_GetSysAcqCtrlInfoAddr(VOS_VOID);

VOS_VOID NAS_MSCC_SetCurrBsrTimerLen(
    VOS_UINT32                          ulBsrTimerLen
);

VOS_UINT32 NAS_MSCC_GetCurrBsrTimerLen(VOS_VOID);

VOS_VOID NAS_MSCC_SetOrigBsrTimerStartRat(VOS_VOID);

VOS_RATMODE_ENUM_UINT32 NAS_MSCC_GetOrigBsrTimerStartRat(VOS_VOID);


VOS_VOID NAS_MSCC_SetDataServiceSwitchTo1xFlg(
    VOS_UINT8                           ucDataServiceSwitchTo1xFlg
);
VOS_UINT8 NAS_MSCC_GetDataServiceSwitchTo1xFlg(VOS_VOID);


NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetPowerSaveModuleOrderAddr_SysCfg(VOS_VOID);

NAS_MSCC_PREF_ORDER_MODULE_LIST* NAS_MSCC_GetSysCfgModuleOrderAddr_SysCfg(VOS_VOID);

/* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
VOS_VOID NAS_MSCC_AddLogMsgState(
    VOS_UINT32                          ulSendPid,
    VOS_UINT32                          ulReceivePid,
    VOS_UINT16                          usMsgName
);
VOS_VOID NAS_MSCC_UpdateMsgExitTime( VOS_VOID );
VOS_VOID NAS_MSCC_LogMsgInfo(
    MSG_HEADER_STRU                    *pstMsgHeader
);

VOS_VOID NAS_MSCC_InitMntnInfo(
    NAS_MSCC_MNTN_CTX_STRU            *pstMntnInfo
);

VOS_VOID NAS_MSCC_InitSysAcqCallCtrl(
    NAS_MSCC_SYS_ACQ_CALL_CTRL_CTX_STRU                    *pstSysAcqCallCtrl
);

/* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, begin */
VOS_VOID  NAS_MSCC_Set1xSysAcqMoCallFlag(
    VOS_UINT8                           ucFlg
);

VOS_UINT8  NAS_MSCC_Get1xSysAcqMoCallFlag(VOS_VOID);

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, end */
#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_DSDS))
VOS_UINT8 NAS_MSCC_IsCLCombinedModeWithRatPrio
(
    NAS_MSCC_PIF_RAT_PRIO_STRU         *pstUserRatPrio
);
#endif

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

#endif /* end of NasMsccCtx.h */
