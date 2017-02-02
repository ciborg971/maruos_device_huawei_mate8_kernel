
/*****************************************************************************
  1 头文件包含
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
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_MAIN_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/


VOS_UINT32 TAF_APS_RcvAtSetPdpContextStateReq_Inactive(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_SET_PDP_STATE_REQ_STRU      *pstSetPdpCtxStateReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg            = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);

    /* PDP激活操作处理 */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /*-------------------------------------------------------
           加载TAF_APS_STA_MS_ACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_ACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态中处理
           ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
        -------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_MS_ACTIVATING,
                           TAF_APS_GetMsActivatingFsmDescAddr(),
                           TAF_APS_MS_ACTIVATING_SUBSTA_INIT);
    }
    else
    {
        /* 指定去激活的CID处于未激活状态, 在预处理中已经处理, 这里不再处理 */
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
       平台能力支持CDMA，且当前驻留模式如果为3GPP2或NULL,
       则选择3GPP2流程，否则选择3GPP流程

       NULL状态下收到MMA上报的服务状态消息，
       如果为LTE模式则退出TAF_APS_FSM_CDATA_ESTING状态机，
       重新加载TAF_APS_STA_MS_ACTIVATING状态机

       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
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
           加载TAF_APS_STA_MS_ACTIVATING状态机
           加载后子状态切换为TAF_APS_MS_ACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态中处理
           ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ消息
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
       平台能力支持CDMA，且当前驻留模式如果为3GPP2或NULL,
       则选择3GPP2流程，否则选择3GPP流程

       NULL状态下收到MMA上报的服务状态消息，
       如果为LTE模式则退出TAF_APS_FSM_CDATA_ESTING状态机，
       重新加载TAF_APS_STA_MS_ACTIVATING状态机

       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
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
       加载TAF_APS_STA_MS_ACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_ACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_ACTIVATING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
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

    /* 获取当前网络模式*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* 检查当前模是否为GU, 如果不是, 丢弃该消息 */
    if ( (TAF_APS_RAT_TYPE_GSM   != enCurrRatType)
      && (TAF_APS_RAT_TYPE_WCDMA != enCurrRatType) )
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSmPdpActivateInd_Inactive: Current RAT is not GSM/WCDMA!");
        return VOS_TRUE;
    }

     /* 迁移到子状态TAF_APS_NW_ACTIVATING_SUBSTA_INIT,在子状态
        TAF_APS_NW_ACTIVATING_SUBSTA_INIT中处理 ID_SMREG_PDP_ACTIVATE_IND
        消息
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

    /* 获取当前网络模式*/
    enCurrRatType                       = TAF_APS_GetCurrPdpEntityRatType();

    /* 检查当前模是否为LTE, 如果不是, 丢弃该消息 */
    if (TAF_APS_RAT_TYPE_LTE != enCurrRatType)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvL4aPdpActivateInd_Inactive: Current RAT is not LTE!");
        return VOS_TRUE;
    }

    /* 迁移到子状态TAF_APS_NW_ACTIVATING_SUBSTA_INIT,在子状态
       TAF_APS_NW_ACTIVATING_SUBSTA_INIT中处理 ID_L4A_APS_PDP_ACTIVATE_IND
       消息
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
    /* 获取当前网络模式*/
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();
#endif
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 根据EPS承载的操作类型(Activate, Deactivate, Modify),
       调用相应的处理函数 */
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
            /* 记录当前的PS服务所在的模式 */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

            /* 通知外部模块当前的PS服务所在的模式 */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);
        }
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-16, end */
#endif

