

/*****************************************************************************
  1 Include Head file
*****************************************************************************/
#include <linux/platform_device.h>
#include <linux/gpio.h>
#include "plat_debug.h"
#include "bfgx_low_power.h"
#include "plat_pm.h"
#include "bfgx_exception_rst.h"
#include "oneimage.h"
#include "oal_kernel_file.h"
#include "oal_sdio_host_if.h"
#include "plat_pm_wlan.h"

/*****************************************************************************
  2 Define global variable
*****************************************************************************/
struct kobject *g_sysfs_hi110x_bfgx    = NULL;
struct kobject *g_sysfs_bfgx_exception = NULL;
struct kobject *g_sysfs_hisi_nfc = NULL;
struct kobject *g_sysfs_hisi_pmdbg = NULL;
int32 g_plat_loglevel = PLAT_LOG_INFO;

extern int isAsic(void);

/*****************************************************************************
  3 Function implement
*****************************************************************************/

STATIC ssize_t show_wifi_pmdbg(struct device *dev, struct device_attribute *attr, int8 *buf)
{
   struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();

   return sprintf(buf, "wifi_pm_debug usage: 1:open 2:close 3:enable 4:disable 5:wakelock 6:wakeunlock 7:dump info 8:disable pm 9:enable pm; other:set timeout\n"
                       "power:%ld,enable:%ld,dev state:%ld,wakelock_cnt=%d,wdg_timeout=%d\n",
                       pst_wlan_pm->ul_wlan_power_state,
                       pst_wlan_pm->ul_wlan_pm_enable,
                       pst_wlan_pm->ul_wlan_dev_state,
                       pst_wlan_pm->pst_sdio->ul_wklock_cnt,
                       pst_wlan_pm->ul_wdg_timeout);
}

STATIC ssize_t store_wifi_pmdbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    struct wlan_pm_s *pst_wlan_pm = wlan_pm_get_drv();
    int input = oal_atoi(buf);

    if (NULL == pst_wlan_pm)
    {
        OAL_IO_PRINT("pm_data is NULL!\n");
        return -FAILURE;
    }

    switch(input)
    {
       case 1:
        wlan_pm_open();
       break;
       case 2:
        wlan_pm_close();
       break;
       case 3:
        wlan_pm_enable();
       break;
       case 4:
        wlan_pm_disable();
       break;
       case 5:
        wlan_pm_debug_wake_lock();
       break;
       case 6:
        wlan_pm_debug_wake_unlock();
       break;
       case 7:
        wlan_pm_dump_info();
       break;
       case 8:
        g_wlan_pm_switch = 0;
       break;
       case 9:
        g_wlan_pm_switch = 1;
       break;
       case 10:
        wlan_pm_debug_wakeup();
       break;
       case 11:
        wlan_pm_debug_sleep();
        break;
       default:
       if((input >= 50) && (input < 5000))
        {
            wlan_pm_set_timeout(input);
        }
        break;
    }

    return count;
}

STATIC ssize_t show_bfgx_pmdbg(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n"
                        "  1  plat pm enable\n  2  plat pm disable\n"
                        "  3   bt  pm enable\n  4   bt  pm disable\n"
                        "  5  gnss pm enable\n  6  gnss pm disable\n"
                        "  7   nfc pm enable\n  8   nfc pm disable\n"
                        "  9  shutdown bcpu \n  0  reset bcpu     \n");
}

extern int32 execute_download_cmd(int32 cmd_type, uint8 *cmd_name, uint8 *cmd_para);
STATIC ssize_t store_bfgx_pmdbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    struct ps_core_s *ps_core_d = NULL;
    struct pm_drv_data *pm_data = NULL;
    int32  cmd = 0;
    int32  ret = 0;

    cmd = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("cmd:%d", cmd);

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL!\n");
        return -FAILURE;
    }

    pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }

    switch (cmd)
    {
        case 1: /* disable plat lowpower function */
            pm_data->bfgx_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 2: /* enable plat lowpower function */
            pm_data->bfgx_lowpower_enable = BFGX_PM_DISABLE;
            break;
        case 3: /* enable bt lowpower function */
            pm_data->bfgx_bt_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 4: /* disable bt lowpower function */
            pm_data->bfgx_bt_lowpower_enable = BFGX_PM_DISABLE;
            break;
        case 5: /* enable gnss lowpower function */
            pm_data->bfgx_gnss_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 6: /* disable gnss lowpower function */
            pm_data->bfgx_gnss_lowpower_enable = BFGX_PM_DISABLE;
            break;
        case 7: /* enable nfc lowpower function */
            pm_data->bfgx_nfc_lowpower_enable = BFGX_PM_ENABLE;
            break;
        case 8: /* disable nfc lowpower function */
            pm_data->bfgx_nfc_lowpower_enable = BFGX_PM_DISABLE;
            break;
        /* case 9 & case 0: shutdown bcpu & reboot bcpu */
        case 9:
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_SHUTDOWN_SLP);
            break;
        case 0:
            execute_download_cmd(2, "WRITEM", "2,0x50000094,1");
            break;
        default:
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

STATIC struct kobj_attribute wifi_pmdbg =
__ATTR(wifi_pm, 0644, (void *)show_wifi_pmdbg, (void *)store_wifi_pmdbg);

STATIC struct kobj_attribute bfgx_pmdbg =
__ATTR(bfgx_pm, 0644, (void *)show_bfgx_pmdbg, (void *)store_bfgx_pmdbg);

STATIC struct attribute *pmdbg_attrs[] = {
        &wifi_pmdbg.attr,
        &bfgx_pmdbg.attr,
        NULL,
};

STATIC struct attribute_group pmdbg_attr_grp = {
    .attrs = pmdbg_attrs,
};

/* functions called from subsystems */
/* called by octty from hal to decide open or close uart */
STATIC ssize_t show_install(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);

    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%d\n", pm_data->ldisc_install);
}

/* read by octty from hal to decide open which uart */
STATIC ssize_t show_dev_name(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);

    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%s\n", pm_data->dev_name);
}

/* read by octty from hal to decide what baud rate to use */
STATIC ssize_t show_baud_rate(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);

    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%ld\n", pm_data->baud_rate);
}

/* read by octty from hal to decide whether or not use flow cntrl */
STATIC ssize_t show_flow_cntrl(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);

    PS_PRINT_FUNCTION_NAME;
    return sprintf(buf, "%d\n", pm_data->flow_cntrl);
}

STATIC ssize_t gnss_lowpower_state_store(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int flag = 0;

    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -EFAULT;
    }
    PS_PRINT_DBG("gnss_lowpower_state_store!\n");

    flag = simple_strtol(buf, NULL, 10);
    /*gnss write the flag to request sleep*/
    if (1 == flag)
    {
        if (BFGX_PM_DISABLE == pm_data->bfgx_lowpower_enable)
        {
            PS_PRINT_DBG("gnss low power disabled!\n");
            return -EFAULT;
        }
        if (BFGX_SLEEP == pm_data->ps_pm_interface->bfgx_dev_state_get())
        {
            PS_PRINT_DBG("gnss proc: dev has been sleep, not allow dev slp\n");
            return -EFAULT;
        }
        /*if bt and fm are both shutdown ,we will pull down gpio directly*/
        PS_PRINT_DBG("flag = 1!\n");

        if (!timer_pending(&pm_data->bfg_timer))
        {
            PS_PRINT_SUC("gnss low power request sleep!\n");
            host_allow_bfg_sleep(pm_data->ps_pm_interface->ps_core_data);
        }

        /*set the flag to 1 means gnss request sleep*/
        atomic_set(&pm_data->gnss_sleep_flag, GNSS_AGREE_SLEEP);
    }
    else
    {
        PS_PRINT_DBG("invalid gnss lowpower data!\n");
        return -EFAULT;
    }

    return count;
}

/* show curr bfg proto yes or not opened state */
STATIC ssize_t show_bfg_active_state(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct ps_plat_s *pm_data = dev_get_drvdata(&hw_ps_device->dev);
    uint8 bt_state   = SUBSYS_STATE_SHUTDOWN;
    uint8 gnss_state = SUBSYS_STATE_SHUTDOWN;
    uint8 fm_state   = SUBSYS_STATE_SHUTDOWN;
    uint8 ir_state   = SUBSYS_STATE_SHUTDOWN;
    uint8 nfc_state  = SUBSYS_STATE_SHUTDOWN;

    PS_PRINT_INFO("%s", __func__);
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_BT].subsys_state))
    {
        bt_state = SUBSYS_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_GNSS].subsys_state))
    {
        gnss_state = SUBSYS_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_FM].subsys_state))
    {
        fm_state = SUBSYS_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_IR].subsys_state))
    {
        ir_state = SUBSYS_STATE_OPEN;
    }
    if (true == atomic_read(&pm_data->core_data->bfgx_info[BFGX_NFC].subsys_state))
    {
        nfc_state = SUBSYS_STATE_OPEN;
    }

    return sprintf(buf, "bt:%d; gnss:%d; fm:%d; ir:%d; nfc:%d;\n", bt_state, gnss_state, fm_state, ir_state, nfc_state);
}

STATIC ssize_t show_loglevel(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "curr loglevel=%d\nalert:0\nerr:1\nwarning:2\nfunc|succ|info:3\ndebug:4\n", g_plat_loglevel);
}

STATIC ssize_t store_loglevel(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 loglevel = PLAT_LOG_INFO;

    PS_PRINT_INFO("%s", __func__);

    loglevel = simple_strtol(buf, NULL, 10);
    if(PLAT_LOG_ALERT > loglevel)
    {
        g_plat_loglevel = PLAT_LOG_ALERT;
    }
    else if(PLAT_LOG_DEBUG < loglevel)
    {
        g_plat_loglevel = PLAT_LOG_DEBUG;
    }
    else
    {
        g_plat_loglevel = loglevel;
    }
    return count;
}

STATIC ssize_t show_ir_mode(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    if (!isAsic())
    {
        PS_PRINT_ERR("HI1102 FPGA VERSION, ir contral gpio not exist\n");
        return -FAILURE;
    }

    return sprintf(buf, "%d\n", gpio_get_value(pm_data->board->bfgn_ir_ctrl));
}

STATIC ssize_t store_ir_mode(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 gpio_level;
    struct pm_drv_data *pm_data = pm_get_drvdata();
    if (NULL == pm_data)
    {
        PS_PRINT_ERR("pm_data is NULL!\n");
        return -FAILURE;
    }

    PS_PRINT_INFO("%s", __func__);

    if (!isAsic())
    {
        PS_PRINT_ERR("HI1102 FPGA VERSION, ignore ir contral gpio\n");
        return count;
    }

    gpio_level = simple_strtol(buf, NULL, 10);
    if (GPIO_LOWLEVEL == gpio_level)
    {
        gpio_direction_output(pm_data->board->bfgn_ir_ctrl, GPIO_LOWLEVEL);
    }
    else if (GPIO_HIGHLEVEL == gpio_level)
    {
        gpio_direction_output(pm_data->board->bfgn_ir_ctrl, GPIO_HIGHLEVEL);
    }
    else
    {
        PS_PRINT_ERR("gpio level should be 0 or 1, cur value is [%d]\n", gpio_level);
    }

    return count;
}

STATIC ssize_t show_dev_test(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n  1  cause bfgx into panic\n  2  enable exception recovery\n");
}

STATIC ssize_t store_dev_test(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32 cmd;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_INFO("%s", __func__);

    ps_get_core_reference(&ps_core_d);
    if (unlikely(NULL == ps_core_d))
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return -EINVAL;
    }

    cmd = simple_strtol(buf, NULL, 10);
    switch (cmd)
    {
        case 1:
            PS_PRINT_INFO("bfgx test cmd %d, cause device panic\n", cmd);
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_DEV_PANIC);
            break;
        case 2:
            PS_PRINT_INFO("cmd %d,enable platform exception recovery\n", cmd);
            pst_exception_data->exception_reset_enable = true;
        default:
            break;
    }

    return count;
}

/* structures specific for sysfs entries */
STATIC struct kobj_attribute ldisc_install =
__ATTR(install, 0444, (void *)show_install, NULL);

STATIC struct kobj_attribute uart_dev_name =
__ATTR(dev_name, 0444, (void *)show_dev_name, NULL);

STATIC struct kobj_attribute uart_baud_rate =
__ATTR(baud_rate, 0444, (void *)show_baud_rate, NULL);

STATIC struct kobj_attribute uart_flow_cntrl =
__ATTR(flow_cntrl, 0444, (void *)show_flow_cntrl, NULL);

STATIC struct kobj_attribute gnss_lowpower_cntrl =
__ATTR(gnss_lowpower_state, 0644, NULL, (void *)gnss_lowpower_state_store);

STATIC struct kobj_attribute bfg_active_state =
__ATTR(bfg_state, 0444, (void *)show_bfg_active_state, NULL);

STATIC struct kobj_attribute bfgx_loglevel =
__ATTR(loglevel, 0664, (void *)show_loglevel, (void *)store_loglevel);

/*TODO:х╗оч0666fix*/
STATIC struct kobj_attribute bfgx_ir_ctrl =
__ATTR(ir_ctrl, 0666, (void *)show_ir_mode, (void *)store_ir_mode);

STATIC struct kobj_attribute bfgx_dev_test =
__ATTR(bfgx_test, 0664, (void *)show_dev_test, (void *)store_dev_test);

STATIC struct attribute *bfgx_attrs[] = {
        &ldisc_install.attr,
        &uart_dev_name.attr,
        &uart_baud_rate.attr,
        &uart_flow_cntrl.attr,
        &gnss_lowpower_cntrl.attr,
        &bfg_active_state.attr,
        &bfgx_loglevel.attr,
        &bfgx_ir_ctrl.attr,
        &bfgx_dev_test.attr,
        NULL,
};

STATIC struct attribute_group bfgx_attr_grp = {
    .attrs = bfgx_attrs,
};

STATIC ssize_t show_bfgx_reset(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: reset msg is %d\n", pst_exception_data->reset_device_msg);
    return sprintf(buf, "%d\n", pst_exception_data->reset_device_msg);
}

STATIC ssize_t show_bfgx_rf_temp(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: bfgx rf temp status is %d\n", atomic_read(&pst_exception_data->bfgx_rf_temperature_status));
    return sprintf(buf, "%d\n", atomic_read(&pst_exception_data->bfgx_rf_temperature_status));
}

STATIC ssize_t show_bfgx_exception_count(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: bfgx rst count is %d\n", pst_exception_data->bfgx_exception_cnt);
    return sprintf(buf, "%d\n", pst_exception_data->bfgx_exception_cnt);
}

STATIC ssize_t show_wifi_exception_count(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: wifi rst count is %d\n", pst_exception_data->wifi_exception_cnt);
    return sprintf(buf, "%d\n", pst_exception_data->wifi_exception_cnt);
}

STATIC ssize_t show_system_power_reset(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    PS_PRINT_DBG("exception debug: reset msg is %d\n", pst_exception_data->reset_device_msg);
    return sprintf(buf, "%d\n", pst_exception_data->reset_device_msg);
}

STATIC ssize_t show_exception_dbg(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    PS_PRINT_INFO("%s", __func__);
    return sprintf(buf, "cmd  func\n"
                        "  1  close bt    \n  2  set beat flat to 0\n");
}

STATIC ssize_t store_exception_dbg(struct device *dev, struct kobj_attribute *attr, const char *buf, size_t count)
{
    int32  cmd = 0;
    int32  ret = 0;
    struct ps_core_s *ps_core_d = NULL;
    struct st_exception_info *pst_exception_data = NULL;

    get_exception_info_reference(&pst_exception_data);
    if (NULL == pst_exception_data)
    {
        PS_PRINT_ERR("get exception info reference is error\n");
        return 0;
    }

    ps_get_core_reference(&ps_core_d);
    if (NULL == ps_core_d)
    {
        PS_PRINT_ERR("ps_core_d is NULL\n");
        return 0;
    }

    cmd = simple_strtol(buf, NULL, 10);
    PS_PRINT_INFO("cmd:%d", cmd);

    ret = prepare_to_visit_node(ps_core_d);
    if (ret < 0)
    {
        PS_PRINT_ERR("prepare work FAIL\n");
        post_to_visit_node(ps_core_d);
        return ret;
    }

    switch (cmd)
    {
        case 1:
            PS_PRINT_INFO("exception debug test: close BT\n");
            ps_tx_sys_cmd(ps_core_d, SYS_MSG, SYS_CFG_CLOSE_BT);
            break;

        case 2:
            PS_PRINT_INFO("exception: set debug beat flag to 0\n");
            pst_exception_data->debug_beat_flag = 0;
            break;

        default:
            break;
    }

    post_to_visit_node(ps_core_d);

    return count;
}

STATIC struct kobj_attribute bfgx_exception_reset =
__ATTR(bfgx_reset, 0444, (void *)show_bfgx_reset, NULL);

STATIC struct kobj_attribute bfgx_rf_overheat =
__ATTR(bfgx_rf_temp, 0444, (void *)show_bfgx_rf_temp, NULL);

STATIC struct kobj_attribute bfgx_exception_count =
__ATTR(bfgx_rst_count, 0444, (void *)show_bfgx_exception_count, NULL);

STATIC struct kobj_attribute wifi_exception_count =
__ATTR(wifi_rst_count, 0444, (void *)show_wifi_exception_count, NULL);

STATIC struct kobj_attribute system_power_reset =
__ATTR(power_reset, 0444, (void *)show_system_power_reset, NULL);

STATIC struct kobj_attribute plat_exception_dbg =
__ATTR(exception_dbg, 0644, (void *)show_exception_dbg, (void *)store_exception_dbg);

STATIC struct attribute *exception_attrs[] = {
        &bfgx_exception_reset.attr,
        &bfgx_rf_overheat.attr,
        &bfgx_exception_count.attr,
        &wifi_exception_count.attr,
        &system_power_reset.attr,
        &plat_exception_dbg.attr,
        NULL,
};

STATIC struct attribute_group exception_attr_grp = {
    .attrs = exception_attrs,
};

STATIC ssize_t show_hisi_nfc_conf_name(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    char hisi_nfc_conf_name[BUFF_LEN] = {0};
    int32 ret = 0;

    ret = read_nfc_conf_name_from_dts(hisi_nfc_conf_name, sizeof(hisi_nfc_conf_name),
                                       DTS_COMP_HISI_NFC_NAME, DTS_COMP_HW_HISI_NFC_CONFIG_NAME);
    if (ret < 0)
    {
        PS_PRINT_ERR("read_nfc_conf_name_from_dts %s,ret = %d\n", DTS_COMP_HW_HISI_NFC_CONFIG_NAME, ret);
        return ret;
    }

    return snprintf(buf, sizeof(hisi_nfc_conf_name), "%s", hisi_nfc_conf_name);
}

STATIC ssize_t show_brcm_nfc_conf_name(struct device *dev, struct device_attribute *attr, int8 *buf)
{
    char brcm_nfc_conf_name[BUFF_LEN] = {0};
    int32 ret = 0;

    ret = read_nfc_conf_name_from_dts(brcm_nfc_conf_name, sizeof(brcm_nfc_conf_name),
                                       DTS_COMP_HISI_NFC_NAME, DTS_COMP_HW_BRCM_NFC_CONFIG_NAME);
    if (ret < 0)
    {
        PS_PRINT_ERR("read_nfc_conf_name_from_dts %s,ret = %d\n", DTS_COMP_HW_BRCM_NFC_CONFIG_NAME, ret);
        return ret;
    }

    return snprintf(buf, sizeof(brcm_nfc_conf_name), "%s", brcm_nfc_conf_name);
}

STATIC struct kobj_attribute hisi_nfc_conf =
__ATTR(nxp_config_name, 0444, (void *)show_hisi_nfc_conf_name, NULL);

STATIC struct kobj_attribute brcm_nfc_conf =
__ATTR(nfc_brcm_conf_name, 0444, (void *)show_brcm_nfc_conf_name, NULL);

STATIC struct attribute *hisi_nfc_attrs[] = {
        &hisi_nfc_conf.attr,
        &brcm_nfc_conf.attr,
        NULL,
};

STATIC struct attribute_group hisi_nfc_attr_grp = {
    .attrs = hisi_nfc_attrs,
};

int32 bfgx_user_ctrl_init(void)
{
    int status;
    struct kobject *pst_root_object = NULL;

    pst_root_object = oal_get_sysfs_root_object();
    if(NULL == pst_root_object)
    {
        PS_PRINT_ERR("[E]get root sysfs object failed!\n");
        return -EFAULT;
    }

    g_sysfs_hisi_pmdbg = kobject_create_and_add("pmdbg", pst_root_object);
    if (NULL == g_sysfs_hisi_pmdbg)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hisi_pmdbg !!!\n ");
		goto fail_g_sysfs_hisi_pmdbg;
    }

    status = sysfs_create_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
    if (status)
    {
		PS_PRINT_ERR("failed to create g_sysfs_hisi_pmdbg sysfs entries\n");
		goto fail_create_pmdbg_group;
    }

    g_sysfs_hi110x_bfgx = kobject_create_and_add("hi110x_ps", NULL);
    if (NULL == g_sysfs_hi110x_bfgx)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_hi110x_ps !!!\n ");
		goto fail_g_sysfs_hi110x_bfgx;
    }

    status = sysfs_create_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
    if (status)
    {
		PS_PRINT_ERR("failed to create g_sysfs_hi110x_bfgx sysfs entries\n");
		goto fail_create_bfgx_group;
    }

    g_sysfs_bfgx_exception = kobject_create_and_add("hi110x_exception", NULL);
    if (NULL == g_sysfs_bfgx_exception)
    {
        PS_PRINT_ERR("Failed to creat g_sysfs_bfgx_exception !!!\n ");
        goto fail_g_sysfs_bfgx_exception;
    }

    status = sysfs_create_group(g_sysfs_bfgx_exception, &exception_attr_grp);
    if (status)
    {
		PS_PRINT_ERR("failed to create g_sysfs_bfgx_exception sysfs entries\n");
		goto fail_create_exception_group;
    }

    if (!is_my_nfc_chip())
    {
        PS_PRINT_ERR("cfg dev board nfc chip type is not match, skip driver init");
    }
    else
    {
        PS_PRINT_INFO("cfg dev board nfc type is matched with hisi_nfc, continue");
        g_sysfs_hisi_nfc = kobject_create_and_add("nfc", NULL);
        if (NULL == g_sysfs_hisi_nfc)
        {
            PS_PRINT_ERR("Failed to creat g_sysfs_hisi_nfc !!!\n ");
            goto fail_g_sysfs_hisi_nfc;
        }

        status = sysfs_create_group(g_sysfs_hisi_nfc, &hisi_nfc_attr_grp);
        if (status)
        {
            PS_PRINT_ERR("failed to create g_sysfs_hisi_nfc sysfs entries\n");
            goto fail_create_hisi_nfc_group;
        }
    }

    return 0;

fail_create_hisi_nfc_group:
    kobject_put(g_sysfs_hisi_nfc);
fail_g_sysfs_hisi_nfc:
    sysfs_remove_group(g_sysfs_bfgx_exception, &exception_attr_grp);
fail_create_exception_group:
    kobject_put(g_sysfs_bfgx_exception);
fail_g_sysfs_bfgx_exception:
    sysfs_remove_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
fail_create_bfgx_group:
    kobject_put(g_sysfs_hi110x_bfgx);
fail_g_sysfs_hi110x_bfgx:
    sysfs_remove_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
fail_create_pmdbg_group:
    kobject_put(g_sysfs_hisi_pmdbg);
fail_g_sysfs_hisi_pmdbg:
    return -EFAULT;
}

void bfgx_user_ctrl_exit(void)
{
    if (is_my_nfc_chip())
    {
        sysfs_remove_group(g_sysfs_hisi_nfc, &hisi_nfc_attr_grp);
        kobject_put(g_sysfs_hisi_nfc);
    }

	sysfs_remove_group(g_sysfs_bfgx_exception, &exception_attr_grp);
	kobject_put(g_sysfs_bfgx_exception);

	sysfs_remove_group(g_sysfs_hi110x_bfgx, &bfgx_attr_grp);
	kobject_put(g_sysfs_hi110x_bfgx);

	sysfs_remove_group(g_sysfs_hisi_pmdbg, &pmdbg_attr_grp);
	kobject_put(g_sysfs_hisi_pmdbg);
}

