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
  1 ͷ�ļ�����
*****************************************************************************/
#include "AdsUpLink.h"
#include "AdsDebug.h"
#include "IpsMntn.h"

#include "AcpuReset.h"

#include "NasNvInterface.h"
#include "TafNvInterface.h"

#include "AdsFilter.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_UPLINK_C
/*lint +e767*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_VOID ADS_UL_StartDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* ������ж��д���, ����������ͳ�ƶ�ʱ�� */
    if (VOS_OK == ADS_UL_IsQueueExistent(ucInstance, ucRabId))
    {
        ADS_StartTimer(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS, TI_ADS_DSFLOW_STATS_LEN);
    }

    return;
}
VOS_VOID ADS_UL_StopDsFlowStats(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* ����������ж����Ѳ����ڣ���ֹͣ����ͳ�ƶ�ʱ�����������ͳ����Ϣ */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist(ucInstance))
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_DSFLOW_STATS, ADS_TIMER_STOP_CAUSE_USER);
        ADS_InitStatsInfoCtx(ucInstance);
    }

    return;
}
VOS_VOID ADS_UL_StartRptStatsInfoTimer(
    VOS_UINT8                           ucInstance,
    VOS_UINT8                           ucRabId
)
{
    /* ������ж��д���, �������ϱ�ͳ����Ϣ��ʱ�� */
    if (VOS_OK == ADS_UL_IsQueueExistent(ucInstance, ucRabId))
    {
        ADS_StartTimer(ACPU_PID_ADS_UL,
                       TI_ADS_RPT_STATS_INFO,
                       TI_ADS_RPT_STATS_LEN);
    }

    return;
}
VOS_VOID ADS_UL_StopRptStatsInfoTimer(VOS_VOID)
{
    VOS_UINT8                           ucInsIndex;

    for (ucInsIndex = 0; ucInsIndex < ADS_INSTANCE_MAX_NUM; ucInsIndex++)
    {
        if (VOS_FALSE == ADS_UL_IsAnyQueueExist(ucInsIndex))
        {
            ADS_StopTimer(ACPU_PID_ADS_UL, TI_ADS_RPT_STATS_INFO, ADS_TIMER_STOP_CAUSE_USER);
        }
    }
}


VOS_UINT32 ADS_UL_SendPacket(
    IMM_ZC_STRU                        *pstData,
    VOS_UINT8                           ucRabId
)
{
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* �ж��Ƿ�Ϊ�����ݰ� */
    if (VOS_NULL_PTR == pstData)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacket: pstData is null!");
        return VOS_ERR;
    }

    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* �������н�������ͳ�Ƹ��� */
    ADS_DBG_RECV_UL_PKT_NUM(ucInstanceIndex, 1);

    /* ����ͳ�� */
    ADS_ULFlowAdd(ucInstanceIndex, pstData->len);

    /* ׷�����н������� */
    ADS_MNTN_TraceRcvUlData();

    /* ͳ�������������յ��������ֽ���������������ѯ */
    ADS_RECV_UL_PERIOD_PKT_NUM(ucInstanceIndex, pstData->len);

    /* ��pstData���뵽ucRabId��Ӧ�Ļ�������� */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstanceIndex, pstData, ucRealRabId))
    {
        ADS_DBG_UL_ENQUE_FAIL_NUM(ucInstanceIndex, 1);
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_SendPacket: insert fail, rab id !", ucRealRabId);
        return VOS_ERR;
    }


    return VOS_OK;
}


VOS_UINT32 ADS_UL_SendPacketEx(
    IMM_ZC_STRU                        *pstData,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType,
    VOS_UINT8                           ucRabId
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* �ж��Ƿ�Ϊ�����ݰ� */
    if (VOS_NULL_PTR == pstData)
    {
        ADS_WARNING_LOG(ACPU_PID_ADS_UL, "ADS_UL_SendPacketEx: pstData is null!");
        return VOS_ERR;
    }

    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* �ж��Ƿ��Ѿ�ע������й��˻ص���������ע���������Ҫ���й�����Ϣ����ȡ������ֱ�ӷ��ͱ��� */
    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);
    if (VOS_NULL_PTR != pstDlRabInfo->pRcvDlFilterDataFunc)
    {
        /* ���ù����������ݰ������� */
        ADS_FILTER_ProcUlPacket(pstData, enIpType);
    }

    /* �������н�������ͳ�Ƹ��� */
    ADS_DBG_RECV_UL_PKT_NUM(ucInstanceIndex, 1);

    /* ����ͳ�� */
    ADS_ULFlowAdd(ucInstanceIndex, pstData->len);

    /* ׷�����н������� */
    ADS_MNTN_TraceRcvUlData();

    /* ͳ�������������յ��������ֽ���������������ѯ */
    ADS_RECV_UL_PERIOD_PKT_NUM(ucInstanceIndex, pstData->len);

    /* ��pstData���뵽ucRabId��Ӧ�Ļ�������� */
    if (VOS_OK != ADS_UL_InsertQueue(ucInstanceIndex, pstData, ucRealRabId))
    {
        ADS_DBG_UL_ENQUE_FAIL_NUM(ucInstanceIndex, 1);
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_SendPacketEx: insert fail, rab id !", ucRealRabId);
        return VOS_ERR;
    }

    return VOS_OK;

}


