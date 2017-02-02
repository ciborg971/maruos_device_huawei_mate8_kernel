


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "vos.h"
#include "TafTypeDef.h"
#include "MnCallApi.h"
#include "MnComm.h"
#include "MnCallImsaProc.h"
#include "MnCallSendCc.h"
#include "MnCallFacilityEncode.h"
#include "MnCall.h"
#include "MnCallMgmt.h"
#include "TafSdcCtx.h"
#include "MnCallReqProc.h"
#include "NasCcIe.h"
#include "MnCallProcNvim.h"
#include "MnCallBcProc.h"
#include "MnCallReqProc.h"
#include "SpmImsaInterface.h"
#include "NasStkInterface.h"

#include "MnCallMnccProc.h"

#include "MnCallSendApp.h"
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e(767)*/
#define    THIS_FILE_ID        PS_FILE_ID_MN_CALL_IMSA_PROC_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/


/*****************************************************************************
  6 ��������
*****************************************************************************/
#if (FEATURE_ON == FEATURE_IMS)

VOS_VOID TAF_CALL_ProcImsaMsg(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                    *pstImsaMsg = VOS_NULL_PTR;

    pstImsaMsg = (MSG_HEADER_STRU *)pMsg;

    switch (pstImsaMsg->ulMsgName)
    {
        case ID_IMSA_CALL_SRVCC_CALL_INFO_NOTIFY:
            TAF_CALL_ProcImsaSrvccCallInfoNtf((CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU *)pstImsaMsg);
            break;

        case ID_IMSA_CALL_MSG_SYNC_IND:
            TAF_CALL_ProcImsaMsgSyncInd((IMSA_CALL_MSG_SYNC_IND_STRU *)pstImsaMsg);
            break;

        case ID_IMSA_CALL_CCWA_CAP_NOTIFY:
            TAF_CALL_ProcImsaCcwaCapNtf((IMSA_CALL_CCWA_CAP_NOTIFY_STRU *)pstImsaMsg);
            break;

        default:
            MN_WARN_LOG("TAF_CALL_ProcImsaMsg:Error MsgName");
            break;
    }

    return;
}




VOS_VOID TAF_CALL_ProcImsaSrvccCallInfoNtf(
    CALL_IMSA_SRVCC_CALL_INFO_NOTIFY_STRU                  *pstCallInfoNtf
)
{
    VOS_UINT8                           ucRealCallNum;
    MNCC_ENTITY_STATUS_STRU             astEntitySta[MNCC_MAX_ENTITY_NUM];

    /* ӳ�����ʵ�� */
    TAF_CALL_CreateCallEntitiesWithImsCallInfo(pstCallInfoNtf->ucCallNum, &(pstCallInfoNtf->astCallInfo[0]), pstCallInfoNtf->ucStartedHifiFlag);

    /* ��ʼ��DTMF������� */
    TAF_CALL_InitDtmfCtx();

    /* ����DTMF������Ϣ */
    TAF_CALL_ProcSrvccDtmfBuffInfo(&(pstCallInfoNtf->stDtmfBuffInfo));

    /* ��CALLģ��ĺ�����Ϣӳ���CCģ��ĺ�����Ϣ */
    PS_MEM_SET(&astEntitySta[0], 0, sizeof(MNCC_ENTITY_STATUS_STRU)*MNCC_MAX_ENTITY_NUM);

    TAF_CALL_MapCallInfoToCcInfo(&astEntitySta[0], &ucRealCallNum);

    /* ֪ͨCCģ�������ϢMNCC_SRVCC_CALL_INFO_NOTIFY */
    TAF_CALL_SendCcSrvccCallInfoNtf(ucRealCallNum, astEntitySta);

    return;
}
VOS_VOID TAF_CALL_SendImsaSrvccStatusNtf(
    CALL_IMSA_SRVCC_STATUS_ENUM_UINT32  enSrvccSta
)
{
    CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_CALL_SendImsaSrvccStatusNtf: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(CALL_IMSA_SRVCC_STATUS_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->enSrvccStatus               = enSrvccSta;

    /* fill in message name */
    pstSndMsg->ulMsgId                     = ID_CALL_IMSA_SRVCC_STATUS_NOTIFY;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_SendImsaSrvccStatusNtf: send msg fail!");
        return;
    }

    return;
}
VOS_VOID TAF_CALL_ConvertOrigReqMsg(
    SPM_IMSA_CALL_ORIG_REQ_STRU        *pstSrcMsg,
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg
)
{
    /* ��Ϣͷ����Ͳ�����д�� */

    pstDstMsg->clientId = pstSrcMsg->usClientId;
    pstDstMsg->opId     = pstSrcMsg->ucOpId;
    pstDstMsg->enReq    = MN_CALL_APP_ORIG_REQ;

    /* ���ƺ��з�����Ϣ���� */
    PS_MEM_CPY(&(pstDstMsg->unParm.stOrig), &(pstSrcMsg->stOrig), sizeof(MN_CALL_ORIG_PARAM_STRU));
}


