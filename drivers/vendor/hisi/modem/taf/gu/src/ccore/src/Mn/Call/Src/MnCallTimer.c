/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : MnCallTimer.c
  �� �� ��   : ����
  ��    ��   : dfakl;f
  ��������   : 2010��5��19��
  ����޸�   :
  ��������   : dakfdjk
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2010��5��19��
    ��    ��   : dfakl;f
    �޸�����   : �����ļ�

******************************************************************************/

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include  "vos.h"
#include  "MnCallApi.h"
#include  "MnCallMgmt.h"
#include  "MnComm.h"
#include  "NasComm.h"
#include  "MnCallReqProc.h"
#include  "MnCallTimer.h"
#include "MnErrorCode.h"
#include "TafLog.h"


#include "MnCallSendCc.h"
#include "MnCallCtx.h"

#include "MnCallMgmt.h"
#include "MnCallSendApp.h"
#include "TafSdcCtx.h"

#define    THIS_FILE_ID  PS_FILE_ID_MNCALL_TIMER_C

/*****************************************************************************
  1 ȫ�ֱ�������
*************************************************************************/

/* ���п��õĶ�ʱ����Դ */
MN_CALL_TIMER_HANDLE_STRU                g_astCallTimerHandle[MN_CALL_TID_BUTT - MN_TIMER_CLASS_CCA];

/*��ʱ����Ϣ���ñ��м�¼��ÿ�ֶ�ʱ���ĳ�ʱʱ��ͳ�ʱ������ */
MN_CALL_TIMER_INFO_STRU                  g_astCallTimerInfoTbl[MN_CALL_TID_BUTT - MN_TIMER_CLASS_CCA] =
{
    {5000, MN_CALL_CstSetupTimeout},                                            /* ����setup��Ϣ��ĳ�ʱ���� */
    {6000, MN_CALL_RingTimerTimeout},                                           /* ѭ���ϱ�Ring�Ĵ��� */



    {30000, MN_CALL_CallRedialPeriodTimeout},
    {5000,  MN_CALL_CallRedialIntervalTimeout},

    {TAF_CALL_DTMF_DEFAULT_ONLENGTH, TAF_CALL_RcvTiDtmfOnLengthExpired},

    {TAF_CALL_DTMF_DEFAULT_OFFLENGTH, TAF_CALL_RcvTiDtmfOffLengthExpired},

#if (FEATURE_ON == FEATURE_ECALL)
    {TAF_ECALL_REDIAL_PERIOD_TIMER_LENGTH,                             TAF_CALL_EcallRedialPeriodTimeout},
    {TAF_ECALL_REDIAL_INTERVAL_TIMER_LENGTH,                           TAF_CALL_EcallRedialIntervalTimeout},

    {TAF_CALL_T2_TIMER_LENGTH,                                         TAF_CALL_RcvT2TimerExpired},

    {(TAF_CALL_T9_MIN_TIMER_LENGTH*TAF_CALL_ONE_HOUR_TIMER_LENGTH),    TAF_CALL_RcvT9TimerExpired}
#endif


};


/*lint -save -e958 */

/*****************************************************************************
  2 ��������
*****************************************************************************/

VOS_VOID MN_CALL_RingTimerTimeout(
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulNumOfCalls;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];

    ulNumOfCalls = 0;
    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));


    /* ֹͣMN_CALL_TID_RING��ʱ�� */
    MN_CALL_StopTimer(MN_CALL_TID_RING);

    MN_CALL_GetCallsByState(MN_CALL_S_INCOMING, &ulNumOfCalls, aCallIds);

    if ( 0 != ulNumOfCalls )
    {
        /* ������ʱ��MN_CALL_TID_RING */
        MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);

        MN_CALL_ReportEvent(aCallIds[0], MN_CALL_EVT_INCOMING);

        return;
    }

    MN_CALL_GetCallsByState(MN_CALL_S_WAITING, &ulNumOfCalls, aCallIds);

    if ( 0 != ulNumOfCalls )
    {
        /* ������ʱ��MN_CALL_TID_RING */
        MN_CALL_StartTimer(MN_CALL_TID_RING, 0, 0, VOS_RELTIMER_NOLOOP);

        MN_CALL_ReportEvent(aCallIds[0], MN_CALL_EVT_INCOMING);

        return;
    }

}
VOS_VOID  MN_CALL_CstSetupTimeout(
    VOS_UINT32                          ulParam
)
{
    MN_CALL_END_PARAM_STRU              stEndParm;
    VOS_UINT32                          ulNumOfCalls;
    VOS_UINT8                           i;
    MN_CALL_ID_T                        aCallIds[MN_CALL_MAX_NUM];
    MN_CALL_TYPE_ENUM_U8                enCallType;
    MN_CALL_INFO_STRU                   stCallInfo;
    VOS_UINT32                          ulRet;

    MN_CALL_StopTimer(MN_CALL_TID_WAIT_CST_SETUP);


    PS_MEM_SET(aCallIds, 0x00, sizeof(aCallIds));

    stEndParm.enEndCause = MN_CALL_INTERWORKING_UNSPECIFIED;


    PS_MEM_SET(&stCallInfo, 0x00, sizeof(stCallInfo));

    /* ���ҵ�ǰ���ڵ�video call��������ڣ����˳�ѭ�� */
    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);
    for ( i = 0; i < ulNumOfCalls; i++ )
    {
        enCallType = MN_CALL_GetCallType(aCallIds[i]);
        if ( MN_CALL_TYPE_VIDEO == enCallType )
        {
            break;
        }

    }

    if ( ulNumOfCalls == i )
    {
        MN_WARN_LOG("MN_CALL_CstSetupTimeout: no video type call exist.");
        return;
    }

    MN_CALL_GetCallInfoByCallId(aCallIds[i],&stCallInfo);
    ulRet = MN_CALL_InternalCallEndReqProc(stCallInfo.clientId,
                                           0,
                                           aCallIds[i],
                                           &stEndParm);
    if (TAF_CS_CAUSE_SUCCESS != ulRet)
    {
        MN_WARN_LOG("MN_CALL_CstSetupTimeout: Fail to MN_CALL_InternalCallEndReqProc.");
    }
}
VOS_VOID  MN_CALL_StartTimer(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId,
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucTimerMode
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulTimeLen;


    if (enTimerId >= (sizeof(g_astCallTimerInfoTbl)/sizeof(g_astCallTimerInfoTbl[0])))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "MN_CALL_StartTimer: enTimerId error!");
        return;
    }

    /* Ѱ�ҿ��еĶ�ʱ����� */
    for (i = 0; i < MN_CALL_TID_BUTT; i++)
    {
        if (MN_CALL_TID_BUTT == g_astCallTimerHandle[i].enTimerId)
        {
            break;
        }
    }

    if (i < MN_CALL_TID_BUTT)
    {
        /* ����VOS��ʱ�� */
        ulTimeLen = ulLength;
        if (0 == ulTimeLen)
        {
            ulTimeLen = g_astCallTimerInfoTbl[enTimerId].ulTimeout;
        }

        /* ��Ҫ��TimerId���� */
        if (VOS_OK == NAS_StartRelTimer(&g_astCallTimerHandle[i].hTimer,
                                        WUEPS_PID_TAF,
                                        ulTimeLen,
                                        enTimerId,
                                        ulParam,
                                        ucTimerMode))
        {
            g_astCallTimerHandle[i].enTimerId = enTimerId;

            g_astCallTimerHandle[i].enTimerStatus = MN_CALL_TIMER_STATUS_RUNING;
        }
        else
        {
            MN_ERR_LOG("MN_CALL_StartTimer: VOS_StartRelTimer failed.");
        }
    }
    else
    {
        MN_ERR_LOG("MN_CALL_StartTimer: Can not find free timer handle.");
    }

}
VOS_VOID MN_CALL_StopTimer(
    MN_CALL_TIMER_ID_ENUM_U32            enTimerId
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if ( enTimerId >= MN_CALL_TID_BUTT )
    {
        return;
    }

    /* Ѱ��enTimerId������ƥ��ľ�� */
    for (i = 0; i < (MN_CALL_TID_BUTT - MN_TIMER_CLASS_CCA); i++)
    {
      if (enTimerId == g_astCallTimerHandle[i].enTimerId)
      {
          break;
      }
    }

    if (i < (MN_CALL_TID_BUTT - MN_TIMER_CLASS_CCA))
    {
        /* ֹͣVOS��ʱ�� */
        ulRet = NAS_StopRelTimer(WUEPS_PID_TAF, enTimerId, &g_astCallTimerHandle[i].hTimer);
        if (VOS_OK == ulRet)
        {
            g_astCallTimerHandle[i].hTimer = VOS_NULL_PTR;
            g_astCallTimerHandle[i].enTimerId = MN_CALL_TID_BUTT;

            g_astCallTimerHandle[i].enTimerStatus = MN_CALL_TIMER_STATUS_STOP;
        }
        else
        {
            MN_WARN_LOG("MN_CALL_StopTimer: NAS_StopRelTimer failed.");
        }
    }
    else
    {
        MN_INFO_LOG("MN_CALL_StopTimer: Can not find the timer handle.");
    }
}



VOS_VOID  MN_CALL_ProcTimeoutMsg(
    REL_TIMER_MSG                       *pTmrMsg
)
{
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId;

    /* �ҵ���Ӧ��TimerId��ִ�ж�Ӧ�ĳ�ʱ������ */
    enTimerId = (MN_CALL_TIMER_ID_ENUM_U32)pTmrMsg->ulName - MN_TIMER_CLASS_CCA;

    if (enTimerId < (sizeof(g_astCallTimerInfoTbl)/sizeof(g_astCallTimerInfoTbl[0])))
    {
        g_astCallTimerInfoTbl[enTimerId].pfnTimeoutProc(pTmrMsg->ulPara);
    }
    else
    {
        MN_ERR_LOG("MN_CALL_ProcTimeoutMsg: TimerId out of range.");
    }
}
VOS_VOID  MN_CALL_InitAllTimers(MN_CALL_POWER_STATE_ENUM_U8 enPowerState)
{
    VOS_UINT32                          i;

    /* �ػ�״̬��Ҫ���ж��Ƿ��������Ķ�ʱ��,�������Ҫ��ֹͣ��ʱ��*/
    if (MN_CALL_POWER_STATE_OFF == enPowerState)
    {
        for (i = 0; i < (MN_CALL_TID_BUTT - MN_TIMER_CLASS_CCA); i++)
        {
            if ((MN_CALL_TID_BUTT != g_astCallTimerHandle[i].enTimerId)
             && (g_astCallTimerHandle[i].hTimer != VOS_NULL_PTR))
            {
                MN_CALL_StopTimer(g_astCallTimerHandle[i].enTimerId);
            }
        }
    }

    for ( i = 0; i < (MN_CALL_TID_BUTT - MN_TIMER_CLASS_CCA); i++)
    {
        g_astCallTimerHandle[i].hTimer    = VOS_NULL_PTR;
        g_astCallTimerHandle[i].enTimerId = MN_CALL_TID_BUTT;

        g_astCallTimerHandle[i].enTimerStatus = MN_CALL_TIMER_STATUS_STOP;
    }
}
VOS_VOID MN_CALL_UpdateTimerPeriod(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId,
    VOS_UINT32                          ulTimerLen
)
{
    if (enTimerId >= (sizeof(g_astCallTimerInfoTbl) / sizeof(g_astCallTimerInfoTbl[0])))
    {
        MN_WARN_LOG("MN_CALL_UpdateTimerPeriod: Can not find the timer Id.");
        return;
    }

    g_astCallTimerInfoTbl[enTimerId].ulTimeout = ulTimerLen;
}



VOS_UINT32 MN_CALL_GetTimerLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
)
{
    if (enTimerId >= (sizeof(g_astCallTimerInfoTbl) / sizeof(g_astCallTimerInfoTbl[0])))
    {
        MN_WARN_LOG("MN_CALL_GetTimerLen: Can not find the timer Id.");
        return 0;
    }

    return g_astCallTimerInfoTbl[enTimerId].ulTimeout;
}



VOS_VOID MN_CALL_CallRedialPeriodTimeout(VOS_UINT32 ulParam)
{
    MN_CALL_StopTimer(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD);

    return;
}


VOS_VOID MN_CALL_CallRedialIntervalTimeout(VOS_UINT32 ulParam)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT32                          ulRslt;


    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    MN_CALL_GetCallState(pstBufferdMsg->stBufferedSetupMsg.ucCallId, &enCallState, &enMptyState);

    MN_CALL_StopTimer(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL);

    if (MN_CALL_S_DIALING != enCallState)
    {
        MN_WARN_LOG("MN_CALL_CallRedialIntervalTimeout: call state is invalid.");
        MN_CALL_ClearBufferedMsg();
        MN_CALL_StopTimer(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD);
        return;
    }

    /* ȡ������Ϣ */
    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
        if (MN_CALL_TYPE_EMERGENCY == MN_CALL_GetCallType(pstBufferdMsg->stBufferedSetupMsg.ucCallId))
        {
            ulRslt = MN_CALL_SendCcBufferedEmgSetupReq(&pstBufferdMsg->stBufferedSetupMsg);
        }
        else
        {
            ulRslt = MN_CALL_SendCcBufferedSetupReq(&pstBufferdMsg->stBufferedSetupMsg);
        }

        /* ��Ϣ���ͳɹ����أ����������rej ind��Ϣ*/
        if (VOS_TRUE == ulRslt)
        {
            return;
        }
    }

    MN_CALL_StopTimer(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD);

    /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
    TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg,
        TAF_CS_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
    /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */

    return;

}


VOS_UINT32  MN_CALL_GetTimerRemainLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
)
{
    VOS_UINT32                          ulTick;
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulTimerNum;

    ulTick     = 0;
    ulTimerNum = sizeof(g_astCallTimerInfoTbl) / sizeof(g_astCallTimerInfoTbl[0]);

    if (enTimerId >= MN_CALL_TID_BUTT)
    {
        return 0;
    }

    for (ulIndex = 0; ulIndex < ulTimerNum; ulIndex++)
    {
        if (enTimerId == g_astCallTimerHandle[ulIndex].enTimerId)
        {
            break;
        }
    }

    if (ulIndex >= ulTimerNum)
    {
       return 0;
    }

    /* hTimer Ϊ��ʱ��˵���˶�ʱ���ѳ�ʱ��ֹͣ */
    if (VOS_NULL_PTR != g_astCallTimerHandle[ulIndex].hTimer)
    {
        if (VOS_OK != VOS_GetRelTmRemainTime(&(g_astCallTimerHandle[ulIndex].hTimer), &ulTick))
        {
            ulTick = 0;
        }
    }

    /* tickֵ����10ת��Ϊ���� */
    return ulTick * MN_CALL_TIMER_TICK;
}



MN_CALL_TIMER_STATUS_ENUM_U8  MN_CALL_GetTimerStatus(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
)
{
    VOS_UINT32                          ulIndex;
    VOS_UINT32                          ulTimerNum;

    ulTimerNum = sizeof(g_astCallTimerInfoTbl) / sizeof(g_astCallTimerInfoTbl[0]);

    if (enTimerId >= ulTimerNum)
    {
        return MN_CALL_TIMER_STATUS_STOP;
    }

    for (ulIndex = 0; ulIndex < ulTimerNum; ulIndex++)
    {
        if (enTimerId == g_astCallTimerHandle[ulIndex].enTimerId)
        {
            return g_astCallTimerHandle[ulIndex].enTimerStatus;
        }
    }

    return MN_CALL_TIMER_STATUS_STOP;
}



VOS_VOID TAF_CALL_RcvTiDtmfOnLengthExpired(
    VOS_UINT32                          ulParam
)
{
    MN_CALL_ID_T                        CallId;

    MN_CALL_StopTimer(TAF_CALL_TID_DTMF_ON_LENGTH);

    /* �ж�״̬�Ƿ��쳣 */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_WAIT_ON_LENGTH_TIME_OUT)
    {
        MN_WARN_LOG("TAF_CALL_RcvTiDtmfOnLengthExpired: Dtmf State Error!");
        return;
    }

    /* ��ȡ������������DTMF��CallId����ȡʧ������ջ�������DTMF״̬���˳� */
    CallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
    {
        MN_WARN_LOG("TAF_CALL_RcvTiDtmfOnLengthExpired: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    if (VOS_OK != MN_CALL_SendCcStopDtmfReq(CallId))
    {
        MN_ERR_LOG("TAF_CALL_RcvTiDtmfExpired: Send Stop Dtmf Failed!");
        return;
    }

    /* ���ͳɹ�������DTMF״̬ */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_AUTO_STOP_CNF);

    return;
}


VOS_VOID TAF_CALL_RcvTiDtmfOffLengthExpired(
    VOS_UINT32                          ulParam
)
{
    MN_CALL_ID_T                        CallId;
    TAF_CALL_DTMF_NODE_STRU            *pstNode         = VOS_NULL_PTR;
    HI_LIST_S                          *pstListHead     = VOS_NULL_PTR;
    TAF_CALL_DTMF_INFO_STRU            *pstDtmfCurInfo  = VOS_NULL_PTR;

    pstDtmfCurInfo  = TAF_CALL_GetDtmfCurInfo();

    MN_CALL_StopTimer(TAF_CALL_TID_DTMF_OFF_LENGTH);

    /* �ж�״̬�Ƿ��쳣 */
    if (TAF_CALL_GetDtmfState() != TAF_CALL_DTMF_WAIT_OFF_LENGTH_TIME_OUT)
    {
        MN_WARN_LOG("TAF_CALL_RcvTiDtmfOffLengthExpired: Dtmf State Error!");
        return;
    }

    /* ������Ϊ�գ������û��漰DTMF״̬���˳� */
    if (0 == TAF_CALL_GetDtmfBufCnt())
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* �л��棬��ΪSTOP_DTMF������ֱ���ͷŴ˻��棬֮����ΪSTART_DTMF�����򷢳� */
    pstListHead = TAF_CALL_GetDtmfListHead();
    /*lint -e961*/
    pstNode     = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
    /*lint -e961*/

    if (0 == pstNode->stDtmf.usOnLength)
    {
        *pstDtmfCurInfo = pstNode->stDtmf;

        /* �ӹ��˱���ɾ���ڵ� */
        TAF_CALL_DelDtmfNode(pstNode);

        /* �ظ�STOP_DTMF����ʽ��Ӧ */
        TAF_CALL_SendDtmfCnf(pstDtmfCurInfo->usClientId,
                             pstDtmfCurInfo->opId,
                             MN_CALL_EVT_STOP_DTMF_RSLT,
                             TAF_CS_CAUSE_SUCCESS);

        /* �������Ϊ�գ���ֱ�����û��漰DTMF״̬���˳� */
        if (TAF_CALL_GetDtmfBufCnt() == 0)
        {
            TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
            return;
        }

        /* ���治Ϊ�գ���ΪSTART_DTMF����׼������ */
        /*lint -e961*/
        pstNode = msp_list_entry(pstListHead->next, TAF_CALL_DTMF_NODE_STRU, stList);
        /*lint +e961*/
    }

    /* ��ȡ������������DTMF��CallId����ȡʧ������ջ�������DTMF״̬���˳� */
    CallId = 0;
    if (TAF_CS_CAUSE_SUCCESS != TAF_CALL_GetAllowedDtmfCallId(&CallId))
    {
        MN_WARN_LOG("TAF_CALL_RcvTiDtmfOffLengthExpired: Dtmf Not Allowed!");
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        return;
    }

    /* �ӻ�����ȡ���ڵ㣬����START_DTMF���� */
    *pstDtmfCurInfo = pstNode->stDtmf;

    /* �ӹ��˱���ɾ���ڵ� */
    TAF_CALL_DelDtmfNode(pstNode);

    if (VOS_OK != MN_CALL_SendCcStartDtmfReq(CallId, pstDtmfCurInfo->cKey))
    {
        TAF_CALL_ResetDtmfCtx(TAF_CS_CAUSE_UNKNOWN);
        MN_ERR_LOG("TAF_CALL_RcvTiDtmfOffLengthExpired: Send Stop Dtmf Failed!");
        return;
    }

    /* ���ͳɹ�������DTMF״̬ */
    TAF_CALL_SetDtmfState(TAF_CALL_DTMF_WAIT_START_CNF);

    return;
}



VOS_UINT32 TAF_CALL_GetTimerLen(
    MN_CALL_TIMER_ID_ENUM_U32           enTimerId
)
{
    return (g_astCallTimerInfoTbl[enTimerId - MN_TIMER_CLASS_CCA].ulTimeout);
}

#if (FEATURE_ON == FEATURE_ECALL)

VOS_VOID TAF_CALL_EcallRedialPeriodTimeout(VOS_UINT32 ulParam)
{
    MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);

    /* ���period��ʱ����ʱ������ʱ��Ϊ0 */
    TAF_CALL_UpdateEcallPeriodRemainTimerLen(0);

    return;
}
VOS_VOID TAF_CALL_EcallRedialIntervalTimeout(VOS_UINT32 ulParam)
{
    MN_CALL_MSG_BUFF_STRU              *pstBufferdMsg = VOS_NULL_PTR;
    MN_CALL_STATE_ENUM_U8               enCallState;
    MN_CALL_MPTY_STATE_ENUM_U8          enMptyState;
    VOS_UINT32                          ulRslt;

    enCallState = MN_CALL_S_BUTT;
    enMptyState = MN_CALL_MPYT_STATE_BUTT;

    pstBufferdMsg  = MN_CALL_GetBufferedMsg();

    MN_CALL_GetCallState(pstBufferdMsg->stBufferedSetupMsg.ucCallId, &enCallState, &enMptyState);

    MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);

    if (MN_CALL_S_DIALING != enCallState)
    {
        MN_CALL_ClearBufferedMsg();
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
        return;
    }

    /* ȡ������Ϣ */
    if (VOS_TRUE == pstBufferdMsg->bitOpBufferedSetupMsg)
    {
        if (VOS_TRUE == TAF_CALL_IsCallTypeEmgencyCall(pstBufferdMsg->stBufferedSetupMsg.ucCallId))
        {
            ulRslt = MN_CALL_SendCcBufferedEmgSetupReq(&pstBufferdMsg->stBufferedSetupMsg);
        }
        else
        {
            ulRslt = MN_CALL_SendCcBufferedSetupReq(&pstBufferdMsg->stBufferedSetupMsg);
        }

        /* ��Ϣ���ͳɹ����أ����������rej ind��Ϣ*/
        if (VOS_TRUE == ulRslt)
        {
            return;
        }
    }

    MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);

    /* Modified by zwx247453 for CHR optimize, 2015-07-07, begin */
    TAF_CALL_ProcBufferedRedialMessage(pstBufferdMsg,
        TAF_CS_CAUSE_MM_INTER_ERR_CS_SERVICE_CONGESTION);
    /* Modified by zwx247453 for CHR optimize, 2015-07-07, end */

    return;
}


VOS_VOID TAF_CALL_RcvT2TimerExpired(
    VOS_UINT32                          ulParam
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

    MN_CALL_StopTimer(TAF_CALL_TID_T2);

    /* T2��ʱ���Ҷϵ�ǰ���� */
    MN_CALL_GetNotIdleStateCalls(&ulNumOfCalls, aCallIds);

    if (0 != ulNumOfCalls)
    {
        for (i = 0; i < ulNumOfCalls; i++)
        {
            MN_CALL_GetCallState(aCallIds[i], &enCallState, &enMptyState);

            if ((VOS_TRUE          == TAF_CALL_IsCallTypeEcall(aCallIds[i]))
             && ((MN_CALL_S_ACTIVE == enCallState)
              || (MN_CALL_S_HELD   == enCallState)))
            {
                /*�Ҷ�ָ���ĺ���*/
                (VOS_VOID)MN_CALL_SendCcDiscReq(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼�����Ҷϵ�ԭ��ֵ */
                MN_CALL_UpdateCcCause(aCallIds[i], MN_CALL_NORMAL_CALL_CLEARING);

                /* ��¼���йҶϵķ��� */
                MN_CALL_UpdateDiscCallDir(aCallIds[i], VOS_TRUE);

                /* ����ز��������ز���ʱ�� */
                TAF_CALL_ClearEcallRedialedBufferAndStopEcallRedialedTimer(aCallIds[i]);
            }
        }
    }
}
VOS_VOID TAF_CALL_RcvT9TimerExpired(
    VOS_UINT32                          ulParam
)
{
    MN_CALL_StopTimer(TAF_CALL_TID_T9);
}
#endif


VOS_VOID TAF_CALL_StopAllRedialTimers(VOS_UINT8 ucCallId)
{
#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        /* ֹͣeCall�ز���ʱ�� */
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);
        MN_CALL_StopTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
    }
    else
#endif
    {
        /* ֹͣcall�ز���ʱ�� */
        MN_CALL_StopTimer(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL);
        MN_CALL_StopTimer(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD);
    }
}

/*lint -save -e958 */

VOS_UINT32 TAF_CALL_GetRedialIntervalTimerLen(VOS_UINT8 ucCallId)
{
    VOS_UINT32                          ulIntervalTimerLen;

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        ulIntervalTimerLen = MN_CALL_GetTimerLen(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);
    }
    else
#endif
    {
        ulIntervalTimerLen = MN_CALL_GetTimerLen(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL);
    }

    return ulIntervalTimerLen;
}
/*lint -restore */

/*lint -save -e958 */

VOS_UINT32 TAF_CALL_GetRemainRedialPeriodTimerLen(VOS_UINT8 ucCallId)
{
    VOS_UINT32                          ulPeriodTimerLen;

    ulPeriodTimerLen = 0;

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD))
        {
            ulPeriodTimerLen = MN_CALL_GetTimerRemainLen(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD);
        }
        else
        {
            ulPeriodTimerLen = TAF_CALL_GetEcallPeriodRemainTimerLen();
        }
    }
    else
#endif
    {
        if (MN_CALL_TIMER_STATUS_RUNING == MN_CALL_GetTimerStatus(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD))
        {
            ulPeriodTimerLen = MN_CALL_GetTimerRemainLen(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD);
        }
    }

    return ulPeriodTimerLen;
}
/*lint -restore */

VOS_VOID TAF_CALL_StartRedialPeriodTimer(VOS_UINT8 ucCallId)
{
#if (FEATURE_ON == FEATURE_ECALL)
    VOS_UINT32                          ulEcallPeriodTimerLen;

    if(VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        ulEcallPeriodTimerLen = TAF_CALL_GetEcallPeriodRemainTimerLen();

        MN_CALL_StartTimer(TAF_CALL_TID_WAIT_ECALL_REDIAL_PERIOD, 0, ulEcallPeriodTimerLen, VOS_RELTIMER_NOLOOP);
    }
    else
#endif
    {
        MN_CALL_StartTimer(MN_CALL_TID_WAIT_CALL_REDIAL_PERIOD, 0, 0, VOS_RELTIMER_NOLOOP);
    }
}


MN_CALL_TIMER_STATUS_ENUM_U8 TAF_CALL_GetRedialIntervalTimerStatus(VOS_UINT8 ucCallId)
{
    MN_CALL_TIMER_STATUS_ENUM_U8        enIntervalTimerStatus;

#if (FEATURE_ON == FEATURE_ECALL)
    if (VOS_TRUE == TAF_CALL_IsCallTypeEcall(ucCallId))
    {
        enIntervalTimerStatus = MN_CALL_GetTimerStatus(TAF_CALL_TID_WAIT_ECALL_REDAIL_INTERVAL);
    }
    else
#endif
    {
        enIntervalTimerStatus = MN_CALL_GetTimerStatus(MN_CALL_TID_WAIT_CALL_REDAIL_INTERVAL);
    }

    return enIntervalTimerStatus;
}

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

