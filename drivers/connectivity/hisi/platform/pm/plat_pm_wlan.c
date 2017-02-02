

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
#include <linux/module.h>   /* kernel module definitions */
#include <linux/init.h>
#include <linux/interrupt.h>
#include <linux/timer.h>
#include <linux/platform_device.h>
#include <linux/kobject.h>
#include <linux/irq.h>
#include <linux/wakelock.h>
#include <linux/mmc/sdio.h>
#include <linux/mmc/host.h>
#include <linux/mmc/card.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/sdio_ids.h>
#include <linux/mmc/sdio_func.h>
#include <linux/mmc/host.h>
#include <linux/gpio.h>

#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"

#include "plat_type.h"
//#include "plat_debug.h"
#include "plat_pm_wlan.h"
#include "plat_pm.h"

#include "oal_hcc_host_if.h"
#include "oam_ext_if.h"

#undef  THIS_FILE_ID
#define THIS_FILE_ID OAM_FILE_ID_PLAT_PM_WLAN_C


/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
struct wlan_pm_s* gpst_wlan_pm_info = OAL_PTR_NULL;

wlan_pm_callback_stru     gst_wlan_pm_callback =
{
    .wlan_pm_wakeup_dev  = wlan_pm_wakeup_dev,
    .wlan_pm_state_get   = wlan_pm_state_get,
    .wlan_pm_wakeup_host = wlan_pm_wakeup_host,
    .wlan_pm_feed_wdg    = wlan_pm_feed_wdg,
    .wlan_pm_fit_freq    = OAL_PTR_NULL,

};
oal_bool_enum g_wlan_pm_switch = 1;

EXPORT_SYMBOL_GPL(g_wlan_pm_switch);

extern  int32 hi110x_power_on(uint8 type);
extern  int32 hi110x_power_off(uint8 type);
void wlan_pm_wakeup_work(oal_work_stru *pst_worker);
void wlan_pm_sleep_work(oal_work_stru *pst_worker);
void wlan_pm_wdg_timeout(struct wlan_pm_s *pm_data);

int32 wlan_pm_wakeup_done_callback(void *data);
int32 wlan_pm_close_done_callback(void *data);
int32 wlan_pm_open_bcpu_done_callback(void *data);
int32 wlan_pm_close_bcpu_done_callback(void *data);

int32 wlan_pm_stop_wdg(struct wlan_pm_s *pst_wlan_pm_info);
oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker);
void wlan_pm_info_clean(void);


struct wlan_pm_s*  wlan_pm_get_drv(oal_void)
{
    return gpst_wlan_pm_info;
}


oal_int32  wlan_pm_set_device_ready(oal_void* data)
{
    struct wlan_pm_s    *pst_wlan_pm = (struct wlan_pm_s*)data;

    OAL_COMPLETE(&pst_wlan_pm->st_device_ready);
    return OAL_SUCC;
}

oal_void wlan_pm_init_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_device_ready);
}

oal_uint32 wlan_pm_wait_device_ready(struct wlan_pm_s    *pst_wlan_pm)
{
    /* 等待host下半部初始化完成 */
    return oal_wait_for_completion_timeout(&pst_wlan_pm->st_device_ready, (oal_uint32)OAL_MSECS_TO_JIFFIES(HOST_WAIT_BOTTOM_INIT_TIMEOUT));
}
oal_int32 wlan_pm_sleep_request(struct wlan_pm_s    *pst_wlan_pm)
{
    return oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_SLEEP_REQ);


}


oal_int32 wlan_pm_allow_sleep_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    //PS_PRINT_INFO("wlan_pm_allow_sleep_callback !\n");

    pst_wlan_pm->ul_sleep_stage = SLEEP_ALLOW_RCV;
    OAL_COMPLETE(&pst_wlan_pm->st_sleep_request_ack);

    return SUCCESS;

}


oal_int32 wlan_pm_disallow_sleep_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    //PS_PRINT_INFO("wlan_pm_disallow_sleep_callback !\n");
    OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_disallow_sleep_callback !\n");

    pst_wlan_pm->ul_sleep_stage = SLEEP_DISALLOW_RCV;
    OAL_COMPLETE(&pst_wlan_pm->st_sleep_request_ack);


    return SUCCESS;

}



struct wlan_pm_s*  wlan_pm_init(oal_void)
{
    struct wlan_pm_s*   pst_wlan_pm;
    BOARD_INFO *        pst_board = get_board_info();

    if(OAL_PTR_NULL == pst_board)
    {
        return OAL_PTR_NULL;
    }

    pst_wlan_pm = kzalloc(sizeof(struct wlan_pm_s), GFP_KERNEL);
    if (NULL == pst_wlan_pm)
    {
        OAL_IO_PRINT("[plat_pm]no mem to allocate wlan_pm_data\n");
        return OAL_PTR_NULL;
    }

    oal_memset(pst_wlan_pm, 0, sizeof(struct wlan_pm_s));

    pst_wlan_pm->pst_sdio                  = oal_get_sdio_stru();
    pst_wlan_pm->pst_sdio->pst_pm_callback = &gst_wlan_pm_callback;

    pst_wlan_pm->ul_wlan_pm_enable          = OAL_FALSE;

    /*work queue初始化*/
    pst_wlan_pm->pst_pm_wq = oal_create_singlethread_workqueue("wlan_pm_wq");
    if (!pst_wlan_pm->pst_pm_wq)
    {
        OAL_IO_PRINT("[plat_pm]Failed to create wlan_pm_wq!");
        kfree(pst_wlan_pm);
        return OAL_PTR_NULL;
    }
    /*register wakeup and sleep work*/
    OAL_INIT_WORK(&pst_wlan_pm->st_wakeup_work, wlan_pm_wakeup_work);
    OAL_INIT_WORK(&pst_wlan_pm->st_sleep_work,  wlan_pm_sleep_work);

    /*sleep timer初始化*/
    init_timer(&pst_wlan_pm->st_watchdog_timer);
    pst_wlan_pm->st_watchdog_timer.data        = (unsigned long)pst_wlan_pm;
    pst_wlan_pm->st_watchdog_timer.function    = (void *)wlan_pm_wdg_timeout;
    pst_wlan_pm->ul_wdg_timeout                = DEFAULT_WDG_TIMEOUT;

    pst_wlan_pm->ul_last_freq                  = WLCPU_160MHZ;
    pst_wlan_pm->ul_wlan_power_state           = WLAN_STATE_SHUTDOWN;
    mutex_init(&pst_wlan_pm->st_power_mutex);

    pst_wlan_pm->ul_wlan_dev_state             = HOST_ALLOW_TO_SLEEP;
    pst_wlan_pm->ul_sleep_stage                = SLEEP_STAGE_INIT;

    pst_wlan_pm->ul_in_suspend                 = OAL_FALSE;
    oal_spin_lock_init(&pst_wlan_pm->st_suspend_lock);

    gpst_wlan_pm_info = pst_wlan_pm;

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_open_bcpu_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_bcpu_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_device_ready);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_wakeup_done);
    OAL_INIT_COMPLETION(&pst_wlan_pm->st_sleep_request_ack);

    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_WLAN_READY,wlan_pm_set_device_ready,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_WAKEUP_SUCC,wlan_pm_wakeup_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_ALLOW_SLEEP,wlan_pm_allow_sleep_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_DISALLOW_SLEEP,wlan_pm_disallow_sleep_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_POWEROFF_ACK,wlan_pm_close_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_OPEN_BCPU_ACK,wlan_pm_open_bcpu_done_callback,pst_wlan_pm);
    oal_sdio_message_register(pst_wlan_pm->pst_sdio,D2H_MSG_CLOSE_BCPU_ACK,wlan_pm_close_bcpu_done_callback,pst_wlan_pm);

    pst_wlan_pm->pst_sdio->gpio_int_count = 0;
    pst_wlan_pm->pst_sdio->data_int_count = 0;
    pst_wlan_pm->pst_sdio->wakeup_int_count = 0;

    OAL_IO_PRINT("[plat_pm]wlan_pm_init ok!");
    return  pst_wlan_pm;
}
oal_uint  wlan_pm_exit(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_SUCC;
    }

    wlan_pm_stop_wdg(pst_wlan_pm);

    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WAKEUP_SUCC);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_WLAN_READY);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_ALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_DISALLOW_SLEEP);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_POWEROFF_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_OPEN_BCPU_ACK);
    oal_sdio_message_unregister(pst_wlan_pm->pst_sdio,D2H_MSG_CLOSE_BCPU_ACK);

    kfree(pst_wlan_pm);

    gpst_wlan_pm_info = OAL_PTR_NULL;

    OAL_IO_PRINT("[plat_pm]wlan_pm_exit ok!");


    return OAL_SUCC;

}


oal_uint32 wlan_pm_is_poweron(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FALSE;
    }

    if(WLAN_STATE_BOOTUP == pst_wlan_pm->ul_wlan_power_state)
    {
        return OAL_TRUE;
    }
    else
    {
        return OAL_FALSE;
    }
}
EXPORT_SYMBOL_GPL(wlan_pm_is_poweron);

oal_int32 wlan_pm_open(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_open,pm_data is NULL!");
        return OAL_FAIL;
    }

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open start!!");

    mutex_lock(&pm_data->host_mutex);

    pst_wlan_pm->ul_open_cnt++;

    if(WLAN_STATE_BOOTUP == pst_wlan_pm->ul_wlan_power_state)
    {
        mutex_unlock(&pm_data->host_mutex);
        OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open aleady opened");
        return OAL_ERR_CODE_ALREADY_OPEN;
    }

    if(!pst_wlan_pm->pst_sdio->ul_wklock_cnt)
    {
        /*make sure open only lock once*/
        oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR, "wlan_pm_open get wakelock %d!",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    if(OAL_SUCC != hi110x_power_on(WLAN_STATE_FLAG))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "hi110x_power_on fail!");
        pst_wlan_pm->ul_wlan_power_state = WLAN_STATE_SHUTDOWN;
		oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
		mutex_unlock(&pm_data->host_mutex);
        return OAL_FAIL;
    }

    mutex_unlock(&pm_data->host_mutex);

    OAM_WARNING_LOG0(0, OAM_SF_PWR, "wlan_pm_open SUCC!!");
    wlan_pm_enable();

    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_open);
extern int isAsic(void);
oal_uint32 wlan_pm_close(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR, "wlan_pm_close,pm_data is NULL!");
        return OAL_FAIL;
    }

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    OAL_IO_PRINT("[plat_pm]wlan_pm_close start!!\n");

    mutex_lock(&pm_data->host_mutex);

    if (!isAsic())
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close is FPGA,do not close wifi!\n");
        mutex_unlock(&pm_data->host_mutex);
        return OAL_SUCC;
    }

    pst_wlan_pm->ul_close_cnt++;

    if(WLAN_STATE_SHUTDOWN == pst_wlan_pm->ul_wlan_power_state)
    {
        mutex_unlock(&pm_data->host_mutex);
        return OAL_ERR_CODE_ALREADY_CLOSE;
    }

    wlan_pm_disable();

    wlan_pm_info_clean();

    /*mask rx sdio data interrupt*/
    oal_sdio_func1_int_mask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);
    
    if(OAL_SUCC!=hi110x_power_off(WLAN_STATE_FLAG))
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"hi110x_power_off FAIL!\n");
		oal_sdio_release_host(pst_wlan_pm->pst_sdio);
        mutex_unlock(&pm_data->host_mutex);
        return OAL_FAIL;
    }

    pst_wlan_pm->ul_wlan_power_state = WLAN_STATE_SHUTDOWN;

    /*unmask rx sdio data interrupt*/
    oal_sdio_func1_int_unmask(pst_wlan_pm->pst_sdio, HISDIO_FUNC1_INT_DREADY);

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

    OAM_WARNING_LOG1(0,OAM_SF_PWR,"wlan_pm_close release wakelock %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    oal_sdio_wakelocks_release_detect(pst_wlan_pm->pst_sdio);

    mutex_unlock(&pm_data->host_mutex);

    OAM_WARNING_LOG0(0,OAM_SF_PWR,"wlan_pm_close succ!\n");
    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_close);


oal_uint32 wlan_pm_enable(oal_void)
{

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(!g_wlan_pm_switch)
    {
        return OAL_SUCC;
    }

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_TRUE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable already enabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    pst_wlan_pm->ul_wlan_pm_enable = OAL_TRUE;

    wlan_pm_feed_wdg();

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_enable SUCC!");

    return OAL_SUCC;
}
EXPORT_SYMBOL_GPL(wlan_pm_enable);


oal_uint32 wlan_pm_disable(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable already disabled!");
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_SUCC;
    }

    wlan_pm_wakeup_dev();

    wlan_pm_stop_wdg(pst_wlan_pm);

    pst_wlan_pm->ul_wlan_pm_enable = OAL_FALSE;

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    oal_cancel_work_sync(&pst_wlan_pm->st_wakeup_work);
    oal_cancel_work_sync(&pst_wlan_pm->st_sleep_work);

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_disable SUCC!");

    return OAL_SUCC;

}
EXPORT_SYMBOL_GPL(wlan_pm_disable);


oal_uint wlan_pm_init_dev(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint             ul_flag;
    oal_int              ret;


    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_init_dev!\n");

    oal_spin_lock_irq_save(&pst_wlan_pm->pst_sdio->st_pm_state_lock,&ul_flag);

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;

    oal_spin_unlock_irq_restore(&pst_wlan_pm->pst_sdio->st_pm_state_lock,&ul_flag);


    /* wait for sdio wakeup */
    ret = down_timeout(&sdio_wake_sema, 6*HZ);
    if (-ETIME == ret)
    {
        //PS_PRINT_ERR("sdio controller is not ready!");
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        return OAL_FAIL;
    }
    up(&sdio_wake_sema);

     /* set sdio register */
    return oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);

}




oal_uint wlan_pm_wakeup_dev(oal_void)
{
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    //oal_uint             ul_flag;
    oal_int32              ret;


    if (OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

    if(OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
    {
        return OAL_SUCC;
    }

    wlan_pm_stop_wdg(pst_wlan_pm);

    if(HOST_DISALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
    {
      return OAL_SUCC;
    }

    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_wakeup_done);

    /* wait for sdio wakeup */
    ret = down_timeout(&sdio_wake_sema, 6*HZ);
    if (-ETIME == ret)
    {
        pst_wlan_pm->ul_wakeup_fail_wait_sdio++;
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"sdio controller is not ready!");
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        return OAL_FAIL;
    }
    up(&sdio_wake_sema);

     /* set sdio register */
    oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_FALSE);

    ret = oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);
    if(OAL_SUCC != ret)
    {
        pst_wlan_pm->ul_wakeup_fail_set_reg++;
        OAM_ERROR_LOG1(0, OAM_SF_PWR,"oal_sdio_wakeup_dev Fail ret = %d",ret);
        oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        return OAL_FAIL;
    }
    OAM_INFO_LOG0(0, OAM_SF_PWR, "wifi wakeup cmd send");

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;
    oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);

    up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);

    ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_wakeup_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_WAKUP_MSG_WAIT_TIMEOUT));
    if(0 == ul_ret)
    {
        OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_dev wait device complete fail !\n");
        if(DISALLOW_TO_SLEEP_VALUE == oal_sdio_get_sleep_state(pst_wlan_pm->pst_sdio))
        {
            pst_wlan_pm->ul_wakeup_fail_timeout++;
            OAM_WARNING_LOG0(0, OAM_SF_PWR,"oal_sdio_wakeup_dev SUCC to set 0xf0 = 0");
            oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);
            pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;
            oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
            return OAL_FAIL;
        }
        else
        {
            pst_wlan_pm->ul_wakeup_fail_set_reg++;
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"oal_sdio_wakeup_dev Fail to set 0xf0 = 0");
            pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;
            oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
            return OAL_FAIL;
        }
    }

    pst_wlan_pm->ul_wakeup_succ++;
    //PS_PRINT_INFO("wlan_pm_wakeup_dev succ, wakelock cnt %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    return OAL_SUCC;

}


oal_uint  wlan_pm_open_bcpu(oal_void)
{

    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint32           ul_ret;

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return OAL_FAIL;
    }

     /*通过sdio配置命令，解复位BCPU*/
    OAM_WARNING_LOG0(0, OAM_SF_PWR,"sdio open BCPU");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_SUCC != wlan_pm_wakeup_dev())
    {
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }

    wlan_pm_feed_wdg();

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_open_bcpu_done);

    ul_ret = oal_sdio_send_msg(pst_wlan_pm->pst_sdio, H2D_MSG_RESET_BCPU);
    if(OAL_SUCC == ul_ret)
    {
        /*等待device执行命令*/
        up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);
        ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_open_bcpu_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_OPEN_BCPU_WAIT_TIMEOUT));
        if(0 == ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_open_bcpu wait device ACK timeout !");
            return OAL_FAIL;
        }

        return  OAL_SUCC;
    }
    else
    {
        OAM_ERROR_LOG0(0, OAM_SF_PWR,"fail to send H2D_MSG_RESET_BCPU");
        return  OAL_FAIL;
    }

}



oal_uint wlan_pm_wakeup_host(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAL_BUG_ON(!pst_wlan_pm);

    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_host get wakelock %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    if(0!=wlan_pm_work_submit(pst_wlan_pm,&pst_wlan_pm->st_wakeup_work))
    {
        pst_wlan_pm->ul_wakeup_fail_submit_work++;
        oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
        OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_host release wakelock %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);
    }
    else
    {
        pst_wlan_pm->ul_wakeup_succ_work_submit++;
    }

    return OAL_SUCC;

}



oal_int wlan_pm_work_submit(struct wlan_pm_s    *pst_wlan_pm, oal_work_stru* pst_worker)
{
    oal_int  i_ret    = 0;

    if(work_busy(pst_worker))
    {
        /*If comm worker is processing,
          we need't submit again*/
        OAM_WARNING_LOG1(0, OAM_SF_PWR,"WiFi %pF Worker is Processing...need't submit\n",(void*)pst_worker->func);
        i_ret = -OAL_EBUSY;
        goto done;
    }
    else
    {
        OAM_INFO_LOG1(0, OAM_SF_PWR,"WiFi %pF Worker Submit\n",(void*)pst_worker->func);
        queue_work(pst_wlan_pm->pst_pm_wq, pst_worker);
    }
done:
    return i_ret;
}


void wlan_pm_wakeup_work(oal_work_stru *pst_worker)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
    oal_uint l_ret;

    OAM_INFO_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_work start!\n");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    l_ret = wlan_pm_wakeup_dev();
    if(OAL_SUCC==l_ret)
    {
        wlan_pm_feed_wdg();
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    /*match for the work submit*/
    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);

    OAM_INFO_LOG1(0, OAM_SF_PWR,"wlan_pm_wakeup_work release wakelock %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    return;

}

int32 wlan_pm_wakeup_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;


    OAM_INFO_LOG0(0, OAM_SF_PWR,"wlan_pm_wakeup_done_callback !\n");

    pst_wlan_pm->ul_wakeup_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_wakeup_done);

    return SUCCESS;

}



int32 wlan_pm_close_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close_done_callback !");

    pst_wlan_pm->ul_close_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_close_done);

    return SUCCESS;

}



int32 wlan_pm_open_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;


    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_open_bcpu_done_callback !");

    pst_wlan_pm->ul_open_bcpu_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_open_bcpu_done);

    return SUCCESS;

}



int32 wlan_pm_close_bcpu_done_callback(void *data)
{
    struct wlan_pm_s *pst_wlan_pm = (struct wlan_pm_s *)data;


    OAM_WARNING_LOG0(0, OAM_SF_PWR,"wlan_pm_close_bcpu_done_callback !");

    pst_wlan_pm->ul_close_bcpu_done_callback++;
    OAL_COMPLETE(&pst_wlan_pm->st_close_bcpu_done);

    return SUCCESS;

}



void wlan_pm_sleep_work(oal_work_stru *pst_worker)
{
   struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();
   //oal_uint             ul_flag;
   oal_int32           l_ret;
   oal_uint32           ul_ret;


   hcc_tx_transfer_lock(hcc_get_default_handler());

   if(OAL_FALSE == pst_wlan_pm->ul_wlan_pm_enable)
   {
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return ;
   }

   if(HOST_ALLOW_TO_SLEEP == pst_wlan_pm->ul_wlan_dev_state)
   {
     //PS_PRINT_INFO("wakeuped,need not do again!\n");
     hcc_tx_transfer_unlock(hcc_get_default_handler());
     return ;
   }

   pst_wlan_pm->ul_sleep_stage = SLEEP_REQ_SND;

   OAL_INIT_COMPLETION(&pst_wlan_pm->st_sleep_request_ack);

   l_ret = wlan_pm_sleep_request(pst_wlan_pm);
   if(OAL_SUCC != l_ret)
   {
      pst_wlan_pm->ul_sleep_fail_request++;
      OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_sleep_request fail !\n");
      goto fail_sleep;
   }

   //PS_PRINT_INFO(WLAN_PM_MODULE"wlan_pm_sleep_request SUCC!\n");
   up(&pst_wlan_pm->pst_sdio->gpio_rx_sema);

   ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_sleep_request_ack, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_SLEEP_MSG_WAIT_TIMEOUT));
   if(0 == ul_ret)
   {
       pst_wlan_pm->ul_sleep_fail_wait_timeout++;
       OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_sleep_work wait completion fail !\n");
       goto fail_sleep;
   }

   if(SLEEP_ALLOW_RCV == pst_wlan_pm->ul_sleep_stage)
   {

       oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_FALSE);

       pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

       l_ret = oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);
       OAM_INFO_LOG0(0, OAM_SF_PWR, "wifi sleep cmd send");
       if(OAL_SUCC!=l_ret)
       {
            pst_wlan_pm->ul_sleep_fail_set_reg++;
            OAM_ERROR_LOG1(0, OAM_SF_PWR,"oal_sdio_sleep_dev Fail ret = %d\r\n",l_ret);
            pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;
            oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);
            goto fail_sleep;
       }

       oal_wlan_gpio_intr_enable(pst_wlan_pm->pst_sdio,OAL_TRUE);
   }
   else
   {

       pst_wlan_pm->ul_sleep_fail_forbid++;
       OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_sleep_work device forbid sleep %ld\n",pst_wlan_pm->ul_sleep_stage);
       goto fail_sleep;
   }

   hcc_tx_transfer_unlock(hcc_get_default_handler());
   oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);


   pst_wlan_pm->ul_sleep_succ++;
   if(0!=pst_wlan_pm->pst_sdio->ul_wklock_cnt)
   {
      OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_sleep_work release wakelock %d!\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);
   }

   return;

fail_sleep:
    wlan_pm_feed_wdg();
    hcc_tx_transfer_unlock(hcc_get_default_handler());
    return ;

}



oal_uint wlan_pm_state_get(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    return pst_wlan_pm->ul_wlan_dev_state;
}



oal_void wlan_pm_state_set(struct wlan_pm_s  *pst_wlan_pm,oal_uint ul_state)
{

    pst_wlan_pm->ul_wlan_dev_state = ul_state;

}

oal_void  wlan_pm_set_timeout(oal_uint32 ul_timeout)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    if(OAL_PTR_NULL == pst_wlan_pm)
    {
        return ;
    }

    OAM_WARNING_LOG1(0, OAM_SF_PWR,"wlan_pm_set_timeout[%dms]",ul_timeout);

    pst_wlan_pm ->ul_wdg_timeout = ul_timeout;

    wlan_pm_feed_wdg();
}
EXPORT_SYMBOL_GPL(wlan_pm_set_timeout);

oal_void  wlan_pm_feed_wdg(oal_void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    /**
     * 需要同时满足两个条件才能喂狗:
     * 1、用户处于STA模式
     * 2、关联成功
     */
    //if (IS_STA(cfg) && IS_CONNECTED(cfg) && IS_GET_IPADDR(pm_info))
    if(pst_wlan_pm->ul_wlan_pm_enable)
    {
        //PS_PRINT_ERR("WiFi Feed Watchdog\n");
        mod_timer(&pst_wlan_pm->st_watchdog_timer, jiffies + msecs_to_jiffies(pst_wlan_pm->ul_wdg_timeout));
    }
}



int32 wlan_pm_stop_wdg(struct wlan_pm_s *pst_wlan_pm_info)
{
    //PS_PRINT_ERR("Stop wlan watchdog");
    if(in_interrupt())
    {
        return del_timer(&pst_wlan_pm_info->st_watchdog_timer);
    }
    else
    {
        return del_timer_sync(&pst_wlan_pm_info->st_watchdog_timer);
    }

}




void wlan_pm_wdg_timeout(struct wlan_pm_s *pm_data)
{
    struct oal_sdio* hi_sdio;
    oal_uint         ul_flag;

    if(NULL == pm_data)
    {
        return;
    }

    hi_sdio = pm_data->pst_sdio;

    oal_spin_lock_irq_save(&hi_sdio->st_pm_state_lock,&ul_flag);

    wlan_pm_work_submit(pm_data, &pm_data->st_sleep_work);

    oal_spin_unlock_irq_restore(&hi_sdio->st_pm_state_lock,&ul_flag);

    pm_data->ul_sleep_work_submit++;

    return;

}


oal_int32 wlan_pm_poweroff_cmd(oal_void)
{
    oal_int32            ret;
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"Send H2D_MSG_PM_WLAN_OFF cmd");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_SUCC != wlan_pm_wakeup_dev())
    {
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }

    wlan_pm_feed_wdg();


    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_done);

    ret =  oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_WLAN_OFF);
    if(OAL_SUCC == ret)
    {
        /*等待device执行命令*/
        ul_ret =  oal_wait_for_completion_timeout(&pst_wlan_pm->st_close_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_POWEROFF_ACK_WAIT_TIMEOUT));
        if(0 == ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_poweroff_cmd wait device ACK timeout !");
			hcc_tx_transfer_unlock(hcc_get_default_handler());
            return OAL_FAIL;
        }

        mdelay(10);
    }

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    return OAL_SUCC;


}
oal_int32 wlan_pm_shutdown_bcpu_cmd(oal_void)
{
    oal_int32            ret;
    oal_uint32           ul_ret;
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    OAM_WARNING_LOG0(0, OAM_SF_PWR,"Send H2D_MSG_PM_WLAN_OFF cmd");

    hcc_tx_transfer_lock(hcc_get_default_handler());

    if(OAL_SUCC != wlan_pm_wakeup_dev())
    {
        hcc_tx_transfer_unlock(hcc_get_default_handler());
        return OAL_FAIL;
    }

    wlan_pm_feed_wdg();

    hcc_tx_transfer_unlock(hcc_get_default_handler());

    OAL_INIT_COMPLETION(&pst_wlan_pm->st_close_bcpu_done);

    ret =  oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_BCPU_OFF);
    if(OAL_SUCC == ret)
    {
        /*等待device执行命令*/
        ul_ret = oal_wait_for_completion_timeout(&pst_wlan_pm->st_close_bcpu_done, (oal_uint32)OAL_MSECS_TO_JIFFIES(WLAN_POWEROFF_ACK_WAIT_TIMEOUT));
        if(0 == ul_ret)
        {
            OAM_ERROR_LOG0(0, OAM_SF_PWR,"wlan_pm_shutdown_bcpu_cmd wait device ACK timeout !");
            return OAL_FAIL;
        }
    }

    return OAL_SUCC;


}

void wlan_pm_dump_info(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();


    OAL_IO_PRINT("----------wlan_pm_dump_info begin-----------\n");
    OAL_IO_PRINT("power on:%ld, enable:%ld,g_wlan_pm_switch:%d\n",pst_wlan_pm->ul_wlan_power_state,pst_wlan_pm->ul_wlan_pm_enable,g_wlan_pm_switch);
    OAL_IO_PRINT("dev state:%ld, sleep stage:%ld\n",pst_wlan_pm->ul_wlan_dev_state,pst_wlan_pm->ul_sleep_stage);
    OAL_IO_PRINT("open:%d,close:%d\n",pst_wlan_pm->ul_open_cnt,pst_wlan_pm->ul_close_cnt);
    OAL_IO_PRINT("sdio suspend:%d,sdio resume:%d\n",pst_wlan_pm->pst_sdio->ul_sdio_suspend,pst_wlan_pm->pst_sdio->ul_sdio_resume);
    OAL_IO_PRINT("gpio_intr:%llu\n",pst_wlan_pm->pst_sdio->gpio_int_count);
    OAL_IO_PRINT("data_intr:%llu\n",pst_wlan_pm->pst_sdio->data_int_count);
    OAL_IO_PRINT("wakeup_intr:%llu\n",pst_wlan_pm->pst_sdio->wakeup_int_count);
    OAL_IO_PRINT("D2H_MSG_WAKEUP_SUCC:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count);
    OAL_IO_PRINT("D2H_MSG_ALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count);
    OAL_IO_PRINT("D2H_MSG_DISALLOW_SLEEP:%d\n",pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count);

    OAL_IO_PRINT("wakeup_succ:%d\n",pst_wlan_pm->ul_wakeup_succ);
    OAL_IO_PRINT("wakeup_done_callback:%d\n",pst_wlan_pm->ul_wakeup_done_callback);
    OAL_IO_PRINT("wakeup_succ_work_submit:%d\n",pst_wlan_pm->ul_wakeup_succ_work_submit);
    OAL_IO_PRINT("wakeup_fail_wait_sdio:%d\n",pst_wlan_pm->ul_wakeup_fail_wait_sdio);
    OAL_IO_PRINT("wakeup_fail_timeout:%d\n",pst_wlan_pm->ul_wakeup_fail_timeout);
    OAL_IO_PRINT("wakeup_fail_set_reg:%d\n",pst_wlan_pm->ul_wakeup_fail_set_reg);
    OAL_IO_PRINT("wakeup_fail_submit_work:%d\n",pst_wlan_pm->ul_wakeup_fail_submit_work);
    OAL_IO_PRINT("sleep_succ:%d\n",pst_wlan_pm->ul_sleep_succ);
    OAL_IO_PRINT("sleep_fail_request:%d\n",pst_wlan_pm->ul_sleep_fail_request);
    OAL_IO_PRINT("sleep_fail_set_reg:%d\n",pst_wlan_pm->ul_sleep_fail_set_reg);
    OAL_IO_PRINT("sleep_fail_wait_timeout:%d\n",pst_wlan_pm->ul_sleep_fail_wait_timeout);
    OAL_IO_PRINT("sleep_fail_forbid:%d\n",pst_wlan_pm->ul_sleep_fail_forbid);
    OAL_IO_PRINT("sleep_work_submit:%d\n",pst_wlan_pm->ul_sleep_work_submit);
    OAL_IO_PRINT("wklock_cnt:%d\n \n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);
    OAL_IO_PRINT("----------wlan_pm_dump_info end-----------\n");

    oal_sdio_send_msg(pst_wlan_pm->pst_sdio,H2D_MSG_PM_DEBUG);
}

void wlan_pm_info_clean(void)
{
    struct wlan_pm_s    *pst_wlan_pm = wlan_pm_get_drv();

    pst_wlan_pm->pst_sdio->gpio_int_count   = 0;
    pst_wlan_pm->pst_sdio->data_int_count   = 0;
    pst_wlan_pm->pst_sdio->wakeup_int_count = 0;

    pst_wlan_pm->pst_sdio->msg[D2H_MSG_WAKEUP_SUCC].count = 0;
    pst_wlan_pm->pst_sdio->msg[D2H_MSG_ALLOW_SLEEP].count = 0;
    pst_wlan_pm->pst_sdio->msg[D2H_MSG_DISALLOW_SLEEP].count = 0;

    pst_wlan_pm->ul_wakeup_succ = 0;
    pst_wlan_pm->ul_wakeup_done_callback = 0;
    pst_wlan_pm->ul_wakeup_succ_work_submit = 0;
    pst_wlan_pm->ul_wakeup_fail_wait_sdio = 0;
    pst_wlan_pm->ul_wakeup_fail_timeout = 0;
    pst_wlan_pm->ul_wakeup_fail_set_reg = 0;
    pst_wlan_pm->ul_wakeup_fail_submit_work = 0;

    pst_wlan_pm->ul_sleep_succ = 0;
    pst_wlan_pm->ul_wakeup_done_callback = 0;
    pst_wlan_pm->ul_sleep_fail_set_reg = 0;
    pst_wlan_pm->ul_sleep_fail_wait_timeout = 0;
    pst_wlan_pm->ul_sleep_fail_forbid = 0;
    pst_wlan_pm->ul_sleep_work_submit = 0;


    return;

}


oal_void wlan_pm_debug_sleep(void)
{
   struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_sleep_dev(pst_wlan_pm->pst_sdio);

    pst_wlan_pm->ul_wlan_dev_state = HOST_ALLOW_TO_SLEEP;

    return  ;
}

oal_void wlan_pm_debug_wakeup(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wakeup_dev(pst_wlan_pm->pst_sdio);

    pst_wlan_pm->ul_wlan_dev_state = HOST_DISALLOW_TO_SLEEP;

    return  ;
}

oal_void wlan_pm_debug_wake_lock(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wake_lock(pst_wlan_pm->pst_sdio);
    OAL_IO_PRINT("wlan_pm_debug_wake_lock:wklock_cnt = %d\r\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    return  ;
}

oal_void wlan_pm_debug_wake_unlock(void)
{
    struct wlan_pm_s   *pst_wlan_pm     = wlan_pm_get_drv();

    oal_sdio_wake_unlock(pst_wlan_pm->pst_sdio);
    OAL_IO_PRINT("wlan_pm_debug_wake_unlock:wklock_cnt = %d\r\n",pst_wlan_pm->pst_sdio->ul_wklock_cnt);

    return  ;
}



