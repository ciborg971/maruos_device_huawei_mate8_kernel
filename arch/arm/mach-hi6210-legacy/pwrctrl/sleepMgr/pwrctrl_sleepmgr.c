/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pwrctrl_sleepmgr.c
  �� �� ��   : ����
  ��    ��   : ������ 56193
  ��������   : 2012��7��25��
  ����޸�   :
  ��������   : �͹���˯�߹���
  �����б�   :
              pwrctrl_sleep_mgr_sleep_init
              pwrctrl_sleep_mgr_tele_vote_lock
              pwrctrl_sleep_mgr_tele_vote_unlock

  �޸���ʷ   :
  1.��    ��   : 2012��7��25��
    ��    ��   : ������ 56193
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#ifndef WIN32
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/cpu.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <asm/memory.h>
#include <mach/system.h>
#include <mach/platform.h>
#include <linux/delay.h>
#include <linux/suspend.h>
#include <asm/mach/time.h>
#include <mach/irqs.h>
#include <mach/hipm.h>
#include <mach/early-debug.h>
#include <linux/android_pmem.h>
#include <asm/hardware/gic.h>
#include <asm/hardware/arm_timer.h>
#include <linux/slab.h>
#include <asm/io.h>
#include <mach/io.h>
#include <mach/gpio.h>
#include <linux/clk.h>
#endif
#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_perimgr.h>
#include <mach/pwrctrl/pwrctrl_sleepmgr.h>
#include <mach/pwrctrl/pwrctrl_sleep.h>


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif



/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
static struct platform_suspend_ops pwrctrl_ops = {
#ifndef WIN32
    .enter      = pwrctrl_deep_sleep,
    .valid      = suspend_valid_only_mem,
#else
    0
#endif
};


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*****************************************************************************
 �� �� ��  : PWRCTRL_SleepMgrSleepInit
 ��������  :
 �������  : ��
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��23��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_sleep_mgr_sleep_init( void_t)
{

    /*ע�����߻ص�*/
    suspend_set_ops(&pwrctrl_ops);
#if 0
    pm_idle = pwrctrl_arm_sleep;
#endif
    return RET_OK;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_sleep_mgr_tele_vote_lock
 ��������  : Զ��ͶƱ��ֹ˯�߽ӿ�
 �������  : teleModeId         Զ��ģ��ID
             enClientId         ͶƱģ��ID
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��23��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_sleep_mgr_tele_vote_lock(PWC_TELE_SLEEP_MODE_ID_E teleModeId, PWC_TELE_SLEEP_CLIENT_ID_E enClientId)
{
    if((enClientId < PWRCTRL_TELE_SLEEP_CSIGHT0 )||(enClientId >= PWRCTRL_TELE_CLIENT_BUTT))
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_lock enClientId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    if( teleModeId > PWRCTRL_TELE_REV2 )
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_lock teleModeId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    pwrctrl_sleep_tele_vote_lock(teleModeId,enClientId);

    return RET_OK;

}

/*****************************************************************************
 �� �� ��  : pwrctrl_sleep_mgr_tele_vote_unlock
 ��������  : Զ��ͶƱ����˯�߽ӿ�
 �������  : teleModeId         Զ��ģ��ID
             enClientId         ͶƱģ��ID
 �������  : ��
 �� �� ֵ  : RET_OK         �ɹ�
             RET_ERR        ʧ��
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��23��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_sleep_mgr_tele_vote_unlock(PWC_TELE_SLEEP_MODE_ID_E teleModeId, PWC_TELE_SLEEP_CLIENT_ID_E enClientId)
{
    if((enClientId < PWRCTRL_TELE_SLEEP_CSIGHT0 )||(enClientId >= PWRCTRL_TELE_CLIENT_BUTT))
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_unlock: enClientId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    if( teleModeId > PWRCTRL_TELE_REV2 )
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_sleep_mgr_tele_vote_unlock: teleModeId param false. \n", 0, 0, 0, 0, 0, 0);
        return RET_ERR;
    }

    pwrctrl_sleep_tele_vote_unlock(teleModeId,enClientId);

    return RET_OK;
}













#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

