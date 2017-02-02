/*************************************************************************
*   ��Ȩ����(C) 1987-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  IPC_BALONG.h
*************************************************************************/

#ifndef _IPC_BALONG_H_
#define _IPC_BALONG_H_
#include <bsp_ipc.h>
#include <osl_irq.h>
#include <osl_types.h>
#include <osl_sem.h>
#include <osl_spinlock.h>
#ifdef __cplusplus
extern "C" {
#endif

#define BSP_IPC_CPU_RAW_INT(i)		(0x400 + (i * 0x10))
#define BSP_IPC_CPU_INT_MASK(i)		(0x404 + (i * 0x10))
#define BSP_IPC_CPU_INT_STAT(i)		(0x408 + (i * 0x10))
#define BSP_IPC_CPU_INT_CLR(i)		(0x40C + (i * 0x10))

#define BSP_IPC_SEM_RAW_INT(i)		(0x600 + (i * 0x10))
#define BSP_IPC_SEM_INT_MASK(i)		(0x604 + (i * 0x10))
#define BSP_IPC_SEM_INT_STAT(i)		(0x608 + (i * 0x10))
#define BSP_IPC_SEM_INT_CLR(i)		(0x60C + (i * 0x10))

#define BSP_IPC_HS_CTRL(i,j)		(0x800 + (i * 0x100) + (j * 0x8 ))
#define BSP_IPC_HS_STAT(i,j)		(0x804 + (i * 0x100) + (j * 0x8 ))


#ifndef SEM_FULL
#define SEM_FULL            (1)
#endif
#ifndef SEM_EMPTY
#define SEM_EMPTY           (0)
#endif

struct ipc_debug_s
{
	u32 u32RecvIntCore;										/*��ǰ�����ж�Ŀ���ID*/
	u32 u32IntHandleTimes[INTSRC_NUM];						/*��¼ĳ���жϽ��մ���*/
	u32 u32IntSendTimes[IPC_CORE_BUTTOM][INTSRC_NUM];		/*��¼��ÿ���˷���ÿ���жϵĴ���*/
	u32 u32SemId;											/*��ǰռ���ź���*/
	u32 u32SemTakeTimes[INTSRC_NUM];						/*ĳ�ź���ռ�óɹ�����*/
	u32 u32SemTakeFailTimes[INTSRC_NUM];					/*ĳ�ź���ռ��ʧ�ܴ���*/
	u32 u32SemGiveTimes[INTSRC_NUM];						/*ĳ�ź����ͷŴ���*/
	u32 u32IntTimeDelta[INTSRC_NUM];						/*��¼ÿ���ж϶�Ӧ����������ʱ��*/
};
struct ipc_control{
    u32     core_num;										/*��¼IPCģ�鹤�����ڵĺ�ID*/
    u32     ipc_base;										/*ipc��ַ*/
    bool   sem_exist[INTSRC_NUM];							/*��¼�ź����Ƿ��Ѿ�����*/
    struct ipc_entry ipc_int_table[INTSRC_NUM];				/*��¼ÿһ���ж�Դע��Ļص�����*/
    osl_sem_id	 sem_ipc_task[INTSRC_NUM];
    spinlock_t lock;
	unsigned long last_int_cb_addr;  /* ���һ�����ص����жϺ����ĵ�ַ */
};

#ifdef __cplusplus
}
#endif

#endif /* end #define _IPC_BALONG_H_*/

