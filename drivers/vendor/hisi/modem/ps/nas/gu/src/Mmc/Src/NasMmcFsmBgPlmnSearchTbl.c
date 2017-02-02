

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcFsmMain.h"
#include "NasMmcFsmBgPlmnSearch.h"
#include "NasMmcFsmBgPlmnSearchTbl.h"
#include "NasMmcTimerMgmt.h"
#include "MmcGmmInterface.h"
/* ɾ��ExtAppMmcInterface.h*/
#include "siappstk.h"

#include "MsccMmcInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_BG_PLMN_SEARCH_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* NAS MMC״̬������:��֧��GU�ı����������״̬������*/
NAS_FSM_DESC_STRU                       g_stNasMmcBgPlmnSearchFsmDesc;


/* NAS_MMC_BG_PLMN_SEARCH_STA_INIT ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchInitActTbl[]             =
{
    /* �յ�HPLMN��ʱ����ʱ��Ϣ */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_HPLMN_TIMER,
                     NAS_MMC_RcvTiHPlmnTimerExpired_BgPlmnSearch_Init),

    /* �յ�High_Prio_Rat_HPLMN��ʱ����ʱ��Ϣ */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_HIGH_PRIO_RAT_HPLMN_TIMER,
                     NAS_MMC_RcvTiHighPrioRatHPlmnTimerExpired_BgPlmnSearch_Init),

    /* �յ�10s�����Գ��Ը����ȼ�������ʱ����ʱ��Ϣ */
    NAS_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_NAS_MMC_PERIOD_TRYING_HIGH_PRIO_PLMN_SEARCH,
                     NAS_MMC_RcvTiPeriodHighPrioPlmnSearchExpired_BgPlmnSearch_Init),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasBgPlmnSearchCnfActTbl[] =
{
   NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                     MMCMMC_ABORT_FSM_REQ,
                     NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_SYS_INFO_IND,
                     NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_REL_IND,
                     NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_BG_PLMN_SEARCH_CNF,
                     NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitWasBgPlmnSearchCnf),

   NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                     TI_NAS_MMC_WAIT_WAS_BG_PLMN_SEARCH_CNF,
                     NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitWasBgPlmnSearchCnf),


   NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                     RRMM_AREA_LOST_IND,
                     NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgPlmnSearchCnf),


};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasBgPlmnSearchCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitGasBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitGasBgPlmnSearchCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgPlmnSearchCnf),


};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasSuspendCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasSuspendCnfActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasBgPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitWasBgStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitWasBgStopCnf),


    /* MMC����stop bg search cnfʱ�ͽ�����bg search cnf��Ϣ�Գ壬�������
       �ظ�stop bg search cnfǰ���ܻ���suspend ind��MMC�ڸ�״̬�޷��������Ϣ,
       ����յ�������search cnf�����յ�stop search cnf,��L1 ������ϵͳָʾ */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitAsBgStopCnf),
};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasBgPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasBgPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasBgStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitGasBgStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitGasBgStopCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvRrMmAreaLostInd_BgPlmnSearch_WaitGasBgStopCnf),


    /* MMC����stop bg search cnfʱ�ͽ�����bg search cnf��Ϣ�Գ壬�������
       �ظ�stop bg search cnfǰ���ܻ���suspend ind��MMC�ڸ�״̬�޷��������Ϣ,
       ����յ�������search cnf�����յ�stop search cnf,��L1 ������ϵͳָʾ */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitAsBgStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasFastPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasFastPlmnStopCnf),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitAsFastPlmnStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasFastPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasFastPlmnStopCnf),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitAsFastPlmnStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_FAST_SEARCH_CNF ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasPlmnFastSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_BgPlmnSearch_WaitWasPlmnFastSearchCnf),
};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_FAST_SEARCH_CNF ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasPlmnFastSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_BgPlmnSearch_WaitGasPlmnFastSearchCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasSysinfoIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoInd),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasSysinfoIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfo),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoInd),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitCsPsRegIndActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* �յ�MM��Abort��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM(WUEPS_PID_MM,
                     MMMMC_ABORT_IND,
                     NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /*���緢���detach*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* AS�ϱ���ǰ���� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_BgPlmnSearch_WaitCsPsRegRsltInd),


    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* �յ�MSCC SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitCsPsRegRsltInd),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CSPS_REG_IND,
                      NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_BgPlmnSearch_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitCsPsRegRsltInd),

};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitCsPsConnRelActTbl[]   =
{
    /* �յ� Abort ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� GMM �� SIGNALING_STATUS_IND ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� GMM �� DETACH_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� GMM �� TBF_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� GMM �� SERVICE_REQUEST_RESULT_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� MM �� RR_CONN_INFO_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmConnInfoInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� MM �� RR_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmRrRelInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� MM �� CM_SERVICE_REJECT_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_BgPlmnSearch_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ�MM��Abort��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_ABORT_IND,
                      NAS_MMC_RcvMmAbortInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� WAS �� RRMM_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� WAS �� RRMM_SUSPEND_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvRrMmSuspendInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� GAS �� RRMM_SUSPEND_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvRrMmSuspendInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� WAS �� SYS_INFO_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ� GAS �� SYS_INFO_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ�MSCC SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitRrcConnRelInd),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitRrcConnRelInd),

    /* �յ���ʱ����ʱ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_RRC_CONN_REL,
                      NAS_MMC_RcvTiWaitRrcConnRelExpired_BgPlmnSearch_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_BgPLmnSearch_WaitRrcConnRelInd),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF_RECAMP_VPLMN ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasSuspendCnfReCampVPlmnActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitWasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF_RECAMP_VPLMN ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitGasSuspendCnfReCampVPlmnActTbl[] =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_BgPlmnSearch_WaitGasSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF_RECAMP_VPLMN ������*/
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasPlmnSearchCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnSearchCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF_RECAMP_VPLMN ������*/
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasPlmnSearchCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnSearchCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitWasPlmnStopCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchStopCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitWasPlmnStopCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasPlmnStopCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_BgPlmnSearch_WaitGasPlmnStopCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND_RECAMP_VPLMN ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitWasSysinfoIndReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvRrMmSysInfoInd_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitWasSysInfoExpired_BgPlmnSearch_WaitWasSysInfoIndReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND_RECAMP_VPLMN ������ */
NAS_ACT_STRU  g_astNasMmcBgPlmnSearchWaitGasSysinfoIndReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitGasSysInfoReCampVPlmn),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGrrMmSysInfoInd_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitGasSysInfoExpired_BgPlmnSearch_WaitGasSysInfoIndReCampVPlmn),

};

#if (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmBgPlmnSearchCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitBgPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgPlmnSearchCnf),

};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmBgPlmnStopCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLmmSysInfoInd_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnStopCnf_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_BG_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiBgStopCnfExpired_BgPlmnSearch_WaitLmmBgStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_AREA_LOST_IND,
                      NAS_MMC_RcvLmmMmcAreaLostInd_BgPlmnSearch_WaitLmmBgStopCnf),

    /* MMC����stop bg search cnfʱ�ͽ�����bg search cnf��Ϣ�Գ壬�������
       �ظ�stop bg search cnfǰ���ܻ���suspend ind��MMC�ڸ�״̬�޷��������Ϣ,
       ����յ�������search cnf�����յ�stop search cnf,��L1 ������ϵͳָʾ */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_BG_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmBgStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmPlmnFastSearchCnfTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                       MMCMMC_ABORT_FSM_REQ,
                       NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchCnf_BgPlmnSearch_WaitLmmPlmnFastSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_BgPlmnSearch_WaitLmmPlmnFastSearchCnf),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmFastPlmnStopCnfTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchStopCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_BgPlmnSearch_WaitLmmFastPlmnStopCnf),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvBgPlmnSearchCnf_BgPlmnSearch_WaitLmmFastPlmnStopCnf),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLSysInfoIndActTbl[]   =
{
    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoInd),

    /* ��Lģ��ϵͳ��Ϣ��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoInd),


    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�   NAS_MMC_RcvLmmMmcRegStatusInd_BgPlmnSearch_WaitLSysInfoInd()������ */
    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitEpsRegRsltIndActTbl[]   =
{
    /* Lģע��Ĺ����л��յ��������Ӵ��ڵı�־��Ҫ���� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /* ɾ��LTE�ϱ�����״̬��ע��״̬�Ľӿ�   NAS_MMC_RcvLmmMmcRegStatusInd_BgPlmnSearch_WaitEpsRegRsltInd()������ */
    /* Deleted by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */



    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* ����suspend״̬�� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_REG_IND,
                      NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_BgPlmnSearch_WaitEpsRegRsltInd),

    /* ��ע���ʱ�������� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_BgPlmnSearch_WaitEpsRegRsltInd),

    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsRegRsltInd),


    /* �յ�MSCC SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsRegRsltInd),


    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_BgPlmnSearch_WaitEpsRegRsltInd),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitEpsConnRelInd[]   =
{

    /* Lģע��Ĺ����л��յ��������Ӵ��ڵı�־��Ҫ���� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* �������ͷŶ�ʱ����ʱ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsConnRelIndExpired_BgPlmnSearch_WaitEpsConnRelInd),

    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* ����suspend״̬�� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_BgPlmnSearch_WaitEpsConnRelInd),

    /* �յ�MSCC SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_BgPlmnSearch_WaitEpsConnRelInd),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_BgPlmnSearch_WaitEpsConnRelInd),

    /* �뱱��ȷ��:ע���������Ҫ���������detach��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_BgPlmnSearch_WaitEpsConnRelInd),

    /* ע���������Ҫ�����û���detach��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmMmcDetachCnf_BgPlmnSearch_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_BgPlmnSearch_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_BgPlmnSearch_WaitEpsConnRelInd),

};


/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmPlmnSearchCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmSrchCnf_BgPlmnSearch_WaitLmmPlmnSearchCnfReCampVPlmn),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF_RECAMP_VPLMN ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_BgPlmnSearch_WaitLmmSuspendCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_BgPlmnSearch_WaitAsSuspendCnf),

};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLmmPlmnStopCnfReCampVPlmnActTbl[]   =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchCnf_BgPlmnSearch_WaitLmmPlmnStopCnfReCampVPlmn),
};

/* NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND_RECAMP_VPLMN ������ */
NAS_ACT_STRU   g_astNasMmcBgPlmnSearchWaitLSysInfoIndReCampVPlmnActTbl[]   =
{
    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn),

    /* ��Lģ��ϵͳ��Ϣ��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_BgPlmnSearch_WaitLSysInfoIndReCampVPlmn),

};
#endif



/* NAS MMCģ��BG PLMN SEARCHע��L2״̬�� */
NAS_STA_STRU g_astNasMmcFsmBgPlmnSearchStaTbl[] =
{
    /* �ȴ���Ϣ״̬ */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_INIT,
                      g_astNasMmcBgPlmnSearchInitActTbl),

    /*  �ȴ�Wģ�ϱ�BG������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitWasBgPlmnSearchCnfActTbl),

    /*  �ȴ�Gģ�ϱ�BG������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasBgPlmnSearchCnfActTbl),

    /*  �ȴ�Wģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF,
                       g_astNasMmcBgPlmnSearchWaitWasSuspendCnfActTbl),

    /*  �ȴ�Gģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasSuspendCnfActTbl),

    /*  �ȴ�Wģ�ϱ�ֹͣBG������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_BG_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitWasBgPlmnStopCnfActTbl ),

    /*  �ȴ�Gģ�ϱ�ֹͣBG������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_BG_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasBgPlmnStopCnfActTbl ),

    /*  �ȴ�Wģ�ϱ�ֹͣ����ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_FAST_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitWasFastPlmnStopCnfActTbl ),

    /*  �ȴ�Gģ�ϱ�ֹͣ����ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_FAST_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitGasFastPlmnStopCnfActTbl ),

    /*  �ȴ�Wģ�ϱ�����ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_FAST_SEARCH_CNF,
                       g_astNasMmcBgPlmnSearchWaitWasPlmnFastSearchCnfActTbl ),

    /*  �ȴ�Gģ�ϱ�����ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_FAST_SEARCH_CNF,
                       g_astNasMmcBgPlmnSearchWaitGasPlmnFastSearchCnfActTbl ),

    /*  �ȴ�Wģ�ϱ�ϵͳ��Ϣ*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND,
                      g_astNasMmcBgPlmnSearchWaitWasSysinfoIndActTbl ),

    /*  �ȴ�Gģ�ϱ�ϵͳ��Ϣ*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND,
                      g_astNasMmcBgPlmnSearchWaitGasSysinfoIndActTbl ),

    /*  �ȴ�CS+PS���ע����*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_CSPS_REG_IND,
                      g_astNasMmcBgPlmnSearchWaitCsPsRegIndActTbl ),

    /*  �ȴ�GU�����ͷ� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_RRC_CONN_REL_IND,
                      g_astNasMmcBgPlmnSearchWaitCsPsConnRelActTbl ),

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SUSPEND_CNF_RECAMP_VPLMN,
                       g_astNasMmcBgPlmnSearchWaitWasSuspendCnfReCampVPlmnActTbl),

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SUSPEND_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasSuspendCnfReCampVPlmnActTbl),

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ�ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitWasPlmnSearchCnfReCampVPlmnActTbl ),

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ�ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasPlmnSearchCnfReCampVPlmnActTbl ),

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ�ָֹͣ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitWasPlmnStopCnfReCampVPlmnActTbl ),

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ�ָֹͣ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasPlmnStopCnfReCampVPlmnActTbl ),

    /*  ��VPLMNʱ�ȴ�Wģ�ϱ�ϵͳ��Ϣ*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_WAS_SYSINFO_IND_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitWasSysinfoIndReCampVPlmnActTbl ),

    /*  ��VPLMNʱ�ȴ�Gģ�ϱ�ϵͳ��Ϣ*/
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_GAS_SYSINFO_IND_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitGasSysinfoIndReCampVPlmnActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /* �ȴ�Lģ�ϱ�BG������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmBgPlmnSearchCnfActTbl),

    /*  �ȴ�Lģ�ϱ�ֹͣBG������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_BG_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmBgPlmnStopCnfActTbl),

    /*  �ȴ�Lģ�ϱ�����ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_FAST_SEARCH_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmPlmnFastSearchCnfTbl),


    /*  �ȴ�Lģ�ϱ�ֹͣ����ָ��������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_FAST_PLMN_STOP_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmFastPlmnStopCnfTbl),


    /* �ȴ�Lģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF,
                      g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfActTbl),

    /* �ȴ�Lģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND,
                      g_astNasMmcBgPlmnSearchWaitLSysInfoIndActTbl ),

    /* �ȴ�epsע���� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_REG_IND,
                      g_astNasMmcBgPlmnSearchWaitEpsRegRsltIndActTbl ),

    /* �ȴ�Lģ�����ͷŽ�� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_EPS_CONN_REL_IND,
                      g_astNasMmcBgPlmnSearchWaitEpsConnRelInd ),


    /* ��VPLMNʱ�ȴ�Lģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLmmPlmnSearchCnfReCampVPlmnActTbl),

    /* ��VPLMNʱ�ȴ�Lģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SUSPEND_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLmmSuspendCnfReCampVPlmnActTbl),

    /* ��VPLMNʱ�ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLmmPlmnStopCnfReCampVPlmnActTbl),

    /* ��VPLMNʱ�ȴ�Lģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_BG_PLMN_SEARCH_STA_WAIT_LMM_SYSINFO_IND_RECAMP_VPLMN,
                      g_astNasMmcBgPlmnSearchWaitLSysInfoIndReCampVPlmnActTbl ),
#endif
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/



VOS_UINT32 NAS_MMC_GetBgPlmnSearchStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcFsmBgPlmnSearchStaTbl)/sizeof(NAS_STA_STRU));
}




NAS_FSM_DESC_STRU * NAS_MMC_GetBgPlmnSearchFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcBgPlmnSearchFsmDesc);
}










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
