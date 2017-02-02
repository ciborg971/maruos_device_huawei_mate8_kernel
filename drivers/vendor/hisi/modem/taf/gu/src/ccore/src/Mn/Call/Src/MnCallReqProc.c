

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "MnCallApi.h"
#include "MnCallSendCc.h"
#include "MnCallMgmt.h"
#include "MnComm.h"
#include "MnErrorCode.h"
#include "UsimPsInterface.h"
#include "MnCallBcProc.h"
#include "NasIeUtil.h"
#include "siapppb.h"
#include "NasOmInterface.h"
#include "MnCallMnccProc.h"
#include "MmaAppLocal.h"
#include "MnCall.h"
#include "MnCallMnccProc.h"
#include "MnCallTimer.h"
#include "MnCallCtx.h"
#include "MnCallProcNvim.h"
#include "MnCallReqProc.h"

#include "NasStkInterface.h"

#include "TafSdcLib.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "NasUsimmApi.h"

#include "TafStdlib.h"

#include "MnCallSendApp.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID        PS_FILE_ID_MNCALL_REQ_PROC_C

/* f_aucCallEmerNumsNoUsim��f_aucCallEmerNumsWithUsim��MN_CALL_MAX_ASCII_NUM_LEN
   f_stMmCallEmerNumList��g_stTafCallCustomEccNumCtx �Ƶ�SPMģ�� */

#define MN_CALL_MODE_FULL               1   /* full functionality */


/*lint -save -e958 */

/*****************************************************************************
   2 ����ʵ��
*****************************************************************************/

LOCAL VOS_VOID MN_CALL_ActCcbsReqPorc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        ucCallId
)
{
    MN_CALL_SendCcActCcbsReq(ucCallId);

    /* ��עCCBS����ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(ucCallId,
                          MN_CALL_SS_PROG_EVT_ACT_CCBS_CNF,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /*��עCCBS����ʧ���¼�����������Ϊ�ϱ�����ʧ��*/
    MN_CALL_RegSsKeyEvent(ucCallId,
                          MN_CALL_SS_PROG_EVT_ACT_CCBS_REJ,
                          MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

    MN_CALL_BeginCallSupsCmdProgress(clientId, MN_CALL_SUPS_CMD_ACT_CCBS);

    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

}


LOCAL VOS_VOID  MN_CALL_RecallCcbsReqPorc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        ucCallId
)
{
    VOS_UINT32                          ulRslt = MN_ERR_NO_ERROR;
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    /*�����Ƿ�������ͨ���ĺ��У�����У����ܷ���SETUP��Ϣ*/
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 == ulNumOfCalls)
    {
        ulRslt = MN_CALL_SendCcbsSetupReq(ucCallId);
        /* ��Ϣ����ʧ�ܣ���������������ʵ�� */
        if ( VOS_OK != ulRslt)
        {
            MN_CALL_FreeCallId(ucCallId);

            MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_UNKNOWN);

            return;
        }

        MN_CALL_UpdateClientId(ucCallId,clientId);
        MN_CALL_UpdateRecallSupsProgress(ucCallId,
                                         MN_CALL_ERR_SS_UNSPECIFIC,
                                         MN_CALL_SS_RES_SUCCESS);

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

        MN_CALL_UpdateCcCallDir(ucCallId, MN_CALL_DIR_MO);
        MN_CALL_UpdateCallState(ucCallId, MN_CALL_S_DIALING);

        /* ���֧�ֺ����ؽ����ܣ�������MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD��ʱ�� */
        if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(ucCallId))
        {
            TAF_CALL_StartRedialPeriodTimer(ucCallId);
        }

        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_ORIG);
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_ATTEMPT,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
     }
     else
     {
        /*����û�ѡ�����CCBS�غ����򷵻�ʧ��,��ǰ���ں��в��ܽ��лغ�*/
        MN_CALL_UpdateClientId(ucCallId, clientId);


        /*�Ҷ�ָ���ĺ���*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_USER_BUSY);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        MN_CALL_UpdateCcCause(ucCallId, MN_CALL_USER_BUSY);

        /* ��¼���йҶϵķ��� */
        MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);

        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(ucCallId,
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);


        /*����ҵ�������ʼ����*/
        MN_CALL_BeginCallSupsCmdProgress(clientId, MN_CALL_SUPS_CMD_ACT_CCBS);

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);
     }

}
LOCAL VOS_VOID MN_CALL_SupsCmdCcbsReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /*�û�����CCBS��������CCBS�غ�����Ϊ����AT����:CHLD+5*/
    MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_ACTIVE,&ulNumOfCalls,aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_ActCcbsReqPorc(clientId, opId, aCallIds[0]);
        return;
    }
    MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_RECALL,&ulNumOfCalls,aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_RecallCcbsReqPorc(clientId, opId, aCallIds[0]);
        return;
    }

    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);
}

/* MN_CALL_IsValidEmerCategory���Ƶ�SPMģ�鲢������ */

/*****************************************************************************
 �� �� ��  : MN_CALL_JudgeAllowToBuildMpty
 ��������  : �ж��Ƿ��ܹ�build Mpty
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - ����build Mpty
             VOS_FALSE - ����build Mpty
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2007��9��20��
    ��    ��   : ���� 49431
    �޸�����   : �����ɺ���
*****************************************************************************/
LOCAL VOS_BOOL MN_CALL_JudgeAllowToBuildMpty(VOS_VOID)
{
    VOS_UINT32                          ulNumOfMptyCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT32                          ulNumOfHoldCalls,ulNumOfActCalls;


    /* ��ȡ����active����hold״̬�ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfActCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfHoldCalls, aCallIds);


    /* �ж���ǰ�Ƿ��к�������MPTY */
    MN_CALL_GetCallsByMptyState(MN_CALL_IN_MPTY, &ulNumOfMptyCalls, aCallIds);
    if (5 <= ulNumOfMptyCalls)
    {
        /* MPTY�Ѿ��������� */
        MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: Beyond MPTY Capability.");
        return VOS_FALSE;
    }

    if (0 == ulNumOfMptyCalls)
    {
        /* ��ǰû��MPTY,�����в�ֹһ�����ڼ������hold״̬�ĺ��� */
        if ((1 != ulNumOfActCalls) || (1 != ulNumOfHoldCalls))
        {
            MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: Not Only One Active or hold Call.");
            return VOS_FALSE;
        }

        return VOS_TRUE;
    }
    else
    {
        if ((0 == ulNumOfActCalls) || (0 == ulNumOfHoldCalls))
        {
            MN_WARN_LOG("MN_CALL_JudgeAllowToBuildMpty: No Active or hold Call.");
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdReqCommProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam,
    VOS_UINT32                          ulRslt
)
{
    /*����ҵ�������ʼ����*/
    MN_CALL_BeginCallSupsCmdProgress(clientId, pstCallSupsParam->enCallSupsCmd);

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, ulRslt);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              ulRslt);
}
VOS_VOID MN_CALL_CommRelAction(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_UpdateClientId(callId, clientId);
    (VOS_VOID)MN_CALL_SendCcDiscReq(callId, MN_CALL_USER_BUSY);

    /* ��¼�����Ҷϵ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(callId, MN_CALL_USER_BUSY);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(callId,
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);
}


VOS_VOID TAF_CALL_RelIncomingOrWaitingCall(
    VOS_UINT8                           ucCallId,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_USER_BUSY);

    /* ��¼�����Ҷϵ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(ucCallId, MN_CALL_USER_BUSY);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);

    if ((MN_CALL_S_INCOMING == enCallState)
      ||(MN_CALL_S_WAITING == enCallState))
    {
        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }
}


VOS_VOID TAF_CALL_RelRedialingCall(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg = MN_CALL_GetBufferedMsg();

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
    {
        /* ��TAF�ڲ��һ�����������ȷ����Ϣ��TAF */
        TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
        TAF_CALL_SendTafRelCallCnf(clientId, opId, TAF_CS_CAUSE_SUCCESS);
    }
    else
#endif
    {
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_SUCCESS);
    }

    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstBufferdMsg->stBufferedSetupMsg.ucCallId))
        {
            /* ֹͣT9��ʱ�� */
            MN_CALL_StopTimer(TAF_CALL_TID_T9);
        }
#endif
        TAF_CALL_StopAllRedialTimers(pstBufferdMsg->stBufferedSetupMsg.ucCallId);

        /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
        TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg, MN_CALL_NORMAL_CALL_CLEARING);
        /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */
    }
}


VOS_VOID TAF_CALL_AtaReportOkAsync(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    /* ����ú��е�call sub state ΪTAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK��ظ�ʧ��*/
    if (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == TAF_CALL_GetCallSubState(callId))
    {
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_NOT_ALLOW);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_NOT_ALLOW);

        return;
    }

    /* ���ú�����״̬ΪTAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK */
    TAF_CALL_SetCallSubState(callId, TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK);

    /*�����ú��� */
    (VOS_VOID)MN_CALL_SendCcSetupRsp(callId);
    MN_CALL_StopTimer(MN_CALL_TID_RING);

    /*�ж�ҵ���ŵ��Ƿ�׼���ã����׼���þ͸�VC���ʹ�����������*/
    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);

            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* ���¸ú��е�Client��Ϣ */
    MN_CALL_UpdateClientId(callId, clientId);

    TAF_CALL_SendSupsCmdCnf(clientId, opId, callId, TAF_CS_CAUSE_SUCCESS);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              callId,
                                              TAF_CS_CAUSE_SUCCESS);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdRelHoldOrUdubReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_CUSTOM_CFG_INFO_STRU        *pstCustomCfgAddr;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /* �����ڵȴ��ĺ���, �Ҷϸú���(ԭ��ΪUser busy) */
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
        MN_CALL_StopTimer(MN_CALL_TID_RING);
        return;
    }

    /* Incoming״̬��Ҳ��ȴ��ĺ���, ���ԹҶϸú���(ԭ��ΪUser busy) */
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
        MN_CALL_StopTimer(MN_CALL_TID_RING);
        return;
    }

    /* �б����ֵĺ���,�Ҷ����б����ֵĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 < ulNumOfCalls)
    {
        /* �Ҷ����б����ֵĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /*��������к��е�ClientId*/
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }
    if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
    {
        /* �����ڵȴ�CCBS����ĺ���, �Ҷϸú���(ԭ��ΪUser busy) */
        MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_ACTIVE, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
            return;
        }

        /* �����ڵȴ�CCBS�غ��ĺ���, �Ҷϸú���(ԭ��ΪUser busy) */
        MN_CALL_GetCallsByState(MN_CALL_S_CCBS_WAITING_RECALL, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            MN_CALL_CommRelAction(clientId,opId,aCallIds[0],pstCallSupsParam);
            return;
        }
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdRelHoldOrUdubReqProc: state err REL ACT ACPT OTH");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;

}
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelActAcptOthReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    /* ������ͨ���ĺ���,�Ҷ���������ͨ���ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    /* �����ڵȴ��ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /*�����ú��� */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ֹͣMN_CALL_TID_RING��ʱ�� */
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /* ��ע�ú��е����ӽ�������¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��е����ӹҶ�����¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    /* �б����ֵĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ��������ֵĺ�����MTPY,��ô�ָ�MTPY����Ȼ�ָ��ú���*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*�ָ�MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                         MN_CALL_SS_RETRIEVEMPTY_OPERATION);
        }
        else
        {
            /*�����ú��� */
            MN_CALL_SendCcRetrieveReq(aCallIds[0]);
        }

        /* ���µ�ǰ��client */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);
        /* ��ע�ú��еĻָ��ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĻָ����ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdRelActAcptOthReqProc: state err REL ACT ACPT OTH");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;

}
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelCallXReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    /* �˴�ɾ�� */



    enCallState    = MN_CALL_S_BUTT;
    enMptyState    = MN_CALL_MPYT_STATE_BUTT;

    /*����X��״̬Ϊunknown��idle, ���������*/
    MN_CALL_GetCallState(pstCallSupsParam->callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_IDLE == enCallState) || (MN_CALL_S_UNKNOWN == enCallState))
    {
        MN_WARN_LOG("MN_CALL_CallSupsCmdRelCallXReqProc: state err REL CALL X");

        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_STATE_ERROR);

        return;
    }

    MN_CALL_UpdateClientId(pstCallSupsParam->callId, clientId);

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstCallSupsParam->callId))
    {
        /* ���"�ȴ�mt eCall���б�־λ" */
        TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

        /* ����ز��������ز���ʱ�� */
        TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(pstCallSupsParam->callId);
    }
#endif

    if ((MN_CALL_S_INCOMING == enCallState)
     || (MN_CALL_S_WAITING == enCallState)
     || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
    {
        TAF_CALL_RelIncomingOrWaitingCall(pstCallSupsParam->callId, enCallState);
    }
    /* ������д���dialing״̬���Һ����ط������ʱ�������У�cc����U0״̬������
       ��cc����disconnect��Ϣ���������rej ind��Ϣ */
    else if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(pstCallSupsParam->callId))
          && (MN_CALL_S_DIALING           == enCallState))
    {
        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
            MN_CALL_SS_PROG_EVT_REL,
            MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*����ҵ�������ʼ����*/
        MN_CALL_BeginCallSupsCmdProgress(clientId, pstCallSupsParam->enCallSupsCmd);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        MN_CALL_UpdateCcCause(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼���йҶϵķ��� */
        MN_CALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);

        TAF_CALL_RelRedialingCall(clientId, opId, pstCallSupsParam);
        return;
    }
    else
    {
        /*�Ҷ�ָ���ĺ���*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        MN_CALL_UpdateCcCause(pstCallSupsParam->callId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼���йҶϵķ��� */
        MN_CALL_UpdateDiscCallDir(pstCallSupsParam->callId, VOS_TRUE);
    }

    /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);


    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdRelCallXReqProc: send clint res succ.");
    return;
 }


VOS_VOID MN_CALL_CallSupsCmdRelAllCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);

    if (0 == ulNumOfCalls)
    {
        MN_WARN_LOG("MN_CALL_CallSupsCmdRelAllCallReqProc: state err REL ALL CALL");

#if (FEATURE_ON == FEATURE_ECALL)
        if (VOS_TRUE == TAF_CALL_GetInternalHangUpFlag())
        {
            /* �÷�֧���ᷢ�����쳣���� */
            TAF_CALL_SetInternalHangUpFlag(VOS_FALSE);
            TAF_CALL_SendTafRelCallCnf(clientId, opId, TAF_CS_CAUSE_SUCCESS);
        }
        else
#endif
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_SUCCESS);
        }

        return;
    }

    /* �Ҷ���������ͨ���ĺ��� */
    for (i = 0; i < ulNumOfCalls; i++)
    {
        MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
        MN_CALL_UpdateClientId(aCallIds[i], clientId);
        if ((MN_CALL_S_INCOMING            == enCallState)
         || (MN_CALL_S_WAITING             == enCallState)
         || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
        {
            TAF_CALL_RelIncomingOrWaitingCall(aCallIds[i], enCallState);
        }
        /* ������д���dialing״̬���Һ����ط������ʱ�������У�cc����U0״̬������
           ��cc����disconnect��Ϣ���������rej ind��Ϣ */
        else if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(aCallIds[i]))
              && (MN_CALL_S_DIALING           == enCallState))
        {
            TAF_CALL_RelRedialingCall(clientId, opId, pstCallSupsParam);
            return;
        }
        else
        {
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_SETUP_COMPL);
        MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_REL);
    }

    /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
    MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                          MN_CALL_SS_PROG_EVT_REL,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdRelAllCallReqProc: send clint res succ.");
    return;
}
LOCAL VOS_VOID MN_CALL_CallSupsCmdHoldActAcptOthReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_ID_T                        ucCallId;
    VOS_UINT32                          ulHeldNumOfCalls;
    VOS_UINT32                          ulIncomingNumOfCalls;
    VOS_UINT32                          ulWaitingNumOfCalls;
    VOS_UINT32                          ulDialNumOfCalls;
    VOS_UINT32                          ulAlertingNumOfCalls;

    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulHeldNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulIncomingNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulWaitingNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_DIALING, &ulDialNumOfCalls, aCallIds);
    MN_CALL_GetCallsByState(MN_CALL_S_ALERTING, &ulAlertingNumOfCalls, aCallIds);

    /* ��˶�CHLD=2,������������ʱ,��������:
       if ����һ������ĺ���:
           a.�����ڲ��ҽ�����һ��HOLD�ĺ���,����
           b.�����ڲ��ҽ�����һ��MT�ĺ���,����
           c.��������������
       else if ����һ��HOLD�ĺ���:
           a.�����ڲ��ҽ�����һ��MT�ĺ���,����
           b.��������������
       else if ����һ��MT�ĺ���
    */
    /* ��ǰ��MO�������ڲ��Ż�����������,�ܾ��û����� */
    if ((0 != ulDialNumOfCalls) || (0 != ulAlertingNumOfCalls))
    {
        TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

        TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                  opId,
                                                  pstCallSupsParam->callId,
                                                  TAF_CS_CAUSE_STATE_ERROR);

        return;
    }


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    /* ������ͨ���ĺ��� */
    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ��ǰ��һ������ĺ���,������һ��HOLD��MT����ʱ,�ܾ�CHLD=2������ */
        if ((0 != ulHeldNumOfCalls) && ((0 != ulIncomingNumOfCalls) || (0 != ulWaitingNumOfCalls)))
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        /* �������ͨ���ĺ�����MTPY,��ô����MTPY*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*����MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                         MN_CALL_SS_HOLDMPTY_OPERATION);
        }
        else
        {
            /*���ָú��� */
            MN_CALL_SendCcHoldReq(aCallIds[0]);
        }
        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ��ע�ú��еĺ��еı��ֱ��ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_HOLD_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        ucCallId = aCallIds[0];

        /*�����ڵȴ��ĺ���*/
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(ucCallId, clientId);

            /*��ע����ͨ���ĺ��еı��ֳɹ��¼�, ��������Ϊ������һ�� */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

            /* ��ע����ͨ���ĺ��б��ֹ����б��Ҷ��ͷ�ʱ�䣬��������Ϊ������һ�� */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_REL,
                                  MN_CALL_SS_SUBSEQ_OP_ACCPT_OTH);

            MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

            return;
        }

        /*�б����ֵĺ���*/
        MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
        if (0 != ulNumOfCalls)
        {
            /* ��������ֵĺ�����MTPY,��ô�ָ�MTPY����Ȼ�ָ��ú���*/
            MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
            if (MN_CALL_IN_MPTY == enMptyState)
            {
                /*�ָ� MPTY*/
                MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                     MN_CALL_SS_RETRIEVEMPTY_OPERATION);
            }
            else
            {
                /*�ָ��ú��� */
                MN_CALL_SendCcRetrieveReq(aCallIds[0]);
            }

            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(aCallIds[0], clientId);

            /*��ע�ú��еĻָ��ɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
            MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

            /*��ע�ú��еĻָ����ܾ��¼�, ��������Ϊ�ϱ�����ʧ��*/
            MN_CALL_RegSsKeyEvent(aCallIds[0],
                                  MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

            /* ����CCģ��ʵ�֣�HOLD CNF���յ��ͱ�־HOLD CNF��RETRIEVE CNF���ᵽ�� */
            MN_CALL_RegSsKeyEvent(ucCallId,
                                  MN_CALL_SS_PROG_EVT_HOLD_CNF,
                                  MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

            MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

            return;
        }

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /*��ע����ͨ���ĺ��еı��ֳɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_HOLD_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    /*�����ڵȴ��ĺ���*/
    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /*�����ú��� */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ��ע�ú��е����ӽ����ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }
    /*�����ڵȴ��ĺ���,��ӦATA*/
    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ����Ŀǰ����alert������Ϣ�󣬲Ż��ϱ�incoming�¼�����˴˴��������·�alert�¼� */

        if (VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
        {
            TAF_CALL_AtaReportOkAsync(clientId, opId, aCallIds[0], pstCallSupsParam);
            return;
        }

        /*�����ú��� */
        (VOS_VOID)MN_CALL_SendCcSetupRsp(aCallIds[0]);
        MN_CALL_StopTimer(MN_CALL_TID_RING);

        /*�ж�ҵ���ŵ��Ƿ�׼���ã����׼���þ͸�VC���ʹ�����������*/
        if(VOS_TRUE == MN_CALL_GetTchStatus())
        {
            if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
            {
                /* ������Ϣ֪ͨVC������ͨ�� */
                MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
                /* ������Ϣ֪ͨAT����ͨ��״̬ */
                MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
            }
            MN_CALL_SetChannelOpenFlg(VOS_TRUE);
        }

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /* ��ע�ú��е����ӽ����ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_SETUP_COMPL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĹҶ�����¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    /*�б����ֵĺ���*/
    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* ��������ֵĺ�����MTPY,��ô�ָ�MTPY����Ȼ�ָ��ú���*/
        MN_CALL_GetCallState(aCallIds[0], &enCallState, &enMptyState);
        if (MN_CALL_IN_MPTY == enMptyState)
        {
            /*�ָ� MPTY*/
            MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                        MN_CALL_SS_RETRIEVEMPTY_OPERATION);
        }
        else
        {
            /*�ָ��ú��� */
            MN_CALL_SendCcRetrieveReq(aCallIds[0]);
        }

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        /*��ע�ú��еĻָ��ɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*��ע�ú��еĻָ����ܾ��¼�, ��������Ϊ�ϱ�����ʧ��*/
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_RETRIEVE_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err HOLD ACT ACPT OTH");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}
LOCAL VOS_VOID MN_CALL_CallSupsCmdHoldAllExcptXReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetCallState(pstCallSupsParam->callId, &enCallState, &enMptyState);
    if (MN_CALL_IN_MPTY == enMptyState)
    {

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(pstCallSupsParam->callId, clientId);

        /*������X��MPTY�з���*/
        MN_CALL_SendCcSimpleFacility(pstCallSupsParam->callId,
                                     MN_CALL_SS_SPLITMPTY_OPERATION);

        /*��ע�ú��еķ���ɹ��¼�, ��������Ϊ�ϱ������ɹ�*/
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                              MN_CALL_SS_PROG_EVT_SPLIT_MPTY_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /*��ע�ú��еķ��뱻�ܾ��¼�, ��������Ϊ�ϱ�����ʧ��*/
        MN_CALL_RegSsKeyEvent(pstCallSupsParam->callId,
                              MN_CALL_SS_PROG_EVT_SPLIT_MPTY_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err HOLD ALL EXCPT X");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdBuildMptyReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    if (VOS_TRUE == MN_CALL_JudgeAllowToBuildMpty())
    {
        /* ����MPTY */
        MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);

        /* ���¸ú��е�Client��Ϣ */
        MN_CALL_UpdateClientId(aCallIds[0], clientId);

        MN_CALL_SendCcSimpleFacility(aCallIds[0],
                                     MN_CALL_SS_BUILDMPTY_OPERATION);


        /* ��ע�ú��еĽ���MPTY�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_BUILD_MPTY_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��еĽ���MPTY���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[0],
                              MN_CALL_SS_PROG_EVT_BUILD_MPTY_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }
    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err BUILD MPTY");


    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}


LOCAL VOS_VOID MN_CALL_CallSupsCmdDeflectCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];

    TAF_CALL_SUB_STATE_ENUM_UINT8       enCallSubState;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);
    if (0 == ulNumOfCalls)
    {
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);
        if (0 == ulNumOfCalls)
        {
            MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err DEFLECT CALL");

            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }
        else
        {
            MN_CALL_StopTimer(MN_CALL_TID_RING);
        }
    }
    else
    {
        /* NV����ж�incoming���еĺ�����״̬Ϊ
           TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK��ֱ���ϱ�ERROR */
        enCallSubState = TAF_CALL_GetCallSubState(pstCallSupsParam->callId);

        if ((VOS_TRUE == TAF_CALL_GetAtaReportOkAsyncFlag())
         && (TAF_CALL_SUB_STATE_INCOMING_WAIT_CONNECT_ACK == enCallSubState))
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }

    MN_CALL_UpdateRedirNumber(aCallIds[0], &pstCallSupsParam->stRedirectNum);

    /*���¸ú��е�Client��Ϣ*/
    MN_CALL_UpdateClientId(aCallIds[0], clientId);

    /* ��������ƫת�Ĳ���ҵ������ */
    MN_CALL_SendCcDeflectFacility(aCallIds[0], &pstCallSupsParam->stRedirectNum);


    /* ��ע�ú��е�ƫת�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
    MN_CALL_RegSsKeyEvent(aCallIds[0],
                          MN_CALL_SS_PROG_EVT_DEFLECT_CNF,
                          MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

    /* ��ע�ú��е�ƫת���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
    MN_CALL_RegSsKeyEvent(aCallIds[0],
                          MN_CALL_SS_PROG_EVT_DEFLECT_REJ,
                          MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

    MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

    MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
    return;

}
LOCAL VOS_VOID MN_CALL_CallSupsCmdEctReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT32                          ulNumOfCalls2;
    MN_CALL_ID_T                        aHeldCallIds[MN_CALL_MAX_NUM];
    MN_CALL_ID_T                        aOtherCallIds[MN_CALL_MAX_NUM];


    PS_MEM_SET(aHeldCallIds,  0x00, sizeof(aHeldCallIds));
    PS_MEM_SET(aOtherCallIds, 0x00, sizeof(aOtherCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aHeldCallIds);
    if ( 0 != ulNumOfCalls )
    {
        MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 = ulNumOfCalls;
        MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 += ulNumOfCalls;
        MN_CALL_GetCallsByState(MN_CALL_S_ALERTING, &ulNumOfCalls, aOtherCallIds);
        ulNumOfCalls2 += ulNumOfCalls;
        if( 0 == ulNumOfCalls2 )
        {
            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;
        }

        /*���¸ú��е�Client��Ϣ*/
        MN_CALL_UpdateClientId(aHeldCallIds[0], clientId);

        /* ECT���� */
        MN_CALL_SendCcSimpleFacility(aHeldCallIds[0],
                                     MN_CALL_SS_ECT_OPERATION);
        /* ��ע�ú��е�ECT�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aHeldCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��е�ECT���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aHeldCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);


        /*������һ���е�Client��Ϣ*/
        MN_CALL_UpdateClientId(aOtherCallIds[0], clientId);


        /* ��ע�ú��е�ECT�ɹ��¼�, ��������Ϊ�ϱ������ɹ� */
        MN_CALL_RegSsKeyEvent(aOtherCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_CNF,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        /* ��ע�ú��е�ECT���ܾ��¼�, ��������Ϊ�ϱ�����ʧ�� */
        MN_CALL_RegSsKeyEvent(aOtherCallIds[0],
                              MN_CALL_SS_PROG_EVT_ECT_REJ,
                              MN_CALL_SS_SUBSEQ_OP_RPT_FAIL);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelAllExceptWaitCallReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT8                           i;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
            if (( MN_CALL_S_INCOMING != enCallState)
             && ( MN_CALL_S_WAITING != enCallState))
            {
                /* ���¸ú��е�Client��Ϣ */
                MN_CALL_UpdateClientId(aCallIds[i], clientId);
                (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼�����Ҷϵ�ԭ��ֵ */
                MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼���йҶϵķ��� */
                MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
                if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
                {
                    /* ���"�ȴ�mt eCall���б�־λ" */
                    TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                    /* ����ز��������ز���ʱ�� */
                    TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
                }
#endif
            }
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelHeldReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT8                           i;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_HELD, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}
LOCAL VOS_VOID MN_CALL_CallSupsCmdRelActiveReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    const MN_CALL_SUPS_PARAM_STRU       *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    VOS_UINT8                           i;


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    MN_CALL_GetCallsByState(MN_CALL_S_ACTIVE, &ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ���ĺ��� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            /* ���¸ú��е�Client��Ϣ */
            MN_CALL_UpdateClientId(aCallIds[i], clientId);
            (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼�����Ҷϵ�ԭ��ֵ */
            MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

            /* ��¼���йҶϵķ��� */
            MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

#if (FEATURE_ON == FEATURE_ECALL)
            if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ���"�ȴ�mt eCall���б�־λ" */
                TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
#endif
        }

        /* ��ע���һ�����ҶϺ��еĹҶ�����¼�, ��������Ϊ������һ�� */
        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(clientId, opId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        MN_NORM_LOG("MN_CALL_CallSupsCmdReqProc: send clint res succ.");
        return;
    }

    MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err REL ALL CALL");

    TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                              opId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_STATE_ERROR);

    return;
}



VOS_VOID  MN_CALL_SetMmEmerNumList(
    MNCC_EMERGENCY_LIST_IND_STRU       *pstMnccEmcListInd
)
{
    VOS_UINT8                           i;

    VOS_UINT32                          j;

    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList    = VOS_NULL_PTR;

    pstMmCallEmerNumList                    = TAF_SDC_GetMmCallEmerNumList();

    pstMmCallEmerNumList->ulMcc             = pstMnccEmcListInd->ulMcc;
    pstMmCallEmerNumList->ucEmergencyNumber = pstMnccEmcListInd->ucEmergencyNumber;

    /* ������������������������ֵ����ʹ�����ֵ */
    if (pstMnccEmcListInd->ucEmergencyNumber > TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER)
    {
        pstMmCallEmerNumList->ucEmergencyNumber = TAF_SDC_EMER_NUM_LISTS_MAX_NUMBER;
    }
    else
    {
        pstMmCallEmerNumList->ucEmergencyNumber = pstMnccEmcListInd->ucEmergencyNumber;
    }

    /* �����������뱣����ȫ�ֱ����� */
    for (i = 0; i < pstMmCallEmerNumList->ucEmergencyNumber; i++)
    {
        pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue = pstMnccEmcListInd->astEmergencyLists[i].ucCategoryValue;
        pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen     = pstMnccEmcListInd->astEmergencyLists[i].ucEmcNumLen;


        /* BCD����0X0F��ʾ�������к�����������BCD����дΪ99f947,����Ҫת��Ϊ99f9 */
        for ( j = 0; j < pstMnccEmcListInd->astEmergencyLists[i].ucEmcNumLen; j++ )
        {
            pstMmCallEmerNumList->astEmergencyLists[i].aucEmergencyList[j] = pstMnccEmcListInd->astEmergencyLists[i].aucEmergencyNum[j];

            /* ��⵽��������0XF_ */
            if (MN_CALL_BCD_ODD_NUMBER_END == (pstMnccEmcListInd->astEmergencyLists[i].aucEmergencyNum[j] & MN_CALL_BCD_ODD_NUMBER_END) )
            {
                /* ��Ҫ�Գ���ֵ���¸�ֵ */
                pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen = (VOS_UINT8)(j + 1);
                break;
            }

        }

    }
}

/* TAF_SPM_UsimEccNumCheck ��TAF_SPM_NetworkEccNumCheck��TAF_SPM_AppCustomEccNumCheck
    TAF_SPM_EccNumCheck���Ƶ�SPM,������ΪTAF_SPM_... */



VOS_UINT32 MN_CALL_GetMoCallBc(
    MN_CALL_ID_T                        CallId,
    NAS_CC_IE_BC_STRU                  *pstBc1,
    NAS_CC_IE_BC_STRU                  *pstBc2,
    MN_CALL_REP_IND_ENUM_U8            *penBcRepeatInd
)
{
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulNumOfBc;
    MN_CALL_MGMT_STRU                   stCallInfo;

    ulRet = MN_CALL_GetSpecificCallInfo(CallId, &stCallInfo);
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* ���ݺ�������, ����ģʽ�����ݺ�����������BC��Repeat Ind���� */
    PS_MEM_SET(pstBc1, 0, sizeof(NAS_CC_IE_BC_STRU));
    PS_MEM_SET(pstBc2, 0, sizeof(NAS_CC_IE_BC_STRU));

    ulNumOfBc = MN_CALL_BuildBcOfSetup(stCallInfo.stCallInfo.enCallType,
                                       stCallInfo.stCallInfo.enCallMode,
                                       &stCallInfo.stCallInfo.stDataCfgInfo,
                                       pstBc1,
                                       pstBc2);
    if (0 == ulNumOfBc)
    {
        return VOS_ERR;
    }
    else if (TAF_CALL_MAX_BC_NUM == ulNumOfBc)
    {
        /* ������BC������£�repeat indicator��Ϊalternate */
        *penBcRepeatInd = MN_CALL_REP_IND_ALTER;
    }
    else
    {
        /* �˴���Ҫ�ο�24.008 10.5.4.22 �еĶ���ȷ��?? */
        *penBcRepeatInd = MN_CALL_REP_IND_NULL;
    }

    return VOS_OK;
}


VOS_UINT32  MN_CALL_BuildNormalCallReqProc(MN_CALL_ID_T callId)
{
    NAS_CC_IE_BC_STRU                   stBc1;
    NAS_CC_IE_BC_STRU                   stBc2;
    MN_CALL_REP_IND_ENUM_U8             enBcRepeatInd;
    VOS_UINT32                          ulRet;
    MN_CALL_MGMT_STRU                   stCallInfo;

    PS_MEM_SET(&stCallInfo, 0, sizeof(stCallInfo));

    ulRet = MN_CALL_GetSpecificCallInfo(callId, &stCallInfo);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("MN_CALL_BuildNormalCallReqProc: BUILD BC FAIL.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    ulRet = MN_CALL_GetMoCallBc(stCallInfo.stCallInfo.callId, &stBc1, &stBc2, &enBcRepeatInd);
    if (VOS_OK != ulRet)
    {
        /* ����BCʧ�ܣ��ͷź��� */
        MN_WARN_LOG("MN_CALL_BuildNormalCallReqProc: BUILD BC FAIL.");
        return TAF_CS_CAUSE_UNKNOWN;
    }

    /* �����ϱ���speed�Ķ��壬��API�еĶ��岻ͬ��
       ��speed����ת����ֱ�Ӵ�BC�н���ת�� */
    if ((MN_CALL_TYPE_CS_DATA == stCallInfo.stCallInfo.enCallType)
      ||(MN_CALL_TYPE_FAX == stCallInfo.stCallInfo.enCallType))
    {
        MN_CALL_GetDataCfgInfoFromBc(&stBc1, &stCallInfo.stCallInfo.stDataCfgInfo);
    }
    else
    {
        /* ������������棬���BC2�л�ȡ */
        if (( MN_CALL_MODE_AVF == stCallInfo.stCallInfo.enCallMode )
          &&( VOS_TRUE == NAS_IE_IS_PRESENT(&stBc2)))
        {
            MN_CALL_GetDataCfgInfoFromBc(&stBc2, &stCallInfo.stCallInfo.stDataCfgInfo);
        }
    }

    /* FDN���Ӧ���� MO CONTROL����ǰִ�У��˴�����ǰ�� */

    /* �����������е�Setup��Ϣ��CC */

    if (VOS_OK != MN_CALL_SendCcSetupReq(enBcRepeatInd,
                                         &stBc1,
                                         &stBc2,
                                         &stCallInfo))
    {
        MN_WARN_LOG("MN_CALL_CallOrigReqProc: SEND MSG ERROR.");
        return TAF_CS_CAUSE_UNKNOWN;
    }
    else
    {
        NAS_EventReport(WUEPS_PID_TAF,
                        NAS_OM_EVENT_CC_MO_ATTEMPT,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    return TAF_CS_CAUSE_SUCCESS;
}
VOS_BOOL MN_CALL_CheckNVAllowCallOrig(
    MN_CALL_TYPE_ENUM_U8                enCallType
)
{
    VOS_UINT8                           enVpNvCfgState;

    if (MN_CALL_TYPE_VOICE == enCallType)
    {
        /* VOICE���͵ĺ������������Ļ���ֱ�ӷ���VOS_FALSE */
        if ( VOS_FALSE == TAF_CALL_GetCallStatusControl())
        {
            return VOS_FALSE;
        }
        return VOS_TRUE;
    }
    enVpNvCfgState = TAF_CALL_GetVpCfgState();
    if (MN_CALL_TYPE_VIDEO == enCallType)
    {
        /* ���ݵ�ǰ��NV�˫���MO��������ģ�����VOS_TRUE */
        if (( MN_CALL_VP_MO_MT_BOTH == enVpNvCfgState )
         || ( MN_CALL_VP_MO_ONLY == enVpNvCfgState ))
        {
            return VOS_TRUE;
        }

        return VOS_FALSE;
    }
    return VOS_TRUE;

}


VOS_VOID  MN_CALL_CallOrigReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    MN_CALL_ORIG_PARAM_STRU            *pstOrigParam
)
{
    VOS_UINT32                          ulRet;
    MN_CALL_ID_T                        NewcallId;

    NewcallId = 0;

    /* ���������жϷ���SPMԤ�����У�����ɾ�� */

    /* ��������У�֪ͨ���з��𷽺����쳣���� */
    ulRet = MN_CALL_MakeNewCall(pstOrigParam->enCallType,
                                &NewcallId);

    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_NORM_LOG("MN_CALL_CallOrigReqProc: Fail to MN_CALL_MakeNewCall.");

        TAF_CALL_SendCallOrigCnf(clientId, opId, callId, ulRet);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(NewcallId, ulRet);
#endif

        return;
    }
    callId = NewcallId;

    /* ����ǽ������У���ֱ�ӷ���CC,�������л���Ҫ����һϵ���ж� */
    if ((MN_CALL_TYPE_EMERGENCY == pstOrigParam->enCallType)
#if (FEATURE_ON == FEATURE_ECALL)
     || (MN_CALL_TYPE_MIEC      == pstOrigParam->enCallType)
     || (MN_CALL_TYPE_AIEC      == pstOrigParam->enCallType)
#endif
       )
    {
        /*�½�һ������ʵ��, ulCcTi��û��ʵ�ʺ���*/
        MN_CALL_CreateMoCallEntity(clientId, opId, callId, pstOrigParam);

        if (VOS_TRUE == pstOrigParam->stEmergencyCat.bExist)
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId,
                                                &(pstOrigParam->stEmergencyCat.ucEmergencyCat));

        }
        else
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, VOS_NULL_PTR);
        }

        if (VOS_OK != ulRet)
        {
            MN_WARN_LOG("MN_CALL_CallOrigReqProc: SEND MSG ERROR: emerge.");

            TAF_CALL_SendCallOrigCnf(clientId, opId, callId, TAF_CS_CAUSE_UNKNOWN);

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }
    else
    {
        /*�½�һ������ʵ��, ulCcTi��û��ʵ�ʺ���*/
        MN_CALL_CreateMoCallEntity(clientId, opId, callId, pstOrigParam);

        /* FDN��CALL control�ļ��������Ƶ�SPMģ�� */

        ulRet = MN_CALL_BuildNormalCallReqProc(callId);

        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_CallOrigReqProc: MN_CALL_BuildNormalCallReqProc fail.");

            TAF_CALL_SendCallOrigCnf(clientId, opId, callId, ulRet);

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, ulRet);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }

    NAS_EventReport(WUEPS_PID_TAF,
                    NAS_OM_EVENT_CC_MO_ATTEMPT,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateCallState(callId, MN_CALL_S_DIALING);

#if (FEATURE_ON == FEATURE_ECALL)
    /* ���T9��ʱ����running, ֹͣT9��ʱ�� */
    MN_CALL_StopTimer(TAF_CALL_TID_T9);

    TAF_CALL_ResetEcallPeriodRemainTimerLen();

    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
#endif

    /* ���֧�ֺ����ؽ����ܣ�������MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD��ʱ�� */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    {
        TAF_CALL_StartRedialPeriodTimer(callId);
    }

    TAF_CALL_SendCallOrigCnf(clientId, opId, callId, TAF_CS_CAUSE_SUCCESS);


    MN_CALL_ReportEvent(callId, MN_CALL_EVT_ORIG);

    MN_NORM_LOG("MN_CALL_CallOrigReqProc: send clint res normal and report event.");
}
TAF_CS_CAUSE_ENUM_UINT32 MN_CALL_GetEndCause(
    TAF_CS_CAUSE_ENUM_UINT32            enEndCause,
    MN_CALL_STATE_ENUM_U8               enCallState
)
{
    /* ��д��Ӧ�ĹҶ�ԭ��ֵ */
    /* enEndCauseС��128ʱ��enEndCause��incoming/waiting״̬��USER_BUSY������127ʱ��interwork unspecified */
    if ( (MN_CALL_INVALID_CAUSE            != enEndCause)
      && (MN_CALL_INTERWORKING_UNSPECIFIED >= enEndCause ) )
    {
        return enEndCause;
    }
    else if ((MN_CALL_S_INCOMING == enCallState)
          || (MN_CALL_S_WAITING == enCallState)
          || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
    {
        return TAF_CS_CAUSE_CC_NW_USER_BUSY;
    }
    else if (MN_CALL_INTERWORKING_UNSPECIFIED < enEndCause)
    {
        return MN_CALL_INTERWORKING_UNSPECIFIED;
    }
    else
    {
        return TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING;
    }

}


VOS_UINT32 MN_CALL_InternalCallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU       *pstEndParm
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_CC_CAUSE_ENUM_U8            enCause;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_CC_CAUSE_BUTT;

    /* ��ȡ��Ӧ�ĺ���״̬�������Idle��Unknown״̬��ֱ���ϱ����� */
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_IDLE == enCallState)
     || (MN_CALL_S_UNKNOWN == enCallState))
    {
        if ( MN_CLIENT_ALL != clientId )
        {
            MN_WARN_LOG1("MN_CALL_InternalCallEndReqProc: send clint res err.",TAF_CS_CAUSE_STATE_ERROR);
            return TAF_CS_CAUSE_STATE_ERROR;
        }

    }

    if ((MN_CALL_S_INCOMING == enCallState)
      ||(MN_CALL_S_WAITING == enCallState))
    {
        MN_CALL_StopTimer(MN_CALL_TID_RING);
    }

    /* enCause��CC��Disconnectʱ�ã����ܳ���127
       pstEndParm->enEndCause��Ҫ���µ��Ҷ�ԭ��ֵ�У���CEND��ʱ���� */
    enCause = (MN_CALL_CC_CAUSE_ENUM_U8)MN_CALL_GetEndCause(pstEndParm->enEndCause, enCallState);

    /* ��¼�����Ҷϵ�ԭ��ֵ */
    MN_CALL_UpdateCcCause(callId, pstEndParm->enEndCause);

    /* ��¼���йҶϵķ��� */
    MN_CALL_UpdateDiscCallDir(callId, VOS_TRUE);

    /* ����MNCC_DISC_REQԭ�� */
    if (VOS_OK != MN_CALL_SendCcDiscReq(callId, enCause))
    {
        MN_WARN_LOG1("MN_CALL_InternalCallEndReqProc: send clint res err.",TAF_CS_CAUSE_UNKNOWN);
        return TAF_CS_CAUSE_UNKNOWN;
    }

    MN_NORM_LOG("MN_CALL_InternalCallEndReqProc: send clint res normal.");
    return TAF_CS_CAUSE_SUCCESS;

}


VOS_VOID  MN_CALL_CallEndReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_END_PARAM_STRU        *pstEndParm
)
{
    VOS_UINT32                          ulRet;

    /* ���д��ں�����ز���ҵ������У�������Ҷϵ绰 */
    if (VOS_FALSE == MN_CALL_AllowSupsOperation())
    {
        MN_WARN_LOG("MN_CALL_CallEndReqProc: state err ss cmd in progress ");

        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);

        return;

    }

    /* ���ݺ���״̬�ͷź��б�����Դ����֪ͨ����绰�Ҷ� */
    ulRet = MN_CALL_InternalCallEndReqProc(clientId, opId, callId, pstEndParm);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_SendClientResponse(clientId, opId, ulRet);
        return;
    }

    /* ���û�֪ͨ�Ҷ��������ڴ��� */
    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);

    /* �����û���Ϣ���ȴ��Ҷϲ����Ľ�� */
    MN_CALL_UpdateClientId(callId, clientId);

    return;

}



VOS_VOID  MN_CALL_CallAnswerReqProc(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_ID_T                        callId,
    const MN_CALL_ANS_PARAM_STRU        *pstAnsParam
)
{
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    enCallState          = MN_CALL_S_BUTT;
    enMptyState          = MN_CALL_MPYT_STATE_BUTT;

    /* ��ȡ��Ӧ�ĺ���״̬���������Incoming����Waiting״̬��ֱ���ϱ����� */
    MN_CALL_GetCallState(callId, &enCallState, &enMptyState);
    if ((MN_CALL_S_INCOMING != enCallState) && (MN_CALL_S_WAITING != enCallState))
    {
        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_STATE_ERROR);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_STATE_ERROR);
#endif

        MN_WARN_LOG1("MN_CALL_CallAnswerReqProc: call state err.state:",enCallState);
        return;
    }

    MN_CALL_StopTimer(MN_CALL_TID_RING);

    /* ����Ŀǰ����alert������Ϣ�󣬲Ż��ϱ�incoming�¼�����˴˴��������·�alert�¼� */

    /*����MN_SETUP_RESԭ�����*/
    if (VOS_OK != MN_CALL_SendCcSetupRsp(callId))
    {
        MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_UNKNOWN);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

        MN_ERR_LOG1("MN_CALL_CallAnswerReqProc: send clint res err.ulrslt:",TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /*�ж�ҵ���ŵ��Ƿ�׼���ã����׼���þ͸�VC���ʹ�����������*/
    if(VOS_TRUE == MN_CALL_GetTchStatus())
    {
        if (VOS_FALSE == MN_CALL_GetChannelOpenFlg())
        {
            /* ������Ϣ֪ͨVC������ͨ�� */
            MN_CALL_SendVcMsg(CALL_VC_CHANNEL_OPEN);
            /* ������Ϣ֪ͨAT����ͨ��״̬ */
            MN_CALL_ReportChannelEvent(MN_CALL_EVT_CHANNEL_OPEN);
        }
        MN_CALL_SetChannelOpenFlg(VOS_TRUE);
    }

    /* �ϱ�Ӧ������ȷ�� */
    MN_SendClientResponse(clientId, opId, TAF_CS_CAUSE_SUCCESS);


    /*���¸ú��е�Client��Ϣ*/
    MN_CALL_UpdateClientId(callId, clientId);

    MN_NORM_LOG("MN_CALL_CallEndReqProc: send clint res normal.");
}


