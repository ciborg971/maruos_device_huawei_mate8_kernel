

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "TafSdcLib.h"
#include "TafApsCtx.h"
#include "TafMmaInterface.h"
#include "TafApsSndXcc.h"
#include "TafApsSndPpp.h"
#include "TafApsSndAds.h"
#include "TafApsSndCds.h"

#include "taf_aps_ppp_pif.h"
#include "TafApsComFunc.h"
#include "TafApsTimerMgmt.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsComFunc.h"
#include "TafSdcCtx.h"
#include "MnApsComm.h"
#include "TafLog.h"
#include "TafApsDsFlowStats.h"

#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsFsmCdataEsting.h"
#include "TafApsFsmCdataDiscingTbl.h"
#include "TafApsSndRlp.h"
#include "TafApsSndCds.h"
#include "TafApsProcIpFilter.h"
#include "hsm_aps_pif.h"
#include "TafApsSndHsm.h"
#include "xcc_aps_pif.h"
#include "TafApsProcEpdszid.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */
#include "ehsm_aps_pif.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndNd.h"
#include "TafApsSndDhcp.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */

#ifdef __cplusplus
#if __cplusplus
    extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_ESTING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/******************************************************************************
   2 �ⲿ������������
******************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
*****************************************************************************/


/******************************************************************************
   5 ����ʵ��
******************************************************************************/


VOS_UINT32 TAF_APS_RcvPsCallOrigReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* ��ʼ��, ��ȡPDP ID�͵�ǰ���뼼�� */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���PS��״̬, �����Ч, ֱ�ӷ���ERROR */
    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        /* �ϱ�PDP������� */
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_SIM_INVALID);

        /* �����Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }

    /* Modified by y00314741 for CDMA Iteration 15, 2015-5-21, begin */
    if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                                 pstCallOrigReq->stDialParaInfo.ucCid,
                                 TAF_PS_CAUSE_SUCCESS);
    }
    /* Modified by y00314741 for CDMA Iteration 15, 2015-5-21, end */

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstCallOrigReq->stDialParaInfo.ucCid,
                                 pstCallOrigReq->stDialParaInfo.enPdpType);

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVATING);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* ���֧��HYBRIDģʽ��������HPRDģʽ�½��г��Խ��� */
    if (VOS_FALSE == TAF_SDC_Is1xOnlyMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_FALSE);

                break;
            case TAF_APS_RAT_TYPE_EHRPD:
                /* Added by y00314741 for CDMA Iteration 15, 2015-5-21, begin */
                TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PS_CALL);
                /* Added by y00314741 for CDMA Iteration 15, 2015-5-21, end */

                break;

            case TAF_APS_RAT_TYPE_1X:
                /* TODO:������Ҫ����DSDS��NO RF�ĳ��� */
                TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_TRUE);
                break;

            case TAF_APS_RAT_TYPE_NULL:
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);

                ulTimerLen = TAF_APS_GetCallRemainTmrLen(ucCid);

                if (0 == ulTimerLen)
                {
                    ulTimerLen = TI_TAF_APS_CDATA_ESTING_LEN;
                }

                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
                TAF_APS_SetCallRemainTmrLen(ucCid, 0);

                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvPsCallOrigReq_CdataEsting_Init: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* �����֧��Hybrid����ֻ֧��1X������1X�³��Խ��� */
        TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPppDialOrigReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT32                          ulTimerLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;

    /* ��ʼ��, ��ȡPDP ID�͵�ǰ���뼼�� */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType       = TAF_APS_GetCurrPdpEntityRatType();
    ucCid               = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���PS��״̬, �����Ч, ֱ�ӷ���ERROR */
    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        /* �ϱ�PDP������� */
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SIM_INVALID);

        /* �����Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }

    if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SUCCESS);
    }

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                 TAF_APS_GetTafCidInfoPdpType(ucCid));



    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVATING);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* ���֧��HYBRIDģʽ��������HPRDģʽ�½��г��Խ��� */
    if (VOS_FALSE == TAF_SDC_Is1xOnlyMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_FALSE);

                break;
            case TAF_APS_RAT_TYPE_EHRPD:
                enPdpType = TAF_APS_GetTafCidInfoPdpType(pstPppDialOrigReq->stPppDialParaInfo.ucCid);

                if ((TAF_PS_CDATA_DIAL_MODE_RELAY == TAF_APS_GetFsmCtxCdataDialMode())
                 || (TAF_PDP_PPP == enPdpType))
                {
                    /* �м�ģʽ���ߵ�ַ��������ΪPPP�����ϱ�����ʧ�� */
                    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_INVALID_PARAMETER);
                }

                TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PPP_DIAL);

                break;

            case TAF_APS_RAT_TYPE_1X:
                /* TODO:������Ҫ����DSDS��NO RF�ĳ��� */
                TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_TRUE);
                break;

            case TAF_APS_RAT_TYPE_NULL:
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);

                ulTimerLen = TAF_APS_GetCallRemainTmrLen(ucCid);
                if (0 == ulTimerLen)
                {
                    ulTimerLen = TI_TAF_APS_CDATA_ESTING_LEN;
                }

                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
                TAF_APS_SetCallRemainTmrLen(ucCid, 0);

                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvPsCallOrigReq_CdataEsting_Init: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* �����֧��Hybrid����ֻ֧��1X������1X�³��Խ��� */
        TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* area lost no RF����, ��������*/
/* TODO:
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_GetRfAvailFlag())
    {
        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL);
    }
#endif
*/
    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* DORMANT״̬�£���Ҫ�����½������� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* TODO: ���������ǰ�ķ���ģʽ�ͽ���ģʽ��ͬ��δ��� */
    switch (TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        case TAF_APS_RAT_TYPE_HRPD:
            TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_FALSE);

            break;

        case TAF_APS_RAT_TYPE_1X:
            TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvPsCallEndReq_CdataEsting_Init: Wrong RAT type!");

            return VOS_TRUE;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingCall;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstIncomingCall = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    /* �𼤻ʱ�� */
    TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    /* TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), 0); */

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* ������״̬ */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* ��¼��ǰ�������ݷ����ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, begin */

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, end */

    /* ����ByePassֵ���д��� */
    if (VOS_TRUE == pstIncomingCall->ucIsAlertAnsByPass)
    {
        /* ǨTAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND);
    }
    else
    {
        /* ����ID_APS_XCC_ANSWER_DATA_CALL_REQ */
        TAF_APS_SndXccAnswerDataCallReq(ucPdpId);

        /* ǨTAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF);
    }
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvCdsServiceInd_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType   = TAF_APS_GetCurrPdpEntityRatType();

    /* area lost no RF����, ��������*/
/* TODO:
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_GetRfAvailFlag())
    {
        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL);
    }
#endif
*/

    /* �û��������ݴ��������ݷ��������ؽ� */
    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);
    /* TODO:��Ҫ�ۺϿ��ǽ�DORMANTǰ���ݷ������ڵ�ģʽ */

    /* ���֧��HYBRIDģʽ��������HPRDģʽ�½��г��Խ��� */
    if (VOS_FALSE == TAF_SDC_Is1xOnlyMode())
    {
        switch (enCurrRatType)
        {
            case TAF_APS_RAT_TYPE_HRPD:
                TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_FALSE);

                break;
            case TAF_APS_RAT_TYPE_EHRPD:
                break;

            case TAF_APS_RAT_TYPE_1X:
            case TAF_APS_RAT_TYPE_NULL:
                /*1X or NULL*/
                TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_TRUE);
                break;

            default:
                TAF_WARNING_LOG(WUEPS_PID_TAF,
                    "TAF_APS_RcvCdsServiceInd_CdataEsting_Init: Wrong RAT type!");
                break;
        }
    }
    else
    {
        /* �����֧��Hybrid����ֻ֧��1X������1X�³��Խ��� */
        TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrigReq_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* Save Sub Fsm Entry Msg */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* Get curr RatType */
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();

    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_1X:
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

            TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_TRUE, VOS_FALSE, VOS_FALSE);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvPsEpdszidReOrigReq_CdataEsting_Init: Wrong RAT type!");
            break;
    }

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-25, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init
 ��������  : CDATA ESTING INIT��״̬���յ�ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��03��25��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* ����ƥ��1X��SrId */
    TAF_APS_SetPdpEntSrId(ucPdpId, TAF_APS_HRPD_DEFAULT_SR_ID);

    /* ��״̬TAF_APS_STA_CDATA_ESTING */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* ��1X�½��� */
    TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_TRUE, VOS_FALSE, VOS_TRUE);

    return VOS_TRUE;
}
/* Added by y00314741 for CDMA Iteration 11, 2015-3-25, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init
 ��������  : CDATA ESTING INIT��״̬���յ�ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��07��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterDormantEnd1xSvc_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* DORMANT״̬�£���Ҫ�����½������� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_TRUE, VOS_TRUE, VOS_FALSE);

    return VOS_TRUE;
}

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

VOS_UINT32 TAF_APS_RcvXccOrigDataCallCnf_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ORIG_DATA_CALL_CNF_STRU    *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    VOS_UINT8                           ucReOrigCount;

    /* ��ʼ�� */
    pstOirgCallCnf  = (XCC_APS_ORIG_DATA_CALL_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId      = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

    if (TAF_XCC_CAUSE_SUCCESS == pstOirgCallCnf->enRslt)
    {
        TAF_APS_SetPdpEntConRef(ucPdpId, pstOirgCallCnf->ucConRef);
        TAF_APS_SetPdpEntConnectId(ucPdpId, pstOirgCallCnf->ucConnectId);

        /* ����ز����ڶ�ʱ�������У���Ҫ�ر��ز����ڶ�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ��¼��ǰ�������ݷ����ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_1X);

        /* Ǩ��TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);

        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

        /* �������� */
        R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(TAF_APS_GetCurrPdpEntityDataServiceMode()));

        TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf();

        /* Clear ReOrig Scene */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }
    else
    {
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_APS_MapXccCause(pstOirgCallCnf->enRslt);

        if ((TAF_XCC_CAUSE_CCS_NOT_SUPPORT == pstOirgCallCnf->enRslt)
         || (TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MO_CALL == pstOirgCallCnf->enRslt)
         || (TAF_XCC_CAUSE_ABORTED_BY_RECEIVED_MT_CALL == pstOirgCallCnf->enRslt))
        {
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
            {
                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_TC_RELEASE);
            }
        }

        /* �ж��Ƿ���Ҫ����Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_1X))
        {
            ucReOrigCount = TAF_APS_GetPdpEntReOrigCount(ucPdpId);

            /* ��¼�Ƿ���L2ʧ��ԭ���µ��ز� */
            if (TAF_XCC_FAIL_LAYER_L2 == pstOirgCallCnf->enFailLayer)
            {
                TAF_APS_SetPdpEntL2ErrReOrigFlag(ucPdpId, VOS_TRUE);

                if (TAF_XCC_FAIL_LAYER_L3 != pstPdpEntity->stCdataInfo.enLastReOrigErr)
                {
                    /*ԭ��ֵ��ͬ, ���ߵ�һ���ز�ʧ�ܣ����ز������ۼ� */
                    TAF_APS_SetPdpEntReOrigCount(ucPdpId, ucReOrigCount + 1);
                }
                else
                {
                    /*ԭ��ֵ��ͬ��������1��ʼ����*/
                    TAF_APS_SetPdpEntReOrigCount(ucPdpId, 1);
                }

                pstPdpEntity->stCdataInfo.enLastReOrigErr = TAF_XCC_FAIL_LAYER_L2;

            }
            else
            {
                TAF_APS_SetPdpEntL2ErrReOrigFlag(ucPdpId, VOS_FALSE);

                if (TAF_XCC_FAIL_LAYER_L2 != pstPdpEntity->stCdataInfo.enLastReOrigErr)
                {
                    TAF_APS_SetPdpEntReOrigCount(ucPdpId, ucReOrigCount + 1);
                }
                else
                {
                    TAF_APS_SetPdpEntReOrigCount(ucPdpId, 1);
                }

                pstPdpEntity->stCdataInfo.enLastReOrigErr = TAF_XCC_FAIL_LAYER_L3;
            }

            if (VOS_TRUE == TAF_APS_IsNeedRedial1xSystemAcquire(pstPdpEntity->enCause))
            {
                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                         usClientId,
                                                         TAF_MMA_1X_NORMAL_DATA_CALL,
                                                         pstPdpEntity->enCause);
            }

            /* ��SILENT_REDIAL_WAIT 4s��ʱ��������˶�ʱ����ʱ���᳢���ز� */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* Ǩ��TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL��״̬ */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            if ((pstOirgCallCnf->enRslt == TAF_XCC_CAUSE_NORMAL_RELEASE)
            || ((pstOirgCallCnf->enRslt != TAF_XCC_CAUSE_NORMAL_RELEASE) && (TAF_XCC_FAIL_LAYER_L3 == pstOirgCallCnf->enFailLayer)))
            {
                TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf();


            }

            /* ֹͣ���̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

            /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
            TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);
        }

    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

    /* ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �жϵ�ǰCDATA PS״̬:�������active, APS����ȥ����״̬�� */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* ֹͣ���ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* ֹͣ�ز����ڶ�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ֮ǰ��������ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
           ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

           ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    }
    else
    {
        /* ����״̬�������Ϣ���������̴���������Ϊ�û�ȥ��������� */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccOrigCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                                TAF_PS_CAUSE_XCC_TIME_OUT);


    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvXccDataServiceConnInd_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_SERVICE_CONNECT_IND_STRU  *pstSoInd;
    VOS_UINT8                               ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstSoInd        = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* ����SO��CONREF��PPP ID��Ϣ */
    TAF_APS_SetPdpEntSo(ucPdpId, pstSoInd->enSo);
    TAF_APS_SetPdpEntConRef(ucPdpId, pstSoInd->ucConRef);

    /* ����SR ID��Ϣ */
    TAF_APS_SetPdpEntSrId(ucPdpId, pstSoInd->ucSrId);


    /* ���ݷ�������ɵĴ��� */
    TAF_APS_ProcCdataEstSucc_CdataEsting(ucPdpId);


    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �жϵ�ǰCDATA PS״̬:�������active, APS����ȥ����״̬�� */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* ֹͣ���ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

         /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
           ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

           ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    }
    else
    {
        /* ����״̬�������Ϣ���������̴���������Ϊ�û�ȥ��������� */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /*------------------------------------------------------------------
       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_INTERNAL_DISC_SO_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* ����ԭ��ֵ */
    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* �����ز���������ʧ�ܵ�ԭ�� */
    TAF_APS_RcvXccDiscCdataEst_CdataEsting_1XMode(ucPdpId, pstPdpEntity->enCause);

    return VOS_TRUE;

}
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccSoConnected(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����ԭ��ֵ */
    pstPdpEntity->enCause = TAF_PS_CAUSE_XCC_TIME_OUT;

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();

    /* �����ڲ���ϢID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ��Ϣ */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                       TAF_APS_INTER_END_CALL_REASON_SO_NEGOTIATE_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);


        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* ��PPP������ϢID_APS_PPP_DEACT_IND */
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        }


    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ) == pstEntryMsg->ulEventType)
          || (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ) == pstEntryMsg->ulEventType))
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_SO_NEGOTIATE_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    else if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND) == pstEntryMsg->ulEventType)
    {
        /* �����ڲ���ϢID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_HANDOFF,
                                       TAF_APS_INTER_EDN_CALL_REASON_HANDOFF,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);

        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* ��PPP������ϢID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        }

    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

    else
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_REEST_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_SO_NEGOTIATE_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXccAnsCallCnf_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_ANSWER_DATA_CALL_CNF_STRU  *pstAnsCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstAnsCallCnf   = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    if (TAF_XCC_CAUSE_SUCCESS == pstAnsCallCnf->enRslt)
    {
        /* Ǩ��TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);
    }
    else
    {
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_APS_MapXccCause(pstAnsCallCnf->enRslt);

        /* ֹͣ���̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* ����ʧ�ܵĴ��� */
        TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                             pstPdpEntity->enCause);

    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /*��ȡPDP ID */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ����״̬�������Ϣ���������̴���������Ϊ�û�ȥ��������� */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��Ϊ��ͻ���������ݱ���ʱ���û�����绰,����XCCӦ�ûظ�ANS_CALL_CNF��Ϣ */

    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd      = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                         pstPdpEntity->enCause);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                                TAF_PS_CAUSE_XCC_TIME_OUT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvXccCallConnectedInd_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_CONN_IND_STRU    *pstCallConnInd;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    pstCallConnInd  = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ����CONREF��Ϣ */
    TAF_APS_SetPdpEntConRef(ucPdpId, pstCallConnInd->ucConRef);

    /* Ǩ��TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED��״̬ */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ����״̬�������Ϣ���������̴���������Ϊ�û�ȥ��������� */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��Ϊ��ͻ���������ݱ���ʱ���û�����绰 */

    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd      = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
    TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                         pstPdpEntity->enCause);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvTiRedialIntervalExpired_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucIsDormDataCall;
    VOS_UINT8                           ucDrsFlag;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    ucDrsFlag    = VOS_TRUE;
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg  = TAF_APS_GetCurrSubFsmMsgAddr();

    if (VOS_TRUE == TAF_APS_GetFinishClSearch())
    {
        /* �ж��Ƿ���Է���HRPD���� */
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
        {
            /* Send Orig Data Call Req To HSM */
            TAF_APS_SndHsmOrigReq(ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
                TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
            }
            TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

            /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF);

            return VOS_TRUE;
        }

        /* �ж��Ƿ���Է���1X���� */
        if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
        {
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
            {
                /* Esting Fsm is started, Set Re-Orig Secne BuTT */
                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
            }

            ucDrsFlag                   = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
            ucIsDormDataCall            = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

            TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(ucIsDormDataCall, ucDrsFlag);

            return VOS_TRUE;
        }

    }

    TAF_APS_GetRemainTimerLen(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                              ucPdpId,
                              &ulRemainTimeLen);

    if ((ulRemainTimeLen >= TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN)
     && (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ))
     && (pstEntryMsg->ulEventType != TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND)))
    {

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }
    else
    {
        /* ֹͣ���̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ֪ͨ����ģ��������� */
        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

            TAF_APS_SetPdpEntCdataEstFailCause(ucPdpId, TAF_APS_RAT_TYPE_1X);
        }
        else
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

            TAF_APS_SetPdpEntCdataEstFailCause(ucPdpId, TAF_APS_RAT_TYPE_HRPD);
        }

        pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

        /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
        TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                             pstPdpEntity->enCause);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �жϵ�ǰCDATA PS״̬:�������active, APSȥ���� */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* ֹͣ���ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* ֹͣ�ز����ڡ��ز������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

        if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
        }

        if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        }

        /* ���û�����DEACTIVE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* ����״̬�������Ϣ���������̴���������Ϊ�û�ȥ��������� */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg  = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST                              *pstPdpEntity = VOS_NULL_PTR;
    VOS_UINT8                                               ucPdpId;
    VOS_UINT8                                               ucIsDormDataCall;
    VOS_UINT8                                               ucDrsFlag;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstSvcStaChangeReq = VOS_NULL_PTR;

    ucDrsFlag    = VOS_TRUE;
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg  = TAF_APS_GetCurrSubFsmMsgAddr();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��ȡ��Ϣ���� */
    pstSvcStaChangeReq = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;


    /*�ж��Ƿ���Ҫ�����ز� */
    if (VOS_FALSE == TAF_APS_IsNeedRedialImmediately(pstPdpEntity->enCause))
    {
        return VOS_TRUE;
    }

    switch(pstSvcStaChangeReq->enRatType)
    {
        /* �ж�HRPD�з��� */
        case TAF_APS_RAT_TYPE_HRPD:

            /* �ж��Ƿ���Է���HRPD���� */
            if(VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
            {
                /* ֹͣ��ʱ�� */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

                /* Send Orig Data Call Req To HSM */
                TAF_APS_SndHsmOrigReq(ucPdpId);

                if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
                {
                    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
                    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
                }

                TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

                /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
                TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF);
            }

            break;

        /* �ж�1X���� */
        case TAF_APS_RAT_TYPE_1X:
            /* �ж��Ƿ���Է���1X���� */
            if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
            {
                /* ֹͣ��ʱ�� */
                TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

                if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ) == pstEntryMsg->ulEventType)
                {
                    /* Esting Fsm is started, Set Re-Orig Secne BuTT */
                    TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
                }

                ucDrsFlag                   = TAF_APS_GetDrsValueByScene(pstEntryMsg->ulEventType);
                ucIsDormDataCall            = TAF_APS_IsRedialCallFromDormantState(ucPdpId);

                TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(ucIsDormDataCall, ucDrsFlag);
            }

            break;
        case TAF_APS_RAT_TYPE_EHRPD:
        case TAF_APS_RAT_TYPE_LTE:
            /* ֹͣ���̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
            }
            else
            {
                TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
            }

            /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
            TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId,
                                                 TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            break;

        default:
            break;
    }

    return VOS_TRUE;

}



VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_CdataEsting_WaitRedial(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_INCOMING_CALL_IND_STRU     *pstIncomingCall;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstIncomingCall = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    /* �˳����£����ܱ��������Ϣ */

    /* ��¼��ǰ�������ݷ����ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    /* �ܵļ��ʱ��TAF_APS_STA_CDATA_ESTING��ʱ�����У���Ҫ�ȹر����������� */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId))
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    }

    /* ֹͣ�ز���ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

    /* ����ByePassֵ���д��� */
    if (VOS_TRUE == pstIncomingCall->ucIsAlertAnsByPass)
    {
        /* ǨTAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND);
    }
    else
    {
        /* ����ID_APS_XCC_ANSWER_DATA_CALL_REQ */
        TAF_APS_SndXccAnswerDataCallReq(ucPdpId);

        /* ǨTAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF��״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg,
    VOS_UINT8                           ucHrpdHandOff1xFlg
)
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;
    VOS_UINT16                          usClientId;

    /* Get Pdp Fsm Entity */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->stCdataInfo.ucCallId              = ucPdpId + 1;
    pstPdpEntity->stCdataInfo.enSo                  = TAF_APS_GetFsmCtxCdataSoInitType();
    pstPdpEntity->stCdataInfo.ucDrsFlg              = ucDrsFlg;
    pstPdpEntity->stCdataInfo.ucIsDormDataCall      = ucIsDormDataCall;
    pstPdpEntity->stCdataInfo.ucIsL2ErrReOrig       = VOS_FALSE;
    pstPdpEntity->stCdataInfo.ucReOrigCount         = 0;

    ucCid      = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);

    /* Send start Ntf to MMA */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_1X);

    /* Start Timer TI_TAF_APS_CDATA_ESTING */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    }

    /* Start Timer TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN, ucPdpId);
    }

    /* �ж��Ƿ���Է���1X���� */
    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
    {
        /* Send Orig Data Call Req To Xcc */
        TAF_APS_SndXccOrigDataCallReq(ucPdpId, ucHrpdHandOff1xFlg);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF);
    }
    else
    {


        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_ProcCdataRedialReOrig_CdataEsting_1XMode(
    VOS_UINT8                           ucIsDormDataCall,
    VOS_UINT8                           ucDrsFlg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ȡAPSʵ������ */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->stCdataInfo.ucCallId              = ucPdpId + 1;
    pstPdpEntity->stCdataInfo.enSo                  = TAF_APS_GetFsmCtxCdataSoInitType();
    pstPdpEntity->stCdataInfo.ucDrsFlg              = ucDrsFlg;
    pstPdpEntity->stCdataInfo.ucIsDormDataCall      = ucIsDormDataCall;

    if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetFsmCtxCdataLastDialOnRatType())
    {
        TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);
        TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);
    }

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_1X);

    /* ��1X�������ݷ������ӽ������� */
    TAF_APS_SndXccOrigDataCallReq(ucPdpId, VOS_FALSE);

    /* ��״̬Ǩ����TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF);

    return VOS_TRUE;


}
VOS_VOID TAF_APS_ProcCdataEstSucc_CdataEsting(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ʼ�� */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

    /* ����ز����ڶ�ʱ�������У���Ҫ�ر��ز����ڶ�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, begin */

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, end */

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE״̬���û���������������ݷ����� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
            /* CDMA HRPDģʽ��Ŀǰֻ֧��һ�����أ�Ĭ��rabIdΪ5 */
            pstPdpEntity->ucNsapi       = TAF_APS_DEFAULT_CDATA_RAB_ID;
            pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
            pstPdpEntity->ActType       = APS_PDP_ACT_PRI;
            TAF_APS_SetPdpEntCdataPdnId(ucPdpId, TAF_APS_DEFAULT_CDATA_PDN_ID);



            /* ����IP���� */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ֪ͨRLP����ʼ�� */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            if (TAF_PS_CDATA_DIAL_MODE_RELAY == TAF_APS_GetFsmCtxCdataDialMode())
            {
                /* ���û��ϱ�ACTIVATE_CNF�¼� */
                TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

                /* ����CDATA PS�����״̬ΪACTIVE״̬ */
                TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);

            }
            else
            {
                /* ����ID_APS_PPP_ACT_REG��Ϣ��PPPģ�� */
                TAF_APS_SndPppActReq(ucPdpId);

                /* �𼤻ʱ�� */
                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                                   TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF_LEN,
                                   ucPdpId);

                /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_ACTIVATING */
                TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVATING);

            }

            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):

            /* CDMA 1Xģʽ��Ŀǰֻ֧��һ�����أ�Ĭ��rabIdΪ5 */
            pstPdpEntity->ucNsapi       = TAF_APS_DEFAULT_CDATA_RAB_ID;
            pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
            pstPdpEntity->ActType       = APS_PDP_ACT_PRI;
            TAF_APS_SetPdpEntCdataPdnId(ucPdpId, TAF_APS_DEFAULT_CDATA_PDN_ID);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ֪ͨRLP����ʼ�� */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* �м�ģʽ�²���Ҫ֪ͨPPP������Э�� */
            if (TAF_PS_CDATA_DIAL_MODE_RELAY == TAF_APS_GetFsmCtxCdataDialMode())
            {
                /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */

                /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

                /* ����IP���� */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* ���û��ϱ�ACTIVATE_CNF�¼� */
                TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

                /* ����CDATA PS�����״̬ΪACTIVE״̬ */
                TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);

                /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
            }
            else
            {
                /* ����ID_APS_PPP_ACT_REG��Ϣ��PPPģ�� */
                TAF_APS_SndPppActReq(ucPdpId);

                /* �𼤻ʱ�� */
                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                                   TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF_LEN,
                                   ucPdpId);

                /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_ACTIVATING */
                TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVATING);

                /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();

            }
            break;

        /* DORMANT״̬���û�ȥ����������ݷ����ؽ����߶Ͽ����� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
            /* �����ڲ���ϢID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                           TAF_APS_INTER_END_CALL_REASON_USER_END,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ֪ͨRLP����ʼ�� */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND):
            /* �����ڲ���ϢID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_HANDOFF,
                                           TAF_APS_INTER_EDN_CALL_REASON_HANDOFF,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ֪ͨRLP����ʼ�� */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

        /* DORMANT״̬���û������������������ݷ����ؽ���ֱ��ǨACTIVE״̬ */
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, begin */
        /* DORMANT״̬�£�HRPD���� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, end */

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ֪ͨRLP����ʼ�� */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ��RLPע����������״̬�Ļص���������ʼ��ʱ */
                CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);
            }


            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
            TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT״̬�����ഥ�������ݷ����ؽ���ֱ��ǨACTIVE״̬ */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            /* TODO:���û��ϱ���DORMANT״̬ */

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* ֪ͨRLP����ʼ�� */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }


            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
            TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_APS_QuitCurrSubFsm();

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ProcCdataEstSucc_CdataEsting:Wrong Msg Entry");
            break;
    }

}

/*****************************************************************************
 �� �� ��  : TAF_APS_ProcCdataEstSucc_CdataEsting_Ehrpd
 ��������  : CDATA����EHRPD�������ɹ��Ĵ���
 �������  : VOS_UINT8                           ucPdpId
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��27��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID TAF_APS_ProcCdataEstSucc_CdataEsting_Ehrpd(
    VOS_UINT8                           ucPdpId,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;

    /* ��ʼ�� */
    pstPdnActCnf    = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* CDMA EHRPDģʽ�³��� */
    pstPdpEntity->ucNsapi       = pstPdnActCnf->ucRabId;
    pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
    pstPdpEntity->ActType       = APS_PDP_ACT_PRI;

    /* ��¼��ǰ�������ݷ����ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* ��¼PDNID Pdnadrr Apn Dns */
    TAF_APS_SetPdpEntCdataPdnId(ucPdpId, pstPdnActCnf->ucPdnId);
    TAF_APS_UpdateCdataEhsmPdnInfo(pstPdpEntity,
                                   &(pstPdnActCnf->stPdnAddr),
                                   &(pstPdnActCnf->stApn),
                                   &(pstPdnActCnf->stIpv4Dns));


    /* ����Ҫ��ȡIpv4 DNS */
    if (((VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnActCnf->stPdnAddr.enPdnType))
    {
        /* ���û��ϱ�ACTIVATE_CNF�¼� */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else
    {
        /* ��Ҫ��ȡIpv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4   == pstPdnActCnf->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActCnf->stPdnAddr.enPdnType))
         && (((VOS_TRUE != pstPdnActCnf->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnActCnf->stIpv4Dns.bitOpIpv4SecDNS))))
        {
            /* ��DHCP����GET_DNS_IPV4��Ϣ  */
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);

            /* ��ʱ��WAIT_DHCP_ACT_IPV4_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF_LEN,
                               ucPdpId);
        }

        /* ��Ҫ��ȡIpv6 DNS��Ipv4,Ipv4v6���� */
        if ((EHSM_APS_PDN_TYPE_IPV6   == pstPdnActCnf->stPdnAddr.enPdnType)
         || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActCnf->stPdnAddr.enPdnType))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;

            /* ��DHCP����GET_DNS_IPV6��Ϣ  */
            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);

            /* ��ʱ��WAIT_DHCP_ACT_IPV6_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF_LEN,
                               ucPdpId);
        }
    }


    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* �������� */
    R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(TAF_APS_GetCurrPdpEntityDataServiceMode()));

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
    TAF_APS_QuitCurrSubFsm();

}
VOS_UINT32 TAF_APS_ProcCdataEstFail_CdataEsting(
    VOS_UINT8                               ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8      enCdataPppState;

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    enCdataPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE״̬���û�ȥ����������ݷ����߶Ͽ����� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):
            /* ���û�����ACTIVE_REJ�¼� */
            TAF_APS_SndPdpActivateRej(ucPdpId, enCause);

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT״̬���û�ȥ����������ݷ����ؽ����߶Ͽ����� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
            /* ���û�����DEACTIVE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* ���PPP�Ѽ��֪ͨPPPȥ���� */
            if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enCdataPppState)
            {
                TAF_APS_SndPppDeactInd(ucPdpId);
            }

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ����IP���� */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();
            break;

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
        /* DORMANT״̬�·������ݷ���ģʽ�л�������ʧ�� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND):

            /* �ϱ�ȥ������¼� */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            /* ���õ�ǰ���ݷ���ģʽ */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

            /* ����ȥ���� */
            TAF_APS_LocalReleaseProc(ucPdpId);

            break;
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

        /* DORMANT״̬���û������������������ݷ����ؽ� */
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, end */

            if (VOS_TRUE == TAF_APS_IsCdataLocalReleaseCause(enCause))
            {
                /* ֹͣ����ͳ�� */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* �ͷ�APS��Դ */
                Aps_ReleaseApsResource(ucPdpId);

                /* ����IP���� */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* ��״̬Ǩ����TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                if (TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND) == pstEntryMsg->ulEventType)
                {
                    /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
                    TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
                }
            }

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT״̬�����緢������ݷ����ؽ���ֱ��ǨDORMANT״̬ */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            if (TAF_PS_CAUSE_XCC_AS_SO_REJ == enCause)
            {
                /* ֹͣ����ͳ�� */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* �ͷ�APS��Դ */
                Aps_ReleaseApsResource(ucPdpId);

                /* ����IP���� */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* ��״̬Ǩ����TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
                TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();

            break;
        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ProcCdataEstFail_CdataEsting:Wrong Msg Entry");
            break;
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXccDiscCdataEst_CdataEsting_1XMode(
    VOS_UINT8                               ucPdpId,
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8      enCdataPppState;

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    enCdataPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE״̬���û�ȥ����������ݷ����ϱ�����ʧ�� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):

            /* ���û�����ACTIVE_REJ�¼� */
            TAF_APS_SndPdpActivateRej(ucPdpId, enCause);

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT״̬���û�ȥ����������ݷ����ؽ����ϱ�ȥ���� */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):

            /* ���û�����DEACTIVE_CNF�¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* ���PPP�Ѽ��֪ͨPPPȥ���� */
            if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enCdataPppState)
            {
                TAF_APS_SndPppDeactInd(ucPdpId);
            }

            /* �ͷ�APS��Դ */
            Aps_ReleaseApsResource(ucPdpId);

            /* ����IP���� */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT״̬���û������������������ݷ����ؽ���ֱ��ǨINACTIVE״̬ */
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, end */

            if (VOS_TRUE == TAF_APS_IsCdataLocalReleaseCause(enCause))
            {
                /* ֹͣ����ͳ�� */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* �ͷ�APS��Դ */
                Aps_ReleaseApsResource(ucPdpId);

                /* ����IP���� */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* ��״̬Ǩ����TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                if (TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND) == pstEntryMsg->ulEventType)
                {
                    /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
                    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
                }
            }

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT״̬�����緢������ݷ����ؽ���ֱ��ǨDORMANT״̬ */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            if (TAF_PS_CAUSE_XCC_AS_SO_REJ == enCause)
            {
                /* ֹͣ����ͳ�� */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* �ͷ�APS��Դ */
                Aps_ReleaseApsResource(ucPdpId);

                /* ����IP���� */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* ��״̬Ǩ����TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
                TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }

            /* �˳���״̬״̬�� */
            TAF_APS_QuitCurrSubFsm();

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvXccDiscCdataEst_CdataEsting_1XMode:Wrong Msg Entry");
            break;
    }

    return VOS_TRUE;
}
VOS_VOID TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(
    VOS_UINT8                           ucPdpId,
    VOS_UINT32                          ulNeedSearchSys
)
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;
    VOS_UINT16                          usClientId;

    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId      = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);

    /* ���Ų��� */
    pstPdpEntity->stCdataInfo.ucCallId = ucPdpId + 1;

    /* Send start Ntf to MMA */
    TAF_SndMmaCdmaMoCallStartNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

    TAF_APS_SetFsmCtxCdataLastDialOnRatType(TAF_APS_RAT_TYPE_HRPD);

    /* Start Timer TI_TAF_APS_CDATA_ESTING */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    }

    /* Start Timer TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING != enTimerStatus)
    {
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD_LEN,
                           ucPdpId);
    }

    /* �ж��Ƿ���Է���HRPD���� */
    if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
    {
        /* Send Orig Data Call Req To HSM */
        TAF_APS_SndHsmOrigReq(ucPdpId);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_HSM_ORIG_CALL_CNF);
    }
    else
    {
        /* Send Redial Ntf to MMA */
        if (VOS_TRUE == ulNeedSearchSys)
        {
            /* ����HRPD������MRU[0] */
            TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                     usClientId,
                                                     TAF_MMA_DO_NORMAL_DATA_CALL,
                                                     TAF_PS_CAUSE_HRPD_NO_SERVICE);

            /* ��Ҫ�ȴ�ϵͳ�������������ز� */
            TAF_APS_SetFinishClSearch(VOS_FALSE);
        }

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                           TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                           ucPdpId);

        /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
    }
}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, begin */

VOS_VOID TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(
    VOS_UINT8                           ucPdpId,
    TAF_APS_ORIG_TYPE_ENUM_UINT8        enDailType

)
{
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;
    VOS_UINT8                           ucCid;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enDataServiceType;
    VOS_UINT32                          ulTimerLen;

    /* ��ȡAPS��Cid, ClientId */
    ucCid      = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* ���û�г��أ�������L�е�C���򻺴�ú��н������� */
    enDataServiceType = TAF_APS_GetCurrPdpEntityDataServiceMode();
    if ((VOS_FALSE == TAF_APS_IsAnyBearerExist())
     || (TAF_APS_RAT_TYPE_EHRPD != enDataServiceType))
    {
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);

        enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
        if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
        {
            ulTimerLen = TAF_APS_GetCallRemainTmrLen(ucCid);

            if (0 == ulTimerLen)
            {
                ulTimerLen = TI_TAF_APS_CDATA_ESTING_LEN;
            }

            TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
            TAF_APS_SetCallRemainTmrLen(ucCid, 0);
        }

        return;
    }

    /* Send pdn activate Call Req To EHSM */
    TAF_APS_SndEhsmPdnActReq(ucPdpId, enDailType);

    /* Sub Fsm State transfer to TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF);

    /* Start Timer TI_TAF_APS_CDATA_ESTING */
    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId);
    if (TAF_APS_TIMER_STATUS_STOP == enTimerStatus)
    {
        ulTimerLen = TAF_APS_GetCallRemainTmrLen(ucCid);

        if (0 == ulTimerLen)
        {
            ulTimerLen = TI_TAF_APS_CDATA_ESTING_LEN;
        }

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, ulTimerLen, ucPdpId);
        TAF_APS_SetCallRemainTmrLen(ucCid, 0);
    }
}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-14, end */



VOS_UINT32 TAF_APS_RcvHsmOrigCnf_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSM_APS_ORIG_CNF_STRU              *pstOirgCallCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT16                          usClientId;
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;

    /* ��ʼ�� */
    pstOirgCallCnf  = (HSM_APS_ORIG_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId      = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);

    if (HSM_APS_CAUSE_SUCCESS == pstOirgCallCnf->enResult)
    {
        /* ��¼��ǰ�������ݷ����ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);


        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

        /* ���ݷ�������ɵĴ��� */
        TAF_APS_ProcCdataEstSucc_CdataEsting(ucPdpId);


        /* �������� */
        R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(TAF_APS_GetCurrPdpEntityDataServiceMode()));
    }
    else
    {
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_APS_MapHsmCause(pstOirgCallCnf->enResult);

        /* �ж��Ƿ���Ҫ����Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_HRPD))
        {
#if 0
            if (VOS_TRUE == TAF_APS_IsNeedRedialHrpdSystemAcquire(pstPdpEntity->enCause))
            {
                /* ����������ʧ�ܣ��ݲ�֪ͨMMA���� */
                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                       usClientId,
                                                       TAF_MMA_DO_NORMAL_DATA_CALL,
                                                       pstPdpEntity->enCause);

                 /* ��Ҫ�ȴ�ϵͳ�������������ز� */
                 TAF_APS_SET_CDATA_WAIT_SYS_REQUIRE(VOS_TRUE);
            }
#endif
            /* ��SILENT_REDIAL_WAIT 4s��ʱ��������˶�ʱ����ʱ���᳢���ز� */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* Ǩ��TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL��״̬ */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            /* ֹͣ���̶�ʱ�� */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* ����ز����ڶ�ʱ�������У���Ҫֹͣ */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

            /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
            TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);
        }

    }
    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

    /* ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* �жϵ�ǰCDATA PS״̬:�������active, APS����ȥ����״̬�� */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* ֹͣ���ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* ֹͣ�ز����ڶ�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* ֮ǰ��������ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
           ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

           ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    }
    else
    {
        /* ����״̬�������Ϣ���������̴���������Ϊ�û�ȥ��������� */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ����ʧ�ܵĴ��� */
    TAF_APS_ProcCdataEstFail_CdataEsting(TAF_APS_GetCurrFsmEntityPdpId(),
                                         TAF_PS_CAUSE_HSM_TIME_OUT);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
   /*------------------------------------------------------------------
       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_INTERNAL_DISC_SO_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}


/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf
 ��������  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF��״̬��
             �յ�ID_EHSM_APS_PDN_ACTIVATE_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��14��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ�� */
    pstPdnActCnf    = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (EHSM_APS_CAUSE_SUCCESS == pstPdnActCnf->enCause)
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* ���ݽ����ɹ����� */
        TAF_APS_ProcCdataEstSucc_CdataEsting_Ehrpd(ucPdpId, pstMsg);
    }
    else if (EHSM_APS_CAUSE_EHRPD_SUSPEND == pstPdnActCnf->enCause)
    {
        /* Ǩ����Suspend״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);
    }
    else
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstPdnActCnf->enCause);



        /* ����Ҫ�ز�ʱ������ʧ�ܵĴ��� */
        TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf
 ��������  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��14��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�PS���йҶ���Ӧ�¼� */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ���ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /*------------------------------------------------------------------
    ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
    ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

    ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
    ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf
 ��������  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF��״̬��
             �յ�TI_TAF_APS_CDATA_ESTING��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��16��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֪ͨehsm����ȥ���� */
    TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

    /* ����ʧ�ܵĴ��� */
    TAF_APS_ProcCdataEstFail_CdataEsting(TAF_APS_GetCurrFsmEntityPdpId(),
                                         TAF_PS_CAUSE_EHSM_PPP_ERROR_TIME_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend
 ��������  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND��״̬��
             �յ�ID_EHSM_APS_PDN_ACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��21��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    VOS_UINT32                          ulRemainTimeLen;
    VOS_UINT8                           ucPdpId;

    ulRemainTimeLen = 0;
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��ʱ��ʣ��ʱ�� */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_CDATA_ESTING, ucPdpId, &ulRemainTimeLen);

    /* ���ʣ��ʱ����0, ֹͣ��ǰ����, ���´���ǰ��״̬�������Ϣ */
    if (0 != ulRemainTimeLen)
    {
        /* ��¼ʣ��ʱ�� */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* ֹͣ�������̶�ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����״̬�������Ϣ���ڲ���Ϣ���� */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend
 ��������  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND��״̬��
             �յ�TI_TAF_APS_CDATA_ESTING��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��21��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_APS_TIME_OUT);

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend
 ��������  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND��״̬��
             �յ�ID_MSG_TAF_PS_CALL_END_REQ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��21��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ�������̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING,
                      ucPdpId);

    /* �ϱ�PDP�������, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                          pstPsCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE, �˳���״̬�� */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;

}
VOS_UINT32 TAF_APS_RcvPsInterSrvStaChangeReq_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID�͵�ǰ���뼼�� */
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();

    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

    /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */
    switch (enCurrRatType)
    {
        case TAF_APS_RAT_TYPE_HRPD:
            TAF_APS_ProcCdataCallOrig_CdataEsting_HrpdMode(ucPdpId, VOS_FALSE);

            break;
        case TAF_APS_RAT_TYPE_EHRPD:
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ) == pstEntryMsg->ulEventType)
            {
                TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PS_CALL);
            }

            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ) == pstEntryMsg->ulEventType)
            {
                TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PPP_DIAL);
            }

            break;
        case TAF_APS_RAT_TYPE_1X:
            TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_FALSE, VOS_TRUE, VOS_FALSE);
            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_RcvPsInterSvcStaChangeReq_CdataEsting_Suspend: Wrong RAT type!");
            break;
    }
    /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-6, end */

    return VOS_TRUE;

}


/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */
#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


