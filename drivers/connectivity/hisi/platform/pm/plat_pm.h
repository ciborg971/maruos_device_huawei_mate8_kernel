/******************************************************************************

          Copyright (C), 2001-2011, huawei technology limited company

 ******************************************************************************
  Filename   : plat_pm.h
  Version    : first draft
  Author     : cwx145522
  Create date: 2012-12-10
  Modify     :
  Func descr : inclue file
  Func list  :
  Modi histoy:
  1.Data     : 2015-04-10
    Author   : cwx145522
    Modify
    content  : Create File

******************************************************************************/

#ifndef __PLAT_PM_H__
#define __PLAT_PM_H__

/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/wakelock.h>

#include "plat_pm_wlan.h"
#include "hw_bfg_ps.h"
#include "board.h"
/*****************************************************************************
  2 Define macro
*****************************************************************************/
/*#define ENABLE_BFG_LOWPOWER_FEATURE*/
#define BFG_LOCK_NAME                   "bfg_wake_lock"

#define SDIO_INIT_OK                    0x02
/*
#define BT_STATE_SHUTDOWN               0x10
#define BT_STATE_BOOTUP                 0x11
#define GNSS_STATE_SHUTDOWN             0x20
#define GNSS_STATE_BOOTUP               0x21
#define FM_STATE_SHUTDOWN               0x30
#define FM_STATE_BOOTUP                 0x31
*/

#define WLAN_STATE_SHUTDOWN             0x40
#define WLAN_STATE_BOOTUP               0x41
#define WLAN_STATE_WAKEUP_START         0x42
#define WLAN_STATE_WAKEUP_END           0x43

/*
#define NFC_STATE_SHUTDOWN              0x50
#define NFC_STATE_BOOTUP                0x51
#define IR_STATE_SHUTDOWN               0x60
#define IR_STATE_BOOTUP                 0x61
*/

#define SUCCESS                         (0)
#define FAILURE                         (1)

#define GNSS_AGREE_SLEEP                (1)
#define GNSS_NOT_AGREE_SLEEP            (0)

#define BFGX_SLEEP                      (0)
#define BFGX_ACTIVE                     (1)

#define UART_READY                      (1)
#define UART_NOT_READY                  (0)

#define HOST_DISALLOW_TO_SLEEP          (0)
#define HOST_ALLOW_TO_SLEEP             (1)

#define BFGX_PM_ENABLE                  (1)
#define BFGX_PM_DISABLE                 (0)

#define BT_STATE_FLAG                   ((uint32)(1 << 0))
#define GNSS_STATE_FLAG                 ((uint32)(1 << 1))
#define FM_STATE_FLAG                   ((uint32)(1 << 2))
#define WLAN_STATE_FLAG                 ((uint32)(1 << 3))
#define NFC_STATE_FLAG                  ((uint32)(1 << 4))
#define IR_STATE_FLAG                   ((uint32)(1 << 5))
#define BT_GNSS_FM_IR_STATE_FLAG        (BT_STATE_FLAG | GNSS_STATE_FLAG | FM_STATE_FLAG | IR_STATE_FLAG)
#define BT_GNSS_FM_NFC_STATE_FLAG       (BT_STATE_FLAG | GNSS_STATE_FLAG | FM_STATE_FLAG | NFC_STATE_FLAG)
#define BT_GNSS_NFC_IR_STATE_FLAG       (BT_STATE_FLAG | GNSS_STATE_FLAG | NFC_STATE_FLAG | IR_STATE_FLAG)
#define BT_FM_NFC_IR_STATE_FLAG         (BT_STATE_FLAG | FM_STATE_FLAG | NFC_STATE_FLAG | IR_STATE_FLAG)
#define GNSS_FM_NFC_IR_STATE_FLAG       (GNSS_STATE_FLAG | FM_STATE_FLAG | NFC_STATE_FLAG | IR_STATE_FLAG)
#define BT_GNSS_FM_NFC_IR_STATE_FLAG    (BT_STATE_FLAG | GNSS_STATE_FLAG | FM_STATE_FLAG | NFC_STATE_FLAG | IR_STATE_FLAG)

#define WAIT_DEVACK_MSEC               (100)
#define WAIT_DEVACK_TIMEOUT_MSEC       (200)

#define WAIT_WKUPDEV_MSEC              (2000)

enum PM_EXCEPT_TYPE
{
    PM_EXCEPT_WIFI_POWEROFF_CMD_FAIL       = 0,         // 下电时sdio发送下电命令失败
    PM_EXCEPT_UART_OPEN_WIFI_FAIL          = 1,         // UART close wifi FAIL
    PM_EXCEPT_UART_CLOSE_WIFI_FAIL         = 2,         // UART close wifi FAIL
    PM_EXCEPT_BCPU_OPEN_FAIL               = 3,         // WIFI OPEN bfgn FAIL
    PM_EXCEPT_BCPU_CLOSE_FAIL              = 4,        // WIFI CLOSE bfgn FAIL
};
typedef oal_uint8 plat_pm_except_enum_uint8;

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/

/*private data for pm driver*/
struct pm_drv_data
{
    /*3 in 1 interface pointer*/
    struct ps_pm_s                  *ps_pm_interface;

    /*wlan interface pointer*/
    struct wlan_pm_s                *pst_wlan_pm_info;

	/* board customize info */
	BOARD_INFO						*board;

    /*wake lock for bfg,be used to prevent host form suspend*/
    struct wake_lock                bfg_wake_lock;

    /*mutex for sync*/
    struct mutex                    host_mutex;

    /*Tasklet to respond to change in hostwake line */
    struct tasklet_struct           hostwake_task;

    /*bfg tx spinlock*/
    spinlock_t                      tx_lock;

    /*bfgx VS. bfg timer spinlock */
    spinlock_t                      node_timer_spinlock;

    /* uart could be used or not */
    uint8   uart_ready;

    /* mark receiving data after set dev as sleep state but before get ack of device */
    uint8 rcvdata_bef_devack_flag;


    /*bfgx sleep state*/
    uint8 bfgx_dev_state;

    /*flag for patch init*/
    uint64 patch_init_flag;

    /*bfg irq num*/
    uint32 bfg_irq;

    /* gnss lowpower state */
    atomic_t gnss_sleep_flag;

    atomic_t bfg_needwait_devboot_flag;

    /* flag to mark whether enable lowpower or not */
    uint8  bfgx_lowpower_enable;
    uint8  bfgx_bt_lowpower_enable;
    uint8  bfgx_gnss_lowpower_enable;
    uint8  bfgx_nfc_lowpower_enable;

    /* workqueue for wkup device */
    struct workqueue_struct *wkup_dev_workqueue;
    struct work_struct wkup_dev_work;
    struct work_struct send_disallow_msg_work;

    /* wait device ack timer */
    struct timer_list bfg_timer;
    struct timer_list dev_ack_timer;

    /* the completion for waiting for host wake up device ok */
    struct completion host_wkup_dev_comp;
    /* the completion for waiting for dev ack(host allow sleep) ok */
    struct completion dev_ack_comp;
    /* the completion for waiting for dev boot ok */
    struct completion dev_bootok_ack_comp;
};

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/

/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern struct pm_drv_data * pm_get_drvdata(void);
extern int32 host_wkup_dev(void);
extern struct pm_drv_data * pm_get_drvdata(void);
extern int32 check_dev_is_shutdown(uint8 type);
extern int firmware_download_function(uint32 which_cfg);
extern oal_int32 hi110x_get_wifi_power_stat(oal_void);
#endif

