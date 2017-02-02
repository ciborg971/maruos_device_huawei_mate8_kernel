

/*lint --e{537,438}*/
#include <osl_common.h>
#include <bsp_memmap.h>
#include <bsp_version.h>
#include <edma_balong.h>
//#include <of.h>
#include <libfdt.h>

void *g_edma_reg_base = NULL;

static inline u32 is_edma_reg_error()
{
    return (g_edma_reg_base == 0);
}

u32 edma_init(void)
{
    struct device_node *edma_node = NULL;
#ifdef CONFIG_OF
	edma_node = of_find_compatible_node(NULL, NULL, "edma_m3");
#endif
	if (!edma_node)
	{
		printk("edma node not found!\n");
		return ERROR;
	}
#ifdef CONFIG_OF
	g_edma_reg_base = of_iomap(edma_node, 0);
#endif
	if (NULL == g_edma_reg_base)
	{
		printk("edma of_iomap failed.\r\n");
		return ERROR;
	}
    return OK;
}
   


/*******************************************************************************
������:     s32 bsp_edma_state(void)
��������:   �ж� edma �Ƿ��ڹ��� �� ��˯ǰ���á�
�������:   u32 channel_id
�������:   ��
����ֵ:     busy����0,��-1
            idle��0
            error: -1
*******************************************************************************/
s32 bsp_edma_channel_state(u32 channel_id)
{
    u32 ch_stat;
    if(is_edma_reg_error())
        return -1;
    if(channel_id>=16)
    {
        printk("chan_stat chan_id=%d err", channel_id);
        return -1;
    }
    ch_stat = readl((unsigned)g_edma_reg_base + HI_CH_STAT_OFFSET);
    return (ch_stat & ((u32)0x1<<channel_id));/*lint !e713*/
}

/*******************************************************************************
������:     s32 bsp_edma_state(void)
��������:   �ж� edma �Ƿ��ڹ��� �� ��˯ǰ���á�
�������:   ��
�������:   ��
����ֵ:     busy����0
            idle��0
*******************************************************************************/
u32 bsp_edma_state(void)
{
    u32 edma16_ch_stat;
    if(is_edma_reg_error())
        return -1;
    /*u32 edma4_ch_stat;*/
    edma16_ch_stat = readl((unsigned)g_edma_reg_base + HI_CH_STAT_OFFSET);
#ifdef HI_EDMA_CH4_REGBASE_ADDR_VIRT
/*    if(PROTOCOL_TYPE_GUL == bsp_get_board_mode_type())
    {
        edma4_ch_stat = readl(HI_EDMA_CH4_REGBASE_ADDR_VIRT + HI_CH_STAT_OFFSET);
    }
    else
    {
    }
    edma16_ch_stat = edma16_ch_stat|edma4_ch_stat;
*/
#endif
    return edma16_ch_stat;
}


/*******************************************************************************
������:     u32 bsp_edma_m2m_chan(u32 chan, u32 src_addr, u32 dest_addr, u32 len)

��������:   ����һ�� EDMA���䡣����EDMA����󣬾ͷ��أ���Ҫ�û�ͨ���ӿ�
            �ж�ͨ���Ƿ������ɡ�

�������:   channel_id��ͨ��ID, TL DSP ���� TCM ʹ�� 0 / 1 ͨ��, �͹��ĸ��á�
            src_addr�����ݴ���Դ��ַ�������������ַ
            des_addr�����ݴ���Ŀ�ĵ�ַ�������������ַ
            len�����ݴ��䳤�ȣ���λ���ֽڣ�
                ��֧�� len<65535�ֽڵ����ⳤ�ȡ�
                ��len>=64k����Ҫʹ�ö�ά���䣬Ҫ�� len 4k(0x1000)����
�������:   ��
����ֵ:     �ɹ���0
            ʧ�ܣ�����
*******************************************************************************/
__ao_func s32 bsp_edma_m2m_channel(u32 channel_id, u32 src_addr, u32 dest_addr, u32 len)
{
    u32 cx_config;
    u32 bindx;
    u32 cnt0, a_count, b_count;

    u32 edma_cfg_base;
    
    if(is_edma_reg_error())
        return -1;
    edma_cfg_base = (unsigned)g_edma_reg_base + 0x40*channel_id;

    cx_config = EDMA_CONFIG_FAST;

    writel(src_addr , edma_cfg_base + HI_CX_SRC_ADDR_0_OFFSET);
    writel(dest_addr, edma_cfg_base + HI_CX_DES_ADDR_0_OFFSET);
    writel(cx_config, edma_cfg_base + HI_CX_CONFIG_0_OFFSET);

    if(len<(SZ_64K-1))
    {
        writel(len, edma_cfg_base + HI_CX_CNT0_0_OFFSET);
    }
    else
    {
        b_count = (!(len%SZ_16K)) ? (len/SZ_16K - 1) \
                : (!(len%SZ_8K )) ? (len/SZ_8K  - 1) \
                : (!(len%SZ_4K )) ? (len/SZ_4K  - 1) : 0;
        if(0==b_count)
        {
            printk("2vec not aligned\n");
            return -1;
        }
        else
        {
            a_count = len / (b_count+1);
            bindx = ( (a_count << 16) | a_count );
            cnt0  =  (b_count<<16)|a_count;
            writel( bindx, edma_cfg_base + HI_CX_BINDX_OFFSET);
            writel( cnt0 , edma_cfg_base + HI_CX_CNT0_0_OFFSET);
        }
    }
    writel((cx_config|EDMA_CONFIG_CH_EN), edma_cfg_base + HI_CX_CONFIG_0_OFFSET);
    return 0;
}


