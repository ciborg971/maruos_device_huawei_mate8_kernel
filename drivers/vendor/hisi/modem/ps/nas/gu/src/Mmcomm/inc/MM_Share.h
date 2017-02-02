
#ifndef _MMSHARE_H_
#define _MMSHARE_H_

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasComm.h"
#include "NasMmlCtx.h"
#include "NasMmcCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#pragma pack(4)

/*****************************************************************************
  2 �궨��
*****************************************************************************/


/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/


/*
<EMM Combined procedures Capability : bit >�������ָʾMS�Ƿ�֧��EMM����ע�ᡣ
0��ʾ��֧��EMM����ע�ᡣ
1��ʾ֧��EMM����ע�ᡣ
*/
enum NAS_EMM_COMB_CAPABILITY_ENUM
{
    NAS_EMM_COMB_CAPABILITY_UNSUPPORT,
    NAS_EMM_COMB_CAPABILITY_SUPPORT,
    NAS_EMM_COMB_CAPABILITY_BUTT
};
typedef VOS_UINT32 NAS_EMM_COMB_CAPABILITY_ENUM_U32;

/*
 <ISR support : bit >�������ָʾMS�Ƿ�֧��ISR���ܣ�
 ISR���ܣ�Idle Mode Signalling Reduction����Ҫ��Ϊ�˼���Lģ��ѡ��GUģ��GUģ
 ��ѡ��Lģ����̬�µ����

0  ��ʾ��֧��ISR���ܡ�
1  ��ʾ֧��ISR���ܡ�
*/
enum NAS_EMM_ISR_SUPPORT_ENUM
{
    NAS_EMM_ISR_SUPPORT_UNSUPPORT,
    NAS_EMM_ISR_SUPPORT_SUPPORT,
    NAS_EMM_ISR_SUPPORT_BUTT
};
typedef VOS_UINT32 NAS_EMM_ISR_SUPPORT_ENUM_U32;

/*
<EPC capability: bit >�������ָʾMS�Ƿ�֧��EPC���������������
0��ʾ��֧��EPC��EPC�Ľ��������PDN�����ء�
1��ʾ֧��EPC��EPC�Ľ��������PDN�����أ�GERAN�Լ�UTRAN
*/
enum NAS_EMM_EPC_CAPABILITY_ENUM
{
    NAS_EMM_EPC_CAPABILITY_UNSUPPORT,
    NAS_EMM_EPC_CAPABILITY_SUPPORT,
    NAS_EMM_EPC_CAPABILITY_BUTT
};
typedef VOS_UINT32 NAS_EMM_EPC_CAPABILITY_ENUM_U32;


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
  8 UNION����
*****************************************************************************/


/*****************************************************************************
  9 OTHERS����
*****************************************************************************/



/* �ϴ��룬�������� */

/* MM�Ӳ㹲������ṹ */
#define     MM_TIMER_TICK               10


/* SUSPENDʱ������ǰ��ʱ���ѳ�ʱ������δ�յ�VOS_TIMER�ĳ�ʱ��Ϣ������ʱȡһ��1s������ʱ��Ϣ�յ������ */

#define     MM_EXTRA_DELAY_TIME_LEN  1000



/************** ucSimType ȡֵ ****************************/
#define     MMC_SIM_TYPE_SIM            (0)
#define     MMC_SIM_TYPE_USIM           (1)


/* �ն˿��������󣬶����ն������罻��ʱ���ݵ�Э��汾 */
#define PS_CUSTOM_REL_VER_R97                               0
#define PS_CUSTOM_REL_VER_R99                               1
#define PS_CUSTOM_REL_VER_AUTO                              2

/* �ն˿��������󣬶����ն������罻��ʱ���ݵ�Э��汾 */
#define PS_STEERING_OF_ROAMING_NOT_SUPPORT                  0
#define PS_STEERING_OF_ROAMING_SUPPORT                      1

#define Mm_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode) \
        NAS_StartRelTimer(phTm, Pid, ulLength, ulName, ulParam, ucMode)
#define Mm_StopRelTimer(Pid, ulName, phTm) \
        NAS_StopRelTimer(Pid, ulName, phTm)


typedef VOS_UINT8 MM_REG_STATE_TYPE;
#define MM_REG_NOT_REGISTERED_NOT_SEARCH   0                /* δע�ᣬδ�������� PLMN�����û���������ע�ᣬ������� */
#define MM_REG_REGISTERED_HOME_NETWORK     1                /* ע�ᣬע���� HOME PLMN */
#define MM_REG_NOT_REGISTERED_SEARCHING    2                /* δע�ᣬ��������PLMN�������ڸ��Ź��� */
#define MM_REG_REGISTERED_DENIED           3                /* ע�ᱻ�ܾ�����ǰ�û�����������ע�ᣬ�������񱻽�ֹ */
#define MM_REG_UNKNOWN                     4                /* ������� */
#define MM_REG_REGISTERED_ROAM             5                /* ע�ᣬע���ڷ� HOME PLMN */

typedef VOS_UINT8 MM_SUSPEND_CAUSE;
#define MM_SUSPEND_FOR_HANDOVER         0                   /* ��������ϵͳ�л�ʱ��MM ��ҵ����� */
#define MM_SUSPEND_FOR_RESELECT         1                   /* ��������ϵͳ�л�ʱ��MM ���У���ҵ�� */
#define MM_INVALID_SUSPEND_CAUSE        2                   /* ��Ч�л�ԭ�� */

#define MM_PAGING_PLMNSRCH_FALSE        0
#define MM_PAGING_PLMNSRCH_TRUE         1

#define MM_UPDATED_SPECIFIC_PROCEDURE        0
#define MM_NOT_UPDATED_SPECIFIC_PROCEDURE    1

typedef struct
{
#define     MM_STATUS_ATTACHED                          0                       /* attached                                 */
#define     MM_STATUS_DETACHED                          1                       /* detached                                 */
    VOS_UINT8                               ucCsAttachState;                        /* attach״̬                               */

#define     MM_UPDATE_STATUS_U1                         0                       /* U1                                       */
#define     MM_UPDATE_STATUS_U2                         1                       /* U2                                       */
#define     MM_UPDATE_STATUS_PLMN_NOT_ALLOWED           2                       /* U3                                       */
#define     MM_UPDATE_STATUS_LA_NOT_ALLOWED             3                       /* U3                                       */
#define     MM_UPDATE_STATUS_U3     MM_UPDATE_STATUS_LA_NOT_ALLOWED             /* U3                                       */

    VOS_UINT8                               ucUpdateSts;                            /* ����״̬                                 */

#define     MM_SPECIFIC_ON                              0                       /* GMM������detach                          */
#define     MM_SPECIFIC_OFF                             1                       /* GMM����detach                            */
    VOS_UINT8                               ucCsSpecificFlg;

    VOS_UINT8                                  MmSuspendEvent;
    VOS_UINT8                                  ucPagingPlmnSrch;
    VOS_UINT8                                   ucSpecProFlg;                       /*MM�Ƿ�ɹ����й�ר�й��̱�־*/
    NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8    ucCsIntegrityProtect;

    VOS_UINT8                           ucReserve;
}MM_SHARE_STRU;

typedef VOS_UINT8 GMM_REG_STATE_TYPE;
#define GMM_REG_NOT_REGISTERED_NOT_SEARCH   0                /* δע�ᣬδ�������� PLMN�����û���������ע�ᣬ������� */
#define GMM_REG_REGISTERED_HOME_NETWORK     1                /* ע�ᣬע���� HOME PLMN */
#define GMM_REG_NOT_REGISTERED_SEARCHING    2                /* δע�ᣬ��������PLMN�������ڸ��Ź��� */
#define GMM_REG_REGISTERED_DENIED           3                /* ע�ᱻ�ܾ�����ǰ�û�����������ע�ᣬ�������񱻽�ֹ */
#define GMM_REG_UNKNOWN                     4                /* ������� */
#define GMM_REG_REGISTERED_ROAM             5                /* ע�ᣬע���ڷ� HOME PLMN */

typedef struct
{
#define     GMM_STATUS_DETACHED                               0                 /* detached                                 */
#define     GMM_STATUS_ATTACHED                               1                 /* attached                                 */
    VOS_UINT8                               ucAttachSta;                        /* attach״̬                               */

#define     GMM_DETACH_DISABLE                               0                  /* GMM������detach                          */
#define     GMM_DETACH_ABLE                                  1                  /* GMM����detach                            */
    VOS_UINT8                               ucDeatchEnableFlg;                  /* �Ƿ�����detach��־                       */
#define     GMM_SPECIFIC_ON                                   0                 /* GMM������detach                          */
#define     GMM_SPECIFIC_OFF                                  1                 /* GMM����detach                            */
    VOS_UINT8                               ucPsSpecificFlg;

    VOS_UINT8                ucGsAssociationFlg;                                /* ��ǰ�Ƿ����Gs������0�������ڣ� 1:���� */
    NAS_MML_RRC_INTEGRITY_PROTECT_ENUM_UINT8   ucPsIntegrityProtect;
    VOS_UINT8                           aucReserve[3];
}GMM_SHARE_STRU;

/*typedef struct
{
    MMC_SHARE_STRU  MmcShare;
    MM_SHARE_STRU   MmShare;
    GMM_SHARE_STRU  GmmShare;
}MM_SUB_LAYER_SHARE_STRU;*/

/*����״̬����*/
typedef enum
{
    MMC_NET_TYPE_GSM_ENUM = 0,
    MMC_NET_TYPE_WCDMA_ENUM,
    MMC_NET_TYPE_BUTT,
}MMC_NET_TYPE_ENUM;


/*MMC����ǰ״̬*/
typedef struct
{
    MM_PLMN_ID_STRU                     stPlmn;
    VOS_UINT8                           aucMsgBuf[71];      /*���͹���֮ǰ��
                                                              ����Ϣ�����ڹ�
                                                              ������ִ�и�
                                                              ��Ϣ*/
    VOS_UINT8                           ucPlmnFlg;          /*ȡֵΪMMC_TRUE �� MMC_FALSE����ʾ��ǰplmn�������*/
}MMC_PLMN_INFO_ST;




/* ��ԭ�����ݽṹ MM_SUB_LAYER_SHARE_STRU ���½����˶���,�����ݽṹ�Ķ�����MM_Share.h�ļ��� */
typedef struct
{
    MM_SHARE_STRU                       MmShare;              /* ԭ�����ݳ�Ա                      */
    GMM_SHARE_STRU                      GmmShare;             /* ԭ�����ݳ�Ա                      */
    MM_SUSPEND_SHARE_STRU               MmSuspendShare; /* ΪMM��GMM����״̬����ȫ�ֱ����ṹ */
  }MM_SUB_LAYER_SHARE_STRU;

typedef struct
{
    VOS_UINT32                          ulNasMsgSize;
    VOS_UINT8                           aucNasMsg[255];
}NAS_MSG_FOR_PCLINT_STRU;

typedef struct
{
    MSG_HEADER_STRU                     MsgHeader;
    RRC_NAS_CN_DOMAIN_TYPE_ENUM_UINT32  ulCnDomainId;
    NAS_MSG_FOR_PCLINT_STRU             RcvNasMsg;
}RRMM_DATA_IND_FOR_PCLINT_STRU;

typedef struct
{
    MSG_HEADER_STRU              MsgHeader;
    VOS_UINT32                   ulTi;
    NAS_MSG_FOR_PCLINT_STRU      SmsMsg;
}MMSMS_DATA_IND_FOR_PCLINT_STRU;

#define AUTHENTICATION_REQ_UMTS_CHALLENGE           0
#define AUTHENTICATION_REQ_GSM_CHALLENGE            1

#define     GMM_PROCEDURE_SRCHPLMN_SUCCESS     0x00
#define     GMM_PROCEDURE_SRCHPLMN_FAILURE     0x01
#define     GMM_PROCEDURE_ATTACH_SUCCESS       0x02
#define     GMM_PROCEDURE_ATTACH_FAILURE       0x03
#define     GMM_PROCEDURE_SERVICE_SUCCESS      0x04
#define     GMM_PROCEDURE_SERVICE_FAILURE      0x05
#define     GMM_PROCEDURE_RAU_SUCCESS          0x06
#define     GMM_PROCEDURE_RAU_FAILURE          0x07
/* BEGIN: Modified by liurui id:40632, 2006/4/20   PN:A32D03300 */
#define     GMM_PROCEDURE_PTMSI_RELOC          0x08
#define     GMM_PROCEDURE_DETACH_OVER          0x09
/* END:   Modified by liurui id:40632, 2006/4/20   PN:A32D03300 */
#define     VOS_RELATIVE_TIMER                 0x02

