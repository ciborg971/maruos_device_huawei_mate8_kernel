

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "MsccMmcInterface.h"
#include "Nasrrcinterface.h"
#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
/* ɾ��ExtAppMmcInterface.h*/
#include "NasMmcFsmPowerOff.h"
#include "NasMmcFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"

#include "MsccMmcInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_POWER_OFF_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������:�ػ���״̬������ */
NAS_FSM_DESC_STRU                       g_stNasMmcPowerOffFsmDesc;

/* NAS_MMC_FSM_L2_POWER_OFF::NAS_MMC_L2_STA_POWEROFF_INIT������ */
NAS_ACT_STRU   g_astNasPoweroffInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_OFF_REQ,
                      NAS_MMC_RcvTafPowerOffReq_PowerOff_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_POWER_SAVE_REQ,
                      NAS_MMC_RcvMsccPowerSaveReq_PowerOff_Init),

};

/* NAS_MMC_FSM_L2_POWER_OFF::NAS_MMC_L2_STA_WAIT_MM_POWEROFF_CNF������ */
NAS_ACT_STRU   g_astNasPoweroffWaitMmPoweroffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_POWER_OFF_CNF,
                      NAS_MMC_RcvMmPowerOffCnf_PowerOff_WaitMmPoweroffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_POWER_OFF_CNF,
                      NAS_MMC_RcvGmmPowerOffCnf_PowerOff_WaitMmPoweroffCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_POWEROFF_CNF,
                      NAS_MMC_RcvTiWaitMmPowerOffCnfExpired_PowerOff_WaitMmPowerOffCnf),
};

/* POWER OFF:�ȴ���ģ�ػ��ظ�״̬�� */
NAS_ACT_STRU   g_astNasPoweroffWaitMasterModePowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitMasterModePowerOffCnf),

#if   (FEATURE_ON == FEATURE_LTE)

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_CNF,
                      NAS_MMC_RcvLmmStopCnf_PowerOff_WaitMasterModePowerOffCnf),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MASTER_MODE_POWEROFF_CNF,
                      NAS_MMC_RcvTiWaitMasterModePowerOffCnfExpired_PowerOff_WaitMasterModePowerOffCnf)
};


NAS_ACT_STRU   g_astNasPoweroffWaitSlaveModePowerOffCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvGasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_MMC_RcvWasPowerOffCnf_PowerOff_WaitSlaveModePowerOffCnf),

#if   (FEATURE_ON == FEATURE_LTE)

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_CNF,
                      NAS_MMC_RcvLmmStopCnf_PowerOff_WaitSlaveModePowerOffCnf),
#endif

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_SLAVE_MODE_POWEROFF_CNF,
                      NAS_MMC_RcvTiWaitSlaveModePowerOffCnfExpired_PowerOff_WaitSlaveModePowerOffCnf)
};


#if   (FEATURE_ON == FEATURE_LTE)

/* NAS_MMC_L1_STA_POWER_OFF::NAS_MMC_L2_STA_WAIT_LMM_USIM_STATUS_CNF������ */
NAS_ACT_STRU   g_astNasPoweroffWaitLmmUsimStatusCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_USIM_STATUS_CNF,
                      NAS_MMC_RcvLmmUsimStatusCnf_PowerOff_WaitLmmUsimStatusCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_USIM_STATUS_CNF,
                      NAS_MMC_RcvTiWaitLmmUsimStatusExpired_PowerOff_WaitLmmUsimStatusCnf),
};

NAS_ACT_STRU   g_astNasPoweroffWaitLmmSuspendCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_PowerOff_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitLmmSuspendCnfExpired_PowerOff_WaitLmmSuspendCnf),
};
#endif

NAS_ACT_STRU   g_astNasMmcPoweroffWaitEpsConnRelIndTbl[]               =
{
    /* Lģע��Ĺ����л��յ��������Ӵ��ڵı�־��Ҫ���� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PowerOff_WaitEpsConnRelInd),

    /* �������ͷŶ�ʱ����ʱ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PowerOff_WaitEpsConnRelInd),

    /* ����suspend״̬�� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PowerOff_WaitEpsConnRelInd),
};

/* NAS_MMC_POWER_OFF_STA_WAIT_RRC_CONN_REL_IND ������ */
NAS_ACT_STRU   g_astNasMmcPowerOffWaitCsPsConnRelActTbl[]              =
{
    /* �յ� GMM �� SIGNALING_STATUS_IND ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_PowerOff_WaitRrcConnRelInd),

    /* �յ� GMM �ĵ� TBF_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_PowerOff_WaitRrcConnRelInd),

    /* �յ� MM �� MMCMM_RR_CONN_INFO_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmConnInfoInd_PowerOff_WaitRrcConnRelInd),

    /* �յ� MM �� RR_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmRrRelInd_PowerOff_WaitRrcConnRelInd),

    /* �յ� WAS �� RRMM_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PowerOff_WaitRrcConnRelInd),

    /* �յ� WAS �� RRMM_SUSPEND_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_PowerOff_WaitRrcConnRelInd),

    /* �յ� GAS �� RRMM_SUSPEND_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_PowerOff_WaitRrcConnRelInd),

    /* �յ���ʱ����ʱ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_RRC_CONN_REL,
                      NAS_MMC_RcvTiWaitRrcConnRelExpired_PowerOff_WaitRrcConnRelInd),

};

NAS_ACT_STRU   g_astNasMmcPowerOffWaitWasSuspendCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PowerOff_WaitAsSuspendCnf),
};

NAS_ACT_STRU   g_astNasMmcPowerOffWaitGasSuspendCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PowerOff_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PowerOff_WaitAsSuspendCnf),

};




/* Э��ջ�ػ�L2״̬�� */
NAS_STA_STRU g_astNasMmcPowerOffStaTbl[] =
{
    /*****************���������κ�����ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_POWEROFF_INIT,
                      g_astNasPoweroffInitActTbl ),

    /*****************���弰�ػ���������ʼ��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_MM_POWEROFF_CNF,
                      g_astNasPoweroffWaitMmPoweroffCnfActTbl ),

    /*****************������ģ�ػ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_MASTER_MODE_POWEROFF_CNF,
                      g_astNasPoweroffWaitMasterModePowerOffCnfActTbl ),

    /*****************�����ģ�ػ�״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_SLAVE_MODE_POWEROFF_CNF,
                      g_astNasPoweroffWaitSlaveModePowerOffCnfActTbl ),

#if   (FEATURE_ON == FEATURE_LTE)
    /*****************������פ��������פ��ʱ���״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_LMM_USIM_STATUS_CNF,
                      g_astNasPoweroffWaitLmmUsimStatusCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_LMM_SUSPEND_CNF,
                      g_astNasPoweroffWaitLmmSuspendCnfActTbl ),
#endif

    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_EPS_CONN_REL_IND,
                      g_astNasMmcPoweroffWaitEpsConnRelIndTbl ),

    /*  �ȴ������ͷŽ�� */
    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_RRC_CONN_REL_IND,
                      g_astNasMmcPowerOffWaitCsPsConnRelActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_GAS_SUSPEND_CNF,
                      g_astNasMmcPowerOffWaitGasSuspendCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_POWER_OFF_STA_WAIT_WAS_SUSPEND_CNF,
                      g_astNasMmcPowerOffWaitWasSuspendCnfActTbl ),

};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPowerOffStaTblSize
 ��������  : ��ȡ�ػ�״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:�ػ�״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPowerOffStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcPowerOffStaTbl)/sizeof(NAS_STA_STRU));
}


/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPowerOffFsmDescAddr
 ��������  : ��ȡ�ػ�״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��ػ�״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��9��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetPowerOffFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcPowerOffFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