VOS_VOID TAF_CALL_ConvertSupsCmdReqMsg(
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU    *pstSrcMsg,
    MN_APP_CALL_SUPS_REQ_STRU          *pstDstMsg
)
{
    /* ��Ϣͷ����Ͳ�����д�� */

    pstDstMsg->opID       = pstSrcMsg->ucOpId;
    pstDstMsg->usClientId = pstSrcMsg->usClientId;
    pstDstMsg->ulMsgId    = MN_CALL_APP_SUPS_CMD_REQ;

    PS_MEM_CPY(&(pstDstMsg->stSupsPara), &(pstSrcMsg->stCallMgmtCmd), sizeof(MN_CALL_SUPS_PARAM_STRU));
}
VOS_VOID TAF_CALL_ConvertStartDtmfReqMsg(
    SPM_IMSA_CALL_START_DTMF_REQ_STRU  *pstSrcMsg,
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg
)
{
    /* ��Ϣͷ����Ͳ�����д�� */

    pstDstMsg->callId   = pstSrcMsg->stDtmf.CallId;
    pstDstMsg->clientId = pstSrcMsg->usClientId;
    pstDstMsg->opId     = pstSrcMsg->ucOpId;
    pstDstMsg->enReq    = MN_CALL_APP_START_DTMF_REQ;

    PS_MEM_CPY(&(pstDstMsg->unParm.stDtmf), &(pstSrcMsg->stDtmf), sizeof(TAF_CALL_DTMF_PARAM_STRU));
}
VOS_VOID TAF_CALL_ConvertStopDtmfReqMsg(
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU   *pstSrcMsg,
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg
)
{
    pstDstMsg->callId = pstSrcMsg->stDtmf.CallId;
    pstDstMsg->clientId = pstSrcMsg->usClientId;
    pstDstMsg->opId     = pstSrcMsg->ucOpId;
    pstDstMsg->enReq    = MN_CALL_APP_STOP_DTMF_REQ;

    PS_MEM_CPY(&(pstDstMsg->unParm.stDtmf), &(pstSrcMsg->stDtmf), sizeof(TAF_CALL_DTMF_PARAM_STRU));
}


VOS_VOID TAF_CALL_ProcOrigReq(SPM_IMSA_CALL_ORIG_REQ_STRU *pstOrigReq)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg = VOS_NULL_PTR;
    /* ������Ϣ�ڴ�  */
    pstDstMsg = (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcOrigReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_CALL_APP_REQ_MSG_STRU));

    /* ����ת����Ϣ���͵�call�ɴ�����ڲ���Ϣ */
    TAF_CALL_ConvertOrigReqMsg(pstOrigReq, pstDstMsg);

    /* ����callģ��Orig Req��Ϣ������ */
    MN_CALL_CallOrigReqProc(pstDstMsg->clientId,
                            pstDstMsg->opId,
                            pstDstMsg->callId,
                            (MN_CALL_ORIG_PARAM_STRU*)&(pstDstMsg->unParm));

    /* �ͷŷ�����ڴ�ռ� */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}


VOS_VOID TAF_CALL_ProcSupsCmdReq(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *pstSupsCmdReq)
{
    MN_APP_CALL_SUPS_REQ_STRU          *pstDstMsg = VOS_NULL_PTR;
    /* ������Ϣ�ڴ�  */
    pstDstMsg = (MN_APP_CALL_SUPS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_APP_CALL_SUPS_REQ_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSupsCmdReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_APP_CALL_SUPS_REQ_STRU));

    /* ����ת����Ϣ���͵�call�ɴ�����ڲ���Ϣ */
    TAF_CALL_ConvertSupsCmdReqMsg(pstSupsCmdReq, pstDstMsg);

    /* ����callģ��SupsCmdReq��Ϣ������ */
    MN_CALL_CallSupsCmdReqProc((struct MsgCB *)pstDstMsg);

    /* �ͷŷ�����ڴ�ռ� */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}


VOS_VOID TAF_CALL_ProcStartDtmfReq(SPM_IMSA_CALL_START_DTMF_REQ_STRU *pstStartDtmfReq)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CS_CAUSE_ENUM_UINT32            ulResult;

    /* ������Ϣ�ڴ�  */
    pstDstMsg = (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSupsCmdReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_CALL_APP_REQ_MSG_STRU));

    /* ����ת����Ϣ���͵�call�ɴ�����ڲ���Ϣ */
    TAF_CALL_ConvertStartDtmfReqMsg(pstStartDtmfReq, pstDstMsg);

    /* ���TCH��û�з��䣬ֱ�Ӿͻ��� */
    if (VOS_FALSE == MN_CALL_GetTchStatus())
    {
        PS_MEM_SET(&stDtmfInfo, 0, sizeof(TAF_CALL_DTMF_INFO_STRU));

        stDtmfInfo.opId        = pstDstMsg->opId;
        stDtmfInfo.usClientId  = pstDstMsg->clientId;
        stDtmfInfo.CallId      = pstDstMsg->unParm.stDtmf.CallId;
        stDtmfInfo.cKey        = pstDstMsg->unParm.stDtmf.cKey;
        stDtmfInfo.usOffLength = pstDstMsg->unParm.stDtmf.usOffLength;
        stDtmfInfo.usOnLength  = pstDstMsg->unParm.stDtmf.usOnLength;

        ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
    }
    else
    {
        /* ����callģ��StartDtmfReq��Ϣ������ */
        TAF_CALL_RcvStartDtmfReq((struct MsgCB *)pstDstMsg);
    }


    /* �ͷŷ�����ڴ�ռ� */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}
VOS_VOID TAF_CALL_ProcStopDtmfReq(SPM_IMSA_CALL_STOP_DTMF_REQ_STRU *pstStopDtmfReq)
{
    MN_CALL_APP_REQ_MSG_STRU           *pstDstMsg = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CS_CAUSE_ENUM_UINT32            ulResult;

    /* ������Ϣ�ڴ�  */
    pstDstMsg = (MN_CALL_APP_REQ_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(MN_CALL_APP_REQ_MSG_STRU));
    if (VOS_NULL_PTR == pstDstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSupsCmdReq: ERROR:Memory Alloc is fail!");

        return;
    }

    PS_MEM_SET(pstDstMsg, 0, sizeof(MN_CALL_APP_REQ_MSG_STRU));

    /* ����ת����Ϣ���͵�call�ɴ�����ڲ���Ϣ */
    TAF_CALL_ConvertStopDtmfReqMsg(pstStopDtmfReq, pstDstMsg);

        /* ���TCH��û�з��䣬ֱ�Ӿͻ��� */
    if (VOS_FALSE == MN_CALL_GetTchStatus())
    {
        PS_MEM_SET(&stDtmfInfo, 0, sizeof(TAF_CALL_DTMF_INFO_STRU));

        stDtmfInfo.opId        = pstDstMsg->opId;
        stDtmfInfo.usClientId  = pstDstMsg->clientId;
        stDtmfInfo.CallId      = pstDstMsg->unParm.stDtmf.CallId;
        stDtmfInfo.cKey        = pstDstMsg->unParm.stDtmf.cKey;
        stDtmfInfo.usOffLength = pstDstMsg->unParm.stDtmf.usOffLength;
        stDtmfInfo.usOnLength  = pstDstMsg->unParm.stDtmf.usOnLength;

        ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             ulResult);
    }
    else
    {
        /* ����callģ��pstStopDtmfReq��Ϣ */
        TAF_CALL_RcvStopDtmfReq((struct MsgCB *)pstDstMsg);
    }

    /* �ͷŷ�����ڴ�ռ� */
    PS_FREE_MSG(WUEPS_PID_TAF, pstDstMsg);
}
VOS_VOID TAF_CALL_ProcSyncServiceMsgReq(MSG_HEADER_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case ID_SPM_IMSA_CALL_ORIG_REQ:
            TAF_CALL_ProcOrigReq((SPM_IMSA_CALL_ORIG_REQ_STRU *)pstMsg);
            break;

        case ID_SPM_IMSA_CALL_SUPS_CMD_REQ:
            TAF_CALL_ProcSupsCmdReq((SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *)pstMsg);
            break;

        case ID_SPM_IMSA_CALL_START_DTMF_REQ:
            TAF_CALL_ProcStartDtmfReq((SPM_IMSA_CALL_START_DTMF_REQ_STRU *)pstMsg);
            break;

        case ID_SPM_IMSA_CALL_STOP_DTMF_REQ:
            TAF_CALL_ProcStopDtmfReq((SPM_IMSA_CALL_STOP_DTMF_REQ_STRU *)pstMsg);
            break;

        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcSyncMsgReq: This is an illegal message!");
            break;

    }
}



VOS_VOID TAF_CALL_ProcImsaMsgSyncInd(IMSA_CALL_MSG_SYNC_IND_STRU *pstMsgSyncInd)
{
    VOS_UINT8                           i;

    /* �����Ϣ��Ŀ�Ƿ�Ϸ� */
    if ((0 == pstMsgSyncInd->ucMsgNum)
     || (IMSA_CALL_MSG_SYNC_MAX_NUM < pstMsgSyncInd->ucMsgNum))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_CALL_ProcImsaMsgSyncInd: message number is invalid!");

        return;
    }

    for (i = 0; i < pstMsgSyncInd->ucMsgNum; i++)
    {
        TAF_CALL_ProcSyncServiceMsgReq((MSG_HEADER_STRU *)&(pstMsgSyncInd->astMsgArray[i]));
    }
}
VOS_VOID TAF_CALL_ProcImsaCcwaCapNtf(
    IMSA_CALL_CCWA_CAP_NOTIFY_STRU     *pstCcwaCapNtf
)
{
    TAF_CALL_CCWA_CTRL_MODE_ENUM_U8     enCcwaCtrlMode;

    enCcwaCtrlMode = TAF_CALL_GetCcwaCtrlMode();

    /* ���NV2340����CCWA����ģʽ����UE���ƣ��򲻴���ID_IMSA_CALL_CCWA_CAP_NOTIFY */
    if (TAF_CALL_CCWA_CTRL_BY_IMS != enCcwaCtrlMode)
    {
        return;
    }

    /* ��IMS���CCWA�������浽ȫ�ֱ��� */
    TAF_CALL_SetCcwaiFlg(pstCcwaCapNtf->ucCcwaCap);

    return;
}


#endif










#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




