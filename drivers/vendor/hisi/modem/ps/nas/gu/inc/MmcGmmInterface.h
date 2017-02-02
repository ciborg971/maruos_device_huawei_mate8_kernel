
#ifndef _MMC_GMM_INTERFACE_H_
#define _MMC_GMM_INTERFACE_H_


/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "NasCommDef.h"
#include "Nasrrcinterface.h"
#include "NasMmlCtx.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#pragma pack(4)
    /*_H2ASN_Include wuepsosa_msg.h*/


/*****************************************************************************
  2 �궨��
*****************************************************************************/
/* �����нṹ���е�ulServiceStsʹ�����µĶ��� */
#define     MMC_GMM_NORMAL_SERVICE                      MM_COM_SRVST_NORMAL_SERVICE
#define     MMC_GMM_LIMITED_SERVICE                     MM_COM_SRVST_LIMITED_SERVICE
#define     MMC_GMM_NO_IMSI                             MM_COM_SRVST_NO_IMSI
#define     MMC_GMM_NO_SERVICE                          MM_COM_SRVST_NO_SERVICE

#define     MMC_GMM_SYS_MSK_PLMN                        RRC_NAS_SYS_MSK_PLMN
#define     MMC_GMM_SYS_MSK_PS_DRX                      RRC_NAS_SYS_MSK_PS_DRX
/* Added by cxd 05-04-21 begin : for interface change */
#define     MMC_GMM_SYS_MSK_CSPS_INFO                   RRC_NAS_SYS_MSK_CSPS_INFO
/* Added by cxd 05-04-21 end   */

#define     MMC_GMM_NO_FORBIDDEN                        0x0000                  /* �����κν�ֹ�б���                         */
#define     MMC_GMM_FORBIDDEN_PLMN                      0x0001                  /* ��forbidden PLMN list��                  */
#define     MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS             0x0002                  /* ��forbidden PLMN for GPRS list��         */
#define     MMC_GMM_FORBIDDEN_LA_FOR_ROAM               0x0004                  /* ��forbidden LA for roaming��             */
#define     MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS       0x0008                  /* ��forbidden LA for regional provision of service�� */
#define     MMC_GMM_MS_ID_TYPE_NULL                     0
#define     MMC_GMM_MS_ID_TYPE_IMSI                     1
#define     MMC_GMM_MS_ID_TYPE_TMSI                     2

#define     MMC_GMM_ATTACH_RESLUT_PS_ONLY               0                       /* GPRS only attached                       */
#define     MMC_GMM_ATTACH_RESLUT_COMBINED              1                       /* Combined attached                        */

#define     MMC_GMM_MAX_EQUPLMN_NUM                     15                      /* ��ЧPLMN��������                        */

#define     MMC_GMM_REAL_PROCEDURE                      0                       /* ������������                             */
#define     MMC_GMM_UNREAL_PROCEDURE                    1                       /* û��������������                         */

/* ԭ��MMCGMM_PDP_STATUS_IND�Ľṹ�� */
#define     MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST        0                       /* �������Ѽ����PDP context                */
#define     MMC_GMM_ACTIVE_PDP_CONTEXT_EXIST            1                       /* �����Ѽ����PDP context                  */

#define     MMC_GMM_NO_TIMER_EXPIRED                    0
#define     MMC_GMM_T3312_EXPIRED                       1
#define     MMC_GMM_T3311_EXPIRED                       2
#define     MMC_GMM_T3302_EXPIRED                       3
#define     MMC_GMM_T3330_EXPIRED                       4

#define     MMC_GMM_SIGNALING_STATUS_ABSENT             0                       /* ������PS����������                        */
#define     MMC_GMM_SIGNALING_STATUS_PRESENT            1                       /* ����PS����������                          */
#define     MMC_GMM_SIGNALING_STATUS_ESTING             2                       /* ���ڽ���PS����������                       */

#define     MMCGMM_GSM_NO_FORBIDDEN                     0x0000                    /* �����κν�ֹ�б���                         */
#define     MMCGMM_GSM_FORBIDDEN_PLMN                   0x0001                    /* ��forbidden PLMN list��                  */
#define     MMCGMM_GSM_FORBIDDEN_PLMN_FOR_GPRS          0x0002                    /* ��forbidden PLMN for GPRS list��         */
#define     MMCGMM_GSM_FORBIDDEN_LA_FOR_ROAM            0x0004                    /* ��forbidden LA for roaming��             */
#define     MMCGMM_GSM_FORBIDDEN_LA_FOR_REG_PRVS_SVS    0x0008                    /* ��forbidden LA for regional provision of service�� */

