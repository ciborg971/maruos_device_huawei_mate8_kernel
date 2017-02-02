

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafFsm.h"
#include "TafMmaFsmMainTbl.h"
#include "TafMmaPreProcAct.h"
#include "TafMmaPreProcTbl.h"
#include "MmaMsccInterface.h"
#include "Taf_Tafm_Remote.h"
#include "MmaAppLocal.h"
#include "Taf_Status.h"
#include "TafMmaSndInternalMsg.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "MmaMsccInterface.h"
#endif
#include "MmaUphyInterface.h"


#include "TafMmaInterface.h"


#include "TafMmaProcUsim.h"

/* Added by y00322978 for CDMA Iteration 17, 2015-7-22, begin */
#include "xcc_mma_pif.h"
#include "hsm_mma_pif.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-22, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_PREPROC_TBL_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/* 预处理状态机 */
TAF_FSM_DESC_STRU                       g_stTafMmaPreFsmDesc;


/*新增状态动作处理表 */

/* 不进状态机处理的消息 动作表 */
TAF_ACT_STRU        g_astTafMmaPreProcessActTbl[]   =
{
#ifdef __PS_WIN32_RECUR__
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      EVT_NAS_MMA_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY,
                      NAS_MMA_RestoreContextData),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      EVT_NAS_MMA_FIXED_PART_CONTEXT,
                      NAS_MMA_RestoreFixedContextData),

#endif

    /* MMA的消息处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_INTER_USIM_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaInterUsimStatusChangeInd_PreProc ),

    TAF_ACT_TBL_ITEM( WUEPS_PID_MMA,
                      MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND,
                      TAF_MMA_RcvMmaSimLockStatusChangeInd_PreProc ),

    /* OM的消息处理 */
    /* Deleted by wx270776 for OM融合, 2015-7-16, begin */

    /* Deleted by wx270776 for OM融合, 2015-7-16, end */


    TAF_ACT_TBL_ITEM( WUEPS_PID_SPY,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOmPhoneModeSetReq_PreProc),

    TAF_ACT_TBL_ITEM( CCPU_PID_CBT,
                      OAM_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_RcvOmPhoneModeSetReq_PreProc),

    /* PHY初始化消息处理 */
    TAF_ACT_TBL_ITEM( DSP_PID_STARTUP,
                      ID_UPHY_MMA_INIT_STATUS_IND,
                      TAF_MMA_RcvUphyInitStatusInd_PreProc),

    /* USIM的消息处理 */
    /* 和hujun确认，USIM不会再报这条消息，通过PIH上报卡状态 */

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_CARDSTATUS_IND,
                      TAF_MMA_RcvPihUsimStatusInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_RACCESS_CNF,
                      MMA_UsimRestrictedAccessCnfMsgProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_HOTINOUT_IND,
                      MMA_ProcHotInOutUsimStatusInd),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_QUERYFILE_CNF,
                      MMA_USIMMaxRecordNumCnfProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_PINHANDLE_CNF,
                      MMA_UsimPINOperateMsgProc),

    /* Deleted by y00307564 for CDMA Iteration 8 2015-2-7 begin */
    /* Deleted by y00307564 for CDMA Iteration 8 2015-2-7 end */
    /* Modified by c00318887 for AT&T phaseII, 2015-3-13, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_USIM,
                      USIMM_READFILE_CNF,
                      TAF_MMA_UsimGetFileRspPreProc),
    /* Modified by c00318887 for AT&T phaseII, 2015-3-13, end */

    TAF_ACT_TBL_ITEM( MAPS_PIH_PID,
                      USIMM_STKREFRESH_IND,
                      TAF_MMA_RcvPihUsimRefreshIndMsgProc),

    /* MSCC的消息处理 */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_RSSI_IND,
                      TAF_MMA_RcvMsccRssiInd_PreProc),
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_LMM_CELL_SIGN_INFO_REPORT_IND,
                      TAF_MMA_RcvMsccLmmCellSignReportInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_MM_INFO_IND,
                      Sta_MmInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SYSTEM_ACQUIRE_END_IND,
                      TAF_MMA_RcvMsccSystemAcquireEndInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SYSTEM_ACQUIRE_START_IND,
                      TAF_MMA_RcvMsccSystemAcquireStartInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_EOPLMN_SET_CNF,
                      TAF_MMA_RcvMsccEOPlmnSetCnf),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_UMTS_CIPHER_INFO_IND,
                      MMA_SaveWCipherInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_GPRS_CIPHER_INFO_IND,
                      MMA_SaveGCipherInfo),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_AC_INFO_CHANGE_IND,
                      TAF_MMA_RcvMsccAcInfoChangeInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SERVICE_STATUS_IND,
                      Sta_ServiceStatusInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_3GPP_SYS_INFO_IND,
                      TAF_MMA_Rcv3gppMsccSysInfoInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CAMP_ON_IND,
                      TAF_MMA_RcvMsccCampOnInd_PreProc),
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_RF_AVAILABLE_IND,
                      TAF_MMA_RcvMsccRfAvailableInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DATATRAN_ATTRI_IND,
                      Sta_DataTranAttri),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_COVERAGE_AREA_IND,
                      Sta_CoverageAreaInd),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_REG_RESULT_IND,
                      TAF_MMA_RcvMsccRegResultInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_NETWORK_CAPABILITY_INFO_IND,
                      TAF_MMA_RcvMsccNetworkCapabilityInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_NET_SCAN_CNF,
                      TAF_MMA_RcvMsccNetScanCnf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ABORT_NET_SCAN_CNF,
                      TAF_MMA_RcvMsccAbortNetScanCnf_PreProc ),


    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_EPLMN_INFO_IND,
                      TAF_MMA_RcvMsccEplmnInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_USIM_AUTH_FAIL_IND,
                      TAF_MMA_RcvMsccUsimAuthFailInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CS_SERVICE_CONN_STATUS_IND,
                      TAF_MMA_RcvMsccCsServiceConnStatusInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SRV_REJ_IND,
                      TAF_MMA_RcvMsccServRejInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_DETACH_IND,
                      TAF_MMA_RcvMsccDetachInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ATTACH_CNF,
                      TAF_MMA_RcvMsccAttachCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SRCHED_PLMN_INFO_IND,
                      TAF_MMA_RcvMsccSrchedPlmnInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ACQ_CNF,
                      TAF_MMA_RcvMsccAcqCnf_PreProc ),

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_ACQ_IND,
                      TAF_MMA_RcvMsccAcqInd_PreProc ),
