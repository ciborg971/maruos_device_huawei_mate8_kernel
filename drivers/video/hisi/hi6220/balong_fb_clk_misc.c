/*
 * Hisilicon Balong Hi6620 SOC clock driver
 *
 * Copyright (c) 2013-2014 Hisilicon Limited.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along
 * with this program; if not, write to the Free Software Foundation, Inc.,
 * 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 */

#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>
#include <linux/fb.h>
#include <linux/clk.h>
#include <trace/trace_kernel.h>
#include <linux/clk-provider.h>

#include "balong_fb.h"

struct misc_clk_list
{
      struct clk     *noc_clk;
      struct clk     *media_sc_clk;
};
static struct misc_clk_list clk_list;

struct platform_device *clk_misc_platform_device = NULL;


static int clk_misc_probe(struct platform_device *pdev)
{
    if (NULL == pdev) {
        balongfb_loge("clk_misc_probe(): pdev is null.");
        return -EEXIST;
    }

    if (NULL != clk_misc_platform_device) {
        balongfb_loge("clk_misc_probe(): clk_misc alreay on.");
        return -EEXIST;
    }

    clk_list.noc_clk = clk_get(&pdev->dev,"clk_ade_core_src");
    if (IS_ERR(clk_list.noc_clk))
    {
        balongfb_loge("clk_misc_probe(): faile to get noc_clk.");
        return -ENODEV;
    }

    clk_list.media_sc_clk = clk_get(&pdev->dev,"pclk_codec_vpu_src");
    if (IS_ERR(clk_list.media_sc_clk))
    {
        balongfb_loge("clk_misc_probe(): faile to get media_sc_clk.");
        return -ENODEV;
    }

    if(0 != clk_prepare_enable(clk_list.noc_clk)) {
        balongfb_loge("fail to clk_prepare_enable noc_clk\n");
    }

    if(0 != clk_prepare_enable(clk_list.media_sc_clk)) {
        balongfb_loge("fail to clk_prepare_enable media_sc_clk\n");
    }

    clk_misc_platform_device = pdev;

    return 0;
}

static int clk_misc_remove(struct platform_device *pdev)
{
    /* put and disable core clock */
    if (!IS_ERR(clk_list.noc_clk)) {
        clk_disable_unprepare(clk_list.noc_clk);
        clk_put(clk_list.noc_clk);
    }

    /* put and disable pclk */
    if (!IS_ERR(clk_list.media_sc_clk)) {
        clk_disable_unprepare(clk_list.media_sc_clk);
        clk_put(clk_list.media_sc_clk);
    }

    return 0;
}

static const struct of_device_id clk_misc_match[] = {
    {
        .compatible = "hisilicon,clk_misc",
        .data = NULL,
    },
    {},
};

static struct platform_driver clk_misc_platform_driver = {
    .probe  = clk_misc_probe,
    .remove = clk_misc_remove,
    .driver = {
        .name    = "clk_misc",
        .of_match_table = clk_misc_match,
    },
};

int __init clk_misc_earlyinit(void)
{
    int err = 0;

    err = platform_driver_register(&clk_misc_platform_driver);
        pr_err("clk_misc_earlyinit platform_driver_register\n");

    if (0 != err) {
        balongfb_loge("clk_misc_earlyinit() Failed to register driver (%d)\n", err);
        clk_misc_platform_device = NULL;
        return err;
    }

    return 0; /* Success */
}

int __init clk_misc_lateinit(void)
{
    if(clk_misc_platform_device)
    {
        clk_misc_remove(clk_misc_platform_device);
    }
    return 0;
}

arch_initcall(clk_misc_earlyinit);
late_initcall(clk_misc_lateinit);

