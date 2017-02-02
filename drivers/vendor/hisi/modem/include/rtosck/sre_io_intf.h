/**
 * @file SRE_io_intf.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������IO�ӿ�ͷ�ļ��� \n
 */

/**@defgroup sre_io_intf IO��ӡ
 *@ingroup SRE_kernel
*/

#ifndef __SRE_IO_INTF_H__
#define __SRE_IO_INTF_H__

#include "sre_base.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_OPTION_IO_INTF == YES)

/**
 *@ingroup sre_io_intf
 *IO�˿ڴ�ӡ�����������
 */
#define OS_IO_INTF_END_SIGN        0

/**
* @ingroup  sre_io_intf
*
* �����û�ע���ͨ���ַ�������Ӻ������͡�
*/
typedef UINT32 (*OS_SENDCHR2CHL_HOOK_FUNC)(UINT8 ucChar);

/**
 * @ingroup sre_io_intf
 * IO�ӿڴ����룺SRE_SendChrToChlHookReg�������Ϊ�ա�
 *
 * ֵ: 0x02003431
 *
 * �������: SRE_SendChrToChlHookReg��������η�Ϊ��ָ�롣
 *
 */
#define OS_ERRNO_IO_INTF_SENDCHR2SHELL_PARA_NULL                                  SRE_ERRNO_OS_ERROR(OS_MID_IO_INTF, 0x31)

/**
 * @ingroup sre_io_intf
 * IO�ӿڴ����룺����������Ӻ���Ϊ�ա�
 *
 * ֵ: 0x02003432
 *
 * �������: ����������Ӻ����Ƿ�Ϊ�ա�
 *
 */
#define OS_ERRNO_IO_INTF_SENDCHR2CHL_HOOK_NULL                                    SRE_ERRNO_OS_ERROR(OS_MID_IO_INTF, 0x32)

/**
 * @ingroup sre_shell
 * HShell�����룺���ڷ��͵��ַ���Ϊ�ա�
 *
 * ֵ: 0x02003433
 *
 * �������: ���ڷ��͵��ַ���Ϊ��
 *
 */
#define OS_ERRNO_IO_INTF_SENDSTR_NULL                                             SRE_ERRNO_OS_ERROR(OS_MID_IO_INTF, 0x33)

/**
* @ingroup  sre_io_intf
* @brief ��IO�˿�����ַ��Ĺ���ע�ắ��
*
* @par ����:
* ע��IO�˿�����ַ�������
*
* @attention
* <ul>��</ul>
*
* @param  pfnSendChr2ChlHook  [IN] ����#OS_SENDCHR2CHL_HOOK_FUNC��ע��Ĺ��Ӻ�����
*
* @retval  #OS_ERRNO_IO_INTF_SENDCHR2SHELL_PARA_NULL 0x02003431���û�ע��Ĺ��Ӻ�������Ϊ�ա�
* @retval  #SRE_OK                                 0x00000000���ɹ���
* @par ����:
* <ul><li>sre_io_intf.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C00
* @see ��
*/
extern UINT32 SRE_SendChrToChlHookReg(OS_SENDCHR2CHL_HOOK_FUNC pfnSendChr2ChlHook);


#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif //__SRE_IO_INTF_H__

