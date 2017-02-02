

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXsmsSndXcc.h"
#include "TafSdcCtx.h"
#include "TafXsmsCtx.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_SND_XCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID TAF_XSMS_SndXccIncomingCallRsp
(
    VOS_UINT8                           ucCallId,
    VOS_UINT8                           ucConnectId,
    XCC_CSMS_RESULT_ENUM_UINT32         enRslt
)
{
    CSMS_XCC_INCOMING_CALL_RSP_STRU    *pstIncomingCallRspMsg;

    /* ������Ϣ */
    pstIncomingCallRspMsg = (CSMS_XCC_INCOMING_CALL_RSP_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                            (sizeof(CSMS_XCC_INCOMING_CALL_RSP_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstIncomingCallRspMsg)
    {
        return;
    }

    pstIncomingCallRspMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstIncomingCallRspMsg->ulReceiverPid       = UEPS_PID_XCC;
    pstIncomingCallRspMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstIncomingCallRspMsg->ulSenderPid         = UEPS_PID_XSMS;

    /*��Ϣ���*/
    pstIncomingCallRspMsg->enMsgId             = ID_CSMS_XCC_INCOMING_CALL_RSP;
    pstIncomingCallRspMsg->ucCallId            = ucCallId;
    pstIncomingCallRspMsg->ucConnectId         = ucConnectId;
    pstIncomingCallRspMsg->usOpId              = 0;
    pstIncomingCallRspMsg->enRslt              = enRslt;


    /* ������Ϣ */
   (VOS_VOID) VOS_SendMsg(UEPS_PID_XSMS, pstIncomingCallRspMsg);

    return;
}
VOS_VOID TAF_XSMS_SndXccAnswerCallReq(VOS_UINT8 ucCallId)
{
    CSMS_XCC_ANSWER_CALL_REQ_STRU      *pstAnswerCallMsg;

    /* ������Ϣ */
    pstAnswerCallMsg = (CSMS_XCC_ANSWER_CALL_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                     (sizeof(CSMS_XCC_ANSWER_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstAnswerCallMsg)
    {
        return;
    }

    pstAnswerCallMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstAnswerCallMsg->ulReceiverPid       = UEPS_PID_XCC;
    pstAnswerCallMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstAnswerCallMsg->ulSenderPid         = UEPS_PID_XSMS;

    /*��Ϣ���*/
    pstAnswerCallMsg->enMsgId             = ID_CSMS_XCC_ANSWER_CALL_REQ;
    pstAnswerCallMsg->ucCallId            = ucCallId;
    pstAnswerCallMsg->usOpId              = 0;


    /* ������Ϣ */
    (VOS_VOID)VOS_SendMsg(UEPS_PID_XSMS, pstAnswerCallMsg);

    return;
}
VOS_VOID TAF_XSMS_SndXccSmsOrgiCallReq
(
    VOS_UINT8                               ucCallId,
    VOS_UINT8                               ucIsL2ErrReOrig,
    VOS_UINT8                               ucL2ErrReOrigCount
)
{
    CSMS_XCC_ORIG_SMS_CALL_REQ_STRU    *pstOrigCallMsg;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec    = TAF_XSMS_MoGetRecAddr();

    /* ������Ϣ */
    pstOrigCallMsg = (CSMS_XCC_ORIG_SMS_CALL_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                     sizeof(CSMS_XCC_ORIG_SMS_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstOrigCallMsg)
    {
        return;
    }

    pstMoRec->ucWaitRedirCompleteFlag   = VOS_FALSE;

    pstMoRec->ucIsOrigReqSendFlag       = VOS_TRUE;

    TAF_SDC_SetXsmsCallExistFlg(VOS_TRUE);

    pstOrigCallMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstOrigCallMsg->ulReceiverPid       = UEPS_PID_XCC;
    pstOrigCallMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstOrigCallMsg->ulSenderPid         = UEPS_PID_XSMS;

    /*��Ϣ���*/
    pstOrigCallMsg->enMsgId             = ID_CSMS_XCC_ORIG_SMS_CALL_REQ;
    pstOrigCallMsg->usOpId              = 0;
    pstOrigCallMsg->ucCallId            = ucCallId;
    pstOrigCallMsg->enSo                = TAF_CDMA_SO_6_SMS;
    /* �����ٺ�NASȷ�����Ƿ������� */
    pstOrigCallMsg->ucIsL2ErrReOrig     = ucIsL2ErrReOrig;
    pstOrigCallMsg->ucL2ErrReOrigCount  = ucL2ErrReOrigCount;


    /* ������Ϣ */
    VOS_SendMsg(UEPS_PID_XSMS, pstOrigCallMsg);

    return;
}


VOS_VOID TAF_XSMS_SndXccEndCallReq
(
    VOS_UINT8                           ucCallId,
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    CSMS_XCC_END_SMS_CALL_REQ_STRU     *pstEndCallMsg;

    /* ������Ϣ */
    pstEndCallMsg = (CSMS_XCC_END_SMS_CALL_REQ_STRU *)VOS_AllocMsg(UEPS_PID_XSMS,
                                                                   (sizeof(CSMS_XCC_END_SMS_CALL_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    if (VOS_NULL_PTR == pstEndCallMsg)
    {
        return;
    }

    TAF_SDC_SetXsmsCallExistFlg(VOS_FALSE);

    pstEndCallMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
    pstEndCallMsg->ulReceiverPid        = UEPS_PID_XCC;
    pstEndCallMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
    pstEndCallMsg->ulSenderPid          = UEPS_PID_XSMS;

    /* ��Ϣ��� */
    pstEndCallMsg->enMsgId              = ID_CSMS_XCC_END_SMS_CALL_REQ;
    pstEndCallMsg->usOpId               = 0;
    pstEndCallMsg->ucCallId             = ucCallId;
    pstEndCallMsg->enEndReason          = enEndReason;


    /* ������Ϣ */
    (VOS_VOID)VOS_SendMsg(UEPS_PID_XSMS, pstEndCallMsg);

    return;

}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



