

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
#include "NasMmcFsmInterSysCellResel.h"
#include "NasMmcFsmInterSysCellReselTbl.h"
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

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CELLRESEL_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*lint -save -e958 */

VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCellResel_Init(
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
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCellResel_Init(
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
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstGUSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ��NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCellResel( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ����д�ϣ����ҹ���ԭ�����ض��򣬸���ͬ�Ľ���㷢��SUSPEND_REL_REQ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        if ( MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }
    }

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND );

/* Modify by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
    /* ƴƬ��CLģʽ�£�������ͬʱ����ʱ�� */
    if (VOS_TRUE == NAS_MMC_StartResumeTimer_InterSysCellResel())
    {
        return VOS_TRUE;
    }
/* Modify by l00324781 for CDMA Iteration 12, 2015-5-29, end */

    /* �����GU�ض���,��ʱ��ʱ��Ϊ90S;�����GL WL֮����ض���,��ʱ��ʱ��Ϊ200S */
    if ( MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

         return VOS_TRUE;
    }

    /* ��ȡ����Ŀ�ķ����������� */
#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendDestinationRatType(NAS_MMC_GetCurrEntryMsg()))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN);
    }
    else
#endif
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);
    }

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCellResel( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��MMC_WAIT_NAS_SUSPEND_RSP_TIMER */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ����д�ϣ����ҹ���ԭ�����ض��򣬸���ͬ�Ľ���㷢��SUSPEND_REL_REQ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        if (MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
        {
            NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());

            return VOS_TRUE;
        }
    }

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_AS_RESUME_IND );

/* Modify by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
    /* ƴƬ��CLģʽ�£�������ͬʱ����ʱ�� */
    if (VOS_TRUE == NAS_MMC_StartResumeTimer_InterSysCellResel())
    {
        return VOS_TRUE;
    }
/* Modify by l00324781 for CDMA Iteration 12, 2015-5-29, end */

    /* �����GU�ض���,��ʱ��ʱ��Ϊ90S;�����GL WL֮����ض���,��ʱ��ʱ��Ϊ200S */
    if ( MMC_SUSPEND_CAUSE_CELLRESELECT == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

         return VOS_TRUE;
    }

    /* ��ȡ����Ŀ�ķ����������� */
#if (FEATURE_ON == FEATURE_LTE)
    if ( NAS_MML_NET_RAT_TYPE_LTE == NAS_MMC_GetSuspendDestinationRatType(NAS_MMC_GetCurrEntryMsg()))
    {
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, TI_NAS_MMC_INTER_SYS_GUL_REDIR_WAIT_AS_RESUME_IND_LEN);
    }
    else
#endif
    {
        ulResumeIndTiLen = NAS_MMC_GetWaitGUTAsRedirResumeIndTimerLen();
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);
    }

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCellResel_WaitMmSuspendRsp:ENTERED");

    /* �����㷢�͹���ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��ϱ�־ */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    /* ��������MM/GMM��SUSPEND_RSP���ٸ�����㷢RRMM_SUSPEND_REL_REQ */

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;


    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_WCDMA);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;


    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_GSM);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);


    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_IN_WAS_WAIT_RESUME_IND_EXPIRED);
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
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ulIsSysChgToHrpd;

    ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif

    /* ��¼��ϱ�־ */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    /* �����GU�ض���,��GU����㷢RRMM_SUSPEND_REL_REQ
       �����Lģ�ض���GU����LMM����LMM_SUSPEND_REL_REQ */
    if (( MMC_SUSPEND_CAUSE_REDIRECTION == NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg()))
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
      || (VOS_TRUE == ulIsSysChgToHrpd)
#endif
      )
    {

        /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

        NAS_MMC_SndSuspendRelReq_InterSysCellResel(NAS_MML_GetCurrNetRatType());
    }

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd = (RRMM_REL_IND_STRU*)pstMsg;


    /* �ͷ�ԭ��ΪUtran releaseʱ, ��Ҫ������ѡ����, �����ȴ�resume ind,
       ������Ϊ���̽���, ����WAS�ָ�, ����ͬWAS������resume ind */
    if (RRC_REL_CAUSE_UTRAN_RELEASE == pstRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);


    /* ����resume��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* ���ǰ���д�ϱ�־���˳���ǰ״̬������������Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
        /* �ظ�InterSysCellReselִ�н�� */
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ulIsSysChgToHrpd;
#endif
    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    NAS_MMC_ClearResumeRspFlag_InterSysCellResel( NAS_MMC_GMM_RESUME_RSP_FLG );

    /* δ������GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
    if(VOS_TRUE == NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel())
    {
        return VOS_TRUE;
    }
/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, end */

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ǰ���д�ϱ�־�����ҵ�ǰ���뼼������LTE���˳���ǰ״̬������������Ϣ
       �����ǰ���뼼����LTE,��Ҫ������LTE��ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if (FEATURE_ON == FEATURE_LTE)
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
        ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif

        if ((NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
           || ((MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause)
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
          &&(VOS_FALSE == ulIsSysChgToHrpd)
#endif
          ))
#endif
        {
            /* �ظ�InterSysCellReselִ�н�� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    /* ���ݲ�ͬ����������Ǩ�Ƶ���ͬ��״̬ */
    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* W��Cell Reselect ��ѡ���˵� W�£����ܽ���FACH̬�����������̣���Ҫ��ǰ�˳���ϵͳ��Ϣ�к���״̬������ */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* ����״̬���ɹ��Ľ�� */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* �˳���ǰ״̬��: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmResumeRsp_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    VOS_UINT32                          ulIsSysChgToHrpd;
#endif
    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    NAS_MMC_ClearResumeRspFlag_InterSysCellResel( NAS_MMC_MM_RESUME_RSP_FLG );

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCellResel() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣMMC_WAIT_MM_RESUME_RSP_TIMER */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

/* Modify by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
    /* �����ѡ��HRPD��֪ͨLMM�ָ����˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_ProcResumeRspFromLteToHrpd_InterSysCellResel())
    {
        return VOS_TRUE;
    }
/* Modify by l00324781 for CDMA Iteration 12, 2015-5-29, end */

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ǰ���д�ϱ�־���˳���ǰ״̬������������Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if   (FEATURE_ON == FEATURE_LTE)
#if   (FEATURE_ON == FEATURE_CL_INTERWORK)
        ulIsSysChgToHrpd = NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg());
#endif
        if ( (NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
          || ((MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause)
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
          &&(VOS_FALSE == ulIsSysChgToHrpd)
#endif
          ))
#endif
        {
            /* �ظ�InterSysCellReselִ�н�� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* W��Cell Reselect ��ѡ���˵� W�£����ܽ���FACH̬�����������̣���Ҫ��ǰ�˳���ϵͳ��Ϣ�к���״̬������ */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* ����״̬���ɹ��Ľ�� */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* �˳���ǰ״̬��: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmResumeRsp_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;
#if (FEATURE_ON == FEATURE_LTE)
    MMC_SUSPEND_CAUSE_ENUM_UINT8        enSuspendCause;

    enSuspendCause                      = NAS_MMC_GetSuspendCause(NAS_MMC_GetCurrEntryMsg());
#endif
    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp:ENTERED");

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ǰ���д�ϱ�־�����ҹ���ԭ������ѡ���˳���ǰ״̬������������Ϣ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_InterSysCellResel())
    {
#if   (FEATURE_ON == FEATURE_LTE)
        if ( (NAS_MML_NET_RAT_TYPE_LTE != enCurNetType)
          || (MMC_SUSPEND_CAUSE_CELLRESELECT == enSuspendCause) )
#endif
        {
            /* �ظ�InterSysCellReselִ�н�� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }
    }

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:


            /* W��Cell Reselect ��ѡ���˵� W�£����ܽ���FACH̬�����������̣���Ҫ��ǰ�˳���ϵͳ��Ϣ�к���״̬������ */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                /* ����״̬���ɹ��Ľ�� */
                NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

                /* �˳���ǰ״̬��: */
                NAS_MMC_FSM_QuitFsmL2();

                return VOS_TRUE;

            }
            else
            {
                /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND״̬ */
                NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SYSINFO_IND);

                /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
                if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
                }
                else
                {
                    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
                }
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCellResel_WaitMmResumeRsp:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��ϱ�־ */
    NAS_MMC_SetAbortFlag_InterSysCellResel(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�WAS��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡�����������㷢��RRMM_SUSPEND_REL_REQ,���յ�������RRMM_RESUME_IND
       �ȴ���RRMM_RESUME_IND,�������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* ͣ�ȴ�SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != enRatType)
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvTiWaitWasSuspendRelCnf_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvRrmmRelInd_InterSysCellResel_WaitWasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�WAS��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /*  ��ϵͳ������ģʽ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�GAS��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡�����������㷢��RRMM_SUSPEND_REL_REQ,���յ�������RRMM_RESUME_IND
       �ȴ���RRMM_RESUME_IND,�������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* ͣ�ȴ�SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);


    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvTiWaitGasSuspendRelCnf_InterSysCellResel_WaitGasSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}






VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    VOS_UINT8                                               ucH3gCtrlFlg;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);

    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);

    }

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* ��ϵͳ��ѡʱ����Ҫ���H3G���γ��������⴦������ǰ�����������HPLMN��
       �����״̬��Ҫ�ȸ���Ϊ���޷��� */
    ucH3gCtrlFlg = NAS_MML_GetH3gCtrlFlg();


    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* ����״̬��ע��״̬�ϱ�����ϵͳ��Ϣ�ϱ����� */
    if ((VOS_TRUE != NAS_MML_ComparePlmnIdWithHplmn(&(stOldCampInfo.stLai.stPlmnId)))
     && (NAS_MML_NET_RAT_TYPE_WCDMA != enOldNtType)
     && (VOS_TRUE == ucH3gCtrlFlg))
    {
        /* С����ѡ���ڳɹ�ע��ǰ�����ϱ�limit service */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    }


    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    ulParentEventType = NAS_MMC_GetParentFsmEventType();

    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enParentFsmId,ulParentEventType) )
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
        NAS_MMC_SndMmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmWasSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

    }


#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
	NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_WAS_SYS_INFO_EXP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_TAS_SYS_INFO_EXP);
    }

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_WAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    VOS_UINT8                                               ucH3gCtrlFlg;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

    /* ����յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* ��ϵͳ��ѡʱ,NV���ж���,���H3G���γ��������⴦������ǰ�����������HPLMN��
       �����״̬��Ҫ�ȸ���Ϊ���޷��� */
    ucH3gCtrlFlg = NAS_MML_GetH3gCtrlFlg();

    /* ����״̬�ϱ�������ϵͳ��Ϣ�ϱ����� */

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMMAģ�鵱ǰ����������Ϣ */
    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldCsRestrictInfo, pstCurCsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_CS, pstCurCsRestrictInfo);
    }

    if (VOS_TRUE == NAS_MML_IsAcInfoChanged(&stOldPsRestrictInfo, pstCurPsRestrictInfo))
    {
        NAS_MMC_SndMsccAcInfoChangeInd(NAS_MSCC_PIF_SRVDOMAIN_PS, pstCurPsRestrictInfo);
    }

#if ((FEATURE_ON == FEATURE_GCBS) || (FEATURE_ON == FEATURE_WCBS))
    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_GSM);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* ����״̬��ע��״̬�ϱ�����ϵͳ��Ϣ�ϱ����� */
    if ((VOS_TRUE != NAS_MML_ComparePlmnIdWithHplmn(&(stOldCampInfo.stLai.stPlmnId)))
     && (NAS_MML_NET_RAT_TYPE_GSM != enOldNtType)
     && (VOS_TRUE == ucH3gCtrlFlg))
    {
        /* С����ѡ���ڳɹ�ע��ǰ�����ϱ�limit service */
        NAS_MMC_ChangeServiceState(NAS_MSCC_PIF_SRVDOMAIN_CS_PS, NAS_MMC_LIMITED_SERVICE);
    }

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    enParentFsmId     = NAS_MMC_GetParentFsmId();
    ulParentEventType = NAS_MMC_GetParentFsmEventType();


    if ( VOS_TRUE == NAS_MMC_IsUserSpecPlmnSrchType_PlmnSelection(enParentFsmId,ulParentEventType) )
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenTypeForUserSpecPlmnSrch(),
                                   VOS_TRUE,
                                   pstMsg);
    }
    else
    {
        /* ת��ϵͳ��Ϣ֪ͨ �� MM/GMM,������ǰϵͳ��Ϣ�� Forbidden ����Я����ȥ */
        NAS_MMC_SndMmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

        NAS_MMC_SndGmmGsmSysInfoInd(NAS_MMC_GetCurrentLaiForbbidenType(),
                                   VOS_FALSE,
                                   pstMsg);

    }

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, begin */
    NAS_MMC_SaveLastCampedPlmnWithRat(NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMcc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.stPlmnId.ulMnc,
                           NAS_MML_GetCurrCampPlmnInfo()->stLai.enCampPlmnNetRat);
    /* Modified by c00318887 for Ԥ��Ƶ�������Ż�, 2015-9-9, end */

    /* ���פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ��ǰ�źŸ��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
	NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_InterSysCellResel_WaitWasSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );



    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_GAS_SYS_INFO_EXP);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_GAS_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#if   (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_RcvLSysInfoInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);



    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }
    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */
    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);
    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* L�ض���GU�����ֹͣGURRC�ɹ��������ض���ʧ�ܻ��˵�Lʱ��
       ��Ϣ���͵�˳��Ϊ��LMM�ϱ�RESUME_IND,���ϱ�LMM_SYS_INFO_IND��AREA_LOST_IND
       ������ϱ�SUSPEND_REL_CNF,֮������˳�״̬������������Ϣ��
       ���Դ˴�Ǩ����LMM��SUSPEND_REL_CNF״̬ */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    /* ����suspend״̬�������Ϣ */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */


    /* ��TAF���������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ֪ͨTAF��ǰ�ķ���״̬ */


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* L�ض���GU�����ֹͣGURRC�ɹ��������ض���ʧ�ܻ��˵�Lʱ��
       ��Ϣ���͵�˳��Ϊ��LMM�ϱ�RESUME_IND,���ϱ�LMM_SYS_INFO_IND��AREA_LOST_IND
       ������ϱ�SUSPEND_REL_CNF,֮������˳�״̬������������Ϣ��
       ���Դ˴�Ǩ����LMM��SUSPEND_REL_CNF״̬ */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_InterSysCellResel_WaitLSysInfoInd:ENTERED");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */
    


    /* ��TAF���������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* L�ض���GU�����ֹͣGURRC�ɹ��������ض���ʧ�ܻ��˵�Lʱ��
       ��Ϣ���͵�˳��Ϊ��LMM�ϱ�RESUME_IND,���ϱ�LMM_SYS_INFO_IND��AREA_LOST_IND
       ������ϱ�SUSPEND_REL_CNF,֮������˳�״̬������������Ϣ��
       ���Դ˴�Ǩ����LMM��SUSPEND_REL_CNF״̬ */
    if ( (VOS_TRUE == NAS_MMC_GetSndSuspendRelReqFlg_InterSysCellResel())
      && (NAS_MML_NET_RAT_TYPE_LTE == enOldNtType) )
    {
        /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

        return VOS_TRUE;
    }

    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CELL_RESEL_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg  = VOS_NULL_PTR;

    pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ת��L�Ĺ�����ϢΪGU��ʽ�� */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stSndSuspendMsg);

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);
    NAS_MMC_SetSuspendRspFlag_InterSysCellResel(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ��״̬Ǩ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;


    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

    /* ֹͣTI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);
#endif
#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    if (VOS_TRUE == NAS_MMC_IsInterSysReselectToHrpd(NAS_MMC_GetCurrEntryMsg()))
    {
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND);
    }
#endif

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_LTE);

    /* ����L��RESUME_IND��Ϣ������CS,PSresume�������ʱ���ջָ��ɹ�����RESUME��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ͣ�ȴ�LMM��SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_WaitAsSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �Գ峡�����������㷢��RRMM_SUSPEND_REL_REQ,���յ�������RRMM_RESUME_IND
       �ȴ���RRMM_RESUME_IND,�������յ�RRMM_SUSPEND_REL_CNF���� */

    RRMM_RESUME_IND_ST                  stResumeIndMsg;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;

    enRatType = NAS_MML_GetCurrNetRatType();

    /* ��ȡ�ɵ��������� */

    /* ͣ�ȴ�SUSPEND_REL_CNF��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(enRatType);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);


    /* ����L��RESUME_IND��Ϣ������CS,PSresume�������ʱ���ջָ��ɹ�����RESUME��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitLmmSuspendRelCnf_InterSysCellResel_WaitLmmSuspendRelCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_InterSysCellResel_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*ֹͣ������ʱ�� TI_NAS_MMC_WAIT_LMM_SYS_INFO*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* �ظ�InterSysCellReselִ�н�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLRESELECT, NAS_MMC_SUSPEND_ABORTED, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvLmmSuspendInfoChangeNotify_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU *pstSuspendInfoChangeNotifyMsg;
    NAS_MMC_ENTRY_MSG_STRU                  *pstEntryMsg;
    LMM_MMC_SUSPEND_IND_STRU                *pstSuspendIndMsg;

    pstSuspendInfoChangeNotifyMsg   = (LMM_MMC_SUSPEND_INFO_CHANGE_NOTIFY_STRU*)pstMsg;


    if ( LMM_MMC_SUSPEND_RAT_INFO_CHANGE != pstSuspendInfoChangeNotifyMsg->ulInfoType)
    {
        return VOS_TRUE;
    }

    pstEntryMsg     = NAS_MMC_GetCurrEntryMsg();

    pstSuspendIndMsg = (LMM_MMC_SUSPEND_IND_STRU*)(pstEntryMsg->aucEntryMsgBuffer);

    if ( LMM_MMC_RAT_CHANGE_G2W == pstSuspendInfoChangeNotifyMsg->ulRatChangeType )
    {
        pstSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2W;

        /*���ͱ仯��Ϣ��mm*/
        NAS_MMC_SndMmRatChangeInd(NAS_MML_NET_RAT_TYPE_WCDMA);
    }
    else if ( LMM_MMC_RAT_CHANGE_W2G == pstSuspendInfoChangeNotifyMsg->ulRatChangeType )
    {
        pstSuspendIndMsg->ulSysChngDir = MMC_LMM_SYS_CHNG_DIR_L2G;

        /*���ͱ仯��Ϣ��mm*/
        NAS_MMC_SndMmRatChangeInd(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        ;
    }
    return VOS_TRUE;
}


#endif

#if   (FEATURE_ON == FEATURE_CL_INTERWORK)

VOS_UINT32 NAS_MMC_RcvCmmcaResumeInd_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CMMCA_RESUME_IND);

    /* ��ѡ��CDMA�����õ�ǰ��3GPP�Ľ��뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ѡ��CDMA�����õ�ǰδפ�� */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* ��MM/GMM���͵�resume ind��Ϣ��ָʾ�ָ���ΪHRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitCmmcaResumeIndExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_CMMCA_RESUME_IND_EXPIRED);

    return VOS_TRUE;
}
#endif



VOS_VOID NAS_MMC_SndSuspendRelReq_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    NAS_MMC_SetSndSuspendRelReqFlg_InterSysCellResel(VOS_TRUE);

    switch (enRat)
    {
       case NAS_MML_NET_RAT_TYPE_WCDMA :
            /* ��WRR����RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndAsSuspendRelReq(WUEPS_PID_WRR);

            /* Ǩ��״̬���ȴ�WAS��SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_WAS_SUSPEND_REL_CNF);

            /* ����Ӧ�ı�����ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF_LEN);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM :
            /* ��GAS����RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndAsSuspendRelReq(UEPS_PID_GAS);

            /* Ǩ��״̬���ȴ�GAS��SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_GAS_SUSPEND_REL_CNF);

            /* ����Ӧ�ı�����ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF_LEN);

            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE :
            /* ��LMM����RRMM_SUSPEND_REL_REQ */
            NAS_MMC_SndLmmSuspendRelReq();

            /* Ǩ��״̬���ȴ�LMM��SUSPEND_REL_CNF */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SUSPEND_REL_CNF);

            /* ����Ӧ�ı�����ʱ�� */
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF_LEN);

            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendRelReq_InterSysCellResel: Rat not support.");
            break;
    }

    return;
}
VOS_VOID NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    switch (enRat)
    {
       case NAS_MML_NET_RAT_TYPE_WCDMA :

            /* ͣWAS�ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_REL_CNF);

            break;

        case NAS_MML_NET_RAT_TYPE_GSM :

            /* ͣGAS�ı�����ʱ�� */
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_REL_CNF);

            break;

#if   (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE :
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_REL_CNF);
            break;
#endif
        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_StopSuspendRelCnfTimer_InterSysCellResel: Rat not support.");
            break;
    }

    return;
}


/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, begin */
#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_LTE))

/*****************************************************************************
Function Name   :   NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsResumeInd
Description     :   CL mode, LTE reselct or redir to hrpd, process message MSCC_MMC_INTERSYS_HRPD_NTF,
                :   set currtType as BUTT,and send resume ind to MM and GMM.
Input parameters:   ulEventType: the Event type
                :   pstMsg     : the MSCC_MMC_INTERSYS_HRPD_NTF message
Outout parameters:  None
Return Value    :
Modify History:
    1)  Date    :   2015-05-29
        Author  :   l00324781
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvMsccInterSysHrpdNtf_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ֹͣTI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF);

    /* ��ѡ���ض���CDMA�����õ�ǰ��3GPP�Ľ��뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ��ѡ���ض���CDMA�����õ�ǰδפ�� */
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetResumeOrign_InterSysCellResel(MMC_RESUME_ORIGEN_HRPD);

    /* ��MM/GMM���͵�resume ind��Ϣ��ָʾ�ָ���ΪHRPD */
    stResumeIndMsg.ucCsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucPsResumeResult = MMC_RESUME_RESULT_SUCCESS;
    stResumeIndMsg.ucResumeOrigen   = MMC_RESUME_ORIGEN_HRPD;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCellResel(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}


/*****************************************************************************
Function Name   :   NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd
Description     :   CL mode, LTE reselct or redir to hrpd, MMC wait MSCC_MMC_INTERSYS_HRPD_NTF
                :   or LMM_MMC_RESUME_IND, but timeout.
Input parameters:   ulEventType: the Event type
                :   pstMsg     : the TI_NAS_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF timout message
Outout parameters:  None
Return Value    :
Modify History:
    1)  Date    :   2015-05-29
        Author  :   l00324781
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMsccInterSysHrpdNtfExpired_InterSysCellResel_WaitAsResumeInd:ENTERED");

    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_MSCC_INTERSYS_HRPD_NTF_EXPIRED);

    return VOS_TRUE;
}

#endif

#if (FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
Function Name   :   NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init
Description     :   CL mode,HRPD Reselct LTE, MMC Recive LMM_MMC_RESUME_IND��wait LMM_MMC_SYSINFO_INF_IND
Input parameters:   ulEventType: the Event type
                :   pstMsg     : the LMM_MMC_RESUME_IND message
Outout parameters:  None
Return Value    :
Modify History:
    1)  Date    :   2015-06-06
        Author  :   l00324781
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCellResel_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* ��LMM������Ӧ��Ϣ */
    NAS_MMC_SndLmmResumeNotify();

    /* ��״̬Ǩ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CELLRESEL_STA_WAIT_LMM_SYSINFO_IND);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

    return VOS_TRUE;
}
#endif

/* Added by l00324781 for CDMA Iteration 12, 2015-5-29, end */

/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


