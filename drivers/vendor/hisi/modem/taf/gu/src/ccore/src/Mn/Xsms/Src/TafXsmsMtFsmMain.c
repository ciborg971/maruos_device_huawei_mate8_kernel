/******************************************************************************

                  ��Ȩ���� (C), 2001-2014, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : TafXsmsMtFsmMain.c
  �� �� ��   : ����
  ��    ��   : h00300778
  ��������   : 2014��10��31��
  ��������   : 1X SMS(Short Message Service)MT����״̬��������
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2014��10��31��
    ��    ��   : h00300778
    �޸�����   : �����ļ�
******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafXsmsMtFsmMain.h"
#include  "TafXsmsMtFsmMainTbl.h"
#include  "TafXsmsCtx.h"
#include  "TafXsmsSndXcc.h"
#include  "TafXsmsSndCas.h"
#include  "TafXsmsSndAt.h"
#include  "TafXsmsMsgProc.h"
#include  "TafXsmsTimer.h"
#include  "UsimPsInterface.h"
#include  "TafXsmsUimProc.h"
#include  "TafXsmsDecode.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "TafXsmsEncode.h"
#include  "TafSdcCtx.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MT_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_UINT32 TAF_XSMS_MtFsmMainProc(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet;
    TAF_XSMS_MT_FSM_ID_ENUM_UINT32      enCurState;
    VOS_UINT16                          usTemp;
    TAF_ACTION_FUNC                     pActFun;
    REL_TIMER_MSG                      *pstRelTimerMsg;

    if (VOS_PID_TIMER == pstMsg->ulSenderPid)
    {
        /* ��ʱ����Ϣ���� */
        pstRelTimerMsg = (REL_TIMER_MSG*)pstMsg;

        ulEventType = TAF_BuildEventType(VOS_PID_TIMER, pstRelTimerMsg->ulName);
    }
    else if (WUEPS_PID_USIM == pstMsg->ulSenderPid)
    {
        /* ����Ϣ���� */
        PS_MEM_CPY(&usTemp, pstMsg->aucValue, 2);

        ulEventType = TAF_BuildEventType(WUEPS_PID_USIM, usTemp);
    }
    else
    {
        PS_MEM_CPY(&usTemp, pstMsg->aucValue, 2);

        ulEventType = TAF_BuildEventType(pstMsg->ulSenderPid, usTemp);
    }

    enCurState = TAF_XSMS_MtGetCurrFsmId();

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MT_FSM, (VOS_UINT8*)&enCurState, sizeof(TAF_XSMS_MO_FSM_ID_ENUM_UINT32));

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtFsmMainProc:Current Status is ", (VOS_INT32)enCurState);
    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtFsmMainProc:Event Type is ", (VOS_INT32)ulEventType);

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = TAF_FSM_FindAct(&g_stTafXsmsMtFsmDesc, enCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* ������ص��¼���������Ϊ��,�����������¼����� */
        ulRet   = (*pActFun)(ulEventType, (struct MsgCB*)pstMsg);

        return ulRet;
    }

    TAF_XSMS_WARNING_LOG("TAF_XSMS_MtFsmMainProc:TAF_FSM_FindAct return null ptr ");

    return VOS_ERR;
}


