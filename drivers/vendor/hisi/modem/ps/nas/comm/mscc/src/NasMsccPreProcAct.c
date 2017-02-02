

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MsccMmcInterface.h"
#include "MmaMsccInterface.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "ImsaMsccInterface.h"
#endif
#include "NasMsccPreProcAct.h"
#include "NasMsccSndMma.h"
#include "NasMsccSndImsa.h"
#include "NasMsccSndMmc.h"
#include "NasMsccCtx.h"
#include "NasMsccSndXsd.h"
#include "NasMsccSndHsd.h"
#include "hsd_mscc_pif.h"
#include "NasMsccComFunc.h"
#include "NasMsccMlplMsplApi.h"
#include "NasMsccSndInternalMsg.h"
#include "NasMntn.h"
#include "NasMsccFsmMain.h"
#include "NasMsccFsmMainTbl.h"
#include "NasMsccProcNvim.h"
#include "NasMsccFsmBsrTbl.h"
#include "NasMsccFsmSysAcqTbl.h"
#include "NasMsccMntn.h"

#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_NAS_MSCC_PRE_PROC_ACT_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
#ifdef DMT
/* 用于DMT测试，设置开机时是否发送读卡命令标志，模拟读卡失败和超时的场景 */
NAS_MSCC_CARD_READ_STUB_TYPE_ENUM_UINT8 genCardReadStubTypeForDmt = NAS_MSCC_CARD_READ_STUB_TYPE_BUTT;
#endif

/*****************************************************************************
  3 函数定义
*****************************************************************************/


VOS_UINT32 NAS_MSCC_IsNetworkCapInfoChanged(
    NAS_MSCC_NETWORK_CAP_INFO_STRU      *pstNewNwCapInfo
)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU      *pstOldNwCapInfo = VOS_NULL_PTR;

    /* 先获取LTE的网络能力信息 */
    pstOldNwCapInfo = NAS_MSCC_GetLteNwCapInfo();

    /* 新旧能力是否有变化 */
    if ((pstOldNwCapInfo->enLteCsCap   != pstNewNwCapInfo->enLteCsCap)
     || (pstOldNwCapInfo->enNwEmcBsCap != pstNewNwCapInfo->enNwEmcBsCap)
     || (pstOldNwCapInfo->enNwImsVoCap != pstNewNwCapInfo->enNwImsVoCap))
    {
        return VOS_TRUE;
    }

    /* 再获取GU的网络能力信息 */
    pstOldNwCapInfo = NAS_MSCC_GetGuNwCapInfo();

    /* 新旧能力是否有变化 */
    if ((pstOldNwCapInfo->enLteCsCap   != pstNewNwCapInfo->enLteCsCap)
     || (pstOldNwCapInfo->enNwEmcBsCap != pstNewNwCapInfo->enNwEmcBsCap)
     || (pstOldNwCapInfo->enNwImsVoCap != pstNewNwCapInfo->enNwImsVoCap))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}



VOS_VOID NAS_MSCC_SetNetworkCapabilityInfo(
    NAS_MSCC_SYS_MODE_ENUM_UINT8        enSysMode,
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstNwCapInfo
)
{
    if (NAS_MSCC_SYS_MODE_LTE == enSysMode)
    {
        NAS_MSCC_SetLteNwCapInfo(pstNwCapInfo);
    }
    else
    {
        NAS_MSCC_SetGuNwCapInfo(pstNwCapInfo);
    }
}


VOS_UINT32 NAS_MSCC_IsImsVoiceSupportedByNW(VOS_VOID)
{
    NAS_MSCC_NETWORK_CAP_INFO_STRU     *pstCurNwCapInfo = VOS_NULL_PTR;
    NAS_MSCC_SYS_INFO_STRU             *pstSysInfo      = VOS_NULL_PTR;

    pstSysInfo = NAS_MSCC_GetCurrSysInfo();

    if (NAS_MSCC_SYS_MODE_LTE == pstSysInfo->st3gppSysInfo.enSysMode)
    {
        pstCurNwCapInfo = NAS_MSCC_GetLteNwCapInfo();
    }
    else
    {
        pstCurNwCapInfo = NAS_MSCC_GetGuNwCapInfo();
    }

    if (NAS_MSCC_NW_IMS_VOICE_NOT_SUPPORTED == pstCurNwCapInfo->enNwImsVoCap)
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_IsImsVoiceSupportedByUE(VOS_VOID)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();

    /* 当前IMS的RAT NV不支持或语音优选域为CS ONLY或网络不支持IMS时 认为IMS VOICE不可用*/
    if ((VOS_FALSE                     == NAS_MSCC_GetImsSupportFlag())
     || (NAS_MSCC_VOICE_DOMAIN_CS_ONLY == pstImsCfgInfo->enVoiceDomain))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_IsCGIInfoChanged(
    NAS_MSCC_3GPP_SYS_INFO_STRU         *pstOldSysInfo,
    MMC_MSCC_SYS_INFO_IND_STRU          *pstMmcSysInfo
)
{
    /* check CGI is changed */
    if ((pstOldSysInfo->stPlmnId.ulMcc  != pstMmcSysInfo->stPlmnId.ulMcc)
     || (pstOldSysInfo->stPlmnId.ulMnc  != pstMmcSysInfo->stPlmnId.ulMnc)
     || (pstOldSysInfo->usLac           != pstMmcSysInfo->usLac)
     || (pstOldSysInfo->ucRac           != pstMmcSysInfo->ucRac)
     || (pstOldSysInfo->ulCellId        != pstMmcSysInfo->stCellId.aulCellId[0])
     || (pstOldSysInfo->ucRoamFlag      != pstMmcSysInfo->ucRoamFlag)
     || (pstOldSysInfo->enSysMode       != pstMmcSysInfo->enCurNetWork)
     || (pstOldSysInfo->enLmmAccessType != pstMmcSysInfo->enLmmAccessType))
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MSCC_RcvMmcNetworkCapabilityInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU               *pstRcvMsg       = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    NAS_MSCC_SYS_INFO_STRU                                  *pstSysInfo      = VOS_NULL_PTR;
    NAS_MSCC_NETWORK_CAP_INFO_STRU                           stNewNwCapInfo;
    VOS_UINT32                                               ulNwCapInfoChanged;
#endif

    pstRcvMsg = (MMC_MSCC_NETWORK_CAPABILITY_INFO_IND_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_IMS)
    stNewNwCapInfo.enNwEmcBsCap = (NAS_MSCC_NW_EMC_BS_CAP_ENUM_UINT8)pstRcvMsg->enNwEmcBsCap;
    stNewNwCapInfo.enNwImsVoCap = (NAS_MSCC_NW_IMS_VOICE_CAP_ENUM_UINT8)pstRcvMsg->enNwImsVoCap;

    switch (pstRcvMsg->enLteCsCap)
    {
        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_NO_ADDITION_INFO:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_NO_ADDITION_INFO;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_CSFB_NOT_PREFER:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_CSFB_NOT_PREFER;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_SMS_ONLY:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_SMS_ONLY;
            break;

        case NAS_MSCC_PIF_LTE_CS_CAPBILITY_NOT_SUPPORTED:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_NOT_SUPPORTED;
            break;

        default:
            stNewNwCapInfo.enLteCsCap = NAS_MSCC_LTE_CS_CAPBILITY_BUTT;
            break;
    }

    /* 判断当前的网络能力与GU和L的能力相比是否发生了改变 */
    ulNwCapInfoChanged = NAS_MSCC_IsNetworkCapInfoChanged(&stNewNwCapInfo);

    if (VOS_TRUE == ulNwCapInfoChanged)
    {
        pstSysInfo = NAS_MSCC_GetCurrSysInfo();

        /* update informaton to the corresponding global variable according to RAT */
        NAS_MSCC_SetNetworkCapabilityInfo(pstSysInfo->st3gppSysInfo.enSysMode, &stNewNwCapInfo);
    }

    if (VOS_TRUE == NAS_MSCC_GetImsSupportFlag())
    {
        /* send service infomation change indcation */
        NAS_MSCC_SndImsaSrvInfoNotify(NAS_MSCC_GetCurr3gppPsServiceStatus(), VOS_FALSE, VOS_FALSE);
    }
#endif

    /* 转发消息给MMA */
    NAS_MSCC_SndMmaNetworkCapabilityInfoInd(pstRcvMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmcSysInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SYS_INFO_IND_STRU         *pstMmcSysInfo     = VOS_NULL_PTR;
    NAS_MSCC_3GPP_SYS_INFO_STRU         stOld3gppSysInfo;

    pstMmcSysInfo     = (MMC_MSCC_SYS_INFO_IND_STRU*)pstMsg;

    PS_MEM_SET(&stOld3gppSysInfo, 0x0, sizeof(NAS_MSCC_3GPP_SYS_INFO_STRU));
    PS_MEM_CPY(&stOld3gppSysInfo, NAS_MSCC_Get3gppSysInfoAddr(), sizeof(NAS_MSCC_3GPP_SYS_INFO_STRU));

    /* update 3gpp sys info */
    NAS_MSCC_Update3gppSysInfo(pstMmcSysInfo);

    /* 转发消息到MMA */
    NAS_MSCC_SndMma3gppSysInfoInd(pstMmcSysInfo);

#if (FEATURE_ON == FEATURE_IMS)
    if (VOS_TRUE == NAS_MSCC_GetImsSupportFlag())
    {
        if (VOS_TRUE == NAS_MSCC_IsCGIInfoChanged(&stOld3gppSysInfo, pstMmcSysInfo))
        {
            NAS_MSCC_SndImsaCampInfoChangeInd();
        }
    }
#endif

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvMmcRegResultInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_REG_RESULT_IND_STRU       *pstRegResultInd   = VOS_NULL_PTR;
#if (FEATURE_ON == FEATURE_IMS)
    VOS_UINT32                          ulUeSupportIms;
#endif

    pstRegResultInd = (MMC_MSCC_REG_RESULT_IND_STRU *)pstMsg;

    /* 转发该消息到MMA */
    NAS_MSCC_SndMmaRegResultInd(pstRegResultInd);

#if (FEATURE_ON == FEATURE_IMS)
    if ((NAS_MSCC_PIF_SRVDOMAIN_PS    == pstRegResultInd->enCnDomainId)
     || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstRegResultInd->enCnDomainId))
    {
        ulUeSupportIms = NAS_MSCC_IsImsVoiceSupportedByUE();

        /* PS注册失败直接通知IMS不可用 */
        /* 当前IMS的RAT NV不支持或语音优选域为CS ONLY或网络不支持IMS时 认为IMS VOICE不可用*/
        if ((VOS_FALSE == NAS_MSCC_IsImsVoiceSupportedByNW())
         || (VOS_FALSE == pstRegResultInd->ucRegRslt)
         || (VOS_FALSE == ulUeSupportIms))
        {
            /* 停止等待IMSA的IMS voice是否可用消息定时器 */
            NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY);

            /* 通知MMC当前IMS voice不可用 */
            NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
            NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
            NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);

            /* 通知MMA当前IMS voice不可用 */
            NAS_MSCC_SndMmaImsVoiceCapInd(VOS_FALSE);

            return VOS_TRUE;
        }

        /* 在PS注册成功时启动保护定时器等待IMS注册完成后上报IMS voice是否可用 */
        NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY, NAS_MSCC_GetWaitImsVoiceAvailTimerLen());
    }
#else
    /* 通知MMC当前IMS voice是否可用 */
    NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
    NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
    NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);

#endif

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcServiceStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstSrvStatusInd;
#if (FEATURE_ON == FEATURE_IMS)
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enOldPsSrvStatus;
    VOS_UINT8                           ucRoamingValid      = VOS_FALSE;
#endif
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enCurrPsSrvStatus;

    pstSrvStatusInd   = (MMC_MSCC_SERVICE_STATUS_IND_STRU *)pstMsg;

    /* 转发该消息给MMA模块 */
    NAS_MSCC_SndMmaServiceStatusInd(pstSrvStatusInd);

    NAS_MSCC_SetSimCsRegStatus(pstSrvStatusInd->ucSimCsRegStatus);

    NAS_MSCC_SetSimPsRegStatus(pstSrvStatusInd->ucSimPsRegStatus);

    /*注册状态上报处理: CS或PS域任一个是注册漫游时，更新3GPP的漫游标示 */
    if (VOS_TRUE == pstSrvStatusInd->bitOpRegSta)
    {
        NAS_MSCC_UpdateRoamFlag(pstSrvStatusInd->enRegState);
    }

    /* 如下处理只针对PS服务状态上报才处理 */
    if ((VOS_TRUE                      == pstSrvStatusInd->bitOpSrvSta)
     && ((NAS_MSCC_PIF_SRVDOMAIN_PS    == pstSrvStatusInd->enCnDomainId)
      || (NAS_MSCC_PIF_SRVDOMAIN_CS_PS == pstSrvStatusInd->enCnDomainId)))
    {
        enCurrPsSrvStatus = NAS_MSCC_ConvertMmcServiceStatusToMsccFormat(pstSrvStatusInd->enServiceStatus);

#if (FEATURE_ON == FEATURE_IMS)
        enOldPsSrvStatus  = NAS_MSCC_GetCurr3gppPsServiceStatus();

        if (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == enCurrPsSrvStatus)
        {
            ucRoamingValid = VOS_TRUE;
        }

        if ((VOS_TRUE         == NAS_MSCC_GetImsSupportFlag())
         && (enOldPsSrvStatus != enCurrPsSrvStatus))
        {
           NAS_MSCC_SndImsaSrvInfoNotify(enCurrPsSrvStatus, ucRoamingValid, NAS_MSCC_GetCurr3gppRoamingFlg());
        }
#endif

        /* 保存当前3GPP的PS服务状态 */
        NAS_MSCC_SetCurr3gppPsServiceStatus(enCurrPsSrvStatus);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        return NAS_MSCC_ProcPsServiceStatusIndInCLMode_PreProc(pstSrvStatusInd);
#endif
    }

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_RcvMmaSignReportReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SIGN_REPORT_REQ_STRU      *pstSignReport = VOS_NULL_PTR;
    pstSignReport = (MMA_MSCC_SIGN_REPORT_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcSignalReportReq(pstSignReport);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaModeChangeReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_MODE_CHANGE_REQ_STRU      *pstModeChangeReq = VOS_NULL_PTR;
    pstModeChangeReq = (MMA_MSCC_MODE_CHANGE_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcModeChangeReq(pstModeChangeReq);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaAttachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_ATTACH_REQ_STRU           *pstAttachReq = VOS_NULL_PTR;

    pstAttachReq = (MMA_MSCC_ATTACH_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcAttachReq(pstAttachReq);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaDetachReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_DETACH_REQ_STRU           *pstDetachReq = VOS_NULL_PTR;

    pstDetachReq = (MMA_MSCC_DETACH_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcDetachReq(pstDetachReq);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaPlmnListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    /* if current rat setting support HRPD,we directly reply fail to upp layer */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* reply upp layer with reject result */
        NAS_MSCC_SndMmaPlmnListRej((MMC_MSCC_PLMN_LIST_REJ_STRU*)pstMsg);

        return VOS_TRUE;
    }

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcPlmnListReq();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaPlmnListAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU   stMmcMsccPlmnListAbortCnf;

    PS_MEM_SET(&stMmcMsccPlmnListAbortCnf, 0x0, sizeof(stMmcMsccPlmnListAbortCnf));

    /* if current rat setting support HRPD,we directly reply fail to upp layer */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndMmaPlmnListAbortCnf(&stMmcMsccPlmnListAbortCnf);

        return VOS_TRUE;
    }

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcPlmnListAbortReq();

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaUserReselReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_RESEL_CNF_STRU        stPlmnReselCnf;

    /* GUL mode or current active mode is LTE, transfer user resel
       request to MMC module */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* reply upp layer with failed result */
        PS_MEM_SET(&stPlmnReselCnf, 0x0, sizeof(MSCC_MMA_PLMN_RESEL_CNF_STRU));
        stPlmnReselCnf.enResult = NAS_MSCC_PIF_USER_PLMN_SEARCH_RESULT_FAIL;

        NAS_MSCC_SndMmaPlmnReselCnf((MMC_MSCC_PLMN_RESEL_CNF_STRU*)&stPlmnReselCnf);

        return VOS_TRUE;
    }

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcPlmnUserReselReq((MMA_MSCC_PLMN_USER_RESEL_REQ_STRU *)pstMsg);


    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaUserSpecPlmnSearch_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_PLMN_SPECIAL_REQ_STRU     *pstPlmnSpecialReq  = VOS_NULL_PTR;

    pstPlmnSpecialReq = (MMA_MSCC_PLMN_SPECIAL_REQ_STRU *)pstMsg;

    /* GUL mode or current active mode is LTE, transfer user resel
       request to MMC module */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        /* reply upp layer with failed result */
        NAS_MSCC_SndMmaPlmnSpecialSelRej((MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU*)pstMsg);

        return VOS_TRUE;
    }

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcPlmnSpecialReq(pstPlmnSpecialReq);

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_RcvMmaSpecPlmnSearchAbortReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* GUL mode or current active mode is LTE, transfer user resel
       request to MMC module */
    if (VOS_TRUE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_HRPD))
    {
        NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf((MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU*)pstMsg);

        return VOS_TRUE;
    }

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcSpecPlmnSearchAbortReq();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaOmMaintainInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *pstMaintainInfoInd = VOS_NULL_PTR;

    pstMaintainInfoInd = (MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcOmMaintainInfoInd(pstMaintainInfoInd);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaUpdateUplmnNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcUpdateUplmnNotify();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaEOPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_EOPLMN_SET_REQ_STRU       *pstEOPlmnSetReq = VOS_NULL_PTR;

    pstEOPlmnSetReq = (MMA_MSCC_EOPLMN_SET_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcEOPlmnSetReq(pstEOPlmnSetReq);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_NET_SCAN_REQ_STRU         *pstNetScanReq = VOS_NULL_PTR;

    pstNetScanReq = (MMA_MSCC_NET_SCAN_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcNetScanMsgReq(pstNetScanReq);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaAbortNetScanReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcAbortNetScanMsgReq();

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_ACQ_REQ_STRU              *pstAcqReq = VOS_NULL_PTR;

    pstAcqReq = (MMA_MSCC_ACQ_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcAcqReq(pstAcqReq);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaRegReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_REG_REQ_STRU              *pstRegReq = VOS_NULL_PTR;

    pstRegReq = (MMA_MSCC_REG_REQ_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcRegReq(pstRegReq);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_PhoneRssiInd
 功能描述  : 收到MMC上报的MSCC_RSSI_IND消息
 输入参数  : MMC_MSCC_RSSI_IND_STRU *pMsg MSCC上传得数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :
 修改历史     :
  1.日    期  : 2015年01月30日
    作    者  : x00314862
    修改内容  : 新建

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPhoneRssiInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaRssiInd((MMC_MSCC_RSSI_IND_STRU*)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : Sta_MmInfo
 功能描述  : 处理MM INFO消息上报
 输入参数  : MMC_MSCC_MM_INFO_IND_STRU *pstMmInfo - MM INFO结构指针
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :
 修改历史     :
  1.日    期  : 2015年01月30日
    作    者  : x00314862
    修改内容  : 新建
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStaMmInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaMmInfo((MMC_MSCC_MM_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;

}


/*****************************************************************************
 函 数 名  : MSCC_ProcPlmnSelectStartInd
 功能描述  : 处理MMC上报的搜网开始消息
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史     :
  1.日    期  : 2015年01月30日
    作    者  : x00314862
    修改内容  : 新建

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSelectStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PLMN_SELECTION_START_IND_STRU                  *pstPlmnStartInd    = VOS_NULL_PTR;

    pstPlmnStartInd = (MMC_MSCC_PLMN_SELECTION_START_IND_STRU *)pstMsg;

    NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

    if (NAS_MSCC_PIF_PLMN_SELECTION_START == pstPlmnStartInd->enPlmnSeleStartFlag)
    {
        /* GUL模式按照原有逻辑通知MMA搜网开始,模式为3GPP */
        if (VOS_TRUE == NAS_MSCC_IsGULModeConfigured())
        {
            NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_3GPP);

            return VOS_TRUE;
        }

        /* CL模式下不在捕获流程中,通知MMA搜网开始,模式为DO_LTE；否则在CL捕获流程开始时通知 */
        if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
        {
            NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO_LTE);
        }
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_RcvMmcEOPlmnSetCnf
 功能描述  : MSCC模块收到MMC模块发送的ID_MMC_MSCC_EOPLMN_SET_CNF
 输入参数  : MMC_MSCC_EOPLMN_SET_CNF_STRU         *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :
 修改历史     :
  1.日    期  : 2015年01月30日
    作    者  : x00314862
    修改内容  : 新建

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcEOPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_EOPLMN_SET_CNF_STRU                  *pstMmcMsg       = VOS_NULL_PTR;

    pstMmcMsg   = (MMC_MSCC_EOPLMN_SET_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaEOPlmnSetCnf(pstMmcMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_SaveWCipherInfo
 功能描述  : 将MSCC发来的Cipher信息保存到全局变量
             (D_MSCC_UMTS_CIPHER_INFO_IND)
 输入参数  : const MSCC_UMTS_CIPHER_INFO_IND_STRU* pstCipherInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

  修改历史     :
  1.日    期  : 2015年01月30日
    作    者  : x00314862
    修改内容  : 新建
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcWCipherInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;

    pstCipherInfoInd = (MMC_MSCC_UMTS_CIPHER_INFO_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaWCipherInfo(pstCipherInfoInd);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MSCC_SndMmaGCipherInfoInd
 功能描述  : 将MSCC发来的Cipher信息保存到全局变量
             (D_MSCC_GPRS_CIPHER_INFO_IND)
 输入参数  : const MSCC_GPRS_CIPHER_INFO_IND_STRU* pstCipherInfoInd
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcGCipherInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU  *pstCipherInfoInd;
    pstCipherInfoInd = (MMC_MSCC_GPRS_CIPHER_INFO_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaGCipherInfo(pstCipherInfoInd);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MSCC_RcvMmcAcInfoChangeInd
 功能描述  : MSCC收到MSCC D_MSCC_AC_INFO_CHANGE_IND消息的处理
 输入参数  : MMC_MSCC_AC_INFO_CHANGE_IND_STRU *pstAcInfoChangeInd
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAcInfoChangeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_AC_INFO_CHANGE_IND_STRU   *pstAcInfoChangeInd;
    pstAcInfoChangeInd = (MMC_MSCC_AC_INFO_CHANGE_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaAcInfoChangeInd(pstAcInfoChangeInd);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_RcvMmcCampOnInd_PreProc
 功能描述  : 处理来自MMC的驻留指示消息
 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCampOnInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_CAMP_ON_IND_STRU_STRU      *pstCampOnInd = VOS_NULL_PTR;

    pstCampOnInd = (MMC_MSCC_CAMP_ON_IND_STRU_STRU*)pstMsg;

    NAS_MSCC_SndMmaCampOnInd(pstCampOnInd);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvMmcRfAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU      *pstRfAvail = VOS_NULL_PTR;

    pstRfAvail = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU*)pstMsg;

    /* the current rat is the master mode, just transfer it to mma */

    NAS_MSCC_SndMmaRfAvailInd(pstRfAvail);

    /* 当前MMC如果没有被激活的话，需要进状态机处理，有可能触发搜网 */
    if (VOS_FALSE == NAS_MSCC_Get3gppActiveFlg())
    {
        return VOS_FALSE;
    }


    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MSCC_Sta_DataTranAttri
 功能描述  : 收到MSCC上报的MSCC_DATATRAN_ATTRI_IND消息
 输入参数  : ucDataTranAttri MSCC上传得数据类型
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : x00314862
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStaDataTranAttri_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_DATATRAN_ATTRI_IND_STRU    *pstDataTranAttri;

    pstDataTranAttri = (MMC_MSCC_DATATRAN_ATTRI_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaDataTranAttri(pstDataTranAttri);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_Sta_CoverageAreaInd
 功能描述  : 收到MMC传上来的CoverageAreaInd
 输入参数  : MMC_MSCC_COVERAGE_AREA_IND_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月30日
    作    者   : x00314862
    修改内容   : 新生成函数
  2.日    期   : 2015年04月07日
    作    者   : y00307564
    修改内容   : 修改
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcStaCoverageAreaInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_COVERAGE_AREA_IND_STRU    *pCoverageAreaInd = VOS_NULL_PTR;

    pCoverageAreaInd = (MMC_MSCC_COVERAGE_AREA_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaCoverageInd(pCoverageAreaInd);

    /* Modified by y00307564 for CDMA Iteration 10 2015-4-07 begin */
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION == NAS_MSCC_GetCurrFsmId())
    {
        return VOS_FALSE;
    }
    /* Modified by y00307564 for CDMA Iteration 10 2015-4-07 end */

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MSCC_RcvMmcNetScanCnf_PreProc
 功能描述  : 收到MSCC传上来的netscan回复
 输入参数  : MMC_MSCC_NET_SCAN_CNF_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月02日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_NET_SCAN_CNF_STRU         *pstMmcNetScanCnf = VOS_NULL_PTR;

    pstMmcNetScanCnf = (MMC_MSCC_NET_SCAN_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaNetScanCnf(pstMmcNetScanCnf);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : MSCC_RcvMmcAbortNetScanCnf_PreProc
 功能描述  : 收到MSCC传上来的打断netscan回复
 输入参数  : MMC_MSCC_NET_SCAN_CNF_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAbortNetScanCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ABORT_NET_SCAN_CNF_STRU    *pstMmcAbortNetScanCnf = VOS_NULL_PTR;

    pstMmcAbortNetScanCnf = (MMC_MSCC_ABORT_NET_SCAN_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaAbortNetScanCnf(pstMmcAbortNetScanCnf);
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_RcvMmcEplmnInfoInd_PreProc
 功能描述  : 收到MSCC 等效plmn信息
 输入参数  : pstEplmnInfoIndMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcEplmnInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_EPLMN_INFO_IND_STRU       *pstEplmnInfoIndMsg  = VOS_NULL_PTR;

    pstEplmnInfoIndMsg   = (MMC_MSCC_EPLMN_INFO_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaEplmnInfoInd(pstEplmnInfoIndMsg);


    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    NAS_MSCC_FSM_ID_ENUM_UINT32          enCurrFsmId;
    NAS_MSCC_FSM_CTX_STRU               *pstCurFsm;
#endif
    MMC_MSCC_ACQ_CNF_STRU               *pstMmcMsccAcqCnf;



#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* Added by m00312079 for CDMA Iteration 10 2015-4-14 begin */
    enCurrFsmId = NAS_MSCC_GetCurrFsmId();
    /* in CL system acquire fsm, then enter fsm to proc this msg */
    if (NAS_MSCC_FSM_SYS_ACQ == enCurrFsmId)
    {
        /* Get the current FSM address*/
        pstCurFsm   = NAS_MSCC_GetCurFsmAddr();

        if (NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND == pstCurFsm->ulState)
        {
             return VOS_FALSE;
        }
    }
    /* Added by m00312079 for CDMA Iteration 10 2015-4-14 end */
#endif

    pstMmcMsccAcqCnf = (MMC_MSCC_ACQ_CNF_STRU *)pstMsg;

    NAS_MSCC_SndMmaAcqCnf(pstMmcMsccAcqCnf);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaPowerSaveReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SetPowerSaveReplyFlg(VOS_TRUE);

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcPowerSaveReq();

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcMsgLmmCellSignInfoInd_PreProc
 功能描述  : 收到MMC的LMM的小区信号信息指示消息
 输入参数  : pstEplmnInfoIndMsg - 消息内容
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcMsgLmmCellSignInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU            *pstLmmCellSignInfoInd = VOS_NULL_PTR;

    pstLmmCellSignInfoInd = (MMC_MSCC_LMM_CELL_SIGN_INFO_REPORT_IND_STRU *)pstMsg;

    /* 转发该消息给MMA模块 */
    NAS_MSCC_SndMmaLmmCellSignInfoReportInd(pstLmmCellSignInfoInd);

    return VOS_TRUE;
}









/*****************************************************************************
 函 数 名  : MSCC_RcvMmcRegCnf_PreProc
 功能描述  : 收到MSCC模块的reg cnf信息
 输入参数  : ulEventType
             pstMsg

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcRegCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaRegCnf((MMC_MSCC_REG_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmcPowerSaveCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SERVICE_STATUS_IND_STRU    stServiceSta;
    MMC_MSCC_POWER_SAVE_CNF_STRU       *pstPowerSaveCnf;

    pstPowerSaveCnf = (MMC_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

    PS_MEM_SET(&stServiceSta, 0X0, sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU));

    if (NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult)
    {
        NAS_MSCC_Set3gppActiveFlg(VOS_FALSE);
        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        /* notify mma no service */
        NAS_MSCC_SetCurr3gppPsServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        stServiceSta.bitOpSrvSta      = VOS_TRUE;
        stServiceSta.enServiceStatus  = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
        stServiceSta.enCnDomainId     = NAS_MSCC_PIF_SRVDOMAIN_CS_PS;
        stServiceSta.ucSimCsRegStatus = NAS_MSCC_GetSimCsRegStatus();
        stServiceSta.ucSimPsRegStatus = NAS_MSCC_GetSimPsRegStatus();

        NAS_MSCC_SndMmaServiceStatusInd(&stServiceSta);

        /* need reply to upplayer */
        if (VOS_TRUE == NAS_MSCC_GetPowerSaveReplyFlg())
        {
            NAS_MSCC_SndMmaPowerSaveCnf((MMC_MSCC_POWER_SAVE_CNF_STRU*)pstMsg);

            NAS_MSCC_SetPowerSaveReplyFlg(VOS_FALSE);
        }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (VOS_FALSE == NAS_MSCC_GetSimPsRegStatus())
        {
            NAS_MSCC_SndHsdDisableLteNtf();
        }
#endif
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : MSCC_RcvMmcUsimAuthFailInd_PreProc
 功能描述  : 收到MMC传上来的USIM鉴权失败原因值信息进行处理
 输入参数  : MMC_MSCC_USIM_AUTH_FAIL_IND_STRU *pMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcUsimAuthFailInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{

    MMC_MSCC_USIM_AUTH_FAIL_IND_STRU    *pstAuthFailInd  = VOS_NULL_PTR;

    pstAuthFailInd            = (MMC_MSCC_USIM_AUTH_FAIL_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaUsimAuthFailInd(pstAuthFailInd);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_RcvMmcCsServiceConnStatusInd_PreProc
 功能描述  : 收到MMC上报的cs业务信令连接状态指示消息
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcCsServiceConnStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU                *pstCsServiceConnStatusInd = VOS_NULL_PTR;


    pstCsServiceConnStatusInd = (MMC_MSCC_CS_SERVICE_CONN_STATUS_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaCsServiceConnStatusInd(pstCsServiceConnStatusInd);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcServRejInd_PreProc
 功能描述  : 收到MMC传上来的服务被拒原因值信息进行处理
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcServRejInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SERV_REJ_IND_STRU          *pstServRejInd = VOS_NULL_PTR;


    pstServRejInd = (MMC_MSCC_SERV_REJ_IND_STRU *) pstMsg;

    (VOS_VOID)NAS_MSCC_SndMmaServRejRsltInd(pstServRejInd);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_RcvMmcAttachCnf_PreProc
 功能描述  : 收到MMC传上来的attach cnf进行处理
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE:消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAttachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ATTACH_CNF_STRU            *pstAttachCnf = VOS_NULL_PTR;

    pstAttachCnf = (MMC_MSCC_ATTACH_CNF_STRU*)pstMsg;

    NAS_MSCC_SndMmaAttachCnf(pstAttachCnf);

    /* 不进状态机处理 */
    return VOS_TRUE;
}


/*****************************************************************************
  函 数 名  : MSCC_RcvMmcDetachInd_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数


*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcDetachInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_DETACH_IND_STRU            *pstDetachInd = VOS_NULL_PTR;
    pstDetachInd = (MMC_MSCC_DETACH_IND_STRU *) pstMsg;

    NAS_MSCC_SndMmaDetachInd(pstDetachInd);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcDetachCnf_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcDetachCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* 转发消息到MMA */
    NAS_MSCC_SndMmaDetachCnf((MMC_MSCC_DETACH_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPlmnListCnf_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnListCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发消息到MMA */
    NAS_MSCC_SndMmaPlmnListCnf((MMC_MSCC_PLMN_LIST_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPlmnListRej_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnListRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* 转发消息到MMA */
    NAS_MSCC_SndMmaPlmnListRej((MMC_MSCC_PLMN_LIST_REJ_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPlmnSpecialSelCnf_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSpecialSelCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* 转发消息到MMA */
    NAS_MSCC_SndMmaPlmnSpecialSelCnf((MMC_MSCC_PLMN_SPECIAL_SEL_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}



/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPlmnListAbortCnf_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnListAbortCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* 转发消息到MMA */
    NAS_MSCC_SndMmaPlmnListAbortCnf((MMC_MSCC_PLMN_LIST_ABORT_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcSpecPlmnSearchAbortCnf_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcSpecPlmnSearchAbortCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* 转发消息到MMA */
    NAS_MSCC_SndMmaSpecPlmnSearchAbortCnf((MMC_MSCC_SPEC_PLMN_SEARCH_ABORT_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPlmnSpecialSelRej_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnSpecialSelRej_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发消息到MMA */
    NAS_MSCC_SndMmaPlmnSpecialSelRej((MMC_MSCC_PLMN_SPECIAL_SEL_REJ_STRU*)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPlmnReselCnf_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPlmnReselCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* 转发消息到MMA */
    NAS_MSCC_SndMmaPlmnReselCnf((MMC_MSCC_PLMN_RESEL_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaCFPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcCFPlmnSetReq((MMA_MSCC_CFPLMN_SET_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaCFPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcCFPlmnQueryReq((MMA_MSCC_CFPLMN_QUERY_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmcCFPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发消息到MMA */
    NAS_MSCC_SndMmaCFPlmnSetCnf((MMC_MSCC_CFPLMN_SET_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmcCFPlmnQueryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发消息到MMA */
    NAS_MSCC_SndMmaCFPlmnQueryCnf((MMC_MSCC_CFPLMN_QUERY_CNF_STRU*)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaSdtConnedInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcSdtConnedInd((MMA_MSCC_OM_MAINTAIN_INFO_IND_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaPrefPlmnSetReq_PreProc
 功能描述  : 处理MMC服务状态上报指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月3日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPrefPlmnSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将设置prefplmn消息转发到mmc */
    NAS_MSCC_SndMmcPrefPlmnSetReq((MMA_MSCC_PREF_PLMN_SET_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaPrefPlmnQueryReq_PreProc
 功能描述  : 处理MMA

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年2月3日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaPrefPlmnQueryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将查询prefplmn消息转发到mmc */
    NAS_MSCC_SndMmcPrefPlmnQueryReq((MMA_MSCC_PREF_PLMN_QUERY_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPrefPlmnQueryCnf_PreProc
 功能描述  : 处理MMA

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月03日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPrefPlmnQueryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将查询prefplmn应答消息转发到mma */
    NAS_MSCC_SndMmaPrefPlmnQueryCnf((MMC_MSCC_PREF_PLMN_QUERY_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmcPrefPlmnSetCnf_PreProc
 功能描述  : 处理MMA

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月03日
   作    者   : y00307564
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPrefPlmnSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将设置prefplmn应答消息转发到mma */
    NAS_MSCC_SndMmaPrefPlmnSetCnf((MMC_MSCC_PREF_PLMN_SET_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmcPrefPlmnInfoInd_PreProc(
    VOS_UINT32                                               ulEventType,
    struct MsgCB                                            *pstMsg
)
{
    MMC_MSCC_PREF_PLMN_INFO_IND_STRU                        *pstPrefPlmnInd      = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU                       *pstMsccEhPlmnInfo   = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU                     *pstMsccUserPlmnInfo = VOS_NULL_PTR;
    NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU                     *pstMsccOperPlmnInfo = VOS_NULL_PTR;

    pstPrefPlmnInd = (MMC_MSCC_PREF_PLMN_INFO_IND_STRU *)pstMsg;


    if (NAS_MSCC_PREF_PLMN_UPLMN == pstPrefPlmnInd->enPrefPlmnType)
    {
        pstMsccUserPlmnInfo = NAS_MSCC_GetUserPlmnInfoAddr();

        PS_MEM_CPY(pstMsccUserPlmnInfo, &(pstPrefPlmnInd->stUplmnInfo),
                   sizeof(NAS_MSCC_PIF_SIM_USERPLMN_INFO_STRU));
    }

    if (NAS_MSCC_PREF_PLMN_HPLMN == pstPrefPlmnInd->enPrefPlmnType)
    {
        pstMsccEhPlmnInfo   = NAS_MSCC_GetEhPlmnInfoAddr();

        PS_MEM_CPY(pstMsccEhPlmnInfo,   &(pstPrefPlmnInd->stEhplmnInfo),
                   sizeof(NAS_MSCC_PIF_SIM_EHPLMN_INFO_STRU));
    }

    if (NAS_MSCC_PREF_PLMN_OPLMN == pstPrefPlmnInd->enPrefPlmnType)
    {
        pstMsccOperPlmnInfo = NAS_MSCC_GetOperPlmnInfoAddr();

        PS_MEM_CPY(pstMsccOperPlmnInfo, &(pstPrefPlmnInd->stOplmnInfo),
                   sizeof(NAS_MSCC_PIF_SIM_OPERPLMN_INFO_STRU));
    }

    return VOS_TRUE;
}




VOS_UINT32 NAS_MSCC_RcvMmaGetGeoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将获取地理位置信息请求转发到mmc */
    NAS_MSCC_SndMmcGetGeoReq((MMA_MSCC_GET_GEO_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmcGetGeoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将获取地理位置信息回复转发到mma */
    NAS_MSCC_SndMmaGetGeoCnf((MMC_MSCC_GET_GEO_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaStopGetGeoReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将停止获取地理位置信息请求转发到mmc */
    NAS_MSCC_SndMmcStopGetGeoReq((MMA_MSCC_STOP_GET_GEO_REQ_STRU *)pstMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmcStopGetGeoCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 将停止获取地理位置信息回复转发到mma */
    NAS_MSCC_SndMmaStopGetGeoCnf((MMC_MSCC_STOP_GET_GEO_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}


#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaCdmaMoCallStartNtf_PreProc
 功能描述  : 收到MMA的Cdma Mo Call Start Ntf消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数预处理完成
             VOS_FALSE:函数预处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : x00314862
    修改内容   : 新生成函数

  2.日    期   : 2015年7月27日
    作    者   : h00313353
    修改内容   : 迭代17 紧急呼
*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmaMoCallStartNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU         *pstCdmaMoCallStartNtf = VOS_NULL_PTR;

    pstCdmaMoCallStartNtf = (MMA_MSCC_CDMA_MO_CALL_START_NTF_STRU*)pstMsg;

    /* 转发该消息给hxd 或xsd模块 */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallStartNtf->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallStartNtf(pstCdmaMoCallStartNtf);
    }
    else
    {
        /* Modified by h00313353 for Iteration 17, 2015-7-25, begin */
        NAS_MSCC_Set1xSysAcqMoCallFlag(VOS_TRUE);

        NAS_MSCC_SndXsdCdmaMoCallStartNtf(pstCdmaMoCallStartNtf);

        /* 当前如果呼叫能下来，则默认1X RAT是支持的，这里仅判断1X是否激活 */
        if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
        {
            NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set1xActiveFlg(VOS_TRUE);

            NAS_MSCC_SndXsdSysAcqReq();
        }
        /* Modified by h00313353 for Iteration 17, 2015-7-25, end */
    }

    return VOS_FALSE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaCdmaMoCallRedialSysAcqNtf_PreProc
 功能描述  : 收到MMA的Cdma Mo Call Start Ntf消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数预处理完成
             VOS_FALSE:函数预处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmaMoCallRedialSysAcqNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU         *pstCdmaMoCallRedialSysAcqNtf = VOS_NULL_PTR;

    pstCdmaMoCallRedialSysAcqNtf = (MMA_MSCC_CDMA_MO_CALL_REDIAL_SYS_ACQ_NTF_STRU*)pstMsg;

    /* 转发该消息给hxd 或xsd模块 */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallRedialSysAcqNtf->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallRedialSysAcqNtf(pstCdmaMoCallRedialSysAcqNtf);
    }
    else
    {
        NAS_MSCC_SndXsdCdmaMoCallRedialSysAcqNtf(pstCdmaMoCallRedialSysAcqNtf);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaCdmaMoCallStartNtf_PreProc
 功能描述  : 收到MMA的Cdma Mo Call Start Ntf消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数预处理完成
             VOS_FALSE:函数预处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmaMoCallSuccessNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU   *pstCdmaMoCallSuccessNtf = VOS_NULL_PTR;

    pstCdmaMoCallSuccessNtf = (MMA_MSCC_CDMA_MO_CALL_SUCCESS_NTF_STRU *)pstMsg;

    /* 转发该消息给hxd 或xsd模块 */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallSuccessNtf->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallSuccessNtf(pstCdmaMoCallSuccessNtf);
    }
    else
    {
        NAS_MSCC_SndXsdCdmaMoCallSuccessNtf(pstCdmaMoCallSuccessNtf);
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaCdmaMoCallEndNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU   *pstCdmaMoCallEndNtf = VOS_NULL_PTR;

    pstCdmaMoCallEndNtf = (MMA_MSCC_CDMA_MO_CALL_END_NTF_STRU *)pstMsg;

    /* 转发该消息给hxd 或xsd模块 */
    if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmaMoCallEndNtf->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallEndNtf(pstCdmaMoCallEndNtf);
    }
    else
    {
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, begin */
        NAS_MSCC_Set1xSysAcqMoCallFlag(VOS_FALSE);
        /* Added by y00314741 for  CDMA Iteration 17, 2015-7-9, end */

        NAS_MSCC_SndXsdCdmaMoCallEndNtf(pstCdmaMoCallEndNtf);
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaCfreqLockNtf_PreProc
 功能描述  : 收到MMA的CfreqLockNtf消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : VOS_TRUE:函数预处理完成
             VOS_FALSE:函数预处理未完成
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCfreqLockNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CFREQ_LOCK_NTF_STRU   *pstCfreqLockNtf = VOS_NULL_PTR;

    pstCfreqLockNtf = (MMA_MSCC_CFREQ_LOCK_NTF_STRU *)pstMsg;

    /* 分发该消息给hxd和xsd模块 */
    NAS_MSCC_SndXsdCfreqLockNtf(pstCfreqLockNtf);

    /* Added by x00306642 for EVDO PILOT Iteration 1, 2015-07-20, begin */
    NAS_MSCC_SndHsdCfreqLockNtf(pstCfreqLockNtf);
    /* Added by x00306642 for EVDO PILOT Iteration 1, 2015-07-20, end */

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaCdmacsqSetReq_PreProc
 功能描述  : 收到MMA的CdmacsqSetReq消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年2月7日
    作    者   : x00314862
    修改内容   : 新生成函数

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaCdmacsqSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_CDMACSQ_SET_REQ_STRU   *pstCdmacsqSetReq = VOS_NULL_PTR;

    pstCdmacsqSetReq = (MMA_MSCC_CDMACSQ_SET_REQ_STRU *)pstMsg;

    /* 转发该消息给hxd 或xsd模块 */
    /*if (NAS_MSCC_PIF_CDMA_CALL_TYPE_DO_NORMAL_DATA_CALL == pstCdmacsqSetReq->enCallType)
    {
        NAS_MSCC_SndHsdCdmaMoCallEndNtf(pstCdmacsqSetReq);
    }
    else
    {
        NAS_MSCC_SndXsdCdmacsqSetReq(pstCdmacsqSetReq);
    }*/
    NAS_MSCC_SndXsdCdmacsqSetReq(pstCdmacsqSetReq);
    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvXsdCdmacsqSetCnf_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdCdmacsqSetCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaCdmacsqSetCnf((XSD_MSCC_CDMACSQ_SET_CNF_STRU *)pstMsg);

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvXsdCdmacsqSignalQualityInd_PreProc
 功能描述  : 处理MMC系统消息指示

 输入参数  : ulEventType  由消息ID与task ID决定
             pstMsg       消息地址
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdCdmacsqSignalQualityInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMmaCdmacsqSignalQualityInd((XSD_MSCC_CDMACSQ_IND_STRU *)pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvXsd1xSystemServiceInfoInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU               *pst1xSysSrvInfoInd;
    MSCC_HSD_1X_SYS_INFO_STRU                               st1xSysInfo;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8                      en1xServiceStatus;
    VOS_UINT8                                               ucIs1xLocationInfoChanged;
    NAS_MSCC_1X_SYS_INFO_STRU                              *pstOld1xSysInfo;
    VOS_UINT8                                               ucIs1xAvail;

    pst1xSysSrvInfoInd  = (XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU *)pstMsg;
    pstOld1xSysInfo     = NAS_MSCC_Get1xSysInfoAddr();

    if ((NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE  == pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus)
     || (NAS_MSCC_PIF_SERVICE_STATUS_LIMITED_SERVICE == pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus))
    {
        ucIs1xAvail = VOS_TRUE;
    }
    else
    {
        ucIs1xAvail = VOS_FALSE;
    }

    st1xSysInfo.usBandClass = pst1xSysSrvInfoInd->stSysSrvInfo.usBandClass;
    st1xSysInfo.usChannel   = pst1xSysSrvInfoInd->stSysSrvInfo.usFreq;
    st1xSysInfo.usSid       = pst1xSysSrvInfoInd->stSysSrvInfo.usSid;
    st1xSysInfo.usNid       = pst1xSysSrvInfoInd->stSysSrvInfo.usNid;

    /* Send the 1x Sys Change Ind to HSD if EVDO is supported */
    if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
    {
        NAS_MSCC_SndHsd1xSysChgInd(ucIs1xAvail, &st1xSysInfo);
    }

    if ((pstOld1xSysInfo->ulMcc != pst1xSysSrvInfoInd->stSysSrvInfo.stServiceInfo.ulMcc)
     || (pstOld1xSysInfo->ulMnc != pst1xSysSrvInfoInd->stSysSrvInfo.stServiceInfo.usMnc)
     || (pstOld1xSysInfo->usSid != pst1xSysSrvInfoInd->stSysSrvInfo.usSid)
     || (pstOld1xSysInfo->usNid != pst1xSysSrvInfoInd->stSysSrvInfo.usNid))
    {
        ucIs1xLocationInfoChanged = VOS_TRUE;
    }
    else
    {
        ucIs1xLocationInfoChanged = VOS_FALSE;
    }

    en1xServiceStatus = NAS_MSCC_Convert1xServiceStatusToMsccFormat(pst1xSysSrvInfoInd->stSysSrvInfo.enServiceStatus);

    NAS_MSCC_SetCurr1xServiceStatus(en1xServiceStatus);

    NAS_MSCC_Update1xSysInfo(pst1xSysSrvInfoInd);

    NAS_MSCC_SndMma1xSystemServiceInfoInd(pst1xSysSrvInfoInd);

    if ((VOS_TRUE == ucIs1xLocationInfoChanged)
     && (VOS_TRUE == ucIs1xAvail))
    {
        /* Update the 1x location info to NVIM if 1x has normal service and location info has changed */
        NAS_MSCC_UpdateLocationInfoToNvim();
    }

    /* in CL system acquire fsm, then enter fsm to proc this msg */
    if (NAS_MSCC_FSM_SYS_ACQ == NAS_MSCC_GetCurrFsmId())
    {
        if (NAS_MSCC_SYSACQ_STA_WAIT_INIT_LOC_INFO_IND == NAS_MSCC_GetFsmTopState())
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvXsd1xSystemTimeInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndMma1xSystemTimeInd((XSD_MSCC_1X_SYSTEM_TIME_IND_STRU *)pstMsg);

    return VOS_TRUE;
}

/* Added by y00322978 for CDMA Iteration 17, 2015-7-9, begin */
/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvXsdSidInd_PreProc
 功能描述  : mscc处理xsd的sid主动上报消息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : BOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月9日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdSidInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SID_IND_STRU              *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (MSCC_XSD_SID_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaSidInd(pstRcvMsg->usSid);
    return VOS_TRUE;
}
/* Added by y00322978 for CDMA Iteration 17, 2015-7-9, end */

/* Added by m00312079 for CDMA Iteration 12 2015-6-10 begin */
/*****************************************************************************
 函 数 名  : NAS_MSCC_CovertSessionType_PreProc
 功能描述  : 将HSD_MSCC之间的session type转换为MSCC_MMA之间的session type
 输入参数  :
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : m00312079
    修改内容   : 新生成函数
*****************************************************************************/
MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32 NAS_MSCC_CovertSessionType_PreProc(
    HSD_MSCC_SESSION_RELEASE_TYPE_ENUM_UINT32               enSessionRelType
)
{
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enCurrSessionRelType;

    if (HSD_MSCC_SESSION_RELEASE_TYPE_0 == enSessionRelType)
    {
        enCurrSessionRelType = MSCC_MMA_SESSION_RELEASE_TYPE_0;
    }
    else if (HSD_MSCC_SESSION_RELEASE_TYPE_A == enSessionRelType)
    {
        enCurrSessionRelType = MSCC_MMA_SESSION_RELEASE_TYPE_A;
    }
    else
    {
        enCurrSessionRelType = MSCC_MMA_SESSION_RELEASE_TYPE_BUTT;
    }

    return enCurrSessionRelType;
}
/* Added by m00312079 for CDMA Iteration 12 2015-6-10 end */

/* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
VOS_UINT32 NAS_MSCC_RcvHsdSessionNegRsltInd_PreProc(
/* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, end */
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_SESSION_NEG_RSLT_IND_STRU                     *pstSessionInfo = VOS_NULL_PTR;
    MSCC_MMA_HRPD_SESSION_RELEASE_TYPE_ENUM_UINT32          enSessionRelType;

    /* Modified by y00307564 for CDMA Iteration 10 2015-4-16 begin */
    pstSessionInfo = (HSD_MSCC_SESSION_NEG_RSLT_IND_STRU *)pstMsg;

    if (VOS_TRUE == NAS_MSCC_IsNeedDiscardHsdServiceStatusInd_PreProc(pstSessionInfo->enRslt))
    {
        NAS_MSCC_MNTN_LogDiscardServStaInfo(NAS_MSCC_DISCARD_HSD_SERVICE_STATUS_IND);

        return VOS_TRUE;
    }
    /* Modified by y00307564 for CDMA Iteration 10 2015-4-16 end */

    if (HSD_MSCC_SESSION_NEG_RESULT_SUCC == pstSessionInfo->enRslt)
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);

        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
        enSessionRelType = NAS_MSCC_CovertSessionType_PreProc(pstSessionInfo->enCurrSessionRelType);

        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NORMAL_SERVICE,
                                            pstSessionInfo->ucIsNewSession,
                                            pstSessionInfo->ucIsEhrpdSupport,
                                            enSessionRelType);
        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, end */

        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE);

        /* 判断是否需要启动或者重启BSR Timer */
        if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
        {
            if (VOS_TRUE == NAS_MSCC_IsNeedRestartBsrTimer())
            {
                NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
                NAS_MSCC_StartBsrTimer();
            }
            else
            {
                if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
                {
                    NAS_MSCC_StartBsrTimer();
                }
            }
        }
    }
    else
    {
        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                            pstSessionInfo->ucIsNewSession,
                                            pstSessionInfo->ucIsEhrpdSupport,
                                            MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);
        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, end */

        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdOverheadMsgInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_OVERHEAD_MSG_IND_STRU     *pstHsdMsccOhm            = VOS_NULL_PTR;
    NAS_MSCC_HRPD_SYS_INFO_STRU         stOldHrpdSysInd;

    pstHsdMsccOhm = (HSD_MSCC_OVERHEAD_MSG_IND_STRU *)pstMsg;

    PS_MEM_SET(&stOldHrpdSysInd, 0x0, sizeof(NAS_MSCC_HRPD_SYS_INFO_STRU));
    PS_MEM_CPY(&stOldHrpdSysInd, NAS_MSCC_GetHrpdSysInfoAddr(), sizeof(NAS_MSCC_HRPD_SYS_INFO_STRU));

    NAS_MSCC_UpdateHrpdSysInfo(pstHsdMsccOhm);

    NAS_MSCC_SndMmaHrpdOverheadMsgInd((HSD_MSCC_OVERHEAD_MSG_IND_STRU *)pstMsg);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvHsdDataCallRedialAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{



    return VOS_TRUE;

}


VOS_UINT32 NAS_MSCC_RcvHsdHrpdCasStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_CAS_STATUS_IND_STRU       *pstHsdMsccCasStatusInd   = VOS_NULL_PTR;

    pstHsdMsccCasStatusInd = (HSD_MSCC_CAS_STATUS_IND_STRU *)pstMsg;

    if (HSD_MSCC_HRPD_CAS_STATUS_ENUM_CONN == pstHsdMsccCasStatusInd->enCasStatus)
    {
        NAS_MSCC_SetHrpdConnExistFlg(VOS_TRUE);
    }
    else
    {
        NAS_MSCC_SetHrpdConnExistFlg(VOS_FALSE);
    }

    /* send cas status to xsd */
    NAS_MSCC_SndXsdHrpdCasStatusInd((HSD_MSCC_CAS_STATUS_IND_STRU *)pstMsg);

    return VOS_TRUE;
}


/* Added by t00323010 for MSCC Iteration 10 2015-4-2 begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_ProcBsrTimerExpired_PreProc
Description     :   This function is used to check whether satisfy conditions to enter BSR FSM
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE:不进入BSR处理
                    VOS_FALSE:进入BSR处理
Modify History:
    1)  Date    :   2014-4-2
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_ProcBsrTimerExpired_PreProc(VOS_VOID)
{
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enMsccSleepTimerStatus;
    NAS_MSCC_TIMER_STATUS_ENUM_UINT8    enMsccAvailTimerStatus;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enCurrFsmId;
    VOS_UINT8                           ucHrpdConnExistFlg;
    VOS_UINT8                           ucLteEpsConnExistFlg;
    NAS_MSCC_MNTN_BSR_CTRL_INFO_STRU    stBsrCtrlInfo;

    enMsccSleepTimerStatus  = NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_SLEEP_TIMER);
    enMsccAvailTimerStatus  = NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_AVAILABLE_TIMER);
    ucHrpdConnExistFlg      = NAS_MSCC_GetHrpdConnExistFlg();
    ucLteEpsConnExistFlg    = NAS_MSCC_GetLteEpsConnExistFlg();
    enCurrFsmId             = NAS_MSCC_GetCurrFsmId();

    /* log 打印 */
    stBsrCtrlInfo.en3gppPsServiceStatus     = NAS_MSCC_GetCurr3gppPsServiceStatus();
    stBsrCtrlInfo.ucSimPsRegStatus          = NAS_MSCC_GetSimPsRegStatus();
    stBsrCtrlInfo.enHrpdPsServiceStatus     = NAS_MSCC_GetCurrHrpdServiceStatus();
    stBsrCtrlInfo.enCsimCardStatus          = NAS_MSCC_GetCsimCardStatus();
    stBsrCtrlInfo.enUsimCardStatus          = NAS_MSCC_GetUsimCardStatus();
    stBsrCtrlInfo.ucMlplMsplValidFlag       = NAS_MSCC_GetMlplMsplValidFlag();
    stBsrCtrlInfo.ulIsHrpdLteBothSupported  = NAS_MSCC_IsHrpdAndLteBothSupported();
    stBsrCtrlInfo.ucHrpdConnExistFlg        = ucHrpdConnExistFlg;
    stBsrCtrlInfo.ucLteEpsConnExistFlg      = ucLteEpsConnExistFlg;
    stBsrCtrlInfo.enMsccSleepTimerStatus    = enMsccSleepTimerStatus;
    stBsrCtrlInfo.enMsccAvailTimerStatus    = enMsccAvailTimerStatus;
    stBsrCtrlInfo.enCurrFsmId               = enCurrFsmId;

    NAS_MSCC_MNTN_LogBsrCtrlInfo(&stBsrCtrlInfo);


    /* 如果有搜网相关定时器在运行，不需要进入BSR FSM */
    if ((NAS_MSCC_TIMER_STATUS_RUNING == enMsccAvailTimerStatus)
     || (NAS_MSCC_TIMER_STATUS_RUNING == enMsccSleepTimerStatus))
    {
        return VOS_TRUE;
    }

    /* 如果MSCC在子状态机执行过程中，启动BSR Retry定时器，等待 */
    /* 如果在数据业务过程中，启动BSR Retry定时器，等待 */
    if ((NAS_MSCC_FSM_L1_MAIN != enCurrFsmId)
     || (VOS_TRUE == ucLteEpsConnExistFlg)
     || (VOS_TRUE == ucHrpdConnExistFlg))
    {
        NAS_MSCC_StartTimer(TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH,
                            TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRI_SYSTEM_SEARCH_LEN);

        return VOS_TRUE;
    }

    /* 如果当前网络不是最高优先级网络，需要进入BSR FSM */
    if (VOS_TRUE == NAS_MSCC_IsBgSearchHighPriSysAllowed())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvTiBsrTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* Ps domain switch to 1x */
    if (VOS_TRUE == NAS_MSCC_GetDataServiceSwitchTo1xFlg())
    {
        return VOS_FALSE;
    }

    return NAS_MSCC_ProcBsrTimerExpired_PreProc();
}

/*****************************************************************************
Function Name   :   NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchTimerExpired_PreProc
Description     :   PreProc for TI_NAS_MSCC_PERIOD_TRYING_HIGH_PRIO_NETWORK_SEARCH
Input parameters:   None
Output parameters:  None
Return Value    :   VOS_TRUE:no need to enter Main FSM
                    VOS_FALSE:need to enter Main FSM
Modify History:
    1)  Date    :   2014-4-2
        Author  :   t00323010
        Modify content :    Create for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvTiPeriodTryingHighPrioNetworkSearchTimerExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    return NAS_MSCC_ProcBsrTimerExpired_PreProc();
}
/* Added by t00323010 for MSCC Iteration 10 2015-4-2 end */

/* Added by m00312079 for CDMA Iteration 10 2015-4-7 begin */

VOS_UINT32 NAS_MSCC_RcvXsdSysAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU   *pstXsdSysAcqCnf = VOS_NULL_PTR;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdSrvst;

    pstXsdSysAcqCnf = (XSD_MSCC_SYSTEM_ACQUIRE_IND_STRU *)pstMsg;

    /* power off过程中或者SCAN定时器超时处理过程中收到XSD上报搜网结果,直接上报MMA搜网失败 */
    if (NAS_MSCC_FSM_POWER_OFF == NAS_MSCC_GetCurrFsmId())
    {
        NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL,
                                           MSCC_MMA_ACQ_SYS_TYPE_1X,
                                           MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);
        return VOS_TRUE;
    }

    /* Get the final result to send to MMA */
    NAS_MSCC_SndMmaSystemAcquireEndInd(NAS_MSCC_GetSystemAcquireFinalResult(pstXsdSysAcqCnf->enRslt),
                                       MSCC_MMA_ACQ_SYS_TYPE_1X,
                                       MSCC_MMA_CL_SYSTEM_ACQUIRE_RESULT_TYPE_BUTT);

    if (NAS_MSCC_PIF_ACQUIRED_RESULT_SUCC == pstXsdSysAcqCnf->enRslt)
    {
        NAS_MSCC_StopTimer(TI_NAS_MSCC_SCAN_TIMER);

        return VOS_TRUE;
    }

    /* if bothe 1x,lte and hrpd are no service, start scan timer */
    if (NAS_MSCC_PIF_ACQUIRED_RESULT_FAIL == pstXsdSysAcqCnf->enRslt)
    {
        /* 1x loss service,clear data service switch to 1x flag,in the next flow,will start available
           timer after CL system acquire both failed*/
        NAS_MSCC_SetDataServiceSwitchTo1xFlg(VOS_FALSE);

        enHrpdSrvst = NAS_MSCC_GetCurrHrpdServiceStatus();

        if ((NAS_MSCC_SERVICE_STATUS_NO_SERVICE == NAS_MSCC_GetCurr3gppPsServiceStatus())
         && (NAS_MSCC_SERVICE_STATUS_NO_SERVICE == enHrpdSrvst))
        {
            /* we start the timer only in CL mode */
            if (VOS_FALSE == NAS_MSCC_IsGULModeConfigured())
            {
                NAS_MSCC_StartTimer(TI_NAS_MSCC_SCAN_TIMER, NAS_MSCC_GetScanTimerLength());
            }
        }
    }

    return VOS_TRUE;

}
/* Added by m00312079 for CDMA Iteration 10 2015-4-7 end */



VOS_UINT32 NAS_MSCC_RcvXsdSysAcqStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

    NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_1X);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvHsdSysAcqStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

    /* 如果不支持LTE,即为HRPD单独的捕获流程;通知捕获开始的系统模式为DO */
    if (VOS_FALSE == NAS_MSCC_IsSpecRatSupported(NAS_MSCC_PIF_NET_RAT_TYPE_LTE))
    {
        NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO);

        return VOS_TRUE;
    }

    /* CL模式下不在捕获流程中,通知MMA搜网开始,模式为DO_LTE；否则在CL捕获流程开始时通知 */
    if (NAS_MSCC_FSM_SYS_ACQ != NAS_MSCC_GetCurrFsmId())
    {
        NAS_MSCC_SndMmaSystemAcquireStartInd(MSCC_MMA_ACQ_SYS_TYPE_DO_LTE);
    }

    return VOS_TRUE;
}


/* Added by y00307564 for CDMA Iteration 10 2015-4-14 begin */
/*****************************************************************************
Function Name   :   NAS_MSCC_IsNeedDiscardHsdServiceStatusInd_PreProc
Description     :   是否需要屏蔽状态上报.
Input parameters:   HSD_MSCC_SESSION_NEG_RSLT_ENUM_UINT32       enRslt
Output parameters:  None.
Return Value    :   TRUE
Modify History:
    1)  Date    :   2015-04-14
        Author  :   y00307564
        Modify content :    Create
*****************************************************************************/
VOS_UINT32 NAS_MSCC_IsNeedDiscardHsdServiceStatusInd_PreProc(
    HSD_MSCC_SESSION_NEG_RSLT_ENUM_UINT32       enRslt
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm  = VOS_NULL_PTR;

    pstCurFsm = NAS_MSCC_GetCurFsmAddr();
    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION == pstCurFsm->enFsmId)
    {
        if ((NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF            == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF_REACQ_LTE  == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF_REACQ_LTE == pstCurFsm->ulState))
        {
            return VOS_TRUE;
        }

        if (HSD_MSCC_SESSION_NEG_RESULT_SUCC != enRslt)
        {
            if (NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF == pstCurFsm->ulState)
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}
/* Added by y00307564 for CDMA Iteration 10 2015-4-14 end */

/* Added by z00316370 for UTS 2015-5-22 begin */
/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaHandsetInfoQryReq_PreProc
 功能描述  : 收到MMA的HandsetInfoQryReq消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
UINT32 NAS_MSCC_RcvMmaHandsetInfoQryReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU   *pstInfoQryReq = VOS_NULL_PTR;

    pstInfoQryReq = (MMA_MSCC_HANDSET_INFO_QRY_REQ_STRU *)pstMsg;

    /* 给XSD发送查询请求 */
    NAS_MSCC_SndXsdHandsetInfoQryReq((VOS_UINT32)pstInfoQryReq->enInfoType);

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvXsdHandsetInfoQryReq_PreProc
 功能描述  : 收到XSD的ID_XSD_MSCC_HANDSET_INFO_QRY_CNF消息的处理
 输入参数  : ulEventType - 消息类型
             pstMsg      - 消息的首地址
 输出参数  : 无
 返 回 值  : UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年5月22日
    作    者   : z00316370
    修改内容   : 新生成函数

*****************************************************************************/
UINT32 NAS_MSCC_RcvXsdHandsetInfoQryCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *pstCnfMsg  = VOS_NULL_PTR;
    MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU  stInfoCnf;

    PS_MEM_SET(&stInfoCnf, 0x00, sizeof(MSCC_MMA_HANDSET_INFO_QRY_CNF_STRU));

    pstCnfMsg = (XSD_MSCC_HANDSET_INFO_QRY_CNF_STRU *)pstMsg;

    stInfoCnf.enInfoType     = (MMA_MSCC_HANDSET_INFO_TYPE_ENUM_UINT32)pstCnfMsg->ulInfoType;
    stInfoCnf.ucCasState     = pstCnfMsg->ucCasState;
    stInfoCnf.ucCasSubSta    = pstCnfMsg->ucCasSubSta;
    stInfoCnf.enHighVer      = (MSCC_MMA_1X_CAS_P_REV_ENUM_UINT8)pstCnfMsg->ucHighVer;

    /* 给MMA发送查询回复 */
    NAS_MSCC_SndMmaHandsetInfoQryCnf(&stInfoCnf);

    return VOS_TRUE;
}

/* Added by z00316370 for UTS 2015-5-22 end */


VOS_UINT32 NAS_MSCC_RcvMmaPsRatTypeNtf_Main_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_PS_RAT_TYPE_NTF_STRU      *pstPsRatTypeNtf;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  en3gppPsServiceSta;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  enHrpdServiceSta;
    NAS_MSCC_SERVICE_STATUS_ENUM_UINT8  en1xServiceSta;

    pstPsRatTypeNtf = (MMA_MSCC_PS_RAT_TYPE_NTF_STRU *)pstMsg;

    en3gppPsServiceSta = NAS_MSCC_GetCurr3gppPsServiceStatus();
    enHrpdServiceSta   = NAS_MSCC_GetCurrHrpdServiceStatus();
    en1xServiceSta     = NAS_MSCC_GetCurr1xServiceStatus();

    /* 数据业务切换到1X时,此时HRPD和LTE应该无服务,此时需要启动BSR定时器,
       BSR超时或进行指定搜LTE */
    if ((NAS_MSCC_PIF_PS_RATTYPE_1X             == pstPsRatTypeNtf->enPsRatType)
     && (NAS_MSCC_SERVICE_STATUS_NORMAL_SERVICE == en1xServiceSta)
     && (NAS_MSCC_SERVICE_STATUS_NO_SERVICE     == en3gppPsServiceSta)
     && (NAS_MSCC_SERVICE_STATUS_NO_SERVICE     == enHrpdServiceSta))
    {
        NAS_MSCC_SetDataServiceSwitchTo1xFlg(VOS_TRUE);

        if (NAS_MSCC_FSM_L1_MAIN != NAS_MSCC_GetCurrFsmId())
        {
            return VOS_TRUE;
        }

        if (VOS_TRUE == NAS_MSCC_IsNeedPerformCLSysAcq())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_AVAILABLE_TIMER);

            NAS_MSCC_StartBsrTimer();
        }
    }

    return VOS_TRUE;
}

/* Added by h00313353 for Iteration 17, 2015-7-9, begin */
/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaQuitCallBackInd_PreProc
 功能描述  : 收到MMA模块的ID_MMA_MSCC_QUIT_CALL_BACK_IND信息
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年07月08日
   作    者   : h00313353
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaQuitCallBackNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_SndXsdEndEmcCallBackNtf();

    return VOS_TRUE;
}
/* Added by h00313353 for Iteration 17, 2015-7-9, end */
/* Added by y00322978 for CDMA Iteration 17, 2015-7-13, begin */
/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvMmaSetCSidListReq_PreProc
 功能描述  : AT CSIDLIST
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月13日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmaSetCSidListReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_XSD_SET_CSIDLIST_REQ_STRU     *pstSndMsg = VOS_NULL_PTR;
    MMA_MSCC_SET_CSIDLIST_REQ_STRU     *pstRcvMsg = VOS_NULL_PTR ;

    pstRcvMsg = (MMA_MSCC_SET_CSIDLIST_REQ_STRU *)pstMsg;
    /* 申请内存  */
    pstSndMsg = (MSCC_XSD_SET_CSIDLIST_REQ_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                           sizeof(MSCC_XSD_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvMmaSetCSidListReq_PreProc:ERROR: Memory Alloc Error for pMsg");
        return VOS_TRUE;
    }

    PS_MEM_SET((VOS_INT8*)pstSndMsg + VOS_MSG_HEAD_LENGTH, 0x00,
                     sizeof(MSCC_XSD_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstSndMsg->stMsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid    = UEPS_PID_XSD;
    pstSndMsg->stMsgHeader.ulSenderCpuId    = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid      = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulLength         = sizeof(MSCC_XSD_SET_CSIDLIST_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName        = ID_MSCC_XSD_SET_CSIDLIST_REQ;
    PS_MEM_CPY(&pstSndMsg->stSidWhiteList, &pstRcvMsg->stSidWhiteList, sizeof(NAS_MSCC_PIF_OPER_LOCK_SYS_WHITE_STRU));

    /* 调用VOS发送原语 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvXsdSetCSidListCnf_PreProc
 功能描述  : set csid list 结果上报
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月13日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdSetCSidListCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_SET_CSIDLIST_CNF_STRU     *pstSndMsg = VOS_NULL_PTR;
    XSD_MSCC_SET_CSIDLIST_CNF_STRU     *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (XSD_MSCC_SET_CSIDLIST_CNF_STRU *)pstMsg;
        /* 申请消息包 */
    pstSndMsg = (MSCC_MMA_SET_CSIDLIST_CNF_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvXsdSetCSidListCnf_PreProc():ERROR:Memory Alloc Error!");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(MSCC_MMA_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstSndMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(MSCC_MMA_SET_CSIDLIST_CNF_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_MSCC_MMA_SET_CSIDLIST_CNF;
    pstSndMsg->ulRslt                        = pstRcvMsg->ulRslt;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);
    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvXsdEmcCallBackNtf_PreProc
 功能描述  : call back 模式主动上报
 输入参数  : VOS_UINT32                          ulEventType
             struct MsgCB                       *pstMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月14日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvXsdEmcCallBackNtf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU *pstSndMsg = VOS_NULL_PTR;
    XSD_MSCC_EMC_CALLBACK_IND_STRU     *pstRcvMsg = VOS_NULL_PTR;

    pstRcvMsg = (XSD_MSCC_EMC_CALLBACK_IND_STRU *)pstMsg;
        /* 申请消息包 */
    pstSndMsg = (MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU *)PS_ALLOC_MSG(UEPS_PID_MSCC,
                        sizeof(MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSndMsg)
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvXsdSetCSidListCnf_PreProc():ERROR:Memory Alloc Error!");
        return VOS_TRUE;
    }

    PS_MEM_SET(((VOS_UINT8*)pstSndMsg) + VOS_MSG_HEAD_LENGTH,
                0x00,
                sizeof(MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    pstSndMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulSenderPid       = UEPS_PID_MSCC;
    pstSndMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstSndMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MMA;
    pstSndMsg->stMsgHeader.ulLength          = sizeof(MSCC_MMA_1X_EMC_CALL_BACK_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstSndMsg->stMsgHeader.ulMsgName         = ID_MSCC_MMA_1X_EMC_CALL_BACK_IND;
    pstSndMsg->enCallBackState               = pstRcvMsg->enCallBackState;

    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, begin */
    NAS_MSCC_LogMsgInfo((MSG_HEADER_STRU*)pstSndMsg);
    /* Added by y00322978 for CDMA Iteration 17, 2015-7-2, end */

    /* 发送消息 */
    PS_SEND_MSG(UEPS_PID_MSCC, pstSndMsg);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvXsdSyncServiceAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU               *pst1xSyncSrvAvailableInd = VOS_NULL_PTR;
    MSCC_MMA_SYNC_SERVICE_AVAIL_IND_STRU                    stSyncSrvAvailInd;

    pst1xSyncSrvAvailableInd = (XSD_MSCC_SYNC_SERVICE_AVAILABLE_IND_STRU *)pstMsg;

    PS_MEM_SET(&stSyncSrvAvailInd, 0x00, sizeof(stSyncSrvAvailInd));
    stSyncSrvAvailInd.usBandClass     = pst1xSyncSrvAvailableInd->usBandClass;
    stSyncSrvAvailInd.usFreq          = pst1xSyncSrvAvailableInd->usFreq;
    stSyncSrvAvailInd.usSid           = pst1xSyncSrvAvailableInd->usSid;
    stSyncSrvAvailInd.usNid           = pst1xSyncSrvAvailableInd->usNid;
    stSyncSrvAvailInd.enServiceStatus = pst1xSyncSrvAvailableInd->enServiceStatus;
    stSyncSrvAvailInd.ucRoamingInd    = pst1xSyncSrvAvailableInd->ucRoamingInd;

    NAS_MSCC_SndMmaSyncServiceAvailInd(&stSyncSrvAvailInd);

    return VOS_TRUE;
}

/* Added by y00322978 for CDMA Iteration 17, 2015-7-13, end */

VOS_UINT32 NAS_MSCC_RcvXsdCurUeStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_UE_STATE_IND_STRU         *pstUeStatusInd;

    pstUeStatusInd = (XSD_MSCC_UE_STATE_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaUeStatusInd(pstUeStatusInd->ucUeMainState,
                               pstUeStatusInd->ucUeSubState);

    return VOS_TRUE;
}



#endif


#if (FEATURE_ON == FEATURE_CL_INTERWORK)
/*****************************************************************************
 函 数 名  : MSCC_RcvMmcAcqInd_PreProc
 功能描述  : 收到MSCC模块的acq ind信息
 输入参数  : ulEventType
             pstMsg

 输出参数  : 无
 返 回 值  : VOS_TRUE
 调用函数  :
 被调函数  :

 修改历史     :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcAcqInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_ACQ_IND_STRU               *pstMmcMmaAcqInd = VOS_NULL_PTR;

    pstMmcMmaAcqInd = (MMC_MSCC_ACQ_IND_STRU *)pstMsg;

    NAS_MSCC_SndMmaAcqInd(pstMmcMmaAcqInd);

    return VOS_TRUE;
}
#endif



#if ((FEATURE_ON == FEATURE_MULTI_MODEM) || (FEATURE_ON == FEATURE_UE_MODE_CDMA))

/*****************************************************************************
 函 数 名  : MSCC_RcvMmcPsServiceConnStatusInd_PreProc
 功能描述  : 收到MSCC模块PS域的连接状态信息
 输入参数  : ulEventType
             pstMsg

 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数
 2.日    期   : 2015年04月07日
   作    者   : t00323010
   修改内容   : 存储连接状态到mscc ctx,for Iteration 10
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcPsServiceConnStatusInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU                *pstPsServiceConnStatusInd = VOS_NULL_PTR;

    pstPsServiceConnStatusInd = (MMC_MSCC_PS_SERVICE_CONN_STATUS_IND_STRU *)pstMsg;

    /* Added by t00323010 for CDMA Iteration 10 2015-4-7 begin */
    if (VOS_TRUE == pstPsServiceConnStatusInd->ucPsServiceConnStatusFlag)
    {
        NAS_MSCC_SetLteEpsConnExistFlg(VOS_TRUE);
    }
    else
    {
        NAS_MSCC_SetLteEpsConnExistFlg(VOS_FALSE);
    }
    /* Added by t00323010 for CDMA Iteration 10 2015-4-7 end */

    NAS_MSCC_SndMmaPsServiceConnStatusInd(pstPsServiceConnStatusInd);

    return VOS_TRUE;
}
#endif

#if (FEATURE_ON == FEATURE_MULTI_MODEM)

VOS_UINT32 NAS_MSCC_RcvMmaOtherModemInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU                  *pstOtherModemInfoNtf = VOS_NULL_PTR;

    pstOtherModemInfoNtf = (MMA_MSCC_OTHER_MODEM_INFO_NOTIFY_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcOtherModemInfoNotify(pstOtherModemInfoNtf);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaOtherModemDplmnNplmnInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU       *pstOhterModemDplmnNplmnInfoNtf = VOS_NULL_PTR;

    pstOhterModemDplmnNplmnInfoNtf = (MMA_MSCC_OTHER_MODEM_DPLMN_NPLMN_INFO_NOTIFY_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcOtherModemDplmnNplmnInfoNotify(pstOhterModemDplmnNplmnInfoNtf);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaNcellInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_NCELL_INFO_NOTIFY_STRU    *pstNcellInfoNtf = VOS_NULL_PTR;

    pstNcellInfoNtf = (MMA_MSCC_NCELL_INFO_NOTIFY_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcNcellInfoNotify(pstNcellInfoNtf);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaPsTransferNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_PS_TRANSFER_NOTIFY_STRU   *pstPsTransferNtf = VOS_NULL_PTR;

    pstPsTransferNtf = (MMA_MSCC_PS_TRANSFER_NOTIFY_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcPsTransferNotify(pstPsTransferNtf);

    return VOS_TRUE;
}
#endif
VOS_UINT32 NAS_MSCC_RcvMmaSrvAcqReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_SRV_ACQ_REQ_STRU          *pstSrvAcqReq = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList    = VOS_NULL_PTR;
    VOS_UINT32                          i;
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    VOS_UINT32                          ulEnterFsmFlg;
    VOS_UINT32                          ulState;
#endif

    pstSrvAcqReq = (MMA_MSCC_SRV_ACQ_REQ_STRU *)pstMsg;

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    ulEnterFsmFlg = VOS_FALSE;
#endif
    pstRatList    = &(pstSrvAcqReq->stRatList);

    for (i = 0; i < pstRatList->ucRatNum; i++)
    {
/* Modified by h00313353 for CDMA Iteration 15, 2015-6-5, begin */
#if (FEATURE_ON == FEATURE_DSDS)
        /* 目前CL模式下没有这种使用场景，代码先保留 */
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL == pstRatList->aenRatType[i])
        {
            /* Set the Camp On flag to FALSE */
            NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

            NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);

            /* 转发该消息给MMC模块 */
            NAS_MSCC_SndMmcSrvAcqReq(pstSrvAcqReq);
        }
#endif
/* Modified by h00313353 for CDMA Iteration 15, 2015-6-5, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X == pstRatList->aenRatType[i])
        {
            ulState = NAS_MSCC_GetFsmTopState();

            if ( (NAS_MSCC_FSM_L1_MAIN == NAS_MSCC_GetCurrFsmId())
              && (NAS_MSCC_L1_STA_DEACTIVE == ulState) )
            {
                /* MSCC处于deactive状态的话，需要进状态机处理 */
                ulEnterFsmFlg = VOS_TRUE;
            }
            else
            {
                NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

                NAS_MSCC_Set1xActiveFlg(VOS_TRUE);

                /* 转发该消息给1X模块 */
                NAS_MSCC_SndXsdSrvAcqReq(pstSrvAcqReq);
            }
        }

        /* 目前没有这种使用场景，代码先保留 */
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD == pstRatList->aenRatType[i])
        {
            NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

            NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

            /* 转发该消息给HSD模块 */
            NAS_MSCC_SndHsdSrvAcqReq(pstSrvAcqReq);
        }
#endif
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (VOS_TRUE == ulEnterFsmFlg)
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvMmaBeginSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *pstBeginSessionNtf = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstBeginSessionNtf = (MMA_MSCC_BEGIN_SESSION_NOTIFY_STRU *)pstMsg;

    pstRatList = &(pstBeginSessionNtf->stRatList);

    for (i = 0; i < pstRatList->ucRatNum; i++)
    {
/* Modified by h00313353 for CDMA Iteration 15, 2015-6-5, begin */
#if (FEATURE_ON == FEATURE_DSDS)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL == pstRatList->aenRatType[i])
        {
            /* 转发该消息给MMC模块 */
            NAS_MSCC_SndMmcBeginSessionNotify(pstBeginSessionNtf);
        }
#endif
/* Modified by h00313353 for CDMA Iteration 15, 2015-6-5, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X == pstRatList->aenRatType[i])
        {
            /* 转发该消息给1X模块 */
            NAS_MSCC_SndXsdBeginSessionNotify(pstBeginSessionNtf);
        }

        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD == pstRatList->aenRatType[i])
        {
            /* 本迭代中没有HSD的代码开发，目前没有应用场景 */

            /* 转发该消息给HSD模块 */
            NAS_MSCC_SndHsdBeginSessionNotify(pstBeginSessionNtf);
        }
#endif
    }


    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaEndSessionNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_END_SESSION_NOTIFY_STRU   *pstEndSessionNtf = VOS_NULL_PTR;
    NAS_MSCC_PIF_SRV_ACQ_RAT_LIST_STRU *pstRatList = VOS_NULL_PTR;
    VOS_UINT32                          i;

    pstEndSessionNtf = (MMA_MSCC_END_SESSION_NOTIFY_STRU *)pstMsg;

    pstRatList = &(pstEndSessionNtf->stRatList);

    for (i = 0; i < pstRatList->ucRatNum; i++)
    {
/* Modified by h00313353 for CDMA Iteration 15, 2015-6-5, begin */
#if (FEATURE_ON == FEATURE_DSDS)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_GUL == pstRatList->aenRatType[i])
        {
            /* 转发该消息给MMC模块 */
            NAS_MSCC_SndMmcEndSessionNotify(pstEndSessionNtf);
        }
#endif
/* Modified by h00313353 for CDMA Iteration 15, 2015-6-5, end */

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_1X == pstRatList->aenRatType[i])
        {
            /* 转发该消息给1X模块 */
            NAS_MSCC_SndXsdEndSessionNotify(pstEndSessionNtf);
        }

        if (NAS_MSCC_PIF_SRV_ACQ_RAT_TYPE_HRPD == pstRatList->aenRatType[i])
        {
            /* 转发该消息给HSD模块 */
            NAS_MSCC_SndHsdEndSessionNotify(pstEndSessionNtf);
        }
#endif
    }

    return VOS_TRUE;
}


/*****************************************************************************
 函 数 名  : MSCC_RcvMmcSrvAcqCnf_PreProc
 功能描述  : 收到mmc的srv acq cnf消息
 输入参数  : ulEventType - 事件类型
             pstMsg      - 消息内容
 输出参数  : 无
 返 回 值  : VOS_FALSE:消息处理未完成，需要继续处理
             VOS_TRUE: 消息处理完成，后续不需要继续处理
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2015年02月02日
   作    者   : x00314862
   修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvMmcSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SRV_ACQ_CNF_STRU           *pstSrvAcqCnf = VOS_NULL_PTR;

    pstSrvAcqCnf = (MMC_MSCC_SRV_ACQ_CNF_STRU *)pstMsg;

    /* 目前不存在1X和LTE一起搜得场景，后续CDMA支持IMS后，CL模式时，可能同时搜1X和LTE，
       只要有一个接入技术成功，则就给MMA回复成功；目前没有使用场景 */

    if (NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        NAS_MSCC_Set3gppCampOnFlag(VOS_TRUE);
    }

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmaSrvAcqCnf(pstSrvAcqCnf);

    return VOS_TRUE;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 NAS_MSCC_RcvXsdSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SRV_ACQ_CNF_STRU          *pstSrvAcqCnf = VOS_NULL_PTR;

    pstSrvAcqCnf = (XSD_MSCC_SRV_ACQ_CNF_STRU *)pstMsg;

    /* 目前不存在1X和LTE一起搜得场景，后续CDMA支持IMS后，CL模式时，可能同时搜1X和LTE，
       只要有一个接入技术成功，则就给MMA回复成功；目前没有使用场景 */

    if (NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        NAS_MSCC_Set1xCampOnFlag(VOS_TRUE);
    }

    /* 转发该消息给MMC模块，由于MMC与MSCC的接口都是转定义于NAS_MSCC_PIF_SRV_ACQ_CNF_STRU
       所以这边直接强制转换进行复用 */
    NAS_MSCC_SndMmaSrvAcqCnf((MMC_MSCC_SRV_ACQ_CNF_STRU *)pstSrvAcqCnf);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdSrvAcqCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    XSD_MSCC_SRV_ACQ_CNF_STRU          *pstSrvAcqCnf = VOS_NULL_PTR;

    pstSrvAcqCnf = (XSD_MSCC_SRV_ACQ_CNF_STRU *)pstMsg;

    if (NAS_MSCC_PIF_SRV_ACQ_RESULT_SUCCESS == pstSrvAcqCnf->enResult)
    {
        NAS_MSCC_SetHrpdCampOnFlag(VOS_TRUE);
    }

    /* 转发该消息给MMC模块，由于MMC与MSCC的接口都是转定义于NAS_MSCC_PIF_SRV_ACQ_CNF_STRU
       所以这边直接强制转换进行复用 */
    NAS_MSCC_SndMmaSrvAcqCnf((MMC_MSCC_SRV_ACQ_CNF_STRU *)pstSrvAcqCnf);

    return VOS_TRUE;
}
#endif



#if (FEATURE_ON == FEATURE_IMS)


VOS_UINT32 NAS_MSCC_RcvMmaImsSrvInfoNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU  *pstImsSrvInfoNtf = VOS_NULL_PTR;

    pstImsSrvInfoNtf = (MMA_MSCC_IMS_SRV_INFO_NOTIFY_STRU *)pstMsg;

    /* 转发该消息给MMC模块 */
    NAS_MSCC_SndMmcImsSrvInfoNotify(pstImsSrvInfoNtf);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvImsaImsVoiceCapNotify_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU                    *pstImsVoiceCap = VOS_NULL_PTR;
    VOS_UINT8                                               ucImsVoiceAvail;
    MSCC_IMSA_IMS_VOICE_CAP_ENUM_UINT8                      enOldImsVoiceCap;

    enOldImsVoiceCap = NAS_MSCC_GetImsVoiceCapability();

    pstImsVoiceCap          = (IMSA_MSCC_IMS_VOICE_CAP_NOTIFY_STRU *)pstMsg;



    /* 停止等待IMSA的IMS voice是否可用消息定时器 */
    NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_IMS_VOICE_CAP_NOTIFY);

    /* 更新IMS voice是否可用信息到SDC中 */
    if (MSCC_IMSA_IMS_VOICE_CAP_AVAILABLE == pstImsVoiceCap->enImsVoiceCap)
    {
        ucImsVoiceAvail = VOS_TRUE;
    }
    else
    {
        ucImsVoiceAvail = VOS_FALSE;
    }

    /* 通知MMC当前IMS voice是否可用 */
    NAS_MSCC_SndMmcImsVoiceCapNotify(ucImsVoiceAvail, pstImsVoiceCap->ucIsExistPersistentBearer);
    NAS_MSCC_SetPersistentBearerState(pstImsVoiceCap->ucIsExistPersistentBearer);

    NAS_MSCC_SetImsVoiceCapability(pstImsVoiceCap->enImsVoiceCap);

    if (enOldImsVoiceCap != pstImsVoiceCap->enImsVoiceCap)
    {
        /* 通知MMA当前IMS VOICE是否可用 */
        NAS_MSCC_SndMmaImsVoiceCapInd(ucImsVoiceAvail);
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaImsVoiceCapNtfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 通知MMC当前IMS voice不可用 */
    NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
    NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
    NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);

    /* 通知SPM当前IMS VOICE是否可用 */
    NAS_MSCC_SndMmaImsVoiceCapInd(VOS_FALSE);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaImsStartReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 通知IMSA开启IMS协议栈 */
    NAS_MSCC_SndImsaStartReq(MSCC_IMSA_START_TYPE_IMS_SWITCH_ON);

    /* Start timer TI_NAS_MSCC_WAIT_IMSA_START_CNF */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_START_CNF, TI_NAS_MSCC_WAIT_IMSA_START_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaImsStopReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    /* 通知IMSA关闭IMS协议栈 */
    NAS_MSCC_SndImsaStopReq(MSCC_IMSA_STOP_TYPE_IMS_SWITCH_OFF);

    /* Start timer TI_NAS_IMSA_WAIT_IMSA_POWER_OFF_CNF */
    NAS_MSCC_StartTimer(TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF, TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF_LEN);

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMmaVoiceDomainChangeInd_PreProc(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU                  *pstVoiceDomainInd = VOS_NULL_PTR;
    NAS_MSCC_IMS_CONFIG_PARA_STRU                          *pstImsCfgInfo = VOS_NULL_PTR;

    pstImsCfgInfo     = NAS_MSCC_GetImsCfgInfo();
    pstVoiceDomainInd = (MMA_MSCC_VOICE_DOMAIN_CHANGE_IND_STRU *)pstMsg;

    /* 更新VOICE DOMAIN的值 */
    pstImsCfgInfo->enVoiceDomain = pstVoiceDomainInd->enVoiceDomain;

    /* 通知IMSA变化后的VOICE DOMAIN值 */
    NAS_MSCC_SndImsaVoiceDomainChangeInd(pstVoiceDomainInd->enVoiceDomain);

    /* 通知MMC变化后的VOICE DOMAIN值 */
    NAS_MSCC_SndMmcVoiceDomainChangeInd(pstVoiceDomainInd->enVoiceDomain);

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvImsaStartCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    /* 判断当前状态机的状态，如果不在开机的状态里面，则认为是IMS SWITCH触发的开机请求 */
    if (NAS_MSCC_FSM_SWITCH_ON != enFsmId)
    {
        /* 更新IMS业务能力 */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_TRUE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_TRUE;

        /* Stop the timer */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_START_CNF);

        /* 通知MMC当前IMS的开关状态 */
        NAS_MSCC_SndMmcImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_ON);

        /* 通知IMSA 驻留信息 */
        NAS_MSCC_SndImsaCampInfoChangeInd();

        /* 通知IMSA Service Change Ind*/
        NAS_MSCC_SndImsaSrvInfoNotify(NAS_MSCC_GetCurr3gppPsServiceStatus(), VOS_FALSE, VOS_FALSE);

        /* 给IMSA回复START CNF消息 */
        NAS_MSCC_SndMmaImsStartCnf(NAS_MSCC_PIF_IMS_START_RESULT_SUCC);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MSCC_RcvImsaStopCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    /* 判断当前状态机的状态，如果不在关机的状态里面，则认为是IMS SWITCH触发的关机请求 */
    if (NAS_MSCC_FSM_POWER_OFF != enFsmId)
    {
        /* 更新IMS业务能力 */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_FALSE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_FALSE;

        /* Stop the timer */
        NAS_MSCC_StopTimer(TI_NAS_MSCC_WAIT_IMSA_POWER_OFF_CNF);

        /* 通知MMC当前IMS的开关状态 */
        NAS_MSCC_SndMmcImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF);

        /* 通知MMC当前IMS voice不可用 */
        NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);

        /* 通知MMA当前IMS VOICE不可用 */
        NAS_MSCC_SndMmaImsVoiceCapInd(VOS_FALSE);

        /* 给IMSA回复STOP CNF消息 */
        NAS_MSCC_SndMmaImsStopCnf(NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaStartCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    /* 判断当前状态机的状态，如果不在开机的状态里面，则认为是IMS SWITCH触发的开机请求 */
    if (NAS_MSCC_FSM_SWITCH_ON != enFsmId)
    {
        /* 更新IMS业务能力 */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_FALSE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_FALSE;

        /* 给MMA回复START CNF消息 */
        NAS_MSCC_SndMmaImsStartCnf(NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MSCC_RcvTiWaitImsaPowerOffCnfExpired_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_IMS_CONFIG_PARA_STRU      *pstImsCfgInfo = VOS_NULL_PTR;
    NAS_MSCC_FSM_ID_ENUM_UINT32         enFsmId;

    pstImsCfgInfo = NAS_MSCC_GetImsCfgInfo();
    enFsmId       = NAS_MSCC_GetCurrFsmId();

    /* 判断当前状态机的状态，如果不在关机的状态里面，则认为是IMS SWITCH触发的关机请求 */
    if (NAS_MSCC_FSM_POWER_OFF != enFsmId)
    {
        /* 更新IMS业务能力 */
        pstImsCfgInfo->stImsRatSupport.ucLteImsSupportFlag = VOS_FALSE;
        pstImsCfgInfo->stImsRatSupport.ucLteEmsSupportFlag = VOS_FALSE;

        /* 通知MMC当前IMS的开关状态 */
        NAS_MSCC_SndMmcImsSwitchStateInd(NAS_MSCC_PIF_IMS_SWITCH_STATE_OFF);

        /* 通知MMC当前IMS voice不可用 */
        NAS_MSCC_SndMmcImsVoiceCapNotify(MSCC_MMC_IMS_VOICE_CAPABILITY_NOT_AVAIL, MSCC_MMC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetPersistentBearerState(NAS_MSCC_PERSISTENT_BEARER_STATE_NOT_EXIST);
        NAS_MSCC_SetImsVoiceCapability(MSCC_IMSA_IMS_VOICE_CAP_UNAVAILABLE);


        /* 通知MMA当前IMS VOICE不可用 */
        NAS_MSCC_SndMmaImsVoiceCapInd(VOS_FALSE);

        /* 给IMSA回复STOP CNF消息 */
        NAS_MSCC_SndMmaImsStopCnf(NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT);

        return VOS_TRUE;
    }

    return VOS_FALSE;
}


#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

VOS_UINT32 NAS_MSCC_RcvXsdPowerSaveCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMC_MSCC_SERVICE_STATUS_IND_STRU                        stServiceSta;
    XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU                st1xSysSrvInfoInd;
    XSD_MSCC_POWER_SAVE_CNF_STRU                           *pstPowerSaveCnf;
    MSCC_HSD_1X_SYS_INFO_STRU           st1xSysInfo;

    pstPowerSaveCnf = (XSD_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

    PS_MEM_SET(&stServiceSta, 0X0, sizeof(MMC_MSCC_SERVICE_STATUS_IND_STRU));

    if (NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult)
    {
        NAS_MSCC_Set1xActiveFlg(VOS_FALSE);
        NAS_MSCC_Set1xCampOnFlag(VOS_FALSE);

        /* notify mma no service */
        NAS_MSCC_SetCurr1xServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        PS_MEM_SET(&st1xSysSrvInfoInd, 0x0, sizeof(XSD_MSCC_1X_SYSTEM_SERVICE_INFO_IND_STRU));
        st1xSysSrvInfoInd.stSysSrvInfo.enServiceStatus       = NAS_MSCC_PIF_SERVICE_STATUS_NO_SERVICE;
        st1xSysSrvInfoInd.stSysSrvInfo.enBaseStationInfoIncl = PS_TRUE;

        NAS_MSCC_SndMma1xSystemServiceInfoInd(&st1xSysSrvInfoInd);

        /* power save 1X系统后，如果HRPD系统支持，通知一下HSD */
        if (VOS_TRUE == NAS_MSCC_IsPlatformSupportCdmaEVDO())
        {
            PS_MEM_SET(&st1xSysInfo, 0, sizeof(MSCC_HSD_1X_SYS_INFO_STRU));

            NAS_MSCC_SndHsd1xSysChgInd(VOS_FALSE, &st1xSysInfo);
        }
    }

    return VOS_FALSE;
}



VOS_UINT32 NAS_MSCC_RcvHsdPowerSaveCnf_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_POWER_SAVE_CNF_STRU       *pstPowerSaveCnf;

    pstPowerSaveCnf = (HSD_MSCC_POWER_SAVE_CNF_STRU*)pstMsg;

    if (NAS_MSCC_PIF_POWER_SAVE_SUCCESS == pstPowerSaveCnf->enResult)
    {
        NAS_MSCC_SetHrpdActiveFlg(VOS_FALSE);
        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);

        /* notify mma no service */
        NAS_MSCC_SetCurrHrpdServiceStatus(NAS_MSCC_SERVICE_STATUS_NO_SERVICE);

        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
        NAS_MSCC_SndMmaHrpdServiceStatusInd(MSCC_MMA_HRPD_SERVICE_STATUS_NO_SERVICE,
                                            VOS_FALSE,
                                            VOS_FALSE,
                                            MSCC_MMA_SESSION_RELEASE_TYPE_BUTT);
        /* Modify by l00324781 for CDMA Iteration 12, 2015-5-30, end */
    }

    return VOS_FALSE;
}
VOS_UINT32 NAS_MSCC_IsNeedDiscardMmcServiceStatusInd_PreProc(
    NAS_MSCC_PIF_SERVICE_STATUS_ENUM_UINT32      enServiceStatus
)
{
    NAS_MSCC_FSM_CTX_STRU              *pstCurFsm = VOS_NULL_PTR;

    pstCurFsm = NAS_MSCC_GetCurFsmAddr();

    if (NAS_MSCC_FSM_BETTER_SYSTEM_RESELECTION == pstCurFsm->enFsmId)
    {
        if ((NAS_MSCC_BSR_STA_WAIT_HSD_POWER_SAVE_CNF                == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_MMC_POWER_SAVE_CNF_REACQ_HRPD     == pstCurFsm->ulState)
         || (NAS_MSCC_BSR_STA_WAIT_HSD_SYSTEM_ACQUIRE_CNF_REACQ_HRPD == pstCurFsm->ulState))
        {
            return VOS_TRUE;
        }

        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE != enServiceStatus)
        {
            if (NAS_MSCC_BSR_STA_WAIT_MMC_PLMN_SEARCH_CNF == pstCurFsm->ulState)
            {
                return VOS_TRUE;
            }
        }
    }

    return VOS_FALSE;
}


VOS_UINT32 NAS_MSCC_ProcPsServiceStatusIndInCLMode_PreProc(
    MMC_MSCC_SERVICE_STATUS_IND_STRU   *pstSrvStatusInd
)
{
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enUsimCardStatus;
    NAS_MSCC_PIF_CARD_STATUS_ENUM_UINT8 enCsimCardStatus;

    /* 不论是否CL模式,统一更新NV */
    if ((VOS_TRUE                                   == NAS_MSCC_IsLtePlmnIdChanged())
     && (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstSrvStatusInd->enServiceStatus))
    {
        /* Update the location info to NVIM if the service status is normal service and the location info is changed */
        NAS_MSCC_UpdateLocationInfoToNvim();
    }

    /* SYSCFGEX不同时支持HRPD+LTE则不处理该消息 */
    if (VOS_FALSE == NAS_MSCC_IsHrpdAndLteBothSupported())
    {
        return VOS_TRUE;
    }

    /* MLPL和MSPL无效则不处理该消息 */
    if (VOS_FALSE== NAS_MSCC_GetMlplMsplValidFlag())
    {
        return VOS_TRUE;
    }

    enUsimCardStatus   = NAS_MSCC_GetUsimCardStatus();
    enCsimCardStatus   = NAS_MSCC_GetCsimCardStatus();

    /* 非CSIM+USIM应用则不处理该消息 */
    if ((NAS_MSCC_PIF_CARD_STATUS_USIM_PRESENT != enUsimCardStatus)
     || (NAS_MSCC_PIF_CARD_STATUS_CSIM_PRESENT != enCsimCardStatus))
    {
        return VOS_TRUE;
    }

    /* BG搜网流程中判定是否需要丢弃该服务状态指示消息 */
    if (VOS_TRUE == NAS_MSCC_IsNeedDiscardMmcServiceStatusInd_PreProc(pstSrvStatusInd->enServiceStatus))
    {
        NAS_MSCC_MNTN_LogDiscardServStaInfo(NAS_MSCC_DISCARD_MMC_SERVICE_STATUS_IND);

        return VOS_TRUE;
    }

    if (VOS_TRUE == NAS_MSCC_IsNeedStartBsrTimer())
    {
        if (VOS_TRUE == NAS_MSCC_IsNeedRestartBsrTimer())
        {
            NAS_MSCC_StopTimer(TI_NAS_MSCC_BSR_TIMER);
            NAS_MSCC_StartBsrTimer();
        }
        else
        {
            if (NAS_MSCC_TIMER_STATUS_RUNING != NAS_MSCC_GetTimerStatus(TI_NAS_MSCC_BSR_TIMER))
            {
                NAS_MSCC_StartBsrTimer();
            }
        }
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvHsdRfAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU      *pstRfAvail = VOS_NULL_PTR;

    pstRfAvail = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaRfAvailInd(pstRfAvail);

    /* if HRPD is deactive, mscc should enter active state to do */
    if (VOS_FALSE == NAS_MSCC_GetHrpdActiveFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
VOS_UINT32 NAS_MSCC_RcvXsdRfAvailableInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU      *pstRfAvail = VOS_NULL_PTR;

    pstRfAvail = (NAS_MSCC_PIF_RF_AVAILABLE_IND_STRU*)pstMsg;

    NAS_MSCC_SndMmaRfAvailInd(pstRfAvail);

    if (VOS_FALSE == NAS_MSCC_Get1xActiveFlg())
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}


#endif

/* Added by x00314862 for CDMA Iteration 6 2015-2-10 end */

#ifdef DMT
VOS_UINT32 NAS_MSCC_RcvMsccMofiyMlplRecordReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MLPL_STRU                                     *pstMlplInfo;
    NAS_MSCC_MSCC_MODIFY_MLPL_RECORD_REQ_STRU              *pstMdyMlplRecReq;
    VOS_UINT8                                               ucMlplRecIndex;
    VOS_UINT8                                               ucMlplRecTagIndex;
    VOS_UINT8                                               i;

    pstMdyMlplRecReq = (NAS_MSCC_MSCC_MODIFY_MLPL_RECORD_REQ_STRU *)pstMsg;
    pstMlplInfo      = NAS_MSCC_GetMlplInfoAddr();

    pstMlplInfo->ucIsContainDefRec = pstMdyMlplRecReq->ucIsContainDefRec;

    for ( i = 0; i < pstMdyMlplRecReq->ucRecNum; i++)
    {
        ucMlplRecIndex = pstMdyMlplRecReq->astMlplRecord[i].ucMlplRecIndex;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->ucIsRecValid   = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucIsRecValid;
        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->ucLocParamType = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucLocParamType;
        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->ucMsplIndex = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucMsplIndex;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->stLocParamVal.usMcc
                        = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.usMcc;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->stLocParamVal.usMnc
                        = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.usMnc;

        ucMlplRecTagIndex = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.ucSysLocTagIndex;

        pstMlplInfo->apstMlplRec[ucMlplRecIndex]->stLocParamVal.astSysLocTag[ucMlplRecTagIndex]
                    = pstMdyMlplRecReq->astMlplRecord[i].stMlplRec.stSysLocTag;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvMsccMofiyMsplIdReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    NAS_MSCC_MSPL_STRU                                     *pstMsplInfo;
    NAS_MSCC_MSCC_MODIFY_MSPL_ID_REQ_STRU                  *pstMdyMsplIdReq;
    VOS_UINT8                                               ucMsplIdIndex;
    VOS_UINT8                                               ucMsplRecIndex;
    VOS_UINT8                                               i;

    pstMdyMsplIdReq = (NAS_MSCC_MSCC_MODIFY_MSPL_ID_REQ_STRU *)pstMsg;
    pstMsplInfo     = NAS_MSCC_GetMsplInfoAddr();

    for ( i = 0; i < pstMdyMsplIdReq->ucRecNum; i++)
    {
        ucMsplIdIndex = pstMdyMsplIdReq->astMsplId[i].ucMlplIdIndex;

        pstMsplInfo->apstMsplId[ucMsplIdIndex]->ucIsMsplIdValid = pstMdyMsplIdReq->astMsplId[i].stMsplId.ucIsMsplIdValid;
        pstMsplInfo->apstMsplId[ucMsplIdIndex]->ucMsplId        = pstMdyMsplIdReq->astMsplId[i].stMsplId.ucMsplId;

        ucMsplRecIndex = pstMdyMsplIdReq->astMsplId[i].stMsplId.ucMsplRecIndex;

        pstMsplInfo->apstMsplId[ucMsplIdIndex]->astMsplRec[ucMsplRecIndex]  = pstMdyMsplIdReq->astMsplId[i].stMsplId.stMsplRec;
    }

    return VOS_TRUE;
}


VOS_UINT32 NAS_MSCC_RcvSetCardReadStubTypeReq_PreProc(
    VOS_UINT32                                              ulEventType,
    struct MsgCB                                           *pstMsg
)
{
    NAS_MSCC_SET_CARD_READ_STUB_TYPE_REQ_STRU              *pstStubReqMsg;

    pstStubReqMsg = (NAS_MSCC_SET_CARD_READ_STUB_TYPE_REQ_STRU *)pstMsg;

    genCardReadStubTypeForDmt = pstStubReqMsg->enStubType;

    return VOS_TRUE;
}

#endif


VOS_UINT32 NAS_MSCC_RcvMmaAutoReselSetReq_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    MMA_MSCC_AUTO_RESEL_SET_STRU       *pstAutoReselSetReq;

    pstAutoReselSetReq = (MMA_MSCC_AUTO_RESEL_SET_STRU *)pstMsg;

    NAS_MSCC_SndMmcAutoReselSetReq(pstAutoReselSetReq->ucActiveFlg);

    return VOS_TRUE;
}



VOS_UINT32 NAS_MSCC_RcvMmcSrchedPlmnInfo_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
       /* 转发消息到MMA */
    NAS_MSCC_SndMmaSrchedPlmnInfo((MMC_MSCC_SRCHED_PLMN_INFO_IND_STRU*)pstMsg);

    return VOS_TRUE;
}

/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvHsdInterSysEndInd_PreProc
 功能描述  : mscc收到消息HSD_MSCC_INTERSYS_END_IND_STRU，根据携带的参数选择不同处理流程
 输入参数  : pstMsg      - 消息内容
             ulEventType - 消息类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息处理未完成

 修改历史      :
 1.日    期   : 2015年5月30日
   作    者   : l00324781
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysEndInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_INTERSYS_END_IND_STRU     *pstInterSysEndInd       = VOS_NULL_PTR;

    pstInterSysEndInd = (HSD_MSCC_INTERSYS_END_IND_STRU*)pstMsg;

    /* CL模式下，LTE2HRPD，hsd收到CAS_CNAS_HRPD_IRAT_FROM_LTE消息后，向mscc发送该消息
        此时，消息参数填写VOS_RATMODE_BUTT
    */
    if (VOS_RATMODE_BUTT == pstInterSysEndInd->enCampedRatMode)
    {
        NAS_MSCC_Set3gppActiveFlg(VOS_FALSE);
        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);
        NAS_MSCC_SetHrpdActiveFlg(VOS_TRUE);

        NAS_MSCC_SndMmcInterSysHrpdInd();
    }
    /* CL模式下，HRPD2LTE, 失败回退到HRPD，收到CAS_CNAS_RESUME_ID消息后，向mscc发送END_IND，参数填写VOS_RATMODE_HRPD.
        此时向mma发送INTERSYS_END_IND消息
    */
    else if (VOS_RATMODE_HRPD == pstInterSysEndInd->enCampedRatMode)
    {
        NAS_MSCC_SndMmaInterSysEndInd(pstInterSysEndInd->enCampedRatMode);
    }
    /* CL模式下，HRPD2LTE, 成功，hsd收到CAS_CNAS_HRPD_IRAT_TO_LTE消息后，向mscc发送END_IND，参数填写VOS_RATMODE_LTE */
    else if (VOS_RATMODE_LTE == pstInterSysEndInd->enCampedRatMode)
    {
        NAS_MSCC_Set3gppActiveFlg(VOS_TRUE);
        NAS_MSCC_Set3gppCampOnFlag(VOS_FALSE);

        NAS_MSCC_SetHrpdCampOnFlag(VOS_FALSE);
        NAS_MSCC_SetHrpdActiveFlg(VOS_FALSE);

        NAS_MSCC_SndMmaInterSysEndInd(pstInterSysEndInd->enCampedRatMode);
    }
    else  /* 其它值，异常，打印记录 */
    {
        NAS_ERROR_LOG(UEPS_PID_MSCC, "NAS_MSCC_RcvHsdInterSysEndInd_PreProc:The IE enCampedRatMode value is error!");
    }

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : NAS_MSCC_RcvHsdInterSysStartInd_PreProc
 功能描述  : mscc收到消息HSD_MSCC_INTERSYS_START_IND_STRU,处理该消息
 输入参数  : pstMsg      - 消息内容
             ulEventType - 消息类型
 输出参数  : 无
 输出参数  : 无
 返 回 值  : VOS_TRUE:消息处理完成
             VOS_FALSE:消息处理未完成

 修改历史      :
 1.日    期   : 2015年5月30日
   作    者   : l00324781
   修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 NAS_MSCC_RcvHsdInterSysStartInd_PreProc(
    VOS_UINT32                          ulEventType,
    struct MsgCB                       *pstMsg
)
{
    HSD_MSCC_INTERSYS_START_IND_STRU                       *pstInterSysStartInd = VOS_NULL_PTR;
    NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_UINT32                 enMsccInterSysCause;

    pstInterSysStartInd = (HSD_MSCC_INTERSYS_START_IND_STRU*)pstMsg;

    /* 枚举类型转换 */
    switch (pstInterSysStartInd->enInterSysCause)
    {
        case MSCC_HSD_INTERSYS_CAUSE_RESELECT:
            enMsccInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_RESELECT;
            break;
        case MSCC_HSD_INTERSYS_CAUSE_REDIR:
            enMsccInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_REDIR;
            break;
        case MSCC_HSD_INTERSYS_CAUSE_HO:
            enMsccInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_HO;
            break;
        default:  /* MSCC_HSD_INTERSYS_CAUSE_ENUM_BUTT */
            enMsccInterSysCause = NAS_MSCC_PIF_INTERSYS_CAUSE_ENUM_BUTT;
            break;
    }

    /* CL模式下，HRPD2LTE, hsd收到CAS_CNAS_HRPD_SUSPEND_IND消息，发起挂起，
        同时向mscc发送该消息，mscc通知mma  */
    NAS_MSCC_SndMmaInterSysStartInd(pstInterSysStartInd->enOrignRatMode,
                                pstInterSysStartInd->enDestRatMode,
                                enMsccInterSysCause);

    return VOS_TRUE;
}
#endif
/* Added by l00324781 for CDMA Iteration 12, 2015-5-30, end */
#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */



