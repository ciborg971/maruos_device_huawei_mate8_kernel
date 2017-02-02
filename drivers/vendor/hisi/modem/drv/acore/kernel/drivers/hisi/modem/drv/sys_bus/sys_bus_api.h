#ifndef __SYS_BUS_API_H__
#define __SYS_BUS_API_H__

#include <sys_bus_single.h>
#include <sys_bus_pressure.h>
#include <sys_bus_core.h>

void bus_single_init(struct sys_bus *sysbus, struct device_node * single_np);
void bus_single_msg_handle(struct bus_single *bus_single, void *msg);

#endif /* __SYS_BUS_SINGLE_H__ */

