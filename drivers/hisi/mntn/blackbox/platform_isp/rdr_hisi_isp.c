/*
 * record the data to rdr. (RDR: kernel run data recorder.)
 * This file wraps the ring buffer.
 *
 * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/printk.h>
#include <linux/irq.h>
#include <linux/interrupt.h>
#include <linux/workqueue.h>
#include <linux/hisi/rdr_pub.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/miscdevice.h>
#include <linux/rproc_share.h>

#include "./rdr_hisi_isp.h"
#include "../rdr_print.h"
#include "../rdr_inner.h"
#include "../rdr_field.h"

typedef enum RDR_ISP_SYSTEM_ERROR_TYPE
{
	ISP_MODID_START = HISI_BB_MOD_ISP_START,
	ISP_WDT_TIMEOUT = 0x81fffdfe,
	ISP_SYSTEM_STATES,
	ISP_MODID_END   = HISI_BB_MOD_ISP_END,
	ISP_SYSTEM_INVALID,
} rdr_isp_sys_err_t;

struct rdr_err_type {
    struct list_head node;
    rdr_isp_sys_err_t type;
};

struct rdr_sys_err_dump_info {
    struct list_head node;
    u32 modid;
    u64 coreid;
    pfn_cb_dump_done cb;
};

struct rdr_isp_device {
    void __iomem *sctrl_addr;
    void __iomem *wdt_addr;
    void __iomem *pctrl_addr;
    void __iomem *rdr_addr;
    struct workqueue_struct *wq;
    struct work_struct err_work;
    struct work_struct dump_work;
    struct list_head err_list;
    struct list_head dump_list;
    spinlock_t err_list_lock;
    spinlock_t dump_list_lock;
    int wdt_irq;
    bool wdt_enable_flag;
};


extern u32 g_isp_rdr_addr;
static u64 core_id = RDR_ISP;
static struct rdr_register_module_result current_info;
static struct rdr_isp_device rdr_isp_dev;

static struct rdr_exception_info_s exc_info[] = {
    [0] = {
        .e_modid = ISP_WDT_TIMEOUT,
        .e_modid_end = ISP_WDT_TIMEOUT,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_ISP,
        .e_reset_core_mask = RDR_AP,
        .e_reentrant = RDR_REENTRANT_DISALLOW,
        .e_exce_type = ISP_S_ISPWD,
        .e_from_core = RDR_ISP,
        .e_from_module = MODULE_NAME,
        .e_desc = "RDR ISP WDT TIMEOUT",
    },
};

static void rdr_system_err_dump_work(struct work_struct *work)
{
    struct rdr_isp_device *dev = &rdr_isp_dev;
    struct rdr_sys_err_dump_info *entry, *tmp;
    unsigned int sync_word;
    int timeout = 20;

    list_for_each_entry_safe(entry, tmp, &dev->dump_list, node) {
        if (ISP_WDT_TIMEOUT == entry->modid) {
            /* check sync word */
            do {
                sync_word = readl(dev->rdr_addr + RDR_SYNC_WORD_OFF);
                msleep(100);
            } while (RDR_ISP_SYNC != sync_word && timeout-- > 0);
            pr_info("%s: sync_word = 0x%x, timeout = %d.\n", __func__, sync_word, timeout);
        }
        entry->cb(entry->modid, entry->coreid);

        spin_lock(&dev->dump_list_lock);
        list_del(&entry->node);
        spin_unlock(&dev->dump_list_lock);

        kfree(entry);
    }
}

static void rdr_isp_dump( u32 modid, u32 etype, u64 coreid,
				char* pathname, pfn_cb_dump_done pfn_cb)
{
    struct rdr_isp_device *dev = &rdr_isp_dev;
    struct rdr_sys_err_dump_info *dump_info;
	pr_info("%s: enter.\n", __func__);

    dump_info = kzalloc(sizeof(struct rdr_sys_err_dump_info), GFP_KERNEL);
    if (!dump_info) {
        pr_err("%s: kzalloc failed. \n", __func__);
        return;
    }

    dump_info->modid = modid;
    dump_info->coreid = core_id;
    dump_info->cb = pfn_cb;
    
    spin_lock(&dev->dump_list_lock);
    list_add_tail(&dump_info->node, &dev->dump_list);
    spin_unlock(&dev->dump_list_lock);

    queue_work(dev->wq, &dev->dump_work);
	pr_info("%s: exit.\n", __func__);
	return;
}

static void rdr_isp_reset( u32 modid, u32 etype, u64 coreid)
{
    pr_info("%s: enter. \n", __func__);
	return;
}

static irqreturn_t isp_wdt_irq_handler(int irq, void *data)
{
    struct rdr_isp_device *dev = &rdr_isp_dev;
    struct rdr_err_type *err_info;
    pr_info("%s:enter.\n", __func__);

    /* disable wdt */
    writel(WDT_UNLOCK, dev->wdt_addr + WDT_LOCK_CTL);
    writel(0, dev->wdt_addr + WDT_ENABLE_CTL);
    writel(WDT_LOCK, dev->wdt_addr + WDT_LOCK_CTL);

    /* init sync work */
    writel(0, dev->rdr_addr + RDR_SYNC_WORD_OFF);

    /* send fiq to isp_a7 */
    writel(0, dev->pctrl_addr + PCTRL_ISP_FIQ);
    writel(1, dev->pctrl_addr + PCTRL_ISP_FIQ);
    writel(0, dev->pctrl_addr + PCTRL_ISP_FIQ);

    err_info = kzalloc(sizeof(struct rdr_err_type), GFP_ATOMIC);
    if (!err_info) {
        pr_info("%s: kzalloc failed. \n", __func__);
        return IRQ_NONE;
    }
    
    err_info->type = ISP_WDT_TIMEOUT;

    spin_lock(&dev->err_list_lock);
    list_add_tail(&err_info->node, &dev->err_list);
    spin_unlock(&dev->err_list_lock);

    queue_work(dev->wq, &dev->err_work);
	pr_info("%s:exit.\n", __func__);
	return IRQ_HANDLED;
}

static void rdr_system_err_work(struct work_struct *work)
{
    struct rdr_isp_device *dev = &rdr_isp_dev;
    struct rdr_err_type *entry, *tmp;

    list_for_each_entry_safe(entry, tmp, &dev->err_list, node) {
        if (ISP_WDT_TIMEOUT == entry->type)
    	    rdr_system_error(entry->type, dev->wdt_irq, 0);
        else
    	    rdr_system_error(entry->type, 0, 0);

        spin_lock_irq(&dev->err_list_lock);
        list_del(&entry->node);
        spin_unlock_irq(&dev->err_list_lock);

        kfree(entry);
    }
}

static int rdr_isp_wdt_init(struct rdr_isp_device *dev)
{
    int ret = 0;

    pr_info("%s: enter.\n", __func__);
    if  (!dev->wdt_enable_flag) {
        pr_info("%s: isp wdt is disabled.\n", __func__);
        return 0;
    }

    dev->wdt_irq = ISP_WDT_IRQ;

    ret = request_irq(dev->wdt_irq, isp_wdt_irq_handler, 0, "isp wtd hanler", NULL);
    if (0 != ret) {
        pr_err("%s: request_irq failed, ret = %d.\n", __func__, ret);
    }

    pr_info("%s: exit.\n", __func__);
    return 0;
}

static int rdr_isp_module_register(void)
{
    struct rdr_isp_device *dev = &rdr_isp_dev;
    struct rdr_module_ops_pub module_ops;
    struct rdr_register_module_result ret_info;
    int ret = 0;
    
    pr_info("%s: enter.\n", __func__);
    module_ops.ops_dump = rdr_isp_dump;
    module_ops.ops_reset = rdr_isp_reset;
    
    ret = rdr_register_module_ops(core_id, &module_ops, &ret_info);
    if(ret != 0) {
        pr_err("%s: rdr_register_module_ops failed! return %d\n", __func__, ret);
        return ret;
    }

    current_info.log_addr = ret_info.log_addr;
    current_info.log_len = ret_info.log_len;
    current_info.nve = ret_info.nve;
    g_isp_rdr_addr = ret_info.log_addr;

    pr_info("%s: log_addr = 0x%llx, log_len = 0x%x, nve = 0x%llx, g_isp_rdr_addr = 0x%x \n",
            __func__, ret_info.log_addr, ret_info.log_len, ret_info.nve, g_isp_rdr_addr);
    
    dev->rdr_addr = hisi_bbox_map((phys_addr_t)g_isp_rdr_addr, current_info.log_len);
    if (!dev->rdr_addr) {
        pr_err("%s: hisi_bbox_map rdr_addr failed.\n", __func__);
        return -ENOMEM;
    }

    pr_info("%s: exit.\n", __func__);
    return 0;
}

static int rdr_isp_exception_register(struct rdr_isp_device *dev)
{
    int i, ret;
    
    pr_info("%s: enter.\n", __func__);
    for (i = 0; i < sizeof(exc_info) / sizeof(struct rdr_exception_info_s); i++) {
        pr_info("%s: register rdr exception, i = %d, type:%d", 
                                            __func__, i, exc_info[i].e_exce_type);

        if (exc_info[i].e_modid == ISP_WDT_TIMEOUT)
            if (!dev->wdt_enable_flag)
                continue;
        
        ret = rdr_register_exception(&exc_info[i]);
        if (ret != exc_info[i].e_modid_end) {
            pr_info("%s: rdr_register_exception failed, ret.%d.\n", __func__, ret);
            return -EINVAL;
        }
    }

    pr_info("%s: exit.\n", __func__);
    return 0;
}

static int rdr_isp_dev_map(struct rdr_isp_device *dev)
{
    unsigned int value;
    bool wdt_flag = false;

    pr_info("%s: enter.\n", __func__);
    dev->wdt_enable_flag = wdt_flag;
    
    dev->sctrl_addr = ioremap((phys_addr_t)SYSCTL_ADDR, SZ_4K);
    if (!dev->sctrl_addr) {
        pr_err("%s: ioremp sctrl failed.\n", __func__);
        return -ENOMEM;
    }
    
    value = readl(dev->sctrl_addr + SC_WDT_OFFSET);

    if (value & (1 << SC_ISP_WDT_BIT))
        wdt_flag = true;
    
    if (wdt_flag) {
        dev->wdt_addr= ioremap((phys_addr_t)WDT_ISP_ADDR, SZ_4K);
        if (!dev->wdt_addr) {
            pr_err("%s: ioremp wdt failed.\n", __func__);
            goto wdt_err;
        }

        dev->pctrl_addr = ioremap((phys_addr_t)PCTRL_ADDR, SZ_4K);
        if (!dev->pctrl_addr) {
            pr_err("%s: ioremp pctrl failed.\n", __func__);
            goto pctrl_err;
        }
    }

    dev->wdt_enable_flag = wdt_flag;
    pr_info("%s: exit.\n", __func__);
    return 0;
    
pctrl_err:
    iounmap(dev->wdt_addr);
wdt_err:
    iounmap(dev->sctrl_addr);

    pr_info("%s: error, exit.\n", __func__);
    return -ENOMEM;
}

static ssize_t rdr_isp_show(struct device *dev, struct device_attribute *attr,
            char *buf)
{
    struct rproc_shared_para *share_para = rproc_get_share_para();
    ssize_t size = 0;
    char *tmp;
    int i = 0;

    pr_info("%s: enter. \n", __func__);

    if (!share_para) {
        pr_info("%s: rproc share memory disable.\n", __func__);
        size += sprintf(buf, "a7 is down, please trun up.\n");
        return size;
    }

    tmp = (char *)kzalloc(SHOW_SIZE, GFP_KERNEL);
    if (unlikely(!tmp)) {
        pr_err("%s: kzalloc failed.\n", __func__);
        return 0;
    }

    size += sprintf(tmp, "\nisp rdr state: %s\n",
                        (!!share_para->rdr_enable) ? "enable" : "disable");

    size += sprintf(tmp + size, "rdr enable module:\n");
    size += sprintf(tmp + size, "trace log: %s\n",
                        (share_para->rdr_enable_type & RDR_LOG_TRACE) ? "enable" : "disable");
    size += sprintf(tmp + size, "last word: %s\n",
                        (share_para->rdr_enable_type & RDR_LOG_LAST_WORD) ? "enable" : "disable");
    size += sprintf(tmp + size, "algo: %s\n", 
                        (share_para->rdr_enable_type & RDR_LOG_ALGO) ? "enable" : "disable");
    size += sprintf(tmp + size, "cvdr: %s\n", 
                        (share_para->rdr_enable_type & RDR_LOG_CVDR) ? "enable" : "disable");
    size += sprintf(tmp + size, "irq: %s\n", 
                        (share_para->rdr_enable_type & RDR_LOG_IRQ) ? "enable" : "disable");

    size += sprintf(tmp + size, "\n-------isp rdr help-------\n");
    size += sprintf(tmp + size, "please echo the following string to the node to enable/disable:\n");
    size += sprintf(tmp + size, "e.g. echo trace_on > rdr_isp\n");

    size += sprintf(tmp + size, "trace_on:      enable trace log\n");
    size += sprintf(tmp + size, "trace_off:     disable trace log\n");
    size += sprintf(tmp + size, "last_wd_on:    enable last word\n");
    size += sprintf(tmp + size, "last_wd_off:   disable last word\n");
    size += sprintf(tmp + size, "algo_on:       enable algorithm log\n");
    size += sprintf(tmp + size, "algo_off:      disable algorithm log\n");
    size += sprintf(tmp + size, "cvdr_on:       enable cvdr log\n");
    size += sprintf(tmp + size, "cvdr_off:      disable cvdr log\n");
    size += sprintf(tmp + size, "irq_on:        enable irq log\n");
    size += sprintf(tmp + size, "irq_off:       disable irq log\n");
    size += sprintf(tmp + size, "sirq_onX:      enable subirq log, X[0-63]\n");
    size += sprintf(tmp + size, "sirq_offX:     disable subirq log, X[0-63]\n");
    size += sprintf(tmp + size, "e.g. echo sirq_on57 > rdr_isp, meaning enable irq 57 log\n");

    size += sprintf(tmp + size, "\nshow subirq log enable details\n");
    while (i < IRQ_NUM) {
        if (share_para->irq[i])
            size += sprintf(tmp + size, "1");
        else
            size += sprintf(tmp + size, "0");
        i++;
        if (i % 8 == 0)
            size += sprintf(tmp + size, "\t");
        if (i % 16 == 0 && i != IRQ_NUM)
            size += sprintf(tmp + size, "\n");
    }

    size += sprintf(tmp + size, "\n");

    memcpy((void *)buf, (void *)tmp, SHOW_SIZE);

    kfree(tmp);
	pr_info("%s:exit.\n", __func__);
    return size;
}

int find_irq_num(char *cmp, const char *input)
{
    unsigned long data;
    int ret, len_cmp;
   
    len_cmp = strlen(cmp);
    ret = strict_strtoul((input + len_cmp), 0, &data);
    if (ret < 0) {
        pr_err("%s: strict_strtoul failed, ret.%d\n", __func__, ret);
        return -EINVAL;
    }

    pr_info("%s: number is %d.\n", __func__, (int)data);
    return (int)data;
}

static ssize_t rdr_isp_store(struct device *dev, struct device_attribute *attr,
             const char *buf, size_t count)
{
    struct rproc_shared_para *share_para = rproc_get_share_para();
    int irq_num;

    pr_info("%s: enter. \n", __func__);

    if (!strncmp("dump", buf, sizeof("dump") - 1)) {
        pr_alert("%s:ISP RDR haven't supported the cmd 'dump',\
        please reference the isp-log in the dentry on the platform,\
        '/data/android_logs/isp-log', thanks.\n", __func__);
        return count;
    } else if (!strncmp(TRACE_ON, buf, sizeof(TRACE_ON) - 1)) {
        pr_info("%s: trace on.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type |= RDR_LOG_TRACE;
        return count;
    } else if (!strncmp(TRACE_OFF, buf, sizeof(TRACE_OFF) - 1)) {
        pr_info("%s: trace off.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type &= ~RDR_LOG_TRACE;
        return count;
    } else if (!strncmp(LAST_WD_ON, buf, sizeof(LAST_WD_ON) - 1)) {
        pr_info("%s: last word on.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type |= RDR_LOG_LAST_WORD;
        return count;
    } else if (!strncmp(LAST_WD_OFF, buf, sizeof(LAST_WD_OFF) - 1)) {
        pr_info("%s: last word off.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type &= ~RDR_LOG_LAST_WORD;
        return count;
    } else if (!strncmp(ALGO_ON, buf, sizeof(ALGO_ON) - 1)) {
        pr_info("%s: algorithm on.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type |= RDR_LOG_ALGO;
        return count;
    } else if (!strncmp(ALGO_OFF, buf, sizeof(ALGO_OFF) - 1)) {
        pr_info("%s: algorithm off.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type &= ~RDR_LOG_ALGO;
        return count;
    } else if (!strncmp(CVDR_ON, buf, sizeof(CVDR_ON) - 1)) {
        pr_info("%s: cvdr on.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type |= RDR_LOG_CVDR;
        return count;
    } else if (!strncmp(CVDR_OFF, buf, sizeof(CVDR_OFF) - 1)) {
        pr_info("%s: cvdr off.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type |= ~RDR_LOG_CVDR;
        return count;
    } else if (!strncmp(IRQ_ON, buf, sizeof(IRQ_ON) - 1)) {
        pr_info("%s: irq on.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type |= RDR_LOG_IRQ;
        return count;
    } else if (!strncmp(IRQ_OFF, buf, sizeof(IRQ_OFF) - 1)) {
        pr_info("%s: irq off.\n", __func__);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->rdr_enable_type |= ~RDR_LOG_IRQ;
        return count;
    } else if (!strncmp(SIRQ_ON, buf, sizeof(SIRQ_ON) - 1)) {
        irq_num = find_irq_num(SIRQ_ON, buf);
        if (irq_num < 0) {
            pr_err("%s: SIRQ_ON irq number overflow.\n", __func__);
            return -EINVAL;
        }

        pr_info("%s: SIRQ_ON.%d\n", __func__, irq_num);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->irq[irq_num] = 1;
        return count;
    } else if (!strncmp(SIRQ_OFF, buf, sizeof(SIRQ_OFF) - 1)) {
        irq_num = find_irq_num(SIRQ_OFF, buf);
        if (irq_num < 0) {
            pr_err("%s: SIRQ_OFF irq number overflow.\n", __func__);
            return -EINVAL;
        }

        pr_info("%s: SIRQ_OFF.%d\n", __func__, irq_num);
        if (!share_para) {
            pr_err("%s:rproc_get_share_para failed.\n", __func__);
            return count;
        }
 
        share_para->irq[irq_num] = 0;
        return count;
    } else {
        pr_info("%s: invalid command: %s.\n", __func__, buf);
        return -EINVAL;
    }

    pr_info("%s:exit.\n", __func__);
    return count;
}

static DEVICE_ATTR(rdr_isp, (S_IRUGO | S_IWUSR | S_IWGRP), rdr_isp_show, rdr_isp_store);

static struct miscdevice isp_rdr_miscdev = { 
    .minor      = 255,
    .name       = "isp_rdr_miscdev",
};

static void rdr_isp_dev_unmap(struct rdr_isp_device *dev)
{
    iounmap(dev->sctrl_addr);
    
    if (dev->wdt_enable_flag) {
        iounmap(dev->wdt_addr);
        iounmap(dev->pctrl_addr);
    }

    return;
}

int __init rdr_isp_init(void)
{
    struct rdr_isp_device *dev = &rdr_isp_dev;
    int ret = 0;

    pr_info("%s: enter.\n", __func__);
    ret = rdr_isp_dev_map(dev);
    if (0 != ret) {
        pr_err("%s: rdr_isp_dev_map failed. \n", __func__);
        return ret;
    }

    ret = rdr_isp_wdt_init(dev);
    if (0 != ret) {
        pr_err("%s: rdr_isp_wdt_init failed.\n", __func__);
        return ret;
    }

    ret = rdr_isp_module_register();
    if (0 != ret) {
        pr_err("%s: rdr_isp_module_register failed.\n", __func__);
        return ret;
    }

    ret = rdr_isp_exception_register(dev);
    if (0 != ret) {
        pr_err("%s: rdr_isp_exception_register failed.\n", __func__);
        return ret;
    }

    dev->wq= create_singlethread_workqueue(MODULE_NAME);
    if (!dev->wq) {
        pr_err("%s: create_singlethread_workqueue failed.\n", __func__);
        return -1;
    }

    INIT_WORK(&dev->dump_work, rdr_system_err_dump_work);
    INIT_WORK(&dev->err_work, rdr_system_err_work);
    INIT_LIST_HEAD(&dev->err_list);
    INIT_LIST_HEAD(&dev->dump_list);
    
    spin_lock_init(&dev->err_list_lock);
    spin_lock_init(&dev->dump_list_lock);
    
    ret = misc_register(&isp_rdr_miscdev);
    if (0 != ret) {
        pr_err("%s: misc_register failed, ret.%d.\n", __func__, ret);
        return ret;
    }
    
    ret = device_create_file(isp_rdr_miscdev.this_device, &dev_attr_rdr_isp);
    if (0 != ret) {
        pr_err("%s: device_create_file failed, ret.%d\n", __func__, ret);    
        return ret;
    }

    pr_info("%s: exit.\n", __func__);
	return ret;
}
subsys_initcall(rdr_isp_init);

static void __exit rdr_isp_exit(void)
{
    struct rdr_isp_device *dev = &rdr_isp_dev;

    rdr_isp_dev_unmap(dev);
    destroy_workqueue(dev->wq);
    misc_deregister(&isp_rdr_miscdev);
	return;
}
module_exit(rdr_isp_exit);

MODULE_LICENSE("GPL v2");

