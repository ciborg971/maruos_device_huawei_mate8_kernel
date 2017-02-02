
#include <osl_irq.h> /*lint !e537*/
#include <bsp_hardtimer.h>
#include <bsp_wakelock.h>
#include "sleep.h"
#include "cpuidle_balong.h"

/*task idle time, unit:slice*/
#ifdef CONFIG_CPUFREQ
extern unsigned int g_ulDfsCcpuIdleTime;
extern unsigned int  g_ulDfsCcpuIdleTime_long;
#else
unsigned int g_ulDfsCcpuIdleTime = 0;
unsigned int g_ulDfsCcpuIdleTime_long = 0;
#endif

/*WFI enter function*/
static void hi6930_enter_idle(void)
{
	cpu_enter_idle();
	return;
}


static int (*idle_go_deepsleep)(void) = NULL;
void cpuidle_set_deepsleep_ops(int (*go_deepsleep)(void))
{
    idle_go_deepsleep = go_deepsleep;
}
void cpuidle_idle_management(void)
{
     /* go deepsleep if it's registed, else enter idle*/
     unsigned int ret = 1;
     unsigned long flags = 0;
     unsigned int oldslice =0;
     unsigned int newslice =0;

     /* coverity[lock_acquire] */
     local_irq_save(flags);

     /*��ȡ����͹��ĵ�ʱ��*/
     oldslice = bsp_get_slice_value();
    /*lint --e{18,718,746}*/
     if(0 == has_wake_lock(0)){
             if(idle_go_deepsleep)
                    ret = idle_go_deepsleep();/*lint !e732*/
     }
     if(ret)
              hi6930_enter_idle();

	 /*��ȡ�˳�WFI��ʱ��*/
     newslice = bsp_get_slice_value();

     g_ulDfsCcpuIdleTime  += get_timer_slice_delta(oldslice, newslice);
     g_ulDfsCcpuIdleTime_long += get_timer_slice_delta(oldslice, newslice);

     local_irq_restore(flags);
     return;
}

void cpu_idle(void)
{
    while(1)
    {
        cpuidle_idle_management();
    }
}

