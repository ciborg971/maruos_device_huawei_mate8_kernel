

/*lint -save -e537*/
#include <securec.h>
#include "bsp_nvim.h"
#include "mdrv_nvim.h"
#include "drv_comm.h"
#include "nv_comm.h"
#include "NVIM_ResumeId.h"
/*lint -restore*/
#ifdef __cplusplus
extern "C"
{
#endif

#define  NV_RESULT_CODE            0xffff
/*lint -save -e958 -e438*/
#ifdef CONFIG_NVIM
/*lint -save -e18*/

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
        (void)memcpy_s(pusNvList, NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)),g_ausNvResumeManufactureIdList,NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)));
        return NV_OK;
    }

    if (NV_USER_ITEM == enNvItem)
    {
        (void)memcpy_s(pusNvList, NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)), g_ausNvResumeUserIdList,NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)));
        return NV_OK;
    }

    if (NV_SECURE_ITEM == enNvItem)
    {
        (void)memcpy_s(pusNvList, NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)), g_ausNvResumeSecureIdList, NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)));
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
    return 0;
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
    return 0;
}
unsigned int mdrv_nv_revert_manufacturnv()
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


#if 0
BSP_U32 NVM_Flush(BSP_VOID)
{
    return bsp_nvm_flush() & NV_RESULT_CODE;
}



BSP_U32 NVM_UpgradeBackup(BSP_U32 uloption)
{
    /* [false alarm]:uloption is never using */
    uloption = uloption;
    return 0;
}


BSP_U32 NVM_UpgradeRestore(BSP_VOID)
{
    return 0;
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
        memcpy(pusNvList, g_ausNvResumeManufactureIdList,NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)));
        return NV_OK;
    }

    if (NV_USER_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeUserIdList,NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)));
        return NV_OK;
    }

    if (NV_SECURE_ITEM == enNvItem)
    {
        memcpy(pusNvList, g_ausNvResumeSecureIdList, NV_GetResumeNvIdNum(enNvItem)*(sizeof(BSP_U16)));
        return NV_OK;
    }

    return NV_OK;
}

int DRV_NV_SEC_CHECK(char* path)
{
    path = path;
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
     /*[false alarm]:Value Never Read*/
    usID = usID;
     /*[false alarm]:Value Never Read*/
    pItem = pItem;
     /*[false alarm]:Value Never Read*/
    ulLength = ulLength;
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
    nve = nve;
    return 0;
}
/*lint -restore +e18*/
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
unsigned int mdrv_nv_revert_manufacturnv()
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

/*lint -restore*/

#ifdef __cplusplus
}
#endif

