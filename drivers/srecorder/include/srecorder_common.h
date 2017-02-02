

#ifndef SRECORDER_COMMON_H
#define SRECORDER_COMMON_H


/*----includes-----------------------------------------------------------------------*/

#include <linux/spinlock.h>
#include <linux/srecorder.h>


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/

/*==================================================================*/
/*                         ģ��License���� begin                    */
/*==================================================================*/
#ifndef USE_LICENSE_GPL
#define USE_LICENSE_GPL (1)
#endif

#if USE_LICENSE_GPL
#define LICENSE_DESCRIPTION "GPL"
#else
#define LICENSE_DESCRIPTION "Proprietary"
#endif
/*==================================================================*/
/*                         ģ��License���� end                      */
/*==================================================================*/


/*==================================================================*/
/*                       SRecorder���ƿ��� begin                    */
/*==================================================================*/
/* SRecorder Control Command */
#define SRECORDER_IOCTL_BASE 'S'
#define SRIOC_SET_DUMP_ENABLE_BIT _IOWR(SRECORDER_IOCTL_BASE, 0, unsigned long)
#define SRIOC_CLR_DUMP_ENABLE_BIT _IOWR(SRECORDER_IOCTL_BASE, 1, unsigned long)
#define SRIOC_SET_DUMP_ENABLE_BITS _IOWR(SRECORDER_IOCTL_BASE, 2, unsigned long)
#define SRIOC_GET_DUMP_ENABLE_BITS _IOWR(SRECORDER_IOCTL_BASE, 3, unsigned long)
#define SRIOC_ENABLE _IOWR(SRECORDER_IOCTL_BASE,  2012, unsigned long)
#define SRIOC_DISABLE _IOWR(SRECORDER_IOCTL_BASE,  2013, unsigned long)
#define SRIOC_CLEAN _IOWR(SRECORDER_IOCTL_BASE,  2014, unsigned long)
/*==================================================================*/
/*                       SRecorder���ƿ��� end                      */
/*==================================================================*/


/*==================================================================*/
/*                      ��־�����߼����ܿ��� begin                  */
/*==================================================================*/
#ifdef CONFIG_POWERCOLLAPSE
#define DUMP_REBOOT_LOG (1) /* ����ϵͳ���� */
#else
#define DUMP_REBOOT_LOG (0) /* ������ϵͳ���� */
#endif
/*==================================================================*/
/*                      ��־�����߼����ܿ��� end                    */
/*==================================================================*/


/*==================================================================*/
/*                     ��ƽ̨�����־�������� begin                 */
/*==================================================================*/
#ifdef CONFIG_ARCH_MSM
#ifndef CONFIG_DUMP_MODEM_LOG_BY_FIQ
//#define CONFIG_DUMP_MODEM_LOG_BY_FIQ
#endif

#ifndef CONFIG_DUMP_MODEM_LOG_DELAY_MAX_MS
#define CONFIG_DUMP_MODEM_LOG_DELAY_MAX_MS (10) /* ��FIQ����ʱ10ms����Ը�ͨƽ̨ */
#endif

/* ���Դ�cpufreqģ���ȡcpuʱ��Ƶ��ʧ��ʱʹ�ã�Ĭ��ֵ�����ʵ��ƽ̨���� */
#ifndef CONFIG_CPU_FREQ_DEFAULT_VALUE
#define CONFIG_CPU_FREQ_DEFAULT_VALUE (1150000000UL) /* 1.15GHz */
#endif
#endif
/*==================================================================*/
/*                     ��ƽ̨�����־�������� end                   */
/*==================================================================*/


/*==================================================================*/
/*                       ϵͳ���ƿ��� begin                         */
/*==================================================================*/
#if defined(CONFIG_ARCH_MSM)
#define LET_MODEM_OR_WATCHDOG_RESET_SYSTEM (1) /* Ϊ�˲��ı�ϵͳԭ�еĴ��������̣�����ʹ�ø����� */
#else
#define LET_MODEM_OR_WATCHDOG_RESET_SYSTEM (0) /* ���ø�����ʱ��SRecorder������־֮�����������ϵͳ */
#endif
/*==================================================================*/
/*                         ϵͳ���ƿ��� end                         */
/*==================================================================*/


/*==================================================================*/
/*                         ģ��ȫ�ֳ������� begin                   */
/*==================================================================*/
#ifndef CONFIG_SRECORDER_VERSION
#define CONFIG_SRECORDER_VERSION ("0.0.0.1") /* ����IPV4��ģʽ */
#endif

#define INVALID_KSYM_ADDR (0UL) /* ������ŵĴ����ַΪ0 */
#define DMESG_MAX_LENGTH (0x20000) /*(128 * 1024)*/ /*128KB*/
/*==================================================================*/
/*                         ģ��ȫ�ֳ������� end                     */
/*==================================================================*/


/*==================================================================*/
/*                          ���Կ��ض��� begin                      */
/*==================================================================*/
#ifdef CONFIG_DEBUG_SRECORDER
#define DEBUG_SRECORDER (CONFIG_DEBUG_SRECORDER) /* �ܵ��Կ��� */
#else
#define DEBUG_SRECORDER 1 /* �ܵ��Կ��� */
#endif

#define DEBUG_KERNEL_SYMBOLS 1           /* �����ں˷��Ŷ�ȡģ�� */
#define DEBUG_CRASH_TIME 1                   /* ����������ʱ���ȡģ�� */
#define DEBUG_SYS_INFO 1                       /* ����ϵͳ��Ϣ */
#define DEBUG_DMESG 1                            /* ����dmesg��Ϣ��ȡ */
#define DEBUG_ALLCPU_STACK 1                /* ��������CPU����ջ */
#define DEBUG_ALLPS_INFO 1                    /* �������н�����Ϣ */
#define DEBUG_CURRENT_PS_BACKTRACE 1 /* ���Ե�ǰ�������н��̵���ջ */
#define DEBUG_SLAB_INFO 1                      /* ����slab ��Ϣ */
/*==================================================================*/
/*                          ���Կ��ض��� end                        */
/*==================================================================*/


/*==================================================================*/
/*                          ��ӡ�������� begin                      */
/*==================================================================*/
#define SRECORDER_PRINTK printk

#if DEBUG_SRECORDER
#define PRINTLINE printk("%s -%d - [%s]\n", __FILE__, __LINE__, __FUNCTION__)
#define PRINT_INFO(info, condition)\
do\
{\
    if (0 != condition)\
    {\
        printk info;\
    }\
} while (0)
#else
#define PRINTLINE
#define PRINT_INFO(info, condition)
#endif
/*==================================================================*/
/*                          ��ӡ�������� end                        */
/*==================================================================*/


/*==================================================================*/
/*                         ȫ�ֺ꺯������ begin                     */
/*==================================================================*/
#define K(x) ((x) << (PAGE_SHIFT - 10)) /* �ֽ�B��KB��ת������sys info��all ps info�����õ� */
#define MAX(a, b) ((a) > (b)) ? (a) : (b)
#define MIN(a, b) ((a) > (b)) ? (b) : (a)
#define LOG_BUF_MASK(log_buf_len) ((log_buf_len) - 1)

/* log_buf_len must equal 2 ^ n ((n >= 0) && (n <= 32)) or the result may be wrong*/
#define LOG_OFFSET(len, log_buf_len) ((len) & LOG_BUF_MASK(log_buf_len))
/*==================================================================*/
/*                         ȫ�ֺ꺯������ end                       */
/*==================================================================*/


