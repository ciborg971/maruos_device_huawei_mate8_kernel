

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "xcc_xcall_pif.h"
#include "VcCallInterface.h"

#include "TafXCallProcXcc.h"
#include "TafXCallCtx.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndXcc.h"
#include "TafXCallSndMma.h"
#include "TafXCallSndVc.h"
#include "TafXCallProcApp.h"
#include "TafXCallTimerMgmt.h"
#include "TafSdcCtx.h"

/* Added by w00351686 for CDMA Iteration 16 2015-7-25 begin */
#include "TafSdcLib.h"
/* Added by w00351686 for CDMA Iteration 16 2015-7-25 end */

/* Added by y00322978 for CDMA Iteration 17, 2015-7-15, begin */
#include "TafMmaSndOm.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-15, end */
#include "TafLog.h"
#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_PROC_XCC_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XCALL_RcvXccCallOrigCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_ORIG_CALL_CNF_STRU       *pstOrigCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          ulRemainTimeLen;
    TAF_XCALL_CALL_ENTITY_STRU         *pstOrigCallEntity = VOS_NULL_PTR;   /* 原呼叫实体指针 */

    pstOrigCnf = (XCC_XCALL_ORIG_CALL_CNF_STRU *)pMsg;

    /* 判断带上来的call id是否合法 */
    ulRslt = TAF_XCALL_IsAvailCallId(pstOrigCnf->ucCallId);
    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    pstCallEntity       = TAF_XCALL_GetCallEntityAddr(pstOrigCnf->ucCallId);
    usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    enCallType          = TAF_XCALL_GetCallType(pstOrigCnf->ucCallId);

    /* 更新原因值 */
    TAF_XCALL_UpdateCcCause(pstOrigCnf->ucCallId, TAF_XCALL_MapXccCauseToCsCause(pstOrigCnf->enCause));

    if (TAF_XCC_CAUSE_SUCCESS != pstOrigCnf->enCause)
    {
        /* 是重拨原因值并且周期性重拨定时器剩余时长大于或等于重拨间隔定时器时长,是则重拨,否则不重拨 */
        ulRemainTimeLen = 0;
        TAF_XCALL_GetRemainTimerLen(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId, &ulRemainTimeLen);

        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-14, begin */
        if (ulRemainTimeLen >= TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN)
        {
            if (TAF_XCC_FAIL_LAYER_L2 == pstOrigCnf->enFailLayer)
            {
                pstCallEntity->ucIsL2ErrReOrig = VOS_TRUE;

                if (TAF_XCC_FAIL_LAYER_L3 != pstCallEntity->enLastReOrigErr)
                {
                    /*原因值相同, 或者第一次重拨失败，则重拨计数累加 */
                    pstCallEntity->ucReOrigCount++;
                }
                else
                {
                    /*原因值不同则重新重1开始计数*/
                    pstCallEntity->ucReOrigCount   = 1;

                }

                pstCallEntity->enLastReOrigErr = TAF_XCC_FAIL_LAYER_L2;

            }
            else
            {
                pstCallEntity->ucIsL2ErrReOrig = VOS_FALSE;

                if (TAF_XCC_FAIL_LAYER_L2 != pstCallEntity->enLastReOrigErr)
                {
                    pstCallEntity->ucReOrigCount++;
                }
                else
                {
                    pstCallEntity->ucReOrigCount   = 1;
                }

                pstCallEntity->enLastReOrigErr = TAF_XCC_FAIL_LAYER_L3;

            }

            /* 紧急呼无条件触发搜网，会通知XSD模块 */
            if (MN_CALL_TYPE_EMERGENCY == enCallType)
            {
                if (TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT == pstOrigCnf->enCause)
                {
                    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, pstOrigCnf->ucCallId);
                    return;
                }
                else if ( (TAF_XCC_CAUSE_EMERGENCY_CALL_FLASHED == pstOrigCnf->enCause)
                       || (TAF_XCC_CAUSE_L2_ACK_TIME_OUT == pstOrigCnf->enCause)
                       || (TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE == pstOrigCnf->enCause) )
                {
                    /* 修改原被叫的呼叫实体中Type和Called Num信息 */
                    if (TAF_XCC_CALLID_NULL != pstOrigCnf->ucOrigCallId)
                    {
                        /* 将当前的呼叫实体信息复制到原有呼叫实体中 */
                        pstOrigCallEntity               = TAF_XCALL_GetCallEntityAddr(pstOrigCnf->ucOrigCallId);

                        enCallType                      = TAF_XCALL_GetCallType(pstOrigCnf->ucOrigCallId);

                        pstOrigCallEntity->enCallType   = MN_CALL_TYPE_EMERGENCY;

                        PS_MEM_CPY(&(pstOrigCallEntity->stCalledNumber), &(pstCallEntity->stCalledNumber), sizeof(MN_CALL_CALLED_NUM_STRU));

                        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId);

                        TAF_XCALL_SndCallReleaseInd(pstOrigCnf->ucCallId);

                        /* 发送原有呼叫的CallEnd */
                        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

                        /* 发送新的紧急呼的Call Success */
                        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(MN_CALL_TYPE_EMERGENCY));

                        /* 释放当前的呼叫实体 */
                        TAF_XCALL_FreeCallEntity(pstOrigCnf->ucCallId);

                        return;
                    }
                }
                else
                {
                    /* Added by h00313353 for Iteration 17, 2015-7-29, begin */
                    /* 重拨前启动重拨定时器 */
                    TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, pstOrigCnf->ucCallId);
                    /* Added by h00313353 for Iteration 17, 2015-7-29, end */
                    TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF, usClientId,TAF_XCALL_BuildMmaCallType(enCallType), TAF_XCALL_MapXccCauseToCsCause(pstOrigCnf->enCause));

                    return;
                }


            }
            else if (VOS_TRUE == TAF_XCALL_IsNeedSilentRedial(pstOrigCnf->enCause))
            {
                /* 只有需要触发搜网的原因值，才会通知XSD模块，否则只是启动定时器，并不通知MMA模块 */
                TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, pstOrigCnf->ucCallId);
                if (VOS_TRUE == TAF_XCALL_IsNeedRedialSystemAcquire(pstOrigCnf->enCause))
                {
                    TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF, usClientId,TAF_XCALL_BuildMmaCallType(enCallType), TAF_XCALL_MapXccCauseToCsCause(pstOrigCnf->enCause));
                }

                return;
            }
            else
            {

            }

        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-14, end */
        }

        /* 停止重拨定时器,如果定时器未启动或call id不一致则跳过 */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId);

        /* 上报呼叫失败 */
        TAF_XCALL_SndCallReleaseInd(pstOrigCnf->ucCallId);

        /* 给MMA发送TAF_MMA_1X_CALL_END_NTF消息 */
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

        /* 释放呼叫实体 */
        TAF_XCALL_FreeCallEntity(pstOrigCnf->ucCallId);

        if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
        {
            /* 清除SDC中CS呼叫标志 */
            TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        }

        return;
    }

    /* 停止重拨定时器,如果定时器未启动或call id不一致则跳过 */
    TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, pstOrigCnf->ucCallId);

    /* 更新呼叫状态，1X模式下，协议规定主叫建立后的状态为active */
    TAF_XCALL_UpdateCallState(pstOrigCnf->ucCallId, MN_CALL_S_ACTIVE);

    /* 上报呼叫成功 */
    TAF_XCALL_SndCallConnectInd(pstOrigCnf->ucCallId);

    /* 给MMA发送TAF_MMA_1X_CALL_SUCCESS_NTF消息 */
    TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

    return;
}
VOS_VOID TAF_XCALL_RcvXccCallHangUpCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_HANGUP_CALL_CNF_STRU                         *pstHangUpCnf = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;
    MN_CALL_STATE_ENUM_U8                                   enCallState;
    VOS_UINT32                                              ulNumOfCalls;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                                              ulModuleId;
    VOS_UINT16                                              usClientId;
    VOS_UINT8                                               ucOpId;
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;

    pstHangUpCnf = (XCC_XCALL_HANGUP_CALL_CNF_STRU *)pMsg;

    enEvt        = TAF_XCALL_SS_PROG_EVT_BUTT;
    enSubseqOp   = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    /* 判断带上来的call id是否合法 */
    ulRslt = TAF_XCALL_IsAvailCallId(pstHangUpCnf->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    enCallState = TAF_XCALL_GetCallState(pstHangUpCnf->ucCallId);

    /* 判断是否为idle态 */
    if (MN_CALL_S_IDLE == enCallState)
    {
        return;
    }

    /* 保存当前call id的module id，用于release all上报 */
    ulModuleId = TAF_XCALL_GetClientInfo(pstHangUpCnf->ucCallId)->ulModuleId;
    usClientId = TAF_XCALL_GetClientInfo(pstHangUpCnf->ucCallId)->usClientId;
    ucOpId     = TAF_XCALL_GetClientInfo(pstHangUpCnf->ucCallId)->ucOpId;

    if (MN_CALL_DIR_MO == TAF_XCALL_GetCallDir(pstHangUpCnf->ucCallId))
    {
        enCallType  = TAF_XCALL_GetCallType(pstHangUpCnf->ucCallId);

        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));
    }

    /* 给APP上报MN_CALL_EVT_RELEASED事件 */
    TAF_XCALL_SndCallReleaseInd(pstHangUpCnf->ucCallId);

    TAF_XCALL_GetSsKeyEvent(pstHangUpCnf->ucCallId, &enEvt, &enSubseqOp);

    if (TAF_XCALL_SS_PROG_EVT_REL == enEvt)
    {
        /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId, pstHangUpCnf->ucCallId, MN_CALL_SS_RES_SUCCESS);

        TAF_XCALL_DeRegSsKeyEvent(pstHangUpCnf->ucCallId, TAF_XCALL_SS_PROG_EVT_REL);
    }

    /* 清空对应的实体信息 */
    TAF_XCALL_FreeCallEntity(pstHangUpCnf->ucCallId);

    if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
    {
        /* 清除SDC中CS呼叫标志 */
        TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    /* 如果没有呼叫实体 */
    if (0 == ulNumOfCalls)
    {
        /* 给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }
}
VOS_VOID TAF_XCALL_RcvXccCallDiscInd(VOS_VOID *pMsg)
{
    XCC_XCALL_CALL_DISC_IND_STRU                           *pstCallDiscInd = VOS_NULL_PTR;
    VOS_UINT32                                              ulRslt;
    MN_CALL_STATE_ENUM_U8                                   enCallState;
    VOS_UINT32                                              ulNumOfCalls;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                                              ulModuleId;
    VOS_UINT16                                              usClientId;
    VOS_UINT8                                               ucOpId;
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;
    VOS_UINT8                                               ucCallId;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;

    pstCallDiscInd = (XCC_XCALL_CALL_DISC_IND_STRU *)pMsg;

    enEvt          = TAF_XCALL_SS_PROG_EVT_BUTT;
    enSubseqOp     = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    /* 判断带上来的call id是否合法 */
    ulRslt = TAF_XCALL_IsAvailCallId(pstCallDiscInd->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        /* 容错判断: XCC在收到XCALL的incoming rsp之前如果收到AS的terminal ind，XCC不知道call id */
        ulRslt = TAF_XCALL_GetCallIdFromConnectId(pstCallDiscInd->ucConnectId, &ucCallId);

        if (VOS_TRUE != ulRslt)
        {
            return;
        }
    }
    else
    {
        ucCallId = pstCallDiscInd->ucCallId;
    }

    enCallState = TAF_XCALL_GetCallState(ucCallId);

    /* 判断是否为非idle态 */
    if (MN_CALL_S_IDLE == enCallState)
    {
        return;
    }

    /* 保存当前call id的client info */
    ulModuleId = TAF_XCALL_GetClientInfo(ucCallId)->ulModuleId;
    usClientId = TAF_XCALL_GetClientInfo(ucCallId)->usClientId;
    ucOpId     = TAF_XCALL_GetClientInfo(ucCallId)->ucOpId;

    /* 更新原因值 */
    TAF_XCALL_UpdateCcCause(ucCallId, TAF_XCALL_MapXccCauseToCsCause(pstCallDiscInd->enCause));

    /* 更新挂断方向 */
    TAF_XCALL_UpdateDiscCallDir(ucCallId, VOS_FALSE);

    enCallType = TAF_XCALL_GetCallType(ucCallId);

    if ((MN_CALL_DIR_MO         == TAF_XCALL_GetCallDir(ucCallId))
     || (MN_CALL_TYPE_EMERGENCY == enCallType))
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));
    }

    /* 给APP上报MN_CALL_EVT_RELEASED事件 */
    TAF_XCALL_SndCallReleaseInd(ucCallId);

    TAF_XCALL_GetSsKeyEvent(ucCallId, &enEvt, &enSubseqOp);

    /* 如果正在挂断过程中，网络挂断，给APP回复挂断成功 */
    if (TAF_XCALL_SS_PROG_EVT_REL == enEvt)
    {
        /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId, ucCallId, MN_CALL_SS_RES_SUCCESS);

        TAF_XCALL_DeRegSsKeyEvent(ucCallId, TAF_XCALL_SS_PROG_EVT_REL);
    }

    /* 如果正在接听过程中，网络挂断，给APP回复接听失败 */
    if (TAF_XCALL_SS_PROG_EVT_ANS == enEvt)
    {
        /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId,
                                ucCallId, MN_CALL_SS_RES_FAIL);

        TAF_XCALL_DeRegSsKeyEvent(ucCallId, TAF_XCALL_SS_PROG_EVT_ANS);
    }

    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */
    /* 清空dtmf缓存 */
    TAF_XCALL_CleanDtmfBuff(ucCallId);

    TAF_XCALL_StopTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, ucCallId);

    /* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */

    if (TAF_XCC_CAUSE_NDSS_REDIAL_IND == pstCallDiscInd->enCause)
    {
        pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

        /* 重新迁呼叫状态到dialing状态 */
        pstCallEntity->enCallState = MN_CALL_S_DIALING;

        /* 上报呼叫发起事件 */
        TAF_XCALL_SndCallOrigInd(ucCallId);

        return;
    }

    /* 清空对应的实体信息 */
    TAF_XCALL_FreeCallEntity(ucCallId);

    if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
    {
        /* 清除SDC中CS呼叫标志 */
        TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    /* 如果没有呼叫实体，给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
    if (0 == ulNumOfCalls)
    {
        TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
    }

    return;
}


VOS_VOID TAF_XCALL_RcvXccCallIncomingInd(VOS_VOID *pMsg)
{
    XCC_XCALL_INCOMING_CALL_IND_STRU   *pstIncomingCallInd = VOS_NULL_PTR;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT8                           ucCallId;
    VOS_UINT32                          ulRslt;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    MN_CALL_TYPE_ENUM_U8                enCallType;

    pstIncomingCallInd = (XCC_XCALL_INCOMING_CALL_IND_STRU *)pMsg;

    /* 判断SO的有效性 */
    if (VOS_TRUE != TAF_XCALL_IsAvailVoiceCallSo(TAF_XCALL_ConvertXccSoToXcallSo(pstIncomingCallInd->enSo)))
    {
        TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_FAIL, pstIncomingCallInd->ucCallId, pstIncomingCallInd->ucConnectId);

        return;
    }

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aucCallIds);

    /* 当前存在一路dialing状态的紧急呼叫，XCC会将该MO转成flash消息发出去，XCALL不做判断
        当前存在一路dialing状态的普通呼叫，XCC会将该MO拒掉，XCALL不做判断
        当前存在一路active状态的呼叫，如果有新的来电callid相同，上报incoming，并将状态改为incoming状态。否则认为异常 */
    if (0 != ulNumOfCalls)
    {
        if (aucCallIds[0] == pstIncomingCallInd->ucCallId)
        {
            /* 记录发起call业务用户的信息(AT/STK) */
            TAF_XCALL_UpdateClientInfo(aucCallIds[0],
                                       WUEPS_PID_AT,
                                       MN_CLIENT_ID_BROADCAST,
                                       0);
            /* 更新SO */
            TAF_XCALL_UpdateSo(aucCallIds[0], TAF_XCALL_ConvertXccSoToXcallSo(pstIncomingCallInd->enSo));

            /* 更新By pass Flag */
            TAF_XCALL_UpdateAlertAnsByPassFlg(aucCallIds[0], pstIncomingCallInd->ucIsAlertAnsByPass);

            /* 更新Connect Reference */
            TAF_XCALL_UpdateConnectRef(aucCallIds[0], pstIncomingCallInd->ucConRef);

            /* 更新Connect Id */
            TAF_XCALL_UpdateConnectId(aucCallIds[0], pstIncomingCallInd->ucConRef);

            /* 更新呼叫状态 */
            TAF_XCALL_UpdateCallState(aucCallIds[0], MN_CALL_S_INCOMING);

            /* 更新呼叫类型 */
            TAF_XCALL_UpdateCallType(aucCallIds[0], MN_CALL_TYPE_VOICE);

            /* 更新发起呼叫Dir */
            TAF_XCALL_UpdateCallDir(aucCallIds[0], MN_CALL_DIR_MT);

            /* 更新来电号码 */
            TAF_XCALL_UpdateCallingNum(aucCallIds[0], &(pstIncomingCallInd->stCallingPartyNum));

            /* 给APP上报MN_CALL_EVT_INCOMING事件 */
            TAF_XCALL_SndCallIncomingInd(aucCallIds[0]);

        }
        else
        {
            TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_FAIL, pstIncomingCallInd->ucCallId, pstIncomingCallInd->ucConnectId);
        }

        return;
    }

    /* 如果有主叫则先中止主叫并停止相关重拨定时器,然后分配被叫的call id */
    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));
    TAF_XCALL_GetCallsByState(MN_CALL_S_DIALING, &ulNumOfCalls, aucCallIds);

    if (0 != ulNumOfCalls)
    {
        pstCallEntity       = TAF_XCALL_GetCallEntityAddr(aucCallIds[0]);
        usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);

        if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[0]))
        {
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD,   aucCallIds[0]);
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[0]);

            enCallType          = TAF_XCALL_GetCallType(aucCallIds[0]);

            TAF_XCALL_UpdateCcCause(aucCallIds[0], TAF_CS_CAUSE_XCALL_UNKNOWN);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

            /* 给APP上报MN_CALL_EVT_RELEASED事件 */
            TAF_XCALL_SndCallReleaseInd(aucCallIds[0]);

            /* 清空对应的实体信息 */
            TAF_XCALL_FreeCallEntity(aucCallIds[0]);

            if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
            {
                /* 清除SDC中CS呼叫标志 */
                TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
            }
        }
    }

    /* 分配一个呼叫实体 */
    ucCallId = 0;

    ulRslt   = TAF_XCALL_AllocCallId(&ucCallId);

    /* 实体分配失败，回复rsp失败 */
    if (VOS_TRUE != ulRslt)
    {
        TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_FAIL, pstIncomingCallInd->ucCallId, pstIncomingCallInd->ucConnectId);

        return;
    }

    TAF_XCALL_CreateMtCallEntity(ucCallId, WUEPS_PID_AT, pstIncomingCallInd);

    /* 设置SDC中CS呼叫标志 */
    TAF_SDC_SetCsCallExistFlg(VOS_TRUE);

    /* 给XCC回复ID_XCALL_XCC_INCOMING_CALL_RSP消息 */
    TAF_XCALL_SndXccIncomingCallRsp(XCC_XCALL_RESULT_SUCC, ucCallId, pstIncomingCallInd->ucConnectId);

    /* 给APP上报MN_CALL_EVT_INCOMING事件 */
    TAF_XCALL_SndCallIncomingInd(ucCallId);

    return;
}
VOS_VOID TAF_XCALL_RcvXccCallAnswerCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_ANSWER_CALL_CNF_STRU     *pstCallAnsCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MN_CALL_STATE_ENUM_U8               enCallState;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                          ulModuleId;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;

    pstCallAnsCnf = (XCC_XCALL_ANSWER_CALL_CNF_STRU *)pMsg;

    /* 判断带上来的call id是否合法 */
    ulRslt = TAF_XCALL_IsAvailCallId(pstCallAnsCnf->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    /* 判断SO的有效性 */
    if (TAF_XCALL_GetSo(pstCallAnsCnf->ucCallId) != TAF_XCALL_ConvertXccSoToXcallSo(pstCallAnsCnf->enSo))
    {
        return;
    }

    enCallState = TAF_XCALL_GetCallState(pstCallAnsCnf->ucCallId);

    /* 判断是否为incoming状态 */
    if (MN_CALL_S_INCOMING != enCallState)
    {
        return;
    }

    /* 保存当前call id的client info */
    ulModuleId = TAF_XCALL_GetClientInfo(pstCallAnsCnf->ucCallId)->ulModuleId;
    usClientId = TAF_XCALL_GetClientInfo(pstCallAnsCnf->ucCallId)->usClientId;
    ucOpId     = TAF_XCALL_GetClientInfo(pstCallAnsCnf->ucCallId)->ucOpId;

    TAF_XCALL_DeRegSsKeyEvent(pstCallAnsCnf->ucCallId, TAF_XCALL_SS_PROG_EVT_ANS);

    /* 更新原因值 */
    TAF_XCALL_UpdateCcCause(pstCallAnsCnf->ucCallId, TAF_XCALL_MapXccCauseToCsCause(pstCallAnsCnf->enCause));

    if (TAF_XCC_CAUSE_SUCCESS == pstCallAnsCnf->enCause)
    {
        /* 更新呼叫状态 */
        TAF_XCALL_UpdateCallState(pstCallAnsCnf->ucCallId, MN_CALL_S_ACTIVE);

        /* 更新connect ref */
        TAF_XCALL_UpdateConnectRef(pstCallAnsCnf->ucCallId, pstCallAnsCnf->ucConRef);

        /* 更新SO */
        TAF_XCALL_UpdateSo(pstCallAnsCnf->ucCallId, TAF_XCALL_ConvertXccSoToXcallSo(pstCallAnsCnf->enSo));

        /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId,
                                pstCallAnsCnf->ucCallId, MN_CALL_SS_RES_SUCCESS);

        /* 给APP上报MN_CALL_EVT_CONNECT事件 */
        TAF_XCALL_SndCallConnectInd(pstCallAnsCnf->ucCallId);

    }
    else
    {
        /* 给APP上报MN_CALL_EVT_RELEASED事件 */
        TAF_XCALL_SndCallReleaseInd(pstCallAnsCnf->ucCallId);

        /* 给APP回复MN_CALL_EVT_SS_CMD_RSLT事件 */
        TAF_XCALL_SndSupsResult(ulModuleId, usClientId, ucOpId,
                                pstCallAnsCnf->ucCallId, MN_CALL_SS_RES_FAIL);

        /* 清空对应的实体信息 */
        TAF_XCALL_FreeCallEntity(pstCallAnsCnf->ucCallId);

        if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
        {
            /* 清除SDC中CS呼叫标志 */
            TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        }

        ulNumOfCalls = 0;

        PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

        TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

        /* 如果没有呼叫实体 */
        if (0 == ulNumOfCalls)
        {
            /* 给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
            TAF_XCALL_SndCallAllReleaseInd(ulModuleId);
        }
    }
}


VOS_VOID TAF_XCALL_RcvXccCallConnectInd(VOS_VOID *pMsg)
{
    XCC_XCALL_CALL_CONNECT_IND_STRU    *pstCallConnectInd = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    MN_CALL_STATE_ENUM_U8               enCallState;
    VOS_UINT8                           ucIsAlertAnsByPass;

    pstCallConnectInd = (XCC_XCALL_CALL_CONNECT_IND_STRU *)pMsg;

    /* 判断带上来的call id是否合法 */
    ulRslt = TAF_XCALL_IsAvailCallId(pstCallConnectInd->ucCallId);

    if (VOS_TRUE != ulRslt)
    {
        return;
    }

    /* 判断SO的有效性 */
    if (TAF_XCALL_GetSo(pstCallConnectInd->ucCallId) != TAF_XCALL_ConvertXccSoToXcallSo(pstCallConnectInd->enSo))
    {
        return;
    }

    enCallState        = TAF_XCALL_GetCallState(pstCallConnectInd->ucCallId);

    ucIsAlertAnsByPass = TAF_XCALL_GetAlertAnsByPassFlg(pstCallConnectInd->ucCallId);

    /* 只有bypass为VOS_TRUE才有connect ind: 对应的状态为incoming，且bypass为VOS_TRUE */
    if ((MN_CALL_S_INCOMING != enCallState)
     || (VOS_FALSE == ucIsAlertAnsByPass))
    {
        return;
    }

    /* 更新呼叫状态 */
    TAF_XCALL_UpdateCallState(pstCallConnectInd->ucCallId, MN_CALL_S_ACTIVE);

    /* 给APP上报MN_CALL_EVT_CONNECT事件 */
    TAF_XCALL_SndCallConnectInd(pstCallConnectInd->ucCallId);

    return;
}
VOS_VOID TAF_XCALL_RcvXccSendFlashCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_SEND_FLASH_CNF_STRU      *pstSndFlashCnf = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;

    pstSndFlashCnf = (XCC_XCALL_SEND_FLASH_CNF_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstSndFlashCnf->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stFlashClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stFlashClientInfo.ucOpId;

    /* 给应用回复TAF_CALL_EVT_SEND_FLASH_RSLT消息 */
    if (TAF_XCC_CAUSE_SUCCESS == pstSndFlashCnf->enCause)
    {
        TAF_XCALL_SndFlashRslt(usClientId, ucOpId, VOS_OK);
    }
    else
    {
        TAF_XCALL_SndFlashRslt(usClientId, ucOpId, VOS_ERR);
    }

    return;
}


VOS_VOID TAF_XCALL_RcvXccInfoRecInd(VOS_VOID *pMsg)
{
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd = VOS_NULL_PTR;

    pstInfoRecInd = (XCC_XCALL_INFO_REC_IND_STRU *)pMsg;



    /* 发送display info */
    TAF_XCALL_SndDisplayInfoInd(pstInfoRecInd);

    /* 发送ext display info */
    TAF_XCALL_SndExtDisplayInfoInd(pstInfoRecInd);

    /* 发送connected num */
    TAF_XCALL_SndConnNumInfoInd(pstInfoRecInd);

    /* 发送called num */
    TAF_XCALL_SndCalledNumInfoInd(pstInfoRecInd);

    /* 发送redirection num */
    TAF_XCALL_SndRedirNumInfoInd(pstInfoRecInd);

    /* 发送line ctrl */
    TAF_XCALL_SndLineCtrlInfoInd(pstInfoRecInd);

    /* 发送calling num or signal，or CCWA */
    TAF_XCALL_SndCallingNumSignalInfoInd(pstInfoRecInd);

    TAF_XCALL_SavePiOfCallingPartyNum(pstInfoRecInd);

    return;
}
VOS_VOID TAF_XCALL_RcvXccCodecOpenInd(VOS_VOID *pMsg)
{
    CALL_VC_CHANNEL_INFO_STRU           stChannelInfo;
    XCC_XCALL_CODEC_OPEN_IND_STRU      *pstCodecOpen = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           i;

    PS_MEM_SET(&stChannelInfo, 0 ,sizeof(stChannelInfo));
    pstCodecOpen = (XCC_XCALL_CODEC_OPEN_IND_STRU *)pMsg;

    stChannelInfo.bChannelEnable            = VOS_TRUE;
    stChannelInfo.stChannelParam.enMode     = CALL_VC_MODE_CDMA;
    stChannelInfo.stChannelParam.enCallType = CALL_VC_CALL_TYPE_NORMAL_CALL;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstCodecOpen->enSo,
                                        &stChannelInfo.stChannelParam.enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 给VC发送CALL_VC_CHANNEL_OPEN消息 */
    TAF_XCALL_SndVcChannelInfoInd(CALL_VC_CHANNEL_OPEN,
                                  &stChannelInfo);


    /* 更新SO */
    for (i = 1; i <= TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if (VOS_TRUE == TAF_XCALL_GetCallEntityAddr(i)->ulUsed)
        {
            TAF_XCALL_UpdateSo(i, (TAF_XCALL_SO_TYPE_ENUM_UINT16)pstCodecOpen->enSo);
        }
    }

    /* TO DO:需要确认是否需要给AT上报channel info */
    return;
}
VOS_VOID TAF_XCALL_RcvXccCodecCloseInd(VOS_VOID *pMsg)
{
    CALL_VC_CHANNEL_INFO_STRU           stChannelInfo;

    PS_MEM_SET(&stChannelInfo, 0 ,sizeof(stChannelInfo));

    stChannelInfo.bChannelEnable        = VOS_FALSE;
    stChannelInfo.stChannelParam.enMode = CALL_VC_MODE_CDMA;

    /* 给VC发送CALL_VC_CHANNEL_CLOSE消息 */
    TAF_XCALL_SndVcChannelInfoInd(CALL_VC_CHANNEL_CLOSE,
                                  &stChannelInfo);

    return;
}
VOS_VOID TAF_XCALL_RcvXccCodecChangedInd(VOS_VOID *pMsg)
{
    CALL_VC_CHANNEL_INFO_STRU           stChannelInfo;
    XCC_XCALL_CODEC_CHANGED_IND_STRU   *pstCodecChange = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           i;

    PS_MEM_SET(&stChannelInfo, 0 ,sizeof(stChannelInfo));
    pstCodecChange = (XCC_XCALL_CODEC_CHANGED_IND_STRU *)pMsg;

    stChannelInfo.bChannelEnable            = VOS_TRUE;
    stChannelInfo.stChannelParam.enMode     = CALL_VC_MODE_CDMA;
    stChannelInfo.stChannelParam.enCallType = CALL_VC_CALL_TYPE_NORMAL_CALL;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstCodecChange->enSo,
                                        &stChannelInfo.stChannelParam.enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 给VC发送CALL_VC_CHANNEL_PARA_CHANGE消息 */
    TAF_XCALL_SndVcChannelInfoInd(CALL_VC_CHANNEL_PARA_CHANGE,
                                  &stChannelInfo);

    /* 更新SO */
    for (i = 1; i <= TAF_XCALL_CALL_ENTITY_MAX_NUM; i++)
    {
        if (VOS_TRUE == TAF_XCALL_GetCallEntityAddr(i)->ulUsed)
        {
            TAF_XCALL_UpdateSo(i, (TAF_XCALL_SO_TYPE_ENUM_UINT16)pstCodecChange->enSo);
        }
    }

    return;

}


VOS_VOID TAF_XCALL_RcvXccSoCtrlMsgInd(VOS_VOID *pMsg)
{
    XCC_XCALL_SO_CTRL_MSG_IND_STRU     *pstSoCtrlMsg = VOS_NULL_PTR;
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;
    VOS_UINT32                          ulRslt;

    pstSoCtrlMsg = (XCC_XCALL_SO_CTRL_MSG_IND_STRU *)pMsg;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstSoCtrlMsg->enSo,
                                        &enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 给VC发送VC_CALL_SO_CTRL_MSG_IND消息 */
    TAF_XCALL_SndVcSoCtrlMsgInd(enCodecType,
                                pstSoCtrlMsg->ucRateReduc,
                                pstSoCtrlMsg->ucMobileToMobile,
                                pstSoCtrlMsg->ucInitCodec);

    return;
}
VOS_VOID TAF_XCALL_RcvXccSoCtrlOrderInd(VOS_VOID *pMsg)
{
    XCC_XCALL_SO_CTRL_ORDER_IND_STRU   *pstSoCtrlOrder = VOS_NULL_PTR;
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;
    VOS_UINT32                          ulRslt;

    pstSoCtrlOrder = (XCC_XCALL_SO_CTRL_ORDER_IND_STRU *)pMsg;

    ulRslt = TAF_XCALL_MapSoToCodecType(pstSoCtrlOrder->enSo,
                                        &enCodecType);

    if (VOS_OK != ulRslt)
    {
        return;
    }

    /* 给VC发送VC_CALL_SO_CTRL_ORDER_IND消息 */
    TAF_XCALL_SndVcSoCtrlOrderInd(enCodecType, pstSoCtrlOrder->ucORDQ);

    return;

}
VOS_UINT32 TAF_XCALL_MapSoToCodecType(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enSo,
    CALL_VC_CODEC_TYPE_ENUM_U8         *penCodecType
)
{
    if (TAF_CDMA_SO_3_EVRC == enSo)
    {
        *penCodecType = CALL_VC_CODEC_TYPE_EVRC;
    }
    else if (TAF_CDMA_SO_68_EVRC_B == enSo)
    {
        *penCodecType = CALL_VC_CODEC_TYPE_EVRCB;
    }
    else
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


TAF_XCALL_SO_TYPE_ENUM_UINT16 TAF_XCALL_ConvertXccSoToXcallSo(
    TAF_CDMA_SO_TYPE_ENUM_UINT16        enXccSo
)
{
    TAF_XCALL_SO_TYPE_ENUM_UINT16       enXcallSo;

    if (TAF_CDMA_SO_3_EVRC == enXccSo)
    {
        enXcallSo = TAF_XCALL_SO_3_EVRC;
    }
    else if (TAF_CDMA_SO_68_EVRC_B == enXccSo)
    {
        enXcallSo = TAF_XCALL_SO_68_EVRC_B;
    }
    else if (TAF_CDMA_SO_73_EVRC_NW == enXccSo)
    {
        enXcallSo = TAF_XCALL_SO_73_EVRC_NW;
    }
    else
    {
        enXcallSo = TAF_XCALL_SO_BUTT;
    }

    return enXcallSo;
}

/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, begin */
/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, begin */

VOS_VOID TAF_XCALL_RcvXccSendBurstDTMFCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_BURST_DTMF_CNF_STRU      *pstSndBurstDTMFCnf = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucRslt;
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;

    pstSndBurstDTMFCnf = (XCC_XCALL_BURST_DTMF_CNF_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstSndBurstDTMFCnf->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    /* 清除等待XCC回复的标识 */
    enWaitForXCCDTMFCnfFlag = TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstSndBurstDTMFCnf->ucCallId);
    if (TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF != enWaitForXCCDTMFCnfFlag)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
                         "TAF_XCALL_RcvXccSendBurstDTMFCnf():Current WaitForXCCDTMFCnfFlag is error",
                         enWaitForXCCDTMFCnfFlag);
        return;
    }

    TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstSndBurstDTMFCnf->ucCallId, TAF_XCALL_WAIT_NO_XCC_CNF);

    /* DTMF缓存处理 ，如果定时器超时或编码失败，进行DTMF缓存处理；如果是呼叫释放或状态异常，则清缓存  */
    switch (pstSndBurstDTMFCnf->enCause)
    {
        case TAF_XCC_CAUSE_SUCCESS:
            ucRslt = VOS_OK;
            TAF_XCALL_ProcDtmfBuffer(pstSndBurstDTMFCnf->ucCallId);
            break;

        /* Move TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE to clean buffer
            add new cause TAF_XCC_CAUSE_L2_ACK_FAIL
        */
        case TAF_XCC_CAUSE_ENCODE_FAIL:
        case TAF_XCC_CAUSE_L2_ACK_TIME_OUT:
        case TAF_XCC_CAUSE_L2_ACK_FAIL:

            ucRslt = VOS_ERR;
            TAF_XCALL_ProcDtmfBuffer(pstSndBurstDTMFCnf->ucCallId);
            break;

        case TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE:
        case TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE:
        case TAF_XCC_CAUSE_ABNORMAL_STATE:

            ucRslt = VOS_ERR;
            TAF_XCALL_CleanDtmfBuff(pstSndBurstDTMFCnf->ucCallId);
            TAF_XCALL_StopTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, pstSndBurstDTMFCnf->ucCallId);
            break;

        default:
            ucRslt = VOS_ERR;
            break;
    }

    TAF_XCALL_SndBurstDTMFRslt(usClientId, ucOpId, ucRslt);

    return;
}
/* Modified by l00324781 for CDMA Iteration 16, 2015-7-24, end */
/* Added by f279542 for CDMA 1X Iteration 4, 2014-11-10, end */


