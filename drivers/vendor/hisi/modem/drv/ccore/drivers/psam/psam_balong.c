/*************************************************************************
*   ��Ȩ����(C) 1987-2014, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  psam_balong.c
*
*   ��    �� :  longyi
*
*   ��    �� :  ʵ��psam�ĳ�ʼ����cipher�Ľӿ�
*
*   �޸ļ�¼ :  2014��8��19��  v1.00  longyi  ����
*                 
*************************************************************************/

#include "osl_malloc.h"
#include "osl_bio.h"
#include "osl_irq.h"
#include <of.h>
#include <bsp_clk.h>
#include <bsp_dump.h>
#include "psam_balong.h"

struct tagpsam_global_var psam_dl;

void psam_help(void)
{
	unsigned int tmp = 0;
	
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"psam_bd_info	 	 	PSAM ��ֱͨlbdq ����bd ��������Ϣ\n");
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"psam_all_bd_Info	 	PSAM ��ֱͨlbdq ����bd ��������Ϣ\n\n");

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"********PSAM ��ֱͨlbdq ������Ϣ\n");
	psam_dl.lbdq_desc.vir_addr = readl(psam_dl.regbase + HI_PSAM_LBDQ_BADDR_OFFSET);
	psam_dl.lbdq_desc.phy_addr = readl(psam_dl.regbase + HI_PSAM_LBDQ_BADDR_OFFSET);
	psam_dl.lbdq_desc.len = readl(psam_dl.regbase + HI_PSAM_LBDQ_SIZE_OFFSET);
	psam_dl.lbdq_desc.cur_rd_p = readl(psam_dl.regbase + HI_PSAM_LBDQ_RPTR_OFFSET);
	psam_dl.lbdq_desc.cur_wt_p = readl(psam_dl.regbase + HI_PSAM_LBDQ_WPTR_OFFSET);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"lbdq vir addr is 			0x%x\n",psam_dl.lbdq_desc.vir_addr);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"lbdq phy addr is 			0x%x\n",psam_dl.lbdq_desc.phy_addr);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"lbdq len is 				%d\n",psam_dl.lbdq_desc.len);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"lbdq write index is 		%d\n",psam_dl.lbdq_desc.cur_wt_p);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"lbdq read index is 		%d\n\n",psam_dl.lbdq_desc.cur_rd_p);

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"********PSAM ��ֱͨlbdq ��ǰ�ա���״̬\n");
	tmp = readl(psam_dl.regbase + HI_PSAM_LBDQ_STAT_OFFSET);
	if(tmp & DESC_EMPTY)
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"��ֱͨLBDQ empty\n");
	
	if(tmp & DESC_FULL)
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"��ֱͨLBDQ full\n\n");

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"********PSAM ��ֱͨlbdq ����ͳ�Ƽ���\n");
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"lBD���ж�ͳ��: 			%d\n", psam_dl.dllbd_empty);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"lBD���ж�ͳ��: 			%d\n\n", psam_dl.dllbd_full);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"cds cfg lbd over idlebd: 	%d\n\n", psam_dl.over_idlebd);

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"********PSAM ����IBD����������\n");
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"����IBD����������: 		%d\n\n",\
		readl(psam_dl.regbase + HI_PSAM_IBDQ_PKT_CNT_OFFSET)); 

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"********PSAM �ӿ���Ϣͳ��\n");
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"��ֱͨ����bd�ɹ�����: 	%d\n",psam_dl.cfg_desc_debug.cfg_suc_cnt);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"����bdʧ�ܴ���: 			%d\n",psam_dl.cfg_desc_debug.cfg_fail_cnt);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"bd����Ϊ�����: 			%d\n",psam_dl.cfg_desc_debug.dlbd_len_zero_cnt);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"����cd ΪNULL����: 		%d\n",psam_dl.cfg_desc_debug.cd_num_p_empty);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"����dl_para ΪNULL����: 	%d\n",psam_dl.cfg_desc_debug.cfg_dl_para_null);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"����lbd Ϊ0����: 			%d\n",psam_dl.cfg_desc_debug.cfg_lbd_num_zero);
	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"cd Ϊ�մ���: 				%d\n",psam_dl.cfg_desc_debug.dlcd_empty);

	bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"psam��ʼ����û�еõ�cipher�Ĳ���: %d\n",psam_dl.init_af_ci_para);
}

