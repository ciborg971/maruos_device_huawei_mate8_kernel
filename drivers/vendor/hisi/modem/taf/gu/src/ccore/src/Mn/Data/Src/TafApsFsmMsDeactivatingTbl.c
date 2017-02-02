

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "Taf_Aps.h"
#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMsDeactivating.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "AtMnInterface.h"
#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSDEACTIVATING_TBL_C

/******************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/* TAF APS״̬������:MS ACTIVATING ״̬������*/
TAF_FSM_DESC_STRU                       g_stTafApsMsDeactivatingFsmDesc;

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF������ */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInternalPdpDeavtivateReq_MsDeactivating_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                    ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                    TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Init),

};

 /* TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND*/
 TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaSuspendActTbl[]   =
 {

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_Suspend),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvL4aPdpDeactivateInd_MsDeactivating_Suspend),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_Suspend),
#endif
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF������ */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_CNF,
                     TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSmDeactivateCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnf),
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_CNF,
                     TAF_APS_RcvSmPdpDeactivateCnf_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStaChangeInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitSmDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvL4aPdpDeactivateInd_MsDeactivating_WaitSmDeactivateCnfSuspend),
#endif

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSmDeactivateCnfSuspend),
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF������ */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_DEACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitSndcpDeactivateRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRsp),

};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_DEACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpDeactivateRsp_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitSndcpDeactivateRspSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitSndcpDeactivateRspSuspend),

};

#if (FEATURE_ON == FEATURE_LTE)
/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_L4A_DEACTIVATE_CNF������ */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitL4aDeactivateCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_CNF,
                     TAF_APS_RcvL4aPdpDeactivateCnf_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_REJ,
                     TAF_APS_RcvL4aPdpDeactivateRej_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PS_CALL_END_CNF,
                     TAF_APS_RcvL4aPsCallEndCnf_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitL4aDeactivateCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitL4aDeactivateCnf),
};

/* TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_L4A_DEACTIVATE_CNF_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsMsDeactivatingSubStaWaitL4aDeactivateCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPppDailOrigReq_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_CNF,
                     TAF_APS_RcvL4aPdpDeactivateCnf_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_REJ,
                     TAF_APS_RcvL4aPdpDeactivateRej_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvL4aPdpDeactivateInd_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PS_CALL_END_CNF,
                     TAF_APS_RcvL4aPsCallEndCnf_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStaChgInd_MsDeactivating_WaitL4aDeactivateCnfSuspend),

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_ACT_TBL_ITEM(UEPS_PID_EHSM,
                     ID_EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND,
                     TAF_APS_RcvEhsmLteHandoverToEhrpdInd_MsDeactivating_WaitL4aDeactivateCnfSuspend),
#endif

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsDeactivating_WaitL4aDeactivateCnfSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_DEACTIVATING,
                     TAF_APS_RcvTiMsDeactivatingExpired_MsDeactivating_WaitL4aDeactivateCnfSuspend),

};
#endif


TAF_STA_STRU g_astTafApsMsDeactivatingStaTbl[] =
{
    /*****************����TAF_APS_MS_DEACTIVATING_SUBSTA_INIT״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_INIT,
                      g_astTafApsMsDeactivatingSubStaInitActTbl ),

    /*****************����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF,
                      g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfActTbl ),

    /*****************����TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaSuspendActTbl ),

    /*****************����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SM_DEACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaWaitSmDeactivateCnfSuspendActTbl ),

    /*****************����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF,
                      g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspActTbl ),

    /*****************����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_SNDCP_DEACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaWaitSndcpDeactivateRspSuspendActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    /*****************����TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_L4A_ACTIVATE_CNF��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_L4A_DEACTIVATE_CNF,
                      g_astTafApsMsDeactivatingSubStaWaitL4aDeactivateCnfActTbl ),

    TAF_STA_TBL_ITEM( TAF_APS_MS_DEACTIVATING_SUBSTA_WAIT_L4A_DEACTIVATE_CNF_SUSPEND,
                      g_astTafApsMsDeactivatingSubStaWaitL4aDeactivateCnfSuspendActTbl ),
#endif

};


/******************************************************************************
   3 ����ʵ��
******************************************************************************/

VOS_UINT32 TAF_APS_GetMsDeactivatingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsMsDeactivatingStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_APS_GetMsDeactivatingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsMsDeactivatingFsmDesc);
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif












