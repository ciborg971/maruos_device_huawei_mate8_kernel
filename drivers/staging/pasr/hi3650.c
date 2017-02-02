/*
 * Device driver for regulators in Hi6421 IC
 *
 * Copyright (C) 2013 Linaro Ltd. Guodong Xu <guodong.xu@linaro.org>
 *
 * Porting to hi3650 by Young Choi.
 * Copyright (C) 2014 Hisilicon, Young Choi <cuiyong1@hisilicon.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */
#include <linux/io.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/platform_device.h>
#include <linux/pasr.h>
#include <linux/device.h>
#include <linux/of.h>
#include <linux/of_platform.h>
#include <linux/of_irq.h>
#include <linux/of_device.h>
#include <linux/of_address.h>
#include <linux/hwspinlock.h>

/*#define PASR_DEBUG pr_err*/
#define PASR_DEBUG(...) 

#define ACCESS_DDR_MR17_BY_AP

#define MASK_BTYE(n)                        (0xFF << (n * 8))
#define CLEAR_BYTE(n)                       (~(0xFF << (n * 8)))
#define SCBAKDATA(n)                        (0x314 + ((n) << 2))

#define RANK_DISABLE(n)                     (1 << n)
#define SFC_RANK(n)                         (1 << (n + 16))
#define SFC_CMD_REQ                         (1)
#define SFC_MR8                             (8)
#define SFC_MR17                            (17)
#define SFC_LOAD_MR                         (2)
#define SFC_READ_MR                         (7)
#define DDR_MR8_DENSITY_OFF                 (2)
#define DDR_MR8_DENSITY_MASK                (0xF << DDR_MR8_DENSITY_OFF)
#define DDR_RANK_NR_OFF                     (20)
#define DDR_RANK_NR_MASK                    (0x3 << DDR_RANK_NR_OFF)
#define DDR_RANK_SIZE_512M                  (0x20000000)
#define DDR_RANK_SIZE_1024M                 (0x40000000)
#define DDR_RANK_SIZE_1536M                 (0x60000000)
#define DDR_RANK_SIZE_2048M                 (0x80000000)
#define DDR_MR17_MASK                       (0xFF)
#define DDR_MR17_RANK0_512M_MASK            (0x00)
#define DDR_MR17_RANK0_1024M_MASK           (0x00)
#define DDR_MR17_RANK0_1536M_MASK           (0x00)
#define DDR_MR17_RANK0_2048M_MASK           (0x00)
#define DDR_HWLOCK_ID                       (22)
#define DDR_HWLOCK_TIMEOUT                  (1000)

#define DDRC_DMC_OFFSET                     (0x8000)
#define DDRC_CFG_WORKMODE2(n)               (DDRC_DMC_OFFSET + ((n) * 0x1000) + 0x044)
#define DDRC_CFG_DDRMODE(n)                 (DDRC_DMC_OFFSET + ((n) * 0x1000) + 0x050)
#define DDRC_CFG_SFC(n)                     (DDRC_DMC_OFFSET + ((n) * 0x1000) + 0x210)
#define DDRC_CFG_SFC_ADDR1(n)               (DDRC_DMC_OFFSET + ((n) * 0x1000) + 0x218)
#define DDRC_HIS_SFC_RDATA0(n)              (DDRC_DMC_OFFSET + ((n) * 0x1000) + 0x4A8)
#define DDRC_CTRL_SFC(n)                    (DDRC_DMC_OFFSET + ((n) * 0x1000) + 0x00C)


/* new macro start */
#include <soc_acpu_baseaddr_interface.h>
#include <soc_ddrc_dmc_interface.h>
#include <soc_sctrl_interface.h>

/* new macro end */
 
struct pasr_fw {
	struct pasr_map *map;
};
extern struct pasr_fw pasr;

enum DDR_TYPE
{
	DDR_TYPE_LPDDR3=3,
	DDR_TYPE_LPDDR4=4,
	DDR_TYPE_UNKNOWN,
};

struct ddr_rank_info {
	u32 addr;
	u32 size;
	u32 memreg;
};

static u32 ddr_type=DDR_TYPE_UNKNOWN;

static struct hwspinlock *ddr_hwlock = NULL;
static void __iomem *ddrc_dmc_base[2][2] = {{0,0},{0,0}};
static void __iomem *sctrl_base = 0;
static spinlock_t pasr_lock;

#ifndef ACCESS_DDR_MR17_BY_AP
static void __iomem *sysctrl_base = NULL;
#endif

static long long rank_nr = 0;
static struct ddr_rank_info rank_info[PASR_MAX_DIE_NR];

static ssize_t show_mem_regs(struct device *dev,
			struct device_attribute *devattr, char *buf);

static DEVICE_ATTR(memregs, S_IRUGO, show_mem_regs, NULL);

static struct attribute *hi3650_pasr_attributes[] = {
	&dev_attr_memregs.attr,
	NULL,
};

static const struct attribute_group hi3650_attr_group = {
	.attrs = hi3650_pasr_attributes,
};

static ssize_t show_mem_regs(struct device *dev,
			struct device_attribute *devattr, char *buf)
{
	struct ddr_rank_info *info;
	int size = 0;
	long long i;

	for(i = 0; i < rank_nr; i++) {
		info = &rank_info[i];
		size += snprintf(buf + size, PAGE_SIZE / rank_nr,
			"%s: rank%lld addr=0x%08x, size = 0x%08x, mem_reg = 0x%08x\n",
			__func__, i, info->addr, info->size, info->memreg);
	}

	return size;
}

/* rank: 0 or 1 */
static void hi3650_pasr_refresh_disable(int rank)
{
#if 1 
	u32 value;
	u32 subsys_i,dmc_j;
	if (ddr_type == DDR_TYPE_LPDDR3) {
		for(subsys_i=0;subsys_i<2;subsys_i++) {
			value = readl(ddrc_dmc_base[subsys_i][0] + 0x44) | RANK_DISABLE(rank);
			writel(value, ddrc_dmc_base[subsys_i][0] + 0x44);
		}
	} else if (ddr_type == DDR_TYPE_LPDDR4) {
		for(subsys_i=0;subsys_i<2;subsys_i++) {
			for(dmc_j=0;dmc_j<2;dmc_j++) {
				value = readl(ddrc_dmc_base[subsys_i][dmc_j] + 0x44) | RANK_DISABLE(rank);
				writel(value, ddrc_dmc_base[subsys_i][dmc_j] + 0x44);
			}
		}
	
	} else {
		pr_err("%s: unexcepted ddr_type %d \n", __func__, ddr_type);
	}

	
#endif
}

static void hi3650_pasr_refresh_enable(int rank)
{
#if 1
	u32 value;
	u32 subsys_i,dmc_j;
	if (ddr_type == DDR_TYPE_LPDDR3) {
		for(subsys_i=0;subsys_i<2;subsys_i++) {
			value = readl(ddrc_dmc_base[subsys_i][0] + 0x44) & (~RANK_DISABLE(rank));
			writel(value, ddrc_dmc_base[subsys_i][0] + 0x44);
		}
	} else if (ddr_type == DDR_TYPE_LPDDR4) {
		for(subsys_i=0;subsys_i<2;subsys_i++) {
			for(dmc_j=0;dmc_j<2;dmc_j++) {
				value = readl(ddrc_dmc_base[subsys_i][dmc_j] + 0x44) & (~RANK_DISABLE(rank));
				writel(value, ddrc_dmc_base[subsys_i][dmc_j] + 0x44);
			}
		}
	} else {
		pr_err("%s: unexcepted ddr_type %d \n", __func__, ddr_type);
	}
	
#endif
}
u32 pasr_switch_flag = 0x55667711;
static int send_sfc_cmd(u32 *cmd, u32 cmd_nr, u32 rank, u32 subsys, u32 num)
{
	volatile unsigned int tmp;
	int timeout = 500;
	int i = 0;
	PASR_DEBUG("in %s.%d start, [rank: %d subsys: %d num: %d]\n", __func__, __LINE__, rank, subsys, num);
	writel(1 << (rank + 16), ddrc_dmc_base[subsys][num] + 0x218);
	PASR_DEBUG("in %s, %d \n", __func__, __LINE__);
	for(i=0;i<cmd_nr;i++) {
		PASR_DEBUG("[0x%x, 0x%x]\n", cmd[i], ddrc_dmc_base[subsys][num]);
		writel(cmd[i], ddrc_dmc_base[subsys][num] + 0x214);
	}
	/*start sfc*/
	writel(1, ddrc_dmc_base[subsys][num] + 0x00C);
	/*wait for complete*/
	do {
		tmp = readl(ddrc_dmc_base[subsys][num] + 0x00C);
		if (timeout-- < 0) {
			pr_err("%s: wait cmd done timeout!\n", __func__);
			break;
		}
	} while( tmp & 0x1 );

	PASR_DEBUG("in %s.%d end \n", __func__, __LINE__);
	return 0; 
}

static void hi3650_pasr_send_sfc_cmd(u32* cmd, u32 cmd_nr, int rank)
{
	int subsys_i, dmc_j;
	if (ddr_type == DDR_TYPE_LPDDR3) {
		for(subsys_i=0;subsys_i<2;subsys_i++) {
			send_sfc_cmd(cmd, cmd_nr, rank, subsys_i, 0);
		}

	} else if (ddr_type == DDR_TYPE_LPDDR4) {

		for(subsys_i=0;subsys_i<2;subsys_i++) {
			for(dmc_j=0;dmc_j<2;dmc_j++) {
				send_sfc_cmd(cmd, cmd_nr, rank, subsys_i, dmc_j);
			}
		}

	} else {
		pr_err("%s: unexcepted ddr_type %d \n", __func__, ddr_type);
	}
}

static void hi3650_pasr_write_ddr_mr(u32 value , int rank, int target)
{
				 /* precharge */
	u32 cmd[2] = {0x401, 0x0};
	PASR_DEBUG("%s %d [%d, 0x%x]\n", __func__, __LINE__, rank, value);
	if (hwspin_lock_timeout(ddr_hwlock, DDR_HWLOCK_TIMEOUT)) {
		pr_err("%s: hwspinlock timeout!\n", __func__);
		return ;
	}

	hi3650_pasr_refresh_disable(rank);
	cmd[1] = 0x4640 | value << 18;
	/*cmd = ((value << 18) | (target << 8) | SFC_LOAD_MR);*/
	hi3650_pasr_send_sfc_cmd(cmd, 2, rank);
	hi3650_pasr_refresh_enable(rank);

	hwspin_unlock(ddr_hwlock);
}

#ifndef ACCESS_DDR_MR17_BY_AP
static void hi3650_pasr_write_sysctrl_reg(u32 value, int rank)
{
	u32 reg = readl(sysctrl_base + SCBAKDATA(11));
	reg &= CLEAR_BYTE(rank);
	reg |= (value << (rank * 8));
	writel(reg, sysctrl_base + SCBAKDATA(11));
}
#endif

static void hi3650_pasr_apply_mask(u32 *mem_reg, void *cookie)
{
	long long rank = (long long)cookie;
	u32 value = *mem_reg;
	PASR_DEBUG("%s: [%d,0x%x]\n", __func__, rank, value);
	if ((rank >= rank_nr) || (rank < 0)) {
		pr_err("%s: invalid rank value %lld.\n",
				__func__, rank);
		return ;
	}

	rank_info[rank].memreg = value;
	//value = hi3650_pasr_mask_reserved_ddr_region(value, rank);

#ifndef ACCESS_DDR_MR17_BY_AP
	if (sysctrl_base != NULL)
		hi3650_pasr_write_sysctrl_reg(value, rank);
#else
	if (ddr_hwlock != NULL)
		hi3650_pasr_write_ddr_mr(value, rank, SFC_MR17);
#endif
}

static void hi3650_pasr_get_rank_info(void)
{
#if 0
	int i;
	u32 size;
	unsigned long flags = 0;

	rank_nr = readl(ddrc_base + DDRC_CFG_DDRMODE(0)) & DDR_RANK_NR_MASK;
	rank_nr = (rank_nr >> DDR_RANK_NR_OFF) + 1;

	memset(rank_info, 0, sizeof(rank_info));

	for (i = 0; i < rank_nr; i++) {
		spin_lock_irqsave(&pasr_lock, flags);
		size = hi3650_pasr_get_rank_size(i);
		spin_unlock_irqrestore(&pasr_lock, flags);

		if (size == 0)
			break;

		rank_info[i].size = size;

		if (i > 0)
			rank_info[i].addr = rank_info[i-1].addr + rank_info[i-1].size;
	}
#endif

	long long i;
	rank_nr = (long long)(pasr.map)->nr_dies;
	for(i = 0; i < rank_nr; i++) {
		rank_info[i].addr =	(pasr.map)->die[i].start;
		rank_info[i].size = (pasr.map)->die[i].nr_sections * (pasr.map)->die[i].section_size;
	}

}

static int hi3650_pasr_probe(struct platform_device *pdev)
{
	struct device_node *np;
	struct device *dev = &pdev->dev;
	int err;
	long long i;
	unsigned int reg_val;

	dev_crit(dev, "%s: enter\n", __func__);
	PASR_DEBUG("%s: enter\n", __func__);

	np = dev->of_node;

#ifndef ACCESS_DDR_MR17_BY_AP
	sysctrl_base = of_iomap(np, 1);
	if (sysctrl_base == NULL) {
		dev_err(dev, "failed to iomap sysctrl regs!\n");
		return -ENXIO;
	}
#endif

#if 0
	ddrc_base = of_iomap(np, 0);
	if (ddrc_base == NULL) {
		dev_err(dev, "failed to iomap ddrc regs!\n");
		return -ENXIO;
	}
#endif
	ddrc_dmc_base[0][0] = (void *)ioremap(SOC_ACPU_DDRC_DMC_0_0_BASE_ADDR, SZ_4K);
	ddrc_dmc_base[0][1] = (void *)ioremap(SOC_ACPU_DDRC_DMC_0_1_BASE_ADDR, SZ_4K);
	ddrc_dmc_base[1][0] = (void *)ioremap(SOC_ACPU_DDRC_DMC_1_0_BASE_ADDR, SZ_4K);
	ddrc_dmc_base[1][1] = (void *)ioremap(SOC_ACPU_DDRC_DMC_1_1_BASE_ADDR, SZ_4K);

	if (ddrc_dmc_base[0][0] == NULL
	 || ddrc_dmc_base[0][1] == NULL
	 || ddrc_dmc_base[1][0] == NULL
	 || ddrc_dmc_base[1][1] == NULL) {
		dev_err(dev, "failed to iomap ddrc regs!\n");
		return -ENXIO;
	}

	sctrl_base = (void *)ioremap(SOC_ACPU_SCTRL_BASE_ADDR, SZ_4K);
	if (sctrl_base == NULL) {
		dev_err(dev, "failed to iomap sctrl regs!\n");
		return -ENXIO;
	}

	reg_val = readl(SOC_SCTRL_SCBAKDATA4_ADDR(sctrl_base)) & 0x1<<31;
	if (reg_val == 0x0) {
		ddr_type = DDR_TYPE_LPDDR3;
	} else {
		ddr_type = DDR_TYPE_LPDDR4;
	}

	PASR_DEBUG("ddr_type: ddr%d\n", ddr_type);
	PASR_DEBUG("dmc_base: 0x%x\n", (u32 *)ddrc_dmc_base[0][0]);
	PASR_DEBUG("dmc_base: 0x%x\n", (u32 *)ddrc_dmc_base[0][1]);
	PASR_DEBUG("dmc_base: 0x%x\n", (u32 *)ddrc_dmc_base[1][0]);
	PASR_DEBUG("dmc_base: 0x%x\n", (u32 *)ddrc_dmc_base[1][1]);

	spin_lock_init(&pasr_lock);

	ddr_hwlock = hwspin_lock_request_specific(DDR_HWLOCK_ID);
	if (ddr_hwlock == NULL) {
		dev_err(dev, "pasr get hwspin_lock failed\n");
		return -EBUSY;
	}

	hi3650_pasr_get_rank_info();

	for (i = 0; i < rank_nr; i++) {
		if (pasr_register_mask_function(rank_info[i].addr,
					&hi3650_pasr_apply_mask, (void *)i)) {
			dev_err(dev, "pasr register failed, rank %lld\n", i);
		}
	}

	err = sysfs_create_group(&pdev->dev.kobj, &hi3650_attr_group);
	if (err < 0) {
		dev_err(dev, "create sysfs group failed (%d)\n", err);
		return err;
	}

	dev_crit(dev, "%s: exit\n", __func__);

	return 0;
}

static int hi3650_pasr_remove(struct platform_device *pdev)
{
	return 0;
}

#ifdef CONFIG_OF
static struct of_device_id of_hi3650_pasr_match_tbl[] = {
	{
		.compatible = "hisilicon,hi3650-pasr",
	},
	{ /* end */ }
};
MODULE_DEVICE_TABLE(of, of_hi3650_pasr_match_tbl);
#endif

static struct platform_driver hi3650_pasr_driver = {
	.driver = {
		.name	= "hi3650-pasr",
		.owner	= THIS_MODULE,
#ifdef CONFIG_OF
		.of_match_table = of_match_ptr(of_hi3650_pasr_match_tbl),
#endif
	},
	.probe	= hi3650_pasr_probe,
	.remove	= hi3650_pasr_remove,
};
module_platform_driver(hi3650_pasr_driver);

MODULE_AUTHOR("Young Choi <cuiyong1@hisilicon.com>");
MODULE_DESCRIPTION("Hi3xxx PASR driver");
MODULE_LICENSE("GPL v2");
