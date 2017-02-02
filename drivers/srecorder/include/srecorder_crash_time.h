

#ifndef SRECORDER_CRASH_TIME_H
#define SRECORDER_CRASH_TIME_H


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
    @function: int srecorder_get_crash_time(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��¼����������ʱ�䣬˳���¼������ԭ��

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_crash_time(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_crash_time(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��crash timeģ��

    @param: pinit_params ģ���ʼ������
        
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_crash_time(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_crash_time(void)
    @brief: �˳�crash timeģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_crash_time(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_CRASH_TIME_H */