#define     MM_AUTH_PRO                             0x0
#define     MM_LAU_SUCCESS                          0x1
#define     MM_LAU_FAILURE                          0x2
#define     MM_SERVICE_SUCCESS                      0x5
#define     MM_SERVICE_FAILURE                      0x6
#define     MM_TMSI_RELOC                           0x7
#define     MM_DETACH_COMPLETE                      0x8

#define     RRC_NAS_MASK_NULL           0x0000
#define     RRC_NAS_MASK_ATTACH         0x0001
#define     RRC_NAS_MASK_USIM_INVALID   0x0002
#define     RRC_NAS_MASK_SECURITY_KEY   0x0004
#define     RRC_NAS_MASK_DRX            0x0008
#define     RRC_NAS_MASK_TMSI_LAI       0x0010
#define     RRC_NAS_MASK_PTMSI_RAI      0x0020
#define     RRC_NAS_MASK_DEL_KEY        0x0040
#define     RRC_NAS_MASK_GSM_GMM_STATE  0x0080  /* GSM������GMM״̬��Ϣ��Ч��־ */
#define     RRC_NAS_MASK_READY_TIMER    0x0100  /* READY TIMERֵ��Ч��־        */
#define     RRC_NAS_MASK_MS_GPRS_MODE   0x0200  /* MS GPRSģʽֵ��Ч��־ */
#define     RRC_NAS_MASK_MAPPED_SECURITY_KEY 0x0400


#define     RRC_NAS_MASK_SYNC_WRR       ( (RRC_NAS_MASK_ATTACH) | (RRC_NAS_MASK_PTMSI_RAI) )


#define     RRC_NAS_MASK_SYNC_GAS     ((RRC_NAS_MASK_ATTACH) | (RRC_NAS_MASK_DRX)                  \
                                      | (RRC_NAS_MASK_PTMSI_RAI) | (RRC_NAS_MASK_GSM_GMM_STATE)     \
                                      | (RRC_NAS_MASK_READY_TIMER) | (RRC_NAS_MASK_MS_GPRS_MODE))



#define     RRC_NAS_SYS_MSK_PLMN        0x0001
#define     RRC_NAS_SYS_MSK_CS_DRX      0x0002
#define     RRC_NAS_SYS_MSK_PS_DRX      0x0004
#define     RRC_NAS_SYS_MSK_CSPS_INFO   0x0008

#define     MM_LOCK_SUCCESS       WUEPS_SEMAPHORE_LOCK_SUCCESS                  /* �����ɹ�                                 */
#define     MM_LOCK_FAILURE       WUEPS_SEMAPHORE_LOCK_FAILURE                  /* ����ʧ��                                 */
#define     MM_UNLOCK_SUCCESS     WUEPS_SEMAPHORE_UNLOCK_SUCCESS                /* �����ɹ�                                 */
#define     MM_UNLOCK_FAILURE     WUEPS_SEMAPHORE_UNLOCK_FAILURE                /* ����ʧ��                                 */

#define EVT_NAS_MM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* ΪPC���̻طŶ������Ϣ */

/*****************************************************************************
 Structure      : NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣��洢����MM��ص�ȫ�ֱ���
 Message origin :
*****************************************************************************/

typedef struct
{
    VOS_UINT8                               pc_gucMmProcessFlg;
    VOS_UINT8                               pc_g_T3211Flag;
    MM_NSD_INFO_ST                          pc_g_stMmNsd;

    MM_GLOBAL_CTRL_STRU                     pc_g_MmGlobalInfo;

    MM_TIMER_STRU                           pc_gstMmTimer[MM_TIMER_MAX];
} NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST;

/*****************************************************************************
 Structure      : NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST
 Description    : PC�طŹ��̣�����MM��ص�ȫ�ֱ���ͨ��������Ϣ�ṹ����
 Message origin :
*****************************************************************************/
typedef struct
{
    VOS_MSG_HEADER
    VOS_UINT32                           ulMsgID;
    NAS_MM_OUTSIDE_RUNNING_CONTEXT_ST    stOutsideCtx;
}NAS_MM_SDT_MSG_ST;


#define EVT_NAS_GMM_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY   0xaaaa          /* ΪPC���̻طŶ������Ϣ */

enum NAS_MM_LOG_OM_INFO_ENUM
{
    NAS_MM_LOG_TIN_TYPE_INFO_IND       = 0xa00,
    NAS_MM_LOG_BUTT
};
typedef VOS_UINT32 NAS_MM_LOG_OM_INFO_ENUM_UINT32;


typedef struct
{
    MSG_HEADER_STRU                     stMsgHeader;
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;                              /* TIN���� */
    VOS_UINT8                           aucReserve[3];
}NAS_MM_LOG_TIN_INFO_STRU;




/*****************************************************************************
  10 ��������
*****************************************************************************/
extern VOS_UINT32 Mm_AtTest_GetGprsState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetGmmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetMmState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetMmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_GetGmmRegState(MM_TEST_AT_RSLT_STRU *pstAtCmdRslt);
extern VOS_UINT32 Mm_AtTest_SetPlmnSearchMode(VOS_UINT32 ulPlmnSearchMode);
extern VOS_UINT32 Mm_AtTest_SetRatMode(VOS_UINT32 ulRatMode);
VOS_UINT32 Mm_AtTest_SetOriginalRejectCause(
    VOS_UINT32                          ulOriginalUeCause
);
extern VOS_UINT32 Gmm_GetState(VOS_VOID);
extern VOS_UINT32 Gmm_GetGprsState(VOS_VOID);

extern VOS_UINT32 Mm_GetState(VOS_VOID);

extern VOS_UINT32 Mm_AtTest(VOS_VOID *pInput,VOS_VOID *pRslt);

extern VOS_VOID Mm_FillNasMmInfo(NAS_OM_MM_CONFIRM_STRU *pMsg);
extern VOS_VOID Gmm_FillNasMmInfo(NAS_OM_MM_CONFIRM_STRU *pMsg);
extern VOS_VOID Mmc_FillNasMmInfo(NAS_OM_MM_CONFIRM_STRU *pMsg);
extern VOS_VOID Mm_OmQuery(VOS_VOID *pMsg);
/* Deleted Mm_TranslateNtwkName2Str */
extern VOS_UINT8 NAS_MM_GetMncLenFromBCCHMnc(
    VOS_UINT32                          ulBcchMnc
);

extern VOS_VOID NAS_MM_SndOutsideContextData(VOS_VOID);
extern VOS_VOID NAS_GMM_SndOutsideContextData(VOS_VOID);
extern VOS_INT8 NAS_Common_Get_Supported_3GPP_Version(VOS_UINT32 ulCnDomainId);
extern VOS_UINT32 NAS_MMC_IsRoam();
extern VOS_VOID MMC_ComGetRatType(VOS_UINT8 *pucRatType);

extern VOS_BOOL NAS_MM_NeedSendEPlmnConnFail(VOS_VOID);

extern VOS_UINT8 NAS_MM_CheckIfMmIsEstablishRRConnection(VOS_VOID);

extern VOS_VOID NAS_MM_HandleGmmCauseValAsLuAccept(VOS_VOID);

extern VOS_VOID NAS_MM_UpdateCsServiceConnStatusFlg(VOS_VOID);

extern VOS_VOID NAS_MM_UpdateCsServiceBufferStatusFlg(VOS_VOID);

VOS_UINT32 NAS_MM_IsGURplmnChanged(
    NAS_MML_PLMN_ID_STRU               *pstRPlmnId,
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat
);

VOS_VOID NAS_MM_WriteRplmnWithRatNvim(
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo
);

VOS_VOID NAS_MM_GenerateEPlmnInfo(
    VOS_UINT32                          ulLauAcceptPlmnNum,
    MM_PLMN_ID_STRU                    *pstLauAcceptPlmnList,
    NAS_MML_EQUPLMN_INFO_STRU          *pstEquPlmnInfo
);

VOS_VOID NAS_MM_WriteEplmnNvim(
    NAS_MML_EQUPLMN_INFO_STRU          *pstEplmnAddr
);

extern VOS_VOID NAS_MM_UpdateEquPlmnInfo(
    VOS_UINT32                          ulCause
);


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

#endif /* MMSHARE_H */
