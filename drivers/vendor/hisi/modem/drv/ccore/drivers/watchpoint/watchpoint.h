
#ifndef	__WATCHPOINT_H__
#define __WATCHPOINT_H__

#include "osl_types.h"
#include "osl_spinlock.h"
#include "bsp_om.h"
#include "bsp_wp.h"

enum
{
    WATCHPOINT_UNALLOC = 0,
    WATCHPOINT_ALLOCED = 1,
};

typedef struct
{
    u32         alloc;
    wp_cfg_t    cfg;
}wp_info_t;

typedef struct
{
    wp_info_t * wp_info;
    u32         wp_cnt;
    bool        init_flag;
    spinlock_t  lock;
    u32         wp_hit_cnt;
}wp_ctrl_t;

typedef struct
{
    u32     dscr;
    u32     wvr_reg[16];
    u32     wcr_reg[16];
}wp_reg_back_t;

#define wp_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_FATAL, BSP_MODU_WATCHPOINT, "[watchpoint]: <%s> "fmt, __FUNCTION__, ##__VA_ARGS__))

#endif //__WATCHPOINT_H__

