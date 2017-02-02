

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "Nasrrcinterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmSwitchOn.h"
#include "NasUtranCtrlFsmSwitchOnTbl.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_SWITCHON_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS UtranCtrl״̬������:�������״̬������ */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlSwitchOnFsmDesc;

/* NAS_UTRANCTRL_FSM_SWITCH_ON::NAS_UTRANCTRL_SWITCH_ON_STA_SWITCH_ON_INIT */
NAS_ACT_STRU   g_astNasUtranCtrlSwitchOnInitActTbl[]                =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_Init),

};

/* NAS_UTRANCTRL_FSM_SWITCH_ON::NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_WAS_START_CNF������ */
NAS_ACT_STRU   g_astNasUtranCtrlSwitchOnWaitWasStartCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitWasStartCnf),

    /* �����Ƿ���Ϣ */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitWasStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_SwitchOn_WaitWasStartCnf),

};

/* NAS_UTRANCTRL_FSM_SWITCH_ON::NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_TD_START_CNF������ */
NAS_ACT_STRU   g_astNasUtranCtrlSwitchOnWaitTdStartCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_SwitchOn_WaitTdStartCnf),

    /* �����Ƿ���Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_SwitchOn_WaitTdStartCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_SwitchOn_WaitTdStartCnf),

};

/* Э��ջ����L2״̬�� */
NAS_STA_STRU g_astNasUtranCtrlSwitchOnStaTbl[] =
{
    /*****************���������κ�����ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_SWITCH_ON_STA_INIT,
                      g_astNasUtranCtrlSwitchOnInitActTbl ),


    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_WAS_START_CNF,
                      g_astNasUtranCtrlSwitchOnWaitWasStartCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_SWITCH_ON_STA_WAIT_TD_START_CNF,
                      g_astNasUtranCtrlSwitchOnWaitTdStartCnfActTbl ),
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32 NAS_UTRANCTRL_GetSwitchOnStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlSwitchOnStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetSwitchOnFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlSwitchOnFsmDesc);
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

