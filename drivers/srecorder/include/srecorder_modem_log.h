

#ifndef SRECORDER_MODEM_LOG_H
#define SRECORDER_MODEM_LOG_H


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
    @function: int srecorder_get_modem_log(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡmodem������ջ��������־

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_modem_log(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_modem_log(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��modem��־ģ��

    @param: pinit_params ģ���ʼ������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_modem_log(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_modem_log(void)
    @brief: �˳�modem��־ģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_modem_log(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_MODEM_LOG_H */

