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
#include <linux/thread_info.h>
#include <linux/syslog.h>
#include <linux/errno.h>
#include <linux/kthread.h>
#include <linux/semaphore.h>
#include <linux/delay.h>
#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/current.h>
#include <asm/string.h>
#include <asm/traps.h>
#include "product_config.h"
#include "osl_types.h"
#include "osl_io.h"
#include "osl_bio.h"
#include "mdrv.h"
#include "bsp_om_api.h"
#include "bsp_dump.h"
#include "bsp_dump_drv.h"
#include "bsp_om_save.h"
#include "bsp_ipc.h"
#include "bsp_memmap.h"
#include "bsp_wdt.h"
#include "bsp_pmu.h"
#include "bsp_icc.h"
#include "bsp_utrace.h"
#include "drv_onoff.h"
#include "bsp_nvim.h"
#include <linux/huawei/rdr.h>

#ifndef RDR_CCORE
#define RDR_CCORE 2
#endif

#define RDR_CCORE_ADDR \
	((struct dump_area_t *)(rdr_core_addr(pbb, RDR_CCORE)))

typedef struct
{
    u32 maxNum;
    u32 front;
    u32 rear;
    u32 num;
    u32 data[1];
} dump_queue_t;

dump_nv_s g_dump_config;

s32 bsp_dump_register_hook(dump_save_modid_t mod_id, dump_save_hook func)
{
    return rdr_dump_register_hook(mod_id, func);
}

s32 bsp_dump_get_cp_field(u32 field_id, char** buffer, u32* length)
{
    u32 i;
    dump_area_t* pCPArea;
    dump_global_internal_t * prdr_global ;

    *buffer = NULL;
    *length = 0;
    
    pCPArea = (dump_area_t*)RDR_CCORE_ADDR;
    prdr_global = (dump_global_internal_t *)(RDR_AREA_RESERVE_ADDR->ap_cp_share.content.rdr_global_internal);

    if(prdr_global->comm_internal.init_flag != DUMP_INIT_FLAG)
    {
        printk("bsp_dump_get_cp_field: init_flag=0x%x\n", prdr_global->comm_internal.init_flag);        
        return BSP_ERROR;
    }

    for(i=0; i<CP_AREA_FIELD_MAX_NUM; i++)
    {
        if(pCPArea->fields[i].field_id == field_id)
        {          
            *buffer = (char*)pCPArea + pCPArea->fields[i].offset_addr;
            *length = pCPArea->fields[i].length;

            return BSP_OK;            
        }
    }
    printk("bsp_dump_get_cp_field: error\n");

    return BSP_ERROR;    
}

s32 bsp_dump_print(void)
{
    char* pbuffer = NULL;
    u32   length  = 0;

    if(bsp_dump_get_cp_field(DUMP_SAVE_MOD_DRX_CCORE, &pbuffer, &length) != BSP_OK)
    {
        printk("bsp_dump_print: error1\n");
        return 0;
    }

    return 0;
}
EXPORT_SYMBOL_GPL(bsp_dump_print);

/* ����mod_id��ȡ��Ӧ��buffer��ַ��ʧ�ܷ���0 */
u32 bsp_dump_get_buffer_addr(dump_save_modid_t mod_id)
{
    u32 addr = 0;
    dump_save_t * top_head = (dump_save_t *)pbb;
    dump_area_t * area_head;
    u32 i;

    /* ��ȡAP buffer */
    if((mod_id & 0x0F000000) == 0x01000000)
    {
        /* AP��Ӧarea 0 */
        area_head = (dump_area_t *)((u32)pbb + top_head->area_info[0].offset);
    }
    /* ��ȡCP buffer */
    else if((mod_id & 0x0F000000) == 0x02000000)
    {
        /* CP��Ӧarea 2 */
        area_head = (dump_area_t *)((u32)pbb + top_head->area_info[2].offset);
    }
    /* ��ȡLPM3 buffer */
    else if((mod_id & 0x0F000000) == 0x04000000)
    {
        /* LPM3��Ӧarea 5 */
        area_head = (dump_area_t *)((u32)pbb + top_head->area_info[5].offset);
        if(area_head->head.magic_num != 0x88118811)
        {
            printk("%s: LPM3 rdr filed is not inited\n", __FUNCTION__);
            return 0;            
        }
    }
    else
    {
        printk("%s: invalid mod id 0x%x\n", __FUNCTION__, (u32)mod_id);
        return 0;
    }

    /* ����filed id */
    for(i=0; i<area_head->head.field_num; i++)
    {
        if(mod_id == area_head->fields[i].field_id)
        {
            addr = (u32)area_head + area_head->fields[i].offset_addr;
            printk("%s: field found, offset 0x%x, addr 0x%x\n", __FUNCTION__, area_head->fields[i].offset_addr, addr);
            break;
        }
    }

    return addr;
}

#define MAX_OUTPUT_RECORD_CNT   10
void bsp_dump_get_cp_task_record(void)
{
    static u32 g_ul_write_p = 0;
    int i;
    u32 front_cnt = 0;
    u32 rear_index = 0;
    dump_queue_t * cp_task_queue;

    cp_task_queue = (dump_queue_t*)bsp_dump_get_buffer_addr(DUMP_CP_TASK_SWITCH);
    if(cp_task_queue == NULL)
    {
        printk("[dump]: get cp task switch addr fail\n");
        return;
    }

    if(cp_task_queue->rear != g_ul_write_p)
    {
        printk("[dump]: get new task switch record, last rear 0x%x, new rear 0x%x\n", g_ul_write_p, cp_task_queue->rear);
    }
    else
    {
        printk("[dump]: no more task switch record, last rear 0x%x, new rear 0x%x\n", g_ul_write_p, cp_task_queue->rear);
    }
    g_ul_write_p = cp_task_queue->rear;

    rear_index = (cp_task_queue->rear)%(cp_task_queue->maxNum);
    if(rear_index < MAX_OUTPUT_RECORD_CNT)
    {
        front_cnt = MAX_OUTPUT_RECORD_CNT - rear_index/2;
    }

    printk("    task_id         timestamp\n");
    printk("   ----------------------------\n");
    for(i=(int)front_cnt*2; i>0; i-=2)
    {
        printk("    0x%x        0x%x\n", cp_task_queue->data[cp_task_queue->maxNum-i], cp_task_queue->data[cp_task_queue->maxNum-i+1]);
    }

    for(i=(int)(MAX_OUTPUT_RECORD_CNT-front_cnt)*2; i>0; i-=2)
    {
        printk("    0x%x        0x%x\n", cp_task_queue->data[rear_index-i], cp_task_queue->data[rear_index-i+1]);
    }
}

