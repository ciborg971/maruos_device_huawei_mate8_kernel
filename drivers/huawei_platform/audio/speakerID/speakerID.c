/*
 * speakerID.c -- speakerID driver
 *
 * Copyright (c) 2014 Huawei Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */
#include <linux/init.h>
#include <linux/input.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/regulator/consumer.h>
#include <linux/string.h>
#include <linux/workqueue.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/of_gpio.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/miscdevice.h>
#include <linux/uaccess.h>
#include <linux/platform_device.h>
#include <linux/huawei/hisi_adc.h>
#include <linux/pinctrl/consumer.h>
#include <huawei_platform/log/hw_log.h>

#define HWLOG_TAG speakerID
HWLOG_REGIST();

#define LOG_TAG "speakerID"

#define SPEAKER_ID_NAME    "speakerID"
#define ADC_READ_COUNT     3
#define SPEAKER_ID_LIMIT   500

#define SPEAKER_ID_HIGH    1
#define SPEAKER_ID_LOW   2

#define SPEAKER_ID_MODE_OF_GPIO    "gpio"

#ifdef CONFIG_LLT_TEST
struct speakerID_static_ops {
    int (*adc_read)();
    int (*gpio_read)();
    ssize_t (*speakerID_read)(struct file *file, char __user *user_buf, size_t count, loff_t *ppos);
    ssize_t (*speaker_id_gpio_show)(struct device* dev, struct device_attribute* attr, char* buf);
    int (*get_check_mode)(struct device_node *dev_node);
    int (*speakerID_probe)(struct platform_device *pdev);
    int (*speakerID_remove)(struct platform_device *pdev);
};
#endif

enum {
    SPEAKER_ID_MODE_USE_GPIO            = 0x0,
    SPEAKER_ID_MODE_USE_ADC             = 0x1,
};

enum {
    SPEAKER_ID_GPIO_TYPE_SOC            = 0x0,
    SPEAKER_ID_GPIO_TYPE_CODEC          = 0x1,
};

struct speaker_id{
    int adc_channel;
    int spk_id_limit;
    int gpio_id;
    int gpio_type;
    int check_mode;
};

struct speaker_id spk_id;

static int adc_read()
{
    int value;
    int loop = ADC_READ_COUNT;

    while(loop) {
        loop--;
        value = hisi_adc_get_value(spk_id.adc_channel);
        hwlog_info("adc_read adc:%d\n", value);
        if(value < 0) {
            hwlog_err("%s(%u) : get hkadc error err = %d\n", __FUNCTION__, __LINE__, value);
            continue;
        }
        break;
    }
    // read err default as SPEAKER_ID_LOW
    if(value < spk_id.spk_id_limit)
        return SPEAKER_ID_LOW;
    else
        return SPEAKER_ID_HIGH;
}

static int gpio_read()
{
    int value;

    if(spk_id.gpio_type == SPEAKER_ID_GPIO_TYPE_SOC) {
        value = gpio_get_value(spk_id.gpio_id);
    } else {
        value = gpio_get_value_cansleep(spk_id.gpio_id);
    }

    hwlog_info("%s:gpio read:%d\n",__FUNCTION__, value);

    if(!value)
        return SPEAKER_ID_LOW;
    else
        return SPEAKER_ID_HIGH;
}

static ssize_t speakerID_read(struct file *file, char __user *user_buf,
                            size_t count, loff_t *ppos)
{
    char buf[32] = {0};
    int id = 0;
    
    if(SPEAKER_ID_MODE_USE_GPIO == spk_id.check_mode){
        id = gpio_read();
    } else {
    	id = adc_read();
    }
    
    hwlog_info("speakerID_read id:%d\n", id);

    snprintf(buf, sizeof(buf), "%d", id);
    return simple_read_from_buffer(user_buf, count, ppos, buf, strlen(buf));
}

static const struct of_device_id speaker_id_match[] = {
    { .compatible = "huawei,speaker_id", },
    {},
};
MODULE_DEVICE_TABLE(of, speaker_id_match);

static const struct file_operations speakerID_fops = {
    .owner          = THIS_MODULE,
    .open           = simple_open,
    .read           = speakerID_read,
};

static struct miscdevice speakerID_device = {
    .minor  = MISC_DYNAMIC_MINOR,
    .name   = SPEAKER_ID_NAME,
    .fops   = &speakerID_fops,
};

static ssize_t speaker_id_gpio_show(struct device* dev,
                                     struct device_attribute* attr, char* buf)
{
     return  snprintf(buf, 32, "%d\n", gpio_read());
}

static DEVICE_ATTR(speaker_id_gpio_status, 0660, speaker_id_gpio_show, NULL);

static struct attribute* speaker_id_attributes[] =
{
    &dev_attr_speaker_id_gpio_status.attr,
    NULL
};

static const struct attribute_group speaker_id_attr_group =
{
    .attrs = speaker_id_attributes,
};

static int get_check_mode(struct device_node *dev_node)
{
    const char *mode;
    int rc;

    /*get check mode*/
	rc = of_property_read_string(dev_node, "check_mode", &mode);
	if (rc) {
		hwlog_info("%s: not find dev_node ,rc=%d\n", __FUNCTION__, rc);
        return SPEAKER_ID_MODE_USE_ADC;
	} else {
		hwlog_info("%s: mode: %s\n", __FUNCTION__, mode);
    }

    if (!strncmp(mode, SPEAKER_ID_MODE_OF_GPIO, sizeof(SPEAKER_ID_MODE_OF_GPIO))) {
		return SPEAKER_ID_MODE_USE_GPIO;
	}else{
        return SPEAKER_ID_MODE_USE_ADC;
    }
}

