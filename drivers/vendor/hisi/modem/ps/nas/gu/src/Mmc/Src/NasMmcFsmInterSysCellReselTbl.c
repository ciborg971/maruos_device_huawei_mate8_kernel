

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
#include "NasMmcFsmInterSysCellResel.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
#include "NasMmcSndInternalMsg.h"

#include "CmmcaMmcInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CELLRESEL_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:������״̬������*/
NAS_FSM_DESC_STRU                       g_stNasMmcInterSysCellReselFsmDesc;

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT������ */
NAS_ACT_STRU   g_astNasInterSysCellReselInitActTbl[]             =
{
    /* �յ�was����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init),

    /* �յ�Gas����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init),

#if   (FEATURE_ON == FEATURE_LTE)
    /* �յ�EMM����ϵͳ��ѡָʾ */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init),
#endif

/* Added by l00324781 for CDMA Iteration 12, 2015-6-8, begin */
#if (FEATURE_ON == FEATURE_LTE)
/* Added by l00324781 for CDMA Iteration 12, 2015-6-8, end */
    /* �յ�EMM����ϵͳ�ָ�ָʾ */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init),
#endif
};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitMmSuspendRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SUSPEND_RSP,
                      NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_SUSPEND_RSP,
                      NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_SUSPEND_RSP,
                      NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp),
};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitAsResumeIndActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd),

#if   (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY,
                      NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd),


#endif

#if   (FEATURE_ON == FEATURE_CL_INTERWORK)
    NAS_ACT_TBL_ITEM( WUEPS_PID_CMMCA,
                      ID_CMMCA_MMC_RESUME_IND,
                      NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CMMCA_RESUME_IND,
                      NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_AS_RESUME_IND,
                      NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd),

/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_INTERSYS_HRPD_NTF,
                      NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsResumeInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF,
                      NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd),
#endif
/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, end */

};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitMmResumeRspActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_RESUME_RSP,
                      NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RESUME_RSP,
                      NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_RESUME_RSP,
                      NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp),

};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitWSysInfoIndActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd),
};

/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitGSysInfoIndActTbl[]       =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd),


    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd),
};

/* g_astNasInterSysCellReselWaitWasSuspendRelCnfActTbl������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitWasSuspendRelCnfActTbl[]              =
{
    /* �յ�WAS��SUSPEND_REL_CNF�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf),

    /* �յ�WAS��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* �յ�GAS��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

#if   (FEATURE_ON == FEATURE_LTE)
    /* �յ�LMM��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),
#endif

    /* �ȴ�WAS��SUSPEND_REL_CNF��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf),

    /* �յ�WAS��RRMM_REL_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf),

};

/* g_astNasInterSysCellReselWaitGasSuspendRelCnfActTbl������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitGasSuspendRelCnfActTbl[]              =
{
    /* �յ�GAS��SUSPEND_REL_CNF�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf),

    /* �յ�WAS��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* �յ�GAS��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

#if   (FEATURE_ON == FEATURE_LTE)
    /* �յ�LMM��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),
#endif

    /* �ȴ�GAS��SUSPEND_REL_CNF��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf),
};

#if   (FEATURE_ON == FEATURE_LTE)
/* g_astNasInterSysCellReselWaitLmmSuspendRelCnfActTbl������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitLmmSuspendRelCnfActTbl[]              =
{
    /* �յ�LMM��SUSPEND_REL_CNF�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_REL_CNF,
                      NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf),

    /* �ȴ�LMM��SUSPEND_REL_CNF��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF,
                      NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf),

    /* �յ�WAS��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* �յ�GAS��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_RESUME_IND,
                      NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),

    /* �յ�LMM��RRMM_RESUME_IND�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_RESUME_IND,
                      NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf),
};
#endif

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND������ */
NAS_ACT_STRU   g_astNasInterSysCellReselWaitLSysInfoIndActTbl[]              =
{
    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd),

    /* ��Lģ��ϵͳ��Ϣ��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd),
};
#endif


/* Э��ջInter Sys CellResel״̬�� */
NAS_STA_STRU g_astNasMmcInterSysCellReselStaTbl[] =
{
     /* ��ϵͳ��ѡ��ʼ״̬ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_INIT,
                     g_astNasInterSysCellReselInitActTbl ),

    /* ����㷢�����ϵͳ��ѡ�����еȴ�MM�Ĺ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP,
                      g_astNasInterSysCellReselWaitMmSuspendRspActTbl ),

    /* ����㷢�����ϵͳ��ѡ�����еȴ������Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND,
                      g_astNasInterSysCellReselWaitAsResumeIndActTbl ),

    /* ����㷢�����ϵͳ��ѡ�����еȴ�MM�Ļָ� */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP,
                      g_astNasInterSysCellReselWaitMmResumeRspActTbl ),

     /* ����㷢�����ϵͳ��ѡ�����еȴ�WASϵͳ��Ϣ */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND,
                       g_astNasInterSysCellReselWaitWSysInfoIndActTbl ),

     /* ����㷢�����ϵͳ��ѡ�����еȴ�GASϵͳ��Ϣ */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND,
                       g_astNasInterSysCellReselWaitGSysInfoIndActTbl ),

     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF,
                       g_astNasInterSysCellReselWaitWasSuspendRelCnfActTbl ),

     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF,
                       g_astNasInterSysCellReselWaitGasSuspendRelCnfActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
     /* ����㷢�����ϵͳ��ѡ�����еȴ�LTEϵͳ��Ϣ */
     NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND,
                       g_astNasInterSysCellReselWaitLSysInfoIndActTbl ),

    /* ����㷢�����ϵͳ��ѡ�����еȴ�LTE��Ϣ */
    NAS_STA_TBL_ITEM( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF,
                      g_astNasInterSysCellReselWaitLmmSuspendRelCnfActTbl),

#endif
};



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetInterSysCellReselStaTblSize
 ��������  : ��ȡinter sys CellResel״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:inter sys CellResel״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetInterSysCellReselStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcInterSysCellReselStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetInterSysCellReselFsmDescAddr
 ��������  : ��ȡ����״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ�����״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetInterSysCellReselFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcInterSysCellReselFsmDesc);
}



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


