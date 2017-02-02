
/*
 *  Copyright (C) 2002 ARM Ltd.
 *  All Rights Reserved
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

/******************************************************************************

 ******************************************************************************
  �� �� ��   : pwrctrl_hotplug_mgr.c
  �� �� ��   : ����
  ��    ��   : ʯ����61250
  ��������   : 2012��9��2��
  ����޸�   :
  ��������   : CPU  HOTPLUG ���Ʋ����
  �����б�   :
              pwrctrl_cpu_load
              pwrctrl_hotplug_timer_workqueue
              pwrctrl_hotlpug_timer_init
              pwrctrl_hotlpug_timer_exit
              pwrctrl_hotlpug_gov_init
              pwrctrl_hotlpug_gov_exit
              pwrctrl_hotlpug_gov_dbs
              pwrctrl_cpu_down_verfiy
              pwrctrl_cpu_up_verfiy
         pwrctrl_cpunumbermax_handle
         pwrctrl_cpunumbermin_handle
         pwrctrl_cpunumberlock_handle
         pwrctrl_hotplug_parm_set
              pwrctrl_hotplug_mcu_control_isr
              pwrctrl_hotplug_mcu_control_init
              pwrctrl_hotplug_mcu_control_uninit
              pwrctrl_hotlpug_init
              pwrctrl_hotlpug_exit
  �޸���ʷ   :
  1.��    ��   : 2012��9��2��
    ��    ��   :  ʯ����61250
    �޸�����   : �����ļ�

******************************************************************************/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/

#include <linux/module.h>
//#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/pm.h>
#include <linux/suspend.h>
#include <linux/cpu.h>
#include <linux/notifier.h>
#include <linux/reboot.h>
#include <asm/memory.h>
#include <linux/cpufreq.h>
#include <linux/threads.h>
#include <linux/tick.h>

#include <mach/pwrctrl/pwrctrl_common.h>
#include <mach/pwrctrl/pwrctrl_hotplug_mgr.h>
#include <mach/pwrctrl/pwrctrl_hotplug_platform.h>
#include <mach/pwrctrl/pwrctrl_hotplug_qos.h>
#include <drv_ipcm.h>
#include <linux/pm_qos_params.h>

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
PWRCTRL_HOTPLUG_PARA_STRU     pwrctrl_hotplug_para;
PWRCTRL_HOTPLUG_CPUQOS_STRU   pwrctrl_hotplug_cpuqos = {0,4,1};
PWRCTRL_HOTPLUG_EXC_LOG_STRU *ppwrctrl_hotplug_exc_log = NULL;

extern void k3v2_secondary_startup(void);

/* pm_qos interface global val*/
struct pm_qos_lst {
	struct pm_qos_request_list *lst;
	int qos_class;
	s32 dvalue;
};

static int g_cpuload_debug = 0;
static struct pm_qos_request_list g_cpumaxlimits;
static struct pm_qos_request_list g_cpuminlimits;

static struct pm_qos_lst pm_qos_list[] = {
{&g_cpumaxlimits, PM_QOS_CPU_MAX_PROFILE, PM_QOS_CPU_MAXPROFILE_DEFAULT_VALUE},
{&g_cpuminlimits, PM_QOS_CPU_MIN_PROFILE, PM_QOS_CPU_MINPROFILE_DEFAULT_VALUE},
};

/* dbs_mutex protects dbs_enable in governor start/stop.
 */
static DEFINE_MUTEX(dbs_mutex);

int pwrctrl_hotplug_gov_dbs(struct cpufreq_policy *policy, unsigned int event) ;

struct cpufreq_governor pwrctrl_hotplug_gov = {
    .name     = "pwrctrl_hotplug",
    .governor = pwrctrl_hotplug_gov_dbs,
    .owner    = THIS_MODULE,
};

struct workqueue_struct *pwrctrl_autohotplug_wq=NULL;
struct workqueue_struct *pwrctrl_mcuhotplug_wq=NULL;
struct delayed_work      pwrctrl_hotplug_wk;
struct work_struct       pwrctrl_mcuhotplug_wk;


#define CPU_FREQ_ADD_THLD 800000 /*800Mhz*/
#define DEF_MAX_TASK_FIFO 4
#define DEF_TASK_MULTIPLIER 10

u32_t avg_task_fifo[DEF_MAX_TASK_FIFO]={0}; /* store the number of RQ */
s32_t avg_task_index=0;
u32_t cnt_thread_add = 0;
u32_t cnt_load_add = 0;
u32_t cnt_thread_sub = 0;
u32_t cnt_load_sub = 0;

/*#define CPU_LOCK_MIN_DBG*/
/*#define CPU_LOCK_MAX_DBG*/

/*��ֵ���Ż�*/
static PWRCTRL_HOTPLUG_LEVEL_STRU hotplug_up_defaultlevel[NR_CPUS_NUMBER]=
{
#ifdef CPU_LOCK_MIN_DBG
    {-1,-1,5,5},
    {-1,-1,5,5},
    {-1,-1,5,5},
    {-1,-1,-1,-1}
#else
    {70,30,0,7},
    {60,40,0,8},
    {50,55,0,5},
    {-1,-1,-1,-1}
#endif
};

static PWRCTRL_HOTPLUG_LEVEL_STRU hotplug_down_defaultlevel[NR_CPUS_NUMBER]=
{
#ifdef CPU_LOCK_MAX_DBG
    {0,0,-1,-1},
    {0,0,1,5},
    {0,0,1,5},
    {0,0,1,5}
#else
    {0,0,-1,-1},
    {12,15,8,8},
    {25,25,5,5},
    {35,35,5,5}
#endif
};

struct cpu_info_s {
    cputime64_t prev_cpu_idle;
    cputime64_t prev_cpu_wall;
    cputime64_t prev_cpu_nice;
};
static DEFINE_PER_CPU(struct cpu_info_s, hp_cpu_info);

/*************************************************************************
 �� �� ��  : pwrctrl_get_cpuidle_time
 ��������  :  ��ȡCPU����ʱ��
 �������  : CPU ID
 �������  : wall
 �� �� ֵ  : idleʱ��
�޸ļ�¼   ��
*****************************************************************/

static inline  cputime64_t pwrctrl_get_cpuidle_time(unsigned int cpu, cputime64_t *wall)
{
    u64 idle_time;
    u64 iowait_time;

    /* cpufreq-hotplug always assumes CONFIG_NO_HZ */
    idle_time = get_cpu_idle_time_us(cpu, wall);

    iowait_time = get_cpu_iowait_time_us(cpu, wall);

    /* cpufreq-hotplug always assumes CONFIG_NO_HZ */
    if (iowait_time != -1ULL && idle_time >= iowait_time)
        idle_time -= iowait_time;

    return idle_time;
}

void update_idletime(unsigned int cpu_on_line_num)
{
    cputime64_t cur_wall_time = 0, cur_idle_time;
    struct cpu_info_s *j_info;
    j_info = &per_cpu(hp_cpu_info, cpu_on_line_num);
    cur_idle_time = pwrctrl_get_cpuidle_time(cpu_on_line_num, &cur_wall_time);
    j_info->prev_cpu_wall = cur_wall_time;
    j_info->prev_cpu_idle = cur_idle_time;
}

/*************************************************************************
 �� �� ��  : pwrctrl_getcpu_load
 ��������  :  ��ȡƽ��CPU���С����
 �������  :
 �������  : CPU���С����
 �� �� ֵ  : ����CPUƽ������
�޸ļ�¼   ��
*****************************************************************/
u32_t pwrctrl_getcpu_load (u32_t *max_load,u32_t *min_load)
{


    unsigned int j=0;
    u32_t sum_load=0;
    u32_t aver_load=0;


    unsigned int load;
    unsigned int idle_time, wall_time;
    cputime64_t cur_wall_time = 0, cur_idle_time;
    struct cpu_info_s *j_info;

    for_each_online_cpu(j)
    {


        j_info = &per_cpu(hp_cpu_info, j);

        /* update both cur_idle_time and cur_wall_time */
        cur_idle_time = pwrctrl_get_cpuidle_time(j, &cur_wall_time);

        /* how much wall time has passed since last iteration? */
        wall_time = (unsigned int) cputime64_sub(cur_wall_time,
                j_info->prev_cpu_wall);
        j_info->prev_cpu_wall = cur_wall_time;

        /* how much idle time has passed since last iteration? */
        idle_time = (unsigned int) cputime64_sub(cur_idle_time,
                j_info->prev_cpu_idle);

        j_info->prev_cpu_idle = cur_idle_time;

        if (unlikely(!wall_time || wall_time < idle_time))
            continue;

        /* load is the percentage of time not spent in idle */
        load = 100 * (wall_time - idle_time) / wall_time;

        /* keep track of highest single load across all CPUs */
        if (load > *max_load)
            *max_load = load;
        if (load < *min_load)
            *min_load = load;

        if(g_cpuload_debug != 0)
        {
            printk(KERN_ERR"cpu(%d) load:%d\r\n", j, load);
        }

        sum_load=sum_load+load;
    }
    aver_load=sum_load/num_online_cpus();
    return aver_load;
}

void get_cpu_load ()
{
	u32_t max_load = 0;
	u32_t min_load = 100;

       g_cpuload_debug = 1;
	pwrctrl_getcpu_load(&max_load, &min_load);
       g_cpuload_debug = 0;
}
/*************************************************************************
 �� �� ��  : pwrctrl_getcpu_avrtask
 ��������  :  ��ȡƽ��CPU���߸���*100
 �������  :
 �������  : ��
 �� �� ֵ  : ƽ��CPU���߸���*100
�޸ļ�¼   ��
************************************************************************/

local_t u32_t pwrctrl_getcpu_avrtask (void)
{
    s32_t i = 0, j = avg_task_index;
    u32_t rq_avg = 0, div_sum = 0;
    u32_t task_weitht = 0;

    avg_task_fifo[avg_task_index] = nr_running() * DEF_TASK_MULTIPLIER;

    /* compute the sum of task by weighting */
    for (i = 0; i  < DEF_MAX_TASK_FIFO; i++)
    {
        task_weitht = DEF_MAX_TASK_FIFO - i;
        rq_avg += avg_task_fifo[j] * task_weitht;
        div_sum +=  task_weitht;

        if (0 == j)
        {
            j = DEF_MAX_TASK_FIFO;
        }
        j--;
    }

    /* compute avg task */
    rq_avg  /=  div_sum;

    avg_task_index++;

    /* return to first element if we're at the circular buffer's end */
    if (DEF_MAX_TASK_FIFO == avg_task_index)
    {
        avg_task_index = 0;
    }

    return rq_avg;
}


/*************************************************************************
 �� �� ��  : pwrctrl_cpu_down_verify
 ��������  : cpu_down �Ϸ��Լ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : OK/ERROR
�޸ļ�¼   ��
************************************************************************/
local_t s32_t pwrctrl_cpu_down_verify(void)
{
    u32_t cpu_online_num = num_online_cpus();

    CPU_LOCK_CHECK;

    if(cpu_online_num>pwrctrl_hotplug_cpuqos.cpu_number_min)
    {
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_cpu_down_verify ok\n",0,0,0,0,0,0);
        return RET_OK;
    }
    else
    {
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, " pwrctrl_cpu_down_verify fail:  cpu_number_min:%d\n",pwrctrl_hotplug_cpuqos.cpu_number_min,0,0,0,0,0);
        return RET_ERR;
    }

}

/*************************************************************************
 �� �� ��  : pwrctrl_cpu_verify_up
 ��������  : cpu_up �Ϸ��Լ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : OK/ERROR
�޸ļ�¼   ��
************************************************************************/
local_t int pwrctrl_cpu_up_verify (void)
{

    u32_t cpu_online_num = num_online_cpus();

    CPU_LOCK_CHECK;

    if(cpu_online_num<pwrctrl_hotplug_cpuqos.cpu_number_max)
    {
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"pwrctrl_cpu_up_verify ok:  cpu_number_max:%d online_num:%d\n",
                pwrctrl_hotplug_cpuqos.cpu_number_max,cpu_online_num,0,0,0,0);
        return RET_OK;
    }
    else
    {
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_cpu_up_verify fail:  cpu_number_max:%d online_num:%d\n",
                pwrctrl_hotplug_cpuqos.cpu_number_max,cpu_online_num,0,0,0,0);
        return RET_ERR;
    }

}

/*************************************************************************
 �� �� ��  : pwrctrl_set_load_task_cnt
 ��������  : ���ݸ��غ�������������load��task����
 �������  :
           load    ƽ������
           task    ƽ��������
           cpu_online_num   ����cpu����
           hotplug_para     hotplug����ʱ����
 �������  :
           load_cnt_add     �������Ӽ���
           task_cnt_add     �������Ӽ���
           load_cnt_sub     ���ؼ��ټ���
           task_cnt_sub     ������ټ���
 �� �� ֵ  : OK/ERROR
�޸ļ�¼   ��
************************************************************************/
int pwrctrl_set_load_task_cnt(u32_t load, u32_t task, u32_t cpu_online_num, PWRCTRL_HOTPLUG_PARA_STRU *hotplug_para, u32_t *load_cnt_add, u32_t *task_cnt_add, u32_t *load_cnt_sub, u32_t *task_cnt_sub)
{
    if(NULL == load_cnt_add || NULL == load_cnt_sub ||  \
        NULL == task_cnt_add || NULL == task_cnt_sub ||NULL == hotplug_para)
    {
        PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_set_load_task_cnt null pointer!!!\n",0,0,0,0,0,0);
        return RET_ERR;
    }
    PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_set_load_task_cnt,load=%d,task=%d!!!\n",load,task,0,0,0,0);

    /*������ش��ڵ�ǰ�����������ޣ��������Ӽ���++*/
    if(load > (hotplug_para->hotplug_up_level[cpu_online_num-1]).cpu_load)
    {
        (*load_cnt_add)++;
        *load_cnt_sub = 0;
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_set_load_task_cnt,load++!!!\n",0,0,0,0,0,0);
    }/*�������С�ڵ�ǰ�����½����ޣ����ؼ��ټ���++*/
    else if(load < (hotplug_para->hotplug_down_level[cpu_online_num-1]).cpu_load)
    {
        (*load_cnt_sub)++;
        *load_cnt_add = 0;
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_set_load_task_cnt,load--!!!\n",0,0,0,0,0,0);
    }
    else
    {
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "cpu num:%d avr_load:%d\n", cpu_online_num, load,0,0,0,0);
    }

    /*������������ڵ�ǰ��������������, �������Ӽ���++*/
    if(task > (hotplug_para->hotplug_up_level[cpu_online_num-1]).avr_task)
    {
        (*task_cnt_add)++;
        *task_cnt_sub = 0;
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"pwrctrl_set_load_task_cnt,task++!!!\n",0,0,0,0,0,0);

    }/*���������С�ڵ�ǰ�������½����ޣ�������ټ���++*/
    else if(task < (hotplug_para->hotplug_down_level[cpu_online_num-1]).avr_task)
    {
        (*task_cnt_sub)++;
        *task_cnt_add = 0;
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"pwrctrl_set_load_task_cnt,task--!!!\n",0,0,0,0,0,0);
    }
    else
    {
        PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"cpu num:%d task:%d\n", cpu_online_num, task,0,0,0,0);
    }

    return RET_OK;
}


/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_timer_workqueue
 ��������  : auto hotplug �������д�����
 �������  :
 �������  : ��
 �� �� ֵ  : RET_OK/RET_ERR
