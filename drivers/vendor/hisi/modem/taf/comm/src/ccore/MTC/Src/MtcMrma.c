

/*****************************************************************************
  1 ͷ�ļ�����
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
  2 ȫ�ֱ�������
*****************************************************************************/

/*****************************************************************************
  3 ��������
*****************************************************************************/

VOS_VOID MTC_SndRcmModemStateInd(VOS_VOID)
{
    MTC_RCM_MODEM_STATE_NOTIFY_STRU    *pstModemState;
    MODEM_ID_ENUM_UINT16                enModemId;
    TAF_MTC_SRV_CONN_STATE_ENUM_UINT8   enCsSrvStatus;

    /* ������Ϣ�� */
    pstModemState = (MTC_RCM_MODEM_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstModemState)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemStateInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstModemState) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_MODEM_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    MTC_CFG_RCM_MSG_HDR(&pstModemState->stMsgHeader, ID_MTC_RCM_MODEM_STATUS_NOTIFY);

    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, begin */
    /* ��д��modem��״̬��Ϣ */
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

    /* ��дCDMA״̬��Ϣ */
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enCsSrvConnState   = MTC_GetOutSideCsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enPsSrvConnState   = MTC_GetOutSidePsConnStateInfo(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemPowerState  = MTC_GetOutSideModemPowerState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enUsimmCardState   = MTC_GetOutSideModemUsimmState(MTC_OUTSIDE_MODEM_CDMA);
    pstModemState->astModemState[MTC_RCM_MODEM_OTHER].enModemType        = MTC_RCM_MODEM_OTHER;
    /* Modified by zwx247453 for K3V3 3 modem TAS, 2015-07-20, end */

    /* ������Ϣ */
    MTC_SEND_MSG(pstModemState);

    return;
}
VOS_VOID MTC_SndImsaModem1InfoInd(VOS_VOID)
{
    MTC_IMSA_MODEM1_INFO_IND_STRU      *pstModem1Info = VOS_NULL_PTR;

    /* IMSAû��Start����Ҫ����Ϣ */
    if (MTC_MODEM_POWER_ON != MTC_GetModemImsaState(MODEM_ID_0))
    {
        return;
    }

    /* ������Ϣ�� */
    pstModem1Info = (MTC_IMSA_MODEM1_INFO_IND_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_IMSA_MODEM1_INFO_IND_STRU));
    if (VOS_NULL_PTR == pstModem1Info)
    {
        MTC_ERROR_LOG("MTC_SndImsaModem1InfoInd: Alloc Msg Fail!");
        return;
    }

    /* �����Ϣ���� */
    PS_MEM_SET(MTC_GET_MSG_ENTITY(pstModem1Info), 0x00, MTC_GET_MSG_LENGTH(pstModem1Info));

    /* �����Ϣͷ */
    MTC_CFG_IMSA_MSG_HDR(pstModem1Info, ID_MTC_IMSA_MODEM1_INFO_IND);

    /* ��дModem1����Ϣ */
    pstModem1Info->enPowerState = MTC_GetModemPowerState(MODEM_ID_1);

    /* ������Ϣ */
    MTC_SEND_MSG(pstModem1Info);

    return;
}

/*****************************************************************************
 �� �� ��  : MTC_SndRcmModemImsVoiceCapInd
 ��������  : MTCģ��֪ͨRCM IMS���ػ�״̬��IMS��������״̬
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��06��17��
    ��    ��   : w00316404
    �޸�����   : NEXT Band26��Ŀ
*****************************************************************************/
VOS_VOID MTC_SndRcmModemImsVoiceCapInd(VOS_VOID)
{
    MTC_RCM_IMS_STATE_NOTIFY_STRU              *pstImsStateNotify   = VOS_NULL_PTR;

    /* ������Ϣ�� */
    pstImsStateNotify = (MTC_RCM_IMS_STATE_NOTIFY_STRU *)MTC_ALLOC_MSG_WITH_HDR(sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU));
    if (VOS_NULL_PTR == pstImsStateNotify)
    {
        MTC_ERROR_LOG("MTC_SndRcmModemImsVoiceCapInd: Alloc Msg Fail!");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstImsStateNotify) + VOS_MSG_HEAD_LENGTH, 0, sizeof(MTC_RCM_IMS_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* �����Ϣͷ */
    MTC_CFG_RCM_MSG_HDR(pstImsStateNotify, ID_MTC_RCM_IMS_STATUS_NOTIFY);

    /* �����Ϣ */
    pstImsStateNotify->enIMSPowerState      = MTC_GetModemImsaState(MODEM_ID_0);
    pstImsStateNotify->enIMSVoiceCapState   = MTC_GetModemImsVoiceCap(MODEM_ID_0);

    /* ������Ϣ */
    MTC_SEND_MSG(pstImsStateNotify);

    return;
}


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

