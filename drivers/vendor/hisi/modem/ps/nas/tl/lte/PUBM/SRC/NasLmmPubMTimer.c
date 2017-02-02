


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include  "NasLmmPubMTimer.h"

/*lint -e767*/
#define    THIS_FILE_ID            PS_FILE_ID_NASMMPUBMTMER_C
#define    THIS_NAS_FILE_ID        NAS_FILE_ID_NASMMPUBMTMER_C
/*lint +e767*/

/*****************************************************************************
  1.1 Cplusplus Announce
*****************************************************************************/
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*****************************************************************************
  2 Declare the Global Variable
*****************************************************************************/


/*****************************************************************************
  3 Function
*****************************************************************************/
/*****************************************************************************
  3.1 ״̬��ʱ�� Function
*****************************************************************************/


/*lint -e960*/
/*lint -e961*/
VOS_VOID    NAS_LMM_StartStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulParam;            /* ��ʱ�����ͱ�ʶ */

    /*��ȡ��״̬��ʱ�����ƿ��ַ*/
    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);
    /*�޷���ȡ�ö�ʱ�����ƿ��ַ��˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_StartStateTimer, pstStateTimer = 0");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_StartStateTimer_ENUM
,LNAS_NULL_PTR);
        return;
    }

    /*����״̬��ʱ���Ƿ������У�����������У���ֹͣ�ö�ʱ����
      ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
    if ( VOS_NULL_PTR != pstStateTimer->psthTimer )
    {
        ulRslt = PS_STOP_REL_TIMER(&(pstStateTimer->psthTimer));
        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartStateTimer, Start State Timer Failure!",
                                 enStateTimerId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StartStateTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                 enStateTimerId);
            return;
        }
    }

    /*���ʱ��Ϊ�㣬ֱ�ӷ��أ���������ʱ��*/
    if(0 == pstStateTimer->ulTimerLen)
    {
        NAS_LMM_PUBM_LOG1_WARN("NAS_LMM_StartStateTimer:TimerLen = 0; enStaTimerId = ",
                               enStateTimerId);
        TLPS_PRINT2LAYER_WARNING1(NAS_LMM_StartStateTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                               enStateTimerId);
        return;
    }

    pstStateTimer->ucTimerType          = NAS_LMM_STATE_TIMER;
    ulParam                             = pstStateTimer->ucTimerType;

    /*
    */
    /*NAS-MM״̬��ʱ���޲�����Ϣ��������ʱ��ʱ����ʱ����������ΪulParam
      ״̬��ʱ�����Ƿ�ѭ����ʱ������ʱ��ģʽΪVOS_RELTIMER_NOLOOP*/
    ulRslt = PS_START_REL_TIMER(&(pstStateTimer->psthTimer),
                                        PS_PID_MM,
                                        pstStateTimer->ulTimerLen,
                                        enStateTimerId,
                                        ulParam,
                                        VOS_RELTIMER_NOLOOP);
    /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
    if ( VOS_OK != ulRslt )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartStateTimer, Start State Timer Failure!",
                             enStateTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StartStateTimer_ENUM
,LNAS_FUNCTION_LABEL3,
                               enStateTimerId);
        return;
    }

    pstStateTimer->ucTimerRs            = NAS_LMM_TIMER_RS_RUNNING;
    pstStateTimer->ucTimerSs            = NAS_LMM_TIMER_SS_NOT_SUSPENDING;

    /*
    NAS_LMM_PUBM_LOG2_NORM("NAS_LMM_StartStateTimer OK. StateTimerId: Timer Len:",
                           enStateTimerId,pstStateTimer->ulTimerLen);
    */


    /* ��ʱ��״̬�������� */
    NAS_LMM_SndOmEmmTimerStatus(NAS_LMM_TIMER_RUNNING, (VOS_UINT16)enStateTimerId
                                , pstStateTimer->ulTimerLen);

    return;
}
VOS_VOID    NAS_LMM_StopStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulTimerRemainLen;

    /*��ȡ��״̬��ʱ�����ƿ��ַ*/
    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);
    /*�޷���ȡ�ö�ʱ�����ƿ飬˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopStateTimer, pstStateTimer = 0.enStateTimerId: ",
                             enStateTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopStateTimer_ENUM,LNAS_FUNCTION_LABEL1,
                               enStateTimerId);
        return;
    }

    /*����״̬��ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
      ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
    if ( VOS_NULL_PTR != pstStateTimer->psthTimer )
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstStateTimer->psthTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }
        ulRslt = PS_STOP_REL_TIMER(&(pstStateTimer->psthTimer));
        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopStateTimer, Stop State Timer Failure!",
                                 enStateTimerId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopStateTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                               enStateTimerId);
            return;
        }

        pstStateTimer->ucTimerRs        = NAS_LMM_TIMER_RS_NOT_RUNNING;
        pstStateTimer->ucTimerSs        = NAS_LMM_TIMER_SS_NOT_SUSPENDING;

        /* ��ʱ��״̬�������� */
        NAS_LMM_SndOmEmmTimerStatus(NAS_LMM_TIMER_STOPED, (VOS_UINT16)enStateTimerId
                                    , ulTimerRemainLen);

    }
    return;
}
VOS_VOID    NAS_LMM_SuspendStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer;
    VOS_UINT32                          ulTick;
    VOS_UINT32                          ulRslt;

    /*��ȡ��״̬��ʱ�����ƿ��ַ*/
    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);
    /*�޷���ȡ�ö�ʱ�����ƿ��ַ��˵����ʱ��ID�Ƿ�*/
    if ((VOS_NULL_PTR == pstStateTimer))
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SuspendStateTimer, pstStateTimer = 0");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SuspendStateTimer_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*����״̬��ʱ���Ƿ������У�����������У��Ȼ�ȡ��ʱ����ʣ��ʱ����
      ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
    if ( VOS_NULL_PTR != pstStateTimer->psthTimer )
    {
        ulRslt = VOS_GetRelTmRemainTime(&(pstStateTimer->psthTimer),
                                        &ulTick);
        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_SuspendStateTimer,VOS_GetRelTmRemainTime.enStateTimerId: ",
                                 enStateTimerId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_SuspendStateTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                                 enStateTimerId);
            return;
        }

        ulRslt = PS_STOP_REL_TIMER(&(pstStateTimer->psthTimer));
        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_SuspendStateTimer,VOS_StopRelTimer.enStateTimerId: ",
                                 enStateTimerId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_SuspendStateTimer_ENUM
,LNAS_FUNCTION_LABEL3,
                                 enStateTimerId);
            return;
        }

        pstStateTimer->ucTimerType      = NAS_LMM_STATE_TIMER;
        pstStateTimer->ucTimerSs        = NAS_LMM_TIMER_SS_SUSPENDING;
        pstStateTimer->ulTimerRemainLen = VOS_TmTickToMillSec(ulTick);
    }

    return;
}


