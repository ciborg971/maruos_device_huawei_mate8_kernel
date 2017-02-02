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

#include <linux/slab.h>
#include <linux/proc_fs.h>
#include <linux/debugfs.h>
#include <linux/seq_file.h>
#include <linux/sched.h>
#include <asm/uaccess.h>
#include <osl_generic.h>
#include <bsp_hardtimer.h>
#include <bsp_pm_om.h>
#include "pm_om_platform.h"
#include "pm_om_debug.h"

struct pm_om_platform g_pmom_platform;

ssize_t pm_om_fread(struct file *file, char __user *buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	u32 len  = 0;
	u32 left = 0;
	int err_code = 0;
	unsigned long flags = 0;
	ssize_t ret;
    DEFINE_WAIT(wait);

	if (0 == count)
	{
		return 0;
	}

	while (1) 
	{
		prepare_to_wait(&g_pmom_platform.wq, &wait, TASK_INTERRUPTIBLE);

		/* 异常保护 */
		if (ctrl->log.init_flag != PM_OM_INIT_MAGIC)
		{
			goto skip_read;
		}

		ctrl->log.rb.write = ctrl->log.smem->rb_info.write;
		ctrl->log.rb.read  = ctrl->log.smem->rb_info.read;
		ret = ring_buffer_is_empty(&ctrl->log.rb);

		if (!ret)
		{
			break;
		}

skip_read:
		if (file->f_flags & O_NONBLOCK)
		{
			ret = -EAGAIN;
			break;
		}

		if (signal_pending(current))
		{
			ret = -EINTR;
			break;
		}

		wake_unlock(&g_pmom_platform.wake_lock);
		schedule();
	}

	finish_wait(&g_pmom_platform.wq, &wait);
	if (ret)
	{
		return ret;
	}

	len  = ring_buffer_writen_size(&ctrl->log.rb);
	len  = min((u32)count, len);
	left = min(len, ctrl->log.rb.size  - ctrl->log.rb.read);
	pmom_pr_debug("len=0x%x, left=0x%x\n", len, left);

	if ((copy_to_user(buf, ctrl->log.rb.base + ctrl->log.rb.read, left)) != 0)
	{
		err_code = 1;
		goto copy_to_user_err;
    }

	if (len >left)
	{
		if ((copy_to_user(buf + left, ctrl->log.rb.base, len - left)) != 0)
		{
			err_code = 2;
			goto copy_to_user_err;
		}
	}

	/* 成功读完之后更新核间ring buffer的读指针 */
	pm_om_spin_lock(&ctrl->log.lock, flags);
	ctrl->log.rb.read += len;
	ctrl->log.rb.read %= (ctrl->log.rb.size);
	ctrl->log.smem->rb_info.read = ctrl->log.rb.read;
	pm_om_spin_unlock(&ctrl->log.lock, flags);

	return len;
copy_to_user_err:
	pmom_pr_err("copy_to_user[%d] err\n", err_code);
	return -EFAULT;
}

static inline int pm_om_fopen(struct inode *inode, struct file *file)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_pmom_platform.lock, flags);
	ctrl->log.smem->fwrite_sw = 1;
	g_pmom_platform.fopen_cnt++;
	spin_unlock_irqrestore(&g_pmom_platform.lock, flags);

	if (g_pmom_platform.fopen_cnt > 1)
	{
		pmom_pr_err("info: fopen_cnt=%d\n", g_pmom_platform.fopen_cnt);
		pm_om_spin_lock(&ctrl->log.lock, flags);
		ctrl->log.smem->rb_info.read = ctrl->log.smem->rb_info.write;
		pm_om_spin_unlock(&ctrl->log.lock, flags);
	}

	pmom_pr_debug("\n");
	return 0;
}

static inline int pm_om_frelease(struct inode *inode, struct file *file)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	unsigned long flags = 0;

	spin_lock_irqsave(&g_pmom_platform.lock, flags);
	ctrl->log.smem->fwrite_sw = 0;
	spin_unlock_irqrestore(&g_pmom_platform.lock, flags);

	wake_unlock(&g_pmom_platform.wake_lock);

	pmom_pr_debug("\n");
	return 0;
}

static const struct file_operations proc_pm_om_operations = {
	.read		= pm_om_fread,
	.open		= pm_om_fopen,
	.release	= pm_om_frelease,
};

int pm_om_fwrite_trigger(void)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	u32 timestamp = 0;

	/* 确认是否需要写文件 */
	if (ctrl->log.app_is_alive)
	{
		timestamp = bsp_get_slice_value();
		if ((timestamp - g_pmom_platform.timestamp) > g_pmom_platform.wakeup_interval)
		{
			wake_lock(&g_pmom_platform.wake_lock);
			wake_up_interruptible(&g_pmom_platform.wq);
		}
		g_pmom_platform.timestamp = bsp_get_slice_value();
	}
	pmom_pr_debug("\n");

	return 0;
}

static ssize_t pm_om_mod_sw_show(struct file *file,  char  __user *buffer, size_t count, loff_t *ppos)
{
    int  len      = 0;
    char buf[32]  = {0};
    u64  sw_value = 0;
    u32  tmp_low  = 0;
    u32  tmp_high = 0;
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;

    sw_value = ctrl->log.smem->nv_cfg.mod_sw_bitmap;
    tmp_low  = (u32)(sw_value & (u32)0xFFFFFFFF);
    tmp_high = (u32)((sw_value >> 32) & (u32)0xFFFFFFFF);

    len = snprintf(buf, 32, "0x%08x%08x\n", tmp_high, tmp_low);
	return simple_read_from_buffer(buffer, count, ppos, (void *)buf, len);
}

static ssize_t get_u32_data_from_user(const char  __user *usr_buf, size_t count)
{
	char buf[32]= {0};
	u32  value  = 0;
	int  ret = 0;

	if(count >= sizeof(buf))
	{
		pmom_pr_err("input size(%d) >= buf size(%d)\n", count, sizeof(buf));
		return -ENOMEM;
	}
	if (copy_from_user(buf, usr_buf, count))
	{
		pmom_pr_err("copy_from_user err\n");
		return -EFAULT;
	}

	ret = sscanf(buf, "%u", &value);
	if (ret < 0)
	{
		return ret;
	}
	return value;
}

static int get_u32_seq_data_from_user(const char  __user *usr_buf, size_t usr_count, u8 *seq_data)
{
	char buf[PM_OM_LOG_THRE_BUF_SIZE]= {0};
	int ret = 0;

	if(usr_count >= sizeof(buf))
	{
		pmom_pr_err("input size(%d) >= buf size(%d)\n", usr_count, sizeof(buf));
		return -ENOMEM;
	}
	if (copy_from_user(buf, usr_buf, usr_count))
	{
		pmom_pr_err("copy_from_user err\n");
		return -EFAULT;
	}

	ret = sscanf(buf, "%c %c %c %c", &seq_data[0], &seq_data[1], &seq_data[2], &seq_data[3]);/* [false alarm]:fortify */
	if (ret != 4)
	{
		return  -EFAULT;
	}
	return 0;
}

/* 通知其他核开启log功能 */
static void pm_om_notify_other_core(pm_om_icc_data_type data)
{
	s32 ret = 0;
	u32 channel_id = 0;

	channel_id = PM_OM_ICC_ACORE_CHN_ID;
	ret = bsp_icc_send(ICC_CPU_MODEM, channel_id, (u8 *)&data, sizeof(data));
	if(sizeof(data) != ret)
	{
		goto icc_send_fail;
	}

	/* TODO:  等M3开启后打开 */
	return;

icc_send_fail:
	pmom_pr_err("icc[0x%x] send fail: 0x%x\n", PM_OM_ICC_ACORE_CHN_ID, ret);
	return;
}

static ssize_t pm_om_mod_on_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	ssize_t mod_id = get_u32_data_from_user(usr_buf, count);

	if(mod_id < 0)
	{
		return mod_id;
	}
	else if(mod_id < 64)
	{
		ctrl->log.init_flag = PM_OM_INIT_MAGIC;
		pm_om_log_mod_on(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), mod_id);
		pm_om_notify_other_core(1);
	}
	else if(mod_id == 64)/* enable all */
	{
		ctrl->log.init_flag = PM_OM_INIT_MAGIC;
		pm_om_log_sw_set(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), 0xffffffffffffffff);
		pm_om_notify_other_core(1);
	}

	return count;
}

static ssize_t pm_om_mod_off_store(struct file *fil,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	ssize_t mod_id = get_u32_data_from_user(usr_buf, count);

	if(mod_id < 0)
	{
		return mod_id;
	}
	else if(mod_id < 64)
	{
		pm_om_log_mod_off(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), mod_id);
	}
	else if(mod_id == 64)/* disable all */
	{
		ctrl->log.init_flag = 0;
		pm_om_log_sw_set(&(ctrl->log.smem->nv_cfg.mod_sw_bitmap), 0);
		pm_om_notify_other_core(0);
	}

	return count;
}

static ssize_t pm_om_fwrite_trigger_on_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	ssize_t sw = get_u32_data_from_user(usr_buf, count);

	if(sw < 0)
	{
		return sw;
	}
	else if(sw)
	{
		ctrl->log.smem->fwrite_sw = 1;
	}
	else if(sw == 0)
	{
		ctrl->log.smem->fwrite_sw = 0;
	}

	return count;
}

static ssize_t pm_om_fwrite_trigger_on_show(struct file *file,  char  __user *usr_buf, size_t count, loff_t *ppos)
{
	int  len      = 0;
	char buf[32]  = {0};
	u32  sw_value = 0;
	struct pm_om_ctrl *ctrl = pm_om_ctrl_get();

	sw_value = ctrl->log.smem->fwrite_sw;
	len = snprintf(buf, 32, "0x%08x\n", sw_value);
	return simple_read_from_buffer(usr_buf, count, ppos, (void *)buf, len);
}

static ssize_t pm_om_rb_size_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	ssize_t rb_size = get_u32_data_from_user(usr_buf, count);

	if(rb_size < 0)
	{
		return rb_size;
	}
	else if(rb_size)
	{
		ctrl->log.rb.size = rb_size;
	}

	return count;
}

static ssize_t pm_om_rb_info_show(struct file *file,  char  __user *usr_buf, size_t count, loff_t *ppos)
{
	int  len      = 0;
	char buf[PM_OM_LOG_THRE_BUF_SIZE]  = {0};

	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	struct ring_buffer *rb = &(ctrl->log.rb);
	len = snprintf(buf, PM_OM_LOG_THRE_BUF_SIZE, 
		"rb_base\t\t\trb_size\t\trb_write\trb_read\n0x%p(0x%p)\t0x%08x\t0x%08x\t0x%08x\t\n",
		(void *)rb->base, (void *)SHD_DDR_V2P((void *)rb->base), rb->size, rb->write, rb->read);
	return simple_read_from_buffer(usr_buf, count, ppos, (void *)buf, len);
}

static ssize_t pm_om_log_threshold_store(struct file *file,  const char  __user *usr_buf, size_t count, loff_t *ppos)
{
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;
	u8 *seq_data = NULL;
	int ret = 0;
	u32 len = sizeof(u8) * PM_OM_LOG_THRE_CORE_NUM;

	seq_data = kmalloc(len, GFP_KERNEL);
	if (!seq_data)
	{
		return -ENOMEM;
	}

	ret = get_u32_seq_data_from_user(usr_buf, count, seq_data);
	if(ret < 0)
	{
		kfree(seq_data);
		seq_data = NULL;
		return ret;
	}
	else
	{
		memcpy((void *)ctrl->log.smem->nv_cfg.log_threshold, (void *)seq_data, len);
		ctrl->log.threshold = ctrl->log.smem->nv_cfg.log_threshold[PM_OM_CPUID];
	}

	kfree(seq_data);
	seq_data = NULL;
	return count;
}

static ssize_t pm_om_log_threshold_show(struct file *file,  char  __user *usr_buf, size_t count, loff_t *ppos)
{
	int len = 0;
	char buf[PM_OM_LOG_THRE_BUF_SIZE] = {0};
	struct pm_om_ctrl *ctrl = g_pmom_platform.ctrl;

	len = snprintf(buf, PM_OM_LOG_THRE_BUF_SIZE, "%2d %2d %2d %2d\n", 
		ctrl->log.smem->nv_cfg.log_threshold[0], 
		ctrl->log.smem->nv_cfg.log_threshold[1],
		ctrl->log.smem->nv_cfg.log_threshold[2],
		ctrl->log.smem->nv_cfg.log_threshold[3]);
	return simple_read_from_buffer(usr_buf, count, ppos, (void *)buf, len);
}

static int pm_om_wakeup_stats_show(struct seq_file *m, void *unused)
{
	struct pm_om_debug *debug = (struct pm_om_debug *)g_pmom_platform.ctrl->debug;

	seq_puts(m, "wake_times\twaket_min\twaket_max\n");
 	seq_printf(m, "%u\t\t%u\t\t%u\n", debug->stat.wakeup_cnt,debug->stat.waket_min, debug->stat.waket_max);

	return 0;
}

static int wakeup_sources_stats_open(struct inode *inode, struct file *file)
{
	return single_open(file, pm_om_wakeup_stats_show, NULL);
}


static const struct file_operations pm_om_mod_on_fops = {
	.read  = pm_om_mod_sw_show,
	.write = pm_om_mod_on_store,
};

static const struct file_operations pm_om_mod_off_fops = {
	.read  = pm_om_mod_sw_show,
	.write = pm_om_mod_off_store,
};

static const struct file_operations pm_om_fwrite_trigger_fops = {
	.read  = pm_om_fwrite_trigger_on_show,
	.write = pm_om_fwrite_trigger_on_store,
};

static const struct file_operations pm_om_rb_info_fops = {
	.read  = pm_om_rb_info_show,
	.write = pm_om_rb_size_store,
};

static const struct file_operations pm_om_log_threshold_fops = {
	.read  = pm_om_log_threshold_show,
	.write = pm_om_log_threshold_store,
};

static const struct file_operations pm_om_wakeup_stats_fops = {
	.open = wakeup_sources_stats_open,
	.read = seq_read,
	.llseek = seq_lseek,
	.release = single_release,
};

static int pm_om_debugfs_create(void)
{
	struct dentry *debugfs_root;

	debugfs_root = debugfs_create_dir("pm_om", NULL);
	if (!debugfs_root)
		return (-ENOENT);

	debugfs_create_file("mod_on", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_mod_on_fops);
	debugfs_create_file("mod_off", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_mod_off_fops);
	debugfs_create_file("fwrite_trigger", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_fwrite_trigger_fops);
	debugfs_create_file("rb_info", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_rb_info_fops);
	debugfs_create_file("log_threshold", (S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_log_threshold_fops);
	debugfs_create_file("wakeup_stats",(S_IRUGO|S_IWUSR), debugfs_root, NULL, &pm_om_wakeup_stats_fops);

	return 0;
}

void pm_om_ipc_handler(u32 data)
{
	pmom_pr_debug("recv ipc[0x%x]\n", data);

	wake_lock(&g_pmom_platform.wake_lock);
	wake_up_interruptible(&g_pmom_platform.wq);
}

/* 系统被唤醒时触发一次写文件，减少acore被唤醒次数 */
s32 pm_om_notify(struct notifier_block *notify_block, unsigned long mode, void *unused)
{
	switch (mode)
	{
	case PM_POST_HIBERNATION:
		wake_lock(&g_pmom_platform.wake_lock);
		wake_up_interruptible(&g_pmom_platform.wq);
		break;
	default:
		break;
	}

	return PM_OM_OK;
}

int pm_om_platform_init(void)
{
	char *dev_name = "pmom";
	int ret = PM_OM_OK;

	struct pm_om_ctrl *ctrl  = pm_om_ctrl_get();

	memset((void *)&g_pmom_platform, 0, sizeof(g_pmom_platform));
	
	g_pmom_platform.misc.minor = MISC_DYNAMIC_MINOR;
	g_pmom_platform.misc.name  = kstrdup(dev_name, GFP_KERNEL);
	if (unlikely(g_pmom_platform.misc.name == NULL))
	{
		pmom_pr_err("malloc [%s] fail\n",  dev_name);
		return PM_OM_ERR;
	}

	g_pmom_platform.misc.fops = &proc_pm_om_operations;
	g_pmom_platform.misc.parent = NULL;

	init_waitqueue_head(&g_pmom_platform.wq);

	ret = misc_register(&g_pmom_platform.misc);
	if (unlikely(ret)) 
	{
		printk("%s register misc fail\n", g_pmom_platform.misc.name);
		return PM_OM_ERR;
	}
	
	spin_lock_init(&g_pmom_platform.lock);

	g_pmom_platform.timestamp       = bsp_get_slice_value();
	g_pmom_platform.wakeup_interval = PM_OM_WAKEUP_INTERVAL;

	pm_om_debugfs_create();

	wake_lock_init(&g_pmom_platform.wake_lock, WAKE_LOCK_SUSPEND, "pmom_wake");

	g_pmom_platform.pm_notify.notifier_call = pm_om_notify;
	register_pm_notifier(&g_pmom_platform.pm_notify);


	if(0 != bsp_ipc_int_connect((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_PM_OM, 
		(voidfuncptr)pm_om_ipc_handler, IPC_ACPU_INT_SRC_CCPU_PM_OM))
	{
		goto ipc_reg_err;
	}
	if(0 != bsp_ipc_int_enable((IPC_INT_LEV_E)IPC_ACPU_INT_SRC_CCPU_PM_OM))
	{
		goto ipc_reg_err;
	}

	g_pmom_platform.ctrl = ctrl;
	ctrl->platform = (void *)&g_pmom_platform;

	return PM_OM_OK;
ipc_reg_err:
	pmom_pr_err("ipc[0x%x] register fail\n", IPC_ACPU_INT_SRC_CCPU_PM_OM);
	return PM_OM_ERR;
}

