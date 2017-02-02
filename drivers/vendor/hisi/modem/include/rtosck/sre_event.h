/**
 * @file sre_event.h
 *
 * Copyright(C), 2011-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * �������¼�ģ��Ķ���ͷ�ļ��� \n
 */

/**@defgroup SRE_event �¼�
  *@ingroup SRE_comm
  */

#ifndef _SRE_EVENT_H
#define _SRE_EVENT_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

//֧�ֹ��ܺ�ü�,sre_buildef.h�ļ���֧�ֵĹ��ܺ�
#if (YES == OS_OPTION_EVENT)
/**
 * @ingroup SRE_event
 * �¼��ȴ�ʱ���趨���¼����ȴ���ʱֵ���á�
 */
#define OS_EVENT_WAIT_FOREVER   0xFFFFFFFF

/**
 * @ingroup SRE_event
 * �¼���ȡģʽ����ʾ����uwEventMask�е��κ�һ���¼���
 */
#define OS_EVENT_ANY            0x00000001

/**
 * @ingroup SRE_event
 * �¼���ȡģʽ����ʾ��������uwEventMask�е������¼���
 */
#define OS_EVENT_ALL            0x00000010

/**
 * @ingroup SRE_event
 * �¼���ȡģʽ����ʾ�ȴ������¼���
 */
#define OS_EVENT_WAIT           0x00010000

/**
 * @ingroup SRE_event
 * �¼���ȡģʽ����ʾ���ȴ������¼���
 */
#define OS_EVENT_NOWAIT         0x00100000

/**
 * @ingroup SRE_event
 * �¼������룺�¼���ȡʧ�ܣ������¼�û�з�����
 *
 * ֵ: 0x02002600
 *
 * �����������ʹ�õȴ���ȡ�¼���
 */
#define OS_ERRNO_EVENT_READ_FAILED                          SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x00)

/**
 * @ingroup SRE_event
 * �¼������룺��ȡ�¼���ʱ��
 *
 * ֵ: 0x02002601
 *
 * ��������������¼���ȡ�ȴ�ʱ�䣬�����������������д�¼�������
 */
#define OS_ERRNO_EVENT_READ_TIMEOUT                         SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x01)

/**
 * @ingroup SRE_event
 * �¼������룺д�¼�ʱ�������ID�Ƿ���
 *
 * ֵ: 0x02002602
 *
 * �������: ������Ϸ�����ID��
 */
#define OS_ERRNO_EVENT_TASKID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x02)

/**
 * @ingroup SRE_event
 * �¼������룺д�¼�ʱ�������δ������
 *
 * ֵ: 0x02002603
 *
 * �������: ������Ϸ�����ID�����ȴ��������ٶ���д�¼�������
 */
#define OS_ERRNO_EVENT_TSK_NOT_CREATED                      SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x03)

/**
 * @ingroup SRE_event
 * �¼������룺���¼�ʱEVENTMASK��ηǷ�����β���Ϊ0��
 *
 * ֵ: 0x02002604
 *
 * �������: ������Ϸ�ֵ��
 */
#define OS_ERRNO_EVENT_EVENTMASK_INVALID                    SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x04)

/**
 * @ingroup SRE_event
 * �¼������룺ֻ���������н��ж��¼�������
 *
 * ֵ: 0x02002605
 *
 * �������: ���������н��ж��¼�������
 */
#define OS_ERRNO_EVENT_READ_NOT_IN_TASK                     SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x05)

/**
 * @ingroup SRE_event
 * �¼������룺���¼��ӿ���uwFlags��ηǷ��������Ϊ��OS_EVENT_ANY��OS_EVENT_ALL����һ���ͣ�OS_EVENT_WAIT��OS_EVENT_NOWAIT���е�һ����ʶ��Ľ����OS_EVENT_WAITģʽ�£��ȴ�ʱ�������㡣
 *
 * ֵ: 0x02002606
 *
 * �������: ������Ϸ�����Ρ�
 */
#define OS_ERRNO_EVENT_FLAGS_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x06)

/**
 * @ingroup SRE_event
 * �¼������룺�����������״̬�£���ֹ���������ڶ��¼���
 *
 * ֵ: 0x02002607
 *
 * �������: �����������Ⱥ��ٽ��ж��¼���
 */
#define OS_ERRNO_EVENT_READ_IN_LOCK                         SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x07)

/**
 * @ingroup SRE_event
 * �¼������룺д�¼�ʱEVENT��ηǷ�����β���Ϊ0��
 *
 * ֵ: 0x02002608
 *
 * �������: ������Ϸ�ֵ��
 */
#define OS_ERRNO_EVENT_INVALID                              SRE_ERRNO_OS_ERROR(OS_MID_EVENT, 0x08)

/**
 *@ingroup SRE_event
 *@brief ���¼���
 *
 *@par ����:
 *��ȡ��ǰ�����ָ������ΪuwEventMask���¼�������һ���Զ�ȡ����¼����¼���ȡ�ɹ��󣬱���ȡ���¼����������
 *@attention
 * <ul>
 * <li>��ȡģʽ����ѡ���ȡ�����¼��Ͷ�ȡ�����¼���</li>
 * <li>�ȴ�ģʽ����ѡ��ȴ��Ͳ��ȴ����ɵȴ�ָ��ʱ�䡢���õȴ���</li>
 * <li>����ȡ�¼�û�з�����Ϊ�ȴ�ģʽʱ���ᷢ��������ȣ�������״̬���⡣</li>
 * <li>������IDLE�����ж��¼�����Ҫ�û����б�֤��</li>
 * <li>������ϵͳ��ʼ��֮ǰ���ö��¼��ӿڡ�</li>
 * </ul>
 *
 *@param uwEventMask [IN] ����Ϊ#UINT32������Ҫ��ȡ���¼����룬ÿ��bitλ��Ӧһ���¼���1��ʾҪ��ȡ������β���Ϊ0��
 *@param uwFlags     [IN] ����Ϊ#UINT32����ȡ�¼�����ȡ�Ĳ���,Ϊ��OS_EVENT_ANY��OS_EVENT_ALL����һ���ͣ�OS_EVENT_WAIT��OS_EVENT_NOWAIT���е�һ����ʶ��Ľ����
 *#OS_EVENT_ALL��ʾ��������uwEventMask�е������¼���#OS_EVENT_ANY��ʾ�ȴ�uwEventMask�е��κ�һ���¼���
 *#OS_EVENT_WAIT��ʾ�������¼�û�з������ȴ����գ�#OS_EVENT_NOWAIT��ʾ�������¼�û�з�����������ȴ����ա�
 *@param uwTimeOut   [IN] ����Ϊ#UINT32���ȴ���ʱʱ�䣬��λΪtick��ȡֵ(0~0xFFFFFFFF]����uwFlags��־ΪOS_EVENT_WAIT�������������Ч����ֵΪ#OS_EVENT_WAIT_FOREVER�����ʾ���õȴ���
 *@param puwEvents   [OUT] ����Ϊ#UINT32 *�����ڱ�����յ����¼���ָ�롣�������Ҫ�����������дNULL��
 *
 *@retval #OS_ERRNO_EVENT_READ_FAILED        0x02002600���¼���ȡʧ�ܣ������¼�û�з�����
 *@retval #OS_ERRNO_EVENT_READ_TIMEOUT       0x02002601����ȡ�¼���ʱ��
 *@retval #OS_ERRNO_EVENT_EVENTMASK_INVALID  0x02002604�����¼�ʱEVENTMASK��ηǷ�����β���Ϊ0��
 *@retval #OS_ERRNO_EVENT_READ_NOT_IN_TASK   0x02002605��ֻ���������н��ж��¼�������
 *@retval #OS_ERRNO_EVENT_FLAGS_INVALID      0x02002606�����¼��ӿ���uwFlags��ηǷ���
 *@retval #OS_ERRNO_EVENT_READ_IN_LOCK       0x02002607�������������״̬�£���ֹ���������ڶ��¼���
 *@retval #SRE_OK                            0x00000000�������ɹ���

 *@par ����:
 * <ul>
 *@li sre_event.h���ýӿ��������ڵ�ͷ�ļ���
 *@since RTOSck V100R001C00
 * </ul>
 *@see SRE_EventWrite
*/
extern UINT32 SRE_EventRead( UINT32 uwEventMask,
                             UINT32 uwFlags,
                             UINT32 uwTimeOut,
                             UINT32 *puwEvents );

/**
 *@ingroup SRE_event
 *@brief д�¼���
 *
 *@par ����:
 *д����IDΪuwTaskID��ָ���¼�������һ����д����¼���������RTOSck�ӹܵ��ж��е��á�
 *@attention
 * <ul>
 * <li>��ָ���������ڵȴ���ȡд����¼�����ἤ��ָ�����񣬲�����������ȡ�</li>
 * <li>������IDLE����д�¼�����Ҫ�û����б�֤��</li>
 * </ul>
 *
 *@param uwTaskID [IN] ����Ϊ#UINT32������ID����ʾҪ��ĳ���������д�¼�������
 *@param uwEvents [IN] ����Ϊ#UINT32���¼��ţ�ÿ��bit��Ӧһ���¼���
 *
 *@retval #OS_ERRNO_EVENT_TSK_NOT_CREATED     0x02002603��д�¼�ʱ�������δ������
 *@retval #OS_ERRNO_EVENT_TASKID_INVALID      0x02002602��д�¼�ʱ�������ID�Ƿ���
 *@retval #OS_ERRNO_EVENT_INVALID             0x02002608��д�¼�ʱ����¼����ͷǷ�������Ϊ�㡣
 *@retval #SRE_OK                             0x00000000�������ɹ���
 *@par ����:
 * <ul>
 *@li sre_event.h���ýӿ��������ڵ�ͷ�ļ���
 * </ul>
 *@since RTOSck V100R001C00
 *@see SRE_EventRead
*/
extern UINT32 SRE_EventWrite(UINT32 uwTaskID, UINT32 uwEvents);

#endif //#if (YES == OS_OPTION_EVENT)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_EVENT_H */


