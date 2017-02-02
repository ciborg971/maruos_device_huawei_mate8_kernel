

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafApsCtx.h"
#include "TafApsGetPdpIdList.h"
#include "TafLog.h"
#include "TafApsTimerMgmt.h"
#include "TafApsDsFlowStats.h"
#include "PsCommonDef.h"
#include "AtMnInterface.h"
#include "ExtAppCmInterface.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsApi.h"
#include "ApsL4aInterface.h"
#include "Taf_ApsForRabm.h"
#include "Taf_ApsForSndcp.h"
#include "MmcApsInterface.h"
#include "Taf_Aps.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsComFunc.h"
#include "TafApsSndInternalMsg.h"
#include "xcc_aps_pif.h"
#include "ApsCdsInterface.h"
#include "taf_aps_ppp_pif.h"
#include "MnApsComm.h"
#include "TafMmaInterface.h"
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
#include "hsm_aps_pif.h"
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */
#include "ehsm_aps_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_GET_PDPID_LIST_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

TAF_APS_GET_FSM_PDPID_LIST_STRU gastApsGetPdpIdList[] =
{
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ), TAF_APS_GetPdpIdListWithAtSetPdpContextStateReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_MODIFY_REQ),           TAF_APS_GetPdpIdListWithAtCallModifyReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ),             TAF_APS_GetPdpIdListWithAtCallOrigReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ),         TAF_APS_GetPdpIdListWithAtPppDialOrigReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ),              TAF_APS_GetPdpIdListWithAtCallEndReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ANSWER_REQ),           TAF_APS_GetPdpIdListWithAtCallAnswerReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_HANGUP_REQ),           TAF_APS_GetPdpIdListWithAtCallHangupReq},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_CNF),               TAF_APS_GetPdpIdListWithSmPdpActCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_REJ),               TAF_APS_GetPdpIdListWithSmPdpActRej},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_IND),               TAF_APS_GetPdpIdListWithSmPdpActInd},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_CNF),                 TAF_APS_GetPdpIdListWithSmPdpModifyCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_IND),                 TAF_APS_GetPdpIdListWithSmPdpModifyInd},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_MODIFY_REJ),                 TAF_APS_GetPdpIdListWithSmPdpModifyRej},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_DEACTIVATE_IND),             TAF_APS_GetPdpIdListWithSmPdpDeactivInd},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_DEACTIVATE_CNF),             TAF_APS_GetPdpIdListWithSmPdpDeactivCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_SEC_CNF),           TAF_APS_GetPdpIdListWithSmPdpActSecCnf},
    {TAF_BuildEventType(WUEPS_PID_SM, ID_SMREG_PDP_ACTIVATE_SEC_REJ),           TAF_APS_GetPdpIdListWithSmPdpActSecRej},
#if (FEATURE_ON == FEATURE_LTE)
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_ACTIVATE_CNF),           TAF_APS_GetPdpIdListWithL4aPdpActivateCnf},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_ACTIVATE_REJ),           TAF_APS_GetPdpIdListWithL4aPdpActivateRej},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_ACTIVATE_IND),           TAF_APS_GetPdpIdListWithL4aPdpActInd},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_MODIFY_CNF),             TAF_APS_GetPdpIdListWithL4aPdpModifyCnf},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_MODIFY_REJ),             TAF_APS_GetPdpIdListWithL4aPdpModifyRej},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_MODIFY_IND),             TAF_APS_GetPdpIdListWithL4aPdpModifyInd},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_DEACTIVATE_CNF),         TAF_APS_GetPdpIdListWithL4aDeactivateCnf},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_DEACTIVATE_REJ),         TAF_APS_GetPdpIdListWithL4aDeactivateRej},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_DEACTIVATE_IND),         TAF_APS_GetPdpIdListWithL4aDeactivateInd},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PDP_SETUP_IND),              TAF_APS_GetPdpIdListWithL4aSetupInd},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_SET_NDISCONN_CNF),           TAF_APS_GetPdpIdListWithL4aSetNdisConnCnf},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_SET_CGANS_CNF),              TAF_APS_GetPdpIdListWithL4aSetCgansCnf},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PPP_DIAL_CNF),               TAF_APS_GetPdpIdListWithL4aPppDialCnf},
    {TAF_BuildEventType(MSP_L4_L4A_PID, ID_L4A_APS_PS_CALL_END_CNF),            TAF_APS_GetPdpIdListWithL4aPsCallEndCnf},
    {TAF_BuildEventType(PS_PID_ESM,     ID_ESM_SM_EPS_BEARER_INFO_IND),         TAF_APS_GetPdpIdListWithEsmSmEpsBearerInfoInd},
#endif
    {TAF_BuildEventType(WUEPS_PID_RABM, ID_RABM_APS_SYS_CHG_TO_GPRS_IND),       TAF_APS_GetPdpIdListWithRabmApsSysChgToGprsInd},
    {TAF_BuildEventType(WUEPS_PID_RABM, RABM_APS_LOCAL_PDP_DEACT_REQ_MSG),      TAF_APS_GetPdpIdListWithRabmApsLocalPdpDeactReqMsg},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_ACT_RSP_MSG_TYPE),                  TAF_APS_GetPdpIdListWithSndcpActRspMsgType},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_MDF_RSP_MSG_TYPE),                  TAF_APS_GetPdpIdListWithSndcpMdfRspMsgType},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_DEACT_RSP_MSG_TYPE),                TAF_APS_GetPdpIdListWithSndcpDeactRspMsgType},
    {TAF_BuildEventType(UEPS_PID_SN, APS_SN_STATUS_REQ_MSG_TYPE),               TAF_APS_GetPdpIdListWithSndcpStatusReqMsgType},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ), TAF_APS_GetPdpIdListWithApsInternalPdpDeactivateReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND),    TAF_APS_GetPdpIdListWithApsLocalPdpDeactivateInd},

    /* Modified by y00314741 for CDMA Iteration 15, 2015-5-21, begin */
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_ATTACH_BEARER_ACTIVATE_IND), TAF_APS_GetPdpIdListWithAttachBearerActivateInd},
    /* Modified by y00314741 for CDMA Iteration 15, 2015-5-21, end */

    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND), TAF_APS_GetPdpIdListWithServiceStatusChangeReq},

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_ORIG_DATA_CALL_CNF),           TAF_APS_GetPdpIdListWithXccOrigDataCnf},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_HANGUP_DATA_CALL_CNF),         TAF_APS_GetPdpIdListWithXccHangUpDataCnf},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_CALL_DISC_IND),           TAF_APS_GetPdpIdListWithXccDataCallDiscInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND),            TAF_APS_GetPdpIdListWithXccIncomingCallInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_CALL_CONN_IND),           TAF_APS_GetPdpIdListWithXccDataCallConnInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_SERVICE_CONNECT_IND),     TAF_APS_GetPdpIdListWithXccDataSrvConnInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_ANSWER_DATA_CALL_CNF),         TAF_APS_GetPdpIdListWithXccAnswerDataCnf},
    {TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND),            TAF_APS_GetPdpIdListWithCdsCdataServiceInd},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND),   TAF_APS_GetPdpIdListWithPsCallEnterDormantInd},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ),  TAF_APS_GetPdpIdListWithApsInternEndCdmaCallReq},
    {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_ACT_CNF),                     TAF_APS_GetPdpIdListWithPppActCnf},
    {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_DEACT_CNF),                   TAF_APS_GetPdpIdListWithPppDeactCnf},
    {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_DEACT_NTF),                TAF_APS_GetPdpIdListWithPppDeactNtf},

    /* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
     {TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_MODIFY_IND),                 TAF_APS_GetPdpIdListWithPppModifyInd},
    /* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-5-12, begin */

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-5-12, end */

    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ), TAF_APS_GetPdpIdListWithEpdszidReOrigReq},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_DATA_CALL_RESUME_IND),         TAF_APS_GetPdpIdListWithXccDataCallResumeInd},
    {TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_UPDATE_DATA_CALL_INFO_IND),    TAF_APS_GetPdpIdListWithXccUpdateDataCallInfoInd},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_ORIG_CNF),    TAF_APS_GetPdpIdListWithHsmOrigCnf},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_DISC_CNF),    TAF_APS_GetPdpIdListWithHsmDiscCnf},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_DISC_IND),    TAF_APS_GetPdpIdListWithHsmDiscInd},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_CONNECT_IND), TAF_APS_GetPdpIdListWithHsmConnectInd},
    {TAF_BuildEventType(UEPS_PID_HSM, ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF),    TAF_APS_GetPdpIdListWithHsm1XToHrpdHandOffCnf},
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-7, begin */
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ),    TAF_APS_GetPdpIdListWith1XToHrpdHandOffReq},
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ),    TAF_APS_GetPdpIdListWithHrpdTo1XHandOffReq},
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-7, end */
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_ACTIVATE_CNF),    TAF_APS_GetPdpIdListWithEhsmPdnActCnf},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_DEACTIVATE_CNF),  TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_DEACTIVATE_IND),  TAF_APS_GetPdpIdListWithEhsmPdnDeactInd},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_PDN_ACTIVATE_IND),    TAF_APS_GetPdpIdListWithEhsmPdnActInd},
    {TAF_BuildEventType(UEPS_PID_EHSM, ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND),    TAF_APS_GetPdpIdListWithEhsmLteHandoverToEhrpdInd},
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    {TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND),   TAF_APS_GetPdpIdListWithEnd1xServiceInDormantInd},
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

    /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */

    /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

