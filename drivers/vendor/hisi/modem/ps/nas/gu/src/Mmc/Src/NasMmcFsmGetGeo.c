

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "NasComm.h"
#include "NasMmlLib.h"
#include "NasMmcFsmGetGeo.h"
#include "NasMmcFsmGetGeoTbl.h"
#include "NasMmcComFunc.h"
#include "NasMmcSndGuAs.h"
#include "NasMmcSndGmm.h"
#include "NasMmcSndMm.h"
#include "NasMmcSndMscc.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "NasMmcSndLmm.h"
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_NAS_MMC_FSM_GET_GEO_C

/* ״̬��������ʼλ�� */

VOS_UINT32 NAS_MMC_RcvMsccGetGeoReq_GetGeo_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatListInfo = VOS_NULL_PTR;

    pstGetGeoRatListInfo                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_GET_GEO_REQ ");

    /*Get_Geo״̬����ʼ�����ͱ�ʾ��ʼ��FFT����Ϊ��ʼ��ʱ��� */
    NAS_MML_SetFftSrchStartTime(VOS_GetSlice());

    /* ���������Ϣ */
    NAS_MMC_SaveCurEntryMsg(ulEventType, pstMsg);

    /* ��ʼ�����Կ��ǻ�ȡ������Ϣ�Ľ��뼼�� */
    NAS_MMC_InitFsmGetGeoRatPrioListCtx_GetGeo();

    /* �����ʼ��֮���ֿ���GET GEO���뼼���б�Ϊ�գ�ֱ�ӷ���ʧ�ܣ��˳�״̬�� */
    if (0 == pstGetGeoRatListInfo->ucRatNum)
    {
        NAS_TRACE_HIGH("rat num is 0, GetGeo fail. ");

        /* ״̬�����ػ�ȡ������Ϣ���ʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ������ҪCSSɨƵ�Ľ��뼼�������ý���ɨƵ�׶� */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN);

    /* ִ��ɨƵ */
    NAS_MMC_PerformBandScan_GetGeo();

    return VOS_TRUE;

}


VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF);

    /* ��abort��־��Ϊtrue */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ��CSS����ֹͣɨƵ��ת���ȴ�ֹͣɨƵ״̬��������ʱ�� */
    NAS_MMC_SndCssStopBandScanReq();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF,
                                 TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF");

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF);

    /* ��abort��־��Ϊtrue */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* ��CSS����ֹͣɨƵ��ת���ȴ�ֹͣɨƵ״̬��������ʱ�� */
    NAS_MMC_SndCssStopBandScanReq();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF,
                                 TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF");

    return VOS_TRUE;
}



VOS_UINT32 NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf   = VOS_NULL_PTR;

    pstBandScanCnf = (CSS_MULTI_BAND_SCAN_CNF_STRU*)pstMsg;

    /* ɨƵ�����ӡ */
    NAS_TRACE_HIGH("enResult = %d, coverageType is, GSM %u, WCDMA %u, LTE %u ",
                    pstBandScanCnf->enResult,
                    pstBandScanCnf->enGsmCoverageType,
                    pstBandScanCnf->enUmtsFddCoverageType,
                    pstBandScanCnf->enLteCoverageType);

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF);

    /* �յ�ɨƵ����¼�ID_CSS_MULTI_BAND_SCAN_CNF
    Get_Geo״̬�����ڴ˺����д���ɨƵ���. ��¼ Band Scan�Ľ�� */
    NAS_MML_SaveFftSrchBandScanResultAndFinishTime(pstBandScanCnf);

    /* �������ֹ��ʶ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬������ɨƵ���abort */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ����Ƶ��Դ */
    if (CSS_MULTI_BAND_SCAN_RESULT_NO_RF == pstBandScanCnf->enResult)
    {
        /* ״̬������ɨƵ���NO RF */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ����ԭ���ʧ�� */
    if (CSS_MULTI_BAND_SCAN_RESULT_SUCC != pstBandScanCnf->enResult)
    {
        /* ״̬������ɨƵ���ʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ɨƵ����ɹ� */
    NAS_TRACE_HIGH("BandScan succ, coverageType is, GSM %u, WCDMA %u, LTE %u ",
                    pstBandScanCnf->enGsmCoverageType,
                    pstBandScanCnf->enUmtsFddCoverageType,
                    pstBandScanCnf->enLteCoverageType);

    /* ����ɨƵ���ˢ��GET GEO���뼼�����ȼ��б� */
    NAS_MMC_UpdateGetGeoRatPrioListCtx_GetGeo(pstBandScanCnf);

    /* ��ά�ɲ⣬���ˢ����Ļ�ȡ������Ϣʹ�õĽ��뼼�����ȼ��б� */
    NAS_MMC_LOG_FsmCtxGetGeoRatListState_GetGeo();

    /* ����PLMN�����׶� */
    NAS_MMC_SetFsmTaskPhase_GetGeo(NAS_MMC_GET_GEO_FSM_TASK_PHASE_PLMN_SEARCH);

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvTiWaitCssBandScanCnfExp_GetGeo_WaitCssBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF");

    /* ��CSS����ֹͣɨƵ��ת���ȴ�ֹͣɨƵ״̬��������ʱ�� */
    NAS_MMC_SndCssStopBandScanReq();

    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF,
                                 TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_STOP_BAND_SCAN_CNF");

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvCssStopBandScanCnf_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_CSS_STOP_BAND_SCAN_CNF");

    /* �յ�ɨƵ����¼�ID_CSS_STOP_BAND_SCAN_CNF,ɨƵ�Ѿ�ֹͣ,��¼ Band Scan�Ľ�� */
    NAS_MML_SaveFftSrchBandScanResultAndFinishTime(VOS_NULL_PTR);

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF);

    /* �������ֹ��ʶ */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);
    }
    else
    {
        /* ���򷵻�ɨƵ����쳣 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABNORMAL, VOS_NULL_PTR);
    }

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF);

    return NAS_MMC_RcvCssBandScanCnf_GetGeo_WaitCssBandScanCnf(ulEventType, pstMsg);
}
VOS_UINT32 NAS_MMC_RcvTiWaitCssStopBandScanCnfExp_GetGeo_WaitCssStopBandScanCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_CSS_STOP_BAND_SCAN_CNF");

    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);
    }
    else
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ�쳣 */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABNORMAL, VOS_NULL_PTR);
    }

    /* �˳�״̬�� */
    NAS_MMC_FSM_QuitFsmL2();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* ���ô�ϱ�ʶ */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ��ȡ������Ϣ����ϣ���Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��GAS����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(UEPS_PID_GAS);

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* ���ô�ϱ�ʶ */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* ��ȡ������Ϣ����ϣ���Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��GAS����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(UEPS_PID_GAS);

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF, enResult = %d", pstSrchCnfMsg->ulSearchRlt);

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF);

    /* ��ȡ������Ϣ�ɹ�������״̬��������״̬����� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ����������л�ȡ������ϢPLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_GSM, pstMsg, &stGeoPlmn);

        /* ״̬�����ػ�ȡ������Ϣ����ɹ� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ������Ϣʧ�� */

    /* �����NO RF���������ȡ������Ϣ��ֱ����Ϊʧ�� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvTiWaitGasGetGeoCnfExp_GetGeo_WaitGasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF.");

    /* ��ȡ������Ϣ��ʱ����Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��GAS����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(UEPS_PID_GAS);

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ���ô�ϱ�ʶ */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ��ȡ������Ϣ����ϣ���Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��WAS����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(WUEPS_PID_WRR);

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ���ô�ϱ�ʶ */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* ��ȡ������Ϣ����ϣ���Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��WAS����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(WUEPS_PID_WRR);

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat     = NAS_MML_NET_RAT_TYPE_BUTT;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstSrchCnfMsg                       = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF, enResult = %d", pstSrchCnfMsg->ulSearchRlt);

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF);

    /* ��ȡ������Ϣ�ɹ�������״̬��������״̬����� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ����������л�ȡ������ϢPLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_WCDMA, pstMsg, &stGeoPlmn);

        /* ״̬�����ػ�ȡ������Ϣ����ɹ� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ������Ϣʧ�� */

    /* �����NO RF���������ȡ������Ϣ��ֱ����Ϊʧ�� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvTiWaitWasGetGeoExp_GetGeo_WaitWasPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF ");

    /* ��ȡ������Ϣ��ʱ����Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��WAS����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndAsStopGetGeoPlmnSearchReq(WUEPS_PID_WRR);

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);
    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_STOP_CNF ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ�������ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF ");

    pstSrchCnfMsg                       = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* ��ȡ������Ϣ�ɹ�������״̬��������״̬����� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        /* ����������л�ȡ������ϢPLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_GSM, pstMsg, &stGeoPlmn);

        /* ״̬�����ػ�ȡ������Ϣ����ɹ� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ����ABORT��ʶ��ֱ���˳�״̬���������ٵ�STOP�ظ� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* �����NO RF���������ȡ������Ϣ��ֱ����Ϊʧ�� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF);

        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ������Ϣ����ԭ���ʧ�ܣ���ͣ��ʱ��������STOP CNF��Ȼ����ִ����һ���Ĵ��� */

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvTiWaitGasStopGetGeoExp_GetGeo_WaitGasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_GAS_PLMN_STOP_CNF ");

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchStopCnf_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_STOP_CNF ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}


VOS_UINT32  NAS_MMC_RcvRrMmPlmnSrchCnf_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    NAS_TRACE_HIGH("Rcv Msg: RRMM_PLMN_SEARCH_CNF ");

    pstSrchCnfMsg = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

    /* ��ȡ������Ϣ�ɹ�������״̬��������״̬����� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        /* ����������л�ȡ������ϢPLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_WCDMA, pstMsg, &stGeoPlmn);

        /* ״̬�����ػ�ȡ������Ϣ����ɹ� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ����ABORT��ʶ��ֱ���˳�״̬���������ٵ�STOP CNF */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* �����NO RF���������ȡ������Ϣ��ֱ����Ϊʧ�� */
    if (RRC_PLMN_SEARCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->ulSearchRlt)
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF);

        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ������Ϣ����ԭ���ʧ�ܣ���ͣ��ʱ��������STOP CNF��Ȼ����ִ����һ���Ĵ��� */

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitWasStopGetGeoExp_GetGeo_WaitWasStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_WAS_PLMN_STOP_CNF ");

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf                       = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_SUSPEND_CNF ");

    /* ����ʧ�ܣ�ֱ�Ӹ�λ */
    if (MMC_AS_SUSPEND_SUCCESS != pstSuspendCnf->ucResult)
    {
        NAS_TRACE_HIGH("suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE");

        /* ���õ���ӿ�RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF);

    /* ��ǰ���뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ���״̬��������ɨƵ�׶Σ�ִ��ɨƵ���� */
    if (NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN == NAS_MMC_GetFsmTaskPhase_GetGeo())
    {
        NAS_MMC_PerformBandScan_GetGeo();
        return VOS_TRUE;
    }

    /* ����һ����PLMN�����׶� */

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvTiWaitGasSuspendCnfExp_GetGeo_WaitGasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF. suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE");

    /* ����ʱ��ֱ�Ӹ�λ�����õ���ӿ�RESET */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_GAS_SUSPEND_FAILURE);
    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvRrMmSuspendCnf_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    RRMM_SUSPEND_CNF_ST                *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf                       = (RRMM_SUSPEND_CNF_ST*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: RRMM_SUSPEND_CNF ");

    /* ����ʧ�ܣ�ֱ�Ӹ�λ */
    if (MMC_AS_SUSPEND_SUCCESS != pstSuspendCnf->ucResult)
    {
        NAS_TRACE_HIGH("suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE");

        /* ���õ���ӿ�RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ����ɹ� */

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF);

    /* ��ǰ���뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ���״̬��������ɨƵ�׶Σ�ִ��ɨƵ���� */
    if (NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN == NAS_MMC_GetFsmTaskPhase_GetGeo())
    {
        NAS_MMC_PerformBandScan_GetGeo();
        return VOS_TRUE;
    }

    /* ����һ����PLMN�����׶� */

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitWasSuspendCnfExp_GetGeo_WaitWasSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF. suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE");

    /* ����ʱ��ֱ�Ӹ�λ�����õ���ӿ�RESET */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_WAS_SUSPEND_FAILURE);
    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ���ô�ϱ�ʶ */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ��ȡ������Ϣ����ϣ���Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��LMM����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndLmmStopGetGeoPlmnSearchReq();

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}
VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ���ô�ϱ�ʶ */
    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    /* ��ȡ������Ϣ����ϣ���Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��LMM����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndLmmStopGetGeoPlmnSearchReq();

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    pstSrchCnfMsg                       = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_PLMN_SRCH_CNF, enResult = %d", pstSrchCnfMsg->enRlst);

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF);

    /* ��ȡ������Ϣ�ɹ�������״̬��������״̬����� */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->enRlst)
    {
        /* ����������л�ȡ������ϢPLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_LTE, pstMsg, &stGeoPlmn);

        /* ״̬�����ػ�ȡ������Ϣ����ɹ� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ������Ϣʧ�� */

    /* �����NO RF���������ȡ������Ϣ��ֱ����Ϊʧ�� */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->enRlst)
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvTiWaitLmmGetGeoCnfExp_GetGeo_WaitLmmPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF ");

    /* ��ȡ������Ϣ��ʱ����Ϊ��ȡʧ�ܣ�֪ͨ��ǰ���뼼��ֹͣ��ȡ������Ϣ */

    /* ��LMM����ֹͣ��ȡ������Ϣ���� */
    NAS_MMC_SndLmmStopGetGeoPlmnSearchReq();

    /* Ǩ�Ƶ��ȴ�ֹͣ��ȡ������Ϣ״̬��������ʱ�� */
    NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF);

    (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF,
                                 TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF_LEN);

    NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_STOP_PLMN_SEARCH_CNF. ");

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvLmmStopPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_STOP_PLMN_SRCH_CNF ");

    /* ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvLmmPlmnSrchCnf_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_PLMN_ID_STRU                stGeoPlmn;
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstSrchCnfMsg = VOS_NULL_PTR;

    PS_MEM_SET((VOS_INT8 *)&stGeoPlmn, 0, sizeof(NAS_MML_PLMN_ID_STRU));

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_PLMN_SRCH_CNF ");

    pstSrchCnfMsg                       = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

    /* ��ȡ������Ϣ�ɹ�������״̬��������״̬����� */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_SUCC == pstSrchCnfMsg->enRlst)
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* ����������л�ȡ������ϢPLMN */
        NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(NAS_MML_NET_RAT_TYPE_LTE, pstMsg, &stGeoPlmn);

        /* ״̬�����ػ�ȡ������Ϣ����ɹ� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_SUCCESS, &stGeoPlmn);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ����ABORT��ʶ��ֱ���˳�״̬����������Ѿ��ظ���CNF��������STOP */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* �����NO RF���������ȡ������Ϣ��ֱ����Ϊʧ�� */
    if (MMC_LMM_PLMN_SRCH_RLT_GET_GEO_NO_RF == pstSrchCnfMsg->enRlst)
    {
        /* ֹͣ�ȴ���ʱ�� */
        NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF);

        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_NO_RF, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ������Ϣ����ԭ���ʧ�ܣ���ͣ��ʱ��������STOP CNF��Ȼ����ִ����һ���Ĵ��� */

    return VOS_TRUE;

}



VOS_UINT32  NAS_MMC_RcvTiWaitLmmStopGetGeoCnfExp_GetGeo_WaitLmmStopPlmnSearchCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;

    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_LMM_PLMN_STOP_CNF ");

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MMC_RcvMmcAbortFsmMsg_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: MMCMMC_ABORT_FSM_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MMC_RcvMsccStopGetGeoReq_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: ID_MSCC_MMC_STOP_GET_GEO_REQ ");

    NAS_MMC_SetAbortFlag_GetGeo(VOS_TRUE);

    /* ����֪ͨMSCC�ظ���� */
    NAS_MMC_SetNotifyMsccFlag_GetGeo(VOS_TRUE);

    return VOS_TRUE;
}
VOS_UINT32  NAS_MMC_RcvLmmSuspendCnf_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat;
    LMM_MMC_SUSPEND_CNF_STRU           *pstSuspendCnf = VOS_NULL_PTR;

    pstSuspendCnf                       = (LMM_MMC_SUSPEND_CNF_STRU*)pstMsg;

    NAS_TRACE_HIGH("Rcv Msg: ID_LMM_MMC_SUSPEND_CNF ");

    /* ����ʧ�ܣ�ֱ�Ӹ�λ */
    if (MMC_LMM_SUCC != pstSuspendCnf->ulRst)
    {
        NAS_TRACE_HIGH("suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE");

        /* ���õ���ӿ�RESET */
        NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
        return VOS_TRUE;
    }

    /* ����ɹ�, ֹͣ�ȴ���ʱ�� */
    NAS_MMC_StopTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF);

    /* ��ǰ���뼼��ΪBUTT */
    NAS_MML_SetCurrNetRatType(NAS_MML_NET_RAT_TYPE_BUTT);

    /* ����ABORT��ʶ��ֱ���˳�״̬�� */
    if (VOS_TRUE == NAS_MMC_GetAbortFlag_GetGeo())
    {
        /* ״̬�����ػ�ȡ������Ϣ���Ϊ����ֹ */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_ABORTED, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ���״̬��������ɨƵ�׶Σ�ִ��ɨƵ���� */
    if (NAS_MMC_GET_GEO_FSM_TASK_PHASE_BAND_SCAN == NAS_MMC_GetFsmTaskPhase_GetGeo())
    {
        NAS_MMC_PerformBandScan_GetGeo();
        return VOS_TRUE;
    }

    /* ����һ����PLMN�����׶Σ�ȡ��һ��Ҫ��ȡ������Ϣ�Ľ��뼼�� */
    if (VOS_TRUE != NAS_MMC_GetNextGetGeoRat_GetGeo(&enDestRat))
    {
        /* ��ȡʧ�ܣ�״̬�����ؽ����ȡ������Ϣʧ�� */
        NAS_MMC_ProcGetGeoRslt_GetGeo(NAS_MMC_GET_GEO_FAIL, VOS_NULL_PTR);

        /* �˳�״̬�� */
        NAS_MMC_FSM_QuitFsmL2();
        return VOS_TRUE;
    }

    /* ��ȡ�ɹ�������һ�����뼼����ȡ������Ϣ */
    NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(enDestRat);

    return VOS_TRUE;

}


VOS_UINT32  NAS_MMC_RcvTiWaitLmmSuspendCnfExp_GetGeo_WaitLmmSuspendCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_TRACE_HIGH("Rcv Msg: TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF. suspend fail: NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE");

    /* ����ʱ��ֱ�Ӹ�λ�����õ���ӿ�RESET */
    NAS_MML_SoftReBoot(NAS_MML_REBOOT_SCENE_MMC_RECEIVE_LMM_SUSPEND_FAILURE);
    return VOS_TRUE;
}

#endif

/* ״̬����������λ�� */

/* ״̬���������õ�����������ʼ����λ�� */

VOS_VOID NAS_MMC_LOG_FsmCtxGetGeoRatListState_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* ѭ������б��е�ÿ����Ԫ��״̬ */
    for (i = 0; i < NAS_MML_MAX_RAT_NUM; i++)
    {
        NAS_TRACE_HIGH("prio %u, enRatType %u, coveragetype %u, IsSrchedFlag %u",
                    i,
                    pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType,
                    pstGetGeoRatInfoList->astGetGeoRatInfo[i].enCoverageType,
                    pstGetGeoRatInfoList->astGetGeoRatInfo[i].ucIsSrchedFlag);
    }

    return;

}
VOS_VOID NAS_MMC_LogSndCssBandScanReq_GetGeo(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU         *pstCssScanInfo
)
{
    NAS_TRACE_HIGH("bitOpMcc = %u, bitOpHighRssi = %u, enBandScanType = %u, aucMcc[0] = %u, aucMcc[1] = %u",
                pstCssScanInfo->bitOpMcc,
                pstCssScanInfo->bitOpHighRssi,
                pstCssScanInfo->enBandScanType,
                pstCssScanInfo->aucMcc[0],
                pstCssScanInfo->aucMcc[1]);

    NAS_TRACE_HIGH("enRatType = %u, %u, %u",
                pstCssScanInfo->stRatList.aucRatList[0],
                pstCssScanInfo->stRatList.aucRatList[1],
                pstCssScanInfo->stRatList.aucRatList[2]);

    return;

}

/*****************************************************************************
 �� �� ��  : NAS_MMC_LOG_PrioRatList_GetGeo
 ��������  : ��ӡSYSCFG��NV���õ�֧�ֵĽ��뼼�����ȼ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : zhaochen 00308719
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_LOG_PrioRatList_GetGeo(VOS_VOID)
{
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstMsPrioRatList  = VOS_NULL_PTR;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoPrioList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    /* ��ȡ��ǰ֧�ֵĽ��뼼���������ȼ� */
    pstMsPrioRatList                    = NAS_MML_GetMsPrioRatList();
    /* ��ά�ɲ⣬ѭ�����SYSCFG���õ�֧�ֵĽ��뼼�����ȼ� */
    for (i = 0; i < pstMsPrioRatList->ucRatNum; i++)
    {
        NAS_TRACE_HIGH("SYSCFG MsPrioRatList: prio %u, enRatType %u ", i, pstMsPrioRatList->aucRatPrio[i]);
    }

    /* ��ȡNV���õĻ�ȡ����λ����Ϣ���뼼�����ȼ��б� */
    pstGetGeoPrioList                   = NAS_MML_GetGeoPrioRatList();
    /* ��ά�ɲ⣬ѭ�����NV���õ�֧�ֵĽ��뼼�����ȼ� */
    for (i = 0; i < pstGetGeoPrioList->ucRatNum; i++)
    {
        NAS_TRACE_HIGH("NV GetGeoPrioList: prio %u, enRatType %u ", i, pstGetGeoPrioList->aucRatPrio[i]);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : NAS_MMC_BuildBandScanInfo_GetGeo
 ��������  : ����ɨƵ��Ϣ
 �������  : NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU*    ����CSS��ɨƵ����
             VOS_UINT32                                �Ƿ��ȡ������Ϣ,
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��10��
    ��    ��   : zhaochen 00308719
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID NAS_MMC_BuildCommBandScanInfo_GetGeo(
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU        *pstCssScanInfo
)
{
    pstCssScanInfo->bitOpMcc         = VOS_FALSE;
    pstCssScanInfo->bitOpHighRssi    = VOS_FALSE;
    pstCssScanInfo->enBandScanType   = CSS_BAND_SCAN_COMM;
    NAS_MMC_ConvertNasRatTypeToCssRatType_GetGeo(&pstCssScanInfo->stRatList);
    return;
}


VOS_VOID NAS_MMC_InitFsmGetGeoRatPrioListCtx_GetGeo(VOS_VOID)
{
    VOS_UINT32                          i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType;
    NAS_MML_PLMN_RAT_PRIO_STRU         *pstGetGeoPrioList    = VOS_NULL_PTR;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* ��ά�ɲ⣬�ֱ����SYSCFG��NV���õ�֧�ֵĽ��뼼�����ȼ� */
    NAS_MMC_LOG_PrioRatList_GetGeo();

    /* ��ȡNV���õĻ�ȡ����λ����Ϣ���뼼�����ȼ��б� */
    pstGetGeoPrioList                   = NAS_MML_GetGeoPrioRatList();

    /* ����ȡ������Ϣ���뼼�����ȼ�˳�򣬵���ǰ֧�ֵĽ��뼼���б��в��� */
    for (i = 0; i < pstGetGeoPrioList->ucRatNum; i++)
    {
        enRatType                       = pstGetGeoPrioList->aucRatPrio[i];

        /* ����˽��뼼����SYSCFG֧�ֵĽ��뼼���б��У�������ӵ�Ŀ���б��� */
        if (VOS_TRUE == NAS_MML_IsNetRatSupported(enRatType))
        {
            pstGetGeoRatInfoList->astGetGeoRatInfo[pstGetGeoRatInfoList->ucRatNum].enRatType      = enRatType;
            pstGetGeoRatInfoList->astGetGeoRatInfo[pstGetGeoRatInfoList->ucRatNum].enCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
            pstGetGeoRatInfoList->astGetGeoRatInfo[pstGetGeoRatInfoList->ucRatNum].ucIsSrchedFlag = VOS_FALSE;
            pstGetGeoRatInfoList->ucRatNum ++;
        }
    }

    return;
}


VOS_VOID NAS_MMC_ConvertNasRatTypeToCssRatType_GetGeo(
    CSS_RAT_LIST                       *pstCssBandScanRatList
)
{
    VOS_UINT32                          i;
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enSrcRat;
    CSS_RAT_TYPE_ENUM_UINT8             enDstRat;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    pstCssBandScanRatList->ucRatNum     = pstGetGeoRatInfoList->ucRatNum;

    /* ��״̬�������������ȡҪɨƵ�Ľ��뼼������ת�� */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        enSrcRat = pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType;

        switch (enSrcRat)
        {
            case NAS_MML_NET_RAT_TYPE_GSM:
                enDstRat                = CSS_RAT_GSM;
                break;

            case NAS_MML_NET_RAT_TYPE_WCDMA:
                enDstRat                = CSS_RAT_UMTS_FDD;
                break;

#if (FEATURE_ON == FEATURE_LTE)
            case NAS_MML_NET_RAT_TYPE_LTE:
                enDstRat                = CSS_RAT_LTE;
                break;
#endif
            default:
                enDstRat                = CSS_RAT_TYPE_BUTT;
                break;
        }

        pstCssBandScanRatList->aucRatList[i] = enDstRat;
    }

    return;

}
NAS_MMC_COVERAGE_TYPE_ENUM_UINT8 NAS_MMC_ConvertCoverageType_GetGeo(
    CSS_COVERAGE_TYPE_ENUM_UINT8        enSrcCoverageType
)
{
    NAS_MMC_COVERAGE_TYPE_ENUM_UINT8    enDestCoverageType;

    switch (enSrcCoverageType)
    {
        case CSS_COVERAGE_TYPE_NONE:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_NONE;
            break;

        case CSS_COVERAGE_TYPE_LOW:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_LOW;
            break;

        case CSS_COVERAGE_TYPE_HIGH:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_HIGH;
            break;

        default:

            enDestCoverageType = NAS_MMC_COVERAGE_TYPE_BUTT;
            break;
    }

    return enDestCoverageType;

}


