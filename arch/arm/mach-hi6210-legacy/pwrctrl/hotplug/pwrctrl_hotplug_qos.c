
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
  �� �� ��   : pwrctrl_hotplug_platform.c
  �� �� ��   : ����
  ��    ��   : ʯ����61250
  ��������   : 2012��9��2��
  ����޸�   :
  ��������   : CPU ���µ�ײ����
  �����б�   :
              pwrctrl_hotplug_qosdev_register
              pwrctrl_hotplug_qosdev_unregister
              pwrctrl_cpunumbermin_notify
              pwrctrl_cpunumbermax_notify
              pwrctrl_cpunumberlock_notify

  �޸���ʷ   :
  1.��    ��   : 2012��9��2��
    ��    ��   :  ʯ����61250
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/notifier.h>
#include <linux/pm_qos_params.h>
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_hotplug_mgr.h>
#include <drv_ipcm.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/



/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/




/*************************************************************************
 �� �� ��  : pwrctrl_cpunumbermin_notify
 ��������  : qos cpunumbermin�ص�������
 �������  : �趨��CPU����
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
void pwrctrl_cpunumbermin_notify (struct notifier_block *b, unsigned long cpumin,
    void *v)
{

    /*��SC�ж�qos�����Ƿ�򿪣�û�д�return ERROR */
    if((cpumin<= num_possible_cpus())&&(cpumin>=1))
    {
        pwrctrl_cpunumbermin_handle((u32_t)cpumin);
    }
    else
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumbermin fail:%d\n",cpumin,0,0,0,0,0);

    }
}


/*************************************************************************
 �� �� ��  : pwrctrl_cpunumbermax_notify
 ��������  : qos cpunumbermax�ص�������
 �������  : �趨��CPU����
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
void pwrctrl_cpunumbermax_notify (struct notifier_block *b, unsigned long cpumax,
    void *v)
{
     int cpu = num_possible_cpus();

     PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumbermax_notify %d,%d\n",cpumax,cpu,0,0,0,0);

    /*��SC�ж�qos�����Ƿ�򿪣�û�д�return ERROR */
    if((cpumax<= num_possible_cpus())&&(cpumax>=1))
    {

        pwrctrl_cpunumbermax_handle((u32_t)cpumax);
    }
    else
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumbermax erro fail:%d\n",cpumax,0,0,0,0,0);

    }
}


/*************************************************************************
 �� �� ��  : pwrctrl_cpunumberlock_notify
 ��������  : qos cpunumberlock�ص�������
 �������  : �趨��CPU����
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
void pwrctrl_cpunumberlock_notify (struct notifier_block *b, unsigned long cpulock,
    void *v)
{

    /*��SC�ж�qos�����Ƿ�򿪣�û�д�return ERROR */
    if(cpulock<= num_possible_cpus())
    {
        pwrctrl_cpunumberlock_handle((u32_t)cpulock);
    }
    else
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_cpunumberlock erro fail:%d\n",cpulock,0,0,0,0,0);

    }
}

local_t struct notifier_block cpu_numberlock_notifier = {
    .notifier_call = pwrctrl_cpunumberlock_notify,
    .next = NULL,
    .priority = 0,
};

local_t struct notifier_block cpu_maxnumber_notifier = {
    .notifier_call = pwrctrl_cpunumbermax_notify,
    .next = NULL,
    .priority = 0,
};
local_t struct notifier_block cpu_minnumber_notifier = {
    .notifier_call = pwrctrl_cpunumbermin_notify,
    .next = NULL,
    .priority = 0,
};
/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_qosdev_register
 ��������  : cpu qos�豸�������ص�notify����ע��
 �������  : ��
 �������  : ��
 �� �� ֵ  : OK/ERROR���豸ע��ɹ�����ʧ��
�޸ļ�¼   ��
************************************************************************/
 int pwrctrl_hotplug_qosdev_register ( void )
{
    /*ע��cpu_number_lock qos notify �ص�����*/
    /*ע��cpu_number_min qos notify �ص�����*/
    /*ע��cpu_number_max qos notify �ص�����*/
/*
#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
*/
    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_CPU_NUMBER_LOCK, &cpu_numberlock_notifier) < 0);

    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_CPU_NUMBER_MAX, &cpu_maxnumber_notifier) < 0);

    RET_ERR_IF(pm_qos_add_notifier(PM_QOS_CPU_NUMBER_MIN, &cpu_minnumber_notifier) < 0);
/*
#endif
*/
    PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_hotplug_qosdev_register sucess\n",0,0,0,0,0,0);

    return 0;
}

/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_qosdev_unregister
 ��������  : A
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
 s32_t pwrctrl_hotplug_qosdev_unregister ( void )
{
    /*ȥע��cpu_number_lock qos notify �ص�����*/
/*
#ifdef CONFIG_CPU_FREQ_GOV_K3HOTPLUG
*/
    RET_ERR_IF(pm_qos_remove_notifier(PM_QOS_CPU_NUMBER_LOCK, &cpu_numberlock_notifier) < 0);

    RET_ERR_IF(pm_qos_remove_notifier(PM_QOS_CPU_NUMBER_MAX, &cpu_maxnumber_notifier) < 0);

    RET_ERR_IF(pm_qos_remove_notifier(PM_QOS_CPU_NUMBER_MIN, &cpu_minnumber_notifier) < 0);
/*
#endif
*/
    PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_hotplug_qosdev_unregister sucess\n",0,0,0,0,0,0);


    return 0;
}



#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

