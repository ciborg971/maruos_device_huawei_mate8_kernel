
#ifndef _GPIO_PL061_H_
#define _GPIO_PL061_H_

#ifdef __cplusplus
extern "C" {
#endif

#define  OF_INTER_OFFSET               32
#define  NAME_LENTH                    32

#define  gpio_print_error(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_GPIO, "[gpio]: <%s> <%d> "fmt, __FUNCTION__, __LINE__, ##__VA_ARGS__))
#define  gpio_print_info(fmt, ...)     (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_GPIO, "[gpio]: "fmt, ##__VA_ARGS__))

struct gpio_pl061{
    void*         base;
	u32           irq;
	const char*   name[PL061_GPIO_NR];
	irq_handler_t handler[PL061_GPIO_NR];
    spinlock_t    lock;
    struct clk*   clk;
}; 

typedef struct{
    struct gpio_pl061 *group;     /*gpio ��Ϣ*/
    unsigned int       group_num; /*gpio ����*/
    unsigned int       max_pin;   /*gpio ÿ��ܽ���*/
    unsigned int       clk_flag;  /*clk�Ƿ�Ҫ���ü���*/
}GPIO_INFO_S;

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

#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif    /* End #define _GPIO_BALONG_H_ */
