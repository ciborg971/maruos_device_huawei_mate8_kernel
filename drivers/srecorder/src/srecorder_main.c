

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/file.h>
#include <linux/stat.h>
#include <linux/spinlock.h>
#include <linux/notifier.h>
#include <linux/kprobes.h>
#include <linux/reboot.h>
#include <linux/io.h>
#include <linux/oom.h>
#include <linux/vmalloc.h>

#include <linux/mm.h>
#include <linux/highmem.h>
#include <linux/version.h>
#include <asm/uaccess.h>
#include <linux/srecorder.h>

#include "../include/srecorder_common.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_crash_time.h"
#include "../include/srecorder_sys_info.h"
#include "../include/srecorder_dmesg.h"
#include "../include/srecorder_allcpu_stack.h"
#include "../include/srecorder_allps_info.h"
#include "../include/srecorder_current_ps_backtrace.h"
#include "../include/srecorder_slabinfo.h"
#include "../include/srecorder_memory.h"
#include "../include/srecorder_modem_log.h"
#include "../include/srecorder_snprintf.h"
#include "../include/srecorder_dev.h"


/*----local macroes------------------------------------------------------------------*/

//#define CRASH_CAUSED_BY_OOPS ("oops ")
//#define CRASH_CAUSED_BY_OOM ("oom ")

#if defined(CONFIG_DUMP_MODEM_LOG)
#define CRASH_CAUSED_BY_MODEM "modemcrash "
#endif
#define CRASH_CAUSED_BY_APANIC "apanic "

#if defined(CONFIG_DUMP_MODEM_LOG)
#define MODEM_NOTIFIER_START_RESET 0x1 /* ���Ҫ���ݸ�ͨmodem�Ĵ��뼰ʱ�޸� */
#endif

/*----local prototypes----------------------------------------------------------------*/

typedef int (*atomic_notifier_chain_unregister_func)(struct atomic_notifier_head *nh, struct notifier_block *n);
typedef int (*atomic_notifier_chain_register_func)(struct atomic_notifier_head *nh, struct notifier_block *n);
typedef int (*register_jprobe_func)(struct jprobe *jp);
typedef void (*unregister_jprobe_func)(struct jprobe *jp);
typedef void (*jprobe_return_func)(void);
typedef int (*register_oom_notifier_func)(struct notifier_block *nb);
typedef int (*unregister_oom_notifier_func)(struct notifier_block *nb);

typedef struct
{
    char *module_name;
    int (*init_module)(srecorder_module_init_params_t *pinit_params);
    int (*get_log)(srecorder_reserved_mem_info_t *pmem_info);
    void (*exit_module)(void);
} srecorder_module_operations;

typedef struct
{
    srecorder_info_type_e type;
    srecorder_module_operations module_operation;
} srecorder_log_dump_module_operations;


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
static int srecorder_panic_notifier_handler(struct notifier_block *this, unsigned long event, void *panic_reason);
#endif

static int srecorder_oom_notifier_handler(struct notifier_block *this, unsigned long event, void *unused);

#if DUMP_REBOOT_LOG
static inline void srecorder_reboot_handler(void);
#ifdef CONFIG_KPROBES
static void srecorder_jkernel_restart(char *cmd);
static void srecorder_jemergency_restart(void);
#else
static int srecorder_reboot_notifier_handler(struct notifier_block *this, unsigned long code, void *reboot_reason);
static int srecorder_emergency_reboot_notifier_handler(struct notifier_block *this, unsigned long code, void *reboot_reason);
#endif
#endif

#if defined(CONFIG_DUMP_MODEM_LOG)
static inline void srecorder_modem_reset_handler(bool do_delay, void *cmd);
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
static int srecorder_modem_fiq_notifier_handler(struct notifier_block *this, unsigned long code, void *cmd);
#endif

#ifdef CONFIG_KPROBES
static void srecorder_jmodem_queue_start_reset_notify(void);
#else
static int srecorder_modem_notifier_handler(struct notifier_block *this, unsigned long code, void *cmd);
#endif
#endif

static int srecorder_init_modules(srecorder_module_init_params_t *pinit_params);

#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
static void srecorder_reboot_machine(void);
#endif

static void srecorder_dump_log(char *reason);
/* ɾ�� */

static unsigned long srecorder_convert_version_string2num(char *pversion);





/*----global function prototypes---------------------------------------------------------*/

#if defined(CONFIG_DUMP_MODEM_LOG)
extern int modem_register_notifier(struct notifier_block *nb);
extern int modem_unregister_notifier(struct notifier_block *nb);
#endif

extern bool srecorder_reserve_special_mem_successfully(void);


/*----local variables------------------------------------------------------------------*/

#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
static struct notifier_block s_panic_notifier_block = 
{
    .notifier_call = srecorder_panic_notifier_handler, 
};
#endif

/* ɾ�� */

static struct notifier_block s_oom_notifier_block = 
{
    .notifier_call = srecorder_oom_notifier_handler, 
};
#if defined(CONFIG_DUMP_MODEM_LOG)
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
static struct notifier_block s_modem_fiq_notifier_block =
{
    .notifier_call = srecorder_modem_fiq_notifier_handler,
};
#endif

#ifdef CONFIG_KPROBES
static struct jprobe s_srecorder_jmodem_queue_start_reset_notify = 
{
    .entry = srecorder_jmodem_queue_start_reset_notify,
    .kp = 
    {
        .symbol_name = "modem_queue_start_reset_notify", 
    },
};
#else
static struct notifier_block s_modem_notifier_block =
{
    .notifier_call = srecorder_modem_notifier_handler,
};
#endif
#endif

#if DUMP_REBOOT_LOG
#ifdef CONFIG_KPROBES
static struct jprobe s_srecorder_jkernel_restart = 
{
    .entry = srecorder_jkernel_restart,
    .kp = 
    {
        .symbol_name = "kernel_restart", 
    },
};

static struct jprobe s_srecorder_jemergency_restart = 
{
    .entry = srecorder_jemergency_restart,
    .kp = 
    {
        .symbol_name = "emergency_restart", 
    },
};
#else
static struct notifier_block s_reboot_notifier_block = 
{
    .notifier_call = srecorder_reboot_notifier_handler, 
};

static struct notifier_block s_emergency_reboot_notifier_block = 
{
    .notifier_call = srecorder_emergency_reboot_notifier_handler, 
};
#endif
#endif

static DEFINE_SPINLOCK(s_srecorder_dump_log_lock);

/*SRecorder�����ڴ����������ṹ���ڱ�����Ϣ��ʱ��Ҫ�õ���*/
static srecorder_reserved_mem_info_t s_srecorder_reserved_mem_info;

static srecorder_module_init_params_t s_srecorder_module_init_params;

/* static char *s_crash_reason = NULL; */
/*�趨SRecorderģ����յĲ���*/

#if 0
/*SRecorderԤ�����ڴ�Ĵ�С*/
static srec_reserved_mem_t pmsize = 0x0;
module_param(pmsize, ulong, S_IRUSR);

/*SRecorderԤ�����ڴ����ʼ��ַ*/
static srec_reserved_mem_t pmstart = 0x0;
module_param(pmstart, ulong, S_IRUSR);

/*�ڴ��д��ʽ */
static unsigned long use_io_memory = 1; /* 1 - use io memory��0 - use normal system ram */
module_param(use_io_memory, ulong, S_IRUSR);
#else
/*
* params[0] - SRecorderԤ�����ڴ����ʼ��ַ
* params[1] - SRecorderԤ�����ڴ�Ĵ�С
* params[2] - �ڴ��д��ʽ, 1 - use io memory��0 - use normal system ram
*/
static unsigned long params[3] = {0x0, 0x0, 0x0};
/*lint -e665 */
module_param_array(params, ulong, NULL, 0444);
/*lint +e665 */
MODULE_PARM_DESC(params, "SRecorder Install Parameters");
#endif

/*�ж�SRecorder�����ڴ����Ƿ��Ѿ�ӳ�����*/
static bool s_srecorder_log_info_saved = false;

static srecorder_module_operations s_srecorder_common_operations[] = 
{
    /*==================================================================*/
    /*                          ����ģ�� begin                          */
    /*==================================================================*/
    /* ��ģ��ĳ�ʼ��������������ģ�� */
    {"srecorder_init_kernel_symbols", srecorder_init_kernel_symbols, NULL, NULL}, 

    /* ��ģ��ĳ�ʼ��������������ģ�� */
    {"srecorder_init_common", srecorder_init_common, NULL, srecorder_exit_common},
    {"srecorder_init_snprintf", srecorder_init_snprintf, NULL, srecorder_exit_snprintf}, /* ������io�ڴ� */
    {"srecorder_init_memory", srecorder_init_memory, NULL, srecorder_exit_memory}, /* �����ڷ�io�ڴ� */
    {"srecorder_init_dev", srecorder_init_dev, NULL, srecorder_exit_dev}, /* �����ڷ�io�ڴ� */
    /*==================================================================*/
    /*                          ����ģ�� end                            */
    /*==================================================================*/
};

static srecorder_log_dump_module_operations s_srecorder_log_operations[] = 
{
    /*==================================================================*/
    /*                      ϵͳ����ʱ���ԭ�� begin                    */
    /*==================================================================*/
    /*�����crash time������ǰ�棬dmesg�������allcpu stack���ں��棬����������˳������ν*/
    {
        .type = CRASH_REASON_TIME_BIT0,
        .module_operation = {"crash reason and time", srecorder_init_crash_time, srecorder_get_crash_time, srecorder_exit_crash_time}
    },
    /*==================================================================*/
    /*                      ϵͳ����ʱ���ԭ�� end                      */
    /*==================================================================*/


    /*==================================================================*/
    /*                         Linux������־ begin                      */
    /*==================================================================*/
    {
        .type = DMESG_BIT2,
        .module_operation = {"dmesg", srecorder_init_dmesg, srecorder_get_dmesg, srecorder_exit_dmesg} /* dump dmesg in boot stage */
    }, 
    {
        .type = CURRENT_PS_BACKTRACE_BIT5,
        .module_operation = {"current ps backtrace", srecorder_init_current_ps_backtrace, 
            srecorder_get_current_ps_backtrace, srecorder_exit_current_ps_backtrace}
    },
    {
        .type = ALL_PS_INFO_BIT4,
        .module_operation = {"allps info", srecorder_init_allps_info, srecorder_get_allps_info, srecorder_exit_allps_info}
    }, 
    {
        .type = ALL_CPU_STACK_BIT3,
        .module_operation = {"allcpu stack", srecorder_init_allcpu_stack, srecorder_get_allcpu_stack, srecorder_exit_allcpu_stack}
    }, 
    {
        .type = SYS_INFO_BIT1,
        .module_operation = {"sysinfo", srecorder_init_sys_info, srecorder_get_sys_info, srecorder_exit_sys_info}
    }, 
    {
        .type = SLABINFO_BIT6,
        .module_operation = {"slabinfo", srecorder_init_slabinfo, srecorder_get_slabinfo, srecorder_exit_slabinfo}
    }, 
    
    /*==================================================================*/
    /*                         Linux������־ end                        */
    /*==================================================================*/


    /*==================================================================*/
    /*                         modem������Ϣ end                        */
    /*==================================================================*/
    {
        .type = MODEM_ERR_BIT7,
        .module_operation = {"modem err", srecorder_init_modem_log, srecorder_get_modem_log, srecorder_exit_modem_log}
    },
    {
        .type = MODEM_ERR_F3_BIT8,
        .module_operation = {"modem err f3", srecorder_init_modem_log, srecorder_get_modem_log, srecorder_exit_modem_log}
    }
    /*==================================================================*/
    /*                         modem������Ϣ end                        */
    /*==================================================================*/
};

static DEFINE_SPINLOCK(s_srecorder_write_header_lock);


/*----function definitions--------------------------------------------------------------*/

#ifdef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
/**
    @function: bool get_srecorder_log_buf(char *panic_reason, char **pbuf, unsigned long *plog_len)
    @brief: get SRecorder's valid log start addres and its length

    @param: panic_reason crash reason.
    @param: pbuf valid log buffer's start address.
    @param: plog_len save valid log length
    
    @return: true - successfully, false - failed

    @note: 
*/
bool get_srecorder_log_buf(char *panic_reason, char **pbuf, unsigned long *plog_len)
{
    if (unlikely(NULL == pbuf || NULL == plog_len))
    {
        SRECORDER_PRINTK("%s - %d - %s, invalid parameters!\n", __FILE__, __LINE__, __FUNCTION__);
        return false;
    }

    if (spin_trylock(&s_srecorder_reserved_mem_info.lock))
    {
        s_srecorder_reserved_mem_info.crash_reason1 = CRASH_CAUSED_BY_APANIC;
        srecorder_dump_log(panic_reason);
        *pbuf = s_srecorder_reserved_mem_info.start_addr;
        *plog_len = s_srecorder_reserved_mem_info.bytes_read;
        spin_unlock(&s_srecorder_reserved_mem_info.lock);
    }
    else
    {
        return false;
    }
    
    return true;
}
#endif


/**
    @function: void srecorder_write_reserved_mem_header(bool normal_reset, 
        bool need_flush_cache, unsigned long magic_number, int valid_log_len)
    @brief: ��дSRecorder�����ڴ�ͷ����Ϣ

    @param: normal_reset ϵͳ�Ƿ񼴽���������
    @param: need_flush_cache �Ƿ���Ҫˢ�»���
    @param: magic_number ħ��
    @param: valid_log_len SRecorderץ������Ч���ݳ���
    
    @return: none

    @note:
*/
void srecorder_write_reserved_mem_header(bool normal_reset, 
    bool need_flush_cache, unsigned long magic_number, int valid_log_len)
{
    srecorder_reserved_mem_header_t *pmem_header;
    unsigned long data_len;
#ifndef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    get_srecorder_log_buf_info(&params[0], &params[1]);
#endif

    pmem_header = (srecorder_reserved_mem_header_t *)params[0];
    data_len = (unsigned long)(sizeof(srecorder_reserved_mem_header_t) 
        - sizeof(pmem_header->crc32) 
        - sizeof(pmem_header->reserved)); 
    
    /* This means SRecorder has dumped log successfully, we should not do anything in that case */
#ifndef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    if (s_srecorder_reserved_mem_info.log_has_been_dumped_previously
        || !srecorder_reserve_special_mem_successfully())
#else
    if (s_srecorder_reserved_mem_info.log_has_been_dumped_previously)
#endif
    {
        return;
    }

    if (!spin_trylock(&s_srecorder_write_header_lock))
    {
        return;
    }
    
    /* �޸ı����ڴ�ͷ��������Ϣ - ��д�汾��ħ�� */
    pmem_header->version = srecorder_convert_version_string2num(CONFIG_SRECORDER_VERSION);
    pmem_header->magic_num = magic_number;
    pmem_header->data_length = (unsigned long)valid_log_len;
    pmem_header->reset_flag = (normal_reset) ? (NORMAL_RESET) : (ABNORMAL_RESET); /* ϵͳ��������ʱ���ñ�־��0 */
    /*if (!s_srecorder_log_info_saved)*/
#ifndef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    {
        platform_special_reserved_mem_info_t *pmem_info = (platform_special_reserved_mem_info_t *)
            __va(CONFIG_KERNEL_LOAD_PHYS_OFFSET + CONFIG_SRECORDER_SPECIAL_MEM_ADDR_FROM_PHYS_OFFSET);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
        kernel_log_buf_info_t kernel_log_buf_info = {0};
        kernel_log_buf_content_header_info_t kernel_log_buf_content_header_info = {0};
#else
        unsigned long log_buf = 0x0;
        unsigned long log_end = 0x0;
        unsigned long log_buf_len = 0x0;
#endif

#if 0
        int mem_info_size = sizeof(platform_special_reserved_mem_info_t);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
        memset((void *)&kernel_log_buf_info, 0, sizeof(kernel_log_buf_info_t));
        memset((void *)&kernel_log_buf_content_header_info, 0, sizeof(kernel_log_buf_content_header_info_t));
        get_log_buf_info(&kernel_log_buf_info);
        get_log_buf_header_info(&kernel_log_buf_content_header_info);
#else
        get_log_buf_info(&log_buf, &log_end, &log_buf_len);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
        pmem_header->log_buf = __pa(*(unsigned long *)kernel_log_buf_info.log_buf);
        pmem_header->log_first_idx_phys_addr = __pa(kernel_log_buf_info.log_first_idx);
        pmem_header->log_next_idx_phys_addr = __pa(kernel_log_buf_info.log_next_idx);
        pmem_header->log_next_seq_phys_addr = __pa(kernel_log_buf_info.log_next_seq);
        pmem_header->log_buf_len = kernel_log_buf_info.log_buf_len;
        pmem_header->log_content_header_size = kernel_log_buf_content_header_info.header_len;
        pmem_header->log_need_reparsed = SRECORDER_KERNEL_LOG_NEED_BE_REPARSED;
#else
        pmem_header->log_buf = __pa(*(unsigned long *)log_buf);
        pmem_header->log_end = __pa(log_end);
        pmem_header->log_buf_len = log_buf_len;
        pmem_header->log_need_reparsed = SRECORDER_KERNEL_LOG_NEED_NOT_BE_REPARSED;
#endif

#if 0
        pmem_header->reserved_mem_size = params[1];
#endif

        /* ����SRecorder�������ַ�ʹ�С */
        memset(pmem_info, 0, sizeof(platform_special_reserved_mem_info_t));
        pmem_info->srecorder_log_buf = __pa(params[0]);
        pmem_info->srecorder_log_buf_len = params[1];
        pmem_info->srecorder_log_buf_bak= __pa(params[0]);
        pmem_info->srecorder_log_buf_len_bak= params[1];
        
#ifdef CONFIG_DUMP_LOGCAT
        (void)get_logcat_buf_info(&(pmem_info->logcat_buf_info[0]));
        SRECORDER_PRINTK("log_main: %08lx, len: %08lx\n", pmem_info->logcat_buf_info[LOGCAT_MAIN].log_buf, 
            pmem_info->logcat_buf_info[LOGCAT_MAIN].log_buf_len);
        SRECORDER_PRINTK("log_system: %08lx, len: %08lx\n", pmem_info->logcat_buf_info[LOGCAT_SYSTEM].log_buf, 
            pmem_info->logcat_buf_info[LOGCAT_SYSTEM].log_buf_len);
        SRECORDER_PRINTK("log_events: %08lx, len: %08lx\n", pmem_info->logcat_buf_info[LOGCAT_EVENTS].log_buf, 
            pmem_info->logcat_buf_info[LOGCAT_EVENTS].log_buf_len);
        SRECORDER_PRINTK("log_radio: %08lx, len: %08lx\n", pmem_info->logcat_buf_info[LOGCAT_RADIO].log_buf, 
            pmem_info->logcat_buf_info[LOGCAT_RADIO].log_buf_len);
#endif
        /* ����Linux�ں�ring buffer�������ַ�ʹ�С */
        pmem_info->crc32 = srecorder_get_crc32((unsigned char *)pmem_info, (unsigned long)
            (sizeof(platform_special_reserved_mem_info_t) - sizeof(pmem_info->crc32)));

#if 0
        srecorder_write_data_to_phys_page(CONFIG_KERNEL_LOAD_PHYS_OFFSET 
            + (KERNEL_TEXT_OFFSET - INITIAL_PAGE_TABLE_SIZE) - mem_info_size, 
            mem_info_size, (char *)&mem_info, mem_info_size);
#endif

        s_srecorder_log_info_saved = true;
    }
#endif
    pmem_header->crc32 = srecorder_get_crc32((unsigned char *)pmem_header, data_len);

    if (need_flush_cache)
    {    
        flush_cache_all();
#ifdef CONFIG_ARM
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 37))
        outer_flush_all();
#endif
#endif
    }
    
    spin_unlock(&s_srecorder_write_header_lock);
}


/**
    @function: static void srecorder_dump_log(char *reason)
    @brief: dump ϵͳ����panicʱ�����Ϣ

    @param: reason ����ԭ��
    
    @return: none

    @note:
*/
static void srecorder_dump_log(char *reason)
{
    /* ɾ��2�� */
    int i = 0;
    int array_size = 0;
#ifdef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    srecorder_reserved_mem_header_t *pmem_header;
    pmem_header = (srecorder_reserved_mem_header_t *)params[0];
#endif
    if (!srecorder_has_been_enabled())
    {
        SRECORDER_PRINTK("SRecorder hasn't been enabled, it can not dump anything!\n");
        return;
    }
    
    /* ������ħ������ֹ��־����ȫʱdumptool������������*/
    srecorder_write_reserved_mem_header(true, false, SRECORDER_MAGIC_NUM, s_srecorder_reserved_mem_info.bytes_read);
    
    /* dump ��λ��Ϣ */
    array_size = sizeof(s_srecorder_log_operations) / sizeof(s_srecorder_log_operations[0]);
    s_srecorder_reserved_mem_info.crash_reason2 = reason;  
    for (i = 0; i < array_size; i++)
    {
        if (!srecorder_dump_enable_bit_has_been_set(s_srecorder_log_operations[i].type))
        {
            SRECORDER_PRINTK("dump %s has not been enabled!\n", s_srecorder_log_operations[i].module_operation.module_name);
            continue;   
        }
        
        if (NULL != s_srecorder_log_operations[i].module_operation.get_log)
        {
            s_srecorder_log_operations[i].module_operation.get_log(&s_srecorder_reserved_mem_info);
        }

        if (NULL != s_srecorder_log_operations[i].module_operation.exit_module)
        {
            s_srecorder_log_operations[i].module_operation.exit_module();
        }
    }
    
    /* �޸ı����ڴ�ͷ��������Ϣ - ��д��Ч��Ϣ����*/
    srecorder_write_reserved_mem_header(true, true, SRECORDER_MAGIC_NUM, s_srecorder_reserved_mem_info.bytes_read);
    
    s_srecorder_reserved_mem_info.log_has_been_dumped_previously = true;
#ifdef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    memcpy_toio(s_srecorder_reserved_mem_info.start_addr_mapped_by_ioremap, 
        (void *)params[0], (size_t)(pmem_header->data_length 
        + sizeof(srecorder_reserved_mem_header_t)));
#endif
}


#if defined(CONFIG_DUMP_MODEM_LOG)
static inline void srecorder_modem_reset_handler(bool do_delay, void *cmd)
{
    if (spin_trylock(&s_srecorder_reserved_mem_info.lock))
    {
#ifdef CONFIG_PREEMPT
        /* Ensure that cond_resched() won't try to preempt anybody */
        add_preempt_count(PREEMPT_ACTIVE);
#endif
        s_srecorder_reserved_mem_info.crash_reason1 = CRASH_CAUSED_BY_MODEM;
        s_srecorder_reserved_mem_info.dump_modem_crash_log_only = true;
        s_srecorder_reserved_mem_info.do_delay_when_dump_modem_log = do_delay ? true : false;
        srecorder_dump_log(cmd);
        spin_unlock(&s_srecorder_reserved_mem_info.lock);
    }
}


#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
static int srecorder_modem_fiq_notifier_handler(struct notifier_block *this, unsigned long code, void *cmd)
{
    srecorder_modem_reset_handler(true, cmd);
    
    return 0;
}
#endif


#ifdef CONFIG_KPROBES
static void srecorder_jmodem_queue_start_reset_notify(void)
{
    srecorder_modem_reset_handler(false, NULL);
    
    jprobe_return();
}
#else
static int srecorder_modem_notifier_handler(struct notifier_block *this, unsigned long code, void *cmd)
{
    if (MODEM_NOTIFIER_START_RESET == code)
    {
        srecorder_modem_reset_handler(false, NULL);
    }

    return 0;
}
#endif
#endif

/* ɾ���˺���ȫ������ */


#if DUMP_REBOOT_LOG
static inline void srecorder_reboot_handler(void)
{
    if (spin_trylock(&s_srecorder_reserved_mem_info.lock))
    {
        srecorder_write_reserved_mem_header(true, true, INVALID_SRECORDER_MAGIC_NUM, 
            s_srecorder_reserved_mem_info.bytes_read);
        spin_unlock(&s_srecorder_reserved_mem_info.lock);
    }
}


#ifdef CONFIG_KPROBES
static void srecorder_jkernel_restart(char *cmd)
{
    srecorder_reboot_handler();
    
    jprobe_return();
}


static void srecorder_jemergency_restart(void)
{
    srecorder_reboot_handler();
    
    jprobe_return();
}
#else
static int srecorder_reboot_notifier_handler(struct notifier_block *this, unsigned long code, void *reboot_reason)
{
    srecorder_reboot_handler();
    
    return 0;
}


static int srecorder_emergency_reboot_notifier_handler(struct notifier_block *this, unsigned long code, void *reboot_reason)
{
    return srecorder_reboot_notifier_handler(this, code, reboot_reason);
}
#endif
#endif


#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
/**
    @function: static void srecorder_reboot_machine(void)
    @brief: ��SRecorder�е��õ�ϵͳ��������

    @param: none
    
    @return: none

    @note: 
*/
static void srecorder_reboot_machine(void)
{
#if LET_MODEM_OR_WATCHDOG_RESET_SYSTEM
    /* Let the modem or watchdog reset the system */
#else
    /*emergency_restart();*/
#endif
}
#endif


/**
    @function: static unsigned long srecorder_convert_version_string2num(char *pversion)
    @brief: ��ipv4��ʽ�İ汾��Ϣת��Ϊunsigned long������

    @param: pversion �汾�ַ���������1.0.0.1
    
    @return: ���ַ����汾��Ӧ������

    @note: 
*/
static unsigned long srecorder_convert_version_string2num(char *pversion)
{
    char *stop = NULL;
    char *ptr = pversion;
    unsigned long result = 0; /* ��ֵһ��Ҫ��0 */
    unsigned long temp = 0;
    
    if (NULL == pversion)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return 0;
    }

    temp = simple_strtoull(ptr, &stop, 10); /* ʮ���� */
    ptr = stop + 1;
    result |= temp;
    while ('\0' != *ptr)
    {
        temp = simple_strtoull(ptr, &stop, 10); /* ʮ���� */
        ptr = stop + 1;
        result <<= 8;
        result |= temp;
        if ('\0' == *stop)
        {
            break;
        }
    }
  
    return result;
}


/**
    @function: static int srecorder_oom_notifier_handler(struct notifier_block *this, unsigned long event, void *unused)
    @brief: oom�ص�����

    @param: this 
    @param: event ����oom���¼���һ�㴫����0
    @param: unused Ŀǰû��ʹ�ã������������Ա�����ʹ��
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
static int srecorder_oom_notifier_handler(struct notifier_block *this, unsigned long event, void *unused)
{
    /*
    * ����OOM��ʱ��ֻ�Ǽ�¼������ԭ��͵���ջ���ɣ����ǵ���CPU�����������Ҫ������
    */
    /* �ں����Ѿ����˶�oom��ȫ��ļ�¼�ʹ���SRecorderû��Ҫ�ټ�¼��Ϣ */
#if 0
    if (spin_trylock_irq(&s_srecorder_reserved_mem_info.lock))
    {
        s_srecorder_reserved_mem_info.crash_reason1 = CRASH_CAUSED_BY_OOM;
        s_srecorder_reserved_mem_info.crash_reason2 = NULL;
        srecorder_get_crash_time(&s_srecorder_reserved_mem_info);
        srecorder_get_current_ps_backtrace(&s_srecorder_reserved_mem_info);
        spin_unlock_irq(&s_srecorder_reserved_mem_info.lock);
    }
#endif

    return 0;
}



#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
/**
    @function: static int srecorder_panic_notifier_handler(struct notifier_block *this, unsigned long event, void *panic_reason)
    @brief: ϵͳpanicʱ�ص�����

    @param: this 
    @param: event ������panic�д�����0
    @param: panic_reason ����panic�ĺ�����������ԭ��
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
static int srecorder_panic_notifier_handler(struct notifier_block *this, unsigned long event, void *panic_reason)
{
    if (spin_trylock(&s_srecorder_reserved_mem_info.lock))
    {
#ifdef CONFIG_PREEMPT
        /* Ensure that cond_resched() won't try to preempt anybody */
        add_preempt_count(PREEMPT_ACTIVE);
#endif
        s_srecorder_reserved_mem_info.crash_reason1 = CRASH_CAUSED_BY_APANIC;
        srecorder_dump_log((char *)panic_reason);
        spin_unlock(&s_srecorder_reserved_mem_info.lock);
        srecorder_reboot_machine();
    }
    
    return 0;
}
#endif


/**
    @function: srecorder_reserved_mem_info_t* srecorder_get_reserved_mem_info(void)
    @brief: ��ȡSRecorder�����ڴ���Ϣ

    @param: none
    
    @return: SRecorder�����ڴ���Ϣ

    @note: 
*/
srecorder_reserved_mem_info_t* srecorder_get_reserved_mem_info(void)
{
    return &s_srecorder_reserved_mem_info;
}


/**
    @function: unsigned long srecorder_get_reserved_mem_addr(void)
    @brief: ��ȡSRecorder�����ڴ���ʼ��ַ

    @param: none
    
    @return: SRecorder�����ڴ���ʼ��ַ

    @note: 
*/
unsigned long srecorder_get_reserved_mem_addr(void)
{
    return (unsigned long)params[0];
}


/**
    @function: static int srecorder_init_modules(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ������ģ��
    
    @param: none
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
static int srecorder_init_modules(srecorder_module_init_params_t *pinit_params)
{
    int i = 0;
    int array_size = sizeof(s_srecorder_common_operations) / sizeof(s_srecorder_common_operations[0]);

    /* ����ģ���ʼ�� */
    for (i = 0; i < array_size; i++)
    {
        if ((NULL == s_srecorder_common_operations[i].init_module)
            || (0 != s_srecorder_common_operations[i].init_module(pinit_params)))
        {
            PRINT_INFO(("%s failed!\n", s_srecorder_common_operations[i].module_name), DEBUG_SRECORDER);
            goto __error_exit;
        }
    }
    
    /* ����ģ���ʼ�� */
    array_size = sizeof(s_srecorder_log_operations) / sizeof(s_srecorder_log_operations[0]);
    for (i = 0; i < array_size; i++)
    {
        if ((NULL == s_srecorder_log_operations[i].module_operation.init_module)
            || (0 != s_srecorder_log_operations[i].module_operation.init_module(pinit_params)))
        {
            PRINT_INFO(("%s failed!\n", s_srecorder_log_operations[i].module_operation.module_name), DEBUG_SRECORDER);
            goto __error_exit;
        }
    }

    return 0;
    
__error_exit:
    return -1;
}

/**
  @function: char *alloc_buf_for_srecorder(unsigned long buf_len)
  @brief: allocate memory for SRecorder by vmalloc

  @param: size memory size of the buffer to be allocated

  @return: the start address of the buffer allocated

  @note: 
 */
char *alloc_buf_for_srecorder(unsigned long size)
{
    return vmalloc(size);
}

static int __init srecorder_init(void)
{
    int ret = -1;

#ifdef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    char *start_addr = NULL;
    char *temp_buf = NULL;
#endif

/* ɾ������ */
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    bool register_panic_notifier_block_successfully = false;
#endif

    bool register_oom_notifier_successfully = false;

#if defined(CONFIG_DUMP_MODEM_LOG)
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
    bool register_modem_fiq_notifier_successfully = false;
#endif

#ifdef CONFIG_KPROBES
    bool register_jmodem_queue_start_reset_notify_successfully = false;
#else
    bool register_modem_notifier_successfully = false;
#endif
#endif

#if DUMP_REBOOT_LOG
#ifdef CONFIG_KPROBES
    bool register_jkernel_restart_successfully = false;
    bool register_jemergency_restart_successfully = false;
#else
    bool register_reboot_notifier_successfully = false;
    bool register_emergency_reboot_notifier_successfully = false;
#endif
#endif

#ifdef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
    kernel_log_buf_info_t kernel_log_buf_info = {0};
#else
    unsigned long log_buf = 0x0;
    unsigned long log_end = 0x0;
    unsigned long log_buf_len = 0x0;
#endif
    char  *temp_buf_addr_for_srecorder = NULL;
    unsigned long temp_buf_size_for_srecorder = CONFIG_SRECORDER_LOG_BUF_LEN;
#endif
    int i = 0;

    /* Enable SRecorder when startup */
    srecorder_enable();
    
    /* ��ȡSRecorder�ı����ڴ��ַ�ʹ�С */
    get_srecorder_log_buf_info(&params[0], &params[1]);

#ifndef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
#ifdef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 5, 0))
    memset((void *)&kernel_log_buf_info, 0, sizeof(kernel_log_buf_info_t));
    get_log_buf_info(&kernel_log_buf_info);
    temp_buf_size_for_srecorder = kernel_log_buf_info.log_buf_len + params[1];
#else
    get_log_buf_info(&log_buf, &log_end, &log_buf_len);
    temp_buf_size_for_srecorder = log_buf_len + params[1];
#endif
    temp_buf_addr_for_srecorder = alloc_buf_for_srecorder(temp_buf_size_for_srecorder);
    if (NULL == temp_buf_addr_for_srecorder)
    {
        SRECORDER_PRINTK("There's no sufficient memory that can be allocated for SRecorder!\n");
        return -ENOMEM;
    }
#endif
    SRECORDER_PRINTK("Install SRecorder\n@@@@ SRecorder's buffer addr = 0x%08lx size = 0x%08lx\n", params[0], params[1]);
#endif

    /* ��ʼ��s_reserved_mem_info���ýṹ�屣��SRecorder�����ڴ����ϸ��Ϣ */
    memset(&s_srecorder_reserved_mem_info, 0, sizeof(srecorder_reserved_mem_info_t));
    memset((char *)params[0], 0, sizeof(srecorder_reserved_mem_header_t));

#ifndef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
#ifdef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    s_srecorder_reserved_mem_info.mem_size = temp_buf_size_for_srecorder - sizeof(srecorder_reserved_mem_header_t);
    s_srecorder_reserved_mem_info.bytes_left = s_srecorder_reserved_mem_info.mem_size;
    s_srecorder_reserved_mem_info.start_addr = temp_buf_addr_for_srecorder + sizeof(srecorder_reserved_mem_header_t);
#else
    s_srecorder_reserved_mem_info.mem_size = params[1] - sizeof(srecorder_reserved_mem_header_t);
    s_srecorder_reserved_mem_info.bytes_left = s_srecorder_reserved_mem_info.mem_size;
    s_srecorder_reserved_mem_info.start_addr = (char *)(params[0] + sizeof(srecorder_reserved_mem_header_t));
#endif
#else
    s_srecorder_reserved_mem_info.mem_size = 
        (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE
        - sizeof(srecorder_reserved_mem_header_t);
    s_srecorder_reserved_mem_info.bytes_left = s_srecorder_reserved_mem_info.mem_size;
    start_addr = (char *)vmalloc((size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
    if (NULL == start_addr)
    {
        printk("File: %s Line: %d Failed to malloc memory for SRecorder!\n", __FILE__, __LINE__);
        goto __error_exit;
    }
    memset(start_addr, 0, (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);

    /* This will be freed by vfree soon */
    temp_buf = (char *)vmalloc((size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
    if (NULL == temp_buf)
    {
        printk("File: %s Line: %d Failed to malloc memory for SRecorder!\n", __FILE__, __LINE__);
        goto __error_exit;
    }
    memset(temp_buf, 0, (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
    s_srecorder_reserved_mem_info.start_addr = (char *)((long)start_addr 
        + sizeof(srecorder_reserved_mem_header_t));
    s_srecorder_reserved_mem_info.start_addr_mapped_by_ioremap = 
        (char *)ioremap_nocache((phys_addr_t)
        CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR, 
        (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
    if (NULL == s_srecorder_reserved_mem_info.start_addr_mapped_by_ioremap)
    {
        printk("IO remap addr for SRecorder failed!\n");
        goto __error_exit; 
    }
    printk("SRecorder's Reserved Mem info: add: %llx size: %llx\n", 
        (phys_addr_t)CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR, 
        (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
    memcpy_fromio(temp_buf, s_srecorder_reserved_mem_info.start_addr_mapped_by_ioremap, 
        (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
    memset_io(s_srecorder_reserved_mem_info.start_addr_mapped_by_ioremap, 
        0, (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
    params[0] = start_addr;
    params[1] = (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE;
    SRECORDER_PRINTK("Install SRecorder\n@@@@ SRecorder's buffer "
        "addr = %p size = 0x%lx\n", 
        (void *)s_srecorder_reserved_mem_info.start_addr_mapped_by_ioremap, 
        (size_t)CONFIG_SRECORDER_RESERVED_MEM_SIZE);
#endif
    s_srecorder_reserved_mem_info.lock = s_srecorder_dump_log_lock;
    s_srecorder_reserved_mem_info.log_has_been_dumped_previously = false;

    memset(&s_srecorder_module_init_params, 0, sizeof(srecorder_module_init_params_t));
#ifndef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    s_srecorder_module_init_params.srecorder_reserved_mem_start_addr = (char *)params[0];
    s_srecorder_module_init_params.srecorder_reserved_mem_size = params[1];
    s_srecorder_module_init_params.srecorder_log_temp_buf = get_srecorder_temp_buf_addr();
#else
    s_srecorder_module_init_params.srecorder_reserved_mem_start_addr = (char *)params[0];
    s_srecorder_module_init_params.srecorder_reserved_mem_size = params[1];
    s_srecorder_module_init_params.srecorder_log_temp_buf = temp_buf;
#endif
    if (NULL != s_srecorder_module_init_params.srecorder_log_temp_buf)
    {
        s_srecorder_module_init_params.srecorder_log_len = 
            ((srecorder_reserved_mem_header_t *)s_srecorder_module_init_params.srecorder_log_temp_buf)->data_length 
            + sizeof(srecorder_reserved_mem_header_t);
    }
    
    ret = srecorder_init_modules(&s_srecorder_module_init_params);
    if (0 != ret)
    {
        goto __error_exit;
    }
    
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    if (0 > atomic_notifier_chain_register(&panic_notifier_list, &s_panic_notifier_block))
    {
        PRINT_INFO(("unable to register s_panic_notifier_block!\n"), DEBUG_SRECORDER);
        goto __error_exit;
    }
    register_panic_notifier_block_successfully = true;
#endif
    
    if (0 > register_oom_notifier(&s_oom_notifier_block))
    {
        PRINT_INFO(("unable to register s_reboot_notifier_block!\n"), DEBUG_SRECORDER);
        goto __error_exit;
    }
    register_oom_notifier_successfully = true;
//ɾ������

#if DUMP_REBOOT_LOG
#ifdef CONFIG_KPROBES
    if (0 > register_jprobe(&s_srecorder_jkernel_restart))
    {
        PRINT_INFO(("unable to register jprobe for funtion [kernel_restart]!\n"), DEBUG_SRECORDER);
        goto __error_exit;
    }
    register_jkernel_restart_successfully = true;
    
    if (0 > register_jprobe(&s_srecorder_jemergency_restart))
    {
        PRINT_INFO(("unable to register jprobe for funtion [emergency_restart]!\n"), DEBUG_SRECORDER);
        goto __error_exit;
    }
    register_jemergency_restart_successfully = true;
#else
    ret = register_reboot_notifier(&s_reboot_notifier_block);
    if (0 != ret)
    {
        PRINT_INFO(("unable to register s_reboot_notifier_block\n"), DEBUG_SRECORDER);
        goto __error_exit;   
    }
    register_reboot_notifier_successfully = true;
    
    ret = register_emergency_reboot_notifier(&s_emergency_reboot_notifier_block);
    if (0 != ret)
    {
        PRINT_INFO(("unable to register s_emergency_reboot_notifier_block\n"), DEBUG_SRECORDER);
        goto __error_exit;   
    }
    register_emergency_reboot_notifier_successfully = true;
#endif
#endif

#if defined(CONFIG_DUMP_MODEM_LOG)
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
    if (0 > register_modem_fiq_notifier(&s_modem_fiq_notifier_block))
    {
        PRINT_INFO(("unable to register s_modem_fiq_notifier_block\n"), DEBUG_SRECORDER);
        goto __error_exit;
    }
    register_modem_fiq_notifier_successfully = true;
#endif

#ifdef CONFIG_KPROBES
    if (0 > register_jprobe(&s_srecorder_jmodem_queue_start_reset_notify))
    {
        PRINT_INFO(("unable to register jprobe for funtion [modem_queue_start_reset_notify]!\n"), DEBUG_SRECORDER);
        goto __error_exit;
    }
    register_jmodem_queue_start_reset_notify_successfully = true;
#else
    ret = modem_register_notifier(&s_modem_notifier_block);
    if (0 != ret)
    {
        PRINT_INFO(("unable to register s_modem_notifier_block\n"), DEBUG_SRECORDER);
        goto __error_exit;   
    }
    register_modem_notifier_successfully = true;
#endif
#endif

    /* Enable SRecorder dump all kinds of log except the "log cat" */
    for (i = 0; i < LOG_TYPE_COUNT; i++)
    {
        srecorder_set_dump_enable_bit((unsigned long)i);
    }
    srecorder_clear_dump_enable_bit(LOGCAT_BIT9);

    SRECORDER_PRINTK("^_^ SRecorder has been installed successfully!\n");
    
    return 0;
    
__error_exit:
#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    if (register_panic_notifier_block_successfully)
    {
        atomic_notifier_chain_unregister(&panic_notifier_list, &s_panic_notifier_block);
    }
#endif

    if (register_oom_notifier_successfully)
    {
        unregister_oom_notifier(&s_oom_notifier_block);
    }
//ɾ������

#if DUMP_REBOOT_LOG
#ifdef CONFIG_KPROBES
    if (register_jkernel_restart_successfully)
    {
        unregister_jprobe(&s_srecorder_jkernel_restart);
    }
    
    if (register_jemergency_restart_successfully)
    {
        unregister_jprobe(&s_srecorder_jemergency_restart);
    }
#else
    if (register_reboot_notifier_successfully)
    {
        unregister_reboot_notifier(&s_reboot_notifier_block);
    }

    if (register_emergency_reboot_notifier_successfully)
    {
        unregister_emergency_reboot_notifier(&s_emergency_reboot_notifier_block);
    }
#endif
#endif

#if defined(CONFIG_DUMP_MODEM_LOG)
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
    if (register_modem_fiq_notifier_successfully)
    {
        unregister_modem_fiq_notifier(&s_modem_fiq_notifier_block);
    }
#endif

#ifdef CONFIG_KPROBES
    if (register_jmodem_queue_start_reset_notify_successfully)
    {
        unregister_jprobe(&s_srecorder_jmodem_queue_start_reset_notify);
    }
#else
    if (register_modem_notifier_successfully)
    {
        modem_unregister_notifier(&s_modem_notifier_block);
    }
#endif
#endif
#ifdef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    if (NULL != start_addr)
    {
        vfree(start_addr);
    }

    if (NULL != temp_buf)
    {
        vfree(temp_buf);
    }
#endif
    return -1;
}


static void __exit srecorder_exit(void)
{
    int i = 0;
    int array_size = sizeof(s_srecorder_common_operations) / sizeof(s_srecorder_common_operations[0]);
    
    PRINT_INFO(("Uninstall SRecorder!\n"), DEBUG_SRECORDER);

#ifndef CONFIG_SRECORDER_DUMP_LOG_TO_STORAGECARD
    atomic_notifier_chain_unregister(&panic_notifier_list, &s_panic_notifier_block);
#endif

    unregister_oom_notifier(&s_oom_notifier_block);
    /* ɾ������ */
//ɾ������

#if DUMP_REBOOT_LOG
#ifdef CONFIG_KPROBES
    unregister_jprobe(&s_srecorder_jkernel_restart);
    unregister_jprobe(&s_srecorder_jemergency_restart);
#else
    unregister_reboot_notifier(&s_reboot_notifier_block);
    unregister_emergency_reboot_notifier(&s_emergency_reboot_notifier_block);
#endif
#endif

#if defined(CONFIG_DUMP_MODEM_LOG)
#if defined(CONFIG_DUMP_MODEM_LOG_BY_FIQ)
    unregister_modem_fiq_notifier(&s_modem_fiq_notifier_block);
#endif

#ifdef CONFIG_KPROBES
    unregister_jprobe(&s_srecorder_jmodem_queue_start_reset_notify);
#else
    modem_unregister_notifier(&s_modem_notifier_block);
#endif
#endif

    /* �˳�ģ�� */
    for (i = 0; i < array_size; i++)
    {
        if (NULL != s_srecorder_common_operations[i].exit_module)
        {
            s_srecorder_common_operations[i].exit_module();
        }
    }

    array_size = sizeof(s_srecorder_log_operations) / sizeof(s_srecorder_log_operations[0]);
    for (i = 0; i < array_size; i++)
    {
        if (NULL != s_srecorder_log_operations[i].module_operation.exit_module)
        {
            s_srecorder_log_operations[i].module_operation.exit_module();
        }
    }
}

module_init(srecorder_init);
module_exit(srecorder_exit);
MODULE_LICENSE(LICENSE_DESCRIPTION);

