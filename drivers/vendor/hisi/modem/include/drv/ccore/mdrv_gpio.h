#ifndef __MDRV_CCORE_GPIO_H__
#define __MDRV_CCORE_GPIO_H__
#ifdef __cplusplus
extern "C"
{
#endif

#include "mdrv_public.h"

/*��ѯ������GPIO��ƽ��*/
typedef enum GPIO_OPRT_ENUM
{
    GPIO_OPRT_SET = 0,
    GPIO_OPRT_GET,
    GPIO_OPRT_BUTT
}GPIO_OPRT_E;

/*�ܽŸ������á�*/
typedef enum MODEM_PIN_MUX_ENUM
{
    MODEM_PIN_MUX_GPIO = 0,
    MODEM_PIN_MUX_ANTEN,
    MODEM_PIN_MUX_BUTT
}MODEM_PIN_MUX_E;

#define GPIO_IRQ_TYPE_NONE		     0x00000000
#define GPIO_IRQ_TYPE_EDGE_RISING	 0x00000001/*�����ش���*/
#define GPIO_IRQ_TYPE_EDGE_FALLING	 0x00000002/*�½��ش���*/
#define GPIO_IRQ_TYPE_EDGE_BOTH	     (GPIO_IRQ_TYPE_EDGE_FALLING | GPIO_IRQ_TYPE_EDGE_RISING)
#define GPIO_IRQ_TYPE_LEVEL_HIGH     0x00000004/*�ߵ�ƽ����*/
#define GPIO_IRQ_TYPE_LEVEL_LOW	     0x00000008/*�͵�ƽ����*/

/*****************************************************************************
	 *  �� �� ��  : mdrv_gpio_oprt
	 *  ��������  :  ���úͲ�ѯGPIO�ĵ�ƽ��
	 *  �������  : ulOp : 1:����/0:��ѯ
	 *
	 *  �������  : ��
	 *  �� �� ֵ  :  0	       �����ɹ���
        *                           ����	����ʧ�ܡ�
     	 *
	 ******************************************************************************/
int mdrv_gpio_oprt(GPIO_OPRT_E ulOp, unsigned char* pucPL);

/*1.	mdrv_set_os_status
2.	mdrv_get_board_info
��ȷ��*/

#if defined(CHIP_BB_HI6210)
/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_irq_enable
	 *	��������  : gpio�ж�ʱ��
	 *	�������  : gpio gpio���
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
static inline int mdrv_gpio_irq_enable(int gpio)
{
    return 0;
}
/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_irq_disable
	 *	��������  : gpio�ж�ȥʱ��
	 *	�������  : gpio gpio���
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
static inline int mdrv_gpio_irq_disable(int gpio)
{
    return 0;
}

/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_request_irq
	 *	��������  : gpio�ж�ע��
	 *	�������  : gpio gpio���
	 *              handler �ص�����
	 *              flags   ��������
	 *              name    ����
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
static inline int mdrv_gpio_request_irq(int gpio, pFUNCPTR handler, unsigned long flags,
	    const char *name)
{
    return 0;
}
/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_get_value
	 *	��������  : ��ȡgpio��ƽ
	 *	�������  : gpio gpio���
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
static inline int mdrv_gpio_get_value(int gpio)
{
    return 0;
}
#else
/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_irq_enable
	 *	��������  : gpio�ж�ʱ��
	 *	�������  : gpio gpio���
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
int mdrv_gpio_irq_enable(int gpio);
/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_irq_disable
	 *	��������  : gpio�ж�ȥʱ��
	 *	�������  : gpio gpio���
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
int mdrv_gpio_irq_disable(int gpio);

/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_request_irq
	 *	��������  : gpio�ж�ע��
	 *	�������  : gpio gpio���
	 *              handler �ص�����
	 *              flags   ��������
	 *              name    ����
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
int mdrv_gpio_request_irq(int gpio, pFUNCPTR handler, unsigned long flags,
	    const char *name);
/*****************************************************************************
	 *	�� �� ��  : mdrv_gpio_get_value
	 *	��������  : ��ȡgpio��ƽ
	 *	�������  : gpio gpio���
	 *
	 *	�������  : ��
	 *	�� �� ֵ  :  0		   �����ɹ���
	 *	             ����	   ����ʧ�ܡ�
	 *
	 ******************************************************************************/
int mdrv_gpio_get_value(int gpio);
#endif
#ifdef __cplusplus
}
#endif

#endif

