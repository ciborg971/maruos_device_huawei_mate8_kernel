

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
/* ɾ��ExtAppMmcInterface.h*/
#include "NasMmcFsmSyscfg.h"
#include "NasMmcFsmSyscfgTbl.h"
#include "NasMmcTimerMgmt.h"

#include "MsccMmcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSMSYSCFG_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:SYSCFG�Ӳ�״̬������ */
NAS_FSM_DESC_STRU                       g_stNasMmcSysCfgFsmDesc;

/* NAS_MMC_SYSCFG_STA_INIT������  */
NAS_ACT_STRU   g_astNasSyscfgInitActTbl[]             =
{
    /* �յ�MSCC��syscfg����������Ϣ */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvMsccSysCfgSetReq_SysCfg_Init),

};

/* NAS_MMC_SYSCFG_STA_WAIT_GAS_SYSCFG_CNF������ */
NAS_ACT_STRU   g_astNasSyscfgWaitGasSyscfgCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SYS_CFG_CNF,
                      NAS_MMC_RcvGasSysCfgCnf_SysCfg_WaitGasSysCfgCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_SysCfg_WaitGasSysCfgCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYSCFG_CNF,
                      NAS_MMC_RcvGasSysCfgCnfExpired_SysCfg_WaitGasSysCfgCnf),

};

/* NAS_MMC_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF������ */
NAS_ACT_STRU   g_astNasSyscfgWaitWasSyscfgCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_MMC_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYSCFG_CNF,
                      NAS_MMC_RcvWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf),
};

/*  NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND ������ */
NAS_ACT_STRU   g_astSyscfgWaitCsPsConnRelIndActTbl[]              =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_SysCfg_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmConnInfoInd_SysCfg_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmcMmRelInd_SysCfg_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_SysCfg_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_SysCfg_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_SysCfg_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_SysCfg_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_RRC_CONN_REL,
                      NAS_MMC_RcvTiWaitRrcConnRelExpired_SysCfg_WaitRrcConnRelInd),

};


#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_SYSCFG_STA_WAIT_LMM_SYSCFG_CNF������ */
NAS_ACT_STRU   g_astNasSyscfgWaitLmmSyscfgCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_CFG_CNF,
                      NAS_MMC_RcvLmmSysCfgCnf_SysCfg_WaitLmmSysCfgCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_SysCfg_WaitLmmSysCfgCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYSCFG_CNF,
                      NAS_MMC_RcvLmmSysCfgCnfExpired_SysCfg_WaitLmmSysCfgCnf),
};

/* NAS_MMC_SYSCFG_STA_WAIT_EPS_CONN_REL_IND������ */
NAS_ACT_STRU   g_astNasSyscfgWaitEpsConnRelInd[]         =
{
    /* Lģע��Ĺ����л��յ��������Ӵ��ڵı�־��Ҫ���� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_SysCfg_WaitEpsConnRelInd),

    /* �������ͷŶ�ʱ����ʱ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsConnRelIndExpired_SysCfg_WaitEpsConnRelInd),


    /* ����suspend״̬�� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_SysCfg_WaitEpsConnRelInd),

};

#endif

/* SYSCFG״̬�� */
NAS_STA_STRU g_astNasMmcSyscfgStaTbl[] =
{
     /* Syscfg��ʼ״̬ */
    NAS_STA_TBL_ITEM(NAS_MMC_SYSCFG_STA_INIT,
                     g_astNasSyscfgInitActTbl),

    /* SYSCFG���̣��ȴ�GAS��RRMM_SYS_CFG_CNF���ûظ���Ϣ */
    NAS_STA_TBL_ITEM(NAS_MMC_SYSCFG_STA_WAIT_GAS_SYSCFG_CNF,
                     g_astNasSyscfgWaitGasSyscfgCnfActTbl),

    /* SYSCFG���̣��ȴ�WAS��RRMM_SYS_CFG_CNF���ûظ���Ϣ */
    NAS_STA_TBL_ITEM(NAS_MMC_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF,
                     g_astNasSyscfgWaitWasSyscfgCnfActTbl),

    /* SYSCFG���̣��ȴ�GU�����ͷ� */
    NAS_STA_TBL_ITEM(NAS_MMC_SYSCFG_STA_WAIT_RRC_CONN_REL_IND,
                     g_astSyscfgWaitCsPsConnRelIndActTbl),

#if (FEATURE_ON == FEATURE_LTE)
    /* SYSCFG���̣��ȴ�LMM��ID_LMM_MMC_SYS_CFG_CNF���ûظ���Ϣ */
    NAS_STA_TBL_ITEM(NAS_MMC_SYSCFG_STA_WAIT_LMM_SYSCFG_CNF,
                     g_astNasSyscfgWaitLmmSyscfgCnfActTbl),

    /* SYSCFG���̣�EPS��������ͷŽ��  */
    NAS_STA_TBL_ITEM(NAS_MMC_SYSCFG_STA_WAIT_EPS_CONN_REL_IND,
                     g_astNasSyscfgWaitEpsConnRelInd),
#endif

};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32 NAS_MMC_GetSysCfgStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcSyscfgStaTbl)/sizeof(NAS_STA_STRU));
}





NAS_FSM_DESC_STRU * NAS_MMC_GetSysCfgFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcSysCfgFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
