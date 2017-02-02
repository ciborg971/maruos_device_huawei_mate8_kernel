/**
 * @file vos_init.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSALϵͳ��������ͷ�ļ��� \n
 */

/**@defgroup vos_init OSAL��ʼ��
 *@ingroup OSAL
 */

#ifndef __VOS_INIT_H__
#define __VOS_INIT_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
#include "sre_typedef.h"
#include "vos_redef.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup  vos_init
 * @brief RTOSck OSAL��ʼ����
 *
 * @par ����:
 * RTOSck OSAL��ʼ�����û�����Ҫʹ��RTOSck OSAL�ӿ�ǰ���ñ���˽ӿڡ�
 *
 * @attention ��
 *
 * @param
 *
 * @retval #VOS_ERRNO_OSAL_INIT_FAILED          0x00000080���������񡢶��С���ʱ��ģ���Ƿ�������ɳ�ʼ����
 * @retval #VOS_ERRNO_NOMEM                     0x0000000C���ͷ�����δʹ�õ��ڴ�ռ���߷�������˽��FSC�ڴ������
 * @retval #VOS_ERROR                           0xFFFFFFFF������������м�ʱ����ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000��OSAL��ʼ���ɹ���
 * @par ����:
 * <ul><li>vos_init.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see
 */
extern UINT32 VOS_AdapterInit(VOID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_INIT_H__

