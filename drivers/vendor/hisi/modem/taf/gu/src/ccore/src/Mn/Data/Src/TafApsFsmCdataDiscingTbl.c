

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafApsFsmCdataDiscingTbl.h"
#include  "taf_aps_ppp_pif.h"
#include  "TafApsFsmCdataDiscing.h"
#include  "TafApsApi.h"
#include  "TafApsTimerMgmt.h"
#include  "xcc_aps_pif.h"
#include  "TafApsSndInternalMsg.h"
#include  "hsm_aps_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */
#include  "ehsm_aps_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_DISCING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/* TAF APS״̬������:CDATA DISCING ״̬������*/
TAF_FSM_DESC_STRU                       g_stTafApsCdataDiscingFsmDesc;

/* TAF_APS_CDATA_DISCING_SUBSTA_INIT������ */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaInitTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND,
                     TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactNtf_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_CNF,
                     TAF_APS_RcvPppDeactCnf_CdataDiscing_Init),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_Init),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DEACT_CNF ������ */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitHsmDecatCnfTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_DISC_CNF,
                     TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_DISC_IND,
                     TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitHsmDiscCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF ������ */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitXccHangUpDataCallCnfTbl[]   =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_HANGUP_DATA_CALL_CNF,
                     TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ,
                     TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf),
};

/* Added by y00314741 for CDMA Iteration 15, 2015-6-6, begin */
/* TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF ������ */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaWaitEhsmPdnDeactCnfTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_DEACTIVATE_CNF,
                     TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_DEACTIVATE_IND,
                     TAF_APS_RcvEhsmPdnDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf),

};

/* TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND ������ */
TAF_ACT_STRU   g_astTafApsCdataDiscingSubStaSuspendTbl[]   =
{

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DISCING,
                     TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_Suspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_Suspend),

};

/* Added by y00314741 for CDMA Iteration 15, 2015-6-6, end */

TAF_STA_STRU g_astTafApsCdataDiscingStaTbl[] =
{

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_INIT,
                      g_astTafApsCdataDiscingSubStaInitTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF,
                      g_astTafApsCdataDiscingSubStaWaitHsmDecatCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF,
                      g_astTafApsCdataDiscingSubStaWaitXccHangUpDataCallCnfTbl ),

    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF,
                      g_astTafApsCdataDiscingSubStaWaitEhsmPdnDeactCnfTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND,
                      g_astTafApsCdataDiscingSubStaSuspendTbl )
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 TAF_APS_GetCdataDiscingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsCdataDiscingStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_APS_GetCdataDiscingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsCdataDiscingFsmDesc);
}







#endif



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
