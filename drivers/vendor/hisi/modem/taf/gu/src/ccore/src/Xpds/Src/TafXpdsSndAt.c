

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "TafXpdsSndAt.h"
#include "AtXpdsInterface.h"
#include "TafXpdsMntn.h"
#include "cprocstime.h"


#ifdef  __cplusplus
#if  __cplusplus
extern "C"{
#endif
#endif

#define THIS_FILE_ID                    PS_FILE_ID_TAF_XPDS_SND_AT_C

#if ((FEATURE_ON == FEATURE_UE_MODE_CDMA) && (FEATURE_ON == FEATURE_AGPS))

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_VOID TAF_XPDS_FillMpcStartPosReq
(
    TAF_XPDS_MPC_START_POS_REQ_STRU                   *pstStartPosReq
)
{
    pstStartPosReq->ucVersion       = TAF_XPDS_CUR_VERSION;
    pstStartPosReq->enMsgType       = ID_TAF_XPDS_MS_TO_MPC_START_POS_REQ;

    /* 能力下发 to be checked in IT2*/
    pstStartPosReq->enMsPosCap      = TAF_XPDS_MS_POS_CAPABILITY_BOTH;

    /* 那个APP发起 TO DO  */
    if (TAF_XPDS_NI == TAF_XPDS_GetCgpsInitialType())
    {
        pstStartPosReq->enAppTypeIndicator  = TAF_XPDS_APP_TYPE_INDICATOR_NETWORK_INITIATED;
    }
    else
    {
        pstStartPosReq->enAppTypeIndicator  = TAF_XPDS_APP_TYPE_INDICATOR_MS_RESIDENT;
    }

    /* 1.0 if ni process ,the value is in mt pos req
       2.0 if java it is a default value
       3.0 other app should get from ap */
    if (TAF_XPDS_APP_TYPE_INDICATOR_NETWORK_INITIATED == pstStartPosReq->enAppTypeIndicator)
    {
        if (1 == TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucPosQoSInc)
        {
            pstStartPosReq->ucPQoS = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucPosQoS;
        }
        else
        {
             pstStartPosReq->ucPQoS = 0;
        }

        pstStartPosReq->ucCorrelationId = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId;

        if (1 == TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.usNumOfFixs)
        {
            pstStartPosReq->ulDuration = 0;
        }
        else
        {
            pstStartPosReq->ulDuration = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.usTimeBetweenFixs *
                                         TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.usNumOfFixs;
        }
    }
    else
    {
        /* to do */
        pstStartPosReq->ucPQoS          = (VOS_UINT8)TAF_XPDS_GetAgpsCfg()->ulQosPerformance;

        pstStartPosReq->ucCorrelationId = TAF_XPDS_GetCorrelationId();

        /* ulDuration: WAP: 0 SINGLE-SHOT FIX: 0 SUCC_TRACKING: 1- XXX to be checked*/
        if (1 == TAF_XPDS_GetAgpsCfg()->usFixNum)
        {
            pstStartPosReq->ulDuration      = 0;
        }
        else
        {
            pstStartPosReq->ulDuration      = (VOS_UINT32)(TAF_XPDS_GetAgpsCfg()->ulFixRateTime * \
                                                TAF_XPDS_GetAgpsCfg()->usFixNum);
        }

    }

    /* MS_ID_REC TO DO */
    TAF_XPDS_EncodeMsIdRec(&pstStartPosReq->stMsIdRec);

    pstStartPosReq->usSID         = (VOS_UINT16)TAF_SDC_Get1xSid();
    pstStartPosReq->usNID         = (VOS_UINT16)TAF_SDC_Get1xNid();
    pstStartPosReq->ulBaseID      = TAF_SDC_Get1xSysInfo()->stBaseStationInfo.usBaseId;
    pstStartPosReq->ulBaseLat     = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLatitude;
    pstStartPosReq->ulBaseLong    = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLongitude;

    /* get from page channel to be checked*/
    pstStartPosReq->usRefPn       = TAF_XPDS_GetPublicDataAddr()->stPilotInfo.usRefPn;

    pstStartPosReq->usBandClass   = TAF_SDC_Get1xSysInfo()->usBandClass;
    pstStartPosReq->ulCdmaFreq    = TAF_SDC_Get1xSysInfo()->usFreq;

    /* time stamp need to do */
    TAF_XPDS_SetTimeStamp(&pstStartPosReq->stTimeStamp);

#if 0
    if (TAF_XPDS_APP_TYPE_INDICATOR_BREW == pstStartPosReq->enAppTypeIndicator)
    {
        /* ulBrewAppID to do */

        /* stAPPIDREC to do*/
    }
#endif
}
VOS_VOID TAF_XPDS_FillMpcPosReportReq
(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
)
{
    pstPosReportReq->ucVersion       = TAF_XPDS_CUR_VERSION;
    pstPosReportReq->enMsgType       = ID_TAF_XPDS_MS_TO_MPC_POS_REPORT;

    pstPosReportReq->usCorrelationId = TAF_XPDS_GetMpcCtxAddr()->stXsmsPosReq.ucCorrelationId;

    /* need to do */
    pstPosReportReq->usFixNum        = TAF_XPDS_GetCtrlInfoAddr()->usCurFixNum;

    /* MS_ID_REC TO DO */
    TAF_XPDS_EncodeMsIdRec(&pstPosReportReq->stMsIdRec);

    pstPosReportReq->usSID         = (VOS_UINT16)TAF_SDC_Get1xSid();
    pstPosReportReq->usNID         = (VOS_UINT16)TAF_SDC_Get1xNid();
    pstPosReportReq->ulBaseID      = TAF_SDC_Get1xSysInfo()->stBaseStationInfo.usBaseId;
    pstPosReportReq->ulBaseLat     = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLatitude;
    pstPosReportReq->ulBaseLong    = (VOS_UINT16)TAF_SDC_Get1xSysInfo()->stBaseStationInfo.lBaseLongitude;

    /* get from page channel to be checked*/
    pstPosReportReq->usRefPn       = TAF_XPDS_GetPublicDataAddr()->stPilotInfo.usRefPn;

    pstPosReportReq->usBandClass   = TAF_SDC_Get1xSysInfo()->usBandClass;
    pstPosReportReq->ulCdmaFreq    = TAF_SDC_Get1xSysInfo()->usFreq;

    /* time stamp need to do */
    TAF_XPDS_SetTimeStamp(&pstPosReportReq->stCellIdTimeStamp);

    TAF_XPDS_SetTimeStamp(&pstPosReportReq->stPosTimeStamp);

    /* 有无位置信息 */
    TAF_XPDS_SetPosReportLocInfo(pstPosReportReq);

    /* 位置信息需要重新考虑 */

    return;
}


VOS_UINT32 TAF_XPDS_CalcTimeInWeek(VOS_UINT32 ulRefTime)
{
    VOS_UINT64                          ulCurrTime64;
    VOS_UINT64                          ulStdTime64;
    VOS_UINT64                          ulStartTime64;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_HRPD);
    }
    else
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X);
    }

    /* 先转化为毫秒 */
    ulCurrTime64 = ulCurrTime64 * 80;

    /* RegTime单位为1.28s */
    ulRefTime    = ulRefTime * 1280;

    /* 基础时间点是以320s为间隔 */
    ulStdTime64  = ulCurrTime64 - ulCurrTime64 % (320 * 1000);

    if ((ulStdTime64 + ulRefTime) > ulCurrTime64)
    {
        ulStartTime64 = (ulStdTime64 - (320 * 1000)) + ulRefTime;
    }
    else
    {
        ulStartTime64 = ulStdTime64 + ulRefTime;
    }

    /* 相对当前周的毫秒 */
    return (VOS_UINT32)(ulStartTime64 % (7*24*3600*1000));
}



VOS_UINT64 TAF_XPDS_CalcAbsTime(VOS_UINT32 ulRefTime)
{
    VOS_UINT64                          ulCurrTime64;
    VOS_UINT64                          ulStdTime64;
    VOS_UINT64                          ulStartTime64;
    TAF_SDC_SYS_MODE_ENUM_UINT8         enSysMode;

    enSysMode = TAF_SDC_GetSysMode();

    if (TAF_SDC_SYS_MODE_EVDO == enSysMode)
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_HRPD);
    }
    else
    {
        ulCurrTime64 = CDMA_Timing_GetSystemTime80ms(CDMA_TIMING_RTT_1X);
    }

    /* 先转化为毫秒 */
    ulCurrTime64 = ulCurrTime64 * 80;

    /* RegTime单位为1s */
    ulRefTime    = ulRefTime * 1000;

    /* 转换为基准时间点,以16384s为间隔 */
    ulStdTime64 = ulCurrTime64 - ulCurrTime64 % (16384 * 1000);

    if ((ulStdTime64 + ulRefTime) > ulCurrTime64)
    {
        ulStartTime64 = (ulStdTime64 - (16384 * 1000)) + ulRefTime;
    }
    else
    {
        ulStartTime64 = ulStdTime64 + ulRefTime;
    }

    return ulStartTime64;
}
VOS_VOID TAF_XPDS_SndAtMsg(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId,
    VOS_UINT32                          ulLen,
    VOS_UINT8                          *pData
)
{
    AT_XPDS_MSG_STRU                   *pstMsgStr;

    /* 判断输入参数 */
    if ((VOS_NULL_PTR == pData) || (0 == ulLen))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsg: para is invalid!");
        return;
    }

    /* 消息空间申请 */
    pstMsgStr = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS,
                                                 sizeof(AT_APPCTRL_STRU) + sizeof(ulMsgId) + ulLen);
    if (VOS_NULL_PTR == pstMsgStr)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsg: alloc msg fail!");
        return;
    }

    /* 填消息包 */
    pstMsgStr->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderPid           = UEPS_PID_XPDS;
    pstMsgStr->ulReceiverPid         = WUEPS_PID_AT;
    pstMsgStr->ulMsgId               = ulMsgId;
    pstMsgStr->stAppCtrl.usClientId  = MN_GetRealClientId(pAppCtrl->usClientId, UEPS_PID_XPDS);
    pstMsgStr->stAppCtrl.ucOpId      = pAppCtrl->ucOpId;
    pstMsgStr->stAppCtrl.aucReserved[0] = 0;
    PS_MEM_CPY(pstMsgStr->aucContent, pData, ulLen);

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStr))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsg():WARNING:SEND MSG FIAL");
    }

    return;
}


VOS_VOID TAF_XPDS_SndAtMsgNoData(
    AT_APPCTRL_STRU                    *pAppCtrl,
    VOS_UINT32                          ulMsgId
)
{
    AT_XPDS_MSG_STRU                   *pstMsgStr;


    /* 消息空间申请 */
    pstMsgStr = (AT_XPDS_MSG_STRU *)PS_ALLOC_MSG(UEPS_PID_XPDS,
                                                 sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstMsgStr)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsgNoData: alloc msg fail!");
        return;
    }

    /* 填消息包 */
    pstMsgStr->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderCpuId         = VOS_LOCAL_CPUID;
    pstMsgStr->ulSenderPid           = UEPS_PID_XPDS;
    pstMsgStr->ulReceiverPid         = WUEPS_PID_AT;
    pstMsgStr->ulLength              = (sizeof(AT_XPDS_MSG_STRU) - VOS_MSG_HEAD_LENGTH) - 4; /* 需要减去消息中的aucContent字段长度 */
    pstMsgStr->ulMsgId               = ulMsgId;
    pstMsgStr->stAppCtrl.usClientId  = MN_GetRealClientId(pAppCtrl->usClientId, UEPS_PID_XPDS);
    pstMsgStr->stAppCtrl.ucOpId      = pAppCtrl->ucOpId;
    pstMsgStr->stAppCtrl.aucReserved[0] = 0;

    /* 发送消息到AT模块 */
    if (VOS_OK != PS_SEND_MSG(UEPS_PID_XPDS, pstMsgStr))
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtMsgNoData():WARNING:SEND MSG FIAL");
    }

    return;
}


VOS_VOID TAF_XPDS_SndAtApOpenCagpsDataCall(VOS_VOID)
{
    XPDS_AT_AP_DATA_CALL_REQ_STRU       stDataConStatus;
    AT_APPCTRL_STRU                     stAppCtrl;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    stDataConStatus.enAgpsMode      = TAF_XPDS_GetCgpsInitialType();            /* SI or Ni */
    stDataConStatus.enAgpsOper      = AT_XPDS_AGPS_DATA_CALL_CTRL_CONNECT;

    stAppCtrl.usClientId = MN_CLIENT_ALL;
    stAppCtrl.ucOpId     = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_AP_DATA_CALL_REQ,
                     sizeof(stDataConStatus),
                     (VOS_UINT8*)&stDataConStatus);

    return;
}
VOS_VOID TAF_XPDS_SndAtApCloseCagpsDataCall(VOS_VOID)
{
    XPDS_AT_AP_DATA_CALL_REQ_STRU       stDataConStatus;
    AT_APPCTRL_STRU                     stAppCtrl;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    stDataConStatus.enAgpsMode      = TAF_XPDS_GetCgpsInitialType();            /* SI or Ni */
    stDataConStatus.enAgpsOper      = AT_XPDS_AGPS_DATA_CALL_CTRL_RELEASE;

    stAppCtrl.usClientId = TAF_XPDS_GetApClientId();
    stAppCtrl.ucOpId     = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
        ID_XPDS_AT_AP_DATA_CALL_REQ,
        sizeof(stDataConStatus),
        (VOS_UINT8*)&stDataConStatus);

    return;
}
VOS_VOID TAF_XPDS_SndAtApOpenSocketReq(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
)
{
    XPDS_AT_AP_SERVER_BIND_REQ_STRU     stBinUpReq;
    AT_APPCTRL_STRU                     stAppCtrl;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    stBinUpReq.enDataCallCtrl = AT_XPDS_AGPS_DATA_CALL_CTRL_CONNECT;
    stBinUpReq.enServerMode   = enServerMode;
    stBinUpReq.ulIpAddr       = ulIpAddr;
    stBinUpReq.ulPortNum      = ulPortNum;

    stAppCtrl.usClientId = TAF_XPDS_GetApClientId();
    stAppCtrl.ucOpId     = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_AP_SERVER_BIND_REQ,
                     sizeof(stBinUpReq),
                     (VOS_UINT8*)&stBinUpReq);

    return;
}


VOS_VOID TAF_XPDS_SndAtApCloseSocketReq(
    AT_XPDS_SERVER_MODE_ENUM_UINT32      enServerMode,
    VOS_UINT32                          ulIpAddr,
    VOS_UINT32                          ulPortNum
)
{
    XPDS_AT_AP_SERVER_BIND_REQ_STRU     stBinUpReq;
    AT_APPCTRL_STRU                     stAppCtrl;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    stBinUpReq.enDataCallCtrl   = AT_XPDS_AGPS_DATA_CALL_CTRL_RELEASE;
    stBinUpReq.enServerMode = enServerMode;
    stBinUpReq.ulIpAddr     = ulIpAddr;
    stBinUpReq.ulPortNum    = ulPortNum;

    stAppCtrl.usClientId = TAF_XPDS_GetApClientId();
    stAppCtrl.ucOpId     = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_AP_SERVER_BIND_REQ,
                     sizeof(stBinUpReq),
                     (VOS_UINT8*)&stBinUpReq);

    return;
}


VOS_VOID TAF_XPDS_SndAtGpsTimeSyncInfo(
    CAS_XPDS_TIME_SYNC_IND_STRU        *pstRcvSyncTime
)
{
    XPDS_AT_GPS_SYNC_TIME_IND_STRU      stSyncTimeInfo;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT32                          ulRet;

    PS_MEM_SET(&stSyncTimeInfo, 0, sizeof(XPDS_AT_GPS_SYNC_TIME_IND_STRU));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    if (XPDS_CAS_RESULT_NO_ERROR == pstRcvSyncTime->enResult)
    {
        stSyncTimeInfo.enResult  = XPDS_AT_SYNC_TIME_VALID;
    }
    else
    {
        /* 异常回复AP协商错误值 */
        stSyncTimeInfo.enResult  = XPDS_AT_SYNC_TIME_NOT_VALID;
    }

    /* GPS需要的单位是ns,cas上报的时1/16chip = 50.863ns */
    ulRet = VOS_64Multi32(pstRcvSyncTime->aulPulseTime[1],
                          pstRcvSyncTime->aulPulseTime[0],
                          51,
                          &stSyncTimeInfo.aulPulseTime[1],
                          &stSyncTimeInfo.aulPulseTime[0]);
    if (VOS_OK != ulRet)
    {
        /* 回复无效值 */
        stSyncTimeInfo.enResult  = XPDS_AT_SYNC_TIME_NOT_VALID;
    }

#if 0
    ulRet = VOS_64Div32(aulPulseTimeTemp[1],
                        aulPulseTimeTemp[0],
                        1000,
                        &stSyncTimeInfo.aulPulseTime[1],
                        &stSyncTimeInfo.aulPulseTime[0],
                        VOS_NULL_PTR);

    if (VOS_OK != ulRet)
    {
        /* 回复无效值 */
        stSyncTimeInfo.enResult  = XPDS_AT_SYNC_TIME_NOT_VALID;
    }
#endif

    stAppCtrl.usClientId = TAF_XPDS_GetGpsClientId();

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                      ID_XPDS_AT_GPS_TIME_INFO_IND,
                      sizeof(stSyncTimeInfo),
                      (VOS_UINT8*)&stSyncTimeInfo);

    return;
}


VOS_VOID TAF_XPDS_SndAtApMpcStartPosReq
(
    VOS_VOID
)
{
    TAF_XPDS_MPC_START_POS_REQ_STRU     stStartPosReq;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[TAF_XPDS_MAX_DATA_LEN];

    PS_MEM_SET(&stStartPosReq, 0, sizeof(TAF_XPDS_MPC_START_POS_REQ_STRU));
    PS_MEM_SET(aucData, 0x00, TAF_XPDS_MAX_DATA_LEN);

    TAF_XPDS_FillMpcStartPosReq(&stStartPosReq);

    TAF_XPDS_MNTN_TraceReverseMpcStartPosReq(&stStartPosReq);

    TAF_XPDS_EncodeMpcStartPosReq(&stStartPosReq,
                                  &ulDataLen,
                                  aucData);

    TAF_XPDS_SndApMsg(AT_XPDS_SERVER_MODE_MPC, aucData, ulDataLen);

    return ;
}


VOS_VOID TAF_XPDS_SndAtApMpcPosReportReq
(
    VOS_VOID
)
{
    TAF_XPDS_MPC_POS_REPORT_STRU        stPosReportReq;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                           aucData[TAF_XPDS_MAX_DATA_LEN];

    PS_MEM_SET(&stPosReportReq, 0, sizeof(TAF_XPDS_MPC_POS_REPORT_STRU));
    PS_MEM_SET(aucData, 0x00, TAF_XPDS_MAX_DATA_LEN);

    TAF_XPDS_FillMpcPosReportReq(&stPosReportReq);

    TAF_XPDS_MNTN_TraceReverseMpcPosReportReq(&stPosReportReq);

    TAF_XPDS_EncodeMpcPosReportReq(&stPosReportReq,
                                   &ulDataLen,
                                   aucData);

    TAF_XPDS_SndApMsg(AT_XPDS_SERVER_MODE_MPC, aucData, ulDataLen);

    return ;
}



