/**
 * @file vos_task.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL����ͷ�ļ��� \n
 */

/**@defgroup vos_task ����
 *@ingroup OSAL
*/

#ifndef __VOS_TASK_H__
#define __VOS_TASK_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_TSK_MIN_STACK_SIZE          0x130
#define VOS_T_PRIORITY_NORMAL           64
#define VOS_TASK_DEFAULT_STACKSIZE      0x1000

typedef VOS_VOID (* TaskStartAddress_PF)
(
    VOS_UINTPTR ulArg0,                 /* ���������ĵ�һ������ */
    VOS_UINTPTR ulArg1,                 /* ���������ĵڶ������� */
    VOS_UINTPTR ulArg2,                 /* ���������ĵ��������� */
    VOS_UINTPTR ulArg3                  /* ���������ĵ��ĸ����� */
);

typedef TaskStartAddress_PF VOS_TASK_ENTRY_TYPE;

/**
 * @ingroup  vos_task
 * @brief ��������
 *
 * @par ����:
 * ����һ��������ϵͳOS��ʼ��ǰ����������ֻ�Ǽ򵥵ؼ���������С�
 * ϵͳ��ʼ���󴴽�������������ȼ����ڵ�ǰ������δ����������������������Ȳ������У��������������С�
 *
 * @attention
 * <ul>
 * <li>����������󳤶�Ϊ15�ֽڣ�������������</li>
 * <li>acTaskName��pfTaskStartAddress��aulTaskArg��pulTaskID������Ϊ�գ����򴴽�ʧ�ܡ�ulTaskPriority���ܴ���255�����򴴽�ʧ�ܡ�</li>
 * <li>��ָ��������ջ��СΪ0����ʹ��������#VOS_TASK_DEFAULT_STACKSIZEָ����Ĭ�ϵ�����ջ��С��</li>
 * <li>����ջ�Ĵ�С���밴16�ֽڴ�С���롣ȷ������ջ��С��ԭ���ǣ����þ��У������˷ѣ���������ջ������������ȡ������Ҫ���Ķ��ٵ�ջ�ڴ棬������������������ò��Խ�ջ�ڴ濪��Խ�󣬾ֲ�����Խ�󣬾ֲ�����Խ�࣬ջ�ڴ濪��ҲԽ��</li>
 * <li>���񴴽�ʱ�����񴴽������е�����ջ��С���ý��鲻Ҫʹ����С����ջ��СVOS_TSK_MIN_STACK_SIZE(��СΪ0x130)������ֻ�ǰ�������������Ԥ����ջ�ռ䣬�������ʱ�������������Ҫ���û����б�֤�㹻������ջ�ռ����á�</li>
 * <li>ÿ����������ֻ�ܶ�Ӧ��������</li>
 * </ul>
 *
 * @param  acTaskName[15] [IN] ����#VOS_CHAR����������֣����Ȳ�����15��������������'\0'����ȡֵ��ΧΪ�ǿա�
 * @param  ulTaskPriority [IN] ����#VOS_UINT32��Ҫ������������ȼ���ȡֵ��Χ��0��255����ֵԽ�����ȼ�Խ�ߡ�ȡֵ��ΧΪĬ��ֵΪVOS_T_PRIORITY_NORMAL��
 * @param  ulTaskMode [IN] ����#VOS_UINT32���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  ulTaskStackSize [IN] ����#VOS_UINT32��Ҫ�������������ջ��С����λΪ�ֽڡ�������0ʱ����ʹ��Ĭ��ֵ0x1000�ֽڡ�ȡֵ��Χ��С��VOS_TSK_MIN_STACK_SIZE�ֽڡ�
 * @param  aulTaskArg[4] [IN] ����#VOS_UINT32��Ҫ����������ں�����VOS_UINPTR���͵Ĳ������׵�ַ��ȡֵ��ΧΪ����ֵ��
 * @param  pfTaskStartAddress [IN] ����#TaskStartAddress_PF��Ҫ�����������ں�����ַ��ȡֵ��ΧΪ�ǿա�
 * @param  pulTaskID [OUT] ����#VOS_UINT32 *�������´��������ID��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_ERRNO_NOMEM                     0x0000000C���ڴ�����ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000�����񴴽��ɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Delete
 */
extern VOS_UINT32 VOS_T_Create(VOS_CHAR acTaskName[15], VOS_UINT32 ulTaskPriority, VOS_UINT32 ulTaskMode, VOS_SIZE_T ulTaskStackSize, VOS_UINTPTR aulTaskArg[4], TaskStartAddress_PF pfTaskStartAddress, VOS_UINT32 *pulTaskID);

/**
 * @ingroup  vos_task
 * @brief ɾ������
 *
 * @par ����:
 * ɾ��ָ��������
 *
 * @attention
 * <ul>
 * <li>��Ϊ��ɾ������������ƿ������ջ����һ�δ�������ʱ�Ż��ա�</li>
 * <li>����������ɾ����RTOSck�����������ص��ź����ͽ��յ�����Ϣ��ǿ��ɾ����</li>
 * <li>������ɾ��ʱ������ɾ�����Ӳ��������pend�ź���������Ȳ�����</li>
 * </ul>
 *
 * @param  ulTaskID [IN] ����#VOS_UINT32��Ҫɾ������ID��ȡֵ��ΧΪ��Ч������ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000��ɾ������ɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Create
 */
extern VOS_UINT32 VOS_T_Delete(VOS_UINT32 ulTaskID);

/**
 * @ingroup  vos_task
 * @brief ��������ȡ�
 *
 * @par ����:
 * ��������ȡ�������ȱ������ٷ��������л�ֱ������������
 *
 * @attention
 * <ul>
 * <li>�ýӿ�ֻ��������ȣ��������жϣ���������Կɱ��жϴ�ϡ�</li>
 * <li>ִ�иýӿ���������ֵ��1��������������ֵ��1����ˣ�������#VOS_TaskUnlock���ʹ�á�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #VOS_OK                              0x00000000����������ȳɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_TaskUnlock
 */
extern VOS_UINT32 VOS_TaskLock(VOS_VOID);

/**
 * @ingroup  vos_task
 * @brief ����������ȡ�
 *
 * @par ����:
 * ����������ֵ��1����Ƕ�׼�������ֻ��������ֵ��Ϊ0�������Ľ�����������ȡ�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>ִ�иýӿ���������ֵ��1��������������ֵ��1����ˣ�������#VOS_TaskLock���ʹ�á�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #VOS_OK                              0x00000000������������ȳɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_TaskUnlock
 */
extern VOS_UINT32 VOS_TaskUnlock(VOS_VOID);

/**
 * @ingroup  vos_task
 * @brief ��ǰ�����ͷ�CPU����Ȩ��
 *
 * @par ����:
 * ��ǰ�����ͷ�CPU����Ȩ��
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>���������У��������������ʱ���øýӿڣ����ͷ�CPU����Ȩʧ�ܡ�</li>
 * <li>δ���������ʱ��˳ȡͬ���ȼ������е���һ������ִ�С���û��ͬ���ľ��������򲻷���������ȣ�����ִ��ԭ����</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Delay | VOS_T_RunDelay
 */
extern VOS_VOID VOS_T_FreeCPU(VOS_VOID);

/**
 * @ingroup  vos_task
 * @brief �����ӳ١�
 *
 * @par ����:
 * �ӳٵ�ǰ���������ִ�С�������ʱ�ȴ�ָ���ĺ����������²�����ȡ�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>Ӳ�жϻ����жϴ����У���������������ʱ����ʧ�ܡ�</li>
 * <li>���������0����δ��������ȣ���˳ȡͬ���ȼ������е���һ������ִ�С���û��ͬ���ľ��������򲻷���������ȣ�����ִ��ԭ����</li>
 * </ul>
 *
 * @param  ulMillisecond [IN] ����#VOS_UINT32��Ҫ��ʱ�ĺ������������ߵ�ʱ�䡣��λ�Ǻ��루ǧ��֮һ�룩��ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 *
 * @retval ��
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_FreeCPU | VOS_T_RunDelay
 */
extern VOS_VOID VOS_T_Delay(VOS_UINT32 ulMillisecond);

/**
 * @ingroup  vos_task
 * @brief �õ�ǰ��������һ��ʱ�����ʱָ��ʱ����
 *
 * @par ����:
 * ��ǰ��������ulRunMillisecsʱ������ʱulDelayMillisecs��
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>Ӳ�жϻ����жϴ����У���������������ʱ����ʧ�ܡ�</li>
 * <li>ulDelayMillisecs���Ϊ0����δ��������ȣ���˳ȡͬ���ȼ������е���һ������ִ�С���û��ͬ���ľ��������򲻷���������ȣ�����ִ��ԭ����</li>
 * </ul>
 *
 * @param  ulRunMillisecs [IN] ����#VOS_UINT32���������еĺ���������λ�Ǻ��루ǧ��֮һ�룩��ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 * @param  ulDelayMillisecs [IN] ����#VOS_UINT32��Ҫ��ʱ�ĺ������������ߵ�ʱ�䡣��λ�Ǻ��루ǧ��֮һ�룩��ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 *
 * @retval ��
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Delay | VOS_T_FreeCPU
 */
extern VOS_VOID VOS_T_RunDelay(VOS_UINT32 ulRunMillisecs, VOS_UINT32 ulDelayMillisecs);

/**
 * @ingroup  vos_task
 * @brief ��������
 *
 * @par ����:
 * ����ָ�����������񽫴Ӿ��������б�ɾ����
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>��Ϊ��ǰ�����������������ܱ�����</li>
 * <li>IDLE�����ܱ�����</li>
 * <li>����IDֵΪ0����ʾ����IDΪ0������</li>
 * </ul>
 *
 * @param  ulTaskID [IN] ����#VOS_UINT32��Ҫ���������ID��ȡֵ��ΧΪ��Ч������ID��
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF��ִ�еײ�OS�㺯������
 * @retval #VOS_OK                              0x00000000����������ɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_T_Suspend(VOS_UINT32 ulTaskID);

/**
 * @ingroup  vos_task
 * @brief ��ѯָ��������������֡�
 *
 * @par ����:
 * ����ָ��������ID����ѯ������ID��Ӧ���������֡�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>���ܲ�ѯID���Ϸ�����������</li>
 * <li>����ѯû�д���������������ѯʧ�ܡ�</li>
 * <li>����IDֵΪ0����ʾ��ѯIDΪ0���������֡�</li>
 * </ul>
 *
 * @param  uwTaskID [IN] ����#VOS_UINT32������ID��ȡֵ��ΧΪ��Ч������ID��
 *
 * @retval #VOS_NULL_PTR                        0x00000000����ѯʧ�ܡ�
 * @retval #����ֵ                              ���Ȳ�����15���ַ����������ֵĵ�ַ��
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_T_GetName
 */
extern VOS_CHAR * VOS_GetTaskName(VOS_UINT32 ulTaskID);

/**
 * @ingroup  vos_task
 * @brief ��ѯ��������
 *
 * @par ����:
 * ��������ID������ѯ����������
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>���ܲ�ѯID���Ϸ�����������</li>
 * <li>����ѯû�д���������������ѯʧ�ܡ�</li>
 * <li>����IDֵΪ0����ʾ��ѯIDΪ0���������֡�</li>
 * </ul>
 *
 * @param  uwTaskID [IN] ����#VOS_UINT32������ID��ȡֵ��ΧΪ��Ч������ID��
 * @param  acTaskName[15] [OUT] ����#VOS_CHAR������Ϊ������15���ַ����������ĵ�ַ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF���������󣬲�ѯʧ�ܡ�
 * @retval #VOS_OK                              0x00000000����ѯ�ɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetTaskName
 */
extern VOS_UINT32 VOS_T_GetName(VOS_UINT32 ulTaskID, VOS_CHAR acTaskName[15]);

/**
 * @ingroup  vos_task
 * @brief ��ȡ��ǰ����ID��
 *
 * @par ����:
 * ��ȡ��������̬������ID��
 *
 * @attention
 * <ul>
 * <li>Ӳ�жϻ����жϴ����У�Ҳ�ɻ�ȡ��ǰ����ID�������жϴ�ϵ�����</li>
 * <li>�������л����Ӵ����е���ʱ����ȡ�������������ID��</li>
 * </ul>
 *
 * @param  pulTaskID [OUT] ����#VOS_UINT32 *����������ID��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERROR                           0xFFFFFFFF���������󣬻�ȡ����IDʧ�ܡ�
 * @retval #VOS_OK                              0x00000000����ȡ����ID�ɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetTaskName
 */
extern VOS_UINT32 VOS_T_GetSelfID(VOS_UINT32 *pulTaskID);

/**
 * @ingroup  vos_task
 * @brief �ж������Ƿ���Ч��
 *
 * @par ����:
 * ��������ID���ж������Ƿ���Ч��
 *
 * @attention
 * <ul>
 * <li>����ID�Ǵ�0��ʼ��ŵġ�</li>
 * </ul>
 *
 * @param  ulTaskId [IN] ����#VOS_UINT32������ID��ȡֵ��ΧΪΪ����ֵ��
 *
 * @retval #VOS_TRUE                            0x00000001������ID�Ϸ���
 * @retval #VOS_FALSE                           0x00000000������ID���Ϸ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see  VOS_GetTaskName
 */
extern VOS_BOOL VOS_TaskIdValidate(VOS_UINT32 ulTaskId);

/**
 * @ingroup  vos_task
 * @brief ��������
 *
 * @par ����:
 * ����һ��������ϵͳOS��ʼ��ǰ����������ֻ�Ǽ򵥵ؼ���������С�
 * ϵͳ��ʼ���󴴽�������������ȼ����ڵ�ǰ������δ����������������������Ȳ������У��������������С�
 *
 * @attention
 * <ul>
 * <li>����������󳤶�Ϊ15�ֽڣ�������������</li>
 * <li>acTaskName��pfTaskStartAddress��aulTaskArg��pulTaskID������Ϊ�գ����򴴽�ʧ�ܡ�ulTaskPriority���ܴ���255�����򴴽�ʧ�ܡ�</li>
 * <li>��ָ��������ջ��СΪ0����ʹ��������#VOS_TASK_DEFAULT_STACKSIZEָ����Ĭ�ϵ�����ջ��С��</li>
 * <li>����ջ�Ĵ�С���밴16�ֽڴ�С���롣ȷ������ջ��С��ԭ���ǣ����þ��У������˷ѣ���������ջ������������ȡ������Ҫ���Ķ��ٵ�ջ�ڴ棬������������������ò��Խ�ջ�ڴ濪��Խ�󣬾ֲ�����Խ�󣬾ֲ�����Խ�࣬ջ�ڴ濪��ҲԽ��</li>
 * <li>���񴴽�ʱ�����񴴽������е�����ջ��С���ý��鲻Ҫʹ����С����ջ��СOS_TSK_MIN_STACK_SIZE(��СΪ0x130)������ֻ�ǰ�������������Ԥ����ջ�ռ䣬�������ʱ�������������Ҫ���û����б�֤�㹻������ջ�ռ����á�</li>
 * <li>ÿ����������ֻ�ܶ�Ӧ��������</li>
 * </ul>
 *
 * @param  puchName [IN] ����#VOS_CHAR *����������֣����Ȳ�����15��������������''����ȡֵ��ΧΪ�ǿա�
 * @param  pulTaskID [OUT] ����#VOS_UINT32 *�������´��������ID��ȡֵ��ΧΪ�ǿա�
 * @param  pfnFunc [IN] ����#VOS_TASK_ENTRY_TYPE��Ҫ�����������ں�����ַ��ȡֵ��ΧΪ�ǿա�
 * @param  ulPriority [IN] ����#VOS_UINT32��Ҫ������������ȼ���ȡֵ��Χ��0��255����ֵԽ�����ȼ�Խ�ߡ�ȡֵ��ΧΪĬ��ֵΪVOS_T_PRIORITY_NORMAL��
 * @param  ulStackSize [IN] ����#VOS_UINT32��Ҫ�������������ջ��С��������0ʱ����ʹ��RTOSckϵͳDOPRA�����Ĭ��ֵ��ȡֵ��ΧΪĬ��ֵ��0x1000�ֽڡ�
 * @param  ulTaskMode [IN] ����#VOS_SIZE_T���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  aulArgs[4] [IN] ����#VOS_UINTPTR ��Ҫ����������ں�����VOS_UINPTR���͵Ĳ������׵�ַ��ȡֵ��ΧΪ����ֵ��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_ERRNO_NOMEM                     0x0000000C���ڴ�����ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000�����񴴽��ɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_DeleteTask
 */
extern VOS_UINT32 VOS_CreateTask(VOS_CHAR *puchName, VOS_UINT32 *pulTaskID, VOS_TASK_ENTRY_TYPE pfnFunc, VOS_UINT32 ulPriority, VOS_SIZE_T ulStackSize, VOS_UINTPTR aulArgs[4]);

/**
 * @ingroup  vos_task
 * @brief ɾ������
 *
 * @par ����:
 * ɾ��ָ��������
 *
 * @attention
 * <ul>
 * <li>��Ϊ��ɾ������������ƿ������ջ����һ�δ�������ʱ�Ż��ա�</li>
 * <li>����������ɾ����RTOSck�����������ص��ź����ͽ��յ�����Ϣ��ǿ��ɾ����</li>
 * <li>������ɾ��ʱ������ɾ�����Ӳ��������pend�ź���������Ȳ�����</li>
 * </ul>
 *
 * @param  ulTaskID [IN] ����#VOS_UINT32��Ҫɾ������ID��ȡֵ��ΧΪ��Ч������ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��ɾ������ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000��ɾ������ɹ���
 * @par ����:
 * <ul><li>vos_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_T_Create
 */
extern VOS_UINT32 VOS_DeleteTask(VOS_UINT32 ulTaskID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_TASK_H__

