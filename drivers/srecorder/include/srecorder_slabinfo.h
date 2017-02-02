

#ifndef SRECORDER_SLABINFO_H
#define SRECORDER_SLABINFO_H


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
    @function: int srecorder_get_slabinfo(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡslabinfo

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_slabinfo(srecorder_reserved_mem_info_t *pmem_info);


/**
    @function: int srecorder_init_slabinfo(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��slabinfoģ��

    @param: pinit_params ģ���ʼ������
        
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_slabinfo(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_slabinfo(void)
    @brief: �˳�slabinfoģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_slabinfo(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_SLABINFO_H */

