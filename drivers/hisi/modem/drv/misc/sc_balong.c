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

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*lint -save -e322 -e7 -e537*/
#include <stdarg.h>
#include <linux/err.h>
#include <linux/string.h>
#include <linux/slab.h>
#include <linux/mtd/mtd.h>
#include <mdrv.h>
#include "bsp_misc.h"
#include "sc_balong.h"
#include "nv_ctrl.h"
/*lint -restore +e322 +e7 +e537*/

/*lint -save -e438 -e530 -e713 -e830 -e529*/
sc_status_stru g_sc_stat;
char g_sc_area_name[64] = {};

/* func type */
void sc_icc_task(void);
s32  sc_bakup(s8 *pdata, u32 len,u32 req_core);
s32  sc_restore(s8 *pdata, u32 len, u32 req_core);

/*
* Function   : sc_icc_msg_proc
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32 sc_icc_msg_proc(u32 chanid, u32 len, void* pdata)
{ 
    if(chanid != SC_ICC_CHAN_ID)
    {
        sc_error_printf(" sc icc channel error :0x%x\n",chanid);
        return BSP_ERR_SC_ICC_READ;
    }

    osl_sem_up(&g_sc_stat.sc_tsk_sem);

    sc_debug_printf("recv from ccore ok!\n");

    return SC_OK;
}


/*
* Function   : sc_bakup
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32  sc_bakup(s8 *pdata, u32 len, u32 req_core)
{
    s32 sc_fp       = 0;
    s32 wlen        = 0;
    u32 sc_mtd_len  = 0;
    struct mtd_info* mtd;
    
    if(MISC_SC_REQ_CCORE == req_core)
    {
        sc_fp = bsp_open((char *)SC_PACKET_TRANS_FILE,(RFILE_RDONLY),0660);
        if(!sc_fp)
        {   
            sc_error_printf("bsp_open error, chanid :0x%x sc_fp :0x%x\n",SC_ICC_CHAN_ID,sc_fp);
            return BSP_ERR_SC_NO_FILE;
        }
        else
        {
            sc_debug_printf("bsp_open ok, file is 0x%x!\n",sc_fp);
        }

        wlen = bsp_read(sc_fp, pdata, len);
        if(wlen != len)
        {
            sc_error_printf("bsp_read error, opt_len :0x%x sc_ram_len :0x%x\n", wlen, len);
            bsp_close(sc_fp);
            return BSP_ERR_SC_READ_FILE_FAIL;
        }
        else
        {
            sc_debug_printf("bsp_read ok, len is 0x%x!\n",(u32)(wlen));
        }
        
        bsp_close(sc_fp);
    }
    mtd = get_mtd_device_nm((char*)g_sc_area_name);
    if (IS_ERR(mtd))
    {
        sc_error_printf("get mtd device err!\n");
        return BSP_ERR_READ_MTD_FAIL;
    }
    sc_mtd_len = mtd->size;
    sc_debug_printf("mtd len: 0x%x\n",sc_mtd_len);
    put_mtd_device(mtd);
    
    if((sc_mtd_len < SC_MTD_PTABLE_OFFSET) || (len >= SC_MTD_PTABLE_OFFSET))
    {
        sc_error_printf("mtd length err! sc_mtd_len: 0x%x, len: 0x%x\n",sc_mtd_len, len);
        return BSP_ERR_READ_LGTH_FAIL;
    }

    wlen = bsp_nand_write((char*)g_sc_area_name, (sc_mtd_len - SC_MTD_PTABLE_OFFSET), pdata, len);
    if(wlen != BSP_OK)
    {
        sc_error_printf("mtd length err! wlen 0x%x, len is 0x%x\n",wlen,len);
        return BSP_ERR_SC_WRITE_FILE_FAIL;
    }
    
    sc_debug_printf("sc write to nand ok, len is 0x%x!\n",(u32)(wlen));
    
    return SC_OK;
}

/*
* Function   : sc_restore
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32  sc_restore(s8 *pdata, u32 len, u32 req_core)
{
    s32 sc_fp       = 0;
    s32 rlen        = 0;
    s32 wlen        = 0;
    u32 sc_mtd_len  = 0;
    struct mtd_info* mtd;

    mtd = get_mtd_device_nm((char*)g_sc_area_name);
    if (IS_ERR(mtd))
    {
        sc_error_printf("get mtd device err! %s\n",mtd);
        return BSP_ERR_READ_MTD_FAIL;
    }
    sc_mtd_len = mtd->size;
    put_mtd_device(mtd);
    
    if((sc_mtd_len < SC_MTD_PTABLE_OFFSET) || (len >= SC_MTD_PTABLE_OFFSET))
    {
        sc_error_printf("mtd length err! size 0x%x\n",mtd->size);
        return BSP_ERR_READ_LGTH_FAIL;
    }

    rlen = bsp_nand_read((char*)g_sc_area_name, (sc_mtd_len - SC_MTD_PTABLE_OFFSET), pdata, len, NULL);
    if(rlen != BSP_OK)
    {
        sc_error_printf("mtd length err! read_ret 0x%x, len is 0x%x\n",rlen,len);
        return BSP_ERR_SC_READ_FILE_FAIL;
    }
    else
    {
        sc_debug_printf("mtd length read ok len is 0x%x\n",rlen);
    }

    if(MISC_SC_REQ_CCORE == req_core)
    {
        /* write to file */
        sc_fp = bsp_open((char*)SC_PACKET_TRANS_FILE,(RFILE_CREAT|RFILE_RDWR),0660);
        if(!sc_fp)
        {   
            sc_error_printf("bsp_open error, chanid :0x%x sc_fp :0x%x\n",SC_ICC_CHAN_ID,sc_fp);
            return BSP_ERR_SC_NO_FILE;
        }
        else
        {
            sc_debug_printf("bsp_open ok, file is 0x%x!\n",sc_fp);
        }

        /* write to file */
        wlen = bsp_write(sc_fp, pdata, len);
        if(wlen != len)
        {
            sc_error_printf("bsp_write error, chanid :0x%x wlen :0x%x, len : 0x%x\n",SC_ICC_CHAN_ID,wlen,len);
            bsp_close(sc_fp);
            return BSP_ERR_SC_WRITE_FILE_FAIL;
        }
        else
        {
            sc_debug_printf("bsp_write ok,wlen is 0x%x",wlen);
        }

        bsp_close(sc_fp);
    }
    return SC_OK;
}


/*
* Function   : sc_icc_task
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
void sc_icc_task(void)
{
    s32 ret         = -1;
    s32 icc_len     = 0;
    sc_icc_stru icc_trans;

    /* coverity[no_escape] */
    for(;;)
    {
        osl_sem_down(&g_sc_stat.sc_tsk_sem);

        sc_debug_printf("icc task, recv from acore ok, chanid :0x%x\n",SC_ICC_CHAN_ID);

        icc_len = bsp_icc_read(SC_ICC_CHAN_ID, (u8 * )&icc_trans, sizeof(sc_icc_stru));
        if((icc_len > sizeof(sc_icc_stru)))
        {
            sc_error_printf("bsp icc read error, chanid :0x%x opt_len :0x%x\n",SC_ICC_CHAN_ID,icc_len);
            osl_sem_up(&g_sc_stat.sc_tsk_sem);
            continue;
        }
        else if(0 >= icc_len)
        {
            sc_debug_printf("bsp icc read error, length is 0!\n");
            continue ;
        }
        
        g_sc_stat.sc_ram_len = icc_trans.sc_total_len;
        sc_debug_printf("len is 0x%x\n", g_sc_stat.sc_ram_len);
        
        
        icc_trans.sc_cnf_ret = SC_OK;
        /* get buffer */
        g_sc_stat.sc_ram_addr = (u8* )osl_malloc(icc_trans.sc_total_len);
        if(!g_sc_stat.sc_ram_addr)
        {
            sc_error_printf("bsp icc read error, chanid :0x%x ret :0x%x\n",SC_ICC_CHAN_ID,ret);
            icc_trans.sc_cnf_ret = BSP_ERR_SC_MALLOC_FAIL;
            goto confirm;
        }
        else
        {
            sc_debug_printf("malloc ok!\n");
        }

        if(MISC_SC_OPT_WRITE== icc_trans.sc_opt_type)
        {
            if(SC_OK != sc_bakup(g_sc_stat.sc_ram_addr, g_sc_stat.sc_ram_len, MISC_SC_REQ_CCORE))
            {
                icc_trans.sc_cnf_ret = BSP_ERR_SC_WRITE_FILE_FAIL;
            }
        }
        else
        {
            if(SC_OK != sc_restore(g_sc_stat.sc_ram_addr, g_sc_stat.sc_ram_len, MISC_SC_REQ_CCORE))
            {
                icc_trans.sc_cnf_ret = BSP_ERR_SC_READ_FILE_FAIL; 
            }
        }
        osl_free(g_sc_stat.sc_ram_addr);
        
        
confirm:
        /* send pkt to modem */
        icc_len = bsp_icc_send(ICC_CPU_MODEM, SC_ICC_CHAN_ID, (u8*)&icc_trans, sizeof(sc_icc_stru));
        if(icc_len != sizeof(sc_icc_stru))
        {
            sc_error_printf("send to modem failed 0,icc_len is 0x%x!\n",icc_len);
        }
        else
        {
            sc_debug_printf("send to mdoem ok,icc_len is 0x%x!\n",icc_len);
        }
        
        continue;
    }
        
}

/*
* Function   : bsp_sc_kernel_init
* Discription: c core nv init,this phase build upon the a core kernel init,
*              this phase after icc init,this phase ensure to use all nv api normal
*              start at this phase ,ops global ddr need spinlock
* Parameter  : none
* Output     : result
* History    : 
*/
s32 bsp_sc_kernel_init(void)
{
    s32 ret = SC_ERROR;
    char result[64] = "block2mtd: ";

    ret = flash_find_ptn((const char*)PARTITION_MODEM_NVDEFAULT_NAME, g_sc_area_name);
    if(ret)
    {
        sc_error_printf("find %s fail, ret = 0x%x\n", PARTITION_MODEM_NVDEFAULT_NAME, ret);
        return BSP_ERR_SC_FIND_FAIL;
    }
    else
    {
        sc_error_printf("%s name: %s\n", PARTITION_MODEM_NVDEFAULT_NAME, g_sc_area_name);
    }
    strncpy(result, "block2mtd: ", sizeof("block2mtd: "));
    strncat(result, g_sc_area_name, sizeof(g_sc_area_name));
    strncpy(g_sc_area_name, result, strlen(result));

    osl_sem_init(0,&g_sc_stat.sc_tsk_sem);

    ret = osl_task_init("sc_acore_task",15,1024, (OSL_TASK_FUNC)sc_icc_task,NULL,(void*)&g_sc_stat.sc_taskid);
    if(ret)
    {
        sc_error_printf("init task failed!\n");
        return BSP_ERR_SC_TASK_INIT_FAIL;
    }
    
    /* yangzhi for sc file backup and restore begin: */
    if(ICC_OK != bsp_icc_event_register(SC_ICC_CHAN_ID, sc_icc_msg_proc,NULL,NULL,NULL))
    {
        sc_error_printf("register icc channel failed!\n");
        return BSP_ERR_SC_SEM_INIT_FAIL ;
    }

    sc_printf("[SC]: init success.\n");

    return SC_OK;
}


/* module init */
module_init(bsp_sc_kernel_init);

/*
* Function   : bsp_sc_restore
* Parameter  : none
* Output     : result
* History    : 
*/
s32 bsp_sc_restore(u8* pRamAddr,u32 len)
{
    return sc_restore((s8 *)pRamAddr,len, MISC_SC_REQ_ACORE);
}

/*
* Function   : bsp_sc_backup
* Parameter  : none
* Output     : result
* History    : 
*/
s32 bsp_sc_backup(u8* pRamAddr,u32 len)
{
    return sc_bakup((s8 *)pRamAddr,len, MISC_SC_REQ_ACORE);
}
/*lint -restore*/
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif



