/*
 * Copyright (C) Huawei Technologies Co., Ltd. 2012-2015. All rights reserved.
 * foss@huawei.com
 *
 * If distributed as part of the Linux kernel, the following license terms
 * apply:
 *
 * * This program is free software; you can redistribute it and/or modify
 * * it under the terms of the GNU General Public License version 2 and
 * * only version 2 as published by the Free Software Foundation.
 * *
 * * This program is distributed in the hope that it will be useful,
 * * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * * GNU General Public License for more details.
 * *
 * * You should have received a copy of the GNU General Public License
 * * along with this program; if not, write to the Free Software
 * * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, USA
 *
 * Otherwise, the following license terms apply:
 *
 * * Redistribution and use in source and binary forms, with or without
 * * modification, are permitted provided that the following conditions
 * * are met:
 * * 1) Redistributions of source code must retain the above copyright
 * *    notice, this list of conditions and the following disclaimer.
 * * 2) Redistributions in binary form must reproduce the above copyright
 * *    notice, this list of conditions and the following disclaimer in the
 * *    documentation and/or other materials provided with the distribution.
 * * 3) Neither the name of Huawei nor the names of its contributors may
 * *    be used to endorse or promote products derived from this software
 * *    without specific prior written permission.
 *
 * * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 * INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 * CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 */
/******************************************************************************
  File Name       : loadm_phone.c
  Description     : load modem image(ccore image),run in ccore
  History         :
******************************************************************************/
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/sched.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/jiffies.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <product_config.h>
#include "loadm.h"
#include <bsp_ipc.h>
#include <bsp_dsp.h>
#include <bsp_dspload.h>

#include <bsp_shared_ddr.h>
#include <mdrv.h>
#include <bsp_hardtimer.h>
#include <bsp_version.h>


/*lint --e{750,665}*/
#if 0
/*****************************************************************************
 函 数 名  : MBB平台上A核请求复位C核
 功能描述  : MBB平台上A核请求复位C核
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回OK,失败返回ERROR
 调用函数  :
 被调函数  :
*****************************************************************************/
static int his_modem_send_reset_request_mbb(void)
{
    int ret = 0;

    ret = bsp_ipc_int_send(IPC_CORE_MCORE, IPC_MCU_INT_SRC_CCPU_START);
    return ret;
}
#endif
/*****************************************************************************
 函 数 名  : 手机平台上A核通过安全OS加载modem镜像,校验成功解复位modem,校验失败返回ERROR
 功能描述  : 手机平台上A核通过安全OS首先把modem镜像加载到内存中,再来校验镜像,校验成功解复位modem,校验失败返回ERROR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回0,失败返回非0
 调用函数  :
 被调函数  :
*****************************************************************************/

static int his_load_modem_image(void)
{
    int ret = 0;
    u64 jiffies_old = 0,jiffies_new=0;
    u64 jiffies_time=0;
    BSP_CORE_TYPE_E ecoretype = BSP_CCORE;
    jiffies_old = get_jiffies_64();
    ret = bsp_reset_loadimage(ecoretype);
    jiffies_new = get_jiffies_64();
    jiffies_time =jiffies_new -jiffies_old;
    if(ret)
    {
        printk(KERN_ERR ">>load his_load_modem_image error, ret 0x%x\n", ret);
    }
    else
    {
        printk(KERN_ERR ">>load his_load_modem_image success, jiffies_time 0x%llx\n", jiffies_time);
    }
    return ret;
}

/*****************************************************************************
 函 数 名  : 正常启动时fastboot把modem镜像搬运到内存中去，modem镜像已经在内存中，A核通过安全OS,校验modem镜像,校验成功解复位modem,校验失败返回ERROR,
 功能描述  : A核通过安全OS,校验modem镜像,校验成功解复位modem,校验失败返回ERROR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回OK,失败返回ERROR
 调用函数  :
 被调函数  :
*****************************************************************************/
static int his_sec_check_modem_image(void)
{
    int ret = 0;
    u64 jiffies_old = 0,jiffies_new=0;
    u64 jiffies_time=0;
    BSP_CORE_TYPE_E ecoretype = BSP_CCORE;
    jiffies_old = get_jiffies_64();
    ret = bsp_image_seccheck(ecoretype);
    jiffies_new = get_jiffies_64();
    jiffies_time =jiffies_new -jiffies_old;
    if(ret)
    {
        printk(KERN_ERR ">>his_sec_check_modem_image error, ret 0x%x\n", ret);
    }
    else
    {
        printk(KERN_ERR ">>his_sec_check_modem_image success, jiffies_time 0x%llx\n", jiffies_time);
    }
    return ret;
}

/*****************************************************************************
 函 数 名  : 正常启动时fastboot把modem镜像搬运到内存中去，因此需要把dts dsp镜像加载并且校验最后解复位modem,
 功能描述  : A核通过安全OS,校验modem镜像,校验成功解复位modem,校验失败返回ERROR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回OK,失败返回ERROR

*****************************************************************************/
int his_load_image_start_up(void)
{
    int ret = 0;
    u64 jiffies_old = 0,jiffies_new=0;
    u64 jiffies_time=0;

    printk(KERN_ERR "his_load_image_start_up start\n");
    jiffies_old = get_jiffies_64();

#if ! defined(DRV_BUILD_SEPARATE)
    ret = his_load_cdsp_image();
	if(ret)
	{
		return -1;
	}
        
	ret = his_load_tldsp_image();
	if(ret)
	{
		return -1;
	}
#endif
    
    ret =his_sec_check_modem_image();
    if(ret)
    {
        return -1;
    }
    jiffies_new = get_jiffies_64();
    jiffies_time =jiffies_new -jiffies_old;
    printk(KERN_ERR "his_load_image_start_up end jiffies_time 0x%llx\n",jiffies_time);

    printk(KERN_ERR "his_load_image_start_up succeed, current slice %d\n", bsp_get_elapse_ms());
    return 0;
}

/*****************************************************************************
 函 数 名  : 给modem单独复位提供镜像加载接口
 功能描述  : 给modem单独复位提供镜像加载接口
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回OK,失败返回ERROR
*****************************************************************************/
int his_reset_modem_load_image(void)
{
    int ret = 0;

    ret = his_load_cdsp_image();
    if(ret)
    {
        return -1;
    }

	ret = his_load_tldsp_image();
	if(ret)
	{
		return -1;
	}

    ret = his_load_modem_image();
    if(ret)
    {
        return -1;
    }
    return ret;
}

extern int modem_rfile_init(void);
extern int modem_nv_init(void);
extern int VOS_ModuleInit(void);

DECLARE_COMPLETION(modem_sysboot_start_complete);

static int modem_sysboot_start_init(void *data)
{
    int ret;
    u64 jiffies_old = 0,jiffies_new=0;
    u64 jiffies_time=0;
    printk(KERN_ERR "modem_sysboot_start_init start\n");
    /*此任务等待被唤醒*/
    wait_for_completion(&modem_sysboot_start_complete);
    printk(KERN_ERR "modem_sysboot_start_init \n");

    if(BSP_BOARD_TYPE_SFT == bsp_get_version_info()->board_type)
    {
        ssleep(60);
    }
    
    /*如果是recovery down模式时不能解复位modem*/
    if(!bsp_need_loadmodem())
	{
        printk(KERN_ERR "upload or charge mode, will not start modem.\n");
		return 0;
	}
    printk(KERN_ERR "modem_rfile_init \n");
    ret = modem_rfile_init();
    if (ret)
    {
        printk(KERN_ERR "%s rfile init fail ",__func__);
    }
    printk(KERN_ERR "modem_nv_init \n");
    ret = modem_nv_init();
    if (ret)
    {
        printk(KERN_ERR "%s NV init fail ",__func__);
    }

#if ! defined(DRV_BUILD_SEPARATE)
    printk(KERN_ERR "VOS_ModuleInit start\n");

    jiffies_old = get_jiffies_64();
    ret = VOS_ModuleInit();
    if (ret)
    {
        printk(KERN_ERR "%s vos module init fail ",__func__);
    }
    jiffies_new  = get_jiffies_64();
    jiffies_time = jiffies_new -jiffies_old;
    printk(KERN_ERR "VOS_ModuleInit end tick 0x%llx\n",jiffies_time);
#endif

    ret = his_load_image_start_up();
    if (ret)
    {
        printk(KERN_ERR "%s his_load_image_start_up fail ",__func__);
    }

    return 0;
}



static struct platform_device his_modem_device = {
    .name = "his_modem",
    .id = 0,
    .dev = {
    .init_name = "his_modem",
    },
};


#define MODEM_SYSBOOT_START  1

static ssize_t modem_sysboot_start_store(struct device *dev, struct device_attribute *attr,
                                       const char *buf, size_t count)
{
    int status = count;
    long modem_sysboot_start = 0;

    if ((strict_strtol(buf, 10, &modem_sysboot_start) < 0))
        return -EINVAL;

    if (modem_sysboot_start == MODEM_SYSBOOT_START)
    {
        complete(&modem_sysboot_start_complete);
        printk(KERN_INFO "modem_sysboot_start write ok \n");
    }
    else
    {
        printk(KERN_ERR "modem_sysboot_start write is %x\n",(unsigned int)modem_sysboot_start);
    }
    return status;
}

static DEVICE_ATTR(modem_sysboot_start, S_IWUSR ,
                                    NULL,
                                    modem_sysboot_start_store);


static struct attribute *his_modem_attributes[] = {
        &dev_attr_modem_sysboot_start.attr,
        NULL
};

static const struct attribute_group his_modem_group = {
    .attrs = his_modem_attributes,
};

static int __init his_modem_probe(struct platform_device *pdev)
{
    int ret = 0;
    kthread_run(modem_sysboot_start_init,NULL,"modem_sysboot_start");
    ret = sysfs_create_group(&pdev->dev.kobj, &his_modem_group);
    if (0 != ret)
    {
        printk(KERN_ERR "create his modem sys node failed.\n");
        return -ENXIO;
    }
    return ret;

}

static int his_modem_resume(struct platform_device *dev)
{
    return 0;
}

static void his_modem_shutdown(struct platform_device *dev)
{
    return;
}

static int his_modem_suspend(struct platform_device *dev, pm_message_t state)
{
    return 0;
}

static int his_modem_remove(struct platform_device *dev)
{
    return 0;
}

static struct platform_driver his_modem_drv = {
    .probe      = his_modem_probe,
    .remove     = his_modem_remove,
    .suspend    = his_modem_suspend,
    .resume     = his_modem_resume,
    .shutdown   = his_modem_shutdown,
    .driver     = {
        .name     = "his_modem",
        .owner    = THIS_MODULE,
    },
};

static int __init his_modem_init_driver(void)
{
    int ret = 0;

    ret = platform_device_register(&his_modem_device);
    if(ret)
    {
        printk(KERN_ERR "register his_modem device failed\n");
        return ret;
    }

    ret = platform_driver_register(&his_modem_drv);
    if(ret)
    {
        printk(KERN_ERR "register his_modem driver failed\n");
        platform_device_unregister(&his_modem_device);
    }

    return ret;

}

static void __exit his_modem_exit_driver(void)
{
    platform_driver_unregister(&his_modem_drv);
    platform_device_unregister(&his_modem_device);
}

/* arch_initcall(his_modem_init_driver);*/
module_init(his_modem_init_driver);
module_exit(his_modem_exit_driver);

MODULE_DESCRIPTION("HIS Balong  Modem load ");
MODULE_LICENSE("GPL");

