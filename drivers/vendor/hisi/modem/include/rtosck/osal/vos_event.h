/**
 * @file vos_event.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL�¼�ͷ�ļ��� \n
 */

/**@defgroup vos_event �¼�
 *@ingroup OSAL
*/

#ifndef __VOS_EVENT_H__
#define __VOS_EVENT_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (YES == OS_OPTION_EVENT)

/**
 * @ingroup vos_event
 * �¼���ȡģʽ����ʾ��������ulEvents�е��κ�һ���¼���
 */
#define VOS_EV_ANY                          ((VOS_UINT32)1 << 26)

/**
 * @ingroup vos_event
 * �¼���ȡģʽ����ʾ��������ulEvents�е������¼���
 */
#define VOS_EV_ALL                          ((VOS_UINT32)1 << 27)

/**
 * @ingroup vos_event
 * �¼������룺��ȡ�¼���ʱ��
 *
 * ֵ: 0x00000040
 *
 * �������: �����¼���ȡ�ȴ�ʱ�䣬�����������������д�¼�������
 */
#define VOS_ERRNO_EVENT_TIMEOUT             0x00000040

/**
 * @ingroup vos_event
 * �¼������룺�¼���ȡʧ�ܣ������¼�û�з�����
 *
 * ֵ: 0x00000041
 *
 * �������: ��ʹ�õȴ���ȡ�¼���
 */
#define VOS_ERRNO_EVENT_READ_UNAVAI         0x00000041

/**
 * @ingroup  vos_event
 * @brief ���¼���
 *
 * @par ����:
 * ��ȡ��ǰ�����ָ������ΪulEvents���¼�������һ���Զ�ȡ����¼����¼���ȡ�ɹ��󣬱���ȡ���¼����������
 *
 * @attention
 * <ul>
 * <li>��ȡģʽ����ѡ���ȡ�����¼��Ͷ�ȡ�����¼���</li>
 * <li>�ȴ�ģʽ����ѡ��ȴ��Ͳ��ȴ����ɵȴ�ָ��ʱ�䡢���õȴ���</li>
 * <li>����ȡ�¼�û�з�����Ϊ�ȴ�ģʽʱ���ᷢ��������ȣ�������״̬���⡣</li>
 * <li>������IDLE�����ж��¼�����Ҫ�û����б�֤��</li>
 * <li>������ϵͳ��ʼ��֮ǰ���ö��¼��ӿڡ�</li>
 * </ul>
 *
 * @param  ulEvents [IN] ����#VOS_UINT32��Ҫ��ȡ���¼����˴����¼��ǰ�λ�洢�ģ�ÿһλ����һ���¼���ȡֵ��ΧΪ���㡣
 * @param  pulEvents [OUT] ����#VOS_UINT32 *�����ڱ�����յ����¼���ָ�롣ȡֵ��ΧΪ�ǿգ����Ϊ�ջᱨ��
 * @param  ulFlags [IN] ����#VOS_UINT32����ȡ�¼�����ȡ�Ĳ���,Ϊ��VOS_EV_ALL��VOS_EV_ANY����һ���ͣ�VOS_WAIT��VOS_NO_WAIT���е�һ����ʶ��Ľ����
 * @param  ulTimerOut [IN] ����Ϊ#VOS_UINT32���ȴ���ʱʱ�䣬��λΪ���롣0��ʾ��Զ�ȴ���ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_ERRNO_EVENT_TIMEOUT             0x00000040�����¼���ʱ���û������¼���ȡ�ȴ�ʱ�䣬���û������������и�������д�¼�������
 * @retval #VOS_ERRNO_EVENT_READ_UNAVAI         0x00000041�������¼�û�з������û���ʹ�õȴ���ȡ�¼���
 * @retval #VOS_ERROR                           0xFFFFFFFF�����¼����û�����Ƿ��������ж��¼������������ʱ���¼���
 * @retval #VOS_OK                              0x00000000�����¼��ɹ���
 * @par ����:
 * <ul><li>vos_event.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Ev_Write
 */
extern VOS_UINT32 VOS_Ev_Read(VOS_UINT32 ulEvents, VOS_UINT32 *pulEvents, VOS_UINT32 ulFlags, VOS_UINT32 ulTimerOut);

/**
 * @ingroup  vos_event
 * @brief д�¼���
 *
 * @par ����:
 * д����IDΪuwTaskID��ָ���¼�������һ����д����¼����������ж��е��á�
 *
 * @attention
 * <ul>
 * <li>��ָ���������ڵȴ���ȡд����¼�����ἤ��ָ�����񣬲�����������ȡ�</li>
 * <li>������IDLE����д�¼�����Ҫ�û����б�֤��</li>
 * </ul>
 *
 * @param  ulTaskID [IN] ����#VOS_UINT32������ID����ʾҪ�Ը�ָ���������д�¼�������ȡֵ��ΧΪ��Ч������ID��
 * @param  ulEvents [IN] ����#VOS_UINT32��д����¼��ţ�ÿһλ����һ���¼���ȡֵ��ΧΪ���㡣
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000��д�¼��ɹ���
 * @par ����:
 * <ul><li>vos_event.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Ev_Read
 */
extern VOS_UINT32 VOS_Ev_Write(VOS_UINT32 ulTaskID, VOS_UINT32 ulEvents);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif
#endif //__VOS_EVENT_H__

