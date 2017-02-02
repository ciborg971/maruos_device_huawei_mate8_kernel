
#include <osl_types.h>
#include <mdrv_public.h>
#include <mdrv_leds.h>
#include <bsp_leds.h>
#include <bsp_om.h>
#include <bsp_softtimer.h>

struct softtimer_list led_softtimer ; 
unsigned char g_cur_work_state = LED_LIGHT_STATE_MAX; /* �����ϲ㹤��״̬ */
unsigned char g_new_work_state = LED_LIGHT_STATE_MAX; /* ��ʼ���Ĺ���״̬��g_cur_work_state����һ�� */
pFUNCPTR p_func_tled_state_get = NULL;              /* new BSP_TLED_LedFlush, ���ڹ����ϲ�ע��Ļص���������ȡ�ϲ㹤��״̬ */
unsigned int led_debug_level;                       /* for LED_TRACE level */

/*******************************************************************************
 * FUNC NAME:
 * led_default_callback() 
 * Function     : C����timerĬ�ϻص�����
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : �µĹ���״̬
 * Decription   : ���ϲ�ע��ص�����֮ǰ����ΪĬ�ϵĻص�����
 ************************************************************************/
unsigned char led_default_callback(void)
{
    return g_new_work_state;
}

/*******************************************************************************
 * FUNC NAME:
 * led_state_check_callback() - C����timer�ص�����
 * Function     : 
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : null
 * Decription   : 
 ************************************************************************/
void led_state_check_callback(void)
{
    int ret = LED_ERROR;

    /* ��ȡ�ϲ�״̬ */
    if (NULL != p_func_tled_state_get)
    {
        g_new_work_state = (unsigned char)((*p_func_tled_state_get)());
    }
    else
    {
        return; 
    }
    
    LED_TRACE(LED_DEBUG_LEVEL(INFO), "[%s]LED get new state success, new state %d\n", __FUNCTION__, g_new_work_state);
    
    /* �뵱ǰ״̬���бȽϣ�����ͬ������µ�ǰ״̬��֪ͨA������ */
    if(g_cur_work_state != g_new_work_state)
    {
        ret = bsp_icc_send(ICC_CPU_APP, LED_ICC_CHN_ID, (unsigned char*)&g_new_work_state, sizeof(unsigned char)); 
        if(ret != (int)sizeof(unsigned char))
        {
    		LED_TRACE(LED_DEBUG_LEVEL(ERROR), "[%s]icc send failed, new state %d, length %d\n", 
                __FUNCTION__, g_new_work_state, ret);
    		return;
        }

   		LED_TRACE(LED_DEBUG_LEVEL(INFO), "[%s]icc send success, new state %d\n", __FUNCTION__, g_new_work_state);
        
        g_cur_work_state = g_new_work_state;
    }
    
    LED_TRACE(LED_DEBUG_LEVEL(INFO), "[%s]LED same state, skip\n", __FUNCTION__);

    bsp_softtimer_add(&led_softtimer);

    return;
}

/*******************************************************************************
 * FUNC NAME:
 * led_softtimer_create() 
 * Function     : ������timer
 * Arguments
 *      input   : @timer - timer�Ķ�ʱʱ��
 *                @wake_type - timer��CPU�Ļ�������
 *      output  : null
 *
 * Return       : LED_OK - �ɹ���else - ʧ��
 * Decription   : null
 ************************************************************************/
int led_softtimer_create(unsigned int time, enum wakeup wake_type)
{
	led_softtimer.func = (softtimer_func)led_state_check_callback;
	led_softtimer.para = 0;                              
	led_softtimer.timeout = time;                        /* ��ʱ���ȣ���λms */
	led_softtimer.wake_type = wake_type;


	if (bsp_softtimer_create(&led_softtimer))
	{
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s]ERROR: softtimer create failed\n", __FUNCTION__);
		return LED_ERROR;
	}
    
	bsp_softtimer_add(&led_softtimer);

    LED_TRACE(LED_DEBUG_LEVEL(INFO), "LED create softtimer OK\n");
    
    return LED_OK;
}

/*******************************************************************************
 * FUNC NAME:
 * bsp_led_init() 
 * Function     : c��led��ʼ������
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : LED_OK - �ɹ���else - ʧ��
 * Decription   : 
 ************************************************************************/
int bsp_led_init(void)
{
    int ret = LED_ERROR;

    /* ��ʼ���ϲ㹤��״̬ */
    g_cur_work_state = LED_LIGHT_STATE_MAX;

    p_func_tled_state_get = (pFUNCPTR)led_default_callback;

    /* ������timer(������)��ע��ص����� */
    ret = led_softtimer_create(LED_TIME_BASE_UNIT, SOFTTIMER_NOWAKE);
	if(ret != LED_OK)
	{
        LED_TRACE(LED_DEBUG_LEVEL(ERROR),"[%s] softtimer create failed, ret = 0x%x\n", __FUNCTION__, ret);
        return ret;
	}   

    LED_TRACE(LED_DEBUG_LEVEL(ALWAYS), "LED init OK\n");

    return ret;
}

/*******************************************************************************
 * FUNC NAME:
 * led_set_debug_level() 
 * Function     : open all debug level
 * Arguments
 *      input   : null
 *      output  : null
 *
 * Return       : 
 * Decription   : 
 ************************************************************************/
void led_set_debug_level(void)
{
    led_debug_level = LED_DEBUG_ALL;
}

/*****************************************************************************
 �� �� ��  : drv_led_flash
 ��������  : ��ɫ�����á�
 �������  : status����ɫ�Ƶ�״̬
 �������  : �ޡ�
 �� �� ֵ  : 0:  �����ɹ���
             -1������ʧ�ܡ�
*****************************************************************************/
int drv_led_flash(unsigned long state)
{
    g_new_work_state = (unsigned char)state;
    return 0;
}

/****************************************************************************
 �� �� ��  : drv_led_state_func_reg
 ��������  : ���ӿ�Ϊ�ṩ��Э��ջ�Ĺ��Ӻ��������ڻ�ȡЭ��ջ�ĵ��״̬��
 �������  : Э��ջ��ȡ���״̬������ָ�롣
 �������  : �ޡ�
 �� �� ֵ  : �ޡ�
 ע������  : �ޡ�

******************************************************************************/
void drv_led_state_func_reg (pFUNCPTR p)
{
    p_func_tled_state_get = p;
}