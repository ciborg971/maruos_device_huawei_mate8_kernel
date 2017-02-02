
#include <string.h>
#include <drv_comm.h>
#include <mdrv_memory.h>
#include <osl_types.h>
#include <stdlib.h>
#include <mem_balong.h>

/*****************************************************************************
* �� �� ��  : mdrv_memcpy
*
* ��������  : ���ݿ����ӿڡ��ײ���ڻ��ʵ�ֵ����Ż��ӿڣ�Ŀǰ��v8r1��ʹ�á�
*
* �������  :  dest : ������Ŀ�ĵ�ַ
*              src  : ������Դ��ַ
*             count : �������ݵĴ�С
* �������  : ��
* �� �� ֵ  : ��
****************************************************************************/
extern void * __rt_memcpy(void * dest, const void * src, unsigned long count);
void * mdrv_memcpy(void * dest, const void * src, unsigned long count)
{
    return __rt_memcpy(dest,src,count);
}

/*****************************************************************************
* �� �� ��  : mdrv_cachedmem_alloc
*
* ��������  :ΪDMA�豸������������һ��cache��ȫ���ڴ档
*
* �������  : bytes: ��Ҫ������ֽڵ�����
*
* �������  : ��
* �� �� ֵ  :  NULL :    �����ڴ�ʧ��
*            ��NULLָ��: �����ڴ�ɹ�����ָ��ָ�������ڴ���ָ��
****************************************************************************/
void* mdrv_cachedmem_alloc (unsigned int  bytes)
{
#ifdef CONFIG_MEM
    return bsp_cachedma_malloc(bytes);
#else
    return NULL;
#endif
}

/*****************************************************************************
* �� �� ��  : mdrv_cachedmem_free
*
* ��������  :�ͷ���mdrv_cachedmem_alloc������ڴ档
*
* �������  : pBuf:ָ��Ҫ�ͷŵ��ڴ���ָ��
*
* �������  : ��
* �� �� ֵ  :  0: �ɹ�
*             -1: ʧ��
****************************************************************************/
int mdrv_cachedmem_free(void*  pBuf)
{
#ifdef CONFIG_MEM
    return bsp_cachedma_free(pBuf);
#else
    return MDRV_OK;
#endif
}
/*****************************************************************************
* �� �� ��  : mdrv_smalloc
*
* ��������  :Ϊ����һ���ڴ档
*
* �������  : size: ��Ҫ������ֽڵ�����
*
* �������  : ��
* �� �� ֵ  :     NULL : �����ڴ�ʧ��
*            ��NULLָ��: �����ڴ�ɹ�����ָ��ָ�������ڴ���ָ��
****************************************************************************/
void* mdrv_smalloc (unsigned int size,MEM_POOL_TYPE flags)
{
#ifdef CONFIG_MEM
    return bsp_smalloc(size, flags);
#else
    return NULL;
#endif
}

/*****************************************************************************
* �� �� ��  : mdrv_sfree
*
* ��������  :�ͷ���mdrv_smalloc������ڴ档
*
* �������  : pBuf:ָ��Ҫ�ͷŵ��ڴ���ָ��
*
* �������  : ��
* �� �� ֵ  :  0: �ɹ�
*             -1: ʧ��
****************************************************************************/
int mdrv_sfree(void*  pBuf)
{
#ifdef CONFIG_MEM
    bsp_sfree(pBuf);
#endif
    return MDRV_OK;
}

/*****************************************************************************
 �� �� ��  : mdrv_get_freeblockmem
 ��������  : �ͷ�mem
 �������  :
 �������  :

 ����ֵ    ��0    �ɹ�
             -1   ʧ��
*****************************************************************************/
int mdrv_get_freeblockmem(void)
{
    return 0;
}

#if 0
BSP_VOID* bsp_malloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags)
{
    return malloc(u32Size);
}
BSP_VOID* bsp_malloc_dbg(BSP_U32 u32Size, MEM_POOL_TYPE enFlags, BSP_U8* pFileName, BSP_U32 u32Line)
{
    return malloc(u32Size);
}
BSP_VOID  bsp_free(BSP_VOID* pMem)
{
    free(pMem);
    return;
}
BSP_VOID  bsp_free_dbg(BSP_VOID* pMem, BSP_U8* pFileName, BSP_U32 u32Line)
{
    free(pMem);
    return;
}
BSP_VOID* bsp_smalloc(BSP_U32 u32Size, MEM_POOL_TYPE enFlags)
{
    return malloc(u32Size);
}
void* bsp_smalloc_dbg(u32 u32Size, MEM_POOL_TYPE enFlags, u8* pFileName, u32 u32Line)
{
    return malloc(u32Size);

}
BSP_VOID  bsp_sfree(BSP_VOID* pMem)
{
    free(pMem);
    return;
}
void  bsp_sfree_dbg(void* pMem, u8* pFileName, u32 u32Line)
{
    free(pMem);
    return;
}
#endif