/*==================================================================*/
/*                   ���̶�ջdump�������붨�� begin                 */
/*==================================================================*/
#define SRECORDER_SHOW_VMA (1 << 0)
#define SRECORDER_SHOW_CMD (1 << 1)
#define SRECORDER_SHOW_ENV (1 << 2)
#define SRECORDER_SHOW_KSTK (1 << 3)
#define SRECORDER_SHOW_USTK (1 << 4)
#define SRECORDER_SHOW_KTRACE (1 << 5)
#define SRECORDER_SHOW_UTRACE (1 << 6)
#define SRECORDER_SHOW_ALL (SRECORDER_SHOW_VMA | SRECORDER_SHOW_CMD| SRECORDER_SHOW_ENV \
    | SRECORDER_SHOW_KSTK | SRECORDER_SHOW_USTK | SRECORDER_SHOW_KTRACE \
    | SRECORDER_SHOW_UTRACE)

#define SRECORDER_SHOW_COMMON (SRECORDER_SHOW_CMD | SRECORDER_SHOW_KSTK | SRECORDER_SHOW_USTK \
    | SRECORDER_SHOW_KTRACE | SRECORDER_SHOW_UTRACE)

#define SRECORDER_NOT_SHOW_VMA (SRECORDER_SHOW_ALL & (~SRECORDER_SHOW_VMA))
#define SRECORDER_NOT_SHOW_KSTK (SRECORDER_SHOW_ALL & (~SRECORDER_SHOW_KSTK))
#define SRECORDER_NOT_SHOW_USTK (SRECORDER_SHOW_ALL & (~SRECORDER_SHOW_USTK))
/*==================================================================*/
/*                   ���̶�ջdump�������붨�� end                   */
/*==================================================================*/


/*----export prototypes---------------------------------------------------------------*/

typedef struct __srecorder_module_init_params_t
{
    char *srecorder_reserved_mem_start_addr; /* SRecorder�����ڴ�������ʼ��ַ */
    char *srecorder_log_temp_buf; /* It is allocted by vmalloc */
    int srecorder_reserved_mem_size; /* SRecorder�����ڴ����ĳ��� */
    int srecorder_log_len;
} srecorder_module_init_params_t, *psrecorder_module_init_params_t;

typedef struct __srecorder_reserved_mem_info_for_log
{
    spinlock_t lock; /* ͬ�������±����Ĳ��� */
    char *start_addr; /* SRecorder's temp buffer to save log, allocated by vmalloc */
#ifdef CONFIG_SRECORDER_RESERVED_MEM_PHYS_ADDR
    char *start_addr_mapped_by_ioremap; /* SRecorder's reserved buffer */
#endif
    int bytes_read; /* ����SRecorder�����ڴ�dump���ֽ��� */
    int bytes_left; /* SRecorder�����ڴ���ʣ��ռ��С */
    int bytes_per_type; /* ÿ����Ϣ���ֽ�������������Ϣͷ����У������ */
    int mem_size; /* SRecorder�����ڴ����洢��Ч��Ϣ�Ĵ�С, ��������ͷ����Ϣ */
    char *crash_reason1; /* ϵͳ����panic�ĵ�һ��ԭ�� */
    char *crash_reason2; /* ϵͳ����panic�ĵڶ���ԭ�򣬱����һ��ԭ����oops�������žͷ���panic��panic���Կ����ڶ�ԭ�� */
    bool dump_modem_crash_log_only; /* �ж��Ƿ���dump modem��־ */
    bool do_delay_when_dump_modem_log; /* �ж���dump modem��־ʱ�Ƿ���Ҫ��ʱ */ 
    bool log_has_been_dumped_previously; /* ��־�Ѿ���dump */
} srecorder_reserved_mem_info_t, *psrecorder_reserved_mem_info_t;

/*srec means SRecorder*/
typedef unsigned long srec_ul32;
typedef unsigned long long srec_ul64;
typedef srec_ul32 srec_ksym_addr_t; /*�ں˷��ŵ�ַ�����ͣ�Ŀǰ��Ϊ32λ�����ݾ���ƽ̨�ı�*/
typedef srec_ul32 srec_reserved_mem_t; /*Ŀǰ������32λϵͳ��������λ����ϵͳ�ϸ���ʵ���������*/

typedef struct __srecorder_virt_zone_info_t
{
    struct page *start_page; /* ��һ����ʼҳ�� */
    char *virt_start; /* ������ʼ��ַ */
    char *ptr; /* ӳ����ʵ�ʶ�дλ�� */
    unsigned long phys_addr; /* ������ʼ��ַ */
    unsigned long size; /* Ҫӳ����ڴ泤�� */
    unsigned long page_delta; /* ������������ҳ���Ӧ��page��ֵ */
    unsigned long virt_page_count; /* ����ҳ������� */
    int mapped_size; /* �Ѿ�ӳ�������ռ䳤�� */
} srecorder_virt_zone_info_t, *psrecorder_virt_zone_info_t;


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

/**
    @function: void srecorder_enable(unsigned long bit)
    @brief: enable SRecorder

    @param: none 
    
    @return: none

    @note: 
*/
void srecorder_enable(void);


/**
    @function: void srecorder_disable(unsigned long bit)
    @brief: disable SRecorder

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_disable(void);


/**
    @function: bool srecorder_has_been_enabled(unsigned long bit)
    @brief: check if SRecorder has been enabled

    @param: bit 
    
    @return: none

    @note: 
*/
bool srecorder_has_been_enabled(void);


/**
    @function: void srecorder_set_log_dumped_bit(unsigned long bit)
    @brief: set bit to indicate that log with some type has been dumped completely

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_set_log_dumped_bit(unsigned long bit);


/**
    @function: void srecorder_clear_log_dumped_bit(unsigned long bit)
    @brief: clear some bit to indicate that log with some type has not been dumped

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_clear_log_dumped_bit(unsigned long bit);


/**
    @function: bool srecorder_log_has_been_dumped(unsigned long bit)
    @brief: check if log with some type has been dumped or not

    @param: bit 
    
    @return: a unsigned long long num

    @note: 
*/
bool srecorder_log_has_been_dumped(unsigned long bit);


/**
    @function: void srecorder_set_dump_enable_bit(unsigned long bit)
    @brief: ����λ

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_set_dump_enable_bit(unsigned long bit);


/**
    @function: void srecorder_clear_dump_enable_bit(unsigned long bit)
    @brief: ���λ

    @param: bit 
    
    @return: none

    @note: 
*/
void srecorder_clear_dump_enable_bit(unsigned long bit);


/**
    @function: bool srecorder_dump_enable_bit_has_been_set(unsigned long bit)
    @brief: ��ȡĳһλ��ֵ

    @param: bit 
    
    @return: none

    @note: 
*/
bool srecorder_dump_enable_bit_has_been_set(unsigned long bit);


/**
    @function: srecorder_reserved_mem_info_t* srecorder_get_reserved_mem_info(void)
    @brief: ��ȡSRecorder�����ڴ���Ϣ

    @param: none
    
    @return: SRecorder�����ڴ���Ϣ

    @note: 
*/
srecorder_reserved_mem_info_t* srecorder_get_reserved_mem_info(void);


/**
    @function: unsigned long srecorder_get_reserved_mem_addr(void)
    @brief: ��ȡSRecorder�����ڴ���ʼ��ַ

    @param: none
    
    @return: SRecorder�����ڴ���ʼ��ַ

    @note: 
*/
unsigned long srecorder_get_reserved_mem_addr(void);

/**
    @function: int srecorder_init_common(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��commonģ��

    @param: pinit_params ģ���ʼ������
        
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_common(srecorder_module_init_params_t *pinit_params);


/**
    @function: void srecorder_exit_common(void)
    @brief: �˳�commonģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_common(void);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_COMMON_H */

