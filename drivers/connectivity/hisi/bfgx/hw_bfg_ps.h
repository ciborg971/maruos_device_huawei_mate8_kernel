/******************************************************************************

          Copyright (C), 2001-2011, huawei technology limited company

 ******************************************************************************
  Filename   : hw_bfg_ps.h
  Version    : first draft
  Author     : zwx144390
  Create date: 2012-10-11
  Modify     :
  Func descr : inclue file
  Func list  :
  Modi histoy:
  1.Data     : 2012-10-11
    Author   : zwx144390
    Modify
    content  : Create File

******************************************************************************/
#ifndef __HW_BFG_PS_H__
#define __HW_BFG_PS_H__

#ifdef __cplusplus
    #if __cplusplus
        extern "C" {
    #endif
#endif

/*****************************************************************************
  Include else Head file
*****************************************************************************/
#include <linux/skbuff.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/debugfs.h>
#include "plat_type.h"

#define FEATURE_PM_DOWNLOAD_PATCH

#define DTS_COMP_HI1101_PS_NAME		"hisilicon,hisi_bfgx"

#define BT_TX_MAX_FRAME             (1500)      /* tx bt data max lenth */
#define GNSS_TX_MAX_FRAME           (3000)      /* gnss send buf max lenth */
#define FM_TX_MAX_FRAME             (512)       /* fm cmd data max lenth */
#define NFC_TX_MAX_FRAME            (512)       /* nfc cmd data max lenth */
#define IR_TX_MAX_FRAME             (5120)      /* ir cmd data max lenth */
#define DBG_TX_MAX_FRAME            (10000)     /* dbg cmd data max lenth */

#define BT_RX_MAX_FRAME             (1500)      /* RX bt data max lenth */
#define GNSS_RX_MAX_FRAME           (10000)     /* gnss recv buf max lenth */
#define FM_RX_MAX_FRAME             (512)       /* fm recv buf max lenth */
#define NFC_RX_MAX_FRAME            (512)       /* nfc recv buf max lenth */
#define IR_RX_MAX_FRAME             (5120)      /* ir recv buf max lenth */
#define DBG_RX_MAX_FRAME            (10000)     /* dbg recv buf max lenth */

/* FIXME: it depends on device's rule, it's 46+5 now,
 *        and should be modified if it's changed in device end.
*/
#define NOBT_FRAME_EXTRA_SPACE      (6)         /* 预留6字节余量 */
#define MAX_NOBT_FRAME_LEN          (51 + NOBT_FRAME_EXTRA_SPACE)/* FGNI max frame len */

#define GNSS_TX_PACKET_LIMIT        (200)
#define FM_TX_PACKET_LIMIT          (200)
#define NFC_TX_PACKET_LIMIT         (200)
#define IR_TX_PACKET_LIMIT          (200)

#define SEPRETED_RX_PKT_SEQ_ERROR   (0)
#define SEPRETED_RX_PKT_SEQ_CORRECT (1)

#define DEBUG_SKB_BUFF_LEN          (2048)
#define PUBLIC_BUF_MAX              (8*1024)      /* public buf total lenth */

#define PACKET_START_SIGNAL         (0x7e)
#define PACKET_END_SIGNAL           (0x7e)

#define BT_TX_TIMES                 (5)         /* times continue tx bt data */

/* last words type in 8 byte packet head */
#define PACKET_RX_FUNC_LAST_WORDS      (0x10)      /* rx last words from device */
#define PACKET_RX_FUNC_DUMP_STACK      (0x08)      /* rx stack dump from device */
#define PACKET_RX_FUNC_DUMP_STACK_SIZE (0x20)      /* rx stack dump size from device */
#define SYS_TOTAL_PACKET_LENTH         (0x06)      /* sys packet total lenth */

/* time in msec to wait for
 * line discipline to be installed
 */
#define HISI_LDISC_TIME             (2000)

#define RX_PACKET_CORRECT           (0)
#define RX_PACKET_CONTINUE          (1)
#define RX_PACKET_ERR               (-1)

#define OPEN_TTY_RETRY_COUNT        (5)

#define HISI_UART_DEV_NAME_LEN      (32)

#define STORE_RST_DEVICE_OVER       ('1')

/* yes or not allow reset device */
#define ALLOW_RST_DEVICE            ('1')
#define MASK_RST_DEVICE             ('0')
#define CLEAR_EXCEPTION_CNT         ('0')

#define DEFAULT_BAUD_RATE           (1000000)
#define WKUP_DEV_BAUD_RATE          (115200)
#define IR_ONLY_BAUD_RATE           (921600)

#define FLOW_CTRL_ENABLE            (1)
#define FLOW_CTRL_DISABLE           (0)

#define VERSION_FPGA                (0)
#define VERSION_ASIC                (1)

/* timeout for gnss read */
#define GNSS_SET_READ_TIME          (1)
#define GNSS_READ_DEFAULT_TIME      (1000)
#define GNSS_MAX_READ_TIME          (10000)

/* timeout for fm read */
#define FM_SET_READ_TIME            (1)
#define FM_READ_DEFAULT_TIME        (1000)
#define FM_MAX_READ_TIME            (10000)

/* timeout for dbg read */
#define DBG_READ_DEFAULT_TIME       (500)

#define LEN_LOW_BYTE(len)           ((uint8)(len & 0xff))
#define LEN_HIGH_BYTE(len)          ((uint8)((len & 0xff00)>>8))

/* define for tx and rx packet queue */
#define TX_HIGH_QUEUE               (1)
#define TX_LOW_QUEUE                (2)
#define RX_GNSS_QUEUE               (3)
#define RX_FM_QUEUE                 (4)
#define RX_BT_QUEUE                 (5)
#define RX_DBG_QUEUE                (6)
#define RX_NFC_QUEUE                (7)
#define RX_IR_QUEUE                 (8)

/* max number for tx and rx packet queue */
#define TX_HIGH_QUE_MAX_NUM         (50)
#define TX_LOW_QUE_MAX_NUM          (250)
#define RX_GNSS_QUE_MAX_NUM         (50)
#define RX_FM_QUE_MAX_NUM           (50)
#define RX_BT_QUE_MAX_NUM           (50)
#define RX_DBG_QUE_MAX_NUM          (50)
#define RX_NFC_QUE_MAX_NUM          (50)
#define RX_IR_QUE_MAX_NUM           (50)

/* timeout when after download patch */
#define WAIT_BFGX_BOOTOK_TIME       (1000)
#define DEV_3IN1_OPEN_TIME          (5000)
#define WAIT_BT_OPEN_TIME           (3000)
#define WAIT_BT_CLOSE_TIME          (3000)
#define WAIT_FM_OPEN_TIME           (3000)
#define WAIT_FM_CLOSE_TIME          (3000)
#define WAIT_GNSS_OPEN_TIME         (3000)
#define WAIT_GNSS_CLOSE_TIME        (3000)
#define WAIT_IR_OPEN_TIME           (3000)
#define WAIT_IR_CLOSE_TIME          (3000)
#define WAIT_NFC_OPEN_TIME          (1000)
#define WAIT_NFC_CLOSE_TIME         (2000)

#define WAIT_WIFI_OPEN_TIME         (3000)
#define WAIT_WIFI_CLOSE_TIME        (1000)
#define WAIT_BFGX_CLOSE_TIME        (1000)


#define RELEASE_DELAT_TIMES         (5)

#define BT_SLEEP_TIME               (5)
#define POWER_ON_STATE              (1)
#define POWER_OFF_STATE             (0)
#define BFG_TIMER_ON                (1)
#define BFG_TIMER_OFF               (0)

#define BFG_POWER_GPIO_DOWN         (0)
#define BFG_POWER_GPIO_UP           (1)

#define BT_WRITE_FLAG               (0)
#define FM_WRITE_FLAG               (1)
#define GNSS_WRITE_FLAG             (2)
#define COEX_WRITE_FLAG             (3)
#define DEBUG_WRITE_FLAG            (4)
#define NFC_WRITE_FLAG              (5)
#define IR_WRITE_FLAG               (6)

#define NONEED_SET_FLAG             (0)
#define NEED_SET_FLAG               (1)


enum BFGN_DATA_MSG_TYPE_ENUM
{
    SYS_MSG             = 0x00, /* 系统串口消息 */
    BT_MSG              = 0x01, /* BT串口消息 */
    GNSS_First_MSG      = 0x02, /* GNSS串口消息，第一个分段消息 */
    GNSS_Common_MSG     = 0x03, /* GNSS串口消息，中间分段消息 */
    GNSS_Last_MSG       = 0x04, /* GNSS串口消息，最后一个分段消息 */
    FM_FIRST_MSG        = 0x05, /* FM串口消息，第一个分段消息 */
    FM_COMMON_MSG       = 0x06, /* FM串口消息，中间分段消息 */
    FM_LAST_MSG         = 0x07, /* FM串口消息，最后一个分段消息 */
    IR_FIRST_MSG        = 0x08, /* 红外串口消息，第一个分段消息 */
    IR_COMMON_MSG       = 0x09, /* 红外串口消息，中间分段消息 */
    IR_LAST_MSG         = 0x0A, /* 红外串口消息，最后一个分段消息 */
    NFC_First_MSG       = 0x0B, /* NFC串口消息，第一个分段消息 */
    NFC_Common_MSG      = 0x0C, /* NFC串口消息，中间分段消息 */
    NFC_Last_MSG        = 0x0D, /* NFC串口消息，最后一个分段消息 */
    OML_MSG             = 0x0E, /* 可维可测消息 */

    MSG_BUTT,
};


/* below is tx sys content define */
enum platform_event_enum
{
    SYS_CFG_OPEN_BT                    = 0,
    SYS_CFG_CLOSE_BT                   = 1,
    SYS_CFG_OPEN_GNSS                  = 2,
    SYS_CFG_CLOSE_GNSS                 = 3,
    SYS_CFG_OPEN_FM                    = 4,
    SYS_CFG_CLOSE_FM                   = 5,
    SYS_CFG_OPEN_NFC                   = 6,
    SYS_CFG_CLOSE_NFC                  = 7,
    SYS_CFG_OPEN_IR                    = 8,
    SYS_CFG_CLOSE_IR                   = 9,
    SYS_CFG_OPEN_WIFI                  = 0xa,     /* host通过uart打开WCPU */
    SYS_CFG_CLOSE_WIFI                 = 0xb,     /* host通过uart关闭WCPU */
    SYS_CFG_READ_STACK                 = 0xc,     /* host通过uart读栈 */
    SYS_CFG_QUERY_RF_TEMP              = 0xd,     /* host通过uart查询rf温度 */
    SYS_CFG_ALLOWDEV_SLP               = 0xe,     /* host allow device sleep */
    SYS_CFG_DISALLOW_SLP               = 0xf,     /* host disallow device sleep */
	SYS_CFG_SHUTDOWN_SLP               = 0x10,    /* shutdown bcpu */
	SYS_CFG_PL_ENABLE_PM               = 0x11,    /* enable plat dev lowpower feature */
	SYS_CFG_PL_DISABLE_PM              = 0x12,    /* disable plat dev lowpower feature */
	SYS_CFG_BT_ENABLE_PM               = 0x13,    /* enable BT dev lowpower feature */
	SYS_CFG_BT_DISABLE_PM              = 0x14,    /* disable BT dev lowpower feature */
	SYS_CFG_GNSS_ENABLE_PM             = 0x15,    /* enable GNSS dev lowpower feature */
	SYS_CFG_GNSS_DISABLE_PM            = 0x16,    /* disable GNSS dev lowpower feature */
	SYS_CFG_NFC_ENABLE_PM              = 0x17,    /* enable NFC dev lowpower feature */
	SYS_CFG_NFC_DISABLE_PM             = 0x18,    /* disable NFC dev lowpower feature */

	SYS_CFG_DEV_PANIC                  = 0x19,    /* cause device into exception */

    PL_EVT_BUTT
};

/* below is rx sys content define from device */
enum SYS_INF_MSG_VALUE_ENUM
{
    SYS_INF_PF_INIT                 =  0x00,        /* 平台软件初始化完成 */
    SYS_INF_BT_INIT                 =  0x01,        /* BT软件初始化完成 */
    SYS_INF_GNSS_INIT               =  0x02,        /* GNSS软件初始化完成 */
    SYS_INF_FM_INIT                 =  0x03,        /* FM软件初始化完成 */
    SYS_INF_BT_DISABLE              =  0x04,        /* BT禁能 */
    SYS_INF_GNSS_DISABLE            =  0x05,        /* GNSS禁能 */
    SYS_INF_FM_DISABLE              =  0x06,        /* FM禁能 */
    SYS_INF_BT_EXIT                 =  0x07,        /* BT退出 */
    SYS_INF_GNSS_EXIT               =  0x08,        /* GNSS退出 */
    SYS_INF_FM_EXIT                 =  0x09,        /* FM退出 */
    SYS_INF_GNSS_WAIT_DOWNLOAD      =  0x0A,        /* 等待GNSS代码下载 */
    SYS_INF_GNSS_DOWNLOAD_COMPLETE  =  0x0B,        /* GNSS代码下载完毕 */
    SYS_INF_BFG_HEART_BEAT          =  0x0C,        /* 心跳信号 */
    SYS_INF_DEV_AGREE_HOST_SLP      =  0x0D,        /* device回复host可睡 */
    SYS_INF_DEV_NOAGREE_HOST_SLP    =  0x0E,        /* device回复host不可睡 */
    SYS_INF_WIFI_OPEN               =  0x0F,        /* WCPU上电完成 */
    SYS_INF_IR_INIT                 =  0x10,        /* IR软件初始化完成 */
    SYS_INF_IR_EXIT                 =  0x11,        /* IR退出 */
    SYS_INF_NFC_INIT                =  0x12,        /* NFC软件初始化完成 */
    SYS_INF_NFC_EXIT                =  0x13,        /* NFC退出 */
    SYS_INF_WIFI_CLOSE              =  0x14,        /* WCPU下电完成*/
    SYS_INF_RF_TEMP_NORMAL          =  0x15,        /* RF温度正常*/
    SYS_INF_RF_TEMP_OVERHEAT        =  0x16,        /* RF温度过热*/


    SYS_INF_BUTT,
};

typedef enum
{
   BFGX_BT      = 0x00,
   BFGX_FM      = 0x01,
   BFGX_GNSS    = 0x02,
   BFGX_IR      = 0x03,
   BFGX_NFC     = 0x04,
   BFGX_BUTT    = 0x05,
}bfgx_subsys_type_enum;

typedef enum {
    SUBSYS_STATE_SHUTDOWN = 0,
    SUBSYS_STATE_OPEN     = 1,
    SUBSYS_STATE_BUTT     = 2,
}subsys_state_enum;

typedef enum
{
    RX_SEQ_NULL  = 0,
    RX_SEQ_START = 1,
    RX_SEQ_INT   = 2,
    RX_SEQ_LAST  = 3,

    RX_SEQ_BUTT,
}bfgx_rx_sepreted_pkt_type;

/*****************************************************************************
  3 STRUCT define
*****************************************************************************/
struct ps_pm_s {
    struct pm_drv_data * pm_priv_data;
    struct ps_core_s * ps_core_data;
    int32 (*change_baud_rate)(int64 baud_rate, uint8 enable_flowctl);
    void  (*bfg_mutex_lock)(uint8);
    int32 (*bfg_power_set)(uint8, uint8);
    void  (*bfg_wake_lock)(void);
    void  (*bfg_wake_unlock)(void);
    int32 (*bfgx_dev_state_get)(void);
    void  (*bfgx_dev_state_set)(uint8);
    int32 (*operate_beat_timer)(uint8);
    void  (*bfg_spin_lock)(uint8);
    void  (*bfgx_uart_state_set)(uint8);
    int8  (*bfgx_uart_state_get)(void);
};

struct ps_packet_head {
    uint8  packet_start;
    uint8  func_type;
    uint16 packet_len;
};

struct ps_packet_end {
    uint8 packet_end;
};

struct bfgx_sepreted_rx_st
{
    spinlock_t sepreted_rx_lock;
    uint8 *rx_buf_ptr;
    uint8 *rx_buf_org_ptr;
    uint16 rx_pkt_len;
    uint16 rx_buf_all_len;
    uint8  rx_prev_seq;
};

struct st_bfgx_data
{
    struct sk_buff_head rx_queue;
    struct completion wait_opened;
    struct completion wait_closed;
    struct bfgx_sepreted_rx_st sepreted_rx;  /* bfgx分包接收数据结构 */
    wait_queue_head_t rx_wait;               /* wait queue for rx packet */
    atomic_t subsys_state;
};

/**
 * struct ps_core_s - PS core internal structure
 * @tty: tty provided by the TTY core for line disciplines.
 * @txq: the list of skbs which needs to be sent onto the TTY.
 * @pm_data: reference to the parent encapsulating structure.
 *
 */
struct ps_core_s {
    struct ps_pm_s *ps_pm;
    struct tty_struct *tty;
    struct st_bfgx_data bfgx_info[BFGX_BUTT];
    /* queue head define for all sk_buff */
    struct sk_buff_head tx_high_seq;
    struct sk_buff_head tx_low_seq;

    struct mutex bfgx_mutex;
    //struct completion bfgx_init_ok;

    struct sk_buff_head rx_dbg_seq;
    /* wait queue for rx packet */
    wait_queue_head_t rx_dbg_wait;
    atomic_t dbg_func_has_open;
    uint16 dbg_read_delay;

    /* define for new workqueue */
    struct workqueue_struct *ps_tx_workqueue;
    /* define new work struct */
    struct work_struct tx_skb_work;

    /* wait for wifi opened */
    struct completion wait_wifi_opened;
    /* wait for wifi closed */
    struct completion wait_wifi_closed;

    spinlock_t rx_lock;

    /* mark user doing something on node */
    atomic_t node_visit_flag;

    atomic_t throttle_flag;

    void  *pm_data;

    /* define variable for decode rx data from uart */
    uint8  rx_pkt_type;
    uint16 rx_pkt_total_len;
    uint16 rx_have_recv_pkt_len;
    uint16 rx_have_del_public_len;
    uint8 *rx_decode_tty_ptr;
    uint8 *rx_public_buf_org_ptr;
    uint8 *rx_decode_public_buf_ptr;

    uint8  tty_have_open;
    uint16 gnss_read_delay;
    uint16 fm_read_delay;
};

/**
 * struct ps_plat_s - the PM internal data, embedded as the
 *  platform's drv data. One for each PS device in the system.
 * @pm_pdev: the platform device added in one of the board-XX.c file
 *  in arch/XX/ directory, 1 for each PS device.
 * @ldisc_installed: completion handler to notify that the OCTTY accepted
 *  the request to install ldisc, notify from tty_open which suggests
 *  the ldisc was properly installed.
 * @core_data: PS core's data, which mainly is the tty's disc_data
 *
 */
struct ps_plat_s {
    struct platform_device *pm_pdev;
    struct completion ldisc_installed;
    struct completion change_baud_rate;
    struct ps_core_s *core_data;
    uint8  dev_name[HISI_UART_DEV_NAME_LEN];
    uint64 baud_rate;
    uint8  ldisc_install;
    uint8  flow_cntrl;
    uint16 fill_byte1;
};

/**
 * struct hw_ps_plat_data - platform data shared between PS driver and
 *  platform specific board file which adds the PS device.
 * @dev_name: The UART/TTY name to which chip is interfaced. (eg: /dev/ttyS1)
 * @flow_cntrl: Should always be 1, since UART's CTS/RTS is used for PM
 *  purposes.
 * @baud_rate: The baud rate supported by the Host UART controller, this will
 *  be shared across with the chip via a HCI VS command from User-Space Init
 *  Mgr application.
 * @suspend:
 * @resume: legacy PM routines hooked to platform specific board file, so as
 *  to take chip-host interface specific action.
 * @set_bt_power: set gpio BT_EN to high.
 */
struct hw_ps_plat_data {
    int32 (*suspend)(struct platform_device *, pm_message_t);
    int32 (*resume)(struct platform_device *);
    void  (*set_bt_power)(void);
    void  (*set_fm_power)(void);
    void  (*set_gnss_power)(void);
    void  (*clear_bt_power)(void);
    void  (*clear_fm_power)(void);
    void  (*clear_gnss_power)(void);
    uint8  dev_name[HISI_UART_DEV_NAME_LEN]; /* uart name */
    uint64 baud_rate;
    uint8  flow_cntrl; /* flow control flag */
    uint16 fill_byte1;
    uint8  fill_byte2;
};

extern int32 (*tty_recv)(void *, const uint8 *, int32);

/*****************************************************************************
  Function declare
*****************************************************************************/
extern struct platform_device *hw_ps_device;

extern int32 ps_pm_register(struct ps_pm_s *new_pm);

extern int32 ps_pm_unregister(struct ps_pm_s *del_pm);

int32 ps_get_plat_reference(struct ps_plat_s **plat_data);

extern int32 uart_wifi_open(void);
extern int32 uart_wifi_close(void);
extern int32 uart_bfgx_close_cmd(void);

/**
 * ps_write_tty -
 * point this to tty->driver->write or tty->ops->write
 * depending upon the kernel version
 */
int32 ps_write_tty(struct ps_core_s*, const uint8*, int32);
int32 ps_core_tx_attemper(struct ps_core_s *ps_core_d);

/* init, exit entry funcs called from PM */
int32 ps_core_init(struct ps_core_s **);
int32 ps_core_exit(struct ps_core_s *);

/**
 * functions called when 1 of the protocol drivers gets
 * registered, these need to communicate with OCTTY to request
 * ldisc installed
 */

int32 ps_get_core_reference(struct ps_core_s **core_data);
int32 ps_core_recv(void *disc_data, const uint8 *data, int32 count);
int32 ps_core_recv_uart_test(void *disc_data, const uint8 *data, int32 count);
int32 ps_tx_sys_cmd(struct ps_core_s *ps_core_d, uint8 type, uint8 content);
int32 ps_tx_gnssbuf(struct ps_core_s *ps_core_d, const int8 __user *buf, size_t count);
int32 ps_tx_nfcbuf(struct ps_core_s *ps_core_d, const int8 __user *buf, size_t count);
int32 ps_tx_irbuf(struct ps_core_s *ps_core_d, const int8 __user *buf, size_t count);
int32 ps_tx_fmbuf(struct ps_core_s *ps_core_d, const int8 __user *buf, size_t count);
int32 ps_skb_enqueue(struct ps_core_s *ps_core_d, struct sk_buff *skb, uint8 type);
int32 ps_add_packet_head(uint8 *buf, uint8 type, uint16 lenth);
int32 ps_change_baud_rate_complete(void *pm_data);
void  ps_kfree_skb(struct ps_core_s *ps_core_d, uint8 type);
struct sk_buff *ps_alloc_skb(uint16 len);
struct sk_buff *ps_skb_dequeue(struct ps_core_s *ps_core_d, uint8 type);
int32 ps_patch_write(uint8 *data, int32 count);
int32 ps_set_sys_packet(uint8 *buf, uint8 type, uint8 content);
int32 ps_change_uart_baud_rate(int64 baud_rate, uint8 enable_flowctl);
uint8 check_bfg_not_booting(struct ps_core_s *ps_core_d);
void host_allow_bfg_sleep(struct ps_core_s *ps_core_d);
uint8  bfgx_wakeup_device(struct ps_core_s *ps_core_d, uint8 type);
int32 ps_check_packet_head(struct ps_core_s *ps_core_d, uint8 *buf_ptr, int32 count);
bool ps_chk_bfg_active(struct ps_core_s *ps_core_d);
int32 prepare_to_visit_node(struct ps_core_s *ps_core_d);
int32 post_to_visit_node(struct ps_core_s *ps_core_d);
void reset_uart_rx_buf(void);

extern struct kset	  *devices_kset;

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
#endif /* HW_BFG_PS_H */


