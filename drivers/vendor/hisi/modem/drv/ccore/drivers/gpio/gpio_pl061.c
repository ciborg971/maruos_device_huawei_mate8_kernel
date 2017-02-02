/*************************************************************************
*   ��Ȩ����(C) 1987-2004, ���ڻ�Ϊ�������޹�˾.
*
*   �� �� �� :  BSP_GPIO.c
*
*   ��    �� :  zuofenghua
*
*   ��    �� :  GPIO�����ļ� 
*
*   �޸ļ�¼ :  2015��3��27��
*
*************************************************************************/
/* includes */
/*lint -save -e537*/
#include <stdio.h>
#include <string.h>
#include "securec.h"
#include <osl_bio.h>
#include <osl_list.h>
#include <osl_spinlock.h>
#include <osl_err.h>
#include <osl_malloc.h>
#include <osl_common.h>
#include <soc_clk.h>

#include <bsp_memmap.h>
#include <bsp_ipc.h>
#include <bsp_clk.h>
#include <bsp_om.h>
#include <bsp_hw_spinlock.h>
#include <bsp_version.h>

#include <of.h>
#include <bsp_gpio.h>
#include <gpio_pl061.h>

/*lint -restore */

#ifdef __cplusplus
extern "C" {
#endif

GPIO_INFO_S g_baseinfo;

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
void bsp_gpio_direction_input(u32 gpio)
{
    u32   chip_num;
    u32   pin;
    u32   irq_flags;
    u32   gpiodir   = 0;
    void* base      = NULL;

    chip_num    = gpio / g_baseinfo.max_pin;
    pin         = gpio % g_baseinfo.max_pin;

    if(chip_num < g_baseinfo.group_num){
        base    = g_baseinfo.group[chip_num].base;
    }
    else{
        gpio_print_error(" GPIO bank number error.\n");
        return ;
    }
    spin_lock_irqsave(&g_baseinfo.group[chip_num].lock, irq_flags);

    gpiodir = readl((u32)base + GPIODIR);
    gpiodir &= ~((u32)1 << pin);
    writel(gpiodir, (u32)base + GPIODIR);    

    spin_unlock_irqrestore(&g_baseinfo.group[chip_num].lock, irq_flags);
}

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
void bsp_gpio_direction_output(u32 gpio, u32 value)
{
    u32   chip_num;
    u32   pin;
    u32   gpiodir    = 0;
    u32   irq_flags;
    void *base       = NULL;

    chip_num    = gpio / g_baseinfo.max_pin;
    pin         = gpio % g_baseinfo.max_pin;

    if(chip_num < g_baseinfo.group_num){
        base    = g_baseinfo.group[chip_num].base;
    }
    else{
        gpio_print_error(" GPIO bank number error.\n");
        return ;
    }
    spin_lock_irqsave(&g_baseinfo.group[chip_num].lock, irq_flags);

    /* ����GPIO����Ϊ��� */    
    gpiodir  = readl((u32)base + GPIODIR);
    gpiodir |= (u32)1 << pin;
    writel(gpiodir,(u32)base + GPIODIR);

    /*���ùܽŵĵ�ƽ*/
    writel(((u32)!!value) << pin, (u32)base + ((u32)1 << (pin + 2)));

    spin_unlock_irqrestore(&g_baseinfo.group[chip_num].lock, irq_flags);

}

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
s32 bsp_gpio_direction_get(u32 gpio)
{
    u32   chip_num;
    u32   pin;
    u32   gpio_value = 0;
    void* base       = NULL;

    chip_num    = gpio / g_baseinfo.max_pin;
    pin         = gpio % g_baseinfo.max_pin;

    if(chip_num < g_baseinfo.group_num){
        base    = g_baseinfo.group[chip_num].base;
    }
    else{
        gpio_print_error(" GPIO bank number error.\n");
        return GPIO_ERROR;
    }

    gpio_value = readl((u32)base + GPIODIR);

    return (s32) !!(gpio_value & ((u32)0x1 << pin));
}

/*****************************************************************************
* �� �� ��  : bsp_gpio_set_value
*
* ��������  : ����GPIO ���ŵĵ�ƽֵ
*
* �������  : u32 gpio        GPIO���ű��
*              u32 value      �ܽŸ�/�͵�ƽ
*
* �� �� ֵ  : ��
*
* �޸ļ�¼  : 2012��11��27��
*****************************************************************************/
void bsp_gpio_set_value(u32 gpio,u32 value)
{
    u32   chip_num;
    u32   pin;
    u32   irq_flags;
    void* base  = NULL;

    chip_num    = gpio / g_baseinfo.max_pin;
    pin         = gpio % g_baseinfo.max_pin;

    if(chip_num < g_baseinfo.group_num){
        base    = g_baseinfo.group[chip_num].base;
    }
    else{
        gpio_print_error(" GPIO bank number error.\n");
        return ;
    }

    
    /*���GPIO�����Ƿ���������Ϊ���룬�򷵻ش���*/
    if(0 == bsp_gpio_direction_get(gpio))
    {
        return;
    }
    spin_lock_irqsave(&g_baseinfo.group[chip_num].lock, irq_flags);

    writel(((u32)!!value) << pin,(u32) base + ((u32)1 << (pin + 2)));

    spin_unlock_irqrestore(&g_baseinfo.group[chip_num].lock, irq_flags);

}

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
s32 bsp_gpio_get_value(u32 gpio)
{
    u32   chip_num;
    u32   pin;
    u32   gpio_value = 0;
    void* base       = NULL;

    chip_num    = gpio / g_baseinfo.max_pin;
    pin         = gpio % g_baseinfo.max_pin;

    if(chip_num < g_baseinfo.group_num){
        base    = g_baseinfo.group[chip_num].base;
    }
    else{
        gpio_print_error(" GPIO bank number error.\n");
        return GPIO_ERROR;
    }

    /* ��ȡ���ŵĵ�ƽֵ */
    gpio_value = !!readl((u32)base + ((u32)1 << (pin + 2)));

    return (int)gpio_value;

}

static void gpio_set_irq_trigger_type(int gpio, unsigned long flags)
{
    u32 base    = (u32)g_baseinfo.group[gpio / PL061_GPIO_NR].base;
    u32 gpioiev = 0;
    u32 gpiois  = 0;
    u32 gpioibe = 0;
    u32 offset  = gpio % PL061_GPIO_NR;
    int ret     = 0;

    ret = hwspin_lock_timeout(HW_GPIO_LOCKID, HW_SPINLOCK_WAIT_FOREVER);
    if(BSP_OK!=ret){
        gpio_print_error("hwspin lock timeout !\n");
    }

    gpioiev = readl(base + GPIOIEV);
    gpiois  = readl(base + GPIOIS);
    gpioibe = readl(base + GPIOIBE);
    
    if (flags & (IRQ_TYPE_LEVEL_HIGH | IRQ_TYPE_LEVEL_LOW)) {
        gpiois |= (u32)1 << offset;
        if (flags & IRQ_TYPE_LEVEL_HIGH)
            gpioiev |= (u32)1 << offset;
        else
            gpioiev &= ~((u32)1 << offset);
    } else
        gpiois &= ~((u32)1 << offset);
    writel(gpiois, base + GPIOIS);

    if ((flags & IRQ_TYPE_EDGE_BOTH) == IRQ_TYPE_EDGE_BOTH)
        gpioibe |= (u32)1 << offset;
    else {
        gpioibe &= ~((u32)1 << offset);
        if (flags & IRQ_TYPE_EDGE_RISING)
            gpioiev |= (u32)1 << offset;
        else if (flags & IRQ_TYPE_EDGE_FALLING)
            gpioiev &= ~((u32)1 << offset);
    }
    writel(gpioibe, base + GPIOIBE);

    writel(gpioiev, base + GPIOIEV);

    ret = hwspin_unlock(HW_GPIO_LOCKID);
    if(BSP_OK!=ret){
        gpio_print_error("hwspin unlock timeout !\n");
    }

    return ;
}

u32 irq_to_gpio_group (u32 irq)
{
    u32 i = 0;

    for (i = 0; i < g_baseinfo.group_num ; i++)
        if( irq == g_baseinfo.group[i].irq )
            return i;

    return g_baseinfo.group_num;
}

static irqreturn_t gpio_irq_handle(void *arg)
{
    int           i       = 0;
    u32           base    = 0;
    u32           pending = 0;
    irq_handler_t handler = NULL;
    irqreturn_t   ret     = IRQ_NONE;
    u32           group   = irq_to_gpio_group((u32)arg);
    u32           mis_reg = GPIO_MIS_CCORE;

    if (group >= g_baseinfo.group_num)
        return IRQ_NONE;

    base     = (u32)g_baseinfo.group[group].base;
    pending  = readl(base + mis_reg);
    writel(pending, base + GPIOIC);
    if (pending) {
        for(i = 0; i < PL061_GPIO_NR; i++)
            if(((u32)1 << i) & pending){
                handler = g_baseinfo.group[group].handler[i];
                
                if( handler ){
                    ret = handler(arg);
                    if(IRQ_HANDLED !=ret){
                        gpio_print_error("irq handle error!ret is %d,group is%d,irq is %d\n",ret,group,arg);
                    }
                }
            }
    }


    return IRQ_HANDLED;
}

int bsp_gpio_request_irq(int gpio, irq_handler_t handler, unsigned long flags,
        const char *name)
{
    int g_num = 0;
    if(gpio >= (int)g_baseinfo.group_num * PL061_GPIO_NR ){
        gpio_print_error("gpio num is invalid, %d \n",gpio);
        return GPIO_ERROR;
    }

    g_num = gpio / (int)g_baseinfo.max_pin;

    /*�ҽӻص�������*/
    g_baseinfo.group[g_num].handler[gpio % PL061_GPIO_NR] = handler;

    g_baseinfo.group[g_num].name[gpio % PL061_GPIO_NR] = name;

    gpio_set_irq_trigger_type(gpio, flags);

    return GPIO_OK;
}

int bsp_gpio_irq_mask(int gpio)
{
    u32 mask   = 1 << (gpio % PL061_GPIO_NR);
    u32 base   = 0;
    u32 gpioie = 0;    
    u32 ie_reg = GPIO_IE_CCORE;
    u32 irq_flags;

    if (gpio >= (int)g_baseinfo.group_num * PL061_GPIO_NR)
        return GPIO_ERROR;

    base   = (u32)g_baseinfo.group[gpio / PL061_GPIO_NR].base;

    spin_lock_irqsave(&g_baseinfo.group[gpio / PL061_GPIO_NR].lock, irq_flags);
    gpioie = readl(base + ie_reg) & ~mask;
    writel(gpioie, base + ie_reg);
    spin_unlock_irqrestore(&g_baseinfo.group[gpio / PL061_GPIO_NR].lock, irq_flags);

    return GPIO_OK;
}

int bsp_gpio_irq_unmask(int gpio)
{
    u32 mask   = 1 << (gpio % PL061_GPIO_NR);
    u32 base   = 0;
    u32 gpioie = 0;
    u32 ie_reg = GPIO_IE_CCORE;
    u32 irq_flags;

    if (gpio >= (int)g_baseinfo.group_num * PL061_GPIO_NR)
        return GPIO_ERROR;

    base   = (u32)g_baseinfo.group[gpio / PL061_GPIO_NR].base;

    spin_lock_irqsave(&g_baseinfo.group[gpio / PL061_GPIO_NR].lock, irq_flags);
    gpioie = readl(base + ie_reg) | mask;
    writel(gpioie, base + ie_reg);
    spin_unlock_irqrestore(&g_baseinfo.group[gpio / PL061_GPIO_NR].lock, irq_flags);

    return GPIO_OK;
}

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
s32 bsp_gpio_init(void)
{
    int                 i            = 0;
    struct device_node *dev_node     = NULL;
    char               *clk_name     = NULL;
    int                 ret          = GPIO_OK;
    u32                 group_size   = 0;
    int                 irq          = (int)GPIO_INVALID_IRQ;
    u32 ie_reg = GPIO_IE_CCORE;

    dev_node = of_find_compatible_node(NULL, NULL, "arm,gpio_pl061_mdm");
    if(NULL == dev_node)
    {
        gpio_print_error("gpio device node not found\n");
        return GPIO_ERROR;
    }
    ret = of_property_read_u32_index(dev_node, "gpio_group", 0,&g_baseinfo.group_num);
    if(ret){
        gpio_print_error("gpio device get gpio_group node failed!\n");
        return GPIO_ERROR;
    }

    clk_name         = osl_malloc(NAME_LENTH);
    if(NULL == clk_name){
        gpio_print_error("clk name malloc faild!\n");
        return GPIO_ERROR;
    }
    group_size       = g_baseinfo.group_num * sizeof(struct gpio_pl061);
    g_baseinfo.group = osl_malloc(group_size);
    if(NULL == g_baseinfo.group){
        gpio_print_error("gpio group malloc faild!\n");
        osl_free(clk_name);
        return  GPIO_ERROR;
    }

    memset_s(g_baseinfo.group, group_size, 0, group_size);

    ret = of_property_read_u32_index(dev_node, "max_pin", 0,&g_baseinfo.max_pin);
    if(ret){
        gpio_print_error("gpio device get max_pin node failed!\n");
        /*lint -save -e801*/
        goto error;
        /*lint -restore -e801*/
    }

    ret = of_property_read_u32_index(dev_node, "clock_flag", 0,&g_baseinfo.clk_flag);
    if(ret){
        gpio_print_error("gpio device get clock_flag node failed!\n");
        /*lint -save -e801*/
        goto error;
        /*lint -restore -e801*/
    }

    for(i = 0; (u32)i < g_baseinfo.group_num; i++)
    {
        /*��ȡ����ַ*/
        g_baseinfo.group[i].base = of_iomap(dev_node, i);
        if (NULL == g_baseinfo.group[i].base)
        {
            gpio_print_error("remap GPIO GROUP %d fail\n",i);
            /*lint -save -e801*/
            goto error;
            /*lint -restore -e801*/
        }

        /*��ȡ�жϺ�*/
        g_baseinfo.group[i].irq = irq_of_parse_and_map(dev_node, i);

        /*�ҽ��жϺ���*/
        irq = (int)g_baseinfo.group[i].irq;
        if ((int)GPIO_INVALID_IRQ != irq){
            writel(0 ,  (u32)g_baseinfo.group[i].base + ie_reg);
            ret = request_irq(irq, gpio_irq_handle, 0, "gpio", (void *)irq);
            if(ret){
                gpio_print_error("gpio irq is invalid! error is 0x%x,gpio group is %d\n",irq, i);
                /*lint -save -e801*/
                goto error;
                /*lint -restore -e801*/
            }
        }

        /*��ʼ��lock*/
        spin_lock_init(&g_baseinfo.group[i].lock);

        /*��ȡʱ��*/
        if(g_baseinfo.clk_flag){

            memset_s  (clk_name, NAME_LENTH, 0 , NAME_LENTH);
            snprintf_s(clk_name, NAME_LENTH, NAME_LENTH, "gpio%d_clk", i); /*lint !e119*/
            g_baseinfo.group[i].clk = (struct clk *)clk_get(NULL, clk_name);
            if(IS_ERR(g_baseinfo.group[i].clk))
            {
                gpio_print_error("gpio%d clk cannot get, 0x%x.\n", i, g_baseinfo.group[i].clk);
                /*lint -save -e801*/
                goto error;
                /*lint -restore -e801*/
            }

            /*MBB GPIO CLK ��Ҫ���ü���*/
            if(0 != clk_enable(g_baseinfo.group[i].clk))
            {
                gpio_print_error("gpio%d clk enable is fail, 0x%x.\n", i, g_baseinfo.group[i].clk);
                /*lint -save -e801*/
                goto error;
                /*lint -restore -e801*/
            }
        }
        
    }

    gpio_print_error("gpio init ok.\n");

    return GPIO_OK;

error:
    osl_free(clk_name);
    osl_free(g_baseinfo.group);
    gpio_print_error("gpio init fail!\n");
    return GPIO_ERROR;

}

#ifdef __cplusplus
}
#endif

