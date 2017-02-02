
#ifndef _BSP_GPIO_H_
#define _BSP_GPIO_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <osl_irq.h>
#include <osl_types.h>
#include "hi_gpio.h"
/* GPIO״̬*/
#define GPIO_OK                     0
#define GPIO_ERROR                  -1

#define GPIO_OUTPUT 1
#define GPIO_INPUT  0

#define GPIO_INVALID_IRQ 0xffffffff

#define IRQF_SHARED		         0x00000080
#define IRQ_TYPE_NONE		     0x00000000
#define IRQ_TYPE_EDGE_RISING	 0x00000001
#define IRQ_TYPE_EDGE_FALLING	 0x00000002
#define IRQ_TYPE_EDGE_BOTH	     (IRQ_TYPE_EDGE_FALLING | IRQ_TYPE_EDGE_RISING)
#define IRQ_TYPE_LEVEL_HIGH      0x00000004
#define IRQ_TYPE_LEVEL_LOW	     0x00000008

typedef enum{
	MASTER_0 = 0,
	MASTER_1,
	NAGTIVE,
	GR_BUTT
}ANTN_SW_GROUP_E;

/*****************************************************************************
* �� �� ��  : bsp_gpio_init
*
* ��������  : GPIO��ʼ���ӿ�
*
* �������  : ��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
s32 bsp_gpio_init(void);

/*****************************************************************************
* �� �� ��  : bsp_gpio_direction_input
*
* ��������  : ����GPIO���ŷ���Ϊ����
*
* �������  : UINT32 gpio    GPIO���ű��
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
void bsp_gpio_direction_input(u32 gpio);

/*****************************************************************************
* �� �� ��  : bsp_gpio_direction_output
*
* ��������  : ����GPIO���ŵķ���Ϊ����������ø�����Ĭ�ϵ�ƽֵ
*
* �������  : UINT32 gpio       GPIO���ű��
*             UINT32 value      �����õ�ƽֵ,��0Ϊ�͵�ƽ��1Ϊ�ߵ�ƽ
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
void bsp_gpio_direction_output(u32 gpio, u32 value);

/*****************************************************************************
* �� �� ��  : bsp_gpio_direction_get
*
* ��������  : ��ѯGPIO ���ŵķ���
*
* �������  : UINT32 gpio        GPIO���ű��
*
* �� �� ֵ  : ����gpio���ŷ���,��0Ϊ���룬1Ϊ���
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
s32 bsp_gpio_direction_get(u32 gpio);

/*****************************************************************************
* �� �� ��  : bsp_gpio_set_value
*
* ��������  : ����GPIO ���ŵĵ�ƽֵ
*
* �������  : u32 gpio        GPIO���ű��
*			  u32 value      �ܽŸ�/�͵�ƽ
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��   
*****************************************************************************/
void bsp_gpio_set_value(u32 gpio,u32 value);

/*****************************************************************************
* �� �� ��  : bsp_gpio_get_value
*
* ��������  : ��ѯGPIO���ŵĵ�ƽֵ
*
* �������  : UINT32 gpio        GPIO���ű��
*
* �� �� ֵ  : ����GPIO���ŵĵ�ƽֵ
*
* �޸ļ�¼  : 2012��11��27��
*****************************************************************************/
s32 bsp_gpio_get_value(u32 gpio);

/**/
void rf_gpio_set_high(void);
void rf_gpio_set_low(void);
int ldo_gpio123_get_value(void);
int ldo_gpio124_get_value(void);
int bsp_antn_sw_unpd_config(ANTN_SW_GROUP_E sw_group ,unsigned int mux);
int bsp_gpio_request_irq(int gpio, irq_handler_t handler, unsigned long flags,
	    const char *name);
int bsp_gpio_irq_mask(int gpio);
int bsp_gpio_irq_unmask(int gpio);

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define _GPIO_BALONG_H_ */
