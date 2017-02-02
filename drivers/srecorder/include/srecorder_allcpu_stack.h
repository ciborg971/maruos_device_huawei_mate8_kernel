

#ifndef SRECORDER_ALLCPU_STACK_H
#define SRECORDER_ALLCPU_STACK_H


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
    @function: int srecorder_get_allcpu_stack(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡ����ʱ���л CPU�ĵ���ջ

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_allcpu_stack(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function:int srecorder_init_allcpu_stack(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��allcpu stackģ��

    @param: pinit_params ģ���ʼ������
        
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_allcpu_stack(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_allcpu(void)
    @brief: ģ���˳�������������Ҫ���������allcpu stackģ���еı���s_reserved_mem_info_for_log_temp��
           ��Ϊ�ڵȴ�workqueue��ɼ��cpu����ջ�ĳ�ʱʱ�䵽���Ժ����ǲ���ϣ���������̻߳���������
           SRecorder�ı����ڴ���д���ݣ���˱����������ΪNULL��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_allcpu_stack(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_ALLCPU_STACK_H */

