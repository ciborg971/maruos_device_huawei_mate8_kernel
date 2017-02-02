
/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "TafTypeDef.h"
#include "TafApsApi.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "MmcApsInterface.h"
#include "TafLog.h"
#include "TafApsCtx.h"
#include "TafApsFsmMain.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsFsmMsActivatingTbl.h"
#include "TafApsFsmMsDeactivatingTbl.h"
#include "TafApsFsmMsModifyingTbl.h"
#include "TafApsFsmNwActivatingTbl.h"
#include "TafApsFsmMsDeactivating.h"
#include "TafApsProcIpFilter.h"
#include "TafApsSndAt.h"
#include "TafApsSndInternalMsg.h"
#include "TafApsSndRabm.h"
#include "TafApsSndSm.h"
#if (FEATURE_ON == FEATURE_LTE)
#include "SmEsmInterface.h"
#include "MnApsMultiMode.h"
#include "ApsL4aInterface.h"
#include "TafApsSndL4a.h"
#endif
#include "ApsNdInterface.h"
#include "TafApsSndNd.h"
#include "TafApsComFunc.h"

#include "TafApsFsmCdataEstingTbl.h"
#include "TafApsFsmCdataDiscingTbl.h"
#include "TafMmaInterface.h"
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
#include "xcc_aps_pif.h"
#include "hsm_aps_pif.h"
#include "TafApsFsmCdataHandOff.h"
#endif
#include "TafApsSndCds.h"
#include "TafApsSndPpp.h"
#include "taf_aps_ppp_pif.h"
/* Added by y00314741 for CDMA Iteration 11, 2015-3-24, begin */
#include "TafApsSndXcc.h"
#include "TafApsFsmCdataHandOffTbl.h"
/* Added by y00314741 for CDMA Iteration 11, 2015-3-24, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-5-21, begin */
#include "TafApsSndNd.h"
#include "TafApsSndEhsm.h"
#include "TafApsSndDhcp.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-21, end */
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
#include "cnas_cttf_hrpd_pa_pif.h"
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

#include "TafApsProcEpdszid.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MAIN_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* PDP����������� */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /*-------------------------------------------------------
           ����TAF_APS_STA_MS_ACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_ACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_ACTIVATING_SUBSTA_INIT��״̬�д���
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        -------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    else
    {
        /* ָ��ȥ�����CID����δ����״̬, ��Ԥ�������Ѿ�����, ���ﲻ�ٴ��� */
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvAtSetPdpContextStateReq_Inactive: Wrong operation");
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       ƽ̨����֧��CDMA���ҵ�ǰפ��ģʽ���Ϊ3GPP2��NULL,
       ��ѡ��3GPP2���̣�����ѡ��3GPP����

       NULL״̬���յ�MMA�ϱ��ķ���״̬��Ϣ��
       ���ΪLTEģʽ���˳�TAF_APS_FSM_CDATA_ESTING״̬����
       ���¼���TAF_APS_STA_MS_ACTIVATING״̬��

       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/

    if (VOS_TRUE == TAF_APS_IsEnterCdataEsting())
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }
    else
#endif
        /*-------------------------------------------------------
           ����TAF_APS_STA_MS_ACTIVATING״̬��
           ���غ���״̬�л�ΪTAF_APS_MS_ACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_ACTIVATING_SUBSTA_INIT��״̬�д���
           ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ��Ϣ
        -------------------------------------------------------*/
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /*-------------------------------------------------------
       ƽ̨����֧��CDMA���ҵ�ǰפ��ģʽ���Ϊ3GPP2��NULL,
       ��ѡ��3GPP2���̣�����ѡ��3GPP����

       NULL״̬���յ�MMA�ϱ��ķ���״̬��Ϣ��
       ���ΪLTEģʽ���˳�TAF_APS_FSM_CDATA_ESTING״̬����
       ���¼���TAF_APS_STA_MS_ACTIVATING״̬��

       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/

    if (VOS_TRUE == TAF_APS_IsEnterCdataEsting())
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }
    else
#endif
    /*-------------------------------------------------------
       ����TAF_APS_STA_MS_ACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_ACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_ACTIVATING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    {
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpActivateInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* ��ȡ��ǰ����ģʽ*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* ��鵱ǰģ�Ƿ�ΪGU, �������, ��������Ϣ */
    if ( (TAF_APS_RAT_TYPE_GSM   != enCurrRatType)
      && (TAF_APS_RAT_TYPE_WCDMA != enCurrRatType) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSmPdpActivateInd_Inactive: Current RAT is not GSM/WCDMA!");
        return VOS_TRUE;
    }

     /* Ǩ�Ƶ���״̬TAF_APS_NW_ACTIVATING_SUBSTA_INIT,����״̬
        TAF_APS_NW_ACTIVATING_SUBSTA_INIT�д��� ID_SMREG_PDP_ACTIVATE_IND
        ��Ϣ
     */
    TAF_APS_InitSubFsm(TAF_APS_FSM_NW_ACTIVATING,
                       TAF_APS_GetNwActivatingFsmDescAddr(),
                       TAF_APS_NW_ACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;

}

#if (FEATURE_ON == FEATURE_LTE)

VOS_UINT32 TAF_APS_RcvL4aPdpActivateInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* ��ȡ��ǰ����ģʽ*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* ��鵱ǰģ�Ƿ�ΪLTE, �������, ��������Ϣ */
    if (TAF_APS_RAT_TYPE_LTE != enCurrRatType)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvL4aPdpActivateInd_Inactive: Current RAT is not LTE!");
        return VOS_TRUE;
    }

    /* Ǩ�Ƶ���״̬TAF_APS_NW_ACTIVATING_SUBSTA_INIT,����״̬
       TAF_APS_NW_ACTIVATING_SUBSTA_INIT�д��� ID_L4A_APS_PDP_ACTIVATE_IND
       ��Ϣ
    */
    TAF_APS_InitSubFsm(TAF_APS_FSM_NW_ACTIVATING,
                       TAF_APS_GetNwActivatingFsmDescAddr(),
                       TAF_APS_NW_ACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#if (FEATURE_ON == FEATURE_IPV6)
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
#endif
    VOS_UINT8                           ucPdpId;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;

#if (FEATURE_ON == FEATURE_IPV6)
    /* ��ȡ��ǰ����ģʽ*/
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();
#endif
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_ACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptActivate(pstPdpEntity, pstBearerInfo);

        if (TAF_APS_DEFAULT_CID == TAF_APS_GetCidFromLteBitCid(pstBearerInfo->ulBitCid))
        {
            TAF_APS_SndInterAttachBearerActivateInd();
        }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-16, begin */
        if (TAF_APS_RAT_TYPE_1X != TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            /* ��¼��ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

            /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);
        }
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-16, end */
#endif

#if (FEATURE_ON == FEATURE_IPV6)
        /* �����ַ������IPv6, ��Ҫͬ����ND Client */
        if ( (TAF_APS_RAT_TYPE_NULL != enCurrRatType)
          && (TAF_APS_CheckPrimaryPdp(ucPdpId))
          && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
#endif
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    return VOS_TRUE;
}
#endif



VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT32                          ulBearerActivateFlg;
    VOS_UINT8                           ucCidValue;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq                = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���ü����� */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /* ��ǰ�Ȳ�֧��һ���Լ�����PDP�ĳ�����һ�μ���һ��������ҵ�һ��Ҫ����� CID */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpCtxStateReq->stCidListStateInfo.aucCid);

    /* PDP����������� */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCidValue))
        {
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                         TAF_PS_CAUSE_SUCCESS);
        }

        TAF_APS_SetCallRemainTmrLen(ucCidValue, 0);

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCidValue);

#if (FEATURE_ON == FEATURE_IPV6)
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
        if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
        {
            /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
            TAF_APS_SndIpv6RaInfoNotifyInd(&(pstSetPdpCtxStateReq->stCtrl),
                                           ucCidValue,
                                           pstPdpEntity->ucNsapi,
                                           (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
        }
#endif

        /* ����ɹ�����������ͳ�� */
        TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
    else
    {
        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_STA_MS_DEACTIVATING
           ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsPppDialOrigReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid))
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid, 0);

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
    TAF_APS_SndPdpActivateCnf(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
    {
        /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstPppDialOrigReq->stCtrl),
                                       pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif

    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvAtPsCallOrigReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#if (FEATURE_ON == FEATURE_IPV6)
    TAF_PDP_TYPE_ENUM_UINT8             enPdpType;
#endif


    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ���CID��Ӧ��ʣ�ඨʱ��ʱ��Ϊ0, ��Ҫ�ϱ���Ӧ�¼� */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                               pstCallOrigReq->stDialParaInfo.ucCid,
                               TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid, 0);

    /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, begin */
    /* ��ehrpd�£���ǰ�Ѿ����initial attach������Ĭ�ϳ���cid=0��
        ����dhcpЭ�̿��ܻ�û��Э�����,��ʱ���ϱ���Э�̽����ϱ� */
    if (VOS_FALSE == pstPdpEntity->ucNeedGetDnsFlg)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF�¼� */
        TAF_APS_SndPdpActivateCnf(ucPdpId, pstCallOrigReq->stDialParaInfo.ucCid);
    }
    /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, end */

#if (FEATURE_ON == FEATURE_IPV6)
    enPdpType    = pstCallOrigReq->stDialParaInfo.enPdpType;

    if ( ((TAF_PDP_IPV6 == enPdpType) || (TAF_PDP_IPV4V6 == enPdpType))
      && (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo) )
    {
        /* �ϱ�ID_EVT_TAF_PS_IPV6_INFO_IND�¼� */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstCallOrigReq->stCtrl),
                                       pstCallOrigReq->stDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif

    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstCallEndReq;
    VOS_UINT8                           ucPdpId;
    TAF_APS_CDATA_PPP_STATE_ENUM_UINT8  enPppState;

    /*-------------------------------------------------------
       ƽ̨����֧��CDMA���ҵ�ǰפ��ģʽ���Ϊ3GPP2,
       ��ѡ��3GPP2���̣�����ѡ��3GPP����

       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
    -------------------------------------------------------*/
    if (VOS_TRUE == TAF_APS_IsEnterCdataDiscing())
    {
        /* ��ȡ��Ϣ���� */
        pstAppMsg       = (TAF_PS_MSG_STRU *)pstMsg;
        pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU *)(pstAppMsg->aucContent);
        ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

        /* �ϱ�PS���йҶ���Ӧ�¼� */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* ������״̬���������Ϣ */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

        TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

        enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

        /* ��ǰ���ݷ�����EHRPD�ϣ������м�ģʽ��(PPPδ������)������ȥ����״̬�� */
        if ((TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
         || (TAF_APS_CDATA_PPP_STATE_INACTIVE == enPppState))
        {
            /* ����TAF_APS_FSM_CDATA_DISCING״̬�� */
            TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                               TAF_APS_GetCdataDiscingFsmDescAddr(),
                               TAF_APS_CDATA_DISCING_SUBSTA_INIT);
        }
        else if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState)
        {
            /* ��PPP������ϢID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* ������ʱ��TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                               TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF_LEN,
                               ucPdpId);
        }
        else if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == enPppState)
        {
            /* ��PPP������ϢID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

            /* ������ʱ��TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                               TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF_LEN,
                               ucPdpId);

        }
        else
        {
            /* ������ڲ����µ�ȥ���ֻ����������Ϣ */
        }
    }
    else
#endif
    {
        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_STA_MS_DEACTIVATING
           ��״̬Ǩ����TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_END_REQ��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                           TAF_APS_GetMsDeactivatingFsmDescAddr(),
                           TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    }
    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallModifyReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_MODIFYING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_MODIFYING_SUBSTA_INIT

       ��TAF_APS_MS_MODIFYING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_MODIFY_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_MODIFYING,
                       TAF_APS_GetMsModifyingFsmDescAddr(),
                       TAF_APS_MS_MODIFYING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallAnswerReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ANSWER_REQ_STRU        *pstCallAnswerReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallAnswerCnf(&(pstCallAnswerReq->stCtrl),
                            pstCallAnswerReq->stAnsInfo.ucCid,
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvAtPsCallHangupReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_HANGUP_REQ_STRU        *pstCallHangupReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS��MT��������, ����δȷ��, Ŀǰֱ�ӷ���ERROR */
    TAF_APS_SndCallHangupCnf(&(pstCallHangupReq->stCtrl),
                            TAF_ERR_UNSPECIFIED_ERROR);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;
    APS_MDFIND_PARA_ST                  stParam;
    SMREG_PDP_MODIFY_IND_STRU          *pstSmPdpModifyInd;
#if (FEATURE_ON == FEATURE_LTE)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif

    /* ��ȡ��Ϣ���� */
    pstSmPdpModifyInd = (SMREG_PDP_MODIFY_IND_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType     = TAF_APS_GetCurrPdpEntityRatType();
#if (FEATURE_ON == FEATURE_LTE)
    pstPdpEntity      = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

    ulResult = Aps_PdpMdfIndParaCheck(pstSmPdpModifyInd, &stParam);
    if (APS_PARA_INVALID  == ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSmPdpModifyInd_Active: Check para failed! ");

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* ���QOS�Ƿ�����MIN */
    if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.NewQos))
    {
        /* ����MINQOS */
        Aps_PdpMdfIndQosSatisfy(ucPdpId, &stParam, pstSmPdpModifyInd);

#if (FEATURE_ON == FEATURE_LTE)
        /* ͬ��PDP��Ϣ��ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_MODIFY);
#endif

        /* �����ǰģΪGSM, Ǩ��״̬ */
        if (TAF_APS_RAT_TYPE_GSM == enCurrRatType)
        {
            /*------------------------------------------------------------------
               ����TAF_APS_STA_MS_MODIFYING״̬��
               ���غ���״̬�л�ΪTAF_APS_MS_MODIFYING_SUBSTA_INIT

               ��TAF_APS_MS_MODIFYING_SUBSTA_INIT��״̬��
               ����D_PMC_SMREG_PDP_MODIFY_IND��Ϣ
            ------------------------------------------------------------------*/
            TAF_APS_InitSubFsm(TAF_APS_FSM_MS_MODIFYING,
                               TAF_APS_GetMsModifyingFsmDescAddr(),
                               TAF_APS_MS_MODIFYING_SUBSTA_INIT);
        }
    }
    else
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_QOS_NOT_ACCEPTED);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSmPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    SMREG_PDP_DEACTIVATE_IND_STRU      *pstSmPdpDeactivateInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* ͬ��PDP״̬����Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_LTE)
VOS_UINT32 TAF_APS_RcvL4aPdpModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_L4A_PDP_MODIFY_IND_STRU        *pstPdpModify;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    pstPdpModify = (APS_L4A_PDP_MODIFY_IND_STRU*)pstMsg;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* �������Ĭ�ϳ��أ����ϱ���Ĭ�ϳ��ز��ϱ� */
    if (TAF_APS_DEFAULT_CID != pstPdpModify->ucCid)
    {
        if (VOS_TRUE == pstPdpModify->bitOpEpsQos)
        {
            pstPdpEntity->bitOpEpsQos   = VOS_TRUE;
            PS_MEM_CPY((VOS_UINT8 *)&pstPdpEntity->stEpsQos,
                       (VOS_UINT8 *)&pstPdpModify->stEpsQosInfo,
                       sizeof(APS_L4A_EPS_QOS_STRU));
        }

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_MODIFIED_IND�¼� */
        TAF_APS_SndPdpModifyInd(ucPdpId);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvL4aPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_L4A_PDP_DEACTIVATE_IND_STRU    *pstL4aPdpDeactivateInd;

    /* ��ȡ��Ϣ���� */
    pstL4aPdpDeactivateInd = (APS_L4A_PDP_DEACTIVATE_IND_STRU*)pstMsg;

    /* ��ȡ��ǰ״̬����APS���� */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��������APSʵ�����ݵ�ַ */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* �������Ĭ�ϳ��أ����ϱ���Ĭ�ϳ��ز��ϱ� */
    if (TAF_APS_DEFAULT_CID != pstPdpEntity->stClientInfo.ucCid)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼��ϱ� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapL4aCause(pstL4aPdpDeactivateInd->ulEsmCause));
    }
    else
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif
    }

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvL4aPdpSetupInd_Active
 ��������  : �յ�ID_L4A_APS_PDP_SETUP_IND��Ϣ�Ĵ���
 �������  : ulEventType: ��Ϣ����
             pstMsg     : ID_L4A_APS_PDP_SETUP_IND��Ϣ
 �������  : ��
 �� �� ֵ  : VOS_FALSE  : ������Ϣʧ��
             VOS_TRUE   : ������Ϣ�ɹ�
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��11��19��
    ��    ��   : w00316404
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvL4aPdpSetupInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

#if (FEATURE_ON == FEATURE_IMS)
    /* ����IMSר�г��� */
    TAF_APS_ProcImsDedicateBearer(pstPdpEntity);
#endif

    /* ����ɹ�����������ͳ�� */
    TAF_APS_StartDsFlowStats(pstPdpEntity->ucNsapi);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvEsmSmEpsBearerInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    TAF_APS_EPS_BEARER_INFO_IND_STRU   *pstBearerInfo;

    pstBearerInfo = (TAF_APS_EPS_BEARER_INFO_IND_STRU*)pstMsg;
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* ����EPS���صĲ�������(Activate, Deactivate, Modify),
       ������Ӧ�Ĵ����� */
    if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-8, begin */
        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            /* �����ڲ���Ϣ���������ڼ�������е�״̬������Ҫ�������Ϣ */
            TAF_APS_SndInterAttachBearerActivateInd();
            /* ��¼��ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);
            /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);

            TAF_APS_SET_CDATA_MTU(0);
        }
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-8, end */

        /* �ϱ���AP */
        TAF_APS_SndCgmtuValueChangeInd(0);

#endif
    }
    else if (SM_ESM_PDP_OPT_DEACTIVATE == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptDeactivate(pstPdpEntity, pstBearerInfo);
    }
    else
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,"TAF_APS_RcvEsmSmEpsBearerInfoInd_Inactive: Wrong option.");
    }

    return VOS_TRUE;
}
#endif


VOS_UINT32 TAF_APS_RcvSndcpActivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulResult;
    VOS_UINT8                           ucPdpId;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    APS_SNDCP_ACTIVATE_RSP_ST          *pstSnActivateRsp;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ulResult         = VOS_OK;
    pstSnActivateRsp = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId          = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* �����Ϣ���� */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_Active: Check para failed!");

        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* �յ�SN_ACT_RSP���޸�APSʵ�����, ����XID����, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* ����RABM�Ĵ���ģʽ */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ��TAF_APS_STA_ACTIVE״̬��, Ŀǰ����Ҫ����APS_SN_DEACT_RSP_MSG_TYPE */

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvSndcpStatusReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT32                          ulRslt;
    VOS_UINT8                           ucPdpId;
    APS_SNDCP_STATUS_REQ_ST            *pstSnStatusReq;

    pstSnStatusReq = &((APS_SNDCP_STATUS_REQ_MSG*)pstMsg)->ApsSnStatusReq;
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();

    ulRslt = TAF_APS_ValidatePdpForSnStatusReq(ucPdpId, pstSnStatusReq);
    if (VOS_TRUE == ulRslt)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* �����ڲ���Ϣ, ����PDPȥ�������� */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvRabmSysChgToGprs_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���SNDCP�����ʶ, ����SNDCP */
    if (APS_SNDCP_INACT == TAF_APS_GetPdpEntSndcpActFlg(ucPdpId))
    {
        Aps_RabmMsgActSndcp(ucPdpId);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvRabmLocalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrRatType;

    /* ��ȡ��ǰ״̬���Ľ��뼼�� */
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��GUģ�´������Ϣ, LTEģֱ�Ӷ��� */
    if (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE);

        /* �����ڲ���Ϣ, ȥ����PDP */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_REGULAR_DEACTIVATION);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvApsInternalPdpDeactivateReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /*------------------------------------------------------------------
       ����TAF_APS_STA_MS_DEACTIVATING״̬��
       ���غ���״̬�л�ΪTAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       ��TAF_APS_MS_DEACTIVATING_SUBSTA_INIT��״̬�д���
       ID_APS_APS_INTER_PDP_DEACTIVATE_REQ��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_MS_DEACTIVATING,
                       TAF_APS_GetMsDeactivatingFsmDescAddr(),
                       TAF_APS_MS_DEACTIVATING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvApsLocalPdpDeactivateInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                               ucPdpId;
    TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU  *pstLocalMsg;
    APS_PDP_CONTEXT_ENTITY_ST              *pstPdpEntity;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstLocalMsg                         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;
    ucPdpId                             = pstLocalMsg->ucPdpId;
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ����ͳ�� */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* ͬ��PDP״̬����Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* ��SM���ͱ���ȥ�������� */
    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ȱʡ�����ҵ�ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* ���SNDCP�Ѿ�����, �ͷ�SNDCP��Դ */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼� */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP������ */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IPV6)
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
#endif
    VOS_UINT8                           ucPdpId;

    /* ��ȡ��Ϣ���� */
    pstServStaChangeInd  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* ��ȡ��ǰ״̬����APSʵ������ */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

#if (FEATURE_ON == FEATURE_IPV6)
    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* �����ַ������IPv6, ��Ҫͬ����ND Client */
    if ( (TAF_APS_RAT_TYPE_NULL != pstServStaChangeInd->enRatType)
      && (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        if (VOS_TRUE != pstPdpEntity->ulNdClientActiveFlg)
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;
        }
    }
#endif

    switch (pstServStaChangeInd->enRatType)
    {
        /* ��ǰģΪGSMʱ, ����������Ϣ����SNDCP */
        case TAF_APS_RAT_TYPE_GSM:
            break;

        /* ��ǰģΪWCDMA/LTEʱ, ��Ҫȥ����SNDCP */
        case TAF_APS_RAT_TYPE_WCDMA:
        case TAF_APS_RAT_TYPE_LTE:
            if (APS_SNDCP_ACT == TAF_APS_GetPdpEntSndcpActFlg(ucPdpId))
            {
                Aps_RabmMsgDeActSndcp(ucPdpId);
            }

        /* TODO:���֮ǰ���ؽ�����HRPD����1X�ϵģ���Ҫ����ȥ���������AP��ȥ���� */

            break;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_APS_RAT_TYPE_1X:
            /* TO DO: ԭ����LTE������޸� */
            /* ͬ��PDP��Ϣ��ESM */
#if (FEATURE_ON == FEATURE_LTE)
            if (TAF_APS_RAT_TYPE_LTE == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);
                // to do :֪ͨL4A�Ͽ� ?
                /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */

                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
                /* ����ȥ���� */
                TAF_APS_LocalReleaseProc(ucPdpId);
                /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-6, end */
            }
#endif
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* �ϱ�ȥ������¼� */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

                /* ����ȥ���� */
                TAF_APS_LocalReleaseProc(ucPdpId);
            }
#endif
            break;
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, end */
#endif
        case TAF_APS_RAT_TYPE_NULL:
        default:
            break;
    }

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 TAF_APS_RcvXccDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId              = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity         = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd           = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    if ((TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
     && (TAF_PS_CAUSE_XCC_AS_SO_REJ != pstPdpEntity->enCause))
    {
        TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_TRUE);
    }
    else
    {
        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        TAF_APS_SndPppDeactInd(ucPdpId);

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ�¼� */
            TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);
        }
        else if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);

            /* �ϱ�ȥ������¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            /* PPP��ACTIVE״̬�£��յ������SO_REJ���ϱ�ȥ������¼� */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);
        }

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsCallEnterDormantInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        /* EHRPDģʽ��ֻ֪ͨEHSM����DORMANT״̬��APS��״̬���ı� */
        TAF_APS_SndEhsmDiscNtf();
    }
    else
    {
        /*------------------------------------------------------------------
           ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
           ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

           ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
           ����ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND��Ϣ
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);
    }


    return VOS_TRUE;
}



VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_APS_CDATA_EPDSZID_STRU         *pstCurrEpdszid;

    pstCurrEpdszid = TAF_APS_GetCurrEpdszidInfo();

    /* Add EPDSZID into Packet Zone List */
    TAF_APS_AddEpdszidToZoneList(pstCurrEpdszid);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXccUpdateDataCallInfoInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU     *pstDataCallInof = VOS_NULL_PTR;
    VOS_UINT8                                   ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDataCallInof = (XCC_APS_UPDATE_DATA_CALL_INFO_IND_STRU *)pstMsg;

    /* Only Update SR_ID Now */
    if (pstDataCallInof->ucSrId != TAF_APS_GetPdpEntSrId(ucPdpId))
    {
        TAF_APS_SetPdpEntSrId(ucPdpId, pstDataCallInof->ucSrId);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvCdsServiceInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode;

    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrCdataServiceMode = TAF_APS_GetCurrPdpEntityDataServiceMode();

    if (TAF_APS_RAT_TYPE_EHRPD == enCurrCdataServiceMode)
    {
        TAF_APS_SndEhsmReconnReq(ucPdpId);
    }
    else
    {
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvHsmDiscInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    HSM_APS_DISC_IND_STRU              *pstDiscInd = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (HSM_APS_DISC_IND_STRU *)pstMsg;
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��¼ʧ��ԭ��ֵ */
    pstPdpEntity->enCause = TAF_APS_MapHsmCause(pstDiscInd->enCause);

    /* ���CDATA PS�Ѽ��Ǩ��DORMANT״̬ */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* Added by y00314741 for CDMA Iteration 11, 2015-3-25, begin */
        TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);
        /* Added by y00314741 for CDMA Iteration 11, 2015-3-25, end */

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
        /* ��RLPȥע����������״̬�Ļص�������ֹͣ��ʱ */
        CTTF_HRPD_RPA_DeregDormancyMonitor();
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

    }
    else
    {

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        TAF_APS_SndPppDeactInd(ucPdpId);

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

            /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_REJ�¼� */
            TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);
        }
        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);

            /* �ϱ�ȥ������¼� */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    }

    return VOS_TRUE;
}

