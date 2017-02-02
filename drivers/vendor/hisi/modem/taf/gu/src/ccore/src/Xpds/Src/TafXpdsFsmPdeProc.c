

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafXpdsCtx.h"
#include "TafXpdsSndInternalMsg.h"
#include "TafXpdsFsmPdeProc.h"
#include "TafXpdsFsmPdeProcComm.h"
#include "TafXpdsMntn.h"
#include "TafXpdsSndAt.h"
#include "TafXpdsSndCas.h"
#include "TafXpdsSndXsms.h"
#include "TafXpdsCommFunc.h"
#include "TafXpdsFsmPdeProcTbl.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_FSM_PDE_PROC_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 Global variable
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_UINT32 TAF_XPDS_RcvXpdsPdeProcStartReq_L2Pde_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU                  *pstPdeProcStartReq = VOS_NULL_PTR;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    pstPdeProcStartReq = (TAF_XPDS_XPDS_PDE_PROC_START_REQ_STRU *)pstMsg;

    TAF_XPDS_MNTN_TraceSessionBeginIndMsg();

    switch (pstPdeProcStartReq->enFixMode)
    {
        case TAF_XPDS_MSA_MODE:
        case TAF_XPDS_AFLT_MODE:
            TAF_XPDS_InitPdePublicDataPdeInit();

            TAF_XPDS_SndPdeStartDeliverData_L2Pde();

            /* ���㷽�� */
            TAF_XPDS_UpdatePpmInGlobal();

            stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;
            stEncodeRlInfo.ucNumOfReq    = 1;
            stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
            stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
            stEncodeRlInfo.ucNumOfResp   = 2;

            (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

            TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_ASSIST_INFO);

            break;

        case TAF_XPDS_MSB_MODE:
            TAF_XPDS_InitPdePublicDataPdeInit();

            TAF_XPDS_SndPdeStartDeliverData_L2Pde();

            /* ���㷽�� */
            TAF_XPDS_UpdatePpmInGlobal();

            stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
            stEncodeRlInfo.aucReqType[1] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ALM;
            stEncodeRlInfo.aucReqType[2] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_EPH;
            stEncodeRlInfo.ucNumOfReq    = 3;

            stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
            stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
            stEncodeRlInfo.ucNumOfResp   = 2;

            TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

            /* ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSB_WAIT_PDE_DATA */
            TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSB_WAIT_PDE_DATA);

            /* ����������ʱ�� */
            (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_MSB_DATA,
                                          TI_TAF_XPDS_WAIT_PDE_MSB_DATA_TIMER_LEN);

            break;

        default:
            XPDS_WARNING_LOG("TAF_XPDS_RcvXpdsPdeProcStartReq_L2Pde_Init: wrong agps fix mode!");
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo
 ��������  : MSA_WAIT_PDE_ASSIST_INFO״̬�յ�ID_TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* ���PDE��Ϣ���·��������а���reject��Ϣ��������λ���̣��˳�L2 PDE״̬�� */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();

        return VOS_TRUE;
    }

    TAF_XPDS_ProcReqFromPde_L2Pde(pstPdeDataInd->ulDataMask, TAF_XPDS_USER_PLANE);

    /* �ж��Ƿ����Assist Info */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_ACQ_ASSIST)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_ACQ_ASSIST & pstPdeDataInd->ulDataMask))
    {
        /* ����Assit Info */
        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF);

        /* before send acq assist to gps ,trace assist ctx first */
        TAF_XPDS_MNTN_TraceAssistDataCtxIndMsg();

        /* send assist data to gps, ��GPS��ȡα����Ϣ  */
        TAF_XPDS_SndAtGpsAcqAssistData();

        /* ���Ȳ��Զ�ʱ�����Ȳ�Ϊ0ʱ����������������� */
        if (0 != TAF_XPDS_GetAgpsCfg()->ulPrecisionTimerLen)
        {
            TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO,
                                TAF_XPDS_GetAgpsCfg()->ulPrecisionTimerLen);
        }
        /* Quality��ʱ��Ҳû�б�������������һ��������ʱ��*/
        else if (TAF_XPDS_TIMER_STATUS_STOP == TAF_XPDS_GetTimerStatus(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY))
        {
            TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF,
                                TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF_TIMER_LEN);
        }
        else
        {
        }

        /* TODO: ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_GPS_PSEUDO_INFO);
    }
    else
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeAssistInfo: no assist info rsp...");
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvTiXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeAssistInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);

    TAF_XPDS_ProcQuitL2Pde_L2Pde();

    return VOS_TRUE;
}


VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* ���PDE��Ϣ���·��������а���reject��Ϣ��������λ���̣��˳�L2 PDE״̬�� */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtGpsPrmInfoRsp_L2Pde_MsaWaitGpsPseudoInfo
 ��������  : MSA_WAIT_GPS_PSEUDO_INFO״̬�յ�ID_AT_XPDS_GPS_PRM_INFO_RSP��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvAtGpsPrmInfoRsp_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* TODO: ���͵�Ƶ��λ������Ϣ��α����Ϣ��PDE������ */
    AT_XPDS_MSG_STRU                                       *pstAtXpdsMsg;
    AT_XPDS_GPS_PRM_INFO_RSP_STRU                          *pstPrmInfo;
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;
    VOS_UINT8                                               ucLoopCount;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

    pstAtXpdsMsg  = (AT_XPDS_MSG_STRU*)pstMsg;

    pstPrmInfo = (AT_XPDS_GPS_PRM_INFO_RSP_STRU*)(pstAtXpdsMsg->aucContent);

    /* ��Ϣ��Ч */
    if (VOS_FALSE == pstPrmInfo->ucPrmValid)
    {
        return VOS_TRUE;
    }

    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    PS_MEM_SET(pstPseuMeas, 0, sizeof(TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU));

    pstPseuMeas->ucPartNum    = 0;
    pstPseuMeas->ucTotalparts = 0;

    if ((pstPrmInfo->ucMeasNum > 0)
     && (pstPrmInfo->ucMeasNum <= TAF_MSG_CDMA_MAX_SV_NUM))
    {
        pstPseuMeas->ucNumOfPS    = pstPrmInfo->ucMeasNum - 1;  /* Э��涨���͸�����ʱ��1 */
    }

    pstPseuMeas->ulTimeRef    = pstPrmInfo->ulMeasTow % 14400000; /* 4Сʱ��λ */
    pstPseuMeas->ucTimeRefSrc = 1;    /* 01 GPS time reference */

    /* ��ȫ�ֱ����л��ʹ�õ�ֵ */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

    for (ucLoopCount = 0; ucLoopCount < pstPrmInfo->ucMeasNum; ucLoopCount++)
    {
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucSvPRNNum      = pstPrmInfo->astMseasData[ucLoopCount].ucSvId;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucSvCNO         = pstPrmInfo->astMseasData[ucLoopCount].ucSvCn0;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].sPsDoppler      = pstPrmInfo->astMseasData[ucLoopCount].sPsDopp;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].usSvCodePhWh    = pstPrmInfo->astMseasData[ucLoopCount].usSvCodePhWhole;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].usSvCodePhFr    = pstPrmInfo->astMseasData[ucLoopCount].usSvCodePhFract;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucMulPathInd    = pstPrmInfo->astMseasData[ucLoopCount].ucMulpathInd;
        pstPseuMeas->astPsuedoInfo[ucLoopCount].ucPsRangeRmsEr  = pstPrmInfo->astMseasData[ucLoopCount].ucPsRmsErr;
    }

    TAF_XPDS_GetPdePublicData()->ucIsReceivedGpsPrmInfo = VOS_TRUE;

    if (TAF_XPDS_TIMER_STATUS_RUNING != TAF_XPDS_GetTimerStatus(TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO))
    {
        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY);

        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_PSEUDORANGE_CNF);

        /* ���㷽�� */
        TAF_XPDS_UpdatePpmInGlobal();

        /* �ظ������������ */
        stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
        stEncodeRlInfo.ucNumOfReq    = 1;

        stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
        stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 2;

        /* Before send msg to PDE, hook current Pseu Range Ctx info */
        TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

        /* ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
        TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvAtPrmInfoRspExpired_L2Pde_MsaWaitGpsPseudoInfo
 ��������  : MSA_WAIT_GPS_PSEUDO_INFO״̬�յ���ʱ����ʱ��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiPrmInfoRspExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* ���͵�Ƶ��λ������Ϣ��α����Ϣ��PDE������ */
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));
    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);

    /* ��ȫ�ֱ����л��ʹ�õ�ֵ */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

     /* ���㷽�� */
    TAF_XPDS_UpdatePpmInGlobal();

    /* �ظ������������ */
    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
    stEncodeRlInfo.ucNumOfReq    = 1;

    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 1;

    if (VOS_TRUE == TAF_XPDS_GetPdePublicData()->ucIsReceivedGpsPrmInfo)
    {
        stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 2;
    }

    /* Before send msg to PDE, hook current Pseu Range Ctx info */
    TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_GPS_PRECISION_PSEUDORANGE_INFO);

    /* ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvTiWaitGpsPrecisionPseudoRangeExpired_L2Pde_MsaWaitGpsPseudoInfo
 ��������  : MSA_WAIT_GPS_PSEUDO_INFO״̬�յ���ʱ����ʱ��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitGpsPrecisionPseudoRangeExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                           ulEventType,
    struct MsgCB                        *pstMsg
)
{
     /* TODO: ���͵�Ƶ��λ������Ϣ��α����Ϣ��PDE������ */
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY);

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));
    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);


    /* ��ȫ�ֱ����л��ʹ�õ�ֵ */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

    /* ���㷽�� */
    TAF_XPDS_UpdatePpmInGlobal();

    /* �ظ������������ */
    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
    stEncodeRlInfo.ucNumOfReq    = 1;

    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 1;

    if (VOS_TRUE == TAF_XPDS_GetPdePublicData()->ucIsReceivedGpsPrmInfo)
    {
        stEncodeRlInfo.aucRspType[1] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PSUEDORANG_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 2;
    }

    /* Before send msg to PDE, hook current Pseu Range Ctx info */
    TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

    /* ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvTiWaitGpsPseudoRangeCnfExpired_L2Pde_MsaWaitGpsPseudoInfo
 ��������  : MSA_WAIT_GPS_PSEUDO_INFO״̬�յ���ʱ����ʱ��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiWaitGpsPseudoRangeCnfExpired_L2Pde_MsaWaitGpsPseudoInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
     /* TODO: ���͵�Ƶ��λ������Ϣ��α����Ϣ��PDE������ */
    TAF_XPDS_REVLINK_RSP_PSEU_RANGE_MEAS_STRU              *pstPseuMeas;
    TAF_XPDS_REVLINK_RSP_PILOT_PHASE_MEAS_STRU             *pstPilotMeas;
    TAF_XPDS_ENCODE_RL_INFO_STRU                            stEncodeRlInfo;

    /* �ֲ�������ʼ�� */
    PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));
    pstPseuMeas  = &(TAF_XPDS_GetPdePublicData()->stRspPrmInfo);
    pstPilotMeas = &(TAF_XPDS_GetPublicDataAddr()->stPilotInfo);


    /* ��ȫ�ֱ����л��ʹ�õ�ֵ */
    pstPseuMeas->ucOffsetIncl       = 1;
    pstPseuMeas->usRefPN            = pstPilotMeas->usRefPn;
    pstPseuMeas->sMobileSysOffset   = pstPilotMeas->sMobSysTOffst;

    /* ���㷽�� */
    TAF_XPDS_UpdatePpmInGlobal();

    /* �ظ������������ */
    stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_LOC_RSP;
    stEncodeRlInfo.ucNumOfReq    = 1;

    stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
    stEncodeRlInfo.ucNumOfResp   = 1;

    /* Before send msg to PDE, hook current Pseu Range Ctx info */
    TAF_XPDS_MNTN_TracePseuRangeInfoCtxIndMsg();

    TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, TAF_XPDS_USER_PLANE);

    (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

    /* ״̬Ǩ�Ƶ�: TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RESP */
    TAF_XPDS_SetCurrFsmState(TAF_XPDS_L2_PDE_PROC_STA_MSA_WAIT_PDE_LOC_RSP);

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeLocRespInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* ���PDE��Ϣ���·��������а���reject��Ϣ��������λ���̣��˳�L2 PDE״̬�� */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();

        return VOS_TRUE;
    }

    TAF_XPDS_ProcReqFromPde_L2Pde(pstPdeDataInd->ulDataMask, TAF_XPDS_USER_PLANE);

    /* �ж��Ƿ����Assist Info */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP & pstPdeDataInd->ulDataMask)
    {

        TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF);

        /* before send locationg to gps , trace locationg ctx first */
        TAF_XPDS_MNTN_TraceLocationInfoCtxIndMsg();

        TAF_XPDS_ProcPdeLocationRsp_L2Pde();

        /* send internal result cnf msg to main FSM */
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }
    else
    {
        XPDS_ERROR_LOG("TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsaWaitPdeLocRespInfo: no location rsp...");
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_RcvXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitLocRespInfo
 ��������  : MSA_WAIT_PDE_LOC_RSP״̬�յ���ʱ����ʱ��Ϣ������
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_UINT32 TAF_XPDS_RcvTiXpdsForwardPdeDataIndExpired_L2Pde_MsaWaitPdeLocRespInfo(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);

    TAF_XPDS_ProcQuitL2Pde_L2Pde();

    return VOS_TRUE;
}



