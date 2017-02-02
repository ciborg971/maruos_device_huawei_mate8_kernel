

#ifndef __OAL_SDIO_HOST_IF_H__
#define __OAL_SDIO_HOST_IF_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


#include "oal_util.h"
#include "oal_net.h"
#include "oal_sdio_comm.h"
#include "oal_workqueue.h"

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/mmc/host.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio.h>
#endif

enum {
    SDIO_READ = 0,
    SDIO_WRITE,
    SDIO_OPT_BUTT
};

typedef oal_int32 (*sdio_msg_rx)(oal_void* data);
typedef oal_int32 (*hisdio_rx)(oal_void* data);
typedef struct _sdio_bus_ops_
{
    hisdio_rx rx;
}sdio_bus_ops;

    /*0x30~0x38, 0x3c~7B*/
#define HISDIO_EXTEND_BASE_ADDR (0x30)
#define HISDIO_EXTEND_REG_COUNT (64)

#define HISDIO_ALIGN_4_OR_BLK(len)     ((len) < HISDIO_BLOCK_SIZE ? ALIGN((len), 4) : ALIGN((len), HISDIO_BLOCK_SIZE))

#define HISDIO_WAKEUP_DEV_REG  (0xf0)
#define ALLOW_TO_SLEEP_VALUE  (1)
#define DISALLOW_TO_SLEEP_VALUE  (0)

struct sdio_msg_stru
{
    sdio_msg_rx msg_rx;
    void* data;
    oal_uint32 count;
    oal_uint64 cpu_time;/*the time of the last come!*/
};

struct hisdio_extend_func
{
    oal_uint32 int_stat;
    oal_uint32 msg_stat;
    oal_uint32 xfer_count;
    oal_uint32 credit_info;
    oal_uint8  comm_reg[HISDIO_EXTEND_REG_COUNT];
};

struct sdio_scatt
{
    oal_uint32 max_scatt_num;
    struct scatterlist*  sglist;
};

struct hsdio_func1_info
{
    oal_uint32 func1_err_reg_info;
    oal_uint32 func1_err_int_count;
    oal_uint32 func1_ack_int_acount;
    oal_uint32 func1_msg_int_count;
    oal_uint32 func1_data_int_count;
    oal_uint32 func1_no_int_count;
};

struct hsdio_error_info
{
    oal_uint32 rx_scatt_info_not_match;
};

typedef struct _hsdio_tx_scatt_buff_
{
    /*record the tx scatt list assembled buffer*/
    oal_void* buff;
    oal_uint32 len;
}hsdio_tx_scatt_buff;

struct hsdio_credit_info{
    oal_uint8   short_free_cnt;
    oal_uint8   large_free_cnt;
    oal_spin_lock_stru credit_lock;
};


typedef struct _wlan_pm_callback
{
    oal_uint (*wlan_pm_wakeup_dev)(oal_void);                        //SDIO发包过程中中PM状态检查，如果是睡眠状态，同时唤醒
    oal_uint (*wlan_pm_state_get)(oal_void);                                   //获取当前PM状态
    oal_uint (*wlan_pm_wakeup_host)(oal_void);                                 //device唤醒host中断处理
    oal_void (*wlan_pm_feed_wdg)(oal_void);                                    //PM Sleep watch dog喂狗接口
    oal_void (*wlan_pm_fit_freq)(oal_uint32 ul_len, oal_uint32 ul_pkt_cnt);   //动态调频接口，CPU/DDR调频
}wlan_pm_callback_stru;

struct oal_sdio
{
    /*sdio work state, sleep , work or shutdown?*/
    oal_uint8                  state;

    oal_spin_lock_stru          st_pm_state_lock;       //pm state互斥锁，pm和gpio中断都用到
    wlan_pm_callback_stru      *pst_pm_callback;

    oal_spin_lock_stru          st_irq_lock;         //wlan gpio中断操作锁
    oal_uint                    ul_wlan_irq ;        //wlan gpio中断
#ifdef CONFIG_HAS_WAKELOCK
    struct wake_lock        st_wklock_wifi;        //wifi wakelock锁
    oal_spin_lock_stru      st_wklock_spinlock;    //wakelock锁操作spinlock锁
    oal_uint32                ul_wklock_cnt;         //持有wakelock锁的次数
#endif

#ifdef CONFIG_MMC
    struct sdio_func           *func;
#endif
    oal_mutex_stru             rx_transfer_lock;
    /*used to sg list sdio block align*/
    oal_uint8                  *sdio_align_buff;

    oal_uint64                  sdio_int_count;
    oal_uint64                  gpio_int_count;
    oal_uint64                  data_int_count;
    oal_uint64                  wakeup_int_count;
    oal_uint32                  ul_sdio_suspend;
    oal_uint32                  ul_sdio_resume;

    struct task_struct         *gpio_rx_tsk;

    /*used to process the sdio int*/
    struct semaphore            gpio_rx_sema;


    oal_void*       bus_data;
    sdio_bus_ops    bus_ops;
    hisdio_rx    credit_update_cb;

    struct sdio_scatt      scatt_info[SDIO_OPT_BUTT];

    struct sdio_msg_stru   msg[D2H_MSG_COUNT];
    oal_uint32 last_msg;

    /*This is get from sdio , must alloc for dma,
      the extend area only can access by CMD53*/
    struct hisdio_extend_func   *sdio_extend;
    struct hsdio_credit_info     sdio_credit_info;
    oal_uint32               func1_int_mask;
    struct hsdio_func1_info  func1_stat;
    struct hsdio_error_info  error_stat;

    hsdio_tx_scatt_buff scatt_buff;

};

extern struct semaphore sdio_wake_sema;

OAL_STATIC OAL_INLINE oal_void oal_sdio_claim_host(struct oal_sdio *hi_sdio)
{
#ifdef CONFIG_MMC
    sdio_claim_host(hi_sdio->func);
#endif
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_release_host(struct oal_sdio *hi_sdio)
{
#ifdef CONFIG_MMC
    sdio_release_host(hi_sdio->func);
#endif
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_rx_transfer_lock(struct oal_sdio *hi_sdio)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    mutex_lock(&hi_sdio->rx_transfer_lock);
#endif
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_rx_transfer_unlock(struct oal_sdio *hi_sdio)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    mutex_unlock(&hi_sdio->rx_transfer_lock);
#endif
}

oal_uint32 oal_sdio_get_large_pkt_free_cnt(struct oal_sdio *hi_sdio);

oal_void oal_netbuf_list_hex_dump(oal_netbuf_head_stru* head);
oal_void oal_netbuf_hex_dump(oal_netbuf_stru* netbuf);
extern oal_uint64 oal_get_gpio_int_count_para(oal_void);
OAL_STATIC OAL_INLINE oal_void oal_sdio_func1_int_mask(struct oal_sdio *hi_sdio, oal_uint32 func1_int_mask)
{
    OAL_BUG_ON(NULL == hi_sdio);
    oal_sdio_claim_host(hi_sdio);
    hi_sdio->func1_int_mask &= ~func1_int_mask;
    oal_sdio_release_host(hi_sdio);
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_func1_int_unmask(struct oal_sdio *hi_sdio, oal_uint32 func1_int_mask)
{
    OAL_BUG_ON(NULL == hi_sdio);
    oal_sdio_claim_host(hi_sdio);
    hi_sdio->func1_int_mask |= func1_int_mask;
    oal_sdio_release_host(hi_sdio);
}

#ifdef CONFIG_MMC
oal_void oal_sdio_set_state(struct oal_sdio *hi_sdio, oal_uint8 state);
oal_void oal_sdio_info_show(struct oal_sdio *hi_sdio);
oal_void oal_netbuf_list_hex_dump(oal_netbuf_head_stru* head);
oal_void oal_netbuf_hex_dump(oal_netbuf_stru* netbuf);
oal_int32 oal_sdio_build_rx_netbuf_list(struct oal_sdio *hi_sdio,
                                             oal_netbuf_head_stru   * head);
oal_void oal_gpio_intr_enable(struct oal_sdio *hi_sdio,oal_int8 enable);
oal_int32 oal_sdio_func_probe(struct oal_sdio* hi_sdio);
oal_void oal_sdio_func_remove(struct oal_sdio* hi_sdio);
oal_int32 oal_sdio_message_register(struct oal_sdio *hi_sdio,oal_uint8 msg, sdio_msg_rx cb, oal_void* data);
oal_void oal_sdio_message_unregister(struct oal_sdio *hi_sdio,
                                                            oal_uint8 msg);
oal_int32 oal_sdio_transfer_rx_register(struct oal_sdio *hi_sdio, hisdio_rx rx);
oal_void  oal_sdio_credit_update_cb_register(struct oal_sdio *hi_sdio,hisdio_rx cb);
oal_void oal_sdio_transfer_rx_unregister(struct oal_sdio *hi_sdio);
extern oal_int32 oal_sdio_transfer_tx(struct oal_sdio *hi_sdio, oal_netbuf_stru* netbuf);

oal_int32 oal_sdio_transfer_netbuf_list(struct oal_sdio *hi_sdio,
                                      oal_netbuf_head_stru * head,
                                      oal_int32 rw);

extern struct oal_sdio*  oal_sdio_init_module(oal_void* data);
extern oal_void  oal_sdio_exit_module(struct oal_sdio* hi_sdio);
extern void oal_set_thread_property(struct task_struct *p,int policy,
                                        const struct sched_param *param,
                                        long nice);
extern struct task_struct *oal_thread_create(int (*threadfn)(void *data),
                                        void                    *data,
                                        struct semaphore        *sema_sync,
                                        const char*               namefmt,
                                        oal_uint32                   policy,
                                        oal_int32                    prio,
                                        oal_int32                    cpuid);
extern void oal_thread_stop( struct task_struct      *tsk,
                          struct semaphore        *sema_sync);
oal_int32 oal_sdio_send_msg(struct oal_sdio* hi_sdio, oal_uint val);
extern struct oal_sdio* oal_get_sdio_stru(oal_void);
extern oal_uint oal_sdio_get_sleep_state(struct oal_sdio *hi_sdio);
extern oal_int32 oal_sdio_wakeup_dev(struct oal_sdio *hi_sdio);
extern oal_int32 oal_sdio_sleep_dev(struct oal_sdio *hi_sdio);
extern void oal_sdio_wake_lock(struct oal_sdio *pst_hi_sdio);
extern void oal_sdio_wake_unlock(struct oal_sdio *pst_hi_sdio);
extern oal_uint oal_sdio_wakelock_active(struct oal_sdio *pst_hi_sdio);
extern oal_int  oal_sdio_wake_release_lock(struct oal_sdio *pst_hi_sdio, oal_uint32 ul_locks);
extern oal_void oal_sdio_wakelocks_release_detect(struct oal_sdio *pst_hi_sdio);
extern oal_uint32 oal_sdio_func_max_req_size(struct oal_sdio *pst_hi_sdio);
extern oal_void oal_wlan_gpio_intr_enable(struct oal_sdio *hi_sdio,oal_uint32  ul_en);
#else
OAL_STATIC OAL_INLINE oal_void oal_sdio_set_state(struct oal_sdio *hi_sdio, oal_uint8 state)
{
    return;
}

OAL_STATIC OAL_INLINE oal_uint32 oal_sdio_func_max_req_size(struct oal_sdio *pst_hi_sdio)
{
    return 0;
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_info_show(struct oal_sdio *hi_sdio)
{
    return;
}
OAL_STATIC OAL_INLINE oal_int32 oal_sdio_send_msg(struct oal_sdio* hi_sdio, oal_uint val)
{
    return OAL_SUCC;
}
OAL_STATIC OAL_INLINE oal_int32 oal_sdio_build_rx_netbuf_list(struct oal_sdio *hi_sdio,
                                             oal_netbuf_head_stru   * head)
{
    return OAL_SUCC;
}

OAL_STATIC OAL_INLINE oal_void  oal_sdio_credit_update_cb_register(struct oal_sdio *hi_sdio, hisdio_rx cb)
{
    return;
}

OAL_STATIC OAL_INLINE oal_int32 oal_sdio_transfer_rx_register(struct oal_sdio *hi_sdio, hisdio_rx rx)
{
    return -OAL_FAIL;
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_transfer_rx_unregister(struct oal_sdio *hi_sdio)
{
}

OAL_STATIC OAL_INLINE oal_int32 oal_sdio_transfer_tx(struct oal_sdio *hi_sdio, oal_netbuf_stru* netbuf)
{
    return -OAL_FAIL;
}

OAL_STATIC OAL_INLINE oal_int32 oal_sdio_transfer_netbuf_list(struct oal_sdio *hi_sdio,
                                      oal_netbuf_head_stru * head,
                                      oal_int32 rw)
{
    return -OAL_FAIL;
}

OAL_STATIC OAL_INLINE struct oal_sdio*  oal_sdio_init_module(oal_void* data)
{
    return NULL;
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_exit_module(struct oal_sdio* hi_sdio)
{
}

OAL_STATIC OAL_INLINE oal_void oal_set_thread_property(struct task_struct *p,int policy,
                                        const struct sched_param *param,
                                        long nice)
{
}

OAL_STATIC OAL_INLINE  struct task_struct *oal_thread_create(int (*threadfn)(void *data),
                                        void                    *data,
                                        struct semaphore        *sema_sync,
                                        const char*               namefmt,
                                        oal_uint32                   policy,
                                        oal_int32                    prio,
                                        oal_int32                    cpuid)
{
    return NULL;
}

OAL_STATIC OAL_INLINE oal_void oal_thread_stop( struct task_struct      *tsk,
                          struct semaphore        *sema_sync)
{
}

OAL_STATIC OAL_INLINE oal_int32 oal_sdio_message_register(struct oal_sdio *hi_sdio,
                                                            oal_uint8 msg, sdio_msg_rx cb,
                                                            oal_void* data)
{
		return -1;
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_message_unregister(struct oal_sdio *hi_sdio,
                                                            oal_uint8 msg)
{
}

OAL_STATIC OAL_INLINE oal_int32 oal_sdio_func_probe(struct oal_sdio* hi_sdio)
{
		return -1;
}

OAL_STATIC OAL_INLINE oal_void oal_sdio_func_remove(struct oal_sdio* hi_sdio)
{
}

#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif

