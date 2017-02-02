#include <linux/of.h>
#include <linux/module.h>
#include <linux/of_address.h>
#include <asm/div64.h>
#include <osl_types.h>
#include "bsp_slice.h"
#include <bsp_sysctrl.h>
#include <sys_bus_core.h>
#include <sys_monitor.h>

struct sys_amon_chan g_sys_amon_chan[MAX_SYS_CHAN_NUM];
struct sys_monitor g_sys_monitor;

struct sys_amon_chan* sys_monitor_req_chan(void)
{
    u32 i = 0;

    for(i = 0; i < MAX_SYS_CHAN_NUM; i++) 
    {
        if(!g_sys_amon_chan[i].use_flag)
        {
            (void)memset((void*)&g_sys_amon_chan[i], 0, sizeof(struct sys_amon_chan));
            g_sys_amon_chan[i].use_flag = 1;
            g_sys_amon_chan[i].chan_id = i;
            return &g_sys_amon_chan[i];
        }
    }
    sys_bus_trace("no idle chan\n");
    return NULL;
}

void sys_monitor_free_chan(u32 chan)
{
    g_sys_amon_chan[chan].use_flag = 0;
}
void sys_monitor_config(u32 chan)
{
    u32 tmp = 0;
    struct sys_amon_chan* sys_amon_chan = &g_sys_amon_chan[chan];
    u32 port  = sys_amon_chan->port;
    u32 id_enable = sys_amon_chan->id_enable;
    u32 adr_enable = sys_amon_chan->adr_enable;
    void __iomem * base_addr = (void __iomem *)g_sys_monitor.base_addr;

    /*config port_sel*/
    if((port<8)&&(chan<8))
    {
        tmp = readl(base_addr + PORT_SEL);
        tmp &= ~(0x7<<(chan*3));
        tmp |= port<<(chan*3);
        writel(tmp, base_addr + PORT_SEL);
    }
    else
    {
        sys_bus_trace("port = %d chan = %d error\n", port, chan);
        return;
    }

    /* config cnt_id */
    tmp = ((id_enable&0x1)<<31) | ((adr_enable&0x1)<<30);

    if(id_enable)
    {
        tmp |= (sys_amon_chan->cnt_id) | (sys_amon_chan->cnt_id_mask<<15);
        writel(tmp, base_addr + CNT_ID + 0x100*chan);
    }

    if(adr_enable)
    {
        /* start addr */
        writel(sys_amon_chan->start_addr, base_addr + ID_ADDR_DES + 0x100*chan);
        /* end addr */
        writel(sys_amon_chan->end_addr, base_addr + ID_ADDR_DES_M + 0x100*chan);
    }
}

void sys_monitor_start(void)
{
    u32 tmp = 0;
    void __iomem * base_addr = (void __iomem *)g_sys_monitor.base_addr;
    void __iomem * sysctrl_base = (void __iomem *)bsp_sysctrl_addr_get((void*)0x90000000);

    /*软复位*/
    tmp = readl(base_addr);
    tmp = tmp|0x2;
    writel(tmp, base_addr);

    /*等待复位成功*/
    do
    {
        tmp = readl(base_addr + CNT_STATE_INT);
    }while((tmp&0x10) != 0x10);

    /*复位*/
    writel(0x1<<29, sysctrl_base + 0x60);
    /*解复位*/
    writel(0x1<<29, sysctrl_base + 0x64);

    /*start*/
    tmp = readl(sysctrl_base + 0x800);
    tmp |= 0x400;
    writel(tmp, sysctrl_base + 0x800);

    /*wait for start*/
    do
    {
        tmp = readl(base_addr + CNT_STATE_INT);
    }while((tmp&0xC) != 0x8);

    if(bsp_slice_getcurtime(&g_sys_monitor.start_t)!= 0)
    {
        sys_bus_trace("get 64bit timestamp error\n");
    }
}

void sys_monitor_stop(void)
{
    u32 tmp = 0;
    void __iomem * base_addr = (void __iomem *)g_sys_monitor.base_addr;
    void __iomem * sysctrl_base = (void __iomem *)bsp_sysctrl_addr_get((void*)0x90000000);

    /*start*/
    tmp = readl(sysctrl_base + 0x800);
    tmp &= ~0x400;
    writel(tmp, sysctrl_base + 0x800);

    /*wait for stop*/
    do
    {
        tmp = readl(base_addr + CNT_STATE_INT);
    }while((tmp&0xC) != 0xC);

    if(bsp_slice_getcurtime(&g_sys_monitor.end_t)!= 0)
    {
        sys_bus_trace("get 64bit timestamp error\n");
    }
    g_sys_monitor.totaltime = (g_sys_monitor.end_t - g_sys_monitor.start_t)>>15;
}

void sys_monitor_record(u32 chan)
{
    void __iomem * base_addr = (void __iomem *)g_sys_monitor.base_addr;

    g_sys_amon_chan[chan].read_bytes[0] = readl(base_addr + READ_BYTES_ID + 0x100*chan);
    g_sys_amon_chan[chan].read_bytes[1] = readl(base_addr + READ_BYTES_ID + 0x4 + 0x100*chan);
    g_sys_amon_chan[chan].write_bytes[0] = readl(base_addr + WRITE_BYTES_ID + 0x100*chan);
    g_sys_amon_chan[chan].write_bytes[1] = readl(base_addr + WRITE_BYTES_ID + 0x4 + 0x100*chan);
}

void sys_monitor_report(u32 chan)
{
    u64 time = g_sys_monitor.end_t - g_sys_monitor.start_t;
    unsigned long mod = 0;
    unsigned long long x,y,rdrate,wrrate;

    x = *((u64*)g_sys_amon_chan[chan].read_bytes)*32768;
    y = time;
    mod = do_div(x, y);
    rdrate = x;
    x = *((u64*)g_sys_amon_chan[chan].write_bytes)*32768;
    y = time;
    mod = do_div(x, y);
    wrrate = x;
    rdrate = rdrate>>20;
    wrrate = wrrate>>20;

    if(g_sys_amon_chan[chan].use_flag)
    {
        sys_bus_trace("=====ID %d %s statistics=====\n", chan, g_sys_amon_chan[chan].name);
        sys_bus_trace("rd total bytes: 0x%08x%08x\n", g_sys_amon_chan[chan].read_bytes[1], g_sys_amon_chan[chan].read_bytes[0]);
        sys_bus_trace("wr total bytes: 0x%08x%08x\n", g_sys_amon_chan[chan].write_bytes[1], g_sys_amon_chan[chan].write_bytes[0]);
        sys_bus_trace("rd total rate: %dMB/s\n", (u32)rdrate);
        sys_bus_trace("wr total rate: %dMB/s\n", (u32)wrrate);
    }
}

int sys_monitor_init(void)
{
    struct device_node *np;
    void __iomem *base = NULL;

    (void)memset((void*)&g_sys_amon_chan, 0, MAX_SYS_CHAN_NUM*sizeof(struct sys_amon_chan));
    np = of_find_compatible_node(NULL, NULL, "sys_bus, bus_amon");
    if (!np)
    {
        sys_bus_trace("find sys_amon node error\n");
        return -1;
    }
    g_sys_monitor.of_node = np;

    base = of_iomap(np, 0);
	if (!base)
    {
		sys_bus_trace("Failed to map amon base\n");
		return -1;
	}
    g_sys_monitor.base_addr = (u32)base;
    sys_bus_trace("reg = 0x%x\n", g_sys_monitor.base_addr);

    return 0;

}

static struct of_device_id sys_monitor_ids[] = {
    {.compatible = "acpu_m1"},
    {.compatible = "m3"},
    {.compatible = "acpu_m0"},
    {.compatible = "hifi"},
    {.compatible = "edma"},
    {.compatible = "socp"},
    {.compatible = "hdlc"},
    {.compatible = "ipf_psam"},
    {.compatible = "rsr_acc"},
    {.compatible = "spe"},
    {.compatible = "cs_tmc"},
    {.compatible = "ahb2axi_mst"},
    {.compatible = "dx"},
    {.compatible = "pcie0"},
    {.compatible = "pcie1"},
    {.compatible = "usb3"},
};

u32 sys_mon_config_id(u32 id, u32 enable, u32 start_addr, u32 end_addr)
{
    struct sys_amon_chan* sys_amon_chan;
    struct device_node *np;
    int ret = 0;

    sys_amon_chan = sys_monitor_req_chan();
    if(sys_amon_chan == NULL)
    {
        return -1;
    }

    np = g_sys_monitor.of_node;
    np = of_find_compatible_node(np, NULL, sys_monitor_ids[id].compatible);
    if (!np)
    {
        sys_bus_trace("find %s node error\n", sys_monitor_ids[id].compatible);
        sys_monitor_free_chan(sys_amon_chan->chan_id);
        return -1;
    }

    ret = of_property_read_u32_array(np, "amon_data", (u32*)&sys_amon_chan->port, 7);
    if(ret)
    {
        sys_bus_trace("find %s amon_data error\n", sys_monitor_ids[id].compatible);
	    return -1;
    }
    sys_amon_chan->name = sys_monitor_ids[id].compatible;
    switch(enable)
    {
        case SYS_AMON_ID_ENABLE:
            sys_amon_chan->id_enable = 1;
            sys_amon_chan->adr_enable = 0;
            break;
        case SYS_AMON_ADR_ENABLE:
            sys_amon_chan->id_enable = 0;
            sys_amon_chan->adr_enable = 1;
            break;
        case SYS_AMON_BOTH_ENABLE:
            sys_amon_chan->id_enable = 1;
            sys_amon_chan->adr_enable = 1;
            break;
        case SYS_AMON_NONE_ENABLE:
            sys_amon_chan->id_enable = 0;
            sys_amon_chan->adr_enable = 0;
            break;
        default:
            sys_amon_chan->id_enable = 1;
            sys_amon_chan->adr_enable = 0;
            break;
    }
    sys_amon_chan->start_addr = start_addr;
    sys_amon_chan->end_addr = end_addr;

    sys_monitor_config(sys_amon_chan->chan_id);

    return sys_amon_chan->chan_id;
}

u32 sys_mon_config_port(u32 port, u32 start_addr, u32 end_addr)
{
    struct sys_amon_chan* sys_amon_chan;

    sys_amon_chan = sys_monitor_req_chan();
    if(sys_amon_chan == NULL)
    {
        return -1;
    }
    sys_amon_chan->name = "port";
    sys_amon_chan->port = port;
    sys_amon_chan->id_enable = 0;
    sys_amon_chan->adr_enable = 1;
    sys_amon_chan->start_addr = start_addr;
    sys_amon_chan->end_addr = end_addr;

    return sys_amon_chan->chan_id;
}

void sys_mon_chan_info(void)
{
    u32 i = 0;

    for(i = 0; i < MAX_SYS_CHAN_NUM; i++) 
    {

        if(g_sys_amon_chan[i].use_flag)
        {
            sys_bus_trace("=====ID %d %s using=====\n", i, g_sys_amon_chan[i].name);
            if(g_sys_amon_chan[i].adr_enable)
            {
                sys_bus_trace("port  %d\n", g_sys_amon_chan[i].port);
                sys_bus_trace("start addr 0x%08x\n", g_sys_amon_chan[i].start_addr);
                sys_bus_trace("end   addr 0x%08x\n", g_sys_amon_chan[i].end_addr);
            }
        }
        else
        {
            sys_bus_trace("=====ID %d is not used=====\n", i);
        }
    }

}

void sys_mon_all_record(void)
{
    u32 i = 0;

    sys_monitor_stop();
    for(i = 0; i < MAX_SYS_CHAN_NUM; i++)
    {
        sys_monitor_record(i);
    }
}

void sys_mon_all_report(void)
{
    u32 i = 0;

    sys_bus_trace("sys monitor report start\n");
    sys_bus_trace("total time %d s\n", (u32)g_sys_monitor.totaltime);
    for(i = 0; i < MAX_SYS_CHAN_NUM; i++)
    {
        sys_monitor_report(i);
    }
    sys_bus_trace("sys monitor report end\n");
}

void sys_mon_start(void)
{
    sys_monitor_start();
}

void sys_mon_result(void)
{
    sys_mon_all_record();
    sys_mon_all_report();
}

void sys_mon_result_and_start(void)
{
    sys_mon_all_record();
    sys_mon_all_report();
    sys_monitor_start();
}

void sys_mon_one_free(u32 chan)
{
    sys_monitor_free_chan(chan);
}

void sys_mon_all_free(void)
{
    u32 i = 0;

    for(i = 0; i < MAX_SYS_CHAN_NUM; i++)
    {
        sys_monitor_free_chan(i);
    }
}

void sys_mon_help(void)
{
    u32  i = 0;

    sys_bus_trace("port info\n");
    for(i=0;i<MAX_SYS_PORT_NUM;i++)
    {
        sys_bus_trace("port %d -- port%d\n",i, i);
    }
    sys_bus_trace("id   info\n");
    for(i=0;i<(sizeof(sys_monitor_ids)/sizeof(struct of_device_id));i++)
    {
        sys_bus_trace("id   %d -- %s\n",i, sys_monitor_ids[i].compatible);
    }

    sys_bus_trace("enable info:\n");
    sys_bus_trace("            0 -- only id enable\n");
    sys_bus_trace("            1 -- only adr enable\n");
    sys_bus_trace("            2 -- both id and adr enable\n");
    sys_bus_trace("            3 -- not enable\n");

    sys_bus_trace("suport cmd:\n");
    sys_bus_trace("sys_mon_config_id   id,enable,start_addr,end_addr\n");
    sys_bus_trace("sys_mon_config_port port,start_addr,end_addr\n");
    sys_bus_trace("sys_mon_one_free chan\n");
    sys_bus_trace("sys_mon_all_free\n");
    sys_bus_trace("sys_mon_start\n");
    sys_bus_trace("sys_mon_result\n");
    sys_bus_trace("sys_mon_result_and_start\n");
    sys_bus_trace("sys_mon_chan_info\n");
}

module_init(sys_monitor_init);
