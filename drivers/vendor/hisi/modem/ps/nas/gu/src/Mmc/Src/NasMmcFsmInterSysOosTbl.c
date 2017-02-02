

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
#include "NasMmcSndInternalMsg.h"
#include "NasMmcFsmInterSysOos.h"
#include "NasMmcFsmInterSysOosTbl.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_OOS_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:������״̬������*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysOosFsmDesc;

/* NAS_MMC_INTER_SYS_OOS_STA_INIT������ */
NAS_ACT_STRU   g_astNasInterSysOosInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysOos_Init),
};

/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_SUSPEND_RSP������ */
NAS_ACT_STRU   g_astNasInterSysOosWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp),
};

/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND������ */
NAS_ACT_STRU   g_astNasInterSysOosWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd),

};


/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF������ */
NAS_ACT_STRU   g_astNasInterSysOosWaitWasSuspendRelCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSuspendRelCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf),

};


/* NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP������ */
NAS_ACT_STRU   g_astNasInterSysOosWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp),
};

/* oos״̬�������е�ϵͳ��Ϣ״̬��ɾ��g_astNasInterSysOosWaitWSysInfoIndActTbl��
   �յ�resume ind��Ϣ����״̬�� */


/* Э��ջInter Sys OOS״̬�� */
NAS_STA_STRU g_astNasMmcInterSysOosStaTbl[] =
{
     /* ����������״̬����ʼ״̬ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_INIT,
                     g_astNasInterSysOosInitActTbl ),

    /* ����㷢��ĳ��������������еȴ�MM�Ĺ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysOosWaitMmSuspendRspActTbl ),

    /* ����㷢��ĳ��������������еȴ������Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysOosWaitAsResumeIndActTbl ),

    /* ����㷢��ĳ��������������еȴ�WAS��SUSPPEND_REL_CNF�ָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF,
                      g_astNasInterSysOosWaitWasSuspendRelCnfActTbl ),

    /* ����㷢��ĳ��������������еȴ�MM�Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysOosWaitMmResumeRspActTbl ),

    /* oos״̬�������е�ϵͳ��Ϣ״̬��ɾ��g_astNasInterSysOosWaitWSysInfoIndActTbl��
       �յ�resume ind��Ϣ����״̬�� */

};




VOS_UINT32 NAS_MMC_GetInterSysOosStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysOosStaTbl)/sizeof(NAS_STA_STRU));
}




NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysOosFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysOosFsmDesc);
}



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

