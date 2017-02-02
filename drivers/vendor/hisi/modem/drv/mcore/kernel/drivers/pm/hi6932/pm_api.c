/*----------------------------------------------------------------------------
 *      balongv7r5 m3 pm
 *----------------------------------------------------------------------------
 *      Name:    pm.C
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r5 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"

#include "osl_types.h"
#include "osl_irq.h"
#include <hi_base.h>
#include "soc_interrupts_m3.h"
#include "drv_edma_enum.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "bsp_nvim.h"
#include "bsp_dsp.h"
#include "bsp_shared_ddr.h"
#include "bsp_softtimer.h"
#include "bsp_hardtimer.h"
#include "edma_balong.h"
#include "dpm_balong.h"
#include "ios_pd.h"
#include "wdt_balong.h"
#include "m3_cpufreq.h"
#include "m3_pm.h"
#include "m3_pm_test.h"
#include "pm_api.h"
#include "cpufreq_api.h"


/*lint --e{40, 63, 409, 438} */
extern T_PM_ST gPmSt;
extern T_PM_BAKEUP_ST gPmBakeupSt;
extern T_PM_COUNT_ST gPmCountSt;
extern T_PM_ERROR_ST gPmErrorSt;
extern DRV_NV_PM_TYPE gPmNvSt;
extern u32 sys_initial;
extern u32 uart_delay_flag;
extern struct m3_pm_stamp *m3_pm_stamps;

//#include "bsp_pm_om.h"
#ifndef bsp_pm_log_type
#define bsp_pm_log_type(a,b,c,d)
#endif

struct crg_clk_bak
{
    u32 crg_dfs1_ctrl1;
    u32 crg_dfs1_ctrl2;
    u32 crg_dfs1_ctrl3;
    u32 pd_crg_clkdiv2;
};

u32 tcxo = 0;
struct crg_clk_bak clk_bak = {0};
u32 m3_record_num = 0;
u32 m3_wakeup_flag = 0;
u32 g_buck3on_txco_on = 1;

T_PM_DDRC gddrreg;

extern DRV_DRX_DELAY_STRU gNvDrxDelaySt;

static void pm_mcu_bakeup_debug(void);
static void pm_mcu_wakeup_debug(void);




/* irqs that can wakeup from deepsleep */
u32 pm_deepsleep_irq[]={M3_TIMER7_INT,/*35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,*/\
M3_CCPU_WAKEUP_INTR,M3_ACPU_WAKEUP_INTR/*,M3_CM3_DBG_WAKE_INT*/}; // todo need or not ?
#define DS_IRQ_NUM sizeof(pm_deepsleep_irq)/sizeof(pm_deepsleep_irq[0])

/*PWR_CTRL16 , PWR_CTRL17*/  /*0x1FFFE0  -- all timer*/
u32 pm_mcore_wsrc[WSRC_REG_NUM]={\
                M3_WSRC_0_TIMER7\
                ,/*M3_WSRC_1_DEBUG|*/M3_WSRC_1_CCPU|M3_WSRC_1_ACPU\
                };
/*PWR_CTRL24 , PWR_CTRL25*/
u32 pm_acore_wsrc[WSRC_REG_NUM]={\
                APPA9_WSRC_0_IPC0|APPA9_WSRC_0_IPC1|APPA9_WSRC_0_RTC\
                |APPA9_WSRC_0_IPF1|APPA9_WSRC_0_TIMER0|APPA9_WSRC_0_TIMER2|APPA9_WSRC_0_PMU\
                ,/*APPA9_WSRC_1_DEBUG|*/APPA9_WSRC_1_GPIO_0|APPA9_WSRC_1_PSAM_0\
                };
/*PWR_CTRL30 , PWR_CTRL31*/
u32 pm_ccore_wsrc[WSRC_REG_NUM]={\
                MDMA9_WSRC_0_IPF0|MDMA9_WSRC_0_TIMER1|MDMA9_WSRC_0_TIMER3\
                |MDMA9_WSRC_0_TIMER4|MDMA9_WSRC_0_LDRX_CPU\
                |MDMA9_WSRC_0_TDRX_CPU|MDMA9_WSRC_0_G1_CPU|MDMA9_WSRC_0_G2_CPU\
                |MDMA9_WSRC_0_W_CPU\
                ,/*MDMA9_WSRC_1_DEBUG|*/MDMA9_WSRC_1_IPC0|MDMA9_WSRC_1_IPC1\
                };

void pm_debug_udelay (u32 ms, u32 flag)
{
    u32 start = 0;
    u32 end = 0;
    u32 tmp = 0;

    if(flag == 1)
    {
        start = bsp_get_slice_value();
        do
        {
            end = bsp_get_slice_value();
            tmp = end - start;
        }while(tmp<(ms*32));
    }

}

void pm_ldo32_enable(void)
{
    u32 reg_value = 0;
    
    reg_value = readl(0x9001a000 + (0x96 << 2));
    reg_value |= (0x1<<1);
    writel(reg_value,0x9001a000 + (0x96 << 2));
}
void pm_ldo32_disable(void)
{
    u32 reg_value = 0;
    
    reg_value = readl(0x9001a000 + (0x96 << 2));
    reg_value &= ~(0x1<<1);
    writel(reg_value,0x9001a000 + (0x96 << 2));
}

void pm_wsrc_init(void)
{
    u32 i = 0;
    
    /* wake_src is set up by PWR_CTRL for m3 */
    for(i = 0; i < WSRC_REG_NUM; i++)
    {
        writel(pm_mcore_wsrc[i], M3PM_SC_BASE_AO+PWR_CTRL16+i*4);
    }
    
    /* wake_src is set up by PWR_CTRL for m3,acore,ccore */
    for(i = 0; i < WSRC_REG_NUM; i++)
    {
        writel(pm_acore_wsrc[i], M3PM_SC_BASE_AO+PWR_CTRL24+i*4);
        writel(pm_ccore_wsrc[i], M3PM_SC_BASE_AO+PWR_CTRL30+i*4);
    }
    (void)request_irq(M3_ACPU_WAKEUP_INTR, IntAcoreHandler, IRQF_DISABLED, "acore irq", 0);/*lint !e713*/
    (void)request_irq(M3_CCPU_WAKEUP_INTR, IntCcoreHandler, IRQF_DISABLED, "ccore irq", 0);/*lint !e713*/

    
    /*  only one wake_src: ipc. hifi do not have PWR_CTRLxx regs to set up wake_src.*/
    (void)request_irq(M3_IPCM2HIFI_0     , IntHiFiHandler, IRQF_DISABLED, "hifi irq", 0);/*lint !e713*/


}


void pm_mdma9_wsrc_set(u32 lvl)
{
    u32 val;
    switch(lvl)
    {
        /* drx timer ,timer5, irq=40 */
        case M3_TIMER5_INT:
            val = readl(M3PM_SC_BASE_AO+PWR_CTRL30);
            val |= MDMA9_WSRC_0_TIMER5;
            writel(val, M3PM_SC_BASE_AO+PWR_CTRL30);
            break;
        default:
            printk("mdma9_wsrc_set %d err\n",lvl);
            break;
    }
    return;
}
void pm_mdma9_wsrc_unset(u32 lvl)
{
    u32 val;
    switch(lvl)
    {
        /* drx timer ,timer5, irq=40 */
        case M3_TIMER5_INT:
            val = readl(M3PM_SC_BASE_AO+PWR_CTRL30);
            val &= ~(MDMA9_WSRC_0_TIMER5);
            writel(val, M3PM_SC_BASE_AO+PWR_CTRL30);
            break;
        default:
            printk("mdma9_wsrc_unset %d err\n",lvl);
            break;
    }
    return;
}


void pm_appa9_nvic_enable(void)
{
    clear_pending_irq(M3_ACPU_WAKEUP_INTR);
    enable_irq(M3_ACPU_WAKEUP_INTR);
}

void pm_appa9_nvic_disable(void)
{
    disable_irq(M3_ACPU_WAKEUP_INTR);
}

void pm_mdma9_nvic_enable(void)
{
    clear_pending_irq(M3_CCPU_WAKEUP_INTR);
    enable_irq(M3_CCPU_WAKEUP_INTR);
}

void pm_mdma9_nvic_disable(void)
{
    disable_irq(M3_CCPU_WAKEUP_INTR);
}

void pm_hifi_nvic_enable(void)
{
    clear_pending_irq(M3_IPCM2HIFI_0);
    enable_irq(M3_IPCM2HIFI_0);
}

void pm_hifi_nvic_disable(void)
{
    disable_irq(M3_IPCM2HIFI_0);
}

void pm_mdma9_pdown(void)
{
#ifndef CONFIG_M3PM_TEST
    u32 temp = 0;
    do{
        temp = readl(M3PM_SC_BASE_AO + PWR_STAT0);
    }while(!(temp&(0x1<<10)));
#endif
    /* disable clk */
    writel(0x1<<3, M3PM_SC_BASE_MDM + MDM_CRG_CLKDIS0);
    /* reset */
    writel(0x80C0, M3PM_SC_BASE_MDM + MDM_CRG_SRSTEN0);
}
void pm_mdma9_pup(void)
{
    /* enable clk */
    writel(0x1<<3, M3PM_SC_BASE_MDM + MDM_CRG_CLKEN0);
    /* unreset */
    writel(0x80C0, M3PM_SC_BASE_MDM + MDM_CRG_SRSTDIS0);
}

void pm_appa9_pdown(void)
{
#ifndef CONFIG_M3PM_TEST
    u32 temp = 0;
    do{
        temp = readl(M3PM_SC_BASE_AO + PWR_STAT0);
    }while(!(temp&(0x1<<12)));
#endif
    /* disable clk */
    writel(0x1<<26, M3PM_SC_BASE_PD + PD_CRG_CLKDIS3);
    /* iso ctrl enable */
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL4);
    /* reset */
    writel(0x4001, M3PM_SC_BASE_PD + PD_CRG_SSRSTEN1);
    /* mtcmos power down */
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL7);
}
void pm_appa9_pup(void)
{
    u32 tmp = 0;
    /* mtcmos power up and wait for complete*/
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL6);
    do{
        tmp = readl(M3PM_SC_BASE_AO + PWR_STAT1);
        tmp = tmp & 0x1;
    }while(!tmp);
    udelay(30);

    /* enable clk */
    writel(0x1<<26, M3PM_SC_BASE_PD + PD_CRG_CLKEN3);
    /* iso ctrl disable */
    writel(0x1, M3PM_SC_BASE_AO + PWR_CTRL5);
    /* unreset */
    writel(0x4001, M3PM_SC_BASE_PD + PD_CRG_SSRSTDIS1);
}


void pm_hifi_pll_close(u32 vote)
{
    u32 tmp = 0;
    UNUSED(vote);

	tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
	tmp |= 0x1;
	writel(tmp, M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
}

void pm_hifi_pll_open(u32 vote)
{
    u32 tmp = 0;

    UNUSED(vote);
	tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
	tmp &= ~0x1;
	writel(tmp, M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);

    do{
		tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
		tmp &= ((u32)0x1<<31);
	}while(!tmp);
}

void pm_hifi_pdown(void)
{
    /* no reg to check wfi */
    /* disable clk */
    writel((0x1<<31), M3PM_SC_BASE_PD + PD_CRG_CLKDIS3);
    /* reset */
    writel((0x3<<19), M3PM_SC_BASE_PD + PD_CRG_SRSTEN2);

}
void pm_hifi_pup(void)
{
    /* unreset */
    writel((0x3<<19), M3PM_SC_BASE_PD + PD_CRG_SRSTDIS2);
    /* enable clk */
    writel((0x1<<31), M3PM_SC_BASE_PD + PD_CRG_CLKEN3);
}


/* todo: main.c ��ʼ��ʱ�е���*/
void pm_dsp_pll_open(u32 vote)
{
    UNUSED(vote);
    return;
}


void pm_acore_sleep()
{
    pm_appa9_pdown();
    bsp_wdt_stop_awdt();
    pm_appa9_nvic_enable();
    cpufreq_set_sleepflag(CPUFREAQ_ACORE, 1);
    gPmCountSt.Acore.SleepTimes++;
}
void pm_ccore_sleep()
{
    pm_mdma9_pdown();
//    pm_dsp_pll_close((u32)PM_PWR_VOTE_CCORE);
    bsp_wdt_stop_cwdt();
    pm_mdma9_nvic_enable();
    cpufreq_set_sleepflag(CPUFREAQ_CCORE, 1);
    gPmCountSt.Ccore.SleepTimes++;
}
void pm_hifi_sleep()
{
    (void)bsp_hifi_stop();
    pm_hifi_pdown();
    pm_hifi_pll_close(PM_PWR_VOTE_HIFI);
    pm_hifi_nvic_enable();
    gPmCountSt.HiFi.SleepTimes++;
}

void pm_acore_wake()
{
    bsp_wdt_restart_awdt();
    pm_appa9_pup();
    cpufreq_set_sleepflag(CPUFREAQ_ACORE, 0);
    bsp_pm_log_type(PM_OM_PMM,ACORE_WAKE,sizeof(T_PM_CORE_WAKE_ST),&gPmCountSt.Acore);
}
void print_acore_wsrc(void)
{
    printk("A wsrc :0x%x,0x%x\n"
        ,readl(M3PM_SC_BASE_AO + PWR_STAT16)
        ,readl(M3PM_SC_BASE_AO + PWR_STAT17));
}
void pm_ccore_wake()
{
    bsp_wdt_restart_cwdt();
//    pm_dsp_pll_open((u32)PM_PWR_VOTE_CCORE);
    pm_mdma9_pup();
    cpufreq_set_sleepflag(CPUFREAQ_CCORE, 0);
    bsp_pm_log_type(PM_OM_PMM,CCORE_WAKE,sizeof(T_PM_CORE_WAKE_ST),&gPmCountSt.Ccore);
}
void print_ccore_wsrc(void)
{
    printk("C wsrc:0x%x,0x%x\n"
        ,readl(M3PM_SC_BASE_AO + PWR_STAT23)
        ,readl(M3PM_SC_BASE_AO + PWR_STAT24));
}

void pm_hifi_wake()
{
    pm_hifi_pll_open(PM_PWR_VOTE_HIFI);
    pm_hifi_pup();
    (void)bsp_hifi_restore();
    (void)bsp_hifi_run();
    bsp_pm_log_type(PM_OM_PMM,HIFI_WAKE,sizeof(T_PM_CORE_WAKE_ST),&gPmCountSt.HiFi);
}

u32 ddr_hit_addr = 0;
static void ddr_hit_set(void)
{
    u32 temp = 0;
    
    if(0==ddr_hit_addr)
    {
        return;
    }
    temp = 0x12345678;
    writel(temp, ddr_hit_addr);
}

static void ddr_hit_test(void)
{
    u32 temp = 0;
    if(0==ddr_hit_addr)
    {
        return;
    }
    temp = readl(ddr_hit_addr);
    if(temp != 0x12345678)
    {
        m3_pm_stamps->ddr_hit_test_out_cnt = 0x12345678;
        __asm__ __volatile__("b .");
    }
    writel(temp, ddr_hit_addr);
    temp = readl(ddr_hit_addr);
    if(temp!=0x12345678)
    {
        m3_pm_stamps->ddr_hit_test_out_cnt = 0x87654321;
        __asm__ __volatile__("b .");
    }
    m3_pm_stamps->ddr_hit_test_out_cnt++;
}

#if 0
porting not used

static void pm_ddr_out_sref()
{
    u32 tmp = 0;
    u32 times = 20;

    writel(0x0, MDDRC_SREFCTRL);
    do{
    tmp = readl(MDDRC_STATUS);
    tmp &= 0x1;
    }while(tmp);

    while(times)
    {
        times--;
    }
    
}
#endif

#if 1

#define _CFG_CLK_CPU_M3_ (120*1000*1000)

void ddrc_init_udelay(unsigned int us)
{
#ifndef BSP_CONFIG_EDA
    while(us--) {
        unsigned long t = (_CFG_CLK_CPU_M3_/3)/1000000;
        while(t--)
            __asm__ __volatile__("nop");
    }
#endif
}

u32 mddrc_save[1] = {0};
void v722_porting_mddrc_save(void)
{
    mddrc_save[0] = readl(0x900400c4);
}

void v722_porting_mddrc_pm_init(void)
{
    writel( 0x7c0     , 0x90000010 );
    writel( 0x60000   , 0x90000364 );
    writel( 0x1       , 0x90040404 );
    writel( 0x1       , 0x90040604 );
    writel( 0x01e00210, 0x9004001c );
    writel( 0x30005700, 0x90040020 );
    writel( 0x131     , 0x9004002c );
    writel( 0xa0000000, 0x90040040 );
    writel( 0x32330603, 0x90040050 );
    writel( 0x04324607, 0x90040054 );
    writel( 0x3230800c, 0x90040058 );
    writel( 0x00032032, 0x9004005c );
    writel( 0x0       , 0x900400f4 );
    writel( 0x00000101, 0x900400ac );
    writel( mddrc_save[0], 0x900400c4 );
    writel( 0x0       , 0x90040004 );
	while( readl(0x90040000) & (0x1<<2) )
    {};   
    ddr_hit_test();
}
void v722_emu_mddrc_pm_init(void)
{
    writel( 0x7c0     , 0x90000010 );
    writel( 0x60000   , 0x90000364 );
    writel( 0x1       , 0x90040404 );
    writel( 0x1       , 0x90040604 );
    writel( 0x01e00211, 0x9004001c );
    writel( 0x30105300, 0x90040020 );
    writel( 0x1122    , 0x9004002c );
    writel( 0xa0000000, 0x90040040 );
    writel( 0x5498170e, 0x90040050 );
    writel( 0x18a7462c, 0x90040054 );
    writel( 0x34514000, 0x90040058 );
    writel( 0x0054e033, 0x9004005c );
    writel( 0x0       , 0x900400f4 );
    writel( 0x00000501, 0x900400ac );
    writel( mddrc_save[0], 0x900400c4 );
    writel( 0x0       , 0x90040004 );
	while( readl(0x90040000) & (0x1<<2) )
    {};   
    ddr_hit_test();
}


void fpga_emu_ddr_pup()
{
    #ifdef BSP_CONFIG_EMU
    v722_emu_mddrc_pm_init();
    #else
    v722_porting_mddrc_pm_init();
    #endif
}

static void pm_ddr_porting_in_sref(void)
{
    u32 tmp = 0;
    volatile u32 times = 20;

    writel(0x1, 0x90040004);
    do{
    tmp = readl(0x90040000);
    }while( ((tmp>>2)&0x1)!=1 );
    
    while(times)
    {
        times--;
    }
}

static void pm_ddr_porting_out_sref(void)
{
    u32 tmp = 0;
    volatile u32 times = 20;

    writel(0x0, 0x90040004);
    do{
    tmp = readl(0x90040000);
    }while( ((tmp>>2)&0x1)==1 );
    
    while(times)
    {
        times--;
    }
}

#endif

struct sys_reg_need_bak
{
    u32 start;
    u32 end;
};

struct sys_reg_need_set
{
    u32 from;
};
#define SYS_REG_BAK_NUM 10
#define SYS_REG_SET_NUM 11
struct sys_reg_bak_cfg
{
    struct sys_reg_need_bak bak[SYS_REG_BAK_NUM];
    struct sys_reg_need_set set[SYS_REG_SET_NUM];
};

/*
SC_BASE_MDM    0x80200000
SC_BASE_PD       0x90000000
SC_BASE_AO       0x20000000

SYS_PD:     0x400-0x468    0x800-0x884
SYS_MDM:  0x400-0x540    0x590-0x5A4

PD_CRG:     clk[0x0] x 4, srst[0x60] x 3
                 0x100-0x10c, 0x114-0x11c, 0x140-0x148, 0x200-0x220, 0x230-0x244
                 
MDM_CRG:  clk[0x0] x 2, srst[0x20] x 2, 0x40-0x44,0x60
*/

void sys_bak_data_init(void)
{
    struct sys_reg_bak_cfg * cfg = 0;

    cfg = (struct sys_reg_bak_cfg*)(SHM_BASE_ADDR + SHM_OFFSET_M3PM);

    /*SYS_PD:     0x400-0x468    0x800-0x884*/
    cfg->bak[0].start = 0x90000400;
    cfg->bak[0].end   = 0x90000468;
    cfg->bak[1].start = 0x90000800;
    cfg->bak[1].end   = 0x90000884;
    /*SYS_MDM:  0x400-0x540    0x590-0x5A4*/
    cfg->bak[2].start = 0x80200400;
    cfg->bak[2].end   = 0x80200540;
    cfg->bak[3].start = 0x80200590;
    cfg->bak[3].end   = 0x802005A4;
    /*PD_CRG:   0x100-0x10c, 0x114-0x11c, 0x140-0x148, 0x200-0x220, 0x230-0x244*/
    cfg->bak[4].start = 0x90000100;
    cfg->bak[4].end   = 0x9000010c;
    cfg->bak[5].start = 0x90000114;
    cfg->bak[5].end   = 0x9000011c;
#if 0
    cfg->bak[6].start = 0x90000140;
    cfg->bak[6].end   = 0x90000148;
    cfg->bak[7].start = 0x90000200;
    cfg->bak[7].end   = 0x90000220;
    cfg->bak[8].start = 0x90000230;
    cfg->bak[8].end   = 0x90000244;
#endif
    /*MDM_CRG:  0x40-0x44,0x60*/
    cfg->bak[6].start = 0x80200040;
    cfg->bak[6].end   = 0x80200044;
    cfg->bak[7].start = 0x80200060;
    cfg->bak[7].end   = 0x80200060;
	
    cfg->bak[8].start = 0x90000900;
    cfg->bak[8].end   = 0x90000910;
	
    cfg->bak[9].start = 0x90100d00;
    cfg->bak[9].end   = 0x90100d10;
    /*PD_CRG:   clk[0x0] x 4, srst[0x60] x 3
      MDM_CRG:  clk[0x0] x 2, srst[0x20] x 2, 
                writle (val) enable, writel ~(val) disable*/
    cfg->set[0].from = 0x90000008;
    cfg->set[1].from = 0x90000018;
    cfg->set[2].from = 0x90000028;
    cfg->set[3].from = 0x90000038;
    cfg->set[4].from = 0x90000068;
    cfg->set[5].from = 0x90000074;
    cfg->set[6].from = 0x90000080;
    cfg->set[7].from = 0x80200008;
    cfg->set[8].from = 0x80200018;
    cfg->set[9].from = 0x80200028;
    cfg->set[10].from= 0x80200038;
    
}


void sys_reg_bak()
{
    struct sys_reg_bak_cfg * cfg = 0;
    u32 * regs_bak = 0;
    u32 i = 0;
    u32 * temp_reg = 0;

    cfg = (struct sys_reg_bak_cfg*)(SHM_BASE_ADDR + SHM_OFFSET_M3PM);
    regs_bak = (u32*) ((u32)cfg + sizeof(struct sys_reg_bak_cfg));

    for(i=0;i<SYS_REG_BAK_NUM;i++)
    {
        for(temp_reg = (u32*)cfg->bak[i].start; temp_reg <= (u32*)cfg->bak[i].end; temp_reg++)
        {
            *regs_bak = *temp_reg;
            regs_bak++;
        }
    }
    for(i=0;i<SYS_REG_SET_NUM;i++)
    {
        temp_reg = (u32*)cfg->set[i].from;
        *regs_bak = *temp_reg;
        regs_bak++;
    }
}
void sys_reg_restore()
{
    struct sys_reg_bak_cfg * cfg = 0;
    u32 *regs_bak = 0;
    u32 i = 0;
    u32 * temp_reg = 0;
    u32 reg_val;

    cfg = (struct sys_reg_bak_cfg*)(SHM_BASE_ADDR + SHM_OFFSET_M3PM);
    regs_bak = (u32*) ((u32)cfg + sizeof(struct sys_reg_bak_cfg));

    for(i=0;i<SYS_REG_BAK_NUM;i++)
    {
        for(temp_reg = (u32*)cfg->bak[i].start; temp_reg <= (u32*)cfg->bak[i].end; temp_reg++)
        {
            *temp_reg = *regs_bak;
            regs_bak++;
        }
    }
    for(i=0;i<SYS_REG_SET_NUM;i++)
    {
        temp_reg = (u32*)cfg->set[i].from;
        *(temp_reg-2) = *regs_bak;
        *(temp_reg-1) = ~(*regs_bak);
        regs_bak++;
    }
    /* open dsp pll */
    reg_val = readl(0x90000214);
    writel(reg_val&(~0x11),0x90000214);
    do{
		reg_val = readl(0x90000214);
		reg_val &= ((u32)0x1<<31);
	}while(!reg_val);
    /* dsp clk_src in enable */
    writel(0x30000000,0x90000030);
    /* dsp clk_src switch to peri pll (default dsp pll) */
    writel(0x2,0x90000148);
    
    /* close dsp pll */
    reg_val = readl(0x90000214);
    writel(reg_val|0x1,0x90000214);
}

s32 sram_bak(void)
{
    s32 ret = 0;
    u32 val = 0;
    
    /* open edma clk */
    val = readl(0x8020000C);
    val = val&(0x1<<18);
    if(!val)
        writel(0x1<<18,0x80200000);
    
    ret = bsp_edma_m2m_channel(0, (u32)(HI_SRAM_MEM_BASE_ADDR), (u32)(SHM_BASE_ADDR + SHM_OFFSET_SRAM_BAK), HI_SRAM_MEM_SIZE);
    if(ret != 0)
    {
        gPmErrorSt.u32AxiBakeupErrTimes++;
        if(!val)
            writel(0x1<<18,0x80200004);
        return 1;
    }
	do
	{
	    ret = bsp_edma_channel_state(0);
	}while(ret != 0);
    
    /* close edma clk */
    if(!val)
        writel(0x1<<18,0x80200004);

    return ret;
}
s32 sram_restore(void)
{
    s32 ret = 0;
    u32 val = 0;
    
    /* open edma clk */
    val = readl(0x8020000C);
    val = val&(0x1<<18);
    if(!val)
        writel(0x1<<18,0x80200000);
    
    ret = bsp_edma_m2m_channel(0, (u32)(SHM_BASE_ADDR + SHM_OFFSET_SRAM_BAK), (u32)(HI_SRAM_MEM_BASE_ADDR), HI_SRAM_MEM_SIZE);
    if(ret != 0)
    {
        gPmErrorSt.u32AxiRestoreErrTimes++;
        if(!val)
            writel(0x1<<18,0x80200004);
        return 1;
    }
	do
	{
	    ret = bsp_edma_channel_state(0);
	}while(ret != 0);

    /* close edma clk */
    if(!val)
        writel(0x1<<18,0x80200004);

    return ret;
}


static void pm_set_bbpwakeup_flag(void)
{

    u32 tmp = 0;

    tmp = readl( M3PM_SC_BASE_AO + PWR_STAT23 );
    tmp = tmp & MDMA9_WSRC_0_LDRX_CPU;  /* todo only lte in old version, tds---? */
    if(tmp){
        writel(1, PM_SHM_TIMESTAMP_ADDR);
    }
    else{
        writel(0, PM_SHM_TIMESTAMP_ADDR);
    }
    writel(readl(M3PM_SC_BASE_AO + 0x8 ), PWR_SRAM_CRG_REG);
    writel(readl(M3PM_SC_BASE_AO + 0x14), PWR_SRAM_CRG_REG + 0x4);
    writel(readl(M3PM_SC_BASE_AO + 0x20), PWR_SRAM_CRG_REG + 0x8);
    writel(readl(M3PM_SC_BASE_AO + 0x2c), PWR_SRAM_CRG_REG + 0xC);
    writel(readl(M3PM_SC_BASE_AO + 0x38), PWR_SRAM_CRG_REG + 0x10);
    writel(readl(M3PM_SC_BASE_AO + 0xe04), PWR_SRAM_CRG_REG + 0x14);
}

/* T32 trace int wakeup */
irqreturn_t trace_int_handler(int irq, void* data)
{
    printk("t32 int\n");
    return IRQ_HANDLED;
}
void pm_config_init(void)
{

    ddr_hit_addr = SHM_BASE_ADDR+SHM_OFFSET_MDMA9_PM_BOOT-4;/* todo ddr addr */

    sys_bak_data_init();
    (void)request_irq(M3_CM3_DBG_WAKE_INT, trace_int_handler, 0, "cm3_debug_wake", 0);/*lint !e713*/
    /* wakeup src clean*/
    /*m3*/
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL16);
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL17);
    /*appa9*/
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL24);
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL25);
    /*mdma9*/
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL30);
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL31);
}

static void pm_config_init_buck3off(void)
{
    u32 tmp = 0;

    /* 3 */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp |= 0x2C00400;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 4 tcxo*/
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL2);
    tmp &= 0xA00000;
       tmp = tmp | 0x1404FFFF;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL2);

    /* 5 */
    writel(0x1FFF0FFF, M3PM_SC_BASE_AO + PWR_CTRL8);

    /* 6 m3 tcm */
    writel(0x21332, M3PM_SC_BASE_AO + PWR_CTRL12);
    writel(0x21335, M3PM_SC_BASE_AO + PWR_CTRL38);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL10);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL11);

    /* 7 pmu pwr down, close clk */
    writel(0x10FE1, M3PM_SC_BASE_AO + PWR_CTRL13);

    /* 8 peri power down */
    if(1 == gPmNvSt.peridown_flag)
    {
        writel(0x20000000, M3PM_SC_BASE_AO + PWR_CTRL9);
    }
}

u32 pm_stamp_value(void)
{
    return bsp_get_slice_value();
}


/*lint -save -e737*/
void pm_mcu_buck3off_pdown(void)
{
    u32 tmp = 0;
    u32 i = 0;

    /* 9 todo */
    for(i = 0; i < 8; i++)
    {
        gPmBakeupSt.u32NvicEnable[i] = NVIC->ISER[i];
        NVIC->ICER[i] = 0xFFFFFFFF;
    } 

    /* ����Դδ���� */
#if 1
    for(i = 0; i < DS_IRQ_NUM; i++)
    {
        enable_irq(pm_deepsleep_irq[i]);
    }
#endif
    /* 10 bak for power down */
    
    ios_suspend();
    m3_pm_stamps->buck3off.after_ios_suspend = pm_stamp_value();
    sys_reg_bak();
    m3_pm_stamps->buck3off.after_sysreg_suspend = pm_stamp_value();
    (void)sram_bak();
    m3_pm_stamps->buck3off.after_sram_suspend = pm_stamp_value();
    
    clk_bak.crg_dfs1_ctrl1 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    clk_bak.crg_dfs1_ctrl2 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    clk_bak.crg_dfs1_ctrl3 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);
    clk_bak.pd_crg_clkdiv2 = readl(M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    
    /* 11 ddr  pdown */
    ddr_hit_set();
    v722_porting_mddrc_save();
    pm_ddr_porting_in_sref();

    m3_pm_stamps->buck3off.after_ddr_sref = pm_stamp_value();

    /* 12  ddr_io normal_io retention */
    writel((0x1FF<<16), M3PM_SC_BASE_AO + PWR_CTRL4);

    if(gPmCountSt.u32PwrRegbakFlag)
    {
        pm_mcu_bakeup_debug();
    }

    m3_pm_stamps->buck3off.before_sram_retention= pm_stamp_value();

    set_cpu_dbg_suspend(cm3_debug_suspend_bit,1);

    /* 13 slow */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x2;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
    do
    {
        tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp = (tmp >> 3)&0x7;
    }while(tmp != 0x2);
    /* 14 */
    writel(0x0, M3PM_SC_BASE_PD +  + PD_CRG_CLKDIV2);

    /* 15 cpu sleep */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 16 dummy: to make sure */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);

    ISB();

    /* wfi */
    if(!gPmCountSt.u32SleepWithoutWfiFlag)
    WFI();
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
}

void pm_mcu_buck3off_pup(void)
{
    u32 tmp = 0;
    u32 tmp1 = 0;
    u32 i = 0;
    u32 arm_boot_type = 0;

    /* 1 a9 pll */
    writel(clk_bak.crg_dfs1_ctrl1, M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    writel(clk_bak.crg_dfs1_ctrl2, M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    writel(clk_bak.crg_dfs1_ctrl3, M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);

    /* new added */
    writel( 0x2C, M3PM_SC_BASE_PD + CRG_DFS5_CTRL3);
    
    /* 2 clk div */
    writel(clk_bak.pd_crg_clkdiv2, M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    /* 3 normal */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x4;
    do{
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = (tmp1 & 0x78) >> 3;
    }while((tmp1 != 0x4));

    m3_pm_stamps->buck3off.after_sram_out_retention= bsp_get_slice_value();
    
    set_cpu_dbg_suspend(cm3_debug_suspend_bit,0);

    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_0);

    slice_resume(); /* udelay timer init , needed by ddr pup */

    /* 4 check arm_boot_type */
    arm_boot_type = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    if(arm_boot_type & (0x1UL<<30))
    {
        m3_pm_stamps->buck3off.before_ddr_restore = pm_stamp_value();
        /* 5 restore ddr */
        fpga_emu_ddr_pup();
        /* 10 clear arm_boot_type */
        arm_boot_type &= ~(0x1UL<<30);
        writel(arm_boot_type, M3PM_SC_BASE_AO + PWR_CTRL0);
        m3_pm_stamps->buck3off.after_ddr_restore = pm_stamp_value();
    }
    else
    {
        m3_pm_stamps->buck3off.no_boot_not_ddr_restore= pm_stamp_value();
        m3_pm_stamps->buck3off.no_sm_cnt++;

        /* 6 ddr io */
        writel((0x1<<24), M3PM_SC_BASE_AO + PWR_CTRL5);
        
        /* 7 XXX */
        
        /* 8 ddr out sref */
        pm_ddr_porting_out_sref();

        m3_pm_stamps->buck3off.after_ddr_out_sref = pm_stamp_value();
        pm_debug_udelay(5,gNvDrxDelaySt.lpm3_2);

        /*9 reset ctl_clkdiv */
        writel(1<<18, 0x90000360);
        writel(1<<18, 0x90000364);
        ddr_hit_test();
    }

    m3_pm_stamps->buck3off.before_sysreg_resume= pm_stamp_value();
    sys_reg_restore();
    m3_pm_stamps->buck3off.before_sram_resume= pm_stamp_value();
    (void)sram_restore();

    m3_pm_stamps->buck3off.after_ios_resume = pm_stamp_value();

    /* 11 ios resume */
    ios_resume();
    m3_pm_stamps->buck3off.after_rf_resetn = pm_stamp_value();

    /* 12 normal io out retention */
    writel((0xFF<<16), M3PM_SC_BASE_AO + PWR_CTRL5);

    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_3);

    pm_mcu_wakeup_debug();

    pm_set_bbpwakeup_flag();

    /* 13 */
    for(i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ISER[i] = gPmBakeupSt.u32NvicEnable[i];
    }
    m3_pm_stamps->buck3off.buck3off_pup_end = pm_stamp_value();

}

static void pm_config_init_buck3on(void)
{
    u32 tmp = 0;

    /* 3 */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp |= 0x2C00400;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 4 tcxo*/
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL2);
    tmp &= 0xA00000;
       tmp = tmp | 0x1404FFFF;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL2);

    /* 5 */
    writel(0x1FFF0FFF, M3PM_SC_BASE_AO + PWR_CTRL8);

    /* 6 m3 tcm */
    writel(0x21332, M3PM_SC_BASE_AO + PWR_CTRL12);
    writel(0x21335, M3PM_SC_BASE_AO + PWR_CTRL38);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL10);
    writel(0x1FFFFFF, M3PM_SC_BASE_AO + PWR_CTRL11);

    /* 7 pmu pwr down, close clk */
    writel(0x10FE1, M3PM_SC_BASE_AO + PWR_CTRL13);

    /* 7 pmu  NO pwr down, but close clk */
    writel(0x0, M3PM_SC_BASE_AO + PWR_CTRL13);

    /* 8 peri power down */
    if(1 == gPmNvSt.peridown_flag)
    {
        writel(0x20000000, M3PM_SC_BASE_AO + PWR_CTRL9);
    }

}


void pm_mcu_buck3on_pdown(void)
{


    u32 tmp = 0;
    u32 i = 0;

    /* 10 close pll DSP/HIFI/USB/BBP  */
#if 0
    //todo: should be closed in a/c core  or not
/* DSP */
    tmp = readl(M3PM_SC_BASE_PD + CRG_DFS2_CTRL3);
    tmp |= (~0x1);
    writel(tmp, M3PM_SC_BASE_AO + CRG_DFS2_CTRL3);
    /* HIFI */
    tmp = readl(M3PM_SC_BASE_PD + CRG_DFS3_CTRL3);
    tmp |= (~0x1);
    writel(tmp, M3PM_SC_BASE_AO + CRG_DFS3_CTRL3);
    /* PERI USB */
    tmp = readl(M3PM_SC_BASE_PD + CRG_DFS6_CTRL3);
    tmp |= (~0x1);
    writel(tmp, M3PM_SC_BASE_AO + CRG_DFS6_CTRL3);
    /* PERI  bbp pll in ABB, config ABB_regs*/
#endif

    /* 9 todo */
    for(i = 0; i < 8; i++)
    {
        gPmBakeupSt.u32NvicEnable[i] = NVIC->ISER[i];
        NVIC->ICER[i] = 0xFFFFFFFF;
    }

    /* ����Դδ���� */
    for(i = 0; i < DS_IRQ_NUM; i++)
    {
        enable_irq(pm_deepsleep_irq[i]);
    }
    
    /* 10 bak for power down */
    
    ios_suspend();
    m3_pm_stamps->buck3on.after_gpio_suspend = pm_stamp_value();
    sys_reg_bak();
    m3_pm_stamps->buck3on.after_sysreg_suspend = pm_stamp_value();
    (void)sram_bak();
    m3_pm_stamps->buck3on.after_sram_suspend = pm_stamp_value();
    
    clk_bak.crg_dfs1_ctrl1 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    clk_bak.crg_dfs1_ctrl2 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    clk_bak.crg_dfs1_ctrl3 = readl(M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);
    clk_bak.pd_crg_clkdiv2 = readl(M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    
    /* 13  ddr pdown  */
    ddr_hit_set();
    v722_porting_mddrc_save();
    pm_ddr_porting_in_sref();

    m3_pm_stamps->buck3on.after_ddr_sref = pm_stamp_value();

    if(gPmCountSt.u32PwrRegbakFlag)
    {
        pm_mcu_bakeup_debug();
    }

    m3_pm_stamps->buck3on.before_sram_retention= pm_stamp_value();

    set_cpu_dbg_suspend(cm3_debug_suspend_bit,1);
            
    /* 13 slow */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x2;
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
    do
    {
        tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp = (tmp >> 3)&0x7;
    }while(tmp != 0x2);
    /* 14 */
    writel(0x0, M3PM_SC_BASE_PD +  + PD_CRG_CLKDIV2);

    /* 15 cpu sleep */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

    /* 16 dummy: to make sure */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);

    ISB();

    /* wfi */
    if(!gPmCountSt.u32SleepWithoutWfiFlag)
    WFI();
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
}

void pm_mcu_buck3on_pup(void)
{

    u32 tmp = 0;
    u32 tmp1 = 0;
    u32 i = 0;
    u32 arm_boot_type = 0;
    //__asm__ __volatile__ ("b .");  // debug for pmu ldo27 overload

    /* 1 a9 pll */
    writel(clk_bak.crg_dfs1_ctrl1, M3PM_SC_BASE_PD + CRG_DFS1_CTRL1);
    writel(clk_bak.crg_dfs1_ctrl2, M3PM_SC_BASE_PD + CRG_DFS1_CTRL2);
    writel(clk_bak.crg_dfs1_ctrl3, M3PM_SC_BASE_PD + CRG_DFS1_CTRL3);
    
    /* new added --- todo, ����buck3on���Բ���Ҫ - guoliang */
    writel( 0x2C, M3PM_SC_BASE_PD + CRG_DFS5_CTRL3);
    
    /* 2 clk div */
    writel(clk_bak.pd_crg_clkdiv2, M3PM_SC_BASE_PD + PD_CRG_CLKDIV2);
    /* 3 normal */
    tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    tmp &= (~0x7);
    tmp |= 0x4;
    do{
    writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp1 = (tmp1 & 0x78) >> 3;
    }while((tmp1 != 0x4));

    m3_pm_stamps->buck3off.after_sram_out_retention= bsp_get_slice_value();
    
    set_cpu_dbg_suspend(cm3_debug_suspend_bit,0);

    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_0);

    slice_resume(); /* udelay timer init , needed by ddr pup */

    /* 4 check arm_boot_type */
    arm_boot_type = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
    if(arm_boot_type & (0x1UL<<30))
    {
        m3_pm_stamps->buck3on.before_ddr_restore = pm_stamp_value();
        /* 5 ddr power up */
        fpga_emu_ddr_pup();

        m3_pm_stamps->buck3on.after_ddr_restore = pm_stamp_value();
        /* 10 clear arm_boot_type */
        arm_boot_type &= ~(0x1UL<<30);
        writel(arm_boot_type, M3PM_SC_BASE_AO + PWR_CTRL0);
    }
    else
    {
        m3_pm_stamps->buck3on.no_boot_not_ddr_restore= pm_stamp_value();
        m3_pm_stamps->buck3on.no_sm_cnt++;

        /* 6 ddr io */
        writel((0x1<<24), M3PM_SC_BASE_AO + PWR_CTRL5);
        /* 7 wait pll lock */
       
        /* 8 ddr out sref */
        pm_ddr_porting_out_sref();
        
        m3_pm_stamps->buck3on.after_ddr_out_sref = pm_stamp_value();
        pm_debug_udelay(5,gNvDrxDelaySt.lpm3_2);
        
        /*9 reset ctl_clkdiv */
        writel(1<<18, 0x90000360);
        writel(1<<18, 0x90000364);
        ddr_hit_test();

    }

    m3_pm_stamps->buck3on.before_sysreg_resume = pm_stamp_value();
    sys_reg_restore();
    m3_pm_stamps->buck3on.after_sysreg_resume = pm_stamp_value();
    (void)sram_restore();
    m3_pm_stamps->buck3on.after_sram_resume = pm_stamp_value();

    /* 11 ios resume */
    ios_resume();
    m3_pm_stamps->buck3on.after_gpio_resume = pm_stamp_value();

    /* 12 normal io out retention no need */
    /* writel((0xFF<<16), M3PM_SC_BASE_AO + PWR_CTRL5);*/

    pm_debug_udelay(5,gNvDrxDelaySt.lpm3_3);

    pm_mcu_wakeup_debug();

    pm_set_bbpwakeup_flag();

    /* 11 */
    for(i = 0; i < 8; i++)
    {
        NVIC->ICER[i] = 0xFFFFFFFF;
        NVIC->ISER[i] = gPmBakeupSt.u32NvicEnable[i];
    }
    m3_pm_stamps->buck3on.buck3on_pup_end = pm_stamp_value();


}

static void pm_mcu_bakeup_debug(void)
{
// todo
}

static void pm_mcu_wakeup_debug(void)
{
// todo
}

/*lint -restore +e737*/
static void pm_mcu_process(void)
{
    u32 buck3offflag = ACORE_BUCK3_ONOFF_FLAG | CCORE_BUCK3_ONOFF_FLAG;
    s32 ret = 0;

    pm_dfs_bak();
    m3_pm_stamps->after_dfs_bak = pm_stamp_value();

    if((1 == gPmNvSt.buck3off_flag)&&(buck3offflag == 0))
    {
        m3_pm_stamps->buck3off.buck3off_cnt++;
        m3_pm_stamps->buck3off.in_buck3off_branch = pm_stamp_value();
        
        ret = dpm_suspend_buck3off();
        
        m3_pm_stamps->buck3off.after_dpm_suspend_buck3off= pm_stamp_value();
        
        if(ret == 0 )
        {
            pm_config_init_buck3off();
            m3_pm_stamps->buck3off.after_buck3off_init = pm_stamp_value();
            pm_mcu_buck3off_pdown();
            pm_mcu_buck3off_pup();

            ret = dpm_resume_buck3off() ;
            m3_pm_stamps->buck3off.after_dpm_resume_buck3off= pm_stamp_value();
            if(ret != 0 )
            {
                __asm__ __volatile__ ("b .");
            }
                pm_debug_udelay(5,gNvDrxDelaySt.lpm3_4);
        }
        else
        {
            __asm__ __volatile__ ("b .");
        }
    }
    else
    {
        m3_pm_stamps->buck3on.buck3on_cnt++;
        m3_pm_stamps->buck3on.in_buck3on_branch = pm_stamp_value();
        
        pm_config_init_buck3on();
        pm_mcu_buck3on_pdown();
        pm_mcu_buck3on_pup();
    }
}

/*lint --e{718,732,746}*/
void pm_normal_wfi(void)
{
    int irqlock;
    u32 sleeptime = 0;
    u32 tc = 0;
    u32 tmp = 0;
    u32 btime = 0;
    u32 ftime = 0;

    local_irq_save(irqlock);

    tc = rt_suspend();
    if(tc>1)
    {
        gPmCountSt.u32NormalWfiTimes++;
        m3_pm_stamps->wfi_cnt = gPmCountSt.u32NormalWfiTimes;
        btime = pm_stamp_value();

        /* pwr_ctrl0 bit25 bit26 set 0*/
        /*
        tmp = readl( M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp &= ~0x6000000;
        writel(tmp,  M3PM_SC_BASE_AO + PWR_CTRL0);
            */
        /* pwr_ctrl0 bit25 set 1*/
        tmp = readl( M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp |= 0x2000000;
        writel(tmp,  M3PM_SC_BASE_AO + PWR_CTRL0);

/* pwr_ctrl0 bit25 bit26 set 0*/
tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
tmp &= ~0x6000000;
writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);



        /* m3 will be wakeup by debug when connected to emulator */
        /* disable irq can only stop irq respond*/
        set_cpu_dbg_suspend(cm3_debug_suspend_bit,1); 
        /*enable_irq(M3_CM3_DBG_WAKE_INT);*/
        
        WFI();
/*
        disable_irq(M3_CM3_DBG_WAKE_INT);
        clear_pending_irq(M3_CM3_DBG_WAKE_INT);
*/
    set_cpu_dbg_suspend(cm3_debug_suspend_bit,0);

/* pwr_ctrl0 bit25 bit26 set 1*/
tmp = readl(M3PM_SC_BASE_AO + PWR_CTRL0);
tmp |= 0x6000000;
writel(tmp, M3PM_SC_BASE_AO + PWR_CTRL0);

        /* pwr_ctrl0 bit25 bit26 set 1
        tmp = readl( M3PM_SC_BASE_AO + PWR_CTRL0);
        tmp |= 0x6000000;
        writel(tmp,  M3PM_SC_BASE_AO + PWR_CTRL0);
        */

        ftime = pm_stamp_value();
        sleeptime = (ftime - btime)* 1000 / PM_MCU_TIMER_CLK;
    }
    else
    {
        sleeptime = 0;
    }
    rt_resume(sleeptime);

    local_irq_restore(irqlock);

}

void pm_deepsleep(void)
{
    int irqlock;
    u32 sleeptime = 0;
    u32 tc = 0;
    s32 tmp = 0;
    u32 btime = 0;
    u32 ftime = 0;

    local_irq_save(irqlock);
    
    if(!debug_can_sleep())
    {
        local_irq_restore(irqlock);
        return;
    }
    
    m3_pm_stamps->before_dpm_suspend = pm_stamp_value();
    tmp = dpm_suspend();
    m3_pm_stamps->after_dpm_suspend = pm_stamp_value();
    if(tmp == DPM_OK)
    {
        gPmSt.u32SleepFlag = 1;
        tc = rt_suspend();
        if(tc>1)
        {
            gPmCountSt.u32DeepSleepTimes++;
            m3_pm_stamps->deepsleep_cnt = gPmCountSt.u32DeepSleepTimes;
            btime = pm_stamp_value();

            pm_mcu_process();

            ftime = pm_stamp_value();
            sleeptime = (ftime - btime)* 1000 / PM_MCU_TIMER_CLK;
        }
        else
        {
            sleeptime = 0;
        }
        rt_resume(sleeptime);
        gPmSt.u32SleepFlag = 0;
        m3_pm_stamps->before_dpm_resume = pm_stamp_value();

        tmp = dpm_resume();
        m3_pm_stamps->after_dpm_resume = pm_stamp_value();

        pm_debug_udelay(5,gNvDrxDelaySt.lpm3_4);

        if(tmp != DPM_OK)
        {
            gPmErrorSt.u32DpmResumeErrTimes++;
            __asm__ __volatile__ ("b ."); /*err not allowed*/
        }
    }
    else
    {
        gPmErrorSt.u32DpmSuspendErrTimes++;
        m3_pm_stamps->dpm_fail_cnt = gPmErrorSt.u32DpmSuspendErrTimes;
    }

    local_irq_restore(irqlock);

}

void idle_task(void)
{

    int irqlock;

    local_irq_save(irqlock);

    bsp_wdt_feed();

    //udelay(2000); /* todo for test */

    /* deepsleep 0ͶƱ˯�ߣ�1����˯�� */
    if((!(gPmSt.u32VoteMap & gPmSt.u32VoteMask)) && (1 == gPmNvSt.deepsleep_flag)
       && (*(u32*)(SRAM_BASE_ADDR+SRAM_OFFSET_RTT_SLEEP_FLAG) != 1))
    {
        pm_deepsleep();
    }
    else if((sys_initial==1) && ((1 == gPmNvSt.normalwfi_flag)))
    {
        pm_normal_wfi();
    }
    
    local_irq_restore(irqlock);
}
#if 0
void pm_print_wsrc(void)
{
    u32 i = 0;
    u32 j = 0;
    u32 tmp = 0;

    printk("ISER 0x%x 0x%x 0x%x 0x%x\n", NVIC->ISER[0], NVIC->ISER[1], NVIC->ISER[2], NVIC->ISER[3]);

    for(j = 0; j < 4; j++)
    {
        printk("wsrc num%d:",j);
        tmp = readl(PWR_CTRL16+j*4);
        for(i = 0; i < 32; i++)
        {
            if(tmp & ((u32)0x1<<i))
            {
                printk(" %d ",i+j*32+16);
            }
        }
        printk("\n");
    }

    pm_print_wakeup_debug();
}

static void pm_print_wakeup_debug(void)
{
    u32 i = 0;
    u32 j = 0;
    u32 tmp = 0;

    if(gPmCountSt.u32WakeupDebugFlag)
    {
        for(j = 0; j < 4; j++)
        {
            printk("wakeup num%d:",j);
            tmp = readl(PWR_SRAM_WAKEUP_REG+m3_record_num*0x20+0x10+j*4);
            for(i = 0; i < 32; i++)
            {
                if(tmp & ((u32)0x1<<i))
                {
                    printk(" %d ",i+j*32+16);
                }
            }
            printk("\n");
        }
    }
}
#endif
static void pm_set_peri_down(u32 flag)
{
    if(flag)
    {
        writel(0x20000000, PWR_CTRL9);
    }
    else
    {
        writel(0x40000000, PWR_CTRL9);
    }
}

void pm_set_debug(u32 type, u32 flag)
{
    switch(type)
    {
        case 1:
            gPmNvSt.normalwfi_flag = (BSP_U8)flag;
            break;
        case 2:
            gPmNvSt.deepsleep_flag = (BSP_U8)flag;
            break;
        case 3:
            if(0 == gPmNvSt.buck3off_flag)
            {
                gPmNvSt.peridown_flag = (BSP_U8)flag;
                pm_set_peri_down(flag);
            }
            else
            {
                printk("buckoff\n");
            }
            break;
        case 4:
            gPmCountSt.u32PwrRegbakFlag = flag;
            break;
        case 5:
            gPmCountSt.u32WakeupDebugFlag = flag;
            break;
        case 6:
            gPmCountSt.u32PrintIrqWsrcFlag = flag;
            break;
        case 7:
            gPmCountSt.u32SleepWithoutWfiFlag= flag;
            break;
        case 8:
            gPmCountSt.u32DebugCanSleepTime= flag;
            break;
        default:
            printk("inputErr\n");
            break;
    }
}


