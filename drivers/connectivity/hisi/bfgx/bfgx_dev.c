

/*****************************************************************************
  1 Include Head file
*****************************************************************************/
#include <linux/platform_device.h>
#include <linux/jiffies.h>
#include <linux/kernel.h>
#include <linux/ktime.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/tty.h>
#include <linux/poll.h>
#include <linux/module.h>
#include <linux/miscdevice.h>

#include "board.h"
#include "hw_bfg_ps.h"
#include "plat_type.h"
#include "plat_debug.h"
#include "plat_uart.h"
#include "plat_pm.h"
#include "bfgx_user_ctrl.h"
#include "bfgx_exception_rst.h"

/*****************************************************************************
  Define global variable
*****************************************************************************/
/**
 * This references is the per-PS platform device in the arch/arm/
 * board-xx.c file.
 */
struct platform_device *hw_ps_device = NULL;
STATIC int g_debug_cnt = 0;
extern int isAsic(void);

/*****************************************************************************
  Function implement
*****************************************************************************/

/**********************************************************************/
/* internal functions */
/**
 * Prototype    : ps_get_plat_reference
 * Description  : reference the plat's dat,This references the per-PS
 *                  platform device in the arch/arm/board-xx.c file.
 * input        : use *hw_ps_device
 * output       : the have registered platform device struct
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_get_plat_reference(struct ps_plat_s **plat_data)
{
    struct platform_device   *pdev = NULL;
    struct ps_plat_s    *ps_plat_d = NULL;

    pdev = hw_ps_device;
    if (!pdev)
    {
        *plat_data = NULL;
        PS_PRINT_ERR("%s pdev is NULL\n", __func__);
        return FAILURE;
    }

    ps_plat_d  = dev_get_drvdata(&pdev->dev);
    *plat_data = ps_plat_d;

    return SUCCESS;
}

/**
 * Prototype    : ps_get_core_reference
 * Description  : reference the core's data,This references the per-PS
 *                  platform device in the arch/xx/board-xx.c file..
 * input        : use *hw_ps_device
 * output       : the have registered ps_core_d struct
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_get_core_reference(struct ps_core_s **core_data)
{
    struct platform_device *pdev = NULL;
    struct ps_plat_s  *ps_plat_d = NULL;

    pdev = hw_ps_device;
    if (!pdev)
    {
        *core_data = NULL;
        PS_PRINT_ERR("%s pdev is NULL\n", __func__);
        return FAILURE;
    }

    ps_plat_d  = dev_get_drvdata(&pdev->dev);
    *core_data = ps_plat_d->core_data;

    return SUCCESS;
}

/**
 * Prototype    : ps_change_baud_rate_complete
 * Description  : to signal completion of change baud rate function
 *                  called from PS Core, upon tty_open.
 * input        : ps_plat_d
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_change_baud_rate_complete(void *pm_data)
{
    struct ps_plat_s *ps_plat_d = (struct ps_plat_s *)pm_data;

    PS_PRINT_INFO("%s\n", __func__);
    complete(&ps_plat_d->change_baud_rate);
    return SUCCESS;
}

/**
 * Prototype    : ps_chk_bfg_active
 * Description  : to chk wether or not bfg active
 *
 * input        : ps_plat_d
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
bool ps_chk_bfg_active(struct ps_core_s *ps_core_d)
{
    int32 i = 0;
    for (i = 0; i < BFGX_BUTT; i++)
    {
        if (SUBSYS_STATE_SHUTDOWN != atomic_read(&ps_core_d->bfgx_info[i].subsys_state))
        {
            return true;
        }
    }

    return false;
}

/* only gnss is open and it agree to sleep */
bool ps_chk_only_gnss_and_cldslp(struct ps_core_s *ps_core_d)
{
    if ((SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_BT].subsys_state)) &&
        (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_FM].subsys_state)) &&
        (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_IR].subsys_state)) &&
        (SUBSYS_STATE_SHUTDOWN == atomic_read(&ps_core_d->bfgx_info[BFGX_NFC].subsys_state)) &&
        (SUBSYS_STATE_OPEN == atomic_read(&ps_core_d->bfgx_info[BFGX_GNSS].subsys_state))   &&
        (GNSS_AGREE_SLEEP == atomic_read(&((struct pm_drv_data *)(ps_core_d->pm_data))->gnss_sleep_flag)))
    {
        return true;
    }
    return false;
}

/**
 * Prototype    : ps_alloc_skb
 * Description  : allocate mem for new skb
 *
 * input        : ps_plat_d
 * output       : no
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
struct sk_buff *ps_alloc_skb(uint16 len)
{
    struct sk_buff *skb = NULL;

    PS_PRINT_FUNCTION_NAME;

    skb = alloc_skb(len, GFP_ATOMIC);
    if (NULL == skb)
	{
        PS_PRINT_WARNING("can't allocate mem for new skb\n");
        return NULL;
    }

    skb_put(skb, len);

    return skb;
}

/**
 * Prototype    : ps_kfree_skb
 * Description  : when close a function, kfree skb
 * input        : ps_core_d, skb type
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
void ps_kfree_skb(struct ps_core_s *ps_core_d, uint8 type)
{
    struct sk_buff *skb = NULL;

    PS_PRINT_FUNCTION_NAME;
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL");
        return;
    }

    while ((skb = ps_skb_dequeue(ps_core_d, type)))
    {
        kfree_skb(skb);
    }

    switch (type)
    {
    case TX_HIGH_QUEUE:
        skb_queue_purge(&ps_core_d->tx_high_seq);
        break;
    case TX_LOW_QUEUE:
        skb_queue_purge(&ps_core_d->tx_low_seq);
        break;
    case RX_GNSS_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_GNSS].rx_queue);
        break;
    case RX_FM_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_FM].rx_queue);
        break;
    case RX_BT_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_BT].rx_queue);
        break;
    case RX_DBG_QUEUE:
        skb_queue_purge(&ps_core_d->rx_dbg_seq);
        break;
    case RX_NFC_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_NFC].rx_queue);
        break;
    case RX_IR_QUEUE:
        skb_queue_purge(&ps_core_d->bfgx_info[BFGX_IR].rx_queue);
        break;
    default:break;
    }
    return;
}

/**
 * Prototype    : ps_restore_skbqueue
 * Description  : when err and restore skb to seq function.
 * input        : ps_core_d, skb
 * output       : not
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_restore_skbqueue(struct ps_core_s *ps_core_d, struct sk_buff *skb, uint8 type)
{
    PS_PRINT_FUNCTION_NAME;

    if (unlikely((NULL == skb) || (NULL == ps_core_d)))
    {
        PS_PRINT_ERR(" skb or ps_core_d is NULL\n");
        return -EINVAL;
    }

    switch (type)
    {
    case RX_GNSS_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_GNSS].rx_queue, skb);
        break;
    case RX_FM_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_FM].rx_queue, skb);
        break;
    case RX_BT_QUEUE:
        skb_queue_head(&ps_core_d->bfgx_info[BFGX_BT].rx_queue, skb);
        break;
    case RX_DBG_QUEUE:
        skb_queue_head(&ps_core_d->rx_dbg_seq, skb);
        break;
    default:
        break;
    }

    return 0;
}



STATIC void host_allow_devslp_in_node(struct ps_core_s *ps_core_d)
{
    /* make "host_allow_bfg_sleep()" happy */
    atomic_dec(&ps_core_d->node_visit_flag);
    host_allow_bfg_sleep(ps_core_d);
    /* recovery the original value */
    atomic_inc(&ps_core_d->node_visit_flag);
}

/* prepare to visit dev_node
*/
int32 prepare_to_visit_node(struct ps_core_s *ps_core_d)
{
    struct pm_drv_data *pm_data = NULL;
    uint8 uart_ready = UART_NOT_READY;
    int32  ret = 0;

    pm_data = pm_get_drvdata();
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EFAULT;
    }

    /* lock wake_lock */
    ps_core_d->ps_pm->bfg_wake_lock();

    /* open tty if tty has not been opened */
    ret = open_tty_drv(ps_core_d->pm_data);
    if (ret != 0)
    {
        PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
        return -EIO;
    }

    /* try to wake up device */
    spin_lock_bh(&pm_data->node_timer_spinlock);
    atomic_inc(&ps_core_d->node_visit_flag);    /* mark someone is visiting dev node */
    uart_ready = ps_core_d->ps_pm->bfgx_uart_state_get();
    spin_unlock_bh(&pm_data->node_timer_spinlock);
    if (UART_NOT_READY == uart_ready)
    {
        if (0 != host_wkup_dev())
        {
            PS_PRINT_ERR("wkup device FAILED!\n");
            return -EIO;
        }
    }

    /*
    if (&ps_core_d->ps_pm->pm_priv_data->bfg_timer == &pm_data->bfg_timer)
    {
        PS_PRINT_INFO("bfg timer is right\n");
    }
    */

    return 0;
}

/* we should do something before exit from visiting dev_node */
int32 post_to_visit_node(struct ps_core_s *ps_core_d)
{
    atomic_dec(&ps_core_d->node_visit_flag);

    return 0;
}

int32 kzalloc_seperted_rx_buf(uint8 subsys, uint32 len)
{
    struct ps_core_s *ps_core_d = NULL;
    struct bfgx_sepreted_rx_st *pst_sepreted_data = NULL;
    uint8 *p_rx_buf = NULL;

    if (subsys >= BFGX_BUTT)
    {
        PS_PRINT_ERR("subsys out of range! subsys=%d\n", subsys);
        return -EINVAL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }
    pst_sepreted_data = &ps_core_d->bfgx_info[subsys].sepreted_rx;

    p_rx_buf = kzalloc(len, GFP_ATOMIC);
    if (NULL == p_rx_buf)
    {
        PS_PRINT_ERR("kzalloc failed! subsys=%d\n, len=%d", subsys, len);
        return -ENOMEM;
    }

    spin_lock(&pst_sepreted_data->sepreted_rx_lock);
    pst_sepreted_data->rx_prev_seq = RX_SEQ_NULL;
    pst_sepreted_data->rx_buf_all_len = 0;
    pst_sepreted_data->rx_buf_ptr = p_rx_buf;
    pst_sepreted_data->rx_buf_org_ptr = p_rx_buf;
    spin_unlock(&pst_sepreted_data->sepreted_rx_lock);

    return 0;
}

int32 kfree_seperted_rx_buf(uint8 subsys)
{
    struct ps_core_s *ps_core_d = NULL;
    struct bfgx_sepreted_rx_st *pst_sepreted_data = NULL;

    if (subsys >= BFGX_BUTT)
    {
        PS_PRINT_ERR("subsys out of range! subsys=%d\n", subsys);
        return -EINVAL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }
    pst_sepreted_data = &ps_core_d->bfgx_info[subsys].sepreted_rx;

    spin_lock(&pst_sepreted_data->sepreted_rx_lock);
    if (NULL != pst_sepreted_data->rx_buf_org_ptr)
    {
        kfree(pst_sepreted_data->rx_buf_org_ptr);
    }
    pst_sepreted_data->rx_prev_seq = RX_SEQ_NULL;
    pst_sepreted_data->rx_buf_all_len = 0;
    pst_sepreted_data->rx_buf_ptr = NULL;
    pst_sepreted_data->rx_buf_org_ptr = NULL;
    spin_unlock(&pst_sepreted_data->sepreted_rx_lock);

    return 0;
}

/**********************************************************************/

int32 uart_wifi_open(void)
{
    struct ps_core_s *ps_core_d = NULL;
    uint64 timeleft;
    int32 ret;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||
        (NULL == ps_core_d->ps_pm) ||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
#else
    if (unlikely(NULL == ps_core_d))
#endif
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    /*如果BFGIN睡眠，则唤醒之*/
    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }
    post_to_visit_node(ps_core_d);

    PS_PRINT_INFO("uart open WCPU\n");
    INIT_COMPLETION(ps_core_d->wait_wifi_opened);
    /* tx sys bt open info */
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_WIFI);

    timeleft = wait_for_completion_timeout(&ps_core_d->wait_wifi_opened, msecs_to_jiffies(WAIT_WIFI_OPEN_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait wifi open ack timeout\n");
        return -ETIMEDOUT;
    }

    msleep(20);

    return SUCCESS;
}

/**********************************************************************/

int32 uart_wifi_close(void)
{
    struct ps_core_s *ps_core_d = NULL;
    uint64 timeleft;
    int32  ret;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||
        (NULL == ps_core_d->ps_pm) ||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
#else
    if (unlikely(NULL == ps_core_d))
#endif
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    /*如果BFGIN睡眠，则唤醒之*/
    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }
    post_to_visit_node(ps_core_d);

    PS_PRINT_INFO("uart close WCPU\n");

    INIT_COMPLETION(ps_core_d->wait_wifi_closed);

    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_WIFI);

    timeleft = wait_for_completion_timeout(&ps_core_d->wait_wifi_closed, msecs_to_jiffies(WAIT_WIFI_CLOSE_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait wifi close ack timeout\n");
        return -ETIMEDOUT;
    }

    return SUCCESS;
}

/**********************************************************************/

int32 uart_bfgx_close_cmd(void)
{
#define wait_close_times  (100)
    struct ps_core_s *ps_core_d = NULL;
    //uint64 timeleft;
    int bwkup_gpio_val = 1;
    int32 ret;
    int i;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||
        (NULL == ps_core_d->ps_pm) ||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
#else
    if (unlikely(NULL == ps_core_d))
#endif
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    /*如果BFGIN睡眠，则唤醒之*/
    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }
    post_to_visit_node(ps_core_d);

    /*下发BFGIN shutdown命令*/
    PS_PRINT_INFO("uart shutdown BCPU\n");

    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_SHUTDOWN_SLP);

    ret = FAILURE;
    for(i=0;i<wait_close_times;i++)
    {
        bwkup_gpio_val = board_get_bwkup_gpio_val();
        if(0 == bwkup_gpio_val)
        {
            ret = SUCCESS;
            break;
        }
        msleep(10);
        PS_PRINT_INFO("bfg gpio level:%d\n", bwkup_gpio_val);
    }

    PS_PRINT_INFO("uart shutdown BCPU finished\n");

    return ret;
}


/**********************************************************************/
/**
 * Prototype    : hw_bt_open
 * Description  : functions called from above bt hal,when open bt file
 *                  input : "/dev/hwbt"
 * input        : return 0 --> open is ok
 * output       : return !0--> open is false
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_bt_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bt_data = NULL;
    uint64 timeleft;
    int32  ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
        return OAL_FAIL;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm) ||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_bt_data = &ps_core_d->bfgx_info[BFGX_BT];

    if (SUBSYS_STATE_OPEN == atomic_read(&pst_bt_data->subsys_state))
    {
        PS_PRINT_WARNING("[BFGX]""BT has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return 0;
    }

    if (isAsic())
    {
        ret = open_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }

        /* bfgx上电，上电逻辑中包含firmware加载 */
        ret = ps_core_d->ps_pm->bfg_power_set(BT_STATE_FLAG, BFG_POWER_GPIO_UP);
        if (ret)
        {
            PS_PRINT_ERR("set bt power on err!ret = %d\n", ret);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    /* do anthing what we actually want */
    INIT_COMPLETION(pst_bt_data->wait_opened);
    /* 向device发送打开bt命令，并等待bt线程初始化完成回复ACK */
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_BT);
    timeleft = wait_for_completion_timeout(&pst_bt_data->wait_opened, msecs_to_jiffies(WAIT_BT_OPEN_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait bt open ack timeout\n");
        /* if every sub-system has been closed, and no one is visit node, we could close tty */
        if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
        {
            PS_PRINT_ERR("bt open failed, need close uart!\n");
            release_tty_drv(ps_core_d->pm_data);
        }
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);

    atomic_set(&pst_bt_data->subsys_state, SUBSYS_STATE_OPEN);
    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_bt_read
 * Description  : functions called from above bt hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_bt_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1;

    PS_PRINT_FUNCTION_NAME;

    if (is_bfgx_exception())
    {
        PS_PRINT_ERR("bfgx is exception\n\n");
        return -EINVAL;
    }

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_BT_QUEUE)))
    {
        PS_PRINT_WARNING("bt read skb queue is null!\n");
        return 0;
    }

    /* read min value from skb->len or count */
    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_BT_QUEUE);
        return -EFAULT;
    }

    /* have read count1 byte */
    skb_pull(skb, count1);

    /* if skb->len = 0: read is over */
    if (0 == skb->len)
    {   /* curr skb data have read to user */
        kfree_skb(skb);
    }
    else
    {   /* if don,t read over; restore to skb queue */
        ps_restore_skbqueue(ps_core_d, skb, RX_BT_QUEUE);
    }
    if (ps_core_d->bfgx_info[BFGX_BT].rx_queue.qlen < (RX_BT_QUE_MAX_NUM/2) && (atomic_read(&ps_core_d->throttle_flag)))
    {   /* open RTS info, allow uart rx data */
        tty_unthrottle(ps_core_d->tty);
        atomic_set(&ps_core_d->throttle_flag, 0);
    }

    return count1;
}

/**
 * Prototype    : hw_bt_write
 * Description  : functions called from above bt hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_bt_write(struct file *filp, const int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb;
    uint16 total_len;
    int32  ret = 0;

    PS_PRINT_FUNCTION_NAME;

    if (is_bfgx_exception())
    {
        PS_PRINT_ERR("bfgx is exception\n\n");
        msleep(50);
        return -EINVAL;
    }

    ps_get_core_reference(&ps_core_d);
#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||
        (NULL == ps_core_d->tty)||(NULL == ps_core_d->ps_pm)))
#else
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
#endif
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > BT_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("bt skb len is too large!\n");
        return -EINVAL;
    }

    /* if high queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_high_seq.qlen > TX_HIGH_QUE_MAX_NUM)
    {
        PS_PRINT_ERR("bt tx high seqlen large than MAXNUM\n");
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }

    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    total_len = count + sizeof(struct ps_packet_head) + sizeof(struct ps_packet_end);

    skb  = ps_alloc_skb(total_len);
    if (NULL == skb)
    {
        PS_PRINT_ERR("ps alloc skb mem fail\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    if (copy_from_user(&skb->data[sizeof(struct ps_packet_head)], buf, count))
    {
        PS_PRINT_ERR("copy_from_user from bt is err\n");
        kfree_skb(skb);
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    ps_add_packet_head(skb->data, BT_MSG, total_len);
    ps_skb_enqueue(ps_core_d, skb, TX_HIGH_QUEUE);
    queue_work(ps_core_d->ps_tx_workqueue, &ps_core_d->tx_skb_work);

    post_to_visit_node(ps_core_d);

    return count;
}

/**
 * Prototype    : hw_bt_poll
 * Description  : called by bt func from hal;
 *                  check whether or not allow read and write
 * input        : file handle
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC uint32 hw_bt_poll(struct file *filp, poll_table *wait)
{
    struct ps_core_s *ps_core_d = NULL;
    uint32 mask = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    /* push curr wait event to wait queue */
    poll_wait(filp, &ps_core_d->bfgx_info[BFGX_BT].rx_wait, wait);

    if (ps_core_d->bfgx_info[BFGX_BT].rx_queue.qlen)
    {   /* have data to read */
        mask |= POLLIN | POLLRDNORM;
    }

    return mask;
}

/**
 * Prototype    : hw_bt_ioctl
 * Description  : called by bt func from hal; default not use
 * input        : file handle, cmd, arg
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int64 hw_bt_ioctl(struct file *file, uint32 cmd, uint64 arg)
{
    PS_PRINT_FUNCTION_NAME;

    return 0;
}

/**
 * Prototype    : hw_bt_release
 * Description  : called by bt func from hal when close bt inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/12/26
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_bt_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_bt_data = NULL;
    int32 ret = 0;
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
       PS_PRINT_ERR("pm_data is NULL!\n");
        return OAL_FAIL;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_bt_data = &ps_core_d->bfgx_info[BFGX_BT];

    wake_up_interruptible(&pst_bt_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    INIT_COMPLETION(pst_bt_data->wait_closed);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_BT);

    timeleft = wait_for_completion_timeout(&pst_bt_data->wait_closed, msecs_to_jiffies(WAIT_BT_CLOSE_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait bt close ack timeout\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    atomic_set(&pst_bt_data->subsys_state, SUBSYS_STATE_SHUTDOWN);
    ps_kfree_skb(ps_core_d, RX_BT_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(BT_STATE_FLAG, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            PS_PRINT_ERR("set bt power off err!ret = %d\n", ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
    {
        ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_DELETE);


        PS_PRINT_INFO("bt close release_tty_drv\n");
        ret = release_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("close tty is err! ret = %d",ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }

    }
    else
    {
        PS_PRINT_DBG("bfg is active\n");
        if (ps_chk_only_gnss_and_cldslp(ps_core_d))
        {
            PS_PRINT_SUC("bt power off request sleep!\n");
            host_allow_devslp_in_node(ps_core_d);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}


STATIC int32 hw_nfc_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_nfc_data = NULL;
    int32 ret = 0;
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);

    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm) ||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_nfc_data = &ps_core_d->bfgx_info[BFGX_NFC];

    if (SUBSYS_STATE_OPEN == atomic_read(&pst_nfc_data->subsys_state))
    {
        PS_PRINT_WARNING("NFC has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return 0;
    }

    ret = kzalloc_seperted_rx_buf(BFGX_NFC, NFC_RX_MAX_FRAME);
    if (0 != ret)
    {
        PS_PRINT_ERR("no mem to allocate to read nfc!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -ENOMEM;
    }

    if (isAsic())
    {
        ret = open_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
            kfree_seperted_rx_buf(BFGX_NFC);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }

        /* bfgx上电，上电逻辑中包含firmware加载 */
        ret = ps_core_d->ps_pm->bfg_power_set(NFC_STATE_FLAG, BFG_POWER_GPIO_UP);
        if (ret)
        {
            PS_PRINT_ERR("set nfc power on err!ret = %d\n", ret);
            kfree_seperted_rx_buf(BFGX_NFC);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    /* send msg to device & wait for ack */
    INIT_COMPLETION(pst_nfc_data->wait_opened);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_NFC);

    timeleft = wait_for_completion_timeout(&pst_nfc_data->wait_opened, msecs_to_jiffies(WAIT_NFC_OPEN_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait nfc open ack timeout\n");
        if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
        {
            PS_PRINT_ERR("nfc open failed, need close uart!\n");
            release_tty_drv(ps_core_d->pm_data);
        }
        post_to_visit_node(ps_core_d);
        kfree_seperted_rx_buf(BFGX_NFC);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);

    atomic_set(&pst_nfc_data->subsys_state, SUBSYS_STATE_OPEN);

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

STATIC ssize_t hw_nfc_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_NFC_QUEUE)))
    {
        PS_PRINT_WARNING("nfc read skb queue is null!");
        return 0;
    }

    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_NFC_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, count1);
    if (0 == skb->len)
    {
        kfree_skb(skb);
    }
    else
    {
        ps_restore_skbqueue(ps_core_d, skb, RX_NFC_QUEUE);
    }

    if (ps_core_d->bfgx_info[BFGX_NFC].rx_queue.qlen < (RX_NFC_QUE_MAX_NUM/2)
        && (atomic_read(&ps_core_d->throttle_flag)))
    {
        tty_unthrottle(ps_core_d->tty);
        atomic_set(&ps_core_d->throttle_flag, 0);
    }

    return count1;
}

STATIC ssize_t hw_nfc_write(struct file *filp, const int8 __user *buf,
                                size_t count, loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);

#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||
        (NULL == ps_core_d->tty)||(NULL == ps_core_d->ps_pm)))
#else
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
#endif
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > NFC_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("bt skb len is too large!\n");
        return -EINVAL;
    }

    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }
    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    /* to divide up packet function and tx to tty work */
    if (ps_tx_nfcbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_nfc_write is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    post_to_visit_node(ps_core_d);

    PS_PRINT_DBG("NFC data write end\n");

    return count;
}
STATIC uint32 hw_nfc_poll(struct file *filp, poll_table *wait)
{
    struct ps_core_s *ps_core_d = NULL;
    uint32 mask = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    /* push curr wait event to wait queue */
    poll_wait(filp, &ps_core_d->bfgx_info[BFGX_NFC].rx_wait, wait);

    if (ps_core_d->bfgx_info[BFGX_NFC].rx_queue.qlen)
    {   /* have data to read */
        mask |= POLLIN | POLLRDNORM;
    }

    return mask;
}

STATIC int32 hw_nfc_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_nfc_data = NULL;
    int32 ret = 0;
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);

    pst_nfc_data = &ps_core_d->bfgx_info[BFGX_NFC];

    wake_up_interruptible(&pst_nfc_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    INIT_COMPLETION(pst_nfc_data->wait_closed);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_NFC);
    timeleft = wait_for_completion_timeout(&pst_nfc_data->wait_closed, msecs_to_jiffies(WAIT_NFC_CLOSE_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait nfc close ack timeout\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    atomic_set(&pst_nfc_data->subsys_state, SUBSYS_STATE_SHUTDOWN);
    kfree_seperted_rx_buf(BFGX_NFC);
    ps_kfree_skb(ps_core_d, RX_NFC_QUEUE);


    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(NFC_STATE_FLAG, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            PS_PRINT_ERR("set nfc power off err!ret = %d\n", ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }


    if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
    {
        ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_DELETE);

        ret = release_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("close tty is err! ret = %d\n",ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }
    }
    else
    {
        PS_PRINT_DBG("bfg is active\n");
        if (ps_chk_only_gnss_and_cldslp(ps_core_d))
        {
            PS_PRINT_SUC("NFC power off request sleep!\n");
            host_allow_devslp_in_node(ps_core_d);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_ir_open
 * Description  : open ir device
 * input        : struct inode *inode, struct file *filp
 * output       : return 0
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC int32 hw_ir_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_ir_data = NULL;
    int32 ret = 0;
    //uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
    {
        PS_PRINT_ERR("ps_core_d is err\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_ir_data = &ps_core_d->bfgx_info[BFGX_IR];

    if (SUBSYS_STATE_OPEN == atomic_read(&pst_ir_data->subsys_state))
    {
        PS_PRINT_WARNING("IR has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return 0;
    }

    ret = kzalloc_seperted_rx_buf(BFGX_IR, IR_RX_MAX_FRAME);
    if (0 != ret)
    {
        PS_PRINT_ERR("no mem to allocate to read ir!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -ENOMEM;
    }

    if (isAsic())
    {
        ret = open_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
            kfree_seperted_rx_buf(BFGX_IR);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }

        /* bfgx上电，上电逻辑中包含firmware加载 */
        ret = ps_core_d->ps_pm->bfg_power_set(IR_STATE_FLAG, BFG_POWER_GPIO_UP);
        if (ret)
        {
            PS_PRINT_ERR("set ir power on err!ret = %d\n", ret);
            kfree_seperted_rx_buf(BFGX_IR);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        kfree_seperted_rx_buf(BFGX_IR);
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    /* send msg to device */
    //INIT_COMPLETION(ps_core_d->bfgx_info[BFGX_IR].wait_opened);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_IR);
#if 0
    timeleft = wait_for_completion_timeout(&ps_core_d->bfgx_info[BFGX_IR].wait_opened, msecs_to_jiffies(WAIT_IR_OPEN_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait ir open ack timeout\n");
        if (false == ps_chk_bfg_active(ps_core_d))
        {
            PS_PRINT_ERR("ir open failed, need close uart!\n");
            release_tty_drv(ps_core_d->pm_data);
        }

        atomic_set(&ps_core_d->bt_state_booting, 0);
        ps_core_d->ps_pm->bfg_mutex_lock(0);
        return -ETIMEDOUT;
    }
#endif
    // fix using ack mode
    msleep(500);

    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);

    atomic_set(&pst_ir_data->subsys_state, SUBSYS_STATE_OPEN);
    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_ir_read
 * Description  : read ir node data
 * input        : struct file *filp, int8 __user *buf, size_t count,loff_t *f_pos
 * output       : return read len
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_ir_read(struct file *filp, int8 __user *buf,
                                size_t count, loff_t *f_pos)
{
    uint16 ret_count;
    struct sk_buff *skb = NULL;
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_IR_QUEUE)))
    {
        PS_PRINT_WARNING("ir read skb queue is null!\n");
        return 0;
    }

    ret_count = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, ret_count))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_IR_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, ret_count);

    if (0 == skb->len)
    {
        kfree_skb(skb);
    }
    else
    {
        ps_restore_skbqueue(ps_core_d, skb, RX_IR_QUEUE);
    }

    if (ps_core_d->bfgx_info[BFGX_IR].rx_queue.qlen < (RX_IR_QUE_MAX_NUM/2)
        &&(atomic_read(&ps_core_d->throttle_flag)))
    {
        tty_unthrottle(ps_core_d->tty);
        atomic_set(&ps_core_d->throttle_flag, 0);
    }

    return ret_count;
}

/**
 * Prototype    : hw_ir_write
 * Description  : write data to ir node
 * input        : struct file *filp, const int8 __user *buf, size_t count, loff_t *f_pos
 * output       : return write len
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_ir_write(struct file *filp, const int8 __user *buf,
                                size_t count, loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);

#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||
        (NULL == ps_core_d->tty)||(NULL == ps_core_d->ps_pm)))
#else
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
#endif
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > IR_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("IR skb len is too large!\n");
        return -EINVAL;
    }

    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }
    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    /* to divide up packet function and tx to tty work */
    if (ps_tx_irbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_ir_write is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    post_to_visit_node(ps_core_d);
    PS_PRINT_DBG("IR data write end\n");

    return count;
}

/**
 * Prototype    : hw_ir_release
 * Description  : release
 * input        : struct inode *inode, struct file *filp
 * output       : return 0
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2015/2/11
 *     Author       : wx222439
 *     Modification : Created function
 *
 */
STATIC int32 hw_ir_release(struct inode *inode, struct file *filp)
{
    int32 ret = 0;
    //uint64 timeleft;
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_ir_data = NULL;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);

    pst_ir_data = &ps_core_d->bfgx_info[BFGX_IR];

    wake_up_interruptible(&pst_ir_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    //INIT_COMPLETION(ps_core_d->bfgx_info[BFGX_IR].wait_closed);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_IR);
#if 0
    timeleft = wait_for_completion_timeout(&ps_core_d->bfgx_info[BFGX_IR].wait_closed, msecs_to_jiffies(WAIT_IR_CLOSE_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait ir close ack timeout\n");
        return -ETIMEDOUT;
    }
#endif
    // fix using ack mode
    msleep(500);

    atomic_set(&pst_ir_data->subsys_state, SUBSYS_STATE_SHUTDOWN);
    kfree_seperted_rx_buf(BFGX_IR);
    ps_kfree_skb(ps_core_d, RX_IR_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(IR_STATE_FLAG, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            PS_PRINT_ERR("set ir power off err!ret = %d", ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
    {
        ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_DELETE);

        ret = release_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("close tty is err! ret = %d\n",ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }
    }
    else
    {
        PS_PRINT_DBG("bfg is active\n");
        if (ps_chk_only_gnss_and_cldslp(ps_core_d))
        {
            PS_PRINT_SUC("ir power off request sleep!\n");
            host_allow_devslp_in_node(ps_core_d);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**********************************************************************/
/**
 * Prototype    : hw_fm_open
 * Description  : functions called from above fm hal,when open fm file
 *                  input : "/dev/hwfm"
 * input        : return 0 --> open is ok
 * output       : return !0--> open is false
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_fm_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_fm_data = NULL;
    uint64 timeleft;
    int32 ret = 0;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_fm_data = &ps_core_d->bfgx_info[BFGX_FM];

    if (SUBSYS_STATE_OPEN == atomic_read(&pst_fm_data->subsys_state))
    {
        PS_PRINT_WARNING("FM has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return 0;
    }

    /* mem prepare */
    ret = kzalloc_seperted_rx_buf(BFGX_FM, FM_RX_MAX_FRAME);
    if (0 != ret)
    {
        PS_PRINT_ERR("no mem to allocate to read fm!\n");
        return -ENOMEM;
    }

    if (isAsic())
    {
        ret = open_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
            kfree_seperted_rx_buf(BFGX_FM);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }

        /* bfgx上电，上电逻辑中包含firmware加载 */
        ret = ps_core_d->ps_pm->bfg_power_set(FM_STATE_FLAG, BFG_POWER_GPIO_UP);
        if (ret)
        {
            PS_PRINT_ERR("set fm power on err!ret = %d\n", ret);
            kfree_seperted_rx_buf(BFGX_FM);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        kfree_seperted_rx_buf(BFGX_FM);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    /* send msg to device */
    INIT_COMPLETION(pst_fm_data->wait_opened);
    /* 向device发送打开fm命令，并等待fm线程初始化完成回复ACK */
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_FM);
    timeleft = wait_for_completion_timeout(&pst_fm_data->wait_opened, msecs_to_jiffies(WAIT_FM_OPEN_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait fm open ack timeout\n");
        if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
        {
            PS_PRINT_ERR("fm open failed, need close uart!\n");
            release_tty_drv(ps_core_d->pm_data);
        }
        post_to_visit_node(ps_core_d);

        kfree_seperted_rx_buf(BFGX_FM);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);

    ps_core_d->fm_read_delay = FM_READ_DEFAULT_TIME;

    atomic_set(&pst_fm_data->subsys_state, SUBSYS_STATE_OPEN);
    post_to_visit_node(ps_core_d);
    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_fm_read
 * Description  : functions called from above fm hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_fm_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1;
    int64 timeout;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (0 == ps_core_d->bfgx_info[BFGX_FM].rx_queue.qlen)
    {   /* if don,t data, and wait timeout function */
        if (filp->f_flags & O_NONBLOCK)
        {   /* if O_NONBLOCK read and return */
            return -EAGAIN;
        }
        /* timeout function;when have data,can interrupt */
        timeout = wait_event_interruptible_timeout(ps_core_d->bfgx_info[BFGX_FM].rx_wait,
            (ps_core_d->bfgx_info[BFGX_FM].rx_queue.qlen > 0), msecs_to_jiffies(ps_core_d->fm_read_delay));
        if (!timeout)
        {
            PS_PRINT_DBG("fm read time out!\n");
            return -ETIMEDOUT;
        }
    }

    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_FM_QUEUE)))
    {
        PS_PRINT_ERR("fm read err!\n");
        return -ETIMEDOUT;
    }

    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_FM_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, count1);

    /* if skb->len == 0: curr skb read is over */
    if (0 == skb->len)
    {   /* curr skb data have read to user */
        kfree_skb(skb);
    }
    else
    {   /* if don,t read over; restore to skb queue */
        ps_restore_skbqueue(ps_core_d, skb, RX_FM_QUEUE);
    }

    if (ps_core_d->bfgx_info[BFGX_FM].rx_queue.qlen < (RX_FM_QUE_MAX_NUM/2)
        &&(atomic_read(&ps_core_d->throttle_flag)))
    {   /* open RTS info, allow uart rx data */
        tty_unthrottle(ps_core_d->tty);
        atomic_set(&ps_core_d->throttle_flag, 0);
    }

    return count1;
}

/**
 * Prototype    : hw_fm_write
 * Description  : functions called from above fm hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_fm_write(struct file *filp, const int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||
        (NULL == ps_core_d->tty)||(NULL == ps_core_d->ps_pm)))
#else
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
#endif
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    /* if count is too large;and don,t tx */
    if (count > (FM_TX_MAX_FRAME - sizeof(struct ps_packet_head) - sizeof(struct ps_packet_end)))
    {
        PS_PRINT_ERR("err:fm packet is too large!\n");
        return -EINVAL;
    }

    /* if low queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }
    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);


    /* to divide up packet function and tx to tty work */
    if (ps_tx_fmbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_fm_write is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    post_to_visit_node(ps_core_d);

    PS_PRINT_DBG("FM data write end\n");

    return count;
}

/**
 * Prototype    : hw_fm_ioctl
 * Description  : called by hw func from hal when open power gpio or close power gpio
 * input        : file handle, cmd, arg
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int64 hw_fm_ioctl(struct file *file, uint32 cmd, uint64 arg)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == file)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (FM_SET_READ_TIME == cmd)
    {
        if (arg < FM_MAX_READ_TIME)
        {   /* set timeout for fm read function */
            ps_core_d->fm_read_delay = arg;
        }
        else
        {
            PS_PRINT_ERR("arg is too large!\n");
            return -EINVAL;
        }
    }

    return 0;
}

/**
 * Prototype    : hw_fm_release
 * Description  : called by fm func from hal when close fm inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_fm_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_fm_data = NULL;
    int32 ret = 0;
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_fm_data = &ps_core_d->bfgx_info[BFGX_FM];

    wake_up_interruptible(&pst_fm_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

	INIT_COMPLETION(pst_fm_data->wait_closed);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_FM);
    timeleft = wait_for_completion_timeout(&pst_fm_data->wait_closed, msecs_to_jiffies(WAIT_FM_CLOSE_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait fm close ack timeout\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    atomic_set(&pst_fm_data->subsys_state, SUBSYS_STATE_SHUTDOWN);
    kfree_seperted_rx_buf(BFGX_FM);
    ps_kfree_skb(ps_core_d, RX_FM_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(FM_STATE_FLAG, BFG_POWER_GPIO_DOWN);
        if (ret != 0)
        {
            PS_PRINT_ERR("set fm power off err!ret = %d", ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
    {
        ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_DELETE);

        ret = release_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("close tty is err!");
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }
    }
    else
    {
        PS_PRINT_DBG("bfg is active\n");
        if (ps_chk_only_gnss_and_cldslp(ps_core_d))
        {
            PS_PRINT_SUC("fm power off request sleep!\n");
            host_allow_devslp_in_node(ps_core_d);
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_gnss_open
 * Description  : functions called from above gnss hal,when open gnss file
 * input        : "/dev/hwgnss"
 * output       : return 0 --> open is ok
 *                return !0--> open is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_gnss_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_gnss_data = NULL;
    int32  ret = 0;
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);

    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)||
        (NULL == ps_core_d->ps_pm)||
        (NULL == ps_core_d->ps_pm->bfg_power_set)||
        (NULL == ps_core_d->ps_pm->bfg_mutex_lock)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);
    pst_gnss_data = &ps_core_d->bfgx_info[BFGX_GNSS];

    if (SUBSYS_STATE_OPEN == atomic_read(&pst_gnss_data->subsys_state))
    {
        PS_PRINT_WARNING("GNSS has opened! It's Not necessary to send msg to device\n");
        mutex_unlock(&pm_data->host_mutex);
        return 0;
    }

    /* mem prepare */
    ret = kzalloc_seperted_rx_buf(BFGX_GNSS, GNSS_RX_MAX_FRAME);
    if (0 != ret)
    {
        PS_PRINT_ERR("no mem to allocate to read gnss!\n");
        mutex_unlock(&pm_data->host_mutex);
        return -ENOMEM;
    }

    if (isAsic())
    {
        ret = open_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
            kfree_seperted_rx_buf(BFGX_GNSS);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }

        /* bfgx上电，上电逻辑中包含firmware加载 */
        ret = ps_core_d->ps_pm->bfg_power_set(GNSS_STATE_FLAG, BFG_POWER_GPIO_UP);
        if (ret)
        {
            PS_PRINT_ERR("set gnss power on err!ret = %d\n", ret);
            kfree_seperted_rx_buf(BFGX_GNSS);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        kfree_seperted_rx_buf(BFGX_GNSS);
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    INIT_COMPLETION(pst_gnss_data->wait_opened);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_OPEN_GNSS);

    timeleft = wait_for_completion_timeout(&pst_gnss_data->wait_opened, msecs_to_jiffies(WAIT_GNSS_OPEN_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait gnss open ack timeout\n");
        if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
        {
            PS_PRINT_ERR("gnss open failed, need close uart!\n");
            release_tty_drv(ps_core_d->pm_data);
        }
        post_to_visit_node(ps_core_d);
        kfree_seperted_rx_buf(BFGX_GNSS);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
    ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_RESET);

    ps_core_d->gnss_read_delay = GNSS_READ_DEFAULT_TIME;

    atomic_set(&((struct pm_drv_data *)(ps_core_d->pm_data))->gnss_sleep_flag, GNSS_NOT_AGREE_SLEEP);
    atomic_set(&pst_gnss_data->subsys_state, SUBSYS_STATE_OPEN);
    post_to_visit_node(ps_core_d);
    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**
 * Prototype    : hw_gnss_read
 * Description  : functions called from above gnss hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_gnss_read(struct file *filp, int8 __user *buf,
                                    size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    int32 count1;
    int64 timeout;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (0 == ps_core_d->bfgx_info[BFGX_GNSS].rx_queue.qlen)
    {   /* if no data, and wait timeout function */
        if (filp->f_flags & O_NONBLOCK)
        {   /* if O_NONBLOCK read and return */
            return -EAGAIN;
        }
        /* timeout function;when have data,can interrupt */
        timeout = wait_event_interruptible_timeout(ps_core_d->bfgx_info[BFGX_GNSS].rx_wait,
            (ps_core_d->bfgx_info[BFGX_GNSS].rx_queue.qlen > 0), msecs_to_jiffies(ps_core_d->gnss_read_delay));
        if (!timeout)
        {
            PS_PRINT_DBG("gnss read time out!\n");
            return -ETIMEDOUT;
        }
    }
    /* pull skb data from skb queue */
    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_GNSS_QUEUE)))
    {
        PS_PRINT_ERR("gnss read time out!\n");
        return -ETIMEDOUT;
    }
    /* read min value from skb->len or count */
    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_GNSS_QUEUE);
        return -EFAULT;
    }
    /* have read count1 byte */
    skb_pull(skb, count1);
    /* if skb->len = 0: read is over */
    if (0 == skb->len)
    {   /* curr skb data have read to user */
        kfree_skb(skb);
    }
    else
    {   /* if don,t read over; restore to skb queue */
        ps_restore_skbqueue(ps_core_d, skb, RX_GNSS_QUEUE);
    }

    if (ps_core_d->bfgx_info[BFGX_GNSS].rx_queue.qlen < (RX_GNSS_QUE_MAX_NUM/2) &&
            (atomic_read(&ps_core_d->throttle_flag)))
    {   /* open RTS info, allow uart rx data */
        tty_unthrottle(ps_core_d->tty);
        atomic_set(&ps_core_d->throttle_flag, 0);
    }
    return count1;
}

/**
 * Prototype    : hw_gnss_write
 * Description  : functions called from above gnss hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_gnss_write(struct file *filp, const int8 __user *buf,
                                    size_t count, loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
#ifdef FEATURE_PM_DOWNLOAD_PATCH
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)||
        (NULL == ps_core_d->tty)||(NULL == ps_core_d->ps_pm)))
#else
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
#endif
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (count > GNSS_TX_MAX_FRAME)
    {
        PS_PRINT_ERR("err:gnss packet is too large!\n");
        return -EINVAL;
    }

    /* if low queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }

    /* to divide up packet function and tx to tty work */
    if (ps_tx_gnssbuf(ps_core_d, buf, count) < 0)
    {
        PS_PRINT_ERR("hw_gnss_write is err\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

/**
 * Prototype    : hw_gnss_ioctl
 * Description  : called by gnss func from hal when open power gpio or close power gpio
 * input        : file handle, cmd, arg
 * output       : no
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int64 hw_gnss_ioctl(struct file *file, uint32 cmd, uint64 arg)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == file)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (GNSS_SET_READ_TIME == cmd)
    {
        if (arg < GNSS_MAX_READ_TIME)
        {   /* set timeout for gnss read function */
            ps_core_d->gnss_read_delay = arg;
        }
        else
        {
            PS_PRINT_ERR("arg is too large!\n");
            return -EINVAL;
        }
    }

    return 0;
}

