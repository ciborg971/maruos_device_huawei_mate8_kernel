
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_FSM_UP_LINK_CTRL_C

/*****************************************************************************
  1 Header File Include
*****************************************************************************/
#include "TafXpdsFsmUpLinkCtrl.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"


#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))


TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8 TAF_XPDS_GetServerBindOperType(
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enMpcBindOper,
    TAF_XPDS_SERVER_BIND_OPER_ENUM_UINT8                    enPdeBindOper
)
{
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32                  enCurrMpcStatus;
    AT_XPDS_SERVER_BIND_STATUS_ENUM_UINT32                  enCurrPdeStatus;

    enCurrMpcStatus = TAF_XPDS_GetMpcServerStatus();
    enCurrPdeStatus = TAF_XPDS_GetPdeServerStatus();

    if ((enMpcBindOper == enCurrMpcStatus)
     && (enPdeBindOper == enCurrPdeStatus))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_NO_ACT;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_CONNECT     == enCurrMpcStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET == enMpcBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_CLOSE_MPC_SOCKET;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_CONNECT     == enCurrPdeStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET == enPdeBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_CLOSE_PDE_SOCKET;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_IDLE       == enCurrMpcStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET == enMpcBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_OPEN_MPC_SOCKET;
    }

    if ((AT_XPDS_SERVER_BIND_STATUS_IDLE       == enCurrPdeStatus)
     && (TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET == enPdeBindOper))
    {
        return TAF_XPDS_SERVER_BIND_TYPE_OPEN_PDE_SOCKET;
    }

    return TAF_XPDS_SERVER_BIND_TYPE_NO_ACT;
}


TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32 TAF_XPDS_GetServerBindFailCause(
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType
)
{
    if ((enBindType == TAF_XPDS_SERVER_BIND_TYPE_OPEN_MPC_SOCKET)
     || (enBindType == TAF_XPDS_SERVER_BIND_TYPE_CLOSE_MPC_SOCKET))
    {
        return TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT;
    }
    else
    {
        return TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT;
    }
}


VOS_VOID TAF_XPDS_UpLinkCtrlServerBindProc(
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType
)
{
    TAF_XPDS_CFG_INFO_STRU             *pstConfigInfo;

    pstConfigInfo = TAF_XPDS_GetAgpsCfg();

    switch (enBindType)
    {
        case TAF_XPDS_SERVER_BIND_TYPE_OPEN_MPC_SOCKET:

            TAF_XPDS_SndAtApOpenSocketReq(AT_XPDS_SERVER_MODE_MPC,
                                          pstConfigInfo->ulMpcAddr,
                                          pstConfigInfo->ulMpcPort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_MPC_SOCKET_CNF);

            break;

        case TAF_XPDS_SERVER_BIND_TYPE_OPEN_PDE_SOCKET:

            TAF_XPDS_SndAtApOpenSocketReq(AT_XPDS_SERVER_MODE_PDE,
                                          pstConfigInfo->ulPdeAddr,
                                          pstConfigInfo->ulPdePort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_OPEN_PDE_SOCKET_CNF);

            break;

        case TAF_XPDS_SERVER_BIND_TYPE_CLOSE_MPC_SOCKET:

            TAF_XPDS_SndAtApCloseSocketReq(AT_XPDS_SERVER_MODE_MPC,
                                           pstConfigInfo->ulMpcAddr,
                                           pstConfigInfo->ulMpcPort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_MPC_SOCKET_CNF);

            break;

        case TAF_XPDS_SERVER_BIND_TYPE_CLOSE_PDE_SOCKET:

            TAF_XPDS_SndAtApCloseSocketReq(AT_XPDS_SERVER_MODE_PDE,
                                           pstConfigInfo->ulPdeAddr,
                                           pstConfigInfo->ulPdePort);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_CLOSE_PDE_SOCKET_CNF);

            break;

        default:
            return;
    }

    /* ����������ʱ�� */
    if (TAF_XPDS_TIMER_START_FAILURE == TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND,
                                                            TI_TAF_XPDS_WAIT_AT_BINDUP_IND_TIMER_LEN))
    {
        XPDS_WARNING_LOG("TAF_XPDS_UpLinkCtrlServerBindProc: WARNING: Start Timer failed!");
    }

    return;
}
VOS_VOID TAF_XPDS_UpLinkCtrlPreEntryMsgProc(VOS_VOID)
{
    TAF_XPDS_MSG_STRU                                      *pstEntryMsg;
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU                    *pstBindServerReq;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8                    enBindType;

    pstEntryMsg       = TAF_XPDS_GetCurrFsmEntryMsgAddr();
    pstBindServerReq  = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstEntryMsg->aucMsgBuffer;


    enBindType        = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                   pstBindServerReq->enPdeBindOpt);

    /* ��������Ϣָ���Ĳ��������뱾�ط�����ά����Socket Bind״̬һ�£��˳�L2״̬�� */
    if (TAF_XPDS_SERVER_BIND_TYPE_NO_ACT == enBindType)
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_QuitFsmL2();

        return;
    }

    TAF_XPDS_UpLinkCtrlServerBindProc(enBindType);

    return;
}
VOS_UINT32  TAF_XPDS_RcvXpdsServerBindReq_UpLinkCtrl_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU    *pstBindServerReq = VOS_NULL_PTR;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType;

    pstBindServerReq = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstMsg;
    enBindType       = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                      pstBindServerReq->enPdeBindOpt);

    /* Init�����ｫAbort״̬����ΪVOS_FALSE */
    TAF_XPDS_SetUplinkAbortScene(TAF_XPDS_PROC_RSLT_SUCC);

    /* ��������Ϣָ���Ĳ��������뱾�ط�����ά����Socket Bind״̬һ�£��˳�L2״̬�� */
    if (TAF_XPDS_SERVER_BIND_TYPE_NO_ACT == enBindType)
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���������Ϣ */
    TAF_XPDS_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ���AGPS Data Call�����ڣ���Ҫ��ȥ����Data Call */
    if (AT_XPDS_DATA_CALL_STATUS_IDLE == TAF_XPDS_GetDataCallStatus())
    {
        /* ������Ϣ����Open Cagps Data CAll ״̬*/
        TAF_XPDS_SndAtApOpenCagpsDataCall();

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_UP_LINK_CTRL_SUBSTA_WAIT_DATA_CAll_CONNECT_CNF);

        /* ���õȴ�AP�ظ���ʱ�� */
        if (TAF_XPDS_TIMER_START_FAILURE == TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND,
                                                                TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND_TIMER_LEN))
        {
            XPDS_WARNING_LOG("TAF_XPDS_RcvXpdsServerBindOperReq_UpLinkCtrl_Init: WARNING: Start Timer failed!");
        }

        return VOS_TRUE;
    }

    TAF_XPDS_UpLinkCtrlServerBindProc(enBindType);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvAtApDataCallStatusInd_UpLinkCtrl_WaitDataCallConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                       *pstAtXpdsMsg;
    AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU   *pstDataCallInd;
    TAF_XPDS_MSG_STRU                      *pstEntryMsg;
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU    *pstBindServerReq;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32      enRslt;

    pstEntryMsg       = TAF_XPDS_GetCurrFsmEntryMsgAddr();
    pstBindServerReq  = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstEntryMsg->aucMsgBuffer;
    enBindType        = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                       pstBindServerReq->enPdeBindOpt);

    pstAtXpdsMsg   = (AT_XPDS_MSG_STRU *)pstMsg;
    pstDataCallInd = (AT_XPDS_AP_DATA_CALL_STATUS_IND_STRU *)pstAtXpdsMsg->aucContent;

    /* ������APͨ��ʹ�õ�ClientId */
    TAF_XPDS_SetApClientId(pstAtXpdsMsg->stAppCtrl.usClientId);

    /* ֹͣ�л�APN������AGPS Data Call�ĵȴ���ʱ�� */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_DATA_CALL_IND);

    /* ����AGPS DATA CALL STATUS */
    TAF_XPDS_SetDataCallStatus(pstDataCallInd->enChannelState);

    /* �����ǰ����Abort������ֱ�ӻظ�L1 Abort CNF */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����л�APNʧ��,�ظ�Failure */
    if (AT_XPDS_DATA_CALL_STATUS_CONNECT != pstDataCallInd->enChannelState)
    {
        enRslt = TAF_XPDS_GetServerBindFailCause(enBindType);

        TAF_XPDS_SndInternalServerBindRsltCnf(enRslt);

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMpcBindStatus;
    AT_XPDS_MSG_STRU                       *pstAtXpdsMsg;

    pstAtXpdsMsg     = (AT_XPDS_MSG_STRU *)pstMsg;
    pstMpcBindStatus = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstAtXpdsMsg->aucContent;

    if (AT_XPDS_SERVER_MODE_MPC != pstMpcBindStatus->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_SetMpcServerStatus(pstMpcBindStatus->enBindStatus);

    /* ֹͣ�ȴ���ʱ�� */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    /* ����Abort��ǣ���ֱ���˳�L2״̬�� */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == pstMpcBindStatus->enBindStatus)
    {
        /* ����Check�Ƿ����ȥOpen PDE Socket */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT);

        TAF_XPDS_QuitFsmL2();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitCloseMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstMpcBindStatus;
    AT_XPDS_MSG_STRU                       *pstAtXpdsMsg;

    pstAtXpdsMsg     = (AT_XPDS_MSG_STRU *)pstMsg;
    pstMpcBindStatus = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstAtXpdsMsg->aucContent;

    if (AT_XPDS_SERVER_MODE_MPC != pstMpcBindStatus->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    TAF_XPDS_SetMpcServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    /* ����Abort��ǣ���ֱ���˳�L2״̬�� */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����Check�Ƿ������������������ */
    TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitOpenPdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstPdeBindStatus;
    AT_XPDS_MSG_STRU                       *pstAtXpdsMsg;

    pstAtXpdsMsg     = (AT_XPDS_MSG_STRU *)pstMsg;
    pstPdeBindStatus = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstAtXpdsMsg->aucContent;

    if (AT_XPDS_SERVER_MODE_PDE != pstPdeBindStatus->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_SetPdeServerStatus(pstPdeBindStatus->enBindStatus);

    /* ֹͣ�ȴ���ʱ�� */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    /* ����Abort��ǣ���ֱ���˳�L2״̬�� */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    if (AT_XPDS_SERVER_BIND_STATUS_CONNECT == pstPdeBindStatus->enBindStatus)
    {
        /* ����Check�Ƿ����ȥOpen MPC Socket */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT);

        TAF_XPDS_QuitFsmL2();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvAtApBindServerStatusInd_UpLinkCtrl_WaitClosePdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *pstPdeBindStatus;
    AT_XPDS_MSG_STRU                       *pstAtXpdsMsg;

    pstAtXpdsMsg     = (AT_XPDS_MSG_STRU *)pstMsg;
    pstPdeBindStatus = (AT_XPDS_AP_SERVER_BIND_STATUS_IND_STRU *)pstAtXpdsMsg->aucContent;

    if (AT_XPDS_SERVER_MODE_PDE != pstPdeBindStatus->enServerMode)
    {
        return VOS_TRUE;
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_AT_BINDUP_IND);

    TAF_XPDS_SetPdeServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    /* ����Abort��ǣ���ֱ���˳�L2״̬�� */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����Check�Ƿ������������������ */
    TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvTiWaitDataCallIndExpired_UpLinkCtrl_WaitDataCallConnCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_MSG_STRU                      *pstEntryMsg;
    TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU    *pstBindServerReq;
    TAF_XPDS_SERVER_BIND_TYPE_ENUM_UINT8    enBindType;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32      enRslt;

    pstEntryMsg      = TAF_XPDS_GetCurrFsmEntryMsgAddr();
    pstBindServerReq = (TAF_XPDS_XPDS_UP_LINK_CTRL_REQ_STRU *)pstEntryMsg->aucMsgBuffer;
    enBindType       = TAF_XPDS_GetServerBindOperType(pstBindServerReq->enMpcBindOpt,
                                                      pstBindServerReq->enPdeBindOpt);

    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        enRslt = TAF_XPDS_GetUpLinkAbortScene();
    }
    else
    {
        enRslt = TAF_XPDS_GetServerBindFailCause(enBindType);
    }

    TAF_XPDS_SndInternalServerBindRsltCnf(enRslt);

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvTiWaitOpenMpcSocketExpired_UpLinkCtrl_WaitOpenMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT);
    }

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvTiWaitCloseMpcSocketExpired_UpLinkCtrl_WaitCloseMpcSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetMpcServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* ����Check�Ƿ������������������ */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

        return VOS_TRUE;
    }
}
VOS_UINT32 TAF_XPDS_RcvTiWaitOpenPdeSocketExpired_UpLinkCtrl_WaitOpenPdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());
    }
    else
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT);
    }

    TAF_XPDS_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 TAF_XPDS_RcvTiWaitClosePdeSocketExpired_UpLinkCtrl_WaitClosePdeSocket(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetPdeServerStatus(AT_XPDS_SERVER_BIND_STATUS_IDLE);

    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetUpLinkAbortScene())
    {
        TAF_XPDS_SndInternalServerBindRsltCnf(TAF_XPDS_GetUpLinkAbortScene());

        TAF_XPDS_QuitFsmL2();

        return VOS_TRUE;
    }
    else
    {
        /* ����Check�Ƿ������������������ */
        TAF_XPDS_UpLinkCtrlPreEntryMsgProc();

        return VOS_TRUE;
    }
}
VOS_UINT32 TAF_XPDS_RcvXpdsAbortAgpsSessionInd_L2UpLink(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortInd;

    pstAbortInd = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *)pstMsg;

    TAF_XPDS_SetUplinkAbortScene(pstAbortInd->enAbortScene);

    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


