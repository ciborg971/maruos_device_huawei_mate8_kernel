/*
 * hi6402_vad.c -- hi6402 vad driver
 *
 * Copyright (c) 2014 Hisilicon Technologies CO., Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/delay.h>
#include <linux/mutex.h>
#include <linux/notifier.h>
#include <linux/io.h>
#include <linux/irq.h>
#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/miscdevice.h>
#include <sound/soc.h>
#include <linux/wakelock.h>
#include <linux/mfd/hi6402_irq.h>
#include <hi6402_algo_interface.h>
#include <misc/hw_soundtrigger_event.h>

#define LOG_TAG "HI6402_VAD"

#define PRINT_INFO  0
#define PRINT_WARN  0
#define PRINT_DEBUG 0
#define PRINT_ERR   1

#if PRINT_INFO
#define logi(fmt, ...) printk("[" LOG_TAG "][I]" fmt "\n", ##__VA_ARGS__)
#else
#define logi(fmt, ...) ((void)0)
#endif

#if PRINT_WARN
#define logw(fmt, ...) printk("[" LOG_TAG "][W]" fmt "\n", ##__VA_ARGS__)
#else
#define logw(fmt, ...) ((void)0)
#endif

#if PRINT_DEBUG
#define logd(fmt, ...) printk("[" LOG_TAG "][D]" fmt "\n", ##__VA_ARGS__)
#else
#define logd(fmt, ...) ((void)0)
#endif

#if PRINT_ERR
#define loge(fmt, ...) printk("[" LOG_TAG "][E]" fmt "\n", ##__VA_ARGS__)
#else
#define loge(fmt, ...) ((void)0)
#endif

#define HI6402_CFG_BASE_ADDR    0x20007000

#define HI6402_DSP_VAD_CMD  (HI6402_CFG_BASE_ADDR + 0x73)

#define HI6402_REG_IRQ_1    (HI6402_CFG_BASE_ADDR + 0x15)
#define HI6402_VAD_BIT          4

#define HI6402_VAD_INT_SET  0x20003000

struct hi6402_vad_platform_data {
    struct hi6402_irq *p_irq;
    struct wake_lock soundtrigger_wake_lock;
    int irq;
};

static const struct of_device_id hi6402_vad_of_match[] = {
    {
        .compatible = "hisilicon,hi6402-vad",
    },
    { },
};
MODULE_DEVICE_TABLE(of, hi6402_vad_of_match);


static irqreturn_t hi6402_sound_trigger_handler(int irq, void *data)
{
    struct hi6402_vad_platform_data *pdata =
            (struct hi6402_vad_platform_data *)data;
    unsigned int soundtrigger_event = 0;

    BUG_ON(NULL == pdata);

    wake_lock_timeout(&pdata->soundtrigger_wake_lock, 2000);

    /* clr VAD INTR */
    hi6402_irq_write(pdata->p_irq, HI6402_VAD_INT_SET, 0);
    hi6402_irq_write(pdata->p_irq, HI6402_REG_IRQ_1, 1<<HI6402_VAD_BIT);

    soundtrigger_event = hi6402_irq_read(pdata->p_irq, HI6402_DSP_VAD_CMD);

    switch(soundtrigger_event) {
    case ST_EVENT_TRIGGER_EMY:
        hw_soundtrigger_event_uevent(soundtrigger_event);
        pr_info("soundtrigger uevent[%d].\n",ST_EVENT_TRIGGER_EMY);
        hw_soundtrigger_event_input(soundtrigger_event);
        pr_info("soundtrigger input[%d].\n",ST_EVENT_TRIGGER_EMY);
        break;
    case ST_EVENT_COMMAND_FINDPHONE:
        hw_soundtrigger_event_input(soundtrigger_event);
        break;
    case ST_EVENT_TRIGGER_OKGOOGLE:
        hw_soundtrigger_event_uevent(soundtrigger_event);
        pr_info("soundtrigger uevent[%d].\n",ST_EVENT_TRIGGER_OKGOOGLE);
        hw_soundtrigger_event_input(soundtrigger_event);
        pr_info("soundtrigger input[%d].\n",ST_EVENT_TRIGGER_OKGOOGLE);
        break;
    default:
        hw_soundtrigger_event_input(soundtrigger_event);
        break;
    }

    return IRQ_HANDLED;
}

static int hi6402_vad_probe(struct platform_device *pdev)
{
    struct device *dev = &pdev->dev;
    struct hi6402_vad_platform_data *pdata = NULL;
    const struct of_device_id *match = NULL;
    int ret = 0;

    dev_info(dev, "%s enter\n",__FUNCTION__);

    pdata = devm_kzalloc(dev, sizeof(*pdata), GFP_KERNEL);
    if (NULL == pdata) {
        dev_err(dev, "cannot allocate hisi 6402 vad platform data\n");
        return -ENOMEM;
    }

    match = of_match_device(hi6402_vad_of_match, dev);
    if (!match) {
        pr_err("get device info err\n");
        return -ENOENT;
    }

    pdata->p_irq = dev_get_drvdata(pdev->dev.parent);
    if (!pdata->p_irq) {
        dev_err(dev, "get parend device error\n");
        return -ENOENT;
    }

    pdata->irq = platform_get_irq_byname(pdev, "vad");
    if (0 > pdata->irq) {
        pr_err("get sound triger error");
        return -ENOENT;
    }

    wake_lock_init(&pdata->soundtrigger_wake_lock, WAKE_LOCK_SUSPEND, "hisi-6402-soundtrigger");

    /* irq request : sound triger */
    ret = devm_request_threaded_irq(dev, pdata->irq, NULL,
                    hi6402_sound_trigger_handler,
                    IRQF_NO_SUSPEND | IRQF_ONESHOT,
                    "sound_triger", pdata);
    if (0 > ret) {
        pr_err("request irq for sound triger err\n");
    }

    pr_info("%s : hi6402 vad probe ok \n", __FUNCTION__);

    return ret;
}

static int hi6402_vad_remove(struct platform_device *pdev)
{
    struct hi6402_vad_platform_data *pdata = platform_get_drvdata(pdev);

    wake_lock_destroy(&pdata->soundtrigger_wake_lock);

    return 0;
}

static struct platform_driver hi6402_vad_driver = {
    .driver = {
        .name   = "hi6402_vad",
        .owner  = THIS_MODULE,
        .of_match_table = hi6402_vad_of_match,
    },
    .probe  = hi6402_vad_probe,
    .remove = hi6402_vad_remove,
};

static int __init hi6402_vad_init(void)
{
    pr_info("%s : hi6402 vad init ok \n", __FUNCTION__);
    return platform_driver_register(&hi6402_vad_driver);
}

static void __exit hi6402_vad_exit(void)
{
    platform_driver_unregister(&hi6402_vad_driver);
}

device_initcall(hi6402_vad_init);
module_exit(hi6402_vad_exit);

MODULE_DESCRIPTION("hi6402_vad driver");
MODULE_LICENSE("GPL");