#endif

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_REG_CNF,
                      TAF_MMA_RcvMsccRegCnf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_POWER_SAVE_CNF,
                      TAF_MMA_RcvMsccPowerSaveCnf_PreProc ),

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PS_SERVICE_CONN_STATUS_IND,
                      TAF_MMA_RcvMsccPsServiceConnStatusInd_PreProc ),
#endif

    /* Added by y00307564 for CDMA Iteration 8 2015-2-5 begin */
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PREF_PLMN_QUERY_CNF,
                      TAF_MMA_RcvMsccPrefPlmnQueryCnf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_PREF_PLMN_SET_CNF,
                      TAF_MMA_RcvMsccPrefPlmnSetCnf_PreProc ),
    /* Added by y00307564 for CDMA Iteration 8 2015-2-5 end */

    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SRV_ACQ_REQ,
                      TAF_MMA_RcvTafSrvAcqReq_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_SRV_ACQ_CNF,
                      TAF_MMA_RcvTiWaitMsccSrvAcqCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SRV_ACQ_CNF,
                      TAF_MMA_RcvMsccSrvAcqCnf_PreProc),
    /* Modified by l00301449 for CDMA Iteration 15, 2015-5-15, end */


    /* 收到at的at+cops=0的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_AUTO_RESEL_REQ,
                      TAF_MMA_RcvPlmnAutoReselReq_PreProc),

    /* 收到at指定搜网请求的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_SPECIAL_SEL_REQ,
                      TAF_MMA_RcvPlmnSpecialSelReq_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PLMN_AUTO_RESEL_CNF,
                      TAF_MMA_RcvTiWaitMsccPlmnAutoSelCnfExpired_PreProc),

     TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PLMN_SPECIAL_SEL_CNF,
                      TAF_MMA_RcvTiWaitMsccSpecPlmnSelCnfExpired_PreProc),

     TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_ABORT_SPEC_PLMN_SEL_CNF,
                      TAF_MMA_RcvTiWaitMsccAbortSpecPlmnSelCnfExpired_PreProc),

     TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_ABORT_PLMN_LIST_CNF,
                      TAF_MMA_RcvTiWaitMsccPlmnListAbortCnfExpired_PreProc),
    /* 收到at列表搜网请求的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PLMN_LIST_REQ,
                      TAF_MMA_RcvAtPlmnList_PreProc),

    /* 收到at syscfg请求的预处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYS_CFG_SET_REQ,
                      TAF_MMA_RcvSysCfgSetReq_PreProc),


    /* AT的消息处理 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_USIM_RESTRICTED_ACCESS,
                      MMA_UsimRestrictedAccessCommandProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_PARA_READ,
                      TAF_MMA_RcvAtParaReadReq_PreProc),

    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, begin */

    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, end */


    /* Deleted by y00322978 for X project phrase 11,2014-03-27,begin*/
    /* Deleted by y00322978 for X project phrase 11,2014-03-27,end*/

    /* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SIM_INSERT_REQ,
                      TAF_MMA_RcvSimInsertReq_PreProc),
    /* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */

    /* Deleted by y00322978 for X project phrase 11, 2015-3-27, begin */
    /* Deleted by y00322978 for X project phrase 11, 2015-3-27, end */


    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_USIM_INFO,
                      MMA_DbProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_CPNN_INFO,
                      MMA_DbProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CIPHER_QRY_REQ,
                      TAF_MMA_RcvCipherQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_LOCATION_INFO_QRY_REQ,
                      TAF_MMA_RcvLocInfoQryReq_PreProc),

    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-24, begin */

    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-24, end */

/* Modified by k902809 for Iteration 11, 2015-3-23, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AC_INFO_QRY_REQ,
                      TAF_MMA_RcvAcInfoQry_PreProc),
/* Modified by k902809 for Iteration 11, Iteration 11 2015-3-23, end */

/* Modified by k902809 for Iteration 11, 2015-3-24, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_COPN_INFO_QRY_REQ,
                      TAF_MMA_RcvCopnInfoQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_EOPLMN_SET_REQ,
                      TAF_MMA_RcvEOPlmnSetReq_PreProc),
/* Modified by k902809 for Iteration 11, Iteration 11 2015-3-24, end */
/* Added by k902809 for Iteration 11, 2015-3-30, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SPN_QRY_REQ,
                      TAF_MMA_RcvSpnQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_MMPLMNINFO_QRY_REQ,
                      TAF_MMA_RcvMMPlmnInfoQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_LAST_CAMP_PLMN_QRY_REQ,
                      TAF_MMA_RcvPlmnQryReq_PreProc),
/* Added by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

/* Modified by k902809 for Iteration 11, 2015-3-30, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_EOPLMN_QRY_REQ,
                      TAF_MMA_RcvEOPlmnQryReq_PreProc),
/* Modified by k902809 for Iteration 11, Iteration 11 2015-3-30, end */

/* Modified by k902809 for Iteration 11, 2015-3-25, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_NET_SCAN_REQ,
                      TAF_MMA_RcvNetScanReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_NET_SCAN_ABORT_REQ,
                      TAF_MMA_RcvAbortNetScanReq_PreProc),
/* Modified by k902809 for Iteration 11, Iteration 11 2015-3-25, end */
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_COPS_FORMAT_TYPE_SET_REQ,
                      TAF_MMA_RcvCopsFormatTypeSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_USIM_STUB_SET_REQ,
                      TAF_MMA_RcvUsimStubSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_REFRESH_STUB_SET_REQ,
                      TAF_MMA_RcvRefreshStubSetReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_AUTO_RESEL_STUB_SET_REQ,
                      TAF_MMA_RcvAutoReselStubSetReq_PreProc),

    /* Modified by h00313353 for Iteration 13, 2015-4-17, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ATTACH_STATUS_QRY_REQ,
                      TAF_MMA_RcvAttachStatusQry_PreProc),
    /* Modified by h00313353 for Iteration 13, 2015-4-17, end */


    /* Deleted by y00307564 for CDMA Iteration 8 2015-2-4 begin */

    /* Deleted by y00307564 for CDMA Iteration 8 2015-2-4 end */

    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, begin */
    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-26, end */

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_TYPE_SET_REQ,
                      TAF_MMA_RcvPrefPlmnTypeSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_MT_POWER_DOWN_REQ,
                      TAF_MMA_RcvPowerDownReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CERSSI_SET_REQ,
                      TAF_MMA_RcvCerssiSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CERSSI_QRY_REQ,
                      TAF_MMA_RcvCerssiQryReq_PreProc),


    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_OP_PIN_REQ,
                      MMA_PhoneProc),

    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-25, begin */
    /* Deleted by y00322978 for CDMA 1X Iteration 11, 2015-3-25, end */

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_ME_PERSONAL_REQ,
                      MMA_PhoneProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_AT,
                      TAF_MSG_MMA_SET_PIN,
                      MMA_SetCPin),

#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_VOICE_CAP_IND,
                      TAF_MMA_RcvMsccImsVoiceCapInd_PreProc),

    /* 定时处理已经下移到MSCC模块，这里删除定时器处理逻辑 */
#endif

    /* 定时器消息 */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TAF_MMA,
                      MMA_TimeExpired),

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_OTHER_MODEM_INFO_NOTIFY,
                      TAF_MMA_RcvMtcOtherModemInfoNotify_PreProc),
    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_NCELL_INFO_IND,
                      TAF_MMA_RcvMtcNcellInfoInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_PS_TRANSFER_IND,
                      TAF_MMA_RcvMtcPsTransferInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MTC,
                      ID_MTC_MMA_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY,
                      TAF_MMA_RcvMtcOtherModemDplmnNplmnInfoNotify_PreProc),

#endif

    /* Deleted by y00307564 for CDMA Iteration 8 2015-2-4 begin */

    /* Deleted by y00307564 for CDMA Iteration 8 2015-2-4 end */

/* TAF的消息处理 */


    /* 收到模式设置请求 */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PHONE_MODE_SET_REQ,
                      TAF_MMA_ProcTafPhoneModeSetReq_PreProc),

    /* 收到AT的cfun查询请求 */
    /* Added by y00322978 for X project phrase 11,2014-03-27,begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PHONE_MODE_QRY_REQ,
                      TAF_MMA_RcvQryPhoneModeReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYSCFG_QRY_REQ,
                      TAF_MMA_RcvMmaQrySyscfgReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYSCFG_TEST_REQ,
                      TAF_MMA_RcvMmaTestSyscfgReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSNR_QRY_REQ,
                      TAF_MMA_RcvMmaCsnrQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSQ_QRY_REQ,
                      TAF_MMA_RcvMmaCsqQryReq_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSQLVL_QRY_REQ,
                      TAF_MMA_RcvMmaCsqLvlQryReq_PreProc),

    /* Added by y00322978 for X project phrase 11,2014-03-27,end */


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ACCESS_MODE_QRY_REQ,
                      TAF_MMA_RcvAccessModeQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_COPS_QRY_REQ,
                      TAF_MMA_RcvCopsQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_REG_STATE_QRY_REQ,
                      TAF_MMA_RcvRegStateQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_QRY_REQ,
                      TAF_MMA_RcvMmaQryAutoAttachReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_SYSINFO_QRY_REQ,
                      TAF_MMA_RcvSysInfoQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ANTENNA_INFO_QRY_REQ,
                      TAF_MMA_RcvAntennaInfoQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_HOME_PLMN_QRY_REQ,
                      TAF_MMA_RcvApHplmnQryReq_PreProc),

    /* Added by k902809 for Iteration 11, 2015-3-27, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_USER_SRV_STATE_QRY_REQ,
                      TAF_MMA_RcvUserSrvStateQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_POWER_ON_AND_REG_TIME_QRY_REQ,
                      TAF_MMA_RcvApPwrOnAndRegTimeQryReq_PreProc),

    /* Added by k902809 for Iteration 11, Iteration 11 2015-3-27, end */


    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_QRY_REQ,
                      TAF_MMA_RcvMmaQryAutoAttachReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_BATTERY_CAPACITY_QRY_REQ,
                      TAF_MMA_RcvBatteryCapacityQry_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_HAND_SHAKE_QRY_REQ,
                      TAF_MMA_RcvHandShakeQry_PreProc),
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_ACQ_BEST_NETWORK_REQ,
                      TAF_MMA_RcvMmaAcqReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_REG_REQ,
                      TAF_MMA_RcvMmaRegReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_POWER_SAVE_REQ,
                      TAF_MMA_RcvMmaPowerSaveReq_PreProc),

