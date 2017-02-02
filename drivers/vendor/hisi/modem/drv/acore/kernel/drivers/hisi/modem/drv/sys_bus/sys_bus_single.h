#ifndef __SYS_BUS_SINGLE_H__
#define __SYS_BUS_SINGLE_H__

#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/of.h>
#include <linux/types.h>


#define single_to_sys_bus(p) (container_of(p, struct sys_bus, bus_single))

#define magic_num_u32 0x5a5a5a5a
#define magic_num_u16 0x5b5b
#define magic_num_u8 0xc

#define MAX_SINGLE_BUF_SIZE 1024

struct bus_single {
    struct device_node	*of_node;
    void (*start)(struct bus_single *);
	void (*stop)(struct bus_single *);
    void (*enable)(struct bus_single *);
	void (*disable)(struct bus_single *);
    void (*record)(struct bus_single *);
    void (*report)(struct bus_single *);
    u32 enflag;
    char* result_buf;
    u32 result_len;
};

struct single_value {
    u32 start;
    u32 size;
    u32 woffset;
    u32 roffset;
};

struct single_result {
    struct list_head entry;
    u8* name;
    u32 result;
};

void bus_single_start(struct bus_single *bus_single);
void bus_single_stop(void);

#endif /* __SYS_BUS_SINGLE_H__ */