#define     MMC_GMM_EMERGENCY_NUM_MAX_LEN               LMM_MMC_EMERGENCY_NUM_MAX_LEN
#define     MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS      LMM_MMC_EMERGENCY_NUM_LIST_MAX_RECORDS /* ���������ֵ */

/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/

enum MMC_GMM_MSG_TYPE_ENUM
{
    /* ��Ϣ���� */                      /*��ϢID*/  /* ��ע */
/* MMC����GMM��ԭ�� */
    MMCGMM_SYS_INFO_IND                         = 0,    /* _H2ASN_MsgChoice MMCGMM_SYS_INFO_IND_STRU */
    MMCGMM_COVERAGE_LOST_IND                    = 2,    /* _H2ASN_MsgChoice MMCGMM_COVERAGE_LOST_IND_STRU */
    MMCGMM_POWER_OFF_REQ                        = 4,    /* _H2ASN_MsgChoice MMCGMM_POWER_OFF_REQ_STRU */
    MMCGMM_PLMN_SEARCH_INITIATED                = 6,    /* _H2ASN_MsgChoice MMCGMM_PLMN_SEARCH_INITIATED_STRU */
    MMCGMM_START_REQ                            = 8,    /* _H2ASN_MsgChoice MMCGMM_START_REQ_STRU */
    MMCGMM_PLMN_USER_SEL_REQ                    = 10,   /* _H2ASN_MsgChoice MMCGMM_PLMN_USER_SEL_REQ_STRU */
    MMCGMM_DETACH_REQ                           = 12,   /* _H2ASN_MsgChoice MMCGMM_DETACH_REQ_STRU */

    MMCGMM_REGISTER_INITIATION                  = 14,   /* _H2ASN_MsgChoice MMCGMM_REGISTER_INITIATION_STRU */
    MMCGMM_ATTACH_REQ                           = 16,   /* _H2ASN_MsgChoice MMCGMM_ATTACH_REQ_STRU */
    MMCGMM_MODE_CHANGE_REQ                      = 18,   /* _H2ASN_MsgChoice MMCGMM_MODE_CHANGE_REQ_STRU */

    MMCGMM_EMERGENCY_NUM_LIST_IND               = 20,   /* _H2ASN_MsgChoice MMCGMM_EMERGENCY_NUM_LIST_IND */

    /* BEGIN: Added by liuyang, id:48197, 2005/11/1 */
    MMCGMM_SUSPEND_IND                          = 22,   /* _H2ASN_MsgChoice MMCGMM_SUSPEND_IND_ST */
    MMCGMM_RESUME_IND                           = 24,   /* _H2ASN_MsgChoice MMCGMM_RESUME_IND_ST */
    MMCGMM_GSM_SYS_INFO_IND                     = 26,   /* _H2ASN_MsgChoice MMCGMM_GSM_SYS_INFO_IND_ST */
    MMCGMM_REL_REQ                              = 28,   /* _H2ASN_MsgChoice MMCGMM_REL_REQ_STRU */
    /* END:   Added by liuyang, id:48197, 2005/11/1 */

    MMCGMM_LTE_SYS_INFO_IND                     = 30,   /* _H2ASN_MsgChoice MMC_GMM_LTE_SYS_INFO_IND_STRU */

    /* MMC����MM LMM��ע���� */
    MMCGMM_LMM_ATTACH_IND                       = 32,   /* _H2ASN_MsgChoice MMCGMM_LMM_ATTACH_IND_STRU */
    MMCGMM_LMM_TAU_RESULT_IND                   = 34,   /* _H2ASN_MsgChoice MMCGMM_LMM_TAU_RESULT_IND_STRU */
    MMCGMM_LMM_MT_DETACH_IND                    = 36,   /* _H2ASN_MsgChoice MMCGMM_LMM_MT_DETACH_IND_STRU */
    MMCGMM_LMM_SERVICE_RESULT_IND               = 38,   /* _H2ASN_MsgChoice MMCGMM_LMM_SERVICE_RESULT_IND_STRU */

    MMCGMM_LMM_MO_DETACH_IND                    = 40,   /* _H2ASN_MsgChoice MMCGMM_LMM_MO_DETACH_IND_STRU */
    MMCGMM_LMM_LOCAL_DETACH_IND                 = 42,   /* _H2ASN_MsgChoice MMMCGMM_LMM_LOCAL_DETACH_IND_STRU */

    MMCGMM_LMM_STATUS_IND                       = 44,   /* _H2ASN_MsgChoice MMCGMM_LMM_STATUS_IND_STRU */
    MMCGMM_W_AC_INFO_CHANGE_IND                 = 46,   /* _H2ASN_MsgChoice MMCGMM_W_AC_INFO_CHANGE_IND_STRU */

    MMCGMM_LMM_TIMER_STATE_NOTIFY               = 48, /* _H2ASN_MsgChoice MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU */

    MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY           = 50,   /* _H2ASN_MsgChoice MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU */

    /* MMC����GMM����ϢID��ż�� */

    /* GMM���͸�MMC��ԭ�� */
    MMCGMM_INFO_IND                             = 1,    /* _H2ASN_MsgChoice MMCGMM_INFO_IND_STRU */
    MMCGMM_PDP_STATUS_IND                       = 3,    /* _H2ASN_MsgChoice MMCGMM_PDP_STATUS_IND_STRU */
    MMCGMM_POWER_OFF_CNF                        = 5,    /* _H2ASN_MsgChoice MMCGMM_POWER_OFF_CNF_STRU */
    MMCGMM_NETWORK_DETACH_IND                   = 7,    /* _H2ASN_MsgChoice MMCGMM_NETWORK_DETACH_IND_STRU */
    MMCGMM_DETACH_CNF                           = 9,    /* _H2ASN_MsgChoice MMCGMM_DETACH_CNF_STRU */
    MMCGMM_START_CNF                            = 11,   /* _H2ASN_MsgChoice MMCGMM_START_CNF_STRU */
    MMCGMM_LOCAL_DETACH_IND                     = 13,   /* _H2ASN_MsgChoice MMCGMM_LOCAL_DETACH_IND_STRU */
    MMCGMM_GPRS_SERVICE_IND                     = 15,   /* _H2ASN_MsgChoice MMCGMM_GPRS_SERVICE_IND_STRU */
    MMCGMM_SIGNALING_STATUS_IND                 = 17,   /* _H2ASN_MsgChoice MMCGMM_SIGNALING_STATUS_IND_STRU */
    MMCGMM_SUSPEND_RSP                          = 19,   /* _H2ASN_MsgChoice MMCGMM_SUSPEND_RSP_ST */
    MMCGMM_RESUME_RSP                           = 21,   /* _H2ASN_MsgChoice MMCGMM_RESUME_RSP_ST */
    MMCGMM_REGISTER_STATE_CHANGE_IND            = 23,   /* _H2ASN_MsgChoice MMCGMM_REGISTER_STATE_CHANGE_IND_ST */

    MMCGMM_TBF_REL_IND                          = 27,   /* _H2ASN_MsgChoice MMCGMM_TBF_REL_IND_STRU */

    MMCGMM_TIN_TYPE_IND                         = 29,   /* _H2ASN_MsgChoice MMCGMM_TIN_TYPE_IND_STRU */

    MMCGMM_ATTACH_CNF                           = 33,   /* _H2ASN_MsgChoice MMCGMM_ATTACH_CNF_STRU */
    GMMMMC_PS_REG_RESULT_IND                    = 35,   /* _H2ASN_MsgChoice GMMMMC_PS_REG_RESULT_IND_STRU */
    GMMMMC_SERVICE_REQUEST_RESULT_IND           = 37,   /* _H2ASN_MsgChoice GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU */

    GMMMMC_CIPHER_INFO_IND                      = 39,   /* _H2ASN_MsgChoice MMC_GMM_CIPHER_INFO_IND_STRU */
    MMCGMM_SIM_AUTH_FAIL_IND                    = 41,  /* _H2ASN_MsgChoice MMCGMM_SIM_AUTH_FAIL_IND_STRU */

    GMMMMC_NETWORK_CAPABILITY_INFO_IND          = 43,   /* _H2ASN_MsgChoice GMMMMC_NETWORK_CAPABILITY_INFO_IND */

    /* GMM����MMC����ϢID������ */

    MMCGMM_MSG_TYPE_BUTT
};
typedef VOS_UINT16 MMC_GMM_MSG_TYPE_ENUM_UINT16;


enum NAS_MMC_GMM_NT_DETACH_ENUM
{
    NAS_MMC_GMM_NT_DETACH_REATTACH      = 1,
    NAS_MMC_GMM_NT_DETACH_NOATTACH      = 2,
    NAS_MMC_GMM_NT_DETACH_IMSI          = 3,
    NAS_MMC_GMM_NT_DETACH_BUTT
};
typedef VOS_UINT32 NAS_MMC_GMM_NT_DETACH_ENUM_U32;


enum GMM_MMC_ACTION_TYPE_ENUM
{
    GMM_MMC_ACTION_RAU                  = 0,
    GMM_MMC_ACTION_ATTACH               = 1,
    GMM_MMC_ACTION_COMBINED_RAU         = 2,
    GMM_MMC_ACTION_COMBINED_ATTACH      = 3,
    GMM_MMC_ACTION_PERIODC_RAU          = 4,
    GMM_MMC_ACTION_BUTT
};
typedef VOS_UINT32 GMM_MMC_ACTION_TYPE_ENUM_U32;


enum GMM_MMC_ACTION_RESULT_ENUM
{
    GMM_MMC_ACTION_RESULT_SUCCESS    = 0,    /*ACTION�ɹ�*/
    GMM_MMC_ACTION_RESULT_FAILURE    = 1,    /*ACTIONʧ��*/
    GMM_MMC_ACTION_RESULT_BUTT
};
typedef VOS_UINT32 GMM_MMC_ACTION_RESULT_ENUM_U32;


enum GMM_MMC_REG_DOMAIN_ENUM
{
    GMM_MMC_REG_DOMAIN_PS    = 0x00,                                            /* ע������ΪPS�� */
    GMM_MMC_REG_DOMAIN_PS_CS = 0x01,                                            /* ע������ΪCS+PS�� */
    GMM_MMC_REG_DOMAIN_BUTT
};
typedef VOS_UINT32 GMM_MMC_REG_DOMAIN_ENUM_UINT32;


enum GMM_MMC_ACTION_PROC_ENUM
{
    GMM_MMC_ACTION_PROC_TRUE     = 0,    /*������������*/
    GMM_MMC_ACTION_PROC_FALSE    = 1,    /*û��������������*/
    GMM_MMC_ACTION_PROC_BUTT
};
typedef VOS_UINT32 GMM_MMC_ACTION_PROC_ENUM_U32;


enum MMC_GMM_DETACH_TYPE_ENUM
{
    MMC_GMM_PS_DETACH        = 1,
    MMC_GMM_CS_DETACH        = 2,
    MMC_GMM_PS_CS_DETACH     = 3,
    MMC_GMM_DETACH_BUTT
};
typedef VOS_UINT32 MMC_GMM_DETACH_TYPE_ENUM_UINT32;


enum MMC_GMM_DETACH_REASON_ENUM
{
    MMC_GMM_DETACH_CAUSE_USER_DETACH          = 0,/* �û�������detach���� */
    MMC_GMM_DETACH_CAUSE_RAT_OR_BAND_DETACH   = 1,/* system configure��RAT��Band���ô�����detach */
    MMC_GMM_DETACH_CAUSE_SRV_DOMAIN_CHANGE    = 2,/* ����仯�����detach */

    MMC_GMM_PIF_DETACH_REASON_BUTT
};
typedef VOS_UINT32 MMC_GMM_DETACH_REASON_ENUM_UINT32;
enum MMC_GMM_ATTACH_TYPE_ENUM
{
    MMC_GMM_ATTACH_TYPE_NULL          = 0,
    MMC_GMM_ATTACH_TYPE_GPRS          = 1,
    MMC_GMM_ATTACH_TYPE_IMSI          = 2,
    MMC_GMM_ATTACH_TYPE_GPRS_IMSI     = 3,
    MMC_GMM_ATTACH_TYPE_BUTT
};
typedef VOS_UINT32 MMC_GMM_ATTACH_TYPE_ENUM_UINT32;

enum MMCGMM_SGSN_REL_VER_ENUM
{
    MMCGMM_SGSN_RELEASE98_OR_OLDER        = 0,
    MMCGMM_SGSN_RELEASE99_ONWARDS         = 1,
    MMCGMM_SGSN_REL_VER_BUTT
};
typedef VOS_UINT8   MMCGMM_SGSN_REL_VER_ENUM_U8;


enum NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM
{
    NAS_MMC_GMM_GPRS_SERVICE_ATTACH               = 0,
    NAS_MMC_GMM_GPRS_SERVICE_PAGING               = 1,
    NAS_MMC_GMM_GPRS_SERVICE_PDPACT               = 2,
    NAS_MMC_GMM_GPRS_SERVICE_DATA                 = 3,
    NAS_MMC_GMM_GPRS_SERVICE_BUTT
};
typedef VOS_UINT32   NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM_UINT32;




enum GMM_MMC_NW_EMC_BS_CAP_ENUM
{
    GMM_MMC_NW_EMC_BS_NOT_SUPPORTED       = 0,
    GMM_MMC_NW_EMC_BS_SUPPORTED           = 1,

    GMM_MMC_NW_EMC_BS_BUTT
};
typedef VOS_UINT8 GMM_MMC_NW_EMC_BS_CAP_ENUM_UINT8;


