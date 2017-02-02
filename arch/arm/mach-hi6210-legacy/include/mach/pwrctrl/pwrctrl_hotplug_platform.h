
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
  �� �� ��   : pwrctrl_hotplug_platform.h
  �� �� ��   : ����
  ��    ��   : ʯ���� 61250
  ��������   : 2012��9��2��
  ����޸�   :
  ��������   : pwrctrl_hotplug_platform.c ��ͷ�ļ�
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2012��9��2��
    ��    ��   : ʯ���� 61250
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ����ͷ�ļ�����
*****************************************************************************/

#ifndef __PWRCTRL_HOTPLUG_PLATFORM_H__
#define __PWRCTRL_HOTPLUG_PLATFORM_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 �궨��
*****************************************************************************/
#define MAILBOX_TARGET_CPU_MCU 6

#define CPU_POWER_DOWN         1
#define CPU_POWER_UP           2
#define IPC_SEM_CPU_BASE       12
#define IPC_SEM_CPU_PW(cpuindex)  (IPC_SEM_SMP_CPU0 + cpuindex)


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif
