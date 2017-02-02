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

/*lint -e767*/
#define    THIS_FILE_ID        PS_FILE_ID_PSDIPC_C
/*lint +e767*/

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "product_config.h"

#if (FEATURE_ON == FEATURE_AT_HSIC)
#include "PsTypeDef.h"
#include "PsDipc.h"
#include "PsCommonDef.h"

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

/* ��ӡ���� */
VOS_UINT32                              g_ulDipcPrintFlag   = PS_FALSE;

/* ��Ϣ���ٿ��� */
VOS_UINT32                              g_ulDipcTraceFlag   = PS_FALSE;

/*����ʹ��ȫ�ֱ���,֮������2��������ΪDIPCΪAPIģʽ����������2������������*/
TRACE_UL_DIPC_DATA_MSG                  *g_pstDipcTraceUlData;
TRACE_DL_DIPC_DATA_MSG                  *g_pstDipcTraceDlData;

/* DIPCͨ����ͳ����Ϣ */
DIPC_STATIC_INFO_STRU                   g_stDipcStaticInfo;

/* �豸����Ϣ�������豸�ڲ���Ϣ���豸��SERVICE֮���ӳ���ϵ */
DEV_INFO_STRU                           g_astDevInfo[DIPC_DEV_NUM];

/* �豸������֮���ӳ���ϵ������ʹ�� */
DEV_SERVICE_INFO_STRU                   g_astDevService[DIPC_DEV_NUM];

/* RAB ID��Service֮���ӳ���ϵ������ʹ�� */
RAB_SERVICE_INFO_STRU                   g_astRabService[RAB_MAX_NUM];

/* SERVICE��Ϣ */
TOTAL_SERVICE_INFO_STRU                 g_stTotalServiceInfo;

/* DIPC���ݶ��� */
DIPC_DATA_Q_CTRL_ST                     g_stDipcDataQ;


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

VOS_VOID DIPC_PrintLog
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString
)
{
    if (PS_TRUE == g_ulDipcPrintFlag)
    {
        vos_printf(pcString);
    }

    return;
}



VOS_VOID DIPC_PrintLog1
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1
)
{
    if (PS_TRUE == g_ulDipcPrintFlag)
    {
        vos_printf(pcString, lPara1);
    }

    return;
}



VOS_VOID DIPC_PrintLog2
(
    VOS_UINT32      ulModuleId,
    VOS_UINT32      ulSubMod,
    VOS_UINT32      ulLevel,
    VOS_CHAR       *pcString,
    VOS_INT32       lPara1,
    VOS_INT32       lPara2
)
{
    if (PS_TRUE == g_ulDipcPrintFlag)
    {
        vos_printf(pcString, lPara1, lPara2);
    }

    return;
}


VOS_UINT32  DIPC_Snd1stDataNotify(VOS_VOID)
{
    DIPC_DATA_PROC_NOTIFY_MSG    *pMsg;
    VOS_INT32                    lLockKey;


    /*������Ϣ�ڴ�:*/
    pMsg = (DIPC_DATA_PROC_NOTIFY_MSG *) PS_ALLOC_MSG( PS_PID_APP_DIPC,
        sizeof(DIPC_DATA_PROC_NOTIFY_MSG) - VOS_MSG_HEAD_LENGTH );

    if (VOS_NULL_PTR == pMsg)
    {
        /*��ӡ������Ϣ---������Ϣ��ʧ��:*/
        DIPC_PrintLog( PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_Snd1stDataNotify:WARNING:Allocates message for DIPC_Snd1stDataNotify FAIL!\r\n" );
        return PS_FAIL;
    }

    /*��д��Ϣ����:*/
    pMsg->ulReceiverCpuId   = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid     = PS_PID_APP_DIPC;
    pMsg->enMsgType         = ID_DIPC_DATA_NOTIFY_REQ;

    lLockKey = VOS_SplIMP();
    g_stDipcDataQ.ulNotifyMsgCnt++;
    VOS_Splx(lLockKey);

    /*������Ϣ:*/
    if (VOS_OK != PS_SEND_MSG(PS_PID_APP_DIPC, pMsg))
    {
        /*��ӡ������Ϣ---������Ϣʧ��:*/
        DIPC_PrintLog( PS_PID_APP_DIPC, 0, PS_PRINT_WARNING, "SEND DIPC_Snd1stDataNotify msg FAIL!\r\n" );
        return PS_FAIL;
    }

    return PS_SUCC;
}
VOS_VOID DIPC_ClearDataQ(VOS_VOID)
{
    IMM_ZC_STRU    *pstMem;
    VOS_INT32       lLockKey;

    for(;;)
    {
        lLockKey    = VOS_SplIMP();

        if ( 0 == IMM_ZcQueueLen(&g_stDipcDataQ.stDipcDataQ) )
        {
            VOS_Splx(lLockKey);
            break;
        }

        VOS_Splx(lLockKey);

        pstMem  = (IMM_ZC_STRU *)IMM_ZcDequeueHead(&g_stDipcDataQ.stDipcDataQ);

        IMM_ZcFree(pstMem);
    }

    return;
}


VOS_UINT32  DIPC_EnqueueData(IMM_ZC_STRU *pstImmZc)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;    /* ��¼�����Ƿ������ɿյ��ǿյ�ת�� */
    IMM_ZC_HEAD_STRU                   *pstDataQ;
    VOS_INT32                           lLockKey;

    pstDataQ   = &g_stDipcDataQ.stDipcDataQ;

    /* A��������Բ���ʵʱ��֮ǰ��ȡ���Ⱥ����зֿ����жϣ�����������������ʱ
       �ж϶��в�Ϊ�գ���������DIPC����õ����ȣ��Ѷ���ȡ�պ��ٽ�����ӵ������
       ��Ϊ����ȡ�������ݸ�������Ӱ�����һ�����ж��� */
    lLockKey = VOS_SplIMP();
    if (( 0 == IMM_ZcQueueLen(pstDataQ)) && (0 == g_stDipcDataQ.ulNotifyMsgCnt))
    {
        ulNonEmptyEvent = PS_TRUE;
    }

    /*�����ݽ��������β��*/
    IMM_ZcQueueTail(pstDataQ, pstImmZc);
    VOS_Splx(lLockKey);

    if (PS_TRUE == ulNonEmptyEvent)
    {
        /*��DIPC�������ݴ���ָʾ*/
       if (PS_SUCC != DIPC_Snd1stDataNotify())
       {
            /* ������Ϣ֪ͨʧ�ܣ���Ҫ����������� */
            DIPC_ClearDataQ();
            DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                "DIPC, DIPC_EnqueueData, WARNING, DIPC_Snd1stDataNotify fail!\r\n");
            return PS_FAIL;
       }
    }

    return PS_SUCC;
} /* DIPC_EnqueueData */




VOS_VOID DIPC_DEV_HsicAcmFreeDlDataCB(IMM_ZC_STRU *pstBuf)
{
    IMM_ZcFree(pstBuf);
    return;
}



VOS_UINT32 DIPC_DEV_AcmOpenDevice(DEV_INFO_STRU *pstDevInfo)
{
    UDI_OPEN_PARAM_S        stParam;

    stParam.devid   = pstDevInfo->enUdiDevId;
    pstDevInfo->slUdiHsicHdl = mdrv_udi_open(&stParam);

    if (UDI_INVAL_DEV_ID == pstDevInfo->slUdiHsicHdl)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_AcmOpenDevice, Call mdrv_udi_open return UDI_INVAL_DEV_ID.\n");
        return PS_FAIL;
    }

    /* ע��HSIC ACM �û���ͨ���������ݽ��ջص� */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiHsicHdl, ACM_IOCTL_SET_READ_CB, pstDevInfo->pRxFunc.pAcmRxFunc))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_AcmOpenDevice, ERROR, Set HSIC ACM data read callback failed!\n");
        return PS_FAIL;
    }

    /* ע��HSIC ACM �û���ͨ�����������ڴ��ͷŽӿ� */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiHsicHdl, ACM_IOCTL_SET_FREE_CB, DIPC_DEV_HsicAcmFreeDlDataCB))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_AcmOpenDevice, ERROR, Set HSIC ACM memory free callback failed!\n");
        return PS_FAIL;
    }

    return PS_SUCC;
}



VOS_UINT32 DIPC_DEV_NcmOpenDevice(DEV_INFO_STRU *pstDevInfo)
{
    UDI_OPEN_PARAM_S                      stParam;

    stParam.devid   = pstDevInfo->enUdiDevId;
    pstDevInfo->slUdiHsicHdl = mdrv_udi_open(&stParam);

    if (UDI_INVAL_DEV_ID == pstDevInfo->slUdiHsicHdl)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,
            "DIPC, DIPC_DEV_NcmOpenDevice, Call mdrv_udi_open return UDI_INVAL_DEV_ID.\n");
        return PS_FAIL;
    }

    /* ע��HSIC NCM �û���ͨ���������ݽ��ջص� */
    if (VOS_OK != mdrv_udi_ioctl (pstDevInfo->slUdiHsicHdl, NCM_IOCTL_REG_UPLINK_RX_FUNC, pstDevInfo->pRxFunc.pNcmRxFunc))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_ERROR,"DIPC_DEV_NcmOpenDevice, regist RxFunc fail!");
        return PS_FAIL;
    }

    return PS_SUCC;
}
VOS_UINT32 DIPC_DEV_AcmGetUlDataBuf(UDI_HANDLE slUdiHsicAcmHdl, IMM_ZC_STRU **ppstBuf)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           lResult;

    stCtlParam.pVirAddr = VOS_NULL_PTR;
    stCtlParam.pPhyAddr = VOS_NULL_PTR;

    /* ��ȡ������������buffer */
    lResult= mdrv_udi_ioctl(slUdiHsicAcmHdl, ACM_IOCTL_GET_RD_BUFF, &stCtlParam);
    if ( VOS_OK != lResult )
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_AcmGetUlDataBuf, WARNING, Get modem buffer failed code <1>!\r\n",
            lResult);
        return PS_FAIL;
    }

    if (VOS_NULL_PTR == stCtlParam.pVirAddr)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_AcmGetUlDataBuf, WARNING, Data buffer is NULL!\r\n");
        return PS_FAIL;
    }

    *ppstBuf = (IMM_ZC_STRU *)stCtlParam.pVirAddr;

    return PS_SUCC;
}
VOS_UINT32 DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID_ENUM_UINT32 enDeviceId)
{
    UDI_HANDLE                          slUdiHandle;
    IMM_ZC_STRU                        *pstBuf;

    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(enDeviceId);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulGetDataFailNums++;
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_UsbAcmReadUlData, can not get the slUdiHandle,ulDeviceId <1>",
            (VOS_INT32)enDeviceId);
        return PS_FAIL;
    }

    /* �������нӿڣ������ȡ�����ݻ�Ӱ����һ�����ݵĽ��� */
    if (PS_SUCC != DIPC_DEV_AcmGetUlDataBuf(slUdiHandle, &pstBuf))
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DEV_UsbAcmReadUlData, call DIPC_DEV_UsbAcmReadUlData return fail!\n");
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulSuccGetUlPacketNums++;

    return DIPC_DEV_UlDataProc(enDeviceId, pstBuf);
}
VOS_UINT32 DIPC_DEV_UsbAcm1ReadUlData( VOS_VOID)
{
    DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID1);
    return VOS_OK;
}



VOS_UINT32 DIPC_DEV_UsbAcm3ReadUlData( VOS_VOID)
{
    DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID2);
    return VOS_OK;
}



VOS_UINT32 DIPC_DEV_UsbAcm5ReadUlData( VOS_VOID)
{
    DIPC_DEV_UsbAcmReadUlData(DIPC_DEV_ID3);
    return VOS_OK;
}



VOS_UINT32 DIPC_DEV_UsbAcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf)
{
    ACM_WR_ASYNC_INFO                   stCtlParam;
    VOS_INT32                           ulResult;


    /* ��д�������ڴ��ַ */
    stCtlParam.pVirAddr                 = (VOS_CHAR*)pstBuf;
    stCtlParam.pPhyAddr                 = VOS_NULL_PTR;
    stCtlParam.u32Size                  = 0;
    stCtlParam.pDrvPriv                 = VOS_NULL_PTR;

    /* �첽��ʽд����*/
    ulResult = mdrv_udi_ioctl(slUdiHandle, ACM_IOCTL_WRITE_ASYNC, &stCtlParam);

    if ( VOS_OK != ulResult )
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_DEV_UsbAcmWriteData, Error, Write data failed with code <1>!",
            ulResult);

        return PS_FAIL;
    }

    return PS_SUCC;
}



VOS_UINT32 DIPC_DEV_UsbNcm0ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    UDI_HANDLE              slUdiHandle;
    IMM_ZC_STRU            *pstImmZcData = (IMM_ZC_STRU*)pPktNode;  /*ImmZc��sk_buff��ȫһ�£�ֱ��ǿת*/


    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID1);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID1].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm0ReadUlData, can not get the slUdiHandle, DIPC_DEV_ID1.");
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    if (ulhandle != slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID1].ulGetDataFailNums++;
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm0ReadUlData, Drv Handle <1> is not same as DevID1 Handle <2>.",
            ulhandle, slUdiHandle);
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID1].ulSuccGetUlPacketNums++;

    DIPC_DEV_UlDataProc(DIPC_DEV_ID1, pstImmZcData);
    return PS_SUCC;
}
VOS_UINT32 DIPC_DEV_UsbNcm1ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    UDI_HANDLE              slUdiHandle;
    IMM_ZC_STRU            *pstImmZcData = (IMM_ZC_STRU*)pPktNode;  /*ImmZc��sk_buff��ȫһ�£�ֱ��ǿת*/


    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID2);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID2].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm1ReadUlData, can not get the slUdiHandle, DIPC_DEV_ID2.");
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    if (ulhandle != slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID2].ulGetDataFailNums++;
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm1ReadUlData, Drv Handle <1> is not same as DevID2 Handle <2>.",
            ulhandle, slUdiHandle);
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID2].ulSuccGetUlPacketNums++;

    DIPC_DEV_UlDataProc(DIPC_DEV_ID2, pstImmZcData);
    return PS_SUCC;
}
VOS_UINT32 DIPC_DEV_UsbNcm2ReadUlData(UDI_HANDLE ulhandle, VOS_VOID *pPktNode)
{
    UDI_HANDLE              slUdiHandle;
    IMM_ZC_STRU            *pstImmZcData = (IMM_ZC_STRU*)pPktNode;  /*ImmZc��sk_buff��ȫһ�£�ֱ��ǿת*/


    slUdiHandle = DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID3);
    if (UDI_INVAL_DEV_ID == slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID3].ulGetDataFailNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm2ReadUlData, can not get the slUdiHandle, DIPC_DEV_ID3.");
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    if (ulhandle != slUdiHandle)
    {
        g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID3].ulGetDataFailNums++;
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_UsbNcm2ReadUlData, Drv Handle <1> is not same as DevID3 Handle <2>.",
            ulhandle, slUdiHandle);
        IMM_ZcFree(pstImmZcData);
        return PS_FAIL;
    }

    g_stDipcStaticInfo.astDipcDevStaticInfo[DIPC_DEV_ID3].ulSuccGetUlPacketNums++;

    DIPC_DEV_UlDataProc(DIPC_DEV_ID3, pstImmZcData);
    return PS_SUCC;
}
VOS_UINT32 DIPC_DEV_UsbNcmWriteData(UDI_HANDLE slUdiHandle, IMM_ZC_STRU *pstBuf)
{
    VOS_INT32                           ulResult;
    VOS_UINT32                          ulSize = IMM_ZcGetUsedLen(pstBuf);

    /* Ϊ�˼���AP��һ�ο��������Դ˴�Ԥ��14�ֽڣ�����AP�����MACͷ�� */
    IMM_ZcPush(pstBuf,IMM_MAC_HEADER_RES_LEN);

    /* �첽��ʽд��*/
    ulResult = mdrv_udi_write(slUdiHandle, pstBuf, ulSize);

    if ( VOS_OK != ulResult )
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_DEV_UsbNcmWriteData, Error, Write data failed with code <1>!",
            ulResult);
        return PS_FAIL;
    }

    return PS_SUCC;
}



VOS_UINT32 DIPC_DEV_UsbWriteData(DIPC_DEV_ID_ENUM_UINT32 enDipcDevId, IMM_ZC_STRU *pstBuf)
{
    DEV_INFO_STRU                           *pstDevInfo;

    pstDevInfo  = &g_astDevInfo[enDipcDevId];

    if (VOS_NULL_PTR == pstDevInfo->pTxFunc)
    {
        return PS_FAIL;
    }

    return pstDevInfo->pTxFunc(pstDevInfo->slUdiHsicHdl, pstBuf);
}



VOS_UINT32 DIPC_DEV_PortInit( VOS_VOID )
{
    DIPC_DEV_ID_ENUM_UINT32         enDipcDevId;
    DEV_INFO_STRU                  *pstDevInfo;


    /*  ��Ʒ��֧��HSIC���ԣ�ֱ�ӳ�ʼ���ɹ� */
    if (BSP_MODULE_SUPPORT != mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC))
    {
        return VOS_OK;
    }

    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC_NCM))
    {
        g_astDevInfo[DIPC_DEV_ID1].enUdiDevId           = UDI_NCM_HSIC_NCM0_ID;
        g_astDevInfo[DIPC_DEV_ID1].pRxFunc.pNcmRxFunc   = DIPC_DEV_UsbNcm0ReadUlData;
        g_astDevInfo[DIPC_DEV_ID1].pTxFunc              = DIPC_DEV_UsbNcmWriteData;

        g_astDevInfo[DIPC_DEV_ID2].enUdiDevId           = UDI_NCM_HSIC_NCM1_ID;
        g_astDevInfo[DIPC_DEV_ID2].pRxFunc.pNcmRxFunc   = DIPC_DEV_UsbNcm1ReadUlData;
        g_astDevInfo[DIPC_DEV_ID2].pTxFunc              = DIPC_DEV_UsbNcmWriteData;

        g_astDevInfo[DIPC_DEV_ID3].enUdiDevId           = UDI_NCM_HSIC_NCM2_ID;
        g_astDevInfo[DIPC_DEV_ID3].pRxFunc.pNcmRxFunc   = DIPC_DEV_UsbNcm2ReadUlData;
        g_astDevInfo[DIPC_DEV_ID3].pTxFunc              = DIPC_DEV_UsbNcmWriteData;

        for(enDipcDevId = 0; enDipcDevId < DIPC_DEV_NUM; enDipcDevId++)
        {
            pstDevInfo = &g_astDevInfo[enDipcDevId];
            pstDevInfo->slUdiHsicHdl    = UDI_INVAL_DEV_ID;

            /* ���˿ڴ�ʧ�ܣ���������һ���˿� */
            if (PS_SUCC != DIPC_DEV_NcmOpenDevice(pstDevInfo))
            {
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC_DEV_PortInit, Open Device <1> fail.\n", (VOS_INT32)enDipcDevId);
            }
        }
    }
    else
    {
        g_astDevInfo[DIPC_DEV_ID1].enUdiDevId           = UDI_ACM_HSIC_ACM1_ID;
        g_astDevInfo[DIPC_DEV_ID1].pRxFunc.pAcmRxFunc   = DIPC_DEV_UsbAcm1ReadUlData;
        g_astDevInfo[DIPC_DEV_ID1].pTxFunc              = DIPC_DEV_UsbAcmWriteData;

        g_astDevInfo[DIPC_DEV_ID2].enUdiDevId           = UDI_ACM_HSIC_ACM3_ID;
        g_astDevInfo[DIPC_DEV_ID2].pRxFunc.pAcmRxFunc   = DIPC_DEV_UsbAcm3ReadUlData;
        g_astDevInfo[DIPC_DEV_ID2].pTxFunc              = DIPC_DEV_UsbAcmWriteData;

        g_astDevInfo[DIPC_DEV_ID3].enUdiDevId           = UDI_ACM_HSIC_ACM5_ID;
        g_astDevInfo[DIPC_DEV_ID3].pRxFunc.pAcmRxFunc   = DIPC_DEV_UsbAcm5ReadUlData;
        g_astDevInfo[DIPC_DEV_ID3].pTxFunc              = DIPC_DEV_UsbAcmWriteData;

        for(enDipcDevId = 0; enDipcDevId < DIPC_DEV_NUM; enDipcDevId++)
        {
            pstDevInfo = &g_astDevInfo[enDipcDevId];
            pstDevInfo->slUdiHsicHdl    = UDI_INVAL_DEV_ID;

            /* ���˿ڴ�ʧ�ܣ���������һ���˿� */
            if (PS_SUCC != DIPC_DEV_AcmOpenDevice(pstDevInfo))
            {
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC_DEV_PortInit, Open Device <1> fail.\n", (VOS_INT32)enDipcDevId);
            }
        }
    }

    return VOS_OK;
}
VOS_VOID DIPC_DEV_AddNewIpTypeService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo)
{
    DEV_SERVICE_INFO_STRU          *pstDevServiceInfo;

    pstDevServiceInfo = &g_astDevService[enDevId];

    pstDevServiceInfo->apstServiceInfo[enDipcServiceType] = pstServiceInfo;
    DIPC_SET_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enDipcServiceType);

    pstDevServiceInfo->ulServiceCnt++;

    return;
}


VOS_UINT32 DIPC_DEV_DelIpTypeService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    DEV_SERVICE_INFO_STRU          *pstDevServiceInfo;

    pstDevServiceInfo = &g_astDevService[enDevId];
    pstDevServiceInfo->apstServiceInfo[enDipcServiceType] = VOS_NULL_PTR;
    DIPC_CLR_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enDipcServiceType);
    pstDevServiceInfo->ulServiceCnt--;

    return PS_SUCC;
}



DIPC_DEV_ID_ENUM_UINT32 DIPC_DEV_GetDevIdByUdiId(UDI_DEVICE_ID_E enUdiDevId)
{
    DIPC_DEV_ID_ENUM_UINT32             enDevId;

    if ((UDI_ACM_HSIC_ACM1_ID != enUdiDevId)
        && (UDI_ACM_HSIC_ACM3_ID != enUdiDevId)
        && (UDI_ACM_HSIC_ACM5_ID != enUdiDevId)
        && (UDI_NCM_HSIC_NCM0_ID != enUdiDevId)
        && (UDI_NCM_HSIC_NCM1_ID != enUdiDevId)
        && (UDI_NCM_HSIC_NCM2_ID != enUdiDevId))
    {
        return DIPC_DEV_BUTT;
    }

    for (enDevId = DIPC_DEV_ID1; enDevId < DIPC_DEV_BUTT; enDevId++)
    {
        if (g_astDevInfo[enDevId].enUdiDevId == enUdiDevId)
        {
            break;
        }
    }

    return enDevId;
}



UDI_HANDLE DIPC_DRV_GetDevHandleByDevId(DIPC_DEV_ID_ENUM_UINT32 enDevId)
{
    if (DIPC_DEV_BUTT <= enDevId)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DRV_GetDevHandleByDevId, enDevId <1> exceed the range.\n",
            (VOS_INT32)enDevId);
        return INVALID_RABID_VALUE;
    }

    return g_astDevInfo[enDevId].slUdiHsicHdl;
}


VOS_UINT32 DIPC_DEV_CheckUdiDevIdPara(UDI_DEVICE_ID_E enUdiDevId)
{
    if (BSP_MODULE_SUPPORT == mdrv_misc_support_check(BSP_MODULE_TYPE_HSIC_NCM))
    {
        if ((UDI_NCM_HSIC_NCM0_ID != enUdiDevId)
            && (UDI_NCM_HSIC_NCM1_ID != enUdiDevId)
            && (UDI_NCM_HSIC_NCM2_ID != enUdiDevId))
        {
            return VOS_ERR;
        }

    }
    else
    {
        if ((UDI_ACM_HSIC_ACM1_ID != enUdiDevId)
            && (UDI_ACM_HSIC_ACM3_ID != enUdiDevId)
            && (UDI_ACM_HSIC_ACM5_ID != enUdiDevId))
        {
            return VOS_ERR;
        }
    }

    return VOS_OK;
}


VOS_UINT32 DIPC_DEV_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf)
{
    VOS_UINT16  usApp;      /* ʹ��skb_buff�ṹ�������ֶδ��������кͲ�����Ϣ */

    if (VOS_NULL_PTR == pstBuf)
    {
        return PS_FAIL;
    }

    usApp = DIPC_SET_APP(ID_DIPC_UL_DATA, enDeviceId);

    IMM_ZcSetUserApp(pstBuf, usApp);

    return DIPC_EnqueueData(pstBuf);
}
SERVICE_INFO_STRU* DIPC_MGR_RegNewService(SERVICE_INFO_STRU *pstServInputInfo)
{
    SERVICE_INFO_STRU  *pstGetServInfo;
    VOS_UINT8           ucServiceNo;

    if (SERVICE_MAX_NUM <= g_stTotalServiceInfo.ulServiceNum)
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_RegNewService, WARNING, Service is FULL!\r\n");
        return VOS_NULL_PTR;
    }

    for (ucServiceNo = 0; ucServiceNo < SERVICE_MAX_NUM; ucServiceNo ++)
    {
        if (0 == DIPC_GET_SERVICE_STRU_USE(g_stTotalServiceInfo.ulServiceMask, ucServiceNo))
        {
            break;
        }
    }

    if (SERVICE_MAX_NUM == ucServiceNo)
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_RegNewService, WARNING, Service Mask <1> is FULL, but ServiceNum <2> is not full!\r\n",
            (VOS_INT32)g_stTotalServiceInfo.ulServiceMask, (VOS_INT32)g_stTotalServiceInfo.ulServiceNum);
        return VOS_NULL_PTR;
    }

    pstGetServInfo = &g_stTotalServiceInfo.astServiceInfo[ucServiceNo];

    pstGetServInfo->ucServiceIndex  = ucServiceNo;
    pstGetServInfo->ucRabId         = pstServInputInfo->ucRabId;
    pstGetServInfo->enDipcDevId     = pstServInputInfo->enDipcDevId;
    pstGetServInfo->pUlMatchFunc    = pstServInputInfo->pUlMatchFunc;
    pstGetServInfo->pDlMatchFunc    = pstServInputInfo->pDlMatchFunc;
    pstGetServInfo->pUlCallFunc     = pstServInputInfo->pUlCallFunc;
    pstGetServInfo->pDlCallFunc     = pstServInputInfo->pDlCallFunc;

    DIPC_SET_SERVICE_STRU_REG(g_stTotalServiceInfo.ulServiceMask, ucServiceNo);
    g_stTotalServiceInfo.ulServiceNum ++;

    return pstGetServInfo;
}



VOS_VOID DIPC_MGR_DeregService(SERVICE_INFO_STRU *pstServiceInfo)
{
    DIPC_CLR_SERVICE_STRU_REG(g_stTotalServiceInfo.ulServiceMask, pstServiceInfo->ucServiceIndex);
    g_stTotalServiceInfo.ulServiceNum --;

    pstServiceInfo->ucServiceIndex  = 0;
    pstServiceInfo->ucRabId         = 0;
    pstServiceInfo->enDipcDevId     = DIPC_DEV_BUTT;
    pstServiceInfo->pUlMatchFunc    = VOS_NULL_PTR;
    pstServiceInfo->pDlMatchFunc    = VOS_NULL_PTR;
    pstServiceInfo->pUlCallFunc     = VOS_NULL_PTR;
    pstServiceInfo->pDlCallFunc     = VOS_NULL_PTR;

    return;
}



VOS_UINT32 DIPC_MGR_UlDataProc(DIPC_DEV_ID_ENUM_UINT32 enDeviceId, IMM_ZC_STRU *pstBuf)
{
    DEV_SERVICE_INFO_STRU              *pstDevServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceType;
    SERVICE_INFO_STRU                  *pstServInfo;

    DIPC_TraceUlData(enDeviceId, pstBuf);

    pstDevServiceInfo = &g_astDevService[enDeviceId];

    for (enServiceType = 0; enServiceType < DIPC_SERVICE_TYPE_MAX_NUM; enServiceType++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enServiceType))
        {
            pstServInfo = pstDevServiceInfo->apstServiceInfo[enServiceType];

            /* ��Ϊ����������Ҫ������������ȷ��Rab Id��������Ҫ����Match���������в���Ҫ */
            if (VOS_NULL_PTR == pstServInfo->pUlMatchFunc)
            {
                DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC, DIPC_MGR_UlDataProc, pUlMatchFunc is NULL,enServiceType <1>, enDeviceId<2>",
                    (VOS_INT32)enServiceType, (VOS_INT32)enDeviceId);
                IMM_ZcFree(pstBuf);
                return PS_FAIL;
            }

            if (PS_SUCC == pstServInfo->pUlMatchFunc(pstBuf))
            {
                if (VOS_NULL_PTR == pstServInfo->pUlCallFunc)
                {
                    DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                        "DIPC, DIPC_MGR_UlDataProc, pUlCallFunc is NULL,enServiceType <1>, enDeviceId<2>",
                        (VOS_INT32)enServiceType, (VOS_INT32)enDeviceId);
                    IMM_ZcFree(pstBuf);
                    return PS_FAIL;
                }

                if (VOS_OK != pstServInfo->pUlCallFunc(pstBuf, pstServInfo->ucRabId))
                {
                    DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                        "DIPC, DIPC_MGR_UlDataProc, call pUlFunc return fail,ulDeviceId <1>, ucRabID",
                        (VOS_INT32)enDeviceId, (VOS_INT32)pstServInfo->ucRabId);
                    IMM_ZcFree(pstBuf);
                    g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulFailSendUlPacketNums++;
                    return PS_FAIL;
                }

                /* �ɹ����գ����˳�����¼ */
                g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulSuccSendUlPacketNums++;
                return PS_SUCC;
            }
        }
    }

    /* ���豸��û���ҵ���Ӧ�ķ����ͷ����� */
    IMM_ZcFree(pstBuf);
    g_stDipcStaticInfo.astDipcDevStaticInfo[enDeviceId].ulFailMatchUlPacketNums++;
    return PS_FAIL;
}
VOS_UINT32 DIPC_MGR_IpV4Match(IMM_ZC_STRU *pstImmZcData)
{
    VOS_UINT8                          *pucIpData;
    DIPC_IPHDR_STRU                    *pstIpPkt;

    pucIpData = IMM_ZcGetDataPtr(pstImmZcData);
    pstIpPkt = (DIPC_IPHDR_STRU *)pucIpData;

    if (DIPC_IP_VER_IPV4 == pstIpPkt->ucIpVer)
    {
        return PS_SUCC;
    }

    return PS_FAIL;
}



VOS_UINT32 DIPC_MGR_IpV6Match(IMM_ZC_STRU *pstImmZcData)
{
    VOS_UINT8                          *pucIpData;
    DIPC_IPHDR_STRU                    *pstIpPkt;

    pucIpData = IMM_ZcGetDataPtr(pstImmZcData);
    pstIpPkt = (DIPC_IPHDR_STRU *)pucIpData;

    if (DIPC_IP_VER_IPV6 == pstIpPkt->ucIpVer)
    {
        return PS_SUCC;
    }

    return PS_FAIL;
}



VOS_UINT32 DIPC_MGR_AddNewIpService(VOS_UINT8 ucRabId,
    DIPC_DEV_ID_ENUM_UINT32 enDevId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType,
    DIPC_SERV_ULDATA_MATCHFUNC pServiceUlDataMatchFunc,     DIPC_SERV_DLDATA_MATCHFUNC pServiceDlDataMatchFunc)
{
    SERVICE_INFO_STRU               stServiceInfo;  /* ����׼��ע��ķ����ȫ����Ϣ�Ľṹ */
    SERVICE_INFO_STRU              *pstServiceInfo; /* ע���ķ��ط���ṹָ�� */

    stServiceInfo.ucRabId       = ucRabId;
    stServiceInfo.enDipcDevId   = enDevId;
    stServiceInfo.pUlMatchFunc  = pServiceUlDataMatchFunc;
    stServiceInfo.pDlMatchFunc  = pServiceDlDataMatchFunc;
    stServiceInfo.pUlCallFunc   = ADS_UL_SendPacket;
    stServiceInfo.pDlCallFunc   = DIPC_DEV_UsbWriteData;

    /* ע����� */
    pstServiceInfo = DIPC_MGR_RegNewService(&stServiceInfo);
    if (VOS_NULL_PTR == pstServiceInfo)
    {
        return PS_FAIL;
    }

    /* ע�������豸֮���ӳ���ϵ�������н���ʱʹ�� */
    DIPC_DEV_AddNewIpTypeService(enDevId, enDipcServiceType, pstServiceInfo);

    /* ע������Rab֮���ӳ���ϵ�������н���ʱʹ�� */
    DIPC_MGR_AddNewIpTypeService(ucRabId, enDipcServiceType, pstServiceInfo);

    return PS_SUCC;
}
VOS_UINT32 DIPC_MGR_DelIpVService(VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    SERVICE_INFO_STRU             *pstServiceInfo;

    /* ���ҵ���RabId�ķ��� */
    pstServiceInfo = DIPC_MGR_GetServiceByRabId(ucRabId, enDipcServiceType);
    if (VOS_NULL_PTR == pstServiceInfo)
    {
        return PS_FAIL;
    }

    /* ɾ��Rab�ͷ���֮���ӳ���ϵ�������н���ʱʹ�� */
    DIPC_MGR_DelIpTypeService(pstServiceInfo->ucRabId, enDipcServiceType);

    /* ȥע�������豸֮���ӳ���ϵ�������н���ʱʹ�� */
    DIPC_DEV_DelIpTypeService(pstServiceInfo->enDipcDevId, enDipcServiceType);

    /* ȥע����� */
    DIPC_MGR_DeregService(pstServiceInfo);

    return PS_SUCC;
}



VOS_UINT32 DIPC_MGR_AddNewService(DIPC_DEV_ID_ENUM_UINT32 enDevId,
    VOS_UINT8 ucRabId, DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    VOS_UINT32              ulRsult;

    switch (enDipcServiceType)
    {
        case DIPC_SERVICE_TYPE_IPV4:
            ulRsult = DIPC_MGR_AddNewIpService(ucRabId, enDevId,
                DIPC_SERVICE_TYPE_IPV4, DIPC_MGR_IpV4Match, DIPC_MGR_IpV4Match);
            break;

        case DIPC_SERVICE_TYPE_IPV6:
            ulRsult = DIPC_MGR_AddNewIpService(ucRabId, enDevId,
                DIPC_SERVICE_TYPE_IPV6, DIPC_MGR_IpV6Match, DIPC_MGR_IpV6Match);
            break;

        default:
            /* ��NASȷ��DIPC_BEARER_TYPE_IPV4V6���͵���ϢNAS���Ϊһ��IPV4��һ��IPV6���͹��� */
            ulRsult = PS_FAIL;
            break;
    }

    return ulRsult;
}
VOS_UINT32 DIPC_MGR_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData)
{
    RAB_SERVICE_INFO_STRU              *pstRabServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceType;
    SERVICE_INFO_STRU                  *pstServInfo;

    DIPC_TraceDlData(ucRabId, pData);

    pstRabServiceInfo = &g_astRabService[ucRabId];

    for (enServiceType = 0; enServiceType < DIPC_SERVICE_TYPE_MAX_NUM; enServiceType++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enServiceType))
        {
            pstServInfo = pstRabServiceInfo->apstServiceInfo[enServiceType];

            if (PS_SUCC == pstServInfo->pDlMatchFunc(pData))
            {
                if (VOS_OK != pstServInfo->pDlCallFunc(pstServInfo->enDipcDevId, pData))
                {
                    DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                        "DIPC, DIPC_MGR_DlAdsDataRcv, call pDlFunc return fail,ulDeviceId <1>, ucRabID",
                        (VOS_INT32)pstServInfo->enDipcDevId, (VOS_INT32)pstServInfo->ucRabId);
                    IMM_ZcFree(pData);
                    g_stDipcStaticInfo.astDipcDevStaticInfo[pstServInfo->enDipcDevId].ulFailSendDlPacketNums++;
                    return PS_FAIL;
                }

                /* �ɹ����գ����˳�����¼ */
                g_stDipcStaticInfo.astDipcDevStaticInfo[pstServInfo->enDipcDevId].ulSuccSendDlPacketNums++;
                return PS_SUCC;
            }
        }
    }

    /* ���豸��û���ҵ���Ӧ�ķ����ͷ����� */
    g_stDipcStaticInfo.ulFailMatchDlPacketNums++;
    IMM_ZcFree(pData);
    return PS_FAIL;
}



SERVICE_INFO_STRU* DIPC_MGR_GetServiceByRabId(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    RAB_SERVICE_INFO_STRU          *pstRabServiceInfo;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    /* �����Ӧ�ķ�������û��ע�ᣬ�򱨴� */
    if (PS_TRUE != DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_GetServiceByRabId, no service.\n");
        return VOS_NULL_PTR;
    }

    /* �������˵������ע���˵���û�ж�Ӧ�ķ���ṹ��˵���ڲ�ά������ */
    if (VOS_NULL_PTR == pstRabServiceInfo->apstServiceInfo[enDipcServiceType])
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_MGR_GetServiceByRabId, no service but with mask.\n");
        return VOS_NULL_PTR;
    }

    return pstRabServiceInfo->apstServiceInfo[enDipcServiceType];
}


VOS_VOID DIPC_MGR_AddNewIpTypeService(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType, SERVICE_INFO_STRU *pstServiceInfo)
{
    RAB_SERVICE_INFO_STRU          *pstRabServiceInfo;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    pstRabServiceInfo->apstServiceInfo[enDipcServiceType] = pstServiceInfo;
    DIPC_SET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType);

    pstRabServiceInfo->ulServiceCnt++;

    return;
}


VOS_VOID DIPC_MGR_DelIpTypeService(VOS_UINT8 ucRabId,
    DIPC_SERVICE_TYPE_ENUM_UINT32 enDipcServiceType)
{
    RAB_SERVICE_INFO_STRU          *pstRabServiceInfo;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    pstRabServiceInfo->apstServiceInfo[enDipcServiceType] = VOS_NULL_PTR;
    DIPC_CLR_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType);

    pstRabServiceInfo->ulServiceCnt--;

    return;
}


DIPC_DEV_ID_ENUM_UINT32 DIPC_GetDevIdByRabId(VOS_UINT8 ucRabId)
{
    RAB_SERVICE_INFO_STRU              *pstRabServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceNum;
    SERVICE_INFO_STRU                  *pstServInfo = VOS_NULL_PTR;

    pstRabServiceInfo = &g_astRabService[ucRabId];

    for (enServiceNum = 0; enServiceNum < DIPC_SERVICE_TYPE_MAX_NUM; enServiceNum++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enServiceNum))
        {
            pstServInfo = pstRabServiceInfo->apstServiceInfo[enServiceNum];
            break;
        }
    }

    if (VOS_NULL_PTR != pstServInfo)
    {
        return (pstServInfo->enDipcDevId);
    }

    return  DIPC_DEV_BUTT;
}



UDI_HANDLE DIPC_GetDevHandleByRabId(VOS_UINT8 ucRabId)
{
    DIPC_DEV_ID_ENUM_UINT32             enDipcDevId;

    if ((ucRabId < MIN_RAB_ID) || (ucRabId > MAX_RAB_ID))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_GetDevHandleByRabId, ucRabId <1> exceed the range.\n", ucRabId);
        return UDI_INVAL_DEV_ID;
    }

    enDipcDevId  = DIPC_GetDevIdByRabId(ucRabId);

    if (DIPC_DEV_BUTT == enDipcDevId)
    {
        return UDI_INVAL_DEV_ID;
    }

    return g_astDevInfo[enDipcDevId].slUdiHsicHdl;
}


VOS_UINT32 DIPC_CheckRelation(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg)
{
    RAB_SERVICE_INFO_STRU              *pstRabServiceInfo;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enServiceNum;
    SERVICE_INFO_STRU                  *pstServInfo = VOS_NULL_PTR;
    UDI_DEVICE_ID_E                       enUdiDevId;
    DIPC_SERVICE_TYPE_ENUM_UINT32       enDipcServiceType;
    DEV_SERVICE_INFO_STRU              *pstDevServiceInfo;

    enDipcServiceType = DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpActMsg->enBearerType);
    pstRabServiceInfo = &g_astRabService[pstAtDipcPdpActMsg->ucRabId];

    /* ֮ǰû��ע�ᣬ��ΪΪ��ȷ��� */
    if (0 == pstRabServiceInfo->ulServiceCnt)
    {
        return VOS_OK;
    }

    /*  ���ServiceCntΪ0������ServiceMask��Ϊ0������Ϊ�ڲ��쳣�������������Ϣ */
    if (0 == pstRabServiceInfo->ulServiceMask)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, Rab <1> Service is wrong.", pstAtDipcPdpActMsg->ucRabId);
        return VOS_ERR;
    }

    /* �����Rab���Ѿ��ж�Ӧ���͵ķ�����ΪΪ���� */
    if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enDipcServiceType))
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, Rab <1> type<2> is already reg.",
            pstAtDipcPdpActMsg->ucRabId, pstAtDipcPdpActMsg->enBearerType);
        return VOS_ERR;
    }


    for (enServiceNum = 0; enServiceNum < DIPC_SERVICE_TYPE_MAX_NUM; enServiceNum++)
    {
        if (PS_TRUE == DIPC_GET_SERVICE_REG(pstRabServiceInfo->ulServiceMask, enServiceNum))
        {
            pstServInfo = pstRabServiceInfo->apstServiceInfo[enServiceNum];
            break;
        }
    }

    /* ���pstRabServiceInfo->ulServiceCnt��Ϊ0�������ϲ������pstServInfoΪ�յ������
    �˴���Ϊ������PC LINT�澯 */
    if (VOS_NULL_PTR == pstServInfo)
    {
        return VOS_ERR;
    }

    /* �����Rab���Ѿ����������͵ķ�����Ϊ��Ӧ���豸IdҪ���µ���Ϣ�е�һ�� */
    enUdiDevId = g_astDevInfo[pstServInfo->enDipcDevId].enUdiDevId;
    if (pstAtDipcPdpActMsg->enUdiDevId != enUdiDevId)
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, pstAtDipcPdpActMsg->enUdiDevId <1> not with enUdiDevId <2>.",
            pstAtDipcPdpActMsg->enUdiDevId, enUdiDevId);
        return VOS_ERR;
    }

    /* ������豸���Ѿ��ж�Ӧ���͵ķ�����ΪΪ���� */
    pstDevServiceInfo = &(g_astDevService[pstServInfo->enDipcDevId]);
    if (PS_TRUE == DIPC_GET_SERVICE_REG(pstDevServiceInfo->ulServiceMask, enDipcServiceType))
    {
        DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckRelation, Dev <1> type<2> is already reg.",
            pstAtDipcPdpActMsg->enUdiDevId, pstAtDipcPdpActMsg->enBearerType);
        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 DIPC_CheckPdpActPara(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg)
{
    if ((pstAtDipcPdpActMsg->ucRabId < MIN_RAB_ID) || (pstAtDipcPdpActMsg->ucRabId > MAX_RAB_ID))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpActPara, Rab Id exceed the range!\n",
            pstAtDipcPdpActMsg->ucRabId);
        return VOS_ERR;
    }

    /* ��NASЭ�����һ��RabId�ϼ���IPV4����IPV6����Ҫ��2���·���DIPC_BEARER_TYPE_IPV4V6�����Ǹ�NAS�ڲ�ʹ�� */
    if (DIPC_BEARER_TYPE_IPV4V6 <= pstAtDipcPdpActMsg->enBearerType)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpActPara, pstAtDipcPdpActMsg->enBearerType <1> exceed the ranger.",
            pstAtDipcPdpActMsg->enBearerType);
        return VOS_ERR;
    }

    if (VOS_OK != DIPC_DEV_CheckUdiDevIdPara(pstAtDipcPdpActMsg->enUdiDevId))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpActPara, pstAtDipcPdpActMsg->enUdiDevId <1> exceed the ranger.",
            pstAtDipcPdpActMsg->enUdiDevId);
        return VOS_ERR;
    }

    if (VOS_OK != DIPC_CheckRelation(pstAtDipcPdpActMsg))
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID DIPC_RcvAtPdpActIndProc(AT_DIPC_PDP_ACT_STRU *pstAtDipcPdpActMsg)
{
    VOS_UINT32                          ulRslt;
    DIPC_DEV_ID_ENUM_UINT32             enDevId;

    if (VOS_OK != DIPC_CheckPdpActPara(pstAtDipcPdpActMsg))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_RcvAtPdpActIndProc, receive error message.\n");
        return;
    }

    /* ͨ��NASʹ�õ��ⲿ�豸ID��ȡ�ڲ��豸ID */
    enDevId = DIPC_DEV_GetDevIdByUdiId(pstAtDipcPdpActMsg->enUdiDevId);
    if (DIPC_DEV_BUTT <= enDevId)    /* �����Ӧ���豸ID������ */
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_RcvAtPdpActIndProc, can not find the device.\n");
        return;
    }

    /* ��DIPC�ڲ�ע��һ���µķ��� */
    ulRslt = DIPC_MGR_AddNewService(enDevId, pstAtDipcPdpActMsg->ucRabId,
        DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpActMsg->enBearerType));

    if (PS_SUCC != ulRslt)
    {
        DIPC_MappingInfoTrace(ID_DIPC_ADD_NEW_MAPPING_INFO_FAIL);
        return;
    }

    if (VOS_OK != (ADS_DL_RegDlDataCallback(pstAtDipcPdpActMsg->ucRabId, DIPC_DlAdsDataRcv)))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_RcvAtPdpActIndProc, call ADS_DL_RegDlDataCallback fail!\n");
        DIPC_MappingInfoTrace(ID_DIPC_REG_ADS_DL_DATA_CALLBACK_FAIL);
        return;
    }

    DIPC_MappingInfoTrace(ID_DIPC_PDP_ACT_SUCC);

    return;
}
VOS_UINT32 DIPC_CheckPdpRelPara(AT_DIPC_PDP_DEACT_STRU *pstAtDipcPdpDeactMsg)
{
    if ((pstAtDipcPdpDeactMsg->ucRabId < MIN_RAB_ID) || (pstAtDipcPdpDeactMsg->ucRabId > MAX_RAB_ID))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpRelPara, Rab Id exceed the range!\n"
            , pstAtDipcPdpDeactMsg->ucRabId);
        return VOS_ERR;
    }

    if (DIPC_BEARER_TYPE_IPV4V6 <= pstAtDipcPdpDeactMsg->enBearerType)
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpRelPara, pstAtDipcPdpDeactMsg->enBearerType <1> exceed the ranger.",
            pstAtDipcPdpDeactMsg->enBearerType);
        return VOS_ERR;
    }

    /* �����Ӧ��Rab Idû��ע����� */
    if (VOS_NULL_PTR == DIPC_MGR_GetServiceByRabId(pstAtDipcPdpDeactMsg->ucRabId,
        DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpDeactMsg->enBearerType)))
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_CheckPdpRelPara, Rab Id <1> not exist!\n"
            , pstAtDipcPdpDeactMsg->ucRabId);
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID DIPC_RcvAtPdpRelIndProc(AT_DIPC_PDP_DEACT_STRU *pstAtDipcPdpDeactMsg)
{
    VOS_UINT32              ulRslt;

    if (VOS_OK != DIPC_CheckPdpRelPara(pstAtDipcPdpDeactMsg))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_RcvAtPdpRelIndProc, receive error message.\n");
        return;
    }

    ulRslt = DIPC_MGR_DelIpVService(pstAtDipcPdpDeactMsg->ucRabId, DIPC_GET_SERVICE_TYPE_BY_BEARER_TYPE(pstAtDipcPdpDeactMsg->enBearerType));

    if (PS_SUCC != ulRslt)
    {
        DIPC_MappingInfoTrace(ID_DIPC_DEL_MAPPING_INFO_FAIL);
        return;
    }

    if (VOS_OK != (ADS_DL_RegDlDataCallback(pstAtDipcPdpDeactMsg->ucRabId, VOS_NULL_PTR)))
    {
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC_RcvAtPdpRelIndProc, call ADS_DL_RegDlDataCallback fail!\n");
        DIPC_MappingInfoTrace(ID_DIPC_DEREG_ADS_DL_DATA_CALLBACK_FAIL);
        return;
    }

    DIPC_MappingInfoTrace(ID_DIPC_PDP_DEACT_SUCC);

    return;
}



VOS_UINT32 DIPC_DlAdsDataRcv(VOS_UINT8 ucRabId, IMM_ZC_STRU *pData,
    ADS_PKT_TYPE_ENUM_UINT8 enPktType)
{
    VOS_UINT16  usApp;      /* ʹ��skb_buff�ṹ�������ֶδ��������кͲ�����Ϣ */

    if (VOS_NULL_PTR == pData)
    {
        g_stDipcStaticInfo.ulNullDlPacketNums++;
        DIPC_PrintLog(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_DlAdsDataRcv, pData is null.\n");
        return PS_FAIL;
    }

    g_stDipcStaticInfo.ulSuccGetDlPacketNums++;

    usApp = DIPC_SET_APP(ID_DIPC_DL_DATA, ucRabId);

    IMM_ZcSetUserApp(pData, usApp);

    return DIPC_EnqueueData(pData);
}
VOS_VOID  DIPC_ProcDataNotify(VOS_VOID)
{
    IMM_ZC_STRU                *pstMem;
    VOS_INT32                   lLockKey;
    VOS_UINT16                  usApp;
    VOS_UINT8                   ucDir;

    lLockKey = VOS_SplIMP();
    g_stDipcDataQ.ulNotifyMsgCnt--;
    VOS_Splx(lLockKey);

    for (;;)
    {
        pstMem  = (IMM_ZC_STRU *)IMM_ZcDequeueHead(&g_stDipcDataQ.stDipcDataQ);

        /* ����Ϊ�յ�ʱ�򷵻ؿ�ָ�� */
        if ( VOS_NULL_PTR == pstMem )
        {
            return;
        }

        /*����ý��(�����ͷŶ����Ѿ��ڸ��������ڲ���ɣ��������ͷŽ��)*/

        usApp = IMM_ZcGetUserApp(pstMem);

        ucDir = (VOS_UINT8)DIPC_GET_DIR(usApp);

        switch ( ucDir )
        {
            case ID_DIPC_UL_DATA:
                DIPC_MGR_UlDataProc(DIPC_GET_PARA(usApp),pstMem);
                break;

            case ID_DIPC_DL_DATA:
                DIPC_MGR_DlAdsDataRcv(DIPC_GET_PARA(usApp),pstMem);
                break;

            default:
                IMM_ZcFree(pstMem);
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC_ProcDataNotify, WARNING, ucDir %d is Abnormal!", ucDir);
                break;
        }
    } /* for (;;) */
} /* DIPC_ProcDataNotify */



VOS_UINT32 DIPC_AtMsgProc( const MsgBlock *pMsgBlock )
{
    TTF_U32MSG_COMM_HEAD_STRU  *pstHsicCtrlMsg    = (TTF_U32MSG_COMM_HEAD_STRU *)pMsgBlock;

    if (WUEPS_PID_AT == pstHsicCtrlMsg->ulSenderPid)
    {
        switch (pstHsicCtrlMsg->ulMsgType)
        {
            case ID_AT_DIPC_PDP_ACT_IND:
                DIPC_RcvAtPdpActIndProc((AT_DIPC_PDP_ACT_STRU *)pMsgBlock);
                break;

            case ID_AT_DIPC_PDP_REL_IND:
                DIPC_RcvAtPdpRelIndProc((AT_DIPC_PDP_DEACT_STRU *)pMsgBlock);
                break;

            default:
                DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                    "DIPC, DIPC_AtMsgProc, received msg ulMsgType <1>",
                    (VOS_INT32)pstHsicCtrlMsg->ulMsgType);
                return VOS_ERR;
        }
    }
    else if (PS_PID_APP_DIPC == pstHsicCtrlMsg->ulSenderPid)
    {
        if (ID_DIPC_DATA_NOTIFY_REQ == pstHsicCtrlMsg->ulMsgType)
        {
            DIPC_ProcDataNotify();
        }
        else
        {
            DIPC_PrintLog2(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
                "DIPC, DIPC_AtMsgProc, received msg ulSenderPid<1> , ulMsgType <2>",
                (VOS_INT32)pstHsicCtrlMsg->ulSenderPid,
                (VOS_INT32)pstHsicCtrlMsg->ulMsgType);
            return VOS_ERR;
        }
    }
    else
    {
        DIPC_PrintLog1(PS_PID_APP_DIPC, 0, PS_PRINT_WARNING,
            "DIPC, DIPC_AtMsgProc, received msg ulSenderPid<1> ",
            (VOS_INT32)pstHsicCtrlMsg->ulSenderPid);
        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_VOID DIPC_DataQInit(VOS_VOID)
{
    IMM_ZC_HEAD_STRU                    *pstDataQ;


    pstDataQ    = &(g_stDipcDataQ.stDipcDataQ);

    VOS_MemSet(&g_stDipcDataQ, 0, sizeof(g_stDipcDataQ));

    IMM_ZcQueueHeadInit(pstDataQ);

    return;
}


VOS_UINT32 DIPC_Init( VOS_VOID )
{
    VOS_UINT8                       ucRabId;
    VOS_UINT32                      ulServiceId;
    SERVICE_INFO_STRU              *pstServiceInfo;
    DIPC_DEV_ID_ENUM_UINT32         enDevId;
    DIPC_SERVICE_TYPE_ENUM_UINT32   enServiceType;

    /* ��ʼ��Rab�������ӳ��� */
    for (ucRabId = 0; ucRabId < RAB_MAX_NUM; ucRabId++)
    {
        for (enServiceType = DIPC_SERVICE_TYPE_IPV4; enServiceType < DIPC_SERVICE_TYPE_BUTT; enServiceType++)
        {
            g_astRabService[ucRabId].apstServiceInfo[enServiceType] = VOS_NULL_PTR;
        }
        g_astRabService[ucRabId].ulServiceCnt   = 0;
        g_astRabService[ucRabId].ulServiceMask  = 0;
    }

    /* ��ʼ��������Ϣ��*/
    for (ulServiceId = 0; ulServiceId < SERVICE_MAX_NUM; ulServiceId++)
    {
        pstServiceInfo = &g_stTotalServiceInfo.astServiceInfo[ulServiceId];
        pstServiceInfo->enDipcDevId     = DIPC_DEV_BUTT;
        pstServiceInfo->ucRabId         = 0;
        pstServiceInfo->pDlCallFunc     = VOS_NULL_PTR;
        pstServiceInfo->pUlCallFunc     = VOS_NULL_PTR;
        pstServiceInfo->pUlMatchFunc    = VOS_NULL_PTR;
    }
    g_stTotalServiceInfo.ulServiceNum   = 0;
    g_stTotalServiceInfo.ulServiceMask  = 0;

    /* ��ʼ���豸�������ӳ��� */
    for (enDevId = DIPC_DEV_ID1; enDevId < DIPC_DEV_BUTT; enDevId++)
    {
        for (enServiceType = DIPC_SERVICE_TYPE_IPV4; enServiceType < DIPC_SERVICE_TYPE_BUTT; enServiceType++)
        {
            g_astDevService[enDevId].apstServiceInfo[enServiceType] = VOS_NULL_PTR;
        }
        g_astDevService[enDevId].ulServiceCnt   = 0;
        g_astDevService[enDevId].ulServiceMask  = 0;
    }

    /* ���HSICͨ���Ѿ�ö�ٳɹ�������Э��ջִ�г�ʼ�����������򽫳�ʼ������ע��������
        �ɵ�����HSICö�ٳɹ�������Խ��г�ʼ��*/
    if (VOS_TRUE == DRV_GET_HSIC_ENUM_STATUS())
    {
        DIPC_DEV_PortInit();
    }
    else
    {
        DRV_HSIC_REGUDI_ENABLECB((HSIC_UDI_ENABLE_CB_T)DIPC_DEV_PortInit);
    }

    DIPC_StaticInfoInit();

    DIPC_DataQInit();

    return VOS_OK;
}



VOS_UINT32 DIPC_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip )
{
    switch( ip )
    {
        case VOS_IP_LOAD_CONFIG:
            DIPC_Init();
            break;
        case VOS_IP_FARMALLOC:
        case VOS_IP_INITIAL:
        case VOS_IP_ENROLLMENT:
        case VOS_IP_LOAD_DATA:
        case VOS_IP_FETCH_DATA:
        case VOS_IP_STARTUP:
        case VOS_IP_RIVAL:
        case VOS_IP_KICKOFF:
        case VOS_IP_STANDBY:
        case VOS_IP_BROADCAST_STATE:
        case VOS_IP_RESTART:
            break;
        default:
            break;
    }

    return PS_SUCC;
}



VOS_VOID DIPC_TraceUlData(DIPC_DEV_ID_ENUM_UINT32 ulDeviceId, IMM_ZC_STRU *pstData)
{
    TRACE_UL_DIPC_DATA_MSG             *pstTraceUlData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucData;
    IMM_ZC_STRU                        *pstDataNode;


    if (PS_TRUE != g_ulDipcTraceFlag)
    {
        return;
    }

    pstDataNode = pstData;

    while(VOS_NULL_PTR != pstDataNode)
    {
        pstTraceUlData  = g_pstDipcTraceUlData;
        pstTraceUlData->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstTraceUlData->ulSenderPid     = PS_PID_APP_DIPC;
        pstTraceUlData->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstTraceUlData->ulReceiverPid   = PS_PID_APP_DIPC;
        pstTraceUlData->enMsgType       = ID_DIPC_TRACE_UL_DATA;
        pstTraceUlData->enDevId         = ulDeviceId;

        ulDataLen   = IMM_ZcGetUsedLen(pstDataNode);
        pucData     = IMM_ZcGetDataPtr(pstDataNode);
        pstTraceUlData->ulDataLen       = ulDataLen;
        pstTraceUlData->ulLength        = (((sizeof(TRACE_UL_DIPC_DATA_MSG) - VOS_MSG_HEAD_LENGTH) - DIPC_DATA_MAX_DATA_LEN) + ulDataLen);
        mdrv_memcpy(pstTraceUlData->aucData, pucData, ulDataLen);
        DIAG_TraceReport(pstTraceUlData);

        pstDataNode = pstDataNode->next;
    }

    return;
}



VOS_VOID DIPC_TraceDlData(VOS_UINT8 ucRabId, IMM_ZC_STRU *pstData)
{
    TRACE_DL_DIPC_DATA_MSG             *pstTraceDlData;
    VOS_UINT32                          ulDataLen;
    VOS_UINT8                          *pucData;


    if (PS_TRUE != g_ulDipcTraceFlag)
    {
        return;
    }

    while(VOS_NULL_PTR != pstData)
    {
        pstTraceDlData  = g_pstDipcTraceDlData;
        pstTraceDlData->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstTraceDlData->ulSenderPid     = PS_PID_APP_DIPC;
        pstTraceDlData->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstTraceDlData->ulReceiverPid   = PS_PID_APP_DIPC;
        pstTraceDlData->enMsgType       = ID_DIPC_TRACE_DL_DATA;
        pstTraceDlData->ucRabId         = ucRabId;

        ulDataLen   = IMM_ZcGetUsedLen(pstData);
        pucData     = IMM_ZcGetDataPtr(pstData);
        pstTraceDlData->ulDataLen       = ulDataLen;
        pstTraceDlData->ulLength        = (((sizeof(TRACE_DL_DIPC_DATA_MSG) - VOS_MSG_HEAD_LENGTH) - DIPC_DATA_MAX_DATA_LEN) + ulDataLen);
        mdrv_memcpy(pstTraceDlData->aucData, pucData, ulDataLen);
        DIAG_TraceReport(pstTraceDlData);

        pstData = pstData->next;
    }

    return;
}



VOS_VOID DIPC_MappingInfoTrace(DIPC_TRACE_MSG_TYPE_ENUM_UINT32 enDipcTraceMsgType)
{
    DIPC_DEV_SUITE_INFO_MSG                 stDevTotalInfo;
    DIPC_DEV_INFO_STRU                     *pstDipcDevSingleInfo;
    DIPC_DEV_ID_ENUM_UINT32                 enDeviceId;
    DIPC_SERVICE_TYPE_ENUM_UINT32           enDipcServiceType;
    SERVICE_INFO_STRU                      *pstServInfo;

    stDevTotalInfo.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stDevTotalInfo.ulSenderPid      = PS_PID_APP_DIPC;
    stDevTotalInfo.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stDevTotalInfo.ulReceiverPid    = PS_PID_APP_DIPC;
    stDevTotalInfo.ulLength         = sizeof(DIPC_DEV_SUITE_INFO_MSG) - VOS_MSG_HEAD_LENGTH;
    stDevTotalInfo.enMsgType        = enDipcTraceMsgType;

    for (enDeviceId = DIPC_DEV_ID1; enDeviceId < DIPC_DEV_BUTT; enDeviceId++)
    {
        pstDipcDevSingleInfo  = &(stDevTotalInfo.astDipcDevData[enDeviceId]);

        for (enDipcServiceType = DIPC_SERVICE_TYPE_IPV4;
            enDipcServiceType < DIPC_SERVICE_TYPE_BUTT;
            enDipcServiceType++)
        {
            pstDipcDevSingleInfo->enServiceType = enDipcServiceType;

            pstServInfo = g_astDevService[enDeviceId].apstServiceInfo[enDipcServiceType];
            if (VOS_NULL_PTR == pstServInfo)
            {
                pstDipcDevSingleInfo->ucRabId       = INVALID_RABID_VALUE;
            }
            else
            {
                pstDipcDevSingleInfo->ucRabId       = pstDipcDevSingleInfo->ucRabId;
            }
        }
    }

    DIAG_TraceReport(&stDevTotalInfo);

    return;
}



VOS_VOID DIPC_StaticInfoInit( VOS_VOID )
{
    PS_MEM_SET(&g_stDipcStaticInfo, 0, sizeof(DIPC_STATIC_INFO_STRU));

    g_pstDipcTraceUlData = PS_ALLOC_STATIC_MEM(PS_PID_APP_DIPC, sizeof(TRACE_UL_DIPC_DATA_MSG));
    g_pstDipcTraceDlData = PS_ALLOC_STATIC_MEM(PS_PID_APP_DIPC, sizeof(TRACE_DL_DIPC_DATA_MSG));

    return;
}



VOS_VOID DIPC_ShowStat( VOS_VOID )
{
    DIPC_DEV_ID_ENUM_UINT32         enDipcDevId;


    DIPC_MappingInfoTrace(ID_DIPC_SHOW_MAPPING_INFO);

    vos_printf("===========DIPC_ShowStat============");

    vos_printf("DIPC Rab Info.\r\n");
    vos_printf("DIPC Get Null Data From ADS, Num = %d.\r\n", g_stDipcStaticInfo.ulNullDlPacketNums);
    vos_printf("DIPC Dl Succ Get PacketNum = %d.\r\n", g_stDipcStaticInfo.ulSuccGetDlPacketNums);
    vos_printf("DIPC Dl FailMatch PacketNum = %d.\r\n", g_stDipcStaticInfo.ulFailMatchDlPacketNums);
    vos_printf("DIPC Dev Static Info.\r\n");

    for(enDipcDevId = 0; enDipcDevId < DIPC_DEV_NUM; enDipcDevId++)
    {
        vos_printf("DIPC Ul Get Fail Nums = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulGetDataFailNums);
        vos_printf("DIPC Ul Succ Get PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulSuccGetUlPacketNums);
        vos_printf("DIPC Ul FailSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulFailSendUlPacketNums);
        vos_printf("DIPC Ul SuccSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulSuccSendUlPacketNums);
        vos_printf("DIPC Ul FailMatch PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulFailMatchUlPacketNums);
        vos_printf("DIPC Dl FailSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulFailSendDlPacketNums);
        vos_printf("DIPC Dl SuccSend PacketNum = %u\r\n",
            g_stDipcStaticInfo.astDipcDevStaticInfo[enDipcDevId].ulSuccSendDlPacketNums);
        vos_printf("\r\n");
    }

    return;
}



VOS_VOID DIPC_ShowMappingInfo( VOS_VOID )
{
    DIPC_DEV_ID_ENUM_UINT32                 enDeviceId;
    DIPC_SERVICE_TYPE_ENUM_UINT32           enDipcServiceType;
    SERVICE_INFO_STRU                      *pstServInfo;

    for (enDeviceId = DIPC_DEV_ID1; enDeviceId < DIPC_DEV_BUTT; enDeviceId++)
    {
        vos_printf("enDeviceId = %d,begin\r\n", enDeviceId);

        for (enDipcServiceType = DIPC_SERVICE_TYPE_IPV4;
            enDipcServiceType < DIPC_SERVICE_TYPE_BUTT;
            enDipcServiceType++)
        {
            pstServInfo = g_astDevService[enDeviceId].apstServiceInfo[enDipcServiceType];
            if (VOS_NULL_PTR != pstServInfo)
            {
                vos_printf("Service Type %d, Rab Id %d\n",
                    enDipcServiceType, pstServInfo->ucRabId);
            }
        }
        vos_printf("enDeviceId = %d,end\r\n", enDeviceId);
    }

    return;
}



VOS_VOID DIPC_SetTraceFlag( VOS_UINT32  ulFlag )
{
    g_ulDipcTraceFlag   = ulFlag;

    return;
}



VOS_VOID DIPC_SetLogFlag( VOS_UINT32  ulFlag )
{
    g_ulDipcPrintFlag   = ulFlag;

    return;
}


#else   /* for feature */

/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "PsTypeDef.h"
#include "mdrv.h"

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/

UDI_HANDLE DIPC_GetDevHandleByRabId(VOS_UINT8 ucRabId)
{
    return UDI_INVAL_DEV_ID;
}


VOS_UINT32 DIPC_Pid_InitFunc( enum VOS_INIT_PHASE_DEFINE ip )
{
    return PS_SUCC;
}


VOS_UINT32 DIPC_AtMsgProc( const MsgBlock *pMsgBlock )
{
    return VOS_OK;
}


#endif    /* end for feature */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