VOS_VOID  MN_CALL_CallSupsCmdReqProc(struct MsgCB *pstCallSups)
{
    MN_CALL_CUSTOM_CFG_INFO_STRU       *pstCustomCfgAddr = VOS_NULL_PTR;
    MN_CALL_SUPS_PARAM_STRU            *pstCallSupsParam = VOS_NULL_PTR;
    MN_CLIENT_ID_T                      clientId;
    MN_OPERATION_ID_T                   opId;

    pstCallSupsParam = (MN_CALL_SUPS_PARAM_STRU *)(&((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->stSupsPara);
    clientId         = ((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->usClientId;
    opId             = ((MN_APP_CALL_SUPS_REQ_STRU *)pstCallSups)->opID;

    /* ��ȡ���Կ���NV��ַ */
    pstCustomCfgAddr                    = MN_CALL_GetCustomCfgInfo();

    /*
    ��ǰ���в���ҵ�������
    ����������Ϊ�Ҷ����к���
    */
    if (VOS_FALSE == MN_CALL_AllowSupsOperation())
    {
        if ((MN_CALL_SUPS_CMD_REL_ALL_CALL != pstCallSupsParam->enCallSupsCmd)
#if (FEATURE_ON == FEATURE_ECALL)
         && (MN_CALL_SUPS_CMD_REL_ECALL    != pstCallSupsParam->enCallSupsCmd)
#endif
        )
        {
            MN_WARN_LOG("MN_CALL_CallSupsCmdReqProc: state err ss cmd in progress ");

            TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

            TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                      opId,
                                                      pstCallSupsParam->callId,
                                                      TAF_CS_CAUSE_STATE_ERROR);

            return;

        }

        TAF_CALL_PreProcRelAllCall();

    }

    switch(pstCallSupsParam->enCallSupsCmd)
    {
        case MN_CALL_SUPS_CMD_REL_HELD_OR_UDUB:
            MN_CALL_CallSupsCmdRelHoldOrUdubReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ACT_ACPT_OTH:
            MN_CALL_CallSupsCmdRelActAcptOthReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_CALL_X:
            MN_CALL_CallSupsCmdRelCallXReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_CALL:
            MN_CALL_CallSupsCmdRelAllCallReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_HOLD_ACT_ACPT_OTH:
            MN_CALL_CallSupsCmdHoldActAcptOthReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_HOLD_ALL_EXCPT_X:
            MN_CALL_CallSupsCmdHoldAllExcptXReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_BUILD_MPTY:
            MN_CALL_CallSupsCmdBuildMptyReqProc(clientId, opId, pstCallSupsParam);
            break;
        case MN_CALL_SUPS_CMD_DEFLECT_CALL:
            if ( MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCallDeflectionSupportFlg)
            {
                MN_CALL_CallSupsCmdDeflectCallReqProc(clientId, opId, pstCallSupsParam);
            }
            else
            {
                TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

                TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                          opId,
                                                          pstCallSupsParam->callId,
                                                          TAF_CS_CAUSE_STATE_ERROR);
            }

            break;

        case MN_CALL_SUPS_CMD_ACT_CCBS:
            if (MN_CALL_NV_ITEM_ACTIVE == pstCustomCfgAddr->ucCcbsSupportFlg)
            {
                MN_CALL_SupsCmdCcbsReqProc(clientId, opId, pstCallSupsParam);
            }
            else
            {
                TAF_CALL_SendSupsCmdCnf(clientId, opId, pstCallSupsParam->callId, TAF_CS_CAUSE_STATE_ERROR);

                TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(clientId,
                                                          opId,
                                                          pstCallSupsParam->callId,
                                                          TAF_CS_CAUSE_STATE_ERROR);
            }
            break;

        case MN_CALL_SUPS_CMD_ECT:
            MN_CALL_CallSupsCmdEctReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ALL_EXCEPT_WAITING_CALL:
            MN_CALL_CallSupsCmdRelAllExceptWaitCallReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_HELD:
            MN_CALL_CallSupsCmdRelHeldReqProc(clientId, opId, pstCallSupsParam);
            break;

        case MN_CALL_SUPS_CMD_REL_ACTIVE:
            MN_CALL_CallSupsCmdRelActiveReqProc(clientId, opId, pstCallSupsParam);
            break;

        #if (FEATURE_ON == FEATURE_ECALL)
        case MN_CALL_SUPS_CMD_REL_ECALL:
            TAF_CALL_EcallSupsCmdRelReqProc(clientId, opId, pstCallSupsParam);
            break;
        #endif

        default:
            break;
    }

}



VOS_VOID  MN_CALL_QryAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    MN_CALL_QRY_ALS_CNF_STRU       stQryAlsCnf;

    stQryAlsCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stQryAlsCnf.OpId     = opId;
    stQryAlsCnf.ulRet    = TAF_ERR_NO_ERROR;
    stQryAlsCnf.enEvent  = MN_CALL_EVT_QRY_ALS_CNF;

    stQryAlsCnf.enAlsLine = MN_CALL_GetAlsLineInfo();

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stQryAlsCnf,sizeof(stQryAlsCnf));

}

VOS_VOID  MN_CALL_QryUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId
)
{
    TAF_PH_QRY_UUS1_INFO_CNF_STRU       stQryUus1Cnf;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulChkCuus1IFlg;
    VOS_UINT32                          ulChkCuus1UFlg;
    TAF_SDC_UNSOLICITED_RPT_CTRL_STRU  *pstUnsolicitedRptCtrl   = VOS_NULL_PTR;

    pstUnsolicitedRptCtrl   = TAF_SDC_GetUnsolicitedRptCtrl();

    ulChkCuus1IFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1I);

    ulChkCuus1UFlg  = TAF_SDC_CheckRptCmdStatus(pstUnsolicitedRptCtrl->aucRptCfg,
                                                TAF_SDC_CMD_RPT_CTRL_BY_UNSOLICITED,
                                                TAF_SDC_RPT_CMD_CUUS1U);

    PS_MEM_SET(&stQryUus1Cnf, 0, sizeof(stQryUus1Cnf));
    stQryUus1Cnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stQryUus1Cnf.OpId     = opId;
    stQryUus1Cnf.ulRet    = TAF_ERR_NO_ERROR;
    stQryUus1Cnf.enEvent  = MN_CALL_EVT_QRY_UUS1_INFO_CNF;

    /* ��ѯ���������CUUS1I��CUUS1U�Ƿ���Ҫ�����ϱ����� */
    stQryUus1Cnf.aenSetType[0] = ulChkCuus1IFlg;
    stQryUus1Cnf.aenSetType[1] = ulChkCuus1UFlg;

    ulRet = MN_CALL_GetCcUus1Info(&stQryUus1Cnf.ulActNum,stQryUus1Cnf.stUus1Info);

    if (VOS_OK != ulRet)
    {
        stQryUus1Cnf.ulRet = TAF_ERR_AT_ERROR;
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stQryUus1Cnf,sizeof(stQryUus1Cnf));
}
VOS_VOID  MN_CALL_SetAls(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_ALS_PARAM_STRU         *pstAls
)
{
    MN_CALL_SET_ALS_CNF_STRU       stAlsCnf;
    VOS_UINT32                     ulRet;

    stAlsCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stAlsCnf.OpId     = opId;
    stAlsCnf.ulRet    = TAF_ERR_NO_ERROR;
    stAlsCnf.enEvent  = MN_CALL_EVT_SET_ALS_CNF;

    ulRet = MN_CALL_UpdateAlsLineInfo(pstAls->enAlsLine,VOS_TRUE);

    if (VOS_OK != ulRet )
    {
        stAlsCnf.ulRet = TAF_ERR_UNSPECIFIED_ERROR;
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stAlsCnf,sizeof(stAlsCnf));

}

VOS_VOID  MN_CALL_SetUus1Info(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_UUS1_PARAM_STRU            *pstUus1Info
)
{
    VOS_UINT32                          i;
    TAF_PH_SET_UUS1_INFO_CNF_STRU       stUus1Cnf;

    /* ��ȡ�������������ϱ���ȫ�ֱ��� */
    VOS_UINT32                          ulCuus1URptCmdStatus;
    VOS_UINT32                          ulCuus1IRptCmdStatus;

    /* ����CUUS1I��CUUS1U��Ӧ��SDCȫ�ֱ��� */
    if (MN_CALL_CUUS1_ENABLE == pstUus1Info->enCuus1UFlg)
    {
        ulCuus1URptCmdStatus  = VOS_TRUE;
    }
    else
    {
        ulCuus1URptCmdStatus  = VOS_FALSE;
    }

    if (MN_CALL_CUUS1_ENABLE == pstUus1Info->enCuus1IFlg)
    {
        ulCuus1IRptCmdStatus  = VOS_TRUE;
    }
    else
    {
        ulCuus1IRptCmdStatus  = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1U, ulCuus1URptCmdStatus);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CUUS1I, ulCuus1IRptCmdStatus);

    stUus1Cnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stUus1Cnf.OpId     = opId;
    stUus1Cnf.ulRet    = TAF_ERR_NO_ERROR;
    stUus1Cnf.enEvent  = MN_CALL_EVT_SET_UUS1_INFO_CNF;

    for (i = 0; i < pstUus1Info->ulActNum; i++ )
    {
        /* ���±�����CC�е������Ϣ��UUS1��Ϣ */
        if (MN_ERR_NO_ERROR != MN_CALL_UpdateCcUus1Info(pstUus1Info->enSetType[i],
                                                       &(pstUus1Info->stUus1Info[i])) )
        {
            stUus1Cnf.ulRet = TAF_ERR_PARA_ERROR;
            break;
         }
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,(VOS_UINT8*)&stUus1Cnf,sizeof(stUus1Cnf));

}


VOS_UINT32 MN_CALL_AddEmerNumsWithUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    VOS_CHAR                          **pucEmcNumsWithUsim  = VOS_NULL_PTR;

    pucEmcNumsWithUsim  = TAF_SDC_GetCallEmerNumsWithUsimTblAddr();

    /* ��Э�鶨��Ľ��������������Ϣ */
    for (i = 0; i < TAF_SDC_NUMOF_EMER_NUMS_WITH_USIM; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = MN_CALL_ECC_NUM_INVALID_CATEGORY;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd(pucEmcNumsWithUsim[i],
                            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                            &pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen))
        {
            MN_WARN_LOG("MN_CALL_AddEmerNumsWithUsimToReportList: TAF_STD_ConvertAsciiNumberToBcd Fail.");
        }

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_CALL_AddEmerNumsNoUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    VOS_CHAR                          **pucEmcNumsNoUsim    = VOS_NULL_PTR;

    pucEmcNumsNoUsim    = TAF_SDC_GetCallEmerNumsNoUsimTblAddr();

    /* ��Э�鶨����޿�ʱ���������� */
    for (i = 0; i < TAF_SDC_NUMOF_EMER_NUMS_NO_USIM; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = MN_CALL_ECC_NUM_INVALID_CATEGORY;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_ABSENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;

        if (MN_ERR_NO_ERROR != TAF_STD_ConvertAsciiNumberToBcd(pucEmcNumsNoUsim[i],
                            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                            &pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen))
        {
            MN_WARN_LOG("MN_CALL_AddEmerNumsNoUsimToReportList: TAF_STD_ConvertAsciiNumberToBcd Fail.");
        }

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 MN_CALL_AddEccNumsInUsimToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    SI_PB_ECC_DATA_STRU                *pstEccData;
    VOS_UINT32                          ulResult;
    VOS_UINT8                           i;

    /* �����еĽ��������������Ϣ */
    pstEccData = (SI_PB_ECC_DATA_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(SI_PB_ECC_DATA_STRU));
    if (VOS_NULL_PTR == pstEccData)
    {
        MN_WARN_LOG("MN_CALL_AddEccNumsInUsimToReportList: Alloc Mem Fail.");
        return VOS_FALSE;
    }
    else
    {
        /* ��ȡUSIM�еĽ������к��� */
        PS_MEM_SET(pstEccData, 0, sizeof(SI_PB_ECC_DATA_STRU));
        NAS_PBAPI_GetEccNumber(pstEccData);

        for (i = 0; i < pstEccData->ulReocrdNum; i++)
        {
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = 0xffffffff;

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory = 0;

            /* �ж�ֵ����Ч�� */
            ulResult = TAF_STD_IsValidEmerCategory(pstEccData->astEccRecord[i].ucESC);

            if ( (VOS_TRUE == pstEccData->astEccRecord[i].bESC)
              && (VOS_TRUE == ulResult))
            {
                pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory         = (pstEccData->astEccRecord[i].ucESC & MN_CALL_EMER_CATEGORG_VAL_MAX);
            }

            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;
            pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen            = USIM_ECC_LEN;
            (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                       pstEccData->astEccRecord[i].aucEccCode,
                       USIM_ECC_LEN);

            pstEccNumInfo->ulEccNumCount++;

            /* �б����� */
            if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
            {
                /* �ڴ��ͷ� */
                PS_MEM_FREE(WUEPS_PID_TAF,pstEccData);
                return VOS_TRUE;
            }
        }

        /* �ڴ��ͷ� */
        PS_MEM_FREE(WUEPS_PID_TAF,pstEccData);
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_CALL_AddMmEccNumsToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    TAF_SDC_MM_EMERGENCY_LIST_STRU     *pstMmCallEmerNumList    = VOS_NULL_PTR;

    pstMmCallEmerNumList    = TAF_SDC_GetMmCallEmerNumList();

    /* ��ע��������Ľ��������������Ϣ */
    for (i = 0; i < pstMmCallEmerNumList->ucEmergencyNumber; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc                  = pstMmCallEmerNumList->ulMcc;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory             = pstMmCallEmerNumList->astEmergencyLists[i].ucCategoryValue;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent      = MN_CALL_ECC_NUM_VALID_SIM_PRESENT;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg   = VOS_FALSE;
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen            = pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen;

        (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                   pstMmCallEmerNumList->astEmergencyLists[i].aucEmergencyList,
                   pstMmCallEmerNumList->astEmergencyLists[i].ucEmcNumLen);

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 MN_CALL_AddCustomEccNumsToReportList(
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo
)
{
    VOS_UINT8                           i;
    TAF_SDC_CUSTOM_ECC_CTX_STRU        *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* ��APP���ƵĽ��������������Ϣ */
    for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
    {
        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ulMcc
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ulMcc;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucCategory
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucCategory;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucValidSimPresent
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucAbnormalServiceFlg
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg;

        pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].ucEccNumLen
            = pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen;

        (VOS_VOID)VOS_MemCpy(pstEccNumInfo->astCustomEccNumList[pstEccNumInfo->ulEccNumCount].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                   pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i].ucEccNumLen);

        pstEccNumInfo->ulEccNumCount++;

        /* �б����� */
        if (MN_CALL_MAX_EMC_NUM == pstEccNumInfo->ulEccNumCount)
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID MN_CALL_ReportEccNumList(VOS_VOID)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;
    TAF_SDC_CURC_RPT_CTRL_STRU         *pstCurcRptCtrl          = VOS_NULL_PTR;

    pstCurcRptCtrl                  = TAF_SDC_GetCurcRptCtrl();



    /* �ж������ϱ��Ƿ�� */
    if (VOS_FALSE == TAF_SDC_CheckRptCmdStatus(pstCurcRptCtrl->aucRptCfg,
                                            TAF_SDC_CMD_RPT_CTRL_BY_CURC,
                                            TAF_SDC_RPT_CMD_XLEMA))
    {
        return;
    }

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_ReportEccNumList: Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ʼ�� */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_ECC_NUM_IND;
    pstEccNumInfo->usClientId = MN_GetRealClientId(MN_CLIENT_ALL, WUEPS_PID_TAF);

    /* ��ȡ�������б� */
    MN_CALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /*  �ϱ�AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_TAF,pstEccNumInfo);

    return;
}
VOS_VOID MN_CALL_SaveCustomEccNum(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT8                               ucIndex;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum = VOS_NULL_PTR;

    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    /* ��ǰPLMN�����ڶ��ƽ��������룬�����ǰ�б� */
    if ((1 == pstCustomEccNumReq->ucIndex)
     && (1 == pstCustomEccNumReq->ucTotal)
     && (MN_CALL_INVALID_CATEGORY == pstCustomEccNumReq->ucCategory))
    {
        PS_MEM_SET(&pstCustomCallEmerNumCtx->stCustomEccNumList, 0, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));
    }
    else
    {
        /* ���涨�ƺ��뵽ȫ�ֱ��� */
        ucIndex         = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;
        pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[ucIndex]);

        pstCustomEccNum->ucCategory             = pstCustomEccNumReq->ucCategory;
        pstCustomEccNum->ucValidSimPresent      = pstCustomEccNumReq->ucSimPresent;
        pstCustomEccNum->ulMcc                  = pstCustomEccNumReq->ulMcc;
        pstCustomEccNum->ucEccNumLen            = pstCustomEccNumReq->stEccNum.ucNumLen;
        pstCustomEccNum->ucAbnormalServiceFlg   = pstCustomEccNumReq->ucAbnormalServiceFlg;

        (VOS_VOID)VOS_MemCpy(pstCustomEccNum->aucEccNum,
                   pstCustomEccNumReq->stEccNum.aucBcdNum,
                   pstCustomEccNumReq->stEccNum.ucNumLen);

        (pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount)++;
    }

    return;
}
VOS_VOID MN_CALL_RcvTafEccNumReq(
    MN_CALL_APP_CUSTOM_ECC_NUM_REQ_STRU*    pstCustomEccNumReq
)
{
    VOS_UINT32                              ulRst;
    MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU   stNvimCustomEccNumList;
    VOS_UINT8                               i;
    MN_CALL_CUSTOM_CFG_INFO_STRU           *pstCustomCfg       = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_NUM_STRU            *pstCustomEccNum    = VOS_NULL_PTR;
    TAF_SDC_CUSTOM_ECC_CTX_STRU            *pstCustomCallEmerNumCtx    = VOS_NULL_PTR;

    pstCustomCallEmerNumCtx = TAF_SDC_GetCustomCallEccNumCtx();

    pstCustomCfg      = MN_CALL_GetCustomCfgInfo();

    /* ���indexΪ1,��ն����б�, ��Ƕ��ƿ�ʼ */
    if (1 == pstCustomEccNumReq->ucIndex)
    {
        PS_MEM_SET(&(pstCustomCallEmerNumCtx->stCustomEccNumList), 0, sizeof(TAF_SDC_CUSTOM_ECC_NUM_LIST_STRU));

        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_TRUE;
    }

    /* ��ǰ���ڶ��ƹ��� */
    if (VOS_FALSE == pstCustomCallEmerNumCtx->ucCustomSetFlg)
    {
        /* ���������� */
        return;
    }

    /* ���涨�ƺ��뵽ȫ�ֱ��� */
    MN_CALL_SaveCustomEccNum(pstCustomEccNumReq);

    /* ��INDEX = TOTAL���߶��ƺ��������ﵽ�����Ϊ���ζ��ƽ��� */
    if ((pstCustomEccNumReq->ucIndex == pstCustomEccNumReq->ucTotal)
     || (TAF_SDC_MAX_CUSTOM_ECC_NUM == pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount))
    {
        (VOS_VOID)VOS_MemSet(&stNvimCustomEccNumList, 0, sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));

        stNvimCustomEccNumList.ucEccNumCount = pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount;

        for (i = 0; i < pstCustomCallEmerNumCtx->stCustomEccNumList.ucEccNumCount; i++)
        {
            pstCustomEccNum = &(pstCustomCallEmerNumCtx->stCustomEccNumList.astCustomEccNumList[i]);

            stNvimCustomEccNumList.astCustomEccNumList[i].ucCategory
                = pstCustomEccNum->ucCategory;
            stNvimCustomEccNumList.astCustomEccNumList[i].ulMcc
                = pstCustomEccNum->ulMcc;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucValidSimPresent
                = pstCustomEccNum->ucValidSimPresent;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucAbnormalServiceFlg
                = pstCustomEccNum->ucAbnormalServiceFlg;
            stNvimCustomEccNumList.astCustomEccNumList[i].ucEccNumLen
                = pstCustomEccNum->ucEccNumLen;
            (VOS_VOID)VOS_MemCpy(stNvimCustomEccNumList.astCustomEccNumList[i].aucEccNum,
                       pstCustomEccNum->aucEccNum,
                       pstCustomEccNum->ucEccNumLen);
        }

        /* ��Ƕ��ƽ��� */
        pstCustomCallEmerNumCtx->ucCustomSetFlg = VOS_FALSE;

        /* ��ȫ�ֱ���������б�д��NV */
        ulRst = NV_Write(en_NV_Item_CUSTOM_ECC_NUM_LIST,(VOS_VOID*)&stNvimCustomEccNumList,sizeof(MN_CALL_NVIM_CUSTOM_ECC_NUM_LIST_STRU));
        if (NV_OK != ulRst)
        {
            MN_ERR_LOG("MN_CALL_RcvTafEccNumReq:Write NVIM Error");
        }

        /* �������ϱ�����NV���ش� */
        if (VOS_TRUE == pstCustomCfg->ucReportEccNumFlg)
        {
            /* ��AT�ϱ���ǰ���еĽ��������� */
            MN_CALL_ReportEccNumList();
        }
    }

    return;
}


VOS_UINT32 MN_CALL_MakeNewCall(
    MN_CALL_TYPE_ENUM_U8                enCallType,
    MN_CALL_ID_T                       *pNewCallId
)
{
    MN_CALL_ID_T                        callId;


    /* ��ȡ���Կ���NV��ַ */

    /* ��MN Callģ���Ϸ���CallId MN_CALL_AllocCallId */

    /* ���NV�������Ƿ���������� MN_CALL_CheckNVAllowCallOrig */

    /* ����Ƿ���Է���/����һ���µĺ��� MN_CALL_IsAllowToMakeNewCall */


    if (VOS_FALSE == MN_CALL_CheckNVAllowCallOrig(enCallType))
    {
        MN_NORM_LOG("MN_CALL_MakeNewCall: Fail to MN_CALL_CheckNVAllowCallOrig.");
        return TAF_CS_CAUSE_NOT_ALLOW;
    }




    /* ��MN Callģ���Ϸ���CallId */
    if (VOS_OK != MN_CALL_AllocCallId(&callId))
    {
        MN_WARN_LOG("MN_CALL_MakeNewCall: Null Point.");
        return TAF_CS_CAUSE_NO_CALL_ID;
    }

    *pNewCallId = callId;

    /* ������������ʵ����״̬����HELD��IDLE����ܾ��º��� */
    if (VOS_TRUE != MN_CALL_IsAllowToMakeNewCall(callId, MN_CALL_DIR_MO))
    {
        MN_WARN_LOG("MN_CALL_MakeNewCall: ONLY SUPPORT ONE CALL.");
        MN_CALL_FreeCallId(callId);
        return TAF_CS_CAUSE_NOT_ALLOW;
    }

    return TAF_CS_CAUSE_SUCCESS;
}
VOS_VOID MN_CALL_RcvAtClprGetReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg)
{
    MN_CALL_CLPR_GET_CNF_STRU           stGetClprCnf;

    PS_MEM_SET(&stGetClprCnf, 0x00, sizeof(MN_CALL_CLPR_GET_CNF_STRU));

    /* ����MN_CALL_EVT_CLPR_GET_CNF��Ϣ */
    stGetClprCnf.stAppCtrl.usClientId = pstCallMsg->clientId;
    stGetClprCnf.stAppCtrl.ucOpId     = pstCallMsg->opId;
    stGetClprCnf.ulRet                = TAF_ERR_ERROR;
    stGetClprCnf.enEvent              = MN_CALL_EVT_CLPR_SET_CNF;

    /* ��������CALLID�Ƿ����,����Ϊ���� */

    if (VOS_TRUE == MN_CALL_CheckCallEntityExist(pstCallMsg->callId))
    {
        MN_CALL_ReadCallEntityRedirectInfo(pstCallMsg->callId, &stGetClprCnf);
    }

    MN_SendReportMsg(MN_CALLBACK_CS_CALL,
                    (VOS_UINT8*)&stGetClprCnf,
                    sizeof(MN_CALL_CLPR_GET_CNF_STRU));

}





VOS_VOID MN_CALL_StkCallOrigReqProc(struct MsgCB * pstMsg)
{
    VOS_UINT32                          ulRet;
    MN_CALL_ID_T                        NewcallId;
    MN_CALL_ID_T                        callId;

    VOS_BOOL                            bSupported;
    MN_APP_CALL_CALLORIG_REQ_STRU      *pstOrigParam = VOS_NULL_PTR;

    pstOrigParam = (MN_APP_CALL_CALLORIG_REQ_STRU *)pstMsg;

    NewcallId = 0;

    /* ��ȡ���Կ���NV��ַ */

    /* ��MN Callģ���Ϸ���CallId MN_CALL_AllocCallId */

    /* ���NV�������Ƿ���������� MN_CALL_CheckNVAllowCallOrig */

    /* ����Ƿ���Է���/����һ���µĺ��� MN_CALL_IsAllowToMakeNewCall */

    /*
       �ǽ������к��룬��ֱ�ӷ���EMERGENTCY SETUP CALL��Ϣ��CC��������:
       2.����EMERGENTCY SETUP CALL��Ϣ��CC��
       3.״̬Ǩ�Ƶ�MN_CALL_S_DIALING
       4.�㲥�ϱ�Ӧ������ȷ���¼�MN_CALL_EVT_NO_ERROR,
       5.�㲥���з���(ORIG)MN_CALL_EVT_ORIG
       6.��STK������ʱ��Ӧ��Ϣ��ԭ��ֵΪMN_ERR_NO_ERROR
       7.�˳�����
    */

     /*
       1.����SETUP CALL��Ϣ��CC��
       2.״̬Ǩ�Ƶ�MN_CALL_S_DIALING
       3.�㲥�ϱ�Ӧ������ȷ���¼�MN_CALL_EVT_NO_ERROR,
       4.�㲥���з���(ORIG)MN_CALL_EVT_ORIG
       5.��STK������ʱ��Ӧ��Ϣ��ԭ��ֵΪMN_ERR_NO_ERROR
       6.�˳�����

     */


    /* ��������У�֪ͨ���з��𷽺����쳣���� */
    ulRet = MN_CALL_MakeNewCall(pstOrigParam->enCallType, &NewcallId);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_NORM_LOG("MN_CALL_StkCallOrigReqProc: Fail to MN_CALL_MakeNewCall.");
        TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                 pstOrigParam->opID,
                                 pstOrigParam->callID,
                                 ulRet);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼CS�����쳣log */
        MN_CALL_CsCallErrRecord(NewcallId, ulRet);
#endif

        return;
    }
    callId = NewcallId;

    /* ����ǽ������У���ֱ�ӷ���CC,�������л���Ҫ����һϵ���ж� */
    if (MN_CALL_TYPE_EMERGENCY == pstOrigParam->enCallType)
    {
        MN_CALL_CreateStkMoCallEntity(callId, MN_CALL_TYPE_EMERGENCY, pstOrigParam);

        if (VOS_TRUE == pstOrigParam->stEmergencyCat.bExist)
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, &(pstOrigParam->stEmergencyCat.ucEmergencyCat));
        }
        else
        {
            ulRet = MN_CALL_SendCcEmergSetupReq(callId, VOS_NULL_PTR);
        }

        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: SEND MSG ERROR: emerge.");
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     TAF_CS_CAUSE_UNKNOWN);

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_UNKNOWN);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }
    else
    {
        MN_CALL_SupportMoCallType(pstOrigParam->enCallType, &bSupported);
        if (VOS_TRUE != bSupported)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: Fail to MN_CALL_SupportMoCallType.");
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, TAF_CS_CAUSE_CALL_CTRL_BEYOND_CAPABILITY);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }

        MN_CALL_CreateStkMoCallEntity(callId, pstOrigParam->enCallType, pstOrigParam);



        ulRet = MN_CALL_BuildNormalCallReqProc(callId);
        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("MN_CALL_StkCallOrigReqProc: MN_CALL_BuildNormalCallReqProc fail.");
            TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                                     pstOrigParam->opID,
                                     callId,
                                     ulRet);

#if (FEATURE_ON == FEATURE_PTM)
            /* ��¼CS�����쳣log */
            MN_CALL_CsCallErrRecord(callId, ulRet);
#endif

            MN_CALL_FreeCallId(callId);
            return;
        }
    }

    NAS_EventReport(WUEPS_PID_TAF,
                    NAS_OM_EVENT_CC_MO_ATTEMPT,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    MN_CALL_UpdateCallState(callId, MN_CALL_S_DIALING);

    /* ���֧�ֺ����ؽ����ܣ�������MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD��ʱ�� */
    if (VOS_TRUE == TAF_CALL_GetRedialSupportFlg(callId))
    {
        TAF_CALL_StartRedialPeriodTimer(callId);
    }

    TAF_CALL_SendCallOrigCnf(pstOrigParam->usClientId,
                             pstOrigParam->opID,
                             callId,
                             TAF_CS_CAUSE_SUCCESS);


    MN_CALL_ReportEvent(callId, MN_CALL_EVT_ORIG);

    MN_NORM_LOG("MN_CALL_StkCallOrigReqProc: send clint res normal and report event.");

    return;
}
VOS_VOID  MN_CALL_RcvAtCssnSetReq(
    MN_CLIENT_ID_T                      clientId,
    MN_OPERATION_ID_T                   opId,
    MN_CALL_SET_CSSN_REQ_STRU          *pstSetCssnReq
)
{
    MN_CALL_SET_CSSN_CNF_STRU           stSetCssnCnf;
    VOS_UINT32                          ulCssiRptStatus;
    VOS_UINT32                          ulCssuRptStatus;

    /* ����CSSI��CSSU��Ӧ��SDCȫ�ֱ��� */
    if (MN_CALL_SET_CSSN_ACT == pstSetCssnReq->aenSetType[0])
    {
        ulCssiRptStatus = VOS_TRUE;
    }
    else
    {
        ulCssiRptStatus = VOS_FALSE;
    }


    if (MN_CALL_SET_CSSN_ACT == pstSetCssnReq->aenSetType[1])
    {
        ulCssuRptStatus = VOS_TRUE;
    }
    else
    {
        ulCssuRptStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSI, ulCssiRptStatus);
    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_CSSU, ulCssuRptStatus);

    PS_MEM_SET(&stSetCssnCnf, 0, sizeof(stSetCssnCnf));
    stSetCssnCnf.ClientId = MN_GetRealClientId(clientId, WUEPS_PID_TAF);
    stSetCssnCnf.OpId     = opId;
    stSetCssnCnf.ulRet    = TAF_ERR_NO_ERROR;
    stSetCssnCnf.enEvent  = MN_CALL_EVT_SET_CSSN_CNF;

    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (VOS_UINT8*)&stSetCssnCnf, sizeof(stSetCssnCnf));

}
VOS_VOID MN_CALL_GetEccNumList(MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo)
{
    VOS_UINT32                          ulListFulled;

    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_GetEccNumList: pstEccNumInfo is NULL.");
        return;
    }

    /* �����н������붼�������Ϣ */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT != TAF_SDC_GetSimStatus())
    {
        /* ��Э�鶨����п�ʱ������������ϱ��б� */
        ulListFulled = MN_CALL_AddEmerNumsWithUsimToReportList(pstEccNumInfo);

        /* �б�δ���������еĽ��������������Ϣ */
        if (VOS_FALSE == ulListFulled)
        {
            ulListFulled = MN_CALL_AddEccNumsInUsimToReportList(pstEccNumInfo);
        }

        /* �б�δ������MM���ϱ��Ľ��������������Ϣ */
        if (VOS_FALSE == ulListFulled)
        {
           ulListFulled = MN_CALL_AddMmEccNumsToReportList(pstEccNumInfo);
        }
    }
    else
    {
        /* ��Э�鶨����޿�ʱ���������� */
        ulListFulled = MN_CALL_AddEmerNumsNoUsimToReportList(pstEccNumInfo);
    }

    /* �б�δ��,��APP���ƵĽ��������������Ϣ */
    if (VOS_FALSE == ulListFulled)
    {
       (VOS_VOID)MN_CALL_AddCustomEccNumsToReportList(pstEccNumInfo);
    }

    return;
}

VOS_VOID MN_CALL_RcvAtXlemaReq(MN_CALL_APP_REQ_MSG_STRU            *pstCallMsg)
{
    MN_CALL_ECC_NUM_INFO_STRU          *pstEccNumInfo = VOS_NULL_PTR;
    VOS_UINT16                          usLen;

    pstEccNumInfo = (MN_CALL_ECC_NUM_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(MN_CALL_ECC_NUM_INFO_STRU));
    if (VOS_NULL_PTR == pstEccNumInfo)
    {
        MN_WARN_LOG("MN_CALL_RcvAtXlemaReq: Alloc Mem Fail.");
        return;
    }

    /* ��Ϣ��ʼ�� */
    PS_MEM_SET(pstEccNumInfo, 0, sizeof(MN_CALL_ECC_NUM_INFO_STRU));

    pstEccNumInfo->enEvent    = MN_CALL_EVT_XLEMA_CNF;
    pstEccNumInfo->usClientId = pstCallMsg->clientId;

    /* ��ȡ�������б� */
    MN_CALL_GetEccNumList(pstEccNumInfo);

    usLen = (VOS_UINT16)sizeof(MN_CALL_ECC_NUM_INFO_STRU);

    /* �ϱ�AT */
    MN_SendReportMsg(MN_CALLBACK_CS_CALL, (TAF_UINT8 *)pstEccNumInfo, usLen);

    /* �ڴ��ͷ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstEccNumInfo);

    return;
}



VOS_VOID  TAF_CALL_RcvStartDtmfReq(struct MsgCB * pstStartDtmf)
{
    MN_CALL_ID_T                        CallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq       = VOS_NULL_PTR;
    TAF_CALL_DTMF_PARAM_STRU           *pstDtmfParam    = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(stDtmfInfo));

    pstAppReq               = ((MN_CALL_APP_REQ_MSG_STRU *)pstStartDtmf);
    pstDtmfParam            = &pstAppReq->unParm.stDtmf;
    stDtmfInfo.CallId       = pstDtmfParam->CallId;
    stDtmfInfo.cKey         = pstDtmfParam->cKey;
    stDtmfInfo.usOnLength   = pstDtmfParam->usOnLength;
    stDtmfInfo.usClientId   = pstAppReq->clientId;
    stDtmfInfo.opId         = pstAppReq->opId;

    stDtmfInfo.usOffLength  = pstDtmfParam->usOffLength;

    /* DTMF��Ϣ�Ϸ����ж� */
    if ( (VOS_OK != TAF_SDC_CheckDtmfKey(&stDtmfInfo.cKey))
      || (stDtmfInfo.usOnLength < TAF_CALL_DTMF_MIN_ONLENGTH) )
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_INVALID_PARAMETER);
        return;
    }

    /* ���жϵ�ǰ�Ƿ�������DTMF���ٻ�ȡ���п��Է���DTMF�ĺ���ID */
    ulResult    = TAF_CALL_CheckUserDtmfCallId(stDtmfInfo.CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    /* �ж�DTMF״̬�Ƿ����� */
    if (TAF_CALL_GetDtmfState() >= TAF_CALL_DTMF_STATE_BUTT)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_STATE_ERROR);
        return;
    }

    /* DTMF���ڷǿ���״̬���򻺴��DTMF */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_IDLE)
    {
        ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    /* DTMF��ǰ���ڿ���̬�����͵�CC */
    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
    *pstDtmfCurInfo = stDtmfInfo;

    /* ��ȡ����DTMF��CALL ID */
    CallId   = 0;
    ulResult = TAF_CALL_GetAllowedDtmfCallId(&CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             ulResult);
        return;
    }

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_START_DTMF_CNF,
                             TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* ���ͳɹ�������DTMF״̬ */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                         stDtmfInfo.opId,
                         MN_CALL_EVT_START_DTMF_CNF,
                         TAF_CS_CAUSE_SUCCESS);

    return;
}
VOS_VOID  TAF_CALL_RcvStopDtmfReq(struct MsgCB * pstStopDtmf)
{
    MN_CALL_ID_T                        CallId;
    MN_CALL_APP_REQ_MSG_STRU           *pstAppReq       = VOS_NULL_PTR;
    TAF_CALL_DTMF_PARAM_STRU           *pstDtmfParam    = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU             stDtmfInfo;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;
    TAF_CALL_DTMF_STATE_ENUM_UINT8      enDtmfState;
    VOS_UINT32                          ulResult;

    PS_MEM_SET(&stDtmfInfo, 0, sizeof(stDtmfInfo));

    pstAppReq               = ((MN_CALL_APP_REQ_MSG_STRU *)pstStopDtmf);
    pstDtmfParam            = &pstAppReq->unParm.stDtmf;
    stDtmfInfo.CallId       = pstDtmfParam->CallId;
    stDtmfInfo.cKey         = pstDtmfParam->cKey;
    stDtmfInfo.usOnLength   = pstDtmfParam->usOnLength;
    stDtmfInfo.usClientId   = pstAppReq->clientId;
    stDtmfInfo.opId         = pstAppReq->opId;
    enDtmfState             = TAF_CALL_GetDtmfState();

    stDtmfInfo.usOffLength  = pstDtmfParam->usOffLength;

    /* STOP_DTMF����ʱ��OnLengthֵ��Ϊ0 */
    if (0 != stDtmfInfo.usOnLength)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_INVALID_PARAMETER);
        return;
    }

    /* �ж�DTMF״̬�Ƿ����� */
    if ( (TAF_CALL_DTMF_STATE_BUTT <= enDtmfState)
      || (TAF_CALL_DTMF_IDLE == enDtmfState) )
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_STATE_ERROR);
        return;
    }

    /* ���жϵ�ǰ�Ƿ�������DTMF���Լ��û�����ĺ���ID�Ƿ���Է���DTMF */
    ulResult    = TAF_CALL_CheckUserDtmfCallId(stDtmfInfo.CallId);
    if (TAF_CS_CAUSE_SUCCESS != ulResult)
    {
        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             ulResult);
        return;
    }

    /* �����ǰû�л����Ҵ��ڵȴ���ʱ����ʱ״̬����ͣ��ʱ��������STOP_DTMF�����򻺴� */
    if ( (0 == TAF_CALL_GetDtmfBufCnt())
      && (TAF_CALL_DTMF_WAIT_ON_LENGTH_TIME_OUT == enDtmfState))
    {
        MN_CALL_StopTimer(TAF_CALL_TID_DTMF_ON_LENGTH);


        pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();
        *pstDtmfCurInfo = stDtmfInfo;

        /* ��ȡ����DTMF��CALL ID */
        CallId = 0;
        ulResult = TAF_CALL_GetAllowedDtmfCallId(&CallId);
        if (TAF_CS_CAUSE_SUCCESS != ulResult)
        {
            TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                                 stDtmfInfo.opId,
                                 MN_CALL_EVT_STOP_DTMF_CNF,
                                 ulResult);
            return;
        }

        if (VOS_OK != MN_CALL_SendCcStopDtmfReq(CallId))
        {
            TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                                 stDtmfInfo.opId,
                                 MN_CALL_EVT_STOP_DTMF_CNF,
                                 TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* ���ͳɹ�������DTMF״̬ */
        TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_STOP_CNF);

        TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                             stDtmfInfo.opId,
                             MN_CALL_EVT_STOP_DTMF_CNF,
                             TAF_CS_CAUSE_SUCCESS);
        return;
    }

    /* ��ǰ���ܷ���STOP_DTMF�����򻺴� */
    ulResult = TAF_CALL_SaveDtmfInfo(&stDtmfInfo);

    TAF_CALL_SendDtmfCnf(stDtmfInfo.usClientId,
                         stDtmfInfo.opId,
                         MN_CALL_EVT_STOP_DTMF_CNF,
                         ulResult);
    return;
}

#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(
    VOS_UINT8                           ucCallId
)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    if ((VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
     && (ucCallId == pstBufferdMsg->stBufferedSetupMsg.ucCallId))
    {
        MN_CALL_ClearBufferedMsg();

        /* ֹͣeCall�ز���ʱ�� */
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
    }
}
VOS_VOID TAF_CALL_RcvQryEcallInfoReq(MN_CALL_QRY_ECALL_INFO_REQ_STRU *pstQryEcallInfoReq)
{
    MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU stQryEcallCnf;
    MN_CALL_MGMT_STRU                  *pstCallEntityAddr = VOS_NULL_PTR;
    VOS_UINT8                           i;

    PS_MEM_SET(&stQryEcallCnf, 0, sizeof(MN_CALL_EVT_QRY_ECALL_INFO_CNF_STRU));

    /* �ں���ʵ���л�ȡMO eCall���е������Ϣ */
    pstCallEntityAddr = TAF_CALL_GetCallEntityAddr();

    for (i = 0; i < MN_CALL_MAX_NUM; i++)
    {
        if (VOS_FALSE == pstCallEntityAddr->bUsed)
        {
            pstCallEntityAddr++;

            continue;
        }

        /* ��ȡeCall������Ϣ */
        if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(pstCallEntityAddr->stCallInfo.callId))
        {
            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].ucCallId    =
                pstCallEntityAddr->stCallInfo.callId;

            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].enCallState =
                pstCallEntityAddr->stCallInfo.enCallState;

            stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].enEcallType =
                pstCallEntityAddr->stCallInfo.enCallType;

            PS_MEM_CPY(&(stQryEcallCnf.stEcallInfo.astEcallInfos[stQryEcallCnf.stEcallInfo.ucNumOfEcall].stDialNumber),
                       &(pstCallEntityAddr->stCallInfo.stCalledNumber),
                       sizeof(MN_CALL_CALLED_NUM_STRU));

            stQryEcallCnf.stEcallInfo.ucNumOfEcall++;
        }

        pstCallEntityAddr++;
    }

    stQryEcallCnf.ucOpId     = pstQryEcallInfoReq->ucOpId;
    stQryEcallCnf.usClientId = pstQryEcallInfoReq->usClientId;

    /* ������Ϣ��������Ϣ�Ĳ�ѯ�� */
    TAF_CALL_SendQueryEcallInfoCnf(pstQryEcallInfoReq->usClientId,
                                   pstQryEcallInfoReq->ucOpId,
                                   &stQryEcallCnf);
}
VOS_VOID TAF_CALL_EcallSupsCmdRelReqProc(
    MN_CLIENT_ID_T                      usClientId,
    MN_OPERATION_ID_T                   ucOpId,
    const MN_CALL_SUPS_PARAM_STRU      *pstCallSupsParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;

    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    if (0 != ulNumOfCalls)
    {
        /* �Ҷ���������ͨ����eCall���� */
        for (i = 0; i < ulNumOfCalls; i++)
        {
            if (VOS_FALSE == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
            {
                /* ECLSTOP������ܹҶ�eCall���� */
                continue;
            }

            /* ���"�ȴ�mt eCall���б�־λ" */
            TAF_CALL_SetWaitingMtEcallFlag(VOS_FALSE);

            MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);
            MN_CALL_UpdateClientId(aCallIds[i], usClientId);

            /* ������д���dialing״̬���Һ����ط������ʱ�������У�cc����U0״̬������
               ��cc����disconnect��Ϣ���������rej ind��Ϣ */
            if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(aCallIds[i]))
             && (MN_CALL_S_DIALING           == enCallState))
            {
                TAF_CALL_RelRedialingCall(usClientId, ucOpId, pstCallSupsParam);
                return;
            }

            if ((MN_CALL_S_INCOMING            == enCallState)
             || (MN_CALL_S_WAITING             == enCallState)
             || (MN_CALL_S_CCBS_WAITING_RECALL == enCallState))
            {
                TAF_CALL_RelIncomingOrWaitingCall(aCallIds[i], enCallState);
            }
            else
            {
                (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼�����Ҷϵ�ԭ��ֵ */
                MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼���йҶϵķ��� */
                MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

                /* ���T9��ʱ�������У�ֹͣT9��ʱ�� */
                if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_T9))
                {
                    /* ֹͣT9��ʱ�� */
                    MN_CALL_StopTimer(TAF_CALL_TID_T9);
                }

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }

            MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_SETUP_COMPL);
            MN_CALL_DeRegSsKeyEvent(aCallIds[i],MN_CALL_SS_PROG_EVT_REL);
        }

        MN_CALL_RegSsKeyEvent(aCallIds[i-1],
                              MN_CALL_SS_PROG_EVT_REL,
                              MN_CALL_SS_SUBSEQ_OP_RPT_SUCC);

        MN_CALL_CallSupsCmdReqCommProc(usClientId, ucOpId, pstCallSupsParam, TAF_CS_CAUSE_SUCCESS);

        return;
    }

    TAF_CALL_SendSupsCmdCnf(usClientId, ucOpId, pstCallSupsParam->callId, TAF_CS_CAUSE_SUCCESS);

    TAF_CALL_UpdateCallInfoWhenSendSupsCmdCnf(usClientId,
                                              ucOpId,
                                              pstCallSupsParam->callId,
                                              TAF_CS_CAUSE_SUCCESS);
}
#endif

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



