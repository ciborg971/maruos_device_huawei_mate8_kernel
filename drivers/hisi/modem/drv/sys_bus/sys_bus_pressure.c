/*
 *
 *
 */
#include <linux/types.h>
#include <linux/interrupt.h>
#include <linux/of.h>
#include <linux/list.h>
#include <linux/slab.h>
#include <sys_bus_core.h>
#include <sys_edma.h>
#include <sys_acore.h>
#include <sys_ipf.h>
#include <sys_hdlc/sys_hdlc.h>
#include <sys_socp.h>
#include <sys_bus_pressure.h>
#include <sys_lcd.h>

extern struct sys_bus *g_sysbus;
struct bus_pressure* g_bus_pressure;

static LIST_HEAD(master_head);


static struct of_device_id bus_pressure_ids[] = {

    {.compatible = "bus_pressure, edma", .data = sys_edma_init},
    {.compatible = "bus_pressure, acore", .data = sys_acore_init},
#ifdef CONFIG_FB_EMI_BALONG
	{.compatible = "bus_pressure, lcd", .data = sys_lcd_init},
#endif
	{.compatible = "bus_pressure, ipf", .data = sys_ipf_init},
	{.compatible = "bus_pressure, hdlc", .data = sys_hdlc_init},  
    {.compatible = "bus_pressure, socp", .data = sys_socp_init},
    {},
};

typedef void(*master_of_init_fn)(struct master*);

void bus_pressure_init(struct sys_bus *sysbus, struct device_node * pressure_np)
{
    const struct of_device_id *match;
    struct master* master;
    master_of_init_fn init_func;
    struct device_node *np;
    struct bus_pressure* bus_pressure;

    np = pressure_np;
    for_each_matching_node_and_match(np, bus_pressure_ids, &match)
    {
        master = kzalloc(sizeof(struct master), GFP_KERNEL);
        if (!master)
        {
            sys_bus_trace("failed to allocate master!");
            return;
        }
        master->np = np;
        init_func = match->data;
        init_func(master);
        list_add_tail(&master->entry, &master_head);
    }

    bus_pressure = kzalloc(sizeof(struct bus_pressure), GFP_KERNEL);
	if (!bus_pressure)
    {
		sys_bus_trace("failed to allocate bus_pressure!\n");
		return ;
	}

    bus_pressure->of_node = pressure_np;
    bus_pressure->start = bus_pressure_start;
    bus_pressure->stop = bus_pressure_stop;
    bus_pressure->enable = NULL;//bus_pressure_enable;
    bus_pressure->disable = NULL;//bus_pressure_disable;
    bus_pressure->record = bus_pressure_record;
    bus_pressure->report = bus_pressure_report;
    //bus_pressure->result_len = 0;

    sysbus->bus_pressure = (void*)bus_pressure;
    g_bus_pressure = bus_pressure;
}

void bus_pressure_start(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->start)
            master->start(master);
    }
}

void bus_pressure_stop(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->stop)
            master->stop(master);
    }
}

void bus_pressure_record(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->record)
            master->record(master);
    }
}

void bus_pressure_report(void)
{
    struct master *master;

    list_for_each_entry(master, &master_head, entry)
    {
        if (master->report)
            master->report(master);
    }
}


