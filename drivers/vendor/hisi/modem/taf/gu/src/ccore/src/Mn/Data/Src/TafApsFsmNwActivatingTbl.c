

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
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmNwActivating.h"
#include "AtMnInterface.h"
#include "MmcApsInterface.h"
#include "TafApsSndInternalMsg.h"


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_NWACTIVATING_TBL_C

/******************************************************************************
   2 ȫ�ֱ�������
*****************************************************************************/
/* TAF APS״̬������:NW ACTIVATING ״̬������*/
TAF_FSM_DESC_STRU                       g_stTafApsNwActivatingFsmDesc;

/* TAF_APS_NW_ACTIVATING_SUBSTA_INIT*/
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaInitActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_IND,
                     TAF_APS_RcvSmPdpActivateInd_NwActivating_Init),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_PDP_ACTIVATE_IND,
                     TAF_APS_RcvL4aPdpActivateInd_NwActivating_Init),
#endif
};

/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER������ */
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaWaitAppAnswerActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvSetPdpContextStateReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ANSWER_REQ,
                     TAF_APS_RcvAtPsCallAnswerReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_HANGUP_REQ,
                     TAF_APS_RcvAtPsCallHangupReq_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitAppAnswer),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivateInd_NwActivating_WaitAppAnswer),

};

/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF������ */
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaWaitSmCnfActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_REJ,
                     TAF_APS_RcvSmPdpActRej_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_SEC_REJ,
                     TAF_APS_RcvSmPdpActSecRej_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_SEC_CNF,
                     TAF_APS_RcvSmPdpActSecCnf_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_ACTIVATE_CNF,
                     TAF_APS_RcvSmPdpActCnf_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSmActivateCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSmActivateCnf),
};

#if (FEATURE_ON == FEATURE_LTE)
/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_L4A_CGANS_CNF������ */
TAF_ACT_STRU g_astTafApsNwActivatingSubStaWaitL4aCgansActTbl[] =
{

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(MSP_L4_L4A_PID,
                     ID_L4A_APS_SET_CGANS_CNF,
                     TAF_APS_RcvL4aSetCgansCnf_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(PS_PID_ESM,
                     ID_ESM_SM_EPS_BEARER_INFO_IND,
                     TAF_APS_RcvEsmSmEpsBearerInfoInd_NwActivating_WaitL4aCgansCnf),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitL4aCgansCnf),

};
#endif

/* TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP������ */
TAF_ACT_STRU   g_astTafApsNwActivatingSubStaWaitSndcpActivateRspActTbl[]   =
{
    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ,
                     TAF_APS_RcvAtSetPdpContextStateReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ,
                     TAF_APS_RcvAtPsPppDialOrigReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_ORIG_REQ,
                     TAF_APS_RcvAtPsCallOrigReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_END_REQ,
                     TAF_APS_RcvAtPsCallEndReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_CALL_MODIFY_REQ,
                     TAF_APS_RcvAtPsCallModifyReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_SM,
                     ID_SMREG_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvSmPdpDeactivInd_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_ACT_RSP_MSG_TYPE,
                     TAF_APS_RcvSndcpActivateRsp_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(UEPS_PID_SN,
                     APS_SN_STATUS_REQ_MSG_TYPE,
                     TAF_APS_RcvSndcpStatusReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_INTERNAL_PDP_DEACTIVATE_REQ,
                     TAF_APS_RcvApsInterPdpDeactivateReq_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_APS_LOCAL_PDP_DEACTIVATE_IND,
                     TAF_APS_RcvApsLocalPdpDeactivateInd_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(WUEPS_PID_TAF,
                     ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND,
                     TAF_APS_RcvInterServiceStatusChangeInd_NwActivating_WaitSndcpActivateRsp),

    TAF_ACT_TBL_ITEM(VOS_PID_TIMER,
                     TI_TAF_APS_NET_ACTIVATING,
                     TAF_APS_RcvTiNwActivatingExpired_NwActivating_WaitSndcpActivateRsp),
};

TAF_STA_STRU g_astTafApsNwActivatingStaTbl[] =
{
    /*****************����TAF_APS_NW_ACTIVATING_SUBSTA_INIT״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_INIT,
                      g_astTafApsNwActivatingSubStaInitActTbl ),

    /*****************����TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER,
                      g_astTafApsNwActivatingSubStaWaitAppAnswerActTbl ),

    /*****************����TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_CNF״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SM_ACTIVATE_CNF,
                      g_astTafApsNwActivatingSubStaWaitSmCnfActTbl ),

#if (FEATURE_ON == FEATURE_LTE)
    TAF_STA_TBL_ITEM(TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_L4A_CGANS_CNF,
                     g_astTafApsNwActivatingSubStaWaitL4aCgansActTbl),
#endif
    /*****************����TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP״̬ת�Ʊ�**********************/
    TAF_STA_TBL_ITEM( TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_SNDCP_ACTIVATE_RSP,
                      g_astTafApsNwActivatingSubStaWaitSndcpActivateRspActTbl ),

};


/******************************************************************************
   3 ����ʵ��
******************************************************************************/

VOS_UINT32 TAF_APS_GetNwActivatingStaTblSize( VOS_VOID )
{
    return (sizeof(g_astTafApsNwActivatingStaTbl)/sizeof(TAF_STA_STRU));
}


TAF_FSM_DESC_STRU * TAF_APS_GetNwActivatingFsmDescAddr( VOS_VOID )
{
    return (&g_stTafApsNwActivatingFsmDesc);
}





#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif










