

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "TafTypeDef.h"
#include "MmaMsccInterface.h"
#include "TafMmaFsmPhoneMode.h"
#include "TafMmaCtx.h"
#include "TafSdcCtx.h"
#include "TafOamInterface.h"
#include "Taf_Status.h"
#include "MmaAppLocal.h"
#include "rfa.h"
#include "NasUsimmApi.h"
#include "msp_nvim.h"
#include "TTFMemInterface.h"
#include "TafMmaMain.h"
#include "TafMmaFsmPhoneModeTbl.h"
#include "TafMmaSndInternalMsg.h"
#include "TafLog.h"
#include "TafMmaTimerMgmt.h"
#include "TafAppMma.h"
#include "TafMmaSndTaf.h"
#include "TafMmaProcNvim.h"
#include "MmaUphyInterface.h"
#include "TafMmaSndApp.h"
#include "TafMmaSndMscc.h"
#include "NasMntn.h"
#include "NasComm.h"
#include "TafMmaComFunc.h"

#include "TafMmaSndUphy.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_PHONE_MODE_C

/*****************************************************************************
  3 ���Ͷ���
*****************************************************************************/

/*****************************************************************************
  4 ��������
*****************************************************************************/

/*****************************************************************************
  5 ��������
*****************************************************************************/
extern VOS_UINT8                                g_ucMmaOmConnectFlg;

extern VOS_UINT8                                g_ucMmaOmPcRecurEnableFlg;

extern MMA_DEACT_SIM_WHEN_POWEROFF_ENUM_UINT8   g_ucMmaDeactSimWhenPoweroff;

extern MMA_ME_PERSONALISATION_STATUS_STRU       g_stMmaMePersonalisationStatus;

extern STATUS_CONTEXT_STRU                      g_StatusContext;

extern TAF_MMA_GLOBAL_VALUE_ST                  gstMmaValue;


extern MMA_TIMER_ST                             g_stPowerDownDelayTimer;

extern MN_PH_REG_TIME_INFO_STRU                 g_stRegTimeInfo;

/*lint -save -e958 */

/*****************************************************************************
  6 ����ʵ��
*****************************************************************************/

VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* ����������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    if (VOS_TRUE == TAF_MMA_IsExternalModuleInitCompeleted())
    {
        if (MMA_UPHY_INIT_STATUS_FAIL == TAF_MMA_GetPhyInitStatus())
        {
            NAS_TRACE_HIGH("MMA UPHY INIT FAIL!!!!!!!!");

            /* �ظ�����ʧ�ܴ��� */
            TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_PHY_FAIL);

            /* ��¼�������ͣ����Ϳ���ʧ�ܸ�OM or AT */
            TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
            TAF_MMA_ReportPhoneModeCnf_PhoneMode();

            /* ����״̬���˳���Ϣ */
            TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

            /* �˳�״̬�� */
            TAF_MMA_FSM_QuitSubFsm();

            return VOS_TRUE;
        }

        /* �ϵ��һ���յ���״̬�仯,�Զ�����������ҪͶƱ��ֹ˯�� */
        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
        TAF_MMA_ProcStartReq_PhoneMode();

        return VOS_TRUE;
    }

    /* Ǩ��״̬���ȴ���ʼ�����״̬�ϱ� */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT);

    /* ����������ʱ��,��Ҫ������ʱ��������ֹͣ���� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT,
                       TAF_MMA_GetWaitExtTimerLen() * NAS_SDC_ONE_THOUSAND_MILLISECOND);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ucIsCLWork;
    VOS_UINT32                          ucIsUsimSrvAvail;

    ucIsCLWork          = TAF_MMA_IsPowerOnCLInterWork();
    ucIsUsimSrvAvail    = TAF_MMA_IsUsimServiceAvailable();

    /* ����������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_PTM)
    /* ��CL��ģʽ�ҿ���Ч������£��Ÿ�AP�ϱ��ػ� */
    if ((VOS_TRUE != ucIsCLWork)
     && (VOS_TRUE == ucIsUsimSrvAvail))
    {
        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_CS);

        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_PS);

        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_TRUE);
    }
#endif

    TAF_MMA_ProcPowerOffReq_PhoneMode();

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvOMPhoneModeSet_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;
    VOS_UINT32                          ucIsCLWork;
    VOS_UINT32                          ucIsUsimSrvAvail;

    ucIsCLWork          = TAF_MMA_IsPowerOnCLInterWork();
    ucIsUsimSrvAvail    = TAF_MMA_IsUsimServiceAvailable();


    pstRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstPhModeSet        = (TAF_PH_OP_MODE_STRU *)pstRcvMsg->aucContent;
    enPhyInitStatus     = TAF_MMA_GetPhyInitStatus();

    /* ����������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ����ΪFULLģʽ���п��� */
    if (TAF_PH_MODE_FULL == pstPhModeSet->PhMode)
    {
         /* PC�ط�ʱ���ж�USIM�Ŀ�״̬ */
#if defined(__PC_TRACE_RECUR__)
#else
        if (VOS_FALSE  == TAF_MMA_IsExternalModuleInitCompeleted())
        {
            /* Ǩ��״̬���ȴ���ʼ�����״̬�ϱ� */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT);


            /* �����ⲿģ���ʼ��������ʱ�� */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT, TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT_LEN);


            return VOS_TRUE;
        }
#endif

        if (MMA_UPHY_INIT_STATUS_SUCCESS == enPhyInitStatus)
        {

            /* ���п������� */
            TAF_MMA_ProcStartReq_PhoneMode();
        }
        else
        {
            /* ��¼�������ͣ����Ϳ���ʧ�ܸ�OM or AT */
            TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
            TAF_MMA_ReportPhoneModeCnf_PhoneMode();

            /* ���Ϳ���ʧ�ܽ����Ϣ */
            TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

            /* �˳�״̬�� */
            TAF_MMA_FSM_QuitSubFsm();
        }

        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_PTM)
    /* ��CL��ģʽ�ҿ���Ч������£��Ÿ�AP�ϱ��ػ� */
    if ((VOS_TRUE != ucIsCLWork)
     && (VOS_TRUE == ucIsUsimSrvAvail))
    {
        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_CS);

        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_PS);

        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_TRUE);
    }
#endif

    /* �����߹ػ����� */
    TAF_MMA_ProcPowerOffReq_PhoneMode();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTafPhoneModeSet_PhoneMode_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhModeSet    = VOS_NULL_PTR;
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;
    VOS_UINT32                          ucIsCLWork;
    VOS_UINT32                          ucIsUsimSrvAvail;

    ucIsCLWork          = TAF_MMA_IsPowerOnCLInterWork();
    ucIsUsimSrvAvail    = TAF_MMA_IsUsimServiceAvailable();


    pstPhModeSet        = (TAF_MMA_PHONE_MODE_SET_REQ_STRU*)pstMsg;
    enPhyInitStatus     = TAF_MMA_GetPhyInitStatus();

    /* ����������Ϣ */
    TAF_MMA_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ����ΪFULLģʽ���п��� */
    if (TAF_PH_MODE_FULL == pstPhModeSet->stPhoneModePara.PhMode)
    {
         /* PC�ط�ʱ���ж�USIM�Ŀ�״̬ */
#if defined(__PC_TRACE_RECUR__)
#else
        if (VOS_FALSE  == TAF_MMA_IsExternalModuleInitCompeleted())
        {
            /* Ǩ��״̬���ȴ���ʼ�����״̬�ϱ� */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_EXTERNAL_MODULE_INIT);


            /* �����ⲿģ���ʼ��������ʱ�� */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT, TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT_LEN);


            return VOS_TRUE;
        }
#endif
        if (MMA_UPHY_INIT_STATUS_SUCCESS == enPhyInitStatus)
        {
            /* ���п������� */
            TAF_MMA_ProcStartReq_PhoneMode();
        }
        else
        {
            /* ��¼�������ͣ����Ϳ���ʧ�ܸ�OM or AT */
            TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
            TAF_MMA_ReportPhoneModeCnf_PhoneMode();

            /* ���Ϳ���ʧ�ܽ����Ϣ */
            TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

            /* �˳�״̬�� */
            TAF_MMA_FSM_QuitSubFsm();
        }

        return VOS_TRUE;
    }


#if (FEATURE_ON == FEATURE_PTM)
    /* ��CL��ģʽ�ҿ���Ч������£��Ÿ�AP�ϱ��ػ� */
    if ((VOS_TRUE != ucIsCLWork)
     && (VOS_TRUE == ucIsUsimSrvAvail))
    {
        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_CS);

        TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_OFF,
                                     NAS_ERR_LOG_OOS_DOMAIN_PS);

        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_TRUE);
    }
#endif

    /* �����߹ػ����� */
    TAF_MMA_ProcPowerOffReq_PhoneMode();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_UPHY_INIT_STATUS_ENUM_UINT16    enPhyInitStatus;

    enPhyInitStatus                     = TAF_MMA_GetPhyInitStatus();

    /* ���������Ѿ�����ʼ�������ֹͣ������ʱ��������ֱ�ӷ��� */
    if (MMA_UPHY_INIT_STATUS_BUTT == enPhyInitStatus)
    {
        return VOS_TRUE;
    }
    else
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);
    }



#ifndef __PS_WIN32_RECUR__
    if ( (VOS_TRUE == g_ucMmaOmConnectFlg)
      && (VOS_TRUE == g_ucMmaOmPcRecurEnableFlg) )
    {
        NAS_MMA_SndOutsideFixedContextData();
    }
#endif

    /* �ϵ��һ���յ���״̬�仯,�Զ�����������ҪͶƱ��ֹ˯�� */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
    TAF_MMA_ProcStartReq_PhoneMode();

    return VOS_TRUE;
}




VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* warning ��ӡ */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitExternalModuleInit:time expired!");

    /* ���¿�״̬Ϊ����Ч */
    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */



    /*�����δ��ʼ����������*/
    if (MMA_UPHY_INIT_STATUS_SUCCESS != TAF_MMA_GetPhyInitStatus())
    {
        NAS_TRACE_HIGH("MMA UPHY INIT TIMEOUT!!!!!!!!");

        /* ����ril�ϱ�������ʼ����ʱ�Ľ�� */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_PHY_TIMEOUT);

        /* ��¼�������ͣ����Ϳ���ʧ�ܸ�OM or AT */
        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* ����״̬���˳���Ϣ */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();

        return VOS_TRUE;
    }

    /* �ϵ��һ���յ���״̬�仯,�Զ�����������ҪͶƱ��ֹ˯�� */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
    TAF_MMA_ProcStartReq_PhoneMode();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvUphyInitStatusInd_PhoneMode_WaitExternalModuleInit(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    UPHY_MMA_INIT_STATUS_IND_STRU      *pstRcvMsg              = VOS_NULL;

    pstRcvMsg                       = (UPHY_MMA_INIT_STATUS_IND_STRU*)pstMsg;

    /*����������ʼ��״̬*/
    if (MMA_UPHY_INIT_STATUS_BUTT > pstRcvMsg->enInitStatus)
    {
        TAF_MMA_SetPhyInitStatus(pstRcvMsg->enInitStatus);
    }

    if (MMA_UPHY_INIT_STATUS_SUCCESS != pstRcvMsg->enInitStatus)
    {
        NAS_TRACE_HIGH("MMA UPHY INIT FAIL!!!!!!!!");

        /* ֹͣ��ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

        /* ����ril��� */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_PHY_FAIL);

        /* ��¼�������ͣ����Ϳ���ʧ�ܸ�OM or AT */
        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_PHY_INIT_FAILURE);
        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* ����״̬���˳���Ϣ */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();

        return VOS_TRUE;
    }


    /* �����״̬�Ѿ��ϱ�����ֹͣ�ȴ���ʱ�� */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {
        /* ֹͣ��ʱ�� */
        TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);
    }

    /* �ϵ翪����ȡ�����빦�ܴ򿪣��Ҳ���C�˵�����λ���µ��ϵ磬��Ҫ�޿���������ȡ������ */
    if (VOS_TRUE  == TAF_MMA_IsNeedGetGeoNoSimStart())
    {
        /* �ϵ��һ���յ�������ʼ����Ϣ,�Զ�����������ҪͶƱ��ֹ˯�� */
        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);

        /* �˴������Ŀ�״̬�������п������޿��������޿����� */
        TAF_MMA_ProcGetGeoNoSimStartReq_PhoneMode();

        return VOS_TRUE;
    }

    /* ���USIM��־��������־��ΪTRUE������Э��ջ */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {

        /* �ϵ��һ���յ�������ʼ����Ϣ,�Զ�����������ҪͶƱ��ֹ˯�� */
        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);
        TAF_MMA_ProcStartReq_PhoneMode();
    }

    return VOS_TRUE;

}




VOS_VOID TAF_MMA_SndStartReq_PhoneMode(
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8         enUsimCardStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8         enCsimCardStatus;
    TAF_MMA_RAT_ORDER_STRU                      stSndRatPrioList;
    TAF_SDC_USIM_STATUS_ENUM_UINT8              enUsimStatus;
    TAF_SDC_USIM_STATUS_ENUM_UINT8              enCsimStatus;
    TAF_MMA_RAT_ORDER_STRU                     *pstRatPrioList  = VOS_NULL_PTR;
    VOS_UINT32                                  ulEventType;
    VOS_UINT8                                   ucIsCardRefresh;

    ulEventType = TAF_MMA_GetCurrFsmMsgAddr()->ulEventType;
    ucIsCardRefresh                             = VOS_FALSE;

    enUsimStatus = TAF_SDC_GetUsimStatus();
    enCsimStatus = TAF_SDC_GetCsimStatus();

    /* ����coverity�澯 */
    if (TAF_SDC_USIM_STATUS_BUTT == enUsimStatus)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_SndStartReq_PhoneMode: Usim Status is BUTT!");
    }

    /* ����coverity�澯 */
    if (TAF_SDC_USIM_STATUS_BUTT == enCsimStatus)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_SndStartReq_PhoneMode: Csim Status is BUTT!");
    }

    /* ��ȡ��״̬ */
    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    enUsimCardStatus = TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(enUsimStatus, TAF_SDC_GetUsimType());
    enCsimCardStatus = TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(enCsimStatus, TAF_SDC_GetCsimType());
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */

    /* ��ȡ���뼼����Ϣ */
    pstRatPrioList = TAF_MMA_GetRatPrioListAddr();

    PS_MEM_SET(&stSndRatPrioList, 0, sizeof(TAF_MMA_RAT_ORDER_STRU));

    stSndRatPrioList.ucRatOrderNum = pstRatPrioList->ucRatOrderNum;
    PS_MEM_CPY(stSndRatPrioList.aenRatOrder,
               pstRatPrioList->aenRatOrder,
               pstRatPrioList->ucRatOrderNum);

    TAF_MMA_GetAvailablePlmnRatPrio(&stSndRatPrioList);

    /* ���Ϳ��������UPHY */
    TAF_MMA_SndUphyPowerOnReq();

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND) == ulEventType)
    {
        ucIsCardRefresh = VOS_TRUE;
    }

    /* ���Ϳ��������MSCC */
    (VOS_VOID)TAF_MMA_SndMsccStartReq(&stSndRatPrioList, enUsimCardStatus, enCsimCardStatus, ucIsCardRefresh);

    /* Ǩ��״̬���ȴ�MSCC�Ŀ����ظ� */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_START_CNF);

    /* ����������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF, TI_TAF_MMA_WAIT_MSCC_START_CNF_LEN);

}
NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 TAF_MMA_ConvertSdcSimStatusToMsccFormat_PhoneMode(
    VOS_UINT8                           ucSdcSimStatus,
    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    VOS_UINT8                           ucSimType
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */
)
{
    /* ��û���յ���״̬��Ϣʱ�򿨲���λ����PIN��ʱ,��Ϊ�޿����� */
    if ((TAF_SDC_USIM_STATUS_BUTT       == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_NO_PRESENT == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PIN    == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK    == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_UNVALID    == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_READY_TIMEROUT    == ucSdcSimStatus))
    {
        return NAS_MSCC_PIF_CARD_STATUS_ABSENT;
    }

    if (TAF_PH_ME_SIM_LOCK == MMA_GetMeLockStatus())
    {
        return NAS_MSCC_PIF_CARD_STATUS_ABSENT;
    }

    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    if (TAF_SDC_SIM_TYPE_USIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_ROM_SIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_SIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_SIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_UIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_UIM_PRESENT;
    }
    else if (TAF_SDC_SIM_TYPE_CSIM == ucSimType)
    {
        return NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT;
    }
    else
    {
        return NAS_MSCC_PIF_CARD_STATUS_ABSENT;
    }
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */
}



VOS_VOID TAF_MMA_SndPowerOffReq_PhoneMode(
    VOS_UINT32                          ulReceivePid
)
{
    TAF_MMA_SndMsccPowerOffReq(TAF_MMA_GetMsccPowerOffCause_PhoneMode());

    /* Ǩ��״̬���ȴ�MSCC�Ĺػ��ظ� */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_POWER_OFF_CNF);

    /* ����������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF, TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF_LEN);

    return;

}



VOS_VOID TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode(VOS_VOID)
{
    VOS_UINT8                                               ucNeedPinFlg;
    VOS_UINT8                                               ucSdcSimStatus;
    VOS_UINT16                                              usAppCfgSupportType;



    usAppCfgSupportType     = TAF_SDC_GetAppCfgSupportType();
    ucSdcSimStatus          = TAF_SDC_GetSimStatus();
    ucNeedPinFlg            = VOS_FALSE;

    /* ���µ�ǰ��ģʽΪFULLģʽ */
    TAF_SDC_SetCurPhoneMode(TAF_PH_MODE_FULL);

    if ((TAF_SDC_USIM_STATUS_SIM_PIN == ucSdcSimStatus)
     || (TAF_SDC_USIM_STATUS_SIM_PUK == ucSdcSimStatus))
    {
       ucNeedPinFlg = VOS_TRUE;
    }

    if (VOS_FALSE == ucNeedPinFlg)
    {
        (VOS_VOID)MMA_GetMeLockStatus();
    }

    TTF_MemCcpuCheckPoolLeak();

    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    if (SYSTEM_APP_WEBUI == usAppCfgSupportType)
    {
        if ((VOS_FALSE == ucNeedPinFlg)
         && (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus))
        {
            MN_PH_SimLockedRpt();
        }
    }

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_ON);
#endif

    /* ��ȫ�ֱ�������ģʽ�жϣ������ΪC+L������ģʽ��������ע������ */
    if (VOS_TRUE != TAF_MMA_IsPowerOnCLInterWork())
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == TAF_SDC_IsPlatformSupport3Gpp2())
        {
            /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
            TAF_MMA_SndMsccCFreqLockNtf(TAF_MMA_GetCFreqLockSetPara());
            /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */
        }
#endif
        TAF_MMA_SndMsccSystemAcquireReq();

        /* ����Ч������£��Ÿ�AP�ϱ����� */
#if (FEATURE_ON == FEATURE_PTM)
        if (VOS_TRUE == TAF_MMA_IsUsimServiceAvailable())
        {
            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_CS);

            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_PS);

            TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_TRUE);
            TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_FALSE);
        }
#endif
    }

#if defined(__PS_WIN32_RECUR__) || defined(NAS_STUB)
    if (TAF_SDC_USIM_STATUS_VALID == TAF_SDC_GetSimStatus())
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_AVAILABLE);
    }
    else
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_UNAVAILABLE);
    }
#endif


    /* ����״̬���˳���Ϣ */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    /* �յ�rrmm-start-cnf��Ϣ��
     ��ǰ���Զ�������
        MMA��Ҫ�ͷ�ͶƱ,��AS����plmn_serach_reqʱ,��OAMͶ����˯��Ʊ,
     ��ǰ�Ƿ��Զ�������
        MMA��Ҫ�ͷ�ͶƱ,����˯��*/

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
    }

    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);


    return;
}


VOS_VOID TAF_MMA_ProcStartCnfSucc_PowerInit_PhoneMode(VOS_VOID)
{
    VOS_UINT32                          ulAutoSwitchOnFlg;
    VOS_UINT8                           ucSdcSimStatus;

    ulAutoSwitchOnFlg       = TAF_MMA_GetAutoSwitchOnFlg();

    /* ��E5�µĳ��ģʽ���Զ��ϵ翪��NV�ر�ʱ���йػ����� */
    if ((DRV_START_MODE_CHARGING == mdrv_sysboot_get_bootmode())
     || (VOS_FALSE == ulAutoSwitchOnFlg))
    {
        /* �ϵ粻�Զ�������NAS��Ҫ�ر�RF */
        MMA_TurnOffForFlightMode();

        NAS_TRACE_HIGH("mdrv_sysboot_get_bootmode = %d, ulAutoSwitchOnFlg = %d",
                        (VOS_UINT32)mdrv_sysboot_get_bootmode(),
                        ulAutoSwitchOnFlg);

        /* �߹ػ����� */
        TAF_MMA_ProcPowerOffReq_PhoneMode();

        return;
    }

    /* ���µ�ǰ��ģʽΪFULLģʽ */
    TAF_SDC_SetCurPhoneMode(TAF_PH_MODE_FULL);

    /* Ӳ���������ߵ���������ײ� */
    MMA_TurnOnForFlightMode();

    TTF_MemCcpuCheckPoolLeak();

#ifndef __PS_WIN32_RECUR__
    NAS_MMA_SndOutsideContextData();
#endif

    TAF_MMA_ReportPhoneModeInd_PhoneMode();

    ucSdcSimStatus          = TAF_SDC_GetSimStatus();

    if (SYSTEM_APP_WEBUI == TAF_SDC_GetAppCfgSupportType())
    {
        /* ����ҪPIN�뵫����ʱ�ϱ�SIM LOCKED�¼� */
        if (((TAF_SDC_USIM_STATUS_SIM_PIN != ucSdcSimStatus)
          && (TAF_SDC_USIM_STATUS_SIM_PUK != ucSdcSimStatus))
         && (MMA_SIM_IS_LOCK == g_stMmaMePersonalisationStatus.SimLockStatus))
        {
            MN_PH_SimLockedRpt();
        }
    }

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_ON);
#endif

    /*��ȫ�ֱ�������ģʽ�жϣ������ΪC+L������ģʽ��������ע������,����ȴ�CMMCA��������ע������ */
    if (VOS_TRUE != TAF_MMA_IsPowerOnCLInterWork())
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_TRUE == TAF_SDC_IsPlatformSupport3Gpp2())
        {
            /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, begin */
            TAF_MMA_SndMsccCFreqLockNtf(TAF_MMA_GetCFreqLockSetPara());
            /* Added by y00307564 for CDMA 1X Iteration 6, 2014-12-29, end */
        }
#endif

        TAF_MMA_SndMsccSystemAcquireReq();

#if (FEATURE_ON == FEATURE_PTM)
        /* ����Ч������£��Ÿ�AP�ϱ����� */
        if (VOS_TRUE == TAF_MMA_IsUsimServiceAvailable())
        {
            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_CS);

            TAF_MMA_ReportErrlogOosBegin(NAS_ERR_LOG_OOS_CAUSE_USER_POWER_ON,
                                         NAS_ERR_LOG_OOS_DOMAIN_PS);

            TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_TRUE);
            TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_FALSE);
        }
#endif

#if 0
        Sta_AttachByModeService(STA_OPID_ATTATCH);
#endif
    }

#if defined(__PS_WIN32_RECUR__) || defined(NAS_STUB)
    if (TAF_SDC_USIM_STATUS_VALID == ucSdcSimStatus)
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_AVAILABLE);
    }
    else
    {
        MN_PH_SndMsgUsimStatus(USIMM_CARD_SERVIC_UNAVAILABLE);
    }
#endif

    /* �յ�rrmm-start-cnf��Ϣ��
     ��ǰ���Զ�������
        MMA��Ҫ�ͷ�ͶƱ,��AS����plmn_serach_reqʱ,��OAMͶ����˯��Ʊ,
     ��ǰ�Ƿ��Զ�������
        MMA��Ҫ�ͷ�ͶƱ,����˯��*/
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
    {
        (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartCnfSucc_PowerInit_PhoneMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
    }

    /* ����״̬���˳���Ϣ */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return;
}


VOS_UINT32 TAF_MMA_RcvMsccStartCnf_PhoneMode_WaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_START_CNF_STRU            *pstStartCnf = VOS_NULL_PTR;
    VOS_UINT32                          ulRslt;

    pstStartCnf                         = (MSCC_MMA_START_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Mscc Start Cnf!!!");

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF);

    /* MSCCģ�鿪���ɹ�����������Ҫ�·�������Ϣ��ģ�飬�·�������Ϣ */
    if ( NAS_MSCC_PIF_START_RESULT_SUCC == pstStartCnf->ulResult )
    {

        /* �����ɹ��Ĵ��� */
        ulRslt      = TAF_MMA_ProcStartComplete_PhoneMode(VOS_TRUE);
    }
    else
    {
        /* ����ʧ�ܵĴ��� */
        ulRslt      = TAF_MMA_ProcStartComplete_PhoneMode(VOS_FALSE);
    }

    return ulRslt;
}



VOS_UINT32 TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* warning��ӡ */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_WaitMsccStartCnf:time expired!");

    NAS_TRACE_HIGH("MMA Start Timeout!");

    /* ������ʱ���� */
    TAF_MMA_ProcStartExpired_PhoneMode();

    return VOS_TRUE;
}


VOS_VOID TAF_MMA_ProcPowerOffCnf_UsimStatusChange_PhoneMode(VOS_VOID)
{
    /* ����ʱ��ɾ��EPLMN��Ϣ */
    if (TAF_SDC_USIM_STATUS_NO_PRESENT == TAF_SDC_GetSimStatus())
    {
        MMA_ClearEplmnFromNV();
        TAF_INFO_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPowerOffCnf_UsimStatusChange_PhoneMode:EPLMN is cleared:");
    }

    /* ��ʼ��ȫ�ֱ��� */
    TAF_MMA_InitCtx(TAF_MMA_INIT_CTX_POWEROFF, TAF_MMA_GetMmaCtxAddr());

    /* ���ڲ��������� */
    TAF_MMA_ProcStartReq_PhoneMode();

    return;
}
VOS_VOID TAF_MMA_ProcPowerOffCnfWithPowerOffMode_PhoneMode(VOS_VOID)
{
    VOS_UINT16                          usAppCfgSupportType;
    VOS_UINT32                          ulRslt;

    usAppCfgSupportType     = TAF_SDC_GetAppCfgSupportType();

    if (SYSTEM_APP_WEBUI == usAppCfgSupportType)
    {
        /* �ر���Ƶ */
        MMA_TurnOffForFlightMode();




        /* ��TASKDELAY�޸�Ϊ������ʱ�����б��� */
        ulRslt = NAS_StartRelTimer(&g_stPowerDownDelayTimer.MmaHTimer,
                              WUEPS_PID_MMA,
                              TI_TAF_MMA_DELAY_POWER_DOWN_TIMER_LEN,
                              TAF_MMA,
                              TI_TAF_MMA_DELAY_POWER_DOWN,
                              VOS_RELTIMER_NOLOOP );

        if( VOS_OK !=  ulRslt)
        {
            MMA_WARNINGLOG("Sta_PowerOffCnf():ERROR:Start TI_TAF_MMA_DELAY_POWER_DOWN Timer Error!");
            mdrv_sysboot_poweroff();
        }



        return;
    }

    if (SYSTEM_APP_ANDROID   == usAppCfgSupportType)
    {
        /* ȥ����USIM�� */
        (VOS_VOID)NAS_USIMMAPI_DeactiveCardReq(WUEPS_PID_MMA);

        /* �ر���Ƶ */
        MMA_TurnOffForFlightMode();

        /* ���ϱ��¼�ǰ�ȵ���COMM�ӿ�Flush NV */
#if (FEATURE_ON == FEATURE_LTE)
        (VOS_VOID)NVM_Flush();
#endif
        (VOS_VOID)NV_Flush();
    }

    return;
}


VOS_VOID TAF_MMA_ProcPowerOffCnfWithSpecPhoneMode_PhoneMode(
    VOS_UINT8                           ucPhoneMode
)
{
    switch (ucPhoneMode)
    {
        case TAF_PH_MODE_POWEROFF:

            TAF_MMA_ProcPowerOffCnfWithPowerOffMode_PhoneMode();
            break;

        case TAF_PH_MODE_MINI:

            MMA_TurnOffForFlightMode();

#if (FEATURE_ON == FEATURE_LTE)
            (VOS_VOID)NVM_Flush();
#endif
            (VOS_VOID)NV_Flush();

            /* ��"AT+CFUN=0������ػ���ȥ����(U)SIM������"������ʹ�ܣ���ȥ����SIM�� */
            if (MMA_DEACT_SIM_WHEN_POWEROFF_ENABLE == g_ucMmaDeactSimWhenPoweroff)
            {
                (VOS_VOID)NAS_USIMMAPI_DeactiveCardReq(WUEPS_PID_MMA);
            }

            break;

        case TAF_PH_MODE_RFOFF:
        case TAF_PH_MODE_LOWPOWER:
        case TAF_PH_MODE_VDFMINI:

            MMA_TurnOffForFlightMode();
            break;

        default:

            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPowerOffCnfWithSpecPhoneMode_PhoneMode:No need to deal with this mode!");
            break;
    }

    return;
}
VOS_UINT32 TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_WaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;

    NAS_TRACE_HIGH("Rcv Mscc Power Off Cnf!!!");


    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF);

    /* �ػ���ɵĴ��� */
    ulRslt = TAF_MMA_ProcPowerOffComplete_PhoneMode();

    return ulRslt;
}



VOS_UINT32 TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* warning��ӡ */
    TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_WaitMsccPowerOffCnf:time expired!");

    NAS_TRACE_HIGH("MMA PowerOff Timeout!!!");


    /* �ػ���ʱ�Ĵ��� */
    TAF_MMA_ProcPowerOffExpired_PhoneMode();

    return VOS_TRUE;
}


