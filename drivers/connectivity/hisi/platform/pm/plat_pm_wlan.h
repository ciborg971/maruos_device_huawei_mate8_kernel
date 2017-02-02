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

#ifndef __PLAT_PM_WLAN_H__
#define __PLAT_PM_WLAN_H__

/*****************************************************************************
  1 Include other Head file
*****************************************************************************/
#if (_PRE_OS_VERSION_LINUX == _PRE_OS_VERSION)
#include <linux/mutex.h>
#include <linux/kernel.h>
#include <linux/wakelock.h>

#include <linux/mmc/host.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio.h>

#include <linux/fb.h>
#endif

#include "oal_ext_if.h"


#define HOST_WAIT_BOTTOM_INIT_TIMEOUT   (20000)
#define WLAN_WAKUP_MSG_WAIT_TIMEOUT     (100)
#define WLAN_SLEEP_MSG_WAIT_TIMEOUT     (100)
#define WLAN_POWEROFF_ACK_WAIT_TIMEOUT  (100)
#define WLAN_OPEN_BCPU_WAIT_TIMEOUT     (100)
#define DEFAULT_WDG_TIMEOUT             (200)  /*50ms*/
#define LONG_WDG_TIMETOUT               (400)

#define WLAN_PM_MODULE               "[wlan]"

enum WLAN_PM_CPU_FREQ_ENUM
{
    WLCPU_40MHZ     =   1,
    WLCPU_80MHZ     =   2,
    WLCPU_160MHZ    =   3,
    WLCPU_240MHZ    =   4,
    WLCPU_320MHZ    =   5,
    WLCPU_480MHZ    =   6,
};

enum WLAN_PM_SLEEP_STAGE
{
    SLEEP_STAGE_INIT    = 0,  //初始
    SLEEP_REQ_SND       = 1,  //sleep request发送完成
    SLEEP_ALLOW_RCV     = 2,  //收到allow sleep response
    SLEEP_DISALLOW_RCV  = 3,  //收到allow sleep response
    SLEEP_CMD_SND       = 4,  //允许睡眠reg设置完成
};

/*****************************************************************************
  3 STRUCT DEFINE
*****************************************************************************/
struct wlan_pm_s
{
    struct oal_sdio        *pst_sdio;            //保存oal_sdio 的指针

    oal_uint                ul_wlan_pm_enable;    ///pm使能开关
    oal_uint                ul_wlan_power_state;  //wlan power on state
    struct mutex            st_power_mutex;        //上下电互斥锁
    volatile oal_uint       ul_wlan_dev_state;    //wlan sleep state
    oal_uint                ul_last_freq;         //保存上一次的CPU频率
    oal_uint                ul_in_suspend;       //处于suspend状态
    oal_spin_lock_stru      st_suspend_lock;     //suspend操作锁

    oal_workqueue_stru*     pst_pm_wq;           //pm work quque
    oal_work_stru           st_wakeup_work;       //唤醒work
    oal_work_stru           st_sleep_work;        //sleep work
    struct timer_list       st_watchdog_timer;   //sleep watch dog
    oal_uint32              ul_wdg_timeout;      //timeout time
    volatile oal_uint       ul_sleep_stage;      //睡眠过程阶段标识

    oal_completion          st_open_bcpu_done;
    oal_completion          st_close_bcpu_done;
    oal_completion          st_close_done;
    oal_completion          st_device_ready;
    oal_completion          st_wakeup_done;
    oal_completion          st_sleep_request_ack;

    /* 维测统计 */
    oal_uint32              ul_open_cnt;
    oal_uint32              ul_open_bcpu_done_callback;
    oal_uint32              ul_close_bcpu_done_callback;
    oal_uint32              ul_close_cnt;
    oal_uint32              ul_close_done_callback;
    oal_uint32              ul_wakeup_succ;
    oal_uint32              ul_wakeup_succ_work_submit;
    oal_uint32              ul_wakeup_done_callback;
    oal_uint32              ul_wakeup_fail_wait_sdio;
    oal_uint32              ul_wakeup_fail_timeout;
    oal_uint32              ul_wakeup_fail_set_reg;
    oal_uint32              ul_wakeup_fail_submit_work;

    oal_uint32              ul_sleep_succ;
    oal_uint32              ul_sleep_fail_request;
    oal_uint32              ul_sleep_fail_wait_timeout;
    oal_uint32              ul_sleep_fail_set_reg;
    oal_uint32              ul_sleep_fail_forbid;
    oal_uint32              ul_sleep_work_submit;


};

/*****************************************************************************
  4 EXTERN VARIABLE
*****************************************************************************/
extern oal_bool_enum g_wlan_pm_switch;
/*****************************************************************************
  5 EXTERN FUNCTION
*****************************************************************************/
extern struct wlan_pm_s*  wlan_pm_get_drv(oal_void);
extern oal_void wlan_pm_debug_sleep(void);
extern oal_void wlan_pm_debug_wakeup(void);
extern void wlan_pm_dump_info(void);
extern oal_void wlan_pm_debug_wake_lock(void);
extern oal_void wlan_pm_debug_wake_unlock(void);
extern struct wlan_pm_s*  wlan_pm_init(oal_void);
extern oal_uint  wlan_pm_exit(oal_void);
extern oal_uint32 wlan_pm_is_poweron(oal_void);
extern oal_int32 wlan_pm_open(oal_void);
extern oal_uint32 wlan_pm_close(oal_void);
extern oal_uint wlan_pm_init_dev(void);
extern oal_uint wlan_pm_wakeup_dev(oal_void);
extern oal_uint wlan_pm_wakeup_host(void);
extern oal_uint  wlan_pm_open_bcpu(oal_void);
extern oal_uint wlan_pm_state_get(void);
extern oal_uint32 wlan_pm_enable(oal_void);
extern oal_uint32 wlan_pm_disable(oal_void);
extern oal_void  wlan_pm_feed_wdg(oal_void);
extern oal_void  wlan_pm_set_timeout(oal_uint32 ul_timeout);
extern oal_int32 wlan_pm_poweroff_cmd(oal_void);
extern oal_int32 wlan_pm_shutdown_bcpu_cmd(oal_void);
extern oal_void wlan_pm_init_device_ready(struct wlan_pm_s    *pst_wlan_pm);
extern oal_uint32 wlan_pm_wait_device_ready(struct wlan_pm_s    *pst_wlan_pm);
#endif

