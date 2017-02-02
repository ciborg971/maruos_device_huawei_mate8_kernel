

/*----includes-----------------------------------------------------------------------*/

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/fs_struct.h>
#include <linux/file.h>
#include <linux/sched.h>
#include <linux/mm.h>
#include <linux/hugetlb.h>
#include <linux/dcache.h>
#include <linux/mount.h>
#include <linux/prefetch.h>
#include <linux/version.h>

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
#include <linux/seq_file.h>
#include <linux/poll.h>
#endif

#include <asm/pgalloc.h>
#include <asm/uaccess.h>
#include <asm/tlb.h>
#include <asm/tlbflush.h>
#include <asm/pgtable.h>
#include <asm/cacheflush.h>

#include "../include/srecorder_current_ps_backtrace.h"
#include "../include/srecorder_kernel_symbols.h"
#include "../include/srecorder_save_log.h"
#include "../include/srecorder_dump_backtrace.h"
#include "../include/srecorder_snprintf.h"


#if defined(CONFIG_DUMP_CURRENT_PS_BACKTRACE)

/*----local macroes------------------------------------------------------------------*/

#define SRECORDER_USER_STACK_DEPTH_MAX (64)
#define SRECORDER_ARM_USER_STACK_PRINT_MAX (10 * (PAGE_SIZE)) /*����ӡ�Ǹ�ҳ�������*/


/*----local prototypes----------------------------------------------------------------*/

struct frame_tail 
{
    struct frame_tail *fp;
    unsigned long sp;
    unsigned long lr;
} __attribute__((packed));

struct stacktrace_state
{
    int depth;
};

typedef const char* (*arch_vma_name_func)(struct vm_area_struct *vma);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
struct mnt_namespace 
{
    atomic_t        count;
    struct mount *    root;
    struct list_head    list;
    wait_queue_head_t poll;
    int event;
};

struct mnt_pcp
{
    int mnt_count;
    int mnt_writers;
};

struct mount 
{
    struct list_head mnt_hash;
    struct mount *mnt_parent;
    struct dentry *mnt_mountpoint;
    struct vfsmount mnt;
#ifdef CONFIG_SMP
    struct mnt_pcp __percpu *mnt_pcp;
    atomic_t mnt_longterm;        /* how many of the refs are longterm */
#else
    int mnt_count;
    int mnt_writers;
#endif
    struct list_head mnt_mounts;    /* list of children, anchored here */
    struct list_head mnt_child;    /* and going through their mnt_child */
    struct list_head mnt_instance;    /* mount instance on sb->s_mounts */
    const char *mnt_devname;    /* Name of device e.g. /dev/dsk/hda1 */
    struct list_head mnt_list;
    struct list_head mnt_expire;    /* link in fs-specific expiry list */
    struct list_head mnt_share;    /* circular list of shared mounts */
    struct list_head mnt_slave_list;/* list of slave mounts */
    struct list_head mnt_slave;    /* slave list entry */
    struct mount *mnt_master;    /* slave is on master->mnt_slave_list */
    struct mnt_namespace *mnt_ns;    /* containing namespace */
#ifdef CONFIG_FSNOTIFY
    struct hlist_head mnt_fsnotify_marks;
    __u32 mnt_fsnotify_mask;
#endif
    int mnt_id;            /* mount identifier */
    int mnt_group_id;        /* peer group identifier */
    int mnt_expiry_mark;        /* true if marked for expiry */
    int mnt_pinned;
    int mnt_ghosts;
};
#endif


/*----local variables------------------------------------------------------------------*/


/*----global variables-----------------------------------------------------------------*/


/*----local function prototypes---------------------------------------------------------*/

static void srecorder_dump_vma(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask);
static void srecorder_dump_taskinfo(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask);
static void srecorder_dump_kernel_stack(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask);
static void srecorder_dump_kernel_trace(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask);
static void srecorder_dump_user_backtrace(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask);
static void srecorder_dump_user_stack(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask);
static int srecorder_dump_current_ps_backtrace(srecorder_reserved_mem_info_t *pmem_info, unsigned int mask);

static struct frame_tail *srecorder_user_backtrace(srecorder_reserved_mem_info_t *pmem_info, struct frame_tail *tail);
static int srecorder_report_trace(srecorder_reserved_mem_info_t *pmem_info, struct stackframe *frame, void *d);
static void notrace srecorder_walk_stackframe(srecorder_reserved_mem_info_t *pmem_info, 
    struct stackframe *frame, int (*fn)(srecorder_reserved_mem_info_t *, struct stackframe *, void *), void *data);
static void srecorder_get_process_maps(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask);
static char *srecorder_d_path(const struct path *path, char *buf, int buflen);
static int srecorder_prepend(char **buffer, int *buflen, const char *str, int namelen);
static int srecorder_prepend_name(char **buffer, int *buflen, struct qstr *name);

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 14))
static int srecorder_prepend_path(const struct path *path, const struct path *root, char **buffer, int *buflen);
#else
static int srecorder_prepend_path(const struct path *path, struct path *root, char **buffer, int *buflen);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 14))
static int srecorder_path_with_deleted(const struct path *path, const struct path *root, char **buf, int *buflen);
#else
static int srecorder_path_with_deleted(const struct path *path, struct path *root, char **buf, int *buflen);
#endif

#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
static char *__srecorder_d_path(const struct path *path, struct path *root, char *buffer, int buflen);
#endif

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
static inline struct mount *srecorder_real_mount(struct vfsmount *mnt)
{
    return container_of(mnt, struct mount, mnt);
}

static inline int srecorder_mnt_has_parent(struct mount *mnt)
{
    return mnt != mnt->mnt_parent;
}
#endif


/*----function definitions--------------------------------------------------------------*/

/**
    @function: static void srecorder_dump_vma(srecorder_reserved_mem_info_for_log_t *pmem_info, struct task_struct *ptask)
    @brief: dump���̵�vma��Ϣ��������Ҫʵ��
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: ptask ����ӡvma��Ϣ�Ľ���
    
    @return: none

    @note: 
*/
static void srecorder_dump_vma(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask)
{
    if (NULL == pmem_info || NULL == ptask)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
}


/**
    @function: static void srecorder_dump_kernel_stack(srecorder_reserved_mem_info_for_log_t *pmem_info, struct task_struct *ptask)
    @brief: ��ӡ���̵���Ϣ����x86��ʵ���ˣ���ARM�Ͽ��Ը�����Ҫ��ʵ��
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: ptask 
    
    @return: none

    @note: 
*/
static void srecorder_dump_taskinfo(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask)
{
    if (NULL == pmem_info || NULL == ptask)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
}


/**
    @function: static void srecorder_dump_kernel_stack(srecorder_reserved_mem_info_for_log_t *pmem_info, struct task_struct *ptask)
    @brief: ��ӡ�ں�̬����ջ
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: ptask ����ӡ�ں�̬����ջ�Ľ���
    
    @return: none

    @note: 
*/
static void srecorder_dump_kernel_stack(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask)
{
    if (NULL == pmem_info || NULL == ptask)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
}


/**
    @function: static void srecorder_dump_kernel_trace(srecorder_reserved_mem_info_for_log_t *pmem_info, struct task_struct *ptask)
    @brief: ��ӡ�ں�̬���ù켣
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: ptask ����ӡ�ں�̬���ù켣�Ľ���
    
    @return: none

    @note: 
*/
static void srecorder_dump_kernel_trace(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask)
{
    if (NULL == pmem_info || NULL == ptask)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }

    srecorder_dump_backtrace(pmem_info, NULL, ptask);
}


/**
    @function: static struct frame_tail *srecorder_user_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info, struct frame_tail *tail)
    @brief: ��ӡ�û�̬�ĵ��ù켣�������̴����û�̬����ֱ�ӵ��øú���
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: tail ջ֡��ַ
    
    @return: ��һ��ջ֡�ĵ�ַ

    @note: 
*/
static struct frame_tail *srecorder_user_backtrace(srecorder_reserved_mem_info_t *pmem_info, struct frame_tail *tail)
{
    struct frame_tail buftail[2];
    int bytes_read = 0;

    memset(buftail, 0, sizeof(buftail));

    if (unlikely(NULL == pmem_info || NULL == tail))
    {
        return NULL;
    }
    
    /* Also check accessibility of one struct frame_tail beyond */
    if (!access_ok(VERIFY_READ, tail, sizeof(buftail))) 
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "  invalid frame pointer %p\n", tail);
        srecorder_renew_meminfo(pmem_info, bytes_read);
        
        return NULL;
    }
    
    if (__copy_from_user_inatomic(buftail, tail, sizeof(buftail))) 
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "  failed to copy frame pointer %p\n", tail);
        srecorder_renew_meminfo(pmem_info, bytes_read);
        
        return NULL;
    }

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, " lr = %p\n", (void *)buftail[0].lr);
    srecorder_renew_meminfo(pmem_info, bytes_read);

    /* frame pointers should strictly progress back up the stack
     * (towards higher addresses) */
    if (tail >= buftail[0].fp)
    {
        return NULL;
    }

    return buftail[0].fp - 1;
}


/**
    @function: static int srecorder_report_trace(srecorder_reserved_mem_info_for_log_t *pmem_info, struct stackframe *frame, void *d)
    @brief: ��ӡ�û�̬�ĵ��ù켣
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: frame ջ֡��ַ
    @param: d ��¼��ջ����״̬�Ľṹ��ָ��
    
    @return: none

    @note: 
*/
static int srecorder_report_trace(srecorder_reserved_mem_info_t *pmem_info, struct stackframe *frame, void *d)
{
#ifdef CONFIG_ARM
    struct stacktrace_state *sts = d;
    int bytes_read = 0;
    
    if (NULL == pmem_info || NULL == frame || NULL == d)
    {
        return -1;
    }
    
    if (0 != sts->depth) 
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "  pc: %p (%pF), lr %p (%pF), sp %p, fp %p\n",
            (void *)frame->pc, (void *)frame->pc, (void *)frame->lr,(void *) frame->lr,
            (void *)frame->sp, (void *)frame->fp);
        srecorder_renew_meminfo(pmem_info, bytes_read);
        sts->depth--;
        return 0;
    }

    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "%s", "  ...\n");
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    return sts->depth == 0;
#else
    return 0;
#endif
}


/**
    @function: static void notrace srecorder_walk_stackframe(srecorder_reserved_mem_info_for_log_t *pmem_info, 
                struct stackframe *frame, int (*fn)(srecorder_reserved_mem_info_for_log_t *, struct stackframe *, void *), void *data)
    @brief: ����ջ֡
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: frame ��ʼջ֡
    @param: fn �û�̬���ù켣��ӡ���������Ǵ�ӡlr������
    @param: data �����Ĳ������Ա�����ʹ��
    
    @return: none

    @note: 
*/
static void notrace srecorder_walk_stackframe(srecorder_reserved_mem_info_t *pmem_info, 
    struct stackframe *frame, int (*fn)(srecorder_reserved_mem_info_t *, struct stackframe *, void *), void *data)
{
    while (1) 
    {
        int ret;

        if (0 != fn(pmem_info, frame, data))
        {
            break;
        }
        
        ret = srecorder_unwind_frame(frame);
        if (ret < 0)
        {
            break;
        }
    }
}


/**
    @function: static int srecorder_prepend(char **buffer, int *buflen, const char *str, int namelen)
    @brief: copy�ַ���
    
    @param: buffer �洢·���Ļ���ָ��
    @param: buflen buffer����
    @param: str �ļ�·����ʼ��ַ
    @param: namelen ·������
    
    @return: 0 - success, -1 - failed

    @note: 
*/
static int srecorder_prepend(char **buffer, int *buflen, const char *str, int namelen)
{
    if (unlikely(NULL == buffer || NULL == buflen || NULL == str))
    {
        return -1;
    }
    
    *buflen -= namelen;
    if (*buflen < 0)
    {
        return -ENAMETOOLONG;
    }
    *buffer -= namelen;
    memcpy(*buffer, str, namelen);
    
    return 0;
}


/**
    @function: static int srecorder_prepend_name(char **buffer, int *buflen, struct qstr *name)
    @brief: copy�ַ���
    
    @param: buffer �洢·���Ļ���ָ��
    @param: buflen buffer����
    @param: name
    
    @return: 0 - success, -1 - failed

    @note: 
*/
static int srecorder_prepend_name(char **buffer, int *buflen, struct qstr *name)
{
    if (unlikely(NULL == buffer || NULL == buflen || NULL == name))
    {
        return -1;
    }
    
    return srecorder_prepend(buffer, buflen, name->name, name->len);
}


/**
    @function: static int srecorder_prepend_path(const struct path *path, const struct path *root, char **buffer, int *buflen)
    @brief: Prepend path string to a buffer
    
    @param: path: the dentry/vfsmount to report
    @param: root: root vfsmnt/dentry
    @param: buffer: pointer to the end of the buffer
    @param: buflen: pointer to buffer length
    
    @return: 0 - success, others - failed

    @note: 
*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 14))
static int srecorder_prepend_path(const struct path *path, const struct path *root, char **buffer, int *buflen)
#else
static int srecorder_prepend_path(const struct path *path, struct path *root, char **buffer, int *buflen)
#endif
{
    struct dentry *dentry;
    struct vfsmount *vfsmnt;
    bool slash = false;
    int error = 0;
    arch_spinlock_t *lock;
    
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
    struct mount *mnt;
#endif

    if (unlikely(NULL == path || NULL == root || NULL == buffer || NULL == buflen 
        || INVALID_KSYM_ADDR == srecorder_get_vfsmount_lock_lock()))
    {
        return -1;
    }
    dentry = path->dentry;
    vfsmnt = path->mnt;
 
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 3, 0))
    mnt = srecorder_real_mount(vfsmnt);
#endif
    preempt_disable();
/*lint -e666 */ 
    lock = &__get_cpu_var(*(arch_spinlock_t *)srecorder_get_vfsmount_lock_lock()); 
/*lint +e666 */ 
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 3, 0))
    if (arch_spin_trylock(lock))
    {
        while (dentry != root->dentry || vfsmnt != root->mnt) 
        {
            struct dentry * parent;

            if (dentry == vfsmnt->mnt_root || IS_ROOT(dentry)) 
            {
                /* Global root? */
                if (vfsmnt->mnt_parent == vfsmnt) 
                {
                    goto global_root;
                }
                dentry = vfsmnt->mnt_mountpoint;
                vfsmnt = vfsmnt->mnt_parent;
                continue;
            }
            parent = dentry->d_parent;
            prefetch(parent);
            error = -1;
            
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 38))
            if (spin_trylock(&dentry->d_lock))
            {
                error = srecorder_prepend_name(buffer, buflen, &dentry->d_name);
                spin_unlock(&dentry->d_lock);
            }
#else
            error = srecorder_prepend_name(buffer, buflen, &dentry->d_name);
#endif

            if (0 == error)
            {
                error = srecorder_prepend(buffer, buflen, "/", 1);
            }

            if (error)
            {
                break;
            }

            slash = true;
            dentry = parent;
        }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 14))
        if (!error && !slash)
        {
            error = srecorder_prepend(buffer, buflen, "/", 1);
        }
#endif
    }

out:
#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 0, 14))
        if (!error && !slash)
        {
            error = srecorder_prepend(buffer, buflen, "/", 1);
        }
#endif
    arch_spin_unlock(lock);
    preempt_enable();
    return error;

global_root:
    /*
    * Filesystems needing to implement special "root names"
    * should do so with ->d_dname()
    */
    if (IS_ROOT(dentry) && (dentry->d_name.len != 1 || dentry->d_name.name[0] != '/')) 
    {
        WARN(1, "Root dentry has weird name <%.*s>\n", (int) dentry->d_name.len, dentry->d_name.name);
    }

#if (LINUX_VERSION_CODE < KERNEL_VERSION(3, 0, 14))
    root->mnt = vfsmnt;
    root->dentry = dentry; 
#else
    if (!slash)
    {
        error = srecorder_prepend(buffer, buflen, "/", 1);
    }

    if (!error)
    {
        error = vfsmnt->mnt_ns ? 1 : 2;
    }
#endif
    goto out;
#else
    if (arch_spin_trylock(lock))
    {
        while (dentry != root->dentry || vfsmnt != root->mnt)
        {
            struct dentry * parent;

            if (dentry == vfsmnt->mnt_root || IS_ROOT(dentry))
            {
                /* Global root? */
                if (!srecorder_mnt_has_parent(mnt))
                {
                    goto global_root;
                }
                dentry = mnt->mnt_mountpoint;
                mnt = mnt->mnt_parent;
                vfsmnt = &mnt->mnt;
                continue;
            }
            parent = dentry->d_parent;
            prefetch(parent);
            error = -1;
            if (spin_trylock(&dentry->d_lock))
            {
                error = srecorder_prepend_name(buffer, buflen, &dentry->d_name);
                spin_unlock(&dentry->d_lock);
            }
            if (!error)
            {
                error = srecorder_prepend(buffer, buflen, "/", 1);
            }

            if (error)
            {
                break;
            }

            slash = true;
            dentry = parent;
        }

        if (!error && !slash)
        {
            error = srecorder_prepend(buffer, buflen, "/", 1);
        }
    }
    
out:
    arch_spin_unlock(lock);
    preempt_enable();
    return error;

global_root:
    /*
    * Filesystems needing to implement special "root names"
    * should do so with ->d_dname()
    */
    if (IS_ROOT(dentry) && (dentry->d_name.len != 1 || dentry->d_name.name[0] != '/')) 
    {
        WARN(1, "Root dentry has weird name <%.*s>\n", (int) dentry->d_name.len, dentry->d_name.name);
    }

    if (!slash)
    {
        error = srecorder_prepend(buffer, buflen, "/", 1);
    }

    if (!error)
    {
        error = srecorder_real_mount(vfsmnt)->mnt_ns ? 1 : 2;
    }
    goto out;
#endif
}


/**
    @function: static int srecorder_path_with_deleted(const struct path *path, const struct path *root, 
        char **buf, int *buflen)
    @brief: return the path of a dentry but appends "(deleted)" for unlinked files.
    
    @param: path: path to report
    @param: root: root vfsmnt/dentry
    @param: buf: buffer to return value in
    @param: buflen: buffer length
    
    @return: none

    @note: 
*/
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 14))
static int srecorder_path_with_deleted(const struct path *path, const struct path *root, char **buf, int *buflen)
#else
static int srecorder_path_with_deleted(const struct path *path, struct path *root, char **buf, int *buflen)
#endif
{
    if (unlikely(NULL == path || NULL == root || NULL == buf || NULL == buflen))
    {
        return -1;
    }
    
    srecorder_prepend(buf, buflen, "\0", 1);
    
    if (d_unlinked(path->dentry))
    {
        int error = srecorder_prepend(buf, buflen, " (deleted)", 10);
        
        if (0 != error)
        {
            return error;
        }
    }

    return srecorder_prepend_path(path, root, buf, buflen);
}


#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 36))
/**
    * __d_path - return the path of a dentry
    * @path: the dentry/vfsmount to report
    * @root: root vfsmnt/dentry (may be modified by this function)
    * @buffer: buffer to return value in
    * @buflen: buffer length
    *
    * Convert a dentry into an ASCII path name. If the entry has been deleted
    * the string " (deleted)" is appended. Note that this is ambiguous.
    *
    * Returns a pointer into the buffer or an error code if the
    * path was too long.
    *
    * "buflen" should be positive. Caller holds the dcache_lock.
    *
    * If path is not reachable from the supplied root, then the value of
    * root is changed (without modifying refcounts).
*/
static char *__srecorder_d_path(const struct path *path, struct path *root, char *buffer, int buflen)
{
    struct dentry *dentry = path->dentry;
    struct vfsmount *vfsmnt = path->mnt;
    char *end = buffer + buflen;
    char *retval;
    bool has_vfsmount_lock = false;
    
    if (unlikely(INVALID_KSYM_ADDR == srecorder_get_vfsmount_lock()))
    {
        return "";
    }

    has_vfsmount_lock = spin_trylock((spinlock_t *)srecorder_get_vfsmount_lock());
    if (has_vfsmount_lock)
    {
        srecorder_prepend(&end, &buflen, "\0", 1);
        if (d_unlinked(dentry) && (srecorder_prepend(&end, &buflen, " (deleted)", 10) != 0))
        {
            goto Elong;
        }

        if (buflen < 1)
        {
            goto Elong;
        }
        
        /* Get '/' right */
        retval = end-1;
        *retval = '/';

        for (;;) 
        {
            struct dentry * parent;

            if (dentry == root->dentry && vfsmnt == root->mnt)
            {
                break;
            }
            
            if (dentry == vfsmnt->mnt_root || IS_ROOT(dentry)) 
            {
                /* Global root? */
                if (vfsmnt->mnt_parent == vfsmnt) 
                {
                    goto global_root;
                }
                dentry = vfsmnt->mnt_mountpoint;
                vfsmnt = vfsmnt->mnt_parent;
                continue;
            }
            parent = dentry->d_parent;
            prefetch(parent);
            if ((srecorder_prepend_name(&end, &buflen, &dentry->d_name) != 0)
                || (srecorder_prepend(&end, &buflen, "/", 1) != 0))
            {
                goto Elong;
            }
            retval = end;
            dentry = parent;
        }
    }
out:
    if (has_vfsmount_lock)
    {
        spin_unlock((spinlock_t *)srecorder_get_vfsmount_lock());
    }
    return retval;

global_root:
    retval += 1;	/* hit the slash */
    if (srecorder_prepend_name(&retval, &buflen, &dentry->d_name) != 0)
    {
        goto Elong;
    }
    root->mnt = vfsmnt;
    root->dentry = dentry;
    goto out;

Elong:
    retval = ERR_PTR(-ENAMETOOLONG);
    goto out;
}
#endif


/**
    @function: static char *srecorder_d_path(const struct path *path, char *buf, int buflen)
    @brief: return the path of a dentry
    
    @param: path: path to report
    @param: buf: buffer to return value in
    @param: buflen: buffer length
    
    @return: none

    @note: 
*/
static char *srecorder_d_path(const struct path *path, char *buf, int buflen)
{
    char *res = buf + buflen;
    struct path root;
    int error;
    int have_lock = 0;

    if (unlikely(NULL == path || NULL == buf)
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
        || INVALID_KSYM_ADDR == srecorder_get_dcache_lock()
#else
        || INVALID_KSYM_ADDR == srecorder_get_rename_lock()
#endif
        )
    {
        return "";
    }
    
    /*
     * We have various synthetic filesystems that never get mounted.  On
     * these filesystems dentries are never used for lookup purposes, and
     * thus don't need to be hashed.  They also don't need a name until a
     * user wants to identify the object in /proc/pid/fd/.  The little hack
     * below allows us to generate a name for these objects on demand:
     */
    if (path->dentry->d_op && path->dentry->d_op->d_dname)
    {
        return path->dentry->d_op->d_dname(path->dentry, buf, buflen);
    }

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 36))
    if (spin_trylock(&(current->fs->lock)))
    {
        root = current->fs->root;
        have_lock = (NULL != root.dentry) && (spin_trylock(&(root.dentry->d_lock))); /* ��Ҫ����˳�� */
        spin_unlock(&(current->fs->lock));
        if (0 != have_lock)
        {
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
            if (spin_trylock((spinlock_t *)srecorder_get_dcache_lock()))
#else
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 10, 0))
            write_seqlock((seqlock_t *)srecorder_get_rename_lock());
#else
            if (write_tryseqlock((seqlock_t *)srecorder_get_rename_lock()))
#endif
#endif
            {
                error = srecorder_path_with_deleted(path, &root, &res, &buflen);
                if (error < 0)
                {
                    res = ERR_PTR(error);
                }
                
#if (LINUX_VERSION_CODE < KERNEL_VERSION(2, 6, 38))
                spin_unlock((spinlock_t *)srecorder_get_dcache_lock());
#else
                write_sequnlock((seqlock_t *)srecorder_get_rename_lock());
#endif
            }
            spin_unlock(&(root.dentry->d_lock));
        }
    }
#else
    if (read_trylock(&(current->fs->lock)))
    {
        root = current->fs->root;
        read_unlock(&(current->fs->lock));
        if (spin_trylock((spinlock_t *)srecorder_get_dcache_lock()))
        {
            res = __srecorder_d_path(path, &root, buf, buflen);
            spin_unlock((spinlock_t *)srecorder_get_dcache_lock());
        }
    }
#endif

    return res;
}


/**
    @function: static void srecorder_get_process_maps(srecorder_reserved_mem_info_for_log_t *pmem_info, struct task_struct *ptask)
    @brief: ��ȡ�������̵�ӳ����Ϣ
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: ptask ����ȡӳ����Ϣ�Ľ���
    
    @return: none

    @note: 
*/
static void srecorder_get_process_maps(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask)
{
    struct mm_struct *mm = NULL;
    struct vm_area_struct *vma = NULL;

    if (unlikely(NULL == pmem_info || NULL == ptask))
    {
        return;
    }

    if (NULL == ptask->mm || ptask->flags & PF_KTHREAD) /* �ں��߳� */
    {
        return;
    }

    mm = ptask->mm;
    vma = mm->mmap;
    while (NULL != vma)
    {
        unsigned long start;
        unsigned long end;
        
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(3, 0, 1))
        vm_flags_t flags = vma->vm_flags;
#else
        int flags = vma->vm_flags;
#endif

        /* We don't show the stack guard page in /proc/maps */
        start = vma->vm_start;
#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 39)) /* ��ʵ��2.6.38.7����������Ĵ��� */
        if (stack_guard_page_start(vma, start))
        {
            start += PAGE_SIZE;
        }
#endif
        end = vma->vm_end;

#if (LINUX_VERSION_CODE >= KERNEL_VERSION(2, 6, 39)) /* ��ʵ��2.6.38.7����������Ĵ��� */
        if (stack_guard_page_end(vma, end))
        {
            end -= PAGE_SIZE;
        }
#endif
        if (flags & VM_EXEC)
        {
            struct file *file = vma->vm_file;
            int bytes_read = 0;

            if (NULL != file)
            {
                char buf[128] = {0}; /* ӳ���ļ���·������Ĭ������Ϊ256�ֽ� */
                char *ppath = srecorder_d_path(&file->f_path, buf, 128);
                
                if (!IS_ERR(ppath))
                {
                    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                        "$ %08lx-%08lx:%s\n", start, end, ppath);
                }
            }
            else
            {
                arch_vma_name_func arch_vma_name = (arch_vma_name_func)srecorder_get_arch_vma_name();
                const char *name = NULL;

                if (NULL != arch_vma_name)
                {
                    name = arch_vma_name(vma);
                }

                bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
                    "$ %08lx-%08lx:%s\n", start, end, (NULL == name) ? ("anonymous") : (name));
            }
            srecorder_renew_meminfo(pmem_info, bytes_read);
        }
        vma = vma->vm_next;
    }
}


/**
    @function: static void srecorder_dump_user_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info, struct task_struct *ptask)
    @brief: ��ӡ���̵��û�̬�ĵ��ù켣��
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: ptask ����ӡ���ù켣�Ľ���
    
    @return: none

    @note: 
*/
static void srecorder_dump_user_backtrace(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask)
{
#ifdef CONFIG_ARM
    struct frame_tail *tail;
    struct stackframe frame;
    int bytes_read = 0;
    struct pt_regs * regs = NULL;
    int depth = SRECORDER_USER_STACK_DEPTH_MAX;
    //struct thread_info *real_thread_info = THREAD_INFO(ssp);
    struct stacktrace_state sts;

    sts.depth = depth;

    //*current_thread_info() = *real_thread_info;
    if (NULL == pmem_info || NULL == ptask)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
    
    if (NULL == current)
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "%s", "current: is NULL!\n");
        srecorder_renew_meminfo(pmem_info, bytes_read);
        return;
    }
    
    regs = task_pt_regs(current);
    if (NULL == regs)
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "%s", "current's registors is NULL!\n");
        srecorder_renew_meminfo(pmem_info, bytes_read);
        return;
    }
    
    /* �ں��߳� */
    if ((NULL == current->mm)
        || (current->flags & PF_KTHREAD)
        || (NULL == (void *)regs->ARM_pc || NULL == (void *)regs->ARM_lr))
    {
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "pc: %p (%pF), lr: %p (%pF) %s\n", (void *)regs->ARM_pc, (void *)regs->ARM_pc, (void *)regs->ARM_lr, 
            (void *)regs->ARM_lr, "The current process is a kernel thread which has no user stack!");
        srecorder_renew_meminfo(pmem_info, bytes_read); 
        return;
    }
    
    frame.fp = regs->ARM_fp;
    frame.sp = regs->ARM_sp;
    frame.lr = regs->ARM_lr;
    frame.pc = regs->ARM_pc;
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "***************************** dump user stack begin *****************************\n"
        "* For %s mode, do user backtrace:\n* pc: %p (%pF), lr: %p (%pF), sp: %p, fp: %p\n",
        user_mode(regs) ? ("USER") : ("NON-USER"), 
        (void *)regs->ARM_pc, (void *)regs->ARM_pc, (void *)regs->ARM_lr, 
        (void *)regs->ARM_lr, (void *)regs->ARM_sp, (void *)regs->ARM_fp);
    srecorder_renew_meminfo(pmem_info, bytes_read);
#if 0 /* ���ǲο�fiq_debugger.c��oprofile��ʵ�ֵ� */
    if (user_mode(regs)) 
    {        
        tail = ((struct frame_tail *)regs->ARM_fp) - 1;
        while (depth-- && NULL != tail && !((unsigned long) tail & 3))
        {
            tail = srecorder_user_backtrace(pmem_info, tail);
        }
    }
    else
    {
        srecorder_walk_stackframe(pmem_info, &frame, srecorder_report_trace, &sts);
    }
#endif
    if (1)
    {
#if 0 /* if 0�����Ĵ���ֻ�ܴ�ӡ�ں�ջ */
        register unsigned long current_sp asm ("sp");

        frame.fp = (unsigned long)__builtin_frame_address(0);
        frame.sp = current_sp;
        frame.lr = (unsigned long)__builtin_return_address(0);
        frame.pc = (unsigned long)srecorder_dump_user_backtrace;
        srecorder_walk_stackframe(pmem_info, &frame, srecorder_report_trace, &sts);
#else
        unsigned long top; /* ջ�� */
        unsigned long base; /* ջ�� */
        unsigned long sp = frame.sp; /* �û�̬ջ�� */
        unsigned long i = 0;

        /* ��#if 1����������ֻ��Ϊ�˱���ͨ����û��ʲô�ر���; */
#if 1        
        tail = NULL;
        srecorder_user_backtrace(NULL, NULL);
#endif
        
        top = sp;
        top &= ~(sizeof(unsigned long) - 1); /* ��֤4�ֽڶ��� */
        base = current->mm->start_stack; /* �����û�̬��ջ����ʼ��ַ */
        base &= ~(sizeof(unsigned long) - 1); /* ��֤4�ֽڶ��� */
        
        /* Ŀǰֻ��ӡʮ��page������ */
        if (abs(base - top) > SRECORDER_ARM_USER_STACK_PRINT_MAX)
        {
#ifdef CONFIG_STACK_GROWSUP
            base = top - SRECORDER_ARM_USER_STACK_PRINT_MAX;
#else
            base = top + SRECORDER_ARM_USER_STACK_PRINT_MAX;
#endif
        }
    
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "* User stack: from 0x%08lx to 0x%08lx\n* User heap: from 0x%08lx to 0x%08lx\n"
            "* cmd arg: from 0x%08lx to 0x%08lx\n* env: from 0x%08lx to 0x%08lx\n", 
            current->mm->start_stack, sp, 
            current->mm->start_brk, current->mm->brk, 
            current->mm->arg_start, current->mm->arg_end, 
            current->mm->env_start, current->mm->env_end);
        srecorder_renew_meminfo(pmem_info, bytes_read);

        /* ��ȡcurrent���̵��û�̬ӳ����Ϣ */
        if (spin_trylock(&(current->alloc_lock)))
        {
            if (0) /* There is no need to get user memory mapping information */
            {
                srecorder_get_process_maps(pmem_info, current);
            }
            spin_unlock(&(current->alloc_lock));
        }
        
        i = 0;
#if 0        
#ifdef CONFIG_STACK_GROWSUP
        while (top >= base)
#else
        while (top <= base)
#endif
        {
            /* There is no need to get user stack backtrace */
            {
                break;
            }
            if (0 == i % 32)
            {
                bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "%08lx: ", top);
                srecorder_renew_meminfo(pmem_info, bytes_read);
            }
            bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, 
                pmem_info->bytes_left, "%08lx ", *(unsigned long *)top);
            srecorder_renew_meminfo(pmem_info, bytes_read);
#ifdef CONFIG_STACK_GROWSUP
            top -= 4; /* ��ַ4�ֽڶ��� */
#else
            top += 4;
#endif
            i++;
            if (8 == i) /* ÿ��ӡ8 * 4�ֽڻ��� */
            {
                bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, "%s", "\n");
                srecorder_renew_meminfo(pmem_info, bytes_read);
                i = 0;
            }
        }
#endif
 
        bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
            "%s", "\n****************************** dump user stack end ******************************\n");
        srecorder_renew_meminfo(pmem_info, bytes_read);
#endif
    }
    else
    {
        srecorder_walk_stackframe(pmem_info, &frame, srecorder_report_trace, &sts);
    }
#endif
}


/**
    @function: static void srecorder_dump_user_stack(srecorder_reserved_mem_info_for_log_t *pmem_info, struct task_struct *ptask)
    @brief: ��ӡ���̵��û�̬����ջ��Ŀǰֻʵ�ִ�ӡ�û�̬�ĵ��ù켣��û���漰��ÿ���û�ջ�е�ÿ����������Ϣ
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: ptask ����ӡ����ջ�Ľ���
    
    @return: none

    @note: 
*/
static void srecorder_dump_user_stack(srecorder_reserved_mem_info_t *pmem_info, struct task_struct *ptask)
{
    if (NULL == pmem_info || NULL == ptask)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return;
    }
}


