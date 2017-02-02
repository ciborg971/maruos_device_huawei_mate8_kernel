/**
 * @file vos_timer.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL��ʱ��ͷ�ļ��� \n
 */

/**@defgroup vos_timer ��ʱ��
 *@ingroup OSAL
*/

#ifndef __VOS_TIMER_H__
#define __VOS_TIMER_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if((YES == OS_OPTION_EVENT) && (YES == OS_OPTION_QUEUE))

#define VOS_TIMER_LOOP                          1
#define VOS_TIMER_NOLOOP                        0
#define VOS_TIMER_DEL_ON_TIMEOUTMSG             4
#define VOS_TIMER_EVENT                         (1 << 15)

/**
 * @ingroup vos_timer
 * ��ʱ��״̬������̬��
 */
#define VOS_TM_IS_IDLE                          0x5A

/**
 * @ingroup vos_timer
 * ��ʱ��״̬���ȴ���ʱ̬��
 */
#define VOS_TM_IS_TICKING                       0xA5

/**
 * @ingroup vos_timer
 * ��ʱ��״̬����ʱ̬��
 */
#define VOS_TM_IS_OUT                           0xAA

/**
 * @ingroup vos_timer
 * ��ʱ��״̬����ɾ��̬��
 */
#define VOS_TM_IS_DELETED                       0x55

/**
 * @ingroup vos_timer
 * OSAL��ʱ����ʱ���������Ͷ��塣
 */
typedef VOS_VOID(*P_TIMER_FUNC)(VOS_VOID *);

/**
 * @ingroup vos_timer
 * OSAL��ʱ����ʱ��Ϣ���͡�
 */
typedef struct tagTIMERMSG
{
    VOS_UINT32      ulSourceID;             /**< ԴID */
    VOS_UINT32      ulTimerID;              /**< ��ʱ��ID */
    P_TIMER_FUNC    pfFunc;                 /**< ��ʱ�ص����� */
    VOS_VOID        *pArg;                  /**< ��ʱ�ص������Ĳ��� */
} VOS_TIMERMSG_S;

/**
 * @ingroup vos_timer
 * OSAL��ʱ��������Ϣ���͡�
 */
typedef struct tagTIMERINFO
{
    VOS_UINT32      ulTaskID;               /**< ��ʱ��������ID�����¼� */
    VOS_UINT32      ulMsgQueID;             /**< ����ID */
    VOS_UINT32      ulFlag;                 /**< ��ʱ��������VOS_TIMER_LOOP��VOS_TIMER_NOLOOP */
    VOS_UINT32      ulTimerStatus;          /**< ��ʱ����״̬ */
    VOS_UINT32      ulMillSec;              /**< ��ʱ���ĳ�ʱʱ�� */
    P_TIMER_FUNC    pfFunc;                 /**< ��ʱ���Ļص����� */
    VOS_VOID        *pArg;                  /**< ��ʱ���Ĳ��� */
} VOS_TIMERINFO_S;

/**
 * @ingroup  vos_timer
 * @brief ����������һ����ʱ����
 *
 * @par ����:
 * ����������һ����ʱ����
 *
 * @attention
 * <ul>
 * <li>�жϴ�����pfnHandler�ĵ�һ�������Ǵ����Ķ�ʱ�����߼���š�</li>
 * <li>�������ڶ�ʱģʽ�Ķ�ʱ���������û���Ҫ�Ѷ�ʱ������õĹ��ͣ�����һֱ������ʱ���Ĵ�������</li>
 * </ul>
 *
 * @param  ulTaskID [IN] ����#VOS_UINT32������ID��ȡֵ��ΧΪ��Ч������ID��
 * @param  ulMsgQueID  [IN] ����#VOS_UINT32������ID��ȡֵ��ΧΪ��Ч�Ķ���ID���ò���ΪNULLʱ����ʾʹ�õ��ǻص���ʽ�Ķ�ʱ����
 * @param  ulMillSec  [IN] ����#VOS_UINT32����ʱ��ʱ������λms��ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 * @param  pfFunc  [IN] ����#P_TIMER_FUNC����ʱ�ص�������ȡֵ��ΧΪ�ǿա�
 * @param  pArg  [IN] ����#VOS_VOID *����ʱ�ص������Ĳ�������ʱ����ʱ�󽫻���ʱ�ص������������������ȡֵ��ΧΪ�ǿա�
 * @param  pulTimerID  [OUT] ����#VOS_UINT32 *�������Ķ�ʱ��ID��ȡֵ��ΧΪ�ǿա�
 * @param  ulFlag  [IN] ����#VOS_UINT32����ʱ�����͡�ȡֵ��ΧΪ{VOS_TIMER_NOLOOP��VOS_TIMER_LOOP}������ֻ��ȡ��һ�����û���������������е��κ�һ����Ĭ�ϲ���VOS_TIMER_NOLOOP��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ʱ�������ɹ���
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Delete
 */
extern VOS_UINT32 VOS_Timer_Create(VOS_UINT32 ulTaskID, VOS_UINT32 ulMsgQueID, VOS_UINT32 ulMillSec, P_TIMER_FUNC pfFunc, VOS_VOID *pArg, VOS_UINT32 *pulTimerID, VOS_UINT32 ulFlag);

/**
 * @ingroup  vos_timer
 * @brief ֹͣ��ɾ����ʱ����
 *
 * @par ����:
 * ֹͣ��ɾ����ʱ����
 *
 * @attention
 * <ul>
 * <li>����ɾ�����ڳ�ʱ����Ķ�ʱ����</li>
 * </ul>
 *
 * @param  ulTimerID [IN] ����#VOS_UINT32����ʱ��ID��ȡֵ��ΧΪ��Ч�Ķ�ʱ��ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ʱ��ɾ���ɹ���
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Create
 */
extern VOS_UINT32 VOS_Timer_Delete(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief �޸Ķ�ʱ���Ķ�ʱʱ����
 *
 * @par ����:
 * �޸Ķ�ʱ���Ķ�ʱʱ����
 *
 * @attention
 * <ul>
 * <li>�����޸����ڳ�ʱ����Ķ�ʱ��ʱ����</li>
 * </ul>
 *
 * @param  ulTimerID [IN] ����#VOS_UINT32����ʱ��ID��ȡֵ��ΧΪ��Ч�Ķ�ʱ��ID��
 * @param  ulNewMillSec [IN] ����#VOS_UINT32���µĶ�ʱ��ʱ������λms��ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000���޸Ķ�ʱ���Ķ�ʱʱ���ɹ���
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Timer_Resize(VOS_UINT32 ulTimerID, VOS_UINT32 ulNewMillSec);

/**
 * @ingroup  vos_timer
 * @brief ��ȡ��ʱ����������Ϣ��
 *
 * @par ����:
 * ��ȡ��ʱ����������Ϣ��
 *
 * @attention ��
 *
 * @param  ulTimerID [IN] ����#VOS_UINT32����ʱ��ID��ȡֵ��ΧΪ��Ч�Ķ�ʱ��ID��
 * @param  pTimerInfo [OUT] ����#VOS_TIMERINFO_S *�����涨ʱ����Ϣ���ڴ�ָ�롣ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡ��ʱ��������Ϣ�ɹ���
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Timer_GetInfo(VOS_UINT32 ulTimerID, VOS_TIMERINFO_S *pTimerInfo);

/**
 * @ingroup  vos_timer
 * @brief ��ѯ��ʱ���Ƿ�ֹͣ��
 *
 * @par ����:
 * ��ѯ��ʱ���Ƿ�ֹͣ��
 *
 * @attention ��
 *
 * @param  ulTimerID [IN] ����#VOS_UINT32����ʱ��ID��ȡֵ��ΧΪ��Ч�Ķ�ʱ��ID��
 *
 * @retval #VOS_FALSE                           0x00000000����ʱ��ID�Ƿ�����ʱ��δֹͣ��
 * @retval #VOS_TRUE                            0x00000001����ʱ����ֹͣ��
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT16 VOS_Timer_IsStoped(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief �ж϶�ʱ���ĺϷ��ԡ�
 *
 * @par ����:
 * �ж϶�ʱ���ĺϷ��ԡ�
 *
 * @attention ��
 *
 * @param  ulTimerID [IN] ����#VOS_UINT32����ʱ��ID��ȡֵ��ΧΪ����ֵ��
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF����ʱ��ID�Ƿ���
 * @retval #VOS_OK                              0x00000000����ʱ��ID�Ϸ���
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Timer_IsValid(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief ��ͣһ����ʱ����
 *
 * @par ����:
 * ��ͣһ����ʱ����
 *
 * @attention ��
 *
 * @param  ulTimerID [IN] ����#VOS_UINT32����ʱ��ID��ȡֵ��ΧΪ��Ч�Ķ�ʱ��ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ʱ����ͣ�ɹ���
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Resume
 */
extern VOS_UINT32 VOS_Timer_Pause(VOS_UINT32 ulTimerID);

/**
 * @ingroup  vos_timer
 * @brief �ָ�һ����ʱ����
 *
 * @par ����:
 * �ָ�һ����ʱ����
 *
 * @attention ��
 *
 * @param  ulTimerID [IN] ����#VOS_UINT32����ʱ��ID��ȡֵ��ΧΪ��Ч�Ķ�ʱ��ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ʱ���ָ��ɹ���
 * @par ����:
 * <ul><li>vos_timer.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Timer_Pause
 */
extern VOS_UINT32 VOS_Timer_Resume(VOS_UINT32 ulTimerID);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */
#endif

#endif //__VOS_TIMER_H__

