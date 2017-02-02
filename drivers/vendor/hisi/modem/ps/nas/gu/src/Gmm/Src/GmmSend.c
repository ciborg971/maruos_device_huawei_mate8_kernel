

#include "GmmInc.h"
#include "GmmCasGlobal.h"
#include "GmmCasComm.h"
#include "GmmCasSend.h"
#include "NasComm.h"
#include "NasCommDef.h"
#include "GmmMmInterface.h"
#include "NasMmlMsgProc.h"
#include "NasMmlCtx.h"
#include "GmmExt.h"
#include "NasUtranCtrlInterface.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"
#include "NasUsimmApi.h"

#ifdef  __cplusplus
  #if  __cplusplus
  extern "C"{
  #endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_GMM_SEND_C



/*lint -save -e958 */

#if (FEATURE_LTE == FEATURE_ON)

VOS_VOID NAS_GMM_SndLmmReselSecuInfoReq( VOS_VOID )
{
    GMM_LMM_RESEL_SECU_INFO_REQ_STRU   *pstReselSecuInfoReq;

#if (VOS_WIN32 == VOS_OS_VER)
    /* �����ڴ�  */
    pstReselSecuInfoReq                 = (GMM_LMM_RESEL_SECU_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                                            sizeof(GMM_LMM_RESEL_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstReselSecuInfoReq = (GMM_LMM_RESEL_SECU_INFO_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_RESEL_SECU_INFO_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstReselSecuInfoReq )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmReselSecuInfoReq:�����ڴ�ʧ��");
        return ;
    }

    pstReselSecuInfoReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstReselSecuInfoReq->ulSenderCpuId  = VOS_LOCAL_CPUID;
    pstReselSecuInfoReq->ulSenderPid    = WUEPS_PID_GMM;
    pstReselSecuInfoReq->ulReceiverPid  = PS_PID_MM;
    pstReselSecuInfoReq->ulMsgId        = ID_GMM_LMM_RESEL_SECU_INFO_REQ;
    pstReselSecuInfoReq->ulLength       = sizeof(GMM_LMM_RESEL_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ulOpId��ulTransceiverTypeĿǰ��ʹ�� */
    pstReselSecuInfoReq->ulOpId         = 0;
    pstReselSecuInfoReq->aucRsv[0]      = 0;
    pstReselSecuInfoReq->aucRsv[1]      = 0;
    pstReselSecuInfoReq->aucRsv[2]      = 0;
    pstReselSecuInfoReq->aucRsv[3]      = 0;

    /* lkh00167671 memset */
#if (VOS_WIN32 == VOS_OS_VER)
    /* ����VOS����ԭ�� */
    PS_SEND_MSG(WUEPS_PID_GMM, pstReselSecuInfoReq);
#else
    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstReselSecuInfoReq);
#endif

    return ;
}
VOS_VOID NAS_GMM_SndLmmHoSecuInfoReq( VOS_VOID )
{
    GMM_LMM_HO_SECU_INFO_REQ_STRU      *pstHoSecuInfoReq;

#if (VOS_WIN32 == VOS_OS_VER)
    /* �����ڴ�  */
    pstHoSecuInfoReq = (GMM_LMM_HO_SECU_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_MMC,
                                                            (sizeof(GMM_LMM_HO_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH));
#else
    pstHoSecuInfoReq = (GMM_LMM_HO_SECU_INFO_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_HO_SECU_INFO_REQ_STRU));
#endif

    if( VOS_NULL_PTR == pstHoSecuInfoReq )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmReselSecuInfoReq:�����ڴ�ʧ��");
        return ;
    }

    pstHoSecuInfoReq->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstHoSecuInfoReq->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstHoSecuInfoReq->ulSenderPid       = WUEPS_PID_GMM;
    pstHoSecuInfoReq->ulReceiverPid     = PS_PID_MM;
    pstHoSecuInfoReq->ulMsgId           = ID_GMM_LMM_HO_SECU_INFO_REQ;
    pstHoSecuInfoReq->ulLength          = sizeof(GMM_LMM_HO_SECU_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ulOpId��ulTransceiverTypeĿǰ��ʹ�� */
    pstHoSecuInfoReq->ulOpId            = 0;
    pstHoSecuInfoReq->aucRsv[0]         = 0;
    pstHoSecuInfoReq->aucRsv[1]         = 0;
    pstHoSecuInfoReq->aucRsv[2]         = 0;
    pstHoSecuInfoReq->aucRsv[3]         = 0;

#if (VOS_WIN32 == VOS_OS_VER)
    /* ����VOS����ԭ�� */
    PS_SEND_MSG(WUEPS_PID_GMM, pstHoSecuInfoReq );

#else
    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstHoSecuInfoReq);
#endif

    return ;

}

VOS_VOID NAS_GMM_SndLmmInfoChangeNotifyReq(
    NAS_MML_NET_RAT_TYPE_ENUM_UINT8     enRat,
    VOS_UINT8                           bitOpConnState,
    VOS_UINT8                           bitOpGprsSuspend,
    VOS_UINT8                           ucSrvState,
    VOS_UINT32                          ulGprsSuspendFlg
)
{
    GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU                    *pstInfoChange = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* ������Ϣ��  */
    pstInfoChange = (GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                                       (sizeof(GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH));
#else
    pstInfoChange = (GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU));
#endif

    if (VOS_NULL_PTR == pstInfoChange)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmInfoChangeNotifyReq:������Ϣ�ڴ�ʧ��");

        return ;
    }

    /* ��Ϣͷ���  */
    pstInfoChange->ulReceiverCpuId          = VOS_LOCAL_CPUID;
    pstInfoChange->ulReceiverPid            = PS_PID_MM;

    pstInfoChange->ulSenderPid              = WUEPS_PID_GMM;
    pstInfoChange->ulSenderCpuId            = VOS_LOCAL_CPUID;

    pstInfoChange->ulMsgId                  = ID_GMM_LMM_INFO_CHANGE_NOTIFY_REQ;
    pstInfoChange->ulOpId                   = 0;
    pstInfoChange->ulLength                 = sizeof(GMM_LMM_INFO_CHANGE_NOTIFY_REQ_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��ʼ��Op�� */
    pstInfoChange->bitOpGprsMmState         = VOS_FALSE;
    pstInfoChange->bitOpPacketMmState       = VOS_FALSE;
    pstInfoChange->bitOpGprsSuspensionState = VOS_FALSE;
    pstInfoChange->bitSpare                 = VOS_FALSE;

    /* �����ǰ���뼼��Ϊ2G */
    if (NAS_MML_NET_RAT_TYPE_GSM == enRat)
    {
        pstInfoChange->bitOpGprsMmState         = bitOpConnState;
        pstInfoChange->bitOpGprsSuspensionState = bitOpGprsSuspend;

        /* ����ucSrvState���enGConnState */
        if (GMM_AGB_GPRS_READY == ucSrvState)
        {
            pstInfoChange->enGprsMmState = GMM_LMM_GPRS_MM_STATE_READY;
        }
        else if (GMM_AGB_GPRS_STANDBY == ucSrvState)
        {
            pstInfoChange->enGprsMmState = GMM_LMM_GPRS_MM_STATE_STANDBY;
        }
        else
        {
            pstInfoChange->enGprsMmState = GMM_LMM_GPRS_MM_STATE_IDLE;
        }

        /* ����ulGprsSuspendFlg���enPsState */
        pstInfoChange->enGprsSuspensionState      = GMM_LMM_GPRS_NOT_SUSPENSION;
        if (VOS_TRUE == ulGprsSuspendFlg)
        {
            pstInfoChange->enGprsSuspensionState  = GMM_LMM_GPRS_SUSPENSION;
        }

        pstInfoChange->enPacketMmState            = GMM_LMM_PACKET_MM_STATE_BUTT;
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == enRat)
    {
        pstInfoChange->bitOpPacketMmState = bitOpConnState;

        /* ����ucSrvState���enUConnState */
        if (GMM_IU_PMM_CONNECTED == ucSrvState)
        {
            pstInfoChange->enPacketMmState        = GMM_LMM_PACKET_MM_STATE_PMM_CONNECTED;
        }
        else if (GMM_IU_PMM_IDLE == ucSrvState)
        {
            pstInfoChange->enPacketMmState        = GMM_LMM_PACKET_MM_STATE_PMM_IDLE;
        }
        else
        {
            pstInfoChange->enPacketMmState        = GMM_LMM_PACKET_MM_STATE_PMM_DETACH;
        }

        pstInfoChange->enGprsMmState              = GMM_LMM_GPRS_MM_STATE_BUTT;
        pstInfoChange->enGprsSuspensionState      = GMM_LMM_GPRS_SUSPENSION_BUTT;
    }
    else
    {
        /* warning�����ӡ */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmInfoChangeNotifyReq:���뼼������ȷ");
    }

#if (VOS_WIN32 == VOS_OS_VER)
    /* ����VOS����ԭ�� */
    PS_SEND_MSG(WUEPS_PID_GMM, pstInfoChange );
#else
    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstInfoChange);
#endif

    return ;
}


VOS_VOID NAS_GMM_SndLmmTimerInfoNotify(
   VOS_UINT8                            ucTimerId,
   GMM_LMM_TIMER_STATE_ENUM_UINT32      enTimerInfo
)
{
    /* ��GMM_LMM_TIMER_STATE_NOTIFY_STRU�ṹ��װ��Ϣ���͸�LMM */
    GMM_LMM_TIMER_STATE_NOTIFY_STRU    *pstTimerStatusNotify;

#if (VOS_WIN32 == VOS_OS_VER)
    /* �����ڴ�  */
    pstTimerStatusNotify = (GMM_LMM_TIMER_STATE_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                               sizeof(GMM_LMM_TIMER_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstTimerStatusNotify = (GMM_LMM_TIMER_STATE_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_TIMER_STATE_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstTimerStatusNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmTimerInfoNotify:�����ڴ�ʧ��");
        return ;
    }

    pstTimerStatusNotify->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstTimerStatusNotify->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstTimerStatusNotify->ulSenderPid     = WUEPS_PID_GMM;
    pstTimerStatusNotify->ulReceiverPid   = PS_PID_MM;
    pstTimerStatusNotify->ulMsgId         = ID_GMM_LMM_TIMER_STATE_NOTIFY;
    pstTimerStatusNotify->ulLength        = sizeof(GMM_LMM_TIMER_STATE_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;

    /* ��ʼ��Op�� */
    pstTimerStatusNotify->bitOpT3312      = VOS_FALSE;
    pstTimerStatusNotify->bitOpRsv        = VOS_FALSE;

    if (GMM_TIMER_T3312 == ucTimerId)
    {
        pstTimerStatusNotify->bitOpT3312    = VOS_TRUE;
        pstTimerStatusNotify->enT3312State  = enTimerInfo;
    }
    pstTimerStatusNotify->ulOpId            = 0;

#if (VOS_WIN32 == VOS_OS_VER)
    /* ����VOS����ԭ�� */
    PS_SEND_MSG(WUEPS_PID_GMM, pstTimerStatusNotify);
#else
    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstTimerStatusNotify);
#endif
    return;
}


#if(FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_GMM_ConvertRrcSessionTypeToLmmFormat(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType,
    GMM_LMM_SESSION_TYPE_ENUM_UINT8    *puclmmSessionType
)
{
    switch (enRrcSessionType)
    {
        case RRC_NAS_SESSION_TYPE_PS_MO_SMS:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_MO_SMS;
            break;

        case RRC_NAS_SESSION_TYPE_PS_MT_SMS:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_MT_SMS;
            break;

        case RRC_NAS_SESSION_TYPE_PS_ATTACH:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_ATTACH;
            break;

        case RRC_NAS_SESSION_TYPE_PS_RAU:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_RAU;
            break;

        case RRC_NAS_SESSION_TYPE_PS_DETACH:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_DETACH;
            break;

        case RRC_NAS_SESSION_TYPE_PS_CONVERSAT_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_CONVERSAT_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_STREAM_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_STREAM_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_INTERACT_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_INTERACT_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_BACKGROUND_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_BACKGROUND_CALL;
            break;

        case RRC_NAS_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_PS_SUBSCRIB_TRAFFIC_CALL;
            break;

        default:
            *puclmmSessionType = GMM_LMM_SESSION_TYPE_BUTT;
            break;
    }
    return;
}


VOS_VOID NAS_GMM_SndLmmBeginSessionNotify(
   GMM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    GMM_LMM_BEGIN_SESSION_NOTIFY_STRU  *pstBeginSessionNotify = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* �����ڴ�  */
    pstBeginSessionNotify = (GMM_LMM_BEGIN_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                               sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstBeginSessionNotify = (GMM_LMM_BEGIN_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstBeginSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmBeginSessionNotify:�����ڴ�ʧ��");
        return ;
    }

    PS_MEM_SET((VOS_UINT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00,
                    sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ������Ϣ�ṹ�� */
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstBeginSessionNotify->stMsgHeader.ulLength        = sizeof(GMM_LMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstBeginSessionNotify->stMsgHeader.ulMsgName       = ID_GMM_LMM_BEGIN_SESSION_NOTIFY;

    pstBeginSessionNotify->enSessionType               = enSessionType;

#if (VOS_WIN32 == VOS_OS_VER)
    /* ����VOS����ԭ�� */
    PS_SEND_MSG(WUEPS_PID_GMM, pstBeginSessionNotify);
#else
    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstBeginSessionNotify);
#endif

    return;
}


VOS_VOID NAS_GMM_SndLmmEndSessionNotify(
   GMM_LMM_SESSION_TYPE_ENUM_UINT8      enSessionType
)
{
    GMM_LMM_END_SESSION_NOTIFY_STRU    *pstEndSessionNotify = VOS_NULL_PTR;

#if (VOS_WIN32 == VOS_OS_VER)
    /* �����ڴ�  */
    pstEndSessionNotify = (GMM_LMM_END_SESSION_NOTIFY_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                               sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
#else
    pstEndSessionNotify = (GMM_LMM_END_SESSION_NOTIFY_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU));
#endif

    if( VOS_NULL_PTR == pstEndSessionNotify )
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndLmmEndSessionNotify:�����ڴ�ʧ��");
        return ;
    }

    PS_MEM_SET((VOS_UINT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0x00,
                        sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ������Ϣ�ṹ�� */
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid   = PS_PID_MM;
    pstEndSessionNotify->stMsgHeader.ulLength        = sizeof(GMM_LMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH;
    pstEndSessionNotify->stMsgHeader.ulMsgName       = ID_GMM_LMM_END_SESSION_NOTIFY;

    pstEndSessionNotify->enSessionType               = enSessionType;

#if (VOS_WIN32 == VOS_OS_VER)
    /* ����VOS����ԭ�� */
    PS_SEND_MSG(WUEPS_PID_GMM, pstEndSessionNotify);
#else
    /* �ڲ���Ϣ�ķ��� */
    NAS_MML_SndInternalMsg(pstEndSessionNotify);
#endif

    return;
}


#endif

#endif

VOS_VOID NAS_GMM_SndMmcNetworkCapabilityInfoInd(
    GMM_MMC_NW_EMC_BS_CAP_ENUM_UINT8    enNwEmcBS,
    NAS_MML_NW_IMS_VOICE_CAP_ENUM_UINT8 enNwImsVoPS,
    GMM_MMC_LTE_CS_CAPBILITY_ENUM_UINT8 enLteCsCap
)
{
    GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU                *pstMmcMsg = VOS_NULL_PTR;

    pstMmcMsg = (GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU *)NAS_MML_GetIntMsgSendBuf(
        sizeof(GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU));

    if (VOS_NULL_PTR == pstMmcMsg)
    {
        /* print error information */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcNetworkCapabilityInfoInd: memory allocation is failure!");

        return ;
    }

    PS_MEM_SET(pstMmcMsg, 0, sizeof(GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU));

    /* set message header */
    pstMmcMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMmcMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_MMC;
    pstMmcMsg->MsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMmcMsg->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMmcMsg->MsgHeader.ulMsgName       = GMMMMC_NETWORK_CAPABILITY_INFO_IND;
    pstMmcMsg->MsgHeader.ulLength        = sizeof(GMMMMC_NETWORK_CAPABILITY_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMmcMsg->enNwEmcBsCap              = enNwEmcBS;
    pstMmcMsg->enNwImsVoCap              = enNwImsVoPS;
    pstMmcMsg->enLteCsCap                = enLteCsCap;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMmcMsg);
}

VOS_VOID GMM_ReportM2NOtaMsg(NAS_MSG_STRU *pNasMsg)
{
    NAS_OTA_MSG_ID_ENUM_UINT16 usNasOtaMsyId = NAS_OTA_MSG_ID_BUTT;

    PS_NAS_LOG1(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_NORMAL, "GMM_ReportM2NOtaMsg:NORMAL: msg id is", pNasMsg->aucNasMsg[1]);

    if (GMM_PD_GMM != (pNasMsg->aucNasMsg[0] & 0x0f))
    {
        return;
    }

    switch(pNasMsg->aucNasMsg[1])
    {
        case GMM_MSG_ATTACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_REQ;
            break;

        case GMM_MSG_ATTACH_COMPLETE:
            usNasOtaMsyId = NAS_OTA_MSG_ATTACH_COMPLETE;
            break;

        case GMM_MSG_DETACH_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_REQ;
            break;

        case GMM_MSG_DETACH_ACCEPT:
            usNasOtaMsyId = NAS_OTA_MSG_DETACH_ACCEPT_BY_MS;
            break;

        case GMM_MSG_RAU_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_REQ;
            break;

        case GMM_MSG_RAU_COMPLETE:
            usNasOtaMsyId = NAS_OTA_MSG_RAU_COMPLETE;
            break;

        case GMM_MSG_SERVICE_REQUEST:
            usNasOtaMsyId = NAS_OTA_MSG_DATA_SERVICE_REQ;
            break;

        case GMM_MSG_P_TMSI_REALLOCATION_COMPLETE:
            usNasOtaMsyId = NAS_OTA_MSG_P_TMSI_REALLOCATION_COMPLETE;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_RESPONSE:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_RESPONSE;
            break;

        case GMM_MSG_AUTHENTICATION_AND_CIPHERING_FAILURE:
            usNasOtaMsyId = NAS_OTA_MSG_AUTH_AND_CIPHER_FAIL;
            break;

        case GMM_MSG_IDENTITY_RESPONSE:
            usNasOtaMsyId = NAS_OTA_MSG_IDENTITY_RESPONSE;
            break;

        case GMM_MSG_GMM_STATUS:
            usNasOtaMsyId = NAS_OTA_MSG_GMM_STATUS_BY_MS;
            break;

        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_ReportM2NOtaMsg:WARNING: invalid msg id");
            /*������GMMģ��Ŀտ���Ϣ������trace����ʾ*/
            return;
    }

    NAS_SendAirMsgToOM(WUEPS_PID_GMM, usNasOtaMsyId, NAS_OTA_DIRECTION_UP, pNasMsg->ulNasMsgSize + 4, (VOS_UINT8*)pNasMsg);
}

/*******************************************************************************
  Module   : Gmm_SndMmcNetworkDetachInd
  Function : MMCGMM_NETWORK_DETACH_INDԭ����д������
  Input    : VOS_UINT8      ucDetachType           detach����
             VOS_UINT8      ucDetachCause          detachԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.08  �¹�����

*******************************************************************************/
VOS_VOID Gmm_SndMmcNetworkDetachInd(
                                VOS_UINT8 ucDetachType,                             /* detach����                               */
                                VOS_UINT8 ucDetachCause                             /* detachԭ��                               */
                                )
{
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstMsg          = VOS_NULL_PTR;
    MMCGMM_NETWORK_DETACH_IND_STRU     *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_NETWORK_DETACH_IND_STRU);

    pstInternalMsg  = (MMCGMM_NETWORK_DETACH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcNetworkDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_NETWORK_DETACH_IND;
    pstMsg->ulDetachType   = ucDetachType;                                        /* ��дdetach����                           */
    pstMsg->ulDetachCause  = ucDetachCause;                                       /* ��дdetachԭ��                           */

    if (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR != ucDetachCause)
    {                                                                           /* ԭ��ֵ��Ϊ#2                             */
        pstMsg->ulServiceSts   = Gmm_ComServiceSts();                             /* ��д����״̬                             */
    }
    else
    {
        pstMsg->ulServiceSts   = 0x0;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
VOS_VOID NAS_GMM_SndMmcAttachCnf(VOS_VOID)
{
    MMCGMM_ATTACH_CNF_STRU             *pstMsg          = VOS_NULL_PTR;
    MMCGMM_ATTACH_CNF_STRU             *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_ATTACH_CNF_STRU);

    pstInternalMsg  = (MMCGMM_ATTACH_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcAttachCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_ATTACH_CNF;
    pstMsg->ulOpid                        = g_GmmGlobalCtrl.stAttachInfo.ulOpid;
    pstMsg->ulServiceStatus               = Gmm_ComServiceSts();

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
VOS_VOID NAS_GMM_SndMmcDetachCnf(VOS_VOID)
{
    MMCGMM_DETACH_CNF_STRU             *pstMsg          = VOS_NULL_PTR;
    MMCGMM_DETACH_CNF_STRU             *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_DETACH_CNF_STRU);

    pstInternalMsg  = (MMCGMM_DETACH_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcDetachCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_DETACH_CNF;
    pstMsg->ulOpid                        = g_GmmGlobalCtrl.stDetachInfo.ulOpid;
    pstMsg->ulServiceSts                  = Gmm_ComServiceSts();

    pstMsg->ulDetachType                  = g_GmmGlobalCtrl.stDetachInfo.enDetachType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    if (MM_COM_SRVST_NORMAL_SERVICE != pstMsg->ulServiceSts)
    {
        NAS_EventReport(WUEPS_PID_GMM,
                        NAS_OM_EVENT_DETACH_FINISH,
                        VOS_NULL_PTR,
                        NAS_OM_EVENT_NO_PARA);
    }

    /* ����������ñ��� */
    g_GmmDetachCtrl.ucSysCfgDetachFlg = VOS_FALSE;

    return;
}


VOS_VOID Gmm_SndMmcPowerOffCnf(VOS_VOID)
{
    MMCGMM_POWER_OFF_CNF_STRU          *pstMsg          = VOS_NULL_PTR;
    MMCGMM_POWER_OFF_CNF_STRU          *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_POWER_OFF_CNF_STRU);

    pstInternalMsg  = (MMCGMM_POWER_OFF_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcPowerOffCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_POWER_OFF_CNF;
    /*A32D11737==>�ػ�����Ҫȥָ��LLC*/
    if (GMM_TRUE == gstGmmCasGlobalCtrl.ucTlliAssignFlg)
    {
        NAS_GMM_FreeTlliForPowerOff();
    }

    Gmm_TimerStop( GMM_TIMER_ALL );

    /* GMM_TIMER_1S���뵥��ͣ����GMM_TIMER_ALL����ֹͣ�ػ�������ʱ�� */
    Gmm_TimerStop( GMM_TIMER_1S );
    g_GmmGlobalCtrl.stPowerOffCtrl.ucSndDetachCnt = 0;

    gucGmmInitState = NAS_GMM_CTRL_STATUS_STARTUP;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
VOS_VOID Gmm_SndMmcInfoInd(NAS_MM_INFO_IND_STRU    *pstMmInfo)
{
    MMCGMM_INFO_IND_STRU               *pstMsg          = VOS_NULL_PTR;
    MMCGMM_INFO_IND_STRU               *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                           ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_INFO_IND_STRU);

    pstInternalMsg  = (MMCGMM_INFO_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcInfoInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_INFO_IND;
    pstMsg->stMmInfo                      = *pstMmInfo;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

VOS_VOID Gmm_SndMmcPdpStatusInd(
                            VOS_UINT8 ucPdpStatusFlg
                            )

{
    MMCGMM_PDP_STATUS_IND_STRU          *pstMsg         = VOS_NULL_PTR;
    MMCGMM_PDP_STATUS_IND_STRU          *pstInternalMsg = VOS_NULL_PTR;
    VOS_UINT32                           ulLen;



    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_PDP_STATUS_IND_STRU);

    pstInternalMsg  = (MMCGMM_PDP_STATUS_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcPdpStatusInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_PDP_STATUS_IND;

    pstMsg->ulPdpStatusFlg = ucPdpStatusFlg;



    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

/*******************************************************************************
  Module   : Gmm_SndMmcStartCnf
  Function : MMCGMM_START_CNFԭ����д������
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����

*******************************************************************************/
VOS_VOID Gmm_SndMmcStartCnf(VOS_VOID)
{
    MMCGMM_START_CNF_STRU              *pstMsg          = VOS_NULL_PTR;
    MMCGMM_START_CNF_STRU              *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_START_CNF_STRU);

    pstInternalMsg  = (MMCGMM_START_CNF_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcStartCnf,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_START_CNF;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
VOS_VOID Gmm_SndMmcTBFRelInd(VOS_VOID)
{
    MMCGMM_TBF_REL_IND_STRU            *pstMsg          = VOS_NULL_PTR;
    MMCGMM_TBF_REL_IND_STRU            *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    NAS_MML_SetPsTbfStatusFlg(VOS_FALSE);

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_TBF_REL_IND_STRU);

    pstInternalMsg  = (MMCGMM_TBF_REL_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcTBFRelInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_TBF_REL_IND;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}

/*******************************************************************************
  Module   : Gmm_SndMmcLocalDetachInd
  Function : MMCGMM_LOCAL_DETACH_INDԭ����д������
  Input    : VOS_UINT32     ulDetachCause             detachԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����

*******************************************************************************/
VOS_VOID Gmm_SndMmcLocalDetachInd(
                              VOS_UINT32 ulDetachCause                               /* detachԭ��                               */
                              )
{
    MMCGMM_LOCAL_DETACH_IND_STRU       *pstMsg          = VOS_NULL_PTR;
    MMCGMM_LOCAL_DETACH_IND_STRU       *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_LOCAL_DETACH_IND_STRU);

    pstInternalMsg  = (MMCGMM_LOCAL_DETACH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcLocalDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_LOCAL_DETACH_IND;
    pstMsg->ulDetachCause                 = ulDetachCause;                                        /* ��дlocal detachԭ��                     */
    pstMsg->ulServiceSts                  = Gmm_ComServiceSts();                                   /* ��д����״̬                             */

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}





VOS_VOID Gmm_SndRrmmEstReq(
                       VOS_UINT32                     ulEstCause,                    /* RRC Connection Setupԭ��                 */
                       VOS_UINT32                     ulIdnnsType,                   /* 3����Ӧpaging��,6��������                */
                       NAS_MSG_STRU              *pMsg                          /* ��CN Domain��NAS��Ϣ�׵�ַ               */
                       )
{
    IDNNS_STRU                   Idnns;
    VOS_UINT8                   *pucData;
    VOS_INT32                    lRet;
    VOS_UINT32                   ulRet;
    RRC_PLMN_ID_STRU             stPlmnId;
    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_PLMN_ID_STRU                        stGmmPlmnId;
    GMM_RAI_STRU                            stRai;
    VOS_UINT8                               ucTmpUeIdMask;
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT8                               aucPtmsi[RRC_NAS_PTMSI_LEN];

    NAS_MML_PLMN_ID_STRU                    stLteRplmn;
#endif

    ucTmpUeIdMask     = GMM_UEID_INVALID;

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmPlmnId);
    stRai.ucRac             = pstLastSuccRai->ucRac;
    stRai.Lai.aucLac[0]     = pstLastSuccRai->stLai.aucLac[0];
    stRai.Lai.aucLac[1]     = pstLastSuccRai->stLai.aucLac[1];
    stRai.Lai.PlmnId        = stGmmPlmnId;

    if(VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmEstReq:WARNING: Null pointer");
        return;
    }

    GMM_ReportM2NOtaMsg(pMsg);


    if (3 == ulIdnnsType)
    {                                                                           /* ��Ӧpaging��                             */
        Idnns.ucIdnnsType = RRC_IDNNS_IMSI_PAGE_RSP;                            /* ��ֵIDdns����                            */
    }
    else
    {                                                                           /* ��Ҫ�ж����͵�                           */
        /* �����ǰUE��IMSIʶ��,��ʱ�ж��µ�ǰ�Ƿ�֧��LTE��֧�ֵĻ��жϴ�LTE�µ�
           GUTIӳ�������PTMSI�Ƿ���Ч����Ч�Ļ���ʱUE��PTMSIʶ�� */
#if (FEATURE_ON == FEATURE_LTE)
        if (NAS_MML_NET_RAT_TYPE_LTE == gstGmmCasGlobalCtrl.ucLastDataSender)
        {
            if (VOS_TRUE == NAS_MML_GetLteRPlmn(&stLteRplmn))
            {
                NAS_GMM_ConvertPlmnIdToGmmFormat(&stLteRplmn, &stGmmPlmnId);
            }
        }

        ucTmpUeIdMask = NAS_GMM_GetPTmsi_GUL(aucPtmsi);
        if (GMM_UEID_INVALID == ucTmpUeIdMask)
        {
            ucTmpUeIdMask = g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask;
        }
#else
        ucTmpUeIdMask = g_GmmGlobalCtrl.UeInfo.UeId.ucUeIdMask;
#endif

        if (GMM_UEID_P_TMSI
            == (ucTmpUeIdMask & GMM_UEID_P_TMSI))
        {                                                                       /* UeId���ڱ�ʶ��P_TMSI��Ч                 */
            if (GMM_FALSE
                == Gmm_Com_CmpPlmnid(&stGmmPlmnId))
            {                                                                   /* PLMN ID ����ͬ                           */
                Idnns.ucIdnnsType = RRC_IDNNS_TMSI_DIFFER_PLMN;                 /* ��ֵIDdns����                            */
            }

            else if (GMM_FALSE == Gmm_Com_CmpRai(&stRai, &g_GmmGlobalCtrl.SysInfo.Rai, g_GmmGlobalCtrl.ucNetMod))
            {                                                                   /* RAI��ͬ                                  */
                Idnns.ucIdnnsType = RRC_IDNNS_TMSI_DIFFER_LA;                   /* ��ֵIDdns����                            */
            }
            else
            {                                                                   /* LAI��ͬ                                  */
                Idnns.ucIdnnsType = RRC_IDNNS_LOCAL_TMSI;                       /* ��ֵIDdns����                            */
            }
        }
        else if(GMM_UEID_IMSI
                == (ucTmpUeIdMask & GMM_UEID_IMSI))
        {                                                                       /* UeId���ڱ�ʶ��IMSI��Ч                   */
            Idnns.ucIdnnsType = RRC_IDNNS_IMSI_UE_INIT;
        }
        else
        {                                                                       /* IMEI��Ч                                 */
            Idnns.ucIdnnsType = RRC_IDNNS_IMEI;                                 /* ��ֵIDdns����                            */
        }
    }
    if ((g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[0]
        != stGmmPlmnId.aucMccDigit[0])
        || (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[1]
        != stGmmPlmnId.aucMccDigit[1]))
    {                                                                           /* ϵͳ��Ϣ��RAI������ֽڲ�ͬ��UE��Ϣ�е�  */
        Idnns.ucEnterPara = NAS_RRC_SPLMN_DIFF_RPLMN;                                           /* ��ֵEntered parameter                    */
    }
    else
    {                                                                           /* ϵͳ��Ϣ��RAI������ֽ���ͬ��UE��Ϣ�е�  */
        Idnns.ucEnterPara = NAS_RRC_SPLMN_SAME_RPLMN;                                          /* ��ֵEntered parameter                    */
    }

    stPlmnId.ulMcc = g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[0]
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[1]<<8)
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[2]<<16);

    stPlmnId.ulMnc = g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[0]
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[1]<<8)
                   + ((VOS_UINT32)g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[2]<<16);

    g_GmmReqCnfMng.ucRrmmEstOpid
        = (g_GmmReqCnfMng.ucRrmmEstOpid+1) % GMM_MAX_OPID;
    /*V200R001 modify,begin*/
    if (GMM_FALSE == GMM_IsCasGsmMode())
    {   /*�����W,�����ԭ���������*/
        pucData = pMsg->aucNasMsg;
        lRet = (*g_GmmImportFunc.RrmmEstReqFunc)(g_GmmReqCnfMng.ucRrmmEstOpid,
                                       RRC_NAS_PS_DOMAIN,
                                       ulEstCause,
                                       &Idnns,
                                       &stPlmnId,
                                       pMsg->ulNasMsgSize,
                                       (VOS_INT8 *)pucData
                                       );                   /* ���÷��ͺ��� */
        if (AS_SUCCESS != lRet)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmEstReq:WARNING: Send msg fail.");
        }
    }
    else
    {   /*GPRS���*/
        GMM_SndRrmmEstReqGsm(g_GmmReqCnfMng.ucRrmmEstOpid, pMsg);
    }
    /*V200R001 modify,end*/

    g_GmmReqCnfMng.ucCnfMask |= GMM_RRC_RRMM_EST_CNF_FLG;                       /* �õȴ���Ӧ��־                           */
    /* ����ͷ�ԭ��ֵ */
    g_GmmGlobalCtrl.ucRelCause = RR_REL_CAUSE_NORMAL_EVENT;

    if ((GMM_DETACH_COMBINED_POWER_OFF > g_GmmGlobalCtrl.ucSpecProc)
        || (GMM_DETACH_NORMAL_SIM_REMOVE < g_GmmGlobalCtrl.ucSpecProc))
    {
        Gmm_SndMmcSignalingStatusInd(MMC_GMM_SIGNALING_STATUS_ESTING);          /* ֪ͨMMC PS�������������ڽ���             */
    }

    ulRet = Gmm_MemFree(pMsg);                                      /* �ͷ�������ڴ�ռ�                       */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmEstReq:WARNING: Free msg fail.");
    }

    g_GmmGlobalCtrl.ucTime2Sndout = VOS_TRUE;

    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_Com_CmpPlmnid
  Function : �Ƚ�ϵͳ��Ϣ��UE��Ϣ�е�PLMN ID�Ƿ���ͬ
  Input    : GMM_PLMN_ID_STRU *pPlmnId
  Output   : ��
  NOTE     : ��
  Return   : GMM_TRUE   ��ͬ
             GMM_FALSE  ��ͬ
  History  :
    1. ��־��  2003.12.09  �¹�����
*******************************************************************************/
VOS_UINT8 Gmm_Com_CmpPlmnid(
                        GMM_PLMN_ID_STRU *pPlmnId                               /* ָ��PLMN��ָ��                           */
                        )
{
    VOS_UINT8           i;                                                          /* ������ʱ����                             */

    for (i=0; i<3; i++)
    {                                                                           /* ��MCC�������ж�                          */
        if (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMccDigit[i]
            != pPlmnId->aucMccDigit[i])
        {                                                                       /* MCC����ͬ                                */
            return GMM_FALSE;                                                   /* ����GMM_FALSE                            */
        }
    }

    if (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.ucMncCnt != pPlmnId->ucMncCnt)
    {                                                                           /* MNC��������ͬ                            */
        return GMM_FALSE;                                                       /* ����GMM_FALSE                            */
    }

    for (i=0; i<g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.ucMncCnt; i++)
    {                                                                           /* ��MNC�������ж�                          */
        if (g_GmmGlobalCtrl.SysInfo.Rai.Lai.PlmnId.aucMncDigit[i]
            != pPlmnId->aucMncDigit[i])
        {                                                                       /* MNC����ͬ                                */
            return GMM_FALSE;                                                   /* ����GMM_FALSE                            */
        }
    }

    return GMM_TRUE;                                                            /* ����GMM_TRUE                             */
}
VOS_VOID Gmm_SndRrmmDataReq(
                        VOS_UINT8               ucPriorityInd,                      /* ��Ϣ���ȼ�ָʾ                           */
                        NAS_MSG_STRU        *pMsg                               /* ��CN Domain��NAS��Ϣ�׵�ַ               */
                        )
{
    VOS_INT32  lRet;
    VOS_UINT32 ulRet;
    if(VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Null pointer");
        return;
    }

    GMM_ReportM2NOtaMsg(pMsg);


    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        GMM_SndRrmmDataReqGsm(pMsg);    /* 2GģʽGMM��Ϣ���� */
        ulRet = Gmm_MemFree(pMsg);                                       /* �ͷ�������ڴ�ռ� */
        if (VOS_OK != ulRet)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Free msg fail.");
        }
        return;
    }

    lRet = (g_GmmImportFunc.RrmmDataReqFunc)(RRC_NAS_PS_DOMAIN,
                                    ucPriorityInd,
                                    pMsg->ulNasMsgSize,
                                    (VOS_INT8 *)pMsg->aucNasMsg);                   /* ���÷��ͺ���                             */

    gstGmmCasGlobalCtrl.ucLastDataSender = NAS_MML_NET_RAT_TYPE_WCDMA;

    if (AS_SUCCESS != lRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Send msg fail.");
    }

    ulRet = Gmm_MemFree(pMsg);                                      /* �ͷ�������ڴ�ռ�                       */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReq:WARNING: Free msg fail.");
    }
    return;                                                                     /* ����                                     */
}

/*******************************************************************************
  Module   : Gmm_SndRrmmRelReq
  Function : ����RRMM_REL_REQԭ�ﴦ��
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����
*******************************************************************************/
VOS_VOID Gmm_SndRrmmRelReq(RRC_CELL_BAR_ENUM_UINT32  enBarValidFlg)
{
    VOS_INT32 lRet;

    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        GMM_SndRrmmRelReqGsm();

        return;
    }

    lRet = (*g_GmmImportFunc.RrmmRelReqFunc)(RRC_NAS_PS_DOMAIN,enBarValidFlg);                /* ���÷��ͺ���                             */
    if (AS_SUCCESS != lRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmRelReq:WARNING: Send msg fail.");
    }
    return;                                                                     /* ����                                     */
}


VOS_VOID  NAS_GMM_SndRrmmRelCsPsAllConnReq(VOS_VOID)
{
    RRMM_REL_CS_PS_ALL_CONN_REQ_STRU   *pstMsg = VOS_NULL_PTR;

    pstMsg = (RRMM_REL_CS_PS_ALL_CONN_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(RRMM_REL_CS_PS_ALL_CONN_REQ_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndRrmmRelCsPsAllConnReq:WARNING: Memory Alloc Fail.");
        return;
    }

    PS_MEM_SET(((VOS_UINT8*)pstMsg) + VOS_MSG_HEAD_LENGTH, 0, sizeof(RRMM_REL_CS_PS_ALL_CONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pstMsg->stMsgHeader.ulLength        = sizeof(RRMM_REL_CS_PS_ALL_CONN_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName       = RRMM_REL_CS_PS_ALL_CONN_REQ;

    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndRrmmRelCsPsAllConnReq Snd msg fail!");
    }

    return;
}



VOS_VOID  NAS_GMM_SyncNasInfoChange_RegisteredStatus(VOS_UINT32 ulMask)
{
    GMM_STATE_TYPE_UINT8                     ucState;

    if ((GMM_SUSPENDED_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_GPRS_SUSPENSION == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_NORMAL_SERVICE == g_GmmGlobalCtrl.ucState)
     || (GMM_SUSPENDED_WAIT_FOR_SYSINFO == g_GmmGlobalCtrl.ucState))
    {
        ucState = gstGmmSuspendCtrl.ucPreState;
    }
    else
    {
        ucState = g_GmmGlobalCtrl.ucState;
    }

    if ((GMM_REGISTERED_NORMAL_SERVICE == ucState)
     || (GMM_REGISTERED_LIMITED_SERVICE == ucState)
     || (GMM_REGISTERED_UPDATE_NEEDED == ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM == ucState)
     || (GMM_REGISTERED_ATTEMPTING_TO_UPDATE == ucState)
     || (GMM_REGISTERED_NO_CELL_AVAILABLE == ucState)
     || (GMM_REGISTERED_PLMN_SEARCH == ucState)
     || (GMM_REGISTERED_IMSI_DETACH_INITIATED == ucState)
     || (GMM_ROUTING_AREA_UPDATING_INITIATED == ucState)
     || (GMM_SERVICE_REQUEST_INITIATED == ucState))
    {
        Gmm_SndRrmmNasInfoChangeReq(ulMask);
    }

    return;
}


VOS_VOID  NAS_GMM_SndWasInfoChangeReq(VOS_UINT32 ulMask)
{

    RRMM_NAS_INFO_CHANGE_REQ_STRU      *pstNasInfoMsg = VOS_NULL_PTR;

    pstNasInfoMsg = (RRMM_NAS_INFO_CHANGE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                     WUEPS_PID_GMM, sizeof(RRMM_NAS_INFO_CHANGE_REQ_STRU));

    if (VOS_NULL_PTR == pstNasInfoMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_INT8*)pstNasInfoMsg + VOS_MSG_HEAD_LENGTH, 0,
               sizeof(RRMM_NAS_INFO_CHANGE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    pstNasInfoMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstNasInfoMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_WRR;
    pstNasInfoMsg->MsgHeader.ulMsgName       = RRMM_NAS_INFO_CHANGE_REQ;                              /* ��Ϣ����                                  */

    /* ���÷����� */
    pstNasInfoMsg->ulCnDomainCnt            = 1;
    pstNasInfoMsg->aNasInfo[0].ulCnDomainId = RRC_NAS_PS_DOMAIN;

    /* Attach״̬��� */
    if (RRC_NAS_MASK_ATTACH == (RRC_NAS_MASK_ATTACH & ulMask))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpAttach  = VOS_TRUE;
        pstNasInfoMsg->aNasInfo[0].ulAttach     = NAS_GMM_GetAttachStatus();

    }

    /* DRX������� */
    if (RRC_NAS_MASK_DRX == (RRC_NAS_MASK_DRX & ulMask))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpDrxLength = VOS_TRUE;

        pstNasInfoMsg->aNasInfo[0].ulDrxLength    = (VOS_UINT32)NAS_MML_GetWSysInfoDrxLen();

    }

    /* UMTS CK IK ��Ϣ��� */
    if (RRC_NAS_MASK_SECURITY_KEY == ( RRC_NAS_MASK_SECURITY_KEY & ulMask ) )
    {
        pstNasInfoMsg->aNasInfo[0].bitOpSecurityKey = VOS_TRUE;

        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucCk,
                   NAS_MML_GetSimPsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);
        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucIk,
                   NAS_MML_GetSimPsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);
    }

    /* P_TMSI��RAI��ֵ */
    if (RRC_NAS_MASK_PTMSI_RAI == (ulMask & RRC_NAS_MASK_PTMSI_RAI))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpPTmsiRai = VOS_TRUE;

        NAS_GMM_GetPTmsiRAI(&(pstNasInfoMsg->aNasInfo[0].PTmsiRai));

    }

    /* Del Key Op������ */
    if (RRC_NAS_MASK_DEL_KEY == (ulMask & RRC_NAS_MASK_DEL_KEY))
    {
        pstNasInfoMsg->aNasInfo[0].bitDelKey = VOS_TRUE;
    }

    /* RRC_NAS_MASK_MAPPED_SECURITY_KEY������ */
    if (RRC_NAS_MASK_MAPPED_SECURITY_KEY == (ulMask & RRC_NAS_MASK_MAPPED_SECURITY_KEY))
    {
        pstNasInfoMsg->aNasInfo[0].bitOpIdleMappedLSecurity = VOS_TRUE;

        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucCk,
                   NAS_MML_GetSimPsSecurityUmtsCk(), NAS_MML_UMTS_CK_LEN);
        PS_MEM_CPY(pstNasInfoMsg->aNasInfo[0].SecurityKey.aucIk,
                   NAS_MML_GetSimPsSecurityUmtsIk(), NAS_MML_UMTS_IK_LEN);
    }


    /* ��Was ���ͽ�� */
    if (VOS_OK != NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstNasInfoMsg))
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndWasInfoChangeReq Snd pstNasInfoMsg fail!");
    }

    return;

}
VOS_VOID Gmm_SndRrmmNasInfoChangeReq(VOS_UINT32 ulMask)
{

    if (RRC_NAS_MASK_NULL == ulMask)
    {
        return;
    }

    if (NAS_MML_NET_RAT_TYPE_GSM == NAS_MML_GetCurrNetRatType())
    {
        NAS_GMM_SndGasInfoChangeReq(ulMask);
    }
    else if (NAS_MML_NET_RAT_TYPE_WCDMA == NAS_MML_GetCurrNetRatType())
    {
        NAS_GMM_SndWasInfoChangeReq(ulMask);
    }
    else
    {

    }

    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_SndSmEstablishCnf(
                           VOS_UINT32                   ulEstResult,             /* ע����                                 */
                           GMM_SM_CAUSE_ENUM_UINT16     enCause                  /* ע��ʧ��ԭ��ֵ */
                           )
{
    GMMSM_ESTABLISH_CNF_STRU   *pMsg;                                           /* ����ָ��                                 */
    VOS_UINT32                  ulRet;
    pMsg = (GMMSM_ESTABLISH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMSM_ESTABLISH_CNF_STRU));                      /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ��ʼ����Ϣ */
    PS_MEM_SET((VOS_CHAR *)pMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(GMMSM_ESTABLISH_CNF_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_ESTABLISH_CNF;                          /* ԭ������                                 */

    pMsg->ulEstResult = ulEstResult;                                            /* ע����                                 */


    pMsg->enCause     = enCause;


    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmEstablishCnf:WARNING: Send msg fail.");
    }
    return;
}


VOS_VOID Gmm_SndSmStatusInd(VOS_VOID)
{
    GMMSM_STATUS_IND_STRU   *pMsg;                                              /* ����ָ��                                 */

    VOS_UINT32               ulGmmStatus;

    VOS_UINT8                   ucAttachSta;

    VOS_UINT8                ucStateChange = GMM_FALSE;
    VOS_UINT32               ulRet;

    NAS_MML_CONN_STATUS_INFO_STRU      *pstConnStatus;

    pstConnStatus   = NAS_MML_GetConnStatus();

    switch (g_GmmGlobalCtrl.ucState)
    {
    case GMM_DEREGISTERED_NORMAL_SERVICE:
    case GMM_DEREGISTERED_LIMITED_SERVICE:
    case GMM_DEREGISTERED_ATTACH_NEEDED:
    case GMM_DEREGISTERED_ATTEMPTING_TO_ATTACH:
    case GMM_DEREGISTERED_NO_CELL_AVAILABLE:
    case GMM_DEREGISTERED_PLMN_SEARCH:
    case GMM_DEREGISTERED_NO_IMSI:
    case GMM_NULL:
        ucAttachSta = GMM_STATUS_DETACHED;
        NAS_GMM_ClearAuthInfo();

#if (FEATURE_LTE == FEATURE_ON)
        if (GMM_TIMER_T3312_FLG == (g_GmmTimerMng.ulTimerRunMask & GMM_TIMER_T3312_FLG))
        {
            NAS_GMM_SndLmmTimerInfoNotify(GMM_TIMER_T3312, GMM_LMM_TIMER_STOP);
        }
#endif

        Gmm_TimerStop(GMM_TIMER_T3312);                                         /* ֹͣT3312                                */
#if (FEATURE_LTE == FEATURE_ON)
        if (NAS_GMM_TIMER_T3323_FLG == (NAS_GMM_TIMER_T3323_FLG & g_GmmTimerMng.ulTimerRunMask))
        {
            Gmm_TimerStop(GMM_TIMER_T3323);
        }
#endif
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;

    case GMM_REGISTERED_LIMITED_SERVICE:

        ucAttachSta = GMM_STATUS_ATTACHED;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;

    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE:

        ucAttachSta = GMM_STATUS_ATTACHED;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;
    case GMM_REGISTERED_NORMAL_SERVICE:
    case GMM_REGISTERED_ATTEMPTING_TO_UPDATE_MM:
        ucAttachSta = GMM_STATUS_ATTACHED;

        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_ABLE;

        break;
    case GMM_REGISTERED_UPDATE_NEEDED:
    case GMM_REGISTERED_NO_CELL_AVAILABLE:
    case GMM_REGISTERED_PLMN_SEARCH:

        ucAttachSta = GMM_STATUS_ATTACHED;
        g_MmSubLyrShare.GmmShare.ucDeatchEnableFlg = GMM_DETACH_DISABLE;

        break;
    case GMM_SUSPENDED_NORMAL_SERVICE:
    case GMM_SUSPENDED_GPRS_SUSPENSION:
    case GMM_SUSPENDED_WAIT_FOR_SYSINFO:
        return;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_SndSmStatusInd:INFO: g_GmmGlobalCtrl.ucState need not report");
        return;

    }

    if (ucAttachSta != g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        ucStateChange = GMM_TRUE;
        g_MmSubLyrShare.GmmShare.ucAttachSta = ucAttachSta;                         /* ����ȫ����                               */
        Gmm_SndRrmmNasInfoChangeReq(RRC_NAS_MASK_ATTACH);
        Gmm_SndSmsRegStateInd();                                                    /* ����ԭ��GMMSMS_REG_STATE_IND             */
    }

    /*modify by liurui, 2006-04-27, A32D01286 test begin*/

    /*if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)*/
    if ((GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
        && (GMM_TRUE == ucStateChange))
    {
        if (VOS_TRUE == NAS_MML_IsPsBearerExist())
        {                                                                        /* ���ڼ����PDP context                   */
            NAS_MML_InitPsBearerContext(NAS_MML_GetPsBearerCtx());

            Gmm_SndMmcPdpStatusInd(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST);       /* ֪ͨMMC PDP context ״̬����             */
            pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;

/*modify by liurui, 2006-04-27, A32D01286 test begin*/
        }
        ulGmmStatus = GMM_SM_STATUS_DETACHED;                         /* �ı���GMMע��״̬                      */
/*modify by liurui, 2006-04-27, A32D01286 test end*/
    }
    else if (GMM_STATUS_ATTACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        /*modify by liurui, 2006-04-27, A32D01286 test begin*/
        if ((GMM_TRUE == g_GmmServiceCtrl.ucRejCauseVaildFlg)
         && (NAS_MML_REG_FAIL_CAUSE_NO_PDP_CONTEXT_ACT == g_GmmServiceCtrl.ucRejCause))
        {
            /*if ((0 != g_GmmGlobalCtrl.UeInfo.aucPdpContextSta[0])
             || (0 != g_GmmGlobalCtrl.UeInfo.aucPdpContextSta[1]))
            { */                                                                    /* ���ڼ����PDP context                   */
            NAS_MML_InitPsBearerContext(NAS_MML_GetPsBearerCtx());

            Gmm_SndMmcPdpStatusInd(MMC_GMM_ACTIVE_PDP_CONTEXT_NOT_EXIST);       /* ֪ͨMMC PDP context ״̬����             */
            /*}*/

            pstConnStatus->ucPdpStatusFlg       = VOS_FALSE;

            ulGmmStatus = GMM_SM_SER_REJ_CAUSE_PDP_NOEXIT;                    /* GMM_SM_STATUS_DEACTIVE;GMM_SM_STATUS_DETACHED;*/
        }
        else if (GMM_TRUE == ucStateChange)
        {
            ulGmmStatus = GMM_SM_STATUS_ATTACHED;                             /* �ı���GMMע��״̬                      */
        }
        /*modify by liurui, 2006-04-27, A32D01286 test end*/
        else
        {
            return;
        }
    }
    else
    {
        return;
    }

    pMsg = (GMMSM_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMSM_STATUS_IND_STRU));                         /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmStatusInd:WARNING: Alloc Memory Fail.");
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_STATUS_IND;                             /* ԭ������                                 */

    pMsg->ulGmmStatus           = ulGmmStatus;

    /* �����ֽڶ���reserve�ֽڳ�ʼ�� */
    pMsg->aucRsv[0] = 0;
    pMsg->aucRsv[1] = 0;

    /* ��L�±�����ܾ�����GMM����ȥע��״̬,֪ͨSMȥע��ʱ,
       �ᵼ��L���޷���������ԭ��ֵ���������̴��� */
    /* ��дDETACHԭ��ֵ */
    /* �ϱ�����GMM״̬�ı��ԭ��ֵ */
    /* DETACH -> ATTACHԭ��ֵ: GMM_SM_CAUSE_BUTT */
    /* ATTACH -> DETACHԭ��ֵ: Lģ:GMM_SM_CAUSE_LTE_MO_DETACH */
    /* ---------------------����ģ:g_GmmGlobalCtrl.enGmmCause */
    pMsg->enCause = GMM_SM_CAUSE_BUTT;

    if (GMM_SM_STATUS_DETACHED == ulGmmStatus)
    {
        pMsg->enCause = NAS_GMM_GetAttach2DetachErrCode();

        if (NAS_MML_NET_RAT_TYPE_LTE == NAS_MML_GetCurrNetRatType())
        {
            pMsg->enCause = GMM_SM_CAUSE_LTE_MO_DETACH;
        }
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                    /* ԭ�﷢��                                 */
    /*modify by liurui, 2006-04-27, A32D01286 test end*/
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmStatusInd:WARNING: Send msg Fail.");
    }
    return;
}
VOS_VOID NAS_GMM_SndSmStatusInd(
    VOS_UINT32                          ulGmmStatus,
    GMM_SM_CAUSE_ENUM_UINT16            enCause
)
{

    GMMSM_STATUS_IND_STRU              *pstMsg = VOS_NULL_PTR;                                  /* ����ָ��                                 */
    VOS_UINT32                          ulRet;

    pstMsg = (GMMSM_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMSM_STATUS_IND_STRU));                         /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SndSmStatusInd:WARNING: Alloc Memory Fail.");
        return;
    }

    pstMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pstMsg->MsgHeader.ulMsgName   = GMMSM_STATUS_IND;                             /* ԭ������                                 */

    pstMsg->ulGmmStatus           = ulGmmStatus;
    pstMsg->enCause = enCause;

    pstMsg->aucRsv[0] = 0;
    pstMsg->aucRsv[1] = 0;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);                                    /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SndSmStatusInd:WARNING: Send msg Fail.");
    }
    return;

}

/*******************************************************************************
  Module   : Gmm_SndSmDataInd
  Function : ԭ��GMMSM_DATA_IND�ķ��ʹ���
  Input    : NAS_MSG_STRU    *pSmMsg     Ҫ������Ϣ�ĵ�ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����

*******************************************************************************/
VOS_VOID Gmm_SndSmDataInd(
                      NAS_MSG_FOR_PCLINT_STRU          *pSmMsg
                      )
{
    VOS_UINT8              i;                                                   /* ����ѭ�����Ʊ���                         */
    GMMSM_DATA_IND_STRU   *pMsg;                                                /* ������ʱ����                             */
    VOS_UINT32             ulRet;

    if (4 < pSmMsg->ulNasMsgSize)
    {
        pMsg = (GMMSM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                (sizeof(GMMSM_DATA_IND_STRU) + pSmMsg->ulNasMsgSize) - 4);        /* �����ڴ�                                 */

    }
    else
    {
        pMsg = (GMMSM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                                sizeof(GMMSM_DATA_IND_STRU));   /* �����ڴ�                                 */
    }
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_DATA_IND;                               /* ԭ������                                 */

    pMsg->SmMsg.ulNasMsgSize = pSmMsg->ulNasMsgSize;                            /* ��д��Ϣ����                             */
    for (i=0; i<pSmMsg->ulNasMsgSize; i++)
    {
        pMsg->SmMsg.aucNasMsg[i] = pSmMsg->aucNasMsg[i];                        /* ��д��Ϣ����                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmDataInd:WARNING: Send msg Fail.");
    }
    return;
}


VOS_VOID GMM_SndSmServiceRej(
                        GMM_SM_CAUSE_ENUM_UINT16     enCause
                        )
{
    GMMSM_SERVICE_REJ_STRU   *pMsg;                                                /* ������ʱ����                             */
    VOS_UINT32                ulRet;

    pMsg = (GMMSM_SERVICE_REJ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_SERVICE_REJ_STRU));   /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_CHAR*)pMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(GMMSM_SERVICE_REJ_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName       = GMMSM_SERVICE_REJ;                               /* ԭ������                                 */

    pMsg->enCause = enCause;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                      /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "GMM_SndSmServiceRej:WARNING: Send msg Fail.");
    }
    return;
}

VOS_VOID Gmm_SndSmPdpStatusInd(
                        VOS_UINT32                      ulPDPStaus,
                        GMM_SM_CAUSE_ENUM_UINT16        enCause
                        )
{
    GMMSM_PDP_STATUS_IND_STRU          *pMsg;
    VOS_UINT32                          ulRet;

    VOS_UINT8                           i;
    VOS_UINT32                          ulPdpContextStatus;

    pMsg = (GMMSM_PDP_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_PDP_STATUS_IND_STRU));   /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    PS_MEM_SET((VOS_CHAR*)pMsg + VOS_MSG_HEAD_LENGTH,
               0x00,
               sizeof(GMMSM_PDP_STATUS_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName       = GMMSM_PDP_STATUS_IND;                               /* ԭ������                                 */

    pMsg->enCause = enCause;

    for (i = 0; i < NAS_MML_MAX_PS_BEARER_NUM; i++)
    {
        pMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_INACTIVE;
        /*lint -e701*/
        ulPdpContextStatus = (ulPDPStaus) & (0x00000001 << (i + NAS_MML_NSAPI_OFFSET));
        /*lint +e701*/
        if (GMMSM_PDP_STATE_INACTIVE != ulPdpContextStatus)
        {
            pMsg->aucPdpContextStatus[i] = GMMSM_PDP_STATE_ACTIVE;
        }
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                      /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmPdpStatusInd:WARNING: Send msg Fail.");
    }
    return;
}
VOS_VOID Gmm_SndSmSysInfoInd(VOS_UINT8 ucSgsnRelease)
{
    GMMSM_SYS_INFO_IND_STRU   *pMsg;
    VOS_UINT32                 ulRet;

    pMsg = (GMMSM_SYS_INFO_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_SYS_INFO_IND_STRU));   /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }
    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName       = GMMSM_SYS_INFO_IND;                               /* ԭ������                                 */
    pMsg->ucSgsnRelVer              = ucSgsnRelease;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                      /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmSysInfoInd:WARNING: Send msg Fail.");
    }
    return;
}
VOS_VOID Gmm_SndSmRelInd(VOS_VOID)
{
    GMMSM_REL_IND_STRU        *pMsg;
    VOS_UINT32                ulRet;

    pMsg = (GMMSM_REL_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_REL_IND_STRU));
    if (VOS_NULL_PTR == pMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndSmRelInd:WARNING: Memory Alloc Fail.");
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SM;
    pMsg->MsgHeader.ulMsgName   = GMMSM_REL_IND;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);

    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmRelInd:WARNING: Send msg Fail.");
    }
    return;
}
/*******************************************************************************
  Module   : Gmm_SndRabmReestablishCnf
  Function : ����GMMRABM_REESTABLISH_CNFԭ�ﴦ��
  Input    : VOS_UINT8  ucResult    SERVICE REQUEST�ɹ�ʧ�ܱ�־
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.09  �¹�����

*******************************************************************************/
VOS_VOID Gmm_SndRabmReestablishCnf(
                               VOS_UINT8            ucResult                        /* SERVICE REQUEST�ɹ�ʧ�ܱ�־              */
                               )
{
    GMMRABM_REESTABLISH_CNF_STRU   *pMsg;                                       /* ����ָ��                                 */
    VOS_UINT32                      ulRet;

    pMsg = (GMMRABM_REESTABLISH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                        sizeof(GMMRABM_REESTABLISH_CNF_STRU));                  /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pMsg->MsgHeader.ulMsgName   = ID_GMM_RABM_REESTABLISH_CNF;                      /* ԭ������                                 */

    pMsg->ulResult = ucResult;                                                  /* ��SERVICE REQUEST�ɹ�ʧ�ܱ�־            */

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRabmReestablishCnf:WARNING: Send msg Fail.");
    }
    return;
}

/*lint -save -e961 */

VOS_UINT8 Gmm_Com_DealOfPlmnList(
                            VOS_VOID                    *pEquPlmnIdList,            /* ��ЧPLMN�б��׵�ַ                       */
                            MMCGMM_PLMN_ID_STRU     *pPlmnId                    /* ԭ���е�PLMN LIST���׵�ַ                */
                            )
{
    VOS_UINT8                   i;                                                  /* ����ѭ�����Ʊ���                         */
    GMM_PLMN_ID_STRU            *pGmmPlmnId;                                        /* �������                                 */
    VOS_UINT32                   ulMccDigit1;
    VOS_UINT32                   ulMccDigit2;
    VOS_UINT32                   ulMncDigit1;
    VOS_UINT32                   ulMncDigit2;
    VOS_UINT8                           ucEplmnNum;

    ulMccDigit1 = 0;
    ulMccDigit2 = 0;
    ulMncDigit1 = 0;
    ulMncDigit2 = 0;

    if (VOS_NULL_PTR == pEquPlmnIdList)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "Gmm_Com_DealOfPlmnList:INFO: The Entry Pointer is VOS_NULL_PTR");
        return GMM_FALSE;                                                       /* ����                                     */
    }

    pGmmPlmnId = (GMM_PLMN_ID_STRU *)Gmm_MemMalloc(sizeof(GMM_PLMN_ID_STRU)
                                                   * MMC_GMM_MAX_EQUPLMN_NUM);  /* �����ڴ�ռ�                             */
    if (VOS_NULL_PTR == pGmmPlmnId)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Com_DealOfPlmnList:WARNING: Alloc mem fail.");
        return GMM_FALSE;                                                       /* ����                                     */
    }
    Gmm_MemSet(pGmmPlmnId, 0, sizeof(GMM_PLMN_ID_STRU)*MMC_GMM_MAX_EQUPLMN_NUM);/* ��������ڴ�ռ���0                      */

    ucEplmnNum = NAS_COMM_MIN((*((VOS_UINT8 *)pEquPlmnIdList +1) / 3), MMC_GMM_MAX_EQUPLMN_NUM);

    for (i=0; i<ucEplmnNum; i++)
    {                                                                           /* ��PLMN List�洢����ʱ����                */
        pGmmPlmnId[i].aucMccDigit[0] = (VOS_UINT8)(*((VOS_UINT8 *)pEquPlmnIdList
                                                        + 2 + (i * 3)) & 0x0F);   /* MCC digit 1 of PLMN i                    */
        pGmmPlmnId[i].aucMccDigit[1] = (VOS_UINT8)((*((VOS_UINT8 *)pEquPlmnIdList
                                                  + 2 + (i * 3)) >> 4) & 0x0F);   /* MCC digit 2 of PLMN i                    */
        pGmmPlmnId[i].aucMccDigit[2] = (VOS_UINT8)(*((VOS_UINT8 *)pEquPlmnIdList
                                                     + 3 + (i * 3)) & 0x0F);      /* MCC digit 3 of PLMN i                    */
        pGmmPlmnId[i].aucMncDigit[0] = (VOS_UINT8)(*((VOS_UINT8 *)pEquPlmnIdList
                                                   + 4 + (i * 3)) & 0x0F);        /* MNC digit 1 of PLMN i                    */
        pGmmPlmnId[i].aucMncDigit[1] = (VOS_UINT8)((*((VOS_UINT8 *)pEquPlmnIdList
                                             + 4 + (i * 3)) >> 4) & 0x0F);        /* MNC digit 2 of PLMN i                    */
        pGmmPlmnId[i].aucMncDigit[2] = (VOS_UINT8)((*((VOS_UINT8 *)pEquPlmnIdList
                                             + 3 + (i * 3)) >> 4) & 0x0F);        /* MNC digit 3 of PLMN i                    */
    }
    for (i=0; i<(*((VOS_UINT8 *)pEquPlmnIdList +1) / 3); i++)
    {                                                                           /* ��PLMN List����ʱ��������Ŀ���ַ        */
        ulMccDigit1 = pGmmPlmnId[i].aucMccDigit[1];
        ulMccDigit2 = pGmmPlmnId[i].aucMccDigit[2];
        pPlmnId[i].ulMcc = pGmmPlmnId[i].aucMccDigit[0]                         /* �洢MCC digit 1 of PLMN i                */
                           | (ulMccDigit1 << 8)                                 /* �洢MCC digit 2 of PLMN i                */
                           | (ulMccDigit2 << 16);                               /* �洢MCC digit 3 of PLMN i                */
        ulMncDigit1 = pGmmPlmnId[i].aucMncDigit[1];
        ulMncDigit2 = pGmmPlmnId[i].aucMncDigit[2];
        pPlmnId[i].ulMnc = pGmmPlmnId[i].aucMncDigit[0]                         /* �洢MNC digit 1 of PLMN i                */
                           | (ulMncDigit1 << 8)                                 /* �洢MNC digit 2 of PLMN i                */
                           | (ulMncDigit2 << 16);                               /* �洢MNC digit 3 of PLMN i                */
    }

    Gmm_MemFree(pGmmPlmnId);                                            /* �ͷ�������ڴ�ռ�                       */
    return GMM_TRUE;                                                            /* ����                                     */
}
/*lint -restore */

/*******************************************************************************
  Module   : Gmm_Com_DealOfMsId
  Function : MS ID����д
  Input    : VOS_VOID                       *pMsIdentity    MS IDENTITY�׵�ַ
             MMC_GMM_MS_IDENTITY_STRU   *pMsId          ԭ���е�MS ID���׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2003.12.10  �¹�����

*******************************************************************************/
VOS_VOID Gmm_Com_DealOfMsId(
                        VOS_VOID                        *pMsIdentity,               /* MS IDENTITY�׵�ַ,���Ϊ����˵��û�д�IE */
                        MMC_GMM_MS_IDENTITY_STRU    *pMsId                      /* ԭ���е�MS ID���׵�ַ                    */
                        )
{
    VOS_UINT8           i;                                                          /* ����ѭ�����Ʊ���                         */

    if (VOS_NULL_PTR == pMsIdentity)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_Com_DealOfMsId:WARNING: The Entry Pointer is VOS_NULL_PTR");
        return;                                                                 /* ����                                     */
    }
    if (GMM_IEI_MS_IDENTITY != *(VOS_UINT8 *)pMsIdentity)
    {                                                                           /* IEI����                                  */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_NULL;                              /* MS ID ����                               */
    }

    if (GMM_MOBILE_ID_TMSI_PTMSI
        == (*((VOS_UINT8 *)pMsIdentity + 2) & GMM_MOBILE_ID_TMSI_PTMSI))
    {                                                                           /* MS id ��TMSI                             */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_TMSI;                              /* MS ID ����                               */
        for (i=0; i<4; i++)
        {
            pMsId->aucTmsi[i] = *((VOS_UINT8 *)pMsIdentity + 3 + i);                /* ��ֵTMSI                                 */
        }

    }
    else if (GMM_MOBILE_ID_IMSI
             == (*((VOS_UINT8 *)pMsIdentity + 2) & GMM_MOBILE_ID_IMSI))
    {                                                                           /* MS id ��IMSI                             */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_IMSI;                              /* MS ID ����                               */

    }
    else
    {                                                                           /* MS id ������                             */
        pMsId->ulIdType = MMC_GMM_MS_ID_TYPE_NULL;                              /* MS ID ����                               */
    }

    return;                                                                     /* ����                                     */
}

#if (FEATURE_ON == FEATURE_PTM)

VOS_VOID NAS_GMM_SndAcpuOmChangePtmsi(VOS_VOID)
{
    VOS_UINT8                          *pucPtmsi     = VOS_NULL_PTR;
    OM_FTM_REPROT_IND_STRU             *pstFtmRptInd = VOS_NULL_PTR;
    NAS_FTM_PTMSI_RPT_EVENT_STRU        stFtmPtmsiRpt;
    VOS_UINT32                          ulMsgLen;
    VOS_UINT32                          ulContentAddr;

    PS_MEM_SET(&stFtmPtmsiRpt, 0, sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU));

    /* ������̲˵�û�д򿪣���ʲô������ */
    if (VOS_FALSE == NAS_MML_GetFtmCtrlFlag())
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_SndAcpuOmChangePtmsi:INFO: FTM CTRL OFF.");
        return;
    }

    pucPtmsi = NAS_MML_GetUeIdPtmsi();

    /* �����ǰPTMSIû�з����ı䣬��ʲô������ */
    if (0 == PS_MEM_CMP(pucPtmsi, NAS_MML_GetSimPsLociFileContent(), NAS_MML_MAX_PTMSI_LEN))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_INFO, "NAS_GMM_SndAcpuOmChangePtmsi:INFO: PTMSI NOT CHANGE.");
        return;
    }

    NAS_COMM_BULID_FTM_HEADER_INFO(&stFtmPtmsiRpt.stHeader,
                                   NAS_MML_MAX_PTMSI_LEN,
                                   VOS_GetModemIDFromPid(WUEPS_PID_GMM),
                                   NAS_FTM_PROJECT_PTMSI_RPT)

    PS_MEM_CPY(stFtmPtmsiRpt.aucPtmsi, pucPtmsi, NAS_MML_MAX_PTMSI_LEN);

    /* ��PTMSI��ֵ���͸�ACPU OMģ�� */
    /* ������Ϣ�ṹ�ڴ� */
    /*lint -e961*/
    ulMsgLen     = sizeof(OM_FTM_REPROT_IND_STRU) - VOS_MSG_HEAD_LENGTH - 4 + sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU);
    /*lint +e961*/

    pstFtmRptInd = (OM_FTM_REPROT_IND_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM, ulMsgLen);
    if (VOS_NULL_PTR == pstFtmRptInd)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndAcpuOmChangePtmsi:ERROR: Alloc msg fail.");
        return;
    }

    /* ������Ϣ�ṹ�� */
    pstFtmRptInd->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstFtmRptInd->ulReceiverPid     = MSP_PID_DIAG_APP_AGENT;
    pstFtmRptInd->ulSenderPid       = WUEPS_PID_GMM;
    pstFtmRptInd->ulMsgName         = ID_OM_FTM_REPROT_IND;
    pstFtmRptInd->ulMsgType         = OM_ERR_LOG_MSG_FTM_REPORT;
    pstFtmRptInd->ulMsgSN           = 0;
    pstFtmRptInd->ulRptlen          = sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU);

    ulContentAddr                   = (VOS_UINT32)pstFtmRptInd->aucContent;
    PS_MEM_CPY((VOS_UINT8 *)ulContentAddr, &stFtmPtmsiRpt, sizeof(NAS_FTM_PTMSI_RPT_EVENT_STRU));

    /* ������Ϣ��ACPU OMģ�� */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_GMM, pstFtmRptInd))
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndAcpuOmChangePtmsi:ERROR: SEND MSG FIAL.");
    }

    return;
}
#endif


VOS_VOID Gmm_SndAgentUsimUpdateFileReq(
                                   VOS_UINT16 usEfId                                /* ϣ����ȡ���ļ�ID                         */
                                   )
{
    VOS_UINT8 *pucPsKey     = VOS_NULL_PTR;                                                 /* ����ָ��                                 */
    VOS_UINT8 *pucPsLocInfo = VOS_NULL_PTR;                                                 /* ����ָ��                                 */

    NAS_NVIM_PS_LOCI_SIM_FILES_STRU stPsLociSimFiles;

    NAS_MML_RAI_STRU                       *pstLastSuccRai;
    GMM_PLMN_ID_STRU                        stGmmPlmnId;

    /* Modified by h00313353 for iteration 9, 2015-2-3, begin */
    NAS_USIMM_UPDATEFILE_INFO_STRU          stSetFileInfo;

    PS_MEM_SET(&stSetFileInfo, 0x00, sizeof(stSetFileInfo));
    /* Modified by h00313353 for iteration 9, 2015-2-3, end */

    pucPsLocInfo = VOS_NULL_PTR;                                                        /* ��ʼ��ָ��                               */

    pstLastSuccRai    = NAS_MML_GetPsLastSuccRai();
    NAS_GMM_ConvertPlmnIdToGmmFormat(&(pstLastSuccRai->stLai.stPlmnId), &stGmmPlmnId);


    switch (usEfId)
    {
    case USIMM_USIM_EFKCGPRS_ID:
    /* BEGIN: Modified by liurui id:40632, 2006/6/29   PN:A32D04514 */
    case USIMM_GSM_EFKCGPRS_ID:     /* 2G SIM GPRS Kc Key */
    /* END:   Modified by liurui id:40632, 2006/6/29   PN:A32D04514 */
        pucPsKey = (VOS_UINT8 *)Gmm_MemMalloc(9);               /* ����ռ� */
        if (VOS_NULL_PTR == pucPsKey)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: Alloc mem fail.");
            return;                                                            /* ����                                     */
        }

        Gmm_MemSet(pucPsKey, 0, 9);                         /* ������Ŀռ���0 */

        pucPsKey[8] = NAS_MML_GetSimPsSecurityCksn();                    /* ����ļ����� */

        Gmm_MemCpy(&pucPsKey[0],
                   NAS_MML_GetSimPsSecurityGsmKc(), 8);

        NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                        /* Modified by h00313353 for iteration 9, 2015-2-4, begin */
                                        USIMM_GUTL_APP,
                                        /* Modified by h00313353 for iteration 9, 2015-2-4, end */
                                        usEfId,
                                        0,
                                        NAS_MML_PS_KC_SIM_FILE_LEN,
                                        pucPsKey);

        (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_GMM, 0, &stSetFileInfo);

        Gmm_MemFree(pucPsKey);                                                  /* �ͷ��ڴ� */

        break;
    case USIMM_USIM_EFKEYSPS_ID:
        pucPsKey = (VOS_UINT8 *)Gmm_MemMalloc(33);                              /* ����ռ�                                 */
        if (VOS_NULL_PTR == pucPsKey)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: Alloc mem fail.");
            return;                                                             /* ����                                     */
        }
        Gmm_MemSet(pucPsKey, 0, 33);                                            /* ������Ŀռ���0                          */

        pucPsKey[0] = NAS_MML_GetSimPsSecurityCksn();                    /* ����ļ�����                             */

        Gmm_MemCpy(&pucPsKey[1],
                   NAS_MML_GetSimPsSecurityUmtsCk(), 16);
        Gmm_MemCpy(&pucPsKey[17],
                   NAS_MML_GetSimPsSecurityUmtsIk(), 16);

        NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                        /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
                                        USIMM_GUTL_APP,
                                        /* Modified by h00313353 for iteration 9, 2015-2-7, end */
                                        usEfId,
                                        0,
                                        NAS_MML_PS_KEY_USIM_FILE_LEN,
                                        pucPsKey);

        (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_GMM, 0, &stSetFileInfo);

        Gmm_MemFree(pucPsKey);                                                  /* �ͷ��ڴ�                                 */
        break;
    case USIMM_USIM_EFPSLOCI_ID:                                             /* ����PS Location information              */
    case USIMM_GSM_EFLOCIGPRS_ID:
        pucPsLocInfo = (VOS_UINT8 *)Gmm_MemMalloc(14);                              /* ����ռ�                                 */
        if (VOS_NULL_PTR == pucPsLocInfo)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: Alloc mem fail.");
            return;                                                             /* ����                                     */
        }
        Gmm_MemSet(pucPsLocInfo, 0, 14);                                        /* ������Ŀռ���0                          */

        Gmm_MemCpy(pucPsLocInfo,
                   NAS_MML_GetUeIdPtmsi(),
                   NAS_MML_MAX_PTMSI_LEN);                                         /* P_TMSI��ֵ                               */
        Gmm_MemCpy(pucPsLocInfo + 4,
                   NAS_MML_GetUeIdPtmsiSignature(),
                   NAS_MML_MAX_PTMSI_SIGNATURE_LEN);                               /* ��P_TMSI signature                       */


        pucPsLocInfo[7] =
            (VOS_UINT8)(stGmmPlmnId.aucMccDigit[0]
            | (stGmmPlmnId.aucMccDigit[1] << 4));   /* ��MCC��MNC                               */
        pucPsLocInfo[8] =
            (VOS_UINT8)(stGmmPlmnId.aucMccDigit[2]
            | (stGmmPlmnId.aucMncDigit[2] << 4));   /* ��MCC��MNC                               */
        pucPsLocInfo[9] =
            (VOS_UINT8)(stGmmPlmnId.aucMncDigit[0]
            | (stGmmPlmnId.aucMncDigit[1] << 4));   /* ��MCC��MNC                               */
        pucPsLocInfo[10] = pstLastSuccRai->stLai.aucLac[0];          /* ��LAC                                    */
        pucPsLocInfo[11] = pstLastSuccRai->stLai.aucLac[1];
        pucPsLocInfo[12] = pstLastSuccRai->ucRac;                  /* ��RAC                                    */
        pucPsLocInfo[13] = NAS_MML_GetPsUpdateStatus();                  /* ������״̬                               */


        /*���д���ļ�6F73�����ݺͿ���ǰ���洢�����ݲ���ͬ����ִ��д������*/
        if (0 != PS_MEM_CMP(pucPsLocInfo, NAS_MML_GetSimPsLociFileContent(), NAS_MML_PS_LOCI_SIM_FILE_LEN))
        {
            NAS_COMM_BUILD_USIM_SET_FILE_INFO(&stSetFileInfo,
                                            /* Modified by h00313353 for iteration 9, 2015-2-7, begin */
                                            USIMM_GUTL_APP,
                                            /* Modified by h00313353 for iteration 9, 2015-2-7, end */
                                            usEfId,
                                            0,
                                            NAS_MML_PS_LOCI_SIM_FILE_LEN,
                                            pucPsLocInfo);

            (VOS_VOID)NAS_USIMMAPI_SetFileReq(WUEPS_PID_GMM, 0, &stSetFileInfo);

            NAS_MML_UpdateSimPsLociFileContent(pucPsLocInfo);

            PS_MEM_CPY(stPsLociSimFiles.aucPsLocInfo, pucPsLocInfo, sizeof(stPsLociSimFiles.aucPsLocInfo));
            if (NV_OK != NV_Write(en_NV_Item_Ps_Loci, &stPsLociSimFiles, sizeof(NAS_NVIM_PS_LOCI_SIM_FILES_STRU)))
            {
                NAS_ERROR_LOG(WUEPS_PID_MMC, "Gmm_SndAgentUsimUpdateFileReq:ERROR: NV_Write Error");
            }

        }




        Gmm_MemFree(pucPsLocInfo);                                              /* �ͷ��ڴ�                                 */
        break;
    default:
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndAgentUsimUpdateFileReq:WARNING: EF id error");
        break;
    }

    return;                                                                     /* ����                                     */
}


VOS_VOID Gmm_SndAgentUsimAuthenticationReq(
                                       VOS_UINT32    ulLength,                       /* AUTN�ĳ���                               */
                                       VOS_VOID     *pAutn                          /* ָ�����AUTN�ĵ�ָ��                     */
                                       )
{
    VOS_UINT8   ucAuthenType;
    VOS_UINT8   ucTempOpId = 0;


    if (GMM_UMTS_AUTHEN_SUPPORTED == g_GmmAuthenCtrl.ucUmtsAuthFlg)
    {
        ucAuthenType = AUTHENTICATION_REQ_UMTS_CHALLENGE;
    }
    else
    {
        ucAuthenType = AUTHENTICATION_REQ_GSM_CHALLENGE;
    }

    ucTempOpId = g_GmmAuthenCtrl.ucOpId;

    g_GmmAuthenCtrl.ucOpId = (VOS_UINT8)((ucTempOpId) % 255);
    g_GmmAuthenCtrl.ucOpId++;

    /* ����USIM��API���ͺ��� */
    NAS_USIMMAPI_AuthReq( WUEPS_PID_GMM,
                   ucAuthenType,
                   (VOS_UINT8 *)g_GmmAuthenCtrl.aucRandSav,
                   (VOS_UINT8 *)pAutn,
                   g_GmmAuthenCtrl.ucOpId);

    g_GmmReqCnfMng.ucCnfMask |= GMM_AGENT_USIM_AUTHENTICATION_CNF_FLG;          /* �õȴ���Ӧ��־                           */

    return;                                                                     /* ����                                     */
}
VOS_VOID Gmm_SndMmcSignalingStatusInd(
                                  VOS_UINT32  ulSignalingSts                         /* PS����������״̬                         */
                                  )
{
    MMCGMM_SIGNALING_STATUS_IND_STRU   *pstMsg          = VOS_NULL_PTR;
    MMCGMM_SIGNALING_STATUS_IND_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_SIGNALING_STATUS_IND_STRU);

    pstInternalMsg  = (MMCGMM_SIGNALING_STATUS_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcSignalingStatusInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_SIGNALING_STATUS_IND;
    pstMsg->ulSignalingSts                = ulSignalingSts;                               /* ��д�������Ӵ���״̬                     */                                         /* attachԭ��                               */


    if (MMC_GMM_SIGNALING_STATUS_ABSENT == ulSignalingSts)
    {
        g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_OFF;
        NAS_MML_SetPsSigConnStatusFlg(VOS_FALSE);

        NAS_GMM_DeleteRandAndResInfoInPmmIdleMode();
    }
    else
    {
        g_MmSubLyrShare.GmmShare.ucPsSpecificFlg = GMM_SPECIFIC_ON;

        if (VOS_FALSE == GMM_IsCasGsmMode())
        {
            NAS_MML_SetPsSigConnStatusFlg(VOS_TRUE);
        }
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}


/*******************************************************************************
  Module   : Gmm_SndSmsRegStateInd
  Function : ����ԭ��GMMSMS_REG_STATE_IND�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.  ��־��  2004.03.11  �¹�����(���ڸ���_GMM_001_2)
*******************************************************************************/
VOS_VOID Gmm_SndSmsRegStateInd(VOS_VOID)
{
    GMMSMS_REG_STATE_IND_STRU   *pMsg;                                          /* ����ָ��                                 */
    VOS_UINT32                   ulRet;

    pMsg = (GMMSMS_REG_STATE_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                    sizeof(GMMSMS_REG_STATE_IND_STRU));         /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = GMMSMS_REG_STATE_IND;                         /* ԭ������                                 */

    if (GMM_STATUS_DETACHED == g_MmSubLyrShare.GmmShare.ucAttachSta)
    {
        pMsg->ulRegSts = GMM_SMS_REG_DETTACHED;                                 /* ��дע��״̬                             */                                         /* attachԭ��                               */
    }
    else
    {
        pMsg->ulRegSts = GMM_SMS_REG_ATTACHED;                                  /* ��дע��״̬                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsRegStateInd:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmsEstCnf
  Function : ����ԭ��PMMSMS_EST_CNF�Ĵ���
  Input    : ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.  ��־��  2004.03.11  �¹�����(���ڸ���_GMM_001_4)
*******************************************************************************/
VOS_VOID Gmm_SndSmsEstCnf(VOS_VOID)
{
    PMMSMS_EST_CNF_STRU   *pMsg;                                                /* ����ָ��                                 */
    VOS_UINT32             ulRet;
    pMsg = (PMMSMS_EST_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                    sizeof(PMMSMS_EST_CNF_STRU));               /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = PMMSMS_EST_CNF;                               /* ԭ������                                 */

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsEstCnf:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmsUnitdataInd
  Function : ����ԭ��PMMSMS_UNITDATA_IND�Ĵ���
  Input    : NAS_MSG_STRU    *pSmMsg     Ҫ������Ϣ�ĵ�ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.03.11  �¹�����(���ڸ���_GMM_001_6)

*******************************************************************************/
VOS_VOID Gmm_SndSmsUnitdataInd(
                           NAS_MSG_FOR_PCLINT_STRU          *pSmsMsg
                           )
{
    VOS_UINT8                       i;                                              /* ����ѭ�����Ʊ���                         */
    PMMSMS_UNITDATA_IND_STRU    *pMsg;                                          /* ������ʱ����                             */
    VOS_UINT32                   ulRet;

    if (4 < pSmsMsg->ulNasMsgSize)
    {
        pMsg = (PMMSMS_UNITDATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                (sizeof(PMMSMS_UNITDATA_IND_STRU)+ pSmsMsg->ulNasMsgSize) - 4);   /* �����ڴ�                                 */

        }
    else
    {
        pMsg = (PMMSMS_UNITDATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                        sizeof(PMMSMS_UNITDATA_IND_STRU));      /* �����ڴ�                                 */
    }
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = PMMSMS_UNITDATA_IND;                          /* ԭ������                                 */

    pMsg->SmsMsg.ulNasMsgSize = pSmsMsg->ulNasMsgSize;                          /* ��д��Ϣ����                             */
    for (i=0; i<pSmsMsg->ulNasMsgSize; i++)
    {
        pMsg->SmsMsg.aucNasMsg[i] = pSmsMsg->aucNasMsg[i];                      /* ��д��Ϣ����                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsUnitdataInd:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndSmsErrorInd
  Function : ����ԭ��PMMSMS_ERROR_IND�Ĵ���
  Input    : VOS_UINT8  ucCause         �ͷ�ԭ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1.  ��־��  2004.03.11  �¹�����(���ڸ���_GMM_001_7)
*******************************************************************************/
VOS_VOID Gmm_SndSmsErrorInd(
                        VOS_UINT8  ucCause                                          /* �ͷ�ԭ��                                 */
                        )
{
    PMMSMS_ERROR_IND_STRU   *pMsg;                                              /* ����ָ��                                 */
    VOS_UINT32               ulRet;
    pMsg = (PMMSMS_ERROR_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                    sizeof(PMMSMS_ERROR_IND_STRU));             /* �����ڴ�                                 */
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
    pMsg->MsgHeader.ulMsgName   = PMMSMS_ERROR_IND;                             /* ԭ������                                 */

    pMsg->ulCause = ucCause;                                                    /* ��дԭ��                                 */

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsErrorInd:WARNING: Send msg fail.");
    }
    return;
}


VOS_VOID Gmm_SndSmsServiceStatusInd(VOS_VOID)
{
    GMMSMS_SERVICE_STATUS_IND_STRU   *pMsg;                                     /* ����ָ��                                 */
    VOS_UINT32                        ulRet;
    VOS_UINT32                        ulTempServiceStatus = GMM_SMS_NO_SERVICE;
    static VOS_UINT32                 ulServiceStatus     = GMM_SMS_NO_SERVICE;

    ulTempServiceStatus = Gmm_GetServiceStatusForSms();

    if (ulServiceStatus != ulTempServiceStatus)
    {                                                                           /* ����״̬�仯�˲��ϱ�������ģ��           */
        pMsg = (GMMSMS_SERVICE_STATUS_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                        sizeof(GMMSMS_SERVICE_STATUS_IND_STRU));/* �����ڴ�                                 */
        if (VOS_NULL_PTR == pMsg)
        {
            return;
        }

        pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
        pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_SMS;
        pMsg->MsgHeader.ulMsgName       = GMMSMS_SERVICE_STATUS_IND;            /* ԭ������                                 */

        ulServiceStatus    = ulTempServiceStatus;
        pMsg->enServiceSts = ulServiceStatus;

        ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                               /* ԭ�﷢��                                 */

        if (VOS_OK != ulRet)
        {
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndSmsServiceStatusInd:WARNING: Send msg fail.");
        }
    }

    return;
}
/*******************************************************************************
  Module   : Gmm_SndTcDataInd
  Function : ����ԭ��TCGMM_DATA_INDԭ��Ĵ���
  Input    : NAS_MSG_STRU *pTcMsg  Ҫ������Ϣ�ĵ�ָ��
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.06.18  �¹�����(TC��Ӧ)
    2. ��־��  2004.08.20  GMM_CHK_����_BUG_077
*******************************************************************************/
VOS_VOID Gmm_SndTcDataInd(
                      NAS_MSG_FOR_PCLINT_STRU          *pTcMsg
                      )
{
    VOS_UINT8                 i;                                                    /* ����ѭ�����Ʊ���                           */
    TCGMM_DATA_IND_STRU   *pMsg;                                                /* ������ʱ����                             */
    VOS_UINT32             ulRet;

    if (4 < pTcMsg->ulNasMsgSize)
    {
        pMsg = (TCGMM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
            (sizeof(TCGMM_DATA_IND_STRU) + pTcMsg->ulNasMsgSize) - 4);            /* �����ڴ�                                 */
    }
    else
    {
        pMsg = (TCGMM_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
            sizeof(TCGMM_DATA_IND_STRU));                                       /* �����ڴ�                                 */
    }
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    pMsg->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->MsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pMsg->MsgHeader.ulMsgName   = TCGMM_DATA_IND;                               /* ԭ������                                 */

    pMsg->RcvTcMsg.ulTcMsgSize = pTcMsg->ulNasMsgSize;                          /* ��д��Ϣ����                             */
    for (i=0; i<pTcMsg->ulNasMsgSize; i++)
    {
        pMsg->RcvTcMsg.aucTcMsg[i] = pTcMsg->aucNasMsg[i];                      /* ��д��Ϣ����                             */
    }

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pMsg);                                   /* ԭ�﷢��                                 */
    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndTcDataInd:WARNING: Send msg fail.");
    }
    return;
}

/*******************************************************************************
  Module   : Gmm_SndRrmmDataReqForCm
  Function : ����RRMM_DATA_REQԭ�ﴦ������CM����Ϣר�ã�
  Input    : VOS_UINT8          ucPriorityInd      ��Ϣ���ȼ�ָʾ
             NAS_MSG_STRU   *Msg               ��CN Domain��NAS��Ϣ�׵�ַ
  Output   : ��
  NOTE     : ��
  Return   : ��
  History  :
    1. ��־��  2004.07.06  �¹����ɣ�GMM_CHK_����_BUG_070��
*******************************************************************************/
VOS_VOID Gmm_SndRrmmDataReqForCm(
                             VOS_UINT8               ucPriorityInd,                 /* ��Ϣ���ȼ�ָʾ                           */
                             NAS_MSG_STRU        *pMsg                          /* ��CN Domain��NAS��Ϣ�׵�ַ               */
                            )
{
    VOS_INT32 lRet;
    /*V200R001,add,begin*/
    if (GMM_TRUE == GMM_IsCasGsmMode())
    {
        GMM_SndRrmmDataReqGsm(pMsg);
        return;
    }
    /*V200R001,add,end*/
    lRet = g_GmmImportFunc.RrmmDataReqFunc(RRC_NAS_PS_DOMAIN,
                                    ucPriorityInd,
                                    pMsg->ulNasMsgSize,
                                    (VOS_INT8 *)pMsg->aucNasMsg);                   /* ���÷��ͺ���                             */

    if (AS_SUCCESS != lRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndRrmmDataReqForCm:WARNING: Send msg fail.");
    }
    return;                                                                     /* ����                                     */
}

VOS_VOID Gmm_SndCcEmergencyNumberList(NAS_MML_EMERGENCY_NUM_LIST_STRU *pEmergencyList)
{
    GMMCC_EMERGENCY_LIST_STRU            *pEmcNumLst;                           /* ����ԭ������ָ��                         */
    VOS_UINT32                           ulRst;

    if (VOS_NULL_PTR == pEmergencyList)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndCcEmergencyNumberList:ERROR:Receive Null Pointer!");
        return;                                                                 /* ����                                     */
    }

    pEmcNumLst = (GMMCC_EMERGENCY_LIST_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                 sizeof(GMMCC_EMERGENCY_LIST_STRU));            /* �����ڴ�                                 */

    if (VOS_NULL_PTR == pEmcNumLst)
    {                                                                           /* �ڴ�����ʧ��                             */

        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndCcEmergencyNumberList:ERROR:MALLOC ERROR!");
        return;                                                                 /* ����                                     */
    }

    pEmcNumLst->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pEmcNumLst->MsgHeader.ulReceiverPid   = WUEPS_PID_CC;
    pEmcNumLst->MsgHeader.ulMsgName       = GMMCC_EMC_NUM_LST_IND;               /* ��Ϣ����                                 */

    pEmcNumLst->ulMcc                     = pEmergencyList->ulMcc;

    pEmcNumLst->ucEmergencyNumber = pEmergencyList->ucEmergencyNumber;

    PS_MEM_CPY(pEmcNumLst->astEmergencyLists, pEmergencyList->aucEmergencyList,
                ((pEmergencyList->ucEmergencyNumber) * sizeof(GMMCC_EMERGENCY_CONTENT_STRU)));

    if (0 == pEmergencyList->ucEmergencyNumber)
    {
        pEmcNumLst->ulMcc = 0XFFFFFFFF;
        PS_MEM_SET((VOS_VOID*)pEmcNumLst->astEmergencyLists,
                    0xFF,
                    GMMCC_EMERGENCY_NUMBER_LISTS_MAX_NUMBER * sizeof(NAS_MML_EMERGENCY_NUM_STRU));
    }

    ulRst = PS_SEND_MSG(WUEPS_PID_GMM, pEmcNumLst);

    if (VOS_OK != ulRst)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "Gmm_SndCcEmergencyNumberList:ERROR:Send Message ERROR!");
        return;
    }

    return;
}


VOS_VOID Gmm_SndMmcGprsServiceInd(
    NAS_MMC_GMM_GPRS_SERVICE_TYPE_ENUM_UINT32               enGprsServiceType
)
{
    MMCGMM_GPRS_SERVICE_IND_STRU       *pstMsg          = VOS_NULL_PTR;
    MMCGMM_GPRS_SERVICE_IND_STRU       *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_GPRS_SERVICE_IND_STRU);

    pstInternalMsg  = (MMCGMM_GPRS_SERVICE_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndMmcGprsServiceInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_GPRS_SERVICE_IND;

    pstMsg->enGprsServiceType             = enGprsServiceType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
VOS_UINT32  NAS_GMM_SndRrmmInterRatHandoverInfoReq( VOS_VOID )
{
    VOS_UINT32                              ulRet;
    RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU   *pSndMsg;

    pSndMsg = (RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_GMM,
                    sizeof(RRMM_INTER_RAT_HANDOVER_INFO_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pSndMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndRrmmInterRatHandoverInfoReq():Error: Failed in VOS_AllocMsg()");
        return VOS_ERR;
    }

    /* NAS��Ϣ������Ϣ������д */
    pSndMsg->MsgHeader.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pSndMsg->MsgHeader.ulReceiverPid    = WUEPS_PID_WRR;
    pSndMsg->MsgHeader.ulMsgName        = RRMM_INTER_RAT_HANDOVER_INFO_REQ;

    PS_MEM_SET(pSndMsg->aucReserve1, 0x00, sizeof(pSndMsg->aucReserve1));

    ulRet = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pSndMsg);

    if (VOS_OK != ulRet)
    {
        /* ��ӡ������Ϣ */
        NAS_ERROR_LOG(WUEPS_PID_GMM, "Gmm_SndRrmmInterRatHandoverInfoReq():Error: Failed in PS_SEND_MSG()");
        return VOS_ERR;
    }

    Gmm_TimerStart(GMM_TIMER_INTERRAT_HANDOVER_INFO_CNF);

    return VOS_OK;
}

#if   (FEATURE_ON == FEATURE_LTE)

/*****************************************************************************
 �� �� ��  : NAS_GMM_SndTinTypeToMmc
 ��������  : ֪ͨGMM��ǰTIN������
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��4��21��
    ��    ��   : zhoujun /40661
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  NAS_GMM_SndTinTypeToMmc(
    NAS_MML_TIN_TYPE_ENUM_UINT8         enTinType
)
{
    MMCGMM_TIN_TYPE_IND_STRU           *pstMsg          = VOS_NULL_PTR;
    MMCGMM_TIN_TYPE_IND_STRU           *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(MMCGMM_TIN_TYPE_IND_STRU);

    pstInternalMsg  = (MMCGMM_TIN_TYPE_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTinTypeToMmc,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = MMCGMM_TIN_TYPE_IND;
    pstMsg->enTinType                     = enTinType;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}

#endif
VOS_VOID NAS_GMM_SndMmLuInitiation(
    VOS_UINT32                          ulT3312TimeoutFlg
)
{
    GMMMM_LU_INITIATION_STRU           *pstMsg          = VOS_NULL_PTR;
    GMMMM_LU_INITIATION_STRU           *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_LU_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_LU_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmLuInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_LU_INITIATION;
    pstMsg->enTimerExpiredFlg             = ulT3312TimeoutFlg;
    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}
VOS_VOID NAS_GMM_SndMmCombinedAttachInitiation(VOS_VOID)
{
    GMMMM_COMBINED_ATTACH_INITIATION_STRU  *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_ATTACH_INITIATION_STRU  *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_COMBINED_ATTACH_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_ATTACH_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedAttachInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                            = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId                 = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid                   = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId               = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid                 = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength                      = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName                     = GMMMM_COMBINED_ATTACH_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}
VOS_VOID NAS_GMM_SndMmCombinedAttachAccept(
    VOS_UINT32                          ulAttachResult,                         /* ע����                                 */
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause,                                /* ʧ��ԭ��ֵ                               */
    NAS_MSG_FOR_PCLINT_STRU            *pNasMsg,                                /* NAS��Ϣ�׵�ַ                            */
    GMM_MSG_RESOLVE_STRU               *pAttachAcceptIe    /* IE�Ƿ���ڵ���Ϣ                         */
)
{
    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU    *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_ATTACH_ACCEPTED_STRU    *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_COMBINED_ATTACH_ACCEPTED_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_ATTACH_ACCEPTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedAttachAccept,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_ATTACH_ACCEPTED;
    pstMsg->enCause                       = enCause;
    pstMsg->enAttachResult                = ulAttachResult;

    if (GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG
        == (pAttachAcceptIe->ulOptionalIeMask
        & GMM_ATTACH_ACCEPT_IE_MS_IDENTITY_FLG))
    {                                                                           /* ��IE����                                 */
        Gmm_Com_DealOfMsId(&pNasMsg->aucNasMsg[pAttachAcceptIe->
                          aucIeOffset[GMM_ATTACH_ACCEPT_IE_MS_IDENTITY]],
                          (MMC_GMM_MS_IDENTITY_STRU*)&(pstMsg->stMsIdentity));                             /* ��дMS ID                                */
    }

    pstMsg->ulAttachAttCounter = g_GmmAttachCtrl.ucAttachAttmptCnt;

    if (GMMMM_ATTACH_RESLUT_PS_ONLY == ulAttachResult)
    {
        pstMsg->ulAttachAttCounter = g_GmmRauCtrl.ucRauAttmptCnt;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
VOS_VOID NAS_GMM_SndMmCombinedAttachRejected(
    VOS_UINT32                          ulCause                                          /* ʧ��ԭ��ֵ                               */
)
{
    GMMMM_COMBINED_ATTACH_REJECTED_STRU    *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_ATTACH_REJECTED_STRU    *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_COMBINED_ATTACH_REJECTED_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_ATTACH_REJECTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedAttachRejected,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_ATTACH_REJECTED;
    pstMsg->enCause                       = (VOS_UINT16)ulCause;
    pstMsg->ulAttachAttCounter            = g_GmmAttachCtrl.ucAttachAttmptCnt;

    if (( GMM_UNREAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg )
     && ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != ulCause ))
    {
        pstMsg->enCause = NAS_MML_REG_FAIL_CAUSE_NULL;
    }
    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}



VOS_VOID NAS_GMM_SndMmImsiDetachInitiation(VOS_VOID)
{
    GMMMM_IMSI_DETACH_INITIATION_STRU  *pstMsg          = VOS_NULL_PTR;
    GMMMM_IMSI_DETACH_INITIATION_STRU  *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_IMSI_DETACH_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_IMSI_DETACH_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmImsiDetachInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_IMSI_DETACH_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}
VOS_VOID NAS_GMM_SndMmImsiDetachComplete(VOS_VOID)
{
    GMMMM_IMSI_DETACH_COMPLETED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_IMSI_DETACH_COMPLETED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_IMSI_DETACH_COMPLETED_STRU);

    pstInternalMsg  = (GMMMM_IMSI_DETACH_COMPLETED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmImsiDetachComplete,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_IMSI_DETACH_COMPLETED;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}
VOS_VOID NAS_GMM_SndMmGprsDetachInitiation(VOS_VOID)
{
    GMMMM_GPRS_DETACH_INITIATION_STRU  *pstMsg          = VOS_NULL_PTR;
    GMMMM_GPRS_DETACH_INITIATION_STRU  *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_GPRS_DETACH_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_GPRS_DETACH_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmGprsDetachInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_GPRS_DETACH_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}
VOS_VOID NAS_GMM_SndMmGprsDetachComplete(VOS_VOID)
{
    GMMMM_GPRS_DETACH_COMPLETED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_GPRS_DETACH_COMPLETED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_GPRS_DETACH_COMPLETED_STRU);

    pstInternalMsg  = (GMMMM_GPRS_DETACH_COMPLETED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmGprsDetachComplete,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_GPRS_DETACH_COMPLETED;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}
VOS_VOID NAS_GMM_SndMmNetworkDetachInd(
    VOS_UINT8                           ucDetachType,                           /* detach����                               */
    VOS_UINT8                           ucDetachCause                           /* detachԭ��                               */
)
{
    GMMMM_NETWORK_DETACH_IND_STRU      *pstMsg          = VOS_NULL_PTR;
    GMMMM_NETWORK_DETACH_IND_STRU      *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_NETWORK_DETACH_IND_STRU);

    pstInternalMsg  = (GMMMM_NETWORK_DETACH_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmNetworkDetachInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_NETWORK_DETACH_IND;
    pstMsg->enDetachType                  = ucDetachType;                         /* ��дdetach����                           */
    pstMsg->ulDetachCause                 = ucDetachCause;                        /* ��дdetachԭ��                           */

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}
VOS_VOID NAS_GMM_SndMmGmmActionResultInd(
    VOS_UINT32                          ulActionResult,                     /* �������                                 */
    VOS_UINT32                          ulCause                             /* ����ʧ��ԭ��                             */
)
{
    GMMMM_GMM_ACTION_RESULT_IND_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_GMM_ACTION_RESULT_IND_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_GMM_ACTION_RESULT_IND_STRU);
    pstInternalMsg  = (GMMMM_GMM_ACTION_RESULT_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmGmmActionResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_GMM_ACTION_RESULT_IND;

    if(GMM_EVENT_CAUSE_INVALID != g_GmmGlobalCtrl.ucEventCause)
    {
        ulCause = g_GmmGlobalCtrl.ucEventCause;
    }

    pstMsg->ucAttCounter    = 0;

    switch (g_GmmGlobalCtrl.ucSpecProc & 0xF0)
    {                                                                           /* �жϵ�ǰspecific����                     */
        case 0x10:                                                                  /* ��ǰ��attch����                          */
            pstMsg->enGmmActionType = GMMMM_ACTION_ATTACH;                            /* action ����                              */
            pstMsg->ucAttCounter    = g_GmmAttachCtrl.ucAttachAttmptCnt;
            break;
        case 0x20:                                                                  /* ��ǰ��RAU����                            */
            pstMsg->enGmmActionType = GMMMM_ACTION_RAU;                               /* action ����                              */
            pstMsg->ucAttCounter    = g_GmmRauCtrl.ucRauAttmptCnt;
            break;
        case 0x40:                                                                  /* ��ǰ��sevice request����                 */
            pstMsg->enGmmActionType = GMMMM_ACTION_SR;                     /* action ����                              */
            break;
        default:
            PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "Gmm_SndMmcGmmActionResultInd:WARNING: Current procedure error");
            return;
    }

    pstMsg->enActionResult  = ulActionResult;
    pstMsg->enCause         = (VOS_UINT16)ulCause;                                /* actionԭ��                               */

    if(GMM_UNREAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg)
    {
        pstMsg->enCause      = NAS_MML_REG_FAIL_CAUSE_NULL;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;
}
VOS_VOID NAS_GMM_SndMmCombinedRauInitiation(VOS_VOID)
{
    GMMMM_COMBINED_RAU_INITIATION_STRU *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_INITIATION_STRU *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_COMBINED_RAU_INITIATION_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_RAU_INITIATION_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedRauInitiation,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_RAU_INITIATION;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}
VOS_VOID NAS_GMM_SndMmCombinedRauAccept(
    VOS_UINT32                          ulRauResult,                            /* ���½��                                 */
    VOS_UINT32                          ulCause,                                /* ����ʧ��ԭ��                             */
    NAS_MSG_FOR_PCLINT_STRU            *pstNasMsg,
    GMM_MSG_RESOLVE_STRU               *pstRauAcceptIe                            /* IE�Ƿ���ڵ���Ϣ                         */
)
{
    GMMMM_COMBINED_RAU_ACCEPTED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_ACCEPTED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_COMBINED_RAU_ACCEPTED_STRU);

    pstInternalMsg  = (GMMMM_COMBINED_RAU_ACCEPTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedRauAccept,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_COMBINED_RAU_ACCEPTED;
    pstMsg->enRauResult                   = ulRauResult;                          /* ��д���½��                             */
    pstMsg->enCause                       = (VOS_UINT16)ulCause;                  /* ��д����ʧ��ԭ��                         */

    pstMsg->stMsIdentity.enMsIdType       = 0;

    if ((GMM_REAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg)
     && (VOS_NULL_PTR != pstRauAcceptIe))
    {                                                                           /* ��ǰΪ������                             */
        if (GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG
            == (pstRauAcceptIe->ulOptionalIeMask
            & GMM_RAU_ACCEPT_IE_MS_IDENTITY_FLG))
        {                                                                       /* ��IE����                                 */
            Gmm_Com_DealOfMsId(&pstNasMsg->aucNasMsg[pstRauAcceptIe->aucIeOffset
                               [GMM_RAU_ACCEPT_IE_MS_IDENTITY]],
                               (MMC_GMM_MS_IDENTITY_STRU*)&(pstMsg->stMsIdentity));                          /* ��дMS ID                                */
        }
    }

    pstMsg->ulRauAttCounter = g_GmmRauCtrl.ucRauAttmptCnt;                        /* ��дRAU attempt counterֵ                */

    pstMsg->enRealProFlg    = g_GmmGlobalCtrl.ucRealProFlg;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}


VOS_VOID NAS_GMM_SndMmCombinedRauRejected(
    VOS_UINT32                          ulCause
)
{
    GMMMM_COMBINED_RAU_REJECTED_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_COMBINED_RAU_REJECTED_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_COMBINED_RAU_REJECTED_STRU);
    pstInternalMsg  = (GMMMM_COMBINED_RAU_REJECTED_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmCombinedRauRejected,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                  = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid       = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName           = GMMMM_COMBINED_RAU_REJECTED;

    pstMsg->enCause                         = (VOS_UINT16)ulCause;                  /* ��д����ʧ��ԭ��                         */
    pstMsg->ulRauAttCounter                 = g_GmmRauCtrl.ucRauAttmptCnt;          /* ��дRAU attempt counterֵ                */
    pstMsg->enRealProFlg                    = g_GmmGlobalCtrl.ucRealProFlg;         /* ��д�������                             */

    if ((GMM_UNREAL_PROCEDURE == g_GmmGlobalCtrl.ucRealProFlg)
     && ( NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE_REG_MAX_TIMES != ulCause ))
    {
        pstMsg->enCause  = NAS_MML_REG_FAIL_CAUSE_NULL;                                          /* ��д����ʧ��ԭ��                         */
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

}
VOS_VOID NAS_GMM_SndMmAuthenticationFailureInd(VOS_VOID)
{
    GMMMM_AUTHENTICATON_FAILURE_IND_STRU   *pstMsg          = VOS_NULL_PTR;
    GMMMM_AUTHENTICATON_FAILURE_IND_STRU   *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMM_AUTHENTICATON_FAILURE_IND_STRU);

    pstInternalMsg  = (GMMMM_AUTHENTICATON_FAILURE_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmAuthenticationFailureInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    pstMsg->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid     = WUEPS_PID_MM;
    pstMsg->stMsgHeader.ulLength          = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->stMsgHeader.ulMsgName         = GMMMM_AUTHENTICATON_FAILURE_IND;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);

    return;

}
VOS_UINT32 NAS_GMM_IsCausePsOnlySucc_CombineReg(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    if ( (NAS_MML_REG_FAIL_CAUSE_MSC_UNREACHABLE       == enCause)
       || (NAS_MML_REG_FAIL_CAUSE_NETWORK_FAILURE      == enCause)
       || (NAS_MML_REG_FAIL_CAUSE_PROCEDURE_CONGESTION == enCause)
       || (NAS_MML_REG_FAIL_CAUSE_IMSI_UNKNOWN_IN_HLR  == enCause))
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}


GMM_MMC_REG_DOMAIN_ENUM_UINT32 NAS_GMM_GetRegRsltDomain(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause

)
{
    GMM_MMC_REG_DOMAIN_ENUM_UINT32  enRlstDomain;

    if ((GMM_MMC_ACTION_COMBINED_RAU == enActionType)
      || (GMM_MMC_ACTION_COMBINED_ATTACH == enActionType))
    {

        if (GMM_MMC_ACTION_RESULT_SUCCESS == enActionResult)
        {
            if (VOS_TRUE == NAS_GMM_IsCausePsOnlySucc_CombineReg(enCause))
            {
                enRlstDomain = GMM_MMC_REG_DOMAIN_PS;
            }
            else
            {
                enRlstDomain = GMM_MMC_REG_DOMAIN_PS_CS;
            }
        }
        else
        {
            enRlstDomain = GMM_MMC_REG_DOMAIN_PS_CS;
        }
    }
    else
    {
        enRlstDomain = GMM_MMC_REG_DOMAIN_PS;
    }

    return enRlstDomain;

}


VOS_VOID NAS_GMM_SndMmcPsRegResultInd(
    GMM_MMC_ACTION_TYPE_ENUM_U32        enActionType,
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstMsg          = VOS_NULL_PTR;
    GMMMMC_PS_REG_RESULT_IND_STRU      *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                          ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMMC_PS_REG_RESULT_IND_STRU);

    pstInternalMsg  = (GMMMMC_PS_REG_RESULT_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcPsRegResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ���IEֵ */
    pstMsg                                = pstInternalMsg;
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = GMMMMC_PS_REG_RESULT_IND;
    pstMsg->enGmmActionType               = enActionType;
    pstMsg->enActionResult                = enActionResult;
    pstMsg->enRegFailCause                = enCause;
    pstMsg->enNetType                     = NAS_MML_GetCurrNetRatType();
    pstMsg->ulServiceStatus               = Gmm_ComServiceSts();

    pstMsg->enReqDomain                   = GMM_MMC_REG_DOMAIN_PS;

    if (GMM_MMC_ACTION_RAU == enActionType)
    {
        pstMsg->ulRegCounter = g_GmmRauCtrl.ucRauAttmptCnt;

        /* ���ݵ�ǰ��ע�����;����Ƿ�Ϊ����RAU */
        if ((GMM_RAU_COMBINED          == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_RAU_WITH_IMSI_ATTACH  == g_GmmGlobalCtrl.ucSpecProc))
        {
            pstMsg->enGmmActionType  = GMM_MMC_ACTION_COMBINED_RAU;

            pstMsg->enReqDomain      = GMM_MMC_REG_DOMAIN_PS_CS;

        }
    }
    else
    {
        pstMsg->ulRegCounter = g_GmmAttachCtrl.ucAttachAttmptCnt;

        /* ���ݵ�ǰ��ע�����;����Ƿ�Ϊ����ATTACH */
        if ((GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
         || (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc))
        {
            pstMsg->enGmmActionType  = GMM_MMC_ACTION_COMBINED_ATTACH;

            pstMsg->enReqDomain      = GMM_MMC_REG_DOMAIN_PS_CS;

        }
    }

    if ( (GMM_MMC_ACTION_PROC_FALSE == g_GmmGlobalCtrl.ucRealProFlg)
      && (GMM_MMC_ACTION_RESULT_SUCCESS == pstMsg->enActionResult))
    {
        /* RAU succ�����̿��ܴ�ԭ��ֵNAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC */
        /* ����NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC������ԭ��ֵ����ΪNAS_MML_REG_FAIL_CAUSE_LOCAL_NULL */
        if (NAS_MML_REG_FAIL_CAUSE_INTER_RAT_CHANGE_SUCC != enCause)
        {
            pstMsg->enRegFailCause = NAS_MML_REG_FAIL_CAUSE_LOCAL_NULL;
        }
    }


    pstMsg->enRsltDomain = NAS_GMM_GetRegRsltDomain(pstMsg->enGmmActionType,
                                                    pstMsg->enActionResult,
                                                    pstMsg->enRegFailCause);


    /* ������RAU��Ҫ֪ͨLMM */
    if ((GMM_TRUE == g_GmmRauCtrl.ucPeriodicRauFlg)
     && (GMM_MMC_ACTION_RAU == enActionType))
    {
        pstMsg->enGmmActionType  = GMM_MMC_ACTION_PERIODC_RAU;
    }

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}

VOS_VOID NAS_GMM_SndMmcServiceRequestResultInd(
    GMM_MMC_ACTION_RESULT_ENUM_U32      enActionResult,
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU *pstMsg          = VOS_NULL_PTR;
    GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU *pstInternalMsg  = VOS_NULL_PTR;
    VOS_UINT32                              ulLen;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    ulLen           = sizeof(GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU);
    pstInternalMsg  = (GMMMMC_SERVICE_REQUEST_RESULT_IND_STRU*)NAS_MML_GetIntMsgSendBuf(ulLen);
    if ( VOS_NULL_PTR == pstInternalMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcServiceRequestResultInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    pstMsg                                = pstInternalMsg;
    /* ���IEֵ */
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = ulLen - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = GMMMMC_SERVICE_REQUEST_RESULT_IND;
    pstMsg->enActionResult                = enActionResult;                       /* ��дdetachԭ��                           */
    pstMsg->enRegFailCause                = enCause;
    pstMsg->ulServiceSts                  = Gmm_ComServiceSts();

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}
VOS_VOID NAS_GMM_SndMmcMmDetachInfo()
{
    NAS_MML_CAMP_PLMN_INFO_STRU        *pstCampInfo;

    /* ��ȡ��ǰ����ģʽ */
    pstCampInfo     = NAS_MML_GetCurrCampPlmnInfo();

    if (NAS_MML_NET_MODE_I == pstCampInfo->enNetworkMode)
    {
        /* ����ģʽI��,PS DETACH��־����,��MMC����DETACH CNF��ͬʱ��MM����GprsDetachComplete */
        if (GMM_WAIT_PS_DETACH ==
            (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
        {
            NAS_GMM_SndMmGprsDetachComplete();

            /* MMC��Ҫ֪��detach���ͣ�����ȷ���Ȼ�����detach���� */
            NAS_GMM_SndMmcDetachCnf();

            g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_PS_DETACH;


            /* GMMֹͣPS���DETACH������ʱ�� */
            Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);
        }

        /* ����ģʽI��,CS DETACH��־����,��MM����ImsiDetachComplete */
        if (GMM_WAIT_CS_DETACH ==
            (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_CS_DETACH) )
        {
            NAS_GMM_SndMmImsiDetachComplete();
            g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_CS_DETACH;
        }
    }
    else
    {
        /* ����ģʽII��,PS DETACH��־����,��MMC����DETACH CNF */
        if (GMM_WAIT_PS_DETACH ==
            (g_GmmGlobalCtrl.stDetachInfo.enDetachType & GMM_WAIT_PS_DETACH) )
        {
            NAS_GMM_SndMmcDetachCnf();
            g_GmmGlobalCtrl.stDetachInfo.enDetachType &= ~GMM_WAIT_PS_DETACH;


            /* GMMֹͣPS���DETACH������ʱ�� */
            Gmm_TimerStop(GMM_TIMER_PROTECT_PS_DETACH);
        }
    }

    g_GmmDetachCtrl.ucT3321OutCnt = 0;
}
VOS_VOID NAS_GMM_SndMmcActionResultIndWhenBarorNotSupportGprs(
    NAS_MML_REG_FAIL_CAUSE_ENUM_UINT16  enCause
)
{
    VOS_UINT8                               ucOldSpecProc;

    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;

    if ( (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
      || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);
    }
    else
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

        /* ��MMC����PSע���� */
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     enCause);
    }
    g_GmmGlobalCtrl.ucSpecProc = ucOldSpecProc;
    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;
    return;
}


VOS_VOID NAS_GMM_SndMmcActionResultIndWhenInForbiddenList(
    VOS_UINT32                          ulForbiddenMask
)
{
    VOS_UINT8                           ucOldSpecProc;
    VOS_UINT32                          ulCause;

    g_GmmGlobalCtrl.ucRealProFlg = GMM_UNREAL_PROCEDURE;
    ucOldSpecProc = g_GmmGlobalCtrl.ucSpecProc;

    if ( MMC_GMM_NO_FORBIDDEN == ulForbiddenMask )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }
    else if ( MMC_GMM_FORBIDDEN_PLMN == (ulForbiddenMask & MMC_GMM_FORBIDDEN_PLMN) )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN;
    }
    else if ( MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS ==  (ulForbiddenMask & MMC_GMM_FORBIDDEN_PLMN_FOR_GPRS ) )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_PLMN_FOR_GPRS;
    }
    else if ( MMC_GMM_FORBIDDEN_LA_FOR_ROAM == (ulForbiddenMask & MMC_GMM_FORBIDDEN_LA_FOR_ROAM )  )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_ROAM;
    }
    else if ( MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS == (ulForbiddenMask & MMC_GMM_FORBIDDEN_LA_FOR_REG_PRVS_SVS )  )
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_FORBIDDEN_LA_FOR_REG_PRVS_SVS;
    }
    else
    {
        ulCause = NAS_MML_REG_FAIL_CAUSE_OTHER_CAUSE;
    }


    if ( (0x10 == (g_GmmGlobalCtrl.ucState & 0xF0))
      || (GMM_REGISTERED_INITIATED == g_GmmGlobalCtrl.ucState) )
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_ATTACH_NORMAL;
        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_ATTACH,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     (VOS_UINT16)ulCause);
    }
    else
    {
        g_GmmGlobalCtrl.ucSpecProc = GMM_RAU_NORMAL;

        NAS_GMM_SndMmcPsRegResultInd(GMM_MMC_ACTION_RAU,
                                     GMM_MMC_ACTION_RESULT_FAILURE,
                                     (VOS_UINT16)ulCause);
    }

    g_GmmGlobalCtrl.ucSpecProc   = ucOldSpecProc;
    g_GmmGlobalCtrl.ucRealProFlg = GMM_REAL_PROCEDURE;

    return;
}



VOS_VOID NAS_GMM_SndTcRrRelInd(VOS_VOID)
{
    TCGMM_RR_REL_IND_STRU              *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ */
    pstMsg = (TCGMM_RR_REL_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                                  sizeof(TCGMM_RR_REL_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_MM, "NAS_GMM_SndTcRrRelInd,ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��װ��Ϣ */
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pstMsg->stMsgHeader.ulLength        = sizeof(TCGMM_RR_REL_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = TCGMM_RR_REL_IND;

    /* ������Ϣ */
    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);
    if( VOS_OK != ulRet )
    {
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTcRrRelInd,WARNING: Message sends fail");
        return;
    }
}
VOS_VOID NAS_GMM_SndTcHandoverInd(VOS_VOID)
{
    TCGMM_HANDOVER_IND_STRU            *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;

    /* ������Ϣ */
    pstMsg = (TCGMM_HANDOVER_IND_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                               sizeof(TCGMM_HANDOVER_IND_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTcHandoverInd():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    /* ��װ��Ϣ */
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_TC;
    pstMsg->stMsgHeader.ulLength        = sizeof(TCGMM_HANDOVER_IND_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = TCGMM_HANDOVER_IND;

    pstMsg->enNetRat = NAS_MML_GetCurrNetRatType();

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);
    if (VOS_OK != ulRet)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndTcHandoverInd():WARNING:GMM SEND TC handover failed!");
    }

    return;
}
VOS_VOID NAS_GMM_SndRabmMmlProcStatusQryCnf(
    RABM_GMM_MML_PROC_STATUS_STRU     *pstMmlProcStatus
)
{
    GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU      *pstMsg = VOS_NULL_PTR;
    VOS_UINT32                                  ulRet;

    /* ������Ϣ */
    pstMsg = (GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU*)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                                               sizeof(GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndRabmMmlProcStatusQryCnf():ERROR:Memory Alloc Error for pstMsg");
        return;
    }

    /* ��װ��Ϣ */
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_RABM;
    pstMsg->stMsgHeader.ulLength        = sizeof(GMM_RABM_MML_PROC_STATUS_QRY_CNF_STRU) - VOS_MSG_HEAD_LENGTH;

    pstMsg->stMsgHeader.ulMsgName       = ID_GMM_RABM_MML_PROC_STATUS_QRY_CNF;

    pstMsg->stMmlProcStatus = *pstMmlProcStatus;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);
    if (VOS_OK != ulRet)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndRabmMmlProcStatusQryCnf():WARNING:GMM SEND MSG failed!");
    }

    return;
}
VOS_VOID NAS_GMM_SndMmcCipherInfoInd(VOS_VOID)
{
    MMC_GMM_CIPHER_INFO_IND_STRU       *pstMsg          = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg  = (MMC_GMM_CIPHER_INFO_IND_STRU*)NAS_MML_GetIntMsgSendBuf(sizeof(MMC_GMM_CIPHER_INFO_IND_STRU));
    if ( VOS_NULL_PTR == pstMsg)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndMmcCipherInfoInd: ERROR:ALLOC BUFFER WRONG!");
        return;
    }

    /* ��д��Ϣͷ */
    pstMsg->MsgHeader.ulSenderCpuId       = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid         = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid       = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength            = sizeof(MMC_GMM_CIPHER_INFO_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName           = GMMMMC_CIPHER_INFO_IND;

    pstMsg->ucGprsCipher                  = gstGmmCasGlobalCtrl.ucGprsCipher;
    pstMsg->ucGprsCipherAlg               = gstGmmCasGlobalCtrl.ucGprsCipherAlg;

    NAS_MML_SndInternalMsg((VOS_VOID*)pstMsg);
}


VOS_VOID NAS_GMM_SndSmSigConnInd(VOS_VOID)
{
    GMMSM_SIG_CONN_IND_STRU            *pstMsg;
    VOS_UINT32                          ulRet;

    pstMsg = (GMMSM_SIG_CONN_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_GMM,
                          sizeof(GMMSM_SIG_CONN_IND_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_ERROR, "NAS_GMM_SndSmSigConnInd:WARNING: Memory Alloc Fail.");
        return;
    }

    pstMsg->stMsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.ulSenderPid     = WUEPS_PID_GMM;
    pstMsg->stMsgHeader.ulReceiverPid   = WUEPS_PID_SM;

    pstMsg->stMsgHeader.ulMsgName       = GMMSM_SIG_CONN_IND;

    ulRet = PS_SEND_MSG(WUEPS_PID_GMM, pstMsg);

    if (VOS_OK != ulRet)
    {
        PS_NAS_LOG(WUEPS_PID_GMM, VOS_NULL, PS_LOG_LEVEL_WARNING, "NAS_GMM_SndSmSigConnInd:WARNING: Send msg Fail.");
    }

    return;
}


NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16 NAS_GMM_ConvertUsimAuthFailInfo(
    USIMM_AUTH_RESULT_ENUM_UINT32    enSimFailValue
)
{
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16 enRptSimFailValue;
    enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_NULL;

    switch (enSimFailValue)
    {
        case USIMM_AUTH_MAC_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_MAC_FAILURE;
            break;
        case USIMM_AUTH_SYNC_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_SYNC_FAILURE;
            break;
        case USIMM_AUTH_UMTS_OTHER_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE;
            break;
        case USIMM_AUTH_GSM_OTHER_FAILURE:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_GSM_OTHER_FAILURE;
            break;
        default:
            enRptSimFailValue = NAS_MML_SIM_AUTH_FAIL_UMTS_OTHER_FAILURE;
            break;
    }

    return enRptSimFailValue;
}


VOS_VOID NAS_GMM_SndMmcSimAuthFailInfo(
    NAS_MML_SIM_AUTH_FAIL_ENUM_UINT16  enSimAuthFailValue
)
{
    MMCGMM_SIM_AUTH_FAIL_IND_STRU      *pstMsg              = VOS_NULL_PTR;

    /* ���ڲ���Ϣ�����л�ȡһ����û��ʹ�õĿռ� */
    pstMsg  = (MMCGMM_SIM_AUTH_FAIL_IND_STRU *)NAS_MML_GetIntMsgSendBuf(sizeof(MMCGMM_SIM_AUTH_FAIL_IND_STRU));

    if ( VOS_NULL_PTR == pstMsg)
    {
        return;
    }

    pstMsg->MsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstMsg->MsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstMsg->MsgHeader.ulReceiverPid     = WUEPS_PID_MMC;
    pstMsg->MsgHeader.ulLength          = sizeof(MMCGMM_SIM_AUTH_FAIL_IND_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg->MsgHeader.ulMsgName         = MMCGMM_SIM_AUTH_FAIL_IND;
    pstMsg->ucReservel                  = 0;

    pstMsg->enSimAuthFailValue          = enSimAuthFailValue;
    pstMsg->enSrvDomain                 = MM_COM_SRVDOMAIN_PS;

    if ((GMM_RAU_COMBINED               == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_RAU_WITH_IMSI_ATTACH       == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_ATTACH_WHILE_IMSI_ATTACHED == g_GmmGlobalCtrl.ucSpecProc)
     || (GMM_ATTACH_COMBINED            == g_GmmGlobalCtrl.ucSpecProc))
    {
        pstMsg->enSrvDomain             = MM_COM_SRVDOMAIN_CS_PS;
    }

    NAS_MML_SndInternalMsg(pstMsg);

    return;
}

#if(FEATURE_ON == FEATURE_DSDS)
VOS_VOID NAS_GMM_SndAsBeginSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType
)
{
    VOS_UINT32                          ulResult;
    RRMM_BEGIN_SESSION_NOTIFY_STRU     *pstBeginSessionNotify = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    pstBeginSessionNotify       = (RRMM_BEGIN_SESSION_NOTIFY_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                                                                        sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstBeginSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsBeginSessionNotify(): Alloc msg fail!");
        return;
    }

    /* �ṹ������ */
    PS_MEM_SET((VOS_INT8*)pstBeginSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_BEGIN_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ������Ϣ�ṹ�� */
    pstBeginSessionNotify->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstBeginSessionNotify->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstBeginSessionNotify->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstBeginSessionNotify->stMsgHeader.ulMsgName         = RRMM_BEGIN_SESSION_NOTIFY;

    pstBeginSessionNotify->enSessionType                 = enSessionType;

    /* ����VOS����ԭ�� */
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstBeginSessionNotify);

    if(VOS_OK != ulResult)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsBeginSessionNotify():WARNING:MMC SEND AS BEGIN SESSION FAILED!");
        return;
    }

    return;
}
VOS_VOID NAS_GMM_SndAsEndSessionNotify(
    VOS_UINT32                          ulReceiverPid,
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enSessionType,
    VOS_UINT32                          ulDelayTime
)
{
    VOS_UINT32                          ulResult;
    RRMM_END_SESSION_NOTIFY_STRU       *pstEndSessionNotify = VOS_NULL_PTR;

    /* ������Ϣ�ṹ�ڴ� */
    pstEndSessionNotify       = (RRMM_END_SESSION_NOTIFY_STRU*)PS_ALLOC_MSG(WUEPS_PID_GMM,
                                                                        sizeof(RRMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);
    if (VOS_NULL_PTR == pstEndSessionNotify)
    {
        NAS_ERROR_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsEndSessionNotify(): Alloc msg fail!");
        return;
    }

    /* �ṹ������ */
    PS_MEM_SET((VOS_INT8*)pstEndSessionNotify + VOS_MSG_HEAD_LENGTH, 0,
                    sizeof(RRMM_END_SESSION_NOTIFY_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ������Ϣ�ṹ�� */
    pstEndSessionNotify->stMsgHeader.ulSenderCpuId     = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulSenderPid       = WUEPS_PID_GMM;
    pstEndSessionNotify->stMsgHeader.ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pstEndSessionNotify->stMsgHeader.ulReceiverPid     = ulReceiverPid;
    pstEndSessionNotify->stMsgHeader.ulMsgName         = RRMM_END_SESSION_NOTIFY;
    pstEndSessionNotify->enSessionType                 = enSessionType;
    pstEndSessionNotify->enCsRelAll                    = VOS_FALSE;
    pstEndSessionNotify->enPsRelAll                    = VOS_FALSE;
    pstEndSessionNotify->ulDelayTime                   = ulDelayTime;

    /* ����VOS����ԭ�� */
    ulResult = NAS_UTRANCTRL_SndAsMsg(WUEPS_PID_GMM, (struct MsgCB **)&pstEndSessionNotify);

    if(VOS_OK != ulResult)
    {
        /* ����ʧ�� */
        NAS_WARNING_LOG(WUEPS_PID_GMM, "NAS_GMM_SndAsEndSessionNotify():WARNING:MMC SEND AS END SESSION failed!");
        return;
    }

    return;
}
VOS_VOID NAS_GMM_SndBeginSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                       stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8         enMtcSessionType;

#if(FEATURE_ON == FEATURE_LTE)
    GMM_LMM_SESSION_TYPE_ENUM_UINT8     enLmmSessionType;
#endif

    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));


    /* ƽ̨֧��W/TD������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_GMM_SndAsBeginSessionNotify(WUEPS_PID_WRR, enRrcSessionType);
    }

    /* ƽ̨֧��G������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_GMM_SndAsBeginSessionNotify(UEPS_PID_GAS, enRrcSessionType);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_GMM_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* ƽ̨֧��LTE������end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_GMM_SndLmmBeginSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* ��дCTLͷ */
        stCtrl.ulModuleId = WUEPS_PID_GMM;

        MTC_SetBeginSessionInfo(&stCtrl,enMtcSessionType);
    }

    return;
}


VOS_VOID NAS_GMM_SndEndSessionNotify(
    RRC_NAS_SESSION_TYPE_ENUM_UINT8     enRrcSessionType
)
{
    TAF_CTRL_STRU                                           stCtrl;
    MTC_SESSION_TYPE_ENUM_UINT8                             enMtcSessionType;

    NAS_MML_DSDS_END_SESSION_DELAY_STRU                    *pstEndDelay = VOS_NULL_PTR;
    VOS_UINT32                                              ulDelayTime;
#if(FEATURE_ON == FEATURE_LTE)
    GMM_LMM_SESSION_TYPE_ENUM_UINT8                         enLmmSessionType;
#endif

    enMtcSessionType = MTC_SESSION_TYPE_BUTT;
    PS_MEM_SET(&stCtrl, 0x0, sizeof(stCtrl));
    pstEndDelay = NAS_MML_GetDsdsSessionEndDelay();

    if ((RRC_NAS_SESSION_TYPE_PS_ATTACH == enRrcSessionType)
     || (RRC_NAS_SESSION_TYPE_PS_RAU    == enRrcSessionType))
    {
        ulDelayTime = pstEndDelay->ulPsRegEndSessionDelayTime;
    }
    else
    {
        ulDelayTime = 0;
    }

    /* ƽ̨֧��W/TD������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportUtran())
    {
        NAS_GMM_SndAsEndSessionNotify(WUEPS_PID_WRR, enRrcSessionType, ulDelayTime);
    }

    /* ƽ̨֧��G������end session */
    if (VOS_TRUE == NAS_MML_IsPlatformSupportGsm())
    {
        NAS_GMM_SndAsEndSessionNotify(UEPS_PID_GAS, enRrcSessionType, ulDelayTime);
    }

#if(FEATURE_ON == FEATURE_LTE)
    NAS_GMM_ConvertRrcSessionTypeToLmmFormat(enRrcSessionType, &enLmmSessionType);

    /* ƽ̨֧��LTE������end session */
    if ( VOS_TRUE == NAS_MML_IsPlatformSupportLte() )
    {
        NAS_GMM_SndLmmEndSessionNotify(enLmmSessionType);
    }
#endif

    if(VOS_OK == NAS_ConvertSessionTypeToMTCFormat(enRrcSessionType, &enMtcSessionType))
    {
        /* ��дCTLͷ */
        stCtrl.ulModuleId = WUEPS_PID_GMM;

        MTC_SetEndSessionInfo(&stCtrl,enMtcSessionType);
    }

    return;
}
VOS_VOID NAS_GMM_NotifySessionAccordingStateChg(
    VOS_UINT8                           ucCurState,
    VOS_UINT8                           ucTargetState
)
{
    if ( ucCurState == ucTargetState )
    {
        return;
    }

    /* ��ǰ״̬��GMM_REGISTERED_INITIATED��Ŀ��״̬����GMM_REGISTERED_INITIATED��
       ����ΪPS ATTACH���̽��������ͷ���Դ */
    if ( GMM_REGISTERED_INITIATED == ucCurState )
    {

        /* ע�ᱻ�ܻ��Ȩ���ܣ����µ�ATTACH����ʱ��ֱ�ӷ���end session */
        NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);

        /* GMM����ATTACHע��ʱ������detach PS���跢��BEGIN�������ʱ����CSȥע��
           ֱ����MMģ����У�RAU�Ļ���Э������ȷ�涨���棬��RAU����֮���ٷ��� */
        if ( GMM_DEREGISTERED_INITIATED == ucTargetState )
        {
            /* ��״̬ΪĿ��״̬ʱ����ʾPS DETACH�������ڽ��� */
            NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);
        }

        return;
    }

    if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucCurState )
    {
        NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);

        return;
    }

    if ( GMM_REGISTERED_INITIATED == ucTargetState )
    {
        /* ��״̬ΪĿ��״̬ʱ����ʾPS attach�������ڽ��� */
        NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_ATTACH);

        return;
    }

    if ( GMM_ROUTING_AREA_UPDATING_INITIATED == ucTargetState )
    {
        /* ��״̬ΪĿ��״̬ʱ����ʾPS RAU�������ڽ��� */
        NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_RAU);

        return;
    }

    if ( (GMM_DEREGISTERED_INITIATED == ucCurState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == ucCurState) )
    {
        /* ��״̬ΪĿ��״̬ʱ����ʾPS DETACH�������ڽ��� */
        NAS_GMM_SndEndSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);

        return;
    }

    if ( (GMM_DEREGISTERED_INITIATED == ucTargetState)
      || (GMM_REGISTERED_IMSI_DETACH_INITIATED == ucTargetState) )
    {
        /* ��״̬ΪĿ��״̬ʱ����ʾPS DETACH�������ڽ��� */
        NAS_GMM_SndBeginSessionNotify(RRC_NAS_SESSION_TYPE_PS_DETACH);

        return;
    }

    return;
}

#endif
/*lint -restore */

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


