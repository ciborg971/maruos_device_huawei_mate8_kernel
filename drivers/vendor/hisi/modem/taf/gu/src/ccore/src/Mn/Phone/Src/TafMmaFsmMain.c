
/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafSdcCtx.h"
#include "MmaAppLocal.h"
#include "TafMmaCtx.h"
#include "Taf_Status.h"
#include "TafMmaSndInternalMsg.h"
#include "TafMmaMain.h"
#include "TafMmaSndApp.h"
#include "TafMmaComFunc.h"


#include "TafMmaMntn.h"
#include "NasComm.h"
/* Added by h00313353 for Iteration 13, 2015-4-13, begin */
#include "TafMmaFsmMain.h"
#include "TafMmaFsmMainTbl.h"
/* Added by h00313353 for Iteration 13, 2015-4-13, end */



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define     THIS_FILE_ID        PS_FILE_ID_TAF_MMA_FSM_MAIN_C
#define     STA_WARNING_PRINT   PS_LOG_LEVEL_WARNING

/*****************************************************************************
  2 全局变量
*****************************************************************************/
extern STATUS_CONTEXT_STRU                     g_StatusContext;

/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/*****************************************************************************
  6 函数实现
*****************************************************************************/


VOS_UINT32 TAF_MMA_RcvAppPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PH_OP_MODE_STRU                *pstPhModeSet    = VOS_NULL_PTR;
    MN_APP_REQ_MSG_STRU                *pstRcvMsg       = VOS_NULL_PTR;

    pstRcvMsg           = (MN_APP_REQ_MSG_STRU*)pstMsg;
    pstPhModeSet        = (TAF_PH_OP_MODE_STRU *)pstRcvMsg->aucContent;

    /* 关机时需要判断是否需要终止其他流程,开机时不需要判断 */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhModeSet->PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}



VOS_UINT32 TAF_MMA_RcvTafPhoneModeSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_SET_REQ_STRU    *pstPhoneModeSetReq  = VOS_NULL_PTR;

    pstPhoneModeSetReq  = (TAF_MMA_PHONE_MODE_SET_REQ_STRU *)pstMsg;

    /* 关机时需要判断是否需要终止其他流程,开机时不需要判断 */
    if ((STA_FSM_ENABLE   != g_StatusContext.ulFsmState)
     && (TAF_PH_MODE_FULL != pstPhoneModeSetReq->stPhoneModePara.PhMode))
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}




