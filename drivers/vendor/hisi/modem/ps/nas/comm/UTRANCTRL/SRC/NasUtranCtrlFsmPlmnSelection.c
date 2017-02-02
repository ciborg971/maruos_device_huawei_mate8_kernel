

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "NasComm.h"
#include "MsccMmcInterface.h"
#include "NasUtranCtrlCtx.h"
#include "NasUtranCtrlCommFunc.h"
#include "NasUtranCtrlFsmMain.h"
#include "Nasrrcinterface.h"
#include "NasUtranCtrlProcNvim.h"
#include "NasMmcTimerMgmt.h"
#include "NasUtranCtrlFsmPlmnSelectionTbl.h"
#include "NasMmlLib.h"
#include "NasMmcComFunc.h"

#include "NasMmcFsmPlmnSelection.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ��������
*****************************************************************************/

#define    THIS_FILE_ID        PS_FILE_ID_NAS_UTRANCTRL_FSM_PLMN_SELECTION_C

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

VOS_UINT32 NAS_UTRANCTRL_RcvWasPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF))
    {
        /* ͣ��ʱ�� */
        NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);
        
        /* ��WAS����ֹͣ�������� */
        NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�wasֹͣ�����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

        return VOS_TRUE;
    }

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchTdsIndMsg_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* tds������ʧ����Ҫ��w�¼������� ����tds */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��WAS����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�ֹͣW������ȥTD������״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF_SEARCH_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}
VOS_UINT32 NAS_UTRANCTRL_RcvWasRrMmRelInd_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �������������Ϣ���浽״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}
VOS_UINT32 NAS_UTRANCTRL_RcvTdPlmnSrchCnf_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* TD������ʧ�ܸ���Я���������б�Ϊ�յ���������˳���ǰ��������,
       ������Ҫ����TD��W������ */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬�������Ϣ */
    NAS_UTRANCTRL_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��TD����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�ֹͣTD������ȥW������״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF_SEARCH_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg     = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg  = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnStopCnfSearchTD: ENTERED");

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ������ʧ����Ϣ����MMC���� */
        return VOS_FALSE;
    }

    /* W������ʧ����Ҫ��TD�¼������� ����WAS */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ����������MMC״̬������ */
    return VOS_TRUE;

}
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnfSearchTD: ENTERED");

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ������ʧ����Ϣ����MMC���� */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg     = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    pstSrchCnfMsg     = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC�������õ�ǰΪTDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* �����ǰ�����ڴ�ϣ���ǰ��Ҫ��������ǰģ�������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;


    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnfSearchW: ENTERED");

    /* �����ǰ���ڴ�ϣ���ֱ���˳�ѡ��״̬�� */
    if ( VOS_TRUE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* �л���MAIN״̬�� */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ������ʧ����Ϣ����MMC���� */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�w������,��TD���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TD����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf()
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;
    
    if (VOS_PID_TIMER == pstMsgHeader->ulSenderPid)
    {
        return VOS_TRUE;
    }

    if (pstEntryMsg->ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_SKIP_SEARCH_W_IND))
    {
        return VOS_TRUE;
    }

    if (pstEntryMsg->ulEventType == NAS_UTRANCTRL_BuildEventType(WUEPS_PID_MMC, MMCMMC_INTER_SKIP_SEARCH_TDS_IND))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    pstRrmmSuspendCnf  = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF);

    /* ״̬����ϱ�ǲ����� */
    if (VOS_FALSE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ��TDRRC����ָ���������� */
        NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȵ�TDRRC�����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_SEARCH_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF_LEN);

        /* ��Ϣ������ɲ����������MMC״̬������ */
        return VOS_TRUE;
    }

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();



    /* �����ǰ�������ϢΪ��ʱ����ʱ,����MMC���͵��ڲ�SKIP ����W��Ϣ������Ҫ���������ظ�ʧ����Ϣ */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {

        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnf: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF);

    /* ״̬����ϱ�ǲ����� */
    if (VOS_FALSE == NAS_UTRANCTRL_GetAbortFlg_PlmnSelection())
    {
        /* ��WAS����ָ���������� */
        NAS_UTRANCTRL_SndGuAsSpecPlmnSearchReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�WAS�����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_SEARCH_CNF);

        /* ������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* �����ǰ�������ϢΪ��ʱ����ʱ������MMC���͵��ڲ�SKIP ����TDS��Ϣ,����Ҫ���������ظ�ʧ����Ϣ */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnf: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ��������ɹ� */
    if ((RRC_PLMN_SEARCH_RLT_SPEC           == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstSrchCnfMsg->ulSearchRlt))
    {
        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC�������õ�ǰΪFDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* ���������б�����й������� */
    if (MMCMMC_INTER_SKIP_SEARCH_TDS_IND != pstMsgHeader->ulMsgName)
    {
        NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                                 NAS_UTRANCTRL_GetSpecTdMccList(),
                                                 &(pstSrchCnfMsg->PlmnIdList));

        /* �����й�����������utran����ģʽ */
        if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
        {
            NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
        }
        else if ((0 != pstSrchCnfMsg->PlmnIdList.ulHighPlmnNum)
              || (0 != pstSrchCnfMsg->PlmnIdList.ulLowPlmnNum))
        {
            /* δ�ѵ��й����粢��WЯ���ǿ��б�,���¹���ģʽΪFDD */
            NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);
        }
        else
        {
            /* WЯ�����б��޸Ĺ���ģʽ */
        }
    }

    /* ���ݵ�ǰ����ģʽΪTDD����Ҫ�ص�TD�� */
    if (NAS_UTRANCTRL_UTRAN_MODE_TDD   == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȴ���TDʱW�Ĺ���ظ�״̬ */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* ״̬���л���MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvInterAbortUtranCtrlPlmnSearchReq_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ����utran modeΪfdd��utranctrl ����״̬���˳�����Ϣ��mmc��������֪ͨ���������mmc���� */
    NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

    /* ֪ͨmmc MMCMMC_INTER_ABORT_UTRAN_CTRL_PLMN_SEARCH_CNF*/
    NAS_MMC_SndInterAbortUtranCtrlPlmnSearchCnfMsg();

    /* ״̬���л���MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    return VOS_TRUE;
}






VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnSearchCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvRrmmRelInd_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ǰδ�ѵ��й�������,����Ϊ��Ȼ��TD��,ģʽ���ֲ��� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȴ���TDʱW�Ĺ���ظ�״̬ */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��WAS����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WAS�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnSearchCnfExpired_PlmnSelection_WaitWasPlmnSearchCnf: ENTERED");

    /* ֹͣWAS���� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WASֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvMmcInterSkipSearchWasIndMsg_PlmnSelection_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ͣ��ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_SEARCH_CNF);
    
    /* ֹͣWAS���� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�WASֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* ���ָ�������ɹ���history�ѳɹ� */
    if ((RRC_PLMN_SEARCH_RLT_SPEC           == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_SUCC   == pstSrchCnfMsg->ulSearchRlt))
    {
        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }


    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪTDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* ���������б�����й������� */
    NAS_UTRANCTRL_UpdateSearchedSpecTdMccFLg(NAS_UTRANCTRL_GetSpecTdMccListNum(),
                                             NAS_UTRANCTRL_GetSpecTdMccList(),
                                             &(pstSrchCnfMsg->PlmnIdList));

    /* �����й�����������utran����ģʽ */
    if (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);
    }

    /* ���ݵ�ǰ����ģʽΪFDD����Ҫ�ص�W�� */
    if (NAS_UTRANCTRL_UTRAN_MODE_FDD   == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        /* ����TD */
        NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

        /* Ǩ��״̬���ȴ���WʱTD�Ĺ���ظ�״̬ */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }

    /* ״̬���л���MAIN */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}



VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPlmnSearchCnf_PlmnSelection_WaitTdPlmnSearchCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_SEARCH_CNF);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��TDRRC����ֹͣ�������� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRCֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnSearchCnfExpired_PlmnSelection_WaitTdPlmnSearchCnf: ENTERED");

    /* ֹͣTDRRC���� */
    NAS_UTRANCTRL_SndGuAsPlmnStopReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRCֹͣ�����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF, TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    if ((WUEPS_PID_MMC == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName))
    {
        /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
        NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

        /* Ǩ��״̬���ȵ�was����ظ� */
        NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF);

        /* ����������ʱ�� */
        NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

        /* ��Ϣ������ɲ���������� */
        return VOS_TRUE;
    }
    

    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_PLMN_STOP_CNF);

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_FDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSearchedPlmnInfoInd_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}


VOS_UINT32  NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTdPlmnSearchCnf_PlmnSelection_WaitWasPlmnStopCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasPlmnStopCnfExpired_PlmnSelection_WaitWasPlmnStopCnf: ENTERED");

    if ((VOS_FALSE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
     && (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
     && (MMCMMC_INTER_SKIP_SEARCH_TDS_IND == pstMsgHeader->ulMsgName))
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�TD��,��WAS���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(WUEPS_PID_WRR);

    /* Ǩ��״̬���ȵ�was����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_WAS_SUSPEND_CNF_BACK_TD);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;


    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);


    /* �й������Ǵ������˳���ǰ״̬�� */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {

        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRC����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}


VOS_UINT32 NAS_UTRANCTRL_RcvRrmmPlmnSearchCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;
    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;


    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_PLMN_STOP_CNF);

    /* �������ʧ�ܣ�ԭ��ΪNO RF����ֱ�ӽ�MMC����ά�ֵ�ǰΪFDDģʽ */
    if ((RRC_PLMN_SEARCH_RLT_SPEC_NO_RF     == pstSrchCnfMsg->ulSearchRlt)
     || (RRC_PLMN_SEARCH_RLT_HISTORY_NO_RF  == pstSrchCnfMsg->ulSearchRlt))
    {
        NAS_UTRANCTRL_SetCurrUtranMode(NAS_UTRANCTRL_UTRAN_MODE_TDD);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��MMC״̬������ */
        return VOS_FALSE;
    }

    /* �й������Ǵ������˳���ǰ״̬�� */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRC����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32  NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvWasPlmnStopCnf_PlmnSelection_WaitTdPlmnStopCnf: illegal MESSAGE! ");

    /* �����÷Ƿ���Ϣ */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvUserReqMsg_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼״̬����ϱ�� */
    NAS_UTRANCTRL_SetAbortFlg_PlmnSelection(VOS_TRUE);

    /* ���浱ǰ�û�������Ϣ */
    NAS_UTRANCTRL_SaveCacheMsgInMsgQueue(ulEventType, pstMsg);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    MSG_HEADER_STRU                    *pstMsgHeader      = VOS_NULL_PTR;
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();

    /* ȡ�õ�ǰ������Ϣ��ͷ */
    pstMsgHeader = (MSG_HEADER_STRU *)pstEntryMsg->aucEntryMsgBuffer;


    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdPlmnStopCnfExpired_PlmnSelection_WaitTdPlmnStopCnf: ENTERED");


    /* �й������Ǵ������˳���ǰ״̬�� */
    if ( (VOS_TRUE == NAS_UTRANCTRL_GetSearchedSpecTdMccFlg())
      || ( (WUEPS_PID_MMC                  == pstMsgHeader->ulSenderPid)
        && (MMCMMC_INTER_SKIP_SEARCH_W_IND == pstMsgHeader->ulMsgName) ) )
    {

        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );

        /* ������Ҫ�滻�����Ϣ��� */
        NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

        /* ״̬���л���MAIN */
        NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

        /* ��Ϣ������ɼ�������MMC״̬������ */
        return VOS_FALSE;
    }

    /* ��ʱ��Ҫ�ص�W��,��TDRRC���͹������� */
    NAS_UTRANCTRL_SndGuAsSuspendReq(TPS_PID_RRC);

    /* Ǩ��״̬���ȵ�TDRRC����ظ� */
    NAS_UTRANCTRL_FSM_SetCurrState(NAS_UTRANCTRL_PLMN_SELECTION_STA_WAIT_TD_SUSPEND_CNF_BACK_W);

    /* ����������ʱ�� */
    NAS_UTRANCTRL_StartTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF, TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF_LEN);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}



VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_WAS_SUSPEND_CNF);

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();


    /* �����ǰ�������ϢΪ��ʱ����ʱ������Ҫ���������ظ�ʧ����Ϣ */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                    (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitWasSuspendCnfExpired_PlmnSelection_WaitWasSuspendCnfBackTD: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvRrmmSuspendCnf_PlmnSelection_WaitTdSuspendCnfBackW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstEntryMsg       = VOS_NULL_PTR;
    RRMM_SUSPEND_CNF_ST                *pstRrmmSuspendCnf = VOS_NULL_PTR;

    NAS_UTRANCTRL_ENTRY_MSG_STRU       *pstBufferEntryMsg = VOS_NULL_PTR;

    /* ��õ�ǰ����Ļ�������ַ */
    pstBufferEntryMsg = NAS_UTRANCTRL_GetBufferUtranSndMmcMsgAddr();
    pstRrmmSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    if (MMC_AS_SUSPEND_FAILURE == pstRrmmSuspendCnf->ucResult)
    {
        /* ���帴λ */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ������ʱ�� */
    NAS_UTRANCTRL_StopTimer(TI_NAS_UTRANCTRL_WAIT_TD_SUSPEND_CNF);

    /* ȡ��ǰ�����ϵͳ��Ϣ */
    pstEntryMsg = NAS_UTRANCTRL_GetCurrEntryMsgAddr();


    /* �����ǰ�������ϢΪ��ʱ����ʱ������Ҫ���������ظ�ʧ����Ϣ */
    if (VOS_TRUE == NAS_UTRANCTRL_IsNeedBuildSearchCnfMsg_WaitSuspendCnf())
    {
        /* ����ָ�������ظ�ʧ����Ϣ���ڴ�Ļ������� */
        NAS_UTRANCTRL_BuildRrMmPlmnSearchCnfFailMsg(WUEPS_PID_WRR,
                                                    WUEPS_PID_MMC,
                                                    NAS_UTRANCTRL_GetBufferedPlmnSearchReqType(),
                                                   (RRMM_PLMN_SEARCH_CNF_STRU *)pstBufferEntryMsg->aucEntryMsgBuffer);

        /* ���湹��ָ�������ظ�ʧ����Ϣ�¼����� */
        pstBufferEntryMsg->ulEventType = NAS_UTRANCTRL_GetMsgEventType( (struct MsgCB *)pstBufferEntryMsg->aucEntryMsgBuffer );
    }
    else
    {
        /* ȡ�����״̬�������ظ�ʧ����Ϣ��MMCģ�� */
        NAS_UTRANCTRL_SaveBufferUtranSndMmcMsg(pstEntryMsg->ulEventType,
                                (struct MsgCB *)pstEntryMsg->aucEntryMsgBuffer);

    }

    /* ������Ҫ�滻�����Ϣ��� */
    NAS_UTRANCTRL_SetReplaceMmcMsgFlg(VOS_TRUE);

    /* �л���MAIN״̬�� */
    NAS_UTRANCTRL_SwitchCurrFsmCtx(NAS_UTRANCTRL_FSM_MAIN);

    /* ��Ϣ������ɼ�������MMC״̬������ */
    return VOS_FALSE;
}
VOS_UINT32 NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_UTRANCTRL_RcvTiWaitTdSuspendCnfExpired_PlmnSelection_WaitTdSuspendCnfBackW: ENTERED");

    /* ��λ */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);

    /* ��Ϣ������ɲ���������� */
    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
