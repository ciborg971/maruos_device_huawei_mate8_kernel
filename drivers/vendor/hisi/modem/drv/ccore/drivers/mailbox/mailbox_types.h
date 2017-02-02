

#ifndef __MAILBOX_TYPES_H__
#define __MAILBOX_TYPES_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#include "product_config.h"
#if defined(__OS_RTOSCK__)
#include "securec.h"
#endif

#ifdef CONFIG_MAILBOX_TYPE
#include <string.h>
#include <osl_irq.h>
#include <osl_malloc.h>
#include <osl_sem.h>
#include <bsp_dump.h>
#include <bsp_dump_drv.h>
#include <bsp_ipc.h>
#include <bsp_sram.h>
#include <drv_comm.h>
#include <bsp_om.h>
#include <bsp_external_stub.h>

#ifdef BSP_CONFIG_P532_FPGA

#ifdef FEATURE_CONFIG_P532_DALLAS
#define MBX_IPC_CORE_DSP                    (IPC_CORE_LDSP)
#else
#define MBX_IPC_CORE_DSP                    (IPC_CORE_BBE)
#endif

#else
#define MBX_IPC_CORE_DSP                    (IPC_CORE_LDSP)
#endif
#define MBX_LDSP_WAKEUP_ADDR                (&((SRAM_SMALL_SECTIONS*)((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DSP_DRV)

/*lint -save -e652 -e683*/
#ifndef printf
#define printf(fmt,...)     bsp_trace(BSP_LOG_LEVEL_ERROR,BSP_MODU_MBX,fmt,##__VA_ARGS__)
#endif
/*lint -restore*/
#else

#ifdef __OS_RTOSCK__
#else
#include <semLib.h>
#endif
#include <osal.h>
#include <BSP_GLOBAL.h>
#include <BSP.h>
#include <general_sram_map.h>
#include "tl_balong_common.h"


#ifndef WAIT_FOREVER
#define WAIT_FOREVER   (-1)
#endif



/*lint -save -e528*/
typedef OSAL_SEM_ID osl_sem_id;

#define osl_sem_init(val,sem)                       (void)OSAL_SemBCreate(sem,(int)val,OSAL_SEM_FIFO)
#define osl_sem_up(sem)                             (void)OSAL_SemGive(*sem)
#define osl_sem_downtimeout(sem,jiffies)            OSAL_SemTake(*sem,jiffies)

/*lint -restore*/

extern void systemError(int modId, int arg1, int arg2, char * arg3, int arg3Length);

#define system_error(m,a1,a2,a3,l)          systemError((int)m,(int)a1,(int)a2,(char*)a3,(int)l)
#define bsp_trace                           BSP_TRACE

#define MBX_IPC_CORE_DSP                    (IPC_CORE_BBE16)
#define MBX_LDSP_WAKEUP_ADDR                (MEMORY_AXI_LDSP_AWAKE_ADDR)

/*system error modid*/
#define     DRV_ERRNO_MBX_WR_FULL       0x1050   /* ���������� */
#define     DRV_ERRNO_MBX_DSP_IPC       0x1051   /* ������������DSP IPC֪ͨARM */
#define     DRV_ERRNO_MBX_PS_TIMEOUT    0x1052   /* PS��DSP��Ϣ��ʱ */
#define     DRV_ERRNO_MBX_UP_WR         0x1053   /* ��������дָ���쳣 */
#define     DRV_ERRNO_MBX_DL_MOD        0x1054   /* ���������ָ��MOD�쳣 */


#endif


#if defined(__KERNEL__)

#define Mbx_Memcpy(dst,src,len)       memcpy(dst,src,len)
#define Mbx_Memset(src,count,len)     memset(src,count,len)

#elif defined(__OS_VXWORKS__)

#define Mbx_Memcpy(dst,src,len)       memcpy(dst,src,len)
#define Mbx_Memset(src,count,len)     memset(src,count,len)

#elif defined(__OS_RTOSCK__)

#define Mbx_Memcpy(dst,src,len)       (void)memcpy_s(dst,len,src,len)
#define Mbx_Memset(src,count,len)     (void)memset_s(src, len, count,len)

#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of mailbox_types.h */