VOS_VOID    NAS_LMM_ResumeStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulParam;            /* ��ʱ�����ͱ�ʶ */

    /*��ȡ��״̬��ʱ�����ƿ��ַ*/
    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);
    /*�޷���ȡ�ö�ʱ�����ƿ��ַ��˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_ResumeStateTimer, pstStateTimer = 0");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_ResumeStateTimer_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*����״̬��ʱ���Ƿ񱻹���*/
    if (    (VOS_NULL_PTR               == pstStateTimer->psthTimer)
         && (NAS_LMM_TIMER_RS_NOT_RUNNING == pstStateTimer->ucTimerRs)
         && (NAS_LMM_TIMER_SS_SUSPENDING == pstStateTimer->ucTimerSs) )
    {
        pstStateTimer->ucTimerType      = NAS_LMM_STATE_TIMER;
        ulParam                         = pstStateTimer->ucTimerType;

        /*NAS-MM״̬��ʱ���޲�����Ϣ��������ʱ��ʱ����ʱ����������ΪulParam
          ״̬��ʱ�����Ƿ�ѭ����ʱ������ʱ��ģʽΪVOS_RELTIMER_NOLOOP*/
        ulRslt = PS_START_REL_TIMER(&(pstStateTimer->psthTimer),
                                        PS_PID_MM,
                                        pstStateTimer->ulTimerRemainLen,
                                        enStateTimerId,
                                        ulParam,
                                        VOS_RELTIMER_NOLOOP );
        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_ResumeStateTimer, Start State Timer Failure!",
                                 enStateTimerId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ResumeStateTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                                 enStateTimerId);
            return;
        }

         /* ͬʱ�޸�g_stMmMainContext�ж�Ӧ��ʱ�������б�ʶ,��
        g_stMmMainContext.astMmTimerSta */
        pstStateTimer->ucTimerRs              = NAS_LMM_TIMER_RS_RUNNING;
    }
    else
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_ResumeStateTimer, State Timer is not suspended!",
                             enStateTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ResumeStateTimer_ENUM
,LNAS_FUNCTION_LABEL3,
                             enStateTimerId);
        return;
    }

    pstStateTimer->ucTimerSs            = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
    pstStateTimer->ulTimerRemainLen     = NAS_LMM_TIMER_ZERO_VALUE;

    return;
}


VOS_VOID    NAS_LMM_ModifyStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId,
                    VOS_UINT32                              ulTimerLen )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer;

    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);
    /*�޷���ȡ�ö�ʱ�����ƿ飬˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_ModifyStateTimer, pstStateTimer = 0.enStateTimerId: ",
                             enStateTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ModifyStateTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                             enStateTimerId);
        return;
    }

    pstStateTimer->ulTimerLen           = ulTimerLen;
    pstStateTimer->ucTimerType          = NAS_LMM_STATE_TIMER;

    NAS_LMM_PUBM_LOG2_NORM("NAS_LMM_ModifyStateTimer OK. StateTimerId, StateTimerLength",
                          enStateTimerId,
                          pstStateTimer->ulTimerLen );
    TLPS_PRINT2LAYER_ERROR2(NAS_LMM_ModifyStateTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                          enStateTimerId,
                          pstStateTimer->ulTimerLen);

    return;
}
VOS_VOID    NAS_LMM_StopAllStateTimer( VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimerList;
    VOS_UINT32                          ulTcbIdxLoop;
    VOS_UINT32                          ulRslt;

    /*��ȡ״̬��ʱ���б��׵�ַ*/
    pstStateTimerList = NAS_LMM_GetStateTimerListAddr();

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for ( ulTcbIdxLoop = TI_NAS_EMM_STATE_NO_TIMER + 1; ulTcbIdxLoop < NAS_LMM_STATE_TI_BUTT; ulTcbIdxLoop++ )
    {
        /*����״̬��ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
          ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
        if ( VOS_NULL_PTR != pstStateTimerList[ulTcbIdxLoop].psthTimer )
        {
            ulRslt = PS_STOP_REL_TIMER(&(pstStateTimerList[ulTcbIdxLoop].psthTimer));
            /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
            if ( VOS_OK != ulRslt )
            {
                /* ����ʧ�ܣ���ӡʧ����Ϣ */
                NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopAllStateTimer, Stop pstStateTimerList[%d] Failure!",
                                     ulTcbIdxLoop);
                TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopAllStateTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                     ulTcbIdxLoop);
            }

            pstStateTimerList[ulTcbIdxLoop].ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
            pstStateTimerList[ulTcbIdxLoop].ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
        }
    }

    return;
}
/*****************************************************************************
 Function Name   : NAS_LMM_SuspendInitStopPtlTimer
 Description     : �ڹ���ʱֹͣ��3412,3402,3423�������Э�鶨ʱ��
 Input           : VOS_VOID
 Output          : None
 Return          : None

 History         :
    1.FTY          2012-02-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_SuspendInitStopPtlTimer (VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimerList;
    VOS_UINT32                          ulTcbIdxLoop;
    VOS_UINT32                          ulRslt;

    /*��ȡ״̬��ʱ���б��׵�ַ*/
    pstPtlTimerList = NAS_LMM_GetPtlTimerListAddr();


    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SuspendInitStopPtlTimer. 3412",
                                      TI_NAS_EMM_PTL_T3412);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SuspendInitStopPtlTimer_ENUM,LNAS_FUNCTION_LABEL1,
                                      TI_NAS_EMM_PTL_T3412);
    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SuspendInitStopPtlTimer. 3402",
                                      TI_NAS_EMM_PTL_T3402);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_SuspendInitStopPtlTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                                      TI_NAS_EMM_PTL_T3402);

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for (   ulTcbIdxLoop = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START +1;
            ulTcbIdxLoop < NAS_LMM_PTL_TI_BUTT;
            ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
         ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
        if ( VOS_NULL_PTR != pstPtlTimerList[ulTcbIdxLoop].psthTimer )
        {
            /* ��ֹͣT3411,T3412,T3423,T3402, T3416*/
            if(  (TI_NAS_EMM_PTL_T3411 == (pstPtlTimerList[ulTcbIdxLoop].ulName))
               ||(TI_NAS_EMM_PTL_T3412 == (pstPtlTimerList[ulTcbIdxLoop].ulName))
               ||(TI_NAS_EMM_PTL_T3402 == (pstPtlTimerList[ulTcbIdxLoop].ulName))
               ||(TI_NAS_EMM_PTL_T3423 == (pstPtlTimerList[ulTcbIdxLoop].ulName))
               ||(TI_NAS_EMM_PTL_T3416 == (pstPtlTimerList[ulTcbIdxLoop].ulName)))
            {
                NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_SuspendInitStopPtlTimer. ",
                                      pstPtlTimerList[ulTcbIdxLoop].ulName);
                TLPS_PRINT2LAYER_INFO1(NAS_LMM_SuspendInitStopPtlTimer_ENUM
,LNAS_FUNCTION_LABEL3,
                                      pstPtlTimerList[ulTcbIdxLoop].ulName);

                continue;
            }

            ulRslt = PS_STOP_REL_TIMER(&(pstPtlTimerList[ulTcbIdxLoop].psthTimer));

            /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
            if ( VOS_OK != ulRslt )
            {
                NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopAllPtlTimer, Stop pstPtlTimerList[%d] Failure!",
                                     ulTcbIdxLoop);
                TLPS_PRINT2LAYER_ERROR1(NAS_LMM_SuspendInitStopPtlTimer_ENUM
,LNAS_FUNCTION_LABEL4,
                                     ulTcbIdxLoop);
            }

            pstPtlTimerList[ulTcbIdxLoop].ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
            pstPtlTimerList[ulTcbIdxLoop].ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
        }
    }

    return;
}

/*****************************************************************************
 Function Name   : NAS_LMM_StopAllStateTimer
 Description     : �ڹ���ʱֹͣ��3411�������״̬��ʱ��
 Input           : VOS_VOID
 Output          : None
 Return          : None

 History         :
    1.FTY          2012-02-15  Draft Enact

*****************************************************************************/
VOS_VOID    NAS_LMM_SuspendInitStopStateTimer (VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU            *pstStateTimerList;
    VOS_UINT32                          ulTcbIdxLoop;
    VOS_UINT32                          ulRslt;

    /*��ȡ״̬��ʱ���б��׵�ַ*/
    pstStateTimerList = NAS_LMM_GetStateTimerListAddr();

    /*ֹͣ��STATE_SERVICE_T3442�Լ�STATE_DEL_FORB_TA_PROID�����д�������״̬��Э�鶨ʱ��*/
    for ( ulTcbIdxLoop = TI_NAS_EMM_STATE_NO_TIMER + 1; ulTcbIdxLoop < NAS_LMM_STATE_TI_BUTT; ulTcbIdxLoop++ )
    {
        /*����״̬��ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
          ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
        if ( VOS_NULL_PTR != pstStateTimerList[ulTcbIdxLoop].psthTimer )
        {
            /* ����STATE_SERVICE_T3442�Լ�STATE_DEL_FORB_TA_PROID����ͣ��ʱ���������ж�ʣ�ඨʱ�� */
            if( (TI_NAS_EMM_STATE_SERVICE_T3442 == (pstStateTimerList[ulTcbIdxLoop].ulName))
                || (TI_NAS_EMM_STATE_DEL_FORB_TA_PROID == (pstStateTimerList[ulTcbIdxLoop].ulName)))
            {
                NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_StopAllStateTimerExcept3411. ",
                                      pstStateTimerList[ulTcbIdxLoop].ulName);
                TLPS_PRINT2LAYER_INFO1(NAS_LMM_SuspendInitStopStateTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                      pstStateTimerList[ulTcbIdxLoop].ulName);
                continue;
            }

            ulRslt = PS_STOP_REL_TIMER(&(pstStateTimerList[ulTcbIdxLoop].psthTimer));
            /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
            if ( VOS_OK != ulRslt )
            {
                /* ����ʧ�ܣ���ӡʧ����Ϣ */
                NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopAllStateTimer, Stop pstStateTimerList[%d] Failure!",
                                     ulTcbIdxLoop);
                TLPS_PRINT2LAYER_ERROR1(NAS_LMM_SuspendInitStopStateTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                                     ulTcbIdxLoop);
            }

            pstStateTimerList[ulTcbIdxLoop].ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
            pstStateTimerList[ulTcbIdxLoop].ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
        }
    }

    return;
}
/*****************************************************************************
  3.2 Э�鶨ʱ�� Function
*****************************************************************************/

VOS_VOID    NAS_LMM_StartPtlTimer(
                    NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimer;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulParam;            /* ��ʱ�����ͱ�ʶ */

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);
    /*�޷���ȡ��Э�鶨ʱ�����ƿ��ַ��˵����Э�鶨ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_StartPtlTimer, pstPtlTimer = 0");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_StartPtlTimer_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*����Э�鶨ʱ���Ƿ������У�����������У���ֹͣ��Э�鶨ʱ����
      ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
    if ( VOS_NULL_PTR != pstPtlTimer->psthTimer )
    {
        ulRslt = PS_STOP_REL_TIMER(&(pstPtlTimer->psthTimer));
        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartPtlTimer, Start Ptl Timer Failure!",
                                 enPtlTimerId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StartPtlTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                                 enPtlTimerId);
            return;
        }
    }

    /*��ʱ��ʱ�����ܳ���18Сʱ����Ϊ��*/
    if((TI_NAS_LMM_TIMER_MAX_LEN < pstPtlTimer->ulTimerLen)
    ||(0 == pstPtlTimer->ulTimerLen))
    {
        NAS_LMM_PUBM_LOG2_WARN("NAS_LMM_StartPtlTimer:TimerLen ERR; enPtlTimerId, TimerLength",
                              enPtlTimerId,
                              pstPtlTimer->ulTimerLen);
        TLPS_PRINT2LAYER_WARNING2(NAS_LMM_StartPtlTimer_ENUM
,LNAS_FUNCTION_LABEL3,
                              enPtlTimerId,
                              pstPtlTimer->ulTimerLen);
        return;
    }

    pstPtlTimer->ucTimerType            = NAS_LMM_PTL_TIMER;
    ulParam                             = pstPtlTimer->ucTimerType;

    /*NAS-MMЭ�鶨ʱ���޲�����Ϣ��������ʱ��ʱ����ʱ����������Ϊ0*/
    ulRslt = PS_START_REL_TIMER(&(pstPtlTimer->psthTimer),
                                        PS_PID_MM,
                                        pstPtlTimer->ulTimerLen,
                                        enPtlTimerId,
                                        ulParam,
                                        pstPtlTimer->ucMode);
    /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
    if ( VOS_OK != ulRslt )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartPtlTimer, Start State Timer Failure!",
                             enPtlTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StartPtlTimer_ENUM
,LNAS_FUNCTION_LABEL4,
                             enPtlTimerId);
        return;
    }

    pstPtlTimer->ucTimerRs            = NAS_LMM_TIMER_RS_RUNNING;
    pstPtlTimer->ucTimerSs            = NAS_LMM_TIMER_SS_NOT_SUSPENDING;

    NAS_LMM_PUBM_LOG2_NORM("NAS_LMM_StartPtlTimer OK. PtlTimerId: Timer Len:",
                           enPtlTimerId,pstPtlTimer->ulTimerLen);
    TLPS_PRINT2LAYER_INFO2(NAS_LMM_StartPtlTimer_ENUM
,LNAS_FUNCTION_LABEL5,
                              enPtlTimerId,pstPtlTimer->ulTimerLen);

    /* ��ʱ��״̬�������� */
    NAS_LMM_SndOmEmmTimerStatus(NAS_LMM_TIMER_RUNNING, (VOS_UINT16)enPtlTimerId
                                , pstPtlTimer->ulTimerLen);



    return;
}
VOS_VOID NAS_LMM_Start3402Timer(VOS_UINT8 ucIs161722Atmpt5CsPs1)
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimer;
    NAS_LMM_PTL_TI_ENUM_UINT16            enPtlTimerId = TI_NAS_EMM_PTL_T3402;

    NAS_LMM_StartPtlTimer( enPtlTimerId);

    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, begin */
    NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3402, LMM_MMC_TIMER_START);
    /* mod by yanglei 00307272 for VIA_CL_MT_DETACH_NDIS_COLLISION, 2015-07-21, end */

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);

    pstPtlTimer->ucRsv  = ucIs161722Atmpt5CsPs1;/* [false alarm]:���뱣֤�˲���Ϊ��ָ�� */
}
/*****************************************************************************
 Function Name   : NAS_LMM_Stop3402Timer
 Description     : ֹͣ3402��ʱ��
 Input           :
 Output          : None
 Return          : None

 History         :
    1.yanglei 00307272      2015-07-22 Draft Enact for VIA_CL_MT_DETACH_NDIS_COLLISION
*****************************************************************************/
VOS_VOID NAS_LMM_Stop3402Timer(VOS_VOID)
{
    NAS_LMM_StopPtlTimer( TI_NAS_EMM_PTL_T3402);

    NAS_EMM_SendTimerStateNotify(TI_NAS_EMM_PTL_T3402, LMM_MMC_TIMER_STOP);
}

VOS_UINT32 NAS_LMM_IsNeedStop3402Timer(VOS_VOID)
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimer = VOS_NULL_PTR;
    NAS_LMM_PTL_TI_ENUM_UINT16            enPtlTimerId = TI_NAS_EMM_PTL_T3402;

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);

    /*����״̬��ʱ���Ƿ�������*/
    if ( (VOS_NULL_PTR != pstPtlTimer->psthTimer)
         && (NAS_LMM_TIMER_161722Atmpt5CSPS1_TRUE == pstPtlTimer->ucRsv) )
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }

}