enum GMM_MMC_LTE_CS_CAPBILITY_ENUM
{
    GMM_MMC_LTE_CS_CAPBILITY_NO_ADDITION_INFO  = 0,
    GMM_MMC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER   = 1,
    GMM_MMC_LTE_CS_CAPBILITY_SMS_ONLY          = 2,
    GMM_MMC_LTE_CS_CAPBILITY_NOT_SUPPORTED     = 3,

    GMM_MMC_LTE_CS_CAPBILITY_BUTT
};
typedef VOS_UINT8 GMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT8;

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
/* ԭ��MMCGMM_SYS_INFO_IND�Ľṹ�� */
typedef struct
{
    /* Լ�������մ�ULONG������ֽڿ�ʼ���θ��ֽ�Ϊֹ��˳�����δ洢MCC��MNC��digit1��digit2��digit3 */
    VOS_UINT32             ulMcc;                                                    /* MCC,3 bytes                              */
    VOS_UINT32             ulMnc;                                                    /* MNC,2 or 3 bytes                         */
}MMCGMM_PLMN_ID_STRU;


typedef struct
{

    MSG_HEADER_STRU             MsgHeader;                                      /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                  ulCellId;
    VOS_UINT32                  ulCnCommonSize;                                 /* CN Common��Ϣ���ֽڳ���                    *
                                                                                 * 0��������CN Common NAS System Infomation  */
    VOS_UINT8                   aucCnCommonInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP];     /* aulCnCommonInfo[0] b0 - b7����һ�ֽڣ�    *
                                                                                 * aulCnCommonInfo[0] b8 - b15���ڶ��ֽڣ�   *
                                                                                 * ...                                      *
                                                                                 * aulCnCommonInfo[1] b0 - b7�������ֽڣ�    *
                                                                                 * ...                                      */
    VOS_UINT32                  ulPsInfoSize;                                        /* PS�������Ϣ���ֽڳ���* * 0��CS����Ϣ������ */
    VOS_UINT32                  aulPsInfo[RRC_NAS_MAX_SIZE_NAS_GSM_MAP/4];           /* aulPsInfo[0] b0 - b7����һ�ֽڣ�          *
                                                                                 * aulPsInfo[0] b8 - b15���ڶ��ֽڣ�         *
                                                                                 * ...                                      *
                                                                                 * aulPsInfo[1] b0 - b7�������ֽڣ�          *
                                                                                 * ...                                      */

    VOS_UINT32                  ulMask;                                              /* ���¸�IE����Ч��־                         */

    MMCGMM_PLMN_ID_STRU         PlmnId;                                              /* ��С������PLMN��ID                        */
    VOS_UINT32                  ulPsDrxLength;                                       /* PS��DRX����ϵ��                           */


    VOS_UINT32                  ulForbiddenMask;                                     /* �Ƿ��ڽ�ֹ�б���                           */
    VOS_UINT32                  ulUserSrchFlg;          /* �Ƿ����û�ָ������ */


    VOS_UINT8                   ucCsChanged2UnBarFlg;             /* �Ƿ�CS���barתΪ��bar: 0 �ޣ�1 �� */
    VOS_UINT8                   ucPsChanged2UnBarFlg;             /* �Ƿ�PS���barתΪ��bar: 0 �ޣ�1 �� */
    VOS_UINT8                   aucReserve[2];

}MMCGMM_SYS_INFO_IND_STRU;

/* MMCGMM_SUSPEND_IND����Ϣ�ṹ */
/* ������ֵ��μ�RRMM_SUSPEND_IND_ST�е�˵�� */

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT8                           ucSuspendCause;                         /* ����ԭ�� */
    VOS_UINT8                           ucSuspendOrigen;                        /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA*/
    MMC_SUSPEND_DESTINATION_UINT8       ucSuspendDestination;                   /* �����Ŀ�ķ� */
    VOS_UINT8                           aucReserve1[1];                         /* ���� */
}MMCGMM_SUSPEND_IND_ST;

/* MMCGMM_RESUME_IND����Ϣ�ṹ */
/* ������ֵ��μ�RRMM_RESUME_IND_ST�е�˵�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT8               ucCsResumeResult;                                   /* CS���л���� */
    VOS_UINT8               ucPsResumeResult;                                   /* PS���л���� */
    VOS_UINT8               ucResumeOrigen;                                     /* ��Ϣ���𷽣�RRMM_ORIGEN_GSM:GSM��RRMM_ORIGEN_WCDMA:WCDMA */
    VOS_UINT8               ucPsSigExistFlg;                                    /* CS�������Ӵ��ڱ�� */
}MMCGMM_RESUME_IND_ST;