IMM_ZC_STRU* ADS_UL_GetInstanceNextQueueNode(
    VOS_UINT8                           ucInstanceIndex,
    VOS_UINT8                          *pucRabId
)
{
    VOS_UINT32                          i;
    VOS_UINT8                          *pucCurIndex;
    ADS_UL_CTX_STRU                    *pstAdsUlCtx;
    IMM_ZC_STRU                        *pstNode;

    pstAdsUlCtx = ADS_GetUlCtx(ucInstanceIndex);

    pucCurIndex = &pstAdsUlCtx->ucAdsUlCurIndex;

    pstNode     = VOS_NULL_PTR;

    /* ���ȼ���ʽ */
    for (i = 0; i < ADS_RAB_NUM_MAX; i++)
    {
        /* ��Ϊ�����Ѿ����򣬵�ǰ������Ч�����������ж��ж���Ч
           ����������������Ч���У�������ͷ���� */
        if (VOS_NULL_PTR == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex))
        {
            i += ADS_RAB_NUM_MAX - (*pucCurIndex + 1U);

            *pucCurIndex = 0;

            continue;
        }

        /* ����Ϊ��Ч���е�������ʱ������������ */
        if (0 == ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex)->qlen)
        {
            /* ������һ�����е�����ʱ���������м�¼����� */
            ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

            *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;

            continue;
        }

        /* �������ȼ��ȼ���Ӧ�ļ�Ȩ���������� */
        /* ���ȼ��ߵ��ȷ��� */
        if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) < ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
        {
            /* ��ȡ����ͷ��� */
            pstNode = IMM_ZcDequeueHead(ADS_UL_GET_QUEUE_LINK_INFO(ucInstanceIndex, *pucCurIndex));

            /* ��ȡ�ý���RabId */
            *pucRabId = ADS_UL_GET_PRIO_QUEUE_INDEX(ucInstanceIndex, *pucCurIndex);

            /* �����м�¼������ 1*/
            ADS_UL_SET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex, 1);

            /* ����Ѿ������걾���е����ȼ���Ȩ�����������ݣ��������¸����з������� */
            if (ADS_UL_GET_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex) == ADS_UL_GET_QUEUE_PRI_WEIGHTED_NUM(ucInstanceIndex, *pucCurIndex))
            {
                /* ������һ�����е�����ʱ���������м�¼����� */
                ADS_UL_CLR_RECORD_NUM_IN_WEIGHTED(ucInstanceIndex, *pucCurIndex);

                *pucCurIndex = (*pucCurIndex + 1) % ADS_RAB_NUM_MAX;
            }

            break;
        }
    }


    return pstNode;
}
IMM_ZC_STRU* ADS_UL_GetNextQueueNode(
    VOS_UINT8                          *pucRabId,
    VOS_UINT8                          *pucInstanceIndex
)
{
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstNode = VOS_NULL_PTR;
    VOS_UINT8                           i;
    VOS_UINT8                           ucCurInstanceIndex;

    pstAdsCtx = ADS_GetAllCtx();

    ucCurInstanceIndex = pstAdsCtx->ucAdsCurInstanceIndex;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        ucCurInstanceIndex = ucCurInstanceIndex % ADS_INSTANCE_MAX_NUM;

        pstNode = ADS_UL_GetInstanceNextQueueNode(ucCurInstanceIndex, pucRabId);

        if (VOS_NULL_PTR != pstNode)
        {
            break;
        }

        ucCurInstanceIndex++;
    }

    /* ����ʵ������������BDʱ��modem id */
    *pucInstanceIndex = ucCurInstanceIndex;

    /* ��¼�´δ��ĸ�ʵ����ȥ���� */
    pstAdsCtx->ucAdsCurInstanceIndex = (ucCurInstanceIndex + 1) % ADS_INSTANCE_MAX_NUM;

    return pstNode;
}



