

#ifdef __cplusplus
extern "C"
{
#endif
/*lint -save -e537*/
#include <securec.h>
#include "osl_irq.h"
#include <osl_thread.h>
#include <osl_malloc.h>
#include "bsp_memmap.h"
#include "bsp_socp.h"
#include "bsp_sysctrl.h"
#include "bsp_om_api.h"
#include "bsp_version.h"
#include "amon_balong.h"
#include "osl_malloc.h"
#include "of.h"
#include "bsp_om_api.h"
#include "securec.h" 

/*lint -restore*/
/******************************ȫ�ֱ�������***********************************/
/*lint -save -e40*/
/* ��ʼ����־ */
int g_sl_init_flag = false;
/* ȫ��ͳ�� */
axi_global_stat_t   g_st_stat_info;
/* ѭ��buffer��Ϣά�� 0:CPUFAST, 1:SOC*/
ring_buf_info_t     g_st_ring_buf_info[2];
/* EDMAͨ����, 0:CPUFASTͨ��, 1:SOCͨ�� */
s32 g_sl_edma_channel[2] = {-1, -1};
/* ��ع����£�IDʹ�ܱ�ʶ */
u32 g_ul_id_en[AXI_MAX_ID] = {0};
/* �ɼ�״̬��¼ */
axi_capt_state_enum_uint32 g_st_capt_buf_state = AXI_CAPT_NORMAL;
/* SOCP��ʱ�� */
struct softtimer_list g_st_socp_timer;
/* Monitorʱ�� */
axi_clk_ctrl_t  g_st_amon_clk;
/* K3V3 version */
u32 g_ul_k3_flag = false;

u32 g_amon_base_addr[AXI_CTRL_ADDR_BUTT];
u32 g_amon_irq = 0;
struct amon_sysctrl_struct g_amon_sysctrl;

extern amon_config_stru g_amon_config;

/**********************************�궨��***********************************/
/* ��ʼ�����궨�� */
#define AXI_CHECK_INIT() \
do{\
    if(false == g_sl_init_flag)\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: not inited\n", __FUNCTION__);\
        return MDRV_ERROR;\
    }\
}while(0)

/* AXI״̬��飬�Ƿ��������У�������ʱ�����������û��߻�ȡͳ������ */
#define AXI_CHECK_STATE(config) \
do{\
    if(MDRV_OK != axi_state_check(config))\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI %d is running\n", __FUNCTION__, config);\
        return MDRV_ERROR;\
    }\
}while(0)  

/* MODE��飬ֻ֧��SOC��CPUFAST */
/*lint -save -e607*/
#define AXI_CHECK_MODE(mode) \
do{\
    if(mode >= AXI_CONFIG_BUTT)\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI mode %d is invalid\n", __FUNCTION__, mode);\
        return MDRV_ERROR;\
    }\
}while(0)
/*lint -restore*/       


/*****************************************************************************
 �� �� ��  : axi_reg_read
 ��������  : AXI�Ĵ���������, һ��ֻ�ܶ�һ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
 �������  : u32 * value
 �� �� ֵ  : void
 ���ú���  :
 ��������  :
 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_read(axi_config_enum_uint32 config, u32 reg, u32 * value)
{
    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    switch(config)
    {
        /* ��ȡCPUFAST�Ĵ��� */
        case AXI_CPUFAST_CONFIG:
            *value = readl(AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* ��ȡSOC�Ĵ��� */
        case AXI_SOC_CONFIG:
            *value = readl(AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : axi_reg_write
 ��������  : AXI�Ĵ���д������һ��ֻ��дһ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
             u32 value
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_write(axi_config_enum_uint32 config, u32 reg, u32 value)
{
    /* ��������Ŀ��д����Ӧ�Ĵ��� */
    switch(config)
    {
        /* дCPUFAST�Ĵ��� */
        case AXI_CPUFAST_CONFIG:
            writel(value, AXI_MON_CPUFAST_BASE_ADDR + reg);
            break;

        /* дSOC�Ĵ��� */
        case AXI_SOC_CONFIG:
            writel(value, AXI_MON_SOC_BASE_ADDR + reg);
            break;

        default:
            break;
    }
}

/*****************************************************************************
 �� �� ��  : axi_reg_getbits
 ��������  : AXI�Ĵ�����λ������һ��ֻ�ܶ�һ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
             u32 pos
             u32 bits
 �������  : u32 * value
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_getbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 * value)
{
    u32 reg_value = 0;

    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    axi_reg_read(config, reg, &reg_value);
    /* ���ݼĴ���ֵȡ��Ӧλ */
    *value = (reg_value >> pos) & (((u32)1 << (bits)) - 1);
}

/*****************************************************************************
 �� �� ��  : axi_reg_setbits
 ��������  : AXI�Ĵ���дλ������һ��ֻ��дһ��Ĵ�����CPUFAST/SOC��
 �������  : axi_config_enum_uint32 config
             u32 reg
             u32 pos
             u32 bits
             u32 value
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reg_setbits(axi_config_enum_uint32 config, u32 reg, u32 pos, u32 bits, u32 value)
{
    u32 reg_value = 0;

    /* ��������Ŀ���ȡ��Ӧ�Ĵ��� */
    axi_reg_read(config, reg, &reg_value);
    /* ����д��Ĵ�����Ŀ��ֵ */
    reg_value = (reg_value & (~((((u32)1 << (bits)) - 1) << (pos)))) | ((u32)((value) & (((u32)1 << (bits)) - 1)) << (pos));
    /* д��Ŀ�ļĴ��� */
    axi_reg_write(config, reg, reg_value);
}

/*****************************************************************************
 �� �� ��  : axi_sc_clk_open
 ��������  : ��ϵͳ������AXI monitorʱ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_sc_clk_open(axi_config_enum_uint32 config)
{  
    if(g_ul_k3_flag)
    {
        amon_soc_clk_enable();
        g_st_amon_clk.is_clk_enable[config] = true;
    }
    else
    {
        /* coverity[check_return] */
        (void)clk_enable(g_st_amon_clk.sc_clk[config]);
        g_st_amon_clk.is_clk_enable[config] = true; 
    }    
}

/*****************************************************************************
 �� �� ��  : axi_sc_clk_close
 ��������  : �ر�ϵͳ������AXI monitorʱ��
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_sc_clk_close(axi_config_enum_uint32 config)
{  
    if(g_ul_k3_flag)
    {
        amon_soc_clk_disable();
        g_st_amon_clk.is_clk_enable[config] = false;
    }
    else
    {    
        clk_disable(g_st_amon_clk.sc_clk[config]);
        g_st_amon_clk.is_clk_enable[config] = false;  
    }
}

/*****************************************************************************
 �� �� ��  : axi_sc_mon_start
 ��������  : AXI Monitor����ͨ��ϵͳ����������
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_sc_mon_start(axi_config_enum_uint32 config)
{
    /* ����CPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_start();
    }
    /* ����SOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_start();
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 �� �� ��  : axi_sc_mon_stop
 ��������  : AXI Monitorֹͣͨ��ϵͳ����������
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_sc_mon_stop(axi_config_enum_uint32 config)
{
    /* ֹͣCPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_stop();
    }
    /* ֹͣSOC */
    else if(AXI_SOC_CONFIG == config)
    {
        amon_soc_stop();
    }
    else
    {
        return;
    }
}

/*****************************************************************************
 �� �� ��  : axi_sc_reset
 ��������  : monitor ��λ��ÿ�������ɼ�֮ǰ��ϵͳ��������λmonitor
             ��λ���֮����Ҫ�⸴λ��������ʹ��
             ��Ƭ���������󣬱��뱣֤����monitorͬʱ��λ
 �������  : ��
 �� �� ֵ  : u32 ��λ
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_sc_reset(void)
{
    if(!g_ul_k3_flag)
    {
        /* CPUFAST */
        /* ��λ */
        amon_cpufast_soft_reset();
        /* �⸴λ */
        amon_cpufast_rls_reset();
    }

    /* SOC */
    /* ��λ */
    amon_soc_soft_reset();
    /* �⸴λ */
    amon_soc_rls_reset();
}

/*****************************************************************************
 �� �� ��  : axi_reset_pkg_buf
 ��������  : ���Monitor���buffer��FIFO���ΪAXI_FIFO_DEPTH
             ��AXI_FIFO_DEPTH�����ݼ�����գ�Ҫ��������Monitor֮ǰִ�иò���
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_reset_pkg_buf(axi_config_enum_uint32 config)
{
    int i;
    u32 reg_base;

    /* CPUFAST */
    if(AXI_CPUFAST_CONFIG == config)
    {
        reg_base = AXI_MON_CPUFAST_BASE_ADDR;
    }
    /* SOC */
    else
    {
        reg_base = AXI_MON_SOC_BASE_ADDR;
    }

    /* ��FIFO��������buffer */
    for(i=0; i<AXI_FIFO_DEPTH; i++)
    {
        (void)readl(reg_base + AXI_CAPT_FIFO_ADDR);
    }
}

/*****************************************************************************
 �� �� ��  : axi_get_data_buf
 ��������  : ��ȡѭ��buffer����������Ϣ
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_get_data_buf(ring_data_buf_t * data_buf, ring_buf_info_t * ring_buf)
{
    /* дָ����ڵ��ڶ�ָ�룬ֱ�Ӽ��� */
    if(ring_buf->write >= ring_buf->read)
    {
        data_buf->p_buf_1 = ring_buf->read;
        data_buf->size_1  = (unsigned int)(ring_buf->write - ring_buf->read);
        data_buf->p_buf_2 = NULL;
        data_buf->size_2  = 0;
    }
    /* ��ָ�����дָ�룬��Ҫ���ǻؾ� */
    else
    {
        data_buf->p_buf_1 = ring_buf->read;
        data_buf->size_1  = (unsigned int)(ring_buf->end - ring_buf->read + 1);
        data_buf->p_buf_2 = ring_buf->start;
        data_buf->size_2  = (unsigned int)(ring_buf->write - ring_buf->start);;
    }
}

/*****************************************************************************
 �� �� ��  : axi_get_idle_buf
 ��������  : ��ȡѭ��buffer����������Ϣ
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_get_idle_buf(ring_idle_buf_t * idle_buf, ring_buf_info_t * ring_buf)
{
    /* ��ָ�����дָ�룬ֱ�Ӽ��� */
    if(ring_buf->write < ring_buf->read)
    {
        idle_buf->p_buf_1 = ring_buf->write;
        idle_buf->size_1  = (u32)(ring_buf->read - ring_buf->write - 1);
        idle_buf->p_buf_2 = NULL;
        idle_buf->size_2  = 0;
    }
    /* дָ����ڵ��ڶ�ָ�룬���ܻؾ� */
    else
    {
        /* readָ������ʼָ�벻��ȣ�д���ݿ��ܻؾ� */
        if(ring_buf->read != ring_buf->start)
        {
            idle_buf->p_buf_1 = ring_buf->write;
            idle_buf->size_1  = (u32)(ring_buf->end - ring_buf->write + 1);
            idle_buf->p_buf_2 = ring_buf->start;
            idle_buf->size_2  = (u32)(ring_buf->read - ring_buf->start - 1);;
        }
        else
        {
            idle_buf->p_buf_1 = ring_buf->write;
            idle_buf->size_1  = (u32)(ring_buf->end - ring_buf->write);
            idle_buf->p_buf_2 = NULL;
            idle_buf->size_2  = 0;
        }
    }
}

/*****************************************************************************
 �� �� ��  : axi_socp_src_chan_init
 ��������  : monitor socpԴͨ����ʼ��
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_socp_src_chan_init(void)
{
    SOCP_CODER_SRC_CHAN_S socp_chan;
    u8 * bd_addr = NULL;
    u8 * rd_addr = NULL;

    /* ����BD�ռ� */
    bd_addr = (u8 *)osl_cachedma_malloc((u32)SOCP_BD_BUF_SIZE);

    if(NULL == bd_addr)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: alloc BD buffer fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ����RD�ռ� */
    rd_addr = (u8 *)osl_cachedma_malloc((u32)SOCP_RD_BUF_SIZE);

    if(NULL == rd_addr)
    {
        (void)osl_cachedma_free((void *)bd_addr);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: alloc RD buffer fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    socp_chan.u32DestChanID = SOCP_CODER_DST_OM_IND;    /*  Ŀ��ͨ��ID */
    socp_chan.eDataType     = SOCP_DATA_TYPE_2;          /*  �������ͣ�ָ�����ݷ�װЭ�飬���ڸ��ö�ƽ̨ */
    socp_chan.eMode         = SOCP_ENCSRC_CHNMODE_LIST;  /*  ͨ������ģʽ */
    socp_chan.ePriority     = SOCP_CHAN_PRIORITY_3;      /*  ͨ�����ȼ� */
    socp_chan.u32BypassEn   = SOCP_HDLC_ENABLE;          /*  ͨ��bypassʹ�� */
    socp_chan.eDataTypeEn   = SOCP_DATA_TYPE_EN;         /*  ��������ʹ��λ */
    socp_chan.eDebugEn      = SOCP_ENC_DEBUG_DIS;        /*  ����λʹ�� */

    socp_chan.sCoderSetSrcBuf.pucInputStart  = AXI_VITR_TO_PHYS(bd_addr);                         /* ����ͨ����ʼ��ַ */
    socp_chan.sCoderSetSrcBuf.pucInputEnd    = AXI_VITR_TO_PHYS(bd_addr) + SOCP_BD_BUF_SIZE -1;   /* ����ͨ��������ַ */
    socp_chan.sCoderSetSrcBuf.pucRDStart     = AXI_VITR_TO_PHYS(rd_addr);                         /* RD buffer��ʼ��ַ */
    socp_chan.sCoderSetSrcBuf.pucRDEnd       = AXI_VITR_TO_PHYS(rd_addr) + SOCP_RD_BUF_SIZE -1;   /* RD buffer������ַ */
    socp_chan.sCoderSetSrcBuf.u32RDThreshold = 0;                                                                  /* RD buffer�����ϱ���ֵ */

    /* ���ñ���Դͨ�� */
    if (MDRV_OK != bsp_socp_coder_set_src_chan(AXI_SOCP_CHAN_ID, &socp_chan))
    {
        (void)osl_cachedma_free((void *)bd_addr);
        (void)osl_cachedma_free((void *)rd_addr);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: set socp src chan fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ��������Դͨ�� */
    if(MDRV_OK != bsp_socp_start(AXI_SOCP_CHAN_ID))
    {
        (void)osl_cachedma_free((void *)bd_addr);
        (void)osl_cachedma_free((void *)rd_addr);        
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: start socp src chan fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_gen_bd_packet
 ��������  : ���ݻ���������SOCP BD��
 �������  : tran_len: ����ɹ�����
 �� �� ֵ  : u32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_gen_bd_packet(ring_data_buf_t * data_buf, u32 * tran_len)
{
    u32 i;
    u32 cnt;
    u32 bd_cnt;
    u32 data_len = 0;
    u32 addr;
    u32 addr_tmp;
    SOCP_BUFFER_RW_STRU  wr_buf  = {0};
    SOCP_BD_DATA_STRU bd_data = {0};

    /* ��ȡSOCP BD buffer */
    if(MDRV_OK != bsp_socp_get_write_buff(AXI_SOCP_CHAN_ID, &wr_buf))
    {
        g_st_stat_info.socp_tran_fail++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: get write buffer fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    if(wr_buf.u32Size + wr_buf.u32RbSize < SOCP_BD_PACKET_SIZE)
    {
        g_st_stat_info.socp_buf_full++;
        return MDRV_ERROR;
    }

    /* �����������, ÿ2k��һ�������ؾ���Ҫ�ְ� */
    cnt = data_buf->size_1/AXI_SOCP_PACKET_SIZE;
    if(0 != data_buf->size_1%AXI_SOCP_PACKET_SIZE)
    {
        cnt++;
    }
    bd_cnt = (wr_buf.u32Size + wr_buf.u32RbSize)/SOCP_BD_PACKET_SIZE;
    cnt = (cnt > bd_cnt)?bd_cnt:cnt;

    /* SOCP���������׵�ַ */
    addr = (u32)AXI_PHYS_TO_VIRT(wr_buf.pBuffer);
    /* SOCP��������ؾ��ַ */
    addr_tmp = (u32)AXI_PHYS_TO_VIRT(wr_buf.pBuffer) + wr_buf.u32Size;

    for(i=0; i<cnt; i++)
    {
        (void)memset_s(&bd_data, sizeof(SOCP_BD_DATA_STRU), 0x0, sizeof(SOCP_BD_DATA_STRU));
        /* BD����Ҫ��д�����ַ */
        bd_data.ulDataAddr    = (u32)data_buf->p_buf_1 + AXI_SOCP_PACKET_SIZE * i;

        /* ����ؾ���������ĳ��� */
        if((u32)(AXI_SOCP_PACKET_SIZE * (i+1)) > data_buf->size_1)
        {
            bd_data.usMsgLen   = data_buf->size_1%AXI_SOCP_PACKET_SIZE;
        }
        else
        {
            bd_data.usMsgLen   = AXI_SOCP_PACKET_SIZE;
        }
        bd_data.enDataType = SOCP_BD_DATA;
        (void)memcpy_s((void *)addr, SOCP_BD_PACKET_SIZE, &bd_data, SOCP_BD_PACKET_SIZE);
        addr += SOCP_BD_PACKET_SIZE;

        /* SOCP BD buffer�лؾ� */
        if(addr >= addr_tmp)
        {
            addr = (u32)AXI_PHYS_TO_VIRT(wr_buf.pRbBuffer);
        }

        data_len += bd_data.usMsgLen;
    }

    if(MDRV_OK != bsp_socp_write_done(AXI_SOCP_CHAN_ID, cnt * SOCP_BD_PACKET_SIZE))
    {
        g_st_stat_info.socp_tran_fail++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: write buffer done fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    *tran_len = data_len;

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_data_buf_update
 ��������  : ���������������ݣ����¶�ָ��
 �������  : ��
 �� �� ֵ  : u32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_data_buf_update(ring_buf_info_t * ring_buf)
{
    ring_data_buf_t data_buf = {0};
    SOCP_BUFFER_RW_STRU socp_buf;
    u32 tran_len;

    /* ��RD */
    if(MDRV_OK != bsp_socp_get_rd_buffer(AXI_SOCP_CHAN_ID, &socp_buf))
    {
        g_st_stat_info.socp_tran_fail++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: get rd buffer fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ������ʱ����Ҫ��RD */
    if(0 != socp_buf.u32Size + socp_buf.u32RbSize)
    {
        if(MDRV_OK != bsp_socp_read_rd_done(AXI_SOCP_CHAN_ID, socp_buf.u32Size + socp_buf.u32RbSize))
        {
            g_st_stat_info.socp_tran_fail++;
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: read rd done fail\n", __FUNCTION__);
            return MDRV_ERROR;
        }
    }

    /* ��ȡ�������ݿռ� */
    axi_get_data_buf(&data_buf, ring_buf);
    /* ������ */
    if(0 == data_buf.size_1 && 0 == data_buf.size_2)
    {
        return MDRV_OK;
    }

    /* ����BD�� */
    if(MDRV_OK != axi_gen_bd_packet(&data_buf, &tran_len))
    {
        return MDRV_ERROR;
    }

    /* ����buffer��ָ�� */
    ring_buf->read += tran_len;
    if(ring_buf->read > ring_buf->end)
    {
        ring_buf->read -= ring_buf->end - ring_buf->start + 1;
    }

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_edma_get_tran_len
 ��������  : ��ȡ���䳤�ȣ���������EDMA
 �������  : ��
 �� �� ֵ  : s32 ���ø�EDMA�Ĵ��䳤�ȣ�����-1��ʾ�޿���
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_edma_get_tran_len(ring_buf_info_t * ring_buf)
{
    ring_idle_buf_t idle_buf;

    axi_get_idle_buf(&idle_buf, ring_buf);
    /* ���пռ䲻�� */
    if(idle_buf.size_1 + idle_buf.size_2 < AXI_CAPT_THRESHOLD)
    {
        return MDRV_ERROR;
    }
    /* дָ�뵽endָ��֮��Ŀռ�С����ֵ����������ָ��֮��ĳ��� */
    if(idle_buf.size_1 < AXI_CAPT_THRESHOLD)
    {
        return (s32)idle_buf.size_1;
    }
    /* ������ֵ��С */
    else
    {
        return AXI_CAPT_THRESHOLD;
    }
}

/*****************************************************************************
 �� �� ��  : axi_get_edma_cnt
 ��������  : ��ȡedmaʣ�ഫ�䳤��
 �������  : ��
 �� �� ֵ  : u32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
u32 axi_get_edma_cnt(u32 channel_id)
{
	u32 left_cnt;
	
	left_cnt = (u32)bsp_edma_current_cnt(channel_id);

    return left_cnt;
}

/*****************************************************************************
 �� �� ��  : axi_socp_timer_handler
 ��������  : socp timer������
 �������  : ��
 �� �� ֵ  : u32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_socp_timer_handler(u32 param)
{
    s32 ret;
    s32 tran_len;
    u32 edma_src_addr;
    axi_config_enum_uint32 axi_mode;
    
    axi_mode = g_st_stat_info.capt_mode;
    if(AXI_SOC_CONFIG == axi_mode)
    {
        edma_src_addr = SOC_BUFF_BASE_ADDR;
    }
    else
    {
        edma_src_addr = CPUFAST_BUFF_BASE_ADDR;
    }    

    (void)axi_data_buf_update(&g_st_ring_buf_info[axi_mode]);
    
    tran_len = axi_edma_get_tran_len(&g_st_ring_buf_info[axi_mode]);
    if(MDRV_ERROR == tran_len)
    {
        bsp_softtimer_add(&g_st_socp_timer);
        return ;
    }
    
    /* ���浱ǰ���䳤�� */
    g_st_stat_info.capt_edma_len = (u32)tran_len;
   
    /* ���ô�����ʼ��Ŀ�ĵ�ַ�����䳤�ȣ�ʹ��EMDAͨ�� */
    ret = bsp_edma_channel_2vec_start((u32)g_sl_edma_channel[axi_mode], edma_src_addr, (u32)g_st_ring_buf_info[axi_mode].write, (u32)tran_len, g_st_stat_info.edma_bindex);
    if(EDMA_SUCCESS != ret)
    {
        g_st_stat_info.edma_tran_fail++;
    }
}

/*****************************************************************************
 �� �� ��  : axi_socp_start_timer
 ��������  : socpͨ�����������ٶ�����Դ���ݲ����ٶȣ�����timer
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_socp_start_timer(u32 time_out)
{  
    s32 ret = 0;
    g_st_socp_timer.func = axi_socp_timer_handler;
    g_st_socp_timer.para = 0;
    g_st_socp_timer.timeout = time_out;
    g_st_socp_timer.wake_type = SOFTTIMER_NOWAKE;

    ret =  bsp_softtimer_create(&g_st_socp_timer);
    if(ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: start timer fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_edma_int_handler
 ��������  : EDMA�жϴ�����
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_edma_int_handler(u32 param, u32 int_status)
{
    s32 tran_len;
    s32 ret;
    u32 edma_src_addr;
    u32 edma_left_cnt;
    axi_config_enum_uint32 axi_mode;;

    axi_mode = g_st_stat_info.capt_mode;
    if(AXI_SOC_CONFIG == axi_mode)
    {
        edma_src_addr = SOC_BUFF_BASE_ADDR;
    }
    else
    {
        edma_src_addr = CPUFAST_BUFF_BASE_ADDR;
    }

    /* ��ȡedma��һ�δ���ʣ�೤�� */
    edma_left_cnt = axi_get_edma_cnt((u32)g_sl_edma_channel[axi_mode]);
    /* ����дָ�� */
    g_st_ring_buf_info[axi_mode].write += g_st_stat_info.capt_edma_len - edma_left_cnt;
    /* �лؾ� */
    if(g_st_ring_buf_info[axi_mode].write > g_st_ring_buf_info[axi_mode].end)
    {
        g_st_ring_buf_info[axi_mode].write = g_st_ring_buf_info[axi_mode].start;
    }

    /* �����ͨ��SOCP���� */
    if(MDRV_OK != axi_data_buf_update(&g_st_ring_buf_info[axi_mode]))
    {
        /* SOCP����������ʱ�� */
        bsp_softtimer_add(&g_st_socp_timer);
        return ;
    }

    /* ��ȡ��һ�δ��䳤�� */
    tran_len = axi_edma_get_tran_len(&g_st_ring_buf_info[axi_mode]);
    if(MDRV_ERROR == tran_len)
    {
        /* SOCP�����ٶȻ�����ʣ��ռ䲻��һ��EDMA���Ƴ��ȣ�������ʱ�� */
        g_st_stat_info.axi_buf_full++;
        bsp_softtimer_add(&g_st_socp_timer);
        return ;
    }

    /* ���浱ǰ���䳤�� */
    g_st_stat_info.capt_edma_len = (u32)tran_len;

    /* ���ô�����ʼ��Ŀ�ĵ�ַ�����䳤�ȣ�ʹ��EMDAͨ�� */
    ret = bsp_edma_channel_2vec_start((u32)g_sl_edma_channel[axi_mode], edma_src_addr, (u32)g_st_ring_buf_info[axi_mode].write, (u32)tran_len, g_st_stat_info.edma_bindex);
    if(EDMA_SUCCESS != ret)
    {
        g_st_stat_info.edma_tran_fail++;
        return ;
    }

    g_st_stat_info.int_stat.edma_tran_over++;

    return ;
}

/*****************************************************************************
 �� �� ��  : axi_edma_config_init
 ��������  : EDMA��ʼ������
 �������  : axi_config_enum_uint32 config
             u32 bindex EDMA��ά���䲽��
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_edma_config_init(axi_config_enum_uint32 config, u32 bindex)
{
    s32 channel_id;
    s32 ret;
    s32 tran_len;
    enum edma_req_id req;
    u32 src_addr;

    if(AXI_CPUFAST_CONFIG == config)
    {
        req      = CPUFAST_EDMA_REQUEST;
        src_addr = CPUFAST_BUFF_BASE_ADDR;
    }
    else
    {
        req      = SOC_EDMA_REQUEST;
        src_addr = SOC_BUFF_BASE_ADDR;
    }

    /* ͨ������ */
    channel_id = bsp_edma_channel_init(/*(BALONG_DMA_REQ)*/req, axi_edma_int_handler, config, EDMA_INT_DONE);
    if(-1 == channel_id)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): alloc edma channel fail\n", __FUNCTION__, config);
        return MDRV_ERROR;
    }

    /* ͨ���������� */
    ret = bsp_edma_channel_set_config((u32)channel_id, EDMA_P2M, EDMA_TRANS_WIDTH_64, EDMA_BUR_LEN_16);
    if(EDMA_SUCCESS != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): edma set config fail\n", __FUNCTION__, config);
        return MDRV_ERROR;
    }

    /* ���ô��䳤�� */
    tran_len = axi_edma_get_tran_len(&g_st_ring_buf_info[config]);
    if(MDRV_ERROR == tran_len)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): get tran len fail\n", __FUNCTION__, config);
        return MDRV_ERROR;
    }

    /* ���ô�����ʼ��Ŀ�ĵ�ַ�����䳤�ȣ����ö�ά���� */
    ret = bsp_edma_channel_2vec_start((u32)channel_id, src_addr, (u32)g_st_ring_buf_info[config].write, (u32)tran_len, bindex);
    if(EDMA_SUCCESS != ret)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): config src/dst fail\n", __FUNCTION__, config);
        return MDRV_ERROR;
    }
    /* ����ͨ��ID */
    g_sl_edma_channel[config] = channel_id;

    /* ����edma���䳤�� */
    g_st_stat_info.capt_edma_len = AXI_CAPT_THRESHOLD;

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_edma_free
 ��������  : EDMAͨ���ͷ�
 �������  : axi_config_enum_uint32 config
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_edma_free(axi_config_enum_uint32 config)
{
    s32 addr;
    int i = 0;
    
    addr = bsp_edma_channel_stop((u32)g_sl_edma_channel[config]);

    if(addr < 0)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: stop edma channel fail\n", __FUNCTION__);
        return MDRV_ERROR; 
    }
    
    /* ����дָ�� */ 
    g_st_ring_buf_info[config].write = (u8 *)addr;

    /* ����ʣ������ */
    while((i++ < AXI_SOCP_TRAN_WAIT_CNT) && (g_st_ring_buf_info[config].write != g_st_ring_buf_info[config].read))
    {
        (void)axi_data_buf_update(&g_st_ring_buf_info[config]);
        (void)osl_task_delay(10);     
    }

    if(g_st_ring_buf_info[config].write != g_st_ring_buf_info[config].read)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: socp transfer can not finish(write 0x%x read 0x%x)\n", __FUNCTION__,
                    (u32)g_st_ring_buf_info[config].write, (u32)g_st_ring_buf_info[config].read);
        return MDRV_ERROR;        
    }

    if(MDRV_OK != bsp_edma_channel_free((u32)g_sl_edma_channel[config]))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: free edma channel fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_get_state
 ��������  : ��ȡAXI monitor����/��λ״̬������ͬʱ��ȡCPUFAST/SOC״̬
 �������  : axi_config_enum_uint32 config
             axi_get_state_req_enum_uint32 state_req
 �������  : ��
 �� �� ֵ  : axi_state_enum_uint32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
