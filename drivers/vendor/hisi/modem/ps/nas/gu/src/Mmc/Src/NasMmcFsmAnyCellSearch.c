

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndLmm.h"
#include "NasMmcSndInternalMsg.h"
#include "NasMmcTimerMgmt.h"
#include "NasMmcCtx.h"
#include "NasMmcFsmAnyCellSearch.h"
#include "NasMmcFsmAnyCellSearchTbl.h"
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmlCtx.h"
#include "NasMmcSndMscc.h"
#include "NasMmcComFunc.h"
#include "NasMmcSndOm.h"

#include "NasMmcPlmnSelectionStrategy.h"

#include "NasUtranCtrlInterface.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_ANYCELL_SEARCH_C


/*lint -save -e958 */

VOS_UINT32 NAS_MMC_RcvTafPlmnSrchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    enRat = NAS_MML_NET_RAT_TYPE_BUTT;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��ʼ��ANYCELL״̬����Ҫ�����Ľ��뼼�� */
    NAS_MMC_SetRatPrioList_AnyCellSearch(NAS_MML_GetMsPrioRatList());

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }


    /* ѡ��״̬������ѡ���������NO RF��� */


    /* �ڷ���Anycell Search֮ǰ�������Utran��Disable��������Enable Utran */
    NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init();

    /* ���µ�ǰ���������ģʽ */
    NAS_MML_SetCurrNetRatType(enRat);

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    NAS_MMC_UpdateServiceStateSpecPlmnSearch();

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* ��ǰUSIM�������ڻ���CS/PS�򶼿���Ч������Ҫ֪ͨGUAS��ǰ����Ч */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }


    /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvMmcInterPlmnSearchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrRatType;
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU                     *pstInterPlmnSrchMsg = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU                              stRatPrioList;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstInterPlmnSrchMsg = (NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU*)pstMsg;

    /* ��ʼ��ANYCELL״̬����Ҫ�����Ľ��뼼�� */
    NAS_MMC_GetCoverageRatPrioList_Anycell(pstInterPlmnSrchMsg, &stRatPrioList);

    /* ɾ��MS��֧�ֵ�ģʽ */
    NAS_MMC_DelMsUnsupportRat(&stRatPrioList);

    NAS_MMC_SetRatPrioList_AnyCellSearch(&stRatPrioList);

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( VOS_TRUE == NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch() )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_REJECT);

        /* ��״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }




    /* �ڷ���Anycell Search֮ǰ�������Utran��Disable��������Enable Utran */
    NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init();

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    /* �뵱ǰ���뼼����ͬ��������������������ʱ�� ���ߵ�ǰ���뼼��ΪButt,
       ��Ӧ�ĳ�����ѡ��״̬����������״̬���յ�Abort��Ϣ,�����ظ�SUSPNED CNF
       ��Ὣ��ǰ����ģʽ����ΪButt���˳�,��ʾ�������κν��뼼��ֱ�ӷ������� */
    if ((enRat == enCurrRatType)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enCurrRatType))
    {
        NAS_MML_SetCurrNetRatType(enRat);

        pstSimStatus = NAS_MML_GetSimStatus();

        /* ��ǰUSIM�������ڻ���CS/PS�򶼿���Ч������Ҫ֪ͨGUAS��ǰ����Ч */
        if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
          || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
            && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
        {
            NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
        }

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);
    }
    else
    {
        /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_AnyCellSearch(enCurrRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    NAS_MMC_UpdateServiceStateSpecPlmnSearch();

    return VOS_TRUE;

}
VOS_UINT32  NAS_MMC_RcvMmcInterAnycellSearchReq_AnyCellSearch_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enCurrRatType;
    NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU                  *pstAnycellMsg = VOS_NULL_PTR;

    NAS_MML_SIM_STATUS_STRU                                *pstSimStatus    = VOS_NULL_PTR;

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    pstAnycellMsg = (NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU*)pstMsg;

    /* ��ʼ��ANYCELL״̬����Ҫ�����Ľ��뼼�� */

    /* ɾ��MS��֧�ֵ�ģʽ */
    NAS_MMC_DelMsUnsupportRat(&(pstAnycellMsg->stAnycellSrchRatList));

    NAS_MMC_SetRatPrioList_AnyCellSearch(&(pstAnycellMsg->stAnycellSrchRatList));

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat         = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( VOS_TRUE == NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch() )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_REJECT);

        /* ��״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }





    /* �ڷ���Anycell Search֮ǰ�������Utran��Disable��������Enable Utran */
    NAS_MMC_UpdateUtranCapabilityStatus_AnyCellSearch_Init();

    /* ��GMM��������ָʾ */
    NAS_MMC_SndGmmPlmnSchInit();

    /* ��MM��������ָʾ */
    NAS_MMC_SndMmPlmnSchInit();

    NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    enCurrRatType = NAS_MML_GetCurrNetRatType();

    /* �뵱ǰ���뼼����ͬ��������������������ʱ�� ���ߵ�ǰ���뼼��ΪButt,
       ��Ӧ�ĳ�����ѡ��״̬����������״̬���յ�Abort��Ϣ,�����ظ�SUSPNED CNF
       ��Ὣ��ǰ����ģʽ����ΪButt���˳�,��ʾ�������κν��뼼��ֱ�ӷ������� */
    if ((enRat == enCurrRatType)
     || (NAS_MML_NET_RAT_TYPE_BUTT == enCurrRatType))
    {
        NAS_MML_SetCurrNetRatType(enRat);

        pstSimStatus = NAS_MML_GetSimStatus();

        /* ��ǰUSIM�������ڻ���CS/PS�򶼿���Ч������Ҫ֪ͨGUAS��ǰ����Ч */
        if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
          || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
            && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
        {
            NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
        }

        /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);
    }
    else
    {
        /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_AnyCellSearch(enCurrRatType);
    }

    NAS_MMC_UpdateRegStateSpecPlmnSearch();
    NAS_MMC_UpdateServiceStateSpecPlmnSearch();


    return VOS_TRUE;

}
VOS_VOID NAS_MMC_SndSearchRslt_AnyCellSearch(
    NAS_MMC_ANYCELL_SEARCH_RESULT_ENUM_UINT32               enResult
)
{
#if (FEATURE_ON == FEATURE_DSDS)
    NAS_MMC_ENTRY_MSG_STRU                                 *pstEntryMsg    = VOS_NULL_PTR;
    NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU                  *pstInterAnycellSearchReq = VOS_NULL_PTR;


    /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg              = NAS_MMC_GetCurrFsmMsgAddr();
    pstInterAnycellSearchReq = (NAS_MMC_INTER_ANYCELL_SEARCH_REQ_STRU *)pstEntryMsg->aucEntryMsgBuffer;

    if ((MMCMMC_INTER_ANYCELL_SEARCH_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
     && (NAS_MMC_ANYCELL_SEARCH_SCENE_SRV_TRIG_PLMN_SEARCH == pstInterAnycellSearchReq->enAnycellSearchScene))
    {
        /* ҵ�񴥷�������anycell�����ɹ�����Ҫ�ظ�mscc ������� */
        if (NAS_MMC_ANYCELL_SEARCH_SUCC == enResult)
        {
            NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS);
        }
        else
        {
            NAS_MMC_SndMsccSrvAcqCnf(NAS_MSCC_PIF_SRV_ACQ_RESULT_FAIL);
        }
    }
#endif

    NAS_MMC_SndAnycellSearchRslt(enResult);
    return;
}



VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* �������������������ͣ���Ҫ��¼�����������ظ����� */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);


    /* ANYCELL����ʧ��ԭ��ΪNO RF,���˳�ANYCELL״̬������RF��Դ�ͷ� */
    if ( RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt )
    {
        /* ����NO RF���� */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if ( RRC_PLMN_SEARCH_RLT_SPEC_FAIL == pstSrchCnfMsg->ulSearchRlt )
    {
        /* �����ǰΪ��ģ��������ģʽ������������������� */
        enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

        if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
        {
            NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                            VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

            /* ��������ʧ�ܽ�� */
            NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);


            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* Ǩ�Ƶ��ȴ�ϵͳ��Ϣ�ϱ�״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SYSINFO_IND);

        /* ������������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO, TI_NAS_MMC_WAIT_WAS_SYS_INFO_LEN);
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSrchCnf_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_PLMN_SEARCH_CNF_STRU                              *pstSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU *)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* �������������������ͣ���Ҫ��¼�����������ظ����� */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);


    /* ANYCELL����ʧ��ԭ��ΪNO RF,���˳�ANYCELL״̬������RF��Դ�ͷ� */
    if ( RRC_PLMN_SEARCH_RLT_SPEC_NO_RF == pstSrchCnfMsg->ulSearchRlt )
    {
        /* ����NO RF���� */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if ( RRC_PLMN_SEARCH_RLT_SPEC_FAIL == pstSrchCnfMsg->ulSearchRlt )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* �����ǰΪ��ģ��������ģʽ������������������� */
        enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

        if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
        {
            /* ��������ʧ�ܽ�� */
            NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

            /* �˳�״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);
    }
    else
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* Ǩ�Ƶ��ȴ�ϵͳ��Ϣ�ϱ�״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SYSINFO_IND);

        /* ������������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO, TI_NAS_MMC_WAIT_GAS_SYS_INFO_LEN);
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    /* ֪ͨASָֹͣ������ */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ������������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֪ͨASֹͣ����ָ������ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬��������������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    RRMM_REL_IND_STRU                  *pstRrmmRelIndMsg    = VOS_NULL_PTR;

    pstRrmmRelIndMsg = (RRMM_REL_IND_STRU *)pstMsg;

    /* �����ж�ԭ��ֵ */

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnSrchCnf: ENTERED");

    /* ֹͣ������ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);


    /* ANYCELL����ʧ��ԭ��ΪNO RF,���˳�ANYCELL״̬������RF��Դ�ͷ� */
    if (RRC_REL_CAUSE_NO_RF == pstRrmmRelIndMsg->ulRelCause)
    {
        /* ����NO RF���� */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

        return VOS_TRUE;
    }

   /* ��ȡ�¸�Ҫ������������뼼�� */
   enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

   if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
   {
       NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                       VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

       /* ��������ʧ�ܽ�� */
       NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

       /* �˳�״̬�� */
       NAS_MMC_FSM_QuitFsmL2();

       return VOS_TRUE;
   }

   /* ��GMM��������ָʾ */
   NAS_MMC_SndGmmPlmnSchInit();

   /* ��MM��������ָʾ */
   NAS_MMC_SndMmPlmnSchInit();

   NAS_MMC_SndMsccCampOnInd(VOS_FALSE);

   NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_START,
                   VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

   enCurrRatType = NAS_MML_GetCurrNetRatType();

   /* �뵱ǰ���뼼����ͬ��������������������ʱ�� ���ߵ�ǰ���뼼��ΪButt,
      ��Ӧ�ĳ�����ѡ��״̬����������״̬���յ�Abort��Ϣ,�����ظ�SUSPNED CNF
      ��Ὣ��ǰ����ģʽ����ΪButt���˳�,��ʾ�������κν��뼼��ֱ�ӷ������� */
   if ((enRat == enCurrRatType)
    || (NAS_MML_NET_RAT_TYPE_BUTT == enCurrRatType))
   {
       NAS_MML_SetCurrNetRatType(enRat);

       /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
       NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);
   }
   else
   {
       /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
       NAS_MMC_SndSuspendReq_AnyCellSearch(enCurrRatType);
   }

   return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasPlmnSrchCnfExpired_AnyCellSearch_WaitWasPlmnSrchCnf: Timer Expired");

    /* �������������������ͣ���Ҫ��¼�����������ظ����� */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

    /* ֪ͨASָֹͣ������ */
    NAS_MMC_SndAsPlmnSrchStopReq(WUEPS_PID_WRR);

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬ */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_STOP_CNF);

    /* ������������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasPlmnSrchCnfExpired_AnyCellSearch_WaitGasPlmnSrchCnf: Timer Expired");

    /* �������������������ͣ���Ҫ��¼�����������ظ����� */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

    NAS_MMC_SndAsPlmnSrchStopReq(UEPS_PID_GAS);

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬��������������ʱ��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_STOP_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */
        if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
          && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        }
        else
        {
            NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_TD_SUSPEND_FAILURE);
        }

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* �ȴ�GU����ظ��������û�detach PS�ᵼ��disable LTE,��ʱ��ȡ�����¸����뼼��
       ����ΪBUTT */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���ĵ�ǰ����ģʽ������ģʽ */
    NAS_MML_SetCurrNetRatType(enRat);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* ��ǰUSIM�������ڻ���CS/PS�򶼿���Ч������Ҫ֪ͨGUAS��ǰ����Ч */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }


    /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvRrMmSuspendCnf_AnyCellSearch_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    pstSuspendCnf = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == pstSuspendCnf->ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* �ȴ�GU����ظ��������û�detach PS�ᵼ��disable LTE,��ʱ��ȡ�����¸����뼼��
       ����ΪBUTT */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ���ĵ�ǰ����ģʽ������ģʽ*/
    NAS_MML_SetCurrNetRatType(enRat);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* ��ǰUSIM�������ڻ���CS/PS�򶼿���Ч������Ҫ֪ͨGUAS��ǰ����Ч */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }

    /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��¼��Ҫ�˳���ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurRat;

    enCurRat      = NAS_MML_GetCurrNetRatType();

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitAsSuspendCnfExpired_AnyCellSearch_WaitAsSuspendCnf: Timer Expired");

    /* ���ɻָ����ϣ���λ */

    if ( (NAS_UTRANCTRL_UTRAN_MODE_FDD == NAS_UTRANCTRL_GetCurrUtranMode())
      && (NAS_MML_NET_RAT_TYPE_WCDMA   == enCurRat) )
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_WAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_GSM == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_GAS_SUSPEND_CNF_EXPIRED);
    }
    else if ( NAS_MML_NET_RAT_TYPE_LTE == enCurRat)
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_LMM_SUSPEND_CNF_EXPIRED);
    }
    else
    {
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_WAIT_TD_SUSPEND_CNF_EXPIRED);
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enRat;

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�AnyCell״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ǰΪ��ģ��������ģʽ������������������� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ж�ԭ��ֵ */

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF );

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvRrMmRelInd_AnyCellSearch_WaitWasPlmnStopCnf: Timer Expired");

    /* ��������Abort��� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

    /* �˳�AnyCell״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvRrMmPlmnSearchStopCnf_AnyCellSearch_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�AnyCell״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ǰΪ��ģ��������ģʽ������������������� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);


        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enRat;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitWasStopCnfExpired_AnyCellSearch_WaitWasPlmnStopCnf: Timer Expired");

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�AnyCell״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ǰΪ��ģ��������ģʽ������������������� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_WCDMA);


    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8        enRat;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitGasStopCnfExpired_AnyCellSearch_WaitGasPlmnStopCnf: Timer Expired");

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�AnyCell״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ǰΪ��ģ��������ģʽ������������������� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_GSM);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;


    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();

#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* ֹͣ�ȴ�ϵͳ��Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SYS_INFO);

    /* ״̬����Ϊ��ǰ�Ѿ�פ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    NAS_MMC_SetAsAnyCampOn(VOS_TRUE);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg,enLCapabilityStatus);
#endif

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ����Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_WasSysInfo(pstMsg);

    /* W�£���NAS_MML_PLMN_FORBID_PLMN��������RRC���ӣ��ҿ�����
       ����NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS,ֻ����CS+PS�������CS����Ч�����
       ��֪ͨ�������ѡ����ΪRESEL_SUITABLE */
    if (VOS_TRUE == NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch())
    {
        NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_RESEL_SUITABLE);

        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));

        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);

        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }
    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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

    /*ת��ϵͳ��Ϣ֪ͨ �� MM/GMM */
    NAS_MMC_SndMmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmWasSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(),VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmWcdmaSysInfoInd(pstMsg);
#endif

    /* ����ANYCELL�����ɹ���� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_SUCC);


    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvSysInfoInd_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurCsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldCsRestrictInfo;
    NAS_MML_ACCESS_RESTRICTION_STRU                         *pstCurPsRestrictInfo = VOS_NULL_PTR;
    NAS_MML_ACCESS_RESTRICTION_STRU                          stOldPsRestrictInfo;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;
   
#if (FEATURE_ON == FEATURE_LTE)

    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;


    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stOldCsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stOldPsRestrictInfo, 0, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* ֹͣ�ȴ�ϵͳ��Ϣ�Ķ�ʱ��  */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SYS_INFO);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    NAS_MMC_SetAsAnyCampOn(VOS_TRUE);

#if (FEATURE_ON == FEATURE_LTE)
    NAS_MMC_RcvGuSysInfoIndSetLteAbility(pstMsg, enLCapabilityStatus);
#endif

    /* ���Anycell Search״̬���յ�GAS��ϵͳ��Ϣ����ĿǰUtran��Enable��������Disable Utran */
    NAS_MMC_RcvGasSysInfoSetUtranCapabilityStatus();

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ����Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);


        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    pstCurCsRestrictInfo    = NAS_MML_GetCsAcRestrictionInfo();
    pstCurPsRestrictInfo    = NAS_MML_GetPsAcRestrictionInfo();

    PS_MEM_CPY(&stOldCsRestrictInfo, pstCurCsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));
    PS_MEM_CPY(&stOldPsRestrictInfo, pstCurPsRestrictInfo, sizeof(NAS_MML_ACCESS_RESTRICTION_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_GasSysInfo(pstMsg);

    /* G�£���NAS_MML_PLMN_FORBID_PLMN��������RRC���ӣ��ҿ�����
       ��֪ͨ�������ѡ����ΪRESEL_SUITABLE */
    if (VOS_TRUE == NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch())
    {
        NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

        NAS_MMC_SndRrMmCellSelReq(RRC_NAS_RESEL_SUITABLE);

        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndGuAsEquPlmnReq(&stSndEquPlmnInfo, NAS_MML_GetCurrNetRatType());
        NAS_MMC_SndOmEquPlmn();

        NAS_MMC_SndMsccEplmnInfoInd(&stSndEquPlmnInfo);
    }
    /* פ��С���仯����������ʱ���ϱ�ϵͳ��Ϣ */
    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();
    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();

    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);

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
    NAS_MMC_SndMmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);
    NAS_MMC_SndGmmGsmSysInfoInd (NAS_MMC_GetCurrentLaiForbbidenType(), VOS_FALSE, pstMsg);

#if (FEATURE_ON == FEATURE_LTE)

    NAS_MMC_SndLmmGsmSysInfoInd(pstMsg);
#endif

    /* ����ANYCELL�����ɹ���� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_SUCC);


    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitWasSysInfoInd: Timer Expired");

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ����Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ANYCELL����ʧ�ܽ�� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}



VOS_UINT32  NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitSysInfoExpired_AnyCellSearch_WaitGasSysInfoInd: Timer Expired");

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ����Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ANYCELL����ʧ�ܽ�� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_RcvLmmPlmnSrchCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    LMM_MMC_PLMN_SRCH_CNF_STRU                             *pstLmmSrchCnfMsg = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8                         enRat;

    pstLmmSrchCnfMsg = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* �������������������ͣ���Ҫ��¼�����������ظ����� */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);


    /* ANYCELL����ʧ��ԭ��ΪNO RF,���˳�ANYCELL״̬������RF��Դ�ͷ� */
    if (MMC_LMM_PLMN_SRCH_RLT_SPEC_NO_RF == pstLmmSrchCnfMsg->enRlst)
    {
        /* ����NO RF���� */
        NAS_MMC_ProcNoRf_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if ( MMC_LMM_PLMN_SRCH_RLT_SPEC_FAIL == pstLmmSrchCnfMsg->enRlst )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* �����ǰΪ��ģ��������ģʽ������������������� */
        enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

        if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
        {
            /* ��������ʧ�ܽ�� */
            NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

            /* �˳�AnyCell״̬�� */
            NAS_MMC_FSM_QuitFsmL2();

            return VOS_TRUE;
        }

        /* �������LMM���͹������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }
    else
    {
        NAS_MMC_SetAsAnyCampOn(VOS_TRUE);

        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_SUCCESS,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);


        /* Ǩ�Ƶ��ȴ�ϵͳ��Ϣ�ϱ�״̬ */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SYSINFO_IND);

        /* ������������ʱ�� */
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO, TI_NAS_MMC_WAIT_LMM_SYS_INFO_LEN);
    }

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLmmAttachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰLTE������״̬��ΪDISABLE ״̬���򲻴������Ϣ */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf: unexpect message received");

        return VOS_TRUE;
    }

    /* ֪ͨASֹͣ����ָ������ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��ǰLTE������״̬��ΪDISABLE ״̬���򲻴������Ϣ */
    if ( NAS_MML_LTE_CAPABILITY_STATUS_DISABLE_UNNOTIFY_AS != NAS_MML_GetLteCapabilityStatus())
    {
        /* �쳣��ӡ */
        NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvLmmDetachCnf_AnyCellSearch_WaitLmmPlmnSrchCnf: unexpect message received");

        return VOS_TRUE;
    }

    /* ֪ͨASֹͣ����ָ������ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֪ͨASֹͣ����ָ������ */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmPlmnSrchCnfExpired_AnyCellSearch_WaitLmmPlmnSrchCnf: Timer Expired");

    /* �������������������ͣ���Ҫ��¼�����������ظ����� */
    NAS_MMC_SetSearchedFlag_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ֪ͨASֹͣ����ָ������ */
    NAS_MMC_SndLmmPlmnSrchStopReq();

    /* Ǩ�Ƶ��ȴ�����ֹͣ�ظ�״̬��*/
    NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_STOP_CNF);

    /* ����������ʱ�� */
    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    return VOS_TRUE;
}

