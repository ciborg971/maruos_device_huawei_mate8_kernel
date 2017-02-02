/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and 
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may 
 * *    be used to endorse or promote products derived from this software 
 * *    without specific prior written permission.
 * 
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

#include <linux/suspend.h>
#include <bsp_hardtimer.h>
#include <bsp_pm.h>
#include <bsp_dump.h>
#include <bsp_pm_om.h>
#include "pm_om_platform.h"
#include "pm_om_debug.h"

struct pm_om_debug g_pmom_debug;

void pm_om_wakeup_log(void)
{
	if (g_pmom_debug.stat.wrs_flag == 1)
	{
		bsp_pm_log(PM_OM_PMLG, 0, NULL);
		g_pmom_debug.stat.wrs_flag = 0;
	}
}

void pm_om_wakeup_stat(void)
{
	u32 cur_slice   = bsp_get_slice_value();
	u32 delta_slice = 0;

	g_pmom_debug.stat.wakeup_cnt++;

	delta_slice = delta_slice - g_pmom_debug.stat.waket_prev;
	g_pmom_debug.stat.waket_prev = cur_slice;
	if (delta_slice > g_pmom_debug.stat.waket_max)
	{
		g_pmom_debug.stat.waket_max = delta_slice;
	}
	if (delta_slice < g_pmom_debug.stat.waket_min)
	{
		g_pmom_debug.stat.waket_min = delta_slice;
	}

	/* 32768hz��ת������ */
	delta_slice /= TIME_SLICE_FREQ;
	g_pmom_debug.stat.wrs_flag = 1;
	pmom_print("[C SR]pm om wakeup\n");
}

u32 pm_om_log_time_rec(u32 time_log_start)
{
	u32 ret = 0;
	u32 delta_slice = bsp_get_slice_value();
	delta_slice = delta_slice - time_log_start;

	if (g_pmom_debug.stat.logt_print_sw && delta_slice > g_pmom_debug.stat.logt_max)
	{
		g_pmom_debug.stat.logt_max = delta_slice;
		ret = delta_slice;
	}
	return ret;
}

void pm_om_dbg_on(void)
{
	bsp_mod_level_set(BSP_MODU_PM_OM, BSP_LOG_LEVEL_DEBUG);
}

void pm_om_dbg_off(void)
{
	bsp_mod_level_set(BSP_MODU_PM_OM, BSP_LOG_LEVEL_ERROR);
}

void pm_om_dump_show(void)
{
	u32 i = 0;
	char *magic = NULL;
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();

	pmom_print("**********************************************\n");
	pmom_print("init_flag : 0x%x\n", ctrl->dump.init_flag);
	pmom_print("base_addr : 0x%x\n", ctrl->dump.base);
	pmom_print("length    : 0x%x\n", PM_OM_DUMP_SIZE);
	pmom_print("region_num: 0x%x\n", ctrl->dump.region_cnt);

	for (i = 0; i < ctrl->dump.region_cnt; i++)
	{
		magic = (char *)(&(ctrl->dump.cfg->entry_tbl[i].magic));
		pmom_print("[%c%c%c%c]    : 0x%x\n",magic[0], magic[1], magic[2], magic[3], ctrl->dump.cfg->entry_tbl[i].len);
	}
	pmom_print("**********************************************\n");
}

void pm_om_log_show(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	pmom_print("**********************************************\n");
	pmom_print("init_flag   : 0x%x\n", ctrl->log.init_flag);
	pmom_print("app_is_alive: 0x%x\n", ctrl->log.app_is_alive);
	pmom_print("buf_is_full : 0x%x\n", ctrl->log.buf_is_full);
	pmom_print("threshold   : 0x%x\n", ctrl->log.threshold);
	pmom_print("debug       : 0x%p\n", ctrl->debug);
	pmom_print("platform    : 0x%p\n", ctrl->platform);
	pmom_print("**********************************************\n");
}

void pm_om_debug_show(void)
{
	pmom_print("**********************************************\n");
	pmom_print("logt_print_sw: 0x%x\n", g_pmom_debug.stat.logt_print_sw);
	pmom_print("logt_max\t: 0x%x\n", g_pmom_debug.stat.logt_max);
	pmom_print("**********************************************\n");
}

void pm_om_wake_interval_set(u32 interval)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();
	struct pm_om_platform *platform = (struct pm_om_platform *)ctrl->platform;

	platform->wakeup_interval = interval;
}

/* pmom��mbb/phone������, ����Ҫʵ��. pm_wakeup_ccore��phone��Ҫ��pmomģ��ʵ��,mbb����pmģ��ʵ�� */
s32 pm_wakeup_ccore(enum debug_wake_type type)
{
	u32 channel_id = (ICC_CHN_IFC << 16) | IFC_RECV_FUNC_WAKEUP;
	s32 ret = 0;
	struct debug_pm_s pm_msg;
	u32 msglen = sizeof(pm_msg);
	pm_msg.wake_type=type;

	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8*)(&pm_msg), msglen);
	if(ret != msglen)
	{
		return -1;
	}
    return 0;
}

void debug_pm_wake_lock(void)
{
    wake_lock(&g_pmom_debug.wakelock_debug);
}

void debug_pm_wake_unlock(void)
{
    wake_unlock(&g_pmom_debug.wakelock_debug);
}

static s32 pm_wakeup_icc_msg(u32 id , u32 len, void* context)
{
	u32 ret = 0;
	struct debug_pm_s read_data;

	/* ������ͨ��icc���ͷǷ����ȵ���Ϣ����(��������Ϊ0) */
	if(len != (u32)sizeof(read_data))
	{
		pmom_pr_err("icc packet len(%d) != sizeof(struct debug_pm_s)(%d)\n", len, (u32)sizeof(read_data));
		return -1;
	}

	ret = bsp_icc_read(id, (u8*)&read_data, len);
	if (ret != (int)sizeof(read_data))
	{
		pmom_pr_err("readed len(%d) != icc packet len(%d)", ret, len);
		return -1;
	}
	if(PM_WAKEUP == read_data.wake_type)
	{
		debug_pm_wake_lock();
	}
	else if(PM_WAKEUP_THEN_SLEEP== read_data.wake_type)
	{
		debug_pm_wake_unlock();
	}
	return 0;
}

void print_ccpu_pm_info(void)
{
	printk(KERN_ERR"****************cp pm info****************\n");
	printk(KERN_ERR"shared mem, phy_addr: 0x%p, virt_addr:0x%p\n", \
		bsp_dump_get_field_phy_addr(DUMP_CP_DRX), g_pmom_debug.cdrx_dump_addr);
	printk(KERN_ERR"soft wakelock:        0x%x\n", *((u32 *)g_pmom_debug.cdrx_dump_addr + CDRX_DUMP_WAKE_OFFSET));
	printk(KERN_ERR"[SLEEP COUNT] pm enter cnt: 0x%x, dpm fail cnt: 0x%x\n"\
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + PM_ENTER_COUNT)) \
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + PM_DPM_FAIL_COUNT)));
	printk(KERN_ERR"[STAMP SLICE] sleep start: 0x%x, sleep end: 0x%x, wake start: 0x%x, wake end: 0x%x\n"\
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_PM_SUSPEND_START)) \
		, *((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_AFTER_SEND_IPC)) \
		,*((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_PWRUP_CODE_BEGIN)) \
		, *((u32 *)(g_pmom_debug.cdrx_dump_corepm_addr + STAMP_AFTER_DPM_RESUME)));
}

int cp_pm_notify(struct notifier_block *nb, unsigned long event, void *dummy)
{
	char* dump_base = NULL;
	if(event == PM_SUSPEND_PREPARE)
	{
		if(!g_pmom_debug.cdrx_dump_addr)
		{
			/*��ȡDUMP �͹��Ĺ����ڴ��ַ*/
			dump_base = (char *)bsp_dump_get_field_addr(DUMP_CP_DRX);
			if(NULL == dump_base)
			{
				pmom_pr_err("*******get cdrx dump buffer failed!*******\n");
				return 0;
			}
			g_pmom_debug.cdrx_dump_addr        = (char*)dump_base;
			g_pmom_debug.cdrx_dump_corepm_addr = (char*)(dump_base + CDRX_DUMP_PM_OFFSET);
		}
	}
	if ((event == PM_POST_SUSPEND)&&(g_pmom_debug.cdrx_dump_addr))
	{
		printk(KERN_ERR"\n############ Ccpu Debug Info,Current Slice 0x%x ############\n",bsp_get_slice_value());
		/*�˴���������CCPU�Ĵ�ӡ��Ϣ����*/
		print_ccpu_pm_info();
	}
	return 0;
}


void pm_wakeup_init(void)
{
	char* dump_base = NULL;

	wake_lock_init(&g_pmom_debug.wakelock_debug, WAKE_LOCK_SUSPEND, "cp_pm_wakeup");

	/* ��ʹע��iccʧ��(�д����ӡ),ֻӰ�����,��Ӱ�칦�� */
	(void)bsp_icc_event_register(ICC_CHN_IFC << 16 | IFC_RECV_FUNC_WAKEUP, \
		(read_cb_func)pm_wakeup_icc_msg, NULL, NULL, NULL);
	(void)bsp_icc_event_register(ICC_CHN_MCORE_ACORE << 16 | MCORE_ACORE_FUNC_WAKEUP, \
		(read_cb_func)pm_wakeup_icc_msg, NULL, NULL, NULL);

	g_pmom_debug.pm.notifier_call = cp_pm_notify;
	register_pm_notifier(&g_pmom_debug.pm);

	if(!g_pmom_debug.cdrx_dump_addr)
	{
    	/*��ȡDUMP �͹��Ĺ����ڴ��ַ*/
		dump_base = (char *)bsp_dump_get_field_addr(DUMP_CP_DRX);
		if(NULL == dump_base)
		{
			printk(KERN_ERR"*******!get dump buffer failed!*******\n");
			return;
		}
        g_pmom_debug.cdrx_dump_addr        = (void*)dump_base;
		g_pmom_debug.cdrx_dump_corepm_addr = (char*)(dump_base + CDRX_DUMP_PM_OFFSET);
    }
}

void pm_om_help(void)
{
	pmom_print("***********************\n");
	pmom_print("pm_om_dump_show\n");
	pmom_print("pm_om_log_show\n");
	pmom_print("pm_om_debug_show\n");
	pmom_print("pm_om_dbg_on\n");
	pmom_print("pm_om_dbg_off\n");
	pmom_print("pm_om_wake_interval_set slice\n");
	pmom_print("pm_wakeup_ccore 0|1\n");
	pmom_print("debug_pm_wake_lock\n");
	pmom_print("debug_pm_wake_unlock\n");
	pmom_print("***********************\n");
}

int pm_om_debug_init(void)
{
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();

	memset((void *)&g_pmom_debug, 0, sizeof(g_pmom_debug));

	g_pmom_debug.stat.waket_prev    = bsp_get_slice_value();
	g_pmom_debug.stat.waket_min     = 0xffffffff;
	g_pmom_debug.stat.logt_print_sw = ctrl->log.smem->nv_cfg.reserved;

	g_pmom_debug.ctrl = ctrl;
	ctrl->debug = (void *)&g_pmom_debug;

	pm_wakeup_init();

	return 0;
}

EXPORT_SYMBOL(pm_wakeup_ccore);

