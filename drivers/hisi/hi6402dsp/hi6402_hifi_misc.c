/* Copyright (c) 2013-2014, Hisilicon Tech. Co., Ltd. All rights reserved.
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License version 2 and
* only version 2 as published by the Free Software Foundation.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.	See the
* GNU General Public License for more details.
*
*/

#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/device.h>
#include <linux/miscdevice.h>
#include <linux/platform_device.h>
#include <linux/dma-mapping.h>
#include <linux/unistd.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <linux/reboot.h>

#include <linux/firmware.h>
#include <linux/errno.h>
#include <linux/proc_fs.h>
#include <asm/uaccess.h>

#include <hi6402_algo_interface.h>
#include <hi6402_hifi_interface.h>
#include "hi6402_hifi_regs.h"
#include "hi6402_hifi_debug.h"

#include <linux/hisi/hi6402_hifi_misc.h>
#include <dsm/dsm_pub.h>
#include "slimbus.h"

#include <linux/hisi/rdr_pub.h>

extern int slimbus_bus_configure(slimbus_bus_config_type_t type);

extern void rdr_codec_hifi_watchdog_process(void);

#define MAX_MSG_SIZE 128
#define MAX_PARA_SIZE 4096
#define RESULT_SIZE 4
#define MAX_OUT_PARA_SIZE ((RESULT_SIZE) + (MAX_PARA_SIZE))
#define MAX_USR_INPUT_SIZE (MAX_MSG_SIZE + MAX_PARA_SIZE)

#define HI6402_EXCEPTION_RETRY 3
#define HI6402_VERSION_CS      0x11
#define MAX_STR_LEN 64
#define HI6402_IFOPEN_WAIT4DPCLK       1000    //wait 100ms.(1000 cycles * 100us every cycle)
#define HI6402DSP_CHECK_DP_CLK_REG     0x200073d8

#define SOC_GPIO_ADDR				   0xfff0e3fc
#define SOC_GPIO_DIR_ADDR			   0xfff0e400
#define HI6402_HIFI_FPGA_OM_TEST_ADDR  0xE86120D4

#define HI6402DEBUG_LEVEL_PROC_FILE   "hi6402debuglevel"
#define HI6402DEBUG_PROC_FILE		  "hi6402debug"
#define HI6402DEBUG_PATH			  "hi6402dbg"

/*XXX: change to 4 to enbale debug print*/
unsigned long hi6402_dsp_debug_level = 3;

static const unsigned int DSP_MSG_START_ADDR =
				HI6402_OCRAM1_BASE + HI6402_MSG_START_ADDR_OFFSET;
static const unsigned int DSP_MLIB_PARA_ADDR = HI6402_OCRAM1_BASE;

#ifdef ENABLE_HI6402_HIFI_DEBUG
static struct proc_dir_entry *hi6402_debug_dir = NULL;
#endif

struct reg_rw_struct {
	unsigned int	reg;
	unsigned int	val;
};

struct hi6402_dsp_priv {
	struct hi6402_irq *p_irq;
	struct device *dev;

	unsigned int irq_cmd_valid;
	unsigned int irq_wtd;
	struct mutex msg_mutex;

	unsigned int sync_msg_ret;
	wait_queue_head_t sync_msg_wq;

	unsigned int dsp_pllswitch_done;
	wait_queue_head_t dsp_pllswitch_wq;

	unsigned int dsp_pwron_done;
	wait_queue_head_t dsp_pwron_wq;

	/* we lock the two below to avoid a change after config */
	enum hi6402_pll_status pll_state;
	bool dsp_is_running;
	struct mutex state_mutex;

	unsigned int low_freq_scene_status;
	unsigned int high_freq_scene_status;
	unsigned int uart_mode;

	bool is_watchdog_coming;
	bool is_sync_write_timeout;
	uint32_t	*src_addr_v;
	dma_addr_t	 src_dma_addr;
};

static struct hi6402_dsp_priv priv;

static struct notifier_block hi6402_sr_nb;
static struct notifier_block hi6402_reboot_nb;
atomic_t volatile hi6402_in_suspend = ATOMIC_INIT(0);
atomic_t volatile hi6402_in_saving = ATOMIC_INIT(0);

extern struct dsm_client *dsm_audio_client;

/* ************************************************************************************
 * use reg access supplied in hi6402_irq
 * */
static void hi6402_hifi_set_pll(bool enable)
{
	/* set pll */
	BUG_ON(priv.p_irq == NULL);
	hi6402_irq_high_freq_pll_enable(priv.p_irq, enable);
}

static void hi6402_hifi_set_low_pll(bool enable)
{
	/* set mad_pll */
	BUG_ON(priv.p_irq == NULL);
	hi6402_irq_low_freq_pll_enable(priv.p_irq, enable);
}

static inline void hi6402_hifi_write_reg(unsigned int reg, unsigned int val)
{
	BUG_ON(priv.p_irq == NULL);
	hi6402_irq_write(priv.p_irq, reg, val);
}

static inline unsigned int hi6402_hifi_read_reg(unsigned int reg)
{
	BUG_ON(priv.p_irq == NULL);
	return hi6402_irq_read(priv.p_irq, reg);
}

static inline void hi6402_hifi_reg_set_bit(unsigned int reg,
					   unsigned int offset)
{
	BUG_ON(priv.p_irq == NULL);
	hi6402_reg_set_bit(priv.p_irq, reg, offset);
}

static inline void hi6402_hifi_reg_clr_bit(unsigned int reg,
					   unsigned int offset)
{
	BUG_ON(priv.p_irq == NULL);
	hi6402_reg_clr_bit(priv.p_irq, reg, offset);
}

static inline void hi6402_hifi_reg_write_bits(unsigned int reg,
						  unsigned int value,
						  unsigned int mask)
{
	BUG_ON(priv.p_irq == NULL);
	hi6402_reg_write_bits(priv.p_irq, reg, value, mask);
}

/* power management */
static void hi6402_hifi_runstall_cfg(bool pull_down)
{
	IN_FUNCTION;
	if (pull_down) {
		/* Pull down runstall of HIFI*/
		hi6402_hifi_reg_clr_bit(HI6402_DSP_SC_DSP_CTRL0, 2);
	} else {
		/* Pull up runstall of HIFI*/
		hi6402_hifi_reg_set_bit(HI6402_DSP_SC_DSP_CTRL0, 2);
	}
	OUT_FUNCTION;
}

static void hi6402_hifi_clk_enable(bool enable)
{
	IN_FUNCTION;
	if (enable) {
		hi6402_hifi_reg_set_bit(HI6402_DSP_SC_DSP_CTRL0, 3);
		/*bit6:hifi_div_clk_en 0:disable 1:enable*/
		hi6402_hifi_reg_set_bit(HI6402_DSP_CLK_CFG, 6);
	} else {
		hi6402_hifi_reg_clr_bit(HI6402_DSP_SC_DSP_CTRL0, 3);
		/*bit6:hifi_div_clk_en 0:disable 1:enable*/
		hi6402_hifi_reg_clr_bit(HI6402_DSP_CLK_CFG, 6);
	}
	OUT_FUNCTION;
}

static void hi6402_hifi_watchdog_enable(bool enable)
{
	IN_FUNCTION;
	if (enable) {
		/*bit3:wd_pclk_en 0:disable 1:enable*/
		hi6402_hifi_reg_set_bit(HI6402_DSP_APB_CLK_CFG, 3);
	} else {
		/*bit3:wd_pclk_en 0:disable 1:enable*/
		hi6402_hifi_reg_clr_bit(HI6402_DSP_APB_CLK_CFG, 3);
	}
	OUT_FUNCTION;
}

/* when hifi is not running, ap access APB register with 0x20007020 bit[2]=1'b0
 * when hifi is running, ap & hifi access APB register with 0x20007020 bit[2]=0'b0*/
static void hi6402_ram2axi_cfg_with_hifi(bool enable)
{
	unsigned int val;
	IN_FUNCTION;
	if (enable) {
		val = hi6402_hifi_read_reg(HI6402_DSP_RAM2AXI_CTRL);
		if(0 == (val & 0x1))
			HI6402_DSP_ERROR("reg error! 0x20007020 = 0x%x\n", val);
		hi6402_hifi_write_reg(HI6402_DSP_RAM2AXI_CTRL, 0x1);
		//hi6402_hifi_reg_clr_bit(HI6402_DSP_RAM2AXI_CTRL, 2);
	} else {
		//hi6402_hifi_reg_set_bit(HI6402_DSP_RAM2AXI_CTRL, 2);
		val = hi6402_hifi_read_reg(HI6402_DSP_RAM2AXI_CTRL);
		if(0 == (val & 0x1))
			HI6402_DSP_ERROR("reg error! 0x20007020 = 0x%x\n", val);
		hi6402_hifi_write_reg(HI6402_DSP_RAM2AXI_CTRL, 0x5);
	}
	OUT_FUNCTION;
}

static void hi6402_hifi_init(void)
{
	IN_FUNCTION;
	/* 1.reset dsp_pd_srst_req */
	hi6402_hifi_reg_set_bit(HI6402_DSP_SW_RST_REQ, 4);

	/* 2.close dspif clocks, and soft reset dspif */
	hi6402_hifi_write_reg(HI6402_DSP_I2S_DSPIF_CLK_EN, 0x0);
	hi6402_hifi_reg_clr_bit(HI6402_DSP_DAC_DP_CLK_EN_1, 4);

	/* 3.turn on dsp_top_mtcmos_ctrl*/
	hi6402_hifi_reg_clr_bit(HI6402_DSP_LP_CTRL, 0);
	/* 4.enable dsp_top_iso_ctrl */
	hi6402_hifi_reg_clr_bit(HI6402_DSP_LP_CTRL, 1);

	/* 5.sc_dsp_en dsp low power enable */
	hi6402_hifi_reg_clr_bit(HI6402_DSP_SC_DSP_CTRL0, 0);
	hi6402_hifi_reg_set_bit(HI6402_DSP_SC_DSP_CTRL0, 5);
	hi6402_hifi_reg_set_bit(HI6402_DSP_SC_DSP_CTRL0, 6);
	hi6402_hifi_runstall_cfg(false);

	/* 6.apb_pd_pclk_en Open APB clock of power-off area */
	hi6402_hifi_reg_set_bit(HI6402_DSP_APB_CLK_CFG, 6);

	/* 7.Release dsp_pd_srst_req */
	hi6402_hifi_reg_clr_bit(HI6402_DSP_SW_RST_REQ, 4);

	/* disable watchdog */
	hi6402_hifi_watchdog_enable(false);
	priv.is_watchdog_coming = false;
	priv.is_sync_write_timeout = false;

	/* sc_dsp_sft_clk_en */
	hi6402_hifi_clk_enable(true);

	OUT_FUNCTION;
}

static void hi6402_hifi_deinit(void)
{
	/* Close watchdog clock */
	hi6402_hifi_watchdog_enable(false);

	/* Close HIFI clock */
	hi6402_hifi_reg_clr_bit(HI6402_DSP_SC_DSP_CTRL0, 0);
	hi6402_hifi_clk_enable(false);

	/* Close APB clock */
	hi6402_hifi_reg_clr_bit(HI6402_DSP_APB_CLK_CFG, 6);

	/* Close DSPIF clocks, and soft reset DSPIF */
	hi6402_hifi_write_reg(HI6402_DSP_I2S_DSPIF_CLK_EN, 0x0);
	hi6402_hifi_reg_clr_bit(HI6402_DSP_DAC_DP_CLK_EN_1, 4);

	/* Enable isolation cell */
	hi6402_hifi_reg_set_bit(HI6402_DSP_LP_CTRL, 1);

	/* Soft reset HIFI */
	hi6402_hifi_reg_set_bit(HI6402_DSP_SW_RST_REQ, 4);

	/* Turn off power of power-off area */
	hi6402_hifi_reg_set_bit(HI6402_DSP_LP_CTRL, 0);

	/* Pull up runstall of HIFI */
	hi6402_hifi_runstall_cfg(false);

	/* disable axi */
	hi6402_hifi_write_reg(HI6402_DSP_RAM2AXI_CTRL, 0x05);
}

static void hi6402_mad_set_param(void)
{
	//ana_stable_l time 6ms
	hi6402_hifi_write_reg(HI6402_MAD_ANA_TIME_L, 0xC1);
	//pll stable time
	hi6402_hifi_write_reg(HI6402_MAD_PLL_TIME_L, 0x01);
	//adc stable time 5ms
	hi6402_hifi_write_reg(HI6402_MAD_ADC_TIME_L, 0xB1);
	//mad_omit_samp 2ms
	hi6402_hifi_write_reg(HI6402_MAD_OMIT_SAMP, 0x20);
	//rms_number 1
	hi6402_hifi_write_reg(HI6402_MAD_RMS_NUM, 0x01);
	//mad_auto_act_number
	hi6402_hifi_write_reg(HI6402_MAD_AUTO_ACT_NUMBER, 0x0);
	//mad_rms_mode & ana_stable_h
	hi6402_hifi_write_reg(HI6402_MAD_RMS_MODE, 0xC0);
	//mad_sleep_time0 5ms
	hi6402_hifi_write_reg(HI6402_MAD_SLEEP_TIME0, 0xA0);
	//mad_sleep_time1
	hi6402_hifi_write_reg(HI6402_MAD_SLEEP_TIME1, 0x0);
	//mad_rms_int_en
	hi6402_hifi_reg_set_bit(HI6402_MAD_RMS_INT_EN, HI6402_MAD_RMS_INT_EN_BIT);
	//mad_rms_thre 30 0x23280
	hi6402_hifi_write_reg(HI6402_MAD_RMS_THRE0, 0x80);
	//mad_rms_thre
	hi6402_hifi_write_reg(HI6402_MAD_RMS_THRE1, 0x32);
	//mad_rms_thre
	hi6402_hifi_write_reg(HI6402_MAD_RMS_THRE2, 0x02);
	//mad_rms_thre
	hi6402_hifi_write_reg(HI6402_MAD_RMS_THRE3, 0x00);
	//mad_rms_time 10ms
	hi6402_hifi_write_reg(HI6402_MAD_RMS_TIME0, 0xA0);
	//mad_rms_time
	hi6402_hifi_write_reg(HI6402_MAD_RMS_TIME1, 0x00);
	//mad_rms_diff_thre
	hi6402_hifi_write_reg(HI6402_MAD_RMS_DIFF_THRE0, 0x49);
	//mad_rms_diff_thre
	hi6402_hifi_write_reg(HI6402_MAD_RMS_DIFF_THRE1, 0x28);
	//mad_filter_id
	hi6402_hifi_reg_write_bits(HI6402_MAD_FILTER_ID,
		0x1<<HI6402_MAD_FILTER_ID_BIT, 0x7<<HI6402_MAD_FILTER_ID_BIT);
	//mad_filter_id1
	hi6402_hifi_reg_write_bits(HI6402_MAD_FILTER_ID1,
		0x3<<HI6402_MAD_FILTER_ID1_BIT, 0x7<<HI6402_MAD_FILTER_ID1_BIT);
	return;
}

/* message handling */
static void hi6402_notify_dsp_to_receive(void)
{
	hi6402_hifi_reg_set_bit(HI6402_DSP_DSP_NMI, 2);
}

/* HI6402_DSP_CMD_STATUS :
 * bit 0 sync_msg
 * bit 1 dsp_pllswitch
 * bit 2 dsp_pwron
 */
static irqreturn_t hi6402_msg_irq_handler(int irq, void *data)
{
	IN_FUNCTION;

	if(!hi6402_hifi_read_reg(HI6402_DSP_CMD_STATUS_VLD)){
		HI6402_DSP_ERROR("CMD invalid\n");
		return IRQ_HANDLED;
	}
	/*
	 * todo : 2.use else if ? cmd should not come together ?
	 * todo : 3.freq high -> freq low and stop mad cmd maybe come together
	 *			(eg.headset play and mad on,then stop play and stop mad)
	 */

	if(hi6402_hifi_read_reg(HI6402_DSP_CMD_STATUS) & (0x1 << 0)){
		hi6402_hifi_reg_clr_bit(HI6402_DSP_SUB_CMD_STATUS, 0);
		priv.sync_msg_ret = 1;
		wake_up_interruptible_all(&priv.sync_msg_wq);
	}
	if(hi6402_hifi_read_reg(HI6402_DSP_CMD_STATUS) & (0x1 << 1)){
		hi6402_hifi_reg_clr_bit(HI6402_DSP_SUB_CMD_STATUS, 1);
		priv.dsp_pllswitch_done= 1;
		wake_up_interruptible_all(&priv.dsp_pllswitch_wq);
	}
	if(hi6402_hifi_read_reg(HI6402_DSP_CMD_STATUS) & (0x1 << 2)){
		hi6402_hifi_reg_clr_bit(HI6402_DSP_SUB_CMD_STATUS, 2);
		priv.dsp_pwron_done = HIFI_STATE_INIT;
		wake_up_interruptible_all(&priv.dsp_pwron_wq);
	}
	OUT_FUNCTION;

	return IRQ_HANDLED;
}

static void hi6402_write(const unsigned int start_addr,
			 const unsigned char *arg,
			 const unsigned int len)
{
	int i = 0;
	unsigned int *to_send = NULL;

	BUG_ON(arg == NULL);
	BUG_ON(len == 0);

	to_send = (unsigned int *)arg;
	for (i = 0; i < len; i += 4) {
		hi6402_hifi_write_reg(start_addr + i, *to_send++);
	}
}

static void hi6402_read(const unsigned int start_addr,
			unsigned char *arg,
			const unsigned int len)
{
	int i = 0;
	unsigned int *to_receive = NULL;

	BUG_ON(arg == NULL);
	BUG_ON(len == 0);

	to_receive = (unsigned int *)arg;
	for (i = 0; i < len; i += 4) {
		*to_receive++ = hi6402_hifi_read_reg(start_addr + i);
	}
}

static int hi6402_write_mlib_para(const unsigned char *arg,
				  const unsigned int len)
{
	if (len > MAX_PARA_SIZE) {
		HI6402_DSP_ERROR("msg length:%u exceed limit!\n", len);
		return ERROR;
	}

	if ((len & 0x3) != 0) {
		HI6402_DSP_ERROR("msg length:%u is not 4 byte aligned\n", len);
		return ERROR;
	}

	hi6402_write(DSP_MLIB_PARA_ADDR, arg, len);

	return OK;
}

static int hi6402_read_mlib_para(unsigned char *arg, const unsigned int len)
{
	BUG_ON(arg == NULL);
	BUG_ON(len == 0);

	if (len > MAX_PARA_SIZE) {
		HI6402_DSP_ERROR("msg length:%u exceed limit!\n", len);
		return ERROR;
	}

	if ((len & 0x3) != 0) {
		HI6402_DSP_ERROR("msg length:%u is not 4 byte aligned\n", len);
		return ERROR;
	}

	hi6402_read(DSP_MLIB_PARA_ADDR, arg, len);

	return OK;
}

unsigned int hi6402_read_mlib_test_para(unsigned char *arg, unsigned int len)
{
	unsigned int addr = 0;
	unsigned int count;
	unsigned int value;
	IN_FUNCTION;

	addr = HI6402_MLIB_TO_AP_MSG_ADDR;

	if (hi6402_hifi_read_reg(addr) != UCOM_PROTECT_WORD) {
		HI6402_DSP_ERROR("mlib test cannot find parameters!\n");
		return -1;
	}

	for (count = 1; count < (HI6402_MLIB_TO_AP_MSG_LEN / sizeof(unsigned int)); count++) {
		value = hi6402_hifi_read_reg(addr + count * sizeof(unsigned int));
		if(count * sizeof(unsigned int) >= len) {
			HI6402_DSP_ERROR("input not enough space!\n");
			return 0;
		}

		if(value == UCOM_PROTECT_WORD && count > 0) {
			break;
		}

		memcpy(arg + (count - 1) * sizeof(unsigned int), &value, sizeof(value));
		HI6402_DSP_INFO("mlib test para[0x%x]\n", value);
	}

	OUT_FUNCTION;
	return (count - 1) * sizeof(unsigned int);
}

static int hi6402_write_msg(const unsigned char *arg, const unsigned int len)
{
	int ret = OK;

	IN_FUNCTION;

	if (len > MAX_MSG_SIZE) {
		HI6402_DSP_ERROR("msg length exceed limit!\n");
		return ERROR;
	}

	if ((len & 0x3) != 0) {
		HI6402_DSP_ERROR("msg length:%u is not 4 byte aligned\n", len);
		return ERROR;
	}

	hi6402_write(DSP_MSG_START_ADDR, arg, len);

	priv.sync_msg_ret = 0;
	hi6402_notify_dsp_to_receive();

	OUT_FUNCTION;

	return ret;
}

static int hi6402_get_input_param(unsigned int usr_para_size,
				  void __user *usr_para_addr,
				  unsigned int *krn_para_size,
				  void **krn_para_addr)
{
	void *para_in = NULL;
	unsigned int para_size_in = 0;

	IN_FUNCTION;

	if (NULL == usr_para_addr) {
		HI6402_DSP_ERROR("usr_para_addr is null no user data\n");
		goto ERR;
	}

	if ((0 == usr_para_size) || (usr_para_size > MAX_USR_INPUT_SIZE)) {
		HI6402_DSP_ERROR("usr buffer size:%u out of range\n", usr_para_size);
		goto ERR;
	}

	para_size_in = roundup(usr_para_size, 4);

	para_in = kzalloc(para_size_in, GFP_KERNEL);
	if (para_in == NULL) {
		HI6402_DSP_ERROR("kzalloc fail\n");
		goto ERR;
	}

	if (copy_from_user(para_in, usr_para_addr, usr_para_size)) {
		HI6402_DSP_ERROR("copy_from_user fail\n");
		goto ERR;
	}

	*krn_para_size = para_size_in;
	*krn_para_addr = para_in;

	OUT_FUNCTION;

	return OK;

ERR:
	if (para_in != NULL) {
		kfree(para_in);
		para_in = NULL;
	}

	OUT_FUNCTION;

	return ERROR;
}

static void hi6402_param_free(void **krn_para_addr)
{
	IN_FUNCTION;

	if (*krn_para_addr != NULL) {
		kfree(*krn_para_addr);
		*krn_para_addr = NULL;
	} else {
		HI6402_DSP_ERROR("krn_para_addr to free is NULL\n");
	}

	OUT_FUNCTION;

	return;
}

static int hi6402_alloc_output_param_buffer(unsigned int usr_para_size,
					    void __user *usr_para_addr,
						unsigned int *krn_para_size,
						void **krn_para_addr)
{
	BUG_ON(*krn_para_addr != NULL);

	HI6402_DSP_DEBUG("malloc size: %u\n", usr_para_size);
	if (usr_para_size == 0 || usr_para_size > MAX_OUT_PARA_SIZE) {
		HI6402_DSP_ERROR("usr space size invalid\n");
		return ERROR;
	}

	if (usr_para_addr == NULL) {
		HI6402_DSP_ERROR("usr_para_addr is NULL\n");
		return ERROR;
	}

	*krn_para_addr = kzalloc(usr_para_size, GFP_KERNEL);
	if (*krn_para_addr == NULL) {
		HI6402_DSP_ERROR("kzalloc fail\n");
		return ERROR;
	}

	*krn_para_size = usr_para_size;

	return OK;
}

static int hi6402_put_output_param(unsigned int usr_para_size,
				   void __user *usr_para_addr,
				   unsigned int krn_para_size,
				   void *krn_para_addr)
{
	int ret = OK;

	BUG_ON(usr_para_size == 0);
	BUG_ON(usr_para_addr == NULL);
	BUG_ON(krn_para_size == 0);
	BUG_ON(krn_para_addr == NULL);

	IN_FUNCTION;

	if (krn_para_size != usr_para_size) {
		HI6402_DSP_ERROR("krn para size:%d != usr para size%d\n",
				 krn_para_size, usr_para_size);
		return ERROR;
	}

	HI6402_DSP_DEBUG("user_para_size:%d\n", usr_para_size);
	ret = copy_to_user(usr_para_addr, krn_para_addr, usr_para_size);
	if (ret != OK) {
		HI6402_DSP_ERROR("copy_to_user fail, ret is %d\n", ret);
		return ERROR;
	}

	OUT_FUNCTION;

	return OK;
}

static bool hi6402_error_detect(void)
{
	if (HI6402_VERSION_CS != hi6402_hifi_read_reg(HI6402_VERSION)) {
		HI6402_DSP_ERROR("Codec err,ver 0x%x,pll 0x%x\n",
			hi6402_hifi_read_reg(HI6402_VERSION),
			hi6402_hifi_read_reg(HI6402_CODEC_ANA_PLL));
		if (!dsm_client_ocuppy(dsm_audio_client)) {
			dsm_client_record(dsm_audio_client, "DSM_HI6402_CRASH\n");
			dsm_client_notify(dsm_audio_client, DSM_CODEC_HIFI_RESET);
		}
		return true;
	}
	return false;
}

static int hi6402_sync_write(const unsigned char *arg, const unsigned int len)
{
	int ret = OK;
	int count = HI6402_EXCEPTION_RETRY;
	IN_FUNCTION;

	priv.sync_msg_ret = 0;

	/* can't get codec version,reset system */
	BUG_ON(hi6402_error_detect());

	while (count) {
		ret = hi6402_write_msg(arg, len);
		if (OK != ret) {
			HI6402_DSP_ERROR("send msg failed\n");
			goto out;
		}
		if (wait_event_interruptible_timeout(priv.sync_msg_wq,
			(priv.sync_msg_ret == 1), HZ) != 0) {
			break;
		}
		count--;
		HI6402_DSP_ERROR("cmd timeout retry %d\n",
			HI6402_EXCEPTION_RETRY - count);
	}

	if (0 == count) {
		/* can't get codec version,reset system */
		BUG_ON(hi6402_error_detect());

		HI6402_DSP_ERROR("cmd timeout\n");
		if (!(priv.is_watchdog_coming) && !(priv.is_sync_write_timeout)) {
			HI6402_DSP_ERROR("save log and reset media \n");
			priv.is_sync_write_timeout = true;
			rdr_codec_hifi_watchdog_process();
		}
		ret = BUSY;
	}

out:
	OUT_FUNCTION;

	return ret;
}

static void hi6402_hifi_pause(void)
{
	IN_FUNCTION;

	hi6402_hifi_watchdog_enable(false);
	hi6402_hifi_clk_enable(false);

	OUT_FUNCTION;
}

static void hi6402_hifi_resume(enum hi6402_pll_status pll_state)
{
	IN_FUNCTION;

	hi6402_hifi_clk_enable(true);
	hi6402_hifi_watchdog_enable(true);

	OUT_FUNCTION;
	return;
}

static bool hi6402_hifi_notify_dsp_pllswitch(unsigned char state)
{

	/* notify dsp stop dma and close dspif */
	priv.dsp_pllswitch_done = 0;
	hi6402_hifi_write_reg(HI6402_DSP_CMD0, state);
	HI6402_DSP_INFO("cmd[0x%x]reg[0x%x]\n",state,
			hi6402_hifi_read_reg(HI6402_DSP_CMD0));

	hi6402_notify_dsp_to_receive();
	/* wait 100s(600ms in total) for dsp close dma and dsspif */
	if (wait_event_interruptible_timeout(priv.dsp_pllswitch_wq,
					   (priv.dsp_pllswitch_done == 1), HZ) == 0) {
		HI6402_DSP_ERROR("wait for dsp_pllswitch_done timeout\n");
	}
	return true;
}

void hi6402_hifi_cfg_before_pll_switch(void)
{
	IN_FUNCTION;

	mutex_lock(&priv.state_mutex);
	if (priv.dsp_is_running) {
		/* todo : put below code in hi6402_hifi_pause() */
		HI6402_DSP_INFO("notify dsp close dma\n");

		hi6402_hifi_notify_dsp_pllswitch(HIFI_POWER_CLK_OFF);
		hi6402_hifi_pause();
	}

	mutex_unlock(&priv.state_mutex);

	OUT_FUNCTION;

	return;
}

bool hi6402_hifi_is_running(void)
{
	return priv.dsp_is_running;
}

static const char *state_name[] = {
	"PLL_DOWN",
	"PLL_HIGH_FREQ",
	"PLL_LOW_FREQ",
};

void hi6402_hifi_cfg_after_pll_switch(enum hi6402_pll_status new_state)
{
	int value = 0;

	IN_FUNCTION;

	mutex_lock(&priv.state_mutex);

	value = hi6402_hifi_read_reg(0x20007000);
	HI6402_DSP_INFO("%s->%s, dsp_is_runing:%d, version:%#x, \n",
		state_name[priv.pll_state], state_name[new_state], priv.dsp_is_running, value);

	priv.pll_state = new_state;
	hi6402_hifi_write_reg(HI6402_DSP_CMD1, priv.pll_state);

	if (priv.dsp_is_running) {
		hi6402_hifi_resume(priv.pll_state);
		/* todo : put below code in hi6402_hifi_resume() */

		hi6402_hifi_notify_dsp_pllswitch(HIFI_POWER_CLK_ON);
	}
	mutex_unlock(&priv.state_mutex);

	OUT_FUNCTION;
	return;
}
/* dsp_if bypass config bit 6,7 */
static unsigned int hi6402_sc_src_lr_ctrls_m[] = {
	HI6402_SC_S1_SRC_LR_CTRL_M,
	HI6402_SC_S2_SRC_LR_CTRL_M,
	HI6402_SC_S3_SRC_LR_CTRL_M,
	HI6402_SC_S4_SRC_LR_CTRL_M,
	HI6402_SC_MISC_SRC_CTRL_H,
};

/* dsp_if io sample rate config */
static unsigned int hi6402_sc_fs_ctrls_h[] = {
	HI6402_SC_FS_S1_CTRL_H,
	HI6402_SC_FS_S2_CTRL_H,
	HI6402_SC_FS_S3_CTRL_H,
	HI6402_SC_FS_S4_CTRL_H,
	HI6402_SC_FS_MISC_CTRL,
};

/* check for parameters used by misc, only for if_open/if_close */
static int hi6402_dsp_if_para_check(const struct krn_param_io_buf *param)
{
	unsigned int i = 0;
	unsigned int message_size = 0;
	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = NULL;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = NULL;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if (param->buf_size_in < sizeof(DSP_IF_OPEN_REQ_STRU)) {
		HI6402_DSP_ERROR("input size:%u invalid\n", param->buf_size_in);
		return ERROR;
	}

	dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)(param->buf_in);
	dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	if (dma_msg_stru->uwIFCount >= HI6402_HIFI_DSP_IF_PORT_BUTT) {
		HI6402_DSP_ERROR("try to open too many ifs\n");
		return ERROR;
	}

	message_size = sizeof(PCM_IF_MSG_STRU) * (dma_msg_stru->uwIFCount)
			+ sizeof(DSP_IF_OPEN_REQ_STRU);
	if (param->buf_size_in < message_size) {
		HI6402_DSP_ERROR("input size:%u invalid\n", param->buf_size_in);
		return ERROR;
	}

	for (i = 0; i < dma_msg_stru->uwIFCount; i++) {
		PCM_IF_MSG_STRU *pcm_if_msg = &dma_msg_stru->stIFCfgList[i];

		if (pcm_if_msg->uwIFId >= HI6402_HIFI_DSP_IF_PORT_BUTT) {
			HI6402_DSP_ERROR("dsp if ID %d is out of range\n",
					pcm_if_msg->uwIFId);
			return ERROR;
		}

		switch (pcm_if_msg->uwSampleRateIn) {
		case 0:
			HI6402_DSP_INFO("DATA_HOOK_PROCESS, sample_rate=0\n");
			break;
		case 8000:
		case 16000:
		case 32000:
		case 48000:
		case 96000:
		case 192000:
			break;
		default:
			HI6402_DSP_ERROR("unsupport sample_rate %d \n",
					pcm_if_msg->uwSampleRateIn);
			return ERROR;
		}
	}

	return OK;
}

static int hi6402_dsp_if_set_sample_rate(unsigned int dsp_if_id,
						unsigned int sample_rate)
{
	unsigned int addr = 0;
	unsigned char mask = 0;
	unsigned char sample_rate_index = 0;

	unsigned int i2s_id = dsp_if_id / 2;
	unsigned int direct =
		(dsp_if_id & 0x1) ? HI6402_HIFI_PCM_OUT : HI6402_HIFI_PCM_IN;

	IN_FUNCTION;

	BUG_ON(i2s_id >= ARRAY_SIZE(hi6402_sc_fs_ctrls_h));

	switch (sample_rate) {

	case 0:
		HI6402_DSP_INFO("DATA_HOOK_PROCESS, sample_rate=0\n");
		break;
	case 8000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_8K;
		break;
	case 16000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_16K;
		break;
	case 32000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_32K;
		break;
	case 48000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_48K;
		break;
	case 96000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_96K;
		break;
	case 192000:
		sample_rate_index = HI6402_HIFI_PCM_SAMPLE_RATE_192K;
		break;
	default:
		/* shouldn't be here */
		HI6402_DSP_ERROR("unsupport sample_rate %d!! \n", sample_rate);
	}

	addr = hi6402_sc_fs_ctrls_h[i2s_id];
	mask = (direct == HI6402_HIFI_PCM_IN) ? 0xf : 0xf0;
	sample_rate_index = (direct == HI6402_HIFI_PCM_IN)
		                ? sample_rate_index : sample_rate_index << 4;
	/* Todo: dac dspif sample rate maybe different */
	if(dsp_if_id == HI6402_HIFI_DSP_IF_PORT_8){
		mask = 0x7c;
		sample_rate_index = sample_rate_index << 4;
	}
	hi6402_hifi_reg_write_bits(addr, sample_rate_index, mask);

	OUT_FUNCTION;

	return 0;
}

static void hi6402_dsp_if_set_bypass(unsigned int dsp_if_id, bool enable)
{
	unsigned int addr = 0;
	unsigned int bit = 0;

	unsigned int i2s_id = dsp_if_id / 2;
	unsigned int direct =
		(dsp_if_id & 0x1) ? HI6402_HIFI_PCM_OUT : HI6402_HIFI_PCM_IN;

	IN_FUNCTION;

	BUG_ON(i2s_id >= ARRAY_SIZE(hi6402_sc_src_lr_ctrls_m));

	bit = (direct == HI6402_HIFI_PCM_IN) ? 6 : 7;
	if(dsp_if_id == HI6402_HIFI_DSP_IF_PORT_8)
		bit = 4;
	addr = hi6402_sc_src_lr_ctrls_m[i2s_id];

	if (enable) {
		hi6402_hifi_reg_set_bit(addr, bit);
	} else {
		hi6402_hifi_reg_clr_bit(addr, bit);
	}

	OUT_FUNCTION;
}

/* now we'v alread check the para, so don't do it again */
static void hi6402_dsp_if_sample_rate_set(const char *arg)
{
	unsigned int i = 0;

	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)arg;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	IN_FUNCTION;

	for (i = 0; i < dma_msg_stru->uwIFCount; i++) {
		PCM_IF_MSG_STRU *pcm_if_msg = &dma_msg_stru->stIFCfgList[i];

		hi6402_dsp_if_set_sample_rate(pcm_if_msg->uwIFId,
				pcm_if_msg->uwSampleRateIn);
	}

	OUT_FUNCTION;
}

static void hi6402_dsp_run(void)
{
	IN_FUNCTION;

	mutex_lock(&priv.state_mutex);

	if (!priv.dsp_is_running) {
		hi6402_ram2axi_cfg_with_hifi(true);
		hi6402_hifi_clk_enable(true);
		hi6402_hifi_watchdog_enable(true);
		priv.dsp_is_running = true;
	}

	mutex_unlock(&priv.state_mutex);

	OUT_FUNCTION;
}

static void hi6402_dsp_stop(void)
{
	IN_FUNCTION;

	mutex_lock(&priv.state_mutex);

	if (priv.dsp_is_running) {
		hi6402_hifi_watchdog_enable(false);
		hi6402_hifi_clk_enable(false);
		hi6402_ram2axi_cfg_with_hifi(false);
		priv.dsp_is_running = false;
	}

	mutex_unlock(&priv.state_mutex);

	OUT_FUNCTION;
}

static int hi6402_request_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	HI6402_DSP_INFO("sid[0x%x]hifreq_status[0x%x]", scene_id,
		priv.high_freq_scene_status);

	if (scene_id >= HI_FREQ_SCENE_BUTT) {
		HI6402_DSP_ERROR("unknow scene for pll: %u\n", scene_id);
		return ERROR;
	}

	if ((priv.high_freq_scene_status & (1 << scene_id)) != 0) {
		HI6402_DSP_WARNING("scene: %u is alread started.\n", scene_id);
		return REDUNDANT;
	}

	if (priv.high_freq_scene_status == 0) {
		hi6402_hifi_set_pll(true);
		hi6402_dsp_run();
	}

	priv.high_freq_scene_status |= (1 << scene_id);

	OUT_FUNCTION;

	return OK;
}

static int hi6402_release_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	if (scene_id >= HI_FREQ_SCENE_BUTT) {
		HI6402_DSP_ERROR("unknow scene for pll: %u\n", scene_id);
		return ERROR;
	}

	if ((priv.high_freq_scene_status & (1 << scene_id)) == 0) {
		HI6402_DSP_WARNING("scene: %u is NOT started\n", scene_id);
		return REDUNDANT;
	}

	priv.high_freq_scene_status &= ~(1 << scene_id);

	if (priv.high_freq_scene_status == 0) {
		if (priv.low_freq_scene_status == 0) {
			hi6402_dsp_stop();
		}
		hi6402_hifi_set_pll(false);
	}

	OUT_FUNCTION;

	return OK;
}

static int hi6402_request_low_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	if (scene_id >= LOW_FREQ_SCENE_BUTT) {
		HI6402_DSP_ERROR("unknow scene for mad pll: %u\n", scene_id);
		return ERROR;
	}

	if ((priv.low_freq_scene_status & (1 << scene_id)) != 0) {
		HI6402_DSP_WARNING("scene: %u is alread started.\n", scene_id);
		return REDUNDANT;
	}

	if (priv.low_freq_scene_status == 0) {
		hi6402_hifi_set_low_pll(true);
		hi6402_dsp_run();
	}

	priv.low_freq_scene_status |= (1 << scene_id);
	HI6402_DSP_INFO("low scene: 0x%x\n", priv.low_freq_scene_status);

	OUT_FUNCTION;

	return OK;
}

static int hi6402_release_low_pll_resource(unsigned int scene_id)
{
	IN_FUNCTION;

	if (scene_id >= LOW_FREQ_SCENE_BUTT) {
		HI6402_DSP_ERROR("unknow scene for low pll: %u\n", scene_id);
		return ERROR;
	}

	if ((priv.low_freq_scene_status & (1 << scene_id)) == 0) {
		HI6402_DSP_WARNING("scene: %u is NOT started\n", scene_id);
		return REDUNDANT;
	}

	priv.low_freq_scene_status &= ~(1 << scene_id);

	if (priv.low_freq_scene_status == 0) {
		if (priv.high_freq_scene_status == 0) {
			hi6402_dsp_stop();
		}
		hi6402_hifi_set_low_pll(false);
	}

	OUT_FUNCTION;

	return OK;
}

void hi6402_hifi_pwr_off(void)
{
	hi6402_dsp_stop();
	hi6402_hifi_runstall_cfg(false);
}

static int check_dp_clk(void)
{
	/* waiting 100ms at most before send if_open cmd, when dpclk is disable */
	unsigned int uwCnt = HI6402_IFOPEN_WAIT4DPCLK;
	while(--uwCnt) {
		if(1 == hi6402_hifi_read_reg(HI6402DSP_CHECK_DP_CLK_REG)) {
			HI6402_DSP_INFO("DP clk is enable, goto send if_open\n");
			return OK;
		} else {
			/* wait 100 to 110us every cycle, if dpclk is disable. */
			usleep_range(100, 110);
		}
	}

	return ERROR;
}

/*
 * cmd_process_functions
 * */
static int hi6402_func_if_open(struct krn_param_io_buf *param)
{
	int ret = 0;

	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = NULL;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = NULL;

	IN_FUNCTION;

	ret = hi6402_dsp_if_para_check(param);
	if (ret != OK) {
		HI6402_DSP_ERROR("dsp if parameter invalid\n");
		goto end;
	}

	dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)(param->buf_in);
	dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	switch (dma_msg_stru->uwProcessId) {
// current not support HOOK
#if 0
	case MLIB_PATH_DATA_HOOK:
		ret = hi6402_request_pll_resource(HI_FREQ_SCENE_HOOK);
		if (ret != OK) {
			goto end;
		}
		break;
#endif
	case MLIB_PATH_WAKEUP:
		ret = hi6402_request_low_pll_resource(LOW_FREQ_SCENE_WAKE_UP);
		if (ret != OK) {
			goto end;
		}
		break;
	case MLIB_PATH_SMARTPA:
		ret = check_dp_clk();
		if (ret != OK) {
			HI6402_DSP_ERROR("DP clk is disable, it's dangerous to send if_open\n");
			if (!dsm_client_ocuppy(dsm_audio_client)) {
				dsm_client_record(dsm_audio_client, "DSM_CODEC_HIFI_IF_OPEN_WITHOUT_DPCLK\n");
				dsm_client_notify(dsm_audio_client, DSM_CODEC_HIFI_IF_OPEN_ERR);
			}
			goto end;
		}
		ret = hi6402_request_pll_resource(HI_FREQ_SCENE_PA);
		if (ret != OK) {
			goto end;
		}
		break;
	default:
		HI6402_DSP_ERROR("ProcessId:%u unsupport\n", dma_msg_stru->uwProcessId);
		ret = ERROR;
		goto end;
	}

	hi6402_dsp_if_sample_rate_set(param->buf_in);
	hi6402_hifi_write_reg(HI6402_DSP_CMD1, priv.pll_state);
	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		goto end;
	}

end:
	OUT_FUNCTION;
	return ret;
}

static int hi6402_func_if_close(struct krn_param_io_buf *param)
{
	int ret = 0;
	DSP_IF_OPEN_REQ_STRU *dsp_if_open_req = NULL;
	PCM_PROCESS_DMA_MSG_STRU *dma_msg_stru = NULL;

	IN_FUNCTION;

	ret = hi6402_dsp_if_para_check(param);
	if (ret != OK) {
		HI6402_DSP_ERROR("dsp if parameter invalid\n");
		goto end;
	}

	dsp_if_open_req = (DSP_IF_OPEN_REQ_STRU *)(param->buf_in);
	dma_msg_stru = &dsp_if_open_req->stProcessDMA;

	if (dma_msg_stru->uwProcessId == MLIB_PATH_WAKEUP) {
		if ((priv.low_freq_scene_status & (1 << LOW_FREQ_SCENE_WAKE_UP)) == 0) {
			HI6402_DSP_WARNING("scene wakeup is NOT opened.\n");
			ret = REDUNDANT;
			goto end;
		}
// current not support HOOK
#if 0
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_DATA_HOOK) {
		if ((priv.high_freq_scene_status & (1 << HI_FREQ_SCENE_HOOK)) == 0) {
			HI6402_DSP_WARNING("scene datahook is NOT opened.\n");
			ret = REDUNDANT;
			goto end;
		}
#endif
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_SMARTPA) {
		if ((priv.high_freq_scene_status & (1 << HI_FREQ_SCENE_PA)) == 0) {
			HI6402_DSP_WARNING("scene smartpa is NOT opened.\n");
			ret = REDUNDANT;
			goto end;
		}
	} else {
		HI6402_DSP_ERROR("ProcessId:%u unsupport\n", dma_msg_stru->uwProcessId);
		ret = ERROR;
		goto end;
	}

	hi6402_hifi_write_reg(HI6402_DSP_CMD1, priv.pll_state);
	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("sync_write ret=%d\n", ret);
		goto end;
	}

	if (dma_msg_stru->uwProcessId == MLIB_PATH_WAKEUP) {
		hi6402_release_low_pll_resource(LOW_FREQ_SCENE_WAKE_UP);
// current not support HOOK
#if 0
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_DATA_HOOK) {
		hi6402_release_pll_resource(HI_FREQ_SCENE_HOOK);
#endif
	} else if (dma_msg_stru->uwProcessId == MLIB_PATH_SMARTPA) {
		hi6402_release_pll_resource(HI_FREQ_SCENE_PA);
	}
end:
	OUT_FUNCTION;

	return ret;
}

static int hi6402_func_fastmode(struct krn_param_io_buf *param)
{
	int ret = OK;

	IN_FUNCTION;

	hi6402_request_low_pll_resource(LOW_FREQ_SCENE_FAST_TRANS_SET);

	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);

	hi6402_release_low_pll_resource(LOW_FREQ_SCENE_FAST_TRANS_SET);

	return ret;
}

static int hi6402_func_para_set(struct krn_param_io_buf *param)
{
	int ret = OK;
	MLIB_PARA_SET_REQ_STRU *mlib_para = NULL;
	struct MlibParameterST *mlib_para_content = NULL;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if (param->buf_size_in < sizeof(MLIB_PARA_SET_REQ_STRU)) {
		HI6402_DSP_ERROR("input size:%u invalid\n", param->buf_size_in);
		return ERROR;
	}

	mlib_para = (MLIB_PARA_SET_REQ_STRU *)param->buf_in;

	mlib_para_content= (struct MlibParameterST *)mlib_para->aucData;

	if (0 == mlib_para->uwSize
	|| mlib_para->uwSize > (param->buf_size_in - sizeof(MLIB_PARA_SET_REQ_STRU))) {
		HI6402_DSP_ERROR("mlib_para size is out of range.\n");
		return ERROR;
	}

	if (MLIB_ST_PARA_TRANSACTION == mlib_para_content->key) {
		hi6402_request_low_pll_resource(LOW_FREQ_SCENE_SET_PARA);
	} else {
		hi6402_request_pll_resource(HI_FREQ_SCENE_SET_PARA);
	}

	ret = hi6402_write_mlib_para(mlib_para->aucData, mlib_para->uwSize);

	if (ret != OK) {
		HI6402_DSP_ERROR("write mlib para failed\n");
		goto end;
	}

	ret = hi6402_sync_write(param->buf_in, sizeof(MLIB_PARA_SET_REQ_STRU));
	if (ret != OK) {
		HI6402_DSP_ERROR("sync write failed\n");
		goto end;
	}

end:
	if (MLIB_ST_PARA_TRANSACTION == mlib_para_content->key) {
		hi6402_release_low_pll_resource(LOW_FREQ_SCENE_SET_PARA);
	} else {
		hi6402_release_pll_resource(HI_FREQ_SCENE_SET_PARA);
	}

	OUT_FUNCTION;
	return ret;
}

static int hi6402_func_para_get(struct krn_param_io_buf *param)
{
	int ret = OK;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);
	BUG_ON(param->buf_out == NULL);
	BUG_ON(param->buf_size_out == 0);

	if (param->buf_size_out <= RESULT_SIZE) {
		HI6402_DSP_ERROR("not enough space for para get\n");
		return ERROR;
	}

	hi6402_request_pll_resource(HI_FREQ_SCENE_GET_PARA);
	/* send request */
	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("sync write failed\n");
		goto end;
	}

	ret = hi6402_read_mlib_para(param->buf_out + RESULT_SIZE,
				param->buf_size_out - RESULT_SIZE);
	if (ret != OK) {
		HI6402_DSP_ERROR("read para failed\n");
		goto end;
	}

end:
	hi6402_release_pll_resource(HI_FREQ_SCENE_GET_PARA);

	OUT_FUNCTION;

	return ret;
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static int hi6402_func_om(struct krn_param_io_buf *param)
{
	int ret = OK;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	hi6402_request_pll_resource(HI_FREQ_SCENE_OM);

	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("sync write failed\n");
		goto end;
	}

end:
	hi6402_release_pll_resource(HI_FREQ_SCENE_OM);
	OUT_FUNCTION;
	return ret;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */


static int hi6402_func_fasttrans_config(struct krn_param_io_buf *param)
{
	int ret = OK;
	FAST_TRANS_CFG_REQ_STRU* pFastCfg = NULL;

	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	pFastCfg =	(FAST_TRANS_CFG_REQ_STRU*)(param->buf_in);
	HI6402_DSP_INFO("hi6402_func_fasttrans_config [%d]\n", pFastCfg->uhwMsgId);

	if (ID_AP_DSP_FASTTRANS_OPEN == pFastCfg->uhwMsgId) {

		hi6402_hifi_write_reg(0x200072C6, 0x66);/*S2_OL_PGA 192K*/
		hi6402_hifi_write_reg(0x200072C8, 0x11);/*S3_OL_PGA 16K*/

		if ((pFastCfg->swStatus) & 0x1) {
			hi6402_hifi_write_reg(0x200072B0, 0x0C);/*S2_CTRL  48K*/
		} else {
			hi6402_hifi_write_reg(0x200072B0, 0x0E);/*S2_CTRL  192K*/
		}

		hi6402_hifi_write_reg(0x200072B2, 0x09);/*S3_CTRL*/
		hi6402_hifi_write_reg(0x200073FE, 0xFF);/*SLIMBUS INPUT ENABLE*/

	} else {
		hi6402_hifi_write_reg(0x200072C6, 0x00);/*S2_OL_PGA 192K*/
		hi6402_hifi_write_reg(0x200072C8, 0x00);/*S3_OL_PGA 16K*/

		if ((pFastCfg->swStatus) & 0x1) {
			hi6402_hifi_write_reg(0x200072B0, 0x0C);/*S2_CTRL  48K*/
		} else {
			hi6402_hifi_write_reg(0x200072B0, 0x04);/*S2_CTRL  disable*/
		}
		hi6402_hifi_write_reg(0x200072B2, 0x00);
		hi6402_hifi_write_reg(0x200073FE, 0xAA);
	}


	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("sync write failed\n");
		goto end;
	}

end:
	OUT_FUNCTION;
	return ret;
}

/*
 *	dsp img download
 */
static int hi6402_hifi_fw_section_head_check(struct drv_hifi_image_head *img_head,
						 struct drv_hifi_image_sec *img_sec)
{
	/* BSS section do not need check offset and size,
	 * beacuse BSS section only record address and length, the content is 0 */
	if (img_sec->type == DRV_HIFI_IMAGE_SEC_TYPE_BSS
		&& (img_sec->sn < img_head->sections_num)
		&& (img_sec->load_attib < (unsigned char)DRV_HIFI_IMAGE_SEC_LOAD_BUTT))
		return 0;

	/* check section number and section size  */
	if ((img_sec->sn >= img_head->sections_num)
		|| (img_sec->src_offset + img_sec->size > img_head->image_size)
		|| (img_sec->type >= (unsigned char)DRV_HIFI_IMAGE_SEC_TYPE_BUTT)
		|| (img_sec->load_attib >= (unsigned char)DRV_HIFI_IMAGE_SEC_LOAD_BUTT))
	{
		HI6402_DSP_ERROR("hifi: drv_hifi_check_sections ERROR.\n");
		return -1;
	}

	return 0;
}

static int hi6402_hifi_fw_head_check(struct drv_hifi_image_head *head)
{
	int i = 0;
	int ret = 0;

	for (i = 0; i < head->sections_num; i++) {
		/* check the sections */
		ret = hi6402_hifi_fw_section_head_check(head, &(head->sections[i]));

		if (ret != 0) {
			HI6402_DSP_INFO("hifi: Invalid hifi section\n");
			goto exit;
		}
	}

exit:
	return ret;
}

static void hi6402_hifi_download(const struct firmware *fw)
{
	struct drv_hifi_image_head *head = NULL;


	uint32_t *src_addr;
	int dmadownload = 0;
	int i = 0;
	int ret = 0;

	HI6402_DSP_INFO("img down begin, size:[%zu] !\n", fw->size);
	/* load firmware */
	head = (struct drv_hifi_image_head *)fw->data;

	ret = hi6402_hifi_fw_head_check(head);

	if (dmadownload) {
		uint64_t dmabaseaddr = 0;
		uint32_t des_addr;
		uint32_t temp;
		uint32_t timeout = 0;
		uint32_t aspdma[4];
		uint32_t codecdma[4];
		int regval = 0;
		int j = 0;

		if (NULL == priv.src_addr_v) {
			HI6402_DSP_INFO("imgdown dma mem is NULL!\n");
			return;
		}

		/* stop 6402 dma */
		for (i=0; i<16; i++) {
			hi6402_hifi_reg_clr_bit(HI6402_CX_CONFIG+i*HI6402_DMA_CONFIG_OFFSET, 0);
			regval = hi6402_hifi_read_reg(HI6402_CX_CONFIG+i*HI6402_DMA_CONFIG_OFFSET);
			if (regval & 0x1) {
				HI6402_DSP_ERROR("dma:%d regval:%#x, dma not stop!\n", i, regval);
			}
		}

		/* stop 6402 dspif */
		hi6402_hifi_write_reg(HI6402_DSP_I2S_DSPIF_CLK_EN, 0x0);
		/* disable RX, TX */
		hi6402_hifi_reg_write_bits(HI6402_SC_S4_IF_L, 0x0, 0x3);
		/* disable i2s4 clk */
		hi6402_hifi_reg_clr_bit(HI6402_SC_FS_S4_CTRL_L, 3);
		hi6402_hifi_reg_write_bits(HI6402_AUD_CLK_EN, 0x3, 0x3);
		/* slibus i2s mux */
		hi6402_hifi_write_reg(HI6402_SC_CODEC_MUX_SEL3_0, 0xff);
		hi6402_hifi_reg_write_bits(HI6402_SC_FS_SELC_TRL, 0xc0, 0xc0);
		/* dsp if6 clk enable*/
		hi6402_hifi_reg_set_bit(HI6402_DSP_I2S_DSPIF_CLK_EN,6);
		hi6402_hifi_reg_set_bit(HI6402_CODEC_DP_CLKEN, 0);
		hi6402_hifi_reg_set_bit(HI6402_SLIM_CTRL1, 0);

		slimbus_bus_configure(SLIMBUS_BUS_CONFIG_IMGDOWN);
		slimbus_track_configure(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_IMAGE_LOAD, NULL);

		dmabaseaddr = (uint64_t)ioremap(ASP_DMAC_BASE_ADDR, ASP_DMAC_SIZE);

		if (!dmabaseaddr) {
			HI6402_DSP_INFO("asp dmac base addr remap error\n");
			return;
		}

		for (i = 0; i < head->sections_num; i++) {
			src_addr = (unsigned int *)((char *)head + head->sections[i].src_offset);
			des_addr = head->sections[i].des_addr;

			if (head->sections[i].size > IMAGEDOWN_SIZE_THRESH) {
				uint32_t pagesize = 25600;
				uint32_t pagenum = head->sections[i].size/pagesize;
				uint32_t pageextra = head->sections[i].size%pagesize;
				uint32_t dmawidth = 16;
				uint32_t curpos = 0;
				uint32_t cursize = 0;
				uint32_t bytesleft = pageextra%dmawidth;
				uint32_t dmanum = 6;
				uint32_t aspdmanum = 10;

				if (head->sections[i].type != DRV_HIFI_IMAGE_SEC_TYPE_BSS) {
					memset(priv.src_addr_v, 0, head->sections[i].size*2);
					if(head->sections[i].type != DRV_HIFI_IMAGE_SEC_TYPE_BSS) {
						for (j=0; j<head->sections[i].size/4; j++) {
							temp = src_addr[j];
							priv.src_addr_v[2*j] = (temp&0x0000ffff)<<16;
							priv.src_addr_v[2*j+1] = temp&0xffff0000;
						}
					}

					for (j=0; j<(pagenum+1); j++) {
						if (j<pagenum) {
							curpos	= pagesize*j;
							cursize = pagesize;
						} else if (j==pagenum) {
							curpos	= pagesize*j;
							cursize = pageextra-bytesleft;
						} else {
							HI6402_DSP_INFO(" error!\n");
						}

						/* 6402 dma */
						hi6402_hifi_write_reg(HI6402_CX_CNT0+dmanum*HI6402_DMA_CONFIG_OFFSET, cursize);
						hi6402_hifi_write_reg(HI6402_CX_SRC_ADDR+dmanum*HI6402_DMA_CONFIG_OFFSET, HI6402_DSP_IF6_ADDR);
						hi6402_hifi_write_reg(HI6402_CX_DES_ADDR+dmanum*HI6402_DMA_CONFIG_OFFSET, des_addr+curpos);
						hi6402_hifi_write_reg(HI6402_CX_CONFIG+dmanum*HI6402_DMA_CONFIG_OFFSET, 0x477110c7);
						usleep_range(1000, 1050);

						/* asp dma */
						writel(cursize*2, (void __iomem *)(dmabaseaddr + ASP_DMAC_CX_CNT0 + aspdmanum*ASP_DMAC_CONFIG_OFFSET));
						writel(priv.src_dma_addr+curpos*2, (void __iomem *)(dmabaseaddr + ASP_DMAC_CX_SRC_ADDR + aspdmanum*ASP_DMAC_CONFIG_OFFSET));
						writel(SLIMBUS_PORT12_ADDR, (void __iomem *)(dmabaseaddr + ASP_DMAC_CX_DES_ADDR + aspdmanum*ASP_DMAC_CONFIG_OFFSET));
						writel(0x833220c7, (void __iomem *)(dmabaseaddr + ASP_DMAC_CX_CONFIG + aspdmanum*ASP_DMAC_CONFIG_OFFSET));
						slimbus_track_activate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_IMAGE_LOAD);

						timeout = 0;
						do {
							usleep_range(100, 150);
							aspdma[3]  = readl((void __iomem *)(dmabaseaddr + ASP_DMAC_CX_CONFIG + aspdmanum*ASP_DMAC_CONFIG_OFFSET));
							codecdma[3] = hi6402_hifi_read_reg(HI6402_CX_CONFIG+dmanum*HI6402_DMA_CONFIG_OFFSET);

							if (timeout++ > 1000) {
								aspdma[0] = readl((void __iomem *)(dmabaseaddr + ASP_DMAC_CX_CURR_CNT0 + aspdmanum*ASP_DMAC_STATUS_OFFSET));
								codecdma[1] = hi6402_hifi_read_reg(HI6402_CX_CURR_CNT0+dmanum*HI6402_DMA_STATUS_OFFSET);
								codecdma[2] = hi6402_hifi_read_reg(HI6402_CX_CURR_DES_ADDR+dmanum*HI6402_DMA_STATUS_OFFSET);

								HI6402_DSP_INFO("timeout! aspdma:%x, %x; 6402 dma:%x, %x, %x, -----\n",
									aspdma[0], aspdma[3], codecdma[1], codecdma[2], codecdma[3]);

								hi6402_hifi_write_reg(HI6402_CX_CONFIG+dmanum*HI6402_DMA_CONFIG_OFFSET, 0x477110c6);
								writel(0x833220c6, (void __iomem *)(dmabaseaddr + ASP_DMAC_CX_CONFIG + aspdmanum*ASP_DMAC_CONFIG_OFFSET));
								break;
							}
						} while ((aspdma[3]&0x1) || (codecdma[3]&0x1));

						slimbus_track_deactivate(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_IMAGE_LOAD);
					}
				} else {
					dmanum = 0;
					hi6402_hifi_write_reg(des_addr, 0x0);

					for (j=0; j<(pagenum+1); j++) {
						if (j<pagenum) {
							curpos	= pagesize*j;
							cursize = pagesize;
						} else if (j==pagenum) {
							curpos	= pagesize*j;
							cursize = pageextra-bytesleft;
						} else {
							HI6402_DSP_INFO(" error !\n");
						}

						/* 6402 dma buffer->buffer*/
						hi6402_hifi_write_reg(HI6402_CX_CNT0+dmanum*HI6402_DMA_CONFIG_OFFSET, cursize);
						hi6402_hifi_write_reg(HI6402_CX_SRC_ADDR+dmanum*HI6402_DMA_CONFIG_OFFSET, des_addr);
						hi6402_hifi_write_reg(HI6402_CX_DES_ADDR+dmanum*HI6402_DMA_CONFIG_OFFSET, des_addr+curpos+4);
						hi6402_hifi_write_reg(HI6402_CX_CONFIG+dmanum*HI6402_DMA_CONFIG_OFFSET, 0x47722003);

						timeout = 0;
						do {
							codecdma[3] = hi6402_hifi_read_reg(HI6402_CX_CONFIG+dmanum*HI6402_DMA_CONFIG_OFFSET);
							if (timeout++ > 100) {
								codecdma[1] = hi6402_hifi_read_reg(HI6402_CX_CURR_CNT0+dmanum*HI6402_DMA_STATUS_OFFSET);
								codecdma[2] = hi6402_hifi_read_reg(HI6402_CX_CURR_DES_ADDR+dmanum*HI6402_DMA_STATUS_OFFSET);
								HI6402_DSP_INFO("timeout! 6402 dma:%x, %x, %x, -----\n", codecdma[1], codecdma[2], codecdma[3]);
								break;
							}
						} while (codecdma[3]&0x1);
					}
				}

				if (bytesleft) {
					curpos += (pageextra-bytesleft);
					des_addr += curpos;
					src_addr += curpos/4;

					if(head->sections[i].type == DRV_HIFI_IMAGE_SEC_TYPE_BSS) {
						for(j = 0; j < bytesleft; j = j + 4) {
							/* copy the sections */
							hi6402_hifi_write_reg(des_addr, 0x0);
							src_addr++;
							des_addr += 4;
						}
					} else {
						for(j = 0; j < bytesleft; j = j + 4) {
							/* copy the sections */
							hi6402_hifi_write_reg(des_addr, *(src_addr));
							src_addr++;
							des_addr += 4;
						}
					}
				}
			} else {
				if(head->sections[i].type == DRV_HIFI_IMAGE_SEC_TYPE_BSS) {
					for(j = 0; j < head->sections[i].size; j = j + 4) {
						/* copy the sections */
						hi6402_hifi_write_reg(des_addr, 0x0);
						des_addr += 4;
					}
				} else {
					for(j = 0; j < head->sections[i].size; j = j + 4) {
						/* copy the sections */
						hi6402_hifi_write_reg(des_addr, *(src_addr));
						src_addr++;
						des_addr += 4;
					}
				}
			}
		}

		iounmap((void __iomem *)dmabaseaddr);
		slimbus_track_remove(SLIMBUS_DEVICE_HI6402, SLIMBUS_TRACK_IMAGE_LOAD);
		slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
		hi6402_hifi_reg_clr_bit(HI6402_DSP_I2S_DSPIF_CLK_EN, 6);
		hi6402_hifi_reg_clr_bit(HI6402_SLIM_CTRL1, 0);
		hi6402_hifi_write_reg(HI6402_SC_CODEC_MUX_SEL3_0, 0x33);
		hi6402_hifi_reg_write_bits(HI6402_SC_FS_SELC_TRL, 0x0, 0xc0);
	} else {
		slimbus_bus_configure(SLIMBUS_BUS_CONFIG_REGIMGDOWN);
		for (i = 0; i < head->sections_num; i++) {
			unsigned int des_addr;
			unsigned int *src_addr;
			int j = 0;

			src_addr = (unsigned int *)((char *)head + head->sections[i].src_offset);
			des_addr = head->sections[i].des_addr;

			/*HI6402_DSP_DEBUG("hifi: sections_num = %d,des_addr = 0x%x, load_attib = %d, size = 0x%x,"
					 " sn = %d, src_offset = 0x%x, type = %d\n", \
					 head->sections_num,\
					 head->sections[i].des_addr,\
					 head->sections[i].load_attib,\
					 head->sections[i].size,\
					 head->sections[i].sn,\
					 head->sections[i].src_offset,\
					 head->sections[i].type);

			HI6402_DSP_INFO("[0x%p]->[0x%x] [0x%x]", src_addr, des_addr, *src_addr);*/
			if (head->sections[i].type == DRV_HIFI_IMAGE_SEC_TYPE_BSS) {
				for(j = 0; j < head->sections[i].size; j = j + 4) {
					/* copy the sections */
					hi6402_hifi_write_reg(des_addr, 0x0);
					des_addr += 4;
				}
			} else {
				for(j = 0; j < head->sections[i].size; j = j + 4) {
					/* copy the sections */
					hi6402_hifi_write_reg(des_addr, *(src_addr));
					src_addr++;
					des_addr += 4;
				}
			}
		}
		slimbus_bus_configure(SLIMBUS_BUS_CONFIG_NORMAL);
	}

	HI6402_DSP_INFO("img down end !\n");
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static void hi6402_reset_codec(void)
{
	unsigned int* addr_gpio = NULL;
	unsigned int* addr_gpio_dir = NULL;

	addr_gpio = (unsigned int*)ioremap_wc(SOC_GPIO_ADDR, 0x4);

	if (NULL == addr_gpio) {
		HI6402_DSP_INFO("HI6402 RESET GPIO ADDR REMAP ERROR\n");
		return;
	}

	addr_gpio_dir = (unsigned int*)ioremap_wc(SOC_GPIO_DIR_ADDR, 0x4);

	if (NULL == addr_gpio_dir) {
		iounmap(addr_gpio);
		HI6402_DSP_INFO("HI6402 RESET GPIO DIR ADDR REMAP ERROR\n");
		return;
	}

	*(unsigned int *)(addr_gpio_dir) = 0x02;
	*(unsigned int *)(addr_gpio) = 0x5a;
	mdelay(100);
	*(unsigned int *)(addr_gpio) = 0x58;
	mdelay(100);
	*(unsigned int *)(addr_gpio) = 0x5a;

	iounmap(addr_gpio);
	iounmap(addr_gpio_dir);
}

static int hi6402_fw_download(void)
{
	int ret = 0;
	const struct firmware *fw = NULL;
	/* download dsp image */
	ret = request_firmware(&fw, "hifi_6402.img", priv.dev);
	if (ret != 0) {
		dev_err(priv.dev, "Failed to request application(%s): %d\n",
			"hifi_6402.img", ret);
		return ret;
	}
	BUG_ON(fw == NULL);
	hi6402_ram2axi_cfg_with_hifi(true);
	hi6402_hifi_download(fw);
	release_firmware(fw);

	return ret;
}

static int hi6402_func_uartmode(struct krn_param_io_buf *param)
{
	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	priv.uart_mode = ((UARTMODE_STRU *)(param->buf_in))->uwUartMode;

	return OK;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

static void release_requested_pll(void)
{
	int i = 0;

	for(i = 0; i < HI_FREQ_SCENE_BUTT; i++) {
		hi6402_release_pll_resource(i);
	}

	for(i = 0; i < LOW_FREQ_SCENE_BUTT; i++) {
		hi6402_release_low_pll_resource(i);
	}

}

static int hi6402_func_fw_download(struct krn_param_io_buf *param)
{
	char *fw_name = NULL;
	const struct firmware *fw = NULL;
	FW_DOWNLOAD_STRU *dsp_fw_download = NULL;

	int ret = 0;
	int i = 0;

	IN_FUNCTION;

	/* request dsp firmware */
	BUG_ON(param == NULL);
	dsp_fw_download = (FW_DOWNLOAD_STRU *)(param->buf_in);

	BUG_ON(dsp_fw_download == NULL);
	fw_name = dsp_fw_download->chwname;

	ret = request_firmware(&fw, fw_name, priv.dev);
	if (ret != 0) {
		dev_err(priv.dev, "Failed to request dsp image(%s): %d\n", fw_name, ret);
		return ret;
	}
	BUG_ON(fw == NULL);

	/* release all requeseted PLL first beacuse 6402 maybe request PLL but didn't release when exception */
	release_requested_pll();
	hi6402_hifi_set_pll(true);

	/* restore dsp_if work status */
	for(i = 0; i < HI6402_HIFI_DSP_IF_PORT_BUTT;i++) {
		hi6402_dsp_if_set_bypass(i,true);
	}
	hi6402_hifi_runstall_cfg(false);
	hi6402_hifi_deinit();
	hi6402_hifi_init();
	/* MAD set param */
	hi6402_mad_set_param();
	hi6402_hifi_clk_enable(true);
	hi6402_ram2axi_cfg_with_hifi(true);

	/* set 6402 dsp uart Baud rate before power up dsp */
	hi6402_hifi_write_reg(HI6402_UART_MODE, priv.uart_mode);

	/* download dsp image */
	hi6402_hifi_download(fw);
	release_firmware(fw);

	/* notify dsp pwr on */
	hi6402_hifi_write_reg(HI6402_DSP_CMD0, HIFI_POWER_ON);
	priv.dsp_pwron_done = HIFI_STATE_UNINIT;

	/* irq clr,unmask*/
	if (hi6402_hifi_read_reg(0x20007016)&0x1) {
		hi6402_hifi_write_reg(0x20007016, 0x1);
	}
	hi6402_hifi_reg_clr_bit(0x20007019, 0x0);

	hi6402_hifi_runstall_cfg(true);
	/*wait 3s for dsp power on */
	/* todo : add a new wq */
	if (wait_event_interruptible_timeout(priv.dsp_pwron_wq,
		(priv.dsp_pwron_done == HIFI_STATE_INIT), (3*HZ)) == 0) {
		unsigned int read_res[6];

		HI6402_DSP_ERROR("wait for dsp pwron timeout\n");
		read_res[0] = hi6402_hifi_read_reg(0x20007014);
		read_res[1] = hi6402_hifi_read_reg(0x20007015);
		read_res[2] = hi6402_hifi_read_reg(0x20007016);
		read_res[3] = hi6402_hifi_read_reg(0x20007017);
		read_res[4] = hi6402_hifi_read_reg(0x20007018);
		read_res[5] = hi6402_hifi_read_reg(0x20007019);
		HI6402_DSP_ERROR("14:%#x, 15:%#x, 16:%#x, 17:%#x, 18:%#x, 19:%#x\n",read_res[0],read_res[1],read_res[2],read_res[3],read_res[4],read_res[5]);
	}
	msleep(1);
	hi6402_ram2axi_cfg_with_hifi(false);
	hi6402_hifi_clk_enable(false);
	hi6402_hifi_set_pll(false);

	OUT_FUNCTION;
	return ret;
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static int hi6402_func_mad_test_start(struct krn_param_io_buf *param)
{
	int ret = OK;
	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	ret = hi6402_request_pll_resource(HI_FREQ_SCENE_MAD_TEST);
	if (ret != OK) {
		goto end;
	}

	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("sync write failed\n");
		hi6402_release_pll_resource(HI_FREQ_SCENE_MAD_TEST);
		goto end;
	}

end:
	OUT_FUNCTION;

	return ret;
}

static int hi6402_func_mad_test_stop(struct krn_param_io_buf *param)
{
	int ret = OK;
	IN_FUNCTION;

	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if ((priv.high_freq_scene_status & (1 << HI_FREQ_SCENE_MAD_TEST)) == 0) {
		HI6402_DSP_ERROR("scene mad test is NOT opened.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("sync write failed\n");
	}

	hi6402_release_pll_resource(HI_FREQ_SCENE_MAD_TEST);
end:
	OUT_FUNCTION;
	return ret;
}

static int hi6402_func_wakeup_test(struct krn_param_io_buf *param)
{
	int ret = OK;
	IN_FUNCTION;
	BUG_ON(param == NULL);
	BUG_ON(param->buf_in == NULL);
	BUG_ON(param->buf_size_in == 0);

	if ((priv.low_freq_scene_status & (1 << LOW_FREQ_SCENE_WAKE_UP)) == 0) {
		HI6402_DSP_INFO("scene wakeup is NOT opened, status:%d.\n", priv.low_freq_scene_status);
		ret = ERROR;
		goto end;
	}

	ret = hi6402_sync_write(param->buf_in, param->buf_size_in);
	if (ret != OK)
		HI6402_DSP_ERROR("sync write failed, ret:%d.\n", ret);

end:
	OUT_FUNCTION;
	return ret;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

static cmd_process_func hi6402_select_func(const unsigned char *arg,
					   const struct cmd_func_pair *func_map,
					   const unsigned int func_map_size)
{
	unsigned int i = 0;
	unsigned short msg_id;

	BUG_ON(arg == NULL);

	msg_id = *(unsigned short*)arg;

	IN_FUNCTION;
	for (i = 0; i < func_map_size; i++) {
		if (func_map[i].cmd_id == msg_id) {
			HI6402_DSP_INFO("cmd:%s\n", func_map[i].cmd_name);
			return func_map[i].func;
		}
	}

	HI6402_DSP_ERROR("cmd_process_func for id:%d not found!\n", msg_id);

	OUT_FUNCTION;
	return (cmd_process_func)NULL;
}

/* not sure whether async commond would be used in future */
#if 0
static struct cmd_func_pair async_cmd_func_map[] = {
};

static int hi6402_hifi_async_cmd(unsigned long arg)
{
	int ret = OK;
	cmd_process_func func = NULL;
	struct misc_io_async_param param;
	struct krn_param_io_buf krn_param;

	memset(&param, 0, sizeof(param));
	memset(&krn_param, 0, sizeof(krn_param));

	IN_FUNCTION;

	//FIXME: should check arg not be NULL?
	if (copy_from_user(&param, (void*)arg,
			sizeof(struct misc_io_async_param))) {
		HI6402_DSP_ERROR("copy_from_user fail.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi6402_get_input_param(param.para_size_in,
			INT_TO_ADDR(param.para_in_l, param.para_in_h),
			&krn_param.buf_size_in,
			(void **)&krn_param.buf_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("get_input_param ret=%d\n", ret);
		goto end;
	}

	func = hi6402_select_func(krn_param.buf_in, async_cmd_func_map,
				  ARRAY_SIZE(async_cmd_func_map));
	if (func == NULL) {
		HI6402_DSP_ERROR("select_func error.\n");
		ret = ERROR;
		goto end;
	}

	ret = func(&krn_param);
	if (ret != OK) {
		HI6402_DSP_ERROR("func process error.\n");
		goto end;
	}

end:
	hi6402_param_free((void **)&krn_param.buf_in);

	OUT_FUNCTION;

	return ret;
}
#endif

static struct cmd_func_pair sync_cmd_func_map[] = {
	{ ID_AP_DSP_IF_OPEN,		 hi6402_func_if_open,		 "ID_AP_DSP_IF_OPEN"	   },
	{ ID_AP_DSP_IF_CLOSE,		 hi6402_func_if_close,		 "ID_AP_DSP_IF_CLOSE"	   },
	{ ID_AP_DSP_PARAMETER_SET,	 hi6402_func_para_set,		 "ID_AP_DSP_PARAMETER_SET" },
	{ ID_AP_DSP_PARAMETER_GET,	 hi6402_func_para_get,		 "ID_AP_DSP_PARAMETER_GET" },
	{ ID_AP_DSP_FASTMODE,		 hi6402_func_fastmode,		 "ID_AP_DSP_FASTMODE"	   },
	{ ID_AP_IMGAE_DOWNLOAD, 	 hi6402_func_fw_download,	 "ID_AP_IMGAE_DOWNLOAD"    },
	{ ID_AP_DSP_FASTTRANS_OPEN,  hi6402_func_fasttrans_config, "ID_AP_DSP_FASTTRANS_OPEN"},
	{ ID_AP_DSP_FASTTRANS_CLOSE, hi6402_func_fasttrans_config, "ID_AP_DSP_FASTTRANS_CLOSE"},
#ifdef ENABLE_HI6402_HIFI_DEBUG
	{ ID_AP_DSP_UARTMODE,		 hi6402_func_uartmode,		 "ID_AP_DSP_UARTMODE"	   },
	{ ID_AP_DSP_OM,			 hi6402_func_om,		"ID_AP_DSP_OM"		  },
	{ ID_AP_DSP_MADTEST_START,	 hi6402_func_mad_test_start,	"ID_AP_DSP_MADTEST_START" },
	{ ID_AP_DSP_MADTEST_STOP,	 hi6402_func_mad_test_stop,	"ID_AP_DSP_MADTEST_STOP"  },
	{ ID_AP_DSP_WAKEUP_TEST,	 hi6402_func_wakeup_test,	"ID_AP_DSP_WAKEUP_TEST"   },
#endif
};

#ifdef ENABLE_HI6402_HIFI_DEBUG
static int hi6402_hifi_read_msg_cmd(unsigned long arg)
{
	int ret = OK;
	struct misc_io_sync_param param;
	struct krn_param_io_buf krn_param;
	unsigned short msg_id = 0;
	int len = 0;
	IN_FUNCTION;

	memset(&param, 0, sizeof(param));
	memset(&krn_param, 0, sizeof(krn_param));

	if (copy_from_user(&param, (void __user *)arg,
		sizeof(struct misc_io_sync_param))) {
		HI6402_DSP_ERROR("copy_from_user fail.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi6402_alloc_output_param_buffer(param.para_size_out,
		INT_TO_ADDR(param.para_out_l, param.para_out_h),
		&krn_param.buf_size_out,
		(void **)&krn_param.buf_out);

	if (ret != OK) {
		HI6402_DSP_ERROR("alloc output buffer failed.\n");
		goto end;
	}

	ret = hi6402_get_input_param(param.para_size_in,
		INT_TO_ADDR(param.para_in_l, param.para_in_h),
		&krn_param.buf_size_in,
		(void **)&krn_param.buf_in);

	if (ret != OK) {
		HI6402_DSP_ERROR("get_input_param ret=%d\n", ret);
		goto end;
	}

	msg_id = *(unsigned short*)krn_param.buf_in;
	if ((msg_id != ID_AP_IMGAE_DOWNLOAD && msg_id != ID_AP_DSP_UARTMODE)
		&& priv.dsp_pwron_done == HIFI_STATE_UNINIT) {
		HI6402_DSP_ERROR("6402 firmware not load!!cmd[%d] not send!!\n",msg_id);
		goto end;
	}

	len = hi6402_read_mlib_test_para(krn_param.buf_out, krn_param.buf_size_out);
	krn_param.buf_size_out = len;
	param.para_size_out = krn_param.buf_size_out;

	/* copy result to user space */
	ret = hi6402_put_output_param(param.para_size_out,
			INT_TO_ADDR(param.para_out_l, param.para_out_h),
			krn_param.buf_size_out,
			(void *)krn_param.buf_out);

	if (ret != OK) {
		HI6402_DSP_ERROR("copy result to user failed\n");
		goto end;
	}

	ret = len;
end:
	hi6402_param_free((void **)&krn_param.buf_in);
	hi6402_param_free((void **)&krn_param.buf_out);

	OUT_FUNCTION;
	return ret;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

static int hi6402_hifi_sync_cmd(unsigned long arg)
{
	int ret = OK;
	cmd_process_func func = NULL;
	struct misc_io_sync_param param;
	struct krn_param_io_buf krn_param;
	unsigned short msg_id = 0;

	IN_FUNCTION;

	memset(&param, 0, sizeof(param));
	memset(&krn_param, 0, sizeof(krn_param));

	if (copy_from_user(&param, (void __user *)arg,
			   sizeof(struct misc_io_sync_param))) {
		HI6402_DSP_ERROR("copy_from_user fail.\n");
		ret = ERROR;
		goto end;
	}

	ret = hi6402_alloc_output_param_buffer(param.para_size_out,
			INT_TO_ADDR(param.para_out_l, param.para_out_h),
			&krn_param.buf_size_out,
			(void **)&krn_param.buf_out);
	if (ret != OK) {
		HI6402_DSP_ERROR("alloc output buffer failed.\n");
		goto end;
	}

	ret = hi6402_get_input_param(param.para_size_in,
			INT_TO_ADDR(param.para_in_l, param.para_in_h),
			&krn_param.buf_size_in,
			(void **)&krn_param.buf_in);
	if (ret != OK) {
		HI6402_DSP_ERROR("get_input_param ret=%d\n", ret);
		goto end;
	}

	msg_id = *(unsigned short*)krn_param.buf_in;
	if ((msg_id != ID_AP_IMGAE_DOWNLOAD && msg_id != ID_AP_DSP_UARTMODE)
		&& priv.dsp_pwron_done == HIFI_STATE_UNINIT) {
		HI6402_DSP_ERROR("6402 firmware not load,cmd:%d not send\n", msg_id);
		goto end;
	}

	func = hi6402_select_func(krn_param.buf_in, sync_cmd_func_map,
				  ARRAY_SIZE(sync_cmd_func_map));
	if (func == NULL) {
		HI6402_DSP_ERROR("select_func error.\n");
		ret = ERROR;
		goto end;
	}

	ret = func(&krn_param);
	if (ret != OK) {
		/* don't print err if redundant cmd was received */
		if (ret != REDUNDANT) {
			HI6402_DSP_ERROR("func process error.\n");
		}
		goto end;
	}

	/* write result to out buf */
	BUG_ON(krn_param.buf_out == NULL);
	if (krn_param.buf_size_out >= sizeof(int)) {
		*(int *)krn_param.buf_out = ret;
	} else {
		HI6402_DSP_ERROR("not enough space to save result\n");
		goto end;
	}

	/* copy result to user space */
	ret = hi6402_put_output_param(param.para_size_out,
			INT_TO_ADDR(param.para_out_l, param.para_out_h),
			krn_param.buf_size_out,
			(void *)krn_param.buf_out);
	if (ret != OK) {
		HI6402_DSP_ERROR("copy result to user failed\n");
		goto end;
	}

end:
	hi6402_param_free((void **)&krn_param.buf_in);
	hi6402_param_free((void **)&krn_param.buf_out);

	OUT_FUNCTION;

	return ret;
}

/*****************************************************************************
 * misc driver
 * */
static int hi6402_hifi_misc_open(struct inode *finode, struct file *fd)
{
	return 0;
}

static int hi6402_hifi_misc_release(struct inode *finode, struct file *fd)
{
	return 0;
}

static long hi6402_hifi_misc_ioctl(struct file *fd,
                                   unsigned int cmd,
                                   unsigned long arg)
{
	int ret = 0;

	IN_FUNCTION;

	if (NULL == (void __user *)arg) {
		HI6402_DSP_ERROR("input error: arg is NULL\n");
		return -EINVAL;
	}

	switch(cmd) {
/* not sure whether async commond would be used in future */
#if 0
		case HI6402_HIFI_MISC_IOCTL_ASYNCMSG:
			HI6402_DSP_DEBUG("ioctl: HIFI_MISC_IOCTL_ASYNCMSG\n");
			mutex_lock(&priv.msg_mutex);
			ret = hi6402_hifi_async_cmd(arg);
			mutex_unlock(&priv.msg_mutex);
			break;
#endif
		case HI6402_HIFI_MISC_IOCTL_SYNCMSG:
			HI6402_DSP_DEBUG("ioctl: HIFI_MISC_IOCTL_SYNCMSG\n");
			mutex_lock(&priv.msg_mutex);
			ret = hi6402_hifi_sync_cmd(arg);
			mutex_unlock(&priv.msg_mutex);
			break;
#ifdef ENABLE_HI6402_HIFI_DEBUG
		case HI6402_HIFI_MISC_IOCTL_MLIB_TEST_MSG:
			HI6402_DSP_DEBUG("ioctl: HI6402_HIFI_MISC_IOCTL_MLIB_TEST_MSG\n");
			mutex_lock(&priv.msg_mutex);
			ret = hi6402_hifi_read_msg_cmd(arg);
			mutex_unlock(&priv.msg_mutex);
			break;
#endif
		default:
			HI6402_DSP_ERROR("ioctl: Invalid CMD =0x%x\n", cmd);
			//TODO: should return a meaningful value
			ret = -1;
			break;
	}

	OUT_FUNCTION;

	return (long)ret;
}

static long hi6402_hifi_misc_ioctl32(struct file *fd,
                                   unsigned int cmd,
                                   unsigned long arg)
{
	void __user *user_ptr = (void __user *)compat_ptr(arg);

	return hi6402_hifi_misc_ioctl(fd, cmd, (unsigned long)user_ptr);
}

#ifdef ENABLE_HI6402_HIFI_DEBUG
static ssize_t hi6402_hifi_misc_read(struct file *file, char __user *buf,
                                     size_t nbytes, loff_t *pos)
{
	struct reg_rw_struct kern_buf;

	if (NULL == buf) {
		HI6402_DSP_ERROR("input error: buf is NULL\n");
		return -EFAULT;
	}

	if (nbytes != sizeof(kern_buf)) {
		HI6402_DSP_ERROR("nbytes:%zu from user space exceed" \
			"sizeof(kern_buf):%zu\n", nbytes, sizeof(kern_buf));
		return -EFAULT;
	}

	if (copy_from_user(&kern_buf, buf, nbytes)) {
		HI6402_DSP_ERROR("copy_from_user fail.\n");
		return -EFAULT;
	}

	kern_buf.val = hi6402_hifi_read_reg(kern_buf.reg);
	if (copy_to_user(buf, &kern_buf, nbytes)) {
		HI6402_DSP_ERROR("copy_to_user fail.\n");
		return -EFAULT;
	}

	return sizeof(kern_buf);
}

static ssize_t hi6402_hifi_misc_write(struct file *file,
				      const char __user *buf,
				      size_t nbytes, loff_t *pos)
{
	struct reg_rw_struct kern_buf;

	if (NULL == buf) {
		HI6402_DSP_ERROR("input error: buf is NULL\n");
		return -EFAULT;
	}

	if (nbytes != sizeof(kern_buf)) {
		HI6402_DSP_ERROR("nbytes:%zu from user space exceed" \
			"sizeof(kern_buf):%zu\n", nbytes, sizeof(kern_buf));
		return -EFAULT;
	}

	if (copy_from_user(&kern_buf, buf, nbytes)) {
		HI6402_DSP_ERROR("copy_from_user fail.\n");
		return -EFAULT;
	}

	hi6402_hifi_write_reg(kern_buf.reg, kern_buf.val);

	return sizeof(kern_buf);
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

static const struct file_operations hi6402_hifi_misc_fops = {
	.owner			= THIS_MODULE,
	.open			= hi6402_hifi_misc_open,
	.release		= hi6402_hifi_misc_release,
#ifdef ENABLE_HI6402_HIFI_DEBUG
	.read			= hi6402_hifi_misc_read,
	.write			= hi6402_hifi_misc_write,
#endif /* ENABLE_HI6402_HIFI_DEBUG */
	.unlocked_ioctl 	= hi6402_hifi_misc_ioctl,
#ifdef CONFIG_COMPAT
	.compat_ioctl 		= hi6402_hifi_misc_ioctl32,
#endif
};

static struct miscdevice hi6402_hifi_misc_device = {
	.minor	= MISC_DYNAMIC_MINOR,
	.name	= "hi6402_hifi_misc",
	.fops	= &hi6402_hifi_misc_fops,
};

#ifdef ENABLE_HI6402_HIFI_DEBUG
static void hi6402_hifi_enable_jtag(void)
{
	hi6402_hifi_write_reg(HI6402_DSP_IOS_IOM_I2S2_SDO, 0x1c4);
	hi6402_hifi_reg_set_bit(HI6402_DSP_IOS_AF_CTRL0, 0);
	hi6402_hifi_reg_clr_bit(HI6402_DSP_IOSHARE_BASE, 5);
}

static void hi6402_hifi_enable_uart(void)
{
	/* enable jtag and uart should set in dsp just for test*/
	hi6402_hifi_write_reg(HI6402_DSP_IOS_IOM_UART_TXD, 0x1c4);
	hi6402_hifi_reg_set_bit(HI6402_DSP_IOSHARE_BASE, 12);
}

/* ********************************************************************
 * sysfs device, for debugging
 * ********************************************************************/
static ssize_t hi6402_debug_show(struct file *file, char __user *buf,
				size_t size, loff_t *data)
{
	loff_t ppos = 0;
	char *help_info = "1 : pwron \n2 : pwroff  \n3 : run \n4 : stop \n"
			  "5 : jtag \n6 : uart\n7 : enable pll\n"
			  "8 : disable pll\n0 : download\n";

	if (NULL == buf) {
		HI6402_DSP_ERROR("input error: buf is NULL\n");
		return -EINVAL;
	}

	return simple_read_from_buffer(buf, PAGE_SIZE, &ppos, help_info, strlen(help_info));
}

static ssize_t hi6402_debug_store(struct file *file, const char __user *buf,
				size_t size, loff_t *data)
{
	unsigned long cmd = 0;
	unsigned int* addr;
	ssize_t ret;
	char level_str[MAX_STR_LEN] = {0};
	loff_t pos = 0;

	if (buf == NULL) {
		HI6402_DSP_ERROR("buf is NULL\n");
		return -EINVAL;
	}

	ret = simple_write_to_buffer(level_str, MAX_STR_LEN - 1 , &pos, buf, size);
	if (ret != size) {
		HI6402_DSP_ERROR("Input param buf read error, return value: %zd\n", ret);
		return -EINVAL;
	}

	if (strict_strtoul(level_str, 0, &cmd) != 0) {
		HI6402_DSP_ERROR("input para is error\n");
		return -EINVAL;
	}

	switch (cmd) {
	case HI6402_HIFI_IMG_DOWNLOAD:
		hi6402_fw_download();
		break;
	case HI6402_HIFI_INIT:
		hi6402_hifi_init();
		break;
	case HI6402_HIFI_DEINIT:
		hi6402_hifi_deinit();
		break;
	case HI6402_HIFI_RUNSTALL_PULL_DOWN:
		hi6402_hifi_runstall_cfg(true);
		break;
	case HI6402_HIFI_RUNSTALL_PULL_UP:
		hi6402_hifi_runstall_cfg(false);
		break;
	case HI6402_HIFI_JTAG_ENABLE:
		hi6402_hifi_enable_jtag();
		break;
	case HI6402_HIFI_UART_ENABLE:
		hi6402_hifi_enable_uart();
		break;
	case HI6402_HIFI_HIPLL_ENABLE:
		hi6402_hifi_set_pll(true);
		break;
	case HI6402_HIFI_HIPLL_DIAABLE:
		hi6402_hifi_set_pll(false);
		break;
	case HI6402_HIFI_LOWPLL_ENABLE:
		hi6402_hifi_set_low_pll(true);
		break;
	case HI6402_HIFI_LOWPLL_DIAABLE:
		hi6402_hifi_set_low_pll(false);
		break;
	/* this case just for assic and FPGA test */
	case HI6402_HIFI_FPGA_CODEC_RESET:
		hi6402_reset_codec();
		break;
	case HI6402_HIFI_FPGA_PWRON_TEST:
		hi6402_hifi_runstall_cfg(false);
		hi6402_hifi_deinit();
		hi6402_hifi_init();
		hi6402_fw_download();
		hi6402_hifi_runstall_cfg(true);
		break;
	/* this case just for om set GPIO */
	case HI6402_HIFI_FPGA_OM_TEST:
		addr = (unsigned int*)ioremap_wc(HI6402_HIFI_FPGA_OM_TEST_ADDR, 0x4);

		if (NULL == addr) {
			HI6402_DSP_INFO("HI6402_HIFI_FPGA_OM_TEST ADDR REMAP ERROR\n");
			return -EINVAL;
		}

		*(unsigned int *)(addr) = 0x2;
		iounmap(addr);
		break;
	default:
		break;
	}

	return size;
}

static const struct file_operations hi6402debug_proc_ops = {
	.owner = THIS_MODULE,
	.read = hi6402_debug_show,
	.write = hi6402_debug_store,
};

static ssize_t hi6402_debuglevel_show(struct file *file, char __user *buf,
				size_t size, loff_t *data)
{
	ssize_t ret;
	loff_t pos = 0;
	char level_str[MAX_STR_LEN] = {0};

	IN_FUNCTION;

	if (NULL == buf) {
		HI6402_DSP_ERROR("input error: buf is NULL\n");
		return -EINVAL;
	}

	snprintf(level_str, MAX_STR_LEN-1, "%lu\n", hi6402_dsp_debug_level);
	ret = simple_read_from_buffer(buf, size, &pos, level_str, strlen(level_str));

	OUT_FUNCTION;

	return ret;
}

static ssize_t hi6402_debuglevel_store(struct file *file, const char __user *buf,
				size_t size, loff_t *data)
{
	ssize_t ret;
	char level_str[MAX_STR_LEN] = {0};
	loff_t pos = 0;

	IN_FUNCTION;

	if (buf == NULL) {
		HI6402_DSP_ERROR("buf is NULL\n");
		return -EINVAL;
	}

	ret = simple_write_to_buffer(level_str, MAX_STR_LEN - 1 , &pos, buf, size);
	if (ret != size) {
		HI6402_DSP_ERROR("Input param buf read error, return value: %zd\n", ret);
		return -EINVAL;
	}

	if (strict_strtoul(level_str, 0, &hi6402_dsp_debug_level) != 0) {
		HI6402_DSP_ERROR("input para is error\n");
		return -EINVAL;
	}

	OUT_FUNCTION;

	return size;
}

static const struct file_operations hi6402_debuglevel_proc_ops = {
	.owner = THIS_MODULE,
	.read = hi6402_debuglevel_show,
	.write = hi6402_debuglevel_store,
};

static void create_hi6402debug_proc_file(void)
{
	struct proc_dir_entry *ent_debug;
	struct proc_dir_entry *ent_debuglevel;

	/* Creating read/write "status" entry */
	ent_debug = proc_create(HI6402DEBUG_PROC_FILE, S_IRUGO | S_IWUSR|S_IWGRP,
							hi6402_debug_dir, &hi6402debug_proc_ops);
	ent_debuglevel = proc_create(HI6402DEBUG_LEVEL_PROC_FILE,
							S_IRUGO | S_IWUSR|S_IWGRP,hi6402_debug_dir,
							&hi6402_debuglevel_proc_ops);

	if ((ent_debug == NULL) || (ent_debuglevel == NULL)) {
		remove_proc_entry("hi6402dbg", 0);
		HI6402_DSP_ERROR("create proc file fail\n");
	}
}

static void remove_hi6402debug_proc_file(void)
{
	remove_proc_entry(HI6402DEBUG_PROC_FILE, hi6402_debug_dir);
	remove_proc_entry(HI6402DEBUG_LEVEL_PROC_FILE, hi6402_debug_dir);
}

static int hi6402_create_procfs(void)
{
	hi6402_debug_dir = proc_mkdir(HI6402DEBUG_PATH, NULL);
	if (hi6402_debug_dir == NULL) {
		HI6402_DSP_ERROR("Unable to create /proc/hi6402dbg directory\n");
		return -ENOMEM;
	}
	create_hi6402debug_proc_file();
	return 0;
}

static void hi6402_remove_procfs(void)
{
	remove_hi6402debug_proc_file();

	return;
}
#endif /* ENABLE_HI6402_HIFI_DEBUG */

#ifdef CONFIG_PM
static int hi6402_sr_event(struct notifier_block *this,
		unsigned long event, void *ptr)
{
	switch (event) {
	case PM_POST_HIBERNATION:
	case PM_POST_SUSPEND:
		HI6402_DSP_INFO("resume +\n");
		atomic_set(&hi6402_in_suspend, 0);
		HI6402_DSP_INFO("resume -\n");
		break;

	case PM_HIBERNATION_PREPARE:
	case PM_SUSPEND_PREPARE:
		HI6402_DSP_INFO("suspend +\n");
		atomic_set(&hi6402_in_suspend, 1);
		while (1) {
			if (atomic_read(&hi6402_in_saving))
				msleep(100);
			else
				break;
		}
		HI6402_DSP_INFO("suspend -\n");
		break;
	default:
		return NOTIFY_DONE;
	}
	return NOTIFY_OK;
}
#endif /* CONFIG_PM */

static int hi6402_reboot_notifier(struct notifier_block *nb,
		unsigned long foo, void *bar)
{
	HI6402_DSP_INFO("reboot +\n");
	atomic_set(&hi6402_in_suspend, 1);
	while (1) {
		if (atomic_read(&hi6402_in_saving))
			msleep(100);
		else
			break;
	}
	HI6402_DSP_INFO("reboot -\n");

	return 0;
}

void hi6402_watchdog_send_event(void)
{
	char *envp[2] = {"hi6402_watchdog", NULL};
	HI6402_DSP_ERROR("hi6402 watchdog coming, now reset mediaserver !\n");
	kobject_uevent_env(&priv.dev->kobj, KOBJ_CHANGE, envp);
}

static irqreturn_t hi6402_wtd_irq_handler(int irq, void *data)
{
	priv.is_watchdog_coming = true;

	/* call rdr_hisi_audio_codec.c watchdog process */
	rdr_codec_hifi_watchdog_process();

	return IRQ_HANDLED;
}

int hi6402_misc_dump_reg(char *buf, int size)
{
	if (!buf || size < HI6402_REG_SIZE) {
		HI6402_DSP_ERROR("input para buf is null or size[0x%x] is smaller than reg_size[0x%x].\n",
							size, HI6402_REG_SIZE);
		return -EINVAL;
	}

	hi6402_request_pll_resource(HI_FREQ_SCENE_DUMP_BIN);

	hi6402_read(HI6402_CFG_SUB_BASE, buf, HI6402_CFG_SUB_SIZE);

	hi6402_read(HI6402_AUDIO_SUB_BASE, (buf + HI6402_CFG_SUB_SIZE), HI6402_AUDIO_SUB_SIZE);

	hi6402_read(HI6402_DSP_EDMA_BASE, (buf + HI6402_CFG_SUB_SIZE + HI6402_AUDIO_SUB_SIZE), HI6402_DSP_EDMA_SIZE1);

	hi6402_read(HI6402_DSP_EDMA_BASE + 0x600, (buf + HI6402_CFG_SUB_SIZE + HI6402_AUDIO_SUB_SIZE + HI6402_DSP_EDMA_SIZE1), HI6402_DSP_EDMA_SIZE2);

	hi6402_release_pll_resource(HI_FREQ_SCENE_DUMP_BIN);

	return OK;
}

void hi6402_misc_dump_bin(unsigned int scene_id,
			const unsigned int start_addr,
			unsigned char *arg,
			const unsigned int len)
{
	int ret = 0;

	ret = hi6402_request_pll_resource(scene_id);
	if (ret) {
		HI6402_DSP_ERROR("request pll fail.\n");
		return;
	}

	hi6402_read(start_addr, arg, len);

	ret = hi6402_release_pll_resource(scene_id);
	if (ret) {
		HI6402_DSP_ERROR("release pll fail.\n");
	}

	return;
}

/*****************************************************************************
 * platfrom driver
 * */
#define DTS_COMP_HI6402_DSP_NAME "hisilicon,hi6402-dsp"

static int hi6402_hifi_misc_probe (struct platform_device *pdev)
{
	int ret = 0;
	int image_down_size = IMAGE_DOWN_MEM_SIZE;
	struct device *dev = &pdev->dev;

	IN_FUNCTION;

	memset(&priv, 0, sizeof(priv));

	BUG_ON(dev == NULL);
	priv.dev = &pdev->dev;
	/* get clk & regulator */
	priv.p_irq = dev_get_drvdata(pdev->dev.parent);
	if (!priv.p_irq) {
		HI6402_DSP_ERROR("get parend device error\n");
		return -ENOENT;
	}

#ifdef CONFIG_PM
	/* Register to get PM events */
	hi6402_sr_nb.notifier_call = hi6402_sr_event;
	hi6402_sr_nb.priority = -1;
	if (register_pm_notifier(&hi6402_sr_nb)) {
		HI6402_DSP_ERROR(" Failed to register for PM events\n");
		return -ENOENT;
	}
#endif
	hi6402_reboot_nb.notifier_call = hi6402_reboot_notifier;
	hi6402_reboot_nb.priority = -1;
	(void)register_reboot_notifier(&hi6402_reboot_nb);

	priv.irq_cmd_valid = platform_get_irq_byname(pdev, "cmd_valid");
	if (0 > priv.irq_cmd_valid) {
		HI6402_DSP_ERROR("get cmd_valid irq failed! \n");
		return -ENOENT;
	}

	/* irq request : cmd_valid */
	ret = devm_request_threaded_irq(dev, priv.irq_cmd_valid, NULL,
					hi6402_msg_irq_handler,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					"cmd_valid", &priv);
	if (0 > ret) {
		HI6402_DSP_ERROR("request_irq failed! \n");
		return -1;
	}

	priv.is_watchdog_coming = false;
	priv.is_sync_write_timeout = false;

	priv.irq_wtd = platform_get_irq_byname(pdev, "wd_irq");

	if (0 > priv.irq_wtd) {
		HI6402_DSP_ERROR("error: get wtd irq failed! \n");
		return -ENOENT;
	}

	/* irq request : wd_irq */
	ret = devm_request_threaded_irq(dev, priv.irq_wtd, NULL,
					hi6402_wtd_irq_handler,
					IRQF_NO_SUSPEND | IRQF_ONESHOT,
					"wd_irq", &priv);
	if (0 > ret) {
		HI6402_DSP_ERROR("error: request_irq failed! \n");
		free_irq(priv.irq_cmd_valid, &priv);
		return -1;
	}

	priv.dsp_pwron_done = HIFI_STATE_UNINIT;
	priv.dsp_pllswitch_done = 0;
	priv.sync_msg_ret = 0;
	priv.uart_mode = 0;
	init_waitqueue_head(&priv.dsp_pwron_wq);
	init_waitqueue_head(&priv.dsp_pllswitch_wq);
	init_waitqueue_head(&priv.sync_msg_wq);

	mutex_init(&priv.msg_mutex);
	mutex_init(&priv.state_mutex);

	misc_register(&hi6402_hifi_misc_device);
#ifdef ENABLE_HI6402_HIFI_DEBUG
	hi6402_create_procfs();
#endif /* ENABLE_HI6402_HIFI_DEBUG */
	priv.p_irq->hifi_misc_probe = true;

	priv.src_addr_v = dma_alloc_coherent(priv.dev, image_down_size, &(priv.src_dma_addr), GFP_KERNEL);
    if (NULL == priv.src_addr_v) {
        HI6402_DSP_INFO("dma alloc failed!\n");
    }

	OUT_FUNCTION;

	return 0;
}

static int hi6402_hifi_misc_remove(struct platform_device *pdev)
{
    int image_down_size = IMAGE_DOWN_MEM_SIZE;
	IN_FUNCTION;

#ifdef CONFIG_PM
	/* Unregister for PM events */
	unregister_pm_notifier(&hi6402_sr_nb);
#endif
	unregister_reboot_notifier(&hi6402_reboot_nb);

	free_irq(priv.irq_cmd_valid, &priv);
	free_irq(priv.irq_wtd, &priv);
	hi6402_hifi_deinit();
	(void)misc_deregister(&hi6402_hifi_misc_device);
#ifdef ENABLE_HI6402_HIFI_DEBUG
	hi6402_remove_procfs();
#endif /* ENABLE_HI6402_HIFI_DEBUG */
	dma_free_coherent(priv.dev, image_down_size, priv.src_addr_v, priv.src_dma_addr);

	OUT_FUNCTION;

	return 0;
}

static const struct of_device_id hi6402_dsp_match_table[] = {
	{
		.compatible = DTS_COMP_HI6402_DSP_NAME,
	},
	{},
};

MODULE_DEVICE_TABLE(of, hi6402_dsp_match_table);

static struct platform_driver hi6402_hifi_misc_driver = {
	.driver =
	{
		.name           = "hi6402 hifi misc",
		.owner          = THIS_MODULE,
		.of_match_table = of_match_ptr(hi6402_dsp_match_table),
	},
	.probe  = hi6402_hifi_misc_probe,
	.remove = hi6402_hifi_misc_remove,
};

static int __init hi6402_hifi_misc_init(void)
{
	return platform_driver_register(&hi6402_hifi_misc_driver);
}

static void __exit hi6402_hifi_misc_exit(void)
{
	platform_driver_unregister(&hi6402_hifi_misc_driver);
}

late_initcall(hi6402_hifi_misc_init);
module_exit(hi6402_hifi_misc_exit);

MODULE_DESCRIPTION("hi6402 hifi misc driver");
MODULE_LICENSE("GPL");