VOS_UINT32 NAS_MMC_RcvLmmSuspendCnf_AnyCellSearch_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    RRMM_SUSPEND_CNF_ST                 stGuSuspendCnf;
    LMM_MMC_SUSPEND_CNF_STRU           *pstLmmSuspendCnf = VOS_NULL_PTR;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;
    NAS_MML_SIM_STATUS_STRU            *pstSimStatus    = VOS_NULL_PTR;

    /* Lģʱ�������¸�ʽת�� */
    pstLmmSuspendCnf = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    stGuSuspendCnf.ucResult = (VOS_UINT8)pstLmmSuspendCnf->ulRst;

    /* ֹͣ��ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    if (MMC_AS_SUSPEND_FAILURE == stGuSuspendCnf.ucResult)
    {
        /* ���ɻָ�����,���õ���ӿ�RESET */

        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);

        return VOS_TRUE;
    }

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�AnyCell״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();
    if (NAS_MML_NET_RAT_TYPE_BUTT == enRat)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMC, "ERROR:FsmId Error");
    }

    /* ���ĵ�ǰ����ģʽ������ģʽ */
    NAS_MML_SetCurrNetRatType(enRat);

    pstSimStatus = NAS_MML_GetSimStatus();

    /* ��ǰUSIM�������ڻ���CS/PS�򶼿���Ч������Ҫ֪ͨGUAS��ǰ����Ч */
    if ( (VOS_FALSE   == NAS_MML_GetSimPresentStatus())
      || ( (VOS_FALSE == pstSimStatus->ucSimPsRegStatus)
        && (VOS_FALSE == pstSimStatus->ucSimCsRegStatus) ) )
    {
        NAS_MMC_SndAsNasUsimStatus(RRC_NAS_USIM_INVALID);
    }

    /* �������LMM�����������󣬸��ݲ�ͬ������ģʽ��Ǩ�Ƶ���ͬ��L2״̬��������������ʱ�� */
    NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(enRat);

    /* ��֤����L�ص�GUʱPS��ע��״̬ʼ��Ϊ2,�˴�����һ�θ���(����LʱL�����ϱ���ע��״̬��Ϊ2) */
    NAS_MMC_UpdateRegStateSpecPlmnSearch();

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_RcvLmmPlmnSearchStopCnf_AnyCellSearch_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    NAS_MMC_StopTimer( TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF );

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�AnyCell״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �޴��ʱ:�����ǰLTE������״̬Ϊdisable LTE���������¸���LTE������
        �����ǰLTE������״̬ΪEnable LTE,�������¸����õ�LTE����
        Enable LTE��Ӧ�ĳ���Ϊ:��LMM���������ʱ�յ�LmmDetachCnf����ҪDisable LTE,Ǩ����LmmStopCnf״̬
        �ڵȴ�LmmStopCnfʱ���յ�LmmAttachCnf������ҪEnable LTE,��ʱ���յ�LmmStopCnf��Ҫ����ȥLTE������ */

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* �¸�Ҫ���������粻����ʱ���˳�״̬�� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �¸�Ҫ������������LTE���磬ֱ�ӷ��������������ȹ���LTE */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* ��LMM������������Ǩ��״̬��������������ʱ�� */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }
    else
    {
        /* ��LMM���͹�������Ǩ��״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }

    return VOS_TRUE;



}



VOS_UINT32 NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat;

    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLmmStopCnfExpired_AnyCellSearch_WaitLmmPlmnStopCnf: Timer Expired");

    NAS_MMC_UpdateRfAvailFlg_AnyCellSearch();

    /* �д��ʱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ��������Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* �˳�AnyCell״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �޴��ʱ:�����ǰLTE������״̬Ϊdisable LTE���������¸���LTE������
        �����ǰLTE������״̬ΪEnable LTE,�������¸����õ�LTE����
        Enable LTE��Ӧ�ĳ���Ϊ:��LMM���������ʱ�յ�LmmDetachCnf����ҪDisable LTE,Ǩ����LmmStopCnf״̬
        �ڵȴ�LmmStopCnfʱ���յ�LmmAttachCnf������ҪEnable LTE,��ʱ���յ�LmmStopCnf��Ҫ����ȥLTE������ */

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    /* �¸�Ҫ���������粻����ʱ���˳�״̬�� */
    if ( NAS_MML_NET_RAT_TYPE_BUTT == enRat )
    {
        NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                        VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

        /* ��������ʧ�ܽ�� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);


        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* �¸�Ҫ������������LTE���磬ֱ�ӷ��������������ȹ���LTE */
    if (NAS_MML_NET_RAT_TYPE_LTE == enRat)
    {
        /* ��LMM������������Ǩ��״̬��������������ʱ�� */
        NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }
    else
    {
        /* ��LMM���͹�������Ǩ��״̬��������������ʱ�� */
        NAS_MMC_SndSuspendReq_AnyCellSearch(NAS_MML_NET_RAT_TYPE_LTE);
    }

    return VOS_TRUE;


}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvLSysInfoInd_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_CAMP_PLMN_INFO_STRU                             stOldCampInfo;

    NAS_MML_EQUPLMN_INFO_STRU                              *pstEquPlmnInfo = VOS_NULL_PTR;
    NAS_MML_EQUPLMN_INFO_STRU                               stSndEquPlmnInfo;

    NAS_MMC_SPEC_PLMN_SEARCH_STATE_ENUM_UINT8                enSpecPlmnSearchState;

    PS_MEM_SET(&stOldCampInfo, 0, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));
    PS_MEM_SET(&stSndEquPlmnInfo, 0, sizeof(NAS_MML_EQUPLMN_INFO_STRU));

    /* ֹͣ�ȴ�ϵͳ��Ϣ�Ķ�ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SYS_INFO);

    /* ����פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_CAMP_ON);

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ����Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /*�����Ż���LTE�µ�С�������仯��LMM��ͨ��ϵͳ��Ϣ֪ͨMMC*/
    /* �����ϵ�פ��������Ϣ */
    pstCurCampInfo  = NAS_MML_GetCurrCampPlmnInfo();
    PS_MEM_CPY(&stOldCampInfo, pstCurCampInfo, sizeof(NAS_MML_CAMP_PLMN_INFO_STRU));

    /* ����ϵͳ��Ϣ������MML��ȫ������ */
    NAS_MMC_UpdateNetworkInfo_LmmSysInfo(pstMsg);


    enSpecPlmnSearchState = NAS_MMC_GetSpecPlmnSearchState();

    if ((VOS_TRUE == NAS_MML_IsCampPlmnInfoChanged(&stOldCampInfo, pstCurCampInfo))
     || (NAS_MMC_SPEC_PLMN_SEARCH_RUNNING == enSpecPlmnSearchState))
    {
        /* �����ϱ� */
        NAS_MMC_SndMsccSysInfo();
    }

    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_STOP);
    /* Modified by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */




    NAS_MMC_SetAsAnyCampOn(VOS_TRUE);

    /* L�£���NAS_MML_PLMN_FORBID_PLMN���������� ,����Ч�Ҳ���SIM����
       ��֪ͨLMM��ѡ����ΪRESEL_SUITABLE */
    if (VOS_TRUE == NAS_MMC_IsNeedSndLmmSuitableCellSelReq_AnyCellSearch())
    {
        NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

        NAS_MMC_SndLmmCellSelReq(MMC_LMM_RESEL_SUITABLE);

        pstEquPlmnInfo = NAS_MML_GetEquPlmnList();
        PS_MEM_CPY(&stSndEquPlmnInfo, pstEquPlmnInfo, sizeof(stSndEquPlmnInfo));
        NAS_MMC_BuildSndLmmEquPlmnInfo(&stSndEquPlmnInfo);
        NAS_MMC_SndLmmEquPlmnReq(&stSndEquPlmnInfo);
        NAS_MMC_SndOmEquPlmn();
    }

    /* CBS�ϱ�*/
    NAS_MMC_SndCbaMsgNetModInd(NAS_MML_NET_RAT_TYPE_LTE);

    NAS_MMC_SndMsccCampOnInd(VOS_TRUE);

    /* ת��GMMϵͳ��Ϣ,��rabmʹ�� */
    NAS_MMC_SndGmmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndMmLteSysinfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    NAS_MMC_SndLmmLteSysInfoInd((LMM_MMC_SYS_INFO_IND_STRU*)pstMsg);

    /* ����ANYCELL�����ɹ���� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_SUCC);

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �쳣��ӡ */
    NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_RcvTiWaitLSysInfoExpired_AnyCellSearch_WaitLSysInfoInd: Timer Expired");

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    /* �����ǰ��Ҫ�˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        /* ����Abort��� */
        NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_ABORTED);

        /* ֱ���˳���ǰ״̬�� */
        NAS_MMC_FSM_QuitFsmL2();

        return VOS_TRUE;
    }

    /* ����ANYCELL����ʧ�ܽ�� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* ֱ���˳���ǰ״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;

}




#endif


VOS_VOID NAS_MMC_GetCoverageRatPrioList_Anycell(
    NAS_MMC_INTER_PLMN_SEARCH_REQ_STRU     *pstInterPlmnSrchReq,
    NAS_MML_PLMN_RAT_PRIO_STRU             *pstRatPrioList
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU                   *pstPlmnRatInfo;
    VOS_UINT32                                              i;
    VOS_UINT32                                              ulIdx;

    ulIdx          =  0;
    pstPlmnRatInfo = pstInterPlmnSrchReq->astInterPlmnSearchInfo;

    /* ���ڲ������ṹ�У���ȡ��ǰ������������Ƚ��뼼���б� */
    for ( i = 0 ; i < NAS_MML_MAX_RAT_NUM; i++ )

    {
        if (NAS_MML_NET_RAT_TYPE_BUTT != pstPlmnRatInfo[i].enRatType)
        {
            pstRatPrioList->aucRatPrio[ulIdx] = pstPlmnRatInfo[i].enRatType;
            ulIdx++;
        }
    }

    /* ���н��뼼��������ʱ��ʹ�� SYSCFG�趨�Ľ��뼼�� */
    if (0 == ulIdx)
    {
        PS_MEM_CPY(pstRatPrioList,
                   NAS_MML_GetMsPrioRatList(), sizeof(NAS_MML_PLMN_RAT_PRIO_STRU));
    }

    else
    {
        pstRatPrioList->ucRatNum = (VOS_UINT8)ulIdx;
    }


    /* ��ǰ���뼼��֧��ʱ���Ե�ǰ���뼼�������� */
    NAS_MML_SortSpecRatPrioHighest(NAS_MML_GetCurrNetRatType(), pstRatPrioList);

}

