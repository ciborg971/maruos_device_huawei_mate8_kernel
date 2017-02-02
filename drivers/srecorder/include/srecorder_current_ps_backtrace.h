

#ifndef SRECORDER_CURRENT_PS_BACKTRACE_H
#define SRECORDER_CURRENT_PS_BACKTRACE_H


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
    @function: int srecorder_get_current_ps_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡ����ʱ��ǰ���̵ĵ���ջ.
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_current_ps_backtrace(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_dmesg(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��current ps backtraceģ��

    @param: pinit_params ģ���ʼ������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_current_ps_backtrace(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_current_ps_backtrace(void)
    @brief: �˳�current ps backtraceģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_current_ps_backtrace(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_CURRENT_PS_BACKTRACE_H */

