
#ifndef    _BSP_MEM_DRV_H_
#define    _BSP_MEM_DRV_H_

#include "product_config.h"
#include "bsp_sram.h"
#include "bsp_shared_ddr.h"

#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ASIC2 ���� */

/**************************************************************************
  �궨��
**************************************************************************/
/* ���˶��� */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#define BSP_MEM_MAIN_PART
#endif

/* ���ȶ��� */
#ifdef PRODUCT_CFG_CORE_TYPE_MODEM
#define MEM_NORM_DDR_POOL_SIZE      (512*1024)
#else
#define MEM_NORM_DDR_POOL_SIZE      (1024*1024)/*2^n*4K*/
#endif

#define MEM_ICC_DDR_POOL_SIZE       (SHM_SIZE_MEMMGR)
#define MEM_ICC_AXI_POOL_SIZE       (SRAM_SIZE_DYNAMIC_SEC)

/* Mem ȫ�ֱ�������AXI�� */
#define MEM_CTX_ADDR                ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MEMMGR_FLAG)


/* ����ַ���� */
#define MEM_NORM_DDR_POOL_BASE_ADDR (memalign(32, MEM_NORM_DDR_POOL_SIZE))
#define MEM_ICC_AXI_POOL_BASE_ADDR  ((unsigned long)SRAM_BASE_ADDR + SRAM_OFFSET_DYNAMIC_SEC)
#define MEM_ICC_DDR_POOL_BASE_ADDR  ((unsigned long)SHM_BASE_ADDR + SHM_OFFSET_MEMMGR)


/* ʹ��ACPģʽ����Ҫˢ Cache */
//#define MEM_USE_ACP

#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* _BSP_MEM_DRV_H_ */



