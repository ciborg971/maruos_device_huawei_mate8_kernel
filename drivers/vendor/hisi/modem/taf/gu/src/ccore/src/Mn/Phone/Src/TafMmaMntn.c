

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafLog.h"
#include "TafMmaMntn.h"
#include "Taf_Status.h"

#include "TafMmaCtx.h"
#include "TafSdcCtx.h"
#include "TafMmaComFunc.h"
#include "TafMmaSndInternalMsg.h"

#include "NasOmTrans.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_MNTN_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
extern STATUS_CONTEXT_STRU                      g_StatusContext;

/*lint -save -e958 */

/*****************************************************************************
  3 函数实现
*****************************************************************************/

VOS_VOID  TAF_MMA_LogFsmInfo(VOS_VOID)
{
    TAF_MMA_LOG_FSM_INFO_STRU          *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_FSM_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA, sizeof(TAF_MMA_LOG_FSM_INFO_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_MMA_LogFsmInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_FSM_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_FSM_INFO_IND;

    pstMsg->ulState                     = TAF_MMA_FSM_GetFsmTopState();
    pstMsg->enFsmId                     = TAF_MMA_GetCurrFsmId();

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}



VOS_VOID  TAF_MMA_LogBufferQueueMsg(
    VOS_UINT32                          ulFullFlg
)
{
    TAF_MMA_LOG_BUffER_MSG_INFO_STRU    *pstBufferMsg = VOS_NULL_PTR;
    TAF_MMA_MSG_QUEUE_STRU              *pstMsgQueue  = VOS_NULL_PTR;

    pstBufferMsg = (TAF_MMA_LOG_BUffER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_BUffER_MSG_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogBufferQueueMsg:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMsgQueue                               = TAF_MMA_GetCachMsgBufferAddr();
    pstBufferMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstBufferMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstBufferMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_BUffER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_BUFFER_MSG_INFO_IND;
    pstBufferMsg->ulFullFlg                   = ulFullFlg;
    PS_MEM_CPY(&(pstBufferMsg->stMsgQueue), pstMsgQueue, sizeof(pstBufferMsg->stMsgQueue));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstBufferMsg);

    return;
}



VOS_VOID TAF_MMA_LogOperCtxInfo(VOS_VOID)
{
    TAF_MMA_LOG_OPER_CTX_INFO_STRU     *pstBufferMsg    = VOS_NULL_PTR;
    TAF_MMA_OPER_CTX_STRU              *pstMmaOperCtx   = VOS_NULL_PTR;

    pstBufferMsg = (TAF_MMA_LOG_OPER_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_OPER_CTX_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogOperCtxInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstMmaOperCtx                             = TAF_MMA_GetOperCtxAddr();
    pstBufferMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstBufferMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstBufferMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_OPER_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_OPER_CTX_INFO_IND;
    PS_MEM_CPY(pstBufferMsg->astMmaOperCtx, pstMmaOperCtx, sizeof(pstBufferMsg->astMmaOperCtx));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstBufferMsg);

    return;
}





VOS_VOID  TAF_MMA_SndOmInternalMsgQueueInfo(
    VOS_UINT8                          ucFullFlg,
    VOS_UINT8                          ucMsgLenValidFlg
)
{
    TAF_MMA_LOG_INTER_MSG_INFO_STRU     *pstInterMsg = VOS_NULL_PTR;

    pstInterMsg = (TAF_MMA_LOG_INTER_MSG_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_INTER_MSG_INFO_STRU));

    if ( VOS_NULL_PTR == pstInterMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_SndOmInternalMsgQueueInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstInterMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstInterMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstInterMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstInterMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_INTER_MSG_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstInterMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_INTER_MSG_INFO_IND;
    pstInterMsg->ucFullFlg                   = ucFullFlg;
    pstInterMsg->ucMsgLenValidFlg            = ucMsgLenValidFlg;

    DIAG_TraceReport(pstInterMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstInterMsg);

    return;
}



VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
)
{
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                              sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogDrvApiPwrCtrlSleepVoteUnlock:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_UNLOCK;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enClientId                  = enClientId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}




VOS_VOID  TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock(
    VOS_UINT32                          ulRslt,
    PWC_CLIENT_ID_E                     enClientId
)
{
    TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU        *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                              sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogDrvApiPwrCtrlSleepVoteLock:ERROR:Alloc Mem Fail.");
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstMsg + VOS_MSG_HEAD_LENGTH,0,
                sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_DRV_API_PWRCTRL_SLEEPVOTE_LOCK;

    pstMsg->ulRslt                      = ulRslt;
    pstMsg->enClientId                  = enClientId;

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}


VOS_VOID TAF_MMA_ShowPhoneModeCtrlInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("*****************************\n");
    (VOS_VOID)vos_printf("*Auto Init Ps Flag:      %d\n", TAF_MMA_GetAutoInitPsFlg());
    (VOS_VOID)vos_printf("*Auto Switch On Flag:    %d\n", TAF_MMA_GetAutoSwitchOnFlg());
    (VOS_VOID)vos_printf("*Cur  Phone Mode:        %d\n", TAF_SDC_GetCurPhoneMode());
    (VOS_VOID)vos_printf("*Cur  Fsm State:         %d\n", g_StatusContext.ulFsmState);
    (VOS_VOID)vos_printf("*Phone Mode Error Code:  %d\n", TAF_MMA_GetCurPhoneErrorCode_PhoneMode());
    (VOS_VOID)vos_printf("*****************************\n");
}


VOS_VOID TAF_MMA_ShowCLConfigInfo(VOS_VOID)
{
    (VOS_VOID)vos_printf("\n");
    (VOS_VOID)vos_printf("*****************************\n");
    (VOS_VOID)vos_printf("*CL CONFIG Enable Flag: %d\n",          TAF_SDC_GetLCEnableFlg());
    (VOS_VOID)vos_printf("*CL CONFIG RatCombined Flag: %d\n",     TAF_SDC_GetLCRatCombined());
    (VOS_VOID)vos_printf("*CL CONFIG LCWORK Flag: %d\n",          TAF_SDC_GetLCWorkCfg());
    (VOS_VOID)vos_printf("*****************************\n");
}


/* Added by c00318887 for AT&T phaseII, 2015-4-8, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_LogCopsRltInfo
 功能描述  : 获取网络运营商名称
 输入参数  : *pstOperatorName          - cops 获取成功后的运营商名
             enType                    - 取运营商名的来源文件或nv
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月11日
    作    者   : c00318887
    修改内容   : AT&T 支持EONS特性修改
*****************************************************************************/
VOS_VOID TAF_MMA_LogCopsRltInfo(
        TAF_PH_NETWORKNAME_STRU                   *pstOperatorName,
        TAF_SDC_LOG_OPER_NAME_TYPE_ENUM_UINT8      enType
)
{
    TAF_MMA_LOG_COPS_RLT_INFO_STRU               *pstBufferMsg            = VOS_NULL_PTR;
    TAF_SDC_ENHANCED_OPERATOR_NAME_INFO_STRU     *pstEnhancedOperNameInfo = VOS_NULL_PTR;

    pstBufferMsg = (TAF_MMA_LOG_COPS_RLT_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                             sizeof(TAF_MMA_LOG_COPS_RLT_INFO_STRU));
    if ( VOS_NULL_PTR == pstBufferMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_LogCopsRltInfo:ERROR:Alloc Mem Fail.");
        return;
    }

    pstEnhancedOperNameInfo = TAF_SDC_GetEnhancedOperatorNameInfo();
    PS_MEM_SET(pstBufferMsg, 0x0, sizeof(TAF_MMA_LOG_COPS_RLT_INFO_STRU));

    pstBufferMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBufferMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstBufferMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstBufferMsg->stMsgHeader.ulLength        = sizeof(TAF_MMA_LOG_COPS_RLT_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBufferMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_COPS_RLT_INFO_IND;

    pstBufferMsg->enType                      = enType;
    pstBufferMsg->stNameFormat                = pstOperatorName->NameFormat;
    pstBufferMsg->ucRaMode                    = pstOperatorName->RaMode;
    pstBufferMsg->ucPlmnSelMode               = pstOperatorName->PlmnSelMode;
    PS_MEM_CPY(&pstBufferMsg->stName, &pstOperatorName->Name, sizeof(TAF_PH_OPERATOR_NAME_STRU));

    /* log中只打印MMINFO和SPN FILE */
    pstBufferMsg->stEonsInfo.cWildCard        = pstEnhancedOperNameInfo->cWildCard;
    pstBufferMsg->stEonsInfo.enCopsFormatType = pstEnhancedOperNameInfo->enCopsFormatType;
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stOperNameTypePrio, &pstEnhancedOperNameInfo->stOperNameTypePrio, sizeof(TAF_SDC_OPER_NAME_TYPE_PRIO_STRU));

    /* SPN USIM FILE */
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stUsimSpnFileInfo,
                &pstEnhancedOperNameInfo->stUsimSpnFileInfo,
                sizeof(TAF_SDC_SPN_FILE_INFO_STRU));

    /* SPN SIM FILE */
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stSimSpnFileInfo,
                &pstEnhancedOperNameInfo->stSimSpnFileInfo,
                sizeof(TAF_SDC_SPN_FILE_INFO_STRU));

    /* MMINFO */
    PS_MEM_CPY(&pstBufferMsg->stEonsInfo.stMmInfo,
                &pstEnhancedOperNameInfo->stMmInfo,
                sizeof(TAF_SDC_MM_INFO_STRU));

    DIAG_TraceReport(pstBufferMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstBufferMsg);

    return;
}

/* Added by c00318887 for AT&T phaseII, 2015-4-8, end */

VOS_VOID TAF_MMA_ModelPihSndUsimStatusInd(
    USIMM_CARD_TYPE_ENUM_UINT32         enCardType,
    USIMM_CARD_SERVIC_ENUM_UINT32       enCardService
)
{
    USIMM_CARDSTATUS_IND_STRU          *pstUsimMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstUsimMsg = (USIMM_CARDSTATUS_IND_STRU *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(USIMM_CARDSTATUS_IND_STRU));
    if (VOS_NULL_PTR == pstUsimMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstUsimMsg);

    pstUsimMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstUsimMsg->ulReceiverPid    = WUEPS_PID_MMA;
    pstUsimMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstUsimMsg->ulSenderPid      = MAPS_PIH_PID;
    pstUsimMsg->ulMsgName        = USIMM_CARDSTATUS_IND;
    pstUsimMsg->enPhyCardType    = USIMM_PHYCARD_TYPE_UICC;

    switch(enCardType)
    {
        case USIMM_CARD_USIM:
        case USIMM_CARD_SIM:
            {
                pstUsimMsg->stUsimSimInfo.enCardType    = enCardType;
                pstUsimMsg->stUsimSimInfo.enCardService = enCardService;
            }
            break;

        case USIMM_CARD_UIM:
        case USIMM_CARD_CSIM:
            {
                pstUsimMsg->stCsimUimInfo.enCardService = enCardService;
                pstUsimMsg->stCsimUimInfo.enCardType    = enCardType;
            }
            break;

        default:
            break;
    }

    /* 调用VOS发送原语 */
    TAF_MMA_SEND_MSG(pstUsimMsg);

    return;

}
VOS_VOID TAF_MMA_ModelUphySndInitStatusInd(
    MMA_UPHY_INIT_STATUS_ENUM_UINT16               enInitStatus
)
{
    UPHY_MMA_INIT_STATUS_IND_STRU      *pstRcvMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstRcvMsg = (UPHY_MMA_INIT_STATUS_IND_STRU *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(UPHY_MMA_INIT_STATUS_IND_STRU));
    if (VOS_NULL_PTR == pstRcvMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstRcvMsg);

    pstRcvMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstRcvMsg->ulReceiverPid    = WUEPS_PID_MMA;
    pstRcvMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstRcvMsg->ulSenderPid      = DSP_PID_STARTUP;
    pstRcvMsg->usMsgID          = ID_UPHY_MMA_INIT_STATUS_IND;
    pstRcvMsg->enInitStatus     = enInitStatus;

    /* 调用VOS发送原语 */
    TAF_MMA_SEND_MSG(pstRcvMsg);

    return;

}
VOS_VOID TAF_MMA_ModelUsimStatusIndTimeOut(VOS_VOID)
{
    REL_TIMER_MSG                      *pstTimerMsg = VOS_NULL_PTR;

    /* 申请内存  */
    pstTimerMsg = (REL_TIMER_MSG *)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(REL_TIMER_MSG));
    if (VOS_NULL_PTR == pstTimerMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstTimerMsg);

    pstTimerMsg->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstTimerMsg->ulReceiverPid    = WUEPS_PID_MMA;
    pstTimerMsg->ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstTimerMsg->ulSenderPid      = VOS_PID_TIMER;
    pstTimerMsg->ulName           = TI_TAF_MMA_WAIT_EXTERNAL_MODULE_INIT;

    /* 调用VOS发送原语 */
    TAF_MMA_SEND_MSG(pstTimerMsg);

    return;

}
VOS_VOID TAF_MMA_SndTestInterPowerInitReq(VOS_VOID)
{
    TAF_MMA_INTER_POWER_INIT_REQ_STRU  *pstPowerInitMsg = VOS_NULL_PTR;
    TAF_SDC_CTX_STRU                   *pstSdcCtx = VOS_NULL_PTR;

    pstSdcCtx = TAF_SDC_GetSdcCtx();

    pstPowerInitMsg  = (TAF_MMA_INTER_POWER_INIT_REQ_STRU*)TAF_MMA_ALLOC_MSG_WITH_HDR(sizeof(TAF_MMA_INTER_POWER_INIT_REQ_STRU));
    if (VOS_NULL_PTR == pstPowerInitMsg)
    {
        return;
    }

    /* 清空消息内容 */
    TAF_MMA_CLR_MSG_ENTITY(pstPowerInitMsg);

    TAF_MMA_CFG_INTRA_MSG_HDR(pstPowerInitMsg, MMA_MMA_INTER_POWER_INIT);

    TAF_MMA_SetPhyInitStatus(MMA_UPHY_INIT_STATUS_BUTT);
    TAF_SDC_InitSimInfo(&pstSdcCtx->stSimInfo.stUsimInfo);

    /* 需要发送外部消息,因为上电时无外部消息触发内部消息 */
    TAF_MMA_SEND_MSG(pstPowerInitMsg);

    return;
}


VOS_VOID TAF_MMA_TestSetGeoInfo(
    VOS_UINT32                          ulMcc,
    VOS_UINT32                          ulMnc
)
{
    TAF_MMA_GET_GEO_CTX_STRU            *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx        = TAF_MMA_GetGeoCtxAddr();

    pstGetGeoCtx->stGeoPlmnId.ulMcc = ulMcc;
    pstGetGeoCtx->stGeoPlmnId.ulMnc = ulMnc;
    pstGetGeoCtx->ulGetGeoTickTime  = VOS_GetTick() / PRE_SECOND_TO_TICK;

    return;
}


/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_LogNetworkInfoAndAppNetworkInfo
 功能描述  : 勾主动上报相关信息NetworkInfo/AppNetworkInfo
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月11日
    作    者   : l00305157
    修改内容   : Service_State_Optimize_PhaseII 项目修改
*****************************************************************************/
VOS_VOID  TAF_MMA_LogNetworkInfoAndAppNetworkInfo(VOS_VOID)
{
    TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU                            *pstMsg = VOS_NULL_PTR;
    TAF_SDC_NETWORK_INFO_STRU           *pstNetworkInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO             *pstAppNetworkInfo= VOS_NULL_PTR;

    pstMsg = (TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU*)PS_MEM_ALLOC(WUEPS_PID_MMA,
                                         sizeof(TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU));

    if ( VOS_NULL_PTR == pstMsg )
    {
        TAF_ERROR_LOG(WUEPS_PID_MMA, "TAF_SDC_LogNetworkInfoAndAppNetworkInfo:ERROR:Alloc Mem Fail.");
        return;
    }
    PS_MEM_SET(pstMsg, 0x00, sizeof(TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU));


    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_MMA;
    pstMsg->stMsgHeader.ulLength        = sizeof(TAF_SDC_LOG_NETWORK_AND_APPNETWORK_CTX_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = TAF_MMA_LOG_NETWORK_APPNETWORK_CTX_INFO_IND;

    pstNetworkInfo          = TAF_SDC_GetCurrNetworkInfo();
    pstAppNetworkInfo       = TAF_SDC_GetAppNetworkInfo();

    PS_MEM_CPY(&(pstMsg->stNetworkInfo), pstNetworkInfo, sizeof(TAF_SDC_NETWORK_INFO_STRU));
    PS_MEM_CPY(&(pstMsg->stAppNetworkInfo), pstAppNetworkInfo, sizeof(TAF_SDC_APPNETWORK_INFO));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(WUEPS_PID_MMA, pstMsg);

    return;
}

/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

/* Added by y00322978 for CDMA Iteration 17, 2015-7-7, begin */
/*****************************************************************************
 函 数 名  : TAF_MMA_LogReadNVInfo
 功能描述  : 勾取读取的NV信息上报 可维可测
 输入参数  : VOS_UINT16                              enNvItem,
             VOS_UINT16                              usNvDataLength,
             VOS_UINT32                              ulPid,
             VOS_UINT32                             *pData
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月7日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_LogReadNVInfo(
    VOS_UINT16                          enNvItem,
    VOS_UINT16                          usNvDataLength,
    VOS_UINT32                          ulPid,
    VOS_UINT8                          *pucData
)
{
    TAF_MMA_LOG_READ_NV_INFO_IND_STRU  *pstMsg = VOS_NULL_PTR;

    pstMsg = (TAF_MMA_LOG_READ_NV_INFO_IND_STRU*)PS_MEM_ALLOC(ulPid,
                             sizeof(TAF_MMA_LOG_READ_NV_INFO_IND_STRU) + usNvDataLength - 4);

    if (VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ulPid;
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = ulPid;
    pstMsg->ulLength        = sizeof(TAF_MMA_LOG_READ_NV_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH + usNvDataLength - 4;
    pstMsg->enMsgId         = TAF_MMA_LOG_READ_NV_INFO_IND;
    pstMsg->enNvItem        = enNvItem;
    pstMsg->usNvDataLength  = usNvDataLength;
    PS_MEM_CPY(pstMsg->aucNvInfo, pucData, usNvDataLength);

    DIAG_TraceReport((VOS_VOID *)pstMsg);

    PS_MEM_FREE(ulPid, pstMsg);
    return;
}


/*lint -restore */




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


