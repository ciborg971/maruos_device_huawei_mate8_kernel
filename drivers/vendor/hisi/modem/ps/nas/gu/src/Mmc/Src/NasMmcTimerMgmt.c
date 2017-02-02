

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "vos.h"
#include "Ps.h"
#include "NasComm.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcCtx.h"
#include "NasMmcSndOm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
  2 ��������
*****************************************************************************/
#define THIS_FILE_ID PS_FILE_ID_NASMMC_TIMERMGMT_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/* ���������޾��ȶ�ʱ����Ϣ��Ĭ��32k */
NAS_TIMER_PRECISION_STRU g_stNasMmcTimerPrcision[]=
{
   {WUEPS_PID_MMC,  TI_NAS_MMC_TIMER_BUTT,       VOS_TIMER_NO_PRECISION},
};

/*lint -save -e958 */

/*****************************************************************************
  6 ��������
*****************************************************************************/

/*****************************************************************************
 �� �� ��  : NAS_MMC_InitAllTimers
 ��������  : ��ʼ�����ж�ʱ����Ӧ��MMC��ʼ����Resetʱ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��5��30��
    ��    ��   : zhoujun 40661
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID  NAS_MMC_InitAllTimers(
    NAS_MMC_TIMER_CTX_STRU              *pstMmcTimerCtx
)
{
    VOS_UINT32                          i;

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
        pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
        pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;
    }
}


VOS_UINT32  NAS_MMC_StartTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId,
    VOS_UINT32                          ulLen
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;
    VOS_UINT32                          ulRet;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;

    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    if (0 == ulLen)
    {
        NAS_INFO_LOG1(WUEPS_PID_MMC,"NAS_MMC_StartTimer:timer len is zero!", (VOS_INT32)enTimerId);
        return VOS_FALSE;
    }

    /* �����������иö�ʱ���Ѿ�������ֱ�ӷ��� */
    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                   == pstMmcTimerCtx[i].enTimerId))
        {
            NAS_INFO_LOG1(WUEPS_PID_MMC, "NAS_MMC_StartTimer:timer is running", enTimerId);

            return VOS_FALSE;
        }
    }

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( NAS_MMC_TIMER_STATUS_STOP == pstMmcTimerCtx[i].enTimerStatus )
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        NAS_WARNING_LOG1(WUEPS_PID_MMC, "NAS_MMC_StartTimer:too many timer", enTimerId);

        return VOS_FALSE;
    }

    if ( ulLen >= VOS_TIMER_MAX_LENGTH )
    {
        ulLen = VOS_TIMER_MAX_LENGTH - 1;
    }

    ulPrecision = NAS_MMC_GetTimerPrecision(enTimerId);

    ulRet = VOS_StartRelTimer(&(pstMmcTimerCtx[i].hTimer),
                              WUEPS_PID_MMC,
                              ulLen,
                              enTimerId,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              ulPrecision);

    if ( VOS_OK != ulRet)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StartTimer:NAS_StartRelTimer failed");

        return VOS_FALSE;
    }

    pstMmcTimerCtx[i].enTimerId     = enTimerId;
    pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_RUNING;


    /* ��ʱ��״̬�������� */
    NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_RUNING, enTimerId, ulLen);


    NAS_TIMER_EventReport((VOS_UINT32)enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_START);

    return VOS_TRUE;

}



VOS_VOID  NAS_MMC_StopTimer(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;


    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMmcTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-10-10, begin */
        NAS_NORMAL_LOG1(WUEPS_PID_MMC, "NAS_MMC_StopTimer:Timer not running", enTimerId);
        /* Modified by z00359541 for CS REG FAIL FORB LA, 2015-10-10, end */

        return;
    }

    /* ֹͣVOS��ʱ��: ����ʱ����ָ���Ѿ�Ϊ�յ�ʱ��, ˵�����Ѿ�ֹͣ���߳�ʱ */
    if (VOS_NULL_PTR != pstMmcTimerCtx[i].hTimer)
    {


        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstMmcTimerCtx[i].hTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }



        (VOS_VOID)VOS_StopRelTimer(&(pstMmcTimerCtx[i].hTimer));
    }

    pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
    pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
    pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;



    if (0!=ulTimerRemainLen)
    {
        NAS_TIMER_EventReport(enTimerId, WUEPS_PID_MMC, NAS_OM_EVENT_TIMER_OPERATION_STOP);
    }


    /* ��ʱ��״̬�������� */
    NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, enTimerId, ulTimerRemainLen * 10);




}
VOS_VOID  NAS_MMC_StopAllTimer( VOS_VOID )
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    VOS_UINT32                          ulTimerRemainLen;

    ulTimerRemainLen = 0;

    pstMmcTimerCtx   =  NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
        {
            if (VOS_OK != VOS_GetRelTmRemainTime(&(pstMmcTimerCtx[i].hTimer), &ulTimerRemainLen ))
            {
                ulTimerRemainLen = 0;
            }

            /* ֹͣVOS��ʱ�� */
            (VOS_VOID)VOS_StopRelTimer(&(pstMmcTimerCtx[i].hTimer));

            NAS_MMC_SndOmMmcTimerStatus(NAS_MMC_TIMER_STATUS_STOP, pstMmcTimerCtx[i].enTimerId, ulTimerRemainLen * 10);

            pstMmcTimerCtx[i].hTimer        = VOS_NULL_PTR;
            pstMmcTimerCtx[i].enTimerId     = TI_NAS_MMC_TIMER_BUTT;
            pstMmcTimerCtx[i].enTimerStatus = NAS_MMC_TIMER_STATUS_STOP;
        }
    }
}
NAS_MMC_TIMER_STATUS_ENUM_U8  NAS_MMC_GetTimerStatus(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
)
{
    NAS_MMC_TIMER_CTX_STRU             *pstMmcTimerCtx;
    VOS_UINT32                          i;

    pstMmcTimerCtx = NAS_MMC_GetTimerAddr();

    for ( i = 0 ; i < NAS_MMC_MAX_TIMER_NUM ; i++ )
    {
        if ( ( NAS_MMC_TIMER_STATUS_RUNING  == pstMmcTimerCtx[i].enTimerStatus )
          && ( enTimerId                    == pstMmcTimerCtx[i].enTimerId))
        {
            break;
        }
    }

    if ( i >= NAS_MMC_MAX_TIMER_NUM)
    {
        return NAS_MMC_TIMER_STATUS_STOP;
    }

    return NAS_MMC_TIMER_STATUS_RUNING;

}


VOS_TIMER_PRECISION_ENUM_UINT32 NAS_MMC_GetTimerPrecision(
    NAS_MMC_TIMER_ID_ENUM_UINT16        enTimerId
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

    VOS_UINT32                          i;
    VOS_TIMER_PRECISION_ENUM_UINT32     ulPrecision;



    /* Ĭ��Ϊ�о���Ҫ�󣬹���32Kʱ���� */
    ulPrecision = VOS_TIMER_PRECISION_5;

    for ( i = 0; i < ( sizeof(g_stNasMmcTimerPrcision)/sizeof(NAS_TIMER_PRECISION_STRU) ); i++)
    {
        if (enTimerId == g_stNasMmcTimerPrcision[i].ulTimerName)
        {
            ulPrecision = g_stNasMmcTimerPrcision[i].ulPrecision;
            break;
        }
    }

    return ulPrecision;
}

/*lint -restore */


#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

