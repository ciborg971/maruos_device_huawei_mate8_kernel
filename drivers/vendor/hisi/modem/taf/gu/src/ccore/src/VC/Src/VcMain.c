

/*****************************************************************************
   1 ͷ�ļ�����
*****************************************************************************/
#include "VcMain.h"
#include "VcCallInterface.h"
#include "VcPhyInterface.h"
#include "VcComm.h"
#include "MnComm.h"
#include "MnErrorCode.h"
#include "product_config.h"
#include "AppVcApi.h"
#include "OmApi.h"
#include "MM_Share_inc.h"
#include "apminterface.h"
#include "TafOamInterface.h"
#include "VcCodecInterface.h"
#include "VcCtx.h"
#include "VcProcNvim.h"
#include "NVIM_Interface.h"
#include "NasNvInterface.h"
#include "TafNvInterface.h"
#if (FEATURE_ON == FEATURE_IMS)
#include "VcImsaInterface.h"
#endif
#if (FEATURE_ON == FEATURE_PTM)
#include "NasComm.h"
#include "TafSdcCtx.h"
#endif
#include "TafSdcLib.h"
#include "VcMntn.h"


#ifdef  __cplusplus
  #if  __cplusplus
      extern "C"{
  #endif
#endif


/*lint -e958*/

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_VC_MAIN_C
/*lint +e767*/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
extern APP_VC_STATE_MGMT_STRU           g_stVcStateMgmt;


#if (FEATURE_HIFI == FEATURE_ON)
VOS_UINT32                                  g_Vc_VoiceOpenFlg = VOS_TRUE;
#else
VOS_UINT32                                  g_Vc_VoiceOpenFlg = VOS_FALSE;
#endif

/*****************************************************************************
   3 ����ʵ��
*****************************************************************************/
extern VOS_VOID APP_VC_ReadNvimInfo(VOS_VOID);

/*****************************************************************************
 �� �� ��  : APP_VC_GetTTYMode
 ��������  : ��ȡ��ǰTTY MODE
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޶���¼  :
  1. ��    ��   : 2015��02��07��
     ��    ��   : w00316404
     �޸�����   : ��������
*****************************************************************************/
TAF_VC_TTYMODE_ENUM_UINT8 APP_VC_GetTTYMode(VOS_VOID)
{
    TAF_NV_TTY_CFG_STRU                 stTTYCfgStru;

    /* ������ʼ�� */
    PS_MEM_SET(&stTTYCfgStru, 0x00, sizeof(TAF_NV_TTY_CFG_STRU));

    /* ��ȡNV�� */
    if (NV_OK != NV_Read(en_NV_Item_TTY_Mode,
                         &stTTYCfgStru,
                         sizeof(TAF_NV_TTY_CFG_STRU)))
    {
        return TAF_VC_TTYMODE_BUTT;
    }

    if ( stTTYCfgStru.ucTTYMode >= TAF_VC_TTYMODE_BUTT )
    {
        return TAF_VC_TTYMODE_BUTT;
    }

    return (TAF_VC_TTYMODE_ENUM_UINT8)stTTYCfgStru.ucTTYMode;
}

/*****************************************************************************
 �� �� ��  : APP_VC_SetTTYMode
 ��������  : ����TTY MODE
 �������  : TTYģʽ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޶���¼  :
  1. ��    ��   : 2015��02��07��
     ��    ��   : w00316404
     �޸�����   : ��������
*****************************************************************************/
VOS_UINT32 APP_VC_SetTTYMode(TAF_VC_TTYMODE_ENUM_UINT8 enTTYMode)
{
    TAF_NV_TTY_CFG_STRU                 stTTYCfgStru;

    /* ������ʼ�� */
    PS_MEM_SET(&stTTYCfgStru, 0x00, sizeof(TAF_NV_TTY_CFG_STRU));

    /* ����NV�� */
    stTTYCfgStru.ucTTYMode = enTTYMode;

    if (NV_OK != NV_Write(en_NV_Item_TTY_Mode, &stTTYCfgStru, sizeof(TAF_NV_TTY_CFG_STRU)))
    {
        VC_ERR_LOG("TAF_VC_SetTTYMode: Write en_NV_Item_TTY_Mode failed!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : TAF_VC_InitTTYMode
 ��������  : ��ʼ��TTY MODE
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޶���¼  :
  1. ��    ��   : 2015��02��07��
     ��    ��   : w00316404
     �޸�����   : ��������
*****************************************************************************/
VOS_VOID APP_VC_InitTTYMode(VOS_VOID)
{
    TAF_VC_TTYMODE_ENUM_UINT8           enTTYMode;

    /* ������ʼ�� */
    enTTYMode = APP_VC_GetTTYMode();

    if (TAF_VC_TTY_OFF == enTTYMode)
    {
        return;
    }

    (VOS_VOID)APP_VC_SetTTYMode(TAF_VC_TTY_OFF);

    return;
}
VOS_UINT32 APP_VC_IsVcVoiceWorkTypeTest()
{
    NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU                   stQuickStartFlg;
    VOS_UINT32                                              ulIsTestMode;

    ulIsTestMode = VOS_FALSE;

    PS_MEM_SET(&stQuickStartFlg, 0x0, sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU));

    /* ��ȡ���ٿ���NV���NV������ÿ���ͨ��AT����CQST������ */
    if (NV_OK != NV_Read(en_NV_Item_FollowOn_OpenSpeed_Flag, (VOS_VOID*)(&stQuickStartFlg), sizeof(NAS_NVIM_FOLLOWON_OPENSPEED_FLAG_STRU)))
    {
       stQuickStartFlg.ulQuickStartSta = APP_VC_QUICK_START_DISABLE;
    }

    /* ���ٿ���ģʽ */
    if (APP_VC_QUICK_START_ENABLE == stQuickStartFlg.ulQuickStartSta)
    {
        /* 9235nvֵΪ0x34343434ʱ����Ϊvcvoice testģʽ */
        if (APP_VC_VOICE_NORMAL_MODE_IN_QUICK_START == g_stVcStateMgmt.ulVoiceTestFlag)
        {
            ulIsTestMode = VOS_FALSE;
        }
        else
        {
            ulIsTestMode = VOS_TRUE;
        }
    }
    /* �ǿ��ٿ���ģʽ */
    else
    {
        /* ��9235nvֵΪ0x55aa55aaʱΪvcvoice testģʽ */
        if (APP_VC_VOICE_TEST_FLAG_ENABLE == g_stVcStateMgmt.ulVoiceTestFlag)
        {
            ulIsTestMode = VOS_TRUE;
        }
        else
        {
            ulIsTestMode = VOS_FALSE;
        }
    }

    return ulIsTestMode;
}
VCVOICE_WORK_TYPE_ENUM_UINT16 APP_VC_GetWorkType(VOS_VOID)
{
    /* Modified by w00316404 for TTY MODE, 2015-02-07, begin */
    TAF_VC_TTYMODE_ENUM_UINT8           enTTYMode;
    VOS_UINT32                          ulIsTestMode;

    /* ������ʼ�� */
    enTTYMode = APP_VC_GetTTYMode();
    /* Modified by w00316404 for TTY MODE, 2015-02-07, end */

    ulIsTestMode = APP_VC_IsVcVoiceWorkTypeTest();

    if (VOS_TRUE == ulIsTestMode)
    {
        return VCVOICE_WORK_TYPE_TEST;
    }
#if (FEATURE_ON == FEATURE_ECALL)
    else if (PS_TRUE == APP_VC_GetInEcallFlag())
    {
        return VCVOICE_WORK_TYPE_ECALL;
    }
#endif
    /* Modified by w00316404 for TTY MODE, 2015-02-07, begin */
    else if((TAF_VC_TTY_OFF != enTTYMode) && (TAF_VC_TTYMODE_BUTT > enTTYMode))
    {
        if (TAF_VC_TTY_FULL == enTTYMode)
        {
            return VCVOICE_WORK_TYPE_TTY_FULL;
        }
        else if (TAF_VC_TTY_VCO == enTTYMode)
        {
            return VCVOICE_WORK_TYPE_TTY_VCO;
        }
        else
        {
            return VCVOICE_WORK_TYPE_TTY_HCO;
        }
    }
    /* Modified by w00316404 for TTY MODE, 2015-02-07, end */
    else
    {
        if (VOS_FALSE == APP_VC_GetPcVoiceSupportFlg())
        {
            if (VOS_TRUE == DRV_GET_CODEC_FUNC_STATUS())
            {
                return VCVOICE_WORK_TYPE_NORMAL;
            }

            return VCVOICE_WORK_TYPE_TEST;
        }
        else
        {
            return VCVOICE_WORK_TYPE_NORMAL;
        }
    }
}
VOS_VOID APP_VC_UpdateState(APP_VC_GLOBAL_STATE_ENUM_U16    enState)
{
    g_stVcStateMgmt.enState = enState;
}


VOS_VOID APP_VC_UpdateRadioMode(CALL_VC_RADIO_MODE_ENUM_U8    enRadioMode)
{
    g_stVcStateMgmt.enRadioMode = enRadioMode;
}


VOS_VOID APP_VC_UpdateClientId(MN_CLIENT_ID_T   clientId)
{
    g_stVcStateMgmt.clientId = clientId;
}



VOS_VOID APP_VC_UpdateOpId(MN_OPERATION_ID_T   opId)
{
    g_stVcStateMgmt.opId = opId;
}


VOS_VOID APP_VC_UpdataPreMuteStatus(APP_VC_MUTE_STATUS_ENUM_UINT8 enMuteStatus)
{
    g_stVcStateMgmt.enPreMuteStatus = enMuteStatus;

    return;
}


VOS_VOID APP_VC_UpdataCurrMuteStatus(APP_VC_MUTE_STATUS_ENUM_UINT8 enMuteStatus)
{
    g_stVcStateMgmt.enCurrMuteStatus = enMuteStatus;

    return;
}


VOS_VOID  APP_VC_ReportEvent(
    APP_VC_EVENT_ENUM_U32               enEventType,
    VOS_UINT32                          ulErrCode
)
{
    APP_VC_EVENT_INFO_STRU              stVcEvtInfo;
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;

    PS_MEM_SET(&stVcEvtInfo, 0x00, sizeof(APP_VC_EVENT_INFO_STRU));
    PS_MEM_SET(&stClvlVolume, 0, sizeof(stClvlVolume));

    APP_VC_GetClvlVolume(&stClvlVolume);

    stVcEvtInfo.clientId     = g_stVcStateMgmt.clientId;
    stVcEvtInfo.opId         = g_stVcStateMgmt.opId;
    /* �����ֵ��80����ΪAT�Ķ��巶ΧΪ0~92,���������֮�䶨��ķ�Χ
       Ϊ-80~12*/
    stVcEvtInfo.usVolume     = (VOS_UINT16)(APP_VC_GetCurrVolume(&stClvlVolume) + 80);
    stVcEvtInfo.enDevMode    = stClvlVolume.usCurrDevMode;
    stVcEvtInfo.enMuteStatus = APP_VC_GetCurrMuteStatus();

#if (FEATURE_ON == FEATURE_ECALL)
    stVcEvtInfo.enEcallState       = APP_VC_GetEcallState();
    stVcEvtInfo.ulEcallDescription = APP_VC_GetEcallDescription();
#endif

    if (ulErrCode != MN_ERR_NO_ERROR)
    {
        stVcEvtInfo.bSuccess = VOS_FALSE;
    }
    else
    {
        stVcEvtInfo.bSuccess = VOS_TRUE;
    }
    stVcEvtInfo.ulErrCode = ulErrCode;

    switch(enEventType)
    {
        case APP_VC_EVT_SET_VOLUME:
        case APP_VC_EVT_SET_VOICE_MODE:
        case APP_VC_EVT_GET_VOLUME:
        case APP_VC_EVT_SET_MUTE_STATUS:
        case APP_VC_EVT_GET_MUTE_STATUS:
#if (FEATURE_ON == FEATURE_ECALL)
        case APP_VC_EVT_SET_ECALL_CFG:
        case APP_VC_EVT_ECALL_TRANS_STATUS:
#endif
            MN_SendClientEvent(g_stVcStateMgmt.clientId,
                               MN_CALLBACK_VOICE_CONTROL,
                               enEventType,
                               (VOS_VOID *)&stVcEvtInfo);
            break;

        default:
            VC_WARN_LOG1("APP_VC_ReportEvent:Wrong Event Type.", (VOS_INT32)enEventType);
            break;
    }

    return;
}


VOS_VOID  APP_VC_InitGlobeVariable(VOS_VOID)
{
    APP_VC_MS_CFG_INFO_STRU             *pstMsCfgInfo;
    VOS_UINT32                           ulVoiceTestFlagValue;
    VOS_UINT32                           ulRlst;
    APP_VC_NV_CLVL_VOLUME_STRU           stClvlVolume;

    ulVoiceTestFlagValue    = 0;

    PS_MEM_SET(&g_stVcStateMgmt, 0, sizeof(g_stVcStateMgmt));

    APP_VC_ReadNvimInfo();

    pstMsCfgInfo            = APP_VC_GetCustomCfgInfo();

    g_stVcStateMgmt.iDevHandle = DRV_CODEC_OPEN("/dev/codec0",0,0);
    if (-1 == g_stVcStateMgmt.iDevHandle)
    {
        VC_ERR_LOG("APP_VC_InitGlobeVariable: Open codec0 Fail");
    }

    /*��ȡnv��Ϣ*/
    PS_MEM_SET(&stClvlVolume, 0x00, sizeof(stClvlVolume));
    APP_VC_GetClvlVolume(&stClvlVolume);

    stClvlVolume.usCurrDevMode = VC_PHY_DEVICE_MODE_EARPHONE;

    g_stVcStateMgmt.ucPcVoiceSupportFlag =
        (APP_VC_NV_ITEM_ACTIVE == pstMsCfgInfo->usVcPcvoiceSupportFlag) ?
            VOS_TRUE : VOS_FALSE;

    /* ���֧�� PC VOICE, �����豸ģʽĬ��ֵΪ PC VOICE */
    if (VOS_TRUE == g_stVcStateMgmt.ucPcVoiceSupportFlag)
    {
        stClvlVolume.usCurrDevMode = VC_PHY_DEVICE_MODE_PCVOICE;
    }

    g_stVcStateMgmt.ucVoicePort = APP_VC_VOICE_PORT_BUTT;

    /* ���µ�Pre Device Mode Pre Volume */
    stClvlVolume.usPreDevMode   = stClvlVolume.usCurrDevMode;
    stClvlVolume.sPreVolume     = APP_VC_GetCurrVolume(&stClvlVolume);
    APP_VC_SaveClvlVolume(&stClvlVolume);

    ulRlst = APP_VC_GetVoiceTestFlag(&ulVoiceTestFlagValue);

    if (VOS_OK == ulRlst)
    {
        g_stVcStateMgmt.ulVoiceTestFlag = ulVoiceTestFlagValue;
    }
    else
    {
        g_stVcStateMgmt.ulVoiceTestFlag = APP_VC_VOICE_TEST_FLAG_DEFALUT;
    }

    g_stVcStateMgmt.enCurrMuteStatus = APP_VC_MUTE_STATUS_UNMUTED;

#if (FEATURE_ON == FEATURE_ECALL)
    APP_VC_SetEcallState(APP_VC_ECALL_TRANS_STATUS_BUTT);
    APP_VC_SetAllowSetMsdFlag(PS_TRUE);
#endif

    /* Added by w00316404 for OPT VC, 2015-02-07, Begin */
    /*lint -e717*/
    HI_INIT_LIST_HEAD(&g_stVcStateMgmt.stBuffMsgListHead);
    /*lint +e717*/
    /* Added by w00316404 for OPT VC, 2015-02-07, End */

    /* Added by w00316404 for TTY MODE, 2015-02-07, Begin */
    APP_VC_InitTTYMode();
    /* Added by w00316404 for TTY MODE, 2015-02-07, end */

    return;
}
VOS_VOID  APP_VC_StartProtectTimer(APP_VC_TIMER_ID_ENUM_U16 enTimerName)
{
    /* ����VOS��ʱ�� */
    if (VOS_OK != VOS_StartRelTimer(&g_stVcStateMgmt.protectTimer,
                                    WUEPS_PID_VC,
                                    1000,
                                    enTimerName,
                                    0,
                                    VOS_RELTIMER_NOLOOP,
                                    VOS_TIMER_PRECISION_5))
    {
        VC_ERR_LOG("VOS_StartRelTimer: failed.");
    }
}


VOS_VOID  APP_VC_StopProtectTimer(VOS_VOID)
{
    /* ����VOS��ʱ�� */
    if (VOS_OK != VOS_StopRelTimer(&g_stVcStateMgmt.protectTimer))
    {
        VC_ERR_LOG("APP_VC_StopProtectTimer: failed.");
    }
}
VOS_UINT32  APP_VC_GetNVIdForGsm(
    VC_PHY_DEVICE_MODE_ENUM_U16         enDevMode
)
{
    switch(enDevMode)
    {
        case VC_PHY_DEVICE_MODE_HANDSET:
            return en_NV_Item_HANDSET_G_PARAM_ID;
        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            return en_NV_Item_HANDHELD_HANDFREE_G_PARAM_ID;
        case VC_PHY_DEVICE_MODE_CAR_FREE:
            return en_NV_Item_VECHILE_HANDFREE_G_PARAM_ID;
        case VC_PHY_DEVICE_MODE_EARPHONE:
            return en_NV_Item_HEADSET_G_PARAM_ID;
        case VC_PHY_DEVICE_MODE_BLUETOOTH:
            return en_NV_Item_BT_G_PARAM_ID;
        case VC_PHY_DEVICE_MODE_PCVOICE:
            return en_NV_Item_PCVOICE_PARAM_ID_W;
        default:
            VC_WARN_LOG1("APP_VC_GetNVIdForGsm: GSM,wrong enDevMode", enDevMode);
            return en_NV_Item_ID_BUTT;
    }
}

VOS_UINT32  APP_VC_GetNVIdForWcdma(
    VC_PHY_DEVICE_MODE_ENUM_U16         enDevMode
)
{
    switch(enDevMode)
    {
        case VC_PHY_DEVICE_MODE_HANDSET:
            return en_NV_Item_HANDSET_W_PARAM_ID;

        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            return en_NV_Item_HANDHELD_HANDFREE_W_PARAM_ID;

        case VC_PHY_DEVICE_MODE_CAR_FREE:
            return en_NV_Item_VECHILE_HANDFREE_W_PARAM_ID;

        case VC_PHY_DEVICE_MODE_EARPHONE:
            return en_NV_Item_HEADSET_W_PARAM_ID;

        case VC_PHY_DEVICE_MODE_BLUETOOTH:
            return en_NV_Item_BT_W_PARAM_ID;

        case VC_PHY_DEVICE_MODE_PCVOICE:
            return en_NV_Item_PCVOICE_PARAM_ID_W;

        default:
            VC_WARN_LOG1("APP_VC_GetNVIdForWcdma: WCDMA,wrong enDevMode", enDevMode);
            return en_NV_Item_ID_BUTT;
    }
}


VOS_UINT32   APP_VC_GetNVId(
    CALL_VC_RADIO_MODE_ENUM_U8          enRadioMode,
    VC_PHY_DEVICE_MODE_ENUM_U16         enDevMode
)
{
    switch(enRadioMode)
    {
        case CALL_VC_MODE_GSM:
            return APP_VC_GetNVIdForGsm(enDevMode);
        case CALL_VC_MODE_WCDMA:
            return APP_VC_GetNVIdForWcdma(enDevMode);
        default:
            VC_WARN_LOG1("APP_VC_GetNVId: wrong enRadioMode", enRadioMode);
            return en_NV_Item_ID_BUTT;
    }
}



VOS_UINT16  APP_VC_GetInDevMode(VC_PHY_DEVICE_MODE_ENUM_U16  enDevMode)
{
    switch(enDevMode)
    {
        case VC_PHY_DEVICE_MODE_HANDSET:
            return APP_VC_IN_DEV_HANDSET_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            return APP_VC_IN_DEV_HANDFREE_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_EARPHONE:
            return APP_VC_IN_DEV_HEADSET_EXTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_HEADPHONE:
            return APP_VC_IN_DEV_HANDFREE_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_SUPER_HANDFREE:
            return APP_VC_IN_DEV_HANDFREE_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_SMART_TALK:
            return APP_VC_IN_DEV_HANDFREE_INTERNAL_MIC;

        default:
            VC_WARN_LOG1("APP_VC_GetInDevMode: wrong enDevMode", enDevMode);
            return APP_VC_IN_DEV_BUTT;
    }

}


VOS_UINT16  APP_VC_GetOutDevMode(VC_PHY_DEVICE_MODE_ENUM_U16  enDevMode)
{
    switch(enDevMode)
    {
        case VC_PHY_DEVICE_MODE_HANDSET:
            return APP_VC_OUT_DEV_HANDSET_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            return APP_VC_OUT_DEV_HANDFREE_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_EARPHONE:
            return APP_VC_OUT_DEV_HEADSET_EXTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_HEADPHONE:
            return APP_VC_OUT_DEV_HANDFREE_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_SUPER_HANDFREE:
            return APP_VC_OUT_DEV_HANDFREE_INTERNAL_MIC;

        case VC_PHY_DEVICE_MODE_SMART_TALK:
            return APP_VC_OUT_DEV_HANDFREE_INTERNAL_MIC;

        default:
            VC_WARN_LOG1("APP_VC_GetOutDevMode: wrong enDevMode", enDevMode);
            return APP_VC_OUT_DEV_BUTT;
    }

}

#if (FEATURE_ON == FEATURE_IMS)

VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32  APP_VC_ConvertVcOpenChannelFailCauseToImsaExceptionCause(
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause
)
{
    switch(enVcCause)
    {
        case APP_VC_OPEN_CHANNEL_CAUSE_SUCC:
            return VC_IMSA_EXCEPTION_CAUSE_SUCC;

        case APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED:
            return VC_IMSA_EXCEPTION_CAUSE_STARTED;

        case APP_VC_OPEN_CHANNEL_FAIL_CAUSE_PORT_CFG_FAIL:
            return VC_IMSA_EXCEPTION_CAUSE_PORT_CFG_FAIL;

        case APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_DEVICE_FAIL:
            return VC_IMSA_EXCEPTION_CAUSE_SET_DEVICE_FAIL;

        case APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL:
            return VC_IMSA_EXCEPTION_CAUSE_SET_START_FAIL;

        case APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_VOLUME_FAIL:
            return VC_IMSA_EXCEPTION_CAUSE_SET_VOLUME_FAIL;

        case APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SAMPLE_RATE_FAIL:
            return VC_IMSA_EXCEPTION_CAUSE_SAMPLE_RATE_FAIL;

        case APP_VC_OPEN_CHANNEL_FAIL_CAUSE_TI_START_EXPIRED:
            return VC_IMSA_EXCEPTION_CAUSE_TI_START_EXPIRED;

        default:
            VC_ERR_LOG("APP_VC_ConvertVcOpenChannelFailCauseToImsaExceptionCause: wrong enVcCause");
            return VC_IMSA_EXCEPTION_CAUSE_BUTT;
    }

}


CALL_VC_CODEC_TYPE_ENUM_U8  APP_VC_ConvertImsaCodeTypeToCallCodeType(
    IMSA_VC_CODEC_TYPE_ENUM_UINT8       enImsaCodeType
)
{
    switch(enImsaCodeType)
    {
        case IMSA_VC_CODEC_TYPE_AMR:
            return CALL_VC_CODEC_TYPE_AMR;

        case IMSA_VC_CODEC_TYPE_AMRWB:
            return CALL_VC_CODEC_TYPE_AMRWB;

        case IMSA_VC_CODEC_TYPE_G711:
            return CALL_VC_CODEC_TYPE_G711;

        default:
            VC_ERR_LOG("APP_VC_ConvertImsaCodeTypeToCallCodeType: wrong enImsaCodeType");
            return CALL_VC_CODEC_TYPE_BUTT;
    }

}

#endif

VOS_UINT32  APP_VC_InputOutPutPortCfg(
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType
)
{
    /* TODO: ���͵���ȷ�Ͻӿ� */
    APP_VC_IOCTL_AUDIO_IN_DEV_ENUM_U16  enAudioInDev;
    APP_VC_IOCTL_AUDIO_OUT_DEV_ENUM_U16 enAudioOutDev;
    VOS_UINT8                           ucSampleRate;
    VC_OM_PCVOICE_TRANS_STATUS_STRU    *pstPcVoiceTransStatusMsg;
    VOS_UINT32                          ulRet;
    APP_VC_MS_CFG_INFO_STRU            *pstMsCfgInfo;
    VC_PHY_DEVICE_MODE_ENUM_U16         enCurrDevMode;

    enCurrDevMode = APP_VC_GetCurrDevMode();

    pstMsCfgInfo                         = APP_VC_GetCustomCfgInfo();

    pstPcVoiceTransStatusMsg = VOS_NULL_PTR;

    /* �����ǰ��δ������й����� */
    if (VOS_FALSE == g_stVcStateMgmt.bInCall)
    {
        /*PC Voice����δʹ��*/
        if (VOS_FALSE == g_stVcStateMgmt.ucPcVoiceSupportFlag)
        {
            if (VCVOICE_WORK_TYPE_TEST != APP_VC_GetWorkType())
            {
                if (APP_VC_INVALID_DEV_HANDLE == APP_VC_GetDevHandle())
                {
                    /* APP_VC_SendEndCallReq();������ͳһ���ͣ������޸���ͬ */
                    VC_WARN_LOG("APP_VC_CallChannelOpenProc: Open Codec Fail" );
                    return VOS_ERR;
                }

                if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_PCM_MODE_SET, 0))
                {
                    VC_WARN_LOG("APP_VC_CallChannelOpenProc: AUDIO_PCM_MODE_SET Fail" );
                    return VOS_ERR;
                }

                if ( CALL_VC_CODEC_TYPE_AMRWB == enCodecType )
                {
                    ucSampleRate = 3;
                }
                else
                {
                    ucSampleRate = 0;
                }

                if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_SAMPLE_RATE_SET, ucSampleRate))
                {
                    (VOS_VOID)DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_CLOSE, 0);
                    VC_WARN_LOG("APP_VC_CallChannelOpenProc: Sample rate failed" );
                    return VOS_ERR;
                }

                if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_OPEN, 0))
                {
                    VC_WARN_LOG("APP_VC_CallChannelOpenProc: VOICE_OPEN Fail" );
                    return VOS_ERR;
                }

                /* �����ͳ����豸����Ҫ����ģ��codec */
                if ((VC_PHY_DEVICE_MODE_BLUETOOTH != enCurrDevMode)
                 && (VC_PHY_DEVICE_MODE_CAR_FREE != enCurrDevMode))
                {
                    enAudioInDev = APP_VC_GetInDevMode(enCurrDevMode);
                    enAudioOutDev = APP_VC_GetOutDevMode(enCurrDevMode);
                    if (APP_VC_IN_DEV_BUTT == enAudioInDev)
                    {
                        VC_WARN_LOG("APP_VC_CallChannelOpenProc: GET IN_OUT_DEV Fail" );
                        return VOS_ERR;
                    }

                    if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_IN_DEV_SELECT, enAudioInDev))
                    {
                        (VOS_VOID)DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_CLOSE, 0);
                        VC_WARN_LOG("APP_VC_CallChannelOpenProc: IN_DEV_SELECT Fail" );
                        return VOS_ERR;
                    }

                    if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_OUT_DEV_SELECT, enAudioOutDev))
                    {
                        (VOS_VOID)DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_CLOSE, 0);
                        VC_WARN_LOG("APP_VC_CallChannelOpenProc: OUT_DEV_SELECT Fail" );
                        return VOS_ERR;
                    }
                }
            }
        }
        else
        {
             if (APP_VC_NV_ITEM_ACTIVE == pstMsCfgInfo->usVcPcvoiceSupportFlag)
             {
                  pstPcVoiceTransStatusMsg = (VC_OM_PCVOICE_TRANS_STATUS_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC,
                                             sizeof(VC_OM_PCVOICE_TRANS_STATUS_STRU) - VOS_MSG_HEAD_LENGTH);

                 if (VOS_NULL_PTR == pstPcVoiceTransStatusMsg)
                 {
                    VC_ERR_LOG("in APP_VC_InputOutPutPortCfg:malloc error!");
                    return VOS_ERR;
                 }
                 pstPcVoiceTransStatusMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
                 pstPcVoiceTransStatusMsg->ulReceiverPid        = WUEPS_PID_TAF;
                 pstPcVoiceTransStatusMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
                 pstPcVoiceTransStatusMsg->ulSenderPid          = WUEPS_PID_VC;
                 pstPcVoiceTransStatusMsg->usPcVoiceChannelOper = OM_PCV_CHANNEL_OPEN;
                 pstPcVoiceTransStatusMsg->usPort               = g_stVcStateMgmt.ucVoicePort;
                 pstPcVoiceTransStatusMsg->ulLength             = sizeof(VC_OM_PCVOICE_TRANS_STATUS_STRU) - VOS_MSG_HEAD_LENGTH;

                 /*����OM�ӿ����������˿�*/
                 if (APP_VC_VOICE_PORT_BUTT != APP_VC_GetPcVoicePort())
                 {

                     ulRet = APP_VC_SendVcReqToOm(OM_PCV_CHANNEL_OPEN, APP_VC_GetPcVoicePort());
                     if (VOS_OK != ulRet)
                     {
                         VC_WARN_LOG("APP_VC_CallChannelOpenProc: OM_PCV_CHANNEL_OPEN FAIL!" );
                         NAS_MNTN_FailtoOpenCsChannel(g_stVcStateMgmt.ucVoicePort, ulRet);
                         g_stVcStateMgmt.ucVoicePort              = APP_VC_VOICE_PORT_BUTT;
                         pstPcVoiceTransStatusMsg->usOmOperResult = VOS_ERR;
                         DIAG_TraceReport(pstPcVoiceTransStatusMsg);
                         (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstPcVoiceTransStatusMsg);
                         return VOS_ERR;
                     }

                 }
                 pstPcVoiceTransStatusMsg->usOmOperResult = VOS_OK;
                 DIAG_TraceReport(pstPcVoiceTransStatusMsg);
                 (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstPcVoiceTransStatusMsg);

             }

        }
    }

    return VOS_OK;
}



VOS_UINT32  APP_VC_CallChannelOpenProc(
    CALL_VC_CHANNEL_INFO_STRU                              *pstChanInfo,
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32             *penCause
)
{
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;
    VOS_INT16                           sCurVolume;

    PS_MEM_SET(&stClvlVolume, 0, sizeof(stClvlVolume));
    APP_VC_GetClvlVolume(&stClvlVolume);

    /* �޸ĵ�:
        1.������ӷ���ֵ
        2.��ʧ�ܵ�ԭ��ֵ��Ϊ�������������
        3.�쳣���ʱ����callģ�鷢EndCallReq�����߸�IMSA��ExceptionNtf��������һ�㷢�� */

    /* �����ǰ�ǲ���ģʽ����ʵ�ʷ��Ͳ���ģʽ����Ϣ������� */
    if (VCVOICE_WORK_TYPE_TEST == APP_VC_GetWorkType())
    {
        APP_VC_SendPhyTestModeNotify(pstChanInfo->stChannelParam.enMode);
        APP_VC_UpdateRadioMode(pstChanInfo->stChannelParam.enMode);

        g_stVcStateMgmt.bInCall = VOS_TRUE;
        *penCause = APP_VC_OPEN_CHANNEL_CAUSE_SUCC;
        return VOS_TRUE;
    }

    if (VOS_OK != APP_VC_InputOutPutPortCfg(pstChanInfo->stChannelParam.enCodecType))
    {
        *penCause = APP_VC_OPEN_CHANNEL_FAIL_CAUSE_PORT_CFG_FAIL;
        return VOS_FALSE;
    }

    APP_VC_UpdateRadioMode(pstChanInfo->stChannelParam.enMode);

    if (VOS_OK != APP_VC_SendSetDeviceReq(stClvlVolume.usCurrDevMode))
    {
        VC_WARN_LOG("APP_VC_CallChannelOpenProc: APP_VC_SendSetDeviceReq fail" );
        *penCause = APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_DEVICE_FAIL;
        return VOS_FALSE;
    }

    if (VOS_OK != APP_VC_SendStartReq(pstChanInfo, APP_VC_GetRadioMode()))
    {
        VC_WARN_LOG("APP_VC_CallChannelOpenProc: APP_VC_SendStartReq fail" );
        *penCause = APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL;
        return VOS_FALSE;
    }

    /* ������������ */
    sCurVolume = APP_VC_GetCurrVolume(&stClvlVolume);

    if (VOS_OK != APP_VC_SendSetVolumeReq(VCVOICE_VOLUME_TARGET_DOWN,
                                          sCurVolume))
    {
        VC_WARN_LOG("APP_VC_CallChannelOpenProc: APP_VC_SendSetVolumeReq fail" );
        *penCause = APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_VOLUME_FAIL;
        return VOS_FALSE;
    }

    /* ���ݾ���״̬���ö�Ӧ����������ֵ */
    sCurVolume = (APP_VC_MUTE_STATUS_UNMUTED == APP_VC_GetCurrMuteStatus()) ?
                 APP_VC_UNMUTED_VOLUME : APP_VC_MUTED_VOLUME;

    if (VOS_OK != APP_VC_SendSetVolumeReq(VCVOICE_VOLUME_TARGET_UP,
                                          sCurVolume))
    {
        VC_WARN_LOG("APP_VC_CallChannelOpenProc: APP_VC_SendSetVolumeReq(mute) fail" );
        *penCause = APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_VOLUME_FAIL;
        return VOS_FALSE;
    }

    *penCause = APP_VC_OPEN_CHANNEL_CAUSE_SUCC;
    APP_VC_StartProtectTimer(APP_VC_TIMER_START);
    APP_VC_UpdateState(APP_VC_S_WAIT_INTERNAL_SET_DEV_RSLT);
    g_stVcStateMgmt.bInCall = VOS_TRUE;

    return VOS_TRUE;
}


VOS_VOID  APP_VC_CallChannelCloseProc(VOS_VOID)
{
    /* TODO: ���͵���ȷ�Ͻӿ� */
    VC_OM_PCVOICE_TRANS_STATUS_STRU     *pstPcVoiceTransStatusMsg;
    VOS_UINT32                           ulRst;
    APP_VC_MS_CFG_INFO_STRU             *pstMsCfgInfo;

    pstMsCfgInfo                         = APP_VC_GetCustomCfgInfo();
    /* �����ǰ�ǲ���ģʽ����ֱ���˳� */
    if (VCVOICE_WORK_TYPE_TEST == APP_VC_GetWorkType())
    {
        g_stVcStateMgmt.bInCall = VOS_FALSE;
        return;
    }

    if (VOS_FALSE == g_stVcStateMgmt.ucPcVoiceSupportFlag)
    {
        if (APP_VC_INVALID_DEV_HANDLE == APP_VC_GetDevHandle())
        {
            VC_ERR_LOG("APP_VC_CallChannelCloseProc: Open Codec Fail");
        }
        else
        {
            if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_CLOSE, 0))
            {
                VC_WARN_LOG("APP_VC_CallChannelCloseProc: VOICE Close Fail");
            }
        }
    }
    else
    {
        if (APP_VC_NV_ITEM_ACTIVE == pstMsCfgInfo->usVcPcvoiceSupportFlag)
        {
            pstPcVoiceTransStatusMsg = (VC_OM_PCVOICE_TRANS_STATUS_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_VC,
                                                              sizeof(VC_OM_PCVOICE_TRANS_STATUS_STRU));    /* �����ڴ� */

            if (VOS_NULL_PTR == pstPcVoiceTransStatusMsg)
            {
                VC_ERR_LOG("in APP_VC_CallChannelCloseProc:malloc error!");
                return;
            }
            pstPcVoiceTransStatusMsg->ulReceiverCpuId      = VOS_LOCAL_CPUID;
            pstPcVoiceTransStatusMsg->ulReceiverPid        = WUEPS_PID_TAF;
            pstPcVoiceTransStatusMsg->ulSenderCpuId        = VOS_LOCAL_CPUID;
            pstPcVoiceTransStatusMsg->ulSenderPid          = WUEPS_PID_VC;
            pstPcVoiceTransStatusMsg->usPcVoiceChannelOper = OM_PCV_CHANNEL_CLOSE;
            pstPcVoiceTransStatusMsg->usPort               = g_stVcStateMgmt.ucVoicePort;
            pstPcVoiceTransStatusMsg->ulLength             = sizeof(VC_OM_PCVOICE_TRANS_STATUS_STRU) - VOS_MSG_HEAD_LENGTH;

            if (APP_VC_VOICE_PORT_BUTT != g_stVcStateMgmt.ucVoicePort)
            {
                ulRst = APP_VC_SendVcReqToOm(OM_PCV_CHANNEL_CLOSE, g_stVcStateMgmt.ucVoicePort);
                g_stVcStateMgmt.ucVoicePort = APP_VC_VOICE_PORT_BUTT;
                g_stVcStateMgmt.bInCall = VOS_FALSE;
                VC_INFO_LOG1("PC VOICE TEST:APPP_VC_HpaMsgProc: OM_PCV_CHANEL_CLOSE.", g_stVcStateMgmt.ucVoicePort);
                pstPcVoiceTransStatusMsg->usOmOperResult = ulRst;
                DIAG_TraceReport(pstPcVoiceTransStatusMsg);
            }
            (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstPcVoiceTransStatusMsg);

        }

    }

    APP_VC_SendStopReq(APP_VC_GetRadioMode());
    APP_VC_StartProtectTimer(APP_VC_TIMER_STOP);
    APP_VC_UpdateState(APP_VC_S_WAIT_INTERNAL_SET_CLOSE_RSLT);
    g_stVcStateMgmt.bInCall = VOS_FALSE;
#if (FEATURE_ON == FEATURE_ECALL)
    APP_VC_SetInEcallFlag(PS_FALSE);
#endif
}
VOS_VOID  APP_VC_CallChannelParaChangeProc(CALL_VC_CHANNEL_INFO_STRU *pstChanInfo)
{
    VOS_UINT8                           ucSampleRate;
    CALL_VC_RADIO_MODE_ENUM_U8          enCurrMode;

    enCurrMode = APP_VC_GetRadioMode();

    /* �����ǰ�ǲ���ģʽ����ϵͳģʽ�����������ʵ�ʷ��Ͳ���ģʽ����Ϣ������� */

    if ( VCVOICE_WORK_TYPE_TEST == APP_VC_GetWorkType())
    {
        if (enCurrMode != pstChanInfo->stChannelParam.enMode)
        {
            APP_VC_SendPhyTestModeNotify(pstChanInfo->stChannelParam.enMode);
            APP_VC_UpdateRadioMode(pstChanInfo->stChannelParam.enMode);
        }
        return;
    }


    APP_VC_UpdateRadioMode(pstChanInfo->stChannelParam.enMode);
    if ( CALL_VC_CODEC_TYPE_AMRWB == pstChanInfo->stChannelParam.enCodecType )
    {
        ucSampleRate = 3;
    }
    else
    {
        ucSampleRate = 0;
    }

    if ( VOS_FALSE == APP_VC_GetPcVoiceSupportFlg() )
    {
        if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_SAMPLE_RATE_SET, ucSampleRate))
        {
            VC_WARN_LOG("APP_VC_CallChannelOpenProc: Sample rate failed" );

#if (FEATURE_ON == FEATURE_IMS)
            if (APP_VC_START_HIFI_ORIG_IMSA == APP_VC_GetStartHifiOrig())
            {
                /* �����IMSA�����������󣬸�IMSA�ظ��쳣 */
                APP_VC_SendImsaExceptionNtf(VC_IMSA_EXCEPTION_CAUSE_SAMPLE_RATE_FAIL);
            }
            else
#endif
            {
                /*�����CALL�����������󣬷�����Ϣ��CALLģ�飬�Ҷϵ绰*/
                APP_VC_SendEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SAMPLE_RATE_FAIL);
            }

            APP_VC_LogEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SAMPLE_RATE_FAIL);

            /* ����ȫ�ֱ���enStartHifiOrig */
            g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;

            return ;
        }
    }


    /* ����ȫ�ֱ���enStartHifiOrig */
    g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;

    APP_VC_SendSetCodecReq(pstChanInfo);
    APP_VC_StartProtectTimer(APP_VC_TIMER_SET_CODEC);
    APP_VC_UpdateState(APP_VC_S_WAIT_INTERNAL_SET_CODEC_RSLT);
}

/*****************************************************************************
 �� �� ��  : APP_VC_AddBufferTafMsg
 ��������  : VCģ�黺��Call��Ϣ������
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : W00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID APP_VC_AddBufferTafMsg(MsgBlock* pMsg)
{
    CALL_VC_CHANNEL_INFO_MSG_STRU      *pstChanInfo = (CALL_VC_CHANNEL_INFO_MSG_STRU *)pMsg;

    /* ����ڿ���������ʱ�򣬳��ֲ����ı䣬�˴������ǻ��洦�����ڱ���
       ��������: ����������ʱ�򣬷������л�����ʱ���͵Ĵ��������������
       �����壬ʹ�õ�ǰ�ĳ�ʱ��������ʱ�������ʱ���µĲ�������Ӧ���Ѿ�
       �л�������һ��ģ����ô�ٴη��ͣ����û���µĲ�������Ϊ������쳣��
       �Ҷϵ绰
    */
    if ((APP_VC_S_WAIT_INTERNAL_SET_START_RSLT == APP_VC_GetState())
     && (CALL_VC_CHANNEL_PARA_CHANGE == pstChanInfo->enMsgName))
    {
        g_stVcStateMgmt.bParaUpdate = VOS_TRUE;
        g_stVcStateMgmt.enCodecType = pstChanInfo->stChannelInfo.stChannelParam.enCodecType;
        g_stVcStateMgmt.enRadioMode = pstChanInfo->stChannelInfo.stChannelParam.enMode;
        return;
    }

    /* ������Ϣ������ */
    APP_VC_AddBufferMsg(pMsg);

    return;
}

#if 0
VOS_VOID  APP_VC_BufferTafMsg(
    MsgBlock                           *pstMsg
)
{
    /* ����ڿ���������ʱ�򣬳��ֲ����ı䣬�˴������ǻ��洦�����ڱ���
       ��������: ����������ʱ�򣬷������л�����ʱ���͵Ĵ��������������
       �����壬ʹ�õ�ǰ�ĳ�ʱ��������ʱ�������ʱ���µĲ�������Ӧ���Ѿ�
       �л�������һ��ģ����ô�ٴη��ͣ����û���µĲ�������Ϊ������쳣��
       �Ҷϵ绰
    */
    CALL_VC_CHANNEL_INFO_MSG_STRU      *pstChanInfo     = VOS_NULL_PTR;
    VC_CALL_MSG_STRU                   *pstVcCallMsg    = VOS_NULL_PTR;
    VOS_UINT32                          ulLength;

    pstVcCallMsg    = (VC_CALL_MSG_STRU *)pstMsg;
    pstChanInfo     = (CALL_VC_CHANNEL_INFO_MSG_STRU *)pstMsg;

    if ((APP_VC_S_WAIT_INTERNAL_SET_START_RSLT == APP_VC_GetState())
     && (CALL_VC_CHANNEL_PARA_CHANGE == pstChanInfo->enMsgName))
    {
        g_stVcStateMgmt.bParaUpdate = VOS_TRUE;
        g_stVcStateMgmt.enCodecType = pstChanInfo->stChannelInfo.stChannelParam.enCodecType;
        g_stVcStateMgmt.enRadioMode = pstChanInfo->stChannelInfo.stChannelParam.enMode;
        return;
    }

    g_stVcStateMgmt.astBufMsg[g_stVcStateMgmt.ulBuffCnt].enMsgOrigin = APP_VC_MSG_ORIGIN_TAF;

    switch (pstVcCallMsg->enMsgName)
    {
        case CALL_VC_CHANNEL_OPEN:
        case CALL_VC_CHANNEL_CLOSE:
        case CALL_VC_CHANNEL_PARA_CHANGE:
        case CALL_VC_CHANNEL_CONNECT:
            ulLength = sizeof(CALL_VC_CHANNEL_INFO_MSG_STRU);
            break;

        case CALL_VC_SO_CTRL_ORDER_IND:
            ulLength = sizeof(CALL_VC_SO_CTRL_ORDER_IND_STRU);
            break;

        case CALL_VC_SO_CTRL_MSG_IND:
            ulLength = sizeof(CALL_VC_SO_CTRL_MSG_IND_STRU);
            break;

        default :
            /* ��¼�������� */
            VC_WARN_LOG("APP_VC_BufferTafMsg: Msg type Err");
            return;
    }

    /* ������Ϣ���� */
    PS_MEM_CPY(g_stVcStateMgmt.astBufMsg[g_stVcStateMgmt.ulBuffCnt].aucBufMsg,
               pstMsg,
               ulLength);

    g_stVcStateMgmt.ulBuffCnt++;

}
#endif

#if (FEATURE_ON == FEATURE_IMS)
/*****************************************************************************
 �� �� ��  : APP_VC_AddBufferImsaMsg
 ��������  : VCģ�黺��Imsa��Ϣ������
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : W00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID APP_VC_AddBufferImsaMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pMsgHeader = VOS_NULL_PTR;
    IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU *pstParaChg = VOS_NULL_PTR;
    CALL_VC_CODEC_TYPE_ENUM_U8          enCodecType;

    /* ����Ϣ���зַ� */
    pMsgHeader  = (MSG_HEADER_STRU *)pMsg;
    pstParaChg  = (IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU *)pMsg;
    enCodecType = APP_VC_ConvertImsaCodeTypeToCallCodeType(pstParaChg->enCodeType);

    /* ����ڿ���������ʱ�򣬳��ֲ����ı䣬�˴������ǻ��洦�����ڱ���
       ��������: ����������ʱ�򣬷������л�����ʱ���͵Ĵ��������������
       �����壬ʹ�õ�ǰ�ĳ�ʱ��������ʱ�������ʱ���µĲ�������Ӧ���Ѿ�
       �л�������һ��ģ����ô�ٴη��ͣ����û���µĲ�������Ϊ������쳣��
       �Ҷϵ绰
    */
    if ((APP_VC_S_WAIT_INTERNAL_SET_START_RSLT == APP_VC_GetState())
     && (ID_IMSA_VC_HIFI_PARA_CHANGED_NTF == pMsgHeader->ulMsgName))
    {
        g_stVcStateMgmt.bParaUpdate = VOS_TRUE;
        g_stVcStateMgmt.enCodecType = enCodecType;
        g_stVcStateMgmt.enRadioMode = CALL_VC_MODE_IMS_EUTRAN;
        return;
    }

    /* ������Ϣ������ */
    APP_VC_AddBufferMsg(pMsg);

    return;
}

#endif
VOS_VOID  APP_VC_TafMsgProc(
    MsgBlock                           *pstMsg
)
{
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32          enCause;
    VC_CALL_MSG_STRU                   *pstVcCallMsg    = VOS_NULL_PTR;
    CALL_VC_CHANNEL_INFO_MSG_STRU      *pstChannelInfo  = VOS_NULL_PTR;

    enCause         = APP_VC_OPEN_CHANNEL_CAUSE_SUCC;

    /* ȡVC��CALL�Ľṹ��MSG_HEAD */
    pstVcCallMsg    = (VC_CALL_MSG_STRU *)pstMsg;
    pstChannelInfo  = (CALL_VC_CHANNEL_INFO_MSG_STRU *)pstMsg;

    /*�����ǰ��״̬����NULL�Ļ�,������Ϣ,����*/
    if (APP_VC_S_NULL != APP_VC_GetState())
    {
        /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
        APP_VC_AddBufferTafMsg((MsgBlock *)pstMsg);
        /* Modified by w00316404 for OPT VC, 2015-02-07, End */
        return;
    }

    switch (pstVcCallMsg->enMsgName)
    {
        case CALL_VC_CHANNEL_OPEN:
        /*PC�طŵ���ȫ�ֱ���ʹ��*/
#ifndef __PS_WIN32_RECUR__
            NAS_VC_SndOutsideContextData();
#endif
            /* ���HIFI�Ѿ�����������Ҫ��������ֱ�ӷ��� */
            if (VOS_TRUE == APP_VC_GetCallStatus())
            {
                APP_VC_SendEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED);
                APP_VC_LogEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED);
                return;
            }

#if (FEATURE_ON == FEATURE_ECALL)
            if (CALL_VC_CALL_TYPE_ECALL == pstChannelInfo->stChannelInfo.stChannelParam.enCallType)
            {
                APP_VC_SetInEcallFlag(PS_TRUE);
            }
#endif

            /* ����ȫ�ֱ�������¼��CALLҪ����HIFI */
            g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_CALL;

            if (VOS_FALSE == APP_VC_CallChannelOpenProc(&(pstChannelInfo->stChannelInfo), &enCause))
            {
#if (FEATURE_ON == FEATURE_ECALL)
                APP_VC_SetInEcallFlag(PS_FALSE); /* ���eCall��ʶ */
#endif

                /* ��������ŵ�ʱ�쳣����CALL����EndCallReq��Ϣ��
                    ͬʱ����ȫ�ֱ���enStartHifiOrig */
                APP_VC_SendEndCallReq(enCause);

                /* ������ά�ɲ���Ϣ */
                APP_VC_LogEndCallReq(enCause);

                g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;
            }
            break;

        case CALL_VC_CHANNEL_CLOSE:
            APP_VC_CallChannelCloseProc();
            break;

        case CALL_VC_CHANNEL_PARA_CHANGE:

            /* ���ŵ��������ʱ��������ʲ���ʧ�ܣ���Ҫ����ͨ����
                �˴�Ҫ����ȫ�ֱ�������¼��CALL����IMSA������֪ͨ��Ӧ��ģ�����ͨ�� */
            g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_CALL;
            APP_VC_CallChannelParaChangeProc(&(pstChannelInfo->stChannelInfo));
            break;

#if (FEATURE_ON == FEATURE_ECALL)
        case CALL_VC_CHANNEL_CONNECT:
            APP_VC_CallChannelConnectProc();
            break;
#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
        case CALL_VC_SO_CTRL_ORDER_IND:
            APP_VC_CallChannelSoCtrlOrderInd(pstMsg);
            break;

        case CALL_VC_SO_CTRL_MSG_IND:
            APP_VC_CallChannelSoCtrlMsgInd(pstMsg);
            break;
#endif
        default:
            VC_WARN_LOG("APP_VC_TafMsgProc: Msg type Err");
            break;
    }
}

/*lint -e429 -e830*/
/*****************************************************************************
 �� �� ��  : APP_VC_AddBufferMsg
 ��������  : VCģ�黺����Ϣ������
 �������  : pMsg
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��2��7��
    ��    ��   : W00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID APP_VC_AddBufferMsg(MsgBlock* pMsg)
{
    APP_VC_BUFF_MSG_NODE_STRU          *pstNode     = VOS_NULL_PTR;
    MsgBlock                           *pNewMsg     = VOS_NULL_PTR;

    /* �жϻ����Ƿ��Ѿ����� */
    if (g_stVcStateMgmt.ulBuffMsgCnt >= APP_VC_BUFF_MSG_MAX_CNT)
    {
        VC_ERR_LOG("APP_VC_AddBufferMsg: Buffer Full!");
        return;
    }

    /* ����ڵ㡢������Ϣ�ڴ� */
    pstNode = (APP_VC_BUFF_MSG_NODE_STRU *)PS_MEM_ALLOC(WUEPS_PID_VC, sizeof(APP_VC_BUFF_MSG_NODE_STRU));
    pNewMsg = (MsgBlock *)PS_MEM_ALLOC(WUEPS_PID_VC, pMsg->ulLength + VOS_MSG_HEAD_LENGTH);
    if ( (VOS_NULL_PTR == pstNode)
      || (VOS_NULL_PTR == pNewMsg) )
    {
        VC_ERR_LOG("APP_VC_AddBufferMsg: Mem Alloc Failed! ");
        return;
    }

    /* ��ʼ���ڵ� */
    PS_MEM_SET(pstNode, 0, sizeof(APP_VC_BUFF_MSG_NODE_STRU));
    PS_MEM_CPY(pNewMsg, pMsg, pMsg->ulLength + VOS_MSG_HEAD_LENGTH);
    pstNode->pBuffMsg = pNewMsg;

    msp_list_add_tail(&pstNode->stList, &g_stVcStateMgmt.stBuffMsgListHead);

    g_stVcStateMgmt.ulBuffMsgCnt++;

    return;
}
/*lint +e429 +e830*/



VOS_VOID  APP_VC_AppSetVolumeProc(
    APP_VC_REQ_MSG_STRU                 *pstAppMsg
)
{
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;
    VOS_UINT32                          ulErrCode;
    VOS_INT16                           sVolume;

    /* ���µ�ǰ��Clentid�����ڷ��� */
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);

    PS_MEM_SET(&stClvlVolume, 0x00, sizeof(stClvlVolume));
    ulErrCode = MN_ERR_NO_ERROR;
    /* �����ֵ��80����ΪAT�Ķ��巶ΧΪ0~92,���������֮�䶨��ķ�ΧΪ-80~12 */
    sVolume = pstAppMsg->aucContent[0] - 80;

    /*��ȡnv��Ϣ*/
    APP_VC_GetClvlVolume(&stClvlVolume);

    /* �Ѿ����������������У�����ֱ�ӷ��� */
    if (VOS_TRUE == stClvlVolume.usSetVoiceFlg)
    {
        if (sVolume != APP_VC_GetCurrVolume(&stClvlVolume))
        {
            ulErrCode = MN_ERR_SYS_BUSY;
        }

        APP_VC_ReportEvent(APP_VC_EVT_SET_VOLUME, ulErrCode);
        return;
    }

    if (VOS_OK != APP_VC_SendSetVolumeReq(VCVOICE_VOLUME_TARGET_DOWN, sVolume))
    {
        /*�ϱ�*/
        APP_VC_ReportEvent(APP_VC_EVT_SET_VOLUME, MN_ERR_UNSPECIFIED);
        return;
    }

    APP_VC_SetCurrVolume(&stClvlVolume, sVolume);
    stClvlVolume.usSetVoiceFlg = VOS_TRUE;
    APP_VC_SaveClvlVolume(&stClvlVolume);

    APP_VC_UpdateState(APP_VC_S_WAIT_AT_SET_VOLUME_RSLT);
    APP_VC_StartProtectTimer(APP_VC_TIMER_SET_VOLUME);

    return;
}
VOS_VOID  APP_VC_AppQryVolumeProc(
    APP_VC_REQ_MSG_STRU                 *pstAppMsg
)
{
    /* ˢ�¿ͻ�����Ϣ */
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);

    APP_VC_ReportEvent(APP_VC_EVT_GET_VOLUME, MN_ERR_NO_ERROR);

    return;
}


VOS_VOID  APP_VC_AppSetModeProc(
    APP_VC_REQ_MSG_STRU                 *pstAppMsg
)
{
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;
    VOS_UINT32                          ulErrCode;
    APP_VC_IOCTL_AUDIO_IN_DEV_ENUM_U16  enAudioInDev;
    APP_VC_IOCTL_AUDIO_OUT_DEV_ENUM_U16 enAudioOutDev;
    VC_PHY_DEVICE_MODE_ENUM_U16         usDeviceMode;

    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);
    usDeviceMode    = pstAppMsg->aucContent[0];
    ulErrCode       = MN_ERR_NO_ERROR;

    /*��ȡnv��Ϣ*/
    PS_MEM_SET(&stClvlVolume, 0x00, sizeof(stClvlVolume));

    APP_VC_GetClvlVolume(&stClvlVolume);

    if (VOS_TRUE == stClvlVolume.usSetVoiceFlg)
    {
        /* ��ǰ���������豸ģʽ������������ִ�� */
        VC_WARN_LOG("APP_VC_AppSetModeProc: set cmd has perfermed now!");

        /* �û����õ��豸ģʽ�뵱ǰ�������õ��豸ģʽ��ͬ����ظ�ʧ�� */
        if (usDeviceMode != stClvlVolume.usCurrDevMode)
        {
            ulErrCode = MN_ERR_SYS_BUSY;
        }

        /* ��AT�ظ���� */
        APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, ulErrCode);

        return ;
    }

    if (VOS_FALSE == g_stVcStateMgmt.ucPcVoiceSupportFlag)
    {
        if (APP_VC_INVALID_DEV_HANDLE == APP_VC_GetDevHandle())
        {
            /*�ϱ�����ʧ��*/
            APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
            return;
        }

        /* �����ͳ����豸����Ҫ����ģ��codec */
        if ((VC_PHY_DEVICE_MODE_BLUETOOTH != stClvlVolume.usCurrDevMode)
         && (VC_PHY_DEVICE_MODE_CAR_FREE != stClvlVolume.usCurrDevMode))
        {
            enAudioInDev = APP_VC_GetInDevMode(stClvlVolume.usCurrDevMode);
            enAudioOutDev = APP_VC_GetOutDevMode(stClvlVolume.usCurrDevMode);

            if (APP_VC_IN_DEV_BUTT == enAudioInDev)
            {
                /*�ϱ�����ʧ��*/
                APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
                return;
            }

            if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_IN_DEV_UNSELECT, enAudioInDev))
            {
                /*�ϱ�����ʧ��*/
                APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
                return;
            }

            if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_OUT_DEV_UNSELECT, enAudioOutDev))
            {
                /*�ϱ�����ʧ��*/
                APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
                return;
            }
        }

        /* �����ͳ����豸����Ҫ����ģ��codec */
        if ((VC_PHY_DEVICE_MODE_BLUETOOTH != usDeviceMode)
         && (VC_PHY_DEVICE_MODE_CAR_FREE != usDeviceMode))
        {
            enAudioInDev = APP_VC_GetInDevMode(usDeviceMode);
            enAudioOutDev = APP_VC_GetOutDevMode(usDeviceMode);
            if (APP_VC_IN_DEV_BUTT == enAudioInDev)
            {
                /*�ϱ�����ʧ��*/
                APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
                return;
            }

            if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_IN_DEV_SELECT, enAudioInDev))
            {
                /*�ϱ�����ʧ��*/
                APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
                return;
            }

            if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_OUT_DEV_SELECT, enAudioOutDev))
            {
                /*�ϱ�����ʧ��*/
                APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
                return;
            }
        }

    }

    if (VOS_OK != APP_VC_SendSetDeviceReq(usDeviceMode))
    {
        /*�ϱ�����ʧ��*/
        APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
        return;
    }

    /* ���õ�ǰ�������ù����е�FLAG */
    stClvlVolume.usCurrDevMode = usDeviceMode;
    stClvlVolume.usSetVoiceFlg = VOS_TRUE;

    /* ����NV�� */
    APP_VC_SaveClvlVolume(&stClvlVolume);

    if (VOS_OK != APP_VC_SendSetVolumeReq(VCVOICE_VOLUME_TARGET_DOWN,
                                          APP_VC_GetCurrVolume(&stClvlVolume)))
    {
        /*�ϱ�����ʧ��*/
        APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
        return;
    }

    APP_VC_UpdateState(APP_VC_S_WAIT_AT_SET_DEV_RSLT);
    APP_VC_StartProtectTimer(APP_VC_TIMER_SET_DEV);

    return;
}
VOS_VOID  APP_VC_AppQryModeReqProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_REQ_MSG_STRU                *pstAppReqMsg;                           /* ������Ϣָ�� */
    MN_AT_IND_EVT_STRU                 *pstMsg;                                 /* ������Ϣָ�� */
    APP_VC_EVENT_INFO_STRU              stAppCnfMsg;
    VOS_UINT32                          ulTmpAddr;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pstAppReqMsg    = pstAppMsg;
    pstMsg          = VOS_NULL_PTR;
    usLength        = 0;

    (VOS_VOID)VOS_MemSet(&stAppCnfMsg, 0x00, sizeof(APP_VC_EVENT_INFO_STRU));

    /* ��ѯ��ǰ�����豸ģʽ */
    stAppCnfMsg.enDevMode               = APP_VC_GetCurrDevMode();

    /* Ϊ��Ϣ������ڴ� */
    usLength        = ((sizeof(MN_AT_IND_EVT_STRU) + sizeof(APP_VC_EVENT_INFO_STRU)) - VOS_MSG_HEAD_LENGTH) - 4;
    pstMsg          = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, usLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        VC_ERR_LOG("APP_VC_AppQryModeReqProc:ERROR:Alloc Msg");
        return;
    }

    /* ��װ��Ϣͷ����Ϣ�� */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_VC;
    pstMsg->ulReceiverPid               = WUEPS_PID_AT;

    pstMsg->usMsgName                   = APP_VC_MSG_CNF_QRY_MODE;
    pstMsg->aucReserved1[0]             = 0;
    pstMsg->aucReserved1[1]             = 0;
    pstMsg->clientId                    = MN_GetRealClientId(pstAppReqMsg->clientId, WUEPS_PID_VC);
    pstMsg->usLen                       = usLength;

    /* ��д����Ϣ���� */
    ulTmpAddr  = (VOS_UINT32)pstMsg->aucContent;
    PS_MEM_CPY((VOS_VOID *)ulTmpAddr, &stAppCnfMsg, sizeof(APP_VC_EVENT_INFO_STRU));

    /*������Ϣ��AT_PID;*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_ERR_LOG("APP_VC_AppQryModeProc:ERROR");
        (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstMsg);
        return;
    }

    return;
}


VOS_VOID  APP_VC_AppSetPortReqProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_REQ_MSG_STRU                *pstAppReqMsg;                           /* ������Ϣָ�� */
    MN_AT_IND_EVT_STRU                 *pstMsg;                                 /* ������Ϣָ�� */
    APP_VC_EVENT_INFO_STRU              stAppCnfMsg;
    APP_VC_VOICE_PORT_ENUM_U8           ucVoicePort;
    VOS_UINT32                          ulTmpAddr;
    VOS_UINT16                          usLength;
    VOS_UINT32                          ulStatus;

    /* ��ʼ�� */
    pstAppReqMsg    = pstAppMsg;
    pstMsg          = VOS_NULL_PTR;
    usLength        = 0;
    ulStatus        = OM_PCV_CHANNEL_BUTT;
    ucVoicePort     = APP_VC_VOICE_PORT_BUTT;

    (VOS_VOID)VOS_MemSet(&stAppCnfMsg, 0x00, sizeof(APP_VC_EVENT_INFO_STRU));

    /* ��AT��������Ϣ�У���ȡҪ���õ������豸�˿ں� */
    PS_MEM_CPY(&ucVoicePort, pstAppReqMsg->aucContent, sizeof(APP_VC_VOICE_PORT_ENUM_U8));

    /* Ϊ��Ϣ������ڴ� */
    usLength        = ((sizeof(MN_AT_IND_EVT_STRU) + sizeof(APP_VC_EVENT_INFO_STRU)) - VOS_MSG_HEAD_LENGTH) - 4;
    pstMsg          = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, usLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        VC_ERR_LOG("APP_VC_AppQryModeReqProc:ERROR:Alloc Msg");
        return;
    }

    if (APP_VC_VOICE_PORT_BUTT == g_stVcStateMgmt.ucVoicePort)
    {
        /* ��һ�����������˿ڣ�״̬Ϊ���� */
        ulStatus = OM_PCV_CHANNEL_OPEN;
    }
    else if (ucVoicePort == g_stVcStateMgmt.ucVoicePort)
    {
        /* ���õ����Զ˿��뵱ǰ�������˿���ͬ��ֱ�ӷ��سɹ� */
        stAppCnfMsg.bSuccess        = VOS_TRUE;
    }
    else
    {
        /* �����������˿ڣ�״̬Ϊ�ı� */
        ulStatus = OM_PCV_CHANNEL_SWITCH;
    }

    /*����OM�ӿ����������˿�*/
    if (VOS_TRUE == g_stVcStateMgmt.bInCall)
    {
        if (TAF_SUCCESS == APP_VC_SendVcReqToOm(ulStatus, ucVoicePort))
        {
            g_stVcStateMgmt.ucVoicePort = ucVoicePort;
            stAppCnfMsg.bSuccess        = VOS_TRUE;
        }
        else
        {
            stAppCnfMsg.bSuccess        = VOS_FALSE;
        }
    }
    else
    {
        g_stVcStateMgmt.ucVoicePort = ucVoicePort;
        stAppCnfMsg.bSuccess        = VOS_TRUE;
    }

    /* ��װ��Ϣͷ����Ϣ�� */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_VC;
    pstMsg->ulReceiverPid               = WUEPS_PID_AT;

    pstMsg->usMsgName                   = APP_VC_MSG_CNF_SET_PORT;
    pstMsg->aucReserved1[0]             = 0;
    pstMsg->aucReserved1[1]             = 0;
    pstMsg->clientId                    = MN_GetRealClientId(pstAppReqMsg->clientId, WUEPS_PID_VC);
    pstMsg->usLen                       = usLength;

    /* ��д����Ϣ���� */
    ulTmpAddr  = (VOS_UINT32)pstMsg->aucContent;
    PS_MEM_CPY((VOS_VOID *)ulTmpAddr, &stAppCnfMsg, sizeof(APP_VC_EVENT_INFO_STRU));

    /*������Ϣ��AT_PID;*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_ERR_LOG("APP_VC_AppQryModeProc:ERROR");
        (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstMsg);
        return;
    }

    return;
}


VOS_VOID  APP_VC_AppQryPortReqProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_REQ_MSG_STRU                *pstAppReqMsg;                           /* ������Ϣָ�� */
    MN_AT_IND_EVT_STRU                 *pstMsg;                                 /* ������Ϣָ�� */
    APP_VC_EVENT_INFO_STRU              stAppCnfMsg;
    VOS_UINT32                          ulTmpAddr;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pstAppReqMsg    = pstAppMsg;
    pstMsg          = VOS_NULL_PTR;
    usLength        = 0;
    (VOS_VOID)VOS_MemSet(&stAppCnfMsg, 0x00, sizeof(APP_VC_EVENT_INFO_STRU));

    /* �Ȼ�ȡ��ǰ�����豸�˿�,�ŵ��ط���AT����Ϣ��*/
    stAppCnfMsg.enVoicePort             = APP_VC_GetPcVoicePort();

    /* Ϊ��Ϣ������ڴ� */
    usLength        = ((sizeof(MN_AT_IND_EVT_STRU) + sizeof(APP_VC_EVENT_INFO_STRU)) - VOS_MSG_HEAD_LENGTH) - 4;
    pstMsg          = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, usLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        VC_ERR_LOG("APP_VC_AppQryModeReqProc:ERROR:Alloc Msg");
        return;
    }

    /* ��װ��Ϣͷ����Ϣ�� */
    pstMsg->ulReceiverCpuId             = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid                 = WUEPS_PID_VC;
    pstMsg->ulReceiverPid               = WUEPS_PID_AT;

    pstMsg->usMsgName                   = APP_VC_MSG_CNF_QRY_PORT;
    pstMsg->aucReserved1[0]             = 0;
    pstMsg->aucReserved1[1]             = 0;
    pstMsg->clientId                    = MN_GetRealClientId(pstAppReqMsg->clientId, WUEPS_PID_VC);
    pstMsg->usLen                       = usLength;

    /* ��д����Ϣ���� */
    ulTmpAddr  = (VOS_UINT32)pstMsg->aucContent;
    PS_MEM_CPY((VOS_VOID *)ulTmpAddr, &stAppCnfMsg, sizeof(APP_VC_EVENT_INFO_STRU));

    /*������Ϣ��AT_PID;*/
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_ERR_LOG("APP_VC_AppQryModeProc:ERROR");
        (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstMsg);
        return;
    }

    return;
}


VOS_VOID APP_VC_AppSetMuteStatusProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_MUTE_STATUS_ENUM_UINT8       enMuteStatus;
    VOS_INT16                           sVolValue;

    enMuteStatus = pstAppMsg->aucContent[0];

    /* ˢ�¿ͻ�����Ϣ */
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);
    /* ���ݾ���״̬���ö�Ӧ������ֵ */
    sVolValue = (APP_VC_MUTE_STATUS_UNMUTED == enMuteStatus) ?
                APP_VC_UNMUTED_VOLUME : APP_VC_MUTED_VOLUME;

    if (VOS_OK != APP_VC_SendSetVolumeReq(VCVOICE_VOLUME_TARGET_UP,
                                          sVolValue))
    {
        APP_VC_ReportEvent(APP_VC_EVT_SET_MUTE_STATUS, MN_ERR_UNSPECIFIED);
        return;
    }

    APP_VC_UpdataPreMuteStatus(APP_VC_GetCurrMuteStatus());
    APP_VC_UpdataCurrMuteStatus(enMuteStatus);
    APP_VC_UpdateState(APP_VC_S_WAIT_AT_SET_MUTE_STATUS_RSLT);
    APP_VC_StartProtectTimer(APP_VC_TIMER_SET_VOLUME);

    return;
}


VOS_VOID  APP_VC_AppGetMuteStatusProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    /* ˢ�¿ͻ�����Ϣ */
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);

    APP_VC_ReportEvent(APP_VC_EVT_GET_MUTE_STATUS, MN_ERR_NO_ERROR);

    return;
}


VOS_VOID  APP_VC_AppSetForeGroundProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);

    /* �����ڵ绰�����·�CODEC ����������Ϣ */
    if ( VOS_TRUE == APP_VC_GetCallStatus() )
    {
        if (VOS_OK == APP_VC_SendSetForeGroundReq())
        {
            APP_VC_UpdateState(APP_VC_S_WAIT_SET_FOREGROUND_RSLT);
            /* ����������ʱ�����ȴ�CODEC�ظ���Ϣ */
            APP_VC_StartProtectTimer(APP_VC_TIMER_SET_FOREGROUND);
        }
        else
        {
            VC_ERR_LOG("APP_VC_AppSetForeGroundProc: SEND FOREGROUND REQ MSG FAILED.");

            APP_VC_SendSetForeGroundCnf( g_stVcStateMgmt.clientId, VCVOICE_EXECUTE_RSLT_FAIL);
        }
    }
    /* �������ڵ绰����ֱ�ӻظ�AT ǰ̨ģʽ����ʧ�� */
    else
    {
        VC_ERR_LOG("APP_VC_AppSetForeGroundProc: NO CALL EXIST.");

        APP_VC_SendSetForeGroundCnf( g_stVcStateMgmt.clientId, VCVOICE_EXECUTE_RSLT_FAIL);
    }
}


VOS_VOID  APP_VC_AppSetBackGroundProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);

    /* VC �жϵ�ǰ�Ƿ��е绰���� */
    if ( VOS_TRUE == APP_VC_GetCallStatus() )
    {
        if ( VOS_OK == APP_VC_SendSetBackGroundReq() )
        {
            APP_VC_UpdateState(APP_VC_S_WAIT_SET_BACKGROUND_RSLT);
            /* ����������ʱ�����ȴ�CODEC�ظ���Ϣ */
            APP_VC_StartProtectTimer(APP_VC_TIMER_SET_BACKGROUND);
        }
        else
        {
            VC_ERR_LOG("APP_VC_AppSetBackGroundProc: SEND BACKGROUND REQ MSG FAILED.");

            APP_VC_SendSetBackGroundCnf(g_stVcStateMgmt.clientId, VCVOICE_EXECUTE_RSLT_FAIL);
        }
    }
    else
    {
        VC_ERR_LOG("APP_VC_AppSetBackGroundProc: NO CALL EXIST.");

        APP_VC_SendSetBackGroundCnf(g_stVcStateMgmt.clientId, VCVOICE_EXECUTE_RSLT_FAIL);
    }
}


VOS_VOID  APP_VC_AppQryGroundProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);

    /* VC �жϵ�ǰ�Ƿ��е绰���� */
    if ( VOS_TRUE == APP_VC_GetCallStatus() )
    {
        if ( VOS_OK == APP_VC_SendGroundQry() )
        {
            APP_VC_UpdateState(APP_VC_S_WAIT_QRY_GROUND_RSLT);
            /* ����������ʱ�����ȴ�CODEC�ظ���Ϣ */
            APP_VC_StartProtectTimer(APP_VC_TIMER_QRY_GROUND);
        }
        else
        {
            VC_ERR_LOG("APP_VC_AppQryGroundProc: SEND GROUND QRY MSG FAILED.");

            APP_VC_SendGroundRsp(g_stVcStateMgmt.clientId, VCVOICE_GROUND_BUTT, VOS_ERR);
        }
    }
    else
    {
        VC_ERR_LOG("APP_VC_AppQryGroundProc: NO CALL EXIST.");

        APP_VC_SendGroundRsp(g_stVcStateMgmt.clientId, VCVOICE_GROUND_BUTT, VOS_ERR);
    }
}


VOS_VOID  APP_VC_AppSetModemLoopProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    VCVOICE_LOOP_ENUM_UINT16            enModemLoop;
    APP_VC_IOCTL_AUDIO_IN_DEV_ENUM_U16  enAudioInDev;
    APP_VC_IOCTL_AUDIO_OUT_DEV_ENUM_U16 enAudioOutDev;

    VC_PHY_DEVICE_MODE_ENUM_U16         enCurrDevMode;
    enCurrDevMode = APP_VC_GetCurrDevMode();

    /* ��ȡ�����������ص�״̬:�˳�������������� */
    enModemLoop = (VCVOICE_LOOP_ENUM_UINT16)pstAppMsg->aucContent[0];

    if (VCVOICE_WORK_TYPE_TEST != APP_VC_GetWorkType())
    {
        if (VCVOICE_LOOP_START == enModemLoop)
        {
            if (APP_VC_INVALID_DEV_HANDLE != APP_VC_GetDevHandle())
            {
                if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_PCM_MODE_SET, 0))
                {
                    VC_WARN_LOG("APP_VC_AppSetModemLoopProc: set PCM mode Fail" );
                }

                if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_OPEN, 0))
                {
                    VC_WARN_LOG("APP_VC_AppSetModemLoopProc: Open codec Fail" );
                }

                if ((VC_PHY_DEVICE_MODE_BLUETOOTH != enCurrDevMode)
                 && (VC_PHY_DEVICE_MODE_CAR_FREE != enCurrDevMode))
                {
                    enAudioInDev = APP_VC_GetInDevMode(enCurrDevMode);
                    enAudioOutDev = APP_VC_GetOutDevMode(enCurrDevMode);
                    if (APP_VC_IN_DEV_BUTT == enAudioInDev)
                    {
                        VC_WARN_LOG("APP_VC_CallChannelOpenProc: GET IN_OUT_DEV Fail" );
                        enAudioInDev    = APP_VC_IN_DEV_HEADSET_EXTERNAL_MIC;
                        enAudioOutDev   = APP_VC_OUT_DEV_HEADSET_EXTERNAL_MIC;
                    }

                    if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_IN_DEV_SELECT, enAudioInDev))
                    {
                        (VOS_VOID)DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_CLOSE, 0);
                        VC_WARN_LOG("APP_VC_CallChannelOpenProc: IN_DEV_SELECT Fail" );
                    }

                    if (VOS_OK != DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_OUT_DEV_SELECT, enAudioOutDev))
                    {
                        (VOS_VOID)DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_CLOSE, 0);
                        VC_WARN_LOG("APP_VC_CallChannelOpenProc: OUT_DEV_SELECT Fail" );
                    }
                }
            }
        }
        else
        {
            (VOS_VOID)DRV_CODEC_IOCTL(APP_VC_GetDevHandle(), APP_VC_IOCTL_AUDIO_VOICE_CLOSE, 0);
        }
    }

    if (VOS_OK != APP_VC_SendSetModemLoopReq(enModemLoop))
    {
        VC_ERR_LOG("APP_VC_AppSetModemLoopProc: SEND SET MODEMLOOP REQ MSG FAILED.");
    }

    return;
}

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  APP_VC_ImsaStartHifiNtfProc(IMSA_VC_START_HIFI_NTF_STRU* pstMsg)
{
    CALL_VC_CHANNEL_INFO_STRU                               stChanInfo;
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause;
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32                     enImsaCause;

    enVcCause = APP_VC_OPEN_CHANNEL_CAUSE_SUCC;


    /* ����ȫ�ֱ�������¼��IMSAҪ����HIFI */
    g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_IMSA;


    /* ����һ��CALL_VC_CHANNEL_INFO_STRU��Ϣ */
    PS_MEM_SET(&stChanInfo, 0, sizeof(stChanInfo));
    stChanInfo.stChannelParam.enMode        = CALL_VC_MODE_IMS_EUTRAN;
    stChanInfo.stChannelParam.enCodecType   =
            APP_VC_ConvertImsaCodeTypeToCallCodeType(pstMsg->enCodeType);

    /* �ŵ�����ʧ�ܣ���IMSA�����쳣��Ϣ */
    if (VOS_FALSE == APP_VC_CallChannelOpenProc(&stChanInfo, &enVcCause))
    {
        /* ��VC��ʧ��ԭ��ֵת����IMSA���쳣ԭ��ֵ */
        enImsaCause = APP_VC_ConvertVcOpenChannelFailCauseToImsaExceptionCause(enVcCause);

        /* ��������ŵ�ʱ�쳣����IMSA����ExceptionNtf��Ϣ��
            ͬʱ����ȫ�ֱ���enStartHifiOrig */
        APP_VC_SendImsaExceptionNtf(enImsaCause);

        /* ������ά�ɲ���Ϣ */
        APP_VC_LogEndCallReq(enVcCause);

        g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;
    }

    return;

}
VOS_VOID  APP_VC_ImsaStopHifiNtfProc(IMSA_VC_STOP_HIFI_NTF_STRU* pstMsg)
{
    /* �����쳣����,�����ǰ�Ĺ���ģʽΪGU��������Ϣ */
    if (CALL_VC_MODE_IMS_EUTRAN != APP_VC_GetRadioMode())
    {
        return;
    }


    /* ���ŵ��ر�ʱ�Ĵ�����ͬ��ֱ�ӵ������к��� */
    APP_VC_CallChannelCloseProc();

}


VOS_VOID  APP_VC_ImsaHifiParaChangeNtfProc(IMSA_VC_HIFI_PARA_CHANGED_NTF_STRU* pstMsg)
{
    CALL_VC_CHANNEL_INFO_STRU           stChanInfo;

    /* �ŵ������ı䣬���ʲ���ʧ��ʱ����Ҫ����ͨ������ʱҪ����ȫ�ֱ������ѽ���ͨ�������͸���Ӧ��ģ�� */
    g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_IMSA;

    /* ����һ��CALL_VC_CHANNEL_INFO_STRU��Ϣ */
    PS_MEM_SET(&stChanInfo, 0, sizeof(stChanInfo));
    stChanInfo.stChannelParam.enMode = CALL_VC_MODE_IMS_EUTRAN;
    stChanInfo.stChannelParam.enCodecType =
        APP_VC_ConvertImsaCodeTypeToCallCodeType(pstMsg->enCodeType);

    /* ���ŵ������ı�ʱ�Ĵ�����ͬ��ֱ�ӵ������к��� */
    APP_VC_CallChannelParaChangeProc(&stChanInfo);

}
#endif

/* Added by w00316404 for TTY MODE, 2015-02-07, begin */
/*****************************************************************************
 �� �� ��  : APP_VC_AppQryTTYModeProc
 ��������  : ����AT�������Ϣ
 �������  : pstAppMsg - AT �·���ģʽ��ѯ������Ϣ
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޶���¼  :
  1.��    ��   : 2015��02��07��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  APP_VC_AppQryTTYModeProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    MN_AT_IND_EVT_STRU                 *pstMsg;                                 /* ������Ϣָ�� */
    APP_VC_QRY_TTYMODE_CNF_STRU         stAppCnfMsg;
    TAF_NV_TTY_CFG_STRU                 stTTYCfgStru;
    VOS_UINT16                          usLength;
    TAF_VC_TTYMODE_ENUM_UINT8           enTTYMode;

    /* ��ʼ�� */
    pstMsg          = VOS_NULL_PTR;
    usLength        = 0;
    PS_MEM_SET(&stAppCnfMsg, 0x00, sizeof(APP_VC_QRY_TTYMODE_CNF_STRU));
    PS_MEM_SET(&stTTYCfgStru, 0x00, sizeof(TAF_NV_TTY_CFG_STRU));

    /* ��ȡNV�� */
    enTTYMode = APP_VC_GetTTYMode();
    stAppCnfMsg.enTTYMode = (TAF_VC_TTYMODE_ENUM_UINT8)enTTYMode;
    if (TAF_VC_TTYMODE_BUTT == enTTYMode)
    {
        stAppCnfMsg.ucQryRslt = VOS_ERR;
    }
    else
    {
        stAppCnfMsg.ucQryRslt = VOS_OK;
    }

    /* Ϊ��Ϣ������ڴ� */
    usLength        = sizeof(MN_AT_IND_EVT_STRU) + sizeof(APP_VC_QRY_TTYMODE_CNF_STRU) - VOS_MSG_HEAD_LENGTH - 4;
    pstMsg          = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, usLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        VC_ERR_LOG("TAF_VC_AppQryTTYModeProc: Alloc Msg ERROR!");
        return;
    }

    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH, 0x00, usLength);

    /* ��װ��Ϣͷ����Ϣ�� */
    pstMsg->ulReceiverPid               = WUEPS_PID_AT;
    pstMsg->usMsgName                   = APP_VC_MSG_QRY_TTYMODE_CNF;
    pstMsg->clientId                    = MN_GetRealClientId(pstAppMsg->clientId, WUEPS_PID_VC);
    pstMsg->usLen                       = usLength;

    /* ��д����Ϣ���� */
    PS_MEM_CPY(&pstMsg->aucContent[0], &stAppCnfMsg, sizeof(APP_VC_QRY_TTYMODE_CNF_STRU));

    /* ������Ϣ��AT_PID */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_ERR_LOG("APP_VC_AppQryModeProc: Send Msg ERROR!");
        (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstMsg);
    }

    return;
}

/*****************************************************************************
 �� �� ��  : APP_VC_AppSetTTYModeProc
 ��������  : ����AT�������Ϣ
 �������  : pstAppMsg - AT �·�������TTYģʽ����Ϣ
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :
 �޶���¼  :
  1.��    ��   : 2015��02��07��
    ��    ��   : w00316404
    �޸�����   : ��������
*****************************************************************************/
VOS_VOID  APP_VC_AppSetTTYModeProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    MN_AT_IND_EVT_STRU                 *pstMsg          = VOS_NULL_PTR;         /* ������Ϣָ�� */
    APP_VC_SET_TTYMODE_REQ_STRU        *pstAppReqMsg    = VOS_NULL_PTR;
    VOS_UINT32                         *pulRslt;
    VOS_UINT16                          usLength;

    /* ��ʼ�� */
    pstAppReqMsg    = (APP_VC_SET_TTYMODE_REQ_STRU *)pstAppMsg->aucContent;
    usLength        = 0;

    /* Ϊ��Ϣ������ڴ� */
    usLength        = sizeof(MN_AT_IND_EVT_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsg          = (MN_AT_IND_EVT_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, usLength);
    if (VOS_NULL_PTR == pstMsg)
    {
        VC_ERR_LOG("TAF_VC_AppSetTTYModeProc: ERROR: Alloc Msg!");
        return;
    }

    PS_MEM_SET((VOS_CHAR *)pstMsg + VOS_MSG_HEAD_LENGTH, 0x00, usLength);

    pulRslt  = (VOS_UINT32 *)pstMsg->aucContent;

    /* �����ڵ绰����ֱ�ӻظ�AT TTYģʽ����ʧ�� */
    if ( VOS_TRUE == APP_VC_GetCallStatus() )
    {
        VC_ERR_LOG("TAF_VC_AppSetTTYModeProc: ERROR: CALL EXIST!");
        *pulRslt = VOS_ERR;
    }
    /* �����ڵ绰�����TTY MODE д�뵽NV���� */
    else
    {
        *pulRslt = APP_VC_SetTTYMode(pstAppReqMsg->enTTYMode);
    }

    /* ��װ��Ϣͷ����Ϣ�� */
    pstMsg->ulReceiverPid               = WUEPS_PID_AT;
    pstMsg->usMsgName                   = APP_VC_MSG_SET_TTYMODE_CNF;
    pstMsg->clientId                    = MN_GetRealClientId(pstAppMsg->clientId, WUEPS_PID_VC);
    pstMsg->usLen                       = usLength;

    /* ������Ϣ��AT_PID */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_ERR_LOG("TAF_VC_AppSetTTYModeProc: ERROR!");
        (VOS_VOID)VOS_FreeMsg(WUEPS_PID_VC, pstMsg);
        return;
    }

    return;
}
/* Added by w00316404 for TTY MODE, 2015-02-07, end */



VOS_VOID  APP_VC_AtParaProc(APP_VC_REQ_MSG_STRU *pstAppMsg)
{

/*�طŹ��ָ̻�ȫ�ֱ���*/
#ifdef __PS_WIN32_RECUR__
        if ( VOS_TRUE == NAS_VC_RestoreContextData((struct MsgCB *)pstAppMsg))
        {
            return;
        }
#endif
    /*�����ǰ��״̬����NULL�Ļ�,������Ϣ,����*/
    if (APP_VC_S_NULL != APP_VC_GetState())
    {
        /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
        APP_VC_AddBufferMsg((MsgBlock *)pstAppMsg);
        /* Modified by w00316404 for OPT VC, 2015-02-07, End */
        return;
    }

    switch (pstAppMsg->enMsgName)
    {
        case APP_VC_MSG_REQ_SET_VOLUME:
            APP_VC_AppSetVolumeProc(pstAppMsg);
            break;

        case APP_VC_MSG_REQ_QRY_VOLUME:
            APP_VC_AppQryVolumeProc(pstAppMsg);
            break;

        case APP_VC_MSG_REQ_SET_MODE:
            APP_VC_AppSetModeProc(pstAppMsg);
            break;

        case APP_VC_MSG_REQ_QRY_MODE:
            APP_VC_AppQryModeReqProc(pstAppMsg);
            break;

        case APP_VC_MSG_REQ_SET_PORT:
            APP_VC_AppSetPortReqProc(pstAppMsg);
            break;

        case APP_VC_MSG_REQ_QRY_PORT:
            APP_VC_AppQryPortReqProc(pstAppMsg);
            break;

        case APP_VC_MSG_SET_MUTE_STATUS_REQ:
            APP_VC_AppSetMuteStatusProc(pstAppMsg);
            break;

        case APP_VC_MSG_GET_MUTE_STATUS_REQ:
            APP_VC_AppGetMuteStatusProc(pstAppMsg);
            break;

        case APP_VC_MSG_SET_FOREGROUND_REQ:
            APP_VC_AppSetForeGroundProc(pstAppMsg);
            break;

        case APP_VC_MSG_SET_BACKGROUND_REQ:
            APP_VC_AppSetBackGroundProc(pstAppMsg);
            break;

        case APP_VC_MSG_FOREGROUND_QRY:
            APP_VC_AppQryGroundProc(pstAppMsg);
            break;

        case APP_VC_MSG_SET_MODEMLOOP_REQ:
            APP_VC_AppSetModemLoopProc(pstAppMsg);
            break;

#if (FEATURE_ON == FEATURE_ECALL)
        case APP_VC_MSG_SET_MSD_REQ:
            APP_VC_SetMsdProc(pstAppMsg);
            break;

        case APP_VC_MSG_QRY_MSD_REQ:
            APP_VC_QryMsdProc(pstAppMsg);
            break;

        case APP_VC_MSG_SET_ECALL_CFG_REQ:
            APP_VC_SetEcallCfgProc(pstAppMsg);
            break;

        case APP_VC_MSG_QRY_ECALL_CFG_REQ:
            APP_VC_QryEcallCfgProc(pstAppMsg);
            break;
#endif

        /* Added by w00316404 for TTY MODE, 2015-02-07, begin */
        case APP_VC_MSG_QRY_TTYMODE_REQ:
            APP_VC_AppQryTTYModeProc(pstAppMsg);
            break;
        case APP_VC_MSG_SET_TTYMODE_REQ:
            APP_VC_AppSetTTYModeProc(pstAppMsg);
            break;
        /* Added by w00316404 for TTY MODE, 2015-02-07, end */

        default:
            VC_WARN_LOG1("APP_VC_AtParaSetProc: wrong MsgName.", pstAppMsg->enMsgName);
            break;
    }
}


VOS_VOID  APP_VC_SetDevCnfProc(
    VCVOICE_OP_RSLT_STRU              *pOpRsltMsg
)
{
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;
    VOS_UINT32                          ulErrCode;

    /* ��ȡNV��Ϣ */
    PS_MEM_SET(&stClvlVolume, 0x00, sizeof(stClvlVolume));

    APP_VC_GetClvlVolume(&stClvlVolume);
    ulErrCode = MN_ERR_NO_ERROR;

    if(pOpRsltMsg->enExeRslt != VCVOICE_EXECUTE_RSLT_SUCC)
    {
        if (APP_VC_S_WAIT_INTERNAL_SET_DEV_RSLT == APP_VC_GetState())
        {
            /* ֻ����״̬�����Ҷϵ绰 */
            APP_VC_UpdateState(APP_VC_S_WAIT_INTERNAL_SET_START_RSLT);
            VC_WARN_LOG("APP_VC_HpaMsgProc: fail:S_WAIT_INTERNAL_SET_DEV to S_WAIT_INTERNAL_SET_START.");
            return;
        }
        else
        {
            /* �����豸ģʽ */
            stClvlVolume.usCurrDevMode = stClvlVolume.usPreDevMode;

            /* ���²������ */
            ulErrCode = MN_ERR_UNSPECIFIED;
        }
    }
    else
    {
        if (APP_VC_S_WAIT_INTERNAL_SET_DEV_RSLT == APP_VC_GetState())
        {
            APP_VC_UpdateState(APP_VC_S_WAIT_INTERNAL_SET_START_RSLT);
            return;
        }
    }

    stClvlVolume.usSetVoiceFlg = VOS_FALSE;
    APP_VC_SaveClvlVolume(&stClvlVolume);

    APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, ulErrCode);

    APP_VC_UpdateState(APP_VC_S_NULL);
    APP_VC_StopProtectTimer();
    /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
    APP_VC_BufferMsgProc();
    /* Modified by w00316404 for OPT VC, 2015-02-07, End */

    return;
}


VOS_VOID  APP_VC_StartCnfProc(
    VCVOICE_OP_RSLT_STRU              *pstMsg
)
{
    CALL_VC_CHANNEL_INFO_STRU           stChanInfo;

    if(pstMsg->enExeRslt != VCVOICE_EXECUTE_RSLT_SUCC)
    {
        /*ֻ����APP_VC_S_WAIT_INTERNAL_SET_DEV_START_RSLT״̬��ʱ��
          �Ż�Ҷϵ绰�����״̬��˵��֮ǰ�Ѿ��Ҷϵ绰��*/
        if ((APP_VC_S_WAIT_INTERNAL_SET_START_RSLT == APP_VC_GetState())
          ||(APP_VC_S_WAIT_INTERNAL_SET_DEV_RSLT == APP_VC_GetState()))
        {
#if (FEATURE_ON == FEATURE_IMS)
            if (APP_VC_START_HIFI_ORIG_IMSA == APP_VC_GetStartHifiOrig())
            {
                /* �����IMSA�����������󣬸�IMSA�ظ��쳣 */
                APP_VC_SendImsaExceptionNtf(VC_IMSA_EXCEPTION_CAUSE_SET_START_FAIL);
            }
            else
#endif
            {
                /*�����CALL�����������󣬷�����Ϣ��CALLģ�飬�Ҷϵ绰*/
                APP_VC_SendEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL);
            }

            APP_VC_LogEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_SET_START_FAIL);

            g_stVcStateMgmt.bInCall = VOS_FALSE;
            g_stVcStateMgmt.bParaUpdate = VOS_FALSE;
        }
    }
    else
    {
        if (VOS_TRUE == g_stVcStateMgmt.bParaUpdate)
        {
            APP_VC_UpdateState(APP_VC_S_NULL);
            stChanInfo.stChannelParam.enMode = g_stVcStateMgmt.enRadioMode;
            stChanInfo.stChannelParam.enCodecType = g_stVcStateMgmt.enCodecType;
            g_stVcStateMgmt.bParaUpdate = VOS_FALSE;
            APP_VC_CallChannelParaChangeProc(&stChanInfo);

            /* ���ȫ�ֱ��� */
            g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;
            return;
        }
    }

    /* ���ȫ�ֱ��� */
    g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;
    APP_VC_UpdateState(APP_VC_S_NULL);
    APP_VC_StopProtectTimer();
    /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
    APP_VC_BufferMsgProc();
    /* Modified by w00316404 for OPT VC, 2015-02-07, End */

}
VOS_VOID APP_VC_SetVolumeCnfProc(
    VCVOICE_OP_RSLT_STRU              *pstOpRsltMsg
)
{
    APP_VC_EVENT_ENUM_U32               enEventType;
    VOS_UINT32                          ulErrCode;
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;

    ulErrCode = MN_ERR_NO_ERROR;
    PS_MEM_SET(&stClvlVolume, 0, sizeof(stClvlVolume));
    APP_VC_GetClvlVolume(&stClvlVolume);

    if (APP_VC_S_WAIT_AT_SET_VOLUME_RSLT == APP_VC_GetState())
    {
        enEventType = APP_VC_EVT_SET_VOLUME;

        stClvlVolume.usSetVoiceFlg = VOS_FALSE;

        if (VCVOICE_EXECUTE_RSLT_SUCC == pstOpRsltMsg->enExeRslt)
        {
            /* �������óɹ� */
            stClvlVolume.sPreVolume = APP_VC_GetCurrVolume(&stClvlVolume);
        }
        else
        {
            ulErrCode = MN_ERR_UNSPECIFIED;
            APP_VC_SetCurrVolume(&stClvlVolume, stClvlVolume.sPreVolume);
        }
    }
    else if (APP_VC_S_WAIT_AT_SET_MUTE_STATUS_RSLT == APP_VC_GetState())
    {
        enEventType = APP_VC_EVT_SET_MUTE_STATUS;

        if (VCVOICE_EXECUTE_RSLT_SUCC != pstOpRsltMsg->enExeRslt)
        {
            ulErrCode = MN_ERR_UNSPECIFIED;

            APP_VC_UpdataCurrMuteStatus(APP_VC_GetPreMuteStatus());
        }
    }
    else
    {
        /* ����绰ʱ��������������Ҫ��APP�ظ� */
        VC_NORM_LOG("APP_VC_SetVolumeCnfProc:set volume in call!");
        return;
    }

    /* ����NV�� */
    APP_VC_SaveClvlVolume(&stClvlVolume);

    APP_VC_ReportEvent(enEventType, ulErrCode);
    APP_VC_UpdateState(APP_VC_S_NULL);
    APP_VC_StopProtectTimer();
    /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
    APP_VC_BufferMsgProc();
    /* Modified by w00316404 for OPT VC, 2015-02-07, End */

    return;
 }
VOS_VOID APP_VC_ProcDtmfInd(
    VOICEVC_DTMF_IND_STRU              *pstDtmfInd
)
{
    VOICE_DTMF_CFG_NV_STRU              stNvDtmfCfg;

    /* ��ʼ����Ϣ���� */
    PS_MEM_SET(&stNvDtmfCfg, 0x0, sizeof(stNvDtmfCfg));

    /* ��ȡNV�ж�DTMF�����Ƿ�� */
    if (NV_OK != NV_Read(en_NV_VoiceDtmfCfg,
                         &stNvDtmfCfg,
                         sizeof(VOICE_DTMF_CFG_NV_STRU)))
    {
        VC_ERR_LOG("APP_VC_ProcDtmfInd: NV_Read en_NV_VoiceDtmfCfg fail!");
        return;
    }

    /* ���Dtmf Decoder����δʹ�ܣ���ʹ�յ�VC��Ϣ��Ҳ�����ϱ� */
    if (VOS_FALSE == stNvDtmfCfg.stDetCfgPara.uhwEnable)
    {
        VC_ERR_LOG("APP_VC_ProcDtmfInd: Dtmf Decoder function is disabled!");
        return;
    }

    /* �ж�DTMF�ź��Ƿ�Ϸ� */
    if (VOS_OK != TAF_SDC_CheckDtmfKey((VOS_CHAR*)&pstDtmfInd->usDtmfCode))
    {
        return;
    }

    if (VOS_OK != APP_VC_SendDtmfInd(pstDtmfInd))
    {
        return;
    }

    return;
}

VOS_VOID APP_VC_ForegroundCnfProc(
    VCVOICE_OP_RSLT_STRU              *pstOpRsltMsg
)
{
    if (APP_VC_S_WAIT_SET_FOREGROUND_RSLT == APP_VC_GetState())
    {
        /* ���յ�ǰ̨ģʽ���ûظ���Ϣ�Ĵ��� */
        APP_VC_SendSetForeGroundCnf(g_stVcStateMgmt.clientId, pstOpRsltMsg->enExeRslt);

        APP_VC_UpdateState(APP_VC_S_NULL);
        APP_VC_StopProtectTimer();
        /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
        APP_VC_BufferMsgProc();
        /* Modified by w00316404 for OPT VC, 2015-02-07, End */
    }

    return;
}
VOS_VOID APP_VC_BackgroundCnfProc(
    VCVOICE_OP_RSLT_STRU              *pstOpRsltMsg
)
{
    if (APP_VC_S_WAIT_SET_BACKGROUND_RSLT == APP_VC_GetState())
    {
        /* ���յ���̨ģʽ���ûظ���Ϣ�Ĵ��� */
        APP_VC_SendSetBackGroundCnf(g_stVcStateMgmt.clientId, pstOpRsltMsg->enExeRslt);

        APP_VC_UpdateState(APP_VC_S_NULL);
        APP_VC_StopProtectTimer();
        /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
        APP_VC_BufferMsgProc();
        /* Modified by w00316404 for OPT VC, 2015-02-07, End */
    }

    return;
}
VOS_VOID APP_VC_GroundRspProc(
    VCVOICE_OP_RSLT_STRU              *pstOpRsltMsg
)
{
    if (APP_VC_S_WAIT_QRY_GROUND_RSLT == APP_VC_GetState())
    {
        /* ���յ�ģʽ��ѯ�ظ���Ϣ�Ĵ��� */
        APP_VC_SendGroundRsp(g_stVcStateMgmt.clientId, ((VCVOICE_GROUND_RSP_STRU*)pstOpRsltMsg)->enState, VOS_OK);

        APP_VC_UpdateState(APP_VC_S_NULL);
        APP_VC_StopProtectTimer();
        /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
        APP_VC_BufferMsgProc();
        /* Modified by w00316404 for OPT VC, 2015-02-07, End */
    }

    return;
}
VOS_VOID  APP_VC_MedMsgProc(VOS_VOID *pMsg)
{
    VCVOICE_OP_RSLT_STRU              *pOpRsltMsg;

    pOpRsltMsg = (VCVOICE_OP_RSLT_STRU*)pMsg;

    /*��һ�����������̴�ӡ��Ϣ*/
    VC_INFO_LOG1("APP_VC_MedMsgProc: msg Name.", pOpRsltMsg->usMsgName);

    if ( (pOpRsltMsg->enExeRslt != VCVOICE_EXECUTE_RSLT_SUCC)
      && (pOpRsltMsg->usMsgName != ID_VOICE_VC_ECALL_TRANS_STATUS_NTF)
      && (pOpRsltMsg->usMsgName != ID_VOICE_VC_AL_ACK_REPORT_IND)
      && (pOpRsltMsg->usMsgName != ID_VOICE_VC_START_SEND_MSD_IND) )
    {
        /* ��ӡ�쳣��ӡ */
        VC_WARN_LOG1("APP_VC_MedMsgProc: Exe Result.", pOpRsltMsg->enExeRslt);
        VC_WARN_LOG1("APP_VC_MedMsgProc: msg Name.", pOpRsltMsg->usMsgName);

#if (FEATURE_ON == FEATURE_PTM)
        /* ��¼VC�����쳣log */
        APP_VC_AppVCFailErrRecord(pOpRsltMsg->usMsgName, pOpRsltMsg->enExeRslt);
#endif
    }

    switch (pOpRsltMsg->usMsgName)
    {
        case ID_VOICE_VC_START_CNF:
            APP_VC_StartCnfProc(pOpRsltMsg);
            break;

        case ID_VOICE_VC_SET_DEVICE_CNF:
            APP_VC_SetDevCnfProc(pOpRsltMsg);
            break;

        case ID_VOICE_VC_SET_VOLUME_CNF:
            /*�ϱ������������*/
            APP_VC_SetVolumeCnfProc(pOpRsltMsg);
            break;

        case ID_VOICE_VC_STOP_CNF:
        case ID_VOICE_VC_SET_CODEC_CNF:
            APP_VC_UpdateState(APP_VC_S_NULL);
            APP_VC_StopProtectTimer();
            /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
            APP_VC_BufferMsgProc();
            /* Modified by w00316404 for OPT VC, 2015-02-07, End */
            break;

        case ID_VOICE_VC_FOREGROUND_CNF:
            APP_VC_ForegroundCnfProc(pOpRsltMsg);
            break;

        case ID_VOICE_VC_BACKGROUND_CNF:
            APP_VC_BackgroundCnfProc(pOpRsltMsg);
            break;

        case ID_VOICE_VC_GROUND_RSP:
            APP_VC_GroundRspProc(pOpRsltMsg);
            break;

#if (FEATURE_ON == FEATURE_ECALL)
        case ID_VOICE_VC_ECALL_TRANS_STATUS_NTF:
            APP_VC_ReportEcallState(pMsg);
            break;

        case ID_VOICE_VC_SET_ECALLCFG_CNF:
            APP_VC_SetEcallCfgCnfProc(pOpRsltMsg->enExeRslt);
            break;

        case ID_VOICE_VC_AL_ACK_REPORT_IND:
            APP_VC_ReportAlAckProc(pMsg);
            break;
        case ID_VOICE_VC_START_SEND_MSD_IND:
            APP_VC_StartSendMsdData(pMsg);
            break;
#endif

        case ID_VOICE_VC_DTMF_IND:
            APP_VC_ProcDtmfInd((VOICEVC_DTMF_IND_STRU *)pMsg);
            break;


        default:
            VC_WARN_LOG1("APP_VC_MedMsgProc: wrong MsgName.", pOpRsltMsg->usMsgName);
            APP_VC_UpdateState(APP_VC_S_NULL);
            APP_VC_StopProtectTimer();
            /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
            APP_VC_BufferMsgProc();
            /* Modified by w00316404 for OPT VC, 2015-02-07, End */
            break;
    }

}

#if (FEATURE_ON == FEATURE_IMS)
VOS_VOID  APP_VC_ImsaMsgProc(VOS_VOID *pMsg)
{
    MSG_HEADER_STRU                     *pMsgHeader = VOS_NULL_PTR;

    pMsgHeader = (MSG_HEADER_STRU *)pMsg;

    /* ����Ѿ�����HIFI,���ұ�����Ϣ����ΪID_IMSA_VC_START_HIFI_NTF������������ */
    if ( (VOS_TRUE == APP_VC_GetCallStatus())
      && (ID_IMSA_VC_START_HIFI_NTF == pMsgHeader->ulMsgName) )
    {
        /* ����Ҫ֪ͨIMSA exception_nty,ֻ������ά�ɲ���Ϣ */
        APP_VC_LogEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_STARTED);

        return;
    }


    /* ���VC״̬��ΪNULL����ʾVC���ڴ�������Ϣ���ѵ�ǰ������Ϣ�Ȼ������� */
    if (APP_VC_S_NULL != APP_VC_GetState())
    {
        /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
        APP_VC_AddBufferImsaMsg(pMsg);
        /* Modified by w00316404 for OPT VC, 2015-02-07, End */
        return;
    }


    /* ����Ϣ���зַ� */
    switch (pMsgHeader->ulMsgName)
    {
        case ID_IMSA_VC_START_HIFI_NTF:
            APP_VC_ImsaStartHifiNtfProc(pMsg);
            break;

        case ID_IMSA_VC_STOP_HIFI_NTF:
            APP_VC_ImsaStopHifiNtfProc(pMsg);
            break;

        case ID_IMSA_VC_HIFI_PARA_CHANGED_NTF:
            APP_VC_ImsaHifiParaChangeNtfProc(pMsg);
            break;

        default:
            VC_WARN_LOG("APP_VC_ImsaMsgProc: wrong MsgName");

            break;
    }

}
#endif

/*lint -e424*/
/*****************************************************************************
 �� �� ��  : APP_VC_BufferMsgProc
 ��������  : ����VCģ�黺������е���Ϣ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��02��07��
    ��    ��   : W00316404
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID APP_VC_BufferMsgProc(VOS_VOID)
{
    APP_VC_BUFF_MSG_NODE_STRU          *pstNode     = VOS_NULL_PTR;
    MsgBlock                           *pBuffMsg    = VOS_NULL_PTR;

    if (0 == g_stVcStateMgmt.ulBuffMsgCnt)
    {
        /* �������Ϊ����ֱ�ӷ��� */
        VC_INFO_LOG("APP_VC_BufferMsgProc: No Buffer Message!");
        return;
    }

    /* �ӻ��������ȡ����Ϣ */
    pstNode     = msp_list_entry(g_stVcStateMgmt.stBuffMsgListHead.next, APP_VC_BUFF_MSG_NODE_STRU, stList);

    /* �ӻ��������ɾ���ڵ� */
    msp_list_del(&pstNode->stList);
    g_stVcStateMgmt.ulBuffMsgCnt--;

    /* ��������Ϣ */
    APP_VC_MsgProc(pstNode->pBuffMsg);

    /* �ͷ��ڴ� */
    pBuffMsg    = pstNode->pBuffMsg;

    PS_MEM_FREE(WUEPS_PID_VC, pstNode);

    PS_MEM_FREE(WUEPS_PID_VC, pBuffMsg);

    return;
}
/*lint +e424*/



VOS_VOID  APP_VC_StartTimeoutProc(VOS_VOID)
{
    CALL_VC_CHANNEL_INFO_STRU                               stChanInfo;
    APP_VC_OPEN_CHANNEL_FAIL_CAUSE_ENUM_UINT32              enVcCause;
#if (FEATURE_ON == FEATURE_IMS)
    VC_IMSA_EXCEPTION_CAUSE_ENUM_UINT32                     enImsaCause;
#endif
    enVcCause   = APP_VC_OPEN_CHANNEL_CAUSE_SUCC;

    if (VOS_TRUE == g_stVcStateMgmt.bParaUpdate)
    {
        APP_VC_UpdateState(APP_VC_S_NULL);
        stChanInfo.stChannelParam.enMode = g_stVcStateMgmt.enRadioMode;
        stChanInfo.stChannelParam.enCodecType = g_stVcStateMgmt.enCodecType;
        g_stVcStateMgmt.bParaUpdate = VOS_FALSE;
        if (VOS_FALSE == APP_VC_CallChannelOpenProc(&stChanInfo, &enVcCause))
        {
#if (FEATURE_ON == FEATURE_IMS)
            if (APP_VC_START_HIFI_ORIG_IMSA == APP_VC_GetStartHifiOrig())
            {
                /* ��VC��ʧ��ԭ��ֵת����IMSA���쳣ԭ��ֵ */
                enImsaCause = APP_VC_ConvertVcOpenChannelFailCauseToImsaExceptionCause(enVcCause);

                /* �����IMSA�����������󣬸�IMSA�ظ��쳣 */
                /* APP_VC_CallChannelOpenProcû��HIFI�Ƿ��Ѿ��������жϣ�����ʧ��ʱ֪ͨIMSA����HIFI�쳣 */
                APP_VC_SendImsaExceptionNtf(enImsaCause);
            }
            else
#endif
            {
                /*�����CALL�����������󣬷�����Ϣ��CALLģ�飬�Ҷϵ绰*/
                APP_VC_SendEndCallReq(enVcCause);
            }

            /* ������ά�ɲ���Ϣ */
            APP_VC_LogEndCallReq(enVcCause);

            /* ����ȫ�ֱ���enStartHifiOrig */
            g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;
        }
    }
    else
    {
#if (FEATURE_ON == FEATURE_IMS)
        if (APP_VC_START_HIFI_ORIG_IMSA == APP_VC_GetStartHifiOrig())
        {
            /* �����IMSA�����������󣬸�IMSA�ظ��쳣 */
            APP_VC_SendImsaExceptionNtf(VC_IMSA_EXCEPTION_CAUSE_TI_START_EXPIRED);
        }
        else
#endif
        {
            /*�����CALL�����������󣬷�����Ϣ��CALLģ�飬�Ҷϵ绰*/
            APP_VC_SendEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_TI_START_EXPIRED);
        }

        /* ������ά�ɲ���Ϣ */
        APP_VC_LogEndCallReq(APP_VC_OPEN_CHANNEL_FAIL_CAUSE_TI_START_EXPIRED);

        /* ����ȫ�ֱ���enStartHifiOrig */
        g_stVcStateMgmt.enStartHifiOrig = APP_VC_START_HIFI_ORIG_BUTT;

        g_stVcStateMgmt.bInCall = VOS_FALSE;
        APP_VC_UpdateState(APP_VC_S_NULL);
        /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
        APP_VC_BufferMsgProc();
        /* Modified by w00316404 for OPT VC, 2015-02-07, End */
    }

    return;

}


VOS_VOID  APP_VC_TimeoutMsgProc(VOS_VOID *pMsg)
{
    REL_TIMER_MSG                      *pTimerMsg;
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;
    VOS_UINT8                           ucRatType;

    pTimerMsg = (REL_TIMER_MSG*)pMsg;

    PS_MEM_SET(&stClvlVolume, 0x00, sizeof(stClvlVolume));

    /* ��ӡ��ʱ��timer���ƣ�״̬��λ */
    VC_WARN_LOG2("APP_VC_TimeoutMsgProc: Timer Name, state", (VOS_INT32)pTimerMsg->ulName, (VOS_INT32)APP_VC_GetState());

    NAS_MNTN_CsMedTimeOut(pTimerMsg->ulName);

 #if (FEATURE_ON == FEATURE_PTM)
    /* ��¼VC��ʱlog */
    APP_VC_AppVCFailErrRecord((VOS_UINT16)pTimerMsg->ulName, VCVOICE_EXECUTE_RSLT_BUTT);
 #endif

    switch(pTimerMsg->ulName)
    {
        /*������Ϣ��֪ͨcallģģ��Ҷϵ绰��״̬��λ*/
        case APP_VC_TIMER_START:
            APP_VC_StartTimeoutProc();
            return;

        case APP_VC_TIMER_STOP:
            /*�ط���ϢVC_PHY_STOP_REQ�������*/
            MMC_ComGetRatType(&ucRatType);  /*��ȡ��ǰ����ģʽ*/
            APP_VC_StartProtectTimer(APP_VC_TIMER_STOP);
            APP_VC_SendStopReq((CALL_VC_RADIO_MODE_ENUM_U8)ucRatType);
            break;

        case APP_VC_TIMER_SET_CODEC:
            break;

        case APP_VC_TIMER_SET_DEV:
            if (APP_VC_S_WAIT_AT_SET_DEV_RSLT == APP_VC_GetState())
            {
                /* ��ȡnv��Ϣ */
                APP_VC_GetClvlVolume(&stClvlVolume);

                stClvlVolume.usCurrDevMode = stClvlVolume.usPreDevMode;
                stClvlVolume.usSetVoiceFlg = VOS_FALSE;

                APP_VC_SaveClvlVolume(&stClvlVolume);


                APP_VC_ReportEvent(APP_VC_EVT_SET_VOICE_MODE, MN_ERR_UNSPECIFIED);
            }
            break;

        case APP_VC_TIMER_SET_VOLUME:
            if (APP_VC_S_WAIT_AT_SET_VOLUME_RSLT == APP_VC_GetState())
            {
                /* ��ȡNV */
                APP_VC_GetClvlVolume(&stClvlVolume);
                APP_VC_SetCurrVolume(&stClvlVolume, stClvlVolume.sPreVolume);
                stClvlVolume.usSetVoiceFlg = VOS_FALSE;

                /* ����NV */
                APP_VC_SaveClvlVolume(&stClvlVolume);

                APP_VC_ReportEvent(APP_VC_EVT_SET_VOLUME, MN_ERR_UNSPECIFIED);
            }
            else
            {
                APP_VC_UpdataCurrMuteStatus(APP_VC_GetPreMuteStatus());
                APP_VC_ReportEvent(APP_VC_EVT_SET_MUTE_STATUS, MN_ERR_UNSPECIFIED);
            }
            break;

        case APP_VC_TIMER_SET_FOREGROUND:
            APP_VC_SendSetForeGroundCnf( g_stVcStateMgmt.clientId, VCVOICE_EXECUTE_RSLT_FAIL);
            break;

        case APP_VC_TIMER_SET_BACKGROUND:
            APP_VC_SendSetBackGroundCnf( g_stVcStateMgmt.clientId, VCVOICE_EXECUTE_RSLT_FAIL);
            break;

        case APP_VC_TIMER_QRY_GROUND:
            APP_VC_SendGroundRsp( g_stVcStateMgmt.clientId, VCVOICE_GROUND_BUTT, VOS_ERR);
            break;

#if (FEATURE_ON == FEATURE_ECALL)
        case APP_VC_TIMER_SET_ECALL_CFG:
            APP_VC_ReportEvent(APP_VC_EVT_SET_ECALL_CFG, MN_ERR_UNSPECIFIED);
            break;
#endif

        default:
            VC_WARN_LOG1("APP_VC_TimeoutMsgProc: Wrong Timer Name.", (VOS_INT32)pTimerMsg->ulName);
            break;
    }

    APP_VC_UpdateState(APP_VC_S_NULL);
    /* Modified by w00316404 for OPT VC, 2015-02-07, Begin */
    APP_VC_BufferMsgProc();
    /* Modified by w00316404 for OPT VC, 2015-02-07, End */

}



VOS_VOID  APP_VC_MsgProc(MsgBlock* pMsg)
{
    switch(pMsg->ulSenderPid)
    {
        case WUEPS_PID_TAF:
            APP_VC_TafMsgProc(pMsg);
            break;

        case WUEPS_PID_AT:
            APP_VC_AtParaProc((APP_VC_REQ_MSG_STRU*)pMsg);
            break;

        case DSP_PID_VOICE:
            APP_VC_MedMsgProc(pMsg);
            break;

        case VOS_PID_TIMER:
            APP_VC_TimeoutMsgProc(pMsg);
            break;

#if (FEATURE_ON == FEATURE_IMS)
        case PS_PID_IMSA:
            APP_VC_ImsaMsgProc(pMsg);
            break;
#endif

        default:
            VC_WARN_LOG1("APP_VC_MsgProc: Timer Pid.", (VOS_INT32)pMsg->ulSenderPid);
            break;
    }
}


VOS_UINT32 WuepsVCPidInit(enum VOS_INIT_PHASE_DEFINE InitPhrase)
{
    switch( InitPhrase )
    {
        case   VOS_IP_LOAD_CONFIG:
            APP_VC_InitGlobeVariable();
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
    }

    return VOS_OK;

}


VOS_VOID NAS_VC_SndOutsideContextData()
{
    NAS_VC_SDT_MSG_ST                      *pSndMsgCB     = VOS_NULL_PTR;
    NAS_VC_OUTSIDE_RUNNING_CONTEXT_ST                 *pstOutsideCtx;

    pSndMsgCB = (NAS_VC_SDT_MSG_ST *)PS_ALLOC_MSG(WUEPS_PID_VC, sizeof(NAS_VC_SDT_MSG_ST));

    if ( VOS_NULL_PTR == pSndMsgCB )
    {
        MN_ERR_LOG("NAS_VC_SndOutsideContextData:ERROR: Alloc Memory Fail.");
        return;
    }

    pstOutsideCtx = &pSndMsgCB->stOutsideCtx;

    PS_MEM_CPY(&pstOutsideCtx->pc_g_g_stVcStateMgmt, &g_stVcStateMgmt,sizeof(APP_VC_STATE_MGMT_STRU));

    pSndMsgCB->MsgHeader.ulReceiverPid   = WUEPS_PID_VC;
    pSndMsgCB->MsgHeader.ulSenderPid     = WUEPS_PID_VC;
    pSndMsgCB->MsgHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pSndMsgCB->MsgHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;

    pSndMsgCB->MsgHeader.ulLength  = sizeof(NAS_VC_OUTSIDE_RUNNING_CONTEXT_ST) + 4;
    pSndMsgCB->MsgHeader.ulMsgName = EVT_NAS_VC_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY;

    DIAG_TraceReport(pSndMsgCB);
    PS_FREE_MSG(WUEPS_PID_VC, pSndMsgCB);

    return;
}


VOS_UINT32  APP_VC_SendVcReqToOm(VOS_UINT32 ulStatus, VOS_UINT32 ulPort)
{
    MN_APP_CS_SET_TRANS_PORT_MSG_STRU  *pstMsg =
        (MN_APP_CS_SET_TRANS_PORT_MSG_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(WUEPS_PID_VC,
                                              sizeof(MN_APP_CS_SET_TRANS_PORT_MSG_STRU));

    if (VOS_NULL_PTR == pstMsg)
    {
        MN_ERR_LOG("MN_CALL_SendAppRequest: Failed to alloc VOS message.");
        return TAF_FAILURE;
    }

    /* ��дVOS��Ϣͷ */
    pstMsg->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->ulSenderPid     = WUEPS_PID_VC;
    pstMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->ulReceiverPid   = ACPU_PID_PCVOICE;

    /* ��дԭ���ײ� */
    pstMsg->usPrimId        = TAF_OAM_SET_TRANS_PORT_REQ;
    pstMsg->ulStatus        = ulStatus;
    pstMsg->ulPort          = ulPort;

    /* ����VOS��Ϣ */
    if (VOS_OK != PS_SEND_MSG(WUEPS_PID_VC, pstMsg))
    {
        VC_ERR_LOG("MN_CALL_SendAppRequest: SEND MSG FAIL.");
        return TAF_FAILURE;
    }

    return TAF_SUCCESS;
}

#ifdef __PS_WIN32_RECUR__
VOS_UINT32 NAS_VC_RestoreContextData(struct MsgCB * pMsg)
{
    NAS_VC_SDT_MSG_ST                      *pRcvMsgCB;
    NAS_VC_OUTSIDE_RUNNING_CONTEXT_ST      *pstOutsideCtx;

    pRcvMsgCB     = (NAS_VC_SDT_MSG_ST *)pMsg;

    if (EVT_NAS_VC_OUTSIDE_RUNNING_CONTEXT_FOR_PC_REPLAY == pRcvMsgCB->MsgHeader.ulMsgName)
    {
        PS_MEM_CPY(&g_stVcStateMgmt, &pstOutsideCtx->pc_g_g_stVcStateMgmt,sizeof(APP_VC_STATE_MGMT_STRU));

        TAF_LOG(WUEPS_PID_VC, VOS_NULL, PS_LOG_LEVEL_INFO,"CALL: NAS_VC_RestoreContextData - data is restored.");
        return VOS_TRUE;
    }
    return VOS_FALSE;
}

#endif


VOS_VOID APP_VC_SaveClvlVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume
)
{
    if (NV_OK != NV_Write(en_NV_Item_Clvl_Volume,
                          pstClvlVolume,
                          sizeof(APP_VC_NV_CLVL_VOLUME_STRU)))
    {
        VC_ERR_LOG("APP_VC_SaveClvlVolume: NV Write Fail!");
    }

    return;
}


VOS_VOID APP_VC_GetClvlVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume
)
{
    if (NV_OK != NV_Read(en_NV_Item_Clvl_Volume,
                         pstClvlVolume,
                         sizeof(APP_VC_NV_CLVL_VOLUME_STRU)))
    {
        VC_ERR_LOG("APP_VC_GetClvlVolume: NV Read Fail!");
        PS_MEM_SET(pstClvlVolume, 0, sizeof(APP_VC_NV_CLVL_VOLUME_STRU));
        pstClvlVolume->sHandSetVolValue     = VC_VOLUME_DEFAULT_VALUE;
        pstClvlVolume->sHandsFreeVolValue   = VC_VOLUME_DEFAULT_VALUE;
        pstClvlVolume->sCarFreeVolValue     = VC_VOLUME_DEFAULT_VALUE;
        pstClvlVolume->sEarphoneVolValue    = VC_VOLUME_DEFAULT_VALUE;
        pstClvlVolume->sBlueToothVolValue   = VC_VOLUME_DEFAULT_VALUE;
        pstClvlVolume->sPcVoiceVolValue     = VC_VOLUME_DEFAULT_VALUE;
        pstClvlVolume->sHeadPhoneVolValue   = VC_VOLUME_DEFAULT_VALUE;
        pstClvlVolume->sSuperFreeVolValue   = 0;
        pstClvlVolume->sSmartTalkVolValue   = 0;

        pstClvlVolume->sPreVolume           = pstClvlVolume->sEarphoneVolValue;

        pstClvlVolume->usCurrDevMode        = VC_PHY_DEVICE_MODE_EARPHONE;
        pstClvlVolume->usPreDevMode         = VC_PHY_DEVICE_MODE_EARPHONE;

        pstClvlVolume->usSetVoiceFlg        = VOS_FALSE;
    }

    return;
}


VOS_INT16 APP_VC_GetCurrVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume
)
{
    VOS_INT16                           sCurrVolume;

    switch(pstClvlVolume->usCurrDevMode)
    {
        case VC_PHY_DEVICE_MODE_HANDSET:
            sCurrVolume = pstClvlVolume->sHandSetVolValue;
            break;

        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            sCurrVolume = pstClvlVolume->sHandsFreeVolValue;
            break;

        case VC_PHY_DEVICE_MODE_CAR_FREE:
            sCurrVolume = pstClvlVolume->sCarFreeVolValue;
            break;

        case VC_PHY_DEVICE_MODE_EARPHONE:
            sCurrVolume = pstClvlVolume->sEarphoneVolValue;
            break;

        case VC_PHY_DEVICE_MODE_BLUETOOTH:
            sCurrVolume = pstClvlVolume->sBlueToothVolValue;
            break;

        case VC_PHY_DEVICE_MODE_PCVOICE:
            sCurrVolume = pstClvlVolume->sPcVoiceVolValue;
            break;

        case VC_PHY_DEVICE_MODE_HEADPHONE:
            sCurrVolume = pstClvlVolume->sHeadPhoneVolValue;
            break;

        case VC_PHY_DEVICE_MODE_SUPER_HANDFREE:
            sCurrVolume = pstClvlVolume->sSuperFreeVolValue;
            break;

        case VC_PHY_DEVICE_MODE_SMART_TALK:
            sCurrVolume = pstClvlVolume->sSmartTalkVolValue;
            break;

        default:
            sCurrVolume = VC_VOLUME_DEFAULT_VALUE;
            break;
    }

    return sCurrVolume;
}


VOS_VOID APP_VC_SetCurrVolume(
    APP_VC_NV_CLVL_VOLUME_STRU         *pstClvlVolume,
    VOS_INT16                           sCurrVolume
)
{
    switch(pstClvlVolume->usCurrDevMode)
    {
        case VC_PHY_DEVICE_MODE_HANDSET:
            pstClvlVolume->sHandSetVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_HANDS_FREE:
            pstClvlVolume->sHandsFreeVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_CAR_FREE:
            pstClvlVolume->sCarFreeVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_EARPHONE:
            pstClvlVolume->sEarphoneVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_BLUETOOTH:
            pstClvlVolume->sBlueToothVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_PCVOICE:
            pstClvlVolume->sPcVoiceVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_HEADPHONE:
            pstClvlVolume->sHeadPhoneVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_SUPER_HANDFREE:
            pstClvlVolume->sSuperFreeVolValue = sCurrVolume;
            break;

        case VC_PHY_DEVICE_MODE_SMART_TALK:
            pstClvlVolume->sSmartTalkVolValue = sCurrVolume;
            break;

        default:
            break;
    }

    return;
}


VC_PHY_DEVICE_MODE_ENUM_U16 APP_VC_GetCurrDevMode(VOS_VOID)
{
    APP_VC_NV_CLVL_VOLUME_STRU          stClvlVolume;

    PS_MEM_SET(&stClvlVolume, 0x00, sizeof(stClvlVolume));

    APP_VC_GetClvlVolume(&stClvlVolume);

    return stClvlVolume.usCurrDevMode;
}


VOS_UINT32 APP_VC_GetVoiceTestFlag(VOS_UINT32 *pVoiceTestFlag)
{
    VOS_UINT32                          ulLength;
    TAF_NV_VOICE_TEST_FLAG_STRU         stVoiceTestFlag;

    ulLength    = 0;
    (VOS_VOID)VOS_MemSet(&stVoiceTestFlag, 0, sizeof(TAF_NV_VOICE_TEST_FLAG_STRU));

    (VOS_VOID)NV_GetLength(en_NV_Item_VOICE_TEST_FLAG, &ulLength);
    if (ulLength > sizeof(stVoiceTestFlag))
    {
        return VOS_ERR;
    }

    if (NV_OK != NV_Read(en_NV_Item_VOICE_TEST_FLAG,
                         &stVoiceTestFlag, ulLength))
    {
        VC_ERR_LOG("APP_VC_GetVcVoiceFlag() NV read Error!");
        return VOS_ERR;
    }

    *pVoiceTestFlag = stVoiceTestFlag.ulFlagValue;
    return VOS_OK;
}

 #if (FEATURE_ON == FEATURE_PTM)

VOS_VOID APP_VC_AppVCFailErrRecord(
    VOS_UINT16                          usName,
    VOS_UINT16                          usCause
)
{
    NAS_ERR_LOG_VC_FAILURE_EVENT_STRU                       stVcFailEvent;
    VOS_UINT32                                              ulIsLogRecord;
    VOS_UINT32                                              ulLength;
    VOS_UINT32                                              ulResult;
    VOS_UINT16                                              usLevel;

    /* ��ѯ��ӦAlarm Id�Ƿ���Ҫ��¼�쳣��Ϣ */
    usLevel       = NAS_GetErrLogAlmLevel(NAS_ERR_LOG_ALM_VC_OPT_FAIL);
    ulIsLogRecord = TAF_SDC_IsErrLogNeedRecord(usLevel);

    /* ����Ҫ��¼ʱ���������쳣��Ϣ */
    if (VOS_FALSE == ulIsLogRecord)
    {
        return;
    }

    ulLength = sizeof(NAS_ERR_LOG_VC_FAILURE_EVENT_STRU);

    /* ���VC�쳣��Ϣ */
    PS_MEM_SET(&stVcFailEvent, 0x00, ulLength);

    NAS_COMM_BULID_ERRLOG_HEADER_INFO(&stVcFailEvent.stHeader,
                                      VOS_GetModemIDFromPid(WUEPS_PID_VC),
                                      NAS_ERR_LOG_ALM_VC_OPT_FAIL,
                                      usLevel,
                                      VOS_GetSlice(),
                                      (ulLength - sizeof(OM_ERR_LOG_HEADER_STRU)));

    stVcFailEvent.ulOptState = APP_VC_GetState();
    stVcFailEvent.ulCasue    = usCause;
    stVcFailEvent.ulName     = usName;

    /*
       ���쳣��Ϣд��Buffer��
       ʵ��д����ַ�������Ҫд��Ĳ������ӡ�쳣
     */
    ulResult = TAF_SDC_PutErrLogRingBuf((VOS_CHAR *)&stVcFailEvent, ulLength);
    if (ulResult != ulLength)
    {
        NAS_ERROR_LOG(WUEPS_PID_VC, "APP_VC_AppVCFailErrRecord(): Push buffer error.");
    }

    NAS_COM_MntnPutRingbuf(NAS_ERR_LOG_ALM_VC_OPT_FAIL,
                           WUEPS_PID_VC,
                           (VOS_UINT8 *)&stVcFailEvent,
                           sizeof(stVcFailEvent));
    return;
}
#endif

#if (FEATURE_ON == FEATURE_ECALL)


VOS_VOID  APP_VC_StartSendMsdData(VOS_VOID *pMsg)
{
    VCVOICE_SET_MSD_REQ_STRU           *pstMsdReq  = VOS_NULL_PTR;
    VOS_UINT8                          *pucMsdAddr = VOS_NULL_PTR;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulLength;


    /* ��ʼ���ֲ����� */
    pucMsdAddr = APP_VC_GetEcallMsdAddr();

    /* ������Ϣ */
    ulLength    = sizeof(VCVOICE_SET_MSD_REQ_STRU) - VOS_MSG_HEAD_LENGTH;
    pstMsdReq   = (VCVOICE_SET_MSD_REQ_STRU *)PS_ALLOC_MSG(WUEPS_PID_VC, ulLength);
    if (VOS_NULL_PTR == pstMsdReq)
    {
        return;
    }

    /* ��ʼ�� */
    PS_MEM_SET((VOS_UINT8 *)pstMsdReq + VOS_MSG_HEAD_LENGTH, 0x0, ulLength);

    pstMsdReq->ulReceiverPid            = DSP_PID_VOICE;
    pstMsdReq->usMsgName                = ID_VC_VOICE_SET_MSD_REQ;
    pstMsdReq->ulMsdLen                 = APP_VC_MSD_DATA_LEN;

    /* ����MSD���� */
    PS_MEM_CPY(pstMsdReq->aucMsd, pucMsdAddr, APP_VC_MSD_DATA_LEN);

    ulRet = PS_SEND_MSG(WUEPS_PID_VC, pstMsdReq);

    if (VOS_ERR == ulRet)
    {
        VC_ERR_LOG("APP_VC_SendMsdReq:SEND MSG FIAL");

        return;
    }

}

VOS_VOID  APP_VC_SetMsdProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_MSG_SET_MSD_REQ_STRU        *pstMsd;
    VOS_UINT8                          *pucMsdAddr;

    pstMsd      = (APP_VC_MSG_SET_MSD_REQ_STRU*)pstAppMsg->aucContent;
    pucMsdAddr  = APP_VC_GetEcallMsdAddr();

    /* ����ǰ���ڴ���MSD���ݣ�����������MSD���� */
    if (VOS_FALSE == APP_VC_GetAllowSetMsdFlag())
    {
        /* �ظ�AT */
        APP_VC_SendAtSetCnf(APP_VC_MSG_SET_MSD_CNF, pstAppMsg->clientId, VCVOICE_EXECUTE_RSLT_FAIL);

        return;
    }

    /* ���֮ǰ��MSD���� */
    PS_MEM_SET(pucMsdAddr, 0x0, (sizeof(VOS_UINT8) * APP_VC_MSD_DATA_LEN));

    /* ����MSD���� */
    PS_MEM_CPY(pucMsdAddr, pstMsd, (sizeof(VOS_UINT8) * APP_VC_MSD_DATA_LEN));

    /* ��ǰ�Ѿ��·���MSD���� */
    APP_VC_SetMsdFlag(PS_TRUE);

    /* �����ݷ��͸�MED */
    APP_VC_SendMsdReq();

    /* �ظ�AT */
    APP_VC_SendAtSetCnf(APP_VC_MSG_SET_MSD_CNF, pstAppMsg->clientId, VCVOICE_EXECUTE_RSLT_SUCC);

    /* �����ǰ�л�����Ϣ����������Ϣ */
    APP_VC_BufferMsgProc();

    return;
}


VOS_VOID  APP_VC_QryMsdProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    /* �ظ�AT */
    APP_VC_SendQryMsdCnf(pstAppMsg->clientId);

    /* �����ǰ�л�����Ϣ����������Ϣ */
    APP_VC_BufferMsgProc();

    return;
}


VOS_VOID  APP_VC_SetEcallCfgProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    APP_VC_MSG_SET_ECALL_CFG_REQ_STRU  *pstCfg;

    /* ˢ�¿ͻ�����Ϣ */
    APP_VC_UpdateClientId(pstAppMsg->clientId);
    APP_VC_UpdateOpId(pstAppMsg->opId);

    pstCfg      = (APP_VC_MSG_SET_ECALL_CFG_REQ_STRU *)pstAppMsg->aucContent;

    /* ���������ݷ��͸�MED */
    if (VOS_OK != APP_VC_SendEcallCfgReq(pstCfg->enMode, pstCfg->enVocConfig))
    {
        /*�ϱ�*/
        APP_VC_ReportEvent(APP_VC_EVT_SET_ECALL_CFG, MN_ERR_UNSPECIFIED);
        return;
    }

    /* ������������ */
    APP_VC_SetNewEcallCfg(pstCfg->enMode, pstCfg->enVocConfig);
    APP_VC_UpdateState(APP_VC_S_WAIT_SET_ECALL_CFG_RSLT);
    APP_VC_StartProtectTimer(APP_VC_TIMER_SET_ECALL_CFG);

    return;
}


VOS_VOID  APP_VC_QryEcallCfgProc(
    APP_VC_REQ_MSG_STRU                *pstAppMsg
)
{
    /* �ظ�AT */
    APP_VC_SendQryEcallCfgCnf(pstAppMsg->clientId);

    /* �����ǰ�л�����Ϣ����������Ϣ */
    APP_VC_BufferMsgProc();

    return;
}


VOS_VOID APP_VC_MapAppEcallTransStatus(
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8  enVcTransStatus,
    APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8  *penAppStatus
)
{
    switch(enVcTransStatus)
    {
        case VCVOICE_ECALL_MSD_TRANSMITTING_START:
            *penAppStatus = APP_VC_ECALL_MSD_TRANSMITTING_START;
            break;
        case VCVOICE_ECALL_MSD_TRANSMITTING_SUCCESS:
            *penAppStatus = APP_VC_ECALL_MSD_TRANSMITTING_SUCCESS;
            break;
        case VCVOICE_ECALL_MSD_TRANSMITTING_FAIL:
            *penAppStatus = APP_VC_ECALL_MSD_TRANSMITTING_FAIL;
            break;
        case VCVOICE_ECALL_PSAP_MSD_REQUIRETRANSMITTING:
            *penAppStatus = APP_VC_ECALL_PSAP_MSD_REQUIRETRANSMITTING;
            break;
        default:
            *penAppStatus = APP_VC_ECALL_TRANS_STATUS_BUTT;
    }

    return;

}


VOS_VOID APP_VC_MapAppEcallTransFailCause(
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  enVcFailCause,
    APP_VC_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  *penAppFailCause
)
{
    switch(enVcFailCause)
    {
        case VCVOICE_ECALL_CAUSE_WAIT_PSAP_TIME_OUT:
            *penAppFailCause = APP_VC_ECALL_CAUSE_WAIT_PSAP_TIME_OUT;
            break;
        case VCVOICE_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT:
            *penAppFailCause = APP_VC_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT;
            break;
        case VCVOICE_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT:
            *penAppFailCause = APP_VC_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT;
            break;
        case VCVOICE_ECALL_CAUSE_UNSPECIFIC_ERROR:
            *penAppFailCause = APP_VC_ECALL_CAUSE_UNSPECIFIC_ERROR;
            break;
        default:
            *penAppFailCause = APP_VC_ECALL_CAUSE_BUTT;
            break;
    }

    return;

}



VOS_VOID APP_VC_MapCallEcallTransStatus(
    VCVOICE_ECALL_TRANS_STATUS_ENUM_UINT8   enVcTransStatus,
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8  *penCallStatus
)
{
    switch(enVcTransStatus)
    {
        case VCVOICE_ECALL_MSD_TRANSMITTING_START:
            *penCallStatus = VC_CALL_ECALL_MSD_TRANSMITTING_START;
            break;
        case VCVOICE_ECALL_MSD_TRANSMITTING_SUCCESS:
            *penCallStatus = VC_CALL_ECALL_MSD_TRANSMITTING_SUCCESS;
            break;
        case VCVOICE_ECALL_MSD_TRANSMITTING_FAIL:
            *penCallStatus = VC_CALL_ECALL_MSD_TRANSMITTING_FAIL;
            break;
        case VCVOICE_ECALL_PSAP_MSD_REQUIRETRANSMITTING:
            *penCallStatus = VC_CALL_ECALL_PSAP_MSD_REQUIRETRANSMITTING;
            break;
        default:
            *penCallStatus = VC_CALL_ECALL_TRANS_STATUS_BUTT;
            break;
    }

    return;
}


VOS_VOID APP_VC_MapCallEcallTransFailCause(
    VCVOICE_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enVcFailCause,
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8  *penCallFailCause
)
{
    switch(enVcFailCause)
    {
        case VCVOICE_ECALL_CAUSE_WAIT_PSAP_TIME_OUT:
            *penCallFailCause = VC_CALL_ECALL_CAUSE_WAIT_PSAP_TIME_OUT;
            break;
        case VCVOICE_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT:
            *penCallFailCause = VC_CALL_ECALL_CAUSE_MSD_TRANSMITTING_TIME_OUT;
            break;
        case VCVOICE_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT:
            *penCallFailCause = VC_CALL_ECALL_CAUSE_WAIT_AL_ACK_TIME_OUT;
            break;
        case VCVOICE_ECALL_CAUSE_UNSPECIFIC_ERROR:
            *penCallFailCause = VC_CALL_ECALL_CAUSE_UNSPECIFIC_ERROR;
            break;
        default:
            *penCallFailCause = VC_CALL_ECALL_CAUSE_BUTT;
            break;
    }

    return;

}



VOS_VOID  APP_VC_ReportEcallState(VOS_VOID *pMsg)
{
    VCVOICE_ECALL_TRANS_STATUS_NTF_STRU        *pstStatus;
    APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8        enAppStatus;
    APP_VC_ECALL_TRANS_STATUS_ENUM_UINT8        enAppFailCause;
    VC_CALL_ECALL_TRANS_STATUS_ENUM_UINT8       enCallStatus;
    VC_CALL_ECALL_TRANS_FAIL_CAUSE_ENUM_UINT8   enCallFailCause;

    /* ��ʼ�� */
    enAppStatus     = APP_VC_ECALL_TRANS_STATUS_BUTT;
    enAppFailCause  = APP_VC_ECALL_TRANS_STATUS_BUTT;
    enCallStatus    = VC_CALL_ECALL_TRANS_STATUS_BUTT;
    enCallFailCause = VC_CALL_ECALL_CAUSE_BUTT;

    pstStatus = (VCVOICE_ECALL_TRANS_STATUS_NTF_STRU*)pMsg;

    /* ���ڲ�Ʒ�߲�Ҫ���ϱ�STOP��������Ϊ�˺�����չ����ʱ��������ӿڣ����ڵ���STOP�Ķ����ϱ� */
    if (pstStatus->enEcallTransStatus >= VCVOICE_ECALL_MSD_TRANSMITTING_STOP)
    {
        return;
    }

    if (VCVOICE_ECALL_MSD_TRANSMITTING_START == pstStatus->enEcallTransStatus)
    {
        /* ����������MSD���� */
        APP_VC_SetAllowSetMsdFlag(PS_FALSE);
    }
    else
    {
        /* ��������MSD���� */
        APP_VC_SetAllowSetMsdFlag(PS_TRUE);
    }

    /* MSD����ʧ�� */
    if (VCVOICE_ECALL_MSD_TRANSMITTING_FAIL == pstStatus->enEcallTransStatus)
    {
        if (pstStatus->enEcallTransFailCause >= VCVOICE_ECALL_CAUSE_BUTT)
        {
            return;
        }
        /* ����ʧ�ܵ�ԭ�� */
        APP_VC_MapAppEcallTransFailCause(pstStatus->enEcallTransFailCause, &enAppFailCause);
        APP_VC_SetEcallDescription(enAppFailCause);

        APP_VC_MapCallEcallTransFailCause(pstStatus->enEcallTransFailCause, &enCallFailCause);
    }

    /* ����ʱ�䴰 */
    if (VCVOICE_ECALL_PSAP_MSD_REQUIRETRANSMITTING == pstStatus->enEcallTransStatus)
    {
        APP_VC_SetEcallDescription(pstStatus->ulTimeWindow);
    }

    /* ���¶˿���Ϣ */
    APP_VC_UpdateClientId(MN_CLIENT_ID_BROADCAST);

    /* ���浱ǰ��״̬ */
    APP_VC_MapAppEcallTransStatus(pstStatus->enEcallTransStatus, &enAppStatus);
    APP_VC_SetEcallState(enAppStatus);

    APP_VC_MapCallEcallTransStatus(pstStatus->enEcallTransStatus, &enCallStatus);

    /* �� CALLģ���ϱ�״̬��Ϣ */
    APP_VC_SendEcallTransStatusInd(enCallStatus, enCallFailCause);

    /* �ϱ���ATģ�� */
    APP_VC_ReportEvent(APP_VC_EVT_ECALL_TRANS_STATUS, MN_ERR_NO_ERROR);

    return;
}
VOS_VOID  APP_VC_CallChannelConnectProc(VOS_VOID)
{
    /* ��MED�·�MSD���� */
    APP_VC_SendMsdReq();

    return;
}
VOS_VOID APP_VC_MapMedMsdMode(
    APP_VC_ECALL_MSD_MODE_ENUM_UINT16   enAppMode,
    VCVOICE_ECALL_MSD_MODE_ENUM_UINT16 *penVoiceMode
)
{
    switch(enAppMode)
    {
        case APP_VC_ECALL_MSD_MODE_TRANSPARENT:
            *penVoiceMode = VCVOICE_ECALL_MSD_MODE_TRANSPARENT;
            break;

        default:
            *penVoiceMode = VCVOICE_ECALL_MSD_MODE_BUTT;
            break;
    }

    return;

}


VOS_VOID APP_VC_MapMedVocConfig(
    APP_VC_ECALL_VOC_CONFIG_ENUM_UINT16           enAppMode,
    VCVOICE_ECALL_MSD_VOICE_ABANDON_ENUM_UINT16  *penVoiceMode
)
{
    switch(enAppMode)
    {
        case APP_VC_ECALL_VOC_CONFIG_NOT_ABANDON:
            *penVoiceMode = VCVOICE_ECALL_MSD_VOICE_NOT_ABANDON;
            break;

        case APP_VC_ECALL_VOC_CONFIG_ABANDON:
            *penVoiceMode = VCVOICE_ECALL_MSD_VOICE_ABANDON;
            break;

        default:
            *penVoiceMode = VCVOICE_ECALL_MSD_VOICE_BUTT;
            break;
    }

    return;

}


VOS_VOID  APP_VC_SetEcallCfgCnfProc
(
    VCVOICE_EXECUTE_RSLT_ENUM_UINT16    enExeRslt
)
{
    if (VCVOICE_EXECUTE_RSLT_SUCC == enExeRslt)
    {
        APP_VC_UpdateCurrEcallCfg();
    }

    APP_VC_ReportEvent(APP_VC_EVT_SET_ECALL_CFG, enExeRslt);
    APP_VC_UpdateState(APP_VC_S_NULL);
    APP_VC_StopProtectTimer();
    APP_VC_BufferMsgProc();
}


VOS_VOID APP_VC_RecordAlAckInfo(
    VOS_UINT32                          ulTimesTamp,
    VOS_UINT8                           ucAkAckValue
)
{
    VC_AL_ACK_REPORT_INFO_STRU         *pstAlAckAddr = VOS_NULL_PTR;

    pstAlAckAddr = APP_VC_GetAlAckInfoAddr();

    pstAlAckAddr->astAlAckInfo[pstAlAckAddr->ulIndex % VC_MAX_AL_ACK_NUM].ulTimeStamp  = ulTimesTamp;
    pstAlAckAddr->astAlAckInfo[pstAlAckAddr->ulIndex % VC_MAX_AL_ACK_NUM].ucAlAckValue = ucAkAckValue;

    pstAlAckAddr->ulIndex++;

    return;
}



VOS_VOID  APP_VC_ReportAlAckProc(VOS_VOID *pMsg)
{
    VOICEVC_AL_ACK_REPORT_IND_STRU      *pstAlAckInfo = VOS_NULL_PTR;

    pstAlAckInfo    = (VOICEVC_AL_ACK_REPORT_IND_STRU *)pMsg;

    if ( 0 != (VC_AL_ACK_CLEAR_DOWN_BIT & pstAlAckInfo->ucAlAckValue) )
    {
        APP_VC_SendEndCallReq(APP_VC_OPEN_CHANNEL_CAUSE_SUCC);
    }

    /* ����Ϣ��¼��ȫ�ֱ����� */
    APP_VC_RecordAlAckInfo(pstAlAckInfo->ulTimeStamp, pstAlAckInfo->ucAlAckValue);

    return;
}


#endif

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_VOID APP_VC_CallChannelSoCtrlOrderInd(
    MsgBlock                           *pstMsg
)
{
    CALL_VC_SO_CTRL_ORDER_IND_STRU     *pstSoCtrlOrder = VOS_NULL_PTR;

    pstSoCtrlOrder  = (CALL_VC_SO_CTRL_ORDER_IND_STRU *)pstMsg;

    /* ��CODEC����ID_VC_VOICE_SO_CTRL_ORDER_IND��Ϣ */
    APP_VC_SendSoCtrlOrderInd(APP_VC_ConvertCallCodeTypeToVodecType(pstSoCtrlOrder->enCodecType),
                              pstSoCtrlOrder->ucORDQ);
    return;
}
VOS_VOID APP_VC_CallChannelSoCtrlMsgInd(
    MsgBlock                           *pstMsg
)
{
    SO_CTRL_MSG_CODEC_STRU              stCodec;
    CALL_VC_SO_CTRL_MSG_IND_STRU       *pstSoCtrlMsg = VOS_NULL_PTR;

    pstSoCtrlMsg  = (CALL_VC_SO_CTRL_MSG_IND_STRU *)pstMsg;
    PS_MEM_SET(&stCodec, 0, sizeof(SO_CTRL_MSG_CODEC_STRU));

    stCodec.ucInitCodec                 = pstSoCtrlMsg->ucInitCodec;
    stCodec.ucMobileToMobile            = pstSoCtrlMsg->ucMobileToMobile;
    stCodec.ucRateReduc                 = pstSoCtrlMsg->ucRateReduc;

    /* ��CODEC����ID_VC_VOICE_SO_CTRL_MSG_IND��Ϣ */
    APP_VC_SendSoCtrlMsgInd(APP_VC_ConvertCallCodeTypeToVodecType(pstSoCtrlMsg->enCodecType),
                            &stCodec);


    return;
}

#endif
VCVOICE_TYPE_ENUM_UINT16 APP_VC_ConvertCallCodeTypeToVodecType(
    CALL_VC_CODEC_TYPE_ENUM_U8       enCodeType
)
{
    switch(enCodeType)
    {
        case CALL_VC_CODEC_TYPE_AMR:
            return VCVOICE_TYPE_AMR;

        case CALL_VC_CODEC_TYPE_EFR:
            return VCVOICE_TYPE_EFR;

        case CALL_VC_CODEC_TYPE_FR:
            return VCVOICE_TYPE_FR;

        case CALL_VC_CODEC_TYPE_HR:
            return VCVOICE_TYPE_HR;

        case CALL_VC_CODEC_TYPE_AMR2:
            return VCVOICE_TYPE_AMR2;

        case CALL_VC_CODEC_TYPE_AMRWB:
            return VCVOICE_TYPE_AMRWB;

        case CALL_VC_CODEC_TYPE_G711:
            return VCVOICE_TYPE_G711;

        case CALL_VC_CODEC_TYPE_EVRC:
            return VCVOICE_TYPE_EVRC;

        case CALL_VC_CODEC_TYPE_EVRCB:
            return VCVOICE_TYPE_EVRCB;

        default:
            VC_ERR_LOG("APP_VC_ConvertCallCodeTypeToVodecType: wrong enCodeType");
            return VCVOICE_TYPE_BUTT;
    }

}



/*lint +e958*/

#ifdef  __cplusplus
  #if  __cplusplus
  }
  #endif
#endif


