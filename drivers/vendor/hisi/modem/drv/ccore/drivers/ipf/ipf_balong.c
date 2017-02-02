/*************************************************************************
*   ��Ȩ����(C) 1987-2012, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  ipf_balong.c
*
*   ��    �� :  luting chendongyue
*
*   ��    �� :  ������Ҫ���IP���˽ӿں�����ʵ�����к����е�IP���˹���
*
*   �޸ļ�¼ :  2011��1��11��  v1.00  luting  ����
*                            2012��11��23��v2.00 chendongyue �޸�
*                            2013��3��29��v2.10 chendongyue �޸�
*                             2014��9��25��  v3.00 longyi�޸ģ�a/c�˲��
*************************************************************************/
/*lint -save -e429 -e529 -e534 -e550 -e650 -e661 -e715 -e537  -e737 -e539 -e574 -e239 -e438 -e701 -e740 -e958 -e451
-e64 -e732 -e740 -e801 -e830 -e530 -e775 -e414 -e525
*/

#ifdef __cplusplus
extern "C" {
#endif


#include <string.h>
#include <of.h>
#include <bsp_clk.h>
#include <bsp_hardtimer.h>
#include <osl_malloc.h>
#include <osl_irq.h>
#include <osl_thread.h>
#include "bsp_dpm.h"
#include "securec.h"
#include "bsp_pm_om.h"
#ifndef CONFIG_IPF_BACKUP_ON_LPM3
#include <bsp_ipc.h>
#endif
#include <bsp_ipf.h>
#include <bsp_psam.h>
#include <ipf_balong.h>
#include <bsp_dump.h>

#include <bsp_sysctrl.h>
#include <bsp_reset.h>

/*C������(��������)��ʾ*/
IPF_FORRESET_CONTROL_E* modem_reset_flag = NULL;
unsigned int crg_clkstat4_offset = 0;
unsigned int sc_stat26_offset = 0;
unsigned int reset_peri_crg[2] = {0,};

IPF_UL_S g_stIpfUl = {0};
IPF_DL_S g_stIpfDl = {0};

#ifdef CONFIG_PSAM
ipf_reg_s psam_para = {0};
#endif

/* ������Ϣ�ṹ�� */
struct ipf_ctx g_ipf_ctx;

#ifndef CONFIG_IPF_BACKUP_ON_LPM3
/*k3�͹��Ļָ����*/
unsigned int* ipf_acore_init_status = NULL;
unsigned int* ipf_ccore_init_status = NULL;
#endif

IPF_MATCH_INFO_S* g_pstExFilterAddr;
IPF_ID_S* g_stIPFExtFreeList = NULL;
IPF_ID_S* g_stIPFBasicFreeList = NULL;
IPF_ID_S* g_stIPFFreeList = NULL;
IPF_ID_S* g_stIPFHeadList = NULL;
IPF_FILTER_INFO_S g_stIPFFilterInfo[IPF_FILTER_CHAIN_MAX_NUM];
IPF_PWRCTL_FILTER_INFO_S g_stIPFPwrCtlFilterInfo[IPF_FILTER_CHAIN_MAX_NUM];
unsigned int g_u32IPFPwrCtlStart = 0;
unsigned int g_u32IpfSwitchInt = 0;
spinlock_t ipf_filter_spinlock;
spinlock_t ipf_dlbd_spinlock;
static spinlock_t ipf_reset_spinlock;
unsigned int g_filter_delay_time = 10;
static struct ipf_memblk_offset memblk_offset;

unsigned int ipf_base_addr_ccore;
static unsigned int irqnum_ccore;
static struct dts_param_c ipf_ccore_dts;

IPF_TIMESTAMP_INFO_S g_ipf_ul_timestamp_info;
unsigned int g_ipf_dl_start_enable;
#define IPF_GET_TIMESTAMP_INFO() (&g_ipf_ul_timestamp_info)
#define IPF_START_STAMP_ENABLE (g_ipf_dl_start_enable)

#ifdef CONFIG_CCORE_PM

/*****************************************************************************
* �� �� ��     : ipf_ul_dpm_prepare
*
* ��������  : dpm����׼������
*
* �������  : �豸ָ��
*   
* �������  : ��
*
* �� �� ֵ     : IPF_ERROR ʧ��
                            IPF_SUCCESS �ɹ�
*
* �޸ļ�¼  :2013��6��16��   �¶���  ����
*****************************************************************************/
static int ipf_ul_dpm_prepare(struct dpm_device *dev)
{
    unsigned int u32_ul_state;

    /* �ж�����IPF�Ƿ���� */
    u32_ul_state = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_STATE_OFFSET);

    if(u32_ul_state != IPF_CHANNEL_STATE_IDLE)
    {
        /*bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r IPF CHANNEL NOT IDLE! \n");*/
        return IPF_ERROR;
    }

    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��     : ipf_ul_suspend
*
* ��������  : dpm׮����
*
* �������  : �豸ָ��
*   
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :2013��6��16��   �¶���  ����
			2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			�޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
static int ipf_ul_suspend(struct dpm_device *dev)
{
#ifndef CONFIG_IPF_BACKUP_ON_LPM3

    unsigned long ipf_flags = 0;
	
    spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
    bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
    *ipf_ccore_init_status = IPF_PWC_DOWN;
    cache_sync();		
    bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
    spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);

#endif
    g_ipf_ctx.status->suspend++;
	return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��     : ipf_ul_resume
*
* ��������  : dpm׮����
*
* �������  : �豸ָ��
*   
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :2013��6��16��   �¶���  ����
*****************************************************************************/
static int ipf_ul_resume(struct dpm_device *dev)
{
	unsigned int status;
	status = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT0_OFFSET); 
	if (status & (IPF_UL_RPT_INT0 \
					| IPF_UL_TIMEOUT_INT0 \
					| IPF_UL_ADQ0_EPTY_INT0 \
					| IPF_UL_ADQ1_EPTY_INT0)) {
		g_ipf_ctx.status->resume_with_intr++;
	}
    g_ipf_ctx.status->resume++;
	return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��     : ipf_ul_dpm_complete
*
* ��������  : dpm׮����
*
* �������  : �豸ָ��
*   
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :2013��6��16��   �¶���  ����
*****************************************************************************/
static int ipf_ul_dpm_complete(struct dpm_device *dev)
{
	return IPF_SUCCESS;
}

struct dpm_device ipf_dpm_device={
	.device_name = "ipf_dpm",
	.prepare = ipf_ul_dpm_prepare,
	.suspend_late = NULL,
	.suspend = ipf_ul_suspend,
	.resume = ipf_ul_resume,
	.resume_early = NULL,
	.complete = ipf_ul_dpm_complete,
};

#endif


int bsp_ipf_srest(void)
{
	int tmp_cnt = 10000;
	ipf_writel(1, ipf_base_addr_ccore + HI_IPF_SRST_OFFSET);//��λ

	while(!ipf_readl(ipf_base_addr_ccore + HI_IPF_SRST_STATE_OFFSET)){
		tmp_cnt--;
		if(!tmp_cnt){
			return -1;
		}
	}	
	ipf_writel(0, ipf_base_addr_ccore + HI_IPF_SRST_OFFSET);//�⸴λ

    ipf_writel(IPF_INT_OPEN0, ipf_base_addr_ccore + HI_IPF_INT_MASK0_OFFSET);
    ipf_writel(IPF_INT_OPEN1, ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);
	return 0;
}
void bsp_ipf_dl_rpt1_switch(int value)
{
	unsigned int tmp = 0;
	tmp = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);
	tmp = value?(tmp | 0x30000):(tmp & 0xfffcffff);
	ipf_writel(tmp, ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);
}

/*
 * On ARMv5 and above those functions can be implemented around
 * the clz instruction.
 * refer to kernel/arch/arm/include/asm/bitops.h
 * put the code here for both vxWorks and linux version.
 */
static inline unsigned int ipf_fls(unsigned int x)
{
    unsigned int ret;

    asm("clz\t%0, %1" : "=r" (ret) : "r" (x));
    ret = 32 - ret;
    return ret;
}

static int get_ipf_ccore_dts(void)
{
	struct device_node *dev = NULL;
	const char *name = "hisilicon,ipf_balong_mdm";
	int ret = 0;

 	dev = of_find_compatible_node(NULL, NULL, name);
	if(NULL == dev)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"device node not found\n");
		return IPF_ERROR;
	}
	
    ipf_ccore_dts.addr = (unsigned int)of_iomap(dev, 0);
	if(!ipf_ccore_dts.addr)
		return IPF_ERROR;

    ipf_ccore_dts.irqnum0 = irq_of_parse_and_map(dev, 0);
	if(!ipf_ccore_dts.irqnum0)
		return IPF_ERROR;
	
    irqnum_ccore = ipf_ccore_dts.irqnum0;
    ipf_base_addr_ccore  = ipf_ccore_dts.addr;
	
	ret = of_property_read_u32_index(dev, "crg_clk_offset", 0, &crg_clkstat4_offset);
	ret |= of_property_read_u32_index(dev, "sc_stat_offset", 0, &sc_stat26_offset);

	if(ret){
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ipf dts crg_clk_offset do not need\n");
	}

	//only dallas platform need to reset ipf by peri_crg before going to start.
	(void)of_property_read_u32_array(dev, "rst_crg", reset_peri_crg, 2);
	bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF,"reset_peri_crg %x, %x, %x\n", reset_peri_crg[0],reset_peri_crg[1]);

	(void)of_property_read_u32_array(dev, "addr_limit", &(g_ipf_ctx.addr_limit), 1);
	
	return 0;
}

static inline void ipf_record_start_time_stamp(unsigned int en, unsigned int* rec_point)
{
    if (!en) {
        return;
    }
    *rec_point = bsp_get_slice_value_hrt();
    return;
}

static inline void ipf_record_end_time_stamp(unsigned int en, unsigned int beg_time)
{
    unsigned int diff_time;
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();
    unsigned int idx;

    if (!en) {
        return;
    }

    diff_time = bsp_get_slice_value_hrt() - beg_time;

    /* avoid to record the overflowed value */
    if (diff_time > IPF_MAX_TIME_LIMIT) {
        stamp_info->overflow++;
    }
    else {
        if (diff_time > stamp_info->diff_max)
            stamp_info->diff_max = diff_time;

        stamp_info->diff_sum += diff_time;
        stamp_info->cnt_sum++;

        /* find the first bit not zero */
        idx = ((ipf_fls(diff_time)-1) & IPF_FLS_MASK);
        stamp_info->diff_order_cnt[idx]++;
    }
}

static inline unsigned int ipf_calc_percent(unsigned int value, unsigned int sum)
{
    if (0 == sum) {
        return 0;
    }
    return (value * 100 / sum);
}

static void ipf_get_version(void)
{
	unsigned int ver = 0;
	ver = ipf_readl(ipf_base_addr_ccore + HI_IPF_VERSION_OFFSET);
	
	switch(ver){
	case IPF_VER_120A:
		g_ipf_ctx.ipf_version = IPF_VERSION_120a;
		break;
	case IPF_VER_130A:
		g_ipf_ctx.ipf_version = IPF_VERSION_130a;
		break;
	case IPF_VER_130B:
		g_ipf_ctx.ipf_version = IPF_VERSION_130b;
		break;
	default:
		g_ipf_ctx.ipf_version = IPF_VERSION_0000;
		break;
	}
}

void ipf_enable_rd_rate(int en)
{
    g_ipf_ctx.status->rate_en = en;
    return;
}

void ipf_enable_ul_time_stamp(int en)
{
    g_ipf_ctx.status->timestamp_en = en;
    return;
}

void ipf_clear_time_stamp(void)
{
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();

    memset_s(stamp_info, sizeof(IPF_TIMESTAMP_INFO_S), 0, sizeof(IPF_TIMESTAMP_INFO_S));/*[false alarm]:fortify*/
    return;
}

void ipf_dump_time_stamp(void)
{
    IPF_TIMESTAMP_INFO_S* stamp_info = IPF_GET_TIMESTAMP_INFO();
    unsigned int tmp = 0;
    int i;

    IPF_PRINT(" max diff:%u(%uus)\n",
              stamp_info->diff_max, stamp_info->diff_max*10/192);
    IPF_PRINT(" sum diff:%u(%uus)\n",
              stamp_info->diff_sum, stamp_info->diff_max/19);

    if (stamp_info->cnt_sum) {
        tmp = stamp_info->diff_sum / stamp_info->cnt_sum;
    }

    IPF_PRINT(" avg diff:%u(%uus)\n", tmp, tmp*10/192);

    for (i = 0; i < IPF_MAX_STAMP_ORDER; i++) {
        tmp = ipf_calc_percent(stamp_info->diff_order_cnt[i], stamp_info->cnt_sum);
        IPF_PRINT(" diff time (%u~%u) (%uus~%uus) count:%u (%u %%)\n",
            (0x80000000 >> (31-i)),
            (0xFFFFFFFF >> (31-i)),
            (0x80000000 >> (31-i))/19,
            (0xFFFFFFFF >> (31-i))/19,
            stamp_info->diff_order_cnt[i], tmp);
    }
    return;
}
/* IPF transfer time recorder end */

