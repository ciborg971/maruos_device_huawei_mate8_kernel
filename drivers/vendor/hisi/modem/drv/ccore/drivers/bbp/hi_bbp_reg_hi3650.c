
/*lint -save -e537 -e656 -e801*/
#include "product_config.h"
#include "osl_bio.h"
#include "osl_err.h"
#include "hi_base.h"
#include "hi_version.h"
#include "hi_bbp_ctu.h"
#include "hi_bbp_int.h"
#include "hi_bbp_lstu.h"
#include "hi_bbp_tstu.h"
#include "hi_bbp_ltedrx.h"
#include "hi_bbp_tdsdrx.h"
#include "hi_bbp_ul.h"

#include <bsp_sysctrl.h>
#include "bsp_hardtimer.h"
#include "bsp_clk.h"
#include "bsp_ipc.h"
#include "bsp_reset.h"
#include <bsp_version.h>

#include "bbp_osl.h"
#include "hi_bbp_reg.h"
#include "bbp_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

extern struct bbp_info g_bbpinfo;
u32 sysreg_base = 0;
struct clk          *bbp_entry_clk;
/*���bbp drx��������bug*/
static void hi_bbp_drxbug_evade(void)
{
    if(sysreg_base)
        (void)readl((u32)sysreg_base + HI_VERSION_ID_OFFSET);
}

/*1������жϣ�0���������ж�*/
/*LTETF����ж�*/
void hi_bbp_int_ltetf_clear(void)
{
    //set_hi_bbp_int_marm_int_cls_arm_position_int_cls(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_ARM_INT_CLS_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_mask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_clr((reg_base + HI_BBP_INT_ARM_INT_MSK_OFFSET),(0x1 << 0));
}
void hi_bbp_int_ltetf_unmask(void)
{
    //set_hi_bbp_int_marm_int_msk_arm_position_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    bbp_bit_set((reg_base + HI_BBP_INT_ARM_INT_MSK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_int_ltetf_status(void)
{
    //return get_hi_bbp_int_marm_int_msk_arm_position_int_msk();
    u32 reg_base = g_bbpinfo.part[BBP_INT].reg_base;
    return bbp_bit_chk((reg_base + HI_BBP_INT_ARM_INT_MSK_OFFSET),(0x1 << 0));
}
/*TDSTF����ж�*/
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
/*WAKEUP����ж�*/
void hi_bbp_int_ltewp_clear(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_ltedrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_ltewp_mask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_clr((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_ltewp_unmask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_ltedrx_arm_sleep_int_msk_wakeup_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
unsigned int hi_bbp_int_ltewp_status(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_value = 0;
    //return get_hi_bbp_ltedrx_arm_int_state_wakeup_int_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    hi_bbp_drxbug_evade();
    reg_value = bbp_bit_chk((reg_base + HI_BBP_LTEDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
void hi_bbp_int_tdswp_clear(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_tdsdrx_arm_sleep_int_clear_wakeup_int_clear(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_tdswp_mask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_tdsdrx_arm_sleep_int_msk_wakeup_int_msk(0x0);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_clr((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}
void hi_bbp_int_tdswp_unmask(void)
{
    unsigned long bbp_flag = 0;
    //set_hi_bbp_tdsdrx_arm_sleep_int_msk_wakeup_int_msk(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_MSK_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
}

unsigned int hi_bbp_int_tdswp_status(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_value = 0;
    //return get_hi_bbp_tdsdrx_arm_int_state_wakeup_int_state();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    hi_bbp_drxbug_evade();
    reg_value =  bbp_bit_chk((reg_base + HI_BBP_TDSDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
void hi_bbp_int_wakeup_lte_clear(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    /*���wake up �ж�*/
    /*Ϊ�˲��ظ�����������ʹ��hi_bbp_int_ltewp_clear()�ӿڣ�ֱ�Ӳ����Ĵ���;*/
    bbp_bit_set((reg_base + HI_BBP_LTEDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    time_stamp = bsp_get_slice_value();
    do{
        /*int_status = hi_bbp_int_ltewp_status();*/
        int_status = bbp_bit_chk((reg_base + HI_BBP_LTEDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
        new_slice = bsp_get_slice_value();
        /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
        hi_bbp_drxbug_evade();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));
    if(int_status != 0){
        bbp_print_error("wakeup lte int cannot clear!\n");
    }
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return;
}
void hi_bbp_int_wakeup_tds_clear(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    u32 int_status;
    unsigned int    time_stamp;
    unsigned int    new_slice;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    /*���wake up �ж�*/
    /*hi_bbp_int_tdswp_clear();*/
    bbp_bit_set((reg_base + HI_BBP_TDSDRX_ARM_SLEEP_INT_CLEAR_OFFSET),(0x1 << 1));
    time_stamp = bsp_get_slice_value();
    do{
        /*int_status = hi_bbp_int_tdswp_status();*/
        int_status = bbp_bit_chk((reg_base + HI_BBP_TDSDRX_ARM_INT_STATE_OFFSET),(0x1 << 1));
        new_slice = bsp_get_slice_value();
        /*���bbp_on ��������,����2013121200228*/
        hi_bbp_drxbug_evade();
    }while((int_status != 0)&&(get_timer_slice_delta(time_stamp, new_slice) < WAKEUP_INT_CLEAR_TIMEOUT));
    if(int_status != 0){
        bbp_print_error("wakeup tds int cannot clear!\n");
    }
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return;
}
/*ϵͳ֡���*/
void hi_bbp_ltestu_tim_lock(void)
{
    //set_hi_bbp_stu_tim_lock_tim_lock(0x1);
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    bbp_bit_set((reg_base + HI_BBP_STU_TIM_LOCK_OFFSET),(0x1 << 0));
}
unsigned int hi_bbp_get_lte_fn(void)
{
    //return get_hi_bbp_stu_sfn_rpt_sfn_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_STU_SFN_RPT_OFFSET)&0x3ff);
}
unsigned int hi_bbp_get_lte_sfn(void)
{
    //return get_hi_bbp_stu_subfrm_num_rpt_subfrm_num_rpt();
    u32 reg_base = g_bbpinfo.part[BBP_LSTU].reg_base;
    /*bit0~9*/
    return (readl((u32)reg_base + HI_BBP_STU_SUBFRM_NUM_RPT_OFFSET)&0x3ff);
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
    /*��ʱ�л�ʹ�ܣ�TODO:��sunliȷ�ϣ��˴��Ƿ���Ҫ��������Ч*/
    bbp_bit_set((reg_base + HI_BBP_TSTU_TIME_ADJ_START_OFFSET),(0x1 << 1));
}
/*������Ҫ*/
void hi_bbp_get_tds_sfn_oft(unsigned short* sf_oft)
{
    u32 reg_base = g_bbpinfo.part[BBP_TSTU].reg_base;
    /*bit0~15*/
    *sf_oft = (unsigned short)readl(reg_base + HI_BBP_TSTU_SFN_OFT_OFFSET);
}
unsigned int hi_bbp_get_lte_slp_needtime(void)
{
    u32 reg_value = 0;
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    reg_value =  readl(reg_base + HI_BBP_LTEDRX_WAKEUP_32K_CNT_OFFSET);
    /* get_chip��Ϊ���bbp_on �������⣬��ʵ������,����2013121200228*/
    hi_bbp_drxbug_evade();
    reg_value +=  readl(reg_base + HI_BBP_LTEDRX_SWITCH_32K_CNT_OFFSET);

    return reg_value;
}
unsigned int hi_bbp_get_tds_slp_needtime(void)
{
    u32 reg_value = 0;
    /*bit0~26*/
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    reg_value = readl(reg_base + HI_BBP_TDSDRX_WAKEUP_32K_CNT_OFFSET);
    /* get_chip��Ϊ���bbp_on �������⣬��ʵ������,����2013121200228*/
    hi_bbp_drxbug_evade();
    reg_value += readl(reg_base + HI_BBP_TDSDRX_SWITCH_32K_CNT_OFFSET);

    return reg_value;
}
unsigned int hi_bbp_get_lte_slp_time(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_ltedrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = readl(reg_base + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
unsigned int hi_bbp_get_tds_slp_time(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_tdsdrx_slp_time_cur_slp_time_cur();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = readl(reg_base + HI_BBP_TDSDRX_SLP_TIME_CUR_OFFSET);
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
unsigned int hi_bbp_get_lte_clk_switch_state(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_ltedrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = bbp_bit_get((reg_base + HI_BBP_LTEDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);

    return reg_value;
}
unsigned int hi_bbp_get_tds_clk_switch_state(void)
{
    unsigned long bbp_flag;
    u32 reg_value = 0;
    //return get_hi_bbp_tdsdrx_clk_switch_state_clk_switch_state();
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    reg_value = bbp_bit_get((reg_base + HI_BBP_TDSDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
    return reg_value;
}
unsigned int hi_bbp_get_lte_wakeup_time(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_LDRX].reg_base;
    u32 sleep_t = 0;/*һ��Ҫ˯�೤ʱ��*/
    u32 sleeped_t = 0;/*�Ѿ�˯�˶೤ʱ��*/
    u32 effect = 0;/*˯��ʱ���Ƿ���Ч*/
    u32 ret;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);

    /*�ж�˯��ʱ���Ƿ���Ч,0xfff12000+0x200*/
    //effect = hi_bbp_get_lte_clk_switch_state();
    effect = bbp_bit_get((reg_base + HI_BBP_LTEDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));

    if(0==effect)
    {   /*��˯��ʱ����Ч���򷵻����ֵ*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_lte_slp_needtime();/* *(0xfff12000+0x1c)+*(0xfff12000+0x20) */
    //sleeped_t = hi_bbp_get_lte_slp_time();/*0xfff12000+0x20c*/
    sleeped_t = readl(reg_base + HI_BBP_LTEDRX_SLP_TIME_CUR_OFFSET);

    ret = sleep_t-sleeped_t;

out:
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
    return ret;
}
unsigned int hi_bbp_get_tds_wakeup_time(void)
{
    unsigned long bbp_flag = 0;
    u32 reg_base = g_bbpinfo.part[BBP_TDRX].reg_base;
    u32 sleep_t = 0;/*һ��Ҫ˯�೤ʱ��*/
    u32 sleeped_t = 0;/*�Ѿ�˯�˶೤ʱ��*/
    u32 effect = 0;/*˯��ʱ���Ƿ���Ч*/
    u32 ret;

    /* IPC��Ϊ���bbp_on ��������,����2013121200228*/
    bsp_ipc_spin_lock_irqsave(IPC_SEM_BBP,bbp_flag);
    /*�ж�˯��ʱ���Ƿ���Ч*/
    //effect = hi_bbp_get_tds_clk_switch_state();/*0xfff13400+0x200*/
    effect = bbp_bit_get((reg_base + HI_BBP_TDSDRX_CLK_SWITCH_STATE_OFFSET),(0x1 << 0));

    if(0==effect){/*��˯��ʱ����Ч���򷵻����ֵ*/
        ret = 0xffffffff;
        goto out;
    }

    sleep_t += hi_bbp_get_tds_slp_needtime();/* *(0xfff13400+0x1c)+*(0xfff13400+0x20) */
    //sleeped_t =hi_bbp_get_tds_slp_time();/*0xfff13400+0x20c*/
    sleeped_t = readl(reg_base + HI_BBP_TDSDRX_SLP_TIME_CUR_OFFSET);
    ret = sleep_t-sleeped_t;

out:
    bsp_ipc_spin_unlock_irqrestore(IPC_SEM_BBP,bbp_flag);
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
    u32 reg_base = g_bbpinfo.part[BBP_UL].reg_base;
    return readl(reg_base + HI_BBP_UL_UL_TA_REG_OFFSET);
}

int hi_bbp_get_timing_val(BBP_TIMING_STRU *pstTiming)
{
    return 0;
}

int hi_bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel)
{
    int ret = BBP_OK;
    unsigned int reg_addr,reg_bit,reg_value = 0;
    u32 chan = 0;

    switch(enModemId)
    {
        case PWC_COMM_MODEM_0:
        case PWC_COMM_MODEM_2:
            /*set g0bbp*/
            reg_bit = 5;
            break;
        case PWC_COMM_MODEM_1:
            /*set g1bbp*/
            reg_bit = 6;
            break;
        default:
            bbp_print_error("can not support modem%d!\n",enModemId);
            return BBP_ERR;
    }
    switch(enChannel)
    {
        case PWC_COMM_CHANNEL_0:
            /*set g0bbp*/
            chan = 0;
            break;
        case PWC_COMM_CHANNEL_1:
            /*set g1bbp*/
            chan = 1;
            break;
        default:
            bbp_print_error("can not support channel%d!\n",enModemId);
            return BBP_ERR;
    }
    reg_addr = ((unsigned int)sysreg_base + 0x148);
    reg_value = readl(reg_addr);
    /*bit clear*/
    reg_value &= ~((u32)0x1 << reg_bit);
    /*bit set*/
    reg_value |= (chan << reg_bit);
    /*set reg*/
    writel(reg_value,reg_addr);

    /*om*/
    g_bbpinfo.clksrc[enModemId].dbg_ctrl.channel_id = enChannel;
    g_bbpinfo.clksrc[enModemId].dbg_ctrl.timestamp = bsp_get_slice_value_hrt();
    g_bbpinfo.clksrc[enModemId].dbg_ctrl.reg_act = readl(reg_addr);

    return ret;
}

/*****************************************************************************
 �� �� ��  : hi_bbp_ccpu_reset_and_wait_idle
 ��������  : c�˸�λ��رղ���bbp�������̬
 �������  : ��
 �������  : ��
 �� �� ֵ  : int
 ���ú���  : ccpu_reset_bbp_and_wait_idle
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2014��3��12��
    �޸�����   : �����ɺ���

*****************************************************************************/
int hi_bbp_ccpu_reset_and_wait_idle(void)
{
    unsigned int regvalue = 0;
    unsigned int u32slicebegin = 0;
    u32 bbp_dma_base = g_bbpinfo.part[BBP_DMA].reg_base;
    u32 wbbp_base = g_bbpinfo.part[BBP_WBBP].reg_base;
    u32 abb_base = g_bbpinfo.part[BBP_ABB].reg_base;
    u32 sysapcrg_base = 0;
    u32 i = 0;

    bsp_reset_timestamp(0xaa, STAMP_RESET_BBP_DEBUG);

    /*��ѯBBPHY��PLLʱ�ӵ�״̬*/
    sysapcrg_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_ap_pericrg);
    /*��ѯ�Ƿ���Դ��DSPPLL 0xfff350dc[bit 4\5] == 2*/
    regvalue = readl(sysapcrg_base + 0xdc);
    regvalue &= (unsigned int)(0x3 << 4);
    if(regvalue == 0x20){
        bsp_reset_timestamp(0xbb, STAMP_RESET_BBP_DEBUG);
        /*dsp pll�Ƿ�ر� 0xe020020c bit26*/
        regvalue = readl(sysreg_base + 0x20c);
        regvalue &= (unsigned int)(0x1 << 26);
        if(regvalue != (unsigned int)(0x1 << 26)){
            bsp_reset_timestamp(0x1, STAMP_RESET_WBBP_MSTER_STOP);
            return BBP_OK;
        }
    }

    /*��ѯBBPHY���ſزο�ʱ�ӵ�״̬*/
    regvalue = readl(sysreg_base + 0x20);
    regvalue &= (unsigned int)(0x1 << 24);
    if(regvalue != (unsigned int)(0x1 << 24)){
        bsp_reset_timestamp(0x2, STAMP_RESET_WBBP_MSTER_STOP);
        return BBP_OK;
    }

    /*��ѯBBP crg�⸴λ��״̬*/
    regvalue = readl(sysreg_base + 0x80);
    regvalue &= (unsigned int)0x1;
    if(regvalue != 0x0){
        bsp_reset_timestamp(0x3, STAMP_RESET_WBBP_MSTER_STOP);
        return BBP_OK;
    }
    /*��ѯCOMM��cmos״̬*/
    regvalue = readl(sysreg_base + 0xe04);
    regvalue &= (unsigned int)0x200;
    if(regvalue != 0x200){
        bsp_reset_timestamp(0x4, STAMP_RESET_WBBP_MSTER_STOP);
        return BBP_OK;
    }
    /*��ѯCOMM��iso״̬*/
    regvalue = readl(sysreg_base + 0xe0c);
    regvalue &= (unsigned int)0x200;
    if(regvalue != 0x0){
        bsp_reset_timestamp(0x5, STAMP_RESET_WBBP_MSTER_STOP);
        return BBP_OK;
    }
    /*��ѯCOMM��clk״̬*/
    regvalue = readl(sysreg_base + 0x38);
    regvalue &= (unsigned int)0x2;
    if(regvalue != 0x2){
        bsp_reset_timestamp(0x6, STAMP_RESET_WBBP_MSTER_STOP);
        return BBP_OK;
    }
    /*��ѯCOMM��reset״̬*/
    regvalue = readl(sysreg_base + 0x80);
    regvalue &= (unsigned int)0x2;
    if(regvalue != 0x0){
        bsp_reset_timestamp(0x7, STAMP_RESET_WBBP_MSTER_STOP);
        return BBP_OK;
    }

    bsp_reset_timestamp(0x1, STAMP_RESET_BBP_DEBUG);

    /*disable dma*/
    writel(0x0, bbp_dma_base + 0x0294);/*data*/
    writel(0x0, bbp_dma_base + 0x02A8);/*channel_0*/
    writel(0x0, bbp_dma_base + 0x02B4);/*channel_1*/
    writel(0x0, bbp_dma_base + 0x02B8);/*log*/
    bsp_reset_timestamp(0x2, STAMP_RESET_BBP_DEBUG);
    /*comm*/
    for (i = 0; i < 96; i++)
    {
        writel(0x0, bbp_dma_base + 0x0308 + 0x10 *i);
    }
    bsp_reset_timestamp(0x3, STAMP_RESET_BBP_DEBUG);
    /*fast*/
    for (i = 0; i < 32; i++)
    {
        regvalue = readl(bbp_dma_base + 0x0A0C + 0x10 *i);
        regvalue &= ~(1 << 28);
        writel(regvalue, bbp_dma_base + 0x0A0C + 0x10 *i);
    }
    bsp_reset_timestamp(0x4, STAMP_RESET_BBP_DEBUG);

    /*delay 50ms*/
    u32slicebegin = bsp_get_slice_value();
    do{
    }while(CHECK_TIMEOUT_50MS(u32slicebegin));
    bsp_reset_timestamp(0x5, STAMP_RESET_BBP_DEBUG);
    /*reset bbpdma*/
    writel(0x7, bbp_dma_base);
    bsp_reset_timestamp(0x6, STAMP_RESET_BBP_DEBUG);
    /*delay 50ms*/
    u32slicebegin = bsp_get_slice_value();
    do{
    }while(CHECK_TIMEOUT_50MS(u32slicebegin));
    bsp_reset_timestamp(0x7, STAMP_RESET_BBP_DEBUG);

    /*��ѯBBP DMA 8/9/10bit 3��ͨ��(��������)�Ƿ����*/
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = readl(sysreg_base+ 0x10);
        regvalue &= (unsigned int)0x700;
    }while((0x0 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x0 != regvalue){
        *(u32 *)STAMP_RESET_IDLE_FAIL_COUNT |= (u32)0x1 << ENUM_RESET_BBP_DMA;
        goto wbbp_idle;
    }

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_BBP_DMA_ENTER_IDLE);

wbbp_idle:
    /*��ѯABB�Ľ⸴λ״̬*/
    regvalue = readl(sysreg_base + 0x80);
    regvalue &= (unsigned int)0x80000000;
    if(regvalue != 0x0){
        bsp_reset_timestamp(0x1, STAMP_RESET_WBBP_ENTER_IDLE);
        goto comm_rst;
    }

    /*��ѯABB PLL��״̬*/
    regvalue = readl(abb_base + (0xa5 << 2));
    regvalue &= (unsigned int)0x22;
    if(regvalue != 0x22){
        bsp_reset_timestamp(0x2, STAMP_RESET_WBBP_ENTER_IDLE);
        goto comm_rst;
    }

    /*��ѯWBBP(wps)��clk״̬*/
    regvalue = readl(sysreg_base + 0x38);
    regvalue &= (unsigned int)0x40;
    if(regvalue != 0x40){
        bsp_reset_timestamp(0x3, STAMP_RESET_WBBP_ENTER_IDLE);
        goto comm_rst;
    }

    /*��ѯWBBP��reset״̬*/
    regvalue = readl(sysreg_base + 0x80);
    regvalue &= (unsigned int)0x40;
    if(regvalue != 0x0){
        bsp_reset_timestamp(0x4, STAMP_RESET_WBBP_ENTER_IDLE);
        goto comm_rst;
    }

    /*��ѯWBBP��ISO״̬*/
    regvalue = readl(sysreg_base + 0xe0c);
    regvalue &= (unsigned int)0x100;
    if(regvalue != 0x0){
        bsp_reset_timestamp(0x5, STAMP_RESET_WBBP_ENTER_IDLE);
        goto comm_rst;
    }

    /*��ѯWBBP��MTCOMS״̬*/
    regvalue = readl(sysreg_base + 0xe04);
    regvalue &= (unsigned int)0x100;
    if(regvalue != 0x100){
        bsp_reset_timestamp(0x6, STAMP_RESET_WBBP_ENTER_IDLE);
        goto comm_rst;
    }

    /*����WBBP*/
    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_WBBP_MSTER_STOP);
    writel(0x0, wbbp_base + 0x9070);

    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_WBBP_SLAVE_STOP);
    writel(0x0, wbbp_base + 0x29070);

    bsp_reset_timestamp(0x8, STAMP_RESET_BBP_DEBUG);

    /*��ѯWBBP 0/16/17/18/19�Ƿ����*/
    u32slicebegin = bsp_get_slice_value();
    do{
        regvalue = readl(wbbp_base + 0x949c);
        regvalue &= (unsigned int)0xF0001;
    }while((0x0 != regvalue) && CHECK_TIMEOUT(u32slicebegin));
    if(0x0 != regvalue){
        bsp_reset_timestamp((0x1U << ENUM_RESET_WBBP)|*(u32 *)STAMP_RESET_IDLE_FAIL_COUNT, STAMP_RESET_IDLE_FAIL_COUNT);
        goto comm_rst;
    }
    bsp_reset_timestamp(bsp_get_slice_value(), STAMP_RESET_WBBP_ENTER_IDLE);

comm_rst:
    bsp_reset_timestamp(0x9, STAMP_RESET_BBP_DEBUG);
    /*reset bbpcomm*/
    writel(0x2, sysreg_base + 0x78);
    bsp_reset_timestamp(0xa, STAMP_RESET_BBP_DEBUG);

    return BBP_OK;
}

/*���dma����lbbp clk��bug*/

void hi_bbpdma_clk_enable(void)
{
    return ;
}
void hi_bbpdma_clk_disable(void)
{
    return;
}

void bbp_comm_reset(void)
{
    (void)bbp_pwrctrl_disable(BBP_PWR_COMM);
}

void bbp_comm_unreset(void)
{
    (void)bbp_pwrctrl_enable(BBP_PWR_COMM);
}

void hi_bbp_sepical_resume(void)
{
}

/*�Ĵ������ʵ��籣��*/
unsigned int bbp_get_twmtcmos_status(void)
{
    return bbp_pwrctrl_is_enabled(BBP_PWR_UTX)\
          &bbp_clkctrl_is_enabled(BBP_CLK_TW_T122M);
}

/*������lte�Ĵ������ʵ��籣��*/
unsigned int bbp_get_ltemtcmos_status(void)
{
    return bbp_pwrctrl_is_enabled(BBP_PWR_LTE);
}

void bbp_ltepwrctrl_enable()
{
    u32 value1 = 0;
    u32 value2 = 0;

    /*���ø�λ*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].rst_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].rst_ctrl.en_bit));

    /*�����ϵ�*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].mos_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].mos_ctrl.en_bit));

    /*�ȴ��ϵ����*/
    do
    {
        value1 = bbp_bit_get(g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].mos_ctrl.rdy_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].mos_ctrl.rdy_bit));
        /*ltebbp0 rdy*/
        value2 = bbp_bit_get(g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].mos_ctrl.rdy_reg,((u32)0x1 << 14));
    }while((value1==0) || (value2==0));
    udelay(30);

    /*���ý⸴λ*/;
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].rst_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].rst_ctrl.dis_bit));

    /*����Ƕλ��ʹ��*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].iso_ctrl.dis_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].iso_ctrl.dis_bit));

    /*����ʱ��ʹ��*/
    bbp_bit_set(g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].clk_ctrl.en_reg,((u32)0x1 << g_bbpinfo.pwr.pwr_act[BBP_PWR_LTE].clk_ctrl.en_bit));
}
void hi_bbp_init()
{

    /*��ȡϵͳ����������ַ*/
    sysreg_base = (u32)bsp_sysctrl_addr_byindex(sysctrl_mdm);

#if (FEATURE_UE_MODE_CDMA == FEATURE_ON)
    /*cmos enable*/
    writel(0xffffffff,(u32)sysreg_base + 0xc18);
    /*clk enable*/
    writel(0xffffffff,(u32)sysreg_base + 0x30);
    /*ios clear*/
    writel(0xffffffff,(u32)sysreg_base + 0xc14);
    /*rst clear*/
    writel(0xffffffff,(u32)sysreg_base + 0x7c);
#else
    /*close all clk and cmos*/
    writel(0xffffffff,(u32)sysreg_base + 0x34);

    /*open comm pd and ao clk*/
    (void)bbp_pwrctrl_enable(BBP_PWR_COMM);
    bbp_clkctrl_enable(BBP_CLK_AO);
#endif
    /*open yima clk*/
    bbp_entry_clk = clk_get(NULL,"bbp_entry_clk");
    if(IS_ERR(bbp_entry_clk))
    {
        bbp_print_error("bbp_entry_clk get failed!\n");
        return;
    }
    (void)clk_enable(bbp_entry_clk);
}
#ifdef __cplusplus
}
#endif
/*lint -restore*/
