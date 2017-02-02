

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsCommonDef.h"
#include "Taf_Tafm_Remote.h"
#include "MnApsComm.h"
#include "MmaAppLocal.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsProcNvim.h"
#include "TafAgentInterface.h"
#include "TafApsPreproc.h"
#include "TafApsComFunc.h"
#include "TafApsSndAt.h"
#include "ApsNdInterface.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "TafApsSndL4a.h"
#include "MnApsMultiMode.h"
#endif
#include "TafSdcLib.h"
#include "TafApsProcIpFilter.h"
#include "TafApsApi.h"

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_aps_pif.h"
#include "TafApsSndXcc.h"
#include "taf_aps_ppp_pif.h"
#include "xreg_aps_pif.h"
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
#include "hsm_aps_pif.h"
#include "TafApsSndHsm.h"
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */
#endif

#include "TafMmaInterface.h"
#include "TafApsMntn.h"

#include "NasOmInterface.h"
#include "NasOmTrans.h"

#include "NasUsimmApi.h"
#include "NasComm.h"

/* Added by y00314741 for CDMA Iteration 15, 2015-5-21, begin */
#include "ehsm_aps_pif.h"
#include "taf_aps_dhcp_pif.h"
#include "TafApsSndCds.h"
#include "TafApsSndDhcp.h"
#include "TafApsSndEhsm.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-21, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-7-1, begin */
#include "TafApsSndPpp.h"
#include "cnas_cttf_hrpd_pa_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-7-1, end */


#include "TafApsProcEpdszid.h"
#include "TafApsSndInternalMsg.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_PREPROC_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 TAF_APS_RcvAtGetDsFlowInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstMsgHeader;
    TAF_PS_GET_DSFLOW_INFO_REQ_STRU    *pstGetDsFlowInfoReq;
    TAF_DSFLOW_QUERY_INFO_STRU          stDsFlowQryInfo;

    /* ��ʼ�� */
    pstMsgHeader        = (TAF_PS_MSG_STRU *)pstMsg;
    pstGetDsFlowInfoReq = (TAF_PS_GET_DSFLOW_INFO_REQ_STRU *)(pstMsgHeader->aucContent);

    /* �����ϱ���Ϣ��ʼ�� */
    PS_MEM_SET(&stDsFlowQryInfo, 0, sizeof(TAF_DSFLOW_QUERY_INFO_STRU));

    /* ��ѯ����RAB���ص�������Ϣ */
    TAF_APS_QryAllRabDsFlowStats(&stDsFlowQryInfo);

    /* ��AT�ظ���ѯ����������Ϣ */
    TAF_APS_SndGetDsFlowInfoCnf(&(pstGetDsFlowInfoReq->stCtrl),
                                TAF_ERR_NO_ERROR,
                               &stDsFlowQryInfo);


    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvAtClearDsFlowReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstMsgHeader;
    TAF_PS_CLEAR_DSFLOW_REQ_STRU       *pstClearDsFlowReq;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx;


    /* ��ʼ�� */
    pstMsgHeader        = (TAF_PS_MSG_STRU*)pstMsg;
    pstClearDsFlowReq   = (TAF_PS_CLEAR_DSFLOW_REQ_STRU*)(pstMsgHeader->aucContent);

    /* �������RAB���ص�������Ϣ */
    TAF_APS_ClearAllRabDsFlowStats();

    /* ���AP�������ͳ�� */
    TAF_APS_ClearApDsFlowStats();

    /* �����������NV����ʹ�ܣ����NV������ʷ��Ϣ */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();
    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowSave2NvFlg)
    {
        TAF_APS_ClearDsFlowInfoInNv();
    }

    /* ��AT�ظ���� */
    TAF_APS_SndClearDsFlowCnf(&(pstClearDsFlowReq->stCtrl),
                               TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtConfigDsFlowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstMsgHeader;
    TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU  *pstConfigDsFlowRptReq;
    VOS_UINT32                          ulRptCmdStatus;

    /* ��ʼ�� */
    pstMsgHeader            = (TAF_PS_MSG_STRU*)pstMsg;
    pstConfigDsFlowRptReq   = (TAF_PS_CONFIG_DSFLOW_RPT_REQ_STRU*)(pstMsgHeader->aucContent);

    /* ���µ����������������ϱ���ȫ�ֱ��� */
    if ( VOS_TRUE == pstConfigDsFlowRptReq->stReportConfigInfo.ulRptEnabled )
    {
        /* ����AT�˿������ϱ� */
        ulRptCmdStatus = VOS_TRUE;
    }
    else
    {
        /* ֹͣAT�˿������ϱ� */
        ulRptCmdStatus = VOS_FALSE;
    }

    TAF_SDC_UpdateRptCmdStatus(TAF_SDC_RPT_CMD_DSFLOWRPT, ulRptCmdStatus);

    /* ��AT�ظ������� */
    TAF_APS_SndConfigDsFlowRptCnf(&(pstConfigDsFlowRptReq->stCtrl),
                                  TAF_ERR_NO_ERROR);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU   *pstSetRptCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU          *pstDsFlowCtx    = VOS_NULL_PTR;
    TAF_PS_CAUSE_ENUM_UINT32                enCause;
    VOS_UINT32                              ulResult;

    pstSetRptCfgReq = (TAF_PS_SET_APDSFLOW_RPT_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx    = TAF_APS_GetDsFlowCtxAddr();

    if (VOS_TRUE == pstSetRptCfgReq->stRptCfg.ulRptEnabled)
    {
        /* ��ֵ����: KBYTE ---> BYTE */
        ulResult = VOS_64Multi32(0,                                             /* ulMultiplicandHigh */
                                 pstSetRptCfgReq->stRptCfg.ulFluxThreshold,     /* ulMultiplicandLow */
                                 TAF_APS_1_KBYTE_1024_BYTE,                     /* ulMultiplicator */
                                 &(pstDsFlowCtx->ulFluxThresHigh),              /* pulProductHigh */
                                 &(pstDsFlowCtx->ulFluxThresLow));              /* pulProductLow */
        if (VOS_OK == ulResult)
        {
            /* ����������ֵ�ϱ����� */
            pstDsFlowCtx->ulFluxThresRptFlg = VOS_TRUE;
            pstDsFlowCtx->ulFluxThresKByte  = pstSetRptCfgReq->stRptCfg.ulFluxThreshold;

            enCause                         = TAF_PS_CAUSE_SUCCESS;
        }
        else
        {
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvSetApDsFlowRptCfgReq_PreProc: VOS_64Multi32 failed.");

            enCause                         = TAF_PS_CAUSE_INVALID_PARAMETER;
        }
    }
    else
    {
        /* ����������ֵ�ϱ����� */
        pstDsFlowCtx->ulFluxThresRptFlg     = VOS_FALSE;
        pstDsFlowCtx->ulFluxThresKByte      = 0;
        pstDsFlowCtx->ulFluxThresHigh       = 0;
        pstDsFlowCtx->ulFluxThresLow        = 0;
        pstDsFlowCtx->ulTotalFluxHigh       = 0;
        pstDsFlowCtx->ulTotalFluxLow        = 0;

        enCause                             = TAF_PS_CAUSE_SUCCESS;
    }

    TAF_APS_SndSetApDsFlowRptCfgCnf(&(pstSetRptCfgReq->stCtrl), enCause);
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvGetApDsFlowRptCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU   *pstGetRptCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU          *pstDsFlowCtx    = VOS_NULL_PTR;
    TAF_APDSFLOW_RPT_CFG_STRU               stRptCfg;

    pstGetRptCfgReq = (TAF_PS_GET_APDSFLOW_RPT_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx    = TAF_APS_GetDsFlowCtxAddr();

    /* ��ȡAPDSFLOW���ò��� */
    stRptCfg.ulRptEnabled    = pstDsFlowCtx->ulFluxThresRptFlg;
    stRptCfg.ulFluxThreshold = pstDsFlowCtx->ulFluxThresKByte;

    TAF_APS_SndGetApDsFlowRptCfgCnf(&(pstGetRptCfgReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS,
                                    &stRptCfg);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU    *pstSetNvWriteCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU              *pstDsFlowCtx        = VOS_NULL_PTR;

    pstSetNvWriteCfgReq = (TAF_PS_SET_DSFLOW_NV_WRITE_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx        = TAF_APS_GetDsFlowCtxAddr();

    /* ��������дNV���� */
    if (VOS_TRUE == pstSetNvWriteCfgReq->stNvWriteCfg.ucEnabled)
    {
        /* ����дNV�����ѿ���, ���ݵ�ǰ����дNV�����Ƿ�������ͬ���� */
        if (VOS_TRUE == pstDsFlowCtx->ucDsFlowSave2NvFlg)
        {
            /* �������дNV���ڱ仯, ˢ�µ�ǰ������NV, ������ʱ�� */
            if (pstDsFlowCtx->ucDsFlowSavePeriod != pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval)
            {
                pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

                TAF_APS_SaveDsFlowInfoToNv();

                TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                                  TAF_APS_INVALID_PDPID);

                TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                                   (pstDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                                   TAF_APS_INVALID_PDPID);
            }
        }
        /* ����дNV����δ����, ʹ������дNV����, ������ʱ�� */
        else
        {
            pstDsFlowCtx->ucDsFlowSave2NvFlg = VOS_TRUE;
            pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

            TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                               (pstDsFlowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                               TAF_APS_INVALID_PDPID);
        }
    }
    /* �ر�����дNV���� */
    else
    {
        /* ����дNV�����ѿ���, ˢ�µ�ǰ������NV, ֹͣ��ʱ�� */
        if (VOS_TRUE == pstDsFlowCtx->ucDsFlowSave2NvFlg)
        {
            pstDsFlowCtx->ucDsFlowSave2NvFlg = VOS_FALSE;
            pstDsFlowCtx->ucDsFlowSavePeriod = pstSetNvWriteCfgReq->stNvWriteCfg.ucInterval;

            TAF_APS_SaveDsFlowInfoToNv();

            TAF_APS_StopTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                              TAF_APS_INVALID_PDPID);
        }
    }

    TAF_APS_SndSetDsFlowNvWriteCfgCnf(&(pstSetNvWriteCfgReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvGetDsFlowNvWriteCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU    *pstGetNvWriteCfgReq = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU              *pstDsFlowCtx        = VOS_NULL_PTR;
    TAF_DSFLOW_NV_WRITE_CFG_STRU                stNvWriteCfg;

    pstGetNvWriteCfgReq = (TAF_PS_GET_DSFLOW_NV_WRITE_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    pstDsFlowCtx        = TAF_APS_GetDsFlowCtxAddr();

    /* ��ȡDSFLOWдNV���ò��� */
    PS_MEM_SET(&stNvWriteCfg, 0x00, sizeof(TAF_DSFLOW_NV_WRITE_CFG_STRU));
    stNvWriteCfg.ucEnabled  = pstDsFlowCtx->ucDsFlowSave2NvFlg;
    stNvWriteCfg.ucInterval = pstDsFlowCtx->ucDsFlowSavePeriod;

    TAF_APS_SndGetDsFlowNvWriteCfgCnf(&(pstGetNvWriteCfgReq->stCtrl),
                                      TAF_PS_CAUSE_SUCCESS,
                                      &stNvWriteCfg);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiDsFlowReportExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx = VOS_NULL_PTR;
    TAF_CTRL_STRU                       stCtrl;
    TAF_DSFLOW_REPORT_STRU              stTotalDsFlowRptInfo;

    PS_MEM_SET(&stCtrl, 0x00, sizeof(TAF_CTRL_STRU));

    /* ��ȡDSFLOW������ */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* �����ǰ��PDP������� */
    if (VOS_FALSE == TAF_APS_CheckIfActiveRabIdExist())
    {
        return VOS_TRUE;
    }

    /* ��ʼ��������ѯ��Ϣ���� */
    PS_MEM_SET(&stTotalDsFlowRptInfo, 0, sizeof(TAF_DSFLOW_REPORT_STRU));

    /* ��ѯ���м���RAB���ص��ϱ�������Ϣ */
    TAF_APS_QryAllRabDsFlowReportInfo(&stTotalDsFlowRptInfo);

    pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt = (pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt + 1)
                                              % pstApsDsflowCtx->ucDsFlowATRptPeriod;

    if (0 == pstApsDsflowCtx->ucDsFlowATRptTmrExpCnt)
    {
        /* ��AT�ϱ�������Ϣ */
        stCtrl.ulModuleId    = WUEPS_PID_AT;
        stCtrl.usClientId    = MN_CLIENT_ID_BROADCAST;
        stCtrl.ucOpId        = 0;

        TAF_APS_SndDsFlowRptInd(&stCtrl, TAF_ERR_NO_ERROR, &stTotalDsFlowRptInfo);
    }

    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowOMReportFlg)
    {
        if (0 == pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt)
        {
            /* ��OM�ϱ�������Ϣ */
            TAF_APS_SndDsFlowOMRptInd(&stTotalDsFlowRptInfo);
        }

        pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt = (pstApsDsflowCtx->ucDsFlowOMRptTmrExpCnt + 1)
                                                  % pstApsDsflowCtx->ucDsFlowOMRptPeriod;
    }

    /* ������ֵ�ϱ����� */
    TAF_APS_ProcApDsFlowRpt();

    /* ���浱ǰ������Ϣ������ͳ��������ȫ�ֱ����������´ζ�ʱ����ʱ�������� */
    TAF_APS_UpdateAllRabCurrentFlowInfo();

    /* APSͳ�Ƶ�������MBΪ��λ�ģ�����Ҫת��ΪMb���� */
    TAF_APS_SwitchDdrRateByCurrentRate((stTotalDsFlowRptInfo.ulCurrentReceiveRate * 8),
                                       (stTotalDsFlowRptInfo.ulCurrentSendRate * 8));

    /* ���������ϱ���ʱ��*/
    TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_REPORT,
                       TI_TAF_APS_DSFLOW_REPORT_LEN,
                       TAF_APS_INVALID_PDPID);

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvTiDsFlowWriteNvExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsflowCtx;

    /* ��ʼ�� */
    pstApsDsflowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ������ʷ������NVʹ�ܣ�����ʷ������Ϣ���浽NV�� */
    TAF_APS_SaveDsFlowInfoToNv();

    /* �жϱ�����ʷ������NV�Ƿ�ʹ�� */
    if (VOS_TRUE == pstApsDsflowCtx->ucDsFlowSave2NvFlg)
    {
        /* ����������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_DSFLOW_WRITE_NV,
                           (pstApsDsflowCtx->ucDsFlowSavePeriod * 60 * TIMER_S_TO_MS_1000),
                           TAF_APS_INVALID_PDPID);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtGetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPrimPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetPdpInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                            *pstPsMsg;
    VOS_UINT8                                   ucIndex;
    VOS_UINT32                                  ulPdpCtxInfoLen;
    VOS_UINT32                                  ulCidNum;
    TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU       *pstGetPdpCtxInfoReq;
    TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU       *pstGetPdpCtxInfoCnf;

    /* ��ʼ����Ϣ */
    pstPsMsg            = (TAF_PS_MSG_STRU*)pstMsg;

    ulPdpCtxInfoLen     = 0;
    ulCidNum            = 0;
    pstGetPdpCtxInfoReq = (TAF_PS_GET_PDP_CONTEXT_INFO_REQ_STRU*)pstPsMsg->aucContent;
    pstGetPdpCtxInfoCnf = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulPdpCtxInfoLen     = sizeof(TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU);

    /* �����ڴ� */
    pstGetPdpCtxInfoCnf = (TAF_PS_GET_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulPdpCtxInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetPdpCtxInfoCnf )
    {
        MN_ERR_LOG("MN_APS_RcvGetPdpCtxInfoReq:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        /*��PDPû�ж���*/
        if (TAF_FREE == g_TafCidTab[ucIndex].ucUsed)
        {
            continue;
        }

        /* ����������PDP,ֻҪ�Ƕ���ľͷ��� */
        pstGetPdpCtxInfoCnf->ulCid[ulCidNum]    = ucIndex;
        ulCidNum++;
    }

    /* ��д�¼�����ͷ */
    pstGetPdpCtxInfoCnf->stCtrl     = pstGetPdpCtxInfoReq->stCtrl;
    pstGetPdpCtxInfoCnf->ulCidNum   = ulCidNum;
    pstGetPdpCtxInfoCnf->enCause    = TAF_PS_CAUSE_SUCCESS;

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_PDP_CONTEXT_INFO_CNF,
                    pstGetPdpCtxInfoCnf,
                    ulPdpCtxInfoLen);

    /* �ͷ����ڴ��PDP�����Ĳ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetPdpCtxInfoCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetSecPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetTftInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetPdpIpAddrInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPdpIpAddrInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetAnsModeInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPdpCtxStateReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}




#if ( FEATURE_ON == FEATURE_LTE )


VOS_UINT32 TAF_APS_RcvAtGetDynamicPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgcontrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetDynamicSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgscontrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetDynamicTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgtftrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucIndex;
    VOS_UINT32                          ulErrCode;
    VOS_UINT32                          ulEqosInfoLen;
    VOS_UINT32                          ulCidNum;
    TAF_PS_MSG_STRU                    *pstPsMsg;
    TAF_PS_GET_EPS_QOS_INFO_REQ_STRU   *pstGetEqosInfoReq;
    TAF_PS_GET_EPS_QOS_INFO_CNF_STRU   *pstGetEqosInfoCnf;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (TAF_PS_MSG_STRU*)pstMsg;
    ulErrCode               = TAF_PARA_OK;
    ulEqosInfoLen           = 0;
    ulCidNum                = 0;
    pstGetEqosInfoReq       = (TAF_PS_GET_EPS_QOS_INFO_REQ_STRU*)pstPsMsg->aucContent;
    pstGetEqosInfoCnf       = VOS_NULL_PTR;

    /* �����¼����ݳ��� */
    ulEqosInfoLen     = sizeof(TAF_PS_GET_EPS_QOS_INFO_CNF_STRU)
                            + ((TAF_MAX_CID + 1) * sizeof(TAF_EPS_QOS_EXT_STRU));

    /* �����ڴ� */
    pstGetEqosInfoCnf = (TAF_PS_GET_EPS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                WUEPS_PID_TAF,
                                ulEqosInfoLen);

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstGetEqosInfoCnf )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvAtGetEpsQosInfoReq_PreProc:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    /* ��д�¼����� */
    for ( ucIndex = 1; ucIndex <= TAF_MAX_CID; ucIndex++ )
    {
        PS_MEM_SET(&(pstGetEqosInfoCnf->astEpsQosInfo[ulCidNum]),
                   0x00,
                   sizeof(TAF_EPS_QOS_EXT_STRU));

        /* ��ȡEPS QOS��Ϣ */
        TAF_APS_QueEpsQosInfo(ucIndex, &(pstGetEqosInfoCnf->astEpsQosInfo[ulCidNum]), &ulErrCode);

        if ( TAF_PARA_OK == ulErrCode )
        {
            ulCidNum++;
        }
    }

    /* ��д�¼�����ͷ */
    pstGetEqosInfoCnf->stCtrl           = pstGetEqosInfoReq->stCtrl;
    pstGetEqosInfoCnf->ulCidNum         = ulCidNum;
    pstGetEqosInfoCnf->enCause          = TAF_PS_CAUSE_SUCCESS;

    /* ���ش����� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_EPS_QOS_INFO_CNF,
                     pstGetEqosInfoCnf,
                     ulEqosInfoLen);

    /* �ͷ����ڴ��PDP�����Ĳ������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstGetEqosInfoCnf);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtGetDynamicEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgeqosrdpReq(pstPsMsg->aucContent);

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvAtGetLteCsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_PS_MSG_STRU                 *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aGetLteCsReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_LTECS_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;

}


VOS_UINT32 TAF_APS_RcvL4aGetLteCsCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_GET_LTE_CS_CNF_STRU        *pstPsMsg = VOS_NULL_PTR;
    TAF_PS_LTECS_CNF_STRU              *pstApsAtLteCsInfo = VOS_NULL_PTR;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg = (APS_L4A_GET_LTE_CS_CNF_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, ulPara);

        /* ����AT������ */
        pstApsAtLteCsInfo =  (TAF_PS_LTECS_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PS_LTECS_CNF_STRU));

        if ( VOS_NULL_PTR == pstApsAtLteCsInfo )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetLteCsCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        PS_MEM_SET(pstApsAtLteCsInfo, 0x00,  sizeof( TAF_PS_LTECS_CNF_STRU));

        /* L4A�������ת�� */
        pstApsAtLteCsInfo->enCause = TAF_APS_TransL4aErrorCode(pstPsMsg->ulErrorCode);

        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstApsAtLteCsInfo->stCtrl,
                                                              TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetLteCsCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtLteCsInfo);

            return VOS_TRUE;
        }

        if(pstApsAtLteCsInfo->enCause == TAF_PS_CAUSE_SUCCESS )
        {
            pstApsAtLteCsInfo->stLteCs.ucSG     = pstPsMsg->ucSmsOverSGs;
            pstApsAtLteCsInfo->stLteCs.ucIMS    = pstPsMsg->ucSmsOverIMS;
            pstApsAtLteCsInfo->stLteCs.ucCSFB   = pstPsMsg->ucCSFB;
            pstApsAtLteCsInfo->stLteCs.ucVCC    = pstPsMsg->ucSrVcc;
            pstApsAtLteCsInfo->stLteCs.ucVoLGA  = pstPsMsg->ucVoLGA;
        }

        /* ����Ϣ���� */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_LTECS_INFO_CNF,
                         pstApsAtLteCsInfo,
                         sizeof(TAF_PS_LTECS_CNF_STRU));

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtLteCsInfo);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, ulPara);

    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetCemodeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aGetCemodeReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_CEMODE_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvL4aGetCemodeCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_GET_CEMODE_CNF_STRU        *pstPsMsg;
    TAF_PS_CEMODE_CNF_STRU             *pstApsAtCemodeInfo = NULL;
    VOS_UINT32                          i;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_GET_CEMODE_CNF_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_GET_CEMODE_CNF, ulPara);

        /* ����AT������ */
        pstApsAtCemodeInfo =  (TAF_PS_CEMODE_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF, sizeof(TAF_PS_CEMODE_CNF_STRU));

        if ( VOS_NULL_PTR == pstApsAtCemodeInfo )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetCemodeCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        PS_MEM_SET(pstApsAtCemodeInfo, 0x00,  sizeof( TAF_PS_CEMODE_CNF_STRU));

        /* L4A�������ת�� */
        pstApsAtCemodeInfo->enCause = TAF_APS_TransL4aErrorCode(pstPsMsg->ulErrorCode);;

        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstApsAtCemodeInfo->stCtrl,
                                                              TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aGetCemodeCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtCemodeInfo);

            return VOS_TRUE;
        }

        if (pstApsAtCemodeInfo->enCause == TAF_PS_CAUSE_SUCCESS )
        {
            pstApsAtCemodeInfo->stCemode.enCurrentUeMode    = pstPsMsg->ulCurrentUeMode;
            pstApsAtCemodeInfo->stCemode.ulSupportModeCnt   = pstPsMsg->ulSupportModeCnt;

            for (i = 0; i < 4; i++)
            {
                pstApsAtCemodeInfo->stCemode.aenSupportModeList[i] = pstPsMsg->aulSupportModeList[i];
            }
        }

            /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_CEMODE_INFO_CNF,
                         pstApsAtCemodeInfo,
                         sizeof( TAF_PS_CEMODE_CNF_STRU));

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstApsAtCemodeInfo);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF, ulPara);

    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtSetPdprofInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara  = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                            TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetPdprofReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                     (VOS_UINT32*)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_SET_PROFILE_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_PDPROFMOD_CNF_STRU     *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_PROFILE_INFO_REQ_STRU   *pstSetPdprofInfoReq;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_PDPROFMOD_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdprofInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo  = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetPdprofInfoCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetPdprofInfoReq = (TAF_PS_SET_PROFILE_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;

        stCtrl = pstSetPdprofInfoReq->stCtrl;

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����Primary PDP�����ĺ�AUTHDATA����(NDIS)  */
            Aps_DefPsPdprofmod(pstSetPdprofInfoReq->stCtrl.usClientId,
                               pstSetPdprofInfoReq->stCtrl.ucOpId,
                               &(pstSetPdprofInfoReq->stPdpProfInfo),
                               &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetPdprofInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}


#endif
VOS_UINT32 TAF_APS_RcvAtGetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetAuthDataInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetUmtsQosInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetUmtsQosMinInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetDynamicUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvGetDynamicUmtsQosInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetPdpAuthInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPdpAuthInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvGetPdpDnsInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvAtSetPrimPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                             *pstPsMsg;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetPdpCtxInfoReq->stCtrl)))
    {
        TAF_APS_SndSetPrimPdpCtxInfoCnf(&(pstSetPdpCtxInfoReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
#endif
#if ( FEATURE_ON == FEATURE_LTE )
    /* ����LTE�����ֱ�ִ�� */
    /* ĿǰESM��֧��PPP���͵Ĳ��� */
    if ((VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
     && (TAF_PDP_PPP != pstSetPdpCtxInfoReq->stPdpContextInfo.enPdpType))
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgdcontReq(pstSetPdpCtxInfoReq);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstSetPdpCtxInfoReq),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstSetPdpCtxInfoReq));

        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                         (VOS_UINT32*)pstSetPdpCtxInfoReq,
                                         sizeof(TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU),
                                         ulPara);

       return VOS_TRUE;
    }

