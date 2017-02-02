/*lint -save -e537*/
#include <product_config.h>
#include <hi_gpio.h>
#include <mdrv_gpio.h>
#include <bsp_gpio.h>


/*lint -restore */

#define  GPIO_OPRT_ERROR    (-1)
#ifdef CONFIG_PASTAR
/*���߿��ز��µ����Կ��أ�ֻ��k3��ʹ�ã�v7R2���漰*/
unsigned int  sw_unpd_en = 0;
int bsp_rf_ldo_init(void)
{
    return -1;
}

void rf_gpio_set_high(void)
{
    return;
}

void rf_gpio_set_low(void)
{
    return;
}

int ldo_gpio123_get_value(void)
{

    return -1;
}

int ldo_gpio124_get_value(void)
{

    return -1;
}


int bsp_antn_sw_unpd_config(ANTN_SW_GROUP_E sw_group ,unsigned int mux)
{
    return 0;
}

#endif
#ifndef HI_K3_GPIO
/*****************************************************************************
 �� �� ��  : mdrv_gpio_oprt
 ��������  : at^GPIOPL,���úͲ�ѯGPIO�ĵ�ƽ
 �������  : �������� ulOp:
             0  ���ø�GPIO��PLֵ
             1  ��ѯ��ǰ��GPIO��PLֵ

             pucPL ��Ӧ20Byte������,ÿ��BYTE����һ��8���ܽŵ�ֵ

             ���ò���ʱ,pucPLΪ���õ�20��Byte
             ��ѯ����ʱ,pucPLΪ��ǰ��ȡ����PL��ʵ��ֵ��ɵ�16��������
             �����û�����at^GPIOPL = ABCDEF,���ӦpucPL������ֵΪ{A,B,C,D,E,F,0,0,...}

 �������  : ��
 �� �� ֵ  :  0 ��OK  �� 0 ��Error

*****************************************************************************/
int mdrv_gpio_oprt(GPIO_OPRT_E ulOp, unsigned char* pucPL)
{
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int bype_pin = 8;
    int          value = 0;

    if(NULL == pucPL)
    {
        return GPIO_OPRT_ERROR;
    }
    
    if(GPIO_OPRT_SET == ulOp)
    {
        for(i = 0;i < GPIO_MAX_BANK_NUM * GPIO_MAX_PINS / bype_pin;i++)
        {
            for(j = 0;j < bype_pin;j++)
            {
                /*lint -save -e701*/
                if(pucPL[i] & (0x1 << j))
                {
                    bsp_gpio_set_value(i * bype_pin + j, 1);
                }
                /*lint -restore */

            }
        }
    }
    else if(GPIO_OPRT_GET == ulOp)
    {
        for(i = 0;i < GPIO_MAX_BANK_NUM * GPIO_MAX_PINS / bype_pin;i++)
        {
            pucPL[i] = 0;
            for(j = 0;j < bype_pin;j++)
            {
                value = bsp_gpio_get_value(i * bype_pin + j);
                if(GPIO_ERROR == value)
                {
                    continue;
                }
                pucPL[i] = (unsigned char)(pucPL[i] | ( (unsigned int)value << j));
            }
        }
    }
    
    return 0;
}
#else
int mdrv_gpio_oprt(GPIO_OPRT_E ulOp, unsigned char* pucPL)
{
    return 0;
}
#endif

int mdrv_gpio_irq_enable(int gpio)
{
    return bsp_gpio_irq_unmask(gpio);
}

int mdrv_gpio_irq_disable(int gpio)
{
    return bsp_gpio_irq_mask(gpio);
}

int mdrv_gpio_request_irq(int gpio, pFUNCPTR handler, unsigned long flags,
	    const char *name)
{
    return bsp_gpio_request_irq(gpio, (irq_handler_t)handler, flags, name);
}

int mdrv_gpio_get_value(int gpio)
{
    return bsp_gpio_get_value((unsigned int)gpio);
}
