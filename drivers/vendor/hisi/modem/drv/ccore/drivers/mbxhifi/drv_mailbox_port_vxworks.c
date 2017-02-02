

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
//#include <vxWorks.h>
#include "osl_bio.h"   /*lint !e537*/
#include "osl_thread.h"
#include "osl_sem.h"
#include "osl_malloc.h"
#include "osl_irq.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "product_config.h"
#include "bsp_shared_ddr.h"
#include "drv_mailbox_cfg.h"
#include "drv_mailbox_debug.h"
#include "drv_mailbox_gut.h"
#include "osl_sem.h"
#include "mdrv_ipc.h"
#include "mdrv_timer.h"
#include "osl_bio.h"   /*lint !e537*/

#if defined(__OS_RTOSCK__)
#include "securec.h"
#endif

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  1 ��ά�ɲ���Ϣ�а�����C�ļ���ź궨��
*****************************************************************************/
#undef  _MAILBOX_FILE_
#define _MAILBOX_FILE_   "vxworks"

#define MAILBOX_MILLISEC_PER_SECOND                         1000

#define  MAILBOX_VXWORKS_SEND_FULL_DELAY_MS                 10          /*�������ӳٺ���*/

#ifdef _DRV_LLT_
#define  MAILBOX_VXWORKS_SEND_FULL_DELAY_TIMES              500         /*�������ӳٳ��Դ���*/
#else
#define  MAILBOX_VXWORKS_SEND_FULL_DELAY_TIMES              0          /*�������ӳٳ��Դ���*/
#endif

#ifndef WAIT_FOREVER
#define WAIT_FOREVER	(-1)
#endif

/*****************************************************************************
  ����C��vxworks����ϵͳ���������ݵĴ���ӿڵ��÷�ʽ
*****************************************************************************/
enum MAILBOX_VXWORKS_PROC_STYLE_E
{
    MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED   = 0,  /*0��ʾ����ͨ��*/

    /*���մ���ʽ���忪ʼ*/
    MAILBOX_VXWORKS_PROC_STYLE_RECEV_START,

    /*�ҽ��������ϵ��ʼ�������п�ʼ*/
    MAILBOX_VXWORKS_PROC_STYLE_TASK_RESERVED,

    MAILBOX_VXWORKS_PROC_STYLE_TASK_MSG,
    MAILBOX_VXWORKS_PROC_STYLE_TASK_IFC ,

    /*�ҽ��������ϵ��ʼ�������н���*/
    MAILBOX_VXWORKS_PROC_STYLE_TASK_BUTT,

    /*���ж��д�����ʼ��������*/
    MAILBOX_VXWORKS_PROC_STYLE_INT_NORMAL,


    /*���մ���ʽ�������*/
    MAILBOX_VXWORKS_PROC_STYLE_RECEV_END

};

/*****************************************************************************
    ����C�����䵥������ҽӵ����乤�����м�������
*****************************************************************************/
struct mb_vx_work
{
    unsigned int                               channel_id;      /*����ID�ţ������Ǻ˼�����ID,Ҳ����������ͨ��ID*/
    unsigned int                               data_flag;       /*�������Ƿ������ݵı�־λ*/
    int								(*cb)(unsigned int channel_id);
    struct mb_vx_work                           *next;          /*ָ����һ��*/
#ifdef MAILBOX_OPEN_MNTN
    struct mb_buff                              *mb_priv;
#endif

};

/*****************************************************************************
  ����C������������ص�����
*****************************************************************************/
struct mb_vx_proc
{
    signed char                                 name[16];   /*����ʽ��*/
    unsigned int                               id;         /*����ʽID��*/
    signed int                                 priority;   /*����ʽ���ȼ�*/
    signed int                                 stack;      /*����ջ��С*/
    osl_sem_id                                  sema;       /*����ȴ�����Ϣ*/
    struct mb_vx_work                          *vxqueue;    /*������ҽӵ����乤������*/
};
/*****************************************************************************
  ������������ͨ�������񣬺˼��жϼ����ջص�����֮��Ķ�Ӧ��ϵ
*****************************************************************************/
struct mb_vx_cfg
{
    unsigned int                               channel_id;      /*����ͨ��ID��*/
    unsigned int                               proc_style;      /*�������ͨ�������崦�����乤�����е�����ID��*/
    unsigned int                               Int_src;         /*����ͨ����ʹ�õĺ˼��ж���Դ�š�*/
    unsigned int                               dst_cpu;          /*����ͨ����ʹ�õĺ˼��ж�Ŀ��CPU��*/
};

//extern int read_efuse(unsigned int group, unsigned int *buf, unsigned int len);
void mailbox_usr_init(void);

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/
/*�������������б�*/
MAILBOX_LOCAL struct mb_vx_proc g_mailbox_vx_proc_tbl[] =
{
    /*����ʽ��*/    /*����ʽID��*/                         /*���ȼ�*/   /*ջ��С*/

    /*����ʽ���ʼ����ݴ���*/
    {"mailboxMsg"   ,MAILBOX_VXWORKS_PROC_STYLE_TASK_MSG,     4,          4096        },
    {"mailboxIfc"   ,MAILBOX_VXWORKS_PROC_STYLE_TASK_IFC,     5,          4096        },

    /*�жϷ�ʽ���ʼ����ݴ���*/
    {"mailboxInt"   ,MAILBOX_VXWORKS_PROC_STYLE_INT_NORMAL,     0,          0         },

    /*���ڴ˺���������ʽ��Ŀ�������Ӱ��UT����*/

    /*����*/
};

/*C�˵�����ͨ����Դ��ƽ̨ϵͳ��Դ��Ӧ��ϵ���ñ�*/
MAILBOX_LOCAL struct mb_vx_cfg g_mailbox_vx_cfg_tbl[] =
{
#if 0
    /*����ͨ��������*/
    /*ChannelID*/                                       /*ͨ������ʽID��*/
    {MAILBOX_MAILCODE_RESERVED(MCU,  CCPU, MSG),    MAILBOX_VXWORKS_PROC_STYLE_TASK_MSG      },
    {MAILBOX_MAILCODE_RESERVED(HIFI, CCPU, MSG),    MAILBOX_VXWORKS_PROC_STYLE_TASK_MSG      },
    {MAILBOX_MAILCODE_RESERVED(ACPU, CCPU, MSG),    MAILBOX_VXWORKS_PROC_STYLE_TASK_MSG      },
    {MAILBOX_MAILCODE_RESERVED(ACPU, CCPU, IFC),    MAILBOX_VXWORKS_PROC_STYLE_TASK_IFC      },
    {MAILBOX_MAILCODE_RESERVED(MCU,  CCPU, IFC),    MAILBOX_VXWORKS_PROC_STYLE_TASK_IFC      },
    /*����ͨ������*/
    /*ChannelID*/                                       /*ͨ������ʽID��*/
    {MAILBOX_MAILCODE_RESERVED( CCPU, MCU,  MSG),   MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED    },
    {MAILBOX_MAILCODE_RESERVED( CCPU, HIFI, MSG),   MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED    },
    {MAILBOX_MAILCODE_RESERVED( CCPU, ACPU, MSG),   MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED    },
    {MAILBOX_MAILCODE_RESERVED( CCPU, ACPU, IFC),   MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED    },
    {MAILBOX_MAILCODE_RESERVED( CCPU, MCU, IFC),    MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED    },
#else
    /*����ͨ��������*/
    /*ChannelID*/                                       /*ͨ������ʽID��*/
    {MAILBOX_MAILCODE_RESERVED(HIFI, CCPU, MSG),    MAILBOX_VXWORKS_PROC_STYLE_TASK_MSG      },
    /*����ͨ������*/
    /*ChannelID*/                                       /*ͨ������ʽID��*/
    {MAILBOX_MAILCODE_RESERVED( CCPU, HIFI, MSG),   MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED    },
#endif
    /*������־*/
    {MAILBOX_MAILCODE_INVALID, 0,0}
};

MAILBOX_LOCAL void *mailbox_mutex_create(void);
/*****************************************************************************
  3 ��������
*****************************************************************************/

MAILBOX_LOCAL void mailbox_receive_task(void* para)
{
    struct mb_vx_work    *work   =   MAILBOX_NULL;
    struct mb_vx_proc   *process =      MAILBOX_NULL;
    process = (struct mb_vx_proc*)para;
	/*lint !e716*/
	/*lint -save -e569*/
    /* coverity[no_escape] */
    while (MAILBOX_OK == osl_sem_downtimeout(&process->sema, WAIT_FOREVER)) {
            work = process->vxqueue;
            while (MAILBOX_NULL != work) {
                /*������־λ���������λ�����ö�Ӧ������ID�ŵĻص�����*/
                if (MAILBOX_TRUE == work->data_flag) {
                    work->data_flag = MAILBOX_FALSE;
 #ifdef MAILBOX_OPEN_MNTN
                mailbox_record_sche_recv(work->mb_priv);
 #endif
                    if (work->cb) {
                        if (MAILBOX_OK !=  work->cb(work->channel_id)) {
                             (void)mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_CALLBACK_ERRO, work->channel_id);
                        }
                    } else {
                        (void)mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_CALLBACK_NOT_FIND, work->channel_id);
                        #ifdef _DRV_LLT_
                        /*PC UT ������֤�ܹ�����*/
                        return MAILBOX_ERR_VXWORKS_CALLBACK_NOT_FIND;
                        #endif
                    }
                }
                work = work->next;
            }
        }
}
/*lint -restore*/
/*������˵Ķ����ṩ�ӿ�*/

/*lint -save -e64*/
MAILBOX_EXTERN int mailbox_init_platform(void)
{
    struct mb_vx_proc   *process    = &g_mailbox_vx_proc_tbl[0];
    unsigned int        count      =  sizeof(g_mailbox_vx_proc_tbl) /
                                       sizeof(struct mb_vx_proc);
    unsigned int        proc_id;
    OSL_TASK_ID          task_id;

    /*����ƽ̨�����ж��ź�������*/
    while (count) {
        /*Ϊ������ʽ������ͨ����������*/
        proc_id = process->id;
        if ((proc_id > MAILBOX_VXWORKS_PROC_STYLE_TASK_RESERVED) && (proc_id < MAILBOX_VXWORKS_PROC_STYLE_TASK_BUTT)) {
            /* ���������������ȴ��ź���*/
            osl_sem_init(0, &process->sema);

            /* �������������ݴ�������*/
            #if 0
            if (ERROR == (int)taskSpawn((char *)process->name, (int)process->priority, (int)0,
                            (int)process->stack,
                            (void*)mailbox_receive_task,
                            (int)(&process->sema),
                            (int)(&process->vxqueue),
                            (int)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0, (int)0)) /*lint !e119 !e64*/
            {
                return mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_TASK_CREATE, proc_id);
            }
            #endif
            if(ERROR == osl_task_init((char *)process->name, process->priority, process->stack,(OSL_TASK_FUNC)mailbox_receive_task,(void*)(process), &task_id))
            {
                return mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_TASK_CREATE, proc_id);
            }
        }
        count--;
        process++;
    }

    mailbox_usr_init();

    return MAILBOX_OK;
}
/*lint -restore*/

MAILBOX_LOCAL int mailbox_ipc_process(
                struct mb_vx_work  *work,
                struct mb_vx_proc  *proc,
                unsigned int channel_id,
                unsigned int proc_id)
{
    unsigned int is_find = MAILBOX_FALSE;

    while (work) {
        /*�����乤���������ҵ���Ӧ�����䣬���ñ�־λ���ͷ��ź���֪ͨ��������*/
        if (channel_id  == work->channel_id) {
            if ((proc_id > MAILBOX_VXWORKS_PROC_STYLE_TASK_RESERVED) && (proc_id < MAILBOX_VXWORKS_PROC_STYLE_TASK_BUTT)) {
                is_find = MAILBOX_TRUE;

                /*�����������乤�����������д���������ݱ�־λ*/
                work->data_flag = MAILBOX_TRUE;
 #ifdef MAILBOX_OPEN_MNTN
                mailbox_record_sche_send(work->mb_priv);
 #endif
                /*�ͷ��ź�����֪ͨ����*/
                osl_sem_up(&proc->sema);
            } else if (MAILBOX_VXWORKS_PROC_STYLE_INT_NORMAL == proc_id) {
                 /*�жϴ���ʽ�����ж���ֱ�Ӵ�����������*/
                if (work->cb) {
                    is_find = MAILBOX_TRUE;

                    if (MAILBOX_OK !=  work->cb(work->channel_id)) {
                         (void)mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_CALLBACK_ERRO, work->channel_id);
                    }
                } else {
                     (void)mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_CALLBACK_NOT_FIND, work->channel_id);
                }
            } else {
                is_find = MAILBOX_FALSE;
            }

        }
        work = work->next;
    }

    return (int)is_find;
}

int g_hifimailbox = 0;


extern    MAILBOX_EXTERN struct mb g_mailbox_handle ;
MAILBOX_LOCAL int mailbox_ipc_int_handle(unsigned int int_src)
{
    struct mb_vx_cfg        *cfg    =  &g_mailbox_vx_cfg_tbl[0];
    struct mb_vx_proc       *proc   =   MAILBOX_NULL;
    struct mb_vx_work       *work   =   MAILBOX_NULL;
    unsigned int count = sizeof(g_mailbox_vx_proc_tbl)/sizeof(struct mb_vx_proc);
    unsigned int proc_id = 0;
    unsigned int channel_id = 0;
    unsigned int is_find = MAILBOX_FALSE;
    unsigned int ret_val = MAILBOX_OK;

    if(MAILBOX_INIT_MAGIC != g_mailbox_handle.init_flag)
    {
        return (int)ret_val;
    }

    g_hifimailbox++;

    /*�ҵ�����ID��Ӧ����������*/
    while (MAILBOX_MAILCODE_INVALID != cfg->channel_id) {
        /*�������йҽӵ�����жϺŵĽ�������ͨ��*/
        proc_id = cfg->proc_style;
        if ((int_src == cfg->Int_src) && (MAILBOX_VXWORKS_PROC_STYLE_SEND_RESERVED != cfg->proc_style)) {
            channel_id = cfg->channel_id;

            proc   =  &g_mailbox_vx_proc_tbl[0];
            count          =   sizeof(g_mailbox_vx_proc_tbl)/sizeof(struct mb_vx_proc);
            while (count) {
                /*�ҵ�������ͨ����Ӧ��������Ϣ*/
                if (proc_id == proc->id) {
                    work = proc->vxqueue;
                    is_find = (unsigned int)mailbox_ipc_process( work,
                                                 proc,
                                                 channel_id,
                                                 proc_id);
                    break;
                }
                count--;
                proc++;
            }

            if (0 == count) {
                 ret_val = (unsigned int)mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_MAIL_TASK_NOT_FIND, channel_id);
            }
        }
        cfg++;
    }

    if (MAILBOX_TRUE != is_find) {
         ret_val = (unsigned int)mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_MAIL_INT_NOT_FIND, channel_id);
    }

    return (int)ret_val;
}
MAILBOX_EXTERN int mailbox_process_register(
                unsigned int channel_id,
                 int (*cb)(unsigned int channel_id),
                 void *priv)
{
    struct mb_vx_work       *work    =   MAILBOX_NULL;
    struct mb_vx_cfg        *cfg  =  &g_mailbox_vx_cfg_tbl[0];
    struct mb_vx_proc       *proc =  &g_mailbox_vx_proc_tbl[0];
    struct mb_vx_cfg*        cfg_find     =   MAILBOX_NULL;
    unsigned int count = sizeof(g_mailbox_vx_proc_tbl)/sizeof(struct mb_vx_proc);

    while (MAILBOX_MAILCODE_INVALID != cfg->channel_id) {
        /*�ҵ��봫������ID�������ϵͳ��������*/
        if (cfg->channel_id ==  channel_id) {
            cfg_find = cfg;
            break;
        }
        cfg++;
    }

    if (cfg_find) {
        /*�������������Ӧ�����乤������*/
        while (count) {
            if (cfg_find->proc_style == proc->id) {
                if (proc->vxqueue) {
                    work = proc->vxqueue;
                    while (MAILBOX_NULL != work->next) {
                        work = work->next;
                    }
                    work->next            = (struct mb_vx_work *)osl_malloc(
                                                    sizeof(struct mb_vx_work));
                    if (MAILBOX_NULL == work->next) {
                        return mailbox_logerro_p0(MAILBOX_ERR_VXWORKS_ALLOC_MEMORY);

                    }
                    /*lint -save -e522 -e534 */
                    (void *)mailbox_memset((void *)work->next,0,(unsigned int)(sizeof(struct mb_vx_work)));
                    /*lint -restore*/
                    work->next->channel_id = cfg_find->channel_id;
                    work->next->cb  = cb;
                    work->next->mb_priv = priv;
                } else {
                    proc->vxqueue     = (struct mb_vx_work *)osl_malloc(
                                                   sizeof(struct mb_vx_work));
                    if (MAILBOX_NULL == proc->vxqueue) {
                        return mailbox_logerro_p0(MAILBOX_ERR_VXWORKS_ALLOC_MEMORY);
                    }
                    /*lint -save -e522 -e534 */
                    (void *)mailbox_memset((void *)proc->vxqueue,0,(unsigned int)(sizeof(struct mb_vx_work)));
                    /*lint -restore*/
                    proc->vxqueue->channel_id = cfg_find->channel_id;
                    proc->vxqueue->cb  = cb;
                    proc->vxqueue->mb_priv = priv;
                }
            }
            count--;
            proc++;
        }

        return MAILBOX_OK;
    }

    return  mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_CHANNEL_NOT_FIND, channel_id);

}

