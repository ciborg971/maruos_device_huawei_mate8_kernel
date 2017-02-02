

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafMtaMain.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmMpcProc.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsSndXsms.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_MPC_PROC_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_UINT32 TAF_XPDS_RcvMpcOperationReqMsg_MpcProc_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU              *pstStartReq;

    pstStartReq = (TAF_XPDS_XPDS_INT_MPC_PROC_START_REQ_STRU*)pstMsg;

    TAF_XPDS_SaveCurEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��Ҫ����START POS REQ */
    if (TAF_XPDS_MPC_OPER_START_POS_REQ == pstStartReq->enMpcOperation)
    {
        TAF_XPDS_SndAtApMpcStartPosReq();

        TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_MPC_START_POS_RSP, TI_TAF_XPDS_WAIT_MPC_START_POS_RSP_TIMER_LEN);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_MPC_PROC_STA_WAIT_START_POS_RESP);
    }
    else if (TAF_XPDS_MPC_OPER_POS_REPORT == pstStartReq->enMpcOperation)
    {
        /* ����ϱ�Pos Report��MPC��������������ʱ�Ѿ�Fix�����λ�ã���ǰFixNum������Ҫ�ۼ� */
        TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum++;

        TAF_XPDS_SndAtApMpcPosReportReq();

        TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP, TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP_TIMER_LEN);

        /* �����ǰ��Ҫ����POS_REPORT */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_MPC_PROC_STA_WAIT_POS_REPORT_RESP);
    }
    else
    {
        /* �������� */
        TAF_XPDS_QuitFsmL2();

        TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_BUTT, TAF_XPDS_PDE_PROC_RSLT_FAIL);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvMpcStartPosResp_MpcProc_WaitStartPosResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����RESP��ԭ��ֵ���д��� */
    TAF_XPDS_MPC_START_POS_RSP_STRU    *pstStartResp;
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enMpcRslt = TAF_XPDS_PROC_RSLT_BUTT;

    pstStartResp = (TAF_XPDS_MPC_START_POS_RSP_STRU*)pstMsg;

    TAF_MTA_StopTimer(TI_TAF_XPDS_WAIT_MPC_START_POS_RSP);

    /* ��Ϣ�洢 */
    PS_MEM_CPY(&(TAF_XPDS_GetMpcCtxAddr()->stStartPosRsp),
               pstStartResp,
               sizeof(TAF_XPDS_MPC_START_POS_RSP_STRU));

    /* ���ݲ�ͬ��ԭ��ֵ���д��� */
    switch (pstStartResp->enPosStatusInd)
    {
        case TAF_XPDS_POS_STATUS_INDICATOR_USE_GPSONE:

            enMpcRslt = TAF_XPDS_PROC_RSLT_SUCC;

            break;

        case TAF_XPDS_POS_STATUS_INDICATOR_CACHED_POS:
        case TAF_XPDS_POS_STATUS_INDICATOR_WITH_CELL_SECTOR:

            enMpcRslt = TAF_XPDS_MPC_OPER_RSLT_POS_TECH_CHANGED;

            break;

        case TAF_XPDS_POS_STATUS_INDICATOR_REQ_NOT_AUTH:
        case TAF_XPDS_POS_STATUS_INDICATOR_MPC_REFUSED:
        case TAF_XPDS_POS_STATUS_INDICATOR_SRV_UNAVAILABLE:
        case TAF_XPDS_POS_STATUS_INDICATOR_CANCEL_FIX_REQ:

            enMpcRslt = TAF_XPDS_PDE_PROC_RSLT_FAIL;

            break;

        case TAF_XPDS_POS_STATUS_INDICATOR_ACK_REQ_NO_ACTION:
            /* ����UE��˵��Ĭ�ϵĶ�λ������GPSONE ���Իظ�����Ҫ��һ�������ǲ��Ե� */
            enMpcRslt = TAF_XPDS_PDE_PROC_RSLT_FAIL;
            break;

        default:
            enMpcRslt = TAF_XPDS_PDE_PROC_RSLT_FAIL;
            break;

    }

    /* �����������ͽoL1״̬�� */

    TAF_XPDS_QuitFsmL2();

    /*
      ����ǵ��ζ�λ������IS 801�Ự��ʱ��

      �й���������
      LBS-05012  [��ѡ]   ��������λ����
      6�� ����������һ�����ζ�λʱ��
          �ն����յ� Start Positioning Process Response��Ϣ��Ӧ����һ����ʱ�� T8

      �ǵ�������λҲҪ����T8��ʱ��:
      �� A-1�� WAP/WEB ��λӦ���еĶ�ʱ��ֵ
      Timer  Default value (sec)  Set at  Description                              Action on expiration
      T8     32                   MS      ���յ�SPPRes ����� IS-801 �Ự�Ķ�ʱ��  �� CP ������λ����Ϣ�ĵڶ���WAP/WEB ҵ������
    */
    if ((1 == TAF_XPDS_GetAgpsCfg()->usFixNum)
     && (TAF_XPDS_PROC_RSLT_SUCC == enMpcRslt))
    {
        TAF_XPDS_StartTimer(TI_TAF_XPDS_IS801_SESSION, TI_TAF_XPDS_IS801_SESSION_TIMER_LEN);
    }

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_START_POS_REQ, enMpcRslt);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvTiStartPosRespExperied_MpcProc_WaitStartPosResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �ȴ���ʱ�Ĵ��� */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_START_POS_REQ, TAF_XPDS_MPC_PROC_RSLT_TIMER_OUT);

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvMpcPosReportResp_MpcProc_WaitPosReportResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32                      enPosRslt;
    TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU         *pstPosReportResp;
    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-6 begin */
    TAF_XPDS_CFG_INFO_STRU                                 *pstCagpsConfigInfo;

    pstCagpsConfigInfo = TAF_XPDS_GetAgpsCfg();
    /* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-6 end */

    pstPosReportResp  = (TAF_XPDS_XPDS_INT_RCV_MPC_POS_REPORT_RESP_STRU*)pstMsg;

    TAF_MTA_StopTimer(TI_TAF_XPDS_WAIT_MPC_POS_REPORT_RSP);

    switch (pstPosReportResp->stPosReportRsp.enReportStatus)
    {
        case TAF_XPDS_MPC_REPORT_STATUS_INDICATOR_ACK:
            enPosRslt = TAF_XPDS_PROC_RSLT_SUCC;
            break;

        case TAF_XPDS_MPC_REPORT_STATUS_DISCON_REPORT:
            enPosRslt = TAF_XPDS_MPC_OPER_RSLT_DISCON_REPORT;
            break;

        case TAF_XPDS_MPC_REPORT_STATUS_PDE_HANDOFF:
            enPosRslt = TAF_XPDS_MPC_OPER_RSLT_PDE_HANDOFF;
            /* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-6 begin */
            pstCagpsConfigInfo->ulPdeAddr = TAF_XPDS_GetMpcCtxAddr()->stPosReportRsp.stPdeAddr.ulPdeIpAddr;
            pstCagpsConfigInfo->ulPdePort = TAF_XPDS_GetMpcCtxAddr()->stPosReportRsp.stPdeAddr.usPdePortNum;

            /* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-6 end */
            break;

        default:
            enPosRslt = TAF_XPDS_PROC_RSLT_SUCC;
            break;

    }

    /* ����RESP��ԭ��ֵ���д��� */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_POS_REPORT, enPosRslt);
    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvTiPosReportExperied_MpcProc_WaitStartPosResp(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �ȴ���ʱ�Ĵ��� */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_POS_REPORT, TAF_XPDS_MPC_PROC_RSLT_TIMER_OUT);
    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvXpdsAbortInd_MpcProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortInd;

    pstAbortInd = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU*)pstMsg;

    if (TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT == pstAbortInd->enAbortScene)
    {
        return VOS_TRUE;
    }

    /* �ȴ���ʱ�Ĵ��� */
    TAF_XPDS_QuitFsmL2();

    TAF_XPDS_SndInternalMpcRslt(TAF_XPDS_MPC_OPER_BUTT, pstAbortInd->enAbortScene);

    return VOS_TRUE;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */









