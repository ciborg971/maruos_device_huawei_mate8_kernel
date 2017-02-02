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
#include "AdsDownLink.h"
#include "AdsDebug.h"
#include "mdrv.h"
#include "IpsMntn.h"
#include "AcpuReset.h"
#include "AdsFilter.h"
#include "AdsDhcpInterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DOWNLINK_C
/*lint +e767*/


/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

#if defined(CONFIG_ARCH_HI3650)
extern 	atomic_long_t naspg_nr;
#endif


/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/


VOS_INT32 ADS_DL_IpfIntCB(VOS_VOID)
{
    /* ��������IPF�ж�ͳ�Ƽ��� */
    ADS_DBG_DL_RECV_IPF_BREAK_NUM(1);

    /* ��������RD�����¼� */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);

    return VOS_OK;
}


VOS_VOID ADS_DL_RcvTiProtectExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* ͳ�ƶ�ʱ����ʱ���� */
    ADS_DBG_DL_RD_TI_PROTECT_EXPIRED_NUM(1);

    /* ֹͣ��ʱ�� */
    ADS_StopTimer(ACPU_PID_ADS_DL, TI_ADS_DL_PROTECT, ADS_TIMER_STOP_CAUSE_USER);

    if (mdrv_ipf_get_dlrd_num() > 0)
    {
        ADS_DBG_DL_RD_PROTECT_EVENT_NUM(1);

        ADS_DL_SndEvent(ADS_DL_EVENT_IPF_RD_INT);
    }

    /* ��������������ʱ�� */
    ADS_DL_StartProtectTimer();

    return;
}
VOS_INT32 ADS_DL_IpfAdqEmptyCB(IPF_ADQ_EMPTY_E eAdqEmpty)
{
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_RECV_ADQ_EMPTY_BREAK_NUM(1);
    ADS_DBG_DL_GET_ADQ_EMPTY_NUM(eAdqEmpty, 1);
    return VOS_OK;
}



VOS_VOID ADS_DL_RcvTiAdqEmptyExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    /* ��������ADQ���жϴ����¼� */
    ADS_DL_SndEvent(ADS_DL_EVENT_IPF_ADQ_EMPTY_INT);
    ADS_DBG_DL_ADQ_EMPTY_TMR_TIMEOUT_NUM(1);
    return;
}
VOS_VOID ADS_DL_ConfigAdq(
    IPF_AD_TYPE_E                       enAdType,
    VOS_UINT                            ulIpfAdNum,
    VOS_UINT                           *pulActAdNum
)
{
    VOS_UINT32                          i;
    IMM_ZC_STRU                        *pstZcData = VOS_NULL_PTR;
    VOS_CHAR                           *pstZcPullData = VOS_NULL_PTR;
    VOS_UINT8                          *pstZcHead = VOS_NULL_PTR;
    VOS_UINT32                          ulActAdNum;
    VOS_UINT16                          usLen;
    IPF_AD_DESC_S                      *pstIpfAdDesc = VOS_NULL_PTR;
    VOS_INT32                           lRslt;
#ifdef CONFIG_ARM64
    struct device                       dev;
    VOS_UINT64                          dma_mask = 0xffffffffULL;

    VOS_MemSet(&dev, 0, (VOS_SIZE_T)sizeof(dev));

    dev.dma_mask = &(dma_mask);
#endif

    ulActAdNum = 0;

    if (IPF_AD_0 == enAdType)
    {
        usLen = ADS_DL_AD0_DATA_LEN;
    }
    else
    {
        usLen = ADS_DL_AD1_DATA_LEN;
    }

    for (i = 0; i < ulIpfAdNum; i++)
    {
        pstIpfAdDesc = ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, i);

        pstZcData = (IMM_ZC_STRU *)IMM_ZcStaticAlloc(usLen);

        if (VOS_NULL_PTR == pstZcData)
        {
            ADS_DBG_DL_ALLOC_AD_FAIL_NUM(enAdType, 1);
            break;
        }

#if defined(CONFIG_ARCH_HI3650)
        pstZcData->psh = 1;
        atomic_long_add(1,&naspg_nr);
#endif

        /* ��������ͷ��� */
        pstZcHead = pstZcData->data;

        /* ƫ��skbuff��tailָ�� */
        IMM_ZcPut(pstZcData, usLen);

        /* ƫ��headָ��14���ֽڣ�����MACͷ */
        pstZcPullData = (VOS_CHAR *)IMM_ZcPull(pstZcData, ADS_DL_AD_DATA_PTR_OFFSET);

#ifdef CONFIG_ARM64
        ADS_CACHE_INVALIDATE_WITH_DEV(&dev, pstZcHead, usLen);
#else
        ADS_CACHE_INVALIDATE(pstZcHead, usLen);
#endif

        /* ���OUTPUT0��Ŀ�ĵ�ַ */
        pstIpfAdDesc->u32OutPtr0 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstZcPullData);

        /* ���OUTPUT1��SKBUFF */
        pstIpfAdDesc->u32OutPtr1 = (VOS_UINT32)virt_to_phys((VOS_VOID *)pstZcData);


        ADS_DBG_DL_ALLOC_AD_SUCC_NUM(enAdType, 1);;

        ulActAdNum++;
    }

    /* ���뵽AD����Ҫ����ADQ */
    if (0 != ulActAdNum)
    {
        lRslt = mdrv_ipf_config_dlad(enAdType, ulActAdNum, ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, 0));

        if (IPF_SUCCESS != lRslt)
        {
            ADS_DBG_DL_CONFIG_AD_FAIL_NUM(enAdType, 1);

            /* ����ʧ�ܣ��ͷ��ڴ� */
            for (i = 0; i < ulActAdNum; i++)
            {
                IMM_ZcFree((IMM_ZC_STRU *)phys_to_virt(ADS_DL_GET_IPF_AD_BUFFER_PTR(enAdType, i)->u32OutPtr1));
            }

            *pulActAdNum = 0;
            return;
        }

        ADS_DBG_DL_CONFIG_AD_SUCC_NUM(enAdType, 1);
    }

    /* ���ʵ�����õ�AD��Ŀ */
    *pulActAdNum = ulActAdNum;

    return;
}


VOS_VOID ADS_DL_ProcAdq(VOS_VOID)
{
    VOS_INT32                           lRslt;
    VOS_UINT                            ulIpfAd0Num;
    VOS_UINT                            ulIpfAd1Num;
    VOS_UINT                            ulActAd0Num;
    VOS_UINT                            ulActAd1Num;

    ulIpfAd0Num = 0;
    ulIpfAd1Num = 0;
    ulActAd0Num = 0;
    ulActAd1Num = 0;

    /* ��ȡ����ADQ�Ŀ��е�AD���� */
    lRslt = mdrv_ipf_get_dlad_num(&ulIpfAd0Num, &ulIpfAd1Num);
    if (IPF_SUCCESS != lRslt)
    {
        ADS_DBG_DL_GET_AD_FAIL_NUM(1);
        return;
    }

    /* �������ô��ڴ��ADQ1 */
    if (0 != ulIpfAd1Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_1, ulIpfAd1Num, &ulActAd1Num);
    }

    /* ������С�ڴ��ADQ0 */
    if (0 != ulIpfAd0Num)
    {
        ADS_DL_ConfigAdq(IPF_AD_0, ulIpfAd0Num, &ulActAd0Num);
    }

    /* AD0Ϊ�ջ���AD1Ϊ����Ҫ����������ʱ�� */
    if ( ((0 == ulActAd0Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd0Num))
      || ((0 == ulActAd1Num) && (ADS_IPF_DLAD_START_TMR_THRESHOLD < ulIpfAd1Num)) )
    {
        /* �������ADQ�κ�һ���������벻���ڴ棬����ʱ�� */
        ADS_DL_StartAdqEmptyTimer();
    }

    return;
}
VOS_VOID ADS_DL_InitAdq(VOS_VOID)
{
    ADS_DL_ProcAdq();
}


VOS_VOID ADS_DL_SendNdClientDataInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_NDCLIENT_DATA_IND_STRU         *pstDataInd;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);

    usDataLen = pstRdDesc->u16PktLen;

    /*������Ϣ  */
    pstDataInd = (ADS_NDCLIENT_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2);

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstDataInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: pstDataInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_NDCLIENT_DATA_IND_STRU) + usDataLen - 2 - VOS_MSG_HEAD_LENGTH));

    /*��д��Ϣ����*/
    /* ND CLIENT ��PID */
    pstDataInd->ulReceiverPid = UEPS_PID_NDCLIENT;
    pstDataInd->enMsgId       = ID_ADS_NDCLIENT_DATA_IND;
    pstDataInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->usLen         = usDataLen;

    PS_MEM_CPY(pstDataInd->aucData, pstImmZc->data, usDataLen);


    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstDataInd);

    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendNdClientDataInd: Send msg fail!");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_DL_SendDhcpDataInd
 ��������  : DHCPv6����ͨ��VOS����DHCP
 �������  : VOS_VOID *pData
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2015��05��18��
    ��    ��   : w00316385
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_DL_SendDhcpDataInd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    VOS_UINT32                          ulResult;
    ADS_DHCP_DATA_IND_STRU             *pstDataInd;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT16                          usDataLen;

    pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);

    usDataLen = pstRdDesc->u16PktLen;

    /* ������Ϣ */
    pstDataInd = (ADS_DHCP_DATA_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                                               ACPU_PID_ADS_DL,
                                               sizeof(ADS_DHCP_DATA_IND_STRU) + usDataLen - 2);

    /* �ڴ�����ʧ�ܣ����� */
    if( VOS_NULL_PTR == pstDataInd )
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpDataInd: pstDataInd is NULL!");

        return;
    }

    PS_MEM_SET((VOS_INT8 *)pstDataInd + VOS_MSG_HEAD_LENGTH,
               0x00,
               (VOS_SIZE_T)(sizeof(ADS_DHCP_DATA_IND_STRU) + usDataLen - 2 - VOS_MSG_HEAD_LENGTH));

    /* ��д��Ϣ���� */
    /* DHCP ��PID */
    pstDataInd->ulReceiverPid = UEPS_PID_DHCP;
    pstDataInd->enMsgId       = ID_ADS_DHCP_DATA_IND;
    pstDataInd->enModemId     = ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->ucRabId       = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    pstDataInd->usLen         = usDataLen;

    PS_MEM_CPY(pstDataInd->aucData, pstImmZc->data, usDataLen);

    /* ����VOS����ԭ�� */
    ulResult = PS_SEND_MSG(ACPU_PID_ADS_DL, pstDataInd);

    if (VOS_OK != ulResult)
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_SendDhcpDataInd: Send msg fail!");
    }

    return;
}
VOS_VOID ADS_DL_FreeIpfUsedAd0(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    /*lint -e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, begin */
    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD0_DESC_SIZE];
    /*lint +e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, end */

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD0_DESC_SIZE));
    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_0, (VOS_UINT32 *)&ulAdNum, astAdDesc))
    {
        /* �ͷ�ADQ0���ڴ� */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD0_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)phys_to_virt(astAdDesc[i].u32OutPtr1));
        }
    }

    return;
}
VOS_VOID ADS_DL_FreeIpfUsedAd1(VOS_VOID)
{
    VOS_UINT32                          i;
    VOS_UINT32                          ulAdNum;

    /*lint -e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, begin */
    IPF_AD_DESC_S                       astAdDesc[IPF_DLAD1_DESC_SIZE];
    /*lint +e813*/ /* added by zwx247453 for pc����ת3650, 2015-08-24, end */

    ulAdNum = 0;
    PS_MEM_SET(astAdDesc, 0, (VOS_SIZE_T)(sizeof(IPF_AD_DESC_S) * IPF_DLAD1_DESC_SIZE));
    if (IPF_SUCCESS == mdrv_ipf_get_used_dlad(IPF_AD_1, (VOS_UINT32 *)&ulAdNum, astAdDesc))
    {
        /* �ͷ�ADQ1���ڴ� */
        for (i = 0; i < PS_MIN(ulAdNum, IPF_DLAD1_DESC_SIZE); i++)
        {
            IMM_ZcFree((IMM_ZC_STRU *)phys_to_virt(astAdDesc[i].u32OutPtr1));
        }
    }

    return;
}
VOS_VOID ADS_DL_FreeRd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    IMM_ZcFree((IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr));

    return;
}
/*****************************************************************************
 �� �� ��  : ADS_DL_Xmit
 ��������  : �ַ����ݰ�, ����ÿ�������ϵ����һ�����������
 �������  : ucRabId       - RABID [5, 15]
             ucInstanceIndex - modem ID
             enIpType       -IP type
             pstCurImmZc   - IP buff
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2013��6��29��
    ��    ��   :
    �޸�����   : �����ɺ���
*****************************************************************************/
VOS_VOID ADS_DL_Xmit(
    VOS_UINT8                           ucRabId,
    VOS_UINT8                           ucInstanceIndex,
    ADS_PKT_TYPE_ENUM_UINT8             enIpType,
    IMM_ZC_STRU                        *pstCurImmZc
)
{
    RCV_DL_DATA_FUNC                    pRcvDlDataFunc = VOS_NULL_PTR;
    IMM_ZC_STRU                        *pstLstImmZc = VOS_NULL_PTR;
    ADS_PKT_TYPE_ENUM_UINT8             enLstIpType;

    /* ��ȡRABID��Ӧ���лص�����ָ�� */
    if (ADS_IS_VALID_RABID(ucRabId))
    {
        pRcvDlDataFunc = ADS_DL_GET_DATA_CALLBACK_FUNC(ucInstanceIndex, ucRabId);
    }
    else
    {
        ADS_NORMAL_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_SndImmZc: Invaild rabId is", ucRabId);

        ADS_DBG_DL_FREE_NUM(ucInstanceIndex,1);

        IMM_ZcFree(pstCurImmZc);

        return;
    }

    pstLstImmZc = ADS_DL_GET_LST_DATA_PTR(ucInstanceIndex,ucRabId);
    enLstIpType    = ADS_DL_GET_LST_DATA_IPTYPE(ucInstanceIndex,ucRabId);

    /* ������������ */
    if (VOS_NULL_PTR != pRcvDlDataFunc)
    {
        if (VOS_NULL_PTR != pstLstImmZc)
        {
            ADS_DBG_SEND_DL_PKT_NUM(ucInstanceIndex, 1);
#if defined(CONFIG_ARCH_HI3650)
            /* empty opt*/
#else
            pstLstImmZc->psh = 0;
            if (VOS_NULL_PTR == pstCurImmZc)
            {
                pstLstImmZc->psh = 1;
            }
#endif

            (VOS_VOID)pRcvDlDataFunc(ADS_BUILD_EX_RAB_ID(ucInstanceIndex, ucRabId), pstLstImmZc, enLstIpType);
        }
        ADS_DL_SET_LST_DATA_PTR(ucInstanceIndex,ucRabId, pstCurImmZc);
        ADS_DL_SET_LST_DATA_IPTYPE(ucInstanceIndex,ucRabId, enIpType);
    }
    else
    {
        ADS_NORMAL_LOG1(ACPU_PID_ADS_DL,
            "ADS_DL_SendNetDevData1: Free TTF memory, RabId is", ucRabId);

        if (VOS_NULL_PTR != pstCurImmZc)
        {
            IMM_ZcFree(pstCurImmZc);
            ADS_DBG_DL_FREE_NUM(ucInstanceIndex, 1);
        }

        if (VOS_NULL_PTR != pstLstImmZc)
        {
            IMM_ZcFree(pstLstImmZc);
            ADS_DBG_DL_FREE_NUM(ucInstanceIndex, 1);
        }

        ADS_DL_SET_LST_DATA_PTR(ucInstanceIndex,ucRabId,VOS_NULL_PTR);
    }

    return;
}
VOS_VOID ADS_DL_ProcRd(
    IPF_RD_DESC_S                      *pstRdDesc
)
{
    IMM_ZC_STRU                        *pstImmZc       = VOS_NULL_PTR;
    VOS_UINT32                          ulIpLen;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRabId;
    ADS_PKT_TYPE_ENUM_UINT8             enIpType;


    /* �ӿ��޸ĺ󣬻�ȡ��ֵ */
    ucInstanceIndex = (VOS_UINT8)ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    ucRabId = ADS_DL_GET_RAB_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);
    enIpType = ADS_DL_GET_IP_TYPE_FROM_IPF_RSLT(pstRdDesc->u16Result);

    /* �����Ź��ܣ����ָ������SK BUFF */
    pstImmZc       = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);
    ulIpLen        = ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen);
    pstImmZc->tail -= (pstImmZc->len - ulIpLen);
    pstImmZc->len  = ulIpLen;

    IPS_MNTN_TraceIpInfo(pstImmZc, ID_IPS_TRACE_ADS_DL,
                         pstRdDesc->u16UsrField1, pstRdDesc->u32UsrField2,
                         pstRdDesc->u32UsrField3, 0);

    ADS_DL_Xmit(ucRabId, ucInstanceIndex, enIpType, pstImmZc);

    return;
}


VOS_VOID ADS_DL_ProcIpfResult(VOS_VOID)
{
    VOS_UINT32                          ulRdNum = IPF_DLRD_DESC_SIZE;
    VOS_UINT32                          ulCnt;
    ADS_DL_IPF_RESULT_STRU             *pstIpfRslt;
    IPF_RD_DESC_S                      *pstRdDesc;
    ADS_DRV_ASSEM_FUNC                  pFcAssemTuneFunc = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRabId;
    IMM_ZC_STRU                        *pstImmZc = VOS_NULL_PTR;
    VOS_UINT32                          ulRxTimeout;

#ifdef CONFIG_ARM64
    struct device                       dev;
    VOS_UINT64                          dma_mask = 0xffffffffULL;

    VOS_MemSet(&dev, 0, (VOS_SIZE_T)sizeof(dev));

    dev.dma_mask = &(dma_mask);
#endif

    ucInstanceIndex = 0;
    ulRxTimeout     = 0;

    /*
    IPF_RD_DESC_S��u16Result����
    [15]Reserve
    [14]bd_cd_noeqBD��len��CD�ĳ��Ȳ��ȴ�����ʾ��0��ʾ����ƥ�䣬1��ʾ���Ȳ�ƥ��
    [13]pkt_parse_err���ݽ�������ָʾ��0��ʾ���ݽ���������1��ʾ���ݽ�������
    [12]bd_pkt_noeqBD��len��IP��ͷָʾ��len���ȴ���ָʾ��0��ʾ����ƥ�䣬1��ʾ���Ȳ�ƥ��
    [11]head_len_err IPV4���ȴ���ָʾ�źţ�IPV6����鳤�ȣ�0��ʾͷ������ȷ��1��ʾͷ���ȴ���
    [10]version_err�汾�Ŵ���ָʾ��0��ʾ�汾����4��6��1��ʾ�汾�Ų���4��6
    [9]ip_type IP�����ͣ�0��ʾIPV4��1��ʾIPV6
    [8]ff_type��Ƭ����һ����Ƭ�Ƿ�����ϲ�ͷָʾ��0��ʾ��Ƭ����һ����Ƭ�����ϲ�ͷ(IP��δ��ƬʱҲΪ0)
     1��ʾ��Ƭ����һ����Ƭ�����ϲ�ͷ
    [7:6]pf_type IP����Ƭָʾ���ͣ�00��ʾIP��δ��Ƭ��01��ʾIP����Ƭ����Ϊ��һ����Ƭ��
       02��ʾ��Ƭ����Ϊ���һ����Ƭ��03��ʾ��Ƭ����Ϊ�м��Ƭ
    [0:5]bear_id���غţ����Ϊ0x3F�������й�������ƥ��
    */

    /*
    IPF_RD_DESC_S��user field����
    u16UsrField1: RabId
    u32UsrField2: Ŀ��TTF_MEM_STָ��
    u32UsrField3: ԴTTF_MEM_STָ��
    */

    /* ��ȡRD */
    pstRdDesc = ADS_DL_GET_IPF_RD_BUFFER_PTR(0);
    mdrv_ipf_get_dlrd(&ulRdNum, pstRdDesc);

    /* ��ȡ��RDΪ0 */
    if (0 == ulRdNum)
    {
        /* ����RD��ȡ����Ϊ0��ͳ�Ƹ��� */
        ADS_DBG_DL_RECV_RD_ZERO_NUM(1);
        return;
    }

#if (FEATURE_OFF == FEATURE_LTE)
    mdrv_wdt_feed(0);
#endif

    /* ����RDͳ�Ƹ��� */
    ADS_DBG_DL_RECV_RD_NUM(ulRdNum);

    /* ׷�����н������� */
    ADS_MNTN_TraceRcvDlData();

    /* ����Ƿ���Ҫ��������������� */
    if (VOS_TRUE == ADS_DL_IsFcAssemTuneNeeded(ulRdNum))
    {
        pFcAssemTuneFunc = ADS_DL_GET_FC_ASSEM_TUNE_FUNC(0);
        pFcAssemTuneFunc();
    }

    /* ������AD���ٴ���RD */
    ADS_DL_ProcAdq();

    for (ulCnt = 0; ulCnt < ulRdNum; ulCnt++)
    {
        pstRdDesc  = ADS_DL_GET_IPF_RD_BUFFER_PTR(ulCnt);
        pstIpfRslt = (ADS_DL_IPF_RESULT_STRU*)&(pstRdDesc->u16Result);

        pstImmZc = (IMM_ZC_STRU *)ADS_DL_GET_DATA_FROM_IPF_OUT(pstRdDesc->u32OutPtr);
#ifdef CONFIG_ARM64
        ADS_CACHE_INVALIDATE_WITH_DEV(&dev, pstImmZc->data - ADS_DL_AD_DATA_PTR_OFFSET, pstRdDesc->u16PktLen + ADS_DL_AD_DATA_PTR_OFFSET);
#else
        ADS_CACHE_INVALIDATE(pstImmZc->data - ADS_DL_AD_DATA_PTR_OFFSET, pstRdDesc->u16PktLen + ADS_DL_AD_DATA_PTR_OFFSET);
#endif /* CONFIG_ARM64 */

        /* �ӿ��޸ĺ󣬻�ȡ��ֵ */
        ucInstanceIndex = (VOS_UINT8)ADS_DL_GET_MODEM_ID_FROM_RD_USER_FIELD1(pstRdDesc->u16UsrField1);

        /* ͳ�������������յ��������ֽ���������������ѯ */
        ADS_RECV_DL_PERIOD_PKT_NUM(ucInstanceIndex, ADS_DL_GET_LEN_FROM_IPF_PKT_LEN(pstRdDesc->u16PktLen));

        /* BearId 0x3F: �����������ݰ���Ҫת����NDIS/PPP/RNIC*/
        if (CDS_ADS_DL_IPF_BEARER_ID_INVALID == pstIpfRslt->usBearedId)
        {
            if (ADS_DL_IPF_RD_RSLT_IS_ERR_PKT(pstRdDesc->u16Result))
            {
                ADS_DBG_DL_IPF_ERR_PKT_NUM(ucInstanceIndex, 1);
            }

            ulRxTimeout = ADS_DL_RX_WAKE_LOCK_TMR_LEN;
            ADS_DL_ProcRd(pstRdDesc);
        }
        /* BearId 19: NDClient������Ҫת����NDClient */
        else if (CDS_ADS_DL_IPF_BEARER_ID_ICMPV6 == pstIpfRslt->usBearedId)
        {
            /* ����ͳ�Ƽ��� */
            ADS_DBG_DL_RECV_NDCLIENT_PKT_NUM(ucInstanceIndex, 1);

            ADS_DL_SendNdClientDataInd(pstRdDesc);

            ADS_DL_FreeRd(pstRdDesc);
        }
        /* BearId 17: DHCPv6������Ҫת����DHCP */
        else if (CDS_ADS_DL_IPF_BEARER_ID_DHCPV6 == pstIpfRslt->usBearedId)
        {
            /* ����ͳ�Ƽ��� */
            ADS_DBG_DL_RECV_DHCPV4V6_PKT_NUM(ucInstanceIndex, 1);

            ADS_DL_SendDhcpDataInd(pstRdDesc);

            ADS_DL_FreeRd(pstRdDesc);
        }
        /* [0,4]��[5,15]����Ϊ�Ƿ����ݰ�; [16,17,18,20,21]Ŀǰֱ���ͷ� */
        else
        {
            /* ����ͳ�Ƽ��� */
            ADS_DBG_DL_RABID_ERR_PKT_NUM(ucInstanceIndex, 1);

            ADS_DL_FreeRd(pstRdDesc);
        }
    }

    for (ucRabId = ADS_RAB_ID_MIN; ucRabId < ADS_RAB_ID_MAX; ucRabId++)
    {
        ADS_DL_Xmit(ucRabId, ucInstanceIndex, 0, VOS_NULL_PTR);
    }

    ADS_DL_EnableRxWakeLockTimeout(ulRxTimeout);
    return;
}
VOS_UINT32 ADS_DL_IsFcAssemTuneNeeded(VOS_UINT32 ulRdNum)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemInfo;
    VOS_UINT32                          ulRslt = VOS_FALSE;

    /* ��ȡ������ֵ���� */
    pstFcAssemInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    if (0 != pstFcAssemInfo->ulEnableMask)
    {
        pstFcAssemInfo->ulRdCnt += ulRdNum;

        if (ADS_TIME_AFTER_EQ(ADS_GET_CURR_KERNEL_TIME(), (pstFcAssemInfo->ulTmrCnt + pstFcAssemInfo->ulExpireTmrLen)))
        {
            if (VOS_FALSE == pstFcAssemInfo->ulFcActiveFlg)
            {
                if (pstFcAssemInfo->ulRdCnt >= pstFcAssemInfo->ulRateUpLev)
                {
                    ADS_DBG_DL_FC_ACTIVATE_NUM(1);
                    pstFcAssemInfo->ulFcActiveFlg = VOS_TRUE;
                    ulRslt = VOS_TRUE;
                }
            }
            else
            {
                if (pstFcAssemInfo->ulRdCnt <= pstFcAssemInfo->ulRateDownLev)
                {
                    pstFcAssemInfo->ulFcActiveFlg = VOS_FALSE;
                }
            }

            ADS_DBG_DL_FC_TMR_EXP_NUM(1);
            pstFcAssemInfo->ulTmrCnt = ADS_GET_CURR_KERNEL_TIME();
            pstFcAssemInfo->ulRdCnt = 0;
        }
    }

    return ulRslt;
}
VOS_VOID ADS_DL_RegDrvAssemFunc(FC_ADS_DRV_ASSEM_STRU *pstDrvAssemParam)
{
    ADS_DL_FC_ASSEM_STRU               *pstFcAssemParamInfo;

    pstFcAssemParamInfo = ADS_DL_GET_FC_ASSEM_INFO_PTR(ADS_INSTANCE_INDEX_0);

    pstFcAssemParamInfo->ulEnableMask     = pstDrvAssemParam->ucEnableMask;
    pstFcAssemParamInfo->ulRateUpLev      = pstDrvAssemParam->ulDlRateUpLev;
    pstFcAssemParamInfo->ulRateDownLev    = pstDrvAssemParam->ulDlRateDownLev;
    pstFcAssemParamInfo->ulExpireTmrLen   = pstDrvAssemParam->ulExpireTmrLen;
    pstFcAssemParamInfo->pFcAssemTuneFunc = pstDrvAssemParam->pDrvAssemFunc;

    return;
}