int mdrv_ipf_set_limited_addr(unsigned int start, unsigned int end)
{
	if(g_ipf_ctx.addr_limit){
		if(start == end)
			return IPF_ERROR;
		
		ipf_writel(start, ipf_base_addr_ccore + HI_IPF_MST_REGION0_START_OFFSET);
		ipf_writel(end, ipf_base_addr_ccore + HI_IPF_MST_REGION0_END_OFFSET);
		ipf_writel(SECCTRL_VALID0, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
	}
	return 0;
}

static int ipf_start_addr_limit(void)
{
	static int limit_set = 0;

	if(limit_set){//only set one times
		return 0;
	}

	if(g_ipf_ctx.addr_limit == 0){
		return IPF_ERROR;
	}
	
	if(g_ipf_ctx.sh_limit_addr->block_err){//acore do not get limit addr
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "acore do not get limit addr!\n");
		return IPF_ERROR;
	}
	
	if(g_ipf_ctx.sh_limit_addr->block_sum){
		
		ipf_writel(g_ipf_ctx.sh_limit_addr->block1_start, ipf_base_addr_ccore + HI_IPF_MST_REGION2_START_OFFSET);
		ipf_writel(g_ipf_ctx.sh_limit_addr->block1_end, ipf_base_addr_ccore + HI_IPF_MST_REGION2_END_OFFSET);
		
		if(g_ipf_ctx.sh_limit_addr->block_sum == 1){
			//acore sep one block and enable limit func
			ipf_writel(SECCTRL_VALID2, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
			limit_set = 1;
			return 0;
		}
		else if(g_ipf_ctx.sh_limit_addr->block_sum == 2){
			//acore sep two blocks and enable limit func
			ipf_writel(g_ipf_ctx.sh_limit_addr->block2_start, ipf_base_addr_ccore + HI_IPF_MST_REGION3_START_OFFSET);
			ipf_writel(g_ipf_ctx.sh_limit_addr->block2_end, ipf_base_addr_ccore + HI_IPF_MST_REGION3_END_OFFSET);
			ipf_writel(SECCTRL_VALID2_3, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
			limit_set = 1;
			return 0;
		}
		return IPF_ERROR;
	}
	return IPF_ERROR;
}

void ipf_write_basic_filter(unsigned int filter_hw_id, IPF_MATCH_INFO_S* match_infos)
{
    unsigned int j;
    unsigned int match_info;
    unsigned int* match_info_addr = (unsigned int*)match_infos;
    ipf_writel(filter_hw_id, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET);
    for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
    {
        match_info = *(match_info_addr+j);
        ipf_writel((match_info), (ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
    }
}

static void ipf_dump_callback(void)
{
	int i;
	char* ptr;
	
	if (g_ipf_ctx.dump_reg) {
		writel(0, ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);
		ptr = (char*)g_ipf_ctx.dump_reg;
		for(i = 0; i < IPF_REGS_SIZE; i += 4) {
			*(unsigned int*)(ptr + i) 
				= readl(ipf_base_addr_ccore + i);
		}
	}
}

void ipf_om_dump_init(void)
{

	g_ipf_ctx.dump_reg = (char*)bsp_dump_register_field(DUMP_CP_IPF, "IPF", 0, 0, 0x400, 0);
	
	if (!g_ipf_ctx.dump_reg) {
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "ipf backup mem for dump alloc failed\n");
		goto err;
	} else {
		g_ipf_ctx.status->dump_mem_alloc_ok = 1;
	}

    /* reg the dump callback to om */
	if (-1 == bsp_dump_register_hook("IPF", ipf_dump_callback)) {
	    goto err;
	}

    g_ipf_ctx.dump_size = 0x400;

    return;

err:
    g_ipf_ctx.dump_reg = NULL;
    g_ipf_ctx.dump_size = 0;
    return;
}

/*****************************************************************************
* �� �� ��      : ipf_init
*
* ��������  : IPF��ʼ��     �ڲ�ʹ�ã�����Ϊ�ӿں���
*
* �������  : void
* �������  : ��
* �� �� ֵ     : IPF_SUCCESS    ��ʼ���ɹ�
*                           IPF_ERROR      ��ʼ��ʧ��
*
* �޸ļ�¼  :2011��1��21��   ³��  ����
				 2013��4��30��    �¶����޸ģ����Ĵ������÷��䵽���� 
*****************************************************************************/
int ipf_init(void)
{
    unsigned int u32BDSize[IPF_CHANNEL_MAX] = {IPF_ULBD_DESC_SIZE, IPF_DLBD_DESC_SIZE};
    unsigned int u32RDSize[IPF_CHANNEL_MAX] = {IPF_ULRD_DESC_SIZE, IPF_DLRD_DESC_SIZE};
    unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {IPF_ADQ_DEFAULT_SEETING,IPF_ADQ_DEFAULT_SEETING};
    unsigned int u32IntMask0 = 0;
    unsigned int u32IntMask1 = 0;
    unsigned int u32ChanCtrl[IPF_CHANNEL_MAX] = {0,0};
    unsigned int u32IntStatus = 0;
    unsigned int u32Timeout = 0;
    unsigned int u32IntGate = 0;
    unsigned int u32DMAOutstanding = 3;	
	unsigned long ipf_flag = 0;
	unsigned int bak_reg=0;
	unsigned int pericrg_base_addr_virt = 0;
#ifdef CONFIG_CCORE_PM
    unsigned int u32Result = 0;
#endif
		
	struct clk *c_ipfclk = NULL; 
	/*ipf enable clock*/
	c_ipfclk = clk_get(NULL, "ipf_clk");
	if(IS_ERR(c_ipfclk))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ccore ipf clk get failed.\n");
		return -1;
	}

	if(0 !=clk_enable(c_ipfclk))
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ccore ipf clk open failed.\n");
		return -1;
	}

	if(IPF_ERROR == get_ipf_ccore_dts())
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r ccore ipf do not get dts data\n",0,0,0,0,0,0);
		return IPF_ERROR;
	}

#ifndef CONFIG_IPF_BACKUP_ON_LPM3
    unsigned long ipf_flags = 0;
    ipf_flags = ipf_flags;
#endif
	
	/*get ipf syscrg base virtual addr*/
	pericrg_base_addr_virt = (unsigned int)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg);

	g_ipf_ctx.sh_limit_addr = (IPF_LIMIT_ADDR_S *)IPF_TRANS_LIMIT_ADDR;

	if(reset_peri_crg[0]){
		//HI_LP_PERI_CRG_REG_ADDR
		if(g_ipf_ctx.sh_limit_addr->reset_flag == 0){
			bak_reg = ipf_readl(pericrg_base_addr_virt + reset_peri_crg[0]);
			bak_reg |= reset_peri_crg[1];

			spin_lock_irqsave(&ipf_reset_spinlock, ipf_flag);
			ipf_writel(bak_reg, pericrg_base_addr_virt + reset_peri_crg[0]);
			g_ipf_ctx.sh_limit_addr->reset_flag = 1;
			spin_unlock_irqrestore(&ipf_reset_spinlock, ipf_flag);
		}
	}

	//disable addr area limit func
	if(g_ipf_ctx.addr_limit){
		ipf_writel(SECCTRL_BYPASS, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
		ipf_writel(ipf_base_addr_ccore + MST_DEFAULT_ADDR, ipf_base_addr_ccore + HI_IPF_MST_DEFAULT_OFFSET);
		//set share ddr regions to ipf reg1
		ipf_writel((unsigned long)((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_IPF), ipf_base_addr_ccore + HI_IPF_MST_REGION1_START_OFFSET);
		ipf_writel(IPF_SHM_USED_END_ADDR, ipf_base_addr_ccore + HI_IPF_MST_REGION1_END_OFFSET);
		ipf_writel(SECCTRL_VALID1, ipf_base_addr_ccore + HI_IPF_MST_SECCTRL_OFFSET);
	}

    /* ��ʼ��ȫ�ֽṹ�� */
    memset_s((void*)IPF_ULBD_MEM_ADDR, IPF_DEBUG_INFO_ADDR - IPF_ULBD_MEM_ADDR, 0x0, IPF_DEBUG_INFO_ADDR - IPF_ULBD_MEM_ADDR);/* [false alarm]:fortify disable */
    
    g_stIpfUl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_ULBD_MEM_ADDR;
    g_stIpfUl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_ULRD_MEM_ADDR;
    g_stIpfUl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_ULAD0_MEM_ADDR;
    g_stIpfUl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_ULAD1_MEM_ADDR;
    g_stIpfUl.pu32IdleBd = (unsigned int*)IPF_ULBD_IDLENUM_ADDR;
    *(unsigned int*)IPF_ULBD_IDLENUM_ADDR = IPF_ULBD_DESC_SIZE;
    
    g_stIpfDl.pstIpfBDQ = (IPF_BD_DESC_S*)IPF_DLBD_MEM_ADDR;
    g_stIpfDl.pstIpfRDQ = (IPF_RD_DESC_S*)IPF_DLRD_MEM_ADDR;
    g_stIpfDl.pstIpfADQ0 = (IPF_AD_DESC_S*)IPF_DLAD0_MEM_ADDR;
    g_stIpfDl.pstIpfADQ1 = (IPF_AD_DESC_S*)IPF_DLAD1_MEM_ADDR;
    g_stIpfDl.pstIpfCDQ = (IPF_CD_DESC_S*)IPF_DLCD_MEM_ADDR;
    g_stIpfDl.u32IpfCdRptr = (unsigned int*) IPF_DLCDRPTR_MEM_ADDR;
    *(g_stIpfDl.u32IpfCdRptr) = 0;

    g_stIpfDl.u32IdleBd = IPF_DLBD_DESC_SIZE;
	
    /* ������չ���������ڴ�, ������չ�������Ļ�ַ */
    g_pstExFilterAddr = (IPF_MATCH_INFO_S*)IPF_EXT_FILTER_ADDR;
    memset_s((void*)g_pstExFilterAddr, EXFLITER_NUM*sizeof(IPF_MATCH_INFO_S), 0x0, EXFLITER_NUM*sizeof(IPF_MATCH_INFO_S));
    
    /* ������չ����������ʼ��ַ */	
    ipf_writel((unsigned int)g_pstExFilterAddr, ipf_base_addr_ccore + HI_IPF_EF_BADDR_OFFSET);

    /* ��ʼ������������ */
    if(IPF_FilterList_Init() != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf_init malloc list ERROR! \n");
        goto FREE_ERROR;
    }
    
    /* ���ó�ʱ���üĴ�����ʹ�ܳ�ʱ�жϣ����ó�ʱʱ�� */
    u32Timeout = TIME_OUT_CFG | (TIME_OUT_ENABLE);
    ipf_writel(u32Timeout, ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);

    /* ����ʱ���ſ����üĴ���������Ϊ�Զ��ſ�*/
    u32IntGate = GATE_CFG;
    ipf_writel(u32IntGate, ipf_base_addr_ccore + HI_IPF_GATE_OFFSET);/* [false alarm]:fortify disable */

    /* ��������ж��� */
    u32ChanCtrl[IPF_CHANNEL_UP] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);
    u32ChanCtrl[IPF_CHANNEL_UP] |= 0x30;
    ipf_writel(u32ChanCtrl[IPF_CHANNEL_UP], ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);

    u32ChanCtrl[IPF_CHANNEL_DOWN] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);
    u32ChanCtrl[IPF_CHANNEL_DOWN] |= 0x30;
    ipf_writel(u32ChanCtrl[IPF_CHANNEL_DOWN], ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);

    /* ��������ͨ����AD��BD��RD��� */
    ipf_writel(u32BDSize[IPF_CHANNEL_UP]-1, ipf_base_addr_ccore + HI_IPF_CH0_BDQ_SIZE_OFFSET);
    ipf_writel(u32RDSize[IPF_CHANNEL_UP]-1, ipf_base_addr_ccore + HI_IPF_CH0_RDQ_SIZE_OFFSET);
    ipf_writel(u32ADCtrl[IPF_CHANNEL_UP], ipf_base_addr_ccore + HI_IPF_CH0_ADQ_CTRL_OFFSET);

    /* ����ͨ����BD��RD��ʼ��ַ*/    
    ipf_writel((unsigned int)g_stIpfUl.pstIpfBDQ, ipf_base_addr_ccore + HI_IPF_CH0_BDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)g_stIpfUl.pstIpfRDQ, ipf_base_addr_ccore + HI_IPF_CH0_RDQ_BADDR_OFFSET);
    ipf_writel((unsigned int)g_stIpfUl.pstIpfADQ0, ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_BASE_OFFSET);
    ipf_writel((unsigned int)g_stIpfUl.pstIpfADQ1, ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_BASE_OFFSET);
	
    /* �����ж�����,ֻ��5���жϣ�����ϱ��������ʱ��RD���磬AD0��AD1�� */
    u32IntMask0 = IPF_INT_OPEN0;  /* 0��ΪModem CPU */
    u32IntMask1 = IPF_INT_OPEN1;
    ipf_writel(u32IntMask0, ipf_base_addr_ccore + HI_IPF_INT_MASK0_OFFSET);
    ipf_writel(u32IntMask1, ipf_base_addr_ccore + HI_IPF_INT_MASK1_OFFSET);

    /* ���ж� */
    u32IntStatus = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT_STATE_OFFSET);
    ipf_writel(u32IntStatus, ipf_base_addr_ccore + HI_IPF_INT_STATE_OFFSET);
    /*��DMAͨ����Outstanding��д*/
    ipf_writel(u32DMAOutstanding, ipf_base_addr_ccore + HI_IPF_DMA_CTRL1_OFFSET);

    /*��ʼ��ipf����������������*/
    spin_lock_init(&ipf_filter_spinlock);
	spin_lock_init(&ipf_dlbd_spinlock);
	
    IPF_Int_Connect();
	
#ifdef CONFIG_CCORE_PM

    u32Result = bsp_device_pm_add(&ipf_dpm_device);
    if(OK!= u32Result)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r ipf_dpm_device add error\n");
        return IPF_ERROR;
    }
#ifndef CONFIG_IPF_BACKUP_ON_LPM3
    ipf_acore_init_status = (unsigned int*)IPF_INIT_ADDR;
    ipf_ccore_init_status = (unsigned int*)(IPF_INIT_ADDR+4);
	
    spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
    bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
    *ipf_ccore_init_status = IPF_CCORE_INIT_SUCCESS;
    bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
    spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
#endif
#endif
	modem_reset_flag = (IPF_FORRESET_CONTROL_E*)(IPF_INIT_ADDR+8);
	bsp_register_master_idle(IPF_IDLE, ccpu_reset_ipf_and_wait_idle);

	/*acore use first block,ccore use scnd block*/
	g_ipf_ctx.status = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR + sizeof(struct ipf_debug));
	memset_s(g_ipf_ctx.status, sizeof(struct ipf_debug), 0, sizeof(struct ipf_debug));

	ipf_om_dump_init();
	ipf_get_version();
	
	g_ipf_ctx.status->init_ok = IPF_CCORE_INIT_SUCCESS;
#ifdef CONFIG_PSAM
	psam_para.dlcdq		 = g_stIpfDl.pstIpfCDQ;
	psam_para.dlcdq_rptr = g_stIpfDl.u32IpfCdRptr;
	psam_para.dlcdq_wptr = &(g_stIpfDl.u32IpfCdWptr);
	psam_para.dlbdq_rptr_addr = ipf_base_addr_ccore + HI_IPF_CH1_BDQ_RPTR_OFFSET;
	psam_para.dlbdq_wptr_addr = ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET;
	bsp_psam_set_ipf_para(&psam_para);
#endif
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"[IPF] ipf init success\n");
	
    return IPF_SUCCESS;

FREE_ERROR:
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r ipf_init malloc ERROR! \n");
    return IPF_ERROR;
}



static irqreturn_t  ipf_interuppt(void * arg)
{
    unsigned int status = 0;

    status = ipf_readl(ipf_base_addr_ccore + HI_IPF_INT0_OFFSET); 
	
	ipf_writel(status, ipf_base_addr_ccore + HI_IPF_INT_STATE_OFFSET);

    if(status & (IPF_UL_RPT_INT0 | IPF_UL_TIMEOUT_INT0)) {
		if (status & IPF_UL_RPT_INT0) {
			g_ipf_ctx.status->rd_comp_intr++;
		}
		
		if (status & IPF_UL_TIMEOUT_INT0) {
			g_ipf_ctx.status->time_out_intr++;
		}

        if(g_stIpfUl.pFnUlIntCb) {
            g_stIpfUl.pFnUlIntCb();  
			g_ipf_ctx.status->rd_cb++;
        } else {
        	g_ipf_ctx.status->rd_cb_null++;
        }
    }

	
    if(status & (IPF_UL_ADQ0_EPTY_INT0 | IPF_UL_ADQ1_EPTY_INT0)) {
		if (g_stIpfUl.pAdqEmptyUlCb) {
        	if ((status & (IPF_UL_ADQ0_EPTY_INT0 | IPF_UL_ADQ1_EPTY_INT0))
				== (IPF_UL_ADQ0_EPTY_INT0 | IPF_UL_ADQ1_EPTY_INT0)) {
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_0]++;
				g_ipf_ctx.status->ad_epty_intr[IPF_AD_1]++;
				g_stIpfUl.pAdqEmptyUlCb(IPF_EMPTY_ADQ);  
			} else {
				if ((status & IPF_UL_ADQ1_EPTY_INT0) == IPF_UL_ADQ1_EPTY_INT0) {
					g_ipf_ctx.status->ad_epty_intr[IPF_AD_1]++;
					g_stIpfUl.pAdqEmptyUlCb(IPF_EMPTY_ADQ1);  
				} else {
					g_ipf_ctx.status->ad_epty_intr[IPF_AD_0]++;
					g_stIpfUl.pAdqEmptyUlCb(IPF_EMPTY_ADQ0);  
				}
			}
			g_ipf_ctx.status->ad_epty_cb++;
		} else {
        	g_ipf_ctx.status->ad_epty_cb_null++;
        }
    }
	
	if(status & IPF_MST_SEC_WR_ERR){
		g_ipf_ctx.status->reg_scur_wr_err++;
		//call system err
	}
	
	if(status & IPF_MST_SEC_RD_ERR){
		g_ipf_ctx.status->reg_scur_rd_err++;
		//call system err
	}
	
    if(status & IPF_UL_RDQ_FULL) {
		g_ipf_ctx.status->rd_full++;
    }

    return IRQ_HANDLED;
}/*lint !e550*/

