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

/*lint --e{537} */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/mtd/mtd.h>
#include <linux/platform_device.h>
#include <linux/io.h>
#include <linux/err.h>
#include <linux/slab.h>
#include <linux/vmalloc.h>
#include <linux/jiffies.h>
#include <mdrv.h>

#include <linux/of.h>
#include <linux/of_address.h>

#include <product_config.h>

#include <hi_dsp.h>
#include <hi_onoff.h>
#include <ptable_com.h>

#include <bsp_om.h>
#include <bsp_dsp.h>
#include <bsp_sec.h>
#include <bsp_sram.h>
#include <bsp_nandc.h>
#include <bsp_shared_ddr.h>
#include <bsp_dspload.h>
#include <bsp_sysctrl.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifdef CONFIG_CBBE

#ifdef CONFIG_HISI_BALONG_MODEM

/*****************************************************************************
 函 数 名  : 手机平台上A核通过安全OS加载dsp镜像,校验成功返回OK,校验失败返回ERROR
 功能描述  : 手机平台上A核通过安全OS加载dsp镜像,校验成功返回OK,校验失败返回ERROR
 输入参数  : 无
 输出参数  : 无
 返 回 值  : 成功返回OK,失败返回ERROR
 调用函数  :
 被调函数  :
*****************************************************************************/
int his_load_cdsp_image(void)
{
    int ret = 0;
    u64 jiffies_old = 0,jiffies_new=0;
    u64 jiffies_time=0;
    BSP_CORE_TYPE_E ecoretype = BSP_CDSP;
    jiffies_old = get_jiffies_64();
    ret = bsp_reset_loadimage(ecoretype);
    jiffies_new = get_jiffies_64();
    jiffies_time =jiffies_new -jiffies_old;
    if(ret)
    {
        printk(KERN_ERR ">>load his_load_cdsp_image error, ret 0x%x\n", ret);
    }
    else
    {
        printk(KERN_ERR ">>load his_load_cdsp_image success, jiffies_time 0x%llx\n", jiffies_time);
		 /* set the ok flag of dsp image */
        writel(DSPLOAD_MAGIC, (void*)(SHM_BASE_ADDR + SHM_OFFSET_CDSP_FLAG));      
    }
    return ret;
}

#else
//dallas porintg平台xdsp加载
static int dsp_balong_load_image(char* part_name)
{
    int ret = 0;
    u32 skip_len = 0;
    u32 len = 0;
    u32 i;
    void *bbe_ddr_addr = NULL;
    struct dsp_bin_header_stru header;
    struct dsp_bin_header_stru *pheader;

    /* 指向一块DDR   空间用于存放镜像和配置数据 */
    bbe_ddr_addr = (void*)ioremap_nocache(DDR_CBBE_IMAGE_ADDR, DDR_CBBE_IMAGE_SIZE);
    if (NULL == bbe_ddr_addr)
    {
        printk("fail to io remap, %d \r\n", __LINE__);
        ret = -ENOMEM;
        goto err_unmap;
    }

    /* clean ok flag */
    //*(u32*)bbe_ddr_addr = 0;

    if (NAND_OK == bsp_nand_read(part_name, 0, &header, sizeof(struct dsp_bin_header_stru), &skip_len))
    {
        len = header.ulFileSize;
    }
    else
    {
        printk("[dsp] fail to load cbbe16 image\r\n");
        ret = NAND_ERROR;
        goto err_unmap;
    }

	/* 判断是否找到X模DSP镜像 */
	if (memcmp(header.acDescription, "BBE", strlen("BBE")))
	{
		printk("cbbe16 image not found .\r\n");
		ret = NAND_ERROR;
		goto err_unmap;
	}

    if(len > DDR_CBBE_IMAGE_SIZE)
    {
        printk("[dsp]*******************************************************************\n");
        printk("[dsp]CBBE_IMG_SIZE, size: 0x%x, DDR_CBBE_IMAGE_SIZE, size: 0x%x.\n",
            len, DDR_CBBE_IMAGE_SIZE);
        printk("[dsp]CBBE_IMG_SIZE is bigger than DDR_CBBE_IMAGE_SIZE.\n");
        printk("[dsp]Load cdsp from flash to ddr failed.\n");
        printk("[dsp]********************************************************************\n");
        goto err_unmap; 
    }

    if (NAND_OK == bsp_nand_read(part_name, 0, bbe_ddr_addr, len, &skip_len))
    {
        pheader = bbe_ddr_addr;

        for(i = 0; i < pheader->ulSectNum; i++)
        {
            if((pheader->astSect[i].ulFileOffset > pheader->ulFileSize)
                || ((pheader->astSect[i].ulFileOffset + pheader->astSect[i].ulSectSize) > pheader->ulFileSize))
            {
                printk("[dsp] image error: i %d, offset %d, size %d, file size %d.\r\n",
                    i, pheader->astSect[i].ulFileOffset, pheader->astSect[i].ulSectSize, pheader->ulFileSize);
                
                ret = NAND_ERROR;
                goto err_unmap;
            }
        }
    }
    else
    {
        printk("[dsp] fail to load cbbe16 image\r\n");
        ret = NAND_ERROR;
        goto err_unmap;
    }

    /* set ok flag */
    //*(u32*)bbe_ddr_addr = DSPLOAD_MAGIC;
    writel(DSPLOAD_MAGIC, (void*)(SHM_BASE_ADDR + SHM_OFFSET_CDSP_FLAG));

err_unmap:
    if (NULL != bbe_ddr_addr)
        iounmap(bbe_ddr_addr);

    return ret;
}