VOS_VOID    NAS_LMM_StopPtlTimer(
                    NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimer;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulTimerRemainLen;

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);
    /*�޷���ȡ��Э�鶨ʱ�����ƿ飬˵����Э�鶨ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopPtlTimer, pstPtlTimer = 0.enPtlTimerId: ",
                             enPtlTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopPtlTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                              enPtlTimerId);
        return;
    }

    /*����Э�鶨ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
      ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
    if ( VOS_NULL_PTR != pstPtlTimer->psthTimer )
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstPtlTimer->psthTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        ulRslt = PS_STOP_REL_TIMER(&(pstPtlTimer->psthTimer));
        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopPtlTimer, Stop Ptl Timer Failure!",
                                 enPtlTimerId);
            TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopPtlTimer_ENUM
,LNAS_FUNCTION_LABEL2,
                              enPtlTimerId);
            return;
        }

        pstPtlTimer->ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
        pstPtlTimer->ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;

        /* ��ʱ��״̬�������� */
        NAS_LMM_SndOmEmmTimerStatus(NAS_LMM_TIMER_STOPED, (VOS_UINT16)enPtlTimerId
                                    , ulTimerRemainLen);


    }

    return;
}
VOS_VOID  NAS_LMM_StartInactivePtlTimer( NAS_LMM_PTL_TI_ENUM_UINT16           enPtlTimerId)
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimer;

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);

    /*�޷���ȡ��Э�鶨ʱ�����ƿ飬˵����Э�鶨ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartInactivePtlTimer, pstPtlTimer = 0.enPtlTimerId: ",
                             enPtlTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StartInactivePtlTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                              enPtlTimerId);
        return;
    }

    /*����Э�鶨ʱ���Ƿ����У����������������*/
    if ( VOS_NULL_PTR == pstPtlTimer->psthTimer )
    {
        NAS_LMM_StartPtlTimer(enPtlTimerId);
    }

    return;
}
VOS_VOID  NAS_LMM_StartInactiveStateTimer( NAS_LMM_STATE_TI_ENUM_UINT16 enStateTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer;

    /*��ȡ��״̬��ʱ�����ƿ��ַ*/
    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);

    /*�޷���ȡ�ö�ʱ�����ƿ��ַ��˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_StartInactiveStateTimer, pstStateTimer = 0");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_StartInactiveStateTimer_ENUM
,LNAS_FUNCTION_LABEL1);
        return;
    }

    /*���״̬��ʱ���Ƿ����У����������������*/
    if ( VOS_NULL_PTR == pstStateTimer->psthTimer )
    {
        NAS_LMM_PUBM_LOG_NORM("NAS_LMM_StartInactiveStateTimer: timer");
        TLPS_PRINT2LAYER_INFO(NAS_LMM_StartInactiveStateTimer_ENUM
,LNAS_FUNCTION_LABEL2);
        NAS_LMM_StartStateTimer(enStateTimerId);
    }

    return;
}
VOS_VOID    NAS_LMM_ModifyPtlTimer(
                    NAS_LMM_PTL_TI_ENUM_UINT16               enPtlTimerId,
                    VOS_UINT32                              ulTimerLen )
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;

    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);

    /*�޷���ȡ��Э�鶨ʱ�����ƿ飬˵����Э�鶨ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_ModifyPtlTimer Error: pstPtlTimer = 0.enPtlTimerId: ",
                             enPtlTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_ModifyPtlTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                             enPtlTimerId);
        return;
    }

    /*�޸� NVIM ʱ���ɹ����޸�ȫ�ֱ���*/
    pstPtlTimer->ulTimerLen           = ulTimerLen;
    pstPtlTimer->ucTimerType          = NAS_LMM_PTL_TIMER;

    /*
    NAS_LMM_PUBM_LOG2_NORM("NAS_LMM_ModifyPtlTimer OK. PtlTimerId, PtlTimerLength",
                          enPtlTimerId,
                          pstPtlTimer->ulTimerLen );
    */

    return;
}

VOS_VOID    NAS_LMM_StopAllPtlTimer( VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimerList;
    VOS_UINT32                          ulTcbIdxLoop;
    VOS_UINT32                          ulRslt;

    /*��ȡ״̬��ʱ���б��׵�ַ*/
    pstPtlTimerList = NAS_LMM_GetPtlTimerListAddr();

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for ( ulTcbIdxLoop = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START +1; ulTcbIdxLoop < NAS_LMM_PTL_TI_BUTT; ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
          ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
        if ( VOS_NULL_PTR != pstPtlTimerList[ulTcbIdxLoop].psthTimer )
        {
            ulRslt = PS_STOP_REL_TIMER(&(pstPtlTimerList[ulTcbIdxLoop].psthTimer));

            /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
            if ( VOS_OK != ulRslt )
            {
                NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopAllPtlTimer, Stop pstPtlTimerList[%d] Failure!",
                                     ulTcbIdxLoop);
                TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopAllPtlTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                     ulTcbIdxLoop);
            }

            pstPtlTimerList[ulTcbIdxLoop].ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
            pstPtlTimerList[ulTcbIdxLoop].ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
        }
    }

   return;
}



/*****************************************************************************
  3.3 ��ʱ�� Function
*****************************************************************************/

