/*
  * hisilicon perf_stat driver, hisi_perf_stat.c
  *
  * Copyright (c) 2013 Hisilicon Technologies CO., Ltd.
  *
  */

#include <asm/memory.h>
#include <asm/cacheflush.h>
#include <asm/irq_regs.h>
#include <asm/irqflags.h>
/*lint -e451*/
#include <asm/bug.h>
/*lint +e451*/
#include <asm/uaccess.h>

#include <linux/init.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_platform.h>
#include <linux/mm.h>
#include <linux/err.h>
#include <linux/clk.h>
#include <linux/device.h>
#include <linux/stddef.h>
#include <linux/types.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
#include <linux/perf_event.h>
#include <linux/bitmap.h>
#include <linux/vmalloc.h>
#include <linux/gfp.h>
#include <linux/dma-direction.h>
#include <linux/ptrace.h>
#include <linux/mutex.h>
#include <linux/printk.h>
#include <linux/wakelock.h>
#include <linux/regulator/consumer.h>
#include <linux/syscalls.h>
#include <linux/workqueue.h>
#include <soc_pmctrl_interface.h>
#include "hisi_perf_stat.h"
#include <linux/atomic.h>


static char *master_name_hi3650[PERF_PORT_NUM] =
{	"perf-dsssubsys0",/*0:dss0*/
	"perf-dsssubsys1",/*1:dss1*/
	"",/*2:cci0*/
	"",/*3:cci1*/
	"perf-g3d",/*4:gpu*/
	"",/*5:modem0*/
	"",/*6:modem1*/
	"perf-ispsubsys0",/*7:isp0*/
	"perf-ispsubsys1",/*8:isp1*/
	"perf-vdec",/*8:vdec*/
	"perf-venc",/*10:venc*/
	"perf-ivp",/*11:ivp*/
	"",/*12:system noc*/
	"perf-asp",/*13:asp*/
	"", /*14:EMMC*/
	"perf-usbotg"/*15:usbotg*/
};

static char *master_name_hi6250[PERF_PORT_NUM] =
{	"perf-dsssubsys0",/*0:dss0*/
	"perf-dsssubsys1",/*1:dss1*/
	"",/*2:cci0*/
	"",/*3:cci1*/
	"perf-g3d",/*4:gpu*/
	"",/*5:modem0*/
	"",/*6:modem1*/
	"perf-ispsubsys0",/*7:isp0*/
	"perf-ispsubsys1",/*8:isp1*/
	"perf-vdec",/*8:vdec*/
	"perf-venc",/*10:venc*/
	"",/*11:ivp*/
	"",/*12:system noc*/
	"perf-asp",/*13:asp*/
	"", /*14:EMMC*/
	""/*15:usbotg*/
};
static char** master_name = NULL;

struct perfstat_dev_info
{
    struct resource   *res;
    struct perf_event *event_bk;    /*backup when user creat a perf_event, needed when overflow called*/
    struct clk *sample_clk;
    struct regulator *perf_supply;
    struct regulator *master_supply[PERF_PORT_NUM];

    struct wake_lock wakelock;
    spinlock_t synclock;            /*sync perf_interrupt and perf_del*/

    int  status;                    /*perf_status flag, when it is set rest, interrupt returns directly*/
    int  irq;
    unsigned long sample_clk_rate;


/* hisilicon perf attibute get from dts
 event_id    : hisilicon perf event_id, when a evnet is initialized,
               we deal with the perf_event only if the evend_id matches ours.
 samp_max_tm : perf_add need it to count buff size,
               buffer_size = samp_max_time / samp_rate * per_size,
               samp_rate = 1 / sample_clk_rate * cnt.
 per_data_sz : hisilicon perf per data size,
               perf_add use it to count the per_size,
               per_size = sample_numer * per_data_sz + data_head_size.
 per_int_size  : when sampling, we should notice the user to copy the data,
               so every per_int_size we send a notice, it means we should
               config perf to generate a (list-done)interrupt every per_int_size */
    int  event_id;
    int  samp_max_tm;
    int  per_data_sz;
    int  per_int_size;
    int  sprt;
	int  vldmsk_of_sprt;
    int  samp_type;    /*HIGHSPEED : 1, NORMALSPEED : 0*/
    struct delayed_work hs_record_data_work; /*Record Data work in HighSpeed Mode*/

/*We report the sample data in each (list-done)interrupt,
  of course we should know the data start address & size.
  The fisrt start address of data is virt_addr, once a interrupt
  comes, we report PAGE_SIZE*pages_u data, then the cur_page_n += pages_u,
  so we could know the next data start address according to the cur_page_n,
  however, when cur_page_n beyonds the total page numbers(pages_n),
  it becomes zero again.
  */
    int  cur_page_n;
    int  pages_n;
    int  pages_u;
    void *virt_addr;

/*perf generates interrupt by analyzing the perf_list_descriptors,
  we config a serial of descriptors in a continuous address, and
  tell perf the first descriptor's address*/
    perf_list_descriptor *list;
    struct page **pages;
};

static struct perfstat_dev_info *perfstat_info;
static void __iomem *perfstat_base;
static bool first_data = true;
static unsigned long sample_time = 0;
static bool perf_file_saved = false;
struct completion perf_comp;
static atomic_t is_recording = ATOMIC_INIT(0);

