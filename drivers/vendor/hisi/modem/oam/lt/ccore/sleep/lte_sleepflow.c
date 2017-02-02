

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
/*lint -save -e537*/
#include <lte_sleepflow.h>
#include "msp_errno.h"
#include "msp_sleep.h"

#include "msp_nvim.h"
#include <phyoaminterface.h>

#if (VOS_VXWORKS == VOS_OS_VER)
#include <cacheLib.h>
#endif

/*lint -restore*/

/*���ڿ��ƴ򿪹ر�MSP���ֵ͹���*/
#ifndef OPEN_MSP_SLEEP
#define OPEN_MSP_SLEEP
#endif

#ifndef MSP_IN_V9R1
#include <TLPhyInterface.h>
#else
#include <global_sram_map.h>
#endif

/*lint --e{1358, 40, 830, 539, 717, 746, 774, 534}*/

#define    THIS_FILE_ID   (MSP_FILE_ID_LTE_SLEEPFLOW_C)

/*ֱ�ӻ�ȡʱ���ǰ���ֵ*/
#define msp_get_timer_slice_delta(begin,end) ((end>=begin)?(end-begin):(0xFFFFFFFF-begin+end))


struct msp_power_control g_msp_pwrctrl = {0}; /*lint !e19*/
struct msp_delay_control g_msp_delay = {0, 5};
struct msp_hids_control g_msp_hidsctrl = {0, 0};
DRV_DRX_DELAY_STRU g_msp_drx_delay = {0};
VOS_INT dfs_bus_req_id = 0;
VOS_INT dfs_ddr_req_id = 0;
VOS_INT dfs_ccpu_req_id = 0;

RTT_SLEEP_INFO_STRU *g_pstRttSleepInfo = VOS_NULL_PTR;

VOS_UINT32 g_ulAddrShrDdr = 0;

TL_SLEEP_NOTIFY_FUNC pSleepFunc = VOS_NULL_PTR;
TL_SLEEP_NOTIFY_FUNC pWakeupFunc = VOS_NULL_PTR;

extern VOS_VOID RTTAGENT_EtSignalingInit(VOS_VOID);
/*****************************************************************************
 �� �� ��  : TLSLEEP_NotifyReg
 ��������  : ΪRCM�ṩ�Ļص�ע��ӿ�
*****************************************************************************/
VOS_VOID TLSLEEP_NotifyReg(TL_SLEEP_NOTIFY_FUNC pFuncSleep, TL_SLEEP_NOTIFY_FUNC pFuncWakeup)
{
    pSleepFunc = pFuncSleep;
    pWakeupFunc = pFuncWakeup;

    return ;
}


#ifdef OPEN_MSP_SLEEP
/*lint -e409 -e52 -e550 -e701 -e746*/
/*****************************************************************************
 �� �� ��  : QueueInit/QueueIn/QueueLoopIn
 ��������  : ���в���,Ϊ��ά�ɲ�ʹ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
static inline void QueueInit(drx_queue_t *Q, VOS_UINT32 elementNum)
{
    Q->maxNum = elementNum;
    Q->front = 0;
    Q->rear = 0;
    Q->num = 0;
}

static inline VOS_INT32 QueueIn(drx_queue_t *Q, VOS_UINT32 state)
{
    if (Q->num == Q->maxNum)
    {
        return -1;
    }

    Q->data[Q->rear].ulSlice = mdrv_timer_get_normal_timestamp();
    Q->data[Q->rear].ulState = state;

    Q->rear = (Q->rear+1) % Q->maxNum;
    Q->num++;

    return 0;
}

static inline VOS_INT32 QueueLoopIn(drx_queue_t *Q, VOS_UINT32 state)
{
    if (Q->num < Q->maxNum)
    {
        return QueueIn(Q, state);
    }
    else
    {
        Q->data[Q->rear].ulSlice = mdrv_timer_get_normal_timestamp();
        Q->data[Q->rear].ulState = state;

        Q->rear = (Q->rear+1) % Q->maxNum;
        Q->front = (Q->front+1) % Q->maxNum;
    }

    return 0;
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_StateRecord
 ��������  : ��¼���������и����׶ε���Ϣ
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_StateRecord(DRX_STATE_SLICE state)
{
    if(VOS_NULL == g_msp_pwrctrl.DrxStateSlice)
    {
        return;
    }
    g_msp_pwrctrl.DrxStateSlice[state].ulCount++;
    g_msp_pwrctrl.DrxStateSlice[state].ulSlice = mdrv_timer_get_normal_timestamp();
}
/*lint +e52 +e550*/
static inline VOS_VOID TLSLEEP_DbgTimeRecord(unsigned int recored)
{
    if(VOS_NULL == g_msp_pwrctrl.time_queue_record)
    {
        return;
    }
    /*Ϊ���������Ĳ����ڴ˼���ʱ����g_msp_delay.delay_control��ÿһ��bit ��־�Ƿ������ʱ*/
    if(g_msp_delay.delay_control&(1<<recored))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    if(TLSLEEP_DSPHALTISR_0 == recored)
    {
        QueueLoopIn(g_msp_pwrctrl.time_queue_record,0x5a5a5a5a);
    }
    QueueLoopIn(g_msp_pwrctrl.time_queue_record, recored);
    g_msp_pwrctrl.dbg_time_record[recored] = mdrv_timer_get_normal_timestamp();
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_DelayMs
 ��������  : ���Թ��ĵĹ�������Ҫ����ʱ�ĵط�������,��λms
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_DelayMs(VOS_UINT delay_ms, VOS_UINT flag)
{
    VOS_UINT oldtime = 0;
    VOS_UINT newtime = 0;

    oldtime = mdrv_timer_get_normal_timestamp();
    newtime = mdrv_timer_get_normal_timestamp();
    if(1 == flag)
    {
        while((oldtime + delay_ms*32) >  newtime)
        {
            newtime = mdrv_timer_get_normal_timestamp();
        }
    }
}

VOS_VOID TLSLEEP_RunDsp(VOS_VOID)
{
    VOS_INT32 power_lock = 0;

    power_lock = VOS_SplIMP();
    set_power_status_bit(MSP_PWR_WAIT_RESUMER);
    VOS_Splx(power_lock);
    (void)mdrv_dsp_run_bbe();
}


/*****************************************************************************
 �� �� ��  : TLSLEEP_PllEnable
 ��������  : ����NV�����ý���PLL��ʹ��
 �������  : ��
 �������  : ��,
 �� �� ֵ  :
*****************************************************************************/
VOS_VOID TLSLEEP_PllEnable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;
    
    switch(enCommModule)
    {
        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_clk_id;
            break;
            
        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;
            
        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }
    
    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_enable_pllclk(enCommMode, enCommModule, PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_PwrctrlUp
 ��������  : ����NV�����ý����ϵ�
 �������  : ��
 �������  : ��,
 �� �� ֵ  :
*****************************************************************************/
VOS_VOID TLSLEEP_PwrctrlUp(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;

    switch(enCommModule)
    {
#ifdef CONFIG_PASwitch_V7R5
        case PWC_COMM_MODULE_PA:
            chan = g_msp_pwrctrl.tlmode_channel[j].pa_switch_id;
            break;
#endif            
        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_channel_id;
            break;
            
        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;
            
        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }
    
    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_pwrup(enCommMode, enCommModule,  PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_PllDisable
 ��������  : ����NV�����ý���PLL��ȥʹ��
 �������  : ��
 �������  : ��,
 �� �� ֵ  :
*****************************************************************************/
VOS_VOID TLSLEEP_PllDisable(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;
    
    switch(enCommModule)
    {
        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_clk_id;
            break;
            
        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;
            
        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }
    
    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_disable_pllclk(enCommMode, enCommModule,  PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_PwrctrlDown
 ��������  : ����NV�����ý����µ�
 �������  : ��
 �������  : ��,
 �� �� ֵ  :
*****************************************************************************/
VOS_VOID TLSLEEP_PwrctrlDown(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule)
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    VOS_UINT32 j;

    j = (VOS_UINT32)enCommMode-PWC_COMM_MODE_LTE;
    switch(enCommModule)
    {
#ifdef CONFIG_PASwitch_V7R5
        case PWC_COMM_MODULE_PA:
            chan = g_msp_pwrctrl.tlmode_channel[j].pa_switch_id;
            break;
#endif
            
        case PWC_COMM_MODULE_RF:
            chan = g_msp_pwrctrl.tlmode_channel[j].rf_channel_id;
            break;
            
        case PWC_COMM_MODULE_ABB:
            chan = g_msp_pwrctrl.tlmode_channel[j].abb_channel_id;
            break;
            
        default:
            mspsleep_print_error("check your input enCommMode:%d,  enCommModule: %d\n", enCommMode, enCommModule);
            return ;
    }
    
    for(i = 0; i < MSP_SLEEP_CHAN_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_pwrdown(enCommMode, enCommModule,  PWC_COMM_MODEM_0, (PWC_COMM_CHANNEL_E)i);
        }
    }
}

/*****************************************************************************
 �� �� ��  : LSLEEP_RttForceAwake
 ��������  : ǿ�ƻ��ѽӿڣ����ͷ�sleep�����ź���
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_RttForceAwake(VOS_VOID)
{
    VOS_INT power_lock = 0;

    mspsleep_print_info("force awake");

    power_lock = VOS_SplIMP();

    TLSLEEP_StateRecord(DRX_FORCE_AWAKE_API);

    if((read_power_status_bit(MSP_PWR_FORCE_AWAKE))||(read_power_status_bit(MSP_PWR_WAKEUP))
        ||(read_power_status_bit(MSP_PWR_WAIT_RESUMER)))
    {
        VOS_Splx(power_lock);
        TLSLEEP_StateRecord(DRX_FORCE_AWAKE_NOT_DEAL);
        return;
    }
    else if(read_power_status_bit(MSP_PWR_SYSTEM_RUN))
    {
        VOS_Splx(power_lock);
        BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RESUME);
        TLSLEEP_StateRecord(DRX_FORCE_AWAKE_RUN_RETURN);
        return;
    }

    set_power_status_bit(MSP_PWR_FORCE_AWAKE);
    VOS_Splx(power_lock);
    VOS_SmV(g_msp_pwrctrl.task_sem);
    return;
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_TCXOIsrProc
 ��������  : ��TCXOʱע��Ļص�����
 �������  : ��
 �������  : ��,
 �� �� ֵ  :
*****************************************************************************/
VOS_VOID TLSLEEP_TCXO0_IsrProc( VOS_VOID )
{
    VOS_SmV(g_msp_pwrctrl.SleepTcxoSem[0]);
}
VOS_VOID TLSLEEP_TCXO1_IsrProc( VOS_VOID )
{
    VOS_SmV(g_msp_pwrctrl.SleepTcxoSem[1]);
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_OpenTCXO
 ��������  : ��TCXO
 �������  : ��
 �������  : ��,
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_OpenTCXO(VOS_VOID )
{
    PWC_COMM_MODEM_E                    enModem = PWC_COMM_MODEM_0;
    VOS_UINT32                          ulTcxoTime = 0;
    VOS_UINT32                          ulTcxoResult = VOS_OK;
    VOS_INT                             ulTcxoStatus[2] = {0};
    VOS_INT                             power_lock = 0;
    
    TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_0);

    if(g_msp_pwrctrl.tlmode_channel[0].tcxo_id == 0x3)
    {
        power_lock = VOS_SplIMP();
        ulTcxoStatus[0] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_0);
        ulTcxoStatus[1] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_1);
        
		mdrv_pm_enable_tcxo(PWC_COMM_MODEM_0, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE);
        mdrv_pm_enable_tcxo(PWC_COMM_MODEM_1, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE);
        
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_1);
        
        if ((PWRCTRL_COMM_OFF == ulTcxoStatus[0])||(PWRCTRL_COMM_OFF == ulTcxoStatus[1]))
        {
            ulTcxoTime  = g_msp_pwrctrl.SleepDrxResumeTime.ulTcxoRsmTime/1000;

            /* ����TCXO�ȶ��ȴ���ʱ�� */
            mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_0, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE, (PWC_TCXO_FUNCPTR)TLSLEEP_TCXO0_IsrProc, VOS_NULL, ulTcxoTime);
            mdrv_pm_start_tcxo_timer(PWC_COMM_MODEM_1, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE, (PWC_TCXO_FUNCPTR)TLSLEEP_TCXO1_IsrProc, VOS_NULL, ulTcxoTime);
            VOS_Splx(power_lock);
            /* coverity[lock] */
            ulTcxoResult    = VOS_SmP(g_msp_pwrctrl.SleepTcxoSem[0], WAIT_FOR_EVER);
            /* coverity[lock] */
            ulTcxoResult    |= VOS_SmP(g_msp_pwrctrl.SleepTcxoSem[1], WAIT_FOR_EVER);
            
            TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_2);
            if (VOS_OK != ulTcxoResult)
            {
                /* �쳣�������� */
                TLSLEEP_StateRecord(DRX_FAIL_WAIT_TCXO_SEM);
                mspsleep_print_error("tcxo get sem fail");
            }
        }
        else
        {
            VOS_Splx(power_lock);
        }
        
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_3);
        mdrv_pm_enable_tcxo_rfclk(PWC_COMM_MODEM_0, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        mdrv_pm_enable_tcxo_rfclk(PWC_COMM_MODEM_1, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_MAX);
    }
    else if(g_msp_pwrctrl.tlmode_channel[0].tcxo_id != 0)
    {
        enModem = (PWC_COMM_MODEM_E)g_msp_pwrctrl.tlmode_channel[0].tcxo_id;
        power_lock = VOS_SplIMP();
        mdrv_pm_enable_tcxo((PWC_COMM_MODEM_E)enModem, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE);
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_1);
        if (PWRCTRL_COMM_OFF == mdrv_pm_get_tcxo_status((PWC_COMM_MODEM_E)enModem))
        {
            ulTcxoTime  = g_msp_pwrctrl.SleepDrxResumeTime.ulTcxoRsmTime/1000;

            /* ����TCXO�ȶ��ȴ���ʱ�� */
            mdrv_pm_start_tcxo_timer(enModem, (PWC_COMM_MODE_E)PWC_COMM_MODE_LTE, (PWC_TCXO_FUNCPTR)TLSLEEP_TCXO0_IsrProc, VOS_NULL, ulTcxoTime);
            VOS_Splx(power_lock);
            
            /* �ȴ�TCXO�ȶ�,Take�ź�����Сʱ�䳤�ȱ���Ϊ1 tick */
            ulTcxoResult = VOS_SmP(g_msp_pwrctrl.SleepTcxoSem[0], WAIT_FOR_EVER);

            TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_2);
            if (VOS_OK != ulTcxoResult)
            {
                /* �쳣�������� */
                TLSLEEP_StateRecord(DRX_FAIL_WAIT_TCXO_SEM);
                mspsleep_print_error("tcxo get sem fail");
            }
        }
        else
        {
            VOS_Splx(power_lock);
        }
        
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_3);
        mdrv_pm_enable_tcxo_rfclk(enModem, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_MAX);
    }
    else
    {
        /* ��DCXO�������ÿ��� */
    }
    /* coverity[missing_unlock] */
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_CloseTCXO
 ��������  : �ر�TCXO
 �������  : ��
 �������  : ��,
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_CloseTCXO(VOS_VOID )
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    
    /* Ĭ��ʹ��LTE�Ĳ��� */
    chan = g_msp_pwrctrl.tlmode_channel[0].tcxo_id;

    for(i = 0; i < MSP_SLEEP_TCXO_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_disable_tcxo_rfclk((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
            mdrv_pm_disable_tcxo((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE);
        }
    }
}


#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)

VOS_VOID TLSLEEP_EnableRFTCXO(VOS_VOID )
{
    VOS_INT32 i;
    VOS_UINT16 chan;

    TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_0);

    /* Ĭ��ʹ��LTE�Ĳ��� */
    chan = g_msp_pwrctrl.tlmode_channel[0].tcxo_id;

    for(i = 0; i < MSP_SLEEP_TCXO_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_enable_tcxo_rfclk((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        }
    }
    
    TLSLEEP_DbgTimeRecord(TLSLEEP_OPENTCXO_MAX);
}

VOS_VOID TLSLEEP_DisableRFTCXO(VOS_VOID )
{
    VOS_INT32 i;
    VOS_UINT16 chan;
    
    /* Ĭ��ʹ��LTE�Ĳ��� */
    chan = g_msp_pwrctrl.tlmode_channel[0].tcxo_id;

    for(i = 0; i < MSP_SLEEP_TCXO_NUM; i++)
    {
        if(chan & (VOS_UINT16)(0x1<<i))
        {
            mdrv_pm_disable_tcxo_rfclk((PWC_COMM_MODEM_E)i, PWC_COMM_MODE_LTE, PWC_COMM_CHANNEL_0);
        }
    }
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_HwPowerUp
 ��������  : ΪRTT��������ϵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS �ɹ�
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerUp(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E                enModem = PWC_COMM_MODEM_0;
    PWC_COMM_CHANNEL_E              enChannel = PWC_COMM_CHANNEL_0;
    VOS_INT32                       ret = 0;
    VOS_INT                         power_lock = 0;

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_0);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_0);
    
    /* DDR������Ƶ�ʲ���Ҫ����ֻ��Ҫ��CCPUƵ�� */
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id,TLSLEEP_DFS_CCPU_600M);
    if(ret)
    {
        power_lock = VOS_SplIMP();/* [false alarm]:����Fortify */
        set_power_status_bit(MSP_DFS_RUN_UPDATE_FAIL);
        VOS_Splx(power_lock);
    }

    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_1);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /* V8R1��ʹ�õ�DCXO������ҪMSP����TCXO���ɵ������Σ�MSP���ִ���Ĺ�һ */
        (void)mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);

        /* ��1��2��ʾ��˯���� */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
        (void)mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        (void)mdrv_pm_enable_pllclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        if(mdrv_dsp_restore_bbe())
        {
            TLSLEEP_StateRecord(RESTORE_DSP_TCM_FAIL);
            mspsleep_print_error("DSP TCM restore fail");
        }
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /* ��2��1��ʾǳ˯���� */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        (void)mdrv_dsp_enable_clk();
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
        (void)mdrv_dsp_unreset_bbe();
    }
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_2);
    /* ABB PLLʹ��ǰ���ϵ� */
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_3);

    /* BBP�ϵ����ǰҪ��ʹ��PLL(PLL����BBPǰ��) */
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_4);

    /* V8R1 BBP��ABB����PLL���˽ӿ��ڵ����д�׮ */
    mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_5);

    /* TDS BBPʱ��ʹ�ܣ�LTE BBPʱ��ʹ����DSP���� */
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_6);

    /* LTE�漰���ʱ��Դ��DSPֻ����һ���֣���ҪMSP���õ���ӿڴ�LTE�������ʱ�� */
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /* TDS BBP�ϵ磬LTE BBP�ϵ���DSP���� */
    (void)mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_7);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_3);
    /*RF�ϵ�*/
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

    TLSLEEP_EnableRFTCXO();

    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_8);

    if(g_pstRttSleepInfo)
    {
        g_pstRttSleepInfo->ulRfTime = mdrv_timer_get_normal_timestamp();
    }
    VOS_FlushCpuWriteBuf();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_9);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        (void)mdrv_dsp_get_br_status();
    }

    BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RUN);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_4);
    TLSLEEP_RunDsp();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_MAX);

    return ERR_MSP_SUCCESS;
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_HwPowerDown
 ��������  : ΪRTT��������µ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS �ɹ�
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerDown(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E                enModem = PWC_COMM_MODEM_0;
    PWC_COMM_CHANNEL_E              enChannel = PWC_COMM_CHANNEL_0;
    VOS_INT32                       ret = 0;
    VOS_INT32                       flag = 0;

    enModem = PWC_COMM_MODEM_0;

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_0);
    mdrv_dsp_stop_bbe();
    /* DDR������Ƶ�ʲ���Ҫ����ֻ��Ҫ��CCPUƵ�� */
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id, TLSLEEP_DFS_CCPU_150M);
    if(ret)
    {
        flag = VOS_SplIMP();
        set_power_status_bit(MSP_DFS_HALT_UPDATE_FAIL);
        VOS_Splx(flag);
    }

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_1);

    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /*������DSP�ϵ��ʱ����ܽ��б��棬�����ǲ�������������̵�*/
        if (mdrv_dsp_backup_bbe())
        {
           TLSLEEP_StateRecord(STORE_DSP_TCM_FAIL);
           mspsleep_print_error("DSP TCM store fail");
        }
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_2);
    /*RF�µ�*/
    TLSLEEP_DisableRFTCXO();
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_3);

    /* TDS BBP�µ磬LTE BBP�µ���DSP���� */
    mdrv_pm_pwrdown(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_4);

    /* TDS BBPʱ��ȥʹ�ܣ�LTE BBPʱ��ȥʹ����DSP���� */
    mdrv_pm_disable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_5);

    /* LTE�漰���ʱ��Դ��DSPֻ����һ���֣���ҪMSP���õ���ӿڴ�LTE�������ʱ�� */
    (void)mdrv_pm_disable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /* BBP PLL�ر�(V8R1�е�DCXO��BBP��PLLʹ��ABB�е�PLL���˽ӿڵ����׮) */
    (void)mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_6);

    /* ABB PLLȥʹ�� */
    TLSLEEP_PllDisable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_7);

    /* ABB PLL�µ� */
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_8);

    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_DEEP_SLEEP_COUNT);
        (void)mdrv_dsp_get_br_status();
        TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_9);
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBE16, enModem, enChannel);
        mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, enChannel);

        /* V8R1��ʹ�õ�DCXO������ҪMSP����TCXO���ɵ������Σ�MSP���ִ���Ĺ�һ */
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_LIGHT_SLEEP_COUNT);
        (void)mdrv_dsp_reset_bbe();
        /*BBE16 ����*/
        (void)mdrv_dsp_disable_clk();
    }
    else
    {
        TLSLEEP_StateRecord(DSP_SLEEP_FLAG_ERROR);
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_MAX);

    return ERR_MSP_SUCCESS;
}

#else

/*****************************************************************************
 �� �� ��  : TLSLEEP_CheckWakeTime
 ��������  : ��⵱ǰ����DSP�Ƿ�ʱ,�����ʱ���д�����
 �������  : ��
 �������  : ��
 �� �� ֵ  :
*****************************************************************************/
static inline VOS_VOID TLSLEEP_CheckWakeTime()
{
    VOS_UINT32 sleep_time = *(VOS_UINT32*)(HI_BBP_LTEDRX_BASE_ADDR + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);
    VOS_UINT32 wake_time = *(VOS_UINT32*)(HI_BBP_LTEDRX_BASE_ADDR + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET);
    VOS_UINT32 clk_time = *(VOS_UINT32*)(HI_BBP_LTEDRX_BASE_ADDR + HI_BBP_LTEDRX_SWITCH_32K_CNT_OFFSET);
    VOS_UINT32 i = 0;
    /*���Ϊ��ģ,���һ��ѳ�ʱ�ͽ��м�¼*/
    if(((sleep_time + g_msp_pwrctrl.exc_overtime.timeOut) > (wake_time + clk_time))&&(clk_time > 163)\
        &&(0 == g_msp_pwrctrl.exc_overtime.ulReadMark))
    {
        for(i = TLSLEEP_DSPHALTISR_0; i < TLSLEEP_TIME_RECORD_MAX; i++)
        {
            g_msp_pwrctrl.exc_overtime.ulTime[i] = g_msp_pwrctrl.dbg_time_record[i];
        }
        g_msp_pwrctrl.exc_overtime.ulReadMark = 1;
        VOS_SmV(g_msp_pwrctrl.exc_overtime.time_sem);
    }
    return;
}

VOS_VOID TLSLEEP_DebugRecordTime(VOS_VOID)
{
    int i = 0;
    VOS_UINT32* axi_time = &g_msp_pwrctrl.dbg_time_record[TLSLEEP_AWAKEISR_0];
    VOS_UINT32* ddr_time = 0;

    if(0 == g_ulAddrShrDdr)
    {
        return;
    }

    ddr_time = (VOS_UINT32*)(g_ulAddrShrDdr + 0x200);

    TLSLEEP_CheckWakeTime();

    if((*(VOS_UINT32*)(g_ulAddrShrDdr + 4)) == 1)
    {
        *(VOS_UINT32*)(g_ulAddrShrDdr + 4) = 2;
        *(VOS_UINT32*)(g_ulAddrShrDdr + 8) = 1;
    }
    else
    {
        return;
    }

    /*0x5A5A5A5A~0x5B5B5B5B,Ϊ�ϵ�����еĵ�*/
    *(ddr_time++) = 0x5A5A5A5A;
    for(i = TLSLEEP_AWAKEISR_0; i <= TLSEEP_HWPOWERUP_9; i++)
    {
        *(ddr_time++) = *(axi_time++);
    }
    /*0x5B5B5B5B~0x5C5C5C5C,Ϊ�µ�����еĵ�*/
    *(ddr_time++) = 0x5B5B5B5B;
    axi_time =  &g_msp_pwrctrl.dbg_time_record[TLSLEEP_DSPHALTISR_0];
    for(i = TLSLEEP_DSPHALTISR_0; i <= TLSLEEP_RTTSLEEP_INNER_MAX; i++)
    {
        *(ddr_time++) = *(axi_time++);
    }
    *(ddr_time++) = 0x5C5C5C5C;
}

VOS_VOID TLSLEEP_PWRCTRL_PWRUP(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId)
{
    (void)mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
    mdrv_dsp_enable_clk();
    mdrv_dsp_reset_bbe();
    mdrv_dsp_unreset_bbe();
}

VOS_VOID TLSLEEP_PWRCTRL_PWRDOWN(PWC_COMM_MODE_E enCommMode, PWC_COMM_MODULE_E enCommModule, PWC_COMM_MODEM_E enModemId)
{
    mdrv_dsp_disable_clk();
    (void)mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, PWC_COMM_MODEM_0, PWC_COMM_CHANNEL_0);
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_HwPowerUp
 ��������  : ΪRTT��������ϵ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS �ɹ�
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerUp(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E       			enModem = PWC_COMM_MODEM_0;
    VOS_INT32                       ret = 0;
    VOS_INT                         power_lock = 0;
    VOS_UINT32                          timestamp_begin = 0;
    VOS_UINT32                          timestamp_end = 0;
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_0);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_0);
    
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_1);
	
    /* RF�����ϵ� */
    mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_FEM, enModem, PWC_COMM_CHANNEL_0);
    /*RF��Դ�ϵ�Ҫ����RFPLLenable������Ҫ���200us*/
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
	timestamp_begin = mdrv_timer_get_normal_timestamp();
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
#ifdef CONFIG_DFS_DDR
        ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_240M);/* [false alarm]:����Fortify */
        if(ret)
        {
            power_lock = VOS_SplIMP();/* [false alarm]:����Fortify */
            set_power_status_bit(MSP_DFS_RUN_UPDATE_FAIL);
            VOS_Splx(power_lock);
        }
#endif
    	TLSLEEP_OpenTCXO();
        /* ��1��2��ʾ��˯���� */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
        mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
        TLSLEEP_PWRCTRL_PWRUP(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem);
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        if(mdrv_dsp_restore_bbe())
        {
            TLSLEEP_StateRecord(RESTORE_DSP_TCM_FAIL);
            mspsleep_print_error("DSP TCM restore fail");
        }
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
#ifdef CONFIG_DFS_DDR
        ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_120M);/* [false alarm]:����Fortify */
        if(ret)
        {
            power_lock = VOS_SplIMP();/* [false alarm]:����Fortify */
            set_power_status_bit(MSP_DFS_RUN_UPDATE_FAIL);
            VOS_Splx(power_lock);
        }
#endif
        /* V7R5/Austin������DSP���µ������ִ��PLL�л�(��DSPģ��ʵ��) */
        mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
        mdrv_dsp_enable_clk();
        /* ��2��1��ʾǳ˯���� */
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_2);
        /*V7R2�Ż�����,��λ�⸴λ����һ��*/
        mdrv_dsp_reset_bbe();
        mdrv_dsp_unreset_bbe();
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_1);
    }
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_2);
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_3);
    /*BBP�ϵ�*/
    mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_4);
    /*��TDS ʹ�õ�BBP 1A����ʱ��*/
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_5);
    mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_6);
    /*ͨ��NV���ƹر��ĸ�ͨ��*/
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_7);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_3);
    
    if(g_pstRttSleepInfo)
    {
        g_pstRttSleepInfo->ulRfTime = mdrv_timer_get_normal_timestamp();
    }
    VOS_FlushCpuWriteBuf();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_8);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        mdrv_dsp_get_br_status();
        TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_9);
    }
    TLSLEEP_DebugRecordTime();
    BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RUN);
    TLSLEEP_DelayMs(5, g_msp_drx_delay.msp_4);
	mdrv_rffe_cfg_on_power_up(PWC_COMM_MODE_LTE, enModem, PWC_COMM_CHANNEL_0);
    /*RF��Դ�ϵ�Ҫ����RFPLLenable������Ҫ���200us*/
    do
    {
        timestamp_end = mdrv_timer_get_normal_timestamp();
    }while((msp_get_timer_slice_delta(timestamp_begin, timestamp_end)) < 7);
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

#ifdef CONFIG_PASwitch_V7R5     
    /*  PA ֻ���V7R5��������߹���bug  */
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_PA);
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_PA);
#endif
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /*ȫϵͳ��ʼ���ϵ����ET��ʼ��*/
        RTTAGENT_EtSignalingInit();
    }
    TLSLEEP_RunDsp();
    TLSLEEP_DbgTimeRecord(TLSEEP_HWPOWERUP_MAX);

    return ERR_MSP_SUCCESS;
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_HwPowerDown
 ��������  : ΪRTT��������µ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ERR_MSP_SUCCESS �ɹ�
*****************************************************************************/
VOS_INT32 TLSLEEP_HwPowerDown(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E       			enModem = PWC_COMM_MODEM_0;
    VOS_INT32                       ret = 0;

	enModem = PWC_COMM_MODEM_0;

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_0);

#ifdef CONFIG_PASwitch_V7R5    
    /*  PA ֻ���V7R5��������߹���bug  */
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_PA);
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_PA);
#endif 
    mdrv_dsp_stop_bbe();
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_1);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        /*������DSP�ϵ��ʱ����ܽ��б��棬�����ǲ�������������̵�*/
        if (mdrv_dsp_backup_bbe())
        {
           TLSLEEP_StateRecord(STORE_DSP_TCM_FAIL);
           mspsleep_print_error("DSP TCM store fail");
        }
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_2);
    /* RF�µ���� */
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
    mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_FEM, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_PllDisable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
	mdrv_rffe_cfg_on_power_down(PWC_COMM_MODE_LTE, enModem, PWC_COMM_CHANNEL_0);
    
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_3);
    TLSLEEP_PllDisable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_4);
    /*BBPʱ�ӹر�*/
    mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_5);
    /*�ر�TDS ʹ�õ�BBP 1A����ʱ��*/
    mdrv_pm_disable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    mdrv_pm_disable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_6);
    /*BBP�µ�*/
    mdrv_pm_pwrdown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_7);
    mdrv_pm_pwrdown(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_8);
    TLSLEEP_PwrctrlDown(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_DEEP_SLEEP_COUNT);
        mdrv_dsp_get_br_status();
        TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_9);
        TLSLEEP_PWRCTRL_PWRDOWN(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem);
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
        TLSLEEP_CloseTCXO();
    }
    else if(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag)
    {
        TLSLEEP_StateRecord(DSP_LIGHT_SLEEP_COUNT);
        /*BBE16 ����*/
        mdrv_dsp_disable_clk();
        /* V7R5/Austin������DSP���µ������ִ��PLL�л�(��DSPģ��ʵ��) */
        mdrv_pm_disable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
    }
    else
    {
        TLSLEEP_StateRecord(DSP_SLEEP_FLAG_ERROR);
    }
    
#ifdef CONFIG_DFS_DDR
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, 0);
    if(ret)
    {
        mspsleep_print_error("MSP vote TLSLEEP_DFS_DDR_0M failed!\n");
    }
#endif

    TLSLEEP_DbgTimeRecord(TLSLEEP_HWPOWERDOWN_MAX);
    return ERR_MSP_SUCCESS;
}

#endif
/*****************************************************************************
 �� �� ��  : TLSLEEP_RttForceAwake_Inner
 ��������  : ���ѹ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_INT32 TLSLEEP_RttForceAwake_Inner(VOS_VOID)
{
    VOS_INT power_lock = 0;
    
    /* ��DSP/RCMҪ�󣬻���ǰ�ص�RCM */
    if(pWakeupFunc)
    {
        TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKE_CB_0);
        pWakeupFunc();
        TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKE_CB_1);
    }

    /*ͶƱ���ܽ���˯��*/
    mdrv_pm_wake_lock(PWRCTRL_SLEEP_TLPS);
    if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_BEFOR_WAKE))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    mspsleep_print_info("start wake");
    TLSLEEP_DbgTimeRecord(TLSLEEP_FORCE_AWAKE_INNER_0);

    if(TLSLEEP_HwPowerUp((PWC_COMM_MODE_E)PWC_COMM_MODE_LTE))
    {
        mspsleep_print_error("sleep power up failed!");
        return MSP_SLEEP_ERROR;
    }
    if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_AFTER_SLEEP))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_FORCE_AWAKE_INNER_1);

    power_lock = VOS_SplIMP();
    clear_power_status_bit(MSP_PWR_WAKEUP);
    clear_power_status_bit( MSP_PWR_FORCE_AWAKE);
    VOS_Splx(power_lock);
    mspsleep_print_info("Complete wake");
    return ERR_MSP_SUCCESS;
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_RttSleep_Inner
 ��������  : ��������
 �������  :
 �������  :
 �� �� ֵ  :  VOS_VOID
*****************************************************************************/
VOS_VOID TLSLEEP_RttSleep_Inner(VOS_VOID)
{
    /*lint -save -e958*/
    VOS_BOOL bMeasFlag = VOS_FALSE;
    VOS_INT power_lock = 0;
    
    /*lint -restore*/
    if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_BEFOR_SLEEP))
    {
        TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
    }
    mspsleep_print_info("start sleep");
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_0);

    /*��������Ƿ�����˯�ߣ�������䲻����˯���򲻽���˯�ߺ��µ磬ֱ�ӽ⸴λDSP*/
    /*TRUE-allow;FALSE-forbid trueΪ1 false Ϊfalse*/
    power_lock = VOS_SplIMP();
    bMeasFlag = (VOS_BOOL)BSP_MailBox_IsAllowDspSleep();
    g_msp_pwrctrl.ForbidDspSleepValue= (read_power_status_bit(MSP_PWR_FORCE_AWAKE))|(read_power_status_bit(MSP_PWR_WAKEUP))| (!bMeasFlag); /*lint !e514*/
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_1);
    if(g_msp_pwrctrl.ForbidDspSleepValue)
    {
        clear_power_status_bit(MSP_PWR_WAKEUP);
        clear_power_status_bit(MSP_PWR_FORCE_AWAKE);
        clear_power_status_bit(MSP_PWR_HALT_INT);
        clear_power_status_bit(MSP_PWR_SYSTEM_RUN);
        clear_power_status_bit(MSP_PWR_WAIT_RESUMER);
        TLSLEEP_ResumeDsp();
        TLSLEEP_StateRecord(SLEEP_TASK_NOT_NEED_DEAL);
        VOS_Splx(power_lock);
        mspsleep_print_info("Resme dsp");
        return;
    }
    else
    {
        VOS_Splx(power_lock);
    }
    TLSLEEP_HwPowerDown(PWC_COMM_MODE_LTE);
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_2);

    power_lock = VOS_SplIMP();
    clear_power_status_bit(MSP_PWR_HALT_INT);
    clear_power_status_bit(MSP_PWR_SYSTEM_RUN);
    clear_power_status_bit(MSP_PWR_WAIT_RESUMER);
    if((!read_power_status_bit(MSP_PWR_FORCE_AWAKE))&&(!read_power_status_bit(MSP_PWR_WAKEUP)))
    {
        VOS_Splx(power_lock);

        /*ͶƱ˯��*/
        if(0 != ((g_msp_delay.delay_control)&DELAY_CTRL_AFTER_SLEEP))
        {
            TLSLEEP_DelayMs(g_msp_delay.delay_ms, 1);
        }
#ifndef MSP_IN_V9R1
        if(((ENUM_YES_VOTE_SLEEP == (VOS_INT)g_msp_pwrctrl.SleepDrxResumeTime.ulVoteSwitch)
            &&(POWER_SAVING_SNOOZE == g_msp_pwrctrl.dsp_sleep_flag))
			||(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag))
#endif
        {
            mdrv_pm_wake_unlock(PWRCTRL_SLEEP_TLPS);
	        TLSLEEP_StateRecord(SLEEP_VOTE_UNLOCK);
        }
    }
    else
    {
        VOS_Splx(power_lock);
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_RTTSLEEP_INNER_MAX);
    mspsleep_print_info("Complete sleep");

    /* ��DSP/RCMҪ��˯�ߺ�ص�RCM */
    if(pSleepFunc)
    {
        TLSLEEP_DbgTimeRecord(TLSLEEP_SLEEP_CB_0);
        pSleepFunc();
        TLSLEEP_DbgTimeRecord(TLSLEEP_SLEEP_CB_1);
    }
}

/* ������Ϣ�����ϱ���ά�ɲ���Ϣ�����߲� */
VOS_VOID TLSLEEP_ReportMntn()
{
    MSP_SLEEP_MNTN_MSG_STRU* pSleepMsg = NULL;

    pSleepMsg = (MSP_SLEEP_MNTN_MSG_STRU*)VOS_AllocMsg(MSP_PID_DRX, sizeof(MSP_SLEEP_MNTN_MSG_STRU) -VOS_MSG_HEAD_LENGTH);
    
    if (pSleepMsg)
    {
        pSleepMsg->ulReceiverPid    = MSP_PID_DRX;
        pSleepMsg->ulMsgId          = ID_MSG_SLEEP_WAKEUP_SLICE_MNTN;
        pSleepMsg->ulHalt           = g_msp_pwrctrl.DrxStateSlice[DRX_HALT_INT].ulSlice;
        pSleepMsg->ulSleepStart     = g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_START].ulSlice;
        pSleepMsg->ulSleepEnd       = g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_END].ulSlice;
        pSleepMsg->ulWakeup         = g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_INT].ulSlice;
        pSleepMsg->ulForceAwake     = g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_API].ulSlice;
        pSleepMsg->ulWakeupStart    = g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_START].ulSlice;
        pSleepMsg->ulAwake_CB_0     = g_msp_pwrctrl.dbg_time_record[TLSLEEP_AWAKE_CB_0];
        pSleepMsg->ulAwake_CB_1     = g_msp_pwrctrl.dbg_time_record[TLSLEEP_AWAKE_CB_1];
        pSleepMsg->ulFORCE_AWAKE_INNER_0 = g_msp_pwrctrl.dbg_time_record[TLSLEEP_FORCE_AWAKE_INNER_0];
        pSleepMsg->ulHWPOWERUP_0    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_0];
        pSleepMsg->ulHWPOWERUP_1    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_1];
        pSleepMsg->ulHWPOWERUP_2    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_2];
        pSleepMsg->ulHWPOWERUP_3    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_3];
        pSleepMsg->ulHWPOWERUP_4    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_4];
        pSleepMsg->ulHWPOWERUP_5    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_5];
        pSleepMsg->ulHWPOWERUP_6    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_6];
        pSleepMsg->ulHWPOWERUP_7    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_7];
        pSleepMsg->ulHWPOWERUP_8    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_8];
        pSleepMsg->ulHWPOWERUP_9    = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_9];
        pSleepMsg->ulHWPOWERUP_MAX  = g_msp_pwrctrl.dbg_time_record[TLSEEP_HWPOWERUP_MAX];
        pSleepMsg->ulFORCE_AWAKE_INNER_1 = g_msp_pwrctrl.dbg_time_record[TLSLEEP_FORCE_AWAKE_INNER_1];
        pSleepMsg->ulWakeupEnd      = g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_END].ulSlice;
        pSleepMsg->ulResume         = g_msp_pwrctrl.DrxStateSlice[DRX_RESUME_INT].ulSlice;

        DIAG_TraceReport(pSleepMsg);
        
        VOS_FreeMsg(MSP_PID_DRX, pSleepMsg);
    }
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_SleepTask
 ��������  : msp˯���������ں���
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_SleepTask(VOS_UINT32 Para0, VOS_UINT32 Para1,
                                VOS_UINT32 Para2, VOS_UINT32 Para3 )
{
    VOS_INT power_lock = 0;

    for (;;)
    {
        /* coverity[lock] */
        if(VOS_OK != VOS_SmP(g_msp_pwrctrl.task_sem, WAIT_FOR_EVER))
        {
            mspsleep_print_error("take task sem error!");
            /* coverity[missing_unlock] */
            return;
        }

        TLSLEEP_StateRecord(DRX_SLEEP_TASK);
        power_lock = VOS_SplIMP();
        /*�����ǰ��halt �ж�*/
        if(read_power_status_bit(MSP_PWR_HALT_INT))
        {
            VOS_Splx(power_lock);
            TLSLEEP_StateRecord(DRX_SLEEP_START);
            TLSLEEP_RttSleep_Inner();
            TLSLEEP_StateRecord(DRX_SLEEP_END);
        }
        else if(read_power_status_bit(MSP_PWR_FORCE_AWAKE)||read_power_status_bit(MSP_PWR_WAKEUP))
        {
            VOS_Splx(power_lock);
            TLSLEEP_StateRecord(DRX_WAKEUP_START);
            TLSLEEP_RttForceAwake_Inner();
            TLSLEEP_StateRecord(DRX_WAKEUP_END);
            TLSLEEP_ReportMntn();
        }
        else
        {
            VOS_Splx(power_lock);
            mspsleep_print_debug("the status is 0x%x", g_msp_pwrctrl.pwr_status);
        }
    }
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_DspHaltIsr
 ��������  : ��ӦDSP halt�жϣ��ͷ��ź�����ʼsleep����ʹ����˯��
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_DspHaltIsr(VOS_UINT param)
{
    VOS_INT flag = 0;
    /*�����Ǹ���ά�ɲ�,DSP�ڿ�ʼ���еĵ�һʱ����Ϊ1,*/
    if(g_pstRttSleepInfo)
    {
        g_pstRttSleepInfo->dspState = ENUM_DSP_IS_SLEEP;
    }
    VOS_FlushCpuWriteBuf();
    flag = VOS_SplIMP();
    if(FIRST_HALT_INT == g_msp_pwrctrl.DspHaltIntMark )
    {
        mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_LTE);
        mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_TDS);
        mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_LTE);
        mdrv_bbp_enable_wakeup_intr(PWC_COMM_MODE_TDS);
        g_msp_pwrctrl.DspHaltIntMark = HAD_HALT_INT;
    }
    if(read_power_status_bit(MSP_PWR_HALT_INT))
    {
        set_power_status_bit(MSP_REPEAT_HALT_ERROR);
        VOS_Splx(flag);
        return;
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_DSPHALTISR_0);
    clear_power_status_bit(MSP_PWR_SYSTEM_RUN);
    set_power_status_bit(MSP_PWR_HALT_INT);
    if(g_pstRttSleepInfo)
    {
        g_msp_pwrctrl.dsp_sleep_flag = (LPHY_RTT_LPC_MODE_ENUM)(g_pstRttSleepInfo->ulLightSleepFlag);
    }
    
    TLSLEEP_StateRecord(DRX_HALT_INT);
    if(ENUM_NO_UP_DOWN_DSP == g_msp_pwrctrl.SleepDrxResumeTime.ulPowerSwich)
    {
        TLSLEEP_RttForceAwake();
    }
    else
    {
        VOS_SmV(g_msp_pwrctrl.task_sem);
    }

    VOS_Splx(flag);
}
/*****************************************************************************
 �� �� ��  : TLSLEEP_DspResumeIsr
 ��������  : ��ӦDSP RESUMER�жϣ�֪ͨ����DSP������
 �������  : void
 �������  : ��
 �� �� ֵ  : ��
*****************************************************************************/
VOS_VOID TLSLEEP_DspResumeIsr(VOS_UINT param)
{
    VOS_INT status_lock = 0;
    VOS_INT ret = 0;

    status_lock = VOS_SplIMP();
    TLSLEEP_StateRecord(DRX_RESUME_INT);
    TLSLEEP_DbgTimeRecord(TLSLEEP_DSPRESUMERISR_0);
#ifdef CONFIG_DFS_DDR
    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_120M);
    if(ret)
    {
        mspsleep_print_error("MSP vote TLSLEEP_DFS_DDR_120M failed!\n");
    }
#endif
    
    /*�жϵ�ǰ���յ�DSP Resume�ж��ڻ����������Ƿ�����*/
    if (read_power_status_bit(MSP_PWR_WAIT_RESUMER))
    {
        clear_power_status_bit(MSP_PWR_WAIT_RESUMER);
        if(read_power_status_bit(MSP_PWR_HALT_INT))
        {
            TLSLEEP_RttForceAwake();
            TLSLEEP_StateRecord(DRX_HALT_RESUME_CONFLICT);
        }
        else
        {
            set_power_status_bit(MSP_PWR_SYSTEM_RUN);

            /*�������������ӿ�֪ͨ���份���Ѿ����*/
            BSP_MailBox_DspAwakeProc(EN_MAILBOX_CALLBACK_DSP_RESUME);
            TLSLEEP_StateRecord(RESUME_NOTIFY_MAILBOX);
        }
		VOS_Splx(status_lock);
        return;
    }
    else
    {
        mspsleep_print_error("dsp resumer int is error");
        mspsleep_print_error("pwr_status = %x", g_msp_pwrctrl.pwr_status);
    }
    VOS_Splx(status_lock);
    return;
}
/*****************************************************************************
 �� �� ��  : LSLEEP_RttIsSleep
 ��������  : ��ѯ��ǰTL�ǻ��ѻ���˯��״̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOS_TRUE:��ǰΪ˯��״̬
             VOS_FALSE:��ǰ����˯��״̬
*****************************************************************************/
VOS_BOOL TLSLEEP_RttIsSleep(VOS_VOID)
{
    VOS_INT power_lock = 0;
    power_lock = VOS_SplIMP();
    /*lint -e514*/
    g_msp_pwrctrl.RttIsSleepValue = (read_power_status_bit(MSP_PWR_HALT_INT))\
                    |(read_power_status_bit(MSP_PWR_WAIT_RESUMER))\
                    |(!read_power_status_bit(MSP_PWR_SYSTEM_RUN));
    /*lint +e514*/
    /*TLSLEEP_StateRecord(DRX_CHECK_DSP_STATUS);*/
    if(g_msp_pwrctrl.RttIsSleepValue)
    {
        VOS_Splx(power_lock);
        return VOS_TRUE;
    }
    VOS_Splx(power_lock);
    return VOS_FALSE;
}


typedef struct
{
    VOS_UINT32      ulMspPowerup;
    VOS_UINT32      ulDspTcmResume;
    VOS_UINT32      ulInterval;
    
    VOS_UINT32      ulPtrWake;
    VOS_UINT32      ulPtrTimer;
    
    VOS_UINT32      ulSwitchLen[100];
    VOS_UINT32      ulDelay[100];
    VOS_UINT32      ulSliceWakeup[100];

    VOS_UINT32      ulSliceTimeout[100];
}TL_SLEEP_SWITCH_TIME_STRU;

TL_SLEEP_SWITCH_TIME_STRU g_stSleepSwitch = {0};

VOS_VOID TLSLEEP_ShowSleepSwitch(VOS_VOID)
{
    VOS_UINT32 i,j;
    
    vos_printf("ulMspPowerup %d, ulDspTcmResume %d, ulInterval %d.\n", g_stSleepSwitch.ulMspPowerup, g_stSleepSwitch.ulDspTcmResume, g_stSleepSwitch.ulInterval);

    for(i = 0; i < 25; i++)
    {
        for(j = 0; j < 4; j++)
        {
            vos_printf("ulSwitchLen %d, ulDelay %d | ", g_stSleepSwitch.ulSwitchLen[4*i+j], g_stSleepSwitch.ulDelay[4*i+j]);
        }
        vos_printf("\n");
    }

    for(i = 0; i < 10; i++)
    {
        for(j = 0; j < 10; j++)
        {
            vos_printf("ulSliceWakeup 0x%x, ulSliceTimeout 0x%x | ", g_stSleepSwitch.ulSliceWakeup[10*i+j], g_stSleepSwitch.ulSliceTimeout[10*i+j]);
        }
        vos_printf("\n");
    }

}

VOS_INT TLSLEEP_TimerIsr(VOS_INT lPara);
VOS_INT TLSLEEP_TimerIsr(VOS_INT lPara)
{
    VOS_INT power_lock = 0;

    (VOS_VOID)mdrv_timer_stop((VOS_UINT32)lPara);

    g_stSleepSwitch.ulSliceTimeout[g_stSleepSwitch.ulPtrTimer] = VOS_GetSlice();
    g_stSleepSwitch.ulPtrTimer = (g_stSleepSwitch.ulPtrTimer+1)%100;

    power_lock = VOS_SplIMP();

    if(read_power_status_bit(MSP_PWR_WAKEUP)||read_power_status_bit(MSP_PWR_FORCE_AWAKE)
      ||read_power_status_bit(MSP_PWR_SYSTEM_RUN)|| read_power_status_bit(MSP_PWR_WAIT_RESUMER))
    {
        VOS_Splx(power_lock);
        TLSLEEP_StateRecord(DRX_INVALID_WAKEUP_INT);
        return ERR_MSP_SUCCESS;
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_0);
    TLSLEEP_StateRecord(DRX_WAKEUP_INT);

    set_power_status_bit(MSP_PWR_WAKEUP);
    VOS_SmV(g_msp_pwrctrl.task_sem);

    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_1);
    VOS_Splx(power_lock);
    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : LSLEEP_AwakeIsr
 ��������  : ��ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ERR_MSP_INIT_FAILURE:��ʼ��ʧ��
             ERR_MSP_SUCCESS: ��ʼ���ɹ�
*****************************************************************************/
VOS_INT TLSLEEP_AwakeIsr(VOS_INT enMode)
{
    VOS_INT power_lock = 0;
    VOS_UINT32 ulSwitchLen;
    VOS_UINT32 ulDelay;

    /*��BBP�����ж�*/
    mdrv_bbp_clear_wakeup_intr((PWC_COMM_MODE_E)enMode);

    ulSwitchLen = mdrv_bbp_get_wakeup_time((PWC_COMM_MODE_E)enMode);
    
    g_stSleepSwitch.ulDelay[g_stSleepSwitch.ulPtrWake] = 0xffffffff;

    if((0xffffffff != ulSwitchLen)
        && (0 != g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup)
        && (0 != g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume)
        && (0 != g_msp_pwrctrl.SleepDrxResumeTime.ulInterval))
    {
        if(POWER_SAVING_DEEP_SLEEP == g_msp_pwrctrl.dsp_sleep_flag)
        {
            ulDelay = (g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup + g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume + g_msp_pwrctrl.SleepDrxResumeTime.ulInterval);
        }
        else
        {
            ulDelay = (g_msp_pwrctrl.SleepDrxResumeTime.ulInterval);
        }
        
        if((ulSwitchLen > ulDelay) && ((ulSwitchLen - ulDelay) > 32))
        {
            ulDelay = ulSwitchLen - ulDelay;

            g_stSleepSwitch.ulDelay[g_stSleepSwitch.ulPtrWake] = ulDelay;
            
            if ( VOS_OK == mdrv_timer_start(TIMER_DSP_SWITCH_DELAY_ID, (FUNCPTR_1)TLSLEEP_TimerIsr, TIMER_DSP_SWITCH_DELAY_ID, ulDelay, TIMER_ONCE_COUNT,TIMER_UNIT_NONE) )
            {
                g_stSleepSwitch.ulSliceWakeup[g_stSleepSwitch.ulPtrWake] = VOS_GetSlice();
                g_stSleepSwitch.ulSwitchLen[g_stSleepSwitch.ulPtrWake] = ulSwitchLen;
                g_stSleepSwitch.ulPtrWake = (g_stSleepSwitch.ulPtrWake+1)%100;

                /*ͶƱ���ܽ���˯��*/
                mdrv_pm_wake_lock(PWRCTRL_SLEEP_TLPS);
                return ERR_MSP_SUCCESS;
            }
        }
    }
    
    g_stSleepSwitch.ulSliceWakeup[g_stSleepSwitch.ulPtrWake] = VOS_GetSlice();
    g_stSleepSwitch.ulSwitchLen[g_stSleepSwitch.ulPtrWake] = ulSwitchLen;
    g_stSleepSwitch.ulPtrWake = (g_stSleepSwitch.ulPtrWake+1)%100;

    power_lock = VOS_SplIMP();

    if(read_power_status_bit(MSP_PWR_WAKEUP)||read_power_status_bit(MSP_PWR_FORCE_AWAKE)
      ||read_power_status_bit(MSP_PWR_SYSTEM_RUN)|| read_power_status_bit(MSP_PWR_WAIT_RESUMER))
    {
        VOS_Splx(power_lock);
        TLSLEEP_StateRecord(DRX_INVALID_WAKEUP_INT);
        return ERR_MSP_SUCCESS;
    }
    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_0);
    TLSLEEP_StateRecord(DRX_WAKEUP_INT);

    set_power_status_bit(MSP_PWR_WAKEUP);
    VOS_SmV(g_msp_pwrctrl.task_sem);

    TLSLEEP_DbgTimeRecord(TLSLEEP_AWAKEISR_1);
    VOS_Splx(power_lock);
    return ERR_MSP_SUCCESS;
}


/*****************************************************************************
 �� �� ��  : TLSLEEP_SetChanel
 ��������  : ���ݾɰ汾������ͨ����Ϣ(�ɰ汾�����ֻ֧������ͨ��)
*****************************************************************************/
VOS_VOID TLSLEEP_SetChanel(NV_TLMODE_BASIC_PARA_STRU astChan[2])
{
    VOS_UINT32 i;

    for(i = 0; i < 2; i++)
    {
        /* ����TCXOʹ�õ�ID */
        if(astChan[i].ucABBSwitch >= 2)
        {
            g_msp_pwrctrl.tlmode_channel[i].abb_channel_id = 0x3;
        }
        else
        {
            g_msp_pwrctrl.tlmode_channel[i].abb_channel_id = (VOS_UINT16)(0x1 << astChan[i].ucABBSwitch);
        }
        
        /* ����RFʹ�õ�ͨ�� */
        if(astChan[i].ucRFSwitch >= 2)
        {
            g_msp_pwrctrl.tlmode_channel[i].rf_channel_id = 0x3;
        }
        else
        {
            g_msp_pwrctrl.tlmode_channel[i].rf_channel_id = (VOS_UINT16)(0x1 << astChan[i].ucRFSwitch);
        }
        
        /* ����TCXOʹ�õ�ID */
        if(astChan[i].ucTCXOSwitch >= 2)
        {
            g_msp_pwrctrl.tlmode_channel[i].tcxo_id = 0x3;
        }
        else
        {
            g_msp_pwrctrl.tlmode_channel[i].tcxo_id = (VOS_UINT16)(0x1 << astChan[i].ucTCXOSwitch);
        }
        
        g_msp_pwrctrl.tlmode_channel[i].rf_clk_id = 0;
    }
}
VOS_VOID TLSLEEP_ExcTimeTask(VOS_UINT32 Para0, VOS_UINT32 Para1,
                                VOS_UINT32 Para2, VOS_UINT32 Para3 )
{
    VOS_CHAR                  acLogPath[] = "/modem_log/msp_sleep.txt";
    FILE                      *logfp = NULL;
    VOS_UINT                  count = 0;
    VOS_CHAR                  auLogBuf[40] = {0};

    logfp = mdrv_file_open(acLogPath, "w+");
    if (VOS_NULL_PTR == logfp)
    {
        return;
    }
    mdrv_file_close(logfp);
    /*lint -save -e716*/
    while(1)
    {
    /*lint -restore*/
        if(VOS_OK != VOS_SmP(g_msp_pwrctrl.exc_overtime.time_sem, WAIT_FOR_EVER))
        {
            mspsleep_print_error("take task sem error!");
        }

        /*���ļ�ϵͳ��д������*/
        if((1 == g_msp_pwrctrl.exc_overtime.ulReadMark)&&(g_msp_pwrctrl.exc_overtime.current_count < 8))
        {
            logfp = mdrv_file_open(acLogPath, "a+");
            VOS_sprintf(auLogBuf, "< %d >\r\n", g_msp_pwrctrl.exc_overtime.current_count);
            mdrv_file_write(auLogBuf, sizeof(VOS_CHAR), sizeof(auLogBuf), logfp);
            (g_msp_pwrctrl.exc_overtime.current_count)++;
            for(count = TLSLEEP_DSPHALTISR_0; count <= TLSEEP_HWPOWERUP_MAX; count++)
            {
                VOS_MemSet((VOS_VOID*)auLogBuf, 0, 40);
                VOS_sprintf(auLogBuf, "0x%x  ", g_msp_pwrctrl.exc_overtime.ulTime[count]);
                mdrv_file_write(auLogBuf, sizeof(VOS_CHAR), 12, logfp);
                if(0 == (count + 1)%8)
                {
                    mdrv_file_write("\r\n", sizeof(VOS_CHAR), 2,logfp);
                }
            }
            mdrv_file_write("\r\n", sizeof(VOS_CHAR), 2 ,logfp);
            mdrv_file_close(logfp);
            g_msp_pwrctrl.exc_overtime.ulReadMark= 0;
        }
        else
        {
            return;
        }
    }
}

VOS_VOID TLSLEEP_GetChannelInfo()
{
    VOS_INT status_flag = 0;
    VOS_UINT32 ret;

#if (FEATURE_MODE_FEM_CHAN_EXT == FEATURE_ON)
    UCOM_NV_FEM_CHAN_PROFILE_STRU astChan;   /*lint !e813*/

    UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU stProfile = {0};

    ret = NVM_Read(en_NV_Item_TRI_MODE_FEM_PROFILE_ID, &stProfile, sizeof(UCOM_NV_TRI_MODE_FEM_PROFILE_ID_STRU));
    ret |= NVM_Read(en_NV_Item_FEM_CHAN_PROFILE, &astChan, sizeof(UCOM_NV_FEM_CHAN_PROFILE_STRU));

    /* ����LTE��TDS��ͨ����Ϣ������ */
    if(0 == ret)
    {
        VOS_MemCpy(g_msp_pwrctrl.tlmode_channel,
                    &astChan.astPara[stProfile.uwProfileId].stModeBasicPara[PWC_COMM_MODE_LTE],
                    sizeof(g_msp_pwrctrl.tlmode_channel));
    }

#else
    NV_TLMODE_BASIC_PARA_STRU astChan[2];

    ret = NVM_Read(NV_ID_MSP_TLMODE_CHAN_PARA_STRU, astChan, 2*sizeof(NV_TLMODE_BASIC_PARA_STRU));

    if(0 == ret)
    {
        TLSLEEP_SetChanel(astChan);
    }

#endif

    if(ret)
    {
        /* coverity[lock_acqire] */
        msp_set_error_bit(status_flag, MSP_READ_NV_FAIL);
        mspsleep_print_error("Read NV: channel Data Fail.");
    }
}


/*****************************************************************************
 �� �� ��  : LSLEEP_Init
 ��������  : ��ʼ��
 �������  : void
 �������  : ��
 �� �� ֵ  : ERR_MSP_INIT_FAILURE:��ʼ��ʧ��
             ERR_MSP_SUCCESS: ��ʼ���ɹ�
*****************************************************************************/
VOS_UINT32 TLSLEEP_Init(VOS_VOID)
{
    VOS_UINT32 Argument[VOS_TARG_NUM];
    VOS_UINT32 ExcArgument[VOS_TARG_NUM];
    int status_flag = 0;
	int lte_int_num = 0, tds_int_num = 0, ret = 0;
    unsigned int debug_len = 0;
    VOS_UINT_PTR realAddr = 0;
    VOS_UINT32 ulSize;
    
#ifndef MSP_IN_V9R1
    g_msp_pwrctrl.dump_len = 0x1000;
    g_msp_pwrctrl.dump_base = (VOS_VOID * )mdrv_om_register_field(OM_CP_MSP_SLEEP, "tl_sleep", (void*)0, (void*)0, 0x1000, 0);

    if(VOS_NULL == g_msp_pwrctrl.dump_base)
    {
        mspsleep_print_error("get exc buffer error,module id = %d", OM_CP_MSP_SLEEP);
        g_msp_pwrctrl.dump_base = (VOS_VOID * )VOS_UnCacheMemAlloc(g_msp_pwrctrl.dump_len, &realAddr);
    }
#else
    {
        g_msp_pwrctrl.dump_len = 0x1000;
        g_msp_pwrctrl.dump_base = (VOS_VOID * )VOS_UnCacheMemAlloc(g_msp_pwrctrl.dump_len, &realAddr);
    }
#endif
    if(VOS_NULL != g_msp_pwrctrl.dump_base)
    {
        VOS_MemSet((void *)g_msp_pwrctrl.dump_base, 0, g_msp_pwrctrl.dump_len);
        /*��ʼ����ά�ɲ�*/
        debug_len = (VOS_UINT)MSP_EXC_RECORED_TIME_SIZE;
        g_msp_pwrctrl.time_queue_record = (drx_queue_t*)(MSP_EXC_RECORED_TIME_OFFSET);
        QueueInit(g_msp_pwrctrl.time_queue_record, (debug_len - 0x10)/sizeof(DRX_RECORD_STRU));
        g_msp_pwrctrl.DrxStateSlice = (SLEEP_RECORD_STRU*)(MSP_EXC_STATE_SLICE_OFFSET);
        g_msp_pwrctrl.DrxStateEnd = MSP_EXC_STATE_SLICE_OFFSET + MSP_EXC_STATE_SLICE_SIZE;
        g_msp_pwrctrl.dsp_state = (DspState *)MSP_EXC_DSP_STATE_OFFSET;
    }
    g_msp_pwrctrl.exc_overtime.timeOut = 45;

    g_msp_pwrctrl.pwr_status = 0;

    if(VOS_OK != VOS_SmBCreate("EXC", 0, VOS_SEMA4_FIFO, &g_msp_pwrctrl.exc_overtime.time_sem))
    {
        mspsleep_print_error("SLEEP_Init: Create EXC SEM Fail.");
        return ERR_MSP_INIT_FAILURE;
    }

    if(VOS_OK != VOS_SmBCreate("TC_0", 0, VOS_SEMA4_FIFO, &g_msp_pwrctrl.SleepTcxoSem[0]))
    {
        msp_set_error_bit(status_flag, MSP_CREATE_TCXO0_SEM_FAIL);
        mspsleep_print_error("SLEEP_Init: Create TCXO 0 Fail.");
        return ERR_MSP_INIT_FAILURE;
    }
    if(VOS_OK != VOS_SmBCreate("TC_1", 0, VOS_SEMA4_FIFO, &g_msp_pwrctrl.SleepTcxoSem[1]))
    {
        msp_set_error_bit(status_flag, MSP_CREATE_TCXO1_SEM_FAIL);
        mspsleep_print_error("SLEEP_Init: Create TCXO 1 Fail.");
        return ERR_MSP_INIT_FAILURE;
    }
#ifndef MSP_IN_V9R1
    /* ��ȡdelay nv */
    if(NVM_Read(NV_ID_DRV_DRX_DELAY, &g_msp_drx_delay, sizeof(DRV_DRX_DELAY_STRU)))
    {
        memset(&g_msp_drx_delay, 0x0, sizeof(DRV_DRX_DELAY_STRU));
    }
#endif
    /* ��ȡNV�����ȶ�ʱ�� */
    if(NVM_Read(NV_ID_MSP_TL_DRX_RESUME_TIME, &g_msp_pwrctrl.SleepDrxResumeTime, sizeof(NV_TL_DRX_RESUME_TIME_STRU)))
    {
        g_msp_pwrctrl.SleepDrxResumeTime.ulTcxoRsmTime = 3000;
        g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup = 0;
        g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume = 0;
        g_msp_pwrctrl.SleepDrxResumeTime.ulInterval = 0;
        /* coverity[lock_acqire] */
        msp_set_error_bit(status_flag, MSP_READ_NV_FAIL);
        mspsleep_print_error("Read NV: 0x%x Data Fail.", NV_ID_MSP_TL_DRX_RESUME_TIME);
    }
    else
    {
        g_stSleepSwitch.ulMspPowerup = g_msp_pwrctrl.SleepDrxResumeTime.ulMspPowerup;
        g_stSleepSwitch.ulDspTcmResume = g_msp_pwrctrl.SleepDrxResumeTime.ulDspTcmResume;
        g_stSleepSwitch.ulInterval = g_msp_pwrctrl.SleepDrxResumeTime.ulInterval;
    }
    
    TLSLEEP_GetChannelInfo();
    
    /*�����ź�����ʼ��*/
    if(VOS_SmBCreate( "SLEEP", 0, VOS_SEMA4_FIFO , &g_msp_pwrctrl.task_sem))
    {
        msp_set_error_bit(status_flag, MSP_CREATE_TASK_SEM_FAIL);
        mspsleep_print_error("create task sem failed");
        return ERR_MSP_INIT_FAILURE;
    }
    /* ��ʼ��exc���������ڻ��ѳ�ʱ��ʱ�����ļ�ϵͳ��д�뻽�ѵ�ʱ���¼*/
    /* coverity[sleep] */
	if(VOS_CreateTask("mspExcTask", &g_msp_pwrctrl.exc_overtime.timeTaskId, TLSLEEP_ExcTimeTask, MSP_EXC_TASK_PRI, 2048, ExcArgument))
	{
		mspsleep_print_error("create Exc task failed");
	}
    /* ��ʼ��˯������*/
    /* coverity[sleep] */
	if(VOS_CreateTask("mspSleepTask", &g_msp_pwrctrl.task_id, TLSLEEP_SleepTask, MSP_SLEEP_TASK_PRI, 32768, Argument))
	{
        msp_set_error_bit(status_flag, MSP_CREATE_TASK_FAIL);
		mspsleep_print_error("create msp task failed");
	}

    /*��������ע��ӿ�ע���鵱ǰ������˯�ߺ�ע��ǿ�ƻ��ѽӿں���*/
    BSP_MailBox_GetDspStatusReg((BSP_MBX_GET_STATUS_FUNC)TLSLEEP_RttIsSleep);
    BSP_MailBox_DspForceAwakeReg(TLSLEEP_RttForceAwake);
#ifdef CONFIG_DFS_DDR
    /*Ϊ�����dsp����ָ��ٶȣ�austin�汾���Ӷ�DDR�ĵ�Ƶ����*/
    ret  = TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, TLSLEEP_DFS_DDR_75M, &dfs_ddr_req_id);
    if(ret)
    {
        set_power_status_bit(MSP_DFS_REQUEST_FAIL);/* [false alarm]:����Fortify */
        mspsleep_print_error("request dfs fai, ret = %d\n", ret);
    }
#endif

#ifdef MSP_IN_V9R1
    ret += TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_BUS_MINFREQ_E, TLSLEEP_DFS_BUS_75M, &dfs_bus_req_id);
    ret += TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, TLSLEEP_DFS_DDR_75M, &dfs_ddr_req_id);
    ret += TLSLEEP_DfsQosRequest((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, TLSLEEP_DFS_CCPU_150M, &dfs_ccpu_req_id);/* [false alarm]:����Fortify */
    if(ret)
    {
        set_power_status_bit(MSP_DFS_REQUEST_FAIL);/* [false alarm]:����Fortify */
        mspsleep_print_error("request dfs fai, ret = %d\n", ret);
    }
#endif
    mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_LTE);
    mdrv_bbp_clear_wakeup_intr(PWC_COMM_MODE_TDS);
    mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_LTE);
    mdrv_bbp_disable_wakeup_intr(PWC_COMM_MODE_TDS);
	lte_int_num = mdrv_int_get_num(BSP_INT_TYPE_LBBP_AWAKE);
	tds_int_num = mdrv_int_get_num(BSP_INT_TYPE_TBBP_AWAKE);

    ret =  mdrv_int_connect(lte_int_num, (VOIDFUNCPTR)TLSLEEP_AwakeIsr, (VOS_INT)PWC_COMM_MODE_LTE);
    ret += mdrv_int_connect(tds_int_num, (VOIDFUNCPTR)TLSLEEP_AwakeIsr, (VOS_INT)PWC_COMM_MODE_TDS);

    ret += mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_INT_DSP_HALT, TLSLEEP_DspHaltIsr, 0);
    ret += mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_INT_DSP_RESUME, TLSLEEP_DspResumeIsr, 0);
    ret += mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_INT_WAKE_GSM, (VOIDFUNCPTR)SLEEP_MasterWakeSlave, (VOS_UINT)PWC_COMM_MODE_GSM);
    ret += mdrv_ipc_int_connect((IPC_INT_LEV_E)IPC_INT_WAKE_WCDMA, (VOIDFUNCPTR)SLEEP_MasterWakeSlave, (VOS_UINT)PWC_COMM_MODE_WCDMA);
    if(ret)
    {
        msp_set_error_bit(status_flag, MSP_INT_CONNECT_FAIL);
		mspsleep_print_error("int connect fail!");
		return ERR_MSP_INIT_FAILURE;
    }
    ret = mdrv_int_enable(lte_int_num);
    ret += mdrv_int_enable(tds_int_num);
    ret += mdrv_ipc_int_enable(IPC_INT_DSP_HALT);
    ret += mdrv_ipc_int_enable(IPC_INT_DSP_RESUME);
    ret += mdrv_ipc_int_enable(IPC_INT_WAKE_GSM);
    ret += mdrv_ipc_int_enable(IPC_INT_WAKE_WCDMA);
    if(ret)
    {
        msp_set_error_bit(status_flag, MSP_INT_ENABLE_FAIL);
		mspsleep_print_error("int connect fail!");
		return ERR_MSP_INIT_FAILURE;
    }

    ret = mdrv_getmeminfo(BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG, (VOS_UINT32 *)(&g_pstRttSleepInfo), &ulSize);
    if(ret)
    {
		mspsleep_print_error("mdrv_getmeminfo BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG fail!");
		return ERR_MSP_INIT_FAILURE;
    }
    VOS_MemSet((void *)g_pstRttSleepInfo, 0, ulSize);

    ret = mdrv_getmeminfo(BSP_DDR_TYPE_SHM_TIMESTAMP, &g_ulAddrShrDdr, &ulSize);
    if(ret)
    {
		mspsleep_print_error("mdrv_getmeminfo BSP_DDR_TYPE_SHM_TIMESTAMP fail!");
		return ERR_MSP_INIT_FAILURE;
    }

    /*��ʼ����DSP֮��ı�־��CCPU���µ�Ҫ�ж������־�����Ƿ��TCXO���µ�*/
    g_pstRttSleepInfo->ulLightSleepFlag = POWER_SAVING_NULL;
    VOS_FlushCpuWriteBuf();

    mspsleep_print_error("msp sleep init OK!");

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : bsp_mailbox_init
 ��������  : ��ģ���Ѵ�ģ�Ľӿ�,LΪ��ģ����GU����,msp�ṩ,oam����
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID)
{
    TLSLEEP_StateRecord(DRX_SLAVE_WAKE_INT);
    TLSLEEP_RttForceAwake();
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_InitPowerUp
 ��������  : �ṩ��Э��ջ���ã�������DSP����֮ǰ���ã�������Щ������Ĭ�����ϵ��
             ��Ҫ�������Ϊ�ϵ�״̬
 �������  : None
 �������  : None
 �� �� ֵ  : None
*****************************************************************************/
VOS_VOID TLSLEEP_ActivateHw(PWC_COMM_MODE_E modeId)
{
    PWC_COMM_MODEM_E                    enModem = PWC_COMM_MODEM_0;
#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)
    PWC_COMM_CHANNEL_E                  enChannel = PWC_COMM_CHANNEL_0;
#endif
    VOS_INT32                           ret = 0;
    VOS_INT                             flag = 0;
    VOS_UINT32                          timestamp_begin = 0;
    VOS_UINT32                          timestamp_end = 0;
	enModem = PWC_COMM_MODEM_0;

    TLSLEEP_OpenTCXO();
#if (FEATURE_MULTI_CHANNEL == FEATURE_ON)

    ret = TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id,TLSLEEP_DFS_CCPU_600M);/* [false alarm]:����Fortify */
    if(ret)
    {
        set_power_status_bit(MSP_DFS_HW_UPDATE_FAIL);/* [false alarm]:����Fortify */
    }

    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    /* Э��ջ����ʱ����ʹ��PLL���ٸ�BBP�ϵ硢���� */
    mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);

    /* TDS��BBP�ϵ�ӿ���ͬʱ��CS/PS���������ϵ磬LTE�����ĵ���DSP���� */
    /* LTEģʽҲ����CS/PS����������CS/PS����LTE��ģҲ�����ϵ� */
    mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /*��TDS ʹ�õ�BBP 1A����ʱ��*/
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    /* LTE�漰���ʱ��Դ��DSPֻ����һ���֣���ҪMSP���õ���ӿڴ�LTE�������ʱ�� */
    mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);

    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);

#else

#ifdef MSP_IN_V9R1
    /*DDR������Ƶ����СֵΪ150M,V9R1ʹ��*/
    ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_BUS_MINFREQ_E, dfs_bus_req_id, TLSLEEP_DFS_BUS_150M);
    ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_DDR_MINFREQ_E, dfs_ddr_req_id, TLSLEEP_DFS_DDR_150M);
    ret += TLSLEEP_DfsQosUpdate((VOS_INT32)DFS_QOS_ID_CCPU_MINFREQ_E, dfs_ccpu_req_id,TLSLEEP_DFS_CCPU_600M);
    if(ret)
    {
        set_power_status_bit(MSP_DFS_HW_UPDATE_FAIL);
    }
#endif   
	/*RF��Դ�ϵ�Ҫ����RFPLLenable������Ҫ���200us*/
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
    timestamp_begin = mdrv_timer_get_normal_timestamp();
    ret = mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0);
    ret += mdrv_pm_enable_pllclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBE16, enModem, PWC_COMM_CHANNEL_0); 
    if(ret)
    {
        mspsleep_print_error("bbe16 pll_enable fail!");
    }
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    ret = mdrv_pm_pwrup(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    ret += mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    if(ret)
    {
        mspsleep_print_error("bbp powerup fail!");
    }
    /*��TDS ʹ�õ�BBP 1A����ʱ��*/
    ret = mdrv_pm_enable_bbpclk(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    ret += mdrv_pm_enable_bbpclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    ret += mdrv_pm_enable_pllclk(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, PWC_COMM_CHANNEL_0);
    if(ret)
    {
        mspsleep_print_error("bbp_pllclk_enable fail!");
    }
    
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB);
    
    ret = mdrv_pm_pwrup(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_FEM, enModem, PWC_COMM_CHANNEL_0);
    if(ret)
    {
        mspsleep_print_error("FEM powerup fail!");
    }

#ifdef CONFIG_PASwitch_V7R5    

    /*  PA ֻ���V7R5��������߹���bug  */
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_PA);
    TLSLEEP_PwrctrlUp(PWC_COMM_MODE_TDS, PWC_COMM_MODULE_PA);
#endif
    /*RF��Դ�ϵ�Ҫ����RFPLLenable������Ҫ���200us*/
    do
    {
        timestamp_end = mdrv_timer_get_normal_timestamp();
    }while((msp_get_timer_slice_delta(timestamp_begin, timestamp_end)) < 7);
    
    TLSLEEP_PllEnable(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF);
    
    /*ȫϵͳ��ʼ���ϵ����ET��ʼ��*/
    RTTAGENT_EtSignalingInit();
#endif
    flag = VOS_SplIMP();
    set_power_status_bit(MSP_PWR_SYSTEM_RUN);
    VOS_Splx(flag);

    return;
}

VOS_VOID TLSLEEP_ResumeDsp(VOS_VOID)
{
    mdrv_dsp_stop_bbe();
    mdrv_dsp_reset_bbe();
    mdrv_dsp_unreset_bbe();
    TLSLEEP_RunDsp();
}

/*****************************************************************************
 �� �� ��  : TLSLEEP_GetPreSfn
 ��������  : �˽ӿ����ڶ�ȡDSP�ڽ���˯��ǰ�����TDS������ţ�Ŀǰ���������˵͹�����ʹ�õ�SRAM�ռ���
 �������  : VOS_VOID
 �������  : DSP�ڽ���˯��ǰ�����TDS�������,PS����
 �� �� ֵ  : DSP�ڽ���˯��ǰ�����TDS�������,PS����
*****************************************************************************/
VOS_UINT32 TLSLEEP_GetPreSfn(VOS_VOID)
{
    VOS_INT32 ret;
    VOS_UINT32 ulSize;
    RTT_SLEEP_INFO_STRU *pstRttSleepInfo = 0;

    if(VOS_NULL_PTR == g_pstRttSleepInfo)
    {
        ret = mdrv_getmeminfo(BSP_DDR_TYPE_SRAM_RTT_SLEEP_FLAG, (VOS_UINT32 *)pstRttSleepInfo, &ulSize);
        if(ret)
        {
            return 0;
        }
    }
    else
    {
        pstRttSleepInfo = g_pstRttSleepInfo;
    }

    if(VOS_NULL_PTR == pstRttSleepInfo)
    {
        return 0;
    }
    
    return pstRttSleepInfo->ulTdsPreSfn;
}
/*****************************************************************************
 �� �� ��  : LSLEEP_ShowStat
 ��������  :
 �������  : void
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TLSLEEP_ShowStat(VOS_UINT32 ulIndex)
{
    VOS_UINT i = 0, bbp_pll = 0, bbp_ldo = 0;
    PWC_COMM_MODEM_E                    enModem = PWC_COMM_MODEM_0;
    PWC_COMM_CHANNEL_E                  enChannel = PWC_COMM_CHANNEL_0;
    VOS_INT                             ulTcxoStatus[2] = {0};
    VOS_UINT32                          abb_pll[2] = {0};
    VOS_UINT32                          rf_ldo[2] = {0};
	enModem = PWC_COMM_MODEM_0;
    bbp_pll = (VOS_UINT)mdrv_pm_get_pllclk_status(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    abb_pll[0] = (VOS_UINT32)mdrv_pm_get_pllclk_status(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB, PWC_COMM_MODEM_0, enChannel);
    abb_pll[1] = (VOS_UINT32)mdrv_pm_get_pllclk_status(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_ABB, PWC_COMM_MODEM_1, enChannel);

    rf_ldo[0] = (VOS_UINT32)mdrv_pm_get_pwrstatus(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF, PWC_COMM_MODEM_0, enChannel);
    rf_ldo[1] = (VOS_UINT32)mdrv_pm_get_pwrstatus(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_RF, PWC_COMM_MODEM_1, enChannel);
    bbp_ldo = (VOS_UINT)mdrv_pm_get_pwrstatus(PWC_COMM_MODE_LTE, PWC_COMM_MODULE_BBP_DRX, enModem, enChannel);
    ulTcxoStatus[0] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_0);
    ulTcxoStatus[1] = mdrv_pm_get_tcxo_status(PWC_COMM_MODEM_1);
    /*lint -save -e713 -e574*/
    vos_printf("RTT SLEEP Show Statistics Info:\n");

    vos_printf("Sleep system state: 0x%x\n", read_power_status_bit(MSP_PWR_SYSTEM_RUN));
    vos_printf("BBP Pll state:      0x%x\n", bbp_pll);
    vos_printf("ABB CHN0 Pll state: 0x%x\n", abb_pll[0]);
    vos_printf("ABB CHN1 Pll state: 0x%x\n", abb_pll[1]);

    vos_printf("RF LDO0 state:       0x%x\n",rf_ldo[0]);
    vos_printf("RF LDO1 state:       0x%x\n",rf_ldo[1]);

    vos_printf("BBP LDO state:      0x%x\n",bbp_ldo);
    vos_printf("TCXO 0 state :      0x%x\n",ulTcxoStatus[0]);
    vos_printf("TCXO 1 state:      0x%x\n",ulTcxoStatus[1]);
    vos_printf("\n");

    vos_printf("Sleep Cmd mask:     0x%x\n",g_msp_pwrctrl.pwr_status);
    vos_printf("Deep Sleep Flag:     0x%x\n",g_msp_pwrctrl.dsp_sleep_flag);
    vos_printf("Last is sleep value: 0x%x\n", g_msp_pwrctrl.RttIsSleepValue);
    vos_printf("Forbid Dsp value: 0x%x\n", g_msp_pwrctrl.ForbidDspSleepValue);

    vos_printf("\n");
    if(VOS_NULL != g_msp_pwrctrl.DrxStateSlice)
    {
    vos_printf("DSP Halt Int:       Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_HALT_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_HALT_INT].ulSlice);
    vos_printf("SLEEP task:         Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_TASK].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_SLEEP_TASK].ulSlice);
    vos_printf("Sleep NeedNot Deal: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[SLEEP_TASK_NOT_NEED_DEAL].ulCount,g_msp_pwrctrl.DrxStateSlice[SLEEP_TASK_NOT_NEED_DEAL].ulSlice);
    vos_printf("DSP deep sleep:     Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DSP_DEEP_SLEEP_COUNT].ulCount,g_msp_pwrctrl.DrxStateSlice[DSP_DEEP_SLEEP_COUNT].ulSlice);
    vos_printf("DSP liaght sleep:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DSP_LIGHT_SLEEP_COUNT].ulCount,g_msp_pwrctrl.DrxStateSlice[DSP_LIGHT_SLEEP_COUNT].ulSlice);
	vos_printf("Store DspMem Fail:  Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[STORE_DSP_TCM_FAIL].ulCount,g_msp_pwrctrl.DrxStateSlice[STORE_DSP_TCM_FAIL].ulSlice);
    vos_printf("Vote sleep:         Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[SLEEP_VOTE_UNLOCK].ulCount,g_msp_pwrctrl.DrxStateSlice[SLEEP_VOTE_UNLOCK].ulSlice);
    vos_printf("Invalid Wake Int:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_INVALID_WAKEUP_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_INVALID_WAKEUP_INT].ulSlice);
    vos_printf("Wake Int:           Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_WAKEUP_INT].ulSlice);
	vos_printf("Restore DspMem Fail Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[RESTORE_DSP_TCM_FAIL].ulCount,g_msp_pwrctrl.DrxStateSlice[RESTORE_DSP_TCM_FAIL].ulSlice);
    vos_printf("Force Awake API:    Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_API].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_API].ulSlice);
    vos_printf("Force Not Nedd Deal   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_NOT_DEAL].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_NOT_DEAL].ulSlice);
    vos_printf("Force Awake Dsp Run:Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_RUN_RETURN].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FORCE_AWAKE_RUN_RETURN].ulSlice);
    vos_printf("Wait Tcxo Sem Fail: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_FAIL_WAIT_TCXO_SEM].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_FAIL_WAIT_TCXO_SEM].ulSlice);
    vos_printf("Resume Notify Mail: Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[RESUME_NOTIFY_MAILBOX].ulCount,g_msp_pwrctrl.DrxStateSlice[RESUME_NOTIFY_MAILBOX].ulSlice);
    vos_printf("DSP Resume Int:     Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_RESUME_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_RESUME_INT].ulSlice);
	vos_printf("SLAVE Wake Int:     Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_SLAVE_WAKE_INT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_SLAVE_WAKE_INT].ulSlice);
	vos_printf("Check Dsp Status:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_CHECK_DSP_STATUS].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_CHECK_DSP_STATUS].ulSlice);
	vos_printf("Sleep Flag Error:   Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DSP_SLEEP_FLAG_ERROR].ulCount,g_msp_pwrctrl.DrxStateSlice[DSP_SLEEP_FLAG_ERROR].ulSlice);
	vos_printf("Halt Resume Conflict:Count 0x%08x, Slice 0x%08x\n",g_msp_pwrctrl.DrxStateSlice[DRX_HALT_RESUME_CONFLICT].ulCount,g_msp_pwrctrl.DrxStateSlice[DRX_HALT_RESUME_CONFLICT].ulSlice);
    }
    if (0 != ulIndex)
    {
        vos_printf("\n");
        vos_printf("==========================================================\n");
        vos_printf("Time Record: count 0x%x position %d\n",g_msp_pwrctrl.SleepTimeRecord.ulCount,((g_msp_pwrctrl.SleepTimeRecord.ulCount-1)%SLEEP_RECORD_NUM));
        vos_printf("Num   Type               Time\n");
        for (i=0; i<(g_msp_pwrctrl.SleepTimeRecord.ulCount < SLEEP_RECORD_NUM ? g_msp_pwrctrl.SleepTimeRecord.ulCount : SLEEP_RECORD_NUM); i++)
        {
            vos_printf("%03d   %16s   0x%08x\n",i ,(VOS_INT)g_msp_pwrctrl.SleepTimeRecord.astRecord[i].acType, g_msp_pwrctrl.SleepTimeRecord.astRecord[i].ulTime);
        }
    }
    vos_printf("dbg time record addr = 0x%08x\r\n", (VOS_UINT)g_msp_pwrctrl.dbg_time_record);
    vos_printf("queue time record addr = 0x%08x\r\n", (VOS_UINT)g_msp_pwrctrl.time_queue_record->data);
    vos_printf("drx state slice addr = 0x%08x\r\n", (VOS_UINT)g_msp_pwrctrl.DrxStateSlice);
    vos_printf("timestamp shared memory address = 0x%08x\r\n", g_ulAddrShrDdr);
    /*lint -restore*/

}

/*****************************************************************************
 �� �� ��  : TLSLEEP_ShowDebugTime
 ��������  :
 �������  : void
 �������  : ��
 �� �� ֵ  : ��ά�ɲ⺯�����ڴ�ӡ���µ�����е�ʱ���
 ���ú���  :
 ��������  :
*****************************************************************************/
VOS_VOID TLSLEEP_ShowDebugTime(VOS_INT mode)
{
    EN_SLEEP_TIME_RECORD i = TLSLEEP_RTTSLEEP_INNER_0;
    VOS_UINT32 count = 0;

    vos_printf("%s:\n", "sleep:", 0, 0, 0, 0, 0);
    for(i = TLSLEEP_DSPHALTISR_0; i <= TLSLEEP_RTTSLEEP_INNER_MAX; i++)
    {
        vos_printf("%08x  ", g_msp_pwrctrl.dbg_time_record[i], 0, 0, 0, 0, 0);
    }
    vos_printf("\n%s:\n", "wake", 0, 0, 0, 0, 0);/* [false alarm]:����Fortify */
    for(i = TLSLEEP_AWAKEISR_0, count = 0; i <= TLSLEEP_DSPRESUMERISR_MAX; i++)
    {
        vos_printf("%08x  ", g_msp_pwrctrl.dbg_time_record[i], 0, 0, 0, 0, 0);
        count++;
        if(count%8 == 0)
        {
            vos_printf("\n", 0, 0, 0, 0, 0, 0);
        }
    }
}


VOS_VOID TLSLEEP_ShowPowerTime(VOS_VOID);

VOS_VOID TLSLEEP_ShowPowerTime(VOS_VOID)
{
    VOS_UINT32 i = 0;
    VOS_UINT32 start = 0, end = 0;
    
    mdrv_pm_wake_lock(PWRCTRL_SLEEP_TLPS);

    for(i = 0; i < ((VOS_UINT)MSP_EXC_RECORED_TIME_SIZE / sizeof(DRX_RECORD_STRU)); i++)
    {
        if(g_msp_pwrctrl.time_queue_record->data[i].ulState < TLSLEEP_FORCE_AWAKE_INNER_0)
        {
            continue;
        }

        if(TLSLEEP_FORCE_AWAKE_INNER_0 == g_msp_pwrctrl.time_queue_record->data[i].ulState)
        {
            start = g_msp_pwrctrl.time_queue_record->data[i].ulSlice;
            vos_printf("\n %08x      ", g_msp_pwrctrl.time_queue_record->data[i].ulSlice);
        }
        else if(g_msp_pwrctrl.time_queue_record->data[i].ulState < TLSLEEP_FORCE_AWAKE_INNER_1)
        {
            vos_printf("%08x      ", g_msp_pwrctrl.time_queue_record->data[i].ulSlice);
        }
        else if(TLSLEEP_FORCE_AWAKE_INNER_1 == g_msp_pwrctrl.time_queue_record->data[i].ulState)
        {
            end = g_msp_pwrctrl.time_queue_record->data[i].ulSlice;
            vos_printf("%08x     (%08x)\n", g_msp_pwrctrl.time_queue_record->data[i].ulSlice, (end - start));
        }
        else
        {
            continue;
        }
    }
    
    mdrv_pm_wake_unlock(PWRCTRL_SLEEP_TLPS);

    return;
}


#else
VOS_UINT32 TLSLEEP_Init(VOS_VOID)
{
    return VOS_OK;
}
VOS_BOOL TLSLEEP_RttIsSleep(VOS_VOID)
{
    return VOS_FALSE;
}
VOS_VOID TLSLEEP_RttForceAwake(VOS_VOID)
{
}

VOS_VOID TLSLEEP_MasterAwakeSlave(VOS_VOID)
{
}

VOS_VOID TLSLEEP_ActivateHw(PWC_COMM_MODE_E modeId)
{
}

VOS_UINT32 TLSLEEP_GetPreSfn(VOS_VOID)
{
    return 0;
}

#endif
/*lint +e409*/

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