axi_state_enum_uint32 axi_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req)
{
    u32 reg_value = 0;

    /* ��״̬�Ĵ�����ȡ����״̬ */
    AXI_REG_READ(config, AXI_MON_CNT_STATE_INT, &reg_value);
    /* ��ȡ����״̬���� */
    if(AXI_GET_RUN_STATE_REQ == state_req)
    {
        reg_value = reg_value & AXI_RUN_STATE_MASK;
    }
    /* ��ȡ��λ״̬���� */
    else if(AXI_GET_RESET_STATE_REQ == state_req)
    {
        reg_value = reg_value & AXI_RESET_STATE_MASK;
    }
    /* ��Ч���� */
    else
    {
        return (axi_state_enum_uint32)AXI_STATE_BUTT;
    }

    return reg_value;
}

/*****************************************************************************
 �� �� ��  : axi_state_check
 ��������  : ״̬�ж��������Ƿ���������
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_state_check(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;

    axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
    /* AXI monitor�������� */
    if(axi_state != AXI_IDLE && axi_state != AXI_STOP)
    {
        return MDRV_ERROR;
    }

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_win_over_int_handler
 ��������  : ʱ�䴰�����жϴ�����
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_win_over_int_handler(void)
{
    u32 reg_value = 0;

    if(!g_ul_k3_flag)
    {
        /* ���CPUFAST�ж� */
        AXI_REG_GETBITS(AXI_CPUFAST_CONFIG, AXI_MON_CNT_STATE_INT, 0, 1, &reg_value);
        if(reg_value)
        {
            /* ���ж� */
            AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_MON_INT_CLR, 0, 1, 0x1);
            g_st_stat_info.int_stat.win_over++;
            /* ����ϱ� */
            (void)axi_mon_info_gen_packet(AXI_CPUFAST_CONFIG);
            /* ʱ�䴰�������ر�ʱ�� */
            if(g_st_amon_clk.is_clk_enable[AXI_CPUFAST_CONFIG] == true)
            {
                axi_sc_clk_close(AXI_CPUFAST_CONFIG);
            } 
        }
    }

    /* ���SOC�ж� */
    reg_value = 0;
    AXI_REG_GETBITS(AXI_SOC_CONFIG, AXI_MON_CNT_STATE_INT, 0, 1, &reg_value);
    if(reg_value)
    {
        /* ���ж� */
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_MON_INT_CLR, 0, 1, 0x1);
        g_st_stat_info.int_stat.win_over++;
        /* ����ϱ� */
        (void)axi_mon_info_gen_packet(AXI_SOC_CONFIG);
        /* ʱ�䴰�������ر�ʱ�� */
        if(g_st_amon_clk.is_clk_enable[AXI_SOC_CONFIG] == true)
        {
            axi_sc_clk_close(AXI_SOC_CONFIG);
        } 
    }       
}

/*****************************************************************************
 �� �� ��  : axi_tran_int_handler
 ��������  : �ɼ������жϴ�����
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_tran_int_handler(void)
{
    u32 reg_value;
    u32 i;

    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        AXI_REG_GETBITS(i, AXI_CAPT_INT_STATE, 0, 4, &reg_value);
        /* buffer���ж� */
        if(reg_value & (1 << 0))
        {
            /* �������ж� */
            AXI_REG_SETBITS(i, AXI_CAPT_INT_MASK, 0, 1, 0x1);  
            g_st_stat_info.int_stat.buff_over++;
            g_st_capt_buf_state = AXI_CAPT_FULL;
        }
        /* ��������ж� */
        if(reg_value & (1 << 1))
        {
            AXI_REG_SETBITS(i, AXI_CAPT_INT_MASK, 1, 1, 0x1);
            AXI_REG_SETBITS(i, AXI_CAPT_INT_CLR, 1, 1, 0x1);
            g_st_stat_info.int_stat.tran_over++; 

            /* buffer���жϺ�����ɣ��ϱ���������ж� */
            if(g_st_capt_buf_state & AXI_CAPT_FULL)
            {
                g_st_capt_buf_state = (g_st_capt_buf_state & ~(AXI_CAPT_FULL)) | AXI_CAPT_FINISHING;
                /* ֹͣ�ɼ� */
                AXI_REG_WRITE(i, AXI_CAPT_CTRL, 0x2);
            }
            /* buffer��������stop֮���ϱ������жϣ������ɼ� */
            else if(g_st_capt_buf_state & AXI_CAPT_FINISHING)
            {               
                /* ������ж� */
                AXI_REG_SETBITS(i, AXI_CAPT_INT_CLR, 0, 1, 0x1);
                /* ������ж����� */
                AXI_REG_SETBITS(i, AXI_CAPT_INT_MASK, 0, 1, 0x0);   
                if(g_st_capt_buf_state & AXI_CAPT_STOP_REQ)
                {
                    g_st_stat_info.tran_over_flag = true;
                    osl_sem_up(&g_st_stat_info.capt_sem);  
                }
                else
                {
                    /* �����ɼ� */
                    AXI_REG_WRITE(i, AXI_CAPT_CTRL, 0x1);
                }
                g_st_capt_buf_state = AXI_CAPT_NORMAL;
            }
            /* ���ڲɼ�stop���󣬴������֮�������ɼ� */
            else if(g_st_capt_buf_state & AXI_CAPT_PERIOD_STOP_REQ)
            {
                /* �����ɼ� */
                AXI_REG_WRITE(i, AXI_CAPT_CTRL, 0x1);
                g_st_capt_buf_state = AXI_CAPT_NORMAL;
            }
            /* ֹͣ�ɼ� */
            else
            {   
                g_st_stat_info.tran_over_flag = true;
                osl_sem_up(&g_st_stat_info.capt_sem);
            }
            AXI_REG_SETBITS(i, AXI_CAPT_INT_MASK, 1, 1, 0x0);
            AXI_REG_GETBITS(i, AXI_CAPT_INT_STATE, 0, 4, &reg_value);
        }
    }
}

/*****************************************************************************
 �� �� ��  : axi_tran_int_handler_k3
 ��������  : �ɼ������жϴ�����
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_tran_int_handler_k3(void)
{
    u32 reg_value;

    AXI_REG_GETBITS(AXI_SOC_CONFIG, AXI_CAPT_INT_STATE, 0, 4, &reg_value);
    /* buffer���ж� */
    if((reg_value & (1 << 0)) || (reg_value & (1 << 1)) || (reg_value & (1 << 2)))
    {
        /* �������ж� */
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0, 3, 0xe);  
        g_st_stat_info.int_stat.buff_over++;
        g_st_capt_buf_state = AXI_CAPT_FULL;
    }
    /* ��������ж� */
    if(reg_value & (1 << 3))
    {
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 3, 1, 0x1);
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_CAPT_INT_CLR, 3, 1, 0x1);
        g_st_stat_info.int_stat.tran_over++; 

        /* buffer���жϺ�����ɣ��ϱ���������ж� */
        if(g_st_capt_buf_state & AXI_CAPT_FULL)
        {
            g_st_capt_buf_state = (g_st_capt_buf_state & ~(AXI_CAPT_FULL)) | AXI_CAPT_FINISHING;
            /* ֹͣ�ɼ� */
            AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_CTRL, 0x2);
        }
        /* buffer��������stop֮���ϱ������жϣ������ɼ� */
        else if(g_st_capt_buf_state & AXI_CAPT_FINISHING)
        {               
            /* ������ж� */
            AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_CAPT_INT_CLR, 0, 3, 0xe);
            /* ������ж����� */
            AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0, 3, 0x0);   
            if(g_st_capt_buf_state & AXI_CAPT_STOP_REQ)
            {
                g_st_stat_info.tran_over_flag = true;
                osl_sem_up(&g_st_stat_info.capt_sem);  
            }
            else
            {
                /* �����ɼ� */
                AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_CTRL, 0x1);
            }
            g_st_capt_buf_state = AXI_CAPT_NORMAL;
        }
        /* ���ڲɼ�stop���󣬴������֮�������ɼ� */
        else if(g_st_capt_buf_state & AXI_CAPT_PERIOD_STOP_REQ)
        {
            /* �����ɼ� */
            AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_CTRL, 0x1);
            g_st_capt_buf_state = AXI_CAPT_NORMAL;
        }
        /* ֹͣ�ɼ� */
        else
        {   
            g_st_stat_info.tran_over_flag = true;
            osl_sem_up(&g_st_stat_info.capt_sem);
        }
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 3, 1, 0x0);
    }
}

/*****************************************************************************
 �� �� ��  : axi_int_handler
 ��������  : �жϴ�����
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_int_handler(void)
{
    axi_tran_int_handler();
    axi_win_over_int_handler();
}

/*****************************************************************************
 �� �� ��  : axi_int_handler_k3
 ��������  : �жϴ�����
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_int_handler_k3(void)
{
    axi_tran_int_handler_k3();
    axi_win_over_int_handler();
}

/*****************************************************************************
 �� �� ��  : axi_reset
 ��������  : AXI monitor��λ
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_reset(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    int i = 0;

    /* �������״̬ */
    AXI_CHECK_STATE(config);

    /* ��λ */
    AXI_REG_WRITE(config, AXI_MON_CNT_RESET, AXI_SOFT_RESET);
    /* ��λ�����ж���AXI monitor״̬�Ĵ���ָʾ��λ���� */
    do       
    {
        axi_state = axi_get_state(config, AXI_GET_RESET_STATE_REQ);
        if(AXI_RESET_FINISH == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);
    
    /* ��λ��ʱ�쳣 */
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: time out\n", __FUNCTION__);
    return MDRV_ERROR;
}


s32 axi_get_irq_and_iomap(void)
{
	struct device_node *dev[AXI_CTRL_ADDR_BUTT] = {};
	const char *name[AXI_CTRL_ADDR_BUTT] = {"hisilicon,amon_fast1_balong", "hisilicon,amon_soc1_balong"};
#ifndef BSP_CONFIG_HI3650  
    char fast_reg_name[amon_cpufast_dts_butt][32] = {"amon_cpufast_srst_en","amon_cpufast_srst_dis", "amon_cpufast_monitor_start"};
#endif
    char soc_reg_name[amon_soc_dts_butt][32] = {"amon_soc_srst_en","amon_soc_srst_dis", "amon_soc_monitor_start"};
    u32 i = 0;
    u32 reg_addr[3] = {};
#ifdef BSP_CONFIG_HI3650  
    if(g_amon_base_addr[AXI_SOC_ADDR_ENUM] != 0)
    {
        return MDRV_OK;
    }

    dev[AXI_SOC_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_SOC_ADDR_ENUM]);

    if(NULL == dev[AXI_SOC_ADDR_ENUM])
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: device node not found\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(dev[AXI_SOC_ADDR_ENUM], 0);

    if (0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM])
    {
        amon_error("remap amon fail\n fast base addr = 0x%x soc base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
        return MDRV_ERROR;
    }

    g_amon_irq = irq_of_parse_and_map(dev[AXI_SOC_ADDR_ENUM], 0);
    /*SOC���ϵͳ��������Ϣ��ʼ��*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_SOC_ADDR_ENUM], soc_reg_name[i], reg_addr, 3))
        {
            amon_error("Get amon dts fail, i = 0x%x\n", i);
            return MDRV_ERROR;
        }
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
#else

    if((g_amon_base_addr[AXI_FAST_ADDR_ENUM] != 0)&&(g_amon_base_addr[AXI_SOC_ADDR_ENUM] != 0))
    {
        return MDRV_OK;
    }
    dev[AXI_FAST_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_FAST_ADDR_ENUM]);
    dev[AXI_SOC_ADDR_ENUM] = of_find_compatible_node(NULL, NULL, name[AXI_SOC_ADDR_ENUM]);

    if((NULL == dev[AXI_FAST_ADDR_ENUM])||(NULL == dev[AXI_SOC_ADDR_ENUM]))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: device node not found\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    g_amon_base_addr[AXI_FAST_ADDR_ENUM] = (u32)of_iomap(dev[AXI_FAST_ADDR_ENUM], 0);
    g_amon_base_addr[AXI_SOC_ADDR_ENUM] = (u32)of_iomap(dev[AXI_SOC_ADDR_ENUM], 0);

    if ((0 == g_amon_base_addr[AXI_FAST_ADDR_ENUM])||(0 == g_amon_base_addr[AXI_SOC_ADDR_ENUM]))
    {
        amon_error("remap amon fail\n fast base addr = 0x%x soc base addr = 0x%x\n", g_amon_base_addr[AXI_FAST_ADDR_ENUM], g_amon_base_addr[AXI_SOC_ADDR_ENUM]);
        return MDRV_ERROR;
    }

    g_amon_irq = irq_of_parse_and_map(dev[AXI_FAST_ADDR_ENUM], 0);
    /*SOC���ϵͳ��������Ϣ��ʼ��*/
    for(i = 0; i < amon_soc_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_SOC_ADDR_ENUM], soc_reg_name[i], reg_addr, 3))
        {
            amon_error("soc of_property_read_u32_array error\n");
            return MDRV_ERROR;
        } 
        /* coverity[uninit_use_in_call] */
        g_amon_sysctrl.amon_sysctrl_soc[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_soc[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_soc[i].end_bit = reg_addr[AMON_END_BIT];
    }
    /*cpu fast���ϵͳ��������Ϣ��ʼ��*/
    for(i = 0; i < amon_cpufast_dts_butt; i++)
    {
        if(of_property_read_u32_array(dev[AXI_FAST_ADDR_ENUM], fast_reg_name[i], reg_addr, 3))
        {
            amon_error("fast of_property_read_u32_array error\n");
            return MDRV_ERROR;
        }
        /* coverity[uninit_use_in_call] */
        g_amon_sysctrl.amon_sysctrl_fast[i].base_addr = (u32)bsp_sysctrl_addr_get((void *)reg_addr[AMON_BASE_ADDR]);
        g_amon_sysctrl.amon_sysctrl_fast[i].start_bit = reg_addr[AMON_START_BIT];
        g_amon_sysctrl.amon_sysctrl_fast[i].end_bit = reg_addr[AMON_END_BIT];
    }
#endif
    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_init
 ��������  : AXI monitor��ʼ��
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_init(void)
{
    int i;
	u32 chip_type;

	if(true == g_sl_init_flag)
	{
		return MDRV_OK;
	}

	/* �Ƿ�ΪK3V3�汾 */
	chip_type = bsp_get_version_info()->chip_type;
	if(CHIP_K3V3 == chip_type || CHIP_K3V5 == chip_type)
	{
		g_ul_k3_flag = true;
	}
    
#ifdef BSP_CONFIG_HI3650  
    g_ul_k3_flag = true;
#endif

    /* ��ʼ��SOCPͨ�� */
    if(MDRV_OK != axi_socp_src_chan_init())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: socp src chan init fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ��ȡʱ�� */
    if(!g_ul_k3_flag)
    {
        g_st_amon_clk.sc_clk[AXI_CPUFAST_CONFIG] = clk_get(NULL, "amon_cpufast_clk");
        g_st_amon_clk.sc_clk[AXI_SOC_CONFIG]     = clk_get(NULL, "amon_soc_clk");  
    }
    /* ��ϵͳʱ�� */
    axi_sc_clk_open(AXI_CPUFAST_CONFIG);
    axi_sc_clk_open(AXI_SOC_CONFIG);
    /* ��¼ʱ��״̬ */
    g_st_amon_clk.is_clk_enable[AXI_CPUFAST_CONFIG] = true;
    g_st_amon_clk.is_clk_enable[AXI_SOC_CONFIG]     = true;
    
    /* �ж����� */
    AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
    AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
    if(g_ul_k3_flag)
    {
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0x3F);
    }
    else
    {
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);        
    }


    if(g_ul_k3_flag)
    {
        /* ���ж� */
        if(MDRV_OK != request_irq(g_amon_irq, (irq_handler_t)axi_int_handler_k3, 0, "AXI_MON_IRQ", NULL))
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: INT connect fail\n", __FUNCTION__);
            return MDRV_ERROR;
        }
    }
    else
    {
        /* ���ж� */
        if(MDRV_OK != request_irq(g_amon_irq, (irq_handler_t)axi_int_handler, 0, "AXI_MON_IRQ", NULL))
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: INT connect fail\n", __FUNCTION__);
            return MDRV_ERROR;
        }
    }


    /* �ź�����ʼ�� */
    osl_sem_init(0, &g_st_stat_info.capt_sem);

    /* ����ռ���䣬�������ɿռ� */
    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        /* ��ʼ��ѭ��buffer��Ϣ */
        g_st_ring_buf_info[i].start = (u8 *)(DDR_SOCP_ADDR);
        g_st_ring_buf_info[i].end   = (u8 *)(DDR_SOCP_ADDR + DDR_SOCP_SIZE - 1);
        g_st_ring_buf_info[i].read  = (u8 *)(DDR_SOCP_ADDR);
        g_st_ring_buf_info[i].write = (u8 *)(DDR_SOCP_ADDR);
    }

    /* ȫ�ֱ�����ʼ�� */
    (void)memset_s(&g_st_stat_info.int_stat,sizeof(axi_int_stat_t), 0x0, sizeof(axi_int_stat_t));
    g_st_stat_info.capt_mode        = AXI_CONFIG_BUTT;
    g_st_stat_info.mon_mode         = AXI_CONFIG_BUTT;
    g_st_stat_info.edma_bindex      = AXI_EDMA_BINDEX;
    g_st_stat_info.capt_cycle       = AXI_CAPT_CYCLE_DEFAULT;
    g_st_stat_info.axi_buf_full     = 0;
    g_st_stat_info.edma_tran_fail   = 0;
    g_st_stat_info.socp_buf_full    = 0;
    g_st_stat_info.socp_tran_fail   = 0;
    g_st_stat_info.mon_ind_cnt      = 0;
    g_st_stat_info.mon_ind_fail_cnt = 0;
    g_st_stat_info.tran_over_flag   = true;

    g_st_capt_buf_state = AXI_CAPT_NORMAL;

    g_sl_init_flag = true;

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_mon_start
 ��������  : ����AXI monitor����ϵͳ����������
 �������  : axi_config_enum_uint32 config
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_mon_start(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    int i = 0;

    /* �������״̬ */
    AXI_CHECK_STATE(config);

    /* ����ϵͳ����������Monitor */
    axi_sc_mon_start(config);

    /* ���������ж����ȴ�������־��λ */
    do
    {
        axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
        if(AXI_UNWIN_RUNNING == axi_state || AXI_WIN_RUNNING == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);
    
    /* ������ʱ�쳣 */
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: time out\n", __FUNCTION__);
    return MDRV_ERROR;
}

/*****************************************************************************
 �� �� ��  : axi_mon_stop
 ��������  : ֹͣAXI monitor����ϵͳ������ֹͣ
 �������  : axi_config_enum_uint32 config
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_mon_stop(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    int i = 0;

    /* ����ϵͳ������ֹͣMonitor */
    axi_sc_mon_stop(config);

    /* ֹͣ�����ж� */
    do
    {
        axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
        if(AXI_STOP == axi_state)
        {
            /* ֹ֮ͣ��ǿ�ƽ���IDLE̬ */
            AXI_REG_WRITE(config, AXI_MON_CNT_RESET, AXI_RESET_TO_IDLE);
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);
    
    /* ֹͣMonitor��ʱ�쳣 */
    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: time out\n", __FUNCTION__);
    return MDRV_ERROR;
}

/*****************************************************************************
 �� �� ��  : axi_capt_start
 ��������  : �������ݲɼ�
 �������  : axi_config_enum_uint32 config
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_capt_start(axi_config_enum_uint32 axi_mode)
{
    s32 ret;
    axi_state_enum_uint32 axi_state;
    u32 lock_key;
    u32 tran_state;
    
    local_irq_save(lock_key);
    tran_state = g_st_stat_info.tran_over_flag;
    local_irq_restore(lock_key); 

    /* ����֮ǰ����ϴδ����Ƿ���� */
    if(false == tran_state)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: last transfer unfinished\n", __FUNCTION__);
        return MDRV_ERROR;
    }  

    /* ���Ȼ�ȡ����״̬�������ɼ�Ҫ��monitor�ѿ�ʼ���� */
    axi_state = axi_get_state(axi_mode, AXI_GET_RUN_STATE_REQ);
    if(axi_state == AXI_IDLE || axi_state == AXI_STOP)
    {
        /* ������monitor����ع��ܲ�����һ�����ã������������� */
        ret = axi_mon_start(axi_mode);
        if(MDRV_OK != ret)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: capture start fail\n", __FUNCTION__);
            return ret;
        }
    }

    /* ���жϣ��򿪲ɼ����жϡ������жϣ�������ֵ�жϡ������ж����� */
    if(g_ul_k3_flag)
    {
        AXI_REG_WRITE(axi_mode, AXI_CAPT_INT_CLR, 0x3F);
        AXI_REG_WRITE(axi_mode, AXI_CAPT_INT_MASK, 0x30);
    }
    else
    {
        AXI_REG_WRITE(axi_mode, AXI_CAPT_INT_CLR, 0xF);
        AXI_REG_WRITE(axi_mode, AXI_CAPT_INT_MASK, 0xC);
    }

    /* �����ɼ� */
    AXI_REG_WRITE(axi_mode, AXI_CAPT_CTRL, 0x1);

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_capt_stop
 ��������  : ֹͣ���ݲɼ�
 �������  : axi_config_enum_uint32 config
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_capt_stop(axi_config_enum_uint32 config)
{
    u32 lock_key;

    /* coverity[lock_acquire] */
    local_irq_save(lock_key);

    if(g_st_capt_buf_state != AXI_CAPT_NORMAL)
    {
        g_st_capt_buf_state |= AXI_CAPT_STOP_REQ;
    }
    else
    {
        /* ֹͣ�ɼ� */
        AXI_REG_WRITE(config, AXI_CAPT_CTRL, 0x2);
    }
    
    g_st_stat_info.tran_over_flag = false;
      
    local_irq_restore(lock_key); 
    
    /* �ȴ�������� */
    /* coverity[lock] */
    if(MDRV_OK != osl_sem_downtimeout(&g_st_stat_info.capt_sem, AXI_CAPT_TRAN_OVER_TIME))
    {
        if(false == g_st_stat_info.tran_over_flag)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: capture transfer time out\n", __FUNCTION__);
            return MDRV_ERROR;
        }
    }
    /* coverity[missing_unlock] */
    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_stop_timer
 ��������  : ɾ��timer
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_stop_timer(void)
{
    if(g_st_stat_info.axi_timer.init_flags != TIMER_INIT_FLAG)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: timer is null\n", __FUNCTION__);
        return;
    }

    (void)bsp_softtimer_delete(&g_st_stat_info.axi_timer);
    (void)bsp_softtimer_free(&g_st_stat_info.axi_timer);
}

/*****************************************************************************
 �� �� ��  : axi_timer_handler
 ��������  : ��ʱ�����������ɼ����ڵ�����Ҫִ��stop, start����
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_timer_handler(u32 param)
{
    u32 lock_key;
 
    local_irq_save(lock_key);

    if(g_st_capt_buf_state == AXI_CAPT_NORMAL)
    {
        g_st_capt_buf_state = AXI_CAPT_PERIOD_STOP_REQ;
        /* ֹͣ�ɼ� */
        AXI_REG_WRITE(g_st_stat_info.capt_mode, AXI_CAPT_CTRL, 0x2);
    }
          
    local_irq_restore(lock_key); 

    /* ����ִ�� */
    bsp_softtimer_add(&g_st_stat_info.axi_timer);
}

/*****************************************************************************
 �� �� ��  : axi_start_timer
 ��������  : ���ڲɼ�������timer
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_start_timer(u32 time_out)
{
    s32 ret = 0;

     g_st_stat_info.axi_timer.func = axi_timer_handler;
     g_st_stat_info.axi_timer.para = 0;
     g_st_stat_info.axi_timer.timeout = time_out;
     g_st_stat_info.axi_timer.wake_type = SOFTTIMER_NOWAKE;

    ret =  bsp_softtimer_create(&g_st_stat_info.axi_timer);
    if(ret)
    {
        return MDRV_ERROR;
    }
    bsp_softtimer_add(&g_st_stat_info.axi_timer);

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_capt_config
 ��������  : �ɼ���������
 �������  : axi_capt_config_t * capt_config
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_capt_config(axi_capt_config_t * capt_config)
{
    axi_config_enum_uint32 mode;
    u32 reg_value;
    u32 i;

    mode = capt_config->mode;

    /* ����AXI_CAPT_TRAN_CONFIG����:�����ɼ��˿ڣ�DMA����level, �������� */
    /* AXI_CAPT_TRAN_CONFIG�Ĵ���: bit5:6-dma, bit4-����ѡ��, bit3-��������ѡ��, bit0:2-port */
    reg_value = (capt_config->port & 0x7) | ((capt_config->op_type & 0x1) << 3) | ((capt_config->dma_req_level & 0x3) << 5);
    /* ����SOC, bit4���� */
    if(mode == AXI_SOC_CONFIG)
    {
        reg_value &= 0xFFFFFFEF;
    }
    /* ����CPUFAST, bit4��1 */
    else
    {
        reg_value |= 0x10;
    }
    AXI_REG_WRITE(mode, AXI_CAPT_TRAN_CONFIG, reg_value);

    /* ����Monitor��ֵ */
    AXI_REG_WRITE(mode, AXI_CAPT_TRANS_DATA_LEVEL, capt_config->data_trans_thr);
    /* ����������� */
    AXI_REG_WRITE(mode, AXI_CAPT_CMD_PKG_SIZE, capt_config->cmd_pkg_len);
    /* �������ݰ��� */
    AXI_REG_WRITE(mode, AXI_CAPT_DATA_PKG_SIZE, capt_config->data_pkg_len);
    /* ���ø��Ӱ��� */
    AXI_REG_WRITE(mode, AXI_CAPT_EXT_PKG_SIZE, capt_config->ext_pkg_len);
    /* ����DMA�������� */
    AXI_REG_WRITE(mode, AXI_CAPT_DMA_REQ_TYPE, capt_config->dma_req_type);

    /* �ɼ�ID���� */
    for(i=0; i<AXI_MAX_ID; i++)
    {
        reg_value = 0;
        if(0 != capt_config->id_cfg[i].id_en)
        {
            /* ����IDʹ�� */
            AXI_REG_SETBITS(mode, AXI_CAPT_ID_EN, i, 1, 1);

            /* ID���üĴ���: bit0:14 ID, bit16:30 MASK */
            reg_value = (capt_config->id_cfg[i].id_value & 0x7FFF) | ((capt_config->id_cfg[i].mask & 0x7FFF) << 16);
            AXI_REG_WRITE(mode, AXI_CAPT_ID(i), reg_value);
        }
    }
}

/*****************************************************************************
 �� �� ��  : axi_mon_config
 ��������  : ��ز�������
 �������  : axi_mon_config_t * mon_config
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_mon_config(axi_mon_config_t * mon_config)
{
    axi_config_enum_uint32 mode;
    axi_mon_id_config_t * id_cfg;
    u32 reg_value;
    u32 i;

    mode = mon_config->mode;

    /* �������ϵͳ���� */
    /* ���bypass */
    AXI_REG_SETBITS(mode, AXI_MON_CNT_CTRL, 5, 16, 0x0);
    /* ʱ�䴰���� */
    if(AXI_WIN_ENABLE == mon_config->win_en)
    {
        AXI_REG_SETBITS(mode, AXI_MON_CNT_CTRL, 1, 2, 0x1);
    }
    else
    {
        AXI_REG_SETBITS(mode, AXI_MON_CNT_CTRL, 1, 2, 0x0);
    }

    /* �������ID���� */
    for(i=0; i<AXI_MAX_ID; i++)
    {
        id_cfg = &mon_config->id_config[i];
        if(!id_cfg->id_en)
        {
            /* ����IDʹ�ܱ�ʶ */
            g_ul_id_en[i] = 0;
        }
        else
        {
            /* ���ü�ض˿� */
            reg_value = id_cfg->port & 0x7;
            AXI_REG_SETBITS(mode, AXI_MON_PORT_SEL, i*3, 3, reg_value);

            /* ���ü�ز������� */
            (void)memcpy_s(&reg_value, sizeof(u32), &id_cfg->opt_type, sizeof(u32));
            AXI_REG_WRITE(mode, AXI_MON_CNT_TYPE(i), reg_value);

            /* ����ID�Ĵ��� */     
            reg_value = ((id_cfg->mask & 0x7FFF) << 15) | (id_cfg->id_value & 0x7FFF);
            /* master id���ʹ�� */
            if(id_cfg->id_mon_en == 1)
            {
                reg_value |= ((u32)1 << 31);
            }
            else
            {
                reg_value &= ~((u32)1 << 31);
            }          
            AXI_REG_WRITE(mode, AXI_MON_CNT_ID(i), reg_value);

            /* ���õ�ַ��� */
            if(id_cfg->addr_en)
            {
                /* ��ַ���ʹ�� */
                AXI_REG_SETBITS(mode, AXI_MON_CNT_ID(i), 30, 1, 1);
                /* �����ʼ��ַ */
                AXI_REG_WRITE(mode, AXI_MON_ID_ADDR_DES(i), id_cfg->addr_start);
                /* ��ؽ�����ַ */
                AXI_REG_WRITE(mode, AXI_MON_ID_ADDR_DES_M(i), id_cfg->addr_end);
            }

            /* ����IDʹ�ܱ�ʶ */
            g_ul_id_en[i] = 1;
        }
    }
}

/*****************************************************************************
 �� �� ��  : axi_capt_set_cnf
 ��������  : �����ɼ���������ظ�������ǰ���õļĴ���״̬��װ�ϱ�
 �������  : axi_config_enum_uint32 mode
 �������  : u32 * out_len �������ݽṹ����
 �� �� ֵ  : AXI_DATA_CONFIG_CNF_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
AXI_DATA_CONFIG_CNF_STRU * axi_capt_set_cnf(axi_config_enum_uint32 mode, u32 * out_len)
{
    AXI_DATA_CONFIG_CNF_STRU * config_cnf;
    u32 i;
    u32 offset;
    u32 len;

    /* �ظ��ļĴ�����Ŀ��AXI_CAPT_CNF_REG_CNT���壬����Ҫʵ���ϱ�������ƥ�� */
    len = sizeof(AXI_DATA_CONFIG_CNF_STRU) + sizeof(AXI_REG_CONFIG_STRU) * AXI_CAPT_CNF_REG_CNT;
    config_cnf = (AXI_DATA_CONFIG_CNF_STRU *)osl_cachedma_malloc(len);
    if(NULL == config_cnf)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: malloc fail\n", __FUNCTION__);
        return NULL;
    }

    config_cnf->ulRegCnt = AXI_CAPT_CNF_REG_CNT;

    /* �ϱ��Ĵ����ռ䲻�������ֶ���д */
    for(i=0; i<10; i++)
    {
        offset = AXI_CAPT_ID_EN + i * 0x4;
        config_cnf->regConfig[i].ulRegOffset = offset;
        AXI_REG_READ(mode, offset, &config_cnf->regConfig[i].ulRegValue);
    }

    config_cnf->regConfig[10].ulRegOffset = AXI_CAPT_TRANS_WAIT_TIME;
    AXI_REG_READ(mode, AXI_CAPT_TRANS_WAIT_TIME, &config_cnf->regConfig[10].ulRegValue);

    for(i=11; i<AXI_CAPT_CNF_REG_CNT-1; i++)
    {
        offset = AXI_CAPT_TRANS_DATA_LEVEL + (i - 11) * 0x4;
        config_cnf->regConfig[i].ulRegOffset = offset;
        AXI_REG_READ(mode, offset, &config_cnf->regConfig[i].ulRegValue);
    }

    config_cnf->regConfig[AXI_CAPT_CNF_REG_CNT-1].ulRegOffset = AXI_CAPT_HEAD_FLAG;
    AXI_REG_READ(mode, AXI_CAPT_HEAD_FLAG, &config_cnf->regConfig[AXI_CAPT_CNF_REG_CNT-1].ulRegValue);

    *out_len = len;

    return  config_cnf;
}

/*****************************************************************************
 �� �� ��  : axi_mon_set_cnf
 ��������  : ���������������ظ�������ǰ���õļĴ���״̬��װ�ϱ�
 �������  : axi_config_enum_uint32 mode
 �������  : u32 * out_len �������ݽṹ����
 �� �� ֵ  : AXI_MON_CONFIG_CNF_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
AXI_MON_CONFIG_CNF_STRU * axi_mon_set_cnf(axi_config_enum_uint32 mode, u32 * out_len)
{
    AXI_MON_CONFIG_CNF_STRU * config_cnf;
    u32 i;
    u32 len;

    /* �ظ��ļĴ�����Ŀ��AXI_CAPT_CNF_REG_CNT���壬����Ҫʵ���ϱ�������ƥ�� */
    len = sizeof(AXI_MON_CONFIG_CNF_STRU) + sizeof(AXI_REG_CONFIG_STRU) * AXI_MON_CNF_REG_CNT;
    config_cnf = (AXI_MON_CONFIG_CNF_STRU *)osl_cachedma_malloc(len);
    if(NULL == config_cnf)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: malloc fail\n", __FUNCTION__);
        return NULL;
    }

    config_cnf->ulRegCnt = AXI_MON_CNF_REG_CNT;

    /* �ϱ��Ĵ����ռ䲻�������ֶ���д */
    /* CNT_CTRL�Ĵ��� */
    config_cnf->regConfig[0].ulRegOffset = AXI_MON_CNT_CTRL;
    AXI_REG_READ(mode, AXI_MON_CNT_CTRL, &config_cnf->regConfig[0].ulRegValue);

    /* ʱ�䴰counter */
    config_cnf->regConfig[1].ulRegOffset = AXI_MON_WIN_COUNTER;
    AXI_REG_READ(mode, AXI_MON_WIN_COUNTER, &config_cnf->regConfig[1].ulRegValue);

    /* ��ض˿�����PORT_SEL */
    config_cnf->regConfig[2].ulRegOffset = AXI_MON_PORT_SEL;
    AXI_REG_READ(mode, AXI_MON_PORT_SEL, &config_cnf->regConfig[2].ulRegValue);

    /* ��ز�������, 8��ID */
    for(i=0; i<AXI_MAX_ID; i++)
    {
        config_cnf->regConfig[i+3].ulRegOffset = AXI_MON_CNT_TYPE(i);
        AXI_REG_READ(mode, AXI_MON_CNT_TYPE(i), &config_cnf->regConfig[i+3].ulRegValue);
    }

    /* ID���á���ַ���� */
    for(i=0; i<AXI_MAX_ID; i++)
    {
        /* ID���� */
        config_cnf->regConfig[i*3 + 11].ulRegOffset = AXI_MON_CNT_ID(i);
        AXI_REG_READ(mode, AXI_MON_CNT_ID(i), &config_cnf->regConfig[i*3 + 11].ulRegValue);
        /* ��ʼ��ַ */
        config_cnf->regConfig[i*3 + 12].ulRegOffset = AXI_MON_ID_ADDR_DES(i);
        AXI_REG_READ(mode, AXI_MON_ID_ADDR_DES(i), &config_cnf->regConfig[i*3 + 12].ulRegValue);
        /* ������ַ */
        config_cnf->regConfig[i*3 + 13].ulRegOffset = AXI_MON_ID_ADDR_DES_M(i);
        AXI_REG_READ(mode, AXI_MON_ID_ADDR_DES_M(i), &config_cnf->regConfig[i*3 + 13].ulRegValue);
    }

    *out_len = len;

    return  config_cnf;
}

/*****************************************************************************
 �� �� ��  : axi_mon_get_reg_value
 ��������  : ��ȡ���ͳ�ƼĴ������
 �������  : axi_config_enum_uint32 mode
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_mon_get_reg_value(axi_config_enum_uint32 mode, AXI_MON_TERMINATE_CNF_STRU * ter_cnf)
{
    AXI_MON_ID_STATISTIC_DATA_STRU * id_stat;
    u32 i;
    
    AXI_REG_READ(mode, AXI_MON_IDLE_COUNTER, &ter_cnf->ulIdelCnt);

    for(i=0; i<AXI_MAX_PORT; i++)
    {
        AXI_REG_READ(mode, AXI_MON_RD_WAIT_CYCLE_PORTS(i), &ter_cnf->ulRdWaitCycle[i]);
        AXI_REG_READ(mode, AXI_MON_WR_WAIT_CYCLE_PORTS(i), &ter_cnf->ulWrWaitCycle[i]);
    }

    for(i=0; i<AXI_MAX_ID; i++)
    {
        id_stat = &(ter_cnf->idStat[i]);

        id_stat->ulIdEn = g_ul_id_en[i];
        AXI_REG_READ(mode, AXI_MON_INCR1_ID(i), &id_stat->ulIncr1Cnt);
        AXI_REG_READ(mode, AXI_MON_INCR2_ID(i), &id_stat->ulIncr2Cnt);
        AXI_REG_READ(mode, AXI_MON_INCR4_ID(i), &id_stat->ulIncr4Cnt);
        AXI_REG_READ(mode, AXI_MON_INCR8_ID(i), &id_stat->ulIncr8Cnt);
        AXI_REG_READ(mode, AXI_MON_INCR16_ID(i), &id_stat->ulIncr16Cnt);
        AXI_REG_READ(mode, AXI_MON_WRAP_ID(i), &id_stat->ulWrapCnt);
        AXI_REG_READ(mode, AXI_MON_BURST_ID(i), &id_stat->ulBurstSendCnt);
        AXI_REG_READ(mode, AXI_MON_FINISH_ID(i), &id_stat->ulBurstFinCnt);
        AXI_REG_READ(mode, AXI_MON_RD_WAIT_ID_LOW(i), &id_stat->ulRdDelayLow);
        AXI_REG_READ(mode, AXI_MON_RD_WAIT_ID_HIGH(i), &id_stat->ulRdDelayHigh);
        AXI_REG_READ(mode, AXI_MON_WR_WAIT_ID_LOW(i), &id_stat->ulWrDelayLow);
        AXI_REG_READ(mode, AXI_MON_WR_WAIT_ID_HIGH(i), &id_stat->ulWrDelayHigh);
        AXI_REG_READ(mode, AXI_MON_WR_WAIT_RESP_ID_LOW(i), &id_stat->ulWrRespDelayLow);
        AXI_REG_READ(mode, AXI_MON_WR_WAIT_RESP_ID_HIGH(i), &id_stat->ulWrRespDelayHigh);
        AXI_REG_READ(mode, AXI_MON_RD_MAX_WAIT_ID(i), &id_stat->ulRdMaxWait);
        AXI_REG_READ(mode, AXI_MON_WR_MAX_WAIT_ID(i), &id_stat->ulWrMaxWait);
        AXI_REG_READ(mode, AXI_MON_WR_MAX_WAIT_RESP_ID(i), &id_stat->ulWrRespMaxWait);
        AXI_REG_READ(mode, AXI_MON_RD_BYTES_ID_LOW(i), &id_stat->ulRdTotalCntLow);
        AXI_REG_READ(mode, AXI_MON_RD_BYTES_ID_HIGH(i), &id_stat->ulRdTotalCntHigh);
        AXI_REG_READ(mode, AXI_MON_WR_BYTES_ID_LOW(i), &id_stat->ulWrTotalCntLow);
        AXI_REG_READ(mode, AXI_MON_WR_BYTES_ID_HIGH(i), &id_stat->ulWrTotalCntHigh);
    }
}

/*****************************************************************************
 �� �� ��  : axi_mon_set_statistic_data
 ��������  : ���������ֹ����ظ�������ǰ���ͳ��ֵ������͸��ϲ�
 �������  : axi_config_enum_uint32 mode
 �������  : u32 * out_len �������ݽṹ����
 �� �� ֵ  : AXI_MON_TERMINATE_CNF_STRU *
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
AXI_MON_TERMINATE_CNF_STRU * axi_mon_set_statistic_data(axi_config_enum_uint32 mode, u32 * out_len)
{
    AXI_MON_TERMINATE_CNF_STRU * ter_cnf;

    ter_cnf = (AXI_MON_TERMINATE_CNF_STRU *)osl_cachedma_malloc(sizeof(AXI_MON_TERMINATE_CNF_STRU));
    if(NULL == ter_cnf)
    {
       bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: alloc fail\n", __FUNCTION__);
       return NULL;
    }

    axi_mon_get_reg_value(mode, ter_cnf);
    *out_len = sizeof(AXI_MON_TERMINATE_CNF_STRU);
    
    return ter_cnf;
}

/*****************************************************************************
 �� �� ��  : axi_mon_info_gen_packet
 ��������  : ʱ�䴰��ؽ���������ϱ�
 �������  : axi_config_enum_uint32 mode
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_mon_info_gen_packet(axi_config_enum_uint32 mode)
{
#if 0
    bsp_socp_head_s *   socp_header      = NULL;
    bsp_om_head_s   *   bsp_om_header    = NULL;
    u8 *    send_buf = NULL;
    u8 *    data;
    u32     data_len;

    /* buffer���� */
    data_len = sizeof(AXI_MON_TERMINATE_CNF_STRU);
    send_buf = (u8 *)bsp_om_get_buf(BSP_OM_SOCP_BUF_TYPE, sizeof(bsp_socp_head_s) + sizeof(bsp_om_head_s) + data_len);
    if(NULL == send_buf)
    {
        g_st_stat_info.mon_ind_fail_cnt++;
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: get buf fail\n", __FUNCTION__);

        return MDRV_ERROR;
    }

    /* ����SOCPͷ */
    socp_header = (bsp_socp_head_s *)send_buf;
    socp_header->service_id         = BSP_SOCP_SID_DIAG_SERVER;
    socp_header->s_service_id       = BSP_SOCP_HIGH4BIT_SSID_ACPU << 4;
    socp_header->service_session_id = BSP_SOCP_SERVER_SESSION_ID;
    socp_header->msg_type           = BSP_SOCP_MSG_TYPE_IND;
    socp_header->msg_trans_id       = g_st_stat_info.mon_ind_cnt++;

    /* ����OMͷ */
    bsp_om_header = (bsp_om_head_s *)(send_buf + sizeof(bsp_socp_head_s));
    bsp_om_header->om_id            = ((u32)BSP_STRU_ID_28_31_GROUP_BSP << 28) | ((u32)BSP_STRU_ID_16_23_BSP_AMON << 16);
    bsp_om_header->data_size        = data_len;

    /* �������� */
    data = send_buf + sizeof(bsp_socp_head_s) + sizeof(bsp_om_head_s);
    axi_mon_get_reg_value(mode, (AXI_MON_TERMINATE_CNF_STRU *)data);

    /* �������� */
    if(MDRV_OK != bsp_om_send_coder_src(send_buf, sizeof(bsp_socp_head_s) + sizeof(bsp_om_head_s) + data_len))
    {
        g_st_stat_info.mon_ind_fail_cnt++;
        (void)bsp_om_free_buf((u32)send_buf, sizeof(bsp_socp_head_s) + sizeof(bsp_om_head_s) + data_len);
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: send data fail\n", __FUNCTION__);

        return MDRV_ERROR;
    }
#endif
    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : axi_capt_ctrl_start
 ��������  : �ɼ����ƣ����������
 �������  : axi_config_enum_uint32 mode
 �������  : ��
 �� �� ֵ  : �ɹ�: 0
             ʧ��: ��0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_capt_ctrl_start(axi_config_enum_uint32 mode)
{
    u32 edma_bindex;
    u32 edma_req_leve;
    u32 i;
    
    AXI_CHECK_INIT();

    /* �����ɼ�����ʱ�ӣ��ɼ�����ʱ�ر� */
    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        if(g_st_amon_clk.is_clk_enable[i] == false)
        {
            axi_sc_clk_open(i);
        }
    }

    
    /* ������·������������������ */
    AXI_CHECK_STATE(mode);

    /* EDMA req levelȡֵ0,1,2,3: ��ʾÿ8, 16, 24, 32�����ݷ�һ������ÿ�����ݵ�λΪ8bytes */
    AXI_REG_GETBITS(mode, AXI_CAPT_TRAN_CONFIG, 5, 2, &edma_req_leve);
    edma_bindex = (edma_req_leve + 1) * 8 * 8;

    /* EDMAͨ����ʼ�� */
    if(MDRV_OK != axi_edma_config_init(mode, edma_bindex))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: config edma fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    g_st_stat_info.edma_bindex = edma_bindex;

    /* �������ڲɼ�timer */
    if(MDRV_OK != axi_start_timer(g_st_stat_info.capt_cycle))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: start capt timer fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ����SOCP timer����ֹSOCP����ʧ�� */
    if(MDRV_OK != axi_socp_start_timer(100))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: start socp timer fail\n", __FUNCTION__);
        return MDRV_ERROR;        
    }
    
    g_st_stat_info.capt_mode  = mode;

    return axi_capt_start(mode);
}

/*****************************************************************************
 �� �� ��  : axi_capt_ctrl_start
 ��������  : �ɼ����ƣ�ֹͣ�����
 �������  : axi_config_enum_uint32 mode
 �������  : ��
 �� �� ֵ  : �ɹ�: 0
             ʧ��: ��0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_capt_ctrl_stop(axi_config_enum_uint32 mode)
{
    s32 ret;
    u32 i;
    axi_state_enum_uint32 axi_state;
    
    AXI_CHECK_INIT();
    
    axi_state = axi_get_state(mode, AXI_GET_RUN_STATE_REQ);
    /* AXI monitorδ���� */
    if(axi_state == AXI_IDLE || axi_state == AXI_STOP)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: monitor has been stopped\n", __FUNCTION__);
        return MDRV_ERROR;
    }

     /* ֹͣtimer */
    axi_stop_timer();

    if(MDRV_OK != axi_capt_stop(mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: stop capture fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    
    /* �ͷ�EDMAͨ�� */
    if(MDRV_OK != axi_edma_free(mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: free edma fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ֹͣMonitor */
    ret = axi_mon_stop(mode);

    /* �ͷ�SOCP timer */
    if(g_st_socp_timer.init_flags == TIMER_INIT_FLAG)
    {
        (void)bsp_softtimer_free(&g_st_socp_timer);
    }
    
    /* �ɼ��������ر�ʱ�� */
    for(i=0; i<AXI_CONFIG_BUTT; i++)
    {
        if(g_st_amon_clk.is_clk_enable[i] == true)
        {
            axi_sc_clk_close(i);
        } 
    }
    
    return ret;
}

/*****************************************************************************
 �� �� ��  : axi_capt_ctrl_export
 ��������  : �ɼ����ƣ����������
 �������  : axi_config_enum_uint32 mode
 �������  : ��
 �� �� ֵ  : �ɹ�: 0
             ʧ��: ��0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 axi_capt_ctrl_export(axi_config_enum_uint32 mode)
{
    /* ����ѽ��в����������������� */
    if(g_sl_init_flag == true)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: something done before export\n", __FUNCTION__);
        return MDRV_ERROR;       
    }

    bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: entered\n", __FUNCTION__);

    /* ��λ�󵼳�����Ҫ�ȳ�ʼ�� */
    if(MDRV_OK != axi_init())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: init fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* monitor�ڲ���λ */
    (void)axi_reset(mode);
   
    /* ������buffer */
    axi_reset_pkg_buf(mode);

    /* EDMAͨ����ʼ�� */
    if(MDRV_OK != axi_edma_config_init(mode, AXI_EDMA_BINDEX))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: config edma fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ����Monitor bufferѡ��Ĭ�ϻ���SOC���� */
    if(AXI_CPUFAST_CONFIG == mode)
    {
        AXI_REG_SETBITS(mode, AXI_CAPT_TRAN_CONFIG, 4, 1, 1);
    }

    /* ȥ���ж����Σ��������ж����� */
    AXI_REG_WRITE(mode, AXI_CAPT_INT_MASK, 0xD);

    /* ����monitor */
    if(MDRV_OK != axi_mon_start(mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: start monitor 0x%x fail\n", __FUNCTION__, mode);
        return MDRV_ERROR;
    }

    if(MDRV_OK != axi_capt_stop(mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: stop capture fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* ֹͣmonitor */
    if(MDRV_OK != axi_mon_stop(mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: stop monitor 0x%x fail\n", __FUNCTION__, mode);
        return MDRV_ERROR;
    }
    
    /* �ͷ�EDMAͨ�� */
    if(MDRV_OK != axi_edma_free(mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: free edma fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    /* �����������ر�ʱ�� */
    if(g_st_amon_clk.is_clk_enable[mode] == true)
    {
        axi_sc_clk_close(mode);
    } 

    amon_error("%s: ok\n", __FUNCTION__);

    return MDRV_OK;
}

s32 amon_addr_is_enable(void)
{
    if((g_amon_config.en_flag & AMON_SOC_MASK) || (g_amon_config.en_flag  & AMON_CPUFAST_MASK))
    {
        return MDRV_OK;
    }

    return MDRV_ERROR;
}

/*****************************************************************************
 �� �� ��  : bsp_axi_capt_config
 ��������  : �ɼ����ýӿ�
 �������  : data    : �ɼ��������ݽṹָ��
 �������  : out_len : �ɼ��Ĵ�������״̬���ݽṹ����
 �� �� ֵ  : ���óɹ�: AXI_DATA_CONFIG_CNF_STRU *
             ����ʧ��: NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
AXI_DATA_CONFIG_CNF_STRU * bsp_axi_capt_config(u8 * data, u32 * out_len)
{
    axi_capt_config_t * capt_config;
    AXI_DATA_CONFIG_CNF_STRU * cfg_cnf;

    if(NULL == data || NULL == out_len)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid para\n", __FUNCTION__);
        return NULL;
    }

    if(MDRV_OK == amon_addr_is_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: addr monitor is enable\n", __FUNCTION__);
        return NULL;
    }
    
    capt_config = (axi_capt_config_t *)data;

    if(capt_config->mode >= AXI_CONFIG_BUTT)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid mode %u\n", __FUNCTION__, capt_config->mode);
        return NULL;
    }

    if(g_ul_k3_flag && (capt_config->mode == AXI_CPUFAST_CONFIG))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): cpufast is not supported for k3\n", __FUNCTION__, capt_config->mode);
        return NULL;
    }

    /* ���״����ã���ʱ�� */
    if(g_sl_init_flag == true && g_st_amon_clk.is_clk_enable[capt_config->mode] == false)
    {
        axi_sc_clk_open(capt_config->mode);
    }
    else
    {
        /* �״�����ǰ���г�ʼ�� */
        if(MDRV_OK != axi_init())
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: init fail\n", __FUNCTION__);
            return NULL;
        }
    }
    
    if(MDRV_OK != axi_state_check(capt_config->mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI %d is running\n", __FUNCTION__, capt_config->mode);
        return NULL;
    }

    /* Monitor�ڲ���λ */
    (void)axi_reset(capt_config->mode);
    /* ϵͳ��������λ */
    axi_sc_reset();

    /* ���òɼ����� */
    axi_capt_config(capt_config);

    /* ����ɼ����� */
    g_st_stat_info.capt_cycle = capt_config->capt_cycle;

    /* �õ�ǰ���ù���CNF */
    cfg_cnf = axi_capt_set_cnf(capt_config->mode, out_len);

    /* �ر�ʱ�� */
    axi_sc_clk_close(capt_config->mode);
    
    return cfg_cnf;
}

/*****************************************************************************
 �� �� ��  : bsp_axi_reg_config
 ��������  : �ɼ�����ؼĴ������ýӿ�
 �������  : data    : �ɼ�������������ݽṹָ��
 �������  : ��
 �� �� ֵ  : ���óɹ�: 0
             ����ʧ��: ��0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 bsp_axi_reg_config(u8 * data)
{
    axi_reg_config_t * reg_config;
    u32 i;

    if(NULL == data)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid para\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    if(MDRV_OK == amon_addr_is_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: addr monitor is enable\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    reg_config = (axi_reg_config_t *)data;

    AXI_CHECK_MODE(reg_config->mode);

    if(g_ul_k3_flag && (reg_config->mode == AXI_CPUFAST_CONFIG))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): cpufast is not supported for k3\n", __FUNCTION__, reg_config->mode);
        return MDRV_ERROR;
    }

    /* ���״����ã���ʱ�� */
    if(g_sl_init_flag == true && g_st_amon_clk.is_clk_enable[reg_config->mode] == false)
    {
        axi_sc_clk_open(reg_config->mode);
    }
    else
    {
        /* �״�����ǰ���г�ʼ�� */
        if(MDRV_OK != axi_init())
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: init fail\n", __FUNCTION__);
            return MDRV_ERROR;
        }
    }

    AXI_CHECK_STATE(reg_config->mode);

    /* Monitor�ڲ���λ */
    (void)axi_reset(reg_config->mode);
    /* ϵͳ��������λ */
    axi_sc_reset();

    /* ���òɼ��Ĵ��� */
    for(i=0; i<reg_config->reg_cnt; i++)
    {
        AXI_REG_WRITE(reg_config->mode, reg_config->reg_cfg[i].reg_offset, reg_config->reg_cfg[i].reg_value);
    }

    /* ����ɼ����� */
    g_st_stat_info.capt_cycle = reg_config->capt_cycle;

    /* �ر�ʱ�� */
    axi_sc_clk_close(reg_config->mode);

    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : bsp_axi_capt_ctrl
 ��������  : �ɼ����������
 �������  : data    : �ɼ������������ݽṹָ��
 �������  : ��
 �� �� ֵ  : �ɹ�: 0
             ʧ��: ��0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 bsp_axi_capt_ctrl(u8 * data)
{
    axi_ctrl_t * ctrl_stu;
    axi_config_enum_uint32 mode;

    if(NULL == data)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid para\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    if(MDRV_OK == amon_addr_is_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: addr monitor is enable\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    ctrl_stu = (axi_ctrl_t *)data;
    mode     = (axi_config_enum_uint32)ctrl_stu->mode;

    AXI_CHECK_MODE(mode);

    if(ctrl_stu->ctrl_type >= AXI_CTRL_BUTT)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid ctrl type %u\n", __FUNCTION__, ctrl_stu->ctrl_type);
        return MDRV_ERROR;
    }

    if(g_ul_k3_flag && (mode == AXI_CPUFAST_CONFIG))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): cpufast is not supported for k3\n", __FUNCTION__, mode);
        return MDRV_ERROR;
    }

    /* ���� */
    if(AXI_CTRL_START == ctrl_stu->ctrl_type)
    {
        return axi_capt_ctrl_start(mode);
    }
    /* ֹͣ */
    else if(AXI_CTRL_STOP == ctrl_stu->ctrl_type)
    {
        return axi_capt_ctrl_stop(mode);
    }
    /* ���� */
    else
    {
        return axi_capt_ctrl_export(mode);
    }
}

/*****************************************************************************
 �� �� ��  : bsp_axi_mon_config
 ��������  : ������ýӿ�
 �������  : data    : ����������ݽṹָ��
 �������  : out_len : ��ؼĴ�������״̬���ݽṹ����
 �� �� ֵ  : ���óɹ�: AXI_MON_CONFIG_CNF_STRU *
             ����ʧ��: NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
AXI_MON_CONFIG_CNF_STRU * bsp_axi_mon_config(u8 * data, u32 * out_len)
{
    axi_mon_config_t * mon_config;
    AXI_MON_CONFIG_CNF_STRU * cfg_cnf;

    if(NULL == data || NULL == out_len)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid para\n", __FUNCTION__);
        return NULL;
    }
    
    if(MDRV_OK == amon_addr_is_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: addr monitor is enable\n", __FUNCTION__);
        return NULL;
    }

    mon_config = (axi_mon_config_t *)data;

    if(mon_config->mode >= AXI_CONFIG_BUTT)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid mode %u\n", __FUNCTION__, mon_config->mode);
        return NULL;
    }

    if(g_ul_k3_flag && (mon_config->mode == AXI_CPUFAST_CONFIG))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): cpufast is not supported for k3\n", __FUNCTION__, mon_config->mode);
        return NULL;
    }

    /* ���״����ã���ʱ�� */
    if(g_sl_init_flag == true && g_st_amon_clk.is_clk_enable[mon_config->mode] == false)
    {
        axi_sc_clk_open(mon_config->mode);
    }
    else
    {
        /* �״�����ǰ���г�ʼ�� */
        if(MDRV_OK != axi_init())
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: init fail\n", __FUNCTION__);
            return NULL;
        }
    }

    if(MDRV_OK != axi_state_check(mon_config->mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI %d is running\n", __FUNCTION__, mon_config->mode);
        return NULL;
    }

    /* Monitor�ڲ���λ */
    (void)axi_reset(mon_config->mode);
    /* ϵͳ��������λ */
    axi_sc_reset();

    /* ���òɼ����� */
    axi_mon_config(mon_config);

    /* �õ�ǰ���ù���CNF */
    cfg_cnf = axi_mon_set_cnf(mon_config->mode, out_len);

    /* �ر�ʱ�� */
    axi_sc_clk_close(mon_config->mode);
        
    return cfg_cnf;
}

/*****************************************************************************
 �� �� ��  : bsp_axi_mon_start
 ��������  : ������������
 �������  : data: ��������������ݽṹָ��
 �������  : ��
 �� �� ֵ  : �ɹ�: 0
             ʧ��: ��0
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 bsp_axi_mon_start(u8 * data)
{
    axi_ctrl_t * ctrl_stu;

    if(NULL == data)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: null pointer\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    if(MDRV_OK == amon_addr_is_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: addr monitor is enable\n", __FUNCTION__);
        return MDRV_ERROR;
    }

    ctrl_stu = (axi_ctrl_t *)data;

    AXI_CHECK_MODE(ctrl_stu->mode);

    if(g_ul_k3_flag && (ctrl_stu->mode == AXI_CPUFAST_CONFIG))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): cpufast is not supported for k3\n", __FUNCTION__, ctrl_stu->mode);
        return MDRV_ERROR;
    }

    /* �������ͼ�� */
    if(AXI_CTRL_START != ctrl_stu->ctrl_type)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid ctrl type %u\n", __FUNCTION__, ctrl_stu->ctrl_type);
        return MDRV_ERROR;
    }

    /* �Ƿ��ʼ��������δ������ֱ������ */
    AXI_CHECK_INIT();

    /* ������أ���ʱ�ӣ���ؽ���ʱ�ر� */
    if(g_st_amon_clk.is_clk_enable[ctrl_stu->mode] == false)
    {
        axi_sc_clk_open(ctrl_stu->mode);
    }

    return axi_mon_start(ctrl_stu->mode);
}

