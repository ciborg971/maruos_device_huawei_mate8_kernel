

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"

#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlFsmMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmModeChangeTbl.h"
#include "NasUtranCtrlFsmModeChange.h"
#include "NasMmlLib.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_MODE_CHANGE_C

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
  3 ����ʵ��
*****************************************************************************/
#if (FEATURE_ON == FEATURE_UE_MODE_TDS)

VOS_UINT32 NAS_UTRANCTRL_RcvWasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  ���ֵ�ǰ�����Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* WΪ��ģʱ������ǰUtranMode֪ͨL/G/TD */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
    }

    /* ���ƽֻ̨֧��W/TD�е�һ�����������߶���֧�֣�����NAS_UTRANCTRL_MsgProc��NAS_UTRANCTRL_ProcessMmcMsg����VOS_FALSE
       �������Utran��״̬������Դ˴�����Ҫ�ж�ƽ̨�Ƿ�֧��W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /*Ǩ���ȴ���ģ�ظ�״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*���ȴ���ģ�ظ���ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  ���ֵ�ǰ�����Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* TDΪ��ģʱ������ǰUtranMode֪ͨL/G/W */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
    }
#endif

    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
    }

    /* ���ƽֻ̨֧��W/TD�е�һ�����������߶���֧�֣�����NAS_UTRANCTRL_MsgProc��NAS_UTRANCTRL_ProcessMmcMsg����VOS_FALSE
       �������Utran��״̬������Դ˴�����Ҫ�ж�ƽ̨�Ƿ�֧��W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    /*Ǩ���ȴ���ģ�ظ�״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*���ȴ���ģ�ظ���ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvGasSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  ���ֵ�ǰ�����Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* GΪ��ģʱ������ǰUtranMode֪ͨL/W/TD */
#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE == NAS_MML_IsPlatformSupportLte())
    {
        NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);
    }
#endif

    /* ���ƽֻ̨֧��W/TD�е�һ�����������߶���֧�֣�����NAS_UTRANCTRL_MsgProc��NAS_UTRANCTRL_ProcessMmcMsg����VOS_FALSE
       �������Utran��״̬������Դ˴�����Ҫ�ж�ƽ̨�Ƿ�֧��W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /*Ǩ���ȴ���ģ�ظ�״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*���ȴ���ģ�ظ���ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_UTRANCTRL_RcvLmmSysInfo_ModeChange_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8 enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    /*  ���ֵ�ǰ�����Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* LΪ��ģʱ������ǰUtranMode֪ͨG/W/TD */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
        NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);
    }

    /* ���ƽֻ̨֧��W/TD�е�һ�����������߶���֧�֣�����NAS_UTRANCTRL_MsgProc��NAS_UTRANCTRL_ProcessMmcMsg����VOS_FALSE
       �������Utran��״̬������Դ˴�����Ҫ�ж�ƽ̨�Ƿ�֧��W/TD */
    NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
    NAS_UTRANCTRL_SetWaitSlaveModeUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /*Ǩ���ȴ���ģ�ظ�״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_SLAVEMODE_CNF);

    /*���ȴ���ģ�ظ���ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF_LEN);

    return VOS_TRUE;
}
#endif


VOS_UINT32 NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* ���WΪ��ģ��������ֱ�ӷ��� */
    if (NAS_UTRANCTRL_MASTER_MODE_WCDMA == enMasterMode)
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* �յ�WAS��UTRAN MODE CNF��Ϣ������ȴ���־ */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_WAS_UTRAN_MODE_CNF);

    /* �յ���ģ�Ļظ��󣬵��ô����ģ�ظ��ĺ��� */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* ���TDΪ��ģ��������ֱ�ӷ��� */
    if (NAS_UTRANCTRL_MASTER_MODE_TDSCDMA == enMasterMode)
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* �յ�TDRRC��UTRAN MODE CNF��Ϣ������ȴ���־ */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_TD_UTRAN_MODE_CNF);

    /* �յ���ģ�Ļظ��󣬵��ô����ģ�ظ��ĺ��� */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvGasUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* ���GΪ��ģ��������ֱ�ӷ��� */
    if (NAS_UTRANCTRL_MASTER_MODE_GSM == enMasterMode)
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* �յ�GAS��UTRAN MODE CNF��Ϣ������ȴ���־ */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_GAS_UTRAN_MODE_CNF);

    /* �յ���ģ�Ļظ��󣬵��ô����ģ�ظ��ĺ��� */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  enMasterMode;

    enMasterMode = NAS_UTRANCTRL_GetMasterMode_ModeChange();

    /* ���LΪ��ģ��������ֱ�ӷ��� */
    if (NAS_UTRANCTRL_MASTER_MODE_LTE == enMasterMode)
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvLmmUtranModeCnf_ModeChange_WaitSlaveModeCnf: ENTERED");

        return VOS_TRUE;
    }

    /* �յ�TDRRC��UTRAN MODE CNF��Ϣ������ȴ���־ */
    NAS_UTRANCTRL_ClearWaitSlaveUtranModeCnfFlg_ModeChange(NAS_UTRANCTRL_WAIT_LMM_UTRAN_MODE_CNF);

    /* �յ���ģ�Ļظ��󣬵��ô����ģ�ظ��ĺ��� */
    NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(enMasterMode);

    return VOS_TRUE;
}

