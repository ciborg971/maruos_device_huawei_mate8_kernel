/**
 * @file sre_symbol_api.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ���������ű�ģ��Ķ���ͷ�ļ� \n
 */

/**
 * @defgroup SRE_symbol ���ű�
 * @ingroup SRE_inspect
*/

#ifndef _SRE_SYMBOL_API_H
#define _SRE_SYMBOL_API_H

#include "sre_typedef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup  SRE_symbol
 * @brief ���ű�
 *
 * @par ����:
 * ��������ķ�����pcName����ȡ��Ӧ�ķ��ŵ�ַ��
 *
 * @attention
 * <ul>
 * <li>��Cortex-A9ƽ̨֧�ִ˹��ܡ�</li>
 * </ul>
 *
 * @param  pcName   [IN] ����#CHAR *������ķ�������
 * @param  puwAddr  [OUT] ����#UINT32 *��������ŵ�ַ��
 *
 * @retval #OS_ERRNO_SYMBOL_FIND_NAME_ERROR           0x02002904���ڷ��ű���û�в��ҵ���������ƥ��ķ��Žڵ㡣
 * @retval #OS_ERRNO_SYMBOL_GET_ADDR_PTR_NULL         0x0200290b�������ָ�����ΪNULL��
 * @retval #SRE_OK                                    0x00000000����ȡ���ŵ�ַ�ɹ���
 * @par ����:
 * <ul><li>sre_symbol.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R005C00
 * @see
 **/
extern UINT32 SRE_SymFindAddrByName(CHAR *pcName, UINT32 *puwAddr);
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_SYMBOL_API_H */

/**
 * History:
 *
 * vi: set expandtab ts=4 sw=4 tw=80:
*/

