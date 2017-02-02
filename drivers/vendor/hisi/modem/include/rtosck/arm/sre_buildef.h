/**
 * @file SRE_buildef.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ����������Ӳ��ƽ̨�ı���ꡣ \n
 */

#ifndef _SRE_BUILDEF_H
#define _SRE_BUILDEF_H


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
* С�ֽ���
*/
#define OS_LITTLE_ENDIAN                                    0x1234

/**
* ���ֽ���
*/
#define OS_BIG_ENDIAN                                       0x4321

/* To define OS_HARDWARE_PLATFORM */
#define OS_C64X                                             0x0
#define OS_C64XPLUS                                         0x1
#define OS_SC3400                                           0x2
#define OS_XTENSA2                                          0x3
#define OS_SC3850                                           0x4
#define OS_RISC170                                          0x5
#define OS_DSP170                                           0x6
#define OS_RISC220                                          0x7
#define OS_DSP220                                           0x8
#define OS_HACCC                                            0x9
#define OS_CORTEX_AX                                        0xa
#define OS_CORTEX_MX                                        0xb
#define OS_HI1210                                           0xc
#define OS_HIDSP                                            0xd

/* To define OS_CPU_TYPE */
#define OS_TI6482                                           0x0
#define OS_LSI2603                                          0x1
#define OS_MSC8144                                          0x2
#define OS_SD6153                                           0x3
#define OS_TI6487                                           0x4
#define OS_GBDSP                                            0x5
#define OS_MSC8156                                          0x6
#define OS_SD6108                                           0x7
#define OS_SD6181                                           0x8
#define OS_SD6182                                           0x9
#define OS_CORTEX_A9                                        0xa
#define OS_STM32F407                                        0xb
#define OS_CORTEX_A7                                        0xc
#define OS_SD6183                                           0xd
#define OS_SD6157                                           0xe

#ifndef OS_HARDWARE_PLATFORM
#define OS_HARDWARE_PLATFORM                                OS_CORTEX_AX
#endif

#if (defined (CHIP_BB_HI6758) || defined (CHIP_BB_HI6210))
#ifndef OS_CPU_TYPE
#define OS_CPU_TYPE                                         OS_CORTEX_A7
#endif
#else
#ifndef OS_CPU_TYPE
#define OS_CPU_TYPE                                         OS_CORTEX_A9
#endif
#endif
#ifndef OS_BYTE_ORDER
#define OS_BYTE_ORDER                                       OS_LITTLE_ENDIAN
#endif


#define LOW                                                 (1)
#define HIGH                                                (2)

/*
����оƬ���ĺ��������ڳ�ʼ��ʱָ��waitforallcores�����鳤�ȡ�
�˺��ڴ�ģ���ʼ����ɣ�֮���ʹ���û����õ��������������ú�������鳤�ȡ�
*/
#define OS_MAX_CORE_NUM                                     1

/*OS�Ƿ�֧�ֶ�˹���*/
#define OS_MULTI_CORE                                       NO

/*OS�Ƿ�֧��Э������*/
#define OS_OPTION_COPROCESSOR                               NO

/*OS�Ƿ�֧��DCACHE*/
#define OS_OPTION_DCACHE                                    YES

/*tick�ж��Ƿ����û������ͽӹ�*/
#define OS_OPTION_TICK_USR_MNG                              NO

/*�Ƿ���OS�ṩcycle����*/
#define OS_OPTION_SYS_CYCLE                                 NO

/*OS�Ƿ�֧�ִӿ�cache���������벻��cache�ڴ�*/
#define OS_OPTION_MEM_UNCACHE_ALLOC                         YES

/*����ջ����Ƿ�֧�������ʽ*/
#define OS_OPTION_STACK_MON_SOFT                            YES

/*OS�Ƿ�֧������ͬ��MSGM�Ĳ���*/
#define OS_OPTION_MSGM_SYN_PARA_RESET                       NO

/*OS�Ƿ�֧�ֲ�ѯͬ��MSGM��ʹ��״̬*/
#define OS_OPTION_MSGM_SYN_STATE_GET                        NO

/*OS�Ƿ�֧���ź����ݹ�PV����*/
#define OS_OPTION_SEM_RECUR_PV                              YES

