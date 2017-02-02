

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/


#include "PsTypeDef.h"
#include "NasMmcCtx.h"
#include "NasMmcTimerMgmt.h"
#include "Nasrrcinterface.h"

#include "MsccMmcInterface.h"

#include "MmcGmmInterface.h"
#include "MmcMmInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "MmcLmmInterface.h"
#endif
#include "NasMmcSndLmm.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndMscc.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcFsmInterSysCco.h"
#include "NasMmcFsmInterSysCcoTbl.h"
#include "NasMmcProcSuspend.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmcProcRegRslt.h"
/* ɾ��ExtAppMmcInterface.h*/
#include "NasMmcComFunc.h"
#include "NasUtranCtrlInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_INTER_SYS_CCO_C
/*****************************************************************************
  2 ȫ�ֱ���
*****************************************************************************/

/*****************************************************************************
  3 �궨��
*****************************************************************************/


/*lint -save -e958 */

VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* ����MM����ظ����:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* ����MM����ظ����:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�MM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ������յ�GMM_suspend_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�SUSPEND:NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRsp:ENTERED");

    /* �����㷢�͹���ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ��ϵͳ������ģʽ��Ҫ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    if ( NAS_MML_NET_RAT_TYPE_GSM != NAS_MML_GetCurrNetRatType())
    {
        /* ��ϵͳ������ģʽ���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeInd:ENTERED");

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


VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd      = (RRMM_REL_IND_STRU*)pstMsg;


    /* �ͷ�ԭ��ΪUtran releaseʱ, ��Ҫ������ѡ����, �����ȴ�resume ind,
       ������Ϊ���̽���, ����WAS�ָ�, ����ͬWAS������resume ind */
    if (RRC_REL_CAUSE_UTRAN_RELEASE == pstRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ��ϵͳ������ģʽ,���С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    /* ����resume��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ����GMM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* ����MM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    /* ������ʱ��TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* ״̬�������ı�����յ�MMCGMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* �ж��Ƿ�����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣTI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND);

            /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:

            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRsp:Unexpected rat type!");
            break;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* ״̬�������ı�����յ�MMCMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣTI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND);

            /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRsp:Unexpected rat type!");
            break;
    }

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurNetType;

    enCurNetType                        = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp:ENTERED");

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���MM/GMM�ĵȴ��ָ���� */
    NAS_MMC_ClearAllResumeRspFlag_InterSysCco();

    switch(enCurNetType)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND);

            /* WAS�Ļ��������У��ϱ�ϵͳ��Ϣʱ��ϳ��������ȴ�ϵͳ��Ϣʱ�� */
            if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg()))
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);
            }
            else
            {
                (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
            }

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRsp:Unexpected Rat type!");
            break;
    }

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

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
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM ,��ָ����������*/
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

    /* �������ģʽ�뵱ǰģʽһ��,ֱ���˳���ǰ״̬�� */
    if ( enOldNtType == NAS_MML_GetCurrNetRatType())
    {
        /*����״̬��ʧ�ܽ��*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND);

    /* ����������ʱ��TI_NAS_MMC_WAIT_EST_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EST_IND, TI_NAS_MMC_WAIT_EST_IND_LEN);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoInd(
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
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    NAS_MMC_FSM_ID_ENUM_UINT32                              enParentFsmId;
    VOS_UINT32                                              ulParentEventType;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ��ȡ�ɵ��������� */
    enOldNtType     = NAS_MMC_GetSuspendOrigenRatType(NAS_MMC_GetCurrEntryMsg());

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

    /* �������ģʽ�뵱ǰģʽһ��,ֱ���˳���ǰ״̬�� */
    if ( enOldNtType == NAS_MML_GetCurrNetRatType())
    {
        /*����״̬��ʧ�ܽ��*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND);

    /* ����������ʱ��TI_NAS_MMC_WAIT_EST_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EST_IND, TI_NAS_MMC_WAIT_EST_IND_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoInd(
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
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();


    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP);
    }


    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCMM_RR_CONN_INFO_IND_STRU        *pstRrconnInfo;

    pstRrconnInfo = (MMCMM_RR_CONN_INFO_IND_STRU*)pstMsg;

    switch(pstRrconnInfo->ulRrConnFlg)
    {
        case MMC_MM_RR_CONN_ESTING:

            /* ���ڽ����������ȴ� */
            NAS_NORMAL_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd:establishing the cs connection!");
            break;
        case MMC_MM_RR_CONN_ESTED:

            /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /*����״̬���ɹ����*/
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �����ӳɹ���CCO���̽������˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            break;
        case MMC_MM_RR_CONN_ABSENT:

            /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* ����ʧ��,����,��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

            break;
        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvMmRrConnInfoInd_InterSysCco_WaitEstInd:Unexpected RR conn status!");
            break;
    }

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMCGMM_SIGNALING_STATUS_IND_STRU    *pstSignalStatusInfo;

    pstSignalStatusInfo = (MMCGMM_SIGNALING_STATUS_IND_STRU*)pstMsg;


    switch(pstSignalStatusInfo->ulSignalingSts)
    {
        case MMC_GMM_SIGNALING_STATUS_ESTING:

             /* PS���ڽ���,�ȴ�*/
             NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd:establishing the ps connection!");

             break;
        case MMC_GMM_SIGNALING_STATUS_PRESENT:

            /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /*����״̬���ɹ����*/
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �����ӳɹ���CCO���̽������˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            break;

        case MMC_GMM_SIGNALING_STATUS_ABSENT:

            /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* ����ʧ��,����,��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

            break;
        default:

            NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvGmmSignalingStatusInd_InterSysCco_WaitEstInd:Unexpected signaling status!");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitEstIndExpired_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ӡ�쳣 */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitEstIndExpired_InterSysCco_WaitEstInd:Entered");

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmTbfRelInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* ��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

    /* ����������ʱ�� TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* ����MM����ظ����:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* �����ȴ�MM�ظ���ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* ����MM����ظ����:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* �����ȴ�MM�ظ���ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvWasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND);

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* ���õȴ���ʶ */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

     /* ���õȴ���ʶ */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* �����ȴ�MM�ظ���ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvGasSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_IND_ST                *pstCcoSuspendMsg;

    pstCcoSuspendMsg   = (RRMM_SUSPEND_IND_ST *)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND);

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)
    /* MMCֻ������������������ԭ��MMC_LMM_EPLMN_NOTIFY_REQ֪ͨLMM:3��ϵͳ�任�У�GU��������Ŀ��ϵͳΪLTEʱ */
    if ( MMC_SUSPEND_DESTINATION_LTE == pstCcoSuspendMsg->ucSuspendDestination )
    {
        /* ֪ͨLTE��ЧPLMN */
        NAS_MMC_SndLmmEquPlmn_InterSysChangeLte();
    }
