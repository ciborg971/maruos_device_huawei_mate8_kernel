

/*****************************************************************************
  1 头文件包含
*****************************************************************************/

#include "PsCommonDef.h"
#include "PsTypeDef.h"
#include "TafLog.h"
#include "Taf_Aps.h"
#include "MnApsComm.h"
#include "ApsCdsInterface.h"
#include "TafApsComFunc.h"
#include "TafApsFsmMainTbl.h"
#include "TafApsCtx.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-25, begin */
#include "ehsm_aps_pif.h"
/* Added by y00314741 for CDMA Iteration 15, 2015-5-25, end */


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*lint -e958*/

/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_TAF_APS_SND_CDS_C


/*****************************************************************************
  2 全局变量定义
*****************************************************************************/


/*****************************************************************************
  3 函数实现
*****************************************************************************/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)


VOS_VOID TAF_APS_SndCdsSndBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *pstSndBuffData = VOS_NULL_PTR;

    pstSndBuffData = (APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_SEND_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstSndBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsSndBuffDataInd: Memory alloc failed");
        return;
    }

    pstSndBuffData->ulReceiverPid       = UEPS_PID_CDS;
    pstSndBuffData->enMsgId             = ID_APS_CDS_CDATA_SEND_BUFF_DATA_IND;
    pstSndBuffData->usOpId              = 0;
    pstSndBuffData->ucRabId             = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndBuffData);

    return;
}


VOS_VOID TAF_APS_SndCdsFreeBuffDataInd(
    VOS_UINT8                           ucRabId
)
{
    APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *pstFreeBuffData = VOS_NULL_PTR;

    pstFreeBuffData = (APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_CDATA_FREE_BUFF_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstFreeBuffData)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsFreeBuffDataInd: Memory alloc failed");
        return;
    }

    pstFreeBuffData->ulReceiverPid      = UEPS_PID_CDS;
    pstFreeBuffData->enMsgId            = ID_APS_CDS_CDATA_FREE_BUFF_DATA_IND;
    pstFreeBuffData->usOpId             = 0;
    pstFreeBuffData->ucRabId            = ucRabId;

    PS_SEND_MSG(WUEPS_PID_TAF, pstFreeBuffData);

    return;
}



VOS_VOID TAF_APS_SndCdsModeChangeInd(
    TAF_APS_RAT_TYPE_ENUM_UINT32        enCurrCdataServiceMode
)
{
    APS_CDS_MODE_CHANGE_IND_STRU       *pstSndMsg = VOS_NULL_PTR;
    APS_CDS_MODE_ENUM_UINT32            enMode;

    switch (enCurrCdataServiceMode)
    {
        case TAF_APS_RAT_TYPE_1X:
            enMode = APS_CDS_MODE_1X;
            break;
        case TAF_APS_RAT_TYPE_HRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        case TAF_APS_RAT_TYPE_EHRPD:
            enMode = APS_CDS_MODE_EVDO;
            break;
        default:
            TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Mode Error");
            return;
    }

    pstSndMsg = (APS_CDS_MODE_CHANGE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_TAF,
                            sizeof(APS_CDS_MODE_CHANGE_IND_STRU));

    if (VOS_NULL_PTR == pstSndMsg)
    {
        TAF_ERROR_LOG(WUEPS_PID_TAF, "TAF_APS_SndCdsModeChangeInd: Memory alloc failed");
        return;
    }

    pstSndMsg->ulReceiverPid    = UEPS_PID_CDS;
    pstSndMsg->enMsgId          = ID_APS_CDS_MODE_CHANGE_IND;
    pstSndMsg->usOpId           = 0;
    pstSndMsg->enMode           = enMode;

    PS_SEND_MSG(WUEPS_PID_TAF, pstSndMsg);

    return;

}



APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8 TAF_APS_GetCdataBearStatus(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                                               ucPdpId;
    VOS_UINT32                                              ulState;
    APS_CDS_CDATA_BEAR_STATUS_ENUM_UINT8                    enBearStatus;
    TAF_APS_TIMER_STATUS_ENUM_U8                            enTimerStatus;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_CDATA_BEAR_STATUS_INACTIVE;
    }

    /* 如果当前Dormant timer正在运行，或者PS业务被挂起(TCH通道被其它业务占用)
       则当前状态为SUSPEND状态，不可以数传，目前不支持辅助业务(SO=66)，以后支持辅助业务时，
       再区分是否存在辅助业务 */

    enTimerStatus = TAF_APS_GetTimerStatus(TI_TAF_APS_CDATA_DORMANT, ucPdpId);

    /* 语音或者短信在重拨时，为了语音业务优先，不可以触发建链 */
    if ((VOS_TRUE == TAF_APS_IsExistXcallOrXsmsOpreation())
     || (TAF_APS_CDMA_TC_SUSPENDED == TAF_APS_GET_CDATA_SUSPEND_STATUS())
     || (TAF_APS_TIMER_STATUS_RUNING == enTimerStatus))
    {
        return APS_CDS_CDATA_BEAR_STATUS_SUSPEND;
    }


    /* Added by y00314741 for CDMA Iteration 15, 2015-5-25, begin */
    if (TAF_APS_RAT_TYPE_EHRPD  == TAF_APS_GetCurrPdpEntityDataServiceMode())
    {
         enBearStatus = TAF_APS_GetCdataEhrpdSvcSta(ucPdpId);

         return enBearStatus;
    }
    /* Added by y00314741 for CDMA Iteration 15, 2015-5-25, end */

    ulState = TAF_APS_GetPdpIdMainFsmState(ucPdpId);

    if (TAF_APS_STA_INACTIVE == ulState)
    {
        return APS_CDS_CDATA_BEAR_STATUS_INACTIVE;
    }
    else if (TAF_APS_STA_ACTIVE == ulState)
    {
        return APS_CDS_CDATA_BEAR_STATUS_ACTIVE;
    }
    else if (TAF_APS_STA_CDATA_ESTING  == ulState)
    {
        return APS_CDS_CDATA_BEAR_STATUS_SUSPEND;
    }
    else if (TAF_APS_STA_CDATA_DISCING  == ulState)
    {
        return APS_CDS_CDATA_BEAR_STATUS_SUSPEND;
    }
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-9, begin */
    else if (TAF_APS_STA_CDATA_HANDOFF  == ulState)
    {
        return APS_CDS_CDATA_BEAR_STATUS_SUSPEND;
    }
    /* Added by y00314741 for CDMA Iteration 11, 2015-4-9, end */
    else if (TAF_APS_STA_DORMANT == ulState)
    {
        return APS_CDS_CDATA_BEAR_STATUS_IDLE;
    }
    else
    {
        /* 多模互操作时，有可能其它模式存在，正在建立链接 */
        return APS_CDS_CDATA_BEAR_STATUS_SUSPEND;
    }

}



VOS_UINT8 TAF_APS_MapRabIdToPdnId(
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByNsapi(ucRabId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_PDN_ID;
    }

    return TAF_APS_GetPdpEntCdataPdnId(ucPdpId);
}


VOS_UINT8 TAF_APS_MapPdnIdToRabId(
    VOS_UINT8                           ucPdnId
)
{
    VOS_UINT8                           ucPdpId;

    ucPdpId = TAF_APS_GetPdpIdByPndId(ucPdnId);
    if (TAF_APS_INVALID_PDPID == ucPdpId)
    {
        return APS_CDS_INVALID_RAB_ID;
    }

    return TAF_APS_GetPdpEntNsapi(ucPdpId);
}

#endif

/*lint +e958*/

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