VOS_UINT32 TAF_XCALL_IsNeedSilentRedial(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    /* 先判断原因值是否满足重拨条件 */
    switch (enCause)
    {
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
        case TAF_XCC_CAUSE_EMERGENCY_CALL_ABORT:
        case TAF_XCC_CAUSE_NORMAL_RELEASE:
        case TAF_XCC_CAUSE_SO_REJ:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}
VOS_UINT32 TAF_XCALL_IsNeedRedialSystemAcquire(
    TAF_XCC_CAUSE_ENUM_UINT32           enCause
)
{
    /* 先判断原因值是否满足重拨条件，满足重拨条件，才可能需要触发搜网 */
    if (VOS_FALSE == TAF_XCALL_IsNeedSilentRedial(enCause))
    {
        return VOS_FALSE;
    }


    /* 根据CDG 143，以下原因值触发重拨时搜网 */
    switch (enCause)
    {
        case TAF_XCC_CAUSE_MAX_ACCESS_PROBES:
        case TAF_XCC_CAUSE_REORDER:
        case TAF_XCC_CAUSE_ACCESS_DENYIED:
        case TAF_XCC_CAUSE_SIGNAL_FADE:
        case TAF_XCC_CAUSE_CHANNEL_ASSIGN_TIMEOUT:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}



VOS_VOID TAF_XCALL_RcvXccNdssResultInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallFound;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT8                           ucCallId;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallEntity   = VOS_NULL_PTR;
    XCC_XCALL_NDSS_RESULT_IND_STRU     *pstNdssResultInd = VOS_NULL_PTR;

    pstNdssResultInd = (XCC_XCALL_NDSS_RESULT_IND_STRU *)pMsg;

    ucCallId    = 0;
    ucCallFound = VOS_FALSE;

    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

        if ((VOS_TRUE                           == pstXcallEntity->ulUsed)
         && (TAF_CS_CAUSE_XCALL_NDSS_REDIAL_IND == pstXcallEntity->enCause))
        {
            ucCallFound = VOS_TRUE;
            break;
        }
    }

    if (VOS_FALSE == ucCallFound)
    {
        /* 重拨呼叫未找到 */
        return;
    }

    if (XCC_XCALL_NDSS_RESULT_SUCCESS == pstNdssResultInd->enNsddResult)
    {
        /* 发起重拨 */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);
    }
    else
    {
        /* 给APP上报MN_CALL_EVT_RELEASED事件 */
        TAF_XCALL_SndCallReleaseInd(ucCallId);

        /* 清空对应的实体信息 */
        TAF_XCALL_FreeCallEntity(ucCallId);

        if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
        {
            /* 清除SDC中CS呼叫标志 */
            TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
        }

        ulNumOfCalls = 0;

        PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

        TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

        /* 如果没有呼叫实体，给APP上报MN_CALL_EVT_ALL_RELEASED事件 */
        if (0 == ulNumOfCalls)
        {
            TAF_XCALL_SndCallAllReleaseInd(TAF_XCALL_GetClientInfo(ucCallId)->ulModuleId);
        }
    }

    return;
}

/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, begin */

VOS_VOID TAF_XCALL_RcvXccSendContDTMFCnf(VOS_VOID *pMsg)
{
    XCC_XCALL_SEND_CONT_DTMF_CNF_STRU  *pstSndContDTMFCnf = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;
    VOS_UINT8                           ucRslt;
    TAF_XCALL_WAIT_XCC_CNF_TYPE_UINT8   enWaitForXCCDTMFCnfFlag;
    VOS_UINT32                          ulStartAndStopContDtmfIntervalLen;

    pstSndContDTMFCnf = (XCC_XCALL_SEND_CONT_DTMF_CNF_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstSndContDTMFCnf->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    /* 清除等待XCC回复CONT DTMF CNF的标识 */
    /* 如果是Start Contf Dtmf Req的cnf，暂时不处理缓存，启动定时器，定时器超时后，再处理缓存，发送Stop
        对于清空缓存的原因值，不在此列，直接清空缓存。
    */
    enWaitForXCCDTMFCnfFlag = TAF_XCALL_GetWaitForXCCDTMFCnfFlag(pstSndContDTMFCnf->ucCallId);
    if (TAF_XCALL_WAIT_XCC_CNF_START_CONT_DTMF == enWaitForXCCDTMFCnfFlag)
    {
        /* 收到Start Cont DTMF的响应，清除等待标志位 */
        TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstSndContDTMFCnf->ucCallId, TAF_XCALL_WAIT_NO_XCC_CNF);

        if (TAF_XCC_CAUSE_SUCCESS == pstSndContDTMFCnf->enCause)
        {
            /* 启动定时器，定时器超时后，再处理缓存 */
            ulStartAndStopContDtmfIntervalLen = TAF_XCALL_GetStartAndStopContDtmfIntervalLen();
            TAF_XCALL_StartTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,
                                ulStartAndStopContDtmfIntervalLen,
                                pstSndContDTMFCnf->ucCallId);

            /* 返回结果，退出 */
            TAF_XCALL_SndContDTMFRslt(usClientId, ucOpId, VOS_OK);

            return;
        }
        else if ((TAF_XCC_CAUSE_L2_ACK_FAIL == pstSndContDTMFCnf->enCause)
              || (TAF_XCC_CAUSE_ENCODE_FAIL == pstSndContDTMFCnf->enCause)
              || (TAF_XCC_CAUSE_L2_ACK_TIME_OUT == pstSndContDTMFCnf->enCause))
        {
            /* 启动定时器，定时器超时后，再处理缓存 */
            ulStartAndStopContDtmfIntervalLen = TAF_XCALL_GetStartAndStopContDtmfIntervalLen();
            TAF_XCALL_StartTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL,
                                ulStartAndStopContDtmfIntervalLen,
                                pstSndContDTMFCnf->ucCallId);

            /* 返回结果，退出 */
            TAF_XCALL_SndContDTMFRslt(usClientId, ucOpId, VOS_ERR);

            return;
        }
        else /* 其它原因，清空缓存，不需要启动定时器 */
        {
            /* do nothing */
        }
    }
    else if (TAF_XCALL_WAIT_XCC_CNF_BURST_DTMF == enWaitForXCCDTMFCnfFlag)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF,
                        "TAF_XCALL_RcvXccSendContDTMFCnf():Current WaitForXCCDTMFCnfFlag is error",
                        enWaitForXCCDTMFCnfFlag);
        return;
    }
    else
    {
        /* 收到Stop Cont DTMF的响应，清除等待标志位 */
        TAF_XCALL_SetWaitForXCCDTMFCnfFlag(pstSndContDTMFCnf->ucCallId, TAF_XCALL_WAIT_NO_XCC_CNF);
    }

    /* CONT DTMF缓存处理 ，如果定时器超时或编码失败，进行CONT DTMF缓存处理；如果是呼叫释放或状态异常，则清缓存  */
    switch (pstSndContDTMFCnf->enCause)
    {
        case TAF_XCC_CAUSE_SUCCESS:
            ucRslt = VOS_OK;
            TAF_XCALL_ProcDtmfBuffer(pstSndContDTMFCnf->ucCallId);
            break;

        case TAF_XCC_CAUSE_L2_ACK_FAIL:
        case TAF_XCC_CAUSE_ENCODE_FAIL:
        case TAF_XCC_CAUSE_L2_ACK_TIME_OUT:
            ucRslt = VOS_ERR;
            TAF_XCALL_ProcDtmfBuffer(pstSndContDTMFCnf->ucCallId);
            break;

        case TAF_XCC_CAUSE_CANNOT_FIND_CALL_INSTANCE:
        case TAF_XCC_CAUSE_WAIT_L2_ACK_CALL_RELEASE:
        case TAF_XCC_CAUSE_ABNORMAL_STATE:
            ucRslt = VOS_ERR;
            TAF_XCALL_CleanDtmfBuff(pstSndContDTMFCnf->ucCallId);
            TAF_XCALL_StopTimer(TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL, pstSndContDTMFCnf->ucCallId);

            break;

        default:
            ucRslt = VOS_ERR;
            break;
    }

    TAF_XCALL_SndContDTMFRslt(usClientId, ucOpId, ucRslt);

    return;
}
/* Added by l00324781 for CDMA Iteration 16, 2015-7-24, end */



VOS_VOID TAF_XCALL_RcvXccBurstDtmfInd(VOS_VOID *pMsg)
{
    XCC_XCALL_BURST_DTMF_IND_STRU      *pstBurstDTMFInd = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;

    /* Added by w00351686 for CDMA Iteration 16 2015-7-25 begin */
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl = VOS_NULL_PTR;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    /* ^CBURSTDTMF at command controlled by CURC */
    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                              TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                              TAF_SDC_RPT_CMD_CBURSTDTMF))
    {
        return;
    }
    /* Added by w00351686 for CDMA Iteration 16 2015-7-25 end */

    pstBurstDTMFInd = (XCC_XCALL_BURST_DTMF_IND_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstBurstDTMFInd->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    if (MN_CALL_S_ACTIVE == TAF_XCALL_GetCallState(pstBurstDTMFInd->ucCallId))
    {
        /* send TAF_CALL_EVT_RCV_BURST_DTMF_IND */
        TAF_XCALL_SndBurstDTMFInd(usClientId, ucOpId, pstBurstDTMFInd);

        return;
    }

    /* If current call state is not MN_CALL_S_ACTIVE, the message is discarded. */
    return;
}


/* Added by k902809 for CDMA Iteration 16, 2015-7-25, begin */
/*****************************************************************************
Function Name   :   TAF_XCALL_RcvXccContDtmfInd
Description     :   The function receives the Continuous DTMF Ind from XCC
                    and sends TAF_CALL_EVT_RCV_CONT_DTMF_IND to AT.
Input parameters:   pMsg - Pointer to XCC Cont DTMF Ind message.

Output parameters:  None
Return Value    :   None
Modify History:
    1)  Date    :   2015-07-25
        Author  :   K00902809
        Modify content :Create
*****************************************************************************/
VOS_VOID TAF_XCALL_RcvXccContDtmfInd(VOS_VOID *pMsg)
{
    XCC_XCALL_CONT_DTMF_IND_STRU       *pstContDTMFInd  = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucOpId;

    /* Added by w00351686 for CDMA Iteration 16 2015-7-25 begin */
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl = VOS_NULL_PTR;

    pstCurcRptCtrl  = TAF_SDC_GetCurcRptCtrl();

    /* ^CCONTDTMF at command controlled by CURC */
    if (VOS_TRUE != TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg, TAF_SDC_CMD_RPT_CTRL_BY_CURC, TAF_SDC_RPT_CMD_CCONTDTMF))
    {
        return;
    }
    /* Added by w00351686 for CDMA Iteration 16 2015-7-25 end */

    pstContDTMFInd = (XCC_XCALL_CONT_DTMF_IND_STRU *)pMsg;

    pstCallEntity = TAF_XCALL_GetCallEntityAddr(pstContDTMFInd->ucCallId);

    usClientId = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    ucOpId     = pstCallEntity->stClientInfo.ucOpId;

    if(MN_CALL_S_ACTIVE == TAF_XCALL_GetCallState(pstContDTMFInd->ucCallId))
    {
        TAF_XCALL_SndContDTMFInd(usClientId, ucOpId, pstContDTMFInd);
        return;
    }

    /* If current call state is not MN_CALL_S_ACTIVE, the message is discarded. */
    return;
}

/* Added by k902809 for CDMA Iteration 16, 2015-7-25, end */

VOS_VOID TAF_XCALL_SavePiOfCallingPartyNum(
    XCC_XCALL_INFO_REC_IND_STRU        *pstInfoRecInd
)
{
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity = VOS_NULL_PTR;

    pstCallEntity                     = TAF_XCALL_GetCallEntityAddr(pstInfoRecInd->ucCallId);

    if (VOS_TRUE == pstInfoRecInd->bitOpCallingNumInfo)
    {
        pstCallEntity->ucPi = pstInfoRecInd->stCallingNumInfo.ucPi;
    }
    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
