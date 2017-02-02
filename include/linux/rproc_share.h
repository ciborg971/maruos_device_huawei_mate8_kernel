/*
 * Remote Processor - Histar ISP remoteproc platform data.
 *
 * Copyright (c) 2013-2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */


#ifndef _INCLUDE_LINUX_RPROC_SHARE_H
#define _INCLUDE_LINUX_RPROC_SHARE_H

enum rdr_enable_mask
{
    RDR_LOG_TRACE       = 0x1,
    RDR_LOG_LAST_WORD   = 0x2,
    RDR_LOG_ALGO        = 0x4,
    RDR_LOG_CVDR        = 0x8,
    RDR_LOG_IRQ         = 0x10,
};

#define RDR_CHOOSE_TYPE     (RDR_LOG_TRACE | RDR_LOG_LAST_WORD)
#define IRQ_NUM             64

/*
 * struct rproc_shared_para - shared parameters for debug
 * @rdr_enable: the rdr function status
 */
struct isp_plat_cfg {
    unsigned int platform_id;
    unsigned int isp_local_timer;
    unsigned int perf_power;
};

struct bw_boot_status {
    unsigned int entry:1;
    unsigned int invalid_tlb:1;
    unsigned int enable_mmu:1;
    unsigned int reserved:29;
};

struct fw_boot_status {
    unsigned int entry:1;
    unsigned int hard_boot_init:1;
    unsigned int hard_drv_init:1;
    unsigned int app_init:1;
    unsigned int reserved:28;
};

struct rproc_shared_para {
    struct isp_plat_cfg plat_cfg;
    int rdr_enable;
    unsigned int rdr_enable_type;
    unsigned char irq[IRQ_NUM];
    int log_flush_flag;
    unsigned int log_head_size;
    unsigned int log_cache_write;
    struct bw_boot_status bw_stat;
    struct fw_boot_status fw_stat;
};

extern struct rproc_shared_para *rproc_get_share_para(void);
#endif /* _INCLUDE_LINUX_RPROC_SHARE_H */
