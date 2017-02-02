#ifndef _SRE_SYS_CALL_H
#define _SRE_SYS_CALL_H

#include "sre_typedef.h"
#include "sre_module.h"
#include "sre_errno.h"
#include "sre_syscall_def.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_syscall
 * syscall��κ���������
 *
 * ֵ: 0x02002f00
 *
 * �������:ȷ�������ȷ��
 *
 */
#define OS_ERRNO_SYSCALL_NAME_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_SYSCALL, OS_ERR_FUN_NAME)

/**
 * @ingroup SRE_syscall
 * syscall������θ�������
 *
 * ֵ: 0x02002f01
 *
 * �������:ȷ�������ȷ��
 *
 */
 
#define OS_ERRNO_SYSCALL_PARA_NUM_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_SYSCALL, OS_ERR_FUN_PARA_NUM)

#define SRE_SYSCALL(pcname,uwParaNum,...)  osSysCallInner(OS_N_##pcname, uwParaNum, __VA_ARGS__)
extern UINT64 osSysCallInner(UINT32 uwsyscallNo, UINT32 uwParaNum,...);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_BUILDEF_H */


