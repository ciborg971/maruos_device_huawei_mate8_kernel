
/*lint --e{944,506,525,64,119,101,132,537,958,438,830,752,762,713,732,569,830,525,539,650,652,69,502}*/

#include "osl_thread.h"
#include "osl_sem.h"
#include "osl_malloc.h"
#include "osl_cache.h"
#include <string.h>
#include "product_config.h"
#include "osl_types.h"
#include "osl_bio.h"
#include "securec.h" 
#include "soc_interrupts.h"
#include "drv_nv_id.h"
#include "mdrv_timer.h"
#include "mdrv_sci.h"
#include "mdrv_public.h"
#include "bsp_om.h"
#include "of.h"
#include "bsp_regulator.h"
#include "bsp_edma.h"
#include "bsp_clk.h"
#include "bsp_nvim.h"
#include "bsp_icc.h"
#include "bsp_pmu.h"
#include "bsp_dump.h"
#include "bsp_dump_def.h"
#include "bsp_sci.h"
#include "sci_debug.h"
#include "sci_pl131.h"
#include "sci_apbitops.h"
#include "sci_appl131.h"

extern SCI_API_MODE sci_api_mode;


#ifndef WAIT_FOREVER
#define WAIT_FOREVER    (-1)
#endif


/*
 * Description:
 * var for block receive
 */
#define T1_PROLOGUE_SIZE 3
u32 g_sci_BWT_int_flag = 0;
#define SCI_TIMEOUT       1

/*
 * Description:
 * SCI stae
 */
SCI_STATE_STRU g_strSciState = {PL131_STATE_UNINIT};

/*
 * Description:
 * Buffer in driver layer
 */
SCI_REC_DATA g_strRecBuf = {0};

/*
 * Description:
 * sci deactive way
 */
u32 g_sci_api_deactive = 0;


/*PV400��֧��DMA����ģʽ���˴��ú����������Ժ�6910����DMA
  ����ģʽ����PV400���벻�����Ӱ��*/
SCI_RX_STATE_STRU g_sciRxStGblStru = {SCI_RX_CPU_MODE, -1, SCI_RX_DATA_REC_OVER};

/* �ص�����ע���¼����Ͳ���*/
u32 g_u32Event;

/* �ص�����ע�ắ��ָ��*/
Sci_Event_Func g_FuncCb;


u32 g_SciExcResetTimes = 0;

OMSCIFUNCPTR g_omSciFuncPtr = NULL;

/*
 * Description:
 * Enable WWT Time Out Deactivation Issue
 */
u32 g_ulChTOUTDeactEn  = 0;
u32 g_ulSciGcfStubFlag = 0;

/*
 * Description:
 * Flag of SCI Clock Time Stop Status
 */
apPL131_eClockMode g_ulSciClkTimeStpFlag = apPL131_CLOCK_START;

/*
 * Description:
 * Flag for SIM card deactivation process
 */
BSP_BOOL g_SciDeactivateFlag = BSP_FALSE;

u32 g_u32ResetSuccess = SCI_DEF_NOT_RESET;

/*��ȡ���ݱ�־����֤Ԥ�����ȡ��������������ֻ����һ�λص�����*/
u32 g_u32ReadFlag = SCI_DEF_READ_FORBID;

/* pmu */
struct regulator *g_sciPmuRegu = NULL;


/* sci vote ctrl flag */

BSP_BOOL g_sci_lp_vote_flag = BSP_TRUE;

/* ����ȫ�ֽṹ���¼SCI��Ӳ��������Ϣ���ŵ�ָ���Ķ��� */
SCI_CFG_STRU __sci_cfg_data g_stSciHwCfg = {0};

/*#pragma section DATA  ".sci.init.data"*/
/* ����ȫ�ֵĺ���ָ�룬��¼SCI_Init�����ĵ�ַ���ŵ�ָ���Ķ���*/
void * __sci_init_data g_fp_sci_init = (void *)sci_init;


SCI_VOLTAGE_STATE g_sci_voltage_state = {PL131_SCI_Class_BUTT,SCI_CLASS_SWITCH_NONE,SCI_VOLTAGE_SWITCH_SENSE_CLASS_BUTT,ATR_IND_CLASS_NONE};

/* sci debug global varis */
extern sci_debug_str  g_sci_debug_base;
/*
 * Description:
 * ATR Buffer in driver layer
 */
extern ATR_sBuffer g_strATRData;
extern SCI_ATRINFO_S g_sci_atr_info;
extern PL131_T1_TIMES g_t1_times;

/*add detect global var*/
/*the new state*/
SCI_DETECT_STATE_E g_sci_detect_state = SIM_CARD_IDLE;

SCI_DETECT_STATE_E g_sci_ind_state = SIM_CARD_IDLE;

/*the hot plug state machine*/
SCI_HOT_PLUG_PROC_STATUS g_sci_hot_plug_proc_status = SCI_HOT_PLUG_IDEL;

/*
 * Description:
 * Limitted the activation times
 */
extern u8 nActiveT;
extern PL131_PPS_STATE g_Pl131_pps_state ;

/* Debug Regs */
extern u8* g_sciRegGblAddr;
extern unsigned int g_SciNVValue;
SCI_HW_ABNORMAL_E g_sci_hw_abnormal = SCI_HW_STATE_OK;
extern const char * g_pcCardRecordFileName[2];
extern const char * g_pcCardTaskName[2];
SCI_CFG_STRU  g_sci_cur_cfg[3]={{0,},{0,},{0,}};
u32 g_sci_lowpower_vote_state = 0;



void sci_int_handler(void);
void sci_rec_sync_task(void);
void sci_buf_clear(void);
s32 sci_detect_cb(u32 channel_id, u32 len, void *context);
u32 bsp_sci_reg_event(u32 u32Event, Sci_Event_Func pFunc);
s32 sci_buf_add(u8 * pucRecbyte);
s32  sci_rx_dma_start(u32* u32DstAddr, u32 u32TransLength);
u32 sci_count_length(void);
s32 sci_clock_stop_mode_cfg( u32 ucClockStopMode, u32 ucClockStopInd);
void sci_reg_event(u32 u32Event, Sci_Event_Func pFunc);
void sci_class_switch_sence_try(void);
s32 sci_set_voltage(SCI_VOLTAGE_SWITCH_DIRECTION direction);
s32 sci_warm_reset(void);
s32 sci_cold_reset(void);
void sci_hot_plug_task(void);
void sci_check_current_state(PL131_eStateOptions eCurrentState);
void sci_atr_clear(void);
extern void sci_print_cfg(SCI_CFG_STRU* p_sci_cfg);



void sci_set_api_llt_mode(void)
{
    sci_api_mode = SCI_API_LLT;
}
void sci_clear_api_llt_mode(void)
{
    sci_api_mode = SCI_API_NORMAL;
}

void sci_rst_global_on_init(void)
{
    g_sci_detect_state = SIM_CARD_IDLE;
    g_sci_ind_state = SIM_CARD_IDLE;
    g_sci_hot_plug_proc_status = SCI_HOT_PLUG_IDEL;
    g_SciDeactivateFlag = BSP_FALSE;
    g_sci_lowpower_vote_state = 0;
}

void sci_init_pps_global(void)
{
    /*set pps related parameters as default value*/
    g_Pl131_pps_state.PL131_PPS_ACTIVATION = 0;
    g_Pl131_pps_state.ucTA1Flag = 0;
    g_Pl131_pps_state.ucPPSFlag = 0;
    g_Pl131_pps_state.PL131_PPS_Response = 0;

    g_u32ResetSuccess = SCI_DEF_NOT_RESET;

}

void sci_init_t1_global(void)
{
    g_sci_atr_info.Tbyte = T0_PROTOCOL_MODE;
    g_strSciState.eProtocol = apPL131_PROTOCOL_T0_CHAR;
    g_sci_atr_info.valIFSC = 32;
    g_sci_atr_info.valIFSD = 32;
    g_sci_atr_info.errDetectMode = T1_ERR_DETECT_MODE_LRC;
    g_sci_BWT_int_flag = 0;
    g_t1_times.CharacterTime = PL131_DEF_CHARTIME_T1;
    g_t1_times.BlockTime = PL131_DEF_BLOCKTIME_T1;
    g_t1_times.BlockGuard =PL131_DEF_BLKGUARDTIME_T1;

}

void sci_init_vlot_state(void)
{
    nActiveT = 0;
    g_sci_voltage_state.sciClassKind = PL131_SCI_Class_BUTT;
    g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_NONE;
    g_sci_voltage_state.sci_vlotage_switch_sense = SCI_VOLTAGE_SWITCH_SENSE_CLASS_BUTT;
    g_sci_voltage_state.atrIndClass = ATR_IND_CLASS_NONE;
}

void sci_reset_state(void)
{
    SCI_STATE_STRU *const pstrState = &g_strSciState;
     /*set default configuration*/
    pstrState->eCurrentState = PL131_STATE_FIRSTINIT;    /*ensures defaults used*/
    pstrState->sSetupParams.ClockFreq = g_stSciHwCfg.sci_freq.sci_ref_freq / 1000;
    pstrState->sSetupParams.eRxHandshake = apPL131_EVEN_HANDSHAKE;
    pstrState->sSetupParams.RxRetries = PL131_DEF_RX_RETRIES;
    pstrState->sSetupParams.TxRetries = PL131_DEF_TX_RETRIES;
    pstrState->sSetupParams.CardFreq = g_stSciHwCfg.sci_freq.sci_work_freq;
    pstrState->sSetupParams.eTxHandshake = apPL131_EVEN_HANDSHAKE;
}

void sci_buf_clear(void)
{
    g_strRecBuf.usLength = 0;
    g_strRecBuf.usStart  = 0;
    g_strRecBuf.usPrelen = 0;

    /* added by yangzhi for dma transfer,2010-11-25,begin*/
    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
    {
        if (NULL != g_strRecBuf.usOutBuf)
        {
            (void)memset_s((void *)(g_strRecBuf.usOutBuf), (SCI_MAX_DATA_BUF_LEN * sizeof(u32)),0x00, (SCI_MAX_DATA_BUF_LEN * sizeof(unsigned short)));
        }
    }

    /* added by yangzhi for dma transfer,2010-11-25,end*/
}
void sci_clear_read_flag(void)
{
    /*��ȡ���ݱ�־����֤Ԥ�����ȡ��������������ֻ����һ�λص�����*/
    g_u32ReadFlag = SCI_DEF_READ_FORBID;
    g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_OVER;
}

void sci_atr_clear(void)
{
    g_strATRData.ulATRLen = 0;
    (void)memset_s(g_strATRData.ATRData, 256,0, 256);
}

void sci_init_global_on_reset()
{
    sci_init_pps_global();
    sci_init_t1_global();
    sci_atr_clear();
    sci_clear_read_flag();
    sci_reset_state();
    sci_init_vlot_state();
    sci_buf_clear();
}
/******************************************************************
* Function:  sci_plus_hotplug_in
* Description:
*      SCI IN HOT PLUG JUDGE THE NEW STATE
* Calls:
*      None
* Called By:
* Table Accessed: NONE
* Table Updated: NONE
* Inputs:
* None
* Outputs:
* None
* Return Value:
*  None
******************************************************************/

void sci_check_current_state(PL131_eStateOptions eCurrentState)
{
    if(eCurrentState == PL131_STATE_READY)
    {
        if(g_sci_detect_state == SIM_CARD_OUT
            && g_sci_ind_state != g_sci_detect_state)
        {
            g_sci_hot_plug_proc_status = SCI_HOT_PLUG_CARD_IN;
            
            SCI_RECORD_EVENT(SCI_EVENT_IND_PLUS_OUT, g_sci_detect_state, __LINE__);/* [false alarm]:fortify */
            osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIHotPlugSem); 
        }
        else if(g_sci_detect_state == SIM_CARD_IN)
        {
            g_sci_hot_plug_proc_status = SCI_HOT_PLUG_CARD_IN;
        }
    }
    else
    {
        if(g_sci_detect_state == SIM_CARD_IN && g_sci_ind_state != g_sci_detect_state)
        {
              g_sci_hot_plug_proc_status = SCI_HOT_PLUG_CARD_OUT;
              
              SCI_RECORD_EVENT(SCI_EVENT_IND_PLUS_IN, g_sci_detect_state, __LINE__);/* [false alarm]:fortify */
              osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIHotPlugSem);                      
        }
        else if(g_sci_detect_state != SIM_CARD_IDLE)
        {
            g_sci_hot_plug_proc_status = SCI_HOT_PLUG_CARD_OUT;
        }
    }
}


/******************************************************************
* Function:  pwrctrl_sci_soft_clk_dis
* Description:
*      SCI SOFT CLK DISABLE
* Calls:
*      None
* Called By:
* Table Accessed: NONE
* Table Updated: NONE
* Inputs:
* None
* Outputs:
* None
* Return Value:
*  None
******************************************************************/
void pwrctrl_sci_soft_clk_dis(void)
{
    if(!IS_ERR(g_stSciHwCfg.clk))
    clk_disable(g_stSciHwCfg.clk);
}

/******************************************************************
* Function:  pwrctrl_sci_soft_clk_en
* Description:
*      SCI SOFT CLK ENABLE
* Calls:
*      None
* Called By:
* Table Accessed: NONE
* Table Updated: NONE
* Inputs:
* None
* Outputs:
* None
* Return Value:
*  None
******************************************************************/

void pwrctrl_sci_soft_clk_en(void)
{
    /* coverity[unchecked_value] */
    if(!IS_ERR(g_stSciHwCfg.clk))
    (void)clk_enable(g_stSciHwCfg.clk);
}

/******************************************************************
* Function:  pwrctrl_sci_low_power_enter
* Description:
*      SCI vote agree sleep.
* Calls:
*      None
* Called By:
* Table Accessed: NONE
* Table Updated: NONE
* Inputs:
* None
* Outputs:
* None
* Return Value:
*  None
******************************************************************/
int pwrctrl_sci_low_power_enter(void)
{
    int result = 0;/* [false alarm]:fortify */

    if(BSP_TRUE != g_sci_lp_vote_flag)
    {
        result = mdrv_pm_wake_unlock(g_stSciHwCfg.sleep_vote);
        if(result != 0)/* [false alarm]:fortify */
        {
            sci_print_error("%d:SCI vote unlock failed, result=%d, line=%d.\n", g_stSciHwCfg.card_id,result,__LINE__,0,0,0);

            SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, result, __LINE__);

            return BSP_ERROR;
        }
        else
        {
            g_sci_lp_vote_flag = BSP_TRUE;/* [false alarm]:  ��*/
            return BSP_OK;
        }
    }

    return BSP_ERROR;

}


/******************************************************************
* Function:  pwrctrl_sci_low_power_exit
* Description:
*      SCI vote dont sleep.
* Calls:
*      None
* Called By:
* Table Accessed: NONE
* Table Updated: NONE
* Inputs:
* None
* Outputs:
* None
* Return Value:
*  None
******************************************************************/
int pwrctrl_sci_low_power_exit(void)
{
    int result = 0;/* [false alarm]:fortify */

    if(BSP_FALSE != g_sci_lp_vote_flag)/* [false alarm]:fortify */
    {
        result = mdrv_pm_wake_lock(g_stSciHwCfg.sleep_vote);/* [false alarm]:fortify */
        if(result != 0)/* [false alarm]:fortify */
        {
            sci_print_error("%d:SCI vote lock failed, result=%d, line=%d.\n", g_stSciHwCfg.card_id,result,__LINE__,0,0,0);/* [false alarm]:fortify */

            SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, result, __LINE__);

            return BSP_ERROR;
        }
        else
        {
            g_sci_lp_vote_flag = BSP_FALSE;/* [false alarm]: fortify ��*/
            return BSP_OK;
        }
    }

    return BSP_ERROR;

}

    
void sci_lowpower_vote_lock(SCI_LOWPWR_VOTE_E module)
{
    g_sci_lowpower_vote_state |= 1 << module;
    
    (void)pwrctrl_sci_low_power_exit();
    (void)pwrctrl_sci_soft_clk_en();
    return;
}


void sci_lowpower_vote_unlock(SCI_LOWPWR_VOTE_E module)
{
    g_sci_lowpower_vote_state &= ~(1 << module);

    if(!g_sci_lowpower_vote_state)
    {
        (void)pwrctrl_sci_low_power_enter();
        (void)pwrctrl_sci_soft_clk_dis();
    }

    return;
}

#define sci_lowpwr_vote_lock(module)\
    do{\
           sci_lowpower_vote_lock(module);\
           SCI_RECORD_EVENT(SCI_EVENT_LOW_POWER_EXIT, module , __LINE__);\
      }while(0)  

#define sci_lowpwr_vote_unlock(module)\
    do{\
           sci_lowpower_vote_unlock(module);\
           SCI_RECORD_EVENT(SCI_EVENT_LOW_POWER_ENTER, module , __LINE__);\
      }while(0) 

void sci_release_usim(void)
{
    if ((g_strRecBuf.usPrelen != 0) && (SCI_DEF_READ_READY == g_u32ReadFlag))
    {      
        g_strRecBuf.usPrelen = 0;
        osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIRecvSyncSem);  
    }
}

void sci_hotplug_deactive(void)
{
    if(g_u32ResetSuccess == SCI_DEF_RESET_SUCCESS)
    {
        g_strSciState.eCurrentState = PL131_STATE_INACTIVECARD;

        sci_lowpwr_vote_lock(SCI_LOWPWR_HOTPLUG);
        apBIT_SET(g_strSciState.pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 0); /*disable RX interrupt*/        
        apBIT_SET(g_strSciState.pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);
        g_SciDeactivateFlag = TRUE;  
    }
    else
    {           
        sci_print_error("card not ready,no need deact\n");
    }

    return;
}

/******************************************************************
* Function:  sci_detect_cb

* Description:
* Calls:
*      None
* Called By:
* Table Accessed: NONE
* Table Updated: NONE
* Inputs:
* None
* Outputs:
* None
* Return Value:
*  None
******************************************************************/
s32 sci_detect_cb(u32 channel_id, u32 len, void *context)
{
    u32 sci_detect_status = 0;
    u32 read_len = 0;

    read_len = bsp_icc_read(channel_id, (u8*)&sci_detect_status, len);
    if(read_len != len)
    {
        sci_print_error("readed len(%d) != expected len(%d)\n", read_len, len);
        return BSP_ERROR;
    }

    sci_print("cnt %d\n",sci_detect_status);

    g_sci_detect_state = sci_detect_status;
    sci_release_usim();
    switch (sci_detect_status)
    {
        case SIM_CARD_IN:
            SCI_RECORD_EVENT(SCI_EVENT_DETECT_CARD_IN, bsp_get_slice_value() , __LINE__);
            break;
            
        case SIM_CARD_OUT:
            sci_atr_clear();
            SCI_RECORD_EVENT(SCI_EVENT_DETECT_CARD_OUT, bsp_get_slice_value() , __LINE__);
            break;
            
        case SIM_CARD_LEAVE:
            SCI_RECORD_EVENT(SCI_EVENT_DETECT_CARD_LEAVE, bsp_get_slice_value() , __LINE__);
            sci_hotplug_deactive();
            break;
            
        default:
            break;
    }
    
    if(g_sci_detect_state != SIM_CARD_LEAVE 
        && g_sci_hot_plug_proc_status != SCI_HOT_PLUG_CARD_PROCESS)
    {
        g_sci_ind_state = sci_detect_status;
        osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIHotPlugSem);   
    }
    
    return MDRV_OK;
}

s32 sci_icc_test(u32 sci_detect_status)
{
    sci_print("cnt %d\n",sci_detect_status);

    g_sci_detect_state = sci_detect_status;

    sci_release_usim();

    switch (sci_detect_status)
    {
        case SIM_CARD_IN:
            SCI_RECORD_EVENT(SCI_EVENT_DETECT_CARD_IN, bsp_get_slice_value() , __LINE__);
            break;
            
        case SIM_CARD_OUT:
            sci_atr_clear();
            SCI_RECORD_EVENT(SCI_EVENT_DETECT_CARD_OUT, bsp_get_slice_value() , __LINE__);
            break;
            
        case SIM_CARD_LEAVE:
            SCI_RECORD_EVENT(SCI_EVENT_DETECT_CARD_LEAVE, bsp_get_slice_value() , __LINE__);
            sci_hotplug_deactive();
            break;
            
        default:
            break;
    }
    
    if(g_sci_detect_state != SIM_CARD_LEAVE 
        && g_sci_hot_plug_proc_status != SCI_HOT_PLUG_CARD_PROCESS)
    {
        g_sci_ind_state = sci_detect_status;
        osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIHotPlugSem);   
    }
    
    return MDRV_OK;
}

int sci_dma_init(void)
{
    int u32DmaChanId = 0;

    /* ��ʼ��DMAͨ�� */
    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
    {
        u32DmaChanId = bsp_edma_channel_init(g_stSciHwCfg.dma_chan, NULL, 0, 0);
        if(u32DmaChanId < 0)
        {
            sci_print_error("dma init failed! \n"); /* [false alarm]:*/
            return MDRV_ERROR;
        }
        if(BSP_OK!= bsp_edma_channel_set_config(u32DmaChanId, EDMA_P2M, 2, 0))
        {
            sci_print_error("dma config failed! \n");
            return MDRV_ERROR;
        }

        g_sciRxStGblStru.DmaChnNo = u32DmaChanId;

        /*Set Default SCI Rx Data Receive Status Flag*/
        g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_OVER;

        /*Create SCI DMA Rx Data Buffer*/
        if (NULL == g_strRecBuf.usOutBuf)
        {
            //when reveived one byte from sci, extend it to one word in usOutBuf
            if (NULL
                == (g_strRecBuf.usOutBuf = (u16 *)osl_cachedma_malloc(SCI_MAX_DATA_BUF_LEN * sizeof(u32))))
            {
                sci_print_error("malloc memory error!\n");
                return MDRV_ERROR;
            }
        }
    }
    else
    {
        /*Set SCI Rx Mode is CPU*/
        g_sciRxStGblStru.RxModeFlag = SCI_RX_CPU_MODE;
    }

    return MDRV_OK;
}

void sci_sem_init()
{
    
    if (!g_stSciHwCfg.sci_sem.g_SCIRecvSyncSem)
    {
        osl_sem_init(0,&g_stSciHwCfg.sci_sem.g_SCIRecvSyncSem);/* [false alarm]:fortify */
        if (0 == g_stSciHwCfg.sci_sem.g_SCIRecvSyncSem)
        {
            sci_print_error("create Recv Semaphore failed.\n");
            return;
        }
    }

    if (!g_stSciHwCfg.sci_sem.g_SCIClockStartSem)
    {
        osl_sem_init(0,&g_stSciHwCfg.sci_sem.g_SCIClockStartSem);/* [false alarm]:fortify */
        if (0 == g_stSciHwCfg.sci_sem.g_SCIClockStartSem)
        {
            sci_print_error("create Timer Semaphore failed.\n");
            return;
        }
    }

    if (!g_stSciHwCfg.sci_sem.g_SCIClockStopSem)
    {
        osl_sem_init(0,&g_stSciHwCfg.sci_sem.g_SCIClockStopSem);/* [false alarm]:fortify */
        if (0 == g_stSciHwCfg.sci_sem.g_SCIClockStopSem)
        {
            sci_print_error("create Timer Semaphore failed.\n");
            return;
        }
    }

    if (!g_stSciHwCfg.sci_sem.g_SCISynSem)
    {
        osl_sem_init(0,&g_stSciHwCfg.sci_sem.g_SCISynSem);/* [false alarm]:fortify */
        if (0 == g_stSciHwCfg.sci_sem.g_SCISynSem)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SCI, "create Sync Semaphore failed.\n", 0, 0, 0, 0, 0, 0);
            return;
        }
    }

    if(!g_stSciHwCfg.sci_sem.g_SCIDeactiveSyncSem)
    {
        osl_sem_init(0,&g_stSciHwCfg.sci_sem.g_SCIDeactiveSyncSem);/* [false alarm]:fortify */
        if (0 == g_stSciHwCfg.sci_sem.g_SCIDeactiveSyncSem )
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SCI, "create g_SCIDeactiveSyncSem  Semaphore failed.\n", 0, 0, 0, 0, 0, 0);
            return;
        }
    }
    
    if (!g_stSciHwCfg.sci_sem.g_SCIBWTSem)
    {
        osl_sem_init(0,&g_stSciHwCfg.sci_sem.g_SCIBWTSem);/* [false alarm]:fortify */
        if (0 == g_stSciHwCfg.sci_sem.g_SCIBWTSem)
        {
            sci_print_error("create bwt Semaphore failed.\n");
            return;
        }
        sci_print("g_stSciHwCfg.sci_sem.g_SCIBWTSem = %d\n",g_stSciHwCfg.sci_sem.g_SCIBWTSem);
    }
    
    if (!g_stSciHwCfg.sci_sem.g_SCIHotPlugSem)
    {
        osl_sem_init(0,&g_stSciHwCfg.sci_sem.g_SCIHotPlugSem);/* [false alarm]:fortify */
        if (0 == g_stSciHwCfg.sci_sem.g_SCIHotPlugSem)
        {
            sci_print_error("create hotplug Semaphore failed.\n");
            return;
        }
     }
}
void sci_sem_destory(SCI_CFG_STRU*  p_sci_cfg)
{
    s32 ret = -1;
    if(p_sci_cfg->sci_sem.g_SCIRecvSyncSem)
    {
        ret = osl_sema_delete(&p_sci_cfg->sci_sem.g_SCIRecvSyncSem);/* [false alarm]:fortify */
        if(ret == 0)
        {
            p_sci_cfg->sci_sem.g_SCIRecvSyncSem =0;
        }
        else
        {
            sci_print_error("g_SCIRecvSyncSem del fail\n");/* [false alarm]:fortify */
        }
        
    }
    if(p_sci_cfg->sci_sem.g_SCIClockStartSem)
    {
        ret = osl_sema_delete(&p_sci_cfg->sci_sem.g_SCIClockStartSem);/* [false alarm]:fortify */
        if(ret == 0)
        {
            p_sci_cfg->sci_sem.g_SCIClockStartSem =0;
        }
        else
        {
            sci_print_error("g_SCIClockStartSem del fail\n");
        }
    
    }
    if(p_sci_cfg->sci_sem.g_SCIClockStopSem)
    {
        ret = osl_sema_delete(&p_sci_cfg->sci_sem.g_SCIClockStopSem);/* [false alarm]:fortify */
        if(ret == 0)
        {
            p_sci_cfg->sci_sem.g_SCIClockStopSem =0;
        }
        else
        {
            sci_print_error("g_SCIClockStopSem del fail\n");
        }
    }
    if(p_sci_cfg->sci_sem.g_SCISynSem)
    {
        ret = osl_sema_delete(&p_sci_cfg->sci_sem.g_SCISynSem);/* [false alarm]:fortify */
        if(ret == 0)
        {
            p_sci_cfg->sci_sem.g_SCISynSem =0;
        }
        else/* [false alarm]:fortify */
        {
            sci_print_error("g_SCISynSem del fail\n");/* [false alarm]:fortify */
        }
    }
    if(p_sci_cfg->sci_sem.g_SCIDeactiveSyncSem)
    {
        ret = osl_sema_delete(&(p_sci_cfg->sci_sem.g_SCIDeactiveSyncSem));/* [false alarm]:fortify */
        if(ret == 0)
        {
            p_sci_cfg->sci_sem.g_SCIDeactiveSyncSem =0;
        }
        else
        {
            sci_print_error("g_SCIDeactiveSyncSem del fail\n");
        }
        
    }
    if(p_sci_cfg->sci_sem.g_SCIHotPlugSem)
    {
        ret = osl_sema_delete(&(p_sci_cfg->sci_sem.g_SCIHotPlugSem));/* [false alarm]:fortify */
        if(ret == 0)
        {
            p_sci_cfg->sci_sem.g_SCIHotPlugSem =0;
        }
        else
        {
            sci_print_error("g_SCIHotPlugSem del fail\n");
        }
    
    }
    
}

void sci_get_chout_deac_flag(void)
{
    u32 sci_gcf_flag_nv = 0;
    if(NV_OK != bsp_nvm_read(NV_ID_DRV_SCI_GCF_STUB_FLAG, (u8*)&sci_gcf_flag_nv, sizeof(u32)))
    {
        sci_print_error("bsp_sci_reset: get gcf nv failed!\n");
    }
  
    g_ulSciGcfStubFlag = sci_gcf_flag_nv;

    if (g_ulSciGcfStubFlag)
    {
        g_ulChTOUTDeactEn = 1;
    }
}
/*lint +e525*/
/**************************************************
*  Function:  sci_init
*
*  Description:
*      Initialise the SCI.
*
*  Calls:
*      sci_buf_clear
*      intConnect
*      intEnable
*
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Output:
*         None
*
*  Return:
*         None
*
******************************************************************/
void sci_init()
{
    s32 ret = BSP_OK;
    SCI_STATE_STRU *const pstrState = &g_strSciState;

    if(g_stSciHwCfg.base_addr == 0)
    {
        sci_print("this sci no hard source");
        return;
    }
    sci_print("now init is sci_id is %d\n",g_stSciHwCfg.sci_id);

    sci_rst_global_on_init();
    sci_init_global_on_reset();

    (void)memset_s((void *)pstrState,sizeof(SCI_STATE_STRU), 0, sizeof(SCI_STATE_STRU));
    pstrState->pBase = (SCI_REG *) (g_stSciHwCfg.base_addr);
    pstrState->eCurrentState = PL131_STATE_FIRSTINIT;

    sci_sem_init();

    if (!g_stSciHwCfg.sync_task_id)
    {
        (void)osl_task_init(g_stSciHwCfg.syncTaskName,25,20000,(OSL_TASK_FUNC)sci_rec_sync_task,0,&g_stSciHwCfg.sync_task_id);/* [false alarm]:fortify */
    }

    if (!g_stSciHwCfg.hotplug_task_id)
    {
        (void)osl_task_init(g_stSciHwCfg.hotPlugTaskName,18,20000,(OSL_TASK_FUNC)sci_hot_plug_task,0,&g_stSciHwCfg.hotplug_task_id);/* [false alarm]:fortify */
    }

    /* init interrupts*/
    pwrctrl_sci_soft_clk_en(); /* [false alarm]:fortify */
    writel(0, SCI_REG_INTMASK); /* [false alarm]:fortify */
    writel(0xffff, SCI_REG_INTCLEAR);

    
    (void)osl_int_connect((g_stSciHwCfg.int_number),(irq_handler_t)sci_int_handler,0);
    g_stSciHwCfg.sci_int_handler = (irq_handler_t)sci_int_handler;
    (void)enable_irq(g_stSciHwCfg.int_number);

    (void)sci_dma_init();
 
    /* ���µ磬��֤��cold reset */
    if(g_stSciHwCfg.sci_pmu == NULL)
    {
        g_stSciHwCfg.sci_pmu = regulator_get(NULL, g_stSciHwCfg.pwr_type);
        if (NULL == g_stSciHwCfg.sci_pmu )
        {
            sci_print_error("get pmu device failed.\n");
            SCI_RECORD_EVENT(SCI_EVENT_REGULATOR_ERR,(*(g_stSciHwCfg.pwr_type)) , __LINE__);
            return ;
        }
    }   
    
    /* init sim card detect icc channel */
    
    ret = bsp_icc_event_register(g_stSciHwCfg.icc_chnl, sci_detect_cb, NULL, NULL, NULL);/*[false alarm]:*/
    sci_print("g_stSciHwCfg.icc_chnl = %d\n",g_stSciHwCfg.icc_chnl);
    if(ret != BSP_OK)
    {
        sci_print_error("icc register failed\n");
    }
    
    /* init sci record */
    sci_record_init();

    sci_get_chout_deac_flag();

    sci_print("[sci] %s: sim%d init OK!\n",__FUNCTION__,g_stSciHwCfg.card_id);

    SCI_RECORD_EVENT(SCI_EVENT_SCI_INIT_SUCCESS, (u32)g_stSciHwCfg.card_id, (__LINE__));

    return ;

}

/******************************************************************
* Function:  sciBufAdd
*
* Description:
*      Add data received by interrupt to driver's buffer
*
* Calls:
*      None
*
* Called By:  Interrupt Service Process
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
* pucRecbyte: the data received by ISR
*
* Outputs:
* None
*
* Return Value:
*  OK  - successful completion
*  ERROR  - failed
*
******************************************************************/
s32 sci_buf_add(u8 * pucRecbyte)
{    
    if ((NULL == pucRecbyte))/* [false alarm]:fortify */
    {
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, 0, __LINE__);/* [false alarm]:fortify */

        sci_print_error("para err,NULL == pucRecbyte\n");
        return BSP_ERROR;
    }

    if(g_strRecBuf.usLength >= SCI_BUF_MAX_LEN)
    {
        SCI_RECORD_EVENT(SCI_EVENT_ERROR_DATA_REC_BUF_OVR,g_strRecBuf.usLength,(u32)pucRecbyte);
        
        sci_print_error("usLength is larger than SCI_BUF_MAX_LEN, and is %d\n", g_strRecBuf.usLength);
        
        if ((g_strRecBuf.usPrelen != 0) && (SCI_DEF_READ_READY == g_u32ReadFlag))
        {
            g_strRecBuf.usPrelen = 0;
            osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIRecvSyncSem);  
        }
        g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_ERROR;      

        sci_hotplug_deactive();
    }
    else
    {
         /* ����ȡ�����ݱ�����buffer��*/
        g_strRecBuf.ucRecBuf[g_strRecBuf.usLength] = *pucRecbyte;

        g_strRecBuf.usLength++;
    }
    

    /* �����ȡ�����ݳ��ȴ��ڵ���Ԥ�������ݳ��ȣ����ͷ��ź�������sciRxTask�����е��ûص����������ݷ��ظ��ϲ�*/
    if ((g_strRecBuf.usPrelen != 0) && (g_strRecBuf.usPrelen <= (g_strRecBuf.usLength - g_strRecBuf.usStart))
        && (SCI_DEF_READ_READY == g_u32ReadFlag))
    {
        g_strRecBuf.usPrelen = 0;

        g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_SATISFIED;
        osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIRecvSyncSem);

    }

    return MDRV_OK;
}



/******************************************************************
*  Function:  sciRegEvent
*
*  Description:
*      ע��ص�����
*
*  Calls:
*      None
*
*  Called By:  PS software
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         u32 u32Event      ע���¼�
*         Sci_Event_Func pFunc  �ص�����
*  Outputs:
*
* Return Value:
*         None
*
******************************************************************/
void sci_reg_event(u32 u32Event, Sci_Event_Func pFunc)
{
    g_u32Event = u32Event;
    g_FuncCb = pFunc;
}
/******************************************************************
* Function:  sci_rx_dma_start
*
* Description:
*       start dma transfer
* Calls:
*      None
*
* Called By:  None
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
*  u32DstAddr: buffer address of data received;
*  u32TransLength: data transfer length;
*
* Outputs:
*  None
*
* Return Value:
*  None
*
******************************************************************/
s32  sci_rx_dma_start(u32* u32DstAddr, u32 u32TransLength)
{

    u32 u32SrcAddr = 0;

    /* open DMA clock gating*/

    if(NULL == u32DstAddr)
    {
        return BSP_ERROR;
    }

    /* ����EDMAԴ��ַ,�˴�����Ҫ�ú�� */
    u32SrcAddr = SCI_REG_DATA;

    if(bsp_edma_channel_stop(g_sciRxStGblStru.DmaChnNo) < 0)
    {
        sci_print_error("dma transfer stop failed! \n");
        SCI_RECORD_EVENT(SCI_EVENT_DMA_ERROR,(u32)u32DstAddr,(u32)u32TransLength);
        return BSP_ERROR;
    }

    /*����һ��EDMA�첽���ݰ���*/
    if (bsp_edma_channel_async_start(g_sciRxStGblStru.DmaChnNo, u32SrcAddr, (u32)u32DstAddr, u32TransLength))
    {
        SCI_RECORD_EVENT(SCI_EVENT_DMA_ERROR,(u32)u32DstAddr,(u32)u32TransLength);
        sci_print_error("transfer failed! \n");
        return BSP_ERROR;
    }

    return BSP_OK;
}


/******************************************************************
* Function:  sci_count_length
*
* Description:
*      SCI count receive buffer total length.
*
*
* Calls:
*      None
*
* Called By:
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
* None
*
* Outputs:
* None
*
* Return Value:
*  None
*
******************************************************************/
u32 sci_count_length(void)
{
    u32 ulSciDMADstAddr = 0;
    u32 receivedDataNum = 0;
    u32 ulSciBufAddr = (u32)g_strRecBuf.usOutBuf;

    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
    {
        ulSciDMADstAddr = bsp_edma_current_transfer_address(g_sciRxStGblStru.DmaChnNo);
        if(ulSciDMADstAddr > 0)
        {
            g_strRecBuf.usLength = (u16)((ulSciDMADstAddr - ulSciBufAddr) / sizeof(u32));

        }
    }

    receivedDataNum = g_strRecBuf.usLength - g_strRecBuf.usStart;
    return receivedDataNum;
}

/******************************************************************
* Function:  sciClockStopModeCfg
*
* Description:
*      start/stop SCI clock
*
* Calls:
*      appl131_data_transfer
*
* Called By:  PS software
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
* ucClockStopMode - If the card supports clock stop mode, this parameter is used
*                              to stop or start the clock.
*                              0: stat the SCI clock
*                              1: stop the SCI clock
*
* Outputs:
* none
*
* Return Value:
*  OK - successful completion
*  ERROR - failed
*  DR_ERR_SCI_PARAERROR - invalid mode specified
*  DR_ERR_SCI_UNSUPPORTED - not support such a operation
*
******************************************************************/
s32 sci_clock_stop_mode_cfg( u32 ucClockStopMode, u32 ucClockStopInd)
{
    s32 staErr;

    staErr = appl131_clock_stop_mode_set(&g_strSciState,
                                       (apPL131_eClockMode)ucClockStopMode, ucClockStopInd);
    if (apERR_UNSUPPORTED == staErr)
    {
        sci_print_error("appl131_clock_stop_mode_set fail = %d.\r\n", staErr, 0, 0, 0, 0, 0);
        return BSP_ERR_SCI_UNSUPPORTED;
    }
    else
    {
        return MDRV_OK;
    }
}


/******************************************************************
*  Function:  bsp_sci_func_register
*
*  Description:
*      Initialise the SCI.
*
*  Calls:
*      apPL131_ParamsSet
*      sci_buf_clear
*      intConnect
*      intEnable
*      semBCreate
*      taskSpawn
*      apPL131_CardActiveSet
*
*  Called By:  PS software
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Output:
*         None
*
*  Return:
*         None
*
******************************************************************/
void bsp_sci_func_register(OMSCIFUNCPTR omSciFuncPtr)
{
    if (NULL == omSciFuncPtr)
    {
        sci_print_error("the input parameter is null!");
        return ;
    }

    g_omSciFuncPtr = omSciFuncPtr;
}

void sci_rst_ip()
{
#ifdef BSP_CONFIG_HI3650
    /* reset ip*/
    if(CARD_CONNECT_SCI0 == g_stSciHwCfg.sci_id)
    {
        BSP_REG_SETBITS(HI_AP_SYSCTRL_BASE_ADDR, SCI_RESET_REG_ADDR, SCI_RESET_CARD0_BIT_SHIFT, 1, 1);
    }
    else
    {
        BSP_REG_SETBITS(HI_AP_SYSCTRL_BASE_ADDR, SCI_RESET_REG_ADDR, SCI_RESET_CARD1_BIT_SHIFT, 1, 1);
    }
#endif
}

void sci_unrst_ip()
{
#ifdef BSP_CONFIG_HI3650
    /* unreset ip*/
    if(CARD_CONNECT_SCI0 == g_stSciHwCfg.sci_id)
    {
        BSP_REG_SETBITS(HI_AP_SYSCTRL_BASE_ADDR, SCI_UNRESET_REG_ADDR, SCI_RESET_CARD0_BIT_SHIFT, 1, 1);
    }
    else
    {
        BSP_REG_SETBITS(HI_AP_SYSCTRL_BASE_ADDR, SCI_UNRESET_REG_ADDR, SCI_RESET_CARD1_BIT_SHIFT, 1, 1);
    }
#endif
}

void sci_wait_deac_finish(void)
{
    u32 i = 0;

    for(;i < 10 ;i++)
    {
        if(g_SciDeactivateFlag == TRUE)
        {
            (void)osl_task_delay(2);
        }
        else
        {
            break;
        }
    }
    if(i >= 10)
    {
        g_SciDeactivateFlag = FALSE;
        g_sci_api_deactive = 0;
    }
}

s32 sci_cold_reset(void)
{
    s32 retvalue   = -1;
    SCI_REG *pstrBase  = BSP_NULL;
    SCI_STATE_STRU *const pstrState = &g_strSciState;
    u32 current_time = 0;
    sci_print_error("begin reset\n");
    current_time = bsp_get_slice_value();

    SCI_RECORD_EVENT(SCI_EVENT_API_RESET_START, current_time , __LINE__);

    if(g_stSciHwCfg.base_addr == 0)
    {
        return BSP_OK;
    }
    
    sci_lowpower_vote_lock(SCI_LOWPWR_USIM);

    sci_rst_ip();


    (void)memset_s((void *)pstrState, sizeof(SCI_STATE_STRU),0, sizeof(SCI_STATE_STRU));
    pstrState->pBase = (SCI_REG *) (g_stSciHwCfg.base_addr);
    pstrBase = pstrState->pBase;

    sci_unrst_ip();

    sci_init_global_on_reset();
            
    /*mask off & clear all interrupts*/
    writel(SCI_DEF_MASK_ALL_IRQ, SCI_REG_INTMASK);
    writel(SCI_DEF_CLEAR_ALL_IRQ, SCI_REG_INTCLEAR);
            
    sci_wait_deac_finish();

    retvalue = sci_set_voltage(SCI_VOLTAGE_SWITCH_CLASS_ZERO2CB);/*[false alarm]:*/
                
    if(retvalue != BSP_OK)
    {
        SCI_RECORD_EVENT(SCI_EVENT_API_RESET_FAILED,g_sci_voltage_state.sciClassKind, __LINE__);
    }
          
    retvalue = appl131_params_set(&g_strSciState, NULL, NULL, NULL);/* [false alarm]:��*/
    if ((retvalue != apERR_NONE) && (retvalue != apERR_PL131_USEDEFAULT))
    {
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);
        SCI_RECORD_EVENT(SCI_EVENT_API_RESET_FAILED,g_strSciState.eCurrentState, __LINE__);
            
        sci_print_error("set parameter interface is error.\n");
        return MDRV_ERROR;
     }
            
      /*set up other registers if not from power on reset*/
     BIT_SET(pstrBase->RegCtrl0, PL131_REGCTRL0_CONV, PL131_CONVENTION_DIRECT);/*[false alarm]:*/
     BIT_SET(pstrBase->RegDMACtrl, PL131_REGDMA, apPL131_DMA_OFF); /* Disable DMA */    
     BIT_SET(pstrBase->RegCtrl0, PL131_REGCTRL0_PARITYBIT, 1);/*������żλ*/
                
     if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)/* [false alarm]: ��*/
     {
        SCI_RECORD_EVENT(SCI_EVENT_DMA_START, g_sciRxStGblStru.RxModeFlag, __LINE__);
           
        if (OK != sci_rx_dma_start((u32*)(g_strRecBuf.usOutBuf), SCI_MAX_DATA_BUF_LEN * sizeof(u32)))/*lint !e740 !e826*/
        {
            sci_print_error("dma transfer start failed! \n");
            return MDRV_ERROR;
        }

      }
            
      if (pstrState->eCurrentState == PL131_STATE_INACTIVECARD)/*[false alarm]:*/
      {
           SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pstrState->eCurrentState, __LINE__);/*[false alarm]:*/
            
           retvalue = appl131_card_active_set(pstrState, TRUE, pstrState->sATRParams.pATRBuffer);
           if (retvalue != apERR_NONE)
           {
                SCI_RECORD_EVENT(SCI_EVENT_API_RESET_FAILED,g_strSciState.eCurrentState, __LINE__);
            
                sci_print_error("card active set interface is error.\n");
                return retvalue;
            }
            SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pstrState->eCurrentState, __LINE__);
       }
       else
       {
            SCI_RECORD_EVENT(SCI_EVENT_ERROR_NOCARD, pstrState->eCurrentState, __LINE__);
            
            sci_print_error("no card!\n");
       }


    if(g_sci_hot_plug_proc_status == SCI_HOT_PLUG_CARD_PROCESS)
    {
        g_sci_hot_plug_proc_status = SCI_HOT_PLUG_CARD_IN;
    }      
   g_ulSciClkTimeStpFlag = apPL131_CLOCK_START;

   g_stSciHwCfg.slot_switch_flag = SCI_SLOT_SWITCH_NONE;
   
   g_sci_hw_abnormal = SCI_HW_STATE_OK;
   
   SCI_RECORD_EVENT(SCI_EVENT_API_RESET_FINISH, pstrState->eCurrentState, __LINE__);
   return MDRV_OK; 
}

s32 sci_warm_reset(void)
{
    s32 retvalue   = -1;
    SCI_STATE_STRU *const pstrState = &g_strSciState;

    /*�ȸ�λ�������ʵ���״̬*/
    /*��������ȸ�λ˵����ǰһ�����й�һ���临λ��pmuΪ����˵���϶���û���й��临λ*/
    /*�����ǰ��readAtr�����뱣֤ts��t0���ܽ������ܽ����ȸ�λ������Ϊ7816-3*/

    if ((pstrState->eCurrentState <= PL131_STATE_INACTIVECARD) 
        || (g_stSciHwCfg.sci_pmu == NULL)
        || ((pstrState->eCurrentState == PL131_STATE_READATR) && g_strATRData.ulATRLen < 2))
    {
        return BSP_ERR_SCI_CURRENT_STATE_ERR;
    }

    /* ���buffer */
    sci_buf_clear();
    sci_atr_clear();
            
    /*mask off & clear all interrupts*/
    writel(SCI_DEF_MASK_ALL_IRQ, SCI_REG_INTMASK);
    writel(SCI_DEF_CLEAR_ALL_IRQ, SCI_REG_INTCLEAR);

    sci_init_global_on_reset();

    sci_wait_deac_finish();

    if (pstrState->eCurrentState >= PL131_STATE_WAITATR)
    {
        SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pstrState->eCurrentState, __LINE__);/*[false alarm]:*/

        retvalue = appl131_card_active_set(pstrState, TRUE, pstrState->sATRParams.pATRBuffer);
        if (retvalue != apERR_NONE)
        {
            SCI_RECORD_EVENT(SCI_EVENT_API_RESET_FAILED,g_strSciState.eCurrentState, __LINE__);
            sci_print_error("card active set interface is error.\n");
            return retvalue;
        }
        SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pstrState->eCurrentState, __LINE__);
     }
     else
     {
        sci_print_error("warm reset fail!\n");
        return BSP_ERR_SCI_NOTREADY;
     }
   g_ulSciClkTimeStpFlag = apPL131_CLOCK_START;
            
   SCI_RECORD_EVENT(SCI_EVENT_API_RESET_FINISH, pstrState->eCurrentState, __LINE__);
   return BSP_OK;

}

/******************************************************************
*  Function:  sciReset
*
*  Description:
*      Initialise the SCI.
*
*  Calls:
*      apPL131_ParamsSet
*      sci_buf_clear
*      intConnect
*      intEnable
*      semBCreate
*      taskSpawn
*      apPL131_CardActiveSet
*
*  Called By:  PS software
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Output:
*         None
*
*  Return:
*         None
*
******************************************************************/
s32 bsp_sci_reset(RESET_MODE_E rstMode)
{
    SCI_RECORD_EVENT(SCI_EVENT_API_RESET_START, bsp_get_slice_value() , __LINE__);
    if (rstMode != WARM_RESET && rstMode != COLD_RESET)
    {
        return BSP_ERR_SCI_INVALIDPARA;
    }
    if(rstMode == WARM_RESET)
    {
        return sci_warm_reset();
    }
    else
    {  
        return sci_cold_reset();
    }
}

/******************************************************************
*  Function:  bsp_sci_card_status_get
*
*  Description:
*      Get the SCI Status.
*
*  Calls:
*      None
*
*  Called By:  PS software
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Outputs:

* pulCardStatus - 0 card ok
*                 1 card error
*
* Return Value:
*  OK  - successful completion
*  ERROR  - failed
*
******************************************************************/
u32 bsp_sci_card_status_get (void)
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;
    u32 u32CardStatus = 0xFF;

    SCI_RECORD_EVENT(SCI_EVENT_API_GET_STATUS, pstrState->eCurrentState, __LINE__);

    if (pstrState->eCurrentState >= PL131_STATE_READY)
    {
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

        u32CardStatus = SCI_CARD_STATE_READY;

    }
    else if ((pstrState->eCurrentState <= PL131_STATE_NOCARD) && \
        (pstrState->eCurrentState != PL131_STATE_FIRSTINIT))
    {
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

        u32CardStatus = SCI_CARD_STATE_NOCARD;
    }
    else
    {
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);
        u32CardStatus = SCI_CARD_STATE_BUSY;
    }

    return (u32CardStatus);
}

/******************************************************************
* Function:  sciDataSend
*
* Description:
*      Begins data transfer from the SCI buffer to the card
*      This will send the specified number of bytes from buffer to the
*      card, using an interrupt-driven system.
*
* Calls:
*      appl131_data_transfer
*
* Called By:  PS software
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
* pucDataBuffer - location of data to send
* ulDataLength - number of bytes/characters to send
*
* Outputs:
* none
*
* Return Value:
*  OK - transmission commenced successfully
*  DR_ERR_SCI_NOTINIT - initialisation routine not run
*  DR_ERR_SCI_DISABLED - driver is in a disabled state
*  DR_ERR_SCI_NOCARD - no card present
*  DR_ERR_SCI_NODATA - buffer is NULL or length is zero
*
*
******************************************************************/
s32 bsp_sci_data_send(u32 ulDataLength, unsigned char *pucDataBuffer)
{
       
    SCI_RECORD_EVENT(SCI_EVENT_API_DATA_SEND, (u32)pucDataBuffer, __LINE__);

    if ((0 == ulDataLength) || (NULL == pucDataBuffer) || (ulDataLength > SCI_DEF_SEND_MAX_LENGTH))
    {
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, (u32)pucDataBuffer, __LINE__);

        sci_print_error("the input parameter ERROR!");
        return BSP_ERR_SCI_INVALIDPARA;
    }

    if (g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    {
        sci_print_error("not initialized\n");
        return BSP_ERR_SCI_NOTINIT;
    }

    sci_buf_clear();


    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
    {
        SCI_RECORD_EVENT(SCI_EVENT_DMA_START, ulDataLength, __LINE__);

        if (BSP_OK != sci_rx_dma_start((u32*)(g_strRecBuf.usOutBuf), SCI_MAX_DATA_BUF_LEN * sizeof(u32)))/*lint !e740 !e826*/
        {
            sci_print_error("sci_data_send: dma transfer start failed\n");
            return MDRV_ERROR;
        }
    }
    return appl131_data_transfer (&g_strSciState, apPL131_TX_TO_CARD, pucDataBuffer, ulDataLength);
}



/******************************************************************
* Function:  sciDataReadSync
*
* Description:
*      Read specified length data from the driver.
*      This function wil be called after the PS software get the drivers information.
*
* Calls:
*      memcpy
*
* Called By:  PS Software
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
* pucRecData - The data buffer to be copied to.
* ulLength - number of bytes/characters to receive
*
* Outputs:
* none
*
* Return Value:
*  OK - transmission commenced successfully
*  DR_ERR_SCI_PARAERROR - invalid mode specified
*
******************************************************************/
s32 bsp_sci_data_read_sync(u32 ulLength, u8 *pucRecData)
{
    s32 sciLockKey = 0;
    u32 ulLoopIndex;
    u32 recDataNum = 0;

    SCI_STATE_STRU * const pstrState = &g_strSciState;
    
    SCI_RECORD_EVENT(SCI_EVENT_API_DATA_REC_START, (u32)pucRecData, __LINE__);

    if ((ulLength > SCI_DEF_RECEIVE_MAX_LENGTH) || (NULL == pucRecData) || (0 == ulLength) )
    {
        sci_print_error("u32Length = %d || pu8Data is NULL!",ulLength,0,0,0,0,0);

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

        return BSP_ERR_SCI_INVALIDPARA;
    }


    if (g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    {
        sci_print_error("not initialized\n");
        return BSP_ERR_SCI_NOTINIT;
    }

    g_u32ReadFlag = SCI_DEF_READ_READY;
    apBIT_SET((pstrState->pBase->RegIntClear), PL131_REGINTMASK_CHTOUT, 1);
    apBIT_SET((pstrState->pBase->RegIntMask), PL131_REGINTMASK_CHTOUT, 1);
    /* coverity[lock_acquire] */
    local_irq_save(sciLockKey);
    recDataNum = sci_count_length();

    /* �����ǰ�������Ѿ����㣬ֱ�ӿ������ݷ��� */
    if (recDataNum >= (u16)ulLength)
    {
        if(g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
        {
            return BSP_ERR_SCI_NOCARD;
        }
        if(g_sciRxStGblStru.RxDataRecFlag == SCI_RX_DATA_REC_ERROR)
        {    
            (void)sci_record_data_save(SCI_LOG_BUF_OVER);
            return BSP_ERR_SCI_NOCARD;
        }
        
        g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_SATISFIED;

        //added by yangzhi for dma test in 2010-11-25
        if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
        {
            (void)osl_cache_invalid(OSL_DATA_CACHE, (u8 *)g_strRecBuf.usOutBuf, SCI_MAX_DATA_BUF_LEN * sizeof(u32));
            for (ulLoopIndex = 0; ulLoopIndex < ulLength; ulLoopIndex++)
            {
                //copy data from usOutBuf to ucRecBuf, which is 8-bits allocated compared to 16-bits allocated in the former one
                g_strRecBuf.ucRecBuf[ulLoopIndex] = (u8)(g_strRecBuf.usOutBuf[g_strRecBuf.usStart * sizeof(u16)
                                                                                 + ulLoopIndex * sizeof(u16)] & 0xFF);
            }

            (void)memcpy_s(pucRecData,256 ,(void *)(&(g_strRecBuf.ucRecBuf[0])), ulLength * (sizeof(u8)));
        }
        else
        {
            /* ��buffer�б�������ݷ��ظ��ϲ�*/
            (void)memcpy_s(pucRecData,256 ,(void *)(&(g_strRecBuf.ucRecBuf[g_strRecBuf.usStart])), ulLength);
        }

        g_strRecBuf.usStart += (u16)ulLength;

        g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_PROCESS;
        g_u32ReadFlag = SCI_DEF_READ_FORBID;

        local_irq_restore(sciLockKey);

        apBIT_SET((pstrState->pBase->RegIntMask), PL131_REGINTMASK_CHTOUT, 0);

        
        SCI_RECORD_EVENT(SCI_EVENT_API_DATA_REC_DONE, ulLength, __LINE__);

        SCI_RECORD_DATA(SCI_DATA_RCV_EVENT, (BSP_U8)ulLength, pucRecData);
        
        return BSP_OK;
    }
    /* ����ȴ� */
    else
    {
        u32 loop = 135;             /* ��255���ֽ������ټ������ */
        u32 ulDataLenPre = 0;
        u32 ulDataLenCur = 0;

        /* ���жϣ���ʼ�������� */
        g_strRecBuf.usPrelen = (u16)ulLength;
        do
        {
            /* �������������� */
             /* coverity[lock_acquire] */
            local_irq_restore(sciLockKey);
            if(g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
            {
                return BSP_ERR_SCI_NOCARD;
            }
            /* coverity[sleep] */
            if(g_sciRxStGblStru.RxDataRecFlag == SCI_RX_DATA_REC_ERROR)
            {    
                (void)sci_record_data_save(SCI_LOG_BUF_OVER);
                return BSP_ERR_SCI_NOCARD;
            }
            (void)osl_sem_downtimeout(&g_stSciHwCfg.sci_sem.g_SCIRecvSyncSem, 200);

            /* ��������֮���ٴμ���������ȫ�ֱ��� */
            /* coverity[lock_acquire] */
            local_irq_save(sciLockKey);

            recDataNum = sci_count_length();
            if (recDataNum >= (u16)ulLength)
            {
                if(g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
                {
                    return BSP_ERR_SCI_NOCARD;
                }
                if(g_sciRxStGblStru.RxDataRecFlag == SCI_RX_DATA_REC_ERROR)
                {    
                    (void)sci_record_data_save(SCI_LOG_BUF_OVER);
                    return BSP_ERR_SCI_NOCARD;
                }
                g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_SATISFIED;
            }
            else
            {
                if(g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
                {
                    return BSP_ERR_SCI_NOCARD;
                }
            }
           

            /* ��������Ƿ��Ѿ����� */
            if (SCI_RX_DATA_REC_SATISFIED == g_sciRxStGblStru.RxDataRecFlag)
            {
                /* ��buffer�б�������ݷ��ظ��ϲ�*/
                if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
                {
                    (void)osl_cache_invalid(OSL_DATA_CACHE, (u8 *)g_strRecBuf.usOutBuf, SCI_MAX_DATA_BUF_LEN * sizeof(u32));
                    for (ulLoopIndex = 0; ulLoopIndex < ulLength; ulLoopIndex++)
                    {
                        g_strRecBuf.ucRecBuf[ulLoopIndex] = (u8)(g_strRecBuf.usOutBuf[g_strRecBuf.usStart
                                                                                         * sizeof(u16)
                                                                                         + ulLoopIndex
                                                                                         * sizeof(u16)] & 0xFF);
                    }

                    (void)memcpy_s(pucRecData, 256,(void *)(&(g_strRecBuf.ucRecBuf[0])), ulLength * (sizeof(u8)));
                }
                else
                {
                    (void)memcpy_s(pucRecData, 256,(void *)(&(g_strRecBuf.ucRecBuf[g_strRecBuf.usStart])), ulLength);
                }

                g_strRecBuf.usStart += (u16)ulLength;

                g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_PROCESS;
                g_u32ReadFlag = SCI_DEF_READ_FORBID;

                local_irq_restore(sciLockKey);

                apBIT_SET((pstrState->pBase->RegIntMask), PL131_REGINTMASK_CHTOUT, 0);

                SCI_RECORD_DATA(SCI_DATA_RCV_EVENT, (BSP_U8)ulLength, pucRecData);
                SCI_RECORD_EVENT(SCI_EVENT_API_DATA_REC_DONE, ulLength, __LINE__);
                
                /* coverity[missing_unlock] */
                return BSP_OK;
            }
            else
            {
                ulDataLenCur = g_strRecBuf.usLength;

                /* ���2s��������û�����ӣ���Ϊ��ʱ */
                if (ulDataLenCur == ulDataLenPre)
                {
                    g_strRecBuf.usPrelen = 0;
                    g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_OVER;

                    local_irq_restore(sciLockKey);

                    apBIT_SET((pstrState->pBase->RegIntMask), PL131_REGINTMASK_CHTOUT, 0);

                    sci_print_error("no data len=%d cur_len=%d, card id is 0x%d\n", ulLength, g_strRecBuf.usLength,g_stSciHwCfg.card_id,0,0,0);

                    SCI_RECORD_EVENT(SCI_EVENT_ERROR_NODATA, pstrState->eCurrentState, __LINE__);

                    SCI_RECORD_EXCGBL(SCI_EVENT_ERROR_NODATA, pstrState->eCurrentState, bsp_get_slice_value());
                   
                    /* save regiter */
                    if(BSP_NULL != g_sciRegGblAddr)
                    {
                        (void)memcpy_s((void *)g_sciRegGblAddr,SCI_RECORD_REG_SIZE,(void *)SCI_BASE_ADDR,(int)SCI_RECORD_REG_SIZE);
                    }
                    sci_record_data_save(SCI_LOG_NO_DATA);
                    /* coverity[missing_unlock] */
                    return BSP_ERR_SCI_NODATA;
                }

                /* ��������������� */
                ulDataLenPre = ulDataLenCur;
            }
        } while (loop--);

        /* ѭ����ɺ󣬻���û���������� */
        g_strRecBuf.usPrelen = 0;
        g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_OVER;
        local_irq_restore(sciLockKey);

        apBIT_SET((pstrState->pBase->RegIntMask), PL131_REGINTMASK_CHTOUT, 0);

        if(BSP_NULL != g_sciRegGblAddr)
        {
            (void)memcpy_s((void *)g_sciRegGblAddr,SCI_RECORD_REG_SIZE,(void *)SCI_BASE_ADDR,(int)SCI_RECORD_REG_SIZE);
        }

        SCI_RECORD_EVENT(SCI_EVENT_ERROR_NODATA, pstrState->eCurrentState, __LINE__);
        
        return BSP_ERR_SCI_NODATA;
    }
}


/******************************************************************
* Function:  sciAllDataRead
*
* Description:
*      Read all data in the driver's buffer.
*      This function wil be called when the PS software overtime while waiting
*      for driver's callback
*
* Calls:
*      memcpy
*
* Called By:  PS Software
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
* pucRecData - The data buffer to be copied to.
* ulLength - number of bytes/characters received in driver's buffer
*
* Outputs:
* none
*
* Return Value:
*  OK - transmission commenced successfully
*  DR_ERR_SCI_PARAERROR - invalid mode specified
*
******************************************************************/
s32 bsp_sci_all_data_read(u32 *pulLength, u8 *pucRecData)
{
    s32 sciLockKey = 0;
    u32 ulLength = 0;
    u32 ulLoopIndex = 0;

    if ((NULL == pulLength) || (NULL == pucRecData))
    {
        sci_print_error("(NULL == u32DataLength) || (NULL == pu8DataBuffer)!");
        return BSP_ERR_SCI_INVALIDPARA;
    }

    if (g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    {
        sci_print_error("bsp_sci_all_data_read: not initialized\n");
        return BSP_ERR_SCI_NOTINIT;
    }

    local_irq_save(sciLockKey);
    ulLength   = sci_count_length();
    *pulLength = ulLength;

    /* ��buffer����������ȫ�����ظ��ϲ㣬buffer���*/
    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
    {
        (void)osl_cache_invalid(OSL_DATA_CACHE, (u8 *)g_strRecBuf.usOutBuf, SCI_MAX_DATA_BUF_LEN * sizeof(u32));
        for (ulLoopIndex = 0; ulLoopIndex < ulLength; ulLoopIndex++)
        {
            g_strRecBuf.ucRecBuf[ulLoopIndex] = (u8)(g_strRecBuf.usOutBuf[g_strRecBuf.usStart * sizeof(u16)
                                                                             + ulLoopIndex * sizeof(u16)] & 0xFF);
        }

        (void)memcpy_s(pucRecData, ulLength * (sizeof(u8)),(void *)(&(g_strRecBuf.ucRecBuf[0])), ulLength * (sizeof(u8)));
    }
    else
    {
        /* ��buffer�б�������ݷ��ظ��ϲ�*/
        (void)memcpy_s(pucRecData, (u32)ulLength,(void *)(&(g_strRecBuf.ucRecBuf[g_strRecBuf.usStart])), (u32)ulLength);
    }

    g_strRecBuf.usStart += (u16)ulLength;

    local_irq_restore(sciLockKey);

    return MDRV_OK;
}

/******************************************************************
* Function:  sciATRGet
*
* Description:
*      Get the ATR data in the driver's buffer.
*      This function will be called when the PS software want to parse the ATR.
*
* Calls:
*      memcpy
*
* Called By:  PS Software
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
* pucATRData - The data buffer to be copied to.
* ulLength - number of ATR bytes/characters received in driver's buffer
*
* Outputs:
* none
*
* Return Value:
*  OK - transmission commenced successfully
*  ERROR -failed
*
*
******************************************************************/
s32 bsp_sci_atr_get(u8 * pulLen, u8 *pucATRData,SCI_ATRINFO_S* stSCIATRInfo)
{
    SCI_RECORD_EVENT(SCI_EVENT_API_GET_ATR, g_u32ResetSuccess, __LINE__);

    if((NULL == pulLen) || (NULL == pucATRData) || (stSCIATRInfo == NULL))
    {
        sci_print_error("(NULL == u32DataLength) || (NULL == pu8ATR)||(stSCIATRInfo == NULL)!");
        return BSP_ERR_SCI_INVALIDPARA;
    }


    if ((TRUE == g_strSciState.sATRParams.HasChecksum) && (0 != g_strATRData.ulATRLen))
    {
        *pulLen = g_strATRData.ulATRLen - 1;
        stSCIATRInfo->tckLen = 1;
    }
    else
    {
        *pulLen = g_strATRData.ulATRLen;        
        stSCIATRInfo->tckLen = 0;
    }


    /* ��ATR���ݷ��ظ��ϲ�ƽ̨*/
    (void)memcpy_s(pucATRData, ((g_strATRData.ulATRLen) * (sizeof(u8))),(void *)(g_strATRData.ATRData), ((g_strATRData.ulATRLen) * (sizeof(u8))));
    /*2014��5��26��17:23:25 t=1*/
    (void)memcpy_s(stSCIATRInfo,sizeof(g_sci_atr_info),&g_sci_atr_info,sizeof(g_sci_atr_info));
    

    return MDRV_OK;
}

void sci_deactive_handle_later(void)
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;/* [false alarm]:fortify */

    (void)sci_set_voltage(SCI_VOLTAGE_SWITCH_CLASS_CB2ZERO);
    if(1 == g_sci_api_deactive)
    {
        if(PL131_STATE_NOCARD != pstrState->eCurrentState)
        {
            osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIDeactiveSyncSem);
        }
        sci_print("deac api\n");

        g_u32ResetSuccess = SCI_DEF_NOT_RESET;
        g_sci_api_deactive = 0;
        sci_lowpwr_vote_unlock(SCI_LOWPWR_USIM);
    }
    else
    {
        /* buffer overflow Begin: */   
        if(g_sciRxStGblStru.RxDataRecFlag == SCI_RX_DATA_REC_ERROR || g_sci_detect_state == SIM_CARD_LEAVE || g_sci_detect_state == SIM_CARD_OUT) 
        {
            nActiveT = 10;
            g_sci_voltage_state.sciClassKind = PL131_SCI_Class_B;
            g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_NONE;
            sci_buf_clear(); 
        
        }

        g_u32ResetSuccess = SCI_DEF_NOT_RESET;
        sci_lowpwr_vote_unlock(SCI_LOWPWR_HOTPLUG);
    }
    
    g_SciDeactivateFlag = FALSE;

    return;
}

void sci_vltg_switch_handle_later(void)
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;/* [false alarm]:fortify */
    int retVal = -1;/* [false alarm]:fortify */

    switch(g_sci_voltage_state.sci_vlotage_switch_sense)
    {
        case SCI_VOLTAGE_SWITCH_SENSE_CLASS_C2B_IMMEDIATELY:
        {
            retVal = sci_set_voltage(SCI_VOLTAGE_SWITCH_CLASS_C2B);/* [false alarm]:fortify */
            nActiveT = 0;
            break;
        }
        case SCI_VOLTAGE_SWITCH_SENSE_CLASS_UNKNOW_TRY:
        {
            if(g_sci_voltage_state.sciClassKind == PL131_SCI_Class_B)
            {
                if(nActiveT <= SCI_MAX_USIM_CARD_DETECT_RETRY_CNT)
                {
                    retVal = sci_set_voltage(SCI_VOLTAGE_SWITCH_CLASS_B2B);/* [false alarm]:fortify */
                }
            }
            if(g_sci_voltage_state.sciClassKind == PL131_SCI_Class_C)
            {
                if(nActiveT > SCI_USIM_CLASS_C_DETECT_RETRY_CNT)
                {
                    retVal = sci_set_voltage(SCI_VOLTAGE_SWITCH_CLASS_C2B);/* [false alarm]:fortify */
                }
                else
                {
                    retVal = sci_set_voltage(SCI_VOLTAGE_SWITCH_CLASS_C2C);/* [false alarm]:fortify */
                }
            }
        
            break;
        }
        default:
            g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_NONE;/* [false alarm]:fortify */
            retVal = BSP_ERROR;/* [false alarm]:fortify */
            break;
            
    }
    g_sci_voltage_state.sci_vlotage_switch_sense = SCI_VOLTAGE_SWITCH_SENSE_CLASS_BUTT;

    if(retVal == BSP_OK)/* [false alarm]:fortify */
    {
        g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_NONE;/* [false alarm]:fortify */
        sci_print_info("RecSyncTask & SCI_CLASS_SWITCH_PROCESS: Start to set Vltg as %ld and do UICC activate\n",
          (int)g_sci_voltage_state.sciClassKind, 0, 0, 0, 0, 0);

        pstrState->eCurrentState = PL131_STATE_INACTIVECARD;
        SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pstrState->eCurrentState, __LINE__);
        retVal = appl131_card_active_set(pstrState, TRUE, pstrState->sATRParams.pATRBuffer);
        if(retVal == 0)
        {
            SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pstrState->eCurrentState, __LINE__);
        }
    }
}

/******************************************************************
* Function:  sciRecSyncTask
*
* Description:
*       Demaen Task
*
* Calls:
*      None
*
* Called By:  None
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs:
*  None
*
* Outputs:
*  None
*
* Return Value:
*  None
*
******************************************************************/
void sci_rec_sync_task(void)
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;/* [false alarm]:fortify */
    volatile u32 ulPPSDelayIndex = 0;/* [false alarm]:fortify */
    int retVal = -1;/* [false alarm]:fortify */

    /* coverity[loop_top]*/
    for (;;)
    {
        osl_sem_down(&g_stSciHwCfg.sci_sem.g_SCISynSem);

        /* Do SIM card deactivation operation */
        if (g_SciDeactivateFlag)
        {
            sci_deactive_handle_later();
            continue;
        }

        /*do Vltg switch process*/
        if (g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG == SCI_CLASS_SWITCH_PROCESS)
        {
            sci_vltg_switch_handle_later();
        }
        
        /*Changed for SIM Card compatibility. Begin*/
        /*Launch PPS Request*/
        else if ((g_Pl131_pps_state.PL131_PPS_ACTIVATION) && (PPS_RESPONE_READY == g_Pl131_pps_state.PL131_PPS_Response))
        {
            /*Add needed delay*/
            for (ulPPSDelayIndex = 0; ulPPSDelayIndex < PPS_REQUEST_DELAY; ulPPSDelayIndex++)
            {
                /*Delay enough time to ensure SIM Card had been ready to recieve data*/
            }

            sci_print_info("Launch PPS Request Process in SCI Task!\n");

            /*Call PPS Request Function*/
            pl131_pps_request(pstrState);

            SCI_RECORD_EVENT(SCI_EVENT_PPS_REQ, pstrState->eCurrentState, __LINE__);
        }
        /*use cold reset to activate UICC after 10ms delay*/
        else
        {
            (void)osl_task_delay(1);
            sci_print_info("Not do class switch, but do powerup\n");

            SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

            pstrState->eCurrentState = PL131_STATE_INACTIVECARD;
            SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pstrState->eCurrentState, __LINE__);
            retVal = appl131_card_active_set(pstrState, TRUE, pstrState->sATRParams.pATRBuffer);
            if(retVal == 0)
            {
                SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pstrState->eCurrentState, __LINE__);
            }
        }
    }
}

void sci_hot_plug_task()
{
    /* coverity[loop_top]*/
    for (;;)
    {
        osl_sem_down(&g_stSciHwCfg.sci_sem.g_SCIHotPlugSem);
        sci_print_error("ind = %d\n",g_sci_ind_state);
        switch (g_sci_ind_state)
        {
            case SIM_CARD_OUT:
                if(g_sci_hot_plug_proc_status == SCI_HOT_PLUG_CARD_OUT 
                   || g_sci_hot_plug_proc_status == SCI_HOT_PLUG_CARD_PROCESS)
                {
                    sci_print("current state no need ind %d\n",g_stSciHwCfg.slot_switch_flag);
                    break;
                }

                sci_hotplug_deactive();
            
                g_sci_hot_plug_proc_status = SCI_HOT_PLUG_CARD_OUT;

                if(NULL != g_omSciFuncPtr 
                    && g_stSciHwCfg.slot_switch_flag != SCI_SLOT_SWITCH_CHANGE)
                {
                    ((OMSCIFUNCPTR)g_omSciFuncPtr)(SIM_CARD_OUT);  
                    sci_print("ind out success\n");
                }
                break;
                
            case SIM_CARD_IN:
                if(g_sci_hot_plug_proc_status == SCI_HOT_PLUG_CARD_IN 
                    || (g_sci_hot_plug_proc_status == SCI_HOT_PLUG_CARD_PROCESS))
                {

                    sci_print("current state no need ind %d\n",g_stSciHwCfg.slot_switch_flag);
                    break;
                }
                
                if(NULL != g_omSciFuncPtr
                    && g_stSciHwCfg.slot_switch_flag != SCI_SLOT_SWITCH_CHANGE)
                {
                    g_sci_hot_plug_proc_status = SCI_HOT_PLUG_CARD_PROCESS;
                    ((OMSCIFUNCPTR)g_omSciFuncPtr)(SIM_CARD_IN);
                    sci_print("ind in success\n");
                }
                break;

            default:
                break;
        }
    }
}

/******************************************************************
* Function:  sciIntHandler
*
* Description:
*     intHandle
*
* Calls:
*      memcpy
*
*
* Table Accessed: NONE
*
* Table Updated: NONE
*
* Inputs: NONE
*
* Outputs:NONE
*
* Return Value: NONE
*
*
******************************************************************/
void sci_int_handler(void)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pstrState = &g_strSciState;
    SCI_REG * const pstrBase = pstrState->pBase;
    u32 IntFlags = 0;               /*the interrupts currently invoked*/
    u32 BytesInFIFO = 0;             /*number of bytes in FIFO*/
    s32 IntID = 0;                  /*the interrupt number*/
    PL131_eStateOptions eInitialState = PL131_STATE_UNINIT;
    u32 FIFOData   = 0;                /*Data in SCI Rx/Tx FIFO, R/W through Data Reg*/
    u32 u32LockKey = 0;
    int retVal = 0;
    //EX_REPORT_SCI_S stReportSci;

    //PROCESS_ENTER(BSP_SCI_TRACE);
    (void)disable_irq(g_stSciHwCfg.int_number);

    /*read and clear the interrupt flags*/
    IntFlags = pstrBase->RegIntStatus;
    writel(IntFlags,SCI_REG_INTCLEAR);

    eInitialState = pstrState->eCurrentState;

    /* coverity[overflow_const]*/
    /* coverity[assignment] */
    IntID = 0xFFFFFFFF;

    while (IntFlags)
    {
        /* coverity[incr] */
        IntID++;

        if (IntFlags & 1)
        {
            switch (IntID)
            {
                /*------------------------CARD INSERTION-----------------------*/
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_CARDIN:
            {
                /*sim card û������ж�*/
                break;
            }

                /*-----------------------CARD REMOVAL------------------------*/
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_CARDOUT:
            {
                /*NOTIFICATION - card has been removed*/
                /*sim card û������ж�*/
                break;
            }

                /*-----------------------CARD ACTIVATION-------------------------------*/
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_CARDUP:
            {
                /* record debug info */
                SCI_RECORD_EVENT(SCI_EVENT_INTR_CARD_UP, pstrState->eCurrentState, __LINE__);

                (void)appl131_clean(pstrState);                      /*terminate transfer*/
                /*NOTIFICATION - card has been activated*/

                pstrState->eCurrentState = PL131_STATE_WAITATR;
                pstrState->sATRParams.Grouping = PL131_ATR_GROUPSTART;               /*ready for ATR*/
                pstrState->sATRParams.BufferAt = 0;
                sci_print_info("\r\n bsPL131_REGINTMASK_CARDUP");

                /*reset pointer for ATR*/
                break;
            }

                /*-----------------------CARD DEACTIVATION---------------------------*/
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_CARDDOWN:
            {

                (void)appl131_clean(pstrState);               /*terminate transfer*/
                (void)pl131_registers_init(pstrState);         /*restore state*/
                
                apBIT_SET(pstrState->pBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 0); /*disable RX interrupt*/
                

                SCI_RECORD_EVENT(SCI_EVENT_INTR_CARD_DOWN, pstrState->eCurrentState, __LINE__);

                pstrState->eCurrentState = PL131_STATE_INACTIVECARD;

                /*Do SIM card deactivation operation */
                if (g_SciDeactivateFlag)
                {
                    /* ֪ͨ�ϲ�ƽ̨sim���Ѿ��µ�*/
                    if (NULL != g_FuncCb)
                    {
                        (void)g_FuncCb((u32)SCI_EVENT_CARD_DEACTIVE_SUCCESS, NULL);
                    }

                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

                    osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCISynSem);
                    break;
                }

                if (g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG == SCI_CLASS_SWITCH_PROCESS)
                {
                    osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCISynSem);

                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);
                }
                /*Changed for Card Status Type Error, Change Begin*/
                else
                {
                    pstrState->eCurrentState = PL131_STATE_NOCARD;

                    /*Do SIM card deactivation operation*/
                    g_SciDeactivateFlag = TRUE;
                    nActiveT = 10;
                    g_sci_voltage_state.sciClassKind = PL131_SCI_Class_B;
                    g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_NONE;
                    osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCISynSem);

                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

                    /*Do SIM card deactivation operation*/
                }

                /* Changed for Card Status Type Error, Change End*/
                sci_print_info("apPL131_CARD DEACTIVATION\n");

                g_strRecBuf.usPrelen = 0;
                g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_OVER;

                break;
            }

                /*-----------------------ERRORS AND TIMEOUTS-------------------------*/
                /*If clock stop mode supported the following timeouts can occur*/
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_CLKSTPI:
            {
                apBIT_SET(pstrBase->RegIntMask, PL131_REGINTMASK_CLKSTPI, 0);
                osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIClockStopSem);

                
                SCI_RECORD_EVENT(SCI_EVENT_INTR_CLK_STOP, pstrState->eCurrentState, __LINE__);

                /*NOTIFICATION - clock has been stopped*/

                sci_print_info("\r\n bsPL131_REGINTMASK_CLKSTPI");

                break;
            }
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_CLKACTI:
            {
                apBIT_SET(pstrBase->RegIntMask, PL131_REGINTMASK_CLKACTI, 0);

                /*Set Current SCI CLK Status Flag*/
                osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIClockStartSem);

                SCI_RECORD_EVENT(SCI_EVENT_INTR_CLK_ACTIVE, pstrState->eCurrentState, __LINE__);
                /*NOTIFICATION - clock has been started*/

                sci_print_info("\r\n bsPL131_REGINTMASK_CLKACTI");
                break;
            }

                /*for an ATR start bit timeout*/
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_ATRSTOUT:
            {
                g_sci_hw_abnormal = SCI_HW_STATE_ATRSTOUT;
                SCI_RECORD_EVENT(SCI_EVENT_INTR_ATRSTOUT, pstrState->eCurrentState, __LINE__);

                SCI_RECORD_EXCGBL(SCI_EVENT_INTR_ATRSTOUT, pstrState->eCurrentState, bsp_get_slice_value());

                SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pstrState->eCurrentState, __LINE__);

                if (g_sci_voltage_state.sciClassKind == PL131_SCI_Class_C)
                {
                    sci_print_info("bsPL131_REGINTMASK_ATRSTOUT: We will move in class switch right now\n");
                    g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_PROCESS;
                    pstrState->eCurrentState = PL131_STATE_INACTIVECARD;
                    sci_print_info("bsPL131_REGINTMASK_ATRSTOUT: Do Deactivation Process No1, cause bsPL131_REGINTMASK_ATRSTOUT\n");
                    g_sci_voltage_state.sci_vlotage_switch_sense = SCI_VOLTAGE_SWITCH_SENSE_CLASS_C2B_IMMEDIATELY;
                    SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH, pstrState->eCurrentState, __LINE__);

                }
                else
                {
                    /*for future use, for example to report UICC not exist*/
                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);
                    sci_check_current_state(pstrState->eCurrentState); 
                    /* û��ATR  �����ͷ��ź���*/
                    if (NULL != g_FuncCb)
                    {
                        (BSP_VOID)g_FuncCb((u32)SCI_EVENT_CARD_RESET_SUCCESS, NULL);
                    }
                }

                apBIT_SET(pstrBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);

                break;
            }
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_CHTOUT:
            case bsPL131_REGINTMASK_BLKTOUT:
            {
                BSP_U16 event;

                switch (IntID)
                {
                case bsPL131_REGINTMASK_BLKTOUT:
                    event = SCI_EVENT_INTR_BLKOUT;
                    break;
                /* coverity[equality_cond] */
                case bsPL131_REGINTMASK_CHTOUT:
                default:
                    event = SCI_EVENT_INTR_CHOUT;
                    
                    g_sci_hw_abnormal = SCI_HW_STATE_CHTOUT;
                    break;
                }

                SCI_RECORD_EVENT(event, pstrState->eCurrentState, __LINE__);

                /* record debug info */
                sci_print_info("bsPL131_REGINTMASK_CHTOUT\r\n");

                if ((PL131_STATE_READATR == pstrState->eCurrentState))
                {
                    g_strRecBuf.usPrelen = 0;

                    sci_print_info("CHTOUT & SCI_CLASS_SWITCH_PROCESS: Do apPL131_CARDDEACT cause WWT excess in ATR process! RegChTimeLS = %l#x\r\n",
                              (int)pstrBase->RegChTimeLS, 0, 0, 0, 0, 0);
                    
                    pstrState->eCurrentState = PL131_STATE_INACTIVECARD;
                    SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pstrState->eCurrentState, __LINE__);
                    SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH, pstrState->eCurrentState, __LINE__);

                    sci_class_switch_sence_try();

                     
      
                }
                else if (g_strRecBuf.usPrelen != 0)
                {
                    BytesInFIFO = readl(SCI_REG_RXCOUNT);

                    /*Fix SCI FIFO overrun and characeter time out bug, Begin*/
                    sci_print_info("CHTOUT Interrupt, g_strRecBuf.usPrelen = %ld, g_strRecBuf.usStart = %ld, g_strRecBuf.usLength = %ld, BytesInFIFO = %l#x\n\n",
                              (int)g_strRecBuf.usPrelen, (int)g_strRecBuf.usStart,
                              (int)g_strRecBuf.usLength, (int)BytesInFIFO, 0, 0);

                    /*Fix SCI FIFO overrun and characeter time out bug, End*/

                    if (g_ulChTOUTDeactEn)
                    {

                        sci_print_info("Do apPL131_CARDDEACT cause WWT excess when PS is communication with SIM!\n", 0, 0, 0,
                                  0, 0,
                                  0);
                        pstrState->eCurrentState = PL131_STATE_INACTIVECARD;
                        apBIT_SET(pstrBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);
                        SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pstrState->eCurrentState, __LINE__);

                    }
                    /*2014��5��28��10:03:13 �յ�BWT�жϣ��ͷ��ź���*/
                    if(pstrState->eProtocol == apPL131_PROTOCOL_T1_BLOCK)
                    {
                        
                        if(event == SCI_EVENT_INTR_BLKOUT)
                        {
                            g_sci_BWT_int_flag = 1;
                            osl_sem_up(&g_stSciHwCfg.sci_sem.g_SCIBWTSem);
                        }
                    }
                    
                }
                else if ((g_Pl131_pps_state.PL131_PPS_ACTIVATION) && (PL131_STATE_READATR == pstrState->eCurrentState))
                {
                    sci_print_info("PPS timeout in CHTOUT Interrupt, we set warm reset here, this is the No.%d reset process\n",
                              g_Pl131_pps_state.PL131_PPS_ACTIVATION, 0, 0, 0, 0, 0);

                    SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_START, pstrState->eCurrentState, __LINE__);

                    retVal = appl131_card_active_set(pstrState, TRUE, pstrState->sATRParams.pATRBuffer);
                    if(retVal == 0)
                    {
                        SCI_RECORD_EVENT(SCI_EVENT_CARD_ACTIVE_SUCCESS, pstrState->eCurrentState, __LINE__);
                    }
      
                }

                break;
            }
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_RORI:
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_TXERR:
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_ATRDTOUT:
            {
                BSP_U16 event;

                /* coverity[dead_error_condition] */
                switch (IntID)
                {
                case bsPL131_REGINTMASK_RORI:
                    event = SCI_EVENT_INTR_RORI;
                    g_sci_hw_abnormal = SCI_HW_STATE_RORI;
                    break;
                case bsPL131_REGINTMASK_TXERR:
                    event = SCI_EVENT_INTR_TX_ERR;
                    g_sci_hw_abnormal = SCI_HW_STATE_TXERR;
                    break;
                case bsPL131_REGINTMASK_ATRDTOUT:
                    event = SCI_EVENT_INTR_ATRDTOUT;
                    g_sci_hw_abnormal = SCI_HW_STATE_ATRSTOUT;
                    break;
                case bsPL131_REGINTMASK_BLKTOUT:
                /* coverity[dead_error_begin] */
                default:
                    event = SCI_EVENT_INTR_BLKOUT;
                    break;
                }

                SCI_RECORD_EVENT(event, pstrState->eCurrentState, __LINE__);

                
                sci_print_info("\r\n bsPL131_REGINTMASK_RORI TXERR ATRDTOUT BLKTOUT.IntID = %d", IntID, 0, 0, 0, 0, 0);
                switch (eInitialState)
                {
                case PL131_STATE_WAITATR:                             /*in ATR mode*/
                case PL131_STATE_READATR:                             /*in ATR mode*/
                {
                    SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pstrState->eCurrentState, __LINE__);
                    SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH, pstrState->eCurrentState, __LINE__);

                    sci_class_switch_sence_try();
                    break;
                }

                    /*abort a transmission, if any*/
                case PL131_STATE_TX:
                {
                    /*NOTIFICATION - transmission error*/
                    apBIT_SET(pstrBase->RegIntMask, PL131_REGINTMASK_TXTIDE, 0);                   /*disable TX interrupt*/

                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);
 
                    break;
                }

                    /*abort a receiption, if any*/
                case PL131_STATE_READY:
                case PL131_STATE_RX:
                {
                    g_strRecBuf.usPrelen = 0;
                    g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_OVER;
                    break;
                }
                case PL131_STATE_UNINIT:
                case PL131_STATE_FIRSTINIT:
                case PL131_STATE_DISABLED:
                case PL131_STATE_NOCARD:
                case PL131_STATE_INACTIVECARD:
                default:
                {
                    break;
                }
                }

                IntFlags = 0;                   /*no other interrupts allowed*/
                (void)appl131_clean(pstrState);             /*terminate transfer*/

                /* ֪ͨ�ϲ�ƽ̨���ͻ��߽��շ�������*/
                if (NULL != g_FuncCb)
                {
                    (void)g_FuncCb((u32)SCI_EVENT_CARD_TX_ERR, NULL);

                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);
                }

                /* �쳣״̬�ϱ���ƽ̨*/
                break;
            }

                /*-------------------------RECEIVE DATA------------------------*/
                /* Modification: Optimize SCI interrupt process*/
            /* coverity[equality_cond] */
            case bsPL131_REGINTMASK_RTOUT:
                
            case bsPL131_REGINTMASK_RXTIDE:
            {
                if(IntID == bsPL131_REGINTMASK_RTOUT)
                {
                    SCI_RECORD_EVENT(SCI_EVENT_INTR_RTOUT, pstrState->eCurrentState, __LINE__);
                }
                /*an inactive card MUST be performing ATR*/
                /*a character moves us into ATR start*/
                if (eInitialState <= PL131_STATE_WAITATR)
                {
                    pstrState->eCurrentState = PL131_STATE_READATR;
                    eInitialState = PL131_STATE_READATR;

                    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);
                }

                //process ATR
                if (eInitialState == PL131_STATE_READATR)
                {  
                    pl131_atr_process(pstrState, pstrBase->RegData);
                    
                }
                else
                {
                    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
                    {
                        sci_print_error("IntHandler:RXTIDE or RTOUT, transient sci rx interrupt happenned in SCI DMA Rx.\r\n\n",
                                  0,0, 0, 0, 0, 0);
                    }
                    else
                    {
                        BytesInFIFO = readl(SCI_REG_RXCOUNT);

                        //receive as many bytes as are available
                        while (BytesInFIFO)
                        {
                            FIFOData = pstrBase->RegData;
                            FIFOData = BIT_GET(FIFOData, PL131_REGDATA_DATA);
                            (void)sci_buf_add((u8*)&FIFOData);
                            BytesInFIFO--;
                        }

                        pstrState->eCurrentState = PL131_STATE_READY;
                    }
                }

                break;
            }

                /*-------------------------TRANSMIT DATA-----------------------------*/
            case bsPL131_REGINTMASK_TXTIDE:
            {
                //modified by yangzhi 20130218 Begin:
                local_irq_save(u32LockKey);
                //modified by yangzhi 20130218 End!

                if (eInitialState == PL131_STATE_TX)
                {
                    BytesInFIFO = BIT_GET(pstrBase->RegTxCount, PL131_REGTXCOUNT_DATA);

                    /*transmit as many bytes as there is space*/
                    while ((BytesInFIFO < PL131_FIFO_SIZE_TX) && pstrState->DataLength)
                    {
                        pstrBase->RegData = (u32)(*pstrState->pDataBuffer);
                        pstrState->DataLength--;
                        pstrState->pDataBuffer++;
                        BytesInFIFO++;                            /*track the bytes in the FIFO*/
                    }
                }

                /*check for termination*/
                if ((!pstrState->DataLength) || (eInitialState != PL131_STATE_TX))
                {
                    /*reset to normal state*/
                    pstrState->pDataBuffer = NULL;
                    pstrState->DataLength = 0;
                    pstrState->eCurrentState = PL131_STATE_READY;
                    BIT_SET(pstrBase->RegIntMask, PL131_REGINTMASK_TXTIDE, 0);       /*disable TX interrupt*/
                    BIT_SET(pstrBase->RegTide, PL131_REGTIDE_TX, 0);
                    BIT_SET(pstrBase->RegCtrl1, PL131_REGCTRL1_MODE, apPL131_RX_FROM_CARD);
                    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
                    {
                        //Set SCI Rx Data Receive Flag is Start
                        g_sciRxStGblStru.RxDataRecFlag = SCI_RX_DATA_REC_START;

                        //Enable SCI DMA Rx
                        appl131_dma_mode_set(&g_strSciState, apPL131_DMA_RX);

                        /*Mask SCI Rx Int*/
                        BIT_SET(pstrBase->RegIntMask, PL131_REGINTMASK_RXTIDE, 0);
                                                
                    }
                }

                //modified by yangzhi 20130218 Begin:
                local_irq_restore((int)u32LockKey);
                //modified by yangzhi 20130218 End!

                break;
            }

                /*------------------------------------------------------------------*/
            default:
            {
                break;
            }
            } /*end of switch*/
            if (eInitialState != pstrState->eCurrentState)
            {
            }
        }

        IntFlags >>= 1;   /*shift to next bit*/
    } /*end of while*/
    
    
    (void)enable_irq(g_stSciHwCfg.int_number);
    //PROCESS_EXIT(BSP_SCI_TRACE);
    return;
}

/******************************************************************
*  Function:  sciDeactive
*
*  Description:
*      deactive sim card
*
*  Calls:
*      None
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Outputs:
*         None
*
* Return Value:
*   OK
*
******************************************************************/
u32 bsp_sci_deactive( void )
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;
    SCI_REG * const pstrBase = pstrState->pBase;
               
    sci_print_error("begin deactive\n");

    SCI_RECORD_EVENT(SCI_EVENT_API_DECATIVE, pstrState->eCurrentState, __LINE__);

    if ((pstrState->eCurrentState >= PL131_STATE_RX) && (pstrState->eCurrentState <= PL131_STATE_TX))
    {
        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

        sci_print_error("not initialized\n");

        return BSP_ERR_SCI_NOTREADY;
    }
    else if (pstrState->eCurrentState >= PL131_STATE_WAITATR)
    {
        /* unvote and enable clk */
        sci_lowpwr_vote_lock(SCI_LOWPWR_USIM);

        /*Set SCI Deactivate Flag*/
        g_SciDeactivateFlag = TRUE;
        g_sci_api_deactive = 1;
        

        /*Set Other Global Flags for Safe*/
        nActiveT = 10;
        g_sci_voltage_state.sciClassKind = PL131_SCI_Class_B;
        g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_NONE;

        sci_buf_clear(); //added by yangzhi in 2010-12-2


        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

        if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
        {
            SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, g_sciRxStGblStru.RxModeFlag, __LINE__);

            if(bsp_edma_channel_stop(g_sciRxStGblStru.DmaChnNo) <0)
            {
                sci_print_error("dma transfer stop failede\n");
                return BSP_ERR_SCI_DISABLED;
            }
        }

        SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pstrState->eCurrentState, __LINE__);

        /*Deactivate SIM Card*/
        pstrState->eCurrentState = PL131_STATE_INACTIVECARD;
        sci_print_info("Deactivate SIM card. g_SciDeactivateFlag = %ld, nActiveT = %ld, sciClassKind = %ld, ucSCI_CLASS_SWITCH_FLAG = %ld.\r\n\n",
                  (int)g_SciDeactivateFlag, (int)nActiveT, (int)g_sci_voltage_state.sciClassKind, (int)g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG, 0, 0);

        apBIT_SET(pstrBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);

        g_strATRData.ulATRLen = 0;
        
        /*g_u32ResetSuccess = SCI_DEF_NOT_RESET;*/
        /* coverity[unchecked_value] */
        (void)osl_sem_downtimeout(&g_stSciHwCfg.sci_sem.g_SCIDeactiveSyncSem, DEACTIVE_SYNC_DELAY);
        

    }   
    else 
    {        
        sci_lowpwr_vote_unlock(SCI_LOWPWR_USIM);
        sci_print_error("Card not activation, not need to do deactivation, satus is 0x%d\r\n\n",pstrState->eCurrentState);       
    }

    return MDRV_OK;
}

/******************************************************************
*  Function:  sciPSClassSwitch
*
*  Description:
*      Do SCI class switch if current voltage is not the highest
*      voltage class.
*
*  Calls:
*      None
*
*  Called By:  PS software
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Outputs:
*         None
*
* Return Value:
*   OK    - Current Voltage is not highest one, do voltage class
*           switch.
*   ERROR - failed
*   1     - Current Voltage is the highest one, not do voltage
*           class switch.
*
******************************************************************/
s32 bsp_sci_vltg_class_switch(void)
{
    /*Create pointers to the instance data block and the register base*/
    SCI_STATE_STRU * const pstrState = &g_strSciState;/* [false alarm]:fortify */
    SCI_REG * const pstrBase = pstrState->pBase;/* [false alarm]:fortify */
    s32 lErroRet = MDRV_OK;/* [false alarm]:fortify */

    SCI_RECORD_EVENT(SCI_EVENT_API_CLASS_SWITCH, pstrState->eCurrentState, __LINE__);

    if (g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)/* [false alarm]:fortify */
    {
        sci_print_error("not initialized\n");/* [false alarm]:fortify */
        return BSP_ERR_SCI_NOTINIT;
    }

    /*busy ״̬��֧���л���ѹ*/
    if ((pstrState->eCurrentState >= PL131_STATE_RX) && (pstrState->eCurrentState <= PL131_STATE_TX))
    {
        sci_print_error("eCurrentState busy\n");/* [false alarm]:fortify */
        return BSP_ERR_SCI_NOTREADY;
    }

    /*Process according to current voltage is the highest one or not*/
    switch (g_sci_voltage_state.sciClassKind)
    {
        /*current voltage is not the highest one*/
        case (PL131_SCI_Class_C):
        {
            if (0x04 == (pstrState->sATRParams.ClassInd & 0x3F))
            {
                sci_print_error("don't support CLASS_B\n");
                lErroRet = BSP_ERR_SCI_VLTG_HIGHEST;/* [false alarm]:fortify */
                break;
            }


            /*Do class switch if current SCI driver state is ready/rx/tx*/
            if (PL131_STATE_READY <= pstrState->eCurrentState)
            {
                sci_lowpwr_vote_lock(SCI_LOWPWR_USIM);

                appl131_dma_mode_set(&g_strSciState, apPL131_DMA_OFF);     //added by yangzhi for dma test
                g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG  = SCI_CLASS_SWITCH_PROCESS;
                pstrState->eCurrentState = PL131_STATE_INACTIVECARD;

                SCI_RECORD_EVENT(SCI_EVENT_REGISTER_FINISH, pstrState->eCurrentState, __LINE__);
                g_sci_voltage_state.sci_vlotage_switch_sense = SCI_VOLTAGE_SWITCH_SENSE_CLASS_C2B_IMMEDIATELY;
                
                SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_SWITCH, pstrState->eCurrentState, __LINE__);
  
                apBIT_SET(pstrBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);
                
                
                lErroRet = MDRV_OK;/* [false alarm]:fortify */
            }
            else
            {
                sci_print_error("The current vltg is PL131_SCI_Class_C, but pstrState->eCurrentState = %ld\n\n",
                          (int)pstrState->eCurrentState, 0, 0, 0, 0, 0);
                lErroRet = BSP_ERR_SCI_CURRENT_STATE_ERR;/* [false alarm]:fortify */
            }

            break;
        }

        /*current voltage is the highest one*/
        case (PL131_SCI_Class_B):
        {
            sci_print_info("sciPSClassSwitch & PL131_SCI_Class_B: The current vltg is PL131_SCI_Class_B, not do class switch.\n\n",
                      0, 0, 0, 0, 0, 0);
            lErroRet = BSP_ERR_SCI_VLTG_HIGHEST;/* [false alarm]:fortify */
            break;
        }
        default:
        {
            sci_print_error("bsp_sci_vltg_class_switch: Unknow Error Happenned! pstrState->eCurrentState = %ld; Current Vltg is %ld; Current class switch state is %ld!\n\n",
                      (int)pstrState->eCurrentState, (int)g_sci_voltage_state.sciClassKind, (int)g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG, 0, 0, 0);
            lErroRet = BSP_ERR_SCI_CURRENT_VLTG_ERR;/* [false alarm]:fortify */
        }
    }

    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, lErroRet, __LINE__);

    if(BSP_ERR_SCI_VLTG_HIGHEST==lErroRet)
    {
        return BSP_SCI_VLTG_SWITCH_NONEED;
    }
    else
    {
        return lErroRet;
    }
}

/******************************************************************
*  Function:  sciShowVltgVal
*
*  Description:
*      Display current SIM vltg supported by LDO 11.
*
*  Calls:
*      None
*
*  Called By:  PS software
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Outputs:
*         None
*
* Return Value:
*         None
*
******************************************************************/
u32 bsp_sci_show_vltg_val(u32 * pu32Vltgval)
{
    if(NULL == pu32Vltgval)
    {
        sci_print_error("NULL == pu32Vltgval!",0,0,0,0,0,0);
        return BSP_ERR_SCI_INVALIDPARA;
    }

    if (g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    {
        sci_print_error("not initialized\n", 0, 0, 0, 0, 0, 0);
        return BSP_ERR_SCI_NOTINIT;
    }

    sci_print_info("Current Working Voltage is %ld, and Current Class Flag is %ld\n\n",
              (int)g_sci_voltage_state.sciClassKind, (int)g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG, 0, 0, 0, 0);

    *pu32Vltgval = g_sci_voltage_state.sciClassKind;

    return MDRV_OK;
}


/*****************************************************************************
* �� �� ��  : bsp_sci_reg_event
*
* ��������  : ���ӿ�����ע��ص�����
*
* �������  : u32 u32Event      �¼����ͣ����������֣�
*                                    0x1���忨��
*                                    0x2���ο���
*                                    0x4�����µ磻
*                                    0x8�����ϵ磻
*                                    0x10�������ݣ�
*                                    0x20���������ݴ���
*              Sci_Event_Func * pFunc   �ص�����
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*          BSP_ERR_SCI_INVALIDPARA
* �޸ļ�¼  : 2009��6��29��   liumengcun  creat
*
*****************************************************************************/
u32 bsp_sci_reg_event(u32 u32Event, Sci_Event_Func pFunc)
{
    if (NULL == pFunc)
    {
        sci_print_error("\r\n bsp_sci_reg_event: pFunc is null");
        return BSP_ERR_SCI_INVALIDPARA;
    }
    sci_reg_event(u32Event, pFunc);

    return MDRV_OK;
}


/******************************************************************
*  Function:  sciGetClkStatus
*
*  Description:
*      Output current SIM clock status.
*
*  Calls:
*      None
*
*  Called By:  PS software
*
*  Table Accessed: NONE
*
*  Table Updated: NONE
*
*  Input:
*         None
*
*  Outputs:
*         pulSciClkStatus - 0: SCI clock start
*                           1: SCI clock stop
*
* Return Value:
*         OK - Done successful.
*         ERROR - NULL pointer error.
*
******************************************************************/
s32 bsp_sci_get_clk_status(u32 *pulSciClkStatus)
{
    if (NULL == pulSciClkStatus)
    {
        sci_print_error("bsp_sci_get_clk_status: NULL == pu32SciClkStatus!");
        return BSP_ERR_SCI_INVALIDPARA;
    }

    if (g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    {
        sci_print_error("bsp_sci_get_clk_status: not initialized\n");
        return BSP_ERR_SCI_NOTINIT;
    }

    if (g_sci_lowpower_vote_state == 0)
    {
        *pulSciClkStatus = (u32)apPL131_CLOCK_STOP;
    }
    else
    {
        *pulSciClkStatus = (u32)apPL131_CLOCK_START;
    }

    return MDRV_OK;
}

/******************************************************************
* Description:
* start/stop SCI clock
*
* Inputs:
* ucClkStatusMode - If the card supports clock stop mode, this parameter is used
*                   to set SIM clock voltage high or low status when passed into
*                   SIM clock stop mode.
*
* ulCardType - card type that identify SIM or USIM card.
*
* Outputs:
* none
*
* Return Value:
*  OK - successful completion
*  ERROR - failed
*  DR_ERR_SCI_PARAERROR - invalid mode specified
*  DR_ERR_SCI_UNSUPPORTED - not support such a operation
******************************************************************/
s32 bsp_sci_clk_status_cfg(u32 ucClkStatusMode)
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;
    s32 lSciErroRet = MDRV_OK;
    
    SCI_RECORD_EVENT(SCI_EVENT_API_CLOCK_STOP, pstrState->eCurrentState, __LINE__);

    if (ucClkStatusMode >= SCI_CLK_STATE_BUTT)/* [false alarm]:fortify */
    {
        sci_print_error("bsp_sci_clk_status_cfg: enTimeStopCfg == 0x%x!",ucClkStatusMode,0,0,0,0,0);/* [false alarm]:fortify */

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

        return BSP_ERR_SCI_INVALIDPARA;
    }

    if (g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    { 
        sci_lowpwr_vote_unlock(SCI_LOWPWR_USIM);
        return BSP_ERR_SCI_NOTINIT;
    }

    /*busy ״̬��֧��ֹͣʱ��*/
    if ((pstrState->eCurrentState >= PL131_STATE_RX) && (pstrState->eCurrentState <= PL131_STATE_TX))
    {
        sci_print_error("bsp_sci_clk_status_cfg: currentstate busy \n");

        SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, pstrState->eCurrentState, __LINE__);

        return BSP_ERR_SCI_NOTREADY;
    }

    // ��ȫ����ATR��ָʾ��������ע�ϲ㴫�ݵĲ���

    if ((apPL131_CLOCK_START == g_ulSciClkTimeStpFlag))
    {
        lSciErroRet = sci_clock_stop_mode_cfg(apPL131_CLOCK_STOP, ucClkStatusMode);
        if (lSciErroRet != MDRV_OK)
        {
            sci_lowpwr_vote_unlock(SCI_LOWPWR_USIM);
            sci_print_error("bsp_sci_clk_status_cfg: Open SIM Clock Stop Mode Failure.lSciErroRet = %ld.\r\n\n",\
                      (int)lSciErroRet,0,0,0,0,0);

            return lSciErroRet;
        }

        if (MDRV_OK != osl_sem_downtimeout(&g_stSciHwCfg.sci_sem.g_SCIClockStopSem, 100))
        {
            sci_print_error("bsp_sci_clk_status_cfg:wait clock stop interrupt error!\n");

            return BSP_OK;
        }

            /*Set Current SCI CLK Status Flag*/
        g_ulSciClkTimeStpFlag = apPL131_CLOCK_STOP;
        sci_lowpwr_vote_unlock(SCI_LOWPWR_USIM);
        
    }

    SCI_RECORD_EVENT(SCI_EVENT_BEYOND_LOG, lSciErroRet, __LINE__);

    return lSciErroRet;
}


/*****************************************************************************
* �� �� ��  : bsp_sci_excreset_times
*
* ��������  : ���ӿ������ϲ������쳣��λ����
*
* �������  : ExcResetTimes �쳣��λ����
*
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*             BSP_ERR_SCI_INVALIDPARA
*
* �޸ļ�¼  : 2010��8��24��   zhouluojun  creat
*
*****************************************************************************/
s32 bsp_sci_excreset_times(u32 ExcResetTimes)
{
    if (ExcResetTimes > 6)
    {
        sci_print_error("Set ExcResetTimes(%d) > 6 %d",ExcResetTimes,0,0,0,0,0);
        return BSP_ERR_SCI_INVALIDPARA;
    }

    g_SciExcResetTimes = ExcResetTimes;

    return BSP_OK;
}

/*****************************************************************************
* �� �� ��  : bsp_sci_record_data_save
*
* ��������  : ���ӿ����ڱ����ά�ɲ���Ϣ��yaffs��
*
* �������  : ��
*
* �������  : ��
*
* �� �� ֵ  : OK    �����ɹ�
*             ����   ����ʧ��
*
* �޸ļ�¼  : 2011��5��21��   yangzhi  creat
*
*****************************************************************************/
u32 bsp_sci_record_data_save(SCI_LOG_MODE log_mode)
{
    return sci_record_data_save(log_mode);
}

/*****************************************************************************
* �� �� ��  : bsp_sci_record_log_read
*
* ��������  : ���ӿڻ�ȡsim���쳣ʱ��λ��Ϣ
* �������  : pucDataBuff: ��ȡ��λ��Ϣ��buffer
              ulMaxLength: ���ֵ���ж�ʹ��
*
* �� �� ֵ  : pulLength: ��ȡ���ݳ���
*
* �޸ļ�¼  : 2011��5��21��   yangzhi  creat
*
*****************************************************************************/
s32 bsp_sci_record_log_read(unsigned char *pucDataBuff, unsigned int * pulLength, unsigned int ulMaxLength)
{
    return sci_record_log_read(pucDataBuff, pulLength, ulMaxLength);
}


s32 sci_set_voltage(SCI_VOLTAGE_SWITCH_DIRECTION direction)
{
    int retVal = 0;

    if(g_stSciHwCfg.sci_pmu == NULL)
    {
        return BSP_ERROR;
    }
    if(direction != SCI_VOLTAGE_SWITCH_CLASS_ZERO2CB)
    {
        (void)regulator_disable(g_stSciHwCfg.sci_pmu);/* [false alarm]:fortify */
        SCI_RECORD_EVENT(SCI_EVENT_REGULATOR_DOWN, g_sci_voltage_state.sciClassKind, __LINE__);
        (void)osl_task_delay(2);
    }

    
    switch(direction)
    {
        case SCI_VOLTAGE_SWITCH_CLASS_C2C:
            {
                if(g_sci_voltage_state.sciClassKind == PL131_SCI_Class_B)
                {
                    SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_ERROR, g_sci_voltage_state.sciClassKind, __LINE__);
                    return BSP_ERROR;
                }
            
                retVal = regulator_set_voltage(g_stSciHwCfg.sci_pmu,1800000,1800000);/*[false alarm]:*/
                SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_CLASS_C2C, g_sci_voltage_state.sciClassKind, __LINE__);
                g_sci_voltage_state.sciClassKind= PL131_SCI_Class_C;
                break;
            }
        case SCI_VOLTAGE_SWITCH_CLASS_C2B:
            {
                if(g_sci_voltage_state.sciClassKind == PL131_SCI_Class_B)
                {
                    SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_ERROR, g_sci_voltage_state.sciClassKind, __LINE__);
                    return BSP_ERROR;           
                }
                retVal = regulator_set_voltage(g_stSciHwCfg.sci_pmu,3000000,3000000);/*[false alarm]:*/
                SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_CLASS_C2B, g_sci_voltage_state.sciClassKind, __LINE__);
                g_sci_voltage_state.sciClassKind= PL131_SCI_Class_B;
                break;
            }
        case SCI_VOLTAGE_SWITCH_CLASS_B2B:
            {
                if(g_sci_voltage_state.sciClassKind == PL131_SCI_Class_C)
                {
                    SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_ERROR, g_sci_voltage_state.sciClassKind, __LINE__);
                    return BSP_ERROR; 
                }
                retVal = regulator_set_voltage(g_stSciHwCfg.sci_pmu,3000000,3000000);/*[false alarm]:*/
                SCI_RECORD_EVENT(SCI_EVENT_VOLTAGE_CLASS_B2B, g_sci_voltage_state.sciClassKind, __LINE__);
                g_sci_voltage_state.sciClassKind= PL131_SCI_Class_B;
                break;
            }
       case SCI_VOLTAGE_SWITCH_CLASS_CB2ZERO:
            {        
   
                break;
            }
       case SCI_VOLTAGE_SWITCH_CLASS_ZERO2CB:
       {
            
             if (g_SciExcResetTimes <= 2)
             {
                 g_sci_voltage_state.sciClassKind = PL131_SCI_Class_C;

                 retVal = regulator_set_voltage(g_stSciHwCfg.sci_pmu,1800000,1800000);
                 if(retVal != 0)
                 {
                    SCI_RECORD_EVENT(SCI_EVENT_REGULATOR_ERR,retVal , __LINE__);
                 }
             }
             else
             {
                
                 g_sci_voltage_state.sciClassKind = PL131_SCI_Class_B;
           
                 retVal = regulator_set_voltage(g_stSciHwCfg.sci_pmu,3000000,3000000);
                 if(retVal != 0)
                 {
                    SCI_RECORD_EVENT(SCI_EVENT_REGULATOR_ERR,retVal , __LINE__);
                 } 
             }
            break;
        }
        default:
            return BSP_ERROR;
    }
    /*�ϵ���Ҫ������ʱ*/
    if(direction != SCI_VOLTAGE_SWITCH_CLASS_CB2ZERO)/* [false alarm]:fortify */
    {
        if(BSP_OK != regulator_enable(g_stSciHwCfg.sci_pmu))/* [false alarm]:fortify */
        {
            SCI_RECORD_EVENT(SCI_EVENT_REGULATOR_ERR,0 , __LINE__);
            sci_print_error("get pmu device failed.\n");
            return MDRV_ERROR;
        }
        else
        {
            SCI_RECORD_EVENT(SCI_EVENT_REGULATOR_UP,g_sci_voltage_state.sciClassKind , __LINE__);
        }
        /* [false alarm]:fortify */
        (void)osl_task_delay(2);
    }
    return BSP_OK;
}



void sci_class_switch_sence_try(void)
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;
    SCI_REG *  pBase = pstrState->pBase;
    
    g_sci_voltage_state.ucSCI_CLASS_SWITCH_FLAG = SCI_CLASS_SWITCH_PROCESS;
    g_sci_voltage_state.sci_vlotage_switch_sense = SCI_VOLTAGE_SWITCH_SENSE_CLASS_UNKNOW_TRY;
    apBIT_SET(pBase->RegCtrl2, PL131_REGCTRL2_FINISH, 1);
}


/* T=1 add Begin */

/*****************************************************************************
* �� �� ��  : bsp_sci_set_bwt
*
* ��������  : ���ӿ��������ÿ�ȴ�ʱ��
*
* �������  : nBWT :���ó�ʱʱ��ΪBWT��nBWT��
*
* �������  : ��
*
* �� �� ֵ  : OK/ERROR
* �޸ļ�¼  : 2014��5��22��16:11:48   lixiaofan  creat
*
*****************************************************************************/
int bsp_sci_set_bwt(u32 nBWT)
{
    SCI_STATE_STRU * const pstrState = &g_strSciState;
    BSP_U32 blkTime = 0;
    if(apPL131_PROTOCOL_T1_BLOCK != pstrState->eProtocol|| nBWT == 0)
    {
        return MDRV_ERROR;
    }

    blkTime = nBWT * g_t1_times.BlockTime;
    /*Э���ж�����BWT��������*/
    if(blkTime < PL131_MIN_BLKGUARDTIME_T1  || blkTime > PL131_MAX_BLKGUARDTIME_T1)
        return MDRV_ERROR;
    SCI_RECORD_EVENT(SCI_EVENT_API_SET_BWT, blkTime, __LINE__);
    g_t1_times.BlockTime = blkTime;
    pstrState->pBase->RegBlkTimeMS = ((blkTime) & 0xFFFF0000) >> 16;
    pstrState->pBase->RegBlkTimeMS = ((blkTime) & 0x0000FFFF);
    
    return BSP_OK;

}

/*****************************************************************************
* �� �� ��  : bsp_sci_protocol_switch
*
* ��������  : ���ӿ�����֪ͨ�������T=0��T=1Э�������л�
*
* �������  : RESET_MODE enSIMProtocolMode:��Ҫ�л�Ϊ��Э������
*
* �������  : ��
*
* �� �� ֵ  : OK/ERROR
* �޸ļ�¼  : 2014��5��22��16:11:48   lixiaofan  creat
*
*****************************************************************************/
int bsp_sci_protocol_switch(PROTOCOL_MODE_E enSIMProtocolMode)
{
    SCI_STATE_STRU * const pState = &g_strSciState;
    SCI_REG* pBase = pState->pBase;

    SCI_RECORD_EVENT(SCI_EVENT_API_PROTOCOL_SWITCH, enSIMProtocolMode, __LINE__);
    if(g_u32ResetSuccess != SCI_DEF_RESET_SUCCESS)
    {
        SCI_RECORD_EVENT(SCI_EVENT_ERROR_PROTOCOL_SWITCH, enSIMProtocolMode, __LINE__);
        return BSP_ERR_SCI_CURRENT_STATE_ERR;
    }

    if (enSIMProtocolMode != T0_PROTOCOL_MODE && enSIMProtocolMode != T1_PROTOCOL_MODE )
    {
        SCI_RECORD_EVENT(SCI_EVENT_ERROR_PROTOCOL_SWITCH, enSIMProtocolMode, __LINE__);
        return BSP_ERR_SCI_INVALIDPARA;
    }

    sci_lowpwr_vote_lock(SCI_LOWPWR_USIM);


        
    /*��������õ�Э�����ͺ�Ŀǰ����ʹ�õ�Э��������ͬ���������������ò���*/
    if (pState->eProtocol == (apPL131_eProtocol)enSIMProtocolMode)
    {
        sci_print("the protle stay the same no need change\n ");
        return BSP_OK;
    }

    if (T0_PROTOCOL_MODE == enSIMProtocolMode)
    {
 
        pState->sATRParams.HasChecksum = FALSE;
        pState->eProtocol = apPL131_PROTOCOL_T0_CHAR;

        pBase->RegChGuard = (pState->sATRParams.ChGuard == 255) ? 1 : pState->sATRParams.ChGuard; /*�����ַ������Ĵ���*/
        /*���ÿ鱣��ʱ��*/
        pBase->RegBlkGuard = PL131_DEF_BLKGUARDTIME;
        /*�����ַ���ʱʱ��*/
        pBase->RegChTimeMS = (pState->sSetupParams.CharacterTime & 0xFFFF0000) >> 16;
        pBase->RegChTimeLS = (pState->sSetupParams.CharacterTime & 0x0000FFFF);
        /*T=0ʱ���鳬ʱʱ������ΪĬ��ֵ*/
            pBase->RegBlkTimeMS = ((pState->sSetupParams.BlockTime) & 0xFFFF0000) >> 16;
        pBase->RegBlkTimeLS = ((pState->sSetupParams.BlockTime) & 0x0000FFFF);

        /*Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. Begin*/
        apBIT_SET(pBase->RegCtrl0,PL131_REGCTRL0_RX,pState->sSetupParams.eRxHandshake); /*Open Even Parity Check*/
        apBIT_SET(pBase->RegCtrl0,PL131_REGCTRL0_TX,pState->sSetupParams.eTxHandshake);
        apBIT_SET(pBase->RegRetry,PL131_REGRETRY_RX,pState->sSetupParams.RxRetries); /*Open retry function after ATR proceduce, 3 times retry*/
        apBIT_SET(pBase->RegRetry,PL131_REGRETRY_TX,pState->sSetupParams.TxRetries);
        /*Changed back to direct convention mode for SIM card compatibility, not open retry function in ATR proceduce. End*/
    
        return BSP_OK;
    }

    if (T1_PROTOCOL_MODE == enSIMProtocolMode)
    {


        pState->sATRParams.HasChecksum = TRUE;
        pState->eProtocol = apPL131_PROTOCOL_T1_BLOCK;
        /*�����ַ�����ʱ��*/
        pBase->RegChGuard = (pState->sATRParams.ChGuard == 255) ? 0 : (pState->sATRParams.ChGuard + 1); /*�����ַ������Ĵ���*/
        /*���ÿ鱣��ʱ��*/
        pBase->RegBlkGuard = g_t1_times.BlockGuard;
        /*�����ַ���ʱʱ��*/
        pBase->RegChTimeMS = ((g_t1_times.CharacterTime) & 0xFFFF0000) >> 16;
        pBase->RegChTimeLS = ((g_t1_times.CharacterTime) & 0x0000FFFF);
        /*���ÿ鳬ʱʱ��*/
        pBase->RegBlkTimeMS = ((g_t1_times.BlockTime) & 0xFFFF0000) >> 16;
        pBase->RegBlkTimeLS = ((g_t1_times.BlockTime) & 0x0000FFFF);

        apBIT_SET(pBase->RegCtrl0,PL131_REGCTRL0_TXNAK,0);
        apBIT_SET(pBase->RegCtrl0,PL131_REGCTRL0_RXNAK,0);
        apBIT_SET(pBase->RegRetry,PL131_REGRETRY_TX, 0);
        apBIT_SET(pBase->RegRetry,PL131_REGRETRY_RX, 0);
      
        return MDRV_OK;
    }
    return BSP_ERROR;
}

/*****************************************************************************
* �� �� ��  : bsp_sci_blk_rcv
* ��������  : ���ӿ�������T=1ʱUSIM Manager��ȡ����SCI Driver�Ŀ��������ݣ�
*             �������BWT��ʱ�������ݶ�ȡʱ����һ����ʱ��ֵSCI_TIMEOUT
*
* �������  : ��
* �������  : BSP_U8 *pu8Data USIM Managerָ����Buffer��SCI Driver�����ݿ�������Buffer��
              BSP_U32 *pulLength SCI Driver���յ������ݳ��ȡ�

* �� �� ֵ  : OK : 0
              ERROR : -1
              SCI_TIMEOUT : 1
*
* �޸ļ�¼  : 2014��5��22��16:11:48   lixiaofan  creat
*
*****************************************************************************/

int bsp_sci_blk_rcv(unsigned char  *pu8Data,u32 *pulLength)
{
    PL131_T1_PROLOGUE* t1_prologue = NULL;
    u32 data_size = 0;
    u32 data_check_len = 0;
    u8 *data_local = pu8Data;

    if((NULL == pulLength) || (NULL == pu8Data))
    {
        g_sci_BWT_int_flag = 0;
        return BSP_ERR_SCI_INVALIDPARA;
    }
    SCI_RECORD_EVENT(SCI_EVENT_API_REV_BLK, (u32)pu8Data, __LINE__);

    g_u32ReadFlag = SCI_DEF_READ_READY;

    /*����Ƿ����BWT��ʱ�ж�*/
    do
    {
        /*������յ�һ����,˵��������BWT��ʱ*/
        if(sci_count_length() > 0)
        {
            break;
        }
        else
        {
            /* coverity[unchecked_value] */
            (void)osl_sem_downtimeout(&g_stSciHwCfg.sci_sem.g_SCIBWTSem,100);
        }

    }while(0 == g_sci_BWT_int_flag);
    /*���g_BWTIntFlagΪ1���ñ�־���ڿ鳬ʱ�жϴ����б���1��ÿ�η���ʱ����*/
    if(g_sci_BWT_int_flag)/* [false alarm]:fortify */
    {
        g_sci_BWT_int_flag = 0;/* [false alarm]:fortify */
        return SCI_TIMEOUT;
    }

    /*T=1 ����Prologue begin*/
    g_strRecBuf.usPrelen = T1_PROLOGUE_SIZE;

    SCI_RECORD_EVENT(SCI_EVENT_API_DATA_REC_START, (UINT32)T1_PROLOGUE_SIZE, (UINT32)pu8Data);

    /*����Ƿ��չ�3���ֽ�*/
    if(MDRV_ERROR == bsp_sci_data_read_sync(T1_PROLOGUE_SIZE,data_local))/* [false alarm]:fortify */
    {
        
        SCI_RECORD_EVENT(SCI_EVENT_ERROR_REV_BLK_PLOUGE, (UINT32)T1_PROLOGUE_SIZE, __LINE__);/* [false alarm]:fortify */
        return MDRV_ERROR;
    }
    /*��ȡ��block data�εĳ���*/
    t1_prologue = (PL131_T1_PROLOGUE*)g_strRecBuf.ucRecBuf;
    data_size = t1_prologue->LEN;

    data_local += T1_PROLOGUE_SIZE;

    /*T=1 ����data �� Epilogue*/

    data_check_len = (T1_ERR_DETECT_MODE_LRC == g_sci_atr_info.errDetectMode) ? (data_size + 1) : (data_size + 2);


    SCI_RECORD_EVENT(SCI_EVENT_API_DATA_REC_START, (UINT32)data_check_len, (UINT32)pu8Data);
    /*����Ƿ��չ�ulDataChkLen���ֽ�*/
    if(MDRV_ERROR == bsp_sci_data_read_sync(data_check_len,data_local))/* [false alarm]:fortify */
    {
        SCI_RECORD_EVENT(SCI_EVENT_ERROR_REV_BLK_DATA, (UINT32)data_check_len, __LINE__);/* [false alarm]:fortify */
        return MDRV_ERROR;
    }

    *pulLength = data_check_len + T1_PROLOGUE_SIZE;

    return MDRV_OK;

}
/* T=1 add End */

void sci_uninit(u32 card_id,u32 sci_id)
{
#if (FEATURE_ON==FEATURE_MULTI_MODEM)

    int retvalue;
    SCI_CFG_STRU*  p_sci_cfg = NULL ;
    p_sci_cfg = (SCI_CFG_STRU *)((int)&_sci_cfg_data_start + \
                                (int)(sizeof(SCI_CFG_STRU) * card_id));


    sci_print("input card id = %d sci_id = %d\n",card_id,sci_id);
    sci_print_error("sci unint sci id is %d\n",p_sci_cfg->sci_id);

    if(p_sci_cfg->base_addr == 0)
    {
        sci_print("this card has no resourse no need uninit");
        return;
    }
    
    if(p_sci_cfg->sci_id == sci_id)
    {
        sci_print_error("the slot stay the same,no need unint\n");
        return;
    }
    
    if(p_sci_cfg->sci_int_handler!= NULL)
    {
        disable_irq(p_sci_cfg->int_number);
        retvalue = osl_int_disconnect((p_sci_cfg->int_number),p_sci_cfg->sci_int_handler, 0);
        if(retvalue != 0)
        {
            sci_print_error("disconnet int fail\n");
        }
        p_sci_cfg->sci_int_handler = NULL;
    }
    if(p_sci_cfg->hotplug_task_id!= 0)
    {
        retvalue = osl_task_delete(&p_sci_cfg->hotplug_task_id);
        if(retvalue != 0)
        {
            sci_print("p_sci_cfg->hotplug_task_id deal\n");
        }
        p_sci_cfg->hotplug_task_id = 0;
            
    }
    if(p_sci_cfg->sync_task_id!= 0)
    {
        retvalue = osl_task_delete(&p_sci_cfg->sync_task_id);
        if(retvalue != 0)
        {
            sci_print_error("del task fail\n");
        }
        p_sci_cfg->sync_task_id = 0;
        sci_print("p_sci_cfg->sync_task_id deal\n");
    }

    sci_sem_destory(p_sci_cfg);

    sci_print_error("p_sci_cfg->icc_chnl = %d\n",p_sci_cfg->icc_chnl);
    retvalue = bsp_icc_event_unregister(p_sci_cfg->icc_chnl);
    if(retvalue != 0)
    {
        sci_print("bsp_icc_event_unregister fail %d\n\n",retvalue);
    }
        
       /* init sci record */
    if(p_sci_cfg->g_sci_debug_base.sci_debug_base_addr != NULL)
    {
            
        (void)memset(&(p_sci_cfg->g_sci_debug_base),0,sizeof(sci_debug_str));
    }
        
    if(p_sci_cfg->sci_pmu != NULL)
    {
        p_sci_cfg->sci_pmu = NULL;
    }
        
    if (SCI_RX_DMA_MODE == g_sciRxStGblStru.RxModeFlag)
    {
        bsp_edma_channel_free(p_sci_cfg->dma_chan);
    }
    
    
#endif 
}
u32 sci_get_card_id(SCI_SLOT sci_slot)
{
    NV_SCI_CFG_UNION * nv_val = (NV_SCI_CFG_UNION *)&g_SciNVValue;
    u32 card_num = nv_val->cfg.card_num;
    u32 i = 0;
        
    for(i = 0; i < card_num ;i++)
    {
        if(g_sci_cur_cfg[i].sci_id == sci_slot)
        {
            return i;
        }
    }
    return 0xff;
    
}


int sci_cfg_init(SCI_SLOT* sci_slot_old,SCI_SLOT* sci_slot_new)
{
    unsigned int i = 0;
    unsigned int init_func_num;
    /* coverity[assign] */
    int *p_init_start = (int *)&_sci_init_data_start;
    int call_addr;
    SCI_INIT_FUNCP p_func_sci_init;
    int card_type = 0;

    call_addr = *(volatile int *)p_init_start;
    p_func_sci_init = (SCI_INIT_FUNCP)call_addr;
    init_func_num = &_sci_init_data_end - &_sci_init_data_start;

    card_type = ((NV_SCI_CFG_UNION *)&g_SciNVValue)->cfg.card_num; 
    
    if(SCI_SINGLE == card_type)
    {
        init_func_num= 1;
    }
    else if (SCI_SINGLE_MODLEM1 == card_type)
    {
         init_func_num= 1;
         /* coverity[ptr_arith] */
         p_init_start++;
    }
    
    sci_print_error("init_func_num %d  start_add_opp 0x%0x\r\n", init_func_num,(p_init_start-(int*)&_sci_init_data_start));
        
    /*����SCI�ĳ�ʼ��*/
    for (i = 0; i < init_func_num; i++) 
    {
        if(sci_slot_old[i] != sci_slot_new[i])
        {
            sci_print("now init sci id is %d = \n",sci_slot_new[i]);
            p_func_sci_init();
        }
        /* coverity[ptr_arith] */
        p_init_start++;
        /* coverity[ptr_arith] */
        call_addr =  *(volatile int *)p_init_start;
        p_func_sci_init = (SCI_INIT_FUNCP)call_addr;

    }
    return BSP_OK;
}

void sci_swtich_slot_cfg(u32 card_id ,u32 sci_id)
{
    u32 src_card_id = 0;
    SCI_CFG_STRU*  dst_sci_cfg = NULL ; 
    SCI_CFG_STRU* src_sci_cfg = NULL;
    enum ICC_RECV_FUNC_ID ac_channel[2] = {IFC_RECV_FUNC_SIM0,IFC_RECV_FUNC_SIM1};
    
    dst_sci_cfg = (SCI_CFG_STRU *)((int)&_sci_cfg_data_start + \
                                (int)(sizeof(SCI_CFG_STRU) * card_id));

    sci_print_error("card_id = %d,sci_id = %d\n ",card_id ,sci_id);
    if(dst_sci_cfg->sci_id == sci_id)
    {
        sci_print("sci id is %d no need switch cfg\n",sci_id);
        return;
    }
    
    src_card_id = sci_get_card_id(sci_id);
    if(src_card_id != 0xff)
    {
        src_sci_cfg = &(g_sci_cur_cfg[src_card_id]);
    }
    else
    {
        sci_print("get error card id\n");
        return;
    }
    
    sci_print("dstcfg sci id = %d,srccfg sci id = %d\n",dst_sci_cfg->sci_id,src_sci_cfg->sci_id);
    memcpy_s(dst_sci_cfg,sizeof(SCI_CFG_STRU),src_sci_cfg,sizeof(SCI_CFG_STRU));
    dst_sci_cfg->slot_switch_flag = SCI_SLOT_SWITCH_NONE;
    dst_sci_cfg->sci_pmu = NULL;
    dst_sci_cfg->sync_task_id = 0;
    dst_sci_cfg->sci_int_handler = NULL;    
    dst_sci_cfg->hotplug_task_id = 0;
    dst_sci_cfg->card_id = card_id;
    if(sci_id < SCI_ID_2)
    {
        /*lint -save -e661*/
        dst_sci_cfg->icc_chnl     = ((ICC_CHN_IFC<< 16) | ac_channel[sci_id]);
        /*lint -restore +e661*/

    }
    
}

void sci_update_cfg_nv()
{
    NV_SCI_CFG_UNION * nv_val = (NV_SCI_CFG_UNION *)&g_SciNVValue;
    SCI_CFG_STRU * p_sci_cfg[3] = {NULL,NULL,NULL};
    u32 card_num = nv_val->cfg.card_num;
    u32 i = 0;
    
    for(i = 0; i < card_num; i++)
    {
        p_sci_cfg[i] = (SCI_CFG_STRU *)((int)&_sci_cfg_data_start + \
                                (int)(sizeof(SCI_CFG_STRU) * i));        
    }
    /*�������������۶�Ӧ��sci id��ͬʱ����nv*/
    nv_val->cfg.sci0 = p_sci_cfg[0]->sci_id;
    nv_val->cfg.sci1 = p_sci_cfg[1]->sci_id;    
    nv_val->cfg.sci2 = p_sci_cfg[2]->sci_id;
}
s32 bsp_sci_slot_switch(SCI_SLOT sci_slot0,SCI_SLOT sci_slot1,SCI_SLOT sci_slot2)
{
#if (FEATURE_ON==FEATURE_MULTI_MODEM)
    u32 nv_back = g_SciNVValue;
    NV_SCI_CFG_UNION * nv_val = (NV_SCI_CFG_UNION *)&g_SciNVValue;
    u32 i = 0;
    u32 card_num = nv_val->cfg.card_num;
    SCI_SLOT sci_slot_new[3] = {sci_slot0,sci_slot1,sci_slot2};
    SCI_SLOT sci_slot_old[3] = {SCI_ID_BUTT,SCI_ID_BUTT,SCI_ID_BUTT};
    SCI_CFG_STRU * p_sci_cfg[3] = {NULL,NULL,NULL};

    
    sci_print_error("enter sci slot switch\n");  
    
    SCI_RECORD_EVENT(SCI_EVENT_API_SLOT_SWITCH, (u32)sci_slot0, (__LINE__));

    if(sci_slot0>= SCI_ID_BUTT || sci_slot1 >= SCI_ID_BUTT || sci_slot2 >= SCI_ID_BUTT)
    {
        sci_print("slot id too large\n");
        return MDRV_ERROR;
    }
    if( sci_slot0 == sci_slot1 || sci_slot2 == sci_slot1 || sci_slot0 == sci_slot2)
    {
        sci_print("the slot id is repeat\n");
        return MDRV_ERROR;
    }
    sci_print("sci cfg before slot change:\n");
    for(i = 0; i < card_num;i++)
    {
        p_sci_cfg[i] = (SCI_CFG_STRU *)((int)&_sci_cfg_data_start + \
                                (int)(sizeof(SCI_CFG_STRU) * i));
        
        sci_print_cfg(p_sci_cfg[i]);
    }
    
    if((sci_slot0 == p_sci_cfg[0]->sci_id) && (sci_slot1 == p_sci_cfg[1]->sci_id) && (sci_slot2 == p_sci_cfg[2]->sci_id))
    {
        sci_print("the slot id stay same,no need change\n");
        return MDRV_OK;
    }

    /*�������������ý���ȥ�����*/
    for(i = 0; i < card_num;i++)
    {   
        sci_uninit(i, sci_slot_new[i]);
    }
   
    /*���ݵ�ǰ���������۵�����*/
    for(i = 0; i < card_num;i++)
    {        
        memcpy_s(&g_sci_cur_cfg[i],sizeof(SCI_CFG_STRU),p_sci_cfg[i],sizeof(SCI_CFG_STRU));  
        sci_slot_old[i] = g_sci_cur_cfg[i].sci_id;
    }

    /*����ǰ���������ÿ�������Ӧ�Ŀ���*/
    for(i = 0; i < card_num;i++)
    {
        sci_swtich_slot_cfg(i,sci_slot_new[i]);
    }

    /*���������õ�NVֵ*/
    sci_update_cfg_nv();
    
    if(BSP_OK != bsp_nvm_write(NV_ID_DRV_SCI_DSDA_SELECT, (u8*)&g_SciNVValue, NV_SCI_LEN)) 
    {   
        
        sci_print("write nv fail,and use before nv cfg\n");
        g_SciNVValue = nv_back;
        /*�������NVʧ�ܽ�ԭ�����ݵĿ������ûָ�*/
        for(i = 0; i < card_num;i++)
        {
            memcpy_s(p_sci_cfg[i],sizeof(SCI_CFG_STRU),&g_sci_cur_cfg[i],sizeof(SCI_CFG_STRU));          
        }
        return MDRV_ERROR;
    }
    
    sci_print("current nv val is 0x%x\n",g_SciNVValue);

    /*�����л���־*/
    for(i = 0; i < card_num;i++)
    {   
        /*ֻ�Կ��۱仯������*/
        if(g_sci_cur_cfg[i].sci_id != p_sci_cfg[i]->sci_id)
        {
            p_sci_cfg[i]->slot_switch_flag = SCI_SLOT_SWITCH_CHANGE;
        }
        else
        {
            sci_print("the slot has no changed,no need set flag  \n");
        }
    }

    sci_print("sci cfg after slot change:\n");

    for(i = 0; i < card_num;i++)
    {         
        sci_print_cfg(p_sci_cfg[i]);
    }
   

    /*���¸����ſ����������Դ*/
    sci_cfg_init(sci_slot_old,sci_slot_new);    
    sci_print("THE SLOT HAS BEEN CHANGED\n");

    return MDRV_OK;
 #else
    sci_print_error("not support DSDA");
    return MDRV_ERROR;
 #endif
 
}
s32 bsp_sci_get_slot_state(SCI_SLOT* sci_slot0,SCI_SLOT* sci_slot1,SCI_SLOT* sci_slot2)
{
#if (FEATURE_ON==FEATURE_MULTI_MODEM)

    NV_SCI_CFG_UNION * nv_val = (NV_SCI_CFG_UNION *)&g_SciNVValue;
    u32 card_num = nv_val->cfg.card_num;
    u32 i = 0;
    SCI_SLOT* sci_slot[3] = {sci_slot0,sci_slot1,sci_slot2};
    SCI_CFG_STRU* p_sci_cfg[3]  = {NULL,NULL,NULL};
    for(i = 0; i < card_num;i++)
    {
        p_sci_cfg[i] = (SCI_CFG_STRU *)((int)&_sci_cfg_data_start + \
                                (int)(sizeof(SCI_CFG_STRU) * i));
    }

    for(i = 0; i < card_num;i++)
    {
        *(sci_slot[i]) = p_sci_cfg[i]->sci_id;
    }
    return 0;
#else
    sci_print_error("not support DSDA\n");  
    return MDRV_ERROR;
#endif
}

/*lint -restore */


