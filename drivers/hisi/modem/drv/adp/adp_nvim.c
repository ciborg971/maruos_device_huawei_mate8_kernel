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

/*lint -save -e537*/
#include "bsp_nvim.h"
#include "mdrv_nvim.h"
#include "drv_comm.h"
#include "nv_comm.h"
#include "NVIM_ResumeId.h"
/*lint -restore +e537*/

/*lint -save -e958 -e438*/

#ifdef __cplusplus
extern "C"
{
#endif

#define  NV_RESULT_CODE            0xffff

#ifdef CONFIG_NVIM

/*****************************************************************************
* 函 数 名  : mdrv_nv_get_nvid_num
*
* 功能描述  : 获取NV项数量
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_get_nvid_num()
{
    return bsp_nvm_get_nv_num();
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_get_nvid_list
*
* 功能描述  : 获取NV列表
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_get_nvid_list(NV_LIST_INFO_STRU *pstNvIdList)
{
    if(pstNvIdList == NULL)
    {
        return NV_ERROR;
    }
    return bsp_nvm_get_nvidlist(pstNvIdList);

}

/*****************************************************************************
* 函 数 名  : mdrv_nv_readex
*
* 功能描述  : 读不同Modem NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_readex(unsigned int modemid, unsigned int itemid, void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;
    return bsp_nvm_dcread(card_id, itemid,(BSP_U8*)pdata,ulLength);

}

/*****************************************************************************
* 函 数 名  : mdrv_nv_writeex
*
* 功能描述  : 写不同Modem NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_writeex(unsigned int modemid, unsigned int itemid,void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcwrite(card_id, itemid,(BSP_U8*)pdata,ulLength);

}

/*****************************************************************************
* 函 数 名  : mdrv_nv_read_partex
*
* 功能描述  : 读NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_read_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcreadpart(card_id,itemid,ulOffset,(BSP_U8*)pdata,ulLength);

}

/*****************************************************************************
* 函 数 名  : mdrv_nv_write_partex
*
* 功能描述  : 写部分NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_write_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    BSP_U32 card_id = 0;

    if(modemid == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(modemid == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else if(modemid == MODEM_ID_2)
        card_id = NV_USIMM_CARD_3;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcwritepart(card_id,itemid,ulOffset,(BSP_U8*)pdata,ulLength);
}


/*****************************************************************************
* 函 数 名  : mdrv_nv_flush
*
* 功能描述  : 将内存中的nv数据刷到flash 文件系统中
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_flush()
{
   return bsp_nvm_flush() & NV_RESULT_CODE;
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_get_length
*
* 功能描述  : 获取NV长度
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_get_length(unsigned int itemid, unsigned int *pulLength)
{
    BSP_U32 len = 0;
    BSP_U32 ret = 0;

    ret = bsp_nvm_get_len(itemid,&len);
    if(ret)
    {
        return ret;
    }
    *pulLength = len;
    return 0;
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_read
*
* 功能描述  : 读NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_read(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_read(itemid,pdata,ulLength);
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_write
*
* 功能描述  : 写NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_write(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_write(itemid,pdata,ulLength);
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_readpart
*
* 功能描述  : 读部分NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_readpart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_readpart(itemid,ulOffset,pdata,ulLength);
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_writepart
*
* 功能描述  : 写部分NV项数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_writepart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return bsp_nvm_writepart(itemid,ulOffset,pdata,ulLength);
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_get_resume_nvid_list
*
* 功能描述  : 获取NV列表
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_get_resume_nvid_list(unsigned int enNvItem, unsigned short *pusNvList, unsigned int ulNvNum)
{
    if (NULL == pusNvList)
    {
        return NV_ERROR;
    }

    if (ulNvNum < NV_GetResumeNvIdNum(enNvItem))
    {
        return NV_ERROR;
    }

    if (NV_MANUFACTURE_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeManufactureIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    if (NV_USER_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeUserIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    if (NV_SECURE_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeSecureIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    return NV_OK;

}

/*****************************************************************************
* 函 数 名  : mdrv_nv_get_resume_nvid_num
*
* 功能描述  : 获取需要恢复恢复NV项数量
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_get_resume_nvid_num(unsigned int enNvItem)
{
    return bsp_nvm_getRevertNum( enNvItem);
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_backup
*
* 功能描述  :  备份NV数据
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_backup()
{
    return bsp_nvm_backup(NV_FLAG_NEED_CRC) & NV_RESULT_CODE;
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_restore_result
*
* 功能描述  :  恢复结果检查
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_restore_result()
{
    BSP_U32 ret = NV_ERROR;
    BSP_U16 resume_flag = 0;

    ret = bsp_nvm_read(NV_ID_DRV_RESUME_FLAG,(BSP_U8*)&resume_flag,sizeof(BSP_U16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return NV_ERROR;
    }
    return 0;
}

/*****************************************************************************
* 函 数 名  : mdrv_nv_restore
*
* 功能描述  :  恢复生产NV项
*
* 输入参数  :
* 输出参数  : 无
*
* 返 回 值  : OK
*
* 修改记录  : Yangzhi create
*
*****************************************************************************/
unsigned int mdrv_nv_restore()
{
    return bsp_nvm_revert() & NV_RESULT_CODE;
}

unsigned int mdrv_nv_backup_factorynv()
{
    return bsp_nvm_update_default();
}

unsigned int mdrv_nv_revert_factorynv()
{
    return bsp_nvm_revert_default();
}

unsigned int mdrv_nv_revert_manufacturnv()
{
    return bsp_nvm_revert_manufacture() & NV_RESULT_CODE;
}

#if 0
BSP_U32 NVM_Flush(BSP_VOID)
{
    return bsp_nvm_flush() & NV_RESULT_CODE;
}



BSP_U32 NVM_UpgradeBackup(BSP_U32 uloption)
{
    return bsp_nvm_backup();
}


BSP_U32 NVM_UpgradeRestore(BSP_VOID)
{
    return bsp_nvm_revert();
}


BSP_U32 NVM_GetItemLength(BSP_U16 ulid, BSP_U32 * pusitemlength)
{
    BSP_U32 len = 0;
    BSP_U32 ret = 0;
    ret = bsp_nvm_get_len(ulid,&len);
    if(ret)
    {
        return NV_ERROR;
    }
    *pusitemlength = len;
    return 0;
}


BSP_U32 NVM_SetFactoryDefault(BSP_VOID)
{
    return bsp_nvm_revert_default() & NV_RESULT_CODE;
}

BSP_U32 mdrv_nv_backup_factorynv(BSP_VOID)
{
    return bsp_nvm_update_default();
}

BSP_U32 mdrv_nv_revert_factorynv(BSP_VOID)
{
    return bsp_nvm_revert_default();
}


BSP_U32 NV_Flush(BSP_VOID)
{
    return bsp_nvm_flush() & NV_RESULT_CODE;
}

BSP_U32 NV_GetLength(BSP_U16 usID, BSP_U32 *pulLength)
{
    BSP_U32 len = 0;
    BSP_U32 ret = 0;
    ret = bsp_nvm_get_len(usID,&len);
    if(ret)
    {
        return ret;
    }
    *pulLength = len;
    return 0;
}
BSP_U32 NV_Backup(BSP_VOID)
{
    return bsp_nvm_backup() & NV_RESULT_CODE;
}
BSP_U32 NV_BackupCheck(BSP_VOID)
{
    return 0;/*TO DO*/
}
BSP_U32 NV_RestoreAll(BSP_VOID)
{
    return bsp_nvm_revert() & NV_RESULT_CODE;
}
BSP_U32 NV_RestoreManufactureDefault(BSP_VOID)
{
    return bsp_nvm_revert_default() & NV_RESULT_CODE;
}
BSP_U32 mdrv_nv_revert_manufacturnv(BSP_VOID)
{
    return bsp_nvm_revert_manufacture() & NV_RESULT_CODE;
}
BSP_U32 NV_RestoreResult(BSP_VOID)
{
    BSP_U32 ret = NV_ERROR;
    BSP_U16 resume_flag = 0;

    ret = bsp_nvm_read(NV_ID_DRV_RESUME_FLAG,(BSP_U8*)&resume_flag,sizeof(BSP_U16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return NV_ERROR;
    }
    return 0;
}
BSP_U32 NV_QueryRestoreResult(BSP_VOID)
{
    BSP_U32 ret = NV_ERROR;
    BSP_U16 resume_flag = 0;

    ret = bsp_nvm_read(NV_ID_DRV_RESUME_FLAG,(BSP_U8*)&resume_flag,sizeof(BSP_U16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return NV_ERROR;
    }
    return 0;
}

BSP_U32 NV_Open_ALL_NV_File(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_Close_ALL_NV_File(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_GetResumeNvIdNum(BSP_U32 enNvItem)
{
    return bsp_nvm_getRevertNum( enNvItem);
}
BSP_U32 NV_GetResumeNvIdList(BSP_U32 enNvItem, BSP_U16 *pusNvList, BSP_U32 ulNvNum)
{
    if (NULL == pusNvList)
    {
        return NV_ERROR;
    }

    if (ulNvNum < NV_GetResumeNvIdNum(enNvItem))
    {
        return NV_ERROR;
    }

    if (NV_MANUFACTURE_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeManufactureIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    if (NV_USER_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeUserIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    if (NV_SECURE_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeSecureIdList,NV_GetResumeNvIdNum(enNvItem)*((BSP_U32)sizeof(BSP_U16)));/*lint !e713*/
        return NV_OK;
    }

    return NV_OK;
}



int DRV_NV_SEC_CHECK(char* path)
{
    return 0;
}
int DRV_COPY_NVUSE_TO_NVBACKUP(void)
{
    return 0;
}
int DRV_COPY_NVUPGRADE_TO_NVUSE(void)
{
    return 0;
}
BSP_U32 NV_Init(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_SpecialNvIdBackup(BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}
BSP_U32 NV_GetNVIdListNum(BSP_VOID)
{
    return bsp_nvm_get_nv_num();
}
BSP_U32 NV_GetNVIdList(NV_LIST_INFO_STRU *pusNvIdList)
{
    if(pusNvIdList == NULL)
    {
        return NV_ERROR;
    }
    return bsp_nvm_get_nvidlist(pusNvIdList);
}

BSP_U32 NV_ReadEx(BSP_U16  enModemID, BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;
    return bsp_nvm_dcread(card_id, usID,(BSP_U8*)pItem,ulLength);
}

BSP_U32 NV_WriteEx(BSP_U16  enModemID,BSP_U16  usID,BSP_VOID   *pItem, BSP_U32  ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcwrite(card_id, usID,(BSP_U8*)pItem,ulLength);
}
BSP_U32 NV_ReadPartEx(BSP_U16 enModemID,BSP_U16 usID,BSP_U32 ulOffset,BSP_VOID *pItem,BSP_U32 ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;

    return bsp_nvm_dcreadpart(card_id,usID,ulOffset,(BSP_U8*)pItem,ulLength);
}
BSP_U32 NV_WritePartEx(BSP_U16   enModemID,BSP_U16   usID,BSP_U32  ulOffset,BSP_VOID *pItem,BSP_U32    ulLength)
{
    BSP_U32 card_id = 0;
    if(enModemID == MODEM_ID_0)
        card_id = NV_USIMM_CARD_1;
    else if(enModemID == MODEM_ID_1)
        card_id = NV_USIMM_CARD_2;
    else
        return BSP_ERR_NV_INVALID_PARAM;
    return bsp_nvm_dcwritepart(card_id,usID,ulOffset,(BSP_U8*)pItem,ulLength);
}
BSP_S32 DRV_NVE_ACCESS(NVE_INFO_S *nve)
{
    return 0;
}

#endif

#else

#include <osl_common.h>

unsigned int mdrv_nv_get_nvid_num()
{
    return 0;
}


unsigned int mdrv_nv_get_nvid_list(NV_LIST_INFO_STRU *pstNvIdList)
{
    if(pstNvIdList == NULL)
    {
        return NV_ERROR;
    }
    return 0;
}

unsigned int mdrv_nv_readex(unsigned int modemid, unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_writeex(unsigned int modemid, unsigned int itemid,void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_read_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_write_partex(unsigned int modemid, unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_flush()
{
    return 0;
}

unsigned int mdrv_nv_get_length(unsigned int itemid, unsigned int *pulLength)
{
    return 0;
}


unsigned int mdrv_nv_read(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_write(unsigned int itemid, void *pdata, unsigned int ulLength)
{
    return 0;
}


unsigned int mdrv_nv_readpart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}


unsigned int mdrv_nv_writepart(unsigned int itemid, unsigned int ulOffset, void *pdata, unsigned int ulLength)
{
    return 0;
}

unsigned int mdrv_nv_get_resume_nvid_list(unsigned int enNvItem, unsigned short *pusNvList, unsigned int ulNvNum)
{
    return 0;
}

unsigned int mdrv_nv_get_resume_nvid_num(unsigned int enNvItem)
{
    return 0;
}


unsigned int mdrv_nv_backup()
{
    return 0;
}

unsigned int mdrv_nv_restore_result()
{
    return 0;
}

unsigned int mdrv_nv_restore()
{
    return 0;
}

unsigned int mdrv_nv_backup_factorynv()
{
    return 0;
}

unsigned int mdrv_nv_revert_factorynv()
{
    return 0;
}
unsigned int mdrv_nv_revert_manufacturnv()
{
    return 0;
}

#if 0
u32 bsp_nvm_read(u32 itemid, u8 * pdata, u32 datalen)
{
    return 0;
}

u32 bsp_nvm_write(u32 itemid, u8 * pdata, u32 datalen)
{
    return 0;
}



u32 bsp_nvm_dcread(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return 0;
}

u32 bsp_nvm_dcwrite(u32 modem_id,u32 itemid, u8* pdata,u32 datalen)
{
    return 0;
}


BSP_U32 NVM_Read(BSP_U32 ulid, BSP_VOID * pdata, BSP_U32 usdatalen)
{
    return 0;
}

BSP_U32 NVM_Write(BSP_U32 ulid, BSP_VOID * pdata, BSP_U32 usdatalen)
{
    return 0;
}

BSP_U32 NVM_Flush(BSP_VOID)
{
    return 0;
}



BSP_U32 NVM_UpgradeBackup(BSP_U32 uloption)
{
    return 0;
}


BSP_U32 NVM_UpgradeRestore(BSP_VOID)
{
    return 0;
}


BSP_U32 NVM_GetItemLength(BSP_U16 ulid, BSP_U32 * pusitemlength)
{
    return 0;
}


BSP_U32 NVM_SetFactoryDefault(BSP_VOID)
{
    return 0;
}

BSP_U32 mdrv_nv_backup_factorynv(BSP_VOID)
{
    return 0;
}

BSP_U32 mdrv_nv_revert_factorynv(BSP_VOID)
{
    return 0;
}

BSP_U32 NV_Read(BSP_U16 ulid, BSP_VOID * pdata, BSP_U32 usdatalen)
{
    return 0;
}

BSP_U32 NV_ReadPart(BSP_U16 usID,BSP_U32 ulOffset,
                                BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}
BSP_U32 NV_Write(BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}
BSP_U32 NV_WritePart(BSP_U16 usID,BSP_U32 ulOffset,
                            BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}

BSP_U32 NV_Flush(BSP_VOID)
{
    return 0;
}

BSP_U32 NV_GetLength(BSP_U16 usID, BSP_U32 *pulLength)
{
    return 0;
}
BSP_U32 NV_Backup(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_BackupCheck(BSP_VOID)
{
    return 0;/*TO DO*/
}
BSP_U32 NV_RestoreAll(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_RestoreManufactureDefault(BSP_VOID)
{
    return 0;
}
BSP_U32 mdrv_nv_revert_manufacturnv(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_RestoreResult(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_QueryRestoreResult(BSP_VOID)
{
    return 0;
}

BSP_U32 NV_Open_ALL_NV_File(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_Close_ALL_NV_File(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_Read_Direct(BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}
BSP_U32 NV_Write_Direct(BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}

BSP_U32 NV_GetResumeNvIdNum(BSP_U32 enNvItem)
{
    return 0;
}
BSP_U32 NV_GetResumeNvIdList(BSP_U32 enNvItem, BSP_U16 *pusNvList, BSP_U32 ulNvNum)
{
    return 0;
}

BSP_U32 nvim_DiagDownLoad(BSP_VOID * pfile, BSP_U32 ulfilelen)
{
    return 0;
}

BSP_U32 nvim_GetInitExportFileInfo(NVIM_EXPORT_FILE_INFO_STRU * pexportfileInfo)
{
    if((NULL == pexportfileInfo)
        ||(NULL == pexportfileInfo->pdata))
    {
        return NV_ERROR;
    }
    return 0;
}
BSP_U32 nvim_GetWorkExportFileInfo(NVIM_EXPORT_FILE_INFO_STRU * pexportfileInfo)
{
    if((NULL == pexportfileInfo)
        ||(NULL == pexportfileInfo->pdata))
    {
        return NV_ERROR;
    }
    return 0;
}



int DRV_NV_SEC_CHECK(char* path)
{
    return 0;
}
int DRV_COPY_NVUSE_TO_NVBACKUP(void)
{
    return 0;
}
int DRV_COPY_NVUPGRADE_TO_NVUSE(void)
{
    return 0;
}
BSP_U32 NV_Init(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_SpecialNvIdBackup(BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}
BSP_U32 NV_GetNVIdListNum(BSP_VOID)
{
    return 0;
}
BSP_U32 NV_GetNVIdList(NV_LIST_INFO_STRU *pusNvIdList)
{
    if(pusNvIdList == NULL)
    {
        return NV_ERROR;
    }
    return 0;
}


int  DRV_UPGRADE_NV_SET_RESULT(int status)
{
    return 0;
}


BSP_U32 NV_ReadEx(BSP_U16  enModemID, BSP_U16 usID,BSP_VOID *pItem,BSP_U32 ulLength)
{
    return 0;
}

BSP_U32 NV_WriteEx(BSP_U16  enModemID,BSP_U16  usID,BSP_VOID   *pItem, BSP_U32  ulLength)
{

    return 0;
}

BSP_U32 NV_WritePartEx(BSP_U16   enModemID,BSP_U16   usID,BSP_U32  ulOffset,BSP_VOID *pItem,BSP_U32    ulLength)
{
    return 0;
}

BSP_S32 DRV_NVE_ACCESS(NVE_INFO_S *nve)
{
    return 0;
}

#endif

#endif

EXPORT_SYMBOL(mdrv_nv_restore);
EXPORT_SYMBOL(mdrv_nv_flush);
EXPORT_SYMBOL(mdrv_nv_get_nvid_list);
EXPORT_SYMBOL(mdrv_nv_revert_factorynv);
EXPORT_SYMBOL(mdrv_nv_get_nvid_num);
EXPORT_SYMBOL(mdrv_nv_writeex);
EXPORT_SYMBOL(mdrv_nv_write_partex);
EXPORT_SYMBOL(mdrv_nv_readex);
EXPORT_SYMBOL(mdrv_nv_readpart);
EXPORT_SYMBOL(mdrv_nv_read_partex);
EXPORT_SYMBOL(mdrv_nv_get_length);
EXPORT_SYMBOL(mdrv_nv_restore_result);
EXPORT_SYMBOL(mdrv_nv_get_resume_nvid_num);
EXPORT_SYMBOL(mdrv_nv_backup);
EXPORT_SYMBOL(mdrv_nv_revert_manufacturnv);
EXPORT_SYMBOL(mdrv_nv_backup_factorynv);
EXPORT_SYMBOL(mdrv_nv_get_resume_nvid_list);


/*lint -restore*/
#ifdef __cplusplus
}
#endif

