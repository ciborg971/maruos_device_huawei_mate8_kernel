

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlFsmMainTbl.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlFsmMain.h"
#include "MsccMmcInterface.h"
/* ɾ��ExtAppMmcInterface.h*/
#include "NasUtranCtrlMntn.h"

#include "MmcGmmInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_MAIN_TBL_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

/* Ԥ����״̬�� */
NAS_FSM_DESC_STRU                       g_stNasUtranCtrlMainFsmDesc;


/**************************************************************************/
/*����״̬��������� */
/**************************************************************************/

/* IDLE״̬���������Ϣ������ */
NAS_ACT_STRU        g_astNasUtranCtrlMainProcessActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvWasSysInfo_Main ),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvGasSysInfo_Main ),

    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvTdSysInfo_Main ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_UTRANCTRL_RcvLmmSysInfo_Main ),
#endif

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_START_CNF,
                      NAS_UTRANCTRL_RcvMmcGmmStartCnf_Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MM_START_CNF,
                      NAS_UTRANCTRL_RcvMmcGmmStartCnf_Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_UTRANCTRL_RcvPlmnSpecialReq_Main),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvPlmnSearchReq_Main),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_UTRANCTRL_RcvMsccAcqReq_Main),


    /* �յ�Was�Ŀ����ظ���Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvWasStartCnf_Main),

    /* �յ�Was�Ŀ����ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasStartCnfExpired_Main),

    /* �յ�Td�Ŀ����ظ���Ϣ */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_START_CNF,
                      NAS_UTRANCTRL_RcvTdStartCnf_Main),

    /* �յ�TD�Ŀ����ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_START_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdStartCnfExpired_Main),

    /* �յ�Was�Ĺػ��ظ���Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvWasPowerOffCnf_Main),

    /* �յ�WAS�Ĺػ��ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_Main),


    /* �յ�TD�Ĺػ��ظ���Ϣ */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTdPowerOffCnf_Main),

    /* �յ�TD�Ĺػ��ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_Main),

    /* �յ�Was��syscfg���ûظ���Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvWasSysCfgCnf_Main),

    /* �յ�WAS��SYSCFG�ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasSysCfgCnfExpired_Main),

    /* �յ�Td��syscfg���ûظ���Ϣ */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_SYS_CFG_CNF,
                      NAS_UTRANCTRL_RcvTdSysCfgCnf_Main),

    /* �յ�TD��SYSCFG�ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_SYSCFG_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdSysCfgCnfExpired_Main),

    /* �յ�Was�������ظ���Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvWasPlmnSrchCnf_Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                     MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_REQ,
                     NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_Main),


    /* �յ�MMC���͵���������W��Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_W_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_Main),


    /* �յ�MMC���͵���������TDS��Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_SKIP_SEARCH_TDS_IND,
                      NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_Main),

    /* �յ�WAS�������ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_UTRANCTRL_RcvWasRrMmRelInd_Main),

    /* �յ�TD�������ظ���Ϣ */
    NAS_ACT_TBL_ITEM( TPS_PID_RRC,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTdPlmnSrchCnf_Main),

    /* �յ�TD�������ظ���ʱ��Ϣ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_Main),

    /* �յ�Was�������ظ���Ϣ */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_UTRANCTRL_RcvGasPlmnSrchCnf_Main),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_UTRANCTRL_RcvRcvLmmPlmnSrchCnf_Main ),
#endif
    /* �յ�Was�������ظ���Ϣ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_ANYCELL_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvMmcInterSearchReq_Main),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_SEARCH_REQ,
                      NAS_UTRANCTRL_RcvMmcInterSearchReq_Main),

     NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_LIST_REQ,
                      NAS_UTRANCTRL_RcvMmcInterSearchReq_Main),


    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_HPLMN_TIMER,
                      NAS_UTRANCTRL_RcvTiHplmnTimerExpired_Main),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH,
                      NAS_UTRANCTRL_RcvTiTryingHighPrioPlmnSearchExpired_Main),

#ifdef __PS_WIN32_RECUR__
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      NAS_UTRANCTRL_OM_MSG_LOG_RUNNING_CONTEXT_FOR_PC_REPLAY,
                      NAS_UTRANCTRL_RestoreContextData_Main),

#endif

};

/* MAIN״̬���������Ϣ ״̬�� */
NAS_STA_STRU        g_astNasUtranCtrlMainProcessFsmTbl[]   =
{
    NAS_STA_TBL_ITEM( NAS_UTRANCTRL_MAIN_STA_INIT,
                      g_astNasUtranCtrlMainProcessActTbl )
};


VOS_UINT32 NAS_UTRANCTRL_GetMainProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasUtranCtrlMainProcessFsmTbl)/sizeof(NAS_STA_STRU));
}


NAS_FSM_DESC_STRU * NAS_UTRANCTRL_GetMainFsmDescAddr(VOS_VOID)
{
    return (&g_stNasUtranCtrlMainFsmDesc);
}
#endif








#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
