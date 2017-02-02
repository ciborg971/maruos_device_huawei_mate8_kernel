
/*lint --e{438,537,732}*/
#include <osl_common.h>
#include <bsp_softtimer.h>
#include <soc_clk.h>
#include <bsp_memmap.h>
#include <bsp_om.h>
#include <bsp_hardtimer.h>
#include <libfdt.h>
#include <soc_timer.h>
#include "softtimer_balong.h"
#include "m3_dump.h"
#ifdef __cplusplus
extern "C" 
{
#endif
#define  softtimer_print(fmt, ...)    (bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_SOFTTIMER, "[softtimer]: <%s> "fmt"\n", __FUNCTION__, ##__VA_ARGS__))
/*lint --e{133 } */
osSemaphoreDef(soft_timer_sem);
static void thread_softtimer_fun(void const *obj);
osThreadDef(thread_softtimer_fun, osPriorityAboveNormal, 1, 1024);
irqreturn_t IntTimerHandler(void);

struct softtimer_ctrl
{
    struct list_head timer_list_head;
    u32 softtimer_start_value;                         /*��¼ÿ������timer������ʼֵ                     */
    u32 hard_timer_id_addr;                            /*��timerʹ�õ�����timer��ַ                     */
    osThreadId thread_softtimer_id;                /*��¼����������                                 */
    osSemaphoreId      soft_timer_sem;    
    u32 clk;                                           /*��ʹ������timer��ʱ��Ƶ��                       */
};

static struct softtimer_ctrl timer_control;       
#ifdef TIMER_ARM_FEATURE
static u32 __inline__ timer_get_value(void)
{
	u32 ret = 0;
	ret=readl(timer_control.hard_timer_id_addr + ARM_ODD_CTRL_OFFSET);
	if(ret&0x80)
	{
		ret=readl(timer_control.hard_timer_id_addr + ARM_ODD_VALUE_OFFSET);
		if(ret >timer_control.softtimer_start_value)
			return timer_control.softtimer_start_value;
		else
			return ret;
	}
	else
		return 0;
}
static void start_hard_timer(u32 ulvalue )
{
    u32 ret = 0;
    timer_control.softtimer_start_value = ulvalue;
    ret = readl(timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    writel(ret&(~0x80),timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    if(0==ulvalue)
	ulvalue=1;
    writel(ulvalue, timer_control.hard_timer_id_addr + ARM_ODD_LOAD_OFFSET);
    ret = readl(timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
	/*one shot mode, 32bit cnt,unmask irq,start timer*/
    writel(ret |0xA3, timer_control.hard_timer_id_addr +ARM_ODD_CTRL_OFFSET);
}
static void stop_hard_timer()
{
    u32 ret = 0;
    ret = readl(timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    writel(ret&(~0x80),timer_control.hard_timer_id_addr+ARM_ODD_CTRL_OFFSET);
    timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
}
#elif defined(TIMER_SYNOPSIS_FEATURE)
static u32 __inline__ timer_get_value(void)
{
	u32 ret = 0;
	ret = readl(timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET); 
	if(ret&0x1)
	{
		ret=readl(timer_control.hard_timer_id_addr + HI_TIMER_CURRENTVALUE_OFFSET);
		if(ret >timer_control.softtimer_start_value)
			return timer_control.softtimer_start_value;
		else
			return ret;
	}
	else
		return 0;
	
}

static void start_hard_timer(u32 ulvalue )
{
    u32 ret = 0;
    timer_control.softtimer_start_value = ulvalue;
    writel(0x0, timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
    while(readl(timer_control.hard_timer_id_addr +HI_TIMER_CURRENTVALUE_OFFSET)!=(u32)0xffffffff)
    {}
    writel(ulvalue, timer_control.hard_timer_id_addr + HI_TIMER_LOADCOUNT_OFFSET);
    writel(0x1, timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
    do{
		ret = readl(timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
	}while((ret&0x1)!=0x1);
    timer_control.softtimer_start_value = ulvalue;
}

static void stop_hard_timer()
{
    u32 ret = 0;
    writel(0x0, timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
    do{
		ret = readl(timer_control.hard_timer_id_addr + HI_TIMER_CONTROLREG_OFFSET);
	}while(ret&0x1);
    timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
}
#else
#endif
static u32 hard_timer_elapsed_time()
{
    u32 ulTempValue = 0;
    if ( ELAPESD_TIME_INVAILD == timer_control.softtimer_start_value)
    {
        return 0;
    }
    ulTempValue = timer_get_value();
    return ((timer_control.softtimer_start_value < ulTempValue) ? 0 : (timer_control.softtimer_start_value - ulTempValue+1));
}

void bsp_softtimer_add(struct softtimer_list * timer)
{
    u32 elapsed_time = 0;
    struct softtimer_list *p = NULL;
    unsigned long flags = 0;
    if (NULL == timer)
    {
        softtimer_print("para  NULL\n");
        return;
    }
    local_irq_save(flags);
    /*����Ѿ��ڳ�ʱ�����У��򲻲���*/
    if(!list_empty(&timer->entry))
    {
    	 local_irq_restore(flags);
    	 return;
    }
    timer->timeout = timer->count_num;
    elapsed_time = hard_timer_elapsed_time();
    timer->timeout += elapsed_time;
    /*���timer����Ϊ�գ������ͷ���*/
    if (list_empty(&(timer_control.timer_list_head)))
    {
        list_add_tail(&(timer->entry),&(timer_control.timer_list_head));
    }
    /*�������Ϊ�գ����ճ�ʱʱ���С�������*/
    else
    {
        p=list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);
        if((TIMER_TRUE==p->is_running)&&(0==elapsed_time))
        {
            timer->timeout += p->timeout;
        }
	    if(elapsed_time!=0)
    	{
    	     timer->timeout -= 1;
	         elapsed_time     -= 1;
    	}
        list_for_each_entry(p,&(timer_control.timer_list_head),entry)
        {
            if(p->timeout <= timer->timeout)
	        {
	            timer->timeout -= p->timeout;
	        }
	        else
	        {
	            break;
	        }
	    }
	    if(&(p->entry)!=&(timer_control.timer_list_head))
	    {
	        p->timeout -= timer->timeout;
	    }
	    list_add_tail(&(timer->entry),&(p->entry));
    }
    if (timer_control.timer_list_head.next == &(timer->entry))
    {
        timer->timeout -= elapsed_time;
	 if ((timer->entry.next)!=(&(timer_control.timer_list_head)))
	 {
	     p = list_entry(timer->entry.next,struct softtimer_list,entry);
	     if(TIMER_TRUE==p->is_running)
	     {
	         p->is_running = TIMER_FALSE;
	     }
	 }
	 timer->is_running = TIMER_TRUE;
	 start_hard_timer(timer->timeout);
    }
    local_irq_restore(flags);
}
s32 bsp_softtimer_delete(struct softtimer_list * timer)
{
    struct softtimer_list * p=NULL;
    unsigned long flags;
    if (NULL == timer)
    {
        softtimer_print("NULL para \n");
        return ERROR;
    }
    local_irq_save(flags);
    if (list_empty(&timer->entry))
    {
        local_irq_restore(flags);
   	 return NOT_ACTIVE;
    }
    else
    {
        if(timer->entry.next == &(timer_control.timer_list_head))/*���ɾ���������һ���ڵ㣬ֱ��ɾ��*/
        {
            timer->is_running = TIMER_FALSE;
            list_del_init(&(timer->entry));
        }
	 /*���ɾ�����������е�һ�����,����������������*/
        else if((timer->entry.prev == &(timer_control.timer_list_head))
			&&(timer->entry.next != &(timer_control.timer_list_head)))
        {
            timer->is_running = TIMER_FALSE;
            list_del_init(&(timer->entry));
			p=list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);/**/
			p->timeout += timer->timeout -hard_timer_elapsed_time();
			start_hard_timer(p->timeout);
			p->is_running = TIMER_TRUE;
        }
	 /*���ɾ�������м�ڵ�*/
        else
        {
            p = list_entry(timer->entry.next,struct softtimer_list,entry);
	        p->timeout += timer->timeout;
	        timer->is_running = TIMER_FALSE;
	        list_del_init(&(timer->entry));
        }
    }
    if (list_empty(&(timer_control.timer_list_head)))/*���ɾ�����º�����Ϊ�գ���ֹͣ����*/
    {
        stop_hard_timer();
    }
    local_irq_restore(flags);
    return OK;
}

s32 bsp_softtimer_modify(struct softtimer_list *timer,u32 new_expire_time)
{
    if((NULL == timer)||(!list_empty(&timer->entry)) )
    {
        return ERROR;
    }
    if((new_expire_time) < (0xFFFFFFFF/timer_control.clk)) 
    {
        timer->timeout= (timer_control.clk* new_expire_time)/1000;
    }
    else /* ��ֹ�˷���� */ 
    {
        timer->timeout= timer_control.clk * (new_expire_time/1000);
    }
    timer->count_num = timer->timeout;
    return OK;
}

s32 bsp_softtimer_create(struct softtimer_list *sft_info)
{
    INIT_LIST_HEAD(&(sft_info->entry));
    sft_info->is_running = TIMER_FALSE;
    sft_info->init_flags = TIMER_INIT_FLAG;
    	/*����������ֵ���򷵻�ʧ��,��λΪms*/
	if(sft_info->timeout>0xFFFFFFFF/timer_control.clk*1000)
	{
		softtimer_print("too long\n");
		return ERROR;
    }
    if((sft_info->timeout) < 0xFFFFFFFF/timer_control.clk)  /* ��С��SOFTTIMER_MAX_LENGTH�ļ�ʱ�����Ա��־��� */
    {
	  sft_info->timeout= (timer_control.clk*(sft_info->timeout))/1000;
    }
    else /* ��ֹ�˷���� */ 
    {
	 sft_info->timeout= timer_control.clk* ((sft_info->timeout)/1000);
    }	
    sft_info->count_num = sft_info->timeout;
     return OK;
}
s32 bsp_softtimer_free(struct softtimer_list *p)
{
    if ((NULL == p)||(!list_empty(&p->entry)))
	{
	    return ERROR;
    }
	p->init_flags = 0;
	 return OK;   
}
static void thread_softtimer_fun(void const *obj)
{
	struct softtimer_list     *p = NULL;
	unsigned long flags;
	softtimer_func func =NULL;
	u32 para = 0;
	/* coverity[no_escape] */
	/*lint --e{569 } */
	for( ; ; )
	{
	        /* coverity[sleep] */
		osSemaphoreWait(timer_control.soft_timer_sem, osWaitForever);
		 /* coverity[lock_acquire] */
		local_irq_save(flags);
		timer_control.softtimer_start_value = ELAPESD_TIME_INVAILD;
		if (!list_empty(&(timer_control.timer_list_head)))
		{
			p = list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);
			if(p->is_running == TIMER_TRUE)
			{
				list_del_init(&p->entry);
				p->is_running = TIMER_FALSE;
				func = p->func;
				para = p->para;
				local_irq_restore(flags); 
				func(para);			
				local_irq_save(flags);
				while(!list_empty(&(timer_control.timer_list_head)))
				{
					p=list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);
					if(0==p->timeout)
					{
						list_del_init(&p->entry);
						p->is_running = TIMER_FALSE;
						func = p->func;
						para = p->para;
						local_irq_restore(flags); 
						func(para);
						local_irq_save(flags);
					}
					else
						break;
				}
				if (!list_empty(&(timer_control.timer_list_head)))/*�������δ��ʱ��ʱ��*/
				{
					p=list_first_entry(&(timer_control.timer_list_head),struct softtimer_list,entry);
					p->is_running = TIMER_TRUE;
					start_hard_timer(p->timeout);
				}
				else 
				{  
					stop_hard_timer();
				}	
			}
			else  if (p->is_running == TIMER_FALSE)
			{
				p->is_running = TIMER_TRUE;
				start_hard_timer(p->timeout);
			}
		}
		else
		{
			stop_hard_timer();
		}
		local_irq_restore(flags); 
	} 
}
#ifdef TIMER_ARM_FEATURE
irqreturn_t IntTimerHandler(void)
{
	 u32 readValue = 0;    
    /*1����ȡӲ����ʱ�����ж�״̬
	 2��������жϣ������жϣ�ͬʱ�ͷ��ź���
   */
    dump_int_enter(get_irq());
    readValue = readl(timer_control.hard_timer_id_addr+ARM_ODD_INTMIS_OFFSET);
    if (0 != readValue)
    {
        writel(0x1,timer_control.hard_timer_id_addr+ARM_ODD_INTCLR_OFFSET);
        osSemaphoreRelease(timer_control.soft_timer_sem);
    }

	dump_int_exit(get_irq());

	return IRQ_HANDLED;
}
#elif defined(TIMER_SYNOPSIS_FEATURE)
irqreturn_t IntTimerHandler(void)
{
	 u32 readValue = 0;    
    /*1����ȡӲ����ʱ�����ж�״̬
	 2��������жϣ������жϣ�ͬʱ�ͷ��ź���
   */
    dump_int_enter(get_irq());    
    readValue = readl(timer_control.hard_timer_id_addr+HI_TIMER_INTSTATUS_OFFSET);
    if (0 != readValue)
    {
        readValue = readl(timer_control.hard_timer_id_addr+HI_TIMER_EOI_OFFSET);
        osSemaphoreRelease(timer_control.soft_timer_sem);
    }

    dump_int_exit(get_irq());

    return IRQ_HANDLED;
}
#else
#endif
int  bsp_softtimer_init(void)
{
    struct device_node *ptr_device_node = NULL;
	const char *compatible_name = "hisilicon,softtimer_m3";
	char *ret_of_iomap = NULL;
	unsigned int irq_no_mcpu_softtimer = 0;

    /* ��ȡ����ַ��ӳ�� */
	ptr_device_node = of_find_compatible_node(NULL, NULL, compatible_name);
	if (!ptr_device_node)  /* �Ҳ����ڵ� */
	{
		softtimer_print("1 er\n");
		return ERROR;
	}
    ret_of_iomap = of_iomap(ptr_device_node, 0); 
	if (!ret_of_iomap)  /* ӳ����� */
	{
		return ERROR;
	}
	timer_control.hard_timer_id_addr=(u32)ret_of_iomap;
	//printk(" timer_control.hard_timer_id_addr =0x%x\n", timer_control.hard_timer_id_addr);
	 /* ��ȡ�жϺ� */
	irq_no_mcpu_softtimer= irq_of_parse_and_map(ptr_device_node, 0);
	if(of_property_read_u32_array(ptr_device_node, "clock-frequency", &timer_control.clk, 1))
	{
		 softtimer_print("2 er\n");
		 return -1;
	}
    INIT_LIST_HEAD(&(timer_control.timer_list_head));
    timer_control.softtimer_start_value  = ELAPESD_TIME_INVAILD;
    
	timer_control.soft_timer_sem=osSemaphoreCreate(osSemaphore(soft_timer_sem),SEM_FULL);
	if(NULL == timer_control.soft_timer_sem)
	{
		softtimer_print("3 err\n");
		return ERROR;
	}
	/*lint --e{569 } */
	osSemaphoreWait(timer_control.soft_timer_sem, osWaitForever);
	 timer_control.thread_softtimer_id = osThreadCreate(osThread(thread_softtimer_fun), (void*)0);
	if (timer_control.thread_softtimer_id == NULL)
	{
		softtimer_print("4 err\n");
		return ERROR;
	}
	stop_hard_timer();
    	(void)request_irq(irq_no_mcpu_softtimer, (irq_handler_t)IntTimerHandler, 0, "softtimer irq", 0);
	enable_irq(irq_no_mcpu_softtimer);
	softtimer_print("ok\n");
	return 0;
}
#ifdef __cplusplus
}
#endif


