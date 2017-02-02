/******************************************************************************/
/*  Copyright (C), 2007-2013, Hisilicon Technologies Co., Ltd. */
/******************************************************************************/
/* File name     : hi_apb_mipi.c */
/* Version       : 2.0 */
/* Created       : 2013-03-13*/
/* Last Modified : */
/* Description   :  The C union definition file for the module apb_mipi*/
/* Function List : */
/* History       : */
/* 1 Date        : */
/* Modification  : Create file */
/******************************************************************************/
/*lint --e{537}*/
#ifdef __cplusplus /* __cplusplus */
extern "C"
{
#endif /* __cplusplus */

#include "soc_memmap.h"
#include <osl_bio.h>
#include "bbp_mipi_balong.h"
#include "hi_bbp_mipi.h"
#include <osl_irq.h>
#include "bsp_version.h"
#include "bsp_hardtimer.h"
/*****************************************************************************
*
*      ȫ�ֱ���
*
*****************************************************************************/

u32 BBP_MIPI_BASE_ADDR[MIPI_BUTT];
static MIPI_INIT_STRU mipi_init;
static u32 mipi_init_flag = 0;
/*****************************************************************************
*
*      ��������
*
*****************************************************************************/

int bsp_mipi_config_frame( u64 trans_type,u64 reg_addr, u64 data,MIPI_CMD_STRU *cmd);


u32 bsp_mipi_parity_check(u8 check_data )
{
    u32 bit=0;
    u32 mask=0;
    u32 count = 0;

    /* ͳ��ÿ��bitλ���϶���Ϊ1 */
    for( bit = 0 ; bit < sizeof(u8)*BIT_CNT+1 ; ++bit)
    {
        mask = (u16)0x1 << bit;
        if(mask == (check_data & mask))
        {
            count++;
        }
    }

    /* ��1�ĸ���Ϊ������������żУ��λΪ0��������żУ��λ1 */
    if(1 == (count%2))
    {
        return 0;
    }
    return 1;
}


int bsp_mipi_data_rev(u8 reg_addr,u8 *data,MIPI_CTRL_ENUM mipi_id)
{
	MIPI_CMD_STRU mipi_cmd;
	u32 count=0;
	u32 reg_val=0;
	u32 data_high;
	u32 data_low;
	u64 reg_addr_temp=reg_addr;
	*data=0xff;
	unsigned long flag=0;

	if((0x0 == reg_addr)||(0x0 == data))
	{
		mipi_print_error("ERROR:para is invalid!\n");
		return MIPI_ERROR;
	}

	/*����֡���ݸ�ʽ*/
	bsp_mipi_config_frame(MIPI_EXTENDED_READ,reg_addr_temp,0, &mipi_cmd);

	/*���������Ĵ���*/
	local_irq_save(flag);

	/*����DSP_MIPI_EN_IMI������xbbp����������*/
	set_bbp_mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi(1,mipi_id);

	/*д������֡*/
	set_bbp_mipi_dsp_mipi0_wdata_low_dsp_mipi0_wdata_low(mipi_cmd.mipi_cmd_low,mipi_id);
	set_bbp_mipi_dsp_mipi0_wdata_high_dsp_mipi0_wdata_high(mipi_cmd.mipi_cmd_high,mipi_id);

	/*ѭ���ȴ�MIPI_GRANT_DSPΪ�ߣ�mipi_grant_dspΪ0ʱ��ʾmipi������Ӧ������Ӧ��Ͻ�����Ϊ1*/
	count=0;
	reg_val= get_bbp_mipi_mipi0_grant_dsp_mipi0_grant_dsp(mipi_id);

	while(MIPI_GRANT_DSP_FLAG_IS_HIGH != reg_val)
	{
        if(++count > MIPI_REG_WAIT_TIMEOUT)
        {
            /*����DSP_MIPI_EN_IMI*/
            set_bbp_mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi(0,mipi_id);
            mipi_print_error("wait for MIPI_GRANT_DSP timeout: %d\n",count);
	    	local_irq_restore(flag);
            return MIPI_ERROR;
        }

    	reg_val= get_bbp_mipi_mipi0_grant_dsp_mipi0_grant_dsp(mipi_id);
	}

	/*��DSP_MIPI_CFG_IND_IMI����1*/
	set_bbp_mipi_dsp_mipi0_cfg_ind_imi_dsp_mipi0_cfg_ind_imi(1,mipi_id);

	/*ѭ���ȴ�mipi_rd_end_flag_mipi0_soft_rd_end_flagΪ1��Ϊ1ʱ��ʾ�����ݼĴ�����Ч*/
	count=0;
	reg_val= get_bbp_mipi_rd_end_flag_mipi0_soft_rd_end_flag_mipi0_soft(mipi_id);

	while(RD_END_FLAG_MIPI_SOFT_FLAG_IS_HIGH != reg_val)
	{
		if(++count > MIPI_REG_WAIT_TIMEOUT)
		{
			/*����DSP_MIPI_EN_IMI*/
			set_bbp_mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi(0,mipi_id);
			mipi_print_error("wait for RD_END_FLAG_MIPI_SOFT timeout: %d\n",count);
			local_irq_restore(flag);
			return MIPI_ERROR;
		}
		reg_val= get_bbp_mipi_rd_end_flag_mipi0_soft_rd_end_flag_mipi0_soft(mipi_id);

	}
    /*��״̬λΪ1ʱ*/
    /*��MIPI_RD_DATA_LOW/HIGH_SOFT[31:0]�л�ȡ���ݣ���ֵ���������*/
	data_low=get_bbp_mipi_mipi0_rd_data_low_soft_mipi0_rd_data_low_soft(mipi_id);
	data_high=get_bbp_mipi_mipi0_rd_data_high_soft_mipi0_rd_data_high_soft(mipi_id);

    /*��DSP_MIPI_RD_CLRд��1����RD_END_FLAG_MIPI_SOFT��־λ*/
    set_bbp_mipi_dsp_mipi0_rd_clr_dsp_mipi0_rd_clr(1,mipi_id);

	/*����DSP_MIPI_EN_IMI*/
    set_bbp_mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi(0,mipi_id);

	/*�ͷŻ�����*/
    local_irq_restore(flag);

	*data=MIPI_EXTENDED_WR_FIRST_DATA_FRAME_GET(data_high, data_low);
	return MIPI_OK;
}


int bsp_mipi_data_send(u8 reg_addr,u8 data,MIPI_CTRL_ENUM mipi_id)
{
	MIPI_CMD_STRU mipi_cmd;
	u32 count=0;
	u32 reg_val=0;
	unsigned long flag = 0;
	if((0x0 == reg_addr))
	{
		mipi_print_error("ERROR:para is invalid!\n");
		return MIPI_ERROR;
	}

	/*����֡���ݸ�ʽ*/
	bsp_mipi_config_frame(MIPI_EXTENDED_WRITE,(u64)reg_addr,(u64)data, &mipi_cmd);

	/*���������Ĵ���*/
	local_irq_save(flag);

	/*����DSP_MIPI_EN_IMI,����xbbp�������ź�*/
	set_bbp_mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi(1,mipi_id);


	/*д������֡*/
	set_bbp_mipi_dsp_mipi0_wdata_low_dsp_mipi0_wdata_low(mipi_cmd.mipi_cmd_low,mipi_id);
	set_bbp_mipi_dsp_mipi0_wdata_high_dsp_mipi0_wdata_high(mipi_cmd.mipi_cmd_high,mipi_id);

	/*ѭ���ȴ�MIPI_GRANT_DSPΪ�ߣ���Ϊ0��ʾ����ִ������Ϊ1��ʾ����ִ�����*/
	count=0;
	reg_val= get_bbp_mipi_mipi0_grant_dsp_mipi0_grant_dsp(mipi_id);

	while(MIPI_GRANT_DSP_FLAG_IS_HIGH != reg_val)
	{
        if(++count > MIPI_REG_WAIT_TIMEOUT)
        {
            /*����DSP_MIPI_EN_IMI*/
            set_bbp_mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi(0,mipi_id);
            mipi_print_error("wait for MIPI_GRANT_DSP timeout: %d\n",count);
	    	local_irq_restore(flag);
            return MIPI_ERROR;
        }
    	reg_val= get_bbp_mipi_mipi0_grant_dsp_mipi0_grant_dsp(mipi_id);
	}

	/*��DSP_MIPI_CFG_IND_IMI����1*/
	set_bbp_mipi_dsp_mipi0_cfg_ind_imi_dsp_mipi0_cfg_ind_imi(1,mipi_id);

	/*����оƬҪ����ʱ1us
	whileѭ������4��ָ���㣬 CPUƵ�ʰ�400M����*/
	udelay(1);

	/*����DSP_MIPI_EN_IMI*/
    set_bbp_mipi_dsp_mipi0_en_imi_dsp_mipi0_en_imi(0,mipi_id);

  	/*�ͷŻ�����*/
    local_irq_restore(flag);

	return MIPI_OK;

}



int bsp_mipi_config_frame( u64 trans_type,u64 reg_addr, u64 data,MIPI_CMD_STRU *cmd)
{
	u64 mipi_cmd;
	u64 parity1;
	u64 parity2;
	u64 parity3;
	u8 cmd_type;
	u64 end_flag=0;

	if(MIPI_EXTENDED_READ == trans_type)
	{
		cmd_type = MIPI_CMD_TYPE_READ;
		end_flag = MIPI_READ_END_FLAG;
	}
	else{
		cmd_type = MIPI_CMD_TYPE_WRITE;
		end_flag = MIPI_WRITE_END_FLAG;
	}

	parity1 = bsp_mipi_parity_check(((cmd_type)<<MIPI_CMD_TYPE_PARITY1_OFFSET)|mipi_init.byte_cnt);
	parity2 = bsp_mipi_parity_check(reg_addr);
	parity3 = bsp_mipi_parity_check(data);

	/*MIPI ֡��ʽ:
	(63bit-61bit)3bit,ָ������
	(60bit-57bit)4bit,slave��ַ
	(56bit-53bit)4bit,����
	(52bit-49bit)4bit,�����ֽ���
	(48bit-48bit)1bit,��żУ��
	(47bit-40bit)8bit,slave��ַ
	(39bit-39bit)1bit,��żУ��
	(38bit-03bit)36bit,����
	(34bit-34bit)1bit,end_flag
	(02bit-00bit)3bit,����
	*/
	mipi_cmd = ((trans_type << MIPI_TRANS_TYPE_OFFSET)
				   |((u64)(mipi_init.slave_addr)<<MIPI_SLAVE_ADDR_OFFSET)
				   |((u64)(cmd_type)<<MIPI_CMD_TYPE_OFFSET)
				   |((u64)(mipi_init.byte_cnt)<<MIPI_BYTE_CNT_OFFSET)
				   |(((u64)parity1)<<MIPI_PARITY1_OFFSET)
				   |(reg_addr<<MIPI_REG_ADDR_OFSET)
				   |(((u64)parity2)<<MIPI_PARITY2_OFFSET)
				   |(end_flag<<MIPI_END_FLAG_OFFSET)
				   |(data<<MIPI_DATA_OFFSET)
				   |(((u64)parity3)<<MIPI_PARITY3_OFFSET));
	cmd->mipi_cmd_high= (mipi_cmd>>MIPI_HIGH_OFFSET) & (LOW_32BIT_MASK);
	cmd->mipi_cmd_low= mipi_cmd & (LOW_32BIT_MASK);

	return MIPI_OK;

}



int bsp_mipi_init(void)
{
	if(MIPI_IS_INITIALIZED_FLAG==mipi_init_flag)
	{
		mipi_print_info("bsp mipi init OK!\n");
		return MIPI_OK;
	}

	/*��ʼ��ȫ�ֱ���*/
	mipi_init.byte_cnt=0;	/*ʵ�ʵ��ֽ���Ϊbyte_cnt+1*/
	mipi_init.slave_addr=MIPI_PASTAR_ADDR;

	BBP_MIPI_BASE_ADDR[MIPI_0] = HI_CTU_BASE_ADDR;

	BBP_MIPI_BASE_ADDR[MIPI_1] =BBP_MIPI_BASE_ADDR[MIPI_0]+0x300;

	return MIPI_OK;

}

#ifdef __cplusplus /* __cplusplus */
}
#endif /* __cplusplus */


