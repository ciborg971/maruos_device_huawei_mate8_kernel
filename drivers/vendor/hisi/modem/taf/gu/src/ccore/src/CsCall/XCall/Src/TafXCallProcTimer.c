


/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "TafXCallProcTimer.h"
#include "TafXCallCtx.h"
#include "TafXCallSndXcc.h"
#include "TafSdcCtx.h"
#include "TafXCallSndMma.h"
#include "TafXCallSndApp.h"
#include "TafXCallProcXcc.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-15, begin */
#include "TafMmaSndOm.h"
/* Added by y00322978 for CDMA Iteration 17, 2015-7-15, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_TIMER_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 ��������
*****************************************************************************/


/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID TAF_XCALL_RcvTiWaitCallRedialPeriodExpired(VOS_VOID *pMsg)
{
    /* nothing to do here */

    return;
}
VOS_VOID TAF_XCALL_RcvTiWaitCallRedialIntervalExpired(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    REL_TIMER_MSG                      *pTmrMsg         = VOS_NULL_PTR;
    TAF_XCALL_CALL_ENTITY_STRU         *pstCallEntity   = VOS_NULL_PTR;
    VOS_UINT16                          usClientId;
    MN_CALL_TYPE_ENUM_U8                enCallType;
    VOS_UINT32                          ulRemainTimeLen;

    pTmrMsg       = (REL_TIMER_MSG *)pMsg;
    ucCallId      = (VOS_UINT8)pTmrMsg->ulPara;
    pstCallEntity = TAF_XCALL_GetCallEntityAddr(ucCallId);

    usClientId          = MN_GetRealClientId(pstCallEntity->stClientInfo.usClientId, WUEPS_PID_TAF);
    enCallType          = TAF_XCALL_GetCallType(ucCallId);

    if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == TAF_SDC_GetCsServiceStatus())
    {
        /* ���ͺ�����Ϣ��XCC */
        TAF_XCALL_SndXccOrigCallReq(ucCallId);
    }
    else
    {
        ulRemainTimeLen = 0;
        TAF_XCALL_GetRemainTimerLen(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, ucCallId, &ulRemainTimeLen);

        if (ulRemainTimeLen >= TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN)
        {
            /* Deleted by h00313353 for Iteration 17, 2015-8-13, begin */

            /* Deleted by h00313353 for Iteration 17, 2015-8-13, end */

            TAF_XCALL_StartTimer(TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL, TI_TAF_XCALL_WAIT_CALL_REDAIL_INTERVAL_LEN, ucCallId);

            /* ��L2ʧ�ܵ�ԭ��ֵ,����ز����� */
            pstCallEntity->ucIsL2ErrReOrig = VOS_FALSE;
            pstCallEntity->ucReOrigCount   = 0;

        }
        else
        {
            /* ֹͣ�ز���ʱ��,�����ʱ��δ������call id��һ�������� */
            TAF_XCALL_StopTimer(TI_TAF_XCALL_WAIT_CALL_REDIAL_PERIOD, ucCallId);

            TAF_XCALL_UpdateCcCause(ucCallId, TAF_CS_CAUSE_XCALL_INTERNAL_NO_SERVICE);

            /* �ϱ�����ʧ�� */
            TAF_XCALL_SndCallReleaseInd(ucCallId);


            /* ��MMA����TAF_MMA_1X_CALL_END_NTF��Ϣ */
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_XCALL_BuildMmaCallType(enCallType));

            /* �ͷź���ʵ�� */
            TAF_XCALL_FreeCallEntity(ucCallId);

            if (VOS_FALSE == TAF_XCALL_ExistCallInstance())
            {
                /* ���SDC��CS���б�־ */
                TAF_SDC_SetCsCallExistFlg(VOS_FALSE);
            }
        }
    }

    return;
}


/*****************************************************************************
 �� �� ��  : TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired
 ��������  : Start Cont Dtmf������Ӧ��������ʱ������ʱ������,��ȡCallID,������
 �������  : VOS_VOID *pMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��18��
    ��    ��   : l00324781
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_XCALL_RcvTiStartAndStopContDtmfIntervalExpired(VOS_VOID *pMsg)
{
    VOS_UINT8                           ucCallId;
    REL_TIMER_MSG                      *pTmrMsg         = VOS_NULL_PTR;

    pTmrMsg       = (REL_TIMER_MSG *)pMsg;
    ucCallId      = (VOS_UINT8)pTmrMsg->ulPara;

    /* �����棬�����ϣ���һ����Ϣ��Stop Cont Dtmf */
    TAF_XCALL_ProcDtmfBuffer(ucCallId);
}

#endif

/*lint -restore */

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




