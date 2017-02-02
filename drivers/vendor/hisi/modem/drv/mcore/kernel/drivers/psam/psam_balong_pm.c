/*************************************************************************
*   ��Ȩ����(C) 1987-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  psam_balong_pm.c
*
*   ��    �� :  longyi
*
*   ��    �� :  psam�ĵ͹��Ľӿڣ�������m3
*
*   �޸ļ�¼ :  2014��09��15��v1.00 longyi ����
*
*************************************************************************/
#include <hi_psam.h>
#include <osl_common.h>
#include <libfdt.h>

#define BIT(x)						(1 << (x))
#define PSAM_SRST_BIT				BIT(0)
#define PSAM_IDLE_BIT				BIT(1)

#define ERROR						(-1)
#define PSAM_BAK_BASE_REGS_CNT		19

void *g_psam_reg_base = NULL;
//������д��Ϊ����Ӧ����IPF ��m3����ռ����v7����share ddr�ռ�
__ao_data unsigned int g_u32_psam_setting_bak_space[PSAM_BAK_BASE_REGS_CNT];
__ao_data unsigned int* g_u32_psam_setting_bak_addr = g_u32_psam_setting_bak_space;


__ao_data unsigned int g_psam_setting_table[] =
{
	HI_PSAM_CONFIG_OFFSET,
	HI_PSAM_INT0_MASK_OFFSET,
	HI_PSAM_INT1_MASK_OFFSET,
	//cipher
	HI_PSAM_CRDQ_CTRL_OFFSET,
	//restore by cipher call psam func(bsp_psam_cipher_ch_srst())
#if 0
	HI_PSAM_CBDQ_CONFIG_OFFSET,
	HI_PSAM_CBDQ_BADDR_OFFSET,
	HI_PSAM_CBDQ_SIZE_OFFSET,
	HI_PSAM_CBDQ_WPTR_ADDR_OFFSET,
	HI_PSAM_CRDQ_RPTR_ADDR_OFFSET,
#endif
	//ibdq
	HI_PSAM_IBDQ_BADDR_OFFSET,
	HI_PSAM_IBDQ_SIZE_OFFSET,
	HI_PSAM_IBDQ_WPTR_ADDR_OFFSET,
	HI_PSAM_IBDQ_RPTR_ADDR_OFFSET,
	HI_PSAM_IBDQ_RPTR_TIMER_OFFSET,
	HI_PSAM_IBDQ_PKT_CNT_OFFSET,
	//lbdq
	HI_PSAM_LBDQ_BADDR_OFFSET,
	HI_PSAM_LBDQ_SIZE_OFFSET,
	//adq
	HI_PSAM_ADQ_CTRL_OFFSET,
	HI_PSAM_ADQ0_BASE_OFFSET,
	HI_PSAM_ADQ0_RPTR_OFFSET, 
	HI_PSAM_ADQ0_WPTR_OFFSET, 
	HI_PSAM_ADQ1_BASE_OFFSET,
	HI_PSAM_ADQ1_WPTR_OFFSET,
	HI_PSAM_ADQ1_RPTR_OFFSET
};


int	bsp_psam_init(void)
{
    struct device_node *node;
	node = of_find_compatible_node(NULL, NULL, "hisilicon,psam_balong_m3");
	if (!node)
	{
		//printk("psam node not found!\n");
		return ERROR;
	}

	g_psam_reg_base = of_iomap(node, 0);
	if (NULL == g_psam_reg_base)
	{
		//printk("psam iomap failed.\r\n");
		return ERROR;
	}
	return 0;
}


static unsigned int psam_idle(void)
{
	unsigned int status;
	status = readl((unsigned int)g_psam_reg_base + HI_PSAM_SRST_OFFSET);
	status &= PSAM_IDLE_BIT;
	
	return status;
}


static int psam_sw_srst(void)
{
	unsigned int count = 10000;
	unsigned int reg_v = 1;

	writel(reg_v, (unsigned int)g_psam_reg_base + HI_PSAM_SRST_OFFSET);
	while(reg_v & PSAM_SRST_BIT){
		reg_v = readl((unsigned int)g_psam_reg_base + HI_PSAM_SRST_OFFSET);
		if(count == 0){
			return ERROR;
		}
		count--;
	}
	return 0;
}


int psam_bakup_reg(void)
{
    unsigned int* u32_addr = NULL;
    unsigned int i = 0;
    unsigned int u32_total = 0;

    /* idle */  	    
    if(psam_idle() != PSAM_IDLE_BIT)
    {
        return ERROR;
    }

	/*ad ����disable ��ΪadԤȡû�иı�ad�Ķ�ָ��*/
    /* �����Ҫ�ļĴ��� */
    u32_total = sizeof(g_psam_setting_table)/sizeof(unsigned int);
    u32_addr = g_u32_psam_setting_bak_addr;
    
    for(i=0; i<u32_total; i++)
    {
        *u32_addr = readl((unsigned int)g_psam_reg_base + g_psam_setting_table[i]);
        u32_addr ++;
    }

    return 0;
}
void psam_restore_reg(void)
{
    unsigned int* u32_addr = NULL;
    unsigned int i = 0;
    unsigned int u32_total = 0;

	writel(0, (unsigned int)g_psam_reg_base + HI_PSAM_EN_OFFSET);
//reset psam
    psam_sw_srst();

//restore registers
    u32_total = sizeof(g_psam_setting_table)/sizeof(unsigned int);
    u32_addr = g_u32_psam_setting_bak_addr;

    for(i=0; i<u32_total; i++)
    {
        writel(*u32_addr, (unsigned int)g_psam_reg_base + g_psam_setting_table[i]);        
        u32_addr ++;
    }

//psam enable after restore all psam registers
    writel(1, (unsigned int)g_psam_reg_base + HI_PSAM_EN_OFFSET);        
}

