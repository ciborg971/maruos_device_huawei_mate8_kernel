

#include "vos.h"
#include "hpacomm.h"
#include "sleepflow.h"
#include "hpaoperatertt.h"
#include "bbp_wcdma_on_interface.h"
#include "bbp_wcdma_interface.h"
#include "bbp_gsm_on_interface.h"
#include "apminterface.h"
#include "OmApi.h"
#include "PamOamSpecTaskDef.h"
#include "TtfOamInterface.h"
#include "NVIM_Interface.h"
#include "DrvNvInterface.h"
#include "v_private.h"
#include "omprivate.h"
#include "PhyNvDefine.h"
#include "apmprocess.h"

#if (RAT_MODE != RAT_GU)
#include "product_config.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SLEEP_FLOW_C

extern VOS_UINT32 PsRegGetDmaCaptureStatus(MODEM_ID_ENUM_UINT16 enModemId);

SLEEP_INFO_STATE_STRU*                  g_pstSleepInfoSlice;

/* ���GUģ��ǰϵͳ״̬ */
SLEEP_MODE_INFO_STRU                    g_astSleepModeInfo[SLEEP_GU_MODE_TYPE_BUTT];

T_MODEM_SR_STAMP_STRU                  *g_pstSleepWakeSliceAddr = VOS_NULL_PTR;

VOS_VOID SHPA_ActivateHw(VOS_VOID)
{
    return;
}

VOS_VOID SHPA_DeactivateHw(VOS_VOID)
{
    return;
}

VOS_VOID SLEEP_EnterLowPower(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : SLEEP_EnableDspPll
 ��������  : ʹ��DSP PLL
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

*****************************************************************************/
VOS_VOID SLEEP_EnableDspPll(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : SLEEP_ExitLowPower
 ��������  : �˳������͹���
 �������  : void
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID SLEEP_ExitLowPower(SLEEP_MODE_ENUM_UINT32 enMode)
{
    return;
}



VOS_BOOL SLEEP_IsSleep(VOS_VOID)
{
    return VOS_FALSE;
}

/*****************************************************************************
 �� �� ��  : Sleep_ActiveDspPll
 ��������  : ʹ��DSP PLL,��HPA����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
 ���ú���  :
 ��������  :

*****************************************************************************/
VOS_VOID Sleep_ActiveDspPll(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : SLEEP_NotifySndMsg
 ��������  : ֪ͨSLEEPģ������Ϣ���͵�DSP
 �������  : pMsgBlock
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID SLEEP_NotifySndMsg(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : GUSLEEP_MasterAwakeSlave
 ��������  : ��ģ����GU��ģ�ӿ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID GUSLEEP_MasterAwakeSlave(VOS_VOID)
{
    return;
}

/*****************************************************************************
 �� �� ��  : SLEEP_32KIsr
 ��������  : ���� 32K ʱ���ж�
 �������  : void
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID SLEEP_32KIsr(SLEEP_MODE_ENUM_UINT32 enMode)
{
    if ((SLEEP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
        || (SLEEP_MASTER_TEMP_LP_STATE == g_astSleepModeInfo[enMode].enSystemState))
    {
        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_BBP_32K);

        SLEEP_WAKE_SLICE_RECORD(0);

        SLEEP_SleepIsrProc(BBP_SLEEP_32K_CLOCK_SWITCH_IND, enMode);
    }
}

/*****************************************************************************
 �� �� ��  : SLEEP_NormalClockIsr
 ��������  : ���� DRX���Ѻ�ʱ���л���61.44M�ж�
 �������  : void
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID SLEEP_NormalClockIsr(SLEEP_MODE_ENUM_UINT32 enMode)
{
    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_BBP_NORMAL);

    if ((SLEEP_TEMP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
        || (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState))
    {
        SLEEP_AwakeIsrProc(BBP_SLEEP_NORMAL_CLOCK_SWITCH_IND, enMode);
    }
}

/*****************************************************************************
 �� �� ��  : SLEEP_AwakeIsr
 ��������  : �������ж�
 �������  : void
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID SLEEP_AwakeIsr(SLEEP_MODE_ENUM_UINT32 enMode)
{
    if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_BBP_WAKE);

        SLEEP_WAKE_SLICE_RECORD(4);

        SLEEP_AwakeIsrProc(BBP_SLEEP_WAKE_IND, enMode);
    }
}

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* PHY������Ϣ����� */
SLEEP_MSG_FUN_STRU g_astSleepPhyMsgFunTbl[] =
{
    {ID_UPHY_OAM_MASTER_SLEEP_IND,      SLEEP_MasterSleepMsgProc},
    {ID_UPHY_OAM_SLAVE_SLEEP_IND,       SLEEP_SlaveSleepMsgProc},
};

/* �ж���Ϣ����� */
SLEEP_MSG_FUN_STRU g_astSleepIsrMsgFunTbl[] =
{
    {BBP_SLEEP_32K_CLOCK_SWITCH_IND,    SLEEP_32KClkMsgProc},
};

/* AWAKE�ж���Ϣ����� */
SLEEP_MSG_FUN_STRU g_astAwakeIsrMsgFunTbl[] =
{
    {BBP_SLEEP_WAKE_IND,                SLEEP_WakeMasterMsgProc},
    {BBP_SLEEP_NORMAL_CLOCK_SWITCH_IND, SLEEP_NormalClkMsgProc},
    {SLEEP_WAKE_MASTER_GU_IND,          SLEEP_WakeMasterGUProc},
    {SLEEP_WAKE_SLAVE_GU_IND,           SLEEP_WakeSlaveGUProc},
};

/* SLEEP���̼�¼ */
SLEEP_TRACK_RECORD_STRU                *g_pstSleepTrackRecord   = VOS_NULL_PTR;
SLEEP_NORMAL_STATE_RECORD_STRU         *g_pstSleepNormalState   = VOS_NULL_PTR;

HIFI_STATE_STRU                        *g_pstHifiStateSlice     = VOS_NULL_PTR;
HPA_LOAD_PHY_STATE_STRU                *g_pstLoadPhyState       = VOS_NULL_PTR;

SLEEP_DEVICE_STATE_STRU                *g_pstSleepDeviceState   = VOS_NULL_PTR;

/* �����ź��� */
VOS_SEM                                 g_ulSleepSem;

/* TCXO�ȶ��ź��� */
VOS_SEM                                 g_ulSleepTcxoSem;

/* DMA�Ĵ��������ź��� */
VOS_SEM                                 g_ulSleepDMACapSem;

/* BBP�Ĵ������ݻָ����� */
VOS_UINT32                              g_ulSleepBBPPosValue    = 0;

VOS_UINT32                              g_ulSleepRusumeTime     = 0;

/* �����ָ�ʱ�� */
WG_DRX_RESUME_TIME_STRU                 g_stSleepDrxResumeTime;

VOS_BOOL                                g_bDrxResetFlag = VOS_FALSE;

/* ע���PID���ڵ͹���״̬����֪ͨ��ע��PID */
SLEEP_NOTIFY_STATE_REG_PID_STRU         g_stSleepNotifyStateRegPidTbl;

VOS_UINT32                              g_ulIsWaitingDMACap = VOS_FALSE;

/* ��������������sleep���ٽ���Դ���� */
VOS_SPINLOCK                            g_stSleepSpinLock;

/* CDMAģʽ������Ϣ */
SLEEP_CDMA_STATE_STRU                   g_stSleepCDMAControl;

UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU    g_stChannelModeProfileId;

#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
UCOM_NV_FEM_CHAN_PROFILE_STRU           g_stChannelModeProfile;
#else
UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU  g_stChannelModeProfile;
#endif

#ifndef SLEEP_BIT_N
#define SLEEP_BIT_N(num)                      (0x01 << (num))
#endif

VOS_UINT32                              g_ulSleepSlaveMsgTrackId = 0;

SLEEP_SLAVE_MSG_TRACK_STRU              g_astSleepSlaveMsgTrack[SLEEP_SLAVE_MSG_TRACK_NUM];

VOS_UINT32                              g_ulSleepNotifyMsgTrackId = 0;

SLEEP_NOTIFY_MSG_TRACK_STRU             g_astSleepNotifyMsgTrack[SLEEP_NOTIFY_MSG_TRACK_NUM];

/* modem0��modem2���Ᵽ���ź��� */
#if defined (INSTANCE_1) || defined (INSTANCE_2)
extern VOS_SEM                          g_ulSleepSlaveSem;
#else
VOS_SEM                                 g_ulSleepSlaveSem;
#endif

VOS_UINT32                              g_ulSleepSlaveSemFlag = VOS_FALSE;


/*****************************************************************************
  3 ��������
*****************************************************************************/


VOS_VOID SLEEP_NotifyStateRegPidTblInit( VOS_VOID )
{
    VOS_UINT32      ulLoop;

    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop] = SLEEP_INVALID_PID;
    }

    return;
}


VOS_UINT32 SLEEP_NotifyStateReg(VOS_UINT32 ulRcvPid, VOS_RATMODE_ENUM_UINT32 enRatMode)
{
    VOS_UINT32                          ulLoop;
    VOS_INT32                           lLockKey;
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState;

    /* ע��PID�Ϸ��� */
    if ((ulRcvPid < VOS_PID_DOPRAEND) || (ulRcvPid >= VOS_PID_BUTT))
    {
        /* �쳣��ά�ɲ��ӡ */
        PS_LOG(WUEPS_PID_SLEEP, 0, PS_PRINT_WARNING, "SLEEP_NotifyStateReg: register invalid PID.");

        return VOS_ERR;
    }

    /* ���ж� */
    lLockKey = VOS_SplIMP();

    /* ��PID�ŵ�ע����� */
    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        if (ulRcvPid == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop])
        {
            enState = g_astSleepModeInfo[enRatMode].enSystemState;

            /* ���ж� */
            VOS_Splx(lLockKey);

            SLEEP_NotifyStateToRegPid(enRatMode, enState);

            return VOS_OK;
        }
    }

    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        /* �ҵ��յ�PID���λ�� */
        if (SLEEP_INVALID_PID == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop])
        {
            /* �洢ע���PID */
            g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop] = ulRcvPid;

            enState = g_astSleepModeInfo[enRatMode].enSystemState;

            /* ���ж� */
            VOS_Splx(lLockKey);

            SLEEP_NotifyStateToRegPid(enRatMode, enState);

            return VOS_OK;
        }
    }

    /* ���ж� */
    VOS_Splx(lLockKey);

    /* �Ҳ����յĴ��λ�ã���ӡ��ά�ɲ���Ϣ */
    PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_WARNING, "SLEEP_NotifyStateReg: No empty entry.", (VOS_INT32)ulRcvPid);

    return VOS_ERR;
}


VOS_UINT32 SLEEP_NotifyStateUnreg(VOS_UINT32 ulRcvPid)
{
    VOS_UINT32      ulLoop;
    VOS_INT32       lLockKey;

    /* ���ж� */
    lLockKey = VOS_SplIMP();

    /* �ж��Ƿ��Ѿ�ע�����PID */
    for (ulLoop = 0; ulLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ulLoop++)
    {
        if (ulRcvPid == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop])
        {
            /* ����PID�ӱ���ȥ�� */
            g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ulLoop] = SLEEP_INVALID_PID;

            /* ���ж� */
            VOS_Splx(lLockKey);

            return VOS_OK;
        }
    }

    /* ���ж� */
    VOS_Splx(lLockKey);

    /* δ�ҵ�ƥ��PID���쳣��ӡ�ͼ�¼ */
    PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_WARNING, "SLEEP_NotifyStateUnreg: PID hasn't been found.", (VOS_INT32)ulRcvPid);

    return VOS_ERR;
}


VOS_VOID SLEEP_NotifyStateToRegPid(
    VOS_RATMODE_ENUM_UINT32             enRatMode,
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enState)
{
    SLEEP_NOTIFY_STATUS_MSG_STRU       *pstMsg;
    VOS_UINT32                          ucLoop;
    VOS_UINT32                          ulMsgLen;

    for (ucLoop = 0; ucLoop < SLEEP_NOTIFY_STATE_REG_PID_MAX; ucLoop++)
    {
        if (SLEEP_INVALID_PID == g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ucLoop])
        {
            continue;
        }

        ulMsgLen = sizeof(SLEEP_NOTIFY_STATUS_MSG_STRU) - VOS_MSG_HEAD_LENGTH;

        pstMsg = (SLEEP_NOTIFY_STATUS_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_SLEEP, ulMsgLen);
        if (VOS_NULL_PTR == pstMsg)
        {
            PS_LOG(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_NotifyStateToRegPid: Alloc msg fail.");
            return;
        }

        /* �����Ϣ���� */
        pstMsg->ulReceiverPid      = g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ucLoop];
        pstMsg->enMsgId            = ID_SLEEP_NOTIFY_STATUS_IND;
        pstMsg->enRatMode          = enRatMode;
        pstMsg->enState            = enState;
        if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
        {
            pstMsg->enLPState       = SLEEP_LOWPOWER_STATE_ON;
        }
        else
        {
            pstMsg->enLPState       = SLEEP_LOWPOWER_STATE_OFF;
        }

        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].ulRegPid    = g_stSleepNotifyStateRegPidTbl.aulRegPidTbl[ucLoop];
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].enRatMode   = enRatMode;
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].enState     = enState;
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].enLPState   = UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId());
        g_astSleepNotifyMsgTrack[g_ulSleepNotifyMsgTrackId].ulSlice     = OM_GetSlice();

        g_ulSleepNotifyMsgTrackId++;

        if (SLEEP_NOTIFY_MSG_TRACK_NUM == g_ulSleepNotifyMsgTrackId)
        {
            g_ulSleepNotifyMsgTrackId   = 0;
        }

        if (VOS_OK != VOS_SendMsg(WUEPS_PID_SLEEP, pstMsg))
        {
            PS_LOG(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_NotifyStateToRegPid: send msg fail.");
        }
    }

    return;
}
MODEM_ID_ENUM_UINT16 SLEEP_GetModemId(VOS_VOID)
{
#if defined (INSTANCE_2)
    return MODEM_ID_2;
#elif defined (INSTANCE_1)
    return MODEM_ID_1;
#else
    return MODEM_ID_0;
#endif
}


VOS_BOOL SLEEP_IsAwakeProc( SLEEP_MODE_ENUM_UINT32 enMode )
{
    if (SLEEP_TEMP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        return VOS_TRUE;
    }

    return VOS_FALSE;
}


VOS_UINT32 SLEEP_AwakeInfoGet( SLEEP_MODE_ENUM_UINT32 enMode, VOS_UINT32 *pstAwakeHWInfo, VOS_UINT32 uLen )
{
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ( (VOS_NULL_PTR == pstAwakeHWInfo)
        || (enMode > VOS_RATMODE_WCDMA)
        || (uLen < UPHY_OAM_SLEEP_INFO_NUM) )
    {
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemSet(pstAwakeHWInfo, 0x0, sizeof(VOS_UINT32)*uLen);
    /*lint +e534*/

    pstAwakeHWInfo[0]
        = 0x887755AA;
    pstAwakeHWInfo[1]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_WAKE].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_WAKE].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[2]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_START].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_START].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[3]
        = g_pstSleepDeviceState->aulDeviceUpSlice[enModem][enMode][PWC_COMM_MODULE_ABB][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[4]
        = g_pstSleepDeviceState->aulDeviceUpSlice[enModem][enMode][PWC_COMM_MODULE_BBP_DRX][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[5]
        = g_pstSleepDeviceState->aulPLLUpSlice[enModem][enMode][PWC_COMM_MODULE_BBP_DRX][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[6]
        = g_pstSleepDeviceState->aulPLLUpSlice[enModem][enMode][PWC_COMM_MODULE_ABB][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[7]
        = g_pstSleepDeviceState->aulDeviceUpSlice[enModem][enMode][PWC_COMM_MODULE_RF][PWC_COMM_CHANNEL_0];
    pstAwakeHWInfo[8]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_END].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_ACTIVATE_END].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[9]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_NORMAL].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_BBP_NORMAL].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[10]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY_PRE].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY_PRE].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[11]
        = g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY].aulSlice[g_pstSleepNormalState->astRecordItem[enMode][SLEEP_MASTER_WAKE_PHY].ulCount%SLEEP_RECORD_TRACK_NUM];
    pstAwakeHWInfo[12]
        = 0xAA557788;

    if ( SLEEP_INFO_RESET_ENABLE == g_bDrxResetFlag )
    {
        VOS_ProtectionReboot(DRX_ACTIVATEHW_ERROR, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);
    }

    return VOS_OK;
}



VOS_VOID SLEEP_VoteLock(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if defined (INSTANCE_2)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_G2);
        /*lint +e534*/
    }
#elif defined (INSTANCE_1)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_G1);
        /*lint +e534*/
    }
#else
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_G0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_WCDMA == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_SLEEP_PS_W0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_1X == enMode)
    {
        /*ΪAustin xģ���Դ�׮������modem����͹��� */
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_TEST_DEEPSLEEP);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
        /*ΪAustin xģ���Դ�׮������modem����͹��� */
        /*lint -e534*/
        mdrv_pm_wake_lock(PWRCTRL_TEST_DEEPSLEEP);
        /*lint +e534*/
    }
    else
    {
        /* for pclint */
    }
#endif

    return;
}
VOS_VOID SLEEP_VoteUnlock(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if defined (INSTANCE_2)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_G2);
        /*lint +e534*/
    }
#elif defined (INSTANCE_1)
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_G1);
        /*lint +e534*/
    }
#else
    if (VOS_RATMODE_GSM == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_G0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_WCDMA == enMode)
    {
        /*lint -e534*/
        mdrv_pm_wake_unlock(PWRCTRL_SLEEP_PS_W0);
        /*lint +e534*/
    }
    else if (VOS_RATMODE_1X == enMode)
    {
    }
    else if (VOS_RATMODE_HRPD == enMode)
    {
    }
    else
    {
        /* for pclint */
    }
#endif

    return;
}
VOS_VOID SLEEP_TimeCal( VOS_VOID )
{
    g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulAbbPwrRsmTime;

    /* ��ȡ���ʱ�� */
    if (g_ulSleepRusumeTime < g_stSleepDrxResumeTime.ulBbpPllRsmTime)
    {
        g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulBbpPllRsmTime;
    }

    if (g_ulSleepRusumeTime < g_stSleepDrxResumeTime.ulRfPwrRsmTime)
    {
        g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulRfPwrRsmTime;
    }

    if (g_ulSleepRusumeTime < g_stSleepDrxResumeTime.ulPaPwrRsmTime)
    {
        g_ulSleepRusumeTime = g_stSleepDrxResumeTime.ulPaPwrRsmTime;
    }

    /* �����Slice��λ */
    g_ulSleepRusumeTime = g_ulSleepRusumeTime/32;

    return;
}


VOS_VOID SLEEP_TCXOIsrProc( VOS_VOID )
{
    /*lint -e534*/
    VOS_SmV(g_ulSleepTcxoSem);
    /*lint +e534*/
}


VOS_VOID SLEEP_TCXOEnable(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_UINT32                          ulTcxoResult;
    VOS_UINT32                          ulTcxoTime;
    VOS_UINT32                          ulTcxoSemTime;

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH <= SLEEP_TCXO_CHAN(enMode)))
    {
        return;
    }

    /*lint -e534*/
    mdrv_pm_enable_tcxo((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode), (PWC_COMM_MODE_E)enMode);
    /*lint +e534*/

    if (PWRCTRL_COMM_OFF == mdrv_pm_get_tcxo_status((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode)))
    {
        ulTcxoTime  = g_stSleepDrxResumeTime.ulTcxoRsmTime/1000;

        /* ����TCXO�ȶ��ȴ���ʱ�� */
        /*lint -e534*/
        mdrv_pm_start_tcxo_timer((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode), (PWC_COMM_MODE_E)enMode,
                                 (PWC_TCXO_FUNCPTR)SLEEP_TCXOIsrProc, VOS_NULL, ulTcxoTime);
        /*lint +e534*/

        /* �ȴ�TCXO�ȶ�,Take�ź�����Сʱ�䳤�ȱ���Ϊ1 tick */
        ulTcxoSemTime = (20 < ulTcxoTime) ?
            ulTcxoTime : 20;

        ulTcxoResult    = VOS_SmP(g_ulSleepTcxoSem, ulTcxoSemTime);

        if (VOS_OK != ulTcxoResult)
        {
            /* �쳣�������� */
            g_pstSleepDeviceState->stDeviceTcxoError.ulCount++;
            g_pstSleepDeviceState->stDeviceTcxoError.ulSlice    = OM_GetSlice();
        }
    }

    /*lint -e534*/
    mdrv_pm_enable_tcxo_rfclk((PWC_COMM_MODEM_E)SLEEP_GetModemId(), (PWC_COMM_MODE_E)enMode, (PWC_COMM_CHANNEL_E)SLEEP_TCXO_CHAN(enMode));
    /*lint +e534*/
    return;
}
VOS_VOID SLEEP_TCXODisable(SLEEP_MODE_ENUM_UINT32 enMode)
{
    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH <= SLEEP_TCXO_CHAN(enMode)))
    {
        return;
    }

    /*lint -e534*/
    mdrv_pm_disable_tcxo_rfclk((PWC_COMM_MODEM_E)SLEEP_GetModemId(), (PWC_COMM_MODE_E)enMode, (PWC_COMM_CHANNEL_E)SLEEP_TCXO_CHAN(enMode));

    /* �ر�TCXO */
    mdrv_pm_disable_tcxo((PWC_COMM_MODEM_E)SLEEP_TCXO_CHAN(enMode), (PWC_COMM_MODE_E)enMode);
    /*lint +e534*/

    return;
}

/*lint -e662 -e661*/


VOS_VOID SLEEP_ABBPowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}


VOS_VOID SLEEP_ABBPowerDown(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}


VOS_VOID SLEEP_RFPowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_FEM, i);
            SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_RF_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_RF_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_RF, SLEEP_RF_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}


VOS_VOID SLEEP_RFPowerDown(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RFCLK_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWDOWN((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_RF, i);
            /*lint +e534*/
        }

        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, i);
            SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_FEM, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_RF_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_RF_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_RF, (PWC_COMM_CHANNEL_E)SLEEP_RF_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}


VOS_VOID SLEEP_RFFECfgPowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RFCLK_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWUP((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_RF, i);
            /*lint +e534*/
        }

        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            mdrv_rffe_cfg_on_power_up((PWC_COMM_MODE_E)enMode, (PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else

#endif

    return;
}


VOS_VOID SLEEP_RFFECfgPowerDown(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_RF_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            mdrv_rffe_cfg_on_power_down((PWC_COMM_MODE_E)enMode, (PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else

#endif

    return;
}


VOS_VOID SLEEP_ABBPllEnable(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWUP(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWUP(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICEPLL_POWUP(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWUP(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}


VOS_VOID SLEEP_ABBPllDisable(SLEEP_MODE_ENUM_UINT32 enMode)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          i;

    enModem = SLEEP_GetModemId();

    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        return;
    }

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(enMode)) != VOS_NULL)
        {
            /*lint -e534*/
            SLEEP_DEVICEPLL_POWDOWN(enModem, enMode, PWC_COMM_MODULE_ABB, i);
            /*lint +e534*/
        }
        /*lint +e701*/
    }
#else
    MODEM_ID_ENUM_UINT16                enModem;

    enModem = SLEEP_GetModemId();

    if ((SLEEP_GU_MODE_TYPE_BUTT <= enMode) || (SLEEP_CHANNEL_BOTH < SLEEP_ABB_CHAN(enMode)))
    {
        return;
    }

    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(enMode))
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWDOWN(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_0);
        SLEEP_DEVICEPLL_POWDOWN(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, PWC_COMM_CHANNEL_1);
        /*lint +e534*/
    }
    else
    {
        /*lint -e534*/
        SLEEP_DEVICEPLL_POWDOWN(enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_ABB, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(enMode));
        /*lint +e534*/
    }
#endif

    return;
}


VOS_UINT32 SLEEP_GBBPClkSrcSelect(VOS_VOID)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          ulRet = 0;
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    VOS_UINT32                          i;
#endif

    enModem = SLEEP_GetModemId();

#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)

    for (i = 0; i < PWC_COMM_CHANNEL_BUTT; i++)
    {
        /*lint -e701*/
        if ((SLEEP_BIT_N(i) & SLEEP_ABB_CHAN(PWC_COMM_MODE_GSM)) != VOS_NULL)
        {
            ulRet |= mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)i);
        }
        /*lint +e701*/
    }
#else
    if (SLEEP_CHANNEL_BOTH == SLEEP_ABB_CHAN(PWC_COMM_MODE_GSM))
    {
        ulRet = mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)SLEEP_CHANNEL_ZERO);
        ulRet |= mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)SLEEP_CHANNEL_ONE);
    }
    else
    {
        ulRet = mdrv_pm_gbbp_select_clksrc((PWC_COMM_MODEM_E)enModem, (PWC_COMM_CHANNEL_E)SLEEP_ABB_CHAN(PWC_COMM_MODE_GSM));
    }
#endif

    return ulRet;
}

/*lint +e662 +e661*/

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
VOS_UINT32 SLEEP_BBE16GetPowerStatus( VOS_VOID )
{
    return g_stSleepCDMAControl.ulBBE16PowerState;
}


VOS_VOID SLEEP_BBE16PowerUp( SLEEP_MODE_ENUM_UINT32 enMode )
{
    if ((VOS_RATMODE_1X == enMode) || (VOS_RATMODE_HRPD == enMode))
    {
        /* ����BBE16����,��ǰ�͹��Ľӿ�δ���忪������ʹ�õ��Խӿڣ��������͹���
           ����ʱ���޸�BBE16���ϵ����� */
        if (VOS_FALSE == SLEEP_BBE16GetPowerStatus())
        {
            (VOS_VOID)mdrv_pm_enable_pllclk(PWC_COMM_MODE_CDMA_1X, PWC_COMM_MODULE_CBBE16, (PWC_COMM_MODEM_E)SLEEP_GetModemId(), PWC_COMM_CHANNEL_0);
            /*lint -e534 -e746*/
            (VOS_VOID)mdrv_dsp_load(BSP_DSP_CBBE);
            (VOS_VOID)mdrv_dsp_stop(BSP_DSP_CBBE);
            (VOS_VOID)mdrv_dsp_run(BSP_DSP_CBBE);
            /*lint +e534 +e746*/

            g_stSleepCDMAControl.ulBBE16PowerState  = VOS_TRUE;
        }
    }

    return;
}
#endif


VOS_VOID SLEEP_PowerUp(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          ulSlice;

    enModem = SLEEP_GetModemId();

    /* ��TXCO */
    SLEEP_TCXOEnable(enMode);

#if (FEATURE_ON == FEATURE_UE_MODE_CDMA)
    /* ����BBE16 */
    SLEEP_BBE16PowerUp(enMode);
#endif

    /* �ϵ�RF */
    SLEEP_RFPowerUp(enMode);

    /* �ϵ�ABB */
    SLEEP_ABBPowerUp(enMode);

    /* ��ABB PLL */
    SLEEP_ABBPllEnable(enMode);

    /* V8R1��BBP CS������Դ�����迪�أ������ڽ⸴λBBP CS����ǰ����Ҫ�ȴ��ſغ�ʱ��*/
    /* ��BBP PLL */

    /*lint -e534*/
    SLEEP_DEVICEPLL_POWUP((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* ��BBP����ʱ�� */
    mdrv_pm_enable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* �ϵ�BBP */
    SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    ulSlice = OM_GetSlice();

    /* �����Slice�ȴ������ȶ� */
    while((g_ulSleepRusumeTime) > (OM_GetSlice() - ulSlice))
    {
        ;
    }

    SLEEP_RFFECfgPowerUp(enMode);

    if (VOS_RATMODE_WCDMA == enMode)
    {
        HPA_Conncet3GISR();

#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
        /* д����������ӳٵȴ�ʱ�� */
        HPA_Write32Reg(WBBP_SWITCH_DELAY_MAX_1CARD_ADDR, SLEEP_BBP_HANDSHAKE_MAX_DELAY);
#endif
    }
    else if (VOS_RATMODE_GSM == enMode)
    {
#if defined (INSTANCE_2)
        HPA_Conncet2GISR2();
#elif defined (INSTANCE_1)
        HPA_Conncet2GISR1();
#else
        HPA_Conncet2GISR0();
#endif
    }
    else if ((VOS_RATMODE_1X == enMode)||(VOS_RATMODE_HRPD == enMode))
    {
        /* CDMAģʽʹ�� */
    }
    else
    {
        /* for pclint */
    }

    return;
}
VOS_UINT32 SLEEP_ReadBaseCntChip( VOS_VOID )
{
    VOS_UINT32                          ulBaseSlot;
    VOS_UINT32                          ulBaseChip;

    /* ��ȡBBP����ʱ�̼���������һ�ζ�������ȡָ��ڶ��ζ�Ϊ��ʱ�������λ�ȡ���ս�� */
    ulBaseSlot  = HPA_Read32Reg(WBBP_SYS_BASE_CNT_ADDR);
    ulBaseSlot  = HPA_Read32Reg(WBBP_SYS_BASE_CNT_ADDR);
    ulBaseSlot  = HPA_Read32Reg(WBBP_SYS_BASE_CNT_ADDR);

    /* ������ʱ�̻����CHIP��λ */
    ulBaseChip  = (ulBaseSlot>>16)&0xFFF;
    ulBaseSlot  = (ulBaseSlot>>28)&0xF;
    ulBaseChip  += ulBaseSlot*2560;

    return ulBaseChip;
}


VOS_VOID SLEEP_ResumeReg( VOS_VOID )
{
#if (VOS_OS_VER != VOS_WIN32)
    SLEEP_NOR_STATE_TRACK(VOS_RATMODE_WCDMA, SLEEP_MASTER_BBP_RESUME_START);

    /*��WBBP�ڲ���ģ���ʱ�Ӻͽ⸴λ*/
    HPA_Write32Reg(WBBP_SYS_RST_CON_W1_ADDR, 0xffff0000);

    /*��WBBP��ʱ�л���CPICH̬*/
    HPA_Write32RegMask(WBBP_TIMING_MODE_ADDR, 0x01);
    HPA_Write32RegMask(WBBP_TIMING_CFG_READY_ADDR, 0x01);

    /*�ָ���ʱģ��ķ���С��CPICH���羶��Ϣ*/
    HPA_Write32Reg(WBBP_TRACE_CPI_FRM_POS_ADDR, g_ulSleepBBPPosValue);
    HPA_Write32Reg(WBBP_PATH_CFG_READY_ADDR, 1);

    SLEEP_NOR_STATE_TRACK(VOS_RATMODE_WCDMA, SLEEP_MASTER_BBP_RESUME_END);
#endif
}

/*****************************************************************************
 �� �� ��  : SLEEP_ForceWakeProtected
 ��������  : �ж�������������Ƿ���
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID SLEEP_DMACapRelease( VOS_VOID )
{
    if (VOS_TRUE == g_ulIsWaitingDMACap)
    {
        /*lint -e534*/
        VOS_SmV(g_ulSleepDMACapSem);
        /*lint +e534*/
    }
}

/*****************************************************************************
 �� �� ��  : SLEEP_ForceWakeProtected
 ��������  : �ж�������������Ƿ���
 �������  : void
 �������  : ��
 �� �� ֵ  : VOS_OK  - ���ᵽ����������������BPP
             VOS_ERR - �����������û���BPP
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 SLEEP_ForceWakeProtected(VOS_VOID)
{
    VOS_UINT32  ulWakeSfn;
    VOS_UINT32  ulWakeSlot;
    VOS_UINT32  ulSysSfn;
    VOS_UINT32  ulSysSlot;

    /*��ǰʱ��֡��[11:0]��ƫ��ʱ϶[31:28]*/
    ulSysSfn  = HPA_Read32Reg(WBBP_SYS_CNT_SLEEP_1CARD_ADDR);
    ulSysSlot  = ulSysSfn>>28;
    ulSysSfn  &= 0xfff;
    ulSysSlot  = (ulSysSfn*SLEEP_SLOT_LEN) + ulSysSlot;

    /*��������ʱ��֡��[11:0]*/
    ulWakeSfn = HPA_Read32Reg(WBBP_CK_WAKE_SFN_1CARD_ADDR)&0xfff;
    /*��������ʱ�̵�ƫ��ʱ϶[19:16]*/
    ulWakeSlot = HPA_Read32Reg(WBBP_CK_WAKE_CNT_1CARD_ADDR);
    ulWakeSlot = (ulWakeSlot>>16)&0xf;
    /*��ֹ��ִ�иú����ڼ䣬�����ж��Ѿ����ˣ��ʽ���������ʱ���Ӻ�2��ʱ϶*/
    ulWakeSlot = ((ulWakeSfn*SLEEP_SLOT_LEN) + ulWakeSlot) + SLEEP_WAKE_DELAY;

    /*����ulWakeCnt��ת�����*/
    if (ulWakeSlot < ulSysSlot)
    {
        ulWakeSlot += SLEEP_SFN_CYCLE_LEN;
    }

    /*�ж���4��ʱ϶���Ƿ�������WAKE�ж��ϱ�*/
    if ((ulSysSlot + (SLEEP_WAKE_DELAY + SLEEP_WAKE_INTERVAL))
        < ulWakeSlot)
    {
        return VOS_OK;
    }

    return VOS_ERR;
}


VOS_VOID SLEEP_DeactivateHw(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_INT                             lIntLevel;

    enModem = SLEEP_GetModemId();

    if (VOS_RATMODE_WCDMA == enMode)
    {
        HPA_3GIsrDisable(enModem);
    }
    else
    {
        HPA_2GIsrDisable(enModem);
    }

    lIntLevel   = VOS_SplIMP();

    if (VOS_TRUE == PsRegGetDmaCaptureStatus(enModem))
    {
        g_ulIsWaitingDMACap = VOS_TRUE;
    }

    VOS_Splx(lIntLevel);

    if (VOS_TRUE == g_ulIsWaitingDMACap)
    {
        if(VOS_OK != VOS_SmP(g_ulSleepDMACapSem, 20))
        {
            g_pstSleepDeviceState->stDMACapError.ulCount++;
            g_pstSleepDeviceState->stDMACapError.ulSlice = OM_GetSlice();
        }

        g_ulIsWaitingDMACap = VOS_FALSE;
    }

    /* BBP�Ĵ������� */
    if (VOS_RATMODE_WCDMA == enMode)
    {
        g_ulSleepBBPPosValue  = HPA_Read32Reg(WBBP_TRACE_CPI_FRM_POS_ADDR);
    }

    /* �µ�BBP */
    /*lint -e534*/
    SLEEP_DEVICE_POWDOWN(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* �ر�BBP����ʱ�� */
    mdrv_pm_disable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* �ر�BBP PLL */
    SLEEP_DEVICEPLL_POWDOWN((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    /* �ر�ABB PLL */
    SLEEP_ABBPllDisable(enMode);

    /* �µ�ABB */
    SLEEP_ABBPowerDown(enMode);

    /* �µ�RF */
    SLEEP_RFPowerDown(enMode);
    SLEEP_RFFECfgPowerDown(enMode);

    /* �ر�TCXO */
    SLEEP_TCXODisable(enMode);

    return;
}


VOS_VOID SLEEP_ActivateHw(SLEEP_MODE_ENUM_UINT32 enMode)
{
    MODEM_ID_ENUM_UINT16                enModem;
    VOS_UINT32                          ulSlice;

    enModem = SLEEP_GetModemId();

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_ACTIVATE_START);

    /* ��TCXO */
    SLEEP_TCXOEnable(enMode);

    SLEEP_WAKE_SLICE_RECORD(5);

    /* �ϵ�RF */
    SLEEP_RFPowerUp(enMode);

    SLEEP_WAKE_SLICE_RECORD(6);

    /* �ϵ�ABB */
    SLEEP_ABBPowerUp(enMode);

    /* ��ABB PLL */
    SLEEP_ABBPllEnable(enMode);

    /* V8R1��BBP CS������Դ�����迪�أ������ڽ⸴λBBP CS����ǰ����Ҫ�ȴ��ſغ�ʱ��*/
    /* ��BBP PLL */
    /*lint -e534*/
    SLEEP_DEVICEPLL_POWUP((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);

    /* ��BBP����ʱ�� */
    mdrv_pm_enable_bbpclk((PWC_COMM_MODE_E)enMode, PWC_COMM_MODULE_BBP_DRX, (PWC_COMM_MODEM_E)enModem, PWC_COMM_CHANNEL_0);

    /* �ϵ�BBP */
    SLEEP_DEVICE_POWUP(enModem, enMode, PWC_COMM_MODULE_BBP_DRX, PWC_COMM_CHANNEL_0);
    /*lint +e534*/

    ulSlice = OM_GetSlice();

    /* �����Slice�ȴ������ȶ� */
    while((g_ulSleepRusumeTime) > (OM_GetSlice() - ulSlice))
    {
        ;
    }

    SLEEP_RFFECfgPowerUp(enMode);

    /* BBP�Ĵ����ָ� */
    if (VOS_RATMODE_WCDMA == enMode)
    {
        SLEEP_ResumeReg();
    }

    if (VOS_RATMODE_WCDMA == enMode)
    {
        if (BBP_ERROR_VALUE == HPA_Read32Reg(WBBP_ARM_INT01_MASK_ADDR))
        {
            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->astDevicePowerError[enMode].ulCount++;
                g_pstSleepDeviceState->astDevicePowerError[enMode].ulSlice  = OM_GetSlice();
            }
        }

        HPA_3GIsrEnable(enModem);
    }
    else
    {
        if (BBP_ERROR_VALUE == HPA_Read32Reg(g_aulGUCBBPRegAddr[INT_MASK][enModem][enMode]))
        {
            ulSlice = OM_GetSlice();

            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->aulABBState[0]       = ulSlice;
            }

            while (SLEEP_BBP_ERROR_TIMEOUT > (OM_GetSlice() - ulSlice))
            {
                if (BBP_ERROR_VALUE != HPA_Read32Reg(g_aulGUCBBPRegAddr[INT_MASK][enModem][enMode]))
                {
                    break;
                }
            }

            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->aulABBState[1]   = OM_GetSlice();

                g_pstSleepDeviceState->astDevicePowerError[enMode].ulCount++;
                g_pstSleepDeviceState->astDevicePowerError[enMode].ulSlice  = OM_GetSlice();

                VOS_ProtectionReboot(DRX_REPORT_BBP_READ_ERROR, (VOS_INT32)g_pstSleepDeviceState->aulABBState[0], (VOS_INT32)g_pstSleepDeviceState->aulABBState[1], VOS_NULL_PTR, VOS_NULL);
             }
        }

        HPA_2GIsrEnable(enModem);
    }

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_ACTIVATE_END);

    return;
}


VOS_UINT32 SLEEP_WakePhy(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode, UPHY_OAM_WAKE_TYPE_ENUM_UINT32 enWakeType)
{
    UPHY_OAM_WAKE_CMD_STRU               *pstPhyMsg;

    /* ������Ϣ�ڴ� */
    pstPhyMsg = (UPHY_OAM_WAKE_CMD_STRU*)VOS_AllocMsg(WUEPS_PID_AWAKE,
                    sizeof(UPHY_OAM_WAKE_CMD_STRU) + sizeof(SLEEP_NORMAL_STATE_RECORD_STRU) - VOS_MSG_HEAD_LENGTH);

    /* ����ʧ�� */
    if (VOS_NULL_PTR == pstPhyMsg)
    {
        return VOS_ERR;
    }

    pstPhyMsg->ulReceiverPid = DSP_PID_WAKE;

    pstPhyMsg->enMsgId       = (VOS_UINT16)ulMsgId;
    pstPhyMsg->enModem       = SLEEP_GetModemId();
    pstPhyMsg->enRatMode     = enMode;
    pstPhyMsg->enWakeType    = enWakeType;

    /*lint -e534*/
    VOS_MemCpy(pstPhyMsg->pRecordInfo, (VOS_VOID *)g_pstSleepNormalState, sizeof(SLEEP_NORMAL_STATE_RECORD_STRU));
    /*lint +e534*/

    /* ������Ϣ */
    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AWAKE, pstPhyMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID SLEEP_AwakeIsrProc(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_INT                             lLockLevel;
    SLEEP_ISR_MSG_STRU                 *pstIsrMsg;

    lLockLevel = VOS_SplIMP();

    /* ��ֹ��˯ͶƱ */
    SLEEP_VoteLock(enMode);

    /* �ж����м�¼ */
    SLEEP_ISR_RECORD(ulMsgId, enMode);

    /* ������Ϣ�ڴ� */
    pstIsrMsg = (SLEEP_ISR_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_AWAKE,
                    sizeof(SLEEP_ISR_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstIsrMsg)
    {
        VOS_Splx(lLockLevel);

        return;
    }

    pstIsrMsg->ulReceiverPid = WUEPS_PID_AWAKE;
    pstIsrMsg->usMsgId       = (VOS_UINT16)ulMsgId;
    pstIsrMsg->enRatMode     = enMode;
    pstIsrMsg->ulSlice       = OM_GetSlice();

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_AWAKE, pstIsrMsg))
    {
        /*; */
    }

    VOS_Splx(lLockLevel);

    return;
}


VOS_VOID SLEEP_SleepIsrProc(VOS_UINT32 ulMsgId, SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_INT                             lLockLevel;
    SLEEP_ISR_MSG_STRU                 *pstIsrMsg;

    lLockLevel = VOS_SplIMP();

    /* ��ֹ��˯ͶƱ */
    SLEEP_VoteLock(enMode);

    /* �ж����м�¼ */
    SLEEP_ISR_RECORD(ulMsgId, enMode);

    /* ������Ϣ�ڴ� */
    pstIsrMsg = (SLEEP_ISR_MSG_STRU*)VOS_AllocMsg(WUEPS_PID_SLEEP,
                    sizeof(SLEEP_ISR_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstIsrMsg)
    {
        VOS_Splx(lLockLevel);

        return;
    }

    pstIsrMsg->ulReceiverPid = WUEPS_PID_SLEEP;
    pstIsrMsg->usMsgId       = (VOS_UINT16)ulMsgId;
    pstIsrMsg->enRatMode     = enMode;
    pstIsrMsg->ulSlice       = OM_GetSlice();

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SLEEP, pstIsrMsg))
    {
        /*; */
    }

    VOS_Splx(lLockLevel);

    return;
}


VOS_VOID SLEEP_32KClkMsgProc(MsgBlock *pstMsg)
{
    UPHY_OAM_SLEEP_IND_STRU             *pstPhyReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#ifdef FEATURE_DSP2ARM
    VOS_UINT32                          ulQueueSize = 0;
#endif
    MSG_CB                             *pMsg;
    VOS_ULONG                           ulLockLevel;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    enMode    = pstPhyReq->enRatMode;

    /* ������� */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* �쳣��ӡ�ͼ�¼ */
        PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_32KClkMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    /* ���統ǰϵͳΪNORMAL̬���л�Ϊ��ģ˯����̬ */
    if (SLEEP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_MASTER_TEMP_LP_STATE;

        /*lint -e534*/
        VOS_SmV(g_ulSleepSem);
        /*lint +e534*/

        return;
    }

    /* ���統ǰϵͳΪ��ģ˯����̬���л�Ϊ��ģ˯��̬ */
    if (SLEEP_MASTER_TEMP_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        SLEEP_WAKE_SLICE_RECORD(2);

        /* �µ�RTT��ϵͳ */
        SLEEP_DeactivateHw(enMode);

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_LP);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_MASTER_LP_STATE;

#ifdef FEATURE_DSP2ARM
        VOS_SpinLockIntLock(&g_stSleepSpinLock, ulLockLevel);

        /* ��ȡGUPHY��Ϣ��������Ϣ���� */
        if (VOS_RATMODE_WCDMA == enMode)
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_WPHY);
        }
        else
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_GPHY);
        }

        /* �����Ϣ����������Ϣ�������ǿ�ƻ������� */
        if (0 < ulQueueSize)
        {
            if (VOS_RATMODE_WCDMA == enMode)
            {
                pMsg   = (MSG_CB *)VOS_FixedQueueReadMsg(DSP_FID_WPHY);
            }
            else
            {
                pMsg   = (MSG_CB *)VOS_FixedQueueReadMsg(DSP_FID_GPHY);
            }

            if (VOS_NULL_PTR != pMsg)
            {
#if defined (INSTANCE_1)
                if ((DSP_PID_GPHY <= pMsg->ulSenderPid) && (DSP_PID_APM >= pMsg->ulSenderPid))
#else
                if ((DSP_PID_APM <= pMsg->ulSenderPid) && (DSP_PID_IDLE >= pMsg->ulSenderPid))
#endif
                {
                    /*VOS_ProtectionReboot(DRX_PHY_PROTECT_ERROR, VOS_FILE_ID, __LINE__, 0, 0);*/
                }
            }

            VOS_SpinUnlockIntUnlock(&g_stSleepSpinLock, ulLockLevel);

            SLEEP_MasterForceWake(enMode);
        }
        else
#endif
        {
            VOS_SpinUnlockIntUnlock(&g_stSleepSpinLock, ulLockLevel);

            SLEEP_WAKE_SLICE_RECORD(3);

            /* ������˯ͶƱ */
            SLEEP_VoteUnlock(enMode);
        }

        /*lint -e534*/
        VOS_SmV(g_ulSleepSem);
        /*lint +e534*/

        return;
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}
VOS_VOID SLEEP_MasterSleepMsgProc(MsgBlock *pstMsg)
{
    UPHY_OAM_SLEEP_IND_STRU                 *pstPhyReq;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    if (VOS_RATMODE_WCDMA == pstPhyReq->enRatMode)
    {
        /* ˯��ǰ���SFN��CFN�ĸ��� */
        HPA_ReadCfnSfn();

        /* ˯��ǰ֪ͨ��2�ж����������Ƿ���� */
        WTTF_MAC_R99MailBox_ReadForIpcHalt();
    }

    SLEEP_NOR_STATE_TRACK(pstPhyReq->enRatMode, SLEEP_MASTER_PHY_HALT);

    SLEEP_WAKE_SLICE_RECORD(1);

    /* ��32K�ж���ͬ�Ĵ������� */
    SLEEP_32KClkMsgProc(pstMsg);

    return;
}
VOS_VOID SLEEP_WakeMasterMsgProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
    VOS_INT32                           lIntLevel;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    /* ������� */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* �쳣��ӡ�ͼ�¼ */
        PS_LOG1(WUEPS_PID_AWAKE, 0, PS_PRINT_ERROR, "SLEEP_WakeMasterMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    /* ֻ��ϵͳ����ģ�͹���״̬���ܽ��뵽NORMAL��̬ */
    if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* �ϵ�RTT��ϵͳ */
        SLEEP_ActivateHw(enMode);

        lIntLevel = VOS_SplIMP();

#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
        /* ����WBBP���ּĴ��� */
        if (VOS_RATMODE_WCDMA == enMode)
        {
            HPA_Write32Reg(WBBP_DSP_READY_IND_1CARD_ADDR, BBP_HANDSHAKE_BIT);

            /* ��¼���ô�����Sliceֵ */
            if (VOS_NULL_PTR != g_pstSleepDeviceState)
            {
                g_pstSleepDeviceState->stHandShakeRecord.ulCount++;
                g_pstSleepDeviceState->stHandShakeRecord.ulSlice = OM_GetSlice();
            }
        }

#endif
        if (VOS_RATMODE_GSM == enMode)
        {
            /* ǿ�ƻ���G BBP */
            HPA_Write32RegMask(GBBP_SLEEP_EN_ADDR, BIT_N(2));
        }

        g_astSleepModeInfo[enMode].enWakeType    = UPHY_OAM_NORMAL_WAKE;
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_TEMP_NORMAL_STATE;

        VOS_Splx(lIntLevel);
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}
VOS_VOID SLEEP_NormalClkMsgProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
    VOS_UINT32                          ulDeltaSlice;
#endif

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    /* ������� */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* �쳣��ӡ�ͼ�¼ */
        PS_LOG1(WUEPS_PID_AWAKE, 0, PS_PRINT_ERROR, "SLEEP_NormalClkMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_WAKE_PHY_PRE);

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    /* ��¼��ǰϵͳ״̬��Sliceֵ */

    ;

    /* ֻ��ϵͳ��NORMAL��̬���ܽ��뵽NORMAL̬ */
    if (SLEEP_TEMP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* ������Ϣ��PHY_IDLE����PHY */
        /*lint -e534*/
        SLEEP_WakePhy(ID_OAM_UPHY_MASTER_WAKE_CMD, enMode, g_astSleepModeInfo[enMode].enWakeType);
        /*lint +e534*/

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_WAKE_PHY);

        SLEEP_WAKE_SLICE_RECORD(7);

        SLEEP_MSG_RECORD(ID_OAM_UPHY_MASTER_WAKE_CMD, DSP_PID_WAKE, g_astSleepModeInfo[enMode].enWakeType);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_NORMAL_STATE;

#if (FEATURE_GUBBP_HANDSHAKE == FEATURE_ON)
        if (VOS_RATMODE_WCDMA == enMode)
        {
            /* BBP�Ĵ���switch_delay_cnt_1card(0x1CC8)��bit 0~31����ȡ��"���Ѻ�ʱ���л��жϱ�ԭ��Ԥ����ʱ�����˶���32kʱ������"����������Ӧ�Ĵ��� */
            ulDeltaSlice = HPA_Read32Reg(WBBP_SWITCH_DELAY_CNT_1CARD_ADDR);
            if ((ulDeltaSlice > 0) && (ulDeltaSlice < SLEEP_BBP_HANDSHAKE_MAX_DELAY))
            {
                /* ��¼��ά�ɲ⣬��������Լ���ִ�У�������λ */
                SLEEP_BBP_SWITCH_INT_DELAY_RECORD(ulDeltaSlice);
            }
            else if (ulDeltaSlice >= SLEEP_BBP_HANDSHAKE_MAX_DELAY)
            {
                /* ����������쳣(���δ�������֣�������쳣����һֱδ����)����¼��ά�ɲ⣬����λ */
                SLEEP_BBP_SWITCH_INT_DELAY_RECORD(ulDeltaSlice);

                VOS_ProtectionReboot(DRX_REPORT_HANDSHAKE_ABNORMAL, THIS_FILE_ID, __LINE__, VOS_NULL_PTR, 0);
            }
            else
            {
                /* ������������账�� */
            }
        }
#endif
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}
VOS_VOID SLEEP_SlaveSleepMsgProc(MsgBlock *pstMsg)
{
    UPHY_OAM_SLEEP_IND_STRU            *pstPhyReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#if ((!defined(INSTANCE_1)) && (!defined(INSTANCE_2)))
    VOS_INT32                           lMeansFlag  = VOS_FALSE;
#endif
#ifdef FEATURE_DSP2ARM
    VOS_UINT32                          ulQueueSize = 0;
#endif

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    enMode    = pstPhyReq->enRatMode;

    /* ������� */
    if (SLEEP_GU_MODE_TYPE_BUTT <= enMode)
    {
        /* �쳣��ӡ�ͼ�¼ */
        PS_LOG1(WUEPS_PID_SLEEP, 0, PS_PRINT_ERROR, "SLEEP_SlaveSleepMsgProc: Mode para is wrong.", (VOS_INT32)enMode);
        return;
    }

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_NOR_STATE_TRACK(enMode, SLEEP_SLAVE_PHY_HALT);

    /* ֻ��ϵͳ��NORMAL̬���ܽ��뵽��ģ�͹��� */
    if (SLEEP_NORMAL_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* �µ�RTT */
        SLEEP_DeactivateHw(enMode);

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_SLAVE_LP);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_SLAVE_LP_STATE;

        /* �����ģ�͹���״̬��֪ͨע��PID */
        SLEEP_NotifyStateToRegPid(enMode, SLEEP_SLAVE_LP_STATE);

#ifdef FEATURE_DSP2ARM
        /* ��ȡGUPHY��Ϣ��������Ϣ���� */
        if (VOS_RATMODE_WCDMA == enMode)
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_WPHY);
        }
        else
        {
            ulQueueSize = VOS_GetQueueSizeFromFid(DSP_FID_GPHY);
        }
#endif

        /*��������Ҫ�ж��Ƿ��в�����־λ*/
#if defined(INSTANCE_1) || defined(INSTANCE_2)
    #ifdef FEATURE_DSP2ARM
        if (0 < ulQueueSize)
        {
            SLEEP_SlaveForceWake(enMode);
        }
        else
    #endif
        {
            /* ������˯ͶƱ */
            SLEEP_VoteUnlock(enMode);

        #if defined(INSTANCE_2)
            if (VOS_RATMODE_GSM == enMode)
            {
                if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
                {
                    if (VOS_TRUE == g_ulSleepSlaveSemFlag)
                    {
                        g_pstSleepDeviceState->ulSlaveSEMGiveTimes++;
                        g_pstSleepDeviceState->ulSlaveSEMGiveStartSlice   = OM_GetSlice();

                        g_ulSleepSlaveSemFlag   = VOS_FALSE;

                        /*lint -e534*/
                        VOS_SmV(g_ulSleepSlaveSem);
                        /*lint +e534*/

                        g_pstSleepDeviceState->ulSlaveSEMGiveEndSlice     = OM_GetSlice();
                    }
                }
            }
        #endif
        }
#else
        lMeansFlag = mdrv_bbp_get_measure_flag((PWC_COMM_MODE_E)enMode);

    #ifdef FEATURE_DSP2ARM
        if ((0 < ulQueueSize) || (VOS_TRUE == lMeansFlag))
    #else
        if (VOS_TRUE == lMeansFlag)
    #endif
        {
            SLEEP_SlaveForceWake(enMode);
        }
        else
        {
            /* ������˯ͶƱ */
            SLEEP_VoteUnlock(enMode);

            if (VOS_RATMODE_GSM == enMode)
            {
                if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
                {
                    if (VOS_TRUE == g_ulSleepSlaveSemFlag)
                    {
                        g_pstSleepDeviceState->ulSlaveSEMGiveTimes++;
                        g_pstSleepDeviceState->ulSlaveSEMGiveStartSlice   = OM_GetSlice();

                        g_ulSleepSlaveSemFlag   = VOS_FALSE;

                        /*lint -e534*/
                        VOS_SmV(g_ulSleepSlaveSem);
                        /*lint +e534*/

                        g_pstSleepDeviceState->ulSlaveSEMGiveEndSlice     = OM_GetSlice();
                    }
                }
            }
        }
#endif
    }

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}
VOS_VOID SLEEP_WakeSlaveGUProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;
#if defined(INSTANCE_1)
#else
    VOS_INT32                           lLockLevel;
#endif
    SLEEP_SYSTEM_STATE_ENUM_UINT32      enSleepState;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    /* Austin Modem0 & Modem2����GBBP��GSM���µ�������Ҫͨ��Ӳ����������б��� */
#if defined(INSTANCE_1)
#else
    lLockLevel = VOS_SplIMP();

    enSleepState    = g_astSleepModeInfo[enMode].enSystemState;

    VOS_Splx(lLockLevel);

    /* �жϵ�ǰ�Ƿ��ڴ�ģ�͹���״̬ */
    if (SLEEP_SLAVE_LP_STATE == enSleepState)
    {
        if (VOS_RATMODE_GSM == enMode)
        {
            if (VOS_TRUE == UPHY_DSDA_GetGsmSlaveDrxFlag(SLEEP_GetModemId()))
            {
                g_pstSleepDeviceState->ulSlaveSEMTakeTimes++;
                g_pstSleepDeviceState->ulSlaveSEMTakeStartSlice   = OM_GetSlice();

                /* ��ȡIPCӲ���� */
                if (VOS_OK != VOS_SmP(g_ulSleepSlaveSem, SLEEP_IPC_TIMEOUT))
                {
                    if (0 != g_ulSleepSlaveMsgTrackId)
                    {
                        g_ulSleepSlaveMsgTrackId--;
                    }
                    else
                    {
                        g_ulSleepSlaveMsgTrackId    = SLEEP_SLAVE_MSG_TRACK_NUM-1;
                    }

                    VOS_ProtectionReboot(DRX_SLAVE_WAKE_IPC_ERROR, (VOS_INT)g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulSenderPid,
                        (VOS_INT)g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulMsgName, 0, 0);
                }

                g_pstSleepDeviceState->ulSlaveSEMTakeEndSlice     = OM_GetSlice();

                g_ulSleepSlaveSemFlag   = VOS_TRUE;
            }
        }
    }
#endif

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_SlaveForceWake(enMode);

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}
VOS_VOID SLEEP_WakeMasterGUProc(MsgBlock *pstMsg)
{
    SLEEP_ISR_MSG_STRU                 *pstIsrReq;
    SLEEP_MODE_ENUM_UINT32              enMode;

    pstIsrReq = (SLEEP_ISR_MSG_STRU*)pstMsg;

    enMode    = pstIsrReq->enRatMode;

    (VOS_VOID)VOS_SmP(g_ulSleepSem, 0);

    SLEEP_MasterForceWake(enMode);

    /*lint -e534*/
    VOS_SmV(g_ulSleepSem);
    /*lint +e534*/

    return;
}


VOS_UINT32 SLEEP_MasterWakeSlave(SLEEP_MODE_ENUM_UINT32 enRatMode)
{
    VOS_INT32                           lLockLevel;

    switch (enRatMode)
    {
        case VOS_RATMODE_WCDMA:
        case VOS_RATMODE_GSM:
            lLockLevel = VOS_SplIMP();

            if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[enRatMode].enSystemState)
            {
                SLEEP_AwakeIsrProc(SLEEP_WAKE_SLAVE_GU_IND, enRatMode);
            }

            VOS_Splx(lLockLevel);

            break;

        case VOS_RATMODE_LTE:
        case VOS_RATMODE_TDS:
#if (RAT_MODE != RAT_GU)
            TLSLEEP_MasterAwakeSlave();
#endif
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}


VOS_VOID SLEEP_MasterForceWake(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_INT32                           lIntLevel;

    if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        /* ��ֹ��˯ͶƱ */
        SLEEP_VoteLock(enMode);

        /* �ϵ�RTT��ϵͳ */
        SLEEP_ActivateHw(enMode);

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_MASTER_FORCE_WAKE);

        lIntLevel = VOS_SplIMP();

        /*�ж�����Ƿ�������WAKE�ж��ϱ�*/
        if (VOS_RATMODE_WCDMA == enMode)
        {
            if (VOS_OK != SLEEP_ForceWakeProtected())
            {
                VOS_Splx(lIntLevel);

                return;
            }

            /* ǿ�ƻ���W BBP */
            HPA_Write32RegMask(WBBP_SWITCH_UP_1CARD_ADDR, BBP_AWAKE_BIT);
        }
        else
        {
            /* ǿ�ƻ���G BBP */
            /*lint -e701*/
            HPA_Write32RegMask(GBBP_SLEEP_EN_ADDR, SLEEP_BIT_N(2));
            /*lint +e701*/
        }

        g_astSleepModeInfo[enMode].enWakeType    = UPHY_OAM_FORCE_WAKE;
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_TEMP_NORMAL_STATE;

        VOS_Splx(lIntLevel);
    }

    return;
}
VOS_VOID SLEEP_SlaveForceWake(SLEEP_MODE_ENUM_UINT32 enMode)
{
    VOS_UINT32                          ulStartSlice;

    /* �жϵ�ǰ�Ƿ��ڴ�ģ�͹���״̬ */
    if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[enMode].enSystemState)
    {
        ulStartSlice    = OM_GetSlice();

        /* ��ֹ��˯ͶƱ */
        SLEEP_VoteLock(enMode);

        /* �ϵ�RTT */
        SLEEP_ActivateHw(enMode);

        SLEEP_MSG_RECORD(ID_OAM_UPHY_SLAVE_WAKE_CMD, DSP_PID_WAKE, ulStartSlice);

        /* ������Ϣ��PHY_IDLE����PHY */
        /*lint -e534*/
        SLEEP_WakePhy(ID_OAM_UPHY_SLAVE_WAKE_CMD, enMode, UPHY_OAM_FORCE_WAKE);
        /*lint +e534*/

        SLEEP_NOR_STATE_TRACK(enMode, SLEEP_SLAVE_FORCE_WAKE);

        g_astSleepModeInfo[enMode].enSystemState = SLEEP_NORMAL_STATE;
    }

    return;
}


VOS_VOID SLEEP_HookMsgProc(MsgBlock *pstMsg)
{
    VOS_INT                             lLockLevel;

    if (VOS_FALSE != VOS_CheckInterrupt())
    {
        return;
    }

    /* �ж��Ƿ�����Ϣ���͸�WPHY */
    if (DSP_PID_WPHY == pstMsg->ulReceiverPid)
    {
        lLockLevel = VOS_SplIMP();

        if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_WCDMA].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_MASTER_GU_IND, VOS_RATMODE_WCDMA);
        }
        else if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_WCDMA].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_SLAVE_GU_IND, VOS_RATMODE_WCDMA);
        }
        else
        {
        }

        VOS_Splx(lLockLevel);

        return;
    }

    /* �ж��Ƿ�����Ϣ���͸�GPHY */
    if (DSP_PID_GPHY == pstMsg->ulReceiverPid)
    {
        lLockLevel = VOS_SplIMP();

        if (SLEEP_MASTER_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_GSM].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_MASTER_GU_IND, VOS_RATMODE_GSM);
        }
        else if (SLEEP_SLAVE_LP_STATE == g_astSleepModeInfo[VOS_RATMODE_GSM].enSystemState)
        {
            SLEEP_AwakeIsrProc(SLEEP_WAKE_SLAVE_GU_IND, VOS_RATMODE_GSM);

            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulMode      = VOS_RATMODE_GSM;
            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulSenderPid = pstMsg->ulSenderPid;
            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulMsgName   = *((VOS_UINT32 *)(pstMsg->aucValue));
            g_astSleepSlaveMsgTrack[g_ulSleepSlaveMsgTrackId].ulSlice     = OM_GetSlice();

            g_ulSleepSlaveMsgTrackId++;

            if (SLEEP_SLAVE_MSG_TRACK_NUM == g_ulSleepSlaveMsgTrackId)
            {
                g_ulSleepSlaveMsgTrackId = 0;
            }
        }
        else
        {
        }

        VOS_Splx(lLockLevel);

        return;
    }

    return;
}


VOS_VOID SLEEP_AwakeMsgProc(MsgBlock* pstMsg)
{
    SLEEP_MSG_FUN_STRU                 *pstMsgFun;
    VOS_UINT32                          ulTlbSize;
    VOS_UINT32                          ulIndex;
    UPHY_OAM_SLEEP_IND_STRU            *pstPhyReq;
    VOS_UINT32                          ulStartSlice = 0;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    /* �ж���Ϣ���� */
    if (WUEPS_PID_AWAKE == pstPhyReq->ulSenderPid)
    {
        pstMsgFun = g_astAwakeIsrMsgFunTbl;
        ulTlbSize = sizeof(g_astAwakeIsrMsgFunTbl)/sizeof(SLEEP_MSG_FUN_STRU);
    }
    else
    {
        /* δ֪��Ϣֱ�ӷ��� */
        /*lint -e534*/
        LogPrint1("SLEEP_AwakeMsgProc: Unknown ulSenderPid:%d.\r\n",
                        (VOS_INT)pstMsg->ulSenderPid);
        /*lint +e534*/

        SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

        return;
    }

    for (ulIndex = 0; ulIndex < ulTlbSize; ulIndex++)
    {
        /* ���ҵ���Ӧ��ϢID�Ĵ����� */
        if (pstPhyReq->enMsgId == (UPHY_OAM_MSG_ID_ENUM_UINT16)pstMsgFun[ulIndex].ulMsgId)
        {
            ulStartSlice = OM_GetSlice();

            pstMsgFun[ulIndex].pMsgFun(pstMsg);

            /* ��¼�������Ϣ */
            SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->enRatMode, ulStartSlice);

            return;
        }
    }

    SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

    /* �쳣��ӡ�ͼ�¼ */
    /*lint -e534*/
    LogPrint2("SLEEP_AwakeMsgProc: Unknown Msg, ulSenderPid:%d, enMsgId:%d.\r\n",
                (VOS_INT)pstPhyReq->ulSenderPid, (VOS_INT)pstPhyReq->enMsgId);
    /*lint +e534*/
    return;
}
VOS_VOID SLEEP_SleepMsgProc(MsgBlock* pstMsg)
{
    SLEEP_MSG_FUN_STRU                 *pstMsgFun;
    VOS_UINT32                          ulTlbSize;
    VOS_UINT32                          ulIndex;
    UPHY_OAM_SLEEP_IND_STRU             *pstPhyReq;
    VOS_UINT32                          ulStartSlice = 0;

    pstPhyReq = (UPHY_OAM_SLEEP_IND_STRU*)pstMsg;

    /* �ж���Ϣ���� */
    if (WUEPS_PID_SLEEP == pstPhyReq->ulSenderPid)
    {
        pstMsgFun = g_astSleepIsrMsgFunTbl;
        ulTlbSize = sizeof(g_astSleepIsrMsgFunTbl)/sizeof(SLEEP_MSG_FUN_STRU);
    }
    /* PHY������Ϣ����*/
    else if (DSP_PID_SLEEP == pstPhyReq->ulSenderPid)
    {
        pstMsgFun = g_astSleepPhyMsgFunTbl;
        ulTlbSize = sizeof(g_astSleepPhyMsgFunTbl)/sizeof(SLEEP_MSG_FUN_STRU);
    }
    else
    {
        /* δ֪��Ϣֱ�ӷ��� */
        /*lint -e534*/
        LogPrint1("SLEEP_MsgProc: Unknown ulSenderPid:%d.\r\n",
                        (VOS_INT)pstMsg->ulSenderPid);
        /*lint +e534*/

        SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

        return;
    }

    for (ulIndex = 0; ulIndex < ulTlbSize; ulIndex++)
    {
        /* ���ҵ���Ӧ��ϢID�Ĵ����� */
        if (pstPhyReq->enMsgId == (UPHY_OAM_MSG_ID_ENUM_UINT16)pstMsgFun[ulIndex].ulMsgId)
        {
            ulStartSlice = OM_GetSlice();

            pstMsgFun[ulIndex].pMsgFun(pstMsg);

            /* ��¼�������Ϣ */
            SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->enRatMode, ulStartSlice);

            return;
        }
    }

    SLEEP_MSG_RECORD(pstPhyReq->enMsgId, pstPhyReq->ulSenderPid, ulStartSlice);

    /* �쳣��ӡ�ͼ�¼ */
    /*lint -e534*/
    LogPrint2("SLEEP_MsgProc: Unknown Msg, ulSenderPid:%d, enMsgId:%d.\r\n",
                (VOS_INT)pstPhyReq->ulSenderPid, (VOS_INT)pstPhyReq->enMsgId);
    /*lint +e534*/
    return;
}


VOS_VOID SLEEP_Init(VOS_VOID)
{
    SLEEP_MODE_ENUM_UINT32              enMode;
    /*lint -e438 ����ulRecordAddrû��ʹ�õĴ���*/
    VOS_UINT32                          ulRecordAddr;
    UCOM_NV_TRI_MODE_ENABLE_STRU        stRfSwitchFlag;
    BSP_DDR_SECT_QUERY_S                stModemSrSectQuery;
    BSP_DDR_SECT_INFO_S                 stModemSrSectInfo = {BSP_DDR_SECT_TYPE_MODEM_SR_STAMP};

    /* ��ʼ����λ��Ϣ */
    ulRecordAddr = (VOS_UINT32)VOS_EXCH_MEM_MALLOC(VOS_DUMP_MEM_TOTAL_SIZE);

#if defined (INSTANCE_1)
    if (VOS_NULL_PTR != ulRecordAddr)
    {
        ulRecordAddr += sizeof(VOS_UINT32);

        ulRecordAddr += sizeof(SLEEP_TRACK_RECORD_STRU) + sizeof(SLEEP_NORMAL_STATE_RECORD_STRU)
                        + sizeof(SLEEP_DEVICE_STATE_STRU) + sizeof(SLEEP_INFO_STATE_STRU);
    }
#elif defined (INSTANCE_2)
    if (VOS_NULL_PTR != ulRecordAddr)
    {
        ulRecordAddr += 2*sizeof(VOS_UINT32);

        ulRecordAddr += 2*(sizeof(SLEEP_TRACK_RECORD_STRU) + sizeof(SLEEP_NORMAL_STATE_RECORD_STRU)
                        + sizeof(SLEEP_DEVICE_STATE_STRU) + sizeof(SLEEP_INFO_STATE_STRU));
    }
#endif

    if (VOS_NULL_PTR != ulRecordAddr)
    {
        *(VOS_UINT32*)ulRecordAddr = 0x5555aaaa;

        ulRecordAddr += sizeof(VOS_UINT32);

        g_pstSleepTrackRecord = (SLEEP_TRACK_RECORD_STRU*)ulRecordAddr;

        /*lint -e534*/
        VOS_MemSet(g_pstSleepTrackRecord, 0, sizeof(SLEEP_TRACK_RECORD_STRU));
        /*lint +e534*/

        ulRecordAddr += sizeof(SLEEP_TRACK_RECORD_STRU);

        g_pstSleepNormalState = (SLEEP_NORMAL_STATE_RECORD_STRU*)ulRecordAddr;

        /*lint -e534*/
        VOS_MemSet(g_pstSleepNormalState, 0, sizeof(SLEEP_NORMAL_STATE_RECORD_STRU));
        /*lint +e534*/

        ulRecordAddr += sizeof(SLEEP_NORMAL_STATE_RECORD_STRU);

        g_pstSleepDeviceState   = (SLEEP_DEVICE_STATE_STRU *)ulRecordAddr;

        /*lint -e534*/
        VOS_MemSet(g_pstSleepDeviceState,   0, sizeof(SLEEP_DEVICE_STATE_STRU));
        /*lint +e534*/

        ulRecordAddr += sizeof(SLEEP_DEVICE_STATE_STRU);

        g_pstSleepDeviceState->ulDeviceFlag = 0x5A5A5A5A;

        g_pstSleepInfoSlice      = (SLEEP_INFO_STATE_STRU *)ulRecordAddr;

        ulRecordAddr += sizeof(SLEEP_INFO_STATE_STRU);

        g_pstSleepInfoSlice->ulEndFlag   = 0x87878787;
    }

    /* ��ʼ��ϵͳ״̬ */
    for (enMode = 0; enMode < SLEEP_GU_MODE_TYPE_BUTT; enMode++)
    {
        g_astSleepModeInfo[enMode].enSystemState = SLEEP_NORMAL_STATE;
    }

    g_stSleepCDMAControl.ulInfoHeadFlag     = 0x5A5A5A5A;
    g_stSleepCDMAControl.ulBBE16PowerState  = VOS_FALSE;

    if(VOS_OK != VOS_SmMCreate("SLEEP", VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulSleepSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create SLEEP.\r\n");
        /*lint +e534*/
        return;
    }

    if(VOS_OK != VOS_SmCCreate("TCXO", 0, VOS_SEMA4_FIFO, &g_ulSleepTcxoSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create TCXO.\r\n");
        /*lint +e534*/
        return;
    }

    if(VOS_OK != VOS_SmCCreate("DMA", 0, VOS_SEMA4_FIFO, &g_ulSleepDMACapSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create DMA.\r\n");
        /*lint +e534*/
        return;
    }

#if defined (INSTANCE_1) || defined (INSTANCE_2)
#else
    if(VOS_OK != VOS_SmBCreate("Ssem", VOS_SEM_FULL, VOS_SEMA4_PRIOR | VOS_SEMA4_INVERSION_SAFE, &g_ulSleepSlaveSem))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Create Ssem.\r\n");
        /*lint +e534*/
        return;
    }
#endif

    /* ��ȡNV�����ȶ�ʱ�� */
    if(NV_OK != NV_Read(en_NV_Item_WG_DRX_RESUME_TIME, &g_stSleepDrxResumeTime, sizeof(WG_DRX_RESUME_TIME_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_WG_DRX_RESUME_TIME Fail.\r\n");
        /*lint +e534*/
        return;
    }

    /* ��ȡDRX�ϵ������쳣����ʹ�ܱ�־ */
    if(NV_OK != NV_Read(en_NV_Item_DRX_RESET_ENABLE_CFG, &g_bDrxResetFlag, sizeof(NV_SLEEP_DRX_RESET_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_DRX_RESET_ENABLE_CFG Fail.\r\n");
        /*lint +e534*/
        return;
    }

    /* ��ȡȫ��ͨProfile Index������ */
    if(NV_OK != NV_Read(en_NV_Item_TRI_MODE_FEM_PROFILE_ID, &g_stChannelModeProfileId, sizeof(UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_TRI_MODE_FEM_PROFILE_ID Fail.\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }

    if (g_stChannelModeProfileId.uwProfileId >= UCOM_NV_TRI_MODE_CHAN_PARA_PROFILE_NUM)
    {
        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);
    }

#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    /* ��ȡģʽͨ�������� */
    if(NV_OK != NV_Read(en_NV_Item_FEM_CHAN_PROFILE, &g_stChannelModeProfile, sizeof(UCOM_NV_FEM_CHAN_PROFILE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_FEM_CHAN_PROFILE Fail.\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }
#else
    /* ��ȡģʽͨ�������� */
    if(NV_OK != NV_Read(en_NV_Item_TRI_MODE_FEM_CHAN_PROFILE, &g_stChannelModeProfile, sizeof(UCOM_NV_TRI_MODE_FEM_CHAN_PROFILE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_TRI_MODE_FEM_CHAN_PROFILE Fail.\r\n");
        /*lint +e534*/

        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }
#endif

    /* ��ȡȫ��ͨProfile Index������ */
    if(NV_OK != NV_Read(en_NV_Item_TRI_MODE_ENABLE, &stRfSwitchFlag, sizeof(UCOM_NV_TRI_MODE_ENABLE_STRU)))
    {
        /*lint -e534*/
        LogPrint("SLEEP_Init: Read en_NV_Item_TRI_MODE_ENABLE Fail.\r\n");
        /*lint +e534*/

        return;
    }

#if defined (INSTANCE_1) || defined (INSTANCE_2)
#else
    if (VOS_TRUE == stRfSwitchFlag.uhwEnable)
    {
        if (VOS_TRUE == g_stChannelModeProfile.astPara[g_stChannelModeProfileId.uwProfileId].uwGpioCtrl)
        {
            /* ȫ��ͨ������Ҫ����ʱ������Ƶ�ܽ� */
            if ( VOS_OK != mdrv_fem_ioctrl(CFG_RFFE_GROUP_GPIO_MIPI, UPHY_OAM_NV_INDEX_FULL_NET, 0, VOS_NULL))
            {
                VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

                return;
            }
        }
        else
        {
            /* ȫ��ͨ������Ҫ����ʱ������Ƶ�ܽ� */
            if ( VOS_OK != mdrv_fem_ioctrl(CFG_RFFE_GROUP_GPIO_MIPI, UPHY_OAM_NV_INDEX_FULL_NET, 1, VOS_NULL))
            {
                VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

                return;
            }
        }
    }
#endif

    /* ����ʱ���õ������µ�ͨ�� */
    if ( VOS_OK != SLEEP_GBBPClkSrcSelect() )
    {
        VOS_ProtectionReboot(DRX_FULLNET_SET_ERROR, VOS_FILE_ID, __LINE__, VOS_NULL_PTR, VOS_NULL);

        return;
    }

    stModemSrSectQuery.enSectType   = BSP_DDR_SECT_TYPE_MODEM_SR_STAMP;

    if (VOS_OK == mdrv_get_fix_ddr_addr(&stModemSrSectQuery, &stModemSrSectInfo))
    {
        g_pstSleepWakeSliceAddr  = (T_MODEM_SR_STAMP_STRU *)((VOS_UINT32)stModemSrSectInfo.pSectVirtAddr);
    }

    SLEEP_TimeCal();

    /* ע��SLEEP���Ӻ�����OSA */
    /*lint -e534*/
    VOS_RegisterAwakeFun(SLEEP_GetModemId(), SLEEP_HookMsgProc);
    /*lint +e534*/

    SLEEP_NotifyStateRegPidTblInit();

    return;
    /*lint +e438 ����ulRecordAddrû��ʹ�õĴ���*/
}


VOS_UINT32 WuepsAwakePidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            break;

        default:
            break;
    }

    return VOS_OK;
}

VOS_UINT32 WuepsAwakeFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_AWAKE,
                                        (Init_Fun_Type)WuepsAwakePidInit,
                                        (Msg_Fun_Type)SLEEP_AwakeMsgProc);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterTaskPrio(WUEPS_FID_AWAKE, COMM_AWAKE_TASK_PRIO);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            break;
        }

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 WuepsSleepPidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            break;

        default:
            break;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : WuepsSleepFidInit
 ��������  : SLEEP ģ�� FID �ĳ�ʼ������
 �������  : enum VOS_INIT_PHASE_DEFINE ip
 �������  : ��
 �� �� ֵ  : VOS_UINT32 FID ��ʼ�����
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_UINT32 WuepsSleepFidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32                          ulRslt;

    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
        {
            ulRslt = VOS_RegisterPIDInfo(WUEPS_PID_SLEEP,
                                        (Init_Fun_Type)WuepsSleepPidInit,
                                        (Msg_Fun_Type)SLEEP_SleepMsgProc);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            ulRslt = VOS_RegisterTaskPrio(WUEPS_FID_SLEEP, COMM_SLEEP_TASK_PRIO);

            if( VOS_OK != ulRslt )
            {
                return VOS_ERR;
            }

            SLEEP_Init();

            break;
        }

        default:
            break;
    }

    return VOS_OK;
}

VOS_VOID SLEEP_GUChannelShow(VOS_VOID)
{
#if (FEATURE_ON == FEATURE_MODE_FEM_CHAN_EXT)
    /*lint -e534*/
    vos_printf("\r\n FEATURE_MODE_FEM_CHAN_EXT ON Channel\r\n");

    vos_printf("GSM ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM RFCLK CHAN is %d\r\n", SLEEP_RFCLK_CHAN(VOS_RATMODE_GSM));

    vos_printf("WCDMA ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA RFCLK CHAN is %d\r\n", SLEEP_RFCLK_CHAN(VOS_RATMODE_WCDMA));
    /*lint +e534*/
#else
    /*lint -e534*/
    vos_printf("\r\n FEATURE_MODE_FEM_CHAN_EXT OFF Channel\r\n");

    vos_printf("GSM ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_GSM));
    vos_printf("GSM TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_GSM));

    vos_printf("WCDMA ABB   CHAN is %d\r\n", SLEEP_ABB_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA RF    CHAN is %d\r\n", SLEEP_RF_CHAN(VOS_RATMODE_WCDMA));
    vos_printf("WCDMA TCXO  CHAN is %d\r\n", SLEEP_TCXO_CHAN(VOS_RATMODE_WCDMA));
    /*lint +e534*/
#endif
}


VOS_VOID SLEEP_WakeSliceShow( VOS_VOID )
{
    VOS_UINT32                          i;

    if (VOS_NULL_PTR != g_pstSleepWakeSliceAddr)
    {
        for (i = 0; i < 8; i++)
        {
            /*lint -e534*/
            vos_printf("SLEEP Wake Slice[%d] is %x\r\n", i, g_pstSleepWakeSliceAddr->auwCommSRStamp[i]);
            /*lint +e534*/
        }
    }
}

#ifdef __cplusplus
#if __cplusplus
    }
#endif
#endif

