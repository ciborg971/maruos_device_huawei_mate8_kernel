

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "pamom.h"
#include "spysystem.h"
#include "TafClientApi.h"
#include "TafAppMma.h"
#include "NVIM_Interface.h"
#include "sleepsleep.h"
#include "errorlog.h"
#include "apminterface.h"
#include "hpaoperatertt.h"
/* Added by ouyangfei for AT Project, 2011-11-08, begin */
#include "TafDrvAgent.h"
/* Added by ouyangfei for AT Project, 2011-11-08, end */
#include "OmApi.h"
#include "TafOamInterface.h"
#include "DspInterface.h"
#include "omprivate.h"
#include "msp_diag_comm.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_SPYSYSTEM_C


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

HTIMER                          g_stSpyTempProtect_Timer = VOS_NULL_PTR;/*�����¶ȱ�����ѯ��ʱ��*/

HTIMER                          g_stSpyFlowCtrlTimer = VOS_NULL_PTR;/*�������ض�ʱ��*/

SPY_SYSCUR_STATUS               g_stSysCurStatus;/*���ڱ��浱ǰϵͳ״̬*/

SPY_STATE_ENUM_UINT32           g_enSpyCurState;/*���ڱ��浱ǰϵͳ����״̬*/

SPY_TEMP_STATE_CTRL_STRU        g_stTempStateCtrl; /*���浱ǰ�¶ȱ���ģ���״̬*/

SPY_TEMP_PROTECT_NV_STRU        g_stTempProtectNv; /*�¶ȱ���NV��Ľṹ*/

VOS_UINT16                      g_usSpyClientId;    /*ע���clientId*/

/*Reserve SD card and Antenna status*/
VOS_UINT32                      g_ulUsbStatus   = 0;
VOS_UINT32                      g_ulAntenStatus = 0;


SPY_DOWNGRADE_PROC_FUNC         g_pfunRegDowngradeProc = VOS_NULL_PTR;  /*�������ؽ���ִ�к���*/

SPY_DOWNGRADE_PROC_FUNC         g_pfunRegUpgradeProc = VOS_NULL_PTR;  /*������������ִ�к���*/

SPY_RESTORE_PROC_FUNC           g_pfunRegRestoreProc = VOS_NULL_PTR;  /*������ػ��ָ�����ִ�к���*/

#ifdef SPY_STATISTICS_DEBUG
/* SPY�±���ʩִ��ͳ����Ϣ */
SPY_STATISTICS_INFO_STRU        g_stSpyStatisticsInfo;

VOS_UINT32                      g_ulSpyRecordFlag = 1;
SPY_RECORD_STRU                 g_stSpyTimeRecord;
#define SPY_GetTime(ulIndex)    (g_stSpyTimeRecord.astRecord[ulIndex].ulTime)
#define SPY_GetType(ulIndex)    (g_stSpyTimeRecord.astRecord[ulIndex].acType)
#endif

#if (RAT_MODE != RAT_GU)
extern VOS_VOID L_ExtAntenStatus(VOS_INT32 para);
#endif

/* �ϱ���NAS���±�״̬��ֻ�п����͹ر�����״̬ */
SPY_TEMPROTECT_SWITCH_STATE_ENUM_UINT32                    g_ulSpySwitchState = SPY_TEMPROTECT_SWITCH_OFF;

/* NAS ֪ͨ SPY �Ľ������е�״̬ */
TAF_OAM_EMERGENCY_CALL_STATUS_ENUM_UINT8                   g_ucSpyEmergencyCallState = TAF_OAM_EMERGENCY_CALL_END;

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

#ifdef SPY_STATISTICS_DEBUG

VOS_VOID Spy_TimeRecord(VOS_CHAR * pcString)
{
    VOS_UINT32 ulRecordPosition = 0;

    if (1 != g_ulSpyRecordFlag)
    {
        return;
    }

    g_stSpyTimeRecord.ulCount++;

    ulRecordPosition = ((g_stSpyTimeRecord.ulCount-1)%SPY_RECORD_NUM);

    SPY_GetTime(ulRecordPosition) = VOS_GetTick();

    /*lint -e534*/
    VOS_StrCpy(SPY_GetType(ulRecordPosition),pcString);
    /*lint +e534*/

    return;
}
#endif

#if (defined(BOARD_ASIC) && (RAT_MODE == RAT_GU))

#if 0

VOS_INT32 Spy_UsbStatusProc(VOS_UINT8 ucUsbStatus)
{
    if (0x5A == ucUsbStatus)
    {
        if (CPHY_STATE_CONNECT == g_enSPYCPHYState)
        {
            HPA_Write32RegMask(SOC_DSP_SMIM_INT_RAW_REG, BIT_N(DSP_USB_START_BIT));
            HPA_Write32RegMask(SOC_DSP_SMIM_INT_EN_REG,  BIT_N(DSP_USB_START_BIT));
        }
        g_ulUsbStatus = BIT_N(DSP_USB_START_BIT);
    }
    else if (0xA5 == ucUsbStatus)
    {
        if (CPHY_STATE_CONNECT == g_enSPYCPHYState)
        {
            HPA_Write32RegMask(SOC_DSP_SMIM_INT_RAW_REG, BIT_N(DSP_USB_STOP_BIT));
            HPA_Write32RegMask(SOC_DSP_SMIM_INT_EN_REG,  BIT_N(DSP_USB_STOP_BIT));
        }
        g_ulUsbStatus = BIT_N(DSP_USB_STOP_BIT);
    }
    else
    {
        /*Do nothing*/
    }

    return VOS_OK;
}

#endif
#endif
VOS_VOID Spy_AntenStatusProc(MODEM_ID_ENUM_UINT16 enModemID, VOS_UINT32 ulStatus)
{
    SPY_MSG_STRU                       *pstSarMsg;

    pstSarMsg = (SPY_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_SAR,
                    sizeof(SPY_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSarMsg)
    {
        return;
    }

    pstSarMsg->ulReceiverPid    = WUEPS_PID_SAR;
    pstSarMsg->ulMsgName        = SPY_SAR_ANTEN_STATUS_IND;
    pstSarMsg->lAntenStatus     = (VOS_INT32)ulStatus;
    pstSarMsg->enModemID        = enModemID;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SAR, pstSarMsg))
    {
        return;
    }

    return;
}