/* MMCGMM_SUSPEND_RSP����Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT8               ucResult;                                           /*WRRC/RR��Ҫ�������ʧ�ܵ������NAS����Щ����¹����ʧ��*/
    VOS_UINT8               aucReserve1[3];                                     /* ���� */
}MMCGMM_SUSPEND_RSP_ST;

/* MMCGMM_RESUME_RSP����Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                                         /* ����*/
}MMCGMM_RESUME_RSP_ST;

/* MMCGMM_REGISTER_STATE_CHANGE_IND����Ϣ�ṹ */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    VOS_UINT8               GmmRegState;

    VOS_UINT8               aucReservel[3];
}MMCGMM_REGISTER_STATE_CHANGE_IND_ST;

/* ԭ��MMCGMM_COVERAGE_LOST_IND�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
}MMCGMM_COVERAGE_LOST_IND_STRU;

/* ԭ��MMCGMM_COMBINED_ATTACH_ACCEPTED�Ľṹ�� */
typedef struct
{
    VOS_UINT32            ulIdType;

    VOS_UINT8            aucTmsi[4];
} MMC_GMM_MS_IDENTITY_STRU;


/* ԭ��MMCGMM_NETWORK_DETACH_IND�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU             MsgHeader;                                      /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/


    VOS_UINT32                   ulDetachType;                                       /* Detach����                               */

    VOS_UINT32                   ulDetachCause;                                      /* Detachԭ��                               */


    VOS_UINT32                  ulServiceSts;                                        /* ����״̬                                 */


}MMCGMM_NETWORK_DETACH_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                           MsgHeader;                        /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    GMM_MMC_ACTION_TYPE_ENUM_U32              enGmmActionType;
    GMM_MMC_ACTION_RESULT_ENUM_U32            enActionResult;


	GMM_MMC_REG_DOMAIN_ENUM_UINT32        	  enReqDomain;                     /* ��ǰע��Ľ����Ps Only��CS_PS */
	GMM_MMC_REG_DOMAIN_ENUM_UINT32        	  enRsltDomain;                     /* ��ǰע��Ľ����Ps Only��CS_PS */


    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16        enRegFailCause;                   /* ����ʧ��ԭ��                             */
	NAS_MML_NET_RAT_TYPE_ENUM_UINT8           enNetType;                        /* ��ǰע����������� */
    VOS_UINT8                                 ucReserved;
    VOS_UINT32                                ulRegCounter;                     /* Attach attempt counter                   */
    VOS_UINT32                                ulServiceStatus;                  /* ����״̬                                 */
}GMMMMC_PS_REG_RESULT_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                           MsgHeader;                        /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    GMM_MMC_ACTION_RESULT_ENUM_U32            enActionResult;                   /* �����Ľ�� */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16        enRegFailCause;                   /* ����ʧ��ԭ�� */
    VOS_UINT32                                ulServiceSts;                     /* ����״̬ */
}GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                        MsgHeader;          /* _H2ASN_Skip */
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8    enNwImsVoCap;
    GMM_MMC_NW_EMC_BS_CAP_ENUM_UINT8       enNwEmcBsCap;
    GMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT8    enLteCsCap;
    VOS_UINT8                              aucReserve[1];
}GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU;
typedef struct
{

    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    MMC_GMM_DETACH_TYPE_ENUM_UINT32     enDetachType;                           /* detachԭ��                               */

    MMC_GMM_DETACH_REASON_ENUM_UINT32   enDetachReason;
} MMCGMM_DETACH_REQ_STRU;
typedef struct
{

    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    VOS_UINT32                          ulServiceSts;                           /* PS����״̬                                 */

    VOS_UINT32                          ulDetachType;                           /* detach ���� */
}MMCGMM_DETACH_CNF_STRU;

/* ԭ��MMCGMM_POWER_OFF_REQ�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
} MMCGMM_POWER_OFF_REQ_STRU;

/* ԭ��MMCGMM_POWER_OFF_CNF�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
} MMCGMM_POWER_OFF_CNF_STRU;

/* ��ϢMMCGMM_INFO_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU             MsgHeader;                                      /*_H2ASN_Skip*/

    NAS_MM_INFO_IND_STRU        stMmInfo;
}MMCGMM_INFO_IND_STRU;

typedef struct
{

    MSG_HEADER_STRU            MsgHeader;                                       /* ��Ϣͷ    */ /*_H2ASN_Skip*/

    VOS_UINT32                  ulPdpStatusFlg;                                 /* �����Ѽ����PDP context��־              */
}MMCGMM_PDP_STATUS_IND_STRU;

/* ��ϢMMCGMM_PLMN_SEARCH_INITIATED�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU        MsgHeader;                                           /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                  ulReserve;                                      /* ����                                     */
} MMCGMM_PLMN_SEARCH_INITIATED_STRU;

