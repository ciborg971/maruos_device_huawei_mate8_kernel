

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafApsCtx.h"
#include  "TafApsTimerMgmt.h"
#include  "PsCommonDef.h"
#include  "TafLog.h"
#include  "TafApsMntn.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define THIS_FILE_ID PS_FILE_ID_TAF_APS_TIMERMGMT_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
TAF_APS_TIMER_PRECISION_STRU g_astTafApsTimerPrcisionTab[]=
{
   {TI_TAF_APS_DSFLOW_REPORT,      VOS_TIMER_NO_PRECISION}
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_UINT32  TAF_APS_BuildTmrParaByCtrlHdr(
    VOS_UINT32                          ulModuleId,
    VOS_UINT32                          ulClientId
)
{
    /*
        ����PID��չ��ModuleId����װ��ʱ������ʱ��Ҫͬʱ����Ӱ��
        Լ��: ModuleId�ṹ Bit0~Bit11: ģ��ID  Bit12~Bit15: ���� Bit16~Bit19: CPU ID Bit20~Bit31: ����
        ��: ModuleID: 0x000A0BCD  ->  0x0000ABCD  ->  0xABCD0000
            ClientID: 0x0000abcd
            CtrlHdr : 0xABCDabcd
    */
    return (((((ulModuleId) & 0xF0000) | (((ulModuleId) & 0xFFF) << 4)) << 12) | (ulClientId));
}


VOS_TIMER_PRECISION_ENUM_UINT32 TAF_APS_GetTimerPrecision(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId
)
{
   /*��ʱ����Ϊ���֣�26M��ʱ����32K��ʱ����
         26M��ʱ����ϵͳ�����٣��Ƽ�ʹ�ã�����DRX˯��ʱ��ֹͣ���������ܼ�ʱ��׼��
         32K��ʱ����ϵͳ�����󣬲��Ƽ�ʹ�ã�����ʱ׼ȷ��
         ��ѡ���޾���Ҫ��ʱ(VOS_TIMER_NO_PRECISION)������26M��ʱ��
         �����о���Ҫ��ģ�����32K��ʱ����
     ��ʱ��ѡ������:
       1����IDLE̬�¶�ʱ����Ҫ��ʱ�������Ǿ�ȷ��ʱ�ģ����������쳣������ʱ����
          �Լ���Ƶ�Ҫ����Զ�ʱ�ģ� Э�鶨ʱ���б�����Զ�ʱ�ģ�����˵�������
          ��ʱ����ͨ��GCF������ �����ඨʱ����ʹ��32K��ʱ����
       2������IDLE��ʱ��������Ҫ���Զ�ʱ�ģ��ҵ�26M��ʱ����
       3����IDLE̬�Ķ�ʱ����ʹ��26M��ʱ�� */

    VOS_UINT32                      i;
    VOS_TIMER_PRECISION_ENUM_UINT32 ulPrecision;

    /* Ĭ�Ͼ���Ϊ32K */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for(i=0; i<( sizeof(g_astTafApsTimerPrcisionTab)/sizeof(TAF_APS_TIMER_PRECISION_STRU) ); i++)
    {
        if (enTimerId == g_astTafApsTimerPrcisionTab[i].enTimerId)
        {
            ulPrecision = g_astTafApsTimerPrcisionTab[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}
VOS_VOID  TAF_APS_InitAllTimers(
    TAF_APS_TIMER_CTX_STRU              *pstApsTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
        pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
        pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;
        pstApsTimerCtx[i].aucReserve[0] = 0;
        pstApsTimerCtx[i].aucReserve[1] = 0;
        pstApsTimerCtx[i].aucReserve[2] = 0;

    }
}



VOS_VOID  TAF_APS_StartTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulLen,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;
    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_APS_TIMER_STATUS_RUNING == pstApsTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstApsTimerCtx[i].enTimerId)
          && ( ulPara                      == pstApsTimerCtx[i].ulPara))
        {
            TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_StartTimer:timer is running!", (VOS_INT32)enTimerId, ulPara);
            return;
        }
    }

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_APS_TIMER_STATUS_STOP == pstApsTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if ( i >= TAF_APS_MAX_TIMER_NUM)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_APS_StartTimer:too many timer!", (VOS_INT32)enTimerId, ulPara);
        return;
    }

    /* ��鶨ʱ��ʱ�� */
    if ( 0 == ulLen)
    {
        TAF_WARNING_LOG2(WUEPS_PID_TAF,"TAF_APS_StartTimer:timer len is zero!", (VOS_INT32)enTimerId, ulPara);
        return;
    }
    else if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }
    else
    {

    }
    ulPrecision = TAF_APS_GetTimerPrecision(enTimerId);

    /* ������ʱ�� */
    ulRet = VOS_StartRelTimer(&(pstApsTimerCtx[i].hTimer),
                              WUEPS_PID_TAF,
                              ulLen,
                              enTimerId,
                              ulPara,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);
    if ( VOS_OK != ulRet)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_StartTimer:VOS_StartRelTimer failed");
        return;
    }

    pstApsTimerCtx[i].enTimerId     = enTimerId;
    pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_RUNING;
    pstApsTimerCtx[i].ulPara        = ulPara;

    /* ��ʱ��״̬�������� */
    TAF_APS_TraceTimer(TAF_APS_TIMER_STATUS_RUNING, enTimerId, ulLen, ulPara);

    return;
}


VOS_VOID  TAF_APS_StopTimer(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;

    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_APS_TIMER_STATUS_RUNING  == pstApsTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstApsTimerCtx[i].enTimerId)
          && ( ulPara                       == pstApsTimerCtx[i].ulPara))
        {
            break;
        }
    }

    if ( i >= TAF_APS_MAX_TIMER_NUM)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_StopTimer:timer already stopped!", (VOS_INT32)enTimerId, ulPara);
        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstApsTimerCtx[i].hTimer)
    {
        (VOS_VOID)VOS_StopRelTimer(&(pstApsTimerCtx[i].hTimer));
    }

    pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
    pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
    pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;

    /* ��ʱ��״̬�������� */
    TAF_APS_TraceTimer(TAF_APS_TIMER_STATUS_STOP, enTimerId, 0, ulPara);

}



VOS_VOID  TAF_APS_StopAllTimer( VOS_VOID )
{

    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;

    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( TAF_APS_TIMER_STATUS_RUNING  == pstApsTimerCtx[i].enTimerStatus )
        {
            /* ֹͣVOS��ʱ�� */
            if (VOS_NULL_PTR != pstApsTimerCtx[i].hTimer)
            {
                (VOS_VOID)VOS_StopRelTimer(&(pstApsTimerCtx[i].hTimer));
            }

            pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
            pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
            pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;
        }
    }

    return;
}
VOS_VOID  TAF_APS_StopPdpAllTimer(
    VOS_UINT32                          ulPara
)
{

    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;

    pstApsTimerCtx   =  TAF_APS_GetTimerCtxAddr();

    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( TAF_APS_TIMER_STATUS_RUNING  == pstApsTimerCtx[i].enTimerStatus )
          && ( ulPara  == pstApsTimerCtx[i].ulPara ))
        {
            /* ֹͣVOS��ʱ�� */
            if (VOS_NULL_PTR != pstApsTimerCtx[i].hTimer)
            {
                (VOS_VOID)VOS_StopRelTimer(&(pstApsTimerCtx[i].hTimer));
            }

            pstApsTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstApsTimerCtx[i].enTimerId     = TI_TAF_APS_TIMER_BUTT;
            pstApsTimerCtx[i].enTimerStatus = TAF_APS_TIMER_STATUS_STOP;
            pstApsTimerCtx[i].ulPara        = TAF_APS_INVALID_TIMER_PARA;
        }
    }

    return;
}
TAF_APS_TIMER_STATUS_ENUM_U8  TAF_APS_GetTimerStatus(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          i;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    pstApsTimerCtx = TAF_APS_GetTimerCtxAddr();

    enTimerStatus  = TAF_APS_TIMER_STATUS_STOP;

    /* ���Ҹö�ʱ���Ƿ��������� */
    for ( i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++ )
    {
        if ( ( enTimerId == pstApsTimerCtx[i].enTimerId)
          && ( ulPara    == pstApsTimerCtx[i].ulPara))
        {
            enTimerStatus = pstApsTimerCtx[i].enTimerStatus;
            break;
        }
    }

    return enTimerStatus;
}
VOS_VOID TAF_APS_GetRemainTimerLen(
    TAF_APS_TIMER_ID_ENUM_UINT32        enTimerId,
    VOS_UINT32                          ulPara,
    VOS_UINT32                         *pulRemainTimeLen
)
{
    TAF_APS_TIMER_CTX_STRU             *pstApsTimerCtx;
    VOS_UINT32                          ulRemainTick;
    VOS_UINT32                          i;

    pstApsTimerCtx = TAF_APS_GetTimerCtxAddr();
    ulRemainTick   = 0;

    for (i = 0 ; i < TAF_APS_MAX_TIMER_NUM ; i++)
    {
        if ( (TAF_APS_TIMER_STATUS_RUNING == pstApsTimerCtx[i].enTimerStatus)
          && (enTimerId                   == pstApsTimerCtx[i].enTimerId)
          && (ulPara                      == pstApsTimerCtx[i].ulPara) )
        {
            break;
        }
    }

    if (i >= TAF_APS_MAX_TIMER_NUM)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_GetRemainTimerLen: Timer already stopped!", (VOS_INT32)enTimerId, ulPara);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_NULL_PTR == pstApsTimerCtx[i].hTimer)
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_GetRemainTimerLen: Timer handle is null!", (VOS_INT32)enTimerId, ulPara);
        *pulRemainTimeLen = 0;
        return;
    }

    if (VOS_OK != VOS_GetRelTmRemainTime(&(pstApsTimerCtx[i].hTimer), &ulRemainTick))
    {
        TAF_INFO_LOG2(WUEPS_PID_TAF,"TAF_APS_GetRemainTimerLen: Get remain time fail!", (VOS_INT32)enTimerId, ulPara);
        *pulRemainTimeLen = 0;
        return;
    }

    *pulRemainTimeLen = ulRemainTick * TI_TAF_APS_1_TICK_10_MS;
    return;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
