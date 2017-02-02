

#ifndef SRECORDER_KERNEL_SYMBOLS_H
#define SRECORDER_KERNEL_SYMBOLS_H


/*----includes-----------------------------------------------------------------------*/

#include <linux/version.h>
#include "srecorder_common.h"


/*----c++ support--------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif


/*----export macroes-----------------------------------------------------------------*/


/*----export prototypes---------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----export function prototypes--------------------------------------------------------*/

#if defined(CONFIG_DUMP_SYS_INFO)
/**
    @function: srec_ksym_addr_t srecorder_get_cpu_name(void)
    @brief: ��ȡ����cpu_name�ĵ�ַ

    @param: none
    
    @return: ����cpu_name�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_cpu_name(void);


/**
    @function: srec_ksym_addr_t srecorder_get_machine_name(void)
    @brief: ��ȡ����machine_name�ĵ�ַ

    @param: none
    
    @return: ����machine_name�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_machine_name(void);


/**
    @function: srec_ksym_addr_t srecorder_get_all_bdevs(void)
    @brief: ��ȡ����all_bdevs�ĵ�ַ

    @param: none
    
    @return: ����all_bdevs�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_all_bdevs(void);


/**
    @function: srec_ksym_addr_t srecorder_get_bdev_lock(void)
    @brief: ��ȡ����bdev_lock�ĵ�ַ

    @param: none
    
    @return: ����bdev_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_bdev_lock(void);


#ifdef CONFIG_SWAP
/**
    @function: srec_ksym_addr_t srecorder_get_nr_swapfiles(void)
    @brief: ��ȡ����nr_swapfiles�ĵ�ַ

    @param: none
    
    @return: ����nr_swapfiles�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_nr_swapfiles(void);


/**
    @function: srec_ksym_addr_t srecorder_get_swap_info(void)
    @brief: ��ȡ����swap_info�ĵ�ַ

    @param: none
    
    @return: ����swap_info�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_swap_info(void);


/**
    @function: srec_ksym_addr_t srecorder_get_swap_lock(void)
    @brief: ��ȡ����swap_lock�ĵ�ַ

    @param: none
    
    @return: ����swap_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_swap_lock(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_vmap_area_lock(void)
    @brief: ��ȡ����swap_lock�ĵ�ַ

    @param: none
    
    @return: ����vmap_area_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_vmap_area_lock(void);


/**
    @function: srec_ksym_addr_t srecorder_get_vmap_area_list(void)
    @brief: ��ȡ����swap_lock�ĵ�ַ

    @param: none
    
    @return: ����vmap_area_list�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_vmap_area_list(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_register_oom_notifier(void)
    @brief: ��ȡ����register_oom_notifier�ĵ�ַ

    @param: none
    
    @return: ����register_oom_notifier�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_register_oom_notifier(void);


/**
    @function: srec_ksym_addr_t srecorder_get_unregister_oom_notifier(void)
    @brief: ��ȡ����unregister_oom_notifier�ĵ�ַ

    @param: none
    
    @return: ����unregister_oom_notifier�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_unregister_oom_notifier(void);


/**
    @function: srec_ksym_addr_t srecorder_get_register_jprobe(void)
    @brief: ��ȡ����register_jprobe�ĵ�ַ

    @param: none
    
    @return: ����register_jprobe�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_register_jprobe(void);


/**
    @function: srec_ksym_addr_t srecorder_get_unregister_jprobe(void)
    @brief: ��ȡ����unregister_jprobe�ĵ�ַ

    @param: none
    
    @return: ����unregister_jprobe�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_unregister_jprobe(void);


/**
    @function: srec_ksym_addr_t srecorder_get_jprobe_return(void)
    @brief: ��ȡ����jprobe_return�ĵ�ַ

    @param: none
    
    @return: ����jprobe_return�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_jprobe_return(void);


#if defined(CONFIG_DUMP_CURRENT_PS_BACKTRACE)
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36))
/**
    @function: srec_ksym_addr_t srecorder_get_vfsmount_lock_lock(void)
    @brief: ��ȡ����vfsmount_lock_lock�ĵ�ַ

    @param: none
    
    @return: ����vfsmount_lock_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_vfsmount_lock_lock(void);
#else
/**
    @function: srec_ksym_addr_t srecorder_get_vfsmount_lock(void)
    @brief: ��ȡ����vfsmount_lock�ĵ�ַ

    @param: none
    
    @return: ����vfsmount_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_vfsmount_lock(void);
#endif


#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
/**
    @function: srec_ksym_addr_t srecorder_get_dcache_lock(void)
    @brief: ��ȡ����dcache_lock�ĵ�ַ

    @param: none
    
    @return: ����dcache_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_dcache_lock(void);
#else
/**
    @function: srec_ksym_addr_t srecorder_get_rename_lock(void)
    @brief: ��ȡ����rename_lock�ĵ�ַ

    @param: none
    
    @return: ����rename_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_rename_lock(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_arch_vma_name(void)
    @brief: ��ȡ����arch_vma_name�ĵ�ַ

    @param: none
    
    @return: ����arch_vma_name�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_arch_vma_name(void);
#endif


#ifdef CONFIG_FUNCTION_GRAPH_TRACER
#endif


#ifdef CONFIG_ARM_UNWIND
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 2, 0))
/**
    @function: srec_ksym_addr_t srecorder_get___origin_unwind_idx(void)
    @brief: ��ȡ����__origin_unwind_idx�ĵ�ַ

    @param: none
    
    @return: ����__origin_unwind_idx�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get___origin_unwind_idx(void);
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_unwind_tables(void)
    @brief: ��ȡ����unwind_tables�ĵ�ַ

    @param: none
    
    @return: ����unwind_tables�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_unwind_tables(void);


/**
    @function: srec_ksym_addr_t srecorder_get_unwind_lock(void)
    @brief: ��ȡ����unwind_lock�ĵ�ַ

    @param: none
    
    @return: ����unwind_lock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_unwind_lock(void);
#endif


#if defined(CONFIG_DUMP_ALLPS_INFO)
#endif


#if defined(CONFIG_DUMP_ALLCPU_STACK) || defined(CONFIG_DUMP_ALLPS_INFO)
#endif


#if defined(CONFIG_DUMP_ALLCPU_STACK)
#endif


/**
    @function: srec_ksym_addr_t srecorder_get_atomic_notifier_chain_register(void)
    @brief: ��ȡ����atomic_notifier_chain_register�ĵ�ַ

    @param: none
    
    @return: atomic_notifier_chain_register�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_atomic_notifier_chain_register(void);


/**
    @function: srec_ksym_addr_t srecorder_get_atomic_notifier_chain_unregister(void)
    @brief: ��ȡ����atomic_notifier_chain_unregister�ĵ�ַ

    @param: none
    
    @return: atomic_notifier_chain_unregister�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_atomic_notifier_chain_unregister(void);


#if defined(CONFIG_DUMP_DMESG)
/**
    @function: srec_ksym_addr_t srecorder_get_log_buf(void)
    @brief: �õ��ں�ring buffer����ʼ��ַ

    @param: none
    
    @return: �ں�ring buffer��ʼ��ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_buf(void);


/**
    @function: srec_ksym_addr_t srecorder_get_log_buf_len(void)
    @brief: �õ��ں˱���log_buf_len����ʼ��ַ

    @param: none
    
    @return: �ں˱���log_buf_len����ʼ��ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_buf_len(void);


/**
    @function: srec_ksym_addr_t srecorder_get_log_end(void)
    @brief: �õ��ں˱���log_end����ʼ��ַ

    @param: none
    
    @return: �ں˱���log_end����ʼ��ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_log_end(void);
#endif


#if defined(CONFIG_DUMP_SLAB_INFO)
#ifdef CONFIG_SLAB
/**
    @function: srec_ksym_addr_t srecorder_get_cache_chain(void)
    @brief: ��ȡcache_chain�ĵ�ַ, slab����Ϣ����������
    
    @param: none
    
    @return: cache_chain

    @note: 
*/
srec_ksym_addr_t srecorder_get_cache_chain(void);


/**
    @function: srec_ksym_addr_t srecorder_get_cache_chain_mutex(void)
    @brief: ��ȡcache_chain_mutex�ĵ�ַ, ����ͬ����cache_chain�Ķ�д
    
    @param: none
    
    @return: cache_chain_mutex

    @note: 
*/
srec_ksym_addr_t srecorder_get_cache_chain_mutex(void);
#elif defined(CONFIG_SLUB)
/**
    @function: srec_ksym_addr_t srecorder_get_slab_caches(void)
    @brief: ��ȡslab_caches�ĵ�ַ, slab����Ϣ����������
    
    @param: none
    
    @return: slab_caches

    @note: 
*/
srec_ksym_addr_t srecorder_get_slab_caches(void);


/**
    @function: srec_ksym_addr_t srecorder_get_slub_lock(void)
    @brief: ��ȡslub_lock�ĵ�ַ, ����ͬ����slab_caches�Ķ�д
    
    @param: none
    
    @return: slub_lock

    @note: 
*/
srec_ksym_addr_t srecorder_get_slub_lock(void);
#endif
#endif


#if defined(CONFIG_DUMP_MODEM_LOG)
/**
    @function: srec_ksym_addr_t srecorder_get_spinlocks_initialized(void)
    @brief: ��ȡ����spinlocks_initialized�ĵ�ַ

    @param: none
    
    @return: ����spinlocks_initialized�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_spinlocks_initialized(void);


/**
    @function: srec_ksym_addr_t srecorder_get_remote_spinlock(void)
    @brief: ��ȡ����remote_spinlock�ĵ�ַ

    @param: none
    
    @return: ����remote_spinlock�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_remote_spinlock(void);


/**
    @function: srec_ksym_addr_t srecorder_get_smem_areas(void)
    @brief: ��ȡ����smem_areas�ĵ�ַ

    @param: none
    
    @return: ����smem_areas�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_smem_areas(void);


/**
    @function: srec_ksym_addr_t srecorder_get_num_smem_areas(void)
    @brief: ��ȡ����num_smem_areas�ĵ�ַ

    @param: none
    
    @return: ����num_smem_areas�ĵ�ַ

    @note: 
*/
srec_ksym_addr_t srecorder_get_num_smem_areas(void);
#endif


/**
    @function: int srecorder_init_kernel_symbols(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��s_kallsyms_lookup_name����syschk_sym_addr_table�ṹ�еĸ���
               ���Ų��Ҷ�Ӧ�������ַ

    @param: pinit_params
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_kernel_symbols(srecorder_module_init_params_t *pinit_params);


#ifdef __cplusplus
}
#endif
#endif /* SRECORDER_KERNEL_SYMBOLS_H */

