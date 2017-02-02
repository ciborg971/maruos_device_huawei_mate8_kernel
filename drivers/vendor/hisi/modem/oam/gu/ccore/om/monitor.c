

#if 0

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define    THIS_FILE_ID        PS_FILE_ID_MONITOR_C


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if 0
MONITOR_USIM_ANT2_CTRL    g_stMonitorUsimAntCtrl;

MONITOR_PA_PARA_STRU      g_stMonitorPAPara = {MONITOR_DEFAULT_PA_TEMPERATURE,
                                               MONITOR_DEFAULT_BATTERY_VOLTAGE};/*PA�¶ȼ���ص�ѹ*/

VOS_UINT32                g_ulMonitorIndType = ID_PHY_MONITOR_NULL_IND; /*DSP�ϱ����ж�����*/

VOS_UINT32                g_ulMonitorConnectState = MONITOR_IDLE_STATE; /*Ŀǰ������״̬*/

VOS_UINT32                g_ulMonitorCtrlSem = VOS_NULL_PTR;  /* Monitor�����ź��� */

VOS_UINT32                g_ulMonitorErrCode = MONITOR_ERR_CODE_NONE;/* Monitorģ�������*/

HTIMER                    g_hQueryTimer = VOS_NULL_PTR; /*Monitor��ʱ��*/

VOS_UINT32                g_ulPHYSimTempFlag = MONITOR_SIM_TEMP_LOW_FLAG; /*�طּ����¼��ǰ�������¶�����*/

VOS_INT32                 g_lSimTempBuf[MONITOR_SIM_TEMP_BUF_LEN];

VOS_UINT32                g_ulSimTempBufPointor = 0;

extern VOS_VOID GSleep_ProcPsWakeCmd(VOS_VOID);

extern VOS_VOID SLEEP_ForceAwake(VOS_VOID);

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_UINT32 Monitor_Init(VOS_VOID)
{

    /*��ȡ���طּ���USIM���¶�����*/
    if(NV_OK != NV_Read(en_NV_Item_W_USIM_TEMP_ANT2_CTRL,
                            (VOS_VOID*)&g_stMonitorUsimAntCtrl,
                            sizeof(MONITOR_USIM_ANT2_CTRL)))
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_NV;

        return VOS_ERR;
    }

    if (VOS_OK != VOS_SmCCreate("MONS", 0, VOS_SEMA4_FIFO, &(g_ulMonitorCtrlSem)))
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_SEM;

        return VOS_ERR;
    }

#if (VOS_VXWORKS == VOS_OS_VER)
    taskSpawn("MONITOR_TASK", 159, 0, 10240,(FUNCPTR)Monitor_QueryTask, 0, 0, 0, 0, 0, 0, 0, 0,0,0);
#endif

    return VOS_OK;
}
VOS_VOID Monitor_WakeUpDsp(VOS_UINT32  RAT_mode)
{
    if( SHPA_SYSTEM_GSM == RAT_mode )
    {
        GSleep_ProcPsWakeCmd();
    }
    else
    {
        SLEEP_ForceAwake();
    }

    return;
}


VOS_VOID Monitor_QueryPA(VOS_INT lSimTemp)
{
    VOS_INT     lPaTemperature  = MONITOR_DEFAULT_PA_TEMPERATURE;
    VOS_INT     lBatteryVoltage = MONITOR_DEFAULT_BATTERY_VOLTAGE;
    VOS_UINT32  RAT_mode;
    VOS_INT32   lResult = VOS_ERROR;
    VOS_UINT32  ulTempType = CPHY_TEMPERATURE_TYPE_NULL;
    VOS_INT32   lSimAverageTemp = 0;
    VOS_UINT32  i;

    RAT_mode =  SHPA_GetRateType();

    /* ���õ���ӿڣ���ȡ��ǰPA�¶� */
    if( SHPA_SYSTEM_GSM == RAT_mode )
    {
        lResult = DRV_GET_PA_GTEMP(&lPaTemperature, g_pusAdcTable);
    }
    else if( SHPA_SYSTEM_WCDMA == RAT_mode )
    {
        lResult = DRV_GET_PA_WTEMP(&lPaTemperature, g_pusAdcTable);
    }
    else
    {
        return;
    }

    if (VOS_OK != lResult)
    {
        /*lint -e534*/
        LogPrint1("\r\nMonitor_QueryPA:Query Tempareture:%d.!", lResult);
        /*lint +e534*/
        return;
    }


    /* ���浱ǰ�¶ȵ�ѭ������ */
    g_ulSimTempBufPointor = g_ulSimTempBufPointor%MONITOR_SIM_TEMP_BUF_LEN;

    g_lSimTempBuf[g_ulSimTempBufPointor] = lSimTemp;

    g_ulSimTempBufPointor++;


    /* ȡ�¶�ѭ������ƽ��ֵ */
    for(i = 0; i < MONITOR_SIM_TEMP_BUF_LEN; i++)
    {
        lSimAverageTemp += g_lSimTempBuf[i];

    }

    lSimAverageTemp = (lSimAverageTemp/MONITOR_SIM_TEMP_BUF_LEN);

    /*�ж��Ƿ���Ҫ��SIM���¶ȱ��������*/
    if((g_stMonitorUsimAntCtrl.sUsimHigh <= lSimAverageTemp)&&
       (MONITOR_SIM_TEMP_LOW_FLAG == g_ulPHYSimTempFlag))
    {

        g_ulPHYSimTempFlag = MONITOR_SIM_TEMP_HIGH_FLAG;

        ulTempType = CPHY_TEMPERATURE_TYPE_SIM;
    }
    else if((g_stMonitorUsimAntCtrl.sUsimLow > lSimAverageTemp)&&(MONITOR_SIM_TEMP_HIGH_FLAG == g_ulPHYSimTempFlag))
    {
        g_ulPHYSimTempFlag = MONITOR_SIM_TEMP_LOW_FLAG;

        ulTempType = CPHY_TEMPERATURE_TYPE_SIM;
    }
    else
    {
        /*do nothing*/
    }

    /* ����¶ȸı䳬������ֵOM_PA_TEMPERATURE_DIFF_LIMIT */
    if ((( lPaTemperature + MONITOR_PA_TEMPERATURE_DIFF_LIMIT ) < g_stMonitorPAPara.lPaTemperature )
        || (( g_stMonitorPAPara.lPaTemperature + MONITOR_PA_TEMPERATURE_DIFF_LIMIT ) < lPaTemperature ))
    {
        g_stMonitorPAPara.lPaTemperature = lPaTemperature;

        ulTempType |= CPHY_TEMPERATURE_TYPE_PA;
    }


    if(CPHY_TEMPERATURE_TYPE_NULL != ulTempType)
    {
        Monitor_WakeUpDsp(RAT_mode);

        /* ���¶���Ϣ���͸�DSP*/
        Shpa_ProcTemperatureReq(GGPHY_MONITOR_TEMP_REQ, (VOS_INT16)lPaTemperature,
                                (VOS_INT16)lSimAverageTemp,ulTempType);
    }

    /* ���õ���ӿڣ���ȡ��ǰ��ص�ѹ */

    /* �����ѹ�ı䳬������ֵOM_BATTERY_VOLTAGE_DIFF_LIMIT */
    if ((( lBatteryVoltage + MONITOR_BATTERY_VOLTAGE_DIFF_LIMIT ) < g_stMonitorPAPara.lBatteryVoltage )
        || (( g_stMonitorPAPara.lBatteryVoltage + MONITOR_BATTERY_VOLTAGE_DIFF_LIMIT ) < lBatteryVoltage ))
    {
        g_stMonitorPAPara.lBatteryVoltage = lBatteryVoltage;

        /* ����ǰ��ص�ѹ��Ϣ���͸�DSP*/

        Shpa_ProcVoltageReq(GGPHY_MONITOR_VOLTAGE_REQ, (VOS_UINT16)lBatteryVoltage);
    }

    return;
}


VOS_VOID Moniter_SetPhyIndType( VOS_UINT32 ulPhyIndType )
{
    g_ulMonitorIndType = ulPhyIndType;
    return;
}


VOS_VOID Moniter_SendReq(VOS_UINT32 ulSenderPid, VOS_UINT32 ulCmdType)
{
    MONITOR_CMD_STRU *pMsg;

    pMsg = (MONITOR_CMD_STRU *)VOS_AllocMsg(ulSenderPid,
                               sizeof(MONITOR_CMD_STRU)-VOS_MSG_HEAD_LENGTH);

    if (VOS_NULL_PTR == pMsg)
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_MEM;
        return;
    }

    pMsg->ulMsgName     = ulCmdType;
    pMsg->ulReceiverPid = WUEPS_PID_MONITOR;

    if (VOS_OK != VOS_SendMsg(ulSenderPid, pMsg))
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_MSG;
    }

    return;
}


VOS_VOID Monitor_QueryTask( VOS_VOID )
{
#if 0
    VOS_UINT32       ulRet;
#endif

    for(;;)
    {
        /* �ȴ��ź��� */
        VOS_SmP(g_ulMonitorCtrlSem, 0);

#if 0

        switch ( g_ulMonitorConnectState )
        {
            case MONITOR_IDLE_STATE:

                if (ID_PHY_MONITOR_QUERY_IND == g_ulMonitorIndType )   /* IDLE̬�յ�������ѯ�ж� */
                {
                    Moniter_SendReq(WUEPS_PID_MONITOR,ID_MONITOR_TEMP_QUERY_REQ);
                }
                else                                        /* IDLE̬�յ�����NORMAL̬�ж� */
                {
                    if (VOS_NULL_PTR == g_hQueryTimer)
                    {
                       ulRet = VOS_StartRelTimer( &g_hQueryTimer,
                                                   WUEPS_PID_MONITOR,
                                                   2000,
                                                   MONITOR_TIMER_NAME_QUERY,
                                                   0,
                                                   VOS_RELTIMER_LOOP );

                        if(VOS_OK != ulRet)
                        {
                            g_ulMonitorErrCode |= MONITOR_ERR_CODE_TIMER;
                        }
                    }

                    g_ulMonitorConnectState = MONITOR_CONNECT_STATE;
                }

                break;

            case MONITOR_CONNECT_STATE:      /* ����CONN̬ */

                if (ID_PHY_MONITOR_QUERY_IND == g_ulMonitorIndType )   /* IDLE̬�յ�������ѯ�ж� */
                {
                    if( VOS_NULL_PTR != g_hQueryTimer )
                    {
                        VOS_StopRelTimer( &g_hQueryTimer );
                    }

                    g_hQueryTimer = VOS_NULL_PTR;

                    Moniter_SendReq(WUEPS_PID_MONITOR, ID_MONITOR_TEMP_QUERY_REQ);

                    g_ulMonitorConnectState = MONITOR_IDLE_STATE;
                }
                else
                {
                    g_ulMonitorErrCode |= MONITOR_ERR_CODE_INT;
                }

                break;

            default:
                break;
        }
#endif
    }
}
VOS_VOID Monitor_TimerMsgProc(REL_TIMER_MSG *pMsg)
{

    if (MONITOR_TIMER_NAME_QUERY == pMsg->ulName)
    {
        Monitor_QueryPA(g_stTempStateCtrl.lOldTemperature);/*��ѯPA�¶�*/
    }
    else
    {
        g_ulMonitorErrCode |= MONITOR_ERR_CODE_MSGPROC;
    }

    return;
}
VOS_UINT32 Monitor_MsgProc(MsgBlock *pMsg)
{
#if 0
    MONITOR_CMD_STRU *pCmdMsg;

    if (VOS_PID_TIMER == pMsg->ulSenderPid)
    {
        Monitor_TimerMsgProc((REL_TIMER_MSG *)pMsg);

        return VOS_OK;
    }

    pCmdMsg = (MONITOR_CMD_STRU *)pMsg;

    switch (pCmdMsg->ulMsgName)
    {
        case ID_MONITOR_TEMP_QUERY_REQ:

            Monitor_QueryPA(g_stTempStateCtrl.lOldTemperature);/*��ѯPA�¶�*/

            break;

        default:

            break;

    }
#endif
    return VOS_OK;
}
VOS_UINT32 WuepsMonitorPidInit ( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case   VOS_IP_LOAD_CONFIG:

            if (VOS_OK != Monitor_Init())
            {
                /*lint -e534*/
                LogPrint("\r\nWuepsMonitorPidInit:Monitor_Init Fail!");
                /*lint +e534*/
            }

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
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
