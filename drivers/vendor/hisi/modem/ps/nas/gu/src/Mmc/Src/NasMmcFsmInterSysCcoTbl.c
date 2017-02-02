

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcTimerMgmt.h"
#include "MsccMmcInterface.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcFsmInterSysCco.h"
#include "NasMmcFsmInterSysCcoTbl.h"




#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CCO_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:������״̬������*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysCcoFsmDesc;

/* NAS_MMC_FSM_L2_InterSysCco:NAS_MMC_InterSysCco_STA_INIT������ */
NAS_ACT_STRU   g_astNasInterSysCcoInitActTbl[]             =
{
    /* �յ�was����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCco_Init),

    /* �յ�Gas����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCco_Init),

#if   (FEATURE_ON == FEATURE_LTE)
    /* �յ�EMM����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCco_Init),
#endif

};


/* NAS_MMC_InterSysCco_STA_wait for mm rsp������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp),

};

/* NAS_MMC_InterSysCco_STA_wait for As resume������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeInd),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeInd),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeInd),

};

/* NAS_MMC_InterSysCco wait for Mm resume rsp������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp),
};


/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitWSysInfoIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd),
};

/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitGSysInfoIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd),
};

#if (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitLSysInfoIndActTbl[]          =
{

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoInd),
};
#endif

/* NAS_MMC_InterSysCco wait EST Ind������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitEstIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd),

#if (FEATURE_LTE == FEATURE_ON)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitEstInd),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_InterSysCco_WaitEstInd),

     /* �յ�was����ϵͳCCOָʾ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitEstInd),

    /* �յ�Gas����ϵͳCCOָʾ */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitEstInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EST_IND,
                      NAS_MMC_RcvTiWaitEstIndExpired_InterSysCco_WaitEstInd),

};

/* NAS_MMC_FSM_L2_InterSysCco:NAS_MMC_InterSysCco_STA_WAIT_AS_SUSPEND_IND_FALLBACK������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitAsSuspendIndFallBackActTbl[]             =
{
    /* �յ�was����ϵͳCCOָʾ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack),

    /* �յ�Gas����ϵͳCCOָʾ */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack),

#if   (FEATURE_ON == FEATURE_LTE)
    /* �յ�EMM����ϵͳCCOָʾ */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitAsSuspendIndFallBack),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_SUSPEND_IND,
                      NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack),
};

/* NAS_MMC_InterSysCco_STA_wait for mm rsp_fallbcak������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmSuspendRspFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack),
};

/* NAS_MMC_InterSysCco_STA_wait for As resume������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitAsResumeIndFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeIndFallBack),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeIndFallBack),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeIndFallBack),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeIndFallBack),

};

/* NAS_MMC_InterSysCco wait for Mm resume rsp������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitMmResumeRspFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack),
};


/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitWSysInfoIndFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoIndFallBack),
};

/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitGSysInfoIndFallBackActTbl[]          =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoIndFallBack),
};

#if (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK������ */
NAS_ACT_STRU   g_astNasInterSysCcoWaitLSysInfoIndFallBackActTbl[]          =
{

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoIndFallBack),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoIndFallBack),
};
#endif

/*InterSysCco״̬��*/
NAS_STA_STRU g_astNasMmcInterSysCcoStaTbl[] =
{
     /* InterSysCco��ʼ״̬ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_INIT,
                     g_astNasInterSysCcoInitActTbl ),

    /* ����㷢���InterSysCco�����еȴ�MM�Ĺ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysCcoWaitMmSuspendRspActTbl ),

    /* ����㷢���InterSysCco�����еȴ������Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysCcoWaitAsResumeIndActTbl ),

    /* ����㷢���InterSysCco�����еȴ�MM�Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysCcoWaitMmResumeRspActTbl ),

    /* ����㷢���InterSysCco�����еȴ�WAS��ϵͳ��Ϣ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND,
                      g_astNasInterSysCcoWaitWSysInfoIndActTbl ),

     /* ����㷢���InterSysCco�����еȴ�GAS��ϵͳ��Ϣ */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND,
                       g_astNasInterSysCcoWaitGSysInfoIndActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /* ����㷢���InterSysCco�����еȴ�L��ϵͳ��Ϣ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND,
                      g_astNasInterSysCcoWaitLSysInfoIndActTbl ),
#endif

    /* ����㷢���InterSysCco�����еȴ�CS/PS/EPS�Ľ������*/
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND,
                      g_astNasInterSysCcoWaitEstIndActTbl ),

    /* ����㷢���InterSysCco���˹����еȴ������Ĺ���ָʾ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK,
                      g_astNasInterSysCcoWaitAsSuspendIndFallBackActTbl ),

    /* ����㷢���InterSysCco���˹����еȴ�MM�Ĺ���ظ�*/
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK,
                      g_astNasInterSysCcoWaitMmSuspendRspFallBackActTbl),

    /* ����㷢���InterSysCco���˹����еȴ������Ļָ�ָʾ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK,
                      g_astNasInterSysCcoWaitAsResumeIndFallBackActTbl ),

    /* ����㷢���InterSysCco���˹����еȴ�MM�Ļָ��ظ�*/
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK,
                      g_astNasInterSysCcoWaitMmResumeRspFallBackActTbl),

    /* ����㷢���InterSysCco���˹����еȴ�WAS��ϵͳ��Ϣ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK,
                      g_astNasInterSysCcoWaitWSysInfoIndFallBackActTbl ),

     /* ����㷢���InterSysCco���˹����еȴ�GAS��ϵͳ��Ϣ */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK,
                       g_astNasInterSysCcoWaitGSysInfoIndFallBackActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /* ����㷢���InterSysCco���˹����еȴ�L��ϵͳ��Ϣ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK,
                      g_astNasInterSysCcoWaitLSysInfoIndFallBackActTbl ),
#endif
};

/*****************************************************************************
  3 ����ʵ��
****************************************************************************/

VOS_UINT32 NAS_MMC_GetInterSysCcoStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysCcoStaTbl)/sizeof(NAS_STA_STRU));
}




NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCcoFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysCcoFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