VOS_VOID    NAS_LMM_InitAllStateTimer( VOS_VOID )
{

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_InitAllStateTimer          START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_InitAllStateTimer_ENUM
,LNAS_BEGIN);

    /*T3440*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_STATE_T3440,
                                        NAS_LMM_TIMER_T3440_LEN);
    /*PUBM*/
    /*USIM*/
    NAS_LMM_InitStateTimer(              TI_NAS_LMM_TIMER_WAIT_USIM_CNF,
                                        NAS_LMM_TIMER_WAIT_USIM_CNF_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_LMM_TIMER_WAIT_USIM_READY_START,
                                        NAS_LMM_TIMER_WAIT_USIM_READY_START_LEN);
    /*MRRC*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_MRRC_WAIT_RRC_CONN_CNF,
                                        NAS_LMM_TIMER_MRRC_WAIT_RRC_CONN_CNF_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_MRRC_WAIT_RRC_REL_CNF,
                                        NAS_LMM_TIMER_MRRC_WAIT_RRC_REL_CNF_LEN);
    /*ATTACH*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_T3410,
                                        NAS_LMM_TIMER_ATTACH_T3410_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_ESM_PDN_RSP,
                                        NAS_LMM_TIMER_ATTACH_WAIT_ESM_PDN_RSP_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_ESM_BEARER_CNF,
                                        NAS_LMM_TIMER_ATTACH_WAIT_ESM_BEARER_CNF_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_RRC_DATA_CNF,
                                        NAS_LMM_TIMER_WAIT_RRC_DATA_CNF_LEN);
    /*DETACH*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_T3421,
                                        NAS_LMM_TIMER_DETACH_T3421_LEN);

    /*TAU*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_STATE_TAU_T3430,
                                        NAS_LMM_TIMER_TAU_T3430);

    /*SER*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_STATE_SERVICE_T3417,
                                        NAS_LMM_TIMER_SER_T3417_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_STATE_SERVICE_T3442,
                                        NAS_EMM_NULL);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_STATE_SERVICE_T3417_EXT,
                                        NAS_LMM_TIMER_SER_T3417_EXT_LEN);

    /*PLMN*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_MMC_START_CNF_TIMER,
                                        NAS_LMM_TIMER_PLMN_WAIT_MMC_START_CNF_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_RRC_START_CNF_TIMER,
                                        NAS_LMM_TIMER_PLMN_WAIT_RRC_START_CNF_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_MMC_STOP_CNF_TIMER,
                                        NAS_LMM_TIMER_PLMN_WAIT_MMC_STOP_CNF_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_RRC_STOP_CNF_TIMER,
                                        NAS_LMM_TIMER_PLMN_WAIT_RRC_STOP_CNF_LEN);

    /*AUTH*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_T3418,
                                        NAS_LMM_TIMER_AUTH_T3418_LEN);
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_T3420,
                                        NAS_LMM_TIMER_AUTH_T3420_LEN);
    /*MMC*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_STATE_DEL_FORB_TA_PROID,
                                        NAS_LMM_TIMER_EMM_DEL_FORB_TA_PRIOD_LEN);
    /*SUSPEND RESUME */
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_RRCORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
                                        NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_SUSPEND_END_TIMER,
                                        NAS_LMM_TIMER_SUSPEND_WAIT_END_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_MMCORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
                                        NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_SYSCFGORI_WAIT_OTHER_SUSPEND_RSP_TIMER,
                                        NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_RRCRSM_WAIT_OTHER_RESUME_RSP_TIMER,
                                        NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_SYSCFGRSM_WAIT_OTHER_RESUME_RSP_TIMER,
                                        NAS_LMM_TIMER_SUSPEND_RESUME_WAIT_LEN);

    /*��ϵͳ�任��ʱ��L->GU->L�����ĳ������ص�L��ʱ����Ҫ��������ʱ�᳤��15s,
      ����LNAS�ȴ�ϵͳ��ʱ�䳬ʱ�Ķ�ʱ����ǰֻ��5s�������ӳ��ȴ�ʱ�䵽20s*/
    NAS_LMM_InitStateTimer(              TI_NAS_EMM_WAIT_SYS_INFO_IND_TIMER,
                                        NAS_LMM_TIMER_WAIT_SYS_INFO_IND_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMM_STATE_WAIT_SYSCFG_CNF_TIMER,
                                        NAS_LMM_TIMER_SYSCFG_CNF_WAIT_LEN);

    NAS_LMM_InitStateTimer(              TI_NAS_EMMC_STATE_WAIT_PLMN_SRCH_CNF_TIMER,
                                        NAS_LMM_TIMER_PLMN_SRCH_CNF_WAIT_LEN);

    return;
}


VOS_VOID    NAS_LMM_InitStateTimer(
                    NAS_LMM_STATE_TI_ENUM_UINT16             enStateTimerId,
                    VOS_UINT32                              ulTimerLen )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer;

    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);

    /*�޷���ȡ�ö�ʱ�����ƿ飬˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_InitStateTimer, pstStateTimer = 0.enStateTimerId: ",
                             enStateTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_InitStateTimer_ENUM
,LNAS_NULL_PTR,
                             enStateTimerId  );
        return;
    }

    pstStateTimer->ulName               = enStateTimerId;
    pstStateTimer->ulTimerLen           = ulTimerLen;
    pstStateTimer->psthTimer            = VOS_NULL_PTR;
    pstStateTimer->ulParam              = NAS_LMM_TIMER_NOT_CARE;
    pstStateTimer->ulTimerRemainLen     = NAS_LMM_TIMER_ZERO_VALUE;
    pstStateTimer->ucMaxNum             = NAS_LMM_TIMER_NOT_CARE;
    pstStateTimer->ucExpedNum           = NAS_LMM_TIMER_ZERO_VALUE;
    pstStateTimer->ucMode               = VOS_RELTIMER_NOLOOP;
    pstStateTimer->ucTimerType          = NAS_LMM_STATE_TIMER;
    pstStateTimer->ucTimerRs            = NAS_LMM_TIMER_RS_NOT_RUNNING;
    pstStateTimer->ucTimerSs            = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
    pstStateTimer->ucTimerVs            = NAS_LMM_TIMER_VS_NOT_NEED_TO_UPDATE;

    return;

}
VOS_VOID    NAS_LMM_InitAllPtlTimer( VOS_VOID )
{

    NAS_LMM_PUBM_LOG_NORM("NAS_LMM_InitAllPtlTimer            START INIT...");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_InitAllPtlTimer_ENUM
,LNAS_BEGIN );

    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_T3412,
                                    NAS_LMM_TIMER_T3412_LEN);
    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_T3402,
                                    NAS_LMM_TIMER_T3402_LEN);
    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_T3423,
                                    NAS_LMM_TIMER_T3423_LEN);
    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_T3416,
                                    NAS_LMM_TIMER_AUTH_T3416_LEN);
    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_SWITCH_OFF_TIMER,
                                    NAS_LMM_TIMER_DETACH_SWITCH_OFF_LEN);
    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_REATTACH_DELAY,
                                     NAS_LMM_TIMER_REATTACH_DELAY_LEN);
    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_T3411,
                                     NAS_LMM_TIMER_T3411_LEN);

    NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_CSFB_DELAY,
                                     NAS_LMM_TIMER_CSFB_DELAY_LEN);

     NAS_LMM_InitPtlTimer(            TI_NAS_EMM_PTL_T3346,
                                     NAS_LMM_TIMER_T3346_LEN);

    return;
}


VOS_VOID    NAS_LMM_InitPtlTimer(
                    NAS_LMM_PTL_TI_ENUM_UINT16             enPtlTimerId,
                    VOS_UINT32                            ulTimerLen )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimer;

    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);

    /*�޷���ȡ�ö�ʱ�����ƿ飬˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_InitPtlimer, pstPtlTimer = 0.enPtlTimerId: ",
                             enPtlTimerId);
        TLPS_PRINT2LAYER_ERROR1(NAS_LMM_InitPtlTimer_ENUM
,LNAS_NULL_PTR,
                             enPtlTimerId);
        return;
    }

    pstPtlTimer->ulName               = enPtlTimerId;
    pstPtlTimer->ulTimerLen           = ulTimerLen;
    pstPtlTimer->psthTimer            = VOS_NULL_PTR;
    pstPtlTimer->ulParam              = NAS_LMM_TIMER_NOT_CARE;
    pstPtlTimer->ulTimerRemainLen     = NAS_LMM_TIMER_ZERO_VALUE;
    pstPtlTimer->ucMaxNum             = NAS_LMM_TIMER_NOT_CARE;
    pstPtlTimer->ucExpedNum           = NAS_LMM_TIMER_ZERO_VALUE;

    pstPtlTimer->ucTimerType          = NAS_LMM_PTL_TIMER;
    pstPtlTimer->ucTimerRs            = NAS_LMM_TIMER_RS_NOT_RUNNING;
    pstPtlTimer->ucTimerSs            = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
    pstPtlTimer->ucTimerVs            = NAS_LMM_TIMER_VS_NOT_NEED_TO_UPDATE;
    pstPtlTimer->ucMode               = VOS_RELTIMER_NOLOOP;
    return;

}
VOS_VOID  NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer(VOS_VOID)
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimerList;
    VOS_UINT32                          ulTcbIdxLoop;
    VOS_UINT32                          ulRslt;
    VOS_BOOL                            bFlag               = VOS_TRUE;

    NAS_LMM_PUBM_LOG_INFO("NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer");
    TLPS_PRINT2LAYER_INFO(NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer_ENUM,LNAS_ENTRY);

    /*��ȡ״̬��ʱ���б��׵�ַ*/
    pstStateTimerList = NAS_LMM_GetStateTimerListAddr();

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for ( ulTcbIdxLoop = TI_NAS_EMM_STATE_NO_TIMER + 1; ulTcbIdxLoop < TI_NAS_EMM_STATE_TI_BUTT; ulTcbIdxLoop++ )
    {
        /* Del Forb Ta Proidֻ���ڹػ�ʱ����ֹͣ,���Դ˴�����Del Forb Ta Proid��ʱ��:
            �����ʱ����ֹͣ, ����Forb Ta�б��е�TA�޷����޳�,�Ӷ�����TAһֱ������ */
        if (TI_NAS_EMM_STATE_DEL_FORB_TA_PROID == ulTcbIdxLoop)
        {
            continue;
        }

        /*����״̬��ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
          ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
        if ( VOS_NULL_PTR != pstStateTimerList[ulTcbIdxLoop].psthTimer )
        {
            ulRslt = PS_STOP_REL_TIMER(&(pstStateTimerList[ulTcbIdxLoop].psthTimer));
            /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
            if ( VOS_OK != ulRslt )
            {
                bFlag = VOS_FALSE;
                /* ����ʧ�ܣ���ӡʧ����Ϣ */
                NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer, Stop pstStateTimerList[%d] Failure!",
                                     ulTcbIdxLoop);
                TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer_ENUM,
                                        LNAS_FUNCTION_LABEL1,
                                        ulTcbIdxLoop);
            }
            pstStateTimerList[ulTcbIdxLoop].ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
            pstStateTimerList[ulTcbIdxLoop].ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
        }
    }

    NAS_LMM_PUBM_LOG1_INFO("NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer: bFlag =", bFlag);
    TLPS_PRINT2LAYER_INFO1(NAS_LMM_StopAllStateTimerExceptDelForbTaProidTimer_ENUM,
                                 LNAS_FUNCTION_LABEL2,
                                 bFlag);

    return;

}



