

#ifndef SRECORDER_DEV_H
#define SRECORDER_DEV_H


/*----includes-----------------------------------------------------------------------*/


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��SRecorder�ַ��豸ģ��

    @param: pinit_params ģ���ʼ������

    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_dev(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_snprintf(void)
    @brief: �˳�SRecorder�ַ��豸ģ��

    @param: none

    @return: none

    @note: 
*/
void srecorder_exit_dev(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_DEV_H */

