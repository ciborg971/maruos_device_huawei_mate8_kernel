/* Copyright (c) 2014-2015, Hisilicon Tech. Co., Ltd. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 */

#include "hisi_fb.h"

#if defined (CONFIG_ATFDRIVER)
#define MASTER_DSS_ID   (2)
struct dss_config_reg {
    uint32_t addr;
    uint32_t val;
    uint8_t bw;
    uint8_t bs;
};
static void configure_dss_register_security(uint32_t addr, uint32_t val, uint8_t bw, uint8_t bs)
{
    u8 *security_config_buff_addr_va = NULL;
    u64 security_config_buff_addr_pa = 0;
    struct hisi_fb_data_type *hisifd = NULL;
    struct dss_config_reg dss_data;

    dss_data.addr = addr;
    dss_data.val = val;
    dss_data.bw = bw;
    dss_data.bs = bs;

    hisifd = hisifd_list[PRIMARY_PANEL_IDX];

    security_config_buff_addr_va = (unsigned char *)dma_alloc_coherent(hisifd->fbi->dev, 64, &security_config_buff_addr_pa, GFP_KERNEL);
    if (!security_config_buff_addr_va) {
        return;
    }
    memcpy((struct dss_reg*)security_config_buff_addr_va, &dss_data, sizeof(dss_data));
    (void)atfd_hisi_service_access_register_smc(ACCESS_REGISTER_FN_MAIN_ID, security_config_buff_addr_pa, (u64)MASTER_DSS_ID, ACCESS_REGISTER_FN_SUB_ID_DDR_DSS);

    return;
}
#endif
static int tui_thread_runner(void *data)
{
    int ret = 0, secu_cfg_ing = 0, secu_pay = 0, first_frame = 1;
    struct hisifb_secure *secure_ctrl = NULL;
    struct hisi_fb_data_type *hisifd = (struct hisi_fb_data_type *)data;

    BUG_ON(hisifd == NULL);
    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);

    while (!kthread_should_stop()) {
        secu_pay = inp32(hisifd->dss_base + DSS_MCTRL_SYS_OFFSET + MCTL_CTL_SECU_CFG);
        secu_pay = secu_pay & BIT(4);

        if ((secure_ctrl->secure_status == DSS_SEC_RUNNING) && (secu_pay)) {
            secu_cfg_ing = inp32(hisifd->dss_base + DSS_MCTRL_CTL4_OFFSET + MCTL_CTL_MUTEX);
            secu_cfg_ing = secu_cfg_ing & BIT(0);
            if (first_frame) {
                if (secu_cfg_ing) {
                    ret = 0;
                    first_frame = 0;
                    HISI_FB_INFO("TUI first_frame start...\n");
                } else {
                    ret = -1;
                }
            } else {
                if (secu_cfg_ing) {
                    ret = -1;
                } else {
                    //if not first secure frame, wait for vactive0 start irq
                    if (secure_ctrl->tui_vactive_start_flag == 0) {
                        ret = wait_event_interruptible(secure_ctrl->tui_wq, secure_ctrl->tui_vactive_start_flag);
                    }
                }
            }

            if (!ret) {
                down(&hisifd->blank_sem);
                secure_ctrl->tui_vactive_start_flag = 0;
                if (secure_ctrl->check_single_update) {
                    secure_ctrl->check_single_update(hisifd);
                }

                //if tui data comes before android data,then android data is delayed to next vactive0_start
                //caution:only in secu_pay, we clear the vactive0_start_flag.
                hisifd->vactive0_start_flag = 0;
                up(&hisifd->blank_sem);
            }
        } else {
            secure_ctrl->tui_vactive_start_flag = 1;
        }
    }
    return 0;
}
static void hisifb_secure_ctrl_wq_handler(struct work_struct *work)
{
    struct hisi_fb_data_type *hisifd = NULL;
    struct hisifb_secure *secure_ctrl = NULL;
    secure_ctrl = container_of(work, typeof(*secure_ctrl), secure_ctrl_work);
    BUG_ON(secure_ctrl == NULL);
    hisifd = secure_ctrl->hisifd;
    BUG_ON(hisifd == NULL);

    HISI_FB_INFO(": secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d +++ \n",\
            secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no);
    spin_lock(&(secure_ctrl->spin_lock));
    if ((DSS_SEC_IDLE == secure_ctrl->secure_status)
            && (DSS_SEC_ENABLE == secure_ctrl->secure_event)) {
        secure_ctrl->secure_status = DSS_SEC_RUNNING;
    }
    spin_unlock(&(secure_ctrl->spin_lock));

    if ((DSS_SEC_RUNNING == secure_ctrl->secure_status)
            && (DSS_SEC_ENABLE == secure_ctrl->secure_event)) {
        hisifb_activate_vsync(hisifd);
        if (is_mipi_cmd_panel(hisifd)) {
            if (secure_ctrl->tui_thread == NULL)
                secure_ctrl->tui_thread = kthread_run(tui_thread_runner, secure_ctrl->hisifd, "dss_tui_thread");
            if (IS_ERR(secure_ctrl->tui_thread)) {
                secure_ctrl->tui_thread = NULL;
                HISI_FB_ERR("ERROR create tui_thread. \n");
            }
        }
#if defined (CONFIG_TEE_TUI)
        send_tui_msg_config(TUI_POLL_CFG_OK, 0, "DSS");
#endif
        HISI_FB_INFO("TUI switch to DSS_SEC_RUNNING succ!!!\n");
    }

    HISI_FB_INFO(": secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d --- \n",\
            secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no);
}

/* receive switch tui request
 **1: secure enable
 **0: secure disable
 */
static int notify_dss_tui_request(void *data, int secure)
{
    int ret = 0;
    struct hisifb_secure *secure_ctrl = NULL;
    struct hisi_fb_data_type *hisifd = NULL;
    int tui_request = secure ? DSS_SEC_ENABLE : DSS_SEC_DISABLE;

    hisifd = (struct hisi_fb_data_type *)data; //hisifd_list[PRIMARY_PANEL_IDX];
    BUG_ON(hisifd == NULL);
    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);

    if (!secure_ctrl->secure_created) {
        HISI_FB_ERR("fb%d, secure is not created yet!\n", hisifd->index);
        return -1;
    }

    if (!hisifd->panel_power_on) {
        HISI_FB_INFO("fb%d, panel is power off!", hisifd->index);
        return -1;
    }
    HISI_FB_INFO("secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d , tui_request = %d +++ \n",\
            secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no, tui_request);

    spin_lock(&secure_ctrl->spin_lock);
    if (secure_ctrl->secure_event == tui_request) {
        spin_unlock(&secure_ctrl->spin_lock);
        HISI_FB_INFO("secure_status = %d,---!\n", secure_ctrl->secure_status);
        return -1;
    }
    secure_ctrl->secure_event = tui_request;
    spin_unlock(&secure_ctrl->spin_lock);

    if (DSS_SEC_ENABLE == secure_ctrl->secure_event) {
        hisifd->dss_module_default.mctl_sys.chn_ov_sel[DSS_OVL0] = set_bits32(hisifd->dss_module_default.mctl_sys.chn_ov_sel[DSS_OVL0], TUI_SEC_RCH, 4, 24);
    } else {
        hisifd->dss_module_default.mctl_sys.chn_ov_sel[DSS_OVL0] = 0xFFFFFFFF;
        if (is_mipi_cmd_panel(hisifd)) {
            if (secure_ctrl->tui_thread) {
                kthread_stop(secure_ctrl->tui_thread);
                secure_ctrl->tui_thread = NULL;
            }
        }
        secure_ctrl->secure_status = DSS_SEC_IDLE;
    }
    secure_ctrl->tui_frame_processed = 0;
    hisifb_activate_vsync(hisifd);
    secure_ctrl->tui_need_switch = 1;
    secure_ctrl->tui_vactive_start_flag = 1;
    wake_up_interruptible_all(&(hisifd->vsync_ctrl.vsync_wait));

    if (secure_ctrl->secure_blank_flag) {
        ret = hisi_fb_blank_sub(FB_BLANK_POWERDOWN, hisifd->fbi);
        if (ret != 0) {
            HISI_FB_ERR("fb%d, blank_mode(%d) failed!\n", hisifd->index, FB_BLANK_POWERDOWN);
        }
        secure_ctrl->secure_blank_flag = 0;
    }

    HISI_FB_INFO("secure_ctrl->secure_status = %d, secure_ctrl->secure_event = %d, frame_no = %d , tui_request = %d --- \n",\
            secure_ctrl->secure_status, secure_ctrl->secure_event, hisifd->ov_req.frame_no, tui_request);
    return 0;
}

/////////////////////////////////////////////////////////////////////////////////////////
static ssize_t hisifb_secure_event_store(struct device* dev,
        struct device_attribute* attr, const char* buf, size_t count)
{
    int val = 0;
    struct fb_info *fbi = NULL;
    struct hisi_fb_data_type *hisifd = NULL;

    if (NULL == dev) {
        HISI_FB_ERR("NULL Pointer\n");
        return 0;
    }

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        HISI_FB_ERR("NULL Pointer\n");
        return 0;
    }

    hisifd = (struct hisi_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        HISI_FB_ERR("NULL Pointer\n");
        return 0;
    }

    val = (int)simple_strtoul(buf, NULL, 0);

    notify_dss_tui_request(hisifd, val);

    return count;
}

static ssize_t hisifb_secure_event_show(struct device *dev,
        struct device_attribute *attr, char *buf)
{
    ssize_t ret = 0;
    struct fb_info *fbi = NULL;
    struct hisi_fb_data_type *hisifd = NULL;

    if (NULL == dev) {
        HISI_FB_ERR("NULL Pointer\n");
        return 0;
    }

    fbi = dev_get_drvdata(dev);
    if (NULL == fbi) {
        HISI_FB_ERR("NULL Pointer\n");
        return 0;
    }

    hisifd = (struct hisi_fb_data_type *)fbi->par;
    if (NULL == hisifd) {
        HISI_FB_ERR("NULL Pointer\n");
        return 0;
    }

    snprintf(buf, PAGE_SIZE, "SECURE_EVENT=%d, SECURE_STATUS=%d\n",
        hisifd->secure_ctrl.secure_event, hisifd->secure_ctrl.secure_status);
    ret = strlen(buf) + 1;
    return ret;
}

/*lint -e665*/
static DEVICE_ATTR(dss_secure, S_IRUGO|S_IWUSR, hisifb_secure_event_show, hisifb_secure_event_store);
/*lint -e665*/

/* for DRM config */
static void hisifd_secure_layer_config(struct hisi_fb_data_type *hisifd, dss_layer_t *layer)
{
    struct hisifb_secure *secure_ctrl = NULL;
    dss_module_reg_t *dss_module = NULL;

    BUG_ON(hisifd == NULL);
    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);
    dss_module = &(hisifd->dss_module);
    HISI_FB_INFO(": ++ chn_idx: %d \n", layer->chn_idx);


    HISI_FB_INFO(": --\n");
}
static void hisifd_secure_layer_deconfig(struct hisi_fb_data_type *hisifd, dss_layer_t *layer)
{
    struct hisifb_secure *secure_ctrl = NULL;
    dss_module_reg_t *dss_module = NULL;
    uint32_t dss_base = 0;
    BUG_ON(hisifd == NULL);
    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);
    dss_module = &(hisifd->dss_module);
    HISI_FB_INFO(": ++ chn_idx: %d \n", layer->chn_idx);
    dss_base = hisifd->dss_base_phy;

    HISI_FB_INFO(": --\n");
}
static void hisifd_notify_secure_switch(struct hisi_fb_data_type *hisifd)
{
    struct hisifb_secure *secure_ctrl = NULL;
    BUG_ON(hisifd == NULL);
    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);

    if (secure_ctrl->secure_status != secure_ctrl->secure_event) {
        if (hisifd->ov_req.sec_enable_status == DSS_SEC_ENABLE) {
            schedule_work(&secure_ctrl->secure_ctrl_work);
        }
    }

}
static void hisifd_check_single_update(struct hisi_fb_data_type *hisifd)
{
    unsigned int count = 0;
    char __iomem *ldi_base;
    char __iomem *dss_base;
    unsigned int secu_cfg_ing = 0;
    struct hisifb_secure *secure_ctrl = NULL;

    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);
    dss_base = hisifd->dss_base;
    ldi_base = dss_base + DSS_LDI0_OFFSET;

    if (!secure_ctrl->tui_frame_processed) {
        secure_ctrl->tui_frame_processed = 1;

        secu_cfg_ing = inp32(dss_base + DSS_MCTRL_CTL4_OFFSET + MCTL_CTL_MUTEX);
        secu_cfg_ing = secu_cfg_ing & BIT(0);

        // wait for secu_cfg_ok being changed to 0
        for (count = 0; (count < 500) && (secu_cfg_ing); count++) {
            udelay(100);
            secu_cfg_ing = inp32(dss_base + DSS_MCTRL_CTL4_OFFSET + MCTL_CTL_MUTEX);
            secu_cfg_ing = secu_cfg_ing & BIT(0);
        }
        if (count >= 500) {
            HISI_FB_INFO("waiting for secu_cfg_ok timeout!\n");
        }
        /* for single mode need */
        //secure_ctrl->set_reg(hisifd->dss_base_phy + DSS_MCTRL_SYS_OFFSET + MCTL_PAY_SECU_FLUSH_EN, 0x1, 32, 0);

        set_reg(ldi_base + LDI_FRM_MSK_UP, 0x1, 1, 0);
        set_reg(ldi_base + LDI_CTRL, 0x1, 1, 0);
    }
}

static void hisifd_secure_set_reg(uint32_t addr, uint32_t val, uint8_t bw, uint8_t bs)
{
#if defined (CONFIG_ATFDRIVER)
    configure_dss_register_security(addr, val, bw, bs);
#endif
}

void hisifb_secure_register(struct platform_device *pdev)
{
    struct hisi_fb_data_type *hisifd = NULL;
    struct hisifb_secure *secure_ctrl = NULL;

    BUG_ON(pdev == NULL);
    hisifd = platform_get_drvdata(pdev);
    BUG_ON(hisifd == NULL);
    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);

    if (secure_ctrl->secure_created) {
        return;
    }
    secure_ctrl->secure_status = DSS_SEC_IDLE;
    secure_ctrl->secure_event  = DSS_SEC_DISABLE;
    secure_ctrl->secure_blank_flag = 0;
    secure_ctrl->tui_need_switch = 0;
    secure_ctrl->tui_vactive_start_flag = 1;
    secure_ctrl->tui_frame_processed = 0;

    init_waitqueue_head(&(secure_ctrl->tui_wq));
    INIT_WORK(&secure_ctrl->secure_ctrl_work, hisifb_secure_ctrl_wq_handler);
    spin_lock_init(&(secure_ctrl->spin_lock));

#if defined (CONFIG_TEE_TUI)
    /* register dss tui process function to sw */
    register_tui_driver(notify_dss_tui_request, "DSS", hisifd);
#endif
    secure_ctrl->secure_layer_config = hisifd_secure_layer_config;
    secure_ctrl->secure_layer_deconfig = hisifd_secure_layer_deconfig;
    secure_ctrl->notify_secure_switch = hisifd_notify_secure_switch;
    secure_ctrl->check_single_update = hisifd_check_single_update;
    secure_ctrl->set_reg = hisifd_secure_set_reg;
    secure_ctrl->hisifd = hisifd;

    secure_ctrl->secure_created = 1;

    if (hisifd->sysfs_attrs_append_fnc)
        hisifd->sysfs_attrs_append_fnc(hisifd, &dev_attr_dss_secure.attr);
}

void hisifb_secure_unregister(struct platform_device *pdev)
{
    struct hisi_fb_data_type *hisifd = NULL;
    struct hisifb_secure *secure_ctrl = NULL;

    BUG_ON(pdev == NULL);
    hisifd = platform_get_drvdata(pdev);
    BUG_ON(hisifd == NULL);
    secure_ctrl = &(hisifd->secure_ctrl);
    BUG_ON(secure_ctrl == NULL);

    if (!secure_ctrl->secure_created)
        return;

    secure_ctrl->secure_created = 0;
}
