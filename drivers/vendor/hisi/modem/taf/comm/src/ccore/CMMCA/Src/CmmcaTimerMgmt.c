
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "CmmcaTimerMgmt.h"
#include "CmmcaCtx.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_CMMCA_TIMER_MGMT_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

/* �������Ӷ�ʱ���ľ�����Ϣ */
CMMCA_TIMER_PRECISION_STRU              g_stCmmcaTimerPrcision[]=
{
   {WUEPS_PID_CMMCA,  TI_CMMCA_WAIT_IPV6_RA_INFO,       VOS_TIMER_PRECISION_0},
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID  CMMCA_MNTN_TraceTimerOperation(
    VOS_UINT32                            ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32            enTimerId,
    VOS_UINT32                            ulTimerLen,
    CMMCA_TIMER_OPERATION_TYPE_ENUM_UINT8 enTimerAction
)
{
    CMMCA_TIMER_INFO_STRU                 stMsg;

    PS_MEM_SET(&stMsg, 0x00, sizeof(CMMCA_TIMER_INFO_STRU));

    stMsg.ulSenderCpuId   = VOS_LOCAL_CPUID;
    stMsg.ulReceiverCpuId = VOS_LOCAL_CPUID;
    stMsg.ulSenderPid     = ulPid;
    stMsg.ulReceiverPid   = VOS_PID_TIMER;
    stMsg.ulLength        = sizeof(CMMCA_TIMER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stMsg.enTimerId       = enTimerId;
    stMsg.ulTimerLen      = ulTimerLen;
    stMsg.enTimerAction   = enTimerAction;

    DIAG_TraceReport(&stMsg);

    return;
}


VOS_TIMER_PRECISION_ENUM_UINT32 CMMCA_GetTimerPrecision(
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
)
{
   /*��ʱ����Ϊ���֣�26M��ʱ����32K��ʱ����
         26M��ʱ����ϵͳ�����٣��Ƽ�ʹ�ã�����DRX˯��ʱ��ֹͣ���������ܼ�ʱ��׼��
         32K��ʱ����ϵͳ�����󣬲��Ƽ�ʹ�ã�����ʱ׼ȷ��
         ��ѡ���޾���Ҫ��ʱ(VOS_TIMER_NO_PRECISION)������26M��ʱ��
         �����о���Ҫ��ģ�����32K��ʱ����
    */

    VOS_UINT32                          i;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    /* Ĭ��Ϊ�о���Ҫ�󣬹���32Kʱ���� */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for ( i = 0; i < (sizeof(g_stCmmcaTimerPrcision)/sizeof(CMMCA_TIMER_PRECISION_STRU)); i++)
    {
        if (enTimerId == g_stCmmcaTimerPrcision[i].ulTimerName)
        {
            ulPrecision = g_stCmmcaTimerPrcision[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}
VOS_VOID  CMMCA_StartTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    CMMCA_TIMER_CTX_STRU               *pstTiCtx;
    VOS_TIMER_PRECISION_ENUM_UINT32     enTmrPrecision;

    /* ���������� */
    if (0 == ulLen)
    {
        CMMCA_ERROR1_LOG("CMMCA_StartTimer:ulLen is", ulLen);
        return;
    }

    if (ulLen >= VOS_TIMER_MAX_LENGTH)
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    pstTiCtx = CMMCA_GetTiCtx();

    /* ����ö�ʱ���Ѿ�������ֱ�ӷ��� */
    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if ((CMMCA_TIMER_STATUS_RUNNING == pstTiCtx[i].enTimerStatus)
         && (enTimerId               == pstTiCtx[i].enTimerId))
        {
            return;
        }
    }

    /* �ҵ�һ������λ�� */
    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if (CMMCA_TIMER_STATUS_STOP == pstTiCtx[i].enTimerStatus )
        {
            break;
        }
    }

    /* δ�ҵ�����λ�ã��޷�����ö�ʱ����Ϣ��ֱ�ӷ��� */
    if (i >= CMMCA_MAX_TIMER_NUM)
    {
        CMMCA_ERROR1_LOG("CMMCA_StartTimer:i is",i);
        return;
    }

    enTmrPrecision = CMMCA_GetTimerPrecision(enTimerId);

    ulRet = VOS_StartRelTimer(&(pstTiCtx[i].hTimer),
                              ulPid,
                              ulLen,
                              enTimerId,
                              ulParam,
                              VOS_RELTIMER_NOLOOP,
                              enTmrPrecision);

    if (VOS_OK != ulRet)
    {
        CMMCA_ERROR_LOG("CMMCA_StartTimer:timer is fail start!");
        return;
    }

    pstTiCtx[i].enTimerId     = enTimerId;
    pstTiCtx[i].enTimerStatus = CMMCA_TIMER_STATUS_RUNNING;

    /* ����CMMCA_TIMER_INFO_STRU */
    CMMCA_MNTN_TraceTimerOperation(ulPid, enTimerId, ulLen, CMMCA_TIMER_OPERATION_START);

    return;
}
VOS_VOID CMMCA_StopTimer(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
)
{
    VOS_UINT32                          i;
    CMMCA_TIMER_CTX_STRU               *pstTiCtx;

    pstTiCtx = CMMCA_GetTiCtx();

    /* ����ö�ʱ���Ѿ�������ֱ�ӷ��� */
    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if ((CMMCA_TIMER_STATUS_RUNNING == pstTiCtx[i].enTimerStatus)
         && (enTimerId               == pstTiCtx[i].enTimerId))
        {
            break;
        }
    }

    /* δ�ҵ��ö�ʱ�� */
    if ( i >= CMMCA_MAX_TIMER_NUM)
    {
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstTiCtx[i].hTimer)
    {
        VOS_StopRelTimer(&(pstTiCtx[i].hTimer));
    }

    pstTiCtx[i].hTimer        = VOS_NULL_PTR;
    pstTiCtx[i].enTimerId     = TI_CMMCA_TIMER_BUTT;
    pstTiCtx[i].enTimerStatus = CMMCA_TIMER_STATUS_STOP;

    /* ����CMMCA_TIMER_INFO_STRU */
    CMMCA_MNTN_TraceTimerOperation(ulPid, enTimerId, 0, CMMCA_TIMER_OPERATION_STOP);

    return;
}


CMMCA_TIMER_STATUS_ENUM_UINT8 CMMCA_GetTimerStatus(
    VOS_UINT32                          ulPid,
    CMMCA_TIMER_ID_ENUM_UINT32          enTimerId
)
{
    CMMCA_TIMER_CTX_STRU               *pstTiCtx;
    CMMCA_TIMER_STATUS_ENUM_UINT8       enTimerStatus;
    VOS_UINT32                          i;

    pstTiCtx  = CMMCA_GetTiCtx();

    enTimerStatus = CMMCA_TIMER_STATUS_STOP;

    for (i = 0; i < CMMCA_MAX_TIMER_NUM; i++)
    {
        if (enTimerId == pstTiCtx[i].enTimerId)
        {
            enTimerStatus = pstTiCtx[i].enTimerStatus;
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

