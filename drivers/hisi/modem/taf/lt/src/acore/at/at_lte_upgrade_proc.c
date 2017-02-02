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
/******************************************************************************
 *//* PROJECT   : MSP
 *//* SUBSYSTEM : MSP
 *//* MODULE    : AT
 *//* OWNER     :
 *//******************************************************************************
 */
/*lint --e{537,322,7,958,732,813,718,746,734}*/
#include "msp_upgrade_proc.h"
#include "at_lte_common.h"
#include "ATCmdProc.h"
#include "ScInterface.h"
#include "mdrv.h"
#include <osm.h>
/*lint -e767 ԭ��:Log��ӡ*/
#define    THIS_FILE_ID        MSP_FILE_ID_AT_LTE_UPGRADE_PROC_C
/*lint +e767 */
VOS_UINT32 g_atNvBackupFlag = 0;

/*bootrom�İ汾��ѯ*/
VOS_UINT32 atQryBootRomVer(VOS_UINT8 ucClientId)
{
#if 0
    FTM_RD_BOOTROMVER_REQ_STRU stBOOTROMVERQryReq = {0};
    VOS_UINT32 ulRst;

 /*   ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_RD_BOOTROMVER_REQ, ucClientId, (VOS_VOID*)(&stBOOTROMVERQryReq),
        sizeof(stBOOTROMVERQryReq)); */

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_BOOTROMVER_READ;
        return AT_WAIT_ASYNC_RETURN;
    }
#endif
    return AT_ERROR;
}

#ifdef FEATURE_UPGRADE_TL
#include "msp_nv_id.h"
#include "drv_nv_id.h"



#define AT_NV_IMEI_LEN              15

VOS_UINT32 At_GetNvRevertState(VOS_VOID)
{
    VOS_UINT32 ret = (VOS_UINT32)-1;
    VOS_UINT16 resume_flag = 0;

    ret = NVM_Read(NV_ID_DRV_RESUME_FLAG,&resume_flag,sizeof(VOS_UINT16)); /*to do*/
    if(ret)
    {
        return ret;
    }
    if(0 != resume_flag)
    {
        return ((VOS_UINT32)-1);
    }
    return 0;
}

VOS_UINT32 At_GetNvAuthorityType(VOS_UINT32 * pdata)
{
    VOS_UINT32 ulRst;
    VOS_UINT8 *pucData = NULL;
    if(pdata==NULL)
    {
        return 0;
    }
    pucData = (VOS_UINT8 *)pdata;
    ulRst = NVM_Read(NV_ID_MSP_AUTHORITY_TYPE, pdata, sizeof(VOS_UINT32));

    if(ulRst != 0)
    {
        pucData[0] = 1;
        pucData[1] = 0;
        pucData[2] = 0;
        pucData[3] = 0;
        return ulRst;
    }

    return  0;
}

VOS_UINT32 At_GetNvAuthorityVer(VOS_UINT32 * pdata)
{
    VOS_UINT32 ulRst;

    if(pdata == NULL)
    {
        return ((VOS_UINT32)-1);
    }

    ulRst = NVM_Read(NV_ID_MSP_AUTHORITY_VER, pdata, sizeof(VOS_UINT32));

    if(ulRst != 0)
    {
        *pdata = 0;
    }

    return 0;
}



VOS_UINT32 At_GetImei(VOS_CHAR szimei [ 16 ])
{
    VOS_UINT32  ret;
    VOS_UINT32  uslen = 0;
    VOS_UINT32  subscript = 0;
    VOS_CHAR   checkdata = 0;
    VOS_CHAR   auctemp[AT_NV_IMEI_LEN+1] = {0};

    uslen = AT_NV_IMEI_LEN+1;

    ret = NVM_Read(0, auctemp, uslen);

    if(ret != 0)
    {
        return ret;
    }
    else
    {
        for (subscript = 0; subscript < (AT_NV_IMEI_LEN - 1); subscript += 2)
        {
            checkdata += (VOS_CHAR)(((auctemp[subscript])
                           +((auctemp[subscript + 1] * 2) / 10))
                           +((auctemp[subscript + 1] * 2) % 10));
        }
        checkdata = (10 - (checkdata%10)) % 10;

        for (subscript = 0; subscript < uslen; subscript++)
        {
            *(szimei + subscript) = *(auctemp + subscript) + 0x30; /*�ַ�ת��*/
        }

        szimei[AT_NV_IMEI_LEN - 1] = checkdata + 0x30;
        szimei[AT_NV_IMEI_LEN] = 0;
    }

    return 0;
}

VOS_UINT32 atQryDLoadVer(VOS_UINT8 ucClientId)
{
    DLOAD_VER_INFO_S                   *pstDloadVerInfo;

    pstDloadVerInfo = mdrv_dload_get_info();

    if(NULL == pstDloadVerInfo)
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    if(NULL == pstDloadVerInfo->dloadver)
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%s\r",
                                           pstDloadVerInfo->dloadver);

    return AT_OK;
}

/*�������û���ѯ������Ϣ�����ڷ��ص���ͺ�̨�汾�š���Ʒ�ͺ����ơ�����������Ϣ*/
VOS_UINT32 atQryDLoadInfo(VOS_UINT8 ucClientId)
{
    DLOAD_VER_INFO_S                   *pstDloadVerInfo;

    pstDloadVerInfo = mdrv_dload_get_info();

    if(NULL == pstDloadVerInfo)
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    if ((NULL == pstDloadVerInfo->softwarever)
     || (NULL == pstDloadVerInfo->productname)
     || (NULL == pstDloadVerInfo->isover))
    {
        CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)(pgucAtSndCodeAddr),
                                            (VOS_CHAR*)(pgucAtSndCodeAddr + gstAtSendData.usBufLen),
                                            "\rswver:%s\r\n",
                                            pstDloadVerInfo->softwarever);

    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)(pgucAtSndCodeAddr),
                                            (VOS_CHAR*)(pgucAtSndCodeAddr+ gstAtSendData.usBufLen),
                                            "\r\nisover:%s\r\n",
                                            pstDloadVerInfo->isover);

    gstAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                            (VOS_CHAR *)(pgucAtSndCodeAddr),
                                            (VOS_CHAR*)(pgucAtSndCodeAddr+ gstAtSendData.usBufLen),
                                            "\r\nproduct name:%s\r\n",
                                            pstDloadVerInfo->productname);

    return AT_OK;
}

/*NV��������*/
VOS_UINT32 atSetNVBackup(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    gstAtSendData.usBufLen = 0;


    ulRst = NVM_UpgradeBackup(EN_NVM_BACKUP_FILE);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }
    g_atNvBackupFlag ++;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );

    return AT_OK;
}

/*NV�ָ�����*/
VOS_UINT32 atSetNVRestore(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    gstAtSendData.usBufLen = 0;


    ulRst = NVM_UpgradeRestore();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );

    return AT_OK;
}

VOS_UINT32 atQryAuthorityVer(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    VOS_UINT32 ulAuthorityVer = 0;
    VOS_UINT8  ucVer[4] ={0};
    VOS_UINT32 i = 0;

    ulRst = At_GetNvAuthorityVer(&ulAuthorityVer);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }

    MSP_MEMCPY(ucVer,&ulAuthorityVer,sizeof(VOS_UINT32));

    for(i = 0;i < 4;i++)
    {
        ucVer[i] = (ucVer[i] > 9 ? 0 : ucVer[i]) + '0';  /**/
    }

    gstAtSendData.usBufLen = 0;
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)pgucAtSndCodeAddr,
                                                (VOS_CHAR*)pgucAtSndCodeAddr,
                                                "\r%s\r",
                                                ucVer
                                                );
    return AT_OK;
}

VOS_UINT32 atQryAuthorityID(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst;
    VOS_UINT8 pData[NV_ITEM_IMEI_SIZE] = {0};
    gstAtSendData.usBufLen = 0;


    ulRst = At_GetImei((VOS_CHAR *)pData);
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }
    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%s\r",
                                           pData
                                         );

    return AT_OK;
}

