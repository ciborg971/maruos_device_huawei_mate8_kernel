

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

#define     THIS_FILE_ID        PS_FILE_ID_TAF_XPDS_TIMER_MGMT_C

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafXpdsMntn.h"

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID  TAF_XPDS_SndOmTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen,
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus
)
{
    TAF_XPDS_TIMER_INFO_STRU           *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_XPDS_TIMER_INFO_STRU*)PS_MEM_ALLOC(UEPS_PID_XPDS,
                             sizeof(TAF_XPDS_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndOmTimerStatus:ERROR:Alloc Mem Fail.");

        return;
    }

    /* ��ʱ��������Ϣ��ֵ */
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = UEPS_PID_XPDS;
    pstMsg->stMsgHeader.ulReceiverPid   = VOS_PID_TIMER;

    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_XPDS_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->ulLen                       = ulLen;

    /* ��ʱ����Ϣ���� */
    (VOS_VOID)DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(UEPS_PID_XPDS, pstMsg);

    return;
}


VOS_VOID  TAF_XPDS_InitAllTimers(
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        pstXPDSTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstXPDSTimerCtx[i].enTimerId     = TI_TAF_XPDS_TIMER_BUTT;
        pstXPDSTimerCtx[i].enTimerStatus = TAF_XPDS_TIMER_STATUS_STOP;
    }

    return;
}



TAF_XPDS_TIMER_START_RESULT_ENUM_UINT8 TAF_XPDS_StartTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId,
    VOS_UINT32                          ulLen
)
{
    TAF_XPDS_TIMER_CTX_STRU            *pstXpdsTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;

    if ( enTimerId >= TI_TAF_XPDS_TIMER_BUTT)
    {
        return TAF_XPDS_TIMER_START_FAILURE;
    }

    pstXpdsTimerCtx = TAF_XPDS_GetTimerCtxAddr();

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_XPDS_TIMER_STATUS_RUNING == pstXpdsTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstXpdsTimerCtx[i].enTimerId))
        {
            XPDS_WARNING1_LOG("TAF_XPDS_StartTimer:timer is running!", (VOS_INT32)enTimerId);

            return TAF_XPDS_TIMER_START_FAILURE;
        }
    }

    /* ���ҵ�ǰ�б���δ�õĽڵ� */
    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if ( TAF_XPDS_TIMER_STATUS_STOP == pstXpdsTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if (TAF_XPDS_CTX_MAX_TIMER_NUM == i)
    {
        XPDS_WARNING_LOG("TAF_XPDS_StartTimer: 10 timers are running!");

        return TAF_XPDS_TIMER_START_FAILURE;
    }

    /* ��鶨ʱ��ʱ�� */
    if ( 0 == ulLen)
    {
        return TAF_XPDS_TIMER_START_FAILURE;
    }
    else if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }
    else
    {

    }

    /* ������ʱ�� */
    ulRet = VOS_StartRelTimer(&(pstXpdsTimerCtx[i].hTimer),
                              UEPS_PID_XPDS,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              VOS_TIMER_PRECISION_5);

    if ( VOS_OK != ulRet)
    {
        XPDS_WARNING_LOG("TAF_XPDS_StartTimer:VOS_StartRelTimer failed");

        return TAF_XPDS_TIMER_START_FAILURE;
    }

    pstXpdsTimerCtx[i].enTimerId     = enTimerId;
    pstXpdsTimerCtx[i].enTimerStatus = TAF_XPDS_TIMER_STATUS_RUNING;

    /* ��ʱ��״̬�������� */
    TAF_XPDS_SndOmTimerStatus(enTimerId, ulLen, TAF_XPDS_TIMER_STATUS_RUNING);

    return TAF_XPDS_TIMER_START_SUCCEE;
}
VOS_VOID  TAF_XPDS_StopTimer(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx;
    VOS_UINT32                          i;

    pstXPDSTimerCtx   =  TAF_XPDS_GetTimerCtxAddr();

    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if ( ( TAF_XPDS_TIMER_STATUS_RUNING  == pstXPDSTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstXPDSTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= TAF_XPDS_CTX_MAX_TIMER_NUM)
    {
        XPDS_WARNING1_LOG("TAF_XPDS_StopTimer:timer already stopped!", (VOS_INT32)enTimerId);

        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstXPDSTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstXPDSTimerCtx[i].hTimer));
    }

    pstXPDSTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstXPDSTimerCtx[i].enTimerId     = TI_TAF_XPDS_TIMER_BUTT;
    pstXPDSTimerCtx[i].enTimerStatus = TAF_XPDS_TIMER_STATUS_STOP;

    /* ��ʱ��״̬�������� */
    TAF_XPDS_SndOmTimerStatus(enTimerId, 0, TAF_XPDS_TIMER_STATUS_STOP);

    return;
}


TAF_XPDS_TIMER_STATUS_ENUM_UINT8  TAF_XPDS_GetTimerStatus(
    TAF_XPDS_TIMER_ID_ENUM_UINT32       enTimerId
)
{
    TAF_XPDS_TIMER_CTX_STRU            *pstXPDSTimerCtx;
    VOS_UINT32                          i;
    TAF_XPDS_TIMER_STATUS_ENUM_UINT8    enTimerStatus;

    pstXPDSTimerCtx = TAF_XPDS_GetTimerCtxAddr();

    enTimerStatus   = TAF_XPDS_TIMER_STATUS_STOP;

    /* ���Ҹö�ʱ���Ƿ��������� */
    for ( i = 0; i < TAF_XPDS_CTX_MAX_TIMER_NUM; i++)
    {
        if (enTimerId == pstXPDSTimerCtx[i].enTimerId)
        {
            enTimerStatus = pstXPDSTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