VOS_VOID NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    VOS_UINT32                                              ulWaitWasPlmnSrchCnfTimerLen;
#if (FEATURE_ON == FEATURE_LTE)
    NAS_MML_LTE_CAPABILITY_STATUS_ENUM_UINT32               enLCapabilityStatus;

    /* ��ȡLTE����״̬ */
    enLCapabilityStatus  = NAS_MML_GetLteCapabilityStatus();
#endif

    ulWaitWasPlmnSrchCnfTimerLen = NAS_MMC_GetWaitWasPlmnSrchCnfTimerLen();

    /* ���µ�ǰΪ��פ��״̬ */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

#if (FEATURE_ON == FEATURE_LTE)
    /* �����ǰ�Ѿ�֪ͨLTE disable,��ʱ����LTE�Ĺ���������Ҫenable LTE */
    if ((VOS_TRUE == NAS_MML_GetDisableLteRoamFlg())
     && (NAS_MML_NET_RAT_TYPE_LTE == enRat))
    {
        /* ��ǰLTE�����ָ����û���ΪĬ��ֵ */
        if ((NAS_MML_LTE_CAPABILITY_STATUS_BUTT == enLCapabilityStatus)
         || (NAS_MML_LTE_CAPABILITY_STATUS_REENABLE_NOTIFIED_AS == enLCapabilityStatus))
        {
            if (NAS_MML_RAT_CAPABILITY_STATUS_DISABLE != NAS_MML_GetLteForbiddenStatusFlg())
            {
                NAS_MMC_SndEnableLteNotify();
                NAS_MMC_ClearDisabledLtePlmnId();
                NAS_MMC_SetEnableLteTimerExpireFlag(VOS_FALSE);
            }
        }

        if (NAS_MMC_TIMER_STATUS_RUNING == NAS_MMC_GetTimerStatus(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER))
        {
            NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_ENABLE_LTE_TIMER);
        }

        /* ����disable LTE������� */
        NAS_MML_SetDisableLteRoamFlg(VOS_FALSE);
    }