VOS_VOID    NAS_LMM_StopAllEmmPtlTimer( VOS_VOID )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimerList;
    VOS_UINT32                          ulTcbIdxLoop;
    VOS_UINT32                          ulRslt;

    /*��ȡ״̬��ʱ���б��׵�ַ*/
    pstPtlTimerList = NAS_LMM_GetPtlTimerListAddr();

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for (   ulTcbIdxLoop = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START +1;
            ulTcbIdxLoop < TI_NAS_EMM_PTL_TI_BUTT;
            ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
          ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
        if ( VOS_NULL_PTR != pstPtlTimerList[ulTcbIdxLoop].psthTimer )
        {
            ulRslt = PS_STOP_REL_TIMER(&(pstPtlTimerList[ulTcbIdxLoop].psthTimer));

            /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
            if ( VOS_OK != ulRslt )
            {
                NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopAllEmmPtlTimer, Stop pstPtlTimerList[%d] Failure!",
                                     ulTcbIdxLoop);
                TLPS_PRINT2LAYER_ERROR1(NAS_LMM_StopAllEmmPtlTimer_ENUM
,LNAS_FUNCTION_LABEL1,
                                     ulTcbIdxLoop);
            }

            pstPtlTimerList[ulTcbIdxLoop].ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
            pstPtlTimerList[ulTcbIdxLoop].ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;
        }
    }

   return;
}

/* ɾ�����ú��� */
/*****************************************************************************
 Function Name   : NAS_LMM_StopAllEmmPtlTimer
 Description     : �ڹ���ʱֹͣEMM��ʱ��
 Input           : VOS_VOID
 Output          : None
 Return          : None

 History         :
    1.FTY         2012-02-21 Draft Enact
*****************************************************************************/
VOS_VOID    NAS_LMM_SuspendInitStopLmmTimer( VOS_VOID )
{
    /* ֹͣ״̬��ʱ�� */
    NAS_LMM_SuspendInitStopStateTimer();

    /* ֹͣЭ�鶨ʱ�� */
    NAS_LMM_SuspendInitStopPtlTimer();
}


VOS_VOID  NAS_LMM_GetStateTimerLen( NAS_LMM_STATE_TI_ENUM_UINT16   enStateTimerId,
                                   VOS_UINT32   *pulTimerLen)
{
    NAS_LMM_TIMER_CTRL_STRU             *pstStateTimer = VOS_NULL_PTR;


    /*��ȡ��״̬��ʱ�����ƿ��ַ*/
    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);
    /*�޷���ȡ�ö�ʱ�����ƿ��ַ��˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetStateTimerLen, pstStateTimer��Ч");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetStateTimerLen_ENUM
,LNAS_NULL_PTR);
        *pulTimerLen = 0;
        return;
    }

    /*��ȡ��ʱ��ʱ��*/
    *pulTimerLen = pstStateTimer->ulTimerLen;
}
VOS_VOID  NAS_LMM_GetPtlTimerLen( NAS_LMM_PTL_TI_ENUM_UINT16   enPtlTimerId,
                                   VOS_UINT32   *pulTimerLen)
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer = VOS_NULL_PTR;


    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);
    /*�޷���ȡ�ö�ʱ�����ƿ��ַ��˵����ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_GetPtlTimerLen, pstPtlTimer��Ч");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_GetPtlTimerLen_ENUM
,LNAS_NULL_PTR);
        *pulTimerLen = 0;
        return;
    }

    /*��ȡ��ʱ��ʱ��*/
    *pulTimerLen = pstPtlTimer->ulTimerLen;
}
NAS_LMM_TIMER_RUN_STA_ENUM_UINT32  NAS_LMM_IsStaTimerRunning(
                                    NAS_LMM_STATE_TI_ENUM_UINT16 enStateTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstStateTimer = VOS_NULL_PTR;

    /*��ȡ��״̬��ʱ�����ƿ��ַ*/
    pstStateTimer = NAS_LMM_GetStateTimerAddr(enStateTimerId);
    if ( VOS_NULL_PTR == pstStateTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsStaTimerRunning: pstStateTimer NULL.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsStaTimerRunning_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_TIMER_INVALID;
    }

    /*����״̬��ʱ���Ƿ�������*/
    if ( VOS_NULL_PTR != pstStateTimer->psthTimer )
    {
        return NAS_LMM_TIMER_RUNNING;
    }
    else
    {
        return NAS_LMM_TIMER_STOPED;
    }
}


NAS_LMM_TIMER_RUN_STA_ENUM_UINT32  NAS_LMM_IsPtlTimerRunning(
                                    NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId )
{
    NAS_LMM_TIMER_CTRL_STRU              *pstPtlTimer = VOS_NULL_PTR;

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetPtlTimerAddr(enPtlTimerId);
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsPtlTimerRunning: pstPtlTimer NULL.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_IsPtlTimerRunning_ENUM
,LNAS_NULL_PTR);
        return NAS_LMM_TIMER_INVALID;
    }

    /*����״̬��ʱ���Ƿ�������*/
    if ( VOS_NULL_PTR != pstPtlTimer->psthTimer )
    {
        return NAS_LMM_TIMER_RUNNING;
    }
    else
    {
        return NAS_LMM_TIMER_STOPED;
    }
}

VOS_VOID    NAS_LMM_SuspendAllPtlTimer( VOS_VOID )
{
    VOS_UINT32                          ulTcbIdxLoop;

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for ( ulTcbIdxLoop = TI_NAS_EMM_STATE_NO_TIMER + 1; ulTcbIdxLoop < TI_NAS_EMM_STATE_TI_BUTT; ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ������У�����������У�����ö�ʱ��*/
        NAS_LMM_SuspendStateTimer((NAS_LMM_STATE_TI_ENUM_UINT16) ulTcbIdxLoop);
    }
    for (   ulTcbIdxLoop = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START +1;
            ulTcbIdxLoop < TI_NAS_EMM_PTL_TI_BUTT;
            ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ������У�����������У�����ö�ʱ��*/
        NAS_LMM_SuspendStateTimer((NAS_LMM_STATE_TI_ENUM_UINT16) ulTcbIdxLoop);
    }

   return;
}
VOS_VOID    NAS_LMM_SuspendAllPtlTimerExpT3412( VOS_VOID )
{
    VOS_UINT32                          ulTcbIdxLoop;

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for ( ulTcbIdxLoop = TI_NAS_EMM_STATE_NO_TIMER + 1; ulTcbIdxLoop < TI_NAS_EMM_STATE_TI_BUTT; ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ������У�����������У�����ö�ʱ��*/
        NAS_LMM_SuspendStateTimer((NAS_LMM_STATE_TI_ENUM_UINT16) ulTcbIdxLoop);
    }
    for (   ulTcbIdxLoop = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START +1;
            ulTcbIdxLoop < TI_NAS_EMM_PTL_TI_BUTT;
            ulTcbIdxLoop++ )
    {
        if(ulTcbIdxLoop == TI_NAS_EMM_PTL_T3412)
        {
            continue;
        }
        /*����Э�鶨ʱ���Ƿ������У�����������У�����ö�ʱ��*/
        NAS_LMM_SuspendStateTimer( (NAS_LMM_STATE_TI_ENUM_UINT16)ulTcbIdxLoop);
    }

   return;
}
VOS_VOID    NAS_LMM_ResumeAllPtlTimer( VOS_VOID )
{
    VOS_UINT32                          ulTcbIdxLoop;

    /*ֹͣ���д�������״̬��Э�鶨ʱ��*/
    for ( ulTcbIdxLoop = TI_NAS_EMM_STATE_NO_TIMER + 1; ulTcbIdxLoop < TI_NAS_EMM_STATE_TI_BUTT; ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ����������ڹ��𣬻ָ��ö�ʱ��*/
        NAS_LMM_ResumeStateTimer((NAS_LMM_STATE_TI_ENUM_UINT16) ulTcbIdxLoop);
    }
    for (   ulTcbIdxLoop = TI_NAS_LMM_PTL_TI_PUB_BOUNDARY_START +1;
            ulTcbIdxLoop < TI_NAS_EMM_PTL_TI_BUTT;
            ulTcbIdxLoop++ )
    {
        /*����Э�鶨ʱ���Ƿ����������ڹ��𣬻ָ��ö�ʱ��*/
        NAS_LMM_ResumeStateTimer((NAS_LMM_STATE_TI_ENUM_UINT16)ulTcbIdxLoop);
    }

   return;
}
VOS_VOID    NAS_LMM_StopAllAttachTimer( VOS_VOID )
{
    NAS_LMM_StopStateTimer( TI_NAS_EMM_WAIT_ESM_PDN_RSP);

    NAS_LMM_StopStateTimer( TI_NAS_EMM_T3410);

    NAS_LMM_StopStateTimer( TI_NAS_EMM_WAIT_ESM_BEARER_CNF);

    NAS_LMM_StopStateTimer( TI_NAS_EMM_WAIT_RRC_DATA_CNF);
}


VOS_VOID  NAS_LMM_SndOmEmmTimerStatus(
    NAS_LMM_TIMER_RUN_STA_ENUM_UINT32          enTimerStatus,
    VOS_UINT16                          enTimerId,
    VOS_UINT32                          ulTimerRemainLen
)
{
    NAS_EMM_TIMER_INFO_STRU            *pstMsg = VOS_NULL_PTR;

    pstMsg = (NAS_EMM_TIMER_INFO_STRU*)NAS_LMM_MEM_ALLOC(sizeof(NAS_EMM_TIMER_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_SndOmEmmTimerStatus: mem alloc fail!.");
        TLPS_PRINT2LAYER_ERROR(NAS_LMM_SndOmEmmTimerStatus_ENUM
,LNAS_NULL_PTR);
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = PS_PID_MM;
    pstMsg->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstMsg->stMsgHeader.ulLength        = sizeof(NAS_EMM_TIMER_INFO_STRU) - NAS_EMM_LEN_VOS_MSG_HEADER;

    pstMsg->stMsgHeader.ulMsgName       = enTimerId + PS_MSG_ID_EMM_TO_EMM_OM_BASE;
    pstMsg->enTimerStatus               = enTimerStatus;
    pstMsg->usTimerId                   = enTimerId;
    pstMsg->usRsv                       = 0;

    pstMsg->ulTimerRemainLen            = ulTimerRemainLen;

    (VOS_VOID)LTE_MsgHook((VOS_VOID*)pstMsg);

    NAS_LMM_MEM_FREE(pstMsg);

}

NAS_LMM_TIMER_CTRL_STRU *NAS_LMM_GetGradualForbidenTimer(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId)
{
    NAS_LMM_TIMER_CTRL_STRU         *pstTimerInfo = VOS_NULL_PTR;

    /* ����TimerId��ulIndex���Ҷ�ʱ��ά���ṹ��ַ */
    switch(enPtlTimerId)
    {
        case TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER:

            pstTimerInfo = &g_stGradualForbTempForbTaList.astGradualForbTa[ulIndex].stGradualForbTimer;
            break;
        case TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER:

            pstTimerInfo = &g_stGradualForbTempForbTaList.astGradualForbTa[ulIndex].stGradualForbAgingTimer;
            break;
        default :
            break;
    }
    return pstTimerInfo;
}
VOS_UINT32  NAS_LMM_IsGradualForbiddenTimerNameValid
(
    VOS_UINT32                          ulIndex,
    NAS_LMM_PTL_TI_ENUM_UINT16          enPtlTimerId
)
{
    VOS_UINT32          ulRslt  = PS_FALSE;

    /* �ж�ulIndex�Ƿ�Ϸ� */
    if(ulIndex >= NAS_LMM_GRADUAL_FORB_MAX_TEMP_TA_NUM)
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_IsGradualForbiddenTimerNameValid Fail ulIndex = ", ulIndex);
        return PS_FALSE;
    }

    /* �ж϶�ʱ��ID�Ƿ�Ϸ� */
    switch(enPtlTimerId)
    {
        case TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER:
        case TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER:
            ulRslt = PS_TRUE;
            break;
        default :
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_IsGradualForbiddenTimerNameValid Fail enPtlTimerId = ", enPtlTimerId);
            break;
    }
    return ulRslt;
}

VOS_UINT32 NAS_LMM_GetGradualForbiddenTimerLen(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId)
{
    VOS_UINT32                               ulTimerLen  = 0;
    NAS_LMM_GRADUAL_FORB_TEMP_FORB_TA_LIST   *pstTempForbTaList = VOS_NULL_PTR;
    VOS_UINT32                               ulRejTimes = 0;
    switch(enPtlTimerId)
    {
        case TI_NAS_EMM_PTL_GRADUAL_FORB_TIMER:

            pstTempForbTaList = NAS_LMM_GetGradualForbTempForbTaListAddr();
            ulRejTimes        = pstTempForbTaList->astGradualForbTa[ulIndex].uc15RejTimes;
            if(NAS_LMM_GRADUAL_FORB_REJ_FIRST == ulRejTimes)
            {
                ulTimerLen    = g_ulGradualForbTimerFirstLen;
            }
            else if(NAS_LMM_GRADUAL_FORB_REJ_SECOND == ulRejTimes)
            {
                ulTimerLen    = g_ulGradualForbTimerSecondLen;
            }
            else
            {
                NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_GetGradualForbTimerLen Fail ulRejTimes = ", ulRejTimes);
            }
            break;
        case TI_NAS_EMM_PTL_GRADUAL_FORB_AGING_TIMER:

            ulTimerLen = g_ulGradualForbAgingTimerLen;
            break;
        default :
            break;
    }
    return ulTimerLen;

}

VOS_VOID NAS_LMM_StartGradualForbiddenTimer(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16 enPtlTimerId, VOS_UINT32 ulTimerPara)
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulTimerLen;

    /* �ж�����Ƿ�Ϸ� */
    if ( PS_FALSE == NAS_LMM_IsGradualForbiddenTimerNameValid(ulIndex, enPtlTimerId) )
    {
        return;
    }

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetGradualForbidenTimer(ulIndex, enPtlTimerId);

    /*�޷���ȡ��Э�鶨ʱ�����ƿ��ַ��˵����Э�鶨ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_StartGradualForbTimer, pstPtlTimer = 0");
        return;
    }

    /*����Э�鶨ʱ���Ƿ������У�����������У���ֹͣ��Э�鶨ʱ����
      ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
    if ( VOS_NULL_PTR != pstPtlTimer->psthTimer )
    {
        ulRslt = PS_STOP_REL_TIMER(&(pstPtlTimer->psthTimer));

        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartGradualForbTimer, Start Ptl Timer Failure!",
                                 enPtlTimerId);
            return;
        }
    }
    /* ��ȡ��ʱ������ */
    ulTimerLen = NAS_LMM_GetGradualForbiddenTimerLen(ulIndex, enPtlTimerId);

    /*��ʱ��ʱ�����ܳ���18Сʱ����Ϊ��*/
    if ( (TI_NAS_LMM_TIMER_MAX_LEN < ulTimerLen) || (0 == ulTimerLen) )
    {
        NAS_LMM_PUBM_LOG2_WARN("NAS_LMM_StartGradualForbTimer:TimerLen ERR; enPtlTimerId, TimerLength",
                              enPtlTimerId,
                              ulTimerLen);
        return;
    }

    pstPtlTimer->ucTimerType            = NAS_LMM_PTL_TIMER;

    /*NAS-MMЭ�鶨ʱ���޲�����Ϣ��������ʱ��ʱ����ʱ����������Ϊ0*/
    ulRslt = PS_START_REL_TIMER(&(pstPtlTimer->psthTimer),
                                        PS_PID_MM,
                                        ulTimerLen,
                                        enPtlTimerId,
                                        ulTimerPara,
                                        VOS_RELTIMER_NOLOOP);

    /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
    if ( VOS_OK != ulRslt )
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartGradualForbTimer, Start State Timer Failure!",
                             enPtlTimerId);
        return;
    }

    pstPtlTimer->ucTimerRs            = NAS_LMM_TIMER_RS_RUNNING;
    pstPtlTimer->ucTimerSs            = NAS_LMM_TIMER_SS_NOT_SUSPENDING;

    NAS_LMM_PUBM_LOG2_NORM("NAS_LMM_StartGradualForbTimer OK. PtlTimerId: Timer Len:",
                           enPtlTimerId, ulTimerLen);

    /* ��ʱ��״̬�������� */
    NAS_LMM_SndOmEmmTimerStatus(NAS_LMM_TIMER_RUNNING, (VOS_UINT16)enPtlTimerId
                                , ulTimerLen);
    return;
}

