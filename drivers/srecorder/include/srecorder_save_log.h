

#ifndef SRECORDER_SAVE_LOG_H
#define SRECORDER_SAVE_LOG_H


/*----includes-----------------------------------------------------------------------*/

#include "srecorder_common.h"
#include "srecorder_snprintf.h"
#include "srecorder_memory.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: int srecorder_save_log(char *file_path, char *pbuf, int data_len)
    @brief: ���ں��н���Ϣ���浽�ļ���

    @param: file_path �ļ�·��
    @param: pbuf �����Ϣ���ڴ���ʼ��ַ
    @param: pbuf Ҫ��������ݳ���
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_save_log(char *file_path, char *pbuf, int data_len);


/**
    @function: int srecorder_renew_meminfo(srecorder_reserved_mem_t *pmem_info, int bytes_read)
    @brief: ����SRecorder�����ڴ���������Ϣ���ݽṹ

    @param: pmem_info 
    @param: bytes_read 
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_renew_meminfo(srecorder_reserved_mem_info_t *pmem_info, int bytes_read);


/**
    @function:int srecorder_write_info_header(srecorder_reserved_mem_t *pmem_info, 
        srecorder_info_type_e type, 
        psrecorder_info_header_t *pinfo_header)
    @brief: ��ʼ��������Ϣ��ͷ�����ݽṹ

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: type ��Ϣ����
    @param: pinfo_header ��Ϣͷ��У�����ݽṹ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_write_info_header(srecorder_reserved_mem_info_t *pmem_info, 
    srecorder_info_type_e type, 
    psrecorder_info_header_t *pinfo_header);


/**
    @function: int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len)
    @brief: �Ը��ֶ�λ��Ϣ��ͷ��������У��

    @param: pheader ������Ϣ��У��ͷ
    @param: data_len ÿ����Ϣ�����ݳ��ȣ�������У��ͷ������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_validate_info_header(srecorder_info_header_t *pheader, unsigned long data_len);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_SAVE_LOG_H */

