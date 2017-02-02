/**
 * @file sre_stkmon.h
 *
 * Copyright(C), 2012-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������ջԽ��ģ��Ķ���ͷ�ļ��� \n
 */

/**@defgroup SRE_stkmon ջԽ����
  *@ingroup SRE_inspect
 */

#ifndef _SRE_STKMON_H
#define _SRE_STKMON_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//KOS��֧������ջ��ع���   
#if (OS_OPTION_STACK_MON == YES)

/**
 * @ingroup SRE_stkmon
 * ջԽ���������: �쳣ģ���ջԽ����ģ��δ�����������趨�쳣ջ�ռ������С��
 *
 * ֵ��0x02002a00
 *
 * ���������ջԽ���������쳣ģ�飬�����Ƿ�ͬʱ���쳣ģ���ջԽ����ģ�鿪���Լ��쳣ջ�ռ��С��
 */
#define OS_ERRNO_STKMON_INIT_FAIL                       SRE_ERRNO_OS_ERROR(OS_MID_STKMON, 0x00)

/**
 * @ingroup SRE_stkmon
 * ջԽ���������: ��ռ0�����ݶϵ�ʧ�ܡ�
 *
 * ֵ��0x02002a02
 *
 * ���������������ݶϵ�0�Ƿ���ʹ�á�
 */
#define OS_ERRNO_STKMON_GETWP_FAIL                      SRE_ERRNO_OS_ERROR(OS_MID_STKMON, 0x02)

/**
 * @ingroup SRE_stkmon
 * ջԽ���������: �ͷ����ݶϵ�0ʧ�ܡ�
 *
 * ֵ��0x02002a03
 *
 * ����������������ݶϵ�0�Ƿ񱻶�ռ��
 */
#define OS_ERRNO_STKMON_FREEWP_FAIL                     SRE_ERRNO_OS_ERROR(OS_MID_STKMON, 0x03)

/**
 * @ingroup SRE_stkmon
 * ջԽ���������: ����ջԽ�硣
 *
 * ֵ: 0x03002a04
 *
 * �������: ��������ʱ��������ջ���߼���Ƿ�����ڴ���������
 *
 */
#define OS_ERRNO_STKMON_OVER_FLOW                       SRE_ERRNO_OS_FATAL(OS_MID_STKMON, 0x04)

/**
 * @ingroup  SRE_stkmon
 * @brief ȥʹ��ջԽ���⡣
 *
 * @par ����:
 * ȥʹ��ջԽ���⹦�ܡ�
 *
 * @attention �ޡ�
 *
 * @param �ޡ�
 *
 * @retval  #OS_ERRNO_STKMON_INIT_FAIL   0x02002a00���쳣ģ���ջԽ����ģ��δ�����������趨�쳣ջ�ռ������С��
 * @retval  #OS_ERRNO_HOOK_NOT_EXISTED   0x02001605��ջԽ����������л����Ӳ����ڡ�
 * @retval  #OS_ERRNO_STKMON_FREEWP_FAIL 0x02002a03���ͷŶ�ռ���ݶϵ�ʧ�ܡ�
 * @retval  #SRE_OK                      0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_stkmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_StkMonRestore
 */
extern UINT32 SRE_StkMonDisable(VOID);

/**
 * @ingroup  SRE_stkmon
 * @brief �ָ�ջԽ����״̬��
 *
 * @par ����:
 * �ָ�ջԽ���鹦�ܡ�
 *
 * @attention �ޡ�
 *
 * @param �ޡ�
 *
 * @retval  #OS_ERRNO_STKMON_INIT_FAIL   0x02002a00���쳣ģ���ջԽ����ģ��δ�����������趨�쳣ջ�ռ������С��
 * @retval  #OS_ERRNO_HOOK_EXISTED       0x02001603��ջԽ����������л������Ѵ��ڡ�
 * @retval  #OS_ERRNO_HOOK_FULL          0x02001604��HOOK���������ø���Ϊ0��
 * @retval  #OS_ERRNO_STKMON_GETWP_FAIL  0x02002a02����ռ���ݶϵ�0ʧ�ܡ�
 * @retval  #SRE_OK                      0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_stkmon.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_StkMonDisable
 */
extern UINT32 SRE_StkMonRestore(VOID);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_STKMON_H */


