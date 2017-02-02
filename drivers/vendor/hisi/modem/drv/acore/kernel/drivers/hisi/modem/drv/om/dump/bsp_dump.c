/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */

/*lint -save -e537*/
#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/thread_info.h>
#include <linux/syslog.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/spinlock.h>
#include <linux/notifier.h>
#include <linux/kdebug.h>
#include <linux/reboot.h>
#include <linux/slab.h>
#include <linux/of.h>
#include <linux/delay.h>
#include <linux/wakelock.h>
#include <asm/string.h>
#include <asm/traps.h>
#include "product_config.h"
#include <linux/syscalls.h>
#ifdef CONFIG_HISI_DUMP
#include <asm/thread_notify.h>
#endif
#include "osl_types.h"
#include "osl_io.h"
#include "osl_bio.h"
#include "osl_malloc.h"
#include "bsp_om_api.h"
#include "bsp_dump.h"
#include "bsp_dump_drv.h"
#include "bsp_om_save.h"
#include "bsp_ipc.h"
#include "bsp_memmap.h"
#include "bsp_wdt.h"
#include "bsp_icc.h"
#include "bsp_onoff.h"
#include "bsp_nvim.h"
#include "bsp_softtimer.h"
#include "bsp_version.h"
#include "bsp_sram.h"
#include "bsp_dump_mem.h"
#include "rdr_adp.h"
#include "bsp_om_version.h"
#include "bsp_coresight.h"
#include "bsp_reset.h"
#include "drv_nv_def.h"
#include "mdrv_om.h"
/*lint -restore*/


/*lint --e{750}*/
#define SRAM_MAX_CPUFREQ_PROFILE_ADDR  (uintptr_t)(&(((SRAM_SMALL_SECTIONS*)(SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MAX_CPUFREQ_PROFILE))/*lint !e750*/
#define SRAM_MIN_CPUFREQ_PROFILE_ADDR  (uintptr_t)(&(((SRAM_SMALL_SECTIONS*)(SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_MIN_CPUFREQ_PROFILE))/*lint !e750*/
#define SRAM_DUMP_POWER_OFF_FLAG_ADDR  (uintptr_t)(&((SRAM_SMALL_SECTIONS*)(SRAM_BASE_ADDR + SRAM_OFFSET_SMALL_SECTIONS))->SRAM_DUMP_POWER_OFF_FLAG)/*lint !e750*/



dump_global_info_t  *g_dump_global_info = BSP_NULL;
dump_base_info_t    *g_dump_base_info = BSP_NULL;
dump_task_info_t    *g_dump_task_info = BSP_NULL;
dump_regs_map_t     *g_dump_reg_map = BSP_NULL;
dump_ctrl_s          g_dump_ctrl;
NV_DUMP_STRU         g_dump_cfg = {{0}};
dump_hook            g_dump_trace_read_cb[DUMP_SYSVIEW_BUTT] = {BSP_NULL};
dump_debug_info_t   g_dump_ptr_info = {0};
dump_hook           g_intlock_in_hook = NULL;
dump_hook           g_intlock_out_hook = NULL;
bool g_exc_flag = false;
/*lint -save -e512*/
spinlock_t g_dump_lock;
struct wake_lock g_dump_wake_lock;
/*lint -restore */
struct softtimer_list g_dump_timer ;
u32 g_dump_save_task_name = false;

rdr_exc_info_s g_rdr_exc_info;
unsigned int g_ulExcType;
unsigned int g_ul_stack_trace_enable = false;
struct pt_regs g_pt_regs;
u32 g_dump_panic_flag = false;

/* RDR�쳣���Ͷ��� */
struct rdr_exception_info_s g_exc_info[] = {
    {
        .e_modid            = RDR_MODEM_AP_MOD_ID,
        .e_modid_end        = RDR_MODEM_AP_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMAP,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem ap reset system",
    },
    {
        .e_modid            = RDR_MODEM_CP_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP| RDR_HIFI | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem self-reset ipc",
    },
    {
        .e_modid            = RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = 0,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_NORMALRESET,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reboot without log",
    },
    {
        .e_modid            = RDR_MODEM_CP_RESET_FAIL_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_RESET_FAIL_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_RESETFAIL,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem self-reset fail",
    },
    {
        .e_modid            = RDR_MODEM_CP_WDT_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_WDT_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_CP,
        .e_reentrant        = RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_EXCEPTION,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem self-reset wdt",
    },
    {
        .e_modid            = RDR_MODEM_CP_RESET_RILD_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_RESET_RILD_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_RILD_EXCEPTION,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reset by rild",
    },
    {
        .e_modid            = RDR_MODEM_CP_RESET_3RD_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_RESET_3RD_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_CP | RDR_HIFI | RDR_LPM3,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_3RD_EXCEPTION,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reset by 3rd modem",
    },
    {
        .e_modid            = RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_NORMALRESET,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem reset stub",
    },
    {
        .e_modid            = RDR_MODEM_NOC_MOD_ID,
        .e_modid_end        = RDR_MODEM_NOC_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP| RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMNOC,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem noc error",
    },
    {
        .e_modid            = RDR_MODEM_CP_RESET_USER_RESET_MOD_ID,
        .e_modid_end        = RDR_MODEM_CP_RESET_USER_RESET_MOD_ID,
        .e_process_priority = RDR_WARN,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = 0,
        .e_reset_core_mask  = RDR_CP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_ALLOW,
        .e_exce_type        = CP_S_NORMALRESET,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem user reset without log",
    },
    {
        .e_modid            = RDR_MODEM_DMSS_MOD_ID,
        .e_modid_end        = RDR_MODEM_DMSS_MOD_ID,
        .e_process_priority = RDR_ERR,
        .e_reboot_priority  = RDR_REBOOT_WAIT,
        .e_notify_core_mask = RDR_AP | RDR_CP | RDR_LPM3 ,
        .e_reset_core_mask  = RDR_AP,
        .e_from_core        = RDR_AP,
        .e_reentrant        = RDR_REENTRANT_DISALLOW,
        .e_exce_type        = CP_S_MODEMDMSS,
        .e_upload_flag      = RDR_UPLOAD_YES,
        .e_from_module      = "CP",
        .e_desc             = "modem dmss error",
    },


};
/*�洢cp�ж���Ϣ �жϺ� �������*/
interupt_table_t *g_cp_interupt_table = NULL;
/*�洢cp���� ���������Ϣ*/
task_table_t *g_cp_task_table = NULL;
/*�洢modid��Χ ���������Ϣ*/
modid_info_t *g_p_modid_table = NULL;



int dump_die_callback(struct notifier_block *nb, unsigned long action, void *data);
int dump_panic_callback(struct notifier_block *nb, unsigned long action, void *data);
int dump_task_switch_callback(struct notifier_block *nb, unsigned long action, void *data);
extern int register_die_notifier(struct notifier_block *nb);
void dump_register_notifier(void);
#ifdef CONFIG_HISI_DUMP
extern int dump_print_all(char * buf, int size, bool clear);
#endif
#ifdef CONFIG_ARM_UNWIND
extern void unwind_backtrace(struct pt_regs *regs, struct task_struct *tsk);
#endif
/*lint -save -e762*/
extern void show_mem(unsigned int filter);
extern void dump_wdt_hook(s32 core);
extern u32 dump_coresight_memmap(void);
extern u32 dump_cs_etb(s32 core);

extern u32 g_wdt_int_no;


/*lint -restore*/
s32 dump_init_phase2(void);
s32 dump_global_info_clear(void);

#define PID_PPID_GET(taskTCB)  ((((struct task_struct *)taskTCB)->pid & 0xffff)| \
                                 ((((struct task_struct *)taskTCB)->real_parent->pid & 0xffff)<< 16))

#define DUMP_T_TASK_ERROR(mod_id)      (mod_id & (1<<24))
#define DUMP_LINUX_TASK_NUM_MAX         128
#define DUMP_REG_SET_MAX                4096

void QueueInit(dump_queue_t *Q, u32 elementNum)
{
    Q->maxNum = elementNum;
    Q->front = 0;
    Q->rear = 0;
    Q->num = 0;
    memset((void *)Q->data, 0, (size_t )(elementNum*sizeof(u32)));
}

__inline__ s32 QueueIn(dump_queue_t *Q, u32 element)
{
    if (Q->num == Q->maxNum)
    {
        return -1;
    }

    Q->data[Q->rear] = element;
    Q->rear = (Q->rear+1) % Q->maxNum;
    Q->num++;

    return 0;
}

s32 QueueOut(dump_queue_t *Q, u32 *element)
{
    if (0 == Q->num)
    {
        return -1;
    }

    *element = Q->data[Q->front];
    Q->front = (Q->front+1) % Q->maxNum;
    Q->num--;

    return 0;
}

int QueueFrontDel(dump_queue_t *Q, u32 del_num)
{
    if (del_num > Q->num)
    {
        return -1;
    }
    Q->front = (Q->front+del_num) % Q->maxNum;
    Q->num   = Q->num - del_num;

    return 0;
}


s32 QueueReadLast(dump_queue_t *Q, u32 *element)
{
    if (0 == Q->num)
    {
        return -1;
    }

    *element = Q->data[((Q->rear+Q->maxNum)-1) % Q->maxNum];

    return 0;
}


__inline__ s32 QueueLoopIn(dump_queue_t *Q, u32 element)
{
    if (Q->num < Q->maxNum)
    {
        return QueueIn(Q, element);
    }
    else
    {
        Q->data[Q->rear] = element;
        Q->rear = (Q->rear+1) % Q->maxNum;
        Q->front = (Q->front+1) % Q->maxNum;
    }

    return 0;
}

u32 QueueNumGet(dump_queue_t *Q)
{
    return Q->num;
}
__inline__ void dump_interrrupt_enter(void)
{
    g_dump_global_info->internal_info.app_internal.inInterrupt++;
}

__inline__ void dump_interrrupt_exit(void)
{
    g_dump_global_info->internal_info.app_internal.inInterrupt--;
}

__inline__ int dump_in_interrrupt(void)
{
    return (int)g_dump_global_info->internal_info.app_internal.inInterrupt;
}

/*lint -save -e123 -e530 -e701 -e713 -e718 -e732 -e737 -e746*/
void dump_task_switch_hook(void *old_tcb, void *new_tcb)
{
#ifdef CONFIG_HISI_DUMP
    /* ��Ҫ�л�������ID��ʱ�����*/
    u32 pid_ppid = 0;
    unsigned long addr = DUMP_TASK_SWITCH_ADDR;
    unsigned long lock_flag;

    if(BSP_FALSE == g_dump_global_info->internal_info.app_internal.taskSwitchStart)
    {
        return;
    }

    pid_ppid = PID_PPID_GET(new_tcb);
    spin_lock_irqsave(&g_dump_lock, lock_flag);
    QueueLoopIn((dump_queue_t *)addr, (u32)pid_ppid);
    QueueLoopIn((dump_queue_t *)addr, om_timer_get());

    g_dump_ptr_info.task_swt_ptr = DUMP_TASK_SWITCH_ADDR +0x10
                                                            + (((dump_queue_t *)addr)->rear )*4;

    spin_unlock_irqrestore(&g_dump_lock, lock_flag);

    if(BSP_NULL != g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH])
    {
        if( (QueueNumGet((dump_queue_t *)addr)*sizeof(u32)) >= DUMP_TASK_SWT_THRESHOLD_SIZE)
        {
            g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH]();
        }
    }

    g_dump_base_info->current_task = (uintptr_t)new_tcb;

    /* ��ʱ����ʱ�����ڼ�¼�������������л�������¼ */
    if(g_dump_save_task_name == true)
    {
        return;
    }

    /* ��ʼ��¼ */
    g_dump_save_task_name = true;

    /* ��Ϊkthreadd�������������񣬵�һ������ʱ������������kthreadd����������ڶ��ν���ʱ���ż�¼ */
    /* dump_magic�ֶΣ�Ƕ��ʽ�޸��ں� */
    if(((struct task_struct*)new_tcb)->dump_magic == (int)new_tcb)
    {
        g_dump_save_task_name = false;
        return;
    }
    else if(((struct task_struct*)new_tcb)->dump_magic == (int)new_tcb + 1)
    {
        u32 task_name_addr = DUMP_ALLTASK_ADDR;

        QueueLoopIn((dump_queue_t *)task_name_addr, pid_ppid);
        QueueLoopIn((dump_queue_t *)task_name_addr, *((u32 *)(((struct task_struct *)(new_tcb))->comm)));
        QueueLoopIn((dump_queue_t *)task_name_addr, *((u32 *)((((struct task_struct *)new_tcb)->comm)+4)));
        QueueLoopIn((dump_queue_t *)task_name_addr, *((u32 *)((((struct task_struct *)new_tcb)->comm)+8)));
        ((struct task_struct*)new_tcb)->dump_magic = (int)new_tcb;
    }
    else
    {
        ((struct task_struct*)new_tcb)->dump_magic = (int)new_tcb + 1;
    }

    g_dump_save_task_name = false;
#endif
}

typedef void (*dump_int_hook)(u32, u32);
dump_int_hook g_int_switch_hook = NULL;
void dump_int_switch_hook_add(dump_int_hook hook_func)
{
    g_int_switch_hook = hook_func;
}

void dump_int_switch_hook_delete(void)
{
    g_int_switch_hook = NULL;
}

void dump_int_switch_hook(u32 dir, u32 newVec)
{
    unsigned long addr = DUMP_TASK_SWITCH_ADDR;
    unsigned long lock_flag;

    if(BSP_FALSE == g_dump_global_info->internal_info.app_internal.taskSwitchStart)
    {
        return;
    }

    spin_lock_irqsave(&g_dump_lock, lock_flag);
    /* ���������ж�ID��ʱ�����*/
    if (0 == dir)/*�жϽ���*/
    {
        QueueLoopIn((dump_queue_t *)addr, (((u32)DUMP_INT_IN_FLAG<<16)|newVec));
        dump_interrrupt_enter();
    }
    else/*�ж��˳�*/
    {
        QueueLoopIn((dump_queue_t *)addr, (((u32)DUMP_INT_EXIT_FLAG<<16)|newVec));
        dump_interrrupt_exit();
    }
    QueueLoopIn((dump_queue_t *)addr, om_timer_get());

    g_dump_ptr_info.task_swt_ptr = DUMP_TASK_SWITCH_ADDR +0x10
                                                            + (((dump_queue_t *)addr)->rear )*4;

    spin_unlock_irqrestore(&g_dump_lock, lock_flag);

    if(BSP_NULL != g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH])
    {
        if( (QueueNumGet((dump_queue_t *)addr)*sizeof(u32)) >= DUMP_TASK_SWT_THRESHOLD_SIZE)
        {
            g_dump_trace_read_cb[DUMP_SYSVIEW_TASKSWITCH]();
        }
    }

    g_dump_base_info->current_int = newVec;

    return;
}

#ifdef CONFIG_HISI_DUMP
void dump_exc_hook(void * currentTaskId, s32 vec, u32* pReg)
{
    if(g_exc_flag)
    {
        return;
    }

    g_dump_base_info->vec = (u32)vec;
    g_pdump_info->p_dump->dump_head.except_reason= DUMP_REASON_ARM;

    /*����ȫ�ָ�λ*/
    system_error(DRV_ERRNO_DUMP_ARM_EXC, DUMP_REASON_ARM, 0, 0, 0);;

    /* ϵͳ����panic��������ǰ���� */
    while((g_dump_panic_flag == true) && !in_interrupt())
    {
        msleep(100);
    }
    return;
}
#endif


void dump_stack_hook(unsigned long where)
{
#ifdef CONFIG_HISI_DUMP
    dump_task_info_t *task = (dump_task_info_t *)g_dump_ctrl.current_task_info;

    if( (DUMP_TASK_INFO_STACK_SIZE - task->offset) > (strlen((void*)where)+12) )
    {
        /* coverity[secure_coding] */
        task->offset += sprintf((char *)task->dump_stack+task->offset, "[%08lx]%pS\n", (unsigned long)where, (void *)where);
    }
#endif
    return;
}

void dump_save_log(void)
{
#ifdef CONFIG_HISI_DUMP
    /* MBB�����ں��޸�printk.c��PHONE dump�������ӡ���ݣ���RDR���� */
    dump_print_all((char*)(DUMP_PRINT_ADDR), DUMP_PRINT_SIZE, false);
#endif
}

void dump_onoff_callback(void)
{
    /* �쳣֮�󣬲���������������־ */
    if(g_exc_flag)
    {
        return;
    }

    g_dump_global_info->internal_info.app_internal.start_flag = DUMP_START_REBOOT;
    g_dump_global_info->internal_info.comm_internal.start_flag = DUMP_START_REBOOT;
    g_dump_global_info->internal_info.m3_internal.start_flag = DUMP_START_REBOOT;
    /* �����������ø�λ��־ */
    g_pdump_info->p_dump->dump_head.except_reason = DUMP_REASON_REBOOT;
    g_pdump_info->p_dump->dump_head.except_core= DUMP_CPU_APP;
    dump_save_log();
}

void dump_register_hook(void)
{
#ifdef CONFIG_HISI_DUMP
    /* �����ϵͳע�ṳ�Ӻ��� */
    if(1 == g_dump_cfg.dump_cfg.Bits.intSwitch)
    {
        dump_int_switch_hook_add((dump_int_hook)dump_int_switch_hook);
    }
#endif
    /*ע��c�˿��Ź��ж�*/
    bsp_ccore_wdt_register_hook();

    /*���Ź��ж�*/
    if(BSP_OK != bsp_wdt_register_hook(dump_wdt_hook))
    {
        dump_error("dump_register_hook[%d]: reg wdt hook failed!\n", __LINE__);
    }

    /* ע�Ὺ�ػ����� */
    bsp_reboot_callback_register(dump_onoff_callback);

    g_dump_global_info->internal_info.app_internal.taskSwitchStart = BSP_TRUE;
    g_dump_global_info->internal_info.app_internal.IntSwitchStart = BSP_TRUE;

    return;
}

bool dump_need_save(u8 * dump_addr)
{
    dump_head_t        *dump_head = (dump_head_t*)(dump_addr+(DUMP_HEAD_ADDR-DUMP_ADDR));
    dump_global_info_t *dump_global_info = (dump_global_info_t*)(dump_addr+(DUMP_GLOBAL_INFO_ADDR-DUMP_ADDR));

    /* ���PMU�쳣����fastboot�����øñ�־��PHONE��dump������PMU�쳣 */
    if(DUMP_REASON_PMU == dump_head->except_reason)
    {
        return BSP_TRUE;
    }

    /* �ȼ��ACORE */
    if((DUMP_START_EXCH == dump_global_info->internal_info.app_internal.start_flag)
        ||(DUMP_START_EXCH == dump_global_info->internal_info.comm_internal.start_flag)
        ||(DUMP_CPU_LPM3 == dump_head->except_core))
    {
        // �쳣����
        if(DUMP_SAVE_FILE_NEED == dump_global_info->internal_info.app_internal.save_file_flag)
        {
            return BSP_TRUE;
        }
        else
        {
            return BSP_FALSE;
        }
    }
    else if((DUMP_START_REBOOT == dump_global_info->internal_info.app_internal.start_flag)
        || (DUMP_START_REBOOT == dump_global_info->internal_info.comm_internal.start_flag))
    {
        return BSP_FALSE;
    }
    else if((DUMP_START_CRASH == dump_global_info->internal_info.app_internal.start_flag)
        || (DUMP_START_CRASH == dump_global_info->internal_info.comm_internal.start_flag))
    {
        dump_head->except_reason = DUMP_REASON_UNDEF;
        return BSP_TRUE;
    }
    else
    {
        return BSP_FALSE;
    }
}

__inline__ void dump_save_global_info(void)
{
    //������ϲ㸴λ����־��λ״̬
    if(DUMP_REASON_UNDEF == g_pdump_info->p_dump->dump_head.except_reason)
    {
        g_pdump_info->p_dump->dump_head.except_reason = DUMP_REASON_NORMAL;
    }

    if(DUMP_REASON_WDT != g_pdump_info->p_dump->dump_head.except_reason)
    {
        g_pdump_info->p_dump->dump_head.except_core= DUMP_CPU_APP;
    }

    g_pdump_info->p_dump->dump_head.except_time= om_timer_tick_get();
    g_dump_global_info->internal_info.app_internal.start_flag = DUMP_START_EXCH;
    dump_fetal("dump save global info finish\n");
    return;
}

void dump_save_base_info(void)
{
    if(BSP_MODU_OTHER_CORE == g_dump_base_info->modId)
    {
        g_dump_base_info->reboot_task = (u32)(-1);
        g_dump_base_info->reboot_int = (u32)(-1);
    }
    else
    {
        /* ��ǰ�����ж� */
        if(in_interrupt())
        {
            g_dump_base_info->reboot_task = (u32)(-1);
            memset(g_dump_base_info->taskName, 0, sizeof(g_dump_base_info->taskName));
            if(DUMP_MBB == dump_get_product_type())
            {
                g_dump_base_info->reboot_int = g_dump_base_info->current_int;
            }
            else
            {
                /* PHONE�ϣ���RDR�����¼�����ж��л���¼ */
                g_dump_base_info->reboot_int = 0xAAAABBBB;
            }
        }
        /* ��ǰ�������� */
        else
        {
            if(g_dump_base_info->modId == 0x11000025 || g_dump_base_info->modId == 0x1100002A)
            {
                /* A��VOSֻ��¼�������pid��û�������task_structָ�룬����¼������ */
                g_dump_base_info->reboot_task = g_dump_base_info->arg1;
            }
            else
            {
                g_dump_base_info->reboot_task = g_dump_base_info->current_task;
                if(NULL != (void*)g_dump_base_info->reboot_task)
                {
                    memcpy(g_dump_base_info->taskName, ((struct task_struct *)(g_dump_base_info->reboot_task))->comm, 16);
                }
            }

            g_dump_base_info->reboot_int = (u32)(-1);
        }
    }

    /*��¼��ǰ״̬������̬�����ж�̬*/
    if (in_interrupt())
    {
        g_dump_base_info->reboot_context = DUMP_CTX_INT;
    }
    else
    {
        g_dump_base_info->reboot_context = DUMP_CTX_TASK;
    }
    dump_fetal("save base info finish\n");
    return;
}

void dump_show_stack(void)
{
    /* ��������쳣��������ӡ�������ջ */
    if (!(DUMP_REASON_ARM == g_dump_base_info->arg1))
    {
        dump_error("###########show mem and current task stack start##############!\n");
        show_mem(0);
         if(DUMP_T_TASK_ERROR(g_dump_base_info->modId))
        {
            show_stack(find_task_by_vpid(g_dump_base_info->arg1),NULL);
        }
        else
        {
            show_stack((struct task_struct *)g_dump_base_info->current_task, NULL);
        }
        dump_error("###########show mem and current task stack end################!\n");
    }
}

__inline__ void dump_save_arm_regs(u32 addr)
{
#ifdef CONFIG_HISI_DUMP
    asm volatile(
        "str r0, [r0,#0x00]\n"
        "str r1, [r0,#0x04]\n"
        "str r2, [r0,#0x08]\n"
        "str r3, [r0,#0x0C]\n"
        "str r4, [r0,#0x10]\n"
        "str r5, [r0,#0x14]\n"
        "str r6, [r0,#0x18]\n"
        "str r7, [r0,#0x1C]\n"
        "str r8, [r0,#0x20]\n"
        "str r9, [r0,#0x24]\n"
        "str r10, [r0,#0x28]\n"
        "str r11, [r0,#0x2C]\n"
        "str r12, [r0,#0x30]\n"
        "str r13, [r0,#0x34]\n"
        "str r14, [r0,#0x38]\n"
        "push {r1}\n"
        "mov r1, pc\n"
        "str r1, [r0,#0x3C]\n"
        "mrs r1, cpsr\n"
        "str r1, [r0,#0x40]\n"
        "pop {r1}\n"
    );
#endif
}

void dump_save_exc_task(u32 addr)
{
    //struct task_struct *task = (struct task_struct *)g_dump_base_info->current_task;
    struct task_struct *task = get_current();

    dump_save_arm_regs(addr);

    g_dump_base_info->current_task = (uintptr_t)task;

    /* Ŀǰֻ����stack, ����ȫ��8K���� */
    memcpy((void * )DUMP_TASK_STACK_ADDR , (const void * )task->stack, (size_t )THREAD_SIZE);/* [false alarm]:����Fortify���� */

    return;
}

void dump_save_all_task(void)
{
#ifdef CONFIG_HISI_DUMP
    struct task_struct *pTid;
    struct thread_info *pThread;
    dump_task_info_t *task_info;
    int ulTaskNum = 0x00;

    for_each_process(pTid)
    {
        if(ulTaskNum >=  DUMP_LINUX_TASK_NUM_MAX)
        {
            return;
        }

        pThread = (struct thread_info*)pTid->stack;
        // ���ȱ���������Ϣ
        task_info = &g_dump_task_info[ulTaskNum];
        task_info->pid = PID_PPID_GET(pTid);
        task_info->entry = (u32)BSP_NULL;                        // linux�ݲ�֧��
        task_info->status = pTid->state;
        task_info->policy = pTid->policy;
        task_info->priority = pTid->prio;
        task_info->stack_base = (uintptr_t)((uintptr_t)pTid->stack + THREAD_SIZE);
        task_info->stack_end = (uintptr_t)end_of_stack(pTid);
        task_info->stack_high = 0;                          // linux�ݲ�֧��
        /* coverity[buffer_size_warning] */
        strncpy((char *)task_info->name, pTid->comm, 16);
        task_info->regs[0] = 0;                             // ǰ�ĸ�ͨ�üĴ���������
        task_info->regs[1] = 0;
        task_info->regs[2] = 0;
        task_info->regs[3] = 0;
        memcpy(&task_info->regs[4], &pThread->cpu_context, 12*sizeof(u32));
        task_info->offset = 0;
        g_dump_ctrl.current_task_info = (uintptr_t)task_info;

#ifdef CONFIG_HISI_DUMP
        g_ul_stack_trace_enable = true;
#ifdef CONFIG_ARM_UNWIND
        unwind_backtrace(NULL, pTid);
#endif
        g_ul_stack_trace_enable = false;
#endif
        ulTaskNum++;
    }
#endif
    dump_fetal("dump save all task finish\n");
    return;
}

void dump_memcpy(u32 * dst, const u32 * src, u32 len)
{
    while(len-- > 0)
    {
        *dst++ = *src++;
    }
}

void dump_save_regs(void)
{
    int size;

    if(g_dump_cfg.dump_cfg.Bits.appRegSave1)
    {
        size = (g_dump_cfg.appRegSize1 < DUMP_REG_SET_MAX) ? g_dump_cfg.appRegSize1 : DUMP_REG_SET_MAX;
        dump_memcpy((u32 *)(DUMP_REGS_ADDR + sizeof(dump_regs_map_t)), (u32 *)((unsigned long)g_dump_cfg.appRegAddr1), size/4);
        g_dump_reg_map->reg_addr1 = g_dump_cfg.appRegAddr1;
        g_dump_reg_map->reg_size1 = size;
    }
    if(g_dump_cfg.dump_cfg.Bits.appRegSave2)
    {
        size = (g_dump_cfg.appRegSize2 < DUMP_REG_SET_MAX) ? g_dump_cfg.appRegSize2 : DUMP_REG_SET_MAX;
        dump_memcpy((u32 *)(DUMP_REGS_ADDR+ DUMP_REG_SET_MAX + sizeof(dump_regs_map_t)), (u32 *)((unsigned long)g_dump_cfg.appRegAddr2), size/4);
        g_dump_reg_map->reg_addr2 = g_dump_cfg.appRegAddr2;
        g_dump_reg_map->reg_size2 = size;
    }
    if(g_dump_cfg.dump_cfg.Bits.appRegSave3)
    {
        size = (g_dump_cfg.appRegSize3 < (DUMP_REG_SET_MAX-sizeof(dump_regs_map_t)))
            ? g_dump_cfg.appRegSize3
            : (DUMP_REG_SET_MAX-sizeof(dump_regs_map_t));
        dump_memcpy((u32 *)(DUMP_REGS_ADDR+ DUMP_REG_SET_MAX*2 + sizeof(dump_regs_map_t)), (u32 *)((unsigned long)g_dump_cfg.appRegAddr3), size/4);
        g_dump_reg_map->reg_addr3 = g_dump_cfg.appRegAddr3;
        g_dump_reg_map->reg_size3 = size;
    }
    dump_fetal("dump save reg finish\n");

    return;
}


void dump_save_usr_data(char *data, u32 length)
{
    s32 len;

    dump_field_map_t* pfield;

    /*�����û���Ϣ*/
    if ((NULL != data) && (length))
    {
        pfield = (dump_field_map_t*)bsp_dump_get_field_map(DUMP_AP_USER_DATA);
        len = (length > DUMP_USER_DATA_SIZE) ? DUMP_USER_DATA_SIZE : length;
        memcpy((void *)DUMP_USER_DATA_ADDR, (const void * )data, (size_t)len); /* [false alarm]:����Fortify���� */
        if(pfield)
        {
            pfield->length = len;
        }
    }
    dump_fetal("dump save usr data finish\n");
    return;
}


#define dump_save_app_done()\
    do{\
        g_dump_global_info->internal_info.app_internal.save_flag = DUMP_SAVE_SUCCESS;\
    }while(0)

#define dump_save_ext_done()\
    do{\
        g_dump_global_info->internal_info.app_internal.ext_save_flag = DUMP_SAVE_SUCCESS;\
    }while(0)

#define dump_save_done()\
    do{\
        g_dump_global_info->internal_info.app_internal.save_file_flag = DUMP_SAVE_FILE_END;\
    }while(0)


void dump_save_ext(void)
{
    struct list_head* cur = NULL;
    dump_field_hook_t* pfieldhook = NULL;
    unsigned long flags;
    dump_area_head_t*  p_head  = (dump_area_head_t*)g_pdump_info->p_cur_area;
    dump_field_map_t*  p_field = (dump_field_map_t*)g_pdump_info->p_cur_area->fields;
    u32 i;
    unsigned long * f_addr;

    list_for_each(cur, &g_pdump_info->cur_hook_list.hook_list)
    {
        spin_lock_irqsave(&g_pdump_info->lock, flags);
        pfieldhook = list_entry(cur, dump_field_hook_t, hook_list);
        spin_unlock_irqrestore(&g_pdump_info->lock, flags);

        if(pfieldhook->pfunc)
        {
            pfieldhook->pfunc();
        }
    }

    /* �����Դ���ַע������ */
    for(i=0; i<p_head->field_num; i++, p_field++)
    {
        f_addr = (unsigned long *)((u8 *)p_head + p_field->offset_addr);
        if(DUMP_FIELD_MAGIC_NUM == *f_addr)
        {
            memcpy((u8 *)f_addr, (u8 *)(*(f_addr + 1)), p_field->length);
        }
    }

    dump_save_ext_done();
    dump_fetal("dump save ext finish\n");

    return;
}

/* ����CP��LPM3�Դ���ַ��չ�� */
void dump_save_ext_by_area(DUMP_AREA_ID area_id)
{
    u32 i;
    u32 * f_data;
    u8  * map_addr;
    dump_area_t     *  p_area  = (dump_area_t *)((u8 *)g_pdump_info->p_dump + g_pdump_info->p_dump->area_info[area_id].offset);
    dump_field_map_t*  p_field = (dump_field_map_t*)p_area->fields;

    if((area_id == DUMP_AREA_CP) && (p_area->area_head.magic_num != DUMP_CP_MAGIC_NUM))
    {
        dump_fetal("DUMP AREA CP has not initialized\n");
        return;
    }

    if((area_id == DUMP_AREA_LPM3) && (p_area->area_head.magic_num != DUMP_LPM3_MAGIC_NUM))
    {
        dump_fetal("DUMP AREA LPM3 has not initialized\n");
        return;
    }

    for(i=0; i<p_area->area_head.field_num; i++, p_field++)
    {
        f_data = (u32 *)((u8 *)p_area + p_field->offset_addr);
        if(DUMP_FIELD_MAGIC_NUM == *f_data)
        {
            map_addr = (u8 *)ioremap_wc(*(f_data + 2), p_field->length);
            printk("phy addr: %p, virt addr: %p\n", f_data + 2, map_addr);
            memcpy((u8 *)f_data, map_addr, p_field->length);
            iounmap(map_addr);
        }
    }
    dump_fetal("dump save ext by area finish\n");
}

void save_last_profile(void)
{
    if(DUMP_MBB == dump_get_product_type())
    {
        writel(*(u32*)SRAM_MAX_CPUFREQ_PROFILE_ADDR, (u8 *)((uintptr_t)DUMP_FASTBOOT_ADDR));
        writel(*(u32*)SRAM_MAX_CPUFREQ_PROFILE_ADDR, (u8 *)((uintptr_t)DUMP_FASTBOOT_ADDR) + 4);
        writel(*(u32*)SRAM_MIN_CPUFREQ_PROFILE_ADDR, (u8 *)((uintptr_t)DUMP_FASTBOOT_ADDR) + 8);
        dump_fetal("save last profile finish\n");
    }
}

s32 dump_save(char * log_path, u32 nve_value)
{
    dump_fetal("dump_save[%d]: enter!\n", __LINE__);

    /* coverity[unchecked_value] */
    bsp_om_save_loop_file(log_path, nve_value, dump_get_product_type());

    dump_save_done();

    return BSP_OK;
}

void dump_trace_stop(void)
{
#ifdef CONFIG_HISI_DUMP
    dump_int_switch_hook_delete();
#endif
    g_dump_global_info->internal_info.app_internal.taskSwitchStart = BSP_FALSE;
    g_dump_global_info->internal_info.app_internal.IntSwitchStart = BSP_FALSE;

    return;
}

__inline__ void dump_wait_for_reboot(void)
{
    /* coverity[no_escape] */
    do{
    }while(1);
}


void dump_save_and_reboot(void)
{
    /*�����ļ��ڸ����ȼ����������*/
    g_dump_ctrl.dump_task_job = DUMP_TASK_JOB_SAVE_REBOOT;
    up(&g_dump_ctrl.sem_dump_task);
    dump_fetal("up g_dump_ctrl.sem_dump_task \n");

//    preempt_enable();

    return;
}


void dump_system_error_enter(void)
{
    /* ֹͣ��¼�����л�/�жϵ� */
    dump_trace_stop();

    /* ��ֹ��ռ */
//    preempt_disable();
    dump_fetal("dump trace stop finish\n");
    return;
}

void dump_notify_target(u32 mod_id)
{
    if(DUMP_MBB == dump_get_product_type())
    {
        if(RDR_MODEM_AP_MOD_ID == mod_id)
        {
            /* AP�쳣��֪ͨCP��LPM3 */
            bsp_ipc_int_send(IPC_CORE_CCORE, IPC_CCPU_SRC_ACPU_DUMP);
            /* ����IPC�жϼ���Ҫ����ʱ�����C��˯�ߣ����ܵ���C��IPC�ò������� */
            udelay(1000);
            bsp_ipc_int_send(IPC_CORE_MCORE, IPC_MCU_INT_SRC_DUMP);
        }
        else if(RDR_MODEM_CP_MOD_ID == mod_id)
        {
            /* CP�쳣��֪ͨLPM3 */
            bsp_ipc_int_send(IPC_CORE_MCORE, IPC_MCU_INT_SRC_DUMP);
        }
        else if(RDR_MODEM_LPM3_MOD_ID == mod_id)
        {
            /* LPM3�쳣��֪ͨCP */
            bsp_ipc_int_send(IPC_CORE_CCORE, IPC_CCPU_SRC_ACPU_DUMP);
        }
        else
        {
            dump_fetal("invalid mod id 0x%x\n", mod_id);
        }
    }

    if(DUMP_PHONE == dump_get_product_type())
    {
        if(RDR_MODEM_AP_MOD_ID == mod_id
            || RDR_MODEM_CP_RESET_RILD_MOD_ID == mod_id
            || RDR_MODEM_CP_RESET_3RD_MOD_ID == mod_id
            || RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID == mod_id
            || RDR_MODEM_NOC_MOD_ID == mod_id
            || RDR_MODEM_DMSS_MOD_ID == mod_id)
        {
            /* AP�쳣��֪ͨCP */
            bsp_ipc_int_send(IPC_CORE_CCORE, IPC_CCPU_SRC_ACPU_DUMP);
        }
    }

    dump_fetal("notify other core success \n");
}

void dump_save_task_name(void)
{
    struct task_struct *pTid = NULL;
    int ulTaskNum = 0x00;
    u32 pid_ppid = 0;
    unsigned long task_name_addr = DUMP_ALLTASK_ADDR;
    char idle_task_name[12] = {"swapper"};

    /* �����л����ڼ�¼��ֱ�ӷ��� */
    if(g_dump_save_task_name == true)
    {
        return;
    }

    /* ��ʼ��¼ */
    g_dump_save_task_name = true;

    for_each_process(pTid)
    {
        if(ulTaskNum >=  DUMP_LINUX_TASK_NUM_MAX)
        {
            break;
        }

        pid_ppid = PID_PPID_GET(pTid);

        QueueLoopIn((dump_queue_t *)task_name_addr, pid_ppid);
        QueueLoopIn((dump_queue_t *)task_name_addr, *((int *)(pTid->comm)));
        QueueLoopIn((dump_queue_t *)task_name_addr, *((int *)((pTid->comm)+4)));
        QueueLoopIn((dump_queue_t *)task_name_addr, *((int *)((pTid->comm)+8)));

        ulTaskNum++;
    }

    QueueLoopIn((dump_queue_t *)task_name_addr, 0);
    QueueLoopIn((dump_queue_t *)task_name_addr, *((int *)(idle_task_name)));
    QueueLoopIn((dump_queue_t *)task_name_addr, *((int *)(idle_task_name+4)));
    QueueLoopIn((dump_queue_t *)task_name_addr, *((int *)(idle_task_name+8)));

    /* ��¼��� */
    g_dump_save_task_name = false;

}

void dump_timer_handler(u32 param)
{
    if(param)
    {}
    dump_save_task_name();
    bsp_softtimer_add(&g_dump_timer);
}

s32 dump_start_timer(u32 time_out)
{
    s32 ret = 0;
    g_dump_timer.func = dump_timer_handler;
    g_dump_timer.para = 0;
    g_dump_timer.timeout = time_out;
    g_dump_timer.wake_type = SOFTTIMER_NOWAKE;

    ret =  bsp_softtimer_create(&g_dump_timer);
    if(ret)
    {
        return BSP_ERROR;
    }
    bsp_softtimer_add(&g_dump_timer);

    return BSP_OK;
}

void dump_stop_timer(void)
{
    if(g_dump_timer.init_flags!=TIMER_INIT_FLAG)
    {
        dump_fetal("timer is null\n");
        return;
    }

    (void)bsp_softtimer_delete(&g_dump_timer);
    (void)bsp_softtimer_free(&g_dump_timer);
}

