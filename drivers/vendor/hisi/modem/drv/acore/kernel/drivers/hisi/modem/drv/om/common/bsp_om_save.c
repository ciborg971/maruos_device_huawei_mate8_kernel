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

#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/timex.h>
#include <linux/rtc.h>
#include <linux/debugfs.h>
#include <linux/module.h>
#include <linux/sched.h>
#include <linux/of.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/stat.h>
#include <asm/uaccess.h>
#include <drv_nv_def.h>
#include <drv_nv_id.h>
#include "bsp_memmap.h"
#include "bsp_om_api.h"
#include "bsp_om_save.h"
#include "bsp_dump_def.h"
#include "bsp_dump_drv.h"
#include "bsp_dump_mem.h"
#include "bsp_nvim.h"
#include "drv_nv_id.h"
#include "bsp_dsp.h"
#include "hi_dsp.h"
#include "bsp_sysctrl.h"
#include <linux/vmalloc.h>
#include <rdr_adp.h>
#include "bsp_dump.h"

struct linux_dirent {
    unsigned long   d_ino;
    unsigned long   d_off;
    unsigned short  d_reclen;
    char            d_name[1];
};

typedef struct {
    char *s;        /* The user's output buffer */
    int nmax;       /* The length of the user's output buffer */
    int length;     /* The current length of the string in s[] */
} print_data_t;

static char g_OmLogBuffer[256] = {0x00};

char g_ResetLogBuffer[256] = {0x00};
extern dump_global_info_t  *g_dump_global_info;
void dump_memcpy(u32 * dst, const u32 * src, u32 len);
extern void bsp_dump_get_reset_context_and_id(u32 *reboot_context, u32 *reboot_task,u32 *reboot_int,dump_head_t* dump_head);
u8* g_modem_ddr_map_addr = NULL;

#ifdef BSP_CONFIG_HI3650
#define pgprot_writecombine_xn(prot) \
    __pgprot_modify(prot, PTE_ATTRINDX_MASK, PTE_ATTRINDX(MT_NORMAL_NC) | PTE_PXN | PTE_UXN)

void *om_vmap(phys_addr_t paddr, size_t size)
{
    int i;
    void *vaddr = NULL;
    pgprot_t pgprot;
    unsigned long offset;
    int pages_count;
    struct page **pages;

    offset = paddr & ~PAGE_MASK;
    paddr &= PAGE_MASK;
    pages_count = PAGE_ALIGN(size + offset)/PAGE_SIZE;

    pages = kmalloc(sizeof(struct page *) * pages_count, GFP_KERNEL);
    if (!pages)
    {
        om_error("kmalloc pages fail\n");
        return NULL;
    }

    pgprot = pgprot_writecombine_xn(PAGE_KERNEL);

    for (i=0; i<pages_count; i++) {
        *(pages + i) = phys_to_page(paddr + PAGE_SIZE*i);
    }
    vaddr = vmap(pages, pages_count, VM_MAP, pgprot);

    if (NULL == vaddr){
        om_error("vmap addr fail\n");
        kfree(pages);
        return NULL;
    }
    return offset + vaddr;
}
#endif

void om_trace(char *buffer, char *fmt,...)
{
    /*lint -save -e40 -e522 */
    va_list arglist;
    /*lint -restore +e40 +e522 */
    va_start(arglist, fmt);
    vsnprintf(buffer, 256, fmt, arglist); /* [false alarm]:����Fortify���� */
    va_end(arglist);

    return;
}

int om_create_dir(char *path)
{
    int fd;

    /* ����ļ��в����ڣ��������ļ���*/
    fd = sys_access(path, 0); //F_OK, ����ļ��Ƿ����
    if(0 != fd)
    {
        fd  = sys_mkdir(path, 0660);
        if(fd < 0)
        {
            bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OM, "create om dir failed! ret = %d\n", fd);
            return fd;
        }
    }

    return BSP_OK;
}

int om_open_dir(char *path)
{
    int fd;

    fd = om_create_dir(path);
    if(BSP_OK == fd)
    {
        fd = sys_open(path, O_RDONLY| O_DIRECTORY, 0);
    }

    return fd;
}

int om_close_dir(int fd)
{
    sys_close(fd);

    return BSP_OK;
}

void om_rm_dir(char * dir_name)
{
    char *buf = BSP_NULL;
    int i;
    int read_bytes;
    struct linux_dirent *dir;
    int fd;
    char temp[OM_DUMP_FILE_NAME_LENGTH];

    buf = kmalloc(1024, GFP_KERNEL);
    if(BSP_NULL == buf)
    {
        om_error("alloc mem error\n");
        return;
    }

    fd = om_open_dir(dir_name);
    if(fd < 0)
    {
        om_error("open dir %s fail\n", dir_name);
        goto out;
    }

    read_bytes = sys_getdents(fd, (struct linux_dirent *)buf, 1024);
    if(-1 == read_bytes)
    {
        om_error("get dents error!\n");
        goto out;
    }

    for(i=0; i<read_bytes; )
    {
        dir = (struct linux_dirent *)(buf + i);
        i += (int)dir->d_reclen;

        snprintf(temp, sizeof(temp), "%s/%s", dir_name, dir->d_name);
        if(0 == strncmp(dir->d_name, ".", strlen(dir->d_name)) || 0 == strncmp(dir->d_name, "..", strlen(dir->d_name)))
        {
            continue;
        }
        if(0 != sys_unlink(temp))
        {
            om_error("del file %s fail\n", dir->d_name);
        }
    }

    om_close_dir(fd);
    if(sys_rmdir(dir_name) < 0)
    {
        om_error("del dir %s fail\n", dir_name);
    }

out:
    kfree(buf);
}


void dump_rm_old_dir(void)
{
    struct linux_dirent *dir = NULL;
    char old_dir[256] = {};
    struct kstat file_status= {};
    u32 i = 0;
    mm_segment_t old_fs;
    int read_bytes = 0;
    char *buf = BSP_NULL;
    char * dir_name = NULL;
    u32 ret = 0;
    int fd = 0;;

    if(DUMP_PHONE == dump_get_product_type())
    {
        return;
    }

    dir_name = "/modem_log/dump/";

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    buf = kmalloc(1024, GFP_KERNEL);
    if(BSP_NULL == buf)
    {
        om_error("alloc mem error\n");
        goto out;
    }

    /*dump�ļ�Ŀ¼����,ɾ�����ļ�*/
    fd = sys_open(dir_name, O_RDONLY| O_DIRECTORY, 0);
    if(fd < 0)
    {
        om_error("open om dir %s failed\n", dir_name);
        goto out;
    }
    read_bytes = sys_getdents(fd, (struct linux_dirent __user *)buf, 1024);
    if(-1 == read_bytes)
    {
        om_error("get dents error!\n");
        set_fs(old_fs);
        goto out;
    }

    for(i =0; i<read_bytes; )
    {
        dir = (struct linux_dirent *)(buf + i);
        i += (int)dir->d_reclen;

        if((0 == strcmp(dir->d_name, "."))||(0 == strcmp(dir->d_name, "..")))
        {
            om_error("dir name = %s\n", dir->d_name);
            continue;
        }
        memset(old_dir, 0, sizeof(old_dir));
        memcpy(old_dir, dir_name, strlen(dir_name));
        strncat((char *)old_dir, dir->d_name, strlen(dir->d_name));

        ret = vfs_stat(old_dir, &file_status);
        if(ret)
        {
            om_error("get %s attr fail\n", old_dir);
            goto out;
        }
        om_error("file_status.mode = 0x%x, %s, %s\n", file_status.mode, old_dir, dir->d_name);
        /*�����Ŀ¼*/
        if((S_ISDIR(file_status.mode))&&(strcmp(old_dir, "/modem_log/dump/cp_log")))
        {
            om_rm_dir(old_dir);
        }
    }
out:
    set_fs(old_fs);
    if(fd > 0){sys_close(fd);}
    if(buf){kfree(buf);}
}

