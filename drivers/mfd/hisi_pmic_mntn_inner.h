/*
 * Device driver for PMU DRIVER
 *
 * Copyright (c) 2011 Hisilicon Co. Ltd
 *
 */

#ifndef __PMIC_MNTN_H__
#define __PMIC_MNTN_H__

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/irq.h>
#include <linux/irqdesc.h>
#include <linux/irqnr.h>
#include <linux/timer.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/rtc.h>
#include <linux/slab.h>
#include <linux/syscalls.h>
#include <linux/hardirq.h>
#include <linux/workqueue.h>
#include <linux/jiffies.h>
#include <linux/of.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/of_platform.h>
#include <linux/string.h>
#include <linux/regulator/consumer.h>
#include <asm/uaccess.h>
#include <linux/hisi/util.h>

#include <linux/mfd/hisi_pmic.h>

#ifdef CONFIG_HISI_BB
#include <platform_ap/rdr_hisi_platform.h>
#include <linux/hisi/rdr_pub.h>
#endif

#define SET_REG_BIT(reg_value, shift, mask, value)  (reg_value = (reg_value & (~((((unsigned int)1 << mask) - 1) << shift)))\
                                                        |((unsigned char)((value) & (((unsigned int)1 << mask) - 1)) << (shift)))

#define PMIC_PRINT_BUF_SIZE             (4*1024)
#define PMIC_DTS_ATTR_LEN               (64)

#define PMIC_OCP_NONE     (0)
#define PMIC_OCP_HANDLED  (1)

#define SUPPLY_SD       "ldo16"
#define SUPPLY_SD_IO     "ldo9"
#define SUPPLY_SPEAKER  "classd"

#define INVALID_REG_ADDR 0xDEAD
#define CLOSE_REGULATOR_CONTROL 0x00
#define PMU_REG_WIDTH (8)

typedef enum
{
    PMIC_HEALTH_STATUS_NORMAL,
    PMIC_HEALTH_OCP_EXCH_HAPPENED,
    PMIC_HEALTH_RECORD_EXCH_HAPPENED,
}PMIC_STATUS_TYPE_ENUM;

typedef struct
{
    unsigned int inacceptable_event;
    char** event_bit_name;
    unsigned int *event_ops_reg;
}PMIC_EXCH_REG;

typedef struct
{
    unsigned int addr;
    unsigned int shift;
    unsigned int mask;
}PMIC_REG_CTRL;

struct special_ocp_attr
{
    char *power_name;
    pmic_ocp_callback handler;
    struct special_ocp_attr *next;
};

typedef struct
{
    int health;
    unsigned int data_width;
    struct kobject *mntn_kobj;

    /*Over Temperature Handle*/
    int otmp_irq;
    unsigned int  otmp_thshd_val;
    PMIC_REG_CTRL otmp_thshd_reg;
    struct workqueue_struct *otmp_wq;
    struct work_struct otmp_wk;

    /*SMPL Function*/
    unsigned int  smpl_en_val;
    PMIC_REG_CTRL smpl_en_reg;
    unsigned int  smpl_tm_val;
    PMIC_REG_CTRL smpl_tm_reg;

    /*SCP/OCP Handle*/
    int ocp_irq;
    unsigned int ocp_reg_n;
    unsigned int *ocp_regs;
    unsigned int reset_when_ocp_n;
    unsigned int *reset_when_ocp;
    unsigned int *ocp_event_buff;
    PMIC_EXCH_REG *ocp_exch_desc;
    struct workqueue_struct *ocp_wq;
    struct work_struct ocp_wk;
    struct special_ocp_attr *ocp_list_head;
    struct special_ocp_attr *ocp_list_tail;

    /*Event Record*/
    unsigned int record_reg_n;
    unsigned int *record_regs;
    unsigned int *record_event_buff;
    PMIC_EXCH_REG *record_exch_desc;

    /*Log*/
    char *init_log_show;
    char *irq_log_show;

    /*ldo buck ocp mold ctrl*/
    int ocp_mold_switch;
    unsigned int ocp_ctrl_n;
    unsigned int *ocp_ctrl_regs;
    unsigned int *ocp_ctrl_val;

    /*pmu record key register*/
    unsigned int pmu_record_reg_n;
    unsigned int *pmu_record_regs;
}PMIC_MNTN_DESC;

#endif
