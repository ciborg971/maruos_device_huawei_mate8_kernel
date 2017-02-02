/**
 * @file sre_symbol_api.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * 描述：符号表模块的对外头文件 \n
 */

/**
 * @defgroup SRE_symbol 符号表
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
 * @brief 符号表。
 *
 * @par 描述:
 * 根据输入的符号名pcName，获取对应的符号地址。
 *
 * @attention
 * <ul>
 * <li>仅Cortex-A9平台支持此功能。</li>
 * </ul>
 *
 * @param  pcName   [IN] 类型#CHAR *，输入的符号名。
 * @param  puwAddr  [OUT] 类型#UINT32 *，保存符号地址。
 *
 * @retval #OS_ERRNO_SYMBOL_FIND_NAME_ERROR           0x02002904，在符号表中没有查找到符号名字匹配的符号节点。
 * @retval #OS_ERRNO_SYMBOL_GET_ADDR_PTR_NULL         0x0200290b，输入的指针参数为NULL。
 * @retval #SRE_OK                                    0x00000000，获取符号地址成功。
 * @par 依赖:
 * <ul><li>sre_symbol.h：该接口声明所在的头文件。</li></ul>
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