VOS_VOID TAF_XSMS_MtDealTlAck
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* �ж��Ƿ���Ҫ��TL ACK */
    if (VOS_TRUE == pstMtRec->stTLP2PMsg.unPresentFlag.stTLBitPresentFlag.bIsOpBearReplyOpPresent)
    {
        TAF_XSMS_NORMAL_LOG("TAF_XSMS_MtDealTlAck:need to send TL ACK");

        if (TAF_XSMS_CCF_AP_MEM_FULL == TAF_XSMS_GetApMemFullFlag())
        {
            TAF_XSMS_NORMAL_LOG("TAF_XSMS_MtDealTlAck: TAF_XSMS_GetApMemFullFlag is full");
            enCauseCode     = TAF_XSMS_TL_DESTINATION_RESOURCE_SHORTAGE;
            enErrorClass    = TAF_XSMS_TL_CAUSECODE_TMP;
        }

        /*  ��CAUSE CODE ����MTȫ�ֱ���������TL_ACK���͵��ܶ�ʱ����1S��ʱ,�������30��ֱ��ʧ���˳����� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_RESEND,
                            pstMtRec->stResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND);

        if (VOS_ERR == TAF_XSMS_EncodeTlAckInMtRec(enCauseCode,  enErrorClass))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_MtDealTlAck: TAF_XSMS_EncodeTlAckInMtRec err");

            TAF_XSMS_MtIdleInit();

            return ;
        }

        if (VOS_ERR == TAF_XSMS_SndCasTlAckAccordingCurUeState())
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_MtDealTlAck: TAF_XSMS_SndCasTlAckAccordingCurUeState err");

            TAF_XSMS_MtIdleInit();

            return ;
        }

        return ;

    }
    else
    {
        if (TAF_XSMS_ACTIVE_CSCH  == pstMtRec->enActiveRevChannel)
        {
            TAF_XSMS_SndCasCschOrderMsg(0, pstMtRec->enIsCasAckFlag, pstMtRec->aucCasAckData);
        }
    }

    /* ����Ҫ�ظ�TL ACK�����߷���TL ACK���� */
    if (TAF_XSMS_ACTIVE_DSCH  == pstMtRec->enActiveRevChannel)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealTlAck:no need to send TL ACK, end call");

        /* Traffic channel�����ŵ� */
        TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealTlAck:no need to send TL ACK, return to IDLE");

        /* Access channel����IDLE,��ʼ��ȫ�ֱ�����״̬�� */
        TAF_XSMS_MtIdleInit();
    }

    return;
}
VOS_VOID TAF_XSMS_MtDealPrl(VOS_VOID)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulEncodedResult;
    VOS_UINT8                           ucEncodedLen;
    VOS_UINT8                           aucData[TAF_XSMS_RECORD_LEN_MAX];
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    PS_MEM_SET(aucData, 0, TAF_XSMS_RECORD_LEN_MAX);

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* ��PRL�������û��,����д������ */
    if (VOS_OK == TAF_XSMS_FindFreeIndex(&ucIndex))
    {
        TAF_XSMS_INFO_LOG1("TAF_XSMS_MtDealPrl:FindFreeIndex = ", (VOS_UINT32)ucIndex);

        /* ���ñ���ӿڽ� stuctת����TL PDU����,bear_reply_seqд��63 */
        ulEncodedResult = TAF_XSMS_EncodeBearDataStruToSimRaw(&pstMtRec->stTLP2PMsg.stMessage,
                                                              aucData + 2,
                                                              TAF_XSMS_BEAR_REPLY_SEQ_PRL,
                                                              &ucEncodedLen,
                                                              TAF_XSMS_STATUS_REC_UNREAD,
                                                              VOS_TRUE);

        /* ���ݳ�������һ������������ֱ�ӷ��ش�cause code��TL ACK������ */
        if (VOS_OK != ulEncodedResult)
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_MtDealPrl:encode BearDataStru to SimRawPDU error");

            TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_OTHER_GENERAL_PROBLEMS,
                                 TAF_XSMS_TL_CAUSECODE_TMP);
            return;
        }

        /* ��Ƕ���Ϊ����δ�� */
        aucData[0] = TAF_XSMS_STATUS_REC_UNREAD;
        /* ��Ƕ���TL PDU���� */
        aucData[1] = ucEncodedLen;

        /* д�� */
        TAF_XSMS_PrlWriteReq(ucEncodedLen + 2, aucData, ucIndex);

        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF_MAX);

        /* ���õ�ǰ״̬Ϊ��д���ظ� */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_UIM_WRITE_CNF_STATE);
    }
    else
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_MtDealPrl:no free index in uim, to report uim full");

        /* ����AT�ӿ��ϱ����� */
        TAF_XSMS_MsgUimFullInd();

        /* ����TL_ACK CAUSE CODE Ϊ���� */
        TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_RESOURCE_SHORTAGE,
                             TAF_XSMS_TL_CAUSECODE_TMP);
    }

    return;
}


VOS_VOID TAF_XSMS_MtDealDataInd(TAF_XSMS_CAS_DATA_IND_MSG_STRU *pstDataInd)
{
    VOS_UINT32                          ulDecodedResult;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* ������ն��ŵ��ŵ� */
    if (ID_CAS_CNAS_1X_DSCH_DATA_IND == pstDataInd->enMsgId)
    {
        pstMtRec->enActiveRevChannel = TAF_XSMS_ACTIVE_DSCH;
    }
    else
    {
        pstMtRec->enActiveRevChannel = TAF_XSMS_ACTIVE_CSCH;
    }

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtDealDataInd:ActiveRevChannel is ",
                       (VOS_UINT32)pstMtRec->enActiveRevChannel);

    /* ͨ������ӿڱ��TL STRU */
    ulDecodedResult = TAF_XSMS_DecodeTLRawToTLStru(pstDataInd->ucLen, pstDataInd->aucMsg, &pstMtRec->stTLP2PMsg);

    TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_RCV_SMS,
                            pstMtRec->stTLP2PMsg.ucBearReplySeqNum,
                            &pstMtRec->stTLP2PMsg.stMessage);

    TAF_XSMS_INFO_LOG1(" Recieve Msg, the seq num is", pstMtRec->stTLP2PMsg.ucBearReplySeqNum);

    /* ����������ֱ�ӷ��ش�cause code��TL ACK������ */
    if (VOS_OK != ulDecodedResult)
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_MtDealDataInd:DecodeTLRawToTLStru error");

        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
        return;
    }

    /* �ж��ǲ���CATPT���� */
    if ((TAF_XSMS_TELESERVICE_CATPT == pstMtRec->stTLP2PMsg.stMessage.ulTeleserviceID)
    &&  (VOS_TRUE == pstMtRec->stTLP2PMsg.unPresentFlag.stTLBitPresentFlag.bIsOpIsPPDownload))
    {
        TAF_XSMS_MtDealCatptMsgProc(pstDataInd);

        return;
    }
    /* �����ǰ���ռ�����ֱ�ӻظ�TL_ACK */

    /* �����AGPS NI������Ҫ����Ȼ�����ݴ���MTA */
    if (TAF_XSMS_TELESERVICE_AGPS_NI_SMS == pstMtRec->stTLP2PMsg.stMessage.ulTeleserviceID)
    {
        if (VOS_ERR == TAF_XSMS_MtAgpsSmsHandle(&pstMtRec->stTLP2PMsg.stMessage))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_MtDealDataInd : TAF_XSMS_MtAgpsSmsHandle ERR");
        }

        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
        return;
    }

    /* �ж��ǲ���PRL���� */
    if (VOS_TRUE == pstMtRec->stTLP2PMsg.unPresentFlag.stTLBitPresentFlag.bIsOpIsPRL)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealDataInd: there is a PRL SMS");

        /* ��PRL,�ȴ濨���ٶ�ȡ�ϱ� */
        TAF_XSMS_MtDealPrl();

        return;
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtDealDataInd: there is a normal SMS");

        /* ����PRL,���� TL_ACK������� */
        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);

        /* ͨ���ӿ��ϱ� */
        TAF_XSMS_MsgDeliveryInd(&pstMtRec->stTLP2PMsg.stMessage);
    }

    return;
}


VOS_UINT32 TAF_XSMS_MtDealSndCasDataReq(VOS_VOID)
{
    VOS_UINT32                          ulRst;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;
    VOS_UINT8                           aucData[3];

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    PS_MEM_SET(aucData, 0, 3);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MtDealSndCasDataReq:ActiveRevChannel is ",
                       (VOS_UINT32)pstMtRec->enActiveRevChannel);

    /* ������㷢��Ϣ */
    if (TAF_XSMS_ACTIVE_DSCH  == pstMtRec->enActiveRevChannel)
    {
        /* Traffic channel */
        ulRst = TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT, &pstMtRec->stDbm);
    }
    else
    {
        /* Access channel����ҪЯ����Ȩ��Ϣ */
        TAF_XSMS_EncodeAuth(&pstMtRec->stTLP2PMsg.stMessage.stAddr, aucData);
        ulRst = TAF_XSMS_SndCasCschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT, aucData, &pstMtRec->stDbm);
    }

    return ulRst;
}
VOS_UINT32 TAF_XSMS_MtSendCasTlAck
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
)
{
    VOS_UINT32                          ulEncodedResult;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* ��causecode��errorclass����ȫ�ֱ��� */
    pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode  = enCauseCode;
    pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass = enErrorClass;

    /* ��������ACK�� SEQ NUM  */
    pstMtRec->stTLP2PMsg.stCauseCode.ucReplySeq     = pstMtRec->stTLP2PMsg.ucBearReplySeqNum;

    TAF_XSMS_INFO_LOG1(" Send TL_ACK the seq num is ", pstMtRec->stTLP2PMsg.ucBearReplySeqNum);

    /* ͨ��������TL ACK DBM�ṹ�� */
    ulEncodedResult = TAF_XSMS_GetAckDBMStru(&pstMtRec->stTLP2PMsg.stMessage.stAddr,
                                             &pstMtRec->stTLP2PMsg.stCauseCode,
                                             &pstMtRec->stDbm);

    if (VOS_OK != ulEncodedResult)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtSendCasTlAck:GetAckDBMStru error");

        /* ����ʧ�� */
        return VOS_ERR;
    }

    if (VOS_OK != TAF_XSMS_MtDealSndCasDataReq())
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtSendCasTlAck:MtDealSndCasDataReq error");

        /* ����DATAREQ���� */
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_MtResend
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���û�г������Դ���
    1.0 ��ǰUE״̬ IDLE ��CSCH�� ���͵ȴ�CSCH_CNF
    2.0 ��ǰ��UE״̬��TCH, ��DSCH�Ϸ���
    3.0 ��ǰUE������״̬�ȴ��л�UE״̬ */
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstMtRec->ucReSendTimes++;

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_RESEND,
                        pstMtRec->stResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND);

    /* ���С��30S�ж��Ƿ���Ҫ���ԣ��������30ֱ��ʧ�� ����IDLE ̬ */
    if (30 > pstMtRec->ucReSendTimes)
    {
        if (VOS_FALSE == pstMtRec->ulIsTlAckSndToCas)
        {
            if (VOS_OK != TAF_XSMS_SndCasTlAckAccordingCurUeState())
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_MtResend : TAF_XSMS_SndCasTlAckAccordingCurUeState ERR");

                TAF_XSMS_MtIdleInit();
            }
        }
        else
        {
            TAF_XSMS_INFO_LOG1("TAF_XSMS_MtResend:cur resendtimes is", (VOS_UINT32)pstMtRec->ucReSendTimes);
        }

    }
    else
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtResend : pstMtRec->ucReSendTimes > 30");

        TAF_XSMS_MtIdleInit();
    }

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvIncomingCall_MtIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ǿת��INCOMING CALL MSG */
    XCC_CSMS_INCOMING_CALL_IND_STRU    *pstIncomingCallIndMsg;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec =  TAF_XSMS_MtGetRecAddr();

    pstIncomingCallIndMsg = (XCC_CSMS_INCOMING_CALL_IND_STRU*)pstMsg;

    /* ����ǰ��·�����óɶ��ű������� */
    pstMtRec->ucIsMtCreatLink   = VOS_TRUE;

    /* �����ǰ����·ʱXSMS�������ñ�־λ */
    TAF_SDC_SetXsmsCallExistFlg(VOS_TRUE);

    /* ����INCOMING CALL �Ļظ� */
    TAF_XSMS_SndXccIncomingCallRsp(TAF_XSMS_SEND_XCC_CALL_ID_MT, 0, XCC_CSMS_RESULT_SUCC);

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvIncomingCall_MtIdle:IsAlertAnsByPass is ",
                      (VOS_UINT32)pstIncomingCallIndMsg->ucIsAlertAnsByPass);

    /* �ж��ǲ���BY PASS */
    if (VOS_TRUE == pstIncomingCallIndMsg->ucIsAlertAnsByPass)
    {
        /* �����BY PASS��������ʱ��ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND_MAX);

        /* ���õ�ǰMT״̬��Ϊ�ȴ�CONN IND */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_CALL_CONN_STATE);

    }
    else
    {
        /* �������BY PASS������ANSWER CALL REQ */
        TAF_XSMS_SndXccAnswerCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MT);

        /* ������ʱ��ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF_MAX);

        /* ���õ�ǰMT״̬��Ϊ�ȴ�CALL CNF */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_CALL_CNF_STATE);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvDataInd_MtIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstDataInd;

    pstDataInd = (TAF_XSMS_CAS_DATA_IND_MSG_STRU*)pstMsg;

    /* ����DATA_IND */
    TAF_XSMS_MtDealDataInd(pstDataInd);

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;
    XCC_CSMS_CALL_CONN_IND_STRU        *pstCallConnInd;

    pstMtRec       =  TAF_XSMS_MtGetRecAddr();

    pstCallConnInd = (XCC_CSMS_CALL_CONN_IND_STRU*)pstMsg;

    /* �ж�call id,�������MT���ŵģ�����ERR */
    if (TAF_XSMS_SEND_XCC_CALL_ID_MT != pstCallConnInd->ucCallId)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvCallConnCnf_MtWaitXccCallConnCnf:not mt CallId");
        return VOS_ERR;
    }

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND);

    /* ��ʶ��ǰ�ŵ���SMS������ */
    pstMtRec->ucIsSmsOrigChannel = VOS_TRUE;

    /* ����������ʱ�� */
    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND,
                        TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND_MAX);

    /* ���뵽�ȴ�SO_IND��״̬ */
    TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE);;

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvCallConnTimeout_MtWaitXccCallConnCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ʼ��MT��ص�ȫ�ֱ����Ͷ�ʱ��,��IDLE */
    TAF_XSMS_MtIdleInit();

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvSoInd_MtWaitXccSoInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_CSMS_SERVICE_CONNECT_IND_STRU  *pstSoIndMsg;

    pstSoIndMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU*)pstMsg;

    /* �ж�SO�Ƿ��Ƕ��ŵ� */
    if ((TAF_CDMA_SO_6_SMS == pstSoIndMsg->enSo)
        || (TAF_CDMA_SO_14_RS2_SMS == pstSoIndMsg->enSo))
    {
        TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvSoInd_MtWaitXccSoInd:SO is ", (VOS_UINT32)pstSoIndMsg->enSo);

        /* ����Ƕ���SO,ͣ����ʱ�� */
        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND);

        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND_MAX);

        /* ���õ�ǰ״̬Ϊ�ȴ�DATA_IND */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE);

        return VOS_OK;
    }
    else
    {
        /* ������Ƕ��ŵ�SO,�����ȴ� */
        return VOS_ERR;
    }
}
VOS_UINT32 TAF_XSMS_RcvSoIndTimeout_MtWaitXccSoInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ŵ� */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_CSMS_ANSWER_CALL_CNF_STRU      *pstCallCnf;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstCallCnf = (XCC_CSMS_ANSWER_CALL_CNF_STRU*)pstMsg;

    /* �ж�call id,�������MT���ŵģ�����ERR */
    if (TAF_XSMS_SEND_XCC_CALL_ID_MT != pstCallCnf->ucCallId)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvAnsCallCnf_MtWaitXccAnsCallCnf:not mt CallId");

        return VOS_ERR;
    }

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF);

    /* �ж��ǲ��Ǵ���OK */
    if (TAF_XCC_CAUSE_SUCCESS == pstCallCnf->enRslt)
    {
        /* �϶��Ƕ��Ž���,����ȫ�ֱ��� */
        pstMtRec->ucIsSmsOrigChannel = VOS_TRUE;

        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND_MAX);

        /* ���뵽�ȴ�SO_IND��״̬ */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_SO_IND_STATE);
    }
    else if (TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH == pstCallCnf->enRslt)
    {
        /* ������Ѿ�������·������Ҫ��SO��ֱ�ӵ�DATA IND */
        pstMtRec->ucIsSmsOrigChannel = VOS_FALSE;
        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND,
                            TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND_MAX);

        /* ���õ�ǰ״̬Ϊ�ȴ�DATA_IND */
        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_DSCH_DATA_IND_STATE);
    }
    else
    {
        /* ���� */
        TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);
    }

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvAnsCallCnfTimeout_MtWaitXccAnsCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ŵ� */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvDschDataInd_MtWaitCasDschDataInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstDschData;

    pstDschData = (TAF_XSMS_CAS_DATA_IND_MSG_STRU*)pstMsg;

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_DATA_IND);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_CNF);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CONN_IND);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_XCC_SO_IND);

    /* ����DATA_IND */
    TAF_XSMS_MtDealDataInd(pstDschData);

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvDschDataIndTimeout_MtWaitCasDschDataInd
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���ŵ��ص�MT_IDLE״̬ */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_UPDATEFILE_CNF_STRU           *pstWriteUimCnf;

    pstWriteUimCnf = (USIMM_UPDATEFILE_CNF_STRU*)pstMsg;

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_WRITE_UIM_CNF);

    if (VOS_OK == pstWriteUimCnf->stCmdResult.ulResult)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf:write uim is ok");

        /* д������ɹ�����ȡ��index��PRL���� */
        if (VOS_OK == TAF_XSMS_PrlReadReq(pstWriteUimCnf->ucRecordNum))
        {
            TAF_XSMS_INFO_LOG("TAF_XSMS_RcvWriteUimCnf_MtWaitWriteUimCnf:read uim req is ok");

            /* ��ʱ��������TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE״̬ */
            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF,
                                TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF_MAX);

            TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_UIM_READ_CNF_STATE);

            return VOS_OK;
        }
    }

    /* д��ʧ�ܻ��߶�������ʧ�ܣ��������ظ�Я��CAUSE_CODE��TL ACK */
    TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

    return VOS_ERR;
}