void dump_int_handle(s32 param)
{
    /* �Ѿ������쳣�����ټ�¼ */
    if(g_exc_flag)
    {
        return;
    }
    else
    {
        g_exc_flag = true;

        /*IPC �ж�˵���˵�ǰC���Ѿ��쳣������Ҫ���ϱ����Ź��ж�*/
        if(DUMP_PHONE == dump_get_product_type())
        {
            disable_irq_nosync(g_wdt_int_no);
        }
    }

    if (DUMP_INIT_FLAG != g_dump_global_info->internal_info.app_internal.init_flag)
    {
        /*�ȴ�����*/
        dump_wait_for_reboot();
        return;
    }

    if(DUMP_MBB == dump_get_product_type())
    {
        /* CP�쳣��֪ͨLPM3 */
        if(param == 0)
        {
            bsp_ipc_int_send(IPC_CORE_MCORE, IPC_MCU_INT_SRC_DUMP);
        }
        /* LPM3�쳣��֪ͨCP */
        else if(param == 1)
        {
            bsp_ipc_int_send(IPC_CORE_CCORE, IPC_CCPU_SRC_ACPU_DUMP);
        }
    }

    if(DUMP_MBB == dump_get_product_type())
    {
        /*�����쳣������Ϣ*/
        dump_save_exc_task((uintptr_t)(&(g_dump_base_info->regSet[0])));
    }

    bsp_coresight_disable();

    g_dump_base_info->modId = BSP_MODU_OTHER_CORE;
    g_dump_base_info->arg1 = 0;
    g_dump_base_info->arg2 = 0;
    g_dump_base_info->arg3 = 0;
    g_dump_base_info->arg3_length = 0;
    dump_save_base_info();

    dump_system_error_enter();

    dump_fetal("[0x%x]================ modem ccore enter system error! ================\n", om_timer_get());

    dump_show_stack();

    /* ��ֹ����˯�� */
    if(DUMP_MBB == dump_get_product_type())
    {
        wake_lock(&g_dump_wake_lock);
    }
    /* ��ֹ����˯�� */
    if(DUMP_PHONE == dump_get_product_type())
    {
        om_save_sysctrl();
    }


    /* CP�쳣 */
    if(param == 0)
    {
        rdr_system_error(RDR_MODEM_CP_MOD_ID, 0, 0);
    }
    /* LPM3�쳣 */
    else if(param == 1)
    {
        rdr_system_error(RDR_MODEM_LPM3_MOD_ID, 0, 0);
    }

    return;
}

void dump_parse_dts_config(void)
{
    struct device_node *node = NULL;
    const char * product_type;

    /* ��ȡ��ǰ��Ʒ��̬ */
    node = of_find_compatible_node(NULL, NULL, "hisilicon,smntn_type");
    if (!node)
    {
        dump_fetal("dts node mntn type not found!\n");
        return;
    }

    if(of_property_read_string(node, "product_type", &product_type))
    {
        dump_fetal("read product_type failed!\n");
        return;
    }

    if(0 == strncmp(product_type, "MBB", strlen("MBB")))
    {
        g_rdr_exc_info.product_type = DUMP_MBB;
    }
    else if(0 == strncmp(product_type, "PHONE", strlen("PHONE")))
    {
        g_rdr_exc_info.product_type = DUMP_PHONE;
    }
    else
    {
        g_rdr_exc_info.product_type = DUMP_PRODUCT_BUTT;
    }
}

s32 dump_config_init(void)
{
    s32 ret;

    ret = bsp_nvm_read(NVID_DUMP, (u8*)&g_dump_cfg, sizeof(NV_DUMP_STRU));
    if (BSP_OK != ret)
    {
        /*ʹ��Ĭ��ֵ*/
        g_dump_cfg.dump_cfg.Bits.dump_switch     = 0x1;
        g_dump_cfg.dump_cfg.Bits.ARMexc          = 0x1;
        g_dump_cfg.dump_cfg.Bits.stackFlow       = 0x1;
        g_dump_cfg.dump_cfg.Bits.taskSwitch      = 0x1;
        g_dump_cfg.dump_cfg.Bits.intSwitch       = 0x1;
        g_dump_cfg.dump_cfg.Bits.intLock         = 0x1;
        g_dump_cfg.dump_cfg.Bits.appRegSave1     = 0x0;
        g_dump_cfg.dump_cfg.Bits.appRegSave2     = 0x0;
        g_dump_cfg.dump_cfg.Bits.appRegSave3     = 0x0;
        g_dump_cfg.dump_cfg.Bits.commRegSave1    = 0x0;
        g_dump_cfg.dump_cfg.Bits.commRegSave2    = 0x0;
        g_dump_cfg.dump_cfg.Bits.commRegSave3    = 0x0;
        g_dump_cfg.dump_cfg.Bits.sysErrReboot    = 0x1;
        g_dump_cfg.dump_cfg.Bits.reset_log       = 0x1;
        g_dump_cfg.dump_cfg.Bits.fetal_err       = 0x1;

        dump_error("read NV failed, use the default value!.ret = %d nv id = 0x%x\n", ret, NVID_DUMP);
    }

    return BSP_OK;
}

void dump_map_init(void)
{
    char* str_tmp;
    unsigned long flags = 0;
    unsigned long base_addr  = 0;
    dump_load_info_t * dump_load;
    dump_area_head_t * p_head  = (dump_area_head_t*)g_pdump_info->p_cur_area;
    dump_field_map_t * p_field = (dump_field_map_t*)&g_pdump_info->p_cur_area->fields[0];
    dump_area_head_t * p_share_head  = (dump_area_head_t*)&(((dump_area_t *)DUMP_AREA_SHARE_ADDR)->area_head);
    dump_field_map_t * p_share_filed = (dump_field_map_t *)&(((dump_area_t *)DUMP_AREA_SHARE_ADDR)->fields[0]);

    dump_load = (dump_load_info_t *)DUMP_LOAD_INFO_ADDR;
    dump_load->magic_num    = DUMP_LOAD_MAGIC;
    dump_load->ap_ddr  = 0xC0000000;
    dump_load->ap_share= (uintptr_t)g_mem_ctrl.sddr_virt_addr;
    dump_load->ap_dump = (u32)DUMP_ADDR;
    dump_load->ap_sram = (u32)(uintptr_t)HI_SRAM_MEM_ADDR_VIRT;
    dump_load->ap_dts  = HI_IO_ADDRESS(DDR_ACORE_DTS_ADDR);

    /* ��ʼ��SHARE���� */

    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_share_filed[0], DUMP_SHARE_GLOBAL_INFO,   "GLOBAL_INFO",  DUMP_AREA_SHARE_ADDR, DUMP_GLOBAL_INFO_ADDR, DUMP_GLOBAL_INFO_SIZE);
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_share_filed[1], DUMP_SHARE_LOAD_INFO,     "LOAD_INFO",    DUMP_AREA_SHARE_ADDR, DUMP_LOAD_INFO_ADDR,   DUMP_LOAD_INFO_SIZE);
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_share_filed[2], DUMP_SHARE_FASTBOOT_INFO, "FASTBOOT_INFO",DUMP_AREA_SHARE_ADDR, DUMP_FASTBOOT_ADDR,    DUMP_FASTBOOT_SIZE);
    p_share_head->magic_num = DUMP_SHARE_MAGIC_NUM;
    p_share_head->field_num = 3;
    strncpy((char*)p_share_head->name, DUMP_SHARE_AREA_NAME, 8);

    dump_parse_dts_config();

    /* ��ʼ��AREA HEAD���� */
    if(DUMP_PHONE == dump_get_product_type())
    {
        p_head->magic_num = DUMP_AP_MAGIC_NUM_64;
    }
    else
    {
        p_head->magic_num = DUMP_AP_MAGIC_NUM;
    }
    strncpy((char*)p_head->name, DUMP_AP_AREA_NAME, 8);
    /* coverity[secure_coding] */
    str_tmp = (char*)bsp_version_get_firmware();
    if(str_tmp)
    {
        /* coverity[buffer_size_warning] */
        strncpy((char*)p_head->version, str_tmp, 16); /* [false alarm]:����Fortify���� */
    }

    /* ע��DUMP��̬���� */
    spin_lock_irqsave(&g_pdump_info->lock, flags);
    base_addr = (unsigned long)g_pdump_info->p_cur_area;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_BASE_INFO,       "BASE_INFO",   base_addr,DUMP_BASE_INFO_ADDR,        DUMP_BASE_INFO_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_TASK_SWITCH,     "TASK_SWITCH", base_addr,DUMP_TASK_SWITCH_ADDR,      DUMP_TASK_SWITCH_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_INTLOCK,         "INTLOCK",     base_addr,DUMP_INTLOCK_ADDR,          DUMP_INTLOCK_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_TASK_STACK,      "TASK_STACK",  base_addr,DUMP_TASK_STACK_ADDR,       DUMP_TASK_STACK_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_INT_STACK,       "INT_STACK",   base_addr,DUMP_INT_STACK_ADDR,        DUMP_INT_STACK_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_ALLTASK,         "TASK_NAME",   base_addr,DUMP_ALLTASK_ADDR,          DUMP_ALLTASK_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_ALLTASK_TCB,     "ALLTASK_TCB", base_addr,DUMP_ALLTASK_TCB_ADDR,      DUMP_ALLTASK_TCB_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_PRINT,           "PRINT",       base_addr,DUMP_PRINT_ADDR,            DUMP_PRINT_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_REGS,            "REGS",        base_addr,DUMP_REGS_ADDR,             DUMP_REGS_SIZE)
    g_pdump_info->cur_field_num++;
    /* coverity[overrun-buffer-arg] */
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_CPUVIEW,         "CPUVIEW",     base_addr,DUMP_CPUVIEW_ADDR,          DUMP_CPUVIEW_SIZE)
    g_pdump_info->cur_field_num++;
    MAKE_FIXED_FIELD(&p_field[g_pdump_info->cur_field_num], DUMP_AP_USER_DATA,       "USER_DATA",   base_addr,DUMP_USER_DATA_ADDR,        DUMP_USER_DATA_SIZE)
    g_pdump_info->cur_field_num++;
    p_head->field_num = g_pdump_info->cur_field_num;
    spin_unlock_irqrestore(&g_pdump_info->lock, flags);

    g_dump_base_info = (dump_base_info_t*)DUMP_BASE_INFO_ADDR;
    g_dump_task_info = (dump_task_info_t*)DUMP_ALLTASK_TCB_ADDR;

    g_dump_reg_map   = (dump_regs_map_t*)DUMP_REGS_ADDR;
    g_dump_reg_map->reg_addr1 = 0;
    g_dump_reg_map->reg_size1 = 0;
    g_dump_reg_map->reg_addr2 = 0;
    g_dump_reg_map->reg_size2 = 0;
    g_dump_reg_map->reg_addr3 = 0;
    g_dump_reg_map->reg_size3 = 0;

    return;
}

s32 dump_global_info_init(void)
{
    g_pdump_info->p_dump->dump_head.except_core = 0;
    g_pdump_info->p_dump->dump_head.except_reason = 0xff;
    g_pdump_info->p_dump->dump_head.except_time = 0;

    g_dump_global_info->internal_info.app_internal.start_flag = DUMP_START_CRASH;
    g_dump_global_info->internal_info.app_internal.save_flag = BSP_FALSE;
    g_dump_global_info->internal_info.app_internal.ext_save_flag = BSP_FALSE;
    g_dump_global_info->internal_info.app_internal.inInterrupt = 0;
    g_dump_global_info->internal_info.app_internal.taskSwitchStart = BSP_FALSE;
    g_dump_global_info->internal_info.app_internal.IntSwitchStart = BSP_FALSE;

    return BSP_OK;
}


s32 dump_global_info_clear(void)
{
    g_dump_global_info->internal_info.app_internal.start_flag = DUMP_START_REBOOT;
    g_dump_global_info->internal_info.comm_internal.start_flag = DUMP_START_REBOOT;

    return BSP_OK;
}

s32 dump_base_info_init(void)
{
    int i;

    memset(g_dump_base_info, 0, sizeof(dump_base_info_t));
    g_dump_base_info->vec = DUMP_ARM_VEC_UNKNOW;

    memset(g_dump_reg_map, 0, sizeof(dump_regs_map_t));

    memset((void*)DUMP_ALLTASK_TCB_ADDR, 0, DUMP_ALLTASK_TCB_SIZE);
    for(i=0; i<DUMP_LINUX_TASK_NUM_MAX; i++)
    {
        g_dump_task_info[i].pid = 0xffffffff;
    }

    return BSP_OK;
}

void dump_queue_t_init(void)
{
    /* ��ʼ�������л����� */
    QueueInit((dump_queue_t *)(DUMP_TASK_SWITCH_ADDR), (DUMP_TASK_SWITCH_SIZE - 0x10) / 0x4);
    g_dump_ptr_info.task_swt_ptr = DUMP_TASK_SWITCH_ADDR +0x10;

    /* ��ʼ���ж϶��� */
    QueueInit((dump_queue_t *)(DUMP_INTLOCK_ADDR), (DUMP_INTLOCK_SIZE - 0x10) / 0x4);
    g_dump_ptr_info.int_lock_ptr = DUMP_INTLOCK_ADDR +0x10;

    /* ��ʼ������������ */
    QueueInit((dump_queue_t *)(DUMP_ALLTASK_ADDR), (DUMP_ALLTASK_SIZE - 0x10) / 0x4);

    return;
}
/*lint -restore */


void dump_wait_ext_area_save_done(u32 tick,bool wait)
{
    u32 time_start;

    /*wait cp & M3 save done*/
    time_start = om_timer_tick_get();
    do{
        if(DUMP_PHONE == dump_get_product_type())
        {
            if((DUMP_SAVE_SUCCESS == g_dump_global_info->internal_info.comm_internal.save_flag))
            {
                dump_fetal("g_dump_global_info->internal_info.comm_internal.save_flag statify\n");
                return;
            }
        }
        else
        {
            if((DUMP_SAVE_SUCCESS == g_dump_global_info->internal_info.comm_internal.save_flag)
                &&(DUMP_SAVE_SUCCESS == g_dump_global_info->internal_info.m3_internal.save_flag))
            {
                dump_fetal("g_dump_global_info->internal_info.comm_internal.save_flag && g_dump_global_info->internal_info.m3_internal.save_flagstatify \n");
                return;
            }
        }

        if(tick <= (om_timer_tick_get()-time_start))
        {
            dump_fetal("dump save max time out\n");
            break;
        }

        if(wait)
        {
            msleep(10);
        }
    }while(1);

    dump_save_ext_by_area(DUMP_AREA_CP);
    if(DUMP_MBB == dump_get_product_type())
    {
        dump_save_ext_by_area(DUMP_AREA_LPM3);
    }

    return;
}


/*lint -save -e514 -e527 -e716*/
int dump_save_task(void *data)
{
    u32 time_cur = 0;
#define DUMP_INIT_WAIT_MAX   60    //60s
    /* coverity[no_escape] */
    while(1)
    {
        down(&g_dump_ctrl.sem_dump_task);
        dump_fetal("down g_dump_ctrl.sem_dump_task\n");
        /**************************************** ����ļ�ϵͳ���� ***********************************************/
        do{
            if(bsp_om_fs_check())
            {
                break;
            }

            msleep(1000);
            time_cur++;
        }while(time_cur < DUMP_INIT_WAIT_MAX);

        if(time_cur >= DUMP_INIT_WAIT_MAX)
        {
            dump_fetal("check om fs time out\n");
        }

        /**************************************** ϵͳ�쳣������dump ********************************************/
        if(DUMP_TASK_JOB_SAVE_REBOOT == (g_dump_ctrl.dump_task_job & DUMP_TASK_JOB_SAVE_REBOOT))
        {
            dump_wait_ext_area_save_done(500, true);

            save_last_profile();

            dump_save(g_rdr_exc_info.log_path, g_rdr_exc_info.soc_rst.nve);
            dump_fetal("dump save finished\n");
            /* ֪ͨRDR dump������� */
            if(g_rdr_exc_info.dump_done != BSP_NULL)
            {
                dump_fetal("notify rdr dump handle finished\n");
                g_rdr_exc_info.dump_done(g_rdr_exc_info.modid, g_rdr_exc_info.coreid);
            }
        }

        g_dump_ctrl.dump_task_job = 0;
    }

    return BSP_OK;
}
/*lint -restore*/


__inline__ void dump_init_done(void)
{
    g_dump_global_info->internal_info.app_internal.init_flag = DUMP_INIT_FLAG;
    return;
}

s32 dump_init_phase1(void)
{
    s32 ret;
    g_dump_global_info = (dump_global_info_t*)DUMP_GLOBAL_INFO_ADDR;

    /*��ȡ����*/
    ret = dump_config_init();
    if(BSP_OK != ret)
    {
        /* ��ȡ����ʧ�ܣ��쳣���� */
        dump_error("dump_init_phase1[%d]: dump_config_init failed! ret = %d\n", __LINE__, ret);
    }

    (void)bsp_om_debug_init();

    /* ע���ж� */
    ret = bsp_ipc_int_connect(IPC_ACPU_SRC_CCPU_DUMP, (voidfuncptr)dump_int_handle, 0);
    if(BSP_OK != ret)
    {
        dump_error("dump_init_phase1[%d]: bsp_ipc_int_connect failed! ret = %d\n", __LINE__, ret);
        return BSP_ERR_DUMP_INIT_FAILED;
    }

    ret = bsp_ipc_int_enable(IPC_ACPU_SRC_CCPU_DUMP);
    if(BSP_OK != ret)
    {
        dump_error("dump_init_phase1[%d]: bsp_ipc_int_enable failed! ret = %d\n", __LINE__, ret);
        return BSP_ERR_DUMP_INIT_FAILED;
    }

    /* ע���жϣ�MCU ->ACPU*/
    ret = bsp_ipc_int_connect(IPC_ACPU_INT_MCU_SRC_DUMP, (voidfuncptr)dump_int_handle, 1);
    if(BSP_OK != ret)
    {
        dump_error("dump_init_phase1[%d]: bsp_ipc_int_connect failed! ret = %d\n", __LINE__, ret);
        return BSP_ERR_DUMP_INIT_FAILED;
    }

    ret = bsp_ipc_int_enable(IPC_ACPU_INT_MCU_SRC_DUMP);
    if(BSP_OK != ret)
    {
        dump_error("dump_init_phase1[%d]: bsp_ipc_int_enable failed! ret = %d\n", __LINE__, ret);
        return BSP_ERR_DUMP_INIT_FAILED;
    }

    sema_init(&g_dump_ctrl.sem_dump_task, 0);
    g_dump_ctrl.dump_task_job = 0;
    g_dump_global_info->internal_info.app_internal.init_flag = DUMP_INIT_FLAG_PHASE1;

    return BSP_OK;
}

/* �����ȡproduct_typeʧ�ܣ�Ĭ�Ϸ���DUMP_MBB������MBB���Դ��� */
dump_product_type_t dump_get_product_type(void)
{
    if(DUMP_PHONE == g_rdr_exc_info.product_type)
    {
        return DUMP_PHONE;
    }
    else
    {
        return DUMP_MBB;
    }
}
void dump_error_proc(u32 modid)
{
    if (DUMP_INIT_FLAG != g_dump_global_info->internal_info.app_internal.init_flag)
    {
        return;
    }

    if(g_exc_flag)
    {
        dump_fetal("exception has happened can not deal new exception\n");
        return;
    }
    else
    {
        g_exc_flag = true;
    }
    dump_notify_target(modid);
    if(DUMP_MBB == dump_get_product_type())
    {
        /*�����쳣������Ϣ*/
        dump_save_exc_task((u32)(uintptr_t)(&(g_dump_base_info->regSet[0])));
    }
    else
    {
        g_dump_base_info->current_task = (uintptr_t)get_current();
    }


    bsp_coresight_disable();

    g_dump_base_info->modId = modid;
    g_dump_base_info->arg1 = 0;
    g_dump_base_info->arg2 = 0;
    g_dump_base_info->arg3 = NULL;
    g_dump_base_info->arg3_length = 0;

    dump_system_error_enter();
    dump_save_global_info();
    dump_save_base_info();
    //dump_save_usr_data(data, length);

    dump_show_stack();
    /* ��ֹ����˯�� */
    if(DUMP_MBB == dump_get_product_type())
    {
        wake_lock(&g_dump_wake_lock);
        /* ��������������Ϣ */
        dump_save_all_task();

        /* ֹͣ��ʱ����ˢ�������� */
        dump_stop_timer();
        dump_save_task_name();
        dump_fetal("dump save  task  name finish\n");
    }
    else
    {
        /* ����ϵͳ��������dump field */
        om_save_sysctrl();
    }

    /* ����Ĵ�����Ϣ */
    dump_save_regs();

    /* APP���ݱ������ */
    dump_save_app_done();

}
u32 dump_callback(u32 modid, u32 etype, u64 coreid, char* logpath, pfn_cb_dump_done fndone)
{

    if(modid == RDR_MODEM_NOC_MOD_ID || modid == RDR_MODEM_DMSS_MOD_ID  )
    {
        dump_fetal("[0x%x]================ modem noc or dmss error happened ! ================\n", om_timer_get());
        dump_error_proc(modid);
    }
    else
    {
        dump_fetal("enter dump callback, mod id:0x%x,time 0x%x\n", modid,om_timer_get());
    }

    g_rdr_exc_info.modid  = modid;
    g_rdr_exc_info.coreid = coreid;
    g_rdr_exc_info.dump_done = fndone;

    if((strlen(logpath) + strlen(RDR_DUMP_FILE_CP_PATH)) >= RDR_DUMP_FILE_PATH_LEN - 1)
    {
        dump_fetal("log path is too long %s\n", logpath);
        return BSP_ERROR;
    }
    memcpy(g_rdr_exc_info.log_path, logpath, strlen(logpath));

    memcpy(g_rdr_exc_info.log_path + strlen(logpath) , RDR_DUMP_FILE_CP_PATH, strlen(RDR_DUMP_FILE_CP_PATH));

    dump_fetal("log path is %s\n", g_rdr_exc_info.log_path);

    /* ������չ������ */
    dump_save_ext();

    /* �����쳣�ļ���¼��־ */
    dump_save_and_reboot();

    return BSP_OK;
}

void dump_reset(u32 modid, u32 etype, u64 coreid)
{
    s32 ret = -1;
    dump_fetal("enter dump reset, mod id:0x%x\n", modid);

    dump_save_log();

    /* PHONE�ϣ�AP�쳣ֱ�Ӹ�λ���壬CP�쳣����C�˵�����λ */
    if(DUMP_PHONE == dump_get_product_type())
    {
        /* AP�쳣����rdr��ɸ�λ������reset����ֱ�ӷ��� */
        if ((RDR_MODEM_AP_MOD_ID == modid)
            || (RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID == modid))
        {
            return;
        }
        else if((RDR_MODEM_CP_MOD_ID == modid)
                || (RDR_MODEM_CP_WDT_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_RILD_MOD_ID == modid)
                || (RDR_MODEM_CP_RESET_3RD_MOD_ID == modid
                || (RDR_MODEM_CP_RESET_USER_RESET_MOD_ID== modid)))
        {
            g_dump_global_info->internal_info.comm_internal.start_wait_flag = DUMP_INIT_FLAG_WAIT;
            /* CP�쳣�����𵥶���λ��������λʧ����Ҫ֪ͨrdr��λȫϵͳ */
            ret = bsp_modem_reset();

            /*��nieluhuaȷ�ϵ�����λΪ׮����-1��������-1������������λ*/
            if(ret == -1)
            {
                dump_fetal("bsp_modem_reset is stub,reset ap\n");
                rdr_system_error(RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID, 0, 0);
            }
            
            if (!bsp_reset_is_successful(RDR_MODEM_CP_RESET_TIMEOUT))
            {
                dump_fetal("modem reset fail, notify rdr\n");
                /* ������λʧ�� */
                rdr_system_error(RDR_MODEM_CP_RESET_FAIL_MOD_ID, 0, 0);
            }
            else
            {
                /* CP������λ��ɣ������ٴδ����쳣 */
                g_exc_flag = false;
                if(g_wdt_int_no != 0)
                {
                    enable_irq(g_wdt_int_no);
                }
            }
        }
        else
        {
            dump_fetal("invalid mod id: 0x%x\n", modid);
        }
    }
    else
    {
        /* �������˯�� */
        wake_unlock(&g_dump_wake_lock);
        /* ����ϵͳ */
        if(1 == g_dump_cfg.dump_cfg.Bits.sysErrReboot)
        {
            g_dump_global_info->internal_info.comm_internal.start_wait_flag = DUMP_INIT_FLAG_WAIT;
            dump_fetal("enter drv reboot process\n");
            bsp_drv_power_reboot_direct();
        }
    }
}

s32 dump_init_phase2(void)
{
    struct rdr_exception_info_s exc_info;
    struct rdr_module_ops_pub   soc_ops;
    int i;

    g_dump_global_info->internal_info.app_internal.save_file_flag = DUMP_SAVE_FILE_NORMAL;
    g_dump_global_info->internal_info.comm_internal.start_wait_flag = DUMP_INIT_FLAG_WAIT;
    g_dump_global_info->internal_info.m3_internal.start_wait_flag = DUMP_INIT_FLAG_WAIT;

    /*ȫ����Ϣ��ʼ��*/
    dump_global_info_init();


    /*��ʼ��CP ��coresight �ռ�*/
    dump_coresight_memmap();

    /*ȫ����Ϣ��ʼ��*/
    dump_base_info_init();

    /*��ʼ������*/
    dump_queue_t_init();

    /*ϵͳ���лص�����ע��*/
    dump_register_hook();

    /*����쳣֪ͨ�� */
    dump_register_notifier();

    /*ϵͳ���лص�����ע��*/
    dump_init_done();

    /* ���PRINT�������� */
    memset((void *)DUMP_PRINT_ADDR, 0, (u32)DUMP_PRINT_SIZE); /* [false alarm]:����Fortify���� */

    if(DUMP_MBB == dump_get_product_type())
    {
        /* ������������¼��ʱ�� */
        dump_start_timer(60000);
    }

    g_rdr_exc_info.dump_done = BSP_NULL;
    /* ��RDRע��MOD ID */
    for(i=0; i<sizeof(g_exc_info)/sizeof(struct rdr_exception_info_s); i++)
    {

        /* coverity[unsigned_compare]*/
        if(rdr_register_exception(&g_exc_info[i]) < 0)
        {
            dump_fetal("dump init: rdr_register_exception 0x%x fail\n", g_exc_info[i].e_modid);
            return BSP_ERROR;
        }
    }

    /* LPM3ΪMBB���� */
    if(DUMP_MBB == dump_get_product_type())
    {
        memset(&exc_info, 0, sizeof(struct rdr_exception_info_s));
        exc_info.e_modid = RDR_MODEM_LPM3_MOD_ID;
        exc_info.e_notify_core_mask = RDR_CP;
        exc_info.e_reset_core_mask  = RDR_CP;

        /* coverity[unsigned_compare]*/
        if(rdr_register_exception(&exc_info) < 0)
        {
            dump_fetal("dump init: rdr_register_exception LPM3 ID fail\n");
            return BSP_ERROR;
        }

        wake_lock_init(&g_dump_wake_lock, WAKE_LOCK_SUSPEND, "dump_wake");
    }

    soc_ops.ops_dump  = (pfn_dump)dump_callback;
    soc_ops.ops_reset = (pfn_reset)dump_reset;
    /* coverity[unsigned_compare] */
    if(rdr_register_module_ops(RDR_CP, &soc_ops, &g_rdr_exc_info.soc_rst) < 0)
    {
        dump_fetal("dump init: rdr_register_soc_ops fail\n");
        return BSP_ERROR;
    }

    dump_rm_old_dir();
    dump_fetal("dump init success!\n");

    return BSP_OK;
}

s32 __init bsp_dump_init(void)
{
    s32 ret;
    /*lint -save -e958 */
#ifdef CONFIG_HISI_DUMP
    u32 * dump_flag = (u32 *)SRAM_DUMP_POWER_OFF_FLAG_ADDR;
    *dump_flag = DUMP_START_CRASH;
#endif
    /*lint -restore */
    g_exc_flag = false;

    /*��ʼ�����ֽṹ��*/
    ret  = dump_init_phase1();
    if(BSP_OK != ret)
    {
        return BSP_ERROR;
    }

    /*����������ͣ���Ϊ��ǰ�ļ�ϵͳ�����ã���Ҫ�����¶���:
      1. ���Ȱ�reset_log��¼���ڴ�;
      2. ��鵱ǰ�Ƿ����쳣������
         ��������������¼reset_log���ļ�ϵͳ��ͬʱ������ʼ��;
         ����ǣ���ͣ��ʼ�������������¼reset_log��dump���ݵ��ļ���Ȼ�������ʼ��
      3. ��¼�������У�ÿ1s���һ���ļ�ϵͳ�Ƿ���ã�ֱ������֮��ʼ��¼�ļ���
         ����г�ʱ���ڣ�60s֮��������Σ���ʼ������һ�׶�
    */
    dump_init_phase2();
    ret = bsp_dump_parse_apr_dts_info();
    if(ret)
    {
       dump_fetal("dump init apr info fail\n");
    }
    return BSP_OK;
}

u32 dump_match_rdr_mod_id(u32 drv_mod_id)
{
    u32 rdr_mod_id = RDR_MODEM_AP_MOD_ID;

    if(DUMP_PHONE == dump_get_product_type())
    {
        switch(drv_mod_id)
        {
        case DRV_ERRNO_RESET_SIM_SWITCH:
            rdr_mod_id = RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID;
            return rdr_mod_id;
        case DRV_ERRNO_RESET_RILD:
            rdr_mod_id = RDR_MODEM_CP_RESET_RILD_MOD_ID;
            return rdr_mod_id;
        case DRV_ERRNO_RESET_3RD_MODEM:
            rdr_mod_id = RDR_MODEM_CP_RESET_3RD_MOD_ID;
            return rdr_mod_id;
        case DRV_ERRNO_RESET_REBOOT_REQ:
            rdr_mod_id = RDR_MODEM_CP_RESET_REBOOT_REQ_MOD_ID;
            return rdr_mod_id;
        case DRV_ERROR_USER_RESET:
            rdr_mod_id = RDR_MODEM_CP_RESET_USER_RESET_MOD_ID;
            return rdr_mod_id;
        default:
            break;
        }
    }

    if((DRV_ERRNO_DUMP_WDT == drv_mod_id) && (g_pdump_info->p_dump->dump_head.except_core == DUMP_CPU_COMM))
    {
        rdr_mod_id = RDR_MODEM_CP_WDT_MOD_ID;
    }
    else
    {
        rdr_mod_id = RDR_MODEM_AP_MOD_ID;
    }
    return rdr_mod_id;

}
void system_error(u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    u32 rdr_mod_id = RDR_MODEM_AP_MOD_ID;
    dump_fetal("[0x%x]================ modem acore enter system error! ================\n", om_timer_get());
    dump_fetal("mod_id=0x%x arg1=0x%x arg2=0x%x data=0x%p len=0x%x\n", mod_id, arg1, arg2, data, length);

    rdr_mod_id = dump_match_rdr_mod_id(mod_id);

    dump_fetal("rdr mod id is 0x%x\n", rdr_mod_id);
    /* modem������λ��������log */
    if(rdr_mod_id == RDR_MODEM_CP_RESET_SIM_SWITCH_MOD_ID ||rdr_mod_id ==  RDR_MODEM_CP_RESET_USER_RESET_MOD_ID)
    {
        dump_fetal("rdr mod id no need to save log,enter rdr_system_error directly\n");
        rdr_system_error(rdr_mod_id, arg1, arg2);
        return;
    }

    if(g_exc_flag)
    {
        dump_fetal("exception has happened can not deal new exception\n");
        return;
    }
    else
    {
        g_exc_flag = true;
    }

    if (DUMP_INIT_FLAG != g_dump_global_info->internal_info.app_internal.init_flag)
    {
        return;
    }

    /*if modem is not in signal reset notify*/
    if(bsp_reset_ccore_is_reboot() == 0)
    {
        dump_notify_target(rdr_mod_id);
    }
    else
    {
        dump_fetal("modem is reseting now,do not notify\n");  
    }

    if(DUMP_MBB == dump_get_product_type())
    {
        /*�����쳣������Ϣ*/
        dump_save_exc_task((u32)(uintptr_t)(&(g_dump_base_info->regSet[0])));
        dump_fetal("save exc task finish\n");
    }
    else
    {
        g_dump_base_info->current_task = (uintptr_t)get_current();
    }

    if(g_pdump_info->p_dump->dump_head.except_core == DUMP_CPU_COMM && mod_id ==DRV_ERRNO_DUMP_WDT && arg1 == DUMP_REASON_WDT)
    {

        dump_fetal(" wdt error save ccore etb \n");
        dump_cs_etb(CCORE_WDT_TIMEOUT);
    }

    bsp_coresight_disable();

    g_dump_base_info->modId = mod_id;
    g_dump_base_info->arg1 = arg1;
    g_dump_base_info->arg2 = arg2;
    g_dump_base_info->arg3 = (u8 *)data;
    g_dump_base_info->arg3_length = length;

    dump_system_error_enter();
    dump_save_global_info();
    dump_save_base_info();
    dump_save_usr_data(data, length);
    dump_show_stack();

    /* ��ֹ����˯�� */
    if(DUMP_MBB == dump_get_product_type())
    {
        wake_lock(&g_dump_wake_lock);
        /* ��������������Ϣ */
        dump_save_all_task();

        /* ֹͣ��ʱ����ˢ�������� */
        dump_stop_timer();
        dump_save_task_name();
        dump_fetal("dump save  task  name finish\n");
    }

    if(DUMP_PHONE == dump_get_product_type())
    {
        /* ����ϵͳ��������dump field */
        om_save_sysctrl();
    }

    /* ����Ĵ�����Ϣ */
    dump_save_regs();

    /* APP���ݱ������ */
    dump_save_app_done();

    /*�ж��з���panic*/
    if((DUMP_MBB == dump_get_product_type())&&(in_interrupt())&&(g_dump_panic_flag == true))
    {
        dump_save_log();

        dump_wait_ext_area_save_done(300,false);

        save_last_profile();

        /*���ֳ�����Ҫ����֮�󱣴�log*/
        g_dump_global_info->internal_info.app_internal.save_file_flag = DUMP_SAVE_FILE_NEED;
        /*��֤���ݾ���д��*/
        cache_sync();

        /* ����ϵͳ */
        if(1 == g_dump_cfg.dump_cfg.Bits.sysErrReboot)
        {
            g_dump_global_info->internal_info.comm_internal.start_wait_flag = DUMP_INIT_FLAG_WAIT;
            dump_fetal("enter drv reboot process\n");
            bsp_drv_power_reboot_direct();
            return;
        }
        /* �������˯�� */
        wake_unlock(&g_dump_wake_lock);
    }

    rdr_system_error(rdr_mod_id, arg1, arg2);

    return;
}
EXPORT_SYMBOL_GPL(system_error);

s32 bsp_dump_register_sysview_hook(dump_sysview_t mod_id, dump_hook func)
{
    if(mod_id >= DUMP_SYSVIEW_BUTT )
    {
        return BSP_ERR_DUMP_INVALID_MODULE;
    }
    else
    {
        g_dump_trace_read_cb[mod_id] = func;
    }

    return BSP_OK;
}

void bsp_dump_trace_stop(void)
{
    dump_trace_stop();
}

/*****************************************************************************
* �� �� ��  : bsp_om_set_hso_conn_flag
*
* ��������  :�ýӿ���ҪMSP�����ģ����HSO���ӻ���ȥ���ӵ�ʱ�����
*
* �������  : flag :���ӱ�־��1��ʾ���ӣ�0��ʾ�Ͽ�
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/

void bsp_dump_set_hso_conn_flag(u32 flag)
{
    g_dump_global_info->internal_info.hso_connect_flag = flag;
}

void dump_show_field(void)
{
    dump_area_head_t * head;
    dump_field_map_t * field;
    u32 i;
    u32 used_len = 0;
    u32 field_cnt;

    head = &(g_pdump_info->p_area[DUMP_AREA_AP]->area_head);
    field_cnt = head->field_num;

    dump_fetal("-----------------------------------------\n");
    dump_fetal("AP AREA INFO(BASE ADDR %p):\n", head);

    for(i=0; i<field_cnt; i++)
    {
        field = &(g_pdump_info->p_area[DUMP_AREA_AP]->fields[i]);
        dump_fetal("FILED %-16s: id=0x%-8x offset=0x%-8x size=0x%x\n", field->field_name, field->field_id, field->offset_addr, field->length);
        used_len += field->length;
    }

    dump_fetal("USED: 0x%x, LEFT: 0x%x\n", used_len, DUMP_AREA_AP_SIZE - DUMP_AREA_AP_HEAD_SIZE - DUMP_AREA_AP_MAP_SIZE - used_len);

    head = &(g_pdump_info->p_area[DUMP_AREA_CP]->area_head);
    field_cnt = head->field_num;
    used_len  = 0;

    dump_fetal("-----------------------------------------\n");
    dump_fetal("CP AREA INFO(BASE ADDR %p):\n", head);

    for(i=0; i<field_cnt; i++)
    {
        field = &(g_pdump_info->p_area[DUMP_AREA_CP]->fields[i]);
        dump_fetal("FILED %-16s: id=0x%-8x offset=0x%-8x size=0x%x\n", field->field_name, field->field_id, field->offset_addr, field->length);
        used_len += field->length;
    }

    dump_fetal("USED: 0x%x, LEFT: 0x%x\n", used_len, DUMP_AREA_CP_SIZE - DUMP_AREA_CP_HEAD_SIZE - DUMP_AREA_CP_MAP_SIZE - used_len);

    if(DUMP_MBB == dump_get_product_type())
    {
        head = &(g_pdump_info->p_area[DUMP_AREA_LPM3]->area_head);
        field_cnt = head->field_num;
        used_len  = 0;

        dump_fetal("-----------------------------------------\n");
        dump_fetal("LPM3 AREA INFO(BASE ADDR %p):\n", head);

        for(i=0; i<field_cnt; i++)
        {
            field = &(g_pdump_info->p_area[DUMP_AREA_LPM3]->fields[i]);
            dump_fetal("FILED %-16s: id=0x%-8x offset=0x%-8x size=0x%x\n", field->field_name, field->field_id, field->offset_addr, field->length);
            used_len += field->length;
        }

        dump_fetal("USED: 0x%x, LEFT: 0x%x\n", used_len, DUMP_AREA_LPM3_SIZE - DUMP_AREA_LPM3_HEAD_SIZE - DUMP_AREA_LPM3_MAP_SIZE - used_len);
    }
}

module_init(bsp_dump_init);

/*lint -restore +e19*/

extern void* g_pdump_backup_addr;
s32 __init  bsp_dump_save_backup(void)
{
    struct task_struct * pid;
    struct sched_param   param;
    bool need_save;

    if(g_pdump_backup_addr == NULL)
    {
        dump_error("bsp_dump_save_backup: ioremap backup physical address failed!\n");
        return BSP_ERROR;
    }

    need_save = dump_need_save((u8 *)g_pdump_backup_addr);
    /* coverity[unchecked_value] */
    bsp_om_record_resetlog((u8 *)g_pdump_backup_addr);
    if(need_save)
    {
        /* coverity[check_return] */
        bsp_om_save_dump_backup(OM_DUMP_PATH, (u8 *)g_pdump_backup_addr, DUMP_SIZE, dump_get_product_type());
    }
    if(g_pdump_backup_addr)
    {
        kfree(g_pdump_backup_addr);
    }

    pid = (struct task_struct *)kthread_run(dump_save_task, 0, "dump_save");
    if (IS_ERR((void*)pid))
    {
        dump_error("bsp_dump_save_backup[%d]: create kthread task failed! ret=%p\n", __LINE__, pid);
        return BSP_ERROR;
    }

    g_dump_ctrl.dump_task_id = (uintptr_t)pid;

    param.sched_priority = 99;
    if (BSP_OK != sched_setscheduler(pid, SCHED_FIFO, &param))
    {
        dump_error("bsp_dump_save_backup[%d]: sched_setscheduler failed!\n", __LINE__);
        return BSP_ERROR;
    }

    return BSP_OK;
}
EXPORT_SYMBOL(bsp_dump_save_backup);

device_initcall_sync(bsp_dump_save_backup);

#ifdef CONFIG_HISI_DUMP
/* dump�����ں��޸� begin */
void dump_set_exc_vec(u32 vec)
{
    g_ulExcType = vec;
}

void dump_int_enter(u32 dir, u32 irq_num)
{
    if(g_int_switch_hook != NULL)
    {
        g_int_switch_hook(dir, irq_num);
    }
}

void dump_int_exit(u32 dir, u32 irq_num)
{
    if(g_int_switch_hook != NULL)
    {
        g_int_switch_hook(dir, irq_num);
    }
}

int dump_stack_trace_print(unsigned long where)
{
    if(g_ul_stack_trace_enable == true)
    {
        dump_stack_hook(where);
        return BSP_OK;
    }

    return BSP_ERROR;
}

/* dump�����ں��޸� end */

int reboot_notify(struct notifier_block *nb, unsigned long event, void *pReg)
{
    printk("%s enter\n", __FUNCTION__);

    return 0;
}

struct notifier_block  reboot_block = {
    .notifier_call = reboot_notify,
    .priority = 100,
};

void reboot_reg(void)
{
    int ret;
    ret = register_reboot_notifier(&reboot_block);
    printk("%s: ret %x\n", __FUNCTION__, ret);
}

/* dump die notifier */
static struct notifier_block dump_die_notifier =
{
    .notifier_call = dump_die_callback,
    .priority      = 0,
};

/* dump panic notifier */
static struct notifier_block dump_panic_notifier =
{
    .notifier_call = dump_panic_callback,
    .priority      = 0,
};

/* dump task switch notifier */
static struct notifier_block dump_task_switch_notifier =
{
    .notifier_call = dump_task_switch_callback,
    .priority      = 0,
};

/* dump die notifier callback function */
int dump_die_callback(struct notifier_block *nb, unsigned long action, void *data)
{
    struct die_args* pargs = (struct die_args*)data;

    printk("dump die callback : str=%s, err=%ld, trapnr=%d, signr=%d\n",
        pargs->str, pargs->err, pargs->trapnr, pargs->signr);
    memcpy(&g_pt_regs, pargs->regs, sizeof(struct pt_regs));

    if (in_interrupt()==0)
    {
        if(!panic_on_oops)
        {
            dump_exc_hook(current, g_ulExcType, (u32*)&g_pt_regs);
        }
    }

    return NOTIFY_OK;
}

/* dump panic notifier callback function */
int dump_panic_callback(struct notifier_block *nb, unsigned long action, void *data)
{
    printk("dump panic callback : %s\n", (char*)data);

    g_dump_panic_flag = true;
    dump_exc_hook(current, g_ulExcType, (u32*)&g_pt_regs);
    return NOTIFY_OK;
}

/* dump task switch callback function */
int dump_task_switch_callback(struct notifier_block *nb, unsigned long action, void *data)
{
    struct thread_info *thread = data;

    if (action != THREAD_NOTIFY_SWITCH)
        return NOTIFY_DONE;

    dump_task_switch_hook(NULL, thread->task);
    return NOTIFY_OK;
}

/* dump register panic notifier chain */
int dump_register_panic_notifier(struct notifier_block *nb)
{
    return atomic_notifier_chain_register(&panic_notifier_list, nb);
}

/* dump unregister panic notifier chain */
int dump_unregister_panic_notifier(struct notifier_block *nb)
{
    return atomic_notifier_chain_unregister(&panic_notifier_list, nb);
}
#endif

/* dump register notifier into kernel */
void dump_register_notifier(void)
{
#ifdef CONFIG_HISI_DUMP
    /* register task switch notifier */
    if(1 == g_dump_cfg.dump_cfg.Bits.taskSwitch)
    {
        thread_register_notifier(&dump_task_switch_notifier);
    }

    /* register exception notifier */
    if(1 == g_dump_cfg.dump_cfg.Bits.ARMexc)
    {
        register_die_notifier(&dump_die_notifier);
        dump_register_panic_notifier(&dump_panic_notifier);
    }
#endif
}
void show_last_profile_addr(void)
{
    uintptr_t sram_max_cpufreq = SRAM_MAX_CPUFREQ_PROFILE_ADDR;
    uintptr_t sram_min_cpufreq = SRAM_MIN_CPUFREQ_PROFILE_ADDR;
    uintptr_t sram_dump_power  = SRAM_DUMP_POWER_OFF_FLAG_ADDR;
    dump_fetal("SRAM_MAX_CPUFREQ_PROFILE_ADDR = 0x%p",sram_max_cpufreq);

    dump_fetal("SRAM_MIN_CPUFREQ_PROFILE_ADDR = 0x%p",sram_min_cpufreq);

    dump_fetal("SRAM_DUMP_POWER_OFF_FLAG_ADDR = 0x%p",sram_dump_power);
}
/*****************************************************************************
* �� �� ��  : bsp_dump_parse_apr_dts_info
*
* ��������  : ��ȡdts��ʼ��������Ϣ���ж���Ϣ �����Ϣ
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
u32 bsp_dump_parse_apr_dts_info(void)
{
    struct device_node *dev_node = NULL;
    struct device_node *child = NULL;
    struct property *prop = NULL;
    const __be32 *p = NULL;
    char * module_name = NULL;
    u32 sum = 0;
    u32 alloc_size = 0;
    u32 index = 0;
    u32 module_index = 0;
    void * temp = NULL;
    u32 modid_sum = 0;
    u32 task_sum = 0;
    u32 int_sum = 0;
    u32 u = 0;
    u32 i = 0;
    /*��ȡ���������Ϣ*/
    dev_node = of_find_compatible_node(NULL,NULL,"hisilicon,apr_config");
    if(!dev_node)
    {
        dump_fetal("get apr_config node failed!\n");
        return MDRV_ERROR;
    }

    for_each_child_of_node(dev_node,child)
    {
        if(of_property_read_u32(child, "modid_sum", &sum))
        {
            sum = 0;
            dump_fetal("get modid_sum failed!\n");
        }
        modid_sum+=sum;
        if(of_property_read_u32(child, "task_sum", &sum))
        {
            sum = 0;
            dump_fetal("get task_sum failed!\n");
        }
        task_sum+=sum;
        if(of_property_read_u32(child, "int_sum", &sum))
        {
            sum = 0;
            dump_fetal("get int_sum failed!\n");
        }
        int_sum+=sum;
    }

    alloc_size = modid_sum*(sizeof(modid_info_t) - sizeof(u32)) + sizeof(u32);
    g_p_modid_table = osl_malloc(alloc_size);
    if(NULL == g_p_modid_table)
    {
        dump_fetal("p_module_info malloc fail, size:0x%x\n", alloc_size);
    }
    memset(g_p_modid_table, 0, alloc_size);
    alloc_size = int_sum*(sizeof(interupt_table_t) - sizeof(u32)) + sizeof(u32);
    g_cp_interupt_table = (interupt_table_t *)osl_malloc(alloc_size);
    if(NULL == g_cp_interupt_table)
    {
        dump_fetal("g_cp_interupt_table malloc fail, size:0x%x\n", alloc_size);
    }
    memset(g_cp_interupt_table, 0, alloc_size);

    alloc_size = task_sum*(sizeof(task_table_t) - sizeof(u32)) + sizeof(u32);
    g_cp_task_table = (task_table_t *)osl_malloc(alloc_size);
    if(NULL == g_cp_task_table)
    {
        dump_fetal("g_cp_task_table malloc fail, size:0x%x\n", alloc_size);
    }
    memset(g_cp_task_table, 0, alloc_size);

    child = NULL;
    for_each_child_of_node(dev_node,child)
    {
        /*������ζ�ȡ�������ʧ�����ٶ�ȡ������Ϣ*/
        if(of_property_read_string(child, (const char*)"module_name", (const char**)&module_name))
        {
            dump_fetal("get module_name fail\n");
            continue;
        }
        /*��ȡmodid��Ϣ*/
        if(of_property_read_u32(child, "modid_sum", &sum))
        {
            sum = 0;
            dump_fetal("get modid_sum failed!\n");
        }

        of_property_for_each_u32(child, "modid_range", prop , p, u)
        {
            module_index = g_p_modid_table->moudid_sum;
            if(i%2 == 0)
            {
                g_p_modid_table->modid_info[module_index].modid_start = u;
            }
            if(i%2 == 1)
            {
                g_p_modid_table->modid_info[module_index].modid_end = u;
                snprintf(g_p_modid_table->modid_info[module_index].module,DUMP_MODULE_NAME_LEN, "%s", module_name);
                g_p_modid_table->moudid_sum++;
            }
            i++;
        }
        /*��ȡtask��Ϣ*/
        if(of_property_read_u32(child, "task_sum", &sum))
        {
            sum = 0;
            dump_fetal("get task_sum failed!\n");
        }
        for(index = 0; (index < sum)&&(g_cp_task_table); index++)
        {
            module_index = g_cp_task_table->task_sum;
            if(of_property_read_string_index(child, (const char*)"task_name", index,(const char**)&temp))
            {
                dump_fetal("get task_name fail\n");
            }
            else
            {
                snprintf(g_cp_task_table->task_info[module_index].task_name, 16, "%s",(char *)temp);
                snprintf(g_cp_task_table->task_info[module_index].module,DUMP_MODULE_NAME_LEN, "%s", module_name);
                g_cp_task_table->task_sum++;
            }
        }
        /*��ȡ�ж���Ϣ*/
        if(of_property_read_u32(child, "int_sum", &sum))
        {
            sum = 0;
            dump_fetal("get int_sum failed!\n");
        }
        for(index = 0; (index < sum)&&(g_cp_interupt_table); index++)
        {
            module_index = g_cp_interupt_table->intrupt_sum;
            if(of_property_read_u32_index(child, "int_id" ,index, &(g_cp_interupt_table->interupt_info[module_index].interrpt_id)))
            {
                dump_fetal("get int_id fail\n");
            }
            else
            {
                snprintf(g_cp_interupt_table->interupt_info[module_index].module,DUMP_MODULE_NAME_LEN, "%s", module_name);
                g_cp_interupt_table->intrupt_sum++;
            }
        }
    }

    dump_fetal("init apr dts success\n");
    return MDRV_OK;
}
/*****************************************************************************
* �� �� ��  : bsp_dump_parse_reset_info
*
* ��������  : ���쳣��Ϣ����
*
* �������  :  reset_info:�洢��������쳣��Ϣ��������
               size
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_parse_reset_info( dump_reset_log_t *dump_reset_info, dump_except_info_t dump_except_info)
{
    bsp_dump_get_reset_ccore(dump_except_info.except_core, dump_reset_info->reboot_core);
    bsp_dump_get_reset_reason(dump_except_info.except_reason, dump_reset_info->reboot_reson);
    bsp_dump_get_reset_modid(dump_except_info.except_reason, dump_except_info.modId, &dump_reset_info->modid);
    bsp_dump_get_reset_voice(dump_except_info.voice, dump_reset_info->voice);
    bsp_dump_get_reset_task(dump_except_info, dump_reset_info->task_name,&dump_reset_info->reboot_int);
    bsp_dump_get_reset_module(dump_except_info, dump_reset_info->task_name,dump_reset_info->module_name);
    if(DUMP_OUT_VOICE == dump_except_info.voice)
    {
        snprintf(dump_reset_info->brieftype, sizeof(dump_reset_info->brieftype), "%s", dump_reset_info->module_name);
    }
    else
    {
        snprintf(dump_reset_info->brieftype, sizeof(dump_reset_info->brieftype),"%s_VOICE", dump_reset_info->module_name);
    }
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_module
*
* ��������  : ������λ���������
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_module(dump_except_info_t dump_except_info, u8* task_name,u8 * module)
{
    u32 index = 0;
    u32 size = 0;

    /*������λ����modidȷ���������*/
    if(DUMP_REASON_NORMAL == dump_except_info.except_reason)
    {
        if(!g_p_modid_table)
        {
            return;
        }
        for(index = 0; index < g_p_modid_table->moudid_sum; index++)
        {
            if((dump_except_info.modId >=g_p_modid_table->modid_info[index].modid_start)
                &&(dump_except_info.modId< g_p_modid_table->modid_info[index].modid_end) )
            {
                snprintf(module, 12, "%s", g_p_modid_table->modid_info[index].module);
                return;
            }
        }
        /*������Ҳ�����λ������������ø�λ������ж����ж��������*/
        if(index == g_p_modid_table->moudid_sum)
        {
            dump_fetal("can't find the modid in dts config\n");
            dump_fetal("reboot modid:0x%x\n", dump_except_info.modId);
        }
    }

    /*wdg abort�����������������жϺ�ȷ���������*/
    /*���Ϊ�жϸ�λ*/
    if(DUMP_CTX_INT == dump_except_info.reboot_context)
    {
        if(!g_cp_interupt_table)
        {
            return;
        }
        for(index = 0; index < g_cp_interupt_table->intrupt_sum; index++ )
        {
            if(dump_except_info.reboot_int == g_cp_interupt_table->interupt_info[index].interrpt_id)
            {
                snprintf(module, 12, "%s",  g_cp_interupt_table->interupt_info[index].module);
                break;
            }
        }
        if(index == g_cp_interupt_table->intrupt_sum)
        {
            dump_fetal("can't find the int in dts config\n");
            dump_fetal("reboot int num:0x%x\n", dump_except_info.reboot_int);
        }
        return;
    }
    if(DUMP_CTX_TASK == dump_except_info.reboot_context)
    {
        /*����Ϊ����λ*/
        if(!g_cp_task_table)
        {
            return;
        }
        /*�����������*/
        for(index = 0; index < g_cp_task_table->task_sum; index++ )
        {
            size = strlen(g_cp_task_table->task_info[index].task_name) > strlen(task_name)? \
                        strlen(task_name):strlen(g_cp_task_table->task_info[index].task_name);
            if(!strncmp(task_name, g_cp_task_table->task_info[index].task_name, size))
            {
                snprintf(module, 12, "%s",  g_cp_task_table->task_info[index].module);
                break;
            }
        }
        /*��������������в��Ҳ��������������Ϊ��*/
        if(index == g_cp_task_table->task_sum)
        {
            dump_fetal("can't find the task in dts config\n");
            dump_fetal("reboot task name:%s\n", task_name);
            return;
        }
    }
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_cp_reset_reason
*
* ��������  : ��ȡCP��λ��ԭ��
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_task(dump_except_info_t dump_except_info,  u8 * task_name, u32 * reboot_int)
{
    u8* task_name_table = NULL;
    u32 task_cnt = 0;
    dump_task_info_s * temp_task_name = NULL;
    u8 *dump_base_info = NULL;
    u32 task_index = 0;
    u32 task_info_filed = 0;
    unsigned long task_name_offset = 0;

    /*�жϴ���*/
    if(DUMP_CTX_INT == dump_except_info.reboot_context)
    {
        dump_fetal("reboot reason int\n");
        *reboot_int = dump_except_info.reboot_int;
        return;
    }
    /*������*/
    if((DUMP_REASON_NORMAL == dump_except_info.except_reason)||(DUMP_REASON_ARM == dump_except_info.except_reason))
    {
        if(DUMP_CPU_COMM == dump_except_info.except_core)
        {
            task_info_filed = DUMP_CP_BASE_INFO;
            task_name_offset = DUMP_CP_TASK_NAME_OFFSET;
        }
        else if(DUMP_CPU_APP == dump_except_info.except_core)
        {
            task_info_filed = DUMP_AP_BASE_INFO;
            task_name_offset = DUMP_AP_TASK_NAME_OFFSET;
        }
        else
        {
            dump_fetal("except core error value:0x%x\n", dump_except_info.except_core);
            return;
        }
        /*��ȡ������Ϣ�������л���¼��ַ��Ϣ*/
        dump_base_info = bsp_dump_get_field_addr(task_info_filed);
        if(NULL == dump_base_info)
        {
            dump_fetal("get ddr info fail\n");
            dump_fetal("base info   field:0x%x ptr:0x%p\n", task_info_filed, dump_base_info);
            return;
        }
        snprintf(task_name, 16, "%s",(dump_base_info + task_name_offset));
    }
    if(DUMP_REASON_WDT == dump_except_info.except_reason)
    {
        /*���Ϊwdg��λ*/
        if(DUMP_CPU_COMM == dump_except_info.except_core)
        {
            task_info_filed = DUMP_CP_ALLTASK;
        }
        else if(DUMP_CPU_APP == dump_except_info.except_core)
        {
            task_info_filed = DUMP_AP_ALLTASK;
        }
        /*CP�洢������������*/
        task_name_table = bsp_dump_get_field_addr(task_info_filed);
        if(NULL == task_name_table)
        {
            dump_fetal("get cp tasck name ddr fail, field:0x%x\n", task_info_filed);
            return;
        }

        task_cnt = *((u32 *)task_name_table + 3)/4;
        /* ƫ��10�ֽڣ�ȥ������ͷ */
        task_name_table += 0x10;
        temp_task_name = (dump_task_info_s *)task_name_table;
        dump_fetal("task_cnt:0x%x\n", task_cnt);
        /*����������*/
        for(task_index = 0;task_index < task_cnt; task_index++)
        {
            dump_fetal("index:0x%x\n", task_index);
            dump_fetal("task_id:0x%x\n", temp_task_name->task_id);
            if(temp_task_name->task_id == dump_except_info.reboot_task)
            {
                dump_fetal("reboot task:%s\n", temp_task_name->task_name);
                snprintf(task_name, 12 , "%s", temp_task_name->task_name);
                break;
            }
            task_index++;
            temp_task_name++;
        }

        /*û���ҵ�������*/
        if(task_index == task_cnt)
        {
            dump_fetal("can't find the task, task id:0x%x\n", dump_except_info.reboot_task);
            return;
        }
    }
}
u32 bsp_dump_search_taskid(dump_queue_t *Q)
{
    u32 element = 0;
    u32 index = 0;
    u32 queue_index = 0;

    for(index = 0; index < Q->rear/2; index++)
    {
        queue_index = ((Q->rear+Q->maxNum)-2*(index + 1)) %Q->maxNum;
        element = Q->data[queue_index];
        dump_fetal("queue_index 0x%x element 0x%x\n", queue_index, element);
        if((DUMP_INT_IN_FLAG != ((element>>16)&0xFFFF))&&(DUMP_INT_EXIT_FLAG != ((element>>16)&0xFFFF)))
        {
            return element;
        }
    }
    return MDRV_ERROR;
}

/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_context_and_taskid
*
* ��������  :��ȡ��λΪ�жϸ�λ��������λ,���Ϊ����λ,������λ����id�������λΪ�жϣ�������λ�жϺ�
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_context_and_id(u32 *reboot_context, u32 *reboot_task,u32 *reboot_int, dump_head_t* dump_head)
{
    dump_queue_t* task_switch = NULL;
    dump_base_info_t *dump_base_info = NULL;
    u32 task_switch_field = 0;
    u32 base_info_field = 0;
    u32 element = 0;

    *reboot_task = MDRV_ERROR;
    if(DUMP_CPU_COMM == dump_head->except_core)
    {
        task_switch_field = DUMP_CP_TASK_SWITCH;
        base_info_field = DUMP_CP_BASE_INFO;
    }
    else if(DUMP_CPU_APP == dump_head->except_core)
    {
        task_switch_field = DUMP_AP_TASK_SWITCH;
        base_info_field = DUMP_AP_BASE_INFO;
    }
    else
    {
        return;
    }


    task_switch = (dump_queue_t*)bsp_dump_get_field_addr(task_switch_field);
    if(NULL == task_switch)
    {
        dump_fetal("get cp task switch ddr fail, field:0x%x\n", task_switch_field);
        return;
    }
    dump_base_info = (dump_base_info_t*)bsp_dump_get_field_addr(base_info_field);
    if(NULL == dump_base_info)
    {
        dump_fetal("get ddr info fail\n");
        dump_fetal("base info field:0x%x ptr:0x%p\n", base_info_field, dump_base_info);
    }

    /*���Ϊ������λ*/
    if((DUMP_REASON_NORMAL == dump_head->except_reason)&&(dump_base_info))
    {
        *reboot_context = dump_base_info->reboot_context;
        if(DUMP_CTX_INT == dump_base_info->reboot_context)
        {
            *reboot_int = dump_base_info->reboot_int;
            *reboot_task = 0xFFFFFFFF;
            return;
        }
        else
        {
            *reboot_int = 0xFFFFFFFF;
            *reboot_task = bsp_dump_search_taskid(task_switch);
            return;
        }
    }
    /*���Ϊwdg��abort��λ*/
    element = task_switch->data[((task_switch->rear+task_switch->maxNum)-2) % task_switch->maxNum];

    if(DUMP_INT_IN_FLAG == ((element>>16)&0xFFFF))
    {
        *reboot_context = DUMP_CTX_INT;
        *reboot_int = element&0xFFFF;
        *reboot_task = 0xFFFFFFFF;
    }
    else
    {
        *reboot_context = DUMP_CTX_TASK;
        *reboot_int = 0xFFFFFFFF;
        *reboot_task = bsp_dump_search_taskid(task_switch);
    }
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_voice
*
* ��������  : ������λʱ�Ƿ���������
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_voice(u32 voice, u8 * reboot_voice)
{
    if(DUMP_OUT_VOICE == voice)
    {
        snprintf(reboot_voice, 4, "no");
    }
    else
    {
        snprintf(reboot_voice, 4, "yes");
    }
    return;
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_modid
*
* ��������  : ��ȡ��λ��modid
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_modid(u32 reason, u32 reboot_modid, u32 * modId)
{
    if(DUMP_REASON_WDT == reason)
    {
       *modId =  DRV_ERRNO_DUMP_WDT;
    }
    else
    {
        *modId = reboot_modid;
    }
}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_cp_reset_reason
*
* ��������  : ��ȡ��λ��ԭ��
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_reason(u32 reason, u8 * reboot_reason)
{
    if(DUMP_REASON_NORMAL == reason)
    {
        snprintf(reboot_reason, 16, "%s", NOARMAL);
    }
    else if(DUMP_REASON_WDT == reason)
    {
        snprintf(reboot_reason, 16, "%s", WDT);
    }
    else if(DUMP_REASON_ARM == reason)
    {
        snprintf(reboot_reason, 16, "%s", DATA_ABORT);
    }
    else if(DUMP_REASON_UNDEF == reason)
    {
        snprintf(reboot_reason, 16, "%s", UNDEFFINE);
    }
    else
    {
        snprintf(reboot_reason, 16, "%s", UNKNOW);
    }

}
/*****************************************************************************
* �� �� ��  : bsp_dump_get_reset_ccore
*
* ��������  : ��ȡCP��λ��ԭ��
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void bsp_dump_get_reset_ccore(u32 core, char *reboot_core)
{
    if(DUMP_CPU_COMM == core)
    {
        snprintf(reboot_core, 8, "%s", CCORE);
    }
    else if(DUMP_CPU_APP == core)
    {
        snprintf(reboot_core, 8, "%s", ACORE);
    }
    else
    {
        snprintf(reboot_core, 8, "%s", UNKNOW_CORE);
    }
    return;
}

u32  bsp_dump_show_apr_cfg(u32 type)
{
    u32 index = 0;

    if((2 == type)||(0 == type))
    {
        if(!g_cp_interupt_table)
        {
            dump_fetal("g_cp_interupt_table = NULL\n");
            return MDRV_ERROR;
        }
        dump_fetal("interupt sum :0x%x\n", g_cp_interupt_table->intrupt_sum);
        for(index = 0;index < g_cp_interupt_table->intrupt_sum; index++)
        {
            dump_fetal("index:0x%-2x interrpt_id:0x%-8x module_name:%s\n", \
                index, g_cp_interupt_table->interupt_info[index].interrpt_id, \
                g_cp_interupt_table->interupt_info[index].module);
        }
    }
    if((3 == type)||(0 == type))
    {
        if(!g_cp_task_table)
        {
            dump_fetal("g_cp_task_table = NULL\n");
            return MDRV_ERROR;
        }
        dump_fetal("task sum :0x%x\n", g_cp_task_table->task_sum);
        for(index = 0;index < g_cp_task_table->task_sum; index++)
        {
            dump_fetal("index:0x%-2x task:%-16s  module_name:%s\n", \
                index, g_cp_task_table->task_info[index].task_name, \
                g_cp_task_table->task_info[index].module);
        }
    }
    if((4 == type)||(0 == type))
    {
        if(!g_p_modid_table)
        {
            dump_fetal("g_p_modid_table = NULL\n");
            return MDRV_ERROR;
        }
        dump_fetal("modid sum :0x%x\n", g_p_modid_table->moudid_sum);
        for(index = 0;index < g_p_modid_table->moudid_sum; index++)
        {
            dump_fetal("index:0x%-2x modid start:0x%-8x end:0x%-8x module_name:%s\n", \
                index, g_p_modid_table->modid_info[index].modid_start, g_p_modid_table->modid_info[index].modid_end, \
                g_p_modid_table->modid_info[index].module);
        }
    }
    return MDRV_OK;
}
