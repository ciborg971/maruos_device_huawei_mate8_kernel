


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasFsm.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmPowerOff.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcTimerMgmt.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_POWEROFF_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:�ػ���״̬������ */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlPowerOffFsmDesc;


/* NAS_UTRANCTRL_FSM_POWER_OFF::NAS_UTRANCTRL_L2_STA_POWEROFF_INIT������ */
NAS_ACT_STRU   g_astNasUtranCtrlPoweroffInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_Init),

    /* �յ�WAS�Ĺػ��ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_Init),

    /* �յ�TD�Ĺػ��ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_Init),

};

/* NAS_UTRANCTRL_FSM_POWER_OFF::NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF������ */
NAS_ACT_STRU   g_astNasUtranCtrlPoweroffWaitWasPowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitWasPowerOffCnf),

    /* �����쳣��Ϣ */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitWasPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_WaitWasPowerOffCnf),
};

/* NAS_UTRANCTRL_FSM_POWER_OFF::NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF������ */
NAS_ACT_STRU   g_astNasUtranCtrlPoweroffWaitTdPowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitTdPowerOffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitTdPowerOffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_WaitTdPowerOffCnf)
};




/* Э��ջ�ػ�L2״̬�� */
NAS_STA_STRU g_astNasUtranCtrlPowerOffStaTbl[] =
{
    /*****************����ػ���ʼ��ʱ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_POWER_OFF_STA_INIT,
                      g_astNasUtranCtrlPoweroffInitActTbl ),

    /*****************����ȴ�Was�ػ��ظ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF,
                      g_astNasUtranCtrlPoweroffWaitWasPowerOffCnfActTbl ),

    /*****************����ȴ�TD�ػ��ظ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF,
                      g_astNasUtranCtrlPoweroffWaitTdPowerOffCnfActTbl ),
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 NAS_UTRANCTRL_GetPowerOffStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlPowerOffFsmDesc);
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