int __init dsp_balong_probe(struct platform_device *pdev)
{
    int ret = 0;

    struct ST_PART_TBL* dsp_part = NULL;
    /* 通过模块名来查找相应模块的镜像 */
    dsp_part = find_partition_by_name(PTABLE_CBBE_NM);
    if(NULL == dsp_part)
    {
        printk("[dsp] balong load dsp image succeed\r\n");
        ret = -EAGAIN;
        goto err_no_part;
    }
    /* 通过镜像名来加载dsp  镜像 */
    ret = dsp_balong_load_image(dsp_part->name);
    if(ret != 0)
    {
        printk("[dsp] dsp_balong_load_image fail.\r\n");
        ret = -EAGAIN;
        goto err_no_part;
    }
    
    printk(KERN_ERR"[dsp] dsp_balong_probe load cbbe16 succeed.\r\n");

err_no_part:

    return ret;
}

static struct platform_device dsp_balong_device = {
    .name = "dsp_balong",
    .id = 0,
    .dev = {
    .init_name = "dsp_balong",
    },
};

static struct platform_driver dsp_balong_drv = {
    .probe      = dsp_balong_probe,
    .driver     = {
        .name     = "dsp_balong",
        .owner    = THIS_MODULE,
    },
};

static int dsp_balong_acore_init(void);
static void dsp_balong_acore_exit(void);

static int __init dsp_balong_acore_init(void)
{
    int ret = 0;

    ret = platform_device_register(&dsp_balong_device);
    if(ret)
    {
        printk("register his_modem device failed\r\n");
        return ret;
    }

    ret = platform_driver_register(&dsp_balong_drv);
    if(ret)
    {
        printk("register his_modem driver failed\r\n");
        platform_device_unregister(&dsp_balong_device);
    }

    return ret;
}

static void __exit dsp_balong_acore_exit(void)
{
    platform_driver_unregister(&dsp_balong_drv);
    platform_device_unregister(&dsp_balong_device);
}

module_init(dsp_balong_acore_init);
module_exit(dsp_balong_acore_exit);

MODULE_AUTHOR("cuijunqiang@huawei.com");
MODULE_DESCRIPTION("HIS Balong DSP load");
MODULE_LICENSE("GPL");
#endif

#endif

#ifdef __cplusplus
}
#endif

