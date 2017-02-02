
/*lint -save -e537 -e656 -e801*/
#include <string.h>
#include <stdlib.h>
#include <securec.h>
#include "product_config.h"
/*osl*/
#include <osl_irq.h>
#include <osl_malloc.h>
#include <osl_spinlock.h>
#include <osl_thread.h>
#include <of.h>

#include <drv_nv_id.h>
#include <drv_nv_def.h>

#include "bsp_memmap.h"
#include "bsp_dpm.h"
#include <bsp_hardtimer.h>
#include <bsp_version.h>
#include <bsp_memrepair.h>
#include "bsp_ipc.h"
#include <bsp_nvim.h>
#include <bsp_hw_spinlock.h>
#include <bsp_dump.h>
#include <bsp_pm_om.h>
#include <bsp_reset.h>
#include "bsp_bbp.h"

#include "soc_memmap.h"
#include "hi_bbp.h"
#include "hi_bbp_dma.h"
#include "hi_bbp_ctu.h"

#include "hi_bbp_reg.h"
#include "bbp_balong.h"

struct bbp_info g_bbpinfo;

/*OM*/
static inline void bbp_stamp_set(u32* stamp_addr)
{
#if 0
    u32 stamp_time;

    stamp_time = bsp_get_slice_value();
    *stamp_addr = stamp_time;
#endif
    print_stamp((u32)stamp_addr);
}

static inline void bbp_om_logact(u32 log_id, u32 pwc_id, u32 module_id, u32 modem_id, u32 mode_id)
{
    struct bbp_pwc_actlog *pwc_log = &g_bbpinfo.dbg.pwc_log;

    if(g_bbpinfo.dbg.pwc_debug)
    {
        pwc_log->act_module = module_id;
        pwc_log->act_modem = modem_id;
        pwc_log->act_mode = mode_id;
        pwc_log->pwc_id = pwc_id;
        pwc_log->ops_id = log_id;
        pwc_log->task_id = (unsigned int)osl_task_self();
        switch(log_id){
        case BBP_LOG_POWERON:
            pwc_id = (pwc_id - BBP_VOTE_PWR_MIN);
            g_bbpinfo.om->pwr[pwc_id].enable_module = module_id;
            g_bbpinfo.om->pwr[pwc_id].enable_modem = modem_id;
            g_bbpinfo.om->pwr[pwc_id].enable_mode = mode_id;
            pwc_log->vote_lock = g_bbpinfo.om->pwr[pwc_id].lock;
            break;
        case BBP_LOG_POWEROFF:
            pwc_id = (pwc_id - BBP_VOTE_PWR_MIN);
            g_bbpinfo.om->pwr[pwc_id].disable_module = module_id;
            g_bbpinfo.om->pwr[pwc_id].disable_modem = modem_id;
            g_bbpinfo.om->pwr[pwc_id].disable_mode = mode_id;
            pwc_log->vote_lock = g_bbpinfo.om->pwr[pwc_id].lock;
            break;
        case BBP_LOG_CLKON:
            pwc_id = (pwc_id - BBP_VOTE_CLK_MIN);
            g_bbpinfo.om->clk[pwc_id].enable_module = module_id;
            g_bbpinfo.om->clk[pwc_id].enable_modem = modem_id;
            g_bbpinfo.om->clk[pwc_id].enable_mode = mode_id;
            pwc_log->vote_lock = g_bbpinfo.om->clk[pwc_id].lock;
            break;
        case BBP_LOG_CLKOFF:
            pwc_id = (pwc_id - BBP_VOTE_CLK_MIN);
            g_bbpinfo.om->clk[pwc_id].disable_module = module_id;
            g_bbpinfo.om->clk[pwc_id].disable_modem = modem_id;
            g_bbpinfo.om->clk[pwc_id].disable_mode = mode_id;
            pwc_log->vote_lock = g_bbpinfo.om->clk[pwc_id].lock;
            break;
        case BBP_LOG_PLLON:
            g_bbpinfo.om->pll.enable_module = module_id;
            g_bbpinfo.om->pll.enable_modem = modem_id;
            g_bbpinfo.om->pll.enable_mode = mode_id;
            pwc_log->vote_lock = g_bbpinfo.om->pll.lock;
            break;
        case BBP_LOG_PLLOFF:
            g_bbpinfo.om->pll.disable_module = module_id;
            g_bbpinfo.om->pll.disable_modem = modem_id;
            g_bbpinfo.om->pll.disable_mode = mode_id;
            pwc_log->vote_lock = g_bbpinfo.om->pll.lock;
            break;
        default:
            bbp_print_error("note support this log!");
            break;
        }
        (void)bsp_pm_log_type(PM_OM_BBP, BBP_LOG_ACTUAL, sizeof(struct bbp_pwc_actlog), pwc_log);
    }
}
static inline void bbp_om_loginfo(u32 log_id, u32 module_id, u32 modem_id, u32 mode_id)
{
    struct bbp_pwc_infolog pwc_log;

    if(g_bbpinfo.dbg.pwc_debug)
    {
        pwc_log.act_module = module_id;
        pwc_log.act_modem = modem_id;
        pwc_log.act_mode = mode_id;
        pwc_log.ops_id = log_id;
        pwc_log.task_id = (unsigned int)osl_task_self();
    }
    (void)bsp_pm_log_type(PM_OM_BBP, BBP_LOG_INFO, sizeof(struct bbp_pwc_infolog), &pwc_log);
}
/*ģ���Լ�����*/
/*****************************************************************************
* ����  : bbp_int_ltetf_regcb
* ����  : ��PS���ã����������ע��1ms��ʱ�жϵĻص�
* ����  : pfunc
* ���  : void
* ����  : void
*****************************************************************************/
void bbp_int_ltetf_regcb(bbpintfunc pfunc)
{
    g_bbpinfo.bbpint[BBP_INT_LTETF].func= pfunc;
}

/*****************************************************************************
* �� ��: bbp_int_ltetf_enable
* �� ��: ��PS���ã�������lte 1ms ��ʱ��֡�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
int bbp_int_ltetf_enable(void)
{
    unsigned long bbp_flag = 0;;
    u32 lbbp_switch = 0;
    int iret = BSP_OK;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����0xffff*/
    /*ques2-return error*/
    lbbp_switch = bbp_get_ltemtcmos_status();
    if(lbbp_switch)
    {
        bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_EN_IN]);
        hi_bbp_int_ltetf_clear();
        bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_EN_CLS]);
        hi_bbp_int_ltetf_unmask();
        bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_EN_UNMASK]);
        iret = enable_irq(g_bbpinfo.bbpint[BBP_INT_LTETF].irq);
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return iret;
}

/*****************************************************************************
* �� ��: bbp_int_ltetf_disable
* �� ��: ��PS���ã������ر�lte 1ms ��ʱ��֡�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
void bbp_int_ltetf_disable(void)
{
    unsigned long bbp_flag = 0;;
    u32 lbbp_switch = 0;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����0xffff*/
    lbbp_switch = bbp_get_ltemtcmos_status();
    if(lbbp_switch)
    {
        bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_DIS_IN]);
        hi_bbp_int_ltetf_mask();
        bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_DIS_MASK]);
    }

    (void)disable_irq(g_bbpinfo.bbpint[BBP_INT_LTETF].irq );

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return ;
}
/*****************************************************************************
* �� ��: bbp_int_ltetf_clear
* �� ��: ��PS���ã��������1ms��ʱ�ж�
* ���� : void
* ��� : void
* �� ��: void
*****************************************************************************/
void bbp_int_ltetf_clear(void)
{
    unsigned long bbp_flag = 0;;
    u32 lbbp_switch = 0;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣����bbpû�е���ʱ��ſɷ���*/
    lbbp_switch = bbp_get_ltemtcmos_status();

    if(lbbp_switch)
    {
        bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_CLEAR_IN]);
        hi_bbp_int_ltetf_clear();
        bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_CLEAR_CLS]);
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
/*****************************************************************************
* ����  : bbp_int_ltetf_handle
* ����  : 1ms�жϴ�����
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
static void bbp_int_ltetf_handle(void)
{
    bbp_int_ltetf_clear();

    g_bbpinfo.bbpint[BBP_INT_LTETF].cnt++;

    if (g_bbpinfo.bbpint[BBP_INT_LTETF].func)
    {
        (g_bbpinfo.bbpint[BBP_INT_LTETF].func)();
    }
    bbp_stamp_set(&g_bbpinfo.om->stamp_ltetf[BBP_LTEINT_HANDLE_FUNC]);
}

/*****************************************************************************
* ����  : bbp_int_tdstf_regcb
* ����  : regist callback
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void bbp_int_tdstf_regcb(bbpintfunc pfunc)
{
    if(NULL != pfunc)
    {
        g_bbpinfo.bbpint[BBP_INT_TDSTF].func = pfunc;
    }
    else
    {
        bbp_print_error("Para pFunc is NULL!\n");
    }
}

/*****************************************************************************
* ����  : bbp_int_tdstf_enable
* ����  : enable tdstf
* ����  : void
* ���  : viod
* ����  : u32
*****************************************************************************/
int bbp_int_tdstf_enable(void)
{
    u32 tbbp_switch = 0;
    unsigned long bbp_flag = 0;
    int iret = BSP_OK;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����-1*/
    tbbp_switch = bbp_get_twmtcmos_status();
    if(tbbp_switch)
    {
        bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_EN_IN]);
        hi_bbp_int_tdstf_clear();
        bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_EN_CLS]);
        hi_bbp_int_tdstf_unmask();
        bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_EN_UNMASK]);

        iret = enable_irq(g_bbpinfo.bbpint[BBP_INT_TDSTF].irq);
    }
    else
    {
        iret = BSP_ERROR;
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return iret;
}

/*****************************************************************************
* ����  : bbp_int_tdstf_disable
* ����  : disable tdstf
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void bbp_int_tdstf_disable(void)
{
    u32 tbbp_switch = 0;
    unsigned long bbp_flag = 0;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����*/
    tbbp_switch = bbp_get_twmtcmos_status();
    if(tbbp_switch)
    {
        bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_DIS_IN]);
        hi_bbp_int_tdstf_mask();
        bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_DIS_MASK]);
    }
    (void)disable_irq(g_bbpinfo.bbpint[BBP_INT_TDSTF].irq);

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return;
}

/*****************************************************************************
* ����  : bsp_bbp_tdstf_clear
* ����  : clear tdstf int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
static void bbp_int_tdstf_clear(void)
{
    u32 tbbp_switch = 0;
    unsigned long bbp_flag = 0;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����0xffff*/
    tbbp_switch = bbp_get_twmtcmos_status();
    if(tbbp_switch)
    {
        bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_CLEAR_IN]);
        hi_bbp_int_tdstf_clear();
        bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_CLEAR_CLS]);
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return;
}

/*****************************************************************************
* ����  : bbp_int_tdstf_handle
* ����  : tdstf int handler
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
static void bbp_int_tdstf_handle(void)
{
    bbp_int_tdstf_clear();  //clear int

    (g_bbpinfo.bbpint[BBP_INT_TDSTF].cnt)++;

    if(g_bbpinfo.bbpint[BBP_INT_TDSTF].func != NULL)
    {
        (g_bbpinfo.bbpint[BBP_INT_TDSTF].func)();
    }
    bbp_stamp_set(&g_bbpinfo.om->stamp_tdstf[BBP_TDSINT_HANDLE_FUNC]);
}

/*****************************************************************************
* ����  : bbp_int_wakeup_enable
* ����  : enable bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void bbp_int_wakeup_enable(PWC_COMM_MODE_E mode)
{
    /*wake up �ж�ʹ��*/
    switch(mode){
    case PWC_COMM_MODE_LTE:
        hi_bbp_int_ltewp_clear();
        hi_bbp_int_ltewp_unmask();
        break;
    case PWC_COMM_MODE_TDS:
        hi_bbp_int_tdswp_clear();
        hi_bbp_int_tdswp_unmask();
        break;
    default:
        ;
    }

    return ;
}
/*****************************************************************************
* ����  : bbp_int_wakeup_disable
* ����  : disable bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
*****************************************************************************/
void bbp_int_wakeup_disable(PWC_COMM_MODE_E mode)
{
    /*wake up �ж�ȥʹ��*/
    switch(mode){
    case PWC_COMM_MODE_LTE:
        hi_bbp_int_ltewp_mask();
        break;
    case PWC_COMM_MODE_TDS:
        hi_bbp_int_tdswp_mask();
        break;
    default:
        ;
    }

    return ;
}

/*****************************************************************************
* ����  : bbp_int_wakeup_clear
* ����  : clear bbp wakeup int
* ����  : void
* ���  : void
* ����  : void
* ˵��  : ʱ��Ƶ�ʲ�ͬ�������ж������ɺ���ܽ����²�����
*****************************************************************************/
void bbp_int_wakeup_clear(PWC_COMM_MODE_E mode)
{
    /*���wake up �ж�*/
    switch(mode){
    case PWC_COMM_MODE_LTE:
        hi_bbp_int_wakeup_lte_clear();
        break;
    case PWC_COMM_MODE_TDS:
        hi_bbp_int_wakeup_tds_clear();
        break;
    default:
        ;
    }

    return ;
}
/*****************************************************************************
* �� �� : bbp_int_timer_init
* �� �� : �ҽ�BBP��֡�ж�(T ��L)
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bbp_int_timer_init(PWC_COMM_MODE_E mode)
{
    int iret = BBP_OK;

    switch(mode){
    case PWC_COMM_MODE_LTE:
        /*mask ltebbp 1ms frame interrupt*/
        hi_bbp_int_ltetf_mask();
        iret = osl_int_connect(g_bbpinfo.bbpint[BBP_INT_LTETF].irq, (irq_handler_t)bbp_int_ltetf_handle, 0);
        //enable_irq(g_bbpinfo.bbpint[BBP_INT_LTETF].irq);
        break;
    case PWC_COMM_MODE_TDS:
        hi_bbp_int_tdstf_mask();
        iret = osl_int_connect(g_bbpinfo.bbpint[BBP_INT_TDSTF].irq, (irq_handler_t)bbp_int_tdstf_handle, 0);
        //enable_irq(g_bbpinfo.bbpint[BBP_INT_TDSTF].irq);
        break;
    default:
        bbp_print_error("input param error:%x,not support this mode!\n",mode);
    }

    return iret;
}

/*****************************************************************************
* ����  : bbp_get_sys_frame
* ����  : get system frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u16 bbp_get_lte_sysframe(void)
{
    unsigned long bbp_flag = 0;
    u32 lbbp_switch = 0;
    u16 framenum = BBP_POWER_DOWN_BACK;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����0xffff*/
    lbbp_switch = bbp_get_ltemtcmos_status();
    if(lbbp_switch)
    {
        hi_bbp_ltestu_tim_lock();
        framenum = (u16)hi_bbp_get_lte_fn();
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return framenum;
}

/*****************************************************************************
* ����  : bbp_get_sys_subframe
* ����  : get system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u16 bbp_get_lte_subframe(void)
{
    unsigned long bbp_flag = 0;
    u32 lbbp_switch = 0;
    u16 framenum = BBP_POWER_DOWN_BACK;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����0xffff*/
    lbbp_switch = bbp_get_ltemtcmos_status();
    if(lbbp_switch)
    {
        hi_bbp_ltestu_tim_lock();
        framenum = (u16)hi_bbp_get_lte_sfn();
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return framenum;
}
/*****************************************************************************
* ����  : bbp_get_tds_subframe
* ����  : get tds system sub frame num
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u16 bbp_get_tds_subframe(void)
{
    unsigned long bbp_flag = 0;
    u32 tbbp_switch = 0;
    u16 framenum = BBP_POWER_DOWN_BACK;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����0xffff*/
    tbbp_switch = bbp_get_twmtcmos_status();
    if(tbbp_switch)
    {
        /*TODO:��liqingboȷ�ϣ��Ƿ���Ҫ������*/
        framenum = (u16)hi_bbp_get_tds_sfn();
        framenum &= BBP_TDS_STU_SFN_MASK;
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return framenum;
}

/*****************************************************************************
* ����  : bbp_set_tds_subframe_offset
* ����  : set tds system sub frame offset
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u16 bbp_set_tds_subframe_offset(u16 sf_offset)
{
    u16 ret = BBP_POWER_DOWN_BACK;
    unsigned long bbp_flag = 0;
    u32 tbbp_switch = 0;

    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*���籣�������BBP���磬����0xffff*/
    tbbp_switch = bbp_get_twmtcmos_status();
    if(tbbp_switch){
        /*������֡ƫ��,��ʱ�л�ʹ��*/
        hi_bbp_set_tds_sfn_oft(sf_offset);
        ret = BBP_OK;
    }

    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return ret;

}



/*****************************************************************************
* ����  : bbp_get_tds_sleeptime
* ����  : Get tds sleep time
* ����  : void
* ���  : void
* ����  : u32
*****************************************************************************/
u32 bbp_get_tds_sleeptime(void)
{
    u32 u32RegVaule = 0;

    u32RegVaule = hi_bbp_get_tds_slp_time();

    return u32RegVaule;
}

/*****************************************************************************
* ����  : bbp_get_tds_clk_status
* ����  : get_tdsclk_switch
* ����  : void
* ���  : 0��ʾ�л���ϵͳʱ�ӣ�1��ʾ�л���32kʱ��
* ����  : void
*****************************************************************************/
unsigned int bbp_get_tds_clkswitch(void)
{
    u32 tds_clk_switch;

    tds_clk_switch = hi_bbp_get_tds_clk_switch_state();/*0xfff13400+0x200*/

    return tds_clk_switch;
}

/*****************************************************************************
* �� �� : bbp_get_wakeup_time
* �� �� : ������ѯ˯�߳�ʱʱ��
* �� �� : PWC_COMM_MODE_E:����ģ��ֻ����TDS/LTE
* �� �� : void
* �� �� : bbp˯��ʣ��ʱ�䣬��λΪ32.768KHzʱ�Ӽ���
*****************************************************************************/
u32 bbp_get_wakeup_time(PWC_COMM_MODE_E mode)
{
    u32 ret = 0xffffffff;

    switch(mode){
    case PWC_COMM_MODE_LTE:
        ret = hi_bbp_get_lte_wakeup_time();
        break;
    case PWC_COMM_MODE_TDS:
        ret = hi_bbp_get_tds_wakeup_time();
        break;
    default:
        bbp_print_error("not support this mode!");
        ;
    }

    return ret;
}
u32 bbp_get_gubbp_wakeup_status(void)
{
    /*yiliu*/
    return 0;
}

/*****************************************************************************
Function:   bbp_get_meansflag
Description:
Input:
Output:     the means flag value;
Return:
Others:
*****************************************************************************/
int bbp_get_meansflag(PWC_COMM_MODE_E enModeId)
{
    //int means_value=0xffffffff;
    int means_value=-1;

    switch(enModeId){
    case PWC_COMM_MODE_WCDMA:
        means_value = (int)hi_bbp_get_wcdma_meanflag();
        break;
    case PWC_COMM_MODE_GSM:
        means_value = (int)hi_bbp_get_gsm_meanflag();
        break;
    case PWC_COMM_MODE_LTE:
        means_value = (int)hi_bbp_get_lte_meanflag();
        break;
    case PWC_COMM_MODE_TDS:
        means_value = (int)hi_bbp_get_tds_meanflag();
        break;
    default:
        return -1;
    }

    return means_value;
}
/*****************************************************************************
* �� �� : bsp_bbp_lps_get_ta
* �� �� : ��lps����,�鿴������֡ͷ���ϵͳ��֡ͷ����ǰ��
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bbp_lps_get_ta(void)
{
    return (int)hi_bbp_get_ta_value();
}


int bbp_get_timing_val(BBP_TIMING_STRU *pstTiming)
{
    /* need to implement */
    return hi_bbp_get_timing_val(pstTiming);
}
/*****************************************************************************
* �� �� : bbp_gbbp_select_clksrc
* �� �� : ��oam����,����gbbp��ͨ������
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return hi_bbp_gbbp_select_clksrc(enModemId,enChannel);
}
#if 1
/*���ϲ�ģ��Ĳ����ж�*/
static int bbp_param_check(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    /* coverity[unsigned_compare] */
    if((enModeId < BBP_PWC_MODE_MIN) ||(enModeId > BBP_PWC_MODE_MAX))
    {
        bbp_print_error("enModeId param false, not support %d. \n",enModeId);
        return BBP_ERR_PARAM_INVALID;
    }
    /* coverity[unsigned_compare] */
    if((enModuleId < BBP_PWC_MODULE_MIN) ||(enModuleId > BBP_PWC_MODULE_MAX))
    {
        bbp_print_error("enModuleId param false, not support %d. \n",enModuleId);
        return BBP_ERR_PARAM_INVALID;
    }
    /* coverity[unsigned_compare] */
    if((enModemId < BBP_PWC_MODEM_MIN)||( enModemId > BBP_PWC_MODEM_MAX))
    {
        bbp_print_error("enModemId param false, not support %d. \n",enModemId);
        return BBP_ERR_PARAM_INVALID;
    }
    return BBP_OK;
}
#define BBP_PARA_CHECK() \
if (BBP_ERR_PARAM_INVALID == bbp_param_check(enModeId, enModuleId, enModemId))\
{\
    bbp_print_error("check your input!\n");\
    return BBP_ERR_PARAM_INVALID;\
}
#define BBP_PARA_TRANS() \
    mode_id = (u32)(enModeId - BBP_PWC_MODE_MIN); \
    modem_id = (u32)(enModemId - BBP_PWC_MODEM_MIN); \
    module_id = (u32)(enModuleId - BBP_PWC_MODULE_MIN); \

