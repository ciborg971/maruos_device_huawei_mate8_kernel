
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafLog.h"
#include "TafMmaCtx.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_SND_INTERNAL_MSG_C

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

TAF_MMA_INTERNAL_MSG_BUF_STRU* TAF_MMA_GetNextInternalMsg( VOS_VOID )
{
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstNextMsg = VOS_NULL_PTR;
    TAF_MMA_CONTEXT_STRU               *pstMmaCtx  =  VOS_NULL_PTR;
    VOS_UINT8                           ucNextIndex;

    pstMmaCtx   = TAF_MMA_GetMmaCtxAddr();

    if (pstMmaCtx->stInternalMsgQueue.ucHeader != pstMmaCtx->stInternalMsgQueue.ucTail)
    {
        ucNextIndex     = pstMmaCtx->stInternalMsgQueue.ucHeader;
        pstNextMsg      = (TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstMmaCtx->stInternalMsgQueue.astMmaMsgQueue[ucNextIndex]);

        /* ȡ��һ����Ϣ,ͷָ�����ƫ�� */
        (pstMmaCtx->stInternalMsgQueue.ucHeader)++;
        (pstMmaCtx->stInternalMsgQueue.ucHeader) %= TAF_MMA_MAX_MSG_QUEUE_SIZE;

        return pstNextMsg;
    }

    TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_GetNextInternalMsg:Empty Internal Msg");

    return VOS_NULL_PTR;

}
TAF_MMA_INTERNAL_MSG_BUF_STRU *TAF_MMA_GetIntMsgSendBuf(
    VOS_UINT32                          ulLen
)
{
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstTafMmaMsg        = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;

    pstInternalMsgQueue         = &(TAF_MMA_GetMmaCtxAddr()->stInternalMsgQueue);

    /* ���������л�ȡ��Ϣ������ָ�� */
    pstTafMmaMsg = ( TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->stSendMsgBuf);

    if (ulLen > TAF_MMA_MAX_MSG_BUFFER_LEN )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_GetIntMsgSendBuf: Buffer full" );

        TAF_MMA_SndOmInternalMsgQueueInfo(VOS_FALSE, VOS_FALSE);

        return VOS_NULL_PTR;
    }

    /* ��������Ϣ���嵥Ԫ */
    PS_MEM_SET(pstTafMmaMsg, 0x00, sizeof(TAF_MMA_INTERNAL_MSG_BUF_STRU));

    /* ���ػ�����ָ�� */
    return pstTafMmaMsg;
}
VOS_VOID  TAF_MMA_SndInternalMsg(
    VOS_VOID                           *pSndMsg
)
{
    VOS_UINT8                           ucMsgPnt;
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstMmaMsg           = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_QUEUE_STRU    *pstInternalMsgQueue = VOS_NULL_PTR;
    TAF_MMA_INTERNAL_MSG_BUF_STRU      *pstSndMsg           = VOS_NULL_PTR;

    pstInternalMsgQueue                 = &(TAF_MMA_GetMmaCtxAddr()->stInternalMsgQueue);
    pstSndMsg                           = (TAF_MMA_INTERNAL_MSG_BUF_STRU*)pSndMsg;

    /* 1. �ж��ڲ���Ϣ�������Ƿ����� */
    ucMsgPnt = pstInternalMsgQueue->ucTail;
    if ( ((ucMsgPnt + 1) % TAF_MMA_MAX_MSG_QUEUE_SIZE) == pstInternalMsgQueue->ucHeader )
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_SndInternalMsg:Warning: The Queue is full.");
        TAF_MMA_SndOmInternalMsgQueueInfo(VOS_TRUE, VOS_FALSE);
        return;
    }

    /* 2. ȡ��һ����Ϣ���嵥Ԫ */
    pstMmaMsg = (TAF_MMA_INTERNAL_MSG_BUF_STRU *)&(pstInternalMsgQueue->astMmaMsgQueue[ucMsgPnt]);

    /* 3. �ж���Ϣ�����Ƿ�Ƿ� */
    if ( pstSndMsg->ulLength > TAF_MMA_MAX_MSG_BUFFER_LEN)
    {
        TAF_WARNING_LOG(UEPS_PID_MSCC, "TAF_MMA_SndInternalMsg:Warning: ulBufLen is too long.");
        return;
    }

    TAF_NORMAL_LOG1(WUEPS_PID_MMA, "TAF_MMA_SndInternalMsg: usMsgID is ", pstMmaMsg->usMsgID);

    /* 4. ���ڲ���Ϣ���͵��ڲ���Ϣ������ */
    PS_MEM_CPY(pstMmaMsg, pstSndMsg, sizeof(TAF_MMA_INTERNAL_MSG_BUF_STRU));

    /* �����ڲ���Ϣ������ */
    pstInternalMsgQueue->ucTail++;
    pstInternalMsgQueue->ucTail         %= TAF_MMA_MAX_MSG_QUEUE_SIZE;

    return;
}
VOS_VOID TAF_MMA_SndInterPowerInitReq(VOS_VOID)
{
    TAF_MMA_INTER_POWER_INIT_REQ_STRU  *pstPowerInitMsg = VOS_NULL_PTR;

    pstPowerInitMsg  = (TAF_MMA_INTER_POWER_INIT_REQ_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_MMA,
                                                                                       sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU));

    if (VOS_NULL_PTR == pstPowerInitMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                      "TAF_MMA_SndMmaPowerInitReq: ERROR:Memory Alloc Error for pstMsg!");

        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstPowerInitMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstPowerInitMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstPowerInitMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstPowerInitMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstPowerInitMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstPowerInitMsg->MsgHeader.ulMsgName       = MMA_MMA_INTER_POWER_INIT;
    pstPowerInitMsg->MsgHeader.ulLength        = sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��Ҫ�����ⲿ��Ϣ,��Ϊ�ϵ�ʱ���ⲿ��Ϣ�����ڲ���Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_MMA, pstPowerInitMsg))
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA,
                      "TAF_MMA_SndMmaPowerInitReq: Send message failed.");
    }

    return;
}
VOS_VOID TAF_MMA_SndInterUsimChangeInd(VOS_VOID)
{
    TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU              *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU);

    pstInternalMsg  = (TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_INTER_USIM_STATUS_CHANGE_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(TAF_MMA_INTER_USIM_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}
VOS_VOID TAF_MMA_SndSimlocakStatusChangeInd(VOS_VOID)
{
    TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU                *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU);

    pstInternalMsg  = (TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND;
    pstInternalMsg->MsgHeader.ulLength        = sizeof(TAF_MMA_SIM_LOCK_STATUS_CHANGE_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}
VOS_VOID TAF_MMA_SndPhoneModeRsltInd(
    TAF_MMA_PHONE_MODE_RESULT_ENUM_UINT8                    enRslt
)
{
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU   *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(TAF_MMA_PHONE_MODE_RSLT_IND_STRU);

    pstInternalMsg  = (TAF_MMA_PHONE_MODE_RSLT_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_PHONE_MODE_RSLT_IND;
    pstInternalMsg->MsgHeader.ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enRslt                    = enRslt;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}

#if (FEATURE_IMS == FEATURE_ON)
VOS_VOID TAF_MMA_SndImsSwitchRsltInd(
    TAF_MMA_IMS_SWITCH_RESULT_ENUM_UINT8                    enRslt
)
{
    TAF_MMA_IMS_SWITCH_RSLT_IND_STRU   *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(TAF_MMA_IMS_SWITCH_RSLT_IND_STRU);

    pstInternalMsg  = (TAF_MMA_IMS_SWITCH_RSLT_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_IMS_SWITCH_RSLT_IND;
    pstInternalMsg->MsgHeader.ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enRslt                    = enRslt;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}
#endif

/* Added by h00313353 for Iteration 13, 2015-5-5, begin */
/*****************************************************************************
 �� �� ��  : TAF_MMA_SndSysCfgRsltInd
 ��������  : ����System Config״̬���˳����ָʾ��Ϣ
 �������  : enRslt:״̬���˳������Ϣ
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��5��
    ��    ��   : h00313353
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_MMA_SndSysCfgRsltInd(
    TAF_MMA_SYS_CFG_RSLT_ENUM_UINT8                         enRslt
)
{
    TAF_MMA_SYS_CFG_RSLT_STRU          *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(TAF_MMA_SYS_CFG_RSLT_STRU);

    pstInternalMsg  = (TAF_MMA_SYS_CFG_RSLT_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_SYS_CFG_RSLT_IND;
    pstInternalMsg->MsgHeader.ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    pstInternalMsg->enRslt                    = enRslt;

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}

/* Added by h00313353 for Iteration 13, 2015-5-5, end */

/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */

VOS_VOID TAF_MMA_SndInterSysCfgSetReq(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfg
)
{
    TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU);

    pstInternalMsg  = (TAF_MMA_INTER_SYS_CFG_SET_REQ_STRU*)TAF_MMA_GetIntMsgSendBuf(ulLen);

    if (VOS_NULL_PTR == pstInternalMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_UINT8*)pstInternalMsg + VOS_MSG_HEAD_LENGTH, 0,
              ulLen - VOS_MSG_HEAD_LENGTH);

    pstInternalMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInternalMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInternalMsg->MsgHeader.ulMsgName       = MMA_MMA_INTER_SYS_CFG_SET_REQ;
    pstInternalMsg->MsgHeader.ulLength        = ulLen - VOS_MSG_HEAD_LENGTH;
    PS_MEM_CPY(&(pstInternalMsg->stSysCfgPara), pstSysCfg, sizeof(TAF_MMA_SYS_CFG_PARA_STRU));

    TAF_MMA_SndInternalMsg(pstInternalMsg);

    return;
}

/* Modified by l00301449 for Iteration 13, 2015-04-09, end */


VOS_VOID TAF_MMA_SndInterMmaAbortInd(VOS_VOID)
{
    TAF_MMA_INTER_ABORT_IND_STRU        *pstSndMsg = VOS_NULL_PTR;

    pstSndMsg = (TAF_MMA_INTER_ABORT_IND_STRU*)TAF_MMA_GetIntMsgSendBuf(sizeof(TAF_MMA_INTER_ABORT_IND_STRU));
    if (VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    PS_MEM_SET(pstSndMsg, 0, sizeof(TAF_MMA_INTER_ABORT_IND_STRU));

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMA;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSndMsg->MsgHeader.ulLength          = sizeof(TAF_MMA_INTER_ABORT_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->MsgHeader.ulMsgName         = MMA_MMA_INTER_ABORT_IND;

    TAF_MMA_SndInternalMsg(pstSndMsg);

    return;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



