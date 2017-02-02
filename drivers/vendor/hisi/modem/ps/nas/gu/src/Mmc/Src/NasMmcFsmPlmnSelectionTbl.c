/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : NasMmcFsmPlmnSelectionTbl.c
  �� �� ��   : ����
  ��    ��   : sunxibo /46746
  ��������   : 2011��07��04��
  ����޸�   :
  ��������   : NAS ��״̬��PlmnSelection״̬�����
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2011��07��04��
    ��    ��   : sunxibo /46746
    �޸�����   : Added for V7R1 phase II

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "NasMmcFsmMain.h"
#include "NasMmcFsmPlmnSelection.h"
#include "NasMmcFsmPlmnSelectionTbl.h"
#include "NasMmcTimerMgmt.h"

#include "MsccMmcInterface.h"

#include "MmcGmmInterface.h"
/* ɾ��ExtAppMmcInterface.h*/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_PLMN_SELECTION_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* NAS MMC״̬������:�������״̬������*/
NAS_FSM_DESC_STRU                       g_stNasMmcPlmnSelectionFsmDesc;

/* NAS_MMC_PLMN_SELECTION_STA_PLMN_SEARCH_INIT ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionInitActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSearchReq_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMmcMmcInterPlmnSearchReq_PlmnSelection_Init),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    /* MMA���͹����Ļ�ȡ���� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_ACQ_REQ,
                      NAS_MMC_RcvMsccAcqReq_PlmnSelection_Init),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasPlmnSearchCnfActTbl[]        =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SEARCHED_PLMN_INFO_IND,
                      NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvInterAbortUtranCtrlPlmnSearchCnf_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasPlmnSearchCnfActTbl[]        =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_PlmnSelection_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasPlmnSearchCnfExpired_PlmnSelection_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SEARCHED_PLMN_INFO_IND,
                      NAS_MMC_RcvSearchedPlmnInfoInd_PlmnSelection_WaitGasPlmnSearchCnf),

};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SEARCHED_PLMN_INFO_IND,
                      NAS_MMC_RcvLmmSearchedPlmnInfoInd_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnf),

};
#endif

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf),
};


#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmSuspendCnfActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_PlmnSelection_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnf),
};

#endif


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitWasPlmnStopCnf),


    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitWasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),

};


/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchStopCnf_PlmnSelection_WaitGasPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopCnfExpired_PlmnSelection_WaitGasPlmnStopCnf),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSearchCnf_PlmnSelection_WaitGasPlmnStopCnf),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),


};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchStopCnf_PlmnSelection_WaitLmmPlmnStopCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnf),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnf),


    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),
};
#endif

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWSysInfoIndActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitWasSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGSysInfoIndActTbl[]       =
{

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvSysInfoInd_PlmnSelection_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SYS_INFO,
                      NAS_MMC_RcvTiWaitSysInfoExpired_PlmnSelection_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitGasSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitCsPsRegRsltIndActTbl[]              =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CSPS_REG_IND,
                      NAS_MMC_RcvTiWaitCsPsRegRsltIndExpired_PlmnSelection_WaitCsPsRegRsltInd),

    /*���緢���detach*/
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitCsPsRegRsltInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitCsPsRegRsltInd),

    /* AS�ϱ���ǰ���� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_AREA_LOST_IND,
                      NAS_MMC_RcvAreaLostInd_PlmnSelection_WaitCsPsRegRsltInd),


    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitCsPsRegRsltInd),

    /* �յ�MMA SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitCsPsRegRsltInd),

    /* �յ�MMA ָ��������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitCsPsRegRsltInd),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitCsPsRegRsltInd),

    /* �յ�MM��Abort��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_ABORT_IND,
                      NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitCsPsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitCsPsRegRsltInd),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitCsPsConnRelActTbl[]              =
{
    /* �յ� GMM �� SIGNALING_STATUS_IND ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_SIGNALING_STATUS_IND,
                      NAS_MMC_RcvGmmSignalingStatusInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� GMM �ĵ� DETACH_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_NETWORK_DETACH_IND,
                      NAS_MMC_RcvGmmNetworkDetachInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� GMM �ĵ� TBF_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      MMCGMM_TBF_REL_IND,
                      NAS_MMC_RcvGmmTbfRelInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� GMM �ĵ� SERVICE_REQUEST_RESULT_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_SERVICE_REQUEST_RESULT_IND,
                      NAS_MMC_RcvGmmServiceRequestResultInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� MM �� SERVICE_REQUEST_RESULT_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_CONN_INFO_IND,
                      NAS_MMC_RcvMmConnInfoInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� MM �� RR_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_RR_REL_IND,
                      NAS_MMC_RcvMmRrRelInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� MM �� CM_SERVICE_REJECT_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMCMM_CM_SERVICE_REJECT_IND,
                      NAS_MMC_RcvCmServiceRejectInd_PlmnSelection_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_GMM,
                      GMMMMC_PS_REG_RESULT_IND,
                      NAS_MMC_RcvGmmPsRegResultInd_PlmnSelection_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_CS_REG_RESULT_IND,
                      NAS_MMC_RcvMmCsRegResultInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� WAS �� RRMM_REL_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_REL_IND,
                      NAS_MMC_RcvRrMmRelInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� WAS �� RRMM_SUSPEND_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvWasSuspendInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� WAS �� SYS_INFO_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SYS_INFO_IND,
                      NAS_MMC_RcvWasSysInfoInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� GAS �� RRMM_SUSPEND_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_IND,
                      NAS_MMC_RcvGasSuspendInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� GAS �� SYS_INFO_IND ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      GRRMM_SYS_INFO_IND,
                      NAS_MMC_RcvGasSysInfoInd_PlmnSelection_WaitRrcConnRelInd),

    /* �յ���ʱ����ʱ��Ϣ�Ĵ���  */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_RRC_CONN_REL,
                      NAS_MMC_RcvTiWaitRrcConnRelExpired_PlmnSelection_WaitRrcConnRelInd),

    /* �յ�MMA ָ��������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitRrcConnRelInd),

    /* �յ�MMA SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitRrcConnRelInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitRrcConnRelInd),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� Abort ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitRrcConnRelInd),

    /* �յ� MM Abort ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MM,
                      MMMMC_ABORT_IND,
                      NAS_MMC_RcvMmAbortInd_PlmnSelection_WaitRrcConnRelInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_LIMIT_SERVICE_CAMP_IND,
                      NAS_MMC_RcvRrmmLimitServiceCampInd_PlmnSelection_WaitRrcConnRelInd),

};

NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitMsccRegReqActTbl[]                =
{
    /* �յ� MMA �� ID_MMA_MMC_REG_REQ ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_REG_REQ,
                      NAS_MMC_RcvMsccRegReq_PlmnSelection_WaitMsccRegReq),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SEARCH_REQ,
                      NAS_MMC_RcvMsccPlmnSrchReq_PlmnSelection_WaitMsccRegReq),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitMsccRegReq),

    /* ��MMA��ע��������Ϣ��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_MSCC_REG_REQ,
                      NAS_MMC_RcvTiWaitMsccRegReqExpired_PlmnSelection_WaitMsccRegReq),

#if   (FEATURE_ON == FEATURE_LTE)
    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitMsccRegReq),

    /* �յ�Lģ�Ĺ���Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitMsccRegReq),

    /* �յ�Lģ�ĳ��������Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitMsccRegReq),

#endif
};

#if   (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLSysInfoIndActTbl[]              =
{
    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoInd),

    /* ��Lģ��ϵͳ��Ϣ��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsRegRsltIndActTbl[]         =
{
    /* Lģע��Ĺ����л��յ��������Ӵ��ڵı�־��Ҫ���� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltInd),

    /* ����suspend״̬�� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_REG_IND,
                      NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltInd),

    /* ��ע���ʱ�������� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltInd),

    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltInd),

    /* �յ�MMA SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltInd),

    /* �յ�MMA ָ��������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltInd),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltInd),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsConnRelInd[]         =
{
    /* Lģע��Ĺ����л��յ��������Ӵ��ڵı�־��Ҫ���� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsConnRelInd),

    /* �������ͷŶ�ʱ����ʱ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsConnRelIndExpired_PlmnSelection_WaitEpsConnRelInd),

    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsConnRelInd),

    /* ����suspend״̬�� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsConnRelInd),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcSuspendRslt_PlmnSelection_WaitEpsConnRelInd),

    /* �յ�MMA ָ��������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsConnRelInd),

    /* �յ�MMA SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsConnRelInd),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsConnRelInd),

    /* �뱱��ȷ��:ע���������Ҫ���������detach��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsConnRelInd),

    /* ע���������Ҫ�����û���detach��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsConnRelInd),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsConnRelInd),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitWasSuspendCnfCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitWasSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitGasSuspendCnfCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_PlmnSelection_WaitGasSuspendCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitAsSuspendCnfExpired_PlmnSelection_WaitAsSuspendCnfCsPsMode1ReCampLte),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfCsPsMode1ReCampLteActTbl[]             =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_CNF,
                      NAS_MMC_RcvLmmAttachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmDetachCnf_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmPlmnSearchCnfExpired_PlmnSelection_WaitLmmPlmnSearchCnfCsPsMode1ReCampLte),

};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfCsPsMode1ReCampLteActTbl[]             =
{
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnStopCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopCnfExpired_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte),

    /* MMC����stop search cnfʱ�ͽ�����search cnf��Ϣ�Գ壬������ڿ���ָ���ѻ�ָ���ѹ��̲�����
       �ظ�stop search cnf��MMC�յ�������search cnf�����յ�stop search cnf*/
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSearchCnf_PlmnSelection_WaitLmmPlmnStopCnfCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitLmmSysInfoIndCsPsMode1ReCampLteActTbl[]              =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte),

    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte),

    /* ��Lģ��ϵͳ��Ϣ��ʱ�Ĵ��� */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SYS_INFO,
                      NAS_MMC_RcvTiWaitLSysInfoExpired_PlmnSelection_WaitLSysInfoIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsRegIndCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* Lģע��Ĺ����л��յ��������Ӵ��ڵı�־��Ҫ���� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_ATTACH_IND,
                      NAS_MMC_RcvLmmMmcAttachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_TAU_RESULT_IND,
                      NAS_MMC_RcvLmmMmcTauResultInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SERVICE_RESULT_IND,
                      NAS_MMC_RcvLmmMmcServiceRsltInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* ����suspend״̬�� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_IND,
                      NAS_MMC_RcvLmmSuspendInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* suspend״̬����ɽ���Ĵ��� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SUSPEND_RSLT_CNF,
                      NAS_MMC_RcvMmcMmcSuspendRslt_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_REG_IND,
                      NAS_MMC_RcvTiWaitEpsRegRsltIndExpired_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* ��ע���ʱ�������� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                     ID_LMM_MMC_AREA_LOST_IND,
                     NAS_MMC_RcvLmmAreaLostInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* �յ�Lģ��ϵͳ��Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SYS_INFO_IND,
                      NAS_MMC_RcvLSysInfoInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* �յ�MMA SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* �յ�MMA ָ��������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SPEC_PLMN_SEARCH_ABORT_REQ,
                      NAS_MMC_RcvTafSpecPlmnSearchAbortReq_PlmnSelection),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_IMS_VOICE_CAP_NOTIFY,
                      NAS_MMC_RcvMsccImsVoiceCapInd_PlmnSelection_WaitEpsRegRsltIndCsPsMode1ReCampLte),
};

/* NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE ������ */
NAS_ACT_STRU   g_astNasMmcPlmnSelectionWaitEpsRelIndCsPsMode1ReCampLteActTbl[]         =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STATUS_IND,
                      NAS_MMC_RcvLmmMmcStatusInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* �������ͷŶ�ʱ����ʱ */
    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_EPS_CONN_REL_IND,
                      NAS_MMC_RcvTiWaitEpsRelIndExpired_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* �յ�MMA ָ��������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_PLMN_SPECIAL_REQ,
                      NAS_MMC_RcvTafPlmnSpecialReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* �յ�MMA SYSCFG������Ϣ�Ĵ��� */
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_SYS_CFG_SET_REQ,
                      NAS_MMC_RcvTafSysCfgReq_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* ����SYSCFG ״̬���Ľ�� */
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_SYSCFG_RSLT_CNF,
                      NAS_MMC_RcvMmcSyscfgRsltCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* �뱱��ȷ��:ע���������Ҫ���������detach��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_IND,
                      NAS_MMC_RcvLmmMmcDetachInd_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),

    /* ע���������Ҫ�����û���detach��� */
    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_DETACH_CNF,
                      NAS_MMC_RcvLmmMmcDetachCnf_PlmnSelection_WaitEpsRelIndCsPsMode1ReCampLte),
};

#endif

/* NAS MMCģ��PLMN SELECTIONע��L2״̬�� */
NAS_STA_STRU g_astNasMmcPlmnSelectionStaTbl[] =
{
    /* �ȴ���Ϣ״̬ */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_INIT,
                          g_astNasMmcPlmnSelectionInitActTbl ),

    /*  �ȴ�Wģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF,
                          g_astNasMmcPlmnSelectionWaitWasPlmnSearchCnfActTbl ),

    /*  �ȴ�Gģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_SEARCH_CNF,
                          g_astNasMmcPlmnSelectionWaitGasPlmnSearchCnfActTbl),

    /*  �ȴ�Wģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF,
                          g_astNasMmcPlmnSelectionWaitWasSuspendCnfActTbl),

    /*  �ȴ�Gģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF,
                          g_astNasMmcPlmnSelectionWaitGasSuspendCnfActTbl),

    /*  �ȴ�Wģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF,
                          g_astNasMmcPlmnSelectionWaitWasPlmnStopCnfActTbl),

    /*  �ȴ�Gģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_PLMN_STOP_CNF,
                          g_astNasMmcPlmnSelectionWaitGasPlmnStopCnfActTbl),

     /*  �ȴ�Wģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SYSINFO_IND,
                          g_astNasMmcPlmnSelectionWaitWSysInfoIndActTbl ),

    /*  �ȴ�Gģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SYSINFO_IND,
                          g_astNasMmcPlmnSelectionWaitGSysInfoIndActTbl ),

    /*  �ȴ�cspsע���� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_CSPS_REG_IND,
                          g_astNasMmcPlmnSelectionWaitCsPsRegRsltIndActTbl ),

    /*  �ȴ������ͷŽ�� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_RRC_CONN_REL_IND,
                          g_astNasMmcPlmnSelectionWaitCsPsConnRelActTbl ),

    /*  �ȴ�MMA��ע������ */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_MSCC_REG_REQ,
                          g_astNasMmcPlmnSelectionWaitMsccRegReqActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /*  �ȴ�Lģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfActTbl),

    /*  �ȴ�Lģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SUSPEND_CNF,
                          g_astNasMmcPlmnSelectionWaitLmmSuspendCnfActTbl),

    /*  �ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfActTbl),

    /*  �ȴ�Lģ�ϱ�ϵͳ��Ϣ��� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND,
                          g_astNasMmcPlmnSelectionWaitLSysInfoIndActTbl ),

    /*  �ȴ�epsע���� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND,
                          g_astNasMmcPlmnSelectionWaitEpsRegRsltIndActTbl ),

    /*  �ȴ�Lģ�����ͷŽ�� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_CONN_REL_IND,
                          g_astNasMmcPlmnSelectionWaitEpsConnRelInd ),

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Wģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitWasSuspendCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Gģ�ϱ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_GAS_SUSPEND_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitGasSuspendCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Lģ�ϱ�������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_SEARCH_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnSearchCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Lģ�ϱ�ֹͣ������� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_PLMN_STOP_CNF_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitLmmPlmnStopCnfCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1�ػ�Lģ�ȴ�Lģ�ϱ�ϵͳ��Ϣ */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_LMM_SYSINFO_IND_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitLmmSysInfoIndCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1�ػ�Lģ�ȴ�EPS���ע���� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REG_IND_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitEpsRegIndCsPsMode1ReCampLteActTbl ),

    /*  CS/PS mode 1�ػ�Lģ�ȴ�EPS�����ͷ� */
    NAS_STA_TBL_ITEM( NAS_MMC_PLMN_SELECTION_STA_WAIT_EPS_REL_IND_CSPSMODE1_RECAMP_LTE,
                          g_astNasMmcPlmnSelectionWaitEpsRelIndCsPsMode1ReCampLteActTbl ),
#endif
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSelectionStaTblSize
 ��������  : ��ȡPLMN SELECTION״̬���Ĵ�С
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_UINT32:PLMN SELECTION״̬���Ĵ�С
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��04��
    ��    ��   : sunxibo 46746
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 NAS_MMC_GetPlmnSelectionStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astNasMmcPlmnSelectionStaTbl)/sizeof(NAS_STA_STRU));
}



/*****************************************************************************
 �� �� ��  : NAS_MMC_GetPlmnSelectionFsmDescAddr
 ��������  : ��ȡ�Զ�����״̬����������
 �������  : ��
 �������  : ��
 �� �� ֵ  : NAS_FSM_DESC_STRU:ָ��PLMN SELECTION״̬����������
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��7��04��
    ��    ��   : sunxibo 46746
    �޸�����   : �����ɺ���

*****************************************************************************/
NAS_FSM_DESC_STRU * NAS_MMC_GetPlmnSelectionFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcPlmnSelectionFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
