
/*lint -save -e537 -e656 -e801*/
#include "hi_base.h"
#include "hi_pwrctrl.h"
#include "hi_pwrctrl_interface.h"

#include "hi_bbp_ctu.h"
#include "hi_bbp_int.h"
#include "hi_bbp_lstu.h"
#include "hi_bbp_tstu.h"
#include "hi_bbp_ltedrx.h"
#include "hi_bbp_tdsdrx.h"
#include "hi_bbp_ul.h"

#include "osl_err.h"
#include "bsp_version.h"
#include "bsp_hardtimer.h"
#include <bsp_sysctrl.h>
#include "bsp_clk.h"

#include "bbp_osl.h"
#include "hi_bbp_reg.h"
#include "bbp_balong.h"
#include "bsp_bbp.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct bbp_info g_bbpinfo;
struct clk          *bbp_tdl_clk;

/*1代表打开中断，0代表屏蔽中断*/
/*LTETF相关中断*/
void hi_bbp_int_ltetf_clear(void)
{
    //set_hi_bbp_int_marm_int_cls_arm_position_int_cls(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_MARM_INT_CLS_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_mask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_INT_MARM_INT_MSK_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_unmask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_MARM_INT_MSK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_int_ltetf_status(void)
{
    //return get_hi_bbp_int_marm_int_msk_arm_position_int_msk();
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_INT_MARM_INT_MSK_OFFSET),(0x1 << 0));
}
/*TDSTF相关中断*/
void hi_bbp_int_tdstf_clear(void)
{
    //set_hi_bbp_tstu_pub_int_clear_arm_sfrm_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TSTU_PUB_INT_CLEAR_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdstf_mask(void)
{
    //set_hi_bbp_tstu_pub_int_msk_arm_sfrm_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_TSTU_PUB_INT_MSK_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdstf_unmask(void)
{
    //set_hi_bbp_tstu_pub_int_msk_arm_sfrm_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TSTU_PUB_INT_MSK_OFFSET),(0x1 << 1));
}
unsigned int hi_bbp_int_tdstf_status(void)
{
    //return get_hi_bbp_tstu_pub_int_msk_arm_sfrm_int_msk();
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_TSTU_PUB_INT_MSK_OFFSET),(0x1 << 1));
}
/*WAKEUP相关中断*/
void hi_bbp_int_ltewp_clear(void)
{
    //set_hi_bbp_ltedrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
}
void hi_bbp_int_ltewp_mask(void)
{
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
void hi_bbp_int_ltewp_unmask(void)
{
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
unsigned int hi_bbp_int_ltewp_status(void)
{
    //return get_hi_bbp_ltedrx_arm_int_state_wakeup_int_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_LTEDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdswp_clear(void)
{
    //set_hi_bbp_tdsdrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdswp_mask(void)
{
    //set_hi_bbp_tdsdrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
void hi_bbp_int_tdswp_unmask(void)
{
    //set_hi_bbp_tdsdrx_arm_sleep_int_msk_wakeup_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
}
unsigned int hi_bbp_int_tdswp_status(void)
{
    //return get_hi_bbp_tdsdrx_arm_int_state_wakeup_int_state();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_TDSDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
}
/* 说明  : 时钟频率不同，必须判断清除完成后才能进行下步操作 */
void hi_bbp_int_wakeup_lte_clear(void)
{
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    hi_bbp_int_ltewp_clear();
    time_stamp = bsp_get_slice_value();
    do{
        int_status = hi_bbp_int_ltewp_status();
        new_slice = bsp_get_slice_value();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));

    if(int_status != 0){
        bbp_print_error("wakeup lte int cannot clear!\n");
    }
    return ;
}
void hi_bbp_int_wakeup_tds_clear(void)
{
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    hi_bbp_int_tdswp_clear();
    time_stamp = bsp_get_slice_value();
    do{
        int_status = hi_bbp_int_tdswp_status();
        new_slice = bsp_get_slice_value();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));

    if(int_status != 0){
        bbp_print_error("wakeup tds int cannot clear!\n");
    }
    return ;
}
/*系统帧相关*/
void hi_bbp_ltestu_tim_lock(void)
{
    //set_hi_bbp_stu_tim_lock_tim_lock(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_LSTU_TIM_LOCK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_lte_fn(void)
{
    //return get_hi_bbp_stu_sfn_rpt_sfn_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_LSTU_SFN_RPT_OFFSET)&0x3ff);
}
unsigned int hi_bbp_get_lte_sfn(void)
{
    //return get_hi_bbp_stu_subfrm_num_rpt_subfrm_num_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_LSTU_SUBFRM_NUM_RPT_OFFSET)&0x3ff);
}
unsigned int hi_bbp_get_tds_sfn(void)
{
    //return get_hi_bbp_tstu_tds_stu_sfn_tds_stu_sfn();
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    /*bit0~15*/
    return readl(reg_base + HI_BBP_TSTU_TDS_STU_SFN_OFFSET);
}
void hi_bbp_set_tds_sfn_oft(unsigned short sf_oft)
{
    //set_hi_bbp_tstu_sfn_oft_sfn_oft(sf_oft);
    //set_hi_bbp_tstu_time_adj_start_time_switch_start(1);
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    /*bit0~15*/
    writel((unsigned int)sf_oft,(reg_base + HI_BBP_TSTU_SFN_OFT_OFFSET));
    /*定时切换使能，TODO:和sunli确认，此处是否需要，脉冲有效*/
    bbp_bit_set((reg_base + HI_BBP_TSTU_TIME_ADJ_START_OFFSET),(0x1 << 1));
}
/*测试需要*/
void hi_bbp_get_tds_sfn_oft(unsigned short* sf_oft)
{
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    /*bit0~15*/
    *sf_oft = (unsigned short)readl(reg_base + HI_BBP_TSTU_SFN_OFT_OFFSET);
}
unsigned int hi_bbp_get_lte_slp_needtime(void)
{
    //return (get_hi_bbp_ltedrx_wakeup_32k_cnt_wakeup_32k_cnt()+get_hi_bbp_ltedrx_switch_32k_cnt_switch_32k_cnt());
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return (readl(reg_base + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET) + \
            readl(reg_base + HI_BBP_LTEDRX_SWITCH_32K_CNT_OFFSET));
}
unsigned int hi_bbp_get_tds_slp_needtime(void)
{
    //return (get_hi_bbp_tdsdrx_wakeup_32k_cnt_wakeup_32k_cnt()+get_hi_bbp_tdsdrx_switch_32k_cnt_switch_32k_cnt());
    /*bit0~26*/
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return (readl(reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET) + \
            readl(reg_base + HI_BBP_TDSDRX_SWITCH_32K_CNT_OFFSET));
}
unsigned int hi_bbp_get_lte_slp_time(void)
{
    //return get_hi_bbp_ltedrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return readl(reg_base + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);
}
unsigned int hi_bbp_get_tds_slp_time(void)
{
    //return get_hi_bbp_tdsdrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return readl(reg_base + HI_BBP_TDSDRX_SLP_TIME_CUR_OFFSET);
}
unsigned int hi_bbp_get_lte_clk_switch_state(void)
{
    //return get_hi_bbp_ltedrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    return bbp_bit_get((reg_base + HI_BBP_LTEDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_tds_clk_switch_state(void)
{
    //return get_hi_bbp_tdsdrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    return bbp_bit_get((reg_base + HI_BBP_TDSDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_lte_wakeup_time(void)
{
    u32 sleep_t = 0;/*一共要睡多长时间*/
    u32 sleeped_t = 0;/*已经睡了多长时间*/
    u32 effect = 0;/*睡眠时长是否生效*/
    u32 ret;

    /*判断睡眠时长是否有效,0xfff12000+0x200*/
    effect = hi_bbp_get_lte_clk_switch_state();

    if(0==effect)
    {   /*若睡眠时长无效，则返回最大值*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_lte_slp_needtime();/* *(0xfff12000+0x1c)+*(0xfff12000+0x20) */
    sleeped_t = hi_bbp_get_lte_slp_time();/*0xfff12000+0x20c*/

    ret = sleep_t-sleeped_t;

out:
    return ret;
}
unsigned int hi_bbp_get_tds_wakeup_time(void)
{
    u32 sleep_t = 0;/*一共要睡多长时间*/
    u32 sleeped_t = 0;/*已经睡了多长时间*/
    u32 effect = 0;/*睡眠时长是否生效*/
    u32 ret;

    /*判断睡眠时长是否有效*/
    effect = hi_bbp_get_tds_clk_switch_state();/*0xfff13400+0x200*/

    if(0==effect){/*若睡眠时长无效，则返回最大值*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_tds_slp_needtime();/* *(0xfff13400+0x1c)+*(0xfff13400+0x20) */
    sleeped_t =hi_bbp_get_tds_slp_time();/*0xfff13400+0x20c*/
    ret = sleep_t-sleeped_t;

out:
    return ret;
}
unsigned int hi_bbp_get_lte_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_L_RD_OFFSET);
}
unsigned int hi_bbp_get_tds_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_T_RD_OFFSET);
}
unsigned int hi_bbp_get_wcdma_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_W_RD_OFFSET);
}
unsigned int hi_bbp_get_gsm_meanflag(void)
{
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    return readl(reg_base + HI_BBP_CTU_MEAS_FLAG_GM_RD_OFFSET);
}
unsigned int hi_bbp_get_ta_value(void)
{
    /*v7r5 change this function,software not support this function ,by yeguohe*/
    return 0;
}


#define BBP_TIMING_LOOP 5
int hi_bbp_get_timing_val(BBP_TIMING_STRU *pstTiming)
{
    int iret = 0;
#ifdef V8R5_BBP
    u32 reg_base = g_bbpinfo.part[BBP_CTU].reg_base;
    u32 reg_value = 0;
    u8 loop,flag = 0;
    unsigned long lock_flags = 0;

    /*check para*/
    if(!pstTiming)
        return -1;

    /*lock*/
    local_irq_save(lock_flags);
    /* 配置C模类型,锁存系统定时(锁存所有模式的系统定时和32 GT定时) */
    bbp_bit_set(reg_base + 0x270,((u32)0x1 << 0));

    /* 等待锁存有效标志，连续读5次，读不到，则返回失败*/
    for ( loop = 0 ; loop < BBP_TIMING_LOOP ; loop++ )
    {
        reg_value = readl(reg_base + 0xca4);
        if(reg_value & 0x1)
        {
            flag = 1;
            break;
        }
    }
    if(!flag)
    {
        g_bbpinfo.dbg.timing_err++;
        iret = -1;
        goto out;
    }
    /*读取lte模定时器寄存器值*/
    pstTiming->uwLTETimeRegVal= readl(reg_base + 0xcdc);
    /*读取32k系统定时器寄存器值*/
    pstTiming->uw32KSysTime = readl(reg_base + 0xcf8);

out:
    local_irq_restore(lock_flags);
#endif
    bbp_print_debug("lte time reg value:0x%x,32k systime reg value:0x%x.\n",pstTiming->uwLTETimeRegVal,pstTiming->uw32KSysTime);

    return iret;
}

int hi_bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    return 0;
}
int hi_bbp_ccpu_reset_and_wait_idle(void)
{
    return 0;
}

/*dma依赖clk*/
void hi_bbpdma_clk_enable(void)
{
    /*clk enable*/
    bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xe0,(u32)0x1 << 5);
    /*rst disable*/
    bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xf4,(u32)0x1 << 5);
}

void hi_bbpdma_clk_disable(void)
{
    /*clk disable*/
    bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xe4,(u32)0x1 << 5);
    /*rst enable*/
    bbp_bit_set(g_bbpinfo.part[BBP_SCTRL].reg_base + 0xf0,(u32)0x1 << 5);
}

void bbp_comm_reset(void)
{
    u32 sysmdm_addr= 0;


    /*close comm mipi*/
    bbp_rstctrl_enable(27);
    bbp_clkctrl_disable(27);

    /*close comm sys*/
    bbp_rstctrl_enable(28);
    bbp_clkctrl_disable(28);

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    /*bbp_off crg/bbc rst ,bit 30-29 should be 0*/
    writel(0x60000000,sysmdm_addr + 0x30);
    /*bbp_off crg/bbc clkdis bit31-30*/
    writel(0xc0000000,sysmdm_addr + 0x14);
}
void bbp_comm_unreset(void)
{
    u32 sysmdm_addr= 0;
    u32 i = 0;

    sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    /*bbp_off crg/bbc clken bit31-30*/
    writel(0xc0000000,sysmdm_addr + 0x10);
    /*bbp_off crg/bbc rst disable,bit 30-29 should be 0*/
    writel(0x60000000,sysmdm_addr + 0x34);

    /*open comm mipi*/
    bbp_clkctrl_enable(27);
    bbp_rstctrl_disable(27);
    /*open comm sys*/
    bbp_clkctrl_enable(28);
    bbp_rstctrl_disable(28);

    /*disable bbpdma*/
    hi_bbpdma_clk_enable();
    for(i = 0;i <= 239;i++)
    {
        writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
    }
    hi_bbpdma_clk_disable();
}
/*寄存器访问掉电保护*/
unsigned int bbp_get_twmtcmos_status(void)
{
    if(CHIP_V750 == bsp_get_version_info()->chip_type)
    {
        return bbp_pwrctrl_is_enabled(1)\
          &bbp_clkctrl_is_enabled(15);/*pwr:wtc;clk:wtc_122m_tw*/
    }
    else
        return 1;
}

/*用作对lte寄存器访问掉电保护*/
unsigned int bbp_get_ltemtcmos_status(void)
{
    if(CHIP_V750 == bsp_get_version_info()->chip_type)
        return bbp_pwrctrl_is_enabled(4);/*pwr lte*/
    else
        return 1;
}
void hi_bbp_sepical_resume(void)
{
    if(CHIP_V750 == bsp_get_version_info()->chip_type)
    {
        /*mask buserr irq*/
        writel(0xfffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x210);
    }
}
void hi_bbp_v7r5_init()
{
    u32 i = 0;
    u32 sysmdm_addr,syson_addr = 0;

    if(g_bbpinfo.dpm.pwc_nv.drx_bbp_init == 0)
    {
        /*open comm mipi*/
        bbp_clkctrl_enable(27);
        bbp_rstctrl_disable(27);
        /*open comm sys*/
        bbp_clkctrl_enable(28);
        bbp_rstctrl_disable(28);
    }
    else
    {
        if(BSP_BOARD_TYPE_BBIT != bsp_get_version_info()->board_type)
        {
            sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);
            syson_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_ao);

            /*******************bbp_on**********************/
            /*rst disable*//*bit31-26*/
            writel(0xfc000000,syson_addr + 0x64);

            /*apb clk*//*bit30*/
            writel(0x40000000,syson_addr);

            /*******************bbp_off*********************/
            /*soc*/
            /*bbp_off crg/bbc clken bit31-30*/
            writel(0xc0000000,sysmdm_addr + 0x10);
            /*bbp_off crg/bbc rst disable,bit 30-29 should be 0*/
            writel(0x60000000,sysmdm_addr + 0x34);
        }

        /*上电*/
        for(i = BBP_PWR_IRM;i <= BBP_PWR_L;i++)
        {
            bbp_pwrctrl_enable(i);
        }

        /*clk and rst*/
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x80);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x94);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xa0);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xb4);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xc0);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xd4);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xe0);
        writel(0xffffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0xf4);

        if(BSP_BOARD_TYPE_BBIT != bsp_get_version_info()->board_type)
        {
            /*turbo*/
            writel(0x10d70,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x100);
        }
    }
    /*mask buserr irq*/
    writel(0xfffffff,g_bbpinfo.part[BBP_SCTRL].reg_base + 0x210);
    /*disable bbpdma*/
    hi_bbpdma_clk_enable();
    for(i = 0;i <= 239;i++)
    {
        writel(0,g_bbpinfo.part[BBP_DMA].reg_base+0x308+0x10*i);
    }
    hi_bbpdma_clk_disable();
}
void hi_bbp_fpga_init(void)
{
    u32 sctrl_addr = g_bbpinfo.part[BBP_SCTRL].reg_base;

    /* dallas fpga bbit */
    writel(0xff,sctrl_addr + 0x0);
    writel(0xff,sctrl_addr + 0x14);
    writel(0xff,sctrl_addr + 0x20);
    writel(0xff,sctrl_addr + 0x34);
    writel(0xffffffff,sctrl_addr + 0x60);
    writel(0xffffffff,sctrl_addr + 0x74);
    writel(0xffffffff,sctrl_addr + 0x80);
    writel(0xffffffff,sctrl_addr + 0x94);
    writel(0xffffffff,sctrl_addr + 0xa0);
    writel(0xffffffff,sctrl_addr + 0xb4);
    writel(0xffffffff,sctrl_addr + 0xc0);
    writel(0xffffffff,sctrl_addr + 0xd4);
    writel(0xffffffff,sctrl_addr + 0xe0);
    writel(0xffffffff,sctrl_addr + 0xf4);
}

void hi_bbp_v8r5_init(void)
{
    u32 bbpon_addr = g_bbpinfo.part[BBP_LDRX].reg_base;
    u32 bbpctu_addr = g_bbpinfo.part[BBP_CTU].reg_base;
    u32 i,value = 0;
    u32 sysmdm_addr = 0;
    u32 sctrl_addr = g_bbpinfo.part[BBP_SCTRL].reg_base;

    if(BSP_BOARD_TYPE_BBIT != bsp_get_version_info()->board_type)
    {
        sysmdm_addr = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);

        /*上电*/
        /*bbp comm*/
        writel((0x1 << 4),sysmdm_addr + 0xc18);
        /*等待上电完成*/
        if(BSP_BOARD_TYPE_ASIC == bsp_get_version_info()->board_type)
        do
        {
            value = readl(sysmdm_addr + 0xe04) & (0x1 << 4);
        }while(value==0);

        udelay(30);
        /*配置解复位*/
        writel((0x1 << 30),sysmdm_addr + 0x34);
        /*配置嵌位不使能*/
        writel((0x1 << 4),sysmdm_addr + 0xc10);
        /*配置时钟使能*/
        writel((0x1 << 30),sysmdm_addr + 0x10);

        /*bbp sctrl*/
        for(i = BBP_PWR_IRM;i <= BBP_PWR_L;i++)
        {
            bbp_pwrctrl_enable(i);
        }
        /*clk and rst*/
        writel(0xffffffff,sctrl_addr + 0x60);
        writel(0xffffffff,sctrl_addr + 0x74);
        writel(0xffffffff,sctrl_addr + 0x80);
        writel(0xffffffff,sctrl_addr + 0x94);
        writel(0xffffffff,sctrl_addr + 0xa0);
        writel(0xffffffff,sctrl_addr + 0xb4);
        writel(0xffffffff,sctrl_addr + 0xc0);
        writel(0xffffffff,sctrl_addr + 0xd4);
        writel(0xffffffff,sctrl_addr + 0xe0);
        writel(0xffffffff,sctrl_addr + 0xf4);
        /*software ctrl tdl clk*/
        writel(0x0008cd78,sctrl_addr + 0x228);
    
        /*open yima clk,form peri_refclk*/
        bbp_tdl_clk = clk_get(NULL,"bbp_tdl_clk");
        if(IS_ERR(bbp_tdl_clk))
        {
            bbp_print_error("bbp_tdl_clk get failed!\n");
            return;
        }
        (void)clk_enable(bbp_tdl_clk);
    }
    else
    {
        hi_bbp_fpga_init();

        writel(0x00,bbpctu_addr+0x10010);/**/
        writel(0x01,bbpon_addr+0x1a20);/*bbp on 0x21fa9a20*/
    }

}

void hi_bbp_v722_init()
{
    /* v722 fpga bbit */
    hi_bbp_fpga_init();

    writel(0x00,0x21f90010);/*chn0 et config*/
    writel(0x00,0x21fa1010);/*chn1 et config*/
    writel(0x01,0x21fa9a20);/*bbp on 0x21fa9a20*/
}

void hi_bbp_init()
{
#ifdef V7R5_BBP
    hi_bbp_v7r5_init();
#endif
#ifdef V8R5_BBP
    hi_bbp_v8r5_init();
#endif
#ifdef V722_BBP
    hi_bbp_v722_init();
#endif

}

#ifdef __cplusplus
}
#endif
/*lint -restore*/
