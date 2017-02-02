

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasTimer.h"
#include "GmmCasSend.h"
#include "GmmCasComm.h"
#include "GmmCasSuspend.h"
#include "GmmMmInterface.h"
#include  "GmmCasGsm.h"

#include "NasComm.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_TIMER_C

extern VOS_UINT32   g_ulGmmDelaySuspendRsp;

/*lint -save -e958 */



/* extern VOS_UINT32 Mmc_IsPlmnSearching(VOS_VOID); */


VOS_VOID Gmm_TimerStart(
                    VOS_UINT8 ucTimerId                                             /* Timer ID                                 */
                    )
{
    VOS_UINT32                          ulResult;                               /* �����������TIMER�������                */

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId,&pulTimerSusMask, &ucTimerBitIndex);
    
    /*lint -e701*/
    if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {                                                                           /* ��timer�Ѿ�����                          */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStart:WARNING: This Timer has been started");
        return;                                                                 /* ����                                     */
    }

    if ((GMM_TIMER_T3302 == ucTimerId) || (GMM_TIMER_T3312 == ucTimerId))
    {                                                                           /* T3302��T3312                             */
        if (0 == g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal)
        {                                                                       /* T3302��T3312ʱ��Ϊ0                      */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "Gmm_TimerStart:NORMAL: Timer Length of T3302 or T3312 is 0");
            return;                                                             /* ����                                     */
        }
    }


    ulResult = Mm_StartRelTimer(      &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,        /* ���TIMER ID�ĵ�ַ                       */
                                       WUEPS_PID_GMM,
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,     /* ʱ��                                     */
                                       (VOS_UINT32)ucTimerId,                             /* ��Ϣ���е�ID                             */
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,        /* ��Ϣ��ַ                                 */
                                       g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                       );
    if (VOS_OK != ulResult)
    {                                                                                         /* ����ʧ��                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_TimerStart:ERROR: Start timer unsuccessfully");
        return;                                                                               /* ����                                     */
    }


    /*lint -e701*/
    (*pulTimerRunMask) |= (0x00000001 << ucTimerBitIndex);                  /* ��Timer��������־                        */

    (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* ��Timer�Ĺ����־                        */
    /*lint +e701*/

    /*add,sunxibo,2006-03-03,itt begin*/
    if (GMM_TIMER_T3314 == ucTimerId)
    {
        /*lint -e701*/
        if ((g_GmmTimerMng.ulTimerRunMask) & (0x00000001 << GMM_TIMER_T3312))   /*T3312��������̬*/
        /*lint +e701*/
        {
#if (FEATURE_LTE == FEATURE_ON)
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
#endif
            Gmm_TimerStop(GMM_TIMER_T3312);
        }

        if (GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
        {
            Gmm_TimerStop(GMM_TIMER_T3311);
        }

        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_READY_TIMER_START,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }
    /*add,sunxibo,2006-03-03,itt end*/

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStart:INFO: StartTimer: ", ucTimerId);

}


VOS_VOID Gmm_TimerStop(
                   VOS_UINT8       ucTimerId                                    /* Timer ID                                 */
                   )
{
    VOS_UINT8    i;                                                             /* ����ѭ������                             */

    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSuspendCtrlRunMask  = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    switch (ucTimerId)
    {                                                                           /* �ж϶�ʱ������                           */
        case GMM_TIMER_ALL:

            for (i = 0; i < GMM_TIMER_NUM; i ++)
            {
                /* �ػ�������ʱ��������ʾͣ����TIMER_ALL��ֹͣ�ö�ʱ�� */
                if ( GMM_TIMER_1S == i )
                {
                    continue;
                }

                NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

                /*lint -e701*/
                if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
                /*lint +e701*/
                {                                                                   /* �ö�ʱ���Ѿ�����                         */
                    if ((GMM_TIMER_T3314 == i)
                     || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                        NAS_EventReport(WUEPS_PID_GMM,
                                        NAS_OM_EVENT_READY_TIMER_STOP,
                                        VOS_NULL_PTR,
                                        NAS_OM_EVENT_NO_PARA);
                    }


                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                        return;                                                     /* ����                                     */
                    }
                    /*lint -e701*/
                    (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);                  /* ��Timer��������־                        */

                    (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* ��Timer�Ĺ����־                        */
                    /*lint +e701*/
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

                }
            }
            gstGmmSuspendCtrl.ulTimerRunMask = 0x0;

            gstGmmSuspendCtrl.ulTimerRunMaskEx              = 0x0; 
                
            break;                                                                  /* ����                                     */
        case GMM_REGSTER_AND_SHUTDOWN_TIMER:
            for (i = 0; i < GMM_TIMER_NUM; i ++)
            {
                /* ��֧��GPRSʱ,����Ҫֹͣ��Щ��ʱ�� */
                if ((GMM_TIMER_1S == i) || (GMM_TIMER_T3302 == i) || (GMM_TIMER_T3311 == i)
                 || (GMM_TIMER_T3312 == i) || (GMM_TIMER_T3314 == i))
                {
                    continue;
                }

                NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
                NAS_GMM_GetTimerSuspendCtrlRunMask(i, &pulTimerSuspendCtrlRunMask, &ucTimerBitIndex);
                
                /*lint -e701*/
                if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
                /*lint +e701*/
                {                                                                   /* �ö�ʱ���Ѿ�����                         */
                    if ((GMM_TIMER_T3314 == i)
                     || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                    {
                        gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;
                        NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                        NAS_EventReport(WUEPS_PID_GMM,
                                        NAS_OM_EVENT_READY_TIMER_STOP,
                                        VOS_NULL_PTR,
                                        NAS_OM_EVENT_NO_PARA);
                    }

                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                    }
                    /*lint -e701*/
                    (*pulTimerRunMask)              &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);          /* ��Timer��������־                        */

                    (*pulTimerSusMask)              &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* ��Timer�Ĺ����־                        */
                    
                    (*pulTimerSuspendCtrlRunMask)   &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);
                    /*lint +e701*/
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

                }
            }
            break;
        case GMM_TIMER_T3312:
            /*lint -e701*/
            if (0 != (g_GmmTimerMng.ulTimerRunMask & (0x00000001 << ucTimerId)))
            /*lint +e701*/
            {                                                                       /* Timer��������                            */
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
                {                                                                   /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop timer unsuccessfully");
                    return;                                                         /* ����                                     */
                }
                /*lint -e701*/
                g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << ucTimerId);         /* ��Timer��������־                        */

                g_GmmTimerMng.ulTimerSusMask &= ~(VOS_UINT32)(0x00000001 << ucTimerId); /* ��Timer�Ĺ����־                        */
                /*lint +e701*/
                PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", ucTimerId);

            }
            break;

        case GMM_TIMER_ALL_EXCEPT_T3312_T3323:

           for (i = 0; i < GMM_TIMER_NUM; i ++)
           {
               if ((GMM_TIMER_1S == i )
                || (GMM_TIMER_T3312 == i)
                || (GMM_TIMER_T3323 == i))
               {
                   continue;
               }

               NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
               NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

               /*lint -e701*/
               if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
               /*lint +e701*/
               {                                                                   /* �ö�ʱ���Ѿ�����                         */
                   if ((GMM_TIMER_T3314 == i)
                    || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
                   {
                       gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                       NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                       NAS_EventReport(WUEPS_PID_GMM,
                                       NAS_OM_EVENT_READY_TIMER_STOP,
                                       VOS_NULL_PTR,
                                       NAS_OM_EVENT_NO_PARA);
                   }


                   if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                       Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                   {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                       PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop all timer unsuccessfully");
                       return;                                                     /* ����                                     */
                   }
                   /*lint -e701*/
                   (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);          /* ��Timer��������־                        */

                   (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);         /* ��Timer�Ĺ����־                        */
                   /*lint +e701*/
                   PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", i);

               }
           }
           gstGmmSuspendCtrl.ulTimerRunMask = 0x0;
           gstGmmSuspendCtrl.ulTimerRunMaskEx              = 0x0;
           
           break;

        default:                                                                    /* �������                                 */
            NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
            
            /*lint -e701*/
            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            /*lint +e701*/
            {                                                                       /* Timer��������                            */
                if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                        Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
                {                                                                   /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerStop:WARNING: Stop timer unsuccessfully");
                    return;                                                         /* ����                                     */
                }
                /*lint -e701*/
                (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);                  /* ��Timer��������־                        */

                (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* ��Timer�Ĺ����־                        */
                /*lint +e701*/
                PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerStop:INFO: StopTimer: ", ucTimerId);
                if (GMM_TIMER_T3314 == ucTimerId)
                {
                    NAS_EventReport(WUEPS_PID_GMM,
                                    NAS_OM_EVENT_READY_TIMER_STOP,
                                    VOS_NULL_PTR,
                                    NAS_OM_EVENT_NO_PARA);
                }

            }
            break;                                                                  /* ����                                     */
    }
    return;                                                                     /* ����                                     */
}


VOS_UINT32 NAS_GMM_IsTimerIdInTimerList(
    VOS_UINT8                           ucTimerId,
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           ucIndex;

    for ( ucIndex = 0 ; ucIndex < ucTimerNum; ucIndex++ )
    {
        if ( ucTimerId == *(pucTimer + ucIndex) )
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_VOID NAS_GMM_TimerStopExceptSpecialTimers(
    VOS_UINT8                           ucTimerNum,
    VOS_UINT8                          *pucTimer
)
{
    VOS_UINT8                           i;
    VOS_UINT8                           ucTotalTimerNum;

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    ucTotalTimerNum = ucTimerNum;

    if (ucTotalTimerNum > GMM_TIMER_NUM)
    {
        ucTotalTimerNum = GMM_TIMER_NUM;
    }

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if ( VOS_TRUE == NAS_GMM_IsTimerIdInTimerList(i, ucTotalTimerNum, pucTimer) )
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);

        /*lint -e701*/
        if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {                                                                   /* �ö�ʱ���Ѿ�����                         */
            if ((GMM_TIMER_T3314 == i)
             || (GMM_AGB_GPRS_READY == gstGmmCasGlobalCtrl.GmmSrvState))
            {
                gstGmmCasGlobalCtrl.GmmSrvState = GMM_AGB_GPRS_STANDBY;

                NAS_GMM_SndGasInfoChangeReq(NAS_GSM_MASK_GSM_GMM_STATE);
                NAS_EventReport(WUEPS_PID_GMM,
                                NAS_OM_EVENT_READY_TIMER_STOP,
                                VOS_NULL_PTR,
                                NAS_OM_EVENT_NO_PARA);
            }


            if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
            {                                                               /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_TimerStopExceptSpecialTimers:WARNING: Stop all timer unsuccessfully");
                return;                                                     /* ����                                     */
            }
            /*lint -e701*/
            (*pulTimerRunMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);             /* ��Timer��������־                        */

            (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);             /* ��Timer�Ĺ����־                        */
            /*lint +e701*/
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_TimerStopExceptSpecialTimers:INFO: StopTimer: ", i);

        }
    }

    gstGmmSuspendCtrl.ulTimerRunMask    = 0x0;
    gstGmmSuspendCtrl.ulTimerRunMaskEx  = 0x0;
}

/***********************************************************************
  Module   : Gmm_TimerPause
  Function : GMMʹ�õĶ�ʱ����ͣ
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2003.12.10  �°�����

  2.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID Gmm_TimerPause(
                    VOS_UINT8                   ucTimerId                           /* Timer ID                                 */
                    )
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {                                                                           /* ��timer�Ѿ�����                          */


        if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                    Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
        {                                                                       /* ��ͣʧ��                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPause:WARNING: Stop timer unsuccessfully");
            return;                                                             /* ����                                     */
        }
        /*lint -e701*/
        (*pulTimerSusMask) |= (0x00000001 << ucTimerBitIndex);              /* ����Timer�Ĺ����־                      */
        /*lint +e701*/
    }
    else
    {                                                                           /* ��timerδ����                            */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPause:WARNING: Timer is not running");
        return;                                                                 /* ����                                     */
    }
}

/***********************************************************************
  Module   : Gmm_TimerResume
  Function : GMMʹ�õ���ͣ��Ķ�ʱ���Ļָ�
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����

  2.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : ��չGMM��ʱ����64��
 ************************************************************************/
VOS_VOID Gmm_TimerResume (
                      VOS_UINT8                   ucTimerId                         /* Timer ID                                 */
                      )
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask     = VOS_NULL_PTR;
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    {                                                                           /* ��timer����                              */
        if (0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex)))
        {                                                                       /* ��Timerδ������                          */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: This timer has been Stoped");
            return;                                                             /* ����                                     */
        }


        if (VOS_OK != Mm_StartRelTimer(   &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_GMM,
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,         /* ʱ��                                     */
                                           (VOS_UINT32)ucTimerId,            /* ��Ϣ���е�ID                             */
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                           g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                           ))
        {                                                                       /* �ָ�ʧ��                                 */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: Start timer unsuccessfully");
            return;                                                             /* ����                                     */
        }

        (*pulTimerSusMask) &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);     /* ��Timer�Ĺ����־                        */
    }
    else
    {                                                                           /* ��timerδ����                            */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResume:WARNING: Timer is not running");
        return;                                                                 /* ����                                     */
    }
    /*lint +e701*/
}
VOS_UINT32  NAS_GMM_QryTimerStatus(VOS_UINT8 ucTimerId)
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
    /*lint +e701*/
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}



VOS_VOID GMM_SuspendTimer(VOS_VOID)
{
    VOS_UINT8 i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    enCurRat = NAS_MML_GetCurrNetRatType();

    gstGmmSuspendCtrl.ulTimerRunMask    = g_GmmTimerMng.ulTimerRunMask;
    gstGmmSuspendCtrl.ulTimerRunMaskEx  = g_GmmTimerMng.ulTimerRunMaskEx;
        

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if ((i == GMM_TIMER_T3312) || (GMM_TIMER_T3314 == i) || (GMM_TIMER_1S == i) || (GMM_TIMER_T3323 == i))
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        
        /*lint -e701*/
        if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {
            /* MMAͨ��SYSCFGEX����detach��attach���̣����detach����������δ��Ӧʱ,
               ��ʱ����һ���µ�LA��RA��Ҫ����LAU/RAUʱ,���ⷴ����GPRS�����ӳ�MMA�ȴ�
               detach�ظ���ʱ��,����MMA��detach��ʱ����attach��GMM��detach��ʱ����ʱ
               ��������detach,��ʱ��ֹͣGMM������detach��ʱ��,��ʱ��ֱ�ӽ��б���detach
            */
            if ((VOS_TRUE                    == g_GmmDetachCtrl.ucSysCfgDetachFlg)
             && (GMM_TIMER_PROTECT_PS_DETACH == i)
             && (NAS_MML_NET_RAT_TYPE_GSM    == enCurRat))
            {
                continue;
            }

            GMM_SuspendSingleTimer(i);
            /*g_GmmTimerMng.ulTimerRunMask &= ~(VOS_UINT32)(0x00000001 << i);*/
        }
    }

}
VOS_VOID GMM_SuspendSingleTimer(VOS_UINT8 ucTimerId)
{
    VOS_UINT32                          ulRet;


    if (VOS_NULL_PTR != g_GmmTimerMng.aTimerInf[ucTimerId].hTimer)
    {
        ulRet = VOS_GetRelTmRemainTime(&(g_GmmTimerMng.aTimerInf[ucTimerId].hTimer),
                                       &gstGmmSuspendCtrl.ulTimerValue[ucTimerId]);
        if (VOS_OK != ulRet)
        {
            gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = MM_EXTRA_DELAY_TIME_LEN;
        }
        else
        {
            gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = gstGmmSuspendCtrl.ulTimerValue[ucTimerId]*MM_TIMER_TICK;
            Gmm_TimerStop(ucTimerId);
        }
    }
    else
    {
        /*  g_GmmTimerMng.aTimerInf[ucTimerId].hTimer Ϊ��ʱ��˵���˶�ʱ���ѳ�ʱ��ֹͣ */
        gstGmmSuspendCtrl.ulTimerValue[ucTimerId] = MM_EXTRA_DELAY_TIME_LEN;
    }


    return;
}
VOS_VOID GMM_ResumeTimer(VOS_UINT8 ucResume)
{
    VOS_UINT8                           i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    VOS_UINT32                         *pulTimerSuspendRunMask      = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;

    enCurRat = NAS_MML_GetCurrNetRatType();

    if (GMM_TIMER_NOT_RESUME == ucResume)
    {
        gstGmmSuspendCtrl.ulTimerRunMask                    = 0x0;

        gstGmmSuspendCtrl.ulTimerRunMaskEx                  = 0x0;
        
        return;
    }

    for (i = 0; i < GMM_TIMER_NUM; i ++)
    {
        if ((GMM_TIMER_T3312 == i) || (GMM_TIMER_T3314 == i) || (GMM_TIMER_SUSPENDED == i))
        {
            continue;
        }

        /* CCO����EST CNF fail���µĻ���,3311ͨ�����ݻ��ƻָ����� */
        if ((gstGmmSuspendCtrl.ucPreRat != NAS_MML_GetCurrNetRatType())
         && (MMC_SUSPEND_CAUSE_CELLCHANGE_FALLBACK == gstGmmSuspendCtrl.ucSuspendCause)
         && (GMM_TIMER_T3311 == i)
         && (GMM_GPRS_SUSPENSION != g_GmmGlobalCtrl.ucState)
         && (GMM_SUSPENDED_WAIT_FOR_SYSINFO != g_GmmGlobalCtrl.ucState))
        {
            continue;
        }

        NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
        NAS_GMM_GetTimerSuspendCtrlRunMask(i, &pulTimerSuspendRunMask, &ucTimerBitIndex);
        
        /*lint -e701*/
        if (0 != ((*pulTimerSuspendRunMask) & (0x00000001 << ucTimerBitIndex)))
        /*lint +e701*/
        {
            /* MMAͨ��SYSCFGEX����detach��attach���̣����detach����������δ��Ӧʱ,
               ��ʱ����һ���µ�LA��RA��Ҫ����LAU/RAUʱ,���ⷴ����GPRS�����ӳ�MMA�ȴ�
               detach�ظ���ʱ��,����MMA��detach��ʱ����attach��GMM��detach��ʱ����ʱ
               ��������detach,��ʱ��ֹͣGMM������detach��ʱ��,��ʱ��ֱ�ӽ��б���detach
            */
            if ((VOS_TRUE                    == g_GmmDetachCtrl.ucSysCfgDetachFlg)
             && (GMM_TIMER_PROTECT_PS_DETACH == i)
             && (NAS_MML_NET_RAT_TYPE_GSM    == enCurRat))
            {
                continue;
            }

            if (VOS_OK != Mm_StartRelTimer(&g_GmmTimerMng.aTimerInf[i].hTimer,
                                            WUEPS_PID_GMM,
                                            gstGmmSuspendCtrl.ulTimerValue[i],
                                            (VOS_UINT32)i,
                                            g_GmmTimerMng.aTimerInf[i].ulParam,
                                            VOS_RELTIMER_NOLOOP))
            {
                GMM_LOG_WARN("Gmm_ResumeTimer:Resume some timer fail.");
            }
            else
            {
                /*lint -e701*/
                (*pulTimerRunMask) |= (0x00000001 << ucTimerBitIndex);
                /*lint +e701*/
            }
        }
    }
    gstGmmSuspendCtrl.ulTimerRunMask = 0x0;
    gstGmmSuspendCtrl.ulTimerRunMaskEx = 0x0;
}

VOS_VOID Gmm_Tim3302Expired(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    /* ��ǰפ����LTE,������ */
    if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
    {
        return;
    }

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �ж�GMM��ǰ״̬                          */
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:

        g_GmmAttachCtrl.ucAttachAttmptCnt = 0;                                  /* attach attempt counter��0                */

        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ���ú�������ATTACH����                   */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

        g_GmmRauCtrl.ucRauAttmptCnt = 0;                                        /* RAU attempt counter ��0                  */

        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);               /* ���ú�������RAU����                      */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:


        /* �����ǰֻ��PS ONLY�� ��������ģʽII,����Ҫ��������ATTACH */
        if ((VOS_TRUE       == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm())
         && (GMM_NET_MODE_II == g_GmmGlobalCtrl.ucNetMod)
         && (GMM_NET_MODE_I  == g_GmmGlobalCtrl.SysInfo.ucNetMod))

        {
            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH); /* ���ú�������RAU����                      */
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);           /* ���ú�������RAU����                      */
        }
        break;                                                                  /* ����                                     */
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3302_EXPIRED);          /* ֪ͨMM����LU                             */
        }
        break;                                                                  /* ����                                     */
    default:                                                                    /* �������                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3302Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* ����                                     */
    }
}


VOS_VOID Gmm_Tim3310Expired(VOS_VOID)
{
    NAS_MSG_STRU                    *pNasMsg = VOS_NULL_PTR ;
    VOS_UINT8                        ucAttachType;

    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪATTACH,��־ΪFINISH */
    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA== enCurRat))
    {
        NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ATTACH, RRMM_GMM_PROC_FLAG_FINISH);

        NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_ATTACH);
        NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* �ж�GMM״̬��GMM_REGISTERED_INITIATED    */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */

        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);
        }

        g_GmmAttachCtrl.ucT3310outCnt++;                                        /* ����T3310���������1                     */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }

        if (g_GmmAttachCtrl.ucT3310outCnt < GMM_TIMER_EXPIRED_MAX_CNT)
        {                                                                       /* �ж�ucT3310OutCnt С�� 5                 */

            /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪATTACH,��־ΪSTART */
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_ATTACH, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_ATTACH);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }

#if (FEATURE_ON == FEATURE_DSDS)

            if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
            {
                NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);
                NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);
            }
#endif

            pNasMsg = Gmm_AttachRequestMsgMake();                               /* ���ú��������տ���Ϣattach request       */

            Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);              /* ʹ��RRMM_DATA_REQԭ�﷢��attach request  */
            Gmm_TimerStart(GMM_TIMER_T3310);                                    /* �˺����ڣ����ж�Timer�Ƿ����С���������
                                                                                 * �У���������                             */


            NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                         GMM_MMC_ACTION_RESULT_FAILURE,
                                         enCause);

            if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
              || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
            {
                ucAttachType = NAS_OM_GMM_GPRS_ATTACH;
            }
            else if (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
            {
                ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;

                NAS_GMM_SndMmCombinedAttachRejected(enCause);

                NAS_GMM_SndMmCombinedRauInitiation();

            }
            else
            {
                ucAttachType = NAS_OM_GMM_COMBINED_GPRS_IMSI_ATTACH;

                NAS_GMM_SndMmCombinedAttachRejected(enCause);

                NAS_GMM_SndMmCombinedRauInitiation();

            }
            NAS_EventReport(WUEPS_PID_GMM,
                            NAS_OM_EVENT_ATTACH_REQ,
                            (VOS_VOID *)&ucAttachType,
                            NAS_OM_EVENT_ATTACH_REQ_LEN);


        }
        else
        {                                                                       /* �ж�ucT3310OutCnt ���� 5                 */
            g_GmmAttachCtrl.ucT3310outCnt = 0;                                  /* ����T3310���������0                     */
            g_GmmAttachCtrl.ucRetryFlg = GMM_FALSE;                             /* ���û�С��������attach��־               */
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_FALSE;                          /* ���followon��־                         */
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_FALSE);

            if (GMM_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
            {                                                                   /* ATTACH��������SM������                   */
                Gmm_SndSmEstablishCnf(GMM_SM_EST_FAILURE, GMM_SM_CAUSE_T3310_EXPIRED);/* ֪ͨSM GMMע��ʧ��                       */
                g_GmmAttachCtrl.ucSmCnfFlg = GMM_FALSE;                         /* ��ucSmCnfFlg��־                         */
            }
            if ((NAS_MML_MS_MODE_CS_ONLY == NAS_MML_GetMsMode())
             && (VOS_FALSE == g_GmmGlobalCtrl.ucUserPsAttachFlag))
            {
                Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
                NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);

                Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);

                if ((GMM_ATTACH_NORMAL_CS_TRANS == g_GmmGlobalCtrl.ucSpecProc)
                    || (GMM_ATTACH_NORMAL       == g_GmmGlobalCtrl.ucSpecProc))
                {
                    NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                                    enCause);
                }
                else
                {
                    NAS_GMM_SndMmCombinedAttachRejected(enCause);
                }


                /* ��MMC����PSע���� */
                NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                             GMM_MMC_ACTION_RESULT_FAILURE,
                                             enCause);

                /* �¼��ϱ� */
                NAS_EventReport(WUEPS_PID_GMM,
                                NAS_OM_EVENT_ATTACH_FAIL,
                                &enCause,
                                NAS_OM_EVENT_ATTACH_FAIL_LEN
                                );

            }
            else
            {
                Gmm_AttachAttemptCounter(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);           /* ���ú�������T3310������                */
            }
            g_GmmGlobalCtrl.ucSpecProc    = GMM_NULL_PROCEDURE;                 /* ������ڽ��е�specific���̱�־           */
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3310Expired:INFO: specific procedure ended");
        }
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_Tim3311Expired(VOS_VOID)
{
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �ж�GMM��ǰ״̬                          */
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        Gmm_AttachInitiate(GMM_NULL_PROCEDURE);                                                   /* ���ú�������ATTACH����                   */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:
    case GMM_REGISTERED_NORMAL_SERVICE:
        if ((GMM_TRUE == g_GmmRauCtrl.ucT3312ExpiredFlg)
         && (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);            /* ���ú�������������RAU����                      */
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);       /* ���ú�������RAU����                      */
        }
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        /*Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);*/           /* ���ú�������RAU����                      */


        /* �����ǰֻ��PS ONLY�� ��������ģʽII,����Ҫ��������ATTACH */
        if ( VOS_TRUE == NAS_GMM_IsAllowedCombinedAttach_GmmRegisteredAttemptingToUpdateMm() )
        {

            Gmm_RoutingAreaUpdateInitiate(GMM_COMBINED_RALAU_WITH_IMSI_ATTACH);
        }
        else
        {
            Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        }

        break;                                                                  /* ����                                     */
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        /* ��¼T3311��ʱ��־����GMM_REGISTERED_NO_CELL_AVAILABLE״̬�յ�ϵͳ��Ϣ֮�󴥷�RAU */
        g_GmmRauCtrl.ucT3311ExpiredFlg = GMM_TRUE;

        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3311_EXPIRED);          /* ֪ͨMM����LU                             */
        }
        break;                                                                  /* ����                                     */
    default:                                                                    /* �������                                 */

        /* ��¼T3311��ʱ��־����GMM_REGISTERED_PLMN_SEARCH״̬�յ�ϵͳ��Ϣ֮�󴥷�RAU */
        g_GmmRauCtrl.ucT3311ExpiredFlg = GMM_TRUE;

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3311Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* ����                                     */
    }
}
VOS_VOID Gmm_Tim3312Expired(VOS_VOID)
{
    VOS_UINT32                  ucOldState;

    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3312Expired:INFO:T3312 Expire.");
    GMM_PrintState();

    ucOldState = g_GmmGlobalCtrl.ucState;
#if (FEATURE_LTE == FEATURE_ON)
     NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_EXP);

     if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     {
         g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;
         if (VOS_TRUE == NAS_GMM_IsNeedStartT3323())
         {
             Gmm_TimerStart(GMM_TIMER_T3323);
         }

        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;

         return;
     }
