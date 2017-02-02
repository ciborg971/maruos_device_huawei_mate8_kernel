#include "product_config.h"
#include <osl_thread.h>
#include <dma-mapping.h>
#include "sys_hdlc.h"
#include "hdlc_for_bbit.h"
#include "osl_bio.h"
#include "baseaddr.h"
#include <sys_bus_pressure.h>


#define STRESS_TEST_BYTE 1024

UINT32 src_addr_hdlc = 0;
UINT32 des_addr_hdlc = 0;
struct device hdlc_dev;
void * sys_bus_sysctrl_crg_addr;
void * sys_bus_hdlc_base_addr;


int g_hdlc_stress_start = 0;

int hdlc_test(void)
{
	sys_mem_clr(src_addr_hdlc, 0x400);  //clear ipf source data memory
    sys_mem_clr(des_addr_hdlc, 0x400);   //clear ipf destination data memory
    return hdlcv200_frm_def_test_bbit(src_addr_hdlc, des_addr_hdlc);
}

int sys_hdlc_test(void)
{
    int ret = 0;

    if (!(src_addr_hdlc && des_addr_hdlc))
    {
        printk("cacheDmaMalloc Fail!\n");
        return ERROR;
    }
    
    ret = hdlc_test();    
    if(ret){
        printk("sys_hdlc_test fail\n");
        ret = 1;
    }
    return ret;

}
u32 count = 0;
int g_delay = 2;

void sys_hdlc_routine(void)
{
	while(g_hdlc_stress_start)
	{
		sys_hdlc_test();
		osl_task_delay(g_delay);
		count++;
	}
	return ;
}
OSL_TASK_ID  sys_hdlc_stress_test_task_id = 0;
void sys_hdlc_start(struct master* master)
{
	//UINT32 reg = 0x1F80000;  
	/*?a?¡ä??*/
	int ret = 0;
    dma_addr_t src_dma_addr_hdlc;
    dma_addr_t des_dma_addr_hdlc;
	
	g_delay = 2;

    hdlc_dev.coherent_dma_mask = ~0;

	src_addr_hdlc   = (UINT32)dma_alloc_coherent(NULL, STRESS_TEST_BYTE, &src_dma_addr_hdlc, GFP_KERNEL);
	des_addr_hdlc   = (UINT32)dma_alloc_coherent(NULL, STRESS_TEST_BYTE, &des_dma_addr_hdlc, GFP_KERNEL);
	g_hdlc_stress_start = 1;

    /*task_priority = 10;*/
	ret = osl_task_init ("guTask", 10, 80000, (OSL_TASK_FUNC)sys_hdlc_routine, NULL, &sys_hdlc_stress_test_task_id);
	if(ret == -1)
	{
		printk("sys_hdlc_routine fail.\n");
	}
    printk("sys_hdlc_routine start finish.\n");	
}

void sys_hdlc_stop(struct master* master)
{
	g_hdlc_stress_start = 0;
}

void sys_hdlc_init(struct master* master)
{
    sys_bus_sysctrl_crg_addr = ioremap(HI_MODEM_SC_BASE_ADDR, 4096);
    sys_bus_hdlc_base_addr = ioremap(HI_HDLC_REGBASE_ADDR, 4096);
    
    master->start = sys_hdlc_start;
    master->stop = sys_hdlc_stop;
    master->record = NULL;
    master->report = NULL;
}