#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetPrimPdpCtxInfoReq(pstSetPdpCtxInfoReq);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtSetSecPdpCtxInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgdscontReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU),
                                         ulPara);

	    return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetSecPdpCtxInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetTftInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgtftReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_TFT_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }

#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetTftInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetAnsModeInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetCgautoReq(pstPsMsg->aucContent);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));
        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                         (VOS_UINT32*)pstPsMsg->aucContent,
                                         sizeof(TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetAnsModeInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetAuthDataInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                     *pstPsMsg;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU   *pstAuthdata;
#if ( FEATURE_ON == FEATURE_LTE )
    VOS_UINT32                          ulPara;
#endif

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstAuthdata     = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstAuthdata->stCtrl)))
    {
        (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&(pstAuthdata->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
#endif

#if ( FEATURE_ON == FEATURE_LTE )
    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        /* ������Ϣ��L4A */
        TAF_APS_SndL4aSetAuthdataReq(pstAuthdata);

        ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstAuthdata),
                                               TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstAuthdata));

        /* ����L4A��Ϣ�ظ�������ʱ�� */
        TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                           TI_TAF_APS_WAIT_L4A_CNF_LEN,
                           ulPara);

        /* �����Ϣ���ȴ����� */
        TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                         (VOS_UINT32*)pstAuthdata,
                                         sizeof(TAF_PS_SET_AUTHDATA_INFO_REQ_STRU),
                                         ulPara);

        return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetAuthDataInfoReq(pstAuthdata);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtSetUmtsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                     *pstPsMsg;
    TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU   *pstSetQosReq;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetQosReq    = (TAF_PS_SET_UMTS_QOS_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetQosReq->stCtrl)))
    {
        TAF_APS_SndSetUmtsQosInfoCnf(&(pstSetQosReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetUmtsQosInfoReq(pstSetQosReq);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetUmtsQosMinInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                         *pstPsMsg;
    TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU   *pstSetQosMinReq;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetQosMinReq = (TAF_PS_SET_UMTS_QOS_MIN_INFO_REQ_STRU *)pstPsMsg->aucContent;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetQosMinReq->stCtrl)))
    {
        TAF_APS_SndSetUmtsQosMinInfoCnf(&(pstSetQosMinReq->stCtrl), TAF_PARA_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }
#endif

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvSetUmtsQosMinInfoReq(pstSetQosMinReq);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtSetPdpAuthInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvSetPdpAuthInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtSetPdpDnsInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvSetPdpDnsInfoReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtTrigGprsDataReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    (VOS_VOID)MN_APS_RcvTrigGprsDataReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvAtConfigNbnsFunctionReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                 *pstPsMsg;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    /* ȥ��Ϣͷ, ����ԭ�����������ظ�AT */
    MN_APS_RcvConfigNbnsFunctionReq(pstPsMsg->aucContent);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtFindCidForDialReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU  *pCnf;
    VOS_UINT8                                 ucCid;

    pCnf = (TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                                   sizeof(TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    /* ���ҿ����ڲ��ŵ�CID */
    ucCid = TAF_APS_FindCidForDial(WUEPS_PID_AT);
    if ( TAF_INVALID_CID == ucCid )
    {
        pCnf->ulRet       = VOS_ERR;
    }

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_FIND_CID_FOR_DIAL_CNF;
    pCnf->ulRet                         = VOS_OK;
    pCnf->ucCid                         = ucCid;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtGetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_GET_CID_PARA_CNF_STRU         *pCnf;
    TAFAGENT_APS_GET_CID_PARA_REQ_STRU         *pMsgReq;
    VOS_UINT32                                  ulResult;

    pCnf = (TAFAGENT_APS_GET_CID_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGENT_APS_GET_CID_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                             = (TAFAGENT_APS_GET_CID_PARA_REQ_STRU*)pstMsg;

    ulResult                            = MN_APS_GetPdpCidPara(&(pCnf->stCidInfo),pMsgReq->ucCid);

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_GET_CID_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_APS_RcvAtSetCidParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_SET_CID_PARA_REQ_STRU                         *pMsgReq;
    TAFAGENT_APS_SET_CID_PARA_CNF_STRU                         *pCnf;
    VOS_UINT32                                                  ulResult;

    pCnf = (TAFAGENT_APS_SET_CID_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                sizeof(TAFAGENT_APS_SET_CID_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                  = (TAFAGENT_APS_SET_CID_PARA_REQ_STRU*)(pstMsg);
    ulResult                 = MN_APS_SetPdpCidPara((VOS_UINT16)pMsgReq->ulClientID,&(pMsgReq->stPdpPrimContextExt));

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_SET_CID_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvFindCidForDialReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtGetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU         *pCnf;
    TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU         *pMsgReq;
    VOS_UINT32                                      ulResult;

    pCnf = (TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                              sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_GetCidQosParaReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    PS_MEM_SET((VOS_CHAR*)pCnf + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(TAFAGENT_APS_GET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsgReq                             = (TAFAGENT_APS_GET_CID_QOS_PARA_REQ_STRU*)pstMsg;

    ulResult                            = TAF_APS_GetPdpCidQosPara(&(pCnf->stQosPara), pMsgReq->ucCid);

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_GET_CID_QOS_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvAtGetCidQosParaReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;

}


VOS_UINT32 TAF_APS_RcvAtSetCidQosParaReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU                         *pMsgReq;
    TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU                         *pCnf;
    VOS_UINT32                                                      ulResult;

    pCnf = (TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU *)PS_ALLOC_MSG(WUEPS_PID_TAF,
                                                sizeof(TAFAGENT_APS_SET_CID_QOS_PARA_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pCnf)
    {
        APS_ERR_LOG("TAF_APS_RcvAtSetCidQosParaReq_PreProc:alloc msg failed.");
        return VOS_TRUE;
    }

    pMsgReq                  = (TAFAGENT_APS_SET_CID_QOS_PARA_REQ_STRU*)(pstMsg);

    ulResult                 = TAF_APS_SetPdpCidQosPara(&(pMsgReq->stQosPara));

    pCnf->ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pCnf->ulSenderPid                   = WUEPS_PID_TAF;
    pCnf->ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pCnf->ulReceiverPid                 = ACPU_PID_TAFAGENT;
    pCnf->enMsgId                       = ID_TAFAGENT_APS_SET_CID_QOS_PARA_CNF;
    pCnf->ulRet                         = (VOS_UINT8)ulResult;

    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_TAF, pCnf))
    {
        APS_ERR_LOG("TAF_APS_RcvAtSetCidQosParaReq_PreProc:send msg failed.");

        return VOS_TRUE;
    }

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;
    VOS_UINT32                          ulRslt;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpStateReq                   = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstSetPdpStateReq->stCtrl)))
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl), TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
#endif

    /* ���ü����� */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /*
       ��ǰ�Ȳ�֧��һ���Լ�����PDP�ĳ�����һ�μ���һ��������ҵ�һ��Ҫ�����
       CID
    */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpStateReq->stCidListStateInfo.aucCid);

    /* ������ص�CIDΪ0����������ЧCID��ֱ�ӷ���ERROR */
    if (0 == ucCidValue)
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    if (ulBearerActivateFlg == VOS_TRUE)
    {
        ulRslt = TAF_APS_ProcActivatePdpContext_PreProc(ucCidValue, pstSetPdpStateReq);
    }
    else
    {
        ulRslt = TAF_APS_ProcDeactivatePdpContext_PreProc(ucCidValue, pstSetPdpStateReq);
    }

    return ulRslt;
}


VOS_UINT32 TAF_APS_ProcActivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    TAF_APS_MATCH_PARAM_STRU            stMatchParam;
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;

    PS_MEM_SET(&stMatchParam, 0x00, sizeof(TAF_APS_MATCH_PARAM_STRU));

    ucPhMode = MMA_GetCurrPhMode();

    /* ���ϵͳΪ����,��ֱ�ӷ���VOS_TRUE */
    if ( TAF_PH_MODE_FULL != ucPhMode )
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    /* CID��Ӧ��������û�ж��壬��ֱ�ӷ���ERROR */
    if (VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(ucCidValue))
    {
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    /* ����ƥ�������Ϣ */
    TAF_APS_GenMatchParamByCidInfo(TAF_APS_GetTafCidInfoAddr(ucCidValue),
                                   &stMatchParam);

#if (FEATURE_ON == FEATURE_LTE)
    /* �ҵ�Ĭ�ϳ��ص�����£�ֱ��ˢ��CID  */
    if (VOS_TRUE == TAF_APS_MatchCallWithAttachBearer(
                                &pstSetPdpStateReq->stCtrl,
                                &stMatchParam))
    {
        /* ����ˢ��CID����ͬʱˢ����ClientId��OP ID */
        ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

        /* ���cid 0 ����Ϣ,��¼PDP ��Ϣ */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    ucCidValue,
                                    pstSetPdpStateReq->stCtrl.ulModuleId,
                                    pstSetPdpStateReq->stCtrl.usClientId,
                                    pstSetPdpStateReq->stCtrl.ucOpId);

        TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCidValue, TAF_APS_GetTafCidInfoPdpType(ucCidValue));

        /* ֪ͨESM��ǰ��Cidˢ�� */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);

        return VOS_FALSE;
    }
#endif

    /* ��ȡPdpId�������ȡ������˵����ǰ�Ǽ���һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��ͬAPN
           ����Ѽ�����ͬAPN��PDP�������ݣ�����PDPʵ��
           ����Ѽ�����ͬAPN��PDP���Ͳ�ͬ�����·���PDPʵ��
           δ����: ACTIVATING,MODIFING,DEACTIVATING
           ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING

           ����ͬAPN��ִ��ԭ������
        */

        /* ���������һ���µ�PDP ID */
        if (VOS_TRUE == TAF_APS_MatchCallWithAllBearer(
                                    &pstSetPdpStateReq->stCtrl,
                                    &stMatchParam,
                                    &ucPdpId))
        {
            /* δ����: ACTIVATING,MODIFING,DEACTIVATING
               ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING */
            if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
            {
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                             TAF_PS_CAUSE_OPERATION_CONFLICT);
                return VOS_TRUE;
            }
            else
            {
                /* ��¼PDP��Ϣ */
                TAF_APS_AddPdpEntClientInfo(ucPdpId,
                                            ucCidValue,
                                            &(pstSetPdpStateReq->stCtrl));

                TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                             ucCidValue,
                                             TAF_APS_GetTafCidInfoPdpType(ucCidValue));
            }
        }
        else
        {
            /* ����TI(PdP Id) */
            if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstSetPdpStateReq->stCtrl,
                                                               ucCidValue,
                                                               &ucPdpId))
            {
                /* ���䲻��ʵ�壬��ֱ�ӷ���ERROR */
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                            TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue) != pstSetPdpStateReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                        TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    ulRslt = TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc(pstSetPdpStateReq);

    return ulRslt;
}


