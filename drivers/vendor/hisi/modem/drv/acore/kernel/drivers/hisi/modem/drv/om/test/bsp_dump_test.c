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

#include <linux/sched.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/slab.h>
#include <linux/thread_info.h>
#include <linux/syslog.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <asm/string.h>
#include <asm/traps.h>
#include "product_config.h"
#include "osl_types.h"
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include "bsp_dump.h"
#include "bsp_dump_drv.h"
#include "bsp_om_api.h"
#include "bsp_memmap.h"
#include "osl_malloc.h"
#include "drv_nv_def.h"

static char* g_dump_st_buffer;
static int   g_dump_st_len;
extern NV_DUMP_STRU g_dump_cfg;

enum exchS
{
    RESET,
    UNDEF,
    SWI,
    PABT,
    DABT,
    DIV,
    LOOP
};

typedef void (*FUNC_VOID)(void);

int exchRESET(void* data)
{
    FUNC_VOID a = 0;/*lint !e611 !e740*/

    
    /* coverity[var_deref_op]*/
    a();

    return 0;
}

int exchUNDEF(void* data)
{
    int b = 0;
    FUNC_VOID a = (FUNC_VOID)(&b);/*lint !e611 !e740*/

    b = 0xffffffff;
    a();

    return 0;
}

int exchSWI(void* data)
{
    msleep(20000);
 //   __asm("        SWI   0x1234   ");

    return 0;
}

int exchPABT(void* data)
{
    FUNC_VOID a = (FUNC_VOID)0xF0000000;

    a();

    return 0;
}

int exchDABT(void* data)
{
    int a;
    
    /* coverity[zero_deref] */
    a = *(int *)0x0; /* [false alarm]:fortify */       
    /* coverity[zero_deref] */
    *(int *)0x0 = 0x12345678;/* [false alarm]:fortify */

    return 0;
}

int exchLOOP(void* data)
{
    for (;;)
    {
        ;
    }
}

int exchDIV(void* a)
{
    int b = 4;
    if(!a || !((uintptr_t)a))
    {
        return -1;  
    }

    return b / (uintptr_t)a;

}

void exchTest(int type)
{
    switch (type)
    {
    case RESET:
        kthread_run(exchRESET, 0, "exchRESET");
        break;
    case UNDEF:
        kthread_run(exchUNDEF, 0, "exchUNDEF");
        break;
    case SWI:
        kthread_run(exchSWI, 0, "exchSWI");
        break;
    case PABT:
        kthread_run(exchPABT, 0, "exchPABT");
        break;
    case DABT:
        kthread_run(exchDABT, 0, "exchDABT");
        break;
    case DIV:
        kthread_run(exchDIV, 0, "exchDIV");
        break;
    case LOOP:
        {
            u32 pid;
            struct sched_param  param = {0,};
            pid = (u32)(uintptr_t)kthread_run(exchLOOP, 0, "exchLOOP");
        	if (IS_ERR((void*)(uintptr_t)pid))
        	{
        		printk("dump_init_phase2: create kthread task dump_save failed!\n");
        		return;
        	}
            
            /* coverity[unchecked_value] */
            sched_setscheduler((struct task_struct*)(uintptr_t)pid, SCHED_FIFO, &param);
        }
        break;
    default:
        break;
    }
}
/* 模式控制 EXC DUMP模式 */
int dump_st_001(void)
{
    system_error(0x72, 1, 2, 0, 0);
    return 0;
}


/* 模式控制 USB DUMP模式 */
int dump_st_002(void)
{
    system_error(0x72, 1, 2, 0, 0);
    return 0;
}

/* RESET错误 */
int dump_st_003(void)
{
//    exchTest(RESET);
    exchRESET(NULL);
    return 0;
}


/* UNDEF错误 */
int dump_st_004(void)
{
//    exchTest(UNDEF);
    exchUNDEF(NULL);
    return 0;
}


/* SWI错误 */
int dump_st_005(void)
{
    exchTest(SWI);
//    exchSWI();
    return 0;
}


/* Prefetch abort错误 */
int dump_st_006(void)
{
//    exchTest(PABT);
    exchPABT(NULL);
    return 0;
}

/* Data abort错误 */
int dump_st_007(void)
{
//    exchTest(DABT);
    exchDABT(NULL);
    return 0;
}

/* 除0错误 */
int dump_st_008(void)
{
    exchDIV(0);
    return 0;
}

/* 核心过流 */
int dump_st_009(void)
{
    return 0;
}

/* 非核心过流 */
int dump_st_010(void)
{
    return 0;
}

/* 看门狗超时错误 */
int dump_st_011(void)
{
    return 0;
}

/* A核软件异常 */
int dump_st_012_013(void)
{
    return 0;
}

/* A核软件异常之后基本信息 */
int dump_st_015_025(void)
{
    return 0;
}

/* A核用户数据 */
int dump_st_026(void)
{
    char *p;
    p = kmalloc(4096, GFP_KERNEL);
    memset(p,1,4096);
    system_error(0x88,1,2,p,4096);
    return 0;
}

void dump_st_hook(void)
{
    printk("dump_st_hook enter \n");
}

/* A核扩展数据 */
int dump_st_028(void)
{
    int ret;

    g_dump_st_buffer = bsp_dump_register_field(DUMP_AP_USB, "USB", 0, 0, 0x1000, 0);
    if(BSP_NULL == g_dump_st_buffer)
    {
        printk("get buffer failed.  test case 28 failed! \n");
        return BSP_ERROR;
    }
    g_dump_st_len = 0x1000;
    
    printk("buffer=0x%p, len=0x%x\n", g_dump_st_buffer, (s32)g_dump_st_len);

    ret = bsp_dump_register_hook("USB", (dump_hook)dump_st_hook);
    if(BSP_ERROR == ret)
    {
        printk("register_hook failed.  test case 28 failed! \n");
        return BSP_ERROR;
    }

    msleep(3000);
    system_error(0,0,0,0,0);

    return 0;
}


void dump_st_029(void)
{
    g_dump_cfg.dump_cfg.Bits.appRegSave1= 1;
    g_dump_cfg.dump_cfg.Bits.appRegSave2= 1;
    g_dump_cfg.dump_cfg.Bits.appRegSave3= 1;
    g_dump_cfg.appRegAddr1 = HI_APP_GIC_BASE_ADDR_VIRT;
    g_dump_cfg.appRegSize1 = HI_APP_GIC_SIZE;
    /*g_dump_cfg.appRegAddr2 = HI_SYSCTRL_BASE_ADDR_VIRT;*/
    /*g_dump_cfg.appRegSize2 = HI_SYSCTRL_REG_SIZE;*/
    g_dump_cfg.appRegAddr3 = HI_WDT_BASE_ADDR_VIRT;
    g_dump_cfg.appRegSize3 = HI_WDT_REG_SIZE;
}

void dump_st_030(void)
{
    dump_handle handle;

    handle = bsp_dump_register_hook("hook_test", dump_st_hook);
    if(BSP_ERROR == handle)
    {
        printk("register_hook failed. test case 30 failed! \n");
        return;        
    }

    if(BSP_OK != bsp_dump_unregister_hook(handle))
    {
        printk("unregister_hook failed. test case 30 failed! \n");
        return;       
    }
}

extern void om_get_dir(char * dir_name, DUMP_FILE_CFG_STRU * cfg, u32 type, char * dst_dir);
extern void om_save_dump_file(char * dir_name, DUMP_FILE_CFG_STRU * cfg, u32 type);
void dump_st_031(u32 cnt)
{
    DUMP_FILE_CFG_STRU  cfg;
    char temp[100];
    
    cfg.file_cnt = cnt;
    om_get_dir("/modem_log/dump/", &cfg, DUMP_MBB, temp);
}

void dump_st_032(void)
{
    DUMP_FILE_CFG_STRU  cfg;

    cfg.file_list.file_bits.mdm_dump = 0x1;
    cfg.file_list.file_bits.lphy_tcm = 0x1;                     
    cfg.file_list.file_bits.lpm3_tcm = 0x1;                     
    cfg.file_list.file_bits.ap_etb   = 0x1;                     
    cfg.file_list.file_bits.mdm_etb  = 0x1;                     
    cfg.file_cnt = 0x3;  

    om_save_dump_file("/modem_log/dump/", &cfg, DUMP_MBB);
}

/********************mdrv对外接口测试 begin***************************/
/* field注册接口测试 */
int mdrv_om_test_001(void)
{
    char * addr;

    addr = (char *)mdrv_om_register_field(DUMP_AP_REGS, "REGS", 0, 0, DUMP_REGS_SIZE, 0);
    if(addr != NULL)
    {
        printk("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* field虚拟地址获取接口测试 */
int mdrv_om_test_002(void)
{
    char * addr;

    addr = (char *)mdrv_om_get_field_addr(DUMP_AP_REGS);
    if(addr != NULL)
    {
        printk("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* field物理地址获取接口测试 */
int mdrv_om_test_003(void)
{
    char * addr;

    addr = (char *)mdrv_om_get_field_phy_addr(DUMP_AP_REGS);
    if(addr != NULL)
    {
        printk("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

dump_handle g_dump_handle_test;
void dump_hook_test(void)
{
    printk("dump hook test enter\n");
}
/* dump回调函数注册接口测试 */
int mdrv_om_test_004(void)
{
    g_dump_handle_test = mdrv_om_register_callback("DUMP_HOOK_TEST", (dump_hook)dump_hook_test);
    if(g_dump_handle_test != BSP_ERROR)
    {
        printk("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* dump回调函数去注册接口测试 */
int mdrv_om_test_005(void)
{
    s32 ret;
    ret = mdrv_om_unregister_callback(g_dump_handle_test);
    if(ret == BSP_OK)
    {
        printk("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* HDIS连接设置接口测试 */
int mdrv_om_test_006(void)
{
    mdrv_om_set_hsoflag(0);

    printk("%s pass\n", __FUNCTION__);
    return BSP_OK;
}

/* sysview配置接口测试 */
int mdrv_om_test_007(void)
{
    u32 ret;
    ret = mdrv_om_set_sysview_swt(1, 0, 3);
    if(ret == BSP_OK)
    {
        printk("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

/* sysview获取任务信息接口测试 */
int mdrv_om_test_008(void)
{
    u32 ret;
    char * data;

    data= osl_malloc(20*128);
    if(data == NULL)
    {
        printk("%s malloc fail\n", __FUNCTION__);
        return BSP_ERROR;
    }

    ret = mdrv_om_get_alltaskinfo(data, 20*128);
    if(ret == BSP_OK)
    {
        printk("%s pass\n", __FUNCTION__);
        osl_free(data);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    osl_free(data);
    return BSP_ERROR;
}

/* get root fs接口测试 */
int mdrv_om_test_009(void)
{
    s32 ret;
    char data[50];

    ret = mdrv_om_get_rootfs(data, sizeof(data));
    if(ret == BSP_OK)
    {
        printk("%s pass\n", __FUNCTION__);
        return BSP_OK;
    }

    printk("%s fail\n", __FUNCTION__);
    return BSP_ERROR;
}

extern bool g_exc_flag;
/* system_error测试 */
int mdrv_om_test_010(void)
{
    bool flag = g_exc_flag;

    g_exc_flag = true;
    mdrv_om_system_error(0xf0000, 0, 0, 0, 0);
    g_exc_flag = flag;

    printk("%s pass\n", __FUNCTION__);
    return BSP_OK;
}
/********************mdrv对外接口测试 end*****************************/


