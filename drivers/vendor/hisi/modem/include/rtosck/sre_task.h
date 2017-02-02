/**
 * @file sre_task.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ����������ģ��Ķ���ͷ�ļ��� \n
 */

 /**@defgroup SRE_task �����������
  *@ingroup SRE_kernel
 */

#ifndef _SRE_TASK_H
#define _SRE_TASK_H

#include "sre_base.h"
#include "sre_hook.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


/**
 * @ingroup SRE_task
 * ����������󳤶ȡ�
 *
 * ����������󳤶ȣ�������β��'\0'��
 */
#define OS_TSK_NAME_LEN                                     16

/**
 * @ingroup SRE_task
 * �������Ϣ�������ĸ�����
 *
 */
#define OS_TSK_MSGQ_MAX                                     8


/**
 * @ingroup SRE_task
 * ������ID��
 *
 * ����SRE_TaskYieldʱ��ʹ��OS_TSK_NULL_ID����OSѡ����������еĵ�һ������
 */
#define OS_TSK_NULL_ID                                      0xFFFFFFFF


/**
 * @ingroup SRE_task
 * Balong AX֧�ֵ����ȼ�Ϊ(0~63)������ƽ̨оƬ֧�ֵ����ȼ�(0~31)��OSϵͳIDLE�߳�ʹ��������ȼ�(63��31)���û�����ʹ�á�
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_00                                  0

/**
* @ingroup SRE_task
* ���õ��������ȼ��궨�塣
*
*/

#define OS_TSK_PRIORITY_01                                  1

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_02                                  2

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_03                                  3

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_04                                  4

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_05                                  5

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_06                                  6

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_07                                  7

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_08                                  8

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_09                                  9

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_10                                  10

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_11                                  11

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_12                                  12

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_13                                  13

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_14                                  14

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_15                                  15

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_16                                  16

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_17                                  17

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_18                                  18

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_19                                  19

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_20                                  20

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_21                                  21

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_22                                  22

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_23                                  23

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_24                                  24

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_25                                  25

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_26                                  26

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_27                                  27

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_28                                  28

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_29                                  29

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_30                                  30

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_31                                  31

/**
 * @ingroup SRE_task
 * Cortex-AX֧�ֵ����ȼ�Ϊ(0~63),�������ȼ���32~63��
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_32                                  32

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_33                                  33

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_34                                  34

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_35                                  35

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_36                                  36

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_37                                  37

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_38                                  38

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_39                                  39

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_40                                  40

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_41                                  41

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_42                                  42

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_43                                  43

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_44                                  44

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_45                                  45

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_46                                  46

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_47                                  47

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_48                                  48

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_49                                  49

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_50                                  50

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_51                                  51

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_52                                  52

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_53                                  53

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_54                                  54

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_55                                  55

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_56                                  56

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_57                                  57

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_58                                  58

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_59                                  59

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_60                                  60

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_61                                  61

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_62                                  62

/**
 * @ingroup SRE_task
 * ���õ��������ȼ��궨�塣
 *
 */
#define OS_TSK_PRIORITY_63                                  63


/**
 * @ingroup SRE_task
 * ��С����ջ��С��
 *
 * ��ָ��������ջ��С���ڴ�ֵ�����������Ĵ�С����16�ֽڶ��룩�����񽫴���ʧ�ܡ�
 * ����ֻ�ǰ�������������Ԥ����ջ�ռ䣬�������ʱ�������������Ҫ���û����б�֤�㹻������ջ�ռ�����, ��ȷ������½���ʹ��Ĭ������ջ��С���á�
 */
#define OS_TSK_MIN_STACK_SIZE                               (ALIGN(0x1D0, 16))


/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * ������ƿ�δ��ʹ�á�
 */
#define OS_TSK_UNUSED                                       0x0001

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * ���񱻹���
 */
#define OS_TSK_SUSPEND                                      0x0004

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * �����������ȴ��ź�������
 */
#define OS_TSK_PEND                                         0x0008

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * �����ڵȴ��ź��������¼��ı�־��
 */
#define OS_TSK_TIMEOUT                                      0x0010

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * ������ʱ��
 */
#define OS_TSK_DELAY                                        0x0020

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * �����Ѿ������Ѽ���������С�
 */
#define OS_TSK_READY                                        0x0040

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * ���������У����ھ������С�
 */
#define OS_TSK_RUNNING                                      0x0080

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * �����������ȴ������ź�������
 */
#define OS_TSK_FSEM_PEND                                    0x0100
/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * �����������ȴ���Ϣ����
 */

#define OS_TSK_MSG_PEND                                     0x0200
/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * �����������ȴ��˼��ź�������
 */
#define OS_TSK_MCSEM_PEND                                   0x0400

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * OS_TSK_EVENT_PEND      --- ���������ڵȴ����¼���
 */
#define OS_TSK_EVENT_PEND                                   0x0800

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * OS_TSK_EVENT_TYPE    --- ������¼����ͣ�0:ANY; 1:ALL��
 */
#define OS_TSK_EVENT_TYPE                                   0x1000


/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * OS_TSK_QUEUE_PEND      --- ����������ȴ����С�
 */
#define OS_TSK_QUEUE_PEND                                   0x2000

/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * OS_TSK_QUEUE_BUSY      --- �������ڶ�д���ݡ�
 */
#define OS_TSK_QUEUE_BUSY                                   0x4000

#if (OS_OPTION_KERNEL_PROCESS == YES) 
/**
 * @ingroup SRE_task
 * ������̿��ƿ�״̬��־��
 *
 * OS_TSK_SLEEP           --- ������̴�������״̬
 */
#define OS_TSK_SLEEP                                        0x8000

#endif

#if  (OS_OPTION_COPROCESSOR == YES)
/**
 * @ingroup SRE_task
 * �����������ƿ�״̬��־��
 *
 * ����ʹ��coprocessor��ʸ���Ĵ����ֳ��ѱ��档
 */
#define OS_TSK_CP_CONTEXT_SAVED                             0x0002
#endif

/**
 * @ingroup SRE_task
 * �����л����͡�
 *
 * ��������л���
 */
#define OS_TSK_FAST_TRAP                                    0x1

/**
 * @ingroup SRE_task
 * �����л����͡�
 *
 * ������ͨ�л���
 */
#define OS_TSK_NORMAL_TRAP                                  0x0


/*
 * ����ģ��Ĵ����붨�塣
 */
/**
 * @ingroup SRE_task
 * ��������룺�����ڴ�ʧ�ܡ�
 *
 * ֵ: 0x02000800
 *
 * �������: ��������˽��FSC�ڴ����
 *
 */
#define OS_ERRNO_TSK_NO_MEMORY                              SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x00)

/**
 * @ingroup SRE_task
 * ��������룺ָ�����Ϊ�ա�
 *
 * ֵ: 0x02000801
 *
 * �������: ������ָ���Ƿ�ΪNUL��
 */
#define OS_ERRNO_TSK_PTR_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x01)

/**
 * @ingroup SRE_task
 * ��������룺����ջ��Сδ��16�ֽڴ�С���롣
 *
 * ֵ: 0x02000802
 *
 * �������: ����������ջ��С�Ƿ�16�ֽڶ��롣
 */
#define OS_ERRNO_TSK_STKSZ_NOT_ALIGN                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x02)

/**
 * @ingroup SRE_task
 * ��������룺�������ȼ��Ƿ���
 *
 * ֵ: 0x02000803
 *
 * �������: �������������ȼ�Balongƽ̨���ܴ���63������ƽ̨���ܴ���31��
 */
#define OS_ERRNO_TSK_PRIOR_ERROR                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x03)

/**
 * @ingroup SRE_task
 * ��������룺������ں���Ϊ�ա�
 *
 * ֵ: 0x02000804
 *
 * �������: ������������ں����Ƿ�ΪNULL��
 */
#define OS_ERRNO_TSK_ENTRY_NULL                             SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x04)

/**
 * @ingroup SRE_task
 * ��������룺��������ָ��Ϊ�ջ�������Ϊ���ַ�����
 *
 * ֵ: 0x02000805
 *
 * �������: ���������ָ�����������
 */
#define OS_ERRNO_TSK_NAME_EMPTY                             SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x05)

/**
 * @ingroup SRE_task
 * ��������룺ָ��������ջ�ռ�̫С��
 *
 * ֵ: 0x02000806
 *
 * �������: �������ջ�Ƿ�С��OS_TSK_MIN_STACK_SIZE��
 */
#define OS_ERRNO_TSK_STKSZ_TOO_SMALL                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x06)

/**
 * @ingroup SRE_task
 * ��������룺����ID�Ƿ���
 *
 * ֵ: 0x02000807
 *
 * �������: ��鵱ǰ���������PID�Ƿ񳬹���������������û��������PID�Ƿ�Ϸ���
 */
#define OS_ERRNO_TSK_ID_INVALID                             SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x07)

/**
 * @ingroup SRE_task
 * ��������룺�����ѱ�����
 *
 * ֵ: 0x02000808
 *
 * �������: ��������������Ƿ�Ϊ�ѹ�������
 */
#define OS_ERRNO_TSK_ALREADY_SUSPENDED                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x08)

/**
 * @ingroup SRE_task
 * ��������룺����δ������
 *
 * ֵ: 0x02000809
 *
 * �������: ������ָ������Ƿ�δ����
 */
#define OS_ERRNO_TSK_NOT_SUSPENDED                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x09)

/**
 * @ingroup SRE_task
 * ��������룺����δ������
 *
 * ֵ: 0x0200080a
 *
 * �������: ��������Ƿ񴴽���
 */
#define OS_ERRNO_TSK_NOT_CREATED                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0a)

/**
 * @ingroup SRE_task
 * ��������룺���������״̬��ɾ����ǰ����
 *
 * ֵ: 0x0300080b
 *
 *�������: �û�ȷ��ɾ������ʱ�������������
 *
 */
#define OS_ERRNO_TSK_DELETE_LOCKED                          SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x0b)

/**
 * @ingroup SRE_task
 * ��������룺������������Ϣ�����㡣
 *
 * ֵ: 0x0200080c
 *
 * �������: �����ɾ�������Ƿ�����δ�������Ϣ��
 */
#define OS_ERRNO_TSK_MSG_NONZERO                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0c)

/**
 * @ingroup SRE_task
 * ��������룺��Ӳ�жϻ����жϵĴ����н�����ʱ������
 *
 * ֵ: 0x0300080d
 *
 *�������: �˲�����ֹ���ж��н��е��ȡ�
 *
 */
#define OS_ERRNO_TSK_DELAY_IN_INT                           SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x0d)

/**
 * @ingroup SRE_task
 * ��������룺���������״̬�½�����ʱ������
 *
 * ֵ: 0x0200080e
 *
 * �������: ����Ƿ�������
 */
#define OS_ERRNO_TSK_DELAY_IN_LOCK                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0e)

/**
 * @ingroup SRE_task
 * ��������룺����ID����Yield����ָ�������ȼ������С�
 *
 * ֵ: 0x0200080f
 *
 * �������: ����������������ȼ���
 */
#define OS_ERRNO_TSK_YIELD_INVALID_TASK                     SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x0f)

/**
 * @ingroup SRE_task
 * ��������룺Yield����ָ�������ȼ������У�����������С��2��
 *
 * ֵ: 0x02000810
 *
 * �������: ���ָ�����ȼ���������ȷ����������������1��
 */
#define OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK                  SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x10)

/**
 * @ingroup SRE_task
 * ��������룺û�п��õ�������ƿ���Դ��������������ü��رա�
 *
 * ֵ: 0x02000811
 *
 * �������: ��������������ü����أ��������㹻���������Դ����
 */
#define OS_ERRNO_TSK_TCB_UNAVAILABLE                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x11)

/**
 * @ingroup SRE_task
 * ��������룺�����Ӳ�ƥ�䣬��Ҫɾ���Ĺ���δע�����ȡ����
 *
 * ֵ: 0x02000812
 *
 * �������: ��鹳���Ƿ���ע�ᡣ
 */
#define OS_ERRNO_TSK_HOOK_NOT_MATCH                         SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x12)


/**
 * @ingroup SRE_task
 * ��������룺����IDLE����
 *
 * ֵ: 0x02000814
 *
 * �������: ����Ƿ����IDLE����
 */
#define OS_ERRNO_TSK_OPERATE_IDLE                           SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x14)

/**
 * @ingroup SRE_task
 * ��������룺���������״̬�¹���ǰ����
 *
 * ֵ: 0x03000815
 *
 *�������: ȷ����������ʱ�������Ѿ�������
 *
 */
#define OS_ERRNO_TSK_SUSPEND_LOCKED                         SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x15)

/**
 * @ingroup SRE_task
 * ��������룺�ͷ�����ջʧ�ܡ�
 *
 * ֵ: 0x02000817
 *
 * �������: ����Ƿ���ڴ浼���ڴ�鲻���ͷš�
 */
#define OS_ERRNO_TSK_FREE_STACK_FAILED                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x17)

/**
 * @ingroup SRE_task
 * ��������룺����ջ��������̫С��
 *
 * ֵ: 0x02000818
 *
 * �������: ��sre_config.h����������ջ��С����OS_TSK_MIN_STACK_SIZE ��
 */
#define OS_ERRNO_TSK_STKAREA_TOO_SMALL                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x18)

/**
 * @ingroup SRE_task
 * ��������룺ϵͳ��ʼ�����񼤻�ʧ�ܡ�
 *
 * ֵ: 0x02000819
 *
 * �������: �鿴����ջ�Ƿ����ô���
 *
 */
#define OS_ERRNO_TSK_ACTIVE_FAILED                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x19)

/**
 * @ingroup SRE_task
 * ��������룺���õ���������̫�࣬���õ��������������ܴ���254��ȥ���õ����жϸ��������������������Idle�����Ҳ���Ϊ0��
 *
 * ֵ: 0x0200081a
 *
 * �������: �������������н������������ΪС�ڵ���254��ȥ���õ����жϸ����Ҵ���0��
 */
#define OS_ERRNO_TSK_MAX_NUM_NOT_SUITED                     SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1a)

/**
 * @ingroup SRE_task
 * ��������룺�����coprocessor�����ı�������δ��16�ֽڶ��롣
 *
 * ֵ: 0x0200081b
 *
 * �������: ��鱣������ʼ��ַ�Ƿ�16�ֽڶ��롣
 */
#define OS_ERRNO_TSK_CP_SAVE_AREA_NOT_ALIGN                 SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1b)

/**
 * @ingroup SRE_task
 * ��������룺�����MSG���и�������8��
 *
 * ֵ: 0x0200081d
 *
 * �������: ȷ�����񴴽�����Ϣ������������8��
 */
#define OS_ERRNO_TSK_MSG_Q_TOO_MANY                         SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1d)

/**
 * @ingroup SRE_task
 * ��������룺�����coprocessor�����ı�������ĵ�ַΪ��ָ�롣
 *
 * ֵ: 0x0200081e
 *
 * �������: ��鱣������ʼ��ַ�Ƿ�ΪNULL��
 */
#define OS_ERRNO_TSK_CP_SAVE_AREA_NULL                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1e)

/**
 * @ingroup SRE_task
 * ��������룺������ɾ��ʱ�ͷ�δ������Ϣ���ڴ�ʧ�ܡ�
 *
 * ֵ: 0x0200081f
 *
 * �������: �ޡ�
 */
#define OS_ERRNO_TSK_SELF_DELETE_ERR                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x1f)

/**
 * @ingroup SRE_task
 * ��������룺��ȡ������Ϣʱ���û�ʵ������ȡ������Ϊ0��
 *
 * ֵ: 0x02000821
 *
 * �������: ��ȡ������Ϣʱ���û�ʵ�����������ȡ��������Ϊ0��
 */
#define OS_ERRNO_TSK_INPUT_NUM_ERROR                        SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x21)


/**
 * @ingroup SRE_task
 * ��������룺�û����õ�����ջ�׵�ַδ16�ֽڶ��롣
 *
 * ֵ: 0x02000822
 *
 * �������: ���ý�������ջ�׵�ַ��16�ֽڶ��롣
 */
#define OS_ERRNO_TSK_STACKADDR_NOT_ALIGN                    SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x22)

/**
 * @ingroup SRE_task
 * ��������룺�������ڲ������С�
 *
 * ֵ: 0x02000823
 *
 * �������: �ñ�ɾ��������õ����ȶ�ȡ��������ݣ�����ɾ����
 */
#define OS_ERRNO_TSK_QUEUE_DOING                            SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x23)

/**
 * @ingroup SRE_task
 * ��������룺���������ȼ��̳С�
 *
 * ֵ: 0x02000824
 *
 * �������: �ȴ�����ָ����ȼ����ٳ���������������ȼ���
 */
#define OS_ERRNO_TSK_PRIORITY_INHERIT                       SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x24)

/**
 * @ingroup SRE_task
 * ��������룺���������ڻ����ź����ϡ�
 *
 * ֵ: 0x02000825
 *
 * �������: �ȴ�����ָ����Ⱥ��ٳ���������������ȼ���
 */
#define OS_ERRNO_TSK_PEND_ON_MUTEX                          SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x25)

/**
 * @ingroup SRE_task
 * ��������룺����ɾ��ʱ���л����ź�����
 *
 * ֵ: 0x02000826
 *
 * �������: ɾ������ʱ���뽫����еĻ����ź����ͷš�
 */
#define OS_ERRNO_TSK_HAVE_MUTEX_SEM                         SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x26)

/**
 * @ingroup SRE_task
 * ��������룺�����˳�ʱû����ȫ�ͷ���Դ��
 *
 * ֵ: 0x03000827
 *
 *�������: �����˳�ǰȷ����ȫ�ͷ���ռ�е���Դ(����Ϣ�������ź�����)��
 *
 */
#define OS_ERRNO_TSK_EXIT_WITH_RESOURCE                     SRE_ERRNO_OS_FATAL(OS_MID_TSK, 0x27)

/**
 * @ingroup SRE_task
 * ��������룺�����������ȼ�ʱ���������������еĻ����ź�����������ȼ���������ȼ���
 *
 * ֵ: 0x02000828
 *
 *�������: �������ȼ�ʱ���ܵ���������Ŀ��������еĻ����ź�����������ȼ���������ȼ���
 *
 */
#define OS_ERRNO_TSK_PRIOR_LOW_THAN_PENDTSK                 SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x28)

/**
 * @ingroup SRE_task
 * ��������룺�����ڵ�ǰ�������е������л�ȡ��ǰ�������������Ϣ��
 *
 * ֵ: 0x02000829
 *
 *�������: ��Ҫ���ж��л�ȡ�������������Ϣ���ߵ�ǰ���������л�ȡ���������������������Ϣ��
 *
 */
#define OS_ERRNO_TSK_CONTEXT_NOT_GETED                      SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x29)

/**
 * @ingroup SRE_task
 * ��������룺�����߳�ʱû�п�ʹ�õ�GTID��Դ���䡣
 *
 * ֵ: 0x0200082a
 *
 * �������: ��鵱ǰ�������̹߳��࣬������Դ��������
 */
#define OS_ERRNO_TSK_NO_GTID_ALLOC_RESOURCE                 SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x2a)


/**
 * @ingroup SRE_process
 * ��������룺������ɾ���߳�ʱ�߳�TID��Ӧ��GTID��Դ�����ڡ�
 *
 * ֵ: 0x0200082b
 *
 * �������: ��鵱ǰ�����е�ɾ�����߳�TID�Ƿ���ڡ�
 */
#define OS_ERRNO_TSK_NO_GTID_RESOURCE_DEL                   SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x2b)

/**
 * @ingroup SRE_process
 * ��������룺û�������������
 *
 * ֵ: 0x0200082c
 *
 * �������: ����������idle���Ƿ���������û������л���
 */
#define OS_ERRNO_TSK_NO_SCHEDULE_REQ                       SRE_ERRNO_OS_ERROR(OS_MID_TSK, 0x2c)


/**
 * @ingroup SRE_task
 * ����ID�����Ͷ��塣
 */
typedef UINT32                                              TSK_HANDLE_T;

/**
 * @ingroup SRE_task
 * �������ȼ������Ͷ��塣
 */
typedef UINT16                                              TSK_PRIOR_T;

/**
 * @ingroup SRE_task
 * ����״̬�����Ͷ��塣
 */
typedef UINT16                                              TSK_STATUS_T;

/**
 * @ingroup SRE_task
 * ����ջ��Ϣ�Ľṹ�嶨�塣
 *
 * ��������ջ����Ϣ��
 */
typedef struct tagStackInfo
{
    UINT32 uwTop;                                           /**< ջ��                       */
    UINT32 uwBottom;                                        /**< ջ��                       */
    UINT32 uwSP;                                            /**< ջ��ǰSPָ��ֵ             */
    UINT32 uwCurrUsed;                                      /**< ջ��ǰʹ�õĴ�С           */
    UINT32 uwPeakUsed;                                      /**< ջʹ�õ���ʷ��ֵ           */
    BOOL   bOvf;                                            /**< ջ�Ƿ����                 */
} STACK_INFO_S;

/**
* @ingroup  SRE_task
* @brief ������ں������Ͷ��塣
*
* @par ����:
* �û�ͨ��������ں������Ͷ���������ں����������񴴽�����֮����øú�����������ִ�С�
* @attention �ޡ�
*
* @param  uwParam1 [IN] ����#UINT32�����ݸ����������ĵ�һ��������
* @param  uwParam2 [IN] ����#UINT32�����ݸ����������ĵڶ���������
* @param  uwParam3 [IN] ����#UINT32�����ݸ����������ĵ�����������
* @param  uwParam4 [IN] ����#UINT32�����ݸ����������ĵ��ĸ�������
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see �ޡ�
*/
typedef VOID (* TSK_ENTRY_FUNC)( UINT32 uwParam1,
                                 UINT32 uwParam2,
                                 UINT32 uwParam3,
                                 UINT32 uwParam4 );
/**
 * @ingroup  SRE_task
 * @brief ���񴴽����Ӻ������Ͷ��塣
 *
 * @par ����:
 * �û�ͨ�����񴴽����Ӻ������Ͷ������񴴽����ӣ���ϵͳ��������ʱ�����øù��ӡ�
 * @attention �ޡ�
 *
 * @param  puwTaskPID [IN] ����#UINT32���´��������PID��
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see �ޡ�
 */
typedef UINT32 (* TSK_CREATE_HOOK)(UINT32 uwTaskPID);

/**
* @ingroup  SRE_task
* @brief ����ɾ�����Ӻ������Ͷ��塣
*
* @par ����:
* �û�ͨ������ɾ�����Ӻ������Ͷ�������ɾ�����ӣ���ϵͳ���������ɾ��ʱ�����øù��ӡ�
* @attention �ޡ�
*
* @param  puwTaskPID [IN] ����#UINT32��ɾ�������PID��
*
* @retval �ޡ�
* @par ����:
* <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
* @since RTOSck V100R001C01
* @see �ޡ�
*/
typedef UINT32 (* TSK_DELETE_HOOK)(UINT32 uwTaskPID);

/**
 * @ingroup  SRE_task
 * @brief �����л����Ӻ������Ͷ��塣
 *
 * @par ����:
 * �û�ͨ�������л����Ӻ������Ͷ��������л����ӣ���ϵͳ����������л�ʱ�����øù��ӡ�
 * @attention �ޡ�
 *
 * @param  uwLastTaskPID [IN] ����#UINT32����һ�������PID��
 * @param  uwNextTaskPID [IN] ����#UINT32����һ�������PID��
 *
 * @retval �ޡ�
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see �ޡ�
 */
typedef UINT32 (* TSK_SWITCH_HOOK)(UINT32 uwLastTaskPID, UINT32 uwNextTaskPID);

/**
 * @ingroup SRE_task
 * ����ģ��������Ϣ�Ľṹ�嶨�塣
 *
 * ��������ģ�����������Ϣ��
 */
typedef struct tagTskModInfo
{
    UINT32 uwMaxNum;                /**< ���֧�ֵ�������           */
    UINT32 uwDefaultSize;           /**< ȱʡ������ջ��С           */
    UINT32 uwIdleStackSize;         /**< Idle���������ջ��С       */
    UINT32 uwStackAreaAddr;         /**< ����ջ�������ʼ��ַ       */
    UINT32 uwStackAreaSize;         /**< ����ջ����Ĵ�С           */
    UINT32 uwMagicWord;             /**< ����ջ��ʼ��ħ��           */
} TSK_MOD_INFO_S;

/**
 * @ingroup SRE_task
 * ���񴴽������Ľṹ�嶨�塣
 *
 * �������񴴽�ʱָ���Ĳ�����Ϣ��
 */
typedef struct tagTskInitParam
{
   TSK_ENTRY_FUNC pfnTaskEntry;     /**< ������ں���               */
   TSK_PRIOR_T    usTaskPrio;       /**< �������ȼ�                 */
   UINT16 usQNum;                   /**< ��Ϣ������                 */
   UINT32 auwArgs[4];               /**< ������������4��          */
   UINT32 uwStackSize;              /**< ����ջ�Ĵ�С               */
   CHAR  *pcName;                   /**< ������                     */
   UINT32 uwStackAddr;              /**< �����������ջ����������ʼ��ַ���û�����Ըó�Ա���г�ʼ����������Ϊ0��ʾ��ϵͳ�ڲ��ռ���䣬�����û�ָ��ջ��ʼ��ַ */
   UINT32 uwPrivateData;            /**< ר���ڱ������˽������     */
} TSK_INIT_PARAM_S;

/**
 * @ingroup SRE_task
 * ������Ϣ�Ľṹ�嶨�塣
 *
 * �û����Բ�ѯ��������Ϣ��
 */

#if (OS_HARDWARE_PLATFORM == OS_CORTEX_AX)
/**
 * @ingroup SRE_task
 * CORTEX_AXƽ̨���������ĵĽṹ�嶨�塣
 */
typedef struct tagTskContext
{
    UINT32 auwR[13];               /**< ��ǰ����Ĵ���R0-R12 */
    UINT32 uwPC;                   /**< ���������           */
    UINT32 uwLR;                   /**< ��R14���ӼĴ���      */
    UINT32 uwCPSR;                 /**< ��ǰ����״̬�Ĵ���   */
} TSK_CONTEXT_S;

#endif


#if ( (OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC))
/**
 * @ingroup SRE_task
 * Xtensa ƽ̨���������ĵĽṹ�嶨�塣
 */
typedef struct tagTskContext
{
    UINT32 auwA[16];                /**< ��ǰ���ڵ�a0-a15               */
    UINT32 uwPC;                    /**< ���������                     */
    UINT32 uwPS;                    /**< ����״̬�Ĵ���                 */
    UINT32 uwLBEG;                  /**< Loop Begin�Ĵ���               */
    UINT32 uwLEND;                  /**< Loop End�Ĵ���                 */
    UINT32 uwLCOUNT;                /**< Loop Count�Ĵ���               */
    UINT32 uwSAR;                   /**< ��λ���Ĵ���                   */
} TSK_CONTEXT_S;
#endif

#if (OS_HARDWARE_PLATFORM == OS_HIDSP)
/**
 * @ingroup SRE_task
 * OS_HIDSPƽ̨���������ĵĽṹ�嶨�塣
 */
typedef struct tagTskContext
{
    UINT32 uwTrapType;                 /**< OS_TSK_NORMAL_TRAP:�����л�; OS_TSK_FAST_TRAP: �����л�   */
    UINT32 uwLBEG0;                    /**< Loop Begin0�Ĵ���               */
    UINT32 uwLEND0;                    /**< Loop End0�Ĵ���                 */
    UINT32 uwLCOUNT0;                  /**< Loop Count0�Ĵ���               */
    UINT32 uwReserve0;                 /**< ����                            */
    UINT32 uwLBEG1;                    /**< Loop Begin1�Ĵ���               */
    UINT32 uwLEND1;                    /**< Loop End1�Ĵ���                 */
    UINT32 uwLCOUNT1;                  /**< Loop Count1�Ĵ���               */
    UINT32 uwReserve1;                 /**< ����                            */
    UINT32 auwA[32];                   /**< a0-a31�Ĵ���                    */
    UINT32 uwPC;                       /**< ���������                      */
    UINT32 uwSR;                       /**< ����״̬�Ĵ���                  */
} TSK_CONTEXT_S;

#endif

/**@ingroup SRE_task
 * ������Ϣ�ṹ��
 */
typedef struct tagTskInfo
{
   UINT32 uwSP;                     /**< �����л�ʱ��SP             */
   UINT32 uwPC;                     /**< �����л�ʱ��PC             */
   TSK_STATUS_T usTaskStatus;       /**< ����״̬                   */
   TSK_PRIOR_T  usTaskPrio;         /**< �������ȼ�                 */
   UINT32 uwStackSize;              /**< ����ջ�Ĵ�С               */
   UINT32 uwTopOfStack;             /**< ����ջ��ջ��               */
   UINT32 uwNumOfMsg;               /**< ������յ�����Ϣ��         */
   CHAR   acName[OS_TSK_NAME_LEN];  /**< ������                     */
} TSK_INFO_S;

/**@ingroup SRE_task
 * ����ջ��ѯ�ṹ��
 */
typedef struct tagStackTask
{
    UINT32 uwID;             /**< ����ID                                          */
    UINT32 uwSize;           /**< ������ʹ�õ�ջ��ֵ�����ջԽ������0xFFFFFFFF��ʾ*/
} OS_STACK_TASK_S;

/**@ingroup SRE_task
 * ����TCB�׵�ַ��Ϣ�ṹ�塣
 */
typedef struct tagTcbAddr
{
    UINT32 uwTskID;         /**< ����ID                  */
    VOID* pTcbAddr;         /**< ����TCB�׵�ַ           */
} TSK_TCB_ADDR_S;

///@cond
/**@ingroup SRE_task
* ����������ƿ�Ľṹ��
* pStackPointer��usTaskStatus��usPriority��λ�ò��ܱ䶯���������д����
*
typedef struct tagMsgQHead
{
    UINT32 uwMsgNum;
    LIST_OBJECT_S stMsgList;
} MSG_QHead_S;

typedef struct tagListObject
{
    struct tagListObject *pstPrev;
    struct tagListObject *pstNext;
} LIST_OBJECT_S;

typedef struct tagPublicTskCB
{
    VOID               *pStackPointer;              // ��ǰ�����SP
    TSK_STATUS_T        usTaskStatus;               // ����״̬
    TSK_PRIOR_T         usPriority;                 // ������������ȼ�
    UINT32              uwStackSize;                // ����ջ��С
    UINT32              uwTopOfStack;               // ����ջ��
    TSK_HANDLE_T        uwTaskPID;                  // ����PID
    TSK_ENTRY_FUNC      pfnTaskEntry;               // ������ں���
    VOID               *pTaskSem;                   // ����Pend���ź���ָ��
    INT32               swFsemCount;                // �����ź�������
    UINT32              auwArgs[4];                 // ����Ĳ���
#if (OS_OPTION_COPROCESSOR == YES)                  // ֻ��SD6108/SD6181/SD6182ƽ̨���иù���
    VOID               *pCpSaveAreaA;               // ʸ���Ĵ��������ַA
    VOID               *pCpSaveAreaB;               // ʸ���Ĵ��������ַB
#endif
    TSK_PRIOR_T         usOrigPriority;             // �����ԭʼ���ȼ�
    UINT16              usStackCfgFlg;              // ����ջ���ñ��
    UINT16              usQNum;                     // ��Ϣ������
    UINT16              usRecvQID;                  // ����������Ϣ��QID
    UINT32              uwPrivateData;              // ˽������
    MSG_QHead_S        *pstMsgQ;                    // ָ����Ϣ��������
    LIST_OBJECT_S       stPendList;                 // �ź�������ָ��
    LIST_OBJECT_S       stTimerList;                // ������ʱ����ָ��
    LIST_OBJECT_S       stSemBList;                 // ���л����ź�������
    UINT64              ullExpirationTick;          // ����ָ���ʱ���(��λTick)
    UINT32              uwEvent;                    // �����¼�
    UINT32              uwEventMask;                // �����¼�����
    UINT32              uwLastErr;                  // �����¼�����һ��������
    UINT32              uwReserved;                 // ����һ��PAD����֤TCB 8�ֽڶ���
} TSK_CB_S;

*/
///@endcond

