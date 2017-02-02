

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/fdtable.h>
#include <linux/version.h>

#include <asm/uaccess.h>

#include "../include/srecorder_allps_info.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"


#if defined(CONFIG_DUMP_ALLPS_INFO)

/*----local macroes------------------------------------------------------------------*/

/*�ú궨���ʾ��ӡռ���ڴ����Ľ��̵�����*/
#define TOP_RSS_NUM 20


/*----local prototypes----------------------------------------------------------------*/

typedef struct srecorder_mem_stat
{
    struct task_struct *p;
    unsigned long total_vm;
    unsigned long task_rss_size;
} srecorder_mem_stat_t;


/*----local variables------------------------------------------------------------------*/

static const char *s_process_state[] = 
{
    "R (running)",        /*   0 */
    "S (sleeping)",       /*   1 */
    "D (disk sleep)",     /*   2 */
    "T (stopped)",        /*   4 */
    "t (tracing stop)",   /*   8 */
    "Z (zombie)",         /*  16 */
    "X (dead)",           /*  32 */
    "x (dead)",           /*  64 */
    "K (wakekill)",       /* 128 */
    "W (waking)",         /* 256 */
};


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

static void srecorder_set_mem_state(srecorder_mem_stat_t *mem_state, struct task_struct *ptask);
static void srecorder_write_allps_header(srecorder_reserved_mem_info_t *pmem_info);
static void srecorder_show_topmem_tasks(char *pbuf, int task_max_count);
static void srecorder_show_single_taskinfo(srecorder_reserved_mem_info_t *pmem_info, 
    struct task_struct *ptask, unsigned int mask);
static void srecorder_show_all_taskinfo(srecorder_reserved_mem_info_t *pmem_info, unsigned int mask);
static int srecorder_count_open_files(struct fdtable *fdt);
static inline const char *srecorder_get_task_state(struct task_struct *ptsk);


/*----function definitions--------------------------------------------------------------*/

/**
    @function:static void srecorder_show_all_taskinfo(srecorder_reserved_mem_info_for_log_t *pmem_info, unsigned int mask)
    @brief: ��ӡ���н��̵���Ϣ

    @param: pmem_info SRecorder���ڴ���Ϣ
    @param: mask ������������ӡ��Щ��Ϣ 
    
    @return: none

    @note: 
*/
static void srecorder_show_all_taskinfo(srecorder_reserved_mem_info_t *pmem_info, unsigned int mask)
{
    struct task_struct *pcur = NULL;

    if (read_trylock(&tasklist_lock))
    {
        for_each_process(pcur)
        {
            if (spin_trylock(&(pcur->alloc_lock)))
            {
                srecorder_show_single_taskinfo(pmem_info, pcur, 0); /*Ŀǰû��ʹ�õ���������-mask*/
                spin_unlock(&(pcur->alloc_lock));
            }
        }

        read_unlock(&tasklist_lock);
    }
}


/**
    @function: static int srecorder_count_open_files(struct fdtable *fdt)
    @brief: ����fdtable�а����Ĵ��ļ���Ŀ

    @param: fdt  
    
    @return: none

    @note: 
*/
static int srecorder_count_open_files(struct fdtable *fdt)
{
    int size = 0;
    int i;

    if (NULL == fdt)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return 0;
    }

    size = fdt->max_fds;
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 4, 0))
    /* Find the last open fd */
    for (i = size / (8 * sizeof(long)); i > 0; ) /*8bit*/ 
    {
        if (fdt->open_fds->fds_bits[--i])
        {
            break;
        }
    }
    
    i = (i + 1) * 8 * sizeof(long); /*8bit*/ 
#else
    /* Find the last open fd */
    for (i = size / BITS_PER_LONG; i > 0; )
    {
        if (fdt->open_fds[--i])
        {
            break;
        }
    }
    
    i = (i + 1) * BITS_PER_LONG;
#endif
 
    return i;
}


/**
    @function: static inline const char *srecorder_get_task_state(struct task_struct *tsk)
    @brief: ��ȡ���̵�״̬

    @param: ptsk 
    
    @return: none

    @note: 
*/
static inline const char *srecorder_get_task_state(struct task_struct *ptsk)
{
    unsigned int state = (ptsk->state & TASK_REPORT) | ptsk->exit_state;
    const char * const *p = &s_process_state[0];

    while (0 != state) 
    {
        p++;
        state >>= 1;
    }
    
    return *p;
}


/**
    @function: static void srecorder_show_single_taskinfo(srecorder_reserved_mem_info_for_log_t *pmem_info, 
        struct task_struct *ptask, unsigned int mask)
    @brief: ��ӡ�������̵���Ϣ

    @param: pbuf �洢��ӡ��Ϣ
    @param: ptask 
    @param: mask ������������ӡ��Щ��Ϣ 
    
    @return: none

    @note: 
*/
static void srecorder_show_single_taskinfo(srecorder_reserved_mem_info_t *pmem_info, 
    struct task_struct *ptask, unsigned int mask)
{
    int bytes_read = 0;
    int open_files = 0;
    struct fdtable *old_fdt = NULL;

    if (NULL == ptask)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }

    if (NULL != ptask->files)
    {
        if (spin_trylock(&ptask->files->file_lock))
        {
            old_fdt = files_fdtable(ptask->files);
            open_files = srecorder_count_open_files(old_fdt);
            spin_unlock(&ptask->files->file_lock);
        }
    }
    else
    {
        open_files = 0;
    }
    
    /*"pid ppid tgid cpuid state vmm rss files name"*/
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%5d %6d %6d %d %s %8lu KB %8lu KB %d %s\n",  
        ptask->pid, 
        ptask->parent->pid, 
        ptask->tgid, 
        task_cpu(ptask), 
        srecorder_get_task_state(ptask),
        (NULL == ptask->mm) ? (0) : (K(ptask->mm->total_vm)), 
        (NULL == ptask->mm) ? (0) : (K(get_mm_rss(ptask->mm))),
        open_files, 
        ptask->comm);

    srecorder_renew_meminfo(pmem_info, bytes_read);
}


/**
    @function:static void srecorder_set_mem_state(srecorder_mem_stat_t *mem_state, struct task_struct *ptask)
    @brief: �ѽ��̵���Ϣ����mem_state

    @param: mem_state 
    @param: ptask 
    
    @return: none

    @note: 
*/
static void srecorder_set_mem_state(srecorder_mem_stat_t *mem_state, struct task_struct *ptask)
{
    if ((NULL == mem_state) || (NULL == ptask))
    {
        SRECORDER_PRINTK(KERN_ERR "srecorder: parameter mem_state or ptask is NULL.\n");
        return;
    }

    if (NULL == ptask->mm)
    {
        SRECORDER_PRINTK(KERN_ERR "srecorder: src->mm is NULL.\n");
        return;
    }

    mem_state->p = ptask;
    mem_state->total_vm = ptask->mm->total_vm;
    mem_state->task_rss_size = (NULL == ptask->mm) ? (0) : get_mm_rss(ptask->mm);
}