#if (FEATURE_ON == FEATURE_IMS)
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SRV_INFO_NOTIFY,
                      TAF_MMA_RcvTafImsSrvInfoNotify_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_IMS_SWITCH_QRY_REQ,
                      TAF_MMA_RcvTafImsSwitchQryReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_VOICE_DOMAIN_SET_REQ,
                      TAF_MMA_RcvTafVoiceDomainSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_VOICE_DOMAIN_QRY_REQ,
                      TAF_MMA_RcvTafVoiceDomainQryReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_IMS_SWITCH_STATE_IND,
                      TAF_MMA_RcvMsccImsSwitchStateInd_PreProc ),

#endif


    /* Added by y00307564 for CDMA Iteration 8 2015-2-4 begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_SET_REQ,
                      TAF_MMA_RcvMmaPrefPlmnSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_TEST_REQ,
                      TAF_MMA_RcvMmaPrefPlmnTestReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PREF_PLMN_QUERY_REQ,
                      TAF_MMA_RcvMmaPrefPlmnQueryReq_PreProc),
    /* Added by y00307564 for CDMA Iteration 8 2015-2-4 end */

    /* Added by c00318887 for AT&T phaseII, 2015-3-12, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MSG_MMA_EONS_UCS2_REQ,
                      TAF_MMA_RcvAtEonsUcs2Req_PreProc),
    /* Added by c00318887 for AT&T phaseII, 2015-3-12, end */

    /* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-24, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_QUICKSTART_SET_REQ,
                      TAF_MMA_RcvMmaSetCqstReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_QUICKSTART_QRY_REQ,
                      TAF_MMA_RcvMmaQryQuickStartReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CRPN_QRY_REQ,
                      TAF_MMA_RcvMmaQryCrpnReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CMM_SET_REQ,
                      TAF_MMA_RcvMmaSetCmmReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_SET_REQ,
                      TAF_MMA_RcvMmaSetAutoAttachReq_PreProc),

    /* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-24, end */

    /* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-24, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_AUTO_ATTACH_SET_REQ,
                      TAF_MMA_RcvMmaSetAutoAttachReq_PreProc),

    /* Added by y00322978 for CDMA 1X Iteration 11, 2015-3-24, end */

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_ACQ_CNF,
                      TAF_MMA_RcvTiWaitMsccAcqCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_REG_CNF,
                      TAF_MMA_RcvTiWaitMsccRegCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_POWER_SAVE_CNF,
                      TAF_MMA_RcvTiWaitMsccPowerSaveExpired_PreProc),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /* Del by 00322978, 20150316 for CDMA 1x Iteration 9, begin */
    /* Del by 00322978, 20150316 for CDMA 1x Iteration 9, end */


    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_SYSTEM_SERVICE_INFO_IND,
                      TAF_MMA_RcvMscc1xSystemServiceInfoInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_SYNC_SERVICE_AVAIL_IND,
                      TAF_MMA_RcvMsccSyncServiceAvailInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_MO_CALL_START_NTF,
                      TAF_MMA_RcvTafCdmaMoCallStartNtf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_MO_CALL_END_NTF,
                      TAF_MMA_RcvTafCdmaMoCallEndNtf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_MO_CALL_SUCCESS_NTF,
                      TAF_MMA_RcvTafCdmaMoCallSuccessNtf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_CALL_REDIAL_SYSTEM_ACQUIRE_NTF,
                      TAF_MMA_RcvTafCdmaCallRedialSystemAcquireNtf),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_LOCINFO_QRY_REQ,
                      TAF_MMA_RcvAtQueryCLocInfo_PreProc),


    /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_FREQ_LOCK_SET_REQ,
                      TAF_MMA_RcvSetCFreqLock_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMA_FREQ_LOCK_QRY_REQ,
                      TAF_MMA_RcvQueryCFreqLock_PreProc),
    /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-9, begin */

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_QUIT_CALLBACK_SET_REQ,
                      TAF_MMA_RcvQuitCallBackInd_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSIDLIST_SET_REQ,
                      TAF_MMA_RcvSetCSidListReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CSID_SET_REQ,
                      TAF_MMA_RcvSetCSidReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_1X_EMC_CALL_BACK_QRY_REQ,
                      TAF_MMA_RcvQryEmcCallBackMode_PreProc),
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-9, end */

    /* Added by m00312079 for CDMA 1X Iteration 6 2014-12-25 begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMACSQ_SET_REQ,
                      TAF_MMA_ProcCdmaCsqSetReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CDMACSQ_SET_CNF,
                      TAF_MMA_RcvMsccCdmaCsqSetCnf_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CDMACSQ_QRY_REQ,
                      TAF_MMA_RcvCdmaCsqQryReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CDMACSQ_SIGNAL_QUALITY_IND,
                      TAF_MMA_RcvMsccCdmaCsqInd_PreProc),
    /* Added by m00312079 for CDMA 1X Iteration 6 2014-12-25 end */



    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HRPD_SERVICE_STATUS_IND,
                      TAF_MMA_RcvMsccHrpdServiceStatusInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HRPD_OVERHEAD_MSG_IND,
                      TAF_MMA_RcvMsccHrpdOverheadMsgInd_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HRPD_SYS_ACQ_CNF,
                      TAF_MMA_RcvMsccHrpdSysAcqCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_SYSTEM_TIME_IND,
                      TAF_MMA_RcvMscc1xSystemTimeInd_PreProc),



    /* Added by z00316370 for UTS 2015-5-16 begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_1XCHAN_SET_REQ,
                      TAF_MMA_Rcv1xChanSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_1XCHAN_QUERY_REQ,
                      TAF_MMA_RcvQuery1xChanReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CVER_QUERY_REQ,
                      TAF_MMA_RcvQueryCVerReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_GETSTA_QUERY_REQ,
                      TAF_MMA_RcvQueryStateReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CHIGHVER_QUERY_REQ,
                      TAF_MMA_RcvQueryHighVerReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_HANDSET_INFO_QRY_CNF,
                      TAF_MMA_RcvMsccHandsetInfoQryCnf_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_STATE_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccStateQryCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CHVER_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccHVerQryCnfExpired_PreProc),
    /* Added by z00316370 for UTS 2015-5-16 end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-4, begin */
    /*可维可测消息 hrpd info msg from hsd*/

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_MMA_HRPD_SYS_INFO_IND,
                      TAF_MMA_RcvHsmHrpdSysInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_HSM,
                      ID_HSM_MMA_HARDWARE_SYS_INFO_IND,
                      TAF_MMA_RcvHsmHardwareSysInfoInd_PreProc ),

    TAF_ACT_TBL_ITEM( MSP_PID_DIAG_APP_AGENT,
                      ID_OM_NAS_MMA_CDMA_STATUS_INFO_REPORT_REQ,
                      TAF_MMA_RcvOmCdmaStatusInfoReportReq_PreProc ),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_FREQUENCE_OF_QRY_CDMA_SYS_INFO,
                      TAF_MMA_RcvTiCdmaSysInfoReport_PreProc),
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-4, end */

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-9, begin */

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
    ID_MSCC_MMA_1X_SID_IND,
    TAF_MMA_RcvMscc1XSidInd_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
    ID_MSCC_MMA_SET_CSIDLIST_CNF,
    TAF_MMA_RcvMsccSetCSidListCnf ),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
    ID_MSCC_MMA_1X_EMC_CALL_BACK_IND,
    TAF_MMA_RcvMscc1XEmcCallBackNtf_PreProc ),

    TAF_ACT_TBL_ITEM( UEPS_PID_XCC,
    ID_XCC_MMA_1X_CALL_STATE_IND,
    TAF_MMA_RcvXcc1xCallStateInd_PreProc ),
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-9, end */

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_1X_UE_STATUS_IND,
                      TAF_MMA_RcvMsccUeStateInd_PreProc),

