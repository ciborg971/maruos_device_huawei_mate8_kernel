
#ifndef _MMC_MM_INTERFACE_H_
#define _MMC_MM_INTERFACE_H_

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "PsTypeDef.h"
#include "NasCommDef.h"
#include "Nasrrcinterface.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define     MMCMM_NAS_MAX_SIZE_NAS_GSM_MAP          RRC_NAS_MAX_SIZE_NAS_GSM_MAP                                  /* Э��ֵ : 8                               */
#define     NAS_MAX_EQUPLMN_NUM                     (15)

/* ��ϢMMCMM_SERVICE_STATUS_IND�Ľṹ�� */
/* ulServiceStatus */
#define     MMC_MM_NORMAL_SERVICE                   NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE
#define     MMC_MM_LIMITED_SERVICE                  NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE
#define     MMC_MM_LIMITED_SERVICE_REGION           NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE_REGION
#define     MMC_MM_NO_IMSI                          NAS_MSCC_PIF_SERVICE_STATUS_NO_IMSI
#define     MMC_MM_NO_SERVICE                       NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE

/* A32D12977==> */
/* ��ϢMMCMM_CM_SERVICE_IND�Ľṹ�� */
/* ulEmcFlg */
#define     MM_EMERGENCY_CALL_TRUE                  1
#define     MM_EMERGENCY_CALL_FALSE                 0

/* ulCsServFlg */
#define     MM_CS_SERV_NOT_EXIST                    0                            /* û��CS��ҵ��                             */
#define     MM_CS_SERV_EXIST                        1                            /* ��CS��ҵ��                               */

#define     MMC_MM_RR_CONN_ABSENT                   0
#define     MMC_MM_RR_CONN_ESTING                   1
#define     MMC_MM_RR_CONN_ESTED                    2

/* ulForbiddenFlg ȡֵ */
#define     MMCMM_NO_FORBIDDEN                      0x00000000
#define     MMCMM_FORBIDDEN_PLMN                    0x00000001
#define     MMCMM_FORBIDDEN_PLMN_FOR_GPRS           0x00000002
#define     MMCMM_FORBIDDEN_LA_FOR_ROAM             0x00000004
#define     MMCMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS     0x00000008

/* usMsgType ȡֵ */
#define     MMC_RECEIVE_ATTACH_REQ                  0                           /* �Ѿ����յ�MMCMM_ATTACH_REQ   */
#define     MMC_RECEIVE_SYS_INFO                    1                           /* �Ѿ����յ�MMCMM_SYS_INFO_IND */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum MMC_MM_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/  /* ��ע */
/* MMC����MM��ԭ�� */
    MMCMM_SYS_INFO_IND                  = 0,   /* _H2ASN_MsgChoice MMCMM_SYS_INFO_IND_STRU */
    MMCMM_COVERAGE_LOST_IND             = 2,   /* _H2ASN_MsgChoice MMCMM_COVERAGE_LOST_IND_STRU */
    MMCMM_PLMN_SEARCH_INITIATED         = 4,   /* _H2ASN_MsgChoice MMCMM_PLMN_SEARCH_INITIATED_STRU */
    MMCMM_START_REQ                     = 6,   /* _H2ASN_MsgChoice MMCMM_START_REQ_STRU */
    MMCMM_DETACH_REQ                    = 8,   /* _H2ASN_MsgChoice MMCMM_DETACH_REQ_STRU */
    MMCMM_POWER_OFF_REQ                 = 10,  /* _H2ASN_MsgChoice MMCMM_POWER_OFF_REQ_STRU */
    /* MMCMM_PLMN_USER_SEL_REQ����ʹ�ã�ɾ�� */
    MMCMM_ATTACH_REQ                    = 14,  /* _H2ASN_MsgChoice MMCMM_ATTACH_REQ_STRU */
    MMCMM_MODE_CHANGE_REQ               = 16,  /* _H2ASN_MsgChoice MMCMM_MODE_CHANGE_REQ_STRU */
    MMCMM_SUSPEND_IND                   = 18,  /* _H2ASN_MsgChoice MMCMM_SUSPEND_IND_STRU */
    MMCMM_RESUME_IND                    = 20,  /* _H2ASN_MsgChoice MMCMM_RESUME_IND_STRU */
    MMCMM_GSM_SYS_INFO_IND              = 22,  /* _H2ASN_MsgChoice MMCMM_GSM_SYS_INFO_IND_ST */
    MMCMM_REL_REQ                       = 24,  /* _H2ASN_MsgChoice MMCMM_REL_REQ_STRU */
    /* MMC����MM LMM��ע���� */
    MMCMM_LMM_ATTACH_IND                = 26,  /* _H2ASN_MsgChoice MMCMM_LMM_ATTACH_IND_STRU */
    MMCMM_LMM_TAU_RESULT_IND            = 28,  /* _H2ASN_MsgChoice MMCMM_LMM_TAU_RESULT_IND_STRU */
    MMCMM_LMM_MT_DETACH_IND             = 30,  /* _H2ASN_MsgChoice MMCMM_LMM_MT_DETACH_IND_STRU */
    MMCMM_LMM_SERVICE_RESULT_IND        = 32,  /* _H2ASN_MsgChoice MMCMM_LMM_SERVICE_RESULT_IND_STRU */

    MMCMM_LTE_SYS_INFO_IND              = 34,   /* _H2ASN_MsgChoice MMC_MM_LTE_SYS_INFO_IND_STRU */

    MMCMM_LMM_MO_DETACH_IND             = 36,  /* _H2ASN_MsgChoice MMCMM_LMM_MO_DETACH_IND_STRU */
    MMCMM_LMM_LOCAL_DETACH_IND          = 38,  /* _H2ASN_MsgChoice MMCMM_LMM_LOCAL_DETACH_IND_STRU */

    MMCMM_W_AC_INFO_CHANGE_IND          = 40,   /* _H2ASN_MsgChoice MMMMC_CS_REG_RESULT_IND_STRU */

    MMCMM_LMM_TIMER_STATE_NOTIFY        = 42,

    MMCMM_SRVCC_INFO_NOTIFY             = 44,   /* _H2ASN_MsgChoice MMCMM_SRVCC_INFO_NOTIFY_STRU */

    MMCMM_RAT_CHANGE_IND                = 46,   /* _H2ASN_MsgChoice MMCMM_RAT_CHANGE_IND_STRU */

    MMCMM_LAU_REQ                       = 48,   /* _H2ASN_MsgChoice MMCMM_LAU_REQ_STRU */


/* MM����MMC��ԭ�� */
    MMCMM_CM_SERVICE_IND                = 1,   /* _H2ASN_MsgChoice MMCMM_CM_SERVICE_IND_STRU */
    MMCMM_CM_SERVICE_REJECT_IND         = 3,   /* _H2ASN_MsgChoice MMCMM_CM_SERVICE_REJECT_IND_STRU */
    MMCMM_START_CNF                     = 5,   /* _H2ASN_MsgChoice MMCMM_START_CNF_STRU */
    MMCMM_DETACH_CNF                    = 7,   /* _H2ASN_MsgChoice MMCMM_DETACH_CNF_STRU */
    MMCMM_POWER_OFF_CNF                 = 9,   /* _H2ASN_MsgChoice MMCMM_POWER_OFF_CNF_STRU */

    MMCMM_RR_CONN_INFO_IND              = 13,  /* _H2ASN_MsgChoice MMCMM_RR_CONN_INFO_IND_STRU */
    MMCMM_RESUME_RSP                    = 15,  /* _H2ASN_MsgChoice MMCMM_RESUME_RSP_STRU */
    MMCMM_REGISTER_STATE_CHANGE_IND     = 17,  /* _H2ASN_MsgChoice MMCMM_REGISTER_STATE_CHANGE_IND_ST */
    MMCMM_INFO_IND                      = 19,  /* _H2ASN_MsgChoice MMCMM_INFO_IND_STRU */
    MMCMM_RR_REL_IND                    = 21,  /* _H2ASN_MsgChoice MMCMM_RR_REL_IND_ST */
    MMCMM_SUSPEND_RSP                   = 23,  /* _H2ASN_MsgChoice MMCMM_SUSPEND_RSP_ST */
    MMCMM_DEREGISTER_INITIATION         = 25,  /* _H2ASN_MsgChoice MMCMM_DEREGISTER_INITIATION_STRU */
    MMMMC_CS_REG_RESULT_IND             = 27,   /* _H2ASN_MsgChoice MMMMC_CS_REG_RESULT_IND_STRU */
    MMCMM_ATTACH_CNF                    = 29,   /* _H2ASN_MsgChoice MMCMM_ATTACH_CNF_STRU */
    MMMMC_ABORT_IND                     = 31,   /* _H2ASN_MsgChoice MMMMC_ABORT_IND_STRU */
    MMCMM_SIM_AUTH_FAIL_IND             = 33,   /* _H2ASN_MsgChoice MMCMM_SIM_AUTH_FAIL_IND_STRU */
    MMCMM_PLMN_SEARCH_IND               = 35,
    MMCMM_CSFB_ABORT_IND                = 36,

    MMCMM_MSG_TYPE_BUTT
};
typedef VOS_UINT16 MMC_MM_MSG_TYPE_ENUM_UINT16;

enum MM_MMC_PLMN_SEARCH_TYPE_ENUM
{
    MM_MMC_PLMN_SEARCH_TYPE_NORMAL          = 0,
    MM_MMC_PLMN_SEARCH_TYPE_EMERGENCY       = 1,
    MM_MMC_PLMN_SEARCH_TYPE_CSFB_BACK_LTE   = 2,

    MM_MMC_PLMN_SEARCH_TYPE_CSFB_END        = 3,

    MM_MMC_PLMN_SEARCH_TYPE_BUTT
};
typedef VOS_UINT32 MM_MMC_PLMN_SEARCH_TYPE_ENUM_U32;

/*****************************************************************************
 ö����    : MM_MMC_LU_RESULT_ENUM
 �ṹ˵��  : MMMMC_REG_RESULT_IND_STRU��Ϣ��LAU�Ľ��
*****************************************************************************/
enum MM_MMC_LU_RESULT_ENUM
{
    MM_MMC_LU_RESULT_SUCCESS    = 0,    /*LAU�ɹ�*/
    MM_MMC_LU_RESULT_FAILURE    = 1,    /*LAUʧ��*/
    MM_MMC_LU_RESULT_BUTT
};
typedef VOS_UINT32 MM_MMC_LU_RESULT_ENUM_U32;

/*****************************************************************************
 ö����    : MM_MMC_LU_PROC_ENUM
 �ṹ˵��  : MMMMC_REG_RESULT_IND_STRU��Ϣ��LAU��������
*****************************************************************************/
enum MM_MMC_LU_PROC_ENUM
{
    MM_MMC_LU_PROC_TRUE     = 0,    /* �����̱�־ */
    MM_MMC_LU_PROC_FALSE    = 1,    /* �����̱�־ */
    MM_MMC_LU_PROC_BUTT
};
typedef VOS_UINT32 MM_MMC_LU_PROC_ENUM_U32;


enum MMC_MM_DETACH_TYPE_ENUM
{
    MMC_MM_PS_DETACH        = 1,
    MMC_MM_CS_DETACH        = 2,
    MMC_MM_PS_CS_DETACH     = 3,
    MMC_MM_DETACH_BUTT
};
typedef VOS_UINT32 MMC_MM_DETACH_TYPE_ENUM_UINT32;


enum MMC_MM_DETACH_REASON_ENUM
{
    MMC_MM_DETACH_REASON_USER_DETACH           = 0,/* �û�������detach���� */
    MMC_MM_DETACH_REASON_RAT_OR_BAND_DETACH    = 1,/* system configure��RAT��band���ô�����detach */
    MMC_MM_DETACH_REASON_SRV_DOMAIN_DETACH     = 2,/* system configure�з����򴥷���detach */