VOS_VOID  NAS_LMM_StopGradualForbiddenTimer(VOS_UINT32 ulIndex, NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId)
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;
    VOS_UINT32                          ulRslt;
    VOS_UINT32                          ulTimerRemainLen;

    /* �ж�����Ƿ�Ϸ� */
    if(PS_FALSE == NAS_LMM_IsGradualForbiddenTimerNameValid(ulIndex, enPtlTimerId))
    {
        NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StartGradualForbTimer ulIndex = ", ulIndex);
        return;
    }

    /*��ȡ��Э�鶨ʱ�����ƿ��ַ*/
    pstPtlTimer = NAS_LMM_GetGradualForbidenTimer(ulIndex, enPtlTimerId);

    /*�޷���ȡ��Э�鶨ʱ�����ƿ��ַ��˵����Э�鶨ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_StopGradualForbTimer, pstPtlTimer = 0");
        return;
    }

    /*����Э�鶨ʱ���Ƿ������У�����������У�ֹͣ�ö�ʱ����
      ֹͣ��ʱ��ʱ��VOS��ֱ�ӽ��ö�ʱ��������ΪVOS_NULL_PTR*/
    if ( VOS_NULL_PTR != pstPtlTimer->psthTimer )
    {
        /* ��ȡ��ǰ��ʱ����ʣ��ʱ�� */
        if (VOS_OK != VOS_GetRelTmRemainTime(&(pstPtlTimer->psthTimer), &ulTimerRemainLen ))
        {
            ulTimerRemainLen = 0;
        }

        ulRslt = PS_STOP_REL_TIMER(&(pstPtlTimer->psthTimer));

        /*������õ���VOS�Ľӿں����������Ҫʹ��VOS�ķ���ֵ���м��*/
        if ( VOS_OK != ulRslt )
        {
            NAS_LMM_PUBM_LOG1_ERR("NAS_LMM_StopPtlTimer, Stop Ptl Timer Failure!",
                                 enPtlTimerId);
            return;
        }

        pstPtlTimer->ucTimerRs = NAS_LMM_TIMER_RS_NOT_RUNNING;
        pstPtlTimer->ucTimerSs = NAS_LMM_TIMER_SS_NOT_SUSPENDING;

        /* ��ʱ��״̬�������� */
        NAS_LMM_SndOmEmmTimerStatus(NAS_LMM_TIMER_STOPED, (VOS_UINT16)enPtlTimerId
                                    , ulTimerRemainLen);
    }
    return;
}
NAS_LMM_TIMER_RUN_STA_ENUM_UINT32 NAS_LMM_IsGradualForbiddenTimerRunning(VOS_UINT32 ulIndex,
                                                                        NAS_LMM_PTL_TI_ENUM_UINT16  enPtlTimerId)
{
    NAS_LMM_TIMER_CTRL_STRU             *pstPtlTimer;

    /* �ж�����Ƿ�Ϸ� */
    if (PS_FALSE == NAS_LMM_IsGradualForbiddenTimerNameValid(ulIndex, enPtlTimerId))
    {
        return NAS_LMM_TIMER_STOPED;
    }
    pstPtlTimer = NAS_LMM_GetGradualForbidenTimer(ulIndex, enPtlTimerId);

    /*�޷���ȡ��Э�鶨ʱ�����ƿ��ַ��˵����Э�鶨ʱ��ID�Ƿ�*/
    if ( VOS_NULL_PTR == pstPtlTimer )
    {
        NAS_LMM_PUBM_LOG_ERR("NAS_LMM_IsGradualForbiddenTimerRunning, pstPtlTimer = 0");
        return NAS_LMM_TIMER_STOPED;
    }

    /* ��ʱ�����Ϊ��˵����ʱ���Ѿ�ֹͣ */
    if ( VOS_NULL_PTR == pstPtlTimer->psthTimer )
    {
        return NAS_LMM_TIMER_STOPED;
    }

    return NAS_LMM_TIMER_RUNNING;
}
/*lint +e961*/
/*lint +e960*/


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