//�л�������ģʽ����������󽫽�������ģʽ
VOS_UINT32 atSetGodLoad(VOS_UINT8 ucClientId)
{
    gstAtSendData.usBufLen = 0;

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "OK"
                                         );
    mdrv_dload_set_curmode(DLOAD_MODE_DOWNLOAD);

    VOS_TaskDelay(500);

    mdrv_dload_set_softload(true);

    mdrv_sysboot_shutdown();

    return AT_OK;
}

//*****************************************************************************
// ��������: atSetReset
// ��������: ������������ "^RESET"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...

//  2.��    ��   : 2015��01��26��
//    ��    ��   : w00316404

//*****************************************************************************
VOS_UINT32 atSetReset(VOS_UINT8 ucClientId)
{
    gstAtSendData.usBufLen = 0;

    At_FormatResultData(ucClientId, AT_OK);

    VOS_TaskDelay(300); /*wait 300 tick*/

    mdrv_sysboot_restart();

    return AT_SUCCESS;
}

//�Զ��ָ�״̬��ѯ
VOS_UINT32 atSetNVRstSTTS(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;
    gstAtSendData.usBufLen = 0;


    ulRst = At_GetNvRevertState();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );

    return AT_OK;

}

VOS_UINT32 atSetNVFactoryRestore(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRst = AT_OK;

    /*��ΪMODEN���Ż��·������������moden�ڲ�����NV�ָ���ֱ�ӷ���OK*/
    if ( AT_MODEM_USER == gastAtClientTab[ucClientId].UserType )
    {
        return AT_OK;
    }

    ulRst = NVM_RevertFNV();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, ulRst, 0, NULL);
        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );
    return AT_OK;
}

#endif

VOS_UINT32 atSetNVFactoryBack(VOS_UINT8 ucClientId)
{
    VOS_UINT32                          ulRst;

    ulRst = NVM_BackUpFNV();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        printk("atSetNVFactoryBack:nv Backup faile! %d", ulRst);

        CmdErrProc(ucClientId, ulRst, 0, NULL);

        return AT_ERROR;
    }

    ulRst = SC_COMM_Backup();
    if(ulRst != ERR_MSP_SUCCESS)
    {
        printk("atSetNVFactoryBack:SC Backup faile! %d", ulRst);

        CmdErrProc(ucClientId, ulRst, 0, NULL);

        return AT_ERROR;
    }

    gstAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                           (VOS_CHAR *)pgucAtSndCodeAddr,
                                           (VOS_CHAR*)pgucAtSndCodeAddr,
                                           "\r%d\r",
                                           ulRst
                                         );
    return AT_OK;

}

VOS_UINT32  AT_SetLteSdloadPara(VOS_UINT8 ucClientId)
{
    FTM_RD_SDLOAD_REQ_STRU stSdloadSetReq = {0};
    VOS_UINT32 ulRst;

    ulRst = atSendFtmDataMsg(MSP_SYS_FTM_PID, ID_MSG_FTM_SET_SDLOAD_REQ, ucClientId, (VOS_VOID*)(&stSdloadSetReq),
        sizeof(stSdloadSetReq));

    if(AT_SUCCESS == ulRst)
    {
        gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_SDLOAD_SET;
        return AT_WAIT_ASYNC_RETURN;
    }

    return AT_ERROR;
}

/* BEGIN: To_Be_Deleted_V7R2 */
VOS_UINT32 atQryBootRomVerCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_BOOTROMVER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_BOOTROMVER_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}

    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf(
                                                    AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                    (VOS_CHAR *)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
                                                    "\r\n%s\r\n",
                                                    pstCnf->szSendStr
                                                    );

        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}
VOS_UINT32 atQryDLoadVerCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_DLOADVER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_DLOADVER_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}

    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf(
              AT_CMD_MAX_LEN,
              (VOS_CHAR *)(pgucLAtSndCodeAddr),
              (VOS_CHAR *)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
              "\r\n%s\r\n",
              pstCnf->cVer
              );

	    CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }

    return AT_OK;
}

VOS_UINT32 atQryDLoadInfoCnf(VOS_UINT8 ucClientId, VOS_VOID *pMsgBlock)
{
    FTM_RD_DLOADINFO_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_DLOADINFO_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = 0;
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
                                                "\r\nswver:%s\r\n",
                                                pstCnf->szSendSW
                                              );

        gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\nisover:%s\r\n",
                                                pstCnf->szSendISO
                                              );
        gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\nproduct name:%s\r\n",
                                                pstCnf->szSendProductID
                                              );
        gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\ndload type:%s\r\n",
                                                pstCnf->szSendDloadType
                                              );
        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetNVBackupCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_NVBACKUP_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_NVBACKUP_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        g_atNvBackupFlag++;

        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%d\r\n",
                                               pstCnf->ulRetValue
                                             );

        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetNVRestoreCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_NVRESTORE_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_NVRESTORE_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%d\r\n",
                                               pstCnf->ulRetValue
                                             );

        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atQryAuthorityVerCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_AUTHORITYVER_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_AUTHORITYVER_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = 0;
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                    (VOS_CHAR *)pgucLAtSndCodeAddr,
                                                    (VOS_CHAR*)pgucLAtSndCodeAddr,
                                                    "\r\n%s\r\n",
                                                    pstCnf->szAuthorityVer
                                                    );
        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atQryAuthorityIDCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_RD_AUTHORITYID_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;

    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_RD_AUTHORITYID_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}
    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%s,%s\r\n",
                                               pstCnf->szAuthorityID,pstCnf->szAuthorityType
                                             );

	    CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetNVRstSTTSCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_NVRSTSTTS_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;
/*  VOS_BOOL bRet = TRUE;
 */
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_NVRSTSTTS_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
	{
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
		return AT_OK;
	}

    if(pstCnf->ulErrCode != ERR_MSP_SUCCESS)
    {
        CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);
		return AT_OK;
    }
    else
    {
        gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%s\r\n",
                                               pstCnf->szNVRst
                                             );
        CmdErrProc(ucClientId, pstCnf->ulErrCode, gstLAtSendData.usBufLen, pgucLAtSndCodeAddr);
    }
    return AT_OK;
}

VOS_UINT32 atSetSdloadCnf(VOS_UINT8 ucClientId,VOS_VOID *pMsgBlock)
{
    FTM_SET_SDLOAD_CNF_STRU *pstCnf = NULL;
    OS_MSG_STRU*pEvent = NULL;
    gstLAtSendData.usBufLen = 0;
/*  VOS_BOOL bRet = TRUE;
 */
    pEvent = (OS_MSG_STRU*)(((MsgBlock*)pMsgBlock)->aucValue);
	pstCnf = (FTM_SET_SDLOAD_CNF_STRU *)pEvent->ulParam1;

    if(NULL == pstCnf)
    {
    	CmdErrProc(ucClientId, ERR_MSP_FAILURE, 0, NULL);
    	return AT_OK;
    }

    CmdErrProc(ucClientId, pstCnf->ulErrCode, 0, NULL);

    return AT_OK;
}
/* END: To_Be_Deleted_V7R2 */
#if 0
//*****************************************************************************
// ��������: atQryBootRomVer
// ��������: ��ѯ����Э��汾���� "^BOOTROMVER"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************
/*
VOS_UINT32 atQryBootRomVer(VOS_UINT8 ucClientId)
{
    S32_T ret = 0;
    VOS_CHAR *pcStr = NULL;
    VOS_CHAR szSendStr[MSP_UPGRADE_DLOAD_VER_LEN +1] = {0,};
    VOS_UINT32 i = 0;
    gstLAtSendData.usBufLen = 0;
    //�������ڻ�ȡ����Э��汾�ŵ��ڴ�
    pcStr = (VOS_CHAR*)MSP_MALLOC(UPGRADE_STR_BUF_SIZE);
    if( NULL == pcStr )
    {
        return AT_CME_MEMORY_FAILURE;
    }
    MSP_MEMSET(pcStr,0,UPGRADE_STR_BUF_SIZE);
    //���õ���ӿڣ���ȡ����Э��汾��
    ret = sda_GetBootRomVer((S8_T*)pcStr,(S32_T)UPGRADE_STR_BUF_SIZE);
    if( (ERR_MSP_FAILURE == ret)
        || (ERR_MSP_INVALID_PARAMETER == ret)
        || (ret > MSP_UPGRADE_DLOAD_VER_LEN))
    {
        //HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_DLOADVER,0);
        MSP_FREE(pcStr);
        return AT_ERROR;
    }
    for(i=0;i<ret;i++)
    {
        szSendStr[i]=pcStr[i];
    }
    if(szSendStr[ret-1]!= '\0')
    {
        szSendStr[ret] = '\0';
    }
    //szSendStr[ret] = '\0';
    MSP_FREE(pcStr);
    pcStr = NULL;
    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf(
            AT_CMD_MAX_LEN,
            (VOS_CHAR *)(pgucLAtSndCodeAddr),
            (VOS_CHAR *)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
            "\r\n%s\r\n",
            szSendStr
            );


    return AT_OK;
}
*/


//*****************************************************************************
// ��������: atSetDLoadVer
// ��������: ��ѯ����Э��汾���� "^DLOADVER"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************
/* ԭ�汸��
VOS_UINT32 atQryDLoadVer(VOS_UINT8 ucClientId)
{
    S32_T ret = 0;
    VOS_CHAR *pcStr = NULL;


    VOS_CHAR szSendStr[MSP_UPGRADE_DLOAD_VER_LEN +1] = {0,};
    VOS_UINT32 i = 0;
    gstLAtSendData.usBufLen = 0;

    //�������ڻ�ȡ����Э��汾�ŵ��ڴ�
    pcStr = (VOS_CHAR*)MSP_MALLOC(UPGRADE_STR_BUF_SIZE);
    if( NULL == pcStr )
    {
        return AT_CME_MEMORY_FAILURE;
    }
    MSP_MEMSET(pcStr,0,UPGRADE_STR_BUF_SIZE);

    //���õ���ӿڣ���ȡ����Э��汾��
    ret = sda_GetDLoadVer((S8_T*)pcStr,(S32_T)UPGRADE_STR_BUF_SIZE);
    if( (ERR_MSP_FAILURE == ret)
        || (ERR_MSP_INVALID_PARAMETER == ret)
        || (ret > MSP_UPGRADE_DLOAD_VER_LEN))
    {
        HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_DLOADVER,0);
        MSP_FREE(pcStr);
        return AT_ERROR;
    }

    for(i=0;i<ret;i++)
    {
        szSendStr[i]=pcStr[i];
    }

    szSendStr[ret] = '\0';

    MSP_FREE(pcStr);
    pcStr = NULL;
    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf(
            AT_CMD_MAX_LEN,
            (VOS_CHAR *)(pgucLAtSndCodeAddr),
            (VOS_CHAR *)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
            "\r\n%s\r\n",
            szSendStr
            );

    return AT_OK;
}
*/
#endif
#if 0
//*****************************************************************************
// ��������: atSetDLoadInfo
// ��������: ��ȡ������Ϣ���� "^DLOADINFO"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************

//ԭ������
VOS_UINT32 atQryDLoadInfo(VOS_UINT8 ucClientId)
{
    S32_T len = 0;
    S32_T ret = 0;

    //����汾��
    VOS_CHAR *pcStrSoftWare  = NULL;
    VOS_CHAR szSendSW[MSP_UPGRADE_DLOAD_SOFTWARE_LEN +1] = {0,};

    //��̨�汾��
    VOS_CHAR *pcStrIsoVer    = NULL;
    VOS_CHAR szSendISO[MSP_UPGRADE_DLOAD_ISO_LEN+1]={0,};

    //��Ʒ����
    VOS_CHAR *pcStrProductID = NULL;
    VOS_CHAR szSendProductID[MSP_UPGRADE_DLOAD_PRODUCTID_LEN+1]={0,};

    //��������
    VOS_CHAR *pcStrDLoadType = NULL;
    VOS_CHAR szSendDloadType[4]={0,};

    VOS_UINT32 i = 0;

    gstLAtSendData.usBufLen = 0;

    //��ȡ����汾���ַ���
    {
        pcStrSoftWare = (VOS_CHAR*)MSP_MALLOC(UPGRADE_STR_BUF_SIZE);
        if( NULL == pcStrSoftWare )
        {
            return AT_CME_MEMORY_FAILURE;
        }
        MSP_MEMSET(pcStrSoftWare,0,UPGRADE_STR_BUF_SIZE);

        ret = sda_GetSoftwareVer((S8_T*)pcStrSoftWare, (S32_T)UPGRADE_STR_BUF_SIZE);
        if( (ERR_MSP_FAILURE == ret)
            ||(ERR_MSP_INVALID_PARAMETER == ret)
            || (ret > MSP_UPGRADE_DLOAD_SOFTWARE_LEN))
        {
            HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_DLOADINFO,0);
            MSP_FREE(pcStrSoftWare);
            return AT_ERROR;
        }
        //swver:
        for( i = 0; i < ret; i++ )
        {
            szSendSW[i]=pcStrSoftWare[i];
        }
        szSendSW[ret]='\0';

        MSP_FREE(pcStrSoftWare);
        pcStrSoftWare = NULL;
    }

    //��̨�汾���ַ���
    {
        pcStrIsoVer = (VOS_CHAR*)MSP_MALLOC(UPGRADE_STR_BUF_SIZE);
        if( NULL == pcStrIsoVer )
        {
            return AT_CME_MEMORY_FAILURE;
        }
        MSP_MEMSET(pcStrIsoVer,0,UPGRADE_STR_BUF_SIZE);

        ret = sda_GetISOVer((S8_T*)pcStrIsoVer, (S32_T)UPGRADE_STR_BUF_SIZE);
        if( (ERR_MSP_FAILURE == ret)
            || (ERR_MSP_INVALID_PARAMETER == ret)
            || (ret > MSP_UPGRADE_DLOAD_ISO_LEN))
        {
            HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_DLOADINFO,0);
            MSP_FREE(pcStrIsoVer);
            return AT_ERROR;
        }
        //isover:
        for(i=0;i<ret;i++)
        {
            szSendISO[i]=pcStrIsoVer[i];
        }
        szSendISO[ret]='\0';

        MSP_FREE(pcStrIsoVer);
        pcStrIsoVer = NULL;
    }

    //��Ʒ�����ַ���
    {
        pcStrProductID = (VOS_CHAR*)MSP_MALLOC(UPGRADE_STR_BUF_SIZE);
        if( NULL == pcStrProductID )
        {
            return AT_CME_MEMORY_FAILURE;
        }
        MSP_MEMSET(pcStrProductID,0,UPGRADE_STR_BUF_SIZE);

        ret = sda_GetProductId((S8_T*)pcStrProductID, (S32_T)UPGRADE_STR_BUF_SIZE);
        if( (ERR_MSP_FAILURE == ret)
            ||(ERR_MSP_INVALID_PARAMETER == ret)
            || (ret > MSP_UPGRADE_DLOAD_SOFTWARE_LEN))
        {
            HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_DLOADINFO,0);
            MSP_FREE(pcStrProductID);
            return AT_ERROR;
        }
        //product name:
        for(i=0;i<ret;i++)
        {
            szSendProductID[i]= pcStrProductID[i];
        }

        szSendProductID[ret]='\0';

        MSP_FREE(pcStrProductID);
        pcStrProductID = NULL;

    }

    //��ȡ��������
    {
        ret = sda_GetDloadType();
        if((ret != 0) && (ret != 1))
        {
            HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_DLOADINFO,0);
            return AT_ERROR;
        }
        //dload type:
        if(ret == 0)
        {
            szSendDloadType[0]='0';
        }
        else
        {
            szSendDloadType[0]='1';
        }
        szSendDloadType[1]='\0';

    }

    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr + gstLAtSendData.usBufLen),
                                                "\r\nswver:%s\r\n",
                                                szSendSW
                                              );

    gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\nisover:%s\r\n",
                                                szSendISO
                                              );
    gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\nproduct name:%s\r\n",
                                                szSendProductID
                                              );
    gstLAtSendData.usBufLen += (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                (VOS_CHAR *)(pgucLAtSndCodeAddr),
                                                (VOS_CHAR*)(pgucLAtSndCodeAddr+ gstLAtSendData.usBufLen),
                                                "\r\ndload type:%s\r\n",
                                                szSendDloadType
                                              );
    return AT_OK;
}
#endif
#if 0
//*****************************************************************************
// ��������: atSetNVBackup
// ��������: NV�������� "^NVBACKUP"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************
/*
//ԭ������
VOS_UINT32 atSetNVBackup(VOS_UINT8 ucClientId)
{

    VOS_UINT32 ret = AT_OK;

    //��¼һ��NV�����ı���
    g_atNvBackupFlag++;

    ret = LNVM_UpgradeBackup(2);
	//ret = 0;
    if( ret > 10)
    {
        HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_NVBACKUP,0);
        return AT_ERROR;
    }
	gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%d\r\n",
                                               ret
                                             );
    return AT_OK;
}
*/



//*****************************************************************************
// ��������: atSetNVRestore
// ��������: NV�ָ����� "^NVRESTORE"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************
/*
VOS_UINT32 atSetNVRestore(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ret = AT_OK;

    ret = LNVM_UpgradeRestore(0,0,0,0);
	//ret = 0;
    if( ret > 10)
    {
        HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_NVRESTORE,0);
        return AT_ERROR;
    }
	gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%d\r\n",
                                                ret
                                              );
    return AT_OK;
}
*/


//*****************************************************************************
// ��������: atSetAuthorityVer
// ��������: ��ѯ��ȨЭ��汾�� "^AUTHORITYVER"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************
/*
//ԭ������
VOS_UINT32 atQryAuthorityVer(VOS_UINT8 ucClientId)
{
    S32_T ret = 0;
    VOS_CHAR *pcStr = NULL;
    VOS_CHAR szAuthorityVer[MSP_UPGRADE_DLOAD_VER_LEN +1] = {0,};
    VOS_UINT32 i = 0;

    //Ϊ��ȡ��ȨЭ��汾�����ڴ�
    pcStr = (VOS_CHAR*)MSP_MALLOC(UPGRADE_STR_BUF_SIZE);
    if( NULL == pcStr )
    {
        return AT_CME_MEMORY_FAILURE;
    }
    MSP_MEMSET(pcStr,0,UPGRADE_STR_BUF_SIZE);

    //��ȡ��ȨЭ��汾
    ret = sda_GetAuthorityVer((S8_T *)pcStr, (S32_T)UPGRADE_STR_BUF_SIZE);

    if( (ERR_MSP_FAILURE == ret) || (ret > MSP_UPGRADE_DLOAD_VER_LEN))
    {
        HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_AUTHORITYVER,0);
        MSP_FREE(pcStr);
        return AT_ERROR;
    }

    for(i=0;i<ret;i++)
    {
        szAuthorityVer[i]=pcStr[i];
    }

    szAuthorityVer[ret] = '\0';

    MSP_FREE(pcStr);
    pcStr = NULL;

    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                                  (VOS_CHAR *)pgucLAtSndCodeAddr,
                                                  (VOS_CHAR*)pgucLAtSndCodeAddr,
                                                  "\r\n%s\r\n",
                                                  szAuthorityVer
                                                );
    return AT_OK;

}
*/




//*****************************************************************************
// ��������: atSetAuthorityID
// ��������: ��ѯ��Ȩ��ʶ "^AUTHORITYID"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************
/*
//ԭ������
VOS_UINT32 atQryAuthorityID(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ret = AT_OK;
    VOS_CHAR *pcStr = NULL;
    VOS_CHAR szAuthorityID[MSP_UPGRADE_DLOAD_VER_LEN +1] = {0,};
    VOS_CHAR szAuthorityType[2]={0,};
    VOS_UINT32 i = 0;
    gstLAtSendData.usBufLen = 0;

    pcStr = (VOS_CHAR*)MSP_MALLOC(UPGRADE_STR_BUF_SIZE);
    if( NULL == pcStr )
    {
        return AT_CME_MEMORY_FAILURE;
    }
    MSP_MEMSET(pcStr,0,UPGRADE_STR_BUF_SIZE);

    //��ȡ��ȨЭ���ʶ��IMEI��
    ret = sda_GetAuthorityId((S8_T*)pcStr, (S32_T)UPGRADE_STR_BUF_SIZE);
    if( (ERR_MSP_FAILURE == ret) || (ret > MSP_UPGRADE_DLOAD_VER_LEN))
    {
        HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_AUTHORITYID,0);
        MSP_FREE(pcStr);
        return AT_ERROR;
    }

    for(i=0;i<ret;i++)
    {
        szAuthorityID[i]=pcStr[i];
    }

    szAuthorityID[ret] = '\0';

    MSP_FREE(pcStr);
    pcStr = NULL;

    //��ȡ��ȨЭ������
    ret = sda_GetAuthorityType();
    if(ret == 0)
    {
        szAuthorityType[0]='0';
        szAuthorityType[1]='\0';
    }
    else
    {
        HAL_DIAG_SDM_FUN(EN_SDM_AT_UPGRADE_ERR,ret,AT_UPGRADE_AUTHORITYID,0);
        return AT_ERROR;
    }
    gstLAtSendData.usBufLen = 0;
    gstLAtSendData.usBufLen = (VOS_UINT16)At_sprintf( AT_CMD_MAX_LEN,
                                               (VOS_CHAR *)pgucLAtSndCodeAddr,
                                               (VOS_CHAR*)pgucLAtSndCodeAddr,
                                               "\r\n%s,%s\r\n",
                                               szAuthorityID,szAuthorityType
                                             );
    return AT_OK;
}
*/
// ��ѯ��Ȩ��ʶ

//*****************************************************************************
// ��������: atSetGodLoad
// ��������: �л�����������ģʽ "^GODLOAD"
//
// ����˵��:
//   ulIndex [in] �û�����
//
// �� �� ֵ:
//    TODO: ...
//
// ����Ҫ��: TODO: ...
// ���þ���: TODO: ...
//*****************************************************************************
/*
HTIMER g_hTimerDload = 0;
VOS_UINT32 atSetGodLoad(VOS_UINT8 ucClientId)
{
    VOS_UINT32 ulRet = 0;
    //gastAtClientTab[ulIndex].CmdCurrentOpt = AT_CMD_GODLOAD;
	gastAtClientTab[ucClientId].CmdCurrentOpt = AT_CMD_GODLOAD;
    sda_SetCurMode(DLOAD_MODE_DOWNLOAD);
	//atStartTimer(ucClientId, 1);

    //���������֮ǰNVû�б���
    if(g_atNvBackupFlag == 0)
    {
        //�������IMEI�����ڻ���IMEI�쳣��ʱ��PC�����·�NV���ݣ����ǻ��ǻ�����NV�ļ�
        //���Դ˴���Ҫ����һ�α���
        LNVM_UpgradeBackup(1);
    }

    ulRet = OSM_StartTimer((VOS_UINT32 *)(&g_hTimerDload),MSP_L4_AT_LTE_PID,
        800, NULL, VOS_RELTIMER_NOLOOP);

	if(ERR_MSP_SUCCESS != ulRet)
	{
            //
	}

    gstLAtSendData.usBufLen = 0;

    return AT_OK;
}
*/
#endif