VOS_UINT32 ADS_DL_RegDlDataCallback(
    VOS_UINT8                           ucRabId,
    RCV_DL_DATA_FUNC                    pFunc)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (VOS_OK != ADS_IsValidRabId(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegDlDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* ����ADS�������ݻص����� */
    pstDlRabInfo->ucRabId        = ucRealRabId;
    pstDlRabInfo->pRcvDlDataFunc = pFunc;

    return VOS_OK;
}
VOS_UINT32 ADS_DL_RegFilterDataCallback(
    VOS_UINT8                           ucRabId,
    ADS_FILTER_IP_ADDR_INFO_STRU       *pstFilterIpAddr,
    RCV_DL_DATA_FUNC                    pFunc
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (!ADS_IS_VALID_RABID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RegFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* ����ADS�������ݹ��˻ص����� */
    pstDlRabInfo->ucRabId               = ucRealRabId;
    pstDlRabInfo->pRcvDlFilterDataFunc  = pFunc;

    /* ������˵�ַ��Ϣ */
    ADS_FILTER_SaveIPAddrInfo(pstFilterIpAddr);

    return VOS_OK;
}


VOS_UINT32 ADS_DL_DeregFilterDataCallback(VOS_UINT8 ucRabId)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo        = VOS_NULL_PTR;
    VOS_UINT8                           ucInstanceIndex;
    VOS_UINT8                           ucRealRabId;

    /* ucRabId�ĸ�2��bit��ʾmodem id*/
    ucInstanceIndex = ADS_GET_MODEM_ID_FROM_EX_RAB_ID(ucRabId);
    ucRealRabId     = ADS_GET_RAB_ID_FROM_EX_RAB_ID(ucRabId);

    /* RabId�Ϸ��Լ�� */
    if (!ADS_IS_VALID_RABID(ucRealRabId))
    {
        ADS_WARNING_LOG1(ACPU_PID_ADS_DL, "ADS_DL_DeregFilterDataCallback: ucRabId is", ucRealRabId);
        return VOS_ERR;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRealRabId);

    /* ȥע��ADS�������ݹ��˻ص����� */
    pstDlRabInfo->pRcvDlFilterDataFunc  = VOS_NULL_PTR;

    /* ���������Ϣ */
    ADS_FILTER_Reset();

    return VOS_OK;
}


VOS_UINT32 ADS_DL_ProcPdpStatusInd(
    MODEM_ID_ENUM_UINT16                enModemId,
    VOS_UINT8                           ucRabId,
    ADS_PDP_STATUS_ENUM_UINT8           enPdpStatus,
    ADS_QCI_TYPE_ENUM_UINT8             enQciType,
    ADS_PDP_TYPE_ENUM_UINT8             enPdpType
)
{
    ADS_DL_RAB_INFO_STRU               *pstDlRabInfo;
    VOS_UINT8                           ucInstanceIndex;
    ADS_CDS_IPF_PKT_TYPE_ENUM_UINT8     enPktType;

    enPktType      = ADS_CDS_IPF_PKT_TYPE_IP;

    ucInstanceIndex = (VOS_UINT8)enModemId;

    /* RabId�Ϸ��Լ�� */
    if (VOS_OK != ADS_IsValidRabId(ucRabId))
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_ProcPdpStatusInd: Rab Id is invalid");

        return VOS_ERR;
    }

    if (ADS_PDP_PPP == enPdpType)
    {
        enPktType = ADS_CDS_IPF_PKT_TYPE_PPP;
    }

    pstDlRabInfo = ADS_DL_GET_RAB_INFO_PTR(ucInstanceIndex, ucRabId);

    /* PDP���� */
    if (ADS_PDP_STATUS_ACT == enPdpStatus)
    {
        /* ����ADS�������ݻص���RABID */
        pstDlRabInfo->ucRabId        = ucRabId;
        pstDlRabInfo->enPktType      = enPktType;
    }
    /* PDPȥ����  */
    else if (ADS_PDP_STATUS_DEACT == enPdpStatus)
    {
        /* ���ADS�������ݻص����� */
        pstDlRabInfo->ucRabId        = ADS_RAB_ID_INVALID;
        pstDlRabInfo->pRcvDlDataFunc = VOS_NULL_PTR;
    }
    else
    {
        ADS_ERROR_LOG(ACPU_PID_ADS_DL, "ADS_DL_ProcPdpStatusInd: Pdp Status is invalid");
    }

    return VOS_OK;
}
VOS_UINT32 ADS_DL_RcvTafPdpStatusInd(MsgBlock *pMsg)
{
    ADS_PDP_STATUS_IND_STRU            *pstPdpStatusInd;
    VOS_UINT32                          ulRslt;

    pstPdpStatusInd = (ADS_PDP_STATUS_IND_STRU *)pMsg;

    ulRslt = ADS_DL_ProcPdpStatusInd(pstPdpStatusInd->enModemId,
                                     pstPdpStatusInd->ucRabId,
                                     pstPdpStatusInd->enPdpStatus,
                                     pstPdpStatusInd->enQciType,
                                     pstPdpStatusInd->enPdpType);

    return ulRslt;
}



VOS_UINT32 ADS_DL_RcvCcpuResetStartInd(
    MsgBlock                           *pstMsg
)
{
    VOS_UINT8                           ucIndex;
#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n ADS_DL_RcvCcpuResetStartInd enter, %u \n", VOS_GetSlice());
#endif

    /* ֹͣ���������Ķ�ʱ�� */
    for (ucIndex = 0; ucIndex < ADS_MAX_TIMER_NUM; ucIndex++)
    {
        ADS_StopTimer(ACPU_PID_ADS_DL, ucIndex, ADS_TIMER_STOP_CAUSE_USER);
    }

    /* �������������� */
    ADS_ResetDlCtx();

    /* ��ֹIPF���ݲ���, ������ȡһ��RD */
    ADS_DL_WakeLock();
    ADS_DL_ProcIpfResult();
    ADS_DL_WakeUnLock();
    ADS_DBG_DL_PROC_RD_EVENT_NUM(1);

    /* �ͷ�IPF��AD */
    ADS_DL_FreeIpfUsedAd1();
    ADS_DL_FreeIpfUsedAd0();

    /* �ͷ��ź�����ʹ�õ���API����������� */
    VOS_SmV(ADS_GetDLResetSem());

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n ADS_DL_RcvCcpuResetStartInd leave, %u \n", VOS_GetSlice());
#endif
    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCcpuResetEndInd(
    MsgBlock                           *pstMsg
)
{
#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n ADS_DL_RcvCcpuResetEndInd enter, %u \n", VOS_GetSlice());
#endif

    /* ���õ�����Ϣ */
    ADS_ResetDebugInfo();

    /* ��λIPF */
    mdrv_ipf_reinit_dlreg();

    /* ���³�ʼ��ADQ */
    ADS_DL_InitAdq();

#if (VOS_OS_VER == VOS_LINUX)
    printk(KERN_ERR "\n ADS_DL_RcvCcpuResetEndInd leave, %u \n", VOS_GetSlice());
#endif
    return VOS_OK;
}
VOS_UINT32 ADS_DL_RcvTafMsg(MsgBlock* pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_APS_ADS_PDP_STATUS_IND:
            ADS_DL_RcvTafPdpStatusInd(pMsg);
            break;

        default:
            break;
    }

    return VOS_OK;
}


VOS_UINT32 ADS_DL_RcvCdsMsg(MsgBlock *pMsg)
{
    /* ��ʱû��Ҫ�������Ϣ������յ���Ϣ�����д��� */
    return VOS_ERR;
}
VOS_UINT32 ADS_DL_RcvAdsDlMsg(MsgBlock *pMsg)
{
    MSG_HEADER_STRU                    *pstMsg;

    pstMsg = (MSG_HEADER_STRU*)pMsg;

    switch(pstMsg->ulMsgName)
    {
        case ID_ADS_CCPU_RESET_START_IND:
            ADS_DL_RcvCcpuResetStartInd(pMsg);
            break;

        case ID_ADS_CCPU_RESET_END_IND:
            ADS_DL_RcvCcpuResetEndInd(pMsg);
            break;

        default:
            ADS_NORMAL_LOG1(ACPU_PID_ADS_DL, "ADS_DL_RcvAdsDlMsg: rcv error msg id %d\r\n", pstMsg->ulMsgName);
            break;
    }

    return VOS_OK;
}


VOS_VOID ADS_DL_ProcMsg(MsgBlock* pMsg)
{
    if (VOS_NULL_PTR == pMsg)
    {
        return;
    }

    /* ��Ϣ�ķַ����� */
    switch ( pMsg->ulSenderPid )
    {
        /* ����APS����Ϣ */
        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:
            ADS_DL_RcvTafMsg(pMsg);
            return;

        /* ����CDS����Ϣ */
        case UEPS_PID_CDS:
            ADS_DL_RcvCdsMsg(pMsg);
            return;

        /* ����ADS DL����Ϣ */
        case ACPU_PID_ADS_DL:
            ADS_DL_RcvAdsDlMsg(pMsg);
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