VOS_VOID TAF_MMA_ProcPowerOffReq_PhoneMode(VOS_VOID)
{
    VOS_UINT32                          ulModuleId;

    ulModuleId = 0;

    /* ����ͶƱ:�ػ�ʱ������˯��,�յ�MSCC�Ĺػ��ظ�֮���� */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);

    /* ����STOP״̬��־��*/
    g_StatusContext.ulFsmState = STA_FSM_STOP;

    /* ���������ע��ɹ�ʱ�� */
    g_stRegTimeInfo.ulCostTime      = 0;

    /* ��ȡ��һ���ػ�������Ϣ��ģ��,������ulModuleIdΪ��Чֵ����� */
    /* �·��ػ����� */
    TAF_MMA_SndPowerOffReq_PhoneMode(ulModuleId);


    /* ���TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU��ʱ���������У���Ҫֹͣ */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodNetSelMenuStatus())
    {
       if (VOS_OK != NAS_StopRelTimer(WUEPS_PID_MMA,
                                      TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU,
                                      &(g_StatusContext.stNetSelMenuCtx.stTiPeriodTryingNetSelMenu.MmaHTimer)))
       {
           TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_ProcPowerOffReq_PhoneMode:stop TI_TAF_MMA_PERIOD_TRYING_NETWORK_SELECTION_MENU failed!");
       }

       TAF_MMA_SetTiTryingPeriodNetSelMenuStatus(MMA_TIMER_STOP);
    }

    /* ���TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING��ʱ���������У���Ҫֹͣ */
    if (MMA_TIMER_RUN == TAF_MMA_GetTiTryingPeriodRatBalancingStatus())
    {
       TAF_MMA_StopTimer(TI_TAF_MMA_PERIOD_TRYING_RAT_BALANCING);

       TAF_MMA_SetTiTryingPeriodRatBalancingStatus(MMA_TIMER_STOP);
    }

    return;
}
VOS_VOID TAF_MMA_ProcStartReq_PhoneMode(VOS_VOID)
{
    TAF_CS_SERVICE_ENUM_UINT32          enCsServCapa;

    /* ����RESTART״̬��־�� */
    g_StatusContext.ulFsmState = STA_FSM_RESTART;

    if (MMA_MMA_INTER_POWER_INIT != TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        /* ��RF��Դ */
        MMA_TurnOnForFlightMode();
    }

    TAF_MMA_UpdateUeBandNvim();

#if (FEATURE_ON == FEATURE_LTE)    
    TAF_MMA_UpdateUserSetLteBands();
#endif
    

    /* ��¼�������ֵ */
    g_StatusContext.ucModeService = gstMmaValue.stSetMsClass.MsClassType;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == TAF_SDC_IsSysCfgRatSupportHrpdAndLte())
    {
        if (NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO != TAF_MMA_GetPlmnSelectionMode())
        {
            /* set PLMN selection mode auto in global variable  */
            TAF_MMA_SetPlmnSelectionMode((VOS_UINT8)NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);

            /* write PLMN selection mode auto in NV */
            TAF_MMA_WritePlmnSelectionModeNvim((VOS_UINT8)NAS_MSCC_PIF_PLMN_SEL_MODE_AUTO);
        }
    }
#endif

    /* ��ȡ��һ������������Ϣ��ģ��,������ulModulePidΪ��Чֵ����� */
    /* �·��������� */
    TAF_MMA_SndStartReq_PhoneMode();


    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        /* ��ȡCS������ */
        if (VOS_TRUE == TAF_MMA_IsCsServDomainAvail(gstMmaValue.stSetMsClass.MsClassType))
        {
            enCsServCapa = TAF_CS_ON;
        }
        else
        {
            enCsServCapa = TAF_CS_OFF;
        }

        TAF_MMA_SndStkCsServiceChangeNotify(enCsServCapa);
        TAF_MMA_SndMsgCsServiceChangeNotify(enCsServCapa);
    }

    MN_PH_UpdateBeginRegTime();

    return;
}
VOS_UINT32  TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulMsgId;

   /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulMsgId         = TAF_MMA_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType);

    return ulMsgId;
}
VOS_UINT8  TAF_MMA_GetCurrFsmEntryMsgOpId_PhoneMode(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg         = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg           = VOS_NULL_PTR;
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

   /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg         = TAF_MMA_GetCurrFsmMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    ulEventType         = pstEntryMsg->ulEventType;

    if (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_POWER_INIT)== ulEventType)
    {
        return STA_OPID_INSIDE;
    }

    if ((TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND) == ulEventType)
     || (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND)   == ulEventType))
    {
        return MMA_OP_ID_INTERNAL;
    }

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ) == ulEventType )
    {
        return pstPhoneModeSetReq->stCtrl.ucOpId;
    }

    return pstAppMsg->opId;

}
VOS_UINT8  TAF_MMA_GetCurrFsmEntryMsgPhoneMode_PhoneMode(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg  = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg    = VOS_NULL_PTR;
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;


    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSet = VOS_NULL_PTR;

    VOS_UINT32                          ulEventType;

   /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();
    pstAppMsg       = (MN_APP_REQ_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    pstPhoneModeSet = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    ulEventType = pstEntryMsg->ulEventType;

    if ((TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ) == ulEventType)
      || (TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ) == ulEventType))
    {
        pstPhModeSet = (TAF_PH_OP_MODE_STRU*)pstAppMsg->aucContent;

        return pstPhModeSet->PhMode;
    }



    /* �ػ�������TAF���͵ģ�Ҳ����ʱCMMCA���͵� */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ) == ulEventType)
    {
        return pstPhoneModeSet->stPhoneModePara.PhMode;
    }
    return TAF_SDC_GetCurPhoneMode();
}


VOS_UINT16  TAF_MMA_GetCurrFsmEntryMsgClientId_PhoneMode(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg         = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstAppMsg           = VOS_NULL_PTR;
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;

    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg         = TAF_MMA_GetCurrFsmMsgAddr();
    pstAppMsg           = (MN_APP_REQ_MSG_STRU *)(pstEntryMsg->aucEntryMsgBuffer);
    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    ulEventType = pstEntryMsg->ulEventType;

    if ((TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_POWER_INIT)             == ulEventType)
     || (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_INTER_USIM_STATUS_CHANGE_IND) == ulEventType)
     || (TAF_BuildEventType(WUEPS_PID_MMA, MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND)   == ulEventType))
    {
        return MMA_CLIENTID_NONE;
    }

    /* CMMCA����AT������ģʽ���� */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ) == ulEventType )
    {
        return pstPhoneModeSetReq->stCtrl.usClientId;
    }

    return pstAppMsg->clientId;

}


VOS_VOID TAF_MMA_ReportPhoneModeCnf_PhoneMode(VOS_VOID)
{
    TAF_MMA_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulEventType;
    VOS_UINT8                           ucOpId;
    TAF_PH_OP_MODE_CNF_STRU             stPhMode;
    VOS_UINT16                          usClientId;
    TAF_ERROR_CODE_ENUM_UINT32          enErrorCode;

    PS_MEM_SET(&stPhMode, 0x00, sizeof(stPhMode));
    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = TAF_MMA_GetCurrFsmMsgAddr();

    ulEventType = pstEntryMsg->ulEventType;
    ucOpId      = TAF_MMA_GetCurrFsmEntryMsgOpId_PhoneMode();
    usClientId  = TAF_MMA_GetCurrFsmEntryMsgClientId_PhoneMode();
    enErrorCode = TAF_MMA_GetCurPhoneErrorCode_PhoneMode();

    /* ֻ��ҪOM��AT��CMMCA�����Ŀ�����ػ�����ģʽ���ý���ϱ� */
    if ( (TAF_BuildEventType(WUEPS_PID_SPY, OAM_MMA_PHONE_MODE_SET_REQ)      == ulEventType)
      || (TAF_BuildEventType(WUEPS_PID_TAF, ID_TAF_MMA_PHONE_MODE_SET_REQ)  == ulEventType)
      || (TAF_BuildEventType(CCPU_PID_CBT, OAM_MMA_PHONE_MODE_SET_REQ)      == ulEventType))
    {
        stPhMode.CmdType = TAF_PH_CMD_SET;
        stPhMode.PhMode = TAF_SDC_GetCurPhoneMode();

        MMA_PhModeReport(usClientId, ucOpId, stPhMode, enErrorCode);

        return;
    }


    return;
}



VOS_VOID TAF_MMA_SndAtPsInitRsltInd_PhoneMode(
    TAF_MMA_PS_INIT_RSLT_ENUM_UINT32    enPsInitRslt
)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent = VOS_NULL_PTR;

    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndAtPsInitRsltInd:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    /* ��ʼ���绰�ϱ��¼� */
    MMA_InitEventInfoOP(pstPhoneEvent);

    pstPhoneEvent->OP_PsInitRslt          = VOS_TRUE;
    pstPhoneEvent->PhoneEvent             = TAF_MMA_EVT_PS_INIT_RESULT_IND;

    /* ��д�¼��ͻ�������Ϊ�㲥�¼� */
    pstPhoneEvent->ClientId               = MMA_CLIENTID_BROADCAST;
    pstPhoneEvent->OpId                   = MMA_OP_ID_INTERNAL;

    pstPhoneEvent->ulPsInitRslt           = enPsInitRslt;

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));

    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);
    return;
}
VOS_VOID TAF_MMA_ReportPhoneModeInd_PhoneMode(VOS_VOID)
{
    TAF_PHONE_EVENT_INFO_STRU          *pstPhoneEvent           = VOS_NULL_PTR;

    /* �㲥�ϱ���ǰ��ϵͳģʽ */
    pstPhoneEvent = (TAF_PHONE_EVENT_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_PHONE_EVENT_INFO_STRU));

    if (VOS_NULL_PTR == pstPhoneEvent)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_ReportPhoneModeInd_PhoneMode:ERROR:ALLOC MEMORY FAIL.");
        return;
    }

    PS_MEM_SET(pstPhoneEvent, 0, sizeof(TAF_PHONE_EVENT_INFO_STRU));
    pstPhoneEvent->OpId = MMA_OP_ID_INTERNAL;
    pstPhoneEvent->ClientId = MMA_CLIENTID_BROADCAST;
    pstPhoneEvent->PhoneEvent = TAF_PH_EVT_OPER_MODE_IND;
    pstPhoneEvent->PhoneError = TAF_ERR_NO_ERROR;
    pstPhoneEvent->OP_OperMode = VOS_TRUE;
    pstPhoneEvent->OperMode.CmdType = TAF_PH_CMD_SET;
    pstPhoneEvent->OperMode.PhMode = TAF_SDC_GetCurPhoneMode();

    /* ���õ绰�����ϱ����� */
    MN_PH_SendMsg(pstPhoneEvent->ClientId,(VOS_UINT8*)pstPhoneEvent,sizeof(TAF_PHONE_EVENT_INFO_STRU));
    PS_MEM_FREE(WUEPS_PID_MMA, pstPhoneEvent);

    return;
}


NAS_MSCC_PIF_POWER_OFF_CAUSE_ENUM_UINT32 TAF_MMA_GetMsccPowerOffCause_PhoneMode(VOS_VOID)
{
    VOS_UINT32                          ulEntryMsgId;

    ulEntryMsgId = TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode();

    /* ͨ��״̬�������Ϣ��ȡ�ػ�ԭ��ֵ */
    if ((MMA_MMA_INTER_USIM_STATUS_CHANGE_IND == ulEntryMsgId)
     || (MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND   == ulEntryMsgId))
    {
        return NAS_MSCC_PIF_POWER_OFF_CAUSE_SIM_REMOVE;
    }

    return NAS_MSCC_PIF_POWER_OFF_CAUSE_NORMAL;
}
VOS_VOID TAF_MMA_ProcStartExpired_PhoneMode(VOS_VOID)
{
    if (MMA_MMA_INTER_POWER_INIT == TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        /* �ϱ�Э��ջ��ʼ��ʧ�� */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_FAIL);
    }

    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    TAF_MMA_SndUphyPowerOffReq();

    /* �ϱ�APP��ǰ״̬�¼� */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();
}


VOS_VOID TAF_MMA_ProcPowerOffExpired_PhoneMode(VOS_VOID)
{
    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    TAF_MMA_SndUphyPowerOffReq();

    /* �ϱ�APP��ǰ״̬�¼� */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    /* �ػ���ʱ֮������˯��ȥ */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);
}


VOS_UINT32 TAF_MMA_ProcStartComplete_PhoneMode(
    VOS_UINT32                          ulRslt
)
{
    VOS_UINT8                           ucSimStatus;
    VOS_UINT8                           ucSimLockStatus;
    TAF_MMA_PS_INIT_RSLT_ENUM_UINT32    enPsInitRslt;

    ucSimStatus                         = MMA_GetUsimStatus(VOS_FALSE);

    /* ��ȡ����״̬ */
    if ( MMA_SIM_IS_LOCK == MMA_GetMeLockStatus() )
    {
        ucSimLockStatus                 = VOS_TRUE;
    }
    else
    {
        ucSimLockStatus                 = VOS_FALSE;
    }

    /* ��������֮������˯��ͶƱ����ÿ��return��֧����������м���õ���ӿڶ��ź�������ʱC�˽���˯�� */

    /* �ϵ翪��ʱ�ϱ�AT��ǰЭ��ջ�ĳ�ʼ����� */
    if (MMA_MMA_INTER_POWER_INIT == TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        if (VOS_TRUE == ulRslt)
        {
            enPsInitRslt = TAF_MMA_PS_INIT_SUCC;
        }
        else
        {
            enPsInitRslt = TAF_MMA_PS_INIT_FAIL;
        }

        NAS_TRACE_HIGH("enPsInitRslt=%d", enPsInitRslt);

        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(enPsInitRslt);

        /* ����RIL�߼�,�����ϱ�һ�ο�״̬ */
        TAF_MMA_SndAtIccStatusInd(ucSimStatus, ucSimLockStatus);
    }



    /* ����ʧ�� */
    if (VOS_FALSE == ulRslt)
    {
        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_UNSPECIFIED_ERROR);

        TAF_MMA_SndUphyPowerOffReq();

        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* ����״̬���˳���Ϣ */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();

        /* �յ�rrmm-start-cnf��Ϣ��
         ��ǰ���Զ�������
            MMA��Ҫ�ͷ�ͶƱ,��AS����plmn_serach_reqʱ,��OAMͶ����˯��Ʊ,
         ��ǰ�Ƿ��Զ�������
            MMA��Ҫ�ͷ�ͶƱ,����˯��*/

        if (VOS_TRUE == TAF_MMA_GetMmaLogInfoFlag())
        {
            (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartComplete_PhoneMode:result = %d\n", ulRslt);
            (VOS_VOID)vos_printf("\n*TAF_MMA_ProcStartComplete_PhoneMode:PWRCTRL_SLEEP_NAS,TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK\n");
        }

        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);


        return VOS_TRUE;
    }

    /* �����ɹ�Ӧ�������ô�״̬,��Ϊ������attach�ȶ������жϴ�״̬ */
    g_StatusContext.ulFsmState          = STA_FSM_ENABLE;

    /* ����SDC�е�SIM����ע��״̬ */
    TAF_MMA_UpdateSimRegStatus();

    /* MMA֪ͨTAF�㿪�� */
    TAF_MMA_SndPowerOnIndMsg();

    /* ͨ��״̬�������Ϣ�ж��Ƿ�Ϊ�ϵ翪�� */
    if (MMA_MMA_INTER_POWER_INIT != TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode())
    {
        TAF_MMA_ProcStartCnfSucc_NoPowerInit_PhoneMode();

        return VOS_TRUE;
    }

    /* �ϵ翪���ɹ��Ľ������ */
    TAF_MMA_ProcStartCnfSucc_PowerInit_PhoneMode();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_ProcPowerOffComplete_PhoneMode(VOS_VOID)
{
    VOS_UINT8                           ucPhoneMode;
    VOS_UINT32                          ulEntryMsgId;
#if (FEATURE_MULTI_MODEM == FEATURE_ON)
    MMA_MTC_CURR_CAMP_PLMN_INFO_IND_STRU    stSndMtcPlmnInfo;
#endif

    MMA_InitCm();


    /* ������֪ͨMSGһ��CS���������ػ�ʱ����Ҫ��֪ͨMSG��STKҪ��ػ�ʱҲ֪ͨһ�� */
    if (VOS_TRUE == TAF_SDC_GetSvlteSupportFlag())
    {
        TAF_MMA_SndStkCsServiceChangeNotify(TAF_CS_OFF);
    }

    /* �ϱ�����״̬�仯 */
    if (TAF_SDC_REPORT_SRVSTA_NO_SERVICE != TAF_SDC_GetServiceStatus())
    {
        TAF_SDC_SetServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);
        TAF_MMA_ReportSrvStatus();
    }

    if (VOS_TRUE == TAF_SDC_IsPlatformSupport3Gpp())
    {
        /* �ϱ�ϵͳģʽ��ģʽ�仯 */
        Sta_ModeChangeEventReport(TAF_PH_INFO_NONE_RAT, TAF_SYS_SUBMODE_NONE);

        TAF_MMA_SndUphyPowerOffReq();

#if  ( FEATURE_MULTI_MODEM == FEATURE_ON )
        TAF_MMA_SndMtcPowerStateInd(MTC_MODEM_POWER_OFF);

        if (VOS_TRUE == TAF_SDC_GetUtranSkipWPlmnSearchFlag())
        {
            PS_MEM_SET(&stSndMtcPlmnInfo, 0, sizeof(stSndMtcPlmnInfo));

            stSndMtcPlmnInfo.enRatMode             = MTC_RATMODE_BUTT;
            stSndMtcPlmnInfo.ucIsForbiddenPlmnFlag = VOS_FALSE;
            stSndMtcPlmnInfo.ucPsAttachAllowFlag   = TAF_SDC_GetPsAttachAllowFlg();
            stSndMtcPlmnInfo.stPlmnId.ulMcc        = TAF_SDC_INVALID_MCC;
            stSndMtcPlmnInfo.stPlmnId.ulMnc        = TAF_SDC_INVALID_MCC;
            TAF_MMA_SndMtcCurrCampPlmnInfoInd(&stSndMtcPlmnInfo);
        }
#endif
    }

    ulEntryMsgId = TAF_MMA_GetCurrFsmEntryMsgId_PhoneMode();

    /* ͨ�������Ϣ�ж��ǿ�״̬�ı�����Ĺػ� */
    if ((MMA_MMA_INTER_USIM_STATUS_CHANGE_IND == ulEntryMsgId)
     || (MMA_MMA_SIM_LOCK_STATUS_CHANGE_IND   == ulEntryMsgId))
    {
        TAF_MMA_ProcPowerOffCnf_UsimStatusChange_PhoneMode();

        /* ǰ���Ѿ��ڷ��ڲ��������̣��ô���ͶƱ˯�߲���Ҫ */

        return VOS_TRUE;
    }

    /* ��ȡOM��AT���õ�ģʽ */
    ucPhoneMode             = TAF_MMA_GetCurrFsmEntryMsgPhoneMode_PhoneMode();

    /* ���µ�ǰ���ֻ�ģʽ */
    TAF_SDC_SetCurPhoneMode(ucPhoneMode);

    TAF_MMA_ProcPowerOffCnfWithSpecPhoneMode_PhoneMode(ucPhoneMode);

    /* ��APP�ϱ�Ӧ���¼�*/
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_SUCC);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    /* ����ͶƱ:�յ��ػ��ظ�֮������˯��ȥ */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    return VOS_TRUE;
}
VOS_VOID TAF_MMA_ProcGetGeoNoSimStartReq_PhoneMode(VOS_VOID)
{
    TAF_MMA_RAT_ORDER_STRU              stSndRatPrioList;
    TAF_MMA_RAT_ORDER_STRU             *pstRatPrioList = VOS_NULL_PTR;

    g_StatusContext.ulFsmState = STA_FSM_RESTART;

    NAS_TRACE_HIGH("MMA Get Geo No Sim Start Begin!!!");

    /* ��ȡ���뼼����Ϣ */
    pstRatPrioList = TAF_MMA_GetRatPrioListAddr();

    PS_MEM_SET(&stSndRatPrioList, 0, sizeof(TAF_MMA_RAT_ORDER_STRU));

    stSndRatPrioList.ucRatOrderNum = pstRatPrioList->ucRatOrderNum;
    PS_MEM_CPY(stSndRatPrioList.aenRatOrder,
               pstRatPrioList->aenRatOrder,
               pstRatPrioList->ucRatOrderNum);

    TAF_MMA_GetAvailablePlmnRatPrio(&stSndRatPrioList);

    /* ���Ϳ��������MSCC */
    (VOS_VOID)TAF_MMA_SndMsccStartReq(&stSndRatPrioList,
                            NAS_MSCC_PIF_CARD_STATUS_ABSENT,
                            NAS_MSCC_PIF_CARD_STATUS_ABSENT,
                            VOS_FALSE);

    /* Ǩ��״̬���ȴ�MSCC��ȡ������Ŀ����ظ� */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_START_CNF);

    /* ����������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF, TI_TAF_MMA_WAIT_MSCC_START_CNF_LEN);

    return;
}


VOS_VOID TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode(VOS_VOID)
{
    /* ����ͶƱ:�ػ�ʱ������˯��,�յ�MSCC�Ĺػ��ظ�֮���� */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_LOCK(PWRCTRL_SLEEP_NAS);

    NAS_TRACE_HIGH("MMA Get Geo No Sim PowerOff Begin!!!");

    /* ����STOP״̬��־��*/
    g_StatusContext.ulFsmState = STA_FSM_STOP;

    TAF_MMA_SndMsccPowerOffReq(NAS_MSCC_PIF_POWER_OFF_CAUSE_NORMAL);

    /* Ǩ��״̬���ȴ�MSCC��ȡ������Ĺػ��ظ� */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_GET_GEO_WAIT_MSCC_POWER_OFF_CNF);

    /* ����������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF, TI_TAF_MMA_WAIT_MSCC_POWER_OFF_CNF_LEN);

    return;
}


VOS_VOID TAF_MMA_ProcStopGetGeoReq_PhoneMode(VOS_VOID)
{
    NAS_TRACE_HIGH("MMA Stop Get Geo Begin!!!");

    /* ����ֹͣ��ȡ������������MSCC */
    TAF_MMA_SndMsccStopGetGeoReq();

    /* Ǩ��״̬���ȴ�MSCC��ȡ������Ŀ����ظ� */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_STOP_GET_GEO_CNF);

    /* ����������ʱ�� */
    TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF, TAF_MMA_WAIT_STOP_GET_GEO_CNF_LEN);

    return;
}
VOS_UINT32 TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_GET_GEO_CNF_STRU      *pstGetGeoCnf = VOS_NULL_PTR;

    pstGetGeoCnf = (NAS_MSCC_PIF_GET_GEO_CNF_STRU *)pstMsg;

    NAS_TRACE_HIGH("Rcv Mscc Get Geo Cnf!!!");

    /* ֹͣ��ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF);

    /* ����PLMN��Ϣ,����ʱ��� */
    TAF_MMA_UpdateGeoInfo((TAF_SDC_PLMN_ID_STRU *)(&(pstGetGeoCnf->stPlmnId)));

    /* ��״̬�Ѿ��ϱ�����ػ�����״̬û�ϱ�Ҳ���˳�״̬���������ȴ���״̬�ϱ� */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {
        TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

        return VOS_TRUE;
    }

    /* �����״̬��û���ϱ�����״̬Ǩ�Ƶ���ȡ��������ɵȴ���״̬�ϱ���״̬
       ��ǰ�ȿ�״̬�ϱ��Ķ�ʱ������������ */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_GET_GEO_CMP_WAIT_USIM_STATUS_IND);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvTiWaitMsccGetGeoCnfExpired_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo Timeout!!!");

    /* ��״̬�Ѿ��ϱ������ϵ�ǰ�Ļ�ȡ����������� */
    if (TAF_SDC_USIM_STATUS_BUTT != TAF_SDC_GetSimStatus())
    {
        TAF_MMA_ProcStopGetGeoReq_PhoneMode();

        return VOS_TRUE;
    }

    /* ��״̬��û���ϱ������˳�״̬���������ȴ���״̬�ϱ� */

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA In Get Geo Status, Rcv PIH Usim Status Ind!!!");

    /* ֹͣ�ȴ���״̬�ϱ���ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

    /* ����λ����Ϣ��δ��ȡ��ϣ���ȡ������Ķ�ʱ������������У���ô�϶��ǻ�ȡ������Ķ�ʱ����ʱֹͣ��.
       ���յ���״̬�ϱ��󣬻�ȡ������Ķ�ʱ���Ѿ���ʱ����Ҫ��ϻ�ȡ���������� */
    if (TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF))
    {
        TAF_MMA_ProcStopGetGeoReq_PhoneMode();

        return VOS_TRUE;
    }

    /* û���յ���ȡ������Ľ���ظ���������ȴ���ȡ������Ľ�� */

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_WaitMsccGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* NOTE: �ö�ʱ����ʱ�϶��ǵȿ�״̬�ϱ���ʱ����ʱ��
             ��Ϊ������ʼ���ɹ������GetGeo������ */

    NAS_TRACE_HIGH("MMA In Get Geo Status, PIH Usim Status Ind Timeout!!!");

    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);

    /* ���TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF�����о�ֹͣ */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF);

    /* ��ȡ���������̻�δ��������Ҫ��ϴ��� */
    TAF_MMA_ProcStopGetGeoReq_PhoneMode();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoCmpWaitUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA In Get Geo Cmp Status, Rcv PIH Usim Status Ind!!!");

    /* ֹͣ�ȴ���״̬�ϱ���ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

    /* �յ���״̬�ϱ���������޿��ػ� */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoCmpWaitUsimStatusInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA In Get Geo Cmp Status, PIH Usim Status Ind Timeout!!!");

    /* NOTE: �ö�ʱ����ʱ�϶��ǵȿ�״̬�ϱ���ʱ����ʱ��
             ��Ϊ������ʼ���ɹ������GetGeo������ */
    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);

    /* ���ϱ���ʱ������޿��ػ� */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMsccStopGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Stop Get Geo Success!!!");

    /* ֹͣ��ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF);

    /* ֹͣ���ȡ����������̺󣬽����޿��ػ� */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMsccGetGeoCnf_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_GET_GEO_CNF_STRU      *pstGetGeoCnf = VOS_NULL_PTR;

    pstGetGeoCnf = (NAS_MSCC_PIF_GET_GEO_CNF_STRU *)pstMsg;

    /* ֹͣ��ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_STOP_GET_GEO_CNF);

    /* ����PLMN��Ϣ,����ʱ��� */
    TAF_MMA_UpdateGeoInfo((TAF_SDC_PLMN_ID_STRU *)(&(pstGetGeoCnf->stPlmnId)));

    NAS_TRACE_HIGH("MMA In Stop Get Geo Status, Rcv Get Geo Cnf!!!");

    /* �޿��ػ����� */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv PIH Usim Status Ind!!!");

    /* TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT��ʱ���Ѿ�ֹͣ����������������չʹ�� */

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTiWaitMsccStopGetGeoCnfExpired_PhoneMode_WaitMsccStopGetGeoCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Stop Get Geo Timeout!!!");

    /* ֹͣ���ȡ����������̳�ʱ��Ҳ�����޿��ػ� */
    TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMsccStartCnf_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_START_CNF_STRU            *pstStartCnf = VOS_NULL_PTR;
    TAF_SDC_USIM_STATUS_ENUM_UINT8      enSimStatus;

    pstStartCnf                         = (MSCC_MMA_START_CNF_STRU*)pstMsg;
    enSimStatus                         = TAF_SDC_GetSimStatus();

    /* ֹͣ������ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_MSCC_START_CNF);

    /* ��ȡ��������޿������ɹ�����Ҫ�ϱ�PSINIT��
       ��ʼ��ȡ�����룬״̬Ǩ�ƣ�����ȴ���ʱ�� */
    if (NAS_MSCC_PIF_START_RESULT_SUCC == pstStartCnf->ulResult)
    {
        NAS_TRACE_HIGH("MMA Get Geo No Sim Start Success!!!");

        /* ������ϱ���ʱ���򲻻�ȡ������ */
        if (TAF_SDC_USIM_STATUS_READY_TIMEROUT == enSimStatus)
        {
            TAF_MMA_ProcGetGeoNoSimPowerOffReq_PhoneMode();
        }
        else
        {
            /* ���ͻ�ȡ����λ����Ϣ�����MSCC */
            TAF_MMA_SndMsccGetGeoReq();

            /* Ǩ��״̬���ȴ�MSCC�Ļ�ȡ����λ����Ϣ�Ļظ� */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_PHONE_MODE_STA_WAIT_MSCC_GET_GEO_CNF);

            /* ����������ʱ�� */
            TAF_MMA_StartTimer(TI_TAF_MMA_WAIT_MSCC_GET_GEO_CNF, TAF_MMA_GetGeoTimerLen());
        }
    }
    else
    {
        /* �ϱ�PSINIT */
        TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_FAIL);

        TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_UNSPECIFIED_ERROR);

        TAF_MMA_ReportPhoneModeCnf_PhoneMode();

        /* ����״̬���˳���Ϣ */
        TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

        /* �˳�״̬�� */
        TAF_MMA_FSM_QuitSubFsm();

        NAS_TRACE_HIGH("MMA Get Geo No Sim Start Fail!!!");

        /* �յ�rrmm-start-cnf��Ϣ��
         ��ǰ���Զ�������
            MMA��Ҫ�ͷ�ͶƱ,��AS����plmn_serach_reqʱ,��OAMͶ����˯��Ʊ,
         ��ǰ�Ƿ��Զ�������
            MMA��Ҫ�ͷ�ͶƱ,����˯��*/

        TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv PIH Usim Status Ind!!!");

    /* ֹͣ�ȴ���״̬�ϱ���ʱ�� */
    TAF_MMA_StopTimer(TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTiWaitMsccStartCnfExpired_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo No Sim Start Timeout!!!");

    /* �ϱ�Э��ջ��ʼ��ʧ�� */
    TAF_MMA_SndAtPsInitRsltInd_PhoneMode(TAF_MMA_PS_INIT_FAIL);

    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    /* �ϱ�APP��ǰ״̬�¼� */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvTiWaitExternalModuleInitExpired_PhoneMode_GetGeoWaitMsccStartCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo Start Timeout!!!");

    TAF_SDC_SetUsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);
    TAF_SDC_SetCsimStatus(TAF_SDC_USIM_STATUS_READY_TIMEROUT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMsccPowerOffCnf_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo No Sim PowerOff Success!!!");

    /* ���ڲ��������� */
    TAF_MMA_ProcStartReq_PhoneMode();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv PIH Usim Status Ind!!!");

    /* ��ʱ��TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT�Ѿ�ֹͣ������������������չ */

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvTiWaitMsccPowerOffCnfExpired_PhoneMode_GetGeoWaitMsccPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("MMA Get Geo No Sim PowerOff Timeout!!!");

    TAF_MMA_SetCurPhoneErrorCode_PhoneMode(TAF_ERR_TIME_OUT);

    /* �ϱ�APP��ǰ״̬�¼� */
    TAF_MMA_ReportPhoneModeCnf_PhoneMode();

    /* ����״̬���˳������Ϣ */
    TAF_MMA_SndPhoneModeRsltInd(TAF_MMA_PHONE_MODE_RESULT_POWER_OFF_FAIL);

    /* �˳�״̬�� */
    TAF_MMA_FSM_QuitSubFsm();

    /* �ػ���ʱ֮������˯��ȥ */
    TAF_DRVAPI_PWRCTRL_SLEEPVOTE_UNLOCK(PWRCTRL_SLEEP_NAS);

    return VOS_TRUE;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



