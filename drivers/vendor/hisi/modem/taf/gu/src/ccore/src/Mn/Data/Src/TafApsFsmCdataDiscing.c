

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include  "TafApsFsmCdataDiscing.h"
#include  "TafApsFsmCdataDiscingTbl.h"
#include  "Taf_Aps.h"
#include  "TafLog.h"
#include  "TafApsCtx.h"
#include  "xcc_taf_pif.h"
#include  "MnApsComm.h"
#include  "TafApsSndInternalMsg.h"
#include  "TafApsSndXcc.h"
#include  "TafApsSndPpp.h"
#include  "xcc_aps_pif.h"
#include  "TafApsFsmMainTbl.h"
#include  "TafApsComFunc.h"
#include  "TafApsSndCds.h"
#include  "taf_aps_ppp_pif.h"
#include  "TafApsFsmCdataEstingTbl.h"
#include  "TafApsProcIpFilter.h"
#include  "TafApsSndHsm.h"
#include  "TafApsProcEpdszid.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-16, begin */
#include  "TafApsSndEhsm.h"
#include  "TafApsSndNd.h"
#include  "TafApsSndDhcp.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-16, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
#include "cnas_cttf_hrpd_pa_pif.h"
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_DISCING_C


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing_Init(
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ������״̬ */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    switch (TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        case TAF_APS_RAT_TYPE_HRPD:
            /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
            /* ��RLPȥע����������״̬�Ļص�������ֹͣ��ʱ */
            CTTF_HRPD_RPA_DeregDormancyMonitor();
            /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

            /* ��HSM������ϢID_APS_HSM_DISC_REQ */
            TAF_APS_SndHsmDiscReq(ucPdpId);

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF);

            break;

        case TAF_APS_RAT_TYPE_1X:
            /* ��XCC������ϢID_APS_XCC_HANGUP_DATA_CALL_REQ */
            TAF_APS_SndXccHangUpDataCallReq(pstPdpEntity->stCdataInfo.ucCallId,
                                            enEndReason);

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF);

            break;

        /* Added by y00314741 for CDMA Iteration 15, 2015-5-15, begin */
        case TAF_APS_RAT_TYPE_EHRPD:
            /* EHRPDģʽ�²�����ȥע���������ݵĻص����� */

            /* ��EHSM������ϢID_APS_EHSM_PDN_DEACTIVATE_REQ */
            TAF_APS_SndEhsmPdnDeactReq(ucPdpId);
            TAF_APS_SndDhcpDeactInd(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)
            /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
            if ((TAF_APS_CheckPrimaryPdp(ucPdpId))
             && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
            {
                TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }
#endif

            /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);

            break;
        /* Added by y00314741 for CDMA Iteration 15, 2015-5-15, end */

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_ProcCdataDisc_CdataDiscing_Init: Wrong RAT type!");

            return VOS_TRUE;
    }

    /* ������ʱ��TI_TAF_APS_CDATA_DISCING */
    TAF_APS_StartTimer(TI_TAF_APS_CDATA_DISCING,
                       TI_TAF_APS_CDATA_DISCING_LEN,
                       ucPdpId);

    return VOS_TRUE;

}


VOS_UINT32  TAF_APS_RcvPsCallEnterDormantInd_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvPppDeactNtf_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_RcvPppDeactCnf_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �����ǰ��1Xģʽ����Ҫԭ��ֵ�������HRPD����Ҫ */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* ����ԭ��ֵ��PPP״̬�ж��Ƿ���Ҫ֪ͨPPPֱ�ӶϿ� */
    if ((TAF_XCC_CAUSE_SO_REJ == pstDiscInd->enCause)
      &&(TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_APS_MapXccCause(pstDiscInd->enCause));

    return VOS_TRUE;
}



VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��PPP״̬�Ǽ���� */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ��Ҫ֪ͨPPPȥ���� */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
    }

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvPsInterEpdszidReOrigReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;

    /* Get Pdp Entity */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* If Discing is not caused by ID_MSG_TAF_PS_CALL_END_REQ and ID_PPP_APS_DEACT_NTF, Set  Epdszid Re-orig secne */
    if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) != pstEntryMsg->ulEventType)
     && (TAF_BuildEventType(MSPS_PID_PPPC, ID_PPP_APS_DEACT_NTF)    != pstEntryMsg->ulEventType))
    {
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_ENTER_DORMANT);
    }

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing(
    TAF_PS_CAUSE_ENUM_UINT32                enCause
)
{
    VOS_UINT8                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                 *pstEntryMsg;
    TAF_APS_INTER_END_CDMA_CALL_REQ_STRU   *pstEndCdmaCall;
    VOS_UINT32                              ulNeedStartTimer;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstEndCdmaCall  = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU*)pstEntryMsg->aucEntryMsgBuffer;

    /* �ж��Ƿ�����Dormant TI */
    ulNeedStartTimer  = VOS_FALSE;

    /* ������û�����ĹҶϣ��ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
    if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
     || ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
      && (TAF_APS_INTER_END_CALL_SCENE_USER_END == pstEndCdmaCall->enEndScene)))
    {
        /* ֹͣ����ͳ�� */
        /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */
        /* ���õ�ǰ���ݷ���ģʽ */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_GetCurrPdpEntityRatType());
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, end */

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF�¼� */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL == pstEndCdmaCall->enEndScene))
    {
        /* ����ʱ��Ҫ���û��ϱ�REJ��Ϣ */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));
    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_HANDOFF == pstEndCdmaCall->enEndScene))
    {
        /* ���õ�ǰ���ݷ���ģʽ */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */
    else
    {
        if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
        {
            /* ���֮ǰ��Active״̬��20sû������������Dormant״̬����Ҫ����Dormant Timer */
            if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND) == pstEntryMsg->ulEventType)
            {
                if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
                {
                    ulNeedStartTimer = VOS_TRUE;
                }
                else
                {
                    ulNeedStartTimer = VOS_FALSE;
                }
            }

            TAF_APS_PdpEntityEnterDormant(ucPdpId, ulNeedStartTimer);

            /* ����Dormant״̬�󣬴����ڲ���Ϣ�������ز�*/
            if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
            {
                TAF_APS_SndInterEpdszidReOrigReq();

                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
            }

            /* �˳���״̬�� */
            TAF_APS_QuitCurrSubFsm();

            return VOS_TRUE;
        }
        else
        {
            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));

        }
    }

    /* �ͷ���Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* �˳���״̬�� */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF״̬��
             �յ�ID_HSM_APS_DISC_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* �����ǰ��PPP״̬�Ǽ���� */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ��Ҫ֪ͨPPPȥ���� */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
    }

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvHsmDiscInd_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF״̬��
             �յ�TI_TAF_APS_CDATA_DISCING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��02��04��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�ID_EHSM_APS_PDN_DEACTIVATE_CNF��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstDeactCnf;

    /* ��ȡʵ����Ϣ */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    if (EHSM_APS_CAUSE_LAST_PDN == pstDeactCnf->enCause)
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* ��������PDNȥ���EHSM��ܾ������ݴ��ض�ԭ��ֵ�������⴦����ʱ
           ��ʵ�岻��ʵ��ȥ������ǻ�ˢ�³�Ĭ�ϳ��أ�ʵ��״̬����Ϊ����״̬ */

        /* ˢ�³�Ĭ�ϳ��ص�CID */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    TAF_APS_DEFAULT_CID,
                                    TAF_APS_INVALID_MODULEID,
                                    TAF_APS_INVALID_CLIENTID,
                                    TAF_APS_INVALID_OPID);
        /* ֪ͨEHSM��ǰ��Cidˢ�� */
        TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);

        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;

    }
    else if(EHSM_APS_CAUSE_EHRPD_SUSPEND == pstDeactCnf->enCause)
    {
        /* Ǩȥ����Suspend״̬ */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND);

    }
    else
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* �������ӶϿ����� */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�ID_EHSM_APS_PDN_DEACTIVATE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֹͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�TI_TAF_APS_CDATA_DISCING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��05��15��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡʵ����Ϣ */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* ֪ͨehsm����ȥ���� */
    TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF״̬��
             �յ�ID_ESM_SM_EPS_BEARER_INFO_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��6��6��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ͣ������ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

    /* ��ȡ��ǰ��״̬�������Ϣ��EVENTTYPE */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* �������Ϣ�е�3GPP״̬������ */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType )
    {
        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        /* ���½�ȥ���������ͳ�������������3GPP״̬������ */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

    }

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
    {
        /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* �˳���״̬�� */
        TAF_APS_QuitCurrSubFsm();

        /* ���½��ڲ�ȥ���������ͳ�������������3GPP״̬������ */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);

    }

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND״̬��
             �յ�TI_TAF_APS_CDATA_DISCING��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��6��6��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* �������ӶϿ����� */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend
 ��������  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND״̬��
             �յ�ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND��Ϣ�Ĵ���
 �������  : ulEventType                - ��ϢID
             pstMsg                     - ��Ϣָ��
 �������  : ��
 �� �� ֵ  : VOS_FALSE:��Ϣ����δ��ɣ���Ҫ��������
             VOS_TRUE:��Ϣ������ɣ���������Ҫ��������

 �޸���ʷ      :
  1.��    ��   : 2015��06��08��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* ��ȡ��Ϣ���� */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();

    if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        /* ��EHSM������ϢID_APS_EHSM_PDN_DEACTIVATE_REQ */
        TAF_APS_SndEhsmPdnDeactReq(ucPdpId);

        /* ״̬Ǩ�Ƶ�TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);
    }
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

        /* �������Ϣ�е�3GPP״̬������ */
        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
        {
            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* �˳���״̬�� */
            TAF_APS_QuitCurrSubFsm();

            /* ���½�ȥ���������ͳ�������������3GPP״̬������ */
            TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        }

        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
        {
            /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* �˳���״̬�� */
            TAF_APS_QuitCurrSubFsm();

            /* ���½��ڲ�ȥ���������ͳ�������������3GPP״̬������ */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);
        }
    }
    else
    {
        /* ֹͣ������ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* �˳���״̬״̬�� */
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;
}


/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