static int speakerID_probe(struct platform_device *pdev)
{
    int ret = -ENODEV;
    const struct of_device_id *match;
    struct device_node *node;
    int temp;
    struct pinctrl *p;
    struct pinctrl_state *pinctrl_def;

    match = of_match_device(speaker_id_match, &pdev->dev);
    if (!match) {
        hwlog_err("get speaker_id device info err\n");
        return -ENOENT;
    }
    node = pdev->dev.of_node;

    spk_id.check_mode = get_check_mode(node);

    if(SPEAKER_ID_MODE_USE_GPIO == spk_id.check_mode){
        spk_id.gpio_id = of_get_named_gpio(node, "gpios", 0);
	    if (spk_id.gpio_id  < 0) {
	        hwlog_err("%s: spk_id.gpio_id is unvalid!\n",__FUNCTION__);
	        return -ENOENT;
	    }

	    if (!gpio_is_valid(spk_id.gpio_id)) {
	        hwlog_err("%s:gpio is unvalid!\n",__FUNCTION__);
	        return -ENOENT;
	    }

        ret = gpio_request(spk_id.gpio_id, "speaker_id_check");
	    if (ret) {
	        hwlog_err("%s:error request GPIO for speaker_id_check fail %d\n",__FUNCTION__, ret);
	        return -ENODEV;
	    }

	    /* get gpio type */
	    if (!of_property_read_u32(node, "gpio_type", &temp)) {
	        spk_id.gpio_type= temp;
	    } else {
	        hwlog_err("get gpio type failed, set to SOC type\n");
	        spk_id.gpio_type = SPEAKER_ID_GPIO_TYPE_SOC;
	    }

	    if(spk_id.gpio_type == SPEAKER_ID_GPIO_TYPE_CODEC) {
	        p = devm_pinctrl_get(&pdev->dev);

	        if (IS_ERR(p)) {
	            hwlog_err("could not get pinctrl.\n");
	            gpio_free(spk_id.gpio_id);
	            return -ENOENT;
	        }

	        pinctrl_def = pinctrl_lookup_state(p, "default");
	        if (IS_ERR(pinctrl_def)) {
	            hwlog_err("could not get defstate.\n");
	            gpio_free(spk_id.gpio_id);
	            return -ENOENT;
	        }

	        ret = pinctrl_select_state(p, pinctrl_def);
	        if (ret) {
	            hwlog_err("could not set pins to default state.\n");
	            gpio_free(spk_id.gpio_id);
	            return -ENOENT;
	        }
			hwlog_info("init gpio success.\n");
	    }

	    /* set gpio to input status */
	    gpio_direction_input(spk_id.gpio_id);

        /* create sysfs for debug function */
	    if ((sysfs_create_group(&pdev->dev.kobj, &speaker_id_attr_group)) < 0) {
	        hwlog_err("%s:failed to register sysfs\n",__FUNCTION__);
	    }

    } else {
	    /* get channel id */
	    if (!of_property_read_u32(node, "channel", &temp)) {
	        spk_id.adc_channel= temp;
	    } else {
	        hwlog_err("get adc channel failed, set default value\n");
	        spk_id.adc_channel = 5;
	    }
	    /*get speakerID limit value*/
	    if (!of_property_read_u32(node, "spk_id_limit", &temp)) {
	        spk_id.spk_id_limit= temp;
	        hwlog_info("get spk_id_limit from dts:%d\n", temp);
	    } else {
	        hwlog_err("get spk_id_limit failed, set default value\n");
	        spk_id.spk_id_limit = SPEAKER_ID_LIMIT;
	    }
    }
    
    ret = misc_register(&speakerID_device);
    if (ret) {
        hwlog_err("%s: speakerID_device register failed", __FUNCTION__);
        return ret;
    }

    return ret;
}

static int speakerID_remove(struct platform_device *pdev)
{
    if(SPEAKER_ID_MODE_USE_GPIO == spk_id.check_mode) {
        gpio_free(spk_id.gpio_id);
    }

    misc_deregister(&speakerID_device);

    return 0;
}


static struct platform_driver speakerID_driver = {
    .driver = {
        .name  = SPEAKER_ID_NAME,
        .owner = THIS_MODULE,
        .of_match_table = of_match_ptr(speaker_id_match),
    },
    .probe  = speakerID_probe,
    .remove = speakerID_remove,
};

static int __init speakerID_init(void)
{
    return platform_driver_register(&speakerID_driver);
}

static void __exit speakerID_exit(void)
{
    platform_driver_unregister(&speakerID_driver);
}

module_init(speakerID_init);
module_exit(speakerID_exit);

#ifdef CONFIG_LLT_TEST
struct speakerID_static_ops speakerID_ops = {
    .adc_read = adc_read,
    .gpio_read = gpio_read,
    .speakerID_read = speakerID_read,
    .speaker_id_gpio_show = speaker_id_gpio_show,
    .get_check_mode = get_check_mode,
    .speakerID_probe = speakerID_probe,
    .speakerID_remove = speakerID_remove,
};
#endif

MODULE_DESCRIPTION("speakerID driver");
MODULE_LICENSE("GPL");