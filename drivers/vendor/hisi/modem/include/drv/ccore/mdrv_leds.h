#ifndef __MDRV_CCORE_LEDS_H__
#define __MDRV_CCORE_LEDS_H__

#include "mdrv_leds_comm.h"
#include <product_config.h>
#ifdef CONFIG_LEDS_CCORE

/****************************************************************************
 �� �� ��  : drv_led_state_func_reg
 ��������  : ���ӿ�Ϊ�ṩ��Э��ջ�Ĺ��Ӻ��������ڻ�ȡЭ��ջ�ĵ��״̬��
 �������  : Э��ջ��ȡ���״̬������ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע������  : �ޡ�

******************************************************************************/
void drv_led_state_func_reg (pFUNCPTR p);

/*****************************************************************************
 �� �� ��  : drv_led_flash
 ��������  : ��ɫ�����á�
 �������  : status����ɫ�Ƶ�״̬
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
int drv_led_flash(unsigned long state);

#else

/*
 * ��׮
 */
static inline void drv_led_state_func_reg (pFUNCPTR p)
{

}

static inline int drv_led_flash(unsigned long state)
{
    return 0;
}


#endif

#define DRV_LED_GET_ADDRESS()   BSP_MNTN_LedControlAddressGet()

#define DRV_LED_FLUSH(state)  drv_led_flash(state)  

#define DRV_LED_STATE_FUNREG(p)  drv_led_state_func_reg(p)
#endif /* #ifndef __MDRV_CCORE_LEDS_H__ */