    MMC_MM_PIF_DETACH_REASON_BUTT
};
typedef VOS_UINT32 MMC_MM_DETACH_REASON_ENUM_UINT32;
enum MMC_MM_ATTACH_TYPE_ENUM
{
    MMC_MM_ATTACH_TYPE_NULL          = 0,
    MMC_MM_ATTACH_TYPE_GPRS          = 1,
    MMC_MM_ATTACH_TYPE_IMSI          = 2,
    MMC_MM_ATTACH_TYPE_GPRS_IMSI     = 3,
    MMC_MM_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_MM_ATTACH_TYPE_ENUM_UINT32;



enum MMC_MM_LAU_REQ_REASON_ENUM
{
    MMC_MM_LAU_REQ_REASON_SOR          = 0,
    MMC_MM_LAU_REQ_REASON_BUTT
};
typedef VOS_UINT32 MMC_MM_LAU_REQ_REASON_ENUM_UINT32;



enum MMC_MM_SYS_INFO_TYPE_ENUM
{
    MMC_MM_SYS_INFO_TYPE_OTA           = 0,                /* ��ǰ��ota */
    MMC_MM_SYS_INFO_TYPE_SYS           = 1,                /* ��ǰ��ϵͳ��Ϣ */
    MMC_MM_SYS_INFO_TYPE_BUTT
};
typedef VOS_UINT8 MMC_MM_SYS_INFO_TYPE_ENUM_UINT8;

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
/* ԭ��MMCMM_SYS_INFO_IND�Ľṹ�� */
#ifndef _PLMN_ID_
#define _PLMN_ID_
    typedef struct
    {
        VOS_UINT32                               ulMcc;                                  /* MCC,3 bytes                              */
        VOS_UINT32                               ulMnc;                                  /* MNC,2 or 3 bytes                         */
    }MM_PLMN_ID_STRU;
#endif
#ifndef _LAI_
#define _LAI_
    typedef struct
    {
        MM_PLMN_ID_STRU                     PlmnId;
        VOS_UINT32                               ulLac;                                  /* BIT STRING(SIZE(16))                     */
    }MM_LAI_STRU;
#endif


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulMask;                                 /* ���¸�IE����Ч��־                         */
    MMC_MM_SYS_INFO_TYPE_ENUM_UINT8     enSysInfoType;
    VOS_UINT8                           aucReserve1[3];
    MM_PLMN_ID_STRU                     PlmnId;                                 /* ��С������PLMN��ID                        */
    VOS_UINT32                          ulCsDrxLength;                          /* CS��DRX����ϵ��                           */
    VOS_UINT32                          ulPsDrxLength;                          /* PS��DRX����ϵ��                           */
    VOS_UINT32                          ulForbiddenFlg;                         /* �뱾С����صĽ�ֹ��Ϣ                */
    VOS_UINT32                          ulCellId;
    VOS_UINT16                          usLac;
    VOS_UINT8                           ucCnCommonSize;
    VOS_UINT8                           ucCsInfoSize;
    VOS_UINT8                           ucPsInfoSize;
    VOS_UINT8                           ucAttachDetach;
    VOS_UINT8                           ucLRTimerT3212;
    VOS_UINT8                           ucGprsSupportInd;
    VOS_UINT8                           ucRac;
    VOS_UINT8                           ucNetworkOperationMode;
    VOS_UINT8                           ucUserSpecificSearchFlg;                /* ��־�Ƿ񱾴�פ����С��Ϊ�û�ָ���������� 0: ��, 1: �� */
    VOS_UINT8                           ucCsChanged2UnBarFlg;                   /* �Ƿ�CS���barתΪ��bar: 0 �ޣ�1 �� */
    VOS_UINT8                           ucPsChanged2UnBarFlg;                   /* �Ƿ�PS���barתΪ��bar: 0 �ޣ�1 �� */
    VOS_UINT8                           aucReserve2[3];
}MMCMM_SYS_INFO_IND_STRU;


/* ԭ��MMCMM_COVERAGE_LOST_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
}MMCMM_COVERAGE_LOST_IND_STRU;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                            /*_H2ASN_Skip*/
    MM_MMC_LU_RESULT_ENUM_U32           enLuResult;                             /* LU���            */
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetType;                              /* ��ǰע����������� */
    VOS_UINT8                           ucIsComBined;                           /* �Ƿ�Ϊ����ע��   */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enRegFailCause;                         /* ����ʧ��ԭ��     */
    VOS_UINT32                          ulServiceStatus ;                       /* ����״̬          */
    VOS_UINT32                          ulCsUpdateStatus ;                      /* CS �����״̬     */
    VOS_UINT32                          ulLuAttemptCnt ;                        /* LU Attempt counter */
    MM_LAI_STRU                         stOldLai ;                              /* ��LAI              */
}MMMMC_CS_REG_RESULT_IND_STRU;

