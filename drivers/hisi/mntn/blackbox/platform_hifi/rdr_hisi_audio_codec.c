/*
 * audio codec rdr.
 *
 * Copyright (c) 2015 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
*/

#include <linux/kernel.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include <linux/thread_info.h>
#include <linux/slab.h>
#include <linux/wakelock.h>

#include <linux/hisi/util.h>
#include <linux/hisi/rdr_hisi_ap_hook.h>

#include <linux/hisi/hi6402_hifi_misc.h>

#include "rdr_print.h"
#include "rdr_hisi_audio_adapter.h"
#include "hi6402_hifi_regs.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#define COMMENT_TEXT_LEN            (256)
#define HI6402_DUMP_STACK_SIZE      (0x200)
#define HI6402_DUMP_STACK_ADDR      (0x1003C2C0)
#define CODEC_HIFI_MODID            (0x84000010)

#define OM_HI6402_LOG_PATH          "codechifi_logs/"
#define DUMP_TCM_FILE_NAME          "codec_tcm.bin"
#define DUMP_OCRAM_FILE_NAME        "codec_ocram.bin"
#define DUMP_REG_FILE_NAME          "codec_reg.bin"

struct rdr_codec_des_s
{
	u32 modid;
	char* pathname;
	pfn_cb_dump_done dumpdone_cb;

	bool is_dump_thread_running;
	bool is_handler_thread_running;
	struct semaphore handler_sem;
	struct semaphore dump_sem;
	struct task_struct *kdump_task;
	struct task_struct *khandler_task;
	struct wake_lock rdr_wl;
};
static struct rdr_codec_des_s codec_des;

static int dump_hifi_tcm(char *filepath)
{
	int ret = 0;
	char *buf = NULL;
	char xn[RDR_FNAME_LEN] = {0};

	BUG_ON(NULL == filepath);

	snprintf(xn, sizeof(xn), "%s%s%s", filepath, OM_HI6402_LOG_PATH, DUMP_TCM_FILE_NAME);/* [false alarm]:经确认此处为fortify误警 */

	buf = (char*)kmalloc(HI6402_TCM_SIZE, GFP_KERNEL);
	if (!buf) {
		BB_PRINT_ERR("hi6402_rdr %s():alloc buf failed\n", __func__);
		return -1;
	}
	memset(buf, 0, HI6402_TCM_SIZE);

	hi6402_misc_dump_bin(HI_FREQ_SCENE_DUMP_BIN, HI6402_TCM_START_ADDR, buf, HI6402_TCM_SIZE);

	ret = rdr_audio_write_file(xn, buf, HI6402_TCM_SIZE);
	if (ret) {
		BB_PRINT_ERR("hi6402_rdr %s(): write file fail.\n", __func__);
	}

	kfree(buf);

	return ret;
}

static int dump_hifi_ocram(char *filepath)
{
	int ret = 0;
	char *buf = NULL;
	char xn[RDR_FNAME_LEN] = {0};

	BUG_ON(NULL == filepath);

	snprintf(xn, sizeof(xn), "%s%s%s", filepath, OM_HI6402_LOG_PATH, DUMP_OCRAM_FILE_NAME);/* [false alarm]:经确认此处为fortify误警 */

	buf = (char*)kmalloc(HI6402_DUMP_STACK_SIZE, GFP_KERNEL);
	if (!buf) {
		BB_PRINT_ERR("hi6402_rdr %s():alloc buf failed\n", __func__);
		return -1;
	}
	memset(buf, 0, HI6402_DUMP_STACK_SIZE);

	hi6402_misc_dump_bin(HI_FREQ_SCENE_DUMP_BIN, HI6402_DUMP_STACK_ADDR, buf, HI6402_DUMP_STACK_SIZE);

	ret = rdr_audio_write_file(xn, buf, HI6402_DUMP_STACK_SIZE);
	if (ret) {
		BB_PRINT_ERR("hi6402_rdr %s(): write file fail.\n", __func__);
	}

	kfree(buf);

	return ret;
}

static int dump_codec_reg(char *filepath)
{
	int ret = OK;
	char *buf = NULL;
	char xn[RDR_FNAME_LEN];

	BUG_ON(NULL == filepath);

	snprintf(xn, sizeof(xn), "%s%s%s", filepath, OM_HI6402_LOG_PATH, DUMP_REG_FILE_NAME);/* [false alarm]:经确认此处为fortify误警 */

	buf = (char*)kmalloc((HI6402_REG_SIZE + COMMENT_TEXT_LEN), GFP_KERNEL);
	if (!buf) {
		BB_PRINT_ERR("hi6402_rdr %s():alloc buf failed\n", __func__);
		return -1;
	}
	memset(buf, 0, (HI6402_REG_SIZE + COMMENT_TEXT_LEN));

	ret = hi6402_misc_dump_reg(buf, HI6402_REG_SIZE);
	if (ret != OK) {
		BB_PRINT_ERR("dump 6402 reg fail.\n");
		kfree(buf);
		return -1;
	}

	snprintf((buf + HI6402_REG_SIZE), COMMENT_TEXT_LEN, "page_cfg_subsys:%08x->0x0, aud_reg:%08x->0x100, DMA:%08x->0x300, DMA:%08x->0x330\n",
		HI6402_CFG_SUB_BASE, HI6402_AUDIO_SUB_BASE, HI6402_DSP_EDMA_BASE, HI6402_DSP_EDMA_BASE + 0x600);

	ret = rdr_audio_write_file(xn, buf, (HI6402_REG_SIZE + COMMENT_TEXT_LEN));
	if (ret) {
		BB_PRINT_ERR("write codec reg file fail.\n");
	}

	kfree(buf);
	buf = NULL;

	return ret;
}

static int dump_codec(char *filepath)
{
	int ret = 0;

/* todo :dump_codec_reg undefined in dallas */
#ifdef CONFIG_HI6402_HIFI_MISC
	BUG_ON(NULL == filepath);
	/* 暂时不导TCM */
	//ret = dump_hifi_tcm(filepath);
	//BB_PRINT_DBG("%s:dump hifi tcm, %s\n", __func__, ret ? "fail" : "success");

	ret = dump_hifi_ocram(filepath);
	BB_PRINT_PN("rdr:%s():dump hifi ocram, %s\n", __func__, ret ? "fail" : "success");

	ret = dump_codec_reg(filepath);
	BB_PRINT_PN("rdr:%s():dump 6402 ret, %s\n", __func__, ret ? "fail" : "success");
#endif
	return ret;
}

void rdr_codec_hifi_watchdog_process()
{
	wake_lock(&codec_des.rdr_wl);
	up(&codec_des.handler_sem);
}

static int irq_handler_thread(void *arg)
{
	BB_PRINT_START();

	while (codec_des.is_handler_thread_running) {
		if (down_interruptible(&codec_des.handler_sem)) {
			BB_PRINT_ERR("down codec_des.handler_sem fail.\n");
			continue;
		}

		BB_PRINT_PN("%s():codechifi watchdog coming.\n", __func__);

		if (!codec_des.is_handler_thread_running) {
			BB_PRINT_ERR("irq handler thread exit.\n");
			break;
		}

		BB_PRINT_PN("enter rdr process for codechifi watchdog.\n");
		rdr_system_error(CODEC_HIFI_MODID, 0, 0);
		BB_PRINT_PN("exit rdr process for codechifi watchdog.\n");
	}

	BB_PRINT_END();

	return 0;
}

