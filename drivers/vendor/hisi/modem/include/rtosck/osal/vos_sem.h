/**
 * @file vos_sem.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL�ź���ͷ�ļ��� \n
 */

/**@defgroup vos_sem �ź���
 *@ingroup OSAL
*/

#ifndef __VOS_SEM_H__
#define __VOS_SEM_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#define VOS_SM_NAME_LENGTH                      16
#define VOS_SEMA4_FIFO                          0x00000001
#define VOS_SEMA4_PRIOR                         0x00000002
#define VOS_SEMA4_DELETE_SAFE                   0x00000004
#define VOS_SEMA4_INVERSION_SAFE                0x00000008
#define VOS_SM_PRIOR                            ((VOS_UINT32)1)

/**
 * @ingroup  vos_sem
 * @brief ����һ�������ź�����
 *
 * @par ����:
 * ����һ�������ź�����
 *
 * @attention
 * <ul><li>�����Ƿ�ɹ����ܵ�"���֧���ź���"����������ơ�</li></ul>
 *
 * @param  acSmName[VOS_SM_NAME_LENGTH] [IN] ����#VOS_CHAR���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  ulFlags [IN] ����#VOS_UINT32�������ź������͡������ź����ĵ��ȷ�ʽֻ֧�����ȼ���ȡֵֻ��ΪVOS_SEMA4_PRIOR���������ͻᱨ��
 * @param  pulSmID [OUT] ����#VOS_UINT32 *�����滥���ź���ID��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000�������ź��������ɹ���
 * @par ����:
 * <ul><li>vos_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmB_Create | VOS_SmCCreate | VOS_SmDelete
 */
extern VOS_UINT32 VOS_SmMCreate(VOS_CHAR acSmName[VOS_SM_NAME_LENGTH], VOS_UINT32 ulFlags, VOS_UINT32 *pulSmID);

/**
 * @ingroup  vos_sem
 * @brief ����һ���������ź�����
 *
 * @par ����:
 * ����һ���������ź�����
 *
 * @attention
 * <ul><li>�����Ƿ�ɹ����ܵ�"���֧���ź���"����������ơ�</li></ul>
 *
 * @param  acSmName[4] [IN] ����#VOS_CHAR���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  ulSmInit [IN] ����#VOS_UINT32���������ź����ĳ�ֵ���������ź��������Ա���һ�Σ���P����ֻ����һ�Ρ���ʼֵΪ0��ʾ�ź�����ʼʱ���ܱ�����Ϊ1��ʾ������һ�Ρ�ȡֵ��ΧΪ{0��1}�����û���������������е��κ�һ���ᱨ��
 * @param  ulFlags [IN] ����#VOS_UINT32���������ź������͡�ȡֵ��ΧΪ{VOS_SM_FIFO��VOS_SM_PRIOR}�����û���������������е��κ�һ���ᱨ��
 * @param  pulSmID [OUT] ����#VOS_UINT32 *������������ź���ID��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000���������ź��������ɹ���
 * @par ����:
 * <ul><li>vos_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmMCreate | VOS_SmCCreate | VOS_SmDelete
 */
extern VOS_UINT32 VOS_SmB_Create(VOS_CHAR acSmName[4], VOS_UINT32 ulSmInit, VOS_UINT32 ulFlags, VOS_UINT32 *pulSmID);

/**
 * @ingroup  vos_sem
 * @brief ����һ���������ź�����
 *
 * @par ����:
 * ����һ���������ź�����
 *
 * @attention
 * <ul><li>�����Ƿ�ɹ����ܵ�"���֧���ź���"����������ơ�</li></ul>
 *
 * @param  acSmName[VOS_SM_NAME_LENGTH] [IN] ����#VOS_CHAR���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param  ulSmInit [IN] ����#VOS_UINT32���������ź����ĳ�ֵ��ȡֵ��ΧΪ0��0xFFFFFFFE��
 * @param  ulFlags [IN] ����#VOS_UINT32���������ź������͡��ȴ��ü������ź���������ĵ��ȷ�ʽ��VOS_SEMA4_FIFO��VOS_SEMA4_PRIOR������ֻ��ȡ��һ�����û���������������е��κ�һ����Ĭ�ϲ���VOS_SEMA4_FIFO����ȡֵ��ΧΪ:{VOS_SEMA4_FIFO��VOS_SEMA4_PRIOR}��
 * @param  pulSmID [OUT] ����#VOS_UINT32 *������������ź���ID��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000���������ź��������ɹ���
 * @par ����:
 * <ul><li>vos_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmMCreate | VOS_SmB_Create | VOS_SmDelete
 */
extern VOS_UINT32 VOS_SmCCreate(VOS_CHAR acSmName[VOS_SM_NAME_LENGTH], VOS_UINT32 ulSmInit, VOS_UINT32 ulFlags, VOS_UINT32 *pulSmID);

/**
 * @ingroup  vos_sem
 * @brief ɾ��һ���ź�����
 *
 * @par ����:
 * ɾ���û�������ź������ָ�����ź�������������������ڸ��ź�������ɾ��ʧ�ܡ�
 *
 * @attention ��
 *
 * @param ulSmID [IN] ����Ϊ#VOS_UINT32���ź���ID��ȡֵ��ΧΪ��Ч���ź���ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000���ź���ɾ���ɹ���
 * @par ����:
 * <ul><li>vos_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmMCreate | VOS_SmB_Create | VOS_SmCCreate
 */
extern VOS_UINT32 VOS_SmDelete(VOS_UINT32 ulSmID);

/**
 * @ingroup  vos_sem
 * @brief �ȴ�һ���ź�����
 *
 * @par ����:
 * �ȴ��û�����ָ�����ź��������������ֵ����0����ֱ�Ӽ�1���سɹ�����������������
 * �ȴ������̷߳������ź����������õȴ���ʱʱ�䡣
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>�ȴ�ʱ�����ѡ����ȴ����ȴ��ض�ʱ�䡢���õȴ���</li>
 * <li>�ýӿ�ֻ�ܱ�������á�</li>
 * <li>������������£��û�ҪPEND�ź�����Ҫ��֤��ǰ�п����ź�����Դ��</li>
 * </ul>
 *
 * @param ulSmID [IN] ����Ϊ#VOS_UINT32���ź���ID��ȡֵ��ΧΪ��Ч���ź���ID��
 * @param ulTimeOutInMillSec [IN] ����Ϊ#VOS_UINT32��ͬ����ʱ�ȴ�ʱ�䣬��λΪ���롣0��ʾ��Զ�ȴ���ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������

 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����ź���ID�Ƿ�Ϸ���
 * @retval #VOS_ERROR                           0xFFFFFFFF���ȴ��ź������������û�����Ƿ������������:1.���������л����������ʱ�ȴ��ź�����2.�ȴ��ź�����ʱ��
 * @retval #VOS_OK                              0x00000000���ȴ��ź����ɹ���
 * @par ����:
 * <ul><li>vos_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmV
 */
extern VOS_UINT32 VOS_SmP(VOS_UINT32 ulSmID, VOS_UINT32 ulTimeOutInMillSec);

/**
 * @ingroup  vos_sem
 * @brief �첽�ȴ��ź�����
 *
 * @par ����:
 * �첽�ȴ��ź���������ź����ļ���ֵ��Ϊ0������ʹ���ź����ļ�����ֵ��1������ź����ļ���ֵΪ0���򷵻�ʧ�ܣ�������������
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>�ýӿ�ֻ�ܱ�������á�</li>
 * </ul>
 *
 * @param ulSmID [IN] ����Ϊ#VOS_UINT32���ź���ID��ȡֵ��ΧΪ��Ч���ź���ID��

 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����ź���ID�Ƿ�Ϸ���
 * @retval #VOS_ERROR                           0xFFFFFFFF���첽�ȴ��ź���ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000���첽�ȴ��ź����ɹ���
 * @par ����:
 * <ul><li>vos_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmV
 */
extern VOS_UINT32 VOS_Sm_AsyP(VOS_UINT32 ulSmID);

/**
 * @ingroup  vos_sem
 * @brief ����ָ�����ź�����
 *
 * @par ����:
 * ����ָ�����ź�������û������ȴ����ź�������ֱ�ӽ���������1���ء�
 * ������ݻ��ѷ�ʽ������Ӧ����������FIFO��ʽ���������������������ȼ���ʽ���������ڴ��ź�����������ȼ�����
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>��δ�����������£�������ѵ��������ȼ����ڵ�ǰ����������̷��������л���</li>
 * <li>���������л�ʱ�����֧�����ȼ����ѷ�ʽ���Ҵ����ź���ʱָ�����ѷ�ʽΪ���ȼ������������ڸ��ź����ϵ�������ȼ�����</li>
 * </ul>
 *
 * @param ulSmID [IN] ����Ϊ#VOS_UINT32���ź���ID��ȡֵ��ΧΪ��Ч���ź���ID��

 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016�����������û���Ҫ����ź���ID�Ƿ�Ϸ���
 * @retval #VOS_ERROR                           0xFFFFFFFF�������ź������������û�����Ƿ������������:1.�ź����Ӳ����������2.�ж����ͷŻ������ź�����3.�ǻ����ź����ĳ��������ͷŴ˻����ź�����
 * @retval #VOS_OK                              0x00000000�������ź����ɹ���
 * @par ����:
 * <ul><li>vos_sem.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_SmP
 */
extern VOS_UINT32 VOS_SmV(VOS_UINT32 ulSmID);

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_SEM_H__

