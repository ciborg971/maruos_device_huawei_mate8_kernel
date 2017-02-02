

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ImsaProcUssdMsg.h"
#include "ImsaEntity.h"
#include "ImsaImsInterface.h"
#include "ImsaPublic.h"
#include "ImsaImsAdaption.h"
/* modify by jiqiang 2014.03.25 pclint fix error 718 begin */
#include "ImsaProcUssdMsg.h"
/* modify by jiqiang 2014.03.25 pclint fix error 718 end */
/*lint -e767*/
#define    THIS_FILE_ID         PS_FILE_ID_IMSAPROCUSSDMSG_C
#define    THIS_NAS_FILE_ID     NAS_FILE_ID_IMSAPROCUSSDMSG_C
/*lint +e767*/


/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/

/*****************************************************************************
  3 Function
*****************************************************************************/

/*lint -e961*/

VOS_VOID IMSA_USSD_Init(VOS_VOID)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    /*��ʼ������*/
    IMSA_MEM_SET(pstUssdManager, 0, sizeof(IMSA_USSD_MANAGER_STRU));
    pstUssdManager->enUssdState = IMSA_USSD_IDLE_STATE;

    /*���ö�ʱ�����ȣ����Ƶ�*/
    pstUssdManager->stUssdWaitNetRspTimer.usName = TI_IMSA_USSD_WAIT_NET_RSP;
    pstUssdManager->stUssdWaitNetRspTimer.ulTimerLen = IMSA_USSD_TIMER_WAIT_NET_RSP_LENGTH;
    pstUssdManager->stUssdWaitNetRspTimer.ucMode = 0;

    pstUssdManager->stUssdWaitAppRspTimer.usName = TI_IMSA_USSD_WAIT_APP_RSP;
    pstUssdManager->stUssdWaitAppRspTimer.ulTimerLen = IMSA_USSD_TIMER_WAIT_APP_RSP_LENGTH;
    pstUssdManager->stUssdWaitAppRspTimer.ucMode = 0;

}


VOS_VOID IMSA_USSD_ClearResource(VOS_VOID)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    /*ֹͣ��ʱ��*/
    if (VOS_TRUE == IMSA_IsTimerRunning(&pstUssdManager->stUssdWaitNetRspTimer))
    {
        IMSA_StopTimer(&pstUssdManager->stUssdWaitNetRspTimer);

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MO_SS);
        #endif

        (VOS_VOID)IMSA_SendSpmUssdErrorEvt(pstUssdManager->usClientId,
                                            pstUssdManager->ucOpId,
                                            TAF_ERR_IMSA_USSD_UNSPECIFIC);

    }

    if (VOS_TRUE == IMSA_IsTimerRunning(&pstUssdManager->stUssdWaitAppRspTimer))
    {
        IMSA_StopTimer(&pstUssdManager->stUssdWaitAppRspTimer);


        #if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MT_SS);
        #endif

        (VOS_VOID)IMSA_SendSpmUssdErrorEvt(pstUssdManager->usClientId,
                                            pstUssdManager->ucOpId,
                                            TAF_ERR_IMSA_USSD_UNSPECIFIC);
    }


    /*��ʼ������*/
    IMSA_MEM_SET(pstUssdManager, 0, sizeof(IMSA_USSD_MANAGER_STRU));
    pstUssdManager->enUssdState = IMSA_USSD_IDLE_STATE;
}




VOS_UINT32 IMSA_SsProcSpmMsgProcessUssdReq(VOS_VOID     *pMsg)
{
    IMSA_IMS_USSD_ENCTYPE_ENUM_UINT8   encType;
    VOS_UINT16   usLength = 0;
    VOS_UINT8    aucMessage[TAF_SS_MAX_USSDSTRING_LEN*2];
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;
    SPM_IMSA_PROCESS_USSD_REQ_STRU *pstUssdReq = VOS_NULL_PTR;

    pstUssdReq = (SPM_IMSA_PROCESS_USSD_REQ_STRU*)pMsg;

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    if (IMSA_USSD_MO_CONN_STATE == pstUssdManager->enUssdState)
    {
        IMSA_INFO_LOG("IMSA_SsProcSpmMsgProcessUssdReq: USSD State is err!");
        TLPS_PRINT2LAYER_INFO(IMSA_SsProcSpmMsgProcessUssdReq_ENUM, IMSA_STATE_ERROR);

        /*��SPM�ظ���Ϣ���󣬲������USSD������Ϣ,ֱ�ӻظ�ʧ��*/
        (VOS_VOID)IMSA_SendSpmUssdErrorEvt(  pstUssdReq->usClientId,
                                    pstUssdReq->ucOpId,
                                    TAF_ERR_IMSA_USSD_BUSY);
        return VOS_TRUE;
    }

    /*����ClientId��opId*/
    pstUssdManager->usClientId  = pstUssdReq->usClientId;
    pstUssdManager->ucOpId      = pstUssdReq->ucOpId;

    usLength = pstUssdReq->stProcUssdReq.UssdStr.usCnt;
    IMSA_MEM_CPY(aucMessage,pstUssdReq->stProcUssdReq.UssdStr.aucUssdStr,usLength);

    if( (TAF_SS_8bit != pstUssdReq->stProcUssdReq.DatacodingScheme)
        && (TAF_SS_UCS2 != pstUssdReq->stProcUssdReq.DatacodingScheme))
    {
        encType = TAF_SS_7bit_LANGUAGE_UNSPECIFIED;

    }
    else
    {
        encType =  pstUssdReq->stProcUssdReq.DatacodingScheme;
    }

    if (IMSA_USSD_IDLE_STATE == pstUssdManager->enUssdState)
    {
         /*����USSD״̬*/
        pstUssdManager->enUssdState = IMSA_USSD_MO_CONN_STATE;

        /*�����ȴ�������Ӧ��ʱ��*/
        IMSA_StartTimer(&(pstUssdManager->stUssdWaitNetRspTimer));

        #if (FEATURE_ON == FEATURE_DSDS)
        /*����begin notify��Ϣ��RRC��֪ͨRRC������Դ*/
        IMSA_SendRrcDsdsBeginNotify(IMSA_LRRC_SESSION_TYPE_MO_SS);
        #endif

    }
    else if (IMSA_USSD_MT_CONN_STATE == pstUssdManager->enUssdState)
    {

        /*ֹͣ�ȴ�APP��Ӧ��ʱ��*/
        IMSA_StopTimer(&(pstUssdManager->stUssdWaitAppRspTimer));
        #if (FEATURE_ON == FEATURE_DSDS)
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MT_SS);
        #endif

        /*����USSD״̬*/
        pstUssdManager->enUssdState = IMSA_USSD_MO_CONN_STATE;

        /*�����ȴ�������Ӧ��ʱ��*/
        IMSA_StartTimer(&(pstUssdManager->stUssdWaitNetRspTimer));
        #if (FEATURE_ON == FEATURE_DSDS)
        /*����begin notify��Ϣ��RRC��֪ͨRRC������Դ*/
        IMSA_SendRrcDsdsBeginNotify(IMSA_LRRC_SESSION_TYPE_MO_SS);
        #endif
    }
    else
    {
        IMSA_INFO_LOG("IMSA_SsProcSpmMsgProcessUssdReq: not process ussd msg");
        TLPS_PRINT2LAYER_INFO(IMSA_SsProcSpmMsgProcessUssdReq_ENUM, LNAS_MSG_INVALID);
    }

    /*��IMS������Ϣ*/
    IMSA_USSD_SndImsUssdReqMsg(encType,usLength,aucMessage);
    return VOS_TRUE;

}
VOS_UINT32 IMSA_SsProcSpmMsgReleaseReq(VOS_VOID* pMsg)
{

    IMSA_USSD_MANAGER_STRU              *pstUssdManager;

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    if ((IMSA_USSD_MO_CONN_STATE != pstUssdManager->enUssdState)
        && (IMSA_USSD_MT_CONN_STATE != pstUssdManager->enUssdState))
    {
        IMSA_INFO_LOG("IMSA_SsProcSpmMsgReleaseReq: USSD State is err!");
        TLPS_PRINT2LAYER_INFO(IMSA_SsProcSpmMsgReleaseReq_ENUM, IMSA_STATE_ERROR);


        return VOS_TRUE;
    }

    /*ֹͣ�ȴ�������Ӧ��ʱ��*/
    IMSA_StopTimer(&(pstUssdManager->stUssdWaitNetRspTimer));

    /*ֹͣ�ȴ�APP��Ӧ��ʱ��*/
    IMSA_StopTimer(&(pstUssdManager->stUssdWaitAppRspTimer));

    #if (FEATURE_ON == FEATURE_DSDS)
    /*���ݵ�ǰ״̬ȷ���ͷ��ĸ�ҵ����Դ*/
    if(IMSA_USSD_MO_CONN_STATE == pstUssdManager->enUssdState)
    {
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MO_SS);
    }
    else
    {
        /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
        IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MT_SS);
    }
    #endif

    pstUssdManager->enUssdState = IMSA_USSD_IDLE_STATE;

    /*��IMS������Ϣ*/
    IMSA_USSD_SndImsUssdDisconnectMsg();

    return VOS_TRUE;

}





VOS_VOID IMSA_USSD_SndImsUssdReqMsg
(
    IMSA_IMS_USSD_ENCTYPE_ENUM_UINT8   encType,
    VOS_UINT16   usLength,
    const VOS_UINT8   *pucMessage
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_USSD_SndImsUssdReqMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_USSD_SndImsUssdReqMsg_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_USSD_SndImsUssdReqMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_USSD_SndImsUssdReqMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(pstInputEvent, 0, sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_USSD;
    pstInputEvent->evt.stInputUssdEvent.enInputUssdReason = IMSA_IMS_INPUT_USSD_REASON_AT_CMD_SEND;
    pstInputEvent->evt.stInputUssdEvent.ulOpId = IMSA_AllocImsOpId();
    pstInputEvent->evt.stInputUssdEvent.encType = encType;
    pstInputEvent->evt.stInputUssdEvent.usMessageLen = usLength;
    IMSA_MEM_CPY(pstInputEvent->evt.stInputUssdEvent.ucMessage,
                pucMessage,
                usLength);

    IMSA_SndImsMsgUssdEvent(pstInputEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return;

}


VOS_VOID IMSA_USSD_SndImsUssdDisconnectMsg
(
    VOS_VOID
)
{
    IMSA_IMS_INPUT_EVENT_STRU *pstInputEvent = VOS_NULL_PTR;

    IMSA_INFO_LOG("IMSA_USSD_SndImsUssdDisconnectMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_USSD_SndImsUssdDisconnectMsg_ENUM, LNAS_ENTRY);

    pstInputEvent = (IMSA_IMS_INPUT_EVENT_STRU *)IMSA_MEM_ALLOC(sizeof(IMSA_IMS_INPUT_EVENT_STRU));
    if (VOS_NULL_PTR == pstInputEvent)
    {
        IMSA_ERR_LOG("IMSA_USSD_SndImsUssdDisconnectMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_USSD_SndImsUssdDisconnectMsg_ENUM, LNAS_NULL_PTR);
        return;
    }

    IMSA_MEM_SET(pstInputEvent, 0, sizeof(IMSA_IMS_INPUT_EVENT_STRU));

    pstInputEvent->enEventType = IMSA_IMS_EVENT_TYPE_USSD;
    pstInputEvent->evt.stInputUssdEvent.enInputUssdReason = IMSA_IMS_INPUT_USSD_REASON_AT_CMD_DISCONNECT;
    pstInputEvent->evt.stInputUssdEvent.ulOpId = IMSA_AllocImsOpId();
    pstInputEvent->evt.stInputUssdEvent.encType = IMSA_IMS_USSD_ENCTYPE_UNSPECIFIED;

    IMSA_SndImsMsgUssdEvent(pstInputEvent);

    IMSA_MEM_FREE(pstInputEvent);

    return;

}


VOS_UINT32 IMSA_SendImsaSpmSsMsg(
                                    const TAF_SS_CALL_INDEPENDENT_EVENT_STRU  *pEvtData,
                                    VOS_UINT16 usLen )
{
    IMSA_SPM_SS_MSG_STRU *pstSpmSsMsg = VOS_NULL_PTR;
    VOS_UINT32 ulMsgLen = 0;

    IMSA_INFO_LOG("IMSA_SendImsaSpmSsMsg is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendImsaSpmSsMsg_ENUM, LNAS_ENTRY);

    ulMsgLen = (sizeof(IMSA_SPM_SS_MSG_STRU) + usLen) - sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU);

    /* ����ռ䲢��������Ƿ�ɹ� */
    pstSpmSsMsg = (VOS_VOID*)IMSA_ALLOC_MSG(ulMsgLen);
    if (VOS_NULL_PTR == pstSpmSsMsg)
    {
        IMSA_ERR_LOG("IMSA_SendImsaSpmSsMsg: alloc memory fail");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendImsaSpmSsMsg_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    /* ��� */
    IMSA_MEM_SET( IMSA_GET_MSG_ENTITY(pstSpmSsMsg), 0, IMSA_GET_MSG_LENGTH(pstSpmSsMsg));

    /* ��д��Ϣͷ */
    IMSA_WRITE_SPM_MSG_HEAD(pstSpmSsMsg, ID_IMSA_SPM_SS_MSG);

    /* ����Client Id����GU��ͨ�������Χ��CLIENT ID��дͬ�¼��е�client id*/
    pstSpmSsMsg->usClientId =  0x3fff;

    /* ������Ϣ���ݼ����� */
    pstSpmSsMsg->usLen = usLen;
    IMSA_MEM_CPY(&pstSpmSsMsg->stSsEventInfo, pEvtData, pstSpmSsMsg->usLen);

    /* ������Ϣ���ͺ��� */
    IMSA_SND_MSG(pstSpmSsMsg);

    return VOS_TRUE;
}


VOS_UINT32 IMSA_SendSpmUssdDataSndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvt;
    VOS_UINT32                          ulRslt;

    IMSA_INFO_LOG("IMSA_SendSpmUssdDataSndEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdDataSndEvt_ENUM, LNAS_ENTRY);

    pstSsEvt = IMSA_MEM_ALLOC(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstSsEvt )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendSpmUssdDataSndEvt:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdDataSndEvt_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET(pstSsEvt, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /* �����¼����� */
    pstSsEvt->SsEvent= TAF_SS_EVT_USSD_DATA_SND;

    /* ����TAF_SS_CALL_INDEPENDENT_EVENT_STRU�е�call id�ȹ�����Ϣ */
    pstSsEvt->ClientId   = (MN_CLIENT_ID_T)usClientId;
    pstSsEvt->OpId     = (MN_OPERATION_ID_T)ucOpId;


    /* ���÷��ͺ��� */
    ulRslt = IMSA_SendImsaSpmSsMsg(pstSsEvt,
                                    sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    IMSA_MEM_FREE(pstSsEvt);

    return ulRslt;
}



VOS_UINT32 IMSA_SendSpmUssdReqIndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucEncType,
    const TAF_SS_USSD_STRING_STRU             *pstUssdString
)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvt = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    IMSA_INFO_LOG("IMSA_SendSpmUssdReqIndEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdReqIndEvt_ENUM, LNAS_ENTRY);

    pstSsEvt = IMSA_MEM_ALLOC(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstSsEvt )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendSpmUssdReqIndEvt:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendSpmUssdReqIndEvt_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET(pstSsEvt, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /* �����¼����� */
    pstSsEvt->SsEvent= TAF_SS_EVT_USS_REQ_IND;

    /* ����TAF_SS_CALL_INDEPENDENT_EVENT_STRU�е���Ϣ */
    pstSsEvt->ClientId   = (MN_CLIENT_ID_T)usClientId;
    pstSsEvt->OpId     = (MN_OPERATION_ID_T)ucOpId;

    pstSsEvt->OP_DataCodingScheme = 1;
    pstSsEvt->OP_UssdString = 1;
    pstSsEvt->DataCodingScheme = (TAF_SS_DATA_CODING_SCHEME)ucEncType;
    pstSsEvt->UssdString.usCnt = pstUssdString->usCnt;

    IMSA_MEM_CPY (pstSsEvt->UssdString.aucUssdStr,pstUssdString->aucUssdStr,pstUssdString->usCnt);


    /* ���÷��ͺ��� */
    ulRslt = IMSA_SendImsaSpmSsMsg(pstSsEvt,
                                    sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    IMSA_MEM_FREE(pstSsEvt);

    return ulRslt;
}


VOS_UINT32 IMSA_SendSpmUssdNotifyIndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT8                           ucEncType,
    const TAF_SS_USSD_STRING_STRU       *pstUssdString
)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvt = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    IMSA_INFO_LOG("IMSA_SendSpmUssdNotifyIndEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdNotifyIndEvt_ENUM, LNAS_ENTRY);

    pstSsEvt = IMSA_MEM_ALLOC(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstSsEvt )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendSpmUssdNotifyIndEvt:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendSpmUssdNotifyIndEvt_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET(pstSsEvt, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /* �����¼����� */
    pstSsEvt->SsEvent= TAF_SS_EVT_USS_NOTIFY_IND;

    /* ����TAF_SS_CALL_INDEPENDENT_EVENT_STRU�е���Ϣ */
    pstSsEvt->ClientId   = (MN_CLIENT_ID_T)usClientId;
    pstSsEvt->OpId     = (MN_OPERATION_ID_T)ucOpId;

    pstSsEvt->OP_DataCodingScheme = 1;
    pstSsEvt->OP_UssdString = 1;
    pstSsEvt->DataCodingScheme = (TAF_SS_DATA_CODING_SCHEME)ucEncType;
    pstSsEvt->UssdString.usCnt = pstUssdString->usCnt;

    IMSA_MEM_CPY (pstSsEvt->UssdString.aucUssdStr,pstUssdString->aucUssdStr,pstUssdString->usCnt);


    /* ���÷��ͺ��� */
    ulRslt = IMSA_SendImsaSpmSsMsg(pstSsEvt,
                                    sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    IMSA_MEM_FREE(pstSsEvt);

    return ulRslt;
}


VOS_UINT32 IMSA_SendSpmUssdRelCompleteIndEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId
)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvt = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    IMSA_INFO_LOG("IMSA_SendSpmUssdRelCompleteIndEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdRelCompleteIndEvt_ENUM, LNAS_ENTRY);

    pstSsEvt = IMSA_MEM_ALLOC(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstSsEvt )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendSpmUssdRelCompleteIndEvt:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendSpmUssdRelCompleteIndEvt_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET(pstSsEvt, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /* �����¼����� */
    pstSsEvt->SsEvent= TAF_SS_EVT_USS_RELEASE_COMPLETE_IND;

    /* ����TAF_SS_CALL_INDEPENDENT_EVENT_STRU�е���Ϣ */
    pstSsEvt->ClientId   = (MN_CLIENT_ID_T)usClientId;
    pstSsEvt->OpId     = (MN_OPERATION_ID_T)ucOpId;

    /* ���÷��ͺ��� */
    ulRslt = IMSA_SendImsaSpmSsMsg(pstSsEvt,
                                    sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    IMSA_MEM_FREE(pstSsEvt);

    return ulRslt;
}


VOS_UINT32 IMSA_SendSpmUssdReqCnfEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT16                          usError
)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvt = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    IMSA_INFO_LOG("IMSA_SendSpmUssdReqCnfEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdReqCnfEvt_ENUM, LNAS_ENTRY);

    pstSsEvt = IMSA_MEM_ALLOC(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstSsEvt )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendSpmUssdReqCnfEvt:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdReqCnfEvt_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET(pstSsEvt, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /* �����¼����� */
    pstSsEvt->SsEvent= TAF_SS_EVT_PROCESS_USS_REQ_CNF;

    /* ����TAF_SS_CALL_INDEPENDENT_EVENT_STRU�е���Ϣ */
    pstSsEvt->ClientId   = (MN_CLIENT_ID_T)usClientId;
    pstSsEvt->OpId     = (MN_OPERATION_ID_T)ucOpId;
    pstSsEvt->OP_Cause = 1;
    pstSsEvt->Cause = (VOS_UINT8)usError;

    /* ���÷��ͺ��� */
    ulRslt = IMSA_SendImsaSpmSsMsg(pstSsEvt,
                                    sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    IMSA_MEM_FREE(pstSsEvt);

    return ulRslt;
}


VOS_UINT32 IMSA_SendSpmUssdErrorEvt
(
    VOS_UINT16                          usClientId,
    VOS_UINT8                           ucOpId,
    VOS_UINT16                          usError
)
{
    TAF_SS_CALL_INDEPENDENT_EVENT_STRU *pstSsEvt = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    IMSA_INFO_LOG("IMSA_SendSpmUssdErrorEvt is entered!");
    TLPS_PRINT2LAYER_INFO(IMSA_SendSpmUssdErrorEvt_ENUM, LNAS_ENTRY);

    pstSsEvt = IMSA_MEM_ALLOC(sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    if ( VOS_NULL_PTR == pstSsEvt )
    {
        /*��ӡ�쳣��Ϣ*/
        IMSA_ERR_LOG("IMSA_SendSpmUssdErrorEvt:ERROR:Alloc Mem fail!");
        TLPS_PRINT2LAYER_ERROR(IMSA_SendSpmUssdErrorEvt_ENUM, LNAS_NULL_PTR);
        return VOS_FALSE;
    }

    IMSA_MEM_SET(pstSsEvt, 0, sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    /* �����¼����� */
    pstSsEvt->SsEvent= TAF_SS_EVT_ERROR;

    /* ����TAF_SS_CALL_INDEPENDENT_EVENT_STRU�е���Ϣ */
    pstSsEvt->ClientId   = (MN_CLIENT_ID_T)usClientId;
    pstSsEvt->OpId     = (MN_OPERATION_ID_T)ucOpId;
    pstSsEvt->OP_Error = 1;
    pstSsEvt->ErrorCode = usError;

    /* ���÷��ͺ��� */
    ulRslt = IMSA_SendImsaSpmSsMsg(pstSsEvt,
                                    sizeof(TAF_SS_CALL_INDEPENDENT_EVENT_STRU));

    IMSA_MEM_FREE(pstSsEvt);

    return ulRslt;
}


VOS_VOID IMSA_USSD_ProcTimerMsgWaitNetRsp(const VOS_VOID *pRcvMsg)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;
    (void)pRcvMsg;

    IMSA_INFO_LOG("IMSA_USSD_ProcTimerMsgWaitNetRsp is entered");
    TLPS_PRINT2LAYER_INFO(IMSA_USSD_ProcTimerMsgWaitNetRsp_ENUM, LNAS_ENTRY);

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MO_SS);
    #endif

    (VOS_VOID)IMSA_SendSpmUssdErrorEvt(pstUssdManager->usClientId,
                            pstUssdManager->ucOpId,
                            TAF_ERR_IMSA_WAIT_NET_TIMEOUT);



    return;
}
VOS_VOID IMSA_USSD_ProcTimerMsgWaitAppRsp(const VOS_VOID *pRcvMsg)
{
    /*IMSA_USSD_MANAGER_STRU              *pstUssdManager;*/
    (void)pRcvMsg;

    IMSA_INFO_LOG("IMSA_USSD_ProcTimerMsgWaitAppRsp is entered");
    TLPS_PRINT2LAYER_INFO(IMSA_USSD_ProcTimerMsgWaitAppRsp_ENUM, LNAS_ENTRY);

    #if (FEATURE_ON == FEATURE_DSDS)
    /*����end notify��Ϣ��RRC��֪ͨRRC�ͷ���Դ*/
    IMSA_SendRrcDsdsEndNotify(IMSA_LRRC_SESSION_TYPE_MT_SS);
    #endif

    /*pstUssdManager = IMSA_USSD_GetEntityAddress();*/
    (VOS_VOID)IMSA_SendSpmUssdErrorEvt(0x3fff,
                            0,
                            TAF_ERR_IMSA_WAIT_APP_TIMEOUT);


    return;
}
VOS_UINT32 IMSA_IsSsConnExist(VOS_VOID)
{
    IMSA_USSD_MANAGER_STRU              *pstUssdManager;

    pstUssdManager = IMSA_USSD_GetEntityAddress();

    if ((IMSA_USSD_MO_CONN_STATE == pstUssdManager->enUssdState) ||
        (IMSA_USSD_MT_CONN_STATE == pstUssdManager->enUssdState))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*lint +e961*/





#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
/* end of ImsaProcUssdMsg.c */






