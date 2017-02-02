#ifndef __SYS_BUS_CORE_H__
#define __SYS_BUS_CORE_H__

#include <bsp_om.h>
#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/skbuff.h>

enum SYS_MODULE_ID {
    E_SYS_MODULE_SINGLE,
    E_SYS_MODULE_PRESSURE,
    E_SYS_MODULE_MAX
};

struct sys_bus {
    struct device_node *of_node;
    struct task_struct* tsk;
    struct semaphore tsk_sema;
    spinlock_t  lock;
    struct sk_buff_head *skb_head;
    u32 channel_id;
	char		*name;
	int		num_events;
	u64		max_period;
	struct platform_device	*plat_device;
    void* bus_single;
    void* bus_pressure;
};

struct sys_msg {
    u32 module;    /* single/pressure/... */
    u32 type;
    u32 len;
    char data[];
};

#define sys_bus_trace(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SYS_BUS, "sys_bus:<%s> <%d> "fmt, __FUNCTION__,__LINE__, ##__VA_ARGS__))


#endif /* __SYS_BUS_CORE_H__ */

