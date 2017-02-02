#ifndef _HI_GLOBAL_SRAM_MAP_INCLUDE_H_
#define _HI_GLOBAL_SRAM_MAP_INCLUDE_H_


#include "soc_baseaddr_interface.h"

/*******************************************
��˹���ͷ�ļ�
�������������ϵͳ���ͷ�ļ�
*******************************************/

#define SRAM_BASE_ADDR              (SOC_SRAM_OFF_BASE_ADDR)

/*��72KB���ֳ�������*/
#define SRAM_SIZE                   (0x12000)

/*��һ����:7KB*/
#define SRAM_SECTION1_SIZE          (0x1C00)

/*�ڶ�����:64KB*/
#define SRAM_SECTION2_SIZE          (0x10000)

/*��������:1KB*/
#define SRAM_SECTION3_SIZE          (0x400)

/*-------------------------------------------------------------------------------
                            SRAM����(��ʱ����)
  -------------------------------------------------------------------------------
  onchiprom/fastboot�����׶�:
                          -----------------------
                         |  fastboot1��VRL       |->2KB
                          -----------------------
                         |  fastboot1��������    |----
                          -----------------------     |->69KB
                         |  onchiprom��ջ        |----
                          -----------------------
                         |  �����־��           |->1KB
                          -----------------------
  linux/vxworks�׶�:
                          -----------------------
                         |  �͹�������           |->7KB
                          -----------------------
                         |  ��ȫOS               |->64KB
                          -----------------------
                         |  �����־��           |->1KB
                          -----------------------

-------------------------------------------------------------------------------*/

/*pm use section 7K*/
#define PM_SRAM_ADDR                (SRAM_BASE_ADDR)
#define PM_SRAM_SIZE                (SRAM_SECTION1_SIZE)

/*teeos use section 64K*/
#define TEEOS_SRAM_ADDR             (SRAM_BASE_ADDR + SRAM_SECTION1_SIZE)
#define TEEOS_SRAM_SIZE             (SRAM_SECTION2_SIZE)

/*general use section 1K*/
#define GENERAL_SRAM_ADDR           (SRAM_BASE_ADDR + SRAM_SECTION1_SIZE + SRAM_SECTION2_SIZE)
#define GENERAL_SRAM_SIZE           (SRAM_SECTION3_SIZE)



/*******************************************
MODEM SRAM�������
*******************************************/
/*GU DSP LOAD*/
#define MEMORY_AXI_DSP_LOAD_ADDR      (SOC_Modem_SRAM_BASE_ADDR)
#define MEMORY_AXI_DSP_LOAD_SIZE      (896*1024)

/*******************************************
FASTBOOT1 HARQ_RAM ����
-----------------------
         fastboot1 ���пռ�           256KB
         fastboot1 log �洢�ռ�       32KB
*******************************************/
/*harqmem����ַ*/
#define FASTBOOT_HARQMEM_BASE_ADDR    (SOC_XG2RAM0_HARQ_BASE_ADDR)
/*fastboot ����ʹ��harqmem��С*/
#define FASTBOOT_RUN_SIZE             (0x40000)  

/*log �洢�ռ��ַ*/
#define FASTBOOT_HARQMEM_LOG_ADDR     (SOC_XG2RAM0_HARQ_BASE_ADDR + FASTBOOT_RUN_SIZE) 
/*log �洢�ռ��С*/
#define FASTBOOT_HARQMEM_LOG_SIZE      (0x8000)

#endif /*_HI_GLOBAL_MEM_MAP_INCLUDE_H_*/

