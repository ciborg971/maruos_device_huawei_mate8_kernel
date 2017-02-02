

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmlCtx.h"
#include "NasComm.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmlCtx.h"
#include "NasMmlLib.h"
#include "NasMmlMsgProc.h"
#include "Nasrrcinterface.h"

#include "MsccMmcInterface.h"

#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndLmm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcProcSuspend.h"
#include "NasMmcFsmInterSysHoTbl.h"
#include "NasMmcFsmInterSysHo.h"
#include "NasUtranCtrlInterface.h"

#include "NasMmcComFunc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_HO_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/

/*lint -save -e958 */

VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysHo_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstHoSuspendMsg;

    pstHoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstHoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstHoSuspendMsg);

    /* ����MM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstHoSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysHo_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstHoSuspendMsg;

    pstHoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstHoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstHoSuspendMsg);

    /* ����MM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstHoSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysHo_Init(
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

    /* ����MM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysHo(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* ���õ�ǰ����ΪLTE */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_LTE);

    /* ����L��RESUME_IND��Ϣ������CS,PSresume�������ʱ���ջָ��ɹ�����RESUME��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_NET_RAT_TYPE_LTE ,&stResumeIndMsg);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd_Handover(&stResumeIndMsg, VOS_FALSE);
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM����:NAS_MMC_SndMmResumeInd */
    NAS_MMC_SndMmResumeInd_Handover(&stResumeIndMsg, VOS_FALSE);
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);

    /* ������ʱ��TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;

}

#endif
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysHo_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;
    /* ������յ�MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysHo( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysHo_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysHo( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_HO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysHo_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysHo_WaitMmSuspendRsp:ENTERED");

    /* �����㷢�͹���ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOldNtType;

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

    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* GU֮����л�,CS�������Ӵ��� */
    if (NAS_MML_NET_RAT_TYPE_GSM == enOldNtType)
    {
        NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
    }

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndMmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetCsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndGmmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetPsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enOldNtType;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }


    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);


    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

    /* GU֮����л�,CS�������Ӵ��� */
    if (NAS_MML_NET_RAT_TYPE_WCDMA == enOldNtType)
    {
        NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
    }

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndMmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetCsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndGmmResumeInd_Handover(pstResumeIndMsg, NAS_MMC_GetPsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysHo_WaitAsResumeInd:ENTERED");

    /* ����om�ӿ�,�ϵ縴λ: */

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


VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd      = (RRMM_REL_IND_STRU*)pstMsg;


    /* �ͷ�ԭ��ΪUtran releaseʱ����Ҫ����HO���̣������ȴ�resume ind��
       ������Ϊ���̽���������WAS�ָ�������ͬWAS������resume ind���������Ѳ����� */
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

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    PS_MEM_SET(&stResumeIndMsg, 0x0, sizeof(stResumeIndMsg));
    NAS_MMC_SndMmResumeInd_Handover(&stResumeIndMsg, NAS_MMC_GetCsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);
    NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_FALSE);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndGmmResumeInd_Handover(&stResumeIndMsg, NAS_MMC_GetPsSigExistFlag_InterSysHo());
    NAS_MMC_SetResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);
    NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_FALSE);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_HO_STA_WAIT_MM_RESUME_RSP);
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvRrMmHandoverInd_InterSysHo_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_HANDOVER_INFO_IND_STRU        *pstHoInfoInd = VOS_NULL_PTR;

    pstHoInfoInd      = (RRMM_HANDOVER_INFO_IND_STRU*)pstMsg;

    /* ��ǰ�л���SRVCC���� */
    if (VOS_TRUE == pstHoInfoInd->ucSrvccFlag)
    {
        NAS_MMC_SndMmSrvccInfoNotify();
    }

    switch (pstHoInfoInd->enSignalInfo)
    {
        case RRC_NAS_SIG_CS:

             NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
             break;

        case RRC_NAS_SIG_PS:

            NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_TRUE);
            break;

        case RRC_NAS_SIG_CSANDPS:

             NAS_MMC_SetPsSigExistFlag_InterSysHo(VOS_TRUE);
             NAS_MMC_SetCsSigExistFlag_InterSysHo(VOS_TRUE);
             break;

        default:

            break;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysHo_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ״̬�������ı�����յ�MMCGMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣTI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

       /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */


    /* ����״̬���ɹ��Ľ�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬��: */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysHo_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ״̬�������ı�����յ�MMCMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysHo(NAS_MMC_MM_RESUME_RSP_FLG);

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysHo() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣTI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

     /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ����״̬���ɹ��Ľ�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬��: */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysHo_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysHo_WaitMmResumeRsp:ENTERED");

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */


    /* ����״̬���ɹ��Ľ�� */
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_HANDOVER, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬��: */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_VOID NAS_MMC_SndGmmResumeInd_Handover(
    RRMM_RESUME_IND_ST                 *pstMsg,
    VOS_UINT8                           ucPsSigExistFlg
)
{
    /*��GMM���ͻָ�ָʾ,����ԭ������ָ�� */
    MMCGMM_RESUME_IND_ST               *pstSndMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg  = (MMCGMM_RESUME_IND_ST*)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_RESUME_IND_ST));

    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_GMM;

    pstSndMsg->MsgHeader.ulLength
        = sizeof(RRMM_RESUME_IND_ST) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSndMsg->MsgHeader.ulMsgName   = MMCGMM_RESUME_IND;

    pstSndMsg->ucCsResumeResult      = pstMsg->ucCsResumeResult;
    pstSndMsg->ucPsResumeResult      = pstMsg->ucPsResumeResult;
    pstSndMsg->ucResumeOrigen        = pstMsg->ucResumeOrigen;

    pstSndMsg->ucPsSigExistFlg       = ucPsSigExistFlg;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}
VOS_VOID  NAS_MMC_SndMmResumeInd_Handover(
    RRMM_RESUME_IND_ST                 *pstMsg,
    VOS_UINT8                           ucCsSigExistFlg
)
{
    /*��MM���ͻָ�ָʾ,����ԭ������ָ�� */
    MMCMM_RESUME_IND_STRU              *pstSndMsg = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstSndMsg  = (MMCMM_RESUME_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCMM_RESUME_IND_STRU));
    if ( VOS_NULL_PTR == pstSndMsg)
    {
        return;
    }

    pstSndMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulSenderPid       = WUEPS_PID_MMC;
    pstSndMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstSndMsg->MsgHeader.ulLength          = sizeof(MMCMM_RESUME_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��д��Ϣ���� */
    pstSndMsg->MsgHeader.ulMsgName   = MMCMM_RESUME_IND;

    pstSndMsg->ucCsResumeResult      = pstMsg->ucCsResumeResult;
    pstSndMsg->ucPsResumeResult      = pstMsg->ucPsResumeResult;
    pstSndMsg->ucResumeOrigen        = pstMsg->ucResumeOrigen;

    pstSndMsg->ucCsSigExistFlg       = ucCsSigExistFlg;

    NAS_MML_SndInternalMsg(pstSndMsg);

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


