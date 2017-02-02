

#ifdef __cplusplus
extern "C"
{
#endif
#include "securec.h"
#include <stdlib.h>
#include <string.h>
#include "osl_irq.h"
#include "bsp_memmap.h"
#include "bsp_om_api.h"
#include "bsp_version.h"
#include <of.h>
#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "bsp_dump.h"
#include <bsp_shared_ddr.h>
#include "bsp_dpm.h"
#include <bsp_hardtimer.h>
#include "amon_balong.h"




/* AXI״̬��飬�Ƿ��������У�������ʱ�����������û��߻�ȡͳ������ */
#define AXI_CHECK_STATE(config) \
do{\
    if(MDRV_OK != amon_state_check(config))\
    {\
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_AMON, "%s: AXI %d is running\n", __FUNCTION__, config);\
        return MDRV_ERROR;\
    }\
}while(0)

/* axi monitor���� */
amon_config_stru g_amon_config;
/* ���ͳ�� */
amon_stat_t g_amon_stat;
/* log��¼ */
amon_buff_info_t g_amon_buff;
extern u32 g_amon_irq;
#ifdef BSP_CONFIG_HI3650
#ifdef CONFIG_CCORE_PM
axi_reg_bak_t g_st_reg_bak;
#endif
#endif

struct amon_ctrl_struct g_amon_ctrl = {};

void amon_int_handler(void);
axi_state_enum_uint32 amon_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req);
s32 amon_state_check(axi_config_enum_uint32 config);
s32 amon_reset(axi_config_enum_uint32 config);
void amon_config(axi_config_enum_uint32 config);
void amon_debug_reset(void);
void amon_debug_show(void);
void amon_save_log(axi_config_enum_uint32 mode, u32 id, u32 opt_type, amon_config_t * config);

void read_test(u32 addr);
void write_test(u32 addr);
void read_test(u32 addr)
{
    amon_debug("read 0x%x: 0x%x", addr, readl(addr));
}
void write_test(u32 addr)
{
    writel(0x9999aaaa, addr);
}


#ifdef CONFIG_MODULE_BUSSTRESS
void config_amon_test(int i)
{
    g_amon_config.en_flag = AMON_SOC_MASK|AMON_CPUFAST_MASK;
    amon_config_stru configinfo = {};

    if(0 == i)
    {
#if 0
        g_amon_config.soc_config[0].reset_flag = 0;
        g_amon_config.soc_config[0].opt_type = 3;
        g_amon_config.soc_config[0].port = 0;
        g_amon_config.soc_config[0].master_id = 0xFFFF8000;
        g_amon_config.soc_config[0].start_addr = 0x90000000;
        g_amon_config.soc_config[0].end_addr = 0x90040000;
#endif
        g_amon_config.soc_config[1].reset_flag = 0;
        g_amon_config.soc_config[1].opt_type = 3;
        g_amon_config.soc_config[1].port = 2;
        g_amon_config.soc_config[1].master_id = 0xFFFF8000;
        g_amon_config.soc_config[1].start_addr = (u32)DDR_SHARED_MEM_ADDR;
        g_amon_config.soc_config[1].end_addr = (u32)DDR_SHARED_MEM_ADDR + DDR_SHARED_MEM_SIZE;
    }

   if(1 == i)
    {
        g_amon_config.cpufast_config[0].reset_flag = 0;
        g_amon_config.cpufast_config[0].opt_type = 3;
        g_amon_config.cpufast_config[0].port = 0;
        g_amon_config.cpufast_config[0].master_id = 0xFFFF8000;
        g_amon_config.cpufast_config[0].start_addr = 0x45400000;
        g_amon_config.cpufast_config[0].end_addr = 0x455467A0;

        g_amon_config.cpufast_config[1].reset_flag = 0;
        g_amon_config.cpufast_config[1].opt_type = 3;
        g_amon_config.cpufast_config[1].port = 2;
        g_amon_config.cpufast_config[1].master_id = 0xFFFF8000;
        g_amon_config.cpufast_config[1].start_addr = 0x80200000;
        g_amon_config.cpufast_config[1].end_addr = 0x80201000;

    }
    if(2 == i)
    {
        configinfo.en_flag = AMON_SOC_MASK;

        configinfo.soc_config[1].reset_flag = 0;
        configinfo.soc_config[1].opt_type = 3;
        configinfo.soc_config[1].port = 3;
        configinfo.soc_config[1].master_id = 0x0;
        configinfo.soc_config[1].start_addr = (u32)DDR_SHARED_MEM_ADDR;
        configinfo.soc_config[1].end_addr = (u32)DDR_SHARED_MEM_ADDR + DDR_SHARED_MEM_SIZE;

        amon_set_config(configinfo);
    }

}
u32 amon_get_info_test(void)
{
    amon_count_stru count = {};
    u32 ret = 0;
    ret = ret;
    ret = amon_get_info(&count);
    return ret;
}
#endif
/* K3����modemʵ��dpm, V7R2��M3ʵ�� */
#ifdef BSP_CONFIG_HI3650
#ifdef CONFIG_CCORE_PM
s32 amon_suspend(struct dpm_device *dev);
s32 amon_resume(struct dpm_device *dev);

struct dpm_device amon_dpm_device={
	.device_name = "amon_dpm",
	.prepare = NULL,
	.suspend_late = NULL,
	.suspend = amon_suspend,
	.resume = amon_resume,
	.resume_early = NULL,
	.complete = NULL,
};
#endif
#endif

/*****************************************************************************
 �� �� ��  : amon_save_log
 ��������  : ƥ�䵽������¼log
             �����ʽ: timestamp    soc/cpufast    id          port
                       masterid     rd/wr          addr_start  addr_end
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void amon_save_log(axi_config_enum_uint32 mode, u32 id, u32 opt_type, amon_config_t * config)
{
    u32 * data_wr = (u32 *)(g_amon_buff.buff + g_amon_buff.write_offset);
#ifdef BSP_CONFIG_HI3650
    u32 value = 0;
    u32 reg_value;
    u32 mask;
#endif
    if((mode == AXI_CONFIG_BUTT)&&(!(g_amon_config.en_flag&AMON_SOC_MASK)))
    {
#ifdef BSP_CONFIG_HI3650
        if( g_amon_buff.buff_size - g_amon_buff.write_offset < 14*sizeof(u32))
        {
            data_wr = (u32*)g_amon_buff.buff;
            g_amon_buff.write_offset = 0;
        }

        if(amon_stop(AXI_SOC_CONFIG))
        {
            amon_error("stop soc monitor fail\n");
            return;
        }
        *data_wr     = 0x5A5A5A5A;

        *(data_wr+1) = om_timer_get();
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_SRC, &value);
        *(data_wr+2) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &value);
        *(data_wr+3) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_STAT, &value);
        *(data_wr+4) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(0), &value);
        *(data_wr+5) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(0), &value);
        *(data_wr+6) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(0), &value);
        *(data_wr+7) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(0), &value);
        *(data_wr+8) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(1), &value);
        *(data_wr+9) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(1), &value);
        *(data_wr+10) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(1), &value);
        *(data_wr+11) = value;
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(1), &value);
        *(data_wr+12) = value;

        *(data_wr+13) = 0x5B5B5B5B;
        g_amon_buff.write_offset = (g_amon_buff.write_offset + 14*sizeof(u32))%(g_amon_buff.buff_size);
           /* SOC������ */
       AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_STAT, &reg_value);
       AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &mask);
       AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (reg_value | mask));
       AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_MON_INT_CLR, reg_value<<16);
       system_error(DRV_ERRNO_AMON_SOC_WR,0xABCD, 0, 0, 0);
#endif
    }
    else
    {
        if(!config)
        {
             amon_error("config info is NULL\n");
             return;
        }
        if( g_amon_buff.buff_size - g_amon_buff.write_offset < 0x20)
        {
            data_wr = (u32*)g_amon_buff.buff;
            g_amon_buff.write_offset = 0;
        }

        *data_wr     = om_timer_get();
        *(data_wr+1) = mode;
        *(data_wr+2) = id;
        *(data_wr+3) = config->port;
        *(data_wr+4) = config->master_id;
        *(data_wr+5) = opt_type;
        *(data_wr+6) = config->start_addr;
        *(data_wr+7) = config->end_addr;
        g_amon_buff.write_offset = (g_amon_buff.write_offset + 0x20)%(g_amon_buff.buff_size);
    }
}

/*****************************************************************************
 �� �� ��  : amon_int_handler
 ��������  : �жϴ������������д�ж�
 �������  : ��
 �� �� ֵ  : void
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
void amon_int_handler(void)
{
    u32 i;
    u32 reg_value;
    u32 mask;

#ifdef BSP_CONFIG_HI3650
    amon_save_log(AXI_CONFIG_BUTT, 0, 0, NULL);
#endif
    /* SOC��д�жϴ��� */
    AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_STAT, &reg_value);
    AXI_REG_READ(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &mask);
    AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (reg_value | mask));
    AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_MON_INT_CLR, reg_value<<16);
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        /*lint -save -e701*/
        /* д�ж� */
        if(reg_value & (1<<(i*2)))
        {
            g_amon_stat.soc_wr_cnt[i]++;
            amon_save_log(AXI_SOC_CONFIG, (u32)i, AMON_OPT_WRITE, &g_amon_config.soc_config[i]);
            if(g_amon_config.soc_config[i].reset_flag == 1)
            {
                amon_error("soc id 0x%x wr hit, reboot\n", i);
                /* �������ж�д�ж� */
                AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_SOC_WR, (u32)i, 0, 0, 0);
                return;
            }
            AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (u32)i*2, 1, 0);
        }
        /* ���ж� */
        if(reg_value & (1<<(i*2+1)))
        {
            g_amon_stat.soc_rd_cnt[i]++;
            amon_save_log(AXI_SOC_CONFIG, (u32)i, AMON_OPT_READ, &g_amon_config.soc_config[i]);
            if(g_amon_config.soc_config[i].reset_flag == 1)
            {
                amon_error("soc id 0x%x rd hit, reboot\n", i);
                /* �������ж�д�ж� */
                AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_SOC_RD, (u32)i, 1, 0, 0);
                return;
            }

            AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_ID_INT_MASK, (u32)i*2+1, 1, 0);
        }
    }

#ifndef BSP_CONFIG_HI3650
    /* CPUFAST��д�жϴ��� */
    AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_ID_INT_STAT, &reg_value);
    AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, &mask);
    AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, (mask | reg_value));
    AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_MON_INT_CLR, reg_value<<16);
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        /* д�ж� */
        if(reg_value & (1<<(i*2)))
        {
            g_amon_stat.cpufast_wr_cnt[i]++;
            amon_save_log(AXI_CPUFAST_CONFIG, (u32)i, AMON_OPT_WRITE, &g_amon_config.cpufast_config[i]);
            if(g_amon_config.cpufast_config[i].reset_flag == 1)
            {
                amon_error("cpufast id 0x%x wr hit, reboot\n", i);
                /* �������ж�д�ж� */
                AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_CPUFAST_WR, (u32)i, 2, 0, 0);
                return;
            }
            AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, (u32)i*2, 1, 0);
        }
        /* ���ж� */
        if(reg_value & (1<<(i*2+1)))
        {
            g_amon_stat.cpufast_rd_cnt[i]++;
            amon_save_log(AXI_CPUFAST_CONFIG, (u32)i, AMON_OPT_READ, &g_amon_config.cpufast_config[i]);
            if(g_amon_config.cpufast_config[i].reset_flag == 1)
            {
                amon_error("cpufast id 0x%x rd hit, reboot\n", i);
                /* �������ж�д�ж� */
                AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xffff);
                system_error(DRV_ERRNO_AMON_CPUFAST_RD, (u32)i, 3, 0, 0);
                return;
            }
            AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, (u32)i*2+1, 1, 0);
        }
        /*lint -restore*/
    }
#endif
}
void amon_sc_reset(axi_config_enum_uint32 config)
{
    if(AXI_SOC_CONFIG == config)
    {
        amon_soc_soft_reset();
        /* �⸴λ */
        amon_soc_rls_reset();
        return;
    }
    if(AXI_CPUFAST_CONFIG == config)
    {
        amon_cpufast_soft_reset();
        /* �⸴λ */
        amon_cpufast_rls_reset();
        return;
    }
}

s32 amon_get_info(amon_count_stru *count)
{
    u32 i = 0;
    u32 timeDelta = 0;
    u32 startTime = 0;
    u32 endTime = 0;
	u64 temp = 0;
	u64 timeFreq = 0;

    if(amon_stop(AXI_SOC_CONFIG))
    {
        amon_error("amon stop fail\n");
        return MDRV_ERROR;
    }

    for(i = 0; i < AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &(count->soc_read_count[i].low_count));
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i),&(count->soc_read_count[i].hig_count));
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &(count->soc_write_count[i].low_count));
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i),&(count->soc_write_count[i].hig_count));
    }
    /*�������һ�ε�����֮���master �ڿ����ɵķ��ʵ�����*/
    startTime = g_amon_ctrl.busStressTime[AXI_SOC_CONFIG][AMON_START_TIME];
    endTime = g_amon_ctrl.busStressTime[AXI_SOC_CONFIG][AMON_END_TIME];
    timeDelta = endTime > startTime ? (endTime - startTime):((0xFFFFFFFF - startTime) + endTime);
	temp = (u64)((u64)timeDelta * (u64)MODEM_PORT_WITH);
	timeFreq = (u64)STRESS_TIME_FREQ;
    count->global_access_count = temp/timeFreq;
    count->monitor_time_delta = timeDelta;
	amon_error("timeDelta = 0x%x\n", timeDelta);
    if(MDRV_OK != amon_start(AXI_SOC_CONFIG))
    {
        amon_error("soc start fail\n");
        return MDRV_ERROR;
    }
