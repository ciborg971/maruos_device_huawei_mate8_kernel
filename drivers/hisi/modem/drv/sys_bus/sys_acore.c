#include <linux/of.h>
#include <linux/dma-mapping.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/delay.h>

#include <bsp_hardtimer.h>
#include <sys_bus_core.h>
#include <sys_bus_pressure.h>
#include <sys_acore.h>

struct sys_acore g_sys_acore;

void sys_acore_record(struct master* master)
{

}

void sys_acore_report(struct master* master)
{

}

void sys_acore_start(struct master* master)
{
    g_sys_acore.flag = 1;
}

void sys_acore_stop(struct master* master)
{
    g_sys_acore.flag = 0;
}

void sys_acore_thread(void)
{
    while(1)
    {
        if(g_sys_acore.flag)
        {
            memset((void*)g_sys_acore.dst, 0x0, g_sys_acore.size);
            memset((void*)g_sys_acore.src, 0xF, g_sys_acore.size);
            memcpy((void*)g_sys_acore.dst, (const void*)g_sys_acore.src, g_sys_acore.size);
        }
        mdelay(10);
    }
}

void sys_acore_init(struct master* master)
{
    dma_addr_t dma_handle;
    struct edma_cb* edma_cb = NULL;

    edma_cb = dma_alloc_coherent(NULL, acore_ddr_size, &dma_handle, \
              GFP_DMA|__GFP_WAIT);
    g_sys_acore.src = (u32)edma_cb;

    edma_cb = dma_alloc_coherent(NULL, acore_ddr_size, &dma_handle, \
              GFP_DMA|__GFP_WAIT);
    g_sys_acore.dst = (u32)edma_cb;

    g_sys_acore.size = acore_ddr_size;

	g_sys_acore.tsk =  kthread_run((void*)sys_acore_thread, (void*)NULL, "sys_acore");
	if (IS_ERR(g_sys_acore.tsk))
	{
		g_sys_acore.tsk = NULL;
		sys_bus_trace("cannot start sys_acore thread\n");
        return;
	}

    master->start = sys_acore_start;
    master->stop = sys_acore_stop;
    master->record = sys_acore_record;
    master->report = sys_acore_report;

    sys_bus_trace("ok\n");
}

