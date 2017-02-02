

#ifndef SRECORDER_MEMORY_H
#define SRECORDER_MEMORY_H


/*----includes-----------------------------------------------------------------------*/

#include <asm/io.h>
#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

#define SRECORDER_MEMCPY_TOIO _memcpy_toio
#define SRECORDER_MEMCPY_FROMIO _memcpy_fromio
#define SRECORDER_MEMSET _memset_io
#define SRECORDER_WRITEB writeb
#define SRECORDER_WRITEW writew
#define SRECORDER_WRITEL writel

#define FLUSH_DCACHE_EVERY_TIME_WHEN_WRITE (0)


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: void srecorder_set_contiguous_virt_addr_flag(void)
    @brief: ����s_srecorder_has_contiguous_virt_addr��ֵ

    @param: flag 
    
    @return: none

    @note: 
*/
void srecorder_set_contiguous_virt_addr_flag(bool flag);


/**
    @function: bool srecorder_has_contiguous_virt_addr(void)
    @brief: �ж�SRecorder�Ƿ�ӵ�������������ַ�ռ�

    @param: none 
    
    @return: true - SRecorderӵ�������������ַ�ռ�, false - SRecorderû�������������ַ�ռ�

    @note: 
*/
bool srecorder_has_contiguous_virt_addr(void);


/**
    @function: void srecorder_read_data_from_phys_page(char *pdst, unsigned long phys_src, size_t bytes_to_read)
    @brief: ���������ַ����ÿ������ҳ�������

    @param: pdst д���ַ
    @param: phys_src Դ����������ʼ��ַ
    @param: bytes_to_read Ҫ��ȡ�����ݳ���
    
    @return: �ɹ���ȡ���ֽ���

    @note: 
*/
int srecorder_read_data_from_phys_page(char *pdst, unsigned long phys_src, size_t bytes_to_read);


/**
    @function: int srecorder_write_data_by_page(unsigned long phys_dst, size_t phys_mem_size, 
        char *psrc, size_t bytes_to_write)
    @brief: ���������ַ����ÿ������ҳ��д������

    @param: phys_dst ������ʼ��ַ
    @param: phys_mem_size ����ռ��С
    @param: psrc ԭʼ���ݻ���
    @param: bytes_to_write ԭʼ���ݳ���
    
    @return: д�뻺����ֽ���

    @note: 
*/
int srecorder_write_data_to_phys_page(unsigned long phys_dst, size_t phys_mem_size, 
    char *psrc, size_t bytes_to_write);


/**
    @function: void srecorder_release_virt_addr(psrecorder_virt_zone_info_t pzone_info)
    @brief: �ͷ�Ӧ��ʹ�ù��������ַ�ռ�

    @param: pzone_info 

    @return: none

    @note: 
*/
void srecorder_release_virt_addr(psrecorder_virt_zone_info_t pzone_info);


/**
    @function: bool srecorder_map_phys_addr(psrecorder_virt_zone_info_t pzone_info)
    @brief: ӳ�������ڴ浽�����ַ�ռ�

    @param: pzone_info 
    
    @return: true - ӳ��ɹ���false - ʧ��

    @note: 
*/
bool srecorder_map_phys_addr(psrecorder_virt_zone_info_t pzone_info);


/**
    @function: int srecorder_init_memory(void)
    @brief: ��ʼ���ڴ�ӳ�����ģ��

    @param: pinit_params ģ���ʼ������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_memory(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_memory(void)
    @brief: �˳��ڴ�ӳ�����ģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_memory(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_MEMORY_H */

