

#ifndef __OAL_HCC_HOST_IF_H
#define __OAL_HCC_HOST_IF_H

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif
#include "oal_util.h"
#include "oal_net.h"

#include "oal_sdio_host_if.h"
#include "oal_hcc_comm.h"
#include "oal_workqueue.h"

#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/kernel.h>
#endif

#ifdef _PRE_WLAN_TCP_OPT
#define TCP_ACK_WAIT_HCC_SCHDULE_COUNT (2)
#endif
#define CONFIG_CREDIT_MSG_FLOW_WATER_LINE   (60)

#define HCC_FLUSH_ALL   (~0UL)

/*hcc tx transfer flow control*/
#define HCC_FC_NONE         (0x0)   /*对调用者不进行流控，netbuf一直缓冲在hcc队列中,这种类型的数据包不宜过多*/
#define HCC_FC_WAIT         (0x1)   /*阻塞等待，如果是在中断上下文调用，该标记被自动清除,非中断上下文生效*/
#define HCC_FC_NET          (0x2)   /*对于网络层的流控*/
#define HCC_FC_DROP         (0x4)   /*流控采用丢包方式,流控时返回成功*/
#define HCC_FC_ALL          (HCC_FC_WAIT|HCC_FC_NET|HCC_FC_DROP)

struct hcc_transfer_param
{
    oal_uint32  main_type;
    oal_uint32  sub_type;
    oal_uint32  extend_len;
    oal_uint32  fc_flag;/*流控标记*/
    oal_uint32  queue_id;/*期望进入的队列号,*/
};

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL

typedef enum _hcc_queue_type_
{
    CTRL_QUEUE = 0,
    DATA_HI_QUEUE,
    DATA_LO_QUEUE,

    DATA_TCP_DATA_QUEUE,
    DATA_TCP_ACK_QUEUE,

    DATA_UDP_BK_QUEUE,
    DATA_UDP_BE_QUEUE,
    DATA_UDP_VI_QUEUE,
    DATA_UDP_VO_QUEUE,

    HCC_QUEUE_COUNT
} hcc_queue_type;

#else

typedef enum _hcc_queue_type_
{
    DATA_HI_QUEUE = 0,
    DATA_LO_QUEUE =1,
    HCC_QUEUE_COUNT
} hcc_queue_type;

#endif
#if 0
#define HCC_TX_PARAM_INITIALIZER(name,mtype,stype,ext_len,arg_flag,queueid) \
        do{\
            name.main_type = mtype;\
            name.sub_type =  stype;\
            name.extend_len = ext_len;\
            name.fc_flag = arg_flag;\
            name.queue_id = queueid;\
        }while(0)

/*default*/
#define DECLARE_HCC_TX_PARAM_DEFAULT(name)					\
	        struct hcc_transfer_param name = {\
            .fc_flag = HCC_FC_NONE,\
            .queue_id = DATA_LO_QUEUE,\
        }
#endif

#define DECLARE_HCC_TX_PARAM_INITIALIZER(name,mtype,stype,ext_len,arg_flag,queueid)					\
	        struct hcc_transfer_param name;\
			hcc_hdr_param_init(&name,mtype,stype,ext_len,arg_flag,queueid);

/*the macro to set hcc hdr*/
OAL_STATIC OAL_INLINE oal_void  hcc_hdr_param_init(struct hcc_transfer_param* param,
                                                        oal_uint32 main_type,
                                                        oal_uint32 sub_type,
                                                        oal_uint32 extend_len,
                                                        oal_uint32 fc_flag,
                                                        oal_uint32 queue_id)
{
    //OAL_BUG_ON(main_type >= HCC_ACTION_TYPE_BUTT);
    //OAL_WARN_ON(extend_len > HCC_HDR_RESERVED_MAX_LEN);
    param->main_type = main_type;
    param->sub_type = sub_type;
    param->extend_len = extend_len;
    param->fc_flag = fc_flag;
    param->queue_id = queue_id;
}

typedef enum _hcc_chan_type_
{
    HCC_TX,
    HCC_RX,
    HCC_DIR_COUNT
} hcc_chan_type;
#define HCC_GET_CHAN_STRING(type) ((HCC_TX==(type))?"tx":"rx")

typedef enum _hcc_send_mode_
{
    hcc_single_send  = 0,
    hcc_assem_send,
    hcc_mode_count
} hcc_send_mode;

typedef struct _hcc_flow_ctrl_
{
    oal_uint8                       flowctrl_flag;
    oal_uint8                       enable;
    oal_uint16                      is_stopped;
    oal_uint16                      low_waterline;
    oal_uint16                      high_waterline;
} hcc_flow_ctrl;

typedef struct _hcc_trans_queue_
{
    /*transfer pkts limit every loop*/
    oal_uint32                  burst_limit;
    hcc_flow_ctrl               flow_ctrl;
    hcc_send_mode               send_mode;
    oal_uint32                  total_pkts;
    oal_uint32                  loss_pkts;
    oal_netbuf_head_stru        data_queue;
    oal_spin_lock_stru          data_queue_lock;
    wlan_net_queue_type         wlan_queue_id;
} hcc_trans_queue;

#define HCC_TX_ASSEM_INFO_MAX_NUM  (HISDIO_HOST2DEV_SCATT_MAX + 1)
#define HCC_RX_ASSEM_INFO_MAX_NUM    (HISDIO_DEV2HOST_SCATT_MAX + 1)
typedef struct _hcc_tx_assem_info_{
    /*The +1 for the single pkt*/
    oal_uint32                       info[HCC_TX_ASSEM_INFO_MAX_NUM];

    /*The max support assemble pkts*/
    oal_uint32                      assemble_max_count;
    /*next assem pkts count*/
    /*oal_uint32                      assembled_cnt;*/
    /*netx assem pkts list*/
    oal_netbuf_head_stru            assembled_head;
    /*the queue is assembling*/
    hcc_queue_type                  assembled_queue_type;

} hcc_tx_assem_info;

typedef struct _hcc_rx_assem_info_{
    oal_uint32                       info[HCC_RX_ASSEM_INFO_MAX_NUM];
} hcc_rx_assem_info;

typedef struct _hcc_netbuf_stru_
{
    oal_netbuf_stru* pst_netbuf;
    oal_int32        len;/*for hcc transfer*/
}hcc_netbuf_stru;

typedef oal_int32 (* hcc_rx_pre_do)(oal_uint8 stype, hcc_netbuf_stru* pst_netbuf, oal_uint8 **pre_do_context);
typedef oal_int32 (* hcc_rx_post_do)(oal_uint8 stype, hcc_netbuf_stru* pst_netbuf, oal_uint8 *pre_do_context);

typedef struct _hcc_rx_action_
{
    oal_uint32          pkts_count;
    hcc_rx_pre_do       pre_do;
    hcc_rx_post_do      post_do;
    oal_void            *context;/*the callback argument*/
}hcc_rx_action;

typedef struct _hcc_rx_action_info_{
    hcc_rx_action          action[HCC_ACTION_TYPE_BUTT];
} hcc_rx_action_info;

typedef struct _hcc_trans_queues_
{
    hcc_trans_queue              queues[HCC_QUEUE_COUNT];
} hcc_trans_queues;

#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
typedef oal_bool_enum_uint8 (*hcc_flowctl_get_mode)(oal_void);
oal_void hcc_flowctl_get_device_mode_register(hcc_flowctl_get_mode get_mode);

typedef oal_void (*hcc_flowctl_start_subq)(oal_uint16 us_queue_idx);
typedef oal_void (*hcc_flowctl_stop_subq)(oal_uint16 us_queue_idx);
oal_void hcc_flowctl_operate_subq_register(hcc_flowctl_start_subq start_subq, hcc_flowctl_stop_subq stop_subq);
#endif

typedef oal_void (*flowctrl_cb)(oal_void);

typedef struct _hcc_tx_flow_ctrl_info_
{
    oal_uint32 flowctrl_flag;
    oal_uint32 flowctrl_on_count;
    oal_uint32 flowctrl_off_count;
    oal_uint32 flowctrl_reset_count;
    oal_wait_queue_head_stru   wait_queue;
    flowctrl_cb net_stopall;
    flowctrl_cb net_startall;
#ifdef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
    hcc_flowctl_get_mode    get_mode;
    hcc_flowctl_stop_subq   stop_subq;
    hcc_flowctl_start_subq  start_subq;
#endif
    oal_timer_list_stru   flow_timer;
    oal_ulong             timeout;
    oal_delayed_work  worker;
	oal_spin_lock_stru lock;
}hcc_tx_flow_ctrl_info;

typedef struct _hcc_thread_stat_
{
    oal_uint64  wait_event_block_count;
    oal_uint64  wait_event_run_count;
    oal_uint64  loop_have_data_count;
    oal_uint64  loop_no_data_count;/*空转*/
}hcc_thread_stat;

struct hcc_transfer_handler
{
    struct task_struct         *hcc_transfer_thread;
    oal_wait_queue_head_stru    hcc_transfer_wq;
#ifdef _PRE_CONFIG_WLAN_THRANS_THREAD_DEBUG
    hcc_thread_stat             thread_stat;
#endif
    hcc_trans_queues            hcc_queues[HCC_DIR_COUNT];
    hcc_tx_assem_info           tx_assem_info;
    hcc_rx_assem_info           rx_assem_info;
    hcc_tx_flow_ctrl_info       tx_flow_ctrl;
    hcc_rx_action_info          rx_action_info;
};

typedef oal_int32 (*hcc_rx_cb)(oal_netbuf_stru* netbuf,
                                    struct hcc_header * hdr,
                                    oal_void* data);

struct hcc_tx_assem_descr{
    oal_uint8                   descr_num;
    oal_netbuf_head_stru        tx_assem_descr_hdr;
};
typedef oal_void (*hcc_sched_transfer_func)(oal_void);
typedef oal_int32 (*hmac_tcp_ack_process_func)(oal_void);
typedef oal_bool_enum_uint8 (*hmac_tcp_ack_need_schedule_func)(oal_void);
struct hcc_handler
{
    oal_atomic                  tx_seq;
    oal_void*                   hi_sdio;
    oal_uint                    hdr_rever_max_len;

    oal_mutex_stru              tx_transfer_lock;
#ifdef CONFIG_HAS_WAKELOCK
    struct wake_lock            st_wklock_hcc_tx;        //hcc tx wakelock锁
#endif
    struct hcc_transfer_handler hcc_transer_info;

    /*the tx descr info, first descr*/
    struct hcc_tx_assem_descr   tx_descr_info;
    hmac_tcp_ack_process_func p_hmac_tcp_ack_process_func;
    hmac_tcp_ack_need_schedule_func p_hmac_tcp_ack_need_schedule_func;
};


#define HCC_TC_TX_PKT_FLAG  (0x5A)
#define HCC_TC_RX_PKT_FLAG  (0xA5)
#define HCC_TC_TX_TCM_FLAG  (0xEF)
#define HCC_TC_RX_TCM_FLAG  (0xFE)

typedef sdio_msg_rx hcc_msg_rx;

oal_int32 hcc_tx(struct hcc_handler* hcc, oal_netbuf_stru* netbuf, struct hcc_transfer_param* param);
#ifdef _PRE_WLAN_TCP_OPT
oal_int32 hcc_thread_process(struct hcc_handler *hcc);
oal_int32 hcc_transfer_thread(oal_void *data);
#endif
#ifndef _PRE_WLAN_FEATURE_OFFLOAD_FLOWCTL
oal_void hcc_tx_flow_ctrl_cb_register(flowctrl_cb stopall, flowctrl_cb startall);
#endif

struct hcc_handler* hcc_module_init(oal_void);

oal_void hcc_tx_assem_info_reset(struct hcc_handler *hcc);
oal_void hcc_rx_assem_info_reset(struct hcc_handler *hcc);
oal_void hcc_assem_info_reset(struct hcc_handler* hcc);

oal_void hcc_module_exit(struct hcc_handler*);


oal_int32 hcc_message_register(struct hcc_handler* hcc, oal_uint8 msg,
                                    hcc_msg_rx cb, oal_void* data);

/*获取默认的HCC通道句柄*/
extern struct hcc_handler* hcc_get_default_handler(oal_void);

OAL_STATIC OAL_INLINE void hcc_tx_transfer_lock(struct hcc_handler *hcc)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    mutex_lock(&hcc->tx_transfer_lock);
#endif
}

OAL_STATIC OAL_INLINE void hcc_tx_transfer_unlock(struct hcc_handler *hcc)
{
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    mutex_unlock(&hcc->tx_transfer_lock);
#endif
}

OAL_STATIC OAL_INLINE void hcc_transfer_lock(struct hcc_handler *hcc)
{
    OAL_BUG_ON(!hcc);
    oal_sdio_rx_transfer_lock((struct oal_sdio *)hcc->hi_sdio);
    hcc_tx_transfer_lock(hcc);
}

OAL_STATIC OAL_INLINE void hcc_transfer_unlock(struct hcc_handler *hcc)
{
    OAL_BUG_ON(!hcc);
    hcc_tx_transfer_unlock(hcc);
    oal_sdio_rx_transfer_unlock((struct oal_sdio *)hcc->hi_sdio);
}



OAL_STATIC OAL_INLINE oal_void hcc_sched_transfer(struct hcc_handler *hcc)
{
    OAL_BUG_ON(!hcc);
    /*OAL_IO_PRINT("sched hcc transfer\n");*/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
    wake_up_interruptible(&hcc->hcc_transer_info.hcc_transfer_wq);
#endif
}

extern oal_int32 hcc_rx_register(struct hcc_handler *hcc, oal_uint8 mtype, hcc_rx_post_do post_do, hcc_rx_pre_do pre_do);
extern oal_int32 hcc_rx_unregister(struct hcc_handler *hcc, oal_uint8 mtype);
extern oal_void hcc_tx_wlan_queue_map_set(struct hcc_handler* hcc,hcc_queue_type hcc_queue_id,wlan_net_queue_type wlan_queue_id);
#ifdef _PRE_CONFIG_CONN_HISI_SYSFS_SUPPORT
extern oal_int32  hcc_test_init_module(struct hcc_handler* hcc);
extern oal_void  hcc_test_exit_module(struct hcc_handler* hcc);
#else
/*function stub*/
OAL_STATIC OAL_INLINE oal_int32  hcc_test_init_module(struct hcc_handler* hcc)
{
    OAL_REFERENCE(hcc);
    return OAL_SUCC;
}

OAL_STATIC OAL_INLINE oal_void  hcc_test_exit_module(struct hcc_handler* hcc)
{
    OAL_REFERENCE(hcc);
    return;
}
#endif

#if (_PRE_MULTI_CORE_MODE_OFFLOAD_DMAC == _PRE_MULTI_CORE_MODE)
extern oal_void hcc_print_device_mem_info(oal_void);
#endif

#define HCC_NETBUF_RESERVED_ROOM_SIZE   (HCC_HDR_TOTAL_LEN+HISDIO_H2D_SCATT_BUFFLEN_ALIGN)
#define hcc_netbuf_alloc(ul_size)   oal_netbuf_alloc(ul_size + HCC_NETBUF_RESERVED_ROOM_SIZE,HCC_NETBUF_RESERVED_ROOM_SIZE,0)

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of oal_hcc_if.h */
