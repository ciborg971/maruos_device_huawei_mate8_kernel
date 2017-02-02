
#ifndef    _BSP_MEM_DRV_H_
#define    _BSP_MEM_DRV_H_

#include <linux/slab.h>
#include "BSP.h"
#include "MemoryLayout.h"
#include "MemoryMap.h"


#ifdef __cplusplus
extern "C"
{
#endif /* __cplusplus */

/* ASIC2 ���� */

#ifndef INLINE
#define INLINE __inline__
#endif

/**************************************************************************
  �궨��
**************************************************************************/

/* ���ȶ��� */
#define MEM_NORM_DDR_POOL_SIZE      (4096)/*2^n*4K*/
#define MEM_ICC_DDR_POOL_SIZE       (MEMORY_RAM_CORESHARE_MEMMGR_SIZE)

/* Mem ȫ�ֱ�������AXI�� */
#define MEM_CTX_ADDR                (IO_ADDRESS(MEMORY_AXI_MEMMGR_FLAG_ADDR))

/* ����ַ���� */
#define MEM_ICC_DDR_POOL_BASE_ADDR  (IO_ADDRESS(MEMORY_RAM_CORESHARE_MEMMGR_ADDR))
#define MEM_AXI_DICC_ADDR           (IO_ADDRESS(MEMORY_AXI_DICC_ADDR))
#define MEM_AXI_TEMP_PROTECT_ADDR   (IO_ADDRESS(MEMORY_AXI_TEMP_PROTECT_ADDR))
#define MEM_AXI_USB_CSHELL_ADDR     (IO_ADDRESS(MEMORY_AXI_USB_CSHELL_ADDR))
#define MEM_ICC_CTRL_CHAN_ADDR      (IO_ADDRESS(MEMORY_AXI_ICC_ADDR))
#define MEM_CORESHARE_MEM_ADDR      (IO_ADDRESS(MEMORY_RAM_CORESHARE_MEM_ADDR))
#define MEM_CORESHARE_SYNC_ADDR     (IO_ADDRESS(MEMORY_RAM_CORESHARE_SYNC_ADDR))


/* ��ַת�� */
#define DDR_VIRT_TO_PHY(addr)       (((unsigned int)addr) - IPC_SHARE_MEM_VIRT_ADDR + IPC_SHARE_MEM_ADDR)
#define DDR_PHY_TO_VIRT(addr)       (((unsigned int)addr) - IPC_SHARE_MEM_ADDR + IPC_SHARE_MEM_VIRT_ADDR)



#ifdef __cplusplus
}
#endif /* __cplusplus */



#endif /* _BSP_MEM_DRV_H_ */



