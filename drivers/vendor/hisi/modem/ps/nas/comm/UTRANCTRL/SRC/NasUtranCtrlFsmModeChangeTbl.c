

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmModeChange.h"
#include "MsccMmcInterface.h"
/* ɾ��ExtAppMmcInterface.h*/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NASUTRANCTRLFSMMODECHANGETBL_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* UTRANCTRLģ���ģʽ���״̬�� */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlModeChangeFsmDesc;

/**************************************************************************/
/*����״̬��������� */
/**************************************************************************/

/* NAS_UTRANCTRL_Mode_Change_STA_INIT ������ */
NAS_ACT_STRU        g_astNasUtranCtrlModeChangeInitActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvWasSysInfo_ModeChange_Init),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvTdSysInfo_ModeChange_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvGasSysInfo_ModeChange_Init),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvLmmSysInfo_ModeChange_Init)
#endif
};

/* NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SlaveMode_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlModeChangeWaitSlaveModeCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf ),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvGasUtranModeCnf_ModeChange_WaitSlaveModeCnf ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf ),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf )
};

/* NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF ������ */
NAS_ACT_STRU        g_astNasUtranCtrlModeChangeWaitMasterModeCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf ),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF,
                      NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf )
};

/* ģʽ���״̬���������Ϣ ״̬�� */
NAS_STA_STRU        g_astNasUtranCtrlModeChangeStaTbl[]   =
{
    /* ģʽ���״̬����ʼ��״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MODE_CHANGE_STA_INIT,
                      g_astNasUtranCtrlModeChangeInitActTbl ),

    /* ģʽ���״̬���ȴ���ģ�ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF,
                      g_astNasUtranCtrlModeChangeWaitSlaveModeCnfActTbl ),

    /* ģʽ���״̬���ȴ���ģ�ظ�״̬ */
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF,
                      g_astNasUtranCtrlModeChangeWaitMasterModeCnfActTbl )
};
VOS_UINT32 NAS_UTRANCTRL_GetModeChangeStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasUtranCtrlModeChangeStaTbl)/sizeof(NAS_STA_STRU));
}


NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetModeChangeFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlModeChangeFsmDesc);
}

#endif





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

