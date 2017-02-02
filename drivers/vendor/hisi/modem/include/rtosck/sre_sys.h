/**
 * @file sre_sys.h
 *
 * Copyright(C), 2008-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
 *
 * ������ϵͳģ��Ķ���ͷ�ļ��� \n
 */

/** @defgroup SRE_sys ϵͳ�������ܽӿ�
 *@ingroup SRE_kernel
 */

#ifndef _SRE_SYS_H
#define _SRE_SYS_H

#include "sre_base.h"
#include "sre_cache.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */

/**
 * @ingroup SRE_sys
 * ϵͳ��ʼ���׶θ�״̬����
 * uwInitPhase�ĸ�16λ��bit[31-16]Ϊ���ж����ϵͳ��ʼ���׶�״ֵ̬��
*/

/*********************************************ϵͳ��ʼ���׶�״̬********************************************************/
/**
 * @ingroup SRE_sys
 * ��ʾ��ʼ̬��
 *
 */
#define OS_DEFAULT_PHASE                                        (0x00)

/**
 * @ingroup SRE_sys
 * ��ʾ���˴���ʵģʽ�����׶�״̬���ý׶���Ҫ���MMUʹ�ܳ�ʼ��������SD6183ƽ̨��Ч��
 *
 */
#define OS_MCORE_PHY_BOOT_PHASE                                 (0x01)

/**
 * @ingroup SRE_sys
 * ��ʾ���˴�����ģʽ�����׶�״̬����SD6183ƽ̨��Ч��
 *
 */
#define OS_MCORE_VIR_BOOT_PHASE                                 (0x02)

/**
 * @ingroup SRE_sys
 * ��ʾ����SRE_HardBootInit��
 *
 */
#define OS_BOOT_PHASE                                           (0x03)

/**
 * @ingroup SRE_sys
 * ��ʾ��ʼ��ʵ�������������á�
 *
 */
#define OS_STARTPARAMCFG_PHASE                                  (0x04)

/**
 * @ingroup SRE_sys
 * ��ʾ�˳�SRE_HardBootInit��
 *
 */
#define OS_AFTER_BOOT_PHASE                                     (0x05)

/**
 * @ingroup SRE_sys
 * ��ʾ����BSS�γ�ʼ����
 *
 */
#define OS_BSSINIT_PHASE                                        (0x06)

/**
 * @ingroup SRE_sys
 * ��ʾDcache��ʼ����ϣ�SD6183ƽ̨������reset���Ѿ���ɣ��ʲ�֧�ָý׶�״̬��
 *
 */
#define OS_DCACHEINIT_PHASE                                     (0x07)

/**
 * @ingroup SRE_sys
 * ��ʾ����C lib���ʼ����
 *
 */
#define OS_LIBCINIT_PHASE                                       (0x08)

/**
 * @ingroup SRE_sys
 * ��ʾϵͳ�ڽ���OSģ��ע��׶Σ�ƥ��MOUDLE_ID֮�󣬱�ǽ���MODULE_ID��ע�ᡣ
 *
 */
#define OS_REGISTER_PHASE                                       (0x09)

/**
 * @ingroup SRE_sys
 * ��ʾϵͳ�ڽ���OSģ���ʼ���׶Σ�ƥ��MOUDLE_ID֮�󣬱�ǽ���MODULE_ID�ĳ�ʼ����
 *
 */
#define OS_INITIALIZE_PHASE                                     (0x0a)

/**
 * @ingroup SRE_sys
 * ��ʾϵͳ�ڽ��в�Ʒ������ʼ���׶Σ�ƥ��MOUDLE_ID֮�󣬱�ǽ���MODULE_ID�ĳ�ʼ����
 *
 */
#define OS_DEVDRVINIT_PHASE                                     (0x0b)

/**
 * @ingroup SRE_sys
 * ��ʾϵͳ�ڽ���OS�����׶Σ�ƥ��MOUDLE_ID֮�󣬱�ǽ���MODULE_ID��������
 *
 */
#define OS_START_PHASE                                          (0x0c)

/*
 * ϵͳģ��Ĵ����붨�塣
*/

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺ָ�����Ϊ�ա�
 *
 * ֵ: 0x02000001
 *
 * �������: ��������Ƿ�Ϊ��
 */
#define OS_ERRNO_SYS_PTR_NULL                               SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x01)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺ϵͳ��Ƶ���÷Ƿ���
 *
 * ֵ: 0x02000002
 *
 * �������: ��sre_config.h�����ú����ϵͳ��Ƶ��
 */
#define OS_ERRNO_SYS_CLOCK_INVALID                          SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x02)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺�û�������ѡ��OS_SYS_CORE_MAX_NUM����Ӧ�ú�оƬƥ�䣬��OS_SYS_CORE_MAX_NUMֵ���ܳ�����оƬ֧�ֵ���������
 *
 * ֵ: 0x02000003
 *
 * �������:�޸�����ѡ��OS_SYS_CORE_MAX_NUM����оƬƥ�䡣
 *
 */
#define OS_ERRNO_SYS_MAXNUMOFCORES_IS_INVALID               SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x03)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺�����Ѵﵽ��������ע������
 *
 * ֵ: 0x02000005
 *
 * �������:��������ע���IDLE��������
 *
 */
#define OS_ERRNO_SYS_HOOK_IS_FULL                           SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x05)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺��ȡϵͳʱ�亯��Cortex-AXƽ̨����ΪNULL��
 *
 * ֵ: 0x02000006
 *
 * �������:���û�ȡϵͳʱ�亯��ʱ��Cortex-AXƽ̨��������Ϊ��NULL��
 *
 */
#define OS_ERRNO_SYS_TIME_HOOK_NULL                         SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x06)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ�����:����ĸ������ô���
 *
 * ֵ: 0x02000007
 *
 * �������: �鿴ÿ���������õľ�������Ƿ���Ȼ��߾������Ϊ0���ߴ�������������
 *
 */
#define OS_ERRNO_SYS_IMAGE_NUM_INVALID                     SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x07)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ�����:����ľ���ID���ò����á�
 *
 * ֵ: 0x02000008
 *
 * �������: �鿴ÿ���������õľ���ID�Ƿ����ظ���������ֵ���󡣾���IDֵ���ܴ��ڵ��ھ��������
 *
 */
#define OS_ERRNO_SYS_IMAGE_ID_INVALID                      SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x08)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺�û�������ѡ��OS_SYS_CORE_MAX_NUM����Ӧ�ú�оƬƥ�䣬��OS_SYS_CORE_MAX_NUMֵ���ܳ�����оƬ֧�ֵ���������
 *
 * ֵ: 0x02000009
 *
 * �������:�޸�����ѡ��OS_SYS_CORE_MAX_NUM����оƬƥ�䡣
 *
 */
#define OS_ERRNO_SYS_CORERUNNUM_IS_INVALID                  SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x09)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺������ģ�鹦�ܺ�û�д򿪡�
 *
 * ֵ: 0x0200000a
 *
 * �������:�����Ӧ��ģ��Ĺ��ܺꡣ
 *
 */
#define OS_ERRNO_SYS_MODE_CLOSE                             SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0a)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺���õ�ϵͳջ��С��
 *
 * ֵ: 0x0200000b
 *
 * �������:���������õ�ϵͳջ��С��
 *
 */
#define OS_ERRNO_SYS_STACK_SIZE_NOT_ENOUGH                  SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0b)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺����(ջ)��ع��ܺ�����������ģ�鹦��δ�򿪡�
 *
 * ֵ: 0x0200000c
 *
 * �������:�������������ģ��ü������Ƿ�򿪡�
 *
 */
#define OS_ERRNO_SYS_TASK_CLOSE                             SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0c)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺��������������ܿ������Ĺ���������δ�򿪡�
 *
 * ֵ: 0x0200000d
 *
 * �������:��������������زü������Ƿ�򿪡�
 *
 */
#define OS_ERRNO_SYS_TASKMON_CLOSE                          SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0d)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺����๦�ܿ������Ĺ���TICKδ�򿪡�
 *
 * ֵ: 0x0200000e
 *
 * �������:���������TICK�ü������Ƿ�򿪡�
 *
 */
#define OS_ERRNO_SYS_TICK_CLOSE                             SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0e)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺CPUP�澯���ܿ������Ĺ���CPUPδ�򿪡�
 *
 * ֵ: 0x0200000f
 *
 * �������:���������CPUP�ü������Ƿ�򿪡�
 *
 */
#define OS_ERRNO_SYS_CPUP_CLOSE                             SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0f)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺���õ��û�ģʽջ��С��
 *
 * ֵ: 0x0200000e
 *
 * �������:���������õ��û�ģʽջ��С��
 *
 */
#define OS_ERRNO_SYS_USER_STACK_SIZE_NOT_ENOUGH             SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0e)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺���õ�ϵͳģʽ����ȷ��
 *
 * ֵ: 0x0200000f
 *
 * �������:ϵͳģʽ����Ϊsuperģʽ����userģʽ��
 *
 */
#define OS_ERRNO_SYS_MODE_INVALID                           SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x0f)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺ϵͳ��CPUP���ü�
 *
 * ֵ: 0x02000010
 *
 * �������:�ų�config���Ƿ���ȷ����ƽ̨��֧��ϵͳ��CPUP
 *
 */
#define OS_ERRNO_SYS_NO_CPUP_SYS                            SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x10)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺CPUP�澯���ü�
 *
 * ֵ: 0x02000011
 *
 * �������:�ų�config���Ƿ���ȷ����ƽ̨��֧��CPUP�澯
 *
 */
#define OS_ERRNO_SYS_NO_CPUP_WARN                           SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x11)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺�̼߳�CPUP���ü�
 *
 * ֵ: 0x02000012
 *
 * �������:�ų�config���Ƿ���ȷ����ƽ̨��֧���̼߳�CPUP
 *
 */
#define OS_ERRNO_SYS_NO_CPUP_THREAD                         SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x12)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺��ȡ�������Ӧ�˳�ʼ���׶�״̬ʱ���˺Ŵ���
 *
 * ֵ: 0x02000013
 *
 * �������:ȷ����κ˺Ų��ܴ��ڵ���OS_MAX_CORE_NUM��
 *
 */
#define OS_ERRNO_SYS_COREID_INVALID                         SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x13)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺��ηǷ�������ָ��ΪNULL��
 *
 * ֵ: 0x02000014
 *
 * �������:ȷ�����õ�ʵ���乲���ڴ�ռ��ַ��ΪNULL��
 *
 */
#define OS_ERRNO_SYS_INST_SHMEM_PTR_NULL                    SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x14)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺����ʵ���乲��UNCACHE�ռ��׵�ַδ4�ֽڶ��롣
 *
 * ֵ: 0x02000015
 *
 * �������:ȷ�����õ�ʵ���乲��UNCACHE�ռ��׵�ַ4�ֽڶ��롣
 *
 */
#define OS_ERRNO_SYS_INST_SHMEM_ADDR_NOT_ALIGN              SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x15)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺����ʵ���乲��UNCACHE�ռ��Сδ4�ֽڶ��롣
 *
 * ֵ: 0x02000016
 *
 * �������:ȷ�����õ�ʵ���乲��UNCACHE�ռ��С4�ֽڶ��롣
 *
 */
#define OS_ERRNO_SYS_INST_SHMEM_SIZE_NOT_ALIGN              SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x16)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺ʵ���乲��UNCACHE�ռ������ַ��ת��
 *
 * ֵ: 0x02000017
 *
 * �������:ȷ�����õ�ʵ���乲��UNCACHE�ռ������ַ��Ҫ��ת��
 *
 */
#define OS_ERRNO_SYS_INST_SHMEM_REGION_OVERTURN             SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x17)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺ʵ���乲��UNCACHE�ռ��С̫С��
 *
 * ֵ: 0x02000018
 *
 * �������:�������õ�ʵ���乲��UNCACHE�ռ��С��
 *
 */
#define OS_ERRNO_SYS_INST_SHMEM_SIZE_TOO_SMALL              SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x18)


/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺����ģ���Ѿ����ü�
 *
 * ֵ: 0x02000019
 *
 * �������:�ų�config���Ƿ���ȷ����ƽ̨��֧�ֶ��У���Ҫ��������OS_INCLUDE_QUEUE����ΪNO��
 *
 */
#define OS_ERRNO_SYS_NO_QUEUE                               SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x19)


/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺������ģ���Ѿ����ü���
 *
 * ֵ: 0x0200001a
 *
 * �������:�ų�config���Ƿ���ȷ����ƽ̨��֧�������أ���Ҫ��������OS_INCLUDE_TSKMON����ΪNO��
 *
 */
#define OS_ERRNO_SYS_NO_TASK_MON                            SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x1a)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺ϵͳ����ģ���Ѿ����ü���
 *
 * ֵ: 0x0200001b
 *
 * �������:�ų�config���Ƿ���ȷ����ƽ̨��֧��ϵͳ���٣���Ҫ��������OS_TRACE_INCLUDE����ΪNO��
 *
 */
#define OS_ERRNO_SYS_NO_TRACE                               SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x1b)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺���ж�ģ���Ѿ����ü���
 *
 * ֵ: 0x0200001c
 *
 * �������:�ų�config���Ƿ���ȷ����ƽ̨��֧�����жϣ����뽫������OS_TASK_INCLUDE����ΪYES��
 *
 */
#define OS_ERRNO_SYS_NO_SWI                                SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x1c)


/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺init traceģ�����ֿռ��������ʧ�ܡ�
 *
 * ֵ: 0x0200001d
 *
 * �������:�������ֿռ��С��
 *
 */
#define OS_ERRNO_SYS_INIT_TRACE_NAME_ALLOC_FAIL            SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x1d)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺init traceģ�����ֿռ�������ʧ�ܡ�
 *
 * ֵ: 0x0200001e
 *
 * �������:ȷ�����ֿռ�����ֶ����Ѿ�������
 *
 */
#define OS_ERRNO_SYS_INIT_TRACE_NAME_FIND_FAIL            SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x1e)

/**
 * @ingroup SRE_sys
 * ϵͳ�������ܴ����룺init trace�ӿ�ֻ�������˵��á�
 *
 * ֵ: 0x0200001f
 *
 * �������:�ޡ�
 *
 */
#define OS_ERRNO_SYS_INIT_TRACE_ONLY_INVOKED_BY_MCPU            SRE_ERRNO_OS_ERROR(OS_MID_SYS, 0x1f)


/**
 * @ingroup SRE_sys
 * ÿ�������
 */
#define SRE_SYS_MS_PER_SECOND         1000

/**
 * @ingroup SRE_sys
 * ÿ��΢����
 */
#define SRE_SYS_US_PER_SECOND         1000000

/**
 * @ingroup SRE_sys
 * OS�汾��
 */
#define OS_SYS_OS_VER_LEN             48

/**
 * @ingroup SRE_sys
 * ��Ʒ�汾��
 */
#define OS_SYS_APP_VER_LEN            64

/**
 * @ingroup SRE_sys
 * ϵͳʱ��
 */
extern UINT32 g_uwSystemClock;

/**
 * @ingroup SRE_sys
 * ����ϵͳTick����ֵ
 */
extern UINT64 g_ullUniTicks;

/**
 * @ingroup  SRE_sys
 * @brief ת��cycleΪ���롣
 *
 * @par ����:
 * ת��cycleΪ���롣
 *
 * @attention ��
 *
 * @param  udwCycle    [IN] ����Ϊ#UINT64��cycle����
 *
 * @retval [0,0xFFFFFFFFFFFFFFFF] ת����ĺ�������
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_Cycle2US
 */
OS_SEC_ALW_INLINE INLINE UINT64 SRE_Cycle2MS(UINT64 udwCycle)
{
    return (UINT64)((udwCycle/(g_uwSystemClock/SRE_SYS_MS_PER_SECOND)));
}

/**
 * @ingroup  SRE_sys
 * @brief ת��cycleΪ΢�롣
 *
 * @par ����:
 * ת��cycleΪ΢�롣
 *
 * @attention ��
 *
 * @param  udwCycle    [IN] ����Ϊ#UINT64��cycle����
 *
 * @retval [0,0xFFFFFFFFFFFFFFFF] ת�����΢������
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_Cycle2MS
 */
OS_SEC_ALW_INLINE INLINE UINT64 SRE_Cycle2US(UINT64 udwCycle)
{
    return (UINT64)((udwCycle/(g_uwSystemClock/SRE_SYS_US_PER_SECOND)));
}

/**
 * @ingroup  SRE_sys
 * @brief ��ȡ���˵�tick����˽�е�ַ��
 *
 * @par ����:
 * ��ȡ���˵�tick����˽�е�ַ��
 *
 * @attention ��
 *
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
#define SRE_GetTickAddr()   ((UINT32)(UINT32 *)&g_ullUniTicks)

/**
 * @ingroup  SRE_sys
 * @brief ��ȡ��ǰ��tick������
 *
 * @par ����:
 * ��ȡ��ǰ��tick������
 *
 * @attention ��
 *
 * @param  ��
 *
 * @retval  [0,0xFFFFFFFFFFFFFFFF] ��ǰ��tick������
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_CycleCountGet
 */
extern UINT64 SRE_TickCountGet(VOID);

/**
 * @ingroup SRE_sys
 * @brief ��ȡÿ��tick��Ӧ��Ӳ��cycle����
 *
 * @par ����:
 * ��ȡÿ��tick��Ӧ��Ӳ��cycle����
 *
 * @attention ��
 *
 * @param  ��
 *
 * @retval [0,0xFFFFFFFF] ÿ��tick��Ӧ��Ӳ��cycle����
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern UINT32 SRE_CyclePerTickGet(VOID);

/**
 * @ingroup SRE_sys
 * @brief �ӳ�ʱ��(��λcycle)��
 *
 * @par ����:
 * �ӳ�ʱ��(��λcycle)��
 *
 * @attention
 * <ul>
 * <li>����Cortex-AXƽ̨���ù���������sre_config.h�е�������OS_SYS_TIME_HOOK���õĻ�ȡϵͳʱ�亯�����ܡ�</li>
 * <li>����Cortex-AXƽ̨����λcycleΪ��ȡϵͳʱ��ʹ�õĶ�ʱ��һ��step��</li>
 * </ul>
 *
 * @param  uwCycles    [IN] ����Ϊ#UINT32���ӳ�cycle��
 *
 * @retval ��
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern VOID SRE_DelayCycle(UINT32 uwCycles);

/**
 * @ingroup SRE_sys
 * @brief �ӳ�ʱ��(��λ΢��)��
 *
 * @par ����:
 * �ӳ�ʱ��(��λ΢��)��
 *
 * @attention
 * <ul>
 * <li>����Cortex-AXƽ̨���ù���������sre_config.h�е�������OS_SYS_TIME_HOOK���õĻ�ȡϵͳʱ�亯�����ܡ�</li>
 * <li>����Cortex-AXƽ̨����Ҫ��֤���Ӻ���ʹ�õĶ�ʱ����Ƶ��������OS_SYS_CLOCKһ�¡�</li>
 * </ul>
 *
 * @param  uwDelay    [IN] ����Ϊ#UINT32���ӳ�΢������
 *
 * @retval ��
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DelayMs
 */
extern VOID SRE_DelayUs(UINT32 uwDelay);

/**
 * @ingroup SRE_sys
 * @brief �ӳ�ʱ��(��λ����)��
 *
 * @par ����:
 * �ӳ�ʱ��(��λ����)��
 *
 * <li>����Cortex-AXƽ̨���ù���������sre_config.h�е�������OS_SYS_TIME_HOOK���õĻ�ȡϵͳʱ�亯�����ܡ�</li>
 * <li>����Cortex-AXƽ̨����Ҫ��֤���Ӻ���ʹ�õĶ�ʱ����Ƶ��������OS_SYS_CLOCKһ�¡�</li>
 *
 * @param  uwDelay    [IN] ����Ϊ#UINT32���ӳٺ�������
 *
 * @retval ��
 * @par ����:
 * <ul><li>SRE_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_DelayUs
 */
extern VOID SRE_DelayMs(UINT32 uwDelay);

/**
 * @ingroup SRE_sys
 * @brief ϵͳ�������Ӻ��������Ͷ��塣
 *
 * @par ����:
 * �û�ͨ��ϵͳ�������Ӻ��������Ͷ���ϵͳ�������ӣ���ϵͳ����֮ǰ���øù��ӡ�
 *
 * @attention �ޡ�
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see �ޡ�
*/
typedef VOID ( *SYS_REBOOT_FUNC )(VOID);

/**
 * @ingroup SRE_sys
 * @brief IDLEѭ�����ӵ����Ͷ��塣
 *
 * @par ����:
 * �û�ͨ��IDLEѭ�����ӵĺ������Ͷ��庯����ϵͳ�ڽ���IDLEѭ��֮ǰ���øù��ӡ�
 *
 * @attention �ޡ�
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see �ޡ�
*/
typedef VOID (* OS_IDLE_HOOK)(VOID);

/**
 * @ingroup SRE_sys
 * @brief ����ϵͳ����ʱ�乳�Ӻ��������Ͷ��塣
 *
 * @par ����:
 * ������Cortex-AXƽ̨OSû�нӹ�Ӳ����ʱ������Ҫ�û��ṩ����ϵͳʱ��Ĺ��Ӻ�����
 *
 * @attention ��ȡ����64bit cycles ���ݡ�
 *
 * @param  ��
 *
 * @retval ϵͳ����ʱ��
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see �ޡ�
*/
typedef UINT64 ( *SYS_TIME_FUNC )(VOID);

/**
 * @ingroup SRE_sys
 * ϵͳģ��������Ϣ�Ľṹ�嶨�塣
 *
 * ����ϵͳģ�����������Ϣ��
 */
typedef struct tagSysModInfo
{
    UINT32 uwSystemClock;                            /**< CPU��Ƶ��ʱ������              */
    UINT8  ucCoreID;                                 /**< ��ǰ��ID                       */
    UINT8  ucCoreRunNum;                             /**< ʵ�����еĺ���                 */
    UINT8  ucCoreMaxNum;                             /**< ���֧�ֵĺ���                 */
    UINT8  ucCoreMaster;                             /**< ����ID                         */
    SYS_REBOOT_FUNC pfnRebootHook;                   /**< �û�ע��ĵ��帴λ����         */
    OS_IDLE_HOOK pfnIdleHook;                        /**< �û�ע���IDLE���Ӻ���         */
    SYS_TIME_FUNC pfnSysTimeHook;                    /**< �û�ע��Ļ�ȡϵͳʱ�亯��     */
    UINT8  ucCpuType;                                /**< CPU type                       */
    UINT8  ucReserve;                                /**< ����Ԥ��                       */
    UINT16 usIdleHookMaxNum;                         /**< �û�ע�����IDLE��������     */
    UINT16 usImageNum;                               /**< �������������о���Ҫһ��   */
    UINT16 usImageId;                                /**< ��ǰ����ID                     */
} SYS_MOD_INFO_S;

#if (OS_CPU_TYPE == OS_SD6182 || OS_CPU_TYPE == OS_SD6157)
/**
 * @ingroup SRE_sys
 * ϵͳջ������Ϣ�Ľṹ�嶨�塣
 *
 * ����ϵͳģ�����������Ϣ��
 */
typedef struct tagSysStackInfo
{
    UINT32 uwSystemStackAddr;                        /**< ϵͳջ��ʼ��ַ                 */
    UINT32 uwSystemStackSize;                        /**< ϵͳջ��С                     */
} SYS_STACK_INFO_S;
#endif

#if (OS_CPU_TYPE == OS_SD6183)
/**
 * @ingroup SRE_sys
 * ϵͳջ������Ϣ�Ľṹ�嶨�塣
 *
 * ����ϵͳģ�����������Ϣ��
 */
typedef struct tagUserModeStackInfo
{
    UINT32 uwUserModeStackAddr;                        /**< �û�ģʽջ��ʼ��ַ           */
    UINT32 uwUserModeStackSize;                        /**< �û�ģʽջ��С               */
} SYS_USER_MODE_STACK_INFO_S;

//������Ҫ�ڴӺ�����ǰ���������ݷ��ڰ汾�ռ���
typedef  struct tagSlvCoreBootPara
{
    UINT32  uwMcpuId;           /**����ID                     */
    UINT32  uwGlbNsmAddr;       /**���õ�ʵ���乲���ڴ��׵�ַ */
    UINT32  uwGlbNsmStart;      /**���ֿռ������׵�ַ         */
    UINT32  uwInstId;           /**ʵ��ID                     */
    UINT32  uwPgId;             /**������ID                   */
    UINT32  uwOldStack;         /**����ǰ�������ɵ�ϵͳջ��   */
    UINT32  uwOldStackEntry;    /**����ǰ�������ɵ�ϵͳջ��   */
    UINT32  uwInitTraceAddr;    /**�Ӻ˳�ʼ��trace������ַ    */
    UINT32  uwMagicWordAddr;    /**�Ӻ˹�CDA������ħ���ֵ�ַ  */
}SLV_CORE_BOOTPARA_S;

typedef struct tagMemOutputCfg
{
    //���¸�����������ã�ÿ���˿������ò�ͬ
    UINT32 uwSysStackAreaVirAddr;    //ϵͳջ��ַ
    UINT32 uwSysStackAreaSize;       //ϵͳջ��С
    UINT32 uwTskStackAreaVirAddr;    //ϵͳջ��ַ
    UINT32 uwTskStackAreaSize;       //��������ջ��С
    UINT32 uwFscPtVirAddr;           //˽��FSC������ַ
    UINT32 uwFscPtSize;              //˽��FSC������С

    UINT32 uwTraceAreaVirAddr;       //Trace�ڴ�����
    UINT32 uwTraceAreaSize;          //Trace�ڴ��С

    UINT32 uwMmuPhy2VirAreaSize;     //MMU�����ַ�������ַת��ӳ����С
    UINT32 uwMmuPhy2VirAreaVirAddr;  //MMU�����ַ�������ַת��ӳ����ַ

    //���¸������ʵ�����ã�ʵ����ÿ����������ͬ
    UINT32 uwMcFscPtVirAddr;       //����̬FSC������ַ
    UINT32 uwMcFscPtSize;          //����̬FSC������С
    UINT32 uwLPShareNcPtVirAddr;   //����������ַ
    UINT32 uwLPShareNcPtSize;      //����������С��

    //���¸������������(image)���ã���������ÿ����������ͬ
    UINT32 uwSymTblNcPtVirAddr;    //���ű��ڴ������ַ
    UINT32 uwSymTblNcPtSize;       //���ű��ڴ������С���������ڸ�����������ͬ
} OS_MEM_OUTPUT_CFG_S;

#endif

#if (OS_OPTION_HUNT_INST_SHARE_MEM == YES)
/**
 * @ingroup SRE_sys
 * SD6183 ʵ���乲��uncache�ռ䴴���Ľṹ�嶨�塣
 */
typedef struct tagInstShMemModInfo
{
    VOID  *pStart;               /**< ʵ���乲��uncache�ռ���ʼ��ַ������hunt������ */
    UINT32 uwSize;               /**< ʵ���乲��uncache�ռ��С                     */
}INST_SHARED_MEM_MOD_INFO_S;
#endif

/**
 * @ingroup SRE_sys
 * ϵͳģ���߳����ͻ�ȡö�ٽṹ����
 *
 * ϵͳģ���߳����ͻ�ȡ
 */
