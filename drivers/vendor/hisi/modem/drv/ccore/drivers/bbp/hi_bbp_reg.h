
#ifndef __HI_BBP_RGE_H__
#define __HI_BBP_RGE_H__

#include "hi_bbp.h"
#include "bbp_balong.h"

#ifdef __cplusplus
extern "C" {
#endif

/*1������жϣ�0���������ж�*/
/*LTETF����ж�*/
void hi_bbp_int_ltetf_clear(void);
void hi_bbp_int_ltetf_mask(void);
void hi_bbp_int_ltetf_unmask(void);
unsigned int hi_bbp_int_ltetf_status(void);
/*TDSTF����ж�*/
void hi_bbp_int_tdstf_clear(void);
void hi_bbp_int_tdstf_mask(void);
void hi_bbp_int_tdstf_unmask(void);
unsigned int hi_bbp_int_tdstf_status(void);
/*WAKEUP����ж�*/
void hi_bbp_int_ltewp_clear(void);
void hi_bbp_int_ltewp_mask(void);
void hi_bbp_int_ltewp_unmask(void);
unsigned int  hi_bbp_int_ltewp_status(void);
void hi_bbp_int_tdswp_clear(void);
void hi_bbp_int_tdswp_mask(void);
void hi_bbp_int_tdswp_unmask(void);
unsigned int  hi_bbp_int_tdswp_status(void);
void hi_bbp_int_wakeup_lte_clear(void);
void hi_bbp_int_wakeup_tds_clear(void);
/*ϵͳʱ�����*/
unsigned int hi_bbp_systime_low(void);
unsigned int hi_bbp_systime_high(void);
/*ϵͳ֡���*/
void hi_bbp_ltestu_tim_lock(void);
unsigned int  hi_bbp_get_lte_fn(void);
unsigned int hi_bbp_get_lte_sfn(void);
unsigned int hi_bbp_get_tds_sfn(void);
void hi_bbp_set_tds_sfn_oft(unsigned short sf_oft);
void hi_bbp_get_tds_sfn_oft(unsigned short* sf_oft);
unsigned int hi_bbp_get_lte_slp_needtime(void);
unsigned int hi_bbp_get_tds_slp_needtime(void);
unsigned int hi_bbp_get_lte_slp_time(void);
unsigned int hi_bbp_get_tds_slp_time(void);
unsigned int hi_bbp_get_lte_clk_switch_state(void);
unsigned int hi_bbp_get_tds_clk_switch_state(void);
unsigned int hi_bbp_get_lte_wakeup_time(void);
unsigned int hi_bbp_get_tds_wakeup_time(void);
unsigned int hi_bbp_get_lte_meanflag(void);
unsigned int hi_bbp_get_tds_meanflag(void);
unsigned int hi_bbp_get_wcdma_meanflag(void);
unsigned int hi_bbp_get_gsm_meanflag(void);
unsigned int hi_bbp_get_ta_value(void);
int hi_bbp_get_timing_val(BBP_TIMING_STRU *pstTiming);
int hi_bbp_gbbp_select_clksrc (PWC_COMM_MODEM_E enModemId,PWC_COMM_CHANNEL_E enChannel);
int hi_bbp_ccpu_reset_and_wait_idle(void);
void hi_bbp_sepical_resume(void);

/*�Ĵ������ʵ��籣��*/
unsigned int bbp_get_twmtcmos_status(void);
/*������lte�Ĵ������ʵ��籣��*/
unsigned int bbp_get_ltemtcmos_status(void);

void bbp_comm_reset(void);
void bbp_comm_unreset(void);
unsigned int hi_lbbp_clk_status(void);
void hi_lbbp_clk_enable(void);
void hi_lbbp_clk_disable(void);
void hi_bbpdma_clk_enable(void);
void hi_bbpdma_clk_disable(void);
unsigned int hi_bbp_pll_status(void);
void hi_bbp_pll_enable(void);
void hi_bbp_pll_disable(void);
void hi_bbp_init(void);


#ifdef __cplusplus
}
#endif

#endif
