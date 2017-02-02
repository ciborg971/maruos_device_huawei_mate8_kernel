#include <linux/init.h>
#include <linux/suspend.h>
#include <linux/syscore_ops.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/err.h>
#include <asm/suspend.h>
#include <linux/platform_device.h>
#include <linux/cpu_pm.h>
#include <asm/cputype.h>
#include <linux/hw_power_monitor.h>

#define POWER_STATE_TYPE_SYS_SUSPEND	3

/*lint -e750 -esym(750,*) */
#ifdef CONFIG_ARCH_HI6250
#define REG_SCBAKDATA8_OFFSET			(0x42C)
#define REG_SCBAKDATA9_OFFSET			(0x430)
#else
#define REG_SCBAKDATA8_OFFSET			(0x334)
#define REG_SCBAKDATA9_OFFSET			(0x338)
#endif
#define CPUIDLE_FLAG_REG(cluster)		((cluster == 0) ? REG_SCBAKDATA8_OFFSET :  REG_SCBAKDATA9_OFFSET)


#define AP_SUSPEND_FLAG					BIT(16)

#define GIC_ENABLE_OFFSET					(0x100)
#define GIC_PENDING_OFFSET					(0x200)
#define IRQ_NUM_MAX		(320)
#define IRQ_GROUP_MAX		(10)
#define IRQ_NUM_PER_WORD	(32)

/* FIXME: need to distinguish diff platform */
#define	AO_GPIO_GROUP		(22)
#define	AO_GPIO_GROUP_NUM	(6)
#define	AO_GPIO_IRQ_BASE	(138)

#define NO_SEQFILE 0

extern void pm_status_show(struct seq_file *s);
extern void pm_nvic_pending_dump(void);
#ifdef CONFIG_HISI_SR_DEBUG
extern void dbg_io_status_show(void);
extern void dbg_pmu_status_show(void);
extern void dbg_clk_status_show(void);
#endif

static void __iomem *sysctrl_base;
static void __iomem *g_enable_base;
static void __iomem *g_pending_base;
static void __iomem *crgctrl_base_addr = NULL;
static unsigned int g_enable_value[10];
static void __iomem *ao_gpio_base[AO_GPIO_GROUP_NUM];
static unsigned int g_plat_flag = 0; /* diff from FPGA and asic, 1: FPGA 0: asic */

char *irq_name[IRQ_NUM_MAX] = {
	"IPI_RESCHEDULE",	/* 0 */
	"IPI_CALL_FUNC",	/* 1 */
	"IPI_CALL_FUNC_SINGLE",	/* 2 */
	"IPI_CPU_STOP",		/* 3 */
	"IPI_TIMER",		/* 4 */
	NULL,		/* 5 */
	NULL,		/* 6 */
	NULL,		/* 7 */
	NULL,		/* 8 */
	NULL,		/* 9 */
	NULL,		/* 10 */
	NULL,		/* 11 */
	NULL,		/* 12 */
	NULL,		/* 13 */
	NULL,		/* 14 */
	NULL,		/* 15 */
	NULL,		/* 16 */
	NULL,		/* 17 */
	NULL,		/* 18 */
	NULL,		/* 19 */
	NULL,		/* 20 */
	NULL,		/* 21 */
	NULL,		/* 22 */
	NULL,		/* 23 */
	NULL,		/* 24 */
	"Virtual maintenance interrupt",	/* 25 */
	"Hypervisor timer",			/* 26 */
	"Virtual timer",			/* 27 */
	"Legacy FIQ signal",			/* 28 */
	"Secure physical timer",		/* 29 */
	"Non-secure physical timer",		/* 30 */
	"Legacy IRQ signal",			/* 31 */
	"Maia_interr",                 /* 32  */
	"Maia_exterr",                 /* 33  */
	"Maia_pmu0",                   /* 34  */
	"Maia_pmu1",                   /* 35  */
	"Maia_pmu2",                   /* 36  */
	"Maia_pmu3",                   /* 37  */
	"Maia_cti0",                   /* 38  */
	"Maia_cti1",                   /* 39  */
	"Maia_cti2",                   /* 40  */
	"Maia_cti3",                   /* 41  */
	"Maia_COMMRX0",                /* 42  */
	"Maia_COMMRX1",                /* 43  */
	"Maia_COMMRX2",                /* 44  */
	"Maia_COMMRX3",                /* 45  */
	"Maia_COMMTX0",                /* 46  */
	"Maia_COMMTX1",                /* 47  */
	"Maia_COMMTX2",                /* 48  */
	"Maia_COMMTX3",                /* 49  */
	"Maia_COMMIRQ0",               /* 50  */
	"Maia_COMMIRQ1",               /* 51  */
	"Maia_COMMIRQ2",               /* 52  */
	"Maia_COMMIRQ3",               /* 53  */
	"A53_interr",                  /* 54  */
	"A53_exterr",                  /* 55  */
	"A53_pmu0",                    /* 56  */
	"A53_pmu1",                    /* 57  */
	"A53_pmu2",                    /* 58  */
	"A53_pmu3",                    /* 59  */
	"A53_cti0",                    /* 60  */
	"A53_cti1",                    /* 61  */
	"A53_cti2",                    /* 62  */
	"A53_cti3",                    /* 63  */
	"A53_COMMRX0",                 /* 64  */
	"A53_COMMRX1",                 /* 65  */
	"A53_COMMRX2",                 /* 66  */
	"A53_COMMRX3",                 /* 67  */
	"A53_COMMTX0",                 /* 68  */
	"A53_COMMTX1",                 /* 69  */
	"A53_COMMTX2",                 /* 70  */
	"A53_COMMTX3",                 /* 71  */
	"A53_COMMIRQ0",                /* 72  */
	"A53_COMMIRQ1",                /* 73  */
	"A53_COMMIRQ2",                /* 74  */
	"A53_COMMIRQ3",                /* 75  */
	"WatchDog0",                   /* 76  */
	"WatchDog1",                   /* 77  */
	"RTC0",                        /* 78  */
	"RTC1",                        /* 79  */
	"TIME00",                      /* 80  */
	"TIME01",                      /* 81  */
	"TIME10",                      /* 82  */
	"TIME11",                      /* 83  */
	"TIME20",                      /* 84  */
	"TIME21",                      /* 85  */
	"TIME30",                      /* 86  */
	"TIME31",                       /* 87  */
	"TIME40",                      /* 88  */
	"TIME41",                      /* 89  */
	"TIME50",                      /* 90  */
	"TIME51",                      /* 91  */
	"TIME60",                      /* 92  */
	"TIME61",                      /* 93  */
	"TIME70",                      /* 94  */
	"TIME71",                      /* 95  */
	"TIME80",                      /* 96  */
	"TIME81",                      /* 97  */
	"TIME90",                      /* 98  */
	"TIME91",                      /* 99  */
	"TIME100",                     /* 100 */
	"TIME101",                     /* 101 */
	"TIME110",                     /* 102 */
	"TIME111",                     /* 103 */
	"TIME120",                     /* 104 */
	"TIME121",                     /* 105 */
	"UART0",                       /* 106 */
	"UART1",                       /* 107 */
	"UART2",                       /* 108 */
	"UART4",                       /* 109 */
	"UART5",                       /* 110 */
	"UART6",                       /* 111 */
	"SPI1",                        /* 112 */
	"I2C3",                        /* 113 */
	"I2C4",                        /* 114 */
	"I2C5(PMU_I2C)",               /* 115 */
	"GPIO0[]",                     /* 116 */
	"GPIO1[]",                     /* 117 */
	"GPIO2[]",                     /* 118 */
	"GPIO3[]",                     /* 119 */
	"GPIO4[]",                     /* 120 */
	"GPIO5[]",                     /* 121 */
	"GPIO6[]",                     /* 122 */
	"GPIO7[]",                     /* 123 */
	"GPIO8[]",                     /* 124 */
	"GPIO9[]",                     /* 125 */
	"GPIO10[]",                    /* 126 */
	"GPIO11[]",                    /* 127 */
	"GPIO12[]",                    /* 128 */
	"GPIO13[]",                    /* 129 */
	"GPIO14[]",                    /* 130 */
	"GPIO15[]",                    /* 131 */
	"GPIO16[]",                    /* 132 */
	"GPIO17[]",                    /* 133 */
	"GPIO18[]",                    /* 134 */
	"GPIO19[]",                    /* 135 */
	"GPIO20[]",                    /* 136 */
	"GPIO21[]",                    /* 137 */
	"GPIO22[]",                    /* 138 */
	"GPIO23[]",                    /* 139 */
	"GPIO24[]",                    /* 140 */
	"GPIO25[]",                    /* 141 */
	"GPIO26[]",                    /* 142 */
	"GPIO27[]",                    /* 143 */
	"IOMCU_WD",                    /* 144 */
	"IOMCU_SPI",                   /* 145 */
	"IOMCU_UART3",                 /* 146 */
	"IOMCU_UART8",                 /* 147 */
	"IOMCU_SPI2",                  /* 148 */
	"IOMCU_I2C3",                  /* 149 */
	"IOMCU_I2C0",                  /* 150 */
	"IOMCU_I2C1",                  /* 151 */
	"IOMCU_I2C2",                  /* 152 */
	"IOMCU_GPIO0_INT1",            /* 153 */
	"IOMCU_GPIO1_INT1",            /* 154 */
	"IOMCU_GPIO2_INT1",            /* 155 */
	"IOMCU_GPIO3_INT1",            /* 156 */
	"IOMCU_DMAC_INT0",             /* 157 */
	"IOMCU_DMAC_ns_INT0",          /* 158 */
	"PERF_STAT",                   /* 159 */
	"IOMCU_COMB",                  /* 160 */
	"IOMCU_BLPWM",                 /* 161 */
	"NOC-comb",                    /* 162 */
	"intr_dmss",                   /* 163 */
	"intr_ddrc0_err",              /* 164 */
	"intr_ddrc1_err",              /* 165 */
	"PMCTRL",                      /* 166 */
	"SECENG_P",                    /* 167 */
	"SECENG_S",                    /* 168 */
	"EMMC0",                       /* 169 */
	"EMMC1",                       /* 170 */
	"SD3",                         /* 171 */
	"SDIO0",                       /* 172 */
	"SDIO1",                       /* 173 */
	"DMAC_int0",                   /* 174 */
	"DMAC_ns_int0",                /* 175 */
	"CLK_MONITOR",                 /* 176 */
	"TSENSOR_Maia",                /* 177 */
	"TSENSOR_A53",                 /* 178 */
	"TSENSOR_G3D",                 /* 179 */
	"TSENSOR_Modem",               /* 180 */
	"ASP_ARM_SECURE",              /* 181 */
	"ASP_ARM",                     /* 182 */
	"VDM_INT2",                    /* 183 */
	"VDM_INT0",                    /* 184 */
	"VDM_INT1",                    /* 185 */
	"MODEM_IPC0[0]",               /* 186 */
	"MODEM_IPC1[0]",               /* 187 */
	"MDM_bus_err",                 /* 188 */
	"MDM_EDMAC[3]",                /* 189 */
	"MDM_EDMAC_NS[3]",             /* 190 */
	"USB3[0]",                     /* 191 */
	"USB3[1]",                     /* 192 */
	"USB3_OTG",                    /* 193 */
	"USB3_BC",                     /* 194 */
	"PMC-DDRC-DFS",                /* 195 */
	"Reserved",                    /* 196 */
	"PMC-DVFS-Maia",               /* 197 */
	"PMC-DVFS-A53",                /* 198 */
	"PMC-DVFS-G3D",                /* 199 */
	"PMC-AVS-Maia",                /* 200 */
	"PMC-AVS-A53",                 /* 201 */
	"PMC-AVS-G3D",                 /* 202 */
	"PMC-AVS-IDLE-Maia",           /* 203 */
	"PMC-AVS-IDLE-A53",            /* 204 */
	"PMC-AVS-IDLE-G3D",            /* 205 */
	"M3_LP_wd",                    /* 206 */
	"CCI400_err",                  /* 207 */
	"CCI400_overflow",             /* 208 */
	"CCI400_overflow[4]",          /* 209 */
	"IPC_S_int0",                  /* 210 */
	"IPC_S_int1",                  /* 211 */
	"IPC_S_int4",                  /* 212 */
	"IPC_S_mbx0",                  /* 213 */
	"IPC_S_mbx1",                  /* 214 */
	"IPC_S_mbx2",                  /* 215 */
	"IPC_S_mbx3",                  /* 216 */
	"IPC_S_mbx4",                  /* 217 */
	"IPC_S_mbx5",                  /* 218 */
	"IPC_S_mbx6",                  /* 219 */
	"IPC_S_mbx7",                  /* 220 */
	"IPC_S_mbx8",                  /* 221 */
	"IPC_S_mbx9",                  /* 222 */
	"IPC_S_mbx18",                 /* 223 */
	"IPC_NS_int0",                 /* 224 */
	"IPC_NS_int1",                 /* 225 */
	"IPC_NS_int4",                 /* 226 */
	"IPC_NS_int5",                 /* 227 */
	"IPC_NS_int6",                 /* 228 */
	"IPC_NS_mbx0",                 /* 229 */
	"IPC_NS_mbx1",                 /* 230 */
	"IPC_NS_mbx2",                 /* 231 */
	"IPC_NS_mbx3",                 /* 232 */
	"IPC_NS_mbx4",                 /* 233 */
	"IPC_NS_mbx5",                 /* 234 */
	"IPC_NS_mbx6",                 /* 235 */
	"IPC_NS_mbx7",                 /* 236 */
	"IPC_NS_mbx8",                 /* 237 */
	"IPC_NS_mbx9",                 /* 238 */
	"IPC_NS_mbx18",                /* 239 */
	"aximon_cpufast_intr",         /* 240 */
	"MDM_WDOG_intr",               /* 241 */
	"ASP-IPC-ARM",                 /* 242 */
	"ASP-IPC-MCPU",                /* 243 */
	"ASP-IPC-BBE16",               /* 244 */
	"ASP_WD",                      /* 245 */
	"ASP_AXI_DLOCK",               /* 246 */
	"ASP_DMA_SECURE",              /* 247 */
	"ASP_DMA_SECURE_N",            /* 248 */
	"SCI0",                        /* 249 */
	"SCI1",                        /* 250 */
	"SOCP0",                       /* 251 */
	"SOCP1",                       /* 252 */
	"MDM_IPF_intr0",               /* 253 */
	"MDM_IPF_intr1",               /* 254 */
	"ddrc_fatal_int[3:0]",         /* 255 */
	"Reserved",                    /* 256 */
	"MDM_UICC_intr",               /* 257 */
	"GIC_IRQ_OUT[0]",              /* 258 */
	"GIC_IRQ_OUT[1]",              /* 259 */
	"GIC_IRQ_OUT[2]",              /* 260 */
	"GIC_IRQ_OUT[3]",              /* 261 */
	"GIC_IRQ_OUT[4]",              /* 262 */
	"GIC_IRQ_OUT[5]",              /* 263 */
	"GIC_IRQ_OUT[6]",              /* 264 */
	"GIC_IRQ_OUT[7]",              /* 265 */
	"GIC_FIQ_OUT[0]",              /* 266 */
	"GIC_FIQ_OUT[1]",              /* 267 */
	"GIC_FIQ_OUT[2]",              /* 268 */
	"GIC_FIQ_OUT[3]",              /* 269 */
	"GIC_FIQ_OUT[4]",              /* 270 */
	"GIC_FIQ_OUT[5]",              /* 271 */
	"GIC_FIQ_OUT[6]",              /* 272 */
	"GIC_FIQ_OUT[7]",              /* 273 */
	"NANDC",                       /* 274 */
	"CoreSight_ETR_Full",          /* 275 */
	"CoreSight_ETF_Full",          /* 276 */
	"DSS-pdp",                     /* 277 */
	"DSS-sdp",                     /* 278 */
	"DSS-offline",                 /* 279 */
	"DSS_mcu_pdp",                 /* 280 */
	"DSS_mcu_sdp",                 /* 281 */
	"DSS_mcu_offline",             /* 282 */
	"DSS_dsi0",                    /* 283 */
	"DSS_dsi1",                    /* 284 */
	"IVP32_SMMU_irpt_s",           /* 285 */
	"IVP32_SMMU_irpt_ns",          /* 286 */
	"IVP32_WATCH_DOG",             /* 287 */
	"VENC",                        /* 288 */
	"VDEC",                        /* 289 */
	"G3D_JOB",                     /* 290 */
	"G3D_MMU",                     /* 291 */
	"G3D_GPU",                     /* 292 */
	"isp_irq[0]",                  /* 293 */
	"isp_irq[1]",                  /* 294 */
	"isp_irq[2]",                  /* 295 */
	"isp_irq[3]",                  /* 296 */
	"isp_irq[4]",                  /* 297 */
	"isp_irq[5]",                  /* 298 */
	"isp_irq[6]",                  /* 299 */
	"isp_irq[7]",                  /* 300 */
	"isp_a7_to_gic_mbx_int[0]",    /* 301 */
	"isp_a7_to_gic_mbx_int[1]",    /* 302 */
	"isp_a7_to_gic_ipc_int",       /* 303 */
	"isp_a7_watchdog_int",         /* 304 */
	"isp_axi_dlcok",               /* 305 */
	"isp_axi_irq_out",             /* 306 */
	"ivp32_dwaxi_dlock_irq",       /* 307 */
	"mmbuf_asc0",                  /* 308 */
	"mmbuf_asc1",                  /* 309 */
	"reserved",                    /* 310 */
	"reserved",                    /* 311 */
	"reserved",                    /* 312 */
	"reserved",                    /* 313 */
	"reserved",                    /* 314 */
	"reserved",                    /* 315 */
	"reserved",                    /* 316 */
	"reserved",                    /* 317 */
	"reserved",                    /* 318 */
	"reserved",                    /* 319 */
};

static int pm_ao_gpio_irq_dump(unsigned int irq_num)
{
	int i, group, data;

	group = (int)irq_num - AO_GPIO_IRQ_BASE;
	if (group >= AO_GPIO_GROUP_NUM || group < 0)
		return -EINVAL;

	data = readl(ao_gpio_base[group] + 0x410)
			& readl(ao_gpio_base[group] + 0x418);

	for (i = 0; i < 8; i++)
		if (data & BIT(i))
			return ((group + AO_GPIO_GROUP) * 8 + i);

	return  -EINVAL;
}

void pm_gic_dump(void)
{
	unsigned int i;

	for (i = 2; i < IRQ_GROUP_MAX; i++)
		g_enable_value[i] = readl(g_enable_base + i * 4);
}

void pm_gic_pending_dump(void)
{
	unsigned int i;
	unsigned int j;
	unsigned int value;
	unsigned int irq;
	int gpio;

	for (i = 2; i < IRQ_GROUP_MAX; i++) {
		value = readl(g_pending_base + i * 4);

		for (j = 0; j < IRQ_NUM_PER_WORD; j++) {
			if ((value & BIT_MASK(j)) && ((value & BIT_MASK(j)) == (g_enable_value[i] & BIT_MASK(j)))) {
				irq = i * IRQ_NUM_PER_WORD + j;
				printk("wake up irq num: %d, irq name: %s", irq, irq_name[irq]);
                power_monitor_report(WAKEUP_IRQ,"%s",irq_name[irq]);
				gpio = pm_ao_gpio_irq_dump(irq);
				if (gpio >= 0)
				{
					printk("(gpio-%d)", gpio);
                    power_monitor_report(WAKEUP_GPIO,"%d",gpio);
				}
				printk("\n");
			}
		}
	}
}

void hisi_set_ap_suspend_flag(unsigned int cluster)
{
	unsigned int val;

	/* do not need lock, as the core is only one now. */
	val = readl(sysctrl_base + CPUIDLE_FLAG_REG(cluster));
	val |= AP_SUSPEND_FLAG;
	writel(val, sysctrl_base + CPUIDLE_FLAG_REG(cluster));
}

void hisi_clear_ap_suspend_flag(unsigned int cluster)
{
	unsigned int val;

	/* do not need lock, as the core is only one now. */
	val = readl(sysctrl_base + CPUIDLE_FLAG_REG(cluster));
	val &= ~AP_SUSPEND_FLAG;
	writel(val, sysctrl_base + CPUIDLE_FLAG_REG(cluster));
}

#ifdef CONFIG_HISI_SR_DEBUG
extern void debuguart_reinit(void);
#endif

#define COREPWRACK_MASK (0x7F800)
#define PERPWRACK_OFFSET (0x15c)


static int hisi_test_pwrdn_othercores(unsigned int cluster, unsigned int core)
{
	unsigned int pwrack_stat = 0;
	unsigned int mask = 0;

#ifdef CONFIG_ARCH_HI6250
	/* NOTE!! ONLY FOR FPGA */
	if (1 == g_plat_flag) {
		if (0 == cluster)
			return (readl(crgctrl_base_addr + 0x318) != 0x0);
		else
			return (readl(crgctrl_base_addr + 0x278) != 0x0);
	}
#endif

	/* boot core mask */
	mask = (0x1 << (11 + cluster * 4 + core));
	pwrack_stat = readl(crgctrl_base_addr + PERPWRACK_OFFSET);
	/* non boot core mask */
	mask = COREPWRACK_MASK & (~mask);
	pwrack_stat &= mask;

	return pwrack_stat;
}

static int hisi_3xxx_pm_enter(suspend_state_t state)
{
	unsigned int cluster = 0;
	unsigned int core = 0;
	unsigned long mpidr = read_cpuid_mpidr();

	pr_err("%s ++\n", __func__);

	cluster = (mpidr >> 8) & 0xff;
	core = mpidr & 0xff;

	pm_gic_dump();
#ifdef CONFIG_HISI_SR_DEBUG
	dbg_io_status_show();
	dbg_pmu_status_show();
	dbg_clk_status_show();
#endif
	while (hisi_test_pwrdn_othercores(cluster, core))
		;
	hisi_set_ap_suspend_flag(cluster);
	cpu_cluster_pm_enter();
	cpu_suspend(POWER_STATE_TYPE_SYS_SUSPEND);
#ifdef CONFIG_HISI_SR_DEBUG
	debuguart_reinit();
#endif
	cpu_cluster_pm_exit();
	hisi_clear_ap_suspend_flag(cluster);
#ifdef CONFIG_HISI_SR_DEBUG
	pm_gic_pending_dump();
	pm_status_show(NO_SEQFILE);
#endif
	pr_err("%s --\n", __func__);

	return 0;
}

static const struct platform_suspend_ops hi3xxx_pm_ops = {
	.enter		= hisi_3xxx_pm_enter,
	.valid		= suspend_valid_only_mem,
};

static int hisi_get_gic_base(void)
{
	void __iomem *hisi_gic_dist_base;
	struct device_node *node;

	node = of_find_compatible_node(NULL, NULL, "arm,cortex-a9-gic");
	if (!node) {
		pr_err("%s: hisilicon,gic No compatible node found\n", __func__);
		return -ENODEV;
	}

	hisi_gic_dist_base = of_iomap(node, 0);
	if (!hisi_gic_dist_base) {
		pr_err("%s: hisilicon,gic_dist_base is NULL\n", __func__);
		return -ENODEV;
	}

	pr_info("hisi_gic_dist_base = %p\n", hisi_gic_dist_base);

	g_enable_base = hisi_gic_dist_base + GIC_ENABLE_OFFSET;
	g_pending_base = hisi_gic_dist_base + GIC_PENDING_OFFSET;

	return 0;
}

static int hisi_get_gpio_regs(void)
{
	int i;
	struct device_node *np = NULL;
	char *io_buffer;

	io_buffer = (char *)kmalloc(40 * sizeof(char), GFP_KERNEL);
	if (!io_buffer)
		return -ENOMEM;

	for (i = 0; i < AO_GPIO_GROUP_NUM; i++) {
		memset(io_buffer, 0, 40*sizeof(char));
		snprintf(io_buffer,40*sizeof(char), "arm,primecell%d", i + AO_GPIO_GROUP);
		np = of_find_compatible_node(NULL, NULL, io_buffer);
		if (!np) {
			pr_err("%s: hisilicon,primecell%d No compatible node found\n", __func__, i + AO_GPIO_GROUP);
			goto err_free_buffer;
		}

		ao_gpio_base[i] = of_iomap(np, 0);
		if (!ao_gpio_base[i])
			goto err_put_node;

		of_node_put(np);
		if ((AO_GPIO_GROUP_NUM - 1) == i)
			pr_info("%s find ao gpio group num:%d\n", __func__, i + 1);
	}

	kfree(io_buffer);
	io_buffer = NULL;
	return 0;
err_put_node:
	of_node_put(np);
err_free_buffer:
	kfree(io_buffer);
	return -ENODEV;
}

static __init int hi3xxx_pm_drvinit(void)
{
	struct device_node *np = NULL;
	int ret = 0;

	if (hisi_get_gpio_regs()) {
		pr_err("%s: hisilicon,get gpio base failed!\n", __func__);
		return -ENODEV;
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,lowpm_test");
	if (!np) {
		pr_err("%s: hisilicon,lowpm_test No compatible node found\n", __func__);
		return -ENODEV;
	}

	ret = of_property_read_u32_array(np, "sr_plat_flag", &g_plat_flag, 1);
	if (ret) {
		pr_err("%s, no sr_plat_flag!\n", __func__);
	}

	np = of_find_compatible_node(NULL, NULL, "hisilicon,sysctrl");
	if (!np) {
		pr_err("%s: hisilicon,sysctrl No compatible node found\n", __func__);
		return -ENODEV;
	}

	sysctrl_base = of_iomap(np, 0);
	if (!sysctrl_base) {
		pr_err("%s: hisilicon,sysctrl_base is NULL\n", __func__);
		return -ENODEV;
	}

	of_node_put(np);

	np = of_find_compatible_node(NULL, NULL, "hisilicon,crgctrl");
	if (!np) {
		pr_info("%s: hisilicon,crgctrl No compatible node found\n", __func__);
		return -ENODEV;
	}

	crgctrl_base_addr = of_iomap(np, 0);
	if (!crgctrl_base_addr) {
		pr_err("%s: hisilicon,crgctrl_base_addr is NULL\n", __func__);
		return -ENODEV;
	}

	of_node_put(np);

	if (hisi_get_gic_base()) {
		pr_err("%s: hisilicon,get gic base failed!\n", __func__);
		return -ENODEV;
	}

	suspend_set_ops(&hi3xxx_pm_ops);

	return 0;
}
arch_initcall(hi3xxx_pm_drvinit);