/* ��ϢMMCGMM_ABORT_REQ�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
} MMCGMM_REL_REQ_STRU;

/* ��ϢMMCGMM_START_REQ�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU             MsgHeader;                                       /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                  ulReserved;                     /* ����*/
}MMCGMM_START_REQ_STRU;

/* ��ϢMMCGMM_START_CNF�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
}MMCGMM_START_CNF_STRU;

/* ��ϢMMCGMM_PLMN_USER_SEL_REQ�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
}MMCGMM_PLMN_USER_SEL_REQ_STRU;

/* ��ϢMMCGMM_LOCAL_DETACH_IND�Ľṹ�� */
typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/

    VOS_UINT32               ulDetachCause ;                                         /* detachԭ��                               */


    VOS_UINT32                  ulServiceSts;                                        /* ����״̬                                 */

} MMCGMM_LOCAL_DETACH_IND_STRU;

typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
} MMCGMM_REGISTER_INITIATION_STRU;

typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32              ulReserved;                     /* ����*/
} MMCGMM_TBF_REL_IND_STRU;

typedef struct
{

    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/

    VOS_UINT32                   ulSignalingSts;                                     /* PS����������״̬                          */
} MMCGMM_SIGNALING_STATUS_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    MMC_GMM_ATTACH_TYPE_ENUM_UINT32     enAttachType;                           /* ע����������                                */
} MMCGMM_ATTACH_REQ_STRU;
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                            /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    VOS_UINT32                          ulOpid;                                 /* MMA����ʹ�ã���¼ATTACH��� */
    VOS_UINT32                          ulServiceStatus ;                       /* PS�����״̬ */
}MMCGMM_ATTACH_CNF_STRU;
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                              /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enCsRestrictRegisterChange;         /* CSע�����޸ı���� */
    NAS_MML_RESTRICTION_CHANGE_ENUM_UINT8   enPsRestrictRegisterChange;         /* PSע�����޸ı���� */
}MMCGMM_W_AC_INFO_CHANGE_IND_STRU;

/*****************************************************************************
 �ṹ��    : MMCGMM_MODE_CHANGE_REQ_STRU
 �ṹ˵��  : MMCGMM_MODE_CHANGE_REQ_STRU��Ϣ�����ݽṹ
 1.��    ��   : 2011��7��01��
   ��    ��   : zhoujun \40661
   �޸�����   : �ֻ�ģʽ�޸�
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                                          /* ��Ϣͷ                                    */ /*_H2ASN_Skip*/
    NAS_MML_MS_MODE_ENUM_UINT8          enMsMode;                                           /* �û�ģʽ                                 */
    VOS_UINT8                           aucReservel[3];
} MMCGMM_MODE_CHANGE_REQ_STRU;



typedef struct
{
    MSG_HEADER_STRU                             MsgHeader;                      /* ��Ϣͷ                                    */ /*_H2ASN_Skip*/
} MMCGMM_VOICE_DOMAIN_CHANGE_NOTIFY_STRU;


/* ��Ϣ MMCGMM_GSM_SYS_INFO_IND �ṹ�� */
typedef struct
{
    MSG_HEADER_STRU     MsgHeader;                                              /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    RRC_PLMN_ID_STRU    stPlmnId;                     /* ��С��PLMN ID */
    VOS_UINT32          ulForbiddenFlg;               /* �뱾С����صĽ�ֹ��Ϣ                     */
    VOS_UINT16          usCellId;                     /* ��С�� ID  */
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
    VOS_UINT8           ucDrxTimerMax;                /* [0,1,2,4,8,16,32,64]s   */

    MMCGMM_SGSN_REL_VER_ENUM_U8    ucSgsnRelease;       /* [0-1] 0 SGSN is Release '98 or older
                                                              1 SGSN is Release '99 onwards */
    RRC_NAS_RESTRICTION_UN              unAcInfo;
    VOS_UINT32                      ulUserSrchFlg;


    VOS_UINT8                   ucCsChanged2UnBarFlg;             /* �Ƿ�CS���barתΪ��bar: 0 �ޣ�1 �� */
    VOS_UINT8                   ucPsChanged2UnBarFlg;             /* �Ƿ�PS���barתΪ��bar: 0 �ޣ�1 �� */
    VOS_UINT8                   aucReserve[2];

}MMCGMM_GSM_SYS_INFO_IND_ST;