VOS_VOID TAF_XPDS_SndAtApPdeSessionEndMsg(VOS_VOID)
{
    TAF_XPDS_PD_MSG_HEADER_STRU                stPdMsgHeader;
    VOS_UINT8                                 *pucMsgBuff;
    VOS_UINT32                                 ulTotLength;
    VOS_UINT32                                 ulTempLen;

    /* allocate memory for the message */
    pucMsgBuff  = (VOS_UINT8 *)PS_MEM_ALLOC(UEPS_PID_XPDS, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    if (VOS_NULL_PTR == pucMsgBuff)
    {
        XPDS_ERROR_LOG("TAF_XPDS_SndAtApPdeSessionEndMsg, malloc failed");

        return;
    }

    PS_MEM_SET(pucMsgBuff, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    PS_MEM_SET(&stPdMsgHeader, 0x00, sizeof(TAF_XPDS_PD_MSG_HEADER_STRU));

    stPdMsgHeader.ucSessStart  = 0;
    stPdMsgHeader.ucSessEnd    = 1;

    if (TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_MS == TAF_XPDS_GetPdeSessionTriggerType())
    {
        stPdMsgHeader.ucSessSrc = 1;
    }
    else
    {
        stPdMsgHeader.ucSessSrc = 0;
    }

    stPdMsgHeader.ucSessTag   = TAF_XPDS_GetSessTagInRsvPdMsgHeader();
    stPdMsgHeader.ucPdMsgType = 0;

    /* number of req and response is 0 as of now in session end message */
    stPdMsgHeader.ucNumOfReq   = 0;
    stPdMsgHeader.ucNumOfResp  = 1;

    ulTotLength              = 0;
    ulTempLen                = 0;

    TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(&stPdMsgHeader);

    TAF_XPDS_EncodePdMsgHeader(&stPdMsgHeader, pucMsgBuff + ulTotLength + 1, &ulTempLen); /* +1 for length field of data burst message */

    ulTotLength += ulTempLen;
    ulTempLen    = 0;

    TAF_XPDS_EncodeProvMsInfo(pucMsgBuff + ulTotLength + 1, &ulTempLen); /* +1 for length field of data burst message */

    ulTotLength += ulTempLen;

    /* update the length field of data burst message */
    pucMsgBuff[0] = (VOS_UINT8)ulTotLength;

    ulTotLength += 1;

    /* need to send message to PDE */
    TAF_XPDS_SndApMsg(AT_XPDS_SERVER_MODE_PDE, pucMsgBuff, ulTotLength);

    /* freeing the memory */
    PS_MEM_FREE(UEPS_PID_XPDS, pucMsgBuff);
}
VOS_VOID TAF_XPDS_SndAtApPdeRejectRsp(
    TAF_XPDS_REVLINK_RSP_REJECT_STRU                       *pstRejInfo
)
{
    TAF_XPDS_PD_MSG_HEADER_STRU         stPdMsgHeader;
    VOS_UINT8                           aucSendData[TAF_XPDS_MAX_PDM_MSG_BUF_LEN];
    VOS_UINT32                          ulDataLen;
    VOS_UINT32                          ulTempLen;

    PS_MEM_SET(aucSendData, 0x00, TAF_XPDS_MAX_PDM_MSG_BUF_LEN);

    /* 构造Posotion Determination Data Message header */
    PS_MEM_SET(&stPdMsgHeader, 0, sizeof(stPdMsgHeader));

    stPdMsgHeader.ucSessStart = 0;
    stPdMsgHeader.ucSessEnd   = 0;

    if (TAF_XPDS_PDE_SESSION_TRIGGER_TYPE_MS == TAF_XPDS_GetPdeSessionTriggerType())
    {
        stPdMsgHeader.ucSessSrc = 1;
    }
    else
    {
        stPdMsgHeader.ucSessSrc = 0;
    }

    stPdMsgHeader.ucSessTag   = TAF_XPDS_GetSessTagInRsvPdMsgHeader();

    stPdMsgHeader.ucPdMsgType = 0;

    stPdMsgHeader.ucNumOfReq  = 0;
    stPdMsgHeader.ucNumOfResp = 1;

    ulDataLen  = 0;
    ulTempLen  = 0;

    TAF_XPDS_MNTN_TraceReversePdeHeaderInfo(&stPdMsgHeader);

    /* First Session Header */
    TAF_XPDS_EncodePdMsgHeader(&stPdMsgHeader, &aucSendData[1], &ulTempLen);

    ulDataLen  += ulTempLen;
    ulTempLen   = 0;

    TAF_XPDS_EncodeReject(pstRejInfo, &aucSendData[ulDataLen + 1], &ulTempLen);

    ulDataLen += ulTempLen;

    aucSendData[0] = (VOS_UINT8)(ulDataLen);

    /* add the first byte */
    ulDataLen  += 1;

    TAF_XPDS_MNTN_TraceReversePdeRejRsp(pstRejInfo);

    /* After encode work, Snd msg to AP */
    TAF_XPDS_SndApMsg(AT_XPDS_SERVER_MODE_PDE, aucSendData, ulDataLen);

    return;
}


VOS_VOID TAF_XPDS_SndApMsg
(
    AT_XPDS_SERVER_MODE_ENUM_UINT32     enServerMode,
    const VOS_UINT8                    *pucData,
    VOS_UINT32                          ulLen
)
{
    AT_APPCTRL_STRU                     stAppCtrl;
    XPDS_AT_AP_REVERSE_DATA_IND_STRU   *pstUpdataReq;
    VOS_UINT32                          ulMsgLen;

    ulMsgLen    = sizeof(XPDS_AT_AP_REVERSE_DATA_IND_STRU) + ulLen - 4;

    pstUpdataReq = (XPDS_AT_AP_REVERSE_DATA_IND_STRU*)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                               ulMsgLen);
    if (VOS_NULL_PTR == pstUpdataReq)
    {
        return;
    }

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));
    PS_MEM_SET((VOS_UINT8*)pstUpdataReq, 0, ulMsgLen);

    pstUpdataReq->enServerMode  = enServerMode;

    pstUpdataReq->ulDataLen     = ulLen;

    PS_MEM_CPY(pstUpdataReq->aucData, pucData, ulLen);

    /* stAppCtrl */
    stAppCtrl.usClientId = TAF_XPDS_GetApClientId();

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                      ID_XPDS_AT_AP_REVERSE_DATA_IND,
                      ulMsgLen,
                      (VOS_UINT8*)pstUpdataReq);

    PS_MEM_FREE(UEPS_PID_XPDS, pstUpdataReq);
}
VOS_VOID TAF_XPDS_SndAtGpsAbortPosInd(
    XPDS_AT_ABORT_POS_REASON_ENUM_UINT16    enAbortReason
)
{
    XPDS_AT_GPS_ABORT_IND_STRU          stAbortInd;
    AT_APPCTRL_STRU                     stAppCtrl;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));
    PS_MEM_SET(&stAbortInd, 0, sizeof(XPDS_AT_GPS_ABORT_IND_STRU));

    stAbortInd.enAbortReason = enAbortReason;

    stAppCtrl.usClientId     = TAF_XPDS_GetGpsClientId();
    stAppCtrl.ucOpId         = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                      ID_XPDS_AT_GPS_ABORT_IND,
                      sizeof(stAbortInd),
                      (VOS_UINT8*)&stAbortInd);

    return;

}


VOS_VOID TAF_XPDS_SndAtGpsStopCnf(VOS_VOID)
{
    XPDS_AT_RESULT_CNF_STRU             stStopCnf;
    AT_APPCTRL_STRU                     stAppCtrl;

    PS_MEM_SET(&stStopCnf, 0x0, sizeof(stStopCnf));
    stStopCnf.enResult = XPDS_AT_RESULT_NO_ERROR;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(stAppCtrl));
    stAppCtrl.usClientId = TAF_XPDS_GetGpsClientId();

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                      ID_XPDS_AT_GPS_STOP_CNF,
                      sizeof(stStopCnf),
                      (VOS_UINT8*)&stStopCnf);

    return;
}


VOS_VOID TAF_XPDS_SndAtGpsNiSessionInd(
    TAF_XPDS_RCV_XSMS_POS_REQ_STRU    *pstXsmsMsg
)
{
    AT_APPCTRL_STRU                     stAppCtrl;
    XPDS_AT_GPS_NI_SESSION_IND_STRU     stNiInd;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));
    PS_MEM_SET(&stNiInd, 0, sizeof(XPDS_AT_GPS_NI_SESSION_IND_STRU));

    /* 填写GPS要求的结构体 */
    stNiInd.ucLen               = pstXsmsMsg->ucLen;
    stNiInd.enNotificationInd   = pstXsmsMsg->enNotificationInd;
    stNiInd.enPosTechInd        = pstXsmsMsg->enPosTechInd;
    stNiInd.ucPosQoSInc         = pstXsmsMsg->ucPosQoSInc;
    stNiInd.ucPosQoS            = pstXsmsMsg->ucPosQoS;
    stNiInd.enIS801PosMode      = pstXsmsMsg->enIS801PosMode;
    stNiInd.usNumOfFixs         = pstXsmsMsg->usNumOfFixs;
    stNiInd.usTimeBetweenFixs   = pstXsmsMsg->usTimeBetweenFixs;
    stNiInd.ucCorrelationId     = pstXsmsMsg->ucCorrelationId;
    stNiInd.ucReqIdEncode       = pstXsmsMsg->ucReqIdEncode;
    stNiInd.ucReqIdLen          = pstXsmsMsg->ucReqIdLen;

    PS_MEM_CPY(stNiInd.aucData, pstXsmsMsg->aucData, stNiInd.ucReqIdLen);

    /* 填写APP_CTRL */
    stAppCtrl.usClientId    = MN_CLIENT_ALL;
    stAppCtrl.ucOpId        = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_GPS_NI_SESSION_IND,
                     sizeof(XPDS_AT_GPS_NI_SESSION_IND_STRU),
                     (VOS_UINT8*)&stNiInd);

    return;

}


VOS_VOID TAF_XPDS_SndAtGpsCancelNiSession(
    VOS_VOID
)
{
    AT_APPCTRL_STRU                     stAppCtrl;
    XPDS_AT_GPS_CANCEL_IND_STRU         stCancelInd;

    stCancelInd.ulData      = 1;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    /* 填写APP_CTRL */
    stAppCtrl.usClientId   = TAF_XPDS_GetGpsClientId();
    stAppCtrl.ucOpId       = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_GPS_CANCEL_IND,
                     sizeof(XPDS_AT_GPS_CANCEL_IND_STRU),
                     (VOS_UINT8*)&stCancelInd);

    return ;
}
VOS_VOID TAF_XPDS_SndAtGpsCpNiStart(
    VOS_VOID
)
{
    AT_APPCTRL_STRU                     stAppCtrl;
    XPDS_AT_GPS_NI_CP_START_STRU        stNiCpStart;

    stNiCpStart.ulStartCode = 0;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    /* 填写APP_CTRL */
    stAppCtrl.usClientId   = TAF_XPDS_GetGpsClientId();
    stAppCtrl.ucOpId       = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_GPS_NI_CP_START,
                     sizeof(XPDS_AT_GPS_NI_CP_START_STRU),
                     (VOS_UINT8*)&stNiCpStart);

    return ;
}
VOS_VOID TAF_XPDS_SndAtGpsCpNiStop(
    VOS_VOID
)
{
    AT_APPCTRL_STRU                     stAppCtrl;
    XPDS_AT_GPS_NI_CP_STOP_STRU         stNiCpStop;

    stNiCpStop.ulStartCode = 0;

    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    /* 填写APP_CTRL */
    stAppCtrl.usClientId   = TAF_XPDS_GetGpsClientId();
    stAppCtrl.ucOpId       = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_GPS_NI_CP_STOP,
                     sizeof(XPDS_AT_GPS_NI_CP_STOP_STRU),
                     (VOS_UINT8*)&stNiCpStop);

    return ;
}


/*****************************************************************************
 Func Name    : TAF_XPDS_SndAtGpsAcqAssistData
 Description  : Function for sending the ID_XPDS_AT_ACQASSIST_DATA_IND msg
                to the GPS module

  History       :
  1.Date        : 21-07-2015
    Author      :  Arjun a00903922
    Modification:  Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsAcqAssistData(VOS_VOID)
{
    XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU                    stPdeAcqAssisData;
    TAF_XPDS_FWDLINK_RSP_GPS_ACQ_ASSIST_STRU               *pstProvAcqAssist;
    AT_APPCTRL_STRU                                         stAppCtrl;
    VOS_UINT8                                               ucLoopCount;

    pstProvAcqAssist = &(TAF_XPDS_GetPdePublicData()->stProvAcqAssist);

    PS_MEM_SET(&stPdeAcqAssisData, 0x00, sizeof(XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    /* update the sending data */

    stPdeAcqAssisData.ucaAzEl           = pstProvAcqAssist->ucAzElIncl;
    stPdeAcqAssisData.ucAddDopplerInc   = pstProvAcqAssist->ucAddDoppIncl;
    stPdeAcqAssisData.ucCodePhaseInc    = pstProvAcqAssist->ucCodePhParIncl;
    stPdeAcqAssisData.ucDoppler0Inc     = pstProvAcqAssist->ucDopp0Incl;
    stPdeAcqAssisData.ucSvNum           = pstProvAcqAssist->ucNumOfSv;
    stPdeAcqAssisData.ulRefTow          = TAF_XPDS_CalcTimeInWeek(pstProvAcqAssist->ucTimeOfApp);

    for (ucLoopCount = 0; ucLoopCount < TAF_MSG_CDMA_MAX_SV_NUM; ucLoopCount++)
    {
        stPdeAcqAssisData.astAaData[ucLoopCount].ucSvId             = pstProvAcqAssist->astSatInfo[ucLoopCount].ucSvPrnNum; //TODO - confirm
        stPdeAcqAssisData.astAaData[ucLoopCount].ucGpsBitNum        = pstProvAcqAssist->astSatInfo[ucLoopCount].ucGpsBitNum;
        stPdeAcqAssisData.astAaData[ucLoopCount].cDoppler1          = pstProvAcqAssist->astSatInfo[ucLoopCount].cDoppler1;
        stPdeAcqAssisData.astAaData[ucLoopCount].sDoppler0          = pstProvAcqAssist->astSatInfo[ucLoopCount].sDoppler0;
        stPdeAcqAssisData.astAaData[ucLoopCount].ucDoppler_win      = pstProvAcqAssist->astSatInfo[ucLoopCount].ucDopplerWin;
        stPdeAcqAssisData.astAaData[ucLoopCount].ucAzimuth          = pstProvAcqAssist->astSatInfo[ucLoopCount].ucAzimuth;
        stPdeAcqAssisData.astAaData[ucLoopCount].ucElevation        = pstProvAcqAssist->astSatInfo[ucLoopCount].ucElevation;
        stPdeAcqAssisData.astAaData[ucLoopCount].usSvCodePhase      = pstProvAcqAssist->astSatInfo[ucLoopCount].usSvCodePh;
        stPdeAcqAssisData.astAaData[ucLoopCount].ucSvCodePhaseInt   = pstProvAcqAssist->astSatInfo[ucLoopCount].ucSvCodePhInt;
        stPdeAcqAssisData.astAaData[ucLoopCount].ucSvCodePhaseWin   = pstProvAcqAssist->astSatInfo[ucLoopCount].ucSvCodePhWin;
    }

    stAppCtrl.usClientId = TAF_XPDS_GetGpsClientId();

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_GPS_ACQ_ASSIST_DATA_IND,
                     sizeof(XPDS_AT_GPS_ACQ_ASSIST_DATA_IND_STRU),
                     (VOS_UINT8*)&stPdeAcqAssisData);

    return;
}
VOS_VOID TAF_XPDS_SndAtGpsIonInfo(VOS_VOID)
{
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph = VOS_NULL_PTR;
    XPDS_AT_GPS_ION_INFO_IND_STRU       stIonInfoInd;
    AT_APPCTRL_STRU                     stAppCtrl;

    PS_MEM_SET(&stIonInfoInd, 0, sizeof(XPDS_AT_GPS_ION_INFO_IND_STRU));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    pstProvEph  = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);

    stIonInfoInd.ucABParIncl = pstProvEph->ucABParIncl;
    stIonInfoInd.ucAlpha0    = pstProvEph->ucAlpha0;
    stIonInfoInd.ucAlpha1    = pstProvEph->ucAlpha1;
    stIonInfoInd.ucAlpha2    = pstProvEph->ucAlpha2;
    stIonInfoInd.ucAlpha3    = pstProvEph->ucAlpha3;
    stIonInfoInd.ucBeta0     = pstProvEph->ucBeta0;
    stIonInfoInd.ucBeta1     = pstProvEph->ucBeta1;
    stIonInfoInd.ucBeta2     = pstProvEph->ucBeta2;
    stIonInfoInd.ucBeta3     = pstProvEph->ucBeta3;

    stAppCtrl.usClientId = TAF_XPDS_GetGpsClientId();
    stAppCtrl.ucOpId     = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_GPS_ION_INFO_IND,
                     sizeof(XPDS_AT_GPS_ION_INFO_IND_STRU),
                     (VOS_UINT8 *)(&stIonInfoInd));
}



VOS_VOID TAF_XPDS_SndAtGpsEphInfo(VOS_VOID)
{
    TAF_XPDS_FWDLINK_RSP_GPS_EPH_STRU  *pstProvEph = VOS_NULL_PTR;
    XPDS_AT_GPS_EPH_INFO_IND_STRU      *pstEphInfoInd = VOS_NULL_PTR;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           ucLoop;

    pstEphInfoInd = (XPDS_AT_GPS_EPH_INFO_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                    sizeof(XPDS_AT_GPS_EPH_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstEphInfoInd)
    {
        return;
    }

    PS_MEM_SET(pstEphInfoInd, 0, sizeof(XPDS_AT_GPS_EPH_INFO_IND_STRU));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    pstProvEph  = &(TAF_XPDS_GetPdePublicData()->stProvGpsEph);

    if (pstProvEph->ucNumOfSvP >= TAF_MSG_CDMA_MAX_EPH_PRN_NUM)
    {
        pstEphInfoInd->ucSvNum = TAF_MSG_CDMA_MAX_EPH_PRN_NUM;
    }
    else
    {
        pstEphInfoInd->ucSvNum = pstProvEph->ucNumOfSvP;
    }

    for (ucLoop = 0; ucLoop < pstEphInfoInd->ucSvNum; ucLoop++)
    {
        pstEphInfoInd->astEphData[ucLoop].ucSvId         = pstProvEph->astSatInfo[ucLoop].ucSv_Prn_Num;
        pstEphInfoInd->astEphData[ucLoop].ucAf2          = pstProvEph->astSatInfo[ucLoop].ucAF2;
        pstEphInfoInd->astEphData[ucLoop].ucIode         = pstProvEph->astSatInfo[ucLoop].ucIODE;
        pstEphInfoInd->astEphData[ucLoop].usToc          = pstProvEph->astSatInfo[ucLoop].usTOC;
        pstEphInfoInd->astEphData[ucLoop].usToe          = pstProvEph->astSatInfo[ucLoop].usTOE;
        pstEphInfoInd->astEphData[ucLoop].usAf1          = pstProvEph->astSatInfo[ucLoop].usAF1;
        pstEphInfoInd->astEphData[ucLoop].usDelta_n      = pstProvEph->astSatInfo[ucLoop].usDelta_N;
        pstEphInfoInd->astEphData[ucLoop].usIdot         = pstProvEph->astSatInfo[ucLoop].usIdot;
        pstEphInfoInd->astEphData[ucLoop].usCrs          = pstProvEph->astSatInfo[ucLoop].usC_RS;
        pstEphInfoInd->astEphData[ucLoop].usCrc          = pstProvEph->astSatInfo[ucLoop].usC_RC;
        pstEphInfoInd->astEphData[ucLoop].usCus          = pstProvEph->astSatInfo[ucLoop].usC_US;
        pstEphInfoInd->astEphData[ucLoop].usCuc          = pstProvEph->astSatInfo[ucLoop].usC_UC;
        pstEphInfoInd->astEphData[ucLoop].usCis          = pstProvEph->astSatInfo[ucLoop].usC_IS;
        pstEphInfoInd->astEphData[ucLoop].usCic          = pstProvEph->astSatInfo[ucLoop].usC_IC;
        pstEphInfoInd->astEphData[ucLoop].ulAf0          = pstProvEph->astSatInfo[ucLoop].ulAF0;
        pstEphInfoInd->astEphData[ucLoop].ulM0           = pstProvEph->astSatInfo[ucLoop].ulM0;
        pstEphInfoInd->astEphData[ucLoop].ulAsqrt        = pstProvEph->astSatInfo[ucLoop].ulA_Sqrt;
        pstEphInfoInd->astEphData[ucLoop].ulEccentricity = pstProvEph->astSatInfo[ucLoop].ulEcCentricity;
        pstEphInfoInd->astEphData[ucLoop].ulIangle       = pstProvEph->astSatInfo[ucLoop].ulAngle_Incli;
        pstEphInfoInd->astEphData[ucLoop].ulOmega0       = pstProvEph->astSatInfo[ucLoop].ulOmega_0;
        pstEphInfoInd->astEphData[ucLoop].ulOmega        = pstProvEph->astSatInfo[ucLoop].ulOmega;
        pstEphInfoInd->astEphData[ucLoop].ulOmegadot     = pstProvEph->astSatInfo[ucLoop].ulOmegaDot;
    }

    stAppCtrl.usClientId = TAF_XPDS_GetGpsClientId();
    stAppCtrl.ucOpId     = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                      ID_XPDS_AT_GPS_EPH_INFO_IND,
                      sizeof(XPDS_AT_GPS_EPH_INFO_IND_STRU),
                      (VOS_UINT8 *)pstEphInfoInd);

    PS_MEM_FREE(UEPS_PID_XPDS, pstEphInfoInd);
}



VOS_VOID TAF_XPDS_SndAtGpsAlmInfo(VOS_VOID)
{
    TAF_XPDS_FWDLINK_RSP_GPS_ALM_STRU  *pstProvAlm = VOS_NULL_PTR;
    XPDS_AT_GPS_ALM_INFO_IND_STRU      *pstAlmInfoInd = VOS_NULL_PTR;
    AT_APPCTRL_STRU                     stAppCtrl;
    VOS_UINT8                           ucLoop;

    pstAlmInfoInd = (XPDS_AT_GPS_ALM_INFO_IND_STRU *)PS_MEM_ALLOC(UEPS_PID_XPDS,
                                                    sizeof(XPDS_AT_GPS_ALM_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstAlmInfoInd)
    {
        return;
    }

    PS_MEM_SET(pstAlmInfoInd, 0, sizeof(XPDS_AT_GPS_ALM_INFO_IND_STRU));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    pstProvAlm  = &(TAF_XPDS_GetPdePublicData()->stProvGpsAlm);

    if (pstProvAlm->ucNumOfSvP >= TAF_MSG_CDMA_MAX_ALM_PRN_NUM)
    {
        pstAlmInfoInd->ucSvNum = TAF_MSG_CDMA_MAX_ALM_PRN_NUM;
    }
    else
    {
        pstAlmInfoInd->ucSvNum = pstProvAlm->ucNumOfSvP;
    }

    pstAlmInfoInd->ucWeekNum = pstProvAlm->ucWeekNum;
    pstAlmInfoInd->ucToa     = pstProvAlm->ucTOA;

    for (ucLoop = 0; ucLoop < pstAlmInfoInd->ucSvNum; ucLoop++)
    {
        pstAlmInfoInd->astAlmData[ucLoop].ucSvId         = pstProvAlm->astSatInfo[ucLoop].ucSv_Prn_Num;
        pstAlmInfoInd->astAlmData[ucLoop].usDeltai       = pstProvAlm->astSatInfo[ucLoop].usDelta_Incli;
        pstAlmInfoInd->astAlmData[ucLoop].usAf0          = pstProvAlm->astSatInfo[ucLoop].usAF0;
        pstAlmInfoInd->astAlmData[ucLoop].usAf1          = pstProvAlm->astSatInfo[ucLoop].usAF1;
        pstAlmInfoInd->astAlmData[ucLoop].usOmegadot     = pstProvAlm->astSatInfo[ucLoop].usOmegaDot;
        pstAlmInfoInd->astAlmData[ucLoop].usEccentricity = pstProvAlm->astSatInfo[ucLoop].usEcCentricity;
        pstAlmInfoInd->astAlmData[ucLoop].ulAsqrt        = pstProvAlm->astSatInfo[ucLoop].ulA_Sqrt;
        pstAlmInfoInd->astAlmData[ucLoop].ulOmega_0      = pstProvAlm->astSatInfo[ucLoop].ulOmega_0;
        pstAlmInfoInd->astAlmData[ucLoop].ulOmega        = pstProvAlm->astSatInfo[ucLoop].ulOmega;
        pstAlmInfoInd->astAlmData[ucLoop].ulM0           = pstProvAlm->astSatInfo[ucLoop].ulM0;
    }

    stAppCtrl.usClientId = TAF_XPDS_GetGpsClientId();
    stAppCtrl.ucOpId     = 0;

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                      ID_XPDS_AT_GPS_ALM_INFO_IND,
                      sizeof(XPDS_AT_GPS_ALM_INFO_IND_STRU),
                      (VOS_UINT8 *)pstAlmInfoInd);

    PS_MEM_FREE(UEPS_PID_XPDS, pstAlmInfoInd);
}

/*****************************************************************************
 Func Name    : TAF_XPDS_SndAtGpsPositionInfo
 Description  : Function for sending the ID_XPDS_AT_PDE_POSI_INFO_IND msg
                to the GPS module

  History       :
  1.Date        : 20-07-2015
    Author      :  Arjun a00903922
    Modification:  Created function
*****************************************************************************/
VOS_VOID TAF_XPDS_SndAtGpsPositionInfo(VOS_VOID)
{
    XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU  stPdePosiInfo;
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU *pstProvLocRsp;
    AT_APPCTRL_STRU                     stAppCtrl;

    pstProvLocRsp   = &(TAF_XPDS_GetPublicDataAddr()->stProvLocRsp);

    PS_MEM_SET(&stPdePosiInfo, 0x00, sizeof(XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU));
    PS_MEM_SET(&stAppCtrl, 0, sizeof(AT_APPCTRL_STRU));

    /* update the sending data */
    stPdePosiInfo.ucVelocityIncl = pstProvLocRsp->ucVelocityIncl;
    stPdePosiInfo.ucHeightIncl   = pstProvLocRsp->ucHeightIncl;
    stPdePosiInfo.ucClockIncl    = pstProvLocRsp->ucClockIncl;
    stPdePosiInfo.ucFixType      = pstProvLocRsp->ucFixType;
    stPdePosiInfo.sLocUncAng     = pstProvLocRsp->ucLocUncerAng;
    stPdePosiInfo.sClockDrift    = pstProvLocRsp->sClockDrift;
    stPdePosiInfo.lClockBias     = pstProvLocRsp->lClockBias;
    stPdePosiInfo.lLatitude      = pstProvLocRsp->lLattitude;
    stPdePosiInfo.lLongitude     = pstProvLocRsp->lLongitude;
    stPdePosiInfo.ulLocUncA      = pstProvLocRsp->ucLocUncerA;
    stPdePosiInfo.ulLocUncP      = pstProvLocRsp->ucLocUncerP;
    stPdePosiInfo.ulVelocityHor  = pstProvLocRsp->usVelocityHor;
    stPdePosiInfo.ulHeading      = pstProvLocRsp->usHeading;
    stPdePosiInfo.lHeight        = pstProvLocRsp->sHeight;
    stPdePosiInfo.lVerticalVelo  = pstProvLocRsp->cVelocityVer;
    stPdePosiInfo.ulLocUncV      = pstProvLocRsp->ucLocUncerV;

    stAppCtrl.usClientId = TAF_XPDS_GetGpsClientId();

    TAF_XPDS_SndAtMsg(&stAppCtrl,
                     ID_XPDS_AT_GPS_PDE_POSI_INFO_IND,
                     sizeof(XPDS_AT_GPS_PDE_POSI_INFO_IND_STRU),
                     (VOS_UINT8*)&stPdePosiInfo );

    return;
}
VOS_VOID TAF_XPDS_SetPosReportLocInfo(
    TAF_XPDS_MPC_POS_REPORT_STRU       *pstPosReportReq
)
{
    TAF_XPDS_FIX_MODE_ENUM_UINT8        enCurFixMode;
    TAF_XPDS_FWDLINK_RSP_LOC_RESP_STRU *pstProvLocRsp;
    AT_XPDS_GPS_POS_INFO_RSP_STRU      *pstCagpsPosInfoRsp;

    pstProvLocRsp       = &(TAF_XPDS_GetPublicDataAddr()->stProvLocRsp);
    pstCagpsPosInfoRsp  = &(TAF_XPDS_GetPublicDataAddr()->stCagpsPosInfoRsp);
    enCurFixMode        = TAF_XPDS_GetAgpsFixMode();

    if ((TAF_XPDS_MSA_MODE == enCurFixMode)
     || (TAF_XPDS_AFLT_MODE == enCurFixMode))
    {
        pstPosReportReq->ulPosIncFlag = VOS_TRUE;

        pstPosReportReq->lLat               = pstProvLocRsp->lLattitude;
        pstPosReportReq->lLong              = pstProvLocRsp->lLongitude;
        pstPosReportReq->ucLocUncrtntyAng   = pstProvLocRsp->ucLocUncerAng;
        pstPosReportReq->ucLocUncrtntyA     = pstProvLocRsp->ucLocUncerA;
        pstPosReportReq->ucLocUncrtntyP     = pstProvLocRsp->ucLocUncerP;
        pstPosReportReq->ucVelocityIncl     = VOS_TRUE;
        pstPosReportReq->usVelocityHor      = pstProvLocRsp->usVelocityHor;
        pstPosReportReq->sVelocityVer       = (VOS_INT16)pstProvLocRsp->cVelocityVer;

        pstPosReportReq->usHeading          = pstProvLocRsp->usHeading;

        pstPosReportReq->usHeihtIncl        = VOS_TRUE;
        pstPosReportReq->sHeiht             =  pstProvLocRsp->sHeight;
        pstPosReportReq->usLocUncrtntyV     =  pstProvLocRsp->ucLocUncerV;


    }
    else if (TAF_XPDS_MSB_MODE == enCurFixMode)
    {
        if (VOS_FALSE == pstCagpsPosInfoRsp->ulValidityMask)
        {
            pstPosReportReq->ulPosIncFlag = VOS_FALSE;
        }
        else
        {
            pstPosReportReq->ulPosIncFlag = VOS_TRUE;

            pstPosReportReq->lLat               = pstCagpsPosInfoRsp->lLatitude;
            pstPosReportReq->lLong              = pstCagpsPosInfoRsp->lLongitude;
            pstPosReportReq->ucLocUncrtntyAng   = 0;
            pstPosReportReq->ucLocUncrtntyA     = 0;
            pstPosReportReq->ucLocUncrtntyP     = 0;
            pstPosReportReq->ucVelocityIncl     = VOS_TRUE;
            pstPosReportReq->usVelocityHor      = (VOS_UINT16)pstCagpsPosInfoRsp->ulHorizontalVelocity;
            pstPosReportReq->sVelocityVer       = (VOS_INT16)pstCagpsPosInfoRsp->ulVerticalVelocity;

            pstPosReportReq->usHeading          = (VOS_UINT16)pstCagpsPosInfoRsp->ulHeading;

            pstPosReportReq->usHeihtIncl        = VOS_FALSE;
        }
    }
    else
    {
        pstPosReportReq->ulPosIncFlag = VOS_FALSE;
    }

    return;
}


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
