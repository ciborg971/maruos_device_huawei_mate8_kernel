/**
  * @file sre_hunt.h
  *
  * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
  *
  * ������PID��ȡ�Ķ���ͷ�ļ���\n
  */

#ifndef _SRE_HUNT_H
#define _SRE_HUNT_H

#include "sre_base.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**@defgroup sre_hunt Hunt����
  *@ingroup SRE_comm
  */

/**
 * @ingroup sre_hunt
 * HUNT�����룺HUNTģ���ʼ��ʧ�ܡ�
 *
 * ֵ: 0x02001f00
 *
 * ���������ȷ���ڴ�ռ��㹻��SD6183:��ʵ���乲��UNCACHE�ռ����룬����ƽ̨:�ӹ���̬fsc�ڴ����˽��fsc�ڴ�������롣
 */
#define OS_ERRNO_HUNT_INIT_ERROR            SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x00)

/**
 * @ingroup sre_hunt
 * HUNT�����룺������������ж�ʱ���߳���������
 *
 * ֵ: 0x02001f01
 *
 * ���������������������ж�ʱ��ȷ���߳���������Ψһ��
 */
#define OS_ERRNO_HUNT_THREAD_NAME_REPEAT    SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x01)

/**
 * @ingroup sre_hunt
 * HUNT�����룺ͨ������ID���߳�����ȡ�߳�TIDʱ�����߳�δ��������ɾ����
 *
 * ֵ: 0x02001f02
 *
 * ���������ȷ���߳��Ѵ�����δ��ɾ����
 */
#define OS_ERRNO_HUNT_THREAD_NOT_CREAT      SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x02)

/**
 * @ingroup sre_hunt
 * HUNT�����룺ͨ���߳�ID��ȡ�߳���ʱ���ָ��Ϊ�գ� ��ͨ������ȡ����PIDʱ��ηǷ���ͨ������ID��ȡ������ʱ���ָ��Ϊ�ա�
 *
 * ֵ: 0x02001f03
 *
 * ���������ȷ�����ָ��ǿա�����߳�ID������ID�ȵĺϷ��ԡ�
 */
#define OS_ERRNO_HUNT_ILLEGAL_INPUT         SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x03)

/**
 * @ingroup sre_hunt
 * HUNT�����룺ͨ���߳������������ȡIDʱ��Hunt����û�г�ʼ����
 *
 * ֵ: 0x02001f04
 *
 * ���������ȷ���������ں˵�hunt���ѳ�ʼ����
 */
#define OS_ERRNO_HUNT_NOT_INIT              SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x04)

/**
 * @ingroup sre_hunt
 * HUNT�����룺�����û����̣�������������
 *
 * ֵ: 0x02001f05
 *
 * ��������������û�����ʱ��ȷ��������������Ψһ��
 */
#define OS_ERRNO_HUNT_PROCESS_NAME_REPEAT   SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x05)

/**
 * @ingroup sre_hunt
 * HUNT�����룺ͨ����������ȡ����PIDʱ���ý�����û���ҵ���
 *
 * ֵ: 0x02001f06
 *
 * ���������ȷ���ý��̵ĺ��Ѿ������������Ҹý�����ע�ᴴ����δ��ɾ����
 */
#define OS_ERRNO_HUNT_PROCESS_NOT_FOUND     SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x06)

/**
 * @ingroup sre_hunt
 * HUNT�����룺hunt ģ����������ʧ�ܡ�
 *
 * ֵ: 0x02001f07
 *
 * ������������������ֿռ��С��
 */
#define OS_ERRNO_HUNT_NAME_ALLOC_FAILED              SRE_ERRNO_OS_ERROR(OS_MID_HUNT, 0x07)

/**
* @ingroup sre_hunt
* @brief ͨ������ID���߳�����ȡ�߳�ID��
*
* @par ����:
* ͨ������ID���߳���(���жϻ�����)��ȡ�߳�ID��
* @attention
* <ul>
* <li>���˵���#SRE_HuntMature����øýӿڣ�����Ŀ�ĺ��Ƿ����#SRE_HuntMature����������ˣ���������в�ѯ����������һֱ�ȴ���</li>
* <li>���˵���#SRE_HuntMature֮ǰ���øýӿڣ�����עĿ�ĺ��Ƿ����#SRE_HuntMature��ֱ�ӽ��в�ѯ������</li>
* </ul>
*
* @param uwProcessID  [IN] ����Ϊ#UINT32�����������˵Ϊ�˺�(SD6183ΪӲ�̺߳�)�����ڶ����(KOS����UOS����)��˵Ϊ��ѯ�߳����ڵĽ���ID(COREID | INDEX): bit0~bit7: ��������Index; bit8~bit15:�˺ţ�����λ������
* @param pcThreadName [IN] ����Ϊ#CHAR*���߳������ȷ�Χ[1,15]��
* @param puwTID [OUT] ����Ϊ#UINT32*���߳�TID��
*
* @retval #OS_ERRNO_HUNT_THREAD_NOT_CREAT 0x02001f02�����߳�δ��������ɾ����
* @retval #OS_ERRNO_HUNT_ILLEGAL_INPUT    0x02001f03����ηǷ���
* @retval #OS_ERRNO_HUNT_NOT_INIT         0x02001f04��hunt����û�г�ʼ����
* @retval #SRE_OK                         0x00000000����ȡPID�ɹ���
* @par ����:
* <ul><li>sre_hunt.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see SRE_HuntPidByName
*/
extern UINT32 SRE_HuntByName(UINT32 uwProcessID, CHAR *pcThreadName, UINT32 *puwTID);


#if ((OS_OPTION_KERNEL_PROCESS == YES)||(OS_OPTION_USR_PROCESS == YES))
/**
* @ingroup sre_hunt
* @brief ͨ����������ȡ����PID��
*
* @par ����:
* ͨ����������ȡ����PID��
* @attention
* <ul>
* <li>���˵���#SRE_HuntMature����øýӿڣ�����Ŀ�ĺ��Ƿ����#SRE_HuntMature����������ˣ���������в�ѯ����������һֱ�ȴ���</li>
* <li>���˵���#SRE_HuntMature֮ǰ���øýӿڣ�����עĿ�ĺ��Ƿ����#SRE_HuntMature��ֱ�ӽ��в�ѯ������</li>
* <li>���øýӿ���Ҫ��֤��ѯ�Ľ����Ѿ�������</li>
* </ul>
*
* @param ucCoreID  [IN] ����Ϊ#UINT8���߳����ں˺�[0,OS_MAX_CORE_NUM-1]��
* @param pcProcessName [IN] ����Ϊ#CHAR*�����������ȷ�Χ[1,15]��
* @param puwPID [OUT] ����Ϊ#UINT32*������ID��
*
* @retval #OS_ERRNO_HUNT_ILLEGAL_INPUT     0x02001f03����ηǷ���
* @retval #OS_ERRNO_HUNT_PROCESS_NOT_FOUND 0x02001f06��ͨ����������ȡ����PIDʱ���ý�����û���ҵ���
* @retval #SRE_OK                          0x00000000����ȡPID�ɹ���
* @par ����:
* <ul><li>sre_hunt.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R003C00
* @see SRE_ProcessNameSet
*/
extern UINT32 SRE_HuntPidByName( CHAR *pcProcessName, UINT32 *puwProcessID);
#endif

/**
* @ingroup sre_hunt
* @brief ��Ǳ������е���������ж��Ѵ�����ɣ�OS��IDLE���⣩�������˿��Գɹ���ѯ���˵�PID��
*
* @par ����:
* ���ϱ���mature��־��ͬʱ�ñ�־��ʹ�ñ����ڵ���#SRE_HuntByNameʱ�����Ŀ�ĺ�û����������һֱ�ȴ���ֱ��Ŀ�ĺ�������mature��־�ŷ��ز�ѯ�����
* @attention
* <ul>
* <li>�����ڱ������е���������жϣ�OS��IDLE���⣩�������֮����á�</li>
* </ul>
*
* @param �ޡ�
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_hunt.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see SRE_HuntByName
*/
extern VOID SRE_HuntMature(VOID);


#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_HUNT_H */


