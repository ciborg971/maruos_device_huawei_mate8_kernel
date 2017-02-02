

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
#include <linux/tty.h>

#include "board.h"
#include "hw_bfg_ps.h"
#include "plat_type.h"
#include "plat_debug.h"
#include "plat_sdio.h"
#include "plat_uart.h"
#include "plat_firmware.h"
#include "plat_pm.h"
#include "plat_pm_user_ctrl.h"
#include "bfgx_low_power.h"
#include "bfgx_exception_rst.h"

#include "oal_sdio.h"
#include "oal_sdio_comm.h"
#include "oal_sdio_host_if.h"
#include "oal_schedule.h"

extern oal_uint32 g_LoadFirmware_on_init;
extern int isAsic(void);

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/
/*judge whether the wake lock is active or not*/
extern int wake_lock_active(struct wake_lock *lock);

struct pm_drv_data * pm_drv_data_t = NULL;

struct pm_drv_data * pm_get_drvdata(void)
{
	return pm_drv_data_t;
}

static void pm_set_drvdata(struct pm_drv_data * data)
{
	pm_drv_data_t = data;
}

extern struct oal_sdio* oal_alloc_sdio_stru(oal_void);

/*****************************************************************************
  3 Function Definition
*****************************************************************************/
int32 sdio_dev_init(struct sdio_func *func)
{
    int32 ret;
    struct pm_drv_data * pm_data = NULL;

    sdio_claim_host(func);

    ret = sdio_enable_func(func);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to enable sdio function! ret=%d\n", ret);
    }

    ret = sdio_set_block_size(func, HISDIO_BLOCK_SIZE);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to set sdio blk size! ret=%d\n", ret);
    }

    /* before enable sdio function 1, clear its interrupt flag, no matter it exist or not */
    sdio_writeb(func, HISDIO_FUNC1_INT_MASK, HISDIO_REG_FUNC1_INT_STATUS, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to clear sdio interrupt! ret=%d\n", ret);
    }

    /*
     * enable four interrupt sources in function 1:
     *      data ready for host to read
     *      read data error
     *      message from arm is available
     *      device has receive message from host
     * */
    sdio_writeb(func, HISDIO_FUNC1_INT_MASK, HISDIO_REG_FUNC1_INT_ENABLE, &ret);
    if (ret < 0)
    {
        PS_PRINT_ERR("failed to enable sdio interrupt! ret=%d\n", ret);
    }
    pm_data = pm_get_drvdata();
    oal_sdio_set_state(pm_data->pst_wlan_pm_info->pst_sdio, (oal_uint8)OAL_TRUE);
    sdio_release_host(func);

    PS_PRINT_INFO("sdio function %d enabled.\n", func->num);

    return ret;
}

/*****************************************************************************
 * Prototype    : check_bfg_state
 * Description  : check whether bfg is sleep or not
 * Input        : none
 * Output       : none
 * Return       : 0  -  sleep
                  1  -  active
                  -1 -  pm_data is null
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/05/08
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 check_bfg_state(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    return pm_data->bfgx_dev_state;
}

void bfg_mutex_lock(uint8 on)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return ;
    }

    if (on)
    {
        mutex_lock(&pm_data->host_mutex);
    }
    else
    {
        mutex_unlock(&pm_data->host_mutex);
    }
}

void bfgx_state_set(uint8 on)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    pm_data->bfgx_dev_state = on;
}

int32 bfgx_state_get(void)
{
    return check_bfg_state();
}

STATIC void bfgx_uart_state_set(uint8 uart_state)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    pm_data->uart_ready = uart_state;
}

STATIC int8 bfgx_uart_state_get(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -1;
    }

    return pm_data->uart_ready;
}

int32 bfgx_pm_feature_set(void)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -FAILURE;
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx platform pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_PL_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx platform pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_PL_DISABLE_PM);
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_bt_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx bt pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_BT_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx bt pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_BT_DISABLE_PM);
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_gnss_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx gnss pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_GNSS_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx gnss pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_GNSS_DISABLE_PM);
    }

    if (BFGX_PM_ENABLE == pm_data->bfgx_nfc_lowpower_enable)
    {
        PS_PRINT_INFO("bfgx nfc pm enable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_NFC_ENABLE_PM);
    }
    else
    {
        PS_PRINT_INFO("bfgx nfc pm disable\n");
        ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_NFC_DISABLE_PM);
    }

    msleep(20);

    return SUCCESS;
}

/*****************************************************************************
 * Prototype    : bfg_wake_lock
 * Description  : control bfg wake lock
 * Input        : uint8 on: 0 means wake unlock ,1 means wake lock.
 * Output       : none
 * Return       : void
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
void bfg_wake_lock(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    if (0 == wake_lock_active(&pm_data->bfg_wake_lock))
    {
        wake_lock(&pm_data->bfg_wake_lock);
    }

}

void bfg_wake_unlock(void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    /* 这里不判断其是否active也可以，因为unlock函数内部也会判断，为封装统一，还是加着 */
    if (wake_lock_active(&pm_data->bfg_wake_lock))
    {
        wake_unlock(&pm_data->bfg_wake_lock);
    }
}

/*****************************************************************************
 * Prototype    : bfg_spin_lock
 * Description  : control bfg spin lock
 * Input        : uint8 on: 0 means spin unlock ,1 means spin lock.
 * Output       : none
 * Return       : void
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
void bfg_spin_lock(uint8 on)
{
	struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return;
    }

    if (on)
    {
        spin_lock_bh(&pm_data->tx_lock);
    }
    else
    {
        spin_unlock_bh(&pm_data->tx_lock);
    }
}



/*****************************************************************************
 * Prototype    : bfg_sleep_wakeup
 * Description  : function for bfg device wake up
 * Input        : none
 * Output       : none
 * Return       : none
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
void host_wkup_dev_work(struct work_struct *work)
{
#define RETRY_TIMES (3)
    int i = 0;
    uint8 zero_num = 0;
    int bwkup_gpio_val = 0;
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;

	struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return ;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);

    /* if B send work item of wkup_dev before A's work item finished, then
     * B should not do actual wkup operation.
     */
     if (bfgx_uart_state_get())
     {
        PS_PRINT_DBG("B do wkup_dev work item after A do it but not finished\n");
        complete_all(&pm_data->host_wkup_dev_comp);
        return;
     }

    /* prepare to wake up device */
    timeleft = wait_for_completion_timeout(&pm_data->dev_ack_comp, msecs_to_jiffies(WAIT_DEVACK_TIMEOUT_MSEC));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait dev allow slp ack timeout\n");
        return;
    }
    /* device doesn't agree to slp */
    if (BFGX_ACTIVE == bfgx_state_get())
    {
        complete_all(&pm_data->host_wkup_dev_comp);
        PS_PRINT_DBG("we know dev ack with NoSleep\n");
        return;
    }

    /* begin to wake up device via uart rxd */
    for (i = 0; i < RETRY_TIMES; i++)
    {
        ps_change_uart_baud_rate(WKUP_DEV_BAUD_RATE, FLOW_CTRL_DISABLE);
        ps_write_tty(ps_core_d, &zero_num, sizeof(uint8));
        msleep(100);

        if (BFGX_ACTIVE == ps_core_d->ps_pm->bfgx_dev_state_get())
        {
            bwkup_gpio_val = board_get_bwkup_gpio_val();
            PS_PRINT_INFO("bfg wkup OK, gpio level:%d\n", bwkup_gpio_val);
            ps_change_uart_baud_rate(DEFAULT_BAUD_RATE, FLOW_CTRL_ENABLE);
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DISALLOW_SLP);
            ps_core_d->ps_pm->bfgx_uart_state_set(UART_READY);
            ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);
            complete_all(&pm_data->host_wkup_dev_comp);
            break;
        }
        else
        {
            bwkup_gpio_val = board_get_bwkup_gpio_val();
            PS_PRINT_INFO("bfg still NOT wkup, gpio level:%d\n", bwkup_gpio_val);
        }
    }
    if (RETRY_TIMES == i)
    {
        ps_change_uart_baud_rate(DEFAULT_BAUD_RATE, FLOW_CTRL_ENABLE);
        PS_PRINT_INFO("host wkup bfg fail\n");
    }
}

//FIXME: remove then, just for test
uint32 ul_disallow_flag = 0;
void host_send_disallow_msg(struct work_struct *work)
{
    struct ps_core_s *ps_core_d = NULL;
    oal_int32            ret;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);

    if (!ps_core_d)
    {
        PS_PRINT_INFO("ps_core has not inited\n");
        return;
    }

    /* 和wifi共用一个信号量,device唤醒host，等待系统恢复:
     * 前提是:sdio resume操作在uart后面进行，否则这里等待sdio信号量无效
     */
    ret = down_timeout(&sdio_wake_sema, 6*HZ);
    if (-ETIME == ret)
    {
        PS_PRINT_ERR("host_send_disallow_msg wait uart resume timeout !\n");
        return ;
    }
    up(&sdio_wake_sema);

    /* clear pf msg parsing buffer to avoid problem caused by wrong packet */
    reset_uart_rx_buf();

    /* 设置唤醒完成，uart可用 */
    bfgx_uart_state_set(UART_READY);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DISALLOW_SLP);

    //FIXME: REMOVE LATER
    ul_disallow_flag = 1;

    /* if any of BFNI is open, we should mod timer. */
    if(!check_dev_is_shutdown(BT_FM_NFC_IR_STATE_FLAG))
    {
        mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    }

    ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);
}

int32 host_wkup_dev(void)
{
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }
    if (BFGX_PM_DISABLE == pm_data->bfgx_lowpower_enable)
    {
        return 0;
    }
    PS_PRINT_DBG("wkup start\n");

    INIT_COMPLETION(pm_data->host_wkup_dev_comp);
    queue_work(pm_data->wkup_dev_workqueue, &pm_data->wkup_dev_work);
    timeleft = wait_for_completion_timeout(&pm_data->host_wkup_dev_comp, msecs_to_jiffies(WAIT_WKUPDEV_MSEC));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait wake up dev timeout\n");
        return -ETIMEDOUT;
    }
    PS_PRINT_DBG("wkup over\n");

    return 0;
}

/*****************************************************************************
 * Prototype    : check_dev_is_shutdown
 * Description  : check device(wlan/bt/fm/gnss) is shutdown or not
 * Input        : uint8 type: means one or more system to check
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/07/29
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 check_dev_is_shutdown(uint8 type)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }
    ps_get_core_reference(&ps_core_d);

    switch(type)
    {
        case BT_STATE_FLAG:
            return ((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state))
            ? true : false);
        case GNSS_STATE_FLAG:
            return ((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))
            ? true : false);
        case FM_STATE_FLAG:
            return ((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state))
            ? true : false);
        case WLAN_STATE_FLAG:
            return ((WLAN_STATE_SHUTDOWN == pm_data->pst_wlan_pm_info->ul_wlan_power_state)
            ? true : false);
        case NFC_STATE_FLAG:
            return ((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state))
            ? true : false);
        case IR_STATE_FLAG:
            return ((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state))
            ? true : false);
        case BT_GNSS_FM_IR_STATE_FLAG:
            return (((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state)))
            ? true : false);
        case BT_GNSS_FM_NFC_STATE_FLAG:
            return (((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state)))
            ? true : false);
        case BT_GNSS_NFC_IR_STATE_FLAG:
            return (((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state)))
            ? true : false);
        case BT_FM_NFC_IR_STATE_FLAG:
            return (((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state)))
            ? true : false);
        case GNSS_FM_NFC_IR_STATE_FLAG:
            return (((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state)))
            ? true : false);
        case BT_GNSS_FM_NFC_IR_STATE_FLAG:
            return (((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state))
            && (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state)))
            ? true : false);
        default:
            PS_PRINT_ERR("invalid type input!\n");
            break;
    }

    return -FAILURE;
}


int32 other_subsystem_is_shutdown(uint8 type)
{
    int32 state = 0;

    if (BT_STATE_FLAG == type)
    {
        PS_PRINT_INFO("bt power on!\n");
        state = check_dev_is_shutdown(GNSS_FM_NFC_IR_STATE_FLAG);
    }
    else if (FM_STATE_FLAG == type)
    {
        PS_PRINT_INFO("fm power on!\n");
        state = check_dev_is_shutdown(BT_GNSS_NFC_IR_STATE_FLAG);
    }
    else if (NFC_STATE_FLAG == type)
    {
        PS_PRINT_INFO("nfc power on!\n");
        state = check_dev_is_shutdown(BT_GNSS_FM_IR_STATE_FLAG);
    }
    else if (IR_STATE_FLAG == type)
    {
        PS_PRINT_INFO("ir power on!\n");
        state = check_dev_is_shutdown(BT_GNSS_FM_NFC_STATE_FLAG);
    }
    else
    {
        PS_PRINT_INFO("gnss power on!\n");
        state = check_dev_is_shutdown(BT_FM_NFC_IR_STATE_FLAG);
    }

    return state;
}

int32 bfg_dev_power_on(void)
{
    uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -FAILURE;
    }

    /*防止Host睡眠*/
    wake_lock(&pm_data->bfg_wake_lock);

    /*如果wifi没有打开，则 pull up power_on_enable gpio*/
    if (check_dev_is_shutdown(WLAN_STATE_FLAG))
    {
        PS_PRINT_INFO("bfgx pull up power_on_enable gpio!\n");
        board_power_on();

		if(SUCCESS != firmware_download_function(BFGX_CFG))
		{
            board_power_off();
            return -FAILURE;
		}
    }
    else
    {
        /*如果wifi睡眠，则唤醒之并发消息解复位BCPU*/
        if(OAL_SUCC != wlan_pm_open_bcpu())
        {
            return  -FAILURE;
        }
    }

    timeleft = wait_for_completion_timeout(&pm_data->dev_bootok_ack_comp, msecs_to_jiffies(WAIT_BFGX_BOOTOK_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait BFGX boot ok timeout\n");
        //TODO:下电等异常处理
        return  -FAILURE;
    }

    /* 等待成功，本次上电不再需要等待device上电成功 */
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NONEED_SET_FLAG);

    bfgx_pm_feature_set();

    /* 保证业务启动前启用流控 */
    ps_change_uart_baud_rate(DEFAULT_BAUD_RATE, FLOW_CTRL_ENABLE);

    return SUCCESS;
}
oal_void  plat_pm_exception_process(plat_pm_except_enum_uint8 en_type)
{
    return;
}

/*****************************************************************************
 * Prototype    : hi110x_power_on
 * Description  : hi110x device power on function
 * Input        : uint8 type: means one of wlan/bt/fm/gnss
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/07/29
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 hi110x_power_on(uint8 type)
{
    struct oal_sdio  *hi_sdio = NULL;
    struct ps_core_s *ps_core_d = NULL;
    int32  ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -FAILURE;
    }


    if (WLAN_STATE_FLAG == type)
    {
        PS_PRINT_INFO("wlan power on!\n");

		hi_sdio = oal_alloc_sdio_stru();

        /*如果BFGIN所有子系统都没有打开，则拉高power_on_enable gpio*/
        if (check_dev_is_shutdown(BT_GNSS_FM_NFC_IR_STATE_FLAG))
        {
            PS_PRINT_SUC("wifi pull up power_on_enable gpio!\n");
            board_power_on();

            wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);

            if(SUCCESS == firmware_download_function(BFGX_AND_WIFI_CFG))
            {
                pm_data->pst_wlan_pm_info->ul_wlan_power_state = WLAN_STATE_BOOTUP;
                oal_wlan_gpio_intr_enable(hi_sdio, OAL_TRUE);
            }
            else
            {
                PS_PRINT_ERR("firmware download fail,pull down GPIO\n");
                /*拉低GPIO，防止漏电*/
                board_power_off();
                return OAL_FAIL;
            }

            if(0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
            {
                PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!\n",HOST_WAIT_BOTTOM_INIT_TIMEOUT);
                /*拉低GPIO，防止漏电*/
                board_power_off();
                return OAL_FAIL;
            }

            if (isAsic())
            {
                pm_data->ps_pm_interface->operate_beat_timer(BEAT_TIMER_DELETE);

            }
        }
        else
        {
            ret = uart_wifi_open();
            if(OAL_SUCC != ret)
            {
                plat_pm_exception_process(PM_EXCEPT_UART_OPEN_WIFI_FAIL);
                return -FAILURE;

            }
            else
            {
                wlan_pm_init_device_ready(pm_data->pst_wlan_pm_info);
                if(SUCCESS == firmware_download_function(WIFI_CFG))
                {
                    pm_data->pst_wlan_pm_info->ul_wlan_power_state = WLAN_STATE_BOOTUP;
                    oal_wlan_gpio_intr_enable(hi_sdio, OAL_TRUE);
                }
    			else
                {
                    PS_PRINT_ERR("firmware download fail\n");
                    return OAL_FAIL;
                }

                if(0 == wlan_pm_wait_device_ready(pm_data->pst_wlan_pm_info))
                {
                    PS_PRINT_ERR("wlan_pm_wait_device_ready timeout %d !!!!!!",HOST_WAIT_BOTTOM_INIT_TIMEOUT);
                    return OAL_FAIL;
                }
            }
        }
    }
    else
    {
        if (other_subsystem_is_shutdown(type))
        {
           ret = bfg_dev_power_on();
           if(SUCCESS != ret)
           {
                plat_pm_exception_process(PM_EXCEPT_BCPU_OPEN_FAIL);
                return -FAILURE;
           }
        }
        else
        {
            /*如果BFGIN睡眠，则唤醒之*/
            //spin_lock_bh(&pm_data->tx_lock);
            ret = prepare_to_visit_node(ps_core_d);
            if (ret < 0)
            {
                PS_PRINT_ERR("prepare work FAIL\n");
                post_to_visit_node(ps_core_d);
                return ret;
            }
            post_to_visit_node(ps_core_d);
        }
    }

    return SUCCESS;
}

/*****************************************************************************
 * Prototype    : bfg_dev_power_off
 * Description  : bfg device power off function
 * Input        : void
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/07/29
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 bfg_dev_power_off(void)
{

    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    int32 ret;

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -FAILURE;
    }

    if (check_dev_is_shutdown(WLAN_STATE_FLAG))
    {
        pm_data->ps_pm_interface->operate_beat_timer(BEAT_TIMER_DELETE);
        pm_data->bfgx_dev_state = BFGX_SLEEP;
        PS_PRINT_INFO("bfgx pull down power_on_enable gpio\n");
        board_power_off();
    }
    else
    {
         ret = uart_bfgx_close_cmd();
         if(SUCCESS != ret)
         {
            return -FAILURE;
         }
         pm_data->bfgx_dev_state = BFGX_SLEEP;

         ret = wlan_pm_shutdown_bcpu_cmd();
         if(OAL_SUCC != ret)
         {
            plat_pm_exception_process(PM_EXCEPT_BCPU_CLOSE_FAIL);
            return -FAILURE;
         }
    }

    /* we do NOT need bfg timer anymore */
    del_timer(&pm_data->bfg_timer);

    /* 下电即将完成，需要在此时设置下次上电要等待device上电成功的flag */
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    /*if wakelock is active, we should wake unlock*/
    if (wake_lock_active(&pm_data->bfg_wake_lock))
    {
        wake_unlock(&pm_data->bfg_wake_lock);
    }

	return SUCCESS;
}

/*****************************************************************************
 * Prototype    : hi110x_power_off
 * Description  : hi110x device power off function
 * Input        : uint8 type: means one of wlan/bt/fm/gnss
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/07/29
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 hi110x_power_off(uint8 type)
{
    int32 state = 0;
    struct ps_core_s *ps_core_d = NULL;
    struct oal_sdio  *hi_sdio = NULL;
    int32 ret;

    /*get pm driver data*/
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    hi_sdio = oal_alloc_sdio_stru();

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return -FAILURE;
    }

    //mutex_lock(&pm_data->host_mutex);

    if (WLAN_STATE_FLAG == type)
    {
        PS_PRINT_INFO("wlan power off!\n");

        if (check_dev_is_shutdown(BT_GNSS_FM_NFC_IR_STATE_FLAG))
        {
            PS_PRINT_INFO("wifi pull down power_on_enable!\n");
            oal_sdio_set_state(hi_sdio, OAL_FALSE);
            board_power_off();
        }
        else
        {
            /*wakeup dev,send poweroff cmd to wifi*/
            ret = wlan_pm_poweroff_cmd();
            if(OAL_SUCC != ret)
            {
                plat_pm_exception_process(PM_EXCEPT_WIFI_POWEROFF_CMD_FAIL);
                return -FAILURE;
            }
            else
            {
                oal_sdio_set_state(hi_sdio, OAL_FALSE);
                /*power off cmd execute succ,send shutdown wifi cmd to BFGN */
                ret = uart_wifi_close();
                if(OAL_SUCC != ret)
                {
                    plat_pm_exception_process(PM_EXCEPT_UART_CLOSE_WIFI_FAIL);
                    return -FAILURE;
                }
            }
        }

        
        oal_wlan_gpio_intr_enable(hi_sdio, OAL_FALSE);

        pm_data->pst_wlan_pm_info->ul_wlan_power_state = WLAN_STATE_SHUTDOWN;
    }
    /*when power off gnss, we don't care bfg low power timer*/
    else if (GNSS_STATE_FLAG == type)
    {
        PS_PRINT_INFO("gnss power off!\n");

        if (check_dev_is_shutdown(BT_FM_NFC_IR_STATE_FLAG))
        {
            bfg_dev_power_off();
        }

        atomic_set(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state, SUBSYS_STATE_SHUTDOWN);
    }
    else if (NFC_STATE_FLAG == type)
    {
        PS_PRINT_INFO("nfc power off!\n");

        if (check_dev_is_shutdown(BT_GNSS_FM_IR_STATE_FLAG))
        {
            bfg_dev_power_off();
        }

        atomic_set(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state, SUBSYS_STATE_SHUTDOWN);
    }
    else if (IR_STATE_FLAG == type)
    {
        PS_PRINT_INFO("ir power off!\n");

        if (check_dev_is_shutdown(BT_GNSS_FM_NFC_STATE_FLAG))
        {
            bfg_dev_power_off();
        }

        atomic_set(&ps_core_d->bfgx_info[BFGX_IR].subsys_state, SUBSYS_STATE_SHUTDOWN);
    }
    /*when power off bt or fm, we should judge the state of the other*/
    else
    {
        if (BT_STATE_FLAG == type)
        {
            PS_PRINT_INFO("bt power off!\n");
            state = check_dev_is_shutdown(FM_STATE_FLAG);
        }
        else if (FM_STATE_FLAG == type)
        {
            PS_PRINT_INFO("fm power off!\n");
            state = check_dev_is_shutdown(BT_STATE_FLAG);
        }

        if (state)
        {
            /*delete bfg low-power timer*/
            //pm_data->ps_pm_interface->reset_bt_timer(0);
        }

        if (BT_STATE_FLAG == type)
        {
            if (check_dev_is_shutdown(GNSS_FM_NFC_IR_STATE_FLAG))
            {
                bfg_dev_power_off();
            }

            atomic_set(&ps_core_d->bfgx_info[BFGX_BT].subsys_state, SUBSYS_STATE_SHUTDOWN);
        }
        else if (FM_STATE_FLAG == type)
        {
            if (check_dev_is_shutdown(BT_GNSS_NFC_IR_STATE_FLAG))
            {
                bfg_dev_power_off();
            }

            atomic_set(&ps_core_d->bfgx_info[BFGX_FM].subsys_state, SUBSYS_STATE_SHUTDOWN);
        }
    }

    //mutex_unlock(&pm_data->host_mutex);

    return SUCCESS;
}

/*****************************************************************************
 * Prototype    : bfg_dev_power_control
 * Description  : bfg power control function
 * Input        : int32 flag: 1 means on, 0 means off
                  uint8 type: means one of bfg
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/07/29
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 bfg_dev_power_control(uint8 type, uint8 flag)
{
    int32 ret                   = 0;


    if (1 == flag)
    {
        ret = hi110x_power_on(type);
        if (ret)
        {
            PS_PRINT_ERR("bfg power on is error!\n");
        }
    }
    else if (0 == flag)
    {
        ret = hi110x_power_off(type);
        if (ret)
        {
            PS_PRINT_ERR("bfg power off is error!\n");
        }
    }
    else
    {
        PS_PRINT_ERR("invalid input data!\n");
        ret = -FAILURE;
    }

    return ret;
}

/*****************************************************************************
 * Prototype    : firmware_download_function
 * Description  : download wlan patch
 * Input        : which_cfg
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int firmware_download_function(uint32 which_cfg)
{
    int32 ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    if (which_cfg >= CFG_FILE_TOTAL)
    {
        PS_PRINT_ERR("cfg file index [%d] outof range\n", which_cfg);
        return -FAILURE;
    }

    PS_PRINT_ERR("enter firmware_download_function\n");

    /*firmware_cfg_init(sdio) function should just be called once*/
    if (!test_bit(SDIO_INIT_OK, &pm_data->patch_init_flag))
    {

        PS_PRINT_ERR("firmware_cfg_init begin\n");
        ret = firmware_cfg_init();
        if (ret)
        {
            PS_PRINT_ERR("firmware_cfg_init failed, ret:%d!\n", ret);
            return ret;
        }

        PS_PRINT_INFO("firmware_cfg_init OK\n");
        set_bit(SDIO_INIT_OK, &pm_data->patch_init_flag);
    }

    PS_PRINT_INFO("start to power restore sdio\n");
    ret = mmc_power_save_host(pm_data->pst_wlan_pm_info->pst_sdio->func->card->host);
    pm_data->pst_wlan_pm_info->pst_sdio->func->card->host->pm_flags &= ~MMC_PM_KEEP_POWER;
    ret = mmc_power_restore_host(pm_data->pst_wlan_pm_info->pst_sdio->func->card->host);
    pm_data->pst_wlan_pm_info->pst_sdio->func->card->host->pm_flags |= MMC_PM_KEEP_POWER;
    if(ret < 0)
    {
        PS_PRINT_ERR("failed to mmc_power_restore_host\n");
    }

    if (sdio_dev_init(pm_data->pst_wlan_pm_info->pst_sdio->func) != SUCCESS)
    {
        PS_PRINT_ERR("sdio dev reinit failed\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("sdio_dev_init ok\n");

    wlan_pm_init_dev();

    PS_PRINT_INFO("firmware_download begin\n");
    ret = firmware_download(which_cfg);
    if (ret < 0)
    {
        PS_PRINT_ERR("firmware download fail!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("firmware_download success\n");

	msleep(100);

    return SUCCESS;
}

/*****************************************************************************
 * Prototype    : ps_pm_register
 * Description  : register interface for 3 in 1
 * Input        : struct ps_pm_s *new_pm: interface want to register
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 ps_pm_register(struct ps_pm_s *new_pm)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL\n");
        return -FAILURE;
    }

    if (NULL == new_pm)
    {
        PS_PRINT_ERR("new_pm is null!\n");
        return -FAILURE;
    }

    pm_data->ps_pm_interface                        = new_pm;
    pm_data->ps_pm_interface->pm_priv_data          = pm_data;
    pm_data->ps_pm_interface->bfg_mutex_lock        = bfg_mutex_lock;
    pm_data->ps_pm_interface->bfg_wake_lock         = bfg_wake_lock;
    pm_data->ps_pm_interface->bfg_wake_unlock       = bfg_wake_unlock;
    pm_data->ps_pm_interface->bfg_spin_lock         = bfg_spin_lock;
    pm_data->ps_pm_interface->bfgx_dev_state_get    = bfgx_state_get;
    pm_data->ps_pm_interface->bfgx_dev_state_set    = bfgx_state_set;
    pm_data->ps_pm_interface->bfg_power_set         = bfg_dev_power_control;
    pm_data->ps_pm_interface->bfgx_uart_state_get   = bfgx_uart_state_get;
    pm_data->ps_pm_interface->bfgx_uart_state_set   = bfgx_uart_state_set;

    PS_PRINT_SUC("pm registered over!");

    return SUCCESS;
}
EXPORT_SYMBOL_GPL(ps_pm_register);

/*****************************************************************************
 * Prototype    : ps_pm_unregister
 * Description  : unregister interface for 3 in 1
 * Input        : struct ps_pm_s *new_pm: interface want to unregister
 * Output       : none
 * Return       : 0 means succeed,-1 means failed
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2013/01/22
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
int32 ps_pm_unregister(struct ps_pm_s *new_pm)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL\n");
        return -FAILURE;
    }

    PS_PRINT_DBG("enter\n");

    if (NULL == new_pm)
    {
        PS_PRINT_ERR("new_pm is null!\n");
        return -FAILURE;
    }

    new_pm->bfg_mutex_lock          = NULL;
    new_pm->bfg_wake_lock           = NULL;
    new_pm->bfg_wake_unlock         = NULL;
    new_pm->bfg_spin_lock           = NULL;
    new_pm->bfgx_dev_state_get      = NULL;
    new_pm->bfgx_dev_state_set      = NULL;
    new_pm->bfg_power_set           = NULL;
    new_pm->bfgx_uart_state_set     = NULL;
    new_pm->bfgx_uart_state_get     = NULL;
    pm_data->ps_pm_interface        = NULL;

    PS_PRINT_SUC("pm unregistered over!");

    return SUCCESS;
}
EXPORT_SYMBOL_GPL(ps_pm_unregister);



/*****************************************************************************
 * Prototype    : bfg_wake_host_isr
 * Description  : functions called when bt wake host via GPIO
 * Input        : irq, dev_id
 * Output       : no
 * Return       :
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/26
 *     Author       : cwx145522
 *     Modification : Created function

*****************************************************************************/
irqreturn_t bfg_wake_host_isr(int irq, void *dev_id)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return IRQ_NONE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (ps_core_d == NULL)
    {
        PS_PRINT_ERR("ps_core_d is null\n");
        return IRQ_NONE;
    }
/*
    if (false == ps_chk_bfg_active(ps_core_d))
    {
        PS_PRINT_ERR("ignore bfgx gpio isr\n");
        return IRQ_NONE;
    }
*/
    ps_core_d->ps_pm->bfg_wake_lock();
    bfgx_state_set(BFGX_ACTIVE);
    if (1 == atomic_read(&pm_data->bfg_needwait_devboot_flag))
    {
        complete(&pm_data->dev_bootok_ack_comp);
    }
    //mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    queue_work(pm_data->wkup_dev_workqueue, &pm_data->send_disallow_msg_work);

    return IRQ_HANDLED;
}

/*return 1 for wifi power on,0 for off.*/
oal_int32 hi110x_get_wifi_power_stat(oal_void)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    return (pm_data->pst_wlan_pm_info->ul_wlan_power_state != WLAN_STATE_SHUTDOWN);
}
EXPORT_SYMBOL(hi110x_get_wifi_power_stat);

STATIC int low_power_remove(void)
{
    int ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    wlan_pm_exit();

    /*remove kobject*/
    pm_user_ctrl_exit();

    /*delete timer*/
    del_timer_sync(&pm_data->bfg_timer);
    del_timer_sync(&pm_data->dev_ack_timer);


    /*destory wake lock*/
    wake_lock_destroy(&pm_data->bfg_wake_lock);

    /*free platform driver data struct*/
    kfree(pm_data);

    pm_data = NULL;

    pm_set_drvdata(NULL);

    return ret;
}

STATIC void devack_timer_expire(uint64 data)
{
    struct pm_drv_data  *pm_data = (struct pm_drv_data*)data;
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("devack timer para is null\n");
        return;
    }

    PS_PRINT_INFO("%s", __func__);

    if (1 == board_get_bwkup_gpio_val())
    {
        /* device doesn't agree to sleep */
        PS_PRINT_INFO("device does not agree to sleep\n");
        if (unlikely(1 == pm_data->rcvdata_bef_devack_flag))
        {
            PS_PRINT_INFO("device send data to host before dev rcv allow slp msg\n");
            pm_data->rcvdata_bef_devack_flag = 0;
        }
        bfgx_state_set(BFGX_ACTIVE);
        pm_data->ps_pm_interface->bfgx_uart_state_set(UART_READY);
        /* if only gnss is open, do NOT mod bfg timer */
        if(!check_dev_is_shutdown(BT_FM_NFC_IR_STATE_FLAG))
        {
            mod_timer(&pm_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
        }
        complete(&pm_data->dev_ack_comp);
    }
    else
    {
        PS_PRINT_INFO("device agree to sleep, but host did not get the ack\n");
        pm_data->ps_pm_interface->operate_beat_timer(BEAT_TIMER_DELETE);
        bfg_wake_unlock();
        complete(&pm_data->dev_ack_comp);
    }

}

STATIC int low_power_probe(void)
{
    int ret = 0;
    struct pm_drv_data  *pm_data = NULL;
    struct workqueue_struct * host_wkup_dev_workq = NULL;

    pm_data = kzalloc(sizeof(struct pm_drv_data), GFP_KERNEL);
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("no mem to allocate pm_data\n");
        goto PMDATA_MALLOC_FAIL;
    }

    pm_data->pst_wlan_pm_info = wlan_pm_init();
    if(0 == pm_data->pst_wlan_pm_info)
    {
        PS_PRINT_ERR("no mem to allocate wlan_pm_info\n");
        goto WLAN_INIT_FAIL;
    }

    pm_data->patch_init_flag         = 0;
    pm_data->rcvdata_bef_devack_flag = 0;
    pm_data->bfgx_dev_state         = BFGX_SLEEP;
    pm_data->bfgx_lowpower_enable   = BFGX_PM_DISABLE;            /* enable host low_power function defaultly */
    pm_data->bfgx_bt_lowpower_enable   = BFGX_PM_DISABLE;
    pm_data->bfgx_gnss_lowpower_enable = BFGX_PM_DISABLE;
    pm_data->bfgx_nfc_lowpower_enable  = BFGX_PM_DISABLE;

    atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    atomic_set(&pm_data->bfg_needwait_devboot_flag, NEED_SET_FLAG);

    /* create an ordered workqueue with @max_active = 1 & WQ_UNBOUND flag to wake up device */
    host_wkup_dev_workq = create_singlethread_workqueue("wkup_dev_workqueue");
    if (!host_wkup_dev_workq)
    {
        PS_PRINT_ERR("create wkup workqueue failed\n");
        goto CREATE_WORKQ_FAIL;
    }
    pm_data->wkup_dev_workqueue = host_wkup_dev_workq;
    INIT_WORK(&pm_data->wkup_dev_work, host_wkup_dev_work);
    INIT_WORK(&pm_data->send_disallow_msg_work, host_send_disallow_msg);

	pm_data->board					= get_board_info();

    pm_data->bfg_irq = pm_data->board->bfgn_irq;

    /*init bfg wake lock */
    wake_lock_init(&pm_data->bfg_wake_lock, WAKE_LOCK_SUSPEND, BFG_LOCK_NAME);

    /*init mutex*/
    mutex_init(&pm_data->host_mutex);

    /*init spinlock*/
    spin_lock_init(&pm_data->tx_lock);
    spin_lock_init(&pm_data->node_timer_spinlock);

    /* init timer */
    init_timer(&pm_data->dev_ack_timer);
    pm_data->dev_ack_timer.function = devack_timer_expire;
    pm_data->dev_ack_timer.data     = (unsigned long)pm_data;

    /* init bfg data timer */
    init_timer(&pm_data->bfg_timer);
    pm_data->bfg_timer.function = bfg_timer_expire;
    pm_data->bfg_timer.data     = (unsigned long)pm_data;

    /* init completion */
    init_completion(&pm_data->host_wkup_dev_comp);
    init_completion(&pm_data->dev_ack_comp);
    init_completion(&pm_data->dev_bootok_ack_comp);

    /*set driver data*/
    pm_set_drvdata(pm_data);

    ret = pm_user_ctrl_init();
    if (ret)
    {
        PS_PRINT_ERR("failed to create power properties!\n");
        goto PM_USER_CTL_FAIL;
    }

    return OAL_SUCC;

PM_USER_CTL_FAIL:

CREATE_WORKQ_FAIL:

WLAN_INIT_FAIL:
    kfree(pm_data);
PMDATA_MALLOC_FAIL:
    return -ENOMEM;
}

int low_power_init(void)
{
    int ret = -FAILURE;

	ret = low_power_probe();
    if (SUCCESS != ret)
    {
        PS_PRINT_ERR("low_power_init: low_power_probe fail\n");
    }

     PS_PRINT_INFO("low_power_init: success\n");
    return ret;
}

void  low_power_exit(void)
{
	low_power_remove();
    firmware_cfg_clear();
}

