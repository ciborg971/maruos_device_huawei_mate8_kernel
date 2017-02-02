

#ifndef SRECORDER_DUMP_BACKTRACE_H
#define SRECORDER_DUMP_BACKTRACE_H


/*----includes-----------------------------------------------------------------------*/

#include <asm/stacktrace.h>
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
    @function: void srecorder_dump_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        struct pt_regs *regs, struct task_struct *tsk)
    @brief: dump����ʱ�ں˵ĵ���ջ��Ϣ
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: regs cpu�ļĴ���״̬
    @param: tsk ��Ҫ��dump����ջ�Ľ���
    
    @return: none

    @note: 
*/
void srecorder_dump_backtrace(srecorder_reserved_mem_info_t *pmem_info, 
    struct pt_regs *regs, struct task_struct *tsk);


/**
    @function: int srecorder_unwind_frame(struct stackframe *frame)
    @brief: ����ջ֡����׷��
    
    @param: frame ������׷�ݵ�ջ֡
    
    @return: 0 - successfully, others - failed

    @note: 
*/
int srecorder_unwind_frame(struct stackframe *frame);


/**
    @function: int srecorder_unwind_frame(struct stackframe *frame)
    @brief: do backtrace
    
    @param: none
    
    @return: none

    @note: 
*/
asmlinkage void srecorder___backtrace(void);


/**
    @function: int srecorder_unwind_frame(struct stackframe *frame)
    @brief: do backtrace for ARM disconfig CONFIG_ARM_UNWIND 
    
    @param: fp frame pointer
    @param: pmode the mode of the processor
    
    @return: none

    @note: 
*/
asmlinkage void srecorder_c_backtrace(unsigned long fp, int pmode);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_DUMP_BACKTRACE_H */