VOS_UINT32 TAF_XSMS_RcvWriteUimCnfTimeout_MtWaitWriteUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* д��ʧ�ܣ��������ظ�Я��CAUSE_CODE��TL ACK */
    TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    USIMM_READFILE_CNF_STRU            *pstReadUimCnf;
    VOS_UINT8                           aucData[TAF_XSMS_CAS_DATA_IND_MAX_LEN];
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTransportMessage;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstReadUimCnf = (USIMM_READFILE_CNF_STRU *)pstMsg;

    /* ֹͣ��ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_READ_UIM_CNF);

    if ( VOS_OK == pstReadUimCnf->stCmdResult.ulResult)
    {
        /* ��ȡ�����϶������� */
        PS_MEM_SET(aucData, 0, sizeof(aucData));
        PS_MEM_CPY(aucData, (pstReadUimCnf->aucEf + 2), (pstReadUimCnf->usEfLen - 2));

        PS_MEM_SET(&stTransportMessage, 0, sizeof(TAF_XSMS_TRANSPORT_MESSAGE_STRU));

        /*���ñ���ӿ�ת�����ϱ��Ľṹ�� */
        TAF_XSMS_DecodeTLRawToTLStru((VOS_UINT8)(pstReadUimCnf->usEfLen - 2), aucData, &stTransportMessage);

        /* �ϱ�AP�յ�һ���¶��� */
        TAF_XSMS_MsgDeliveryInd(&stTransportMessage.stMessage);

        /* �������ظ�TL ACK */
        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                             pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);

        return VOS_OK;
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvReadUimCnf_MtWaitReadUimCnf:read uim is error");

        /* ����ʧ�ܣ��������ظ�Я��CAUSE_CODE��TL ACK */
        TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

        return VOS_ERR;
    }

}


VOS_UINT32 TAF_XSMS_RcvReadUimCnfTimeout_MtWaitReadUimCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ʧ�ܣ��������ظ�Я��CAUSE_CODE��TL ACK */
    TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_DESTINATION_BUSY, TAF_XSMS_TL_CAUSECODE_TMP);

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU     *pstDschDataCnf;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec =  TAF_XSMS_MtGetRecAddr();

    /* ֹͣ��ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF);

    pstDschDataCnf = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pstDschDataCnf->enRslt)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf: dsch cnf succ");

        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_RESEND);

        /* ��ʼ��ȫ�ֱ�����״̬��,��IDLE */
        TAF_XSMS_MtIdleInit();

    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvDschDataCnf_MtWaitCasDataCnf: dsch cnf failed");
    }

    /* ���õ�ǰ��SND FLAG ΪFALSE �ط���ʱ����ʱ֮���� */
    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    return VOS_OK;

}
VOS_UINT32 TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CAS_CNAS_1X_CSCH_DATA_CNF_STRU     *pstCschDataCnf;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec =  TAF_XSMS_MtGetRecAddr();

    /* ֹͣ��ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF);

    pstCschDataCnf = (CAS_CNAS_1X_CSCH_DATA_CNF_STRU *)pstMsg;

    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == pstCschDataCnf->enRslt)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf: CSCH cnf succ");

        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_RESEND);

        /* ��ʼ��ȫ�ֱ�����״̬��,��IDLE */
        TAF_XSMS_MtIdleInit();
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvCschDataCnf_MtWaitCasDataCnf: CSCH cnf failed");
    }

    /* ���õ�ǰ��SND FLAG ΪFALSE �ط���ʱ����ʱ֮���� */
    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvCasCnfTimeout_MtWaitCasDataCnf : Wait cnf time out");

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvEndCallCnf_MtWaitEndCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END);

    /* ���۳ɹ�ʧ�ܣ����ص�MT_IDLE״,��ʼ��ȫ�ֱ�����״̬�� */
    TAF_XSMS_MtIdleInit();

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvEndCallCnfTimeout_MtWaitEndCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ʱ�����MT_IDLE״̬,��ʼ��ȫ�ֱ�����״̬�� */
    TAF_XSMS_MtIdleInit();

    return VOS_OK;
}
VOS_VOID TAF_XSMS_MtEndcallReq(VOS_UINT8 enEndReason)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;
    /* Deleted by h00313353 for Pc Lint, 2015-3-30 */
    /* Deleted by h00313353 for Pc Lint, 2015-3-30 */

    pstMtRec      = TAF_XSMS_MtGetRecAddr();
    /* Deleted by h00313353 for Pc Lint, 2015-3-30 */
    /* Deleted by h00313353 for Pc Lint, 2015-3-30 */

    /* �����MT SMS�������ŵ�����XCC���Ͳ��ŵ����� */
    if (VOS_TRUE == pstMtRec->ucIsSmsOrigChannel)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_MtEndcallReq:MO is IDLE, EndCall");

        TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MT, enEndReason);

        /* ��ʱ��������MT_WAITING_XCC_DISCONNECT_STATE״̬ */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END,
                            TI_TAF_XSMS_TIMER_MT_WAIT_CALL_END_MAX);

        TAF_XSMS_MtSetCurrFsmState(TAF_XSMS_MT_WAITING_XCC_DISCONNECT_STATE);
    }
    else
    {
        /* ��ʼ��ȫ�ֱ�����״̬��,��IDLE */
        TAF_XSMS_MtIdleInit();
    }

    return;
}
VOS_UINT32 TAF_XSMS_RcvMtLinkAbort
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���� */
    TAF_XSMS_MtEndcallReq(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_MtAgpsSmsHandle(
    TAF_XSMS_MESSAGE_STRU              *pstMessage
)
{

    VOS_UINT16                          usUserDataStartByte = 0;
    VOS_UINT16                          usUserDataLen       = 0;
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;

    PS_MEM_SET(&stUserData, 0, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    /* ����USER DATA */
    TAF_XSMS_DecodeUserDataInBearerData(pstMessage->ulBearerDataLen,
                                        pstMessage->aucBearerData,
                                        &usUserDataStartByte,
                                        &usUserDataLen,
                                        &stUserData);

    /* �������8BIT OCTET�п�����Ҫת�� */
    if (TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET != stUserData.enMsgCodeType)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MtAgpsSmsHandle : TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET != enMsgCodeType");
        return VOS_ERR;
    }

    /* ���������ݷ��ͽoMTA */
    TAF_XSMS_SendXpdsGpsSms(&pstMessage->stAddr,
                            stUserData.ucNumFields,
                            stUserData.aucUserData);

    return VOS_OK;

}
VOS_VOID TAF_XSMS_MtDealCatptMsgProc(TAF_XSMS_CAS_DATA_IND_MSG_STRU *pstDataInd)
{
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;
    VOS_UINT8                           ucIndex = 0;
    VOS_UINT8                           ucIsUimPPDownloadEnable;
    VOS_UINT8                           ucIsCsimPPDownloadEnable;
    pstMtRec = TAF_XSMS_MtGetRecAddr();

    ucIsUimPPDownloadEnable     = (VOS_UINT8)USIMM_IsServiceAvailable(UIM_SVR_SMS_PP_DOWNOLAD);
    ucIsCsimPPDownloadEnable    = (VOS_UINT8)USIMM_IsServiceAvailable(CSIM_SVR_SMSPP_DOWNLOAD);

    if ((PS_USIM_SERVICE_AVAILIABLE  == ucIsUimPPDownloadEnable)
     || (PS_USIM_SERVICE_AVAILIABLE  == ucIsCsimPPDownloadEnable))
    {
        /* �ϱ���STK */
        TAF_XSMS_SendStkCATPTMsg(pstDataInd->ucLen,
                                 pstDataInd->aucMsg,
                                 &pstMtRec->stTLP2PMsg.stMessage);

        /* �ظ�TL_ACK */
        TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                         pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
    }
    else
    {
        /* ֱ��DOWNLOAD ��USIM�� */
        if ((VOS_OK != TAF_XSMS_FindFreeIndex(&ucIndex))
        || ((TAF_XSMS_RECORD_LEN_MAX - 2)    < pstDataInd->ucLen))
        {
            /* �ظ�TL_ACK */
            TAF_XSMS_MtDealTlAck(TAF_XSMS_TL_UNEXPECTED_PARM_SIZE,
                                 TAF_XSMS_TL_CAUSECODE_TMP);
        }
        else
        {
            /* д������ */
            TAF_XSMS_CommonFileWriteReq(pstDataInd->ucLen,
                                        pstDataInd->aucMsg,
                                        ucIndex);

            /* �ظ�TL_ACK */
            TAF_XSMS_MtDealTlAck(pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode,
                         pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass);
        }

    }

    return;
}


VOS_UINT32 TAF_XSMS_RcvMtLinkAbort_MtWaitCasCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �յ�ABORT֮��,��CAS ȷ��û��CNF�ظ������DATA_REQ�Ѿ����͵�FLAG
    �ȴ��ط���ʱ����ʱ֮���ж��ܷ��ط� */
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_EncodeTlAckInMtRec
(
    TAF_XSMS_TL_CAUSE_CODE_ENUM8        enCauseCode,
    TAF_XSMS_TL_ERROR_CLASS_ENUM8       enErrorClass
)
{
    VOS_UINT32                          ulEncodedResult;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstMtRec = TAF_XSMS_MtGetRecAddr();

    /* ��causecode��errorclass����ȫ�ֱ��� */
    pstMtRec->stTLP2PMsg.stCauseCode.enCauseCode  = enCauseCode;
    pstMtRec->stTLP2PMsg.stCauseCode.enErrorClass = enErrorClass;

    /* ��������ACK�� SEQ NUM  */
    pstMtRec->stTLP2PMsg.stCauseCode.ucReplySeq     = pstMtRec->stTLP2PMsg.ucBearReplySeqNum;

    TAF_XSMS_INFO_LOG1(" Send TL_ACK the seq num is ", pstMtRec->stTLP2PMsg.ucBearReplySeqNum);

    TAF_XSMS_HookSmsTlAck(TAF_XSMS_HOOK_MSG_TYPE_SND_TL_ACK, &pstMtRec->stTLP2PMsg.stCauseCode);

    /* ͨ��������TL ACK DBM�ṹ�� */
    ulEncodedResult = TAF_XSMS_GetAckDBMStru(&pstMtRec->stTLP2PMsg.stMessage.stAddr,
                                             &pstMtRec->stTLP2PMsg.stCauseCode,
                                             &pstMtRec->stDbm);

    if (VOS_OK != ulEncodedResult)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_EncodeTlAckInMtRec:TAF_XSMS_GetAckDBMStru error");

        /* ����ʧ�� */
        return VOS_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 TAF_XSMS_SndCasTlAckAccordingCurUeState
(
    VOS_VOID
)
{
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8     enCurUeStatus;
    TAF_XSMS_MSG_MT_REC_STRU                *pstMtRec;
    VOS_UINT8                                aucData[3] = {0};

    pstMtRec =  TAF_XSMS_MtGetRecAddr();

    enCurUeStatus = TAF_SDC_GetCdmaCurUeState();

    TAF_XSMS_INFO_LOG1("TAF_XSMS_SndCasTlAckAccordingCurUeState: enCurUeStatus",enCurUeStatus);

    PS_MEM_SET(aucData, 0, 3);

    if (CAS_CNAS_1X_CAS_IDLE_STATE == enCurUeStatus)
    {
        /* Access channel����ҪЯ����Ȩ��Ϣ */
        TAF_XSMS_EncodeAuth(&pstMtRec->stTLP2PMsg.stMessage.stAddr, aucData);

        if (VOS_OK != TAF_XSMS_SndCasCschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT,
                                                 aucData,
                                                 &pstMtRec->stDbm))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasTlAckAccordingCurUeState:TAF_XSMS_SndCasCschDataReq ERR");
            return VOS_ERR;
        }

        pstMtRec->ulIsTlAckSndToCas = VOS_TRUE;

        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_CSCH_CNF_MAX);
    }
    else if (CAS_CNAS_1X_CAS_TCH_STATE == enCurUeStatus)
    {
        /* Traffic channel */
        if(VOS_OK != TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MT, &pstMtRec->stDbm))
        {

            TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasTlAckAccordingCurUeState:TAF_XSMS_SndCasDschDataReq ERR");
            return VOS_ERR;
        }

        pstMtRec->ulIsTlAckSndToCas = VOS_TRUE;

        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MT_WAIT_DSCH_CNF_MAX);
    }
    else
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_SndCasTlAckAccordingCurUeState: enCurUeStatus is not idle or tch");
        pstMtRec->ulIsTlAckSndToCas = VOS_FALSE;
    }

    /* �Ѿ�����TL ACK�����õ�ǰ״̬Ϊ�ȴ�AS CNF */
    TAF_XSMS_MtSetCurrFsmState(TI_TAF_XSMS_TIMER_MT_WAIT_AS_CNF);

    return VOS_OK;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

