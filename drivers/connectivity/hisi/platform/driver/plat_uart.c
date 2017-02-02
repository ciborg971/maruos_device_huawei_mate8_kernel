

/*****************************************************************************
  1 Header File Including
*****************************************************************************/
/*lint -e322*//*lint -e7*/
#include <linux/tty.h>
#include <linux/delay.h>
#include "plat_debug.h"
#include "hw_bfg_ps.h"
#include "bfgx_user_ctrl.h"
/*lint +e322*//*lint +e7*/

/*****************************************************************************
  2 Global Variable Definition
*****************************************************************************/

/*****************************************************************************
  3 Function Definition
*****************************************************************************/

/**
 * Prototype    : ps_tty_complete
 * Description  : to signal completion of line discipline installation
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
int32 ps_tty_complete(void *pm_data)
{
    struct ps_plat_s *ps_plat_d = (struct ps_plat_s *)pm_data;

    PS_PRINT_FUNCTION_NAME;
    complete(&ps_plat_d->ldisc_installed);
    return 0;
}

/********************************************************************/
/**
 * Prototype    : ps_tty_open
 * Description  : called by tty uart itself when open tty uart from octty
 * input        : tty -> have opened tty
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
STATIC int32 ps_tty_open(struct tty_struct *tty)
{
    int32 err = 0;
    struct ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    ps_core_d->tty = tty;
    tty->disc_data = ps_core_d;

    /* don't do an wakeup for now */
    clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

    /* set mem already allocated */
    tty->receive_room = 65536;
    /* Flush any pending characters in the driver and discipline. */
    tty_ldisc_flush(tty);
    tty_driver_flush_buffer(tty);
    /* signal to octty that installation of N_HW_BFG ldisc is complete   */
    ps_tty_complete(ps_core_d->pm_data);
    ps_change_baud_rate_complete(ps_core_d->pm_data);
    PS_PRINT_INFO("%s have done !!!\n", __func__);

    return err;
}

/**
 * Prototype    : ps_tty_close
 * Description  : called by tty uart when close tty uart from octty
 * input        : tty -> have opened tty
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
STATIC void ps_tty_close(struct tty_struct *tty)
{
    struct  ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;
    PS_PRINT_INFO("%s: entered!!!\n", __func__);

    if ((NULL == tty)||(NULL == tty->disc_data))
    {
        PS_PRINT_ERR("tty or tty->disc_data is NULL\n");
        return;
    }
    ps_core_d = tty->disc_data;

    /* Flush any pending characters in the driver and discipline. */
    tty_ldisc_flush(tty);
    tty_driver_flush_buffer(tty);
    ps_core_d->tty = NULL;

    /* signal to complate that N_HW_BFG ldisc is un-installed */
    ps_tty_complete(ps_core_d->pm_data);

    ps_kfree_skb(ps_core_d, TX_HIGH_QUEUE);
    ps_kfree_skb(ps_core_d, TX_LOW_QUEUE);

    PS_PRINT_INFO("%s: have done!!!\n", __func__);
}

/**
 * Prototype    : ps_tty_receive
 * Description  : called by tty uart when recive data from tty uart
 * input        : tty   -> have opened tty
 *                data -> recive data ptr
 *                count-> recive data count
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
STATIC void ps_tty_receive(struct tty_struct *tty, const uint8 *data,
               int8 *tty_flags, int32 count)
{
    struct  ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;

    if (unlikely((NULL == tty)||(NULL == tty->disc_data)||(NULL == tty_recv)))
    {
        PS_PRINT_ERR("tty or tty->disc_data or tty_recv is NULL\n");
        return;
    }
    ps_core_d = tty->disc_data;
    spin_lock(&ps_core_d->rx_lock);
#ifdef FEATURE_PM_DOWNLOAD_PATCH
	PS_PRINT_DBG("RX:data[0] = %x, data[1] = %x, data[2] = %x, data[3] = %x, data[4] = %x, data[count-1] = %x\n",
			  data[0],data[1],data[2],data[3],data[4],data[count-1]);

    tty_recv(tty->disc_data, data, count);
#else
    ps_core_recv(tty->disc_data, data, count);
#endif
    spin_unlock(&ps_core_d->rx_lock);
}

/**
 * Prototype    : ps_tty_wakeup
 * Description  : called by tty uart when wakeup from suspend
 * input        : tty   -> have opened tty
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
STATIC void ps_tty_wakeup(struct tty_struct *tty)
{
    struct  ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;
    if ((NULL == tty)||(NULL == tty->disc_data))
    {
        PS_PRINT_ERR("tty or tty->disc_data is NULL\n");
        return;
    }
    ps_core_d = tty->disc_data;
    /* don't do an wakeup for now */
    clear_bit(TTY_DO_WRITE_WAKEUP, &tty->flags);

    /* call our internal wakeup */
    queue_work(ps_core_d->ps_tx_workqueue, &ps_core_d->tx_skb_work);
}

/**
 * Prototype    : ps_tty_flush_buffer
 * Description  : called by tty uart when flush buffer
 * input        : tty   -> have opened tty
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
STATIC void ps_tty_flush_buffer(struct tty_struct *tty)
{
    PS_PRINT_INFO("time to %s\n", __func__);
    reset_uart_rx_buf();

/*
    struct tty_buffer *thead;
    struct tty_bufhead *buf = &(tty->port->buf);

    PS_PRINT_INFO("time to %s\n", __func__);

    while ((thead = buf->head->next) != NULL)
    {
    if (buf->head->size)
    {
    PS_PRINT_INFO("tty buf is not free\n");
    }
    buf->head = thead;
}
*/
#if 0
    struct  ps_core_s *ps_core_d = NULL;

    PS_PRINT_FUNCTION_NAME;
    if ((NULL == tty)||(NULL == tty->disc_data))
    {
        PS_PRINT_ERR("tty or tty->disc_data is NULL");
        return;
    }
    ps_core_d = tty->disc_data;
    tty->ops->flush_buffer(tty);
#endif

    return;
}

/**
 * Prototype    : ps_change_uart_baud_rate
 * Description  : change arm platform uart baud rate to secend
 *                baud rate for high baud rate when download patch
 * input        : ps_core_d
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
int32 ps_change_uart_baud_rate(int64 baud_rate, uint8 enable_flowctl)
{
    struct ps_plat_s *ps_plat_d = NULL;
    uint64 timeleft = 0;

    PS_PRINT_INFO("%s\n", __func__);

    ps_get_plat_reference(&ps_plat_d);
    if (unlikely(NULL == ps_plat_d))
    {
        PS_PRINT_ERR("ps_plat_d is NULL\n");
        return -EINVAL;
    }

    INIT_COMPLETION(ps_plat_d->change_baud_rate);
    /* set changed baud rate */
    ps_plat_d->flow_cntrl = enable_flowctl;  /* enable flow_cntrl */
    ps_plat_d->baud_rate = baud_rate;
    ps_plat_d->ldisc_install = 1;   /* open uart */
    /* notify to octty; octty change baud rate */
    sysfs_notify(g_sysfs_hi110x_bfgx, NULL, "install");
    /* wait change baud rate is over */
    timeleft = wait_for_completion_timeout(&ps_plat_d->change_baud_rate,
            msecs_to_jiffies(HISI_LDISC_TIME));
    if (!timeleft)
    {
        PS_PRINT_ERR("change baud_rate timeout\n");
        return -EINVAL;
    }
    else
    {
        /* ldisc installed now */
        PS_PRINT_SUC("change baud_rate installed\n");
        return 0;
    }
}

/**
 * Prototype    : open_tty_drv
 * Description  : called from PS Core when BT protocol stack drivers
 *                  registration,or FM/GNSS hal stack open FM/GNSS inode
 * input        : ps_plat_d
 * output       : return 0--> open tty uart is ok
 *                return !0-> open tty uart is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 open_tty_drv(void *pm_data)
{
    struct ps_plat_s *ps_plat_d = NULL;
    struct ps_core_s *ps_core_d;
#if 0
    struct clk *uart_clock;
    struct clk *uart_pclock;
    int32 ret = 0;
#endif
    uint8 retry = OPEN_TTY_RETRY_COUNT;
    uint64 timeleft = 0;

    PS_PRINT_DBG("%s\n", __func__);
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("pm_data is NULL");
        return -EINVAL;
    }
    ps_plat_d = (struct ps_plat_s *)pm_data;
    ps_core_d = ps_plat_d->core_data;
    if (true == ps_core_d->tty_have_open)
    {
        PS_PRINT_DBG("line discipline have installed");
        return 0;
    }

    reset_uart_rx_buf();


#if 0
    uart_clock = k3v2_get_clock_by_name(CLK_UART4);
    if (!uart_clock)
    {
        PS_PRINT_ERR("Unable to initialize clock");
        return -EINVAL;
    }

    uart_pclock = k3v2_get_clock_by_name(CLKIN_SYS);
    if (!uart_pclock)
    {
        PS_PRINT_ERR("Unable to find parent clock");
        return -EINVAL;
    }

    ret = clk_set_parent(uart_clock, uart_pclock);
    if(ret)
    {
        PS_PRINT_ERR("Unable to set parent of clock");
        return -EINVAL;
    }
#endif

    do {
        /* re-initialize the completion */
        INIT_COMPLETION(ps_plat_d->ldisc_installed);
        /* send notification to octty */
        ps_plat_d->ldisc_install = 1;
        PS_PRINT_INFO("ldisc_install = 1\n");
        /* notify a info to octty */
        sysfs_notify(g_sysfs_hi110x_bfgx, NULL, "install");
        /* wait for ldisc to be installed */
        timeleft = wait_for_completion_timeout(&ps_plat_d->ldisc_installed,
                msecs_to_jiffies(HISI_LDISC_TIME));
        if (!timeleft)
        {
            /* ldisc installation timeout */
            PS_PRINT_ERR("ldisc installation timeout");
            continue;
        }
        else
        {
            /* ldisc installed now */
            PS_PRINT_SUC("line discipline installed");
            ps_core_d->tty_have_open = true;
            return 0;
        }
    } while (retry--);
    return -EPERM;
}

/**
 * Prototype    : release_tty_drv
 * Description  : called from PS Core when BT protocol stack drivers
 *                  unregistration,or FM/GNSS hal stack close FM/GNSS inode
 * input        : ps_plat_d
 * output       : return 0--> open tty uart is ok
 *                return !0-> open tty uart is false
 * Calls        :
 * Called By    :
 *
 *   History        :
 *   1.Date         : 2012/11/05
 *     Author       : wx144390
 *     Modification : Created function
 *
 */
int32 release_tty_drv(void *pm_data)
{
    struct ps_plat_s *ps_plat_d = NULL;
    struct tty_struct *tty = NULL;
    struct ps_core_s *ps_core_d;
    uint64 timeleft = 0;
    uint8 delay_times = RELEASE_DELAT_TIMES;

    PS_PRINT_INFO("%s", __func__);
    if (unlikely(NULL == pm_data))
    {
        PS_PRINT_ERR("pm_data is NULL");
        return -EINVAL;
    }

    ps_plat_d = (struct ps_plat_s *)pm_data;
    ps_core_d = ps_plat_d->core_data;
    tty = ps_core_d->tty;

    if (false == ps_core_d->tty_have_open)
    {
        PS_PRINT_INFO("line discipline have uninstalled");
        return 0;
    }
    /* clean all tx sk_buff */
    while(((ps_core_d->tx_high_seq.qlen)||(ps_core_d->tx_low_seq.qlen))&&(delay_times))
    {
        msleep(100);
        delay_times --;
    }
    msleep(200);

    INIT_COMPLETION(ps_plat_d->ldisc_installed);

    if (tty)
    {   /* can be called before ldisc is installed */
        /* Flush any pending characters in the driver and discipline. */
        PS_PRINT_INFO(" %s--> into flush_buffer\n", __func__);
        tty_ldisc_flush(tty);
        tty_driver_flush_buffer(tty);
    }

    /* send uninstall notification to octty */
    PS_PRINT_INFO("ldisc_install = 0");
    ps_plat_d->ldisc_install = 0;
    /* notify info to octty,and close uart */
    sysfs_notify(g_sysfs_hi110x_bfgx, NULL, "install");

    /* wait for ldisc to be un-installed */
    timeleft = wait_for_completion_timeout(&ps_plat_d->ldisc_installed,
            msecs_to_jiffies(HISI_LDISC_TIME));
    if (!timeleft)
    {   /* timeout */
        PS_PRINT_ERR(" timed out waiting for ldisc to be un-installed");
        return -ETIMEDOUT;
    }

    ps_core_d->tty_have_open = false;
    ps_plat_d->flow_cntrl = FLOW_CTRL_DISABLE;
    /* baud rate change to default */
    ps_plat_d->baud_rate = DEFAULT_BAUD_RATE;

    return 0;
}

STATIC struct tty_ldisc_ops ps_ldisc_ops = {
    .magic          = TTY_LDISC_MAGIC,
    .name           = "n_ps",
    .open           = ps_tty_open,
    .close          = ps_tty_close,
    .receive_buf    = ps_tty_receive,
    .write_wakeup   = ps_tty_wakeup,
    .flush_buffer   = ps_tty_flush_buffer,
    .owner          = THIS_MODULE
};

int32 plat_uart_init(void)
{
    return tty_register_ldisc(N_HW_BFG, &ps_ldisc_ops);
}

int32 plat_uart_exit(void)
{
    return tty_unregister_ldisc(N_HW_BFG);
}