VOS_UINT32 TAF_XPDS_RcvXpdsForwardPdeDataInd_L2Pde_MsbWaitPdeData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU                *pstPdeDataInd = VOS_NULL_PTR;

    pstPdeDataInd = (TAF_XPDS_XPDS_FORWARD_PDE_DATA_IND_STRU *)pstMsg;

    /* ���PDE��Ϣ���·��������а���reject��Ϣ��������λ���̣��˳�L2 PDE״̬�� */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_REJECT & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_PDE_REJECT);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();

        return VOS_TRUE;
    }

    /* �ж��Ƿ����EPH���� */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_EPH & pstPdeDataInd->ulDataMask))
    {
        /* ����EPH���� */
        TAF_XPDS_ProcEphData_L2Pde_MsbWaitPdeData();
    }

    /* �ж��Ƿ����ALM���� */
    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_GPS_ALM & pstPdeDataInd->ulDataMask))
    {
        /* ����ALM���� */
        TAF_XPDS_ProcAlmData_L2Pde_MsbWaitPdeData();
    }

    if (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP
            == (TAF_XPDS_RCV_PDE_DATA_MASK_RSP_PROV_LOC_RSP & pstPdeDataInd->ulDataMask))
    {
        TAF_XPDS_SndAtGpsPositionInfo();
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_XPDS_RcvTiWaitPdeMsbDataExpired_L2Pde_MsbWaitPdeData(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph = VOS_NULL_PTR;
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU  *pstProvAlm = VOS_NULL_PTR;

    pstProvEph = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);
    pstProvAlm = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);

    /* ���EPH��ALM���ݰ�����Ŀ��Ϊ0����Ϊ������Ч�����س�ʱ��
       ������Ϊ������Ч�����سɹ�
    */
    if ((0 == pstProvEph->ucNumOfSvP) && (0 == pstProvAlm->ucNumOfSvP))
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PDE_PROC_RSLT_TIMER_OUT);
    }
    else
    {
        /* ���û����GPS����EPH���ݣ����� */
        if (VOS_FALSE == TAF_XPDS_GetGpsEphDataFinishedFlag())
        {
            if (VOS_TRUE == TAF_XPDS_GetRespGpsIonInEphimFlag())
            {
                TAF_XPDS_SndAtGpsIonInfo();
                TAF_XPDS_SetRespGpsIonInEphimFlag(VOS_FALSE);
            }

            TAF_XPDS_SndAtGpsEphInfo();
        }

        /* ���û����GPS����ALM���ݣ����� */
        if (VOS_FALSE == TAF_XPDS_GetGpsAlmDataFinishedFlag())
        {
            TAF_XPDS_SndAtGpsAlmInfo();
        }

        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);
    }

    TAF_XPDS_ProcQuitL2Pde_L2Pde();

    return VOS_TRUE;
}



VOS_UINT32 TAF_XPDS_RcvXpdsAbnormalAbortSessionInd_L2Pde(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *pstAbortIndMsg;

    pstAbortIndMsg = (TAF_XPDS_XPDS_INT_ABNORMAL_ABORT_AGPS_SESSION_IND_STRU *)(pstMsg);

    switch (pstAbortIndMsg->enAbortScene)
    {
        case TAF_XPDS_PROC_RSLT_AT_STOP:
        case TAF_XPDS_PROC_RSLT_XSMS_NI_CANCEL:
        case TAF_XPDS_PROC_RSLT_XSMS_SI_CANCEL:
        case TAF_XPDS_PROC_RSLT_XSMS_SI_REFRESH:
        case TAF_XPDS_PROC_RSLT_XSMS_SI_LONGINACTIVE:
        case TAF_XPDS_PROC_RSLT_UP_PDE_DISCONNECT:
        case TAF_XPDS_PROC_RSLT_IS801_TIMEOUT:
            TAF_XPDS_SndInternalPdeProcRsltInd(pstAbortIndMsg->enAbortScene);

            TAF_XPDS_ProcQuitL2Pde_L2Pde();
            break;

        default:
            break;
    }

    return VOS_TRUE;
}


/*****************************************************************************
 �� �� ��  : TAF_XPDS_ProcReqFromPde_L2Pde
 ��������  : ����PDE����������Ϣ
 �������  : ulEventType - ��Ϣ����
             pstMsg      - ��Ϣ����
 �������  : ��
 �� �� ֵ  : VOS_TRUE  - �Ѵ���
             VOS_FALSE - δ����
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��8��27��
    ��    ��   : x00314862
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID TAF_XPDS_ProcReqFromPde_L2Pde
(
    VOS_UINT32                          ulDataMask,
    TAF_XPDS_CALL_TYPE_ENUM_UINT8       enCallType
)
{
    TAF_XPDS_ENCODE_RL_INFO_STRU        stEncodeRlInfo;
    VOS_UINT32                          ulTimerLen;

    /* in order to provide psuedo range measurement, first need to request for aquisition asssitance request to PDE */
    if ((TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PSEURANGE_MEAS)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PSEURANGE_MEAS & ulDataMask))
    {
        PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

        stEncodeRlInfo.aucReqType[0] = TAF_XPDS_RL_MSGTYPE_REQ_GPS_ACQ_ASSIST;
        stEncodeRlInfo.ucNumOfReq    = 1;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, enCallType);

        (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF, TI_TAF_XPDS_WAIT_PDE_CNF_TIMER_LEN);

        ulTimerLen = TAF_XPDS_GetPrmTimerLimitLen();

        if (0 != ulTimerLen)
        {
            (VOS_VOID)TAF_XPDS_StartTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY, ulTimerLen);
        }
    }

    if ((TAF_XPDS_RCV_PDE_DATA_MASK_REQ_MS_INFO)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_REQ_MS_INFO & ulDataMask))
    {
        PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

        stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_MS_INFO;
        stEncodeRlInfo.ucNumOfResp   = 1;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, enCallType);
    }

    if ((TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PILOT_PHASE_MEAS)
     == (TAF_XPDS_RCV_PDE_DATA_MASK_REQ_PILOT_PHASE_MEAS & ulDataMask))
    {
        TAF_XPDS_UpdatePpmInGlobal();

        PS_MEM_SET(&stEncodeRlInfo, 0x00, sizeof(TAF_XPDS_ENCODE_RL_INFO_STRU));

        stEncodeRlInfo.aucRspType[0] = TAF_XPDS_RL_MSGTYPE_RESP_PROV_PILPHASE_MEAS;
        stEncodeRlInfo.ucNumOfResp   = 1;

        TAF_XPDS_SndPdeReverseMsg_L2Pde(&stEncodeRlInfo, enCallType);

    }

    return;
}
VOS_VOID TAF_XPDS_ProcPdeLocationRsp_L2Pde(VOS_VOID)
{
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enFixMode;

    enFixMode = TAF_XPDS_GetAgpsFixMode();

    /* Get Location INfo From GPS, And need to send to GPS */
    TAF_XPDS_SndAtGpsPositionInfo();

    /* MSA AfLT�����У�λ����Ϣ��������PDE, ��ȡλ����Ϣ�󣬿��ԶϿ�PDE����· */
    if ((TAF_XPDS_MSA_MODE  == enFixMode)
     || (TAF_XPDS_AFLT_MODE == enFixMode))
    {
        if (TAF_XPDS_PDE_SESSION_STATUS_ENDED != TAF_XPDS_GetPdeSessionStatus())
        {
           /* if ucSessStart's value equals 0, means that MS don't receive End Indication From PDE, So MS Can send end Frist  */
            TAF_XPDS_SndAtApPdeSessionEndMsg();

            TAF_XPDS_SetPdeSessionStatus(TAF_XPDS_PDE_SESSION_STATUS_ENDED);

            TAF_XPDS_MNTN_TraceSessionEndIndMsg();
        }
    }

    return;
}
VOS_VOID TAF_XPDS_ProcEphData_L2Pde_MsbWaitPdeData(VOS_VOID)
{
    if (VOS_TRUE == TAF_XPDS_GetRespGpsIonInEphimFlag())
    {
        TAF_XPDS_SndAtGpsIonInfo();
        TAF_XPDS_SetRespGpsIonInEphimFlag(VOS_FALSE);
    }

    TAF_XPDS_SndAtGpsEphInfo();

    /* �������ALM���ݰ��ѽ�����ɣ���λ�ɹ����˳�PDE L2״̬����
       �����EPH������ɱ�־���ó�TRUE���ȴ�ALM���ݰ����
    */
    if (VOS_TRUE == TAF_XPDS_GetGpsAlmDataFinishedFlag())
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }
    else
    {
        TAF_XPDS_SetGpsEphDataFinishedFlag(VOS_TRUE);
    }

    return;
}


VOS_VOID TAF_XPDS_ProcAlmData_L2Pde_MsbWaitPdeData(VOS_VOID)
{
    TAF_XPDS_SndAtGpsAlmInfo();

    /* �������EPH���ݰ��ѽ�����ɣ���λ�ɹ����˳�PDE L2״̬����
       �����ALM������ɱ�־���ó�TRUE���ȴ�EPH���ݰ����
    */
    if (VOS_TRUE == TAF_XPDS_GetGpsEphDataFinishedFlag())
    {
        TAF_XPDS_SndInternalPdeProcRsltInd(TAF_XPDS_PROC_RSLT_SUCC);

        TAF_XPDS_ProcQuitL2Pde_L2Pde();
    }
    else
    {
        TAF_XPDS_SetGpsAlmDataFinishedFlag(VOS_TRUE);
    }

    return;
}


VOS_VOID TAF_XPDS_ProcQuitL2Pde_L2Pde(VOS_VOID)
{
    /* ���PDEû���·�SS_SEND��Ϣ����PDE����SS_SEND��Ϣ */
    if (TAF_XPDS_PDE_SESSION_STATUS_ENDED != TAF_XPDS_GetPdeSessionStatus())
    {
        TAF_XPDS_SndAtApPdeSessionEndMsg();

        TAF_XPDS_SetPdeSessionStatus(TAF_XPDS_PDE_SESSION_STATUS_ENDED);
    }

    TAF_XPDS_StopAllL2PdeTimer_L2Pde();

    TAF_XPDS_IncreaseSessTagInRsvPdMsgHeader();

    TAF_XPDS_InitPdePublicDataPdeInit();

    TAF_XPDS_QuitFsmL2();

    return;
}
VOS_VOID TAF_XPDS_SndPdeStartDeliverData_L2Pde(VOS_VOID)
{
    VOS_UINT8                          *pucEncodeBuf       = VOS_NULL_PTR;
    TAF_XPDS_START_DELV_DATA_STRU       stStartDelvData;
    VOS_UINT32                          ulMsgBufLen;

    pucEncodeBuf  = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XPDS, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    if (VOS_NULL_PTR == pucEncodeBuf)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndPdeStartDeliverData_L2Pde, malloc failed");

        return;
    }

    PS_MEM_SET(pucEncodeBuf, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    PS_MEM_SET(&stStartDelvData, 0x00, sizeof(TAF_XPDS_START_DELV_DATA_STRU));

    stStartDelvData.ucMSIDType = TAF_XPDS_MSID_TYPE;
    stStartDelvData.ucMSIDLen  = TAF_XPDS_MSID_DATA_LEN_IN_BYTE;
    stStartDelvData.ucLength   = TAF_XPDS_START_DELIVERY_DATA_LEN_IN_BYTE;

    TAF_XPDS_GetMsIdRecFromCard(stStartDelvData.stMsIdRec.aucMsIdRec);

    ulMsgBufLen = 0;

    TAF_XPDS_MNTN_TraceReverseStartDeliverData(&stStartDelvData);

    TAF_XPDS_EncodeStartDeliverData(&stStartDelvData, pucEncodeBuf, &ulMsgBufLen);

    /* in control plane send data burst message */
    if (TAF_XPDS_CTRL_PLANE == TAF_XPDS_GetAgpsCfg()->enCallType)
    {
        TAF_XPDS_SndCasDataBurstMsg(pucEncodeBuf, ulMsgBufLen);
    }
    else
    {
        TAF_XPDS_SndApMsg(AT_XPDS_SERVER_MODE_PDE, pucEncodeBuf, ulMsgBufLen);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pucEncodeBuf);

    return;
}
VOS_VOID TAF_XPDS_SndPdeReverseMsg_L2Pde(
    TAF_XPDS_ENCODE_RL_INFO_STRU       *pstEncodeRlInfo,
    TAF_XPDS_CALL_TYPE_ENUM_UINT8       enCallType
)
{
    VOS_UINT8                          *pucEncodeBuf;
    VOS_UINT32                          ulEncodeBufLength;

    /* allocate memory for the message */
    pucEncodeBuf  = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XPDS, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    if (VOS_NULL_PTR == pucEncodeBuf)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndPdeReverseMsg_L2Pde, malloc failed");
        return;
    }

    PS_MEM_SET(pucEncodeBuf, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    ulEncodeBufLength = 0;

    TAF_XPDS_MNTN_TraceReverseMsgInfoIndMsg(pstEncodeRlInfo);

    TAF_XPDS_EncodeReverseMsg(pstEncodeRlInfo, pucEncodeBuf, &ulEncodeBufLength);

    /* in control plane send data burst message */
    if (TAF_XPDS_CTRL_PLANE == enCallType)
    {
        TAF_XPDS_SndCasDataBurstMsg(pucEncodeBuf, ulEncodeBufLength);
    }
    else
    {
        TAF_XPDS_SndApMsg(AT_XPDS_SERVER_MODE_PDE, pucEncodeBuf, ulEncodeBufLength);
    }

    PS_MEM_FREE(UEPS_PID_XPDS, pucEncodeBuf);

    return;
}


VOS_VOID TAF_XPDS_StopAllL2PdeTimer_L2Pde(VOS_VOID)
{
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_ASSIST_DATA_CNF);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_RSP_PDE_PSEUDORANGE_REQ_QUALITY);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_LOCATION_INFO_CNF);
    TAF_XPDS_StopTimer(TI_TAF_XPDS_WAIT_PDE_MSB_DATA);

    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */








