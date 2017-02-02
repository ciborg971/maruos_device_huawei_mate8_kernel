#ifndef __L2CACHE_SCREENING_H__
#define __L2CACHE_SCREENING_H__

/************************DDRʹ��˵��*************************************************************************************
                                         |(DDR_MEM_ADDR --- DDR_MEM_ADDR+0x4000)            **ҳ��16K
*(DDR_MEM_ADDR -DDR_MEM_ADDR+0x100000)   |(DDR_MEM_ADDR + 0x4000 --- DDR_MEM_ADDR+0x10000)  **SP
*��ʼ��1M�ռ䲻������ʹ��                |(DDR_MEM_ADDR + 0x100000 -0x4)                      **���ڴ�Ų��Ա��

*(DDR_MEM_ADDR + 0x100000 -DDR_MEM_ADDR+0x300000)  ��������ʹ�� 3M  
*(DDR_MCORE_ADDR + 0x400000 -DDR_MCORE_ADDR+0x900000)  ���ڴ��A9�ľ���(MCORE_TEXT_START_ADDR)
*(DDR_MCORE_ADDR + 0xA00000 -DDR_MCORE_ADDR+DDR_MCORE_SIZE) MCORE DDR����������
*************************************************************************************************************************/
#include <product_config.h>
#include <securec.h>
#include <soc_memmap.h>

#define MINI_DDR_BASE_ADDR       (DDR_MEM_ADDR)
#define MINI_DDR_MEM_SIZE        (DDR_MEM_SIZE)
#define MINI_MODEM_IMAGE_ADDR    (MCORE_TEXT_START_ADDR)
#define MINI_TLB_BASE_ADDR       (MINI_DDR_BASE_ADDR) /*ҳ�����ַ*/
#define MINI_PAGE_SIZE           (0x100000)           /*ҳ��С1M*/
#define L2CACHE_TEST_FLAG_ADDR   (MINI_DDR_BASE_ADDR + MINI_PAGE_SIZE - 0x4)/*���Խ�����*/
#define L2CACHE_TEST_START_ADDR  (MINI_DDR_BASE_ADDR + 0xA00000)           /*���Կ�ʼ�ĵ�ַ*/
#define L2CACHE_TEST_END_ADDR    (DDR_MCORE_ADDR + DDR_MCORE_SIZE) /*���Խ����ĵ�ַ*/

#define MINI_OS_ASM     __asm__ __volatile__

#define L2_CTRL_BASE             HI_MDMA9_L2_REGBASE_ADDR
#define L2_CACHE_ID              (L2_CTRL_BASE + 0x0)
#define L2_CACHE_TYPE            (L2_CTRL_BASE + 0x4)
#define L2_CONTROL               (L2_CTRL_BASE + 0x100)
#define L2_AUX_CONTROL           (L2_CTRL_BASE + 0x104)
#define L2_INT_MASK              (L2_CTRL_BASE + 0x214)
#define L2_INT_CLEAR             (L2_CTRL_BASE + 0x220)

#define L2_CACHE_SYNC            (L2_CTRL_BASE + 0x730)
#define L2_INVALIDATE_PA         (L2_CTRL_BASE + 0x770)
#define L2_INVALIDATE_WAY        (L2_CTRL_BASE + 0x77c)
#define L2_CLEAN_PA              (L2_CTRL_BASE + 0x7b0)
#define L2_CLEAN_WAY             (L2_CTRL_BASE + 0x7bc)
#define L2_CLEAN_INVALIDATE_PA   (L2_CTRL_BASE + 0x7f0)
#define L2_CLEAN_INVALIDATE_WAY  (L2_CTRL_BASE + 0x7fc)

#define L2_PREFETCH_CTRL         (L2_CTRL_BASE + 0xF60)
#define L2_POWER_CTRL            (L2_CTRL_BASE + 0xF80)

#define AUX_EARLY_BRESP         (0x1<<30)
#define AUX_INSTR_PREFETCH      (0x1<<29)
#define AUX_DATA_PREFETCH       (0x1<<28)
#define AUX_FULL_LINE_OF_ZERO   (0x1<<0)

#define PREF_DOUBLE_LINEFILL    (0x1<<30)
#define PREF_INSTR_PREFETCH     (0x1<<29)   /*the same to aux bit29*/
#define PREF_DATA_PREFETCH      (0x1<<28)  /*the same to aux bit28*/
#define PREF_PREFETCH_DROP      (0x1<<24)
#define PREF_PREFETCH_OFFSET    (0x7)

#define POWER_CLK_GATING        (0x1<<1)
#define POWER_STANDBY_MODE      (0x1<<0)

#define L2_CONTROL_ENABLE        (0x1)
#define L2_WAY_ALL               (0xff) /* 8-ways */
#define L2_OPERATION_IN_PROGRESS (0x1)
#define L2_INT_MASK_ALL          (0x0)
#define L2_INT_CLEAR_ALL         (0x1ff)

#define L2_CACHE_SIZE            (0x80000)
#define L2_CACHE_LINE_SIZE       (0x20)
#define L2_CACHE_LINE_MASK       (L2_CACHE_LINE_SIZE - 1)

#define BIT_A9_FULL_LINE         (3)
#define BIT_A9_L1_PREFETCH       (2)
#define BIT_A9_L2_PREFETCH_HINTS (1)

#define SCU_CTRL_OFFSET          (0x0)
#define SCU_IC_STANDBY           (0x1<<6)
#define SCU_STANDBY              (0x1<<5)
#define SCU_SPECUL_LINEFILL      (0x1<<3)
#define SCU_SCU_ENABLE           (0x1<<0)

#define SCU_CTRL_CONFIG          (SCU_IC_STANDBY|SCU_STANDBY|SCU_SPECUL_LINEFILL|SCU_SCU_ENABLE)

#define ARMA9CTX_REGISTER_READ(reg_addr) \
    *(volatile unsigned int *)(reg_addr)

#define ARMA9CTX_REGISTER_WRITE(reg_addr, data)\
    *(volatile unsigned int *)(reg_addr) = (data)

#define CACHE_FLUSH_AND_INV_ALL \
  	do{ \
        (void)l1Dcache_flush_all_mini();\
        l2cache_flush_mini();\
        (void)l1Dcache_flush_inv_all_mini();\
	}while(0)
extern unsigned int l1cache_inv_all_mini(void);
extern unsigned int l1cache_enable_mini(void);
extern unsigned int l1Dcache_flush_all_mini(void);
extern unsigned int l1Dcache_flush_inv_all_mini(void);
void l2cache_flush_mini(void);
void l2cache_screening_case(void);
#endif