s32 bsp_dump_get_buffer(dump_save_modid_t mod_id, char** buffer, u32* length)
{
    if((!buffer) || (!length))
    {
        printk("bsp_dump_get_buffer, invalid param!.buffer=0x%x length=0x%x\n", (u32)buffer, (u32)length);
        return BSP_ERR_DUMP_INVALID_PARAM;
    }

    if((mod_id>=DUMP_CP_FIELD_BEGIN) && (mod_id<DUMP_CP_FIELD_END))
    {
        return bsp_dump_get_cp_field(mod_id, buffer, length);
    }

    switch(mod_id)
    {
        case DUMP_SAVE_MOD_USB:
            *length = (u32)DUMP_EXT_USB_DATA_SIZE;
            break;	
        case DUMP_SAVE_MOD_SIM0:
            *length = (u32)DUMP_EXT_SCI0_DATA_SIZE;
            break;
        case DUMP_SAVE_MOD_SIM1:
            *length = (u32)DUMP_EXT_SCI1_DATA_SIZE;
            break;
        case DUMP_SAVE_MOD_OM_MSG:
            *length = (u32)DUMP_EXT_OM_MSG_SIZE;
            break;
        case DUMP_SAVE_MOD_OM_LOG:
            *length = (u32)DUMP_EXT_OM_LOG_SIZE;
            break;
        case DUMP_SAVE_MOD_OSA_APP:
            *length = (u32)DUMP_INTER_OSA_APP_SIZE;
            break;
        case DUMP_SAVE_MOD_OSA_COMM:
            *length = (u32)DUMP_INTER_OSA_COMM_SIZE;
            break;
        case DUMP_SAVE_MOD_UTRACE:
            *length = (u32)DUMP_EXT_OM_UTRACE_DATA_SIZE;
            break;
        case DUMP_SAVE_MOD_DRX_ACORE:
            *length = (u32)DUMP_EXT_OM_DRX_ACORE_SIZE;
            break;
        case DUMP_SAVE_MOD_DRX_CCORE:
            *length = (u32)DUMP_EXT_OM_DRX_CCORE_SIZE;
            break;
        //case DUMP_SAVE_MOD_OSA_MEM:
            //*buffer = (char *)DUMP_MEMINFO_ADDR;
        //    *length = (u32)DUMP_MEMINFO_SIZE;
        //    break;

		/* icc */
		case DUMP_SAVE_MOD_ICC_ACORE:
			*length = (u32)DUMP_EXT_ICC_ACORE_SIZE;
			break;
		case DUMP_SAVE_MOD_ICC_CCORE:
			*length = (u32)DUMP_EXT_ICC_CCORE_SIZE;
			break;
		case DUMP_SAVE_MOD_ICC_MCORE:
			*length = (u32)DUMP_EXT_ICC_MCORE_SIZE;
			break;
        default:
            printk("bsp_dump_get_buffer[%d]:  mod_id is invalid! mod=%d\n", __LINE__, mod_id);
            *buffer = NULL;
            *length = 0;
            return BSP_ERR_DUMP_INVALID_MODULE;
    }

    *buffer = rdr_balong_reg_field(mod_id, *length);

    if(*buffer == NULL)
    {
        printk("bsp_dump_get_buffer[%d]: rdr_balong_reg_field failed! mod_id:%d, length:%d\n", __LINE__, mod_id, *length);
        return BSP_ERROR;
    }   

    return BSP_OK;
}

s32 bsp_dump_save_file(dump_save_file_t file_id, char* buffer, u32 length, dump_save_file_mode_t mode)
{
    char *filename;

    if((DUMP_SAVE_FILE_BUTT <= file_id) || ((DUMP_SAVE_FILE_MODE_BUTT <= mode)) || (!buffer) || (!length))
    {
        printk("bsp_dump_save_file[%d]:  invalid param! %d 0x%x %d %d\n", __LINE__, (u32)file_id, (u32)buffer, (u32)length, (u32)mode);
        return BSP_ERR_DUMP_INVALID_PARAM;
    }

    switch(file_id)
    {
        case DUMP_SAVE_FILE_OM:
            filename = OM_OAM_LOG;
            break;
        case DUMP_SAVE_FILE_DIAG:
            filename = OM_DIAG_LOG;
            break;
        case DUMP_SAVE_FILE_ZSP:
            filename = OM_ZSP_DUMP;
            break;
        case DUMP_SAVE_FILE_HIFI:
            filename = OM_HIFI_DUMP;
            break;
        case DUMP_SAVE_FILE_NCM:
            filename = OM_NCM_LOG;
            break;
        default:
            printk("bsp_dump_save_file[%d]:  file_id is invalid! file=%d\n", __LINE__, file_id);
            return BSP_ERR_DUMP_INVALID_FILE;
    }

    bsp_om_save_file(filename, buffer, length, mode);

    return BSP_OK;
}

void bsp_dump_int_lock(bsp_module_e mod_id)
{
}

void bsp_dump_int_unlock(bsp_module_e mod_id)
{
}

void bsp_dump_trace_stop(void)
{
}

void bsp_dump_set_hso_conn_flag(u32 flag)
{
}

void system_error (u32 mod_id, u32 arg1, u32 arg2, char *data, u32 length)
{
    hisi_system_error(mod_id, arg1, arg2, data, length);
}