/**
 * @ingroup  SRE_task
 * @brief ��������
 *
 * @par ����:
 * ����һ��������ϵͳOS��ʼ��ǰ����������ֻ�Ǽ򵥵ؼ���������С�
 * ϵͳ��ʼ���󴴽�������������ȼ����ڵ�ǰ������δ����������������������Ȳ������У��������������С�
 *
 * @attention
 * <ul>
 * <li>��ָ��������ջ����������ʼ��ַ��Ϊ0��������û����õĶ�������ջ����ջ�ռ���䣬����ϵͳ��ռ��(��Ϣ���и�������12�ֽ�)�Ŀռ�������Ϣ����ͷ��</li>
 * <li>���񴴽�ʱ�����֮ǰ��ɾ�������������ƿ������ջ���л��գ��û��������õ�����ջ���⡣</li>
 * <li>����������󳤶�Ϊ16�ֽڣ�����������</li>
 * <li>��������ʱ��Ҫ������Ϣ��������</li>
 * <li>ͬһ�����������������ظ����Ҳ���������ж�������</li>
 * <li>��ָ��������ջ��СΪ0����ʹ��������#OS_TSK_DEFAULT_STACK_SIZEָ����Ĭ�ϵ�����ջ��С��</li>
 * <li>����ջ�Ĵ�С���밴16�ֽڴ�С���롣ȷ������ջ��С��ԭ���ǣ����þ��У������˷ѣ���������ջ������������ȡ������Ҫ���Ķ��ٵ�ջ�ڴ棬������������������ò��Խ�ջ�ڴ濪��Խ�󣬾ֲ�����Խ�󣬾ֲ�����Խ�࣬ջ�ڴ濪��ҲԽ��</li>
 * <li>�û����õ�����ջ�׵�ַ��16�ֽڶ��룬�����õ�����ջ�ռ��У�os��ʹ����Ϣ������������Ϣ���п��ƿ���ڴ��С��</li>
 * <li>�û����õ�����ջ�ռ������û���֤��Ϸ��ԣ����Կ�cache�ռ�ĵ�ַ�û���Ҫ��֤������ջ�׵�ַ��ջ��Сcache line���룬ϵͳ�������봦������ʹ�ú������û������ͷš�</li>
 * <li>���񴴽�ʱ�����񴴽������е�����ջ��С���ý��鲻Ҫʹ����С����ջ��СOS_TSK_MIN_STACK_SIZE(��СΪ0x130)������ֻ�ǰ�������������Ԥ����ջ�ռ䣬�������ʱ�������������Ҫ���û����б�֤�㹻������ջ�ռ����á�</li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] ����#UINT32 *����������PID��
 * @param  pstInitParam [IN] ����#TSK_INIT_PARAM_S *�����񴴽���������ṹ���еĳ�Ա����uwStackAddr����ʱ������г�ʼ�������������û����õĶ�������ջ����ջ�ռ���䣬�ó�Ա�����ʼ��Ϊ0��
 *
 * @retval #OS_ERRNO_TSK_NO_MEMORY              0x02000800�������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TSK_STKSZ_NOT_ALIGN        0x02000802������ջ��Сδ��16�ֽڴ�С���롣
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803���������ȼ��Ƿ���
 * @retval #OS_ERRNO_TSK_ENTRY_NULL             0x02000804��������ں���Ϊ�ա�
 * @retval #OS_ERRNO_TSK_NAME_EMPTY             0x02000805����������ָ��Ϊ�ջ�������Ϊ���ַ�����
 * @retval #OS_ERRNO_TSK_STKSZ_TOO_SMALL        0x02000806��ָ��������ջ�ռ�̫С��
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_SUSPENDED          0x02000809������δ������
 * @retval #OS_ERRNO_TSK_FREE_STACK_FAILED      0x02000817���ͷ�����ջʧ�ܡ�
 * @retval #OS_ERRNO_TSK_TCB_UNAVAILABLE        0x02000811��û�п��õ�������ƿ���Դ��
 * @retval #OS_ERRNO_TSK_MSG_Q_TOO_MANY         0x0200081d�������MSG���и�������8��
 * @retval #OS_ERRNO_HUNT_THREAD_NAME_REPEAT    0x02001f01����������ʱ���߳���������
 * @retval #OS_ERRNO_TSK_STACKADDR_NOT_ALIGN    0x02000822����������ʱ���û���������ջ��ַδ16�ֽڶ��롣
 * @retval #SRE_OK                              0x00000000�����񴴽��ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDelete | SRE_TaskCreateHookAdd | SRE_TaskCreateOnly
 */
extern UINT32 SRE_TaskCreate(UINT32 *puwTaskPID, TSK_INIT_PARAM_S *pstInitParam);


/**
 * @ingroup  SRE_task
 * @brief �������񣬵�����������
 *
 * @par ����:
 * ����һ�����񡣸����񲻼���������У�ֻ���ڹ���״̬���û���Ҫ�����������Ҫͨ������SRE_TaskResume�������伤�
 *
 * @attention
 * <ul>
 * <li>��ָ��������ջ����������ʼ��ַ��Ϊ0��������û����õĶ�������ջ����ջ�ռ���䣬����ϵͳ��ռ��(usQNum * 12�ֽ�)�Ŀռ�������Ϣ����ͷ��</li>
 * <li>���񴴽�ʱ�����֮ǰ��ɾ�������������ƿ������ջ���л��գ��û��������õ�����ջ���⡣</li>
 * <li>����������󳤶�Ϊ16�ֽڣ�����������</li>
 * <li>��������ʱ��Ҫ������Ϣ��������</li>
 * <li>ͬһ�����������������ظ����Ҳ���������ж�������</li>
 * <li>��ָ��������ջ��СΪ0����ʹ��������#OS_TSK_DEFAULT_STACK_SIZEָ����Ĭ�ϵ�����ջ��С��</li>
 * <li>����ջ�Ĵ�С���밴16�ֽڴ�С���롣ȷ������ջ��С��ԭ���ǣ����þ��У������˷ѣ���������ջ������������ȡ������Ҫ���Ķ��ٵ�ջ�ڴ棬������������������ò��Խ�ջ�ڴ濪��Խ�󣬾ֲ�����Խ�󣬾ֲ�����Խ�࣬ջ�ڴ濪��ҲԽ��</li>
 * <li>�û����õ�����ջ�׵�ַ��16�ֽڶ��룬�����õ�����ջ�ռ��У�os��ʹ����Ϣ������*��Ϣ���п��ƿ���ڴ��С��</li>
 * <li>�û����õ�����ջ�ռ������û���֤��Ϸ��ԣ����Կ�cache�ռ�ĵ�ַ�û���Ҫ��֤������ջ�׵�ַ��ջ��Сcache line���룬ϵͳ�������봦������ʹ�ú������û������ͷš�</li>
 * <li>���񴴽�ʱ�����񴴽������е�����ջ��С���ý��鲻Ҫʹ����С����ջ��СOS_TSK_MIN_STACK_SIZE(��СΪ0x130)������ֻ�ǰ�������������Ԥ����ջ�ռ䣬�������ʱ�������������Ҫ���û����б�֤�㹻������ջ�ռ����á�</li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] ����#UINT32 *����������PID��
 * @param  pstInitParam [IN] ����#TSK_INIT_PARAM_S *�����񴴽���������ṹ���еĳ�Ա����uwStackAddr����ʱ������г�ʼ�������������û����õĶ�������ջ����ջ�ռ���䣬�ó�Ա�����ʼ��Ϊ0��
 *
 * @retval #OS_ERRNO_TSK_NO_MEMORY              0x02000800�������ڴ�ʧ�ܡ�
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TSK_STKSZ_NOT_ALIGN        0x02000802������ջ��Сδ��16�ֽڴ�С���롣
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803���������ȼ��Ƿ���
 * @retval #OS_ERRNO_TSK_ENTRY_NULL             0x02000804��������ں���Ϊ�ա�
 * @retval #OS_ERRNO_TSK_NAME_EMPTY             0x02000805����������ָ��Ϊ�ջ�������Ϊ���ַ�����
 * @retval #OS_ERRNO_TSK_STKSZ_TOO_SMALL        0x02000806��ָ��������ջ�ռ�̫С��
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_TCB_UNAVAILABLE        0x02000811��û�п��õ�������ƿ���Դ��
 * @retval #OS_ERRNO_TSK_MSG_Q_TOO_MANY         0x0200081d�������MSG���и�������8��
 * @retval #OS_ERRNO_HUNT_THREAD_NAME_REPEAT    0x02001f01����������ʱ���߳�������.
 * @retval #OS_ERRNO_TSK_STACKADDR_NOT_ALIGN    0x02000822����������ʱ���û���������ջ��ַδ16�ֽڶ���.
 * @retval #SRE_OK                              0x00000000�����񴴽��ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDelete | SRE_TaskCreateHookAdd | SRE_TaskCreate
 */
extern UINT32 SRE_TaskCreateOnly(UINT32 *puwTaskPID, TSK_INIT_PARAM_S *pstInitParam);


/**
 * @ingroup  SRE_task
 * @brief �ָ�����
 *
 * @par ����:
 * �ָ����������
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>�������Դ�����ʱ������̬����ֻ��ȡ������̬����������������С�</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 *
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #OS_ERRNO_TSK_NOT_SUSPENDED          0x02000809������δ������
 * @retval #SRE_OK                              0x00000000���ָ�����ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSuspend
 */
extern UINT32 SRE_TaskResume(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
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
 * </ul>
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 *
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_ALREADY_SUSPENDED      0x02000808�������ѱ�����
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814������IDLE����
 * @retval #OS_ERRNO_TSK_SUSPEND_LOCKED         0x03000815�����������״̬�¹���ǰ����
 * @retval #SRE_OK                              0x00000000����������ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since  RTOSck V100R001C01
 * @see SRE_TaskResume | SRE_TaskLock
 */
extern UINT32 SRE_TaskSuspend(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief ɾ������
 *
 * @par ����:
 * ɾ��ָ���������ͷ�����ջ��������ƿ���Դ��
 *
 * @attention
 * <ul>
 * <li>��Ϊ��ɾ������������ƿ������ջ����һ�δ�������ʱ�Ż��ա�</li>
 * <li>����������ɾ����RTOSck�����������ص��ź����ͽ��յ�����Ϣ��ǿ��ɾ����</li>
 * <li>������ɾ��ʱ��ɾ�����Ӳ��������pend�ź���������Ȳ�����</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 *
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #OS_ERRNO_TSK_DELETE_LOCKED          0x0300080b�����������״̬��ɾ����ǰ����
 * @retval #OS_ERRNO_TSK_MSG_NONZERO            0x0200080c��������������Ϣ�����㡣
 * @retval #OS_ERRNO_TSK_HAVE_MUTEX_SEM         0x02000826��������л������ź���ʱɾ��������
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814������IDLE����
 * @retval #OS_ERRNO_TSK_QUEUE_DOING            0x02000823���������ڲ������С�
 * @retval #SRE_OK                              0x00000000��ɾ������ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCreate | SRE_TaskDeleteHookAdd
 */
extern UINT32 SRE_TaskDelete(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief �ӳ��������е�����
 *
 * @par ����:
 * �ӳٵ�ǰ���������ִ�С�������ʱ�ȴ�ָ����Tick�������²�����ȡ�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>Ӳ�жϻ����жϴ����У���������������ʱ����ʧ�ܡ�</li>
 * <li>���������0����δ��������ȣ���˳ȡͬ���ȼ������е���һ������ִ�С���û��ͬ���ľ��������򲻷���������ȣ�����ִ��ԭ����</li>
 * </ul>
 *
 * @param  uwTick [IN] ����#UINT32���ӳٵ�Tick����
 *
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803���������ȼ��Ƿ���
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_YIELD_INVALID_TASK     0x0200080f������ID����Yield����ָ�������ȼ������С�
 * @retval #OS_ERRNO_TSK_DELAY_IN_INT           0x0300080d����Ӳ�жϻ����жϵĴ����н�����ʱ������
 * @retval #OS_ERRNO_TSK_DELAY_IN_LOCK          0x0200080e�����������״̬�½�����ʱ������
 * @retval #OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK  0x02000810��Yield����ָ�������ȼ������У�����������С��2��
 * @retval #SRE_OK                              0x00000000��������ʱ�ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskYield
 */
extern UINT32 SRE_TaskDelay(UINT32 uwTick);


/**
 * @ingroup  SRE_task
 * @brief ��������ȡ�
 *
 * @par ����:
 * ��������ȡ���������ȱ������򲻷��������л���
 *
 * @attention
 * <ul>
 * <li>ֻ����������ȣ��������жϣ���������Կɱ��жϴ�ϡ�</li>
 * <li>ִ�д˺�����������ֵ��1��������������ֵ��1����ˣ�������#SRE_TaskUnlock���ʹ�á�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskUnlock
 */
extern VOID SRE_TaskLock(VOID);


/**
 * @ingroup  SRE_task
 * @brief ����������ȡ�
 *
 * @par ����:
 * ����������ֵ��1����Ƕ�׼�������ֻ��������ֵ��Ϊ0�������Ľ�����������ȡ�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>ִ�д˺�����������ֵ��1��������������ֵ��1����ˣ�������#SRE_TaskLock���ʹ�á�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskLock
 */
extern VOID SRE_TaskUnlock(VOID);


/**
 * @ingroup  SRE_task
 * @brief ��ȡ��ǰ����PID��
 *
 * @par ����:
 * ��ȡ��������̬������PID��
 *
 * @attention
 * <ul>
 * <li>Ӳ�жϻ����жϴ����У�Ҳ�ɻ�ȡ��ǰ����PID�������жϴ�ϵ�����</li>
 * <li>�������л����Ӵ����е���ʱ����ȡ�������������ID��</li>
 * </ul>
 *
 * @param  puwTaskPID [OUT] ����#UINT32����������PID��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������ID�Ƿ���
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskStatusGet | SRE_TaskInfoGet
 */
extern UINT32 SRE_TaskSelf(UINT32 *puwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief �������PID��
 *
 * @par ����:
 * �������PID�Ƿ�Ϸ���
 *
 * @attention
 * <ul>
 * <li>����ID�����Ǵ�0��ʼ��ŵġ�</li>
 * <li>�ýӿ�ֻ֧�ֱ�������PID�ļ�⡣</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 *
 * @retval #TRUE        1�� ����PID����Ϸ���
 * @retval #FALSE       0�� ����PID���벻�Ϸ���

 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSelf
 */
extern BOOL SRE_TaskIDCheck(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief ��ȡ����״̬��
 *
 * @par ����:
 * ��ȡָ�������״̬��
 *
 * @attention ��
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 *
 * @retval #(TSK_STATUS_T)OS_INVALID    ����ʧ�ܡ�
 * @retval #����״̬ ���سɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskInfoGet | SRE_TaskContextGet | SRE_TaskPrivateDataGet
 */
extern TSK_STATUS_T SRE_TaskStatusGet(UINT32 uwTaskPID);


/**
 * @ingroup  SRE_task
 * @brief ��ȡ������Ϣ��
 *
 * @par ����:
 * ��ȡָ���������Ϣ��
 *
 * @attention
 * <ul>
 * <li>����ȡ��ǰ�������Ϣ����ֻ��Ӳ�жϡ����жϡ��쳣�Ĵ����в������壬�����ȡ��SPֵ��PCֵ�ǲ�׼�ġ�(��Xtensaƽ̨�²����������������л�ȡ��������Ϣ)</li>
 * <li>���������л�ʱ����������ϢҲ����������ջ�У����������Ϣ�е�SP�Ǳ���������֮���ʵ�ʵ�SPֵ��</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 * @param  pstTaskInfo [OUT] ����#TSK_INFO_S *������������Ϣ��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskStatusGet | SRE_TaskContextGet | SRE_TaskPrivateDataGet
 */
extern UINT32 SRE_TaskInfoGet(UINT32 uwTaskPID, TSK_INFO_S *pstTaskInfo);

#if ( (OS_HARDWARE_PLATFORM == OS_RISC170) || (OS_HARDWARE_PLATFORM == OS_DSP170) \
    || (OS_HARDWARE_PLATFORM == OS_RISC220)|| (OS_HARDWARE_PLATFORM == OS_DSP220) \
    || (OS_HARDWARE_PLATFORM == OS_HACCC) || (OS_HARDWARE_PLATFORM == OS_CORTEX_AX) \
    || (OS_HARDWARE_PLATFORM == OS_HIDSP))

/**
 * @ingroup  SRE_task
 * @brief ��ȡ���������ġ�
 *
 * @par ����:
 * ��ȡָ������������ġ�
 *
 * @attention
 * <ul>
 * <li>����ȡ��ǰ�������������Ϣ����ֻ��Ӳ�жϡ����жϡ��쳣�Ĵ����в������壬�����ȡ��PCֵ�ǲ�׼�ġ�</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 * @param  pstContext [OUT] ����#TSK_CONTEXT_S *������������������Ϣ��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #OS_ERRNO_TSK_CONTEXT_NOT_GETED      0x02000829, ��ȡ��ǰ�������������������������Ϣʧ�ܡ�
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskStatusGet | SRE_TaskInfoGet | SRE_TaskPrivateDataGet
 */
 extern UINT32 SRE_TaskContextGet(UINT32 uwTaskPID, TSK_CONTEXT_S *pstContext);
#endif

/**
 * @ingroup  SRE_task
 * @brief ��ȡ˽�����ݡ�
 *
 * @par ����:
 * ��ȡ��ǰ�����˽�����ݡ�
 *
 * @attention
 * <ul>
 * <li>����ǰ������������ʱ�����øýӿ��ܻ�ȡ��ǰ�����˽�����ݡ�</li>
 * <li>�������жϴ��ʱ���ж�����øýӿ��ܻ�ȡ���жϴ�ϵ������˽�����ݡ�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval #��ǰ�����˽������ ����ֵ����δ���ã��򷵻ص�ֵ��ȷ����
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPrivateDataSet
 */
extern UINT32 SRE_TaskPrivateDataGet(VOID);


/**
 * @ingroup  SRE_task
 * @brief ����˽������ֵ��
 *
 * @par ����:
 * ���õ�ǰ�����˽������ֵ��
 *
 * @attention
 * <ul>
 * <li>ֻ�����������е��á������ж������ã���������Ǹձ���ϵ�����</li>
 * </ul>
 *
 * @param  uwPrivateData [IN] ����#UINT32������ֵ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPrivateDataGet
 */
extern VOID SRE_TaskPrivateDataSet(UINT32 uwPrivateData);


/**
 * @ingroup  SRE_task
 * @brief ��ȡ���ȼ���
 *
 * @par ����:
 * ��ȡָ����������ȼ���
 *
 * @attention ��
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 * @param  uwTaskPID [OUT] ����#TSK_PRIOR_T *�������������ȼ�ָ�롣
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPrioritySet
 */
extern UINT32 SRE_TaskPriorityGet(UINT32 uwTaskPID, TSK_PRIOR_T * pusTaskPrio);

/**
 * @ingroup  SRE_task
 * @brief �������ȼ���
 *
 * @par ����:
 * ����ָ����������ȼ���
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>�����õ����ȼ����ڵ�ǰ���е��������������������ȡ�</li>
 * <li>��������ǰ������������ȼ���ͬ����������������ȡ�</li>
 * <li>�����������ȼ��̳л������������ڻ����ź����ϣ�������������������ȼ���</li>
 * </ul>
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 * @param  usTaskPrio [IN] ����#TSK_PRIOR_T���������ȼ���
 *
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803���������ȼ��Ƿ���
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #OS_ERRNO_TSK_OPERATE_IDLE           0x02000814������IDLE����
 * @retval #OS_ERRNO_TSK_PRIORITY_INHERIT       0x02000824�����������ȼ��̳С�
 * @retval #OS_ERRNO_TSK_PEND_ON_MUTEX          0x02000825�����������ڻ����ź����ϡ�
 * @retval #OS_ERRNO_TSK_PRIOR_LOW_THAN_PENDTSK 0x02000828���������ȼ����������������еĻ����ź�����������ȼ���������ȼ�
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskPriorityGet
 */
extern UINT32 SRE_TaskPrioritySet(UINT32 uwTaskPID, TSK_PRIOR_T usTaskPrio);


/**
 * @ingroup  SRE_task
 * @brief ����ָ�����ȼ����������˳��
 *
 * @par ����:
 * ��uwNextTaskΪ#OS_TSK_NULL_ID�������ȼ������еĵ�һ�����������������β,
 * ���򣬽�uwNextTaskָ����������������ȼ����еĶ��ס�
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>ǰ����ָ�����ȼ��ľ�����������Ҫ�������������񣬷��򱨴��ء�</li>
 * </ul>
 *
 * @param  usTaskPrio [IN] ����#TSK_PRIOR_T������usTaskPrio��ָ���������ȼ����С�
 * @param  uwNextTask [IN] ����#UINT32������ID��OS_TSK_NULL_ID��
 * @param  puwYeildTo [OUT] ����#UINT32 *�����汻���������׵�����PID����ΪNULL(����Ҫ�����������PID)��
 *
 * @retval #OS_ERRNO_TSK_PRIOR_ERROR            0x02000803���������ȼ��Ƿ���
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_YIELD_INVALID_TASK     0x0200080f������PID����Yield����ָ�������ȼ������С�
 * @retval #OS_ERRNO_TSK_YIELD_NOT_ENOUGH_TASK  0x02000810��Yield����ָ�������ȼ������У�����������С��2��
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSuspend
 */
extern UINT32 SRE_TaskYield( TSK_PRIOR_T  usTaskPrio,
                             UINT32 uwNextTask,
                             UINT32 *puwYeildTo );



/**
 * @ingroup  SRE_task
 * @brief ��ѯ����ָ����������PEND���ź�����
 *
 * @par ����:
 * ��������״̬��������ƿ飬�ж������Ƿ���PEND�ź������Լ�PEND���ź���ID��
 *
 * @attention
 * <ul>
 * <li>�û�Ӧ���ж�PEND״̬��״̬Ϊ0��������û�б��ź���������</li>
 * <li>�����ź���û���ź���ID�������������ڿ����ź������򷵻ص��ź���IDΪ#OS_INVALID��</li>
 * </ul>
 *
 * @param  uwTaskID     [IN]  ����#UINT32������PID��
 * @param  pusSemID     [OUT] ����#UINT16 *������PEND���ź���ID����#OS_INVALID��
 * @param  pusPendState [OUT] ����#UINT16 *�������PEND״̬��0��#OS_TSK_FSEM_PEND��#OS_TSK_PEND��#OS_TSK_MCSEM_PEND��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL       0x02000801��ָ�����Ϊ�ա�
 * @retval #OS_ERRNO_TSK_ID_INVALID     0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED    0x0200080a������δ������
 * @retval #SRE_OK                      0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SemPendListGet | SRE_McSemPendListGet
 */
extern UINT32 SRE_TaskPendSemGet(TSK_HANDLE_T uwTaskID, UINT16 *pusSemID, UINT16 *pusPendState);

/**
 * @ingroup  SRE_task
 * @brief ��ѯ��ǰ��������ָ�����е���Ϣ�����ո�����
 *
 * @par ����:
 *��ѯ��ǰ����������Ϣ����uwQid�ϴ�������Ϣ������
 *
 * @attention
 * <ul>
 * <li>6181/6108/6182ƽ̨�ϱ�ʾ�����ϵ�ָ������Ϣ���е���Ϣ��������ƽ̨��֧�ֶ���Ϣ���У��ýӿڱ�ʾ��Ϣ�����ϵ���Ϣ�������uwQid��Ч��</li>
 * <li>���uwQid��Ч�������û���֤��</li>
 * </ul>
 *
 * @param  uwQid [IN] ����#UINT32��6181/6108/6182ƽ̨�ϱ�ʾ�����ϵ���Ϣ���У�����ƽ̨��Ч��Ρ�
 *
 * @retval  ��ǰ��������ָ�����е���Ϣ�����ո�����
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_TaskMsgNumGet(UINT32 uwQid);

/**
 * @ingroup  SRE_task
 * @brief ��ȡָ������Ķ�ջ��Ϣ��
 *
 * @par ����:
 * ��ȡָ������Ķ�ջ��Ϣ��
 *
 * @attention ��
 *
 * @param  uwTaskPID [IN] ����#UINT32������PID��
 * @param  pstStackInfo [OUT] ����#STACK_INFO_S������ջ��Ϣ��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL      0x02000801�����ָ��Ϊ�ա�
 * @retval #OS_ERRNO_TSK_ID_INVALID    0x02000807���������ID���Ϸ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED   0x0200080a������δ������
 * @retval #SRE_OK                     0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_TaskStackInfoGet(TSK_HANDLE_T uwTaskPID, STACK_INFO_S *pstStackInfo);


#if  (OS_OPTION_COPROCESSOR == YES)

/**
 * @ingroup  SRE_task
 * @brief ���������ʸ���������������ݱ�����
 *
 * @par ����:
 * ��ָ���������ʸ���������������ݱ�����
 *
 * @attention
 * <ul>
 * <li>�ò���������SD6108/SD6181ƽ̨��DSP�ˣ�SD6182/SD6157ƽ̨��</li>
 * <li>����ʸ�������������õ��˵�˫LoadStoreָ��������õ�SaveAreaA/SaveAreaB�ڲ�ͬ��Memory Bank�С�</li>
 * <li>ʸ�����������ݱ�������С�����û�����оƬʵ�ʴ��ڵ�ʸ���Ĵ����ܴ�Сȷ����</li>
 * </ul>
 *
 * @param  uwTaskID [IN] ����Ϊ#TSK_HANDLE_T������ID��
 * @param  pstParam [IN] ����#CP_SAVE_CFG_PARAM_S *�������ṹָ��
 *
 * @retval #OS_ERRNO_TSK_CP_SAVE_AREA_NULL      0x0200081e�������coprocessor�����ı�������ĵ�ַΪ��ָ�롣
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807����������ID�Ƿ���
 * @retval #OS_ERRNO_TSK_CP_SAVE_AREA_NOT_ALIGN 0x0200801b����������δ��16�ֽڶ��롣
 * @retval #SRE_OK                              0x00000000���ɹ���
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCpEntry | SRE_TaskCpExit
 */
extern UINT32 SRE_TaskCpSaveCfg(TSK_HANDLE_T uwTaskID, CP_SAVE_CFG_PARAM_S *pstParam);

/**
 * @ingroup  SRE_task
 * @brief ������ִ��ʸ�����������
 *
 * @par ����:
 * ������ִ��ʸ�����������, ʸ��������ʼ֮ǰ����ô˽ӿڡ�
 *
 * @attention
 * <ul>
 * <li>�ò���������SD6108/SD6181ƽ̨��DSP�ˣ�SD6182/SD6157/SD6183ƽ̨��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCpExit
 */
extern VOID SRE_TaskCpEntry(VOID);

/**
 * @ingroup  SRE_task
 * @brief ������ִ��ʸ�������ĳ���
 *
 * @par ����:
 * ������ִ��ʸ�������ĳ��ڣ�ʸ���������֮������ô˽ӿڡ�
 *
 * @attention
 * <ul>
 * <li>�ò���������SD6108/SD6181ƽ̨��DSP�ˣ�SD6182/SD6157/SD6183ƽ̨��</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCpEntry
 */
extern VOID SRE_TaskCpExit(VOID);

#else
#define SRE_TaskCpSaveCfg(uwTaskID, pstParam)   SRE_OK
#define SRE_TaskCpEntry(VOID)
#define SRE_TaskCpExit(VOID)
#endif

/**
 * @ingroup  SRE_task
 * @brief ��ȡָ��PID������TCB�׵�ַ��
 *
 * @par ����:
 * ��ȡָ��PID������TCB�׵�ַ��
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>���ܻ�ȡID���Ϸ�������TCB��ַ��</li>
 * <li>����ȡID������û�д���������ʧ�ܡ�</li>
 * </ul>
 *
 * @param  uwTaskPID  [IN] ����#UINT32������PID��
 * @param  puwTcbAddr [OUT] ����#UINT32* ����������TCB��ַ��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��pTskTcbAddrΪNULL��
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807������PID�Ƿ���
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a������δ������
 * @retval #SRE_OK                              0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskIDList
 */
extern UINT32 SRE_TaskTcbAddrGet(TSK_HANDLE_T uwTaskPID, UINT32* puwTcbAddr);

/**
 * @ingroup  SRE_task
 * @brief ��ȡ�����Ѵ���������PID��Ϣ��
 *
 * @par ����:
 * ��ȡ�����Ѵ���������PID��Ϣ����������ID��С���������
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * </ul>
 *
 * @param  pusMaxNum  [IN/OUT] ����#UINT16 *��Ԫ�ظ���������/������������룺������pstTaskPID�����ɵ�Ԫ�ظ������������д�ڻ�����pstTaskPID����Ч��Ԫ�ظ�����
 * @param  pstTaskPID [OUT]    ����#UINT32 *����������������������ڱ������������PID��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL           0x02000801����ȡ���������PID��Ϣʱ���������ΪNULL��
 * @retval #OS_ERRNO_TSK_INPUT_NUM_ERROR    0x02000821����ȡ���������PID��Ϣʱ��������Ϊ0����
 * @retval #SRE_OK                          0x00000000���ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_TaskIDList(UINT16 *pusMaxNum, UINT32 *pstTaskPID);

/**
 * @ingroup  SRE_task
 * @brief ��ѯ��������
 *
 * @par ����:
 * ��������PID����ѯ��������
 *
 * @attention
 * <ul>
 * <li>��osStart֮ǰ���ܵ��øýӿڡ�</li>
 * <li>���ܲ�ѯID���Ϸ�����������</li>
 * <li>����ѯû�д���������������ѯʧ�ܡ�</li>
 * </ul>
 *
 * @param  uwTaskID [IN] ����#UINT32������ID��
 * @param  ppcName  [OUT] ����#CHAR **�������������ַ������׵�ַ��
 *
 * @retval #OS_ERRNO_TSK_PTR_NULL               0x02000801��  ����������ָ��ΪNULL��
 * @retval #OS_ERRNO_TSK_NOT_CREATED            0x0200080a��  ����δ������
 * @retval #OS_ERRNO_TSK_ID_INVALID             0x02000807��  ����ID�Ƿ���
 * @retval #SRE_OK                              0x00000000��  ��ѯ�ɹ���
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see  SRE_TaskIDList
 */
extern UINT32 SRE_TaskNameGet(TSK_HANDLE_T uwTaskID,CHAR **ppcName);

/**
 * @ingroup  SRE_task
 * @brief ע�������л����ӡ�
 *
 * @par ����:
 * ע�������л����Ӻ��������Ӻ���������������ǰ�����á�
 *
 * @attention
 * <ul>
 * <li>��ͬ���Ӻ�����ִ�е��Ⱥ�˳�򣬲�Ӧ������������ϵ��</li>
 * <li>��Ӧ�������л���������п�������������ȵĴ����磺������ʱ��P�ź����ȡ�</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#TSK_SWITCH_HOOK�������л����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSwitchHookDelete | SRE_TaskDeleteHookAdd | SRE_TaskCreateHookAdd
 */
#define SRE_TaskSwitchHookAdd(pfnHook) SRE_HookAdd(OS_HOOK_TSK_SWITCH, (OS_VOID_FUNC)(TSK_SWITCH_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief ȡ�������л����ӡ�
 *
 * @par ����:
 * ȡ��ָ���������л����ӡ����Ӻ���������������ǰ�����á�
 *
 * @attention  ��
 *
 * @param  pfnHook [IN] ����#TSK_SWITCH_HOOK�������л����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskSwitchHookAdd
 */
#define SRE_TaskSwitchHookDelete(pfnHook) SRE_HookDel(OS_HOOK_TSK_SWITCH, (OS_VOID_FUNC)(TSK_SWITCH_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief ע�����񴴽����ӡ�
 *
 * @par ����:
 * ע�����񴴽����Ӻ���,���Ӻ��������񴴽��ɹ��󱻵��á�
 *
 * @attention
 * <ul>
 * <li>��Ӧ�����񴴽������ﴴ������</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#TSK_CREATE_HOOK�����񴴽����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCreateHookDelete | SRE_TaskDeleteHookAdd | SRE_TaskSwitchHookAdd
 */
#define SRE_TaskCreateHookAdd(pfnHook)  SRE_HookAdd(OS_HOOK_TSK_CREATE, (OS_VOID_FUNC)(TSK_CREATE_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief ȡ�����񴴽����ӡ�
 *
 * @par ����:
 * ȡ��ָ�������񴴽����Ӻ���,���Ӻ��������񴴽��ɹ��󱻵��á�
 *
 * @attention ��
 *
 * @param  pfnHook [IN] ����#TSK_CREATE_HOOK�����񴴽����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskCreateHookAdd
 */
#define SRE_TaskCreateHookDelete(pfnHook) SRE_HookDel(OS_HOOK_TSK_CREATE, (OS_VOID_FUNC)(TSK_CREATE_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief ע������ɾ�����ӡ�
 *
 * @par ����:
 * ע������ɾ�����Ӻ���,���Ӻ�������Դ����ǰ�����á�
 *
 * @attention
 * <ul>
 * <li>����ɾ�������в��������pend�ź���������</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#TSK_DELETE_HOOK������ɾ�����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDeleteHookDelete | SRE_TaskCreateHookAdd | SRE_TaskSwitchHookAdd
 */
#define SRE_TaskDeleteHookAdd(pfnHook)  SRE_HookAdd(OS_HOOK_TSK_DELETE,(OS_VOID_FUNC)(TSK_DELETE_HOOK)pfnHook)

/**
 * @ingroup  SRE_task
 * @brief ȡ������ɾ�����ӡ�
 *
 * @par ����:
 * ȡ��ָ��������ɾ������,���Ӻ�������Դ����ǰ�����á�
 *
 * @attention
 * <ul>
 * <li>��Ӧ������ɾ��������ɾ������</li>
 * </ul>
 *
 * @param  pfnHook [IN] ����#TSK_DELETE_HOOK������ɾ�����Ӻ�����
 *
 * @par ����:
 * <ul><li>sre_task.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_TaskDeleteHookAdd
 */
#define SRE_TaskDeleteHookDelete(pfnHook) SRE_HookDel(OS_HOOK_TSK_DELETE, (OS_VOID_FUNC)(TSK_DELETE_HOOK)pfnHook)

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_BASE_H */


