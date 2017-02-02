

/*****************************************************************************
  1 头文件包含
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
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/
VOS_UINT32  TAF_APS_ProcCdataDisc_CdataDiscing_Init(
    TAF_XCC_END_REASON_ENUM_UINT8       enEndReason
)
{
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 设置主状态 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_DISCING);

    switch (TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
        case TAF_APS_RAT_TYPE_HRPD:
            /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */
            /* 给RLP去注册上行数据状态的回调函数，停止计时 */
            CTTF_HRPD_RPA_DeregDormancyMonitor();
            /* Added by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

            /* 向HSM发送消息ID_APS_HSM_DISC_REQ */
            TAF_APS_SndHsmDiscReq(ucPdpId);

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF);

            break;

        case TAF_APS_RAT_TYPE_1X:
            /* 向XCC发送消息ID_APS_XCC_HANGUP_DATA_CALL_REQ */
            TAF_APS_SndXccHangUpDataCallReq(pstPdpEntity->stCdataInfo.ucCallId,
                                            enEndReason);

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_XCC_HANGUP_DATA_CALL_CNF);

            break;

        /* Added by y00314741 for CDMA Iteration 15, 2015-5-15, begin */
        case TAF_APS_RAT_TYPE_EHRPD:
            /* EHRPD模式下不主动去注册上行数据的回调函数 */

            /* 向EHSM发送消息ID_APS_EHSM_PDN_DEACTIVATE_REQ */
            TAF_APS_SndEhsmPdnDeactReq(ucPdpId);
            TAF_APS_SndDhcpDeactInd(ucPdpId);

#if (FEATURE_ON == FEATURE_IPV6)
            /* 如果是缺省承载且地址类型是IPv6, 需要同步给ND Client */
            if ((TAF_APS_CheckPrimaryPdp(ucPdpId))
             && (TAF_APS_CheckPdpAddrTypeIpv6(ucPdpId)) )
            {
                TAF_APS_SndNdPdpDeactInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }
#endif

            /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);

            break;
        /* Added by y00314741 for CDMA Iteration 15, 2015-5-15, end */

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF,
                "TAF_APS_ProcCdataDisc_CdataDiscing_Init: Wrong RAT type!");

            return VOS_TRUE;
    }

    /* 启动定时器TI_TAF_APS_CDATA_DISCING */
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
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_NORMAL_RELEASE);

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_RcvApsInternEndCdmaCallReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvPppDeactNtf_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}


VOS_UINT32  TAF_APS_RcvPppDeactCnf_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvTiPppDeactCnfExpired_CdataDiscing_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 如果当前是1X模式，需要原因值，如果是HRPD则不需要 */
    TAF_APS_ProcCdataDisc_CdataDiscing_Init(TAF_XCC_END_REASON_SERVICE_INACTIVE);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvXccHangUpDataCnf_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* 数据链接断开处理 */
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

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    enPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    /* 根据原因值和PPP状态判断是否需要通知PPP直接断开 */
    if ((TAF_XCC_CAUSE_SO_REJ == pstDiscInd->enCause)
      &&(TAF_APS_CDATA_PPP_STATE_ACTIVE == enPppState))
    {
        TAF_APS_SndPppDeactInd(ucPdpId);
    }

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_APS_MapXccCause(pstDiscInd->enCause));

    return VOS_TRUE;
}



VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 更改子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前的PPP状态是激活的 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 需要通知PPP去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
        TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_INACTIVE);
    }

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitXccHangUpDataCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 数据链接断开处理 */
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

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    pstEndCdmaCall  = (TAF_APS_INTER_END_CDMA_CALL_REQ_STRU*)pstEntryMsg->aucEntryMsgBuffer;

    /* 判断是否启动Dormant TI */
    ulNeedStartTimer  = VOS_FALSE;

    /* 如果是用户发起的挂断，上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
    if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
     || ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
      && (TAF_APS_INTER_END_CALL_SCENE_USER_END == pstEndCdmaCall->enEndScene)))
    {
        /* 停止流量统计 */
        /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, begin */
        /* 设置当前数据服务模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_GetCurrPdpEntityRatType());
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-6, end */

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    }
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_ORIG_FAIL == pstEndCdmaCall->enEndScene))
    {
        /* 主叫时需要给用户上报REJ消息 */
        TAF_APS_SndPdpActivateRej(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));
    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
    else if ((TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) == pstEntryMsg->ulEventType)
          && (TAF_APS_INTER_END_CALL_SCENE_HANDOFF == pstEndCdmaCall->enEndScene))
    {
        /* 设置当前数据服务模式 */
        TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

        /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
        TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

    }
    /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */
    else
    {
        if (TAF_APS_CDATA_PS_STATE_ACTIVE == TAF_APS_GetPdpEntCdataPsState(ucPdpId))
        {
            /* 如果之前是Active状态，20s没有数传而进入Dormant状态后，需要启动Dormant Timer */
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

            /* 进入Dormant状态后，触发内部消息，发起重拨*/
            if (TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG != TAF_APS_GetEpdszidChgReOrigScene())
            {
                TAF_APS_SndInterEpdszidReOrigReq();

                TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
            }

            /* 退出子状态机 */
            TAF_APS_QuitCurrSubFsm();

            return VOS_TRUE;
        }
        else
        {
            /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_IND事件 */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_APS_GetPdpEntPdpCause(ucPdpId));

        }
    }

    /* 释放资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

    /* 退出子状态机 */
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF状态下
             收到ID_HSM_APS_DISC_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvHsmDiscCnf_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvPsCallEndReq_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 更改子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 如果当前的PPP状态是激活的 */
    if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
    {
        /* 需要通知PPP去激活 */
        TAF_APS_SndPppDeactInd(ucPdpId);

        /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
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
    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_HSM_DISC_CNF状态下
             收到TI_TAF_APS_CDATA_DISCING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年02月04日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitHsmDiscCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到ID_EHSM_APS_PDN_DEACTIVATE_CNF消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactCnf_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    EHSM_APS_PDN_DEACTIVATE_CNF_STRU   *pstDeactCnf;

    /* 获取实体信息 */
    ucPdpId     = TAF_APS_GetCurrFsmEntityPdpId();
    pstDeactCnf = (EHSM_APS_PDN_DEACTIVATE_CNF_STRU *)pstMsg;

    if (EHSM_APS_CAUSE_LAST_PDN == pstDeactCnf->enCause)
    {
        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 如果是最后PDN去激活，EHSM会拒绝，根据此特定原因值进行特殊处理，此时
           该实体不会实际去激活，但是会刷新成默认承载，实体状态保持为激活状态 */

        /* 刷新成默认承载的CID */
        TAF_APS_SetPdpEntClientInfo(ucPdpId,
                                    TAF_APS_DEFAULT_CID,
                                    TAF_APS_INVALID_MODULEID,
                                    TAF_APS_INVALID_CLIENTID,
                                    TAF_APS_INVALID_OPID);
        /* 通知EHSM当前的Cid刷新 */
        TAF_APS_SndEhsmPdnCtxInfoNotify(ucPdpId, EHSM_APS_PDN_OPTION_MODIFIED);

        /* 主状态迁移至TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;

    }
    else if(EHSM_APS_CAUSE_EHRPD_SUSPEND == pstDeactCnf->enCause)
    {
        /* 迁去激活Suspend状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND);

    }
    else
    {
        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        /* 数据链接断开处理 */
        TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到ID_EHSM_APS_PDN_DEACTIVATE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEhsmPdnDeactInd_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到TI_TAF_APS_CDATA_DISCING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年05月15日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 通知ehsm本地去激活 */
    TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF状态下
             收到ID_ESM_SM_EPS_BEARER_INFO_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvEsmSmEpsBearerInfoInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* 初始化, 获取消息内容 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停保护定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

    TAF_APS_StopDsFlowStats(g_PdpEntity[ucPdpId].ucNsapi);

    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 将入口消息切到3GPP状态机处理 */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType )
    {
        /* 主状态迁移至TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        /* 重新将去激活请求发送出来，后续进入3GPP状态机处理 */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

    }

    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
    {
        /* 主状态迁移至TAF_APS_STA_ACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

        /* 退出子状态机 */
        TAF_APS_QuitCurrSubFsm();

        /* 重新将内部去激活请求发送出来，后续进入3GPP状态机处理 */
        TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);

    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_WaitEhsmPdnDeactCnf
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND状态下
             收到TI_TAF_APS_CDATA_DISCING消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年6月6日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvTiCdataDiscingExpired_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 数据链接断开处理 */
    TAF_APS_ProcCdataDisc_CdataDiscing(TAF_PS_CAUSE_SUCCESS);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend
 功能描述  : TAF_APS_CDATA_DISCING_SUBSTA_SUSPEND状态下
             收到ID_MSG_TAF_PS_INTER_SERVICE_STATUS_CHANGE_IND消息的处理
 输入参数  : ulEventType                - 消息ID
             pstMsg                     - 消息指针
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理

 修改历史      :
  1.日    期   : 2015年06月08日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_APS_RcvPsInterSrvStaChangeInd_CdataDiscing_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                                               ucPdpId;
    TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU           *pstServStaChangeInd = VOS_NULL_PTR;
    TAF_APS_ENTRY_MSG_STRU                                 *pstEntryMsg;

    /* 获取消息内容 */
    pstServStaChangeInd = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU *)pstMsg;
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    pstEntryMsg         = TAF_APS_GetCurrSubFsmMsgAddr();

    if (TAF_APS_RAT_TYPE_EHRPD == pstServStaChangeInd->enRatType)
    {
        /* 向EHSM发送消息ID_APS_EHSM_PDN_DEACTIVATE_REQ */
        TAF_APS_SndEhsmPdnDeactReq(ucPdpId);

        /* 状态迁移到TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_DISCING_SUBSTA_WAIT_EHSM_PDN_DEACTIVATE_CNF);
    }
    else if (TAF_APS_RAT_TYPE_LTE == pstServStaChangeInd->enRatType)
    {
        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_LTE);

        /* 将入口消息切到3GPP状态机处理 */
        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
        {
            /* 主状态迁移至TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* 退出子状态机 */
            TAF_APS_QuitCurrSubFsm();

            /* 重新将去激活请求发送出来，后续进入3GPP状态机处理 */
            TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        }

        if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ) ==pstEntryMsg->ulEventType)
        {
            /* 主状态迁移至TAF_APS_STA_ACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* 退出子状态机 */
            TAF_APS_QuitCurrSubFsm();

            /* 重新将内部去激活请求发送出来，后续进入3GPP状态机处理 */
            TAF_APS_SndInterPdpDeactivateReq(ucPdpId, SM_TAF_CAUSE_SM_UNKNOWN);
        }
    }
    else
    {
        /* 停止保护定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_DISCING, ucPdpId);

        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 配置IP过滤 */
        TAF_APS_IpfConfigUlFilter(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态状态机 */
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
