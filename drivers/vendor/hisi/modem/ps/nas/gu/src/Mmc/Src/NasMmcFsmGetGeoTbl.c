
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasFsm.h"
#include "UsimPsApi.h"
#include "Nasrrcinterface.h"
#include "NasMmcFsmGetGeo.h"
#include "NasMmcFsmGetGeoTbl.h"
#include "NasMmcTimerMgmt.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndInternalMsg.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_GET_GEO_TBL_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* NAS MMC״̬������: GetGeo���״̬������ */
NAS_FSM_DESC_STRU                       g_stNasMmcGetGeoFsmDesc;


/* NAS_MMC_GET_GEO_STA_INIT������ */
NAS_ACT_STRU   g_astNasGetGeoInitActTbl[]                  =
{
    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_GET_GEO_REQ,
                      NAS_MMC_RcvMsccGetGeoReq_GetGeo_Init)

};

/* NAS_MMC_GET_GEO_STA_WAIT_CSS_BAND_SCAN_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitCssBandScanCnfActTbl[]     =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssBandScanCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssBandScanCnf),

    NAS_ACT_TBL_ITEM( PS_PID_CSS,
                      ID_CSS_MULTI_BAND_SCAN_CNF,
                      NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssBandScanCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF,
                      NAS_MMC_RcvTiWaitCssBandScanCnfExp_GetGeo_WaitCssBandScanCnf)
};

/* NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitCssStopBandScanCnfActTbl[]     =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssStopBandScanCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssStopBandScanCnf),

    NAS_ACT_TBL_ITEM( PS_PID_CSS,
                      ID_CSS_STOP_BAND_SCAN_CNF,
                      NAS_MMC_RcvCssStopBandScanCnf_GetGeo_WaitCssStopBandScanCnf),

    NAS_ACT_TBL_ITEM( PS_PID_CSS,
                      ID_CSS_MULTI_BAND_SCAN_CNF,
                      NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssStopBandScanCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF,
                      NAS_MMC_RcvTiWaitCssStopBandScanCnfExp_GetGeo_WaitCssStopBandScanCnf)
};

/* NAS_MMC_GET_GEO_STA_WAIT_GAS_PLMN_SEARCH_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitGasPlmnSearchCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitGasGetGeoCnfExp_GetGeo_WaitGasPlmnSearchCnf)
};


/* NAS_MMC_GET_GEO_STA_WAIT_WAS_PLMN_SEARCH_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitWasPlmnSearchCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitWasGetGeoExp_GetGeo_WaitWasPlmnSearchCnf),

};

/* NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitGasStopPlmnSearchCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitGasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitGasStopGetGeoExp_GetGeo_WaitGasStopPlmnSearchCnf),

};

/* NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_GET_GEO_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitWasStopPlmnSearchCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_STOP_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitWasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitWasStopGetGeoExp_GetGeo_WaitWasStopPlmnSearchCnf),

};

/* NAS_MMC_GET_GEO_STA_WAIT_GAS_SUSPEND_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitGasSuspendCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_GAS,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitGasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitGasSuspendCnfExp_GetGeo_WaitGasSuspendCnf),

};

/* NAS_MMC_GET_GEO_STA_WAIT_WAS_SUSPEND_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitWasSuspendCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( WUEPS_PID_WRR,
                      RRMM_SUSPEND_CNF,
                      NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitWasSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitWasSuspendCnfExp_GetGeo_WaitWasSuspendCnf),

};

#if (FEATURE_ON == FEATURE_LTE)
/* NAS_MMC_GET_GEO_STA_WAIT_LMM_PLMN_SEARCH_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitLmmPlmnSearchCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                      NAS_MMC_RcvTiWaitLmmGetGeoCnfExp_GetGeo_WaitLmmPlmnSearchCnf),

};

/* NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitLmmStopPlmnSearchCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_STOP_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmStopPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_PLMN_SRCH_CNF,
                      NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                      NAS_MMC_RcvTiWaitLmmStopGetGeoCnfExp_GetGeo_WaitLmmStopPlmnSearchCnf),

};

/* NAS_MMC_GET_GEO_STA_WAIT_LMM_SUSPEND_CNF������ */
NAS_ACT_STRU   g_astNasGetGeoWaitLmmSuspendCnfActTbl[]       =
{
    NAS_ACT_TBL_ITEM( WUEPS_PID_MMC,
                      MMCMMC_ABORT_FSM_REQ,
                      NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( UEPS_PID_MSCC,
                      ID_MSCC_MMC_STOP_GET_GEO_REQ,
                      NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( PS_PID_MM,
                      ID_LMM_MMC_SUSPEND_CNF,
                      NAS_MMC_RcvLmmSuspendCnf_GetGeo_WaitLmmSuspendCnf),

    NAS_ACT_TBL_ITEM( VOS_PID_TIMER,
                      TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                      NAS_MMC_RcvTiWaitLmmSuspendCnfExp_GetGeo_WaitLmmSuspendCnf),

};
#endif



/* Э��ջGET_GEO��L2״̬�� */
NAS_STA_STRU g_astNasMmcGetGeoStaTbl[] =
{
    /*****************����GET_GEO״̬��״̬ת�Ʊ�**********************/
    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_INIT,
                      g_astNasGetGeoInitActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_CSS_BAND_SCAN_CNF,
                      g_astNasGetGeoWaitCssBandScanCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF,
                      g_astNasGetGeoWaitCssStopBandScanCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_GAS_PLMN_SEARCH_CNF,
                      g_astNasGetGeoWaitGasPlmnSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_WAS_PLMN_SEARCH_CNF,
                      g_astNasGetGeoWaitWasPlmnSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF,
                      g_astNasGetGeoWaitGasStopPlmnSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF,
                      g_astNasGetGeoWaitWasStopPlmnSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_GAS_SUSPEND_CNF,
                      g_astNasGetGeoWaitGasSuspendCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_WAS_SUSPEND_CNF,
                      g_astNasGetGeoWaitWasSuspendCnfActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_LMM_PLMN_SEARCH_CNF,
                      g_astNasGetGeoWaitLmmPlmnSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF,
                      g_astNasGetGeoWaitLmmStopPlmnSearchCnfActTbl ),

    NAS_STA_TBL_ITEM( NAS_MMC_GET_GEO_STA_WAIT_LMM_SUSPEND_CNF,
                      g_astNasGetGeoWaitLmmSuspendCnfActTbl ),
#endif
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32 NAS_MMC_GetGeoStaTblSize(VOS_VOID)
{
    return (sizeof(g_astNasMmcGetGeoStaTbl)/sizeof(NAS_STA_STRU));
}



NAS_FSM_DESC_STRU * NAS_MMC_GetGeoFsmDescAddr(VOS_VOID)
{
    return (&g_stNasMmcGetGeoFsmDesc);
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

