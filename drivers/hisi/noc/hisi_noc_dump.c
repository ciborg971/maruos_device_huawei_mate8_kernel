#include <linux/module.h>
#include <linux/bitops.h>
#include <linux/io.h>
#include <linux/kernel.h>
#include <linux/interrupt.h>
#include <linux/slab.h>
#include <linux/err.h>
#include <linux/device.h>
#include <linux/of_address.h>
#include <linux/of_irq.h>
#include <linux/of_platform.h>
#include <linux/syscore_ops.h>
#include <linux/hrtimer.h>
#include <linux/ktime.h>
#include <linux/vmalloc.h>
#include <linux/sched.h>
#include <linux/debugfs.h>
#include <asm/io.h>
#include <linux/string.h>
#include <linux/clk.h>
#include <linux/hisi/util.h>
#include <linux/hisi/reset.h>
#include <linux/clk.h>

#include "hisi_noc.h"
#include "hisi_err_probe.h"
#include "hisi_noc_packet.h"
#include "hisi_noc_bus.h"
#include "hisi_noc_transcation.h"
#include "hisi_noc_dump.h"
#ifdef CONFIG_HISI_BB
#include "platform_ap/rdr_hisi_platform.h"
#endif
#include <soc_cfg_sys_noc_bus_interface.h>
#include <soc_acpu_baseaddr_interface.h>
#include <soc_pmctrl_interface.h>
#include <soc_pctrl_interface.h>
#include <soc_sctrl_interface.h>

static struct hisi_noc_device *noc_dev = NULL;

static const char *tbl_noc_dump_error_bus[NOC_DUMP_ERRPRO_BUS_NUM] = {
    "cfg_bus",
    "sys_bus",
    "dma_bus",
    "dbg_bus",
    "mmc1_bus",
    "mmc0_bus",
    "modem_bus",
/*    "dss_bus",*/
    "peri_vcodec_bus",
};

static const uint noc_dump_errprobe_offset[NOC_DUMP_ERRPRO_OFF_NUM] = {
    ERR_PORBE_FAULTEN_OFFSET,
    ERR_PORBE_ERRVLD_OFFSET,
    ERR_PORBE_ERRLOG0_OFFSET,
    ERR_PORBE_ERRLOG1_OFFSET,
    ERR_PORBE_ERRLOG3_OFFSET,
    ERR_PORBE_ERRLOG5_OFFSET,
    ERR_PORBE_ERRLOG7_OFFSET,
};

static const uint noc_dump_reg_single[]= {
    (PCTRL_PH_BASE+PCTRL_PERI_STAT2),     /* PCTRL中PERI_STAT2（0x09C）*/
    (SCTRL_PH_BASE+SCTRL_SCPERSTATUS6),     /* SCTRL中SCPERSTATUS6（0x234）*/
    (PMCTRL_PH_BASE+PMCTRL_NOC_POWER_IDLEREQ),     /* PMCTRL中NOC_POWER_IDLEREQ（0x380）*/
    (PMCTRL_PH_BASE+PMCTRL_NOC_POWER_IDLEACK),     /* PMCTRL中NOC_POWER_IDLEACK(0x384) */
    (PMCTRL_PH_BASE+PMCTRL_NOC_POWER_IDLE),     /* PMCTRL中NOC_POWER_IDLE(0x388) */
    (PMCTRL_PH_BASE+PMCTRL_PERI_INT_STAT0_OFFSET),     /* PMCTRL中PERI_INT0_STAT（0x3a4）*/
    (SCTRL_PH_BASE+SCTRL_SCPERSTATUS6),     /* SCTRL中SCPERSTATUS6（0x234）*/
};

static int noc_dump_err_log_parse(char *kn_buf, int *pt_buf_seek, struct err_probe_msg *pt_err_msg)
{
    NOC_L_D_PRT("[err_code=%d] %s\n", pt_err_msg->err_code.val, \
    pt_err_msg->err_code.pt_str);
    NOC_L_D_PRT("[opc=%d] %s\n", pt_err_msg->opc.val, \
    pt_err_msg->opc.pt_str);
    /* ERR LOG 1*/
    NOC_L_D_PRT("[init_flow=%d]: %s\n", pt_err_msg->init_flow.val,\
    pt_err_msg->init_flow.pt_str);
    NOC_L_D_PRT("[target_flow=%d]: %s\n", pt_err_msg->target_flow.val, \
    pt_err_msg->target_flow.pt_str);
    NOC_L_D_PRT("[target_subrange]: %d\n", pt_err_msg->targetsubrange);
    /* ERR LOG 3,4*/
    NOC_L_D_PRT("ADDRESS_LOW = 0x%x  (0x%x)\n", pt_err_msg->addr_low+pt_err_msg->base_addr,\
    pt_err_msg->addr_low);
    NOC_L_D_PRT("ADDRESS_HIGH = 0x%x\n", pt_err_msg->addr_high);
    /* ERR LOG 5*/
    NOC_L_D_PRT("[USER_SIGNAL = 0x%x MID: %s \n", pt_err_msg->user_signal,\
    pt_err_msg->mid_name);
    /* ERR LOG 7*/
    NOC_L_D_PRT("SECURITY = %d\n", pt_err_msg->SECURITY);
    return 0;
}

static int noc_dump_err_probe(char *kn_buf, int *pt_buf_seek)
{
    struct noc_node *node=NULL;
    int j,k;
    void __iomem *iobase=NULL;
    struct err_probe_msg err_msg;
    struct err_probe_msg *pt_err_msg = &err_msg;
    uint reg_val_buf[10];
    unsigned long pending;
    uint faulten,errvld;

    NOC_L_D_PRT("***ErrorProbe status***\n");

    pending = noc_get_irq_status(noc_dev->pctrl_base);
    for (j = 0; j < ARRAY_SIZE(tbl_noc_dump_error_bus); j++) {
        if (NULL == (node = get_probe_node(tbl_noc_dump_error_bus[j]))) {
            continue;
        }
        if (!is_noc_node_available(node)) {
            pr_err("[%s]: this node is power down, cannot access.\n", node->name);
            continue;
        }
        iobase = node->base + node->eprobe_offset;
        faulten = readl_relaxed(iobase + ERR_PORBE_FAULTEN_OFFSET);
        errvld = readl_relaxed(iobase + ERR_PORBE_ERRVLD_OFFSET);
        if (!(pending & BIT(node->eprobe_hwirq)) && !(errvld & ERR_PORBE_ERRVLD_BIT)) {
            pr_err("[%s]:no error probe happens on this node!\n", node->name);
            continue;
        }
        NOC_L_D_PRT("ERR_PORBE_BUS is [%s]\n", tbl_noc_dump_error_bus[j]);
        NOC_L_D_PRT("FAULTEN_OFFSET = 0x%x\n", faulten);
        NOC_L_D_PRT("ERR_VLD = 0x%x\n", errvld);

        for (k = 0; k < 8; k++) {
            reg_val_buf[k] = readl_relaxed(iobase + ERR_PORBE_ERRLOG0_OFFSET + 4*k);
            NOC_L_D_PRT("ERRLOG %d = 0x%08x\n", k, reg_val_buf[k]);
        }
        /* Parse error log and dump*/
        noc_err_get_msg(reg_val_buf, node->bus_id, pt_err_msg);
        noc_dump_err_log_parse(kn_buf, pt_buf_seek, pt_err_msg);
    }
    return 0;
}

static int noc_dump_prt(char *kn_buf, int *pt_buf_seek)
{
    uint reg_value,reg_val1;
/* NoPendingTrans状态 */
    NOC_L_D_PRT("***NoPendingTrans status***\n");
    reg_value = readl_relaxed(noc_dev->pctrl_base + PCTRL_PERI_STAT2);
    NOC_L_D_PRT("PCTRL_PERI_STAT2 = 0x%x\n", reg_value);
    reg_value = readl_relaxed(noc_dev->sctrl_base + SCTRL_SCPERSTATUS6);
    NOC_L_D_PRT("SCTRL_SCPERSTATUS6 = 0x%x\n", reg_value);
/* 低功耗握手状态 */
    NOC_L_D_PRT("***LowPower HandInHand***\n");
    reg_value = readl_relaxed(noc_dev->pmctrl_base + PMCTRL_NOC_POWER_IDLEREQ);
    NOC_L_D_PRT("PMCTRL_NOC_POWER_IDLEREQ = 0x%x\n", reg_value);
    reg_value = readl_relaxed(noc_dev->pmctrl_base + PMCTRL_NOC_POWER_IDLEACK);
    NOC_L_D_PRT("PMCTRL_NOC_POWER_IDLEACK = 0x%x\n", reg_value);
    reg_value = readl_relaxed(noc_dev->pmctrl_base + PMCTRL_NOC_POWER_IDLE);
    NOC_L_D_PRT("PMCTRL_NOC_POWER_IDLE = 0x%x\n", reg_value);
/* Timeout 状态 */
    NOC_L_D_PRT("***Timeout status***\n");
    reg_value = readl_relaxed(noc_dev->pmctrl_base + PMCTRL_PERI_INT_STAT0_OFFSET);
    NOC_L_D_PRT("PMCTRL_PERI_INT0_STAT = 0x%x\n", reg_value);
    reg_val1 = readl_relaxed(noc_dev->sctrl_base + SCTRL_SCPERSTATUS6);
    NOC_L_D_PRT("SCTRL_SCPERSTATUS6 = 0x%x\n", reg_val1);
/* ErrorProbe */
	if (!IS_NOC_TMOUT_HAPPEN(reg_value, reg_val1)) {
		/* Timeout happened , do not dump error probe register*/
        noc_dump_err_probe(kn_buf, pt_buf_seek);
	}

/* 地址交织粒度配置 */
    NOC_L_D_PRT("***Address interleaving status***\n");
    reg_value = readl_relaxed(noc_dev->pctrl_base + PCTRL_PERI_CTRL19);
    NOC_L_D_PRT("PCTRL_PERI_CTRL19 = 0x%x\n", reg_value);
    return 0;
}

static void __iomem *noc_get_vaddr_from_paddr(uint paddr)
{
    void __iomem * ret;
    switch (paddr) {
    case PCTRL_PH_BASE:
        ret = noc_dev->pctrl_base;
        break;
    case SCTRL_PH_BASE:
        ret = noc_dev->sctrl_base;
        break;
    case PMCTRL_PH_BASE:
        ret = noc_dev->pmctrl_base;
        break;
    default:
        ret = NULL;
        break;
    }
    return ret;
}

static int noc_dump_hi3xxx(void* dump_addr, unsigned int size)
{
    struct noc_node *node = NULL;
    int i,j;
    struct noc_dump_data *pt_dump = kzalloc(sizeof(*pt_dump), GFP_KERNEL);
    uint *ptr;
    void __iomem *iobase;
    uint ret_size = 0;
    ret_size = size;

    pr_info("noc_dump:addr=0x%llx,size=[0x%x/0x%x]", (unsigned long long)dump_addr,
            (unsigned int)sizeof(*pt_dump), size);

    if (pt_dump == NULL) {
        pr_err("noc_dump: pt_dump malloc error\n");
        goto malloc_free;
    }

    noc_dev = platform_get_drvdata(noc_get_pt_pdev());
    for (i = 0; i < (NOC_DUMP_SYNC_LEN-1); i++) {
        pt_dump->sync[i] = NOC_DUMP_SYNC_HEAD1;  /* sync head 1 */
    }
    pt_dump->sync[i] = ((NOC_DUMP_SYNC_HEAD2 & 0xFFFFFF00) | NOC_PLATFORM_ID);      /* sync head 2 */
    ptr = (uint *)&pt_dump->NopendingTrans;

    for (i = 0; i<ARRAY_SIZE(noc_dump_reg_single); i++,ptr++) {
        iobase = noc_get_vaddr_from_paddr(noc_dump_reg_single[i]&0xFFFFF000);
        if (NULL == iobase) {
            pr_err("fault paddr : 0x%x", noc_dump_reg_single[i]&0xFFFFF000);
            goto malloc_free;
        }
        *ptr = readl_relaxed(iobase + (noc_dump_reg_single[i]&0x00000FFF));
    }

	if (IS_NOC_TMOUT_HAPPEN(pt_dump->TimeoutSts.uPERI_INT0_STAT, pt_dump->TimeoutSts.uSCPERSTATUS6)) {
		/* Timeout happened , do not dump error probe register*/
		goto ERR_PROBE_DUMP_END;
	}

	/* ERR PROBE Register dumping start */
    for (i = 0; i<ARRAY_SIZE(tbl_noc_dump_error_bus); i++ ) {
        node = get_probe_node(tbl_noc_dump_error_bus[i]);
        if (NULL == node) {
            continue;
        }
        if (!is_noc_node_available(node)) {
            continue;
        }

        ptr = (u32 *)&pt_dump->ErrorProbe[i];
        *ptr++ = NOC_DUMP_NODE_EN_F;     /* enable  */
        iobase = node->base + node->eprobe_offset;
        for (j = 0; j<ARRAY_SIZE(noc_dump_errprobe_offset); j++) {
            *ptr++ = readl_relaxed(iobase +  noc_dump_errprobe_offset[j]);
        }
    }

ERR_PROBE_DUMP_END:
    pt_dump->AddrInter.uPERI_CTRL19 = readl_relaxed(noc_dev->pctrl_base+ PCTRL_PERI_CTRL19);

    for (i=0; i<NOC_DUMP_NOC_LEN; i++)
        pt_dump->tail[i] = NOC_DUMP_TAIL_NR;  /* tail */

/* copy buffer */
    if (sizeof(*pt_dump) < ret_size)
        ret_size = sizeof(*pt_dump);
/* COPY data to RDR module */
    memcpy(dump_addr, pt_dump, size);

/* Check buffer data */
    ptr = (uint*)pt_dump;
    for (i = 0; i < sizeof(*pt_dump)/16; i++) {
        pr_info("(%03d~%03d)%08x %08x %08x %08x\n", 4*i, 4*i+3, \
                    ptr[4*i], ptr[4*i+1], ptr[4*i+2], ptr[4*i+3]);
    }

malloc_free:
/* kmalloc free */
    kfree(pt_dump);
    pt_dump = NULL;
    noc_dump_prt(NULL, NULL);
    return ret_size;
}

/*
Function: noc_dump
Description: noc dump function, mainly job is recording registers value
input: void* dump_addr: address to be save to
        unsigned int size: max data size to be save
output: none
return: real data size saved
*/
static int noc_dump(void* dump_addr, unsigned int size)
{
    return noc_dump_hi3xxx(dump_addr, size);
}

/*
Function: noc_dump_init
Description: noc dump function registers to black-box module, so noc dump can be processed before reset
input: none
output: none
return: 0->success
*/
int noc_dump_init(void)
{
    int ret = -1;
#ifdef CONFIG_HISI_BB	/* function "register_module_dump_mem_func" can only be used when CONFIG_HISI_BB*/
	ret = register_module_dump_mem_func(noc_dump, "NOC", MODU_NOC);
#endif
    return ret;
}
/*END OF FILE*/

