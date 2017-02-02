

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "MtcRcmInterface.h"
#include "ImsaMtcInterface.h"
#include "MtcCtx.h"
#include "MtcDebug.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define    THIS_FILE_ID        PS_FILE_ID_MTC_MRMA_C

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

/*****************************************************************************
  3 函数定义
*****************************************************************************/

VOS_VOID MTC_SndRcmModemStateInd(VOS_VOID)
{
    MTC_RCM_MODEM_STATE_NOTIFY_STRU    *pstModemState;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;

    /* 申请消息包 */
    pstModemState = (MTC_RCM_MODEM_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstModemState)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemStateInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstModemState) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    MTC_CFG_RCM_MSG_HDR(&pstModemState->stMsgHeader, ID_MTC_RCM_MODEM_STATUS_NOTIFY);

    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */
    /* 填写各modem的状态信息 */
    for (enModemId = 0; enModemId < MODEM_ID_BUTT ; enModemId++)
    {
        pstModemState->astModemState[enModemId].enPsSrvConnState        = MTC_GetPsSrvState(enModemId);
        pstModemState->astModemState[enModemId].enModemPowerState       = MTC_GetModemPowerState(enModemId);
        pstModemState->astModemState[enModemId].enUsimmCardState        = MTC_GetUsimmStateInfo(enModemId);
        pstModemState->astModemState[enModemId].enModemType             = MTC_RCM_MODEM_0 + enModemId;
        enCsSrvStatus                                                    = MTC_GetCsSrvState(enModemId);;

        if ( (PS_TRUE           == MTC_IsCsSessionInfoExit(enModemId))
          || (TAF_MTC_SRV_EXIST == enCsSrvStatus) )
        {
            pstModemState->astModemState[enModemId].enCsSrvConnState        = TAF_MTC_SRV_EXIST;
        }
        else
        {
            pstModemState->astModemState[enModemId].enCsSrvConnState        = TAF_MTC_SRV_NO_EXIST;
        }
    }

    /* 填写CDMA状态信息 */
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enCsSrvConnState   = MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enPsSrvConnState   = MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemPowerState  = MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enUsimmCardState   = MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemType        = MTC_RCM_MODEM_OTHER;
    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */

    /* 发送消息 */
    MTC_SEND_MSG(pstModemState);

    return;
}
VOS_VOID MTC_SndImsaModem1InfoInd(VOS_VOID)
{
    MTC_IMSA_MODEM1_INFO_IND_STRU      *pstModem1Info = VOS_NULL_PTR;

    /* IMSA没有Start则不需要发消息 */
    if (MTC_MODEM_POWER_ON != MTC_GetModemImsaState(MODEM_ID_0))
    {
        return;
    }

    /* 申请消息包 */
    pstModem1Info = (MTC_IMSA_MODEM1_INFO_IND_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_IMSA_MODEM1_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstModem1Info)
    {
        MTC_ERROR_LOG("MTC_SndImsaModem1InfoInd: Alloc Msg Fail!");
        return;
    }

    /* 清空消息内容 */
    PS_MEM_SET(MTC_GET_MSG_ENTITY(pstModem1Info), 0x00, MTC_GET_MSG_LENGTH(pstModem1Info));

    /* 填充消息头 */
    MTC_CFG_IMSA_MSG_HDR(pstModem1Info, ID_MTC_IMSA_MODEM1_INFO_IND);

    /* 填写Modem1的信息 */
    pstModem1Info->enPowerState = MTC_GetModemPowerState(MODEM_ID_1);

    /* 发送消息 */
    MTC_SEND_MSG(pstModem1Info);

    return;
}

/*****************************************************************************
 函 数 名  : MTC_SndRcmModemImsVoiceCapInd
 功能描述  : MTC模块通知RCM IMS开关机状态和IMS语音可用状态
 输入参数  : VOS_VOID
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月17日
    作    者   : w00316404
    修改内容   : NEXT Band26项目
*****************************************************************************/
VOS_VOID MTC_SndRcmModemImsVoiceCapInd(VOS_VOID)
{
    MTC_RCM_IMS_STATE_NOTIFY_STRU              *pstImsStateNotify   = VOS_NULL_PTR;

    /* 申请消息包 */
    pstImsStateNotify = (MTC_RCM_IMS_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstImsStateNotify)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemImsVoiceCapInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstImsStateNotify) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* 填充消息头 */
    MTC_CFG_RCM_MSG_HDR(pstImsStateNotify, ID_MTC_RCM_IMS_STATUS_NOTIFY);

    /* 填充消息 */
    pstImsStateNotify->enIMSPowerState      = MTC_GetModemImsaState(MODEM_ID_0);
    pstImsStateNotify->enIMSVoiceCapState   = MTC_GetModemImsVoiceCap(MODEM_ID_0);

    /* 发送消息 */
    MTC_SEND_MSG(pstImsStateNotify);

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

