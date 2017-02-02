/*
 * devfreq_cooling: Thermal cooling device implementation for devices using
 *                  devfreq
 *
 * Copyright (C) 2014 ARM Limited
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 *
 * This program is distributed "as is" WITHOUT ANY WARRANTY of any
 * kind, whether express or implied; without even the implied warranty
 * of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#ifndef __DEVFREQ_COOLING_H__
#define __DEVFREQ_COOLING_H__

#include <linux/devfreq.h>
#include <linux/thermal.h>

#ifdef CONFIG_DEVFREQ_THERMAL

/**
 * struct devfreq_cooling_ops - Devfreq cooling power ops
 * @get_static_power: Take voltage, in mV, and return the static power in mW.
 * @get_dynamic_power: Take voltage, in mV, and frequency, in HZ, and return
 * the dynamic power draw in mW.
 */
struct devfreq_cooling_ops {
	unsigned long (*get_static_power)(unsigned long voltage);
	unsigned long (*get_dynamic_power)(unsigned long freq,
			unsigned long voltage);
};

/**
 * struct devfreq_cooling_device - Devfreq cooling device
 * @cdev:          Pointer to associated thermal cooling device.
 * @devfreq:       Pointer to associated devfreq device.
 * @cooling_state: Current cooling state.
 * @power_table:   Pointer to table with maximum power draw for each cooling
 *                 state. State is the index into the table, and the power is
 *                 stated in mW.
 * @power_ops:     Pointer to power operations, used to generate @power_table.
 * @last_status:   The devfreq status at last devfreq polling.
 */
struct devfreq_cooling_device {
	struct thermal_cooling_device *cdev;
	struct devfreq *devfreq;
	unsigned long cooling_state;
	u32 *power_table;
	struct devfreq_cooling_ops *power_ops;
	struct devfreq_dev_status last_status;
};

struct devfreq_cooling_device *
of_devfreq_cooling_register_power(struct device_node *np, struct devfreq *df,
		struct devfreq_cooling_ops *ops);
struct devfreq_cooling_device *
of_devfreq_cooling_register(struct device_node *np, struct devfreq *df);
struct devfreq_cooling_device *devfreq_cooling_register(struct devfreq *df);
void devfreq_cooling_unregister(struct devfreq_cooling_device *dfc);

#else /* !CONFIG_DEVFREQ_THERMAL */

struct devfreq_cooling_device *
of_devfreq_cooling_register_power(struct device_node *np, struct devfreq *df,
		struct devfreq_cooling_ops *ops)
{
	return NULL;
}

static inline struct devfreq_cooling_device *
of_devfreq_cooling_register(struct device_node *np, struct devfreq *df)
{
	return NULL;
}

static inline struct devfreq_cooling_device *
devfreq_cooling_register(struct devfreq *df)
{
	return NULL;
}

static inline void
devfreq_cooling_unregister(struct devfreq_cooling_device *dfc)
{
	return;
}

#endif /* CONFIG_DEVFREQ_THERMAL */
#endif /* __DEVFREQ_COOLING_H__ */