/*OS�Ƿ�֧��LPͬ����Ϣ��ȡ����*/
#define OS_OPTION_LP_SYN_INFO_GET                           NO

/*OS�Ƿ�֧��LP���˸�λ����*/
#define OS_OPTION_LP_CORE_RESET                             NO

/*OS�Ƿ�֧��ϵͳ��CPUP*/
#define OS_OPTION_CPUP_SYS                                  YES

/*OS�Ƿ�֧���̼߳�CPUP*/
#define OS_OPTION_CPUP_THREAD                               YES

/*OS�Ƿ�֧��CPUP�澯*/
#define OS_OPTION_CPUP_WARN                                 YES

/*ʵ�����ʼ���׶�*/
#define OS_OPTION_INIT_PHASE_QUERY                          NO

/*OS�Ƿ�֧��clib��*/
#define OS_OPTION_LIBC                                      YES

/*OS�Ƿ�֧��IO�ӿ�*/
#define OS_OPTION_IO_INTF                                   YES

/*OS�Ƿ�֧��INIT TRACE��ӡ����*/
#define OS_OPTION_PRINT_INIT_TRACE_INFO                     YES

/*OS�Ƿ�֧��ssc�ڴ��㷨*/
#define OS_OPTION_SSC_MEM                                   NO

/*HUNT�Ƿ�ʹ��ʵ���乲���ڴ�*/
#define OS_OPTION_HUNT_INST_SHARE_MEM                       NO

/*OS�Ƿ�֧����Ϣ�ڴ����*/
#define OS_OPTION_MSG_MEM_RECLAIM                           NO

/*OS�Ƿ�֧��ֱ��ģʽӲ���ź���*/
#define OS_OPTION_HWSEM_DIRECT                              NO

/*OS�Ƿ�֧��Ӳ���ź����ĵ��˸�λ--HWSEM DELETE*/
#define OS_OPTION_HWSEM_CORE_RESET                          NO

/*OS�Ƿ�֧�ֺ˼��ź�������*/
#define OS_OPTION_MCSEM_RECLAIM                             NO

/*OS�Ƿ�֧��HUNT �ڴ����*/
#define OS_OPTION_HUNT_MEM_RECLAIM                          NO

/*OS�Ƿ�֧�ֹ���̬fsc�ڴ��ͷ�*/
#define OS_OPTION_MCSTA_FSCMEM_FREE                         NO

/*OS�Ƿ�֧��msgm��Դ���û�����*/
#define OS_OPTION_MSGM_USR_MNG                              NO

/*OS�Ƿ�֧�������ع���*/
#define OS_OPTION_TASK_MON                                  YES

/*OS�Ƿ�֧��ϵͳ���ٹ���*/
#define OS_OPTION_TRACE                                     YES

/*OS�Ƿ�֧�������ռ书��*/
#define OS_OPTION_NSM                                       NO

/*OS�Ƿ�֧���¼�����*/
#define OS_OPTION_EVENT                                     YES

/*OS�Ƿ�֧�ֶ��й���*/
#define OS_OPTION_QUEUE                                     YES

/*OSʹ�õİ�ȫC�⺯���ȼ�,
  NO   --δʹ��,
  LOW  --��ʹ��ʵ�ĺ���,
  HIGH --ʹ��ʵ�ĺͿ��ĺ���*/
#define OS_OPTION_SEC_C_LEVEL                               HIGH

/*OS�Ƿ�֧����Ϣ������*/
#define OS_OPTION_MSG_WHITE_LIST                            NO

/*OS�Ƿ�֧���ں�̬����*/
#define OS_OPTION_KERNEL_PROCESS                            NO

/*OS�Ƿ�֧���û�̬����*/
#define OS_OPTION_USR_PROCESS                               NO

/*OS�Ƿ�֧�����ж�*/
#define OS_OPTION_SWI                                       YES

/*OS�Ƿ�֧�ֿ����ź���*/
#define OS_OPTION_FSEM                                      YES

/*OS�Ƿ�֧���쳣�ӹ�*/
#define OS_OPTION_EXC                                       YES

/*OS�Ƿ�֧������ջ���*/
#define OS_OPTION_STACK_MON                                 YES

/*OS�Ƿ�֧�ֺ�����*/
#define OS_OPTION_CORESLEEP                                 YES

/*OS�Ƿ�֧�ַ��ű���Ч�˲���*/
#define OS_OPTION_SYMBOL_COREBITMAP                         NO

/*OS�Ƿ�֧��BM_SRE*/
#define OS_OPTION_BM_SRE                                    NO
/*OS�Ƿ�֧��log�ϱ�*/
#define OS_OPTION_LOG_REPORT                               NO
/* �����˶��Ƶ�Write error interrupt�жϺ�OS_EXC_WRITE_ERROR_INTERRUPT,
   �Ⱥ��������˶�֧�ָ��ж�֮���ٿ������������룬
   ����sre_exc_init.c�����øú괦��#ifɾ�� */
#define OS_EXC_WRITE_ERROR_INTERRUPT                        9

/****************************** ����ģ�� ****************************/
/**
 * CORTEX_A9(Balong C��) ƽ̨����֧��64�����ȼ����ֱ�Ϊ0-63��0��ʾ������ȼ���63��ʾ������ȼ���
 * IDLE����ʹ�ô����ȼ�(63)���û�Ӧ�����������ȼ�������
 */
#define OS_TSK_PRIORITY_HIGHEST                             0
#define OS_TSK_PRIORITY_LOWEST                              63
/**
*  CORTEX_A9 ƽ̨����֧�ֵ����ȼ���64��
*/
#define OS_TSK_NUM_OF_PRIORITIES                            64

#ifdef DEBUG
#define OS_DEBUG
#endif

#ifndef _WIN32
/* �������ϵͳ�Ĵ������ݷֶ� */
/*ָʾ����Ϊinlne����*/
#ifndef OS_SEC_ALW_INLINE
#define OS_SEC_ALW_INLINE           __attribute__((always_inline))
#endif

#ifndef OS_SEC_TEXT
#define OS_SEC_TEXT                 __attribute__((section(".os.text")))
#endif

#ifndef OS_KERNEL_TEXT
#define OS_KERNEL_TEXT              __attribute__((section(".os.kernel.text")))
#endif

#ifndef OS_SEC_TEXT_MINOR
#define OS_SEC_TEXT_MINOR           __attribute__((section(".os.minor.text")))
#endif

#ifndef OS_SEC_TEXT_MONITOR
#define OS_SEC_TEXT_MONITOR         __attribute__((section(".os.monitor.text")))
#endif

#ifndef OS_SEC_TEXT_INIT
#define OS_SEC_TEXT_INIT            __attribute__((section(".os.init.text")))
#endif

#ifndef OS_SEC_TEXT_NONCACHE
#define OS_SEC_TEXT_NONCACHE
#endif

#ifndef OS_SEC_DATA
#define OS_SEC_DATA                 __attribute__((section(".os.data")))
#endif

#ifndef OS_SEC_DATA_SHARED
#define OS_SEC_DATA_SHARED          __attribute__((section(".os.data")))
#endif

#ifndef OS_SEC_DATA_INIT
#define OS_SEC_DATA_INIT            __attribute__((section(".os.data")))
#endif

#ifndef OS_SEC_PRI_DATA_HSHELL
#define OS_SEC_PRI_DATA_HSHELL      __attribute__((section(".os.hshell.pri.data")))
#endif

#ifndef OS_SEC_BSS
#define OS_SEC_BSS                  __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_SHARED
#define OS_SEC_BSS_SHARED           __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_INIT
#define OS_SEC_BSS_INIT             __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_BACK
#define OS_SEC_BSS_BACK             __attribute__((section(".os.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_TEXT_HSHELL
#define OS_SEC_TEXT_HSHELL          __attribute__((section(".os.hshell.text")))
#endif

#ifndef OS_SEC_DATA_HSHELL
#define OS_SEC_DATA_HSHELL          __attribute__((section(".os.hshell.data")))
#endif

#ifndef OS_SEC_BSS_HSHELL
#define OS_SEC_BSS_HSHELL           __attribute__((section(".os.hshell.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_BSS_HSHELL_SVR
#define OS_SEC_BSS_HSHELL_SVR       __attribute__((section(".os.hshell.svr.bss, \"aw\", %nobits@")))
#endif

#ifndef OS_SEC_DATA_SYMBOL
#define OS_SEC_DATA_SYMBOL          __attribute__((section(".os.symbol.data")))
#endif

/* Hi1380 nocache data */
#ifndef OS_SEC_NC_DATA_SHARED
#define OS_SEC_NC_DATA_SHARED
#endif

/* Hi1380 nocache bss */
#ifndef OS_SEC_NC_BSS_SHARED
#define OS_SEC_NC_BSS_SHARED
#endif

/* Hi1380 test data */
#ifndef OS_SEC_TEST_DATA_SHARED
#define OS_SEC_TEST_DATA_SHARED
#endif

#ifndef PAT_SEC_DATA_SHARED
#define PAT_SEC_DATA_SHARED     __attribute__((section(".os.mcpatch.data")))
#endif

#ifndef PAT_SEC_BSS_SHARED
#define PAT_SEC_BSS_SHARED      __attribute__((section(".os.mcpatch.bss, \"aw\", %nobits@")))
#endif
#ifndef OS_SEC_BSS_INSTANCE_SHARED
#define OS_SEC_BSS_INSTANCE_SHARED   __attribute__((section(".os.over.inst.shared.bss, \"aw\", %nobits@")))
#endif
#define EXTERN_FAR extern

#define PACK1
#else
/*ָʾ����Ϊinlne����*/
#ifndef OS_SEC_ALW_INLINE
#define OS_SEC_ALW_INLINE
#endif

#ifndef OS_SEC_TEXT
#define OS_SEC_TEXT
#endif

#ifndef OS_KERNEL_TEXT
#define OS_KERNEL_TEXT
#endif

#ifndef OS_SEC_TEXT_MINOR
#define OS_SEC_TEXT_MINOR
#endif

#ifndef OS_SEC_TEXT_MONITOR
#define OS_SEC_TEXT_MONITOR
#endif

#ifndef OS_SEC_TEXT_INIT
#define OS_SEC_TEXT_INIT
#endif

#ifndef OS_SEC_TEXT_NONCACHE
#define OS_SEC_TEXT_NONCACHE
#endif

#ifndef OS_SEC_DATA
#define OS_SEC_DATA
#endif

#ifndef OS_SEC_DATA_SHARED
#define OS_SEC_DATA_SHARED
#endif

#ifndef OS_SEC_DATA_INIT
#define OS_SEC_DATA_INIT
#endif

#ifndef OS_SEC_PRI_DATA_HSHELL
#define OS_SEC_PRI_DATA_HSHELL
#endif

#ifndef OS_SEC_BSS
#define OS_SEC_BSS
#endif

#ifndef OS_SEC_BSS_SHARED
#define OS_SEC_BSS_SHARED
#endif

#ifndef OS_SEC_BSS_INIT
#define OS_SEC_BSS_INIT
#endif

#ifndef OS_SEC_BSS_BACK
#define OS_SEC_BSS_BACK
#endif

#ifndef OS_SEC_TEXT_HSHELL
#define OS_SEC_TEXT_HSHELL
#endif

#ifndef OS_SEC_DATA_HSHELL
#define OS_SEC_DATA_HSHELL
#endif

#ifndef OS_SEC_BSS_HSHELL
#define OS_SEC_BSS_HSHELL
#endif

#ifndef OS_SEC_BSS_HSHELL_SVR
#define OS_SEC_BSS_HSHELL_SVR
#endif

#ifndef OS_SEC_DATA_SYMBOL
#define OS_SEC_DATA_SYMBOL
#endif

/* Hi1380 nocache data */
#ifndef OS_SEC_NC_DATA_SHARED
#define OS_SEC_NC_DATA_SHARED
#endif

/* Hi1380 nocache bss */
#ifndef OS_SEC_NC_BSS_SHARED
#define OS_SEC_NC_BSS_SHARED
#endif

/* Hi1380 test data */
#ifndef OS_SEC_TEST_DATA_SHARED
#define OS_SEC_TEST_DATA_SHARED
#endif

#ifndef PAT_SEC_DATA_SHARED
#define PAT_SEC_DATA_SHARED
#endif

#ifndef PAT_SEC_BSS_SHARED
#define PAT_SEC_BSS_SHARED
#endif

#ifndef OS_SEC_BSS_INSTANCE_SHARED
#define OS_SEC_BSS_INSTANCE_SHARED
#endif
#define EXTERN_FAR extern

#define PACK1
#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#endif /* _SRE_BUILDEF_H */