#endif

    /* ���ݲ�ͬ�Ľ��뼼������AnyCell�������� */
    switch (enRat)
    {
#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmPlmnAnyCellSrchReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF, TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);
            break;
#endif
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsPlmnAnyCellSrchReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF, ulWaitWasPlmnSrchCnfTimerLen);
            break;

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsPlmnAnyCellSrchReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_PLMN_SEARCH_CNF);

            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF, NAS_MMC_GetWaitGasPlmnSearchCnfTimerLen(VOS_FALSE));
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndAnyCellPlmnSearchReq_AnyCellSearch: Rat not support.");
            break;
    }

    return;
}


VOS_VOID NAS_MMC_SndSuspendReq_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat
)
{
    /* ״̬����Ϊ��ǰδפ�� */
    NAS_MMC_SetAsCellCampOn(NAS_MMC_AS_CELL_NOT_CAMP_ON);
    NAS_MMC_SetSpecPlmnSearchState(NAS_MMC_SPEC_PLMN_SEARCH_RUNNING);

    NAS_MMC_SetAsAnyCampOn(VOS_FALSE);

    /* ���ݲ�ͬ�Ľ��뼼�����õȴ������ظ���״̬ */
    switch (enRat)
    {
        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF, TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);
            break;
#endif

        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_ANYCELL_SEARCH_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF, TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);
            break;

        default:
            NAS_WARNING_LOG(WUEPS_PID_MMC, "NAS_MMC_SndSuspendReq_AnyCellSearch: Rat not support.");
            break;
    }

    return;
}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_AnyCellSearch(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* ��¼��Ҫ�˳���ǰ״̬����־ */
    NAS_MMC_SetAbortFlag_AnyCellSearch(VOS_TRUE);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MMC_IsNeedSndAsSuitableCellSelReq_AnyCellSearch(VOS_VOID)
{
    VOS_UINT32                                              ulIsPlmnForbidGPRSFlg;
    VOS_UINT32                                              ulPlmnLaType;
    NAS_MML_MS_MODE_ENUM_UINT8                              enMsMode;

    ulIsPlmnForbidGPRSFlg   = VOS_FALSE;
    ulPlmnLaType            = NAS_MMC_GetCurrentLaiForbbidenType();
    enMsMode                = NAS_MML_GetMsMode();

    /* ����14�����,ֻ��PS ONLY����CS+PSʱCS����Ч���������Ϊ��ֹ����,����Ϊ��ֹ���� */
    if ((NAS_MML_MS_MODE_PS_ONLY           == enMsMode)
     && (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS == ulPlmnLaType))
    {
        ulIsPlmnForbidGPRSFlg = VOS_TRUE;
    }

    /* AģʽʱCS����Чʱ */
    if ((VOS_FALSE                         == NAS_MML_GetSimCsRegStatus())
     && (NAS_MML_MS_MODE_PS_CS             == enMsMode)
     && (NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS == ulPlmnLaType))
    {
        ulIsPlmnForbidGPRSFlg = VOS_TRUE;
    }

    if (NAS_MML_PLMN_FORBID_ROAM_LA == (ulPlmnLaType & NAS_MML_PLMN_FORBID_ROAM_LA))
    {
        return VOS_FALSE;
    }

    /* W�£���NAS_MML_PLMN_FORBID_PLMN��������RRC���ӣ��ҿ�����
       ����NAS_MML_PLMN_FORBID_PLMN_FOR_GPRS,ֻ����CS+PS�������CS����Ч�����
       ��֪ͨ�������ѡ����ΪRESEL_SUITABLE */
    if ((VOS_TRUE                 == NAS_MML_IsUsimStausValid())
     && (NAS_MML_PLMN_FORBID_PLMN != ulPlmnLaType)
     && (VOS_FALSE                == ulIsPlmnForbidGPRSFlg))
    {

        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 NAS_MMC_IsNeedSndLmmSuitableCellSelReq_AnyCellSearch(VOS_VOID)
{
    NAS_MML_CAMP_PLMN_INFO_STRU                            *pstCurCampInfo = VOS_NULL_PTR;
    NAS_MML_SIM_FORBIDPLMN_INFO_STRU                       *pstForbidPlmnInfo = VOS_NULL_PTR;
    NAS_MML_SIM_STATUS_STRU                                *pstSimStatus    = VOS_NULL_PTR;
    VOS_UINT32                                              ulUsimStausFlg;
    VOS_UINT32                                              ulForbidRoamingFlg;
    VOS_UINT32                                              ulIsPlmnForbidGPRSFlg;
    NAS_MML_SIM_TYPE_ENUM_UINT8                             enSimType;
    NAS_MMC_REG_CONTROL_ENUM_UINT8                          enRegCtrl;

    pstCurCampInfo    = NAS_MML_GetCurrCampPlmnInfo();
    pstForbidPlmnInfo = NAS_MML_GetForbidPlmnInfo();

    ulIsPlmnForbidGPRSFlg = NAS_MML_IsBcchPlmnIdInDestSimPlmnList(&(pstCurCampInfo->stLai.stPlmnId),
                                          pstForbidPlmnInfo->ucForbGprsPlmnNum,
                                          pstForbidPlmnInfo->astForbGprsPlmnList);

    /* ��ֹLTE���� */
    ulForbidRoamingFlg = NAS_MMC_IsNeedDisableLteRoam(pstCurCampInfo->stLai.stPlmnId.ulMcc);

    pstSimStatus = NAS_MML_GetSimStatus();

    ulUsimStausFlg = VOS_TRUE;

    /* ������λ��PS��Ч����Ϊ����Ч */
    if ( ( VOS_FALSE == NAS_MML_GetSimPresentStatus() )
      || ( VOS_FALSE == pstSimStatus->ucSimPsRegStatus))
    {
        ulUsimStausFlg = VOS_FALSE;
    }

    enSimType = NAS_MML_GetSimType();
    enRegCtrl = NAS_MMC_GetRegCtrl();

    if ( (NAS_MML_PLMN_FORBID_PLMN != NAS_MMC_GetCurrentLaiForbbidenType())
      && (VOS_TRUE  == ulUsimStausFlg)
      && (VOS_FALSE == ulIsPlmnForbidGPRSFlg)
      && (VOS_FALSE == ulForbidRoamingFlg)
      && (NAS_MML_SIM_TYPE_SIM != enSimType)
      && (NAS_MMC_REG_CONTROL_BY_3GPP_MMC == enRegCtrl))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
#endif



VOS_UINT32 NAS_MMC_IsNeedRejectAnycellSerach_AnyCellSearch(VOS_VOID)
{
    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus = VOS_NULL_PTR;
    VOS_UINT32                          ulRrcConnExistFlag;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRatType;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enAnycellSearchRat;

    pstConnStatus = NAS_MML_GetConnStatus();
    enCurrRatType = NAS_MML_GetCurrNetRatType();
    ulRrcConnExistFlag   = NAS_MML_IsRrcConnExist();

    /* ��ǰ���Ӳ����ڣ�����ҪREJ */
    if ( VOS_FALSE == ulRrcConnExistFlag )
    {
        return VOS_FALSE;
    }

    /* ��ȡ�¸�Ҫ������������뼼�� */
    enAnycellSearchRat = NAS_MMC_GetNextSearchRat_AnyCellSearch();

    if (NAS_MML_NET_RAT_TYPE_LTE == enCurrRatType)
    {
        /* ��ǰ��L�£���һ��Ҫ�����Ľ��뼼��ΪGU������Ҫ����Lʱ�򣬼�������·��Ҳ�ǿ��Է���ANYCELL������ */
        if (NAS_MML_NET_RAT_TYPE_LTE != enAnycellSearchRat)
        {
            return VOS_FALSE;
        }

        /* ��L������·ʱ����׼����L�½���ANYCELL��������ֱ�Ӿܾ���ǰ��ANYCELL���� */
        return VOS_TRUE;
    }

    /* ��GU�£������ǰ������RRC��·������Գ��Խ���ANYCELL����,����ܾ���ǰ��ANYCELL���� */
    if (VOS_TRUE == pstConnStatus->ucRrcStatusFlg)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_MMC_ProcNoRf_AnyCellSearch(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enNasRat
)
{
    /* ����NO RF ��� */
    NAS_MML_SetCurrRatRfAvailFlg(enNasRat, VOS_FALSE);

    /* ��MSCC֪ͨ��ǰNO RF��Ϣ  */
    NAS_MMC_SndMsccRfAvailInd(VOS_FALSE);

    /* ��������ʧ�ܽ�� */
    NAS_MMC_SndSearchRslt_AnyCellSearch(NAS_MMC_ANYCELL_SEARCH_FAIL);

    /* ��RRM����ע�� */
    NAS_MMC_RegisterRrmResourceNtf(enNasRat, RRM_PS_TASK_TYPE_NAS_SEARCH);

    NAS_EventReport(WUEPS_PID_MMC, NAS_OM_EVENT_PLMN_SELECTION_FAILURE,
                    VOS_NULL_PTR, NAS_OM_EVENT_NO_PARA);

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return;
}
VOS_VOID NAS_MMC_UpdateRfAvailFlg_AnyCellSearch(VOS_VOID)
{
    if (VOS_TRUE == NAS_MML_GetRfAvailFlg())
    {
        return;
    }

    /* �������no rf��ǣ��������֪ͨmma */
    NAS_MML_SetCurrRatRfAvailFlg(NAS_MML_NET_RAT_TYPE_BUTT, VOS_TRUE);

    /* ��MSCC֪ͨ��ǰNO RF��Ϣ  */
    NAS_MMC_SndMsccRfAvailInd(VOS_TRUE);

    /* �������̱�����ϱ�MSCC֮ǰ��Ϊno rf��û���ϱ���״̬ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_AnyCellSearch())
    {
        NAS_MMC_SndMsccCurrServiceRelatedInfo();
    }

    return;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif




