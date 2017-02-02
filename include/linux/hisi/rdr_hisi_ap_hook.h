
#include <linux/thread_info.h>
#include <linux/hisi/rdr_types.h>
#include <linux/hisi/rdr_pub.h>

typedef u64 (*arch_timer_func_ptr)(void);

typedef enum{
    HK_IRQ = 0,
    HK_TASK,
    HK_CPUIDLE,
    HK_PERCPU_TAG, /*percpu�Ĺ켣����HK_PERCPU_TAG����*/
    HK_CPU_ONOFF = 3,
    HK_SYSCALL,
    HK_HUNGTASK,
    HK_BUDDY_FAIL,
    HK_MAX
}
hook_type;

typedef struct
{
    u64 clock;
    u64 jiff;
    u32 irq;
    u8 cpu;
    u8 dir;
}
irq_info;

typedef struct
{
    u64 clock;
    u8 cpu;
    u32 pid;
    char comm[TASK_COMM_LEN];
}
task_info;

typedef struct
{
    u64 clock;
    u8 cpu;
    u8 dir;
}
cpuidle_info;

typedef struct
{
    u64 clock;
    u8 cpu;
    u8 on;
}
cpu_onoff_info;

typedef struct
{
    u64 clock;
    u32 syscall;
    u8 cpu;
    u8 dir;
}
syscall_info;

typedef struct
{
    u64 clock;
	u32 timeout;
    u32 pid;
    char comm[TASK_COMM_LEN];
}
hung_task_info;

typedef struct
{
    u64 clock;
	u32 order;
    u32 pid;
    char comm[TASK_COMM_LEN];
}
buddy_fail_info;


typedef struct
{
    unsigned char * buffer_addr;
    unsigned char * percpu_addr[NR_CPUS];
    unsigned int    percpu_length[NR_CPUS];
    unsigned int    buffer_size;
}
percpu_buffer_info;

int register_arch_timer_func_ptr(arch_timer_func_ptr func);
int irq_buffer_init(percpu_buffer_info* buffer_info, unsigned char* addr, unsigned int size);
int task_buffer_init(percpu_buffer_info* buffer_info, unsigned char* addr, unsigned int size);
int cpuidle_buffer_init(percpu_buffer_info* buffer_info, unsigned char* addr, unsigned int size);
int cpu_onoff_buffer_init(unsigned char* addr, unsigned int size);
int syscall_buffer_init(unsigned char* addr, unsigned int size);
int hung_task_buffer_init(unsigned char* addr, unsigned int size);
int buddy_fail_buffer_init(unsigned char* addr, unsigned int size);

#ifdef CONFIG_HISI_BB
void irq_trace_hook(unsigned int dir, unsigned int old_vec, unsigned int new_vec);
void task_switch_hook(const void *pre_task, void *next_task);
void cpuidle_stat_hook (u32 dir);
void cpu_on_off_hook(u32 cpu, u32 on);
void syscall_hook(u32 syscall_num, u32 dir);
void hung_task_hook(void *tsk, u32 timeout);
/*void buddy_fail_hook(u32 order); is declared in include/linux/gfp.h*/
#else
static inline void irq_trace_hook(unsigned int dir, unsigned int old_vec, unsigned int new_vec){}
static inline void task_switch_hook(const void *pre_task, void *next_task){}
static inline void cpuidle_stat_hook (u32 dir){}
static inline void cpu_on_off_hook(u32 cpu, u32 on){}
static inline void syscall_hook(u32 syscall_num, u32 dir){}
static inline void hung_task_hook(void *tsk, u32 timeout){}
static inline u32 get_current_last_irq(unsigned int cpu){}
#endif
int hisi_ap_hook_install(hook_type hk);
int hisi_ap_hook_uninstall(hook_type hk);