/* ��ϢMMCMM_INFO_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MM_INFO_IND_STRU    stMmInfo;                                           /* MM INFORMATION(GMM INFORMATION)          */
}MMCMM_INFO_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulCsServFlg;                                        /* CS��ҵ�����ޱ�־                         */
    VOS_UINT32                      ulEmcFlg;/* ��־�Ƿ��ǽ�������,��ulCsServFlgΪMM_CS_SERV_NOT_EXISTʱ�Ҵ˱�־ΪMM_TRUEʱ,������ֹPLMN���� */
}MMCMM_CM_SERVICE_IND_STRU;
/* A32D12977<== */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    MM_MMC_PLMN_SEARCH_TYPE_ENUM_U32    enPlmnSearchType;                           /* ָʾMM��MMC���͵��������� */
}MMCMM_PLMN_SEARCH_IND_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulReserve;                           /* ָʾMM��MMC���͵��������� */
}MMCMM_CSFB_ABORT_IND_STRU;

/* ��ϢMMCMM_CM_SERVICE_REJECT_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulCause;                                            /* ʧ��ԭ��                                 */
    VOS_UINT32                      ulServiceStatus ;
}MMCMM_CM_SERVICE_REJECT_IND_STRU;

/* ��ϢMMCMM_PLMN_SEARCH_INITIATED�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulReserve;                                          /* ����                                     */
} MMCMM_PLMN_SEARCH_INITIATED_STRU;

/* ��ϢMMCMM_ABORT_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
} MMCMM_REL_REQ_STRU;

/* ��ϢMMCMM_START_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
}MMCMM_START_REQ_STRU;

/* ɾ����ϢMMCMM_PLMN_USER_SEL_REQ�Ľṹ�� */

/* ��ϢMMCMM_START_CNF�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
} MMCMM_START_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    MMC_MM_DETACH_TYPE_ENUM_UINT32      enDetachType ;                         /* DETACH ���� */
    MMC_MM_DETACH_REASON_ENUM_UINT32    enDetachReason;
} MMCMM_DETACH_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    VOS_UINT32                          ulServiceStatus ;                       /* CS�����״̬ */
    /* Added by zwx247453 for CHR optimize ,2015-3-13 begin */
    VOS_UINT32                          ulDetachType;                           /* detach ���� */
    /* Added by zwx247453 for CHR optimize ,2015-3-13 end */
} MMCMM_DETACH_CNF_STRU;


typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enCsRestrictRegisterChange;         /* CSע�����޸ı���� */
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enPsRestrictRegisterChange;         /* PSע�����޸ı���� */
}MMCMM_W_AC_INFO_CHANGE_IND_STRU;

/* ��ϢMMCMM_POWER_OFF_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
} MMCMM_POWER_OFF_REQ_STRU;

/* ��ϢMMCMM_POWER_OFF_CNF�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
} MMCMM_POWER_OFF_CNF_STRU;

/* ��ϢMMCMM_REGISTER_INITIATION�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
} MMCMM_REGISTER_INITIATION_STRU;

/* ��ϢMMCMM_DEREGISTER_INITIATION�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserve;                                          /* ����                                     */
} MMCMM_DEREGISTER_INITIATION_STRU;

/* ��ϢMMCMM_RR_CONN_INFO_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulRrConnFlg ;
} MMCMM_RR_CONN_INFO_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMCMM_ATTACH_REQ_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : MMCMM_ATTACH_REQ��Ϣ�����ݽṹ
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    MMC_MM_ATTACH_TYPE_ENUM_UINT32      enAttachType;                           /* ע����������                                 */
} MMCMM_ATTACH_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    VOS_UINT32                          ulServiceStatus ;                       /* CS��ķ���״̬ */
}MMCMM_ATTACH_CNF_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulServiceStatus ;
} MMCMM_SERVICE_STATUS_IND_STRU;