typedef enum
{
    SYS_HWI,       /**<��ǰ�߳���������Ӳ�ж�*/
    SYS_SWI,       /**<��ǰ�߳������������ж�*/
    SYS_TASK,      /**<��ǰ�߳�������������*/
    SYS_KERNEL,    /**<��ǰ�߳����������ں�*/
    SYS_BUTT
}OS_THREAD_TYPE_E;

/**
 * @ingroup SRE_sys
 * @brief ��λ���塣
 *
 * @par ����:
 * ��λ���壬�������¼���ִ�С�
 *
 * @attention
 * <ul>
 * <li>����ֱ�Ӹ�λ���壬���ǹ��жϣ��ȴ����Ź���λ��</li>
 * <li>�û�����ͨ��������OS_SYS_REBOOT_HOOK�ҽӸ�λ������</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ��
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see ��
 */
extern VOID SRE_Reboot(VOID);

/**
 * @ingroup SRE_sys
 * ϵͳ��ʼ���׶���Ϣ�����ṹ�嶨�塣
 *
 * ���ڱ�ǵ�ǰϵͳ���е��ĸ��׶�,uwInitPhase = OS_INIT_PHASE | MODULE_ID;
 * OS_INIT_PHASE��ʾϵͳ��ʼ���׶�״̬bit[31-16]; MODULE_ID��ʾ��ǰϵͳ��ʼ����ģ���bit[0-15]������ģ�����sre_module.h���ж��塣
 * ��¼ϵͳģ���Ƿ���ɳ�ʼ����0-63λ������¼�ѽ��г�ʼ��������ģ���ģ��ţ���ĳ��ģ������˳�ʼ������������ģ��Ŷ�Ӧ��λ��Ϊ1��
 * auwInitTrace[0] : ��ʾģ���Ϊ0~31��auwInitTrace[1] : ��ʾģ���Ϊ32~63,���ٵ��ǵ�ǰϵͳ�и�ģ��ĳ�ʼ���������Լ�ϵͳ��ʼ��
 * ���׶�״̬��ʵʱֵ��
 */
typedef struct tagSysTraceInfo
{
    UINT32 uwInitMagicWord;         /**< ��ʼ���׶ι�CDA������Ϣ��ħ����                                                                    */
    UINT32 uwInitPhase;             /**< ��ǰ�˳�ʼ���׶�״̬��ʶ���ڱ�ǵ�ǰϵͳ���е��ĸ��׶�,uwInitPhase = OS_INIT_PHASE | MODULE_ID;
                                         OS_INIT_PHASE��ʾϵͳ��ʼ���׶�״̬bit[31-16]��MODULE_ID��ʾ��ǰϵͳ��ʼ����ģ���bit[0-15]��      */
    UINT32 auwInitTrace[2];         /**< ��ǰ�˳�ʼ��������ģ����и��ٱ�ʶ��¼ϵͳģ���Ƿ���ɳ�ʼ����[0]bit0-31,[1]bit32~63������¼
                                         �ѽ��г�ʼ��������ģ���ģ��ţ���ĳ��ģ������˳�ʼ������������ģ��Ŷ�Ӧλ����1��                */
    UINT32 uwErrNo;                 /**< ��ʼ���׶δ����뷵��ֵ��¼                                                                         */
}SYS_INIT_TRACE_INFO_S;

/**
 * @ingroup SRE_sys
 * ϵͳ��ʼ��Trace��Ϣ��
 *
 * ϵͳ��ʼ��Trace��Ϣ��
 */
extern SYS_INIT_TRACE_INFO_S  stSysInitTraceInfo;

/**
 * @ingroup SRE_sys
 * ��ǰ��ID��
 *
 * ��IDΪӲ���Ĵ����е�ID�š�
 */
extern UINT8 g_ucLocalCoreID;

/**
 * @ingroup  SRE_sys
 * @brief ��ȡ��ǰ��ID��
 *
 * @par ����:
 * ��ȡ��ǰ��ID��
 *
 * @attention
 * <ul>
 * <li>��ȡ�ĺ�IDΪӲ���Ĵ����е�ID�š�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval �����ID��
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_GetNumberOfCores | SRE_GetMasterCore
 */
#define SRE_GetCoreID()          ((UINT8)(g_ucLocalCoreID + (UINT8)0))

/**
 * @ingroup SRE_sys
 * ����ID��
 *
 * ��IDΪӲ���Ĵ����е�ID�š�
 */
extern UINT8 g_ucMasterCoreID;

/**
 * @ingroup  SRE_sys
 * @brief ��ȡ����ID��
 *
 * @par ����:
 * ��ȡ����ID��
 *
 * @attention
 * <ul>
 * <li>��ȡ�ĺ�IDΪӲ���Ĵ����е�ID�š�</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval �����ID��
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_GetNumberOfCores | SRE_GetCoreID
 */
#define SRE_GetMasterCore()      ((UINT8)(g_ucMasterCoreID + (UINT8)0))

 /**
 * @ingroup SRE_sys
 * ʵ�����еĺ�����
 *
 * ʵ�����еĺ�����������RTOSck���֧�ֵĺ�����
 */
extern UINT8 g_ucNumOfCores;

 /**
 * @ingroup SRE_sys
 * ����֧�����еĺ�����
 *
 * ΪRTOSck���֧�ֵĺ�����������RTOSckʵ�����еĺ�����
 */