#endif
};


/*****************************************************************************
  3 函数实现
*****************************************************************************/
/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, begin */

/* Deleted by y00314741 for CDMA Iteration 11, 2015-4-15, end */


VOS_VOID TAF_APS_GetPdpIdListWithAtSetPdpContextStateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;

    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* 设置激活标记 */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /* 当前先不支持一次性激活多个PDP的场景，一次激活一个 */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpStateReq->stCidListStateInfo.aucCid);

    /* 预处理已经处理，不会获取不到PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(ucCidValue);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithAtCallEndReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* 当前先不支持一次性去激活多个PDP的场景，一次去激活一个 */
    pstAppMsg     = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 预处理已经处理，不会获取不到PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstCallEndReq->ucCid);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithAtCallAnswerReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    if (VOS_NULL_PTR == pstNwActFsm)
    {
        pstPdpIdList->ucPdpNum = 0;
    }
    else
    {
        pstPdpIdList->aucPdpId[0] = pstNwActFsm->ucPdpId;
        pstPdpIdList->ucPdpNum = 1;
    }
}


VOS_VOID TAF_APS_GetPdpIdListWithAtCallHangupReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    if (VOS_NULL_PTR == pstNwActFsm)
    {
        pstPdpIdList->ucPdpNum = 0;
    }
    else
    {
        pstPdpIdList->aucPdpId[0] = pstNwActFsm->ucPdpId;
        pstPdpIdList->ucPdpNum = 1;
    }
}


VOS_VOID TAF_APS_GetPdpIdListWithAtCallModifyReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;

    ulBearerActivateFlg = VOS_FALSE;
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    /* 当前先不支持一次性Moidify多个PDP的场景，一次Moidfy一个 */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstCallModifyReq->stCidListInfo.aucCid);

    /* 预处理已经处理，不会获取不到PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(ucCidValue);
    pstPdpIdList->ucPdpNum = 1;

}


VOS_VOID TAF_APS_GetPdpIdListWithAtCallOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* 当前先不支持一次性激活多个PDP的场景，一次激活一个 */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 预处理已经处理，不会获取不到PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstCallOrigReq->stDialParaInfo.ucCid);
    pstPdpIdList->ucPdpNum = 1;

}


VOS_VOID TAF_APS_GetPdpIdListWithAtPppDialOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* 当前先不支持一次性激活多个PDP的场景，一次激活一个 */
    pstAppMsg         = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 预处理已经处理，不会获取不到PdpId */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);
    pstPdpIdList->ucPdpNum = 1;

}


VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum    = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;
}
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_IND_STRU *)pstMsg;


    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpModifyCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_MODIFY_CNF_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithSmPdpModifyInd
 功能描述  : 获取当前SM 的Modify IND消息所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2012年1月4日
    作    者   : zhangyizhan 60575
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID  TAF_APS_GetPdpIdListWithSmPdpModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_MODIFY_IND_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpModifyRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;


}
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpDeactivInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmMsg;
    VOS_UINT8                           i;
    VOS_UINT8                           ucTearDownInd;
    VOS_UINT32                          ulOP_TearDownInd;

    pstSmMsg         = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    ucTearDownInd    = pstSmMsg->ucTearDownInd;
    ulOP_TearDownInd = pstSmMsg->bitOpTearDownInd;

    /* Deactive Ind消息中如果带有TearDown,
       该PDP下挂接的其他专有PDP也都需要本地去激活掉 */
    if ((VOS_TRUE == ulOP_TearDownInd)
     && (TAF_PDP_TEAR_DOWN == ucTearDownInd))
    {
        if (APS_PDP_ACT_PRI == g_PdpEntity[pstSmMsg->ucConnectId].ActType)
        {
            /* pstSmMsg->ucCr即为对应的Pdp Id */
            pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
            pstPdpIdList->ucPdpNum    = 1;

            TAF_APS_GetSpecPdpLinkedPdpInfo(pstPdpIdList, g_PdpEntity[pstSmMsg->ucConnectId].ucNsapi);
        }
        else
        {
            /* 先通过需要去激活SecPDP对应的LinkedNsapi(主PDP)，查找到所有挂接在
               主PDP下得从PDP ID，再找到主PDP对应的PDP ID */
            TAF_APS_GetSpecPdpLinkedPdpInfo(pstPdpIdList, g_PdpEntity[pstSmMsg->ucConnectId].ucLinkedNsapi);

            for (i = 0; i < TAF_APS_MAX_PDPID; i++)
            {
                if (g_PdpEntity[pstSmMsg->ucConnectId].ucLinkedNsapi == g_PdpEntity[i].ucNsapi)
                {
                    pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = i;
                    pstPdpIdList->ucPdpNum++;
                }
            }
        }
    }
    /* 不带TearDown时, 如果是PriPDP需要去激活该主PDP下挂接的SecPdp
       否则单独去激活该PDP */
    else
    {
        if (APS_PDP_ACT_PRI == g_PdpEntity[pstSmMsg->ucConnectId].ActType)
        {
            /* pstSmMsg->ucCr即为对应的Pdp Id */
            pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
            pstPdpIdList->ucPdpNum = 1;

            TAF_APS_GetSpecPdpLinkedPdpInfo(pstPdpIdList, g_PdpEntity[pstSmMsg->ucConnectId].ucNsapi);
        }
        else
        {
            /* pstSmMsg->ucCr即为对应的Pdp Id */
            pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
            pstPdpIdList->ucPdpNum = 1;
        }
    }

}


VOS_VOID TAF_APS_GetPdpIdListWithSmPdpDeactivCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_DEACTIVATE_CNF_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActSecCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSmPdpActSecRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU*)pstMsg;

    /* pstSmMsg->ucCr即为对应的Pdp Id */
    pstPdpIdList->aucPdpId[0] = pstSmMsg->ucConnectId;
    pstPdpIdList->ucPdpNum = 1;

}

#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID TAF_APS_GetPdpIdListWithL4aPdpActivateCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_ACTIVATE_CNF_STRU      *pstL4aActCnf;

    pstL4aActCnf = (APS_L4A_PDP_ACTIVATE_CNF_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aActCnf->ucCid);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithL4aPdpActivateRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_ACTIVATE_REJ_STRU      *pstL4aActRej;

    pstL4aActRej = (APS_L4A_PDP_ACTIVATE_REJ_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aActRej->ucCid);
    pstPdpIdList->ucPdpNum = 1;
}
VOS_VOID TAF_APS_GetPdpIdListWithL4aPdpActInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_ACTIVATE_IND_STRU      *pstL4aActInd;

    pstL4aActInd = (APS_L4A_PDP_ACTIVATE_IND_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aActInd->ucCid);
    pstPdpIdList->ucPdpNum = 1;
}
VOS_VOID TAF_APS_GetPdpIdListWithL4aPdpModifyCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_MODIFY_CNF_STRU        *pstL4aModifyCnf;

    pstL4aModifyCnf = (APS_L4A_PDP_MODIFY_CNF_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aModifyCnf->ucCid);
    pstPdpIdList->ucPdpNum = 1;
}
VOS_VOID TAF_APS_GetPdpIdListWithL4aPdpModifyRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_MODIFY_REJ_STRU        *pstL4aModifyRej;

    pstL4aModifyRej = (APS_L4A_PDP_MODIFY_REJ_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aModifyRej->ucCid);
    pstPdpIdList->ucPdpNum = 1;
}
VOS_VOID TAF_APS_GetPdpIdListWithL4aPdpModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_MODIFY_IND_STRU        *pstL4aModifyInd;

    pstL4aModifyInd = (APS_L4A_PDP_MODIFY_IND_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aModifyInd->ucCid);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithL4aDeactivateCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_DEACTIVATE_CNF_STRU    *pstL4aDeactivateCnf;

    pstL4aDeactivateCnf = (APS_L4A_PDP_DEACTIVATE_CNF_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aDeactivateCnf->ucCid);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithL4aDeactivateRej(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_DEACTIVATE_REJ_STRU    *pstL4aDeactivateRej;

    pstL4aDeactivateRej = (APS_L4A_PDP_DEACTIVATE_REJ_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aDeactivateRej->ucCid);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithL4aDeactivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_DEACTIVATE_IND_STRU    *pstL4aDeactivateInd;

    pstL4aDeactivateInd = (APS_L4A_PDP_DEACTIVATE_IND_STRU*)pstMsg;

    if (VOS_TRUE == pstL4aDeactivateInd->bitOpLinkCid)
    {
        /* 从消息中所带的Cid来查找对应的PDP ID */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid_InL4aDeactivateInd(pstL4aDeactivateInd->ucCid);
        pstPdpIdList->ucPdpNum = 1;
    }
    else
    {
        /* 从消息中所带的EpsbId来查找对应的PDP ID */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByEpsbId_InL4aDeactivateInd(pstL4aDeactivateInd->ulEpsbId);
        pstPdpIdList->ucPdpNum = 1;
    }
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithL4aSetupInd
 功能描述  : 获取当前L4A 上报的PDP SETUP IND所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : w00316404
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithL4aSetupInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PDP_SETUP_IND_STRU         *pstPdpSetupInd;

    pstPdpSetupInd = (APS_L4A_PDP_SETUP_IND_STRU*)pstMsg;

    if (VOS_TRUE == pstPdpSetupInd->bitOpLinkCid)
    {
        /* 从消息中所带的Cid来查找对应的PDP ID */
        pstPdpIdList->aucPdpId[0]   = TAF_APS_GetPdpIdByCid(pstPdpSetupInd->ucCid);
        pstPdpIdList->ucPdpNum      = 1;
    }
    else
    {
        /* 从消息中所带的RabId来查找对应的PDP ID */
        pstPdpIdList->aucPdpId[0]   = TAF_APS_GetPdpIdByEpsbId(pstPdpSetupInd->ulRabId);
        pstPdpIdList->ucPdpNum      = 1;
    }

}


VOS_VOID TAF_APS_GetPdpIdListWithL4aSetNdisConnCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_SET_NDISCONN_CNF_STRU      *pstL4aNdisConnCnf;

    pstL4aNdisConnCnf = (APS_L4A_SET_NDISCONN_CNF_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstL4aNdisConnCnf->ucCid);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithEsmSmEpsBearerInfoInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    VOS_UINT8                           ucCid;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;

    /* 前面预处理已经处理，这里不可能出现CID是不可能是异常的 */
    ucCid = TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid);

    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        /* 从消息中所带的Cid来查找对应的PDP ID，预处理中已经检查, ucCid一定有值 */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid_InEpsBearerIndOptActivate(ucCid);
        pstPdpIdList->ucPdpNum = 1;
    }
    else
    {
        /* 从消息中所带的EpsbId来查找对应的PDP ID */
        pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByEpsbId(pstBearerInfo->ulEpsbId);
        pstPdpIdList->ucPdpNum = 1;
    }
}


VOS_VOID TAF_APS_GetPdpIdListWithL4aSetCgansCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithL4aPppDialCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PPP_DIAL_CNF_STRU          *pstPppDialCnf;

    /* 初始化, 获取消息内容 */
    pstPppDialCnf = (APS_L4A_PPP_DIAL_CNF_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstPppDialCnf->ucCid);
    pstPdpIdList->ucPdpNum = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithL4aPsCallEndCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_L4A_PS_CALL_END_CNF_STRU       *pstPsCallEndCnf;

    /* 初始化, 获取消息内容 */
    pstPsCallEndCnf = (APS_L4A_PS_CALL_END_CNF_STRU*)pstMsg;

    /* 从消息中 中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstPsCallEndCnf->ucCid);
    pstPdpIdList->ucPdpNum = 1;
}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-21, begin */
#endif
/* Added by y00314741 for CDMA Iteration 15, 2015-5-21, end */


VOS_VOID TAF_APS_GetPdpIdListWithAttachBearerActivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* 注册承载激活指示消息需要进入到所有的实体状态机中 */
    for ( i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}
/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-21, begin */

/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-21, end */

VOS_VOID TAF_APS_GetPdpIdListWithRabmApsSysChgToGprsInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* 当前讨论，RABM消息不做外部检查，如同MMC的消息需要进入到所有的实体状态机中 */
    for (i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}
VOS_VOID TAF_APS_GetPdpIdListWithRabmApsLocalPdpDeactReqMsg(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* 当前讨论，RABM消息不做外部检查，如同MMC的消息需要进入到所有的实体状态机中 */
    for ( i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}
VOS_VOID TAF_APS_GetPdpIdListWithSndcpActRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    APS_SNDCP_ACTIVATE_RSP_MSG         *pstSnActRsp;

    pstSnActRsp = (APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg;

    /* 从SNDCP的消息中获取NSAPI */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByNsapi(pstSnActRsp->ApsSnActRsp.ucNsapi);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSndcpMdfRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    APS_SNDCP_MODIFY_RSP_MSG           *pstSnModifyRsp;

    pstSnModifyRsp = (APS_SNDCP_MODIFY_RSP_MSG*)pstMsg;

    /* 从SNDCP的消息中获取NSAPI */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByNsapi(pstSnModifyRsp->ApsSnMdfRsp.ucNsapi);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSndcpDeactRspMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    APS_SNDCP_DEACTIVATE_RSP_MSG       *pstSnDeactivateRsp;

    pstSnDeactivateRsp = (APS_SNDCP_DEACTIVATE_RSP_MSG*)pstMsg;

    /* 从SNDCP的消息中获取NSAPI */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByNsapi(pstSnDeactivateRsp->ApsSnDeActRsp.ucNsapi);
    pstPdpIdList->ucPdpNum = 1;

}
VOS_VOID TAF_APS_GetPdpIdListWithSndcpStatusReqMsgType(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                          i;

    /* SNDCP消息需要进入到所有的实体状态机中 */
    for ( i = 0; i < TAF_APS_MAX_PDPID; i++)
    {
        pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = (VOS_UINT8)i;
        pstPdpIdList->ucPdpNum++;
    }
}
VOS_VOID TAF_APS_GetPdpIdListWithApsInternalPdpDeactivateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU          *pstInterMsg;

    pstInterMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstInterMsg->ucPdpId;
    pstPdpIdList->ucPdpNum = 1;

}


VOS_VOID TAF_APS_GetPdpIdListWithApsLocalPdpDeactivateInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU          *pstInterMsg;

    pstInterMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstInterMsg->ucPdpId;
    pstPdpIdList->ucPdpNum = 1;

}


VOS_VOID TAF_APS_GetPdpIdListWithApsInternalPdpActivateReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU          *pstInterMsg;

    pstInterMsg = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU*)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstInterMsg->ucPdpId;
    pstPdpIdList->ucPdpNum = 1;
}


VOS_VOID  TAF_APS_GetFsmPdpIdList(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT32                              i;
    VOS_UINT32                              ulTblSize;
    TAF_APS_GET_FSM_PDPID_FUNC_PTR          pGetPdpIdFsmProcFunc;
    REL_TIMER_MSG                          *pstTimerMsg;

    if ( VOS_PID_TIMER == pstMsg->ulSenderPid )
    {
        pstTimerMsg = (REL_TIMER_MSG*)pstMsg;
        pstPdpIdList->ucPdpNum = 1;
        pstPdpIdList->aucPdpId[0] = (VOS_UINT8)pstTimerMsg->ulPara;
        return;
    }


    ulTblSize = sizeof(gastApsGetPdpIdList)/sizeof(gastApsGetPdpIdList[0]);

    /*在ulEventType中，查找对应的处理函数*/
    pGetPdpIdFsmProcFunc = VOS_NULL_PTR;
    for ( i = 0 ; i < ulTblSize; i++ )
    {
        if (ulEventType == gastApsGetPdpIdList[i].ulEventType)
        {
            pGetPdpIdFsmProcFunc = gastApsGetPdpIdList[i].pGetPdpIdFsmProcFunc;

            break;
        }

    }

    /*找到后，调用对应的处理,并返回对应的后续处理时*/
    if (VOS_NULL_PTR != pGetPdpIdFsmProcFunc)
    {
        /* 根据消息发送方、消息中携带的CR,CID获取处理当前消息
           所应该选用的状态机实体 */
        pGetPdpIdFsmProcFunc(pstMsg, pstPdpIdList);

    }

}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithServiceStatusChangeReq
 功能描述  : 获取ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月08日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithServiceStatusChangeReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU     *pstSvcStatusChgReq;


    pstSvcStatusChgReq = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstSvcStatusChgReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_VOID TAF_APS_GetPdpIdListWithXccOrigDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstCallCnf;

    pstCallCnf = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstCallCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithXccHangUpDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_HANGUP_DATA_CALL_CNF_STRU  *pstCallCnf;

    pstCallCnf = (XCC_APS_HANGUP_DATA_CALL_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstCallCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallDiscInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstCallDiscInd;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;

    pstCallDiscInd = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstCallDiscInd->ucConnectId)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }


}


VOS_VOID TAF_APS_GetPdpIdListWithXccIncomingCallInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingInd;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;

    pstIncomingInd = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }


        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.enSo == pstIncomingInd->enSo)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }

}


VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallConnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstConnInd;

    pstConnInd = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstConnInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithXccDataSrvConnInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU  *pstConnInd;

    pstConnInd = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstConnInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithXccAnswerDataCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU      *pstCallCnf;

    pstCallCnf = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstCallCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithCdsCdataServiceInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    CDS_APS_CDATA_SERVICE_IND_STRU         *pstSrvInd;
    VOS_UINT8                               ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity   = VOS_NULL_PTR;

    pstSrvInd = (CDS_APS_CDATA_SERVICE_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }
        pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->ucNsapi == pstSrvInd->ucRabId)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }
}


VOS_VOID TAF_APS_GetPdpIdListWithPsCallEnterDormantInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_CALL_ENTER_DORMANT_IND_STRU *pstEnterDormInd;


    pstEnterDormInd = (TAF_PS_CALL_ENTER_DORMANT_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstEnterDormInd->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithApsInternEndCdmaCallReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_END_CDMA_CALL_REQ_STRU     *pstExtCallEndReq;


    pstExtCallEndReq = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstExtCallEndReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithPppActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf = VOS_NULL_PTR;

    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppActCnf->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithPppDeactCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_DEACT_CNF_STRU             *pstPppDeactCnf = VOS_NULL_PTR;

    pstPppDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppDeactCnf->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}


VOS_VOID TAF_APS_GetPdpIdListWithPppDeactNtf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_DEACT_NTF_STRU             *pstPppDeactNtf = VOS_NULL_PTR;

    pstPppDeactNtf = (PPP_APS_DEACT_NTF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppDeactNtf->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithPppModifyInd
 功能描述  : 获取ID_PPP_APS_MODIFY_IND所对应需要操作的PDP列表
 输入参数  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月27日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithPppModifyInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    PPP_APS_MODIFY_IND_STRU            *pstPppModifyInd = VOS_NULL_PTR;

    pstPppModifyInd = (PPP_APS_MODIFY_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstPppModifyInd->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;
}
/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */
/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-12, begin */

/* Deleted by y00314741 for CDMA Iteration 15, 2015-5-12, end */

VOS_VOID TAF_APS_GetPdpIdListWithEpdszidReOrigReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT32                          ulMainfsmState;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        ulMainfsmState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

        if ((TAF_APS_STA_DORMANT        == ulMainfsmState)
         || (TAF_APS_STA_ACTIVE         == ulMainfsmState)
         || (TAF_APS_STA_CDATA_DISCING  == ulMainfsmState))
        {
            pstPdpIdList->aucPdpId[pstPdpIdList->ucPdpNum] = ucPdpId;
            pstPdpIdList->ucPdpNum++;
        }
    }
}


VOS_VOID TAF_APS_GetPdpIdListWithXccDataCallResumeInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_DATA_CALL_RESUME_IND_STRU  *pstResumeInd;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;

    pstResumeInd = (XCC_APS_DATA_CALL_RESUME_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstResumeInd->ucConnectId)
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;
            return ;
        }
    }
}


VOS_VOID TAF_APS_GetPdpIdListWithXccUpdateDataCallInfoInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInfoInd;

    pstDataCallInfoInd = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstDataCallInfoInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}


/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithHsmOrigCnf
 功能描述  : 获取ID_HSM_APS_ORIG_CNF所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmOrigCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOrigCnf;

    pstOrigCnf = (HSM_APS_ORIG_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstOrigCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithHsmConnectInd
 功能描述  : 获取ID_HSM_APS_CONNECT_IND所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmConnectInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_STA_ENUM_UINT32             enStatus;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* 当前只支持dormant状态下，网络发起的寻呼，因此无效的PDP ID，直接跳过 */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* 网络激活只处理DORMANT和TAF_APS_STA_CDATA_ESTING状态下的流程 */
        enStatus = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ((TAF_APS_STA_DORMANT == enStatus)
          ||(TAF_APS_STA_CDATA_ESTING == enStatus))
        {
            pstPdpIdList->aucPdpId[0] = ucPdpId;
            pstPdpIdList->ucPdpNum    = 1;

            /* 进状态机处理 */
            return ;
        }
    }

}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithHsmDiscCnf
 功能描述  : 获取ID_HSM_APS_DISC_CNF所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmDiscCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    HSM_APS_DISC_CNF_STRU              *pstDiscCnf;

    pstDiscCnf = (HSM_APS_DISC_CNF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstDiscCnf->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithHsmDiscInd
 功能描述  : 获取ID_HSM_APS_DISC_IND所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmDiscInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    HSM_APS_DISC_IND_STRU              *pstDiscInd;

    pstDiscInd = (HSM_APS_DISC_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCallId(pstDiscInd->ucCallId);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithHsmOrigCnf
 功能描述  : 获取ID_HSM_APS_LOC_CHANGED_IND所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsmLocChangedInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
/*    HSM_APS_LOC_CHANGED_IND_STRU       *pstLocChangedInd;

    pstLocChangedInd = (HSM_APS_LOC_CHANGED_IND_STRU *)pstMsg;
*/
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithHsm1XHrpdHandOff
 功能描述  : 获取ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHsm1XToHrpdHandOffCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpIdList->aucPdpId[0] = ucPdpId;
        pstPdpIdList->ucPdpNum    = 1;

        /* 进状态机处理 */
        return ;
    }
}

/* Added by y00314741 for CDMA Iteration 11, 2015-4-7, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWith1XToHrpdHandOffReq
 功能描述  : 获取ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月07日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWith1XToHrpdHandOffReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU     *pst1XToHrpdReq;


    pst1XToHrpdReq = (TAF_APS_INTER_1X_TO_HRPD_HANDOFF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pst1XToHrpdReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithHrpdTo1XHandOffReq
 功能描述  : 获取ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月07日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithHrpdTo1XHandOffReq(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU        *pstHrpdTo1XReq;


    pstHrpdTo1XReq = (TAF_APS_INTER_HRPD_TO_1X_HANDOFF_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0] = pstHrpdTo1XReq->ucPdpId;
    pstPdpIdList->ucPdpNum    = 1;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-4-7, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithEhsmPdnActCnf
 功能描述  : 获取ID_EHSM_APS_PDN_ACTIVATE_CNF所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnActCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstEhsmPdnActCnf;

    pstEhsmPdnActCnf          = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;

    /* 从消息中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnActCnf->ucCid);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf
 功能描述  : 获取ID_EHSM_APS_PDN_DEACTIVATE_CNF所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstEhsmPdnDeactCnf;

    pstEhsmPdnDeactCnf        = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    /* 从消息中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnDeactCnf->ucCid);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithEhsmPdnDeactCnf
 功能描述  : 获取ID_EHSM_APS_PDN_DEACTIVATE_IND所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnDeactInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstEhsmPdnDeactInd;

    pstEhsmPdnDeactInd        = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;

    /* 从消息中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByPndId(pstEhsmPdnDeactInd->ucPdnId);
    pstPdpIdList->ucPdpNum    = 1;

}

/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithEhsmPdnActInd
 功能描述  : 获取ID_EHSM_APS_PDN_ACTIVATE_IND所对应需要操作的PDP列表
 输入参数  : pstMsg:传入的消息
 输出参数  : pstPdpIdList - PDP操作列表
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEhsmPdnActInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{

    EHSM_APS_PDN_ACTIVATE_IND_STRU   *pstEhsmPdnActInd;

    pstEhsmPdnActInd          = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;

    /* 从消息中所带的Cid来查找对应的PDP ID */
    pstPdpIdList->aucPdpId[0] = TAF_APS_GetPdpIdByCid(pstEhsmPdnActInd->ucCid);
    pstPdpIdList->ucPdpNum    = 1;

}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */


VOS_VOID TAF_APS_GetPdpIdListWithEhsmLteHandoverToEhrpdInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU   *pstEhsmHandoverInd;

    pstEhsmHandoverInd          = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0]   = TAF_APS_GetPdpIdByCid(pstEhsmHandoverInd->ucCid);
    pstPdpIdList->ucPdpNum      = 1;

    return;
}


/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_GetPdpIdListWithEnd1xServiceInDormantInd
 功能描述  : 获取ID_MSG_TAF_PS_INTER_END_1X_SERVICE_IN_DORMANT_IND所对应需要操作的PDP列表
 输入参数  : struct MsgCB                       *pstMsg
             TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月04日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_GetPdpIdListWithEnd1xServiceInDormantInd(
    struct MsgCB                       *pstMsg,
    TAF_APS_PDPID_LIST_STRU            *pstPdpIdList
)
{
    TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU   *pstEnd1xSvcInd;

    pstEnd1xSvcInd              = (TAF_PS_CALL_INTER_DORMANT_END_1X_SERVICE_IND_STRU *)pstMsg;

    pstPdpIdList->aucPdpId[0]   = pstEnd1xSvcInd->ucPdpId;
    pstPdpIdList->ucPdpNum      = 1;

    return;
}
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
