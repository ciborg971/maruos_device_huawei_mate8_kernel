

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafXpdsFsmMain.h"
#include "TafXpdsSndAt.h"
#include "TafSdcCtx.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsSndInternalMsg.h"
/* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-6 begin */
#include "TafXpdsMntn.h"
/* Added by x00314862 for CDMA XPDS Iteration 2 2015-9-6 end */
#include "TafXpdsCommFunc.h"
#include "TafXpdsFsmMainTbl.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_MAIN_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_UINT32 TAF_XPDS_RcvAtGpsStartReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsReqMsg;
    AT_XPDS_GPS_START_REQ_STRU         *pstStartReq;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    TAF_XPDS_CTRL_INFO_STRU            *pstCtrlInfo;
    XPDS_AT_RESULT_CNF_STRU             stStartCnf;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    /* �ֲ�������ʼ�� */
    pstAtXpdsReqMsg  = (AT_XPDS_MSG_STRU*)pstMsg;

    /* Ĭ�ϻظ�ʧ�� */
    PS_MEM_SET(&stStartCnf, 0x0, sizeof(stStartCnf));
    stStartCnf.enResult = XPDS_AT_RESULT_ERROR;

    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();
    pstCtrlInfo = TAF_XPDS_GetCtrlInfoAddr();

    pstStartReq = (AT_XPDS_GPS_START_REQ_STRU*)(pstAtXpdsReqMsg->aucContent);

    /* ��������ȷ�ظ�ABORT��Ϣ */
    if (TAF_XPDS_INITIAL_BUTT > pstStartReq->enAgpsType)
    {
        pstCagpsCfg->enAgpsType    = pstStartReq->enAgpsType;

        stStartCnf.enResult = XPDS_AT_RESULT_NO_ERROR;

        /* ����Reference Loction���� */
        enSysMode = TAF_SDC_GetSysMode();

        TAF_XPDS_SndCasRefLocReq(enSysMode,
                                 XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);

        /* ��������ʱ��ģʽ */
        pstCtrlInfo->enOrigSysMode = enSysMode;
    }

    TAF_XPDS_SndAtMsg(&pstAtXpdsReqMsg->stAppCtrl,
                      ID_XPDS_AT_GPS_START_CNF,
                      sizeof(stStartCnf),
                      (VOS_UINT8*)&stStartCnf);
    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgMpcAddrReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsReqMsg;
    AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU  *pstMpcAddr;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    XPDS_AT_RESULT_CNF_STRU             stMpcAddrCnf;

    /* �ֲ�������ʼ�� */
    pstAtXpdsReqMsg  = (AT_XPDS_MSG_STRU*)pstMsg;

    pstMpcAddr = (AT_XPDS_GPS_CFG_MPC_ADDR_REQ_STRU*)(pstAtXpdsReqMsg->aucContent);

    /* ��ȡȫ�ֱ�����ַ */
    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    pstCagpsCfg->ulMpcAddr = pstMpcAddr->ulIpAddr;

    pstCagpsCfg->ulMpcPort = pstMpcAddr->usIpPort;

    /* ��Ϣ����ɹ�����AT�ظ��ɹ� */
    PS_MEM_SET(&stMpcAddrCnf, 0x0, sizeof(stMpcAddrCnf));

    stMpcAddrCnf.enResult = VOS_OK;

    TAF_XPDS_SndAtMsg(&pstAtXpdsReqMsg->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MPC_ADDR_CNF,
                     sizeof(stMpcAddrCnf),
                     (VOS_UINT8*)&stMpcAddrCnf);

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPdeAddrReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsReqMsg;
    AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU  *pstPdeAddr;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;
    XPDS_AT_RESULT_CNF_STRU             stPdeAddrCnf;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stPdeAddrCnf, 0x0, sizeof(stPdeAddrCnf));
    stPdeAddrCnf.enResult = VOS_ERR;

    pstAtXpdsReqMsg  = (AT_XPDS_MSG_STRU*)pstMsg;

    pstPdeAddr = (AT_XPDS_GPS_CFG_PDE_ADDR_REQ_STRU*)(pstAtXpdsReqMsg->aucContent);

    if (VOS_FALSE == pstPdeAddr->ucAddrValid)
    {
        TAF_XPDS_SndAtMsg(&pstAtXpdsReqMsg->stAppCtrl,
                         ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,
                         sizeof(stPdeAddrCnf),
                         (VOS_UINT8*)&stPdeAddrCnf);
        return VOS_TRUE;
    }

    /* ��ȡȫ�ֱ�����ַ */
    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    /* IPV4 */
    if (0 == pstPdeAddr->ucIPType)
    {
        pstCagpsCfg->ulPdeAddr = pstPdeAddr->ulIp4Addr;
        pstCagpsCfg->ulPdePort = pstPdeAddr->ulPortNum;

        stPdeAddrCnf.enResult = VOS_OK;
    }

    /* ��Ϣ������ɣ���AT�ظ���� */
    TAF_XPDS_SndAtMsg(&pstAtXpdsReqMsg->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_PDE_ADDR_CNF,
                     sizeof(stPdeAddrCnf),
                     (VOS_UINT8*)&stPdeAddrCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvAtGpsCfgPositionModeReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                            *pstAtXpdsReqMsg;
    AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU      *pstCfgMode;
    TAF_XPDS_CFG_INFO_STRU                      *pstCagpsCfg;
    XPDS_AT_RESULT_CNF_STRU                      stCfgModeCnf;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stCfgModeCnf, 0x0, sizeof(stCfgModeCnf));
    stCfgModeCnf.enResult = VOS_ERR;

    pstAtXpdsReqMsg  = (AT_XPDS_MSG_STRU*)pstMsg;

    /* ������GPS����ͨ����ClientId */
    TAF_XPDS_SetGpsClientId(pstAtXpdsReqMsg->stAppCtrl.usClientId);

    pstCfgMode = (AT_XPDS_GPS_CFG_POSITION_MODE_REQ_STRU*)(pstAtXpdsReqMsg->aucContent);

    /* ��ȡȫ�ֱ�����ַ */
    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    if (TAF_XPDS_CALL_BUTT <= pstCfgMode->enCallType)
    {
        /* ��Ϣ������ɣ���AT�ظ���� */
        TAF_XPDS_SndAtMsg(&pstAtXpdsReqMsg->stAppCtrl,
                         ID_XPDS_AT_GPS_CFG_MODE_CNF,
                         sizeof(stCfgModeCnf),
                         (VOS_UINT8*)&stCfgModeCnf);

        return VOS_TRUE;
    }

    pstCagpsCfg->enCallType = pstCfgMode->enCallType;

    if ((TAF_XPDS_MSA_MODE  == pstCfgMode->enFixMode)
     || (TAF_XPDS_MSB_MODE  == pstCfgMode->enFixMode)
     || (TAF_XPDS_AFLT_MODE == pstCfgMode->enFixMode))
    {
        pstCagpsCfg->enFixMode  = pstCfgMode->enFixMode;
        pstCagpsCfg->ulPrecisionTimerLen = TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO_DEFAULT_TIMER_LEN;
    }
    else
    {
        /* ��Ϣ������ɣ���AT�ظ���� */
        TAF_XPDS_SndAtMsg(&pstAtXpdsReqMsg->stAppCtrl,
                         ID_XPDS_AT_GPS_CFG_MODE_CNF,
                         sizeof(stCfgModeCnf),
                         (VOS_UINT8*)&stCfgModeCnf);

        return VOS_TRUE;
    }

    pstCagpsCfg->usFixNum           = pstCfgMode->usFixNum;
    pstCagpsCfg->ulFixRateTime      = pstCfgMode->ulFixRateTime;
    pstCagpsCfg->ulQosHaccuracy     = pstCfgMode->ulQosHaccuracy;
    pstCagpsCfg->ulQosVaccuracy     = pstCfgMode->ulQosVaccuracy;
    pstCagpsCfg->ulQosPerformance   = pstCfgMode->ulQosPerformance;

    stCfgModeCnf.enResult = VOS_OK;

    /* ��Ϣ������ɣ���AT�ظ���� */
    TAF_XPDS_SndAtMsg(&pstAtXpdsReqMsg->stAppCtrl,
                     ID_XPDS_AT_GPS_CFG_MODE_CNF,
                     sizeof(stCfgModeCnf),
                     (VOS_UINT8*)&stCfgModeCnf);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvAtGpsReplyNiReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsReqMsg;
    AT_XPDS_GPS_REPLY_NI_RSP_STRU      *pstReplyNi;

    /* �ֲ�������ʼ�� */
    pstAtXpdsReqMsg = (AT_XPDS_MSG_STRU*)pstMsg;
    pstReplyNi      = (AT_XPDS_GPS_REPLY_NI_RSP_STRU*)(pstAtXpdsReqMsg->aucContent);

    /* ֹͣ�ȴ�NI�ظ���ʱ�� */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_ANSWER_NI_REQ_CNF);

    /* ������GPS����ͨ����ClientId */
    TAF_XPDS_SetGpsClientId(pstAtXpdsReqMsg->stAppCtrl.usClientId);

    if (AT_XPDS_GPS_NI_REQ_REPLY_RESULT_ACCEPT == pstReplyNi->enReplyResult)
    {
        /* �·���AGPS ^CAGPSSTARTREQ */
        TAF_XPDS_SndAtMsgNoData(&pstAtXpdsReqMsg->stAppCtrl,
                               ID_XPDS_AT_GPS_START_REQ);
    }
    /* reject */
    else if (AT_XPDS_GPS_NI_REQ_REPLY_RESULT_REJECT == pstReplyNi->enReplyResult)
    {
        /* ��Ҫ�ظ�������reject */
        if (AT_XPDS_GPS_NI_REQ_REJECT_TYPE_TIMER_OUT == pstReplyNi->enRejReason)
        {
            (VOS_VOID)TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_POP_UP_SCREEN_TIMER_OUT);
        }
        else
        {
            (VOS_VOID)TAF_XPDS_SndXsmsRejNiPosReq(TAF_XPDS_REJ_POS_REASON_USER_DENIED_REQ);
        }
    }
    else
    {
        ;
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvAtGpsQryTimeInfoReq_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsMsg  = VOS_NULL_PTR;
    TAF_XPDS_CTRL_INFO_STRU            *pstCtrlInfo = VOS_NULL_PTR;

    /* �ֲ�������ʼ�� */
    pstAtXpdsMsg                       = (AT_XPDS_MSG_STRU*)pstMsg;

    pstCtrlInfo = TAF_XPDS_GetCtrlInfoAddr();

    pstCtrlInfo->enSyncTimeActionType = pstAtXpdsMsg->aucContent[0];


    if (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == pstCtrlInfo->enSyncTimeActionType)
    {

        if (TAF_XPDS_USER_PLANE == TAF_XPDS_GetAgpsCfg()->enCallType)
        {
            /* ����һ�л�����λ״̬ */
            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

            /* �����û�����·״̬�� */
            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

            /* �����ڲ���Ϣȥ����MPC��Socket��· */
            TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                                  TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);
        }
        else
        {
            /* ����һ�л�����λ״̬ */
            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

            /* �����û�����·״̬�� */
            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_LINK_CTRL);

            /* send ID_TAF_XPDS_XPDS_CP_LINK_START_REQ for starting the link proc */
            TAF_XPDS_SndControlPlaneLinkStart_CpLinkCtrl();

            TAF_XPDS_SndCasRefLocReq(TAF_SDC_GetSysMode(), XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);
        }

    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvCasPdeDataInd_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰ�յ��������DATA_IND ��Ҫ�л���POSING ��PDE״̬ */

    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstCasDataInd;

    pstCasDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU*)pstMsg;

    if (TAF_XPDS_CTRL_PLANE == pstCasDataInd->enCallType)
    {
        /* �oGPS ����NICPSTART */
        if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
        {
            TAF_XPDS_SndAtGpsCpNiStart();
        }

        TAF_XPDS_SndCasRefLocReq(TAF_SDC_GetSysMode(), XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);

        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_PDE_PROC);

        TAF_XPDS_SndInternalCpPdeProcStartReq();
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvXccIncomingInd_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_POSITIONING);

    TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_LINK_CTRL);

    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsPosInfoRsp_Pos
 ��������  : XPDS����ID_AT_XPDS_POS_INFO_RSP
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��7��16��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsPosInfoRsp_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    AT_XPDS_MSG_STRU                   *pstAtXpdsReqMsg;
    AT_XPDS_GPS_POS_INFO_RSP_STRU      *pstCagpsPosInfoRsp;
    TAF_XPDS_CFG_INFO_STRU             *pstCagpsCfg;

    pstCagpsCfg        = TAF_XPDS_GetAgpsCfg();

    /* �ֲ�������ʼ�� */
    pstAtXpdsReqMsg    = (AT_XPDS_MSG_STRU *)pstMsg;

    pstCagpsPosInfoRsp = (AT_XPDS_GPS_POS_INFO_RSP_STRU*)(pstAtXpdsReqMsg->aucContent);

    PS_MEM_CPY(&(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfoRsp),
               pstCagpsPosInfoRsp,
               sizeof(AT_XPDS_GPS_POS_INFO_RSP_STRU));

    /* NI���ζ�λ��������Ҫ�ϱ���GPSֹͣ */
    if ((TAF_XPDS_NI == pstCagpsCfg->enAgpsType)
     && (1 == pstCagpsCfg->usFixNum))
    {
        TAF_XPDS_SndAtGpsCancelNiSession();
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvCasPdeDataInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰ�յ��������DATA_IND ��Ҫ�л���POSING ��PDE״̬ */

    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstCasDataInd;

    pstCasDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU*)pstMsg;

    if (TAF_XPDS_CTRL_PLANE == pstCasDataInd->enCallType)
    {
        /* Ӧ������Ҫ�ж��ǲ��ǵ�ǰ��·�Ѿ����� */

        /* �oGPS ����NICPSTART */
        if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
        {
            TAF_XPDS_SndAtGpsCpNiStart();
        }

        TAF_XPDS_SndCasRefLocReq(TAF_SDC_GetSysMode(), XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_START);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_PDE_PROC);

        TAF_XPDS_SndInternalCpPdeProcStartReq();
    }

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS);

    return VOS_TRUE;
}
VOS_VOID TAF_XPDS_ProcNiCancelPos(
    TAF_XPDS_POS_PROC_RSLT_ENUM_UINT32  enProcRslt
)
{
    TAF_XPDS_CANCEL_REASON_ENUM_UINT8   enCancelReason;

    /* NI��������Ҫͨ�������ϱ�Cancel */
    if (TAF_XPDS_NI != TAF_XPDS_GetCgpsInitialType())
    {
        return;
    }

    enCancelReason = TAF_XPDS_FindCancelReasonByRslt(enProcRslt);

    if (TAF_XPDS_CANCEL_REASON_BUTT != enCancelReason)
    {
        TAF_XPDS_SndXsmsCancelPosNotify(enCancelReason);

        return;
    }

    return;
}
VOS_VOID TAF_XPDS_ProcAtGpsStopReq(VOS_VOID)
{
    TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enLinkStatus;

    enLinkStatus = TAF_XPDS_GetUpLinkStatus();

    if (TAF_XPDS_UP_LINK_NOT_EXISTED != enLinkStatus)
    {
        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

        /* �����ڲ���Ϣ�Ͽ���· */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);
    }
    else
    {
        /* ֪ͨAP��APN���� */
        TAF_XPDS_SndAtApCloseCagpsDataCall();

        TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
            XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

        /* ����OK */
        TAF_XPDS_SndAtGpsStopCnf();

        /* ��ʼ����λ���ȫ�ֱ��� */
        TAF_XPDS_InitPosCtx();

        /* ��״̬�е�Init̬ */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);
    }

    return;
}
VOS_VOID TAF_XPDS_ProcServerBindRsltSucc_NoLink(VOS_VOID)
{
    TAF_XPDS_CFG_INFO_STRU             *pstAgpsConfig;

    pstAgpsConfig = TAF_XPDS_GetAgpsCfg();

    if (TAF_XPDS_NI == pstAgpsConfig->enAgpsType)
    {
        /* ��ǰΪ��ζ�λ����� */
        if (1 < pstAgpsConfig->usFixNum)
        {
            if (TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum < pstAgpsConfig->usFixNum)
            {
                //�������ڶ�λ��ʱ��
                TAF_XPDS_StartTimer(TI_TAF_XPDS_NI_POS_REPORT_INTERNAL,
                                    TAF_XPDS_GetAgpsCfg()->ulFixRateTime);

                return;
            }

            /* ��������NI Track Session */
            TAF_XPDS_SndAtGpsCancelNiSession();
        }
        else
        {
            if (TAF_XPDS_MSB_MODE != TAF_XPDS_GetAgpsFixMode())
            {
                /* ��������NI Track Session */
                TAF_XPDS_SndAtGpsCancelNiSession();
            }
        }
    }

    /* ��Ϊ�쳣����ʱ��Ҫ������²��� */
    if (TAF_XPDS_PROC_RSLT_SUCC != TAF_XPDS_GetPosProcRslt())
    {
        /* ֪ͨAP��APN���� */
        TAF_XPDS_SndAtApCloseCagpsDataCall();

        TAF_XPDS_SndAtGpsStopCnf();

        /* ��ʼ����λ���ȫ�ֱ��� */
        TAF_XPDS_InitPosCtx();

        TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
                                 XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

        /* ��״̬�е�Init̬ */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);
    }

    return;
}
VOS_VOID TAF_XPDS_ProcServerBindRsltSucc(VOS_VOID)
{
    TAF_XPDS_UP_LINK_STATUS_ENUM_UINT8  enLinkStatus;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enLinkStatus  = TAF_XPDS_GetUpLinkStatus();

    /* MPC���ӳɹ�������MPC״̬�� */
    if (TAF_XPDS_UP_LINK_MPC_CONNECTED == enLinkStatus)
    {
        /* �жϵ�ǰ�Ƿ���Ҫ��ѯTIME */
        if (AT_XPDS_REPLY_SYNC_TIME_AND_ASSIST_DATA == TAF_XPDS_GetCtrlInfoAddr()->enSyncTimeActionType)
        {
            enSysMode = TAF_SDC_GetSysMode();

            TAF_XPDS_SndCasSyncTimeReq(enSysMode);

            TAF_XPDS_GetCtrlInfoAddr()->enSyncTimeActionType = AT_XPDS_REPLY_SYNC_TIME_INFO;
        }

        /* �ڼ�ֻҪMPC�����ɹ�����ֵ��Ҫ��Ϊ0 */
        TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum = 0;

        if (VOS_FALSE == TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc)
        {
            TAF_XPDS_SndInternalStartMpcProcess(TAF_XPDS_MPC_OPER_START_POS_REQ);
        }
        else
        {
            TAF_XPDS_SndInternalStartMpcProcess(TAF_XPDS_MPC_OPER_POS_REPORT);
        }

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_MPC_PROC);

        return;
    }

    /* PDE���ӳɹ�������PDE״̬�� */
    if (TAF_XPDS_UP_LINK_PDE_CONNECTED == enLinkStatus)
    {
        TAF_XPDS_SndInternalPdeProcStartReq(TAF_XPDS_GetAgpsFixMode());

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_PDE_PROC);

        return;
    }

    /* MPC��PDE���Ͽ�����Ҫ��GPS�ظ�OKָʾ */
    if (TAF_XPDS_UP_LINK_NOT_EXISTED == enLinkStatus)
    {
        TAF_XPDS_ProcServerBindRsltSucc_NoLink();
    }

    return;
}
VOS_UINT32 TAF_XPDS_ProcTrackingMpcConnectFail(VOS_VOID)
{
    TAF_XPDS_CFG_INFO_STRU             *pstAgpsConfig;

    pstAgpsConfig = TAF_XPDS_GetAgpsCfg();

    if ((VOS_TRUE != TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc)
     || (TAF_XPDS_NI != pstAgpsConfig->enAgpsType))
    {
        return VOS_ERR;
    }

    /* ��������λ��Ҫ�ϱ�Position report,����������MPC��ʧ�ܣ���abort�쳣 */
    TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum++;

    if (TAF_XPDS_MPC_REPORT_FAIL_MAX_TIMES == TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum)
    {
        XPDS_WARNING_LOG("Failed to send pos report to MPC, and reach max times...");

        return VOS_ERR;
    }

    TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum++;

    if (TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum == pstAgpsConfig->usFixNum)
    {
        XPDS_WARNING_LOG("The time of positioning reach max times...");

        return VOS_ERR;
    }

    TAF_XPDS_SetPosProcRslt(TAF_XPDS_PROC_RSLT_SUCC);

    //����MPCʧ�� ͬ���������ڶ�λ��ʱ��
    TAF_XPDS_StartTimer(TI_TAF_XPDS_NI_POS_REPORT_INTERNAL,
                        pstAgpsConfig->ulFixRateTime);

    return VOS_OK;
}
VOS_VOID TAF_XPDS_RestartPosProc(VOS_VOID)
{
    TAF_XPDS_SetPosProcRslt(TAF_XPDS_PROC_RSLT_SUCC);

    /* ������Ϣ����
      * ���·�����ٶ�λ����
      */
    TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc = VOS_FALSE;
    TAF_XPDS_GetCtrlInfoAddr()->ucPosReportFailNum = 0;
    TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum = 0;

    /* �����ڲ���Ϣȥ����MPC��Socket��· */
    TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                          TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

    TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

    return;
}
VOS_UINT32 TAF_XPDS_RcvXpdsBindServerCnf_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU    *pstBindCnf;

    /* �ж���·��� */
    pstBindCnf = (TAF_XPDS_XPDS_UP_LINK_CTRL_CNF_STRU*)pstMsg;

    /* ����֮ǰ�Ѿ������򲻸��½��ֵ */
    if (TAF_XPDS_PROC_RSLT_SUCC == TAF_XPDS_GetPosProcRslt())
    {
        TAF_XPDS_SetPosProcRslt(pstBindCnf->enRslt);
    }

    /* ����L2 UP link �ظ�Succ����� */
    if (TAF_XPDS_PROC_RSLT_SUCC == pstBindCnf->enRslt)
    {
        TAF_XPDS_ProcServerBindRsltSucc();

        return VOS_TRUE;
    }

    /* PDE��ַ�����仯��Ҫ������λ���� */
    if ((TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH == pstBindCnf->enRslt)
     || (TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE == pstBindCnf->enRslt))
    {
        TAF_XPDS_RestartPosProc();

        return VOS_TRUE;
    }

    /***********************************************************/
    /*         ���´������L2�ظ�ʧ���쳣�Ĵ���                */
    /***********************************************************/

    /* ����ǵ��ζ�λ��PDE����ʧ�ܣ�ֹͣIS 801 session��ʱ�� */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_IS801_SESSION);

    if (TAF_XPDS_PROC_RSLT_UP_MPC_DISCONNECT == pstBindCnf->enRslt)
    {
        if (VOS_OK == TAF_XPDS_ProcTrackingMpcConnectFail())
        {
            return VOS_TRUE;
        }
    }

    /* ͨ�����ֵ����Cancel��Xsms */
    TAF_XPDS_ProcNiCancelPos(pstBindCnf->enRslt);

    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstBindCnf->enRslt)
    {
        TAF_XPDS_ProcAtGpsStopReq();

        return VOS_TRUE;
    }

    /* ֪ͨGPS�쳣 */
    TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_DATA_LINK_ERR);

    return VOS_TRUE;
}


VOS_VOID TAF_XPDS_ProcMpcRsltSucc(VOS_VOID)
{
    if (VOS_FALSE == TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc)
    {
        /* MPC��Ȩ�ɹ�������ȫ�ֱ���ֵ */
        TAF_XPDS_GetCtrlInfoAddr()->ucIsMpcAuthSucc = VOS_TRUE;

        /* MPC��Ȩ�ɹ�֮����һ���Ĳ�����������PDE��������ȡ�������ݣ�������Ҫ��PDE����· */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
    }
    else
    {
        /* Postion report�ɹ��ϱ�MPC����ʱ��Ҫ�Ͽ�MPC��· */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

        TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
    }

    return;
}
VOS_UINT32 TAF_XPDS_RcvXpdsMpcProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU    *pstMpcProcRlst;

    pstMpcProcRlst = (TAF_XPDS_XPDS_INT_MPC_PROC_RSLT_IND_STRU*)pstMsg;

    TAF_XPDS_SetPosProcRslt(pstMpcProcRlst->enMpcOperRslt);

    /* MPC�����ɹ� */
    if (TAF_XPDS_PROC_RSLT_SUCC == pstMpcProcRlst->enMpcOperRslt)
    {
        TAF_XPDS_ProcMpcRsltSucc();

        return VOS_TRUE;
    }

    /* PDE��ַ�����仯��Ҫ������λ���� */
    if ((TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH == pstMpcProcRlst->enMpcOperRslt)
     || (TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE == pstMpcProcRlst->enMpcOperRslt))
    {
        TAF_XPDS_RestartPosProc();

        return VOS_TRUE;
    }

    /* ͨ�����ֵ����Cancel��Xsms */
    TAF_XPDS_ProcNiCancelPos(pstMpcProcRlst->enMpcOperRslt);

    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstMpcProcRlst->enMpcOperRslt)
    {
        TAF_XPDS_ProcAtGpsStopReq();

        return VOS_TRUE;
    }

    /* ֪ͨGPS�쳣 */
    TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_NETWORK_NO_RSP);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvTiPosReportExpired_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* MSB��Ҫ��MPC ServerȥReport Position */
    if (TAF_XPDS_MSB_MODE == TAF_XPDS_GetAgpsFixMode())
    {
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);
    }
    else
    {
        /* MSA or AFLT��Ҫ��PDE����ȥ��ȡλ����Ϣ  */
        TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                              TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET);
    }

    TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvXpdsPdeProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU       *pstPdeProcRlst;
    TAF_XPDS_CFG_INFO_STRU                     *pstCagpsCfg;

    pstCagpsCfg    = TAF_XPDS_GetAgpsCfg();
    pstPdeProcRlst = (TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU*)pstMsg;

    TAF_XPDS_SetPosProcRslt(pstPdeProcRlst->enRslt);

    /* PDE����֮��ֹͣIS 801 session��ʱ�� */
    TAF_XPDS_StopTimer(TI_TAF_XPDS_IS801_SESSION);

    if (TAF_XPDS_PROC_RSLT_SUCC == pstPdeProcRlst->enRslt)
    {
        /* �����NI�����Ͷ�λ����Ҫ�Ͽ�PDE,����MPC������ */
        if ((TAF_XPDS_NI == pstCagpsCfg->enAgpsType)
         && (pstCagpsCfg->usFixNum > 1))
        {
            TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_OPEN_SOCKET,
                                                  TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
        }
        /* AGPS������λ���̿��Խ��� */
        else
        {
            TAF_XPDS_SndInternalServerBindOperReq(TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET,
                                                  TAF_XPDS_SERVER_BIND_OPER_CLOSE_SOCKET);

            TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_LINK_CTRL);
        }

        return VOS_TRUE;
    }

    /* PDE��ַ�����仯��Ҫ������λ���� */
    if ((TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH == pstPdeProcRlst->enRslt)
     || (TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE == pstPdeProcRlst->enRslt))
    {
        TAF_XPDS_RestartPosProc();

        return VOS_TRUE;
    }

    /* ͨ�����ֵ����Cancel��Xsms */
    TAF_XPDS_ProcNiCancelPos(pstPdeProcRlst->enRslt);

    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstPdeProcRlst->enRslt)
    {
        TAF_XPDS_ProcAtGpsStopReq();

        return VOS_TRUE;
    }

    /* ֪ͨGPS�쳣 */
    TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_NETWORK_NO_RSP);

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvXpdsAbnormalAbortAgpsSessionInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortMsg;
    TAF_XPDS_CFG_INFO_STRU                                 *pstCagpsCfg;
    VOS_UINT16                                              usCurFixNum;

    pstCagpsCfg = TAF_XPDS_GetAgpsCfg();

    pstAbortMsg = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU*)pstMsg;

    /* ֻ�����������̽�����Ŵ��� */
    if (TAF_XPDS_PROC_RSLT_SUCC == TAF_XPDS_GetPosProcRslt())
    {
        TAF_XPDS_SetPosProcRslt(pstAbortMsg->enAbortScene);

        usCurFixNum = TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum;

        /* ���統ǰΪ�����Ͷ�λ����Ҫ֪ͨGPS�ж϶�λ���� */
        if ((1 < pstCagpsCfg->usFixNum)
         && (pstCagpsCfg->usFixNum > usCurFixNum))
        {
            /* ͨ�����ֵ����Cancel��Xsms */
            TAF_XPDS_ProcNiCancelPos(pstAbortMsg->enAbortScene);

            /* �����쳣������Ҫ֪ͨGPS */
            if (TAF_XPDS_PROC_RSLT_AT_STOP != pstAbortMsg->enAbortScene)
            {
                /* ֪ͨGPS�쳣 */
                TAF_XPDS_SndAtGpsAbortPosInd(XPDS_AT_ABORT_POS_REASON_ENUM_NETWORK_NO_RSP);
            }
        }
    }

    /* ����ΪGPS������STOP��Ϣ��Ҫ�������д��� */
    if (TAF_XPDS_PROC_RSLT_AT_STOP == pstAbortMsg->enAbortScene)
    {
        TAF_XPDS_ProcAtGpsStopReq();
    }

    return VOS_TRUE;
}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvCpXpdsPdeProcRsltInd_Pos
 Description  : The handling of Cp pde operation result

  History       :
  1.Date        :   11-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCpXpdsPdeProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU       *pstPdeProcRlst;

    pstPdeProcRlst = (TAF_XPDS_XPDS_PDE_PROC_RSLT_IND_STRU*)pstMsg;

    TAF_XPDS_SetPosProcRslt(pstPdeProcRlst->enRslt);

    /* send the GPS Cp stop */
    if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
    {
        TAF_XPDS_SndAtGpsCpNiStop();
    }

    TAF_XPDS_SndCasRefLocReq(TAF_SDC_GetSysMode(),
                         XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

    /* ��ʼ����λ���ȫ�ֱ��� */
    TAF_XPDS_InitPosCtx();

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);

    return VOS_TRUE;

}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvCpXpdsLinkProcRsltInd_Pos
 Description  : The handling of Cp link operation result

  History       :
  1.Date        :   11-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvCpXpdsLinkProcRsltInd_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU   *pstCpLinkRslt;

    pstCpLinkRslt = (TAF_XPDS_XPDS_CP_LINK_PROC_RSLT_IND_STRU *)pstMsg;

    switch (pstCpLinkRslt->enRslt)
    {
        case TAF_XPDS_PROC_RSLT_SUCC:
            if (TAF_XPDS_SI == TAF_XPDS_GetAgpsCfg()->enAgpsType)
            {
                TAF_XPDS_InitFsmL2(TAF_XPDS_FSM_CP_PDE_PROC);
                TAF_XPDS_SndInternalCpPdeProcStartReq();
            }
            else
            {
                /* start the timer for wait data ind */
                TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS,
                                    TI_TAF_XPDS_WAIT_CAS_DATA_IND_L1_POS_TIMER_LEN);
            }
            break;

        case TAF_XPDS_PDE_PROC_RSLT_FAIL:
        case TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT:

            /* ��ʼ����λ���ȫ�ֱ��� */
            TAF_XPDS_InitPosCtx();

            TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
                                     XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);

            break;

        default:
            XPDS_ERROR_LOG("TAF_XPDS_RcvCpXpdsLinkProcRsltInd_Pos: Incorrect parameter.");
            break;
    }

    return VOS_TRUE;

}

/*****************************************************************************
 Func Name    : TAF_XPDS_RcvTiDataIndWaitExpired_Pos
 Description  : The handling of cas data ind wait timer expiry

  History       :
  1.Date        :   11-09-2015
    Author      :   Arjun A00903922
    Modification:   Created function
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiDataIndWaitExpired_Pos(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_InitPosCtx();

    TAF_XPDS_SndCasRefLocReq(TAF_XPDS_GetCtrlInfoAddr()->enOrigSysMode,
                             XPDS_CAS_REF_LOC_RPT_TYPE_ENUM_STOP);

    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L1_STA_INIT);

    return VOS_TRUE;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