VOS_VOID NAS_MMC_UpdateGetGeoRatCoverageType_GetGeo(
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf,
    NAS_MMC_GET_GEO_RAT_INFO_STRU      *pstDestRatInfo
)
{
    /* ���ݴ˽��뼼���Ƿ���ڸ��ǣ�����Ƿ���TRUE�������򷵻�FALSE */
    switch (pstDestRatInfo->enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:

            pstDestRatInfo->enCoverageType = NAS_MMC_ConvertCoverageType_GetGeo(pstBandScanCnf->enGsmCoverageType);
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:

            pstDestRatInfo->enCoverageType = NAS_MMC_ConvertCoverageType_GetGeo(pstBandScanCnf->enUmtsFddCoverageType);
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            pstDestRatInfo->enCoverageType = NAS_MMC_ConvertCoverageType_GetGeo(pstBandScanCnf->enLteCoverageType);
            break;
#endif
        default:

            NAS_TRACE_HIGH("enRat ERR.");
            break;
    }

    return;

}
VOS_VOID NAS_MMC_UpdateGetGeoRatPrioListCtx_GetGeo(
    CSS_MULTI_BAND_SCAN_CNF_STRU       *pstBandScanCnf
)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* ����ȡ������Ϣ���뼼�����ȼ��б�������ȼ�˳�򣬵�ɨƵ����в��� */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        /* ���µ�ǰ���뼼���ĸ������� */
        NAS_MMC_UpdateGetGeoRatCoverageType_GetGeo(pstBandScanCnf, &pstGetGeoRatInfoList->astGetGeoRatInfo[i]);
    }

    return;
}



VOS_UINT32 NAS_MMC_GetNextGetGeoRat_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8    *penDestRat
)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* ɨ��������ȡ������Ϣ���뼼�����ȼ��б� */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        if (((NAS_MMC_COVERAGE_TYPE_LOW == pstGetGeoRatInfoList->astGetGeoRatInfo[i].enCoverageType)
          || (NAS_MMC_COVERAGE_TYPE_HIGH == pstGetGeoRatInfoList->astGetGeoRatInfo[i].enCoverageType))
         && (VOS_FALSE == pstGetGeoRatInfoList->astGetGeoRatInfo[i].ucIsSrchedFlag))
        {
            /* �ҵ�δ���������ȡ������Ϣ�Ҵ��ڸ��ǵĽ��뼼�������سɹ� */
            *penDestRat = pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType;

            NAS_TRACE_HIGH("enDestRat is %u", *penDestRat);
            return VOS_TRUE;
        }
    }

    /* ѭ������Ҳδ�ҵ������ػ�ȡʧ�� */
    NAS_TRACE_HIGH("GetNextRat fail");
    return VOS_FALSE;

}
VOS_VOID NAS_MMC_GetGeoPlmnFromPlmnSrchRslt_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType,
    struct MsgCB                       *pstMsg,
    NAS_MML_PLMN_ID_STRU               *pstPlmnId
)
{
    NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU stPlmnSearchInfo;
    RRMM_PLMN_SEARCH_CNF_STRU          *pstGuAsSrchCnfMsg = VOS_NULL_PTR;
    LMM_MMC_PLMN_SRCH_CNF_STRU         *pstLmmSrchCnfMsg  = VOS_NULL_PTR;


    PS_MEM_SET(&stPlmnSearchInfo, 0, sizeof(NAS_MMC_SEARCHED_PLMN_LIST_INFO_STRU));

    switch (enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
        case NAS_MML_NET_RAT_TYPE_WCDMA:

            pstGuAsSrchCnfMsg           = (RRMM_PLMN_SEARCH_CNF_STRU*)pstMsg;

            if (0 < pstGuAsSrchCnfMsg->PlmnIdList.ulHighPlmnNum)
            {
                pstPlmnId->ulMcc        = pstGuAsSrchCnfMsg->PlmnIdList.aHighPlmnList[0].stPlmnId.ulMcc;
                pstPlmnId->ulMnc        = pstGuAsSrchCnfMsg->PlmnIdList.aHighPlmnList[0].stPlmnId.ulMnc;
            }
            else if (0 < pstGuAsSrchCnfMsg->PlmnIdList.ulLowPlmnNum)
            {
                pstPlmnId->ulMcc        = pstGuAsSrchCnfMsg->PlmnIdList.aLowPlmnList[0].PlmnId.stPlmnId.ulMcc;
                pstPlmnId->ulMnc        = pstGuAsSrchCnfMsg->PlmnIdList.aLowPlmnList[0].PlmnId.stPlmnId.ulMnc;
            }
            else
            {
                pstPlmnId->ulMcc        = NAS_MML_INVALID_MCC;
                pstPlmnId->ulMnc        = NAS_MML_INVALID_MNC;
            }

            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:

            pstLmmSrchCnfMsg            = (LMM_MMC_PLMN_SRCH_CNF_STRU*)pstMsg;

            /* ��Lģ�ϱ���PLMNת����MMCʹ�õĸ�ʽ */
            NAS_MMC_ConvertLmmPlmnList2SearchedPlmnListInfo(&pstLmmSrchCnfMsg->stPlmnIdList,
                                                            &stPlmnSearchInfo);

            if (0 < stPlmnSearchInfo.ulHighPlmnNum)
            {
                pstPlmnId->ulMcc        = stPlmnSearchInfo.astHighPlmnList[0].ulMcc;
                pstPlmnId->ulMnc        = stPlmnSearchInfo.astHighPlmnList[0].ulMnc;
            }
            else if (0 < stPlmnSearchInfo.ulLowPlmnNum)
            {
                pstPlmnId->ulMcc        = stPlmnSearchInfo.astLowPlmnList[0].stPlmnId.ulMcc;
                pstPlmnId->ulMnc        = stPlmnSearchInfo.astLowPlmnList[0].stPlmnId.ulMnc;
            }
            else
            {
                pstPlmnId->ulMcc        = NAS_MML_INVALID_MCC;
                pstPlmnId->ulMnc        = NAS_MML_INVALID_MNC;
            }

            break;
#endif
        default:
            break;
    }

    return;

}
VOS_VOID NAS_MMC_SetRatIsSearchedInGetGeoRatPrioList_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
)
{
    VOS_UINT32                          i;
    NAS_MMC_GET_GEO_RAT_INFO_LIST_STRU *pstGetGeoRatInfoList = VOS_NULL_PTR;

    pstGetGeoRatInfoList                = NAS_MMC_GetGeoRatInfoList_GetGeo();

    /* ɨ��������ȡ������Ϣ�Ľ��뼼���б� */
    for (i = 0; i < pstGetGeoRatInfoList->ucRatNum; i++)
    {
        if (enDestRat == pstGetGeoRatInfoList->astGetGeoRatInfo[i].enRatType)
        {
            /* �ҵ�Ŀ����뼼��������Ϊ������ */
            pstGetGeoRatInfoList->astGetGeoRatInfo[i].ucIsSrchedFlag = VOS_TRUE;
            break;
        }
    }

    /* δ�ҵ�����ӡ�쳣 */
    if (i >= pstGetGeoRatInfoList->ucRatNum)
    {
        NAS_TRACE_HIGH("ERR, can't find enDestRat.");
    }

    return;

}
VOS_VOID NAS_MMC_SuspendCurrentRat_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRatType
)
{
    /* ������ڵ�ǰ���뼼��������Ҫ����ǰ���뼼�����ܿ�ʼɨƵ */
    switch (enRatType)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:
            NAS_MMC_SndAsSuspendReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF,
                                         TI_NAS_MMC_WAIT_GAS_SUSPEND_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_SUSPEND_CNF. ");
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsSuspendReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF,
                                         TI_NAS_MMC_WAIT_WAS_SUSPEND_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_SUSPEND_CNF. ");
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmSuspendReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_SUSPEND_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF,
                                         TI_NAS_MMC_WAIT_LMM_SUSPEND_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_SUSPEND_CNF. ");
            break;
#endif
        default:
            break;
    }

    return;
}
VOS_VOID NAS_MMC_SndAsGetGeoReq_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
)
{
    /* ���ݲ�ͬ�Ľ��뼼�������������� */
    switch (enDestRat)
    {
        case NAS_MML_NET_RAT_TYPE_GSM:

            NAS_MMC_SndAsGetGeoPlmnSearchReq(UEPS_PID_GAS);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_GAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF,
                                         TI_NAS_MMC_WAIT_GAS_PLMN_SEARCH_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_GAS_PLMN_SEARCH_CNF. ");
            break;

        case NAS_MML_NET_RAT_TYPE_WCDMA:
            NAS_MMC_SndAsGetGeoPlmnSearchReq(WUEPS_PID_WRR);
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_WAS_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF,
                                         TI_NAS_MMC_WAIT_WAS_PLMN_SEARCH_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_WAS_PLMN_SEARCH_CNF. ");
            break;

#if (FEATURE_ON == FEATURE_LTE)
        case NAS_MML_NET_RAT_TYPE_LTE:
            NAS_MMC_SndLmmGetGeoPlmnSearchReq();
            NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_LMM_PLMN_SEARCH_CNF);
            (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF,
                                         TI_NAS_MMC_WAIT_LMM_PLMN_SEARCH_CNF_LEN);

            NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_LMM_PLMN_SEARCH_CNF. ");
            break;
#endif

        default:
            NAS_TRACE_HIGH("enDestRat is ERR. ");
            break;
    }

    return;
}
VOS_VOID NAS_MMC_PerformBandScan_GetGeo(VOS_VOID)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8               enCurrRat;
    NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU         stCssScanInfo;

    /* ��ǰ���뼼������BUTT��������������ǰ���뼼����ɨƵ�������������ɨƵ */
    enCurrRat                           = NAS_MML_GetCurrNetRatType();

    if (NAS_MML_NET_RAT_TYPE_BUTT > enCurrRat)
    {
        /* ����ǰ���뼼�� */
        NAS_MMC_SuspendCurrentRat_GetGeo(enCurrRat);
    }
    else
    {
        PS_MEM_SET((VOS_INT8 *)&stCssScanInfo, 0, sizeof(NAS_MMC_CSS_MULTI_BAND_SCAN_INFO_STRU));

        /* ����CSS���������������ʼ����ҪCSSɨƵ�Ľ��뼼���б� */
        NAS_MMC_BuildCommBandScanInfo_GetGeo(&stCssScanInfo);

        /* ��ά�ɲ⣬��ӡ��CSS����ɨƵ�������Ϣ */
        NAS_MMC_LogSndCssBandScanReq_GetGeo(&stCssScanInfo);

        /* ��CSS����ɨƵ���� */
        NAS_MMC_SndCssMultiBandScanReq(&stCssScanInfo);

        /* �ѷ���Multi-Band Scan���󣬼�¼ɨƵ��ʼʱ�� */
        NAS_MML_SetFftSrchBandScanStartTime(VOS_GetSlice());

        /* ת����CSSɨƵ���̬��������ʱ�� */
        NAS_MMC_FSM_SetCurrState(NAS_MMC_GET_GEO_STA_WAIT_CSS_BAND_SCAN_CNF);
        (VOS_VOID)NAS_MMC_StartTimer(TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF,
                                     TI_NAS_MMC_WAIT_CSS_BAND_SCAN_CNF_LEN);

        NAS_TRACE_HIGH("STA trans to: NAS_MMC_GET_GEO_STA_WAIT_CSS_BAND_SCAN_CNF. ");
    }

    return;

}
VOS_VOID NAS_MMC_PerformGetGeoPlmnSearch_GetGeo(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enDestRat
)
{
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enCurrRat;

    /* ��ǰ���뼼������BUTT�����ȡ������ϢĿ����뼼����ͬ����������
    ����ǰ���뼼���ٻ�ȡ�������������ֱ�ӻ�ȡ */
    enCurrRat                           = NAS_MML_GetCurrNetRatType();

    NAS_TRACE_HIGH("CurrNetRat %u, enDestRat %u", enCurrRat, enDestRat);

    if ((NAS_MML_NET_RAT_TYPE_BUTT > enCurrRat)
     && (enDestRat != enCurrRat))
    {
        /* ����ǰ���뼼�� */
        NAS_MMC_SuspendCurrentRat_GetGeo(enCurrRat);
    }
    else
    {
        /* ����Ŀ����뼼��Ϊ��ǰ���뼼�� */
        NAS_MML_SetCurrNetRatType(enDestRat);

        /*��¼��ǰ��PLMN Search�Ľ��뼼����ʽ*/
        NAS_MML_SetFftSrchPlmnSrchRatType(enDestRat);

        /* ����ȡ������Ϣ���뼼�����ȼ��б��е�Ŀ����뼼������Ϊ������ */
        NAS_MMC_SetRatIsSearchedInGetGeoRatPrioList_GetGeo(enDestRat);

        /* ��ά�ɲ⣬������º�ĸ��������뼼�����ȼ��б� */
        NAS_MMC_LOG_FsmCtxGetGeoRatListState_GetGeo();

        /* ��MM��GMM��������ָʾ */
        NAS_MMC_SndGmmPlmnSchInit();
        NAS_MMC_SndMmPlmnSchInit();

        /* ��Ŀ����뼼�����ͻ�ȡ������Ϣ���� */
        NAS_MMC_SndAsGetGeoReq_GetGeo(enDestRat);
    }

    return;

}
VOS_UINT32  NAS_MMC_IsMsccGetGeo_GetGeo(VOS_VOID)
{
    NAS_MMC_ENTRY_MSG_STRU             *pstEntryMsg    = VOS_NULL_PTR;

   /* ����FSM ID��ȡ��FSM �����Ϣ */
    pstEntryMsg     = NAS_MMC_GetCurrFsmMsgAddr();

    if (ID_MSCC_MMC_GET_GEO_REQ == NAS_ExtractMsgNameFromEvtType(pstEntryMsg->ulEventType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_VOID NAS_MMC_ProcGetGeoRslt_GetGeo(
    NAS_MMC_GET_GEO_RSLT_ENUM_UINT32    enGetGeoRslt,
    NAS_MML_PLMN_ID_STRU               *pstGeoPlmn
)
{
    if ((VOS_TRUE == NAS_MMC_GetNotifyMsccFlag_GetGeo())
     && (NAS_MMC_GET_GEO_ABORTED == enGetGeoRslt))
    {
        NAS_MMC_SndMsccStopGetGeoCnf();
    }
    else if (VOS_TRUE == NAS_MMC_IsMsccGetGeo_GetGeo())
    {
        NAS_MMC_SndMsccGetGeoCnf(pstGeoPlmn);
    }
    else
    {
    }

    /* ״̬�����ػ�ȡ������Ϣ��� */
    NAS_MMC_SndGetGeoRsltMsg(enGetGeoRslt, pstGeoPlmn);

    /* Get_Geo״̬�ѵõ�����������ڴ˴��ϱ�CHR��� */
    NAS_MML_SaveFftSrchResultAndFinishTime((VOS_UINT8)enGetGeoRslt);
#if (FEATURE_ON == FEATURE_PTM)
    NAS_MMC_RecordFftSrchMccInfo();
#endif
    return;
}

/* ״̬���������õ�����������������λ�� */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