/* ��ȡĿ��Ŀ¼��MBB��Ʒ��Ҫ��̬�����쳣�ļ�Ŀ¼��PHONE��ƷĿ¼��RDRָ�� */
void om_get_dir(char * dir_name, DUMP_FILE_CFG_STRU * cfg, u32 type, char * dst_dir)
{
    int i;
    int j=0;
    int read_bytes;
    int fd;
    char *buf = BSP_NULL;
    struct linux_dirent *dir;
    mm_segment_t old_fs;
    char file_name[OM_DUMP_FILE_MAX_NUM][OM_DUMP_FILE_NAME_LENGTH] = {{0}, {0}, {0}};
    char temp[OM_DUMP_FILE_NAME_LENGTH];
    struct timex txc;
    struct rtc_time tm;

    if(DUMP_PHONE == type)
    {
        strncpy(dst_dir, dir_name, OM_DUMP_FILE_NAME_LENGTH - 1);
        return;
    }

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    buf = kmalloc(1024, GFP_KERNEL);
    if(BSP_NULL == buf)
    {
        om_error("alloc mem error\n");
        goto out;
    }

    fd = om_open_dir(dir_name);
    if(fd < 0)
    {
        om_error("open om dir failed\n");
        goto out;
    }

    read_bytes = sys_getdents(fd, (struct linux_dirent *)buf, 1024);
    if(-1 == read_bytes)
    {
        om_error("get dents error!\n");
        goto out;
    }

    for(i=0; i<read_bytes; )
    {
        dir = (struct linux_dirent *)(buf + i);
        i += (int)dir->d_reclen;

        for(j=0; j<OM_DUMP_FILE_MAX_NUM; j++)
        {
            memset(temp, 0, sizeof(temp));
            snprintf(temp, sizeof(temp), "DUMP_%02d", j);
            if(NULL != strstr((char *)dir->d_name, temp))
            {
                snprintf(temp, sizeof(temp), "%s%s", dir_name, dir->d_name);
                /* �������õ����洢����, ɾ��Ŀ¼ */
                if((j >= (int)cfg->file_cnt - 1) || (j >= OM_DUMP_FILE_MAX_NUM - 1))
                {
                    om_rm_dir(temp);
                }
                /* ɾ���ظ����Ŀ¼ */
                else if(0 == strncmp(file_name[j], temp, sizeof(dir->d_name)))
                {
                    om_rm_dir(temp);
                }
                else
                {
                    strncpy(file_name[j], temp, OM_DUMP_FILE_NAME_LENGTH - 1);
                }
            }
        }
    }

    /* �������õ����洢�������������쳣Ŀ¼ */
    j = (cfg->file_cnt > OM_DUMP_FILE_MAX_NUM) ? OM_DUMP_FILE_MAX_NUM : cfg->file_cnt;
    for(j=j-1; j>0; j--)
    {
        memset(temp, 0, sizeof(temp));
        if(file_name[j-1][0])
        {
            strncpy(temp, file_name[j-1], OM_DUMP_FILE_NAME_LENGTH - 1);
            temp[strlen(temp)-1] = j + '0';
            (void)sys_rename(file_name[j-1], temp);
        }
    }

    do_gettimeofday(&(txc.time));
    rtc_time_to_tm(txc.time.tv_sec, &tm);
    memset(temp, 0, sizeof(temp));
    /* Ŀ¼������ʽ:ʱ���_DUMP_���*/
    snprintf(temp, sizeof(temp), "%s%d%02d%02d%02d%02d%02d_DUMP_00", dir_name, tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
    /* ������Ŀ¼������Ŀ¼�� */
    (void)om_create_dir(temp);
    snprintf(dst_dir, OM_DUMP_FILE_NAME_LENGTH - 1, "%s/", temp);
    (void)om_close_dir(fd);

out:
    set_fs(old_fs);
    kfree(buf);
}

void om_save_file(char * file_name, void * addr, u32 len)
{
    int ret;
    int fd;
    int bytes;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    //fd = sys_creat(file_name, 0755);
    fd = sys_open(file_name, O_CREAT|O_RDWR|O_SYNC, 0755);
    if(fd < 0)
    {
        om_error("creat file %s failed\n", file_name);
        goto out;
    }

    bytes = sys_write(fd, addr, len);
    if(bytes != len)
    {
        om_error("write data to %s failed, bytes %d, len %d\n", file_name, bytes, len);
        (void)sys_close(fd);
        goto out;
    }

    (void)sys_fsync(fd);

    ret = sys_close(fd);
    if(0 != ret)
    {
        om_error("close file failed, ret = %d\n", ret);
        goto out;
    }

out:
    set_fs(old_fs);
}

void om_save_pdtcm(char * file_name)
{
    int fd;
    int bytes;
    mm_segment_t old_fs;
    u8 * data;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_creat(file_name, 0755);
    if(fd < 0)
    {
        om_fetal("creat file %s failed\n", file_name);
        set_fs(old_fs);
        return;
    }
        /* DTCM PUB */
    data = (u8 *)ioremap_wc(LPHY_BBE16_PUB_DTCM_LOAD_ADDR, LPHY_BBE16_PUB_DTCM_LOAD_SIZE);
    if(NULL == data)
    {
        om_fetal("ioremap DTCM PUB fail\n");
        goto out_fs;
    }
    else
    {
        om_fetal("ioremap_wc data = 0x%p",data);
    }
    bytes = sys_write(fd, data, LPHY_BBE16_PUB_DTCM_LOAD_SIZE);
    if(bytes != LPHY_BBE16_PUB_DTCM_LOAD_SIZE)
    {
        om_fetal("write DTCM PUB to file failed(bytes %d, len %d)\n", bytes, LPHY_BBE16_PUB_DTCM_LOAD_SIZE);
        goto out;
    }
out:
    iounmap(data);
out_fs:
    (void)sys_close(fd);
    set_fs(old_fs);

}

void om_save_mdtcm(char * file_name)
{
    int fd;
    int bytes;
    mm_segment_t old_fs;
    u8 * data;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_creat(file_name, 0755);
    if(fd < 0)
    {
        om_error("creat file %s failed\n", file_name);
        set_fs(old_fs);
        return;
    }
        /* DTCM PUB */
    data = (u8 *)ioremap_wc(LPHY_BBE16_MOD_DTCM_LOAD_ADDR, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
    if(NULL == data)
    {
        om_error("ioremap DTCM PUB fail\n");
        goto out_fs;
    }
    bytes = sys_write(fd, data, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
    if(bytes != LPHY_BBE16_MOD_DTCM_LOAD_SIZE)
    {
        om_error("write DTCM PUB to file failed(bytes %d, len %d)\n", bytes, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
        goto out;
    }
out:
    iounmap(data);
out_fs:
    (void)sys_close(fd);
    set_fs(old_fs);

}

void om_save_pitcm(char * file_name)
{
    int fd;
    int bytes;
    mm_segment_t old_fs;
    u8 * data;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_creat(file_name, 0755);
    if(fd < 0)
    {
        om_error("creat file %s failed\n", file_name);
        set_fs(old_fs);
        return;
    }
        /* DTCM PUB */
    data = (u8 *)ioremap_wc(LPHY_BBE16_PUB_ITCM_LOAD_ADDR, LPHY_BBE16_PUB_ITCM_LOAD_SIZE);
    if(NULL == data)
    {
        om_error("LPHY_BBE16_PUB_ITCM_LOAD_ADDR\n");
        goto out_fs;
    }
    bytes = sys_write(fd, data, LPHY_BBE16_PUB_ITCM_LOAD_SIZE);
    if(bytes != LPHY_BBE16_PUB_ITCM_LOAD_SIZE)
    {
        om_error("write DTCM PUB to file failed(bytes %d, len %d)\n", bytes, LPHY_BBE16_PUB_ITCM_LOAD_SIZE);
        goto out;
    }
out:
    iounmap(data);
out_fs:
    (void)sys_close(fd);
    set_fs(old_fs);

}

void om_save_mitcm(char * file_name)
{
    int fd;
    int bytes;
    mm_segment_t old_fs;
    u8 * data;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_creat(file_name, 0755);
    if(fd < 0)
    {
        om_error("creat file %s failed\n", file_name);
        set_fs(old_fs);
        return;
    }
        /* DTCM PUB */
    data = (u8 *)ioremap_wc(LPHY_BBE16_MOD_ITCM_LOAD_ADDR, LPHY_BBE16_MOD_ITCM_LOAD_SIZE);
    if(NULL == data)
    {
        om_error("ioremap DTCM PUB fail\n");
        goto out_fs;
    }
    bytes = sys_write(fd, data, LPHY_BBE16_MOD_ITCM_LOAD_SIZE);
    if(bytes != LPHY_BBE16_MOD_ITCM_LOAD_SIZE)
    {
        om_error("write DTCM PUB to file failed(bytes %d, len %d)\n", bytes, LPHY_BBE16_MOD_ITCM_LOAD_SIZE);
        goto out;
    }
out:
    iounmap(data);
out_fs:
    (void)sys_close(fd);
    set_fs(old_fs);

}


void om_save_lphy_tcm(char * file_name)
{
    int fd;
    int bytes;
    mm_segment_t old_fs;
    u8 * data;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_creat(file_name, 0755);
    if(fd < 0)
    {
        om_error("creat file %s failed\n", file_name);
        set_fs(old_fs);
        return;
    }

    /* DTCM PUB */
#ifdef BSP_CONFIG_HI3650
    data = (u8 *)om_vmap(DDR_TLPHY_IMAGE_ADDR, LPHY_BBE16_PUB_DTCM_LOAD_SIZE);
#else
    data = (u8 *)ioremap_wc(DDR_TLPHY_IMAGE_ADDR, LPHY_BBE16_PUB_DTCM_LOAD_SIZE);
#endif
    if(NULL == data)
    {
        om_error("ioremap DTCM PUB fail\n");
        goto out_fs;
    }
    bytes = sys_write(fd, data, LPHY_BBE16_PUB_DTCM_LOAD_SIZE);
    if(bytes != LPHY_BBE16_PUB_DTCM_LOAD_SIZE)
    {
        om_error("write DTCM PUB to file failed(bytes %d, len %d)\n", bytes, LPHY_BBE16_PUB_DTCM_LOAD_SIZE);
        goto out;
    }
    iounmap(data);

    /* DTCM LTE */
#ifdef BSP_CONFIG_HI3650
    data = (u8 *)om_vmap(DDR_TLPHY_IMAGE_ADDR + LPHY_BBE16_PUB_DTCM_LOAD_SIZE + LPHY_BBE16_PUB_ITCM_LOAD_SIZE, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
#else
    data = (u8 *)ioremap_wc(DDR_TLPHY_IMAGE_ADDR + LPHY_BBE16_PUB_DTCM_LOAD_SIZE + LPHY_BBE16_PUB_ITCM_LOAD_SIZE, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
#endif
    if(NULL == data)
    {
        om_error("ioremap DTCM LTE fail\n");
        goto out_fs;
    }
    bytes = sys_write(fd, data, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
    if(bytes != LPHY_BBE16_MOD_DTCM_LOAD_SIZE)
    {
        om_error("write DTCM LTE to file failed(bytes %d, len %d)\n", bytes, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
        goto out;
    }
    iounmap(data);

    /* DTCM TDS */
#ifdef BSP_CONFIG_HI3650
    data = (u8 *)om_vmap(DDR_TLPHY_IMAGE_ADDR + LPHY_BBE16_PUB_DTCM_LOAD_SIZE + LPHY_BBE16_PUB_ITCM_LOAD_SIZE + LPHY_BBE16_MOD_DTCM_LOAD_SIZE + LPHY_BBE16_MOD_ITCM_LOAD_SIZE, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
#else
    data = (u8 *)ioremap_wc(DDR_TLPHY_IMAGE_ADDR + LPHY_BBE16_PUB_DTCM_LOAD_SIZE + LPHY_BBE16_PUB_ITCM_LOAD_SIZE + LPHY_BBE16_MOD_DTCM_LOAD_SIZE + LPHY_BBE16_MOD_ITCM_LOAD_SIZE, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
#endif
    if(NULL == data)
    {
        om_error("ioremap DTCM TDS fail\n");
        goto out_fs;
    }
    bytes = sys_write(fd, data, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
    if(bytes != LPHY_BBE16_MOD_DTCM_LOAD_SIZE)
    {
        om_error("write DTCM PUB to file failed(bytes %d, len %d)\n", bytes, LPHY_BBE16_MOD_DTCM_LOAD_SIZE);
        goto out;
    }

out:
    iounmap(data);
out_fs:
    (void)sys_close(fd);
    set_fs(old_fs);
}


void om_save_sysctrl(void)
{
    u32 * field_addr;
    u32 * reg_addr;
    u32 reg_size;

    field_addr = (u32 *)bsp_dump_get_field_addr(DUMP_CP_SYSCTRL);
    if(field_addr == NULL)
    {
        om_error("SYSCTRL field addr is NULL\n");
        return;
    }

    if(DUMP_MBB == dump_get_product_type())
    {
        /* sysctrl ao */
        reg_addr = (u32 *)bsp_sysctrl_addr_byindex(sysctrl_ao);
        reg_size = 0x1000;

        /* coverity[dereference] */
        dump_memcpy(field_addr, reg_addr, reg_size >> 2);

        /* ����ͷ��Ϣ: magic_num reg_base reg_size reserved, 16�ֽ� */
        *(field_addr + (reg_size >> 2) - 4) = (u32)OM_SYSCTRL_MAGIC;
        *(field_addr + (reg_size >> 2) - 3) = (uintptr_t)bsp_sysctrl_addr_phy_byindex(sysctrl_mdm);
        *(field_addr + (reg_size >> 2) - 2) = reg_size;
        *(field_addr + (reg_size >> 2) - 1) = 0;
        /* ͷ����:0x10, �������򳤶�:0x1000 */
        field_addr = field_addr + (reg_size >> 2);

        /* sysctrl pd */
        reg_addr = (u32 *)bsp_sysctrl_addr_byindex(sysctrl_pd);
        reg_size = 0x1000;

        /* coverity[dereference] */
        dump_memcpy(field_addr, reg_addr, reg_size >> 2);
        *(field_addr + (reg_size >> 2) - 4) = (u32)OM_SYSCTRL_MAGIC;
        *(field_addr + (reg_size >> 2) - 3) = (uintptr_t)bsp_sysctrl_addr_phy_byindex(sysctrl_mdm);
        *(field_addr + (reg_size >> 2) - 2) = reg_size;
        *(field_addr + (reg_size >> 2) - 1) = 0;
        field_addr = field_addr + (reg_size >> 2);
    }

    /* sysctrl mdm */
    reg_addr = (u32 *)bsp_sysctrl_addr_byindex(sysctrl_mdm);
    reg_size = 0x1000;

    /* coverity[dereference] */
    dump_memcpy(field_addr, reg_addr, reg_size >> 2);
    *(field_addr + (reg_size >> 2) - 4) = (u32)OM_SYSCTRL_MAGIC;
    *(field_addr + (reg_size >> 2) - 3) = (uintptr_t)bsp_sysctrl_addr_phy_byindex(sysctrl_mdm);
    *(field_addr + (reg_size >> 2) - 2) = reg_size;
    *(field_addr + (reg_size >> 2) - 1) = 0;
    field_addr = field_addr + (reg_size >> 2);
}
/*****************************************************************************
* �� �� ��  : om_get_reset_info
*
* ��������  : ��ȡ��λ��Ϣ
*
* �������  :
*
*
* �������  :��
*
* �� �� ֵ  : ��
*****************************************************************************/
void om_get_reset_info(char * reset_info, u32 size)
{
    dump_head_t *dump_head = (dump_head_t*)(DUMP_ADDR+(DUMP_HEAD_ADDR-DUMP_ADDR));
    dump_except_info_t dump_except_info = {-1, -1, -1, -1, -1, -1, -1};
    dump_reset_log_t dump_reset_info = {};
    u8 *dump_base_info = NULL;
    u32 base_info_field = 0;
    unsigned long modid_offset = 0;

    /*��ȡ��λ�����Ϣ*/
    if(DUMP_CPU_COMM == dump_head->except_core)
    {
        base_info_field = DUMP_CP_BASE_INFO;
        modid_offset = DUMP_CP_MODID_OFFSET;
    }
    else if(DUMP_CPU_APP == dump_head->except_core)
    {
        base_info_field = DUMP_AP_BASE_INFO;
        modid_offset = DUMP_AP_MODID_OFFSET;
    }
    else
    {
        dump_fetal("except core error value:0x%x\n", dump_head->except_core);
    }

    dump_base_info = bsp_dump_get_field_addr(base_info_field);
    if(NULL == dump_base_info)
    {
        dump_fetal("get ddr info fail\n");
        dump_fetal("base info   field:0x%x ptr:0x%p\n", base_info_field, dump_base_info);
    }
    dump_except_info.except_core = dump_head->except_core;
    dump_except_info.voice = dump_head->voice;
    if(dump_base_info)
    {
        dump_except_info.modId = *(u32*)(dump_base_info + modid_offset);
    }
    dump_except_info.except_reason = dump_head->except_reason;
    bsp_dump_get_reset_context_and_id(&(dump_except_info.reboot_context),\
                &(dump_except_info.reboot_task),&(dump_except_info.reboot_int),(dump_head_t*)dump_head);


    dump_fetal("except_core = 0x%x\n", dump_except_info.except_core);
    dump_fetal("voice = 0x%x\n", dump_except_info.voice);
    dump_fetal("modId = 0x%x\n", dump_except_info.modId);
    dump_fetal("except_reason = 0x%x\n", dump_except_info.except_reason);
    dump_fetal("reboot_int = 0x%x\n", dump_except_info.reboot_int);
    dump_fetal("reboot_context = 0x%x\n", dump_except_info.reboot_context);
    dump_fetal("reboot_task = 0x%x\n", dump_except_info.reboot_task);
    /*������λ��Ϣ*/
    bsp_dump_parse_reset_info(&dump_reset_info, dump_except_info);
    /*��λ��Ϣд��������*/
    snprintf(reset_info, size,"brief:%s\ncmpnt:%s\nreset_reason:%s\ntask_name:%s\nmodid:0x%x\nreboot_int:0x%x\nvoice:%s\nreset_core:%s\n",
                dump_reset_info.brieftype,
                dump_reset_info.module_name,
                dump_reset_info.reboot_reson,
                dump_reset_info.task_name,
                dump_reset_info.modid,
                dump_reset_info.reboot_int,
                dump_reset_info.voice,
                dump_reset_info.reboot_core
            );

    /*����λԭ�����ΪĬ��ֵ*/
    dump_head->except_reason = 0xFF;
}

/* ���ֲ�Ʒ��̬��PHONEֱ�ӱ����ļ���MBB��Ҫ������Ŀ¼ */
void om_save_dump_file(char * dir_name, DUMP_FILE_CFG_STRU * cfg, dump_product_type_t type)
{
    char dst_path[OM_DUMP_FILE_NAME_LENGTH]  = {0};
    char file_name[OM_DUMP_FILE_NAME_LENGTH] = {0};
    u8 * data;
    int fd = -1;
    u32 is_beta = 0;
    char temp_reset_info[256] = {};

    if(dir_name == NULL || cfg == NULL)
    {
        om_fetal("dir_name or cfg is null\n");
        return;
    }

    is_beta = (u32)(bbox_check_edition() == EDITION_INTERNAL_BETA);

    fd = om_create_dir(dir_name);
    if(fd < 0)
    {
        om_fetal("creat dir fail exit\n");
        return;
    }
    om_get_dir(dir_name, cfg, type, dst_path);

    /* ����modem_dump.bin */
    if(cfg->file_list.file_bits.mdm_dump == 1)
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%smodem_dump.bin", dst_path);
        om_save_file(file_name, (u8 *)g_dump_mem_ctrl.smntn_virt_addr, g_dump_mem_ctrl.smntn_mem_size);
        om_fetal("[dump]: save %s finished\n", file_name);
    }

    /* ����lpm3_tcm.bin */
    if(cfg->file_list.file_bits.lpm3_tcm == 1 && type == DUMP_MBB)
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%slpm3_tcm.bin", dst_path);
        data = (u8 *)ioremap_wc(HI_M3TCM0_MEM_ADDR, HI_M3TCM0_MEM_SIZE + HI_M3TCM1_MEM_SIZE);
        if(NULL == data)
        {
            om_fetal("ioremap LPM3 TCM fail\n");
        }
        else
        {
            om_save_file(file_name, data, HI_M3TCM0_MEM_SIZE + HI_M3TCM1_MEM_SIZE);
            iounmap(data);
            om_fetal("[dump]: save %s finished\n", file_name);
        }
    }

    /* ����ap_etb.bin */
    if(cfg->file_list.file_bits.ap_etb == 1)
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%sap_etb.bin", dst_path);
        data = (u8 *)bsp_dump_get_field_addr(DUMP_AP_UTRACE);
        if(data != NULL)
        {
            om_save_file(file_name, data, 0x2400);
            om_fetal("[dump]: save %s finished\n", file_name);
        }
    }

    /* ����modem_etb.bin */
    if(cfg->file_list.file_bits.mdm_etb == 1)
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%smodem_etb.bin", dst_path);
        data = (u8 *)bsp_dump_get_field_addr(DUMP_CP_UTRACE);
        if(data != NULL)
        {
            om_save_file(file_name, data, 0x2400);
            om_fetal("[dump]: save %s finished\n", file_name);
        }
    }

    /* ����lphy_tcm.bin */
    if(type == DUMP_PHONE)
    {
        if(TRUE == is_beta)
        {
#ifdef BSP_CONFIG_HI3650
            if(0 == bsp_bbe_tcm_accessible())
            {
                om_fetal( "dsp is accessable\n");
                memset(file_name, 0, sizeof(file_name));
                snprintf(file_name, sizeof(file_name), "%spdtcm.bin", dst_path);
                om_save_pdtcm(file_name);
                om_fetal("[dump]: save %s finished\n", file_name);


                memset(file_name, 0, sizeof(file_name));
                snprintf(file_name, sizeof(file_name), "%smdtcm.bin", dst_path);
                om_save_mdtcm(file_name);
                om_fetal("[dump]: save %s finished\n", file_name);

                memset(file_name, 0, sizeof(file_name));
                snprintf(file_name, sizeof(file_name), "%spidtcm.bin", dst_path);
                om_save_pitcm(file_name);
                om_fetal("[dump]: save %s finished\n", file_name);

                memset(file_name, 0, sizeof(file_name));
                snprintf(file_name, sizeof(file_name), "%smitcm.bin", dst_path);
                om_save_mitcm(file_name);
                om_fetal("[dump]: save %s finished\n", file_name);

                memset(file_name, 0, sizeof(file_name));
                snprintf(file_name, sizeof(file_name), "%slphy.bin", dst_path);
                om_fetal("[dump]: save %s finished\n", file_name);
                om_save_lphy_tcm(file_name);

            }
            else
#endif
            {
                om_fetal("dsp is not accessable\n");
                memset(file_name, 0, sizeof(file_name));
                snprintf(file_name, sizeof(file_name), "%slphy.bin", dst_path);
                om_fetal("[dump]: save %s finished\n", file_name);
                om_save_lphy_tcm(file_name);
            }
        }
    }
    else
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%slphy.bin", dst_path);
        om_fetal("[dump]: save %s finished\n", file_name);
        om_save_lphy_tcm(file_name);
    }



    /* ����modem_sram.bin */
    if((cfg->file_list.file_bits.mdm_sram == 1)&&(TRUE == is_beta))
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%smodem_sram.bin", dst_path);
        om_save_file(file_name, (u8 *)g_mem_ctrl.sram_virt_addr, g_mem_ctrl.sram_mem_size);
        om_fetal("[dump]: save %s finished\n", file_name);
    }

    /* ����modem_share.bin��ֻ��PHONE���棬MBB��fastboot���� */
    if(cfg->file_list.file_bits.mdm_share == 1 && type == DUMP_PHONE && (TRUE == is_beta))
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%smodem_share.bin", dst_path);
        om_save_file(file_name, (u8 *)g_mem_ctrl.sddr_virt_addr, g_mem_ctrl.sddr_mem_size);
        om_fetal("[dump]: save %s finished\n", file_name);
    }

    /* ����modem_ddr.bin��ֻ��PHONE���棬MBB��fastboot���� */
    if(cfg->file_list.file_bits.mdm_ddr == 1 && type == DUMP_PHONE && (TRUE == is_beta))
    {
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%smodem_ddr.bin", dst_path);
        
        if(NULL == g_modem_ddr_map_addr)
        {
            om_fetal("ioremap MODEM DDR fail\n");
        }
        else
        {
            om_save_file(file_name, g_modem_ddr_map_addr, DDR_MCORE_SIZE);
            om_fetal("[dump]: save %s finished\n", file_name);
        }
    }
    /* ����reset.log�ļ�,Phone�д�,MBB�в��� */
    if(cfg->file_list.file_bits.reset_log == 1)
    {
        /*��ȡ��λ��Ϣ*/
        om_get_reset_info(temp_reset_info, 256);
        memset(file_name, 0, sizeof(file_name));
        snprintf(file_name, sizeof(file_name), "%sreset.log", dst_path);
        om_fetal("[dump]: save %s start\n", file_name);
        om_save_file(file_name, (u8 *)temp_reset_info, strlen(temp_reset_info));
        om_fetal("[dump]: save %s finished\n", file_name);
    }
}

int om_append_file(char * dir, char *filename, void * address, u32 length, u32 max_size)
{
    int ret = BSP_OK;
    int fd;
    int bytes;
    int len;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    ret = om_create_dir(dir);
    if(BSP_OK != ret)
    {
        om_error("create dir<%s> failed! ret = %d\n", dir, ret);
        goto out;
    }

    /* open file */
    ret = sys_access(filename, 0);
    if(BSP_OK != ret)
    {
        /*create file */
        fd = sys_open(filename, O_CREAT|O_RDWR, 0755);
        if(fd < 0)
        {
            om_error("open failed while mode is create, ret = %d\n", fd);
            goto out;
        }
    }
    else
    {
        fd = sys_open(filename, O_APPEND|O_RDWR, 0755);
        if(fd < 0)
        {
            om_error("open failed while mode is append, ret = %d\n", fd);
            goto out;
        }
    }

    len = sys_lseek(fd, 0, SEEK_END);
    if(BSP_ERROR == len)
    {
        om_error("seek failed! ret = %d\n", len);
        (void)sys_close(fd);
        goto out;
    }

    if (len >= max_size)
    {
        sys_close(fd);
        ret = sys_unlink(filename);
        if (OK != ret)
        {
            om_error("remove failed! ret = %d\n", ret);
            goto out;
        }

        /*���½���reset�ļ�*/
        fd = sys_open(filename, O_CREAT|O_RDWR, 0755);
        if(fd < 0)
        {
            om_error("create failed! ret = %d\n", fd);
            goto out;
        }
    }

    bytes = sys_write(fd, address, length);
    if(bytes != length)
    {
        om_error("write data failed! ret = %d\n", bytes);
        ret = BSP_ERROR;
        (void)sys_close(fd);
        goto out;
    }

    ret = sys_close(fd);
    if(0 != ret)
    {
        om_error("close failed! ret = %d\n", ret);
        ret = BSP_ERROR;
        goto out;
    }

    ret = BSP_OK;

out:
    set_fs(old_fs);
    return ret;
}

DUMP_FILE_CFG_STRU g_dump_file_cfg;
char dump_file_name[DUMP_FILE_BUTT][20] = {"MODEM_DUMP", "MODEM_SRAM", "MODEM_SHARE", "MODEM_DDR", "LPHY_TCM", "LPM3_TCM", "AP_ETB", "MODEM_ETB"};

void om_debug_help(void)
{
    om_fetal("usage:\n");
    om_fetal("\t echo cmd [param1] [param2] ... [paramN] > /sys/kernel/debug/modem_om/dump\n");
    om_fetal("cmd list:\n");
    om_fetal("\t SET_COUNT --- set max dump directory count<1-3>\n");
    om_fetal("\t SET_FILE  --- set dump file list\n");
    om_fetal("\t GET_COUNT --- get present file list to be saved\n");
    om_fetal("\t GET_FILE  --- get present dump directory count\n");
    om_fetal("\t FLUSH     --- save config to nv\n");
    om_fetal("file list:\n");
    om_fetal("\t [MODEM_DUMP],[MODEM_SRAM],[MODEM_SHARE],[MODEM_DDR],[LPHY_TCM],[LPM3_TCM],[AP_ETB],[MODEM_ETB]\n");
}

int om_debug_open(struct inode *inode, struct file *filp)
{
    filp->private_data = inode->i_private;
    return BSP_OK;
}

static ssize_t om_debug_read(struct file *file, char __user *ubuf, size_t cnt, loff_t *ppos)
{
    om_debug_help();
    return BSP_OK;
}

static ssize_t om_debug_write(struct file *filp, const char __user *ubuf, size_t cnt, loff_t *ppos)
{
    char buf[128] = {0};
    char cmd_buf[20] = {0};
    char param_buf[DUMP_FILE_BUTT][20];
    int  file_cnt;
    u32  file_value = 0;
    u32  i,j;
    ssize_t ret = cnt;

    cnt = (cnt > 127) ? 127 : cnt;
    if(copy_from_user(buf, ubuf, cnt))
    {
        om_error("copy from user fail\n");
        ret = -EFAULT;
        goto out;
    }
    buf[cnt] = 0;

    /* �����쳣Ŀ¼���� */
    if(0 == strncmp(buf, "SET_COUNT", strlen("SET_COUNT")))
    {
        /* coverity[secure_coding] */
        (void)sscanf(buf, "%s %d", cmd_buf, &file_cnt);/* [false alarm]:fortify */
        if(file_cnt > 3 || file_cnt < 1)
        {
            om_error("invalid file cnt %d\n", file_cnt);
        }
        else
        {
            g_dump_file_cfg.file_cnt = (u32)file_cnt;
        }
        goto out;
    }

    /* ���ô������쳣�ļ��б� */
    if(0 == strncmp(buf, "SET_FILE", strlen("SET_FILE")))
    {

        /* coverity[secure_coding] */
        (void)sscanf(buf, "%s %s %s %s %s %s %s %s %s", cmd_buf, param_buf[0], param_buf[1], param_buf[2], param_buf[3],/* [false alarm]:fortify */
                param_buf[4], param_buf[5], param_buf[6], param_buf[7]);/* [false alarm]:fortify */
        for(i=0; i<DUMP_FILE_BUTT; i++)
        {
            for(j=0; j<DUMP_FILE_BUTT; j++)
            {
                if(0 == strncmp(param_buf[j], dump_file_name[i], strlen(dump_file_name[i])))
                {
                    printk("set file %s\n", dump_file_name[i]);
                    file_value |= 1 << i;
                    break;
                }
            }
        }

        g_dump_file_cfg.file_list.file_value = file_value;

        goto out;
    }

    /* ��ȡ�������쳣�ļ��б� */
    if(0 == strncmp(buf, "GET_FILE", strlen("GET_FILE")))
    {
        printk("dump file list to be saved:\n");
        for(i=0; i<DUMP_FILE_BUTT; i++)
        {
            if(g_dump_file_cfg.file_list.file_value & (1 << i))
            {
                printk("%s ", dump_file_name[i]);
            }
        }
        printk("\n");

        goto out;
    }

    /* ��ȡ�������쳣�ļ����� */
    if(0 == strncmp(buf, "GET_COUNT", strlen("GET_COUNT")))
    {
        printk("dump directory count: %u\n", g_dump_file_cfg.file_cnt);
        goto out;
    }

    /* �������� */
    if(0 == strncmp(buf, "FLUSH", strlen("FLUSH")))
    {
        printk("[om]: save config to nv\n");
        if(BSP_OK != bsp_nvm_write(NV_ID_DRV_DUMP_FILE, (u8 *)&g_dump_file_cfg, sizeof(DUMP_FILE_CFG_STRU)))
        {
            om_error("write nv 0x%x fail\n", NV_ID_DRV_DUMP_FILE);
        }
        goto out;
    }

out:
    return ret;
}

long om_debug_ioctl(struct file *file, unsigned int cmd, unsigned long arg)
{
    DUMP_FILE_CFG_STRU cfg;
    long ret = BSP_OK;

    if(copy_from_user(&cfg, (u8 *)arg, sizeof(DUMP_FILE_CFG_STRU)))
    {
        om_error("copy from user fail\n");
        ret = BSP_ERROR;
        goto out;
    }

    switch(cmd)
    {
        case DUMP_CMD_SET_COUNT:
            g_dump_file_cfg.file_cnt = cfg.file_cnt;
            break;

        case DUMP_CMD_SET_FILE:
            g_dump_file_cfg.file_list.file_value = cfg.file_list.file_value;
            break;

        case DUMP_CMD_FLUSH:
            printk("[om]: save config to nv\n");
            if(BSP_OK != bsp_nvm_write(NV_ID_DRV_DUMP_FILE, (u8 *)&g_dump_file_cfg, sizeof(DUMP_FILE_CFG_STRU)))
            {
                om_error("write nv 0x%x fail\n", NV_ID_DRV_DUMP_FILE);
            }
            break;

        default:
            om_error("invalid cmd id 0x%x\n", cmd);
            ret = BSP_ERROR;
            goto out;
    }
    ret = BSP_OK;

out:
    return ret;
}

static const struct file_operations om_debug_fops = {
    .open       = om_debug_open,
    .read       = om_debug_read,
    .write      = om_debug_write,
    .unlocked_ioctl = om_debug_ioctl,
};
void dump_memmap_modem_ddr(void)
{
    dump_product_type_t type = dump_get_product_type();

    dump_fetal("mdm_ddr= %d,type=%d\n",g_dump_file_cfg.file_list.file_bits.mdm_ddr,type);
    if(g_dump_file_cfg.file_list.file_bits.mdm_ddr == 1 && type == DUMP_PHONE )
    {
#ifdef BSP_CONFIG_HI3650 
        g_modem_ddr_map_addr = (u8*)om_vmap(DDR_MCORE_ADDR, DDR_MCORE_SIZE);
#else     
        g_modem_ddr_map_addr = (u8 *)ioremap_wc(DDR_MCORE_ADDR, DDR_MCORE_SIZE);
#endif
        if(g_modem_ddr_map_addr == NULL)
        {
            dump_fetal("map g_modem_ddr_map_addr fail\n");
        }
        else
        {
            dump_fetal("g_modem_ddr_map_addr = 0x%p \n",g_modem_ddr_map_addr);  
        }
    }
}

int bsp_om_debug_init(void)
{
    struct dentry * d_file;

    if(BSP_OK != bsp_nvm_read(NV_ID_DRV_DUMP_FILE, (u8 *)&g_dump_file_cfg, sizeof(DUMP_FILE_CFG_STRU)))
    {
        g_dump_file_cfg.file_cnt = 2;
        g_dump_file_cfg.file_list.file_bits.mdm_dump = 0x1;
        g_dump_file_cfg.file_list.file_bits.mdm_share= 0x1;
        g_dump_file_cfg.file_list.file_bits.mdm_ddr  = 0x1;
        g_dump_file_cfg.file_list.file_bits.mdm_etb  = 0x1;
        g_dump_file_cfg.file_list.file_bits.lphy_tcm = 0x1;
        g_dump_file_cfg.file_list.file_bits.lpm3_tcm = 0x1;
        g_dump_file_cfg.file_list.file_bits.ap_etb   = 0x1;
        g_dump_file_cfg.file_list.file_bits.reset_log= 0x1;

        om_error("read nv 0x%x fail, use default config\n", NV_ID_DRV_DUMP_FILE);
    }

    d_file = debugfs_create_dir("modem_om", NULL);
    if(!d_file)
    {
        om_error("create debugfs dir modem_om fail\n");
        return BSP_ERROR;
    }

    if(!debugfs_create_file("dump", 0644, d_file, NULL, &om_debug_fops))
    {
        om_error("create debugfs file modem_om/dump file\n");
        return BSP_ERROR;
    }
    dump_memmap_modem_ddr();
    return BSP_OK;
}

bool bsp_om_fs_check(void)
{
    int fd;
    mm_segment_t old_fs;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    fd = sys_access(OM_ROOT_DIR, 0); //F_OK, ����ļ��Ƿ����
    if(0 != fd)
    {
        /*bsp_trace(BSP_LOG_LEVEL_ERROR, BSP_MODU_OM, "[BSP_OM]:bsp_om_fs_check file system is invalid\n");*/
        set_fs(old_fs);
        return false;
    }

    om_fetal("om fs is ready\n");
    set_fs(old_fs);

    return true;
}

void bsp_om_save_dump_backup(char * dir_name, u8 * addr, u32 len, u32 type)
{
    DUMP_FILE_CFG_STRU cfg;

    if(DUMP_MBB == type)
    {
        /* �����󱣴棬ֻ����modem_dump.bin */
        cfg.file_list.file_bits.mdm_dump = 0x1;
        cfg.file_cnt = g_dump_file_cfg.file_cnt;
        om_save_dump_file(dir_name, &cfg, type);
    }
    else
    {
        om_error("dump should save file before system reboot\n");
    }
}

void bsp_om_save_loop_file(char * dir_name, u32 nve_value, u32 type)
{
    /*TODO: set file saving config by nve_value*/
    om_save_dump_file(dir_name, &g_dump_file_cfg, type);
}

int bsp_om_append_file(char *filename, void * address, u32 length, u32 max_size)
{
    if(filename == NULL || address == NULL)
    {
        om_error("invalid params\n");
        return BSP_ERROR;
    }

    return om_append_file(OM_LOG_PATH, filename, address, length, max_size);
}

void bsp_om_save_reboot_log(const char * func_name, const void* caller)
{
    struct timex txc;
    struct rtc_time tm = {0,};
    char log_buff[200] = {0};
    char temp[30] = {0};

    do_gettimeofday(&(txc.time));
    rtc_time_to_tm(txc.time.tv_sec, &tm);
    snprintf(temp, sizeof(temp), "%d-%02d-%02d %02d:%02d:%02d", tm.tm_year+1900, tm.tm_mon+1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    /* coverity[overrun-buffer-val] */
    om_trace((char*)log_buff, "system reboot reason: NORMAL_RESET A CORE, FUNC:%s, caller:%p, TIME:%s\n", func_name, caller, temp);
    om_append_file(OM_DUMP_PATH, OM_RESET_LOG, (void*)log_buff, strlen(log_buff), OM_RESET_LOG_MAX);
}

void bsp_om_save_resetlog(void)
{
    om_append_file(OM_DUMP_PATH, OM_RESET_LOG, (void*)g_ResetLogBuffer, strlen(g_ResetLogBuffer), OM_RESET_LOG_MAX);

    return;
}

void bsp_om_record_resetlog(u8 * dump_addr)
{
    s8 *reason;
    s8 *core;
    dump_base_info_t *base_info;

    dump_head_t        *dump_head        = (dump_head_t*)(dump_addr+(DUMP_HEAD_ADDR-DUMP_ADDR));
    dump_global_info_t *dump_global_info = (dump_global_info_t*)(dump_addr+(DUMP_GLOBAL_INFO_ADDR-DUMP_ADDR));

#define NORMAL_EXCH         "Software"
#define ARM_EXCH            "ARM"
#define PMU_EXCH            "PMU"
#define WDT_EXCH            "WDT"
#define CRASH_EXCH          "CRASH"
#define UNDEF_EXCH          "UNDEF"
#define NORMAL_POWER_ON     "NORMAL POWER ON"
#define NORMAL_RESET        "NORMAL RESET"
#define UNKNOW              "UNKNOW"

#define CCORE_REBOOT        "C CORE "
#define ACORE_REBOOT        "A CORE "
#define MCORE_REBOOT        "M CORE "
#define UNKNOW_CORE_REBOOT  "CORE UNKNOW "

    if((DUMP_START_EXCH == dump_global_info->internal_info.app_internal.start_flag)
        || (DUMP_START_EXCH == dump_global_info->internal_info.comm_internal.start_flag)
        || (DUMP_CPU_LPM3 == dump_head->except_core)
        || (DUMP_START_REBOOT == dump_global_info->internal_info.app_internal.start_flag)
        || (DUMP_START_REBOOT == dump_global_info->internal_info.comm_internal.start_flag)
        || (DUMP_START_REBOOT == dump_global_info->internal_info.m3_internal.start_flag))
    {
        /* �ȼ��ACORE */
        if(DUMP_REASON_NORMAL == dump_head->except_reason)
        {
            reason = NORMAL_EXCH;
        }
        else if(DUMP_REASON_WDT == dump_head->except_reason)
        {
            reason = WDT_EXCH;
        }
        else if(DUMP_REASON_ARM == dump_head->except_reason)
        {
            reason = ARM_EXCH;
        }
        else if(DUMP_REASON_PMU== dump_head->except_reason)
        {
            reason = PMU_EXCH;
        }
        else if(DUMP_REASON_REBOOT == dump_head->except_reason)
        {
            reason = NORMAL_RESET;
        }
        else if(DUMP_REASON_UNDEF == dump_head->except_reason)
        {
            reason = UNDEF_EXCH;
        }
        else
        {
            reason = UNKNOW;
        }

        if(DUMP_CPU_COMM == dump_head->except_core)
        {
            core = CCORE_REBOOT;
            base_info = (dump_base_info_t*)(dump_addr+(DUMP_AREA_CP_STATIC_ADDR -DUMP_ADDR));
        }
        else if(DUMP_CPU_APP == dump_head->except_core)
        {
            core = ACORE_REBOOT;
            base_info = (dump_base_info_t*)(dump_addr+(DUMP_AREA_AP_STATIC_ADDR-DUMP_ADDR));
        }
        else if(DUMP_CPU_LPM3 == dump_head->except_core)
        {
             core = MCORE_REBOOT;
            base_info = (dump_base_info_t*)(dump_addr+(DUMP_AREA_LPM3_STATIC_ADDR-DUMP_ADDR));
        }
        else
        {
            core = UNKNOW_CORE_REBOOT;
            base_info = NULL;
        }
    }
    else if((DUMP_START_CRASH == dump_global_info->internal_info.app_internal.start_flag)
        && (DUMP_START_CRASH ==  dump_global_info->internal_info.comm_internal.start_flag))
    {
        reason = CRASH_EXCH;
        core = UNKNOW_CORE_REBOOT;
        base_info = NULL;
    }
    else
    {
        // �����ϵ硣
        reason = NORMAL_POWER_ON;
        core = NULL;
        base_info = NULL;
    }

    if(NULL == core)
    {
        (void)om_trace((char*)g_ResetLogBuffer, "system reboot reason: %s %s\n",reason, "");
        om_fetal("system reboot reason: %s %s\r\n",reason, "");
    }
    else
    {
        if(NULL == base_info)
        {

            (void)om_trace((char*)g_ResetLogBuffer,"system reboot reason: %s %s\r\n", reason, core);
            om_fetal("system reboot reason: %s %s\r\n", reason, core);
        }
        else
        {

            (void)om_trace((char*)g_ResetLogBuffer,
                            "system reboot reason: %s %s, tick: 0x%x, systemError para: ModId=0x%x, Arg1=0x%x, Arg2=0x%x \r\n",
                            reason, core,
                            dump_head->except_time,
                            base_info->modId,
                            base_info->arg1,
                            base_info->arg2);
            om_fetal("system reboot reason: %s %s, tick: 0x%x, systemError para: ModId=0x%x, Arg1=0x%x, Arg2=0x%x \r\n",
                            reason, core,
                            dump_head->except_time,
                            base_info->modId,
                            base_info->arg1,
                            base_info->arg2);
        }
    }

    /* �������ػ�������������ǰ����log */
    if(DUMP_REASON_REBOOT != dump_head->except_reason)
    {
        bsp_om_save_resetlog();
    }

    return;
}

void print2file(char* filename, char *fmt,...)
{
    /*lint -save -e40 -e522 */
    va_list arglist;
    /*lint -restore +e40 +e522 */
    va_start(arglist, fmt);
    vsnprintf(g_OmLogBuffer, 256, fmt, arglist); /* [false alarm]:����Fortify���� */
    va_end(arglist);

    bsp_om_append_file(filename, (void*)g_OmLogBuffer, strlen(g_OmLogBuffer), OM_PRINT_LOG_MAX);

    return;
}

s32 om_save_cp_task_name(int fd)
{
    u8 * field_addr;
    u32  task_id[127];  /* C�����������:127 */
    u32  task_cnt;
    int  i;
    int  j;
    int  len;
    char record_buf[50];

    field_addr = bsp_dump_get_field_addr(DUMP_CP_ALLTASK);
    if(field_addr == NULL)
    {
        om_error("get CP task name field fail\n");
        return BSP_ERROR;
    }

    len = snprintf(record_buf, sizeof(record_buf), "********CP TASK NAME BEGIN********\n");
    if(len != sys_write(fd, record_buf, len))
    {
        om_error("sys write cp head fail\n");
        return BSP_ERROR;
    }

    task_cnt = *((u32 *)field_addr + 3)/4;
    /* ƫ��10�ֽڣ�ȥ������ͷ */
    field_addr += 0x10;

    memset((u8 *)task_id, 0, sizeof(u32)*127);
    for(i=0; i<(int)task_cnt; i++)
    {
        /* task id�Ƿ��Ѵ��� */
        for(j=0; j<i; j++)
        {
            if(task_id[j] == *(u32 *)field_addr)
            {
                break;
            }
        }

        /* task id�����ڣ����task id��Ϣ */
        if(i == j)
        {
            task_id[i] = *(u32 *)field_addr;
            len = snprintf(record_buf, sizeof(record_buf), "id: %-8x, name: %s\n", task_id[i], field_addr + 4);
            if(len != sys_write(fd, record_buf, len))
            {
                om_error("sys write task id <0x%x> fail\n", task_id[i]);
                return BSP_ERROR;
            }
        }

        field_addr += 0x10;
    }

    len = snprintf(record_buf, sizeof(record_buf), "********CP TASK NAME END**********\n");
    if(len != sys_write(fd, record_buf, len))
    {
        om_error("sys write cp tail fail\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}
#if 0
/*lint --e{750}*/
#define GET_PPID(taskTCB)  ((((struct task_struct *)taskTCB)->pid & 0xffff)| ((((struct task_struct *)taskTCB)->real_parent->pid & 0xffff)<< 16))
/*lint -restore */
#endif

s32 om_save_ap_task_name(int fd)
{
    struct task_struct * task_tcb = NULL;
    u32  pid_ppid = 0;
    int  len;
    char record_buf[50];

    len = snprintf(record_buf, sizeof(record_buf), "********AP TASK NAME BEGIN********\n");
    if(len != sys_write(fd, record_buf, len))
    {
        om_error("sys write ap head fail\n");
        return BSP_ERROR;
    }

    len = snprintf(record_buf, sizeof(record_buf), "id: %-8x, name: swapper\n", 0);
    if(len != sys_write(fd, record_buf, len))
    {
        om_error("sys write task id <0x0> fail\n");
        return BSP_ERROR;
    }

    for_each_process(task_tcb)
    {
        pid_ppid = (((struct task_struct *)task_tcb)->pid & 0xffff) | ((((struct task_struct *)task_tcb)->real_parent->pid & 0xffff)<< 16);
        len = snprintf(record_buf, sizeof(record_buf), "id: %-8x, name: %s\n", pid_ppid, task_tcb->comm);
        if(len != sys_write(fd, record_buf, len))
        {
            om_error("sys write task id <0x%x> fail\n", pid_ppid);
            return BSP_ERROR;
        }
    }

    len = snprintf(record_buf, sizeof(record_buf), "********AP TASK NAME END**********\n");
    if(len != sys_write(fd, record_buf, len))
    {
        om_error("sys write ap tail fail\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}

/* ����A/C��������������ID��Ӧ��ϵ��bit 0:acore, bit1: ccore */
void om_save_task_name(u32 core_opt)
{
    int  fd;
    mm_segment_t old_fs;
    u32  core_mask = 0;

    old_fs = get_fs();
    set_fs(KERNEL_DS);

    core_mask |= 1 << OM_ACORE;
    core_mask |= 1 << OM_CCORE;
    if((core_opt & core_mask) == 0)
    {
        om_error("invalid core opt<%u>\n", core_opt);
        goto out;
    }

    if(BSP_OK != om_create_dir(OM_LOG_PATH))
    {
        om_error("create dir<%s> fail\n", OM_LOG_PATH);
        goto out;
    }

    fd = sys_open(OM_TASK_NAME, O_CREAT|O_RDWR|O_TRUNC, 0755);
    if(fd < 0)
    {
        om_error("creat file %s fail,error code id %d\n", OM_TASK_NAME,fd);
        goto out;
    }

    if(core_opt & (1 << OM_CCORE))
    {
        if(BSP_OK != om_save_cp_task_name(fd))
        {
            om_error("save cp task name fail\n");
            sys_close(fd);
            goto out;
        }
    }

    /* PHONE�ϲ�����AP������ */
    if((core_opt & (1 << OM_ACORE)) && (DUMP_MBB == dump_get_product_type()))
    {
        if(BSP_OK != om_save_ap_task_name(fd))
        {
            om_error("save ap task name fail\n");
            sys_close(fd);
            goto out;
        }
    }

    (void)sys_fsync(fd);
    (void)sys_close(fd);
out:
    set_fs(old_fs);
}

int om_task_name_proc(void * data)
{
    /* �ȴ�20s֮�󱣴�һ�� */
    msleep(20000);
    om_save_task_name((1 << OM_ACORE) + (1 << OM_CCORE));
    /* C�˻�������1���Ӻ�ˢ��һ����������A���ڵȴ�1���Ӻ��ٴα��� */
    msleep(60000);
    om_save_task_name((1 << OM_ACORE) + (1 << OM_CCORE));

    return BSP_OK;
}

int om_task_name_init(void)
{
    struct task_struct * pid;

    pid = (struct task_struct *)kthread_run(om_task_name_proc, 0, "om_task_name");
    if (IS_ERR((void*)pid))
    {
        om_error("creat task name saving task fail\n");
        return BSP_ERROR;
    }

    return BSP_OK;
}

late_initcall(om_task_name_init);

