/*******************************************************************************
  Copyright    : 2005-2007, Huawei Tech. Co., Ltd.
  File name    : SsSndTimer.c
  Description  : ����Timer��Ϣ�Ĵ���
  Function List:
      1.  Ss_TimerStart         ����������Timer
      2.  Ss_TimerStop          ֹͣ������Timer
  History:
      1.  ��־�� 2004.03.09   �°�����
      2.  ��  �� 2006.11.07   ���ⵥA32D07063
*******************************************************************************/

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif



/*=>A32D07063*/
#if 0

#include "SsInclude.h"

#define SS_TIMER_START(ulTimerId, TimerName, ulTimerLen) \
VOS_StartRelTimer(&g_SsTimerMng[ulTimerId].SsTimerId,\
                  WUEPS_PID_SS,\
                  ulTimerLen,\
                  TimerName,\
                  ulTimerId,\
                  VOS_RELTIMER_NOLOOP)

#define SS_TIMER_STOP(ulTimerId)  VOS_StopRelTimer(&g_SsTimerMng[ulTimerId].SsTimerId)

/***********************************************************************
*  MODULE   : Ss_TimerStart
*  FUNCTION : ����������Timer
*  INPUT    : VOS_UINT8     ucTi         ��Ӧ��Ti
*  OUTPUT   : VOS_VOID
*  RETURN   : VOS_VOID
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 04-03-09  �°�����
*     2.
************************************************************************/

VOS_VOID Ss_TimerStart(
                   VOS_UINT8 ucTi                                                   /* ��Ӧ��Ti                                 */
                   )
{
                                                 /* ���͵���Ϣ                               */
    VOS_UINT32       ulResult;                                                        /* ���ڽ����������                         */

    if( SS_TIMER_IDLE == g_SsTimerMng[ucTi].ucTimerState )
    {                                                                           /* �ж�ָ��Timer�Ƿ�δ����                  */

        ulResult = SS_TIMER_START(ucTi, SS_T551, SS_T551_LEN * 1000);
        if( VOS_OK != ulResult)
        {
            SS_WARN_LOG( "\n [Error]Timer T551 Start Failure! \r" );
            return;
        }

        g_SsTimerMng[ucTi].ucTimerState = SS_TIMER_RUN;                         /* ����Timer������־                        */


    }
}

/***********************************************************************
*  MODULE   : Ss_TimerStop
*  FUNCTION : ֹͣ������Timer
*  INPUT    : VOS_UINT8     ucTi           ��Ӧ��Ti
*  OUTPUT   : ��
*  RETURN   : ��
*  NOTE     : ��
*  HISTORY  :
*     1.  ��־�� 03-12-10  �°�����
************************************************************************/

VOS_VOID Ss_TimerStop(
                  VOS_UINT8 ucTi                                                    /* ��Ӧ��Ti                                 */
                  )
{
    VOS_UINT32        ulResult;                                                        /* ���ڽ���ֹͣ���                         */

    if( SS_TIMER_RUN == g_SsTimerMng[ucTi].ucTimerState )
    {                                                                           /* ��Timer��������                          */
        SS_TIMER_STOP(ucTi);
        if( VOS_OK != ulResult)
        {
            SS_WARN_LOG( "\n [Error]Timer Stop Failure! \r" );
        }

        SS_NORM_LOG("\n SS TimerStop: T551\r" );

        g_SsTimerMng[ucTi].ucTimerState = SS_TIMER_IDLE;                        /* ����Timer��ֹͣ��־                      */


    }
}

#endif
/*<=A32D07063*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif
