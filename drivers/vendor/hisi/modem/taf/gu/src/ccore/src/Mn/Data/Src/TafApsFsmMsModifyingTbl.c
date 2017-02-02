

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
#include "AtMnInterface.h"
#include "MmcApsInterface.h"

#include "TafFsm.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsFsmMsModifying.h"

#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "ApsL4aInterface.h"
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MSMODIFYING_TBL_C

/******************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/* TAF APS״̬������:MS ACTIVATING ״̬������*/
TAF_FSM_DESC_STRU                       g_stTafApsMsModifyingFsmDesc;


/* TAF_APS_MS_MODIFYING_SUBSTA_INIT������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_Init),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_IND,
                     TAF_APS_RcvSmPdpModifyInd_MsModifying_Init),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_Suspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_Suspend),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSmModifyCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_CNF,
                     TAF_APS_RcvSmPdpModifyCnf_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_REJ,
                     TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_RABM,
                     RABM_APS_LOCAL_PDP_DEACT_REQ_MSG,
                     TAF_APS_RcvRabmLocalPdpDeactReq_MsModifying_WaitSmModifyCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnf),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSmModifyCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_MODIFY_REJ,
                     TAF_APS_RcvSmPdpModifyRej_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSmModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSmModifyCnfSuspend),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSndcpModifyRspActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_MDF_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRsp),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitSndcpModifyRspSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_MDF_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpModifyRsp_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvTafInternalPdpDeaReq_MsModifying_WaitSndcpModifyRspSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitSndcpModifyRspSuspend),
};

#if (FEATURE_ON == FEATURE_LTE)

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitL4aModifyCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_MODIFY_CNF,
                     TAF_APS_RcvL4aPdpModifyCnf_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_MODIFY_REJ,
                     TAF_APS_RcvL4aPdpModifyRej_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitL4aModifyCnf),
};

/* TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF_SUSPEND������ */
TAF_ACT_STRU   g_astTafApsMsModifyingSubStaWaitL4aModifyCnfSuspendActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDailOrigReq_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_MODIFY_CNF,
                     TAF_APS_RcvL4aPdpModifyCnf_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_MODIFY_REJ,
                     TAF_APS_RcvL4aPdpModifyRej_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_MsModifying_WaitL4aModifyCnfSuspend),



    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_MsModifying_WaitL4aModifyCnfSuspend),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_MS_MODIFYING,
                     TAF_APS_RcvTiTafApsMsModifyingExpired_MsModifying_WaitL4aModifyCnfSuspend),
};
#endif


TAF_STA_STRU g_astTafApsMsModifyingStaTbl[] =
{
    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_INIT״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_INIT,
                      g_astTafApsMsModifyingSubStaInitActTbl ),

    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_SUPEND״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_SUSPEND,
                      g_astTafApsMsModifyingSubStaSuspendActTbl ),

    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF,
                      g_astTafApsMsModifyingSubStaWaitSmModifyCnfActTbl ),

    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SM_MODIFY_CNF_SUSPEND,
                      g_astTafApsMsModifyingSubStaWaitSmModifyCnfSuspendActTbl ),

    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP,
                      g_astTafApsMsModifyingSubStaWaitSndcpModifyRspActTbl ),

    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_SNDCP_MODIFY_RSP_SUSPEND,
                      g_astTafApsMsModifyingSubStaWaitSndcpModifyRspSuspendActTbl ),

#if (FEATURE_ON == FEATURE_LTE)

    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF��״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF,
                      g_astTafApsMsModifyingSubStaWaitL4aModifyCnfActTbl ),

    /*****************����TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF_SUSPEND��״̬ת�Ʊ�**********************/
      TAF_STA_TBL_ITEM( TAF_APS_MS_MODIFYING_SUBSTA_WAIT_L4A_MODIFY_CNF_SUSPEND,
                        g_astTafApsMsModifyingSubStaWaitL4aModifyCnfSuspendActTbl ),
#endif
};


/******************************************************************************
   3 ����ʵ��
******************************************************************************/

VOS_UINT32 TAF_APS_GetMsModifyingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsMsModifyingStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_APS_GetMsModifyingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsMsModifyingFsmDesc);
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif













