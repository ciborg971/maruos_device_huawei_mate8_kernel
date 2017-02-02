#ifndef __SYS_ACORE_H__
#define __SYS_ACORE_H__

#define acore_ddr_size  (1*1024*1024)

struct sys_acore {
    struct task_struct* tsk;
    u32 src;
    u32 dst;
    u32 size;
    u32 flag;
    u32 totalsize; /* MB */
    u32 totaltime; /* 32K timestamp */
    u32 start_t;   /* 32K timestamp */
    u32 end_t;     /* 32K timestamp */
};

void sys_acore_init(struct master* master);

#endif /* __SYS_ACORE_H__ */
