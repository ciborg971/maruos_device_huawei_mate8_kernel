
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafLog.h"
#include "TafSpmCtx.h"
#include "TafSdcCtx.h"
#include "TafSpmSndImsa.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_SPM_SND_IMSA_C

/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

/*****************************************************************************
  4 ����ʵ��
*****************************************************************************/
#if (FEATURE_IMS == FEATURE_ON)

VOS_VOID TAF_SPM_SendImsaCallOrigReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_ORIG_REQ_STRU        *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_ORIG_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaCallOrigReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_ORIG_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId                     = ID_SPM_IMSA_CALL_ORIG_REQ;
    pstSendImsaMsg->usClientId                  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId                      = pstAppMsg->opId;

    PS_MEM_CPY(&(pstSendImsaMsg->stOrig),
               &(pstAppMsg->unParm.stOrig),
               sizeof(MN_CALL_ORIG_PARAM_STRU));

    pstSendImsaMsg->stOrig.enCallType           = pstAppMsg->unParm.stOrig.enCallType;

    /* VOLTE PhaseI��ΪCS����Ҫ�ٳ���,�����׶�ά�� */
    pstSendImsaMsg->stOrig.ucCsCallRetryFlg     = VOS_FALSE;

    PS_MEM_CPY(&(pstSendImsaMsg->stOrig.stEmergencyCat),
               &(pstAppMsg->unParm.stOrig.stEmergencyCat),
               sizeof(MN_CALL_EMERGENCY_CAT_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaCallOrigReq: Send message failed.");
    }

    return;
}


VOS_VOID TAF_SPM_SendImsaSupsCmdReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_SUPS_CMD_REQ_STRU        *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_SUPS_CMD_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaSupsCmdReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_SUPS_CMD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId                     = ID_SPM_IMSA_CALL_SUPS_CMD_REQ;
    pstSendImsaMsg->usClientId                  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId                      = pstAppMsg->opId;

    PS_MEM_CPY(&(pstSendImsaMsg->stCallMgmtCmd),
                &(pstAppMsg->unParm.stCallMgmtCmd),
                sizeof(MN_CALL_SUPS_PARAM_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaSupsCmdReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_SPM_SendImsaGetCallInfoReq(
    MN_CALL_APP_REQ_MSG_STRU                               *pstAppMsg,
    CALL_IMSA_GET_CALL_INFO_REQ_TYPE_ENMU_UINT8             enReqType                              /* �������� */
)
{
    SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU                   *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetCallInfoReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_GET_CALL_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId     = ID_SPM_IMSA_CALL_GET_CALL_INFO_REQ;
    pstSendImsaMsg->usClientId  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId      = pstAppMsg->opId;

    /* ���ӱ�ʶ��^CLCC��ѯ������Ϣ������ATAʱ����TAFAGENT API��ѯ������Ϣ */
    pstSendImsaMsg->enReqType   = enReqType;

    /* AT��������MN_CALL_APP_GET_INFO_REQû��unParm����Ϣ������Ҳ����д */

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetCallInfoReq: Send message failed.");
    }

    return;
}


VOS_VOID TAF_SPM_SendImsaGetEconfInfoReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU   *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetEconfInfoReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId     = ID_SPM_IMSA_CALL_GET_ECONF_CALLED_INFO_REQ;
    pstSendImsaMsg->usClientId  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId      = pstAppMsg->opId;
    pstSendImsaMsg->enReqType   = CALL_IMSA_GET_CALL_INFO_REQ_TYPE_CLCC;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetEconfInfoReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_SPM_SendImsaGetClprReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_GET_CLPR_REQ_STRU        *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_GET_CLPR_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_GET_CLPR_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetClprReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_GET_CLPR_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid       = PS_PID_IMSA;
    pstSendImsaMsg->ulLength            = sizeof(SPM_IMSA_CALL_GET_CLPR_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId             = ID_SPM_IMSA_CALL_GET_CLPR_REQ;
    pstSendImsaMsg->usClientId          = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId              = pstAppMsg->opId;
    pstSendImsaMsg->callId              = pstAppMsg->callId;

    /* AT��������MN_CALL_APP_CLPR_GET_REQû��unParm����Ϣ������Ҳ����д */

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetClprReq: Send message failed.");
    }

    return;
}



VOS_VOID TAF_SPM_SendImsaStartDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_START_DTMF_REQ_STRU        *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_START_DTMF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_START_DTMF_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaStartDtmfReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_START_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_START_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId     = ID_SPM_IMSA_CALL_START_DTMF_REQ;
    pstSendImsaMsg->usClientId  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId      = pstAppMsg->opId;

    PS_MEM_CPY(&(pstSendImsaMsg->stDtmf),
                &(pstAppMsg->unParm.stDtmf),
                sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaStartDtmfReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_SPM_SendImsaStopDtmfReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_STOP_DTMF_REQ_STRU        *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_STOP_DTMF_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_STOP_DTMF_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaStopDtmfReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_STOP_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_STOP_DTMF_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId     = ID_SPM_IMSA_CALL_STOP_DTMF_REQ;
    pstSendImsaMsg->usClientId  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId      = pstAppMsg->opId;

    PS_MEM_CPY(&(pstSendImsaMsg->stDtmf), &(pstAppMsg->unParm.stDtmf), sizeof(TAF_CALL_DTMF_PARAM_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaStopDtmfReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_SPM_SendImsaGetCdurReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_GET_CUDR_REQ_STRU        *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_GET_CUDR_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_GET_CUDR_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetCdurReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_GET_CUDR_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_GET_CUDR_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId                     = ID_SPM_IMSA_CALL_GET_CUDR_REQ;
    pstSendImsaMsg->usClientId                  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId                      = pstAppMsg->opId;
    pstSendImsaMsg->callId                      = pstAppMsg->callId;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaGetCdurReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_SPM_SendImsaRegisterSsReq(
    struct MsgCB                       *pstMsg
)
{
    SPM_IMSA_REGISTER_SS_REQ_STRU      *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (SPM_IMSA_REGISTER_SS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_REGISTER_SS_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaRegisterSsMsg: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(SPM_IMSA_REGISTER_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(SPM_IMSA_REGISTER_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message name */
    pstSndMsg->ulMsgId                   = ID_SPM_IMSA_REGISTER_SS_REQ;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendImsaRegisterSsMsg: send msg fail!");
        return;
    }

}
VOS_VOID TAF_SPM_SendImsaEraseSsReq(
    struct MsgCB                       *pstMsg
)
{
    SPM_IMSA_ERASE_SS_REQ_STRU         *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (SPM_IMSA_ERASE_SS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_ERASE_SS_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaEraseSsMsg: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(SPM_IMSA_ERASE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(SPM_IMSA_ERASE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message name */
    pstSndMsg->ulMsgId                   = ID_SPM_IMSA_ERASE_SS_REQ;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendImsaEraseSsMsg: send msg fail!");
        return;
    }

}
VOS_VOID TAF_SPM_SendImsaActivateSsReq(
    struct MsgCB                       *pstMsg
)
{
    SPM_IMSA_ACTIVATE_SS_REQ_STRU      *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (SPM_IMSA_ACTIVATE_SS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_ACTIVATE_SS_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaActivateSsMsg: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(SPM_IMSA_ACTIVATE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(SPM_IMSA_ACTIVATE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message name */
    pstSndMsg->ulMsgId                   = ID_SPM_IMSA_ACTIVATE_SS_REQ;


    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendImsaActivateSsMsg: send msg fail!");
        return;
    }

}
VOS_VOID TAF_SPM_SendImsaDeactivateSsReq(
    struct MsgCB                       *pstMsg
)
{
    SPM_IMSA_DEACTIVATE_SS_REQ_STRU    *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (SPM_IMSA_DEACTIVATE_SS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_DEACTIVATE_SS_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaDeactivateSsMsg: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(SPM_IMSA_DEACTIVATE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(SPM_IMSA_DEACTIVATE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message name */
    pstSndMsg->ulMsgId                   = ID_SPM_IMSA_DEACTIVATE_SS_REQ;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendImsaDeactivateSsMsg: send msg fail!");
        return;
    }

}
VOS_VOID TAF_SPM_SendImsaInterrogateSsReq(
    struct MsgCB                       *pstMsg
)
{
    SPM_IMSA_INTERROGATE_SS_REQ_STRU   *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (SPM_IMSA_INTERROGATE_SS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_INTERROGATE_SS_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaInterrogateSsMsg: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(SPM_IMSA_INTERROGATE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(SPM_IMSA_INTERROGATE_SS_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message name */
    pstSndMsg->ulMsgId                   = ID_SPM_IMSA_INTERROGATE_SS_REQ;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendImsaInterrogateSsMsg: send msg fail!");
        return;
    }

}
VOS_VOID TAF_SPM_SendImsaProcessUssSsReq(
    struct MsgCB                       *pstMsg
)
{
    SPM_IMSA_PROCESS_USSD_REQ_STRU     *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (SPM_IMSA_PROCESS_USSD_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_PROCESS_USSD_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaProcessUssSsMsg: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(SPM_IMSA_PROCESS_USSD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(SPM_IMSA_PROCESS_USSD_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message name */
    pstSndMsg->ulMsgId                   = ID_SPM_IMSA_PROCESS_USSD_REQ;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendImsaProcessUssSsMsg: send msg fail!");
        return;
    }
}
VOS_VOID TAF_SPM_SendImsaReleaseSsReq(
    struct MsgCB                       *pstMsg
)
{
    SPM_IMSA_RELEASE_REQ_STRU          *pstSndMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ�ڴ�  */
    pstSndMsg = (SPM_IMSA_RELEASE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_RELEASE_REQ_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaReleaseSsMsg: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* fill in message header */
    pstSndMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSndMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSndMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSndMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSndMsg->ulLength                    = sizeof(SPM_IMSA_RELEASE_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    PS_MEM_CPY( ((VOS_UINT8 *)pstSndMsg + VOS_MSG_HEAD_LENGTH),
                ((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH),
                sizeof(SPM_IMSA_RELEASE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* fill in message name */
    pstSndMsg->ulMsgId                   = ID_SPM_IMSA_RELEASE_REQ;

    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    if (VOS_OK != ulRet)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_SPM_SendImsaReleaseSsMsg: send msg fail!");
        return;
    }
}
VOS_VOID TAF_SPM_SendImsaCallInviteNewPtptReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU                 *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                                WUEPS_PID_TAF,
                                                                sizeof(SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaCallInviteNewPtptReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8*)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId               = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid                 = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid               = PS_PID_IMSA;
    pstSendImsaMsg->ulLength                    = sizeof(SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId                     = ID_SPM_IMSA_CALL_INVITE_NEW_PTPT_REQ;
    pstSendImsaMsg->usClientId                  = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId                      = pstAppMsg->opId;

    /* ��д�Է����뼰�������� */
    pstSendImsaMsg->stNewPtptNumber.enNumType   = pstAppMsg->unParm.stOrig.stDialNumber.enNumType;
    pstSendImsaMsg->stNewPtptNumber.ucNumLen    = pstAppMsg->unParm.stOrig.stDialNumber.ucNumLen;
    if (MN_CALL_MAX_CALLED_BCD_NUM_LEN < pstSendImsaMsg->stNewPtptNumber.ucNumLen)
    {
        pstSendImsaMsg->stNewPtptNumber.ucNumLen = MN_CALL_MAX_CALLED_BCD_NUM_LEN;
    }

    PS_MEM_CPY(&(pstSendImsaMsg->stNewPtptNumber.aucBcdNum[0]),
               &(pstAppMsg->unParm.stOrig.stDialNumber.aucBcdNum[0]),
               pstSendImsaMsg->stNewPtptNumber.ucNumLen);

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
            "TAF_SPM_SendImsaCallInviteNewPtptReq: Send message failed.");
    }

    return;
}

/*lint -restore */

VOS_VOID TAF_SPM_SendImsaCallModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_MODIFY_REQ_STRU      *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_MODIFY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_TAF,
                                                      sizeof(SPM_IMSA_CALL_MODIFY_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaCallModifyReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8 *)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               (sizeof(SPM_IMSA_CALL_MODIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid       = PS_PID_IMSA;
    pstSendImsaMsg->ulLength            = (sizeof(SPM_IMSA_CALL_MODIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId             = ID_SPM_IMSA_CALL_MODIFY_REQ;
    pstSendImsaMsg->usClientId          = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId              = pstAppMsg->opId;

    pstSendImsaMsg->callId              = pstAppMsg->callId;
    pstSendImsaMsg->enCurrCallType      = pstAppMsg->unParm.stModifyReq.enCurrCallType;
    pstSendImsaMsg->enExpectCallType    = pstAppMsg->unParm.stModifyReq.enExpectCallType;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaCallModifyReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_SPM_SendImsaCallAnswerRemoteModifyReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU         *pstSendImsaMsg = VOS_NULL_PTR;

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                      WUEPS_PID_TAF,
                                                      sizeof(SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU));
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaCallAnswerRemoteModifyReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8 *)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               (sizeof(SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid       = PS_PID_IMSA;
    pstSendImsaMsg->ulLength            = sizeof(SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId             = ID_SPM_IMSA_CALL_ANSWER_REMOTE_MODIFY_REQ;
    pstSendImsaMsg->usClientId          = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId              = pstAppMsg->opId;

    pstSendImsaMsg->callId              = pstAppMsg->callId;
    pstSendImsaMsg->enCurrCallType      = pstAppMsg->unParm.stModifyReq.enCurrCallType;
    pstSendImsaMsg->enExpectCallType    = pstAppMsg->unParm.stModifyReq.enExpectCallType;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaCallAnswerRemoteModifyReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_SPM_SendImsaEconfAddUsersReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU     *pstSendImsaMsg  = VOS_NULL_PTR;
    TAF_CALL_ECONF_DIAL_REQ_STRU               *pstEconfDialReq = VOS_NULL_PTR;
    VOS_UINT32                                  ulMsgLen;

    ulMsgLen       = sizeof(SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU);

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_ECONF_ADD_USERS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                               WUEPS_PID_TAF,
                                                               ulMsgLen);
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaEconfAddUsersReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8 *)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               (ulMsgLen - VOS_MSG_HEAD_LENGTH));

    pstEconfDialReq = (TAF_CALL_ECONF_DIAL_REQ_STRU *)&pstAppMsg->unParm;

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid       = PS_PID_IMSA;
    pstSendImsaMsg->ulLength            = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId             = ID_SPM_IMSA_CALL_ECONF_ADD_USERS_REQ;
    pstSendImsaMsg->usClientId          = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId              = pstAppMsg->opId;

    /* �����Ч�ĵ绰���� */
    PS_MEM_CPY(&pstSendImsaMsg->stEconfCalllist, &pstEconfDialReq->stEconfCalllist, sizeof(TAF_CALL_ECONF_CALL_LIST_STRU));

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaEconfAddUsersReq: Send message failed.");
    }

    return;
}


VOS_VOID TAF_SPM_SendImsaEconfDialReq(
    MN_CALL_APP_REQ_MSG_STRU           *pstAppMsg
)
{
    SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU  *pstSendImsaMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen       = sizeof(SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU);

    /* ������Ϣ */
    pstSendImsaMsg = (SPM_IMSA_CALL_ECONF_DIAL_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                                          WUEPS_PID_TAF,
                                                          ulMsgLen);
    if (VOS_NULL_PTR == pstSendImsaMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaEconfDialReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET(((VOS_UINT8 *)pstSendImsaMsg) + VOS_MSG_HEAD_LENGTH,
               0x00,
               (ulMsgLen - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣͷ */
    pstSendImsaMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstSendImsaMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstSendImsaMsg->ulReceiverPid       = PS_PID_IMSA;
    pstSendImsaMsg->ulLength            = ulMsgLen - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSendImsaMsg->ulMsgId             = ID_SPM_IMSA_CALL_ECONF_DIAL_REQ;
    pstSendImsaMsg->usClientId          = pstAppMsg->clientId;
    pstSendImsaMsg->ucOpId              = pstAppMsg->opId;
    pstSendImsaMsg->stDialReq           = pstAppMsg->unParm.stEconfDial;

    /* ������Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pstSendImsaMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF,
                "TAF_SPM_SendImsaEconfDialReq: Send message failed.");
    }

    return;
}

#if 0 /* ���������Ҫ�����ɹ��ĺ��뷢��IMSA����Ҫʹ��������� */

VOS_VOID TAF_SPM_FillImsaEconfCallList(
    TAF_CALL_ECONF_CALL_LIST_STRU      *pstCallList
)
{
    TAF_SPM_CALL_ECONF_INFO_STRU       *pstEconfInfoAddr    = VOS_NULL_PTR;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulCallNum;

    pstEconfInfoAddr    = TAF_SPM_GetCallEconfInfoAddr();
    ulCallNum           = 0;

    for (ulIndex = 0; ulIndex < pstEconfInfoAddr->ucCallNum; ulIndex++)
    {
        if (TAF_CS_CAUSE_SUCCESS == pstEconfInfoAddr->astEconfCheckInfo[ulIndex].enCheckRslt)
        {
            PS_MEM_CPY(&pstCallList->astDialNumber[ulCallNum],
                       &pstEconfInfoAddr->astEconfCheckInfo[ulIndex].stCalledNumber,
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            PS_MEM_CPY(&pstCallList->astSubaddr[ulCallNum],
                       &pstEconfInfoAddr->astEconfCheckInfo[ulIndex].stSubaddr,
                       sizeof(MN_CALL_SUBADDR_STRU));

            ulCallNum++;
        }
    }

    pstCallList->ulCallNum = ulCallNum;

    return;
}
#endif



#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