#endif


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf: ENTERED");

    /* ����ģ��ģʽ֪ͨ */
    NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(NAS_UTRANCTRL_GetMasterMode_ModeChange());

    /* ���ȴ���ģ�ظ���ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF_LEN);

    /* Ǩ���ȴ���ģ�ظ�״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF);

    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvMasterModeCnf_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU                           *pstEntryMsg;

    /* ͣ�ȴ���ģ�ظ���ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF);

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg( pstEntryMsg->ulEventType,
                                     (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* ���û�����Ϣ��Ч��־ */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �˳�MODE CHANGE״̬�����л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitMasterModeCnfExpired_ModeChange_WaitMasterModeCnf: ENTERED");

    /* ������еȴ�ģʽ����ظ��ı�־ */
    NAS_UTRANCTRL_ClearAllWaitAsUtranModeCnfFlg_ModeChange();

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg( pstEntryMsg->ulEventType,
                                     (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    /* ���û�����Ϣ��Ч��־ */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �˳�MODE CHANGE״̬�����л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    return VOS_FALSE;
}
VOS_VOID NAS_UTRANCTRL_ProcSlaveModeCnf_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
)
{
    VOS_UINT8                           ucWaitSlaveModeUtranModeCnfFlg;

    ucWaitSlaveModeUtranModeCnfFlg = NAS_UTRANCTRL_GetWaitSlaveModeUtranModeCnfFlg_ModeChange();

    if (NAS_UTRANCTRL_WAIT_UTRAN_MODE_CNF_NULL != ucWaitSlaveModeUtranModeCnfFlg)
    {
        return;
    }

    /* ����Ѿ�����������ģ�Ļظ���ͣ�ȴ���ģ�ظ���ʱ��,����ģ��ģʽ�������
       ���ȴ���ģ�ظ���ʱ����Ǩ���ȴ���ģ�ظ�״̬ */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_SLAVEMODE_UTRAN_MODE_CNF);

    NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(enMasterMode);

    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_MODE_CHANGE_STA_WAIT_MASTERMODE_CNF);

    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF, TI_NAS_UTRANCTRL_WAIT_MASTERMODE_UTRAN_MODE_CNF_LEN);

    return;
}


VOS_VOID NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange(
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode
)
{

    NAS_UTRANCTRL_UTRAN_MODE_ENUM_UINT8                      enCurrUtranMode;

    enCurrUtranMode = NAS_UTRANCTRL_GetCurrUtranMode();

    switch (enMasterMode)
    {
        case NAS_UTRANCTRL_MASTER_MODE_WCDMA:
            NAS_UTRANCTRL_SndGuAsUtranModeReq(WUEPS_PID_WRR, enCurrUtranMode);
            break;

        case NAS_UTRANCTRL_MASTER_MODE_TDSCDMA:
            NAS_UTRANCTRL_SndGuAsUtranModeReq(TPS_PID_RRC, enCurrUtranMode);
            break;

        case NAS_UTRANCTRL_MASTER_MODE_GSM:
            NAS_UTRANCTRL_SndGuAsUtranModeReq(UEPS_PID_GAS, enCurrUtranMode);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_UTRANCTRL_MASTER_MODE_LTE:
            NAS_UTRANCTRL_SndLmmUtranModeReq(enCurrUtranMode);
            break;
#endif

        default:
            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_SndMasterModeUtranModeReq_ModeChange: unexpected master mode.");
            break;
    }

    return;
}
NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8  NAS_UTRANCTRL_GetMasterMode_ModeChange(VOS_VOID)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU                           *pstEntryMsg;
    MSG_HEADER_STRU                                        *pstHead;
    NAS_UTRANCTRL_MASTER_MODE_ENUM_UINT8                    enMasterMode;

    /*  ȡ����������Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();
    pstHead     = (MSG_HEADER_STRU *)(pstEntryMsg->aucEntryMsgBuffer);

    switch (pstHead->ulSenderPid)
    {
        case WUEPS_PID_WRR:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_WCDMA;
            break;

        case TPS_PID_RRC:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_TDSCDMA;
            break;

        case UEPS_PID_GAS:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_GSM;
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case PS_PID_MM:
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_LTE;
            break;
#endif

        default:
            /* �쳣��ӡ */
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitSlaveModeUtranModeCnfExpired_ModeChange_WaitSlaveModeCnf: ENTERED");
            enMasterMode = NAS_UTRANCTRL_MASTER_MODE_BUTT;
            break;
    }

    return enMasterMode;
}
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

