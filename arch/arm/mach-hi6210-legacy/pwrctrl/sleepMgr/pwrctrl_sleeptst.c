/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : pwrctrl_sleeptst.c
  �� �� ��   : ����
  ��    ��   : ������ 56193
  ��������   : 2012��7��25��
  ����޸�   :
  ��������   : �͹��Ĳ����ļ�
  �����б�   :

  �޸���ʷ   :
  1.��    ��   : 2012��7��25��
    ��    ��   : ������ 56193
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#ifndef WIN32
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/irq.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/delay.h>
#include <linux/string.h>
#include <linux/wakelock.h>
#endif
#include  <mach/pwrctrl/pwrctrl_common.h>
#include  <mach/pwrctrl/pwrctrl_perimgr.h>
#include  <mach/pwrctrl/pwrctrl_sleeptst.h>
#include  "soc_ao_sctrl_interface.h"

#if 0   /*acpu softtimer hasn't ready*/
#include  "softtimer.h"
#endif


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

/*****************************************************************************
 �� �� ��  : pwrctrl_mntn_show
 ��������  : test init
 �������  : ��
 �������  : ��
 �� �� ֵ  : s32_t
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��31��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_mntn_show(void_t)
{

     PWC_TRACE(PWC_LOG_ERROR, "exc vaddr: %x, paddr: %x \n", (s32_t)g_stAcpuPwcExcLog, EXCH_ACPU_CORE_PWC_ADDR, 0, 0, 0, 0);
     PWC_TRACE(PWC_LOG_ERROR, "sleep cnt: %x, slice: %x \n", (s32_t)(g_stAcpuPwcExcLog->core0.SlpCnt), (s32_t)(g_stAcpuPwcExcLog->core0.SlpMgrSTm), 0, 0, 0, 0);
     PWC_TRACE(PWC_LOG_ERROR, "wake cnt: %x, slice: %x \n", (s32_t)(g_stAcpuPwcExcLog->core0.WkCnt), (s32_t)(g_stAcpuPwcExcLog->core0.WkMgrSTm), 0, 0, 0, 0);

}



/*****************************************************************************
 �� �� ��  : pwrctrl_test_time_int
 ��������  : ˯��ѹ�����Ժ���-�жϴ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : s32_t
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��31��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_test_time_int(void_t)
{
    pwrctrl_write_reg32(PWC_REG_UART_PHY, 'A');
    pwrctrl_write_reg32(PWC_REG_UART_PHY, '\n');


    return RET_OK;
}

/*****************************************************************************
 �� �� ��  : pwrctrl_test_time_set
 ��������  : ˯��ѹ�����Ժ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : RET_OK
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��31��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_test_time_set(u32_t time)
{

#if 0  /*after acpu softtimer ready, should be deleted*/
    /*ע��Ӳ����ʱ���ж�*/
    setup_irq ( PWRCTRL_ACPU_TST_TIMER_INT_ID, &pwrctrl_tst_timer_irq);

    /*����timer����*/
    pwrctrl_write_reg32(SOC_TIMER_TIMERN_LOAD_ADDR(SOC_Timer4_BASE_ADDR,1),time);
    pwrctrl_write_reg32(SOC_TIMER_TIMERN_CONTROL_ADDR(SOC_Timer4_BASE_ADDR,1),PWCTRL_ACPU_TST_TIMER_CTRL);

#endif

    return RET_OK;

}





/*****************************************************************************
 �� �� ��  : pwrctrl_test_init
 ��������  : test init
 �������  : ��
 �������  : ��
 �� �� ֵ  : s32_t
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��8��31��
    ��    ��   : ������ 56193
    �޸�����   : �����ɺ���

*****************************************************************************/
s32_t pwrctrl_test_init(void_t)
{
    return RET_OK;
}







late_initcall(pwrctrl_test_init);




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
