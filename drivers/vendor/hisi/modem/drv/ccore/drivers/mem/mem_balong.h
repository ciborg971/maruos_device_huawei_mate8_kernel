
#ifndef    _BSP_MEM_H_
#define    _BSP_MEM_H_

#include <bsp_om.h>
#include "osl_cache.h"
#include "osl_types.h"
#include "mem_balong_drv.h"
#include <bsp_sram.h>
#include <mdrv_memory.h>
#include <bsp_ipc.h>
#include <mdrv_ipc.h>
#include <bsp_om.h>
#include <bsp_shared_ddr.h>
//#include <cacheLib.h>


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/**************************************************************************
  �궨��
**************************************************************************/

#define  mem_print_error(fmt,...)      (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  mem_print_dbg(fmt,...)		       (bsp_trace(BSP_LOG_LEVEL_DEBUG, BSP_MODU_MEM, "[mem]: <%s> <%d>"fmt"\n", __FUNCTION__, __LINE__, ##__VA_ARGS__))

#define STATIC

/**************************************************************************
  ��������
**************************************************************************/
void bsp_mem_init(void);
s32 bsp_set_most_used_size(u32 u32Size, u32 u32PoolType);

void* bsp_smalloc(u32 u32Size, MEM_POOL_TYPE enFlags);
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line);
void  bsp_sfree(void* pMem);
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line);
void *bsp_cachedma_malloc (unsigned int nBytes);
int   bsp_cachedma_free (void* buf);

/**************************************************************************
  �ӿ�����
**************************************************************************/

/*****************************************************************************
* �� �� ��  : BSP_SMALLOC
*
* ��������  : BSP ��̬�ڴ����(��spin lock����,��˳���ʹ��)
*
* �������  : sz: ����Ĵ�С(byte)
*             flags: �ڴ�����(ʹ��DDR / AXI)
* �������  : ��
* �� �� ֵ  : ����������ڴ�ָ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_SMALLOC(sz, flags) bsp_smalloc_dbg(sz, (MEM_POOL_TYPE)flags, (u8*)__FILE__, __LINE__)
#else
#define BSP_SMALLOC(sz, flags) bsp_smalloc(sz, flags)
#endif

/*****************************************************************************
* �� �� ��  : BSP_SFREE
*
* ��������  : BSP ��̬�ڴ��ͷ�(��spin lock����,��˳���ʹ��)
*
* �������  : ptr: ��̬�ڴ�ָ��
* �������  : ��
* �� �� ֵ  : ��
*****************************************************************************/
#ifdef __BSP_DEBUG__
#define BSP_SFREE(ptr) bsp_sfree_dbg(ptr, (u8*)__FILE__, __LINE__)
#else
#define BSP_SFREE(ptr) bsp_sfree(ptr)
#endif
/*������Ϊ����������warnning*/
s32 bsp_mem_info(u32 u32MemType);
s32 bsp_mem_dump_alloc_list(u32 u32Size, u32 u32PoolType);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _BSP_MEM_H_ */