int psam_bd_info(unsigned int bdq_ptr)
{    
    unsigned int cd_ptr;

    if(bdq_ptr >= PSAM_DLBD_DESC_SIZE)
    {
        return -1;
    }
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"==========BD Info=========\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"BDλ��:         %d\n",bdq_ptr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16Attribute:   %d\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u16Attribute);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16PktLen:      %d\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u16PktLen);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u32InPtr:       0x%x\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u32InPtr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u32OutPtr:      0x%x\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u32OutPtr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16Resv:        %d\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u16Result);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16UsrField1:   %d\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u16UsrField1);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u32UsrField2:   0x%x\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u32UsrField2);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u32UsrField3:   0x%x\n",psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u32UsrField3);
	
	cd_ptr = psam_dl.g_psam_dl.psam_bdq[bdq_ptr].u32InPtr-(unsigned int)psam_dl.ipf_para.dlcdq;
    cd_ptr = cd_ptr/sizeof(IPF_CD_DESC_S);
#if 0
    while((psam_dl.ipf_para.dlcdq[cd_ptr].u16Attribute != 1) && (cd_ptr < IPF_DLCD_DESC_SIZE-1))//cd not end
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"==========CD Info=========\n");
	    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"CDλ��(CD header):  %d\n",cd_ptr);
	    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16Attribute:       %d\n",psam_dl.ipf_para.dlcdq[cd_ptr].u16Attribute);
	    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16PktLen:          %d\n",psam_dl.ipf_para.dlcdq[cd_ptr].u16PktLen);
	    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u32Ptr:             0x%x\n",psam_dl.ipf_para.dlcdq[cd_ptr].u32Ptr);  
        cd_ptr = ((cd_ptr+1) < IPF_DLCD_DESC_SIZE)?(cd_ptr+1):0;
    };
#else
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"==========CD Info=========\n");
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"CDλ��(CD header):  %d\n",cd_ptr);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16Attribute:       %d\n",psam_dl.ipf_para.dlcdq[cd_ptr].u16Attribute);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u16PktLen:          %d\n",psam_dl.ipf_para.dlcdq[cd_ptr].u16PktLen);
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"u32Ptr:             0x%x\n",psam_dl.ipf_para.dlcdq[cd_ptr].u32Ptr);  
#endif

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"************************\n");

	return 0;
}

int psam_all_bd_Info(void)
{
    unsigned int i;
    for(i = 0;i < PSAM_DLBD_DESC_SIZE;i++)
    {
        psam_bd_info(i);
    }
    return 0;
}

static int psam_get_dts(void)
{
	struct device_node *dev = NULL;
	static unsigned int init_flag = 0;
	const char *name_psam = "hisilicon,psam_balong_mdm";
	if(!init_flag){
	 	dev = of_find_compatible_node(NULL, NULL, name_psam);
		if(NULL == dev)
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"device node not found\n");
			return -EINVAL;
		}
	    psam_dl.regbase = (unsigned int)of_iomap(dev, 0);
		if(psam_dl.regbase == 0)
		{
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"psam ccore dts regaddr error\n");
			return -EINVAL;
		}

		(void)of_property_read_u32_array(dev, "addr_limit", &(psam_dl.addr_limit), 1);

		init_flag = 1;
	}
	return 0;
}

int psam_srset(void)
{
	unsigned int count = 10000;
	unsigned int reg_v = 1;

	writel(reg_v, psam_dl.regbase + HI_PSAM_SRST_OFFSET);
	while(reg_v & PSAM_SRST_BIT){
		reg_v = readl(psam_dl.regbase + HI_PSAM_SRST_OFFSET);
		if(count == 0){
			return -EINVAL;
		}
		count--;
	}
	return 0;
}

/*init just ccore*/
int psam_reinit_regs(void)
{
	if(psam_dl.regbase == 0)
		return -EINVAL;
	
	psam_set_crdq_ctrl(IPF_MODEM0_DLFC);
	
	writel(IPF_DLBD_MEM_ADDR, psam_dl.regbase + HI_PSAM_IBDQ_BADDR_OFFSET);
	writel(IPF_DLBD_DESC_SIZE-1, psam_dl.regbase + HI_PSAM_IBDQ_SIZE_OFFSET);

	//rd,wr pointer addresses
	writel(psam_dl.ipf_para.dlbdq_wptr_addr, psam_dl.regbase + HI_PSAM_IBDQ_WPTR_ADDR_OFFSET);
	writel(psam_dl.ipf_para.dlbdq_rptr_addr, psam_dl.regbase + HI_PSAM_IBDQ_RPTR_ADDR_OFFSET);

	//LBDQ
	writel((unsigned int)psam_dl.g_psam_dl.psam_bdq, psam_dl.regbase + HI_PSAM_LBDQ_BADDR_OFFSET);
	writel(PSAM_DLLBD_DESC_SIZE-1, psam_dl.regbase + HI_PSAM_LBDQ_SIZE_OFFSET);
	
	writel(0, psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);

	writel(psam_dl.ciphers_para.cbdq_config, psam_dl.regbase + HI_PSAM_CBDQ_CONFIG_OFFSET);
	writel(psam_dl.ciphers_para.cbdq_baddr, psam_dl.regbase + HI_PSAM_CBDQ_BADDR_OFFSET);
	writel(psam_dl.ciphers_para.cbdq_size - 1, psam_dl.regbase + HI_PSAM_CBDQ_SIZE_OFFSET);
	writel(psam_dl.ciphers_para.cbdq_wptr_addr, psam_dl.regbase + HI_PSAM_CBDQ_WPTR_ADDR_OFFSET);
	/*psam_crdq_baddr cipher config by itself, psam don`t care*/
	writel(psam_dl.ciphers_para.crdq_rptr_addr, psam_dl.regbase + HI_PSAM_CRDQ_RPTR_ADDR_OFFSET);

	writel(1, psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);

	/*psam enable: acore disable and ccore enable*/
	writel(1, psam_dl.regbase + HI_PSAM_EN_OFFSET);

	return 0;
}

/*lint -save -e69*/
int psam_set_crdq_ctrl(unsigned int cipher_fc_head)
{
	HI_PSAM_CRDQ_CTRL_T fc_head;
	
	if(cipher_fc_head >= IPF_MODEM_MAX)
		return -EINVAL; 
	
	fc_head = (HI_PSAM_CRDQ_CTRL_T)readl(psam_dl.regbase + HI_PSAM_CRDQ_CTRL_OFFSET);
	fc_head.bits.fc_head = cipher_fc_head;

	writel(fc_head.u32, psam_dl.regbase + HI_PSAM_CRDQ_CTRL_OFFSET);
	
	return 0; 
}

static void psam_cipher_ch_en(unsigned int ch_en)
{
	HI_PSAM_CIPHER_CH_EN_T cipher_ch_en;
	
	cipher_ch_en = (HI_PSAM_CIPHER_CH_EN_T)readl(psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);
	cipher_ch_en.bits.cipher_ch_en = ch_en;

	writel(cipher_ch_en.u32, psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);
}
/*lint -restore*/

unsigned int psam_get_crdq_ptr(void)
{
	return readl(psam_dl.regbase + HI_PSAM_CRDQ_PTR_OFFSET);
}

unsigned int psam_get_cipher_busy(void)
{
	HI_PSAM_CIPHER_CH_EN_T ch_en;
	ch_en.u32 = readl(psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);
	return ch_en.bits.cipher_ch_busy;
}

static void psam_dump_cb(void)
{
	unsigned int i;
	unsigned int ptr;
	unsigned int reg_base;
	
	reg_base= (unsigned int)psam_dl.regbase;
	ptr = psam_dl.dump_addr;		
	
	for(i = 0; i < PSAM_REGS_SIZE; i += 4){
		*(unsigned int *)(ptr + i) = readl(reg_base + i);
	}
}

int psam_om_dump_init()
{
	unsigned int dump = 0;

	/*Register Psam dump memory.*/
	dump = (unsigned int)bsp_dump_register_field(DUMP_CP_PSAM, "PSAM", 0, 
													0, PSAM_DUMP_SIZE, 0);
	if(!dump){
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"Fail to get dump memory!\n");
		return -EAGAIN;
	} else {
	
		/*address should be an integral multiple of 4 bytes,
		* because registers are 32bit width.
		*/
		if(dump % sizeof(unsigned int)){
			bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"Dump address align error!\n");
			return -EAGAIN;
		} else {
			psam_dl.dump_addr = dump;
		}
	}

	/*Register dump callback function to om module*/
	if (BSP_ERROR == bsp_dump_register_hook("PSAM", psam_dump_cb)){
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"Fail to register dump handler!\n");
		return -EAGAIN;
	}

	return 0;
}

void psam_reset_cbdq_crdq_ptr(void)
{
	psam_cipher_ch_en(0);

	writel(0, psam_dl.regbase + HI_PSAM_CBDQ_WPTR_OFFSET);
	writel(0, psam_dl.regbase + HI_PSAM_CRDQ_PTR_OFFSET);
	writel(0, psam_dl.regbase + HI_PSAM_CBDQ_STAT_OFFSET);

	psam_cipher_ch_en(1);
}

static int psam_start_addr_limit(void)
{
	static int set_flag = 0;

	if(set_flag){
		return 0;
	}
	
	if(psam_dl.addr_limit == 0){
		return -1;
	}

	if(psam_dl.sh_limit_addr->block_err){//acore do not get limit addr
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"acore do not get limit addr!\n");
		return -1;
	}
	
	if(psam_dl.sh_limit_addr->block_sum){
		
		writel(psam_dl.sh_limit_addr->block1_start, psam_dl.regbase + HI_PSAM_ADQ_PADDR_STR0_OFFSET);
		writel(psam_dl.sh_limit_addr->block1_end, psam_dl.regbase + HI_PSAM_ADQ_PADDR_END0_OFFSET);
		
		if(psam_dl.sh_limit_addr->block_sum == 1){
			//acore sep one block and enable 
			writel(ADQ_CTRL_1, psam_dl.regbase + HI_PSAM_ADQ_PADDR_CTRL_OFFSET);
			set_flag = 1;
			return 0;
		}
		else if(psam_dl.sh_limit_addr->block_sum == 2){
			//acore sep two blocks and enables
			writel(psam_dl.sh_limit_addr->block2_start, psam_dl.regbase + HI_PSAM_ADQ_PADDR_END1_OFFSET);
			writel(psam_dl.sh_limit_addr->block2_end, psam_dl.regbase + HI_PSAM_ADQ_PADDR_END1_OFFSET);
			writel(ADQ_CTRL_2, psam_dl.regbase + HI_PSAM_ADQ_PADDR_CTRL_OFFSET);
			set_flag = 1;
			return 0;
		}
		return -1;
	}
	return -1;
}

int mdrv_psam_set_crdq_ctrl(unsigned int cipher_fc_head)
{
	int ret;
	ret = psam_set_crdq_ctrl(cipher_fc_head);
	return ret;
}

int bsp_psam_get_cipher_bd(struct tagpsam_cipher_reg * param)
{
	if(param == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"get cipher para is NULL!\n");
		return -EINVAL;
	}
	
	if(param->cbdq_size == 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"cipher para psam_reg_cbdq_size is zero!\n");
		return -EINVAL;
	}
	
	psam_dl.ciphers_para.cbdq_baddr 	= param->cbdq_baddr;
	psam_dl.ciphers_para.cbdq_config 	= param->cbdq_config;
	psam_dl.ciphers_para.cbdq_size		= param->cbdq_size;
	psam_dl.ciphers_para.cbdq_wptr_addr	= param->cbdq_wptr_addr;
	psam_dl.ciphers_para.crdq_rptr_addr	= param->crdq_rptr_addr;

	psam_dl.get_cipher_para = 1;
	return 0;
}

int bsp_psam_config_cipher_rd(cipher_addr_s *para)
{
	if(para == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"parament is NULL!\n");
		return -EINVAL;
	}
	if(psam_get_dts() != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"ccore psam dts failed.\n");
		return -1;
	}

	para->direct_addr = (void *)(psam_dl.regbase + HI_PSAM_CRDQ_BADDR_OFFSET);
	para->cnt = PSAM_CIPER_RD_CNT;
	
	return 0;
}

void bsp_psam_move_cbdq_ptr(unsigned int bdq_ptr)
{
	writel(bdq_ptr, psam_dl.regbase + HI_PSAM_CBDQ_WPTR_OFFSET);
}

int	bsp_psam_cipher_ch_srst(unsigned int soft_reset)
{
	HI_PSAM_CIPHER_CH_SOFTRESET_T cipher_ch_srst_p;
	unsigned int count = 10000;
	
	if((soft_reset != 0) && (soft_reset != 1))
		return -EINVAL;
	
	cipher_ch_srst_p.u32 = readl(psam_dl.regbase + HI_PSAM_CIPHER_CH_SOFTRESET_OFFSET);
	cipher_ch_srst_p.bits.cipher_ch_srst = soft_reset;

	writel(cipher_ch_srst_p.u32, psam_dl.regbase + HI_PSAM_CIPHER_CH_SOFTRESET_OFFSET);

    do{
		if(!readl(psam_dl.regbase + HI_PSAM_CIPHER_CH_SOFTRESET_OFFSET))
		{
			/*psam_int1_mask needs do nothing*/
			writel(0, psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);

			writel(psam_dl.ciphers_para.cbdq_config, psam_dl.regbase + HI_PSAM_CBDQ_CONFIG_OFFSET);
			writel(psam_dl.ciphers_para.cbdq_baddr, psam_dl.regbase + HI_PSAM_CBDQ_BADDR_OFFSET);
			writel(psam_dl.ciphers_para.cbdq_size -1, psam_dl.regbase + HI_PSAM_CBDQ_SIZE_OFFSET);
			writel(psam_dl.ciphers_para.cbdq_wptr_addr, psam_dl.regbase + HI_PSAM_CBDQ_WPTR_ADDR_OFFSET);
			/*psam_crdq_baddr cipher config by itself, psam don`t care*/
			writel(psam_dl.ciphers_para.crdq_rptr_addr, psam_dl.regbase + HI_PSAM_CRDQ_RPTR_ADDR_OFFSET);

			writel(1, psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);
			return 0;
		}
		count--;
	}while(count != 0);

	return -EAGAIN;
	
}

void bsp_psam_config_adthred(unsigned int u32DlADThr)
{
	unsigned int ADCtrl = 0;
	
	ADCtrl = readl(psam_dl.regbase + HI_PSAM_ADQ_CTRL_OFFSET);
	ADCtrl &= IPF_ADQ_THR_MASK;
	ADCtrl |= (u32DlADThr<<16);
	/* config psam dl ad thred value*/
    writel(ADCtrl, psam_dl.regbase + HI_PSAM_ADQ_CTRL_OFFSET);
}

int bsp_psam_config_dlbd(unsigned int u32Num, psam_config_dlparam_s* dl_para)
{
    unsigned int bdq_wptr = 0;
    unsigned int i;
    unsigned int bd_in_ptr = 0;
    unsigned int bd_cnt = 0;
    unsigned short total_data_len = 0;
    psam_desc_attr_t bd_attr;
	psam_dl_s* dl_bd = &(psam_dl.g_psam_dl);
	unsigned int cur_idlebd = 0, dummy_cd = 0;

	if(psam_start_addr_limit()){
		//bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"ccore psam limit func diable.\n");
	}

	cur_idlebd = bsp_psam_get_dlbd_num(&dummy_cd);

	if(u32Num > cur_idlebd){
		psam_dl.over_idlebd ++;
	}
	
    if((NULL == dl_para)||(0 == u32Num))
    {
    	(u32Num==0)? psam_dl.cfg_desc_debug.cfg_lbd_num_zero++ :\
					 psam_dl.cfg_desc_debug.cfg_dl_para_null++;
    	psam_dl.cfg_desc_debug.cfg_fail_cnt++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r bsp_psam_config_dlbd input para ERROR! \n");
        return -EINVAL;
    }
	
    for(i = 0; i < u32Num; i++)
    {
        if(0 == dl_para[i].u16Len)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"\r INPUT BD_Len =0 !Drop pkt \n");
			psam_dl.cfg_desc_debug.dlbd_len_zero_cnt++;
            return -EINVAL;
        }
    }

    bdq_wptr = readl(psam_dl.regbase + HI_PSAM_LBDQ_WPTR_OFFSET);
    bd_cnt = bdq_wptr&PSAM_DQ_PTR_MASK;

	/*lint -save -e830 -e539*/
    for(i = 0; i < u32Num; i++)
    {
        /* ����CD */
        if(IPF_ConfigCD((void*)dl_para[i].u32Data, &total_data_len, &bd_in_ptr) != 0)
        {
			psam_dl.cfg_desc_debug.dlcd_empty++;
            return -EAGAIN;
        }
        bd_attr.u16 = dl_para[i].u16Attribute;
        bd_attr.bits.cd_en = 1;
        dl_bd->psam_bdq[bd_cnt].u16Attribute = bd_attr.u16; 
        dl_bd->psam_bdq[bd_cnt].u32InPtr =  bd_in_ptr;
        dl_bd->psam_bdq[bd_cnt].u16PktLen = total_data_len;
        dl_bd->psam_bdq[bd_cnt].u16UsrField1 = dl_para[i].u16UsrField1;
        //dl_bd->psam_bdq[bd_cnt].u32UsrField2 = dl_para[i].u32UsrField2;/*myself*/
        //dl_bd->psam_bdq[bd_cnt].u32UsrField3 = dl_para[i].u32UsrField3;/*chip*/
        bd_cnt = ((bd_cnt + 1) < PSAM_DLBD_DESC_SIZE)? (bd_cnt + 1) : 0;
    }

	psam_dl.cfg_desc_debug.cfg_suc_cnt += u32Num;
	/*lint -restore*/

    writel(bd_cnt, psam_dl.regbase + HI_PSAM_LBDQ_WPTR_OFFSET);  
    return 0;
}

int bsp_psam_set_ipf_para(struct tagpsam_ipf_reg *para)
{
	if(para == NULL)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"get cipher para is NULL!\n");
		return -EINVAL;
	}

	psam_dl.ipf_para.dlbdq_rptr_addr 	= para->dlbdq_rptr_addr;
	psam_dl.ipf_para.dlbdq_wptr_addr 	= para->dlbdq_wptr_addr;
	psam_dl.ipf_para.dlcdq_wptr		 	= para->dlcdq_wptr;
	psam_dl.ipf_para.dlcdq_rptr		 	= para->dlcdq_rptr;
	psam_dl.ipf_para.dlcdq				= para->dlcdq;

	return 0;
}

unsigned int bsp_psam_get_dlbd_num(unsigned int* cd_num)
{
    unsigned int bdq_depth = 0;
    unsigned int idle_bd = 0;
    unsigned int idlecd = 0;
    unsigned int idle_cd_down = 0;
    unsigned int idle_cd_up = 0;
	
	/*lint -save -e570*/
	if(cd_num == NULL)
	{
		psam_dl.cfg_desc_debug.cd_num_p_empty++;
		return -1;
	}
	/*lint -restore*/

	/* �������BD���� */
    bdq_depth = readl(psam_dl.regbase + HI_PSAM_LBDQ_DEPTH_OFFSET);
    bdq_depth = bdq_depth & PSAM_DQ_DEPTH_MASK;
    idle_bd = PSAM_DLBD_DESC_SIZE - bdq_depth - PSAM_DLBD_RES_NUM;
	
	if(idle_bd == 0){
		psam_dl.dllbd_full++;
	}

	if(idle_bd == PSAM_DLBD_DESC_SIZE - PSAM_DLBD_RES_NUM){
		psam_dl.dllbd_empty++;
	}
	
    /* �������CD ���� */
    if(*(psam_dl.ipf_para.dlcdq_rptr) > *(psam_dl.ipf_para.dlcdq_wptr))
    {
        idlecd = *(psam_dl.ipf_para.dlcdq_rptr) - *(psam_dl.ipf_para.dlcdq_wptr) - 1;
    }
    else
    {
        idle_cd_up = (*(psam_dl.ipf_para.dlcdq_rptr) > 1)?(*(psam_dl.ipf_para.dlcdq_rptr) - 1):0;
        idle_cd_down = PSAM_DLCD_DESC_SIZE -  *(psam_dl.ipf_para.dlcdq_wptr) - 1;
        idlecd = (idle_cd_up > idle_cd_down)? idle_cd_up:idle_cd_down;
    }
    psam_dl.g_psam_dl.idle_bd = idle_bd;
    *cd_num = idlecd;

    return idle_bd;
}

int psam_init(void)
{
	struct clk *c_psamclk; 

	/*psam enable clock*/
    c_psamclk = clk_get(NULL, "psam_aclk");
    if(IS_ERR(c_psamclk))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"psam_init: ccore psam clk get failed.\n");
        return -1;
    }

	/*lint -save -e830 -e539*/
    if(clk_enable(c_psamclk) != 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"psam_init: ccore psam clk open failed.\n");
        return -1;
    }

	if(psam_get_dts() != 0)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"ccore psam dts failed.\n");
		return -1;
	}
	/*lint -restore*/

	//disable addr area limit func
	if(psam_dl.addr_limit){
		writel(AD_CHECK_BYPASS, psam_dl.regbase + HI_PSAM_ADQ_PADDR_CTRL_OFFSET);
	}
	psam_dl.sh_limit_addr = (psam_limit_addr_s *)PSAM_TRANS_LIMIT_ADDR;

	//LBD config 
	psam_dl.g_psam_dl.psam_bdq = (psam_bd_desc_s*)osl_cachedma_malloc(PSAM_DLBD_MEM_SIZE);
	if(!psam_dl.g_psam_dl.psam_bdq)
	{
		bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_PSAM,"c core alloc lbdq buff failed.\n");
		return -1;
	}

	psam_set_crdq_ctrl(IPF_MODEM0_DLFC);

	//IBDQ
	writel(IPF_DLBD_MEM_ADDR, psam_dl.regbase + HI_PSAM_IBDQ_BADDR_OFFSET);
	writel(IPF_DLBD_DESC_SIZE-1, psam_dl.regbase + HI_PSAM_IBDQ_SIZE_OFFSET);

	//rd,wr pointer addresses
	writel(psam_dl.ipf_para.dlbdq_wptr_addr, psam_dl.regbase + HI_PSAM_IBDQ_WPTR_ADDR_OFFSET);
	writel(psam_dl.ipf_para.dlbdq_rptr_addr, psam_dl.regbase + HI_PSAM_IBDQ_RPTR_ADDR_OFFSET);

	//LBDQ
	writel((unsigned int)psam_dl.g_psam_dl.psam_bdq, psam_dl.regbase + HI_PSAM_LBDQ_BADDR_OFFSET);
	writel(PSAM_DLLBD_DESC_SIZE-1, psam_dl.regbase + HI_PSAM_LBDQ_SIZE_OFFSET);

	/* config cipher relate registers */
	/* psam cipher regs could not be configured in bsp_psam_get_cipher_bd(), at that time psam do not enable clk*/
	if(!psam_dl.get_cipher_para)
	{
		bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_PSAM,"psam do not get cipher para!\n");
		psam_dl.init_af_ci_para = 1;
	}
	writel(0, psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);

	writel(psam_dl.ciphers_para.cbdq_config, psam_dl.regbase + HI_PSAM_CBDQ_CONFIG_OFFSET);
	writel(psam_dl.ciphers_para.cbdq_baddr, psam_dl.regbase + HI_PSAM_CBDQ_BADDR_OFFSET);
	writel(psam_dl.ciphers_para.cbdq_size - 1, psam_dl.regbase + HI_PSAM_CBDQ_SIZE_OFFSET);
	writel(psam_dl.ciphers_para.cbdq_wptr_addr, psam_dl.regbase + HI_PSAM_CBDQ_WPTR_ADDR_OFFSET);
	/*psam_crdq_baddr cipher config by itself, psam don`t care*/
	writel(psam_dl.ciphers_para.crdq_rptr_addr, psam_dl.regbase + HI_PSAM_CRDQ_RPTR_ADDR_OFFSET);

	writel(1, psam_dl.regbase + HI_PSAM_CIPHER_CH_EN_OFFSET);

	/*psam enable*/
	writel(1, psam_dl.regbase + HI_PSAM_EN_OFFSET);

	if(psam_om_dump_init())
		bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_PSAM,"psam reg dump failed!\n");

	bsp_trace(BSP_LOG_LEVEL_ALERT, BSP_MODU_PSAM,"psam init success!\n");
	return 0;
}

