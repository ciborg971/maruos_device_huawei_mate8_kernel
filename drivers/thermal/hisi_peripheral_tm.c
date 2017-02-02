/*
 * Copyright (c) 2011-2012, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

/*
 * Qualcomm PMIC hisi_peripheral Thermal Manager driver
 */

#define pr_fmt(fmt) "%s: " fmt, __func__

#include <linux/module.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/mutex.h>
#include <linux/interrupt.h>
#include <linux/platform_device.h>
#include <linux/completion.h>
#include "hisi_peripheral_tm.h"
#include <linux/of.h>
#include <linux/device.h>

#define PM_TM_DEV_NAME	"hisi_peripheral_tm"
static struct hisi_peripheral_tm_chip *gtm_dev;

enum hisi_peripheral_temp_chanel {
	DETECT_SYSTEM_H_CHANEL = 0,
	DETECT_FLASH_LED_CHANEL,
	DETECT_CHARGER_CHANEL,
	DETECT_PA_0_CHANEL,
	DETECT_PA_1_CHANEL,
	DETECT_DCXO0_CHANEL,
	DETECT_SHELL_CHANEL,
	DETECT_BATTERY_CHANEL
};

char *hisi_peripheral_chanel[] = {
	[DETECT_SYSTEM_H_CHANEL]		= "system_h",
	[DETECT_FLASH_LED_CHANEL]		= "flash_led",
	[DETECT_CHARGER_CHANEL]	= "charger",
	[DETECT_PA_0_CHANEL]		= "pa_0",
	[DETECT_PA_1_CHANEL]		= "pa_1",
	[DETECT_DCXO0_CHANEL]		= "dcxo0",
	[DETECT_SHELL_CHANEL]		= "shell",
	[DETECT_BATTERY_CHANEL]		= "Battery",
};

#define TSENSOR_USED_NUM		5
#define BOARD_BUFFER_LENGTH		40
extern int hisi_peripheral_get_temp(struct periph_tsens_tm_device_sensor *chip, unsigned long *temp);
static int hisi_peripheral_tm_get_temp(struct thermal_zone_device *thermal,
				      unsigned long *temp)
{
	struct periph_tsens_tm_device_sensor *chip = thermal->devdata;
	int ret;
	if (!chip || !temp)
		return -EINVAL;
	*temp = 0;

	ret = hisi_peripheral_get_temp(chip, temp);
	if (ret < 0) {
		pr_err("%s,get temp failed\n\r", __func__);
		return ret;
	}

	return 0;
}

static int hisi_peripheral_tm_get_mode(struct thermal_zone_device *thermal,
			      enum thermal_device_mode *mode)
{
	struct periph_tsens_tm_device_sensor *chip = thermal->devdata;

	if (!chip || !mode)
		return -EINVAL;

	*mode = chip->mode;

	return 0;
}

static struct thermal_zone_device_ops hisi_peripheral_thermal_zone_ops = {
	.get_temp = hisi_peripheral_tm_get_temp,
	.get_mode = hisi_peripheral_tm_get_mode,
};

static int get_equipment_tree_data(struct platform_device *pdev, int sensor_num)
{
	struct device_node *of_node = pdev->dev.of_node;
	struct device *dev = &pdev->dev;
	int equipment_chanel_value = 0;
	const char *equipment_chanel_ntc_name, *equipment_chanel_ntc_state;
	int i, rc, j;
	char temp_buffer[BOARD_BUFFER_LENGTH];

	/*get detect equipment thermal HKADC chanel, name and state*/
	for (i = DETECT_SYSTEM_H_CHANEL, j = DETECT_SYSTEM_H_CHANEL; i < sensor_num; i++, j++) {
		memset((void*)temp_buffer, 0, sizeof(temp_buffer));
		snprintf(temp_buffer, sizeof(temp_buffer), "hisi,detect_%s_tm_chanel", hisi_peripheral_chanel[i]);
		rc = of_property_read_u32(of_node, temp_buffer, &equipment_chanel_value);
		if (rc) {
			dev_err(&pdev->dev, "canot get %d tm chanel\n", i);
			rc = -ENODEV;
			goto read_chanel_fail;
		}
		gtm_dev->sensor[i].chanel = equipment_chanel_value;

		memset((void*)temp_buffer, 0, sizeof(temp_buffer));
		snprintf(temp_buffer, sizeof(temp_buffer), "hisi,detect_%s_tm_state", hisi_peripheral_chanel[i]);
		rc = of_property_read_string(of_node, temp_buffer, &equipment_chanel_ntc_state);
		if (rc) {
			dev_err(dev, "detect %d tm ntc state failed\n", i);
			rc = -EINVAL;
			goto read_state_fail;
		}
		if (strcmp(equipment_chanel_ntc_state, "enable") == 0) {
			gtm_dev->sensor[i].state = 1;
		} else if (strcmp(equipment_chanel_ntc_state, "disable") == 0) {
			gtm_dev->sensor[i].state = 0;
		} else {
			dev_err(dev, "input  ntc %d state is error\n\r", i);
			rc = -EINVAL;
			goto read_state_fail;
		}

		memset(temp_buffer, 0, sizeof(temp_buffer));
		snprintf(temp_buffer, sizeof(temp_buffer), "hisi,detect_%s_tm_ntc", hisi_peripheral_chanel[i]);
		rc = of_property_read_string(of_node, temp_buffer, &equipment_chanel_ntc_name);
		if (rc) {
			dev_err(dev, "detect %d tm ntc name failed\n", i);
			rc = -EINVAL;
			goto read_name_fail;
		}

		gtm_dev->sensor[i].ntc_name = (const char *)kmemdup((const void *)equipment_chanel_ntc_name, strlen(equipment_chanel_ntc_name) + 1, GFP_KERNEL);
		if (!gtm_dev->sensor[i].ntc_name) {
			dev_err(dev, "application %d chanel ntc name room failing\n", i);
			rc = -EINVAL;
			goto kmalloc_fail;
		}
	}

	return 0;

kmalloc_fail:
read_name_fail:
read_state_fail:
read_chanel_fail:
	for (i = DETECT_SYSTEM_H_CHANEL; i < j; i++) {
		kfree(gtm_dev->sensor[i].ntc_name);
	}

	return rc;
}
static int get_periph_tm_device_tree_data(struct platform_device *pdev)
{
	const struct device_node *of_node = pdev->dev.of_node;
	u32 rc = 0, periph_tsens_num_sensors = 0;

	rc = of_property_read_u32(of_node,
			"hisi,peripheral_sensors", &periph_tsens_num_sensors);
	if (rc) {
		dev_err(&pdev->dev, "missing sensor number\n");
		return -ENODEV;
	}

	gtm_dev = devm_kzalloc(&pdev->dev, sizeof(struct hisi_peripheral_tm_chip) +
			periph_tsens_num_sensors * sizeof(struct periph_tsens_tm_device_sensor), GFP_KERNEL);
	if (gtm_dev == NULL) {
		pr_err("%s: kzalloc() failed.\n", __func__);
		return -ENOMEM;
	}

	gtm_dev->tsens_num_sensor = periph_tsens_num_sensors;
	rc = get_equipment_tree_data(pdev, periph_tsens_num_sensors);
	if (rc) {
		dev_err(&pdev->dev, "get periph equipment dts data error\n");
		return -ENODEV;
	}

	return rc;
}

static struct platform_driver hisi_peripheral_tm_driver;

static int hisi_peripheral_tm_probe(struct platform_device *pdev)
{
	int rc = 0;
	char name[BOARD_BUFFER_LENGTH];
	int i, flag;

	if (pdev->dev.of_node) {
		rc = get_periph_tm_device_tree_data(pdev);
		if (rc) {
			dev_err(&pdev->dev, "Error reading peripheral tm \n");
			return rc;
		}
	} else
		return -ENODEV;

	gtm_dev->pdev = pdev;

	for (i = DETECT_SYSTEM_H_CHANEL, flag = DETECT_SYSTEM_H_CHANEL; i < (gtm_dev->tsens_num_sensor + DETECT_SYSTEM_H_CHANEL); i++) {
		if (gtm_dev->sensor[i].state == 0)
			continue;

		memset((void*)name,0,sizeof(name));
		snprintf(name, sizeof(name),"%s", hisi_peripheral_chanel[i]);

		gtm_dev->sensor[i].mode = THERMAL_DEVICE_ENABLED;
		gtm_dev->sensor[i].sensor_num = (i + TSENSOR_USED_NUM);
		gtm_dev->sensor[i].tz_dev = thermal_zone_device_register(name,
				0, 0, &gtm_dev->sensor[i],
				&hisi_peripheral_thermal_zone_ops, NULL, 0, 0);
		flag++;
		if (IS_ERR(gtm_dev->sensor[i].tz_dev)) {
			dev_err(&pdev->dev, "thermal_zone_device_register() failed.\n");
			rc = -ENODEV;
			goto fail;
		}
	}

	platform_set_drvdata(pdev, gtm_dev);
	return 0;
fail:
	for (i = DETECT_SYSTEM_H_CHANEL; i < flag; i++) {
		thermal_zone_device_unregister(gtm_dev->sensor[i].tz_dev);
	}

	return rc;
}

static int hisi_peripheral_tm_remove(struct platform_device *pdev)
{
	struct hisi_peripheral_tm_chip *chip = platform_get_drvdata(pdev);
	int i;

	if (chip) {
		platform_set_drvdata(pdev, NULL);
		for (i = DETECT_SYSTEM_H_CHANEL; i < (gtm_dev->tsens_num_sensor + DETECT_SYSTEM_H_CHANEL); i++) {
			kfree(gtm_dev->sensor[i].ntc_name);
			thermal_zone_device_unregister(gtm_dev->sensor[i].tz_dev);
		}
		kfree(chip);
	}
	return 0;
}

static struct of_device_id hisi_peripheral_tm_match[] = {
	{	.compatible = "hisi,hisi-peripheral-tm",
	},
	{}
};

static struct platform_driver hisi_peripheral_tm_driver = {
	.probe	= hisi_peripheral_tm_probe,
	.remove	= hisi_peripheral_tm_remove,
	.driver	= {
		.name = PM_TM_DEV_NAME,
		.owner = THIS_MODULE,
		.of_match_table = hisi_peripheral_tm_match,
	},
};

static int __init hisi_peripheral_tm_init(void)
{
	return platform_driver_register(&hisi_peripheral_tm_driver);
}

static void __exit hisi_peripheral_tm_exit(void)
{
	platform_driver_unregister(&hisi_peripheral_tm_driver);
}

module_init(hisi_peripheral_tm_init);
module_exit(hisi_peripheral_tm_exit);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("PM Thermal Manager driver");
MODULE_VERSION("1.0");
MODULE_ALIAS("platform:" PM_TM_DEV_NAME);