/**
    @function: static void srecorder_show_topmem_tasks(char *pbuf, int task_max_count)
    @brief: ��ӡ��������, ��ӡռ���ڴ�����ǰ20�����̵��ڴ�ռ�����

    @param: pbuf �洢��ӡ��Ϣ
    @param: task_max_count Ҫ��ӡ�Ľ��̵�����
    
    @return: none

    @note: 
*/
static void srecorder_show_topmem_tasks(char *pbuf, int task_max_count)
{
    struct task_struct *pcur = NULL;
    srecorder_mem_stat_t top_rss[TOP_RSS_NUM];  
    unsigned long cur_task_rss = 0;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int total_process = 0;

    if (unlikely(NULL == pbuf))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param or just for test!\n", __FILE__, __LINE__);
        return;
    }
    
    memset((void *)top_rss, 0, sizeof(top_rss));

    if (read_trylock(&tasklist_lock))
    {
        /*
       * ���ò������򷨶�pTop->mm->rss�Ӵ�С����. ȡǰ20������ֵ.
       */
        for_each_process(pcur)
        {
            /*
          * total_vm and rss sizes do not exist for tasks with a
          * detached mm so there's no need to report them.
          */
            total_process++;

            if (spin_trylock(&(pcur->alloc_lock)))
            {
                if (NULL == pcur->mm)
                {
                    spin_unlock(&(pcur->alloc_lock));
                    continue;
                }

                cur_task_rss = (NULL == pcur->mm) ? (0) : get_mm_rss(pcur->mm);

                for (i = 0; i < TOP_RSS_NUM; i++)
                {
                    if (NULL == top_rss[i].p)
                    {
                        srecorder_set_mem_state(&top_rss[i], pcur);
                        break;
                    }

                    if (cur_task_rss >= top_rss[i].task_rss_size)
                    {
                        for (j = TOP_RSS_NUM - 1;  j > i; j--)
                        {
                            top_rss[j] = top_rss[j - 1];  /* �ṹ��ֱ�Ӹ�ֵ */
                        }  

                        /* ���������ڴ�����task������ǰ�� */
                        srecorder_set_mem_state(&top_rss[i], pcur);
                        break;     
                    }      
                }
                spin_unlock(&(pcur->alloc_lock));
            }
        }

        /*
       * ��ӡǰ20���ڴ�ռ������task�ڴ�ʹ�����
       */
        SRECORDER_PRINTK("total process: %d\n[ pid ]    total_vm           rss     name\n", total_process);  
        for (i = 0; i < TOP_RSS_NUM; i++)
        {
            if (NULL == top_rss[i].p)
            {
                SRECORDER_PRINTK(KERN_WARNING "srecorder: smart_task[%d]:%lu maybe NULL.\n", i, top_rss[i].task_rss_size);
                SRECORDER_PRINTK("NULL\n"); 
                continue;
            }

            if (spin_trylock(&(top_rss[i].p->alloc_lock)))
            {
                /* �������ڴ���tasklist_lock�ı���֮�У����Բ��õ���topRss[i].pΪ�� */
                SRECORDER_PRINTK("[%5d]  %8lu KB  %8lu KB  %s\n",
                    top_rss[i].p->pid, 
                    K(top_rss[i].total_vm), 
                    K(top_rss[i].task_rss_size), 
                    top_rss[i].p->comm);        
                spin_unlock(&(top_rss[i].p->alloc_lock));
            }
        } 
        
        read_unlock(&tasklist_lock);
    }
}


/**
    @function: static void srecorder_write_allps_header(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��д������Ϣ��ͷ��

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: none

    @note: 
*/
static void srecorder_write_allps_header(srecorder_reserved_mem_info_t *pmem_info)
{
    int bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "%s", "pid    ppid    tgid  cpuid  state        vmm         rss     files    name\n");

    srecorder_renew_meminfo(pmem_info, bytes_read);
}


/**
    @function: int srecorder_get_allps_info(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡ����ʱ���н��̵���Ϣ

    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_allps_info(srecorder_reserved_mem_info_t *pmem_info)
{
    char *pbuf = NULL;
    psrecorder_info_header_t pinfo_header = NULL;
    
    if (unlikely(NULL == pmem_info))
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    if (srecorder_log_has_been_dumped(ALL_PS_INFO_BIT4) || pmem_info->dump_modem_crash_log_only)/* [false alarm]:there is pmem_info protect before  */
    {
        SRECORDER_PRINTK("all ps info have been dumped successfully!\n");
        return -1;
    }
    
    if (0 != srecorder_write_info_header(pmem_info, ALL_PS_INFO_BIT4, &pinfo_header))
    {
        return -1;
    }
    
    pbuf = pmem_info->start_addr + pmem_info->bytes_read;
    srecorder_write_allps_header(pmem_info);
    srecorder_show_all_taskinfo(pmem_info, 0);
    srecorder_show_topmem_tasks(NULL, 0);

    srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
    
    return 0;
}


/**
    @function: int srecorder_init_allps_info(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��allps infoģ��

    @param: pinit_params ģ���ʼ������
        
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_allps_info(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(ALL_PS_INFO_BIT4);
    
    return 0;
}


/**
    @function: void srecorder_exit_allps_info(void)
    @brief: �˳�allps infoģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_allps_info(void)
{
    srecorder_set_log_dumped_bit(ALL_PS_INFO_BIT4);
}
#else
int srecorder_get_allps_info(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_allps_info(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_allps_info(void)
{
    return;
}
#endif

