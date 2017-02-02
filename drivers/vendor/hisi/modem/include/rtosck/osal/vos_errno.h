/**
 * @file vos_errno.h
 *
 * Copyright(C), 2012-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL������ͷ�ļ��� \n
 */

/**@defgroup vos_errno ������
 *@ingroup OSAL
*/

#ifndef _VOS_ERRNO_H
#define _VOS_ERRNO_H

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_OK                  (0)
#define VOS_ERROR               ((VOS_UINT32)(-1))

/**
 * @ingroup vos_errno
 * OSAL�����룺��������
 *
 * ֵ: 0x00000016
 *
 * �������: �û������Σ���֤��κϷ���
 */
#define VOS_ERRNO_INVAL                 0x00000016

/**
 * @ingroup vos_errno
 * OSAL�����룺�ڴ治�㡣
 *
 * ֵ: 0x0000000C
 *
 * �������: �ͷ�����δʹ�õ��ڴ�ռ���߷�������˽��FSC�ڴ������
 */
#define VOS_ERRNO_NOMEM                 0x0000000C

/**
 * @ingroup vos_errno
 * OSAL�����룺OSAL��ʼ��ʧ�ܡ�
 *
 * ֵ: 0x00000080
 *
 * �������: ���������ź��������С���ʱ��ģ���Ƿ�������ɳ�ʼ����
 */
#define VOS_ERRNO_OSAL_INIT_FAILED      0x00000080

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif /* _VOS_ERRNO_H */

