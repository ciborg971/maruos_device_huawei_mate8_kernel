/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
/******************************************************************************

 ******************************************************************************
  �� �� ��   : pwrctrl_hotplug_mgr.h
  �� �� ��   : ����
  ��    ��   : ʯ���� 61250
  ��������   : 2012��9��2��
  ����޸�   :
  ��������   : pwrctrl_hotplug_mgr.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��2��
    ��    ��   : ʯ���� 61250
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __PWRCTRL_HOTPLUG_MGR_H__
#define __PWRCTRL_HOTPLUG_MGR_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif




/*****************************************************************************
  2 �궨��
*****************************************************************************/


#define NR_CPUS_NUMBER (4)

#define PWC_HOTPARA_DEFAULT (0x55AA)

#define CPU_LOCK_FLAG  (0xFF)

#define CPU_HOTPLUG_TIMER_US  50000
#define CPU_HOTPLUG_BOOT_DELAY 60000000


#define CPU_LOCK_CHECK                                   \
    if(pwrctrl_hotplug_cpuqos.cpu_number_lock!=0)                                                 \
    {                                                        \
        PWC_TRACE(PWC_LOG_INFO, "cpu_number_lock :%d,pwrctrl_cpu_verify  fail\n", pwrctrl_hotplug_cpuqos.cpu_number_lock, 0, 0, 0, 0, 0);  \
        return RET_ERR;                                      \
    }

#ifndef  WIN32
#define QOS_DOWN_RECORD                      \
    ppwrctrl_hotplug_exc_log->qos_control_info.down_count++;              \
    ppwrctrl_hotplug_exc_log->qos_control_info.down_slicetime=pwrctrl_get_slice_time();

#define QOS_UP_RECORD                            \
    ppwrctrl_hotplug_exc_log->qos_control_info.up_count++;            \
    ppwrctrl_hotplug_exc_log->qos_control_info.up_slicetime=pwrctrl_get_slice_time();

#define MCU_UP_RECORD \
    ppwrctrl_hotplug_exc_log->mcu_control_info.up_count++; \
    ppwrctrl_hotplug_exc_log->mcu_control_info.up_slicetime=pwrctrl_get_slice_time();


#define AUTO_DOWN_RECORD                      \
    ppwrctrl_hotplug_exc_log->autohotplug_info.down_count++; \
    ppwrctrl_hotplug_exc_log->autohotplug_info.down_slicetime=pwrctrl_get_slice_time();

#define AUTO_UP_RECORD \
    ppwrctrl_hotplug_exc_log->autohotplug_info.up_count++; \
    ppwrctrl_hotplug_exc_log->autohotplug_info.up_slicetime=pwrctrl_get_slice_time();

#define CPU_DOWN_RECORD(cpuid)  \
    ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpuid].cpu_down_count++; \
    ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpuid].cpu_down_time = pwrctrl_get_slice_time();

#define CPU_UP_RECORD(cpuid)                      \
    ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpuid].cpu_up_count++;         \
    ppwrctrl_hotplug_exc_log->hotplug_cpu_info[cpuid].cpu_up_time = pwrctrl_get_slice_time();
#else
#define QOS_DOWN_RECORD
#define QOS_UP_RECORD
#define MCU_UP_RECORD
#define AUTO_DOWN_RECORD
#define AUTO_UP_RECORD
#define CPU_DOWN_RECORD(cpuid)
#define CPU_UP_RECORD(cpuid)

#endif
/*****************************************************************************
  3 ö�ٶ���
*****************************************************************************/



/*****************************************************************************
  4 ��Ϣͷ����
*****************************************************************************/


/*****************************************************************************
  5 ��Ϣ����
*****************************************************************************/


/*****************************************************************************
  6 STRUCT����
*****************************************************************************/

typedef struct PWRCTRL_HOTPLUG_LEVEL
{
    u32_t  cpu_load;
    u32_t  avr_task;
    u32_t  cnt_load;
    u32_t  cnt_task;

} PWRCTRL_HOTPLUG_LEVEL_STRU;


typedef struct PWRCTRL_HOTPLUG_PARA_STRU_S
{
    u32_t  hotlpug_timer;      /*0x0*/
    PWRCTRL_HOTPLUG_LEVEL_STRU hotplug_up_level[NR_CPUS_NUMBER];/*ƫ��Ϊ0x04*/
    PWRCTRL_HOTPLUG_LEVEL_STRU hotplug_down_level[NR_CPUS_NUMBER]; /*ƫ��Ϊ4*4*4+4*/

} PWRCTRL_HOTPLUG_PARA_STRU;

typedef struct PWRCTRL_HOTPLUG_CPUQOS_S
{
    u32_t  cpu_number_lock;
    u32_t  cpu_number_max;
    u32_t  cpu_number_min ;

} PWRCTRL_HOTPLUG_CPUQOS_STRU;


/*ÿ��cpu״̬�仯ʱ���¼�ṹ�� */
typedef struct PWRCTRL_HOTPLUG_CPUINFO_STRU_S
{
    u32_t  cpu_down_count;
    u32_t  cpu_down_time ;
    u32_t  down_power_time ;
    u32_t  down_notemcu_time ;

    u32_t  cpu_up_count;
    u32_t  cpu_up_time ;
    u32_t  up_power_time ;
    u32_t  up_asm_exit_time ;
    u32_t  up_notemcu_time ;
} PWRCTRL_HOTPLUG_CPUINFO_STRU;

/*autohotplug/mcu/qos ����cpuʱ���¼�ṹ�� */
   typedef struct PWRCTRL_HOTPLUG_CON_STRU_S
{
    u32_t  up_slicetime ;
    u32_t  down_slicetime ;
    u32_t  up_count ;
    u32_t  down_count ;
} PWRCTRL_HOTPLUG_CON_STRU;


          /*hotplug ά����Ϣ�ṹ��*/
typedef struct PWRCTRL_HOTPLUG_EXC_LOG_STRU_S
{
    PWRCTRL_HOTPLUG_CON_STRU  autohotplug_info;
    PWRCTRL_HOTPLUG_CON_STRU mcu_control_info;
    PWRCTRL_HOTPLUG_CON_STRU qos_control_info;
    PWRCTRL_HOTPLUG_CPUINFO_STRU hotplug_cpu_info[NR_CPUS_NUMBER];
} PWRCTRL_HOTPLUG_EXC_LOG_STRU;


/*****************************************************************************
  7 UNION����
*****************************************************************************/


/*****************************************************************************
  8 OTHERS����
*****************************************************************************/


/*****************************************************************************
  9 ȫ�ֱ�������
*****************************************************************************/


extern PWRCTRL_HOTPLUG_EXC_LOG_STRU *ppwrctrl_hotplug_exc_log;
/*****************************************************************************
  10 ��������
*****************************************************************************/

extern s32_t pwrctrl_cpunumbermin_handle(u32_t value);
extern s32_t pwrctrl_cpunumbermax_handle (u32_t value);
extern s32_t pwrctrl_cpunumberlock_handle (u32_t value);







#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of pwrctrl_hotplug_mgr.h */
