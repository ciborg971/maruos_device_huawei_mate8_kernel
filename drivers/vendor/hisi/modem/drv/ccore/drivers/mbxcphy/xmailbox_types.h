

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
#define     DRV_ERRNO_XMBX_WR_FULL       0x1070   /* ���������� */
#define     DRV_ERRNO_XMBX_DSP_IPC       0x1071   /* ������������DSP IPC֪ͨARM */
#define     DRV_ERRNO_XMBX_PS_TIMEOUT    0x1072   /* PS��DSP��Ϣ��ʱ */
#define     DRV_ERRNO_XMBX_UP_WR         0x1073   /* ��������дָ���쳣 */
#define     DRV_ERRNO_XMBX_DL_MOD        0x1074   /* ���������ָ��MOD�쳣 */


#endif


#if defined(__OS_VXWORKS__)

#define xMbx_Memcpy(dst,src,len)       memcpy(dst,src,len)
#define xMbx_Memset(src,count,len)     memset(src,count,len)

#elif defined(__OS_RTOSCK__)

#define xMbx_Memcpy(dst,src,len)       (void)memcpy_s(dst,len,src,len)
#define xMbx_Memset(src,count,len)     (void)memset_s(src, len, count,len)

#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif


#endif /* end of mailbox_types.h */

