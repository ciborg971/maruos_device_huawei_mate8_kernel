

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "TafMmaCtx.h"
#include "TafMmaSndApp.h"
#include "TafMmaTimerMgmt.h"
#include "TafMmaComFunc.h"
#include "TafLog.h"
#include "TafMmaSndInternalMsg.h"

#if (FEATURE_IMS == FEATURE_ON)
#include "TafMmaFsmImsSwitch.h"
#include "TafMmaFsmImsSwitchTbl.h"
#include "TafMmaSndMscc.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_IMS_SWITCH_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 TAF_MMA_RcvTafImsSwitchSet_ImsSwitch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstImsSwitchSet = VOS_NULL_PTR;

    pstImsSwitchSet = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU*)pstMsg;

    /* ����������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��IMSҵ���ܵ����� */
    if (TAF_MMA_IMS_SWITCH_SET_POWER_ON == pstImsSwitchSet->enImsSwitch)
    {
        /* ����IMS���������MSCC */
        TAF_MMA_SndMsccImsStartReq();

        /* Ǩ��״̬���ȴ�IMSA�Ŀ����ظ� */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_START_CNF);

        /* ����������ʱ�� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF, TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF_LEN);
    }
    else    /* �����߹ر�IMSҵ���ܵ����� */
    {
        /* ����IMS�ر������MSCC */
        TAF_MMA_SndMsccImsStopReq();

        /* Ǩ��״̬���ȴ�IMSA�Ĺػ��ظ� */
        TAF_MMA_FSM_SetCurrState(TAF_MMA_IMS_SWITCH_STA_WAIT_MSCC_STOP_CNF);

        /* ����������ʱ�� */
        TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF, TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF_LEN);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMsccImsStartCnf_ImsSwitch_WaitMsccImsStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_IMS_START_CNF_STRU         *pstStartCnf = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32           enErrorCode;

    pstStartCnf = (MSCC_MMA_IMS_START_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_IMS_START_CNF);

    /* ת�������� */
    TAF_MMA_TransMsccImsStartResultToTafErrorCode(pstStartCnf->enResult, &enErrorCode);

    if (TAF_ERR_NO_ERROR == enErrorCode)
    {
        /* ��IMSΪ�ѿ��� */
        TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_ON);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
        TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_ON);
#endif

        /* ���ϲ�ظ��ɹ� */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_SUCC);
    }
    else
    {
        /* ��IMSΪ�ѹػ� */
        TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
        /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
        TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

        /* ����NVΪ��֧��IMSҵ�񣬷���AP��ѯ�����Ľ����MODEMά���Ĳ�һ�� */
        if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
        {
            /* warning��ӡ */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag fail!");
        }

        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_FAIL);
    }

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        vos_printf("\n*TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf\n");
    }

    /* warning��ӡ */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccImsStartCnfExpired_ImsSwitch_WaitMsccImsStartCnf:time expired!");

    /* ��IMSΪ�ѹػ� */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* ����NVΪ��֧��IMSҵ�񣬷���AP��ѯ�����Ľ����MODEMά���Ĳ�һ�� */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
    {
        /* warning��ӡ */
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag fail!");
    }

    /* ���ϲ�ظ�ʧ�� */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                            TAF_ERR_IMS_STACK_TIMEOUT);

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_ON_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMsccImsStopCnf_ImsSwitch_WaitMsccImsStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_IMS_STOP_CNF_STRU          *pstStopCnf = VOS_NULL_PTR;
    TAF_ERROR_CODE_ENUM_UINT32           enErrorCode;

    pstStopCnf = (MSCC_MMA_IMS_STOP_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_IMS_STOP_CNF);

    /* ��IMSΪ�ѹػ� */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ��ػ�״̬ */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* ת�������� */
    TAF_MMA_TransMsccImsStopResultToTafErrorCode(pstStopCnf->enResult, &enErrorCode);

    if (TAF_ERR_NO_ERROR == enErrorCode)
    {
        /* ���ϲ�ظ��ɹ� */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_SUCC);
    }
    else
    {
        /* ���ϲ�ظ�ʧ�� */
        TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                                enErrorCode);

        TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_FAIL);
    }

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        vos_printf("\n*TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf\n");
    }

    /* warning��ӡ */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccImsStopCnfExpired_ImsSwitch_WaitMsccImsStopCnf:time expired!");

    /* ��IMSΪ�ѹػ� */
    TAF_SDC_SetCurImsSwitchState(TAF_SDC_IMS_SWITCH_STATE_OFF);

#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    /* ֪ͨMTC IMSA�Ŀ���״̬ */
    TAF_MMA_SndMtcImsaStateInd(MTC_MODEM_POWER_OFF);
#endif

    /* ���ϲ�ظ�ʧ�� */
    TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(TAF_MMA_APP_OPER_RESULT_FAILURE,
                                            TAF_ERR_IMS_STACK_TIMEOUT);

    TAF_MMA_SndImsSwitchRsltInd(TAF_MMA_IMS_SWITCH_RESULT_OFF_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}
VOS_VOID TAF_MMA_ReportImsSwitchSetCnf_ImsSwitch(
    TAF_MMA_APP_OPER_RESULT_ENUM_UINT32 enResult,
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCause
)
{
    VOS_UINT32                          ulEventType;
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg     = VOS_NULL_PTR;
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstImsSwitchSet = VOS_NULL_PTR;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg = TAF_MMA_GetCurrFsmMsgAddr();
    ulEventType = pstEntryMsg->ulEventType;

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_IMS_SWITCH_SET_REQ) == ulEventType)
    {
        pstImsSwitchSet = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   enResult, enErrorCause);

    }

    return;

}

#endif /* FEATURE_IMS */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



