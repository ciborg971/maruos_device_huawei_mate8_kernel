

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXCallMntn.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_X_CALL_MNTN_C

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/
/*lint -save -e958*/

VOS_VOID TAF_XCALL_MNTN_LogCallInfo(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_CALL_INFO_STRU  *pstLogCallInfoMsg;

    pstLogCallInfoMsg = (TAF_XCALL_MNTN_LOG_CALL_INFO_STRU *)PS_MEM_ALLOC(WUEPS_PID_TAF,
                                    sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU));

    if (VOS_NULL_PTR == pstLogCallInfoMsg)
    {
        return;
    }

    PS_MEM_SET(pstLogCallInfoMsg, 0x00, sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU));

    /* 消息封装 */
    pstLogCallInfoMsg->ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstLogCallInfoMsg->ulSenderPid         = WUEPS_PID_TAF;
    pstLogCallInfoMsg->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstLogCallInfoMsg->ulReceiverPid       = WUEPS_PID_TAF;
    pstLogCallInfoMsg->ulLength            = sizeof(TAF_XCALL_MNTN_LOG_CALL_INFO_STRU) - VOS_MSG_HEAD_LENGTH;

    pstLogCallInfoMsg->enMsgId             = ID_TAF_XCALL_MNTN_LOG_CALL_INFO_IND;

    PS_MEM_CPY(pstLogCallInfoMsg->astCallEntity,
               TAF_XCALL_GetCtxAddr()->astCallEntity,
               TAF_XCALL_CALL_ENTITY_MAX_NUM * sizeof(TAF_XCALL_CALL_ENTITY_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(pstLogCallInfoMsg);

    PS_MEM_FREE(WUEPS_PID_TAF, pstLogCallInfoMsg);

    return;

}


VOS_VOID TAF_XCALL_MNTN_LogSupsCmdMgmt(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT_STRU                   stLogSupsCmdMgmt;

    PS_MEM_SET(&stLogSupsCmdMgmt, 0x00, sizeof(stLogSupsCmdMgmt));

    /* 消息封装 */
    stLogSupsCmdMgmt.ulSenderCpuId       = VOS_LOCAL_CPUID;
    stLogSupsCmdMgmt.ulSenderPid         = WUEPS_PID_TAF;
    stLogSupsCmdMgmt.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    stLogSupsCmdMgmt.ulReceiverPid       = WUEPS_PID_TAF;
    stLogSupsCmdMgmt.ulLength            = sizeof(stLogSupsCmdMgmt) - VOS_MSG_HEAD_LENGTH;

    stLogSupsCmdMgmt.enMsgId             = ID_TAF_XCALL_MNTN_LOG_SUPS_CMD_MGMT;

    PS_MEM_CPY(&(stLogSupsCmdMgmt.stSupsCmdMgmt),
               TAF_XCALL_GetSupsCmdMgmt(),
               sizeof(TAF_XCALL_SUPS_CMD_MGMT_STRU));

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogSupsCmdMgmt);

    return;

}

/* Added by h00313353 for Iteration 17, 2015-8-7, begin */
/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogEmcCallRedialPeriod
 功能描述  : 勾ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月10日
    作    者   : h00313353
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogEmcCallRedialPeriod(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU              stLogEmcCallRedialPeriod;

    PS_MEM_SET(&stLogEmcCallRedialPeriod, 0x00, sizeof(stLogEmcCallRedialPeriod));

    /* 消息封装 */
    stLogEmcCallRedialPeriod.ulSenderCpuId                  = VOS_LOCAL_CPUID;
    stLogEmcCallRedialPeriod.ulSenderPid                    = WUEPS_PID_TAF;
    stLogEmcCallRedialPeriod.ulReceiverCpuId                = VOS_LOCAL_CPUID;
    stLogEmcCallRedialPeriod.ulReceiverPid                  = WUEPS_PID_TAF;
    stLogEmcCallRedialPeriod.ulLength                       = sizeof(TAF_XCALL_MNTN_LOG_CALL_REDIAL_PERIOD_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogEmcCallRedialPeriod.enMsgId                        = ID_TAF_XCALL_MNTN_LOG_EMC_CALL_REDIAL_PERIOD;
    stLogEmcCallRedialPeriod.ulEmcRedialPeriod              = TAF_XCALL_GetConfigInfo()->ulEmcRedialPeriod;

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogEmcCallRedialPeriod);

    return;
}

/* Added by h00313353 for Iteration 17, 2015-8-7, end */

/*****************************************************************************
 函 数 名  : TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval
 功能描述  : 勾TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU消息
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年8月18日
    作    者   : l00324781
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID TAF_XCALL_MNTN_LogStartAndStopContDtmfInterval(VOS_VOID)
{
    TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU                   stLogMntn;

    PS_MEM_SET(&stLogMntn, 0x00, sizeof(stLogMntn));

    /* 消息封装 */
    stLogMntn.ulSenderCpuId     = VOS_LOCAL_CPUID;
    stLogMntn.ulSenderPid       = WUEPS_PID_TAF;
    stLogMntn.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    stLogMntn.ulReceiverPid     = WUEPS_PID_TAF;
    stLogMntn.ulLength          = sizeof(TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL_STRU) - VOS_MSG_HEAD_LENGTH;
    stLogMntn.enMsgId           = ID_TAF_XCALL_MNTN_LOG_START_AND_STOP_CONT_DTMF_INTERVAL;
    stLogMntn.ulStartAndStopContDtmfInterval = TAF_XCALL_GetStartAndStopContDtmfIntervalLen();

    /* 勾出可维可测信息 */
    DIAG_TraceReport(&stLogMntn);

    return;
}

/*lint -restore*/
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




