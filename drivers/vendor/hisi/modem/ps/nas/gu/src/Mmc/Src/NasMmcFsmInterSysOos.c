

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "Nasrrcinterface.h"
#include "MM_Share.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMscc.h"
#include "NasMmcFsmInterSysOos.h"
#include "NasMmcFsmInterSysOosTbl.h"
#include "NasMmcFsmInterSysOos.h"
#include "NasMmcProcRegRslt.h"
#include "NasMmcProcSuspend.h"
/* ɾ��ExtAppMmcInterface.h*/
#include "NasMmcComFunc.h"
#include "NasUtranCtrlInterface.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_OOS_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/




VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysOos_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstGUSuspendMsg = VOS_NULL_PTR;

    pstGUSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);


#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstGUSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif


    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysOos(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysOos( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsOosResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysOos( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_OOS_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsOosResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysOos_WaitMmSuspendRsp:ENTERED");

    /* ������ظ�����ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysOos_WaitAsResumeInd:ENTERED");

    /* ����om�ӿ�,�ϵ縴λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_GAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_LMM_WAIT_RESUME_IND_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_TD_WAIT_RESUME_IND_EXPIRED);
    }

   return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* ��ǰAS���� RRMM_SUSPEND_REL_REQ */
    if ( NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_MMC_SndAsSuspendRelReq(WUEPS_PID_WRR);
    }
    else
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitAsResumeInd:could not support current rat!");

        return VOS_FALSE;
    }

    /* Ǩ��״̬���ȴ�SUSPEND_REL_CNF */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_WAS_SUSPEND_REL_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �����ж�ԭ��ֵ */


    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ����RESUME��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

VOS_UINT32  NAS_MMC_RcvWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    /* ���ݽӿ�Լ��,��WRR����RRMM_SUSPEND_REL_CNFʱ,�Ѿ�������IDLE,����WRR������MM/GMM���������ͷ�ָʾ,
       ����MMC��Ҫ����������ӱ�־ */
    NAS_MML_SetRrcConnStatusFlg(VOS_FALSE);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysOos_WaitWasSuspendRelCnf:ENTERED");

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡���Ĵ����ո�����㷢��RRMM_SUSPEND_REL_REQ���յ�������RRMM_RESUME_IND
       �����յ�RRMM_RESUME_IND��Ϣ���������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysOos(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_OOS_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_ClearResumeRspFlag_InterSysOos( NAS_MMC_GMM_RESUME_RSP_FLG );

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_ClearResumeRspFlag_InterSysOos( NAS_MMC_MM_RESUME_RSP_FLG );

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysOos() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysOos_WaitMmResumeRsp:ENTERED");

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

/* oos״̬�������е�ϵͳ��Ϣ״̬��ɾ��g_astNasInterSysOosWaitWSysInfoIndActTbl��
   �յ�resume ind��Ϣ����״̬�� */

/* NAS_MMC_UpdateSearchedPlmnListInfo_Oos����list��bg������״̬������Ҫʹ������NasMmcCommFunc.c */

/* oos״̬�������е�ϵͳ��Ϣ״̬��ɾ��NAS_MMC_RcvWasSuspendInd_InterSysOos_WaitWasSysInfoInd/
   NAS_MMC_RcvMmcAbortFsmMsg_InterSysOos_WaitWasSysInfoInd�յ�resume ind��Ϣ����״̬�� */



VOS_UINT32  NAS_MMC_RcvRrMmRelInd_InterSysOos_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �����ж�ԭ��ֵ */


    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);
    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );

    /* ֪ͨTAF��ǰ�ķ���״̬ */
    NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_NO_SERVICE);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_PLMNSEARCH, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