/*****************************************************************************
 �� �� ��  : bsp_axi_mon_terminate
 ��������  : ���ֹͣ�����������
 �������  : data   : �����ֹ�������ݽṹָ��
 �������  : out_len: �������ݽṹ����
 �� �� ֵ  : �ɹ�: AXI_MON_TERMINATE_CNF_STRU *
             ʧ��: NULL
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
AXI_MON_TERMINATE_CNF_STRU * bsp_axi_mon_terminate(u8 * data, u32 * out_len)
{
    axi_ctrl_t * ctrl_stu;
    axi_config_enum_uint32 mode;
    AXI_MON_TERMINATE_CNF_STRU * ter_cnf;

    if(NULL == data || NULL == out_len)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: null pointer\n", __FUNCTION__);
        return NULL;
    }

    if(MDRV_OK == amon_addr_is_enable())
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: addr monitor is enable\n", __FUNCTION__);
        return NULL;
    }

    ctrl_stu = (axi_ctrl_t *)data;
    mode     = (axi_config_enum_uint32)ctrl_stu->mode;

    if(mode >= AXI_CONFIG_BUTT)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid mode %u\n", __FUNCTION__, mode);
        return NULL;
    }

    if(g_ul_k3_flag && (mode == AXI_CPUFAST_CONFIG))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): cpufast is not supported for k3\n", __FUNCTION__, mode);
        return NULL;
    }

    if(ctrl_stu->ctrl_type != AXI_CTRL_STOP && ctrl_stu->ctrl_type != AXI_CTRL_EXPORT)
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: invalid ctrl type %u\n", __FUNCTION__, ctrl_stu->ctrl_type);
        return NULL;
    }

    if(MDRV_OK != axi_mon_stop(mode))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: stop monitor %u fail\n", __FUNCTION__, mode);
        return NULL;
    }

    ter_cnf = axi_mon_set_statistic_data(mode, out_len);

    /* ��ؽ������ر�ʱ�� */
    if(g_st_amon_clk.is_clk_enable[mode] == true)
    {
        axi_sc_clk_close(mode);
    }   
    
    return ter_cnf;
}

/*****************************************************************************
 �� �� ��  : axi_print_debug_info
 ��������  : ��ӡ��Ϣ
 �������  : ��
 �� �� ֵ  : u32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_print_debug_info(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    u32 reg_value = 0;

    if(g_ul_k3_flag && (config == AXI_CPUFAST_CONFIG))
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s(%u): cpufast is not supported for k3\n", __FUNCTION__, config);
        return;
    }

    axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
    amon_error("AXI running state       : 0x%x\n", axi_state);

    AXI_REG_READ(config, AXI_MON_WIN_COUNTER, &reg_value);
    amon_error("AXI window counter      : 0x%x\n", reg_value);

    AXI_REG_READ(config, AXI_CAPT_ERR_STATE, &reg_value);
    amon_error("AXI capture state       : 0x%x\n", reg_value);

    AXI_REG_READ(config, AXI_CAPT_TRANS_DATA_CNT, &reg_value);
    amon_error("AXI trans data cnt      ; 0x%x\n", reg_value);

    AXI_REG_READ(config, AXI_CAPT_TRANS_DATA_CNT_HIGH, &reg_value);
    amon_error("AXI trans data cnt high ; 0x%x\n", reg_value);
    amon_error("AXI CPUFAST EDMA channel: %d\n", g_sl_edma_channel[AXI_CPUFAST_CONFIG]);
    amon_error("AXI SOC EDMA channel    : %d\n", g_sl_edma_channel[AXI_SOC_CONFIG]);
}

/*****************************************************************************
 �� �� ��  : axi_print_int_cnt
 ��������  : ��ӡ�ж�ͳ����Ϣ
 �������  : ��
 �� �� ֵ  : u32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_print_int_cnt(void)
{
    amon_error("AXI win over cnt        : %d\n", g_st_stat_info.int_stat.win_over);
    amon_error("AXI buff over cnt       : %d\n", g_st_stat_info.int_stat.buff_over);
    amon_error("AXI tran threshold cnt  : %d\n", g_st_stat_info.int_stat.tran_thresh);
    amon_error("AXI tran req cnt        : %d\n", g_st_stat_info.int_stat.tran_req);
    amon_error("AXI tran over cnt       : %d\n", g_st_stat_info.int_stat.tran_over);
    amon_error("AXI edma tran over cnt  : %d\n", g_st_stat_info.int_stat.edma_tran_over);
    amon_error("AXI capt buff full cnt  : %d\n", g_st_stat_info.axi_buf_full);
    amon_error("AXI edma tran fail cnt  : %d\n", g_st_stat_info.edma_tran_fail);
    amon_error("AXI socp buff full cnt  : %d\n", g_st_stat_info.socp_buf_full);
    amon_error("AXI socp tran fail cnt  : %d\n", g_st_stat_info.socp_tran_fail);
    amon_error("AXI mon ind cnt         : %d\n", g_st_stat_info.mon_ind_cnt);
    amon_error("AXI mon ind fail cnt    : %d\n", g_st_stat_info.mon_ind_fail_cnt);
}

/*****************************************************************************
 �� �� ��  : axi_print_ring_buf_info
 ��������  : ��ӡѭ��bufferָ��״̬
 �������  : ��
 �� �� ֵ  : u32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void axi_print_ring_buf_info(void)
{
    if(!g_ul_k3_flag)
    {
        amon_error("********* CPUFAST RING BUFFER *********\n");
        amon_error("CPUFAST START: 0x%x\n", (u32)g_st_ring_buf_info[0].start);
        amon_error("CPUFAST END  : 0x%x\n", (u32)g_st_ring_buf_info[0].end);
        amon_error("CPUFAST READ : 0x%x\n", (u32)g_st_ring_buf_info[0].read);
        amon_error("CPUFAST WRITE: 0x%x\n", (u32)g_st_ring_buf_info[0].write);
    }

    amon_error("*********   SOC RING BUFFER   *********\n");
    amon_error("SOC START    : 0x%x\n", (u32)g_st_ring_buf_info[1].start);
    amon_error("SOC END      : 0x%x\n", (u32)g_st_ring_buf_info[1].end);
    amon_error("SOC READ     : 0x%x\n", (u32)g_st_ring_buf_info[1].read);
    amon_error("SOC WRITE    : 0x%x\n", (u32)g_st_ring_buf_info[1].write);
}
void axi_make_pclint_happy(void)
{
	amon_cpufast_clk_enable();
	amon_cpufast_clk_disable();
}

void axi_capt_test_config(u32 port, u32 mask, u32 value)
{
    axi_capt_config_t capt_config = {};
    u32 cnf = 0;    
    

    capt_config.mode = AXI_SOC_CONFIG;
    capt_config.port = port;
    capt_config.op_type = 0;
    capt_config.dma_req_level = 0;
    capt_config.cmd_pkg_len = 0x2F;
    capt_config.data_pkg_len = 0x5F;
    capt_config.ext_pkg_len = 0x1F;
    capt_config.data_trans_thr = 0x100;
    capt_config.dma_req_type = 0x2;
    capt_config.capt_cycle = 10000000;

    capt_config.id_cfg[0].id_en = 1;
    capt_config.id_cfg[0].id_value = value;
    capt_config.id_cfg[0].mask = mask;

    (void)bsp_axi_capt_config((u8 *)&capt_config, &cnf);
    
    (void)axi_capt_ctrl_start(capt_config.mode);
#if 0
    axi_capt_ctrl_stop(capt_config.mode);
#endif
}

/*lint -restore +e40*/
#ifdef __cplusplus
}
#endif