�޸ļ�¼   ��
************************************************************************/
 u32_t pwrctrl_hotplug_timer_workqueue (void)
{
    s32_t ret;
    u32_t max_load = 0;
    u32_t min_load = 100;
    u32_t avr_task=0;
    u32_t avr_load=0;
    u32_t cpu_freq = 0;
    /*local_t u32_t boot_delay_timer = 0;*/

    u32_t cpu_online_num = num_online_cpus();

#if 0
    if(CPU_HOTPLUG_BOOT_DELAY > boot_delay_timer)
    {
        boot_delay_timer ++;
        queue_delayed_work_on(0,pwrctrl_autohotplug_wq, &pwrctrl_hotplug_wk, usecs_to_jiffies(pwrctrl_hotplug_para.hotlpug_timer));
        return RET_OK;
    }
#endif

    /*��SC�ж�autohotplug�����Ƿ�򿪣�û�д򿪲��� */
    if((RET_OK == pwrctrl_is_func_on(PWC_SWITCH_AUTOHOTPLUG))&&(PWRCTRL_INIT_FLAG == g_pwc_init_flag))
    {
        avr_load = pwrctrl_getcpu_load(&max_load,&min_load);
        avr_task = pwrctrl_getcpu_avrtask();

        ret = pwrctrl_set_load_task_cnt(avr_load, avr_task, cpu_online_num, &pwrctrl_hotplug_para,\
            &cnt_load_add, &cnt_thread_add, &cnt_load_sub, &cnt_thread_sub);

        if(ret != RET_OK)
        {
            PWC_TRACE(PWC_LOG_ERROR, "set load task cnt failed!!!\n",0,0,0,0,0,0);
            /*queue_delayed_work_on(0,pwrctrl_autohotplug_wq, &pwrctrl_hotplug_wk, usecs_to_jiffies(pwrctrl_hotplug_para.hotlpug_timer));*/
    		schedule_delayed_work_on(0, &pwrctrl_hotplug_wk, usecs_to_jiffies(pwrctrl_hotplug_para.hotlpug_timer));

            return RET_ERR;
        }

        /*��ȡ��ǰcpuƵ��*/
        cpu_freq = cpufreq_get(0);

        /*�Ӻ˷�֧*/
        if(((cpu_freq > CPU_FREQ_ADD_THLD) && (cnt_thread_add > pwrctrl_hotplug_para.hotplug_up_level[cpu_online_num-1].cnt_task)) || \
            ((cnt_load_add > pwrctrl_hotplug_para.hotplug_up_level[cpu_online_num-1].cnt_load) && (cnt_thread_add > pwrctrl_hotplug_para.hotplug_up_level[cpu_online_num-1].cnt_task)))
        {
            if(RET_OK == pwrctrl_cpu_up_verify())
            {
                PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"###pwrctrl_hotplug add core,cpu_online_num=%d.\n",cpu_online_num);
                AUTO_UP_RECORD;
                CPU_UP_RECORD(cpu_online_num);
                cpu_up(cpu_online_num);
				if(ret == 0)
				{
					update_idletime(cpu_online_num);		 
				}
            }
            else
            {
                PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"pwrctrl_cpu_up_verify failed\n");
            }
            cnt_load_add = cnt_thread_add = 0;
            cnt_load_sub = cnt_thread_sub = 0;
        } /*���˷�֧*/
        else if((cnt_thread_sub > pwrctrl_hotplug_para.hotplug_down_level[cpu_online_num-1].cnt_task)&&(cnt_load_sub > pwrctrl_hotplug_para.hotplug_down_level[cpu_online_num-1].cnt_load))
        {
            if(RET_OK == pwrctrl_cpu_down_verify())
            {
                PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"###pwrctrl_hotplug del core,cpu_online_num=%d.\n",cpu_online_num);
                AUTO_UP_RECORD;
                CPU_DOWN_RECORD(cpu_online_num-1);
                cpu_down(cpu_online_num-1);				
            }
            else
            {
                PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"pwrctrl_cpu_down_verify failed\n");
            }
        	cnt_load_add = cnt_thread_add = 0;
            cnt_load_sub = cnt_thread_sub = 0;
        }
        else
        {
            PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"cpu_load:%d task:%d freq:%d cpu_num:%d cnt_load_add:%d "\
                "cnt_load_sub:%d cnt_thread_add:%d cnt_thread_sub:%d\n", avr_load, avr_task,\
                cpu_freq, cpu_online_num, cnt_load_add, cnt_load_sub, cnt_thread_add, cnt_thread_sub);
        }
    }
    /*queue_delayed_work_on(0,pwrctrl_autohotplug_wq, &pwrctrl_hotplug_wk, usecs_to_jiffies(pwrctrl_hotplug_para.hotlpug_timer));*/
	schedule_delayed_work_on(0, &pwrctrl_hotplug_wk, usecs_to_jiffies(pwrctrl_hotplug_para.hotlpug_timer));

    return RET_OK;
}





/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_timer_init
 ��������  : auto hotplug timer��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : RET_OK/RET_ERR
�޸ļ�¼   ��
************************************************************************/
 s32_t pwrctrl_hotplug_timer_init (void)
{
    if(RET_OK != pwrctrl_is_func_on(PWC_SWITCH_AUTOHOTPLUG))
    {
        return RET_ERR;
    }
	INIT_DELAYED_WORK_DEFERRABLE(&pwrctrl_hotplug_wk, pwrctrl_hotplug_timer_workqueue);

    /*����ģʽ������*/
	/*if (RUNMODE_FLAG_NORMAL == runmode_is_factory())*/
	schedule_delayed_work_on(0, &pwrctrl_hotplug_wk, usecs_to_jiffies(CPU_HOTPLUG_BOOT_DELAY));


#if 0
    if(NULL == pwrctrl_autohotplug_wq )
    {
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_timer_init\n",0,0,0,0,0,0);

        pwrctrl_autohotplug_wq = create_workqueue("pwrctrl_autohotplug");
        INIT_DELAYED_WORK_DEFERRABLE(&pwrctrl_hotplug_wk, pwrctrl_hotplug_timer_workqueue);
        queue_delayed_work_on(0,pwrctrl_autohotplug_wq, &pwrctrl_hotplug_wk, usecs_to_jiffies(pwrctrl_hotplug_para.hotlpug_timer));
        return RET_OK;
    }
    else
    {

        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_timer has been working\n",0,0,0,0,0,0);
             return RET_ERR;
    }
#endif
}


/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_timer_exit
 ��������  : autohotplug timer�˳�����
 �������  : us
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
 s32_t pwrctrl_hotplug_timer_exit ( void )
{
    cancel_delayed_work_sync(&pwrctrl_hotplug_wk);

#if 0
    /*destroy hotplug timer�������� */
    if (pwrctrl_autohotplug_wq )
    {
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_timer_exit\n",0,0,0,0,0,0);
        cancel_delayed_work_sync(&pwrctrl_hotplug_wk);
        destroy_workqueue(pwrctrl_autohotplug_wq);
        pwrctrl_autohotplug_wq = NULL;
        return RET_OK;
    }
    else
    {
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_timer not exist\n",0,0,0,0,0,0);
        return RET_ERR;
    }
#endif
}

void v9hotplug_pm_qos_add(void)
{
	int i = 0;
	int ilength = sizeof(pm_qos_list)/sizeof(struct pm_qos_lst);

	for (i = 0; i < ilength; i++) {
		pm_qos_add_request(pm_qos_list[i].lst, pm_qos_list[i].qos_class,
			pm_qos_list[i].dvalue);
	}
}

void v9hotplug_pm_qos_remove(void)
{
	int i = 0;
	int ilength = sizeof(pm_qos_list)/sizeof(struct pm_qos_lst);

	for (i = 0; i < ilength; i++)
		pm_qos_remove_request(pm_qos_list[i].lst);
}

static int cpufreq_pm_notify(struct notifier_block *nfb, unsigned long action, void *ignored)
{
	pr_info("%s %ld +\n", __func__, action);
	switch (action)
	{
	case PM_SUSPEND_PREPARE:
	case PM_HIBERNATION_PREPARE:
		pwrctrl_hotplug_timer_exit();
		break;
	case PM_POST_SUSPEND:
	case PM_POST_HIBERNATION:
        /*����pwrctrl_hotplug_timer_init����timer��ʱ��*/
        pwrctrl_hotplug_timer_init();
		break;
	default:
		pr_warn("%s %d %ld\n", __func__, __LINE__, action);
		break;
	}

	pr_info("%s -\n", __func__);

	return NOTIFY_OK;
}

static struct notifier_block hotplug_pm_nb = {
	.notifier_call = cpufreq_pm_notify,
};


/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_gov_dbs
 ��������  : hotplug ���Դ�����
 �������  : NA
 �������  : ��
 �� �� ֵ  : OK��ERROR�����Դ���ɹ�/ʧ��
�޸ļ�¼   ��
************************************************************************/
 int pwrctrl_hotplug_gov_dbs(struct cpufreq_policy *policy,
                   unsigned int event)
{
    unsigned int cpu = policy->cpu;

    switch (event)
    {
        case CPUFREQ_GOV_START:
        {
            mutex_lock(&dbs_mutex);
            PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG,"pwrctrl_hotplug_gov_dbs   START\n",0,0,0,0,0,0);
            if (cpu == 0) {
                /*����pwrctrl_hotplug_timer_init����timer��ʱ��*/
                pwrctrl_hotplug_timer_init();
                v9hotplug_pm_qos_add();
    			register_pm_notifier(&hotplug_pm_nb);
            }
            mutex_unlock(&dbs_mutex);
            break;
        }

        case CPUFREQ_GOV_STOP:
        {
            mutex_lock(&dbs_mutex);
            PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_hotplug_gov_dbs   STOP\n",0,0,0,0,0,0);

            /*ֹͣtimer��ʱ��*/
            if (cpu == 0) {
                pwrctrl_hotplug_timer_exit();
                v9hotplug_pm_qos_remove();
    			unregister_pm_notifier(&hotplug_pm_nb);
            }
            mutex_unlock(&dbs_mutex);
            break;

        }
        case CPUFREQ_GOV_LIMITS:
        {
            mutex_lock(&dbs_mutex);
            PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_hotplug_gov_dbs   LIMITS.max:%d min:%d\n",
                policy->max,policy->min,0,0,0,0);

    		if (cpu == 0) {
    			pm_qos_update_request(&g_cpumaxlimits, policy->max);
    			pm_qos_update_request(&g_cpuminlimits, policy->min);
    		}
    		mutex_unlock(&dbs_mutex);
    		break;
        }
        default:
        {
            PRINT_PWC_DBG(PWC_SWITCH_AUTOHOTPLUG, "pwrctrl_hotplug_gov_dbs  don't need handle event:%d \n",event,0,0,0,0,0);
            break;

        }
    }
    return RET_OK;
}

/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_gov_init
 ��������  : hotplug gov���Գ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : OK/ERROR,���Գɹ�����ʧ��
�޸ļ�¼   ��
************************************************************************/
 int pwrctrl_hotplug_gov_init ( void )
{

/*���ú���cpufreq_register_governor����hotplug���Ĺ�����Ե�ע��*/
    int err = 0;
    err = cpufreq_register_governor(&pwrctrl_hotplug_gov);
    if (err)
    {
        PWC_TRACE(PWC_LOG_INFO, "cpufreq_register_governor pwrctrl_hotplug_gov fail \n",0,0,0,0,0,0);
    }
    else
    {
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_gov_init sucess\n",0,0,0,0,0,0);
    }

    return err;
}

/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_gov_exit
 ��������  : hotplug gov���Գ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
 void pwrctrl_hotplug_gov_exit ( void )
{
     PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_gov_exit\n",0,0,0,0,0,0);

    /*���ú���cpufreq_unregister_governor hotplug���Ĺ�����Ե�ע���ȥ��ʼ��*/
         cpufreq_unregister_governor(&pwrctrl_hotplug_gov);
}





/*************************************************************************
 �� �� ��  : pwrctrl_cpunumbermax_handle
 ��������  : cpunumber max ������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
 s32_t pwrctrl_cpunumbermax_handle (u32_t value)
{
    u32_t cpu_online_num = num_online_cpus();
    pwrctrl_hotplug_cpuqos.cpu_number_max=value;

    CPU_LOCK_CHECK;

     PWC_TRACE(PWC_LOG_INFO, "pwrctrl_cpunumbermax_handle  from :%d to:%d\n",cpu_online_num,pwrctrl_hotplug_cpuqos.cpu_number_max,0,0,0,0);

    while(cpu_online_num>pwrctrl_hotplug_cpuqos.cpu_number_max)
    {
        QOS_DOWN_RECORD;
        CPU_DOWN_RECORD(cpu_online_num-1);
        cpu_down(cpu_online_num-1);
        cpu_online_num = num_online_cpus();
    }
    return RET_OK;
}
/*************************************************************************
 �� �� ��  : pwrctrl_cpunumbermin_handle
 ��������  : cpunumber min������
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
 s32_t  pwrctrl_cpunumbermin_handle (u32_t value)
{
    u32_t cpu_online_num = num_online_cpus();

    pwrctrl_hotplug_cpuqos.cpu_number_min=value;

    CPU_LOCK_CHECK;

    PWC_TRACE(PWC_LOG_INFO, "pwrctrl_cpunumbermin_handle  from :%d to:%d\n",cpu_online_num,pwrctrl_hotplug_cpuqos.cpu_number_min,0,0,0,0);

    while(cpu_online_num<pwrctrl_hotplug_cpuqos.cpu_number_min)
    {
        QOS_UP_RECORD;
        CPU_UP_RECORD(cpu_online_num);
        cpu_up(cpu_online_num);
		if(ret == 0)
		{
			update_idletime(cpu_online_num);	 
		}
        cpu_online_num = num_online_cpus();
    }
    return RET_OK;
}

/*************************************************************************
 �� �� ��  : pwrctrl_cpunumberlock_handle
 ��������  : cpunumber lock������
 �������  :��������������CORE��
 �������  : ��
 �� �� ֵ  : RET_OK/RET_ERR
�޸ļ�¼   ��
************************************************************************/

 s32_t pwrctrl_cpunumberlock_handle(u32_t value)
{
    int cpu_online_num =0;
    pwrctrl_hotplug_cpuqos.cpu_number_lock=value;
    /*value ==0 Ϊ�ͷ���������Ϊ������core��*/

    if(pwrctrl_hotplug_cpuqos.cpu_number_lock==0)
    {
        PWC_TRACE(PWC_LOG_INFO, "pwrctrl_cpunumberlock_handle :unlock\n",0,0,0,0,0,0);
        pwrctrl_cpunumbermin_handle (pwrctrl_hotplug_cpuqos.cpu_number_min);
        pwrctrl_cpunumbermax_handle (pwrctrl_hotplug_cpuqos.cpu_number_max);
        /*��ǰ autoplug ��û����ò���*/
        /*pwrctrl_hotplug_timer_init();*/
    }
    else
    {

            PWC_TRACE(PWC_LOG_INFO, "pwrctrl_cpunumberlock_handle :lock:%d\n",pwrctrl_hotplug_cpuqos.cpu_number_lock,0,0,0,0,0);
            /*��ǰ autoplug ��û����ò���*/
            /*pwrctrl_hotplug_timer_exit();*/
            cpu_online_num=num_online_cpus();
        while (pwrctrl_hotplug_cpuqos.cpu_number_lock!= cpu_online_num)
        {

            if (pwrctrl_hotplug_cpuqos.cpu_number_lock < cpu_online_num)
            {
                QOS_DOWN_RECORD;
                CPU_DOWN_RECORD(cpu_online_num-1);
                cpu_down(cpu_online_num-1);
            }
            else
            {
                QOS_UP_RECORD;
                CPU_UP_RECORD(cpu_online_num);
                cpu_up(cpu_online_num);
				if(ret == 0)
				{
					update_idletime(cpu_online_num);
				}
            }

            cpu_online_num = num_online_cpus();
        }
    }
    return RET_OK;

}



/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_para_init
 ��������  : hotplug���ܿ��Ʋ�����ʼ��������ӿڡ�
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
s32_t   pwrctrl_hotplug_parm_set (u32_t offset, u32_t value,  u32_t flag)
{
    PWRCTRL_HOTPLUG_PARA_STRU *ppara=&pwrctrl_hotplug_para;

    if(PWC_HOTPARA_DEFAULT == flag )
    {
        pwrctrl_hotplug_para.hotlpug_timer=CPU_HOTPLUG_TIMER_US;
        memcpy(pwrctrl_hotplug_para.hotplug_up_level,hotplug_up_defaultlevel,(NR_CPUS_NUMBER)*sizeof(PWRCTRL_HOTPLUG_LEVEL_STRU));
        memcpy(pwrctrl_hotplug_para.hotplug_down_level,hotplug_down_defaultlevel,(NR_CPUS_NUMBER)*sizeof(PWRCTRL_HOTPLUG_LEVEL_STRU));
        return RET_OK;
    }

    if(offset>sizeof(PWRCTRL_HOTPLUG_PARA_STRU))
    {
        /*�ڲ����⹦��ֻ����Χ��飬��������������*/
         return RET_ERR;
    }
    else
    {
        PWC_TRACE(PWC_LOG_INFO, "hotplug param modify offset:%d value : %d\n",offset,value,0,0,0,0);
        *((u32_t *)(ppara)+offset)=value;
    }

    PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_hotplug_parm_set sucess\n",0,0,0,0,0,0);

    return RET_OK;
}

 #if 0