/* ��ϢMMCMM_ MODE_CHANGE_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                                      /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MML_MS_MODE_ENUM_UINT8  enMsMode;
    VOS_UINT8                   aucReservel[3];
} MMCMM_MODE_CHANGE_REQ_STRU;

/* ��Ϣ MMCMM_REGISTER_STATE_CHANGE_IND �ṹ�� */
typedef struct
{

    MSG_HEADER_STRU             stMsgHeader;                                            /*_H2ASN_Skip*/
    VOS_UINT8                   MmRegState;
    VOS_UINT8                   aucReservel[3];
}MMCMM_REGISTER_STATE_CHANGE_IND_ST;

/* ��Ϣ MMCMM_GSM_SYS_INFO_IND �ṹ�� */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU    stPlmnId;                     /* ��С��PLMN ID */
    VOS_UINT32          ulCellId;
    VOS_UINT32          ulForbiddenFlg;               /* �뱾С����صĽ�ֹ��Ϣ                     */
    VOS_UINT16          usLac;                        /* [0x0001��0xFFFE] λ������  */
    VOS_UINT8           ucAttachDetach;               /* [0-1] ����֪ͨMS���ڱ�С�����Ƿ��������IMSI��Ϻͷ����������:
                                                         0��ʾ�������ֻ�����IMSI���źͷ�����̣�
                                                         1���ʾ�ֻ������������źͷ�����̣�message origin:SI3,PSI2 */
    VOS_UINT8           ucLRTimerT3212;               /* [0-255] ����λ�ø��¶�ʱ��,ȷ�����ֻ���������λ�ø��µ�Ƶ��,
                                                         ÿ1����λ��ʾ6���ӵ�ʱ�䣬Ϊ0���ʾ������λ�ø��£�message origin:SI3,PSI2 */

    VOS_UINT8           ucGprsSupportInd;             /* [0-1] GPRS֧��ָʾ:0-��֧��;1-֧��*/
    VOS_UINT8           ucRac;                        /* ·��������*/
    VOS_UINT8           ucNetworkOperationMode;       /*   ��������ģʽ:
                                                           0-��Ч;
                                                           1-��������ģʽI;
                                                           2-��������ģʽII;
                                                           3-��������ģʽIII; */
    VOS_UINT8           ucMsrRelease;                 /* [0-1] 0 MSC is Release '98 or older
                                                               1 MSC is Release '99 onwards */


    VOS_UINT8           ucUserSpecificSearchFlg;     /* ��־�Ƿ񱾴�פ����С��Ϊ�û�ָ���������� : 0: �� 1: �� */

    RRC_NAS_RESTRICTION_UN              unAcInfo;

    VOS_UINT8           ucCsChanged2UnBarFlg;             /* �Ƿ�CS���barתΪ��bar: 0 �ޣ�1 �� */
    VOS_UINT8           ucPsChanged2UnBarFlg;             /* �Ƿ�PS���barתΪ��bar: 0 �ޣ�1 �� */

}MMCMM_GSM_SYS_INFO_IND_ST;


/* BEGIN: Added by liuyang id:48197, 2006/3/28   PN:A32D02606*/
/*MMCMM_RR_REL_IND��Ϣ�ṹ����*/
/* MMCMM_RR_REL_IND_ST ulRrcConnStatusȡֵ */
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                  /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                      ulCnDomainId;                                               /* �ͷ��������ӵ�������                     */
    VOS_UINT32                      ulRrcConnStatus;                                            /* �ͷ��������Ӻ�RRC�����Ƿ���ڣ�ȡֵ���궨��             */
    VOS_UINT32                      ulRelCause;                                                 /* �����ͷ�ԭ��ȡֵ���궨��               */
}MMCMM_RR_REL_IND_ST;
/* END:   Added by liuyang id:48197, 2006/3/28 */

/* BEGIN: Added by liuyang id:48197, 2006/5/4   PN:A32D03487*/
/*��Ϣ MMCMM_SUSPEND_RSP �ṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
}MMCMM_SUSPEND_RSP_ST;
/* END:   Added by liuyang id:48197, 2006/5/4   PN:A32D03487*/


/*��Ϣ MMCMM_RESUME_RSP�ṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
}MMCMM_RESUME_RSP_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_RESUME_RESULT_ENUM_UINT8        ucCsResumeResult;                       /* CS���л���� */
    MMC_RESUME_RESULT_ENUM_UINT8        ucPsResumeResult;                       /* PS���л���� */
    MMC_RESUME_ORIGEN_ENUM_UINT8        ucResumeOrigen;                         /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8                           ucCsSigExistFlg;                        /* CS�������Ӵ��ڱ�� */
}MMCMM_RESUME_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /*_H2ASN_Skip*/
    MMC_SUSPEND_CAUSE_ENUM_UINT8        ucSuspendCause;                         /* ����ԭ�� */
    MMC_SUSPEND_ORIGEN_UINT8            ucSuspendOrigen;                        /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA*/
    MMC_SUSPEND_DESTINATION_UINT8       ucSuspendDestination;                   /* �����Ŀ�ķ� */
    VOS_UINT8                           aucReserve1[1];                         /* ���� */
    NAS_RRC_RE_TX_MSG_STRU              astReTxMsg[NAS_RRC_MAX_RE_TX_MSG_NUM];  /* �����ط�����Ϣ */
}MMCMM_SUSPEND_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;                              /*_H2ASN_Skip*/
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enAbortCause;                           /* Abortԭ�� */
    VOS_UINT8                           aucReserve1[2];                         /* ���� */
}MMMMC_ABORT_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                          /* ��Ϣͷ  */ /*_H2ASN_Skip*/
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16       enSimAuthFailValue;
    VOS_UINT8                               ucReservel;
    NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8    enSrvDomain;
}MMCMM_SIM_AUTH_FAIL_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                 MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT8                       aucRsv[4];                                          /* ����                                     */
}MMCMM_SRVCC_INFO_NOTIFY_STRU;




typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;          /*_H2ASN_Skip*/
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNetRatType;       /* NAS RAT */
    VOS_UINT8                           aucReserve1[3];     /* ���� */
}MMCMM_RAT_CHANGE_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                         /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    MMC_MM_LAU_REQ_REASON_ENUM_UINT32   enLauReqReason;                                    /* MMC����LAU��ԭ��                         */
}MMCMM_LAU_REQ_STRU;


#if (FEATURE_ON == FEATURE_LTE)

typedef  LMM_MMC_ATTACH_IND_STRU MMCMM_LMM_ATTACH_IND_STRU;


typedef  LMM_MMC_TAU_RESULT_IND_STRU MMCMM_LMM_TAU_RESULT_IND_STRU;



typedef  LMM_MMC_DETACH_IND_STRU MMCMM_LMM_MT_DETACH_IND_STRU;


typedef  LMM_MMC_SERVICE_RESULT_IND_STRU MMCMM_LMM_SERVICE_RESULT_IND_STRU;


typedef  LMM_MMC_DETACH_CNF_STRU MMCMM_LMM_MO_DETACH_IND_STRU;


typedef  LMM_MMC_DETACH_IND_STRU MMCMM_LMM_LOCAL_DETACH_IND_STRU;


typedef  LMM_MMC_SYS_INFO_IND_STRU MMC_MM_LTE_SYS_INFO_IND_STRU;



typedef  LMM_MMC_TIMER_STATE_NOTIFY_STRU MMCMM_LMM_TIMER_STATE_NOTIFY_STRU;

#endif

/*****************************************************************************
  8 UNION����
*****************************************************************************/

/*****************************************************************************
  9 OTHERS����
*****************************************************************************/
/*****************************************************************************
  H2ASN������Ϣ�ṹ����
*****************************************************************************/
typedef struct
{
    MMC_MM_MSG_TYPE_ENUM_UINT16         enMsgID;    /*_H2ASN_MsgChoice_Export MMC_MM_MSG_TYPE_ENUM_UINT16*/
                                                    /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.1ʹ��MMC_MM_MSG_TYPE_ENUM_UINT16 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMC_MM_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MMC_MM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMC_MM_MSG_DATA                    stMsgData;
}MmcMmInterface_MSG;

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif/* __cpluscplus */

#endif



