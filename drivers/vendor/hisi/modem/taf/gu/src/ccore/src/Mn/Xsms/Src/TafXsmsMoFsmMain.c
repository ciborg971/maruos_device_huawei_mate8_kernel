

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "PsLogdef.h"
#include  "TafXsmsSndAt.h"
#include  "TafXsmsTimer.h"
#include  "TafXsmsDecode.h"
#include  "TafXsmsEncode.h"
#include  "TafXsmsSndXcc.h"
#include  "TafXsmsSndCas.h"
#include  "TafXsmsMsgProc.h"
#include  "TafXsmsUimProc.h"
#include  "TafXsmsMoFsmMain.h"
#include  "TafXsmsMoFsmMainTbl.h"
#include  "MmaXsmsInterface.h"
#include  "cas_1x_control_main_nas_pif.h"
#include  "TafXpdsXsmsInterface.h"

#include  "TafSdcCtx.h"




#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XSMS_MO_FSM_MAIN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/



VOS_UINT32 TAF_XSMS_MoFsmMainProc(MsgBlock *pstMsg)
{
    VOS_UINT32                          ulEventType;
    VOS_UINT32                          ulRet           = VOS_ERR;
    TAF_XSMS_MO_FSM_ID_ENUM_UINT32      enCurState;
    VOS_UINT16                          usTemp;
    TAF_ACTION_FUNC                     pActFun;
    REL_TIMER_MSG                      *pstRelTimerMsg;

    enCurState = TAF_XSMS_MoGetCurrFsmId();

    TAF_XSMS_MsgHook(TAF_XSMS_HOOK_MSG_TYPE_MO_FSM, (VOS_UINT8*)&enCurState, sizeof(TAF_XSMS_MO_FSM_ID_ENUM_UINT32));

    if (VOS_PID_TIMER == pstMsg->ulSenderPid)
    {
        pstRelTimerMsg = (REL_TIMER_MSG*)pstMsg;
        /* �ж��ǲ��� ��MO_IDLE״̬ ��ʱ */
        if ((TI_TAF_XSMS_TIMER_MO_IDLE == pstRelTimerMsg->ulName)
            && (TAF_XSMS_MO_IDLE_STATE != enCurState))
        {
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);

            TAF_XSMS_MoIdleInit();

            TAF_XSMS_ERROR_LOG("TAF_XSMS_MoFsmMainProc: MO_IDLE timeOut");

            return VOS_ERR;
        }
        else
        {
            ulEventType = TAF_BuildEventType(VOS_PID_TIMER, pstRelTimerMsg->ulName);
        }
    }
    else
    {
        /* ��Ҫ�жϴ�С�� */
        PS_MEM_CPY(&usTemp, pstMsg->aucValue, 2);

        ulEventType = TAF_BuildEventType(pstMsg->ulSenderPid, usTemp);
    }

    TAF_XSMS_INFO_LOG1("TAF_XSMS_MoFsmMainProc:Current Status is ", (VOS_INT32)enCurState);
    TAF_XSMS_INFO_LOG1("TAF_XSMS_MoFsmMainProc:Event Type is ", (VOS_INT32)ulEventType);

    /* ����״̬ת�Ʊ��е���Ӧ�Ķ��������� */
    pActFun = TAF_FSM_FindAct(&g_stTafXsmsMoFsmDesc, enCurState, ulEventType);

    if (VOS_NULL_PTR != pActFun)
    {
        /* ������ص��¼���������Ϊ��,�����������¼����� */
        ulRet = (*pActFun)(ulEventType, (struct MsgCB*)pstMsg);

        return ulRet;
    }

    TAF_XSMS_WARNING_LOG("TAF_XSMS_MoFsmMainProc:TAF_FSM_FindAct return null ptr ");

    return VOS_ERR;
}



VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnDschProc(VOS_VOID)
{
    TAF_XSMS_INFO_LOG("TAF_XSMS_MoIdleRcvAtSendReqOnDschProc: first time to link");

    TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnCschProc(VOS_VOID)
{
    TAF_XSMS_SndCasCschReq_MoWaitCasCnf();

    return VOS_OK;
}

VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqOnDschOrCschProc(TAF_XSMS_MSG_MO_REC_STRU *pstRecAddr)
{
#if 0
    if (/* ��ǰ״̬��IDLE״̬ */)
    {
        pstRecAddr->enActiveSndChannel = TAF_XSMS_ACTIVE_CSCH;
        TAF_XSMS_MoIdleRcvAtSendReqOnCschProc();
    }
    else
    {
        pstRecAddr->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;
        TAF_XSMS_MoIdleRcvAtSendReqOnDschProc();
    }
#endif
    pstRecAddr->enActiveSndChannel = TAF_XSMS_ACTIVE_CSCH;

    TAF_XSMS_MoIdleRcvAtSendReqOnCschProc();

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(TAF_XSMS_MSG_MO_REC_STRU *pstMoRec)
{
    VOS_UINT32                          ulRslt;

    /* ��ǰ��������ר���ŵ� */
    if (TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN == pstMoRec->stNvResend.enXsmsChannelOption)
    {
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnDschProc();
    }
    /* ��ǰ�������߹����ŵ� */
    else if (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN == pstMoRec->stNvResend.enXsmsChannelOption)
    {
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_CSCH;
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnCschProc();
    }
    /* ��ǰ�������������ŵ������� */
    else if (TAF_XSMS_DATA_REQ_SEND_CHAN_BOTH == pstMoRec->stNvResend.enXsmsChannelOption)
    {
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnDschOrCschProc(pstMoRec);
    }
    else
    {
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;
        ulRslt = TAF_XSMS_MoIdleRcvAtSendReqOnDschProc();
    }

    /* �ж������ǰ״̬�ı� ֱ��������MO_IDLE״̬������ʱ�� */
    if (VOS_OK == ulRslt)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_IDLE,
                            TI_TAF_XSMS_TIMER_MO_IDLE_MAX);
    }
    return ulRslt;
}