static BBP_VOTE_LOCK_E bbp_vote_is_locked(u32 vote_id, u32 dev_id)
{
    u64 vote_lock = 0;

    switch(vote_id){
    case BBP_VOTE_PWR:
        vote_lock = g_bbpinfo.om->pwr[dev_id].lock;
        break;
    case BBP_VOTE_CLK:
        vote_lock = g_bbpinfo.om->clk[dev_id].lock;
        break;
    case BBP_VOTE_PLL:
        vote_lock = g_bbpinfo.om->pll.lock;
        break;
    default:
        bbp_print_error("note support this vote!");
        break;
    }

    if(vote_lock)
        return BBP_VOTE_LOCK;
    else
        return BBP_VOTE_UNLOCK;
}

static void bbp_vote_lock(u32 vote_id, u32 dev_id, u32 module_id, u32 modem_id, u32 mode_id)
{
    u32 vote_bit;

    switch(vote_id){
    case BBP_VOTE_PWR:
        g_bbpinfo.om->pwr[dev_id].enable_vote[module_id][modem_id][mode_id] ++;
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        g_bbpinfo.om->pwr[dev_id].lock |= ((u64)1 << vote_bit);
        break;
    case BBP_VOTE_CLK:
        g_bbpinfo.om->clk[dev_id].enable_vote[module_id][modem_id][mode_id] ++;
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        g_bbpinfo.om->clk[dev_id].lock |= ((u64)1 << vote_bit);
        break;
    case BBP_VOTE_PLL:
        g_bbpinfo.om->pll.enable_vote[module_id][modem_id][mode_id] ++;
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        g_bbpinfo.om->pll.lock |= ((u64)1 << vote_bit);
        break;
    default:
        bbp_print_error("note support this vote!");
        break;
    }
}
static void bbp_vote_unlock(u32 vote_id, u32 dev_id,u32 module_id, u32 modem_id, u32 mode_id)
{
    u32 vote_bit;

    switch(vote_id){
    case BBP_VOTE_PWR:
        g_bbpinfo.om->pwr[dev_id].disable_vote[module_id][modem_id][mode_id] ++;
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        g_bbpinfo.om->pwr[dev_id].lock &= ~((u64)1 << vote_bit);
        break;
    case BBP_VOTE_CLK:
        g_bbpinfo.om->clk[dev_id].disable_vote[module_id][modem_id][mode_id] ++;
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        g_bbpinfo.om->clk[dev_id].lock &= ~((u64)1 << vote_bit);
        break;
    case BBP_VOTE_PLL:
        g_bbpinfo.om->pll.disable_vote[module_id][modem_id][mode_id] ++;
        vote_bit = BBP_MODE_NUM*BBP_MODEM_NUM*module_id + BBP_MODE_NUM*modem_id + mode_id;
        g_bbpinfo.om->pll.lock &= ~((u64)1 << vote_bit);
        break;
    default:
        bbp_print_error("note support this vote!");
        break;
    }
}
int bbp_pwrctrl_status(u32 enPwrId)
{
    u32 status=0;

    status = bbp_pwrctrl_is_enabled(enPwrId);

    if(status)
    {
        return PWC_ON;
    }
    else
    {
        return PWC_OFF;
    }
}
int bbp_pwrctrl_poweron(u32 enPwrId)
{
    int ret = BBP_OK;

    /*���Ѵ򿪣������*/
    if(bbp_pwrctrl_status(enPwrId) == PWC_ON)
    {
        bbp_print_info("bbp mode %d has opened!\n",enPwrId);
        ret = BBP_OK;
        goto out;
    }

    bbp_pwrctrl_enable(enPwrId);

out:
     return ret;
}
int bbp_pwrctrl_poweroff(u32 enPwrId)
{
    int ret = BBP_OK;

    /*����ǰ�ѹرգ���ֱ�ӷ���*/
    if(bbp_pwrctrl_status(enPwrId) == PWC_OFF)
    {
        bbp_print_info("bbp mode %d has closed!\n",enPwrId);
        ret = BBP_OK;
        goto out;
    }

    bbp_pwrctrl_disable(enPwrId);

out:
    return ret;
}

int bbp_power_up(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    unsigned long bbp_flags = 0;
    int ret = BBP_OK;
    u32 i = 0;
    u32 pwr_id,vote_pwr_id = 0;
    u32 mode_id,modem_id,module_id = 0;

    bbp_om_loginfo(BBP_LOG_POWERON,enModuleId,enModemId,enModeId);

    BBP_PARA_CHECK();
    /*change to inner id*/
    BBP_PARA_TRANS();

    /*�ҵ�Ҫ������pwrid*/
    for (i = 0 ;i < BBP_VOTE_PWR_NUM ;i++ )
    {
        pwr_id = g_bbpinfo.pwr.pwr_list[module_id][modem_id][mode_id].pwc_pwr[i];

        if (BBP_PWC_NULL == pwr_id)
        {
            break;
        }
        else if(BBP_PWC_ALWAYSON != pwr_id)/*�ǳ�����*/
        {
            spin_lock_irqsave(&g_bbpinfo.pwr.pwr_act[pwr_id].spinlock, bbp_flags);
            vote_pwr_id = pwr_id - BBP_VOTE_PWR_MIN;
            bbp_vote_lock(BBP_VOTE_PWR,vote_pwr_id,module_id,modem_id,mode_id);
            ret = bbp_pwrctrl_poweron(pwr_id);
            g_bbpinfo.om->pwr[vote_pwr_id].enable_actual++;
            bbp_stamp_set(&g_bbpinfo.om->stamp_pwron[vote_pwr_id]);
            bbp_om_logact(BBP_LOG_POWERON,pwr_id,enModuleId,enModemId,enModeId);
            spin_unlock_irqrestore(&g_bbpinfo.pwr.pwr_act[pwr_id].spinlock, bbp_flags);
        }
    }

    return ret;
}
int bbp_power_down(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    unsigned long bbp_flags = 0;
    int ret = BBP_OK;
    u32 i = 0;
    u32 pwr_id,vote_pwr_id = 0;
    u32 mode_id,modem_id,module_id = 0;

    bbp_om_loginfo(BBP_LOG_POWEROFF,enModuleId,enModemId,enModeId);

    BBP_PARA_CHECK();
    /*change to inner id*/
    BBP_PARA_TRANS();

    /*�ҵ�Ҫ������pwrid*/
    for (i = 0 ;i < BBP_VOTE_PWR_NUM ;i++ )
    {
        pwr_id = g_bbpinfo.pwr.pwr_list[module_id][modem_id][mode_id].pwc_pwr[i];

        if (BBP_PWC_NULL == pwr_id)
        {
            break;
        }
        else if(BBP_PWC_ALWAYSON != pwr_id)/*�ǳ�����*/
        {
            spin_lock_irqsave(&g_bbpinfo.pwr.pwr_act[pwr_id].spinlock, bbp_flags);
            vote_pwr_id = pwr_id - BBP_VOTE_PWR_MIN;
            bbp_vote_unlock(BBP_VOTE_PWR,vote_pwr_id,module_id,modem_id,mode_id);
            if(bbp_vote_is_locked(BBP_VOTE_PWR,vote_pwr_id) == BBP_VOTE_UNLOCK)
            {
                /*����NV�����������Ƿ�ر�*/
                if (g_bbpinfo.dpm.pwc_nv.drx_bbppwr_pd == 0)
                {
                    g_bbpinfo.om->pwr[vote_pwr_id].disable_actual++;
                    ret = bbp_pwrctrl_poweroff(pwr_id);
                    bbp_stamp_set(&g_bbpinfo.om->stamp_pwroff[vote_pwr_id]);
                }
            }
            bbp_om_logact(BBP_LOG_POWEROFF,pwr_id,enModuleId,enModemId,enModeId);
            spin_unlock_irqrestore(&g_bbpinfo.pwr.pwr_act[pwr_id].spinlock, bbp_flags);
        }
    }

    return ret;
}
int bbp_power_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    int ret = PWRCTRL_COMM_OFF;
    int status = PWC_ON;
    unsigned long bbp_flags = 0;
    u32 i = 0;
    u32 pwr_id = 0;
    u32 mode_id,modem_id,module_id = 0;

    BBP_PARA_CHECK();
    /*change to inner id*/
    BBP_PARA_TRANS();

    if(g_bbpinfo.dpm.pwc_nv.drx_bbppwr_pd == 1)
        return PWRCTRL_COMM_ON;

    for (i = 0 ;i < BBP_VOTE_PWR_NUM ;i++ )
    {
        pwr_id = g_bbpinfo.pwr.pwr_list[module_id][modem_id][mode_id].pwc_pwr[i];

        if (BBP_PWC_NULL == pwr_id)
        {
            if(i == 0)/*û��Ҫ������pwr_id,Ĭ��Ϊ��*/
               status = PWC_OFF;

            break;
        }
        else if(BBP_PWC_ALWAYSON != pwr_id)/*�ǳ�����*/
        {
            spin_lock_irqsave(&g_bbpinfo.pwr.pwr_act[pwr_id].spinlock, bbp_flags);
            status &= bbp_pwrctrl_status(pwr_id);
            spin_unlock_irqrestore(&g_bbpinfo.pwr.pwr_act[pwr_id].spinlock, bbp_flags);
        }
        else/*������*/
        {
            status &= PWC_ON;
        }
    }

    if(status == PWC_ON)
        ret = PWRCTRL_COMM_ON;

    return ret;
}
int bbp_clkctrl_status(u32 enClkId)
{
    u32 status=0;

    status = bbp_clkctrl_is_enabled(enClkId);

    if(status)
    {
        return PWC_ON;
    }
    else
    {
        return PWC_OFF;
    }
}
void bbp_clkctrl_clkenable(u32 enClkId)
{
    /*���Ѵ򿪣������*/
    if(bbp_clkctrl_status(enClkId) == PWC_ON)
    {
        bbp_print_info("bbp clk %d has opened!\n",enClkId);
        return;
    }

    bbp_clkctrl_enable(enClkId);
}
void bbp_clkctrl_clkdisable(u32 enClkId)
{
    /*����ǰ�ѹرգ���ֱ�ӷ���*/
    if(bbp_clkctrl_status(enClkId) == PWC_OFF)
    {
        bbp_print_info("bbp clk %d has closed!\n",enClkId);
        return;
    }

    bbp_clkctrl_disable(enClkId);
}
int bbp_rstctrl_status(u32 enClkId)
{
    u32 status=0;

    status = bbp_rstctrl_is_enabled(enClkId);

    if(!status)
    {
        return PWC_ON;/*�⸴λ���ؿ�*/
    }
    else
    {
        return PWC_OFF;/*��λ���ع�*/
    }
}
void bbp_rstctrl_unrstenable(u32 enClkId)
{
    /*���ѽ⸴λ�������ٽ⸴λ*/
    if(bbp_rstctrl_status(enClkId) == PWC_ON)
    {
        bbp_print_info("bbp clk %d has unrst!\n",enClkId);
        return;
    }

    bbp_rstctrl_disable(enClkId);
}
void bbp_rstctrl_unrstdisable(u32 enClkId)
{
    /*����ǰ�Ѹ�λ����ֱ�ӷ���*/
    if(bbp_rstctrl_status(enClkId) == PWC_OFF)
    {
        bbp_print_info("bbp clk %d has rst!\n",enClkId);
        return;
    }

    bbp_rstctrl_enable(enClkId);
}
int bbp_clk_status(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    unsigned long bbp_flags = 0;
    int ret = PWRCTRL_COMM_OFF;
    int status = PWC_ON;
    u32 i = 0;
    u32 clk_id = 0;
    u32 mode_id,modem_id,module_id = 0;

    BBP_PARA_CHECK();
    /*change to inner id*/
    BBP_PARA_TRANS();

    /*dpm*/
    if(g_bbpinfo.dpm.pwc_nv.drx_bbpclk_pd == 1)
        return PWRCTRL_COMM_ON;

    /*�ҵ�Ҫ������clkid*/
    for (i = 0 ;i < BBP_VOTE_CLK_NUM ;i++ )
    {
        clk_id = g_bbpinfo.clk.clk_list[module_id][modem_id][mode_id].pwc_clk[i];

        if (BBP_PWC_NULL == clk_id)
        {
            if(i == 0)/*û��Ҫ������clk_id��Ĭ��Ϊ��*/
               status = PWC_OFF;

            break;
        }
        else if(BBP_PWC_ALWAYSON != clk_id)/*�ǳ�����*/
        {
            spin_lock_irqsave(&g_bbpinfo.clk.clk_act[clk_id].spinlock, bbp_flags);
            status &= bbp_clkctrl_status(clk_id);
            if(g_bbpinfo.clk.rst_flag)
                status &= bbp_rstctrl_status(clk_id);
            spin_unlock_irqrestore(&g_bbpinfo.clk.clk_act[clk_id].spinlock, bbp_flags);
        }
        else
        {
            status &= PWC_ON;
        }
    }
    if(status == PWC_ON)
        ret = PWRCTRL_COMM_ON;

    return ret;
}
/*****************************************************************************
* �� �� : bbp_clk_enable
* �� �� : ���͹��ĵ��ã�BBP CLK ʹ��
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bbp_clk_enable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    unsigned long bbp_flags = 0;
    int ret = BBP_OK;
    u32 i = 0;
    u32 clk_id,vote_clk_id = 0;
    u32 mode_id,modem_id,module_id = 0;

    bbp_om_loginfo(BBP_LOG_CLKON,enModuleId,enModemId,enModeId);

    BBP_PARA_CHECK();
    /*change to inner id*/
    BBP_PARA_TRANS();

    /*�ҵ�Ҫ������clkid*/
    for (i = 0 ;i < BBP_VOTE_CLK_NUM ;i++ )
    {
        clk_id = g_bbpinfo.clk.clk_list[module_id][modem_id][mode_id].pwc_clk[i];

        if (BBP_PWC_NULL == clk_id)
        {
            break;
        }
        else if(BBP_PWC_ALWAYSON != clk_id)/*�ǳ�����*/
        {
            spin_lock_irqsave(&g_bbpinfo.clk.clk_act[clk_id].spinlock, bbp_flags);
            vote_clk_id = clk_id - BBP_VOTE_CLK_MIN;
            bbp_vote_lock(BBP_VOTE_CLK,vote_clk_id,module_id,modem_id,mode_id);
            g_bbpinfo.om->clk[vote_clk_id].enable_actual++;
            bbp_clkctrl_clkenable(clk_id);
            if(g_bbpinfo.clk.rst_flag)
                bbp_rstctrl_unrstenable(clk_id);
            bbp_stamp_set(&g_bbpinfo.om->stamp_clkon[vote_clk_id]);
            bbp_om_logact(BBP_LOG_CLKON,clk_id,enModuleId,enModemId,enModeId);
            spin_unlock_irqrestore(&g_bbpinfo.clk.clk_act[clk_id].spinlock, bbp_flags);
        }

    }

    return ret;
}
/*****************************************************************************
* �� �� : bbp_clk_disable
* �� �� : ���͹��ĵ��ã�BBP CLK ȥʹ��
* �� �� : void
* �� �� : void
* �� �� : 0Ϊ�ɹ���-1ʧ��
* ˵ �� :
*****************************************************************************/
int bbp_clk_disable(PWC_COMM_MODE_E enModeId, PWC_COMM_MODULE_E enModuleId, PWC_COMM_MODEM_E enModemId)
{
    unsigned long bbp_flags = 0;
    int ret = BBP_OK;
    u32 i = 0;
    u32 clk_id,vote_clk_id = 0;
    u32 mode_id,modem_id,module_id = 0;

    bbp_om_loginfo(BBP_LOG_CLKOFF,enModuleId,enModemId,enModeId);

    BBP_PARA_CHECK();
    /*change to inner id*/
    BBP_PARA_TRANS();

    /*�ҵ�Ҫ������clkid*/
    for (i = 0 ;i < BBP_VOTE_CLK_NUM ;i++ )
    {
        clk_id = g_bbpinfo.clk.clk_list[module_id][modem_id][mode_id].pwc_clk[i];

        if (BBP_PWC_NULL == clk_id)
        {
            break;
        }
        else if(BBP_PWC_ALWAYSON != clk_id)/*�ǳ�����*/
        {
            spin_lock_irqsave(&g_bbpinfo.clk.clk_act[clk_id].spinlock, bbp_flags);
            vote_clk_id = clk_id - BBP_VOTE_CLK_MIN;
            bbp_vote_unlock(BBP_VOTE_CLK,vote_clk_id,module_id,modem_id,mode_id);
            if(bbp_vote_is_locked(BBP_VOTE_CLK,vote_clk_id) == BBP_VOTE_UNLOCK)
            {
                /*����NV�����������Ƿ�ر�*/
                if (g_bbpinfo.dpm.pwc_nv.drx_bbpclk_pd == 0)
                {
                    g_bbpinfo.om->clk[vote_clk_id].disable_actual++;
                    bbp_clkctrl_clkdisable(clk_id);
                    if(g_bbpinfo.clk.rst_flag)
                        bbp_rstctrl_unrstdisable(clk_id);
                    bbp_stamp_set(&g_bbpinfo.om->stamp_clkoff[vote_clk_id]);
                }
            }
            bbp_om_logact(BBP_LOG_CLKOFF,clk_id,enModuleId,enModemId,enModeId);
            spin_unlock_irqrestore(&g_bbpinfo.clk.clk_act[clk_id].spinlock, bbp_flags);
        }

    }

    return ret;
}

#endif

/*****************************************************************************
* �� �� : bbp_dma_tran
* �� �� : ʹ��bbp dma�������ݰ���
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_dma_tran(struct bbp_dma_cfg dma_config)
{
    u32 config_data = 0;
    u32 chan = 0;

    bbp_stamp_set(&g_bbpinfo.om->stamp_dma[BBP_DMATRAN_IN]);
    chan = dma_config.chan;

    hi_bbpdma_clk_enable();

    bbp_stamp_set(&g_bbpinfo.om->stamp_dma[BBP_DMATRAN_CLKEN]);
    /*���ݰ��Ƶ�bbp�ռ��ַ*/
    writel(dma_config.bbp_addr,(u32)g_bbpinfo.part[BBP_DMA].reg_base+HI_BBP_FAST_CH0_BBP_ADDR_OFFSET + 0x10*chan);

    /*���ݰ��Ƶ�soc�ռ��ַ*/
    writel(dma_config.soc_addr,(u32)g_bbpinfo.part[BBP_DMA].reg_base+HI_BBP_FAST_CH0_SOC_ADDR_OFFSET + 0x10*chan);
    bbp_stamp_set(&g_bbpinfo.om->stamp_dma[BBP_DMATRAN_ADDR]);

    /*���ð������ݳ���(�ֽ���/�Ĵ�������-1)��ģʽ��ʹ��*/
    config_data = ((dma_config.size/sizeof(dma_config.size)-1) << BBP_DMA_LEN_BIT_OFFSET) \
                    |(dma_config.type << BBP_DMA_FAST_BIT_OFFSET) \
                    |(1 << BBP_DMA_ALL_DATA_BIT_OFFSET)\
                    |(1 << BBP_DMA_FAST_SOFT_BIT_OFFSET) \
                    |(1 << BBP_DMA_ENABLE_BIT_OFFSET);
    writel(config_data,(u32)&g_bbpinfo.om->stamp_dma[BBP_DMACONFIG]);
    writel(config_data,(u32)g_bbpinfo.part[BBP_DMA].reg_base+HI_BBP_FAST_CH0_CTL_OFFSET+ 0x10*chan);

    bbp_stamp_set(&g_bbpinfo.om->stamp_dma[BBP_DMATRAN_END]);
}
/*****************************************************************************
* �� �� : bbp_dma_finish
* �� �� : �ȴ�bbp dma�������
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
void bbp_dma_finish(struct bbp_dma_cfg dma_config)
{
    u32 status = 0;
    u32 dma_chan = 0;

    bbp_stamp_set(&g_bbpinfo.om->stamp_dma[BBP_DMAFINISH_IN]);
    dma_chan = dma_config.chan;

    do
    {
        status = readl((u32)g_bbpinfo.part[BBP_DMA].reg_base + HI_BBP_FAST_CH0_CFG_OFFSET+ 0x10*dma_chan);
    }while(status & (1 << BBP_DMA_BUSY_BIT_OFFSET));
    bbp_stamp_set(&g_bbpinfo.om->stamp_dma[BBP_DMAFINISH_BUSY]);

    hi_bbpdma_clk_disable();

    bbp_stamp_set(&g_bbpinfo.om->stamp_dma[BBP_DMAFINISH_END]);
}
#ifdef CONFIG_CCORE_PM
/*****************************************************************************
* �� �� : bbp_time_start
* �� �� : bbp ��ʱ��ʼ
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
u32 bbp_time_get(void)
{
    u32 time = 0;

    if(g_bbpinfo.dbg.time_debug)
    {
        time = bsp_get_slice_value_hrt();
    }
    return time;
}
/*****************************************************************************
* �� �� : bbp_time_end
* �� �� : bbp ��ʱ��ʼ
* �� �� : Ŀ���ַ��Դ��ַ������
* �� �� : vo
* �� �� :
* ˵ �� :
*****************************************************************************/
 void bbp_time_show(u32 time_start ,u32 time_end)
{
    if(g_bbpinfo.dbg.time_debug)
    {
        bbp_print_error("start:0x%x,end:0x%x,cost:0x%x!\n",time_start,time_end,(time_end - time_start));
    }
}

/*****************************************************************************
* �� �� : bbp_dpm_prepare
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
static void bbp_save_by_dma(void)
{
    struct bbp_dma_cfg dma_cfg;

    /*use phy addr*/
    dma_cfg.bbp_addr = (u32) g_bbpinfo.part[BBP_CTU].reg_phyaddr;
    dma_cfg.soc_addr=(u32) g_bbpinfo.dpm.ctu_save_addr;
    dma_cfg.size = g_bbpinfo.dpm.ctu_save_size;
    dma_cfg.type = BBP_TO_SOC;/*change to enum*/
    dma_cfg.chan = g_bbpinfo.dpm.dma_chan;

    /*save ctu register data*/
    bbp_dma_tran(dma_cfg);
}
/*****************************************************************************
* �� �� : bbp_dpm_prepare
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
static void bbp_save_by_dma_ok(void)
{
    struct bbp_dma_cfg dma_cfg={0};

    dma_cfg.chan = g_bbpinfo.dpm.dma_chan;

    /*save ctu register data*/
    bbp_dma_finish(dma_cfg);
}
#ifndef HI_BBP_CTU_CPU_RX1_TX1_CKG_BYPASS_OFFSET
#define HI_BBP_CTU_CPU_RX1_TX1_CKG_BYPASS_OFFSET          (0x420)
#endif
/*****************************************************************************
* �� �� : bbp_dpm_prepare
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
static void bbp_resume_by_dma(void)
{
    struct bbp_dma_cfg dma_cfg;

    if(CHIP_K3V5 == bsp_get_version_info()->chip_type)
    {
        /*��ckg_bypass�Ĵ�������ֵ��ֵΪ0*/
        *(u32 *)(g_bbpinfo.dpm.ctu_save_addr+HI_BBP_CTU_CPU_RX1_TX1_CKG_BYPASS_OFFSET) = 0;
    }
    /*use phy addr*/
    dma_cfg.bbp_addr = (u32)g_bbpinfo.part[BBP_CTU].reg_phyaddr;
    dma_cfg.soc_addr= (u32)g_bbpinfo.dpm.ctu_save_addr;
    dma_cfg.size = g_bbpinfo.dpm.ctu_save_size;
    dma_cfg.type = SOC_TO_BBP;
    dma_cfg.chan = g_bbpinfo.dpm.dma_chan;

    /*save ctu register data*/
    bbp_dma_tran(dma_cfg);
}
/*****************************************************************************
* �� �� : bbp_dpm_prepare
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
static void bbp_resume_by_dma_ok(void)
{
    struct bbp_dma_cfg dma_cfg={0};

    dma_cfg.chan = g_bbpinfo.dpm.dma_chan;

    /*save ctu register data*/
    bbp_dma_finish(dma_cfg);
}
#if 0
/*****************************************************************************
* �� �� : bbp_dpm_prepare
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
static void bbp_save_by_memcpy(void)
{
    return;
}
/*****************************************************************************
* �� �� : bbp_resume_by_memcpy
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
static void bbp_resume_by_memcpy(void)
{
    return;
}
#endif
/*****************************************************************************
* �� �� : bbp_dpm_prepare
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bbp_dpm_prepare(struct dpm_device *dev)
{
    u32 time_before = 0;
    u32 time_after = 0;

    bbp_stamp_set(&g_bbpinfo.om->stamp_suspend[BBP_PREPAIR_IN]);

    time_before = bbp_time_get();
    if(g_bbpinfo.dpm.enable_dma)
        bbp_save_by_dma();

    /*��������Ĵ���*/
    if(CHIP_K3V5 == bsp_get_version_info()->chip_type)
    {
        g_bbpinfo.dpm.ckg_bypass_data= *(u32 *)((u32)g_bbpinfo.part[BBP_CTU].reg_base+HI_BBP_CTU_CPU_RX1_TX1_CKG_BYPASS_OFFSET);
    }
    g_bbpinfo.dpm.irm_data = *(u32 *)((u32)g_bbpinfo.part[BBP_CTU].reg_base+BBP_IRM_SAVE_OFFSET);

    time_after = bbp_time_get();
    bbp_time_show(time_before,time_after);

    bbp_stamp_set(&g_bbpinfo.om->stamp_suspend[BBP_PREPAIR_END]);

    return BSP_OK;
}

/*****************************************************************************
* �� �� : bbp_dpm_suspend
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bbp_dpm_suspend(struct dpm_device *dev)
{

    u32 time_before = 0;
    u32 time_after = 0;

    bbp_stamp_set(&g_bbpinfo.om->stamp_suspend[BBP_SUSPEND_IN]);

    time_before = bbp_time_get();
    if(g_bbpinfo.dpm.enable_dma)
        bbp_save_by_dma_ok();
    time_after = bbp_time_get();
    bbp_time_show(time_before,time_after);

    bbp_comm_reset();
    bbp_stamp_set(&g_bbpinfo.om->stamp_resume[BBP_SUSPEND_BBCRST]);

    bbp_stamp_set(&g_bbpinfo.om->stamp_suspend[BBP_SUSPEND_END]);

    return BSP_OK;
}

/*****************************************************************************
* �� �� : bsp_bbp_dpm_resume
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bbp_dpm_resume(struct dpm_device *dev)
{
    u32 time_before = 0;
    u32 time_after = 0;

    bbp_stamp_set(&g_bbpinfo.om->stamp_resume[BBP_RESUME_IN]);

    bbp_comm_unreset();
    bbp_stamp_set(&g_bbpinfo.om->stamp_resume[BBP_RESUME_BBCUNRST]);

    time_before = bbp_time_get();
    if(g_bbpinfo.dpm.enable_dma)
        bbp_resume_by_dma();
    time_after = bbp_time_get();
    bbp_time_show(time_before,time_after);

    bbp_stamp_set(&g_bbpinfo.om->stamp_resume[BBP_RESUME_END]);

    return BSP_OK;
}

/*****************************************************************************
* �� �� : bsp_bbp_dpm_complete
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bbp_dpm_complete(struct dpm_device *dev)
{
    int iret = BBP_OK;
    u32 time_before = 0;
    u32 time_after = 0;

    bbp_stamp_set(&g_bbpinfo.om->stamp_resume[BBP_COMPLETE_IN]);

    time_before = bbp_time_get();
    if(g_bbpinfo.dpm.enable_dma)
    {
        bbp_resume_by_dma_ok();
    }

    /*д��0x420,�ָ�ͨ��1������ʱ���ſ�bypass*/
    if(CHIP_K3V5 == bsp_get_version_info()->chip_type)
    {
        *(u32 *)((u32)g_bbpinfo.part[BBP_CTU].reg_base+HI_BBP_CTU_CPU_RX1_TX1_CKG_BYPASS_OFFSET)=g_bbpinfo.dpm.ckg_bypass_data;
    }
    *(u32 *)((u32)g_bbpinfo.part[BBP_CTU].reg_base+BBP_IRM_SAVE_OFFSET) = g_bbpinfo.dpm.irm_data;
    
    hi_bbp_sepical_resume();

    time_after = bbp_time_get();
    bbp_time_show(time_before,time_after);

    bbp_stamp_set(&g_bbpinfo.om->stamp_resume[BBP_COMPLETE_END]);

    return iret;
}


struct dpm_device g_bbp_dpm_device={
    .device_name = "bbp_dpm",
    .prepare = bbp_dpm_prepare,
    .suspend = bbp_dpm_suspend,
    .resume = bbp_dpm_resume,
    .complete = bbp_dpm_complete,
    .suspend_late = NULL,
    .resume_early = NULL
};
#endif

/*����ʹ�ã���Ƭʱʹ��*/
void bbp_poweron(void)
{
    u32 i = 0;

    for(i = BBP_VOTE_PWR_MIN;i <= BBP_VOTE_PWR_MAX;i++)
    {
        (void)bbp_pwrctrl_poweron(i);
    }

    for(i = BBP_VOTE_CLK_MIN;i <= BBP_VOTE_CLK_MAX;i++)
    {
        bbp_clkctrl_clkenable(i);
        if(g_bbpinfo.clk.rst_flag)
            bbp_rstctrl_unrstenable(i);
    }
}
void bbp_poweroff(void)
{
    u32 i = 0;

    for(i = BBP_VOTE_PWR_MIN;i <= BBP_VOTE_PWR_MAX;i++)
    {
        (void)bbp_pwrctrl_poweroff(i);
    }

    for(i = BBP_VOTE_CLK_MIN;i <= BBP_VOTE_CLK_MAX;i++)
    {
        bbp_clkctrl_clkdisable(i);
    }
}

void* bbp_part_addr_get(BBP_PART_ID_E part_id)
{
    return (void*)g_bbpinfo.part[part_id].reg_base;
}

static void bbp_om_id_init()
{
    u32 i = 0;

    for(i = 0;i < BBP_VOTE_PWR_NUM;i++)
    {
        g_bbpinfo.om->pwr[i].id = i + BBP_VOTE_PWR_MIN;
    }
    for(i = 0;i < BBP_VOTE_CLK_NUM;i++)
    {
        g_bbpinfo.om->clk[i].id = i + BBP_VOTE_CLK_MIN;
    }
}

/*****************************************************************************
* �� �� : bbp_int_init
* �� �� :
* �� �� : void
* �� �� : void
* �� �� :
* ˵ �� :
*****************************************************************************/
int bbp_init(void)
{
    int i=0;
    int ret = BSP_OK;

    bbp_print_info("bbp_init begin\n");


    ret = bbp_dts_init();
    if(ret)
        goto out;

    /*��ʼ��ȫ�ֱ���*/
    /*�ӵ������*/
    for(i=0;i<BBP_PWR_NUM;i++)
    {
        spin_lock_init(&g_bbpinfo.pwr.pwr_act[i].spinlock);
    }
    for(i=0;i<BBP_CLK_NUM;i++)
    {
        spin_lock_init(&g_bbpinfo.clk.clk_act[i].spinlock);
    }

    /*�͹����ӵ����nv ����*/
    ret = (int)bsp_nvm_read(NV_ID_DRV_NV_PWC_SWITCH, (u8 *)(&g_bbpinfo.dpm.pwc_nv), sizeof(ST_PWC_SWITCH_STRU));
    if(ret != 0)
    {
        bbp_print_error("NV_ID_DRV_NV_PWC_SWITCH:0xd10b read failure!\n");
        (void)memset_s(&g_bbpinfo.dpm.pwc_nv,sizeof(ST_PWC_SWITCH_STRU),0,sizeof(ST_PWC_SWITCH_STRU));
    }

    if( g_bbpinfo.dpm.enable_dma)
    {
        g_bbpinfo.dpm.ctu_save_addr = osl_cachedma_malloc(g_bbpinfo.dpm.ctu_save_size);
    }
    else
    {
        g_bbpinfo.dpm.ctu_save_addr = osl_malloc(g_bbpinfo.dpm.ctu_save_size);
    }
    if(NULL == g_bbpinfo.dpm.ctu_save_addr)
    {
        bbp_print_error("MEM Malloc for ctu_save_addr failed!\n");
        ret = BSP_ERROR;
        goto out;
    }
    (void)memset_s((void *)g_bbpinfo.dpm.ctu_save_addr,g_bbpinfo.dpm.ctu_save_size,0,g_bbpinfo.dpm.ctu_save_size);

    /*��ά�ɲ��ʼ��*/
    g_bbpinfo.om = bsp_pm_dump_get(PM_OM_BBP,sizeof(struct bbp_om_info));
    if(NULL == g_bbpinfo.om)
    {
        bbp_print_error("pm_dump malloc failed,malloc myself!\n");
        g_bbpinfo.om = &g_bbpinfo.ominfo;
    }
    (void)memset_s(g_bbpinfo.om,sizeof(struct bbp_om_info),0,sizeof(struct bbp_om_info));

    /*om����Դ�м�ʱ����id��ʼ��*/
    bbp_om_id_init();

#ifdef CONFIG_CCORE_PM
    ret = bsp_device_pm_add(&g_bbp_dpm_device);
    if (ret){
        bbp_print_error("fail to add bbp dpm device\r\n");
    }
#endif

    /*��ͬоƬƽ̨�ĳ�ʼ������*/
    //g_bbpinfo.ops.init();
    hi_bbp_init();

    if(g_bbpinfo.dpm.pwr_default== 1)
        bbp_poweron();        /*����Ĭ�Ͽ��ӿ���*/
    else if(g_bbpinfo.dpm.pwr_default == 2)
        bbp_poweroff(); /*����Ĭ�Ϲ����µ�*/

    /*register bbp reset and idle*/
    bsp_register_master_idle(BBP_IDLE, hi_bbp_ccpu_reset_and_wait_idle);

    bbp_print_error("bbp init ok!\n");

out:
    return ret;
}

/*lint -restore*/
