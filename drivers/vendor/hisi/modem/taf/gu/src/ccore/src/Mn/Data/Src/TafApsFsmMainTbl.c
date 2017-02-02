
/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "Taf_Aps.h"
#include "TafApsMain.h"
#include "TafApsFsmMainTbl.h"
#include "AtMnInterface.h"
#include "TafApsFsmMain.h"
#include "ExtAppCmInterface.h"
#include "MmcApsInterface.h"
#include "Taf_ApsForRabm.h"
#include "TafApsSndInternalMsg.h"

#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "ApsL4aInterface.h"
#endif

#include "TafMmaInterface.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "taf_aps_ppp_pif.h"
#include "ApsCdsInterface.h"
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */
#include "ehsm_aps_pif.h"
#include "taf_aps_dhcp_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */

#endif


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MAIN_TBL_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* TAF APS状态机数组:LAY1 状态机名称*/
TAF_FSM_DESC_STRU                       g_stTafApsMainFsmDesc;


/* TAF_APS_STA_INACTIVE动作表 */
TAF_ACT_STRU   g_astTafApsInactiveActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_Inactive),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_Inactive),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_Inactive),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_IND,
                     TAF_APS_RcvSmPdpActivateInd_Inactive),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_ACTIVATE_IND,
                     TAF_APS_RcvL4aPdpActivateInd_Inactive),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive),
#endif


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


    /* Added by y00314741 for CDMA Iteration 15, 2015-5-19, begin */
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_ACTIVATE_IND,
                     TAF_APS_RcvEhsmPdnActInd_Inactive),
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-19, end */

#endif

};

/* TAF_APS_STA_ACTIVE动作表 */
TAF_ACT_STRU   g_astTafApsActiveActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_IND,
                     TAF_APS_RcvSmPdpModifyInd_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_Active),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_MODIFY_IND,
                     TAF_APS_RcvL4aPdpModifyInd_Active),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvL4aPdpDeactivateInd_Active),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_SETUP_IND,
                     TAF_APS_RcvL4aPdpSetupInd_Active),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_Active),
#endif

    TAF_ACT_TBL_ITEM(WUEPS_PID_RABM,
                     ID_RABM_APS_SYS_CHG_TO_GPRS_IND,
                     TAF_APS_RcvRabmSysChgToGprs_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_RABM,
                     RABM_APS_LOCAL_PDP_DEACT_REQ_MSG,
                     TAF_APS_RcvRabmLocalPdpDeactivateReq_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_ACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpActivateRsp_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_DEACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpDeactivateRsp_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInternalPdpDeactivateReq_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterServiceStatusChangeInd_Active),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_NTF,
                     TAF_APS_RcvPppDeactInd_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND,
                     TAF_APS_RcvPsCallEnterDormantInd_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_DISC_IND,
                     TAF_APS_RcvXccDiscInd_Active),


    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ,
                     TAF_APS_RcvPsCallInterEpdszidReOrig_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND,
                     TAF_APS_RcvXccUpdateDataCallInfoInd_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_CDS,
                     ID_CDS_APS_CDATA_SERVICE_IND,
                     TAF_APS_RcvCdsServiceInd_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_DISC_IND,
                     TAF_APS_RcvHsmDiscInd_Active),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_ACT_CNF,
                     TAF_APS_RcvPppActCnf_Active),

    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_DEACT_CNF,
                     TAF_APS_RcvPppDeactCnf_Active),

    /* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
    TAF_ACT_TBL_ITEM(MSPS_PID_PPPC,
                     ID_PPP_APS_MODIFY_IND,
                     TAF_APS_RcvPppModifyInd_Active),
    /* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                     TAF_APS_RcvTiPppActCnfExpired_Active),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                     TAF_APS_RcvTiPppDectCnfExpired_Active),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ,
                     TAF_APS_RcvInterEndCdmaCallReq_Active),

    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_PDN_DEACTIVATE_IND,
                     TAF_APS_RcvEHsmPdnDeactInd_Active),

    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND,
                     TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF,
                     TAF_APS_RcvTiDhcpActIpv4Expired_Active),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF,
                     TAF_APS_RcvTiDhcpActIpv6Expired_Active),

    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

#endif
};

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/* TAF_APS_STA_DORMANTE动作表 */
TAF_ACT_STRU   g_astTafApsDormantActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvPsCallOrigReq_Dormant),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvPsPppDialOrigReq_Dormant),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvPsCallEndReq_Dormant),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_INCOMING_CALL_IND,
                     TAF_APS_RcvXccIncomingCallInd_Dormant),

    TAF_ACT_TBL_ITEM(UEPS_PID_CDS,
                     ID_CDS_APS_CDATA_SERVICE_IND,
                     TAF_APS_RcvCdsServiceInd_Dormant),

    /* Modified by y00314741 for CDMA Iteration 11, 2015-4-9, begin */
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant),
    /* Modified by y00314741 for CDMA Iteration 11, 2015-4-9, end */

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ,
                     TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_CDATA_DORMANT,
                     TAF_APS_RcvTiDormantTimerExpired_Dormant),

    TAF_ACT_TBL_ITEM(UEPS_PID_XCC,
                     ID_XCC_APS_DATA_CALL_RESUME_IND,
                     TAF_APS_RcvXccResumeInd_Dormant),

    /* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
    TAF_ACT_TBL_ITEM(UEPS_PID_HSM,
                     ID_HSM_APS_CONNECT_IND,
                     TAF_APS_RcvHsmCalConnectInd_Dormant),

    /* Added by y00314741 for CDMA Iteration 11, 2015-3-30, begin */
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ,
                     TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ,
                     TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant),
    /* Added by y00314741 for CDMA Iteration 11, 2015-3-30, end */

    /* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */

    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND,
                     TAF_APS_RcvPsInterEnd1xService_Dormant),

    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */
};
#endif

TAF_STA_STRU g_astTafApsMainFsmStaTbl[] =
{
    /*****************定义TAF_APS_STA_INACTIVE状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_STA_INACTIVE,
                      g_astTafApsInactiveActTbl ),

    /*****************定义TAF_APS_STA_ACTIVE的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_STA_ACTIVE,
                      g_astTafApsActiveActTbl ),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

    /*****************定义TAF_APS_STA_ACTIVE的状态转移表**********************/
    TAF_STA_TBL_ITEM( TAF_APS_STA_DORMANT,
                      g_astTafApsDormantActTbl ),
#endif

};


/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_UINT32 TAF_APS_GetMainFsmStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsMainFsmStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_APS_GetMainFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsMainFsmDesc);
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