#endif

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
    case GMM_REGISTERED_NORMAL_SERVICE:
        Gmm_Tim3312Expired_RegNmlServ();                                        /* ����״̬GMM_REGISTERED_NORMAL_SERVICE��  *
                                                                                 * ��T3312�������                          */
        break;                                                                  /* ����                                     */

    case GMM_REGISTERED_LIMITED_SERVICE:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
        Gmm_Tim3312Expired_RegNoCell();                                         /* ����״̬GMM_REGISTERED_NO_CELL_AVAILABLE *
                                                                                 * �µ�T3312�������                        */
        break;
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_REGISTERED_UPDATE_NEEDED:
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;

        if (  (VOS_TRUE == NAS_MML_GetPsRestrictRegisterFlg())
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* ֪ͨMM����LU                             */
        }

#if (FEATURE_LTE == FEATURE_ON)
        /* GMM����ע�ᱻbar״̬��ISR�����Ҫ����T3323��ʱ�� */
        if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
        {
            Gmm_TimerStart(GMM_TIMER_T3323);
        }
#endif
        break;                                                                  /* ����                                     */

    case GMM_REGISTERED_PLMN_SEARCH:
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;

#if (FEATURE_LTE == FEATURE_ON)

        /* GMM����ʱ����GMM_REGISTERED_PLMN_SEARCH��ISR�����Ҫ����T3323��ʱ����
           ���������米���ѵĿ���ָ����״̬ISR������������T3323  */
        if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
         && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
        {
            Gmm_TimerStart(GMM_TIMER_T3323);
        }
#endif
        break;

     default:                                                                    /* �������                                 */
        g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                                                            /* ����                                     */
        break;
    }

    /* ��ǰ��LTE�²���GMM��REG_NORMAL_SERVICE̬,���GS�� */
    if ((NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
     && (GMM_REGISTERED_NORMAL_SERVICE != ucOldState)
     && (GMM_REGISTERED_PLMN_SEARCH    != ucOldState))
    {
        g_MmSubLyrShare.GmmShare.ucGsAssociationFlg = VOS_FALSE;
    }

    return;
}


VOS_VOID Gmm_Tim3312Expired_RegNmlServ(VOS_VOID)
{
    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                  /* ��3312�����־                           */


    /*��ǰG�²�����ѡ��������ʱ������������RAU */
    if ((NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
     && (VOS_FALSE == gstGmmCasGlobalCtrl.ucCellReselFlg))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_PERIODC_UPDATING);
    }
    else
    {
    }


}



VOS_VOID Gmm_Tim3312Expired_RegNoCell(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;

    enTinType = NAS_MML_GetTinType();

    /* GMM����GMM_REGISTERED_NO_CELL_AVAILABLE��GMM_REGISTERED_LIMITED_SERVICE��ISR���
       ��Ҫ����T3323��ʱ�� */
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
    {
        Gmm_TimerStart(GMM_TIMER_T3323);
    }
#endif

    g_GmmRauCtrl.ucT3312ExpiredFlg = GMM_TRUE;                                  /* ���T3312�Ѿ����                        */

    if ((GMM_TRUE == g_GmmGlobalCtrl.SysInfo.ucSysValidFlg)
     && (GMM_FALSE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
    {                                                                           /* ��ǰС����֧��GPRS                       */
        if ((VOS_TRUE == NAS_MML_GetCsAttachAllowFlg())
         && (GMM_NET_MODE_I == g_GmmGlobalCtrl.ucNetMod))
        {                                                                       /* �û�ģʽA������ģʽI                     */
            NAS_GMM_SndMmLuInitiation(GMMMM_T3312_EXPIRED);          /* ֪ͨMM����LU                             */
        }
    }
    else
    {
    }
}
VOS_VOID Gmm_Tim3316Expired(VOS_VOID)
{
    g_GmmAuthenCtrl.ucResStoredFlg  = GMM_FALSE;                                /* ��RES���ڱ�־��ΪFALSE                   */
    g_GmmAuthenCtrl.ucRandStoredFlg = GMM_FALSE;                                /* RAND���ڱ�־�ó�FALSE                    */
}



VOS_VOID Gmm_Tim3317Expired(VOS_VOID)
{
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    enCause = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬��SERVICE_REQUEST_INITIATED  */
        Gmm_TimerStop(GMM_TIMER_T3318);                                         /* ֹͣT3318                                */
        Gmm_TimerStop(GMM_TIMER_T3320);                                         /* ֹͣT3320                                */
        Gmm_ComStaChg(g_GmmGlobalCtrl.ucServPreSta);                            /* ����״̬�Ĺ�������                       */
        if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
                                        == (g_GmmReqCnfMng.ucCnfMask
            & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
        {                                                                       /* �ȴ���Ȩ��Ӧ                             */
            Gmm_TimerStop(GMM_TIMER_PROTECT);                                   /* ͣ������ʱ��                             */
            g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG; /* ���ԭ��ȴ���־                         */
        }
        Gmm_ComCnfHandle();
        if ((GMM_SERVICE_REQUEST_DATA_IDLE
                        == g_GmmGlobalCtrl.ucSpecProc)
                 || (GMM_SERVICE_REQUEST_SIGNALLING
                        == g_GmmGlobalCtrl.ucSpecProc)
                 || (GMM_SERVICE_REQUEST_PAGING_RSP
                        == g_GmmGlobalCtrl.ucSpecProc))
        {                                                                       /* service request������Ϊ��PMM-IDLE�´���
                                                                                 * data,signalling,paging response����֮һ  */
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);                               /* �ͷ�����                                 */
        }
        else
        {
        }

        if (GMM_TIMER_T3311_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3311_FLG))
        {                                                                       /* ���ڱ������T3311                        */
            Gmm_TimerResume(GMM_TIMER_T3311);                                   /* �ָ�T3311                                */
        }
        else if (GMM_TIMER_T3302_FLG
            == (g_GmmTimerMng.ulTimerSusMask & GMM_TIMER_T3302_FLG))
        {                                                                       /* ���ڱ������T3302                        */
            Gmm_TimerResume(GMM_TIMER_T3302);                                   /* �ָ�T3302                                */
        }
        else
        {
        }

        if (VOS_TRUE== NAS_MML_GetDailRejectCfg())
        {
            GMM_SndSmServiceRej(GMM_SM_CAUSE_T3317_EXPIRED);

            g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
        }

        NAS_GMM_SndMmGmmActionResultInd(GMMMM_ACTION_FAILURE,
                                        enCause);                                     /* ����MMCGMM_GMM_ACTION_RESULT_IND()       */


        /* ��MMC����service request��� */
        NAS_GMM_SndMmcServiceRequestResultInd(GMM_MMC_ACTION_RESULT_FAILURE,
                                              enCause);
        /* �¼��ϱ� */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DATA_SERVICE_REJ,
                        (VOS_VOID*)&enCause,
                        NAS_OM_EVENT_SERVICE_REJ_LEN);

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;                        /* �����ǰ����                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Tim3317Expired:INFO: specific procedure ended");
    }
}
VOS_VOID Gmm_Tim3318Expired(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8             enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    /* Authentication attempt counter��0 */
    /* ��ǰС����barred */
    /* ��ǰ��RAT��W��������ֹ��ǰ������;��ǰ��RAT��G��������Ȩʧ��3������ֹ��ǰ������ */
    if (((g_GmmAuthenCtrl.ucAuthenAttmptCnt >= GMM_AUTHEN_ATTEMPT_MAX_CNT)
     && (NAS_MML_NET_RAT_TYPE_GSM == enCurRat))
     || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat))
    {
        g_GmmAuthenCtrl.ucAuthenAttmptCnt = 0;
        g_GmmAuthenCtrl.ucLastFailCause = GMM_AUTHEN_REJ_CAUSE_INVALID;

        /* ��ǰС����barred)                        */
        NAS_GMM_SndGasGprsAuthFailNotifyReq();

        Gmm_SndRrmmRelReq(RRC_CELL_BARRED);
    }

    /* ���ڱ�ֹͣ��retransmission timer�������� */
    Gmm_Start_StopedRetransmissionTimer();
}

VOS_VOID Gmm_Tim3319Expired(VOS_VOID)
{
    VOS_VOID                            *pMsg;
    GMMRABM_REESTABLISH_REQ_STRU        *pRabmReEst;

    if (GMM_MSG_HOLD_FOR_SERVICE ==
        (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
    {                                                                           /* ����б�����SRԭ��                       */
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SERVICE;      /* ��������־                             */

        pMsg = (VOS_VOID *)g_GmmGlobalCtrl.MsgHold.ulMsgAddrForService;

        /*����ַ���Ϣ*/
        pRabmReEst = (GMMRABM_REESTABLISH_REQ_STRU *)Gmm_MemMalloc(sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        if (VOS_NULL_PTR == pRabmReEst)
        {
            Gmm_MemFree(pMsg);
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR,
                "Gmm_DealWithBuffAfterProc:ERROR: Gmm_MemMalloc fail !! ");
            return;
        }

        Gmm_MemCpy(pRabmReEst, pMsg, sizeof(GMMRABM_REESTABLISH_REQ_STRU));

        /*�ͷű����RAMB��Ϣ*/
        Gmm_MemFree(pMsg);

        /*�ַ������Service��Ϣ*/
        Gmm_MsgDistribute((VOS_VOID *)(pRabmReEst));

        /*�ͷ���������ڴ�*/
        Gmm_MemFree(pRabmReEst);
    }
}
/***********************************************************************
  Module   : Gmm_Tim3320Expired
  Function : ��ʱ��T3320�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
 ************************************************************************/
VOS_VOID Gmm_Tim3320Expired(VOS_VOID)
{
    Gmm_Tim3318Expired();
}

/***********************************************************************
  Module   : Gmm_Tim3321Expired
  Function : ��ʱ��T3321�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2003.12.10  �°�����
 ************************************************************************/
VOS_VOID Gmm_Tim3321Expired(VOS_VOID)
{
    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
    case GMM_DEREGISTERED_INITIATED:
        Gmm_Tim3321Expired_DeregInit ();                                        /* ����T3321��״̬GMM_DEREGISTERED_INITIATE
                                                                                 * D�µ��������                            */
        break;                                                                  /* ����                                     */
    case GMM_REGISTERED_IMSI_DETACH_INITIATED:
        Gmm_Tim3321Expired_RegImsiDtchInit ();                                  /* ����T3321��״̬GMM_REGISTERED_IMSI_DETAC *
                                                                                 * H_INITIATED�µ��������                  */
        break;                                                                  /* ����                                     */
    default:                                                                    /* �������                                 */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Tim3321Expired:WARNING: g_GmmGlobalCtrl.ucState is Abnormal");
        break;                                                                  /* ����                                     */
    }
}
VOS_VOID NAS_GMM_TimerProtectPsDetachExpired(VOS_VOID)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulGmmState;

    ulGmmState = g_GmmGlobalCtrl.ucState;

    /* ɾ�������PS��DETACHԭ�� */
    ulRslt = NAS_GMM_DeleteSavedDetachMsg(GMM_WAIT_PS_DETACH);

    if ( VOS_TRUE == ulRslt )
    {
        /* ֪ͨMMC/MM��ǰdetach��� */
        g_GmmGlobalCtrl.stDetachInfo.enDetachType = GMM_WAIT_PS_DETACH;

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        NAS_GMM_SndMmcMmDetachInfo();
    }

    switch ( ulGmmState )
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:
        case GMM_GPRS_SUSPENSION:
        case GMM_SUSPENDED_GPRS_SUSPENSION:
        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:

            /* ����״̬���б���detach��������ϣ�ֱ�ӷ��� */
            NAS_GMM_LocalDetach_GprsSuspension();
            return;

        case GMM_DEREGISTERED_INITIATED:

            /* GMM_DEREGISTERED_INITIATED״̬���б���detach��������ϣ�ֱ�ӷ��� */
            NAS_GMM_LocalDetach_GmmDeregisteredInitiated();
            return;

        case GMM_ROUTING_AREA_UPDATING_INITIATED:

            /* GMM_ROUTING_AREA_UPDATING_INITIATED״̬���б���detach��������ϣ�ֱ�ӷ��� */
            NAS_GMM_LocalDetach_GmmRauInitiated();
            return;

        case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
        case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

            /* GMM-REGISTERED.ATTEMPTING-TO-UPDATE״̬���б���detach��������ϣ�ֱ�ӷ���  */
            NAS_GMM_LocalDetach_GmmDeregisteredAttemptingToAttach();
            return;

        case GMM_REGISTERED_NO_CELL_AVAILABLE :
            Gmm_ComStaChg(GMM_DEREGISTERED_NO_CELL_AVAILABLE);
            break;

        case GMM_REGISTERED_PLMN_SEARCH :
            Gmm_ComStaChg(GMM_DEREGISTERED_PLMN_SEARCH);
            break;

        case GMM_REGISTERED_LIMITED_SERVICE :
            Gmm_ComStaChg(GMM_DEREGISTERED_LIMITED_SERVICE);
            break;

        case GMM_REGISTERED_UPDATE_NEEDED :
            Gmm_ComStaChg(GMM_DEREGISTERED_ATTACH_NEEDED);
            break;

        /* ����״̬������Ǩ�� */
        case GMM_DEREGISTERED_NO_IMSI :
        case GMM_DEREGISTERED_PLMN_SEARCH :
        case GMM_DEREGISTERED_LIMITED_SERVICE :
        case GMM_DEREGISTERED_NO_CELL_AVAILABLE :
        case GMM_NULL :
        case GMM_DEREGISTERED_ATTACH_NEEDED :

            break;

        /* �����Ƿ񶼿���Ǩ�Ƶ�GMM_DEREGISTERED_NORMAL_SERVICE */
        default:
            Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);
            break;
    }

    /* GMM���б���PS��DETACH */
    NAS_GMM_GprsLocalDetach();

    return;
}


VOS_VOID NAS_Gmm_RcvMmT3211ExpiredNotify(
    VOS_VOID                           *pstMsg
)
{
    VOS_UINT8                                               ucPsAttachAllowFlg;
    NAS_MML_CONN_STATUS_INFO_STRU                          *pstConnStatus = VOS_NULL_PTR;
    MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU                  *pstT3211ExpiredNotify = VOS_NULL_PTR;
    VOS_UINT8                                               ucSimPsRegStatus;

    pstConnStatus         = NAS_MML_GetConnStatus();
    pstT3211ExpiredNotify = (MMGMM_T3211_TIMER_EXPIRED_NOTIFY_STRU *)pstMsg;
    ucSimPsRegStatus      = NAS_MML_GetSimPsRegStatus();

    if (VOS_FALSE == NAS_MML_IsPlmnSupportDam(NAS_MML_GetCurrCampPlmnId()))
    {
        /* ��ǰפ�����粻��֧��DAM���������б��У������� */
        return;
    }

    /* ���mm����T3211��ʱ��ʱlau����ԭ��ֵ��Ϊ#17�򲻴���GSM-BTR-1-0644��
       GSM-BTR-1-0650��GSM-BTR-1-0652��GSM-BTR-1-0656������������lau��#17�ܾ� */
    if (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE != pstT3211ExpiredNotify->ucRejectCause)
    {
        return;
    }

    /* GAS��PS���Է���ע��GMM�Ż������Ϣ�������յ�GAS��gprs resume ind��Ϣ
       ��cs�������Ӳ�����Ϣʱ�������T3211��ʱ����ʱ��Ϣ
       �����register normal service״̬Ҳ�败��rau��*/

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        ucPsAttachAllowFlg = NAS_MML_GetPsAttachAllowFlg();

        /* PS���Է���ע��ʱ����Ҫ�����յ�T3211��ʱ����ʱ��ʶ */
        if ((VOS_FALSE == NAS_MML_GetPsRestrictRegisterFlg())
         && (VOS_TRUE  == ucPsAttachAllowFlg)
         && (VOS_TRUE == ucSimPsRegStatus))
        {
            if (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg)
            {
                /* RR���Ӳ����ڱ�ʾCS���ڽ�������,��Ҫ�����յ�T3211��ʱ����ʱ��ʶ*/
                if (VOS_FALSE == pstConnStatus->ucRrcStatusFlg)
                {
                    NAS_GMM_SetMmT3211ExpiredDelayRauFlag(VOS_TRUE);
                }
                return;
            }
        }
        return;
    }

    /* AT&T GSM-BTR-1-0644��GSM-BTR-1-0650��GSM-BTR-1-0652��GSM-BTR-1-0656��������
      Ҫ��MM��attempting to update״̬��T3211��ʱ����ʱ��MM��lau��ͬʱ��
      ֪ͨGMM T3211��ʱ����ʱ��W��GMM��register normal service״̬Ҳ�败��rau*/
    if (GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    /* ���gmm��GMM_SERVICE_REQUEST_INITIATED״̬����rabm�ؽ���pdp��������У�����*/
    if (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        NAS_GMM_SetMmT3211ExpiredDelayRauFlag(VOS_TRUE);
    }

    return;
}
VOS_VOID NAS_Gmm_RcvMmCsLocalDetachInd(
    VOS_VOID                           *pstMsg
)
{
    /* ɾ�������CS��DETACH */
    (VOS_VOID)NAS_GMM_DeleteSavedDetachMsg(GMM_WAIT_CS_DETACH);

    switch (g_GmmGlobalCtrl.ucState)
    {                                                                           /* ����״̬�ַ�                             */
        case GMM_REGISTERED_IMSI_DETACH_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RegImsiDtchInit();
            break;

        case GMM_REGISTERED_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RegInit();
            break;

        case GMM_ROUTING_AREA_UPDATING_INITIATED:
            NAS_Gmm_RcvMmCsLocalDetachInd_RauInit();
            break;

        default:
            break;
    }

    /* ����ģʽI��,CS DETACH��־����,��ɾ����־ */
    if (GMM_WAIT_CS_DETACH ==
        (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH) )
    {
        g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
    }

    return;
}
VOS_VOID Gmm_Tim3321Expired_DeregInit(VOS_VOID)
{
    NAS_MSG_STRU         *pNasMsg = VOS_NULL_PTR ;                              /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }
    g_GmmDetachCtrl.ucT3321OutCnt ++;                                           /* T3321���������1                         */
    if (g_GmmDetachCtrl.ucT3321OutCnt < GMM_TIMER_EXPIRED_MAX_CNT)
    {                                                                           /* �ж���������Ƿ�С��5                    */

#if (FEATURE_ON == FEATURE_DSDS)
        /* ��DSDSʱ��GSM��ATTACH/RAU/DETACHʧ��ʱ�������Ѿ��ͷ�����Դ����Ҫ�������룬������ģһֱ��ȡ������Դ */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }
#endif

        pNasMsg = Gmm_DetachRequestMsgMake();                                   /* ����detach request��Ϣ��������           */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                  /* ����DETACH REQUEST��Ϣ                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {
        Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                         /* ����״̬�Ĺ�������                       */
        /* BEGIN: Added by liurui id:40632, 2006/4/17   PN:A32D03132 */

        if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
        {
            NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);     /* ��PS���attach��ֹ��־                   */
        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
        /* END:   Added by liurui id:40632, 2006/4/17   PN:A32D03132 */

        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321���������0                         */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
        else
        {
            /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
            NAS_GMM_SndMmGprsDetachComplete();
        }



        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

        /* BEGIN: Added by liurui id:40632, 2006/4/17   PN:A32D03132 */
        if (GMM_TRUE == GMM_IsCasGsmMode())
        {
            Gmm_ClearLlcData(LL_GMM_CLEAR_DATA_TYPE_ALL);
        }
        /* END:   Added by liurui id:40632, 2006/4/17   PN:A32D03132 */

    }
    return;                                                                     /* ����                                     */
}

/***********************************************************************
  Module   : Gmm_Tim3321Expired_RegImsiDtchInit
  Function : ��ʱ��T3321�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��    2003.12.10  �°�����

************************************************************************/
VOS_VOID Gmm_Tim3321Expired_RegImsiDtchInit(VOS_VOID)
{
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR ;                               /* ����ָ��                                 */

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }
    g_GmmDetachCtrl.ucT3321OutCnt++;                                            /* T3321���������1                         */
    if (GMM_TIMER_EXPIRED_MAX_CNT > g_GmmDetachCtrl.ucT3321OutCnt)
    {                                                                           /* �ж��������С��5                        */


#if (FEATURE_ON == FEATURE_DSDS)
        /* ��DSDSʱ��GSM��ATTACH/RAU/DETACHʧ��ʱ�������Ѿ��ͷ�����Դ����Ҫ�������룬������ģһֱ��ȡ������Դ */
        if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }
#endif

        pNasMsg = Gmm_DetachRequestMsgMake();                                   /* ����detach request��Ϣ��������           */

        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pNasMsg);                  /* ����DETACH REQUEST��Ϣ                   */
        Gmm_TimerStart(GMM_TIMER_T3321);                                        /* ��T3321                                  */
    }
    else
    {                                                                           /* �ж������������5                        */
        Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);                           /* ����״̬�Ĺ�������                       */
        g_GmmDetachCtrl.ucT3321OutCnt = 0;                                      /* T3321���������0                         */

        if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
            & GMM_UEID_P_TMSI_SIGNATURE))
        {                                                                       /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
            g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask
                &= ~GMM_UEID_P_TMSI_SIGNATURE;                                  /* ���P_TMSI_SIGNATURE                     */

            NAS_MML_InitUeIdPtmsiSignatureInvalid();

            /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
            if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
            }
            else
            {
                Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
            }
            /* Modified by h00313353 for iteration 9, 2015-2-4, end */
        }

        /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
        if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
        {
            NAS_GMM_SndMmcMmDetachInfo();
        }
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_Tim3330Expired(VOS_VOID)
{
    VOS_UINT8            ucUpdateType = GMM_RA_UPDATING;                         /* ������ʱ���������������                 */
    NAS_MSG_STRU        *pNasMsg = VOS_NULL_PTR ;                                /* ����ֲ�����                             */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause;
    VOS_UINT8                           ucCsRestrictionFlg;
    VOS_UINT8                           ucPsRestrictionFlg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat = NAS_MML_GetCurrNetRatType();

    ucCsRestrictionFlg  = NAS_MML_GetCsRestrictRegisterFlg();
    ucPsRestrictionFlg  = NAS_MML_GetPsRestrictRegisterFlg();

    enCause  = NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT;

    if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
      || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        if (GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {
            /* ��GAS����GRRGMM_GPRS_PROC_IND,����ΪPERIODIC RAU,��־ΪFINISH */;
            NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_PERIOD_RAU, RRMM_GMM_PROC_FLAG_FINISH);

            NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_PERIOD_RAU);
            NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
        }
        else
        {
            /* ��GAS����GRRGMM_GPRS_PROC_IND,����ΪNORMAL RAU,��־ΪFINISH */;
            NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_NORMAL_RAU, RRMM_GMM_PROC_FLAG_FINISH);

            NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_NORMAL_RAU);
            NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_FINISH);
        }
    }

    if (GMM_RAU_FOR_WAITSERVICE == gstGmmSuspendCtrl.ucRauCause)
    {
        /* �˱�־��¼����ϵͳ����ѡ�����л�ʱ,RAI��ͬʱ,����������������ʱ��Ҫ����RAU.
           ��Ϊ���ô˺���ʱRAU�Ѿ����,������Ҫ����˱�־ */
        gstGmmSuspendCtrl.ucRauCause = GMM_RAU_FOR_NORMAL;
    }

    if (GMM_REGISTERED_UPDATE_NEEDED == g_GmmGlobalCtrl.ucState)
    {
        if (  (VOS_TRUE == ucPsRestrictionFlg)
            &&(VOS_FALSE == ucCsRestrictionFlg)
            &&(VOS_TRUE == g_MmSubLyrShare.GmmShare.ucGsAssociationFlg))
        {
            NAS_GMM_SndMmLuInitiation(GMMMM_T3330_EXPIRED);          /* ֪ͨMM����LU                             */
            Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
            Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */
            return;
        }
    }

    if (GMM_ROUTING_AREA_UPDATING_INITIATED != g_GmmGlobalCtrl.ucState)
    {                                                                           /* �жϵ�ǰ״̬                             */
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "g_GmmGlobalCtrl.ucState:WARNING: g_GmmGlobalCtrl.ucState is not GMM_ROUTING_AREA_UPDATING_INITIATED");
        return;                                                                 /* ����                                     */
    }

    Gmm_TimerStop(GMM_TIMER_T3318);                                             /* ֹͣT3318                                */
    Gmm_TimerStop(GMM_TIMER_T3320);                                             /* ֹͣT3320                                */

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        Gmm_SndLlcAbortReq(LL_GMM_CLEAR_DATA_TYPE_SIGNALLING);
    }

    /* �����ǰ�л���Ķ������󣬻ظ�ʧ��ָʾ��*/
    if (GMM_TRUE == g_GmmServiceCtrl.ucSmsFlg)
    {
        Gmm_SndSmsErrorInd(GMM_SMS_SIGN_NO_EXIST);                              /* ����PMMSMS_ERROR_IND                     */
        g_GmmServiceCtrl.ucSmsFlg = GMM_FALSE;
    }

    if (GMM_MSG_HOLD_FOR_SMS
        ==(g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SMS))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_SMS;
        g_GmmGlobalCtrl.MsgHold.ulMsgAddrForSMS = (VOS_UINT32)NULL;
    }

    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
        == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {                                                                           /* �ȴ���Ȩ��Ӧ                             */
        Gmm_TimerStop(GMM_TIMER_PROTECT);                                       /* ͣ������ʱ��                             */
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;     /* ���ԭ��ȴ���־                         */
    }


    g_GmmRauCtrl.ucT3330outCnt ++;                                              /* T3330�������+1                          */
    if (GMM_TIMER_EXPIRED_MAX_CNT > g_GmmRauCtrl.ucT3330outCnt)
    {                                                                           /* �жϴ���                                 */
        if (GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
        {                                                                       /* ��ǰRAU�Ƿ�������RAU��־                 */
            ucUpdateType = GMM_PERIODC_UPDATING;                                /* RAU������RAU                             */

            /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪPERIODIC RAU,��־ΪSTART */;
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_PERIOD_RAU, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_PERIOD_RAU);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }

        }
        else
        {
        #if (FEATURE_ON == FEATURE_LTE)

            /* ����CSFBҵ��ʱ������RAU */
            if ( VOS_TRUE == NAS_MML_GetCsSigConnStatusFlg() )
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
            }
        #endif

            if (VOS_FALSE == NAS_MML_GetCsAttachAllowFlg())
            {
                g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;
                g_GmmGlobalCtrl.CsInfo.ucCsTransFlg = GMM_FALSE;                         /* ��CSͨ����Ϊ��                           */
            }

            if ((GMM_RAU_NORMAL != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_NORMAL_CS_TRANS != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_WITH_IMSI_ATTACH != g_GmmGlobalCtrl.ucSpecProc)
             && (GMM_RAU_COMBINED != g_GmmGlobalCtrl.ucSpecProc))
            {

                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "g_GmmGlobalCtrl:WARNING: g_GmmGlobalCtrl.ucSpecProc is Abnormal");
                return;                                                         /* ����                                     */
            }

            ucUpdateType = NAS_GMM_GetRoutingAreaUpdateType();

            g_GmmGlobalCtrl.MsgHold.ucHandleRauFlg  = GMM_FALSE;                        /* �����־                                 */
            g_GmmGlobalCtrl.MsgHold.ucInitiateLuFlg = GMM_FALSE;                        /* �����־                                 */


            /* �����ǰ���뼼����G����GAS����GRRGMM_GPRS_PROC_IND,����ΪNORMAL RAU,��־ΪSTART */;
            if ( (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
              || (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
            {
                NAS_GMM_SndRrmmGmmProcNotify(RRMM_GMM_PROC_TYPE_NORMAL_RAU, RRMM_GMM_PROC_FLAG_START);

                NAS_MML_SetGmmProcType(NAS_MML_GMM_PROC_TYPE_NORMAL_RAU);
                NAS_MML_SetGmmProcFlag(NAS_MML_GMM_PROC_FLAG_START);
            }

        }

        /* ���� Rau ʱ���ж��Ƿ����ϲ�ҵ������У������� Follow-On ��־ */
        if ((GMM_MSG_HOLD_FOR_SERVICE
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SERVICE))
            ||(GMM_MSG_HOLD_FOR_SM
            == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_SM)))
        {
            g_GmmGlobalCtrl.ucFollowOnFlg = GMM_TRUE;
            NAS_MML_SetPsServiceBufferStatusFlg(VOS_TRUE);
        }

#if (FEATURE_ON == FEATURE_DSDS)

        if (NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
        {
            NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);
        }
#endif

        pNasMsg = Gmm_RoutingAreaUpdateRequestMsgMake(ucUpdateType);            /* ��Ϣ����                                 */
           /* send DATA Req to delete the saved data */
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH , pNasMsg);             /* ����RAU REQUEST��Ϣ                      */
        Gmm_TimerStart(GMM_TIMER_T3330);                                    /* ����T3330                                */
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_RAU_REQ,
                        (VOS_VOID *)&ucUpdateType,
                        NAS_OM_EVENT_RAU_REQ_LEN);

        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);

        if ((GMM_COMBINED_RALA_UPDATING == ucUpdateType)
         || (GMM_COMBINED_RALAU_WITH_IMSI_ATTACH == ucUpdateType))
        {
            NAS_GMM_SndMmCombinedRauRejected(enCause);

            NAS_GMM_SndMmCombinedRauInitiation();
        }
    }
    else
    {
        if (GMM_RAU_FOR_NORMAL != gstGmmSuspendCtrl.ucRauCause)
        {
            GMM_RauFailureInterSys();
        }
        else
        {
            GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_NORMAL, GMM_RABM_RAU_FAILURE);
        }

        g_GmmRauCtrl.ucT3330outCnt = 0;                                         /* T3330���������0                         */
        g_GmmRauCtrl.ucRetryFlg = GMM_FALSE;                                    /* ���û�С��������RAU��־                  */
        Gmm_RoutingAreaUpdateAttemptCounter(NAS_MML_REG_FAIL_CAUSE_TIMER_TIMEOUT);        /* ����RAU attempt counter�Ĺ�������        */
    }
    return;                                                                     /* ����                                     */
}

/***********************************************************************
  Module   : NAS_GMM_Timer3340Expired
  Function : ��ʱ��T3340�������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ŷ����    2010.01.03  �����¶�ʱ��T3340
 ************************************************************************/
VOS_VOID NAS_GMM_Timer3340Expired(VOS_VOID)
{
    if ((GMM_FALSE == GMM_IsCasGsmMode()) && (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg))
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;                                                                     /* ����                                     */
}
VOS_VOID NAS_GMM_TimerDetachForPowerOffExpired(VOS_VOID)
{
    /* �ػ�������ʱ����ʱ��ǿ�ƹػ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        /* W�������������ڣ��ͷ���· */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        }

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ���P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
    }

    /* ��MMC�������Ӧ��ģ��ظ���Ϣ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* ���ȫ�ֱ��� */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();
    Gmm_ComVariantInit();
    GMM_BufferMsgDump();
    return;
}



VOS_VOID Gmm_Tim5sExpired(VOS_VOID)
{
    NAS_MSG_STRU           *pNasMsg;                                            /* ����ָ�� */
    VOS_UINT8               ucPsRestrictionFlg;

    ucPsRestrictionFlg      = NAS_MML_GetPsRestrictRegisterFlg();

    if (g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt < GMM_MAX_DETACH_CNT_WHEN_POWER_OFF)
    {
        ++ g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt;

        Gmm_TimerStart(GMM_TIMER_1S);

        /* ���������������GPRS��֧�֣����ٳ��� */
        if (  (RRC_EST_OTHER_ACCESS_BARRED == g_GmmGlobalCtrl.stPowerOffCtrl.ulEstResult)
           || (GMM_NOT_SUPPORT_GPRS == g_GmmGlobalCtrl.SysInfo.ucNotSupportGprs)
           || (VOS_TRUE == ucPsRestrictionFlg))
        {
            g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = GMM_MAX_DETACH_CNT_WHEN_POWER_OFF;
            return;
        }

        /* GMM����̬��ֱ�ӷ��� */
        if ( (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
          || (GMM_SUSPENDED_GPRS_SUSPENSION  == g_GmmGlobalCtrl.ucState))
        {
            return;
        }

        /* RRC ���ӽ��������С����� */
        if (GMM_RRC_RRMM_EST_CNF_FLG
            == (g_GmmReqCnfMng.ucCnfMask & GMM_RRC_RRMM_EST_CNF_FLG))
        {
            return;
        }

        /* W��RRC���ӻ�δ���� */
        if (GMM_TRUE != g_GmmGlobalCtrl.ucSigConFlg)
        {
            pNasMsg = Gmm_DetachRequestMsgMake();                       /* DETACH REQUEST��Ϣ����                   */

            Gmm_SndRrmmEstReq (RRC_EST_CAUSE_DETACH,
                               GMM_RRC_IDNNS_UNKNOWN,
                               pNasMsg);                                /* ����RRMM_EST_REQ                         */

            Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);      /* ֪ͨMMC PS�������������ڽ���             */

            GMM_CasFsmStateChangeTo(GMM_DEREGISTERED_NORMAL_SERVICE);

            if ((GMM_DETACH_COMBINED_SIM_REMOVE == g_GmmGlobalCtrl.ucSpecProc)
             || (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc))
            {                                                                   /* ��ǰ������combined sim remove��power off */
                g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;   /* �ñ�־λ����detach                       */
            }

            /* G�¹ػ��ο��������:GMM����5S��ʱ��,����detach������ֻ��Ҫ����5�� */
            Gmm_TimerStart(GMM_TIMER_DETACH_FOR_POWER_OFF);
        }

        return;
    }

    /* �ػ�������ʱ����ʱ��ǿ�ƹػ� */
    NAS_EventReport(WUEPS_PID_GMM,
                    NAS_OM_EVENT_DETACH_FINISH,
                    VOS_NULL_PTR,
                    NAS_OM_EVENT_NO_PARA);

    if (GMM_TRUE != GMM_IsCasGsmMode())
    {
        /* W�������������ڣ��ͷ���· */
        if (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg)
        {
            Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
        }

        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);
    }

    /* ���P_TMSI_SIGNATURE */
    if (GMM_UEID_P_TMSI_SIGNATURE
            == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
    }

    /* ��MMC�������Ӧ��ģ��ظ���Ϣ */
    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);

    if (GMM_DETACH_COMBINED_POWER_OFF == g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_GMM_SndMmGprsDetachComplete();
    }

    Gmm_SndMmcPowerOffCnf();
    Gmm_ComCnfHandle();
    NAS_GMM_FreeTlliForPowerOff();

    /* ���ȫ�ֱ��� */
    if (GMM_MSG_HOLD_FOR_POWEROFF == (g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk & GMM_MSG_HOLD_FOR_POWEROFF))
    {
        Gmm_MemFree(g_GmmGlobalCtrl.MsgHold.ulMsgAddrForPowerOff);
        g_GmmGlobalCtrl.MsgHold.ulMsgHoldMsk &= ~GMM_MSG_HOLD_FOR_POWEROFF;
    }
    Gmm_HoldBufferFree();

    GMM_BufferMsgDump();

    Gmm_ComVariantInit();

    return;
}
VOS_VOID Gmm_TimProtectExpired(VOS_VOID)
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimProtectExpired:WARNING: Protected Timer is expired");

    /* �ȴ�USIM����Ȩ���������� */
    if (GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG
       == (g_GmmReqCnfMng.ucCnfMask & GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG))
    {
        g_GmmReqCnfMng.ucCnfMask &= ~GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;


        g_GmmAuthenCtrl.ucAuthenAttmptCnt++;

        if (GMM_AUTHEN_ATTEMPT_MAX_CNT == g_GmmAuthenCtrl.ucAuthenAttmptCnt)
        {
            Gmm_AuCntFail();            /* ��Ȩʧ�ܴ����������� */
        }
    }
}


VOS_VOID Gmm_RcvTimerExpired(
    VOS_UINT8                           ucTimerId
)
{
    VOS_UINT32                         *pulTimerRunMask     = VOS_NULL_PTR;  
    VOS_UINT8                           ucTimerBitIndex;
    
    NAS_INFO_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:INFO: Timer Expired: ", ucTimerId);

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
 

    NAS_TIMER_EventReport(ucTimerId, WUEPS_PID_GMM, NAS_OM_EVENT_TIMER_OPERATION_EXPIRED);

    /*lint -e701*/
    if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex )))
    /*lint +e701*/
    {
        /* ָ��Timer�Ѿ�����  */
        Gmm_TimerStop(ucTimerId);
    }
    else
    {
        /* �ö�ʱ����ǰδ���� */
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: The Timer hasn't been started: ", ucTimerId);
        return;
    }

    switch (ucTimerId)
    {
    case  GMM_TIMER_T3302:
        Gmm_Tim3302Expired();
        break;
    case  GMM_TIMER_T3310:
        Gmm_Tim3310Expired();
        break;
    case  GMM_TIMER_T3311:
        Gmm_Tim3311Expired();
        break;
    case  GMM_TIMER_T3312:
        Gmm_Tim3312Expired();
        break;
    case  GMM_TIMER_T3316:
        Gmm_Tim3316Expired();
        break;
    case  GMM_TIMER_T3317:
        Gmm_Tim3317Expired();
        break;
    case  GMM_TIMER_T3318:
        Gmm_Tim3318Expired();
        break;
    case  GMM_TIMER_T3319:
        Gmm_Tim3319Expired();
        break;
    case  GMM_TIMER_T3320:
        Gmm_Tim3320Expired();
        break;
    case  GMM_TIMER_T3321:
        Gmm_Tim3321Expired();
        break;
    case  GMM_TIMER_T3330:
        Gmm_Tim3330Expired();
        break;
    case  GMM_TIMER_1S:
        Gmm_Tim5sExpired();
        break;
    case  GMM_TIMER_PROTECT:
        Gmm_TimProtectExpired();
        break;
    case  GMM_TIMER_PROTECT_FOR_SIGNALING:
        Gmm_TimProtectForSignalingExpired();
        break;
    case  GMM_TIMER_SUSPENDED:
        GMM_LOG_WARN("GMM_TIMER_SUSPENDED expired.");
        GMM_TimSuspendedExpired();
        break;
    case  GMM_TIMER_T3314:
        GMM_TimReadyExpired();
        break;
    case  GMM_TIMER_RAU_RSP:
        GMM_TimRauRspExpired();
        break;
    case  GMM_TIMER_PROTECT_FOR_RR_REL:
        NAS_WARNING_LOG(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: PROTECT_FOR_RR_REL Expired");
        GMM_TimProtectForRrRel();
        break;
    case  GMM_TIMER_PROTECT_OLD_TLLI:
        GMM_TimProtectForOldTlli();
        break;
    case  GMM_TIMER_T3340:
        NAS_GMM_Timer3340Expired();
        break;
    case  GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF:
        NAS_GMM_TimerWaitInterRatCnfExpired();
        break;

    case  GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF:
        NAS_GMM_TimerWaitReselSecuCnfExpired();
        break;

    case  GMM_TIMER_WAIT_GET_HO_SECU_INFO_CNF:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_GMM_TimerWaitHoSecuCnfExpired();
#endif
        break;

    case GMM_TIMER_WAIT_CONNECT_REL:
        NAS_GMM_TimerWaitConnectRelExpired();
        break;

    case GMM_TIMER_TC_DELAY_SUSPEND_RSP:
        NAS_GMM_TimerTcDelaySuspendRspExpired();
        break;

    case GMM_TIMER_T3323:
#if (FEATURE_ON == FEATURE_LTE)
        NAS_GMM_Timer3323Expired();
#endif
        break;




#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_DELAY_RADIO_CAPA_TRIGED_RAU:
        NAS_GMM_TimerDelayRadioCapaTrigedRauExpired();
        break;
#endif


#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_WAIT_AS_MS_RADIO_CAPA_INFO:
        NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired();
        break;
#endif

    /* GMM �ػ�detach��ʱ����ʱ */
    case GMM_TIMER_DETACH_FOR_POWER_OFF:
        NAS_GMM_TimerDetachForPowerOffExpired();
        break;


    /* GMM��PS��detach���̱�����ʱ����ʱ */
    case GMM_TIMER_PROTECT_PS_DETACH:
        NAS_GMM_TimerProtectPsDetachExpired();
        break;



    /* GMM��GMM_TIMER_HO_WAIT_SYSINFO������ʱ����ʱ */
    case GMM_TIMER_HO_WAIT_SYSINFO:
        NAS_GMM_TimerHoWaitSysinfoExpired();
        break;

#if (FEATURE_ON == FEATURE_LTE)
    case GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU:
        NAS_GMM_TimerDelayVoiceDomainTrigRauExpired();
        break;
#endif


    case GMM_TIMER_DELAY_PS_SMS_CONN_REL:
        NAS_GMM_RcvTiDelayPsSmsConnRelExpired();
        break;

    default:
        NAS_WARNING_LOG1(WUEPS_PID_GMM, "Gmm_RcvTimerExpired:WARNING: Unhandled TimerId: ", ucTimerId);
        break;
    }
}


/***********************************************************************
  Module   : Gmm_TimerPauseForTc
  Function : GMMʹ�õĶ�ʱ����ͣ(TC������)
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1. ��־��  2004.06.18  �¹�����(TC��Ӧ)
 ************************************************************************/
VOS_VOID Gmm_TimerPauseForTc(
                         VOS_UINT8                   ucTimerId                      /* Timer ID                                 */
                         )
{
    VOS_UINT8    i;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSusTcMask           = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendTcMask(ucTimerId, &pulTimerSusTcMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (GMM_TIMER_ALL == ucTimerId)
    {
        for (i = 0; i < GMM_TIMER_NUM; i ++)
        {                                                                       /* ѭ����������TIMER                        */
            NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendTcMask(i, &pulTimerSusTcMask, &ucTimerBitIndex);

            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            {                                                                   /* �ö�ʱ���Ѿ�����                         */

                if (0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex)))
                {                                                               /* �ö�ʱ��û�б�����                       */
                    if (VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                           Mm_StopRelTimer(WUEPS_PID_GMM, i, &g_GmmTimerMng.aTimerInf[i].hTimer))
                    {                                                           /* ֹͣʧ�ܣ��Ѿ�ֹͣ��Timer������          */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPauseForTc:WARNING: Stop all timer unsuccessfully");
                        return;                                                 /* ����                                     */
                    }

                    (*pulTimerSusTcMask) |= (0x00000001 << ucTimerBitIndex);        /* ��Timer�Ĺ����־(TC)                    */
                    
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerPauseForTc:INFO: StopTimer: ",i);
                }
            }
        }
    }
    else if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    {                                                                           /* ��timer�Ѿ�����                          */
        if ((0 == ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
            &&(0 == ((*pulTimerSusMask) & (0x00000001 << ucTimerBitIndex))))
        {
            if( VOS_ERRNO_RELTM_STOP_TIMERINVALID ==
                 Mm_StopRelTimer(WUEPS_PID_GMM, ucTimerId, &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer))
            {                                                                   /* ��ͣʧ��                                 */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerPauseForTc:WARNING: Stop timer unsuccessfully");
                return;                                                         /* ����                                     */
            }
            (*pulTimerSusTcMask) |= (0x00000001 << ucTimerBitIndex);        /* ����Timer�Ĺ����־                      */
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerPauseForTc:INFO: StopTimer: ",ucTimerId);
        }
    }
    else
    {
    }
    /*lint +e701*/
    return;
}

/***********************************************************************
  Module   : Gmm_TimerResumeForTc
  Function : GMMʹ�õ���ͣ��Ķ�ʱ���Ļָ�(TC������)
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
     1.  ��־��  2004.06.18  �¹�����(TC��Ӧ)
 ************************************************************************/
