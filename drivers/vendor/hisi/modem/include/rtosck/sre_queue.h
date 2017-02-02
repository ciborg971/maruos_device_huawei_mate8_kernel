/**
 * @file sre_queue.h
 *
 * Copyright(C), 2011-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ����������ģ��Ķ���ͷ�ļ��� \n
 */

/**@defgroup SRE_queue ����
  *@ingroup SRE_comm
  */

#ifndef _SRE_QUEUE_H
#define _SRE_QUEUE_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//֧�ֹ��ܺ�ü�,sre_buildef.h�ļ���֧�ֵĹ��ܺ�
#if (OS_OPTION_QUEUE == YES) 
/**
 * @ingroup SRE_queue
 * ���д����룺���������Դ�����ó�0��
 *
 * ֵ: 0x02002701
 *
 * �������: ���������Դ�����ô���0��������ö���ģ�飬�������òü�����ΪNO��
 */
#define OS_ERRNO_QUEUE_MAXNUM_ZERO                     SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x01)

/**
 * @ingroup SRE_queue
 * ���д����룺��ʼ�������ڴ治�㡣
 *
 * ֵ: 0x02002702
 *
 * �������: ���������ڴ������
 */
#define OS_ERRNO_QUEUE_NO_MEMORY                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x02)

/**
 * @ingroup SRE_queue
 * ���д����룺���д���ʱ�ڴ治�㡣
 *
 * ֵ: 0x02002703
 *
 * �������: ���Խ��ڴ�ռ���󡣻򽫴������еĽڵ㳤�Ⱥͽڵ�������١�
 */
#define OS_ERRNO_QUEUE_CREATE_NO_MEMORY                SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x03)

/**
 * @ingroup SRE_queue
 * ���д����룺û�п��еĶ�����Դ���Ѿ��ﵽ���õ�����������
 *
 * ֵ: 0x02002704
 *
 * �������: �����������ж�����Դ�����á�
 */
#define OS_ERRNO_QUEUE_CB_UNAVAILABLE                  SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x04)

/**
 * @ingroup SRE_queue
 * ���д����룺�����л�����ʱ����ֹ���������ڶ��С�
 *
 * ֵ: 0x02002705
 *
 * �������: ʹ��ǰ�������Ƚ�����
 */
#define OS_ERRNO_QUEUE_PEND_IN_LOCK                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x05)

/**
 * @ingroup SRE_queue
 * ���д����룺���еȴ���ʱ��
 *
 * ֵ: 0x02002706
 *
 * �������: ��鿴��ʱʱ�������Ƿ���ʡ�
 */
#define OS_ERRNO_QUEUE_TIMEOUT                         SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x06)

/**
 * @ingroup SRE_queue
 * ���д����룺����ɾ�������������Ķ��С�
 *
 * ֵ: 0x02002707
 *
 * �������: ����������������Դ���������ڴ˶����ϡ�
 */
#define OS_ERRNO_QUEUE_IN_TSKUSE                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x07)

/**
 * @ingroup SRE_queue
 * ���д����룺�г�ʱ�����д���в������ж���ʹ�á�
 *
 * ֵ: 0x02002708
 *
 * �������: ͬ�����г�ʱʱ������Ϊ�޵ȴ�����ʹ���첽���С�
 */
#define OS_ERRNO_QUEUE_IN_INTERRUPT                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x08)

/**
 * @ingroup SRE_queue
 * ���д����룺����δ������
 *
 * ֵ: 0x02002709
 *
 * �������: ������ȷ����Ρ�
 */
#define OS_ERRNO_QUEUE_NOT_CREATE                      SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x09)

/**
 * @ingroup SRE_queue
 * ���д����룺�����������ϵĶ��б������û�еõ����ȣ�����ɾ��
 *
 * ֵ: 0x0200270a
 *
 * �������: �ȴ����񱻵��Ⱥ󣬾Ϳ���ɾ����
 */
#define OS_ERRNO_QUEUE_BUSY                            SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0a)

/**
 * @ingroup SRE_queue
 * ���д����룺���д���ʱ�����ָ��Ϊ�ա�
 *
 * ֵ: 0x0200270b
 *
 * �������: �鿴���д���ʱ�����ָ���Ƿ�Ϊ�ա�
 */
#define OS_ERRNO_QUEUE_CREAT_PTR_NULL                  SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0b)

/**
 * @ingroup SRE_queue
 * ���д����룺���д���ʱ��ζ��г��Ȼ��߶�����Ϣ����СΪ0��
 *
 * ֵ: 0x0200270c
 *
 * �������: ������ȷ����Ρ�
 */
#define OS_ERRNO_QUEUE_PARA_ZERO                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0c)

/**
 * @ingroup SRE_queue
 * ���д����룺���о���Ƿ�������򳬳����о����Χ��
 *
 * ֵ: 0x0200270d
 *
 * �������: �鿴����Ķ��о��ֵ�Ƿ���Ч��
 */
#define OS_ERRNO_QUEUE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0d)

/**
 * @ingroup SRE_queue
 * ���д����룺ָ��Ϊ�ա�
 *
 * ֵ: 0x0200270e
 *
 * �������: �鿴�����ָ���Ƿ�����Ϊ�ա�
 */
#define OS_ERRNO_QUEUE_PTR_NULL                        SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0e)

/**
 * @ingroup SRE_queue
 * ���д����룺��д����ʱbuffer����Ϊ0��
 *
 * ֵ: 0x0200270f
 *
 * �������: ������ȷ����Ρ�
 */
#define OS_ERRNO_QUEUE_SIZE_ZERO                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x0f)

/**
 * @ingroup SRE_queue
 * ���д����룺д����ʱ������buffer�Ĵ�С���ڶ��н���С��
 *
 * ֵ: 0x02002710
 *
 * �������: ����buffer�Ĵ�С������ʹ�ø������С�Ķ��С�
 */
#define OS_ERRNO_QUEUE_SIZE_TOO_BIG                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x10)

/**
 * @ingroup SRE_queue
 * ���д����룺��д����ʱ��û����Դ��
 *
 * ֵ: 0x02002711
 *
 * �������: д����ǰ�豣֤Ҫ�п��еĽڵ㣬������ʱ�豣֤����������Ϣ��
 */
#define OS_ERRNO_QUEUE_NO_SOURCE                       SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x11)

/**
 * @ingroup SRE_queue
 * ���д����룺�������ȼ���������
 *
 * ֵ: 0x02002712
 *
 * �������: �������������ֻ����0��1
 */
#define OS_ERRNO_QUEUE_PRIO_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x12)

/**
 * @ingroup SRE_queue
 * ���д����룺�ڵ㳤�ȳ������ֵ
 *
 * ֵ: 0x02002713
 *
 * �������: ���нڵ㳤�Ȳ��ܴ���0XFFFA
 */
#define OS_ERRNO_QUEUE_NSIZE_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_QUEUE, 0x13)


/**
 * @ingroup SRE_queue
 * �������ȼ�����
 */
typedef enum
{
    OS_QUEUE_NORMAL = 0,      /**< ��ͨ��Ϣ����*/
    OS_QUEUE_URGENT,          /**< ������Ϣ����*/
    OS_QUEUE_BUTT
}OS_QUEUE_PRIO_E;

/**
 * @ingroup SRE_queue
 * ���еȴ�ʱ���趨����ʾ���õȴ���
 */
#define OS_QUEUE_WAIT_FOREVER     0xFFFFFFFF

/**
 * @ingroup SRE_queue
 * ���еȴ�ʱ���趨����ʾ���ȴ���
 */
#define OS_QUEUE_NO_WAIT          0

/**
 * @ingroup SRE_queue
 * ����PID��
 */
#define OS_QUEUE_PID_ALL          0xFFFFFFFF

/**
 * @ingroup SRE_queue
 * @brief �������С�
 *
 * @par ����:
 * ����һ�����У�����ʱ�����趨���г��ȺͶ��н���С��
 * @attention
 * <ul>
 * <li>ÿ�����нڵ�Ĵ�С�ĵ�λ��BYTE��</li>
 * <li>ÿ�����нڵ�ĳ����Զ���2�ֽڶ��롣</li>
 * <li>ÿ�����нڵ�ĳ��Ȳ��ܴ���0xFFFA��</li>
 * </ul>
 * @param usNodeNum      [IN] ����Ϊ#UINT16    �����нڵ����������Ϊ0��
 * @param usMaxNodeSize  [IN] ����Ϊ#UINT16    ��ÿ�����н��Ĵ�С��
 * @param puwQueueID     [OUT] ����Ϊ#UINT32 * ���洢����ID��ID��1��ʼ��
 *
 * @retval #SRE_OK                           0x00000000�������ɹ���
 * @retval #OS_ERRNO_QUEUE_CREAT_PTR_NULL    0x0200270b�����д���ʱ�����ָ��Ϊ�ա�
 * @retval #OS_ERRNO_QUEUE_PARA_ZERO         0x0200270c����ζ��г��Ȼ��߶�����Ϣ����СΪ0��
 * @retval #OS_ERRNO_QUEUE_CB_UNAVAILABLE    0x02002704��û�п��еĶ�����Դ�����Ѿ��ﵽ���õ�����������
 * @retval #OS_ERRNO_QUEUE_CREATE_NO_MEMORY  0x02002703�����д���ʱ�ڴ治�㡣
 * @retval #OS_ERRNO_QUEUE_NSIZE_INVALID     0x02002713,�ڵ㳤�ȳ������ֵ��
 * @par ����:
 * @li SRE_queue.h���ýӿ��������ڵ�ͷ�ļ���
 * @since RTOSck V100R001C00
 * @see SRE_QueueDelete
*/
extern UINT32 SRE_QueueCreate(   UINT16 usNodeNum,
                                 UINT16 usMaxNodeSize,
                                 UINT32 *puwQueueID);

/**
 * @ingroup SRE_queue
 * @brief �����С�
 *
 * @par ����:
 * ��ȡָ�������е����ݡ�����ȡ�������ݴ���pBufferAddr��ַ��pBufferAddr��ַ�Ͷ�ȡ���ݴ�С���û����롣
 * @attention
 * <ul>
 * <li>���ж�ȡ�Ų���FIFOģʽ���������ȳ�����ȡ����������д�������(����ڶ��нڵ����Ⱥ�˳��)��</li>
 * <li>���uwBufferSize���ڶ�����ʵ����Ϣ�Ĵ�С����ֻ����ʵ�ʴ�С�����ݣ�����ֻ��ȡuwBufferSize��С�����ݡ�</li>
 * <li>uwBufferSize��С�ĵ�λ��BYTE��</li>
 * <li>����ģʽ������idle����ʹ�ã����û���֤��</li>
 * <li>��osStart֮ǰ���ܵ��øýӿڣ����û���֤��</li>
 * </ul>
 * @param uwQueueID      [IN]      ����Ϊ#UINT32 ������ID��
 * @param pBufferAddr    [OUT]     ����Ϊ#VOID*  ����ȡ��Ŷ��������ݵ���ʼ��ַ��
 * @param puwLen         [IN/OUT]  ����Ϊ#UINT32 ������BUF�Ĵ�С�����ʵ����Ϣ�Ĵ�С��
 * @param uwTimeOut      [IN]      ����Ϊ#UINT32 ����ʱʱ�䡣
 *
 * @retval #SRE_OK                       0x00000000�������ɹ���
 * @retval #OS_ERRNO_QUEUE_PTR_NULL      0x0200270e��������ʱ����ָ��Ϊ�ա�
 * @retval #OS_ERRNO_QUEUE_INVALID       0x0200270d�������о���Ƿ���
 * @retval #OS_ERRNO_QUEUE_SIZE_ZERO     0x0200270f��������ʱ�����Ŷ�ȡ������buffer��СΪ0��
 * @retval #OS_ERRNO_QUEUE_NO_SOURCE     0x02002711, ������ʱ����Ϊ�ա�
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE    0x02002709��Ҫ��ȡ�Ķ��л�δ������
 * @retval #OS_ERRNO_QUEUE_IN_INTERRUPT  0x02002708, �жϲ��ܱ�������
 * @retval #OS_ERRNO_QUEUE_PEND_IN_LOCK  0x02002705���������²��ܱ�������
 * @retval #OS_ERRNO_QUEUE_TIMEOUT       0x02002706�����г�ʱ��

 * @par ����:
 * @li SRE_queue.h���ýӿ��������ڵ�ͷ�ļ���
 * @since RTOSck V100R001C00
 * @see SRE_QueueWrite
*/
extern UINT32 SRE_QueueRead(UINT32  uwQueueID,
                            VOID *  pBufferAddr,
                            UINT32* puwLen,
                            UINT32  uwTimeOut);

/**
 * @ingroup SRE_queue
 * @brief д���С�
 *
 * @par ����:
 * ��ָ������д���ݡ���pBufferAddr��ַ��uwBufferSize��С������д�뵽�����С�
 * @attention
 * <ul>
 * <li>�豣֤uwBufferSize��СС�ڻ���ڶ��н���С��</li>
 * <li>uwBufferSize��С�ĵ�λ��BYTE��                </li>
 * <li>����ģʽ������idle����ʹ�ã����û���֤��      </li>
 * <li>��osStart֮ǰ���ܵ��øýӿڣ����û���֤��     </li>
 * </ul>
 * @param uwQueueID      [IN]  ����Ϊ#UINT32 ������ID��
 * @param pBufferAddr    [IN]  ����Ϊ#VOID*  ��д�����������ݵ���ʼ��ַ��
 * @param uwBufferSize   [IN]  ����Ϊ#UINT32 ��д�����������ݵĴ�С��
 * @param uwTimeOut      [IN]  ����Ϊ#UINT32 ����ʱʱ�䡣
 * @param uwPrio         [IN]  ����Ϊ#UINT32 �����ȼ�, ȡֵOS_QUEUE_NORMAL��OS_QUEUE_URGENT��
 *
 * @retval #SRE_OK                               0x00000000�������ɹ���
 * @retval #OS_ERRNO_QUEUE_PTR_NULL              0x0200270e��д����ʱ����ָ��Ϊ�ա�
 * @retval #OS_ERRNO_QUEUE_INVALID               0x0200270d��д���о���Ƿ���
 * @retval #OS_ERRNO_QUEUE_SIZE_TOO_BIG          0x02002710��д����ʱ������buffer�Ĵ�С���ڶ��н���С��
 * @retval #OS_ERRNO_QUEUE_SIZE_ZERO             0x0200270f��д����ʱ����Ҫд�����ݴ�СΪ0��
 * @retval #OS_ERRNO_QUEUE_PRIO_INVALID          0x02002712���������ȼ�����
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE            0x02002709������û�д�����
 * @retval #OS_ERRNO_QUEUE_NO_SOURCE             0x02002711����������û�п�д����Դ��
 * @retval #OS_ERRNO_QUEUE_IN_INTERRUPT          0x02002708�����жϱ�������
 * @retval #OS_ERRNO_QUEUE_PEND_IN_LOCK          0x02002705���������±�������
 * @retval #OS_ERRNO_QUEUE_TIMEOUT               0x02002706�����г�ʱ��

 * @par ����:
 * @li SRE_queue.h���ýӿ��������ڵ�ͷ�ļ���
 * @since RTOSck V100R001C00
 * @see SRE_QueueRead
*/
extern UINT32 SRE_QueueWrite( UINT32 uwQueueID,
                              VOID * pBufferAddr,
                              UINT32 uwBufferSize,
                              UINT32 uwTimeOut,
                              UINT32 uwPrio);

/**
 * @ingroup SRE_queue
 * @brief ɾ�����С�
 *
 * @par ����:
 * ɾ��һ����Ϣ���С�ɾ���������Դ�����ա�
 * @attention
 * <ul>
 * <li>����ɾ��δ�����Ķ��С�</li>
 * <li>ɾ��ͬ������ʱ������ȷ�����������ڸö��У����ޱ������û��ʱ�������е����񣬷���ɾ������ʧ�ܡ�</li>
 * </ul>
 * @param uwQueueID   [IN] ����Ϊ#UINT32  ������ID��
 *
 * @retval #SRE_OK                       0x00000000�������ɹ���
 * @retval #OS_ERRNO_QUEUE_INVALID       0x0200270d��δ�ҵ�Ҫɾ���Ķ��С�
 * @retval #OS_ERRNO_QUEUE_IN_TSKUSE     0x02002707�������������ڸö��У����в���ɾ����
 * @retval #OS_ERRNO_QUEUE_BUSY          0x0200270a�����񱻼��û�м�ʱд���С�
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE    0x02002709��Ҫɾ���Ķ���δ������

 * @par ����:
 * @li SRE_queue.h���ýӿ��������ڵ�ͷ�ļ���
 * @since RTOSck V100R001C00
 * @see SRE_QueueCreate | SRE_QueueCreateSyn
 */
extern UINT32 SRE_QueueDelete(UINT32  uwQueueID);

/**
 * @ingroup SRE_queue
 * @brief ��ȡ���е���ʷ���ʹ�ó��ȡ�
 *
 * @par ����:
 * ��ȡ�Ӷ��д�����ɾ��ǰ����ʷ���ʹ�ó��ȡ�
 * @attention
 * <ul>
 * <li>��ֵ�ڶ���ɾ��ǰ�����ᱻ���㡣</li>
 * </ul>
 * @param uwQueueID          [IN]  ����Ϊ#UINT32  ������ID
 * @param puwQueueUsedNum    [OUT] ����Ϊ#UINT32*  �����нڵ�ʹ�÷�ֵ
 *
 * @retval #SRE_OK                         0x00000000�������ɹ���
 * @retval #OS_ERRNO_QUEUE_INVALID         0x0200270d��δ�ҵ�Ҫɾ���Ķ��С�
 * @retval #OS_ERRNO_QUEUE_PTR_NULL        0x0200270e��ָ��Ϊ�ա�
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE      0x02002709������δ������

 * @par ����:
 * @li SRE_queue.h���ýӿ��������ڵ�ͷ�ļ���
 * @since RTOSck V100R002C00
 * @see SRE_QueueNodeNumGet
 */
extern UINT32 SRE_QueueUsedPeak(UINT32 uwQueueID, UINT32 *puwQueueUsedNum);

/**
 * @ingroup SRE_queue
 * @brief ��ȡָ��ԴPID�Ĵ�������Ϣ������
 *
 * @par ����:
 * ��ָ�������У���ȡָ��ԴPID�Ĵ�������Ϣ������
 * @attention
 * <ul>
 * <li>PIDΪOS_QUEUE_PID_ALLʱ����ʾ��ȡ���д��������Ϣ���� </li>
 * <li>PID�ĺϷ��Բ����жϣ����Ϸ���PID��ȡ����Ϣ����Ϊ0     </li>
 * </ul>
 * @param uwQueueID   [IN] ����Ϊ#UINT32  ������ID��
 * @param uwTaskPID   [IN] ����Ϊ#UINT32  ���߳�PID��
 * @param puwNum      [OUT]����Ϊ#UINT32*  �����������Ϣ������
 *
 * @retval #SRE_OK                         0x00000000�������ɹ���
 * @retval #OS_ERRNO_QUEUE_INVALID         0x0200270d��δ�ҵ�Ҫɾ���Ķ��С�
 * @retval #OS_ERRNO_QUEUE_PTR_NULL        0x0200270e��ָ��Ϊ�ա�
 * @retval #OS_ERRNO_QUEUE_NOT_CREATE      0x02002709������δ������

 * @par ����:
 * @li SRE_queue.h���ýӿ��������ڵ�ͷ�ļ���
 * @since RTOSck V100R002C00
 * @see SRE_QueueUsedPeak
 */
extern UINT32 SRE_QueueNodeNumGet(UINT32 uwQueueID, UINT32 uwTaskPID, UINT32 *puwNum);
#endif //if (OS_OPTION_QUEUE == YES) 

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _sre_queue_h */


