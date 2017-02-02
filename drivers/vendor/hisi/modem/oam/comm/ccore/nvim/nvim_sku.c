/*****************************************************************************/
/*                                                                           */
/*                Copyright 1999 - 2003, Huawei Tech. Co., Ltd.              */
/*                           ALL RIGHTS RESERVED                             */
/*                                                                           */
/* FileName: NVIM_Function.c                                                 */
/*                                                                           */
/*                                                                           */
/* Version: 1.0                                                              */
/*                                                                           */
/* Date: 2012-12-21                                                             */
/*                                                                           */
/* Description: implement NV subroutine                                      */
/*                                                                           */
/* Others:                                                                   */
/*                                                                           */
/* History:                                                                  */
/* 1. Date: 2012-12-21                                                       */
/*    Author: dongtinghuan                                                   */
/*    Modification: Create this file                                         */
/*                                                                           */
/*****************************************************************************/
#include "nvim_internalfunc.h"
#include "nvim_fileoperateinterface.h"
#include "NVIM_ResumeId.h"
#include "mdrv.h"
#include "NvIdList.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/* Macro of log */
#define THIS_FILE_ID PS_FILE_ID_NVIM_SKU_C

#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)
extern VOS_CHAR g_acNvUpdateDir[];  /* update����·�� */

extern VOS_CHAR g_acNvDefaultDir[]; /* default����·�� */

extern VOS_CHAR g_acNvUpdateFile[];

#if (VOS_WIN32 == VOS_OS_VER)
VOS_CHAR        g_acNvUpdateForderName[]   = "Nvim\\NvimUp";
VOS_CHAR        g_acNvDefaultForderName[]  = "Nvim\\NvimDef";
#else
VOS_CHAR        g_acNvUpdateForderName[]   = "Nvim/NvimUp";
VOS_CHAR        g_acNvDefaultForderName[]  = "Nvim/NvimDef";
#endif

VOS_CHAR        g_acSpecBin[]              = "spec.bin";    /* ��Ʒ�߿�����Ա���ӵı��ݻָ�NV�� */
const VOS_CHAR  g_acVercfgFile[]           = "vercfg.bin";  /* ���ļ������ҷǿ� */
VOS_CHAR        g_acUserBin[]              = "user.bin";    /* �����û������޸ĵ�NV�� */
VOS_CHAR        g_acOperatorFile[]         = "operator.xml"; /* ��Ӫ�������ļ� */

SKU_SWITCH_FLAG_STRU                g_stSkuSwitchFlag;      /* ��Ӫ���л���� */

NV_IMAGE_PATH_STRU                  g_stCurrentImagePath;   /* ��ǰImage·�� */

VOS_UINT32 NV_GetDirectoryByPath(VOS_CHAR *pcPath, VOS_CHAR *pcDirName, VOS_UINT32 ulModle)
{
    VOS_UINT32                          ulLoop    = 0;
    VOS_UINT32                          ulResult  = VOS_ERR;
    VOS_CHAR                           *pcResult  = VOS_NULL_PTR;
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};
    VOS_CHAR                            acDilms[] = "/";

#if ( VOS_WIN32 == VOS_OS_VER )
    acDilms[0] = '\\';
#endif

    if (VOS_NULL_PTR == pcPath)
    {
        return VOS_ERR;
    }

    /*lint -e534*/
    VOS_MemCpy(acFilePath, pcPath, VOS_StrLen(pcPath));
    /*lint +e534*/

    pcResult = VOS_StrTok(acFilePath, acDilms);
    while (VOS_NULL_PTR != pcResult)
    {
        if (ulModle == ulLoop)
        {
            /* lint -e534 */
            VOS_MemCpy(pcDirName, pcResult, VOS_StrLen(pcResult));
            /*lint +e534*/
            ulResult = VOS_OK;
            break;
        }
        ulLoop++;
        pcResult = VOS_StrTok(VOS_NULL_PTR, acDilms);
    }
    return ulResult;
}


VOS_BOOL NV_CheckImgWithCarrMatch(VOS_CHAR *pcCarrierDir, VOS_CHAR *pcImageDir)
{
    /* �������ȼ�� */
    if (NV_MIN_IMAGE_PATH_LEN > VOS_StrLen(pcImageDir))
    {
        NV_Printf("NV_CheckImageWithCarrierMatch: %s is not available path!\r\n", pcImageDir);
        return VOS_FALSE;
    }

    /* ��� Image ���ȴ���Carrier���ȣ�ֱ�ӷ��� */
    if ( VOS_StrLen(pcImageDir) >= VOS_StrLen(pcCarrierDir) )
    {
        NV_Printf("NV_CheckImageWithCarrierMatch: %s is not available path with %s!\r\n",
                   pcImageDir, pcCarrierDir);
        return VOS_FALSE;
    }

    /* Imageƥ���� */
    if (VOS_OK != VOS_StrNCmp(pcCarrierDir, pcImageDir, VOS_StrLen(pcImageDir)))
    {
        NV_Printf("#info:NV_CheckImageWithCarrierMatch: %s with %s not match!\r\n", pcCarrierDir, pcImageDir);
        return VOS_FALSE;
    }

    /* ƥ������ϣ������жϸ���Ӫ���ļ����Ƿ���� */
    if(VOS_OK != NV_File_Exist(pcCarrierDir, VOS_NULL_PTR))
    {
        NV_Printf("NV_CheckImageWithCarrierMatch: Carrier path %s is not exist!\r\n", pcCarrierDir);
        return VOS_FALSE;
    }

    return VOS_TRUE;

}


VOS_VOID NV_SwitchFlagPrintf(VOS_CHAR *pcFunctionName)
{
   NV_Printf("%s:Switch Carrier flag: \r\n", pcFunctionName);
   NV_Printf("     acCurrentCarrierPath: %s \r\n", g_stSkuSwitchFlag.acCurrentCarrierPath);
   NV_Printf("     acSwitchCarrierPath: %s \r\n", g_stSkuSwitchFlag.acSwitchCarrierPath);
   NV_Printf("     ulCarrierSwitchFlag: %d \r\n", g_stSkuSwitchFlag.ulCarrierSwitchFlag);
   NV_Printf("Switch Image flag: \r\n     acCurrentImagePath: %s \r\n", g_stSkuSwitchFlag.acCurrentImagePath);
   NV_Printf("     acSwitchImagePath: %s \r\n", g_stSkuSwitchFlag.acSwitchImagePath);
   NV_Printf("     ulImageSwitchFlag: %d \r\n", g_stSkuSwitchFlag.ulImageSwitchFlag);
}


VOS_VOID NV_StrcatFilePath(VOS_CHAR *pcDest, VOS_CHAR* pcSrc1, VOS_CHAR* pcSrc2)
{
    /*lint -e534*/
    VOS_StrNCpy(pcDest, pcSrc1, VOS_StrLen(pcSrc1));
    /*lint +e534*/

    if (VOS_NULL_PTR != pcSrc2)
    {
        VOS_StrNCat(pcDest, pcSrc2, VOS_StrLen(pcSrc2));
    }

    return;
}


VOS_VOID NV_ReadSwitchFlag(VOS_VOID)
{
    /* ��ȡ�л���� */
    /*lint -e534*/
    VOS_MemSet(&g_stSkuSwitchFlag, 0, sizeof(SKU_SWITCH_FLAG_STRU));
    /*lint +e534*/
    if (VOS_OK != DRV_READ_SWITCH_FLAG(&g_stSkuSwitchFlag))
    {
        /*lint -e534*/
        VOS_MemSet(&g_stSkuSwitchFlag, 0, sizeof(SKU_SWITCH_FLAG_STRU));

        NV_Printf("NV_ReadSwitchFlag: Read switch flag fail.\r\n");
        /*lint +e534*/
    }

    return;
}
VOS_UINT32 NV_SkuGetOperatorPath(VOS_CHAR *pcFilePath)
{
    if (NV_MIN_CARRIER_PATH_LEN > VOS_StrLen(g_stSkuSwitchFlag.acCurrentCarrierPath))
    {
        NV_Printf("NV_SkuGetOperatorPath: Current carrier path is %s error.\r\n",
                    g_stSkuSwitchFlag.acCurrentCarrierPath);
        return VOS_ERR;
    }

    /* ƴ���ļ����� */
    NV_StrcatFilePath(pcFilePath, g_stSkuSwitchFlag.acCurrentCarrierPath, g_acOperatorFile);

    return VOS_OK;
}
VOS_UINT32 NV_SkuSetDefAndUpDir(VOS_VOID)
{
    /* ��ȡ��ǰImage·�� */
    /*lint -e534*/
    VOS_MemSet(&g_stCurrentImagePath, 0, sizeof(NV_IMAGE_PATH_STRU));
    /*lint +e534*/
    if (VOS_OK != DRV_GET_CURRENT_IMAGE_PATH(g_stCurrentImagePath.acImagePath))
    {
        NV_Printf("NV_SkuSetDefAndUpDir:Get current Image path from DRV return error.\r\n");
        return VOS_ERR;
    }

    if (NV_MAX_IMAGE_PATH_LEN < VOS_StrLen(g_stCurrentImagePath.acImagePath))
    {
        NV_Printf("NV_SkuSetDefAndUpDir:Get current Image path:%s fail from DRV .\r\n",
                   g_stCurrentImagePath.acImagePath);
        return VOS_ERR;
    }

    if (NV_MIN_IMAGE_PATH_LEN > VOS_StrLen(g_stCurrentImagePath.acImagePath))
    {
        NV_Printf("NV_SkuSetDefAndUpDir:Get current Image path:%s fail from DRV .\r\n",
                   g_stCurrentImagePath.acImagePath);
        return VOS_ERR;
    }

    /* ������������·��*/
    /*lint -e534*/
    VOS_MemSet(g_acNvUpdateDir, 0, NV_MAX_UPDEATE_PATH_LEN);
    /*lint +e534*/
    NV_StrcatFilePath(g_acNvUpdateDir, g_stCurrentImagePath.acImagePath, g_acNvUpdateForderName);

    /* ����Ĭ�Ϸ���·��*/
    /*lint -e534*/
    VOS_MemSet(g_acNvDefaultDir, 0, NV_MAX_DEFAULT_PATH_LEN);
    /*lint +e534*/
    NV_StrcatFilePath(g_acNvDefaultDir, g_stCurrentImagePath.acImagePath, g_acNvDefaultForderName);

    return VOS_OK;
}
VOS_UINT32 NV_CheckUpdateFlag(VOS_VOID)
{
    if (VOS_OK != NV_File_Exist(g_acNvUpdateDir, g_acNvUpdateFile))
    {
        /* �ж�����Ŀ¼���� NVupdate.bin */
        if (VOS_OK != NV_File_Exist(g_acNvDefaultDir, g_acNvUpdateFile))
        {
            NV_Printf("NV_CheckUpdateFlag: NV default Dir is not exist NvUpdate.bin.\r\n");
            return VOS_ERR;
        }

        /* Ĭ����������ʹ���� */
        if (NV_OK != NV_Xcopy((VOS_CHAR*)g_acNvDefaultDir, (VOS_CHAR*)g_acNvUpdateDir))
        {
            NV_Printf("NV_CheckUpdateFlag: NV_Xcopy %s to %s is failed.\r\n", g_acNvDefaultDir,g_acNvUpdateDir);

            return NV_SKU_XCOPY_UPDATE_FAIL;
        }
    }

    return VOS_OK;
}


VOS_UINT32 NV_SkuRestoreNvFile(VOS_BOOL bIsDefault)
{
    /* ����������Ҫ�ָ��ļ�ͼ־
    ----------------------------------------------------------------
    |  ����\���� |  ���� |  user.bin  |  spec.bin     |operator.xml|
    ---------------------------------------------------------------
    |NV �������� |  �ָ� |     ��     |       ��      |     ��     |
    ----------------------------------------------------------------
    |NV �л����� |  �ָ� |     ��     |       ��      |     ��     |
    ----------------------------------------------------------------
    |�ָ���������|  �ָ� |     ��     |       ��      |     ��     |
    ----------------------------------------------------------------*/

    /* ֻ���������л����̲Żָ� user.bin */
    if (VOS_TRUE != bIsDefault)
    {
        /* ����user�ָ���ָ���Ӫ��user.bin */
        if (VOS_OK != NV_SkuRestoreNvFileRead(g_acUserBin))
        {
            NV_Printf("NV_SkuRestoreNvFile: Sku Restore user.bin return error!");
            return VOS_ERR;
        }
    }
    else
    {
        /* �ָ������������̣�ɾ����ǰ��Ӫ��user.bin�ļ� */
        NV_File_Remove(g_stSkuSwitchFlag.acCurrentCarrierPath, g_acUserBin);
    }

    /* ���лָ����̶���Ҫ�ָ� spec.bin */
#if (0 < NV_RESUME_SKU_SPEC_ID_LIST_LEN)
    /* ����汾�Զ����NV��ݻָ�����0 */

    /* �ָ��汾�Զ���ָ��� */
    if (VOS_OK != NV_SkuRestoreNvFileRead(g_acSpecBin))
    {
        NV_Printf("NV_SkuRestoreNvFile: Sku Restore spec.bin return error!");
        return VOS_ERR;
    }
#endif

    return VOS_OK;
}


VOS_UINT32 NV_SkuBackupNvFile(VOS_VOID)
{
   /* ����������Ҫ�����ļ�ͼ־
    ----------------------------------------------------------------
    |  ����\���� |  ���� |  user.bin  |  spec.bin     |operator.xml|
    ---------------------------------------------------------------
    |NV �������� |  ���� |     ��     |       ��      |     ��     |
    ----------------------------------------------------------------
    |NV �л����� |  ���� |     ��     |       ��      |     ��     |
    ----------------------------------------------------------------
    |�ָ���������|  ���� |     ��     |       ��      |     ��     |
    ----------------------------------------------------------------*/

    /* ����汾�Զ����NV��ݻָ�����0 */
    /* ���ݰ汾�Զ��屸���� */
     if (VOS_OK != NV_SkuBackupNvFileWrite(g_acSpecBin,
                                           NV_GetResumeNvIdNum(NV_SKU_ITEM),
                                           g_ausNvResumeSkuSpecIdList))
     {
        return VOS_ERR;
     }

    /* ����user �����������Ӫ��user.bin */
    if (VOS_OK != NV_SkuBackupNvFileWrite(g_acUserBin,
                                          NV_GetResumeNvIdNum(NV_USER_ITEM),
                                          g_ausNvResumeUserIdList))
     {
        return VOS_ERR;
     }

    return VOS_OK;
}
VOS_UINT32 NV_SkuGetNvFilePath(VOS_CHAR *pcFilePath, VOS_CHAR *pcFileName)
{
    if (VOS_OK == VOS_MemCmp(pcFileName, g_acUserBin, VOS_StrLen(g_acUserBin)))
    {
        /* user.bin */
        NV_StrcatFilePath(pcFilePath, g_stSkuSwitchFlag.acCurrentCarrierPath, pcFileName);
        return VOS_OK;
    }

    if (VOS_OK == VOS_MemCmp(pcFileName, g_acSpecBin, VOS_StrLen(g_acSpecBin)))
    {
        /* spec.bin */
        NV_StrcatFilePath(pcFilePath, g_stCurrentImagePath.acImagePath, pcFileName);
        return VOS_OK;
    }

    return VOS_ERR;
}



VOS_UINT32 NV_SkuRestoreNvFileRead(VOS_CHAR *pcFileName)
{
    FILE                               *pFile       = VOS_NULL_PTR;
    NV_SKU_DATA_INFO_STRU              *pstNvSkuDataInfo;
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};
    VOS_CHAR                           *pcFileContent;
    VOS_UINT32                          ulLength    = 0;
    VOS_UINT32                          uloffset    = 0;
    VOS_UINT32                          ulRest      = VOS_OK;
    VOS_UINT32                          ulDilms    = 0x5A5A5A5A;

    /* ��ȡ�ļ���ַ */
    if (VOS_OK != NV_SkuGetNvFilePath(acFilePath, pcFileName))
    {
        NV_Printf("NV_SkuRestoreNvFileRead: Get Restore NV File path error!: %s", acFilePath);
        return VOS_ERR;
    }

    /* �ж��ļ��Ƿ���� */
    if (VOS_OK != NV_File_Exist(acFilePath, VOS_NULL_PTR))
    {
        NV_Printf("NV_SkuRestoreNvFileRead:%s file is not exist.\r\n", pcFileName);
        return VOS_OK;
    }

    /* ���ļ� */
    pFile = NV_File_Open(acFilePath, NV_FILE_OPEN_MODE_R);
    if (VOS_NULL_PTR == pFile)
    {
        NV_Printf("NV_SkuRestoreNvFileRead:Open %s file fail.\r\n", pcFileName);
        return VOS_ERR;
    }

    /* �ض�λ���ϵ��ļ��ڲ�λ��ָ��*/
    NV_File_Seek(pFile, 0, NV_FILE_SEEK_END);

    ulLength = (VOS_UINT32)NV_File_Tell(pFile);
    if (0 == ulLength)
    {
        /* �ļ��쳣 */
        NV_Printf("NV_SkuRestoreNvFileRead:file lenth is 0.\r\n");
        NV_File_Close(pFile);
        return VOS_ERR;
    }

    pcFileContent = (VOS_CHAR*)VOS_MemAlloc(WUEPS_PID_OM, DYNAMIC_MEM_PT, ulLength);

    if(VOS_NULL_PTR == pcFileContent)
    {
        NV_Printf("NV_SkuRestoreNvFileRead:Alloc buffer fail.\r\n");
        NV_File_Close(pFile);
        return VOS_ERR;
    }

    NV_File_Seek(pFile, 0, NV_FILE_SEEK_SET);

    NV_File_Read(pcFileContent, ulLength, 1, pFile);

    /* ���ݽ��� */
    while (uloffset < ulLength)
    {
        /* ������ NV ID */
        pstNvSkuDataInfo = (NV_SKU_DATA_INFO_STRU *)(pcFileContent + uloffset);

        uloffset += sizeof(NV_SKU_DATA_INFO_STRU) + pstNvSkuDataInfo->usNvLength - sizeof(VOS_UINT32);

        /* �����Դ��� */
        if(ulLength < uloffset)
        {
            NV_Printf("NV_SkuRestoreNvFileRead:offset:%d > file lenth:%d error.\r\n", uloffset, ulLength);
            ulRest = VOS_ERR;
            break;
        }

        if (VOS_OK != VOS_MemCmp((pcFileContent + uloffset), &ulDilms, sizeof(VOS_UINT32)))
        {
            NV_Printf("NV_SkuRestoreNvFileRead:%s content error.\r\n");
            ulRest = VOS_ERR;
            break;
        }

        /* ������NV��ֵд��NVʹ���� */

        if (VOS_OK != NV_WriteDirectAll(pstNvSkuDataInfo->usNvId, (VOS_VOID*)pstNvSkuDataInfo->aucData, pstNvSkuDataInfo->usNvLength))
        {
            NV_Printf("NV_SkuRestoreNvFileRead:NV Restore Write fail.\r\n");
            ulRest = VOS_ERR;
            break;
        }

        uloffset += sizeof(VOS_UINT32);

    }

    /*lint -e534*/
    VOS_MemFree(WUEPS_PID_OM, pcFileContent);
    /*lint +e534*/
    NV_File_Close(pFile);

    return ulRest;
}
FILE * NV_SkuOpenNvFile(VOS_CHAR *pcFileName)
{
    VOS_CHAR                            acFilePath[NV_MAX_PATH_SIZE] = {0};

    if (VOS_NULL_PTR == pcFileName)
    {
        NV_Printf("NV_SkuOpenNvFile:para error.\r\n");
        return VOS_NULL_PTR;
    }

    /* ��ȡ�ļ���ַ */
    if (VOS_OK != NV_SkuGetNvFilePath(acFilePath, pcFileName))
    {
        NV_Printf("NV_SkuOpenNvFile: Open NV File Name fail!: %s", pcFileName);
        return VOS_NULL_PTR;
    }

    /* �ж��ļ��Ƿ���� */
    if (VOS_OK == NV_File_Exist(acFilePath, VOS_NULL_PTR))
    {
        NV_Printf("#info:NV_SkuOpenNvFile:%s file is exist.\r\n", pcFileName);
        NV_File_Remove(acFilePath, VOS_NULL_PTR);
    }

    /* ���ļ� */
    return NV_File_Open(acFilePath, NV_FILE_OPEN_MODE_NEW_RW);

}
VOS_UINT32 NV_SkuBackupNvFileWrite(VOS_CHAR *pcFileName, VOS_UINT32 ulNvNum, VOS_UINT16 *pusNvId)
{
    FILE                               *pFile      = VOS_NULL_PTR;
    NV_SKU_DATA_INFO_STRU              *pstSkuDataInfo;
    VOS_UINT32                          ulNvLength = 0;
    VOS_UINT32                          ulRest     = VOS_OK;
    VOS_UINT32                          ulDilms    = 0x5A5A5A5A; /* �ָ��� 0x5A5A5A5A */
    VOS_UINT32                          i;

    if (0 == ulNvNum)
    {
        NV_Printf("NV_SkuBackupNvFileWrite: #info :no nv id restore.\r\n");
        return VOS_OK;
    }

    /* ���ļ� */
    pFile = NV_SkuOpenNvFile(pcFileName);
    if (VOS_NULL_PTR == pFile)
    {
        NV_Printf("NV_SkuBackupNvFileWrite:opern %s file fail.\r\n", pcFileName);
        return VOS_ERR;
    }

    for (i = 0; i< ulNvNum; i++)
    {
        ulRest = NV_GetLength(pusNvId[i], &ulNvLength);
        if (VOS_OK != ulRest)
        {
            /* ID ������ */
            NV_Printf("NV_SkuBackupNvFileWrite:NV ID NO.%d not exist.\n", pusNvId[i]);
            break;
        }

        /* �ָ������ڴ�һ������ */
        pstSkuDataInfo = (NV_SKU_DATA_INFO_STRU*)VOS_MemAlloc(
                                                 WUEPS_PID_OM,
                                                 DYNAMIC_MEM_PT,
                                                 sizeof(NV_SKU_DATA_INFO_STRU) + ulNvLength);

        if(VOS_NULL_PTR == pstSkuDataInfo)
        {
            NV_Printf("NV_SkuBackupNvFileWrite:Alloc buffer fail\n");
            ulRest = VOS_ERR;
            break;
        }

        /* NV ��ȡ */
        ulRest = NV_ReadEx(MODEM_ID_0, pusNvId[i], pstSkuDataInfo->aucData, ulNvLength);
        if(NV_OK != ulRest)
        {
            NV_Printf("NV_SkuBackupNvFileWrite:NV Read fail.\r\n");
            /*lint -e534*/
            VOS_MemFree(WUEPS_PID_OM, pstSkuDataInfo);
            /*lint +e534*/
            break;
        }

        pstSkuDataInfo->usNvId     = pusNvId[i];
        pstSkuDataInfo->usNvLength = (VOS_UINT16)ulNvLength;

        /* ���Ϸָ�� */
        /*lint -e534*/
        VOS_MemCpy((pstSkuDataInfo->aucData + ulNvLength), &ulDilms, sizeof(VOS_UINT32));
        /*lint +e534*/

        /* д���Ӧ��NV �ļ��� */
        NV_File_Write(pstSkuDataInfo, sizeof(VOS_UINT8),
                      (sizeof(NV_SKU_DATA_INFO_STRU) + ulNvLength),
                      pFile);

        /*lint -e534*/
        VOS_MemFree(WUEPS_PID_OM, pstSkuDataInfo);
        /*lint +e534*/
    }

    NV_File_Close(pFile);
    return ulRest;

}
VOS_UINT32 NV_SwitchAvailCarr(VOS_VOID)
{
    NV_CARRIER_PATH_STRU                stCarrierPath;
    VOS_UINT32                          ulCarrierPathLen;

    /* ��ѯ������Ӫ�������ļ�·�� */
    ulCarrierPathLen = NV_MAX_CARRIER_PATH_LEN;
    /*lint -e534*/
    VOS_MemSet(&stCarrierPath, 0, sizeof(NV_CARRIER_PATH_STRU));
    /*lint +e534*/
    if (VOS_OK != DRV_GET_AVAILABLE_CARRIER_PATH(stCarrierPath.acCarrierPath, &ulCarrierPathLen))
    {
        NV_Printf("NV_SwitchAvailCarr:Get Available Carrier path from DRV error.\r\n");
        return VOS_ERR;
    }

    /* ��ѯ������ */
    if ((NV_MAX_CARRIER_PATH_LEN < ulCarrierPathLen)||
        (NV_MIN_CARRIER_PATH_LEN > ulCarrierPathLen))
    {
        NV_Printf("NV_SwitchAvailCarr:Carrier path error, lenth %d !\r\n", ulCarrierPathLen);
        return VOS_ERR;
    }

    /* ���õ�ǰ��Ӫ�� */
    /*lint -e534*/
    VOS_MemCpy(g_stSkuSwitchFlag.acCurrentCarrierPath,
               stCarrierPath.acCarrierPath,
              (sizeof(stCarrierPath.acCarrierPath)));
    /*lint +e534*/

    return VOS_OK;

}
VOS_UINT32 NV_SelectCarrier(VOS_VOID)
{
    /* �л���Ƕ�ȡ */
    NV_ReadSwitchFlag();

    /* ��ӡ�л����λ��Ϣ */
    NV_SwitchFlagPrintf("NV_SelectCarrier");

    /* �л���ǲ����� */
    if (VOS_TRUE != g_stSkuSwitchFlag.ulCarrierSwitchFlag)
    {
        /* ����������Ӫ��ƥ���� */
        if (VOS_TRUE == NV_CheckImgWithCarrMatch(g_stSkuSwitchFlag.acCurrentCarrierPath,
                                                 g_stCurrentImagePath.acImagePath))
        {
            return VOS_OK;
        }

        NV_Printf("NV_SelectCarrier:Switch carrier flag is 0,but Current carrier not match:%s with %s.\r\n",
                    g_stSkuSwitchFlag.acCurrentCarrierPath, g_stCurrentImagePath.acImagePath);

        /* ���ҿ�����Ӫ�̷����л����������õ������� */
        if (VOS_OK != NV_SwitchAvailCarr())

        {
            NV_Printf("NV_SelectCarrier:Switch carrier flag is 0, Get Available Carrier fail.\r\n");
            return VOS_ERR;
        }
    }
    else
    {
        /* �л���Ǵ��� �жϴ��л���Ӫ�̺�Image�Ƿ�ƥ�� */
        if (VOS_TRUE != NV_CheckImgWithCarrMatch(g_stSkuSwitchFlag.acSwitchCarrierPath,
                                                 g_stCurrentImagePath.acImagePath))
        {
            NV_Printf("NV_SelectCarrier:Switch carrier flag is 1,but Switch carrier not match:%s with %s.\r\n",
                g_stSkuSwitchFlag.acSwitchCarrierPath, g_stCurrentImagePath.acImagePath);

            /* ���ҿ�����Ӫ�̷����л����������õ������� */
            if (VOS_OK != NV_SwitchAvailCarr())
            {
                NV_Printf("NV_SelectCarrier:Switch carrier flag is 1, Get Available Carrier fail.\r\n");
                return VOS_ERR;
            }
        }
        else
        {
            /* ���õ�ǰ��Ӫ�� */
            /*lint -e534*/
            VOS_MemCpy(g_stSkuSwitchFlag.acCurrentCarrierPath,
                       g_stSkuSwitchFlag.acSwitchCarrierPath,
                       sizeof(g_stSkuSwitchFlag.acSwitchCarrierPath));
            /*lint +e534*/
        }
    }

    /* ������Ǽ�� */
    if (VOS_OK != NV_CheckUpdateFlag())
    {
        NV_Printf("NV_SelectCarrier:NV Check Update Flag fail.\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 NV_SkuSwitchProc()
{
    /* ��Ӫ������������Ĭ���Ϸ���·������ */
    if (VOS_OK != NV_SkuSetDefAndUpDir())
    {
        NV_Printf("NV_SkuSwitchProc:Set carrier default and update path fail.\r\n");
        return VOS_ERR;
    }

    /* ��Ӫ��ѡ�� */
    if (VOS_OK != NV_SelectCarrier())
    {
        NV_Printf("NV_SkuSwitchProc:Select carrier return fail.\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 NV_SkuUpdateSwitchFlag()
{
    /* ���µ�ǰ�л���ʶ */
    /*lint -e534*/
    VOS_MemSet(g_stSkuSwitchFlag.acSwitchCarrierPath, 0, sizeof(g_stSkuSwitchFlag.acSwitchCarrierPath));
    /*lint +e534*/

    g_stSkuSwitchFlag.ulCarrierSwitchFlag = VOS_FALSE;

    if (VOS_OK != DRV_WRITE_SWITCH_FLAG(&g_stSkuSwitchFlag))
    {
        /* Log��¼ */
        NV_Printf("NV_SkuUpdateSwitchFlag:Write switch flag fail.\r\n");
        return NV_SKU_WRITE_SWITCH_FALG_ERR;
    }

    return VOS_OK;

}


VOS_UINT32 NV_SetSwitchCarrierFlag(
    VOS_CHAR                           *pcCarrierPath,
    VOS_UINT32                          ulCarrierPathLen,
    VOS_BOOL                           *pbIsSwitchImage)
{
    VOS_CHAR                            acImageName[NV_MAX_IMAGE_NAME_LEN + 1] = {0};

    /* ������� */
    if ((VOS_NULL_PTR == pcCarrierPath)
        || (0 == ulCarrierPathLen)
        || (NV_MAX_CARRIER_PATH_LEN < ulCarrierPathLen))
    {
        NV_Printf("NV_SetSwitchCarrierFlag:para is error: %s, length %d.\r\n",
                    pcCarrierPath, ulCarrierPathLen);
        return NV_SKU_CARRIER_PARA_ERR;
    }

    /* ��ǰ��Ӫ��NV���� */
    if (NV_OK != NV_ExNoBackup())
    {
        /* ����ʧ�� */
        NV_Printf("NV_SetSwitchCarrierFlag:Carrier:%s NV Backup fail.\r\n",
                    pcCarrierPath);
        return NV_SKU_CARRIER_NV_BACKUP_ERR;
    }

    /* �ж�Image�Ƿ���Ҫ�л� */
    if (VOS_TRUE !=  NV_CheckImgWithCarrMatch(pcCarrierPath,
                                              g_stCurrentImagePath.acImagePath))
    {
        /* ��ȡ��Ҫ�л�Image���� */
        if (VOS_OK != NV_GetDirectoryByPath(pcCarrierPath,
                                            acImageName,
                                            NV_SKU_IMAGE_PATH_LEVEL))
        {
            NV_Printf("NV_SetSwitchCarrierFlag:Get directory by path %s fail.\r\n",
                        g_stCurrentImagePath.acImagePath);
            return VOS_ERR;

        }

        /*lint -e534*/
        VOS_MemSet(g_stSkuSwitchFlag.acSwitchImagePath, 0, sizeof(g_stSkuSwitchFlag.acSwitchImagePath));
        /*lint +e534*/

        /* ��ȡ����Image·������ֱ��д�����ļ��� */
        if (VOS_OK != DRV_GET_IMAGE_PATH(acImageName, g_stSkuSwitchFlag.acSwitchImagePath))
        {
             NV_Printf("NV_SetSwitchCarrierFlag:Get Switch Image path from drv fail. ImageName:%s, Getpath:%s\r\n",
                        acImageName, g_stSkuSwitchFlag.acSwitchImagePath);
             return VOS_ERR;
        }

        /* ��Image�л���� */
        g_stSkuSwitchFlag.ulImageSwitchFlag = VOS_TRUE;

        *pbIsSwitchImage = VOS_TRUE;

    }

    /* ��¼���л���Ӫ��·�� */
    /*lint -e534*/
    VOS_MemCpy(g_stSkuSwitchFlag.acSwitchCarrierPath, pcCarrierPath, VOS_StrLen(pcCarrierPath)+ 1);
    /*lint +e534*/

    /* ����Ӫ���л���� */
    g_stSkuSwitchFlag.ulCarrierSwitchFlag = VOS_TRUE;

    /* ���µ�ǰ�л���ʶ */
    if (VOS_OK != DRV_WRITE_SWITCH_FLAG(&g_stSkuSwitchFlag))
    {
        /* Log��¼ */
        NV_Printf("NV_SetSwitchCarrierFlag:Write switch flag fail.\r\n");
        return NV_SKU_WRITE_SWITCH_FALG_ERR;
    }

    return VOS_OK;
}

#endif
VOS_UINT32 NV_SwitchCarrier(
    VOS_CHAR                           *pcCarrierName,
    VOS_UINT32                          ulCarrierNameLen,
    VOS_BOOL                           *pbIsSwitchImage)
{
#if (FEATURE_ON == FEATURE_S_SKU_M_OPERATORS)

    NV_CARRIER_PATH_STRU                stCarrierPath;
    VOS_UINT32                          ulCarrierPathLen = 0;
    VOS_CHAR                            aucCarrierName[NV_MAX_CARRIER_NAME_LEN] = {0};
    VOS_UINT32                          ulRest;

    /* ������� */
    if ((VOS_NULL_PTR == pcCarrierName)
        || (0 == ulCarrierNameLen)
        || (NV_MAX_CARRIER_NAME_LEN < ulCarrierNameLen))
    {
        NV_Printf("NV_SwitchCarrier:para is error: %s, length %d.\r\n",
                    pcCarrierName, ulCarrierNameLen);
        return NV_SKU_CARRIER_PARA_ERR;
    }

    /* ��ӡ�л����λ��Ϣ */
    NV_SwitchFlagPrintf("NV_SwitchCarrier");

    /* ��ȡ��ǰ��Ӫ��Ŀ¼ */
    if (VOS_OK != NV_GetDirectoryByPath(g_stSkuSwitchFlag.acCurrentCarrierPath,
                                        aucCarrierName,
                                        NV_SKU_CARRIER_PATH_LEVEL))
    {
        NV_Printf("NV_SwitchCarrier:Get directory by path %s, Level:%d fail.\r\n",
                    g_stSkuSwitchFlag.acCurrentCarrierPath, NV_SKU_CARRIER_PATH_LEVEL);

        return NV_GET_CURRENT_CARRIER_NAME_ERR;
    }

    /* �ж��Ƿ����л�����ǰ��Ӫ�� */
    if (VOS_OK == VOS_StrNCmp(aucCarrierName, pcCarrierName, ulCarrierNameLen))
    {
        /* ��ǰ��Ӫ�̲����л� */
        return VOS_OK;
    }

    /*lint -e534*/
    VOS_MemSet(&stCarrierPath, 0, sizeof(NV_CARRIER_PATH_STRU));
    /*lint +e534*/

    /* ��ѯĿ����Ӫ�������ļ�·�� */
    if (VOS_OK != DRV_GET_CARRIER_PATH(pcCarrierName,
                                       ulCarrierNameLen,
                                       stCarrierPath.acCarrierPath,
                                       &ulCarrierPathLen))
     {
        NV_Printf("NV_SwitchCarrier:Get Carrier path from DRV fail.\r\n");

        return NV_SKU_GET_CARRIER_PATH_ERR;
     }

    /* ���л���� */
    ulRest = NV_SetSwitchCarrierFlag(stCarrierPath.acCarrierPath,
                                     ulCarrierPathLen, pbIsSwitchImage);
    if (VOS_OK != ulRest)
    {
        NV_Printf("NV_SwitchCarrier:Set Switch carrier falg fail! return %d.\r\n",
                    ulRest);
        return ulRest;
    }

#endif

    return VOS_OK;
}

#ifdef __cplusplus
    #if __cplusplus

        }
    #endif
#endif


