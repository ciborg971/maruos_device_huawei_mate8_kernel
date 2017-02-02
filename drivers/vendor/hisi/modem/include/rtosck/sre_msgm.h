/**
 * @file sre_msgm.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������MSGMģ��Ķ���ͷ�ļ��� \n
 */

/**
*@defgroup  SRE_msgm  MSGM��Ϣ����
*@ingroup SRE_comm
*/
#ifndef _SRE_MSGM_H
#define _SRE_MSGM_H

#include "sre_base.h"
#include "sre_msg.h"
#include "sre_hwi.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP) )

/**
 * @ingroup SRE_msgm
 * MSGQ�ĵ�һ��QPORT��
 */
#define SRE_QPORT_ID_0        0

/**
 * @ingroup SRE_msgm
 * MSGQ�ĵڶ���QPORT��
 */
#define SRE_QPORT_ID_1        1

/**
 * @ingroup SRE_msgm
 * MSGQ�ĵ�����QPORT����HACCC���и�QPORT��
 */
#define SRE_QPORT_ID_2        2

/**
 * @ingroup SRE_msgm
 * ȫ��MSGM��ʶ��
 */
#define SRE_GLOBAL_MSGM       0

/**
 * @ingroup SRE_msgm
 * �ֲ�MSGM��ʶ��
 */
#define SRE_LOCAL_MSGM        1

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����Ϣ������ʼ�������У�MSGMͨ������Ӧ�����ߺ˽���״̬Ϊ��ɣ����ж����Ƿ������߹�����
 *
 * ֵ: 0x02002b01
 *
 * �������: ��ҪӲ��ȷ��һ��MSGQ_RESP_STATUS�Ĵ���״̬��ʱ�䲻Ϊ0������MSGM_NOR_CORE_STATE��ʱ�䲻Ϊ1�����⡣
 *
 */
#define OS_ERRNO_MSGM_INIT_MSGQ_NORESP                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x01)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����QPORT�Ķ������ʱ�������PORT ID�Ƿ���
 *
 * ֵ: 0x02002b02
 *
 * �������: QPORT IDȡֵ��Χ: dsp:0-1;cpu:0-1;haccc:0-2��
 *
 */
#define OS_ERRNO_MSGM_QDEP_QORTID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x02)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����QPORT�Ķ������ʱ�������QUEUE ID�Ƿ���
 *
 * ֵ: 0x02002b03
 *
 * �������: QUEUE IDȡֵ��Χ: 0-1��
 *
 */
#define OS_ERRNO_MSGM_QDEP_QUEID_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x03)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����QPORT�Ķ������ʱ������Ķ�����ȷǷ���
 *
 * ֵ: 0x02002b04
 *
 * �������: ������ȱ����Ƿ�0ֵ����GLBAL MSGM���ܳ���SD6182/SD6157:2048��SD6183:8192��LOCAL MSGM���ܳ���SD6182/SD6157:1024��SD6183:2048��
 *
 */
#define OS_ERRNO_MSGM_QDEP_QDEPTH_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x04)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����QPORT�Ķ������ʱ�����д���ʹ��״̬��
 *
 * ֵ: 0x02002b05
 *
 * �������: QPORTֻ֧���ڶ��д���ȥʹ�ܵ�״̬�½������á�
 *
 */
#define OS_ERRNO_MSGM_QDEP_QUEEN_WRONG                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x05)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����Qport��Ϣʱ����Ϣ��ַ�Ƿ���
 *
 * ֵ: 0x02002b07
 *
 * �������: Ϊ�˱�����ECC������QPort��Ϣ����ʹ��ȫF���ݡ�
 *
 */
#define OS_ERROR_MSGM_QPORT_SEND_DATA_INVALID                   SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x07)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺ע��qport��Ϣ����ʱ�������tagֵ�Ƿ���
 *
 * ֵ: 0x02002b08
 *
 * �������: tagֵ��Чȡֵ��Χ��1~7����Ӧ��128bit��Ϣ�е�4��WORD�ĵ�3bit��
 *
 */
#define OS_ERRNO_MSGM_QHOOK_TAG_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x08)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����Qport��ͨ��Ϣʱ�������ַָ��Ϊ�ա�
 *
 * ֵ: 0x02002b09
 *
 * �������: ��ַָ�벻��Ϊ�ա�
 *
 */
#define OS_ERRNO_MSGM_SEND_ADDR_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x09)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����Qport��Ϣʱ����Ϣ��ַΪ��
 *
 * ֵ: 0x02002b0a
 *
 * �������: ��Ҫ�Ϸ�����Ϣ���ַ���Ա������Ϣ���͡�
 *
 */
#define OS_ERROR_MSGM_QPORT_SEND_DATA_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0a)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��QPort�յ��������в��ɾ�ECC����
 *
 * ֵ: 0x02002b0b
 *
 * �������: �ޡ�
 *
 */
#define OS_ERROR_MSGM_QPORT_RECV_SER                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0b)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����Qport��Ϣʱ����Ϣ���ַ��Ч��
 *
 * ֵ: 0x02002b0c
 *
 * �������: ��Ҫ�Ϸ�����Ϣ���ַ���Ա㱣�������Ϣ��
 *
 */
#define OS_ERROR_MSGM_QPORT_RECV_DATA_NULL                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0c)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��MSGQ������Ϣ��
 *
 * ֵ: 0x02002b0d
 *
 * �������: ����MSGQ����Ӧ��MSGM�������Ƿ������ݷ��ͳ�������MSGQ����Ϣ�Ѿ�ȫ���������ꡣ
 *
 */
#define OS_ERRNO_MSGM_RECV_QORT_EMPTY                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0d)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ָ����MSGQ�Ͻ�����Ϣʱ��ָ����QPORT ID�Ƿ���
 *
 * ֵ: 0x02002b0e
 *
 * �������: QPORT IDȡֵ��Χ: dsp:0-1;cpu:0-1;haccc:0-2��
 *
 */
#define OS_ERRNO_MSGM_RECV_QID_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0e)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺ʹ��MSGM���з�����Ϣʱ��ָ����Ŀ�ĺ˷Ƿ���
 *
 * ֵ: 0x02002b0f
 *
 * �������: ָ����Ŀ�ĺ˱�����ʵ�ʴ��ڵĺ˺Ż���Ŀ�ĺ˻�û��������ɣ���������Ϣ����������Ŀ�ĺ���Ҫ�ڰ������ڡ�
 *
 */
#define OS_ERRNO_MSGM_SEND_DSTCORE_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x0f)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺ʹ��MSGM���з�����Ϣʱ��ָ����QPORT ID�Ƿ���
 *
 * ֵ: 0x02002b10
 *
 * �������: QPORT IDȡֵ��Χ: dsp:0-1;cpu:0-1;haccc:0-2��
 *
 */
#define OS_ERRNO_MSGM_SEND_PORTID_INVALID                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x10)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺ʹ��MSGM���з�����Ϣʱ��ָ����QUEUE ID�Ƿ���
 *
 * ֵ: 0x02002b11
 *
 * �������: QUEUE IDֻ��Ϊ0��1��
 *
 */
#define OS_ERRNO_MSGM_SEND_QUEUEID_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x11)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ʹ����װos��Ϣ���͵���Ϣ��װ�ӿ�ʱ��ָ����Ŀ���̷߳Ƿ���
 *
 * ֵ: 0x02002b13
 *
 * �������: �������͸�os�̶�ռ�õ��߳�(idle����idle���жϣ�tick���ж�)���ұ������Ѵ�������Ч�̺߳ţ���������Ϣ����������Ŀ�ĺ���Ҫ�ڰ������ڡ�
 *
 */
#define OS_ERRNO_MSGM_PID_INVALID                               SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x13)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�յ�δע�ṳ�Ӻ�������Ϣ��
 *��
 * ֵ: 0x02002b14
 *
 * �������: �û��ڷ�����Ϣ����ʱ����鷢�����ݵĺϷ��ԣ���֤���͹�ȥ������Tagֵ����Ӧ�Ĺ��Ӻ����Ѿ�ע�����
 *
 */
#define OS_ERRNO_MSGM_QHOOK_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x14)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ʹ����װos��Ϣ���͵���Ϣ��װ�ӿ�ʱ����������Ϣ���ݵ�ָ��Ϊ�ա�
 *
 * ֵ: 0x02002b15
 *
 * �������: ��ʹ����װos��Ϣ���͵���Ϣ��װ�ӿ�ʱ����������Ϣ���ݵ�ָ�벻��Ϊ�ա�
 *
 */
#define OS_ERRNO_MSGM_MSG_POINT_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x15)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����MSGM��IDֵ���Ϸ���
 *
 * ֵ: 0x02002b16
 *
 * �������: ��ȷ��MSGM��IDֵΪSRE_GLOBAL_MSGM��SRE_LOCAL_MSGM(SRE_LOCAL_MSGM��SD6182/SD6183��Ч)��
 *
 */
#define OS_ERRNO_MSGM_ID_ILLEGAL                                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x16)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����TRACE��������ʼ��ַδ256bit���롣
 *
 * ֵ: 0x02002b17
 *
 * �������: ��ȷ�������TRACE��������ʼ��ַ����256bit���ж��롣
 *
 */
#define OS_ERRNO_MSGM_TRACE_BUFFER_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x17)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����TRACE��������Сδ256bit���롣
 *
 * ֵ: 0x02002b18
 *
 * �������: ��ȷ�������TRACE��������С����256bit���ж��롣
 *
 */
#define OS_ERRNO_MSGM_TRACE_SIZE_NOT_ALIGN                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x18)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����TRACE��������ʼ��ַΪNULL��
 *
 * ֵ: 0x02002b19
 *
 * �������: ��ȷ�������TRACE��������ʼ��ַ��ΪNULL��
 *
 */
#define OS_ERRNO_MSGM_TRACE_BUFFER_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x19)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺MSGM��TRACE��������ʼ��ַδ�������á�
 *
 * ֵ: 0x02002b1a
 *
 * �������: ʹ��TRACEʹ�ܽӿ�ǰ����ȷ�ϻ�������ʼ��ַ�Ƿ��Ѿ����ù���
 *
 */
#define OS_ERRNO_MSGM_TRACE_NOT_CONFIG                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1a)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺MSGM��TRACE������ʹ�ܣ���ʱ��ֹ�û��������á�
 *
 * ֵ: 0x02002b1b
 *
 * �������: ��ȷ������ʱ��TRACE���ܴ���δʹ��״̬��
 *
 */
#define OS_ERRNO_MSGM_TRACE_ENABLE                              SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1b)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����TRACE��������СΪ0�򻺳�����С̫���������
 *
 * ֵ: 0x02002b1c
 *
 * �������: ��ȷ������ʱ��TRACE��������С��Ϊ0���С���ʣ��������������
 *
 */
#define OS_ERRNO_MSGM_TRACE_SIZE_ILLEGAL                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1c)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺MSGM��TRACEƥ����������׵�ַΪNULL��
 *
 * ֵ: 0x02002b1d
 *
 * �������: ��ȷ������ʱ��MSGM��TRACEƥ����������׵�ַ��ΪNULL��
 *
 */
#define OS_ERRNO_MSGM_TRACE_FILTERBIT_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_MSG, 0x1D)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�û������ȡ��ǰ��Ϣ��ָ��ΪNULL��
 *
 * ֵ: 0x02002b1e
 *
 * �������: ��ȷ������Ļ�ȡ��ǰ��Ϣ��ָ�벻ΪNULL��
 *
 */
#define OS_ERRNO_MSGM_TRACE_PTR_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1e)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺MSGM Profiling ��������ʼ��ַ�ǿ�ʱ������MSGM Profiling����������ʼ��ַ�����Ȳ��Ϸ���
 *
 * ֵ: 0x02002b1f
 *
 * �������: ���MSGM Profiling ��������ʼ��ַ����16�ֽڶ����Լ���������������16�ֽڶ����Profiling ��������ʼ��ַӦ��С�ڽ�����ַ��
 *
 */
#define OS_ERRNO_MSGM_PROFILING_CONFIG_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x1f)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ڵ���SRE_QportMsgCreate�ӿ���װ��Ϣʱ���������Ϣ����Ƿ����������ɾ������ָ��ΪNULL����������Ϣ���ڱ�ʹ�á�
 *
 * ֵ: 0x02002b21
 *
 * �������: ������Ϣ�Ƿ�ֻ����һ�λ����Ƿ�����ʹ����(����Ϣ��������װ״̬)����鴫�����Ϣ����Ƿ���ȷ(ȷ���ǲ���SRE_MsgAlloc�ӿ����뷵�ص���Ϣ�����û�б�ɾ��)��
 *
 */
#define OS_ERRNO_MSGM_MSG_CREATE_HANDLE_INVALID                 SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x21)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����MSGM�������ʱ��MSGMû�г�ʼ����
 *
 * ֵ: 0x02002b22
 *
 * �������: ��ǰ�˵�MSGM��ʼ����ɺ�������MSGM������ȡ�
 *
 */
#define OS_ERRNO_MSGM_NOT_INITED                                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x22)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺���й�����Ϣ�����շ��Ȳ���ʱ�������handle�Ƿ���
 *
 * ֵ: 0x02002b23
 *
 * �������: ȷ�ϸ�handle�Ƿ����ڹ�����Ϣ���д�ʱ��ȡ��ʹ�ù������Ƿ񱻷Ƿ��޸ġ�
 *
 */
#define OS_ERROR_MSGM_SH_HANDLE_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x23)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ڴ򿪹�����Ϣ����ʱ�������ID�Ƿ���
 *
 * ֵ: 0x02002b24
 *
 * �������: ������Ϣ����ID��Ч��ΧSD6182/SD6157Ϊ[0,31]��SD6183Ϊ[0,63]��
 *
 */
#define OS_ERROR_MSGM_SH_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x24)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�򿪹�����Ϣ����ʱ�������handleָ��Ϊ�ա�
 *
 * ֵ: 0x02002b25
 *
 * �������: ��ָ�벻��Ϊ�ա�
 *
 */
#define OS_ERROR_MSGM_SH_HANDLE_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x25)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�򿪹�����Ϣ����ʱ��FIFO�������ô���
 *
 * ֵ: 0x02002b26
 *
 * �������: FIFO����SD6182/SD6157Ϊ[0,1023]��SD6183Ϊ[0,2047]��Χ�ڡ�
 *
 */
#define OS_ERROR_MSGM_SH_FIFO_OVERRUN                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x26)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺������Ϣ����δ�򿪡�
 *
 * ֵ: 0x02002b27
 *
 * �������: ������Ϣ������ʹ��֮ǰ�����ɱ��˻������˴򿪡�
 *
 */
#define OS_ERROR_MSGM_SH_NOT_OPENED                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x27)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����MSGM���������Ϣ����ѯʱ���������Ϣ����ָ��δ�ա�
 *
 * ֵ: 0x02002b28
 *
 * �������: ��ָ�����ָ����Ч���ݣ��Ա��ѯ���д�ء�
 *
 */
#define OS_ERROR_MSGM_SH_MSGNUM_NULL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x28)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺���͹�����Ϣʱ�����ݷǷ���
 *
 * ֵ: 0x02002b29
 *
 * �������: ȫ0��ȫF�����ݲ������͡�
 *
 */
#define OS_ERROR_MSGM_SH_INVALID_DATA                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x29)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ӹ�����Ϣ���н�������ʱ��������Ϣ����Ϊ�ա�
 *
 * ֵ: 0x02002b2a
 *
 * �������: ȷ�������Ƿ��Ѿ����͡�
 *
 */
#define OS_ERROR_MSGM_SH_RECV_EMPTY                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2a)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ӹ�����Ϣ���н��յ��������в��ɾ�ECC����
 *
 * ֵ: 0x02002b2b
 *
 * �������: �ޡ�
 *
 */
#define OS_ERROR_MSGM_SH_RECV_SER                               SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2b)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ���������ID�Ƿ���
 *
 * ֵ: 0x02002b2c
 *
 * �������: ͬ����Ϣ���и�����ЧID��ΧSD6182/SD6157Ϊ[0, 15]��SD6183Ϊ[0, 255]��
 *
 */
#define OS_ERROR_MSGM_SYN_ID_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2c)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ����������ò���attrָ��Ϊ�ա�
 *
 * ֵ: 0x02002b2d
 *
 * �������: �봫����Ч�����ò�����
 *
 */
#define OS_ERROR_MSGM_SYN_ATTR_NULL                             SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2d)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ����������handle�ĵ�ַָ��Ϊ�ա�
 *
 * ֵ: 0x02002b2e
 *
 * �������: �봫����Ч�ĵ�ַָ�롣
 *
 */
#define OS_ERROR_MSGM_SYN_HANDLE_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2e)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����ͬ����Ϣ����ͬ�����͡�ͳ�Ʋ�ѯ�Ȳ���ʱ�������handle��Ч��
 *
 * ֵ: 0x02002b2f
 *
 * �������: ��ȷ�ϸ�handle�Ƿ�ͨ��������Ϣ���д�ʱ��ã���ʹ�ù�����û�зǷ��޸ġ�
 *
 */
#define OS_ERROR_MSGM_SYN_HANDLE_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x2f)


/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺���չ�����Ϣʱ����Ϣ���ַ��Ч��
 *
 * ֵ: 0x02002b30
 *
 * �������: ��Ҫ�Ϸ�����Ϣ���ַ���Ա㱣�������Ϣ��
 *
 */
#define OS_ERROR_MSGM_SH_RECV_DATA_PTR_NULL                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x30)


/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺startͬ������ʱ��ͬ����Ϣ����δ�򿪡�
 *
 * ֵ: 0x02002b31
 *
 * �������: ͬ�����б����ڴ�֮�󣬲��ܽ���start������
 *
 */
#define OS_ERROR_MSGM_SYN_NOT_OPENED                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x31)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ڴ�ͬ������ʱ�������ͬ��������Ч��
 *
 * ֵ: 0x02002b32
 *
 * �������: ͬ������ֵ��Ч��ΧSD6182/SD6157:[1, 31],SD6183:[1, 127]��
 *
 */
#define OS_ERROR_MSGM_SYN_SYNNUM_INVALID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x32)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ�������LOADģʽ��Ч��
 *
 * ֵ: 0x02002b33
 *
 * �������: ֻ����ʹ��SRE_MSGM_SYN_LOAD_PERIOD��SRE_MSGM_SYN_LOAD_ONCE����ģʽ��
 *
 */
#define OS_ERROR_MSGM_SYN_LOAD_MODE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x33)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ��ѡ�����ж�֪ͨģʽ����ָ����Ŀ�����Ч��
 *
 * ֵ: 0x02002b34
 *
 * �������: ȷ��Ŀ��˺��Ƿ���ȷ��
 *
 */
#define OS_ERROR_MSGM_SYN_DST_CORE_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x34)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ������ĳ�ʱʱ�䵵λ�Ƿ���
 *
 * ֵ: 0x02002b35
 *
 * �������: ��Ч��ʱʱ�䵵λΪ[0, 11]�� ����SRE_MSGM_SYN_TOT_FOREVER��
 *
 */
#define OS_ERROR_MSGM_SYN_TOT_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x35)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ�����ò���ͬ������ģʽ�Ƿ���
 *
 * ֵ: 0x02002b36
 *
 * �������: ��ЧֵΪSRE_MSGM_SYN_RECV_IRQ��SRE_MSGM_SYN_RECV_MSG��
 *
 */
#define OS_ERROR_MSGM_SYN_RECV_MODE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x36)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ��ѡ������Ϣ֪ͨģʽ������Ϣ����Ŀ���ַ�Ƿ���
 *
 * ֵ: 0x02002b37
 *
 * �������: ��ȷ�ϸõ�ַ�Ƿ�Ϊ��Чȫ�ֵ�ַ, ���ҵ�ַ16�ֽڶ��롣
 *
 */
#define OS_ERROR_MSGM_SYN_DES_ADDR_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x37)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ҽ��ж�֪ͨ����ʱ��������жϺŻ��ж�ģʽ��Ч��
 *
 * ֵ: 0x02002b38
 *
 * �������: ��ǰ82��57оƬ�ɹҽ��ж�֪ͨ������Ч�жϺŷ�ΧΪ[19, 26]����ÿ�ιҽӲ��õ��жϺź��ж�ģʽ����һ�¡�
 *
 */
#define OS_ERROR_MSGM_SYN_RECV_IRQ_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x38)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ҽ��ж�֪ͨ����ʱ�������Ѿ�ע�ᡣ
 *
 * ֵ: 0x02002b39
 *
 * �������: ��ȷ��֮ǰ�Ƿ��Ѿ��ɹ�ע�ᡣ
 *
 */
#define OS_ERROR_MSGM_SYN_IRQ_RECV_DISCARD                       SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x39)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ѯ��ǰͬ������ʱ������ķ��ص�ַָ��Ϊ�ա�
 *
 * ֵ: 0x02002b3a
 *
 * �������: ��������Ч��ַָ�롣
 *
 */
#define OS_ERROR_MSGM_SYN_MSGCNT_NULL                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3a)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����ͬ����Ϣʱ����Ϣ���ַΪ�ա�
 *
 * ֵ: 0x02002b3b
 *
 * �������: ����Ϣ���ַ������Ϊ�ա�
 *
 */
#define OS_ERROR_MSGM_SYN_MSG_PTR_NULL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3b)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺ͬ����Ϣ���в���ͬ�������С�
 *
 * ֵ: 0x02002b3c
 *
 * �������: ͬ�������ڷ��͡�ͳ�ƵȲ���ǰ����Ҫ��start�ö��С�
 *
 */
#define OS_ERROR_MSGM_SYN_NOT_GOING                              SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3c)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺ͬ����Ϣ������Ϣ����
 *
 * ֵ: 0x02002b3d
 *
 * �������: ͬ��֪ͨ��Ϣ�������������ʱ��������ʹ��ȫ0��ȫf����Ϣ��
 *
 */
#define OS_ERROR_MSGM_SYN_MSG_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3d)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ҽ��ж�֪ͨ����ʱ��ע�ṳ��Ϊ�ա�
 *
 * ֵ: 0x02002b3e
 *
 * �������: ע�ṳ�Ӳ���Ϊ�ա�
 *
 */
#define OS_ERROR_MSGM_SYN_RECV_HOOK_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3e)

/**
 * @ingroup SRE_msgm
 * ����ʵ����������������������MSGM��ͨ���л�������Χʱ�����MSGM������ʼ��ַ�򳤶ȷ�4�ֽڶ��롣
 *
 * ֵ: 0x02002b3f
 *
 * �������: ��ȷ�������MSGM������ʼ��ַ�ͳ��ȶ���4�ֽڶ���ġ�
 */
#define OS_ERRNO_MSGM_CFG_ADDR_OR_LEN_NOT_ALIGN                  SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x3f)

/**
 * @ingroup SRE_msgm
 * ����ʵ����������ʱ�����MSGM������ʼ��ַ�Ƿ���
 *
 * ֵ: 0x02002b40
 *
 * �������: ��ȷ�������MSGM������ʼ��ַ���������֧�ֵĵ�ַ��
 */
#define OS_ERRNO_MSGM_CFG_START_ADDR_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x40)

/**
 * @ingroup SRE_msgm
 * ����ʵ����������ʱ�����MSGM���г��ȷǷ���
 *
 * ֵ: 0x02002b41
 *
 * �������: ��ȷ�������MSGM���г��Ȳ��������֧�ֵĳ��ȡ�
 */
#define OS_ERRNO_MSGM_CFG_QUEUE_LEN_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x41)

/**
 * @ingroup SRE_msgm
 * ����ʵ����������ʱ�����MSGM������ʼ��ַ�ͳ��Ⱦ���������Ƿ���
 *
 * ֵ: 0x02002b42
 *
 * �������: ��ȷ�������MSGM������ʼ��ַ�ͳ��Ⱦ���������Ϸ�������Global MSGM��ͨ���У���Ч��ΧSD6182/SD6157Ϊ[0,2047]��SD6183Ϊ[0,8191]������Local MSGM��ͨ���У��Լ�������У���Ч��ΧSD6182/SD6157Ϊ[0,1023]��SD6183Ϊ[0,2047]��
 */
#define OS_ERRNO_MSGM_CFG_QUEUE_REGION_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x42)

/**
 * @ingroup SRE_msgm
 * ���ñ��˵���ͨ�ֲ���Ϣ���峤�ȹ�����
 *
 * ֵ: 0x02002b43
 *
 * �������: ��ȷ����ʵ�����к���������ͨ�ֲ���Ϣ�����ܳ��Ȳ���������ı�ʵ���������ͨ�ֲ���Ϣ���峤�ȡ�
 */
#define OS_ERRNO_MSGM_CFG_LOCAL_QUE_TOO_LONG                    SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x43)

/**
 * @ingroup SRE_msgm
 * ���ñ��˵���ͨȫ����Ϣ���峤�ȹ�����
 *
 * ֵ: 0x02002b44
 *
 * �������: ��ȷ����ʵ�����к���������ͨȫ����Ϣ�����ܳ��Ȳ���������ı�ʵ���������ͨȫ����Ϣ���峤�ȡ�
 */
#define OS_ERRNO_MSGM_CFG_GLOBAL_QUE_TOO_LONG                   SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x44)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ȡ������Ϣ������ڵ�ַʱ�������ַָ��Ϊ�ա�
 *
 * ֵ: 0x02002b45
 *
 * �������: �õ�ַָ�벻��Ϊ�ա�
 *
 */
#define OS_ERROR_MSGM_SH_ADDR_GET_NULL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x45)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ȡͬ����Ϣ������ڵ�ַʱ�������ַָ��Ϊ�ա�
 *
 * ֵ: 0x02002b46
 *
 * �������: �õ�ַָ�벻��Ϊ�ա�
 *
 */
#define OS_ERROR_MSGM_SYN_ADDR_GET_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x46)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺ע��ͬ����Ϣ�����ж�֪ͨ���Ӻ���ʱ�������ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02002b47
 *
 * �������: ����OSȱʡ������С���á�
 *
 */
#define OS_ERROR_MSGM_SYN_IRQ_NO_MEMORY                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x47)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺������ͨ��Ϣ���������ʱ������Ļ������׵�ַ��Ч��
 *
 * ֵ: 0x02002b48
 *
 * �������: �������׵�ַ������ΪNULL����Ϊ��Ч��ȫ�ֵ�ַ��
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_ILLEGAL                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x48)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺������ͨ��Ϣ���������ʱ������Ļ�������С��Ч��
 *
 * ֵ: 0x02002b49
 *
 * �������: ��������СҪ��16�ֽڶ��룬��Ϊ��Ч��ȫ�ֵ�ַ�ռ䡣
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_BUFFER_SIZE_ILLEGAL                SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x49)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺������ͨ��Ϣ���������ʱ����������ַû�е�ַ���롣
 *
 * ֵ: 0x02002b4a
 *
 * �������: �������׵�ַ�ͳ��ȶ�Ҫ��16�ֽڶ��롣
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_NOT_ALIGN              SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4a)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺������ͨ��Ϣ���������ʱ�������MSGM ID��Ч��
 *
 * ֵ: 0x02002b4b
 *
 * �������: MSGM ID��ЧֵΪSRE_GLOBAL_MSGM��SRE_LOCAL_MSGM(SRE_LOCAL_MSGMֻ��SD6182/SD6183��Ч)��
 *
 */
#define OS_ERRNO_MSGM_NOR_OV_MSGM_ID_ILLEGAL                    SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4b)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺���͹�����Ϣʱ����Ϣ���ַ��Ч��
 *
 * ֵ: 0x02002b4c
 *
 * �������: ��Ҫ�Ϸ�����Ϣ���ַ���Ա������Ϣ���͡�
 *
 */
#define OS_ERROR_MSGM_SH_SEND_DATA_PTR_NULL                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4c)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����VMIDʱ�������VMIDֵ��Ч��
 *
 * ֵ: 0x02002b4e
 *
 * �������: ��VMID����Ϊͨ����VMIDʱ��VMIDֵ��Ч��Χ[0,7]����Ϊͨ��VMIDʱ����Ч��Χ��8bit��Ч��
 *
 */
#define OS_ERRNO_MSGM_VMID_VALUE_ILLEGAL                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4e)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����ͨ������ֵ��Ч��
 *
 * ֵ: 0x02002b4f
 *
 * �������: ͨ������ֵ��Ч��ΧΪ[0,3]��
 *
 */
#define OS_ERRNO_MSGM_CHG_IDX_ILLEGAL                           SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x4f)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺������ͨ��Ϣ����VMIDʱ������ı��ֵ��Ч��
 *
 * ֵ: 0x02002b50
 *
 * �������: Ӳ�̱߳��ֵ��Ч��Χ[0,33]��
 *
 */
#define OS_ERRNO_MSGM_NOR_CORE_IDX_ILLEGAL                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x50)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺���ù��������VMIDʱ������ı��ֵ��Ч��
 *
 * ֵ: 0x02002b51
 *
 * �������: �����������ֵ��Ч��Χ[0,7]��
 *
 */
#define OS_ERRNO_MSGM_SH_IDX_ILLEGAL                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x51)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����ͬ��������VMIDʱ������ı��ֵ��Ч��
 *
 * ֵ: 0x02002b52
 *
 * �������: �����������ֵ��Ч��Χ[0,31]��
 *
 */
#define OS_ERRNO_MSGM_SYNC_IDX_ILLEGAL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x52)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����Ķ���������Ч��
 *
 * ֵ: 0x02002b53
 *
 * �������: MSGM����������Чֵ��Χ[0,2]��
 *
 */
#define OS_ERRNO_MSGM_QUEUE_TYPE_ILLEGAL                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x53)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺����ĺ˺���Ч��
 *
 * ֵ: 0x02002b54
 *
 * �������: �˺���Ч��ΧSD6182:[0-16]��SD6157:(0��1��2��12)��SD6183[0,33]��
 *
 */
#define OS_ERRNO_MSGM_COREID_INVALID                            SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x54)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�����ͨ����ӳ�����ñ�Ƿ���
 *
 * ֵ: 0x02002b55
 *
 * �������: ��ͨ����Ӳ�߳�bitmap��34λ��Ч�����������bitmap��8λ��Ч��
 *
 */
#define OS_ERRNO_MSGM_MAP_INFO_ILLEGAL                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x55)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ѯͬ����Ϣ����ʹ��״̬ʱ������ʹ��״̬�ĵ�ַָ��Ϊ�ա�
 *
 * ֵ: 0x02002b56
 *
 * �������: �봫����Ч�ĵ�ַָ�롣
 *
 */
#define OS_ERROR_MSGM_SYN_EN_STATE_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x56)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ�����÷�����Ϣ����ģʽ�Ƿ���
 *
 * ֵ: 0x02002b57
 *
 * �������: ��ЧֵΪSRE_MSGM_SYN_DATA_DYN��SRE_MSGM_SYN_DATA_STATIC��
 *
 */
#define OS_ERROR_MSGM_SYN_DATA_MODE_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x57)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺��ͬ����Ϣ����ʱ������ƥ��wordֵ�Ƿ���
 *
 * ֵ: 0x02002b58
 *
 * �������: ��Ч��Χ[0,3]��
 *
 */
#define OS_ERROR_MSGM_SYN_CMP_WORD_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x58)


/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺�ں˽��̷ǿ��жϽ���Qport��Ϣʱ��Ŀ�Ľ��̵ľֲ��߳�ID��ȫ���߳�ID����PID�Ƿ���
 *
 * ֵ: 0x02002b59
 *
 * �������: �Ų�Ŀ�Ľ��̵��û��߳��Ƿ񴴽�����
 *
 */
#define OS_ERROR_MSGM_INVLAID_GLTID_PID                        SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x59)

/**
 * @ingroup SRE_msgm
 * �����Ϣ���������룺KOS��ǿ��жϽ���Qport��Ϣʱ��Ŀ�Ľ��̵���ϢMSGM�����������
 *
 * ֵ: 0x02002b5a
 *
 * �������: ȷ���û����̵���Ϣ��ʱ���ա�
 *
 */
#define OS_ERROR_MSGM_USR_MSG_BUF_OV                          SRE_ERRNO_OS_ERROR(OS_MID_MSGM, 0x5a)


/**
 * @ingroup SRE_msgm
 * @brief qport��Ϣ�������Ͷ��塣
 *
 * @par ����:
 * �ù���ͨ��SRE_QportHookSet����ע�ᡣ
 * �����˵�osʹ�õ�Qport�ǿ��жϽ��յ������͵���Ϣʱ���Ὣ���յ�����Ϣͨ�����ݸ������������û����д���
 * @attention �ޡ�
 *
 * @param  auwData[4] [IN] ����#UINT32�����յ���128bit��Ϣ���׵�ַ��
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see �ޡ�
 */
typedef VOID (*SRE_QPORT_HOOK)(UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * MSGMģ��������Ϣ�Ľṹ�嶨�塣
 */
typedef struct tagMsgmModInfo
{
    VOID  *pProfBufAddr;        /**< ÿ���˵�profiling�������׵�ַ */
    UINT32 uwProfBufSize;       /**< ÿ���˵�profiling���������� */
}MSGM_MOD_INFO_S;

/**
 * @ingroup SRE_task
 * ͬ��������Ϣ����handle��
 */
typedef UINT32 QUE_HANDLE_T;

/**
 * @ingroup SRE_msgm
 * @brief: ͬ����Ϣ�ж�֪ͨ�������Ͷ��塣
 *
 * @par ����:
 * �ù���ͨ��SRE_MsgmSynRevHookReg����ע�ᡣ
 * �������յ�ͬ����Ϣ�ж�֪ͨ�󣬻�ͨ���ýӿ�֪ͨ�û�����һ������
 * @attention �ޡ�
 *
 * @param  hQue [IN] ����#QUE_HANDLE_T��ͬ����Ϣ����handle��
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynRevHookReg
 */
typedef VOID (* SRE_MSGM_SYN_REV_HOOK)(QUE_HANDLE_T hQue);

/**
 * @ingroup SRE_msgm
 * ͬ����Ϣ���м������ڼ�������ģʽ
 */
#define SRE_MSGM_SYN_LOAD_PERIOD    0

/**
 * @ingroup SRE_msgm
 * ͬ����Ϣ���м������μ�������ģʽ
 */
#define SRE_MSGM_SYN_LOAD_ONCE      1

/**
 * @ingroup SRE_msgm
 * SD6182/SD6157 ͬ����Ϣ���в����жϷ�ʽ����֪ͨ
 */
#define SRE_MSGM_SYN_RECV_IRQ       0

/**
 * @ingroup SRE_msgm
 * SD6182/SD6157 ͬ����Ϣ���в�����Ϣ��ʽ����֪ͨ
 */
#define SRE_MSGM_SYN_RECV_MSG       1

/**
 * @ingroup SRE_msgm
 * SD6183 ͬ����Ϣ���в��ö�̬ģʽ
 */
#define SRE_MSGM_SYN_DATA_DYN       0

/**
 * @ingroup SRE_msgm
 * SD6183 ͬ����Ϣ���в��þ�̬ģʽ
 */
#define SRE_MSGM_SYN_DATA_STATIC    1

/**
 * @ingroup SRE_msgm
 * ͬ����Ϣ���г�ʱʱ�䣬��ʾ������ʱ���
 */
#define SRE_MSGM_SYN_TOT_FOREVER    0xFFFFFFFFU

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup SRE_msgm
 * SD6182/SD6157 MSGMͬ����Ϣ�������ò����Ľṹ�嶨�塣
 */
typedef struct tagSreSynQueAttr
{
    UINT32 uwLoadMode;       /**< ������ͬ�����ط�ʽ��SRE_MSGM_SYN_LOAD_PERIOD��SRE_MSGM_SYN_LOAD_ONCE                                   */
    UINT32 uwRecvMode;       /**< ͬ�����֪ͨģʽ��SRE_MSGM_SYN_RECV_IRQ���ж�ģʽ, SRE_MSGM_SYN_RECV_MSG:��Ϣ֪ͨģʽ                  */
    UINT32 uwSynCnt;         /**< ͬ������ֵ����Ч��Χ[1, 31]                                                                            */
    UINT32 uwTimeOut;        /**< ��ʱʱ�䵵λ��ȡֵ��ΧN: [0~11]����Ӧ��ʱʱ��: 2^N*8Kcycles�� SRE_MSGM_SYN_TOT_FOREVER��ʾ������ʱ��� */
    UINT32 uwSynMatch;       /**< ��Ϣ�Ĺ������ݣ�������Ϣ�����һ��word���й���                                                         */
    UINT32 uwSynMask;        /**< ������Ϣ�����룬��Ӧ����λ����Ϊ0������Ӧλ��Ҫ������Ϣƥ���顣������Ϣ�����һ��word��������        */
    UINT32 uwIrqDstCore;     /**< �ж�֪ͨģʽʱ��֪ͨ��Ŀ��˺š�(���ж�֪ͨģʽ��Ч)                                                   */
    VOID * pMsgDstAddr;      /**< ��Ϣ֪ͨģʽʱ����Ϣ֪ͨ��Ŀ�ĵ�ַ��(����Ϣ֪ͨģʽ��Ч, ��Ҫ����Ϊ��Чȫ�ֵ�ַ��16�ֽڶ���)           */
    UINT32 auwMsgData[4];    /**< ��Ϣ֪ͨģʽʱ����Ϣ֪ͨ����Ϣ���ݡ�(����Ϣ֪ͨģʽ��Ч)                                               */
}SRE_SYN_QUE_ATTR_S;

#elif (OS_HARDWARE_PLATFORM == OS_HIDSP)

/**
 * @ingroup SRE_msgm
 * SD6183 MSGMͬ����Ϣ�������ò����Ľṹ�嶨�塣
 */
typedef struct tagSreSynQueAttr
{
    UINT32 uwLoadMode;       /**< ������ͬ�����ط�ʽ��SRE_MSGM_SYN_LOAD_PERIOD��SRE_MSGM_SYN_LOAD_ONCE                                   */
    UINT32 uwQueMode;        /**< ������Ϣ����ģʽ��SRE_MSGM_SYN_DATA_DYN����̬ģʽ, SRE_MSGM_SYN_DATA_STATIC:��̬ģʽ                   */
    UINT32 uwSynCnt;         /**< ͬ������ֵ����Ч��Χ[1, 127]                                                                           */
    UINT32 uwTimeOut;        /**< ��ʱʱ�䵵λ��ȡֵ��ΧN: [0~11]����Ӧ��ʱʱ��: 2^N*8Kcycles�� SRE_MSGM_SYN_TOT_FOREVER��ʾ������ʱ��� */
    UINT32 uwSynMatch;       /**< ��Ϣ�Ĺ������ݣ�������Ϣ��uwSynCmpWord��word���й���                                                   */
    UINT32 uwSynMask;        /**< ������Ϣ�����룬��Ӧ����λ����Ϊ1������Ӧλ��Ҫ������Ϣƥ���顣������Ϣ��uwSynCmpWord��word��������  */
    UINT32 uwSynCmpWord;     /**< ��Ϣ���ڼ���WORD����Ч��Χ[0, 3]                                                                     */
    VOID * pMsgDstAddr;      /**< ��Ϣ֪ͨģʽʱ����Ϣ֪ͨ��Ŀ�ĵ�ַ��(����Ϣ֪ͨģʽ��Ч, ��Ҫ����Ϊ��Чȫ�������ַ��16�ֽڶ���)       */
    UINT32 auwMsgData[4];    /**< ��Ϣ֪ͨģʽʱ����Ϣ֪ͨ����Ϣ���ݡ�(����Ϣ֪ͨģʽ��Ч)                                               */
}SRE_SYN_QUE_ATTR_S;

#endif

/**
 * @ingroup SRE_msgm
 * SD6183 ��������ֵ
 */
typedef enum tagMsgmQueueType
{
    OS_MSGM_NOR_QUEUE     = 0,    /**< ��ͨ��Ϣ����             */
    OS_MSGM_SH_QUEUE      = 1,    /**< ������Ϣ����             */
    OS_MSGM_SYNC_QUEUE    = 2     /**< ͬ����Ϣ����             */
}MSGM_QUEUE_TYPE_E;

/**
 * @ingroup SRE_msgm
 * SD6183 ͨ����ӳ��Ľṹ�嶨�塣
 */
typedef struct tagMsgmChgMapInfo
{
    UINT64 ullNorChBitmap;        /**< ��ͨ����Ӳ�̺߳�bitmap����34bit��Ч��ÿ1bit����1��Ӳ�̺߳�*/
    UINT32 uwShChBitmap;          /**< ���������bitmap����8bit��Ч��ÿ1bit����1�����������     */
    UINT32 uwSyncChBitmap;        /**< ͬ��������bitmap��32λ��Ч�� ÿ1bit����1��ͬ��������      */
}MSGM_CHG_MAP_S;

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_HIDSP))

#if (OS_OPTION_MSGM_USR_MNG == YES)
/**
 * @ingroup SRE_msgm
 * @brief ����ָ����ָ��Qportָ�����е���ʼλ�ú���ȡ�
 *
 * @par ����:
 * ÿ��Qport��MSGM�д�������������У����ӿڸ��ݶ�����ʼλ�ö�ÿ��������е���Ƚ������ã�һ����ȵ�Ԫ����һ����Ϣ��
 * ��������������֮����ָ�����н������ȼ����ã�Ĭ�ϻὫ0�������óɸ����ȼ���1�������õ����ȼ�����ʹ�ܶ��й��ܡ�
 * @attention
 * <ul>
 * <li>������SD6183��SD6182/SD6157ƽ̨��</li>
 * <li>OSʹ����0��QPORT��0�Ŷ��У�0��QPORTΪOS��������Ϊ�жϷ�ʽ�����û�����ͨ���жϷ�ʽ����0��QPORT��������Ϣ(����ʱͨ���û��Լ�ע��Ĺ��Ӻ���ʵ����Ϣ���մ���)��</li>
 * <li>SD6182/SD6157 CPU��DSPʹ�õ����ж�����ȼ��������ܳ���2048��HACCCʹ�õ����ж�����ȼ��������ܳ���1024����SD6183 DSP��ʹ�õ����ж�����ȼ��������ܳ���8192��HACCCʹ�õ����ж�����ȼ��������ܳ���2048��</li>
 * <li>������ʼλ�úͶ�����ȱ������ó�4����������</li>
 * <li>�����ȵ���SRE_MsgmQportReset�ӿڶ�ָ���˽�����λ���������ö�Ӧ�˵Ķ�����ȡ�</li>
 * <li>SD6183ƽ̨���û���֤��ͨ����VMIDȨ�޵��øýӿڡ�</li>
 * </ul>
 *
 * @param uwCoreID       [IN] ����#UINT32��ָ���ĺ˺�,ȡֵ��ΧSD6182:[0-16]��SD6157:(0��1��2��12)��SD6183[0,33]��
 * @param uwQportID      [IN] ����#UINT32��ָ����QPORT ID,ȡֵ��Χ��dsp:[0,1];haccc:[0,2]��
 * @param uwQueIdx       [IN] ����#UINT32��ָ���Ķ���ID��ȡֵ��Χ��0��1��
 * @param uwQueStart     [IN] ����#UINT32��������ʼλ�ã�ȡֵ��Χ��4������������
 * @param uwQueDepth     [IN] ����#UINT32�����е���ȣ�ȡֵ��Χ��4������������
 *
 * @retval #OS_ERRNO_MSGM_COREID_INVALID            0x02002b54���˺ŷǷ���
 * @retval #OS_ERRNO_MSGM_QDEP_QORTID_INVALID       0x02002b02��QPORT ID�Ƿ���
 * @retval #OS_ERRNO_MSGM_QDEP_QUEID_INVALID        0x02002b03������ID�Ƿ���
 * @retval #OS_ERRNO_MSGM_QDEP_QDEPTH_INVALID       0x02002b04��������ȷǷ���
 * @retval #OS_ERRNO_MSGM_INIT_MSGQ_NORESP          0x02002b01�������Ϣ������ʼ�������У�MSGMͨ������Ӧ�����ߺ˽���״̬Ϊ��ɣ����ж����Ƿ������߹�����
 * @retval #SRE_OK                                  0x00000000�����óɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_MsgmNorQueSet(UINT32 uwCoreID, UINT32 uwQportID, UINT32 uwQueIdx, UINT32 uwQueStart, UINT32 uwQueDepth);

/**
 * @ingroup SRE_msgm
 * @brief ��ָ���˵�MSGM���к�Qport��λ��
 *
 * @par ����:
 * ��ָ�������е�Qport�Լ�MSGM������λ��
 * @attention
 * <ul>
 * <li>������SD6183��SD6182/SD6157ƽ̨��</li>
 * <li>�����ȵ��øýӿڶ�ָ���˽�����λ���������ö�Ӧ�˵Ķ�����ȡ�</li>
 * <li>���øýӿں�ָ���˵�MSGM���к�Qport�����������Ϣ���ᶪʧ��</li>
 * <li>SD6183ƽ̨���û���֤��ͨ����VMIDȨ�޵��øýӿڡ�</li>
 * </ul>
 *
 * @param uwCoreID       [IN] ����#UINT32��ָ���ĺ˺�,ȡֵ��ΧSD6182:[0-16]��SD6157:(0-2��12)��SD6183[0,33]��
 *
 * @retval #OS_ERRNO_MSGM_COREID_INVALID            0x02002b54���˺ŷǷ���
 * @retval #OS_ERRNO_MSGM_INIT_MSGQ_NORESP          0x02002b01�������Ϣ������ʼ�������У�MSGMͨ������Ӧ�����ߺ˽���״̬Ϊ��ɣ����ж����Ƿ������߹�����
 * @retval #SRE_OK                                  0x00000000�����óɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_MsgmQportReset(UINT32 uwCoreID);

#else
/**
 * @ingroup SRE_msgm
 * @brief MSGM�������ú�����
 *
 * @par ����:
 * ÿ��Qport��MSGM�д�������������У����ӿڶ�ÿ��������е���Ƚ������ã�һ����ȵ�Ԫ����һ����Ϣ��
 * ��������������֮���Ա����н������ȼ����ã�Ĭ�ϻὫ0�������óɸ����ȼ���1�������õ����ȼ�����ʹ�ܶ��й��ܡ�
 * @attention
 * <ul>
 * <li>������SD6182 ��SD6157ƽ̨��</li>
 * <li>OSʹ����0��QPORT��0�Ŷ��У�0��QPORTΪOS��������Ϊ�жϷ�ʽ�����û�����ͨ���жϷ�ʽ����0��QPORT��������Ϣ(����ʱͨ���û��Լ�ע��Ĺ��Ӻ���ʵ����Ϣ���մ���)��</li>
 * <li>CPU��DSPʹ�õ����ж�����ȼ��������ܳ���2048��HACCCʹ�õ����ж�����ȼ��������ܳ���1024��</li>
 * <li>���е���Ⱦ������ó�4����������������ǣ��ӿ��Զ������������4����������Ʃ�����ó�7��ʵ����Ч��8��</li>
 * </ul>
 *
 * @param uwQportID      [IN] ����#UINT32��ָ����QPORT ID,ȡֵ��Χ��dsp:[0,1];cpu:[0,1];haccc:[0,2]��
 * @param uwQueIdx       [IN] ����#UINT32��ָ���Ķ���ID��ȡֵ��Χ��0��1��
 * @param uwQueDepth     [IN] ����#UINT32�����е���ȣ�ȡֵ��Χ��4������������
 *
 * @retval #OS_ERRNO_MSGM_QDEP_QORTID_INVALID       0x02002b02��QPORT ID�Ƿ���
 * @retval #OS_ERRNO_MSGM_QDEP_QUEID_INVALID        0x02002b03������ID�Ƿ���
 * @retval #OS_ERRNO_MSGM_QDEP_QDEPTH_INVALID       0x02002b04��������ȷǷ���
 * @retval #OS_ERRNO_MSGM_QDEP_QUEEN_WRONG          0x02002b05�����������ѱ�ʹ�ܡ�
 * @retval #OS_ERRNO_MSGM_NOT_INITED                0x02002b22������MSGM�������ʱ��MSGMû�г�ʼ����
 * @retval #OS_ERRNO_MSGM_CFG_LOCAL_QUE_TOO_LONG    0x02002b43�����ñ��˵���ͨ�ֲ���Ϣ���峤�ȹ�����
 * @retval #OS_ERRNO_MSGM_CFG_GLOBAL_QUE_TOO_LONG   0x02002b44�����ñ��˵���ͨȫ����Ϣ���峤�ȹ�����
 * @retval #SRE_OK                                  0x00000000�����óɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_QueDepthSet(UINT32 uwQportID, UINT32 uwQueIdx, UINT32 uwQueDepth);

/**
 * @ingroup SRE_msgm
 * @brief ���غ���������MSGM��ͨ���л�������Χ������
 *
 * @par ����:
 * ���غ���������MSGM��ͨ���л�������Χ��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157ƽ̨��</li>
 * <li>�û���֤ʵ����MSGM������û���ص���</li>
 * <li>�ýӿڻ�Ա��˵�MSGQ��MSGM���������³�ʼ����</li>
 * <li>�û���֤������ȵ��������ڱ��ӿڱ�������Ϻ���ִ�С�</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * </ul>
 *
 * @param uwGMsgmBufStart    [IN] ����#UINT32��ȫ��MSGM��ͨ���л�������ʼ��ַ��
 * @param uwGMsgmBufLen      [IN] ����#UINT32��ȫ��MSGM��ͨ���л��������ȡ�
 *
 * @retval #OS_ERRNO_MSGM_CFG_ADDR_OR_LEN_NOT_ALIGN  0x02002b3f����������MSGM��ͨ���л�������Χʱ�����MSGM������ʼ��ַ�򳤶ȷ�4�ֽڶ��롣
 * @retval #OS_ERRNO_MSGM_CFG_START_ADDR_INVALID     0x02002b40����������MSGM��ͨ���л�������Χʱ�����MSGM������ʼ��ַ�Ƿ���
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_LEN_INVALID      0x02002b41����������MSGM��ͨ���л�������Χʱ�����MSGM���г��ȷǷ���
 * @retval #OS_ERRNO_MSGM_CFG_QUEUE_REGION_INVALID   0x02002b42����������MSGM��ͨ���л�������Χʱ�����MSGM������ʼ��ַ�ͳ��Ⱦ���������Ƿ���
 * @retval #OS_ERRNO_MSGM_INIT_MSGQ_NORESP           0x02002b01�������Ϣ������ʼ�������У�MSGMͨ������Ӧ�����ߺ˽���״̬Ϊ��ɣ����ж����Ƿ������߹�����
 * @retval #SRE_OK                                   0x00000000�����óɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmBufRecfg(UINT32 uwGMsgmBufStart, UINT32 uwGMsgmBufLen);

#endif

#if ((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ��������ж�֪ͨ����ע��ӿڡ�
 *
 * @par ����:
 * �ýӿ���ͬ�����Ŀ��˽���ע�ᣬ������OS���յ�ͬ���ж�֪ͨ�����ע�ṳ��֪ͨ�û���
 * @attention
 * <ul>
 * <li>������SD6182��SD6157ƽ̨��</li>
 * <li>ÿ������handle������ע�ᣬ�����һ��Ϊ׼��</li>
 * <li>���еĶ��й���һ���жϺš�����ͬһ���ˣ�Ҫ��uwIntHum��usMode����������ÿ�ε��ù����б��뱣��һ�¡�</li>
 * </ul>
 *
 * @param hQueue        [IN] ����#QUE_HANDLE_T��ͬ����Ϣ����handle��
 * @param uwIntNum      [IN] UINT32���жϺ�, ��Ч��ΧΪ[19, 26]��
 * @param usMode        [IN] HWI_MODE_T���ж�ģʽ����ռ������͡�
 * @param pfnHook       [IN] SRE_MSGM_SYN_REV_HOOK�����Ӻ���ָ�룬����Ϊ�ա�
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID       0x02002b2f��handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_RECV_IRQ_INVALID     0x02002b38���жϺ���Ч��
 * @retval #OS_ERROR_MSGM_SYN_RECV_HOOK_NULL       0x02002b3e��ע�ṳ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SYN_IRQ_NO_MEMORY        0x02002b47�������ڴ�ʧ�ܡ�
 * @retval #SRE_OK                                 0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmSynRevHookReg(QUE_HANDLE_T hQueue, UINT32 uwIntNum, HWI_MODE_T usMode, SRE_MSGM_SYN_REV_HOOK pfnHook);

/**
 * @ingroup SRE_msgm
 * @brief ��ͨ��Ϣ������������ýӿڡ�
 *
 * @par ����:
 * �����û�����Ĳ���������ָ����MSGM��ͨ��Ϣ�������������ʹ��������湦�ܡ�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157ƽ̨��</li>
 * <li>����ظ����ã������һ��Ϊ׼�� ֮ǰ��������ݣ����µ�������Ч�󣬽��������</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * <li>OS��LMSGM������������ڴ��Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * </ul>
 *
 * @param uwMsgmID      [IN] UINT32��MSGM ID����ЧֵΪSRE_GLOBAL_MSGM��SRE_LOCAL_MSGM(SRE_LOCAL_MSGMֻ��SD6182)��
 * @param pBufAddr      [IN] VOID *���������׵�ַ��Ҫ��ΪGLOBAL��д��ַ�������׵�ַ16�ֽڶ��롣
 * @param uwBufSize     [IN] UINT32�����ֽ�Ϊ��λ�Ļ��������ȡ�����Ҫ��16�ֽڶ��롣
 *
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_ILLEGAL       0x02002b48���������׵�ַΪNULL, ���߲���Global��ַ��
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_SIZE_ILLEGAL       0x02002b49����������С��Ч��
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_NOT_ALIGN     0x02002b4a���������׵�ַ�򳤶�û��16�ֽڶ��롣
 * @retval #OS_ERRNO_MSGM_NOR_OV_MSGM_ID_ILLEGAL           0x02002b4b��MSGM ID��Ч��
 * @retval #SRE_OK                                         0x00000000�����óɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_NorQueOvBufAddrCfg(UINT32 uwMsgmID, VOID * pBufAddr, UINT32 uwBufSize);

#else
/**
 * @ingroup SRE_msgm
 * @brief MSGMͨ����ӳ���ϵ���ú�Vmid���ýӿڡ�
 *
 * @par ����:
 * 1������ͨ��Ϣ���С�������Ϣ���к�ͬ����Ϣ����ӳ�䵽��Ӧ��ͨ���顣
 * 2������ͨ�����VMID��
 * @attention
 * <ul>
 * <li>������SD6183ƽ̨��</li>
 * </ul>
 *
 * @param uwChgId       [IN] ����#UINT32��ͨ����ID��ȡֵ��Χ[0,3]��
 * @param pstChgMapInfo [IN] ����#MSGM_CHG_MAP_S *��ͨ����ӳ�����ñ�
 * @param uwChgVmid     [IN] ����#UINT32��ͨ����Vmidֵ��ȡֵ��Χ[0,7]��
 *
 * @retval #OS_ERRNO_MSGM_CHG_IDX_ILLEGAL           0x02002b4f������ͨ����VMIDʱ������ı��ֵ��Ч��
 * @retval #OS_ERRNO_MSGM_VMID_VALUE_ILLEGAL        0x02002b4e������VMIDʱ�������VMIDֵ��Ч��
 * @retval #OS_ERRNO_MSGM_MAP_INFO_ILLEGAL          0x02002b55�������ͨ����ӳ�����ñ�Ƿ���
 * @retval #SRE_OK                                  0x00000000�����سɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_MsgmChgCfg(UINT32 uwChgId, MSGM_CHG_MAP_S *pstChgMapInfo, UINT32 uwChgVmid);

/**
 * @ingroup SRE_msgm
 * @brief MSGMͨ��VMID���ýӿڡ�
 *
 * @par ����:
 * ������ͨ��Ϣ���С�������Ϣ���С�ͬ����Ϣ���е�VMID��
 * @attention
 * <ul>
 * <li>������SD6183ƽ̨��</li>
 * </ul>
 *
 * @param enQueueType    [IN] ����#MSGM_QUEUE_TYPE_E���������ͣ�ȡֵ��Χ[0,2]��
 * @param uwChId         [IN] ����#UINT32��ͨ�����(enQueueTypeΪ��ͨ��Ϣ����:Ӳ�̱߳��[0,33]��������Ϣ����:�����������[0,7]��ͬ����Ϣ����:ͬ����������[0,31])��
 * @param uwChVmidBitmap [IN] ����#UINT32��Vmidֵ(8λbit map)��
 *
 * @retval #OS_ERRNO_MSGM_QUEUE_TYPE_ILLEGAL        0x02002b53������Ķ���������Ч��
 * @retval #OS_ERRNO_MSGM_VMID_VALUE_ILLEGAL        0x02002b4e������VMIDʱ�������VMIDֵ��Ч��
 * @retval #OS_ERRNO_MSGM_NOR_CORE_IDX_ILLEGAL      0x02002b50��������ͨ��Ϣ����VMIDʱ������ı��ֵ��Ч��
 * @retval #OS_ERRNO_MSGM_SH_IDX_ILLEGAL            0x02002b51�����ù��������VMIDʱ������ı��ֵ��Ч��
 * @retval #OS_ERRNO_MSGM_SYNC_IDX_ILLEGAL          0x02002b52������ͬ��������VMIDʱ������ı��ֵ��Ч��
 * @retval #SRE_OK                                  0x00000000�����سɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_MsgmChVmidSet(MSGM_QUEUE_TYPE_E enQueueType, UINT32 uwChId, UINT32 uwChVmidBitmap);

/**
 * @ingroup SRE_msgm
 * @brief ��ͨ��Ϣ������������ýӿڡ�
 *
 * @par ����:
 * �����û�����Ĳ���������ָ����MSGM��ͨ��Ϣ�������������ʹ��������湦�ܡ�
 * @attention
 * <ul>
 * <li>������SD6183��</li>
 * <li>����ظ����ã������һ��Ϊ׼��֮ǰ��������ݣ����µ�������Ч�󣬽��������</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * <li>OS��LMSGM������������ڴ��Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * </ul>
 *
 * @param uwMsgmID      [IN] UINT32��MSGM ID����ЧֵΪSRE_GLOBAL_MSGM��SRE_LOCAL_MSGM��
 * @param uwChgId       [IN] UINT32��ͨ����ID����Чֵ��ΧΪ[0,3]��
 * @param pBufAddr      [IN] VOID *���������׵�ַ��Ҫ��Ϊ��д���ַ�������׵�ַ16�ֽڶ��롣�û���֤ΪGLOBAL��ַ��
 * @param uwBufSize     [IN] UINT32�����ֽ�Ϊ��λ�Ļ��������ȡ�����Ҫ��16�ֽڶ��롣
 *
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR                       0x02001239�����ַתʵ��ַʧ�ܡ�
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_SIZE_ILLEGAL       0x02002b49����������С��Ч��
 * @retval #OS_ERRNO_MSGM_NOR_OV_BUFFER_ADDR_NOT_ALIGN     0x02002b4a���������׵�ַ�򳤶�û��16�ֽڶ��롣
 * @retval #OS_ERRNO_MSGM_NOR_OV_MSGM_ID_ILLEGAL           0x02002b4b��MSGM ID��Ч��
 * @retval #SRE_OK                                         0x00000000�����óɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see ��
 */
extern UINT32 SRE_NorQueOvBufAddrCfg(UINT32 uwMsgmID, UINT32 uwChgId, VOID * pBufAddr, UINT32 uwBufSize);
#endif
#endif

/**
 * @ingroup SRE_msgm
 * @brief Qport��Ϣ���ӵ�ע�ắ����
 *
 * @par ����:
 * ���ñ����û�ʹ��0��QPORTͨ�Ŵ���Ĺ��Ӻ�����
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�ýӿ�ֻ���OSռ�õ�0��QPORTʹ�ã�����QPORT�������ж�ģʽ�£��ù������ж��н��е��ã�����ע��ִ��ʱ�䲻�ɹ�����</li>
 * <li>������Ĺ���Ϊ��ʱ����ʾȡ�����û����ӣ���ʱ���ؽ��Ϊ�ɹ���</li>
 * <li>��ε��������һ��Ϊ׼��</li>
 * </ul>
 *
 * @param uwTag      [IN] ����#UINT32��Qport��Ϣ��ʶTag��ȡֵ��Χ��1~7(ҵ���Զ�����Ϣ); OS��Ϣʹ�õ�TagΪ0��
 * @param pfnHook    [IN] ����#SRE_QPORT_HOOK���ص�������
 *
 * @retval #OS_ERRNO_MSGM_QHOOK_TAG_INVALID      0x02002b08��ע��ʧ�ܣ�uwTag���Ϸ���
 * @retval #SRE_OK                               0x00000000��ע��ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_QportHookSet(UINT32 uwTag, SRE_QPORT_HOOK  pfnHook);

/**
 * @ingroup SRE_msgm
 * @brief ��Ϣ��ڵ�ַ��ȡ�����ӿڡ�
 *
 * @par ����:
 * ��ȡĿ�ĺ�ָ�����е���Ϣ��ڵ�ַ��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>ע��OSʹ����0��QPORT��0�Ŷ��У�0��QPORTΪOS��������Ϊ�жϷ�ʽ�����û�����ͨ���жϷ�ʽ����0��QPORT��������Ϣ(����ʱͨ���û��Լ�ע��Ĺ��Ӻ���ʵ����Ϣ���մ���)��</li>
 * </ul>
 *
 * @param uwDstCoreID    [IN] ����#UINT32����Ϣ���͵�ָ����Ŀ��ˡ�
 * @param uwQportID      [IN] ����#UINT32��ָ����qport id,ȡֵ��Χ��dsp:[0,1];cpu:[0,1];haccc:[0,2]��
 * @param uwQueIdx       [IN] ����#UINT32��ָ���Ķ��У�ȡֵ��Χ��0��1��
 * @param pQportAddr     [OUT] ����#VOID *�����ص���ϢQport������ڵ�ַ��
 *
 * @retval #OS_ERRNO_MSGM_SEND_ADDR_NULL         0x02002b09����ȡ��ַʧ�ܣ�����Qport������ڵ�ַΪ�ա�
 * @retval #OS_ERRNO_MSGM_SEND_DSTCORE_INVALID   0x02002b0f����ȡ��ַʧ�ܣ�Ŀ�ĺ˷Ƿ���
 * @retval #OS_ERRNO_MSGM_SEND_PORTID_INVALID    0x02002b10����ȡ��ַʧ�ܣ�qport�Ƿ���
 * @retval #OS_ERRNO_MSGM_SEND_QUEUEID_INVALID   0x02002b11����ȡ��ַʧ�ܣ�queue id�Ƿ���
 * @retval #SRE_OK                               0x00000000����ȡ��ַ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_QportAddrGet(UINT32 uwDstCoreID, UINT32 uwQportID, UINT32 uwQueIdx, VOID *pQportAddr);

/**
 * @ingroup SRE_msgm
 * @brief Qport��Ϣ�ķ��ͺ�����
 *
 * @par ����:
 * ֱ��ʹ��Ӳ����Qport������Ϣ��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>ע��OSʹ����0��QPORT��0�Ŷ��У�0��QPORTΪOS��������Ϊ�жϷ�ʽ�����û�����ͨ���жϷ�ʽ����0��QPORT��������Ϣ(����ʱͨ���û��Լ�ע��Ĺ��Ӻ���ʵ����Ϣ���մ���)��</li>
 * <li>auwData[3]�ĵ�3bitΪtag��1~7(ҵ���Զ�����Ϣ); OS��Ϣʹ�õ�TagΪ0��</li>
 * <li>�û���֤���͵��ֽڵ�ַ128bit���롣</li>
 * <li>OS��Ŀ�ĺ��Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * </ul>
 *
 * @param uwDstCoreID    [IN] ����#UINT32����Ϣ���͵�ָ����Ŀ��ˡ�
 * @param uwQportID      [IN] ����#UINT32��ָ����qport id,ȡֵ��Χ��dsp:[0,1];cpu:[0,1];haccc:[0,2]��
 * @param uwQueIdx       [IN] ����#UINT32��ָ���Ķ��У�ȡֵ��Χ��0��1��
 * @param auwData        [IN] ����#UINT32*�������͵���Ϣ���� ������Ϊ16�ֽڡ�
 *
 * @retval #OS_ERRNO_MSGM_SEND_DSTCORE_INVALID      0x02002b0f������ʧ�ܣ�Ŀ�ĺ˷Ƿ���
 * @retval #OS_ERRNO_MSGM_SEND_PORTID_INVALID       0x02002b10������ʧ�ܣ�qport�Ƿ���
 * @retval #OS_ERRNO_MSGM_SEND_QUEUEID_INVALID      0x02002b11������ʧ�ܣ�queue id�Ƿ���
 * @retval #OS_ERROR_MSGM_QPORT_SEND_DATA_NULL      0x02002b0a������ʧ�ܣ�����ָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_QPORT_SEND_DATA_INVALID   0x02002b07������ʧ�ܣ�����������Ч��
 * @retval #SRE_OK                                  0x00000000�����ͳɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_QportSend(UINT32 uwDstCoreID, UINT32 uwQportID, UINT32 uwQueIdx, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief Qport��Ϣ�Ľ��պ�����
 *
 * @par ����:
 * ���ձ���ָ��Qport����Ϣ��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>ע��2��QPORTֻ��������HACCC�ˡ�</li>
 * <li>ע��OSʹ����0��QPORT��0�Ŷ��У�0��QPORTΪOS��������Ϊ�жϷ�ʽ�����û�����ͨ���жϷ�ʽ����0��QPORT��������Ϣ(����ʱͨ���û��Լ�ע��Ĺ��Ӻ���ʵ����Ϣ���մ���)��</li>
 * <li>�û���ʹ��PORT0 1�Ŷ���ʱ��OS�Ѿ�������HPQ�жϲ�ע���˴��������û�ֻ��ͨ���Լ�ע�ṳ�Ӻ���(SRE_QportHookSet��ʵ��)�����ܴ�����Ϣ�������ַ�ʽ��ֱ��ʹ��SRE_QportRecv�ӿ������OS��ͻ ����Ҫʹ�ò�ѯ��ʽ������ȥʹ�ܸ��жϡ�</li>
 * <li>auwData[3]�ĵ�3bitΪtag��1~7(ҵ���Զ�����Ϣ); OS��Ϣʹ�õ�TagΪ0��</li>
 * <li>���û���֤128bit����������ݡ�</li>
 * </ul>
 *
 * @param uwQportID      [IN] ����#UINT32��ָ����qport,ȡֵ��Χ��dsp:[0,1];cpu:[0,1];haccc:[0,2]��
 * @param auwData        [IN] ����#UINT32*����������Ϣbuffer�׵�ַ ��buffer����Ϊ16�ֽڡ�
 *
 * @retval #OS_ERRNO_MSGM_RECV_QID_INVALID      0x02002b0e������ʧ�ܣ�qport�Ƿ���
 * @retval #OS_ERRNO_MSGM_RECV_QORT_EMPTY       0x02002b0d������ʧ�ܣ�ָ����qport������Ϣ��
 * @retval #OS_ERROR_MSGM_QPORT_RECV_SER        0x02002b0b, ���������в��ɾ���2bit ECC����
 * @retval #OS_ERROR_MSGM_QPORT_RECV_DATA_NULL  0x02002b0c������ʧ�ܣ����������ָ��Ϊ�ա�
 * @retval #SRE_OK                              0x00000000�����ճɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_QportRecv(UINT32 uwQportID, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief ������Ϣ��װ������
 *
 * @par ����:
 * ��128bit�����ݰ���OS��Ϣ��ʽ��װ,��Ҫ������HACCC����DSP&CPU����Ϣͨ��ʱ����Ҫ����OS��Ϣ��ʽ��װ��
 * @attention:
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>����Qport����Ϣ��auwData[0~2]����Ϣ����, auwData[3]Ϊ���ɵ�MSG header��</li>
 * <li>��Ϣ���Բ�������Ϣ�壬�����Ͳ�����Ϣ����Ϣ����MSG_HANDLE_T���ΪOS_MSG_NO_PAYLOAD��</li>
 * <li>ע����ʹ�øýӿڴ�����װ������Ϣ���û�������ϢҪ����OS��Ϣ���͹淶������ɼ�OS��Ϣģ����ֲᡣ</li>
 * <li>ע�ⴴ����װ������Ϣ�ĵ�ַauwData����Ϊ�ա�</li>
 * <li>ͨ��MSGM���͵���Ϣֻ֧�ַ��͵�Ŀ�Ķ��̵߳�0����Ϣ���С�</li>
 * </ul>
 *
 * @param uwMsgHandle    [IN]  ����#UINT32����Ϣ��������Դ����Ϣ�崴���ɹ�����ճɹ������ֵ��
 * @param uwMsgID        [IN]  ����#UINT32����ϢID�����Ա�ʶ����Ϣ��Ψһ�ԡ�
 * @param uwDstPID       [IN]  ����#UINT32�������ߵ��߳�ID��
 * @param uwDstQID       [IN]  ����#UINT32�����������ָ�����У�ֻ��Ϊ0�Ŷ��У���������Ϊ���жϣ���������Ч��
 * @param auwData        [OUT] ����#UINT32*����������Ϣbuffer�׵�ַ��buffer����Ϊ16�ֽڡ�
 *
 * @retval #OS_ERRNO_MSGM_PID_INVALID                0x02002b13��Ŀ���߳�PID�Ƿ���
 * @retval #OS_ERRNO_MSGM_MSG_POINT_NULL             0x02002b15, ��������Ϣ���ݵ�ָ�벻��Ϊ�ա�
 * @retval #OS_ERRNO_MSGM_MSG_CREATE_HANDLE_INVALID  0x02002b21, �������Ϣ�����Ƿ����������ɾ������ָ��ΪNULL����������Ϣ�����ڱ�ʹ�á�
 * @retval #SRE_OK                                   0x00000000����Ϣ��װ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_QportMsgCreate(MSG_HANDLE_T uwMsgHandle, UINT32 uwMsgID, MSG_PID_T uwDstPID, UINT32 uwDstQID, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief ����MSGM�˼���Ϣ���͸���(TRACE)�������Խӿڡ�
 *
 * @par ����:
 * �����û������msgm������msgmID���������ռ�ָ��pTraceBufAddr��uwTraceBufSize��С�Ļ�������auwMask[4]��С�����롢auwMatch[4]��С��ƥ���� �����к˼���Ϣ���͸��٣�TRACE)�������Ե����á�
 * ���롢ƥ���롢��Ϣֵ���߼���ϵΪ�� ��Ϣֵ(auwData) | ����ֵ(auwMask) = ƥ����ֵ(auwMatch)������auwMask��ӦλΪ1����£�auwMatch��Ӧλһ������Ϊ1��auwData��Ӧλ���ܹ��ˣ���auwMaskΪ0����£�auwData��Ӧλ = auwMatch��Ӧλ���ܹ��ˡ�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>��ֹ��ʹ������½������á�</li>
 * <li>������ظ����ã������һ������Ϊ׼��</li>
 * <li>�û�����Ļ�������ַ����Ϊ�����ַ��</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * <li>OS��LMSGM�ͻ����ַ�ռ��Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * <li>SD6183ƽ̨���û���֤��COMM VMIDȨ�޵��øýӿڡ�</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32��0--��dsp&cpu�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�1--��haccc�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�����ֵ�Ƿ���
 * @param pTraceBufAddr  [IN] VOID *��TRACE BUFFER���׵�ַ(SD6183ƽ̨Ϊ���ַ)��ע���豣֤Ϊ256bit�����GLOBAL��ַ��
 * @param uwTraceBufSize [IN] UINT32�� TRACE BUFFER�ĳ��ȣ�ע���豣֤Ϊ256bit����������
 * @param auwMask        [IN] UINT32 *��128bit����Ϣ��������ֵ��
 * @param auwMatch       [IN] UINT32 *��128bit����Ϣƥ��ֵ��
 *
 * @retval #OS_ERRNO_MMU_VA2PA_ERROR             0x02001239�����ַתʵ��ַʧ�ܡ�
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16��ָ����MSGM ID�Ƿ���
 * @retval #OS_ERRNO_MSGM_TRACE_BUFFER_NULL      0x02002b19�������MSGM TRACE��������ַΪNULL��
 * @retval #OS_ERRNO_MSGM_TRACE_BUFFER_NOT_ALIGN 0x02002b17�������TRACE��������ʼ��ַδ256bit���롣
 * @retval #OS_ERRNO_MSGM_TRACE_SIZE_NOT_ALIGN   0x02002b18�������TRACE��������Сδ256bit���롣
 * @retval #OS_ERRNO_MSGM_TRACE_ENABLE           0x02002b1b��MSGM��TRACE������ʹ�ܣ���ʱ��ֹ�û��������á�
 * @retval #OS_ERRNO_MSGM_TRACE_SIZE_ILLEGAL     0x02002b1c�������TRACE��������СΪ0�򻺳�����С̫���������
 * @retval #OS_ERRNO_MSGM_TRACE_FILTERBIT_NULL   0x02002b1d�������MSGM��TRACEƥ����������׵�ַΪNULL��
 * @retval #SRE_OK                               0x00000000�����˹��ܵ��������óɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_MsgTraceCfg(UINT32 uwMsgmID, VOID *pTraceBufAddr, UINT32 uwTraceBufSize, UINT32 auwMask[4], UINT32 auwMatch[4]);

/**
 * @ingroup SRE_msgm
 * @brief ʹ��MSGM�˼���Ϣ���͸���(TRACE)���ܽӿڡ�
 *
 * @par ����:
 * �����û������msgm������msgmID����MSGM�˼���Ϣ���͸���(TRACE)���ܽ���ʹ�ܡ�
 * ��ʹ��MSGM�˼���Ϣ���͸���(TRACE)����ʱ��TRACE BUFFER�ռ䵱ǰ��Ϣָ�뽫������գ��ظ�ʹ��ʱ���������ա�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>������ظ�ʹ�ܣ������سɹ���</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * <li>OS��LMSGM�Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * <li>SD6183ƽ̨���û���֤��COMM VMIDȨ�޵��øýӿڡ�</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32��0--��dsp&cpu�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�1--��haccc�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�����ֵ�Ƿ���
 *
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16��ָ����MSGM ID�Ƿ���
 * @retval #OS_ERRNO_MSGM_TRACE_NOT_CONFIG       0x02002b1a��MSGM��TRACE��������ʼ��ַδ�������á�
 * @retval #SRE_OK                               0x00000000��ʹ��MSGM�˼���Ϣ���͸���(TRACE)���ܳɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MsgTraceDisable
 */
extern UINT32 SRE_MsgTraceEnable(UINT32 uwMsgmID);

/**
 * @ingroup SRE_msgm
 * @brief ȥʹ��MSGM�˼���Ϣ���͸���(TRACE)���ܽӿڡ�
 *
 * @par ����:
 * �����û������msgm������msgmID����MSGM�˼���Ϣ���͸���(TRACE)���ܽ���ȥʹ�ܡ�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>������ظ�ȥʹ�ܣ������سɹ���</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * <li>OS��LMSGM�Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * <li>SD6183ƽ̨���û���֤��COMM VMIDȨ�޵��øýӿڡ�</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32��0--��dsp&cpu�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�1--��haccc�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�����ֵ�Ƿ���
 *
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16��ָ����MSGM ID�Ƿ���
 * @retval #SRE_OK                               0x00000000��ȥʹ��MSGM�˼���Ϣ���͸���(TRACE)���ܳɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_MsgTraceEnable
 */
extern UINT32 SRE_MsgTraceDisable(UINT32 uwMsgmID);

/**
 * @ingroup SRE_msgm
 * @brief ��ȡTRACE BUFFER�ռ䵱ǰ��Ϣָ��ӿڡ�
 *
 * @par ����:
 * �����û������msgm������msgmID����ȡ�ռ䵱ǰ��Ϣָ�룬ͨ��ָ�����puwTracePtr���з��أ���ȡ�����Ǹ��׵�ַƫ������
 * �˽ӿڷ��ص��Ǵ�д�����һ����Ϣƫ�Ƶ�ַ��ʹ��ʱ���������׵�ַ + ��ǰ��Ϣָ�� = ��һ����д�����Ϣ��ַ��
 * ��ʹ��MSGM�˼���Ϣ���͸���(TRACE)����ʱ��TRACE BUFFER�ռ䵱ǰ��Ϣָ�뽫������ա�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>δ���û���������£���������ô˽ӿڣ�����ָ��Ϊ0XFFFFFFFF��</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * <li>OS��LMSGM�Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * </ul>
 *
 * @param uwMsgmID       [IN] UINT32��0--��dsp&cpu�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�1--��haccc�˷�����Ϣʱʹ�õ�msgm��Ϣ���У�����ֵ�Ƿ���
 * @param puwTracePtr    [OUT] UINT32 *�����ص�TRACE BUFFER�ռ䵱ǰ��Ϣָ�룬����ִ��ʧ���Ҵ���ָ�벻ΪNULLʱ��ָ�뷵��0xFFFFFFFF��
 *
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL             0x02002b16��ָ����MSGM ID�Ƿ���
 * @retval #OS_ERRNO_MSGM_TRACE_PTR_NULL         0x02002b1e���û������ȡ��ǰ��Ϣ��ָ��ΪNULL��
 * @retval #OS_ERRNO_MSGM_TRACE_NOT_CONFIG       0x02002b1a��MSGM��TRACE��������ʼ��ַδ�������á�
 * @retval #SRE_OK                               0x00000000����ȡTRACE BUFFER�ռ䵱ǰ��Ϣָ��ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_MsgTracePtrGet(UINT32 uwMsgmID, UINT32 *puwTracePtr);

/**
 * @ingroup SRE_msgm
 * @brief �򿪹�����Ϣ���нӿڡ�
 *
 * @par ����:
 * �����û�����Ķ���ID��FIFO��������ʼ������ָ�����С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�û���Ҫ���б�֤��ͬ���е�FIFO�����޽��档</li>
 * <li>����ö���֮ǰ�Ѿ��򿪣��ö��н�����λ�����´򿪡�</li>
 * <li>�ýӿ��ڲ��޺˼������������ڿ��ܳ��ֶ��ͬʱ�򿪻�ر�ͬһ���е����Σ��û�������������������</li>
 * </ul>
 *
 * @param uwQueID       [IN] UINT32����������ID����Чֵ��ΧSD6182/SD6157Ϊ[0, 31],SD6183Ϊ[0, 63]��
 * @param uwFifoStart   [IN] UINT32������FIFO��ʼ�α�ֵ����Чֵ��ΧSD6182/SD6157Ϊ[0, 1023],SD6183Ϊ[0, 2047]��
 * @param uwFifoDepth   [IN] UINT32������FIFO��ȣ���Ч��ΧSD6182/SD6157Ϊ[1, 1024],SD6183Ϊ[1, 2048]����uwFifoStart + uwFifoDepthSD6182/SD6157���ܳ���1024,SD6183���ܳ���2048��
 * @param phQueue       [OUT] QUE_HANDLE_T *�����򿪳ɹ������ض���handle��
 *
 * @retval #OS_ERROR_MSGM_SH_ID_INVALID          0x02002b24��ID�Ƿ���
 * @retval #OS_ERROR_MSGM_SH_HANDLE_NULL         0x02002b25��handleָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SH_FIFO_OVERRUN        0x02002b26��FIFO�������ô���
 * @retval #SRE_OK                               0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueClose
 */
extern UINT32 SRE_MsgmShQueOpen(UINT32 uwQueID, UINT32 uwFifoStart, UINT32 uwFifoDepth, QUE_HANDLE_T * phQueue);

/**
 * @ingroup SRE_msgm
 * @brief �رչ�����Ϣ���нӿڡ�
 *
 * @par ����:
 * �����û������handle���رն�Ӧ�Ĺ�����Ϣ���С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�����еĲ������ݽ��ᱻ������</li>
 * <li>�����ظ��رչ�����У�����SRE_OK��</li>
 * <li>�ýӿ��ڲ��޺˼������������ڿ��ܳ��ֶ��ͬʱ�򿪻�ر�ͬһ���е����Σ��û�������������������</li>
 * <li>SD6183ƽ̨���û���֤��ͨ���� VMIDȨ�޵��øýӿڡ�</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T��������Ϣ����handle��
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23��handle�Ƿ���
 * @retval #SRE_OK                               0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueOpen
 */
extern UINT32 SRE_MsgmShQueClose(QUE_HANDLE_T hQueue);

/**
 * @ingroup SRE_msgm
 * @brief ������Ϣ������Ϣ���ͽӿڡ�
 *
 * @par ����:
 * ��handle��Ӧ�Ķ��з�����ϢauwData��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>���û���֤128bit���뷢�����ݡ�</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T��������Ϣ����handle��
 * @param auwData      [IN] UINT32*�����͵���Ϣ�����ݡ�
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID       0x02002b23��handle�Ƿ���
 * @retval #OS_ERROR_MSGM_SH_INVALID_DATA         0x02002b29�����ݷǷ���
 * @retval #OS_ERROR_MSGM_SH_NOT_OPENED           0x02002b27��������Ϣ����δ�򿪡�
 * @retval #OS_ERROR_MSGM_SH_SEND_DATA_PTR_NULL   0x02002b4c����Ч����Ϣ���ַ��
 * @retval #SRE_OK                                0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueRecv
 */
extern UINT32 SRE_MsgmShQueSend(QUE_HANDLE_T hQueue, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief ������Ϣ������Ϣ���սӿڡ�
 *
 * @par ����:
 *  ��handle��Ӧ�Ĺ�����Ϣ���ж�ȡһ����Ϣ��������auwData�ڴ��С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>���û���֤128bit����������ݡ�</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T��������Ϣ����handle��
 * @param auwData      [OUT] UINT32*���������ݱ����ַ
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23��handle�Ƿ���
 * @retval #OS_ERROR_MSGM_SH_NOT_OPENED          0x02002b27��������Ϣ����δ�򿪡�
 * @retval #OS_ERROR_MSGM_SH_RECV_EMPTY          0x02002b2a��������Ϣ����Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SH_RECV_SER            0x02002b2b�������в��ɾ�ECC����
 * @retval #OS_ERROR_MSGM_SH_RECV_DATA_PTR_NULL  0x02002b30����Ч����Ϣ���ַ��
 * @retval #SRE_OK                               0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmShQueSend
 */
extern UINT32 SRE_MsgmShQueRecv(QUE_HANDLE_T hQueue, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief ������Ϣ������Ϣ���������ѯ�ӿڡ�
 *
 * @par ����:
 * ��ѯhandle��Ӧ�Ĺ�����Ϣ���еĻ�����Ϣ�����������浽puwMsgNum��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * </ul>
 *
 * @param hQueue       [IN] QUE_HANDLE_T��������Ϣ����handle��
 * @param puwMsgNum    [OUT] UINT32 *��������Ϣ����
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23��handle�Ƿ���
 * @retval #OS_ERROR_MSGM_SH_MSGNUM_NULL         0x02002b28����Ϣ����ָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SH_NOT_OPENED          0x02002b27��������Ϣ����δ�򿪡�
 * @retval #SRE_OK                               0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmShQueStatics(QUE_HANDLE_T hQueue, UINT32 * puwMsgNum);

/**
 * @ingroup SRE_msgm
 * @brief ������Ϣ������Ϣ��ڵ�ַ��ȡ�����ӿڡ�
 *
 * @par ����:
 * ��ȡָ��������Ϣ���е���Ϣ��ڵ�ַ��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * </ul>
 *
 * @param hQueue       [IN] ����#QUE_HANDLE_T��������Ϣ����handle��
 * @param pQueAddr     [OUT] ����#VOID *�����صĹ�����Ϣ������ڵ�ַ��
 *
 * @retval #OS_ERROR_MSGM_SH_HANDLE_INVALID      0x02002b23��handle�Ƿ���
 * @retval #OS_ERROR_MSGM_SH_ADDR_GET_NULL       0x02002b45����ַΪ�ա�
 * @retval #SRE_OK                               0x00000000����ȡ��ַ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmShQueAddrGet(QUE_HANDLE_T hQueue, VOID * pQueAddr);

#if (OS_OPTION_MSGM_SYN_PARA_RESET == YES)

/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ���в����������ýӿڡ�
 *
 * @par ����:
 * �����û�����Ķ���ID�����ò������������ò�������ָ�����С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�����ͬһ�����ж�β������裬�����һ��Ϊ׼��</li>
 * <li>���������ͬ���еĶ��н��в������裬��ôͬ������ֹͣ�����н����¸�λ�򿪡�</li>
 * <li>�ýӿ��ڲ��޺˼������������ڿ��ܳ��ֶ��ͬʱ�򿪡��رա�������ֹͣͬһ���е����Σ��û�������������������</li>
 * <li>��Ϣ֪ͨģʽʱ���û���֤��Ϣ֪ͨ��Ŀ�ĵ�ַΪ��Чȫ�ֵ�ַ��</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T��ͬ����Ϣ����handle��
 * @param pstSynQueAttr [IN] SRE_SYN_QUE_ATTR_S *���������ò�����
 *
 * @retval #OS_ERROR_MSGM_SYN_ID_INVALID          0x02002b2c, �������ID�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_ATTR_NULL           0x02002b2d�����ò���attrָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SYN_SYNNUM_INVALID      0x02002b32��ͬ��������Ч��
 * @retval #OS_ERROR_MSGM_SYN_LOAD_MODE_INVALID   0x02002b33��LOADģʽ��Ч��
 * @retval #OS_ERROR_MSGM_SYN_TOT_INVALID         0x02002b35����ʱʱ�䵵λ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_DST_CORE_INVALID    0x02002b34��Ŀ�����Ч��
 * @retval #OS_ERROR_MSGM_SYN_RECV_MODE_INVALID   0x02002b36��ͬ������ģʽ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_DES_ADDR_INVALID    0x02002b37����Ϣ����Ŀ���ַ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_MSG_INVALID         0x02002b3d����Ϣ����
 * @retval #OS_ERROR_MSGM_SYN_DATA_MODE_INVALID   0x02002b57�����÷�����Ϣ����ģʽ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_CMP_WORD_INVALID    0x02002b58������ƥ��wordֵ�Ƿ���
 * @retval #SRE_OK                                0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MsgmSynQueOpen
 */
extern UINT32 SRE_MsgmSynParaReset(QUE_HANDLE_T hQueue, SRE_SYN_QUE_ATTR_S * pstSynQueAttr);

#endif

#if (OS_OPTION_MSGM_SYN_STATE_GET == YES)

/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ����ʹ��״̬��ѯ�ӿڡ�
 *
 * @par ����:
 * ��ѯͬ����Ϣ����ʹ��״̬��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T��ͬ����Ϣ����handle��
 * @param puwState      [OUT] UINT32 *��ͬ����Ϣ���е�ʹ��״̬������1����ʹ��״̬��0����ȥʹ��״̬��
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID      0x02002b2f��handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_EN_STATE_NULL       0x02002b56������ʹ��״̬�ĵ�ַָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED          0x02002b31��ͬ����Ϣ����δ�򿪡�
 * @retval #SRE_OK                                0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R003C00
 * @see SRE_MsgmSynQueStatics
 */
extern UINT32 SRE_MsgmSynStateGet(QUE_HANDLE_T hQueue, UINT32* puwState);

#endif

/**
 * @ingroup SRE_msgm
 * @brief ��ͬ����Ϣ���нӿڡ�
 *
 * @par ����:
 * �����û�����Ķ���ID�����ò�������ʼ������ָ�����С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>ͬһ�������������δ򿪣������һ��Ϊ׼��</li>
 * <li>���������ͬ���еĶ��У���ôͬ������ֹͣ�����н����¸�λ�򿪡�</li>
 * <li>�ýӿ��ڲ��޺˼������������ڿ��ܳ��ֶ��ͬʱ�򿪡��رա�������ֹͣͬһ���е����Σ��û�������������������</li>
 * <li>��Ϣ֪ͨģʽʱ���û���֤��Ϣ֪ͨ��Ŀ�ĵ�ַΪ��Чȫ�ֵ�ַ��</li>
 * </ul>
 *
 * @param uwQueID       [IN] UINT32����������ID����Чֵ��ΧΪSD6182/SD6157:[0, 15]��SD6183:[0, 255]��
 * @param pstSynQueAttr [IN] SRE_SYN_QUE_ATTR_S *���������ò�����
 * @param phQueue       [OUT] QUE_HANDLE_T *�����򿪳ɹ������ض���handle��
 *
 * @retval #OS_ERROR_MSGM_SYN_ID_INVALID          0x02002b2c, �������ID�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_ATTR_NULL           0x02002b2d�����ò���attrָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_NULL         0x02002b2e��handle�ĵ�ַָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SYN_SYNNUM_INVALID      0x02002b32��ͬ��������Ч��
 * @retval #OS_ERROR_MSGM_SYN_LOAD_MODE_INVALID   0x02002b33��LOADģʽ��Ч��
 * @retval #OS_ERROR_MSGM_SYN_TOT_INVALID         0x02002b35����ʱʱ�䵵λ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_DST_CORE_INVALID    0x02002b34��Ŀ�����Ч��
 * @retval #OS_ERROR_MSGM_SYN_RECV_MODE_INVALID   0x02002b36��ͬ������ģʽ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_DES_ADDR_INVALID    0x02002b37����Ϣ����Ŀ���ַ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_MSG_INVALID         0x02002b3d����Ϣ����
 * @retval #OS_ERROR_MSGM_SYN_DATA_MODE_INVALID   0x02002b57�����÷�����Ϣ����ģʽ�Ƿ���
 * @retval #OS_ERROR_MSGM_SYN_CMP_WORD_INVALID    0x02002b58������ƥ��wordֵ�Ƿ���
 * @retval #SRE_OK                                0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueClose
 */
extern UINT32 SRE_MsgmSynQueOpen(UINT32 uwQueID, SRE_SYN_QUE_ATTR_S * pstSynQueAttr, QUE_HANDLE_T * phQueue);

/**
 * @ingroup SRE_msgm
 * @brief �ر�ͬ����Ϣ���нӿڡ�
 *
 * @par ����:
 * �ر�hQueue����Ӧ����Ϣ���С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�ظ��ر��Ѿ��رյ�ͬ����Ϣ���У�����SRE_OK��</li>
 * <li>�ýӿ��ڲ��޺˼������������ڿ��ܳ��ֶ��ͬʱ�򿪡��رա�������ֹͣͬһ���е����Σ��û�������������������</li>
 * <li>����Ĺر�ֻ�Ǽ򵥵ؽ���stop��������Ҫ�û���֤close���ٽ���start����������ͬ���Ĳ��� </li>
 * <li>SD6183ƽ̨���û���֤��ͨ���� VMIDȨ�޵��øýӿڡ�</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T��ͬ����Ϣ����handle��
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID     0x02002b2f�������handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED         0x02002b31��ͬ����Ϣ����δ�򿪡�
 * @retval #SRE_OK                               0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueOpen
 */
#define SRE_MsgmSynQueClose(hQueue)  SRE_MsgmSynQueStop(hQueue)

/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ���������ӿڡ�
 *
 * @par ����:
 * ����hQueue����Ӧ����Ϣ���С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�ýӿ��ڲ��޺˼������������ڿ��ܳ��ֶ��ͬʱ�򿪡��رա�������ֹͣͬһ���е����Σ��û�������������������</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T��ͬ����Ϣ����handle��
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID        0x02002b2f�������handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED            0x02002b31��ͬ����Ϣ����δ�򿪡�
 * @retval #SRE_OK                                  0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueStop
 */
extern UINT32 SRE_MsgmSynQueStart(QUE_HANDLE_T hQueue);

/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ����ֹͣ�ӿڡ�
 *
 * @par ����:
 * ֹͣhQueue����Ӧ����Ϣ���С�
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>�ýӿ��ڲ��޺˼������������ڿ��ܳ��ֶ��ͬʱ�򿪡��رա�������ֹͣͬһ���е����Σ��û�������������������</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T��ͬ����Ϣ����handle��
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID        0x02002b2f�������handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_NOT_OPENED            0x02002b31��ͬ����Ϣ����δ�򿪡�
 * @retval #SRE_OK                                  0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_MsgmSynQueStart
 */
extern UINT32 SRE_MsgmSynQueStop(QUE_HANDLE_T hQueue);

/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ������Ϣ���ͽӿڡ�
 *
 * @par ����:
 * ��hQueue��Ӧ�Ķ��з���ͬ����Ϣ��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T��ͬ����Ϣ����handle��
 * @param auwData       [IN] UINT32*��������Ϣ���ݡ�
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID        0x02002b2f��handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_NOT_GOING             0x02002b3c������ͬ�������С�
 * @retval #OS_ERROR_MSGM_SYN_MSG_PTR_NULL          0x02002b3b�����ݵ�ַΪ�ա�
 * @retval #SRE_OK                                  0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmSynQueSend(QUE_HANDLE_T hQueue, UINT32 auwData[4]);

/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ����ͳ�ƽӿڡ�
 *
 * @par ����:
 * ��ѯhQueue��Ӧ���е�ǰͳ�Ƽ�����
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * <li>��û�з���ͬ����Ϣ������ͬ����ɵ�����£�SD6182/SD6157ƽ̨���ص�ʣ����Ϣ����Ϊͬ����������SD6183ƽ̨���ص�Ϊ0��</li>
 * </ul>
 *
 * @param hQueue        [IN] QUE_HANDLE_T��ͬ����Ϣ����handle��
 * @param puwSynMsgCnt  [OUT] UINT32*��ʣ����Ϣ������
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID     0x02002b2f��handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_MSGCNT_NULL        0x02002b3a�����ص�ַָ��Ϊ�ա�
 * @retval #OS_ERROR_MSGM_SYN_NOT_GOING          0x02002b3c������ͬ�������С�
 * @retval #SRE_OK                               0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmSynQueStatics(QUE_HANDLE_T hQueue, UINT32 * puwSynMsgCnt);

/**
 * @ingroup SRE_msgm
 * @brief ͬ����Ϣ������Ϣ��ڵ�ַ��ȡ�����ӿڡ�
 *
 * @par ����:
 * ��ȡָ��ͬ����Ϣ���е���Ϣ��ڵ�ַ��
 * @attention
 * <ul>
 * <li>������SD6182��SD6157��SD6183ƽ̨��</li>
 * </ul>
 *
 * @param hQueue       [IN] ����#QUE_HANDLE_T��ͬ����Ϣ����handle��
 * @param pQueAddr     [OUT] ����#VOID *�����ص�ͬ����Ϣ������ڵ�ַ��
 *
 * @retval #OS_ERROR_MSGM_SYN_HANDLE_INVALID     0x02002b2f��handle��Ч��
 * @retval #OS_ERROR_MSGM_SYN_ADDR_GET_NULL      0x02002b46����ַΪ�ա�
 * @retval #SRE_OK                               0x00000000����ȡ��ַ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmSynQueAddrGet(QUE_HANDLE_T hQueue, VOID * pQueAddr);

#if ((OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HIDSP))
/**
 * @ingroup SRE_msgm
 * @brief MSGM DFX�쳣�ӹܳ�ʼ�����ýӿڡ�
 *
 * @par ����:
 * �ýӿڳ�ʼ��MSGM�����쳣��ؼĴ�����������ʹ�ܴ�����Ӳ�жϡ�
 * @attention
 * <ul>
 * <li>GMSGM��ʼ������GMSGM DFX�Ĵ�����ʼ�������Լ������жϴ�����LMSGM��ʼ��ֻ����LMSGM DFX�Ĵ�����ʼ�����á�</li>
 * <li>GMSGMֻ�ܳ�ʼ������һ�Σ�������SRE_AppInit��֮����á�</li>
 * <li>LMSGM������γ�ʼ�����ã���������GMSGM��ʼ��֮�����(������ܳ���δ�ӹ��ж�)�����û����б�֤��</li>
 * <li>�ýӿڲ���GICͨ�����ã�MSGM�����쳣�ӹܹ�����Ҫ��GIC��֮ͨ�������ʽ��Ч��</li>
 * <li>�ýӿ��ڲ���MSGM��Ӳ������û�к˼������������ڿ��ܳ��ֶ��ͬʱ���õĳ������û���֤���в�����</li>
 * <li>OS��LMSGM�Ƿ񱻵͹��Ĺضϲ����жϣ��û������б�֤��</li>
 * <li>�������غ˵��øýӿڡ�</li>
 * </ul>
 *
 * @param uwMsgmID      [IN] UINT32������ʼ����λ��MSGM����ЧֵΪSRE_GLOBAL_MSGM��SRE_LOCAL_MSGM(SRE_LOCAL_MSGMֻ��SD6182/SD6183��Ч)��
 *
 * @retval #OS_ERRNO_HWI_ALREADY_CREATED                 0x02001402��Ӳ�ж��ѱ���������Ӧ�ж��������ѱ������ж�ռ�á�
 * @retval #OS_ERRNO_HWI_MEMORY_ALLOC_FAILED             0x02001408��������жϽڵ�����˽�о�̬�ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_HWI_COMBINEHOOK_ALREADY_CREATED     0x02001409��������ж��Ѵ�������ͬ���жϴ�������
 * @retval #OS_ERRNO_MSGM_ID_ILLEGAL                     0x02002b16��ָ����MSGM ID�Ƿ���
 * @retval #SRE_OK                                       0x00000000����ȡ��ַ�ɹ���
 *
 * @par ����:
 * <ul><li>sre_msgm.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern UINT32 SRE_MsgmDfxInit(UINT32 uwMsgmID);
#endif
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_MSGM_H */



