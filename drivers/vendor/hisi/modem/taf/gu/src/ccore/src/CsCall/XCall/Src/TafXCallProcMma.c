


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallProcMma.h"
#include "TafXCallCtx.h"
#include "TafXCallSndApp.h"
#include "TafXCallSndMma.h"
#include "TafXCallProcUsim.h"
#include "TafXCallSndXcc.h"
#include "TafSdcCtx.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-15, begin */
#include "TafMmaSndOm.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-15, end */
#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_MMA_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID TAF_XCALL_ResetAllCalls(VOS_VOID)
{
    VOS_UINT32                                              ulNumOfCalls;
    VOS_UINT8                                               aucCallIds[TAF_XCALL_CALL_ENTITY_MAX_NUM];
    VOS_UINT32                                              ulModuleId;
    VOS_UINT8                                               i;
    TAF_XCALL_SS_PROGRESS_EVT_ENUM_UINT8                    enEvt;
    TAF_XCALL_SS_SUBSEQ_OP_ENUM_UINT8                       enSubseqOp;
    TAF_XCALL_CALL_ENTITY_STRU                             *pstCallEntity = VOS_NULL_PTR;
    VOS_UINT16                                              usClientId;
    MN_CALL_TYPE_ENUM_U8                                    enCallType;

    enEvt        = TAF_XCALL_SS_PROG_EVT_BUTT;
    enSubseqOp   = TAF_XCALL_SS_SUBSEQ_OP_BUTT;

    ulNumOfCalls = 0;

    PS_MEM_SET(aucCallIds, 0, sizeof(aucCallIds));

    TAF_XCALL_GetNotIdleStateCalls(&ulNumOfCalls, aucCallIds);

    if (0 == ulNumOfCalls)
    {
        return;
    }

    /* ���浱ǰcall id��module id������release all�ϱ� */
    ulModuleId = TAF_XCALL_GetClientInfo(aucCallIds[0])->ulModuleId;

    /* ��ػ�ʱ��Ҫ�жϵ�ǰ�Ƿ��з�IDLE̬�ĺ��У��������Ҫ�ϱ�MN_CALL_EVT_RELEASED�¼� */
    for (i = 0; i < TAF_XCALL_MIN(ulNumOfCalls, TAF_XCALL_CALL_ENTITY_MAX_NUM); i++)
    {
        /* ��¼�����Ҷϵ�ԭ��ֵ */
        TAF_XCALL_UpdateCcCause(aucCallIds[i], TAF_CS_CAUSE_XCALL_POWER_DOWN_IND);

        /* ��MMA����TAF_MMA_1X_CALL_END_NTF��Ϣ */
        pstCallEntity       = TAF_XCALL_GetCallEntityAddr(aucCallIds[i]);
        usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
        enCallType          = TAF_XCALL_GetCallType(aucCallIds[i]);

        if (MN_CALL_DIR_MO == TAF_XCALL_GetCallDir(aucCallIds[i]))
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));
        }

        /* ���б���ֹͣ����ز���ʱ�� */
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, aucCallIds[i]);
        TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, aucCallIds[i]);

        /* ��APP�ϱ�MN_CALL_EVT_RELEASED�¼� */
        TAF_XCALL_SndCallReleaseInd(aucCallIds[i]);


        TAF_XCALL_GetSsKeyEvent(aucCallIds[i], &enEvt, &enSubseqOp);

        /* ������ڹҶϹ����У�����Ҷϣ���APP�ظ��Ҷϳɹ� */
        if (TAF_XCALL_SS_PROG_EVT_REL == enEvt)
        {
            /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
            TAF_XCALL_SndSupsResult(TAF_XCALL_GetClientInfo(aucCallIds[i])->ulModuleId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->usClientId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->ucOpId,
                                    aucCallIds[i], MN_CALL_SS_RES_SUCCESS);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_REL);
        }

        /* ������ڽ��������У�����Ҷϣ���APP�ظ�����ʧ�� */
        if (TAF_XCALL_SS_PROG_EVT_ANS == enEvt)
        {
            /* ��APP�ظ�MN_CALL_EVT_SS_CMD_RSLT�¼� */
            TAF_XCALL_SndSupsResult(TAF_XCALL_GetClientInfo(aucCallIds[i])->ulModuleId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->usClientId,
                                    TAF_XCALL_GetClientInfo(aucCallIds[i])->ucOpId,
                                    aucCallIds[i], MN_CALL_SS_RES_FAIL);

            TAF_XCALL_DeRegSsKeyEvent(aucCallIds[i], TAF_XCALL_SS_PROG_EVT_ANS);
        }
    }

    /* ��APP�ϱ�MN_CALL_EVT_ALL_RELEASED�¼� */
    TAF_XCALL_SndCallAllReleaseInd(ulModuleId);

}
VOS_VOID TAF_XCALL_RcvMmaPowerOffInd(VOS_VOID *pMsg)
{
    /* �������к��� */
    TAF_XCALL_ResetAllCalls();

    /* �����ĳ�ʼ�� */
    TAF_XCALL_InitCtx();

}



VOS_VOID TAF_XCALL_RcvMmaPowerOnInd(VOS_VOID *pMsg)
{
    /* 6F47�ļ�,�洢��SDC��TAF_SDC_Set1xCallUcimEmccNumList */
    /* TO DO ����USIMMģ���ṩAPI�ӿ�ֱ�ӻ�ȡ�������к���,�첽��ȡ�ļ��ӿ��ݲ�ʵ�� */
}



VOS_UINT8 TAF_XCALL_IsNeedRedialImmediately(
    TAF_CS_CAUSE_ENUM_UINT32            enCause
)
{
    switch(enCause)
    {
        case TAF_CS_CAUSE_XCALL_NDSS:
        case TAF_CS_CAUSE_XCALL_REDIRECTION:
        case TAF_CS_CAUSE_XCALL_ABORT:
            return VOS_TRUE;

        default:
            return VOS_FALSE;
    }
}

VOS_VOID TAF_XCALL_RcvMmaServiceStatusInd(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    VOS_UINT8                           ucCallFound;
    TAF_XCALL_CALL_ENTITY_STRU         *pstXcallEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucRedialFlg;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus;

    MMA_TAF_1X_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd;

    pstMmaServiceStatusInd = (MMA_TAF_1X_SERVICE_STATUS_IND_STRU*)pMsg;

    if (VOS_TRUE != pstMmaServiceStatusInd->ulExist1XService)
    {
        return;
    }


    ucCallFound     = VOS_FALSE;
    enServiceStatus = TAF_SDC_GetCsServiceStatus();

    for (ucCallId = 1; ucCallId <= TAF_XCALL_CALL_ENTITY_MAX_NUM; ucCallId++)
    {
        pstXcallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

        /* Added by h00313353 for Iteration 17, 2015-7-28, begin */
        /* ����ǽ���������Ϊ��Ҫ�������Է������ */
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (MN_CALL_TYPE_EMERGENCY == pstXcallEntity->enCallType))
        {
            ucCallFound = VOS_TRUE;
            break;
        }
        /* Added by h00313353 for Iteration 17, 2015-7-28, end */

        /*��ȡ�Ƿ���Ҫ�����ز��ı�� */
        ucRedialFlg    = TAF_XCALL_IsNeedRedialImmediately(pstXcallEntity->enCause);

        /*�Ƿ�����ز����� */
        if ((VOS_TRUE == pstXcallEntity->ulUsed)
         && (VOS_TRUE == ucRedialFlg))
        {
            ucCallFound = VOS_TRUE;
            break;
        }
    }

    if (VOS_FALSE == ucCallFound)
    {
        return;
    }

    /*�жϺ���״̬ */
    if (MN_CALL_TYPE_EMERGENCY == pstXcallEntity->enCallType)
    {
        /*�жϷ���״̬*/
        if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE  == enServiceStatus)
         || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == enServiceStatus))
         {
            /*�жϺ����ز���ʱ���Ƿ��Ѿ���ʱ */
            if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId))
            {
                /*�ر��ز���ʱ���������ز� */
                TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId);

                TAF_XCALL_SndXccOrigCallReq(ucCallId);
            }
         }
    }
    else
    {
        if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == enServiceStatus)
        {
            /*�жϺ����ز���ʱ���Ƿ��Ѿ���ʱ */
            if (TAF_XCALL_TIMER_STATUS_RUNING == TAF_XCALL_GetTimerStatus(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId))
            {
                /*�ر��ز���ʱ���������ز� */
                TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, ucCallId);

                TAF_XCALL_SndXccOrigCallReq(ucCallId);
            }
        }
    }

    return;
}

#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