#ifndef BSP_CONFIG_HI3650
    if(amon_stop(AXI_CPUFAST_CONFIG))
    {
        amon_error("amon stop fail id = 0x%x\n", AXI_CPUFAST_CONFIG);
        return MDRV_ERROR;
    }


    for(i = 0; i < AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &(count->fast_read_count[i].low_count));
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i),&(count->fast_read_count[i].hig_count));
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &(count->fast_write_count[i].low_count));
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i),&(count->fast_write_count[i].hig_count));
    }
    amon_cpufast_soft_reset();
    /* �⸴λ */
    amon_cpufast_rls_reset();
    if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
    {
        amon_error("soc reset fail\n");
        return MDRV_ERROR;
    }
    if(MDRV_OK != amon_start(AXI_CPUFAST_CONFIG))
    {
        amon_error("soc start fail\n");
        return MDRV_ERROR;
    }

#endif
    return MDRV_OK;

}

/*****************************************************************************
 �� �� ��  : �·�����
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
/* coverity[pass by value] */
s32 amon_set_config(amon_config_stru configinfo)
{

    (void)memcpy(&g_amon_config, &configinfo, sizeof(configinfo));

    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        amon_soc_clk_enable();

        if(amon_stop(AXI_SOC_CONFIG))
        {
            amon_error("amon stop fail id = 0x%x\n", AXI_SOC_CONFIG);
            return MDRV_ERROR;
        }
        /* SOCϵͳ��������λ */
        amon_sc_reset(AXI_SOC_CONFIG);
        /* monitor�ڲ���λ */
        if(MDRV_OK != amon_reset(AXI_SOC_CONFIG))
        {
            amon_error("soc reset fail\n");
            return MDRV_ERROR;
        }
        /* �ж����� */
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        amon_config(AXI_SOC_CONFIG);
    }
#ifndef BSP_CONFIG_HI3650
     /* CPUFAST��ʼ�� */
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
		amon_cpufast_clk_enable();
        if(amon_stop(AXI_SOC_CONFIG))
        {
            amon_error("amon stop fail\n");
            return MDRV_ERROR;
        }
        /* CPUFASTϵͳ��������λ */
        amon_sc_reset(AXI_CPUFAST_CONFIG);
        if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
        {
            amon_error("cpufast reset fail id = 0x%x\n", AXI_CPUFAST_CONFIG);
            return MDRV_ERROR;
        }
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
        amon_config(AXI_CPUFAST_CONFIG);
    }
#endif


    return MDRV_OK;
}
/*****************************************************************************
 �� �� ��  : amon_get_state
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
axi_state_enum_uint32 amon_get_state(axi_config_enum_uint32 config, axi_get_state_req_enum_uint32 state_req)
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
 �� �� ��  : amon_state_check
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
s32 amon_state_check(axi_config_enum_uint32 config)
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
 �� �� ��  : amon_reset
 ��������  : monitor�ڲ���λ
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 amon_reset(axi_config_enum_uint32 config)
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
    amon_error("reset 0x%x time out\n", config);
    return MDRV_ERROR;
}

/*****************************************************************************
 �� �� ��  : amon_start
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
s32 amon_start(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
#ifndef CONFIG_MODULE_BUSSTRESS
    amon_config_t * amon_config_local = NULL;
    u32 reg_value = 0xffff;
#endif
    u32 i = 0;

    amon_sc_reset(config);
    if(amon_reset(config))
    {
        amon_error("soft reset error 0x%x\n", config);
    }
    /* �������״̬ */
    AXI_CHECK_STATE(config);

    /* ���ж� */
    AXI_REG_WRITE(config, AXI_MON_INT_CLR, 0xFFFFFFFF);
#ifndef CONFIG_MODULE_BUSSTRESS
    if(config == AXI_SOC_CONFIG)
    {
        amon_config_local = (amon_config_t *)g_amon_config.soc_config;
    }
    else
    {
        amon_config_local = (amon_config_t *)g_amon_config.cpufast_config;
    }
    /*lint -save -e701*/
    /* �����д�ж����Σ�����NV���ù��� */
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        /* ID i��ض����� */
        if(amon_config_local->opt_type & AMON_OPT_READ)
        {
            reg_value = reg_value & (~(u32)(1<<(i*2+1)));
        }
        /* ID i���д���� */
        if(amon_config_local->opt_type & AMON_OPT_WRITE)
        {
            reg_value = reg_value & (~(u32)(1<<(i*2)));
        }
        amon_config_local++;
    }

    AXI_REG_WRITE(config, AXI_ID_INT_MASK, reg_value);
#endif

    /* ����ϵͳ����������Monitor */
    axi_sc_mon_start(config);
    g_amon_ctrl.busStressTime[config][AMON_START_TIME] = bsp_get_slice_value_hrt();

    /* ���������ж����ȴ�������־��λ */
    i=0;
    do
    {
        axi_state = axi_get_state(config, AXI_GET_RUN_STATE_REQ);
        if(AXI_UNWIN_RUNNING == axi_state || AXI_WIN_RUNNING == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);
    /*lint -restore*/
    /* ������ʱ�쳣 */
    amon_error("start 0x%x time out\n", config);
    return MDRV_ERROR;
}

/*****************************************************************************
 �� �� ��  : amon_stop
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
s32 amon_stop(axi_config_enum_uint32 config)
{
    axi_state_enum_uint32 axi_state;
    int i = 0;

    /* ���ζ�д�ж� */
    AXI_REG_WRITE(config, AXI_ID_INT_MASK, 0xFFFFF);

    /* ����ϵͳ������ֹͣMonitor */
    axi_sc_mon_stop(config);
    g_amon_ctrl.busStressTime[config][AMON_END_TIME] = bsp_get_slice_value_hrt();

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
        if(AXI_IDLE == axi_state)
        {
            return MDRV_OK;
        }
    }while(i++ < AXI_WAIT_CNT);

    /* ֹͣMonitor��ʱ�쳣 */
    amon_error("stop 0x%x time out\n", config);
    return MDRV_ERROR;
}

/*****************************************************************************
 �� �� ��  : amon_config
 ��������  : ����monitor���ID
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
void amon_config(axi_config_enum_uint32 config)
{
    u32 i;

    if(AXI_SOC_CONFIG == config)
    {
        for(i=0; i<AXI_MAX_CONFIG_ID; i++)
        {
            /* ���ö˿� */
            AXI_REG_SETBITS(config, AXI_MON_PORT_SEL, i*3, 3, g_amon_config.soc_config[i].port&0x7);
            /* ����masterid */
            AXI_REG_WRITE(config, AXI_MON_CNT_ID(i), g_amon_config.soc_config[i].master_id);
            /* ������ʼ��ַ */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES(i), g_amon_config.soc_config[i].start_addr);
            /* ���ý�����ַ */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES_M(i), g_amon_config.soc_config[i].end_addr);
        }
    }

    if(AXI_CPUFAST_CONFIG == config)
    {
        for(i=0; i<AXI_MAX_CONFIG_ID; i++)
        {
            /* ���ö˿� */
            AXI_REG_SETBITS(config, AXI_MON_PORT_SEL, i*3, 3, g_amon_config.cpufast_config[i].port&0x7);
            /* ����masterid */
            AXI_REG_WRITE(config, AXI_MON_CNT_ID(i), g_amon_config.cpufast_config[i].master_id);
            /* ������ʼ��ַ */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES(i), g_amon_config.cpufast_config[i].start_addr);
            /* ���ý�����ַ */
            AXI_REG_WRITE(config, AXI_MON_ID_ADDR_DES_M(i), g_amon_config.cpufast_config[i].end_addr);
        }
    }
}
s32 amon_get_clk_node(void)
{
    /*soc ʱ��*/
    g_amon_ctrl.soc_clk = clk_get(NULL, "amon_soc_clk");
    if(IS_ERR(g_amon_ctrl.soc_clk))
    {
        amon_error("get amon_soc_clk fail\n");
        return MDRV_ERROR;
    }
#ifndef BSP_CONFIG_HI3650
    /*fast ʱ��*/
    g_amon_ctrl.cpufast_clk = clk_get(NULL, "amon_cpufast_clk");
    if(IS_ERR(g_amon_ctrl.cpufast_clk))
    {
        amon_error("get amon_cpufast_clk fail\n");
        return MDRV_ERROR;
    }
#endif
    return MDRV_OK;
}
/*****************************************************************************
 �� �� ��  : bsp_amon_init
 ��������  : axi monitor��ʼ������ȡNV���ü��ID
 �������  : ��
 �������  : ��
 �� �� ֵ  : s32
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��1��29��
    ��    ��   : f
    �޸�����   : �����ɺ���

*****************************************************************************/
s32 bsp_amon_init(void)
{

    s32 ret = 0;

    /* �жϰ汾 */
	g_amon_ctrl.chip_version = bsp_get_version_info()->chip_type;;

    /* ��ȡNV���� */
#ifdef CONFIG_MODULE_BUSSTRESS
#if 0
    config_amon_test(0);
    config_amon_test(1);
#endif
#else
    if(MDRV_OK != bsp_nvm_read(NV_ID_DRV_AMON, (u8*)&g_amon_config, sizeof(amon_config_stru)))
    {
        amon_error("read nv 0x%x fail\n", NV_ID_DRV_AMON);
        return MDRV_ERROR;
    }
#endif


    ret = axi_get_irq_and_iomap();

    if(MDRV_ERROR == ret)
    {
        amon_error("%s: INT number get fail\n", __FUNCTION__);
        return MDRV_ERROR;
    }
    ret = amon_get_clk_node();
    if(MDRV_ERROR == ret)
    {
        amon_error("amon_get_clk_node fail\n");
        return ret;
    }
    if(amon_soc_state()&&(!(g_amon_config.en_flag&AMON_SOC_MASK)))
    {
        g_amon_buff.buff = (char *)bsp_dump_register_field(DUMP_CP_AMON, "AMON", 0, 0, 0x1000, (AMON_MAIN_VERSION << 8) + AMON_MINOR_VERSION);
        if(BSP_NULL == g_amon_buff.buff)
        {
            amon_error("get buffer fail\n");
            return MDRV_ERROR;
        }
        g_amon_buff.buff_size = 0x1000;

        g_amon_buff.write_offset = 0;
        (void)memset_s(g_amon_buff.buff, g_amon_buff.buff_size, 0, g_amon_buff.buff_size);

        /* ���ж� */
        if(MDRV_OK != request_irq(g_amon_irq, (irq_handler_t)amon_int_handler, 0, "AXI_MON_IRQ", NULL))
        {
            amon_error("INT connect fail\n");
            return MDRV_ERROR;
        }

        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xFFFFFFF0);
        /* ʹ��monitor��ע��dpm */
#ifdef BSP_CONFIG_HI3650
#ifdef CONFIG_CCORE_PM
        if(MDRV_OK != bsp_device_pm_add(&amon_dpm_device))
        {
            amon_error("add amon_dpm_device fail\n");
            return MDRV_ERROR;
        }
        (void)memset_s(&g_st_reg_bak, sizeof(axi_reg_bak_t), 0x0, sizeof(axi_reg_bak_t));
#endif
#endif
        return MDRV_OK;
/*lint -save -e525*/
   }
/*lint -restore*/

    /* δʹ�ܣ�����ʼ�� */
    if(g_amon_config.en_flag == 0)
    {
        return MDRV_OK;
    }

    /* SOC��ʼ�� */
    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        amon_soc_clk_enable();
        /* SOCϵͳ��������λ */
        amon_soc_soft_reset();
        amon_soc_rls_reset();
        /* monitor�ڲ���λ */
        if(MDRV_OK != amon_reset(AXI_SOC_CONFIG))
        {
            amon_error("soc reset fail\n");
            return MDRV_ERROR;
        }
        /* �ж����� */
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_SETBITS(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
        AXI_REG_WRITE(AXI_SOC_CONFIG, AXI_CAPT_INT_MASK, 0xF);
    }

#ifndef BSP_CONFIG_HI3650
     /* CPUFAST��ʼ�� */
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
		amon_cpufast_clk_enable();
        /* CPUFASTϵͳ��������λ */
        amon_cpufast_soft_reset();
        amon_cpufast_rls_reset();
        if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
        {
            amon_error("cpufast reset fail\n");
            return MDRV_ERROR;
        }
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_ID_INT_MASK, 0xFFFF);
        AXI_REG_WRITE(AXI_CPUFAST_CONFIG, AXI_CAPT_INT_MASK, 0xF);
        AXI_REG_SETBITS(AXI_CPUFAST_CONFIG, AXI_MON_CNT_CTRL, 2, 2, 0x3);
    }
#endif

    g_amon_buff.buff = (char *)bsp_dump_register_field(DUMP_CP_AMON, "AMON", 0, 0, 0x1000, (AMON_MAIN_VERSION << 8) + AMON_MINOR_VERSION);
    if(BSP_NULL == g_amon_buff.buff)
    {
        amon_error("get buffer fail\n");
        return MDRV_ERROR;
    }
    g_amon_buff.buff_size = 0x1000;

    g_amon_buff.write_offset = 0;
    (void)memset_s(g_amon_buff.buff, g_amon_buff.buff_size, 0, g_amon_buff.buff_size);

    /* ���ж� */
    if(MDRV_OK != request_irq(g_amon_irq, (irq_handler_t)amon_int_handler, 0, "AXI_MON_IRQ", NULL))
    {
        amon_error("INT connect fail\n");
        return MDRV_ERROR;
    }

    /* ����SOC��� */
    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        amon_config(AXI_SOC_CONFIG);
        if(!(g_amon_config.en_flag&AMON_ENABLE_MASK))
        {
            if(MDRV_OK != amon_start(AXI_SOC_CONFIG))
            {
                amon_error("soc start fail\n");
                return MDRV_ERROR;
            }
        }
    }

#ifndef BSP_CONFIG_HI3650
    /* ����CPUFAST��� */
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
        amon_config(AXI_CPUFAST_CONFIG);
        if(!(g_amon_config.en_flag&AMON_ENABLE_MASK))
        {
            if(MDRV_OK != amon_start(AXI_CPUFAST_CONFIG))
            {
                amon_error("cpufast start fail\n");
                return MDRV_ERROR;
            }
        }
    }
#endif

    amon_debug("%s init ok\n", __FUNCTION__);

    return MDRV_OK;
}

s32 amon_soft_enable(void)
{

    if(g_amon_config.en_flag & AMON_SOC_MASK)
    {
        if(MDRV_OK != amon_reset(AXI_SOC_CONFIG))
        {
            return MDRV_ERROR;
        }
        if(MDRV_OK != amon_start(AXI_SOC_CONFIG))
        {
            amon_error("soc start fail\n");
            return MDRV_ERROR;
        }
    }
#ifndef BSP_CONFIG_HI3650
    if(g_amon_config.en_flag & AMON_CPUFAST_MASK)
    {
        if(MDRV_OK != amon_reset(AXI_CPUFAST_CONFIG))
        {
            return MDRV_ERROR;
        }
        if(MDRV_OK != amon_start(AXI_CPUFAST_CONFIG))
        {
            amon_error("cpufast start fail\n");
            return MDRV_ERROR;
        }
    }
#endif
    return MDRV_OK;
}
void amon_debug_reset(void)
{
    int i;

    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        g_amon_stat.soc_rd_cnt[i]     = 0;
        g_amon_stat.soc_wr_cnt[i]     = 0;
#ifndef BSP_CONFIG_HI3650
        g_amon_stat.cpufast_rd_cnt[i] = 0;
        g_amon_stat.cpufast_wr_cnt[i] = 0;
#endif
    }
}

#if 0
void SRE_SetMonitor(void)
{
#ifdef BSP_CONFIG_HI3650
    u32 value = 0;
    u32 i = 0;

    /*����*/
    writel(0x400000, 0xE0200024);
    /*ѡ��������Դ����ĸ�port*/
    writel(0x2D, 0xE047601C);
    /*���õ�ַʹ��idʹ��*/
    writel(0x40000000, 0xE0476100);
    /*��ʼ��ַ*/
    writel(0x10000000, 0xE0476104);
    /*������ַ*/
    writel(0x37FFFFFF, 0xE0476108);
    /*master id*/
    writel(0x40000000, 0xE0476200);

    writel(0x40000000, 0xE0476204);

    writel(0xDFFFFFFF, 0xE0476208);

    /*��λ*/
    value = readl(0xE0476000);
    value = value|0x2;
    writel(value, 0xE0476000);

    /*�ȴ���λ�ɹ�*/
    i = 0;
    while(i++< 0x40000)
    {
        value = readl(0xE0476008);
        if(0x10 == (value&0x10))
        {
            break;
        }
    }
    /*��λ*/
    writel(0x20000000, 0xE0200060);
    /*�⸴λ*/
    writel(0x20000000, 0xE0200064);

    /*start*/
    value = readl(0xE020040C);
    value = value|0x400;
    writel(value, 0xE020040C);

    /*�ȴ�����*/
    i = 0;
    while(i++< 0x40000)
    {
        value = readl(0xE0476008);
        if(0x8 == (value&0xC))
        {
            break;
        }
    }
#endif
    return;
}
#endif
void amon_debug_show(void)
{
    u32 i;
    u32 reg_value_low;
    u32 reg_value_high;

    /* SOCͳ����Ϣ */
    amon_debug("************SOC STAT************\n");
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("=======ID %d statistics=======\n", i);
        amon_debug("rd int cnt       : 0x%x\n", g_amon_stat.soc_rd_cnt[i]);
        amon_debug("wr int cnt       : 0x%x\n", g_amon_stat.soc_wr_cnt[i]);
        amon_debug("rd total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("rd total bytes(l): 0x%x\n", reg_value_low);
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("wr total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("wr total bytes(l): 0x%x\n", reg_value_low);
    }

    amon_debug("\n");

#ifndef BSP_CONFIG_HI3650
    /* CPUFASTͳ����Ϣ */
    amon_debug("************CPUFAST STAT************\n");
    for(i=0; i<AXI_MAX_CONFIG_ID; i++)
    {
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("=======ID %d statistics=======\n", i);
        amon_debug("rd int cnt: 0x%x\n", g_amon_stat.cpufast_rd_cnt[i]);
        amon_debug("wr int cnt: 0x%x\n", g_amon_stat.cpufast_wr_cnt[i]);
        amon_debug("rd total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("rd total bytes(l): 0x%x\n", reg_value_low);
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_LOW(i), &reg_value_low);
        AXI_REG_READ(AXI_CPUFAST_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(i), &reg_value_high);
        amon_debug("wr total bytes(h): 0x%x\n", reg_value_high);
        amon_debug("wr total bytes(l): 0x%x\n", reg_value_low);
    }
#endif
}

#ifdef BSP_CONFIG_HI3650
#ifdef CONFIG_CCORE_PM
s32 amon_suspend(struct dpm_device *dev)
{
    u32 j;
    u32 reg_value;
    /*lint -save -e958*/
    unsigned long long data_cnt;
    /*lint -restore*/
    u32 data_low;
    u32 data_high;
    axi_reg_bak_t * reg_bak;

    /* ����ǰ����ֹͣmonitor */
    axi_sc_mon_stop(AXI_SOC_CONFIG);

    reg_bak = &g_st_reg_bak;
    /* ���ƼĴ������� */
    axi_reg_read(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, &(reg_bak->ctrl_reg));
    axi_reg_read(AXI_SOC_CONFIG, AXI_MON_PORT_SEL, &(reg_bak->port_reg));
    axi_reg_read(AXI_SOC_CONFIG, AXI_ID_INT_MASK, &(reg_bak->int_mask));
    for(j=0; j<AXI_MAX_CONFIG_ID; j++)
    {
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_CNT_ID(j), &(reg_bak->id_reg[j]));
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES(j), &(reg_bak->addr_start_reg[j]));
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES_M(j), &(reg_bak->addr_end_reg[j]));
    }

    /* ͳ�ƼĴ����ۼ� */
    for(j=0; j<AXI_MAX_CONFIG_ID; j++)
    {
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR1_ID(j), &reg_value);
        reg_bak->incr1_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR2_ID(j), &reg_value);
        reg_bak->incr2_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR4_ID(j), &reg_value);
        reg_bak->incr4_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR8_ID(j), &reg_value);
        reg_bak->incr8_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_INCR16_ID(j), &reg_value);
        reg_bak->incr16_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_WRAP_ID(j), &reg_value);
        reg_bak->wrap_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_BURST_ID(j), &reg_value);
        reg_bak->burst_send_reg[j] += reg_value;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_FINISH_ID(j), &reg_value);
        reg_bak->burst_fin_reg[j] += reg_value;
        /* ��д��������40bit���ȣ���Ҫ�������ֵ */
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_LOW(j), &data_low);
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_RD_BYTES_ID_HIGH(j), &data_high);
        data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->rd_cnt_low_reg[j];
        reg_bak->rd_cnt_high_reg[j] += data_high;
        if(data_cnt >> 32)
        {
            reg_bak->rd_cnt_high_reg[j] += 1;
        }
        reg_bak->rd_cnt_low_reg[j] = (u32)data_cnt;
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_LOW(j), &data_low);
        axi_reg_read(AXI_SOC_CONFIG, AXI_MON_WR_BYTES_ID_HIGH(j), &data_high);
        data_cnt = (unsigned long long)data_low + (unsigned long long)reg_bak->wr_cnt_low_reg[j];
        reg_bak->wr_cnt_high_reg[j] += data_high;
        if(data_cnt >> 32)
        {
            reg_bak->wr_cnt_high_reg[j] += 1;
        }
        reg_bak->wr_cnt_low_reg[j] = (u32)data_cnt;
    }
    /* �ر�ʱ�� */
    amon_soc_clk_disable();
    return MDRV_OK;
}

