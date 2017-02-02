/*************************************************************************
*   ��Ȩ����(C) 1987-2013, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  IPC_BALONG.h
*************************************************************************/

#ifndef _IPC_BALONG_H_
#define _IPC_BALONG_H_
#include <bsp_ipc.h>
#include <soc_interrupts_m3.h>
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

#ifndef NULL
#define NULL (void*)0
#endif
#define MCPU_IPC_INT M3_IPCM_INT0_2
#define BAK_REG_NUM 10

#ifdef IPC_DEBUG_FEATURE
struct ipc_debug_s
{
	u32  u32RecvIntCore;										/*��ǰ�����ж�Ŀ���ID*/
	u32  u32IntHandleTimes[INTSRC_NUM];							/*��¼ĳ���жϽ��մ���*/
	u32  u32IntSendTimes[IPC_CORE_BUTTOM][INTSRC_NUM]; 			/*��¼��ÿ���˷���ÿ���жϵĴ���*/	
};
#endif

struct ipc_control{
    u32    core_num;									/* ��¼IPCģ�鹤�����ڵĺ�ID*/
    u32    ipc_base;									/*ipc��ַ*/
    struct ipc_entry ipc_int_table[INTSRC_NUM];			/*��¼ÿһ���ж�Դע��Ļص�����*/
    u32    ipc_store_reg_table[BAK_REG_NUM];			/*V7R2 ����ˣ�ÿ�����������Ĵ�����Ҫ���棬���������ж�����Ĵ�����IPC_CPU_INT_MASK�����ź����ͷ��ж�����Ĵ�����IPC_SEM_INT_MASK��������16��*/
	unsigned long last_int_cb_addr;  /* ���һ�����ص����жϺ����ĵ�ַ */
};

#ifdef __cplusplus
}
#endif

#endif /* end #define _IPC_BALONG_H_*/