/* ��ϢMMCGMM_SERVICE_STATUS_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/

    VOS_UINT32               ulServiceStatus ;
} MMCGMM_SERVICE_STATUS_IND_STRU;


/* ��ϢMMCGMM_GPRS_SERVICE_IND�Ľṹ�� */
typedef struct
{
    MSG_HEADER_STRU         MsgHeader;                                          /* ��Ϣͷ                                   */ /*_H2ASN_Skip*/
	NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM_UINT32     enGprsServiceType;
}MMCGMM_GPRS_SERVICE_IND_STRU;



typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ    */ /*_H2ASN_Skip*/
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    VOS_UINT8                           aucReservel[3];
} MMCGMM_TIN_TYPE_IND_STRU;
typedef struct
{
    MSG_HEADER_STRU                         MsgHeader;                              /* ��Ϣͷ  */ /*_H2ASN_Skip*/
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16       enSimAuthFailValue;
    VOS_UINT8                               ucReservel;
    NAS_MM_COM_SERVICE_DOMAIN_ENUM_UINT8    enSrvDomain;
}MMCGMM_SIM_AUTH_FAIL_IND_STRU;


#if (FEATURE_ON == FEATURE_LTE)
typedef  LMM_MMC_ATTACH_IND_STRU MMCGMM_LMM_ATTACH_IND_STRU;


typedef  LMM_MMC_TAU_RESULT_IND_STRU MMCGMM_LMM_TAU_RESULT_IND_STRU;



typedef  LMM_MMC_DETACH_IND_STRU MMCGMM_LMM_MT_DETACH_IND_STRU;


typedef  LMM_MMC_SERVICE_RESULT_IND_STRU MMCGMM_LMM_SERVICE_RESULT_IND_STRU;


typedef  LMM_MMC_DETACH_CNF_STRU MMCGMM_LMM_MO_DETACH_IND_STRU;


typedef  LMM_MMC_DETACH_IND_STRU MMCGMM_LMM_LOCAL_DETACH_IND_STRU;


typedef  LMM_MMC_STATUS_IND_STRU MMCGMM_LMM_STATUS_IND_STRU;



typedef  LMM_MMC_SYS_INFO_IND_STRU MMC_GMM_LTE_SYS_INFO_IND_STRU;


typedef  LMM_MMC_TIMER_STATE_NOTIFY_STRU MMCGMM_LMM_TIMER_STATE_NOTIFY_STRU;


typedef  LMM_MMC_EMERGENCY_NUM_STRU MMC_GMM_EMERGENCY_NUM_STRU;


typedef struct
{
    VOS_MSG_HEADER                                              /*_H2ASN_Skip*/
    MMC_LMM_MSG_ID_ENUM_UINT32              ulMsgId;            /*_H2ASN_Skip*/
    VOS_UINT32                              ulOpId;

    VOS_UINT8                               ucOpEmcNumList;

    VOS_UINT8                               ucEmergencyNumAmount;

    VOS_UINT8                               aucReserved[2];

    MMC_GMM_EMERGENCY_NUM_STRU              astEmergencyNumList[MMC_GMM_EMERGENCY_NUM_LIST_MAX_RECORDS];
} MMCGMM_EMERGENCY_NUM_LIST_IND_STRU;
#endif


/*****************************************************************************
 �ṹ��    : MMC_GMM_CIPHER_INFO_IND_STRU
 Э����  :
 ASN.1���� :
 �ṹ˵��  : GMM�����ϱ�MMC�������㷨����
*****************************************************************************/
typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;                              /* ��Ϣͷ  _H2ASN_Skip*/
    VOS_UINT8                           ucGprsCipherAlg;                        /* GPRS�����㷨 */
    VOS_UINT8                           ucGprsCipher;                           /* VOS_TRUE:��������,VOS_FALSE:���ܲ�������*/
    VOS_UINT8                           aucRsv[2];                              /* Ԥ��λ */
}MMC_GMM_CIPHER_INFO_IND_STRU;
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
    MMC_GMM_MSG_TYPE_ENUM_UINT16         enMsgID;    /*_H2ASN_MsgChoice_Export MMC_GMM_MSG_TYPE_ENUM_UINT32*/
                                                    /* Ϊ�˼���NAS����Ϣͷ���壬����ת��ASN.1ʹ��MMC_GMM_MSG_TYPE_ENUM_UINT32 */

    VOS_UINT8                           aucMsgBlock[2];
    /***************************************************************************
        _H2ASN_MsgChoice_When_Comment          MMC_GMM_MSG_TYPE_ENUM_UINT16
    ****************************************************************************/
}MMC_GMM_MSG_DATA;
/*_H2ASN_Length UINT32*/

typedef struct
{
    VOS_MSG_HEADER
    MMC_GMM_MSG_DATA                    stMsgData;
}MmcGmmInterface_MSG;

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