#endif

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CFPLMN_SET_REQ,
                      TAF_MMA_RcvCFPlmnSetReq_PreProc),

    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_CFPLMN_QUERY_REQ,
                      TAF_MMA_RcvCFPlmnQueryReq_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CFPLMN_SET_CNF,
                      TAF_MMA_RcvMsccCFPlmnSetCnf_PreProc),

    TAF_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMA_CFPLMN_QUERY_CNF,
                      TAF_MMA_RcvMsccCFPlmnQueryCnf_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CFPLMN_SET_CNF,
                      TAF_MMA_RcvTiWaitMsccCFPlmnSetCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_CFPLMN_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccCFPlmnQueryCnfExpired_PreProc),


    /* Added by y00307564 for CDMA Iteration 8 2015-2-8 begin */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_SET_CNF,
                      TAF_MMA_RcvTiWaitMsccPrefPlmnSetCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_QUERY_CNF,
                      TAF_MMA_RcvTiWaitMsccPrefPlmnQueryCnfExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_MSCC_PREF_CPOL_TEST_CNF,
                      TAF_MMA_RcvTiWaitMsccPrefPlmnTestCnfExpired_PreProc),
    /* Added by y00307564 for CDMA Iteration 8 2015-2-8 end */

    /* Added by c00318887 for AT&T phaseII, 2015-2-15, begin */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_CS_SERVICE_DISCONN,
                      TAF_MMA_RcvCSServiceDisconnExpired_PreProc),

    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_WAIT_READ_SIM_FILES,
                      TAF_MMA_RcvWaitReadSimFilesExpired_PreProc),

    /* Added by c00318887 for AT&T phaseII, 2015-2-15, end */
    /* Added by y00314741 for CDMA Iteration 15, 2015-6-1, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                      ID_TAF_MMA_PS_RAT_TYPE_NTF,
                      TAF_MMA_RcvTafPsRatTypeNtf_PreProc),

    /* Added by y00314741 for CDMA Iteration 15, 2015-6-1, end */

    /* Added by h00313353 for Iteration 13, 2015-4-13, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                       ID_TAF_MMA_DETACH_REQ,
                       TAF_MMA_RcvDetachReq_PreProc),
    /* Added by h00313353 for Iteration 13, 2015-4-13, end */

    /* Modified by l00301449 for Iteration 13, 2015-04-20, begin */
    TAF_ACT_TBL_ITEM( WUEPS_PID_TAF,
                       ID_TAF_MMA_ATTACH_REQ,
                       TAF_MMA_RcvAttachReq_PreProc),

    /* Modified by l00301449 for Iteration 13, 2015-04-20, end */

    /* Added by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    TAF_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS,
                      TAF_MMA_RcvDelayReportServiceStatusExpired_PreProc),
    /* Added by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

};

/* 不进状态机处理的消息 状态表 */
TAF_STA_STRU        g_astTafMmaPreProcessFsmTbl[]   =
{
    TAF_STA_TBL_ITEM( TAF_MMA_MAIN_STA_PREPROC,
                      g_astTafMmaPreProcessActTbl )
};
VOS_UINT32 TAF_MMA_GetPreProcessStaTblSize( VOS_VOID  )
{
    return (sizeof(g_astTafMmaPreProcessFsmTbl)/sizeof(TAF_STA_STRU));
}

/*****************************************************************************
 函 数 名  : TAF_MMA_GetPreFsmDescAddr
 功能描述  : 获取预处理状态机的描述表
 输入参数  : 无
 输出参数  : 无
 返 回 值  : TAF_FSM_DESC_STRU:指向预处理状态机的描述表
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2011年5月9日
    作    者   : zhoujun 40661
    修改内容   : 新生成函数

*****************************************************************************/
TAF_FSM_DESC_STRU * TAF_MMA_GetPreFsmDescAddr(VOS_VOID)
{
    return (&g_stTafMmaPreFsmDesc);
}




/*****************************************************************************
  3 函数实现
*****************************************************************************/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