BSP_IPC_MASK(  BSP_U32  enSrc)
{
    BSP_U32                                IPCMaskReg = 0;

   /*�����Ӧ�ж�Դ�ж�*/
    BSP_RegWr(BSP_IPC_CPU_INT_CLR_ACPU, (0x1<<enSrc));

    /*��ȡMask�Ĵ������ݣ���ֹ���ݸ�д*/
    IPCMaskReg = BSP_RegRd(BSP_IPC_CPU_INT_MASK_ACPU);

    IPCMaskReg=IPCMaskReg&(~(0x1<<enSrc));
    /*������λ��ʹ�ܸ�Դ�ж�*/
    BSP_RegWr(BSP_IPC_CPU_INT_MASK_ACPU, IPCMaskReg));

}

BSP_IPC_UNMASK(  BSP_U32  enSrc)
{
    BSP_U32                                IPCMaskReg = 0;

   /*�����Ӧ�ж�Դ�ж�*/
    BSP_RegWr(BSP_IPC_CPU_INT_CLR_ACPU, (0x1<<enSrc));

    /*��ȡMask�Ĵ������ݣ���ֹ���ݸ�д*/
    IPCMaskReg = BSP_RegRd(BSP_IPC_CPU_INT_MASK_ACPU);

    /*������λ��ʹ�ܸ�Դ�ж�*/
    BSP_RegWr(BSP_IPC_CPU_INT_MASK_ACPU, ((0x1<<enSrc)|IPCMaskReg));

}
#endif


local_t s32_t  pwrctrl_hotplug_mcu_workqueue(void)
{
    int cpu_online_num = num_online_cpus();

    printk(KERN_INFO"%s enter.\n", __FUNCTION__);

    MCU_UP_RECORD;
    CPU_UP_RECORD(cpu_online_num);

    cpu_up(cpu_online_num);

    BSP_IPC_IntEnable(IPC_MCU_INT_SRC_ACPU_HOTPLUG); /*IPC_MCU_INT_SRC_MCU_HOTPLUG -> IPC_MCU_INT_SRC_ACPU_HOTPLUG*/

    return RET_OK;
}

local_t s32_t pwrctrl_hotplug_mcu_control_isr (void)
{

       /*��SC�ж�mcu control ����cpu�����Ƿ�� */
    if(RET_OK == pwrctrl_cpu_up_verify())
    {
        PWC_TRACE(PWC_LOG_INFO, "mcu  set hotplug add\n",0,0,0,0,0,0);
        /*����IPC�ж�*/
        BSP_IPC_IntDisable(IPC_MCU_INT_SRC_ACPU_HOTPLUG);
        queue_work(pwrctrl_mcuhotplug_wq,&pwrctrl_mcuhotplug_wk);
        return RET_OK;
    }
    else
    {
          PWC_TRACE(PWC_LOG_INFO, "mcu  set hotplug have no effect\n",0,0,0,0,0,0);
          return RET_ERR;
    }
}

local_t s32_t  pwrctrl_hotplug_mcu_control_init (void)
{
    /*ע��IPC�жϴ�����pwrctrl_hotplug_mcu_isr*/
    BSP_IPC_IntConnect(IPC_MCU_INT_SRC_ACPU_HOTPLUG, pwrctrl_hotplug_mcu_control_isr, MAILBOX_TARGET_CPU_MCU);

    /*����hotplug_mcu control��������*/
    pwrctrl_mcuhotplug_wq = create_workqueue("pwrctrl_mcuhotplug");
    INIT_WORK(&pwrctrl_mcuhotplug_wk, (void *)pwrctrl_hotplug_mcu_workqueue);
    return RET_OK;

}

/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_mcu_control_uninit
 ��������  : mcu����hotplugȥ��ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
local_t s32_t pwrctrl_hotplug_mcu_control_uninit (void)
{
    /*����IPC�ж�*/
    /*ȥע��IPC�жϴ�����*/
     BSP_IPC_IntDisable(IPC_MCU_INT_SRC_ACPU_HOTPLUG);
     BSP_IPC_IntConnect(IPC_MCU_INT_SRC_ACPU_HOTPLUG, NULL, MAILBOX_TARGET_CPU_MCU);

    /*ɾ��hotplug_mcu control��������*/
    cancel_work_sync(&pwrctrl_mcuhotplug_wk);
    destroy_workqueue(pwrctrl_mcuhotplug_wq);
    return RET_OK;
}




/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_init
 ��������  : hotplug�͹��ĳ�ʼ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
 int __init pwrctrl_hotplug_init(void)
{
    volatile unsigned int *secondary_phy_addr = 0;

    ppwrctrl_hotplug_exc_log = (PWRCTRL_HOTPLUG_EXC_LOG_STRU *)(EXCH_ACPU_CORE_HOTPLUG_ADDR);

    /*secondary core boot phy addr*/
    secondary_phy_addr = MEMORY_AXI_SEC_CORE_BOOT_ADDR;
    *secondary_phy_addr = virt_to_phys(k3v2_secondary_startup);

    PWC_TRACE(PWC_LOG_ERROR, "MEMORY_AXI_SEC_CORE_BOOT_ADDR=0x%x\n",secondary_phy_addr,0,0,0,0,0);
    PWC_TRACE(PWC_LOG_ERROR, "secondary_boot_phy_addr=0x%x\n",*secondary_phy_addr,0,0,0,0,0);

    /*���ú���pwrctrl_hotplug_para_set����hotplug��صĲ�����ʼ��*/
    pwrctrl_hotplug_parm_set(0,0,PWC_HOTPARA_DEFAULT);

    /*���ú���pwrctrl_hotplug_qosdev_register����QOS�豸ע��*/
    pwrctrl_hotplug_qosdev_register();


    /*���ú���pwrctrl_hotplug_gov_init����hotplug���Ĺ�����Ե�ע��*/
    pwrctrl_hotplug_gov_init();

#if 0
    /*���ú���pwrctrl_hotplug_mcu_control_init ����mcu����hotplug�Ļص�����ע��*/
    pwrctrl_hotplug_mcu_control_init();
#endif

    PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_hotplug_init sucess\n",0,0,0,0,0,0);

    return 0 ;

}


/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_exit
 ��������  : hotplug�͹��ĳ�ʼ��

 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/

 void __exit pwrctrl_hotplug_exit(void)
{
    /*���ú���pwrctrl_hotplug_gov_exit����hotplug���Ĺ�����Ե�ȥע��*/
    pwrctrl_hotplug_gov_exit();
    /*���ú���pwrctrl_hotplug_mcu_control_uninit ����mcu����hotplug�Ļص�����ע��*/
#if 0
    pwrctrl_hotplug_mcu_control_uninit();
#endif
    pwrctrl_hotplug_qosdev_unregister();

    PWC_TRACE(PWC_LOG_ERROR, "pwrctrl_hotplug_exit sucess\n",0,0,0,0,0,0);
}

/*************************************************************************
 �� �� ��  : pwrctrl_hotplug_mntn
 ��������  : hotplug��ά����Ϣdump
 �������  : us
 �������  : ��
 �� �� ֵ  : ��
�޸ļ�¼   ��
************************************************************************/
void pwrctrl_hotplug_mntn (void)
{
    int i=0;
    PWRCTRL_HOTPLUG_CPUINFO_STRU *precord;
    PWRCTRL_HOTPLUG_LEVEL_STRU *photplug_level;

    /* dump Hotplug�͹���ȫ�ֱ�������¼*/

    PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_para:timer:%d\n",pwrctrl_hotplug_para.hotlpug_timer,0,0,0,0,0);

    /*��¼cpu���ء�task��ֵ�趨*/
    photplug_level=pwrctrl_hotplug_para.hotplug_up_level;
    PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_para:cpu up level:\n",0,0,0,0,0,0);
    for(i=0;i<NR_CPUS_NUMBER-1;i++)
    {
        PWC_TRACE(PWC_LOG_INFO, "index:%d,\n",i,photplug_level[i].cnt_load,photplug_level[i].cpu_load,photplug_level[i].avr_task,0,0);
    }

    photplug_level=pwrctrl_hotplug_para.hotplug_down_level;
    PWC_TRACE(PWC_LOG_INFO, "pwrctrl_hotplug_para:cpu down level:\n",0,0,0,0,0,0);
    for(i=0;i<NR_CPUS_NUMBER-1;i++)
    {
        PWC_TRACE(PWC_LOG_INFO, "index:%d,\n",i,photplug_level[i].cnt_load,photplug_level[i].cpu_load,photplug_level[i].avr_task,0,0);
    }

    /*��¼cpu_number_lock��cpu_number_max��cpu_number_min�趨*/
    PWC_TRACE(PWC_LOG_INFO, "qos cpu_number_max:%d\n",pwrctrl_hotplug_cpuqos.cpu_number_max,0,0,0,0,0);
    PWC_TRACE(PWC_LOG_INFO, "qos cpu_number_min:%d\n",pwrctrl_hotplug_cpuqos.cpu_number_min,0,0,0,0,0);
    PWC_TRACE(PWC_LOG_INFO, "qos cpu_number_lock:%d\n",pwrctrl_hotplug_cpuqos.cpu_number_lock,0,0,0,0,0);
    PWC_TRACE(PWC_LOG_INFO, "qos cpu_number online:%d\n",num_online_cpus(),0,0,0,0,0);

    /*��¼����core��������¼core�׶�״̬��*/
    precord=ppwrctrl_hotplug_exc_log->hotplug_cpu_info;
    for(i=0;i<NR_CPUS_NUMBER;i++)
    {


        PWC_TRACE(PWC_LOG_INFO, " cpu  down info:\n",0,0,0,0,0,0);

        PWC_TRACE(PWC_LOG_INFO, " cpu index:%d, down_count: %d,down_time:%d,down_power:%d,note_mcu:%d\n",
            i,precord[i].cpu_down_count,precord[i].cpu_down_time,
            precord[i].down_power_time,precord[i].down_notemcu_time, 0);
        PWC_TRACE(PWC_LOG_INFO, " cpu  up info:\n",0,0,0,0,0,0);

        PWC_TRACE(PWC_LOG_INFO, " cpu index:%d, up_count: %d,up_time:%d,up_power:%d,up_asm_exit:%d,note_mcu:%d\n",
            i,precord[i].cpu_up_count,precord[i].cpu_up_time,precord[i].up_power_time,
            precord[i].up_asm_exit_time,precord[i].up_notemcu_time);

    }

}


MODULE_AUTHOR("s61250");
MODULE_DESCRIPTION("'pwrctrl_hotplug' - cpu governor for hotplug");
MODULE_LICENSE("GPL");

fs_initcall(pwrctrl_hotplug_init);
module_exit(pwrctrl_hotplug_exit);

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