/*****************************************************************************
* �� �� ��     : IPF_Int_Connect
*
* ��������  : ��IPF�жϴ�����(���˶��ṩ)
*
* �������  : void
* �������  : ��
* �� �� ֵ      : ��
*
* �޸ļ�¼  :2011��12��2��   ³��  ����
*****************************************************************************/
void IPF_Int_Connect(void)
{
	int s32Result;

	s32Result = request_irq(irqnum_ccore, (irq_handler_t)ipf_interuppt, IRQF_NO_SUSPEND, "balong_ipf_v700r200", NULL);
	if(0 != s32Result)
	{
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r IPF_Int_Connect Failed! \n",0,0,0,0,0,0);
	}
}


#ifndef CONFIG_IPF_BACKUP_ON_LPM3
/*����K3V3����������⣬ipf�޷���M3�ϻָ�ipf�Ĵ��������ƶ���acore��ccore*/

/*****************************************************************************
* �� �� ��       : ipf_drx_restore_filter
*
* ��������  : �ṩ�ĵ͹��Ľӿڣ�����IPF�ϵ�ָ�
*
* �������  : ��
*             
* �������  : ��
* �� �� ֵ     : ��
*
* ע��:�ú�����Ҫ�����жϵ�����µ���
* �޸ļ�¼  : 2013��4��23��v1.00 chendongyue ����
			2014��1��23��v1.01 chendongyue ��ֲ��A9core
*****************************************************************************/
int ipf_drx_restore_filter(void)
{
    unsigned int i,j,k,filter_serial;
    IPF_MATCH_INFO_S* pstMatchInfo;
    unsigned int match_info;
    unsigned int* match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR);

    for(i=0 ; i < IPF_MODEM_MAX; i++)
    {
        match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR + i*sizeof(IPF_MATCH_INFO_S));
        pstMatchInfo = (IPF_MATCH_INFO_S*)match_info_addr;
        filter_serial = i;
        k = 0;
        do
        {
            if(filter_serial < IPF_BF_NUM)
            {
                ipf_writel(filter_serial, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
                for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
                {
                        match_info = *(match_info_addr+j);
                        ipf_writel((match_info), (ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
                }
                k++;
            }
            filter_serial = pstMatchInfo->unFltChain.Bits.u16NextIndex;
            pstMatchInfo = (IPF_MATCH_INFO_S*)(IPF_PWRCTL_BASIC_FILTER_ADDR + filter_serial*sizeof(IPF_MATCH_INFO_S));
            match_info_addr = (unsigned int *)pstMatchInfo;
            if(k >= IPF_BF_NUM)
            {
                break;
            }
        }while(filter_serial != IPF_TAIL_INDEX);
    }
    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��       : ipf_check_filter_restore
*
* ��������  : �ṩ�ĵ͹��Ľӿڣ�����IPF�ϵ�ָ�
*
* �������  : ��
*             
* �������  : ��
* �� �� ֵ     : ��
*
* 
* �޸ļ�¼  : 2014��1��23��v1.00 chendongyue����
*****************************************************************************/
void ipf_check_filter_restore(void)
{
#ifdef CONFIG_CCORE_PM
	unsigned long ipf_flags = 0;
	unsigned int ipf_init_status = 0;
	spin_lock_irqsave(&ipf_filter_spinlock, ipf_flags);
	bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);

	ipf_init_status = (*ipf_acore_init_status)|(*ipf_ccore_init_status);
	*ipf_ccore_init_status = IPF_CCORE_INIT_SUCCESS;

	cache_sync();

	if(IPF_PWC_DOWN != ipf_init_status)
	{
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
		spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
		return;
	}
	else
	{
		ipf_drx_restore_filter();
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
		spin_unlock_irqrestore(&ipf_filter_spinlock, ipf_flags);
		return;
	}
#endif
}

#endif

int mdrv_ipf_config_timeout(unsigned int u32Timeout)
{
    if((u32Timeout == 0) || (u32Timeout > 0xFFFF))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_timeout u32Timeout ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    u32Timeout |= TIME_OUT_ENABLE;
    ipf_writel(u32Timeout, ipf_base_addr_ccore + HI_IPF_TIME_OUT_OFFSET);
    
    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��      : mdrv_ipf_set_pktlen
*
* ��������  : �ýӿ��������ù�������������С����
*
* �������  : unsigned int MaxLen   ������
*                           unsigned int MinLen   ��С����
*
* �������   : ��
* �� �� ֵ      : IPF_SUCCESS                �ɹ�
*                           BSP_ERR_IPF_INVALID_PARA   ��������(����������С����С)
*
* �޸ļ�¼  :2011��2��17��   ³��  ����
*****************************************************************************/
int mdrv_ipf_set_pktlen(unsigned int u32MaxLen, unsigned int u32MinLen)
{
    unsigned int u32PktLen = 0;

    /* ������� */
    if(u32MaxLen < u32MinLen)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r mdrv_ipf_set_pktlen input error! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    
    u32PktLen = ((u32MaxLen&0x3FFF)<<16) | (u32MinLen&0x3FFF);
    
    ipf_writel(u32PktLen, ipf_base_addr_ccore + HI_IPF_PKT_LEN_OFFSET);
    return IPF_SUCCESS;
}/*lint !e550*/

/**********************************��ά�ɲ�ӿں���************************************/
void bsp_ipf_help(void)
{
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_info ����1:ͨ������  0Ϊ���У�1Ϊ����\n");
    IPF_PRINT("bsp_ipf_bdinfo  ����1:ͨ������  ����2:BDָ��\n");
    IPF_PRINT("bsp_ipf_rdinfo  ����1:ͨ������  ����2:RDָ��\n"); 
    IPF_PRINT("bsp_ipf_adinfo ����1:ͨ������  ����2:ADָ�����3:AD ��������0Ϊ��,1Ϊ��\n"); 
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_dump_bdinfo  ����1:ͨ������\n");
    IPF_PRINT("bsp_ipf_dump_rdinfo  ����1:ͨ������\n"); 
    IPF_PRINT("bsp_ipf_dump_adinfo����1:ͨ������\n"); 
    IPF_PRINT("===============================================\n");
    IPF_PRINT("ipf_enable_ul_time_stamp  ����1:0-disable, 1-enable\n");
    IPF_PRINT("ipf_enable_dl_time_stamp  ����1:0-disable, 1-enable\n");
    IPF_PRINT("ipf_clear_time_stamp  ���ʵ�ʴ���¼\n");
    IPF_PRINT("ipf_dump_time_stamp  Linux:����ʱ���, vxWorks:����ʱ���\n");
    IPF_PRINT("===============================================\n");
    IPF_PRINT("bsp_ipf_usefilterinfo 	����1:ͨ������\n"); 
    IPF_PRINT("BSP_IPF_FreeFilterInfo\n"); 
    IPF_PRINT("bsp_ipf_filterinfohwid	����1:Ӳ��Filter ID\n");
    IPF_PRINT("bsp_ipf_filterinfopsid	����1 :PS Filter ID\n");
}
void bsp_ipf_show_status(void)
{
	int i;
	struct ipf_debug* ptr = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR);

	g_ipf_ctx.status->flt_chain_loop = (int)readl(ipf_base_addr_ccore + HI_FLT_CHAIN_LOOP_OFFSET);

	for (i = 0; i < IPF_CHANNEL_MAX; i++) {
		IPF_PRINT("====ipf %score status====\n", i == 0 ? "a" : "c");
		IPF_PRINT("flt_chain_loop		%d\n", ptr->flt_chain_loop);
		IPF_PRINT("time_out_intr		%d\n", ptr->time_out_intr);
		IPF_PRINT("rd_comp_intr			%d\n", ptr->rd_comp_intr);
		IPF_PRINT("rd_full			%d\n", ptr->rd_full);
		IPF_PRINT("rd_cb			%d\n", ptr->rd_cb);
		IPF_PRINT("rd_cb_null		%d\n", ptr->rd_cb_null);
		IPF_PRINT("get_rd_num_times	%d\n", ptr->get_rd_num_times);
		IPF_PRINT("get_rd_times		%d\n", ptr->get_rd_times);
		IPF_PRINT("get_rd_short_cnt		%d\n", ptr->get_rd_cnt[IPF_AD_0]);
		IPF_PRINT("get_rd_long_cnt		%d\n", ptr->get_rd_cnt[IPF_AD_1]);
		IPF_PRINT("get_ad_num_times	%d\n", ptr->get_ad_num_times);
		IPF_PRINT("get_ad_thred	%d\n", 	   ptr->ad_thred);
		IPF_PRINT("short_adq_empty_intr	%d\n", ptr->ad_epty_intr[IPF_AD_0]);
		IPF_PRINT("short_adq_cfg_count	%d\n", ptr->cfg_ad_cnt[IPF_AD_0]);
		IPF_PRINT("short_adq_out_ptr_null	%d\n", ptr->ad_out_ptr_null[IPF_AD_0]);
		IPF_PRINT("long_adq_cfg_count	%d\n", ptr->cfg_ad_cnt[IPF_AD_1]);
		IPF_PRINT("long_adq_empty_intr	%d\n", ptr->ad_epty_intr[IPF_AD_1]);
		IPF_PRINT("long_adq_out_ptr_null	%d\n", ptr->ad_out_ptr_null[IPF_AD_1]);
		IPF_PRINT("ad_epty_cb		%d\n", ptr->ad_epty_cb);
		IPF_PRINT("ad_epty_cb_null		%d\n", ptr->ad_epty_cb_null);
		IPF_PRINT("bd_epty_intr		%d\n", ptr->bd_epty_intr);
		IPF_PRINT("bd_epty_cb		%d\n", ptr->bd_epty_cb);
		IPF_PRINT("bd_epty_cb_null		%d\n", ptr->bd_epty_cb_null);
		IPF_PRINT("get_bd_num_times	%d\n", ptr->get_bd_num_times);
		IPF_PRINT("bd_cfg_times		%d\n", ptr->cfg_bd_times);
		IPF_PRINT("cfg_bd_cnt		%d\n", ptr->cfg_bd_cnt);
		IPF_PRINT("bd_full			%d\n", ptr->bd_full);
		IPF_PRINT("bd_len_zero_err		%d\n", ptr->bd_len_zero_err);
		IPF_PRINT("busy_cnt		%d\n", ptr->busy_cnt);
		IPF_PRINT("resume			%d\n", ptr->resume);
		IPF_PRINT("suspend			%d\n", ptr->suspend);
		IPF_PRINT("time_stamp_en		%d\n", ptr->timestamp_en);
		IPF_PRINT("rate_en			%d\n", ptr->rate_en);
		IPF_PRINT("init_ok			0x%x\n", ptr->init_ok);
		IPF_PRINT("mdrv_called_not_init	%d\n", ptr->mdrv_called_not_init);
		IPF_PRINT("invalid_para		%d\n", ptr->invalid_para);
		IPF_PRINT("debug			%d\n", ptr->debug);
		IPF_PRINT("scr wr			%d\n", ptr->reg_scur_wr_err);
		IPF_PRINT("scr rd			%d\n", ptr->reg_scur_rd_err);
		ptr++;
	}
}

int bsp_ipf_bdinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32BdqPtr)
{      
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32BdqPtr >= IPF_ULBD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("==========BD Info=========\n");
            IPF_PRINT("BDλ��:         %d\n",u32BdqPtr);
            IPF_PRINT("u16Attribute:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:      %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
            IPF_PRINT("u16Resv:        %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:   %d\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfUl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
			IPF_PRINT("BD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfBDQ + u32BdqPtr));
			IPF_PRINT("BD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfBDQ + u32BdqPtr)));
            break;
       case IPF_CHANNEL_DOWN:
            if(u32BdqPtr >= IPF_DLBD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("==========BD Info=========\n");
            IPF_PRINT("BDλ��:         %d\n",u32BdqPtr);
            IPF_PRINT("u16Attribute:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:      %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:       0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:      0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32OutPtr);
            IPF_PRINT("u16Resv:        %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:   %d\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:   0x%x\n",g_stIpfDl.pstIpfBDQ[u32BdqPtr].u32UsrField3);
			IPF_PRINT("BD Desc Virt Addr:	0x%x\n",(g_stIpfDl.pstIpfBDQ + u32BdqPtr));
			IPF_PRINT("BD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfDl.pstIpfBDQ + u32BdqPtr)));
            break; 
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}

int bsp_ipf_dump_bdinfo(IPF_CHANNEL_TYPE_E eChnType)
{
    unsigned int i;
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
			
            for(i = 0;i < IPF_ULBD_DESC_SIZE;i++)
            {
                bsp_ipf_bdinfo(IPF_CHANNEL_UP,i);
            }
        break;
		
        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLBD_DESC_SIZE;i++)
            {
                bsp_ipf_bdinfo(IPF_CHANNEL_DOWN,i);
            }
        break;
				
        default:
        IPF_PRINT("Input param invalid ! \n");
        break;

    }
    return 0;
}

int bsp_ipf_rdinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32RdqPtr)
{     
    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32RdqPtr >= IPF_ULRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("===========RD Info==========\n");
            IPF_PRINT("RDλ��:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfUl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
			IPF_PRINT("RD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfRDQ + u32RdqPtr));
			IPF_PRINT("RD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfRDQ + u32RdqPtr)));
            break;
       case IPF_CHANNEL_DOWN:
            if(u32RdqPtr >= IPF_DLRD_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            IPF_PRINT("============RD Info===========\n");
            IPF_PRINT("RDλ��:             %d\n",u32RdqPtr);
            IPF_PRINT("u16Attribute:       %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Attribute);
            IPF_PRINT("u16PktLen:          %d\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16PktLen);
            IPF_PRINT("u32InPtr:           0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32InPtr);
            IPF_PRINT("u32OutPtr:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32OutPtr);
            IPF_PRINT("u16Result:          0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16Result);
            IPF_PRINT("u16UsrField1:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u16UsrField1);
            IPF_PRINT("u32UsrField2:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField2);
            IPF_PRINT("u32UsrField3:       0x%x\n",g_stIpfDl.pstIpfRDQ[u32RdqPtr].u32UsrField3);
			IPF_PRINT("RD Desc Virt Addr:	0x%x\n",(g_stIpfUl.pstIpfRDQ + u32RdqPtr));
			IPF_PRINT("RD Desc Phy Addr:	0x%x\n",SHD_DDR_V2P((void *)(g_stIpfUl.pstIpfRDQ + u32RdqPtr)));
            break; 
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}


int bsp_ipf_dump_rdinfo(IPF_CHANNEL_TYPE_E eChnType)
{
    int i;

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:

            for(i = 0;i < IPF_ULBD_DESC_SIZE;i++)
            {
                bsp_ipf_rdinfo(IPF_CHANNEL_UP,i);
            }
        break;
		
        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLBD_DESC_SIZE;i++)
            {
                bsp_ipf_rdinfo(IPF_CHANNEL_DOWN,i);
            }
        break;
        default:
        IPF_PRINT("Input param invalid ! \n");
        break;
    }
    return 0;
}
int bsp_ipf_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdqPtr, unsigned int u32AdType)
{

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            if(u32AdqPtr >= IPF_ULAD0_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            if(0 == u32AdType)
            {
                 IPF_PRINT("===========UL AD0 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfUl.pstIpfADQ0[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfUl.pstIpfADQ0[u32AdqPtr].u32OutPtr1);
            }
            else
            {
                 IPF_PRINT("===========UL AD1 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfUl.pstIpfADQ1[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfUl.pstIpfADQ1[u32AdqPtr].u32OutPtr1);
            }
            break;
       case IPF_CHANNEL_DOWN:
            if(u32AdqPtr >= IPF_ULAD1_DESC_SIZE)
            {
                return IPF_ERROR;
            }
            if(0 == u32AdType)
	      	{
                 IPF_PRINT("===========DL AD0 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfDl.pstIpfADQ0[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfDl.pstIpfADQ0[u32AdqPtr].u32OutPtr1);
            }
            else
            {
                 IPF_PRINT("===========DL AD1 Info==========\n");
                 IPF_PRINT("ADλ��:             %d\n",u32AdqPtr);
                 IPF_PRINT("u32OutPtr0(phy_addr, use by hardware):       0x%x\n",g_stIpfDl.pstIpfADQ1[u32AdqPtr].u32OutPtr0);
                 IPF_PRINT("u32OutPtr1(usrfield skb_addr default):          0x%x\n",g_stIpfDl.pstIpfADQ1[u32AdqPtr].u32OutPtr1);
            }
            break;
        default:
            break;
    }
    IPF_PRINT("************************\n");
    return 0;
}


int bsp_ipf_dump_adinfo(IPF_CHANNEL_TYPE_E eChnType, unsigned int u32AdType)
{
    int i;

    switch(eChnType)
    {
        case IPF_CHANNEL_UP:
            for(i = 0;i < IPF_ULAD0_DESC_SIZE;i++)
            {
                bsp_ipf_adinfo(IPF_CHANNEL_UP, i, u32AdType);
            }
        break;
		
        case IPF_CHANNEL_DOWN:

            for(i = 0;i < IPF_DLAD1_DESC_SIZE;i++)
            {
                bsp_ipf_adinfo(IPF_CHANNEL_DOWN, i, u32AdType);
            }
        break;
		
        default:
        IPF_PRINT("Input param invalid ! \n");
        break;
    }
    return 0;
}

int bsp_ipf_info(IPF_CHANNEL_TYPE_E eChnType)
{
    unsigned int u32BdqDepth = 0;
    unsigned int u32BdqWptr = 0;
    unsigned int u32BdqRptr = 0;
    unsigned int u32BdqWaddr = 0;
    unsigned int u32BdqRaddr = 0;
    unsigned int u32RdqDepth = 0;
    unsigned int u32RdqRptr = 0;
    unsigned int u32RdqWptr = 0;
    unsigned int u32RdqWaddr = 0;
    unsigned int u32RdqRaddr = 0;
    unsigned int u32Depth = 0;
    unsigned int u32status = 0;
	
    unsigned int u32Adq0Rptr = 0;
    unsigned int u32Adq0Wptr = 0;

    unsigned int u32Adq1Rptr = 0;
    unsigned int u32Adq1Wptr = 0;

    if(IPF_CHANNEL_UP == eChnType)
    {
        u32Depth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_DQ_DEPTH_OFFSET);
        u32RdqDepth = (u32Depth>>16)&IPF_DQ_DEPTH_MASK;
        u32BdqDepth = u32Depth&IPF_DQ_DEPTH_MASK;

        u32status = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_STATE_OFFSET);

        u32BdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_WPTR_OFFSET);
        u32BdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_RPTR_OFFSET); 
        u32BdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_WADDR_OFFSET); 
        u32BdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_BDQ_RADDR_OFFSET); 
    
        u32RdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_WPTR_OFFSET);
        u32RdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RPTR_OFFSET);
        u32RdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_WADDR_OFFSET); 
        u32RdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RADDR_OFFSET); 
		
        u32Adq0Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
        u32Adq0Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);

        u32Adq1Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
        u32Adq1Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);

    }
    else if(IPF_CHANNEL_DOWN == eChnType)
    {
        u32Depth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_DQ_DEPTH_OFFSET);
        u32RdqDepth = (u32Depth>>16)&IPF_DQ_DEPTH_MASK;
        u32BdqDepth = u32Depth&IPF_DQ_DEPTH_MASK;

        u32status = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_STATE_OFFSET);
		
        u32BdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET);
        u32BdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_RPTR_OFFSET); 
        u32BdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WADDR_OFFSET); 
        u32BdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_RADDR_OFFSET); 
    
        u32RdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_WPTR_OFFSET);
        u32RdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_RPTR_OFFSET);
        u32RdqWaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_WADDR_OFFSET); 
        u32RdqRaddr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_RDQ_RADDR_OFFSET); 

        u32Adq0Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ0_RPTR_OFFSET);
        u32Adq0Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ0_WPTR_OFFSET);

        u32Adq1Rptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ1_RPTR_OFFSET);
        u32Adq1Wptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ1_WPTR_OFFSET);

    }
    else
    {
        return 1;
    }
    IPF_PRINT("============================\n");
    IPF_PRINT("ͨ�� ״̬:            0x%x\n", u32status);
    IPF_PRINT("BD ���:            %d\n", u32BdqDepth);
    IPF_PRINT("BD дָ��:          %d\n", u32BdqWptr);
    IPF_PRINT("BD ��ָ��:          %d\n", u32BdqRptr);
    IPF_PRINT("BD д��ַ:          0x%x\n", u32BdqWaddr);
    IPF_PRINT("BD ����ַ:          0x%x\n", u32BdqRaddr);
    IPF_PRINT("RD ���:            %d\n", u32RdqDepth);
    IPF_PRINT("RD ��ָ��:          %d\n", u32RdqRptr);
    IPF_PRINT("RD дָ��:          %d\n", u32RdqWptr);
    IPF_PRINT("RD ����ַ:          0x%x\n", u32RdqRaddr);
    IPF_PRINT("RD д��ַ:          0x%x\n", u32RdqWaddr);

    IPF_PRINT("AD0 ��ָ��:          %d\n", u32Adq0Rptr);
    IPF_PRINT("AD0 дָ��:          %d\n", u32Adq0Wptr);
	
    IPF_PRINT("AD1 ��ָ��:          %d\n", u32Adq1Rptr);
    IPF_PRINT("AD1 дָ��:          %d\n", u32Adq1Wptr);
    IPF_PRINT("============================\n");   
    return 0;
}

void bsp_ipf_mem(void)
{
	ipf_ddr_t *ddr_info = &g_ipf_ctx.status->share_ddr_info;
	unsigned int dl_start = IPF_DLBD_MEM_ADDR;
	
	IPF_PRINT("IPF Shared DDR information:\n");
	IPF_PRINT("start				 0x%x \n", ddr_info->start);
	IPF_PRINT("ul_start 			 0x%x \n", ddr_info->ul_start);
	IPF_PRINT("dl_start 			 0x%x \n", dl_start);
	IPF_PRINT("filter_pwc_start 	 0x%x \n", ddr_info->filter_pwc_start);
	IPF_PRINT("pwc_info_start		 0x%x \n", ddr_info->pwc_info_start);
	IPF_PRINT("dlcdrptr 			 0x%x \n", ddr_info->dlcdrptr);
	IPF_PRINT("debug_dlcd_start 	 0x%x \n", ddr_info->debug_dlcd_start);
	IPF_PRINT("debug_dlcd_size		 0x%x \n", ddr_info->debug_dlcd_size);
	IPF_PRINT("end					 0x%x \n", ddr_info->end);
	IPF_PRINT("len(The max:0x10000)  0x%x \n", ddr_info->len);

	IPF_PRINT("=======================================\n");
	IPF_PRINT("   bsp_ipf_mem		   ADDR 		   SIZE\n");
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_ULBD_MEM_ADDR	  ", IPF_ULBD_MEM_ADDR, (unsigned long)IPF_ULBD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_ULRD_MEM_ADDR	  ", IPF_ULRD_MEM_ADDR, (unsigned long)IPF_ULRD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLBD_MEM_ADDR	  ", IPF_DLBD_MEM_ADDR, (unsigned long)IPF_DLBD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLRD_MEM_ADDR	  ", IPF_DLRD_MEM_ADDR, (unsigned long)IPF_DLRD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DLCD_MEM_ADDR	  ", IPF_DLCD_MEM_ADDR, (unsigned long)IPF_DLCD_MEM_SIZE);
	IPF_PRINT("%s%lx\t\t%d\n", "IPF_INIT_ADDR		 ", IPF_INIT_ADDR, IPF_INIT_SIZE);
	IPF_PRINT("%s%lx\t\t%lu\n", "IPF_DEBUG_INFO_ADDR  ", IPF_DEBUG_INFO_ADDR, (unsigned long)IPF_DEBUG_INFO_SIZE);
}

/*****************************************************************************
* �� �� ��     : BSP_IPF_GetControlFLagForCcoreReset
*
* ��������  : modem������λipf���亯���������ڸ�λʱ��ֹ��������
*
* �������  : ��
*   
* �������  : ��
*
* �� �� ֵ     : �ɹ�
*
* �޸ļ�¼  :2014��2��14��   �¶���  ����
*****************************************************************************/
static IPF_FORRESET_CONTROL_E BSP_IPF_GetControlFLagForCcoreReset(void)
{
    return *modem_reset_flag;
}

/*****************************************************************************
 �� �� ��  : ccpu_reset_ipf_and_wait_idle
 ��������  : c�˸�λ��رղ��ȴ�ipf�������̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : ccpu_reset_ipf_and_wait_idle
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    �޸�����   : �����ɺ���

*****************************************************************************/
int ccpu_reset_ipf_and_wait_idle(void)
{
    unsigned int regvalue = 0;
    unsigned int u32slicebegin = 0;
	unsigned int hi_syscrg_base_addr_virt = 0;

	/*get ipf syscrg base virtual addr*/
	hi_syscrg_base_addr_virt = (unsigned int)bsp_sysctrl_addr_byindex(sysctrl_mdm);
	
    /*��ѯipf clk��״̬*/
    regvalue = ipf_readl(hi_syscrg_base_addr_virt + crg_clkstat4_offset);
    regvalue &= (unsigned int)0x1 << 10;
    if(regvalue != ((unsigned int)0x1 << 10)){
        return IPF_SUCCESS;
    }
    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_IPF_SOFT_RESET);

    /*��ѯIPF�Ƿ����*/
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = ipf_readl(hi_syscrg_base_addr_virt + sc_stat26_offset);
        regvalue &= (unsigned int)0x2;
    }while((0x2 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x2 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_IPF_STEP2)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return IPF_ERROR;
    }

    /*��λIPF*/
    regvalue = ipf_readl(ipf_base_addr_ccore + HI_IPF_SRST_OFFSET);
    regvalue |= (unsigned int)0x1;
    ipf_writel(regvalue, ipf_base_addr_ccore + HI_IPF_SRST_OFFSET);

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_IPF_ENTER_IDLE);

    /*�жϸ�λ�Ƿ�ɹ�*/
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = ipf_readl(ipf_base_addr_ccore + HI_IPF_SRST_STATE_OFFSET);
        regvalue &= (unsigned int)0x1;
    }while((0x1 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x1 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_IPF_STEP1)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return IPF_ERROR;
    }

    /*��ѯIPF�Ƿ����*/
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = ipf_readl(hi_syscrg_base_addr_virt + sc_stat26_offset);
        regvalue &= (unsigned int)0x2;
    }while((0x2 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x2 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_IPF_STEP2)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        return IPF_ERROR;
    }
    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��  : IPF_FilterList_Init
*
* ��������  : IPF�����������ʼ��     �ڲ�ʹ�ã�����Ϊ�ӿں���
*
* �������  : void
* �������  : ��
* �� �� ֵ  : IPF_SUCCESS    �����������ʼ���ɹ�
*                       IPF_ERROR      �����������ʼ��ʧ��
*
* �޸ļ�¼  :2011��11��17��   ³��  ����
*****************************************************************************/
int IPF_FilterList_Init(void)
{
    unsigned int i = 0;
    IPF_ID_S* current = NULL;
    IPF_ID_S* prev = NULL;
    IPF_ID_S* tmp = NULL;
	
    /* ��ʼ������ͷ�ڵĵĹ�������uselist����0-7*/	
    for(i =  0; i < IPF_FILTER_CHAIN_MAX_NUM; i++)
    {
        g_stIPFFilterInfo[i].u32FilterNum = 0;
        g_stIPFFilterInfo[i].pstUseList = NULL;
        IPF_DeleteAll(i);
    }

    /* ��ʼ��basiclist  ��8�ſ�ʼ��0-7������ͷ������*/
    for(i =  IPF_FILTER_CHAIN_MAX_NUM; i < IPF_BF_NUM; i++)
    {
        /* coverity[alloc_fn] */
        current = (IPF_ID_S*)osl_malloc(sizeof(IPF_ID_S));
        if(NULL == current)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init malloc ERROR! \n");
            goto FREE_ALL;
        }
        if(g_stIPFBasicFreeList != NULL)
        {
            if(NULL != prev)
            {
                prev->pstNext = current;/*lint !e613*/
            }
            else
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init prev == null! \n");
                goto FREE_ALL;
            }
        }
        else /* basicfreelistͷ��� */
        {
            g_stIPFBasicFreeList = current;
        }
        current->u32FilterID = i;
        current->u32PsID = 0;
        current->pstNext = NULL;

        prev = current;
    }
	
    prev = NULL;
    /* ��ʼ��extfreelist  ��64�ſ�ʼ*/
    for(i =  IPF_BF_NUM; i < IPF_TOTAL_FILTER_NUM; i++)
    {
        current = (IPF_ID_S*)osl_malloc(sizeof(IPF_ID_S));
        if(NULL == current)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init malloc ERROR! \n");
            goto FREE_ALL;
        }
        if(g_stIPFExtFreeList != NULL)
        {
            if(NULL != prev)
            {
                prev->pstNext = current;/*lint !e613*/
            }
            else
            {
                bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF_FilterList_Init prev == null! \n");
                goto FREE_ALL;
            }
        }
        else /* freelistͷ��� */
        {
            g_stIPFExtFreeList = current;
        }
        current->u32FilterID = i;
        current->u32PsID = 0;
        current->pstNext = NULL;
        prev = current;
    }
    	
    return IPF_SUCCESS;
    
FREE_ALL:
    i=0;
	
    /* coverity[overrun-local] */
    while((g_stIPFFilterInfo[i].pstUseList != NULL)&&(i <IPF_FILTER_CHAIN_MAX_NUM))/* [false alarm]:fortify disable */
    {
        osl_free(g_stIPFFilterInfo[i].pstUseList );
        /* coverity[incr] */
        i++;
    }

    while(g_stIPFBasicFreeList!= NULL)
    {
    	tmp = g_stIPFBasicFreeList->pstNext;
        osl_free(g_stIPFBasicFreeList);
        g_stIPFBasicFreeList = tmp;
    }

    while(g_stIPFExtFreeList!= NULL)
    {
    	tmp = g_stIPFExtFreeList->pstNext;
        osl_free(g_stIPFExtFreeList);
        g_stIPFExtFreeList = tmp;
    }

    return IPF_ERROR;
}

/*****************************************************************************
* �� �� ��  : IPF_AddToFreeList
*
* ��������  : �����ӵ�freelist�ĺ���λ��
*
* �������  : IPF_ID_S* stNode             ������Ľ��ָ��
*             
* �������  : ��

* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011��3��30��   ³��  ����
*****************************************************************************/
void IPF_AddToBasicFreeList(IPF_ID_S* stNode)
{
    IPF_ID_S* current = NULL;    
    IPF_ID_S* prev = NULL;

    current = g_stIPFBasicFreeList;

    /* ���freelistΪ�� */
    if(NULL == current)
    {
        g_stIPFBasicFreeList = stNode;
        g_stIPFBasicFreeList->pstNext = NULL;
        return;
    }

    /* ����ȵ�һ������ID��С */
    if(stNode->u32FilterID < current->u32FilterID)
    {
        stNode->pstNext = current;
        g_stIPFBasicFreeList = stNode;       
        return;
    }

    prev = g_stIPFBasicFreeList;
    current = g_stIPFBasicFreeList->pstNext;

    while(current != NULL)
    {
        if(stNode->u32FilterID < current->u32FilterID)
        {
            prev->pstNext = stNode;
            stNode->pstNext = current;
            return;
        }
        prev = current;
        current = current->pstNext;
    }
    /* ������� */
    prev->pstNext = stNode;
    stNode->pstNext = NULL;

}

void IPF_AddToExtFreeList(IPF_ID_S* stNode)
{
    IPF_ID_S* current = NULL;    
    IPF_ID_S* prev = NULL;

    current = g_stIPFExtFreeList;

    /* ���freelistΪ�� */
    if(NULL == current)
    {
        g_stIPFExtFreeList = stNode;
        g_stIPFExtFreeList->pstNext = NULL;
        return;
    }

    /* ����ȵ�һ������ID��С */
    if(stNode->u32FilterID < current->u32FilterID)
    {
        stNode->pstNext = current;
        g_stIPFExtFreeList = stNode;       
        return;
    }

    prev = g_stIPFExtFreeList;
    current = g_stIPFExtFreeList->pstNext;

    while(current != NULL)
    {
        if(stNode->u32FilterID < current->u32FilterID)
        {
            prev->pstNext = stNode;
            stNode->pstNext = current;
            return;
        }
        prev = current;
        current = current->pstNext;
    }
    /* ������� */
    prev->pstNext = stNode;
    stNode->pstNext = NULL;

}

/*****************************************************************************
* �� �� ��  : IPF_DeleteAll
*
* ��������  : ɾ�������е����н��
*
* �������  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead���������׵�ַ           
*             
* �������  : ��

* �� �� ֵ  : ��
*
* �޸ļ�¼  :2011��3��30��   ³��  ����
*****************************************************************************/
void IPF_DeleteAll(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead)
{
    IPF_ID_S* pstMove = NULL;
    /* coverity[var_decl] */
    while(IPF_FILTERHEAD < g_stIPFFilterInfo[eFilterChainhead].u32FilterNum)
    {
        pstMove = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
        /* ������uselistɾ�� */
        g_stIPFFilterInfo[eFilterChainhead].pstUseList = pstMove->pstNext;
	
        /* ��ɾ���Ľ����ӵ�freelist�� */ 
        if(IPF_BF_NUM > (pstMove->u32FilterID))
        {
            IPF_AddToBasicFreeList(pstMove); 
        }
        else
        {	
            IPF_AddToExtFreeList(pstMove); 
        }
        g_stIPFFilterInfo[eFilterChainhead].u32FilterNum--;
    }

    /* ���׹�������������Ϊ511��ʹ������Ϊ0 */
    ipf_writel(eFilterChainhead, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET);
    ipf_writel(IPF_TAIL_INDEX, ipf_base_addr_ccore+HI_FLT_CHAIN_OFFSET); 
    ipf_writel(IPF_DISABLE_FILTER, ipf_base_addr_ccore+HI_FLT_RULE_CTRL_OFFSET); 
    BSP_IPF_BackupFilter(eFilterChainhead);
}

/*****************************************************************************
* �� �� ��  : IPF_MallocOneBasicFilter
*
* ��������  : ��freelist�з���һ�����(ȡ����һ�����)
*
* �������  : ��       
*             
* �������  : ��

* �� �� ֵ  : ���ָ��
*
* �޸ļ�¼  : 2011��3��30��   ³��  ����
*
* ˵��      : �ɵ��ú�������֤һ���ܷ��䵽���
*****************************************************************************/
IPF_ID_S* IPF_MallocOneBasicFilter(void)
{
    IPF_ID_S* current = NULL;
    	current = g_stIPFBasicFreeList ;

    if(NULL == current)
    {
        bsp_trace(BSP_LOG_LEVEL_WARNING, BSP_MODU_IPF, "IPF_MallocOneBasicFilter Basic run out\n");
        return NULL;
    }
    g_stIPFBasicFreeList  = g_stIPFBasicFreeList ->pstNext;  

    return current;
}
/*****************************************************************************
* �� �� ��  : IPF_MallocOneExtFilter
*
* ��������  : ��freelist�з���һ�����(ȡ����һ�����)
*
* �������  : ��       
*             
* �������  : ��

* �� �� ֵ  : ���ָ��
*
* �޸ļ�¼  : 2011��3��30��   ³��  ����
*
* ˵��      : �ɵ��ú�������֤һ���ܷ��䵽���
*****************************************************************************/
IPF_ID_S* IPF_MallocOneExtFilter(void)
{
    IPF_ID_S* current = NULL;
    	current = g_stIPFExtFreeList ;

    if(NULL == current)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "IPF_MallocOneExtFilter Ext run out\n");
        return NULL;
    }
    g_stIPFExtFreeList  = g_stIPFExtFreeList ->pstNext;  

    return current;
}

/*****************************************************************************
* �� �� ��  : IPF_AddTailUsedFilter
*
* ��������  : �����ӵ�uselist�Ľ�β
*
* �������  : unsigned char eFilterChainhead ͨ������   
*             IPF_ID_S* stNode             ������Ľ��ָ��
*             
* �������  : ��

* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011��3��30��   ³��  ����
                             2012��11��25�ճ¶����޸�
*****************************************************************************/
void IPF_AddTailUsedFilter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead,IPF_ID_S* stNode)
{
    IPF_ID_S* current = NULL;

    current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
    if(NULL == current)
    {
        g_stIPFFilterInfo[eFilterChainhead].pstUseList = stNode;
        g_stIPFFilterInfo[eFilterChainhead].pstUseList->pstNext = NULL;
        g_stIPFFilterInfo[eFilterChainhead].u32FilterNum = 1;
        return;
    }
	
    /* �����ӵ������β */
    while(current->pstNext != NULL)
    {
        current = current->pstNext;
    }
    current->pstNext = stNode;
    stNode->pstNext = NULL;
    
    g_stIPFFilterInfo[eFilterChainhead].u32FilterNum++;

}

/*****************************************************************************
* �� �� ��  : IPF_AddTailFilterChain
*
* ��������  :�����������õ�Ӳ����
*
* �������  : unsigned int u32LastFilterID, unsigned int u32FilterID, IPF_MATCH_INFO_S* pstMatchInfo
*             
* �������  : ��

* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011��3��30��   ³��  ����
*****************************************************************************/
void IPF_AddTailFilterChain(unsigned int u32LastFilterID, 
	unsigned int u32FilterID, IPF_MATCH_INFO_S* pstMatchInfo)
{
    unsigned int u32Value = 0;
    IPF_MATCH_INFO_S* pstLastMatchInfo = NULL;
    
    /* ����������--���µĹ������������õ������� */
    if(u32FilterID < IPF_BF_NUM)
    {
        ipf_write_basic_filter(u32FilterID, pstMatchInfo);
		
        /*�Ի������������б���*/
        BSP_IPF_BackupFilter(u32FilterID);
    }
    /* ��չ������ */
    else
    {
        memcpy_s((void*)(g_pstExFilterAddr + u32FilterID - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S), pstMatchInfo, sizeof(IPF_MATCH_INFO_S));
    }

    /* �������һ��filter����Ҫ������һ��filter��nextindex�� */
    if(u32LastFilterID != IPF_TAIL_INDEX)
    {
        /* ���ϴ��������һ����������nextIndex���������� */
        if(u32LastFilterID < IPF_BF_NUM)
        {
            ipf_writel(u32LastFilterID, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
            u32Value = ipf_readl(ipf_base_addr_ccore + HI_FLT_CHAIN_OFFSET);
            u32Value = (u32Value&0x1FF0000) + u32FilterID;
            ipf_writel(u32Value, ipf_base_addr_ccore + HI_FLT_CHAIN_OFFSET);
			
            /*���޸�next index�Ļ����������������±���*/
            BSP_IPF_BackupFilter(u32LastFilterID);
        }
        else
        {
            pstLastMatchInfo = g_pstExFilterAddr + u32LastFilterID - IPF_BF_NUM;
            pstLastMatchInfo->unFltChain.Bits.u16NextIndex = u32FilterID;        
        }
    }    
}

/*****************************************************************************
* �� �� ��     : IPF_FindFilterID
*
* ��������  : ��������������Ѱ����PS ID ƥ���Filter ID
*
* �������  : IPF_FILTER_CHAIN_TYPE_E eFilterChainhead    ͨ������
*                           unsigned int u32PsID                PS ID            
*             
* �������  : unsigned int* u32FilterID   ��ѯ����Filter ID

* �� �� ֵ     : IPF_SUCCESS                ��ѯ�ɹ�
*                          IPF_ERROR                  ��ѯʧ��
*
* �޸ļ�¼  :2011��1��11��   ³��  ����
*****************************************************************************/
int IPF_FindFilterID(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32PsID, unsigned int* u32FilterID)
{
    IPF_ID_S* current = NULL;

    current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
    while(current != NULL)
    {
        if(current->u32PsID != u32PsID)
        {
            current = current->pstNext;
        }
        else
        {
            *u32FilterID = current->u32FilterID;
            return IPF_SUCCESS;
        }
    }
    return IPF_ERROR;        
}

int mdrv_ipf_init(IPF_COMMON_PARA_S *pstCommPara)
{
    HI_IPF_CTRL_T ipf_ctrl;
    int chn_schedule_strategy = SCH_ALL_DESC;

    if(NULL == pstCommPara)
    {
    	g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_Init pstCommPara NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF NOT Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    /* ����IPFȫ�ֿ������üĴ��� */
    ipf_ctrl.bits.filter_seq = pstCommPara->bFilterSeq;
    ipf_ctrl.bits.flt_addr_reverse = pstCommPara->bFltAddrReverse;
    ipf_ctrl.bits.sp_cfg = pstCommPara->bSpPriSel;
    ipf_ctrl.bits.sp_wrr_sel = pstCommPara->bSpWrrModeSel;
    ipf_ctrl.bits.max_burst_len = pstCommPara->eMaxBurst;
    ipf_ctrl.bits.ipv6_nh_sel = pstCommPara->bIpv6NextHdSel;
    ipf_ctrl.bits.ah_esp_sel = pstCommPara->bEspAhSel;
    ipf_ctrl.bits.ah_disable = pstCommPara->bAhSpiDisable;
    ipf_ctrl.bits.esp_disable = pstCommPara->bEspSpiDisable;
    ipf_ctrl.bits.mfc_en = pstCommPara->bMultiFilterChainEn;
    ipf_ctrl.bits.mm_en = pstCommPara->bMultiModeEn;
    ipf_ctrl.bits.add_rep = pstCommPara->bAdReport;
    ipf_ctrl.bits.schedule_strategy = chn_schedule_strategy;
	if(g_ipf_ctx.ipf_version >= IPF_VERSION_120a){
    	ipf_ctrl.u32 |= IPF_CD_EN_BIT;
	}
	
    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF, "\r u32IPFCtrl = 0x%x \n", ipf_ctrl.u32);
    ipf_writel(ipf_ctrl.u32, ipf_base_addr_ccore + HI_IPF_CTRL_OFFSET); 

    return  IPF_SUCCESS; 
}


int mdrv_ipf_config_ulchan(IPF_CHL_CTRL_S *pstCtrl)
{
    unsigned int u32ChanCtrl = 0; 
	


    if(NULL == pstCtrl)
    {
 		g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulchan pstCtrl NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r IPF NOT Init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }


    /*��������ͨ�����ƼĴ��� */
    u32ChanCtrl = pstCtrl->eIpfMode | (pstCtrl->bEndian<<2) | 
                            (pstCtrl->bDataChain<<3) | (pstCtrl->u32WrrValue<<16);
    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF,"\r u32ChanCtrl = 0x%x \n", u32ChanCtrl);
    ipf_writel(u32ChanCtrl, ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);  

    return IPF_SUCCESS;
}

int mdrv_ipf_config_dlchan(IPF_CHL_CTRL_S *pstCtrl)
{
    unsigned int u32ChanCtrl = 0; 

    if(NULL == pstCtrl)
    {
 		g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_dlchan pstCtrl NULL! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }
    
    /*��������ͨ�����ƼĴ��� */
    u32ChanCtrl = pstCtrl->eIpfMode | (pstCtrl->bEndian<<2) | 
                            (pstCtrl->bDataChain<<3) | (pstCtrl->u32WrrValue<<16);
    bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_IPF,"\r u32ChanCtrl = 0x%x \n", u32ChanCtrl);
    ipf_writel(u32ChanCtrl, ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);

    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��      : BSP_IPF_ConfigADThr
*
* ��������  : ����������ͨ��ADq���̰���ֵ
*
* �������  : unsigned int u32UlADThr,unsigned int u32DlADThr
* �������  : ��
* �� �� ֵ      : ��
*
* ˵��             : ����������ͨ��ADq���̰���ֵ
*
* �޸ļ�¼  : 2011��12��13��   �¶�������
			 2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			 �޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