VOS_VOID ADS_UL_SaveIpfUlSrcMem(IMM_ZC_STRU *pstImmZcNode)
{
    IMM_ZC_HEAD_STRU                   *pstUlFreeQue = VOS_NULL_PTR;

    /* ���ٶ����ܵ�Ӱ�죬���ú����ܱ�֤pstIpfUlBdBuff��ulSaveNum����Ч�ԣ����в����в������ */

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    /* ������� */
    IMM_ZcQueueTail(pstUlFreeQue, pstImmZcNode);

    ADS_DBG_UL_IPF_SAVE_SRCMEM_SUCC_NUM(1);

    return;
}


VOS_VOID ADS_UL_FreeIpfUlConfigSuccSrcMem(VOS_VOID)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;
    VOS_UINT32                        ulIdleBD;
    VOS_UINT32                        ulBusyBD;
    VOS_UINT32                        ulCanFree;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    IMM_ZC_STRU                      *pFreeNode = VOS_NULL_PTR;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    ulQueCnt = IMM_ZcQueueLen(pstUlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    /* get busy bd num */
    ulIdleBD = mdrv_ipf_get_uldesc_num();
    ulBusyBD = IPF_ULBD_DESC_SIZE - ulIdleBD;
    if (ulQueCnt >= ulBusyBD)
    {
        ulCanFree = ulQueCnt - ulBusyBD;
    }
    else
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_UL, "ADS_UL_FreeIpfUlSrcMem: Buff Num Less IPF Busy BD Num.",ulQueCnt,ulBusyBD);
        ADS_DBG_UL_IPF_FREE_SRCMEM_ERROR(1);
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulCanFree; ulCnt++)
    {
        pFreeNode = IMM_ZcDequeueHead(pstUlFreeQue);

        IMM_ZcFree(pFreeNode);

        ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}


VOS_VOID ADS_UL_FreeIpfUlConfigFailSrcMem(VOS_UINT32 ulNeedFreeCnt)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    IMM_ZC_STRU                      *pFreeNode = VOS_NULL_PTR;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    ulQueCnt = IMM_ZcQueueLen(pstUlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    if (ulNeedFreeCnt > ulQueCnt)
    {
        ADS_ERROR_LOG2(ACPU_PID_ADS_UL, "ADS_UL_FreeIpfUlConfigFailSrcMem: Queue Num Less Need Free Num.",ulQueCnt,ulNeedFreeCnt);
        ADS_DBG_UL_IPF_FREE_SRCMEM_ERROR(1);
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulNeedFreeCnt; ulCnt++)
    {
        pFreeNode = IMM_ZcDequeueTail(pstUlFreeQue);

        IMM_ZcFree(pFreeNode);

        ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}
VOS_VOID ADS_UL_ClearIpfUlSrcMem(VOS_VOID)
{
    IMM_ZC_HEAD_STRU                 *pstUlFreeQue = VOS_NULL_PTR;
    VOS_UINT32                        ulQueCnt;
    VOS_UINT32                        ulCnt;
    IMM_ZC_STRU                      *pstFreeNode = VOS_NULL_PTR;
    VOS_UINT8                         i;
    VOS_UINT32                        ulIpfUlBdNum;

    pstUlFreeQue = ADS_UL_IPF_SRCMEM_FREE_QUE();

    ulQueCnt = IMM_ZcQueueLen(pstUlFreeQue);
    if (0 == ulQueCnt)
    {
        return;
    }

    /* ���е�PDP��ȥ����󣬲���BD�Ѿ�ȫ�����У�����������ȫ�����꣬���������Դ�ڴ���� */
    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        if (VOS_FALSE == ADS_UL_CheckAllQueueEmpty(i))
        {
            return;
        }
    }

    ulIpfUlBdNum = mdrv_ipf_get_uldesc_num();

    /* ����BD���63�� */
    if (IPF_ULBD_DESC_SIZE != ulIpfUlBdNum)
    {
        return;
    }

    /*free src mem*/
    for (ulCnt = 0; ulCnt < ulQueCnt; ulCnt++)
    {
        pstFreeNode = IMM_ZcDequeueHead(pstUlFreeQue);

        IMM_ZcFree(pstFreeNode);

        ADS_DBG_UL_IPF_FREE_SRCMEM_NUM(1);
    }

    return;
}
VOS_VOID ADS_UL_SetMaxQueueLength(
    VOS_UINT32                          ulLength,
    VOS_UINT8                           ucInstanceIndex
)
{
    g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.ulUlMaxQueueLength = ulLength;
}


VOS_VOID ADS_UL_ConfigBD(VOS_UINT32 ulBdNum)
{
    VOS_UINT32                          ulCnt;
    VOS_INT32                           lRslt;
    VOS_UINT8                           ucRabId;
    IMM_ZC_STRU                        *pstImmZcNode;
    IPF_CONFIG_ULPARAM_S               *pstIpfConfigUlParam;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT32                          i;
#ifdef CONFIG_ARM64
    struct device                       dev;
    VOS_UINT64                          dma_mask = 0xffffffffULL;

    VOS_MemSet(&dev, 0, (VOS_SIZE_T)sizeof(dev));

    dev.dma_mask = &(dma_mask);
#endif

    for (ulCnt = 0; ulCnt < ulBdNum; ulCnt++)
    {
        pstImmZcNode = ADS_UL_GetNextQueueNode(&ucRabId, &ucInstanceIndex);

        if (VOS_NULL_PTR == pstImmZcNode)
        {
            break;
        }

        /* ��ȡ����IPF��BD��Ϣ */
        pstIpfConfigUlParam = ADS_UL_GET_BD_CFG_PARA_PTR(ulCnt);

        pstIpfConfigUlParam->u32Data      = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstImmZcNode->data);

        pstIpfConfigUlParam->u16Len       = (VOS_UINT16)pstImmZcNode->len;
        pstIpfConfigUlParam->u16UsrField1 = (VOS_UINT16)ADS_UL_BUILD_BD_USER_FIELD_1(ucInstanceIndex, ucRabId);
        pstIpfConfigUlParam->u32UsrField3 = (VOS_UINT)pstImmZcNode->tstamp.tv64;

        /* ADS �������ݴ�ӡ���� */
        if (VOS_TRUE == g_ulAdsPrintUlDataFlg)
        {
            vos_printf("ADS_UL_ConfigBD: ucInstanceIndex is %d, ucRabId is %d, attribute is %d\r\n", ucInstanceIndex, ucRabId, pstIpfConfigUlParam->u16UsrField1);

            vos_printf("ADS_UL_ConfigBD: Data Len is %d.\r\n", pstImmZcNode->len);

            vos_printf("ADS_UL_ConfigBD: Data Content is :\r\n");

            for (i = 0; i < pstImmZcNode->len; i++)
            {
                if (pstImmZcNode->data[i] > 0xf)
                {
                    vos_printf("%x", pstImmZcNode->data[i]);
                }
                else
                {
                    vos_printf("0%x", pstImmZcNode->data[i]);
                }
            }

            vos_printf("\r\n");
        }

        /* Attribute: �ж�ʹ�ܣ����˼Ӱ��ƣ����������modem0��0��modem1��1 */
        pstIpfConfigUlParam->u16Attribute = (VOS_UINT16)ADS_UL_BUILD_BD_ATTRIBUTE(VOS_FALSE, IPF_MODE_FILTERANDTRANS, ADS_UL_GET_BD_FC_HEAD(ucInstanceIndex));

        IPS_MNTN_TraceIpInfo(pstImmZcNode, ID_IPS_TRACE_ADS_UL,
                             pstIpfConfigUlParam->u16UsrField1, pstIpfConfigUlParam->u32UsrField2,
                             pstIpfConfigUlParam->u32UsrField3, 0);

        /* ��Ҫ������д��DDR��IPF��DDR�ж����� */
#ifdef CONFIG_ARM64
        ADS_CACHE_FLUSH_WITH_DEV(&dev, pstImmZcNode->data, pstIpfConfigUlParam->u16Len);
#else
        ADS_CACHE_FLUSH(pstImmZcNode->data, pstIpfConfigUlParam->u16Len);
#endif

        /* �������õ�BDԴ�ڴ汣�浽Դ�ڴ���� */
        ADS_UL_SaveIpfUlSrcMem(pstImmZcNode);
    }

    /* ʵ�ʴӶ�����ȡ�����ݸ������Ϊ0���쳣 */
    if (0 == ulCnt)
    {
        return;
    }

    /* ���һ��BD�����ж�ʹ�� */
    pstIpfConfigUlParam = ADS_UL_GET_BD_CFG_PARA_PTR(0);
    ADS_UL_SET_BD_ATTR_INT_FLAG(pstIpfConfigUlParam[ulCnt -1].u16Attribute);

    /* ����BD��д��IPF */
    lRslt = mdrv_ipf_config_ulbd(ulCnt, ADS_UL_GET_BD_CFG_PARA_PTR(0));
    if (IPF_SUCCESS != lRslt)
    {
        /* дIPFʧ�ܵĴ��� */
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_ConfigBD: IPF CONFIG FAIL!");

        /* IPF����ʧ�ܣ���Ҫ�ͷ�Դ�ڴ� */
        ADS_UL_FreeIpfUlConfigFailSrcMem(ulCnt);

        ADS_DBG_UL_SEND_PKT_FAIL_NUM(ulCnt);

        return;
    }

    ADS_DBG_UL_SEND_BUFF_PKT_NUM(ulCnt);

    /* ׷�����з������� */
    ADS_MNTN_TraceSndUlData();

    ADS_UL_EnableTxWakeLockTimeout(ADS_UL_TX_WAKE_LOCK_TMR_LEN);
    return;
}
VOS_VOID ADS_UL_ProcLinkData(VOS_VOID)
{
    VOS_UINT32                          ulAllUlQueueDataNum;
    VOS_UINT32                          ulIpfUlBdNum;
    VOS_UINT32                          ulSndBdNum;

    /* �������ʱ�е����� */
    for (;;)
    {
        /* ���ڸ�λ������ֱ���˳� */
        if (VOS_TRUE == ADS_GetUlResetFlag())
        {
            printk(KERN_ERR "\n ADS_UL_ProcLinkData in ccore reset \n");
            return;
        }


        /* ��ȡ���п��Է��͵�BD���� */
        ulIpfUlBdNum = mdrv_ipf_get_uldesc_num();

        if (0 == ulIpfUlBdNum)
        {
            ADS_DBG_UL_CFG_IPF_HAVE_NO_BDCD(1);

            /* ���÷��ͽ�����־ */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);

            /* ������ʱ���˳� */
            ADS_StartTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());
            break;
        }


        /* �������ڷ��ͱ�־ */
        ADS_UL_SET_SENDING_FLAG(VOS_TRUE);

        /* ��ȡ��ǰ���ж����е����ݰ����� */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /* ���㵱ǰ�ɷ��͵�BD��Ŀ */
        ulSndBdNum = PS_MIN(ulIpfUlBdNum, ulAllUlQueueDataNum);

        ADS_UL_FreeIpfUlConfigSuccSrcMem();

        /* ����BD��д��IPF */
        ADS_UL_ConfigBD(ulSndBdNum);

        /* ��ȡ��ǰ���ж����е����ݰ����� */
        ulAllUlQueueDataNum = ADS_UL_GetAllQueueDataNum();

        /* ��ǰ������û�����ݣ��˳����ȴ��´ζ����ɿձ�Ϊ�ǿմ��� */
        if (0 == ulAllUlQueueDataNum)
        {
            /* ���÷��ͽ�����־ */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);
            break;
        }
        /* ��ǰ�����������ݣ�������Ҫ�����ܰ� */
        else if (ulAllUlQueueDataNum <= ADS_UL_SEND_DATA_NUM_THREDHOLD)
        {
            ADS_StartTimer(ACPU_PID_ADS_UL, TI_ADS_UL_SEND, ADS_UL_GET_PROTECT_TIMER_LEN());

            /* ���÷��ͽ�����־ */
            ADS_UL_SET_SENDING_FLAG(VOS_FALSE);
            break;
        }
        else
        {
            continue;
        }
    }

    return;
}
VOS_UINT32 ADS_UL_ProcPdpStatusInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    ADS_PDP_STATUS_ENUM_UINT8           enPdpStatus,
    ADS_QCI_TYPE_ENUM_UINT8             enQciType,
    ADS_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;
    ADS_QCI_TYPE_ENUM_UINT8             enPrio;

    enPktType                           = ADS_CDS_IPF_PKT_TYPE_IP;

    ucInstanceIndex                     = (VOS_UINT8)enModemId;

    enPrio                              = enQciType;

    /* RabId�Ϸ��Լ�� */
    if (VOS_OK != ADS_IsValidRabId(ucRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_UL, "ADS_UL_ProcPdpStatusInd: ucRabId is ", ucRabId);
        return VOS_ERR;
    }

    /* ������������ȼ������޸�����PDP��QCIΪ��ͬ���ȼ������������㷨��������ʹ�ȼ����PDP���ȴ��� */
    if (VOS_FALSE == g_stAdsCtx.astAdsSpecCtx[ucInstanceIndex].stAdsUlCtx.stQueuePriNv.ulStatus)
    {
        enPrio = ADS_QCI_TYPE_QCI9_NONGBR;
    }

    if (ADS_PDP_PPP == enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    /* ����PDP״̬�ֱ���д��� */
    switch(enPdpStatus)
    {
        /* PDP���� */
        case ADS_PDP_STATUS_ACT:

            /* ����������� */
            ADS_UL_CreateQueue(ucInstanceIndex, ucRabId, enPrio, enPktType);

            /* ��������ͳ�� */
            ADS_UL_StartDsFlowStats(ucInstanceIndex, ucRabId);

            /* �����ϱ�ͳ����Ϣ��ʱ�� */
            ADS_UL_StartRptStatsInfoTimer(ucInstanceIndex, ucRabId);

            break;

        /* PDP�޸� */
        case ADS_PDP_STATUS_MODIFY:

            /* ���޸ĵĶ�����Ϣ���µ����ж��й����� */
            ADS_UL_UpdateQueueInPdpModified(ucInstanceIndex, enPrio, ucRabId);

            break;

        /* PDPȥ���� */
        case ADS_PDP_STATUS_DEACT:

            /* ���ٻ������ */
            ADS_UL_DestroyQueue(ucInstanceIndex, ucRabId);

            /* �����е�PDP��ȥ��������Դ�ڴ���� */
            ADS_UL_ClearIpfUlSrcMem();

            /* ֹͣ����ͳ�� */
            ADS_UL_StopDsFlowStats(ucInstanceIndex, ucRabId);

            /* �ر��ϱ�ͳ����Ϣ��ʱ�� */
            ADS_UL_StopRptStatsInfoTimer();

            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    VOS_UINT32                          ulRslt;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    ulRslt = ADS_UL_ProcPdpStatusInd(pstPdpStatusInd->enModemId,
                                     pstPdpStatusInd->ucRabId,
                                     pstPdpStatusInd->enPdpStatus,
                                     pstPdpStatusInd->enQciType,
                                     pstPdpStatusInd->enPdpType);

    return ulRslt;
}


VOS_UINT32 ADS_UL_RcvCdsIpPacketMsg(MsgBlock *pMsg)
{
    VOS_UINT32                          ulResult;
    ADS_NDIS_DATA_IND_STRU             *pstAdsNdisDataInd;
    IMM_ZC_STRU                        *pstZcData;
    CDS_ADS_DATA_IND_STRU              *pstDataInd;
    VOS_CHAR                           *pstZcPutData;

    pstDataInd = (CDS_ADS_DATA_IND_STRU *)pMsg;

    /* ������Ϣ  */
    pstAdsNdisDataInd = (ADS_NDIS_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                             ACPU_PID_ADS_UL,
                                             sizeof(ADS_NDIS_DATA_IND_STRU));

    if (VOS_NULL_PTR == pstAdsNdisDataInd)
    {
        return VOS_ERR;
    }

    PS_MEM_SET((VOS_INT8 *)pstAdsNdisDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_NDIS_DATA_IND_STRU) - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    pstAdsNdisDataInd->ulReceiverPid  = PS_PID_APP_NDIS;
    pstAdsNdisDataInd->enMsgId        = ID_ADS_NDIS_DATA_IND;
    pstAdsNdisDataInd->enModemId      = pstDataInd->enModemId;
    pstAdsNdisDataInd->ucRabId        = pstDataInd->ucRabId;
    pstAdsNdisDataInd->enIpPacketType = pstDataInd->enIpPacketType;

    pstZcData = (IMM_ZC_STRU *)IMM_ZcStaticAlloc((VOS_UINT32)pstDataInd->usLen);

    if (VOS_NULL_PTR == pstZcData)
    {
        PS_MEM_FREE(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

        return VOS_ERR;
    }


    /*�˲��費���٣�����ƫ������βָ��*/
    pstZcPutData = (VOS_CHAR *)IMM_ZcPut(pstZcData, pstDataInd->usLen);

    PS_MEM_CPY(pstZcPutData, pstDataInd->aucData, pstDataInd->usLen);

    pstAdsNdisDataInd->pstSkBuff = pstZcData;

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_UL, pstAdsNdisDataInd);

    if(VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_RcvCdsIpPacketMsg: Send Msg Fail!");

        IMM_ZcFree(pstZcData);

        return VOS_ERR;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucInsIndex;
    VOS_UINT8                           ucRabIndex;
    VOS_UINT8                           ucTiIndex;
    ADS_CTX_STRU                       *pstAdsCtx = VOS_NULL_PTR;

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n ADS_UL_RcvCcpuResetStartInd enter, %u \n", VOS_GetSlice());
#endif

    pstAdsCtx = ADS_GetAllCtx();

    /* ����������л������ */
    for (ucInsIndex = 0; ucInsIndex < ADS_INSTANCE_MAX_NUM; ucInsIndex++)
    {
        for (ucRabIndex = 0; ucRabIndex < ADS_RAB_ID_MAX + 1; ucRabIndex++)
        {
            ADS_UL_DestroyQueue(ucInsIndex, ucRabIndex);
        }
    }

    /* ���Դ�ڴ���� */
    ADS_UL_ClearIpfUlSrcMem();

    /* ֹͣ���������Ķ�ʱ�� */
    for (ucTiIndex = 0; ucTiIndex < ADS_MAX_TIMER_NUM; ucTiIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_UL, ucTiIndex, ADS_TIMER_STOP_CAUSE_USER);
    }

    /* �������������� */
    ADS_ResetUlCtx();

    /* ����IPF��ص������� */
    ADS_ResetIpfCtx();

    /* ���õ�ǰʵ������ֵ */
    pstAdsCtx->ucAdsCurInstanceIndex = ADS_INSTANCE_INDEX_0;

    /* ����ADS Filter���������� */
    ADS_FILTER_Reset();

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n ADS_UL_RcvCcpuResetStartInd leave, %u \n", VOS_GetSlice());
#endif

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(ADS_GetULResetSem());

    return VOS_OK;
}

VOS_VOID ADS_UL_RcvTiDsFlowStatsExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulTaBytes;
    VOS_UINT32                          ulRate;
    VOS_UINT8                           ucInstance;

    /* ��ǰ��ͳ��Modem0��������Ϣ */
    ucInstance = ADS_INSTANCE_INDEX_0;

    /* ���û�����ж��д���, ����ͳ������ */
    if (VOS_FALSE == ADS_UL_IsAnyQueueExist(ucInstance))
    {
        ADS_NORMAL_LOG(ACPU_PID_ADS_DL, "ADS_UL_RcvTiDsFlowStatsExpired: no queue is exist!");
        return;
    }

    /* ��ȡ2����������ݸ��� */
    ulTaBytes = ADS_GET_DL_PERIOD_PKT_NUM(ucInstance);

    /* ÿ2���Ӽ���һ��,��λΪ:byte/s */
    ulRate = ulTaBytes>>1;
    ADS_SET_CURRENT_DL_RATE(ucInstance, ulRate);

    /* ��ȡ2����������� */
    ulTaBytes = ADS_GET_UL_PERIOD_PKT_NUM(ucInstance);

    /* ÿ2���Ӽ���һ��,��λΪ:byte/s */
    ulRate = ulTaBytes>>1;
    ADS_SET_CURRENT_UL_RATE(ucInstance, ulRate);

    /* ÿ������ͳ�����ڽ�������Ҫ������ͳ��Byte����� */
    ADS_CLEAR_UL_PERIOD_PKT_NUM(ucInstance);
    ADS_CLEAR_DL_PERIOD_PKT_NUM(ucInstance);

    /* ��������ͳ�ƶ�ʱ��*/
    ADS_StartTimer(ACPU_PID_ADS_UL,
                   ulTimerName,
                   TI_ADS_DSFLOW_STATS_LEN);

    return ;
}


