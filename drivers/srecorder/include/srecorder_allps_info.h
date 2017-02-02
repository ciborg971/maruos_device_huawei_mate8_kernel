

#ifndef SRECORDER_ALLPS_INFO_H
#define SRECORDER_ALLPS_INFO_H


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
    @function: int srecorder_get_allps_info(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡ����ʱ���н��̵���Ϣ

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_allps_info(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_allps_info(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��allps infoģ��

    @param: pinit_params ģ���ʼ������
        
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_allps_info(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_allps_info(void)
    @brief: �˳�allps infoģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_allps_info(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_ALLPS_INFO_H */