int mdrv_ipf_config_adthred (unsigned int u32UlADThr, unsigned int u32DlADThr)
{
    unsigned int u32ADCtrl[IPF_CHANNEL_MAX] = {0,0};
	struct ipf_debug* a_status = (struct ipf_debug*)(IPF_DEBUG_INFO_ADDR);

    if((u32UlADThr == 0)  || (u32UlADThr > 0xFFFF) 
		|| (u32DlADThr == 0)  || (u32DlADThr > 0xFFFF))
    {
 		g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_adthred invlaid para! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init! \n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    u32ADCtrl[IPF_CHANNEL_UP] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ_CTRL_OFFSET);
    u32ADCtrl[IPF_CHANNEL_UP] &= IPF_ADQ_THR_MASK;
    u32ADCtrl[IPF_CHANNEL_UP] |= (u32UlADThr<<16);
	a_status->ad_thred = u32UlADThr;
    /* ��������ͨ����AD��ֵ*/
    ipf_writel(u32ADCtrl[IPF_CHANNEL_UP], ipf_base_addr_ccore + HI_IPF_CH0_ADQ_CTRL_OFFSET);

#ifdef CONFIG_PSAM
	bsp_psam_config_adthred(u32DlADThr);
#else
	u32ADCtrl[IPF_CHANNEL_DOWN] = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_ADQ_CTRL_OFFSET);
	u32ADCtrl[IPF_CHANNEL_DOWN] &= IPF_ADQ_THR_MASK;
	u32ADCtrl[IPF_CHANNEL_DOWN] |= (u32DlADThr<<16);
	/* coverity[var_deref_op] */
	g_ipf_ctx.status->ad_thred = u32DlADThr;
	/* ��������ͨ����AD��ֵ*/
    ipf_writel(u32ADCtrl[IPF_CHANNEL_DOWN], ipf_base_addr_ccore + HI_IPF_CH1_ADQ_CTRL_OFFSET);
#endif
	
    return IPF_SUCCESS;
}
int mdrv_ipf_set_filter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, 
	IPF_FILTER_CONFIG_S *pstFilterInfo, unsigned int u32FilterNum)
{
	unsigned int i = 0;
	IPF_ID_S* current = NULL;
	unsigned int u32LastFilterID = IPF_TAIL_INDEX;
	unsigned int u32FirstFilterID = IPF_TAIL_INDEX;
	unsigned long flags = 0;



	if((eFilterChainhead >= IPF_FILTER_CHAIN_MAX_NUM) || (NULL == pstFilterInfo))
	{
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_set_filter invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

#ifndef CONFIG_IPF_BACKUP_ON_LPM3
    /*����K3V3����������⣬ʹ��ipf ǰ��Ҫ����Ƿ���Ҫ�ָ�������*/
    ipf_check_filter_restore();
#endif

	spin_lock_irqsave(&ipf_filter_spinlock, flags);
#ifndef CONFIG_IPF_BACKUP_ON_LPM3
	bsp_ipc_spin_lock(IPC_SEM_IPF_PWCTRL);
#endif
	/* ����üĴ������׵�ַ��������н�� */
	IPF_DeleteAll(eFilterChainhead);
	udelay(g_filter_delay_time);
		
	/*��������*/
	for(i = 0; i < u32FilterNum; i++)
	{
        /* ��freelist��ȡ��δ���õĹ����� */
		if(!(IPF_SET_EXT_FILTER & (pstFilterInfo->u32FilterID)))
		{    
			current = IPF_MallocOneBasicFilter();
			if(NULL == current)
			{		
				current = IPF_MallocOneExtFilter();
				if(NULL == current)
				{		
				#ifndef CONFIG_IPF_BACKUP_ON_LPM3
					bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
				#endif
					spin_unlock_irqrestore(&ipf_filter_spinlock, flags);
					bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r IPF_MallocOneFilter error! \n");
					return BSP_ERR_IPF_FILTER_NOT_ENOUGH;
				}
			}		
		}
		else
		{
			current = IPF_MallocOneExtFilter();
			if(NULL == current)
			{
			#ifndef CONFIG_IPF_BACKUP_ON_LPM3
				bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
			#endif
				spin_unlock_irqrestore(&ipf_filter_spinlock, flags);
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r IPF_MallocOneFilter error! \n");
				return BSP_ERR_IPF_FILTER_NOT_ENOUGH;
			}
		}
		if(0 == i)
		{
			u32FirstFilterID = current->u32FilterID;
		}
		current->u32PsID = (pstFilterInfo->u32FilterID)&IPF_FILTERTYPE_MASK;
		/* �Ƚ�NextIndex����Ϊ511 */
		pstFilterInfo->stMatchInfo.unFltChain.Bits.u16NextIndex = IPF_TAIL_INDEX;
		IPF_AddTailFilterChain(u32LastFilterID, current->u32FilterID, &pstFilterInfo->stMatchInfo);
		IPF_AddTailUsedFilter(eFilterChainhead, current);
		u32LastFilterID = current->u32FilterID;
		pstFilterInfo++; 
	}
	
	/*�����úõĹ��������ҵ�������*/
	ipf_writel(eFilterChainhead, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET);
	ipf_writel(u32FirstFilterID, ipf_base_addr_ccore+HI_FLT_CHAIN_OFFSET); 
	
	/*���ݸ��ĺ���׹�����*/
	BSP_IPF_BackupFilter(eFilterChainhead);
	cache_sync();


	#ifndef CONFIG_IPF_BACKUP_ON_LPM3
		bsp_ipc_spin_unlock(IPC_SEM_IPF_PWCTRL);
	#endif
	spin_unlock_irqrestore(&ipf_filter_spinlock, flags);

	return IPF_SUCCESS;
}
/*****************************************************************************
* �� �� ��      : BSP_IPF_GetFilter
*
* ��������  : �ṩ��PS��ѯĳ��Filter������Ϣ
*
* �������  : unsigned int u32FilterID   Filter ID��ע�������psid
*             
* �������  : IPF_FILTER_CONFIG_S * pFilterInfo  ��ѯ����Filter��Ϣ

* �� �� ֵ     : IPF_SUCCESS                ��ѯ�ɹ�
*                           IPF_ERROR                  ��ѯʧ��
*                           BSP_ERR_IPF_NOT_INIT       ģ��δ��ʼ��
*                           BSP_ERR_IPF_INVALID_PARA   ��������
*
* �޸ļ�¼  : 2011��1��11��   ³��  ����
                             2011��3��30��   ³��  �޸�
                             2011    11��30��   ³��  �޸�
                             2012    11��26��   �¶����޸�
				 			 2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
							 �޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
int mdrv_ipf_get_filter(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32FilterID, IPF_FILTER_CONFIG_S *pstFilterInfo)
{
    unsigned int u32FindID = 0;
    


    /* ������� */
    if(NULL == pstFilterInfo)
    {
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_get_filter invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

	
#ifndef CONFIG_IPF_BACKUP_ON_LPM3
    /*����K3V3����������⣬ʹ��ipf ǰ��Ҫ����Ƿ���Ҫ�ָ�������*/
    ipf_check_filter_restore();
#endif
    /* ����PS ID ��Ӧ��FilterID*/
    if(IPF_FindFilterID(eFilterChainhead, u32FilterID, &u32FindID) != IPF_SUCCESS)
    {
        return IPF_ERROR;
    }
    pstFilterInfo->u32FilterID = u32FilterID;    
    
    /* ����ǻ��������� */
    if(u32FindID < IPF_BF_NUM)
    {
        /* д���˱������ַ */    
        ipf_writel(u32FindID, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
         
        /* ���������������� */
        memcpy_s(&pstFilterInfo->stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET), sizeof(IPF_MATCH_INFO_S));/* [false alarm]:fortify disable */
    }
    /* ��չ������ */
    else
    {
        /* ���������������� */
        memcpy_s(&pstFilterInfo->stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(g_pstExFilterAddr + u32FindID - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S));
    }
    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��      : IPF_ConfigCD
*
* ��������  : ����CD
*
* �������  : IPF_TTF_MEM_ST *pstTtf, unsigned short* pu16TotalDataLen, unsigned int* pu32BdInPtr
* �������  : ��
* �� �� ֵ      :  ��
*
* �޸ļ�¼  :2011��1��24��   ³��  ����
*****************************************************************************/
int IPF_ConfigCD(void *pstTtf, unsigned short* pu16TotalDataLen, unsigned int* pu32BdInPtr)
{
    unsigned int u32DlCDWptr = 0;
    unsigned int u32DlCDRptr = 0;
    unsigned short u16TotalDataLen = 0;
	unsigned int* header = (unsigned int*)pstTtf;

    /* Ϊ��ֹBD �����ߺ�������Ŀ�ĵ�ַ���ɹ���������ʱcd��λ�� */
    u32DlCDWptr = g_stIpfDl.u32IpfCdWptr;
    u32DlCDRptr = *(g_stIpfDl.u32IpfCdRptr);
    *pu32BdInPtr = (unsigned int)(g_stIpfDl.pstIpfCDQ + (u32DlCDWptr));

    /* ����CD */
    do
    {
        /* �ж��Ƿ��п���CD */
        if(u32DlCDRptr != (u32DlCDWptr+1)%IPF_DLCD_DESC_SIZE)
        {
            g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u32Ptr = (unsigned int)IPF_GET_MEMBLK_BUF(header);
			g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16PktLen = IPF_GET_MEMBLK_LEN(header);
            u16TotalDataLen += IPF_GET_MEMBLK_LEN(header);
            
            /* ��ʶ�Ƿ���� */
            if(IPF_GET_NEXT_MEMBLK(header) != NULL)
            {
                g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16Attribute = 0;
                if(u32DlCDWptr+1 < IPF_DLCD_DESC_SIZE)
                {
                    u32DlCDWptr += 1;
                    header = IPF_GET_NEXT_MEMBLK(header);
                }
                /* δ����ʱ��CD���ܷ�ת�����Ǽ�¼CD��β����ͬʱ����0��ʼ����CD */
                else
                {
                    u32DlCDWptr = 0;
                    u16TotalDataLen = 0;
                    header = (unsigned int*)pstTtf;
                    *pu32BdInPtr = (unsigned int)g_stIpfDl.pstIpfCDQ;
                }
            }
            else
            {
                g_stIpfDl.pstIpfCDQ[u32DlCDWptr].u16Attribute = 1;
                
                /* ����ʱCD���Է�ת */
                u32DlCDWptr = (u32DlCDWptr+1 < IPF_DLCD_DESC_SIZE)?(u32DlCDWptr+1):0;
                break;
            }
        }
        else
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,
                    "\r DownFilter CD FULL ! u32DlCDRptr=%d u32DlCDWptr=%d\n",u32DlCDRptr,u32DlCDWptr);
            return BSP_ERR_IPF_CDQ_NOT_ENOUGH;
        }        
    }while(header != NULL);
    
    g_stIpfDl.u32IpfCdWptr = u32DlCDWptr;
    *pu16TotalDataLen = u16TotalDataLen;    
    return IPF_SUCCESS;
}

int ipf_config_dlbd(unsigned int u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara)
{
    unsigned int u32BdqWptr = 0;
    unsigned int i;
    unsigned int u32BdInPtr = 0;
    unsigned int u32BD = 0;
    unsigned short u16TotalDataLen = 0;
    unsigned int u32TimeStampEn;
    ipf_desc_attr_t bd_attr;
	IPF_DL_S* dl_bd = &g_stIpfDl;
	unsigned long flags = 0;

    /*��μ��*/
    if((NULL == pstDlPara)||(0 == u32Num))
    {
    	g_ipf_ctx.status->invalid_para++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ipf_config_dlbd invalid para\n");
        return BSP_ERR_IPF_INVALID_PARA;
    }

	/* coverity[FORWARD_NULL] */
    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

    /* ���Ccore�Ƿ��ϵ�*/
    if(IPF_FORRESET_CONTROL_FORBID <= BSP_IPF_GetControlFLagForCcoreReset())
    {
    	/* coverity[var_deref_op] */
        g_ipf_ctx.status->mdrv_called_not_init++;
        return BSP_ERR_IPF_CCORE_RESETTING;
    }

#ifndef CONFIG_IPF_BACKUP_ON_LPM3
    /*����K3V3����������⣬ʹ��ipf ǰ��Ҫ����Ƿ���Ҫ�ָ�������*/
    ipf_check_filter_restore();
#endif
    for(i = 0; i < u32Num; i++)
    {
        if(0 == pstDlPara[i].u16Len)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r INPUT BD_Len =0 !Drop pkt \n");
			/* coverity[var_deref_op] */
            g_ipf_ctx.status->bd_len_zero_err++;
            return BSP_ERR_IPF_INVALID_PARA;
        }
    }

    /* ����BDдָ�� */
    u32BdqWptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET);
    u32BD = u32BdqWptr&IPF_DQ_PTR_MASK;
	/* coverity[var_deref_op] */
    u32TimeStampEn = g_ipf_ctx.status->timestamp_en;/*[false alarm]:fortify*/

    for(i = 0; i < u32Num; i++)
    {
        /* ����CD */
        if(IPF_ConfigCD((void*)pstDlPara[i].u32Data, &u16TotalDataLen, &u32BdInPtr) != IPF_SUCCESS)
        {
            g_ipf_ctx.status->cd_not_enough++;
            return BSP_ERR_IPF_CDQ_NOT_ENOUGH;
        }
        bd_attr.u16 = pstDlPara[i].u16Attribute;
        bd_attr.bits.cd_en = ipf_enable;
        dl_bd->pstIpfBDQ[u32BD].u16Attribute = bd_attr.u16; 
        dl_bd->pstIpfBDQ[u32BD].u32InPtr =  u32BdInPtr;
        dl_bd->pstIpfBDQ[u32BD].u16PktLen = u16TotalDataLen;
        dl_bd->pstIpfBDQ[u32BD].u16UsrField1 = pstDlPara[i].u16UsrField1;
        dl_bd->pstIpfBDQ[u32BD].u32UsrField2 = pstDlPara[i].u32UsrField2;
        dl_bd->pstIpfBDQ[u32BD].u32UsrField3 = pstDlPara[i].u32UsrField3;
        ipf_record_start_time_stamp(u32TimeStampEn, &dl_bd->pstIpfBDQ[u32BD].u32UsrField2);
        u32BD = ((u32BD + 1) < IPF_DLBD_DESC_SIZE)? (u32BD + 1) : 0;
		
    }

	spin_lock_irqsave(&ipf_dlbd_spinlock, flags);
    /* ���Ccore�Ƿ��ϵ�*/
    if(IPF_FORRESET_CONTROL_FORBID <= BSP_IPF_GetControlFLagForCcoreReset())
    {
        g_ipf_ctx.status->mdrv_called_not_init++;
		spin_unlock_irqrestore(&ipf_dlbd_spinlock, flags);
        return BSP_ERR_IPF_CCORE_RESETTING;
    }

    g_ipf_ctx.status->cfg_bd_cnt += u32Num;

    /* ����BDдָ�� */
    ipf_writel(u32BD, ipf_base_addr_ccore + HI_IPF_CH1_BDQ_WPTR_OFFSET);  
	spin_unlock_irqrestore(&ipf_dlbd_spinlock, flags);
    return IPF_SUCCESS;
}

int mdrv_ipf_config_dlbd(unsigned int u32Num, IPF_CONFIG_DLPARAM_S* pstDlPara)
{	
	if(ipf_start_addr_limit()){
		//IPF_PRINT("limit func disable\n");
	}
	
	g_ipf_ctx.status->cfg_bd_times++;
	
#ifdef CONFIG_PSAM
	return bsp_psam_config_dlbd(u32Num, pstDlPara);
#else
	return ipf_config_dlbd(u32Num, pstDlPara);
#endif
}


/*****************************************************************************
* �� �� ��     : mdrv_ipf_config_ulad
*
* ��������  : �ýӿڽ���C���ṩ�������ƶ�ADQдָ�룬
				�����е�AD�����µ��ڴ滺������һ�ο��Դ�����AD��
				����ǰҪ��������������仺������
*                           
* �������  : unsigned int u32Num0; 
				 unsigned int u32Num1; 
				 void* psk0; 
				 void* psk1
*
* �������  : ��
* �� �� ֵ      : ��
* �޸ļ�¼  :2012��11��24��   �¶���  ����
			2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			�޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
int mdrv_ipf_config_ulad(IPF_AD_TYPE_E u32AdType, unsigned int  u32AdNum, IPF_AD_DESC_S * pstAdDesc)
{
	unsigned int u32ADQwptr = 0;
	struct tagIPF_AD_DESC_S * pstADDesc = pstAdDesc;
	unsigned int i;

	

	g_ipf_ctx.status->cfg_ad_times++;
	if(NULL == pstAdDesc || u32AdType >= IPF_AD_MAX)
	{
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulad invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }

	
	if(IPF_AD_0 == u32AdType)
	{
		if(u32AdNum >= IPF_ULAD0_DESC_SIZE)
		{
	 		g_ipf_ctx.status->invalid_para++;
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulad input para ERROR! u32AdNum >=IPF_ULAD0_DESC_SIZE\n");
			return BSP_ERR_IPF_INVALID_PARA;
		}
		
		/*����дָ��*/
		u32ADQwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);
		for(i=0; i < u32AdNum; i++)
		{
			if(NULL == (void*)(pstADDesc->u32OutPtr1))
			{
				g_ipf_ctx.status->ad_out_ptr_null[IPF_AD_0]++;
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_ConfigDlAd input u32OutPtr1 NULL! \n");
				return BSP_ERR_IPF_INVALID_PARA;
			}
			g_stIpfUl.pstIpfADQ0[u32ADQwptr].u32OutPtr1 = pstADDesc->u32OutPtr1;
			g_stIpfUl.pstIpfADQ0[u32ADQwptr].u32OutPtr0 = pstADDesc->u32OutPtr0;
			u32ADQwptr = ((u32ADQwptr + 1) < IPF_ULAD0_DESC_SIZE)? (u32ADQwptr + 1) : 0;	
			pstADDesc++;
		}
		g_ipf_ctx.status->cfg_ad_cnt[IPF_AD_0] += u32AdNum;

		/* ����AD0дָ��*/
		ipf_writel(u32ADQwptr, ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);  
	}
	
	else if(IPF_AD_1 == u32AdType)
	{
		if(u32AdNum >= IPF_ULAD1_DESC_SIZE)
		{
	 		g_ipf_ctx.status->invalid_para++;
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_config_ulad input para ERROR! u32AdNum >=IPF_ULAD1_DESC_SIZE\n");
			return BSP_ERR_IPF_INVALID_PARA;
		}
		
		/*����дָ��*/
		u32ADQwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);
		for(i=0; i < u32AdNum; i++)
		{
			if(NULL == (void*)(pstADDesc->u32OutPtr1))
			{
				g_ipf_ctx.status->ad_out_ptr_null[IPF_AD_1]++;
				bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_ConfigDlAd input u32OutPtr1 NULL! \n");
				return BSP_ERR_IPF_INVALID_PARA;
			}
			g_stIpfUl.pstIpfADQ1[u32ADQwptr].u32OutPtr1 = pstADDesc->u32OutPtr1;
			g_stIpfUl.pstIpfADQ1[u32ADQwptr].u32OutPtr0 = pstADDesc->u32OutPtr0;
			u32ADQwptr = ((u32ADQwptr + 1) < IPF_ULAD1_DESC_SIZE)? (u32ADQwptr + 1) : 0;		
			pstADDesc++;
		}
		g_ipf_ctx.status->cfg_ad_cnt[IPF_AD_1] += u32AdNum;

		/* ����AD0дָ��*/
		ipf_writel(u32ADQwptr, ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);  

	}
	return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��     : BSP_IPF_ChannelEnable
*
* ��������  : �ýӿ�����ʹ�ܻ�λIP������������ͨ��
*
* �������  : IPF_CHANNEL_TYPE_E eChanType      ������ͨ����ʶ
*                           int bFlag   ʹ�ܸ�λ��ʶ 
*
* �������  : ��
* �� �� ֵ      : IPF_SUCCESS                ʹ�ܸ�λ�ɹ�
*                            IPF_ERROR                  ʹ�ܸ�λʧ��
*                            BSP_ERR_IPF_INVALID_PARA   ��������
*
* �޸ļ�¼  :2011��1��11��   ³��  ����
			2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			�޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
int mdrv_ipf_enable_chan(IPF_CHANNEL_TYPE_E eChanType, int bFlag)
{
    unsigned int u32ChanEnable = 0;
    unsigned int u32ChanState = 0;
    unsigned int u32Times = 0;
    unsigned int u32ChCtrl = 0;


    /* ������� */
    if(eChanType >= IPF_CHANNEL_MAX)
    {
 		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_enable_chan invalid para\n");
		return BSP_ERR_IPF_INVALID_PARA;
	}

    if(g_ipf_ctx.status && IPF_CCORE_INIT_SUCCESS != g_ipf_ctx.status->init_ok)
    {
    	g_ipf_ctx.status->mdrv_called_not_init++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r ipf not init\n");
        return BSP_ERR_IPF_NOT_INIT;
    }


    /* ͨ��ʹ�� */
    if(bFlag)
    {
        u32ChanEnable = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET);
        u32ChanEnable |= 0x1<<eChanType;
        ipf_writel(u32ChanEnable, ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET);                        
    }
    /* ͨ��ȥʹ�� */
    else
    {
        u32ChanEnable = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET);
        u32ChanEnable &= 0xFFFFFFFF ^ (0x1<<eChanType);
        ipf_writel(u32ChanEnable, ipf_base_addr_ccore + HI_IPF_CH_EN_OFFSET); 
        
        /* ����ֱ��ͨ��״̬Ϊ0 */      
        do
        {
            (void)osl_task_delay(1);
            u32ChanState = ipf_readl(ipf_base_addr_ccore + HI_IPF_EN_STATE_OFFSET);
            u32ChanState &= 0x1<<eChanType;
            u32Times++;
        }while((u32ChanState) && (u32Times < 100)); 
        
        if(100 == u32Times)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,
                       "\r mdrv_ipf_enable_chan disable error u32Times = %d ! \n",u32Times,0,0,0,0,0);
            return IPF_ERROR;
        }
		
        /* ��λ������к�������еĶ�дָ�� */
        if(IPF_CHANNEL_UP == eChanType)
        {
            u32ChCtrl = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET);
            u32ChCtrl |= 0x30; /* ��4��5bit����Ϊ1 */
            ipf_writel(u32ChCtrl, ipf_base_addr_ccore + HI_IPF_CH0_CTRL_OFFSET); 
        }
        else if(IPF_CHANNEL_DOWN == eChanType)
        {
            u32ChCtrl = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET);
            u32ChCtrl |= 0x30; /* ��4��5bit����Ϊ1 */
            ipf_writel(u32ChCtrl, ipf_base_addr_ccore + HI_IPF_CH1_CTRL_OFFSET); 
        }
        else
        {
            return BSP_ERR_IPF_INVALID_PARA;
        }
    }
    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_dlbd_num
*
* ��������  : �ýӿ����ڻ�ȡ���п���BD��CD ��Ŀ
*                           BD ��Χ: 0~63      CD��Χ: 0~1023
* �������  : ��
*
* �������  : ����CD��Ŀ
* �� �� ֵ      : ����BD��Ŀ
*  
* �޸ļ�¼  :2011��11��30��   ³��  ����
			2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			�޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�

*****************************************************************************/
unsigned int ipf_get_dlbd_num (unsigned int* pu32CDNum)
{
    unsigned int u32BdqDepth = 0;
    unsigned int u32IdleBd = 0;
    unsigned int u32IdleCd = 0;
    unsigned int u32IdleCdDown = 0;
    unsigned int u32IdleCdUp = 0;
	

    /* �������BD���� */
    u32BdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_DQ_DEPTH_OFFSET);
    u32BdqDepth = u32BdqDepth & IPF_DQ_DEPTH_MASK;
    u32IdleBd = IPF_DLBD_DESC_SIZE - u32BdqDepth;
    /* �������CD ���� */
    if(*(g_stIpfDl.u32IpfCdRptr) > g_stIpfDl.u32IpfCdWptr)
    {
        u32IdleCd = *(g_stIpfDl.u32IpfCdRptr) - g_stIpfDl.u32IpfCdWptr - 1;
    }
    else
    {
        u32IdleCdUp = (*(g_stIpfDl.u32IpfCdRptr) > 1)?(*(g_stIpfDl.u32IpfCdRptr) - 1):0;
        u32IdleCdDown = IPF_DLCD_DESC_SIZE -  g_stIpfDl.u32IpfCdWptr - 1;
        u32IdleCd = (u32IdleCdUp > u32IdleCdDown)? u32IdleCdUp:u32IdleCdDown;
    }
    g_stIpfDl.u32IdleBd = u32IdleBd;
    *pu32CDNum = u32IdleCd;

    if(0 == u32IdleBd)
	{
		g_ipf_ctx.status->bd_full++;
	}
    return u32IdleBd;
}

unsigned int mdrv_ipf_get_dlbd_num (unsigned int* pu32CDNum)
{
	g_ipf_ctx.status->get_bd_num_times++;
#ifdef CONFIG_PSAM
	return bsp_psam_get_dlbd_num(pu32CDNum);
#else
	return ipf_get_dlbd_num(pu32CDNum);
#endif
}

/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_dlrd_num
*
* ��������  : �ýӿ����ڶ�ȡ����RD��Ŀ
*
* �������  : ��
*   
* �������  : ��
*
* �� �� ֵ     : ����RD��Ŀ
*
* �޸ļ�¼  :2013��8��1��   chendongyue  ����
*****************************************************************************/
unsigned int mdrv_ipf_get_dlrd_num(void)
{
    unsigned int u32RdqDepth = 0;

    /* ��ȡRD��� */
    u32RdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH1_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
    return u32RdqDepth;
}

/*****************************************************************************
* �� �� ��     : BSP_IPF_RegisterWakeupUlCb
*
* ��������  : �ýӿ�����ע������PS����ص�����
*                           
* �������  : BSP_IPF_WakeupUlCb *pFnWakeupUl
*
* �������  : ��
* �� �� ֵ      : ��
*  
* �޸ļ�¼  :2011��11��30��   ³��  ����
*****************************************************************************/
int ipf_register_wakeup_ulcb(BSP_IPF_WakeupUlCb pFnWakeupUl)
{
    /* ������� */
    if(NULL == pFnWakeupUl)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_RegisterWakeupUlCb inputPara ERROR! \n");
        return BSP_ERR_IPF_INVALID_PARA;
    }
    g_stIpfUl.pFnUlIntCb = pFnWakeupUl;
    return IPF_SUCCESS;
}

/*****************************************************************************
* �� �� ��     : BSP_IPF_RegisterAdqEmptyUlCb
*
* ��������  : �˽ӿ�ֻ��C���ṩ������ע�ỽ������PS��
                             ADQ���пջص�����
*                           
* �������  : BSP_IPF_AdqEmptyCb pFnWakeupUl
*
* �������  : ��
* �� �� ֵ      : IPF_SUCCESS ע��ɹ�
*                            IPF_ERROR	ע��ʧ��
* �޸ļ�¼  :2012��11��24��   �¶���  ����
*****************************************************************************/
int ipf_register_adq_empty_ulcb(BSP_IPF_AdqEmptyUlCb pAdqEmptyUl)
{
    /* ������� */
    if(NULL == pAdqEmptyUl)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r BSP_IPF_RegisterAdqEmptyUlCb inputPara ERROR! \n");
        return IPF_ERROR;
    }
    g_stIpfUl.pAdqEmptyUlCb = pAdqEmptyUl;
    return IPF_SUCCESS;
}

int ipf_rd_rate(unsigned int enable, IPF_CHANNEL_TYPE_E eChnType)
{	
	unsigned int rate = 0;
	unsigned int rd_len = 0;
	unsigned int rd_ts =  0;
	unsigned int ratio = IPF_LEN_RATIO / (IPF_TIMER_RATIO * 8);
	
	if(!enable) {
		return IPF_ERROR;
	}

	if(eChnType > IPF_CHANNEL_DOWN){
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"eChnType err!\n");/* [false alarm]:fortify disable */
		return IPF_ERROR;
	}
	
	switch(eChnType)
    {
        case IPF_CHANNEL_UP:			
			rd_ts =  bsp_get_slice_value() - g_ipf_ctx.status->rd_ts;
			if(rd_ts < IPF_RD_TMOUT) {
				return IPF_ERROR;
			}
			
			rd_len = g_ipf_ctx.status->rd_len_update - g_ipf_ctx.status->rd_len;
			g_ipf_ctx.status->rd_ts = bsp_get_slice_value();
			g_ipf_ctx.status->rd_len = g_ipf_ctx.status->rd_len_update;
			break;
		default:
            break;
	}
	
	if(rd_len <= 0 || rd_ts <= 0) {
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ipf rd len or ts err!\n");
		return IPF_ERROR;
	} else {
		rate = rd_len / (rd_ts * ratio);
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"ipf rd rate:%uMbps\n", rate);
	}
	
	return IPF_SUCCESS;
}
int mdrv_ipf_register_ops(struct mdrv_ipf_ops *ops)
{
	if(ops)
	{
		if(ipf_register_wakeup_ulcb(ops->rx_complete_cb)!= IPF_SUCCESS)
			return IPF_ERROR;
		if(ipf_register_adq_empty_ulcb(ops->adq_empty_cb)!= IPF_SUCCESS)
			return IPF_ERROR;
	}
	return IPF_SUCCESS;
}

static inline void ipf_pm_print_packet(void *buf, unsigned int len)
{
	if (g_ipf_ctx.status->resume_with_intr){

		if (len > 64) {
			len = 64;
		}
		bsp_pm_log(PM_OM_CIPF, len, buf);
		g_ipf_ctx.status->resume_with_intr = 0;
	}
	return;
}

