

/*****************************************************************************
  1 头文件包含
*****************************************************************************/


#include "TafMmaCtx.h"
#include "TafMmaProcNvim.h"
#include "TafLog.h"
#include "NasUsimmApi.h"
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
#include "TafMmaMntn.h"
#include "TafMmaComFunc.h"
/* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

#include "TafSdcCtx.h"

#include "NasOmTrans.h"
/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-20, begin */
#include "TafStdlib.h"
/* Added by y00322978 for CDMA 1X Iteration 17, 2015-8-20, end */

#include "NasComm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_TAF_MMA_COM_FUNC_C

/*****************************************************************************
  2 常量定义
*****************************************************************************/
/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, begin */
#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

TAF_MMA_SESSION_STATUS_MAP_STRU          g_astTafMmaSessionStatusMapTbl[] =
{
    {NAS_OM_MMA_HRPD_SESSION_STATUS_CLOSE,                    HSM_MMA_SESSION_STATUS_CLOSE},
    {NAS_OM_MMA_HRPD_SESSION_STATUS_OPEN,                     HSM_MMA_SESSION_STATUS_OPEN},
    {NAS_OM_MMA_HRPD_SESSION_STATUS_BUTT,                     HSM_MMA_SESSION_STATUS_BUTT},
};
TAF_MMA_CDMA_PHONE_MODE_MAP_STRU         g_astTafMmaCdmaPhoneModeMapTbl[] =
{
    {NAS_OM_MMA_PHONE_MODE_MINI,                        TAF_SDC_PHONE_MODE_MINI},
    {NAS_OM_MMA_PHONE_MODE_FULL,                        TAF_SDC_PHONE_MODE_FULL},
    {NAS_OM_MMA_PHONE_MODE_TXOFF,                       TAF_SDC_PHONE_MODE_TXOFF},
    {NAS_OM_MMA_PHONE_MODE_RXOFF,                       TAF_SDC_PHONE_MODE_RXOFF},
    {NAS_OM_MMA_PHONE_MODE_RFOFF,                       TAF_SDC_PHONE_MODE_RFOFF},
    {NAS_OM_MMA_PHONE_MODE_FT,                          TAF_SDC_PHONE_MODE_FT},
    {NAS_OM_MMA_PHONE_MODE_RESET,                       TAF_SDC_PHONE_MODE_RESET},
    {NAS_OM_MMA_PHONE_MODE_VDFMINI,                     TAF_SDC_PHONE_MODE_VDFMINI},
    {NAS_OM_MMA_PHONE_MODE_POWEROFF,                    TAF_SDC_PHONE_MODE_POWEROFF},
    {NAS_OM_MMA_PHONE_MODE_LOWPOWER,                    TAF_SDC_PHONE_MODE_LOWPOWER},
};
TAF_MMA_SYS_MODE_MAP_STRU          g_astTafMmaSysModeMapTbl[] =
{
    {NAS_OM_MMA_SYS_MODE_GSM,                       TAF_SDC_SYS_MODE_GSM},
    {NAS_OM_MMA_SYS_MODE_WCDMA,                     TAF_SDC_SYS_MODE_WCDMA},
    {NAS_OM_MMA_SYS_MODE_LTE,                       TAF_SDC_SYS_MODE_LTE},
    {NAS_OM_MMA_SYS_MODE_CDMA_1X,                   TAF_SDC_SYS_MODE_CDMA_1X},
    {NAS_OM_MMA_SYS_MODE_EVDO,                      TAF_SDC_SYS_MODE_EVDO},
    {NAS_OM_MMA_SYS_MODE_HYBRID,                    TAF_SDC_SYS_MODE_HYBRID},
    {NAS_OM_MMA_SYS_MODE_SVLTE,                     TAF_SDC_SYS_MODE_SVLTE},
};

TAF_MMA_SYS_SUBMODE_MAP_STRU          g_astTafMmaSysSubModeMapTbl[] =
{
    {NAS_OM_MMA_SYS_SUBMODE_NONE,                    TAF_SDC_SYS_SUBMODE_NONE},
    {NAS_OM_MMA_SYS_SUBMODE_GSM,                     TAF_SDC_SYS_SUBMODE_GSM},
    {NAS_OM_MMA_SYS_SUBMODE_GPRS,                    TAF_SDC_SYS_SUBMODE_GPRS},
    {NAS_OM_MMA_SYS_SUBMODE_EDGE,                    TAF_SDC_SYS_SUBMODE_EDGE},
    {NAS_OM_MMA_SYS_SUBMODE_WCDMA,                   TAF_SDC_SYS_SUBMODE_WCDMA},

    {NAS_OM_MMA_SYS_SUBMODE_HSDPA,                   TAF_SDC_SYS_SUBMODE_HSDPA},
    {NAS_OM_MMA_SYS_SUBMODE_HSUPA,                   TAF_SDC_SYS_SUBMODE_HSUPA},
    {NAS_OM_MMA_SYS_SUBMODE_HSDPA_HSUPA,             TAF_SDC_SYS_SUBMODE_HSDPA_HSUPA},
    {NAS_OM_MMA_SYS_SUBMODE_TD_SCDMA,                TAF_SDC_SYS_SUBMODE_TD_SCDMA},
    {NAS_OM_MMA_SYS_SUBMODE_HSPA_PLUS,               TAF_SDC_SYS_SUBMODE_HSPA_PLUS},

    {NAS_OM_MMA_SYS_SUBMODE_LTE,                     TAF_SDC_SYS_SUBMODE_LTE},
    {NAS_OM_MMA_SYS_SUBMODE_DC_HSPA_PLUS,            TAF_SDC_SYS_SUBMODE_DC_HSPA_PLUS},
    {NAS_OM_MMA_SYS_SUBMODE_DC_MIMO,                 TAF_SDC_SYS_SUBMODE_DC_MIMO},
    {NAS_OM_MMA_SYS_SUBMODE_CDMA_1X,                 TAF_SDC_SYS_SUBMODE_CDMA_1X},
    {NAS_OM_MMA_SYS_SUBMODE_EVDO_REL_0,              TAF_SDC_SYS_SUBMODE_EVDO_REL_0},

    {NAS_OM_MMA_SYS_SUBMODE_EVDO_REL_A,              TAF_SDC_SYS_SUBMODE_EVDO_REL_A},
    {NAS_OM_MMA_SYS_SUBMODE_HYBRID_EVDO_REL_0,       TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0},
    {NAS_OM_MMA_SYS_SUBMODE_HYBRID_EVDO_REL_A,       TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_A},
    {NAS_OM_MMA_SYS_SUBMODE_EHRPD,                   TAF_SDC_SYS_SUBMODE_EHRPD},

};

#endif
/* Added by y00322978 for CDMA Iteration 17, 2015-7-6, end */



/*****************************************************************************
  3 类型定义
*****************************************************************************/

/*****************************************************************************
  4 函数声明
*****************************************************************************/

/*****************************************************************************
  5 变量定义
*****************************************************************************/

/* Modified by l00301449 for Iteration 13, 2015-04-13, begin */
extern TAF_MMA_GLOBAL_VALUE_ST          gstMmaValue;
/* Modified by l00301449 for Iteration 13, 2015-04-13, end */

/*****************************************************************************
  6 函数实现
*****************************************************************************/

#if (FEATURE_IMS == FEATURE_ON)

VOS_UINT32 TAF_MMA_UpdataVoiceDomain(
    TAF_SDC_VOICE_DOMAIN_ENUM_UINT32    enVoiceDomain
)
{
    /* 如果没有发生变化则不需要更新 */
    if (enVoiceDomain == TAF_SDC_GetVoiceDomain())
    {
        return VOS_TRUE;
    }

    if (VOS_TRUE != TAF_MMA_UpdataVoiceDomainNv((VOS_UINT32)enVoiceDomain))
    {
        /* warning打印 */
        TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdataVoiceDomain: updata nv fail!");

        return VOS_FALSE;
    }

    /* 只有在NV更新成功后才能更新全局变量，以免出现状态不一致 */
    TAF_SDC_SetVoiceDomain(enVoiceDomain);

    return VOS_TRUE;
}
VOS_UINT32 TAF_MMA_UpdateLteImsSupportFlag(
    VOS_UINT8                           ucFlag
)
{
    VOS_UINT8                           ucLteImsSupportFlag;
    VOS_UINT8                           ucLteEmsSupportFlag;

    ucLteImsSupportFlag = TAF_SDC_GetLteImsSupportFlag();
    ucLteEmsSupportFlag = TAF_SDC_GetLteEmsSupportFlag();

    /* 如果没有发生变化则不需要更新 */
    if ((ucFlag != ucLteImsSupportFlag)
     || (ucFlag != ucLteEmsSupportFlag))
    {
        if (VOS_TRUE != TAF_MMA_UpdateLteImsSupportNv(ucFlag))
        {
            /* warning打印 */
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_UpdateLteImsSupportFlag: updata Lte Ims support nv fail!");

            return VOS_FALSE;
        }

        TAF_SDC_SetLteImsSupportFlag(ucFlag);
        TAF_SDC_SetLteEmsSupportFlag(ucFlag);
    }

    return VOS_TRUE;
}


VOS_VOID TAF_MMA_TransMsccImsStartResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_START_RESULT_ENUM_UINT32               enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
)
{
    switch (enResult)
    {
        case NAS_MSCC_PIF_IMS_START_RESULT_SUCC:
            *penErrorCode = TAF_ERR_NO_ERROR;
            break;

        case NAS_MSCC_PIF_IMS_START_RESULT_TIMEOUT:
            *penErrorCode = TAF_ERR_IMS_STACK_TIMEOUT;
            break;

        default:
            *penErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }

    return;
}


VOS_VOID TAF_MMA_TransMsccImsStopResultToTafErrorCode(
    NAS_MSCC_PIF_IMS_STOP_RESULT_ENUM_UINT32                enResult,
    TAF_ERROR_CODE_ENUM_UINT32                             *penErrorCode
)
{
    switch (enResult)
    {
        case NAS_MSCC_PIF_IMS_STOP_RESULT_SUCC:
            *penErrorCode = TAF_ERR_NO_ERROR;
            break;

        case NAS_MSCC_PIF_IMS_STOP_RESULT_TIMEOUT:
            *penErrorCode = TAF_ERR_IMS_STACK_TIMEOUT;
            break;

        default:
            *penErrorCode = TAF_ERR_UNSPECIFIED_ERROR;
            break;
    }

    return;
}
#endif

/*****************************************************************************
 函 数 名  : TAF_MMA_SetSysCfgRatSetFlg
 功能描述  : 设置SYSCFG中RAT标志
 输入参数  : TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType
             VOS_UINT32                         *pucRatExistedFlg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月15日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetSysCfgRatSetFlg(
    TAF_MMA_RAT_TYPE_ENUM_UINT8         enRatType,
    VOS_UINT32                         *pucRatExistedFlg
)
{
    if (TAF_MMA_RAT_GSM == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_G_SET;
    }

    if (TAF_MMA_RAT_WCDMA == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_W_SET;
    }

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    if (TAF_MMA_RAT_1X == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_1X_SET;
    }

    if (TAF_MMA_RAT_HRPD == enRatType)
    {
        *pucRatExistedFlg |= TAF_MMA_SYS_CFG_RAT_DO_SET;
    }
#endif

}



VOS_UINT32 TAF_MMA_GetSysCfgRatFlag(
    TAF_MMA_RAT_ORDER_STRU             *pstRatOrder,
    VOS_UINT32                         *pulRatExistedFlg
)
{
    VOS_UINT32                          ulPlatformSuppFlg;
    VOS_UINT32                          i;

    /* 判断用户设置的接入技术是否是平台支持的接入技术 */
    for (i = 0; i < pstRatOrder->ucRatOrderNum; i++)
    {
        ulPlatformSuppFlg = TAF_MMA_IsPlatformSupportSpecUserRat(pstRatOrder->aenRatOrder[i]);

        /* 如果不支持，返回失败，如果支持，继续检查下一个 */
        if (VOS_FALSE == ulPlatformSuppFlg)
        {
            return VOS_FALSE;
        }
        else
        {
            TAF_MMA_SetSysCfgRatSetFlg(pstRatOrder->aenRatOrder[i], pulRatExistedFlg);
        }
    }

    return VOS_TRUE;
}
/*****************************************************************************
 函 数 名  : TAF_MMA_IsUserSettedSysCfgParaValid
 功能描述  : 用户设置的syscfg参数有效性检查
 输入参数  : TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月8日
    作    者   : l00301449
    修改内容   : 新生成函数

  2.日    期   : 2015年4月10日
    作    者   : h00313353
    修改内容   : SysCfg重构
*****************************************************************************/
VOS_UINT32 TAF_MMA_IsUserSettedSysCfgParaValid(
    TAF_MMA_SYS_CFG_PARA_STRU          *pstSysCfgPara
)
{
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                           ucCardType;
    VOS_UINT8                           ucRatBalancingEnableFlg;
#endif
    VOS_UINT32                          ulRatExistedFlg;

#if (FEATURE_ON == FEATURE_LTE)
    ucRatBalancingEnableFlg = TAF_MMA_GetRatBalancingEnableFlg();

    /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
    ucCardType = USIMM_CARD_NOCARD;
    /* Modified by h00313353 for iteration 9, 2015-2-9, end */
#endif

    ulRatExistedFlg = TAF_MMA_SYS_CFG_RAT_NONE_SET;

    /* 接入技术用户设置没了 */
    if (0 == pstSysCfgPara->stRatOrder.ucRatOrderNum)
    {
        return VOS_FALSE;
    }

    if (VOS_FALSE == TAF_MMA_GetSysCfgRatFlag(&pstSysCfgPara->stRatOrder, &ulRatExistedFlg))
    {
        return VOS_FALSE;
    }

    /* 如果UE不支持GSM，当设置成G单模时，返回失败;当设置成多模时，给MSCC发送请求时校正去掉G模
        如果UE不支持GSM，当设置成G单模时，已在TAF_MMA_IsPlatformSupportSpecUserRat函数中返回VOS_FALSE
     */

#if (FEATURE_ON == FEATURE_LTE)
    /* 如果是SIM卡，当设置成L单模时，返回失败；当设置成多模时，给MSCC发送请求时校正去掉L模 */
    if (VOS_TRUE == MN_MMA_IsLOnlyMode(&(pstSysCfgPara->stRatOrder)))
    {
        /* Modified by h00313353 for iteration 9, 2015-2-9, begin */
        (VOS_VOID)NAS_USIMMAPI_GetCardType(VOS_NULL_PTR, &ucCardType) ;
        /* Modified by h00313353 for iteration 9, 2015-2-9, end */

        if ( (USIMM_CARD_SIM == ucCardType)
          && (VOS_TRUE       == ucRatBalancingEnableFlg) )
        {
            return VOS_FALSE;
        }
    }
#endif

    /* 1x/HRPD和G/U的冲突判断 */
    if (TAF_MMA_SYS_CFG_RAT_NONE_SET != (ulRatExistedFlg & TAF_MMA_SYS_CFG_RAT_C_SET))
    {
        if (TAF_MMA_SYS_CFG_RAT_NONE_SET != (ulRatExistedFlg & TAF_MMA_SYS_CFG_RAT_GU_SET))
        {
            return VOS_FALSE;
        }
    }

    /* 判断用户设置的频段是否有效 */
    if (VOS_TRUE != TAF_MMA_IsUserSettedGuBandValid(&(pstSysCfgPara->stGuBand)))
    {
        return VOS_FALSE;
    }

#if (FEATURE_ON == FEATURE_LTE)
    if (VOS_TRUE != TAF_MMA_IsUserSettedLBandValid(&(pstSysCfgPara->stLBand)))
    {
        return VOS_FALSE;
    }
#endif

    return VOS_TRUE;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_IsUserSettedGuBandValid
 功能描述  : 判断用户设置的GU频段是否有效
 输入参数  : TAF_USER_SET_PREF_BAND64           *pstGuBand
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月7日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsUserSettedGuBandValid(
    TAF_USER_SET_PREF_BAND64           *pstGuBand
)
{
    TAF_MMA_USER_BAND_SET_UN           uGuBand;
    TAF_MMA_UE_BAND_CAPA_ST           *pstBandCap = VOS_NULL_PTR;

    /* 将GU频段 pstSysCfgPara->stGuBand 64位转换为32位的 */
    MN_MMA_Convert64BitBandTo32Bit(pstGuBand, &uGuBand.ulPrefBand);

    MN_MMA_ConvertGUFrequencyBand(&uGuBand.ulPrefBand);

    pstBandCap = TAF_MMA_GetUeSupportBandAddr();
    /* 单模或多模时,用户设置的GU和L的频段必须要与当前UE支持的GU和L的频段有重叠频段
       否则禁止用户设置频段下去;当UE支持的GU或L的频段无效时,不检查用户设置的频段 */
    if ((0 == (uGuBand.ulPrefBand & pstBandCap->ulUeGSptBand))
     && (0 != pstBandCap->ulUeGSptBand))
    {
        return VOS_FALSE;
    }

    if ((0 == (uGuBand.ulPrefBand & pstBandCap->ulUeWSptBand))
     && (0 != pstBandCap->ulUeWSptBand))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}

#if(FEATURE_ON == FEATURE_LTE)
/*****************************************************************************
 函 数 名  : TAF_MMA_IsUserSettedLBandValid
 功能描述  : 判断用户设置的L频段是否有效
 输入参数  : TAF_USER_SET_PREF_BAND64           *pstLBand
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月7日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32  TAF_MMA_IsUserSettedLBandValid(
    TAF_USER_SET_PREF_BAND64           *pstLBand
)
{
    TAF_USER_SET_PREF_BAND64           *pstUeSupportLteBand = VOS_NULL_PTR;

    /* 获取用户设置的LBand */
    TAF_MMA_ConvertLteFrequencyBand(pstLBand);

    pstUeSupportLteBand = TAF_MMA_GetUeSupportLteBandAddr();

    if ((0 == (pstLBand->ulBandLow & pstUeSupportLteBand->ulBandLow))
     && (0 == (pstLBand->ulBandHigh & pstUeSupportLteBand->ulBandHigh))
     && ((0 != pstUeSupportLteBand->ulBandLow)
      || (0 != pstUeSupportLteBand->ulBandHigh)))
    {
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
#endif




/*****************************************************************************
 函 数 名  : TAF_MMA_SetAttachAllowFlg
 功能描述  : 根据attach类型设置attach是否允许标志
 输入参数  : VOS_UINT32                          ulAttachType
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年4月18日
    作    者   : l00301449
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_SetAttachAllowFlg(
    TAF_MMA_ATTACH_TYPE_ENUM_UINT8     ulAttachType
)
{
    if (TAF_MMA_ATTACH_TYPE_GPRS == ulAttachType)
    {
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);
    }

    if (TAF_MMA_ATTACH_TYPE_IMSI == ulAttachType)
    {
        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
    }

    if (TAF_MMA_ATTACH_TYPE_GPRS_IMSI == ulAttachType)
    {
        TAF_SDC_SetPsAttachAllowFlg(VOS_TRUE);

        TAF_SDC_SetCsAttachAllowFlg(VOS_TRUE);
    }

}


VOS_UINT32 TAF_MMA_IsRatOrderChange(
    TAF_MMA_RAT_ORDER_STRU             *pstCurrRat,
    TAF_MMA_RAT_ORDER_STRU             *pstLastRat
)
{
    if (pstCurrRat->ucRatOrderNum == pstLastRat->ucRatOrderNum)
    {
        if (0 == PS_MEM_CMP(&(pstCurrRat->aenRatOrder[0]),
                            &(pstLastRat->aenRatOrder[0]),
                            pstLastRat->ucRatOrderNum * sizeof(TAF_MMA_RAT_TYPE_ENUM_UINT8)))
        {
            return VOS_FALSE;
        }
    }

    return VOS_TRUE;
}


VOS_VOID TAF_MMA_MapCdmaNetworkExistanceSrvStaToSysMode(
    TAF_SDC_NETWORK_EXISTANCE_ENUM_UINT32                   enCdmaNetworkExist,
    TAF_SDC_SYS_MODE_ENUM_UINT8                            *penOutSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                         *penOutSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                   *ppTafSdcSysmodServiceRegStaUpdateFunc
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enGetSysmode;
    VOS_UINT32                          ulEntryCnt;
    VOS_UINT32                          i;

    TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU     astSysModeSearchTable[] =
    {
        /* 1.status ind , 2.old/current mode, 3.dest mode, 4.dest submode */
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_BUTT   , TAF_SDC_SYS_SUBMODE_NONE,              TAF_MMA_UpdateSerRegSta_HrpdToNone},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAT_MMA_UpdateSerRegSta_HybridTo1x},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_NOT_EXIST, TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_HRPD_NETWORK_EXIST,     TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},

        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              TAF_MMA_UpdateSerRegSta_1xToNone},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        TAF_MMA_UpdateSerRegSta_HybridToHrpd},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_NOT_EXIST,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               TAF_MMA_UpdateSerRegSta_SvlteToLte},

        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_1X_NETWORK_EXIST,       TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_EXIST,      TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_SUBMODE_LTE,               VOS_NULL_PTR},

        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_NONE,              VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_MODE_EVDO,    TAF_SDC_SYS_SUBMODE_EVDO_REL_0,        VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_MODE_HYBRID,  TAF_SDC_SYS_SUBMODE_HYBRID_EVDO_REL_0, VOS_NULL_PTR},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_LTE,     TAF_SDC_SYS_MODE_BUTT,    TAF_SDC_SYS_SUBMODE_BUTT,              TAF_MMA_UpdateSerRegSta_LteToNone},
        {TAF_SDC_LTE_NETWORK_NOT_EXIST,  TAF_SDC_SYS_MODE_SVLTE,   TAF_SDC_SYS_MODE_CDMA_1X, TAF_SDC_SYS_SUBMODE_CDMA_1X,           TAF_MMA_UpdateSerRegSta_SvlteTo1x},

    };

    /* initialize the output param and the const struct here */
    *penOutSysMode                          = TAF_SDC_SYS_MODE_BUTT;
    *penOutSubMode                          = TAF_SDC_SYS_SUBMODE_NONE;

    enGetSysmode = TAF_SDC_GetSysMode();
    ulEntryCnt   = sizeof(astSysModeSearchTable)/sizeof(TAF_SDC_MAP_SERVICE_STATUS_TO_SYSMODE_TLB_STRU);

    for (i = 0; i < ulEntryCnt; i++)
    {
        if ((enCdmaNetworkExist == astSysModeSearchTable[i].enCdmaNetworkExist)
         && (enGetSysmode == astSysModeSearchTable[i].enCurSysMode))
        {
            *penOutSysMode = astSysModeSearchTable[i].enNewSysMode;
            *penOutSubMode = astSysModeSearchTable[i].enNewSubMode;
            *ppTafSdcSysmodServiceRegStaUpdateFunc = astSysModeSearchTable[i].pfuncSysmodServiceRegStatusUpdate;
            return;
        }
    }
}


VOS_VOID TAF_MMA_UpdateSerRegSta_HrpdToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enPsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;
}
VOS_VOID TAT_MMA_UpdateSerRegSta_HybridTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta = VOS_TRUE;

    pstSrvInfo->enPsSrvSta    = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta    = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
}
VOS_VOID TAF_MMA_UpdateSerRegSta_1xToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;
}
VOS_VOID TAF_MMA_UpdateSerRegSta_HybridToHrpd(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_PS;

}
VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteToLte(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpCsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpCsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enCsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enCsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_PS;
}
VOS_VOID TAF_MMA_UpdateSerRegSta_LteToNone(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta  = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta  = VOS_TRUE;
    pstSrvInfo->bitOpSrvSta    = VOS_TRUE;
    pstSrvInfo->bitOpSrvDomain = VOS_TRUE;

    pstSrvInfo->enPsSrvSta     = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta     = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
    pstSrvInfo->enSrvSta       = TAF_SDC_REPORT_SRVSTA_NO_SERVICE;
    pstSrvInfo->enSrvDomain    = TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN;

}
VOS_VOID TAF_MMA_UpdateSerRegSta_SvlteTo1x(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo
)
{
    /* 不能先设置全局变量，后续上报的话，通过Get方式来获取老的状态 */
    pstSrvInfo->bitOpPsSrvSta = VOS_TRUE;
    pstSrvInfo->bitOpPsRegSta = VOS_TRUE;

    pstSrvInfo->enPsSrvSta    = TAF_SDC_SERVICE_STATUS_NO_SERVICE;
    pstSrvInfo->enPsRegSta    = TAF_SDC_REG_NOT_REGISTERED_NOT_SEARCH;
}

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID TAF_MMA_UpdateSrvRegSta_Main(
    TAF_SDC_SRV_REG_INFO_STRU          *pstSrvInfo,
    TAF_PH_ACCESS_TECH_ENUM_UINT8       enAct
)
{
    TAF_SDC_REPORT_SRVSTA_ENUM_UINT8    oldSrvSta;

    oldSrvSta = TAF_SDC_GetServiceStatus();

    if (VOS_TRUE == pstSrvInfo->bitOpCsSrvSta)
    {
        TAF_SDC_SetCsServiceStatus(pstSrvInfo->enCsSrvSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpPsSrvSta)
    {
        TAF_SDC_SetPsServiceStatus(pstSrvInfo->enPsSrvSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvDomain)
    {
        TAF_SDC_SetServiceDomain(pstSrvInfo->enSrvDomain);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpSrvSta)
    {
        TAF_SDC_SetServiceStatus(pstSrvInfo->enSrvSta);

        if (TAF_SDC_GetServiceStatus() != oldSrvSta)
        {
            /* 处理^SRVST命令上报 */
            TAF_MMA_ReportSrvStatus();
        }
    }

    if (VOS_TRUE == pstSrvInfo->bitOpCsRegSta)
    {
        TAF_MMA_Report1xCregStatus(pstSrvInfo->enCsRegSta);
    }

    if (VOS_TRUE == pstSrvInfo->bitOpPsRegSta)
    {
        TAF_MMA_ReportPsRegStatus(pstSrvInfo->enPsRegSta, enAct);
    }
}
VOS_VOID TAF_MMA_ChgSysModeAndSrvRegSta(
    TAF_PH_ACCESS_TECH_ENUM_UINT8                           enAct,
    TAF_SDC_SYS_MODE_ENUM_UINT8                             enSysMode,
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8                          enSubMode,
    pTafSdcSysmodServiceRegStaUpdateFunc                    pFuncTafSdcSysmodServiceRegStaUpdate
)
{
    TAF_SDC_SRV_REG_INFO_STRU                               stSrvRegInfo;

    PS_MEM_SET(&stSrvRegInfo, 0x00, sizeof(stSrvRegInfo));

    /* ^MODE命令上报处理 */
    Mma_ModeChgReport(enSysMode, enSubMode);

    /* 更新MMA维护的Mode/SubMode */
    TAF_SDC_SetSysMode(enSysMode);

    TAF_SDC_SetSysSubMode(enSubMode);

    /* 执行更新服务状态与注册状态函数 */
    if (VOS_NULL_PTR != pFuncTafSdcSysmodServiceRegStaUpdate)
    {
        pFuncTafSdcSysmodServiceRegStaUpdate(&stSrvRegInfo);

        /* 判断服务状态、注册状态是否变化，变化的话，就上报 */
        TAF_MMA_UpdateSrvRegSta_Main(&stSrvRegInfo, enAct);
    }
}

/*****************************************************************************
 函 数 名  : TAF_MMA_MapHsmSessionStatus
 功能描述  : cdma session map table convert
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月6日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapHsmSessionStatus(
    HSM_MMA_SESSION_STATUS_ENUM_UINT8  enSessionStatus
)
{
    TAF_MMA_SESSION_STATUS_MAP_STRU    *pstSessionStatusMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSesionStatusMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSessionStatusMapPtr = TAF_MMA_SESSION_STATUS_MAP_TBL_PTR();
    ulSesionStatusMapTblSize = TAF_MMA_SESSION_STATUS_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSesionStatusMapTblSize; ulCnt++)
    {
        if (pstSessionStatusMapPtr[ulCnt].enHsmSessionStatus == enSessionStatus)
        {
            return pstSessionStatusMapPtr[ulCnt].enMmaSessionStatus;
        }
    }

    return HSM_MMA_SESSION_STATUS_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_MapCdmaPhoneMode
 功能描述  : map phone mode for om ind
 输入参数  : enPhoneMode 手机模式
 输出参数  : 无
 返 回 值  : NAS_OM_MMA_PHONE_MODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapCdmaPhoneMode(
    TAF_SDC_PHONE_MODE_ENUM_UINT8       enPhoneMode
)
{
    TAF_MMA_CDMA_PHONE_MODE_MAP_STRU   *pstCdmaPhoneModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulCdmaPhoneModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstCdmaPhoneModeMapPtr = TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_PTR();
    ulCdmaPhoneModeMapTblSize = TAF_MMA_CDMA_PHONE_MODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulCdmaPhoneModeMapTblSize; ulCnt++)
    {
        if (pstCdmaPhoneModeMapPtr[ulCnt].enTafCdmaPhoneMode == enPhoneMode)
        {
            return pstCdmaPhoneModeMapPtr[ulCnt].enNasOmCdmaPhoneMode;
        }
    }

    return NAS_OM_MMA_PHONE_MODE_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_MapSysMode
 功能描述  : map sys mode for om ind
 输入参数  : enSysMode 驻留系统网络模式
 输出参数  : 无
 返 回 值  : NAS_OM_MMA_SYS_MODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode
)
{
    TAF_MMA_SYS_MODE_MAP_STRU          *pstSysModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSysModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSysModeMapPtr = TAF_MMA_SYS_MODE_MAP_TBL_PTR();
    ulSysModeMapTblSize = TAF_MMA_SYS_MODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSysModeMapTblSize; ulCnt++)
    {
        if (pstSysModeMapPtr[ulCnt].enTafCdmaSysMode == enSysMode)
        {
            return pstSysModeMapPtr[ulCnt].enNasOmCdmaSysMode;
        }
    }

    return NAS_OM_MMA_SYS_MODE_BUTT;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_MapSubSysMode
 功能描述  : map sub sys mode for om ind
 输入参数  : TAF_SDC_SYS_SUBMODE_ENUM_UINT8 enSysSubMode  驻留网络的子系统模式
 输出参数  : 无
 返 回 值  : NAS_OM_MMA_SYS_SUBMODE_ENUM_UINT8
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月10日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 TAF_MMA_MapSysSubMode(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSysSubMode
)
{
    TAF_MMA_SYS_SUBMODE_MAP_STRU       *pstSysSubModeMapPtr = VOS_NULL_PTR;
    VOS_UINT32                          ulSysSubModeMapTblSize;
    VOS_UINT32                          ulCnt;

    pstSysSubModeMapPtr = TAF_MMA_SYS_SUBMODE_MAP_TBL_PTR();
    ulSysSubModeMapTblSize = TAF_MMA_SYS_SUBMODE_MAP_TBL_SIZE();

    for (ulCnt = 0; ulCnt < ulSysSubModeMapTblSize; ulCnt++)
    {
        if (pstSysSubModeMapPtr[ulCnt].enTafSysSubMode == enSysSubMode)
        {
            return pstSysSubModeMapPtr[ulCnt].enNasOmSysSubMode;
        }
    }

    return NAS_OM_MMA_SYS_SUBMODE_BUTT;
}
/* Added by z00316370 for UTS 2015-5-18 end */

/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertMeidToUl
 功能描述  : 把meid 56bit转换为两个uint32数
 输入参数  : VOS_UINT8                          *pucMeid,
             VOS_UINT32                          ulMeid,
             VOS_UINT32                          ulMeidCnt
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月25日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_MMA_ConvertMeidToUl(
    VOS_UINT8                          *pucMeid,
    VOS_UINT32                         *pMeid,
    VOS_UINT32                         *pMeidCnt
)
{
    VOS_UINT8                           aucMeid[NAS_OM_MMA_MEID_OCTET_NUM] = {0};
    VOS_UINT32                          ulMeid;
    VOS_UINT32                          ulMeidCnt;

    PS_MEM_CPY(aucMeid, pucMeid, NAS_OM_MMA_MEID_OCTET_NUM);
    ulMeid    = ((aucMeid[0] << 16) & 0x00ff0000)
               |((aucMeid[1] << 8) & 0x0000ff00)
               |( aucMeid[2] & 0x000000ff);
    ulMeidCnt = ((aucMeid[3] << 24) & 0xff000000)
               |((aucMeid[4] << 16) & 0x00ff0000)
               |((aucMeid[5] << 8) & 0x0000ff00)
               |( aucMeid[6] & 0x000000ff);
    *pMeid = ulMeid;
    *pMeidCnt = ulMeidCnt;

}
/*****************************************************************************
 函 数 名  : TAF_MMA_ConvertUatiToUl
 功能描述  : 把128bit的uati转换为4个32bit的整数 4个VOS_UINT8合并成一个VOS_UINT32数
 输入参数  : VOS_UINT8                          *pstUati,
             VOS_UINT32                          ulLength
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月4日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 TAF_MMA_ConvertUatiToUl(
    VOS_UINT8                          *pstUati
)
{
    VOS_UINT8                           aucUati[4] = {0};
    VOS_UINT32                          ulUati;

    ulUati = 0;

    PS_MEM_CPY(aucUati, pstUati, 4);
    ulUati = ((aucUati[3] << 24) & 0xff000000)
            |((aucUati[2] << 16) & 0x00ff0000)
            |((aucUati[1] << 8) & 0x0000ff00)
            |( aucUati[0] & 0x000000ff);

    return ulUati;

}
/*****************************************************************************
 函 数 名  : TAF_MMA_MapModemId
 功能描述  :  modemid映射
 输入参数  : MODEM_ID_ENUM_UINT16                enModemId
 输出参数  : MODEM_ID_ASN_ENUM_UINT16
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年9月8日
    作    者   : y00322978
    修改内容   : 新生成函数

*****************************************************************************/
MODEM_ID_ASN_ENUM_UINT16 TAF_MMA_MapModemId(
    MODEM_ID_ENUM_UINT16                enModemId
)
{
    MODEM_ID_ASN_ENUM_UINT16            enModemIdAsn;

    switch(enModemId)
    {
        case MODEM_ID_0:
            enModemIdAsn = MODEM_ID_0_ASN;
            break;
        case MODEM_ID_1:
            enModemIdAsn = MODEM_ID_1_ASN;
            break;
        case MODEM_ID_2:
            enModemIdAsn = MODEM_ID_2_ASN;
            break;
        default:
            enModemIdAsn = MODEM_ID_BUTT_ASN;
    }
    return enModemIdAsn;
}


VOS_UINT32 TAF_MMA_QryCdmaStatusInfo(
    NAS_OM_MMA_CDMA_STATUS_COMMON_INFO_STRU             *pstCdmaCommInfo,
    NAS_OM_MMA_1X_SYS_INFO_STRU                         *pst1xSysInfo,
    NAS_OM_MMA_HRPD_SYS_INFO_STRU                       *pstHrpdSysInfo
)
{
    TAF_SDC_SYS_INFO_STRU               *pstSysInfo;
    TAF_SDC_SYS_MODE_ENUM_UINT8          enSysMode;
    VOS_UINT8                            aucUati[NAS_OM_MMA_UATI_OCTET_LENGTH] = {0};

    TAF_SDC_PHONE_MODE_ENUM_UINT8       enCurPhoneMode;

    enCurPhoneMode = TAF_SDC_GetCurPhoneMode();
    pstSysInfo = TAF_SDC_GetSysInfo();
    enSysMode = TAF_SDC_GetSysMode();
    PS_MEM_CPY(aucUati, pstSysInfo->stHrpdSysInfo.aucCurUATI, NAS_OM_MMA_UATI_OCTET_LENGTH);

    /* clear coverity warning */
    if (TAF_SDC_PHONE_MODE_BUTT == enCurPhoneMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_QryCdmaStatusInfo: Curr Phone Mode is BUTT!");
    }

    /* clear coverity warning */
    if(TAF_SDC_SYS_MODE_BUTT == enSysMode)
    {
        TAF_WARNING_LOG(WUEPS_PID_MMA,
                        "TAF_MMA_QryCdmaStatusInfo: Curr System Mode is BUTT!");
    }
    //cdma comm info
    pstCdmaCommInfo->enPhoneMode = TAF_MMA_MapCdmaPhoneMode(enCurPhoneMode);
    pstCdmaCommInfo->enSysMode = TAF_MMA_MapSysMode(enSysMode);
    pstCdmaCommInfo->enModemId = TAF_MMA_MapModemId(pstSysInfo->enModemId);
    pstCdmaCommInfo->ulEsn = pstSysInfo->ulEsn;
    TAF_MMA_ConvertMeidToUl(pstSysInfo->aucMeId, &pstCdmaCommInfo->ulMeid, &pstCdmaCommInfo->ulMeidCnt);


    //cdma 1x info
    if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode)
     || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
    {
        pst1xSysInfo->en1xCallState = TAF_SDC_GetXCallState();
        pst1xSysInfo->lNid = pstSysInfo->st1xSysInfo.lNid;
        pst1xSysInfo->lSid = pstSysInfo->st1xSysInfo.lSid;
        pst1xSysInfo->ulMcc = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(pstSysInfo->st1xSysInfo.stServiceInfo.ulMcc);
        pst1xSysInfo->usBandClass = pstSysInfo->st1xSysInfo.usBandClass;
        pst1xSysInfo->usMnc = (VOS_UINT32)TAF_STD_TransformBcdMncToDeciDigit(pstSysInfo->st1xSysInfo.stServiceInfo.usMnc);
        pst1xSysInfo->usFreq = pstSysInfo->st1xSysInfo.usFreq;
        pst1xSysInfo->usBaseId = pstSysInfo->st1xSysInfo.stBaseStationInfo.usBaseId;
    }

    //cdma hrpd info
    if ((TAF_SDC_SYS_MODE_EVDO == enSysMode)
     || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
    {
        pstHrpdSysInfo->usBandClass = pstSysInfo->stHrpdSysInfo.usBandClass;
        pstHrpdSysInfo->ucColorCode = pstSysInfo->stHrpdSysInfo.ucColorCode;
        pstHrpdSysInfo->enSessionStatus = pstSysInfo->stHrpdSysInfo.ucSessionStatus;
        pstHrpdSysInfo->ucSubNetMask = pstSysInfo->stHrpdSysInfo.ucSubNetMask;
        pstHrpdSysInfo->ulMcc = (VOS_UINT32)TAF_STD_TransformBcdMccToDeciDigit(pstSysInfo->stHrpdSysInfo.ulMcc);
        pstHrpdSysInfo->ulSessionSeed = pstSysInfo->stHrpdSysInfo.ulSessionSeed;
        pstHrpdSysInfo->usChannel = pstSysInfo->stHrpdSysInfo.usFreq;
        pstHrpdSysInfo->ulSector24 = pstSysInfo->stHrpdSysInfo.ulSector24;
        pstHrpdSysInfo->enSysSubMode = TAF_MMA_MapSysSubMode(pstSysInfo->enSysSubMode);
        pstHrpdSysInfo->ulCurUATI1 = TAF_MMA_ConvertUatiToUl(aucUati);
        pstHrpdSysInfo->ulCurUATI2 = TAF_MMA_ConvertUatiToUl(&aucUati[4]);
        pstHrpdSysInfo->ulCurUATI3 = TAF_MMA_ConvertUatiToUl(&aucUati[8]);
        pstHrpdSysInfo->ulCurUATI4 = TAF_MMA_ConvertUatiToUl(&aucUati[12]);
    }

    return VOS_TRUE;
}
/*****************************************************************************
Function Name   :  TAF_MMA_IsPesnValid
Description     :  judge if esn is valid
Input parameters:  NV_PESN_STRU       *pstPesn,
Outout parameters:  none
Return Value    :   vos_ture        valid
                    vos_false       invalid

Modify History  :
1)  Date           : 2015-08-03
    Author         : y00322978
    Modify content : Create
*****************************************************************************/
 VOS_UINT8 TAF_MMA_IsPesnValid(
    NV_PESN_STRU                       *pstPesn
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < PESN_NV_DATA_LEN; ucIndex++)
    {
        if (0x00 != pstPesn->aucPEsn[ucIndex])
        {
           return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}

/*****************************************************************************
Function Name   :  TAF_MMA_IsMeidValid
Description     :  judge if meid is valid
Input parameters:  NV_MEID_STRU       *pstMeid
Outout parameters:  none
Return Value    :   vos_ture        valid
                    vos_false       invalid

Modify History  :
1)  Date           : 2015-08-03
    Author         : y00322978
    Modify content : Create
*****************************************************************************/
 VOS_UINT8 TAF_MMA_IsMeidValid(
    NV_MEID_STRU                       *pstMeid
)
{
    VOS_UINT8                           ucIndex;

    for (ucIndex = 0; ucIndex < MEID_NV_DATA_LEN_NEW; ucIndex++)
    {
        if (0x00 != pstMeid->aucMeID[ucIndex])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
/*****************************************************************************
Function Name   :  TAF_MMA_IsUIMIDValid
Description     :  judge whether UIMID is valid
                   if in the bytes num of ucUIMIDByteNum,all the bits of UIMID is 1,then UIMID is invalid
                   other cases,then UIMID is valid
Input parameters:   pstUIMID--pointer of UIMID
Outout parameters:  None
Return Value    :   VOS_TRUE:UIMID is valid;   VOS_FALSE:UIMID is invalid

Modify History  :
1)  Date           : 2015-08-27
    Author         : Y00322978
    Modify content : Create
*****************************************************************************/
VOS_UINT8 TAF_MMA_IsUIMIDValid(
    VOS_UINT8                          *pucEFRUIMID
)
{
    VOS_UINT8                           ucUIMIDByteNum;
    VOS_UINT8                           i;

    /* the first byte of EFRUIMID indicates the bytes num of UIMID (here,the num is 4) in EFRUIMID */
    ucUIMIDByteNum = pucEFRUIMID[0];

    /*
      according to the protocal C.S0023-D_v2.0_R-UIM ,the EF of EFRuimid store the 32-bit UIMID constructed in the following way:

      Bytes              Description                M/O                Length

        1               number of Bytes              M                  1byte

        2               lowest-order byte            M                  1byte

        3                   ...                      M                  1byte

        4                   ...                      M                  1byte

        5                   ...                      M                  1byte

        6                   ...                      O                  1byte

        7                   ...                      O                  1byte

        8               highest-order byte           O                  1byte

        the EF consists of 8 bytes,in which the first byte indicates the bytes num of UIMID (here,the num is 4) in EF,
        so,when check the validity of UIMID,just need to check from the second byte to the fifth byte
        if all the bits of the four bytes which indicates the UIMID value from the second byte to the fifth byte are 1,then UIMID is invalid
        vice versa
    */
    for (i = 1; i <= ucUIMIDByteNum; i++)
    {
        if (0xFF != pucEFRUIMID[i])
        {
            return VOS_TRUE;
        }
    }

    return VOS_FALSE;
}
#endif


/* Added by zwx247453 for CHR optimize, 2015-3-13 Begin */
#if (FEATURE_ON == FEATURE_PTM)
VOS_VOID TAF_MMA_RatFrequentlySwitchRecord(VOS_VOID)
{
    NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU           *pstRatFreqSwitchEvent = VOS_NULL_PTR;
    VOS_UINT32                                              ulNvSwitchNum;
    VOS_UINT32                                              ulEventLength;
    VOS_UINT32                                              ulActuallyReadLength;
    VOS_UINT8                                               ucActiveRptFlag;
    VOS_UINT8                                               ucRatSwitchRptFlag;
    VOS_UINT16                                              usLevel;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel             = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH);

    ucActiveRptFlag     = TAF_SDC_GetErrlogActiveRptFlag();
    ucRatSwitchRptFlag  = TAF_SDC_GetErrlogRatSwitchRptFlag();
    ulNvSwitchNum       = TAF_SDC_GetErrlogRatSwitchStatisticNum();
    ulEventLength       = sizeof(NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU);

    /* 只有当主动上报的NV打开，才上报 */
    if ((VOS_FALSE == ucActiveRptFlag)
     || (VOS_FALSE == ucRatSwitchRptFlag))
    {
        return;
    }

    pstRatFreqSwitchEvent = (NAS_ERR_LOG_RAT_FREQUENTLY_SWITCH_EVENT_STRU *)PS_MEM_ALLOC(
                                WUEPS_PID_MMA, ulEventLength);

    if (VOS_NULL_PTR == pstRatFreqSwitchEvent)
    {
        NAS_ERROR_LOG(WUEPS_PID_MMA, "TAF_MMA_RatFrequentlySwitchRecord(): PS_MEM_ALLOC error.");

        return;
    }

    PS_MEM_SET(pstRatFreqSwitchEvent, 0x00, ulEventLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&(pstRatFreqSwitchEvent->stHeader),
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulEventLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    pstRatFreqSwitchEvent->ulStatisticTime = TAF_SDC_GetErrlogRatSwitchStatisticTime();
    pstRatFreqSwitchEvent->ulSwitchNum     = ulNvSwitchNum;

    /* 填充结构体中astPositionInfo数组元素 */
    /* 从队列中rear位置开始到队列中front位置拷贝到stGutlFreqSwitchEvent中 */
    ulActuallyReadLength = TAF_SDC_GetRecordFromRatSwitchRingBuf((VOS_CHAR *)pstRatFreqSwitchEvent->astRatSwitchInfo,
                          ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU));

    if (ulActuallyReadLength != (ulNvSwitchNum * sizeof(NAS_ERR_LOG_RAT_SWITCH_RECORD_STRU)))
    {
        PS_MEM_FREE(WUEPS_PID_MMA, pstRatFreqSwitchEvent);

        return;
    }

    TAF_SDC_CleanRatSwitchRingBuf();

    /* 将RAT频繁切换信息发送给ACPU OM模块 */
    TAF_SndAcpuOmFaultErrLogInd(pstRatFreqSwitchEvent, ulEventLength, NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH);

    /* RAT频繁切换，只需要上报，不需要记录到共享缓存中。*/

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_RAT_FREQUENTLY_SWITCH,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)pstRatFreqSwitchEvent,
                           ulEventLength);

    PS_MEM_FREE(WUEPS_PID_MMA, pstRatFreqSwitchEvent);

    return;
}


VOS_VOID TAF_MMA_ReportErrlogOosBegin(
    NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32   enOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enLostDomain
)
{
    NAS_ERR_LOG_OOS_BEGIN_STRU          stOosBeginEvent;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    VOS_UINT32                          ulIsLogRecord;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_BEGIN);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_OOS_BEGIN_STRU);

    PS_MEM_SET(&stOosBeginEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stOosBeginEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_OOS_BEGIN,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stOosBeginEvent.stPositionInfo);

    /* 获取HPLMN */
    MN_PH_QryApHplmn(&stOosBeginEvent.stHomePlmnId.ulMcc, &stOosBeginEvent.stHomePlmnId.ulMnc);

    stOosBeginEvent.enOosCause      = enOosCause;
    stOosBeginEvent.enLostDomain    = enLostDomain;
    stOosBeginEvent.usGUTCellUlFreq = TAF_SDC_GetAppCellUlFreq();
    stOosBeginEvent.usGUTCellDlFreq = TAF_SDC_GetAppCellDlFreq();
    stOosBeginEvent.ucRssiValue     = TAF_SDC_GetAppRssiValue();

    stOosBeginEvent.ulLteArfcn      = TAF_SDC_GetAppLteArfcn();

    /* 主动上报给AP */
    TAF_SndAcpuOmFaultErrLogInd(&stOosBeginEvent,
                                ulLength,
                                NAS_ERR_LOG_ALM_OOS_BEGIN);

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_BEGIN,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)&stOosBeginEvent,
                           sizeof(stOosBeginEvent));

    return;
}



VOS_VOID TAF_MMA_ReportErrlogOosEnd(
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enResumeDomain
)
{
    NAS_ERR_LOG_OOS_END_STRU            stOosEndEvent;
    VOS_UINT32                          ulLength;
    VOS_UINT16                          usLevel;
    VOS_UINT32                          ulIsLogRecord;

    /* 查询对应Alarm Id是否需要记录异常信息 */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_OOS_END);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* 模块异常不需要记录或异常原因值不需要记录时，不保存异常信息 */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_OOS_END_STRU);

    PS_MEM_SET(&stOosEndEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stOosEndEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_MMA),
                                      NAS_ERR_LOG_ALM_OOS_END,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    /* 获取当前位置信息 */
    NAS_MNTN_OutputPositionInfo(&stOosEndEvent.stPositionInfo);

    stOosEndEvent.enResumeDomain = enResumeDomain;

    if (NAS_ERR_LOG_OOS_DOMAIN_CS == enResumeDomain)
    {
        stOosEndEvent.ucReportFlag   = TAF_SDC_GetErrLogCsOosReportToAppFlag();

        TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_FALSE);
    }
    else
    {
        stOosEndEvent.ucReportFlag   = TAF_SDC_GetErrLogPsOosReportToAppFlag();

        TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_FALSE);
    }

    stOosEndEvent.usGUTCellDlFreq   = TAF_SDC_GetAppCellDlFreq();
    stOosEndEvent.usGUTCellUlFreq   = TAF_SDC_GetAppCellUlFreq();
    stOosEndEvent.ucRssiValue       = TAF_SDC_GetAppRssiValue();

    stOosEndEvent.ulLteArfcn        = TAF_SDC_GetAppLteArfcn();

    /* 主动上报给AP */
    TAF_SndAcpuOmFaultErrLogInd(&stOosEndEvent,
                                ulLength,
                                NAS_ERR_LOG_ALM_OOS_END);

    /* 可维可测勾包 */
    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_OOS_END,
                           WUEPS_PID_MMA,
                           (VOS_UINT8 *)&stOosEndEvent,
                           sizeof(stOosEndEvent));

    return;
}
VOS_VOID TAF_MMA_ProcErrlogDomainOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldRegState,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enNewRegState,
    VOS_UINT32                          ulOosCause,
    NAS_ERR_LOG_OOS_DOMAIN_ENUM_UINT32  enOosDomain
)
{
    VOS_UINT8                           ucReportPowerOnBeginFlag;
    VOS_UINT8                           ucReportPowerOffBeginFlag;


    ucReportPowerOnBeginFlag  = TAF_SDC_GetErrLogReportPowerOnBeginFlag();
    ucReportPowerOffBeginFlag = TAF_SDC_GetErrLogReportPowerOffBeginFlag();

    /* 某个域离开注册状态(即1或者5)时，给AP上报OOS BGEIN消息，
       某个域回到注册状态(即1或者5)时，给AP上报OOS END消息。
     */

    /* 离开注册状态 */
    if (((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == enOldRegState)
      || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == enOldRegState))
     && ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enNewRegState)
      && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enNewRegState)))
    {
        /* 如果之前已经上报过开关机Begin，则不再上报任何原因的Begin */
        if ((VOS_TRUE != ucReportPowerOnBeginFlag)
         && (VOS_TRUE != ucReportPowerOffBeginFlag))
        {
            TAF_MMA_ReportErrlogOosBegin((NAS_ERR_LOG_OOS_CAUSE_ENUM_UINT32)ulOosCause,
                                         enOosDomain);
        }

        return;
    }

    /* 回到注册状态 */
    if (((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enOldRegState)
      && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enOldRegState))
     && ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK == enNewRegState)
      || (NAS_MSCC_PIF_REG_REGISTERED_ROAM         == enNewRegState)))
    {
        TAF_MMA_ReportErrlogOosEnd(enOosDomain);

        TAF_SDC_SetErrLogReportPowerOnBeginFlag(VOS_FALSE);
        TAF_SDC_SetErrLogReportPowerOffBeginFlag(VOS_FALSE);

        return;
    }

    return;
}
VOS_VOID TAF_MMA_ProcErrlogOosReport(
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldCsRegState,
    TAF_SDC_REG_STATUS_ENUM_UINT8       enOldPsRegState,
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == pstServiceStatus->enCnDomainId)
    {
        TAF_MMA_ProcErrlogDomainOosReport(enOldCsRegState,
                                          pstServiceStatus->enRegState,
                                          pstServiceStatus->ulOosCause,
                                          NAS_ERR_LOG_OOS_DOMAIN_CS);
        return;
    }

    if (NAS_MSCC_PIF_SRVDOMAIN_PS == pstServiceStatus->enCnDomainId)
    {

        TAF_MMA_ProcErrlogDomainOosReport(enOldPsRegState,
                                          pstServiceStatus->enRegState,
                                          pstServiceStatus->ulOosCause,
                                          NAS_ERR_LOG_OOS_DOMAIN_PS);
        return;

    }

    return;
}


#endif
/* Added by zwx247453 for CHR optimize, 2015-3-13 End */

VOS_VOID TAF_MMA_RecordRegStatusReportFlag(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId,
    NAS_MSCC_PIF_REG_STATE_ENUM_UINT8   enRegState
)
{
    /* 如果上报的是无服务，则记录已上报无服务 */
    if ((NAS_MSCC_PIF_REG_REGISTERED_HOME_NETWORK != enRegState)
     && (NAS_MSCC_PIF_REG_REGISTERED_ROAM         != enRegState))
    {
        if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
        {
            TAF_SDC_SetErrLogCsOosReportToAppFlag(VOS_TRUE);
        }
        else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
        {
            TAF_SDC_SetErrLogPsOosReportToAppFlag(VOS_TRUE);
        }
        else
        {
            return;
        }
    }

    return;
}
VOS_UINT32 TAF_MMA_IsUsimServiceAvailable(VOS_VOID)
{
    VOS_UINT32                           ulRslt;

    switch (TAF_SDC_GetSimStatus())
    {
        case TAF_SDC_USIM_STATUS_ROMSIM:
        case TAF_SDC_USIM_STATUS_VALID:
        case TAF_SDC_USIM_STATUS_CS_UNVALID:
        case TAF_SDC_USIM_STATUS_PS_UNVALID:
            ulRslt = VOS_TRUE;
            break;

        case TAF_SDC_USIM_STATUS_SIM_PIN:
        case TAF_SDC_USIM_STATUS_SIM_PUK:
        case TAF_SDC_USIM_STATUS_NET_LCOK:
        case TAF_SDC_USIM_STATUS_IMSI_LCOK:
        case TAF_SDC_USIM_STATUS_UNVALID:
        case TAF_SDC_USIM_STATUS_NO_PRESENT:
        case TAF_SDC_USIM_STATUS_BUTT:
        case TAF_SDC_USIM_STATUS_CS_PS_UNVALID:
        case TAF_SDC_USIM_STATUS_READY_TIMEROUT:
            ulRslt = VOS_FALSE;
            break;

        default:
            ulRslt = VOS_FALSE;
            TAF_WARNING_LOG(WUEPS_PID_MMA, "TAF_MMA_IsUsimServiceAvailable(): something wrong!");
            break;
    }

    return ulRslt;
}



VOS_VOID TAF_MMA_UpdateGeoInfo(
    TAF_SDC_PLMN_ID_STRU               *pstPlmnId
)
{
    TAF_MMA_GET_GEO_CTX_STRU            *pstGetGeoCtx = VOS_NULL_PTR;

    pstGetGeoCtx        = TAF_MMA_GetGeoCtxAddr();

    /* get geo NV项关闭时不需要更新 */
    if (VOS_FALSE == pstGetGeoCtx->stGetGeoNvCfg.ucCfgGetGeoFlag)
    {
        return;
    }

    pstGetGeoCtx->stGeoPlmnId.ulMcc = pstPlmnId->ulMcc;
    pstGetGeoCtx->stGeoPlmnId.ulMnc = pstPlmnId->ulMnc;
    pstGetGeoCtx->ulGetGeoTickTime  = VOS_GetTick() / PRE_SECOND_TO_TICK;

    return;
}
VOS_VOID TAF_MMA_ConvertSysInfoExSysMode(
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSrcSysMode,
    MN_PH_SYS_MODE_EX_ENUM_U8          *penDestSysMode
)
{
    switch(enSrcSysMode)
    {

        case TAF_SDC_SYS_MODE_LTE:
           *penDestSysMode = MN_PH_SYS_MODE_EX_LTE_RAT;
            return;

        case TAF_SDC_SYS_MODE_CDMA_1X:
           *penDestSysMode = MN_PH_SYS_MODE_EX_CDMA_RAT;
            return;

        case TAF_SDC_SYS_MODE_EVDO:
           *penDestSysMode = MN_PH_SYS_MODE_EX_EVDO_RAT;
            return;

        case TAF_SDC_SYS_MODE_HYBRID:
           *penDestSysMode = MN_PH_SYS_MODE_EX_HYBRID_RAT;
            return;

        case TAF_SDC_SYS_MODE_SVLTE:
           *penDestSysMode = MN_PH_SYS_MODE_EX_SVLTE_RAT;
            return;

        case TAF_SDC_SYS_MODE_BUTT:
           *penDestSysMode = MN_PH_SYS_MODE_EX_NONE_RAT;
            return;

        default:
           *penDestSysMode = MN_PH_SYS_MODE_EX_BUTT_RAT;
           return;
    }
}
VOS_VOID TAF_MMA_ConvertSysInfoExSysSubMode(
    TAF_SDC_SYS_SUBMODE_ENUM_UINT8      enSrcSysSubMode,
    MN_PH_SUB_SYS_MODE_EX_ENUM_U8      *penDestSysSubMode
)
{
    MN_PH_ConvertSysSubModeToAtFormat_FDD(enSrcSysSubMode, penDestSysSubMode);

    return;
}






VOS_UINT8 TAF_MMA_IsSameAsAppServiceStatus(
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   enServiceStatus,
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ucOldCsAppServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ucOldPsAppServiceStatus;
    VOS_UINT8                           ucIsSameAsAppSrvStatus;

    ucOldCsAppServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ucOldPsAppServiceStatus = TAF_SDC_GetAppPsServiceStatus();
    ucIsSameAsAppSrvStatus  = VOS_TRUE;


    switch (enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            if (ucOldCsAppServiceStatus != enServiceStatus)
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            if (ucOldPsAppServiceStatus != enServiceStatus)
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;

        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
            if ( (ucOldCsAppServiceStatus != enServiceStatus)
               ||(ucOldPsAppServiceStatus != enServiceStatus))
            {
                ucIsSameAsAppSrvStatus = VOS_FALSE;
            }
            break;
        default:
            break;
    }

    return ucIsSameAsAppSrvStatus;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateAppSrvStatusInfo
 功能描述  : 更新AppNetworkInfo中保存的服务状态信息
 输入参数  : enCnDomainId:需要更新的域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : l00305157
    修改内容   : 新增函数 Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppSrvStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*打印可维可测*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stServPlmnInfo.stServicePlmnId), &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId), sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stServPlmnInfo.enServiceSysMode       = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stServPlmnInfo.enServiceSysSubMode    = pstCurNwInfo->stSysInfo.enSysSubMode;
    pstAppNwInfo->stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* 信号质量更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stRssiValue), &(pstCurNwInfo->stRssiValue), sizeof(TAF_SDC_RSSI_VALUE_STRU));

    /* 服务状态更新到AppNetworkInfo */
    switch(enCnDomainId)
    {
        case NAS_MSCC_PIF_SRVDOMAIN_CS:
            TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_PS:
            TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);
            break;
        case NAS_MSCC_PIF_SRVDOMAIN_NO_CHANGE:
        case NAS_MSCC_PIF_SRVDOMAIN_CS_PS:
        case NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING:
            /* 这两种服务域只有MMC才会上报，因此PS/CS都需要更新 */
            TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
            TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);
            break;
        default:
            break;
    }

    /*更新总的服务状态*/
    TAF_MMA_UpdateAppReportSrvStatus();

    /*更新总的服务域*/
    TAF_MMA_UpdateAppReportSrvDomain(enCnDomainId);

    return ;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateAppRegStatusInfo
 功能描述  : 更新AppNetworkInfo中保存的注册状态信息
 输入参数  : enCnDomainId:需要更新的域
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : l00305157
    修改内容   : 新增函数 Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppRegStatusInfo(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*打印可维可测*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stServPlmnInfo.stServicePlmnId), &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId), sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stServPlmnInfo.enServiceSysMode       = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stServPlmnInfo.enServiceSysSubMode    = pstCurNwInfo->stSysInfo.enSysSubMode;
    pstAppNwInfo->stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* 信号质量更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stRssiValue), &(pstCurNwInfo->stRssiValue), sizeof(TAF_SDC_RSSI_VALUE_STRU));

    /* 注册状态更新到AppNetworkInfo */
    if (NAS_MSCC_PIF_SRVDOMAIN_CS == enCnDomainId)
    {
        TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
    }
    else if (NAS_MSCC_PIF_SRVDOMAIN_PS == enCnDomainId)
    {
        TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);
    }
    else if(NAS_MSCC_PIF_SRVDOMAIN_CS_PS == enCnDomainId)
    {
        TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
        TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);
    }
    else
    {
        TAF_ERROR_LOG (WUEPS_PID_MMA,
            "TAF_MMA_UpdateAppRegStatusInfo():WARNING:enCurRegStatus is TAF_SDC_REG_STATUS_BUTT");
    }

    return ;
}


VOS_VOID TAF_MMA_UpdateAppNetworkInfo(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;

    /*打印可维可测*/
    TAF_MMA_LogNetworkInfoAndAppNetworkInfo();

    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stServPlmnInfo.stServicePlmnId), &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId), sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stServPlmnInfo.enServiceSysMode       = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stServPlmnInfo.enServiceSysSubMode    = pstCurNwInfo->stSysInfo.enSysSubMode;
    pstAppNwInfo->stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    /* 信号质量更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stRssiValue), &(pstCurNwInfo->stRssiValue), sizeof(TAF_SDC_RSSI_VALUE_STRU));

    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, begin */
    /* 服务状态更新到AppNetworkInfo */
    TAF_SDC_SetAppCsServiceStatus(pstCurNwInfo->stCsDomainInfo.enCsServiceStatus);
    TAF_SDC_SetAppPsServiceStatus(pstCurNwInfo->stPsDomainInfo.enPsServiceStatus);

    TAF_SDC_SetAppCsRegStatus(pstCurNwInfo->stCsDomainInfo.enCsRegStatus);
    TAF_SDC_SetAppPsRegStatus(pstCurNwInfo->stPsDomainInfo.enPsRegStatus);

    TAF_SDC_SetAppServiceStatus(pstCurNwInfo->enReportSrvsta);
    TAF_SDC_SetAppServiceDomain(pstCurNwInfo->enServiceDomain);
    /* Add by l00305157 for Service_State_Optimize_PhaseII, 2015-02-11, end */

    return ;

}


VOS_VOID TAF_MMA_UpdateAppServPlmnInfo(VOS_VOID)
{
    TAF_SDC_NETWORK_INFO_STRU          *pstCurNwInfo = VOS_NULL_PTR;
    TAF_SDC_APPNETWORK_INFO            *pstAppNwInfo = VOS_NULL_PTR;


    pstCurNwInfo  = TAF_SDC_GetCurrNetworkInfo();
    pstAppNwInfo  = TAF_SDC_GetAppNetworkInfo();

    /* 驻留信息更新到AppNetworkInfo */
    PS_MEM_CPY(&(pstAppNwInfo->stServPlmnInfo.stServicePlmnId), &(pstCurNwInfo->stSysInfo.st3gppSysInfo.stPlmnId), sizeof(TAF_SDC_PLMN_ID_STRU));
    pstAppNwInfo->stServPlmnInfo.enServiceSysMode       = pstCurNwInfo->stSysInfo.enSysMode;
    pstAppNwInfo->stServPlmnInfo.ucServiceUtranMode     = NAS_UTRANCTRL_GetCurrUtranMode();
    pstAppNwInfo->stServPlmnInfo.enServiceSysSubMode    = pstCurNwInfo->stSysInfo.enSysSubMode;
    pstAppNwInfo->stServPlmnInfo.usServiceLac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.usLac;
    pstAppNwInfo->stServPlmnInfo.ucServiceRac           = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRac;
    pstAppNwInfo->stServPlmnInfo.ulServiceCellId        = pstCurNwInfo->stSysInfo.st3gppSysInfo.ulCellId;
    pstAppNwInfo->stServPlmnInfo.ucServiceRoamFlg       = pstCurNwInfo->stSysInfo.st3gppSysInfo.ucRoamFlag;

    return ;

}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateAppReportSrvStatus
 功能描述  : 更新AppNetworkInfo中保存的总的服务状态
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : l00305157
    修改内容   : 新增函数 Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppReportSrvStatus(VOS_VOID)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppPsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppCsServiceStatus;


    ulAppCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ulAppPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

        /* 更新总的服务状态 */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus))
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus)
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE_REGION == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_REGIONAL_LIMITED_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_LIMITED_SERVICE == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else if ((TAF_SDC_SERVICE_STATUS_NO_IMSI == ulAppCsServiceStatus)
          || (TAF_SDC_SERVICE_STATUS_NO_IMSI == ulAppPsServiceStatus) )
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_LIMITED_SERVICE);
    }
    else
    {
        TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_NO_SERVICE);

        if (VOS_TRUE == gstMmaValue.pg_StatusContext->ulTimMaxFlg )
        {
            TAF_SDC_SetAppServiceStatus(TAF_SDC_REPORT_SRVSTA_DEEP_SLEEP);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : TAF_MMA_UpdateAppReportSrvDomain
 功能描述  : 更新AppNetworkInfo中保存的总的服务状态和服务域信息
 输入参数  : enCnDomainId:上报的当期的服务域信息
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月10日
    作    者   : l00305157
    修改内容   : 新增函数 Service_State_Optimize_PhaseII

*****************************************************************************/
VOS_VOID TAF_MMA_UpdateAppReportSrvDomain(
    NAS_MSCC_PIF_SRVDOMAIN_ENUM_UINT32  enCnDomainId
)
{
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppPsServiceStatus;
    TAF_SDC_SERVICE_STATUS_ENUM_UINT8   ulAppCsServiceStatus;


    ulAppCsServiceStatus = TAF_SDC_GetAppCsServiceStatus();
    ulAppPsServiceStatus = TAF_SDC_GetAppPsServiceStatus();

     /* 更新总的服务域 */
    if ((TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
     && (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus))
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppCsServiceStatus)
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
    }
    else if (TAF_SDC_SERVICE_STATUS_NORMAL_SERVICE == ulAppPsServiceStatus)
    {
        TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
    }
    else
    {
    }

    if (TAF_SDC_REPORT_SRVSTA_NORMAL_SERVICE != TAF_SDC_GetAppServiceStatus() )
    {
        if(NAS_MSCC_PIF_SRVDOMAIN_NOT_REG_PLMN_SEARCHING == enCnDomainId)
        {
            TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_SEARCHING);
        }
        else
        {
            switch(gstMmaValue.stSetMsClass.NewMsClassType)
            {
                case TAF_PH_MS_CLASS_A:
                case TAF_PH_MS_CLASS_B:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS_PS);
                    break;
                case TAF_PH_MS_CLASS_CC:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_CS);
                    break;
                case TAF_PH_MS_CLASS_CG:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_PS);
                    break;
                case TAF_PH_MS_CLASS_NULL:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
                default:
                    TAF_SDC_SetAppServiceDomain(TAF_SDC_SERVICE_DOMAIN_NO_DOMAIN);
                    break;
            }
        }
    }

    return;
}
VOS_VOID TAF_MMA_ProcDelayReport(VOS_VOID)
{
    if ( TAF_MMA_TIMER_STATUS_RUNING != TAF_MMA_GetTimerStatus(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS))
    {
        /*需要延时上报，开启延时上报定时器*/
        TAF_MMA_StartTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS, (TAF_MMA_GetDelayReportServiceStatusCfgTimerLen()));
    }

    return;
}
VOS_VOID TAF_MMA_ProcServiceStatusImmediatelyReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    /*上报服务状态，停止延时定时器，更新APPINFO*/
    TAF_MMA_ProcMsccServiceStatusReport(TAF_SDC_GetServiceStatus(), TAF_SDC_GetAppServiceStatus());

    if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstServiceStatus->enServiceStatus)
    {
        TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);
    }

    TAF_MMA_UpdateAppSrvStatusInfo(pstServiceStatus->enCnDomainId);

    return;
}
VOS_VOID TAF_MMA_ProcServiceStatusNotReport(
    MSCC_MMA_SERVICE_STATUS_IND_STRU   *pstServiceStatus
)
{
    /*与当前APP保存的服务状态相同则不需要上报*/
    if (VOS_TRUE == TAF_MMA_IsSameAsAppServiceStatus((TAF_SDC_SERVICE_STATUS_ENUM_UINT8)pstServiceStatus->enServiceStatus, pstServiceStatus->enCnDomainId))
    {
        /* 当前域从normal service->normal service也更新一下驻留信息和信号强度 */
        if (NAS_MSCC_PIF_SERVICE_STATUS_NORMAL_SERVICE == pstServiceStatus->enServiceStatus)
        {
            TAF_MMA_StopTimer(TI_TAF_MMA_DELAY_REPORT_SERVICE_STATUS);

            TAF_MMA_UpdateAppSrvStatusInfo(pstServiceStatus->enCnDomainId);
        }
    }

    return;
}


VOS_VOID TAF_MMA_FillActForAtCmdCregInClMode(
    TAF_MMA_QRY_REG_STATUS_TYPE_ENUM_UINT32                 enQryRegStaType,
    TAF_PH_ACCESS_TECH_ENUM_UINT8                          *pucAct
)
{
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();

    *pucAct = TAF_PH_ACCESS_TECH_BUTT;

    /* CL模式下CREG查询是1X下的CS注册状态 */
    if (TAF_MMA_QRY_REG_STATUS_TYPE_CS == enQryRegStaType)
    {
        if ((TAF_SDC_SYS_MODE_CDMA_1X == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_HYBRID  == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_CDMA_1X;
        }
    }
    /* CL模式下CGREG查询的是LTE或HRPD的PS注册状态 */
    else if (TAF_MMA_QRY_REG_STATUS_TYPE_PS == enQryRegStaType)
    {
        if ((TAF_SDC_SYS_MODE_LTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
        }

        if ((TAF_SDC_SYS_MODE_EVDO   == enSysMode)
         || (TAF_SDC_SYS_MODE_HYBRID == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_EVDO;
        }
    }
    /* EPS状态查询 */
    else
    {
        if ((TAF_SDC_SYS_MODE_LTE   == enSysMode)
         || (TAF_SDC_SYS_MODE_SVLTE == enSysMode))
        {
            *pucAct = TAF_PH_ACCESS_TECH_E_UTRAN;
        }
    }

    return;
}


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