extern UINT8 g_ucMaxNumOfCores;
/**
 * @ingroup  SRE_sys
 * @brief ��ȡʵ�����еĺ�����
 *
 * @par ����:
 * ��ȡʵ�����еĺ�����
 *
 * @attention
 * <ul>
 * <li>��ȡ��Ϊʵ�����еĺ�����������OS���֧�ֵĺ�����</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ������
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since  RTOSck V100R001C01
 * @see SRE_GetCoreID | SRE_GetMasterCore
 */
#define SRE_GetNumberOfCores()       ((UINT8)(g_ucNumOfCores + (UINT8)0))

/**
 * @ingroup  SRE_sys
 * @brief ��ȡ����֧�����еĺ�����
 *
 * @par ����:
 * ��ȡ����֧�����еĺ�����
 *
 * @attention
 * <ul>
 * <li>��ȡ��ΪOS���֧�ֵĺ�����������OSʵ�����еĺ�����</li>
 * </ul>
 *
 * @param  ��
 *
 * @retval ������
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since  RTOSck V100R001C01
 * @see SRE_GetCoreID | SRE_GetMaxNumberOfCores
 */
#define SRE_GetMaxNumberOfCores()     ((UINT8)(g_ucMaxNumOfCores + (UINT8)0))

/**
 * @ingroup  SRE_sys
 * @brief ��ȡϵͳ����Ƶ��
 *
 * @par ����:
 * ��ȡϵͳ����Ƶ��
 *
 * @attention
 *
 * @param
 *
 * @retval ϵͳ��Ƶ
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_GetCoreID
 */
extern UINT32 SRE_GetSysClk(VOID);

/**
 * @ingroup  SRE_sys
 * @brief ��ȡOS�İ汾�š�
 *
 * @par ����:
 * ��ȡOS�İ汾�š��汾��Ÿ�ʽΪRTOSck Vx00R00xCxx SVNID(XXX)��
 *
 * @attention ��
 *
 * @param  ��
 *
 * @retval ָ��OS�汾�ŵ��ַ���ָ�롣 �磺RTOSck V100R001C01 SVNID (XXX) ��
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SetAppVersion | SRE_GetAppVersion
 */
extern CHAR * SRE_GetOsVersion(VOID);

/**
 * @ingroup  SRE_sys
 * @brief ע��Ӧ�ó���İ汾�š�
 *
 * @par ����:
 * ע��Ӧ�ó���İ汾�š�
 *
 * @attention
 * <ul>
 * <li>ϵͳAPP�汾�ű�����ȫ�������У��������õ�APP�汾����󳤶�Ϊ64�ֽ�(���������ַ�)��</li>
 * </ul>
 *
 * @param  pcAppVersion [IN] ����#CHAR *��ָ��Ӧ�ó���汾�ŵ��ַ���ָ�롣
 *
 * @retval #OS_ERRNO_SYS_PTR_NULL           0x02000001��ָ�����Ϊ�ա�
 * @retval #SRE_OK                          0x02000000��ע��APP�汾�ųɹ���
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_GetAppVersion | SRE_GetOsVersion
 */
extern UINT32 SRE_SetAppVersion(CHAR *pcAppVersion);

/**
 * @ingroup  SRE_sys
 * @brief ��ȡӦ�ó���İ汾�š�
 *
 * @par ����:
 * ��ȡӦ�ó���İ汾�š�
 *
 * @attention ��֮ǰδע�ᣬ�򷵻�ָ��"Unknown"��ָ�롣
 *
 * @param  ��
 *
 * @retval ָ��Ӧ�ó���汾�ŵ��ַ���ָ�롣
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_SetAppVersion | SRE_GetOsVersion
 */
extern CHAR * SRE_GetAppVersion(VOID);

/**
 * @ingroup  SRE_sys
 * @brief ��cycleֵת���ɺ��롣
 *
 * @par ����:
 * ��cycleֵת���ɺ��롣
 *
 * @attention
 * <ul>
 * <li>��ϵͳ��Ƶ��Ϊ1000������ʱ���ýӿڻ�ȡ����ms������</li>
 * </ul>
 *
 * @param  pstCpuTick [IN] ����#CPU_TICK *����ת����cycle������ַ��
 * @param  puwMsHi [OUT] ����#UINT32 *���������ĸ�32λ�ĵ�ַ��
 * @param  puwMsLo [OUT] ����#UINT32 *���������ĵ�32λ�ĵ�ַ��
 *
 * @retval #OS_ERRNO_SYS_PTR_NULL           0x02000001��ָ�����Ϊ�ա�
 * @retval #SRE_OK                          0�������ɹ���
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_CpuTick2US
 */
extern UINT32 SRE_CpuTick2MS(CPU_TICK *pstCpuTick, UINT32 *puwMsHi, UINT32 *puwMsLo);

/**
 * @ingroup  SRE_sys
 * @brief ��cycleֵת����΢�롣
 *
 * @par ����:
 * ��cycleֵת����΢�롣
 *
 * @attention ��
 *
 * @param  pstCpuTick [IN] ����#CPU_TICK *����ת����cycle������ַ��
 * @param  puwUsHi [OUT] ����#UINT32 *������΢��ĸ�32λ�ĵ�ַ��
 * @param  puwUsLo [OUT] ����#UINT32 *������΢��ĵ�32λ�ĵ�ַ��
 *
 * @retval #OS_ERRNO_SYS_PTR_NULL           0x02000001��ָ�����Ϊ�ա�
 * @retval #SRE_OK                          0x00000000�������ɹ���
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_CpuTick2MS
 */
extern UINT32 SRE_CpuTick2US(CPU_TICK *pstCpuTick, UINT32 *puwUsHi, UINT32 *puwUsLo);

/**
 * @ingroup  SRE_sys
 * @brief ��ȡϵͳ��ǰ�߳����͡�
 *
 * @par ����:
 * ��ȡϵͳ��ǰ�߳����͡�
 *
 * @attention ��
 *
 * @param  �ޡ�
 *
 * @retval #OS_THREAD_TYPE_E                    �߳����͡�
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see ��
 */
extern OS_THREAD_TYPE_E  SRE_CurThreadType(VOID);

/**
 * @ingroup  SRE_sys
 * @brief ע��IDLEѭ������ǰ���õĹ��ӡ�
 *
 * @par ����:
 * Ϊ����ע��IDLEѭ������ǰ���õĹ��ӣ��ù���ֻ�ᱻ����һ�Ρ�
 *
 * @attention
 * <ul>
 * <li>ע��Ĺ���ֻ�ڽ���IDLEѭ��ǰִ��һ�Ρ�</li>
 * <li>������δ�ü��������õ�������IDLEѭ���������񱻲ü��������õ������ж�IDLEѭ����</li>
 * <li>IDLE��������ʹ��ʸ���Ĵ�����Ҫ��ǰ�ù����е���#SRE_TaskCpSaveCfg�ӿ�����ʸ�����������ı�������</li>
 * <li>IDLE���жϹ�����ʹ��ʸ���Ĵ�����Ҫ��ǰ�ù����е���#SRE_SwiCpSaveCfg�ӿ�����ʸ�����������ı�������</li>
 * </ul>
 *
 * @param  pfnHook    [IN] ����Ϊ#OS_IDLE_HOOK�����Ӻ�����
 *
 * @retval #OS_ERRNO_SYS_PTR_NULL           0x02000001��ָ�����Ϊ�ա�
 * @retval #SRE_OK                          0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R001C01
 * @see SRE_IdleHookAdd
 */
extern UINT32 SRE_IdlePrefixHookAdd(OS_IDLE_HOOK pfnHook);

/**
 * @ingroup  SRE_sys
 * @brief ע��IDLEѭ���е��õĹ���
 *
 * @par ����:
 * ע����IDLE�����IDLE���ж�ѭ���е��õĹ��Ӻ�����
 *
 * @attention
 * <ul>
 * <li>�����в��ܵ������������������л��ĺ�����</li>
 * </ul>
 *
 * @param  pfnHook [OUT] ����#OS_IDLE_HOOK��IDLE���Ӻ������ò�������Ϊ�ա�
 *
 * @retval #OS_ERRNO_HOOK_TYPE_INVALID      0x02001600��HOOK���ʹ���
 * @retval #OS_ERRNO_HOOK_PTR_NULL          0x02001602��HOOKָ��ա�
 * @retval #SRE_OK                          0x00000000�������ɹ���
 *
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_IdleHookDel
 */
#define SRE_IdleHookAdd(pfnHook) SRE_HookAdd(OS_HOOK_IDLE_PERIOD, (OS_VOID_FUNC)(OS_IDLE_HOOK)pfnHook)

/**
 * @ingroup  SRE_sys
 * @brief ɾ��IDLEѭ���е��õĹ���
 *
 * @par ����:
 * ɾ����IDLE�����IDLE���ж�ѭ���е��õĹ��Ӻ�����
 *
 * @attention
 *<ul>
 * ��
 * </ul>
 *
 * @param  pfnHook [OUT] ����#OS_IDLE_HOOK��IDLE���Ӻ������ò�������Ϊ�ա�
 *
 * @par ����:
 * <ul><li>sre_sys.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see SRE_IdleHookAdd
 */
#define SRE_IdleHookDel(pfnHook) SRE_HookDel(OS_HOOK_IDLE_PERIOD, (OS_VOID_FUNC)(OS_IDLE_HOOK)pfnHook)

#if (OS_OPTION_INIT_PHASE_QUERY == YES)
/**
 * @ingroup SRE_sys
 * ��ʼ���Ľ׶�
 */
typedef enum
{
    PHASE_IN_PRE_STARTUP = 0,   /**<��ǰOS��Ԥ�����׶�,״̬δ��ֵǰ     */
    PHASE_IN_MAIN_ENTRY,        /**<��ǰOS�ڽ���MAIN�Ľ׶�              */
    PHASE_IN_EXC_INIT_END,      /**<��ǰOS�쳣��ȫ���ӹܽ׶�            */
    PHASE_IN_OS_START,           /**<��ǰOS������г�ʼ����׼����������  */
    PHASE_IN_BUTT               /**<�Ƿ��׶�                            */
} INIT_PHASE_E;

#endif

#if (OS_CPU_TYPE == OS_SD6183)
/**
 * @ingroup  SRE_sys
 * @brief ��ȡ��ǰ��Context ID
 *
 * @par ����:
 * ��ȡ��ǰ��Context ID��
 *
 * @attention
 * <ul>
 * </ul>
 *
 * @retval #����ֵ����ǰ��context ID��
 * @par ����:
 * <ul><li>sre_mmu.h���ýӿ��������ڵ�ͷ�ļ���</li></ul>
 * @since RTOSck V100R002C00
 * @see
 */
extern UINT32 SRE_GetCurCntxId();

#if (OS_OPTION_USR_PROCESS == YES)
//usr pid >= 1. kernel pid = 0
extern UINT32 SRE_SelfPidGet(UINT32 *puwPID);
#define SRE_SelfPidGet(puwPID) \
        (UINT32)SRE_SYSCALL(SRE_SelfPidGet, 1, (UINT32)puwPID)


#define SRE_PrcesSleep() \
        (UINT32)SRE_SYSCALL(SRE_PrcesSleep, 0, 0)

#endif

#endif



#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

#endif /* _SRE_SYS_H */