/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_ulrd
*
* ��������  : �ýӿ����ڶ�ȡ����BD, ֧��һ�ζ�ȡ���BD
*
* �������  : unsigned int* pu32Num    
*                           IPF_RD_DESC_S *pstRd
*   
* �������  : unsigned int* pu32Num    ʵ�ʶ�ȡ��RD��Ŀ
*
* �� �� ֵ     : IPF_SUCCESS               �����ɹ�
*                           IPF_ERROR                   ����ʧ��
*
* �޸ļ�¼  :2011��11��30��   ³��  ����
*****************************************************************************/
void mdrv_ipf_get_ulrd(unsigned int* pu32Num, IPF_RD_DESC_S *pstRd)
{
    unsigned int u32RdqRptr = 0;
    unsigned int u32RdqDepth = 0;
    unsigned int u32Num = 0;
    unsigned int i = 0;
    unsigned int u32TimeStampEn;
	unsigned int rd_rate_en;
	
	if(ipf_start_addr_limit()){
		//IPF_PRINT("limit func disable\n");
	}
	
    /* ��ȡRD��� */
    u32RdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
    u32Num = (u32RdqDepth < *pu32Num)?u32RdqDepth:*pu32Num;

	g_ipf_ctx.status->get_rd_times++;
    if(0 == u32Num)
    {
        *pu32Num = 0;
        return;
    }

    u32TimeStampEn = g_ipf_ctx.status->timestamp_en;
	rd_rate_en = g_ipf_ctx.status->rate_en;

    /* ��ȡRD��ָ�� */
    u32RdqRptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RPTR_OFFSET);
    for(i = 0; i < u32Num; i++)
    {        
        /* ��ȡRD */
        pstRd[i].u16Attribute = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16Attribute;
        pstRd[i].u16PktLen = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16PktLen;
        pstRd[i].u16Result = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16Result;
        pstRd[i].u32InPtr = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32InPtr;
        pstRd[i].u32OutPtr = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32OutPtr;
        pstRd[i].u16UsrField1 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u16UsrField1;
        pstRd[i].u32UsrField2 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField2;
        pstRd[i].u32UsrField3 = g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField3;
        ipf_record_end_time_stamp(u32TimeStampEn, g_stIpfUl.pstIpfRDQ[u32RdqRptr].u32UsrField2);

		ipf_pm_print_packet((void*)pstRd[i].u32OutPtr, pstRd[i].u16PktLen);
        /* ����RD��ָ�� */
        u32RdqRptr = ((u32RdqRptr+1) < IPF_ULRD_DESC_SIZE)?(u32RdqRptr+1):0;
		
		g_ipf_ctx.status->rd_len_update += pstRd[i].u16PktLen;

		pstRd[i].u16PktLen > (g_ipf_ctx.status->ad_thred)? g_ipf_ctx.status->get_rd_cnt[IPF_AD_1]++:\
							   		  g_ipf_ctx.status->get_rd_cnt[IPF_AD_0]++;
    }

	ipf_rd_rate(rd_rate_en, IPF_CHANNEL_UP);
    ipf_writel(u32RdqRptr, ipf_base_addr_ccore + HI_IPF_CH0_RDQ_RPTR_OFFSET);

    *pu32Num = u32Num;
}


/*****************************************************************************
* �� �� ��       : mdrv_ipf_get_ulad_num
*
* ��������  : �ýӿ�ֻ��C���ṩ����ȡ���У�C�ˣ�����AD��Ŀ
*
* �������  :BSP_OK����������
                            BSP_ERROR������
*             
* �������  : ��
* �� �� ֵ     : ��
* �޸ļ�¼  : 2011��11��24��   �¶���  ����
			2014��1��23��v1.01 �¶��� �޸� ����K3V3����������⣬
			�޷���m3�Ͻ��е͹��Ļָ����ƶ���A9�Ͻ��С�
*****************************************************************************/
int mdrv_ipf_get_ulad_num(unsigned int* pu32AD0Num,unsigned int* pu32AD1Num)
{
	unsigned int u32UlAdDepth = 0;
	unsigned int u32UlAdwptr = 0;
	unsigned int u32UlAdrptr = 0;



	g_ipf_ctx.status->get_ad_num_times++;
	/*��μ��*/
	if((NULL == pu32AD0Num)||(NULL == pu32AD1Num))
	{
		g_ipf_ctx.status->invalid_para++;
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF,"\r mdrv_ipf_get_ulad_num pstCtrl NULL! \n");
		return BSP_ERR_IPF_INVALID_PARA;
	}
	/* �������AD���� */
	u32UlAdwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_WPTR_OFFSET);
	u32UlAdrptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ0_RPTR_OFFSET);
	if (u32UlAdwptr >= u32UlAdrptr)/*дָ����ǰ������˳��*/
	{
		u32UlAdDepth = IPF_ULAD0_DESC_SIZE - (u32UlAdwptr - u32UlAdrptr);
	}
	else
	{
		u32UlAdDepth =  u32UlAdrptr -u32UlAdwptr;
	}
	*pu32AD0Num = u32UlAdDepth;

	/*�۳�reserve ad�����ڷ�ֹӲ����ad������ʶ��ɿպ͵͹��������ڴ�й¶*/	
	if(u32UlAdDepth > IPF_ADQ_RESERVE_NUM)
	{
		*pu32AD0Num = u32UlAdDepth - IPF_ADQ_RESERVE_NUM;
	}
	else
	{
		*pu32AD0Num = 0;
	}

	u32UlAdwptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_WPTR_OFFSET);
	u32UlAdrptr = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_ADQ1_RPTR_OFFSET);
	if (u32UlAdwptr >= u32UlAdrptr)/*дָ����ǰ������˳��*/
	{
		u32UlAdDepth = IPF_ULAD1_DESC_SIZE - (u32UlAdwptr - u32UlAdrptr);
	}
	else
	{
		u32UlAdDepth =  u32UlAdrptr - u32UlAdwptr;
	}
	
	/*�۳�reserve ad�����ڷ�ֹӲ����ad������ʶ��ɿպ͵͹��������ڴ�й¶*/
	if(u32UlAdDepth > IPF_ADQ_RESERVE_NUM)
	{
		*pu32AD1Num = u32UlAdDepth - IPF_ADQ_RESERVE_NUM;
	}
	else
	{
		*pu32AD1Num = 0;
	}

	return IPF_SUCCESS;
}


/*****************************************************************************
* �� �� ��     : mdrv_ipf_get_ulrd_num
*
* ��������  : �ýӿ����ڶ�ȡ����RD��Ŀ
*
* �������  : ��
*   
* �������  : ��
*
* �� �� ֵ     : ����RD��Ŀ
*
* �޸ļ�¼  :2012��2��16��   ³��  ����
*****************************************************************************/
unsigned int mdrv_ipf_get_ulrd_num(void)
{
    unsigned int u32RdqDepth = 0;
	g_ipf_ctx.status->get_rd_num_times++;  
    /* ��ȡRD��� */
    u32RdqDepth = ipf_readl(ipf_base_addr_ccore + HI_IPF_CH0_DQ_DEPTH_OFFSET);
    u32RdqDepth = (u32RdqDepth>>16)&IPF_DQ_DEPTH_MASK;
    return u32RdqDepth;
}

int mdrv_ipf_set_dbuf_para(unsigned int bufoffset, 
							unsigned int lenoffset, unsigned int nextoffset)
{
	memblk_offset.bufoffset = bufoffset;
	memblk_offset.lenoffset = lenoffset;
	memblk_offset.nextoffset = nextoffset;
	
	return 0;
}
/*****************************************************************************
* �� �� ��       : BSP_IPF_SwitchInt
*
* ��������  : �ṩ�ĵ͹��Ľӿڣ� ���ϱ���A�˵��ж�ͬʱ�ϱ���C ��
*
* �������  : 1   �ϱ���C��
*                           0  ���ϱ���C��
*             
* �������  : ��
* �� �� ֵ     : ��
* �޸ļ�¼  : 2011��2��14��   ³��  ����
*****************************************************************************/
void BSP_IPF_SwitchInt(int bFlag)
{
	unsigned int u32IntMask0 = 0;

	if(bFlag == 1)
	{
    	u32IntMask0 = IPF_INT_OPEN0 | IPF_INT_OPEN1;
		g_u32IpfSwitchInt = 1;
	}
	else
	{
		u32IntMask0 = IPF_INT_OPEN0;
		g_u32IpfSwitchInt = 0;
	}
    ipf_writel(u32IntMask0, ipf_base_addr_ccore + HI_IPF_INT_MASK0_OFFSET);
}

/*****************************************************************************
* �� �� ��  : bsp_ipf_usefilterinfo
*
* ��������  : �ṩ��debug�ӿڣ���ȡ�Ѿ�ʹ�õ�filter��
*
* �������  : IPF_CHANNEL_TYPE_E eChnType  ͨ������
*             
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011��1��11��   ³��  ����
                             2011��3��30��   ³��  �޸�
*****************************************************************************/
void bsp_ipf_usefilterinfo(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead)
{
    IPF_ID_S* current = NULL;
    unsigned int u32FilterNum = 0;
/*    int s32GetChar = 0;*/
    
    u32FilterNum = g_stIPFFilterInfo[eFilterChainhead].u32FilterNum;
    current = g_stIPFFilterInfo[eFilterChainhead].pstUseList;
	
    IPF_PRINT("Total Filter Num = %u\n",u32FilterNum);            
    IPF_PRINT("=============================\n");

    while(u32FilterNum)
    { 
        while(u32FilterNum)
        {
            if(1 == u32FilterNum)
            {
                IPF_PRINT("Filter ID = %d,    PS ID = %d\n    ,Next HWID = %d\n",current->u32FilterID, current->u32PsID, current->pstNext->u32FilterID);            
                u32FilterNum--;
            }
            else
            {
                IPF_PRINT("Filter ID = %d,    PS ID = %d\n    ,Next HWID = %d\n",current->u32FilterID, current->u32PsID, current->pstNext->u32FilterID);            
                current = current->pstNext;
                u32FilterNum--;
            }
        }
    }
    IPF_PRINT("*****************************\n");

}

/*****************************************************************************
* �� �� ��  : BSP_IPF_FreeFilterInfo
*
* ��������  : �ṩ��debug�ӿڣ���ȡδʹ�õ�filter��
*
* �������  : IPF_CHANNEL_TYPE_E eChnType  ͨ������
*             
* �������  : ��
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2011��1��11��   ³��  ����
*
*****************************************************************************/
void bsp_ipf_basicfreefilterinfo(void)
{
    IPF_ID_S* current = NULL;
/*    int s32GetChar = 0;*/

    current = g_stIPFBasicFreeList;

    IPF_PRINT("============================\n");

    while(current != NULL)
    {
        while(current != NULL)
        {
            IPF_PRINT("Filter ID:      %d\n",current->u32FilterID);
            current = current->pstNext; 
        }
    }
    IPF_PRINT("*****************************\n");    
}
void bsp_ipf_extfreefilterinfo(void)
{
    IPF_ID_S* current = NULL;
/*    int s32GetChar = 0;*/

    current = g_stIPFExtFreeList;

    IPF_PRINT("============================\n");

    while(current != NULL)
    {
        while(current != NULL)
        {
            IPF_PRINT("Filter ID:      %d\n",current->u32FilterID);
            current = current->pstNext; 
        }
    }
    IPF_PRINT("*****************************\n");    
}

void bsp_ipf_filterinfohwid(unsigned int u32Num)
{
    IPF_MATCH_INFO_S stMatchInfo; 
    
    if(u32Num < IPF_BF_NUM)
    {
         /* д���˱������ַ */    
        ipf_writel(u32Num, ipf_base_addr_ccore + HI_BFLT_INDEX_OFFSET); 
         
        /* ���������������� */
        memcpy_s(&stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET), sizeof(IPF_MATCH_INFO_S));/* [false alarm]:fortify disable */
    }
    else
    {
        memcpy_s(&stMatchInfo, sizeof(IPF_MATCH_INFO_S), (void*)(g_pstExFilterAddr + u32Num - IPF_BF_NUM), sizeof(IPF_MATCH_INFO_S));
    }

    IPF_PRINT("============================\n");
    IPF_PRINT("src ADDR0 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[0], stMatchInfo.u8SrcAddr[1], stMatchInfo.u8SrcAddr[2], stMatchInfo.u8SrcAddr[3]);
    IPF_PRINT("src ADDR1 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[4], stMatchInfo.u8SrcAddr[5], stMatchInfo.u8SrcAddr[6], stMatchInfo.u8SrcAddr[7]);
    IPF_PRINT("src ADDR2 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[8], stMatchInfo.u8SrcAddr[9], stMatchInfo.u8SrcAddr[10], stMatchInfo.u8SrcAddr[11]);
    IPF_PRINT("src ADDR3 : %x.%x.%x.%x\n", stMatchInfo.u8SrcAddr[12], stMatchInfo.u8SrcAddr[13], stMatchInfo.u8SrcAddr[14], stMatchInfo.u8SrcAddr[15]);
    IPF_PRINT("dst ADDR0 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[0], stMatchInfo.u8DstAddr[1], stMatchInfo.u8DstAddr[2], stMatchInfo.u8DstAddr[3]);
    IPF_PRINT("dst ADDR1 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[4], stMatchInfo.u8DstAddr[5], stMatchInfo.u8DstAddr[6], stMatchInfo.u8DstAddr[7]);
    IPF_PRINT("dst ADDR2 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[8], stMatchInfo.u8DstAddr[9], stMatchInfo.u8DstAddr[10], stMatchInfo.u8DstAddr[11]);
    IPF_PRINT("dst ADDR3 : %x.%x.%x.%x\n", stMatchInfo.u8DstAddr[12], stMatchInfo.u8DstAddr[13], stMatchInfo.u8DstAddr[14], stMatchInfo.u8DstAddr[15]);
    IPF_PRINT("SrcPortLo : %d  SrcPortHi: %d\n", stMatchInfo.unSrcPort.Bits.u16SrcPortLo, stMatchInfo.unSrcPort.Bits.u16SrcPortHi);
    IPF_PRINT("DstPortLo : %d  DstPortHi: %d\n", stMatchInfo.unDstPort.Bits.u16DstPortLo, stMatchInfo.unDstPort.Bits.u16DstPortHi);
    IPF_PRINT("TrafficClass :      %d\n", stMatchInfo.unTrafficClass.u32TrafficClass);
    IPF_PRINT("TrafficClassMsk :  %d\n", stMatchInfo.u32LocalAddressMsk);
    IPF_PRINT("Protocol :          %d\n", stMatchInfo.unNextHeader.u32Protocol);
    IPF_PRINT("FlowLable :         %d\n", stMatchInfo.u32FlowLable);
    IPF_PRINT("Type :        %d  Code: %d\n", stMatchInfo.unFltCodeType.Bits.u16Type, stMatchInfo.unFltCodeType.Bits.u16Code);
    IPF_PRINT("NextIndex : %d  FltPri: %d\n", stMatchInfo.unFltChain.Bits.u16NextIndex, stMatchInfo.unFltChain.Bits.u16FltPri);
    IPF_PRINT("FltSpi :             %d\n", stMatchInfo.u32FltSpi);
    IPF_PRINT("FltRuleCtrl :        %x\n", stMatchInfo.unFltRuleCtrl.u32FltRuleCtrl);    
    IPF_PRINT("============================\n");
}

void bsp_ipf_filterinfopsid(IPF_FILTER_CHAIN_TYPE_E eFilterChainhead, unsigned int u32Num)
{
    unsigned int u32FindID = 0;
    
    /* ����PS ID ��Ӧ��FilterID*/
    if(IPF_FindFilterID(eFilterChainhead, u32Num, &u32FindID) != IPF_SUCCESS)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_IPF, "\r cannot find filter ID! \n");
        return ;
    }
    IPF_PRINT("HWID is %d",u32FindID);
    bsp_ipf_filterinfohwid(u32FindID);
}

/*****************************************************************************
* �� �� ��     : BSP_IPF_BackupFilter
*
* ��������  : ���ݻ�����������DDR
*
* �������  : ������ID
*   
* �������  : ��
*
* �� �� ֵ     : ��
*
* �޸ļ�¼  :2013��5��16��   �¶���  ����
*****************************************************************************/
void BSP_IPF_BackupFilter(unsigned int u32FilterID)
{
    unsigned int j;	
    unsigned int* match_info_addr = (unsigned int *)(IPF_PWRCTL_BASIC_FILTER_ADDR + u32FilterID*sizeof(IPF_MATCH_INFO_S));

    for(j=0; j<(sizeof(IPF_MATCH_INFO_S)/4); j++)
    {
        *match_info_addr = ipf_readl((ipf_base_addr_ccore+HI_FLT_LOCAL_ADDR0_OFFSET+j*4)); 
        match_info_addr++;

    }
}

#ifdef __cplusplus
}
#endif

/*lint -restore*/