VOS_VOID Gmm_TimerResumeForTc(
                          VOS_UINT8                   ucTimerId                     /* Timer ID                                 */
                          )
{
    VOS_UINT8    i;
    VOS_UINT32                         *pulTimerRunMask             = VOS_NULL_PTR;  
    VOS_UINT32                         *pulTimerSusMask             = VOS_NULL_PTR;
    VOS_UINT32                         *pulTimerSusTcMask           = VOS_NULL_PTR;    
    VOS_UINT8                           ucTimerBitIndex;

    NAS_GMM_GetTimerRunMask(ucTimerId, &pulTimerRunMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendMask(ucTimerId, &pulTimerSusMask, &ucTimerBitIndex);
    NAS_GMM_GetTimerSuspendTcMask(ucTimerId, &pulTimerSusTcMask, &ucTimerBitIndex);

    /*lint -e701*/
    if (GMM_TIMER_ALL == ucTimerId)
    {
        for (i = 0; i < GMM_TIMER_NUM; i ++)
        {                                                                       /* ѭ����������TIMER                        */
            NAS_GMM_GetTimerRunMask(i, &pulTimerRunMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendMask(i, &pulTimerSusMask, &ucTimerBitIndex);
            NAS_GMM_GetTimerSuspendTcMask(i, &pulTimerSusTcMask, &ucTimerBitIndex);

            if (0 != ((*pulTimerRunMask) & (0x00000001 << ucTimerBitIndex)))
            {                                                                   /* �ö�ʱ���Ѿ�����                         */
                if (0 != ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
                {                                                               /* �ö�ʱ���Ѿ�����                         */
                    if (VOS_OK != Mm_StartRelTimer(
                                           &g_GmmTimerMng.aTimerInf[i].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                           WUEPS_PID_GMM,
                                           g_GmmTimerMng.aTimerInf[i].ulTimerVal,         /* ʱ��                                     */
                                           (VOS_UINT32)i,            /* ��Ϣ���е�ID                             */
                                           g_GmmTimerMng.aTimerInf[i].ulParam,               /* ��Ϣ��ַ                                 */
                                           g_GmmTimerMng.aTimerInf[i].ucMode          /* ��Ϣ���ȼ�                               */
                                           ))
                    {                                                           /* �ָ�ʧ��                                 */
                        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResumeForTc:WARNING: Start all timer unsuccessfully");
                        return;                                                 /* ����                                     */
                    }
                    
                    (*pulTimerSusTcMask)
                        &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);      /* ��Timer�Ĺ����־                        */
                    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerResumeForTc:INFO: StartTimer: ",i);
                }
            }
        }
    }
    else if (0 != ( (*pulTimerRunMask) & ( 0x00000001 << ucTimerBitIndex)))
    {                                                                           /* ��timer�Ѿ�����                          */
        if (0 != ((*pulTimerSusTcMask) & (0x00000001 << ucTimerBitIndex)))
        {
            if( VOS_OK != Mm_StartRelTimer(
                                &g_GmmTimerMng.aTimerInf[ucTimerId].hTimer,     /* ���TIMER ID�ĵ�ַ                       */
                                WUEPS_PID_GMM,
                                g_GmmTimerMng.aTimerInf[ucTimerId].ulTimerVal,         /* ʱ��                                     */
                                (VOS_UINT32)ucTimerId,            /* ��Ϣ���е�ID                             */
                                g_GmmTimerMng.aTimerInf[ucTimerId].ulParam,               /* ��Ϣ��ַ                                 */
                                g_GmmTimerMng.aTimerInf[ucTimerId].ucMode          /* ��Ϣ���ȼ�                               */
                                ))
            {                                                                   /* �ָ�ʧ��                                 */
                PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimerResumeForTc:WARNING: Start timer unsuccessfully");
                return;                                                         /* ����                                     */
            }
            (*pulTimerSusTcMask)
                &= ~(VOS_UINT32)(0x00000001 << ucTimerBitIndex);      /* ����Timer�Ĺ����־                      */
            PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_TimerResumeForTc:INFO: StartTimer: ",ucTimerId);
        }
    }
    else
    {
    }
    /*lint +e701*/
    return;
}
VOS_VOID Gmm_TimProtectForSignalingExpired(VOS_VOID)
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_TimProtectForSignalingExpired:WARNING: Protected timer for signalling is expired");
    GMM_SndRrmmRelReqGsm();

    /* ��ȡ���ű��ܶ����Ƿ�ʹ�� */
    if (VOS_TRUE == NAS_MML_GetDailRejectCfg())
    {
        GMM_SndSmServiceRej(GMM_SM_CAUSE_TIMER_SIGNALING_PROTECT_EXPIRED);

        g_GmmServiceCtrl.ucSmFlg = GMM_FALSE;
    }
}


VOS_VOID GMM_TimProtectForRrRel()
{
    RRMM_REL_IND_STRU *prrmm_rel_ind;

    if ( GMM_ABORT_CURRENT_SERVICE == g_GmmGlobalCtrl.ucSpecProc )
    {
        prrmm_rel_ind = (RRMM_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM, sizeof(RRMM_REL_IND_STRU) );
        if ( VOS_NULL_PTR == prrmm_rel_ind )
        {
            Gmm_ComStaChg(GMM_REGISTERED_NORMAL_SERVICE);
        }
        else
        {
            prrmm_rel_ind->MsgHeader.ulSenderPid = WUEPS_PID_WRR;
            prrmm_rel_ind->MsgHeader.ulMsgName = RRMM_REL_IND;
            prrmm_rel_ind->ulCnDomainId = RRC_NAS_PS_DOMAIN;
            prrmm_rel_ind->ulRelCause = RRC_REL_CAUSE_NAS_ABORT;
            prrmm_rel_ind->ulRrcConnStatus = RRC_RRC_CONN_STATUS_ABSENT;

            Gmm_RcvRrmmRelInd(prrmm_rel_ind);

            PS_FREE_MSG(WUEPS_PID_GMM, prrmm_rel_ind);

        }

        g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;

        return;
    }

    if (GMM_DEREGISTERED_INITIATED != g_GmmGlobalCtrl.ucState)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_TimProtectForRrRel:WARNING: Gmm State is unexpected.");
        return;
    }

    Gmm_ComStaChg(GMM_DEREGISTERED_NORMAL_SERVICE);                             /* ����״̬�Ĺ�������                       */

    if (GMM_DETACH_NORMAL_NETMODE_CHANGE != g_GmmGlobalCtrl.ucSpecProc)
    {
        NAS_MML_SetPsAttachAllowFlg(VOS_FALSE);          /* ����PS���ֹע���־                     */
    }

    if (GMM_UEID_P_TMSI_SIGNATURE
        == (g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask & GMM_UEID_P_TMSI_SIGNATURE))
    {                                                                           /* DETACH�ɹ���ʹ����P_TMSI_SIGNATURE       */
        g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask &= ~GMM_UEID_P_TMSI_SIGNATURE;   /* ���P_TMSI_SIGNATURE                     */

        NAS_MML_InitUeIdPtmsiSignatureInvalid();

        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
        if (NAS_MML_SIM_TYPE_USIM == NAS_MML_GetSimType())
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_USIM_EFPSLOCI_ID);       /* ����SIM����Ϣ                            */
        }
        else
        {
            Gmm_SndAgentUsimUpdateFileReq(USIMM_GSM_EFLOCIGPRS_ID);
        }
        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
    }
    /* �жϵȴ���־�Ƿ���ڣ������������MMC,MM����DETACH��Ϣ */
    if (GMM_WAIT_NULL_DETACH != g_GmmGlobalCtrl.stDetachInfo.enDetachType)
    {
        NAS_GMM_SndMmcMmDetachInfo();
    }
    else if ( VOS_FALSE == NAS_MML_GetPsAttachAllowFlg() )
    {
        /* �յ������ȥע��ɹ�����Ҫ֪ͨMM������MM������T3212��ʱ�� */
        NAS_GMM_SndMmGprsDetachComplete();
    }
    else
    {

    }


    /* ��MMC����PSע���� */
    NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                 GMM_MMC_ACTION_RESULT_FAILURE,
                                 NAS_MML_REG_FAIL_CAUSE_MS_CFG_DOMAIN_NOT_SUPPORT);

    g_GmmGlobalCtrl.ucSpecProc = GMM_NULL_PROCEDURE;
    Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

	/* W�´�����������ʱ��֪ͨPS�����·�ͷ� */
	if ( (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
		&& (GMM_TRUE == g_GmmGlobalCtrl.ucSigConFlg) )
	{
		Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
	}
}
VOS_VOID GMM_TimSuspendedExpired()
{
    switch(g_GmmGlobalCtrl.ucState)
    {
        case GMM_SUSPENDED_NORMAL_SERVICE:
            GMM_LOG_INFO("GMM_TimSuspendedExpired:MMC is still suspended.");
            Gmm_TimerStart(GMM_TIMER_SUSPENDED);
            break;

        case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
            GMM_LOG_WARN("GMM_TimSuspendedExpired:MMC have not get sys info.");
            g_GmmRauCtrl.ucNpduCnt = 0x0;
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
            {
                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
            }
            else
            {
#if 0
                GMM_SndRabmGprsInfoInd(GMM_RABM_GPRS_SUPPORTED, GMM_RABM_PROC_HANDOVER,
                               GMM_RABM_IMMEDIATELY_RAU);
#endif

                GMM_SndRabmRauInd(GMM_RABM_RAU_UNDER_HANDOVER, GMM_RABM_RAU_FAILURE);
            }
            Gmm_ComStaChg(gstGmmSuspendCtrl.ucPreState);
            GMM_ResumeTimer(GMM_TIMER_RESUME);
            GMM_ResumeFailure();
            break;
        default:
            GMM_LOG_WARN("GMM_TimSuspendedExpired:Receive GMM_TIMER_SUSPENDED in abnormal state.");
            break;
    }
    return;
}


VOS_VOID GMM_TimProtectForOldTlli()
{
    Gmm_TimerStop(GMM_TIMER_PROTECT_OLD_TLLI);
    GMM_FreeOldTlli();
    gstGmmCasGlobalCtrl.ulOldTLLI = 0xffffffff;
}


VOS_VOID NAS_GMM_TimerWaitInterRatCnfExpired( VOS_VOID )
{
    NAS_MSG_STRU                            *pstSendNasMsg = VOS_NULL_PTR;

    g_GmmInterRatInfoCtrl.ucInterRatCnfMsgRcvdFlg = VOS_TRUE;

    if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucAttachCmpWaitInterRatCnfMsg)
    {
        if (VOS_TRUE == g_GmmAttachCtrl.ucSmCnfFlg)
        {
            /* ATTACH��������SM������,֪ͨSM GMMע��ɹ�,����ucSmCnfFlg��־ */
            Gmm_SndSmEstablishCnf(GMM_SM_EST_SUCCESS, GMM_SM_CAUSE_SUCCESS);
            g_GmmAttachCtrl.ucSmCnfFlg = VOS_FALSE;
        }

        /* �ظ�����Attach Complete ��Ϣ */
        pstSendNasMsg = Gmm_AttachCompleteMsgMake();

        if (VOS_NULL_PTR == pstSendNasMsg)
        {
            NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Make Attach Complete Msg Fail!");
            return;
        }
        Gmm_SndRrmmDataReq(RRC_NAS_MSG_PRIORTY_HIGH, pstSendNasMsg);

    }
    else if (VOS_TRUE == g_GmmInterRatInfoCtrl.ucRauCmpWaitInterRatCnfMsg)
    {
        /* ����Ҫ�ȴ�RABM�Ļظ���Ϣ�������Ѿ��յ�RABM�Ļظ���Ϣ������RAU���̽�������Ӧ���� */
        if (   (VOS_FALSE == gstGmmCasGlobalCtrl.ucWaitRabmRauRspFlg)
            || (VOS_TRUE == gstGmmCasGlobalCtrl.ucRabmRauRspRcvdFlg))
        {
            NAS_GMM_RauCompleteHandling();
        }
    }
    else
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_RcvInterRatHandoverInfoCnf: Not Expected Msg Received.");
    }

    return;
}


VOS_VOID  NAS_GMM_TimerWaitReselSecuCnfExpired( VOS_VOID )
{
    if (NAS_GMM_SPEC_PROC_RAU == NAS_GMM_GetSpecProcNeedSecInfo())
    {
        Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
    }
    else
    {
        Gmm_SndAttachReq();
    }

    NAS_GMM_SetLmmSecInfoFlg(VOS_FALSE);

    g_GmmInterRatCellReselect = 0;

    /* ��Ҫ��ȡ��ȫ������ʱ,����ǰ�Ľ��뼼���ӳٸ��� */
    gstGmmSuspendCtrl.ucPreRat = NAS_MML_GetCurrNetRatType();

    NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_BUTT);
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_VOID  NAS_GMM_TimerWaitHoSecuCnfExpired( VOS_VOID )
{
    /* �����ʱ��GMM�Ĺ���״̬�����ҹ�����ΪLTE������MMC�ظ�����ظ� */
    if ( (NAS_MML_NET_RAT_TYPE_LTE     == NAS_MML_GetCurrNetRatType())
      && (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();
    }

}
VOS_VOID NAS_GMM_Timer3323Expired(VOS_VOID)
{
    NAS_MML_RPLMN_CFG_INFO_STRU        *pstRplmnCfgInfo = VOS_NULL_PTR;

    pstRplmnCfgInfo = NAS_MML_GetRplmnCfg();

    /* 3GPP 24.008 4.7.2.2�½�������
       After expiry of timer T3323 the MS shall deactivate ISR by setting
       its TIN to "GUTI". */
    if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == pstRplmnCfgInfo->enTinType)
    {
        NAS_GMM_WriteTinInfoNvim(NAS_MML_TIN_TYPE_GUTI, pstRplmnCfgInfo->aucLastImsi);
        Gmm_TimerStop(GMM_TIMER_T3323);

        /* ISRȥ�����Ҫ����pdp��������ISR����ǰ����� */
        NAS_MML_UpdateAllPsBearIsrFlg(NAS_MML_PS_BEARER_EXIST_BEFORE_ISR_ACT);
    }
    return;
}

#endif

/* �յ�MM��CsConnectIndʱ,���RRC���Ӵ���,��������RAU��
   ����,�յ�������ϱ���ϵͳ��Ϣ����������RAU */


VOS_VOID NAS_GMM_TimerWaitConnectRelExpired()
{
    PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_TimerWaitConnectRelExpired:WARNING: Wait connect rel expired.");

    if ((GMM_DEREGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState)
     && (GMM_REGISTERED_PLMN_SEARCH != g_GmmGlobalCtrl.ucState))
    {
        return;
    }

    /* �����ǰפ��WCDMA������MMCָʾ���Ӳ����ڣ�������MMCָʾTBF�ͷ� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        /* ����PS�������Ӳ����� */
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        /* ��MMC�������Ӳ�������Ϣ */
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ABSENT);

        NAS_GMM_ClearGmmLinkCtrlStru();
    }
    else
    {
        /* ����TBF���Ӳ����� */
        NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

        /* ��MMC�������Ӳ�������Ϣ */
        Gmm_SndMmcTBFRelInd();
    }

    return;
}
VOS_VOID NAS_GMM_TimerTcDelaySuspendRspExpired(VOS_VOID)
{
#if (defined(__PS_WIN32_RECUR__)) || ( VOS_WIN32 == VOS_OS_VER )
    if (1 == g_ulGmmDelaySuspendRsp)
    {
        Gmm_TimerStart(GMM_TIMER_SUSPENDED);

        GMM_SndMmcSuspendRsp();

        return;
    }
#endif

    /* ���ڴ˴�״̬��Ǩ�ƣ���ʹ���л�֮ǰGMM״̬�����жϡ� */
    if (GMM_TC_ACTIVE != gstGmmSuspendCtrl.ucPreState)
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_TimerTcDelaySuspendRspExpired:WARNING: Expired NOT GMM_TC_ACTIVE STATE");
        return;
    }

    Gmm_TimerStart(GMM_TIMER_SUSPENDED);

    GMM_SndMmcSuspendRsp();
}

#if (FEATURE_ON == FEATURE_LTE)


VOS_UINT32 NAS_GMM_CheckRatTrigedRAU(
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstOldRatList,
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstNewRatList
)
{
    VOS_UINT32                          ulLteExistInOldRatList;
    VOS_UINT32                          ulLteExistInNewRatList;
    VOS_UINT32                          ulWExistInNewRatLList;
    VOS_UINT32                          ulGExistInNewRatLList;

    /* ��ǰ����GUģ��ģʽ�仯�漰�����ӻ����Lģʱ������RAU,��������£������� */
    ulLteExistInOldRatList = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstOldRatList);
    ulLteExistInNewRatList = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_LTE,
                                                        pstNewRatList);
    ulWExistInNewRatLList  = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_WCDMA,
                                                        pstNewRatList);
    ulGExistInNewRatLList  = NAS_MML_IsSpecRatInRatList(NAS_MML_NET_RAT_TYPE_GSM,
                                                        pstNewRatList);

    if (ulLteExistInOldRatList != ulLteExistInNewRatList)
    {
        if ((VOS_TRUE == ulWExistInNewRatLList)
         || (VOS_TRUE == ulGExistInNewRatLList))
        {
            return VOS_TRUE;
        }
    }


    return VOS_FALSE;
}
VOS_VOID NAS_GMM_TimerDelayRadioCapaTrigedRauExpired(VOS_VOID)
{
    /* rau��attach��ms radio capa IE��Я����LTE���������������ϱ���LTE������һ�£���Ҫ����rau */
    if (g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromAs == g_GmmGlobalCtrl.UeInfo.ucMsRadioCapSupportLteFromRegReq)
    {
        return;
    }

    NAS_GMM_HandleMsRadioCapLteSupportChanged();

    return;

}


VOS_VOID NAS_GMM_TimerWaitAsMsRadioCapaInfoExpired(VOS_VOID)
{
    VOS_UINT32                          ulGetLmmSecInfoFlg;

    VOS_UINT32                          ucIsSupportLteCapaFlg;

    VOS_UINT8                           ucLDisabledUseLInfoFlag;

    ucLDisabledUseLInfoFlag = NAS_MML_GetLteDisabledRauUseLteInfoFlag();

    ucIsSupportLteCapaFlg  = NAS_MML_IsSupportLteCapability();

    ulGetLmmSecInfoFlg = NAS_GMM_GetLmmSecInfoFlg();

    /* l disabled attach ����l��ȡ��ȫ�����ģ� l disabled rau nv�����Ƿ���Ҫ��l��ȡ��ȫ������*/
    if ((NAS_MML_TIN_TYPE_GUTI == NAS_MML_GetTinType())
     && (VOS_FALSE == gstGmmSuspendCtrl.ucGetLteSecContext)
     && (VOS_FALSE == ulGetLmmSecInfoFlg)
     && ((VOS_TRUE == ucIsSupportLteCapaFlg)
      || ((VOS_TRUE == ucLDisabledUseLInfoFlag)
       && (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState))))
    {
        NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_RAU);
        NAS_GMM_SetLmmSecInfoFlg(VOS_TRUE);

        if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_RAU);
        }

        if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
        {
            NAS_GMM_SetSpecProcNeedSecInfo(NAS_GMM_SPEC_PROC_ATTACH);
        }

        /* ��Lģ����GMM_LMM_RESEL_SECU_INFO_REQ */
        NAS_GMM_SndLmmReselSecuInfoReq();

        /* ������ʱ�� */
        Gmm_TimerStart(GMM_TIMER_WAIT_GET_RESEL_SECU_INFO_CNF);

        return;
    }

    if (GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_SndRoutingAreaUpdateReq(NAS_GMM_GetRauUpdateType());
        return;
    }

    if (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
    {
        Gmm_SndAttachReq();
    }
    return;
}



VOS_UINT32 NAS_GMM_IsNeedStartT3323(VOS_VOID)
{
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType;
    VOS_UINT8                           ucIsNeedStartT3323;

    enTinType          = NAS_MML_GetTinType();
    ucIsNeedStartT3323 = VOS_FALSE;

    switch (g_GmmGlobalCtrl.ucState)
    {
        case GMM_REGISTERED_LIMITED_SERVICE:
        case GMM_REGISTERED_NO_CELL_AVAILABLE:
        case GMM_DEREGISTERED_ATTACH_NEEDED:
        case GMM_REGISTERED_UPDATE_NEEDED:

             /* GMM����GMM_REGISTERED_NO_CELL_AVAILABLE��GMM_REGISTERED_LIMITED_SERVICE��ISR���
                ��Ҫ����T3323��ʱ��,GMM����ע�ᱻbar״̬��ISR�����Ҫ����T3323��ʱ�� */
            if (NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == enTinType)
            {
                ucIsNeedStartT3323 = VOS_TRUE;
            }
            break;

        case GMM_REGISTERED_PLMN_SEARCH:

            /* GMM����ʱ����GMM_REGISTERED_PLMN_SEARCH��ISR�����Ҫ����T3323��ʱ����
               ���������米���ѵĿ���ָ����״̬ISR������������T3323  */
            if ((NAS_MML_TIN_TYPE_RAT_RELATED_TMSI == NAS_MML_GetTinType())
             && (GMM_TRUE == g_GmmGlobalCtrl.ucCvrgAreaLostFlg))
            {
                ucIsNeedStartT3323 = VOS_TRUE;
            }
            break;

        default:
            break;
    }

    return ucIsNeedStartT3323;
}

#endif




VOS_VOID NAS_GMM_TimerHoWaitSysinfoExpired(VOS_VOID)
{
    /* �л�����һ����ҵ��ʱ�Ż��У�PS�򲻱�ע��ɹ������̣���CS�ϱ�����֤פ����Ϣ���ź�ǿ�ȸ��£�����IMSA���ܻ���ǰȥ����IMSA
       ����:L2G��SRVCC,CMCCҪ��绰����֮�󣬲���ȥע��IMSA��
       ��ʱ����������̣�MMC�ͻ�֪ͨMMAע��״̬�ͷ���״̬��MMA�ͻ�֪ͨIMSA����״̬�仯 */
    /* ��ǰ����GMM_SUSPENDED_WAIT_FOR_SYSINFO״̬������Ҫ����  */
    if ( GMM_SUSPENDED_WAIT_FOR_SYSINFO != Gmm_GetState() )
    {
        return ;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        return;
    }

    Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);

    return;
}


#if (FEATURE_ON == FEATURE_LTE)
VOS_VOID NAS_GMM_TimerDelayVoiceDomainTrigRauExpired(VOS_VOID)
{
    /* ���Э���½�:
    3GPP 24008:
    4.7.5.1 Normal and periodic routing area updating procedure

    The normal routing area updating procedure is initiated:
    ......
    -    when the UE's usage setting or the voice domain preference for E-UTRAN change in the MS;
    ......
    */

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_INT8                  cVersion;

    cVersion        = NAS_Common_Get_Supported_3GPP_Version(MM_COM_SRVDOMAIN_PS);
    pstConnStatus   = NAS_MML_GetConnStatus();

    if (cVersion < PS_PTL_VER_R9)
    {
        return;
    }

    /* voice domain���ϴη���ע��ʱ����ͬ������Ҫ����RAU */
    if (g_GmmGlobalCtrl.UeInfo.enVoiceDomainFromRegReq == NAS_MML_GetVoiceDomainPreference())
    {
        return;
    }

    /* �������CSҵ����ֱ�ӷ��� */
    if (VOS_TRUE == pstConnStatus->ucCsServiceConnStatusFlg)
    {
        return;
    }

    /* ������ڷ���CSҵ����������ʱ����ҵ����ʧ��������ʱ������RAU��
       ҵ����ɹ���ʱ����ʱʱ��ֱ�ӷ��� */
    if ((VOS_TRUE == NAS_MML_GetCsServiceBufferStatusFlg())
     && (VOS_TRUE == pstConnStatus->ucCsSigConnStatusFlg))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);

        return;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == g_GmmGlobalCtrl.ucState))
    {
        Gmm_RoutingAreaUpdateInitiate(GMM_UPDATING_TYPE_INVALID);
        return;
    }

    if ((GMM_ROUTING_AREA_UPDATING_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == g_GmmGlobalCtrl.ucState))
    {
        Gmm_TimerStart(GMM_TIMER_DELAY_VOICE_DOMAIN_TRIG_RAU);
    }

    return;
}
#endif


/*****************************************************************************
 �� �� ��  : NAS_GMM_RcvTiDelayPsSmsConnRelExpired
 ��������  : GMM_TIMER_DELAY_PS_SMS_CONN_REL��ʱ����ʱ�Ĵ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��9��23��
    ��    ��   : c00318887
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_GMM_RcvTiDelayPsSmsConnRelExpired(VOS_VOID)
{
    if (VOS_TRUE == NAS_GMM_IsNeedProcDelayPsSmsConnRelTimer())
    {
        Gmm_SndRrmmRelReq(RRC_CELL_UNBARRED);
    }

    return;    
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerRunMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerRunMask   �ö�ʱ��RunMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerRunMask �� g_GmmTimerMng.ulTimerRunMaskEx
             VOS_UINT8      *pucTimerBitIndex  �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerRunMask,  
    VOS_UINT8                          *pucTimerBitIndex
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerRunMask)              = &g_GmmTimerMng.ulTimerRunMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerRunMask)              = &g_GmmTimerMng.ulTimerRunMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8           ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerSusMask   �ö�ʱ��SusMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerSusMask �� g_GmmTimerMng.ulTimerSusMaskEx
             VOS_UINT8      *pucTimerIndex     �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerSusMask)              = &g_GmmTimerMng.ulTimerSusMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerSusMask)              = &g_GmmTimerMng.ulTimerSusMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}


/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendTcMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8       ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerSusTcMask   �ö�ʱ��ulTimerSusTcMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerSusTcMask �� g_GmmTimerMng.ulTimerSusTcMaskEx
             VOS_UINT8      *pucTimerBitIndex    �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendTcMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerSusTcMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerSusTcMask)            = &g_GmmTimerMng.ulTimerSusTcMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerSusTcMask)            = &g_GmmTimerMng.ulTimerSusTcMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}

/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendTcMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8       ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulTimerRunMask   �ö�ʱ��ulTimerValMask ��ʾλ�ĳ�Ա: g_GmmTimerMng.ulTimerValMask �� g_GmmTimerMng.ulTimerValMaskEx
             VOS_UINT8      *pucTimerIndex     �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerValMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulTimerValMask,  
    VOS_UINT8                          *pucTimerBitIndex
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulTimerValMask)              = &g_GmmTimerMng.ulTimerValMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulTimerValMask)              = &g_GmmTimerMng.ulTimerValMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}
/***********************************************************************
  Module   : NAS_GMM_GetTimerSuspendCtrlRunMask
  Function : GMMʹ�õĶ�ʱ������
  Input    : VOS_UINT8       ucTimerId     ��ʱ��ID
  Output   : 
             VOS_UINT32    **pulSuspendCtrlRunMask   �ö�ʱ��TimerSusTcMask ��ʾλ�ĳ�Ա: gstGmmSuspendCtrl.ulTimerRunMask �� gstGmmSuspendCtrl.ulTimerRunMaskEx
             VOS_UINT8      *pucTimerBitIndex     �ö�ʱ���ڱ�ʾλ������
  NOTE     : ��
  Return   : ��
  History  :
  1.��    ��   : 2015��9��26��
    ��    ��   : c00318887
    �޸�����   : �½�����
 ************************************************************************/
VOS_VOID NAS_GMM_GetTimerSuspendCtrlRunMask(
    VOS_UINT8                           ucTimerId,
    VOS_UINT32                        **pulSuspendCtrlRunMask,  
    VOS_UINT8                          *pucTimerBitIndex 
)
{
    if (ucTimerId < GMM_TIMER_ONE_GROUP_NUMR)
    {
        (*pulSuspendCtrlRunMask)        = &gstGmmSuspendCtrl.ulTimerRunMask;
        (*pucTimerBitIndex)             = ucTimerId;
    }
    else
    {
        (*pulSuspendCtrlRunMask)        = &gstGmmSuspendCtrl.ulTimerRunMaskEx;
        (*pucTimerBitIndex)             = ucTimerId - GMM_TIMER_ONE_GROUP_NUMR;
    }
}


/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif

