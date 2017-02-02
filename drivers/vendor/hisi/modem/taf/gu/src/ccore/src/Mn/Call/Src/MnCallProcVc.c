


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "MnCallProcVc.h"
#include "MnCallApi.h"
#include "MnCallMgmt.h"
#include "MnCallReqProc.h"
#include "MnCallCtx.h"
#include "MnComm.h"
#include "MnCallTimer.h"
#include "MnCallSendCc.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_MN_CALL_PROC_VC_C

/*****************************************************************************
   2 ��������
*****************************************************************************/
/* call���к�����Ϣ */
LOCAL MN_CALL_INFO_STRU                   f_astCallInfos[MN_CALL_MAX_NUM];

VC_TO_TAFCS_CAUSE_STRU                    g_astVcCauseToTafCsCause[] =
{
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED         ,   TAF_CS_CAUSE_VC_ERR_STARTED         },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_PORT_CFG_FAIL   ,   TAF_CS_CAUSE_VC_ERR_PORT_CFG_FAIL   },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_DEVICE_FAIL ,   TAF_CS_CAUSE_VC_ERR_SET_DEVICE_FAIL },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL  ,   TAF_CS_CAUSE_VC_ERR_SET_START_FAIL  },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_VOLUME_FAIL ,   TAF_CS_CAUSE_VC_ERR_SET_VOLUME_FAIL },
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SAMPLE_RATE_FAIL,   TAF_CS_CAUSE_VC_ERR_SAMPLE_RATE_FAIL},
    {APP_VC_OPEN_CHANNEL_FAIL_CAUSE_TI_START_EXPIRED,   TAF_CS_CAUSE_VC_ERR_TI_START_EXPIRED},
};
/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID TAF_CALL_RcvVcCallEndCall(VC_CALL_MSG_STRU *pstEndCall)
{
    TAF_UINT8                           ucNumOfCalls;
    MN_CALL_END_PARAM_STRU              stEndParm;
    VOS_UINT32                          ulRet;

    /* ECALLʱ�յ�MED��AlAck�ϱ�����Ϊ�������Ҷϣ���ԭ��ֵ#16 */
    stEndParm.enEndCause    = TAF_CALL_ConvertVcCauseToTafCsCause(pstEndCall->enCause);

    MN_CALL_GetCallInfoList(&ucNumOfCalls,f_astCallInfos);
    if (ucNumOfCalls != 0)
    {
        ulRet = MN_CALL_InternalCallEndReqProc(MN_CLIENT_ALL,
                                               0,
                                               f_astCallInfos[0].callId,
                                               &stEndParm);
        if (TAF_CS_CAUSE_SUCCESS != ulRet)
        {
            MN_WARN_LOG("TAF_CALL_RcvVcCallEndCall: Fail to MN_CALL_InternalCallEndReqProc.");
        }
    }
}

#if (FEATURE_ON == FEATURE_ECALL)
VOS_VOID TAF_CALL_ProcEcallMsdTransSuccess(VOID)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCallId;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    MN_CALL_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* Added by w00316404 for clean coverity, 2015-4-2, begin */
    enCallState                         = MN_CALL_S_BUTT;
    /* Added by w00316404 for clean coverity, 2015-4-2, end */


    pstBufferdMsg = MN_CALL_GetBufferedMsg();
    if (VOS_FALSE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
        /* �޻��棬ֱ�Ӹ���MSD״̬����ʼ̬ */
        TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
        return;
    }

    enTimerStatus = MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);

    if ((MN_CALL_TIMER_STATUS_RUNING != MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD))
     && (MN_CALL_TIMER_STATUS_RUNING != enTimerStatus))
    {
        /* �����ʱ�����������У�Ӧ������eCallͨ���У�MSD����ɹ�������״̬ */
        TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS);
        return;
    }

    ucCallId = pstBufferdMsg->stBufferedSetupMsg.ucCallId;

    /* 1. �������Ǵ��������������ͷ���ɣ�������յ�MSD���ݴ���ɹ���״ָ̬ʾ
     *    ��ʱ��Ҫֹͣ�ز���ʱ�����ͷ���Դ���ϱ������ͷ����
     */
    MN_CALL_GetCallState(ucCallId, &enCallState, &enMptyState);

    /* ��dialing״̬�Ҽ����ʱ��������ʱ��������Ϣ��δ���͸�CC����˱����ͷź��оͿ����� */
    if ((MN_CALL_TIMER_STATUS_RUNING == TAF_CALL_GetRedialIntervalTimerStatus(ucCallId))
     && (MN_CALL_S_DIALING           == enCallState))
    {
        /* �ϱ������ͷ��¼� */
        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_RELEASED);

        MN_CALL_ReportEvent(ucCallId, MN_CALL_EVT_ALL_RELEASED);

        TAF_CALL_ProcCallStatusFail(ucCallId, enCallState);

        MN_CALL_FreeCallId(ucCallId);
    }
    else
    {
        /*�Ҷ�ָ���ĺ���*/
        (VOS_VOID)MN_CALL_SendCcDiscReq(ucCallId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼�����Ҷϵ�ԭ��ֵ */
        MN_CALL_UpdateCcCause(ucCallId, MN_CALL_NORMAL_CALL_CLEARING);

        /* ��¼���йҶϵķ��� */
        MN_CALL_UpdateDiscCallDir(ucCallId, VOS_TRUE);
    }

    /* ���MO�����ز����� */
    MN_CALL_ClearBufferedMsg();

    /* ֹͣ����eCall�ز�ʱ����ʱ�� */
    TAF_CALL_StopAllRedialTimers(ucCallId);

    /* �����ͷţ�����MSD״̬����ʼ̬ */
    TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
}


VOS_VOID TAF_CALL_RcvVcEcallTransStatusNtf(VC_CALL_ECALL_TRANS_STATUS_NTF_STRU *pstEcallTransStatusNtf)
{


    switch (pstEcallTransStatusNtf->enEcallTransStatus)
    {
        case VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS:
            TAF_CALL_ProcEcallMsdTransSuccess();
            break;

        case VC_CALL_ECALL_MSD_TRANSMITTING_FAIL:
        case VC_CALL_ECALL_MSD_TRANSMITTING_START:
        case VC_CALL_ECALL_PSAP_MSD_REQUIRETRANSMITTING:
            /* ����eCall MSD���ݴ���״̬ */
            TAF_CALL_SetEcallMsdTransStatus(pstEcallTransStatusNtf->enEcallTransStatus);
            break;

        default:
            /* �Ƿ�ֵ�����µ�butt */
            TAF_CALL_SetEcallMsdTransStatus(VC_CALL_ECALL_TRANS_STATUS_BUTT);
            break;
    }
}
#endif


TAF_CS_CAUSE_ENUM_UINT32 TAF_CALL_ConvertVcCauseToTafCsCause(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32 enVcCause
)
{
    TAF_CS_CAUSE_ENUM_UINT32            enTafCause;
    VOS_UINT32                          i;

    enTafCause  = TAF_CS_CAUSE_CC_NW_NORMAL_CALL_CLEARING;

    for (i = 0; i < (sizeof(g_astVcCauseToTafCsCause) / sizeof(g_astVcCauseToTafCsCause[0])); i++)
    {
        if (enVcCause == g_astVcCauseToTafCsCause[i].enVcCause)
        {
            enTafCause = g_astVcCauseToTafCsCause[i].enTafCsCasue;
        }
    }

    return enTafCause;

}

/*lint -restore */


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



