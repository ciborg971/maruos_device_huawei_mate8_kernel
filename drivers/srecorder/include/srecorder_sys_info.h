

#ifndef SRECORDER_SYS_INFO_H
#define SRECORDER_SYS_INFO_H


/*----includes-----------------------------------------------------------------------*/

#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: int srecorder_get_sys_info(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡ����ʱ��ǰϵͳ����Ϣ

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_sys_info(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_sys_info(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��sys infoģ��

    @param: pinit_params ģ���ʼ������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_sys_info(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_sys_info(void)
    @brief: �˳�sys infoģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_sys_info(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_SYS_INFO_H */

