
#ifdef __cplusplus
extern "C" {
#endif
#include <cmsis_os.h>
#include <product_config.h>
#include <osl_common.h>
#include <libfdt.h>


#ifdef CONFIG_CCORE_WDT
/*lint --e{537, 762 } */
#include <soc_interrupts_m3.h>
#include <bsp_wdt.h>
#include <hi_wdt.h>
#include <bsp_memmap.h>
#include "wdt_balong.h"

#ifndef CONFIG_HI3630_CCORE_WDT
#include <osl_irq.h>
#include <bsp_sram.h>
#include <bsp_ipc.h>
#include <hi_timer.h>
#include <irq.h>
#include <printk.h>
#include <mdrv_sysboot.h>
#include "wdt_balong.h"
#include "m3_dump.h"
struct wdt_info hi6930_wdt_ident;

unsigned int current_timeout = 0;


unsigned long start_time = 0;

static struct wdt_control g_wdt_ctrl={
	.wdt_cb = WDT_NULL,
};
wdt_timeout_cb g_wdt_rebootfunc = WDT_NULL;

#define M3_WDT_DTS_NAME 		"hisilicon,watchdog_m3"
#define APP_WDT_DTS_NAME  		"hisilicon,ap_wdt_m3"
#define MDM_WDT_DTS_NAME  		"hisilicon,cp_wdt_m3"
struct wdt_base
{
	u32 wdt_base_addr;
	u32 wdt_app_base_addr;
	u32 wdt_mdm_base_addr;
	u32 wdt_int_no;
	u32 wdt_app_int_no;
	u32 wdt_mdm_int_no;
};

struct wdt_base g_wdt_base_info;

s32 bsp_wdt_start(void);
static int hi6930_wdt_stop(void);
static int hi6930_wdt_keepalive(void);
static int hi6930_wdt_set_timeout(u32 timeout);
static u32 hi6930_wdt_get_timeleft(void);
s32 bsp_wdt_suspend(u32 timeout);
void bsp_wdt_resume(void);
s32 bsp_wdt_keepalive(void);

void bsp_wdt_feed(void)
{
	u32 end_time = bsp_get_slice_value();
	if (get_timer_slice_delta(start_time, end_time) >= (WDT_KEEPALIVE_TIME * WDT_DEF_CLK_FREQ))
	{
		start_time = bsp_get_slice_value();
		(void)bsp_wdt_keepalive();
	}
}
/* functions */
static int hi6930_wdt_keepalive(void)
{
	int irqlock = 0;
	local_irq_save(irqlock);
	/* 寄存器解锁 */
	writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	/*中断清除*/
	writel(0x0, g_wdt_base_info.wdt_base_addr + HI_WDG_INTCLR_OFFSET);
	/*给Watchdog上锁*/
	writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);

	local_irq_restore(irqlock);
	return WDT_OK;
}

static int hi6930_wdt_stop(void)
{
    int irqlock = 0;
    local_irq_save(irqlock);
    /* 寄存器解锁 */
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    writel(0x0, g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    /*给Watchdog上锁*/
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    local_irq_restore(irqlock);

    return WDT_OK;
}

void wdt_timer_event(u32 agrv)
{
	if (BSP_FALSE == hi6930_wdt_ident.enable)
	{
		wdt_err("wdtnvdis\n");
		return;
	}
	bsp_softtimer_add(&hi6930_wdt_ident.wdt_timer_list);
}

static int hi6930_wdt_start(void)
{
    int irqlock = 0;
    DRV_WDT_INIT_PARA_STRU wdt_nv_param = {0};
	s32 retValue = -1;
    retValue = (s32)bsp_nvm_read(NV_ID_DRV_WDT_INIT_PARAM, (u8*)&wdt_nv_param, sizeof(DRV_WDT_INIT_PARA_STRU));
    if (NV_OK != retValue)
    {
        wdt_err("wdtnvvalue\n");
		wdt_nv_param.wdt_enable = 0;
		wdt_nv_param.wdt_timeout = 30;
		wdt_nv_param.wdt_suspend_timerout = 120;
    }

	hi6930_wdt_ident.enable = (s32)wdt_nv_param.wdt_enable;
	hi6930_wdt_ident.wdt_timeout = wdt_nv_param.wdt_timeout;
	hi6930_wdt_ident.wdt_suspend_timeout = wdt_nv_param.wdt_suspend_timerout;
	
	hi6930_wdt_ident.wdt_timer_list.func = ( softtimer_func )wdt_timer_event;
	hi6930_wdt_ident.wdt_timer_list.para = 0;
	hi6930_wdt_ident.wdt_timer_list.timeout = WDT_KEEPALIVE_TIME * 1000;
	hi6930_wdt_ident.wdt_timer_list.wake_type = SOFTTIMER_WAKE;

	retValue= bsp_softtimer_create(&hi6930_wdt_ident.wdt_timer_list);
	if (retValue)
    {
		printk("wdttimererr\n");
		return WDT_ERROR;
    }
	
	retValue = (s32)(WDT_DEF_CLK_FREQ * hi6930_wdt_ident.wdt_timeout);/*lint !e713*/
    if (BSP_FALSE == hi6930_wdt_ident.enable)
    {
		printk("wdtdis\n");
		return WDT_OK;
    }
    bsp_softtimer_add(&hi6930_wdt_ident.wdt_timer_list);
    local_irq_save(irqlock);
    
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    writel((u32)retValue, g_wdt_base_info.wdt_base_addr + HI_WDG_LOAD_OFFSET);
    writel(WDT_RST_INT_EN, g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	current_timeout = (u32)retValue / WDT_DEF_CLK_FREQ;
    local_irq_restore(irqlock);

    return WDT_OK;
}

static int hi6930_wdt_set_timeout(u32 timeout) /*输入参数单位是秒*/
{
    int irqlock = 0;
    local_irq_save(irqlock);
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    writel(timeout * WDT_DEF_CLK_FREQ, g_wdt_base_info.wdt_base_addr + HI_WDG_LOAD_OFFSET);
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);

    local_irq_restore(irqlock);
    current_timeout = timeout;
    return WDT_OK;
}

static u32 hi6930_wdt_get_timeleft(void)
{
	u32 reg = 0;
	u32 timeleft = 0;
	int irqlock = 0;
	
	local_irq_save(irqlock);
	
	writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	reg = readl(g_wdt_base_info.wdt_base_addr + HI_WDG_VALUE_OFFSET);
	writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	
	local_irq_restore(irqlock);

	timeleft = reg/WDT_DEF_CLK_FREQ;

	return timeleft;
}
 
/*模拟硬狗复位*/
unsigned int acore_wdt_flag = 0;
unsigned int ccore_wdt_flag = 0;
static irqreturn_t  hi6930_acore_wdt_irq(int irqno, void*param)
{
	/*clear timer3 interrupt*/
#ifdef TIMER_ARM_FEATURE
	writel(0,g_wdt_base_info.wdt_app_base_addr + ARM_ODD_INTCLR_OFFSET);
#else
	readl(g_wdt_base_info.wdt_app_base_addr + HI_TIMER_EOI_OFFSET);
#endif
	printk("awdt\n");

    dump_int_enter(g_wdt_base_info.wdt_app_int_no);

	if (0 == acore_wdt_flag)
	{
		acore_wdt_flag++;
		bsp_ipc_int_send(IPC_CORE_ACORE,IPC_ACPU_INT_SRC_MCPU_WDT);
		if(g_wdt_ctrl.wdt_cb)
		{
			g_wdt_ctrl.wdt_cb(ACORE_WDT_TIMEOUT);
		}
	}
	else if ((0 ==  ((SRAM_SMALL_SECTIONS * )(SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_WDT_AM_FLAG) 
				&& acore_wdt_flag != 0)
	{
		acore_wdt_flag = 0;
		bsp_wdt_reboot_direct();
	}

    dump_int_exit(g_wdt_base_info.wdt_app_int_no);

	return IRQ_HANDLED;
}


static irqreturn_t  hi6930_ccore_wdt_irq(int irqno, void* param)
{
	printk("cwdt\n");
	
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		(void)disable_irq(g_wdt_base_info.wdt_mdm_int_no);
	}

    dump_int_enter(g_wdt_base_info.wdt_mdm_int_no);

	if(g_wdt_ctrl.wdt_cb)
	{
		g_wdt_ctrl.wdt_cb(CCORE_WDT_TIMEOUT);
	}

    dump_int_exit(g_wdt_base_info.wdt_mdm_int_no);

	return IRQ_HANDLED;
}

s32 get_base_info_from_dts(void)
{
	s32 ret = 0;
    struct device_node *np = NULL;

	/* wdt info from dts */
	np = of_find_compatible_node(NULL, NULL, M3_WDT_DTS_NAME);
	if (!np)
	{
		ret = -1;
		goto fail;
	}

	g_wdt_base_info.wdt_base_addr = (u32)of_iomap(np, 0);
	if(0 == g_wdt_base_info.wdt_base_addr)
	{
		ret = -2;
		goto fail;
	}
	g_wdt_base_info.wdt_int_no = (u32)irq_of_parse_and_map(np, 0);
	if(0 == g_wdt_base_info.wdt_int_no)
	{
		ret = -3;
		goto fail;
	}

	/* a core watchdog info from dts */
	np = of_find_compatible_node(NULL, NULL, APP_WDT_DTS_NAME);
	if (!np)
	{
		ret = -4;
		goto fail;
	}

	g_wdt_base_info.wdt_app_base_addr = (u32)of_iomap(np, 0);
	if(0 == g_wdt_base_info.wdt_app_base_addr)
	{
		ret = -5;
		goto fail;
	}
	g_wdt_base_info.wdt_app_int_no = (u32)irq_of_parse_and_map(np, 0);
	if(0 == g_wdt_base_info.wdt_app_int_no)
	{
		ret = -6;
		goto fail;
	}

	/* c core watchdog info from dts */
	np = of_find_compatible_node(NULL, NULL, MDM_WDT_DTS_NAME);
	if (!np)
	{
		ret = -7;
		goto fail;
	}

	g_wdt_base_info.wdt_mdm_base_addr = (u32)of_iomap(np, 0);
	if(0 == g_wdt_base_info.wdt_mdm_base_addr)
	{
		ret = -8;
		goto fail;
	}
	g_wdt_base_info.wdt_mdm_int_no = (u32)irq_of_parse_and_map(np, 0);
	if(0 == g_wdt_base_info.wdt_mdm_int_no)
	{
		ret = -9;
		goto fail;
	}
	
	if(of_property_read_u32_array(np, "wdog_periphid", &g_wdt_ctrl.periphid ,1))
	{
		ret = -10;
		goto fail;
	}
	return WDT_OK;
fail:
    printk("failret%d\n", ret);
    return WDT_ERROR;
}

s32 hi6930_wdt_init(void)
{
	if (0 != get_base_info_from_dts())
	{
        return WDT_ERROR;
    }
    if (0 != request_irq(g_wdt_base_info.wdt_app_int_no, hi6930_acore_wdt_irq, 0, "wdt acore irq", NULL)) 
	{
        printk("airqerr\n");
    }
    if (0 != request_irq(g_wdt_base_info.wdt_mdm_int_no, hi6930_ccore_wdt_irq, 0, "wdt ccore irq", NULL)) 
	{
        printk("cirqerr\n");
    }
    bsp_wdt_start();
    printk("wdtok\n");
    return WDT_OK;	
}

void bsp_wdt_enable(void)
{
}

s32 bsp_wdt_start(void)
{
	start_time = bsp_get_slice_value();
	hi6930_wdt_start();
	return WDT_OK;
}

s32 bsp_wdt_stop(void)
{
    hi6930_wdt_stop();
    return WDT_OK;
}

s32 bsp_wdt_keepalive(void)
{
    hi6930_wdt_keepalive();
    return WDT_OK;
}

s32 bsp_wdt_get_timeleft(u32 *timeleft)
{
	if(WDT_NULL == timeleft)
	{
		printk("timeleftNULL\n");
		return WDT_ERROR;
	}
    *timeleft = hi6930_wdt_get_timeleft();
    return WDT_OK;
}
extern void bsp_drv_power_reboot_direct(void);
/*系统重启*/
void bsp_wdt_reboot_direct(void)
{
    bsp_drv_power_reboot_direct();
}

signed int bsp_wdt_register_hook(void *hook)
{
    if(NULL == hook)
    {
    	printk("hookNULL\n");
       return WDT_ERROR;
    }

	g_wdt_ctrl.wdt_cb = hook;
    return WDT_OK;
}

signed int  bsp_wdt_unregister_hook()
{
	g_wdt_ctrl.wdt_cb = NULL;
	return WDT_OK;
}
s32 bsp_wdt_reboot_register_hook(void *hook)
{
    if(WDT_NULL == hook)
    {
        return WDT_ERROR;
    }
	g_wdt_rebootfunc = hook;
	
	return WDT_OK;
}

s32  bsp_wdt_reboot_unregister_hook(void)
{
	g_wdt_rebootfunc = WDT_NULL;
	
	return WDT_OK;
}

s32 bsp_wdt_set_timeout(u32 timeout)
{
	s32 result;
	result = hi6930_wdt_set_timeout(timeout);
	return result;
}
s32 bsp_wdt_suspend(u32 timeout)
{
	u32 suspend_timeout = hi6930_wdt_ident.wdt_suspend_timeout;
	
	if (BSP_FALSE == hi6930_wdt_ident.enable)
	{
		return WDT_OK;
	}
	bsp_softtimer_delete(&hi6930_wdt_ident.wdt_timer_list);
	bsp_softtimer_modify(&hi6930_wdt_ident.wdt_timer_list, 
										(suspend_timeout - WDT_KEEPALIVE_TIME) * 1000);
	bsp_softtimer_add(&hi6930_wdt_ident.wdt_timer_list);
	bsp_wdt_set_timeout(suspend_timeout);
	return WDT_OK;
}
void bsp_wdt_resume(void)
{
	if (BSP_FALSE == hi6930_wdt_ident.enable)
	{
		return;
	}
	bsp_softtimer_delete(&hi6930_wdt_ident.wdt_timer_list);
	bsp_softtimer_modify(&hi6930_wdt_ident.wdt_timer_list, hi6930_wdt_ident.wdt_timer_list.timeout);
	bsp_softtimer_add(&hi6930_wdt_ident.wdt_timer_list);
    bsp_wdt_set_timeout(hi6930_wdt_ident.wdt_timeout);
}


void bsp_wdt_stop_awdt(void)
{
	u32 ret = 0;
	if (BSP_FALSE == hi6930_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		ret = readl(g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);
		writel(ret&(~0x80),g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
		ret &= ~HARD_TIMER_ENABLE;
		ret |=TIMER_INT_MASK;
		writel(ret, HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
	}
}
void bsp_wdt_restart_awdt(void)
{
	u32 ret = 0;
	if (BSP_FALSE == hi6930_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		ret = readl(g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);
		writel(ret|0x80,g_wdt_base_info.wdt_app_base_addr + ARM_ODD_CTRL_OFFSET);		
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
		ret |= HARD_TIMER_ENABLE ;
		ret&=(~TIMER_INT_MASK);
		writel(ret,HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_app_base_addr);
	}
}
void bsp_wdt_stop_cwdt(void)
{
	u32 ret = 0;
	unsigned long irqlock;
	if (BSP_FALSE == hi6930_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		local_irq_save(irqlock);
    	writel(WDT_UNLOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	writel(0x0, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_CONTROL_OFFSET);
    	writel(WDT_LOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	local_irq_restore(irqlock);
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
		ret &= ~HARD_TIMER_ENABLE;
		ret |=TIMER_INT_MASK;
		writel(ret, HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
	}
}
void bsp_wdt_restart_cwdt(void)
{
	u32 ret = 0;
	unsigned long irqlock;

	if (BSP_FALSE == hi6930_wdt_ident.enable)
    {
		return;
    }
	if(HARD_WATCHDOG == g_wdt_ctrl.periphid)
	{
		local_irq_save(irqlock);
    	writel(WDT_UNLOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	writel(0x01, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_CONTROL_OFFSET);
    	writel(WDT_LOCK, g_wdt_base_info.wdt_mdm_base_addr + HI_WDG_LOCK_OFFSET);
    	local_irq_restore(irqlock);
	}
	else
	{
		ret = readl(HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
		ret |= HARD_TIMER_ENABLE ;
		ret&=(~TIMER_INT_MASK);
		writel(ret,HI_TIMER_CONTROLREG_OFFSET + g_wdt_base_info.wdt_mdm_base_addr);
	}
}
void bsp_wdt_print_debug(void)
{
    unsigned int timeleft = 0;
    bsp_wdt_get_timeleft(&timeleft);
    printk("\r\ntimeleft:%d\n", timeleft);
    printk("set time:%d\n", current_timeout);
    timeleft = readl(g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    printk("ctr reg:0x%x\n", timeleft);
    timeleft = readl(g_wdt_base_info.wdt_base_addr + HI_WDG_VALUE_OFFSET);
    printk("wdt val:0x%x\n", timeleft);
}

#elif defined(CONFIG_HI3630_CCORE_WDT)

#include <m3_modem.h>


s32 bsp_wdt_stop(void)
{
	writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    writel(0x0, g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    /*给Watchdog上锁*/
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
	return WDT_OK;
}
s32 bsp_wdt_set_timeout(u32 timeout)
{
	s32 retValue = -1;
	retValue = WDT_DEF_CLK_FREQ * timeout;
    writel(WDT_UNLOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);
    	/*中断清除*/
	writel(0x0, g_wdt_base_info.wdt_base_addr + HI_WDG_INTCLR_OFFSET);
    writel(retValue, g_wdt_base_info.wdt_base_addr + HI_WDG_LOAD_OFFSET);
    writel(WDT_RST_INT_EN, g_wdt_base_info.wdt_base_addr + HI_WDG_CONTROL_OFFSET);
    writel(WDT_LOCK, g_wdt_base_info.wdt_base_addr + HI_WDG_LOCK_OFFSET);

    return WDT_OK;
}
extern u32 get_modem_init_flag(void);

__ao_data int hi6930_wdt_timeout = 30;
__ao_data int hi6930_wdt_enable = 0;
void bsp_wdt_stop_cwdt(void)
{
	if (BSP_FALSE == hi6930_wdt_enable)
    {
		return;
    }
	(void)bsp_wdt_stop();
}
void bsp_wdt_restart_cwdt(void)
{
	
	if (BSP_FALSE == hi6930_wdt_enable)
    {
		return;
    }
	 (void)bsp_wdt_set_timeout(hi6930_wdt_timeout);
}

s32 hi6930_wdt_init(void)
{
	//添加初始化判断
	s32 retValue = -1;
	DRV_WDT_INIT_PARA_STRU wdt_nv_param = {0};
	if (MODEM_ALREADY_INIT_MAGIC != get_modem_init_flag())
	{
	    retValue = bsp_nvm_read(NV_ID_DRV_WDT_INIT_PARAM, (u8*)&wdt_nv_param, sizeof(DRV_WDT_INIT_PARA_STRU));
	    if (NV_OK != retValue)
	    {
	       	printk("read nv fail\n");
			wdt_nv_param.wdt_enable = 0;
			wdt_nv_param.wdt_timeout = 30;
	    }

	    /*读取系统控制寄存器0x33c bit[0]为0打开看门狗，1关闭看门狗*/
	    retValue = readl(HI_AP_SYSCTRL_BASE_ADDR + HI_WDG_SYSCTRL_ENABLE_OFFSET) & 0x1;
		/*NV 、寄存器共同判别是否可开狗*/
		if ((0 == retValue) && (wdt_nv_param.wdt_enable != 0))
		{
			wdt_nv_param.wdt_enable = 1;
		}
		else
		{
			wdt_nv_param.wdt_enable = 0;
		}
		hi6930_wdt_enable = wdt_nv_param.wdt_enable;
		hi6930_wdt_timeout = wdt_nv_param.wdt_timeout;
	}

   	return 0;
}

void bsp_wdt_enable(void)
{
	s32 timeout = 600;
	if (BSP_FALSE == hi6930_wdt_enable)
    {
		return;
    }
	(void)bsp_wdt_set_timeout(timeout);
}
void bsp_wdt_feed(void)
{
	
}

 s32 bsp_wdt_suspend(u32 timeout)
 {
	return WDT_OK;
 }
 void bsp_wdt_resume(void)
 {
 }
 
void bsp_wdt_stop_awdt(void)
{
	
}
void bsp_wdt_restart_awdt(void)
{
	
}

#endif     /*end CONFIG_HI3630_CCORE_WDT*/

#else       /* !CONFIG_CCORE_WDT   此分支为打桩*/

#ifndef WDT_OK
#define WDT_OK                   			(0)
#endif
#ifndef WDT_ERROR
#define WDT_ERROR                			(-1)
#endif

s32 hi6930_wdt_init(void)
{
	return WDT_OK;
}
s32 bsp_wdt_start(void)
{
    return WDT_OK;
}

s32 bsp_wdt_stop(void)
{
	return WDT_OK;
}
void bsp_wdt_enable(void)
{

}
/*****************************************************************************
* 函 数 名  : BSP_WDT_HardwareFeed
*
* 功能描述  : 重置看门狗计数寄存器（喂狗）
*
* 输入参数  : BSP_U8 u8WdtId :看门狗ID
* 输出参数  : 无
*
* 返 回 值  : WDT_OK:    操作成功
*             WDT_ERROR: 操作失败
* 其它说明  :
*
*****************************************************************************/
s32 bsp_wdt_keepalive(void)
{
    return WDT_OK;
}


/*****************************************************************************
* 函 数 名  : BSP_WDT_TimerReboot
*
* 功能描述  : 通过设置timer中断，通知mcore重启。
*
* 输入参数  : 无
* 输出参数  : 无
*
* 返 回 值  : WDT_OK:    操作成功
*             WDT_ERROR: 操作失败
* 其它说明  :
*
*****************************************************************************/

s32 bsp_wdt_set_timeout(u32 timeout)/*s*/
{
	return WDT_OK;
}
 s32 bsp_wdt_get_timeleft(u32 *timeleft)/*s*/
{
	return WDT_OK;
}
 s32 bsp_wdt_register_hook(void *hook)
{
	return WDT_OK;
}

s32  bsp_wdt_unregister_hook(void)
{
	return WDT_OK;
}

 s32 bsp_wdt_suspend(u32 timeout)
 {
	return WDT_OK;
 }
 void bsp_wdt_resume(void)
 {
 }
 
void bsp_wdt_stop_awdt(void)
{
	
}
void bsp_wdt_restart_awdt(void)
{
	
}
void bsp_wdt_stop_cwdt(void)
{
	
}
void bsp_wdt_restart_cwdt(void)
{
	
}
void bsp_wdt_feed(void)
{

}
void bsp_wdt_print_debug(void)
{

}
#endif   /* end of CONFIG_CCORE_WDT */

#ifdef __cplusplus
}
#endif