#endif

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(pstCcoSuspendMsg);

    /* ����MM����ظ����:*/
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(pstCcoSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* �����ȴ�MM�ظ���ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitAsSuspendIndExpired_InterSysCco_WaitAsSuspendIndFallBack:Entered");

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE,NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ״̬�������ı�����յ�MMCMM_SUSPEND_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_MM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if (  NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco()  )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer (TI_NAS_MMC_WAIT_MM_SUSPEND_RSP);

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    /* ������ʱ��TI_NAS_MMC_WAIT_AS_RESUME_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvGmmSuspendRsp_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResumeIndTiLen;

    /* ״̬�������ı�����յ�MMCGMM_SUSPEND_RSP */
    NAS_MMC_ClearSuspendRspFlag_InterSysCco( NAS_MMC_GMM_SUSPEND_RSP_FLG );

    /* δ����GMM,MM��SUSPNED_RSP�����ؼ����ȴ� */
    if (  NAS_MMC_SUSPEND_RSP_NULL_FLG != NAS_MMC_GetSuspendRspFlg_InterSysCco()  )
    {
        return VOS_TRUE;
    }

    /* ֹͣ��ʱ��TI_NAS_MMC_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_StopTimer ( TI_NAS_MMC_WAIT_MM_SUSPEND_RSP );

    /* �����㷢�͹���ɹ� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_SUCCESS);

    /* ��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK */
    NAS_MMC_FSM_SetCurrState( NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_RESUME_IND_FALLBACK );

    ulResumeIndTiLen = NAS_MMC_GetWaitAsResumeIndTimerLen();

    /* ������ʱ��TI_NAS_MMC_WAIT_AS_RESUME_IND */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND, ulResumeIndTiLen);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmSuspendRspExpired_InterSysCco_WaitMmSuspendRspFallBack:ENTERED");

    /* �����㷢�͹���ʧ�� */
    NAS_MMC_SndSuspendRsp(NAS_MML_GetCurrNetRatType(), RRC_NAS_SUSPEND_FAILURE);

    /* ���ݹ���ķ��𷽣�����һ���ָ���Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    /* ��MM/GMM���лָ� */
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE,NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳�״̬��*/
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvWasResumeInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ���С����Ϣ�Լ��ź��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* ������ʱ��TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGasResumeInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_RESUME_IND_ST                 *pstResumeIndMsg = VOS_NULL_PTR;

    /* ֹͣMMC_WAIT_AS_RESUME_IND_TIMER */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);

    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_GSM);

    /* ���С����Ϣ�Լ��ź��� */
    NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());

    /* ����RESUME��Ϣ */
    pstResumeIndMsg                 = (RRMM_RESUME_IND_ST *)pstMsg;

    /* ��resume �Ľ��������GMM_MMC_RESUME_INd ��Ϣ�У�����GMM���� */
    NAS_MMC_SndGmmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM���� */
    NAS_MMC_SndMmResumeInd(pstResumeIndMsg);
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* ������ʱ��TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_ERROR_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsResumeIndExpired_InterSysCco_WaitAsResumeIndFallBack:ENTERED");

    /* ����om�ӿ�,�ϵ縴λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
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


VOS_UINT32 NAS_MMC_RcvRrMmRelInd_InterSysCco_WaitAsResumeIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_REL_IND_STRU                  *pstRelInd = VOS_NULL_PTR;
    RRMM_RESUME_IND_ST                  stResumeIndMsg;

    pstRelInd      = (RRMM_REL_IND_STRU*)pstMsg;


    /* �ͷ�ԭ��ΪUtran releaseʱ, ��Ҫ������ѡ����, �����ȴ�resume ind,
       ������Ϊ���̽���, ����WAS�ָ�, ����ͬWAS������resume ind */
    if (RRC_REL_CAUSE_UTRAN_RELEASE == pstRelInd->ulRelCause)
    {
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_WCDMA != NAS_MML_GetCurrNetRatType())
    {
        /* ����ϵͳ�����С����Ϣ�Լ��ź��� */
        NAS_MML_InitRssiValue(NAS_MML_GetCampCellInfo());
    }


    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ֹͣTI_NAS_MMC_WAIT_AS_RESUME_IND */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_RESUME_IND);


    /* ����resume��Ϣ */
    NAS_MMC_BulidResumeMsg(NAS_MML_GetCurrNetRatType(), &stResumeIndMsg);

    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ����GMM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* ����MM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* ������ʱ��TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ״̬�������ı�����յ�MMCGMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP�����ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣTI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ݲ�ͬ����������Ǩ�Ƶ���ͬ��״̬ */
    switch(NAS_MML_GetCurrNetRatType())
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvGmmResumeRsp_InterSysCco_WaitMmResumeRspFallBack:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ״̬�������ı�����յ�MMCMM_RESUME_RSP */
    NAS_MMC_ClearResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* δ����GMM��MMCGMM_RESUME_RSP�� MM��MMCMM_RESUEM_RSP,���ؼ����ȴ� */
    if ( NAS_MMC_RESUME_RSP_NULL_FLG != NAS_MMC_GetResumeRspFlg_InterSysCco() )
    {
        return VOS_TRUE;
    }

    /* ����Ѿ�����,ֹͣTI_NAS_MMC_WAIT_MM_RESUME_RSP */
    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_MM_RESUME_RSP );

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    /* ���ݲ�ͬ����������Ǩ�Ƶ���ͬ��״̬ */
    switch(NAS_MML_GetCurrNetRatType())
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvMmResumeRsp_InterSysCco_WaitMmResumeRspFallBack:Unexpected Rat Type!");
            break;
    }

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack:ENTERED");

    /* ����뷢�ͻָ��ظ� */
    NAS_MMC_SndResumeRsp(NAS_MML_GetCurrNetRatType());

    /* ģʽ�л�ʱ����֪ͨ�����NAS_MMC_SndInfoReportReq��������ģʱ�յ������ϱ���������б��� */

    switch(NAS_MML_GetCurrNetRatType())
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_WAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_INTER_SYS_FALL_BACK_WAIT_WAS_SYS_INFO_LEN);

            break;
        case NAS_MML_NET_RAT_TYPE_GSM:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_GAS_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);

            break;
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK״̬ */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_LMM_SYSINFO_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);

            break;
#endif

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitMmResumeRspExpired_InterSysCco_WaitMmResumeRspFallBack:Unexpected Rat Type!");
            break;
    }


    return VOS_TRUE;

}




VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitWSysInfoIndFallBack(
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
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_WCDMA);
#endif

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM ,��ָ����������*/
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

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitWSysInfoIndFallBack(
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
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitGSysInfoIndFallBack(
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

    /* פ��С���仯ʱ���ϱ�ϵͳ��Ϣ */
    if (VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    /* פ��С���Ľ���������Ϣ�仯ʱ,֪ͨMSCCģ�鵱ǰ����������Ϣ */
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

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvAreaLostInd_InterSysCco_WaitGSysInfoIndFallBack(
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
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitGasSysInfoExpired_InterSysCco_WaitGSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_GAS_SYS_INFO_EXP);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitWasSysInfoExpired_InterSysCco_WaitWSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());




    /* ��MM/GMM/TAF�������������� */
    NAS_MMC_SndMmCoverageLostInd();

    NAS_MMC_SndGmmCoverageLostInd();

    /* ���·���״̬ */
    NAS_MMC_SndMsccCoverageInd( NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST );




    if (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_WAS_SYS_INFO_EXP);
    }
    else
    {
        NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_TAS_SYS_INFO_EXP);
    }

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);


    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCco_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg;
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;

    pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ת��L�Ĺ�����ϢΪGU��ʽ�� */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stSndSuspendMsg);

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);

    /* ����MM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;

}



VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeInd(
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
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ����GMM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM����:NAS_MMC_SndMmResumeInd */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* ����MM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP);

    /* ������ʱ��TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ��*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */



    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ֪ͨTAF��ǰ�ķ���״̬ */

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmAreaLostInd_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ��ʱ��*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */


    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ֪ͨTAF��ǰ�ķ���״̬ */



    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_COVERAGE_LOST,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enOldNtType;
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

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

    /* �������ģʽ�뵱ǰģʽһ��,ֱ���˳���ǰ״̬�� */
    if ( enOldNtType == NAS_MML_GetCurrNetRatType())
    {
        /*����״̬��ʧ�ܽ��*/
        NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

        /* �˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_EST_IND);

    /*����������ʱ�� TI_NAS_MMC_WAIT_EST_IND*/
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_EST_IND, TI_NAS_MMC_WAIT_EST_IND_LEN);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitAsSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */

    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ֪ͨTAF��ǰ�ķ���״̬ */


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvSysInfoInd_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
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

    /*����״̬���ɹ����*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitLSysInfoIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC,"NAS_MMC_RcvTiWaitLmmSysInfoExpired_InterSysCco_WaitAsSysInfoInd:Entered");

    NAS_MML_InitCampRai(NAS_MML_GetCurrCampPlmnInfo());

    /* ���·���״̬ */



    /* ��TAF�������������� */
    NAS_MMC_SndMsccCoverageInd(NAS_MSCC_PIF_COVERAGE_AREA_CHANGE_MODE_LOST);

    /* ֪ͨTAF��ǰ�ķ���״̬ */


    NAS_MMC_RecordOosEvent(NAS_ERR_LOG_OOS_EVENT_INTER_SYS_CCO_TI_WAIT_LNAS_SYS_INFO_EXP);

    /*����״̬��ʧ�ܽ��*/
    NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_FAIL, NAS_MMC_SUSPEND_FAIL_CAUSE_AREA_LOST, VOS_NULL_PTR);

    /* �˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_STATUS_IND_STRU            *pstStatus;

    pstStatus = (LMM_MMC_STATUS_IND_STRU*)pstMsg;

    if ( VOS_FALSE == pstStatus->bitOpConnState)
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd:bitOpConnState IS VOS_FALSE");
        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_LTE != NAS_MML_GetCurrNetRatType())
    {
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd:NetType is not Lte");
        return VOS_TRUE;
    }

    /* ���ݵ�ǰ���ӽ��������ȷ����CCO���̽������ǻ��ˣ�ͬʱ����LMM������״̬ */
    switch (pstStatus->ulConnState)
    {
        case MMC_LMM_CONN_ESTING:

            /* ����EPS����������Ϊ���� */
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);

            break;
        case MMC_LMM_CONNECTED_SIG:

            /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* ����EPS����������Ϊ���� */
            NAS_MML_SetEpsSigConnStatusFlg(VOS_TRUE);

            /* ����״̬�ɹ���� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            break;

        case MMC_LMM_CONNECTED_DATA:

            /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* ����EPS����������Ϊ���� */
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_TRUE);

            /* ����״̬�ɹ���� */
            NAS_MMC_SndSuspendRsltMsg(MMC_SUSPEND_CAUSE_CELLCHANGE, NAS_MMC_SUSPEND_SUCCESS, NAS_MMC_SUSPEND_FAIL_CAUSE_BUTT, VOS_NULL_PTR);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();
            break;

        case MMC_LMM_CONN_IDLE:

            /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

            /* ����EPS����������Ϊ������ */
            NAS_MML_SetEpsSigConnStatusFlg(VOS_FALSE);

            /* ����EPS����������Ϊ������ */
            NAS_MML_SetEpsServiceConnStatusFlg(VOS_FALSE);

            /* ��MMC��״̬�ó�NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK */
            NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_AS_SUSPEND_IND_FALLBACK);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND, TI_NAS_MMC_WAIT_AS_SUSPEND_IND_LEN);

            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmMmcStatusInd_InterSysCco_WaitEstInd:Unexpected eps con status!");
            break;
    }

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitEstInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLSuspendMsg;
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;

    pstLSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_EST_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_EST_IND);

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ת��L�Ĺ�����ϢΪGU��ʽ�� */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLSuspendMsg, &stSndSuspendMsg);

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);

    /* ����MM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvLmmSuspendInd_InterSysCco_WaitAsSuspendIndFallBack(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_SUSPEND_IND_STRU           *pstLmmSuspendMsg;
    RRMM_SUSPEND_IND_ST                 stSndSuspendMsg;

    pstLmmSuspendMsg   = (LMM_MMC_SUSPEND_IND_STRU*)pstMsg;

    /* ֹͣ������ʱ��  TI_NAS_MMC_WAIT_AS_SUSPEND_IND*/
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_AS_SUSPEND_IND);

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ת��L�Ĺ�����ϢΪGU��ʽ�� */
    NAS_MMC_ConvertLmmSuspendMsgToGUtype(pstLmmSuspendMsg, &stSndSuspendMsg);

    /* ��MM�������ָʾ */
    NAS_MMC_SndMmSuspendInd(&stSndSuspendMsg);

    /* ����MM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_MM_SUSPEND_RSP_FLG);

    /* ��GMM�������ָʾ */
    NAS_MMC_SndGmmSuspendInd(&stSndSuspendMsg);

    /* ����GMM����ظ���� */
    NAS_MMC_SetSuspendRspFlag_InterSysCco(NAS_MMC_GMM_SUSPEND_RSP_FLG);

    /* ״̬Ǩ�Ƶ�NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_SUSPEND_RSP_FALLBACK);

    /* �����ȴ�MM�ظ���ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_SUSPEND_RSP, TI_NAS_MMC_WAIT_MM_SUSPEND_RSP_LEN);

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvLmmResumeInd_InterSysCco_WaitAsResumeIndFallBack(
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
    NAS_MMC_SndGmmResumeInd(&stResumeIndMsg);

    /* ����GMM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_GMM_RESUME_RSP_FLG);

    /* ��resume �Ľ��������MM_MMC_RESUME_IND��Ϣ�У�����MM����:NAS_MMC_SndMmResumeInd */
    NAS_MMC_SndMmResumeInd(&stResumeIndMsg);

    /* ����MM�ȴ���ʶ */
    NAS_MMC_SetResumeRspFlag_InterSysCco(NAS_MMC_MM_RESUME_RSP_FLG);

    /* Ǩ�뵽NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_INTER_SYS_CCO_STA_WAIT_MM_RESUME_RSP_FALLBACK);

    /* ������ʱ��TI_NAS_MMC_WAIT_MM_RESUME_RSP */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_MM_RESUME_RSP, TI_NAS_MMC_WAIT_MM_RESUME_RSP_LEN);

    return VOS_TRUE;
}

#endif

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