void tm_mailbox_msg_reg(unsigned int channel_id)
{
}


MAILBOX_EXTERN int mailbox_channel_register(
                unsigned int channel_id,
                unsigned int int_src,
                unsigned int dst_id,
                unsigned int direct,
                void   **mutex)
{
    struct mb_vx_cfg    *cfg  =  &g_mailbox_vx_cfg_tbl[0];

    while (MAILBOX_MAILCODE_INVALID != cfg->channel_id) {
        if (channel_id == cfg->channel_id) {
            *mutex = mailbox_mutex_create();

            /*ͨ����Դ�������ҵ���ע��IPC�ж�*/
            cfg->Int_src = int_src;
            cfg->dst_cpu  = dst_id;
            if(MIALBOX_DIRECTION_RECEIVE == direct) {
                (void)mdrv_ipc_int_connect((IPC_INT_LEV_E)int_src , (VOIDFUNCPTR)mailbox_ipc_int_handle, int_src);
                (void)mdrv_ipc_int_enable ((IPC_INT_LEV_E)int_src);

                /*���ST����ͨ��ע��*/
                /*lint -save -e522 */
                (void)tm_mailbox_msg_reg((unsigned long)channel_id);
                /*lint -restore*/

                /*TODO: ������������µ��������ԣ�������Ҫ��������һ��ͨ�����ص�:  */
                /*mailbox_ipc_int_handle(int_src);*/
            }

            return MAILBOX_OK;
        }
        cfg++;
    }

    /*���������Ҳ�����Ӧ�����ã�����*/
    return mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_CHANNEL_NOT_FIND, channel_id);

}
MAILBOX_EXTERN int mailbox_delivery(unsigned int channel_id)
{
    struct mb_vx_cfg     *cfg       =  &g_mailbox_vx_cfg_tbl[0];
    struct mb_vx_cfg     *cfg_find  =   MAILBOX_NULL;

    while (MAILBOX_MAILCODE_INVALID != cfg->channel_id) {
        /*�ҵ��봫������ID�������ϵͳ��������*/
        if (cfg->channel_id == channel_id) {
            cfg_find = cfg;
            break;
        }
        cfg++;
    }

    cache_sync();

    if (MAILBOX_NULL != cfg_find) {
        return (long)mdrv_ipc_int_send((IPC_INT_CORE_E)cfg_find->dst_cpu, (IPC_INT_LEV_E)cfg_find->Int_src);
    }

    return mailbox_logerro_p1(MAILBOX_ERR_VXWORKS_CHANNEL_NOT_FIND, channel_id);
}
osl_sem_id g_hifimailbox_mutex;
MAILBOX_LOCAL void *mailbox_mutex_create(void)
{
    osl_sem_init(1,&g_hifimailbox_mutex);
    return (void*)(&g_hifimailbox_mutex);
}


MAILBOX_EXTERN int mailbox_mutex_lock(void **mutexId)
{
    osl_sem_down(*mutexId);
    return 0;
}



MAILBOX_EXTERN void mailbox_mutex_unlock(void **mutex_id)
{
    (void)osl_sem_up(*mutex_id);
}
/*lint -save -e64*/
osl_sem_id g_hifimailbox_comp;
MAILBOX_EXTERN void *mailbox_init_completion(void)
{
    osl_sem_init(0, &g_hifimailbox_comp);
    return (void*)&g_hifimailbox_comp;

}
/*lint -restore*/

MAILBOX_EXTERN int  mailbox_wait_completion(void **sema_id, unsigned int timeout)
{
    long ret = (long)osl_sem_downtimeout(*sema_id, (long)timeout);
    return ret;

}

MAILBOX_EXTERN void mailbox_complete(void **sema_id)
{
    (void)osl_sem_up(*sema_id);

}

MAILBOX_EXTERN void mailbox_del_completion(void **wait)
{
    (void)osl_sem_delete(*wait);

}



MAILBOX_EXTERN void *mailbox_memcpy(void *dst, const void *src, unsigned int size)
{
    return (void *)memcpy_s(dst, size, src, size);/*lint !e516*/
}
MAILBOX_EXTERN void *mailbox_memset(void * m, int c, unsigned int size)
{
    return (void*)memset_s(m,size,c,size);/*lint !e516*/
}
/*lint -save -e715*/
extern int sysClkRateGet(void);
MAILBOX_EXTERN void mailbox_assert(unsigned int ErroNo)
{
#ifndef _DRV_LLT_
    unsigned int ticks = 0;

    ticks = (unsigned int)sysClkRateGet();
    ticks++;

    /* coverity[no_escape] */
    while (1) /*lint !e716*/
    {
        bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_HIFIMBX,"mb Assert!!");

        (void)osl_task_delay((int)ticks);

    }
#endif
}
/*lint -restore*/


/*lint -save -e18 -e64*/
MAILBOX_EXTERN int mailbox_int_context(void)
{
    return  (int)osl_int_context();
}
/*lint -restore*/


/*lint -save -e685 -e568*/
MAILBOX_EXTERN int mailbox_scene_delay(unsigned int scene_id,  int *try_times)
{
    unsigned int go_on = MAILBOX_FALSE;
    unsigned int delay_ms = 0;
    unsigned int ticks = 0;

    switch (scene_id) {
        case MAILBOX_DELAY_SCENE_MSG_FULL:
        case MAILBOX_DELAY_SCENE_IFC_FULL:
            delay_ms = MAILBOX_VXWORKS_SEND_FULL_DELAY_MS;
            /* coverity[unsigned_compare] */
            go_on = (*try_times >= MAILBOX_VXWORKS_SEND_FULL_DELAY_TIMES) ?
                     MAILBOX_FALSE : MAILBOX_TRUE;
            break;
        default:
            break;
    }

    if (MAILBOX_TRUE == go_on) {
        ticks = (delay_ms * sysClkRateGet()) / MAILBOX_MILLISEC_PER_SECOND; /*lint !e737*/
        ticks++;

    #ifndef _DRV_LLT_ /*taskDelay()Ӱ��UT�����ʺͲ���Ч��*/
        (void)osl_task_delay((int)ticks);
    #endif
    }

    *try_times = *try_times + 1;
    return (int)go_on;
}
/*lint -restore*/

MAILBOX_EXTERN int mailbox_get_timestamp(void)
{

#ifndef _DRV_LLT_
    return (long)mdrv_timer_get_normal_timestamp();
#else
    return 0;
#endif
}

#if 0
#ifndef _DRV_LLT_
IFC_GEN_EXEC3(read_efuse,
			  IFC_INCNT, unsigned int, group, 0,
			  IFC_OUTVAR, unsigned int*, buf, 0,
			  IFC_INCNT, unsigned int, len, 0)

#else
extern int ife_read_efuse(unsigned int group, unsigned int *buf, unsigned int len);
#endif
#endif

void mailbox_usr_init(void)
{
//    MAILBOX_IFC_REG(MAILBOX_IFC_ACPU_TO_CCPU_READ_EFUSE, read_efuse);
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif

