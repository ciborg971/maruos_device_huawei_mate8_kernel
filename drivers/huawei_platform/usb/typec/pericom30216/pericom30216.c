

#include <linux/i2c.h>
#include <linux/delay.h>
#include <linux/gpio.h>
#include <linux/timer.h>
#include <linux/param.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/workqueue.h>
#include <linux/slab.h>
#include <linux/device.h>
#include <linux/err.h>
#include <linux/interrupt.h>
#include <linux/io.h>
#include <linux/platform_device.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <asm/irq.h>
#include <linux/uaccess.h>
#include <linux/fs.h>
#include <linux/huawei/usb/hisi_usb.h>
#include <huawei_platform/log/hw_log.h>
#ifdef CONFIG_HUAWEI_HW_DEV_DCT
#include <linux/hw_dev_dec.h>
#endif
#include "pericom30216.h"
#include "../../switch/switch_usb_class.h"
#include <huawei_platform/usb/hw_typec_dev.h>

#define HWLOG_TAG pericom30216_typec
HWLOG_REGIST();

struct typec_device_info *g_pericom30216_dev = NULL;

static int pericom30216_read_reg(int regnr)
{
    u8 buf[PERICOM30216_REGISTER_NUM];
    struct typec_device_info *di = g_pericom30216_dev;

    struct i2c_msg msgs[1] = {
        {
            .addr = di->client->addr,
            .flags = I2C_M_RD,
            .len = sizeof(u8) * PERICOM30216_REGISTER_NUM,
            .buf = (void *)buf
        },
    };

    if (i2c_transfer(di->client->adapter, msgs, 1) != 1)
        return -EIO;

    di->reg[regnr - 1] = buf[regnr - 1];

    return 0;
}

static int pericom30216_read_all_reg(void)
{
    int i;
    u8 buf[PERICOM30216_REGISTER_NUM];
    struct typec_device_info *di = g_pericom30216_dev;

    struct i2c_msg msgs[1] = {
        {
            .addr = di->client->addr,
            .flags = I2C_M_RD,
            .len = sizeof(u8) * PERICOM30216_REGISTER_NUM,
            .buf = (void *)buf
        },
    };

    if (i2c_transfer(di->client->adapter, msgs, 1) != 1)
        return -EIO;

    for (i = 0; i < 4; i++) {
        di->reg[i] = buf[i];
    }

    return 0;
}

static int pericom30216_write_reg(u8 reg, u8 value)
{
    int i;
    u8 buf[PERICOM30216_REGISTER_NUM];
    struct typec_device_info *di = g_pericom30216_dev;

    struct i2c_msg msgs[1] = {
        {
            .addr = di->client->addr,
            .len = sizeof(u8) * PERICOM30216_REGISTER_NUM,
            .buf = (void *)buf
        },
    };

    pericom30216_read_all_reg();

    for (i = 0; i < PERICOM30216_REGISTER_NUM; i++)
        buf[i] = di->reg[i];

    buf[reg - 1] = value;

    if (i2c_transfer(di->client->adapter, msgs, 1) != 1)
        return -EIO;

    return 0;
}

static int pericom30216_clean_int_mask(void)
{
    u8 reg_val;
    struct typec_device_info *di = g_pericom30216_dev;

    pericom30216_read_reg(PERICOM30216_REG_CONTROL);
    reg_val = di->reg[PERICOM30216_REG_CONTROL - 1];
    reg_val &= ~PERICOM30216_REG_CONTROL_INT_MASK;

    pericom30216_write_reg(PERICOM30216_REG_CONTROL, reg_val);

    return 0;
}

static int pericom30216_device_check(void)
{
    return pericom30216_read_reg(PERICOM30216_REG_DEVICE_ID);
}

static int pericom30216_current_status_setting(u8 val)
{
    struct typec_device_info *di = g_pericom30216_dev;
    u8 reg_val, current_set_val, mask_val;
    int ret;

    ret = pericom30216_read_reg(PERICOM30216_REG_CONTROL);
    if (ret < 0) {
        hwlog_err("%s: read PERICOM30216_REG_CONTROL error ret = %d\n", __func__, ret);
        return ret;
    }

    reg_val = di->reg[PERICOM30216_REG_CONTROL - 1];
    mask_val = reg_val & (~PERICOM30216_REG_SET_CURRENT_STATUES);
    current_set_val = reg_val & PERICOM30216_REG_SET_CURRENT_STATUES;

    if (val == current_set_val) {
        hwlog_info("%s: current mode is same as setting\n", __func__);
        return 0;
    }

    val |= mask_val;
    ret = pericom30216_write_reg(PERICOM30216_REG_CONTROL, val);
    if (ret < 0) {
        hwlog_err("%s: read PERICOM30216_REG_CONTROL error ret = %d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static int pericom30216_ctrl_output_current(int value)
{
    switch (value) {
        case TYPEC_HOST_CURRENT_DEFAULT:
            hwlog_info("%s: set to default current\n", __func__);
            pericom30216_current_status_setting(PERICOM30216_REG_CONTROL_DEFAULT_CURRENT);
            break;
        case TYPEC_HOST_CURRENT_MID:
            hwlog_info("%s: set to medium current\n", __func__);
            pericom30216_current_status_setting(PERICOM30216_REG_CONTROL_MID_CURRENT);
            break;
        case TYPEC_HOST_CURRENT_HIGH:
            hwlog_info("%s: set to high current\n", __func__);
            pericom30216_current_status_setting(PERICOM30216_REG_CONTROL_HIGH_CURRENT);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -1;
    }

    return 0;
}

static int pericom30216_port_status_setting(u8 val)
{
    struct typec_device_info *di = g_pericom30216_dev;
    u8 reg_val, port_set_val, mask_val;
    int ret;

    ret = pericom30216_read_reg(PERICOM30216_REG_CONTROL);
    if (ret < 0) {
        hwlog_err("%s: read PERICOM30216_REG_CONTROL error ret = %d\n", __func__, ret);
        return ret;
    }

    reg_val = di->reg[PERICOM30216_REG_CONTROL - 1];
    mask_val = reg_val & (~PERICOM30216_REG_SET_PORT_STATUS);
    port_set_val = reg_val & PERICOM30216_REG_SET_PORT_STATUS;

    if (val == port_set_val) {
    hwlog_info("%s: port mode is same as setting\n", __func__);
    return 0;
    }

    val |= mask_val;
    ret = pericom30216_write_reg(PERICOM30216_REG_CONTROL, val);
    if (ret < 0) {
        hwlog_err("%s: read PERICOM30216_REG_CONTROL error ret = %d\n", __func__, ret);
        return ret;
    }

    return 0;
}

static int pericom30216_ctrl_port_mode(int value)
{
    switch (value) {
        case TYPEC_HOST_PORT_MODE_DFP:
            hwlog_info("%s: set to DFP mode\n", __func__);
            pericom30216_port_status_setting(PERICOM30216_REG_CONTROL_SET_DFP);
            break;
        case TYPEC_HOST_PORT_MODE_UFP:
            hwlog_info("%s: set to UFP mode\n", __func__);
            pericom30216_port_status_setting(PERICOM30216_REG_CONTROL_SET_UFP);
            break;
        case TYPEC_HOST_PORT_MODE_DRP:
            hwlog_info("%s: set to DRP mode\n", __func__);
            pericom30216_port_status_setting(PERICOM30216_REG_CONTROL_SET_DRP);
            break;
        default:
            hwlog_err("%s: wrong input action!\n", __func__);
            return -1;
    }

    return 0;
}

static int pericom30216_detect_attachment_status(void)
{
    struct typec_device_info *di = g_pericom30216_dev;
    u8 reg_val, reg_cc_status, reg_ctrl;

    pericom30216_read_all_reg();
    reg_val = di->reg[PERICOM30216_REG_INTERRUPT - 1];
    reg_cc_status = di->reg[PERICOM30216_REG_CC_STATUS - 1];
    reg_ctrl = di->reg[PERICOM30216_REG_CONTROL - 1];
    hwlog_info("%s: reg reg1 = 0x%x, reg2 = 0x%x, reg3 = 0x%x, reg4 = 0x%x \n", __func__, di->reg[0], di->reg[1], di->reg[2], di->reg[3]);

    // pericom30216 chip bug workaround
    if (0x97 == reg_cc_status) {
        mdelay(300);
        pericom30216_write_reg(PERICOM30216_REG_CONTROL, 0x01);
        pericom30216_write_reg(PERICOM30216_REG_CONTROL, 0x05);
        pericom30216_read_reg(PERICOM30216_REG_CC_STATUS);
        pericom30216_write_reg(PERICOM30216_REG_CONTROL, reg_ctrl);
    }

    if (reg_val & PERICOM30216_REG_ATTACH) {
        hwlog_info("%s: pericom ATTACH\n", __func__);
        di->dev_st.attach_status = TYPEC_ATTACH;
    } else if (reg_val & PERICOM30216_REG_DETACH) {
        hwlog_info("%s: pericom DETACH\n", __func__);
        di->dev_st.attach_status = TYPEC_DETACH;
    } else {
        /* there will be two interrupts when a DFP device is detected.
         the first is attach and the next is a none-type interrupt as a chip feature. */
    }

    return di->dev_st.attach_status;
}

static int pericom30216_detect_current_mode(void)
{
    struct typec_device_info *di = g_pericom30216_dev;
    u8 reg_val, current_detect_val;

    reg_val = di->reg[PERICOM30216_REG_CC_STATUS - 1];
    current_detect_val = reg_val & PERICOM30216_REG_DEV_CURRENT_MODE;

    switch (current_detect_val) {
        case PERICOM30216_REG_HIGH_CURRENT:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_HIGH;
            hwlog_info("%s: detected type c current is 3A\n", __func__);
            break;
        case PERICOM30216_REG_MID_CURRENT:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_MID;
            hwlog_info("%s: detected type c current is 1.5A\n", __func__);
            break;
        case PERICOM30216_REG_DEFAULT_CURRENT:
            di->dev_st.input_current = TYPEC_DEV_CURRENT_DEFAULT;
            hwlog_info("%s: detected type c current is default\n", __func__);
            break;
        default:
            return -1;
    }

    return di->dev_st.input_current;
}

static int pericom30216_detect_cc_orientation(void)
{
    struct typec_device_info *di = g_pericom30216_dev;
    u8 reg_val, cc_val;

    reg_val = di->reg[PERICOM30216_REG_CC_STATUS - 1];
    cc_val = reg_val & PERICOM30216_REG_CC_CONNECTED_STATUS;

    if (PERICOM30216_REG_CC1_CONNECTED == cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_CC1;
        hwlog_info("%s: cc1 detected\n", __func__);
    } else if (PERICOM30216_REG_CC2_CONNECTED == cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_CC2;
        hwlog_info("%s: cc2 detected\n", __func__);
    } else if (PERICOM30216_REG_CC_UNDERTERMINED == cc_val) {
        di->dev_st.cc_orient = TYPEC_ORIENT_NOT_READY;
        hwlog_info("%s: undetermined status is detected\n", __func__);
    } else {
        hwlog_err("%s: detect cc orientation error\n", __func__);
    }

    return di->dev_st.cc_orient;
}

static int pericom30216_detect_port_mode(void)
{
    struct typec_device_info *di = g_pericom30216_dev;
    u8 reg_val, port_mode_val;

    reg_val = di->reg[PERICOM30216_REG_CC_STATUS - 1];
    port_mode_val = reg_val & PERICOM30216_REG_PORT_MODE;

    if (PERICOM30216_REG_STATUS_UFP == port_mode_val) {
        hwlog_info("%s: UFP OTG DETECTED\n", __func__);
        /* UFP means the device detected is UFP, while the phone is DFP */
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_DFP;
    } else if (PERICOM30216_REG_STATUS_DFP == port_mode_val) {
        hwlog_info("%s: DFP HOST DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_UFP;
    } else if (PERICOM30216_REG_STATUS_AUDIO == port_mode_val) {
        hwlog_info("%s: AUDIO ACCESSORY DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_AUDIOACC;
    } else if (PERICOM30216_REG_STATUS_DEBUG == port_mode_val) {
        hwlog_info("%s: DEBUG ACCESSORY DETECTED\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_DEBUGACC;
    } else {
        hwlog_err("%s: detect port mode error\n", __func__);
        di->dev_st.port_mode = TYPEC_DEV_PORT_MODE_NOT_READY;
    }

    return di->dev_st.port_mode;
}

struct typec_device_ops pericom30216_ops = {
    .clean_int_mask = pericom30216_clean_int_mask,
    .detect_attachment_status = pericom30216_detect_attachment_status,
    .detect_cc_orientation = pericom30216_detect_cc_orientation,
    .detect_input_current = pericom30216_detect_current_mode,
    .detect_port_mode = pericom30216_detect_port_mode,
    .ctrl_output_current = pericom30216_ctrl_output_current,
    .ctrl_port_mode = pericom30216_ctrl_port_mode,
};

static ssize_t dump_regs_show(struct device *dev, struct device_attribute *attr,
                char *buf)
{
    struct typec_device_info *di = g_pericom30216_dev;

    return scnprintf(buf, PAGE_SIZE, "0x%02X,0x%02X,0x%02X,0x%02x\n",
                di->reg[0], di->reg[1], di->reg[2], di->reg[3]);
}
static DEVICE_ATTR(dump_regs, S_IRUGO, dump_regs_show, NULL);

static struct attribute *pericom30216_attributes[] = {
    &dev_attr_dump_regs.attr,
    NULL,
};

static const struct attribute_group pericom30216_attr_group = {
    .attrs = pericom30216_attributes,
};

static int pericom30216_create_sysfs(void)
{
    int ret = 0;
    struct class *typec_class = NULL;
    struct device *new_dev = NULL;

    typec_class = hw_typec_get_class();
    if (typec_class) {
        new_dev = device_create(typec_class, NULL, 0, NULL, "pericom30216");
        ret = sysfs_create_group(&new_dev->kobj, &pericom30216_attr_group);
        if (ret) {
            hwlog_err("pericom30216 sysfs create error\n");
        }
    }

    return ret;
}

static void pericom30216_remove_sysfs(struct typec_device_info *di)
{
    if (NULL == di) {
        hwlog_err("%s: di is NULL when tusb320 remove sysfs\n", __func__);
        return;
    }

    device_remove_file(&di->client->dev, &dev_attr_dump_regs);
}

static irqreturn_t pericom30216_irq_handler(int irq, void *dev_id)
{
    int gpio_value_intb;
    struct typec_device_info *di = dev_id;

    hwlog_info("%s: ------entry.\n", __func__);
    gpio_value_intb = gpio_get_value(di->gpio_intb);
    if (1 == gpio_value_intb)
        hwlog_err("%s: intb = %d when interrupt occured!!!\n", __func__, gpio_value_intb);

    schedule_work(&di->g_intb_work);

    return IRQ_HANDLED;
}

static int pericom30216_probe(
        struct i2c_client *client, const struct i2c_device_id *id)
{
    int ret = 0;
    int gpio_enb_val = 1;
    struct typec_device_info *di = NULL;
    struct typec_device_info *pdi = NULL;
    struct device_node *node;

    di = devm_kzalloc(&client->dev, sizeof(*di), GFP_KERNEL);
    if (!di) {
       hwlog_err("%s: alloc di error!\n", __func__);
       return -ENOMEM;
    }

    if (!i2c_check_functionality(client->adapter, I2C_FUNC_I2C)) {
        hwlog_err("%s: i2c_check_functionality error!!!\n", __func__);
        ret = -ENODEV;
        goto err_i2c_check_functionality_0;
    }

    g_pericom30216_dev = di;
    di->dev = &client->dev;
    di->client = client;
    node = di->dev->of_node;
    i2c_set_clientdata(client, di);

    di->gpio_enb = of_get_named_gpio(node, "pericom30216_typec,gpio_enb", 0);
    if (!gpio_is_valid(di->gpio_enb)) {
        hwlog_err("%s: of_get_named_gpio-enb error!!! ret=%d, gpio_enb=%d.\n", __func__, ret, di->gpio_enb);
        ret = -EINVAL;
        goto err_i2c_check_functionality_0;
    }

    ret = gpio_request(di->gpio_enb, "pericom30216_en");
    if (ret < 0) {
        hwlog_err("%s: gpio_request error!!! ret=%d. gpio=%d.\n", __func__, ret, di->gpio_enb);
        ret = -ENOMEM;
        goto err_i2c_check_functionality_0;
    }

    ret = of_property_read_u32(node, "pericom30216_gpio_enb", &gpio_enb_val);
    if (ret) {
        hwlog_err("%s: read gpio dts value ret=%d. gpio enb=%d.\n", __func__, ret, gpio_enb_val);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    hwlog_info("%s: read gpio dts value gpio enb=%d.\n", __func__, gpio_enb_val);
    ret = gpio_direction_output(di->gpio_enb, gpio_enb_val);
    if (ret < 0) {
        hwlog_err("%s: gpio_direction_input error!!! ret=%d. gpio=%d.\n", __func__, ret, di->gpio_enb);
        goto err_gpio_enb_request_1;
    }

    ret = pericom30216_device_check();
    if (ret < 0) {
        hwlog_err("%s: the chip is not pericom30216!!!\n", __func__);
        goto err_gpio_enb_request_1;
    }

    pdi = typec_chip_register(di->dev, &pericom30216_ops, THIS_MODULE);
    if (NULL == pdi) {
        hwlog_err("%s: typec register chip error!\n", __func__);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    di->gpio_intb = of_get_named_gpio(node, "pericom30216_typec,gpio_intb", 0);
    if (!gpio_is_valid(di->gpio_intb)) {
        hwlog_err("%s: of_get_named_gpio-intb error!!! ret=%d, gpio_intb=%d.\n", __func__, ret, di->gpio_intb);
        ret = -EINVAL;
        goto err_gpio_enb_request_1;
    }

    ret = gpio_request(di->gpio_intb, "pericom30216_int");
    if (ret < 0) {
        hwlog_err("%s: gpio_request error!!! ret=%d. gpio_intb=%d.\n", __func__, ret, di->gpio_intb);
        ret = -ENOMEM;
        goto err_gpio_enb_request_1;
    }

    di->irq_intb = gpio_to_irq(di->gpio_intb);
    if (di->irq_intb < 0) {
        hwlog_err("%s: gpio_to_irq error!!! ret=%d, gpio_intb=%d, irq_intb=%d.\n", __func__, ret, di->gpio_intb, di->irq_intb);
        goto err_gpio_intb_request_2;
    }

    ret = gpio_direction_input(di->gpio_intb);
    if (ret < 0) {
        hwlog_err("%s: gpio_direction_input error!!! ret=%d. gpio_intb=%d.\n", __func__, ret, di->gpio_intb);
        goto err_gpio_intb_request_2;
    }

    ret = request_irq(di->irq_intb,
               pericom30216_irq_handler,
               IRQF_NO_SUSPEND | IRQF_TRIGGER_FALLING,
               "pericom30216_int", pdi);
    if (ret) {
        hwlog_err("%s: request_irq error!!! ret=%d.\n", __func__, ret);
        di->irq_intb = -1;
        goto err_gpio_intb_request_2;
    }

    ret = pericom30216_create_sysfs();
    if (ret < 0) {
        hwlog_err("%s: create sysfs error %d\n", __func__, ret);
        goto err_irq_request_3;
    }

#ifdef CONFIG_HUAWEI_HW_DEV_DCT
    /* detect current device successful, set the flag as present */
    set_hw_dev_flag(DEV_I2C_TYPEC);
#endif

    hwlog_info("%s: ------end.\n", __func__);
    return ret;

err_irq_request_3:
    pericom30216_remove_sysfs(di);
    free_irq(di->gpio_intb, di);
err_gpio_intb_request_2:
    gpio_free(di->gpio_intb);
err_gpio_enb_request_1:
    gpio_free(di->gpio_enb);
err_i2c_check_functionality_0:
    g_pericom30216_dev = NULL;
    devm_kfree(&client->dev, di);
    di = NULL;

    hwlog_err("%s: ------FAIL!!! end. ret = %d.\n", __func__, ret);
    return ret;
}

static int pericom30216_remove(struct i2c_client *client)
{
    struct typec_device_info *di = i2c_get_clientdata(client);

    pericom30216_remove_sysfs(di);
    free_irq(di->irq_intb, di);
    gpio_set_value(di->gpio_enb, 1);
    gpio_free(di->gpio_enb);
    gpio_free(di->gpio_intb);
    g_pericom30216_dev = NULL;
    devm_kfree(&client->dev, di);
    di = NULL;

    return 0;
}

static const struct of_device_id typcc_pericom30216_ids[] = {
    { .compatible = "huawei,pericom30216" },
    {},
};
MODULE_DEVICE_TABLE(of, typcc_pericom30216_ids);

static const struct i2c_device_id pericom30216_i2c_id[] = {
    { "pericom30216", 0 },
    { }
};

static struct i2c_driver pericom30216_i2c_driver = {
    .driver = {
        .name = "pericom30216",
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(typcc_pericom30216_ids),
    },
    .probe = pericom30216_probe,
    .remove = pericom30216_remove,
    .id_table = pericom30216_i2c_id,
};

static __init int pericom30216_i2c_init(void)
{
    int ret = 0;
    hwlog_info("%s: ------entry.\n", __func__);

    ret = i2c_add_driver(&pericom30216_i2c_driver);
    if (ret) {
        hwlog_err("%s: i2c_add_driver error!!!\n", __func__);
    }

    hwlog_info("%s: ------end.\n", __func__);
    return ret;
}

static __exit void pericom30216_i2c_exit(void)
{
    i2c_del_driver(&pericom30216_i2c_driver);
}

module_init(pericom30216_i2c_init);
module_exit(pericom30216_i2c_exit);

MODULE_AUTHOR("WangJing<wangjing6@huawei.com>");
MODULE_DESCRIPTION("I2C bus driver for pericom30216 type c connector");
MODULE_LICENSE("GPL v2");
