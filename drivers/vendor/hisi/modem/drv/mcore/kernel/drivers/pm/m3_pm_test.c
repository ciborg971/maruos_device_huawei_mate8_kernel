/*----------------------------------------------------------------------------
 *      balongv7r2 m3 pm test
 *----------------------------------------------------------------------------
 *      Name:    m3_pm_test.c
 *      Purpose: RTX example program
 *----------------------------------------------------------------------------
 *      This code is part of balongv7r2 PWR.
 *---------------------------------------------------------------------------*/

#include <ARMCM3.h>
#include "console.h"
#include "printk.h"

#include "osl_types.h"
#include "osl_bio.h"
#include "osl_irq.h"

#include "m3_pm.h"
#include "pm_api.h"
#include "mdrv_ipc.h"
#include "ipc_balong.h"
#include "drv_nv_def.h"
#include "drv_nv_id.h"
#include "bsp_nvim.h"
#include "m3_cpufreq.h"
#include "bsp_dsp.h"
#include "bsp_icc.h"
#include "bsp_hardtimer.h"
#include "wdt_balong.h"

#include <bsp_softtimer.h>

void m3_pm_timer_isr(void);


struct softtimer_list pm_test_softtimer ={   
    .func = (softtimer_func)m3_pm_timer_isr,
   .para = 0,
   .timeout = 2000,
   .wake_type = SOFTTIMER_WAKE,
  
    };
u32 pm_test_inited = 0;
void set_pm_test_timer(u32 timeout)
{
    if(0==pm_test_inited)
    {
        bsp_softtimer_create(&pm_test_softtimer);
        bsp_softtimer_add(&pm_test_softtimer);
        pm_test_inited = 1;
    }
    else
    {
        bsp_softtimer_delete(&pm_test_softtimer);
        bsp_softtimer_modify(&pm_test_softtimer,timeout);
        bsp_softtimer_add(&pm_test_softtimer);
    }
}

unsigned int pm_timer_cnt = 0;
void m3_pm_timer_isr(void)
{
    bsp_softtimer_add(&pm_test_softtimer);
    pm_timer_cnt++;
    printk(" pm_timer_cnt %d \n",pm_timer_cnt);
}

#include <soc_memmap.h>
#define  IPC_CPU_RAW_INT_M3   0x420

/* c->m send ipc_int  addr & bit  */
#define  PM_C2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
#define  PM_C2M_IPC_BIT        (0x1<<IPC_MCU_INT_SRC_CCPU_PD)
/* a->m send ipc_int  addr & bit  */
#define  PM_A2M_IPC_ADDR       (HI_IPCM_REGBASE_ADDR+IPC_CPU_RAW_INT_M3)
#define  PM_A2M_IPC_BIT        (0x1<<IPC_MCU_INT_SRC_ACPU_PD)

void m3_send_a_ipc(void)
{
    writel(PM_A2M_IPC_BIT, PM_A2M_IPC_ADDR);
}
void m3_send_c_ipc(void)
{
    writel(PM_C2M_IPC_BIT, PM_C2M_IPC_ADDR);
}





/*
u32DebugCanSleepTime  深睡次数控制功能
0 表示正常睡眠
-1 表示不睡眠
其他 表示正常睡眠次

*/
T_PM_COUNT_ST gPmCountSt;

u32 debug_can_sleep(void)
{
    if(0 == gPmCountSt.u32DebugCanSleepTime)
    {
        return 1;
    }
    else
    {
        if((u32)(-1) == gPmCountSt.u32DebugCanSleepTime)
        {
            return 0;
        }
        else if( 1 == gPmCountSt.u32DebugCanSleepTime)
        {
            gPmCountSt.u32DebugCanSleepTime = -1;
            return 1;
        }
        else
        {
            gPmCountSt.u32DebugCanSleepTime--;
            return 1;
        }
    }
}

        