VOS_VOID ADS_UL_RcvTiRptStatsInfoExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    ADS_LOG_RPT_STATS_INFO_STRU        *pstMsg = VOS_NULL_PTR;

    /* ����¼��ͳ����Ϣͨ��SDT��Ϣ������ */
    pstMsg = (ADS_LOG_RPT_STATS_INFO_STRU*)PS_MEM_ALLOC(ACPU_PID_ADS_UL, sizeof(ADS_LOG_RPT_STATS_INFO_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_UL, "ADS_UL_RcvTiRptStatsInfoExpired: ERROR:Alloc Mem Fail");
        return;
    }

    PS_MEM_SET(pstMsg, 0, sizeof(ADS_LOG_RPT_STATS_INFO_STRU));

    pstMsg->stLogHeader.ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMsg->stLogHeader.ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMsg->stLogHeader.ulSenderPid     = ACPU_PID_ADS_UL;
    pstMsg->stLogHeader.ulReceiverPid   = ACPU_PID_ADS_UL;
    pstMsg->stLogHeader.ulLength        = sizeof(ADS_LOG_RPT_STATS_INFO_STRU) - VOS_MSG_HEAD_LENGTH;;
    pstMsg->stLogHeader.enMsgId         = ID_ADS_LOG_RPT_STATS_INFO;

    PS_MEM_CPY(&pstMsg->stAdsStats, &g_stAdsStats, sizeof(g_stAdsStats));

    DIAG_TraceReport(pstMsg);

    PS_MEM_FREE(ACPU_PID_ADS_UL, pstMsg);

    /* ���������ϱ�ͳ����Ϣ��ʱ�� */
    ADS_StartTimer(ACPU_PID_ADS_UL, ulTimerName, TI_ADS_RPT_STATS_LEN);

    return ;
}



VOS_VOID ADS_UL_RcvTiDataStatExpired(
    VOS_UINT32                          ulTimerName,
    VOS_UINT32                          ulParam
)
{
    VOS_UINT32                          ulStatPktNum;

    ulStatPktNum = ADS_UL_GET_STAT_PKT_NUM();

    /* �������ݰ����������ް����� */
    if (ulStatPktNum < ADS_UL_GET_WATER_LEVEL_ONE())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_ONE);
        ADS_DBG_UL_LEVEL_ONE_CNT(1);
    }
    else if (ulStatPktNum <  ADS_UL_GET_WATER_LEVEL_TWO())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_TWO);
        ADS_DBG_UL_LEVEL_TWO_CNT(1);
    }
    else if (ulStatPktNum <  ADS_UL_GET_WATER_LEVEL_THREE())
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_THREE);
        ADS_DBG_UL_LEVEL_THREE_CNT(1);
    }
    else
    {
        ADS_UL_SET_SEND_DATA_NUM_THREDHOLD(ADS_UL_DATA_THRESHOLD_FOUR);
        ADS_DBG_UL_LEVEL_FOUR_CNT(1);
    }

    /* 100ms��û�����ݰ���ö�ʱ���������� */
    if (0 != ulStatPktNum)
    {
        /* ������������ͳ�ƶ�ʱ�� */
        ADS_StartTimer(ACPU_PID_ADS_UL, TI_ADS_UL_DATA_STAT, ADS_UL_GET_STAT_TIMER_LEN());
    }

    /* ���ͳ�ư��ĸ��� */
    ADS_UL_CLR_STAT_PKT_NUM();

    return;
}


VOS_UINT32 ADS_UL_RcvTafMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;


    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_UL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvCdsMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_CDS_ADS_IP_PACKET_IND:
            ADS_UL_RcvCdsIpPacketMsg(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_UL_RcvTimerMsg(MsgBlock *pMsg)
{
    REL_TIMER_MSG                      *pstTimerMsg;

    pstTimerMsg = (REL_TIMER_MSG *)pMsg;

    /* ֹͣ�ö�ʱ�� */
    ADS_StopTimer(ACPU_PID_ADS_UL, pstTimerMsg->ulName, ADS_TIMER_STOP_CAUSE_TIMEOUT);

    switch (pstTimerMsg->ulName)
    {
        case TI_ADS_UL_SEND:
            ADS_UL_WakeLock();
            ADS_UL_ProcLinkData();
            ADS_UL_WakeUnLock();
            break;

        case TI_ADS_DSFLOW_STATS:
            ADS_UL_RcvTiDsFlowStatsExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            break;

        case TI_ADS_RPT_STATS_INFO:
            ADS_UL_RcvTiRptStatsInfoExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            break;

        case TI_ADS_UL_DATA_STAT:
            ADS_UL_RcvTiDataStatExpired(pstTimerMsg->ulName, pstTimerMsg->ulPara);
            break;

        default:
            break;
    }

    return VOS_OK;
}
VOS_UINT32 ADS_UL_RcvAdsUlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_UL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            /* do nothing */
            ADS_NORMAL_LOG(ACPU_PID_ADS_UL, "ADS_DL_RcvAdsDlMsg: rcv ID_CCPU_ADS_UL_RESET_END_IND");
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_UL, "ADS_UL_RcvAdsUlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}
VOS_VOID ADS_UL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ��Ϣ�ķַ����� */
    switch ( pMsg->ulSenderPid )
    {
        /* ����Timer����Ϣ */
        case VOS_PID_TIMER:
            ADS_UL_RcvTimerMsg(pMsg);
            return;

        /* ����TAF����Ϣ */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ADS_UL_RcvTafMsg(pMsg);
            return;

        /* ����CDS����Ϣ */
        case UEPS_PID_CDS:
            ADS_UL_RcvCdsMsg(pMsg);
            return;

        /* ����ADS UL����Ϣ */
        case ACPU_PID_ADS_UL:
            ADS_UL_RcvAdsUlMsg(pMsg);
            return;

        default:
            return;
    }
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