s32 amon_resume(struct dpm_device *dev)
{
    u32 j;
    axi_reg_bak_t * reg_bak;

    reg_bak = &g_st_reg_bak;

    /* �ȴ�ʱ�� */
    amon_soc_clk_enable();

    axi_reset(AXI_SOC_CONFIG);

    /* �ָ����üĴ��� */
    axi_reg_write(AXI_SOC_CONFIG, AXI_MON_CNT_CTRL, reg_bak->ctrl_reg);
    axi_reg_write(AXI_SOC_CONFIG, AXI_MON_PORT_SEL, reg_bak->port_reg);
    axi_reg_write(AXI_SOC_CONFIG, AXI_ID_INT_MASK, reg_bak->int_mask);
    for(j=0; j<AXI_MAX_CONFIG_ID; j++)
    {
        axi_reg_write(AXI_SOC_CONFIG, AXI_MON_CNT_ID(j), reg_bak->id_reg[j]);
        axi_reg_write(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES(j), reg_bak->addr_start_reg[j]);
        axi_reg_write(AXI_SOC_CONFIG, AXI_MON_ID_ADDR_DES_M(j), reg_bak->addr_end_reg[j]);
    }

    /* ����monitor */
    axi_sc_mon_start(AXI_SOC_CONFIG);

    return MDRV_OK;
}
#endif
#endif


void amon_make_pclint_happy(void)
{
    amon_cpufast_start();
    amon_soc_start();
    amon_cpufast_stop();
    amon_soc_stop();
    amon_cpufast_clk_enable();
    amon_soc_clk_enable();
    amon_cpufast_clk_disable();
    amon_soc_clk_disable();
}

#ifdef __cplusplus
}
#endif

