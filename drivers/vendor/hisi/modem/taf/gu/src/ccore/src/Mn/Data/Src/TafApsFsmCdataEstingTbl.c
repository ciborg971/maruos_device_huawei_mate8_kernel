

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmCdataEsting.h"
#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafMmaInterface.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "taf_aps_ppp_pif.h"
#include "ApsCdsInterface.h"
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */
#include "ehsm_aps_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */

#endif


#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_ESTING_TBL_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:CDATA ESTIVATING 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsCdataEstingFsmDesc;


/******************************************************************************
   5 函数实现
******************************************************************************/

/* TAF_APS_CDATA_ESTING_SUBSTA_INIT动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaInitTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvPsCallOrigReq_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_INCOMING_CALL_IND,
                     TAF_APS_RcvXccIncomingCallInd_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(UEPS_PID_CDS,
                     ID_CDS_APS_CDATA_SERVICE_IND,
                     TAF_APS_RcvCdsServiceInd_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ,
                     TAF_APS_RcvPsInterEpdszidReOrigReq_CdataEsting_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvPppDialOrigReq_CdataEsting_Init),

    /* Added by y00314741 for CDMA Iteration 11, 2015-3-25, begin */
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ,
                     TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init),
    /* Added by y00314741 for CDMA Iteration 11, 2015-3-25, end */

    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND,
                     TAF_APS_RcvPsInterDormantEnd1xSvc_CdataEsting_Init),
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccOrigCallCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_ORIG_DATA_CALL_CNF,
                     TAF_APS_RcvXccOrigDataCallCnf_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccOrigCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccOrigCallCnf),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccSoConnectedActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_SERVICE_CONNECT_IND,
                     TAF_APS_RcvXccDataServiceConnInd_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccSoConnected),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccSoConnected),

};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccAnsCallCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_ANSWER_DATA_CALL_CNF,
                     TAF_APS_RcvXccAnsCallCnf_CdataEsting_WaitXccAnsCallCnf),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccAnsCallCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccAnsCallCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccAnsCallCnf),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitXccCallConnectedIndActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_CONN_IND,
                     TAF_APS_RcvXccCallConnectedInd_CdataEsting_WaitXccCallConnectedInd),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccCallConnectedInd),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccCallConnectedInd),
};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitIntervalRedialActTbl[]   =
{
    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                     TAF_APS_RcvTiRedialIntervalExpired_CdataEsting_WaitRedial),


    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitRedial),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_WaitRedial),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_INCOMING_CALL_IND,
                     TAF_APS_RcvXccIncomingCallInd_CdataEsting_WaitRedial),


};

/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitHsmActCnfActTbl[]   =
{

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_ORIG_CNF,
                     TAF_APS_RcvHsmOrigCnf_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitHsmOrigCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvInterEndCdmaCallReq_WaitHsmOrigCnf),


};

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/* TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubStaWaitEhsmPdnActCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_ACTIVATE_CNF,
                     TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf),

};

/* TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND动作表 */
TAF_ACT_STRU   g_astTafApsCdataEstingSubstaSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND,
                     TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING,
                     TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_Suspend),

};

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

TAF_STA_STRU g_astTafApsCdataEstingStaTbl[] =
{
    /*****************定义TAF_APS_MS_ACTIVATING_SUBSTA_INIT状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_INIT,
                      g_astTafApsCdataEstingSubStaInitTbl ),

    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF,
                      g_astTafApsCdataEstingSubStaWaitXccOrigCallCnfActTbl ),

    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED,
                      g_astTafApsCdataEstingSubStaWaitXccSoConnectedActTbl ),

    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF,
                      g_astTafApsCdataEstingSubStaWaitXccAnsCallCnfActTbl ),

    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND,
                      g_astTafApsCdataEstingSubStaWaitXccCallConnectedIndActTbl ),

    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL,
                      g_astTafApsCdataEstingSubStaWaitIntervalRedialActTbl ),

    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF,
                      g_astTafApsCdataEstingSubStaWaitHsmActCnfActTbl ),
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF,
                      g_astTafApsCdataEstingSubStaWaitEhsmPdnActCnfActTbl ),

    /*****************定义TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND,
                      g_astTafApsCdataEstingSubstaSuspendActTbl ),
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

};


VOS_UINT32 TAF_APS_GetCdataEstingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsCdataEstingStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_APS_GetCdataEstingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsCdataEstingFsmDesc);
}


#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



