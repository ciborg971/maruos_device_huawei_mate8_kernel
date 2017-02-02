/**
 * @file vos_queue.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������OSAL����ͷ�ļ��� \n
 */

/**@defgroup vos_queue ����
 *@ingroup OSAL
*/

#ifndef __VOS_QUEUE_H__
#define __VOS_QUEUE_H__

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)

#include "vos_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if (YES == OS_OPTION_QUEUE)

#define VOS_URGENT                  ((VOS_UINT32)1 << 28)
#define VOS_NORMAL                  ((VOS_UINT32)1 << 29)
#define VOS_QUE_NODE_SIZE           (sizeof(VOS_UINTPTR) * 4)
#define VOS_DEFAULT_QUEUE_SIZE      64
#define VOS_Q_PRIOR                 ((VOS_UINT32)1)
#define VOS_Q_FIFO                  ((VOS_UINT32)1 << 1)
#define VOS_Q_ASYN                  ((VOS_UINT32)1 << 2)
#define VOS_Q_SYN                   ((VOS_UINT32)1 << 3)

/**
 * @ingroup vos_queue
 * ���д����룺�첽������ʱ������Ϊ�ա�
 *
 * ֵ: 0x00000030
 *
 * �������: ������ʱ�豣֤����������Ϣ��
 */
#define VOS_ERRNO_QUEUE_READ_NOMSG          0x00000030

/**
 * @ingroup vos_queue
 * ���д����룺ͬ��������ʱ��������ʱ��
 *
 * ֵ: 0x00000031
 *
 * �������: ��鿴��ʱʱ�������Ƿ���ʡ�
 */
#define VOS_ERRNO_QUEUE_READ_TIMEOUT        0x00000031

/**
 * @ingroup vos_queue
 * ���д����룺�첽д����ʱ������������
 *
 * ֵ: 0x00000032
 *
 * �������: д����ǰ�豣֤Ҫ�п��еĽڵ㡣
 */
#define VOS_ERRNO_QUEUE_WRITE_MSGFULL       0x00000032

/**
 * @ingroup vos_queue
 * ���д����룺ͬ��д����ʱ��������ʱ��
 *
 * ֵ: 0x00000033
 *
 * �������: ��鿴��ʱʱ�������Ƿ���ʡ�
 */
#define VOS_ERRNO_QUEUE_WRITE_TIMEOUT       0x00000033

/**
 * @ingroup vos_queue
 * ���д����룺ͬ����д����ʱ�������Ѿ���ɾ����
 *
 * ֵ: 0x00000034
 *
 * �������: ������ȷ����Ρ�
 */
#define VOS_ERRNO_QUEUE_QUEUEDELETED        0x00000034

/**
 * @ingroup  vos_queue
 * @brief ����һ����Ϣ���С�
 *
 * @description
 * ����һ����Ϣ���У�����Ϣ��������ΪchQueName������ΪulQueDepth�������ɹ��󣬰Ѵ����õĶ���ID�������������ָ��pulQueueID�С�
 *
 * @attention
 * <ul>
 * <li>ÿ�����нڵ�Ĵ�С�ĵ�λ��BYTE��</li>
 * <li>ÿ�����нڵ�ĳ����Զ���2�ֽڶ��롣</li>
 * <li>ÿ�����нڵ�ĳ���ΪVOS_QUE_NODE_SIZE�ֽڣ���Ϣ����󳤶�ΪVOS_QUE_NODE_SIZE�ֽ�</li>
 * </ul>
 *
 * @param chQueName[4] [IN] ����Ϊ#VOS_CHAR��Ҫ�����Ķ������ƣ�����Ϊ4�ֽڡ��������ƿ���Ϊ���ַ������������������鴫�벻Ϊ���ַ������������淶��
 * @param ulQueDepth [IN] ����Ϊ#VOS_UINT32��Ҫ�������е���Ϣ���������ܹ����ɶ��ٸ���Ϣ����ȡֵΪ0����ʾʹ��ȱʡ�Ķ��г��ȣ�Ϊ64��
 * @param ulFlags [IN] ����Ϊ#VOS_UINT32����Ϣ���е�����ģʽ���ò������ԣ�ȡֵ��ΧΪ����ֵ��
 * @param pulQueueID [OUT] ����Ϊ#VOS_UINT32 *�����ڱ��洴���Ķ���ID��ָ�롣ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016��chQueName����pulQueueIDΪ�գ���������Ч�Ķ������ƻ����ID��ָ�롣
 * @retval #VOS_ERRNO_NOMEM                     0x0000000c���ڴ治�㣬�����ͷ�һ�����ڴ档
 * @retval #VOS_ERROR                           0xFFFFFFFF��û�п��еĶ�����Դ�������������ж�����Դ�����á�
 * @retval #VOS_OK                              0x00000000��������Ϣ���гɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Delete
 */
extern VOS_UINT32 VOS_Que_Create(VOS_CHAR chQueName[4], VOS_UINT32 ulQueDepth, VOS_UINT32 ulFlags, VOS_UINT32 *pulQueueID);

/**
 * @ingroup  vos_queue
 * @brief ɾ��ָ������Ϣ���С�
 *
 * @description
 * ���ݴ����ulQueueID��ɾ����Ӧ����Ϣ���С�ɾ���������Դ�����ա�
 *
 * @attention
 * <ul>
 * <li>����ɾ��δ�����Ķ��С�</li>
 * <li>ɾ��ͬ������ʱ������ȷ�������������ڸö��У����ޱ������û��ʱ�������е����񣬷���ɾ������ʧ�ܡ�</li>
 * </ul>
 *
 * @param ulQueueID [IN] ����Ϊ#VOS_UINT32��Ҫɾ���Ķ���ID��ȡֵ��ΧΪ�Ϸ��Ķ���ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���������ulQueueID�Ƿ����û���Ҫ����Լ������������
 * @retval #VOS_ERROR                           0xFFFFFFFF��ɾ������ʧ�ܣ����ܵ�ԭ��Ϊ�ͷŶ����ڴ�ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000��ɾ�����гɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Create
 */
extern VOS_UINT32 VOS_Que_Delete(VOS_UINT32 ulQueueID);

/**
 * @ingroup  vos_queue
 * @brief д��Ϣ���С�
 *
 * @description
 * ���ݴ����ulFlags��ͬ�������첽дһ����Ϣ������ulQueueID�У�����Ϣд������β������д����Ϣ��ַ��aulQueMsg������ΪVOS_QUE_NODE_SIZE��
 * ͬ��д����ʱ�������Ϣ����������д���е����񽫱����������ȴ�д��ֱ����ʱ����uiTimeOut���룩���߶�����Ϣ��������
 *
 * @attention
 * <ul>
 * <li>����ģʽ������idle����ʹ�ã����û���֤��</li>
 * <li>��osStart֮ǰ���ܵ��øýӿڣ����û���֤��</li>
 * </ul>
 *
 * @param ulQueueID [IN] ����Ϊ#VOS_UINT32��Ҫд�Ķ���ID��ȡֵ��ΧΪ�Ϸ��Ķ���ID��
 * @param aulQueMsg[4] [IN] ����Ϊ#VOS_UINTPTR����������Ϣ�ĵ�ַ��ȡֵ��ΧΪ�ǿա�
 * @param ulFlags [IN] ����Ϊ#VOS_UINT32��д���е�ģʽ��ͬ�����첽��ȡֵ��ΧΪ{VOS_WAIT|VOS_URGENT��VOS_NO_WAIT|VOS_URGENT��VOS_WAIT|VOS_NORMAL��VOS_NO_WAIT|VOS_NORMAL}��
 * @param ulTimeOut [IN] ����Ϊ#VOS_UINT32��ͬ��д����ʱ��д������ʱ�ȴ�ʱ�䡣��λΪ���롣Ϊ0��ʾ��Զ�ȴ���ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���������ulQueueID�Ƿ���aulQueMsgΪ��ָ�롣�û���Ҫ����Լ������������
 * @retval #VOS_ERRNO_QUEUE_WRITE_MSGFULL       0x00000032���첽д����ʱ������������
 * @retval #VOS_ERRNO_QUEUE_WRITE_TIMEOUT       0x00000033��ͬ��д����ʱ��������ʱ��
 * @retval #VOS_ERRNO_QUEUE_QUEUEDELETED        0x00000034��ͬ��������ʱ�������Ѿ���ɾ����
 * @retval #VOS_ERROR                           0xFFFFFFFF��д����ʧ�ܣ����ܵ�ԭ���������л�����ʱ����������д���С�
 * @retval #VOS_OK                              0x00000000��д���гɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Read
 */
extern VOS_UINT32 VOS_Que_Write(VOS_UINT32 ulQueueID, VOS_UINTPTR aulQueMsg[4], VOS_UINT32 ulFlags, VOS_UINT32 ulTimeOut);

/**
 * @ingroup  vos_queue
 * @brief ����Ϣ���С�
 *
 * @description
 * ���ݴ����ulFlags��ͬ�������첽��ȡ���� ulQueueID �е�һ����Ϣ������ȡ������Ϣ���浽��ַΪ aulQueMsg�� ��СΪVOS_QUE_NODE_SIZE�Ļ�������
 * ͬ��������ʱ���������Ϊ�գ���ȡ���е����񽫱����������ȴ���ȡֱ����ʱ����ulTimeOut���룩��������Ϣд�롣
 *
 * @attention
 * <ul>
 * <li>���ж�ȡ�Ų���FIFOģʽ���������ȳ�����ȡ����������д�������(����ڶ��нڵ����Ⱥ�˳��)��</li>
 * <li>����ģʽ������idle����ʹ�ã����û���֤��</li>
 * <li>��osStart֮ǰ���ܵ��øýӿڣ����û���֤��</li>
 * </ul>
 *
 * @param ulQueueID [IN] ����Ϊ#VOS_UINT32��Ҫ��ȡ�Ķ���ID��ȡֵ��ΧΪ�Ϸ��Ķ���ID��
 * @param aulQueMsg[4] [OUT] ����Ϊ#VOS_UINTPTR����Ŷ�ȡ��������Ϣ��Buffer������ΪVOS_QUE_NODE_SIZE����ȡ�ɹ�����Ϣ���������˻������С�ȡֵ��ΧΪ�ǿա�
 * @param ulFlags [IN] ����Ϊ#VOS_UINT32�������е�ģʽ��ͬ�����첽��ȡֵ��ΧΪ{VOS_WAIT��VOS_NO_WAIT}��
 * @param ulTimeOut [IN] ����Ϊ#VOS_UINT32��ͬ��������ʱ������������ʱ�ȴ�ʱ�䣬�Ժ���Ϊ��λ��Ϊ0��ʾ��Զ�ȴ���ȡֵ��ΧΪ��������0xFFFFFFFF/ÿ����������Tick������
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���������ulQueueID�Ƿ���aulQueMsgΪ��ָ�롣�û���Ҫ����Լ������������
 * @retval #VOS_ERRNO_QUEUE_READ_NOMSG          0x00000030���첽������ʱ������Ϊ�ա�
 * @retval #VOS_ERRNO_QUEUE_READ_TIMEOUT        0x00000031��ͬ��������ʱ��������ʱ��
 * @retval #VOS_ERRNO_QUEUE_QUEUEDELETED        0x00000034��ͬ��������ʱ�������Ѿ���ɾ����
 * @retval #VOS_ERROR                           0xFFFFFFFF��������ʧ�ܣ����ܵ�ԭ���������л�����ʱ���������ж����С�
 * @retval #VOS_OK                              0x00000000�������гɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Write
 */
extern VOS_UINT32 VOS_Que_Read(VOS_UINT32 ulQueueID, VOS_UINTPTR aulQueMsg[4], VOS_UINT32 ulFlags, VOS_UINT32 ulTimeOut);

/**
 * @ingroup  vos_queue
 * @brief ��ȡһ����Ϣ�����е���Ϣ��Ŀ��
 *
 * @description
 * ��ȡ����ulQueueID����Ϣ��Ŀ���洢��pulMsgNum�С�
 *
 * @attention ��
 *
 * @param ulQueueID [IN] ����Ϊ#VOS_UINT32��Ҫ��ȡ��Ϣ��Ŀ�Ķ���ID��ȡֵ��ΧΪ�Ϸ��Ķ���ID��
 * @param pulMsgNum [OUT] ����Ϊ#VOS_UINT32 *���洢��ȡ������Ϣ��Ŀ��ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���������ulQueueID�Ƿ���pulMsgNumΪ��ָ�롣�û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡ����ulQueueID����Ϣ��Ŀ�ɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Que_GetMsgNum(VOS_UINT32 ulQueueID, VOS_UINT32 *pulMsgNum);

/**
 * @ingroup  vos_queue
 * @brief ��ȡһ����Ϣ�����������Ϣ������
 *
 * @description
 * ��ȡָ������ulQueueID�������Ϣ���������ö����ܹ����ɵ�������Ϣ��������ȡ�ɹ���������Ϣ���������������ָ��pulMaxNum�С�
 *
 * @attention ��
 *
 * @param ulQueueID [IN] ����Ϊ#VOS_UINT32��Ҫ��ȡ��Ϣ��Ŀ�Ķ���ID��ȡֵ��ΧΪ�Ϸ��Ķ���ID��
 * @param pulMaxNum [OUT] ����Ϊ#VOS_UINT32 *�������ȡ������Ϣ���е������Ϣ������ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���������ulQueueID�Ƿ����������pulMaxNum�ǿ�ָ�롣�û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡ��Ϣ�����������Ϣ�����ɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Que_GetMaxNum(VOS_UINT32 ulQueueID, VOS_UINT32 *pulMaxNum);

/**
 * @ingroup  vos_queue
 * @brief ��ȡ���е����֡�
 *
 * @description
 *
 * ��ȡulQueueID��Ӧ���е����֣��洢��chQueName��
 *
 * @attention ��
 *
 * @param ulQueueID [IN] ����Ϊ#VOS_UINT32��Ҫ��ȡ���ֵ���Ϣ����ID��ȡֵ��ΧΪ�Ϸ��Ķ���ID��
 * @param chQueName[4] [OUT] ����Ϊ#VOS_CHAR�����ڴ洢��ȡ���Ķ��е����֣�����Ϊ4�ֽڡ�ȡֵ��ΧΪ�ǿա�
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���������ֻ�ȡʧ�ܣ��������ulQueueID�Ƿ����������chQueName�ǿ�ָ�롣�û���Ҫ����Լ������������
 * @retval #VOS_OK                              0x00000000����ȡ�������ɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern VOS_UINT32 VOS_Que_GetName(VOS_UINT32 ulQueueID, VOS_CHAR chQueName[4]);

/**
 * @ingroup  vos_queue
 * @brief ɾ��ָ������Ϣ���С�
 *
 * @description
 * ���ݴ����ulQueueID��ɾ����Ӧ����Ϣ���С�ɾ���������Դ�����ա�
 *
 * @attention
 * <ul>
 * <li>����ɾ��δ�����Ķ��С�</li>
 * <li>ɾ��ͬ������ʱ������ȷ�������������ڸö��У����ޱ������û��ʱ�������е����񣬷���ɾ������ʧ�ܡ�</li>
 * </ul>
 *
 * @param ulQueueID [IN] ����Ϊ#VOS_UINT32��Ҫɾ���Ķ���ID��ȡֵ��ΧΪ�Ϸ��Ķ���ID��
 *
 * @retval #VOS_ERRNO_INVAL                     0x00000016���������ulQueueID�Ƿ����û���Ҫ����Լ������������
 * @retval #VOS_ERROR                           0xFFFFFFFF��ɾ������ʧ�ܣ����ܵ�ԭ��Ϊ�ͷŶ����ڴ�ʧ�ܡ�
 * @retval #VOS_OK                              0x00000000��ɾ�����гɹ���
 * @par ����:
 * <ul><li>vos_queue.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see VOS_Que_Create
 */
extern VOS_UINT32 VOS_QueueDelete(VOS_UINT32 ulQueueID);

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif

#endif //__VOS_QUEUE_H__