static struct of_device_id of_perfstat_match_tbl[] = {
    {
        .compatible = "hisilicon,hi3650-perfstat-driver",
        .data = master_name_hi3650,
    },
    {
        .compatible = "hisilicon,hi6250-perfstat-driver",
        .data = master_name_hi6250,
    },

    { /* end */ }
};

#define perfstat_reg_read(reg_addr)  \
                (*(volatile int *)((char *)perfstat_base + reg_addr))
#define perfstat_reg_write(reg_addr,reg_value) \
                (*(volatile int *)((char *)perfstat_base + reg_addr) = reg_value)

static void perfstat_set_sample_cnt(int cnt)
{
    perfstat_reg_write(PERF_SAMPCNT, cnt);
}

static void perfstat_set_sample_period(int usec)
{
    int value;
    struct perfstat_dev_info *dev_info = perfstat_info;

    value = usec * (int)(dev_info->sample_clk_rate / 1000000);
    perfstat_set_sample_cnt(value);
}

static void perfstat_set_sample_num(int times)
{
    perfstat_reg_write(PERF_SAMPNUM, times);
}

static void perfstat_set_sample_port(int port)
{
    perfstat_reg_write(PERF_SAMPPORT, port);
}

static void perfstat_set_addr_mode(int mode)
{
    perfstat_reg_write(PERF_ADDRMODE, mode);
}

static int perfstat_set_list_mode_addr(int addr)
{
    if(!PERF_IS_ALIGNED(addr, 8)) {
        pr_err("[%s] 8 bytes align needed\n",__func__);
        return PERF_ERROR;
    }

    perfstat_reg_write(PERF_LISTADDR, addr);

    return PERF_OK;
}

static void perfstat_set_timeout_cnt(int cnt)
{
    perfstat_reg_write(PERF_OVERTIMECNT, cnt);
}

static void perfstat_set_timeout_duration(int msec)
{
    int value;
    struct perfstat_dev_info *dev_info = perfstat_info;

    value = msec * (int)(dev_info->sample_clk_rate / 1000);
    perfstat_set_timeout_cnt(value);
}

static void perfstat_set_monitor_reset(void)
{
    perfstat_reg_write(PERF_MONITORRST, 0x1);
}

static void perfstat_trigger_sample_start(void)
{
    perfstat_reg_write(PERF_SAMPSTART, 0x1);
}

static void perfstat_trigger_sample_stop(void)
{
    perfstat_reg_write(PERF_SAMPSTOP, 0x1);
}

static void perfstat_enable_interrupt(int type)
{
    int value;

    value = perfstat_reg_read(PERF_INTEN);
    value |= type;
    perfstat_reg_write(PERF_INTEN, value);
}

static void perfstat_clear_interrupt(int type)
{
    perfstat_reg_write(PERF_INTCLR, type);
}

static int perfstat_get_masked_int_stat(void)
{
    return perfstat_reg_read(PERF_INTMASKSTAT);
}

static int perfstat_get_cur_sample_cnt(void)
{
    return perfstat_reg_read(PERF_CURSAMPCNT);
}

static int perfstat_get_cur_data_addr(void)
{
    return perfstat_reg_read(PERF_CURSAMPADDR);
}

static int perfstat_get_cur_list_addr(void)
{
    return perfstat_reg_read(PERF_CURLIST);
}

static int perfstat_get_fifo_status(void)
{
    return perfstat_reg_read(PERF_DBGFIFOFULL);
}

static int perfstat_get_block_port(void)
{
    return perfstat_reg_read(PERF_DBGBLOCK);
}

static int perfstat_get_list_mode_addr(void)
{
    return perfstat_reg_read(PERF_LISTADDR);
}

static int perfstat_get_reset_cnt(void)
{
    return perfstat_reg_read(PERF_RSTCNT);
}

static int perfstat_get_is_sampling(void)
{
    return perfstat_reg_read(PERF_SAMPSTART);
}

static void perfstat_debug_info_show(void)
{
    int cur_samp_cnt, cur_data_addr, cur_list_addr, dbg_fifo_stat, dbg_block_port;

    cur_samp_cnt   = perfstat_get_cur_sample_cnt();
    cur_data_addr  = perfstat_get_cur_data_addr();
    cur_list_addr  = perfstat_get_cur_list_addr();
    dbg_fifo_stat  = perfstat_get_fifo_status();
    dbg_block_port = perfstat_get_block_port();

    pr_err("[%s]CurSampCnt   : 0x%x\n", __func__, cur_samp_cnt);
    pr_err("[%s]CurDataAddr  : 0x%x\n", __func__, cur_data_addr);
    pr_err("[%s]CurListAddr  : 0x%x\n", __func__, cur_list_addr);
    pr_err("[%s]DbgFIFOStat  : 0x%x\n", __func__, dbg_fifo_stat);
    pr_err("[%s]DbgBlockPort : 0x%x\n", __func__, dbg_block_port);

    return;
}