VOS_UINT32 TAF_APS_ProcDeactivatePdpContext_PreProc(
    VOS_UINT8                           ucCidValue,
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_BITCID_INFO_STRU            stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));

    /* ��ȡPdpId�������ȡ������˵����ǰ��ȥ����һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /*
           ȥ��������������ȥ����һ���µ�CID,˵����ǰ��Ӧ��CID��û�м���
           ���߳��Լ��ֱ�ӷ���OK
        */
        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_SUCCESS);

        /* û���ҵ�ƥ���PDP, ���PDPû�м���, �ϱ�ȥ����ɹ��¼� */
        TAF_APS_SndCidInactiveEvt(&(pstSetPdpStateReq->stCtrl),
                                  ucCidValue);

        return VOS_TRUE;
    }
    else
    {
        if (TAF_APS_INVALID_CLIENTID == TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue))
        {
            TAF_APS_SetPdpEntClientId(ucPdpId, ucCidValue, pstSetPdpStateReq->stCtrl.usClientId);
        }
        else if (TAF_APS_GetPdpEntClientId(ucPdpId, ucCidValue) != pstSetPdpStateReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                         TAF_PS_CAUSE_UNKNOWN);

            return VOS_TRUE;
        }
        else
        {
            /* ���PDPʵ�����Ƿ���ڶ��cid */
            TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

            if (stCid.ulNum > 1)
            {
                /* ���ظ�cidȥ����ɹ� */
                TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                             TAF_PS_CAUSE_SUCCESS);

                TAF_APS_SndPdpDeActivateCnf(ucPdpId, ucCidValue);

                /* ���PDPʵ���и�CID��Ϣ */
                TAF_APS_RmvPdpEntClientInfo(ucPdpId, ucCidValue, &stCid);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_MODIFY_REQ_STRU        *pstCallModifyReq;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCidValue;
    VOS_UINT32                          ulBearerActivateFlg;
    TAF_APS_BITCID_INFO_STRU                     stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));

    /* ��ǰ�Ȳ�֧��һ����Modify���PDP�ĳ�����һ��Modifyһ�� */
    ulBearerActivateFlg                 = VOS_FALSE;
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallModifyReq                    = (TAF_PS_CALL_MODIFY_REQ_STRU*)(pstAppMsg->aucContent);

    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstCallModifyReq->stCidListInfo.aucCid);

    /* ������ص�CIDΪ0����������ЧCID��ֱ�ӷ���ERROR */
    if ( 0 == ucCidValue )
    {
        /* �ϱ�ERROR */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;

    }

    /* ��ȡPdpId�������ȡ������˵����ǰû�п����޸ĵ�PDP ID */
    ucPdpId = TAF_APS_GetPdpIdByCid(ucCidValue);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ֱ�ӷ���ERROR */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;
    }

    /* ���PDPʵ�����Ƿ���ڶ��cid */
    TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);
    if (stCid.ulNum > 1)
    {
        /* ����APN����ʱ���������û�����MODIFY */
        TAF_APS_SndCallModifyCnf(&(pstCallModifyReq->stCtrl),
                                 TAF_PS_CAUSE_OPERATION_CONFLICT);
        return VOS_TRUE;
    }

    TAF_APS_SetPdpEntModDialInfo(ucPdpId, &(pstCallModifyReq->stCtrl));

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_MATCH_PARAM_STRU            stMatchParam;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;

    PS_MEM_SET(&stMatchParam, 0x00, sizeof(TAF_APS_MATCH_PARAM_STRU));

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPhMode                            = MMA_GetCurrPhMode();
    ucPdpId                             = TAF_APS_INVALID_PDPID;

#if (FEATURE_ON == FEATURE_CL_INTERWORK)
    /* L-C������ģʽ����������Ϣ��Ч�����ж� */
    if (VOS_FALSE == TAF_APS_LCCheckReqValid(&(pstCallOrigReq->stCtrl)))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                      pstCallOrigReq->stDialParaInfo.ucCid,
                      TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
#endif

    /* ���ϵͳΪ��������ֱ�ӷ���VOS_TRUE */
    if (TAF_PH_MODE_FULL != ucPhMode)
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    /* ����ƥ�������Ϣ */
    TAF_APS_GenMatchParamByDailInfo(&pstCallOrigReq->stDialParaInfo,
                                    &stMatchParam);

    /* Modified by y00314741 for CDMA Iteration 15, 2015-5-26, begin */
    /* �ҵ�Ĭ�ϳ��ص�����£�ֱ��ˢ��CID  */
    if (VOS_TRUE == TAF_APS_MatchCallWithAttachBearer(
                                &pstCallOrigReq->stCtrl,
                                &stMatchParam))
    {
        /* ����ˢ��CID����ͬʱˢ����ClientId��OP ID */
        ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

        /* ���CID 0 ����Ϣ,��¼PDP ��Ϣ */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    pstCallOrigReq->stDialParaInfo.ucCid,
                                    pstCallOrigReq->stCtrl.ulModuleId,
                                    pstCallOrigReq->stCtrl.usClientId,
                                    pstCallOrigReq->stCtrl.ucOpId);

        TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                     pstCallOrigReq->stDialParaInfo.ucCid,
                                     pstCallOrigReq->stDialParaInfo.enPdpType);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

        /* ֪ͨEHSM��ǰ��Cidˢ�� */
        TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);

#endif

#if (FEATURE_ON == FEATURE_LTE)
        /* ֪ͨESM��ǰ��Cidˢ�� */
        MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                SM_ESM_PDP_OPT_MODIFY);
#endif

        return VOS_FALSE;
    }
    /* Modified by y00314741 for CDMA Iteration 15, 2015-5-26, end */

    /* ��ȡPdpId�������ȡ������˵����ǰ�Ǽ������ȥ����һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstCallOrigReq->stDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��ͬAPN
             ����Ѽ�����ͬAPN��PDP�������ݣ�����PDPʵ��
             ����Ѽ�����ͬAPN��PDP���Ͳ�ͬ�����·���PDPʵ��
             δ����: ACTIVATING,MODIFING,DEACTIVATING
             ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING

           ����ͬAPN��ִ��ԭ������  */
        if (VOS_TRUE == TAF_APS_MatchCallWithAllBearer(
                                    &pstCallOrigReq->stCtrl,
                                    &stMatchParam,
                                    &ucPdpId))
        {
            /* δ����: ACTIVATING,MODIFING,DEACTIVATING
               ��������ԭ��ֵTAF_PS_CAUSE_SAME_APN_OPERATING */
            if (TAF_APS_STA_ACTIVE != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
            {
                TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                       pstCallOrigReq->stDialParaInfo.ucCid,
                                       TAF_PS_CAUSE_OPERATION_CONFLICT);
                return VOS_TRUE;
            }
            else
            {
                /* ��¼PDP��Ϣ */
                TAF_APS_AddPdpEntClientInfo(ucPdpId,
                                            pstCallOrigReq->stDialParaInfo.ucCid,
                                            &(pstCallOrigReq->stCtrl));

                TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                             pstCallOrigReq->stDialParaInfo.ucCid,
                                             pstCallOrigReq->stDialParaInfo.enPdpType);
            }
        }
        else
        {
            /* ����ʵ�� */
            if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstCallOrigReq->stCtrl,
                                                               pstCallOrigReq->stDialParaInfo.ucCid,
                                                               &ucPdpId))
            {
                /* ���䲻��ʵ�壬��ֱ�ӷ���ERROR */
                TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                      pstCallOrigReq->stDialParaInfo.ucCid,
                                      TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstCallOrigReq->stDialParaInfo.ucCid) != pstCallOrigReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                  pstCallOrigReq->stDialParaInfo.ucCid,
                                  TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer(
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq
)
{
    VOS_UINT8                           ucPdpId;

    /* ����CID��ȡPDP ID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* �����ȡ������˵������Ӧ�����缤�� */
        return VOS_FALSE;
    }

    /* �ҵ�PDP ID���ȡ��Ӧ��״̬��������������缤��ȴ��û�Ӧ��״̬��˵������Ӧ�����缤�� */
    if (TAF_APS_STA_NW_ACTIVATING != TAF_APS_GetPdpIdMainFsmState(ucPdpId))
    {
        return VOS_FALSE;
    }

    if (TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER != TAF_APS_GetPdpIdSubFsmState(ucPdpId))
    {
        return VOS_FALSE;
    }

    /* �ж϶˿��Ƿ�һ�� */
    if (pstPppDialOrigReq->stCtrl.usClientId != TAF_APS_GetPdpEntClientId(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPppDialOrigReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg = VOS_NULL_PTR;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;
    TAF_PH_MODE                         ucPhMode;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32                          ulResult;
    VOS_UINT32                          ulErrCode;
#endif

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPhMode                            = MMA_GetCurrPhMode();

    /* �жϵ�ǰ�������缤��ȴ��û�Ӧ��״̬��ֱ�ӽ���״̬�� */
    if (VOS_TRUE == TAF_APS_IsStaNwActivatingSubStaWaitAppAnswer(pstPppDialOrigReq))
    {
        return VOS_FALSE;
    }

    /* ���ϵͳδ���������CID��Ӧ��������û�ж��壬��ֱ�ӷ���ERROR */
    if ( (TAF_PH_MODE_FULL != ucPhMode)
      || (VOS_FALSE == TAF_APS_GetTafCidInfoUsedFlg(pstPppDialOrigReq->stPppDialParaInfo.ucCid)) )
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

#if (FEATURE_ON == FEATURE_LTE)

    if (VOS_TRUE == TAF_SDC_IsPlatformSupportLte())
    {
        ulErrCode = TAF_ERR_NO_ERROR;

        ulResult = TAF_APS_FindSutiablePdpForPppDial_LteMode(&pstPppDialOrigReq->stPppDialParaInfo,
                                                             &ulErrCode);
        if (TAF_ERR_ERROR == ulErrCode)
        {
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }

        /* �ҵ�Ĭ�ϳ��ص�����£�ֱ��ˢ��CID */
        if (VOS_TRUE == ulResult)
        {
            /* ����ˢ��CID����ͬʱˢ����ClientId��OP ID */
            ucPdpId = TAF_APS_GetPdpIdByDefaultCid();

            /* ���cid 0 ����Ϣ,��¼PDP ��Ϣ */
            TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                        pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                        pstPppDialOrigReq->stCtrl.ulModuleId,
                                        pstPppDialOrigReq->stCtrl.usClientId,
                                        pstPppDialOrigReq->stCtrl.ucOpId);

            TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                         pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                         TAF_APS_GetTafCidInfoPdpType(pstPppDialOrigReq->stPppDialParaInfo.ucCid));

            /* ֪ͨESM��ǰ��Cidˢ�� */
            MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId),
                                    SM_ESM_PDP_OPT_MODIFY);

            return VOS_FALSE;
        }
    }

#endif

    /* ��ȡPdpId�������ȡ������˵����ǰ�Ǽ������ȥ����һ���µ�CID */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ����ʵ�� */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&pstPppDialOrigReq->stCtrl,
                                                           pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                                           &ucPdpId))
        {
            /* ���䲻��ʵ�壬��ֱ�ӷ���ERROR */
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid) != pstPppDialOrigReq->stCtrl.usClientId)
        {
            /* ClientId��ƥ��, ��ֱ�ӷ���ERROR */
            TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
    }

    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                 TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;
    TAF_APS_BITCID_INFO_STRU            stCid;

    PS_MEM_SET(&stCid, 0, sizeof(TAF_APS_BITCID_INFO_STRU));
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq                       = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡPdpId�������ȡ������ֱ�ӷ��أ�����״̬�� */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstCallEndReq->ucCid);

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* �ó����·���ERROR, ��ֹʹ���߹��� */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                              pstCallEndReq->ucCid,
                              TAF_PS_CAUSE_CID_INVALID);
        return VOS_TRUE;

    }
    else
    {
        if (TAF_APS_GetPdpEntClientId(ucPdpId, pstCallEndReq->ucCid) != pstCallEndReq->stCtrl.usClientId)
        {
            TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                                  pstCallEndReq->ucCid,
                                  TAF_PS_CAUSE_CID_INVALID);

            return VOS_TRUE;
        }
        else
        {
            /* �����û���Ϣ--IMSA��ʹ�ò�ͬ��opid */
            TAF_APS_SetPdpEntOpId(ucPdpId,
                                  pstCallEndReq->ucCid,
                                  pstCallEndReq->stCtrl.ucOpId);

            /* ���PDPʵ�����Ƿ���ڶ��cid */
            TAF_APS_GetPdpEntBitCidInfo(ucPdpId, &stCid);

            if (stCid.ulNum > 1)
            {
                /* ���ظ�cidȥ����ɹ� */
                TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl),
                                      pstCallEndReq->ucCid,
                                      TAF_PS_CAUSE_SUCCESS);

                TAF_APS_SndPdpDeActivateCnf(ucPdpId, pstCallEndReq->ucCid);

                /* ���PDPʵ���и�CID��Ϣ */
                TAF_APS_RmvPdpEntClientInfo(ucPdpId, pstCallEndReq->ucCid, &stCid);

                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;

}


VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;
    TAF_PRI_PDP_QUERY_INFO_STRU         stPdpPriPara;
    VOS_UINT32                          ulErrCode;
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;
    VOS_UINT8                           ucPdpId;

    VOS_UINT8                           ucCid;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);
    ucCid                               = pstCallAnswerReq->stAnsInfo.ucCid;

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    /* �жϵ�ǰ�Ƿ������缤��ȴ��û�Ӧ��״̬ */
    if (VOS_NULL_PTR == pstNwActFsm)
    {
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    ucPdpId = pstNwActFsm->ucPdpId;

    /* ��֧��IPV4/IPV4V6���ͣ�ֱ�ӻ�ERROR */
#if (FEATURE_ON == FEATURE_IPV6)
    if ((MN_APS_ADDR_IPV6 == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
     || (MN_APS_ADDR_IPV4V6 == g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
    {
        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                 TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }
#endif

    /* �û�ָ����CID����Ҫƥ��PDP TYPE��ADDR������ʹ������ָ����PDP TYPE��ADDR */
    if (0 != ucCid)
    {
        /* ��ȡPrimary PDP��������Ϣ */
        PS_MEM_SET(&stPdpPriPara, 0x00, sizeof(TAF_PRI_PDP_QUERY_INFO_STRU));
        Aps_QuePri(pstCallAnswerReq->stAnsInfo.ucCid, &stPdpPriPara, &ulErrCode);
        if (TAF_PARA_OK != ulErrCode)
        {
            TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                     pstCallAnswerReq->stAnsInfo.ucCid,
                                     TAF_PS_CAUSE_UNKNOWN);
            return VOS_TRUE;
        }
        else
        {
            /* �û����õ����ͺ������·������Ͳ�һ�� */
            if (TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum) != stPdpPriPara.stPriPdpInfo.stPdpAddr.enPdpType)
            {
                TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                         pstCallAnswerReq->stAnsInfo.ucCid,
                                         TAF_PS_CAUSE_UNKNOWN);
                return VOS_TRUE;
            }

            /* ���緢���PPP���͵Ĳ��ţ���Ҫ����ƥ�䲦������ */
            /* ���緢���IPV4���͵Ĳ��ţ���Ҫ����ƥ�䲦�����ͺ�IP��ַ */
            if (APS_ADDR_PPP != g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum)
            {
                /* �û�������PDP ADDR */
                if ('\0' != stPdpPriPara.stPriPdpInfo.stPdpAddr.aucIpv4Addr[0])
                {
                    if (0 != PS_MEM_CMP(stPdpPriPara.stPriPdpInfo.stPdpAddr.aucIpv4Addr,
                                        g_PdpEntity[ucPdpId].PdpAddr.aucIpAddr,
                                        TAF_IPV4_ADDR_LEN))
                    {
                        TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                                 pstCallAnswerReq->stAnsInfo.ucCid,
                                                 TAF_PS_CAUSE_UNKNOWN);
                        return VOS_TRUE;
                    }
                }
            }
        }
    }

    ucCid = ((0 != ucCid) ? ucCid : TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��¼PDP ��Ϣ */
    TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                ucCid,
                                pstCallAnswerReq->stCtrl.ulModuleId,
                                pstCallAnswerReq->stCtrl.usClientId,
                                pstCallAnswerReq->stCtrl.ucOpId);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId, ucCid, TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum));

    /* ���AT^ANSWER�����IP���͵����缤����Ӧ��ֱ���ϱ�CONNECT��AT���ȴ�PPP���𲦺����� */
    if (VOS_TRUE == pstCallAnswerReq->stAnsInfo.ucAnsExtFlg)
    {
        if (TAF_PDP_IPV4 == TAF_APS_ConvertPdpType(g_PdpEntity[ucPdpId].PdpAddr.ucPdpTypeNum))
        {
            /* ǰ������ɹ�����¼��Ӧ��Ŀͻ��˺ͺ��б�ʶ��Cid */
            g_PdpEntity[ucPdpId].PdpProcTrack.ucHowToInitAct
                                                = APS_APP_MANUL_ACT;

            TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                                     TAF_APS_GetPdpEntCurrCid(ucPdpId),
                                     TAF_ERR_AT_CONNECT);

            return VOS_TRUE;
        }
    }


    /* Ԥ�����������Ҫ����״̬�� */
    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_PDP_ENTITY_FSM_CTX_STRU    *pstNwActFsm;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    pstNwActFsm = TAF_APS_GetPdpEntityFsm(TAF_APS_STA_NW_ACTIVATING,
                                          TAF_APS_FSM_NW_ACTIVATING,
                                          TAF_APS_NW_ACTIVATING_SUBSTA_WAIT_APP_ANSWER);

    /* �жϵ�ǰ�Ƿ������缤��ȴ��û�Ӧ��״̬ */
    if (VOS_NULL_PTR == pstNwActFsm)
    {
        TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl), TAF_PS_CAUSE_UNKNOWN);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvSmRegPdpActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_CNF_STRU        *pstSmMsg;
    SM_TAF_TRANS_ID_STRU                stTi;
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    if (VOS_TRUE == pstPdpActLimitInfo->ucPdpActLimitFlg)
    {
        pstPdpActLimitInfo->ucPdpActFailCount = 0;

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            TAF_APS_StopTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID);
        }
    }


    /* mo������ֱ���ڴ˴�ˢ��ʵ����Ti��ֵ */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;

}
VOS_UINT32 TAF_APS_RcvSmRegPdpActRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_REJ_STRU        *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_REJ_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* PDP�������޴���:PDP����Ĵ���ΪSMʵ�ʳ��Ե�PDP������� */
    if (SM_TAF_CAUSE_SM_MAX_TIME_OUT == pstSmMsg->enCause)
    {
        TAF_APS_ProcPdpActLimit_PreProc(pstSmMsg->ucExpiredCount);
    }
    else
    {
        TAF_APS_ProcPdpActLimit_PreProc(pstSmMsg->ucExpiredCount + 1);
    }

    return VOS_FALSE;
}



VOS_UINT32 TAF_APS_RcvSmRegPdpActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_IND_STRU        *pstSmMsg;
    APS_PDP_CONTEXT_ENTITY_ST          *pstCurrEntity;
    SM_TAF_TRANS_ID_STRU                stTi;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_IND_STRU *)pstMsg;


    /* ���緢���PDP�����Ԥ��������PDP ID,�����CR ��ͬ��PDP ID */
    pstCurrEntity = TAF_APS_GetPdpEntInfoAddr(pstSmMsg->ucConnectId);
    pstCurrEntity->stClientInfo.ucCid   = TAF_APS_FindCidForAns();
    pstCurrEntity->ulUsedFlg            = VOS_TRUE;
    pstCurrEntity->ucPdpId              = pstSmMsg->ucConnectId;

    /* ˢ��PDP��Ϣ */
    TAF_APS_SetPdpEntClientInfo(pstCurrEntity->ucPdpId,
                                pstCurrEntity->stClientInfo.ucCid,
                                TAF_APS_INVALID_MODULEID,
                                TAF_APS_INVALID_CLIENTID,
                                TAF_APS_INVALID_OPID);

    /* mt������ֱ���ڴ˴�ˢ��ʵ����Ti��ֵ */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_IND_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_CNF_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;

}
VOS_UINT32 TAF_APS_RcvSmRegPdpModifyRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_MODIFY_REJ_STRU          *pstSmMsg;

    pstSmMsg = (SMREG_PDP_MODIFY_REJ_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}
VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_IND_STRU *)pstMsg;

    /* ����TI��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* PDP�������޴���: �������������PDPȥ�����Ϊ����PDP����Ĵ���Ϊ1 */
    TAF_APS_ProcPdpActLimit_PreProc(1);

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvSmRegPdpDeactivCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_DEACTIVATE_CNF_STRU      *pstSmMsg;

    pstSmMsg = (SMREG_PDP_DEACTIVATE_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_SEC_CNF_STRU    *pstSmMsg;
    SM_TAF_TRANS_ID_STRU                stTi;


    PS_MEM_SET(&stTi, 0x00, sizeof(stTi));


    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_CNF_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    /* mo������ֱ���ڴ˴�ˢ��ʵ����Ti��ֵ */
    stTi.ucTiValue = pstSmMsg->stTransId.ucTiValue;
    stTi.ucTiFlag  = pstSmMsg->stTransId.ucTiFlag;

    TAF_APS_SetPdpEntityTi(pstSmMsg->ucConnectId, &stTi);

    return VOS_FALSE;


}
VOS_UINT32 TAF_APS_RcvSmRegPdpActSecRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    SMREG_PDP_ACTIVATE_SEC_REJ_STRU    *pstSmMsg;

    pstSmMsg = (SMREG_PDP_ACTIVATE_SEC_REJ_STRU *)pstMsg;

    /* ����CR��ȡ������Ӧ��PDP ID�����ӡ�쳣��ֱ�ӷ��أ�����״̬�� */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstSmMsg->ucConnectId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvSmRegPdpActCnf_PreProc:Wrong ConnectId", pstSmMsg->ucConnectId);
        return VOS_TRUE;
    }

    return VOS_FALSE;


}

#if ( FEATURE_ON == FEATURE_LTE )
VOS_UINT32 TAF_APS_RcvAtSetEpsQosInfoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(TAF_APS_GET_MODULEID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent),
                                           TAF_APS_GET_CLIENTID_FORM_CTRL_HDR((TAF_CTRL_STRU *)pstPsMsg->aucContent));

    /* ������Ϣ��L4A */
    TAF_APS_SndL4aSetCgeqosReq(pstPsMsg->aucContent);

    /* ����L4A��Ϣ�ظ�������ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                       TI_TAF_APS_WAIT_L4A_CNF_LEN,
                       ulPara);

    /* �����Ϣ���ȴ����� */
    TAF_APS_SaveItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                     (VOS_UINT32 *)pstPsMsg->aucContent,
                                     sizeof(TAF_PS_SET_EPS_QOS_INFO_REQ_STRU),
                                     ulPara);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvL4aSetCgdcontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGDCONT_CNF_STRU               *pstPsMsg;
    TAF_CTRL_STRU                               stCtrl = {0};
    VOS_UINT32                                  ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                    *pstMsgInfo;
    TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU  *pstSetPdpCtxInfoReq;
    VOS_UINT32                                  ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGDCONT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdpCtxInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgdcontCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }
        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetPdpCtxInfoReq = (TAF_PS_SET_PRIM_PDP_CONTEXT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetPdpCtxInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {

            /* PDP�����������Դ򿪣���ͣ���ʱ���������� */
            if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
            {
                TAF_APS_RcvSetPrimPdpCtxInfoReq_PdpActLimit(pstSetPdpCtxInfoReq);
            }


            /* ����Primary PDP������ */
            Aps_DefPsPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                                pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                                &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                                &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetPrimPdpCtxInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvL4aSetCgdscontCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGDSCONT_CNF_STRU              *pstPsMsg;
    TAF_CTRL_STRU                               stCtrl = {0};
    VOS_UINT32                                  ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                    *pstMsgInfo;
    TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU   *pstSetPdpCtxInfoReq;
    VOS_UINT32                                  ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGDSCONT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetPdpCtxInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgdscontCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetPdpCtxInfoReq = (TAF_PS_SET_SEC_PDP_CONTEXT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetPdpCtxInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����Primary PDP������ */
            Aps_DefPsSecPdpContext(pstSetPdpCtxInfoReq->stCtrl.usClientId,
                                   pstSetPdpCtxInfoReq->stCtrl.ucOpId,
                                   &(pstSetPdpCtxInfoReq->stPdpContextInfo),
                                   &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetSecPdpCtxInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aSetCgtftCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGTFT_CNF_STRU         *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_TFT_INFO_REQ_STRU       *pstSetTftInfoReq;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGTFT_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetTftInfoReq        = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetTftInfoReq = (TAF_PS_SET_TFT_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetTftInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����TFT���� */
            TAF_APS_SetTftInfo(&(pstSetTftInfoReq->stTftInfo), &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetTftInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aSetCgautoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGAUTO_CNF_STRU            *pstPsMsg;
    TAF_CTRL_STRU                           stCtrl = {0};
    VOS_UINT32                              ulErrCode;
    TAF_APS_CMD_BUFFER_STRU                *pstMsgInfo;
    TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU   *pstSetAnsModeInfoReq;
    VOS_UINT32                              ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGAUTO_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetAnsModeInfoReq    = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);


    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgautoCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetAnsModeInfoReq = (TAF_PS_SET_ANSWER_MODE_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetAnsModeInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ���Ӧ��ģʽ�Ƿ�Ϸ� */
            if ( (TAF_PDP_ANSWER_MODE_MANUAL == pstSetAnsModeInfoReq->ulAnsMode)
              || (TAF_PDP_ANSWER_MODE_AUTO   == pstSetAnsModeInfoReq->ulAnsMode) )
            {
                /* ����Ӧ��ģʽ */
                Aps_SetPsAnsMode(pstSetAnsModeInfoReq->stCtrl.usClientId,
                                 pstSetAnsModeInfoReq->stCtrl.ucOpId,
                                 (TAF_PDP_ANSWER_MODE_ENUM_UINT8)pstSetAnsModeInfoReq->ulAnsMode,
                                 &ulErrCode);
            }
            else
            {
                ulErrCode = TAF_PARA_SET_ERROR;
            }
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetAnsModeInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvL4aSetCgansCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����L4A��������Ϣ */

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvL4aSetCgeqosCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGEQOS_CNF_STRU        *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_EPS_QOS_INFO_REQ_STRU   *pstSetEpsQosInfoReq;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_CGEQOS_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstSetEpsQosInfoReq     = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgeqosCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstSetEpsQosInfoReq = (TAF_PS_SET_EPS_QOS_INFO_REQ_STRU*)pstMsgInfo->pulMsgInfo;
        stCtrl = pstSetEpsQosInfoReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����Ӧ��ģʽ */
            TAF_APS_SetEpsQosInfo(&pstSetEpsQosInfoReq->stEpsQosInfo,
                                  &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, ulPara);

        /* ����AT������ */
        TAF_APS_SndSetCgeqosCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aSetAuthdataCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_AUTHDATA_CNF_STRU      *pstPsMsg;
    TAF_CTRL_STRU                       stCtrl = {0};
    VOS_UINT32                          ulErrCode;
    TAF_APS_CMD_BUFFER_STRU            *pstMsgInfo;
    TAF_PS_SET_AUTHDATA_INFO_REQ_STRU  *pstAuthDataReq;
    VOS_UINT32                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                = (APS_L4A_SET_AUTHDATA_CNF_STRU*)pstMsg;
    ulErrCode               = pstPsMsg->ulErrorCode;
    pstMsgInfo              = VOS_NULL_PTR;
    pstAuthDataReq          = VOS_NULL_PTR;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);

        /* �ӻ�������л�ȡ��Ϣ */
        pstMsgInfo      = TAF_APS_GetItemFromCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);
        if (VOS_NULL_PTR == pstMsgInfo)
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetAuthdataCnf_PreProc: Get message info failed!");
            return VOS_TRUE;
        }

        /* ��Ϣ��ȡ�ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        pstAuthDataReq = (TAF_PS_SET_AUTHDATA_INFO_REQ_STRU *)pstMsgInfo->pulMsgInfo;
        stCtrl = pstAuthDataReq->stCtrl;

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4Aȫ�ֱ������³ɹ�, ����APS����ȫ�ֱ���, дNV���� */
        if (TAF_PS_CAUSE_SUCCESS == ulErrCode)
        {
            /* ����AUTHDATA����(NDIS) */
            Aps_DefNdisAuthdata(pstAuthDataReq->stCtrl.usClientId,
                                pstAuthDataReq->stCtrl.ucOpId,
                                &(pstAuthDataReq->stAuthDataInfo),
                                &ulErrCode);
        }

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, ulPara);

        /* ����AT������ */
        (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&stCtrl, ulErrCode);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGCONTRDP_CNF_STRU                     *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU  *pstGetDynamicPdpCtxInfoCnf;
    VOS_UINT32                                          ulGetDynamicPdpCtxInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGCONTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode   = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CID����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* ����ظ��¼���Ϣ���ݳ��� */
        ulGetDynamicPdpCtxInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU));

        /* �����ڴ� */
        pstGetDynamicPdpCtxInfoCnf      = (TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                           ulGetDynamicPdpCtxInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicPdpCtxInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf,
                   0x00,
                   ulGetDynamicPdpCtxInfoCnfLen);


        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicPdpCtxInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgcontrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

            return VOS_TRUE;
        }

        pstGetDynamicPdpCtxInfoCnf->enCause         = ulErrCode;
        pstGetDynamicPdpCtxInfoCnf->ulCidNum        = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo,
                       pstPsMsg->astPrimParaInfo,
                       (ulCidNum * sizeof(TAF_PDP_DYNAMIC_PRIM_EXT_STRU)));
        }

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_PRIM_PDP_CONTEXT_INFO_CNF,
                        pstGetDynamicPdpCtxInfoCnf,
                        ulGetDynamicPdpCtxInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, ulPara);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGSCONTRDP_CNF_STRU                    *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU   *pstGetDynamicPdpCtxInfoCnf;
    VOS_UINT32                                          ulGetDynamicPdpCtxInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGSCONTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CID����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* �����¼����ݳ��� */
        ulGetDynamicPdpCtxInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_PDP_DYNAMIC_SEC_EXT_STRU));

        /* �����ڴ� */
        pstGetDynamicPdpCtxInfoCnf      = (TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                          ulGetDynamicPdpCtxInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicPdpCtxInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicPdpCtxInfoCnf,
                   0x00,
                   ulGetDynamicPdpCtxInfoCnfLen);

        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicPdpCtxInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgscontrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

            return VOS_TRUE;
        }

        pstGetDynamicPdpCtxInfoCnf->enCause          = ulErrCode;
        pstGetDynamicPdpCtxInfoCnf->ulCidNum         = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicPdpCtxInfoCnf->astPdpContxtInfo,
                       pstPsMsg->astSecParaInfo,
                       (ulCidNum * sizeof(TAF_PDP_DYNAMIC_SEC_EXT_STRU)));
        }

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_SEC_PDP_CONTEXT_INFO_CNF,
                         pstGetDynamicPdpCtxInfoCnf,
                         ulGetDynamicPdpCtxInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicPdpCtxInfoCnf);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, ulPara);
    }

    return VOS_TRUE;
}
VOS_VOID TAF_APS_FillPfTftInfo(
    TAF_PF_TFT_STRU                    *pstPfTftInfo,
    APS_L4A_SDF_PF_TFT_STRU            *pstL4aPfTftInfo,
    VOS_UINT32                          ulCidNum
)
{
    VOS_UINT32                          ulIndex1;
    VOS_UINT32                          ulIndex2;

    /* ��ʼ������ */
    ulIndex1        = VOS_NULL;
    ulIndex2        = VOS_NULL;

    /* ѭ���������TFT���� */
    for (ulIndex1 = 0; ulIndex1 < ulCidNum; ulIndex1++)
    {
        pstPfTftInfo[ulIndex1].ulCid    = pstL4aPfTftInfo[ulIndex1].ulCid;
        pstPfTftInfo[ulIndex1].ulPFNum  = pstL4aPfTftInfo[ulIndex1].ulPfNum;

        for (ulIndex2 = 0; ulIndex2 < pstL4aPfTftInfo[ulIndex1].ulPfNum; ulIndex2++)
        {
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPktFilterId    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPktFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPrecedence     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpPrecedence;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcIp          = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcIp;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpProtocolId     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpProtocolId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDestPortRange  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDestPortRange;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcPortRange   = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSrcPortRange;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSpi            = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpSpi;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpTosMask        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpTosMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpFlowLable      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpFlowLable;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDirection      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpDirection;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpNwPktFilterId  = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].bitOpNwPktFilterId;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucCid               = (VOS_UINT8)pstL4aPfTftInfo[ulIndex1].ulCid;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucDefined           = VOS_TRUE;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPacketFilterId    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPacketFilterId;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPrecedence        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucPrecedence;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucProtocolId        = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucProtocolId;

            PS_MEM_CPY(&(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpaddr),
                       &(pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpaddr),
                       sizeof(TAF_PDP_ADDR_STRU));
            PS_MEM_CPY(&(pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpMask),
                       &(pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].stSourceIpMask),
                       sizeof(TAF_PDP_ADDR_STRU));

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowSourcePort     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowSourcePort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighSourcePort    = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighSourcePort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowDestPort       = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usLowDestPort;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighDestPort      = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].usHighDestPort;

            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulSecuParaIndex     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulSecuParaIndex;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulFlowLable         = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ulFlowLable;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfServiceMask = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfServiceMask;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfService     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucTypeOfService;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucDirection         = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].enTftFilterDirection;
            pstPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucNwPktFilterId     = pstL4aPfTftInfo[ulIndex1].astTftInfo[ulIndex2].ucNwPktFilterId;
        }

    }
    return;
}


VOS_UINT32 TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGTFTRDP_CNF_STRU          *pstPsMsg;
    VOS_UINT32                              ulErrCode;
    VOS_UINT32                              ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU   *pstGetDynamicTftInfoCnf;
    VOS_UINT32                              ulGetDynamicTftInfoCnfLen;
    VOS_UINT32                              ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGTFTRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CIDNum����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* �����¼����ݳ��� */
        ulGetDynamicTftInfoCnfLen   = sizeof(TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU)
                                        + (ulCidNum * sizeof(TAF_PF_TFT_STRU));

        /* �����ڴ� */
        pstGetDynamicTftInfoCnf = (TAF_PS_GET_DYNAMIC_TFT_INFO_CNF_STRU*)PS_MEM_ALLOC(
                                                WUEPS_PID_TAF,
                                                ulGetDynamicTftInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicTftInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicTftInfoCnf,
                   0x00,
                   ulGetDynamicTftInfoCnfLen);

        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicTftInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicTftInfoCnf);

            return VOS_TRUE;
        }

        pstGetDynamicTftInfoCnf->enCause          = ulErrCode;
        pstGetDynamicTftInfoCnf->ulCidNum         = ulCidNum;

        TAF_APS_FillPfTftInfo(pstGetDynamicTftInfoCnf->astPfTftInfo, pstPsMsg->astPfTftInfo, ulCidNum);

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_TFT_INFO_CNF,
                         pstGetDynamicTftInfoCnf,
                         ulGetDynamicTftInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicTftInfoCnf);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, ulPara);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_CGEQOSRDP_CNF_STRU                     *pstPsMsg;
    VOS_UINT32                                          ulErrCode;
    VOS_UINT32                                          ulCidNum;                   /* CID����  */
    TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU           *pstGetDynamicEpsQosInfoCnf;
    VOS_UINT32                                          ulGetDynamicEpsQosInfoCnfLen;
    VOS_UINT32                                          ulPara;

    /* ��ʼ����Ϣ */
    pstPsMsg                            = (APS_L4A_SET_CGEQOSRDP_CNF_STRU*)pstMsg;
    ulErrCode                           = pstPsMsg->ulErrorCode;
    ulCidNum                            = pstPsMsg->ulCidNum;

    ulPara = TAF_APS_BuildTmrParaByCtrlHdr(pstPsMsg->stCtrl.ulPid,
                                           pstPsMsg->stCtrl.ulClientId);

    /* �жϱ�����ʱ���Ƿ��ѳ�ʱ */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                              ulPara))
    {
        /* ������ʱ��û�г�ʱ, ֹͣ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, ulPara);

        /* L4A�������ת�� */
        ulErrCode           = TAF_APS_TransL4aErrorCode(ulErrCode);

        /* ���L4A��ѯ��̬����ʧ�ܣ�CIDNum����Ϊ0 */
        if ( TAF_PS_CAUSE_SUCCESS != ulErrCode )
        {
            ulCidNum = 0;
        }

        /* �����¼����ݳ��� */
        ulGetDynamicEpsQosInfoCnfLen    = sizeof(TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU)
                                            + (ulCidNum * sizeof(TAF_EPS_QOS_EXT_STRU));

        /* �����ڴ� */
        pstGetDynamicEpsQosInfoCnf      = (TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF_STRU*)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                                                                                  ulGetDynamicEpsQosInfoCnfLen);

        /* ������Ϣʧ�� */
        if ( VOS_NULL_PTR == pstGetDynamicEpsQosInfoCnf )
        {
            /* ϵͳ�쳣��ӡ, ֱ�ӷ��� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgtftrdpCnf_PreProc: PS_MEM_ALLOC Error!");
            return VOS_TRUE;
        }

        /* ��д�¼����� */
        PS_MEM_SET(pstGetDynamicEpsQosInfoCnf,
                   0x00,
                   ulGetDynamicEpsQosInfoCnfLen);

        /* �ӻ�������л�ȡ��Ϣ */
        if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&pstGetDynamicEpsQosInfoCnf->stCtrl,
                                                              TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                              ulPara))
        {
            /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aSetCgeqosrdpCnf_PreProc: Get message info failed!");

            /* �ͷ��ڴ� */
            PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicEpsQosInfoCnf);

            return VOS_TRUE;
        }

        pstGetDynamicEpsQosInfoCnf->enCause           = ulErrCode;
        pstGetDynamicEpsQosInfoCnf->ulCidNum          = ulCidNum;

        if (0 != ulCidNum)
        {
            PS_MEM_CPY(pstGetDynamicEpsQosInfoCnf->astEpsQosInfo,
                       pstPsMsg->astEpsQosInfo,
                       (ulCidNum * sizeof(TAF_EPS_QOS_EXT_STRU)));
        }

        /* ����Ϣ����AT */
        (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_DYNAMIC_EPS_QOS_INFO_CNF,
                         pstGetDynamicEpsQosInfoCnf,
                         ulGetDynamicEpsQosInfoCnfLen);

        /* �ͷ��ڴ� */
        PS_MEM_FREE(WUEPS_PID_TAF, pstGetDynamicEpsQosInfoCnf);

        /* ����Ϣ�ȴ�������ɾ������Ϣ */
        TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, ulPara);

    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGDCONT_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgdcontCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetPrimPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDCONT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                         TI_TAF_APS_WAIT_SET_CGDSCONT_CNF,
                                                         pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgdscontCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetSecPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGDSCONT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgtftCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGTFT_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgtftCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetTftInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFT_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgautoCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGAUTO_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgautoCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetAnsModeInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGAUTO_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGEQOS_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgeqosCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetCgeqosCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOS_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_AUTHDATA_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetAuthdataCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    (VOS_VOID)TAF_APS_SndSetAuthDataInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_AUTHDATA_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiGetLtecsCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_GET_LTE_CS_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiGetLtecsCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetLtecsInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_LTE_CS_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiGetCemodeCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_GET_CEMODE_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiGetCemodeCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetCemodeInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_GET_CEMODE_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetPdprofInfoExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_PDPROF_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetPdprofInfoExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndSetPdprofInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_PDPROF_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgcontrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    (VOS_VOID)TAF_APS_SndGetDynamicPrimPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGCONTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgscontrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetDynamicSecPdpCtxInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGSCONTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl = {0};
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgtftrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    (VOS_VOID)TAF_APS_SndGetDynamicTftInfoCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT, 0);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGTFTRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_CTRL_STRU                       stCtrl;
    REL_TIMER_MSG                      *pstRcvTimerMsg;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));

    pstRcvTimerMsg = (REL_TIMER_MSG *)pstMsg;

    if (VOS_TRUE != TAF_APS_GetCtrlHdrFromCmdBufferQueue(&stCtrl,
                                                          TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF,
                                                          pstRcvTimerMsg->ulPara))
    {
        /* ��Ϣ��ȡʧ��, ��ӡ������Ϣ */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvTiSetCgeqosrdpCnfExpired_PreProc: Get message info failed!");
        return VOS_TRUE;
    }

    /* ��ʧ����Ϣ���ظ�AT */
    TAF_APS_SndGetCgeqosrdpCnf(&stCtrl, TAF_PS_CAUSE_APS_TIME_OUT);

    /* ����Ϣ�ȴ�������ɾ������Ϣ */
    TAF_APS_DelItemInCmdBufferQueue(TI_TAF_APS_WAIT_SET_CGEQOSRDP_CNF, pstRcvTimerMsg->ulPara);

    return VOS_TRUE;
}
TAF_PS_CAUSE_ENUM_UINT32 TAF_APS_TransL4aErrorCode(
    VOS_UINT32                          ulL4aErrCode
)
{
    /* ���зǳɹ��Ĵ���������ز������ô��� */
    if (0 == ulL4aErrCode)
    {
        return TAF_PS_CAUSE_SUCCESS;
    }
    else
    {
        return TAF_PS_CAUSE_INVALID_PARAMETER;
    }
}
VOS_UINT32 TAF_APS_RcvL4aApsPdpActivateCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_ACTIVATE_CNF_STRU      *pstPdpActCnf;

    pstPdpActCnf = (APS_L4A_PDP_ACTIVATE_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdpActCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aApsPdpActivateRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_ACTIVATE_REJ_STRU      *pstPdpActRej;

    pstPdpActRej = (APS_L4A_PDP_ACTIVATE_REJ_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdpActRej->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aApsPdpActivateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_ACTIVATE_IND_STRU      *pstPdpActInd;
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));
    /* MODULE IDĬ������ΪAT, �����Ҫ�ϱ���IMSA�Ļ�����������ϱ�
       SM_ESM_EPS_BEARER_INFO_IND_STRU��Ϣ������ˢ�� */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;

    pstPdpActInd = (APS_L4A_PDP_ACTIVATE_IND_STRU*)pstMsg;

    /* ����(PdP Id) */
    if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                       pstPdpActInd->ucCid,
                                                       &ucPdpId))
    {
        /* ���䲻��ʵ�壬��ӡ�쳣����ʱ��Ӧ�÷��䲻��ʵ�� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvL4aApsPdpActivateInd_PreProc, alloc pdp id fail");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aApsPdpModifyCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_MODIFY_CNF_STRU      *pstPdpModifyCnf;

    pstPdpModifyCnf = (APS_L4A_PDP_MODIFY_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdpModifyCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aApsPdpModifyRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_MODIFY_REJ_STRU      *pstPdpModifyRej;

    pstPdpModifyRej = (APS_L4A_PDP_MODIFY_REJ_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdpModifyRej->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aApsPdpModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_MODIFY_IND_STRU      *pstPdpModifyInd;

    pstPdpModifyInd = (APS_L4A_PDP_MODIFY_IND_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdpModifyInd->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 TAF_APS_RcvL4aApsPdpDeactivateCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_DEACTIVATE_CNF_STRU    *pstPdpDeactCnf;

    pstPdpDeactCnf = (APS_L4A_PDP_DEACTIVATE_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdpDeactCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aApsPdpDeactivateRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_DEACTIVATE_REJ_STRU    *pstPdpDeactRej;

    pstPdpDeactRej = (APS_L4A_PDP_DEACTIVATE_REJ_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdpDeactRej->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}




VOS_UINT32 TAF_APS_RcvL4aApsPdpDeactivateInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_DEACTIVATE_IND_STRU    *pstPdpDeactInd;
    VOS_UINT8                           ucPdpId;

    pstPdpDeactInd = (APS_L4A_PDP_DEACTIVATE_IND_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (VOS_TRUE == pstPdpDeactInd->bitOpLinkCid)
    {
        ucPdpId = TAF_APS_GetPdpIdByCid_InL4aDeactivateInd(pstPdpDeactInd->ucCid);
    }
    else
    {
        ucPdpId = TAF_APS_GetPdpIdByEpsbId_InL4aDeactivateInd(pstPdpDeactInd->ulEpsbId);
    }

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aApsPdpSetupInd_PreProc
 ��������  : �յ�ID_L4A_APS_PDP_SETUP_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��19��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aApsPdpSetupInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PDP_SETUP_IND_STRU         *pstPdpSetupInd;
    VOS_UINT8                           ucPdpId;

    pstPdpSetupInd = (APS_L4A_PDP_SETUP_IND_STRU*)pstMsg;

    if (VOS_TRUE == pstPdpSetupInd->bitOpLinkCid)
    {
        /* ����Ϣ��������Cid�����Ҷ�Ӧ��PDP ID */
        ucPdpId = TAF_APS_GetPdpIdByCid((VOS_UINT8)(pstPdpSetupInd->ucCid));
    }
    else
    {
        /* ����Ϣ��������RabId�����Ҷ�Ӧ��PDP ID */
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstPdpSetupInd->ulRabId);
    }

    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvL4aSenNdisconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_SET_NDISCONN_CNF_STRU      *pstSetNdisConnCnf;

    pstSetNdisConnCnf = (APS_L4A_SET_NDISCONN_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstSetNdisConnCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_UINT32 TAF_APS_RcvEsmEpsBearInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    TAF_CTRL_STRU                       stCtrl;

    PS_MEM_SET(&stCtrl, 0, sizeof(TAF_CTRL_STRU));
    /* MODULE IDĬ������ΪAT, �����Ҫ�ϱ���IMSA�Ļ�����������ϱ�
       SM_ESM_EPS_BEARER_INFO_IND_STRU��Ϣ������ˢ�� */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;

    pstBearerInfo = (SM_ESM_EPS_BEARER_INFO_IND_STRU*)pstMsg;


    ucCid = TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid);

    /* Cid��ֵ��Ч����ֱ�ӷ��� */
    if ( TAF_INVALID_CID == ucCid )
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, invalid Cid");
        return VOS_TRUE;
    }

    /* ��������£�����CID������Pdp Id */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        ucPdpId = TAF_APS_GetPdpIdByCid_InEpsBearerIndOptActivate(ucCid);
    }
    else
    {
        ucPdpId = TAF_APS_GetPdpIdByEpsbId(pstBearerInfo->ulEpsbId);
    }

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        return VOS_FALSE;
    }
    else
    {
        /* �Զ�Ӧ��ģʽ��, ��Ҫ�����µ�APSʵ�����洢������Ϣ */
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, Get PDP ID fail.");
    }


    /* cidΪ0ʱ����ʾ��Ĭ�ϳ��أ���ʱ����Ǽ�������һ���µ�PDP ID
       client id��op id��ʱ��Ϊ����Чֵ��������������ʱ���ٽ���ˢ��
    */
    if ( ((TAF_APS_DEFAULT_CID == ucCid) || (ucCid > APS_PDP_MAX_CID))
      && (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption) )
    {
        /* ����(PdP Id) */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                           ucCid,
                                                           &ucPdpId))
        {
            /* ���䲻��ʵ�壬��ӡ�쳣����ʱ��Ӧ�÷��䲻��ʵ�� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, alloc pdp id fail");
            return VOS_TRUE;
        }

        /* ��¼Ĭ�ϳ��صı�־ */
        if (TAF_APS_DEFAULT_CID == ucCid)
        {
           TAF_APS_SetPdpEntAttachBearerFlag(ucPdpId, VOS_TRUE);
        }
    }
    else
    {
        /* �쳣��Ϣ, ���� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEsmEpsBearInfoInd_PreProc, Abnormal EPS Bearer.");
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aPppDialCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PPP_DIAL_CNF_STRU      *pstPppDialCnf;

    pstPppDialCnf = (APS_L4A_PPP_DIAL_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPppDialCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvL4aPsCallEndCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_L4A_PS_CALL_END_CNF_STRU      *pstPsCallEndCnf;

    pstPsCallEndCnf = (APS_L4A_PS_CALL_END_CNF_STRU*)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPsCallEndCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#if (FEATURE_ON == FEATURE_IMS)

VOS_UINT32 TAF_APS_RcvEsmNotificationInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    ESM_APS_NOTIFICATION_IND_STRU      *pstEsmNotiInd;

    pstEsmNotiInd = (ESM_APS_NOTIFICATION_IND_STRU*)pstMsg;

    /* ������Ϣ */
    TAF_APS_SndImsaSrvccCancelNotify(pstEsmNotiInd->enNotificationIndicator);

    return VOS_TRUE;
}

#endif

#endif
VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_ACTIVATE_RSP_MSG         *pstSnActRsp;

    pstSnActRsp = (APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI,�����ȡ�������� */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnActRsp->ApsSnActRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvSndcpModifyRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_MODIFY_RSP_MSG           *pstSnModifyRsp;

    pstSnModifyRsp = (APS_SNDCP_MODIFY_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI,�����ȡ�������� */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnModifyRsp->ApsSnMdfRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvSndcpDeactRsp_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_SNDCP_DEACTIVATE_RSP_MSG           *pstSnDeactRsp;

    pstSnDeactRsp = (APS_SNDCP_DEACTIVATE_RSP_MSG*)pstMsg;

    /* ��SNDCP����Ϣ�л�ȡNSAPI,�����ȡ�������� */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstSnDeactRsp->ApsSnDeActRsp.ucNsapi))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}

#if (FEATURE_ON == FEATURE_IPV6)
VOS_UINT32 TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;
    NDCLIENT_APS_PARA_INFO_NOTIFY_STRU *pstNdIpv6ParaInfoNotifyInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;


    PS_MEM_SET(&stCtrl, 0x00, sizeof(stCtrl));

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstNdIpv6ParaInfoNotifyInd = (NDCLIENT_APS_PARA_INFO_NOTIFY_STRU*)pstMsg;

    /* ��ȡNSAPI��Ӧ��APSʵ������ */
    ucPdpId = TAF_APS_GetPdpIdByNsapi(pstNdIpv6ParaInfoNotifyInd->ucRabId);
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* ����APSʵ���RA������Ϣ */
        pstPdpEntity->bitOpIpv6RaInfo = VOS_TRUE;
        PS_MEM_CPY((VOS_CHAR*)&pstPdpEntity->stIpv6RaInfo,
                   (VOS_CHAR*)&pstNdIpv6ParaInfoNotifyInd->stIpv6Info,
                   sizeof(NDCLIENT_APS_IPV6_INFO_STRU));

#if (FEATURE_ON == FEATURE_LTE)
        /* ͬ��RA��Ϣ��ESM */
        (VOS_VOID)TAF_APS_SndL4aIpv6InfoNotifyInd(pstPdpEntity->ucNsapi,
                                        &pstPdpEntity->stIpv6RaInfo);
#endif

        /* ��鵱ǰ���뼼��, �����GUģ, ��Ҫ����IPF */
        enRatType = TAF_APS_GetCurrPdpEntityRatType();

        if ( (TAF_APS_RAT_TYPE_GSM   == enRatType)
          || (TAF_APS_RAT_TYPE_WCDMA == enRatType) )
        {
            TAF_APS_IpfConfigUlFilter(ucPdpId);
        }

        /* Added by y00314741 for CDMA Iteration 15, 2015-5-24, begin */
        /* ����Ѿ��յ�DHCP�Ļظ���Ϣ�������ϱ�����������NDCLIENT��־λ */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if ((TAF_APS_RAT_TYPE_1X    == enRatType)
         || (TAF_APS_RAT_TYPE_HRPD  == enRatType)
         || (TAF_APS_RAT_TYPE_EHRPD == enRatType))
        {
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            if (VOS_TRUE == pstPdpEntity->ucRcvDhcpDnsFlgIpv6)
            {
                /* ��дAPP����ͷ */
                TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

                /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
                TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                               pstPdpEntity->stClientInfo.ucCid,
                                               pstPdpEntity->ucNsapi,
                                               (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);

                /* ����Ѿ��ϱ����־λ */
                pstPdpEntity->ucRcvNdClientNtyFlg = VOS_FALSE;
                pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_FALSE;
                pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_FALSE;

                return VOS_TRUE;
            }
            else
            {
                pstPdpEntity->ucRcvNdClientNtyFlg = VOS_TRUE;

                return VOS_TRUE;
            }

        }
#endif
        /* Added by y00314741 for CDMA Iteration 15, 2015-5-24, end */

        /* ��鵱ǰAPS�Ƿ����û�ʹ��, ������û�ʹ��, �ϱ�RA��Ϣ�¼� */
        if ((TAF_APS_INVALID_CLIENTID != TAF_APS_GetPdpEntClientId(ucPdpId, pstPdpEntity->stClientInfo.ucCid))
         && (VOS_TRUE == pstPdpEntity->ulUsedFlg))
        {
            /* ��дAPP����ͷ */
            TAF_APS_SetPsCallEvtCtrl(ucPdpId, pstPdpEntity->stClientInfo.ucCid, &stCtrl);

            /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
            TAF_APS_SndIpv6RaInfoNotifyInd(&stCtrl,
                                           pstPdpEntity->stClientInfo.ucCid,
                                           pstPdpEntity->ucNsapi,
                                           (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
        }
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvNdIpv6ParaInfoNotifyInd_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

#endif
VOS_UINT32 TAF_APS_RcvAtGetGprsActiveTypeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                              ulErrCode;
    TAF_PDP_TYPE_ENUM_UINT8                 enPdpType;
    TAF_CID_GPRS_ACTIVE_TYPE_STRU           stCidGprsActiveType;
    TAF_PS_MSG_STRU                        *pstAppMsg;
    TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU *pstGetGprsActiveTypeReq;

    /* ��ʼ�� */
    ulErrCode               = TAF_PARA_OK;
    pstAppMsg               = (TAF_PS_MSG_STRU*)pstMsg;
    pstGetGprsActiveTypeReq = (TAF_PS_GET_D_GPRS_ACTIVE_TYPE_REQ_STRU*)(pstAppMsg->aucContent);

    /* ��ȡGPRS�������� */
    PS_MEM_SET(&stCidGprsActiveType, 0x00, sizeof(TAF_CID_GPRS_ACTIVE_TYPE_STRU));
    stCidGprsActiveType.ucCid = pstGetGprsActiveTypeReq->stAtdPara.ucCid;

    enPdpType = Taf_GetCidType(pstGetGprsActiveTypeReq->stAtdPara.ucCid);

    /* ɾ��L2PЭ�����͵��жϴ��� */

    /* ֱ�Ӹ���CID�����ĵ�PDP���;�������PPPʵ������ */
    switch (enPdpType)
    {
        case TAF_PDP_IPV4:
            /* IP����,����IP���TE��������PPP��MT������PPP */
            stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
            break;

#if (FEATURE_ON == FEATURE_IPV6)
        case TAF_PDP_IPV6:
        case TAF_PDP_IPV4V6:
            /* IP����,����IP���TE��������PPP��MT������PPP */
            stCidGprsActiveType.enActiveType = TAF_IP_ACTIVE_TE_PPP_MT_PPP_TYPE;
            break;
#endif

        case TAF_PDP_PPP:
            /* PPP����,����PPP���TE��������PPP��MT�в�����PPP */
            stCidGprsActiveType.enActiveType = TAF_PPP_ACTIVE_TE_PPP_MT_NOT_PPP_TYPE;
            break;

        default:
            ulErrCode = TAF_PS_CAUSE_INVALID_PARAMETER;
            break;
    }

    (VOS_VOID)TAF_APS_SndGetGprsActiveTypeCnf(&(pstGetGprsActiveTypeReq->stCtrl),
                                   ulErrCode,
                                   &stCidGprsActiveType);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtSetDnsQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                        *pstPsMsg        = VOS_NULL_PTR;
    TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU    *pstNegoDnsReq   = VOS_NULL_PTR;
    TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU     stNegoDnsCnf;
    VOS_UINT8                               ucPdpId         = TAF_APS_INVALID_PDPID;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity    = VOS_NULL_PTR;
    TAF_APS_STA_ENUM_UINT32                 enStaState      = TAF_APS_STA_BUTT;
    TAF_APS_CDATA_PS_STATE_ENUM_UINT8       enCdataPsState;

    /* ��ʼ�� */
    pstPsMsg        = (TAF_PS_MSG_STRU*)pstMsg;
    pstNegoDnsReq   = (TAF_PS_GET_NEGOTIATION_DNS_REQ_STRU *)pstPsMsg->aucContent;
    ucPdpId         = TAF_APS_GetPdpIdByCid(pstNegoDnsReq->ucCid);
    PS_MEM_SET(&stNegoDnsCnf, 0, sizeof(stNegoDnsCnf));

    /* ��д��Ϣ���� */
    stNegoDnsCnf.stCtrl                 = pstNegoDnsReq->stCtrl;

    stNegoDnsCnf.enCause                = TAF_PS_CAUSE_UNKNOWN;

    /* ��ȡCID��Ӧ��PdpId */
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        enCdataPsState = TAF_APS_GetPdpEntCdataPsState(ucPdpId);

        /* ����CID��ӦPDP�Ƿ񼤻� */
        enStaState  = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ( (TAF_APS_STA_ACTIVE            == enStaState)
          || (TAF_APS_STA_MS_MODIFYING      == enStaState)
          || (TAF_APS_STA_MS_DEACTIVATING   == enStaState)
          || (TAF_APS_STA_CDATA_DISCING     == enStaState)
          || (TAF_APS_CDATA_PS_STATE_ACTIVE == enCdataPsState) )
        {
            /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
            pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

            /* ��ȡ�ü���PDP��Ӧ����DNS, ��DNS��Ϣ */
            stNegoDnsCnf.stNegotiationDns.ucCid = pstNegoDnsReq->ucCid;
            stNegoDnsCnf.enCause = TAF_PS_CAUSE_SUCCESS;
            stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpPrimDnsAddr = VOS_TRUE;
            stNegoDnsCnf.stNegotiationDns.stDnsInfo.bitOpSecDnsAddr  = VOS_TRUE;

            if (VOS_TRUE == pstPdpEntity->PdpDnsFlag)
            {
                if (VOS_TRUE == pstPdpEntity->PdpDns.OP_PriDns)
                {
                    PS_MEM_CPY(stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucPrimDnsAddr,
                               pstPdpEntity->PdpDns.aucPriDns,
                               TAF_IPV4_ADDR_LEN);
                }

                if (VOS_TRUE == pstPdpEntity->PdpDns.OP_SecDns)
                {
                    PS_MEM_CPY(stNegoDnsCnf.stNegotiationDns.stDnsInfo.aucSecDnsAddr,
                               pstPdpEntity->PdpDns.aucSecDns,
                               TAF_IPV4_ADDR_LEN);
                }
            }
        }
    }

    /* ������������ATģ�� */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_NEGOTIATION_DNS_CNF,
                     &stNegoDnsCnf,
                     sizeof(TAF_PS_GET_NEGOTIATION_DNS_CNF_STRU));

    return VOS_TRUE;
}






VOS_UINT32 TAF_APS_RcvTiApsLimitPdpActExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvTiApsMsActvaingExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* PDP�������޴���:�˶�ʱ����ʱ��Ϊ�쳣,PDP���������һ�δ��� */
    TAF_APS_ProcPdpActLimit_PreProc(1);

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_GetActPdpLimitTimerLen(
    VOS_UINT8                           ucFailCount
)
{
    VOS_UINT32                          ulTimeLen;

    ulTimeLen = 0;

    /* ��ͣPDP���ʱ��ʱ�����ż���ʧ�ܵĴ�����ȷ����С�ڵ���10��ֱ�ӷ���ʱ��0.
    11-18�ΰ���10s��������ʱ��������18�ε�ͳһʹ��90sʱ�� */
    if (ucFailCount <= TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
    {
        return 0;
    }

    /* PDP�����11-19��֮�ڣ�����10s��������������ʱ�� */
    if (ucFailCount < TAF_APS_PDP_ACT_LIMIT_STEP_DELAY_COUNT_THRESHOLD)
    {
        ulTimeLen = (ucFailCount - TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
                        * TAF_APS_PDP_ACT_LIMIT_STEP_TIME;
    }
    else
    {   /* PDP�����19��(����19��)���ϣ�����90sʱ��������ʱ�� */
        /* ��ʧ�ܴ�����10��������ʱ��PDP��ͣ���ʱ��ʹ�����ʱ�� */
        if (0 == (ucFailCount % TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_FAILCOUNT))
        {
            ulTimeLen = TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME
                        + VOS_Rand(TAF_APS_PDP_ACT_LIMIT_RANDOM_TIME_THRESHOLD);
        }
        else
        {
            ulTimeLen = TAF_APS_PDP_ACT_LIMIT_AVERAGE_DELAY_TIME;
        }
    }

    /* ��ʱ��ʱ����λΪms */
    return (ulTimeLen * TIMER_S_TO_MS_1000);
}


VOS_VOID TAF_APS_ProcPdpActLimit_PreProc(VOS_UINT8 ucTryingCount)
{
    TAF_APS_PDP_ACT_LIMIT_INFO_STRU    *pstPdpActLimitInfo;

    pstPdpActLimitInfo = TAF_APS_GetPdpActLimitInfoAddr();

    /* �ж�PDP�������޹����Ƿ�� */
    if (VOS_TRUE == pstPdpActLimitInfo->ucPdpActLimitFlg)
    {
        pstPdpActLimitInfo->ucPdpActFailCount = pstPdpActLimitInfo->ucPdpActFailCount + ucTryingCount;

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            return;
        }

        if (pstPdpActLimitInfo->ucPdpActFailCount > TAF_APS_PDP_ACT_LIMIT_NO_DELAY_COUNT_THRESHOLD)
        {
            TAF_APS_StartTimer(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_GetActPdpLimitTimerLen(pstPdpActLimitInfo->ucPdpActFailCount), TAF_APS_PDP_ACT_LIMIT_PDP_ID);
        }
    }

    return;
}
VOS_UINT32 TAF_APS_IsPdpActLimit_PreProc(VOS_VOID)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    enCurrRatType        = TAF_APS_GetCurrPdpEntityRatType();

    /* PS����Ч����״̬���д��� */
    if (VOS_FALSE == TAF_APS_GetCurrPdpEntitySimRegStatus())
    {
        return VOS_FALSE;
    }

    /* ĿǰPDP�������޵Ĺ���ֻ������GUģ */
    if ((TAF_APS_RAT_TYPE_GSM == enCurrRatType)
     || (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType))
    {
        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_LIMIT_PDP_ACT, TAF_APS_PDP_ACT_LIMIT_PDP_ID))
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_PdpActLimit_PreProc(
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpStateReq
)
{
    if (VOS_TRUE == TAF_APS_IsPdpActLimit_PreProc())
    {
        /* ������ȥ���� */
        if (TAF_CGACT_ACT != pstSetPdpStateReq->stCidListStateInfo.ucState)
        {
            return VOS_FALSE;
        }

        TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpStateReq->stCtrl),
                                    TAF_PS_CAUSE_PDP_ACTIVATE_LIMIT);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_APS_RcvOmSetDsflowRptReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Modified by wx270776 for OM�ں�, 2015-7-1, begin */
    NAS_OM_SET_DSFLOW_RPT_REQ_STRU     *pstDsflowRptReq = VOS_NULL_PTR;
    NAS_OM_SET_DSFLOW_RPT_CNF_STRU     *pstDsflowRptCnf = VOS_NULL_PTR;
    TAF_APS_DSFLOW_STATS_CTX_STRU      *pstApsDsFlowCtx = VOS_NULL_PTR;//global
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulRet;

    /* ������Ϣ */
    ulMsgLen        = sizeof(NAS_OM_SET_DSFLOW_RPT_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstDsflowRptCnf = (NAS_OM_SET_DSFLOW_RPT_CNF_STRU*)PS_ALLOC_MSG(WUEPS_PID_TAF, ulMsgLen);
    if (VOS_NULL_PTR == pstDsflowRptCnf)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvOmSetDsflowRptReq_PreProc: PS_MEM_ALLOC Failed!");

        return VOS_FALSE;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8*)pstDsflowRptCnf + VOS_MSG_HEAD_LENGTH, 0x00, ulMsgLen);

    pstDsflowRptReq = (NAS_OM_SET_DSFLOW_RPT_REQ_STRU*)pstMsg;

    pstApsDsFlowCtx = TAF_APS_GetDsFlowCtxAddr();

    /* ����OM�����ϱ���־λ */
    switch(pstDsflowRptReq->enRptAction)
    {
        case NAS_OM_REPORT_START:
            if ( (pstDsflowRptReq->usRptPeriod >= TI_TAF_APS_DSFLOW_REPORT_LEN)
              && (0 == (pstDsflowRptReq->usRptPeriod % TI_TAF_APS_DSFLOW_REPORT_LEN)) )
            {
                pstApsDsFlowCtx->ucDsFlowOMReportFlg    = VOS_TRUE;
                pstApsDsFlowCtx->ucDsFlowOMRptPeriod    = (VOS_UINT8)(pstDsflowRptReq->usRptPeriod / TI_TAF_APS_DSFLOW_REPORT_LEN);
                pstDsflowRptCnf->enResult                 = NAS_OM_RESULT_NO_ERROR;
            }
            else
            {
                pstDsflowRptCnf->enResult                 = NAS_OM_RESULT_INCORRECT_PARAMETERS;
            }
            break;
        case NAS_OM_REPORT_STOP:
            pstApsDsFlowCtx->ucDsFlowOMReportFlg        = VOS_FALSE;
            pstApsDsFlowCtx->ucDsFlowOMRptPeriod        = 0;
            break;
        default:
            pstDsflowRptCnf->enResult                     = NAS_OM_RESULT_INCORRECT_PARAMETERS;
            break;
    }

    /* �����Ϣ���� */
    pstDsflowRptCnf->ulReceiverPid    = MSP_PID_DIAG_APP_AGENT;
    pstDsflowRptCnf->ulMsgId          = ID_NAS_OM_SET_DSFLOW_RPT_CNF;
    pstDsflowRptCnf->usOriginalId     = pstDsflowRptReq->usOriginalId;
    pstDsflowRptCnf->usTerminalId     = pstDsflowRptReq->usTerminalId;
    pstDsflowRptCnf->ulTimeStamp      = pstDsflowRptReq->ulTimeStamp;
    pstDsflowRptCnf->ulSN             = pstDsflowRptReq->ulSN;


    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_TAF, pstDsflowRptCnf);
    if (VOS_OK != ulRet)
    {
        MN_WARN_LOG("NAS_MMC_SndOmOtaCnf:WARNING: Send msg fail.");

        return VOS_FALSE;
    }



    return VOS_TRUE;
    /* Modified by wx270776 for OM�ں�, 2015-7-1, end */

}
VOS_UINT32 TAF_APS_RcvMmcServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_APS_SERVICE_STATUS_IND_STRU    *pstSerStaInd;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enLastRatType;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSerStaInd  = (MMC_APS_SERVICE_STATUS_IND_STRU*)pstMsg;
    enRatType     = TAF_APS_ConvertMmcRatType(pstSerStaInd->enRatType);
    enLastRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* ���µ�PS��״̬ */
    TAF_APS_SetCurrPdpEntitySimRegStatus(pstSerStaInd->ulPsSimRegStatus);

    if (TAF_APS_RAT_TYPE_NULL != enRatType)
    {
         /* ��¼���õ�PS��״̬���ڹ���ʱʹ�� */
        TAF_APS_SET_RAT_TYPE_IN_SUSPEND(enRatType);

        /* ��¼���õ�PS��״̬ */
        TAF_APS_SetCurrPdpEntityRatType(enRatType);
    }
    else
    {

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        TAF_APS_SetFinishClSearch(VOS_FALSE);

        if (TAF_APS_RAT_TYPE_1X == enLastRatType)
        {
            /* ���ԭ����1Xģʽ��������MMC�ϱ���NULL��֪ͨ */
            return VOS_TRUE;
        }
        else
#endif
        {
            TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_NULL);
        }
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* �����ǰPDPʵ�岻ΪINACTIVE״̬�������ڲ���Ϣ��״̬������ */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            /* �ڲ���Ϣ��Я������MMC�ϱ��ķ���״̬���������������е�
               ״̬��������ڲ���Ϣʱ��ʹ����Ϣ��Я������Ϣ
            */
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   enRatType,
                                                   enLastRatType,
                                                   pstSerStaInd->ulPsSimRegStatus,
                                                   VOS_FALSE);
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsGetCidSdfReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucNum;
    TAF_PS_SDF_INFO_REQ_STRU           *pstSdfInfoReq;
    TAF_PS_SDF_INFO_CNF_STRU           *pstSdfInfoCnf;

    pstSdfInfoReq = (TAF_PS_SDF_INFO_REQ_STRU *)pstMsg;

    /* ������Ϣ�ڴ� */
    pstSdfInfoCnf = (TAF_PS_SDF_INFO_CNF_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                            sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* ������Ϣʧ�� */
    if ( VOS_NULL_PTR == pstSdfInfoCnf )
    {
        MN_ERR_LOG("TAF_APS_RcvPsGetCidSdfReq_PreProc:  ERROR : PS_MEM_ALLOC Error!");
        return VOS_TRUE;
    }

    PS_MEM_SET(pstSdfInfoCnf, 0, sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* ��д��Ϣͷ */
    pstSdfInfoCnf->stCtrl = pstSdfInfoReq->stCtrl;

    for (ucNum = 1; ucNum <= TAF_MAX_CID_NV; ucNum++)
    {
        if (VOS_OK == TAF_APS_GetSdfParaInfo(ucNum,
                              &(pstSdfInfoCnf->stSdfInfo.astSdfPara[pstSdfInfoCnf->stSdfInfo.ulSdfNum])))
        {
            pstSdfInfoCnf->stSdfInfo.ulSdfNum ++;
        }
    }

    /* ����ID_MSG_TAF_GET_CID_SDF_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_CID_SDF_CNF,
                     (VOS_VOID *) pstSdfInfoCnf,
                     sizeof(TAF_PS_SDF_INFO_CNF_STRU));

    /* �ͷ����ڴ��SDF�������ڴ� */
    PS_MEM_FREE(WUEPS_PID_TAF, pstSdfInfoCnf);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSetImsPdpCfgReq_PreProc
 ��������  : ����PDP�Ƿ�֧��IMS
 �������  : VOS_VOID                           *pMsgData
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��29��
    ��    ��   : z00301431
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvSetImsPdpCfgReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CID_IMS_CFG_TBL_STRU       *pstCidImsCfgTbl;
    TAF_PS_SET_IMS_PDP_CFG_REQ_STRU    *pstSetImsPdpCfgReq;
    TAF_PS_SET_IMS_PDP_CFG_CNF_STRU     stSetImsPdpCfgCnf;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucImsFlag;

    enCause             = TAF_PS_CAUSE_SUCCESS;
    pstSetImsPdpCfgReq  = (TAF_PS_SET_IMS_PDP_CFG_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ucCid       = pstSetImsPdpCfgReq->stImsPdpCfg.ucCid;
    ucImsFlag   = pstSetImsPdpCfgReq->stImsPdpCfg.ucImsFlag;

    /* �ж�CID��Ч�� */
    if (!(TAF_PS_PDP_CONTEXT_CID_VALID(ucCid)))
    {
        enCause = TAF_PS_CAUSE_CID_INVALID;
    }
    else
    {
        /* ����CID��IMS���� */
        pstCidImsCfgTbl = TAF_APS_GetCidImsCfgTable();
        pstCidImsCfgTbl->aucImsFlag[ucCid] = ucImsFlag;
    }

    PS_MEM_SET(&stSetImsPdpCfgCnf, 0, sizeof(TAF_PS_SET_IMS_PDP_CFG_CNF_STRU));

    /* ��д��Ϣͷ */
    stSetImsPdpCfgCnf.stCtrl  = pstSetImsPdpCfgReq->stCtrl;
    stSetImsPdpCfgCnf.enCause = enCause;

    /* ����ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_IMS_PDP_CFG_CNF,
                               &stSetImsPdpCfgCnf,
                               sizeof(TAF_PS_SET_IMS_PDP_CFG_CNF_STRU));

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_CL_INTERWORK)

VOS_UINT8 TAF_APS_LCCheckReqValid(
    TAF_CTRL_STRU                       *pstCtrlInfo
)
{
    TAF_PH_MODE                         ucPhMode;

    ucPhMode                            = MMA_GetCurrPhMode();

    /* �ǿ���״̬���������� */
    if (TAF_PH_MODE_FULL != ucPhMode)
    {
        return VOS_TRUE;
    }
    /* ��L+C�����������£���CMMCA�·����������� */
    if ((VOS_TRUE        == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (WUEPS_PID_CMMCA != pstCtrlInfo->ulModuleId))
    {
        return VOS_FALSE;
    }

    /* �ڷ�L+C�����������£�CMMCA�·����������� */
    if ((VOS_FALSE       == TAF_SDC_IsConfigCLInterWorkCOutside())
     && (WUEPS_PID_CMMCA == pstCtrlInfo->ulModuleId))
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_APS_RcvXccDataCallSuspendInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_SUSPEND_IND_STRU *pstSuspendInd = VOS_NULL_PTR;

    pstSuspendInd = (XCC_APS_DATA_CALL_SUSPEND_IND_STRU *)pstMsg;

    TAF_APS_SET_CDATA_SUSPEND_STATUS(TAF_APS_CDMA_TC_SUSPENDED);


    /* TO DO:����״̬���д������Ϣ */

    /* DMT����ʱ�����g_ulApsTestStubΪTRUE���򲻻ظ�SUSPEND_RSP��Ϣ */
    if (VOS_FALSE == g_ulApsTestStub)
    {
        TAF_APS_SndXccDataCallSuspendRsp(pstSuspendInd->ucConnectId);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvXccDataCallResumeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_RESUME_IND_STRU  *pstResumeInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT32                          ulExist1XService;
    VOS_UINT8                           ucPdpId;



    /* ��ȡ��Ϣ���� */
    pstResumeInd            = (XCC_APS_DATA_CALL_RESUME_IND_STRU *)pstMsg;
    ulExist1XService        = TAF_APS_Get1XPsServiceStatus();

    TAF_APS_SET_CDATA_SUSPEND_STATUS(TAF_APS_CDMA_TC_RESUMED);


    if ((TAF_APS_RAT_TYPE_NULL == TAF_APS_GetCurrPdpEntityRatType())
     && (VOS_TRUE == ulExist1XService))
    {
        TAF_APS_SetCurrPdpEntityRatType(TAF_APS_RAT_TYPE_1X);
        /* TODO: ��Ҫ�ٷ��ڲ���Ϣ */
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstResumeInd->ucConnectId)
        {
            /* ��ǰֻ֧��һ·���У�ConnectIdƥ��ɹ��󣬽���״̬������ */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstOrigCallCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstOrigCallCnf = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstOrigCallCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccOrigDataCallCnf_PreProc:Wrong CallId", pstOrigCallCnf->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvXccHangupDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_HANGUP_DATA_CALL_CNF_STRU  *pstHangUpCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstHangUpCnf = (XCC_APS_HANGUP_DATA_CALL_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstHangUpCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccHangupDataCallCnf_PreProc:Wrong CallId", pstHangUpCnf->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;

}


VOS_UINT32 TAF_APS_RcvXccDataCallDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscCallInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscCallInd = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.ucConnectId == pstDiscCallInd->ucConnectId)
        {
            /* ��״̬������ */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingCallInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstIncomingCallInd = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* ��ǰֻ֧��dormant״̬�£����緢���Ѱ���������Ч��PDP ID��ֱ������ */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }



        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        if (pstPdpEntity->stCdataInfo.enSo == pstIncomingCallInd->enSo)
        {
            /* ����ConnectId��APSʵ���� */
            TAF_APS_SetPdpEntConnectId(ucPdpId, pstIncomingCallInd->ucConnectId);

            TAF_APS_SndXccIncomingCallRsp(pstPdpEntity->stCdataInfo.ucCallId,
                                          pstIncomingCallInd->ucConnectId,
                                          XCC_APS_RESULT_SUCC);

            /* ��״̬������ */
            return VOS_FALSE;
        }
    }

    TAF_APS_SndXccIncomingCallRsp(pstIncomingCallInd->ucCallId,
                                  pstIncomingCallInd->ucConnectId,
                                  XCC_APS_RESULT_FAIL);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXccDataCallConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstConnCallInd = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstConnCallInd = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstConnCallInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccDataCallConnInd_PreProc:Wrong CallId", pstConnCallInd->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU        *pstServiceConnInd = VOS_NULL_PTR;
    VOS_UINT8                                     ucPdpId;

    pstServiceConnInd = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstServiceConnInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccDataServiceConnInd_PreProc:Wrong CallId", pstServiceConnInd->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;

}


VOS_UINT32 TAF_APS_RcvXccAnswerDataCallCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU  *pstAnswerCallCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstAnswerCallCnf = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstAnswerCallCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccAnswerDataCallCnf_PreProc:Wrong CallId", pstAnswerCallCnf->ucCallId);
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

VOS_VOID TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    VOS_UINT8                           ucPdpId;

    switch (pstSoCtrlMsgInd->ucDormCntl)
    {
        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_DISABLE:
            TAF_APS_SetSocmDormantTiLen(0);
            TAF_APS_SetUserCfgDormTiVal(0);
            break;

        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_SET_MIN_VALUE:
        case XCC_APS_SOCM_DORMANT_TIMER_CTRL_SET_MIN_AND_CUR_VALUE:
            if (TAF_APS_GetSocmDormantTiLen() < (pstSoCtrlMsgInd->ucDormTimer * 100))
            {
                TAF_APS_SetSocmDormantTiLen(pstSoCtrlMsgInd->ucDormTimer * 100);
            }

            for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
            {
                if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
                {
                    continue;
                }

                /* TO DO: ��ҵ��SO�����ж� */
                if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
                {
                    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

                    if (TAF_APS_GetUserCfgDormTiVal() > TAF_APS_GetSocmDormantTiLen())
                    {
                        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetUserCfgDormTiVal(), ucPdpId);
                    }
                    else
                    {
                        TAF_APS_StartTimer(TI_TAF_APS_CDATA_DORMANT, TAF_APS_GetSocmDormantTiLen(), ucPdpId);
                    }
                }
            }

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc, Invalid DormCntl Field");
            break;
    }

    return;
}
VOS_VOID TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc(
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsgInd
)
{
    /* Parse Socm msg according to Pkt_Conect_Cntl Field */
    switch (pstSoCtrlMsgInd->ucPktConCntl)
    {
        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_DISABLE:
            TAF_APS_EpdszidSocmDisableReconn();
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_ENABLE:
            TAF_APS_EpdszidSocmEnableReconn(pstSoCtrlMsgInd->ucPktZoneListLen);
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_CLEAR:
            TAF_APS_EpdszidSocmClearPacketZoneList(pstSoCtrlMsgInd->ucPktZoneListLen);
            break;

        case XCC_APS_SOCM_PACKET_ZONE_RECONNECT_CTRL_TRANSFER:
            TAF_APS_EpdszidScomTransferPzid(pstSoCtrlMsgInd);
            break;

        default:
            break;
    }

    return;
}
VOS_UINT32 TAF_APS_RcvXccSoCtrlMsg_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_SO_CTRL_MSG_IND_STRU       *pSoCtrlMsg;

    pSoCtrlMsg = (XCC_APS_SO_CTRL_MSG_IND_STRU *)pstMsg;

    switch (pSoCtrlMsg->enFieldType)
    {
        case XCC_APS_SO_CTRL_FIELD_DORMANT_TIMER_CTRL:
            TAF_APS_RcvXccSetPdpEntDormantTimer_PreProc(pSoCtrlMsg);
            break;

        case XCC_APS_SO_CTRL_FIELD_PACKET_ZONE_RECONN_CTRL:
            TAF_APS_RcvXccSetPacketZoneReconnFeature_PreProc(pSoCtrlMsg);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvXccSoCtrlMsg_PreProc, Error Socm msg");
            break;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPppActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf = VOS_NULL_PTR;

    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppActCnf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPppDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstPppDeactCnf  = VOS_NULL_PTR;

    pstPppDeactCnf = (PPP_APS_DEACT_CNF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppDeactCnf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;

}
VOS_UINT32 TAF_APS_RcvPppDeactNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_NTF_STRU             *pstPppDeactNtf = VOS_NULL_PTR;

    pstPppDeactNtf = (PPP_APS_DEACT_NTF_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppDeactNtf->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;

}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppModifyInd_PreProc
 ��������  : �յ�ID_PPP_APS_MODIFY_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPppModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_MODIFY_IND_STRU            *pstPppModifyInd = VOS_NULL_PTR;

    pstPppModifyInd = (PPP_APS_MODIFY_IND_STRU *)pstMsg;

    if (TAF_APS_INVALID_PDPID != TAF_APS_GetPdpIdByPndId(pstPppModifyInd->ucPdnId))
    {
        return VOS_FALSE;
    }

    /* ���򲻽�״̬������ */
    return VOS_TRUE;
}
/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */


VOS_UINT32 TAF_APS_RcvCdsServiceInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    CDS_APS_CDATA_SERVICE_IND_STRU     *pstCdsServiceInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstCdsServiceInd = (CDS_APS_CDATA_SERVICE_IND_STRU *)pstMsg;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* ��������ҵ���Ӧ��ʵ�壬��¼��ǰ�Ĵ������� */
        if (pstPdpEntity->ucNsapi == pstCdsServiceInd->ucRabId)
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_SetCqosPriReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstPsMsg;
    TAF_PS_SET_1X_CQOS_PRI_REQ_STRU    *pstSetCqosPriReq;

    pstPsMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetCqosPriReq                   = (TAF_PS_SET_1X_CQOS_PRI_REQ_STRU*)(pstPsMsg->aucContent);

    /* ���û����ü�¼��NV���� */

    /* NVδ���壬To Do */

    /* �������ý�� */

    /* ���ش����� */
    TAF_APS_SndSetCqosPriCnf(&(pstSetCqosPriReq->stCtrl),
                              TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CALL_ENTER_DORMANT_IND_STRU *pstDormantInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstDormantInd = (TAF_PS_CALL_ENTER_DORMANT_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstDormantInd->ucPdpId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvPsCallEnterDormantInd_PreProc:Wrong PdpId", pstDormantInd->ucPdpId);
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 TAF_APS_RcvTiHatExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ProcEpdszidHatExpired();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvTiHtExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ProcEpdszidHtExpired();

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvMmaEpdszidInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_EPDSZID_INFO_IND_STRU      *pEpdszidInfoInd = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;
    VOS_UINT8                           ucPdpId;

    pEpdszidInfoInd = (MMA_APS_EPDSZID_INFO_IND_STRU *)pstMsg;

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = pEpdszidInfoInd->usSid;
    stCdataEpdszid.usNid  = pEpdszidInfoInd->usNid;
    stCdataEpdszid.ucPzid = pEpdszidInfoInd->ucPzid;

    /* ��ά�ɲ� */
    TAF_APS_TraceEpdszidInfo();

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* ��ǰ���״̬��ʵ�崦��Inactive״̬������Ҫ����EPDSZID�ı���������ؽ� */
        if (TAF_APS_STA_INACTIVE == TAF_APS_GetPdpIdMainFsmState(ucPdpId))
        {
            continue;
        }

        /* �������� */
        /* �ǲ��Ǽ�⵽һ����Ч��PDPID���ɷ��ͺ��������Ǹ���ҵ��� */
        TAF_APS_ProcMmaEpdszidInfo(pEpdszidInfoInd->usSid,
                                   pEpdszidInfoInd->usNid,
                                   pEpdszidInfoInd->ucPzid,
                                   ucPdpId);
        return VOS_TRUE;
    }

    /* If Don't Snd Internal Msg Only Update Epdszid */
    TAF_APS_SetCurrEpdszidInfo(&stCdataEpdszid);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXregRegBeginInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XREG_APS_REG_BEGIN_IND_STRU        *pRegBeginInd = VOS_NULL_PTR;

    pRegBeginInd = (XREG_APS_REG_BEGIN_IND_STRU *)pstMsg;

    TAF_APS_ProcXregEpdszidRegBeginInd(pRegBeginInd->usSid,
                                       pRegBeginInd->usNid,
                                       pRegBeginInd->ucPzid);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrig_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*TO Do: ���������Ӷ�ģ�ںϺ�Ĵ��� */

    return VOS_FALSE;
}

/* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsHaiChangeInd_PreProc
 ��������  : �յ�ID_MSG_TAF_PS_HAI_CHANGE_IND��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��1��4��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsHaiChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_HAI_CHANGE_IND_STRU         *pstHaiChangeInd;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstHaiChangeInd = (TAF_PS_HAI_CHANGE_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (VOS_TRUE != TAF_APS_IsPdpIdValid(pstHaiChangeInd->ucPdpId))
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvPsHaiChangeInd_PreProc:Wrong PdpId", pstHaiChangeInd->ucPdpId);
        return VOS_TRUE;
    }

    TAF_APS_ProcEpdszidHaiChangeInd();

    return VOS_TRUE;
}
/* Added by y00314741 for CDMA 1X Iteration 7, 2015-1-4, end */

VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInfo = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdpId;

    pstDataCallInfo = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    /* If can not find corresponding PDP ID, discard this message */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDataCallInfo->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvXccUpdateDataCallInfoInd_PreProc:Wrong CallId", pstDataCallInfo->ucCallId);
        return VOS_TRUE;
    }

    /* Enter FSM to process */
    return VOS_FALSE;
}

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmOrigCnf_PreProc
 ��������  : �յ�ID_HSM_APS_ORIG_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmOrigCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOrigCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstOrigCnf = (HSM_APS_ORIG_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstOrigCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmConnectInd_PreProc
 ��������  : �յ�ID_HSM_APS_CONNECT_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmConnectInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity   = VOS_NULL_PTR;
    TAF_APS_STA_ENUM_UINT32             enStatus;
    VOS_UINT8                           ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* ��ǰֻ֧��dormant״̬�£����緢���Ѱ���������Ч��PDP ID��ֱ������ */
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        /* ���缤��ֻ����DORMANT��TAF_APS_STA_CDATA_ESTING״̬�µ����� */
        enStatus = TAF_APS_GetPdpIdMainFsmState(ucPdpId);
        if ((TAF_APS_STA_DORMANT == enStatus)
          ||(TAF_APS_STA_CDATA_ESTING == enStatus))
        {
            pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

            TAF_APS_SndHsmConnectRsp(pstPdpEntity->stCdataInfo.ucCallId);

            /* ��״̬������ */
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscCnf_PreProc
 ��������  : �յ�ID_HSM_APS_DISC_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmDiscCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_DISC_CNF_STRU              *pstDiscCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscCnf = (HSM_APS_DISC_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDiscCnf->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscInd_PreProc
 ��������  : �յ�ID_HSM_APS_DISC_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmDiscInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_DISC_IND_STRU              *pstDiscInd     = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    pstDiscInd = (HSM_APS_DISC_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    ucPdpId = TAF_APS_GetPdpIdByCallId(pstDiscInd->ucCallId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmLocChangedInd_PreProc
 ��������  : �յ�ID_HSM_APS_LOC_CHANGED_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmLocChangedInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_LOC_CHANGED_IND_STRU       *pstLocChangedInd = VOS_NULL_PTR;
    TAF_APS_CDATA_EPDSZID_STRU          stCdataEpdszid;

    pstLocChangedInd = (HSM_APS_LOC_CHANGED_IND_STRU *)pstMsg;

    PS_MEM_SET(&stCdataEpdszid, 0, sizeof(TAF_APS_CDATA_EPDSZID_STRU));
    stCdataEpdszid.usSid  = pstLocChangedInd->usSid;
    stCdataEpdszid.usNid  = pstLocChangedInd->usNid;
    stCdataEpdszid.ucPzid = pstLocChangedInd->ucPktZoneId;

    /* TODO:Ŀǰֻ��¼��current�У���1X��HRPD���л�ʱ�پ��忼�� */
    TAF_APS_SetCurrEpdszidInfo(&stCdataEpdszid);

    /* ����hrpd���µ�Sid/Nid��Ϣ */
    TAF_APS_SetHrpdEpdszidInfo(pstLocChangedInd->usSid,
                               pstLocChangedInd->usNid,
                               pstLocChangedInd->ucPktZoneId);

    /* ��ά�ɲ� */
    TAF_APS_TraceEpdszidInfo();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsm1XToHrpdHandOff_PreProc
 ��������  : �յ�ID_HSM_APS_1X_TO_HRPD_HANDOFF_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��05��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsm1XToHrpdHandOff_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucPdpId;

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        if (VOS_TRUE != TAF_APS_IsPdpIdValid(ucPdpId))
        {
            continue;
        }

        return VOS_FALSE;
    }

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */

/* Modified by y00314741 for  CDMA Iteration 17, 2015-7-8, begin */
VOS_UINT32 TAF_APS_RcvPsSet1xPktDataInactivityTimeLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_CTA_INFO_REQ_STRU       *pstSet1xPktDtInactivityTmrlenReq = VOS_NULL_PTR;

    pstSet1xPktDtInactivityTmrlenReq = (TAF_PS_SET_CTA_INFO_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    TAF_APS_Set1xPktDataInactivityTimerLen(pstSet1xPktDtInactivityTmrlenReq->uc1XPktDtInactivityTmrLen);

    TAF_APS_SndSet1xPktDataInactivityTimerLenCnf(&(pstSet1xPktDtInactivityTmrlenReq->stCtrl), TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}
/* Modified by y00314741 for  CDMA Iteration 17, 2015-7-17, begin */
VOS_UINT32 TAF_APS_RcvPsGet1xPktDataInactivityTimerLenReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_1X_CTA_INFO_REQ_STRU    *pstGet1xPktDtInactivityTmrlenReq = VOS_NULL_PTR;
    VOS_UINT8                                               ucTimeLen;

    pstGet1xPktDtInactivityTmrlenReq  = (TAF_PS_GET_1X_CTA_INFO_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ucTimeLen = TAF_APS_Get1xPktDataInactivityTimerLen();

    TAF_APS_SndGet1xPktDataInactivityTimerLenCnf(&(pstGet1xPktDtInactivityTmrlenReq->stCtrl), ucTimeLen, TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}
/* Modified by y00314741 for  CDMA Iteration 17, 2015-7-8, end */


VOS_UINT32 TAF_APS_RcvPowerOnInd_Preproc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_SDC_SIM_TYPE_ENUM_UINT8         enSimType;
    VOS_UINT16                          usFileId;
    NAS_USIMM_GETFILE_INFO_STRU         stGetFileInfo;

    /* Modified by l00301449 for card multi type, 2015-5-25, begin */
    enSimType = TAF_SDC_GetCsimType();
    /* Modified by l00301449 for card multi type, 2015-5-25, end */

    usFileId = 0;

    if (TAF_SDC_SIM_TYPE_CSIM == enSimType)
    {
        usFileId = (VOS_UINT16)USIMM_CSIM_EFDGC_ID;
    }
    else if (TAF_SDC_SIM_TYPE_UIM == enSimType)
    {
        usFileId = (VOS_UINT16)USIMM_CDMA_EFDGC_ID;
    }
    else
    {}

    TAF_COMM_BUILD_USIM_GET_FILE_INFO(&stGetFileInfo,
                                      USIMM_CDMA_APP,
                                      usFileId,
                                      0);

    NAS_USIMMAPI_GetFileReq(WUEPS_PID_TAF, 0, &stGetFileInfo);

    return VOS_TRUE;
}


/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtSetDialModeReq_PreProc
 ��������  :
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��02��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsSetDialModeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CDATA_DIAL_MODE_REQ_STRU    *pstDialModeReq = VOS_NULL_PTR;
    TAF_PS_MSG_STRU                    *pstPsMsg       = VOS_NULL_PTR;

    /* ��ʼ�� */
    pstDialModeReq    = (TAF_PS_CDATA_DIAL_MODE_REQ_STRU *)pstMsg;

    /* ȥ��Ϣͷ, �ظ�AT */
    pstPsMsg          = (TAF_PS_MSG_STRU *)pstMsg;
    pstDialModeReq    = (TAF_PS_CDATA_DIAL_MODE_REQ_STRU *)pstPsMsg->aucContent;

    TAF_APS_SetFsmCtxCdataDialMode(pstDialModeReq->enDialMode);

    /* Added by y00314741 for CDMA Iteration 15, 2015-7-1, begin */
    TAF_APS_SndPppDialModeNotify(pstDialModeReq->stCtrl.usClientId);
    /* Added by y00314741 for CDMA Iteration 15, 2015-7-1, end */

    TAF_APS_SndSetDialModeCnf(&(pstDialModeReq->stCtrl), TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvGetCgmtuValue_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_CGMTU_VALUE_REQ_STRU    *pstCgmtuValueReq = VOS_NULL_PTR;
    VOS_UINT32                          ulMtuValue;

    pstCgmtuValueReq = (TAF_PS_GET_CGMTU_VALUE_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    ulMtuValue       = TAF_APS_GET_CDATA_MTU();

    TAF_APS_SndGetCgmtuValueCnf(&(pstCgmtuValueReq->stCtrl), ulMtuValue);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMma1XServiceStatusInd_PreProc
 ��������  : �յ�ID_MMA_TAF_1X_SERVICE_STATUS_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMma1XServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_TAF_1X_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enOldRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enNewRatType;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstMmaServiceStatusInd = (MMA_TAF_1X_SERVICE_STATUS_IND_STRU*)pstMsg;

    /* ����1X��PS�����״̬��Ϣ */
    TAF_APS_Set1XPsServiceStatus(pstMmaServiceStatusInd->ulExist1XService);

    enOldRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* �ж�syscfg���ã������֧��CDMA��ֱ���˳� */
    if (VOS_TRUE != TAF_SDC_IsConfigCLMode())
    {
        return VOS_TRUE;
    }

    /* ��ӡ��Ϣ����֮ǰ��APS״̬����Ϣ */
    TAF_APS_LogFsmMntnInfo(VOS_NULL_PTR, VOS_NULL_PTR);

    /* ���ֻ֧��1X����ֱ��ȡ1X�ķ���״̬ */
    if (VOS_TRUE == TAF_SDC_Is1xOnlyMode())
    {
        /* 1X��PS��������ʱ��ȡ1X�ķ��� */
        enNewRatType = (pstMmaServiceStatusInd->ulExist1XService ? TAF_APS_RAT_TYPE_1X:TAF_APS_RAT_TYPE_NULL);

        TAF_APS_SetFinishClSearch(VOS_TRUE);
    }
    else
    {
        if ((VOS_TRUE == TAF_APS_GetFinishClSearch())
         && (TAF_APS_RAT_TYPE_NULL == enOldRatType)
         && (VOS_TRUE == pstMmaServiceStatusInd->ulExist1XService))
         {
            /* ֮ǰ���κ�PS�����1X��PS��������ʱ��ȡ1X�ķ��� */
            enNewRatType = TAF_APS_RAT_TYPE_1X;
         }
         else if((TAF_APS_RAT_TYPE_1X == enOldRatType)
              && (VOS_FALSE == pstMmaServiceStatusInd->ulExist1XService))
         {
            /* ֮ǰΪ1X��PS�����1X��PS����񲻿���ʱ��ȡNULL */
            enNewRatType = TAF_APS_RAT_TYPE_NULL;
         }
         else
         {
            /* ���������ȡԭ��¼:NULL false,1x true */
            enNewRatType = TAF_APS_GetCurrPdpEntityRatType();
         }
    }

    /* ����״̬��ʵ����뼼�� */
    TAF_APS_SetCurrPdpEntityRatType(enNewRatType);

    /* ��ӡ��Ϣ����֮���APS״̬����Ϣ */
    TAF_APS_LogFsmMntnInfo(VOS_NULL_PTR, VOS_NULL_PTR);

    /* ģʽû�иı����ٴν���״̬������ */
    if ((enOldRatType == enNewRatType)
     && (TAF_APS_RAT_TYPE_NULL == enNewRatType))
    {
        return VOS_TRUE;
    }

    /* TO DO:Ԥ��������Ehsm����Loc Detach Ind��Ϣ */

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* �����ǰPDPʵ�岻ΪINACTIVE״̬�������ڲ���Ϣ��״̬������ */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   TAF_APS_GetCurrPdpEntityRatType(),
                                                   enOldRatType,
                                                   TAF_APS_GetCurrPdpEntitySimRegStatus(),
                                                   VOS_FALSE);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvMmaCLServiceStatusInd_PreProc
 ��������  : �յ�ID_MMA_TAF_SERVICE_STATUS_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvMmaCLServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_APS_CL_SERVICE_STATUS_IND_STRU *pstMmaServiceStatusInd = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enOldRatType;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enNewRatType;
    VOS_UINT32                          ulExist1XService;
    VOS_UINT8                           ucPdpId;


    /* ��ȡ��Ϣ���� */
    pstMmaServiceStatusInd  = (MMA_APS_CL_SERVICE_STATUS_IND_STRU*)pstMsg;
    ulExist1XService        = TAF_APS_Get1XPsServiceStatus();
    enOldRatType            = TAF_APS_GetCurrPdpEntityRatType();
    enNewRatType            = enOldRatType;

    /* �ж�syscfg���ã������֧��CDMA��ֱ���˳� */
    if (VOS_TRUE != TAF_SDC_IsConfigCLMode())
    {
        return VOS_TRUE;
    }

    /* ��ӡ��Ϣ����֮ǰ��APS״̬����Ϣ */
    TAF_APS_LogFsmMntnInfo(VOS_NULL_PTR, VOS_NULL_PTR);


    TAF_APS_SetFinishClSearch(VOS_TRUE);

    if ((MMA_TAF_CL_STATUS_DO_LTE_NO_SERVICE == pstMmaServiceStatusInd->enClStatus)
     && (VOS_TRUE == ulExist1XService))
    {
        /* DO��LTE��PS����񶼲����ã�1X��PS���������Ҳ��ڴ�绰/����ʱ��ȡ1X�ķ��� */
        if (TAF_APS_CDMA_TC_SUSPENDED != TAF_APS_GET_CDATA_SUSPEND_STATUS())
        {
            enNewRatType = TAF_APS_RAT_TYPE_1X;


        }
    }
    /* DO/LTE���з����޷���ʱ�Ĵ��� */
    else if ((MMA_TAF_CL_STATUS_DO_NO_SERVICE == pstMmaServiceStatusInd->enClStatus)
          || (MMA_TAF_CL_STATUS_LTE_NO_SERVICE == pstMmaServiceStatusInd->enClStatus))
    {
        /* ��ǰ1X�з����յ�DO��LTE�޷��񣬲����½��뼼��ģʽ */
        if ((VOS_TRUE == ulExist1XService)
         && (TAF_APS_CDMA_TC_SUSPENDED != TAF_APS_GET_CDATA_SUSPEND_STATUS()))
        {
            enNewRatType = TAF_APS_RAT_TYPE_1X;
        }
        else
        {
            enNewRatType = TAF_APS_RAT_TYPE_NULL;
        }
    }
    else
    {
        enNewRatType = TAF_APS_ConvertMmaClServiceToApsRatType(pstMmaServiceStatusInd->enClStatus);
    }

    /* ����״̬��ʵ����뼼�� */
    TAF_APS_SetCurrPdpEntityRatType(enNewRatType);

    /* TODO:֪ͨCDS��ǰģʽ�仯 */

    /* ��ӡ��Ϣ����֮���APS״̬����Ϣ */
    TAF_APS_LogFsmMntnInfo(VOS_NULL_PTR, VOS_NULL_PTR);

    /* ģʽû�иı����ٴν���״̬�����������ظ��������������Ϣ */
    if (enOldRatType == enNewRatType)
    {
        return VOS_TRUE;
    }

    for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
    {
        /* �����ǰPDPʵ�岻ΪINACTIVE״̬�������ڲ���Ϣ��״̬������ */
        if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
        {
            (VOS_VOID)TAF_APS_SndInterServiceStatusChangeInd(ucPdpId,
                                                   TAF_APS_GetCurrPdpEntityRatType(),
                                                   enOldRatType,
                                                   TAF_APS_GetCurrPdpEntitySimRegStatus(),
                                                   pstMmaServiceStatusInd->ucIsNewSession);
        }
    }

    return VOS_TRUE;
}


/* Added by y00314741 for CDMA Iteration 11, 2015-4-2, end */

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnActiveInd_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_ACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_IND_STRU     *pstEhsmPdnInd;
    VOS_UINT8                           ucPdpId;
    TAF_CTRL_STRU                       stCtrl;

    pstEhsmPdnInd = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;
    /* MODULE IDĬ������ΪAT */
    stCtrl.ulModuleId   = WUEPS_PID_AT;
    stCtrl.usClientId   = TAF_APS_INVALID_CLIENTID;
    stCtrl.ucOpId       = TAF_APS_INVALID_OPID;

    /* Cid��ֵ��Ч����ֱ�ӷ��� */
    if ( TAF_INVALID_CID == pstEhsmPdnInd->ucCid )
    {
        TAF_WARNING_LOG1(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc:invalid Cid", pstEhsmPdnInd->ucCid);
        return VOS_TRUE;
    }

#if 0
    /* ��������£�����CID������Pdp Id */
    ucPdpId = TAF_APS_GetPdpIdByCid(pstEhsmPdnInd->ucCid);
    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        return VOS_FALSE;
    }
    else
    {
        /* �Զ�Ӧ��ģʽ��, ��Ҫ�����µ�APSʵ�����洢������Ϣ */
        TAF_NORMAL_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, Get PDP ID fail.");
    }
#endif

    /* cidΪ0ʱ����ʾ��Ĭ�ϳ��أ������һ���µ�PDP ID
       client id��op id��ʱ��Ϊ����Чֵ��������������ʱ���ٽ���ˢ�� */
    if (TAF_APS_DEFAULT_CID == pstEhsmPdnInd->ucCid)
    {
        /* ����(PdP Id) */
        if (TAF_APS_ALLOC_PDPID_FAIL == TAF_APS_AllocPdpId(&stCtrl,
                                                           pstEhsmPdnInd->ucCid,
                                                           &ucPdpId))
        {
            /* ���䲻��ʵ�壬��ӡ�쳣����ʱ��Ӧ�÷��䲻��ʵ�� */
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, alloc pdp id fail");
            return VOS_TRUE;
        }
    }
    else
    {
        /* �쳣��Ϣ, ���� */
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvEhsmPdnActInd_PreProc, Abnormal Ehsm CID.");
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnDeactiveInd_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnDeactInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstPdnDeactInd;

    pstPdnDeactInd = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByPndId(pstPdnDeactInd->ucPdnId))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc
 ��������  : �յ�ID_MMA_TAF_SERVICE_STATUS_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��5��11��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU       *pstPdnIratHrpdInd;

    pstPdnIratHrpdInd = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByNsapi(pstPdnIratHrpdInd->ucRabId))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* ��¼��ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* �����״̬������ */
    return VOS_FALSE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnActCnf_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_ACTIVATE_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��19��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;

    pstPdnActCnf = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnActCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnDeactCnf_PreProc
 ��������  : �յ�ID_EHSM_APS_PDN_DEACTIVATE_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnDeactCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstPdnDeactCnf;

    pstPdnDeactCnf = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == TAF_APS_GetPdpIdByCid(pstPdnDeactCnf->ucCid))
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    /* �����״̬������ */
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmReconnCnf_PreProc
 ��������  : �յ�ID_EHSM_APS_RECONN_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32         ulEventType
             struct MsgCB      *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmReconnCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_RECONN_CNF_STRU           *pstReconnCnf;
    VOS_UINT8                           ucPdpId;

    pstReconnCnf = (EHSM_APS_RECONN_CNF_STRU *)pstMsg;
    ucPdpId      = TAF_APS_GetPdpIdByCid(pstReconnCnf->ucCid);

    /* ����Ҳ�����Ӧ��PDP ID����������Ϣ */
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        /* ��������Ϣ */
        return VOS_TRUE;
    }

    if (EHSM_APS_CAUSE_SUCCESS == pstReconnCnf->enCause)
    {
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-15, begin */
        /* ��RLPע����������״̬�Ļص���������ʼ��ʱ */
        CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-15, end */

    }
	
    /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
	
    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvDhcpDnsGetCnf_PreProc
 ��������  : �յ�DHCP��ID_DHCP_APS_GET_DNS_IPV4_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��24��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    DHCP_APS_DNS_IPV4_CNF_STRU         *pstDhcpDnsIpv4Cnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstDhcpDnsIpv4Cnf = (DHCP_APS_DNS_IPV4_CNF_STRU *)pstMsg;

    /* ��ȡNSAPI��Ӧ��APSʵ�� */
    ucPdpId           = TAF_APS_GetPdpIdByNsapi(pstDhcpDnsIpv4Cnf->ucRabId);

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
        pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        TAF_APS_StopTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF,
                          ucPdpId);

        if (VOS_OK             == pstDhcpDnsIpv4Cnf->ulResult)
        {
            /* ����PDPʵ���DNS */
            TAF_APS_UpdateCdataIpv4Dns(pstPdpEntity, pstDhcpDnsIpv4Cnf);
        }
        else
        {
            /* Э��ʧ�ܴ��� */
            TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                               TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV4_FAIL);

            return VOS_TRUE;
        }

        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-9, begin */
        if (APS_ADDR_STATIC_IPV4 == pstPdpEntity->PdpAddr.ucPdpTypeNum)
        {
            /* Э�̽��� */
            pstPdpEntity->ucNeedGetDnsFlg = VOS_FALSE;

            if (TAF_APS_DEFAULT_CID != ucCid)
            {
                /* ���û��ϱ�ACTIVATE_CNF�¼� */
                TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
            }

            return VOS_TRUE;
        }
        else
        {
            /* �����Ipv4Ipv6, �����ñ�IPV4�ı�־λ */
            pstPdpEntity->ucRcvDhcpDnsFlgIpv4 = VOS_TRUE;
        }

         /* ��ǰΪIpv4v6, �� RaInfo*/
        TAF_APS_RcvSequenceProcessDhcpNdclient(ucPdpId, ucCid);
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-9, end */


    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvDhcpDnsIpv4Cnf_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc
 ��������  : �յ�DHCP��ID_DHCP_APS_GET_DNS_IPV6_CNF��Ϣ��Ԥ����
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��24��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    DHCP_APS_DNS_IPV6_CNF_STRU         *pstDhcpDnsIpv6Cnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstDhcpDnsIpv6Cnf = (DHCP_APS_DNS_IPV6_CNF_STRU *)pstMsg;

    /* ��ȡNSAPI��Ӧ��APSʵ�� */
    ucPdpId           = TAF_APS_GetPdpIdByNsapi(pstDhcpDnsIpv6Cnf->ucRabId);

    if (TAF_APS_INVALID_PDPID != ucPdpId)
    {
        ucCid             = TAF_APS_GetPdpEntCurrCid(ucPdpId);
        pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        TAF_APS_StopTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF,
                          ucPdpId);

        if (VOS_OK             == pstDhcpDnsIpv6Cnf->ulResult)
        {
            /* ����PDPʵ���DNS */
            TAF_APS_UpdateCdataIpv6Dns(pstPdpEntity, pstDhcpDnsIpv6Cnf);
        }
        else
        {
            /* Э��ʧ�ܴ��� */
            TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                               TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV6_FAIL);

            return VOS_TRUE;
        }

        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* Ipv4Ipv6, �����ñ�IPV6�ı�־λ
            ��ֻ��IPV6��Э��   */
        pstPdpEntity->ucRcvDhcpDnsFlgIpv6 = VOS_TRUE;

        /* ��ǰΪIpv4 v6, ��Ҫ�жϱ�־λ���������ĸ�������Ϣ�ϱ� ipv4Cnf ipv6Cnf ndclientInd */
        TAF_APS_RcvSequenceProcessDhcpNdclient(ucPdpId, ucCid);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvDhcpDnsIpv6Cnf_PreProc: Can't find PDP ID form RAB ID!");
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterPsServiceModeModifyInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU   *pstInterMsg = VOS_NULL_PTR;
    TAF_APS_RAT_TYPE_ENUM_UINT32                         enPsRatType;
    VOS_UINT8                                            ucPdpId;

    pstInterMsg     = (TAF_PS_CALL_INTER_PS_SERVICE_MODE_MODIFY_IND_STRU *)pstMsg;

    switch (pstInterMsg->enPsOptionType)
    {
        case TAF_APS_INTER_PS_OPTION_DISCONNECTED:
            for (ucPdpId = 0; ucPdpId < TAF_APS_MAX_PDPID; ucPdpId++)
            {
                if (VOS_TRUE == TAF_APS_IsPdpIdValid(ucPdpId))
                {
                    /* ��ǰ�����ڳ��أ�����PSģʽ���ı� */
                    return VOS_TRUE;
                }
            }

            /* ��ǰ��PSҵ�� */
            enPsRatType = TAF_APS_RAT_TYPE_NULL;
            break;

        case TAF_APS_INTER_PS_OPTION_CONNECTED:
        case TAF_APS_INTER_PS_OPTION_SWITCH:

            enPsRatType = TAF_APS_GetCurrPdpEntityRatType();
            break;

        default:
            return VOS_TRUE;
    }

    /* ���õ�ǰPSҵ�����ڵ�ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(enPsRatType);

    /* ֪ͨ�ⲿģ�鵱ǰPSҵ�����ڵ�ģʽ */
    TAF_APS_SndExternalModulePsRatTypeNtf(enPsRatType);

    return VOS_TRUE;
}


/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvSet1xDormantTimer_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtSet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_SET_1X_DORM_TIMER_REQ_STRU  *pstSet1xDormTimerReq = VOS_NULL_PTR;
    VOS_UINT32                          ulSocmDormTimer;
    TAF_PS_CAUSE_ENUM_UINT32            enCause;
    TAF_PS_SET_1X_DORM_TIMER_CNF_STRU   stSet1xDormTimerCnf;

    enCause              = TAF_PS_CAUSE_SUCCESS;
    pstSet1xDormTimerReq = (TAF_PS_SET_1X_DORM_TIMER_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);
    ulSocmDormTimer      = TAF_APS_GetSocmDormantTiLen();

    /* Dormant timer feature is enable, and user cfg value shall not less than SOCM setting  */
    if ((ulSocmDormTimer > 0) && ((pstSet1xDormTimerReq->ucDormantTimer * 100) >= ulSocmDormTimer))
    {
        TAF_APS_SetUserCfgDormTiVal(pstSet1xDormTimerReq->ucDormantTimer * 100);
    }
    else
    {
        enCause       = TAF_PS_CAUSE_INVALID_PARAMETER;
    }

    PS_MEM_SET(&stSet1xDormTimerCnf, 0, sizeof(TAF_PS_SET_1X_DORM_TIMER_CNF_STRU));

    /* ��д��Ϣͷ */
    stSet1xDormTimerCnf.stCtrl  = pstSet1xDormTimerReq->stCtrl;
    stSet1xDormTimerCnf.enCause = enCause;

    /* ����ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF,
                               &stSet1xDormTimerCnf,
                               sizeof(TAF_PS_SET_1X_DORM_TIMER_CNF_STRU));

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtGet1xDormantTimer_PreProc
 ��������  : ��ϢID_MSG_TAF_PS_SET_1X_MAX_NO_DATA_TIME_LEN_REQԤ������
 �������  : ulEventType --- �¼���
             pstMsg      --- ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE    --- ��Ϣ�������
             VOS_FALSE   --- ��Ϣδ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��08��13��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtGet1xDormantTimer_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_GET_1X_DORM_TIMER_REQ_STRU  *pstGet1xDormTimerReq = VOS_NULL_PTR;
    TAF_PS_GET_1X_DORM_TIMER_CNF_STRU   stGet1xDormTimerCnf;

    pstGet1xDormTimerReq = (TAF_PS_GET_1X_DORM_TIMER_REQ_STRU *)TAF_PS_GET_MSG_CONTENT(pstMsg);

    PS_MEM_SET(&stGet1xDormTimerCnf, 0, sizeof(TAF_PS_GET_1X_DORM_TIMER_CNF_STRU));

    /* ��д��Ϣͷ */
    stGet1xDormTimerCnf.stCtrl             = pstGet1xDormTimerReq->stCtrl;
    stGet1xDormTimerCnf.ucSocmDormTiVal    = (VOS_UINT8)(TAF_APS_GetSocmDormantTiLen()/100);
    stGet1xDormTimerCnf.ucUserCfgDormTival = (VOS_UINT8)(TAF_APS_GetUserCfgDormTiVal()/100);

    /* ����ID_EVT_TAF_PS_SET_1X_DORM_TIMER_CNF��Ϣ */
    (VOS_VOID)TAF_APS_SndPsEvt(ID_EVT_TAF_PS_GET_1X_DORM_TIMER_CNF,
                               &stGet1xDormTimerCnf,
                               sizeof(TAF_PS_GET_1X_DORM_TIMER_CNF_STRU));

    return VOS_TRUE;
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