VOS_VOID TAF_XSMS_MoIncreaseMessageId(VOS_VOID)
{
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfoAddr;
    VOS_UINT8                           aucMsgId[sizeof(VOS_UINT16)];
    VOS_UINT16                          usMsgId;

    pstInitCtrlInfoAddr = TAF_XSMS_GetInitCtrlInfoAddr();

    /* ��MSG��1��д��UIM���ڣ����ȴ�UIM��CNF��Ϣ����ʹʧ��Ҳ��Ӱ�����Ķ��ŷ��� */
    pstInitCtrlInfoAddr->usMessageId++;

    usMsgId = pstInitCtrlInfoAddr->usMessageId;

    aucMsgId[0] = (usMsgId >> 8) & 0xFF;
    aucMsgId[1] = usMsgId & 0xFF;

    TAF_XSMS_MsgIdUpdataReq(aucMsgId);

    return;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_RcvAtSendReqProc_MoIdle
 ��������  : MO Idle״̬���յ�AT�·���AT����Ͷ��ŵĴ�������
 �������  : ulEventType:�¼�����(��Sendpid��msg type���)
             pstMsg:AT����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvAtSendReqProc_MoIdle(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{

    VOS_UINT32                          ulState;
    TAF_XSMS_SEND_MSG_REQ_STRU         *pstAtMsg;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    VOS_UINT8                           ucReqSeq = 0;

    USIMM_FdnQuery(&ulState);


    if (USIMM_FDNSTATUS_OFF == ulState)
    {
        pstAtMsg    = (TAF_XSMS_SEND_MSG_REQ_STRU *)pstMsg;

        /* MO ��¼ȫ�ֱ��� */
        pstMoRec    = TAF_XSMS_MoGetRecAddr();
        pstDbm      = &(pstMoRec->stDbm);

        /* INIT CTRL ��¼ȫ�ֱ��� */
        pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

        /* ��AT�·���STRU���浽ȫ�ֱ�����(FDN,CC���ܻ���) */
        PS_MEM_CPY(&pstMoRec->st1xSms, &pstAtMsg->st1XSms, sizeof(TAF_XSMS_MESSAGE_STRU));

        pstMoRec->enOrigPid         = TAF_XSMS_AT_SEND_XSMS;
        pstMoRec->usIsStkUserAck    = VOS_FALSE;

        /* �����ڵ�MSG_IDд��MO_RECȫ�ֱ����� */
        pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;
        ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);

        /* ��AT�·�������ת����DBM����ȫ�ֱ����� */
        if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&pstAtMsg->st1XSms,
                                               pstMoRec->usMessageId,
                                               ucReqSeq,
                                               TAF_XSMS_STATUS_STO_UNSEND,
                                               pstDbm,
                                               VOS_TRUE))
        {
            /* ����MO_IDLE */
            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

            return VOS_ERR;
        }

        TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &pstAtMsg->st1XSms);

        /* ��MSG_IDд�ؿ��� (��Ҫ��������ʱ��д���ǵȵ�TL_ACK��д) */
        TAF_XSMS_MoIncreaseMessageId();

        return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);
    }
    else
    {
        /* ��FDN�Ĵ��� */
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_RcvStkSendReqProc_MoIdle
 ��������  : MO Idle״̬���յ�STK�·���AT����Ͷ��ŵĴ�������
 �������  : ulEventType:�¼�����(��Sendpid��msg type���)
             pstMsg:STK����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvStkSendReqProc_MoIdle(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{

    VOS_UINT32                          ulState;
    STK_XSMS_SEND_SMS_REQ_STRU         *pstStkSendMsg;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    VOS_UINT8                           ucReqSeq = 0;

    USIMM_FdnQuery(&ulState);


    if (USIMM_FDNSTATUS_OFF == ulState)
    {
        pstStkSendMsg    = (STK_XSMS_SEND_SMS_REQ_STRU *)pstMsg;

        /* MO ��¼ȫ�ֱ��� */
        pstMoRec    = TAF_XSMS_MoGetRecAddr();
        pstDbm      = &(pstMoRec->stDbm);

        /* INIT CTRL ��¼ȫ�ֱ��� */
        pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

        /* ��STK�·���STRU���浽ȫ�ֱ�����(FDN,CC���ܻ���) */
        PS_MEM_CPY(&pstMoRec->st1xSms, &pstStkSendMsg->st1XSms, sizeof(TAF_XSMS_MESSAGE_STRU));

        pstMoRec->enOrigPid         = TAF_XSMS_STK_SEND_XSMS;
        pstMoRec->usIsStkUserAck    = (VOS_UINT16)pstStkSendMsg->ulIsUserAck;

        /* �����ڵ�MSG_IDд��MO_RECȫ�ֱ����� */
        pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;

        /* ��STK�·�������ת����DBM����ȫ�ֱ����� */
        if (VOS_TRUE != pstMoRec->usIsStkUserAck)
        {
            ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);
            if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&pstStkSendMsg->st1XSms,
                                                   pstMoRec->usMessageId,
                                                   ucReqSeq,
                                                   TAF_XSMS_STATUS_STO_UNSEND,
                                                   pstDbm,
                                                   VOS_TRUE))
            {
                /* ����MO_IDLE */
                TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

                return VOS_ERR;
            }
        }
        else
        {
            if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&pstStkSendMsg->st1XSms,
                                                   pstMoRec->usMessageId,
                                                   0,
                                                   TAF_XSMS_STATUS_STO_UNSEND,
                                                   pstDbm,
                                                   VOS_FALSE))
            {
                /* ����MO_IDLE */
                TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

                return VOS_ERR;
            }

        }
        TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &pstStkSendMsg->st1XSms);

        /* ��MSG_IDд�ؿ��� (��Ҫ��������ʱ��д���ǵȵ�TL_ACK��д) */
        TAF_XSMS_MoIncreaseMessageId();

        return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);
    }
    else
    {
        /* ��FDN�Ĵ��� */
    }

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_EncodeXsmsMsgBearDataByContext
 ��������  : MO Idle״̬���յ�MTA�·�������Ͷ��ŵĴ�������
 �������  : ulEventType:�¼�����(��Sendpid��msg type���)
             pstMsg:MTA����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_EncodeXsmsMsgBearDataByContext
(
    VOS_UINT8                          *pucData,
    VOS_UINT16                          usDataLen,
    TAF_XSMS_MESSAGE_STRU              *pstXsmsMsg
)
{
    TAF_XSMS_BD_MSG_USER_DATA_STRU      stUserData;
    VOS_UINT8                           aucEncodedData[256] = {0};
    VOS_UINT8                           ucEncodeDataLen     = 0;
    TAF_XSMS_MSG_ID_STRU                stMsgId;

    /* ��׼��MSG_ID �ṹ�� */
    stMsgId.enMsgType           = TAF_XSMS_BD_MSG_TYPE_SUBMIT;
    stMsgId.ucIsHeadIndExist    = VOS_FALSE;
    stMsgId.usMsgID             = 0;

    /* ��ɱ�׼USER DATA �ṹ */
    PS_MEM_SET(&stUserData, 0, sizeof(TAF_XSMS_BD_MSG_USER_DATA_STRU));

    stUserData.enMsgCodeType = TAF_XSMS_USER_DATA_MSG_ENCODE_OCTET;

    if (TAF_XSMS_BD_PURE_CONTEXT_MAX_LEN_8 < usDataLen)
    {
        return VOS_ERR;
    }

    stUserData.ucNumFields  = (VOS_UINT8)usDataLen;

    PS_MEM_CPY(stUserData.aucUserData, pucData, usDataLen);

    /* ����BEAR DATA */
    /* ����MSG ID */
    TAF_XSMS_EncodeMsgID(&stMsgId,
                         &ucEncodeDataLen,
                         aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
                         aucEncodedData,
                         ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    /* ����USER DATA */
    TAF_XSMS_EncodeUserData(&stUserData,
                            &ucEncodeDataLen,
                            aucEncodedData);

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
                         aucEncodedData,
                         ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    /* ����LANGUAGE INDICATOR */
    aucEncodedData[0] = TAF_XSMS_BD_LANGUAGE_INDICATOR;
    aucEncodedData[1] = 1;
    aucEncodedData[2] = TAF_XSMS_BD_LANGUAGE_INDICATOR_ENGLISH;

    ucEncodeDataLen   = 3;

    PS_MEM_CPY(pstXsmsMsg->aucBearerData + pstXsmsMsg->ulBearerDataLen,
                         aucEncodedData,
                         ucEncodeDataLen);

    pstXsmsMsg->ulBearerDataLen += ucEncodeDataLen;

    return VOS_OK;

}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_RcvXpdsSendReqProc_MoIdle
 ��������  : MO Idle״̬���յ�MTA�·�������Ͷ��ŵĴ�������
 �������  : ulEventType:�¼�����(��Sendpid��msg type���)
             pstMsg:MTA����Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXpdsSendReqProc_MoIdle
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XSMS_SEND_REQ_STRU        *pstSendReq;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_INIT_CTRL_INFO_STRU       *pstInitCtrlInfo;
    TAF_XSMS_MESSAGE_STRU               stXsmsMsg;
    TAF_XSMS_DATA_BURST_MSG_STRU       *pstDbm;
    VOS_UINT8                           ucReqSeq = 0;

    pstSendReq  = (TAF_XPDS_XSMS_SEND_REQ_STRU*)pstMsg;

    PS_MEM_SET(&stXsmsMsg, 0, sizeof(stXsmsMsg));

    /* MO ��¼ȫ�ֱ��� */
    pstMoRec    = TAF_XSMS_MoGetRecAddr();
    pstDbm      = &(pstMoRec->stDbm);

    /* INIT CTRL ��¼ȫ�ֱ��� */
    pstInitCtrlInfo = TAF_XSMS_GetInitCtrlInfoAddr();

    /* ��MTA��Ϣת���ɱ�׼�Ķ��Žṹ�� */
    PS_MEM_CPY(&stXsmsMsg.stAddr,
               &pstSendReq->stXsmsAddr,
               sizeof(TAF_XSMS_ADDR_STRU));

    if (VOS_ERR == TAF_XSMS_EncodeXsmsMsgBearDataByContext(pstSendReq->aucData,
                                                           pstSendReq->usDataLen,
                                                          &stXsmsMsg))
    {
        return VOS_ERR;
    }

    /* ��STK�·���STRU���浽ȫ�ֱ�����(FDN,CC���ܻ���) */
    PS_MEM_CPY(&pstMoRec->st1xSms, &stXsmsMsg, sizeof(TAF_XSMS_MESSAGE_STRU));

    pstMoRec->enOrigPid         = TAF_XSMS_XPDS_SEND_XSMS;
    pstMoRec->usIsStkUserAck    = VOS_FALSE;

    /* �����ڵ�MSG_IDд��MO_RECȫ�ֱ����� */
    pstMoRec->usMessageId = pstInitCtrlInfo->usMessageId;

    ucReqSeq              = TAF_XSMS_MoGetBearSeqNum(pstMoRec);
    /* ��MTA�·�������ת����DBM����ȫ�ֱ����� */
    if  (VOS_OK != TAF_XSMS_GetP2PDBMStru(&stXsmsMsg,
                                           pstMoRec->usMessageId,
                                           ucReqSeq,
                                           TAF_XSMS_STATUS_STO_UNSEND,
                                           pstDbm,
                                           VOS_TRUE))
    {
        /* ����MO_IDLE */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvAtSendReqProc_MoIdle: TAF_XSMS_GetP2PDBMStru fail");

        return VOS_ERR;
    }

    TAF_XSMS_HookSmsContect(TAF_XSMS_HOOK_MSG_TYPE_SND_SMS, ucReqSeq, &stXsmsMsg);

    /* ��MSG_IDд�ؿ��� (��Ҫ��������ʱ��д���ǵȵ�TL_ACK��д) */
    TAF_XSMS_MoIncreaseMessageId();

    return TAF_XSMS_MoIdleRcvAtSendReqDispatchProc(pstMoRec);


}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_RcvXccOrgiCallCnfRedialCheck
 ��������  : ����XCC�ϱ���ԭ��ֵ�ж��Ƿ���Ҫ�ذ�
 �������  : enRslt:XCC�ϱ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_TRUE/VOS_FALSE
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : H00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XSMS_RcvXccOrgiCallCnfRedialCheck(TAF_XCC_CAUSE_ENUM_UINT32 enRslt)
{
    switch (enRslt)
    {
        /* ��Ҫ�ذε�ԭ��ֵ */
        case TAF_XCC_CAUSE_NO_SERVICE:
        case TAF_XCC_CAUSE_MAX_ACCESS_PROBES:
        case TAF_XCC_CAUSE_REORDER:
        case TAF_XCC_CAUSE_ACCESS_DENYIED:
        case TAF_XCC_CAUSE_ACCT_BLOCK:
        case TAF_XCC_CAUSE_NDSS:
        case TAF_XCC_CAUSE_REDIRECTION:
        case TAF_XCC_CAUSE_ACCESS_IN_PROGRESS:
        case TAF_XCC_CAUSE_ACCESS_FAIL:
        case TAF_XCC_CAUSE_ABORT:
        case TAF_XCC_CAUSE_SIGNAL_FADE:
        case TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT:
        case TAF_XCC_CAUSE_CCS_NOT_SUPPORT:
        case TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL:
        case TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL:
        case TAF_XCC_CAUSE_SO_REJ:

            return VOS_TRUE;
        default:

        /* no matter what reason just try to relink */
            return VOS_TRUE;
    }
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_RcvXccOrigCallCnfRedialProc
 ��������  : ����XCC�ϱ���ԭ��ֵ�ж��Ƿ���Ҫ�ذεĴ���
 �������  : pstMoRec:MO����������Ϣ
             pstXccSmsOrigCallCnf:XCC�ϱ�����Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��12��30��
    ��    ��   : H00300778
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XSMS_RcvXccOrigCallCnfRedialProc(
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec,
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU    *pstXccSmsOrigCallCnf)
{
    if (VOS_TRUE == TAF_XSMS_RcvXccOrgiCallCnfRedialCheck(pstXccSmsOrigCallCnf->enRslt))
    {
        if (pstMoRec->stNvResend.ucResendMax > pstMoRec->ucResendTimes)
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnfRedialProc:Remain times left, retry");

            /* ���ò�2�����ʶ
            1.0 ����˴���L2���� �ϴ�Ҳ��L2 ֱ�Ӽ�1
            2.0 ����˴���L2���� �ϴβ���L2 ����������1
            3.0 ����˴β���L2���� �ϴβ���L2 ���������1
            4.0 ����˴β���L2���� �ϴ���L2 ����������1*/
            if (TAF_XCC_FAIL_LAYER_L2 == pstXccSmsOrigCallCnf->enIsL2Err)
            {
                pstMoRec->ucIsL2ErrReOrig   = VOS_TRUE;
                pstMoRec->enLastErrType     = TAF_XCC_FAIL_LAYER_L2;
                if (TAF_XCC_FAIL_LAYER_L3 != pstMoRec->enLastErrType)
                {
                    pstMoRec->ucL2ErrReOrigCount++;
                }
                else
                {
                    pstMoRec->ucL2ErrReOrigCount = 1;
                }
            }
            else
            {
                pstMoRec->ucIsL2ErrReOrig   = VOS_FALSE;
                pstMoRec->enLastErrType     = TAF_XCC_FAIL_LAYER_L3;
                if (TAF_XCC_FAIL_LAYER_L2 != pstMoRec->enLastErrType)
                {
                    pstMoRec->ucL2ErrReOrigCount++;
                }
                else
                {
                    pstMoRec->ucL2ErrReOrigCount = 1;
                }

            }
            /* ������Ϊʲôԭ��ʧ�ܣ����ڵȴ�OHM֮�����½���������5�붨ʱ����ʱ֮���� */
            pstMoRec->ucWaitRedirCompleteFlag = VOS_TRUE;

            /* ����������ʱ�������ı䵱ǰ״̬(�ȴ�XCC_CNF) */
            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                                pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND);

        }
        /* ���Դ������޲��ٳ��ԣ�����IDLE״̬ */
        else
        {
            TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnfRedialProc:No times left,return MO Idle");

            /* �ϱ�AT����ʧ�� */
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

            /* ����,��ʼ��ȫ�ֱ��� */
            TAF_XSMS_MoIdleInit();
        }
    }
    else
    {
        TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnfRedialProc:No need retry");

        /* �ϱ�AT����ʧ�� */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        /* ������ʼ��ȫ�ֱ��� */
        TAF_XSMS_MoIdleInit();
    }

    return;
}
VOS_UINT32 TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    XCC_CSMS_ORIG_SMS_CALL_CNF_STRU    *pstXccSmsOrigCallCnf;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_MSG_MT_REC_STRU           *pstMtRec;

    pstXccSmsOrigCallCnf = (XCC_CSMS_ORIG_SMS_CALL_CNF_STRU *)pstMsg;

    if (TAF_XSMS_SEND_XCC_CALL_ID_MO != pstXccSmsOrigCallCnf->ucCallId)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf:Call Id error");

        return VOS_ERR;
    }

    pstMoRec = TAF_XSMS_MoGetRecAddr();
    pstMtRec = TAF_XSMS_MtGetRecAddr();

    pstMoRec->ucIsOrigReqSendFlag       = VOS_FALSE;

    /* �����ǰ����·��MT���У����ҵ�ǰ��ԭ��ֵ���Ѿ���TCH����Ϊ���ڵ�ԭ��ֵ��ʧ�ܵ� */
    if ((VOS_TRUE == pstMtRec->ucIsMtCreatLink)
     && (TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH == pstXccSmsOrigCallCnf->enRslt ))
    {
        pstXccSmsOrigCallCnf->enRslt = TAF_XCC_CAUSE_NO_SERVICE;
    }

    /* ֹͣ��ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF);

    switch (pstXccSmsOrigCallCnf->enRslt)
    {
        /* ���з���ɹ��ȴ�SOЭ�� */
        case TAF_XCC_CAUSE_SUCCESS:
            /* ��XSMS���� */
            pstMoRec->ucIsSmsOrigChannel = VOS_TRUE;

            pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;

            /* ����״̬��Ϊ�ȴ�SOЭ����� */
            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_SO_IND);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND,
                                TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND_MAX);

            break;

        /* �Ѿ�����TCH�ŵ�������Ҫ�ٵȴ�SOЭ�� */
        case TAF_XCC_CAUSE_OTHER_SERVICE_IN_TCH:

            /* ����XSMS���� */
            pstMoRec->ucIsSmsOrigChannel = VOS_FALSE;

            /* ��AT�������֮����ר���ŵ��Ϸ��� */
            if (VOS_OK != TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, &pstMoRec->stDbm))
            {
                TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf:TAF_XSMS_SndCasDschDataReq fail.");

                TAF_XSMS_MoIdleInit();

                return VOS_ERR;
            }

            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                                TI_TAF_XSMS_TIMER_MO_WAIT_DSCH_CNF_MAX);

            break;

        default:
            TAF_XSMS_WARNING_LOG("TAF_XSMS_RcvXccOrigCallCnf_MoWaitXccOrigCallCnf:Redial Proc");

            /* �ذδ��� */
            TAF_XSMS_RcvXccOrigCallCnfRedialProc(pstMoRec, pstXccSmsOrigCallCnf);

            break;
    }

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvXccCallCnfTimeOut_MoWaitXccCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    pstMoRec->ucIsOrigReqSendFlag       = VOS_FALSE;

    if (pstMoRec->stNvResend.ucResendMax > pstMoRec->ucResendTimes)
    {

        /* ���Ͷ������� */
        TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);

        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                            pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND);
    }
    /* ���Դ������޲��ٳ��ԣ�����IDLE״̬ */
    else
    {
        /* �ϱ�AT����ʧ�� */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        /* ����,��ʼ��ȫ�ֱ��� */
        TAF_XSMS_MoIdleInit();
    }

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec = VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* ����������1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf: cur resend time is", pstMoRec->ucResendTimes);

    if (VOS_FALSE == pstMoRec->ucIsOrigReqSendFlag)
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvRelinkTimeOut_MoWaitXccOrigCallCnf: orig_req has not send");

        /* ���õ�ǰ�ŵ�ѡ��Ϊר���ŵ� */
        pstMoRec->enActiveSndChannel = TAF_XSMS_ACTIVE_DSCH;

        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    }

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* �������Դ�����1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd: cur relink time is", pstMoRec->ucResendTimes);

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND);

    /* �������Դ��� */
    if ((pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
     || (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN ==  pstMoRec->stNvResend.enXsmsChannelOption))
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_RcvMoLinkAbort_MoWaitSoInd: no relink time left");

        /* ֱ���ϱ�ʧ�� ����IDLE̬ */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        TAF_XSMS_MoIdleInit();
    }
    else
    {
        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();
    }

    return VOS_OK;

}


VOS_UINT32 TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* �������Դ�����1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvXccSoIndTimeOut_MoWaitXccSoInd: cur relink time is", pstMoRec->ucResendTimes);

    /* �������Դ��� */
    if ((pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
     || (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN ==  pstMoRec->stNvResend.enXsmsChannelOption))
    {
        /* ֱ���ϱ�ʧ�� ����IDLE̬ */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        TAF_XSMS_MoIdleInit();
    }
    else
    {
        /* �����ǰ��DSCH���Ͷ��� */
        TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND);

        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    }

    return VOS_OK;

}


VOS_UINT32 TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{

    XCC_CSMS_SERVICE_CONNECT_IND_STRU  *pstSoIndMsg;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec    =  TAF_XSMS_MoGetRecAddr();
    pstSoIndMsg = (XCC_CSMS_SERVICE_CONNECT_IND_STRU*)pstMsg;

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_SO_IND);

    if ((TAF_CDMA_SO_6_SMS == pstSoIndMsg->enSo)
     || (TAF_CDMA_SO_14_RS2_SMS == pstSoIndMsg->enSo))

    {
        /* ���Ͷ��� ���õ�ǰ״̬Ϊ�ȴ�AS_CNF */
        if (VOS_ERR == TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, &pstMoRec->stDbm))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvXccSoInd_MoWaitXccSoInd:TAF_XSMS_SndCasDschDataReq fail");

            TAF_XSMS_MoPrepareReturnToMoIdle();

            return VOS_ERR;
        }

        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);

        /* ����������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_DSCH_CNF_MAX);

    }
    else
    {
        /* �ϱ�AT����ʧ�� */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
        {
            /* ���ŵ� */
            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
        }

        TAF_XSMS_MoIdleInit();

    }

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvDschDataCnf_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8                    enRslt;
    CAS_CNAS_1X_DSCH_DATA_CNF_STRU                         *pstCnfMsg;
    TAF_XSMS_MSG_MO_REC_STRU                               *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();
    pstCnfMsg = (CAS_CNAS_1X_DSCH_DATA_CNF_STRU *)pstMsg;

    enRslt = pstCnfMsg->enRslt;

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* ���ݷ��ͳɹ� */
    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == enRslt)
    {
        if ((VOS_TRUE == pstMoRec->usIsStkUserAck)
         && (TAF_XSMS_STK_SEND_XSMS == pstMoRec->enOrigPid))
        {
            /* ֱ�ӽ����������� ,����Ҫ�ϱ� */
            if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
            {
                /* ���ŵ� */
                TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
            }

            /* ��ʼ����MO_IDLE״̬ */
            TAF_XSMS_MoIdleInit();

        }
        else
        {
            /* ����Ϊ�ȴ�TL_ACK��״̬,����18�뱣����ʱ�� */
            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_TL_ACK);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK,
                                TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK_MAX);
        }
    }
    else
    {
        /* ���ݴ���ԭ��ֵ (1.0 ���½����ŵ�,���·��� 2.0 ���·��� 3.0 ����ֱ�ӷ��� �ص�MO_IDLE) */
        if (VOS_OK != TAF_XSMS_MoAsDataCnfErrProc(enRslt))
        {
            /* �ϱ�AT����ʧ�� */
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

            if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
            {
                TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
            }

            TAF_XSMS_MoIdleInit();
        }
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MoAccessChanResendProc
 ��������  : ��ֻʹ�ù����ŵ��µ�MO��������TAF_XSMS_MO_WAITING_AS_CNF״̬���յ�CNF��Ϣ�н��Ϊ����Ĵ���
 �������  : enRslt:����㷵�صĴ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_OK/VOS_ERR
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoAccessChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* ����㷵�ع����ŵ�����̫���޷����ͣ����ٳ��ԣ�����IDLE״̬ */
    if (CAS_CNAS_1X_DATA_CNF_RSLT_DBM_TOO_LARGE == enRslt)
    {
        TAF_XSMS_MoIdleInit();

        return VOS_ERR;
    }
    else
    {
        /* ��ʱ�ط� */
        pstMoRec->ucResendTimes++;

        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (4 * pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MoTrafficChanResendProc
 ��������  : ��ֻʹ��ר���ŵ��µ�MO��������TAF_XSMS_MO_WAITING_AS_CNF״̬���յ�CNF��Ϣ�н��Ϊ����Ĵ���
 �������  : enRslt:����㷵�صĴ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoTrafficChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* ��ʱ�ط� */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                        (pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND));

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_XSMS_MoBothChanResendProc
 ��������  : ��ʹ��ר���ŵ��򹫹��ŵ��µ�MO��������TAF_XSMS_MO_WAITING_AS_CNF״̬���յ�CNF��Ϣ�н��Ϊ����Ĵ���
 �������  : enRslt:����㷵�صĴ���ԭ��ֵ
 �������  : ��
 �� �� ֵ  : VOS_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��11��03��
    ��    ��   : h00300778
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XSMS_MoBothChanResendProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* ��ǰ���ڹ����ŵ��Ϸ��ͣ����ܺ�ԭ������н����ŵ� */
    if (TAF_XSMS_ACTIVE_CSCH == pstMoRec->enActiveSndChannel)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                            (pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND));

        /* ����״̬��Ϊ�ȴ�XCC��CNF��Ϣ */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF);
    }
    /* ��ǰ�Ѿ���ר���ŵ��ϲ��ٷ�����У��ط����� */
    else
    {
        /* ��ʱ�ط� */
        pstMoRec->ucResendTimes++;

        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));
    }

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_MoAsDataCnfErrProc(CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8 enRslt)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    VOS_UINT32                          ulRslt;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* �����������ѵ����ֵ������,��ʼ��,ֱ�ӻص�MO_IDLE */
    if (pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
    {
        TAF_XSMS_ERROR_LOG("TAF_XSMS_MoAsDataCnfErrProc: ucResendTimes >= stNvResend.ucResendMax");

        return VOS_ERR;
    }

    /* ���ݴ���ԭ��ֵ �ж����ؽ�,���ط� ����ֱ�ӷ����ص�MO_IDLE (����) */
    switch (pstMoRec->stNvResend.enXsmsChannelOption)
    {
        case TAF_XSMS_DATA_REQ_SEND_CHAN_TRAFFIC_CHAN:
            ulRslt = TAF_XSMS_MoTrafficChanResendProc(enRslt);
            break;

        case TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN:
            ulRslt = TAF_XSMS_MoAccessChanResendProc(enRslt);
            break;

        case TAF_XSMS_DATA_REQ_SEND_CHAN_BOTH:
            ulRslt =TAF_XSMS_MoBothChanResendProc(enRslt);
            break;

        /* �������ߵ������� */
        default:
            return VOS_ERR;
    }

    return ulRslt;
}
VOS_UINT32 TAF_XSMS_RcvAsCnfTimeout_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* ���û�г���������Դ��� */
    if (pstMoRec->stNvResend.ucResendMax > pstMoRec->ucResendTimes)
    {
        /* ��ʱ�ط� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));

        pstMoRec->ucResendTimes++;

        /* ���ֵ�ǰ״̬���� */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);
    }
    else
    {
        /* �ϱ�AT����ʧ�� */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_NO_PAGE_RESPONSE);

        if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
        {
            /* ���ŵ� */
            TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);
        }

        /* ����MO_IDLE */
        TAF_XSMS_MoIdleInit();
    }

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    VOS_UINT8                           aucData[3];

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    PS_MEM_SET(aucData, 0, sizeof(aucData));


    /* ѡ���ط��ŵ��ŵ������·���DATA_REQ */
    if (TAF_XSMS_ACTIVE_DSCH == pstMoRec->enActiveSndChannel)
    {
        if (VOS_ERR == TAF_XSMS_SndCasDschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, &pstMoRec->stDbm))
        {
            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf: TAF_XSMS_SndCasDschDataReq fail");

            TAF_XSMS_MoIdleInit();

            TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvResendTimeOut_MoWaitAsCnf: TAF_XSMS_SndCasDschDataReq fails");

            return VOS_ERR;
        }
    }
    else
    {
        TAF_XSMS_SndCasCschReq_MoWaitCasCnf();
    }

    /* ���õ�ǰ״̬ΪTAF_XSMS_MO_WAITING_AS_CNF */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);

    if (TAF_XSMS_ACTIVE_CSCH == pstMoRec->enActiveSndChannel)
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_CSCH_CNF_MAX);
    }
    else
    {
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_DSCH_CNF_MAX);
    }

    return VOS_OK;
}



VOS_UINT32 TAF_XSMS_RcvCschDataCnf_MoWaitAsCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    CAS_CNAS_1X_DATA_CNF_RSLT_ENUM_UINT8                    enRslt;
    CAS_CNAS_1X_CSCH_DATA_CNF_STRU                         *pstCnfMsg;
    TAF_XSMS_MSG_MO_REC_STRU                               *pstMoRec;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    pstCnfMsg = (CAS_CNAS_1X_CSCH_DATA_CNF_STRU *)pstMsg;

    enRslt = pstCnfMsg->enRslt;

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* ���ݷ��ͳɹ� */
    if (CAS_CNAS_1X_DATA_CNF_RSLT_SUCCESS == enRslt)
    {
        if ((VOS_TRUE == pstMoRec->usIsStkUserAck)
         && (TAF_XSMS_STK_SEND_XSMS == pstMoRec->enOrigPid))
        {
            /* ֱ�ӽ����������� ,����Ҫ�ϱ� */
            /* ��ʼ����MO_IDLE״̬ */
            TAF_XSMS_MoIdleInit();

        }
        else
        {
            /* ����Ϊ�ȴ�TL_ACK��״̬,����������ʱ�� */
            TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_TL_ACK);

            TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK,
                                TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK_MAX);
        }

    }
    else
    {
        /* ���ݴ���ԭ��ֵ (1.0 ���½����ŵ�,���·��� 2.0 ���·��� 3.0 ����ֱ�ӷ��� �ص�MO_IDLE) */
        if (VOS_OK != TAF_XSMS_MoAsDataCnfErrProc(enRslt))
        {
            /* �ϱ�AT����ʧ�� */
            TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

            TAF_XSMS_MoIdleInit();
        }
    }

    return VOS_OK;

}
VOS_UINT32 TAF_XSMS_RcvDschTlACK_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstDschDataInd;
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTlAck;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstDschDataInd = (TAF_XSMS_CAS_DATA_IND_MSG_STRU *)pstMsg;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    PS_MEM_SET(&stTlAck, 0, sizeof(TAF_XSMS_TRANSPORT_MESSAGE_STRU));

    /* ͨ������ӿڽ�TL ACK���TL STRU */
    if (VOS_ERR == TAF_XSMS_DecodeTLRawToTLStru(pstDschDataInd->ucLen, pstDschDataInd->aucMsg, &stTlAck))
    {
        /* ������� */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvDschTlACK_MoWaitTlACK:TAF_XSMS_DecodeTLRawToTLStru fail");

        return VOS_ERR;
    }


    TAF_XSMS_INFO_LOG1(" In MO TL_ACK the seq num is", stTlAck.stCauseCode.ucReplySeq);

    TAF_XSMS_HookSmsTlAck(TAF_XSMS_HOOK_MSG_TYPE_RCV_TL_ACK, &stTlAck.stCauseCode);

    if (stTlAck.stCauseCode.ucReplySeq != (pstMoRec->ucReplySeq - 1))
    {
        /* ���Ƕ�Ӧ��TL_ACK */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvDschTlACK_MoWaitTlACK:Reply Seq not match");

        return VOS_ERR;
    }

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* ������Ƕ��Ž�����ֱ���ϱ��ɹ�����ʧ��
    ����Ƕ��Ž������ȴ���·�ͷ�֮�����ֱ���ϱ����ŷ��ͽ�� */
    if (VOS_FALSE == pstMoRec->ucIsSmsOrigChannel)
    {
        if ( TAF_XSMS_TL_CAUSECODE_NONE == stTlAck.stCauseCode.enErrorClass)
        {
            /* ����ɹ����ϱ����ͳɹ� */
            TAF_XSMS_MsgSubmitSuccInd((VOS_UINT32)(pstMoRec->usMessageId));
        }
        else
        {
            /* ���ʧ�ܣ��ϱ����ŷ���ʧ��*/
            TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)(stTlAck.stCauseCode.enCauseCode));

        }
    }
    else
    {
        /* �洢CAUSE CODE */
        PS_MEM_CPY(&pstMoRec->stCauseCode, &stTlAck.stCauseCode, sizeof(TAF_XSMS_CAUSE_CODE_STRU));
    }

    /* �ж��Ƿ���SMS�������ŵ�������ǣ����ŵ� */
    TAF_XSMS_MoPrepareReturnToMoIdle();

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvCschTlACK_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_CAS_DATA_IND_MSG_STRU     *pstCschDataInd;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    TAF_XSMS_TRANSPORT_MESSAGE_STRU     stTlAck;

    pstCschDataInd = (TAF_XSMS_CAS_DATA_IND_MSG_STRU *)pstMsg;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    PS_MEM_SET(&stTlAck, 0, sizeof(stTlAck));

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_TL_ACK);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);

    /* ͨ������ӿڽ�TL ACK���TL STRU */
    TAF_XSMS_DecodeTLRawToTLStru(pstCschDataInd->ucLen, pstCschDataInd->aucMsg, &stTlAck);

    TAF_XSMS_INFO_LOG1(" In MO TL_ACK the seq num is", stTlAck.stCauseCode.ucReplySeq);

    TAF_XSMS_HookSmsTlAck(TAF_XSMS_HOOK_MSG_TYPE_RCV_TL_ACK, &stTlAck.stCauseCode);

    if (stTlAck.stCauseCode.ucReplySeq != (pstMoRec->ucReplySeq - 1))
    {
        /* log ��ӡTL_ACK SEQ NUM ��ƥ�� */
        TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvCschTlACK_MoWaitTlACK: SEQ_NUM mot match");

        return VOS_ERR;
    }

    if (TAF_XSMS_TL_CAUSECODE_NONE == stTlAck.stCauseCode.enErrorClass)
    {
        /* ����ɹ����ϱ����ͳɹ� */
        TAF_XSMS_MsgSubmitSuccInd((VOS_UINT32)(pstMoRec->usMessageId));
    }
    else
    {
        /* ���ʧ�ܣ��ϱ����ŷ���ʧ�� */
        TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)(stTlAck.stCauseCode.enCauseCode));
    }

    /* ����MO_IDLE */
    TAF_XSMS_MoIdleInit();

    return VOS_OK;

}



VOS_UINT32 TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec   = TAF_XSMS_MoGetRecAddr();

    TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvTlAckTimeOut_MoWaitTlACK: wait tl_ack timeout,ap should resend");

    /* �ϱ�AT �ȴ�TLACK ��ʱ */
    if ((TAF_XSMS_ACTIVE_CSCH == pstMoRec->enActiveSndChannel)
     ||((TAF_XSMS_ACTIVE_DSCH == pstMoRec->enActiveSndChannel)
     && (VOS_FALSE == pstMoRec->ucIsSmsOrigChannel)))
    {
        TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)TAF_XSMS_TL_NO_ACK);
    }
    else
    {
        pstMoRec->stCauseCode.enCauseCode   = TAF_XSMS_TL_NO_ACK;
        pstMoRec->stCauseCode.enErrorClass  = TAF_XSMS_TL_CAUSECODE_TMP;

    }

    /* �����ص�MO_IDLE */
    TAF_XSMS_MoPrepareReturnToMoIdle();

    return VOS_OK;
}


VOS_UINT32 TAF_XSMS_RcvEndCallCnf_MoWaitEndCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL);

    /* ���õ�ǰ״̬Ϊ�ȴ�LINK ABORT */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND);

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT,
                        TI_TAF_XSMS_TIMER_MO_WAIT_LINK_ABORT_MAX);

    return VOS_OK;
}



VOS_UINT32 TAF_XSMS_RcvSmsAbortInd_MoWaitLinkAbort(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec  = TAF_XSMS_MoGetRecAddr();

    /* ͣ����ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL);

    /* �ϱ��ɹ�����ʧ�� */
    if ( TAF_XSMS_TL_CAUSECODE_NONE == pstMoRec->stCauseCode.enErrorClass)
    {
        /* ����ɹ����ϱ����ͳɹ� */
        TAF_XSMS_MsgSubmitSuccInd((VOS_UINT32)(pstMoRec->usMessageId));
    }
    else
    {
        /* ���ʧ�ܣ��ϱ����ŷ���ʧ��*/
        TAF_XSMS_MsgSubmitFailInd((VOS_UINT32)(pstMoRec->stCauseCode.enCauseCode));

    }

    /* ���۳ɹ�ʧ�ܣ����ص�MT_IDLE״̬ */
    TAF_XSMS_MoIdleInit();

    return VOS_OK;
}
VOS_UINT32 TAF_XSMS_RcvEndCallCnfTimeout_MoWaitEndCallCnf(VOS_UINT32 ulEventType, struct MsgCB *pstMsg)
{
    /* ���õ�ǰ״̬Ϊ�ȴ�LINK ABORT */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_CAS_SMS_ABORT_IND);

    TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_SMS_ABORT,
                        TI_TAF_XSMS_TIMER_MO_WAIT_LINK_ABORT_MAX);

    return VOS_OK;

}
VOS_VOID TAF_XSMS_MoPrepareReturnToMoIdle(VOS_VOID)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    /* Deleted by h00313353 for Pc Lint, 2015-3-30 */
    pstMoRec        = TAF_XSMS_MoGetRecAddr();
    /* Deleted by h00313353 for Pc Lint, 2015-3-30 */

    /* �ж��Ƿ���SMS�������ŵ�������ǣ����ŵ� */
    if (VOS_TRUE == pstMoRec->ucIsSmsOrigChannel)
    {
        /* ���ŵ� */
        TAF_XSMS_SndXccEndCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO, TAF_XCC_END_REASON_NORMAL_RELEASE);

        /* ���ö�ʱ��Ϊ�ȴ�XCC�ҶϺ��е�CNF */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_END_CALL_CNF);

        /* ��ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL,
                            TI_TAF_XSMS_TIMER_MO_WAIT_END_CALL_MAX);
    }
    else
    {
        /*�����ŵ�����ʼ����MO_IDLE״̬ */
        TAF_XSMS_MoIdleInit();
    }

    return;
}
VOS_UINT32 TAF_XSMS_RcvMmaServiceStatus_MoWaitXccOrigCallCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    MMA_XSMS_SERVICE_STATUS_IND_STRU   *pMmaXsmsStatusInd;
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;

    pstMoRec            =   TAF_XSMS_MoGetRecAddr();
    pMmaXsmsStatusInd   =  (MMA_XSMS_SERVICE_STATUS_IND_STRU*)pstMsg;

    /* ������ڵȴ��ض�����ɶ����ض���֮��Ľ��뼼��Ϊ1X���߻��ģʽ */
    if ((TAF_SDC_SYS_MODE_CDMA_1X == pMmaXsmsStatusInd->enRatType)
    &&  (VOS_TRUE == pstMoRec->ucWaitRedirCompleteFlag)
    &&  (VOS_FALSE == pstMoRec->ucIsOrigReqSendFlag))
    {
        pstMoRec->ucWaitRedirCompleteFlag   = VOS_FALSE;

        /* ֱ�ӷ��������� */
        TAF_XSMS_SndXccSmsOrgiCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO,
                                      pstMoRec->ucIsL2ErrReOrig,
                                      pstMoRec->ucL2ErrReOrigCount);

        /* ������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF_MAX);

        /* ����״̬��Ϊ�ȴ�XCC��CNF��Ϣ */
        TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF);
    }

    return VOS_OK;

}



VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec    =  VOS_NULL_PTR;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /* ��·������Ҫͣ���ȴ�CNF�Ķ�ʱ�������ط��Ķ�ʱ�� */
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF);
    TAF_XSMS_StopTimer(TI_TAF_XSMS_TIMER_MO_RESEND);

    /* �������Դ�����1 */
    pstMoRec->ucResendTimes++;

    TAF_XSMS_INFO_LOG1("TAF_XSMS_RcvMoLinkAbort_MoWaitAsCnf: cur relink time is", pstMoRec->ucResendTimes);

    /* �������Դ��� */
    if (pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
    {
        /* ֱ���ϱ�ʧ�� ����IDLE̬ */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        TAF_XSMS_MoIdleInit();
    }
    else if (TAF_XSMS_DATA_REQ_SEND_CHAN_ACCESS_CHAN ==  pstMoRec->stNvResend.enXsmsChannelOption)
    {
        TAF_XSMS_SndCasCschReq_MoWaitCasCnf();
    }
    else
    {
        /* �����ǰ��DSCH���Ͷ��� */
        TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf();

    }

    return VOS_OK;
}
VOS_VOID TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf
(
    VOS_VOID
)
{
    TAF_XSMS_MSG_MO_REC_STRU                *pstMoRec;
    TAF_SDC_1X_UE_MAIN_STATUS_ENUM_UINT8     enCasState;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8        enCsServiceStatus;
    VOS_UINT8                                ucCsCallExistFlg;

    pstMoRec = TAF_XSMS_MoGetRecAddr();

    /*�жϵ�ǰ��ʱ�������Ƿ�ﵽ������*/
    if (pstMoRec->stNvResend.ucResendMax <= pstMoRec->ucResendTimes)
    {
        /* �ϱ�AT����ʧ�� */
        TAF_XSMS_MsgSubmitFailInd(TAF_XSMS_TL_DESTINATION_BUSY);

        /* ����,��ʼ��ȫ�ֱ��� */
        TAF_XSMS_MoIdleInit();

        return;
    }

    enCsServiceStatus  = TAF_SDC_GetCsServiceStatus();
    enCasState         = TAF_SDC_GetCdmaCurUeState();
    ucCsCallExistFlg   = TAF_SDC_GetCsCallExistFlg();

    if ( (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCsServiceStatus)
       && ((VOS_TRUE !=  ucCsCallExistFlg) || (TAF_SDC_1X_UE_MAIN_STATUS_TCH_STATE == enCasState)))
    {
        TAF_XSMS_INFO_LOG("TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf: normal service snd xcc orig_req");

        /* ��XCC������� */
        TAF_XSMS_SndXccSmsOrgiCallReq(TAF_XSMS_SEND_XCC_CALL_ID_MO,
                                      pstMoRec->ucIsL2ErrReOrig,
                                      pstMoRec->ucL2ErrReOrigCount);

        /* ������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_XCC_CALL_CNF_MAX);

    }
    else
    {
        /* �����������Ӷ�ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RELINK,
                            pstMoRec->stNvResend.ucReconnectInterval * TAF_XSMS_MILLISECS_IN_SECOND);

        TAF_XSMS_ERROR_LOG("TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf: TAF_SDC_GetCsServiceStatus not normal service");
        TAF_XSMS_ERROR_LOG("TAF_XSMS_SndXccOrigReq_MoWaitOrigCnf: Start XSMS relink timer");

    }

    /* ����״̬��Ϊ�ȴ� */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_XCC_ORIG_CALL_CNF);

    return;

}
VOS_VOID TAF_XSMS_SndCasCschReq_MoWaitCasCnf
(
    VOS_VOID
)
{
    TAF_XSMS_MSG_MO_REC_STRU           *pstMoRec;
    VOS_UINT8                           aucData[3];
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enCurService;

    pstMoRec        = TAF_XSMS_MoGetRecAddr();
    enCurService    =  TAF_SDC_GetCsServiceStatus();

    PS_MEM_SET(aucData, 0, 3);
    TAF_XSMS_EncodeAuth(&pstMoRec->st1xSms.stAddr, aucData);

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enCurService)
    {
        /* �����ݷ���CAS */
        if (VOS_ERR == TAF_XSMS_SndCasCschDataReq(TAF_XSMS_CAS_DATA_REQ_TYPE_MO, aucData, &(pstMoRec->stDbm)))
        {
            TAF_XSMS_MoIdleInit();

            TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasCschReq_MoWaitCasCnf: TAF_XSMS_SndCasCschDataReq fail");

            return ;
        }

        /* ������ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_WAIT_AS_CNF,
                            TI_TAF_XSMS_TIMER_MO_WAIT_CSCH_CNF_MAX);

    }
    else
    {
        /* ����4S��ʱ�� */
        TAF_XSMS_StartTimer(TI_TAF_XSMS_TIMER_MO_RESEND,
                            (4 * pstMoRec->stNvResend.ucResendInterval * TAF_XSMS_MILLISECS_IN_SECOND));

        TAF_XSMS_ERROR_LOG("TAF_XSMS_SndCasCschReq_MoWaitCasCnf:  unnormal service");
    }

    /* ����״̬��Ϊ�ȴ������ظ� */
    TAF_XSMS_MoSetCurrFsmState(TAF_XSMS_MO_WAITING_AS_CNF);

    return;
}



VOS_UINT32 TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck
(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XSMS_ERROR_LOG("TAF_XSMS_RcvMoLinkAbort_MoWaitTlAck: do nothing,should wait for 18s and AP resend");
    return VOS_OK;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



