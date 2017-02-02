

#ifndef SRECORDER_SNPRINTF_H
#define SRECORDER_SNPRINTF_H


/*----includes-----------------------------------------------------------------------*/

#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

#define SRECORDER_SNPRINTF srecorder_snprintf


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/


/**
    @function: int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...)
    @brief: ��ָ����ʽ����ַ�����ָ�������С�

    @param: buf ����
    @param: size ����ռ��С
    @param: fmt �ַ�����ʽ

    @return: д�뻺����ֽ���

    @note: 
*/
int srecorder_snprintf(char *buf, size_t size, const char *fmt, ...);


/**
    @function: int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ����ʽ�����ģ��

    @param: pinit_params ģ���ʼ������

    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_snprintf(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_snprintf(void)
    @brief: �˳���ʽ�����ģ��

    @param: none

    @return: none

    @note: 
*/
void srecorder_exit_snprintf(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_SNPRINTF_H */