/**
 * Prototype    : hw_gnss_release
 * Description  : called by gnss func from hal when close gnss inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_gnss_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    struct st_bfgx_data *pst_gnss_data = NULL;
    int32  ret = 0;
    uint64 timeleft;
    struct pm_drv_data *pm_data = pm_get_drvdata();

    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    mutex_lock(&pm_data->host_mutex);

    pst_gnss_data = &ps_core_d->bfgx_info[BFGX_GNSS];

    wake_up_interruptible(&pst_gnss_data->rx_wait);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return ret;
    }

    INIT_COMPLETION(pst_gnss_data->wait_closed);
    ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_GNSS);

    timeleft = wait_for_completion_timeout(&pst_gnss_data->wait_closed, msecs_to_jiffies(WAIT_GNSS_CLOSE_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("wait gnss close ack timeout\n");
        post_to_visit_node(ps_core_d);
        mutex_unlock(&pm_data->host_mutex);
        return -ETIMEDOUT;
    }

    atomic_set(&pst_gnss_data->subsys_state, SUBSYS_STATE_SHUTDOWN);
    atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    kfree_seperted_rx_buf(BFGX_GNSS);
    ps_kfree_skb(ps_core_d, RX_GNSS_QUEUE);

    if (isAsic())
    {
        ret = ps_core_d->ps_pm->bfg_power_set(GNSS_STATE_FLAG, BFG_POWER_GPIO_DOWN);
        if (ret)
        {
            PS_PRINT_ERR("set gnss power off err!ret = %d", ret);
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EPERM;
        }
    }


    if ((false == ps_chk_bfg_active(ps_core_d)) && (atomic_read(&ps_core_d->node_visit_flag) == 1))
    {
        ps_core_d->ps_pm->operate_beat_timer(BEAT_TIMER_DELETE);

        ret = release_tty_drv(ps_core_d->pm_data);
        if (ret != 0)
        {
            PS_PRINT_ERR("close tty is err!\n");
            post_to_visit_node(ps_core_d);
            mutex_unlock(&pm_data->host_mutex);
            return -EINVAL;
        }
    }

    post_to_visit_node(ps_core_d);

    mutex_unlock(&pm_data->host_mutex);

    return 0;
}

/**********************************************************************/
/**
 * Prototype    : hw_debug_open
 * Description  : functions called from above oam hal,when open debug file
 *                  input : "/dev/hwbfgdbg"
 * input        : return 0 --> open is ok
 * output       : return !0--> open is false
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_debug_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    //mod_timer(&ps_core_d->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);
	g_debug_cnt++;
    PS_PRINT_INFO("%s g_debug_cnt=%d", __func__, g_debug_cnt);
    atomic_set(&ps_core_d->dbg_func_has_open, 1);

    ps_core_d->dbg_read_delay = DBG_READ_DEFAULT_TIME;

    return 0;
}

/**
 * Prototype    : hw_debug_read
 * Description  : functions called from above oam hal,read count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual read byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_debug_read(struct file *filp, int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
    uint16 count1 = 0;
    int64 timeout;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (0 == ps_core_d->rx_dbg_seq.qlen)
    {   /* if no data, and wait timeout function */
        if (filp->f_flags & O_NONBLOCK)
        {   /* if O_NONBLOCK read and return */
            return -EAGAIN;
        }

        /* timeout function;when have data,can interrupt */
        timeout = wait_event_interruptible_timeout(ps_core_d->rx_dbg_wait,
            (ps_core_d->rx_dbg_seq.qlen > 0), msecs_to_jiffies(ps_core_d->dbg_read_delay));
        if (!timeout)
        {
            PS_PRINT_DBG("debug read time out!\n");
            return -ETIMEDOUT;
        }
    }

    /* pull skb data from skb queue */
    if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_DBG_QUEUE)))
    {
        PS_PRINT_ERR("dbg read err!\n");
        return -ETIMEDOUT;
    }
    /* read min value from skb->len or count */
    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("debug copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_DBG_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, count1);

    /* if skb->len == 0: curr skb read is over */
    if (0 == skb->len)
    {   /* curr skb data have read to user */
        kfree_skb(skb);
    }
    else
    {   /* if don,t read over; restore to skb queue */
        ps_restore_skbqueue(ps_core_d, skb, RX_DBG_QUEUE);
    }

    return count1;
}

/**
 * Prototype    : hw_debug_write
 * Description  : functions called from above oam hal,write count data to buf
 * input        : file handle, buf, count
 * output       : return size --> actual write byte size
 *
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC ssize_t hw_debug_write(struct file *filp, const int8 __user *buf,
                                size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb;
    uint16 total_len;
    int32 ret = 0;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    if (false == ps_core_d->tty_have_open)
    {
        PS_PRINT_ERR("err: uart not opened!\n");
        return -EFAULT;
    }

    if (count > (DBG_TX_MAX_FRAME - sizeof(struct ps_packet_head) - sizeof(struct ps_packet_end)))
    {
        PS_PRINT_ERR("err: dbg packet is too large!\n");
        return -EINVAL;
    }

    /* if low queue num > MAX_NUM and don't write */
    if (ps_core_d->tx_low_seq.qlen > TX_LOW_QUE_MAX_NUM)
    {
        return 0;
    }

#if 0
	if (POWER_OFF_STATE == ps_core_d->fm_state &&
		POWER_OFF_STATE == ps_core_d->gnss_state &&
		POWER_OFF_STATE == ps_core_d->bt_state)
	{

        PS_PRINT_ERR("bfg is closed, /dev/hwdebug cant't write!!!\n");
        return -EINVAL;
	}
#else
    if (false == ps_chk_bfg_active(ps_core_d))
    {

        PS_PRINT_ERR("bfg is closed, /dev/hwdebug cant't write!!!\n");
        return -EINVAL;
    }
#endif

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }
    /* modify expire time of uart idle timer */
    mod_timer(&ps_core_d->ps_pm->pm_priv_data->bfg_timer, jiffies + BT_SLEEP_TIME * HZ);

    total_len = count + sizeof(struct ps_packet_head) + sizeof(struct ps_packet_end);

    skb  = ps_alloc_skb(total_len);
    if (NULL == skb)
    {
        PS_PRINT_ERR("ps alloc skb mem fail\n");
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    if (copy_from_user(&skb->data[sizeof(struct ps_packet_head)], buf, count))
    {
        PS_PRINT_ERR("copy_from_user from dbg is err\n");
        kfree_skb(skb);
        post_to_visit_node(ps_core_d);
        return -EFAULT;
    }

    ps_add_packet_head(skb->data, OML_MSG, total_len);
    ps_skb_enqueue(ps_core_d, skb, TX_LOW_QUEUE);
    queue_work(ps_core_d->ps_tx_workqueue, &ps_core_d->tx_skb_work);

    post_to_visit_node(ps_core_d);

    return count;
}

/**
 * Prototype    : hw_debug_release
 * Description  : called by oam func from hal when close debug inode
 * input        : have opened file handle
 * output       : return 0 --> close is ok
 *                return !0--> close is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 hw_debug_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

	g_debug_cnt--;
    PS_PRINT_INFO("%s g_debug_cnt=%d", __func__, g_debug_cnt);
	if (0 == g_debug_cnt)
	{
		/* wake up bt dbg wait queue */
		wake_up_interruptible(&ps_core_d->rx_dbg_wait);
		atomic_set(&ps_core_d->dbg_func_has_open, 0);

		/* kfree have rx dbg skb */
		ps_kfree_skb(ps_core_d, RX_DBG_QUEUE);
	}

    return 0;
}

/**********************************************************************/

/**********************************************************************/
int8 *uart_test_tx_buffer = NULL;
STATIC int g_uartopen_test_count = 0;
STATIC int g_pack_count = 100000;
STATIC int32 hw_uarttest_open(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d;
    int32 ret;

    PS_PRINT_INFO("%s", __func__);
    ps_core_d = NULL;
    ps_get_core_reference(&ps_core_d);

    uart_test_tx_buffer = kzalloc(5000, GFP_ATOMIC);
    if (NULL == uart_test_tx_buffer)
    {
        PS_PRINT_ERR("malloc tx_buffer fail\n");
        return -1;
    }

    if (unlikely((NULL == ps_core_d)||(NULL == inode)||
        (NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    ps_core_d->ps_pm->bfg_mutex_lock(1);

	g_uartopen_test_count++;

    ret = open_tty_drv(ps_core_d->pm_data);
    if (ret != 0)
    {
        PS_PRINT_ERR("open tty is err! ret = %d\n",ret);
        ps_core_d->ps_pm->bfg_mutex_lock(0);
        return -EINVAL;
    }

    ps_core_d->ps_pm->bfg_mutex_lock(0);

    return 0;
}
STATIC ssize_t hw_uarttest_read(struct file *filp, int8 __user *buf, size_t count,loff_t *f_pos)
{
    struct ps_core_s *ps_core_d = NULL;
    struct sk_buff *skb = NULL;
	uint64 timeout;
    uint16 count1;

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == buf)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

	if (ps_core_d->rx_dbg_seq.qlen == 0)
	{
		PS_PRINT_INFO("rx_debug quenen is %d\n", ps_core_d->rx_dbg_seq.qlen);

        timeout = wait_event_interruptible_timeout(ps_core_d->rx_dbg_wait,
            (ps_core_d->rx_dbg_seq.qlen > 0), msecs_to_jiffies(500));
        if (!timeout)
        {
            PS_PRINT_DBG("uart test read time out!\n");
            return -ETIMEDOUT;
        }
	}

	if (NULL == (skb = ps_skb_dequeue(ps_core_d, RX_DBG_QUEUE)))
    {
        PS_PRINT_ERR("dbg read err!\n");
        return -ETIMEDOUT;
    }

    count1 = min_t(size_t, skb->len, count);
    if (copy_to_user(buf, skb->data, count1))
    {
        PS_PRINT_ERR("copy_to_user is err!\n");
        ps_restore_skbqueue(ps_core_d, skb, RX_DBG_QUEUE);
        return -EFAULT;
    }

    skb_pull(skb, count1);

    if (0 == skb->len)
    {
        kfree_skb(skb);
    }
    else
    {
        ps_restore_skbqueue(ps_core_d, skb, RX_DBG_QUEUE);
    }
    if (ps_core_d->rx_dbg_seq.qlen < (RX_DBG_QUE_MAX_NUM/2) && (atomic_read(&ps_core_d->throttle_flag)))
    {
        tty_unthrottle(ps_core_d->tty);
        atomic_set(&ps_core_d->throttle_flag, 0);
    }

    return count1;
}

int32 uart_test_tx(uint8 *data, int32 len)
{
    int32 ret;
    int32 tx_len = 0;
    struct ps_core_s *ps_core_d = NULL;

    ps_get_core_reference(&ps_core_d);

    if(NULL == data)
    {
        PS_PRINT_ERR("data pointer is null\n");
        return -1;
    }

    if (0 > len)
    {
        PS_PRINT_ERR("data len is error %d\n", len);
        return 0;
    }

    while(tx_len < len)
    {
        ret = ps_write_tty(ps_core_d, data + tx_len, len - tx_len);
        if (ret < 0)
        {
            PS_PRINT_ERR("tty has not opened!\n");
            return -1;
        }
        tx_len = tx_len + ret;
    }

    return tx_len;
}

STATIC ssize_t hw_uarttest_write(struct file *filp, const int8 __user *buf, size_t count, loff_t *f_pos)
{
    uint8  cmd = 0;
    unsigned long long tx_total_len = 0, total_time;
    unsigned long long speed;
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = -1;
    uint8 tx_16data[16]   = {0};
    uint8 tx_32data[32]   = {0};
    uint8 tx_64data[64]   = {0};
    uint8 tx_128data[128] = {0};
    ktime_t start_time, end_time, trans_time;
    int32 i;

    memset(tx_16data,  1, 16);
    memset(tx_32data,  2, 32);
    memset(tx_64data,  3, 64);
    memset(tx_128data, 4, 128);

    if (NULL == buf || 0 == count)
    {
        PS_PRINT_ERR("para is invalided\n");
    }

    PS_PRINT_INFO("%s\n", __func__);

    if (copy_from_user(&cmd, buf, sizeof(cmd)))
    {
        PS_PRINT_ERR("copy_from_user from fm is err");
        return -EFAULT;
    }

    PS_PRINT_INFO("cmd:0x%x", cmd);

    ps_get_core_reference(&ps_core_d);

    ps_core_d->ps_pm->bfg_mutex_lock(1);
    start_time = ktime_get();
    switch (cmd)
    {
        case '1':
            PS_PRINT_INFO("tx %d package, len 16\n", g_pack_count);

            for(i = 0; i < g_pack_count; i++)
            {
                ret = uart_test_tx(tx_16data, 16);
                if (16 != ret)
                {
                    PS_PRINT_ERR("send data error ret=%d, i=%d\n", ret, i);
                    ps_core_d->ps_pm->bfg_mutex_lock(0);
                    return count;
                }
            }
            tx_total_len = g_pack_count*16;
            break;
        case '2':
            PS_PRINT_INFO("tx %d package, len 32\n", g_pack_count);

            for(i = 0; i < g_pack_count; i++)
            {
                ret = uart_test_tx(tx_32data, 32);
                if (32 != ret)
                {
                    PS_PRINT_ERR("send data error ret=%d, i=%d\n", ret, i);
                    ps_core_d->ps_pm->bfg_mutex_lock(0);
                    return count;
                }
            }
            tx_total_len = g_pack_count*32;
            break;
        case '3':
            PS_PRINT_INFO("tx %d package, len 64\n", g_pack_count);

            for(i = 0; i < g_pack_count; i++)
            {
                ret = uart_test_tx(tx_64data, 64);
                if (64 != ret)
                {
                   PS_PRINT_ERR("send data error ret=%d, i=%d\n", ret, i);
                    ps_core_d->ps_pm->bfg_mutex_lock(0);
                    return count;
                }
            }
            tx_total_len = g_pack_count*64;
            break;
        case '4':
            PS_PRINT_INFO("tx %d package, len 128\n", g_pack_count);

            for(i = 0; i < g_pack_count; i++)
            {
                ret = uart_test_tx(tx_128data, 128);
                if (128 != ret)
                {
                    PS_PRINT_ERR("send data error ret=%d, i=%d\n", ret, i);
                    ps_core_d->ps_pm->bfg_mutex_lock(0);
                    return count;
                }
            }
            tx_total_len = g_pack_count*128;
            break;
        default:
            break;
    }
    end_time = ktime_get();
    ps_core_d->ps_pm->bfg_mutex_lock(0);

    trans_time = ktime_sub(end_time, start_time);
    total_time = (unsigned long long)ktime_to_us(trans_time);
    speed = tx_total_len*1000000*10;
    do_div(speed, total_time);

    PS_PRINT_INFO("[UART]SEND Test                %d pkts sent\n", g_pack_count);
    PS_PRINT_INFO("[UART]SEND Test                %d pkts rcvd\n", 0);
    PS_PRINT_INFO("[UART]SEND Test data lengh     %llu\n", tx_total_len);
    PS_PRINT_INFO("[UART]SEND Test USED TIME      %llu us\n", total_time);
    PS_PRINT_INFO("[UART]SEND Test speed          %llu bps\n", speed);
    speed = speed;
    do_div(speed, 30000);
    PS_PRINT_INFO("[UART]SEND Test effect         %llu%% bps\n", speed);

    return count;
}


STATIC int32 hw_uarttest_release(struct inode *inode, struct file *filp)
{
    struct ps_core_s *ps_core_d = NULL;
    int32 ret = 0;

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely((NULL == ps_core_d)||(NULL == inode)||(NULL == filp)))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    ps_core_d->ps_pm->bfg_mutex_lock(1);

	g_uartopen_test_count--;

	if (g_uartopen_test_count == 0)
	{
	    ret = release_tty_drv(ps_core_d->pm_data);
	    if (ret != 0)
	    {
	        PS_PRINT_ERR("close tty is err! ret = %d\n",ret);
	        ps_core_d->ps_pm->bfg_mutex_lock(0);
	        return -EINVAL;
	    }
	}


    ps_core_d->ps_pm->bfg_mutex_lock(0);

	if (NULL != uart_test_tx_buffer)
	{
    	kfree(uart_test_tx_buffer);
	}

    return 0;
}

/**********************************************************************/
STATIC const struct file_operations hw_bt_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_bt_open,
        .write          = hw_bt_write,
        .read           = hw_bt_read,
        .poll           = hw_bt_poll,
        .unlocked_ioctl = hw_bt_ioctl,
        .release        = hw_bt_release,
};

STATIC const struct file_operations hw_fm_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_fm_open,
        .write          = hw_fm_write,
        .read           = hw_fm_read,
        .unlocked_ioctl = hw_fm_ioctl,
        .release        = hw_fm_release,
};

STATIC const struct file_operations hw_gnss_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_gnss_open,
        .write          = hw_gnss_write,
        .read           = hw_gnss_read,
        .unlocked_ioctl = hw_gnss_ioctl,
        .release        = hw_gnss_release,
};

STATIC const struct file_operations hw_debug_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_debug_open,
        .write          = hw_debug_write,
        .read           = hw_debug_read,
        .release        = hw_debug_release,
};

static const struct file_operations hw_nfc_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_nfc_open,
        .write          = hw_nfc_write,
        .read           = hw_nfc_read,
        .poll           = hw_nfc_poll,
        .release        = hw_nfc_release,
};

static const struct file_operations hw_ir_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_ir_open,
        .write          = hw_ir_write,
        .read           = hw_ir_read,
        .release        = hw_ir_release,
};

STATIC const struct file_operations hw_uarttest_fops = {
        .owner          = THIS_MODULE,
        .open           = hw_uarttest_open,
        .write          = hw_uarttest_write,
        .read           = hw_uarttest_read,
        .release        = hw_uarttest_release,
};

STATIC struct miscdevice hw_bt_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwbt",
        .fops   = &hw_bt_fops,
};

STATIC struct miscdevice hw_nfc_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwnfc",
        .fops   = &hw_nfc_fops,
};

STATIC struct miscdevice hw_ir_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwir",
        .fops   = &hw_ir_fops,
};

STATIC struct miscdevice hw_fm_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwfm",
        .fops   = &hw_fm_fops,
};

STATIC struct miscdevice hw_gnss_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwgnss",
        .fops   = &hw_gnss_fops,
};

STATIC struct miscdevice hw_debug_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "hwbfgdbg",
        .fops   = &hw_debug_fops,
};

STATIC struct miscdevice hw_uarttest_device = {
        .minor  = MISC_DYNAMIC_MINOR,
        .name   = "uarttest",
        .fops   = &hw_uarttest_fops,
};

static struct  hw_ps_plat_data   hisi_platform_data = {
    .dev_name           = "/dev/ttyAMA3",
    .flow_cntrl         = FLOW_CTRL_DISABLE,
    .baud_rate          = DEFAULT_BAUD_RATE,
    .suspend            = NULL,
    .resume             = NULL,
    .set_bt_power       = NULL,
    .set_fm_power       = NULL,
    .set_gnss_power     = NULL,
    .clear_bt_power     = NULL,
    .clear_fm_power     = NULL,
    .clear_gnss_power   = NULL,
};

STATIC int32 ps_probe(struct platform_device *pdev)
{
    struct hw_ps_plat_data *pdata = NULL;
    struct ps_plat_s *ps_plat_d;
    int32  err;
	struct device_node *np;
	const char * pdev_name;

    PS_PRINT_FUNCTION_NAME;

	np = of_find_compatible_node(NULL, NULL,DTS_COMP_HI1101_PS_NAME);	// should be the same as dts node compatible property
	if (NULL == np)
	{
		PS_PRINT_ERR("Unable to find %s\n",DTS_COMP_HI1101_PS_NAME);
		return -ENOENT;
	}

	if (of_property_read_string(np, "hi1102,uart_port", &pdev_name))
	{
		PS_PRINT_ERR("%s node doesn't have uart-dev property!\n", np->name);
		return -ENOENT;
	}

	strncpy(hisi_platform_data.dev_name, pdev_name, strlen(pdev_name));
	PS_PRINT_INFO("%s node have uart-dev property = %s \n", np->name, hisi_platform_data.dev_name);

	pdev->dev.platform_data = &hisi_platform_data;
	pdata = &hisi_platform_data;

    hw_ps_device = pdev;

    ps_plat_d = kzalloc(sizeof(struct ps_plat_s), GFP_ATOMIC);
    if (NULL == ps_plat_d)
    {
        PS_PRINT_ERR("no mem to allocate\n");
        return -ENOMEM;
    }
    dev_set_drvdata(&pdev->dev, ps_plat_d);

    err = ps_core_init(&ps_plat_d->core_data);
    if (0 != err)
    {
        PS_PRINT_ERR(" PS core init failed\n");
        goto err_core_init;
    }

    /* refer to itself */
    ps_plat_d->core_data->pm_data = ps_plat_d;
    /* get reference of pdev */
    ps_plat_d->pm_pdev = pdev;

    init_completion(&ps_plat_d->ldisc_installed);
    init_completion(&ps_plat_d->change_baud_rate);

    err = plat_bfgx_exception_rst_register(ps_plat_d);
    if (0 > err)
    {
        PS_PRINT_ERR("bfgx_exception_rst_register failed\n");
        goto err_exception_rst_reg;
    }

    err = bfgx_user_ctrl_init();
    if (0 > err)
    {
        PS_PRINT_ERR("bfgx_user_ctrl_init failed\n");
        goto err_user_ctrl_init;
    }

    /* copying platform data */
    strncpy(ps_plat_d->dev_name, pdata->dev_name, HISI_UART_DEV_NAME_LEN);
    ps_plat_d->flow_cntrl = pdata->flow_cntrl;
    ps_plat_d->baud_rate  = pdata->baud_rate;
    PS_PRINT_INFO("sysfs entries created\n");
//#if 0
#ifndef UART_LOOP_TEST
    tty_recv = ps_core_recv;
#else
    tty_recv = ps_core_recv_uart_test;
#endif

    err = misc_register(&hw_uarttest_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register uarttest inode\n ");
        goto err_register_uarttest;
    }

    err = misc_register(&hw_bt_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register bt inode\n ");
        goto err_register_bt;
    }

    err = misc_register(&hw_fm_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register fm inode\n ");
        goto err_register_fm;
    }

    err = misc_register(&hw_gnss_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register gnss inode\n ");
        goto err_register_gnss;
    }

    err = misc_register(&hw_debug_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register debug inode\n");
        goto err_register_debug;
    }

    err = misc_register(&hw_nfc_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register nfc inode\n ");
        goto err_register_nfc;
    }

    err = misc_register(&hw_ir_device);
    if (0 != err)
    {
        PS_PRINT_ERR("Failed to register ir inode\n");
        goto err_register_ir;
    }

    PS_PRINT_SUC("%s is success!\n", __func__);

    return 0;

    err_register_ir:
        misc_deregister(&hw_nfc_device);
    err_register_nfc:
        misc_deregister(&hw_debug_device);
    err_register_debug:
        misc_deregister(&hw_gnss_device);
    err_register_gnss:
        misc_deregister(&hw_fm_device);
    err_register_fm:
        misc_deregister(&hw_bt_device);
    err_register_bt:
        misc_deregister(&hw_uarttest_device);
    err_register_uarttest:
        bfgx_user_ctrl_exit();
    err_user_ctrl_init:
    err_exception_rst_reg:
        ps_core_exit(ps_plat_d->core_data);
    err_core_init:
    	kfree(ps_plat_d);

        return -EFAULT;
}

/**
 * Prototype    : ps_suspend
 * Description  : called by kernel when kernel goto suspend
 * input        : pdev, state
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_suspend(struct platform_device *pdev, pm_message_t state)
{
#if 0
    struct hw_ps_plat_data  *pdata = pdev->dev.platform_data;
    if (pdata->suspend)
    {
        return pdata->suspend(pdev, state);
    }

    return -EOPNOTSUPP;
#else
    return 0;
#endif
}

/**
 * Prototype    : ps_resume
 * Description  : called by kernel when kernel resume from suspend
 * input        : pdev
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 ps_resume(struct platform_device *pdev)
{
#if 0
    struct hw_ps_plat_data  *pdata = pdev->dev.platform_data;
    if (pdata->resume)
    {
        return pdata->resume(pdev);
    }

    return -EOPNOTSUPP;
#else
    return 0;
#endif
}
/**
 * Prototype    : ps_remove
 * Description  : called when user applation rmmod driver
 * input        : pdev
 * output       : return 0 --> ps_suspend is ok
 *                return !0--> ps_suspend is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
STATIC int32 ps_remove(struct platform_device *pdev)
{
    struct ps_plat_s *ps_plat_d;
    struct hw_ps_plat_data *pdata;

    PS_PRINT_FUNCTION_NAME;

    pdata = pdev->dev.platform_data;
    ps_plat_d = dev_get_drvdata(&pdev->dev);

    bfgx_user_ctrl_exit();
    PS_PRINT_INFO("sysfs entries removed");

    ps_plat_d->pm_pdev = NULL;
    ps_core_exit(ps_plat_d->core_data);

    misc_deregister(&hw_bt_device);
    misc_deregister(&hw_fm_device);
    PS_PRINT_INFO("misc fm device have removed");
    misc_deregister(&hw_gnss_device);
    PS_PRINT_INFO("misc gnss device have removed");
    misc_deregister(&hw_debug_device);
    PS_PRINT_INFO("misc debug device have removed");
    misc_deregister(&hw_nfc_device);
    PS_PRINT_INFO("misc nfc have removed");
    misc_deregister(&hw_ir_device);
    PS_PRINT_INFO("misc ir have removed");
    misc_deregister(&hw_uarttest_device);
    PS_PRINT_INFO("misc uarttest have removed");

    kfree(ps_plat_d);
    ps_plat_d = NULL;
    return 0;
}
#ifdef _PRE_CONFIG_USE_DTS
static struct of_device_id hi1101_ps_match_table[] = {
	{
		.compatible = DTS_COMP_HI1101_PS_NAME,
		.data = NULL,
    },
	{ },
};
#endif

/**********************************************************/
/*  platform_driver struct for PS module */
STATIC struct platform_driver ps_platform_driver = {
        .probe      = ps_probe,
        .remove     = ps_remove,
        .suspend    = ps_suspend,
        .resume     = ps_resume,
        .driver     = {
            .name   = "hisi_bfgx",
            .owner  = THIS_MODULE,
#ifdef _PRE_CONFIG_USE_DTS
			.of_match_table	= hi1101_ps_match_table,
#endif
        },
};

int32 hw_ps_init(void)
{
    int32 ret;

    PS_PRINT_FUNCTION_NAME;

    ret = platform_driver_register(&ps_platform_driver);
    if (ret)
    {
        PS_PRINT_ERR("Unable to register platform bfgx driver.\n");
    }
    return ret;
}

void hw_ps_exit(void)
{
    platform_driver_unregister(&ps_platform_driver);
}

MODULE_DESCRIPTION("Public serial Driver for huawei BT/FM/GNSS chips");
MODULE_LICENSE("GPL");