VOS_UINT32 TAF_APS_RcvPppActCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_ACT_CNF_STRU               *pstPppActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

    /* �жϵ�ǰPPP״̬��ΪACTIVATING̬�����˳� */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVATING != TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppActCnf_Active: PPP STATUS IS NOT ACTIVING");
        return VOS_TRUE;
    }

    if (VOS_OK == pstPppActCnf->ulResult)
    {
        pstPdpEntity->PdpAddrFlag           = VOS_TRUE;

        if (TAF_APS_PPP_ADDR_TYPE_IPV4 == pstPppActCnf->enPdnType)
        {
            pstPdpEntity->PdpAddr.ucPdpTypeNum  = APS_ADDR_STATIC_IPV4;
            TAF_APS_UpdataCdataIpv4Addr(pstPdpEntity, pstPppActCnf);

            /* ���û��ϱ�ACTIVATE_CNF�¼� */
            TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        }
        else if (TAF_APS_PPP_ADDR_TYPE_IPV6 == pstPppActCnf->enPdnType)
        {
            pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV6;
            TAF_APS_UpdataCdataIpv6Addr(pstPdpEntity, pstPppActCnf);
            /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, begin */
            /* IPV6 RA INFO */
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
            /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, end */

        }
        else if (TAF_APS_PPP_ADDR_TYPE_IPV4V6 == pstPppActCnf->enPdnType)
        {
            pstPdpEntity->PdpAddr.ucPdpTypeNum  = MN_APS_ADDR_IPV4V6;
            TAF_APS_UpdataCdataIpv4Addr(pstPdpEntity, pstPppActCnf);
            TAF_APS_UpdataCdataIpv6Addr(pstPdpEntity, pstPppActCnf);
            /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, begin */
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
            /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, end */
        }
        else
        {
            /* TODO:���IP���ʹ�����Ҫ�ڲ�ȥ����? */
        }

        TAF_APS_SET_CDATA_MTU(pstPppActCnf->usMtu);

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
        /* ����CDATA PS�����״̬ΪACTIVE״̬ */
        TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_ACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVE);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */

        /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

    }
    else
    {
        pstPdpEntity->enCause           = TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL;

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* �����ڲ���ϢID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ��Ϣ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                       TAF_APS_INTER_END_CALL_REASON_PPP_ACT_FAIL,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPppDeactCnf_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    PPP_APS_DEACT_CNF_STRU             *pstDeactCnf = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf     = (PPP_APS_DEACT_CNF_STRU*)pstMsg;

    /* �жϵ�ǰPPP״̬��ΪDEACTIVATING̬�����˳� */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING != TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppDeactCnf_Active: PPP STATUS IS INACTIVE");
        return VOS_TRUE;
    }

    /* ֹͣ���̶�ʱ�� */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* ���PPP�ظ�ʧ�ܣ���ǿ��PPPȥ���� */
    if (VOS_OK != pstDeactCnf->ulResult)
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* ����TAF_APS_FSM_CDATA_DISCING״̬�� */
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPppDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_APS_TIMER_STATUS_ENUM_U8        enTimerStatus;

    /* ��ʼ�� */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    enTimerStatus   = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus)
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);
    }

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_ACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /*------------------------------------------------------------------
       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_PPP_APS_DEACT_IND��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPppModifyInd_Active
 ��������  : ACTIVE��״̬���յ�ID_PPP_APS_MODIFY_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvPppModifyInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    PPP_APS_MODIFY_IND_STRU            *pstModifyInd;
    TAF_PDP_TYPE_ENUM_UINT8             enPdnType;
    VOS_INT32                           lCmpRst;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    lCmpRst        = VOS_ERROR;
    pstModifyInd   = (PPP_APS_MODIFY_IND_STRU*)pstMsg;
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    enPdnType      = TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid);

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (enPdnType != pstModifyInd->enPdnType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;

        return VOS_TRUE;
    }

    /* �ж�PPP������ */
    switch (pstModifyInd->enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:

            lCmpRst = PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpAddr,
                                 pstModifyInd->aucIpv4Addr,
                                 TAF_APS_PPP_IPV4_ADDR_LEN);
            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV6:

            lCmpRst =  PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpV6Addr,
                                  pstModifyInd->aucIpv6Addr,
                                  TAF_APS_PPP_IPV6_ADDR_LEN);

            break;

        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:

            lCmpRst = PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpV6Addr,
                                 pstModifyInd->aucIpv6Addr,
                                 TAF_APS_PPP_IPV6_ADDR_LEN);

            if ((0 != PS_MEM_CMP(pstPdpEntity->PdpAddr.aucIpAddr,
                                 pstModifyInd->aucIpv4Addr,
                                 TAF_APS_PPP_IPV4_ADDR_LEN))
             || (0 != lCmpRst))
            {
                lCmpRst = VOS_ERROR;

            }

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppModifyInd_Active:Wrong Msg Entry");
            break;
    }

    if (0 != lCmpRst)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* ��¼ʧ��ԭ��ֵ */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;
    }

    if (pstModifyInd->usMtu != TAF_APS_GET_CDATA_MTU())
    {
        TAF_APS_SET_CDATA_MTU(pstModifyInd->usMtu);

        TAF_APS_SndCgmtuValueChangeInd(pstModifyInd->usMtu);
    }
    return VOS_TRUE;
}
/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, end */


VOS_UINT32 TAF_APS_RcvTiPppDectCnfExpired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause               = TAF_PS_CAUSE_PPP_TIME_OUT;

    /* ֪ͨPPPȥ���� */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /*------------------------------------------------------------------
       ��״̬Ǩ����TAF_APS_FSM_CDATA_DISCING
       ��״̬Ǩ����TAF_APS_CDATA_DISCING_SUBSTA_INIT

       ��TAF_APS_CDATA_DISCING_SUBSTA_INIT��״̬��
       ����ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND��Ϣ
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;

}


VOS_UINT32 TAF_APS_RcvTiPppActCnfExpired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause               = TAF_PS_CAUSE_PPP_TIME_OUT;

    /* ֪ͨPPPȥ���� */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* �����ڲ���ϢID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
    TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL,
                                   TAF_APS_INTER_END_CALL_REASON_PPP_ACT_TIME_OUT,
                                   ucPdpId,
                                   TI_TAF_APS_CDATA_DISCING_LEN);
    return VOS_TRUE;

}


VOS_UINT32 TAF_APS_RcvInterEndCdmaCallReq_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ������״̬���������Ϣ */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* DORMANT״̬�£��û�����ȥ��������ɹ���PPPȥ����Э�� */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* ��PPP������ϢID_APS_PPP_DEACT_REQ */
        TAF_APS_SndPppDeactReq(ucPdpId);

        /* ����PPP״̬ΪTAF_APS_CDATA_PPP_STATE_DEACTIVATING */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

        /* ������ʱ��TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                           TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF_LEN,
                           ucPdpId);

    }
    else
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
    }
    return VOS_TRUE;
}




/* Modified by y00314741 for CDMA 1X Iteration 11, 2015-3-25, begin */

VOS_UINT32 TAF_APS_RcvPsInterServiceStatusChangeReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                     ucPdpId;
    TAF_APS_RAT_TYPE_ENUM_UINT32                  enCurrCdataServiceMode;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *pstServStaChange = VOS_NULL_PTR;

    /* ��ȡPDP ID */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��ȡ��Ϣ���� */
    pstServStaChange  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /*��ȡ��ǰ�������ݷ����ģʽ*/
    enCurrCdataServiceMode  = TAF_APS_GetCurrPdpEntityDataServiceMode();

    /* ���ݴ�����뼼���ֱ��� */
    if (TAF_APS_RAT_TYPE_HRPD == pstServStaChange->enRatType)
    {
         /* ��1X�л���HRPD */
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            TAF_APS_Proc1xToHrpdHandOff(ucPdpId, pstServStaChange->ucIsNewSession);
        }
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChange->enRatType)
    {
        /* ��HRPD�л���1X */
        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* �����ڲ�HRPD��1X�л�������Ϣ */
            TAF_APS_SndInterHrpdTo1XHandOffReq(ucPdpId);
        }
    }
    /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    else if (TAF_APS_RAT_TYPE_LTE   == pstServStaChange->enRatType)
    {
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            /* ����1X dormant̬ȥ���� */
            TAF_APS_SndInterEnd1xServiceInDormantInd(ucPdpId);
        }

        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* �ϱ�ȥ������¼� */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
            /* ����ȥ���� */
            TAF_APS_LocalReleaseProc(ucPdpId);
        }
    }
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChange->enRatType)
    {
        /* �ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
        /* ����ȥ���� */
        TAF_APS_LocalReleaseProc(ucPdpId);
    }
    /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-4, end */
    else
    {
        ;
    }

    return VOS_TRUE;
}

/* Modified by y00314741 for CDMA 1X Iteration 11, 2015-3-25, end */


VOS_UINT32 TAF_APS_RcvCdsServiceInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if ((TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
     || (TAF_APS_CDMA_TC_SUSPENDED == TAF_APS_GET_CDATA_SUSPEND_STATUS()))
    {
        /* ��CDS����ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND��Ϣ */
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvXccIncomingCallInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* ֹͣDormant ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);
    }

    /*-------------------------------------------------------
       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);


    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsCallOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_ORIG_REQ_STRU          *pstCallOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�����ɹ� */
    TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                           pstCallOrigReq->stDialParaInfo.ucCid,
                           TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsPppDialOrigReq_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_PPP_DIAL_ORIG_REQ_STRU      *pstPppDialOrigReq;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* �ϱ�����ɹ� */
    TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                              TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsCallEndReq_Dormant(
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

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���Dormant Timer�����У�ֱ����PPP����Deact Ind���ϱ�ȥ����ɹ� */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* �ϱ�PS���йҶ���Ӧ�¼� */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* ֹͣDormant ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* �����ǰ��PPP״̬�Ǽ���� */
        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* ��PPP����deact ind */
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* �ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SUCCESS);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }

    if (TAF_PDP_PPP == TAF_APS_GetPdpEntDialPdpType(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId)))
    {
        /* �ϱ�PS���йҶ���Ӧ�¼� */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* ֹͣDormant ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* �ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SUCCESS);

        /* �ͷ�APS��Դ */
        Aps_ReleaseApsResource(ucPdpId);

        /* ����IP���� */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;

    }

    /*-------------------------------------------------------
       DORMANT״̬�£���Ҫ�����½������ӣ�Ȼ���ٶϿ���

       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvPsCallInterEpdszidReOrig_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Get PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* If Dormant Timer is running ,Set Epdszid ReOrig Flag */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* Don't start Re-Orig right now , Only Set the Epdszid Re-Orig scene After Dormant Ti expired */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_REORIG_AFTER_DORMANT_TI_EXPIRED);
    }
    else
    {
        /* Start Re-Orig */
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                           TAF_APS_GetCdataEstingFsmDescAddr(),
                           TAF_APS_CDATA_ESTING_SUBSTA_INIT);
    }

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvTiDormantTimerExpired_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* If Re-Orig Pending Status is TRUE, After Dormant Timer Expired, Start Re-Orig Again */
    if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
    {
        /* Snd Inter Msg To Re-Orig */
        TAF_APS_SndInterEpdszidReOrigReq();

        /* Esting Fsm is started, Set Re-Orig Secne BuTT */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvXccResumeInd_Dormant(

    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* Get PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        return VOS_TRUE;
    }

    /* If Re-Orig Pending Status is TRUE, After Traffic channel exist Expired, Start Re-Orig Again */
    if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
    {
        /* Snd Inter Msg to Re-Orig */
        TAF_APS_SndInterEpdszidReOrigReq();

        /* Esting Fsm is started, Set Re-Orig Secne BuTT */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvHsmCalConnectInd_Dormant
 ��������  : In Dormant State, Receive CONNECT_IND,
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
VOS_UINT32 TAF_APS_RcvHsmCalConnectInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */
/* Added by y00314741 for CDMA Iteration 11, 2015-3-25, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant
 ��������  : �յ��ڲ�1X��HRPD�л���Ϣ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     ����TAF_APS_FSM_CDATA_HANDOFF״̬��
     ���غ���״̬�л�ΪTAF_APS_CDATA_HANDOFF_SUBSTA_INIT

     ��TAF_APS_CDATA_HANDOFF_SUBSTA_INIT��״̬�д���
     ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ��Ϣ
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_HANDOFF,
                       TAF_APS_GetCdataHandOffFsmDescAddr(),
                       TAF_APS_CDATA_HANDOFF_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant
 ��������  : �յ��ڲ�HRPD��1X�л���Ϣ��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��04��01��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     ����TAF_APS_FSM_CDATA_ESTING״̬��
     ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

     ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
     ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ��Ϣ
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-25, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEHsmPdnDeactInd_Active
 ��������  : ACTIVE��״̬���յ�ID_EHSM_APS_PDN_DEACTIVATE_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvEHsmPdnDeactInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    VOS_UINT8                           ucCid;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    EHSM_APS_PDN_DEACTIVATE_IND_STRU   *pstEhsmPdnDeactInd;

    /* ��ȡ��Ϣ���� */
    pstEhsmPdnDeactInd    = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    ucCid                 = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdpEntity          = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ��¼ʧ��ԭ��ֵ */
    pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstEhsmPdnDeactInd->enCause);

    /* �������Ĭ�ϳ��أ����ϱ���Ĭ�ϳ��ز��ϱ� */
    if (TAF_APS_DEFAULT_CID != ucCid)
    {
        /* �ϱ�ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND�¼��ϱ� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);
    }
    else
    {
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
    }

    /* �ͷ�APS��Դ */
    Aps_ReleaseApsResource(ucPdpId);

    /* ����IP���� */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* ��״̬Ǩ����TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvEhsmLteHandoverToEhrpdInd_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU                *pstLteHandoverInd;
    VOS_UINT8                                               ucPdpId;

    pstLteHandoverInd = (EHSM_APS_LTE_HANDOVER_TO_EHRPD_IND_STRU *)pstMsg;
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    if (EHSM_APS_PDN_OPTION_MODIFIED == pstLteHandoverInd->enPdnOption)
    {
        TAF_APS_ProcModifyReq_LteHandoverToEhrpdScene(ucPdpId, pstLteHandoverInd);

        if (pstLteHandoverInd->usMtu != TAF_APS_GET_CDATA_MTU())
        {
            TAF_APS_SET_CDATA_MTU(pstLteHandoverInd->usMtu);

            /* MTU�仯����Ҫ�ϱ���AP */
            TAF_APS_SndCgmtuValueChangeInd(pstLteHandoverInd->usMtu);
        }

        /* ��RLPע����������״̬�Ļص���������ʼ��ʱ */
        CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);
    }
    else if (EHSM_APS_PDN_OPTION_DEACTIVED == pstLteHandoverInd->enPdnOption)
    {
        TAF_APS_ProcLocDeactBear_MsDeactivating_LteMode();
    }
    else
    {
        ;
    }

    /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    /* �����ڲ���Ϣ���������ڼ�������е�״̬����Ҫ�������Ϣ */
    TAF_APS_SndInterAttachBearerActivateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvEhsmPdnActInd_Inactive
 ��������  : ACTIVE��״̬���յ�ID_EHSM_APS_PDN_ACTIVATE_IND��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��19��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActInd_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_IND_STRU     *pstPdnActInd;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    pstPdnActInd = (EHSM_APS_PDN_ACTIVATE_IND_STRU *)pstMsg;

    /* ��ȡ��PDPID��PDPʵ�����ݵ�ַ */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* ����PdnId, APN, PdnAdrr */
    pstPdpEntity->ucNsapi       = pstPdnActInd->ucRabId;
    pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
    pstPdpEntity->ActType       = APS_PDP_ACT_PRI;

    TAF_APS_SetPdpEntCdataPdnId(ucPdpId, pstPdnActInd->ucPdnId);

    TAF_APS_UpdateCdataEhsmPdnInfo(  pstPdpEntity,
                                   &(pstPdnActInd->stPdnAddr),
                                   &(pstPdnActInd->stApn),
                                   &(pstPdnActInd->stIpv4Dns));

    if (TAF_APS_DEFAULT_CID == pstPdnActInd->ucCid)
    {
        TAF_APS_SndInterAttachBearerActivateInd();
    }

    /* ��¼��ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* ֪ͨ�ⲿģ�鵱ǰ��PS�������ڵ�ģʽ */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    TAF_APS_SET_CDATA_MTU(pstPdnActInd->usMtu);

    TAF_APS_SndCgmtuValueChangeInd(pstPdnActInd->usMtu);

    /* ��״̬Ǩ����TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    /* ����Ҫ��ȡIpv4 DNS */
    if (((VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType))
    {
        /* ��RLPע����������״̬�Ļص���������ʼ��ʱ */
        CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);

        return VOS_TRUE;
    }
    else
    {
        /* ��Ҫ��ȡIpv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
         && (((VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))))
        {
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;

            /* ��ʱ��WAIT_DHCP_ACT_IPV4_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF_LEN,
                               ucPdpId);
        }

        /* ��Ҫ��ȡIpv6 DNS */
        if ((EHSM_APS_PDN_TYPE_IPV6   == pstPdnActInd->stPdnAddr.enPdnType)
         || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;

            /* ��ʱ��WAIT_DHCP_ACT_IPV6_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF_LEN,
                               ucPdpId);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiDhcpActIpv4Expired_Active
 ��������  : ACTIVE��״̬���յ�TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��29��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDhcpActIpv4Expired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause  = TAF_PS_CAUSE_DHCP_TIME_OUT;

    /* Э��ʧ�ܴ��� */
    TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                       TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV4_TIEM_OUT);

    return VOS_TRUE;

}

/*****************************************************************************
 �� �� ��  : TAF_APS_RcvTiDhcpActIpv6Expired_Active
 ��������  : ACTIVE��״̬���յ�TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF��Ϣ�Ĵ���
 �������  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 �������  : ��
 �� �� ֵ  : VOS_UINT32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��29��
    ��    ��   : y00314741
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDhcpActIpv6Expired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡ��Ϣ���� */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause  = TAF_PS_CAUSE_DHCP_TIME_OUT;

    /* Э��ʧ�ܴ��� */
    TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                       TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV6_TIEM_OUT);


    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
/*****************************************************************************
 �� �� ��  : TAF_APS_RcvPsInterEnd1xService_Dormant
 ��������  : DORMANT��״̬���յ�ID_MSG_TAF_PS_INTER_END_1X_SERVICE_IN_DORMANT_IND��Ϣ�Ĵ���
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
VOS_UINT32 TAF_APS_RcvPsInterEnd1xService_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* ��ʼ��, ��ȡPDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* ���Dormant Timer�����У�ֹͣ��ʱ��������ȥ���� */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* ֹͣDormant ��ʱ�� */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* �ϱ�ȥ������¼� */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* ����ȥ���� */
        TAF_APS_LocalReleaseProc(ucPdpId);

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       DORMANT״̬�£���Ҫ�����½������ӣ�Ȼ���ٶϿ���

       ����TAF_APS_FSM_CDATA_ESTING״̬��
       ���غ���״̬�л�ΪTAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       ��TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT��״̬�д���
       ID_MSG_TAF_PS_CALL_ORIG_REQ��Ϣ
    -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */


#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