VOS_UINT32 TAF_MMA_RcvSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_SYS_CFG_REQ_STRU           *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (TAF_MMA_SYS_CFG_REQ_STRU *)pstMsg;

    /* Modified by l00301449 for Iteration 13, 2015-04-07, begin */
    switch (g_StatusContext.ulFsmState)
    {
        case STA_FSM_NULL:
        case STA_FSM_STOP:
            TAF_MMA_SetSyscfg_PowerOffStatus(pstRcvMsg);
            break;

        case STA_FSM_PLMN_RESEL:
            /* 如果是6F15触发的自动搜网，下发SYSCFG；
                  如果是AT触发的，由AT保证串行处理，此处不需处理 */
            if (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == TAF_MMA_GetAutoPlmnSelUser())
            {
                /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
                TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

                /* 启动SYS CFG状态机 */
                TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            }
            else
            {
                TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvSysCfgSetReq_Main: wrong state!");
            }

            break;

        case STA_FSM_ENABLE:
            /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
            TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

            /* 启动SYS CFG状态机 */
            TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
            break;


        default:
            TAF_MMA_SndSysCfgSetCnf(&(pstRcvMsg->stCtrl), TAF_ERR_CMD_TYPE_ERROR);

            break;
    }
    /* Modified by l00301449 for Iteration 13, 2015-04-08, end */

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaPlmnListReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PLMN_LIST_REQ_STRU         *pstRcvMsg          = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx      = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CTRL_STRU        *pstPlmnListCtrl    = VOS_NULL_PTR;
    TAF_MMA_PLMN_LIST_CNF_PARA_STRU    *pstPlmnListCnfPara = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstRcvMsg = (TAF_MMA_PLMN_LIST_REQ_STRU *)pstMsg;

    pstMmaOperCtx = TAF_MMA_GetOperCtxAddr();

    pstPlmnListCnfPara = (TAF_MMA_PLMN_LIST_CNF_PARA_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));
    if (NULL == pstPlmnListCnfPara)
    {
        return VOS_TRUE;
    }

    PS_MEM_SET(pstPlmnListCnfPara, 0x0, sizeof(TAF_MMA_PLMN_LIST_CNF_PARA_STRU));

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_LIST_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_LIST_REQ))
    {
        /* 直接回复plmn list失败 */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
         /* 直接回复plmn list失败 */
        pstPlmnListCnfPara->ucOpError    = VOS_TRUE;
        pstPlmnListCnfPara->enPhoneError = TAF_ERR_TI_ALLOC_FAIL;
        TAF_MMA_SndPlmnListCnf(&(pstRcvMsg->stCtrl), pstPlmnListCnfPara);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstRcvMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_LIST_REQ, ucCtxIndex);

    pstPlmnListCtrl = (TAF_MMA_PLMN_LIST_CTRL_STRU *)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_PLMN_LIST_CTRL_STRU));
    if (NULL == pstPlmnListCtrl)
    {
        /* 直接回复plmn list失败 */
        TAF_MMA_PlmnListErrorReport(TAF_ERR_ERROR);

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    pstPlmnListCtrl->usCurrIndex = pstRcvMsg->stPlmnListPara.usCurrIndex;
    pstPlmnListCtrl->usReadNum   = pstRcvMsg->stPlmnListPara.usQryNum;

    pstMmaOperCtx[ucCtxIndex].pPara = (VOS_VOID *)pstPlmnListCtrl;

    /* 如果不是分段上报中的首次查询，则直接调用缓存中的内容上报 */
    if (0 != pstPlmnListCtrl->usCurrIndex)
    {
        Sta_PlmnListEventReport();

        PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

        return VOS_TRUE;
    }

    PS_MEM_FREE(WUEPS_PID_MMA, pstPlmnListCnfPara);

    /* 继续原有的plmn list流程 */
    MMA_PhonePlmnList();

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMmaInterPowerInit_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaInterUsimStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }


    /* 如果当前为CL模式，则等待CDMA触发关机 */
    if (VOS_TRUE == TAF_SDC_IsConfigCLInterWorkCOutside())
    {
        return VOS_TRUE;
    }



    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}


VOS_UINT32 TAF_MMA_RcvMmaSimlockStatusChangeInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    if (STA_FSM_ENABLE != g_StatusContext.ulFsmState)
    {
        TAF_MMA_ProcPhoneStop_NotEnableStatus();
    }

    /* 启动phone mode状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_PHONE_MODE);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaPhoneModeRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_PHONE_MODE_RSLT_IND_STRU   *pstPhoneModeRslt    = VOS_NULL_PTR;
    TAF_SDC_CTX_STRU                   *pstSdcCtx           = VOS_NULL_PTR;

    pstPhoneModeRslt = (TAF_MMA_PHONE_MODE_RSLT_IND_STRU*)pstMsg;
    pstSdcCtx = TAF_SDC_GetSdcCtx();

    if (TAF_MMA_PHONE_MODE_RESULT_SWITCH_ON_SUCC == pstPhoneModeRslt->enRslt)
    {
        /*进入使能状态，设置状态标志量*/
        g_StatusContext.ulFsmState = STA_FSM_ENABLE;
    }
    else
    {
        /* 初始化全局变量 */
        TAF_MMA_InitCtx(TAF_MMA_INIT_CTX_POWEROFF, TAF_MMA_GetMmaCtxAddr());

        TAF_SDC_InitServiceInfo(&pstSdcCtx->stServiceInfo);

        TAF_SDC_InitLcConfigPara(&(pstSdcCtx->stMsCfgInfo.stMsCapInfo.stLcConfigPara));

        g_StatusContext.ulFsmState = STA_FSM_NULL;
    }

    return VOS_TRUE;
}

/* Added by h00313353 for Iteration 13, 2015-5-5, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_RcvMmaSysCfgRsltInd_Main
 功能描述  : 收到MMA的SysCfg状态机退出消息的主处理
 输入参数  : ulEventType
             pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月5日
    作    者   : h00313353
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 TAF_MMA_RcvMmaSysCfgRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode;
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode;
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate;

    pFuncTafSdcSysmodServiceRegStaUpdate = VOS_NULL_PTR;
    enSysMode = TAF_SDC_SYS_MODE_BUTT;
    enSubMode = TAF_SDC_SYS_SUBMODE_BUTT;

    if (VOS_TRUE == TAF_SDC_IsConfigCLMode())
    {
        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_LTE))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_LTE_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_E_UTRAN,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_CDMA_1X))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_1X_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_CDMA_1X,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);
        }

        if (VOS_FALSE == TAF_SDC_IsSyscfgSupportSpecRat(TAF_SDC_SYS_MODE_EVDO))
        {
            TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(TAF_SDC_HRPD_NETWORK_NOT_EXIST, &enSysMode, &enSubMode, &pFuncTafSdcSysmodServiceRegStaUpdate);

            TAF_MMA_ChgSysModeAndSrvRegSta(TAF_PH_ACCESS_TECH_EVDO,
                                           enSysMode,
                                           enSubMode,
                                           pFuncTafSdcSysmodServiceRegStaUpdate);
        }
    }

#endif

    /* 退出SYSCFG状态机后，迁移当前L1状态到idle状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_IDLE);

    return VOS_TRUE;
}

/* Added by h00313353 for Iteration 13, 2015-5-5, end */

/* Modified by l00301449 for Iteration 13, 2015-04-09, begin */

VOS_UINT32 TAF_MMA_RcvMmaInterSysCfgSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* 启动SYS CFG状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}
/* Modified by l00301449 for Iteration 13, 2015-04-09, end */

VOS_UINT32 TAF_MMA_RcvPihUsimStatusInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 发送内部卡状态改变消息 */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvUsimRefreshIndMsg_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 发送内部卡状态改变消息 */
    TAF_MMA_SndInterUsimChangeInd();

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvDetachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_DETACH_REQ_STRU            *pstDetachReqMsg;

    pstDetachReqMsg                     = (TAF_MMA_DETACH_REQ_STRU *)pstMsg;
    /* Deleted by h00313353 for Iteration 13, 2015-4-13, begin */
    /* Deleted by h00313353 for Iteration 13, 2015-4-13, end */

    /* Added by h00313353 for Iteration 13, 2015-4-13, begin */
    /* ENABLE或RESTART状态允许进行DETACH */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndDetachCnf(&(pstDetachReqMsg->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_ERROR);

        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_RcvDetachReq_Main():FSM state not in Enabled or Restart!");

        return VOS_TRUE;
    }

    /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* 启动System Config状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);
    /* Added by h00313353 for Iteration 13, 2015-4-13, end */

    return VOS_TRUE;
}



/* Modified by l00301449 for Iteration 13, 2015-04-11, begin */

VOS_UINT32 TAF_MMA_RcvAttachReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* ENABLE或者refresh触发的自动搜网允许发起attach */
    if (VOS_TRUE != TAF_MMA_IsEnableDeAttach())
    {
        TAF_MMA_SndAttachCnf(&(((TAF_MMA_ATTACH_REQ_STRU *)pstMsg)->stCtrl),
                             TAF_MMA_APP_OPER_RESULT_FAILURE,
                             TAF_ERR_PHONE_MSG_UNMATCH);

        return VOS_TRUE;
    }
    /* 进状态机之前，迁移当前L1状态到SYSCFG状态 */
    TAF_MMA_FSM_SetCurrState(TAF_MMA_MAIN_STA_SYSCFG);

    /* 启动SYS CFG状态机 */
    TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_SYS_CFG);

    return VOS_TRUE;
}

/* Added by y00307564 for CDMA Iteration 8 2015-2-4 end */

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 TAF_MMA_IsRefreshTrigger_Main(VOS_VOID)
{
    TAF_MMA_AUTO_PLMN_SEL_USER_ENUM_UINT8 enAutoPlmnSelUser;

    enAutoPlmnSelUser = TAF_MMA_GetAutoPlmnSelUser();

    /* refresh触发的自动搜网 */
    if ((STA_FSM_PLMN_RESEL == g_StatusContext.ulFsmState)
     && (TAF_MMA_AUTO_PLMN_SEL_USER_USIM_REFRESH == enAutoPlmnSelUser))
    {
        return VOS_TRUE;
    }

    /* refresh触发的SYSCFG*/
    /* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, begin */
    /* 如果在SYSCFG过程，在SYSCFG状态机中处理abort。此处删除 */
    /* Modified by l00301449 for CDMA 1X Iteration 13, 2015-04-16, end */

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_ProcImsSwitchOff_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* 如果当前处于IMS业务过程中，不允许关闭IMS业务 */
    if (VOS_TRUE == TAF_SDC_IsImsSrvExist())
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_SERVICE_EXIST);

        return VOS_TRUE;
    }

    /* 如果语音优选域设置成了PS_ONLY，不允许关闭IMS业务 */
    if (TAF_SDC_VOICE_DOMAIN_IMS_PS_ONLY == TAF_SDC_GetVoiceDomain())
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_REJECT,
                                   TAF_ERR_IMS_VOICE_DOMAIN_PS_ONLY);

        return VOS_TRUE;
    }

    /* 更新IMS业务能力变量和NV */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_FALSE))
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);
        return VOS_TRUE;
    }

    /* 当前IMS协议栈已经关闭或者处于飞行模式状态，
       则不需要给IMSA发关闭请求，只更新NV即可 */
    if ((TAF_SDC_IMS_SWITCH_STATE_OFF == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* 给上层回复成功 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_ProcImsSwitchOn_Main(
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU     *pstImsSwitchSet
)
{
    TAF_SDC_IMS_SWITCH_STATE_ENUM_UINT8 enLastState;
    VOS_UINT32                          ulPhoneMode;

    enLastState      = TAF_SDC_GetCurImsSwitchState();
    ulPhoneMode      = TAF_SDC_GetCurPhoneMode();

    /* 更新NV放在给IMSA发送start req的前面，IMSA收到start req会读NV项，需要用最新的NV值 */
    if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportFlag(VOS_TRUE))
    {
        /* 给上层回复失败 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_FAILURE,
                                   TAF_ERR_UNSPECIFIED_ERROR);

        return VOS_TRUE;
    }

    /* 当前IMS协议栈已经开启或者处于飞行模式状态，
       则不需要给IMSA发启动请求，只更新NV即可  */
    if ((TAF_SDC_IMS_SWITCH_STATE_ON == enLastState)
     || (TAF_PH_MODE_FULL != ulPhoneMode))
    {
        /* 给上层回复成功 */
        TAF_MMA_SndImsSwitchSetCnf(&pstImsSwitchSet->stCtrl,
                                   TAF_MMA_APP_OPER_RESULT_SUCCESS,
                                   TAF_ERR_NO_ERROR);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 TAF_MMA_RcvTafImsSwitchSetReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_MMA_IMS_SWITCH_SET_REQ_STRU    *pstSetReq   = VOS_NULL_PTR;
    VOS_UINT32                          ulResult;

    ulResult   = VOS_TRUE;
    pstSetReq  = (TAF_MMA_IMS_SWITCH_SET_REQ_STRU *)pstMsg;


    /* 如果当前有其他AT的请求在处理，则直接给上层回复失败，
       卡触发的请求可以设置IMS开关，但结果回复的时候需要缓存 */
    if ((STA_FSM_ENABLE != g_StatusContext.ulFsmState)
     && (STA_FSM_NULL   != g_StatusContext.ulFsmState)
     && (STA_FSM_STOP   != g_StatusContext.ulFsmState))
    {
        /* 不是卡触发的，即由AT触发的请求 */
        if (VOS_FALSE == TAF_MMA_IsRefreshTrigger_Main())
        {
            /* 给上层回复失败 */
            TAF_MMA_SndImsSwitchSetCnf(&pstSetReq->stCtrl,
                                       TAF_MMA_APP_OPER_RESULT_FAILURE,
                                       TAF_ERR_UNSPECIFIED_ERROR);

            return VOS_TRUE;
        }
    }

    /* 关闭IMS业务 */
    if (TAF_MMA_IMS_SWITCH_SET_POWER_OFF == pstSetReq->enImsSwitch)
    {
        ulResult = TAF_MMA_ProcImsSwitchOff_Main(pstSetReq);
    }
    else
    {
        ulResult = TAF_MMA_ProcImsSwitchOn_Main(pstSetReq);
    }

    /* 返回VOS_FALSE，代表需要继续进IMS_SWITCH状态机处理 */
    if ( VOS_FALSE == ulResult )
    {
        /* 启动IMS SWITCH状态机 */
        TAF_MMA_FSM_InitSubFsm(TAF_MMA_FSM_IMS_SWITCH);
    }

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_RcvMmaImsSwitchRsltInd_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 暂时没有处理，只是为了后续的缓存处理，以后如果有需要，可以在这里添加处理 */

    return VOS_TRUE;
}
#endif
VOS_UINT32 TAF_MMA_RcvPlmnSpecialSelReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    TAF_PLMN_ID_STRU                    stPlmn;
    VOS_UINT32                          ulRet;
    TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU  *pstPlmnSpecialSelMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnSpecialSelMsg = (TAF_MMA_PLMN_SPECIAL_SEL_REQ_STRU *)pstMsg;

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_SPEC_SEL_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_SPEC_SEL_REQ))
    {
        /* 直接回复SEL设置失败 */
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnSpecialSelCnf(&pstPlmnSpecialSelMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstPlmnSpecialSelMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_SPEC_SEL_REQ, ucCtxIndex);

    /* 在CL模式时候，不支持AT进行选网操作,直接返回ERROR */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 转化用户输入PLMN字符为PLMN ID */
    ulRet = MMA_FormatPlmnStr2PlmnId(&stPlmn,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucFormatType,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.usOperNameLen,
                                      pstPlmnSpecialSelMsg->stPlmnUserSel.ucOperName);
    if( VOS_TRUE == ulRet)
    {
        MMA_PlmnId2NasStyle(&stPlmn);

        /* 通过原有的TAF_PH_EVT_PLMN_SEL_CNF消息把指定搜结果发送给AT */
        MMA_PhonePlmnUserSel(pstPlmnSpecialSelMsg->stCtrl.usClientId, pstPlmnSpecialSelMsg->stCtrl.ucOpId, stPlmn, pstPlmnSpecialSelMsg->stPlmnUserSel.enAccessMode, TAF_PLMN_RESELETION_MANUAL);
    }
    else
    {
        /*错误处理*/
        TAF_MMA_ProcPlmnSpecialSelCnf(TAF_ERR_PARA_ERROR);
    }

    return VOS_TRUE;
}

VOS_UINT32 TAF_MMA_RcvPlmnAutoReselReq_Main(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    VOS_UINT8                           ucError;
    TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU   *pstPlmnReselMsg = VOS_NULL_PTR;
    VOS_UINT8                           ucCtxIndex;

    pstPlmnReselMsg = (TAF_MMA_PLMN_AUTO_RESEL_REQ_STRU *)pstMsg;

    /* 如果g_stTafMmaCtx.astMmaOperCtx里TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ类型结构正在被使用 */
    if (VOS_TRUE == TAF_MMA_IsOperTypeUsed(TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ))
    {
        /* 直接回复RESEL设置失败 */
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    /* 找不到未被使用的，回复失败 */
    if (VOS_FALSE == TAF_MMA_GetUnusedOperCtxIndex(&ucCtxIndex))
    {
        TAF_MMA_SndPlmnAutoReselCnf(&pstPlmnReselMsg->stCtrl, TAF_MMA_APP_OPER_RESULT_FAILURE);
        return VOS_TRUE;
    }

    /* 分配一个g_stTafMmaCtx.astMmaOperCtx到对应操作 */
    TAF_MMA_SetOperCtx(pstPlmnReselMsg->stCtrl,
                       TAF_MMA_OPER_PLMN_AUTO_RESEL_REQ, ucCtxIndex);

    ucError = TAF_ERR_NO_ERROR;
    ucError = MMA_CheckUsimStatusForPlmnSel();
    if(TAF_ERR_NO_ERROR != ucError)
    {
        MMA_WARNINGLOG("TAF_MMA_RcvPlmnAutoReselReq_Main():WARNING:UsimStatus Error!");
        /*错误处理*/
        TAF_MMA_ProcPlmnAutoReselCnf(ucError);
        return VOS_TRUE;
    }

    /* 在CL模式时候，不支持AT进行选网操作,直接返回ERROR */
    if (VOS_TRUE == TAF_MMA_IsPowerOnCLInterWork())
    {
        TAF_MMA_ProcPlmnAutoReselCnf(TAF_ERR_ERROR);
        return VOS_TRUE;
    }

    Sta_PlmnReselectAuto(pstPlmnReselMsg->stCtrl.ucOpId);

    return VOS_TRUE;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