#if (FEATURE_ON == FEATURE_IPV6)
        /* 如果地址类型是IPv6, 需要同步给ND Client */
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

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
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

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstSetPdpCtxStateReq                = (TAF_PS_SET_PDP_STATE_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 设置激活标记 */
    ulBearerActivateFlg = (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState) ? VOS_TRUE : VOS_FALSE;

    /* 当前先不支持一次性激活多个PDP的场景，一次激活一个，因此找第一个要激活的 CID */
    ucCidValue = TAF_APS_GetCidValue(ulBearerActivateFlg, pstSetPdpCtxStateReq->stCidListStateInfo.aucCid);

    /* PDP激活操作处理 */
    if (TAF_CGACT_ACT == pstSetPdpCtxStateReq->stCidListStateInfo.ucState)
    {
        /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
        if (0 == TAF_APS_GetCallRemainTmrLen(ucCidValue))
        {
            TAF_APS_SndSetPdpCtxStateCnf(&(pstSetPdpCtxStateReq->stCtrl),
                                         TAF_PS_CAUSE_SUCCESS);
        }

        TAF_APS_SetCallRemainTmrLen(ucCidValue, 0);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCidValue);

#if (FEATURE_ON == FEATURE_IPV6)
        pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
        if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
        {
            /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
            TAF_APS_SndIpv6RaInfoNotifyInd(&(pstSetPdpCtxStateReq->stCtrl),
                                           ucCidValue,
                                           pstPdpEntity->ucNsapi,
                                           (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
        }
#endif

        /* 激活成功，启动流量统计 */
        TAF_APS_StartDsFlowStats(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
    else
    {
        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_STA_MS_DEACTIVATING
           子状态迁移至TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_SET_PDP_CONTEXT_STATE_REQ消息
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

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid))
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstPppDialOrigReq->stPppDialParaInfo.ucCid, 0);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
    TAF_APS_SndPdpActivateCnf(ucPdpId, pstPppDialOrigReq->stPppDialParaInfo.ucCid);

#if (FEATURE_ON == FEATURE_IPV6)
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    if (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo)
    {
        /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstPppDialOrigReq->stCtrl),
                                       pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif

    /* 激活成功，启动流量统计 */
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


    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果CID对应的剩余定时器时长为0, 需要上报响应事件 */
    if (0 == TAF_APS_GetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid))
    {
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                               pstCallOrigReq->stDialParaInfo.ucCid,
                               TAF_PS_CAUSE_SUCCESS);
    }

    TAF_APS_SetCallRemainTmrLen(pstCallOrigReq->stDialParaInfo.ucCid, 0);

    /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, begin */
    /* 在ehrpd下，当前已经完成initial attach，存在默认承载cid=0，
        但是dhcp协商可能还没有协商完成,暂时不上报，协商结束上报 */
    if (VOS_FALSE == pstPdpEntity->ucNeedGetDnsFlg)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, pstCallOrigReq->stDialParaInfo.ucCid);
    }
    /* Modified by y00314741 for CDMA Iteration 15, 2015-6-5, end */

#if (FEATURE_ON == FEATURE_IPV6)
    enPdpType    = pstCallOrigReq->stDialParaInfo.enPdpType;

    if ( ((TAF_PDP_IPV6 == enPdpType) || (TAF_PDP_IPV4V6 == enPdpType))
      && (VOS_TRUE == pstPdpEntity->bitOpIpv6RaInfo) )
    {
        /* 上报ID_EVT_TAF_PS_IPV6_INFO_IND事件 */
        TAF_APS_SndIpv6RaInfoNotifyInd(&(pstCallOrigReq->stCtrl),
                                       pstCallOrigReq->stDialParaInfo.ucCid,
                                       pstPdpEntity->ucNsapi,
                                       (TAF_PDP_IPV6_RA_INFO_STRU *)&pstPdpEntity->stIpv6RaInfo);
    }
#endif

    /* 激活成功，启动流量统计 */
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
       平台能力支持CDMA，且当前驻留模式如果为3GPP2,
       则选择3GPP2流程，否则选择3GPP流程

       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_END_REQ消息
    -------------------------------------------------------*/
    if (VOS_TRUE == TAF_APS_IsEnterCdataDiscing())
    {
        /* 获取消息内容 */
        pstAppMsg       = (TAF_PS_MSG_STRU *)pstMsg;
        pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU *)(pstAppMsg->aucContent);
        ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

        /* 上报PS呼叫挂断响应事件 */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* 保存子状态机的入口消息 */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

        TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

        enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

        /* 当前数据服务在EHRPD上，或者中继模式下(PPP未被激活)，加载去激活状态机 */
        if ((TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
         || (TAF_APS_CDATA_PPP_STATE_INACTIVE == enPppState))
        {
            /* 加载TAF_APS_FSM_CDATA_DISCING状态机 */
            TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                               TAF_APS_GetCdataDiscingFsmDescAddr(),
                               TAF_APS_CDATA_DISCING_SUBSTA_INIT);
        }
        else if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState)
        {
            /* 向PPP发送消息ID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            /* 启动定时器TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                               TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF_LEN,
                               ucPdpId);
        }
        else if (TAF_APS_CDATA_PPP_STATE_ACTIVATING == enPppState)
        {
            /* 向PPP发送消息ID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactReq(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_DEACTIVATING */
            TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

            /* 启动定时器TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                               TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF_LEN,
                               ucPdpId);

        }
        else
        {
            /* 如果是内部导致的去激活，只需更换入口消息 */
        }
    }
    else
#endif
    {
        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_STA_MS_DEACTIVATING
           子状态迁移至TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

           在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
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
       加载TAF_APS_STA_MS_MODIFYING状态机
       加载后子状态切换为TAF_APS_MS_MODIFYING_SUBSTA_INIT

       在TAF_APS_MS_MODIFYING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_MODIFY_REQ消息
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

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallAnswerReq                    = (TAF_PS_CALL_ANSWER_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS域MT呼叫流程, 方案未确定, 目前直接返回ERROR */
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

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallHangupReq                    = (TAF_PS_CALL_HANGUP_REQ_STRU*)(pstAppMsg->aucContent);

    /* PS域MT呼叫流程, 方案未确定, 目前直接返回ERROR */
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

    /* 获取消息内容 */
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

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* 检查QOS是否满足MIN */
    if (APS_PARA_VALID == Aps_CheckQosSatisify(ucPdpId, &stParam.NewQos))
    {
        /* 满足MINQOS */
        Aps_PdpMdfIndQosSatisfy(ucPdpId, &stParam, pstSmPdpModifyInd);

#if (FEATURE_ON == FEATURE_LTE)
        /* 同步PDP信息至ESM */
        MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_MODIFY);
#endif

        /* 如果当前模为GSM, 迁移状态 */
        if (TAF_APS_RAT_TYPE_GSM == enCurrRatType)
        {
            /*------------------------------------------------------------------
               加载TAF_APS_STA_MS_MODIFYING状态机
               加载后子状态切换为TAF_APS_MS_MODIFYING_SUBSTA_INIT

               在TAF_APS_MS_MODIFYING_SUBSTA_INIT子状态中
               处理D_PMC_SMREG_PDP_MODIFY_IND消息
            ------------------------------------------------------------------*/
            TAF_APS_InitSubFsm(TAF_APS_FSM_MS_MODIFYING,
                               TAF_APS_GetMsModifyingFsmDescAddr(),
                               TAF_APS_MS_MODIFYING_SUBSTA_INIT);
        }
    }
    else
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_QOS_NOT_ACCEPTED);

        /* 发送内部消息, 触发PDP去激活流程 */
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

    /* 初始化, 获取消息内容 */
    pstSmPdpDeactivateInd               = (SMREG_PDP_DEACTIVATE_IND_STRU*)pstMsg;
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* 同步PDP状态和信息至ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* 如果SNDCP已经激活, 释放SNDCP资源 */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstSmPdpDeactivateInd->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
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

    /* 初始化, 获取PDP ID */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 如果不是默认承载，则上报，默认承载不上报 */
    if (TAF_APS_DEFAULT_CID != pstPdpModify->ucCid)
    {
        if (VOS_TRUE == pstPdpModify->bitOpEpsQos)
        {
            pstPdpEntity->bitOpEpsQos   = VOS_TRUE;
            PS_MEM_CPY((VOS_UINT8 *)&pstPdpEntity->stEpsQos,
                       (VOS_UINT8 *)&pstPdpModify->stEpsQosInfo,
                       sizeof(APS_L4A_EPS_QOS_STRU));
        }

        /* 上报ID_EVT_TAF_PS_CALL_PDP_MODIFIED_IND事件 */
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

    /* 获取消息内容 */
    pstL4aPdpDeactivateInd = (APS_L4A_PDP_DEACTIVATE_IND_STRU*)pstMsg;

    /* 获取当前状态机的APS索引 */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取该索引的APS实体内容地址 */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* 如果不是默认承载，则上报，默认承载不上报 */
    if (TAF_APS_DEFAULT_CID != pstPdpEntity->stClientInfo.ucCid)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件上报 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapL4aCause(pstL4aPdpDeactivateInd->ulEsmCause));
    }
    else
    {
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
#endif
    }

    /* 如果SNDCP已经激活, 释放SNDCP资源 */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvL4aPdpSetupInd_Active
 功能描述  : 收到ID_L4A_APS_PDP_SETUP_IND消息的处理
 输入参数  : ulEventType: 消息类型
             pstMsg     : ID_L4A_APS_PDP_SETUP_IND消息
 输出参数  : 无
 返 回 值  : VOS_FALSE  : 处理消息失败
             VOS_TRUE   : 处理消息成功
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年11月19日
    作    者   : w00316404
    修改内容   : 新生成函数

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
    /* 处理IMS专有承载 */
    TAF_APS_ProcImsDedicateBearer(pstPdpEntity);
#endif

    /* 激活成功，启动流量统计 */
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

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);


    /* 根据EPS承载的操作类型(Activate, Deactivate, Modify),
       调用相应的处理函数 */
    if (SM_ESM_PDP_OPT_MODIFY == pstBearerInfo->enPdpOption)
    {
        MN_APS_ProcEsmBearerInfoIndOptModify(pstPdpEntity, pstBearerInfo);
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-8, begin */
        if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
        {
            /* 发送内部消息，所有正在激活过程中的状态机都需要处理该消息 */
            TAF_APS_SndInterAttachBearerActivateInd();
            /* 记录当前的PS服务所在的模式 */
            TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);
            /* 通知外部模块当前的PS服务所在的模式 */
            TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_LTE);

            TAF_APS_SET_CDATA_MTU(0);
        }
        /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-8, end */

        /* 上报给AP */
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

    /* 初始化, 获取消息内容 */
    ulResult         = VOS_OK;
    pstSnActivateRsp = &((APS_SNDCP_ACTIVATE_RSP_MSG*)pstMsg)->ApsSnActRsp;
    ucPdpId          = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity     = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 检查消息参数 */
    ulResult = Aps_SnMsgModSnActRspParaCheck(pstSnActivateRsp);
    if (APS_PARA_VALID != ulResult)
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF,
            "TAF_APS_RcvSndcpActivateRsp_Active: Check para failed!");

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        /* 发送内部消息, 触发PDP去激活流程 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_NW_PROTOCOL_ERR_UNSPECIFIED);

        return VOS_TRUE;
    }

    /* 收到SN_ACT_RSP后修改APS实体参数, 包括XID参数, TRANSMODE */
    Aps_SnActRspChngEntity(pstSnActivateRsp, ucPdpId);

    /* 设置RABM的传输模式 */
    TAF_APS_SndRabmSetTransModeMsg(pstSnActivateRsp->ucNsapi,
                                   pstPdpEntity->GprsPara.TransMode);

    return VOS_TRUE;
}


VOS_UINT32 TAF_APS_RcvSndcpDeactivateRsp_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 在TAF_APS_STA_ACTIVE状态下, 目前不需要处理APS_SN_DEACT_RSP_MSG_TYPE */

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
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_NW_LLC_OR_SNDCP_FAILURE);

        /* 发送内部消息, 触发PDP去激活流程 */
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

    /* 获取当前状态机的APS实体索引 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 检查SNDCP激活标识, 激活SNDCP */
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

    /* 获取当前状态机的接入技术 */
    enCurrRatType = TAF_APS_GetCurrPdpEntityRatType();

    /* 获取当前状态机的APS实体索引 */
    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* 在GU模下处理该消息, LTE模直接丢弃 */
    if (TAF_APS_RAT_TYPE_WCDMA == enCurrRatType)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SM_RAB_SETUP_FAILURE);

        /* 发送内部消息, 去激活PDP */
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
       加载TAF_APS_STA_MS_DEACTIVATING状态机
       加载后子状态切换为TAF_APS_MS_DEACTIVATING_SUBSTA_INIT

       在TAF_APS_MS_DEACTIVATING_SUBSTA_INIT子状态中处理
       ID_APS_APS_INTER_PDP_DEACTIVATE_REQ消息
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

    /* 初始化, 获取消息内容 */
    pstLocalMsg                         = (TAF_APS_INTER_PDP_DEACTIVATE_REQ_STRU *)pstMsg;
    ucPdpId                             = pstLocalMsg->ucPdpId;
    pstPdpEntity                        = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流量统计 */
    TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi);

    /* 同步PDP状态和信息至ESM */
#if (FEATURE_ON == FEATURE_LTE)
    MN_APS_SndEsmPdpInfoInd(pstPdpEntity, SM_ESM_PDP_OPT_DEACTIVATE);
#endif

    /* 向SM发送本地去激活请求 */
    if (VOS_TRUE == pstPdpEntity->bitOpTransId)
    {
        TAF_APS_SndSmPdpLocalDeactivateReq(ucPdpId);
    }

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
    if ( (TAF_APS_CheckPrimaryPdp(ucPdpId))
      && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
    {
        TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
    }
#endif

    /* 如果SNDCP已经激活, 释放SNDCP资源 */
    if (APS_SNDCP_ACT == pstPdpEntity->PdpProcTrack.ucSNDCPActOrNot)
    {
        Aps_ReleaseSndcpResource(ucPdpId);
    }

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
    TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_MapSmCause(pstLocalMsg->enCause));

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤器 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
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

    /* 获取消息内容 */
    pstServStaChangeInd  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /* 获取当前状态机的APS实体索引 */
    ucPdpId                = TAF_APS_GetCurrFsmEntityPdpId();

#if (FEATURE_ON == FEATURE_IPV6)
    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity           = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
#endif

#if (FEATURE_ON == FEATURE_IPV6)
    /* 如果地址类型是IPv6, 需要同步给ND Client */
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
        /* 当前模为GSM时, 不依靠该消息激活SNDCP */
        case TAF_APS_RAT_TYPE_GSM:
            break;

        /* 当前模为WCDMA/LTE时, 需要去激活SNDCP */
        case TAF_APS_RAT_TYPE_WCDMA:
        case TAF_APS_RAT_TYPE_LTE:
            if (APS_SNDCP_ACT == TAF_APS_GetPdpEntSndcpActFlg(ucPdpId))
            {
                Aps_RabmMsgDeActSndcp(ucPdpId);
            }

        /* TODO:如果之前承载建立在HRPD或者1X上的，需要本地去激活或者由AP来去激活 */

            break;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case TAF_APS_RAT_TYPE_1X:
            /* TO DO: 原来是LTE该如何修改 */
            /* 同步PDP信息至ESM */
#if (FEATURE_ON == FEATURE_LTE)
            if (TAF_APS_RAT_TYPE_LTE == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                MN_APS_SndEsmPdpInfoInd(TAF_APS_GetPdpEntInfoAddr(ucPdpId), SM_ESM_PDP_OPT_DEACTIVATE);
                // to do :通知L4A断开 ?
                /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
                /* 本地去激活 */
                TAF_APS_LocalReleaseProc(ucPdpId);
                /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-6, end */
            }
#endif
/* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
            if (TAF_APS_RAT_TYPE_EHRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

                /* 本地去激活 */
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

    /* 初始化, 获取消息内容 */
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
        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        TAF_APS_SndPppDeactInd(ucPdpId);

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

            /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
            TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);
        }
        else if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);

            /* 上报去激活的事件 */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }
        else
        {
            /* PPP在ACTIVE状态下，收到网侧的SO_REJ，上报去激活的事件 */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);
        }

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
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
        /* EHRPD模式下只通知EHSM进入DORMANT状态，APS的状态不改变 */
        TAF_APS_SndEhsmDiscNtf();
    }
    else
    {
        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND消息
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

    /* 初始化, 获取消息内容 */
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

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (HSM_APS_DISC_IND_STRU *)pstMsg;
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 记录失败原因值 */
    pstPdpEntity->enCause = TAF_APS_MapHsmCause(pstDiscInd->enCause);

    /* 如果CDATA PS已激活，迁到DORMANT状态 */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* Added by y00314741 for CDMA Iteration 11, 2015-3-25, begin */
        TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);
        /* Added by y00314741 for CDMA Iteration 11, 2015-3-25, end */

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
        /* 给RLP去注册上行数据状态的回调函数，停止计时 */
        CTTF_HRPD_RPA_DeregDormancyMonitor();
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

    }
    else
    {

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
        TAF_APS_SndPppDeactInd(ucPdpId);

        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

            /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_REJ事件 */
            TAF_APS_SndPdpActivateRej(ucPdpId, pstPdpEntity->enCause);
        }
        if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId))
        {
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);

            /* 上报去激活的事件 */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));
        }

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
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

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPppActCnf = (PPP_APS_ACT_CNF_STRU *)pstMsg;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF, ucPdpId);

    /* 判断当前PPP状态不为ACTIVATING态，则退出 */
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

            /* 给用户上报ACTIVATE_CNF事件 */
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
            /* TODO:检查IP类型错误，需要内部去激活? */
        }

        TAF_APS_SET_CDATA_MTU(pstPppActCnf->usMtu);

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
        /* 设置CDATA PS域服务状态为ACTIVE状态 */
        TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_ACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVE);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */

        /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

    }
    else
    {
        pstPdpEntity->enCause           = TAF_PS_CAUSE_PPP_NEGOTIATE_FAIL;

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息 */
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

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf     = (PPP_APS_DEACT_CNF_STRU*)pstMsg;

    /* 判断当前PPP状态不为DEACTIVATING态，则退出 */
    if (TAF_APS_CDATA_PPP_STATE_DEACTIVATING != TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_RcvPppDeactCnf_Active: PPP STATUS IS INACTIVE");
        return VOS_TRUE;
    }

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);

    /* 如果PPP回复失败，则强制PPP去激活 */
    if (VOS_OK != pstDeactCnf->ulResult)
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* 加载TAF_APS_FSM_CDATA_DISCING状态机 */
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

    /* 初始化 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    enTimerStatus   = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);
    if (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus)
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF, ucPdpId);
    }

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_ACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /*------------------------------------------------------------------
       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_PPP_APS_DEACT_IND消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-27, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvPppModifyInd_Active
 功能描述  : ACTIVE主状态下收到ID_PPP_APS_MODIFY_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月27日
    作    者   : y00314741
    修改内容   : 新生成函数

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

    /* 初始化, 获取消息内容 */
    lCmpRst        = VOS_ERROR;
    pstModifyInd   = (PPP_APS_MODIFY_IND_STRU*)pstMsg;
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    enPdnType      = TAF_APS_GetPdpEntDialPdpType(ucPdpId, ucCid);

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity   = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (enPdnType != pstModifyInd->enPdnType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_PPP_MODIFY,
                                       TAF_APS_INTER_END_CALL_REASON_IP_ADDR_CHANGED,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_PS_CAUSE_PPP_MODE_CHANGE;

        return VOS_TRUE;
    }

    /* 判断PPP的类型 */
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
        /* 记录失败原因值 */
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

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause               = TAF_PS_CAUSE_PPP_TIME_OUT;

    /* 通知PPP去激活 */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /*------------------------------------------------------------------
       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_CALL_ENTER_DORMANT_IND消息
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

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause               = TAF_PS_CAUSE_PPP_TIME_OUT;

    /* 通知PPP去激活 */
    TAF_APS_SndPppDeactInd(ucPdpId);

    /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
    TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);

    /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
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

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_DEACTIVATING);

    /* DORMANT状态下，用户主动去激活，建链成功后PPP去激活协商 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 向PPP发送消息ID_APS_PPP_DEACT_REQ */
        TAF_APS_SndPppDeactReq(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_DEACTIVATING */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_DEACTIVATING);

        /* 启动定时器TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF */
        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF,
                           TI_TAF_APS_CDATA_ESTING_WAIT_PPP_DEACT_CNF_LEN,
                           ucPdpId);

    }
    else
    {
        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_INTERNAL_DISC_SO_REQ消息
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

    /* 获取PDP ID */
    ucPdpId           = TAF_APS_GetCurrFsmEntityPdpId();

    /* 获取消息内容 */
    pstServStaChange  = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;

    /*获取当前建立数据服务的模式*/
    enCurrCdataServiceMode  = TAF_APS_GetCurrPdpEntityDataServiceMode();

    /* 根据传入接入技术分别处理 */
    if (TAF_APS_RAT_TYPE_HRPD == pstServStaChange->enRatType)
    {
         /* 从1X切换到HRPD */
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            TAF_APS_Proc1xToHrpdHandOff(ucPdpId, pstServStaChange->ucIsNewSession);
        }
    }
    else if (TAF_APS_RAT_TYPE_1X == pstServStaChange->enRatType)
    {
        /* 从HRPD切换到1X */
        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* 发送内部HRPD到1X切换请求消息 */
            TAF_APS_SndInterHrpdTo1XHandOffReq(ucPdpId);
        }
    }
    /* Modified by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    else if (TAF_APS_RAT_TYPE_LTE   == pstServStaChange->enRatType)
    {
        if (TAF_APS_RAT_TYPE_1X == enCurrCdataServiceMode)
        {
            /* 发起1X dormant态去激活 */
            TAF_APS_SndInterEnd1xServiceInDormantInd(ucPdpId);
        }

        if (TAF_APS_RAT_TYPE_HRPD == enCurrCdataServiceMode)
        {
            /* 上报去激活的事件 */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
            /* 本地去激活 */
            TAF_APS_LocalReleaseProc(ucPdpId);
        }
    }
    else if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChange->enRatType)
    {
        /* 上报去激活的事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);
        /* 本地去激活 */
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
        /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
        TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
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

    /* 初始化, 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);
    }

    /*-------------------------------------------------------
       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
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

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq                      = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报激活成功 */
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

    /* 初始化, 获取消息内容 */
    pstAppMsg                           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq                   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报激活成功 */
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

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 初始化, 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果Dormant Timer在运行，直接向PPP发送Deact Ind，上报去激活成功 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* 上报PS呼叫挂断响应事件 */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* 如果当前的PPP状态是激活的 */
        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* 向PPP发送deact ind */
            TAF_APS_SndPppDeactInd(ucPdpId);
        }

        /* 上报去激活的事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SUCCESS);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;
    }

    if (TAF_PDP_PPP == TAF_APS_GetPdpEntDialPdpType(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId)))
    {
        /* 上报PS呼叫挂断响应事件 */
        TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* 上报去激活的事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_SUCCESS);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        return VOS_TRUE;

    }

    /*-------------------------------------------------------
       DORMANT状态下，需要先重新建立链接，然后再断开。

       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
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
 函 数 名  : TAF_APS_RcvHsmCalConnectInd_Dormant
 功能描述  : In Dormant State, Receive CONNECT_IND,
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月05日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvHsmCalConnectInd_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId       = TAF_APS_GetCurrFsmEntityPdpId();

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

    return VOS_TRUE;
}
/* Added by y00314741 for CDMA 1X Iteration 9, 2015-2-5, end */
/* Added by y00314741 for CDMA Iteration 11, 2015-3-25, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant
 功能描述  : 收到内部1X到HRPD切换消息消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInter1XToHrpdHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     加载TAF_APS_FSM_CDATA_HANDOFF状态机
     加载后子状态切换为TAF_APS_CDATA_HANDOFF_SUBSTA_INIT

     在TAF_APS_CDATA_HANDOFF_SUBSTA_INIT子状态中处理
     ID_MSG_TAF_PS_INTER_1X_TO_HRPD_HANDOFF_REQ消息
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_HANDOFF,
                       TAF_APS_GetCdataHandOffFsmDescAddr(),
                       TAF_APS_CDATA_HANDOFF_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant
 功能描述  : 收到内部HRPD到1X切换消息消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月01日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallInterHrpdTo1XHandOff_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /*-------------------------------------------------------
     加载TAF_APS_FSM_CDATA_ESTING状态机
     加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

     在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
     ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ消息
     -------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_ESTING,
                       TAF_APS_GetCdataEstingFsmDescAddr(),
                       TAF_APS_CDATA_ESTING_SUBSTA_INIT);

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 11, 2015-3-25, end */
/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEHsmPdnDeactInd_Active
 功能描述  : ACTIVE主状态下收到ID_EHSM_APS_PDN_DEACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月16日
    作    者   : y00314741
    修改内容   : 新生成函数

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

    /* 获取消息内容 */
    pstEhsmPdnDeactInd    = (EHSM_APS_PDN_DEACTIVATE_IND_STRU *)pstMsg;
    ucPdpId               = TAF_APS_GetCurrFsmEntityPdpId();
    ucCid                 = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    pstPdpEntity          = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 记录失败原因值 */
    pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstEhsmPdnDeactInd->enCause);

    /* 如果不是默认承载，则上报，默认承载不上报 */
    if (TAF_APS_DEFAULT_CID != ucCid)
    {
        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件上报 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, pstPdpEntity->enCause);
    }
    else
    {
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_DISCONNECTED);
    }

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
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

            /* MTU变化后需要上报给AP */
            TAF_APS_SndCgmtuValueChangeInd(pstLteHandoverInd->usMtu);
        }

        /* 给RLP注册上行数据状态的回调函数，开始计时 */
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

    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    /* 发送内部消息，其它正在激活过程中的状态机需要处理此消息 */
    TAF_APS_SndInterAttachBearerActivateInd();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnActInd_Inactive
 功能描述  : ACTIVE主状态下收到ID_EHSM_APS_PDN_ACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月19日
    作    者   : y00314741
    修改内容   : 新生成函数

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

    /* 获取该PDPID的PDP实体内容地址 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 更新PdnId, APN, PdnAdrr */
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

    /* 记录当前的PS服务所在的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* 通知外部模块当前的PS服务所在的模式 */
    TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_EHRPD);

    TAF_APS_SET_CDATA_MTU(pstPdnActInd->usMtu);

    TAF_APS_SndCgmtuValueChangeInd(pstPdnActInd->usMtu);

    /* 主状态迁移至TAF_APS_STA_ACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

    /* 不需要获取Ipv4 DNS */
    if (((VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType))
    {
        /* 给RLP注册上行数据状态的回调函数，开始计时 */
        CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);

        return VOS_TRUE;
    }
    else
    {
        /* 需要获取Ipv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4   == pstPdnActInd->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
         && (((VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnActInd->stIpv4Dns.bitOpIpv4SecDNS))))
        {
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;

            /* 起定时器WAIT_DHCP_ACT_IPV4_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF_LEN,
                               ucPdpId);
        }

        /* 需要获取Ipv6 DNS */
        if ((EHSM_APS_PDN_TYPE_IPV6   == pstPdnActInd->stPdnAddr.enPdnType)
         || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActInd->stPdnAddr.enPdnType))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;

            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);
            pstPdpEntity->ucNeedGetDnsFlg = VOS_TRUE;

            /* 起定时器WAIT_DHCP_ACT_IPV6_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF_LEN,
                               ucPdpId);
        }
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiDhcpActIpv4Expired_Active
 功能描述  : ACTIVE主状态下收到TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月29日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDhcpActIpv4Expired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause  = TAF_PS_CAUSE_DHCP_TIME_OUT;

    /* 协商失败处理 */
    TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                       TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV4_TIEM_OUT);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiDhcpActIpv6Expired_Active
 功能描述  : ACTIVE主状态下收到TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月29日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiDhcpActIpv6Expired_Active(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    pstPdpEntity->enCause  = TAF_PS_CAUSE_DHCP_TIME_OUT;

    /* 协商失败处理 */
    TAF_APS_ProcCdataDhcpNegotiateFail(ucPdpId,
                                       TAF_APS_INTER_END_CALL_REASON_DHCP_ACT_IPV6_TIEM_OUT);


    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterEnd1xService_Dormant
 功能描述  : DORMANT主状态下收到ID_MSG_TAF_PS_INTER_END_1X_SERVICE_IN_DORMANT_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年07月04日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterEnd1xService_Dormant(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 如果Dormant Timer在运行，停止定时器，本地去激活 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId))
    {
        /* 停止Dormant 定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

        /* 上报去激活的事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

        /* 本地去激活 */
        TAF_APS_LocalReleaseProc(ucPdpId);

        return VOS_TRUE;
    }

    /*-------------------------------------------------------
       DORMANT状态下，需要先重新建立链接，然后再断开。

       加载TAF_APS_FSM_CDATA_ESTING状态机
       加载后子状态切换为TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT

       在TAF_APS_FSM_CDATA_ESTING_SUBSTA_INIT子状态中处理
       ID_MSG_TAF_PS_CALL_ORIG_REQ消息
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

