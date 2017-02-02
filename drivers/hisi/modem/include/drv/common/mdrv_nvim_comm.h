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

#ifndef __MDRV_NVIM_COMMON_H__
#define __MDRV_NVIM_COMMON_H__

#ifdef __cplusplus
extern "C"
{
#endif
#include <product_config.h>



/******************************** NV return value, need to be cleared *********************************/
#define NV_OK                           0
#define NV_ID_NOT_EXIST                 1
#define NV_BUFFER_TOO_LONG              2
#define NV_BUFFER_NOT_EXIST             4
#define NV_WRITE_SECURE_FAIL            18
#define NV_RESTORE_RUNNING              0x5A5A55AA


/******************************** NV恢复表类型 *********************************/
enum NV_RESUME_ITEM
{
    NV_MANUFACTURE_ITEM = 0,
    NV_USER_ITEM,
    NV_SECURE_ITEM,
    NV_ITEM_BUTT
};
typedef unsigned long NV_RESUME_ITEM_ENUM_UINT32;

/*****************************************************************************
 *  结构名    : NV_LIST_INFO_STRU
 *  协议表格  :
 *  ASN.1描述 :
 *  结构说明  : 获取NV列表信息
 ******************************************************************************/
typedef struct tag_NV_LIST_INFO_STRU
{
	unsigned short usNvId;                  /*NVID值*/
	unsigned char  ucNvModemNum;            /*NV是否存在多份*/
	unsigned char  ucRsv;
}NV_LIST_INFO_STRU;  /*back*/

/* 获取NV项数量 */
unsigned int mdrv_nv_get_nvid_num(void);

/* 获取NV列表 */
unsigned int mdrv_nv_get_nvid_list(NV_LIST_INFO_STRU *pstNvIdList);

/* 读不同Modem NV项数据 */
unsigned int mdrv_nv_readex(unsigned int modemid, unsigned int itemid, void *pdata, unsigned int ulLength);

/* 写不同Modem NV项数据 */
unsigned int mdrv_nv_writeex(unsigned int modemid, unsigned int itemid,void *pdata, unsigned int ulLength);

/* 读NV项数据 */
unsigned int mdrv_nv_read_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);

/* 写部分NV项数据 */
unsigned int mdrv_nv_write_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);

/* 将内存中的nv数据刷到flash 文件系统中 */
unsigned int mdrv_nv_flush(void);

/* 获取NV长度 */
unsigned int mdrv_nv_get_length(unsigned int itemid, unsigned int *pulLength);

/* 读NV项数据 */
unsigned int mdrv_nv_read(unsigned int itemid, void *pdata, unsigned int ulLength);

/* 写NV项数据 */
unsigned int mdrv_nv_write(unsigned int itemid, void *pdata, unsigned int ulLength);

/* 读NV项数据 */
unsigned int mdrv_nv_readpart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);

/* 写部分NV项数据 */
unsigned int mdrv_nv_writepart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength);

/* 获取NV列表 */
unsigned int mdrv_nv_get_resume_nvid_list(unsigned int enNvItem, unsigned short *pusNvList, unsigned int ulNvNum);

/* 获取需要恢复恢复NV项数量 */
unsigned int mdrv_nv_get_resume_nvid_num(unsigned int enNvItem);

/* 备份NV数据 */
unsigned int mdrv_nv_backup(void);

/* 恢复结果检查 */
unsigned int mdrv_nv_restore_result(void);

/* 恢复生产NV项 */
unsigned int mdrv_nv_restore(void);

/*备份出厂NV项*/
unsigned int mdrv_nv_backup_factorynv(void);

/*恢复出厂NV项*/
unsigned int mdrv_nv_revert_factorynv(void);

/************************************适配GU对外接口*****************************************/
unsigned int mdrv_nv_revert_manufacturnv(void);

#define NV_GetNVIdListNum()		                    mdrv_nv_get_nvid_num()
#define NV_GetNVIdList(list)		                mdrv_nv_get_nvid_list(list)
#define NV_ReadEx(modemid, id, item, len)	        mdrv_nv_readex(modemid, id, item, len)
#define NV_WriteEx(modemid, id, item, len) 	        mdrv_nv_writeex(modemid, id, item, len)
#define NV_ReadPartEx(modemid, id, off, item, len)	mdrv_nv_read_partex(modemid, id, off, item, len)
#define NV_WritePartEx(modemid, id, off, item, len)	mdrv_nv_write_partex(modemid, id, off, item, len)
#define NV_Flush()	                                mdrv_nv_flush()
#define NV_GetLength(id, len)	                    mdrv_nv_get_length(id, len)
#define NV_GetResumeNvIdList(item, list, num)       mdrv_nv_get_resume_nvid_list(item, list, num)
#define NV_GetResumeNvIdNum(item)	                mdrv_nv_get_resume_nvid_num(item)
#define NV_Backup()	                                mdrv_nv_backup()
#define NV_RestoreResult()	                        mdrv_nv_restore_result()
#define NV_Restore()	                            mdrv_nv_restore()
#define NV_RestoreAll()                             mdrv_nv_restore()
#define NV_QueryRestoreResult()                     mdrv_nv_restore_result()
#define NVM_BackUpFNV()                             mdrv_nv_backup_factorynv()
#define NVM_RevertFNV()                             mdrv_nv_revert_factorynv()
#define NV_RestoreManufactureDefault()              mdrv_nv_revert_factorynv()
#define NV_RestoreManufacture()                     mdrv_nv_revert_manufacturnv()
#define NV_SpecialNvIdBackup(a,b,c)                 (0)
#define NV_RestoreManufactureExt()                  (1)
#define NV_BackupCheck()                            (0)

#if defined (INSTANCE_1)
#define NV_Read(id, item, len)	                    mdrv_nv_readex(MODEM_ID_1, id, item, len)
#define NV_Write(id, item, len)                     mdrv_nv_writeex(MODEM_ID_1, id, item, len)
#define NV_ReadPart(id, off, item, len)             mdrv_nv_read_partex(MODEM_ID_1, id, off, item, len)
#define NV_WritePart(id, off, item, len)            mdrv_nv_write_partex(MODEM_ID_1, id, off, item, len)
#elif defined (INSTANCE_2)
#define NV_Read(id, item, len)	                    mdrv_nv_readex(MODEM_ID_2, id, item, len)
#define NV_Write(id, item, len)                     mdrv_nv_writeex(MODEM_ID_2, id, item, len)
#define NV_ReadPart(id, off, item, len)             mdrv_nv_read_partex(MODEM_ID_2, id, off, item, len)
#define NV_WritePart(id, off, item, len)            mdrv_nv_write_partex(MODEM_ID_2, id, off, item, len)
#else
#define NV_Read(id, item, len)	                    mdrv_nv_readex(MODEM_ID_0, id, item, len)
#define NV_Write(id, item, len)                     mdrv_nv_writeex(MODEM_ID_0, id, item, len)
#define NV_ReadPart(id, off, item, len)             mdrv_nv_read_partex(MODEM_ID_0, id, off, item, len)
#define NV_WritePart(id, off, item, len)            mdrv_nv_write_partex(MODEM_ID_0, id, off, item, len)
#endif


/************************************适配TL对外接口*****************************************/
#define NVM_Flush()                                 mdrv_nv_flush()
#define NVM_GetItemLength(id, len)	                mdrv_nv_get_length(id, len)
#define NVM_UpgradeBackup(uloption)	                mdrv_nv_backup()
#define NVM_UpgradeRestore()	                    mdrv_nv_restore()

#if defined (INSTANCE_1)
#define NVM_Read(id, item, len)                     mdrv_nv_readex(MODEM_ID_1, id, item, len)
#define NVM_Write(id, item, len)                    mdrv_nv_writeex(MODEM_ID_1, id, item, len)
#elif defined (INSTANCE_2)
#define NVM_Read(id, item, len)                     mdrv_nv_readex(MODEM_ID_2, id, item, len)
#define NVM_Write(id, item, len)                    mdrv_nv_writeex(MODEM_ID_2, id, item, len)
#else
#define NVM_Read(id, item, len)                     mdrv_nv_readex(MODEM_ID_0, id, item, len)
#define NVM_Write(id, item, len)                    mdrv_nv_writeex(MODEM_ID_0, id, item, len)
#endif


#ifdef __cplusplus
}
#endif
#endif //__MDRV_NVIM_COMMON_H__