static int dump_thread(void *arg)
{
	BB_PRINT_START();

	while (codec_des.is_dump_thread_running) {
		if (down_interruptible(&codec_des.dump_sem)) {
			BB_PRINT_ERR("down codec_des.dump_sem fail.\n");
			continue;
		}

		if (!codec_des.is_dump_thread_running) {
			BB_PRINT_PN("codec dump thread exit.\n");
			break;
		}

		BB_PRINT_DBG("begin to dump codec hifi log.\n");
		dump_codec(codec_des.pathname);
		BB_PRINT_DBG("end dump codec hifi log.\n");

		if (codec_des.dumpdone_cb) {
			BB_PRINT_DBG("begin dump codec hifi done callback, modid: 0x%x.\n" , codec_des.modid);
			codec_des.dumpdone_cb(codec_des.modid, RDR_HIFI);
			BB_PRINT_DBG("end dump codec hifi done callback.\n");
		}
	}

	BB_PRINT_END();

	return 0;
}

void rdr_audio_codec_dump(u32 modid, char* pathname, pfn_cb_dump_done pfb)
{
	BUG_ON(NULL == pathname);
	BUG_ON(NULL == pfb);

	BB_PRINT_START();

	codec_des.modid = modid;
	codec_des.dumpdone_cb = pfb;
	codec_des.pathname = pathname ;

	up(&codec_des.dump_sem);

	BB_PRINT_END();

	return;
}

void rdr_audio_codec_reset( u32 modid, u32 etype, u64 coreid )
{
	BB_PRINT_START();
/* todo :hi6402_watchdog_send_event undefined in dallas */
#ifdef CONFIG_HI6402_HIFI_MISC
	/*	 ....send watchdog event.....	*/
	hi6402_watchdog_send_event();
#endif

	wake_unlock(&codec_des.rdr_wl);

	BB_PRINT_END();

	return;
}

int rdr_audio_codec_init(void)
{
	BB_PRINT_START();

	codec_des.modid = ~0;
	codec_des.pathname= NULL;
	codec_des.dumpdone_cb = NULL;

	wake_lock_init(&codec_des.rdr_wl, WAKE_LOCK_SUSPEND, "rdr_codechifi");
	sema_init(&codec_des.dump_sem, 0);
	sema_init(&codec_des.handler_sem, 0);
	codec_des.kdump_task = NULL;
	codec_des.khandler_task = NULL;
	codec_des.is_dump_thread_running = true;
	codec_des.is_handler_thread_running = true;

	codec_des.kdump_task = kthread_run(dump_thread, NULL, "rdr_codec_hifi_dump_thread");
	if (!codec_des.kdump_task) {
		codec_des.is_dump_thread_running = false;
		BB_PRINT_ERR("create rdr codec dump thead fail.\n");

		goto error;
	}

	codec_des.khandler_task = kthread_run(irq_handler_thread, NULL, "rdr_codec_hifi_irq_handler_thread");
	if (!codec_des.khandler_task) {
		codec_des.is_handler_thread_running= false;
		BB_PRINT_ERR("create rdr codec irq handler thead fail.\n");

		goto error;
	}

	BB_PRINT_END();

	return 0;

error:
	if (codec_des.kdump_task != NULL) {
		kthread_stop(codec_des.kdump_task);
	}

	if (codec_des.khandler_task != NULL) {
		kthread_stop(codec_des.khandler_task);
	}

	wake_lock_destroy(&codec_des.rdr_wl);
	BB_PRINT_END();

	return -1;
}

void rdr_audio_codec_exit(void)
{
	BB_PRINT_START();

	codec_des.is_handler_thread_running = false;
	codec_des.is_dump_thread_running = false;
	up(&codec_des.dump_sem);
	up(&codec_des.handler_sem);

	if (codec_des.kdump_task != NULL) {
		kthread_stop(codec_des.kdump_task);
	}

	if (codec_des.khandler_task != NULL) {
		kthread_stop(codec_des.khandler_task);
	}

	wake_lock_destroy(&codec_des.rdr_wl);
	BB_PRINT_END();

	return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

