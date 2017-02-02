/******************************************************************************

                  版权所有 (C), 2001-2014, 华为技术有限公司

 ******************************************************************************
  文 件 名   : TafXCallProcNvim.c
  版 本 号   : 初稿
  作    者   : h00313353
  生成日期   : 2015年07月07日
  最近修改   :
  功能描述   : 处理Nvim的文件
  函数列表   :

  修改历史   :
  1.日    期   : 2015年07月07日
    作    者   : h00313353
    修改内容   : 创建文件

******************************************************************************/


/*****************************************************************************
   1 头文件包含
*****************************************************************************/

#include "TafXCallCtx.h"
#include "NVIM_Interface.h"
#include "TafXCallProcNvim.h"
#include "TafLog.h"
#include "TafXCallMntn.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#define    THIS_FILE_ID                 PS_FILE_ID_TAF_X_CALL_PROC_NVIM_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
   2 变量定义
*****************************************************************************/


/*****************************************************************************
   3 函数实现
*****************************************************************************/
/*****************************************************************************
 函 数 名  : TAF_XCALL_ReadEmcCallRedialPeriod
 功能描述  : 读取紧急呼重拨定时器时长
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月6日
    作    者   : h00313353
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID  TAF_XCALL_ReadEmcCallRedialPeriod(VOS_VOID)
{
    TAF_XCALL_CONFIG_STRU                                  *pstXcallConfig = VOS_NULL_PTR;
    TAF_XCALL_NVIM_1X_EMC_CALL_REDIAL_PERIOD_STRU           stEmcCallRedialPeriod;

    pstXcallConfig      = TAF_XCALL_GetConfigInfo();

    PS_MEM_SET(&stEmcCallRedialPeriod, 0x0, sizeof(stEmcCallRedialPeriod));

    if (NV_OK != NV_Read(en_Nv_Item_EMC_REDIAL_PERIOD,
                         &stEmcCallRedialPeriod, sizeof(stEmcCallRedialPeriod)))
    {
        pstXcallConfig->ulEmcRedialPeriod   = TAF_XCALL_EMC_CALL_REDIAL_PERIOD_DEFAULT * 1000;

        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_ReadEmcCallRedialPeriod():WARNING: en_Nv_Item_EMC_REDIAL_PERIOD Error");;
        return;
    }

    pstXcallConfig->ulEmcRedialPeriod = stEmcCallRedialPeriod.ulEmcCallRedialPeriod * 1000;

    TAF_XCALL_MNTN_LogEmcCallRedialPeriod();

    return;
}


VOS_VOID TAF_XCALL_Read1xVoiceSoCfgNvim()
{
    TAF_XCALL_SO_TYPE_ENUM_UINT16      *penSoType = VOS_NULL_PTR;
    TAF_NVIM_1X_VOICE_SO_CFG            st1xVoiceSoCfg;

    penSoType = &(TAF_XCALL_GetConfigInfo()->enSoInitType);

    PS_MEM_SET(&st1xVoiceSoCfg, 0x0, sizeof(st1xVoiceSoCfg));

    if (NV_OK != NV_Read(en_Nv_Item_1X_VOICE_SO_CFG,
                         &st1xVoiceSoCfg, sizeof(st1xVoiceSoCfg)))
    {
        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_Read1xVoiceSoCfgNvim:Read Nvim Failed");

       *penSoType = TAF_XCALL_SO_3_EVRC;
        return;
    }

    if ((TAF_XCALL_SO_3_EVRC    != st1xVoiceSoCfg.usSo)
     && (TAF_XCALL_SO_68_EVRC_B != st1xVoiceSoCfg.usSo))
    {
        *penSoType = TAF_XCALL_SO_3_EVRC;
        
    }
    else
    {
        *penSoType = st1xVoiceSoCfg.usSo;
    }
   
}

/*****************************************************************************
 函 数 名  : TAF_XCALL_ReadStartAndStopContDtmfIntervalLen
 功能描述  : 读取 发送Stop Cont DTMF Req和Start Cont DTMF Req时间间隔定时器时长，单位为毫秒
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : 新增函数
*****************************************************************************/
VOS_VOID TAF_XCALL_ReadStartAndStopContDtmfIntervalLen(VOS_VOID)
{
    TAF_XCALL_CONFIG_STRU                                  *pstXcallConfig = VOS_NULL_PTR;
    TAF_XCALL_NVIM_START_AND_STOP_CONT_DTMF_INTERVAL_STRU   stStartAndStopContDtmfInterVal;

    pstXcallConfig      = TAF_XCALL_GetConfigInfo();

    PS_MEM_SET(&stStartAndStopContDtmfInterVal, 0x0, sizeof(stStartAndStopContDtmfInterVal));

    if (NV_OK != NV_Read(en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL,
                         &stStartAndStopContDtmfInterVal, sizeof(stStartAndStopContDtmfInterVal)))
    {
        /* 读取失败，使用最小时长，为360ms */
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN;

        TAF_WARNING_LOG(WUEPS_PID_TAF, "TAF_XCALL_ReadStartAndStopContDtmfIntervalLen():WARNING: en_NV_Item_START_AND_STOP_CONT_DTMF_INTERVAL Error");
        return;
    }

    /* NV配置检查 */
    if (TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN > stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen)
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MIN;
    }
    else if (TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX < stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen)
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = TI_TAF_XCALL_START_AND_STOP_CONT_DTMF_INTERVAL_MAX;
    }
    else
    {
        pstXcallConfig->ulStartAndStopContDtmfIntervalLen = stStartAndStopContDtmfInterVal.ulStartAndStopContDtmfIntervalLen;
    }

    /* 可维可测，勾包 */
    TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval();

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




