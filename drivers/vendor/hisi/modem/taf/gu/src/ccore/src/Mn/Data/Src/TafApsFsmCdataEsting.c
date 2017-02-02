

/*****************************************************************************
  1 头文件包含
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
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_FSM_CDATA_ESTING_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/******************************************************************************
   2 外部函数变量声明
******************************************************************************/

/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
*****************************************************************************/


/******************************************************************************
   5 函数实现
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

    /* 初始化, 获取PDP ID和当前接入技术 */
    pstAppMsg      = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallOrigReq = (TAF_PS_CALL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId        = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType  = TAF_APS_GetCurrPdpEntityRatType();
    ucCid          = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        /* 上报PDP操作结果 */
        TAF_APS_SndCallOrigCnf(&(pstCallOrigReq->stCtrl),
                              pstCallOrigReq->stDialParaInfo.ucCid,
                              TAF_PS_CAUSE_SIM_INVALID);

        /* 清除资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
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

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstCallOrigReq->stDialParaInfo.ucCid,
                                 pstCallOrigReq->stDialParaInfo.enPdpType);

    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVATING);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
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
                /* TODO:这里需要考虑DSDS下NO RF的场景 */
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
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
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

    /* 初始化, 获取PDP ID和当前接入技术 */
    pstAppMsg           = (TAF_PS_MSG_STRU*)pstMsg;
    pstPppDialOrigReq   = (TAF_PS_PPP_DIAL_ORIG_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId             = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType       = TAF_APS_GetCurrPdpEntityRatType();
    ucCid               = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 检查PS域卡状态, 如果无效, 直接返回ERROR */
    if (TAF_SDC_USIM_STATUS_VALID != TAF_SDC_GetCsimStatus())
    {
        /* 上报PDP操作结果 */
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SIM_INVALID);

        /* 清除资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();

        return VOS_TRUE;
    }

    if (0 == TAF_APS_GetCallRemainTmrLen(ucCid))
    {
        TAF_APS_SndPppDialOrigCnf(&(pstPppDialOrigReq->stCtrl),
                                  TAF_PS_CAUSE_SUCCESS);
    }

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetPdpEntDialPdpType(ucPdpId,
                                 pstPppDialOrigReq->stPppDialParaInfo.ucCid,
                                 TAF_APS_GetTafCidInfoPdpType(ucCid));



    TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVATING);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
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
                    /* 中继模式或者地址类型设置为PPP，则上报拨号失败 */
                    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_INVALID_PARAMETER);
                }

                TAF_APS_ProcCdataCallOrig_CdataEsting_EhrpdMode(ucPdpId, TAF_APS_ORIG_TYPE_PPP_DIAL);

                break;

            case TAF_APS_RAT_TYPE_1X:
                /* TODO:这里需要考虑DSDS下NO RF的场景 */
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
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
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

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* area lost no RF场景, 触发搜网*/
/* TODO:
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_GetRfAvailFlag())
    {
        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL);
    }
#endif
*/
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* DORMANT状态下，需要先重新建立链接 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* TODO: 考虑如果当前的服务模式和接入模式不同如何处理 */
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

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstIncomingCall = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    /* 起激活定时器 */
    TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    /* TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), 0); */

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 设置主状态 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* 记录当前建立数据服务的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, begin */

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, end */

    /* 根据ByePass值进行处理 */
    if (VOS_TRUE == pstIncomingCall->ucIsAlertAnsByPass)
    {
        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND);
    }
    else
    {
        /* 发送ID_APS_XCC_ANSWER_DATA_CALL_REQ */
        TAF_APS_SndXccAnswerDataCallReq(ucPdpId);

        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态 */
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

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    enCurrRatType   = TAF_APS_GetCurrPdpEntityRatType();

    /* area lost no RF场景, 触发搜网*/
/* TODO:
#if (FEATURE_ON == FEATURE_DSDS)
    if (VOS_FALSE == TAF_SDC_GetRfAvailFlag())
    {
        TAF_MMA_SrvAcqReq(TAF_MMA_SRV_TYPE_PS_SUBSCRIB_TRAFFIC_CALL);
    }
#endif
*/

    /* 用户上行数据触发的数据服务链接重建 */
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);
    /* TODO:需要综合考虑进DORMANT前数据服务所在的模式 */

    /* 如果支持HYBRID模式，首先在HPRD模式下进行尝试建链 */
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
        /* 如果不支持Hybrid，即只支持1X，则在1X下尝试建链 */
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
 函 数 名  : TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年03月25日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取PDP ID */
    ucPdpId  = TAF_APS_GetCurrFsmEntityPdpId();

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 设置匹配1X的SrId */
    TAF_APS_SetPdpEntSrId(ucPdpId, TAF_APS_HRPD_DEFAULT_SR_ID);

    /* 主状态TAF_APS_STA_CDATA_ESTING */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_CDATA_ESTING);

    /* 在1X下建链 */
    TAF_APS_ProcCdataCallOrig_CdataEsting_1XMode(VOS_TRUE, VOS_FALSE, VOS_TRUE);

    return VOS_TRUE;
}
/* Added by y00314741 for CDMA Iteration 11, 2015-3-25, end */

/* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsInterHrpdTo1XHandOff_CdataEsting_Init
 功能描述  : CDATA ESTING INIT子状态下收到ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND消息的处理
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
VOS_UINT32 TAF_APS_RcvPsInterDormantEnd1xSvc_CdataEsting_Init(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* DORMANT状态下，需要先重新建立链接 */
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

    /* 初始化 */
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

        /* 如果重拨周期定时器在运行，需要关闭重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 记录当前建立数据服务的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /* 通知外部模块当前的PS服务所在的模式 */
        TAF_APS_SndExternalModulePsRatTypeNtf(TAF_APS_RAT_TYPE_1X);

        /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);

        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

        /* 设置流控 */
        R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(TAF_APS_GetCurrPdpEntityDataServiceMode()));

        TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf();

        /* Clear ReOrig Scene */
        TAF_APS_SetEpdszidChgReOrigScene(TAF_APS_CDATA_EPDSZID_CHG_NO_REORIG);
    }
    else
    {
        /* 记录失败原因值 */
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

        /* 判断是否需要发起Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_1X))
        {
            ucReOrigCount = TAF_APS_GetPdpEntReOrigCount(ucPdpId);

            /* 记录是否是L2失败原因导致的重拨 */
            if (TAF_XCC_FAIL_LAYER_L2 == pstOirgCallCnf->enFailLayer)
            {
                TAF_APS_SetPdpEntL2ErrReOrigFlag(ucPdpId, VOS_TRUE);

                if (TAF_XCC_FAIL_LAYER_L3 != pstPdpEntity->stCdataInfo.enLastReOrigErr)
                {
                    /*原因值相同, 或者第一次重拨失败，则重拨计数累加 */
                    TAF_APS_SetPdpEntReOrigCount(ucPdpId, ucReOrigCount + 1);
                }
                else
                {
                    /*原因值不同则重新重1开始计数*/
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

            /* 起SILENT_REDIAL_WAIT 4s定时器，如果此定时器超时，会尝试重拨 */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL子状态 */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            if ((pstOirgCallCnf->enRslt == TAF_XCC_CAUSE_NORMAL_RELEASE)
            || ((pstOirgCallCnf->enRslt != TAF_XCC_CAUSE_NORMAL_RELEASE) && (TAF_XCC_FAIL_LAYER_L3 == pstOirgCallCnf->enFailLayer)))
            {
                TAF_APS_ProcEpdszidAfterRcvXccOrigDataCallCnf();


            }

            /* 停止流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* 如果重拨周期定时器在运行，需要停止 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_1X_NORMAL_DATA_CALL);

            /* 不需要重拨时，建链失败的处理 */
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

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_1X_NORMAL_DATA_CALL);

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 判断当前CDATA PS状态:如果不是active, APS加载去激活状态机 */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* 停止激活定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 停止重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    }
    else
    {
        /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
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

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 不需要重拨时，建链失败的处理 */
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

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstSoInd        = (XCC_APS_DATA_SERVICE_CONNECT_IND_STRU *)pstMsg;

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 更新SO、CONREF和PPP ID信息 */
    TAF_APS_SetPdpEntSo(ucPdpId, pstSoInd->enSo);
    TAF_APS_SetPdpEntConRef(ucPdpId, pstSoInd->ucConRef);

    /* 更新SR ID信息 */
    TAF_APS_SetPdpEntSrId(ucPdpId, pstSoInd->ucSrId);


    /* 数据服务建链完成的处理 */
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

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 判断当前CDATA PS状态:如果不是active, APS加载去激活状态机 */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* 停止激活定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

         /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    }
    else
    {
        /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
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
       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_INTERNAL_DISC_SO_REQ消息
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

    /* 初始化, 获取消息内容 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstDiscInd      = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    /* 获取该PDPID的PDP实体内容地址 */
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 保存原因值 */
    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* 不需重拨，处理建链失败的原因 */
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

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    /* 保存原因值 */
    pstPdpEntity->enCause = TAF_PS_CAUSE_XCC_TIME_OUT;

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg    = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ消息 */
    if (TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ) == pstEntryMsg->ulEventType)
    {
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                       TAF_APS_INTER_END_CALL_REASON_SO_NEGOTIATE_TIME_OUT,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);


        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* 向PPP发送消息ID_APS_PPP_DEACT_IND */
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
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
        /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
        TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_HANDOFF,
                                       TAF_APS_INTER_EDN_CALL_REASON_HANDOFF,
                                       ucPdpId,
                                       TI_TAF_APS_CDATA_DISCING_LEN);

        if (TAF_APS_CDATA_PPP_STATE_ACTIVE == TAF_APS_GetPdpEntPppState(ucPdpId))
        {
            /* 向PPP发送消息ID_APS_PPP_DEACT_REQ */
            TAF_APS_SndPppDeactInd(ucPdpId);

            /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_INACTIVE */
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

    /* 初始化 */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstAnsCallCnf   = (XCC_APS_ANSWER_DATA_CALL_CNF_STRU *)pstMsg;

    if (TAF_XCC_CAUSE_SUCCESS == pstAnsCallCnf->enRslt)
    {
        /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED);
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapXccCause(pstAnsCallCnf->enRslt);

        /* 停止流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 建链失败的处理 */
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

    /*获取PDP ID */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccAnsCallCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 此为冲突场景，数据被叫时，用户拨打电话,否则XCC应该回复ANS_CALL_CNF消息 */

    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd      = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 不需要重拨时，建链失败的处理 */
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

    /* 初始化, 获取消息内容 */
    ucPdpId                             = TAF_APS_GetCurrFsmEntityPdpId();

    /* 不需要重拨时，建链失败的处理 */
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

    /* 初始化 */
    pstCallConnInd  = (XCC_APS_DATA_CALL_CONN_IND_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 更新CONREF信息 */
    TAF_APS_SetPdpEntConRef(ucPdpId, pstCallConnInd->ucConRef);

    /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_SO_CONNECTED子状态 */
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

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    return VOS_TRUE;
}
VOS_UINT32  TAF_APS_RcvXccDataCallDiscInd_CdataEsting_WaitXccCallConnectedInd(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 此为冲突场景，数据被叫时，用户拨打电话 */

    XCC_APS_DATA_CALL_DISC_IND_STRU    *pstDiscInd      = VOS_NULL_PTR;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity    = VOS_NULL_PTR;
    VOS_UINT8                           ucPdpId;

    /* 初始化, 获取消息内容 */
    ucPdpId      = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstDiscInd   = (XCC_APS_DATA_CALL_DISC_IND_STRU *)pstMsg;

    pstPdpEntity->enCause = TAF_APS_MapXccCause(pstDiscInd->enCause);

    /* 停止流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* 不需要重拨时，建链失败的处理 */
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
        /* 判断是否可以发起HRPD建链 */
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

        /* 判断是否可以发起1X建链 */
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
        /* 停止流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 如果重拨周期定时器在运行，需要停止 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 通知搜网模块结束搜网 */
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

        /* 不需要重拨时，建链失败的处理 */
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

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 判断当前CDATA PS状态:如果不是active, APS去激活 */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* 停止激活定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 停止重拨周期、重拨间隔定时器 */
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

        /* 给用户返回DEACTIVE_CNF事件 */
        TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 主状态迁移至TAF_APS_STA_INACTIVE */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

        /* 退出子状态状态机 */
        TAF_APS_QuitCurrSubFsm();
    }
    else
    {
        /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
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

    /* 获取消息内容 */
    pstSvcStaChangeReq = (TAF_APS_INTER_SERVICE_STATUS_CHANGE_IND_STRU*)pstMsg;


    /*判断是否需要立即重拨 */
    if (VOS_FALSE == TAF_APS_IsNeedRedialImmediately(pstPdpEntity->enCause))
    {
        return VOS_TRUE;
    }

    switch(pstSvcStaChangeReq->enRatType)
    {
        /* 判断HRPD有服务 */
        case TAF_APS_RAT_TYPE_HRPD:

            /* 判断是否可以发起HRPD建链 */
            if(VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_HRPD))
            {
                /* 停止定时器 */
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

        /* 判断1X服务 */
        case TAF_APS_RAT_TYPE_1X:
            /* 判断是否可以发起1X建链 */
            if (VOS_TRUE == TAF_APS_IsAllowCdataEsting(TAF_APS_RAT_TYPE_1X))
            {
                /* 停止定时器 */
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
            /* 停止流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* 如果重拨周期定时器在运行，需要停止 */
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

            /* 不需要重拨时，建链失败的处理 */
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

    /* 初始化, 获取PDP ID */
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstIncomingCall = (XCC_APS_INCOMING_CALL_IND_STRU *)pstMsg;

    /* 此场景下，不能保存入口消息 */

    /* 记录当前建立数据服务的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_1X);

    /* 总的激活定时器TAF_APS_STA_CDATA_ESTING此时在运行，需要先关闭再重新运行 */
    if (TAF_APS_TIMER_STATUS_RUNING == TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_ESTING, ucPdpId))
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING, TI_TAF_APS_CDATA_ESTING_LEN, ucPdpId);
    }

    /* 停止重拨定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL, ucPdpId);

    /* 根据ByePass值进行处理 */
    if (VOS_TRUE == pstIncomingCall->ucIsAlertAnsByPass)
    {
        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND子状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_CALL_CONNECTED_IND);
    }
    else
    {
        /* 发送ID_APS_XCC_ANSWER_DATA_CALL_REQ */
        TAF_APS_SndXccAnswerDataCallReq(ucPdpId);

        /* 迁TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ANS_CALL_CNF子状态 */
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

    /* 判断是否可以发起1X建链 */
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

    /* 获取APS实体索引 */
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

    /* 向1X发送数据服务链接建立请求 */
    TAF_APS_SndXccOrigDataCallReq(ucPdpId, VOS_FALSE);

    /* 子状态迁移至TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF */
    TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_XCC_ORIG_CALL_CNF);

    return VOS_TRUE;


}
VOS_VOID TAF_APS_ProcCdataEstSucc_CdataEsting(
    VOS_UINT8                           ucPdpId
)
{
    TAF_APS_ENTRY_MSG_STRU             *pstEntryMsg;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;

    /* 初始化 */
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();

    /* 如果重拨周期定时器在运行，需要关闭重拨周期定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, begin */

    /* Deleted by y00314741 for CDMA Iteration 15, 2015-6-18, end */

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE状态下用户发生激活触发的数据服务建立 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
            /* CDMA HRPD模式下目前只支持一个承载，默认rabId为5 */
            pstPdpEntity->ucNsapi       = TAF_APS_DEFAULT_CDATA_RAB_ID;
            pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
            pstPdpEntity->ActType       = APS_PDP_ACT_PRI;
            TAF_APS_SetPdpEntCdataPdnId(ucPdpId, TAF_APS_DEFAULT_CDATA_PDN_ID);



            /* 配置IP过滤 */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            if (TAF_PS_CDATA_DIAL_MODE_RELAY == TAF_APS_GetFsmCtxCdataDialMode())
            {
                /* 给用户上报ACTIVATE_CNF事件 */
                TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

                /* 设置CDATA PS域服务状态为ACTIVE状态 */
                TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);

            }
            else
            {
                /* 发送ID_APS_PPP_ACT_REG消息给PPP模块 */
                TAF_APS_SndPppActReq(ucPdpId);

                /* 起激活定时器 */
                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                                   TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF_LEN,
                                   ucPdpId);

                /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_ACTIVATING */
                TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVATING);

            }

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):

            /* CDMA 1X模式下目前只支持一个承载，默认rabId为5 */
            pstPdpEntity->ucNsapi       = TAF_APS_DEFAULT_CDATA_RAB_ID;
            pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
            pstPdpEntity->ActType       = APS_PDP_ACT_PRI;
            TAF_APS_SetPdpEntCdataPdnId(ucPdpId, TAF_APS_DEFAULT_CDATA_PDN_ID);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* 中继模式下不需要通知PPP做激活协商 */
            if (TAF_PS_CDATA_DIAL_MODE_RELAY == TAF_APS_GetFsmCtxCdataDialMode())
            {
                /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, begin */

                /* Deleted by y00314741 for  CDMA Iteration 17, 2015-7-3, end */

                /* 配置IP过滤 */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* 给用户上报ACTIVATE_CNF事件 */
                TAF_APS_SndPdpActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

                /* 设置CDATA PS域服务状态为ACTIVE状态 */
                TAF_APS_SetPdpEntCdataPsState(ucPdpId, TAF_APS_CDATA_PS_STATE_ACTIVE);

                /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();
            }
            else
            {
                /* 发送ID_APS_PPP_ACT_REG消息给PPP模块 */
                TAF_APS_SndPppActReq(ucPdpId);

                /* 起激活定时器 */
                TAF_APS_StartTimer(TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF,
                                   TI_TAF_APS_CDATA_ESTING_WAIT_PPP_ACT_CNF_LEN,
                                   ucPdpId);

                /* 更新PPP状态为TAF_APS_CDATA_PPP_STATE_ACTIVATING */
                TAF_APS_SetPdpEntPppState(ucPdpId, TAF_APS_CDATA_PPP_STATE_ACTIVATING);

                /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
                TAF_APS_QuitCurrSubFsm();

            }
            break;

        /* DORMANT状态下用户去激活触发的数据服务重建，走断开流程 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
            /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_USER_END,
                                           TAF_APS_INTER_END_CALL_REASON_USER_END,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND):
            /* 发送内部消息ID_MSG_TAF_PS_INTER_END_CDMA_CALL_REQ */
            TAF_APS_SndInterEndCdmaCallReq(TAF_APS_INTER_END_CALL_SCENE_HANDOFF,
                                           TAF_APS_INTER_EDN_CALL_REASON_HANDOFF,
                                           ucPdpId,
                                           TI_TAF_APS_CDATA_DISCING_LEN);

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);
            TAF_APS_QuitCurrSubFsm();

            break;
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

        /* DORMANT状态下用户上行数传触发的数据服务重建，直接迁ACTIVE状态 */
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, begin */
        /* DORMANT状态下，HRPD丢网 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, end */

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }

            if (TAF_APS_RAT_TYPE_HRPD == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 给RLP注册上行数据状态的回调函数，开始计时 */
                CTTF_HRPD_RPA_RegDormancyMonitor(TAF_APS_ProcEvdoRlpDataStatusCb);
            }


            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
            TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下网侧触发的数据服务重建，直接迁ACTIVE状态 */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            /* TODO:给用户上报出DORMANT状态 */

            if (TAF_APS_RAT_TYPE_1X == TAF_APS_GetCurrPdpEntityDataServiceMode())
            {
                /* 通知RLP做初始化 */
                TAF_APS_SndRlpInitReq(ucPdpId);
            }


            /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_ACTIVE);

            /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
            TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));

            TAF_APS_QuitCurrSubFsm();

            break;

        default:
            TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_APS_ProcCdataEstSucc_CdataEsting:Wrong Msg Entry");
            break;
    }

}

/*****************************************************************************
 函 数 名  : TAF_APS_ProcCdataEstSucc_CdataEsting_Ehrpd
 功能描述  : CDATA数据EHRPD服务建链成功的处理
 输入参数  : VOS_UINT8                           ucPdpId
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月27日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_APS_ProcCdataEstSucc_CdataEsting_Ehrpd(
    VOS_UINT8                           ucPdpId,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucCid;

    /* 初始化 */
    pstPdnActCnf    = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* CDMA EHRPD模式下承载 */
    pstPdpEntity->ucNsapi       = pstPdnActCnf->ucRabId;
    pstPdpEntity->PdpNsapiFlag  = VOS_TRUE;
    pstPdpEntity->ActType       = APS_PDP_ACT_PRI;

    /* 记录当前建立数据服务的模式 */
    TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_EHRPD);

    /* 记录PDNID Pdnadrr Apn Dns */
    TAF_APS_SetPdpEntCdataPdnId(ucPdpId, pstPdnActCnf->ucPdnId);
    TAF_APS_UpdateCdataEhsmPdnInfo(pstPdpEntity,
                                   &(pstPdnActCnf->stPdnAddr),
                                   &(pstPdnActCnf->stApn),
                                   &(pstPdnActCnf->stIpv4Dns));


    /* 不需要获取Ipv4 DNS */
    if (((VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4PrimDNS) || (VOS_TRUE == pstPdnActCnf->stIpv4Dns.bitOpIpv4SecDNS))
      && (EHSM_APS_PDN_TYPE_IPV4   == pstPdnActCnf->stPdnAddr.enPdnType))
    {
        /* 给用户上报ACTIVATE_CNF事件 */
        TAF_APS_SndPdpActivateCnf(ucPdpId, ucCid);
    }
    else
    {
        /* 需要获取Ipv4 DNS */
        if (((EHSM_APS_PDN_TYPE_IPV4   == pstPdnActCnf->stPdnAddr.enPdnType) || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActCnf->stPdnAddr.enPdnType))
         && (((VOS_TRUE != pstPdnActCnf->stIpv4Dns.bitOpIpv4PrimDNS) && (VOS_TRUE != pstPdnActCnf->stIpv4Dns.bitOpIpv4SecDNS))))
        {
            /* 给DHCP发送GET_DNS_IPV4消息  */
            TAF_APS_SndDhcpDnsIpv4Req(ucPdpId);

            /* 起定时器WAIT_DHCP_ACT_IPV4_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV4_CNF_LEN,
                               ucPdpId);
        }

        /* 需要获取Ipv6 DNS，Ipv4,Ipv4v6类型 */
        if ((EHSM_APS_PDN_TYPE_IPV6   == pstPdnActCnf->stPdnAddr.enPdnType)
         || (EHSM_APS_PDN_TYPE_IPV4V6 == pstPdnActCnf->stPdnAddr.enPdnType))
        {
            TAF_APS_SndNdPdpActInd(pstPdpEntity->ucNsapi,
                                   pstPdpEntity->PdpAddr.aucIpV6Addr);

            pstPdpEntity->ulNdClientActiveFlg = VOS_TRUE;

            /* 给DHCP发送GET_DNS_IPV6消息  */
            TAF_APS_SndDhcpDnsIpv6Req(ucPdpId);

            /* 起定时器WAIT_DHCP_ACT_IPV6_CNF  */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF,
                               TI_TAF_APS_CDATA_EHRPD_WAIT_DHCP_ACT_IPV6_CNF_LEN,
                               ucPdpId);
        }
    }


    /* 配置IP过滤 */
    TAF_APS_IpfConfigUlFilter(ucPdpId);

    /* 设置流控 */
    R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(TAF_APS_GetCurrPdpEntityDataServiceMode()));

    /* 主状态迁移至TAF_APS_STA_ACTIVE, 退出子状态状态机 */
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

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    enCdataPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE状态下用户去激活触发的数据服务，走断开流程 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):
            /* 给用户返回ACTIVE_REJ事件 */
            TAF_APS_SndPdpActivateRej(ucPdpId, enCause);

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下用户去激活触发的数据服务重建，走断开流程 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):
            /* 给用户返回DEACTIVE_CNF事件 */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* 如果PPP已激活，通知PPP去激活 */
            if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enCdataPppState)
            {
                TAF_APS_SndPppDeactInd(ucPdpId);
            }

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 配置IP过滤 */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();
            break;

        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, begin */
        /* DORMANT状态下发生数据服务模式切换，建链失败 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_DORMANT_END_1X_SERVICE_IND):

            /* 上报去激活的事件 */
            TAF_APS_SndPdpDeActivateInd(ucPdpId, TAF_PS_CAUSE_RAT_TYPE_CHANGE);

            /* 设置当前数据服务模式 */
            TAF_APS_SndInterPsServiceModeModifyInd(TAF_APS_INTER_PS_OPTION_SWITCH);

            /* 本地去激活 */
            TAF_APS_LocalReleaseProc(ucPdpId);

            break;
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-4, end */

        /* DORMANT状态下用户上行数传触发的数据服务重建 */
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, end */

            if (VOS_TRUE == TAF_APS_IsCdataLocalReleaseCause(enCause))
            {
                /* 停止流量统计 */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* 释放APS资源 */
                Aps_ReleaseApsResource(ucPdpId);

                /* 配置IP过滤 */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* 主状态迁移至TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* 主状态迁移至TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                if (TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND) == pstEntryMsg->ulEventType)
                {
                    /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
                    TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
                }
            }

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下网络发起的数据服务重建，直接迁DORMANT状态 */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            if (TAF_PS_CAUSE_XCC_AS_SO_REJ == enCause)
            {
                /* 停止流量统计 */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* 释放APS资源 */
                Aps_ReleaseApsResource(ucPdpId);

                /* 配置IP过滤 */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* 主状态迁移至TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* 主状态迁移至TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
                TAF_APS_SndCdsFreeBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }

            /* 退出子状态状态机 */
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

    /* 获取当前的状态机入口消息和EVENTTYPE */
    pstEntryMsg     = TAF_APS_GetCurrSubFsmMsgAddr();
    enCdataPppState = TAF_APS_GetPdpEntPppState(ucPdpId);

    switch(pstEntryMsg->ulEventType)
    {
        /* INACTIVE状态下用户去激活触发的数据服务，上报激活失败 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_ORIG_REQ):
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_PPP_DIAL_ORIG_REQ):

            /* 给用户返回ACTIVE_REJ事件 */
            TAF_APS_SndPdpActivateRej(ucPdpId, enCause);

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下用户去激活触发的数据服务重建，上报去激活 */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_CALL_END_REQ):

            /* 给用户返回DEACTIVE_CNF事件 */
            TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

            /* 如果PPP已激活，通知PPP去激活 */
            if (TAF_APS_CDATA_PPP_STATE_ACTIVE == enCdataPppState)
            {
                TAF_APS_SndPppDeactInd(ucPdpId);
            }

            /* 释放APS资源 */
            Aps_ReleaseApsResource(ucPdpId);

            /* 配置IP过滤 */
            TAF_APS_IpfConfigUlFilter(ucPdpId);

            /* 主状态迁移至TAF_APS_STA_INACTIVE */
            TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下用户上行数传触发的数据服务重建，直接迁INACTIVE状态 */
        case TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND):

        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_EPDSZID_REORIG_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, begin */
        case TAF_BuildEventType(WUEPS_PID_TAF, ID_MSG_TAF_PS_INTER_HRPD_TO_1X_HANDOFF_REQ):
        /* Added by y00314741 for CDMA Iteration 11, 2015-4-1, end */

            if (VOS_TRUE == TAF_APS_IsCdataLocalReleaseCause(enCause))
            {
                /* 停止流量统计 */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* 释放APS资源 */
                Aps_ReleaseApsResource(ucPdpId);

                /* 配置IP过滤 */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* 主状态迁移至TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* 主状态迁移至TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                if (TAF_BuildEventType(UEPS_PID_CDS, ID_CDS_APS_CDATA_SERVICE_IND) == pstEntryMsg->ulEventType)
                {
                    /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
                    TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
                }
            }

            /* 退出子状态状态机 */
            TAF_APS_QuitCurrSubFsm();

            break;

        /* DORMANT状态下网络发起的数据服务重建，直接迁DORMANT状态 */
        case TAF_BuildEventType(UEPS_PID_XCC, ID_XCC_APS_INCOMING_CALL_IND):

            if (TAF_PS_CAUSE_XCC_AS_SO_REJ == enCause)
            {
                /* 停止流量统计 */
                /* TAF_APS_StopDsFlowStats(pstPdpEntity->ucNsapi); */

                /* 上报去激活的事件 */
                TAF_APS_SndPdpDeActivateInd(ucPdpId, enCause);

                /* 释放APS资源 */
                Aps_ReleaseApsResource(ucPdpId);

                /* 配置IP过滤 */
                TAF_APS_IpfConfigUlFilter(ucPdpId);

                /* 主状态迁移至TAF_APS_STA_INACTIVE */
                TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
            }
            else
            {
                /* 主状态迁移至TAF_APS_STA_DORMANT */
                TAF_APS_PdpEntityEnterDormant(ucPdpId, VOS_FALSE);

                /* 给CDS发送ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND消息 */
                TAF_APS_SndCdsSndBuffDataInd(TAF_APS_GetPdpEntNsapi(ucPdpId));
            }

            /* 退出子状态状态机 */
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

    /* 拨号参数 */
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

    /* 判断是否可以发起HRPD建链 */
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
            /* 触发HRPD下搜索MRU[0] */
            TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                     usClientId,
                                                     TAF_MMA_DO_NORMAL_DATA_CALL,
                                                     TAF_PS_CAUSE_HRPD_NO_SERVICE);

            /* 需要等待系统重新搜网后再重播 */
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

    /* 获取APS，Cid, ClientId */
    ucCid      = TAF_APS_GetPdpEntCurrCid(ucPdpId);

    /* 如果没有承载，或者由L切到C，则缓存该呼叫建立请求 */
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

    /* 初始化 */
    pstOirgCallCnf  = (HSM_APS_ORIG_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);
    ucCid           = TAF_APS_GetPdpEntCurrCid(ucPdpId);
    usClientId      = TAF_APS_GetPdpEntClientId(ucPdpId, ucCid);

    if (HSM_APS_CAUSE_SUCCESS == pstOirgCallCnf->enResult)
    {
        /* 记录当前建立数据服务的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);


        TAF_SndMmaCdmaMoCallSuccessNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

        /* 数据服务建链完成的处理 */
        TAF_APS_ProcCdataEstSucc_CdataEsting(ucPdpId);


        /* 设置流控 */
        R_ITF_SetFlowLev(TAF_APS_MapRatType2VosRatMode(TAF_APS_GetCurrPdpEntityDataServiceMode()));
    }
    else
    {
        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapHsmCause(pstOirgCallCnf->enResult);

        /* 判断是否需要发起Silent Redial */
        if (VOS_TRUE == TAF_APS_IsNeedSilentRedial(pstPdpEntity->enCause, TAF_APS_RAT_TYPE_HRPD))
        {
#if 0
            if (VOS_TRUE == TAF_APS_IsNeedRedialHrpdSystemAcquire(pstPdpEntity->enCause))
            {
                /* 建链过程中失败，暂不通知MMA搜网 */
                TAF_SndMmaCdmaCallRedialSystemAcquireNtf(WUEPS_PID_TAF,
                                                       usClientId,
                                                       TAF_MMA_DO_NORMAL_DATA_CALL,
                                                       pstPdpEntity->enCause);

                 /* 需要等待系统重新搜网后再重播 */
                 TAF_APS_SET_CDATA_WAIT_SYS_REQUIRE(VOS_TRUE);
            }
#endif
            /* 起SILENT_REDIAL_WAIT 4s定时器，如果此定时器超时，会尝试重拨 */
            TAF_APS_StartTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL,
                               TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_INTERVAL_LEN,
                               ucPdpId);

            /* 迁移TAF_APS_CDATA_ESTING_SUBSTA_WAIT_REDIAL子状态 */
            TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_WAIT_INTERVAL_REDIAL);
        }
        else
        {
            /* 停止流程定时器 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

            /* 如果重拨周期定时器在运行，需要停止 */
            TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

            TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, usClientId, TAF_MMA_DO_NORMAL_DATA_CALL);

            /* 不需要重拨时，建链失败的处理 */
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

    /* 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstCallEndReq   = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    TAF_SndMmaCdmaMoCallEndNtf(WUEPS_PID_TAF, 0, TAF_MMA_DO_NORMAL_DATA_CALL);

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 判断当前CDATA PS状态:如果不是active, APS加载去激活状态机 */
    if (TAF_APS_CDATA_PS_STATE_ACTIVE != TAF_APS_GetPdpEntCdataPsState(ucPdpId))
    {
        /* 停止激活定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 停止重拨周期定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_WAIT_CALL_REDIAL_PERIOD, ucPdpId);

        /* 之前发起建链的模式 */
        TAF_APS_SetCurrPdpEntityDataServiceMode(TAF_APS_RAT_TYPE_HRPD);

        /*------------------------------------------------------------------
           主状态迁移至TAF_APS_FSM_CDATA_DISCING
           子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

           在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
           处理ID_MSG_TAF_PS_CALL_END_REQ消息
        ------------------------------------------------------------------*/
        TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                           TAF_APS_GetCdataDiscingFsmDescAddr(),
                           TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    }
    else
    {
        /* 更换状态机入口消息，激活流程触发条件变为用户去激活触发建链 */
        TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitHsmOrigCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 建链失败的处理 */
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
       主状态迁移至TAF_APS_FSM_CDATA_DISCING
       子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

       在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
       处理ID_MSG_TAF_PS_INTERNAL_DISC_SO_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}


/* Added by y00314741 for CDMA Iteration 15, 2015-5-8, begin */
/*****************************************************************************
 函 数 名  : TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF子状态下
             收到ID_EHSM_APS_PDN_ACTIVATE_CNF消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月14日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvEhsmPdnActCnf_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    EHSM_APS_PDN_ACTIVATE_CNF_STRU     *pstPdnActCnf;
    APS_PDP_CONTEXT_ENTITY_ST          *pstPdpEntity;
    VOS_UINT8                           ucPdpId;

    /* 初始化 */
    pstPdnActCnf    = (EHSM_APS_PDN_ACTIVATE_CNF_STRU *)pstMsg;
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();
    pstPdpEntity    = TAF_APS_GetPdpEntInfoAddr(ucPdpId);

    if (EHSM_APS_CAUSE_SUCCESS == pstPdnActCnf->enCause)
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 数据建立成功处理 */
        TAF_APS_ProcCdataEstSucc_CdataEsting_Ehrpd(ucPdpId, pstMsg);
    }
    else if (EHSM_APS_CAUSE_EHRPD_SUSPEND == pstPdnActCnf->enCause)
    {
        /* 迁激活Suspend状态 */
        TAF_APS_SetCurrPdpEntitySubFsmState(TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND);
    }
    else
    {
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 记录失败原因值 */
        pstPdpEntity->enCause = TAF_APS_MapEhsmCause(pstPdnActCnf->enCause);



        /* 不需要重拨时，建链失败的处理 */
        TAF_APS_ProcCdataEstFail_CdataEsting(ucPdpId, pstPdpEntity->enCause);
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月14日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvPsCallEndReq_CdataEsting_WaitEhsmPdnActCnf(
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

    /* 上报PS呼叫挂断响应事件 */
    TAF_APS_SndCallEndCnf(&(pstCallEndReq->stCtrl), pstCallEndReq->ucCid, TAF_PS_CAUSE_SUCCESS);

    /* 保存子状态机的入口消息 */
    TAF_APS_SaveCurrSubFsmEntryMsg(ulEventType, pstMsg);

    /* 获取PDP ID */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

    /*------------------------------------------------------------------
    主状态迁移至TAF_APS_FSM_CDATA_DISCING
    子状态迁移至TAF_APS_CDATA_DISCING_SUBSTA_INIT

    在TAF_APS_CDATA_DISCING_SUBSTA_INIT子状态中
    处理ID_MSG_TAF_PS_CALL_END_REQ消息
    ------------------------------------------------------------------*/
    TAF_APS_InitSubFsm(TAF_APS_FSM_CDATA_DISCING,
                       TAF_APS_GetCdataDiscingFsmDescAddr(),
                       TAF_APS_CDATA_DISCING_SUBSTA_INIT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_WAIT_EHSM_PDN_ACTIVATE_CNF子状态下
             收到TI_TAF_APS_CDATA_ESTING消息的处理
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
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_WaitEhsmPdnActCnf(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    /* 获取实体信息 */
    ucPdpId = TAF_APS_GetCurrFsmEntityPdpId();

    /* 通知ehsm本地去激活 */
    TAF_APS_SndEhsmLocDeactNtf(ucPdpId);

    /* 建链失败的处理 */
    TAF_APS_ProcCdataEstFail_CdataEsting(TAF_APS_GetCurrFsmEntityPdpId(),
                                         TAF_PS_CAUSE_EHSM_PPP_ERROR_TIME_OUT);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvInterAttachBearerActivateInd_CdataEsting_Suspend
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND子状态下
             收到ID_EHSM_APS_PDN_ACTIVATE_IND消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月21日
    作    者   : y00314741
    修改内容   : 新生成函数

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

    /* 获取定时器剩余时长 */
    TAF_APS_GetRemainTimerLen(TI_TAF_APS_CDATA_ESTING, ucPdpId, &ulRemainTimeLen);

    /* 如果剩余时长非0, 停止当前流程, 重新处理当前的状态机入口消息 */
    if (0 != ulRemainTimeLen)
    {
        /* 记录剩余时长 */
        TAF_APS_SetCallRemainTmrLen(TAF_APS_GetPdpEntCurrCid(ucPdpId), ulRemainTimeLen);

        /* 停止激活流程定时器 */
        TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING, ucPdpId);

        /* 释放APS资源 */
        Aps_ReleaseApsResource(ucPdpId);

        /* 发送状态机入口消息至内部消息队列 */
        TAF_APS_SndInterFsmEntryMsg(pstEntryMsg);

        /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
        TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
        TAF_APS_QuitCurrSubFsm();
    }

    return VOS_TRUE;

}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND子状态下
             收到TI_TAF_APS_CDATA_ESTING消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月21日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvTiCdataEstingExpired_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 上报ID_EVT_TAF_PS_CALL_PDP_ACTIVATE_REJ事件 */
    TAF_APS_SndPdpActivateRej(ucPdpId, TAF_PS_CAUSE_APS_TIME_OUT);

    /* 释放APS资源 */
    Aps_ReleaseApsResource(ucPdpId);

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态状态机 */
    TAF_APS_SetCurrPdpEntityMainFsmState(TAF_APS_STA_INACTIVE);
    TAF_APS_QuitCurrSubFsm();

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend
 功能描述  : TAF_APS_CDATA_ESTING_SUBSTA_SUSPEND子状态下
             收到ID_MSG_TAF_PS_CALL_END_REQ消息的处理
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月21日
    作    者   : y00314741
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_APS_RcvAtPsCallEndReq_CdataEsting_Suspend(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucPdpId;
    TAF_PS_MSG_STRU                    *pstAppMsg;
    TAF_PS_CALL_END_REQ_STRU           *pstPsCallEndReq;

    /* 初始化, 获取消息内容 */
    pstAppMsg       = (TAF_PS_MSG_STRU*)pstMsg;
    pstPsCallEndReq = (TAF_PS_CALL_END_REQ_STRU*)(pstAppMsg->aucContent);
    ucPdpId         = TAF_APS_GetCurrFsmEntityPdpId();

    /* 停止激活流程定时器 */
    TAF_APS_StopTimer(TI_TAF_APS_CDATA_ESTING,
                      ucPdpId);

    /* 上报PDP操作结果, NO_ERROR */
    TAF_APS_SndCallEndCnf(&(pstPsCallEndReq->stCtrl),
                          pstPsCallEndReq->ucCid,
                          TAF_PS_CAUSE_SUCCESS);

    /* 上报ID_EVT_TAF_PS_CALL_PDP_DEACTIVATE_CNF事件 */
    TAF_APS_SndPdpDeActivateCnf(ucPdpId, TAF_APS_GetPdpEntCurrCid(ucPdpId));

    /* 主状态迁移至TAF_APS_STA_INACTIVE, 退出子状态机 */
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

    /* 初始化, 获取PDP ID和当前接入技术 */
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


