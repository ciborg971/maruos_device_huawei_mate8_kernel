

#ifndef ICC_PLATFORM_H
#define ICC_PLATFORM_H

#ifdef __cplusplus
extern "C" {
#endif

#include <cmsis_os.h>
#include <osl_common.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#include <osl_malloc.h>
#include <bsp_hardtimer.h>
#include <bsp_dump.h>
#include <libfdt.h>
#include <bsp_ipc.h>
#include <bsp_icc.h>

#define ICC_CHANNEL_INIT_COMPITABLE  "hisilicon,icc_balong_m3"

#define  ICC_THIS_CPU                  (ICC_CPU_MCU)
#define  ICC_RECV_IPC_SHARED          (IPC_MCU_INT_SRC_ICC)
#define  ICC_TASK_STK_SIZE            (512)
#define  NOTIFY_STOP_MASK             (0x8000)
#define  ICC_TASK_SHARED_PRI          (osPriorityAboveNormal)

#define ICC_SDDR_START_ADDR_ON_THIS_COER    (ICC_DBG_MSG_ADDR_IN_DDR + ICC_DBG_MSG_LEN_IN_DDR)
#define ICC_SRAM_START_ADDR_ON_THIS_CORE    (ADDR_MCCORE_SEND)

typedef  osSemaphoreId osl_sem_id;
typedef osThreadId icc_task_id;
typedef  s32 wait_queue_head_t;

#define WAKE_LOCK_SUSPEND (0)
#define kthread_stop(id) osThreadTerminate(id)
#define osl_sem_init(val, name)  osSemaphoreCreate(osSemaphore(name), val)
#define kthread_stop(id) osThreadTerminate(id)

#define  icc_print_error(fmt, ...)    (printk("<%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
#define  icc_print_info                printk
#define  icc_print_notice(fmt, ...)
#define icc_print_debug(fmt, ...)

#define memset_s(dest, destMax, val, count) memset(dest, val, count)
#define memcpy_s(dest, destMax, src, count) memcpy(dest, src, count)
#define sprintf_s(buf, max_dst_size, fmt, ...)   sprintf(buf, fmt, ...)


struct icc_channel_vector
{
	read_cb_func  read_cb;        /* ���������Ķ��ص�����ָ�� */
	void          *read_context;  /* ���������Ķ��ص�����context */
	write_cb_func write_cb;       /* ����������д�ص�����ָ�� */
	void          *write_context; /* ����������д�ص�����context */
};

struct wake_lock
{
	int lock;
};

struct icc_control
{
	u32                cpu_id;                    /* ��ǰ��cpu id */
	u32                state;                     /* icc���ƽṹ��״̬: ����|������ */
	icc_task_id        shared_task_id;            /* ͨ����������id */
	u32                shared_recv_ipc_irq_id;    /* ͨ������Ľ�������ʹ��ipc�ж� */
	osl_sem_id         shared_task_sem;           /* ����ͨ������������ź��� */
	struct icc_channel *channels[ICC_CHN_ID_MAX]; /* icc_channel�Ľṹ��ָ������ */
	u32                channel_size;              /* ͨ����Ŀ */
	struct             wake_lock wake_lock;
};

static inline void icc_system_error(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length){return ;}
static inline void icc_wake_lock_init(struct wake_lock *lock, int lock_id, const char *name){return ;}
static inline void icc_wake_lock(struct wake_lock *lock){return ;}
static inline void icc_wake_unlock(struct wake_lock *lock){return ;}
static inline void bsp_icc_channel_uninit(u32 real_channel_id){return ;}
static inline int icc_pm_init(void){return ICC_OK;}
static inline int icc_ccore_is_reseting(u32 cpuid){return ICC_OK;}

static __inline__ osStatus osl_sem_up(osl_sem_id *sem){return osSemaphoreRelease(*sem);}
static __inline__ s32 osl_sem_down(osl_sem_id *sem){return osSemaphoreWait(*sem, osWaitForever);}
static __inline__ s32 osl_sem_downtimeout(osl_sem_id *sem, u32 ms)
{
	if(osSemaphoreWait(*sem, ms))
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
static __inline__ osStatus osl_sema_delete(osl_sem_id *sem){return osSemaphoreDelete(*sem);}

static inline void icc_debug_in_isr(void){return ;}
static inline s32  icc_debug_init(u32 channel_num){return ICC_OK;}
static inline int icc_channel_packet_dump(struct icc_channel_packet *packet){return ICC_OK;}
static inline void icc_packet_print(struct icc_channel_packet *packet){return ;}

#define icc_debug_before_send(packet)
#define icc_debug_after_send(channel, packet, data)
#define icc_debug_before_recv(pkg_header)
#define icc_debug_in_read_cb(channel_id, data, data_len, read_ptr, write_ptr)
#define icc_debug_after_recv(pkg_header)

#ifdef __cplusplus
}
#endif

#endif