/**
    @function: static int srecorder_dump_current_ps_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info, unsigned int mask)
    @brief: ��ȡ����ʱ��ǰ���̵ĵ���ջ.
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    @param: mask ��Ϣdump��������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: Ŀǰֻ����ARMƽ̨��ʵ�֣�X86������ƽ̨������ʵ��
*/
static int srecorder_dump_current_ps_backtrace(srecorder_reserved_mem_info_t *pmem_info, unsigned int mask)
{
    int is_user_thread = 0; /*Ĭ�����ں��߳�*/
    int bytes_read = 0;
    char *pbuf = NULL;
    psrecorder_info_header_t pinfo_header = NULL;
    
    if (NULL == pmem_info)
    {
        SRECORDER_PRINTK("File [%s] line [%d] invalid param!\n", __FILE__, __LINE__);
        return -1;
    }

    if (0 != srecorder_write_info_header(pmem_info, CURRENT_PS_BACKTRACE_BIT5, &pinfo_header))
    {
        return -1;
    }
    
    pbuf = pmem_info->start_addr + pmem_info->bytes_read;
    bytes_read = SRECORDER_SNPRINTF(pmem_info->start_addr + pmem_info->bytes_read, pmem_info->bytes_left, 
        "current: pid=%d ppid=%d cpuid=%d name=%s\n", 
        current->pid, current->parent->pid, 
        task_cpu(current), current->comm);
    srecorder_renew_meminfo(pmem_info, bytes_read);
    
    /*
    * FIXME:��ô֪�����Ǹ��ں��߳�? ��������һ����������
    */
    if (NULL != current->mm)
    {
        is_user_thread = 1;
    }

    if (0 != is_user_thread)
    {
        /*dump vma*/
        if (mask & SRECORDER_SHOW_VMA)
        {
            srecorder_dump_vma(pmem_info, current);
        }

        /*dump cmdline*/
        if (mask & SRECORDER_SHOW_CMD)
        {
            srecorder_dump_taskinfo(pmem_info, current);
        }

        /*dump env*/
        if (mask & SRECORDER_SHOW_ENV)
        {
            /*TODO:*/
        }
    }

    /*dump_kernel stack*/
    if (mask & SRECORDER_SHOW_KSTK)
    {
        srecorder_dump_kernel_stack(pmem_info, current);
    }

    if (mask & SRECORDER_SHOW_KTRACE)
    {
        srecorder_dump_kernel_trace(pmem_info, current);
    }

    if (0 != is_user_thread)
    {
        /*��ӡ�û�ջ�ĵ��ù켣*/
        srecorder_dump_user_backtrace(pmem_info, current);

        /*
      * dump_user_stack, ���Կ���ʹ�� raw backtrace ��ʽ��ӡ�û�ջ�ĵ��ù켣
      */
        srecorder_dump_user_stack(pmem_info, current);
    }

    srecorder_validate_info_header(pinfo_header, pmem_info->bytes_per_type);
    
    return 0;
}


/**
    @function: int srecorder_get_current_ps_backtrace(srecorder_reserved_mem_info_for_log_t *pmem_info)
    @brief: ��ȡ����ʱ��ǰ���̵ĵ���ջ.
    
    @param: pmem_info SRecorder�ı����ڴ���Ϣ
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_get_current_ps_backtrace(srecorder_reserved_mem_info_t *pmem_info)
{
    if (srecorder_log_has_been_dumped(CURRENT_PS_BACKTRACE_BIT5) || pmem_info->dump_modem_crash_log_only)
    {
        SRECORDER_PRINTK("current ps backtrace has been dumped successfully!\n");
        return 0;
    }
    
    return srecorder_dump_current_ps_backtrace(pmem_info, SRECORDER_SHOW_ALL);
}


/**
    @function: int srecorder_init_dmesg(srecorder_module_init_params_t *pinit_params)
    @brief: ��ʼ��current ps backtraceģ��

    @param: pinit_params ģ���ʼ������
    
    @return: 0 - �ɹ���-1-ʧ��

    @note: 
*/
int srecorder_init_current_ps_backtrace(srecorder_module_init_params_t *pinit_params)
{
    srecorder_clear_log_dumped_bit(CURRENT_PS_BACKTRACE_BIT5);
    
    return 0;
}


/**
    @function: void srecorder_exit_current_ps_backtrace(void)
    @brief: �˳�current ps backtraceģ��

    @param: none
    
    @return: none

    @note: 
*/
void srecorder_exit_current_ps_backtrace(void)
{
    srecorder_set_log_dumped_bit(CURRENT_PS_BACKTRACE_BIT5);
}
#else
int srecorder_get_current_ps_backtrace(srecorder_reserved_mem_info_t *pmem_info)
{
    return 0;
}


int srecorder_init_current_ps_backtrace(srecorder_module_init_params_t *pinit_params)
{
    return 0;
}


void srecorder_exit_current_ps_backtrace(void)
{
    return;
}
#endif