static void perfstat_list_done_handler(void)
{
    struct perfstat_dev_info *dev_info = perfstat_info;
    struct perf_sample_data data;
    struct pt_regs *regs;
    struct perf_raw_record raw;
    int page_new;
    void *start;
    int size;

    if (PERF_SAMPLE_HIGHSPEED == dev_info->samp_type) {
        if (!perf_file_saved && !atomic_read(&is_recording)) {
            pr_err("%s: save perf data...\n", __func__);
            schedule_delayed_work(&dev_info->hs_record_data_work, 0);
        }
        return;
    }

    /*count the data start_addr & size*/
    start = (void *)((char*)(dev_info->virt_addr) + PAGE_SIZE * dev_info->cur_page_n);
    page_new = dev_info->cur_page_n + dev_info->pages_u;
    if(dev_info->pages_n > page_new) {
        size = PAGE_SIZE * dev_info->pages_u;
        dev_info->cur_page_n = page_new;
    }else {
        size = PAGE_SIZE * (dev_info->pages_n - dev_info->cur_page_n);
        dev_info->cur_page_n = 0;
    }
    /*invalid data buffer to be copied*/
    __dma_map_area((const void *)start, size, DMA_FROM_DEVICE);

    regs = get_irq_regs();
    if (first_data) {
        perf_sample_data_init(&data, 0, 0);
        raw.data = &sample_time;
        raw.size = sizeof(sample_time);
        data.raw = &raw;

        if(perf_event_overflow(dev_info->event_bk,
                &data, regs)) {
            pr_err("[%s]report event fail\n",__func__);
        }
        first_data = false;
    }
    perf_sample_data_init(&data, 0, 0);
    raw.data = start;
    raw.size = size;
    data.raw = &raw;

    if(perf_event_overflow(dev_info->event_bk,
            &data, regs)) {
        pr_err("[%s]report event fail\n",__func__);
    }

    return;
}

static void perfstat_sample_done_handler(void)
{
    struct perfstat_dev_info *dev_info = perfstat_info;
    struct perf_sample_data data;
    struct pt_regs *regs;
    int i,page_idx;
    struct perf_raw_record raw;
    int cur_list_addr,list_addr,cur_data_addr;
    void *start;
    int size,offset;

    pr_err("[%s]perf sample done\n",__func__);
    perfstat_debug_info_show();
    if(!dev_info->list) {
        pr_err("[%s]no list exits\n",__func__);
        return;
    }

    /*find out the current page_idx in pages*/
    cur_list_addr = perfstat_get_cur_list_addr();
    cur_data_addr = perfstat_get_cur_data_addr();
    list_addr = (int)__virt_to_phys(dev_info->list);
    for(i = 0; i < dev_info->pages_n; i++) {
        if(list_addr == cur_list_addr)
            break;
        list_addr = list_addr + sizeof(u64);
    }
    if(unlikely(dev_info->pages_n == i)) {
        pr_err("[%s]no list addr matched\n",__func__);
        return;
    }
    else {
        page_idx = i;
    }
    /*count the data start_addr & size*/
    offset = cur_data_addr - dev_info->list[page_idx].bit_config.address;
    start = (void *)((char*)(dev_info->virt_addr) + PAGE_SIZE * dev_info->cur_page_n);
    size = PAGE_SIZE * (page_idx - dev_info->cur_page_n) + offset;
    /*invalid data buffer to be copied*/
    __dma_map_area((const void *)start, size, DMA_FROM_DEVICE);

    regs = get_irq_regs();
    perf_sample_data_init(&data, 0, 0);
    raw.data = start;
    raw.size = size;
    data.raw = &raw;

    if(perf_event_overflow(dev_info->event_bk,
            &data, regs)) {
        pr_err("[%s]report event fail\n",__func__);
    }

    return;
}

static void perfstat_list_error_handler(void)
{
    struct perfstat_dev_info *dev_info = perfstat_info;
    int val;
    perf_list_descriptor *list_cfg;

    pr_err("[%s]perf list error\n",__func__);
    perfstat_debug_info_show();

    val = perfstat_get_list_mode_addr();
    pr_err("[%s]list addr inReg is 0x%x.\n", __func__, val);
    list_cfg = dev_info->list;
    if(!list_cfg)
        pr_err("[%s]list addr inSof is null.\n",__func__);
    else
        pr_err("[%s]list addr inSof is 0x%x.\n",__func__,(int)__virt_to_phys(list_cfg));

    return;
}

static void perfstat_port_overtime_handler(void)
{
    pr_err("[%s]perf port overtime\n",__func__);
    perfstat_debug_info_show();
}

static irqreturn_t perfstat_interrupt_handler(int irq, void *data)
{
    int val;
    struct perfstat_dev_info *dev_info = (struct perfstat_dev_info *)data;

    spin_lock(&dev_info->synclock);
    if(PERF_IS_REST == dev_info->status) {
        perfstat_clear_interrupt(PERF_INT_ALL);
        goto out;
    }

    val = perfstat_get_masked_int_stat();
    if(val & PERF_INT_SAMP_DONE) {
        perfstat_clear_interrupt(PERF_INT_ALL);
        perfstat_sample_done_handler();
    }

    if(val & PERF_INT_LIST_DONE) {
        perfstat_clear_interrupt(PERF_INT_LIST_DONE);
        perfstat_list_done_handler();
    }

    if(val & PERF_INT_LIST_ERR) {
        perfstat_clear_interrupt(PERF_INT_LIST_ERR);
        perfstat_list_error_handler();
    }

    if(val & PERF_INT_OVER_TIME) {
        perfstat_clear_interrupt(PERF_INT_OVER_TIME);
        perfstat_port_overtime_handler();
    }

out:
    spin_unlock(&dev_info->synclock);
    return IRQ_HANDLED;
}

static int perfstat_check_ready(void)
{
    volatile int val;
    volatile int count;

    count = 200;
    do {
        val = perfstat_get_reset_cnt();
        count--;
    }while(val & count);

    if(!count)
        return PERF_ERROR;

    perfstat_set_monitor_reset();
    return PERF_OK;
}

static int perfstat_is_modem_powerup(void)
{
	struct device_node *np = NULL;
	void __iomem *pmctrl_base;
	int modem_noc_idleack;
	int ret = PERF_OK;

	np = of_find_compatible_node(NULL, NULL, "hisilicon,pmctrl");
	pmctrl_base = of_iomap(np, 0);
	if (!pmctrl_base)
		return PERF_ERROR;

	modem_noc_idleack = readl_relaxed(pmctrl_base + SOC_PMCTRL_NOC_POWER_IDLEACK_ADDR(0));
	if (modem_noc_idleack & BIT(3)) {
		ret = PERF_ERROR;
	}

	iounmap(pmctrl_base);
	pmctrl_base = NULL;
	return ret;
}

static int perfstat_master_is_valid(unsigned long *sprt)
{
	int i;
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_err("[%s]port is 0x%x\n",__func__, (int)*sprt);

	for (i = 0; i < PERF_PORT_NUM; i++) {
		if (*sprt & PERF_PORT_BIT(i)) {
			if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {
				pr_err("[%s] (%d)%s this port is not valid!\n",__func__, i, master_name[i]);
				*sprt &= (~ PERF_PORT_BIT(i));	/* clear this port */
			}
		}
	}

	/* If no master is powered up, not need to start perfstat. */
	if (0 == *sprt) {
		pr_err("[%s]no master is valid\n",__func__);
		return PERF_ERROR;
	}

	pr_err("[%s]port is 0x%x\n",__func__, (int)*sprt);
	return PERF_OK;
}

/**
* Judge if the master is powerup and
* only monitor the powerup ones.
**/
static int perfstat_master_is_powerup(unsigned long *sprt)
{
	int i,ret = PERF_OK;
	struct perfstat_dev_info *dev_info = perfstat_info;

	pr_err("[%s]port is 0x%x\n",__func__, (int)*sprt);

	for (i = 0; i < PERF_PORT_NUM; i++) {
		if (*sprt & PERF_PORT_BIT(i)) {
			if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {	/*if master is not valid, goto next master*/
				pr_err("[%s] %s-supply is not valid!\n",__func__, master_name[i]);
				*sprt &= ~PERF_PORT_BIT(i);
				continue;
			}
			if ((PERF_PORT_MODEM0 == i) || (PERF_PORT_MODEM1 == i)) {
				ret = perfstat_is_modem_powerup();
				if(ret != PERF_OK) {
					pr_err("[%s] modem-supply is not enabled\n",__func__);
					*sprt &= ~(PERF_PORT_BIT(PERF_PORT_MODEM0) | PERF_PORT_BIT(PERF_PORT_MODEM1));
				}
				continue;
			}
			if (!strncmp("", master_name[i], strlen(master_name[i]) + 1)) {
				continue;
			}
			ret = regulator_is_enabled(dev_info->master_supply[i]);
			if(!ret) {
				pr_err("[%s] %s-supply is not enabled\n",__func__, master_name[i]);
				*sprt &= ~PERF_PORT_BIT(i);
			}
		}
	}

	/* If no master is powered up, not need to start perfstat. */
	if (0 == *sprt) {
		pr_err("[%s]no master is powerup\n",__func__);
		return PERF_ERROR;
	}

	pr_err("[%s]port is 0x%x\n",__func__, (int)*sprt);
	return PERF_OK;
}

static void perfstat_record_sample_data(struct work_struct *work)
{
	struct perfstat_dev_info *dev_info = perfstat_info;
	unsigned long fs;
	long fd = 0;
	int ret = 0;
	void *start;
	int size;

	if (!atomic_add_unless(&is_recording, 1, 1)) {
		pr_err("[%s] is recording, failed to record.\n", __func__);
		return;
	}

	start = dev_info->virt_addr;
	size = PAGE_SIZE * dev_info->pages_n;
	/*invalid data buffer to be copied*/
	__dma_map_area((const void *)start, size, DMA_FROM_DEVICE);

	fs = get_fs();
	set_fs(KERNEL_DS);
	fd = sys_open(PERF_HIGHSPEED_DATA_PATH, O_CREAT|O_WRONLY|O_TRUNC, 0660);
	if (fd < 0) {
		pr_err("[%s]open file failed, ret is %lu.\n", __func__, fd);
		set_fs(fs);
		goto record_err;
	}

	/*write time info*/
	ret = sys_write(fd, (const char *)&sample_time, sizeof(sample_time));
	if (ret < 0) {
		pr_err("[%s]write file failed, ret is %d.\n", __func__, ret);
		set_fs(fs);
		goto record_err;
	}

	/*write perfstat raw data*/
	ret = sys_write(fd, start, size);
	if (ret < 0) {
		pr_err("[%s]write file failed, ret is %d.\n", __func__, ret);
		set_fs(fs);
		goto record_err;
	}

	ret = sys_fsync(fd);
	if (ret < 0) {
		pr_err("[%s]sys_fsync failed, ret is %d\n", __func__, ret);
	}

	ret = sys_close(fd);
	if (ret < 0) {
		pr_err("[%s]sys_close failed, ret is %d\n", __func__, ret);
		set_fs(fs);
		goto record_err;
	}

	set_fs(fs);
	perf_file_saved = true;
	complete(&perf_comp);
	pr_err("[%s]perf data saved complete!\n", __func__);

record_err:
	atomic_dec(&is_recording);
}

static void perfstat_event_destroy(struct perf_event *event)
{
    struct perfstat_dev_info *dev_info = perfstat_info;
    struct page **pages;
    int i,ret;

    if(perfstat_get_is_sampling()) {
        perfstat_trigger_sample_stop();
    }

    if (PERF_SAMPLE_HIGHSPEED == dev_info->samp_type) {
        wait_for_completion(&perf_comp);
    }

    pages = dev_info->pages;
    vunmap((const void *)dev_info->virt_addr);
    for(i = 0; i < dev_info->pages_n; i++) {
        __free_pages(pages[i], 0);
    }

    kfree(dev_info->list);
    kfree(dev_info->pages);
    dev_info->list = NULL;
    dev_info->pages = NULL;

    ret = regulator_disable(dev_info->perf_supply);
    if(ret < 0) {
        pr_err("[%s]perf-supply disable fail\n",__func__);
    }
    first_data = true;
    perf_file_saved = false;
    dev_info->event_bk = NULL;

    return;
}

static int perfstat_event_init(struct perf_event *bp)
{
    int event_id;
    struct perfstat_dev_info *dev_info = perfstat_info;
    int sprd, sptm;
    unsigned long sprt;
    int spn;
    int per_sz, sz;
    int page_u, page_n;
    signed int i = 0;
    int ret;
    struct page **pages = NULL;
    perf_list_descriptor *list_cfg = NULL;
    int list_head_phyaddr;
    int phy_addr;

    ret = regulator_enable(dev_info->perf_supply);
    if(ret < 0) {
        pr_err("[%s]perf-supply enable fail\n",__func__);
        return -ENOENT;
    }

    ret = perfstat_check_ready();
    if(ret < 0) {
        pr_err("[%s]perfstat is not ready\n",__func__);
        goto perf_supply_err;
    }

    if (bp->attr.type != PERF_TYPE_RAW)
        goto perf_supply_err;

    event_id = (int)(bp->attr.config >> 32);
    if ((event_id != dev_info->event_id) && (event_id != dev_info->event_id + 1))
        goto perf_supply_err;

    if (event_id == dev_info->event_id + 1) {
        dev_info->samp_type = PERF_SAMPLE_HIGHSPEED;
        pr_err("[%s]perfstat use high speed sample type.\n", __func__);
    } else {
        dev_info->samp_type = 0;
        pr_err("[%s]perfstat use low speed sample type.\n", __func__);
    }

    bp->attr.sample_type = PERF_SAMPLE_RAW;
    bp->attr.mmap = 0;
    bp->attr.comm = 0;
    bp->attr.task = 0;
    bp->destroy = perfstat_event_destroy;
    bp->attr.disabled = 0;
    bp->state = PERF_EVENT_STATE_INACTIVE;

    pr_err("==============[hisi perf prepare +]================\n");
    /*count buffer size to store data,then figure out
      the pages size needed, and also the page size
      reported once a interrupt*/
    sprd = bp->attr.sample_period & 0xffffffff;
    sprt = bp->attr.config & PERF_PORT_ALL;
    sptm = (int)((bp->attr.config >> 16) & 0xffff);

	ret = perfstat_master_is_valid(&sprt);
    if(PERF_OK != ret) {
        pr_err("[%s]no master is valid!\n",__func__);
        goto perf_supply_err;
    }

    ret = perfstat_master_is_powerup(&sprt);
    if(PERF_OK != ret) {
        pr_err("[%s]no master is powered up!\n",__func__);
        goto perf_supply_err;
    }

	if (dev_info->status != PERF_IS_REST) {
        pr_err("[%s] Perf sampleing, please wait for it finished!\n",__func__);
		goto perf_supply_err;
	}
    if (PERF_SAMPLE_HIGHSPEED == dev_info->samp_type) {
        if (0 == sptm) {
            pr_err("%s: timing not specified, use default time.\n", __func__);
            page_n = PERF_MALLOC_PAGES_100M;
        } else {
            spn = bitmap_weight((const unsigned long *)&sprt, 2 * sizeof(sprt));
            per_sz = (spn * dev_info->per_data_sz) + sizeof(perf_sample_data_head);
            sz = per_sz * ((sptm * 1000000 / sprd) + 1);
            page_n = Count_xINy_Num(PAGE_SIZE, sz);
        }
        pages = kzalloc((page_n * sizeof(struct page *)), GFP_KERNEL | GFP_DMA);
        if(!pages) {
            pr_err("[%s] cannot allocate pages ptr buffer\n", __func__);
            goto err;
        }

        dev_info->pages = pages;
        dev_info->pages_n = page_n;
        dev_info->sprt = (int)sprt;

        pr_err("[%s] port   : 0x%x\n",__func__,(int)sprt);
        pr_err("[%s] period : %dus\n",__func__,sprd);
        pr_err("[%s] page_n  : %d\n",__func__,page_n);

        list_cfg = kzalloc((page_n * sizeof(perf_list_descriptor)), GFP_KERNEL | GFP_DMA);
        if(!list_cfg) {
            pr_err("[%s] cannot allocate list_cfg buffer\n",__func__);
            goto err;
        }
        dev_info->list = list_cfg;
        list_head_phyaddr = (int)__virt_to_phys(list_cfg);
        pr_info("[%s] list_head_phyaddr is 0x%x\n", __func__, list_head_phyaddr);

        for(i = 0; i < page_n; i++) {
            pages[i] = alloc_page(GFP_KERNEL);
            if(!pages[i])
                goto err;
            phy_addr = (int)__virt_to_phys(page_address(pages[i]));

            if (unlikely(i == page_n - 1))
                list_cfg[i].value = PERF_LIST_CFG_INT;
            else
                list_cfg[i].value = PERF_LIST_CFG_NORMAL;

            list_cfg[i].bit_config.address = phy_addr;
            list_cfg[i].bit_config.length = PAGE_SIZE;
        }

        /*flush list_cfg into ddr*/
        __dma_map_area((const void *)list_cfg, (page_n * sizeof(perf_list_descriptor)), DMA_TO_DEVICE);
    } else {
        spn = bitmap_weight((const unsigned long *)&sprt, 2 * sizeof(sprt));
        per_sz = (spn * dev_info->per_data_sz) + sizeof(perf_sample_data_head);
        sz = per_sz * ((dev_info->samp_max_tm * 1000 / sprd) + 1);

        page_u = dev_info->per_int_size;
        page_n = Count_xINy_Num(PAGE_SIZE, sz);
        /*page_number is two at least to guarantee data copy*/
        if(page_n < PERF_MIN_PAGE_NUM) page_n = PERF_MIN_PAGE_NUM;

        pr_info("[%s] port   : 0x%x\n",__func__,(int)sprt);
        pr_info("[%s] period : %dus\n",__func__,sprd);
        pr_info("[%s] size   : %d bytes\n",__func__,sz);
        pr_info("[%s] page_u  : %d\n",__func__,page_u);
        pr_info("[%s] page_n  : %d\n",__func__,page_n);

        pages = kzalloc((page_n * sizeof(struct page *)), GFP_KERNEL | GFP_DMA);
        if(!pages) {
            pr_err("[%s] cannot allocate pages ptr buffer\n",__func__);
            goto err;
        }
        dev_info->pages = pages;
        dev_info->pages_n = page_n;
        dev_info->pages_u = page_u;
        dev_info->cur_page_n = 0;
        dev_info->sprt = (int)sprt;

        /*another list_descriptor performs as a linker*/
        list_cfg = kzalloc(((page_n + 1) * sizeof(perf_list_descriptor)), GFP_KERNEL | GFP_DMA);
        if(!list_cfg) {
            pr_err("[%s] cannot allocate list_cfg buffer\n",__func__);
            goto err;
        }
        dev_info->list = list_cfg;
        list_head_phyaddr = (int)__virt_to_phys(list_cfg);
        pr_info("[%s] list_head_phyaddr is 0x%x\n", __func__, list_head_phyaddr);

        for(i = 0; i < page_n; i++) {
            pages[i] = alloc_page(GFP_KERNEL);
            if(!pages[i])
                goto err;
            phy_addr = (int)__virt_to_phys(page_address(pages[i]));

            if((((i + 1) % page_u) == 0) || ((i + 1) == page_n)) {
                list_cfg[i].value = PERF_LIST_CFG_INT;
            }
            else {
                list_cfg[i].value = PERF_LIST_CFG_NORMAL;
            }

            list_cfg[i].bit_config.address = phy_addr;
            list_cfg[i].bit_config.length = PAGE_SIZE;
        }
        //last descriptor is a link to the head
        list_cfg[page_n].value = PERF_LIST_CFG_LINK;
        list_cfg[page_n].bit_config.address = list_head_phyaddr;

        /*flush list_cfg into ddr*/
        __dma_map_area((const void *)list_cfg,
                ((page_n + 1) * sizeof(perf_list_descriptor)), DMA_TO_DEVICE);
    }

    /*map pages to a continuous virtual address*/
    dev_info->virt_addr = vmap(pages, page_n, VM_MAP, PAGE_KERNEL);
    if(!dev_info->virt_addr) {
        pr_err("[%s] vmap pages error\n",__func__);
        goto err;
    }

    memset(dev_info->virt_addr, 0, page_n * PAGE_SIZE);
    __dma_map_area((const void *)dev_info->virt_addr,
            (page_n * PAGE_SIZE), DMA_FROM_DEVICE);
    pr_info("[%s] vmap is %p\n",__func__,dev_info->virt_addr);

    perfstat_set_sample_period(sprd);
    perfstat_set_sample_port((int)sprt);
    perfstat_set_sample_num(PERF_SAMPLE_ALWAYS);
    perfstat_set_addr_mode(PERF_LIST_ADDR_MODE);
    ret = perfstat_set_list_mode_addr(list_head_phyaddr);
    if(PERF_OK != ret) {
        pr_err("[%s] set list addr error\n",__func__);
        goto err;
    }

    perfstat_clear_interrupt(PERF_INT_ALL);
    perfstat_enable_interrupt(PERF_INT_ALL);
    perfstat_set_timeout_duration(10);

    sample_time= sched_clock();
    pr_err("[%s] sample time is %lu\n", __func__, sample_time);
    pr_err("==============[hisi perf prepare -]================\n");

    dev_info->event_bk = bp;

    return 0;

err:
    if(dev_info->virt_addr) {
        vunmap(dev_info->virt_addr);
        dev_info->virt_addr = NULL;
    }
    if(dev_info->list) {
        kfree(dev_info->list);
        dev_info->list = NULL;
    }
    if(dev_info->pages) {
        for(i = i - 1; i >= 0 ; i--)
            __free_pages(dev_info->pages[i], 0);
        kfree(dev_info->pages);
        dev_info->pages = NULL;
    }
perf_supply_err:
    ret = regulator_disable(dev_info->perf_supply);
    if (ret < 0) {
        pr_err("[%s]perf-supply disable fail\n",__func__);
    }
    return -ENOENT;
}

static int perfstat_add(struct perf_event *bp, int flags)
{
    struct perfstat_dev_info *dev_info = perfstat_info;

    wake_lock(&dev_info->wakelock);

    dev_info->status = PERF_IS_WORK;

    pr_info("[%s][hisi perf start sample...]\n",__func__);
    perfstat_trigger_sample_start();

    return 0;
}

static void perfstat_del(struct perf_event *bp, int flags)
{
    struct perfstat_dev_info *dev_info = perfstat_info;

    spin_lock(&dev_info->synclock);
    dev_info->status = PERF_IS_REST;
    spin_unlock(&dev_info->synclock);

    if ((PERF_SAMPLE_HIGHSPEED == dev_info->samp_type) && (!perf_file_saved) && !atomic_read(&is_recording)) {
        pr_err("%s: save perf data...\n", __func__);
        schedule_delayed_work(&dev_info->hs_record_data_work, 0);
    }

    pr_info("[%s][hisi perf stop sample]\n",__func__);
    perfstat_trigger_sample_stop();

    pr_err("==============[hisi perf finish +]================\n");
    perfstat_debug_info_show();
    pr_err("==============[hisi perf finish -]================\n");

    wake_unlock(&dev_info->wakelock);

    return;
}

static void perfstat_start(struct perf_event *bp, int flags)
{
    bp->hw.state = 0;
}

static void perfstat_stop(struct perf_event *bp, int flags)
{
    bp->hw.state = PERF_HES_STOPPED;
}

static void perfstat_read(struct perf_event *bp)
{
    return;
}

static int perfstat_event_idx(struct perf_event *bp)
{
    return 0;
}

static struct pmu perf_stat_pmu = {
    .event_init = perfstat_event_init,
    .add        = perfstat_add,
    .del        = perfstat_del,
    .start      = perfstat_start,
    .stop       = perfstat_stop,
    .read       = perfstat_read,
    .event_idx  = perfstat_event_idx,
};

static int fake_of_get_perfstat_attribute(const struct device_node *np, struct perfstat_dev_info *dev_info)
{
    int ret;

    ret = of_property_read_u32(np, "hisilicon,perf-event-id", &dev_info->event_id);
    if(ret < 0) {
        pr_err("[%s] cannot get perf-event-id\n",__func__);
        return -ENOENT;
    }

    ret = of_property_read_u32(np, "hisilicon,max-sample-time", &dev_info->samp_max_tm);
    if(ret < 0) {
        pr_err("[%s] cannot get max-sample-time\n",__func__);
        return -ENOENT;
    }

    ret = of_property_read_u32(np, "hisilicon,per-int-size", &dev_info->per_int_size);
    if(ret < 0) {
        pr_err("[%s] cannot get per-int-size\n",__func__);
        return -ENOENT;
    }

    ret = of_property_read_u32(np, "hisilicon,per-data-size", &dev_info->per_data_sz);
    if(ret < 0) {
        pr_err("[%s] cannot get per-data-size\n",__func__);
        return -ENOENT;
    }

    ret = of_property_read_u32(np, "hisilicon,vldmsk-of-sprt", &dev_info->vldmsk_of_sprt);
    if(ret < 0) {
        pr_err("[%s] cannot get vldmsk-of-sprt\n",__func__);
        return -ENOENT;
    }
    return 0;
}

static int perfstat_get_fpga_flag(unsigned int* pFpga)
{
    struct device_node *np = NULL;
	unsigned int fpga_flag = 0;
    int ret = 0;

    np = of_find_compatible_node(NULL, NULL, "hisilicon,hisifb");
    if (!np) {
        printk("NOT FOUND device node 'hisilicon,hisifb'!\n");
        return -ENXIO;
    }
    ret = of_property_read_u32(np, "fpga_flag", &fpga_flag);
    if (ret) {
        printk("failed to get fpga_flag resource.\n");
        return -ENXIO;
    }
    *pFpga = fpga_flag;
    return 0;
}

static int perfstat_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    struct device_node *np = dev->of_node;
    int i,ret;
    struct perfstat_dev_info *dev_info;
    unsigned int fpga_flag = 0;
    const struct of_device_id *match;

    pr_err("================[hisi perf probe s]================\n");

    /* Get fpga flag first */
    perfstat_get_fpga_flag(&fpga_flag);

    /* to check which type of regulator this is */
    match = of_match_device(of_perfstat_match_tbl, dev);
    if (NULL == match) {
        pr_err("[%s]: mismatch of perf_stat driver \n\r", __func__);
        return -ENODEV;
    }

    master_name = (char **)match->data;

    dev_info = devm_kzalloc(dev, sizeof(struct perfstat_dev_info), GFP_KERNEL);
    if(!dev_info) {
        pr_err("[%s] cannot alloc perfstat desc\n",__func__);
        return -ENOMEM;
    }
    perfstat_info = dev_info;

    dev_info->res = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if (!dev_info->res) {
        pr_err("[%s] platform_get_resource err\n",__func__);
        return -ENOENT;
    }

    if (!devm_request_mem_region(dev, dev_info->res->start,
                resource_size(dev_info->res),
                    pdev->name)) {
        pr_err("[%s] cannot claim register memory\n",__func__);
        return -ENOMEM;
    }

    perfstat_base = ioremap(dev_info->res->start, resource_size(dev_info->res));
    if(!perfstat_base) {
        pr_err("[%s] base address ioremap fail\n",__func__);
        return -ENOMEM;
    }

    dev_info->irq = platform_get_irq(pdev, 0);
    if(dev_info->irq < 0) {
        pr_err("[%s] platform_get_irq err\n",__func__);
        return -ENXIO;
    }

    ret = request_threaded_irq(dev_info->irq, perfstat_interrupt_handler, NULL,
            IRQF_NO_SUSPEND, "pertstat-irq", dev_info);
    if(ret < 0) {
        pr_err("[%s] requset irq error\n",__func__);
        return -ENODEV;
    }

    dev_info->sample_clk = devm_clk_get(&pdev->dev, "sample_clk");
    if(IS_ERR(dev_info->sample_clk)) {
        pr_err("[%s] get sample_clk error\n",__func__);
        return -ENODEV;
    }

    if (!fpga_flag) {    /*When fpga mode, no need to set sample clock to 60MHz*/
        ret = clk_set_rate(dev_info->sample_clk, 60000000);
        if (ret) {
            pr_err("[%s] set sample_clk error\n",__func__);
            return -ENODEV;
        }
    }
    dev_info->sample_clk_rate = clk_get_rate(dev_info->sample_clk);
    pr_err("[%s] sample_clk is %lu\n",__func__, dev_info->sample_clk_rate);

    dev_info->perf_supply = devm_regulator_get(&pdev->dev, "perf-power");
    if(IS_ERR(dev_info->perf_supply)) {
        pr_err("[%s] get perf-power-supply error\n",__func__);
        return -ENODEV;
    }

    ret = fake_of_get_perfstat_attribute(np, dev_info);
    if(ret < 0) {
        pr_err("[%s] get hisilicon dts fail\n",__func__);
        return -ENOENT;
    }

    for (i = 0; i < PERF_PORT_NUM; i++) {
        pr_debug("[%s] %s\n",__func__, master_name[i]);
        if (!strncmp("", master_name[i], strlen(master_name[i]) + 1)) {
            continue;
        }
        if (!(dev_info->vldmsk_of_sprt & PERF_PORT_BIT(i))) {
			continue;
        }
        pr_debug("[%s] get %s-supply\n",__func__, master_name[i]);
        dev_info->master_supply[i] = devm_regulator_get(&pdev->dev, master_name[i]);
        if(IS_ERR(dev_info->master_supply[i])) {
            pr_err("[%s] get %s-supply error\n",__func__, master_name[i]);
            return -ENODEV;
        }
    }

    ret = perf_pmu_register(&perf_stat_pmu, "HiPERFSTAT", PERF_TYPE_RAW);
    if(ret < 0) {
        pr_err("[%s] register perf pmu fail\n",__func__);
        return -ENODEV;
    }

    INIT_DELAYED_WORK(&dev_info->hs_record_data_work, perfstat_record_sample_data);
    init_completion(&perf_comp);

    spin_lock_init(&dev_info->synclock);
    wake_lock_init(&dev_info->wakelock, WAKE_LOCK_SUSPEND, "perf-stat-wakelock");
    dev_info->status = PERF_IS_REST;

    pr_err("================[hisi perf probe e]================\n");

    return 0;
}

static int perfstat_remove(struct platform_device *pdev)
{
    return 0;
}

static struct platform_driver perfstat_driver = {
    .driver = {
        .name = "HiPERFSTAT",
        .owner = THIS_MODULE,
        .of_match_table = of_perfstat_match_tbl,
    },
    .probe  = perfstat_probe,
    .remove = perfstat_remove,
};

static __init int perfstat_init(void)
{
    int ret = 0;

    ret = platform_driver_register(&perfstat_driver);
    if (ret) {
        pr_err("[%s] platform_driver_register failed %d\n",
                __func__, ret);
    }

    return ret;
}

static void __exit perfstat_exit(void)
{
    platform_driver_unregister(&perfstat_driver);
}

module_init(perfstat_init);
module_exit(perfstat_exit);
