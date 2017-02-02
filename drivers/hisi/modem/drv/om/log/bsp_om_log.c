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

/*****************************************************************************
  1 头文件包含
*****************************************************************************/
/*lint -save -e322 -e7 -e537 */
#include "bsp_om_api.h"
#include "bsp_om_log.h"
#include "bsp_om.h"
#include "bsp_socp.h"
#include <linux/kernel.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/semaphore.h>
#include <linux/fs.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/kthread.h>
#include "osl_sem.h"
#include "bsp_dump_drv.h"
#include "bsp_dump.h"
#include "bsp_ipc.h"
#include "bsp_hardtimer.h"
/*lint -restore*/
#if 0
/*lint --e{750}*/
#define    THIS_MODU_ID        BSP_MODU_LOG
/*lint -restore */
#endif

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
bsp_log_swt_cfg_s  g_mod_peint_level_info[BSP_MODU_MAX]    =
{
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR},
    {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}, {BSP_LOG_LEVEL_ERROR}
};

u32 bsp_log_level_set(bsp_log_level_e log_level);
void bsp_log_show(void);



/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*****************************************************************************
* 函 数 名  : bsp_log_module_cfg_get
*
* 功能描述  : 查询模块当前设置的打印级别
*
* 输入参数  : mod_id:被查询模块ID
*
* 输出参数  : 无
*
* 返 回 值  : 打印级别
*****************************************************************************/

u32 bsp_log_module_cfg_get(bsp_module_e mod_id)
{
    if(mod_id >= BSP_MODU_MAX )
    {
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    return g_mod_peint_level_info[mod_id].print_level;
}

/*****************************************************************************
* 函 数 名  : bsp_mod_level_set
*
* 功能描述  : 设置单个模块的打印级别
*
* 输入参数  : mod_id:模块ID
*                         print_level: 打印级别
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 设置成功，其他  设置失败
*****************************************************************************/

u32 bsp_mod_level_set(bsp_module_e  mod_id ,u32 print_level)
{
    if(mod_id >= BSP_MODU_MAX )
    {
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    if(print_level >BSP_LOG_LEVEL_MAX)
    {
        return BSP_ERR_LOG_INVALID_LEVEL;
    }

    g_mod_peint_level_info[mod_id].print_level = print_level;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : bsp_log_level_set
*
* 功能描述  : 设置所有模块的打印级别
*
* 输入参数  : print_level: 打印级别
*
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 设置成功，其他  设置失败
*****************************************************************************/

u32 bsp_log_level_set(bsp_log_level_e log_level)
{
    u32 mod_id = 0;

    if(log_level > BSP_LOG_LEVEL_MAX)
    {
        return BSP_ERR_LOG_INVALID_LEVEL;
    }

    for(mod_id = 0; mod_id < BSP_MODU_MAX; mod_id++)
    {
        g_mod_peint_level_info[mod_id].print_level = log_level;
    }

    return BSP_OK;
}


/*****************************************************************************
* 函 数 名  : bsp_log_level_reset
*
* 功能描述  : 将所有模块的打印级别设置为默认值
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/

void bsp_log_level_reset(void)
{
    u32 i;

    for(i = 0; i < BSP_MODU_MAX;i++)
    {
        g_mod_peint_level_info[i].print_level= BSP_LOG_LEVEL_ERROR;
    }

}

/*****************************************************************************
* 函 数 名  : bsp_trace
*
* 功能描述  : 底软打印输出处理接口
*
* 输入参数  :  mod_id: 输出模块
*                           print_level: 打印级别
*                           fmt :打印输入参数
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/

void bsp_trace(bsp_log_level_e log_level,bsp_module_e mod_id,char *fmt,...)
{
    char    bsp_print_buffer[BSP_PRINT_BUF_LEN] ;
    va_list arglist;

    /*打印级别过滤*/
    if(mod_id >= BSP_MODU_MAX )
    {
        return ;
    }

    if(g_mod_peint_level_info[mod_id].print_level > log_level )
    {
        return ;
    }

    /*lint -save -e530*/
    va_start(arglist, fmt);
    /*lint -restore +e530*/
    vsnprintf(bsp_print_buffer, BSP_PRINT_BUF_LEN, fmt, arglist); /* [false alarm]:屏蔽Fortify错误 */
    va_end(arglist);

    bsp_print_buffer[BSP_PRINT_BUF_LEN - 1] = '\0';

    printk(KERN_ERR"%s", bsp_print_buffer);

    return ;
}
EXPORT_SYMBOL_GPL(bsp_trace);

#ifdef ENABLE_BUILD_OM
/*****************************************************************************
* 函 数 名  : bsp_log_module_cfg_set
*
* 功能描述  : HSO设置底软打印级别处理函数
*
* 输入参数  : log_swt_stru:各个模块的打印级别值
*                         data_len:      参数log_swt_stru的长度
* 输出参数  : 无
*
* 返 回 值  : BSP_OK 成功;其他 失败
*****************************************************************************/

u32 bsp_log_module_cfg_set(bsp_log_swt_cfg_s *log_swt_stru ,u32 data_len)
{
    u32 mod_num = 0;
    u32 i;

    if((NULL == log_swt_stru )||( 0 == data_len)||((data_len % sizeof(bsp_log_swt_cfg_s) != 0)))
    {
        bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set error!!  data_len = %d\n",data_len);
       return BSP_ERR_LOG_INVALID_PARAM;
    }

    mod_num = data_len / sizeof(bsp_log_swt_cfg_s);

    if(mod_num > BSP_MODU_MAX )
    {
        bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set error!!  mod_num = %d\n",mod_num);
        return BSP_ERR_LOG_INVALID_MODULE;
    }

    for(i = 0; i < mod_num; i++)
    {
        if(log_swt_stru[i].print_level <= BSP_LOG_LEVEL_MAX)
        {
            g_mod_peint_level_info[i].print_level = log_swt_stru[i].print_level;

        }
        else
        {
            bsp_om_debug(BSP_LOG_LEVEL_ERROR," bsp_log_module_cfg_set   log_swt_stru[i].print_level = %d\n",log_swt_stru[i].print_level);
            return BSP_ERR_LOG_INVALID_LEVEL ;
        }

    }

    return BSP_OK;
}




/*debug 接口*/
void bsp_log_show(void)
{
    printk("trace level              = %d\n",g_mod_peint_level_info[0].print_level);
}

struct semaphore g_st_log_sem;
static LIST_HEAD(kernel_log_list);

void log_buff_info(void)
{
    log_mem_stru * log = NULL;
    log_mem_stru * m3_log = NULL;

    log    = (log_mem_stru *)bsp_dump_get_field_addr(DUMP_CP_DMESG);
    m3_log = (log_mem_stru *)bsp_dump_get_field_addr(DUMP_M3_LOG);
    if(log != NULL)
    {
        printk("CCORE DMESG ADDR: %p\n",   log);
        printk("BUFFER MAGIC    : 0x%x\n", log->magic);
        printk("READ POINTER    : 0x%x\n", log->log_read);
        printk("WRITE POINTER   : 0x%x\n", log->log_write);
        printk("BUFFER LENGTH   : 0x%x\n", log->log_buf_len);
        printk("FULL FLAG       : 0x%x\n", log->full_flag);
    }

    if(m3_log != NULL)
    {
        printk("M3 LOG ADDR     : %p\n",   m3_log);
        printk("BUFFER MAGIC    : 0x%x\n", m3_log->magic);
        printk("READ POINTER    : 0x%x\n", m3_log->log_read);
        printk("WRITE POINTER   : 0x%x\n", m3_log->log_write);
        printk("BUFFER LENGTH   : 0x%x\n", m3_log->log_buf_len);
        printk("FULL FLAG       : 0x%x\n", m3_log->full_flag);
    }
}

/*****************************************************************************
* 函 数 名  : log_buff_init
*
* 功能描述  : 初始化log设备buffer, 核间同步, C核、M核初始化可能晚于log_init
*
* 输入参数  : logger_info_stru * log_info
*
* 输出参数  : 无
*
* 返 回 值  : 0 --- 成功，非0 --- 失败
*****************************************************************************/
int log_buff_init(logger_info_stru * log_info)
{
    DUMP_SAVE_MOD_ENUM mod_id;
    u8 * addr = NULL;

    if(!strncmp(log_info->misc.name, CCORE_LOG_DEV_NAME, sizeof(CCORE_LOG_DEV_NAME)))
    {
        mod_id = DUMP_CP_DMESG;
    }
    else if(!strncmp(log_info->misc.name, MCORE_LOG_DEV_NAME, sizeof(MCORE_LOG_DEV_NAME)))
    {
        mod_id = DUMP_M3_LOG;
    }
    else
    {
        /* invalid mod id */
        mod_id = DUMP_AP_FIELD_END;
    }

    addr = bsp_dump_get_field_addr(mod_id);
    if(addr == NULL)
    {
        return BSP_ERROR;
    }

    log_info->log_mem = (log_mem_stru *)addr;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : log_task_func
*
* 功能描述  : log task，定时唤醒因无数据进入睡眠的应用
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  :
*****************************************************************************/
int log_task_func(void * data)
{
    logger_info_stru * log_info;
    unsigned long lock_flag;
    u32 sleep_flag;

    while(1)
    {
        if(0 != down_timeout(&g_st_log_sem, LOG_TASK_SCHED_TIME))
        {
            /* do nothing */
        }

        list_for_each_entry(log_info, &kernel_log_list, logs)
        {
            /* 如果设备log buffer没有初始化，先做初始化 */
            if(log_info->log_mem == NULL)
            {
                if(BSP_OK != log_buff_init(log_info))
                {
                    continue;
                }
            }

            if(log_info->in_use == BSP_FALSE)
            {
                continue;
            }
            spin_lock_irqsave(&log_info->lock, lock_flag);
            sleep_flag = log_info->sleep_flag;
            spin_unlock_irqrestore(&log_info->lock, lock_flag);

            /* 无数据或者应用正在读取数据，查询下一个设备 */
            if((sleep_flag == BSP_FALSE) || (log_info->log_mem->log_read == log_info->log_mem->log_write))
            {
                continue;
            }

            spin_lock_irqsave(&log_info->lock, lock_flag);
            log_info->sleep_flag = BSP_FALSE;
            spin_unlock_irqrestore(&log_info->lock, lock_flag);
            /* 唤醒应用 */
            wake_up_interruptible(&log_info->wq);
        }
    }

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : get_log_from_minor
*
* 功能描述  : 获取log设备指针
*
* 输入参数  :  int minor，次设备号
*
* 输出参数  : 无
*
* 返 回 值  : logger_info_stru *
*****************************************************************************/
logger_info_stru * get_log_from_minor(int minor)
{
    logger_info_stru * log;

    list_for_each_entry(log, &kernel_log_list, logs)
    {
        if (log->misc.minor == minor)
        {
            return log;
        }
    }

    return NULL;
}

/*****************************************************************************
* 函 数 名  : do_read_data_to_user
*
* 功能描述  : 拷贝数据至用户态
*
* 输入参数  : char * src, 数据源buffer
*             char * dst，数据目的buffer
*             u32 len, 期望读取的数据长度
*
* 输出参数  : 无
*
* 返 回 值  : 实际读取的数据长度
*****************************************************************************/
int do_read_data_to_user(char * src, char * dst, u32 len)
{
    u32 ret;

    /* 返回未能拷贝的数据长度 */
    ret = (u32)copy_to_user(dst, src, len);

    return (int)(len - ret);
}

/*****************************************************************************
* 函 数 名  : is_log_buffer_full
*
* 功能描述  : 缓冲区是否满
*
* 输入参数  : u32 read_p,  读指针
*             u32 write_p，写指针
*             u32 buf_len, buffer长度
*
* 输出参数  : 无
*
* 返 回 值  : BSP_TRUE:满，BSP_FALSE:未满
*****************************************************************************/
int is_log_buffer_full(u32 read_p, u32 write_p, u32 buf_len)
{
    u32 left_len;

    if(read_p > write_p)
    {
        left_len = read_p - write_p;
    }
    else
    {
        left_len = buf_len - write_p + read_p;
    }

    if(left_len < LOG_BUFFER_FULL_THRESHOLD)
    {
        printk("%s: buffer full read 0x%x, write 0x%x, len 0x%x\n", __FUNCTION__, read_p, write_p, buf_len);
        return BSP_TRUE;
    }

    return BSP_FALSE;
}

/*****************************************************************************
* 函 数 名  : log_read
*
* 功能描述  : 从log设备读取数据
*
* 输入参数  : struct file *file, 设备文件file指针
*             buf，目的buffer
*             count, 目的buffer大小
*
*
* 输出参数  : 无
*
* 返 回 值  : 0，打开成功， 非0，打开失败
*****************************************************************************/
static ssize_t log_read(struct file *file, char __user *buf, size_t count, loff_t *pos)
{
    logger_info_stru * log_info;
    u32 read_p;
    u32 write_p;
    u32 len;
    u32 msg_len;
    int ret;
    unsigned long lock_flag;
    char * log_buff;
    DEFINE_WAIT(wait);

    log_info = file->private_data;
    if(NULL == log_info)
    {
        printk("%s: get log_info fail\n", __FUNCTION__);
        return BSP_ERROR;
    }

    /* buffer未初始化，进入睡眠 */
    if(log_info->log_mem == NULL)
    {
        prepare_to_wait(&log_info->wq, &wait, TASK_INTERRUPTIBLE);
        spin_lock_irqsave(&log_info->lock, lock_flag);
        log_info->sleep_flag = BSP_TRUE;
        spin_unlock_irqrestore(&log_info->lock, lock_flag);
        schedule();
    }

    read_p  = log_info->log_mem->log_read;
	while(1)
    {
		prepare_to_wait(&log_info->wq, &wait, TASK_INTERRUPTIBLE);

        write_p = log_info->log_mem->log_write;
        /* buffer满，更改读指针，将buffer置空 */
        if(is_log_buffer_full(read_p, write_p, log_info->log_mem->log_buf_len))
        {
            /* 更新读指针 */
            log_info->log_mem->log_read = write_p;
            read_p = write_p;
            /* 输出提示信息 */
            msg_len = (u32)strlen(LOG_DROPPED_MESSAGE);
            len = (count > msg_len) ? msg_len : count;
            ret = do_read_data_to_user(LOG_DROPPED_MESSAGE, buf, len);
			break;
        }

		ret = (read_p == write_p);
		if (!ret)
			break;

        /* 读写指针相等，无数据，如果为非阻塞方式打开，再次尝试 */
		if (file->f_flags & O_NONBLOCK) {
			ret = -EAGAIN;
			break;
		}

        /* 如果有信号需要处理，直接返回 */
		if (signal_pending(current)) {
			ret = -EINTR;
			break;
		}

        /* 无数据，睡眠 */
        spin_lock_irqsave(&log_info->lock, lock_flag);
        log_info->sleep_flag = BSP_TRUE;
        spin_unlock_irqrestore(&log_info->lock, lock_flag);
		schedule();
	}

	finish_wait(&log_info->wq, &wait);
	if (ret)
		return ret;

    if(read_p <= write_p)
    {
        len = write_p - read_p;
    }
    else
    {
        len = log_info->log_mem->log_buf_len - read_p;
    }
    len = (len > count) ? count : len;

    log_buff = (char *)(log_info->log_mem) + sizeof(log_mem_stru);
    /* 拷贝数据 */
    ret = do_read_data_to_user(log_buff + read_p, buf, len);

    /* 更新读指针 */
    log_info->log_mem->log_read = (read_p + ret)%(log_info->log_mem->log_buf_len);
    if(log_info->log_mem->full_flag)
    {
        log_info->log_mem->full_flag = 0;
    }

    return ret;
}

/*****************************************************************************
* 函 数 名  : log_open
*
* 功能描述  : 打开log设备
*
* 输入参数  : struct inode *inode, 设备文件inode节点
*             struct file *file
*
* 输出参数  : 无
*
* 返 回 值  : 0，打开成功， 非0，打开失败
*****************************************************************************/
int log_open(struct inode *inode, struct file *file)
{
    logger_info_stru * log_info;

    log_info = get_log_from_minor(MINOR(inode->i_rdev));
    if(NULL == log_info)
    {
        printk("%s: get device fail\n", __FUNCTION__);
        return BSP_ERROR;
    }

    if(log_info->in_use == BSP_TRUE)
    {
        printk("%s: device %s is in use\n", __FUNCTION__, log_info->misc.name);
        return BSP_ERROR;
    }
    log_info->in_use = BSP_TRUE;

    file->private_data = log_info;

    return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : log_release
*
* 功能描述  : 关闭log设备
*
* 输入参数  : struct inode *inode, 设备文件inode节点
*             struct file *file
*
* 输出参数  : 无
*
* 返 回 值  : 0，成功
*****************************************************************************/
int log_release(struct inode *ignored, struct file *file)
{
    logger_info_stru * log_info;

    log_info = file->private_data;
    if(NULL == log_info)
    {
        printk("%s: release device fail\n", __FUNCTION__);
        return BSP_ERROR;
    }

    log_info->in_use = BSP_FALSE;

    return BSP_OK;
}

static const struct file_operations logger_fops = {
	.read    = log_read,
	.open    = log_open,
	.release = log_release,
};

/*****************************************************************************
* 函 数 名  : log_int_handle
*
* 功能描述  : IPC中断处理函数，唤醒log task
*
* 输入参数  : u32 data
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void log_int_handle(u32 data)
{
    logger_info_stru * log;

    list_for_each_entry(log, &kernel_log_list, logs)
    {
        if (log->in_use == BSP_TRUE)
        {
            up(&g_st_log_sem);
        }
    }
}

/*****************************************************************************
* 函 数 名  : log_dump_handle
*
* 功能描述  : 注册给dump的回调函数，系统异常时，唤醒log task
*
* 输入参数  : u32 data
*
* 输出参数  : 无
*
* 返 回 值  : 无
*****************************************************************************/
void log_dump_handle(void)
{
    logger_info_stru * log;

    list_for_each_entry(log, &kernel_log_list, logs)
    {
        if (log->in_use == BSP_TRUE)
        {
            up(&g_st_log_sem);
        }
    }

}

/*****************************************************************************
* 函 数 名  : log_device_init
*
* 功能描述  : 初始化函数，创建log设备节点
*
* 输入参数  : char * dev_name, 设备名, log_mem_stru * log_info, log缓冲区
*
* 输出参数  : 无
*
* 返 回 值  : 0，成功, 非0，失败
*****************************************************************************/
int log_device_init(char * dev_name)
{
	int ret = 0;
	logger_info_stru * log;

	log = kzalloc(sizeof(logger_info_stru), GFP_KERNEL);
	if (log == NULL)
    {
        printk("%s: malloc fail\n", __FUNCTION__);
		return BSP_ERROR;
	}

	log->misc.minor = MISC_DYNAMIC_MINOR;
	log->misc.name = kstrdup(dev_name, GFP_KERNEL);
    if (log->misc.name == NULL)
    {
        printk("%s: malloc for dev name[%s] fail\n", __FUNCTION__, dev_name);
        kfree(log);
        return BSP_ERROR;
	}

    log->in_use = BSP_FALSE;
    log->sleep_flag = BSP_FALSE;
	log->misc.fops = &logger_fops;
	log->misc.parent = NULL;
    log->log_mem = NULL;

	init_waitqueue_head(&log->wq);
    spin_lock_init(&log->lock);

	INIT_LIST_HEAD(&log->logs);
	list_add_tail(&log->logs, &kernel_log_list);

	ret = misc_register(&log->misc);
	if (unlikely(ret)) {
        printk("%s: failed to register misc device for log '%s'!\n", __FUNCTION__, log->misc.name);
        kfree(log);
        return BSP_ERROR;
	}

	return BSP_OK;
}

/*****************************************************************************
* 函 数 名  : log_init
*
* 功能描述  : 初始化函数，分配相关资源
*
* 输入参数  : 无
*
* 输出参数  : 无
*
* 返 回 值  : 0，成功, 非0，失败
*****************************************************************************/
int log_init(void)
{
    int ret = 0;
    struct task_struct  *tsk;

    if(DUMP_MBB == dump_get_product_type())
    {
        /* ccore device */
        ret = log_device_init(CCORE_LOG_DEV_NAME);
        if(BSP_OK != ret)
        {
            printk("%s: log_ccore device init fail\n", __FUNCTION__);
            return BSP_ERROR;
        }
        /* mcore device */
        ret = log_device_init(MCORE_LOG_DEV_NAME);
        if(BSP_OK != ret)
        {
            printk("%s: log_mcore device init fail\n", __FUNCTION__);
            return BSP_ERROR;
        }

        sema_init(&g_st_log_sem, 0);

        ret= bsp_dump_register_hook("KERNEL_LOG", log_dump_handle);
        if(BSP_ERROR == ret)
        {
            printk("%s: register to dump failed!\n", __FUNCTION__);
            return BSP_ERROR;
        }

        ret = bsp_ipc_int_connect(IPC_ACPU_INT_SRC_CCPU_LOG, (voidfuncptr)log_int_handle, 0);
        if(BSP_OK != ret)
        {
            printk("%s: ipc connect failed! ret = %d\n", __FUNCTION__, ret);
            return BSP_ERROR;
        }

        ret = bsp_ipc_int_enable(IPC_ACPU_INT_SRC_CCPU_LOG);
        if(BSP_OK != ret)
        {
            printk("%s: ipc enable failed! ret = %d\n", __FUNCTION__, ret);
            return BSP_ERROR;
        }

        tsk = kthread_run(log_task_func, 0, "log_task");
        if (IS_ERR(tsk))
        {
            printk("%s: create log_task failed!\n", __FUNCTION__);
            return BSP_ERROR;
        }

        printk("%s  ok\n", __FUNCTION__);

    }

    return BSP_OK;
}

module_init(log_init);
#endif