VOS_VOID Spy_Anten0StatusProc(VOS_VOID)
{
    VOS_UINT                            ulStatus = 0; /* �������� */

    if (VOS_OK != mdrv_anten_get_lockstate(PWC_COMM_MODEM_0, &ulStatus))
    {
        SAR_ERROR_LOG("Spy_Anten0StatusProc: get anten status from drv fail.\r\n");
        return;
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_0, Spy_Anten0StatusProc, (VOS_INT)ulStatus);

    Spy_AntenStatusProc(MODEM_ID_0, ulStatus);
}

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
VOS_VOID Spy_Anten1StatusProc(VOS_VOID)
{
    VOS_UINT                            ulStatus = 0; /* �������� */;

    if (VOS_OK != mdrv_anten_get_lockstate(PWC_COMM_MODEM_1, &ulStatus))
    {
        SAR_ERROR_LOG("Spy_Anten1StatusProc: get anten status from drv fail.\r\n");
        return;
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_1, Spy_Anten1StatusProc, (VOS_INT)ulStatus);

    Spy_AntenStatusProc(MODEM_ID_1, ulStatus);

}
#endif
VOS_VOID Spy_SarSendToDsp(MODEM_ID_ENUM_UINT16 enModemID, MN_APP_SAR_INFO_STRU *pstSpyToDsp)
{
    PHY_OAM_SAR_CTRL_REQ_STRU          *pstSarMsg;

    pstSarMsg = (PHY_OAM_SAR_CTRL_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_SAR,
                        sizeof(PHY_OAM_SAR_CTRL_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if ( VOS_NULL_PTR == pstSarMsg )
    {
        SAR_WARNING_LOG("Spy_SarSendToDsp: Msg Alloc Failed!");
        return;
    }

    pstSarMsg->ulMask  = pstSpyToDsp->ulSarType;
    pstSarMsg->enMsgId = ID_OAM_PHY_SAR_CTRL_REQ;

    if(MODEM_ID_0 == enModemID)
    {
        pstSarMsg->ulReceiverPid    = I0_DSP_PID_APM;
    }
    else
    {
        pstSarMsg->ulReceiverPid    = I1_DSP_PID_APM;
    }

    /* ����״̬ */
    if ( PHY_OM_SAR_MASK_ANTSTATE == (PHY_OM_SAR_MASK_ANTSTATE & pstSpyToDsp->ulSarType) )
    {
        pstSarMsg->lAntenStatus = pstSpyToDsp->lAntenStatus;
    }

    /* ���ʻ��˵ȼ� */
    if ( PHY_OM_SAR_MASK_REDUCTION == (PHY_OM_SAR_MASK_REDUCTION & pstSpyToDsp->ulSarType) )
    {
        pstSarMsg->ulSarReduction = pstSpyToDsp->ulSarReduction;
    }

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SAR, pstSarMsg))
    {
        SAR_ERROR_LOG("Spy_SarSendToDsp: Send Msg Failed!");
        return;
    }

    return;
}


VOS_VOID Spy_SarSendToTaf(MODEM_ID_ENUM_UINT16 enModemID, VOS_INT32  lAntenStatus)
{
    MN_APP_SAR_ANTENSTATUS_MSG_STRU *pstAntenStatusStru;

    pstAntenStatusStru = (MN_APP_SAR_ANTENSTATUS_MSG_STRU *)VOS_AllocMsg(WUEPS_PID_SAR,
                            sizeof(MN_APP_SAR_ANTENSTATUS_MSG_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstAntenStatusStru)
    {
        SAR_WARNING_LOG("Spy_SarSendToTaf: Msg Alloc Failed!");
        return;
    }

    if (MODEM_ID_0 == enModemID)
    {
        pstAntenStatusStru->ulReceiverPid   = I0_WUEPS_PID_DRV_AGENT;
    }
    else
    {
        pstAntenStatusStru->ulReceiverPid   = I1_WUEPS_PID_DRV_AGENT;
    }

    pstAntenStatusStru->ulMsgId         = SAR_ANTSTATE_IND;
    pstAntenStatusStru->lAntenStatus    = lAntenStatus;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SAR, pstAntenStatusStru))
    {
        SAR_ERROR_LOG("Spy_SarSendToTaf: SendMsg Failed!");
        return;
    }

    return;
}


VOS_VOID Spy_SendAntenStatusToLte(MODEM_ID_ENUM_UINT16 enModemID, VOS_INT32 lAntenStatus)
{
#if (RAT_MODE != RAT_GU)
    PLATAFORM_RAT_CAPABILITY_STRU       stPlatFormRat;
    VOS_UINT32                          i;

    if (MODEM_ID_0 == enModemID)
    {
        /* ��ȡ����״̬���ж��Ƿ���Ҫ�� L ģ�� */
        if (NV_OK != NV_ReadEx(enModemID, en_NV_Item_Platform_RAT_CAP, &stPlatFormRat,
                              sizeof(PLATAFORM_RAT_CAPABILITY_STRU)))
        {
            SAR_ERROR_LOG("Spy_SendAntenStatusToLte: read nv fail.\r\n");
            return;
        }

        for (i=0; i<stPlatFormRat.usRatNum; i++)
        {
            /* ƽ̨֧��LTE */
            if (PLATFORM_RAT_LTE == stPlatFormRat.aenRatList[i])
            {
                L_ExtAntenStatus(lAntenStatus);
            }
        }
    }
#endif
    return;
}


VOS_UINT32  Spy_SarMsgProc(MsgBlock *pMsg)
{
    SPY_MSG_STRU                        *pstMsg;
    MN_APP_SAR_INFO_STRU                      stSpyToDsp;

    pstMsg = (SPY_MSG_STRU *)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case SPY_SAR_ANTEN_STATUS_IND:

            if (MODEM_ID_BUTT <= pstMsg->enModemID)
            {
                SPY_ERROR1_LOG("Spy_SarMsgProc: Modem ID is: %d error!", pstMsg->enModemID);
                return VOS_ERR;
            }

            /* ��DSP��������״̬ */
            /*lint -e534*/
            VOS_MemSet(&stSpyToDsp, 0, sizeof(MN_APP_SAR_INFO_STRU));
            /*lint +e534*/
            stSpyToDsp.lAntenStatus = pstMsg->lAntenStatus;
            stSpyToDsp.ulSarType    = PHY_OM_SAR_MASK_ANTSTATE;
            Spy_SarSendToDsp(pstMsg->enModemID,&stSpyToDsp);

            /* ��Taf��������״̬ */
            Spy_SarSendToTaf(pstMsg->enModemID,
                             pstMsg->lAntenStatus);

            /* ��Lģ��������״̬ */
            Spy_SendAntenStatusToLte(pstMsg->enModemID,
                                     pstMsg->lAntenStatus);
            break;

        default:
            break;
    }

    return VOS_OK;
}
VOS_VOID Spy_AntenStatusInit(VOS_VOID)
{
    VOS_UINT                    ulStatus = 0; /* �������� */

    if (VOS_OK == mdrv_anten_get_lockstate(PWC_COMM_MODEM_0, &ulStatus))
    {
        /* ��Lģ��������״̬ (ֻ�п�0 ����Lģ) */
        Spy_SendAntenStatusToLte(MODEM_ID_0, (VOS_INT32)ulStatus);
    }
    else
    {
        SAR_WARNING_LOG("Spy_AntenStatusInit: Get Anten 0 status Failed!");
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_0, Spy_Anten0StatusProc, (VOS_INT)ulStatus);

#if ( FEATURE_MULTI_MODEM == FEATURE_ON )
    if (VOS_OK != mdrv_anten_get_lockstate(PWC_COMM_MODEM_1, &ulStatus))
    {
        SAR_WARNING_LOG("Spy_AntenStatusInit: Anten 1 Get Failed!");
    }

    mdrv_anten_register_intr_cb(PWC_COMM_MODEM_1, Spy_Anten1StatusProc, (VOS_INT)ulStatus);
#endif

    return;
}


VOS_VOID Spy_ReportEvent(SPY_EVENT_NAME_ENUM_UINT32 enEventId, VOS_INT lSimTemp)
{
    DIAG_EVENT_IND_STRU                 stEventInd;

    stEventInd.ulModule = DIAG_GEN_MODULE(DIAG_MODEM_0, DIAG_MODE_COMM);
    stEventInd.ulPid    = WUEPS_PID_SPY;
    stEventInd.ulEventId= enEventId;
    stEventInd.ulLength = sizeof(lSimTemp);
    stEventInd.pData    = (VOS_VOID *)(&lSimTemp);

    /*lint -e534*/
    (VOS_VOID)DIAG_EventReport(&stEventInd);
    /*lint +e534*/

    return;
}

#if (RAT_MODE != RAT_GU)

VOS_VOID Spy_RegPhoneCallback(TAF_PHONE_EVENT_INFO_STRU *pEvent)
{
    if(VOS_YES != pEvent->OP_OperMode)/*�жϵ�ǰ�Ƿ��ǿ��ػ��¼�*/
    {
        return;
    }

    if((VOS_OK != pEvent->OP_PhoneError)
        &&(TAF_PH_MODE_LOWPOWER == pEvent->OperMode.PhMode))/*�жϵ�ǰ�ػ��¼������Ľ��*/
    {
        SPY_WARNING_LOG("Spy_RegPhoneCallback: TAF Return Error");

        g_enSpyCurState = SPY_STATE_NORMAL;
    }

    if((TAF_PH_MODE_FULL == pEvent->OperMode.PhMode)
        &&(SPY_STATE_PSOFF == g_enSpyCurState))/*�����ǰϵͳ�ǹػ�������Ϣ���ǿ����������û��ֶ�����*/
    {
        SPY_WARNING_LOG("Spy_RegPhoneCallback: User Open the PS when the PS State is TAF_PH_MODE_FULL");

        g_enSpyCurState = SPY_STATE_NORMAL;
    }

    return;
}

#endif  /*defined(VERSION_V7R1_C010)*/

/*****************************************************************************
 �� �� ��  : Spy_SendAtTempProtectMsg
 ��������  : ��AT�������±�״̬�仯ָʾ��Ϣ
 �������  : ulTempProtectEvent -- �¶ȱ���״̬�仯�¼�
             ulTempProtectParam -- Ԥ���Ա���չ
 �������  : ��
 �� �� ֵ  : VOS_OK
             VOS_ERR
 �޸���ʷ  :
*****************************************************************************/
VOS_UINT32 Spy_SendAtTempProtectMsg(VOS_UINT32 ulTempProtectEvent, VOS_UINT32 ulTempProtectParam)
{
    VOS_UINT32                       ulTempState;
    TEMP_PROTECT_EVENT_AT_IND_STRU  *pstSpyMsg;

#if (RAT_MODE != RAT_GU)
    pstSpyMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU *)VOS_AllocMsg(WUEPS_PID_SPY,
                sizeof(TEMP_PROTECT_EVENT_AT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSpyMsg)
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg: alloc normal msg Return Null");

        return VOS_ERR;
    }

    pstSpyMsg->ulReceiverPid        = WUEPS_PID_AT;
    pstSpyMsg->ulMsgId              = ID_TEMPPRT_AT_EVENT_IND;
    pstSpyMsg->ulTempProtectEvent   = ulTempProtectEvent;
    pstSpyMsg->ulTempProtectParam   = ulTempProtectParam;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SPY, pstSpyMsg))
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg: send normal Return Failed");

        return VOS_ERR;
    }
#endif

    if ( SPY_STATE_NORMAL == ulTempProtectEvent )
    {
        ulTempState = SPY_TEMPROTECT_SWITCH_OFF;
    }
    else
    {
        ulTempState = SPY_TEMPROTECT_SWITCH_ON;
    }

    if ( ulTempState == g_ulSpySwitchState )
    {
        SPY_INFO_LOG("Spy_SendAtTempProtectMsg: No Action");

        return VOS_OK;
    }

    g_ulSpySwitchState = ulTempState;

    pstSpyMsg = (TEMP_PROTECT_EVENT_AT_IND_STRU *)VOS_AllocMsg(WUEPS_PID_SPY,
                sizeof(TEMP_PROTECT_EVENT_AT_IND_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstSpyMsg)
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg:  alloc switch msg Return Null");

        return VOS_ERR;
    }

    pstSpyMsg->ulReceiverPid        = WUEPS_PID_AT;
    pstSpyMsg->ulMsgId              = ID_TEMPPRT_STATUS_AT_EVENT_IND;
    pstSpyMsg->ulTempProtectEvent   = ulTempState;
    pstSpyMsg->ulTempProtectParam   = ulTempProtectParam;

    if (VOS_OK != VOS_SendMsg(WUEPS_PID_SPY, pstSpyMsg))
    {
        SPY_ERROR_LOG("Spy_SendAtTempProtectMsg: send switch Return Failed");

        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_VOID Spy_CountInit(VOS_UINT16 usState)
{
    if (0 != (usState & TEMP_CLOSE_ITEM))
    {
        g_stTempStateCtrl.ulTempCloseCount = TEMP_CLOSE_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Close Count");
    }

    if (0 != (usState & TEMP_ALARM_ITEM))
    {
        g_stTempStateCtrl.ulTempAlarmCount = TEMP_ALARM_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Alarm Count");
    }

    if (0 != (usState & TEMP_RESUME_ITEM))
    {
        g_stTempStateCtrl.ulTempResumeCount = TEMP_RESUME_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Resume Count");
    }

    if (0 != (usState & TEMP_POWEROFF_ITEM))
    {
        g_stTempStateCtrl.ulTempPowerOffCount = TEMP_POWEROFF_ADC_COUNT;

        SPY_NORMAL_LOG("Spy_CountInit: Clean the Temp Power Off Count");
    }

    return;
}


VOS_UINT32 Spy_TempCheckInit(VOS_VOID)
{
    g_stTempStateCtrl.enTempEnable = TEMP_CLOSE_STATE;

    /*��ȡ�ȱ�������ֵ��NV��*/
    if(NV_OK != NV_Read(en_NV_Item_USIM_TEMP_PROTECT_NEW,
                            (VOS_VOID*)&g_stTempProtectNv,
                            sizeof(SPY_TEMP_PROTECT_NV_STRU)))
    {

        SPY_ERROR_LOG("Spy_TempCheckInit: NV_Read en_NV_Item_USIM_TEMP_PROTECT!");

        return VOS_ERR;
    }

    g_stTempStateCtrl.lOldTemperature = 0;

    /*��ʼ���¶ȱ������Ʊ���*/
    g_stTempStateCtrl.enTempEnable      = g_stTempProtectNv.ulIsEnable;

    g_stTempStateCtrl.enTempState       = TEMP_NORMAL_STATE;

    g_stTempStateCtrl.ulTempCloseCount  = TEMP_CLOSE_ADC_COUNT;

    g_stTempStateCtrl.ulTempAlarmCount  = TEMP_ALARM_ADC_COUNT;

    g_stTempStateCtrl.ulTempPowerOffCount   = TEMP_POWEROFF_ADC_COUNT;

    g_stTempStateCtrl.ulTempResumeCount = TEMP_RESUME_ADC_COUNT;

    g_stTempStateCtrl.ulTempWaitTimeLen = TEMP_CLOSE_TIMER_LEN;

    g_stTempStateCtrl.ulBatteryTempAlarmCount = 0;

    return VOS_OK;
}


VOS_UINT32 Spy_TempProtectInit(VOS_VOID)
{
    VOS_INT16                           sTemp;

    g_enSpyCurState = SPY_STATE_NORMAL;

#ifdef SPY_STATISTICS_DEBUG
    /*lint -e534*/
    VOS_MemSet(&g_stSpyStatisticsInfo, 0, sizeof(SPY_STATISTICS_INFO_STRU));
    VOS_MemSet(&g_stSpyTimeRecord, 0, sizeof(SPY_RECORD_STRU));
    /*lint +e534*/
#endif

    if(VOS_OK != Spy_TempCheckInit())
    {
        SPY_ERROR_LOG("Spy_TempProtectInit: Spy_TempCheckInit Failed!");

        return VOS_ERR;
    }

    if(TEMP_ENABLE_STATE == g_stTempStateCtrl.enTempEnable)
    {
        /*��ȡ��ǰ�¶�ֵ*/
        if(VOS_OK !=  mdrv_hkadc_get_temp((HKADC_TEMP_PROTECT_E)(g_stTempProtectNv.ulLocation),
                                          VOS_NULL_PTR, &sTemp, HKADC_CONV_DELAY))
        {
            SPY_WARNING_LOG("Spy_TempProtectInit: The Drv Interface Return Failed!");

            return VOS_ERR;
        }

        g_stTempStateCtrl.lOldTemperature   = sTemp;

        if(VOS_OK != VOS_StartRelTimer(&g_stSpyTempProtect_Timer, WUEPS_PID_SPY,
                                    SPY_TIMER_LEN, 1, 0, VOS_RELTIMER_NOLOOP,VOS_TIMER_NO_PRECISION))
        {
            SPY_ERROR_LOG("Spy_TempProtectInit: Start The Check Timer Failed!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}
VOS_INT32 Spy_CheckTemp(VOS_VOID)
{
    VOS_INT16               sTemp;
    VOS_INT                 lSimTemp = 0;

    /* ���������ڼ䲻�����¶ȱ���,��������±��Ѿ���ʼ�ˣ���ô�����ǽ������� */
    if ( (SPY_STATE_NORMAL == g_enSpyCurState) && (TAF_OAM_EMERGENCY_CALL_START == g_ucSpyEmergencyCallState) )
    {
        return SPY_VOTE_NOMAL;
    }

    /*�¶ȼ��û������ ���� ��ǰ����FTģʽ��*/
    if ((TEMP_CLOSE_STATE == g_stTempStateCtrl.enTempEnable)
        || (TAF_PH_MODE_FT == g_stSysCurStatus.ulCurPSStatus))
    {
        SPY_NORMAL_LOG("Spy_CheckTemp: The Tempture Check is Disable");

        return SPY_VOTE_NOMAL;
    }

    if (VOS_OK != mdrv_hkadc_get_temp((HKADC_TEMP_PROTECT_E)(g_stTempProtectNv.ulLocation),
                                      VOS_NULL_PTR, &sTemp, HKADC_CONV_DELAY))
    {
        SPY_WARNING_LOG("Spy_CheckTemp: The Drv Interface Return Failed");

        return SPY_VOTE_NOMAL;
    }

    lSimTemp    = sTemp;

    /*�ж������¶Ȳ��Ƿ񳬱�*/
    if (SPY_TEMP_MAX_INTERVAL < GET_TEMP_INTERVAL(g_stTempStateCtrl.lOldTemperature, lSimTemp))
    {
        g_stTempStateCtrl.lOldTemperature = lSimTemp;

        SPY_NORMAL1_LOG("Spy_CheckTemp: The Tempture is Too Larger then Old.", lSimTemp);

        return SPY_VOTE_NOMAL;
    }

    SPY_INFO1_LOG("Spy_CheckTemp: SIM temperature is %d", lSimTemp);

    g_stTempStateCtrl.lOldTemperature = lSimTemp;

    if (lSimTemp >= TEMP_POWEROFF_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempPowerOffCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Higher then Power Off Level, %d", lSimTemp);

        if(0 == g_stTempStateCtrl.ulTempPowerOffCount)
        {
            Spy_CountInit(TEMP_ALL_ITEM);

            g_stTempStateCtrl.enTempState = TEMP_WAIT_STATE;

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the Power Off");

            return SPY_VOTE_POWEROFF;
        }
    }
    else
    {
        Spy_CountInit(TEMP_POWEROFF_ITEM);
    }

    /*�ж��Ƿ񳬹�ʵʩ�ػ�������*/
    if (lSimTemp >= TEMP_CLOSE_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempCloseCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Higher then PS Off Level, %d", lSimTemp);

        if (0 == g_stTempStateCtrl.ulTempCloseCount)
        {
            /*������ػ������������뵽�͹���״̬*/
            Spy_CountInit(TEMP_ALL_ITEM);

            g_stTempStateCtrl.enTempState = TEMP_WAIT_STATE;

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the soft down");

            return SPY_VOTE_SOFTDOWN;
        }
    }
    else
    {
        Spy_CountInit(TEMP_CLOSE_ITEM);
    }

    /*�ж��Ƿ񳬹��������޵�����*/
    if (lSimTemp >= TEMP_ALARM_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempAlarmCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Higher then Warning Level, %d", lSimTemp);

        /*SIM���¶ȳ����������������뱨��״̬*/
        if (0 == g_stTempStateCtrl.ulTempAlarmCount)
        {
            Spy_CountInit(TEMP_ALL_ITEM);

            g_stTempStateCtrl.enTempState = TEMP_WAIT_STATE;

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the Qos 384");

            return SPY_VOTE_QOSDOWN;
        }

        Spy_ReportEvent(SPY_EVENT_TEMP_OVER_HIGH, lSimTemp);
    }
    else
    {
        Spy_CountInit(TEMP_ALARM_ITEM);
    }

    /*�ж��Ƿ���ڻָ����޵�����*/
    if (lSimTemp <= TEMP_RESUME_THRESHOLD)
    {
        g_stTempStateCtrl.ulTempResumeCount--;

        SPY_WARNING1_LOG("Spy_CheckTemp: The Tempture is Lower then Resume Level, %d", lSimTemp);

        /*SIM���¶ȵ��ڻָ����ޣ����лָ�����*/
        if (0 == g_stTempStateCtrl.ulTempResumeCount)
        {
            Spy_CountInit(TEMP_ALL_ITEM);

            SPY_WARNING_LOG("Spy_CheckTemp: Vote the Resume");

            Spy_ReportEvent(SPY_EVENT_TEMP_RESUME, lSimTemp);

            return SPY_VOTE_RESUME;
        }
    }
    else
    {
        Spy_CountInit(TEMP_RESUME_ITEM);
    }

    return SPY_VOTE_NOMAL;
}
VOS_UINT32 Spy_VoteJudgeState(VOS_INT32 lVote)
{
    SPY_STATE_ENUM_UINT32       enState     = SPY_STATE_NORMAL;
    SPY_VOTERESULT_ENUM_UINT32  enVoteResult= SPY_VOTERESULT_NULL;

    switch(lVote)
    {
        case SPY_VOTE_POWEROFF:/*��ǰ��ͶƱ����ǹػ�*/
            enVoteResult    = SPY_VOTERESULT_POWEROFF;
            SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Power OFF");
            break;

        case SPY_VOTE_SOFTDOWN :
            if(TAF_PH_MODE_FULL == g_stSysCurStatus.ulCurPSStatus)/*��ǰ����״̬����������¿��Թػ�*/
            {
                enState         = SPY_STATE_PSOFF;  /*���µ�ǰϵͳ״̬*/
                enVoteResult    = SPY_VOTERESULT_PSOFF;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Soft Down");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_PSOFF, 0);
                /*lint +e534*/
            }
            else /*������������ػ������¶ȱ���ģ���л�������״̬*/
            {
                enState = g_enSpyCurState;
                g_stTempStateCtrl.enTempState = TEMP_NORMAL_STATE;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Current PS Status is not TAF_PH_MODE_FULL");
            }
            break;

        case SPY_VOTE_QOSDOWN: /*��ǰ��ͶƱ����ǵ���QOS 384*/
            if (SPY_STATE_NORMAL == g_enSpyCurState)
            {
                enState = SPY_STATE_QOS;
                enVoteResult    = SPY_VOTERESULT_DOWNQOS;  /*���µ�ǰϵͳ״̬*/
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is QOS DOWN");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_QOS, 0);
                /*lint +e534*/
            }
            else
            {
                enState = g_enSpyCurState;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is NULL");
            }
            break;

        case SPY_VOTE_RESUME:   /*��ǰ��Ҫ�ָ�*/
            if(SPY_STATE_QOS == g_enSpyCurState)/*��ǰϵͳ״̬�ڵ���QOS����ָܻ�*/
            {
                enVoteResult    = SPY_VOTERESULT_DEFQOS;
                enState         = SPY_STATE_NORMAL;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Resume Qos");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_NORMAL, 0);
                /*lint +e534*/
            }
            else if(TAF_PH_MODE_LOWPOWER == g_stSysCurStatus.ulCurPSStatus)/*��ǰ��ػ�״̬,������SPY������ػ�*/
            {
                enVoteResult    = SPY_VOTERESULT_PSON;  /*ϵͳ״̬�ǿ���*/
                enState         = SPY_STATE_NORMAL;
                SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is Turn On the PS");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_NORMAL, 0);
                /*lint +e534*/
            }
            else
            {
                SPY_WARNING_LOG("Spy_VoteJudgeState: The Current System do not Need Resume");
            }
            break;

        default:
            SPY_NORMAL_LOG("Spy_VoteJudgeState: The Vote is NULL");
            return SPY_VOTERESULT_NULL;
    }

    g_enSpyCurState = enState;

    return enVoteResult;
}


VOS_UINT32 Spy_PowerDown(VOS_VOID)
{
    OAM_MNTN_SPY_ERROR_EVENT_STRU       stSpyErrorLog;

    /* ��Errorlog�ļ��м�¼�¼� */
    if(VOS_OK != MNTN_RecordErrorLog(MNTN_SPY_PWOER_DOWN_EVENT, (void *)&stSpyErrorLog,
                                            sizeof(OAM_MNTN_SPY_ERROR_EVENT_STRU)))
    {
        SPY_ERROR_LOG("Spy_PowerDown: Fail to record Power Down event in Errorlog file");
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Power Down");
    g_stSpyStatisticsInfo.ulPowerOffNum++;
#endif

    /*lint -e534*/
    vos_printf("\r\nSpy_PowerDown SHUT DOWN\r\n");
    /*lint +e534*/

    /* ��ǰ�汾�ֻ���̬Modem���ڿ��Ƶ����µ磬��ģ���MBB��Ʒ��̬����ӿ�ֻ�ܸ�λ���岻���ṩ�µ�
       ���������ﲻ�ٵ��õ����µ�ӿڣ�ֱ��ʹ��CCPU������λ�ӿ���Ϊ�ػ����� */
    VOS_ProtectionReboot(SPY_FLOWCTRL_POWEROFF, VOS_FILE_ID, __LINE__, VOS_NULL, VOS_NULL_PTR);
    /*mdrv_sysboot_shutdown(DRV_SHUTDOWN_TEMPERATURE_PROTECT);*/ /*�����֧�ֵ��Ҳ���Ե��ýӿڣ������ڲ���׮*/

    return VOS_OK;
}
VOS_UINT32 Spy_SysCtrlCmd(VOS_UINT8 usOpId, VOS_UINT16 usClientId, VOS_UINT32 ulMode, MODEM_ID_ENUM_UINT16 enModemID)
{
    MN_APP_PHONE_MODE_SET_REQ_STRU *pstMsg;

    if(MODEM_ID_BUTT <= enModemID)
    {
        PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_ERROR, "OM_SysCtrlCmd: Modem ID Error!");

        return VOS_ERR;
    }

    pstMsg = (MN_APP_PHONE_MODE_SET_REQ_STRU*)VOS_AllocMsg(WUEPS_PID_SPY,
            sizeof(MN_APP_PHONE_MODE_SET_REQ_STRU) - VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pstMsg)
    {
        PS_LOG(WUEPS_PID_SPY, 0, PS_PRINT_ERROR, "OM_SysCtrlCmd: VOS_AllocMsg failed!");

        return VOS_ERR;
    }

    if(MODEM_ID_1 == enModemID)
    {
        pstMsg->ulReceiverPid      = I1_WUEPS_PID_MMA;
    }
    else
    {
        pstMsg->ulReceiverPid      = I0_WUEPS_PID_MMA;
    }

    pstMsg->ulMsgId            = OAM_MMA_PHONE_MODE_SET_REQ;

    /* ������Ϣ��NAS����ϵͳ���� */
    pstMsg->usClientId         = usClientId;
    pstMsg->opID               = usOpId;
    pstMsg->stPhOpMode.CmdType = TAF_PH_CMD_SET;
    pstMsg->stPhOpMode.PhMode  = (VOS_UINT8)ulMode;
    pstMsg->stPhOpMode.PhReset = TAF_PH_OP_MODE_UNRESET;

    return VOS_SendMsg(WUEPS_PID_SPY, pstMsg);
}
VOS_UINT32 Spy_SoftPowerOff(VOS_VOID)
{
#ifndef COMM_ITT
    OAM_MNTN_SPY_ERROR_EVENT_STRU       stSpyErrorLog;

    /*�ر�2���Ӷ�ʱ��*/
    if (VOS_NULL_PTR!= g_stSpyFlowCtrlTimer)
    {
        /*lint -e534*/
        (VOS_VOID)VOS_StopRelTimer(&g_stSpyFlowCtrlTimer);
        /*lint +e534*/
    }

    /* ��Errorlog�ļ��м�¼�¼� */
    if(VOS_OK != MNTN_RecordErrorLog(MNTN_SPY_SOFTOFF_EVENT, (void *)&stSpyErrorLog,
                                            sizeof(OAM_MNTN_SPY_ERROR_EVENT_STRU)))
    {
        SPY_ERROR_LOG("Spy_SoftPowerOff: Fail to Write Soft Off event in Errorlog file");
    }

    /* �ָ�����*/
    if (VOS_NULL_PTR != g_pfunRegRestoreProc)
    {
        g_pfunRegRestoreProc();
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Soft Power Off");
    g_stSpyStatisticsInfo.ulSoftPowerOffNum++;
#endif
    /*lint -e534*/
    Spy_SysCtrlCmd(VOS_NULL, OAM_CLIENT_ID_SPY, TAF_PH_MODE_LOWPOWER, MODEM_ID_0);
    /*lint +e534*/
#endif

    return VOS_OK;
}
VOS_UINT32 Spy_SoftPowerOn(VOS_VOID)
{
#ifndef COMM_ITT

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Soft Power On");
    g_stSpyStatisticsInfo.ulSoftPowerOnNum++;
#endif
    /*lint -e534*/
    Spy_SysCtrlCmd(VOS_NULL, OAM_CLIENT_ID_SPY, TAF_PH_MODE_FULL, MODEM_ID_0);
    /*lint +e534*/
#endif

    return VOS_OK;
}


VOS_UINT32 Spy_FlowCtrlDown()
{
    /*call L2*/
    SPY_NORMAL_LOG("Spy_FlowCtrlDown: Down Flow Control Start.");

    if (VOS_NULL_PTR != g_stSpyFlowCtrlTimer)
    {
        /*lint -e534*/
        (VOS_VOID)VOS_StopRelTimer(&g_stSpyFlowCtrlTimer);
        /*lint +e534*/
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Flow Ctrl Down");
    g_stSpyStatisticsInfo.ulFlowCtrlDownNum++;
#endif

    if (VOS_NULL_PTR != g_pfunRegDowngradeProc)
    {
        /* �������δ��ɣ�����Ҫ������2���Ӷ�ʱ��*/
        if (SPY_DATA_DOWNGRADE_CONTINUE == g_pfunRegDowngradeProc())
        {
            /*����2���Ӷ�ʱ��*/
            if (VOS_OK != VOS_StartRelTimer(&g_stSpyFlowCtrlTimer, WUEPS_PID_SPY,
                 SPY_FLOW_CTRL_TIMER_LEN,TIMER_FLOWCTRL,0,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
            {
                SPY_ERROR_LOG("Spy_FlowCtrlDown:Start The Check Timer Failed!");
            }
        }
    }

    return VOS_OK;
}
VOS_UINT32 Spy_FlowCtrlUp()
{
    /*call L2*/
    SPY_NORMAL_LOG("Spy_FlowCtrlUp: Up Flow Control Start.");

    if (VOS_NULL_PTR!= g_stSpyFlowCtrlTimer)
    {
        /*lint -e534*/
        (VOS_VOID)VOS_StopRelTimer(&g_stSpyFlowCtrlTimer);
        /*lint +e534*/
    }

#ifdef SPY_STATISTICS_DEBUG
    Spy_TimeRecord("Flow Ctrl Up");
    g_stSpyStatisticsInfo.ulFlowCtrlUpNum++;
#endif

    if (VOS_NULL_PTR != g_pfunRegDowngradeProc)
    {
        /* �������δ��ɣ�����Ҫ������2���Ӷ�ʱ��*/
        if (SPY_DATA_UPGRADE_CONTINUE == g_pfunRegUpgradeProc())
        {
            /*����2���Ӷ�ʱ��*/
            if (VOS_OK != VOS_StartRelTimer(&g_stSpyFlowCtrlTimer, WUEPS_PID_SPY,
                SPY_FLOW_CTRL_TIMER_LEN,TIMER_FLOWCTRL,0,VOS_RELTIMER_NOLOOP, VOS_TIMER_NO_PRECISION))
            {
                SPY_ERROR_LOG("Spy_FlowCtrlUp:Start The Check Timer Failed!");
            }
        }
    }

    return VOS_OK;
}
VOS_UINT32 Spy_Execute(VOS_UINT32 ulVoteResult)
{
    VOS_UINT32  ulResult = VOS_ERR;

    switch(ulVoteResult)
    {
        case SPY_VOTERESULT_DEFQOS:
            SPY_NORMAL_LOG("Spy_Execute: Need Resume the User Default Qos Value");

            ulResult = Spy_FlowCtrlUp();
            break;

        case SPY_VOTERESULT_PSON:
            SPY_NORMAL_LOG("Spy_Execute: Need Re Start the PS");
            ulResult = Spy_SoftPowerOn();
            break;

        case SPY_VOTERESULT_DOWNQOS:
            SPY_NORMAL_LOG("Spy_Execute: Need Limit To the Qos");

            ulResult = Spy_FlowCtrlDown();
            break;

        case SPY_VOTERESULT_PSOFF:
            SPY_NORMAL_LOG("Spy_Execute: Need Power off the PS");
            ulResult = Spy_SoftPowerOff();
            break;

        case SPY_VOTERESULT_POWEROFF:
            SPY_NORMAL_LOG("Spy_Execute: Need Power off the Platform");
            ulResult = Spy_PowerDown();
            break;

        default:
            SPY_WARNING_LOG("Spy_Execute: The Vote is NULL");
            break;
    }

    if(VOS_ERR == ulResult)
    {
        SPY_WARNING1_LOG("Spy_Execute: Excute the Vote %d is Failed",
            (VOS_INT32)ulVoteResult);
    }

    return ulResult;
}


VOS_VOID Spy_MainProc(VOS_VOID)
{
    VOS_INT32  lTempVote;
    VOS_UINT32 ulVoteResult = SPY_VOTERESULT_NULL;
    VOS_UINT32 ulResult     = VOS_OK;
    VOS_UINT32 ulTimeLen    = SPY_TIMER_LEN;
    VOS_UINT32 ulPrecision  = VOS_TIMER_NO_PRECISION;

    lTempVote = Spy_CheckTemp();/*��ȡ�¶ȼ�ص�ͶƱ*/

    if (SPY_VOTE_NOMAL != lTempVote)
    {
        Spy_ReportEvent(SPY_EVENT_VOTE_RESULT, (VOS_INT)lTempVote);

        ulVoteResult = Spy_VoteJudgeState(lTempVote);    /*��Ҫ���ݵ�ǰ��ͶƱ���ȷ��ϵͳ״̬ת��*/

        if(SPY_VOTERESULT_NULL != ulVoteResult)
        {
            ulTimeLen = TEMP_CLOSE_TIMER_LEN * SPY_TIMER_LEN;

            ulResult = Spy_Execute(ulVoteResult);

            if(VOS_OK != ulResult) /*����ͶƱ�������*/
            {
                SPY_ERROR1_LOG(
                    "Spy_MainProc:Spy_Execute return result is  Failed!,Current State is %d", (VOS_INT32)g_enSpyCurState);

                ulTimeLen    = SPY_TIMER_LEN;
            }
        }
    }

    /* �±���ػ��󣬶�ʱ��������Ҫ�޸�Ϊ32K��ʱ��,ȷ��CCPU�µ���Ȼ���Խ����¶ȼ�� */
    if (SPY_STATE_PSOFF == g_enSpyCurState)
    {
        ulPrecision = VOS_TIMER_PRECISION_5;
    }

    if(VOS_OK != VOS_StartRelTimer(&g_stSpyTempProtect_Timer, WUEPS_PID_SPY,
                                ulTimeLen,1,0,VOS_RELTIMER_NOLOOP, ulPrecision))
    {
        SPY_ERROR_LOG("Spy_MainProc:Start The Check Timer Failed!");
    }

    return;
}


VOS_VOID Spy_E5_CheckSIMTemp(VOS_VOID)
{
    VOS_UINT32                  ulResult;
    VOS_INT16                   sTemp;
    VOS_INT                     lSimTemp = 0;

    if(BSP_MODULE_UNSUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_CHARGE))   /*��ǰ��֧�ֵ��*/
    {
        return ;
    }

    /*ͨ������ӿڻ�ȡ��ǰSIM���¶�*/
    ulResult = (VOS_UINT32)mdrv_hkadc_get_temp(HKADC_TEMP_SIM_CARD, VOS_NULL_PTR, &sTemp, HKADC_CONV_DELAY);

    if(VOS_OK != ulResult)
    {
        SPY_ERROR_LOG("Spy_E5_CheckSIMTemp: DRV_GET_SIM_TEMP Failed");

        return;
    }

    lSimTemp    = sTemp;

    if(lSimTemp >= TEMP_SIM_POWEROFF_THRESHOLD)
    {
        /*lint -e534*/
        vos_printf("\r\nSpy_E5_CheckSIMTemp SHUT DOWN, SIM Temperature is %d\r\n", lSimTemp);
        /*lint +e534*/
        mdrv_sysboot_shutdown(DRV_SHUTDOWN_TEMPERATURE_PROTECT);
    }

    return;
}


VOS_UINT32 Spy_ReadTempMsgProc(MsgBlock *pMsg)
{
    /* ����һ���պ����Է������ٴη����仯 */
    return VOS_OK;
}
VOS_VOID Spy_TempProtectMsgProc(MsgBlock *pstMsg)
{
    REL_TIMER_MSG                           *pstExpireMsg;
    TAF_OAM_EMERGENCY_CALL_STATUS_STRU      *pstTafEmergencyMsg;

    if(VOS_PID_TIMER == pstMsg->ulSenderPid)
    {
        pstExpireMsg                = (REL_TIMER_MSG*)pstMsg;

        if (TIMER_FLOWCTRL == pstExpireMsg->ulName)
        {
            /*2���Ӷ�ʱ�µ�����*/
            if(SPY_STATE_QOS == g_enSpyCurState)
            {
                /*lint -e534*/
                Spy_FlowCtrlDown();
                /*lint +e534*/
            }

            /*2���Ӷ�ʱ�ϵ�����*/
            if(SPY_STATE_NORMAL == g_enSpyCurState)
            {
                /*lint -e534*/
                Spy_FlowCtrlUp();
                /*lint +e534*/
            }
        }
        else
        {
            Spy_E5_CheckSIMTemp();

            g_stSysCurStatus.ulCurPSStatus = MMA_GetCurrentPhoneMode();

            /* ����±���ػ�ʧ�ܻ��û��ֶ������������±�״̬ */
            if ((TAF_PH_MODE_FULL == g_stSysCurStatus.ulCurPSStatus)&&(SPY_STATE_PSOFF == g_enSpyCurState))
            {
                g_enSpyCurState = SPY_STATE_NORMAL;

                SPY_NORMAL_LOG("Spy_TempProtectMsgProc: SPY state change from softoff to normal");

                /*lint -e534*/
                Spy_SendAtTempProtectMsg(SPY_STATE_NORMAL, 0);
                /*lint +e534*/
            }

            Spy_MainProc();
        }
    }
    else if(WUEPS_PID_TAF == pstMsg->ulSenderPid)
    {
        pstTafEmergencyMsg = (TAF_OAM_EMERGENCY_CALL_STATUS_STRU *)pstMsg;

        if ( TAF_OAM_EMERGENCY_CALL_STATUS_NOTIFY != pstTafEmergencyMsg->ulMsgId )
        {
            return;
        }

        if ( TAF_OAM_EMERGENCY_CALL_STATUS_BUTT == pstTafEmergencyMsg->enEmergencyCallStatus )
        {
            return;
        }

        g_ucSpyEmergencyCallState = pstTafEmergencyMsg->enEmergencyCallStatus;
    }
    else
    {
        SPY_WARNING1_LOG("Spy_TempProtectMsgProc: Receive Unkown Msg, Send PID is %d",(VOS_INT32)pstMsg->ulSenderPid);
    }

    return;
}
VOS_UINT32 Spy_FID_Init(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32 ulResult = VOS_OK;

    switch (ip)
    {
        case VOS_IP_LOAD_CONFIG:
            ulResult = VOS_RegisterTaskPrio(WUEPS_FID_SPY, COMM_SPY_TASK_PRIO);

            if (ulResult != VOS_OK)
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterTaskPrio Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_SPY,
                                            VOS_NULL_PTR,
                                            (Msg_Fun_Type)Spy_TempProtectMsgProc);

            if (ulResult != VOS_OK)
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterPIDInfo WUEPS_PID_SPY Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_MONITOR,
                                            VOS_NULL_PTR,
                                            (Msg_Fun_Type)Spy_ReadTempMsgProc);

            if( VOS_OK != ulResult )
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterPIDInfo WUEPS_PID_MONITOR Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            ulResult = VOS_RegisterPIDInfo(WUEPS_PID_SAR,
                                            VOS_NULL_PTR,
                                            (Msg_Fun_Type)Spy_SarMsgProc);

            if( VOS_OK != ulResult )
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: VOS_RegisterPIDInfo WUEPS_PID_SAR Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }
            break;

        case VOS_IP_INITIAL:

            /*DRV_USB_STATUS_CALLBACK_REGI(Spy_UsbStatusProc);*/
            Spy_AntenStatusInit();

            ulResult = Spy_TempProtectInit();

            if (ulResult != VOS_OK)
            {
                /*lint -e534*/
                LogPrint("Spy_FID_Init: Spy_TempProtectInit Failed!");
                /*lint +e534*/
                return VOS_ERR;
            }

            break;

        default:
            break;
    }

    return ulResult;

}
VOS_UINT32 Spy_SetTempPara(SPY_TEMP_THRESHOLD_PARA_STRU *stTempPara)
{
    SPY_TEMP_PROTECT_NV_STRU stTempProtectNv;
    VOS_UINT32               ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_UNCHANGE;

    if(VOS_NULL_PTR == stTempPara)
    {
        SPY_ERROR_LOG("Spy_SetTempPara: Input VOS_NULL_PTR");

        return VOS_ERR;
    }

    /*��ȡ�ȱ�������ֵ��NV��*/
    if(NV_OK != NV_Read(en_NV_Item_USIM_TEMP_PROTECT_NEW,
                        (VOS_VOID*)&stTempProtectNv,
                        sizeof(SPY_TEMP_PROTECT_NV_STRU)))
    {
        SPY_ERROR_LOG("Spy_SetTempPara: NV_Read en_NV_Item_USIM_TEMP_PROTECT Fail!");

        return VOS_ERR;
    }

    /*�����������Ч������и�ֵ*/
    if((SPY_TEMP_THRESHOLD_PARA_INVALID != stTempPara->ulIsEnable)
        &&(stTempProtectNv.ulIsEnable != stTempPara->ulIsEnable))
    {
        stTempProtectNv.ulIsEnable = stTempPara->ulIsEnable;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if((SPY_TEMP_THRESHOLD_PARA_INVALID != (VOS_UINT32)stTempPara->lCloseAdcThreshold)
        &&(stTempProtectNv.lCloseAdcThreshold != stTempPara->lCloseAdcThreshold))
    {
        stTempProtectNv.lCloseAdcThreshold = stTempPara->lCloseAdcThreshold;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if((SPY_TEMP_THRESHOLD_PARA_INVALID != (VOS_UINT32)stTempPara->lAlarmAdcThreshold)
        &&(stTempProtectNv.lAlarmAdcThreshold != stTempPara->lAlarmAdcThreshold))
    {
        stTempProtectNv.lAlarmAdcThreshold = stTempPara->lAlarmAdcThreshold;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    if((SPY_TEMP_THRESHOLD_PARA_INVALID != (VOS_UINT32)stTempPara->lResumeAdcThreshold)
        &&(stTempProtectNv.lResumeAdcThreshold != stTempPara->lResumeAdcThreshold))
    {
        stTempProtectNv.lResumeAdcThreshold = stTempPara->lResumeAdcThreshold;
        ulChangeFlag = SPY_TEMP_THRESHOLD_PARA_CHANGE;
    }

    /*�ж�ȡֵ�Ϸ���*/
    if((stTempProtectNv.lAlarmAdcThreshold >= stTempProtectNv.lCloseAdcThreshold)
       ||(stTempProtectNv.lResumeAdcThreshold >= stTempProtectNv.lAlarmAdcThreshold))
    {
        SPY_ERROR_LOG("Spy_SetTempPara: NV Value Error!");

        return VOS_ERR;
    }

    /*����û���������ԭ�ȵ�����ֵ��ͬ��д��NV��*/
    if(SPY_TEMP_THRESHOLD_PARA_CHANGE == ulChangeFlag)
    {
        if (NV_OK != NV_Write(en_NV_Item_USIM_TEMP_PROTECT_NEW,
                             (VOS_VOID*)&stTempProtectNv,
                             sizeof(SPY_TEMP_PROTECT_NV_STRU)))
        {
            SPY_ERROR_LOG("Spy_SetTempPara: NV_Write en_NV_Item_USIM_TEMP_PROTECT Fail!");

            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_VOID Spy_DownGradeRegister(SPY_DOWNGRADE_PROC_FUNC pFnDowngradeProcFunc)
{
    if (VOS_NULL_PTR ==  pFnDowngradeProcFunc)
    {
        SPY_ERROR_LOG("Spy_DownGradeRegister: Input VOS_NULL_PTR");
        return;
    }

    g_pfunRegDowngradeProc = pFnDowngradeProcFunc;

    if (SPY_STATE_QOS == g_enSpyCurState)
    {
        /*lint -e534*/
        Spy_FlowCtrlDown();
        /*lint +e534*/
    }

    return;
}


VOS_VOID Spy_UpGradeRegister(SPY_UPGRADE_PROC_FUNC pFnUpgradeProcFunc)
{
    if (VOS_NULL_PTR ==  pFnUpgradeProcFunc)
    {
        SPY_ERROR_LOG("Spy_UpGradeRegister: Input VOS_NULL_PTR");
        return;
    }

    g_pfunRegUpgradeProc = pFnUpgradeProcFunc;

    if (SPY_STATE_NORMAL == g_enSpyCurState)
    {
        /*lint -e534*/
        Spy_FlowCtrlUp();
        /*lint +e534*/
    }
    return;
}


VOS_VOID Spy_RestoreRegister(SPY_RESTORE_PROC_FUNC pFnRestoreProcFunc)
{
    if (VOS_NULL_PTR ==  pFnRestoreProcFunc)
    {
        SPY_ERROR_LOG("Spy_RestoreRegister: Input VOS_NULL_PTR");
        return;
    }

    g_pfunRegRestoreProc = pFnRestoreProcFunc;

    return;
}

#ifdef SPY_STATISTICS_DEBUG

VOS_VOID  Spy_ShowCmdHelp(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("\r\n");
    vos_printf("********************** SPY COMMAND HELP *********************\r\n");
    vos_printf(" Spy_ShowSpyStat [1]\r\n");
    vos_printf(" Spy_ShowSysStat \r\n");
    vos_printf(" Spy_ShowNvItem \r\n");
    vos_printf(" Spy_ShowHkadcTable \r\n");
    vos_printf(" Spy_ShowMonitorStat \r\n");

    vos_printf("*******************************************************************\r\n");
    vos_printf("\r\n");
    /*lint +e534*/

    return;
}


VOS_VOID Spy_ShowSpyStat(VOS_UINT32 ulIndex)
{
    VOS_UINT32 i;

    /*lint -e534*/
    vos_printf("Spy current state:      0x%x\r\n",g_enSpyCurState);
    vos_printf("Spy enable flag:        0x%x\r\n",g_stTempStateCtrl.enTempEnable);
    vos_printf("PowerOff count:         %d\r\n",g_stTempStateCtrl.ulTempPowerOffCount);
    vos_printf("Soft close count:       %d\r\n",g_stTempStateCtrl.ulTempCloseCount);
    vos_printf("Alarm count:            %d\r\n",g_stTempStateCtrl.ulTempAlarmCount);
    vos_printf("Resume count:           %d\r\n",g_stTempStateCtrl.ulTempResumeCount);
    vos_printf("Wait time:              %d\r\n",g_stTempStateCtrl.ulTempWaitTimeLen);
    vos_printf("Last temperature:       %d\r\n",g_stTempStateCtrl.lOldTemperature);

    vos_printf("\r\n");
    vos_printf("Spy timer info:\r\n");
    vos_printf("Spy temp protect timer: 0x%x\r\n",g_stSpyTempProtect_Timer);
    vos_printf("Spy flow ctrl timer:    0x%x\r\n",g_stSpyFlowCtrlTimer);

    vos_printf("\r\n");
    vos_printf("Spy statistics info:\r\n");
    vos_printf("Flow control down num:  %d\r\n",g_stSpyStatisticsInfo.ulFlowCtrlDownNum);
    vos_printf("Flow control up num:    %d\r\n",g_stSpyStatisticsInfo.ulFlowCtrlUpNum);
    vos_printf("Soft power off num:     %d\r\n",g_stSpyStatisticsInfo.ulSoftPowerOffNum);
    vos_printf("Soft power on num:      %d\r\n",g_stSpyStatisticsInfo.ulSoftPowerOnNum);
    vos_printf("Power off num:          %d\r\n",g_stSpyStatisticsInfo.ulPowerOffNum);
    /*lint +e534*/

    if (0 != ulIndex)
    {
        /*lint -e534*/
        vos_printf("\r\n");
        vos_printf("==========================================================\r\n");
        vos_printf("Time Record: count %d, current position %d\r\n",g_stSpyTimeRecord.ulCount,
            ((0==g_stSpyTimeRecord.ulCount) ? 0 : ((g_stSpyTimeRecord.ulCount-1)%SPY_RECORD_NUM)));
        vos_printf("Num      Type                 Time\r\n");
        /*lint +e534*/
        for (i=0; i<((g_stSpyTimeRecord.ulCount<SPY_RECORD_NUM) ? (g_stSpyTimeRecord.ulCount) : SPY_RECORD_NUM); i++)
        {
            /*lint -e534*/
            vos_printf("%3d    %-16s  %10d\r\n",i,g_stSpyTimeRecord.astRecord[i].acType,g_stSpyTimeRecord.astRecord[i].ulTime);
            /*lint +e534*/
        }
    }
}


VOS_VOID Spy_ShowSysStat(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("PDP status:          0x%x\r\n",g_stSysCurStatus.ulCurPSStatus);
    /*lint +e534*/
}


VOS_VOID Spy_ShowNvItem(VOS_VOID)
{
    /*lint -e534*/
    vos_printf("SPY NV item:\r\n");
    vos_printf("Spy enable flag:        0x%x\r\n",g_stTempProtectNv.ulIsEnable);
    vos_printf("Spy Location:           0x%x\r\n",g_stTempProtectNv.ulLocation);
    vos_printf("PowerOff threshold:     %d\r\n",g_stTempProtectNv.lPowerOffThreshold);
    vos_printf("Soft close threshold:   %d\r\n",g_stTempProtectNv.lCloseAdcThreshold);
    vos_printf("Alarm threshold:        %d\r\n",g_stTempProtectNv.lAlarmAdcThreshold);
    vos_printf("Resume threshold:       %d\r\n",g_stTempProtectNv.lResumeAdcThreshold);
    vos_printf("SIM PowerOff threshold: %d\r\n",g_stTempProtectNv.lSIMPowerOffThreshold);

    vos_printf("Alarm count:            %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempOverCount);
    vos_printf("Rusume count:           %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempRsumeCount);
    vos_printf("Soft close count:       %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempCloseCount);
    vos_printf("PowerOff count:         %d\r\n",g_stTempProtectNv.stTempCtrlPara.ucTempPowerOffCount);
    vos_printf("Wait time:              %d\r\n",g_stTempProtectNv.stTempCtrlPara.ulWaitTimer);

    vos_printf("\r\n");
    vos_printf("AntCtrl NV item:\r\n");
    /*lint +e534*/
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */




