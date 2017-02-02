

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmSyscfg.h"
#include "NasUtranCtrlFsmSyscfgTbl.h"
#include "NasMmcTimerMgmt.h"

#include "MsccMmcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SYSCFG_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:SYSCFG�Ӳ�״̬������ */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlSysCfgFsmDesc;


/* NAS_UTRANCTRL_SYSCFG_STA_INIT������  */
NAS_ACT_STRU   g_astNasUtranCtrlSyscfgInitActTbl[]             =
{
    /* �յ�Was��syscfg���ûظ���Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_Init),

    /* �յ�Td��syscfg���ûظ���Ϣ */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_Init),

};

/* NAS_UTRANCTRL_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF������ */
NAS_ACT_STRU   g_astNasUtranCtrlSyscfgWaitWasSyscfgCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitWasSysCfgCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_UTRANCTRL_RcvWasSuspendInd_SysCfg_WaitWasSysCfgCnf),

    /* �쳣��Ϣ���� */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitWasSysCfgCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiWasSysCfgCnfExpired_SysCfg_WaitWasSysCfgCnf),
};

/* NAS_UTRANCTRL_SYSCFG_STA_WAIT_TD_SYSCFG_CNF������ */
NAS_ACT_STRU   g_astNasUtranCtrlSyscfgWaitTdSyscfgCnfActTbl[]          =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_SysCfg_WaitTdSysCfgCnf),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SUSPEND_IND,
                      NAS_UTRANCTRL_RcvTdSuspendInd_SysCfg_WaitTdSysCfgCnf),

    /* �쳣��Ϣ���� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_SysCfg_WaitTdSysCfgCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiTdSysCfgCnfExpired_SysCfg_WaitTdSysCfgCnf),
};


/* SYSCFG״̬�� */
NAS_STA_STRU g_astNasUtranCtrlSyscfgStaTbl[] =
{
     /* Syscfg��ʼ״̬ */
    NAS_STA_TBL_ITEM(NAS_UTRANCTRL_SYSCFG_STA_INIT,
                     g_astNasUtranCtrlSyscfgInitActTbl),

    /* SYSCFG���̣��ȴ�WAS��RRMM_SYS_CFG_CNF���ûظ���Ϣ */
    NAS_STA_TBL_ITEM(NAS_UTRANCTRL_SYSCFG_STA_WAIT_WAS_SYSCFG_CNF,
                     g_astNasUtranCtrlSyscfgWaitWasSyscfgCnfActTbl),

    /* SYSCFG���̣��ȴ�TD��RRMM_SYS_CFG_CNF���ûظ���Ϣ */
    NAS_STA_TBL_ITEM(NAS_UTRANCTRL_SYSCFG_STA_WAIT_TD_SYSCFG_CNF,
                     g_astNasUtranCtrlSyscfgWaitTdSyscfgCnfActTbl),

};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_GetSysCfgStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlSyscfgStaTbl)/sizeof(NAS_STA_STRU));
}





NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetSysCfgFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlSysCfgFsmDesc);
}


#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

