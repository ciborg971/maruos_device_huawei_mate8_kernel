/**
 * @file sre_trace.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������ϵͳģ��Ķ���ͷ�ļ��� \n
 */


/** @defgroup SRE_trace ϵͳ����
 *@ingroup SRE_inspect
 */

#ifndef _SRE_TRACE_H
#define _SRE_TRACE_H

#include "sre_base.h"
#include "sre_mem.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//֧�ֹ��ܺ�ü�,sre_buildef.h�ļ���֧�ֵĹ��ܺ�
#if (OS_OPTION_TRACE == YES) 

/**
 * @ingroup SRE_trace
 * ϵͳ���ٴ����룺�û����õ�ϵͳ���������׵�ַΪ�ջ�16�ֽڲ����롣
 *
 * ֵ: 0x02002501
 *
 * �������: ϵͳ���������׵�ַ����Ϊ�ǿ���16�ֽڶ��롣
 */
#define OS_ERRNO_TRACE_INIT_PARA_ADDR_ERR                                   SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x01)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٴ����룺�û����õ�ϵͳ���������С��ȥ����ͷ�Ĵ�СOS_TRACE_HEAD_SIZE��С�ڵ���0��Ϊ2��N���ݡ�
 *
 * ֵ: 0x02002502
 *
 * �������: ϵͳ���������С��ȥ����ͷ�Ĵ�СOS_TRACE_HEAD_SIZE��Ӧ����16��Ϊ2��N���ݡ�
 */
#define OS_ERRNO_TRACE_INIT_PARA_SIZE_ERR                                   SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x02)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٴ����룺�Ƿ����¼����͡�
 *
 * ֵ: 0x02002505
 *
 * �������: ����Ϊ�Ϸ����¼�����, ��OS_TRACE_TYPE_TSK��OS_TRACE_TYPE_SEM�ȡ�
 */
#define OS_ERRNO_TRACE_TYPE_ERR                                             SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x05)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٴ����룺�û������Ч, ��ָ�롣
 *
 * ֵ: 0x02002506
 *
 * �������: ����ǿյ�ָ�롣
 */
#define OS_ERRNO_TRACE_PARA_INVALID                                         SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x06)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٴ����룺�¼�ID�Ƿ���
 *
 * ֵ: 0x02002507
 *
 * �������: �û������ϱ�ϵͳ����ʱ��������¼�ID���ڵ���OS_TRACE_USRERR��
 */
#define OS_ERRNO_TRACE_EVTID_INVALID                                        SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x07)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٴ����룺�жϺŷǷ���
 *
 * ֵ: 0x02002509
 *
 * �������: ʹ���жϵ�ϵͳ����ʱ�����úϷ���Ӳ�жϺŻ����ж�PID������ο�Ӳ�жϻ����жϵĽ��ܡ�
 */
#define OS_ERRNO_TRACE_INTNUM_INVALID                                       SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x09)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٴ����룺ϵͳ����ģ��û�г�ʼ����
 *
 * ֵ: 0x0200250C
 *
 * �������: ��ϵͳ����ģ����ÿ��أ���Ӧ������OS_TRACE_INCLUDE��
 */
#define OS_ERRNO_TRACE_UNINITED                                             SRE_ERRNO_OS_ERROR(OS_MID_TRACE, 0x0C)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٿ���ͷ��С
 *
 */
#define OS_TRACE_HEAD_SIZE                                                  sizeof(OS_TRACE_OBJ_S)

/**
 * @ingroup SRE_trace
 * ϵͳ���ٿ�����Ϣ�ṹ��
 *
 */
typedef struct tagTraceObj
{
    UINT32 uwSeqID;         /**<  ��һ��ϵͳ���ټ�¼�����к�*/
    UINT32 uwIdxMask;       /**<  ���к�����, ֵΪ�����������־��-1, ��˻�������С��ҪΪ2��N����, �Ҳ�С��16        */
    UINT32 uwRsv1;          /**<  Ӳ��ƽ̨|cpu����|�˺�|ħ����  */
    UINT32 uwRsv2;          /**<  ����λ        */
} OS_TRACE_OBJ_S;

/**
 * @ingroup SRE_trace
 * ϵͳ������־��Ϣ�ṹ��
 *
 */
typedef struct tagTraceEvent
{
    UINT32 uwTSL32;        /**<  CPU cycle�ĵ�32λ  */
    UINT32 uwEvtID;        /**<  �¼�ID        */
    UINT32 uwPara1;        /**<  ����1         */
    UINT32 uwPara2;        /**<  ����2         */
} OS_TRACE_EVENT_S;

/**
* @ingroup  SRE_trace
*
* ����TRACEģ���������Ϣ��
*/
typedef struct tagTraceModInfo
{
    UINT32 uwTraceBufAddr;       /**<ϵͳ���ٿռ���ʼ��ַ, ��16�ֽڶ���*/
    UINT32 uwTraceBufSize;       /**<ϵͳ���ٿռ��С,������ͷ,�۳�����ͷ��СӦΪ2��N�����Ҳ�С��16*/
} TRACE_MOD_INFO_S;

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: Ӳ�жϿ�ʼ�¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ��Ӳ�жϺš�
 */
#define OS_TRACE_HWI_BEGIN                                        1

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: Ӳ�жϽ����¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ��Ӳ�жϺš�
 */
#define OS_TRACE_HWI_END                                          2

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: ���жϿ�ʼ�¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ�����ж�PID��
 */
#define OS_TRACE_SWI_BEGIN                                        3

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: ���жϽ����¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ�����ж�PID��
 */
#define OS_TRACE_SWI_END                                          4


/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: �����г��¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ������PID������״̬��
 * #OS_TRACE_TSKOUT��#OS_TRACE_TSKIN�¼��Ǻ�Ϊһ��
 * ��Ϣ���м�¼�ģ��ڹ��߶˽���ʱ���������ԭ��������Ϣ��
 */
#define OS_TRACE_TSKOUT                                           7

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: ���������¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ������PID������״̬��
 * #OS_TRACE_TSKOUT��#OS_TRACE_TSKIN�¼��Ǻ�Ϊһ����Ϣ���м�¼
 * �ģ��ڹ��߶˽���ʱ���������ԭ��������Ϣ��
 */
#define OS_TRACE_TSKIN                                            8

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: �ź���POST�¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ���ź���ID���ź����ļ���ֵ��
 */
#define OS_TRACE_SEMPOST                                          9

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: ���������¼�����¼����Ϣ�������¼�ID�������롣
 */
#define OS_TRACE_FATAL_ERR                                        10
/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: �쳣�¼�����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ���쳣ʱCPU cycle�ĸ�32λ�͵�32λ��
 */
#define OS_TRACE_EXCEPTION                                        11

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�ID: �û��Զ����¼���ID��0x100��ʼ�� 0x100����ΪOS���¼�ID����¼����Ϣ�������¼�ID��CPU cycle�ĵ�32λ���û�ָ���Ĳ���ֵ��
 */
#define OS_TRACE_USRERR                                           0x100

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�����: Ӳ�жϣ�����#OS_TRACE_HWI_BEGIN��#OS_TRACE_HWI_END�¼���
 */
#define OS_TRACE_TYPE_HWI                                         0x1

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�����: ���жϣ�����#OS_TRACE_SWI_BEGIN��#OS_TRACE_SWI_END�¼���
 */
#define OS_TRACE_TYPE_SWI                                         0x2

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�����: ���񣬰���#OS_TRACE_TSKOUT��#OS_TRACE_TSKIN�¼���
 */
#define OS_TRACE_TYPE_TSK                                         0x4

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�����: �ź���������#OS_TRACE_SEMPOST�¼���
 */
#define OS_TRACE_TYPE_SEM                                         0x8

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�����: �������󣬰���#OS_TRACE_FATAL_ERR�¼���
 */
#define OS_TRACE_TYPE_FATAL_ERR                                   0x10

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�����: �쳣������#OS_TRACE_EXCEPTION�¼���
 */
#define OS_TRACE_TYPE_EXC                                         0x20

/**
 * @ingroup SRE_trace
 * ϵͳ�����¼�����: �����¼����������û��¼���
 */
#define OS_TRACE_TYPE_ALL                                         0xffffffff

/**
 * @ingroup SRE_trace
 * ϵͳ�����жϺ�: �������жϻ�Ӳ�жϡ�
 */
#define OS_TRACE_INT_ALL                                          0xffffffff

/**
* @ingroup  SRE_trace
* @brief ʹ��ϵͳ���١�
*
* @par ����:
* ʹ��ָ���¼����͵�ϵͳ���١�
*
* @attention
* <ul>
* <li>ʹ��ϵͳ���ٵ��¼�������Ϊ�жϣ�������ж�û�д������Կ��Ը��ٸ��жϡ�</li>
* <li>ʹ��ϵͳ���ٵ��¼�������Ϊ�������������û�д������Կ��Ը��ٸ�����</li>
* </ul>
*
* @param  uwEvtType      [IN]   ����#UINT32���¼����ͣ� ȡֵ��Χ:#OS_TRACE_TYPE_HWI�� #OS_TRACE_TYPE_SWI��#OS_TRACE_TYPE_TSK��
                                #OS_TRACE_TYPE_SEM�� #OS_TRACE_TYPE_FATAL_ERR��#OS_TRACE_TYPE_EXC��#OS_TRACE_TYPE_ALL
* @param  uwParam        [IN]   ����#UINT32��Ӳ�жϺŻ����ж�ID�� OS_TRACE_INT_ALL��ʾ����Ӳ�жϻ����жϣ�
                                ��uwEvtTypeΪ�ź������������������쳣���¼����ͣ��ò���������
*
* @retval #OS_ERRNO_TRACE_UNINITED             0x0200250C��ϵͳ����ģ��û�г�ʼ����
* @retval #OS_ERRNO_TRACE_TYPE_ERR             0x02002505���¼����ͷǷ���
* @retval #OS_ERRNO_TRACE_INTNUM_INVALID       0x02002509���жϺŷǷ���
* @retval #SRE_OK                              0x00000000��ʹ��ϵͳ���ٳɹ���
* @par ����:
* <ul><li>sre_trace.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_SysTraceDisable
*/
extern UINT32 SRE_SysTraceEnable(UINT32 uwEvtType, UINT32 uwParam);

/**
* @ingroup  SRE_trace
* @brief ȡ��ϵͳ���١�
*
* @par ����:
* ȡ��ָ���¼����͵�ϵͳ���١�
*
* @attention
* <ul>
* <li>��ָ�����ж�(Ӳ�жϡ����ж�)��û��ʹ��ϵͳ���٣��Կ���ȡ����ϵͳ���١�</li>
* </ul>
*
* @param  uwEvtType      [IN]   ����#UINT32���¼����ͣ� ȡֵ��Χ:#OS_TRACE_TYPE_HWI�� #OS_TRACE_TYPE_SWI��#OS_TRACE_TYPE_TSK��
                                #OS_TRACE_TYPE_SEM�� #OS_TRACE_TYPE_FATAL_ERR��#OS_TRACE_TYPE_EXC��#OS_TRACE_TYPE_ALL��
* @param  uwParam        [IN]   ����#UINT32��Ӳ�жϺŻ����ж�ID�� OS_TRACE_INT_ALL��ʾ����Ӳ�жϻ����жϣ�
*                               ��uwEvtTypeΪ�ź������������������쳣���¼����ͣ� �ò��������塣
*
* @retval #OS_ERRNO_TRACE_UNINITED             0x0200250C��ϵͳ����ģ��û�г�ʼ����
* @retval #OS_ERRNO_TRACE_TYPE_ERR             0x02002505���¼����ͷǷ���
* @retval #OS_ERRNO_TRACE_INTNUM_INVALID       0x02002509���жϺŷǷ���
* @retval #SRE_OK                              0x00000000��ȡ��ϵͳ���ٳɹ���
* @par ����:
* <ul><li>sre_trace.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_SysTraceEnable
*/
extern UINT32 SRE_SysTraceDisable(UINT32 uwEvtType, UINT32 uwParam);

/**
* @ingroup  SRE_trace
* @brief �ϱ��Զ���ϵͳ�����¼���
*
* @par ����:
* �ϱ�һ���Զ���ϵͳ�����¼���
*
* @attention
* <ul>
* <li>�û��¼�IDӦ���ڵ���#OS_TRACE_USRERR��</li>
* </ul>
*
* @param  pstTraceEvt      [IN]   ����#OS_TRACE_EVENT_S *��ָ����ϱ���ϵͳ�����¼���
*                                 ���У�uwTSL32�����û�ֵ����OS��� uwEvtIDΪ�û����¼�ID��uwPara1��uwPara2Ϊ�û��Զ����������Ϣ ��
*
* @retval #OS_ERRNO_TRACE_UNINITED              0x0200250C��ϵͳ����ģ��û�г�ʼ����
* @retval #OS_ERRNO_TRACE_EVTID_INVALID         0x02002507���¼�ID�Ƿ���
* @retval #OS_ERRNO_TRACE_PARA_INVALID          0x02002506���û������Ч�� ��ָ��ȡ�
* @retval #SRE_OK                               0x00000000���ϱ�ϵͳ�����¼��ɹ���
* @par ����:
* <ul><li>sre_trace.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see ��
*/
extern UINT32 SRE_TraceReport(OS_TRACE_EVENT_S *pstTraceEvt);

#endif //if (OS_OPTION_TRACE == YES) 

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_TRACE_H */


