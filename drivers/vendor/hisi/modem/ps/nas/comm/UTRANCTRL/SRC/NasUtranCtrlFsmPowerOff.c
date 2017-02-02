



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"
#include "PsTypeDef.h"
#include "NasUtranCtrlFsmPoweroffTbl.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlCtx.h"
#include "NasMmlCtx.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasUtranCtrlCommFunc.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_POWEROFF_C

#if (FEATURE_ON == FEATURE_UE_MODE_TDS)
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/


/*****************************************************************************
  3 �궨��
*****************************************************************************/


VOS_UINT32 NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�W�¹ػ��ظ���֪ͨTDģ��ػ� */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDģ�Ĺػ��ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN);

    /* ���������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�W�¹ػ��ظ���֪ͨTDģ��ػ� */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDģ�Ĺػ��ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_TD_POWEROFF_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF_LEN);

    /* ���������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�TD�¹ػ��ظ���֪ͨWģ��ػ� */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�Wģ�Ĺػ��ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN);

    /* ���������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������Ĺػ��ɹ���Ϣ��Ϊ״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �յ�TD�¹ػ��ظ���֪ͨWģ��ػ� */
    NAS_UTRANCTRL_SndGuAsPowerOffReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�Wģ�Ĺػ��ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_POWER_OFF_STA_WAIT_WAS_POWEROFF_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF_LEN);

    /* ���������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitWasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRLֹͣ�ȴ�WAS�ظ���ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_POWER_OFF_CNF);

    /* UTRANCTRL״̬���ص�MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* �������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32  NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitWasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitWasPowerOffCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_WaitWasPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_POWER_OFF_CNF_STRU             stNasPowerOffCnf;
    VOS_UINT32                          ulPowerOffEventType;


    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPowerOffCnfExpired_PowerOff_WaitWasPowerOffCnf: ENTERED");

    /* ����ػ��ظ���Ϣ */
    NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg(WUEPS_PID_WRR,
                                          WUEPS_PID_MMC,
                                          &stNasPowerOffCnf);

    ulPowerOffEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)&stNasPowerOffCnf );

    /* �������Ĺػ��ظ���Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulPowerOffEventType,
                                           (struct MsgCB *)&stNasPowerOffCnf);

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* UTRANCTRL״̬���ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣδ�����������MMC�������� */
    return VOS_FALSE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvTdPowerOffCnf_PowerOff_WaitTdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* UTRANCTRLֹͣ�ȴ�TD�ظ���ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_POWER_OFF_CNF);

    /* �ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32  NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitTdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPowerOffCnf_PowerOff_WaitTdPowerOffCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_WaitTdPowerOffCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_POWER_OFF_CNF_STRU             stNasPowerOffCnf;
    VOS_UINT32                          ulPowerOffEventType;


    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPowerOffCnfExpired_PowerOff_WaitTdPowerOffCnf: ENTERED");

    /* ����ػ��ظ���Ϣ */
    NAS_UTRANCTRL_BuildRrMmPowerOffCnfMsg(WUEPS_PID_WRR,
                                          WUEPS_PID_MMC,
                                          &stNasPowerOffCnf);

    ulPowerOffEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)&stNasPowerOffCnf );

    /* �����Ĺ��ĳ�ʱ��Ϣ�ŵ���������� */
    NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(ulPowerOffEventType,
                                           (struct MsgCB *)&stNasPowerOffCnf);

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �ص�main״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��ǰ��Ϣ�������MMC״̬������ */
    return VOS_FALSE;
}

#endif  /* end of #if (FEATURE_ON == FEATURE_UE_MODE_TDS) */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

