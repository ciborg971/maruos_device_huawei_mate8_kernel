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

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID                 PS_FILE_ID_ADS_DEBUG_C
/*lint +e767*/


/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "AdsDebug.h"
#include "AdsCtx.h"
#include "vos.h"
#include "v_timer.h"

#define ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD   (5000000)
#define ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD   (500000)

/*****************************************************************************
  2 �ⲿ��������
*****************************************************************************/

/******************************************************************************
   3 ˽�ж���
******************************************************************************/


/******************************************************************************
   4 ȫ�ֱ�������
******************************************************************************/
ADS_STATS_INFO_STRU                     g_stAdsStats;
VOS_UINT32                              g_ulAdsLatencySwitch = 0;
VOS_UINT32                              g_ulAdsDebugFlg = VOS_FALSE;

HTIMER                                  g_pDebugRdhTimer;
VOS_UINT32                              g_ulDebugCurRdIntNum;
VOS_UINT32                              g_ulDebugCurRdNum;
RCV_DL_DATA_FUNC                        g_pDebugRcvFunc = VOS_NULL_PTR;

VOS_UINT32                              g_ulAdsPrintUlDataFlg = VOS_FALSE;

/******************************************************************************
   5 ����ʵ��
******************************************************************************/
VOS_VOID ADS_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulAdsPrintUlDataFlg = ulFlg;
}

VOS_VOID ADS_Debug(VOS_VOID)
{
    vos_printf("ADS_Debug 5\r\n");
}
VOS_VOID ADS_RecordRcvFunc(VOS_UINT8 ucRabId)
{
    /* ��¼���н��պ��� */
    g_pDebugRcvFunc = ADS_DL_GET_DATA_CALLBACK_FUNC(0, ucRabId);
    vos_printf("ADS_RecordRcvFunc:g_TestRcvFunc is %d\r\n", g_pDebugRcvFunc);
}

VOS_VOID ADS_ResumeRcvFunc(VOS_UINT8 ucRabId)
{
    vos_printf("ADS_ResumeRcvFunc:\r\n");
    ADS_DL_RegDlDataCallback(ucRabId, g_pDebugRcvFunc);
}
VOS_VOID ADS_SetEmptyRcvFunc(VOS_UINT8 ucRabId)
{
    vos_printf("ADS_SetEmptyRcvFunc:\r\n");
    ADS_DL_RegDlDataCallback(ucRabId, VOS_NULL_PTR);
}

VOS_VOID ADS_Debug_DL_RdNum(VOS_VOID)
{
    VOS_UINT32                          ulRd;
    ulRd = mdrv_ipf_get_dlrd_num();

    vos_printf("ADS_Debug_DL_RdNum: ulRd is %d\r\n", ulRd);
}

VOS_VOID ADS_Debug_DL_ProtectedTi(VOS_VOID)
{
    vos_printf("ADS_Debug_DL_ProtectedTi\r\n");
    ADS_DL_StartProtectTimer();
}

VOS_VOID ADS_Debug_RcvTiRDIntEventExpired(
    VOS_UINT32                          ulParam,
    VOS_UINT32                          ulTimerName
)
{
    VOS_UINT32                          ulNum;
    ulNum = g_stAdsStats.stDlComStatsInfo.ulDlRecvIPFBreakNum - g_ulDebugCurRdIntNum;
    vos_printf("ADS_DL_RcvTiRDIntEventExpired rd INT num is %d\r\n", ulNum);
    ulNum = g_stAdsStats.stDlComStatsInfo.ulDlRecvRDNum - g_ulDebugCurRdNum;
    vos_printf("ADS_DL_RcvTiRDIntEventExpired rd num is %d\r\n", ulNum);
}
VOS_VOID ADS_Debug_RD_Int_Event(VOS_UINT32 ulTiLen)
{
    g_ulDebugCurRdIntNum = g_stAdsStats.stDlComStatsInfo.ulDlRecvIPFBreakNum;
    g_ulDebugCurRdNum    = g_stAdsStats.stDlComStatsInfo.ulDlRecvRDNum;

    VOS_StartCallBackRelTimer(&g_pDebugRdhTimer,
                              ACPU_PID_ADS_DL,
                              ulTiLen,
                              TI_ADS_TIMER_BUTT,
                              0,
                              VOS_RELTIMER_NOLOOP,
                              ADS_Debug_RcvTiRDIntEventExpired,
                              VOS_TIMER_NO_PRECISION);
}

VOS_VOID ADS_ShowPeriodPktNum(VOS_VOID)
{
    vos_printf("ADS_ShowPeriodPktNum Cur DL PeriodPktNum is %d\r\n", g_stAdsCtx.astAdsSpecCtx[0].stAdsStatsInfoCtx.stDLDataStats.ulDLCurDataRate);
    vos_printf("ADS_ShowPeriodPktNum Cur UL PeriodPktNum is %d\r\n", g_stAdsCtx.astAdsSpecCtx[0].stAdsStatsInfoCtx.stULDataStats.ulULCurDataRate);
}
VOS_VOID ADS_SetTxWakeLockTmrLen(VOS_UINT32 ulValue)
{
    g_stAdsCtx.stAdsIpfCtx.ulTxWakeLockTmrLen = ulValue;
    return;
}


VOS_VOID ADS_SetRxWakeLockTmrLen(VOS_UINT32 ulValue)
{
    g_stAdsCtx.stAdsIpfCtx.ulRxWakeLockTmrLen = ulValue;
    return;
}


VOS_VOID ADS_ShowEntityStats(VOS_VOID)
{
    VOS_UINT8                           i;
    VOS_UINT8                           j;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        vos_printf("ADS Modem i                              %d\n", i);

        for (j = ADS_RAB_ID_MIN; j <= ADS_RAB_ID_MAX; j++)
        {
            if (VOS_NULL_PTR != g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink)
            {
                vos_printf("ADS Queue length is %d\n", IMM_ZcQueueLen(g_stAdsCtx.astAdsSpecCtx[i].stAdsUlCtx.astAdsUlQueue[j].pstAdsUlLink));
            }

            vos_printf("ADS DL RabId is %d\r\n", g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.astAdsDlRabInfo[j - ADS_RAB_ID_OFFSET].ucRabId);
            vos_printf("ADS DL Rcv Func is 0x%x\r\n", g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.astAdsDlRabInfo[j - ADS_RAB_ID_OFFSET].pRcvDlDataFunc);
        }
    }

    vos_printf("ADS�������ڷ��ͱ�ʶ                             %d\n",g_stAdsCtx.stAdsIpfCtx.ucSendingFlg);
    vos_printf("\r\n");

    return;
}


VOS_VOID ADS_ShowULProcStats(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        vos_printf("********************ADS����ͳ����Ϣ, Instance is %d************************\n", i);
        vos_printf("ADS�յ��������ݵĸ���                           %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulUlRecvPktNum);

        g_stAdsStats.astAdsSpecStatsInfo[i].ulUlSaveBuffPktNum = ADS_UL_GetInstanceAllQueueDataNum(i);

        vos_printf("ADS���л��������ݰ��ĸ���                       %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulUlSaveBuffPktNum);
        vos_printf("ADS�������ʧ�ܵĴ���                           %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulUlEnQueFail);
    }

    vos_printf("********************ADS����ͳ����Ϣ, Common************************\n");
    vos_printf("��������IPFû�л��BD/CD����                    %d\n",g_stAdsStats.stUlComStatsInfo.ulUlCfgIpfHaveNoBDCD);
    vos_printf("ADS�������а�����                               %d\n",g_stAdsStats.stUlComStatsInfo.ulUlSendBuffPktNum);
    vos_printf("ADS���������¼�����                             %d\n",g_stAdsStats.stUlComStatsInfo.ulUlProcEventNum);

    vos_printf("���б���Դ�ڴ�fail����                          %d\n",g_stAdsStats.stUlComStatsInfo.ulUlIpfSaveSrcMemFail);
    vos_printf("���б���Դ�ڴ�succ����                          %d\n",g_stAdsStats.stUlComStatsInfo.ulUlIpfSaveSrcMemSucc);
    vos_printf("�����ͷ�Դ�ڴ����                              %d\n",g_stAdsStats.stUlComStatsInfo.ulUlIpfFreeSrcMemNum);
    vos_printf("�����ͷ��ڴ����                                %d\n",g_stAdsStats.stUlComStatsInfo.ulUlIpfFreeSrcMemErr);
    vos_printf("���г������г��ȣ���������                      %d\n",g_stAdsStats.stUlComStatsInfo.ulUlDroppedPacketNum);

    vos_printf("����ˮ�߽߱�1���ô���                           %d\n",g_stAdsStats.stUlComStatsInfo.ulLevelOneCnt);
    vos_printf("����ˮ�߽߱�2���ô���                           %d\n",g_stAdsStats.stUlComStatsInfo.ulLevelTwoCnt);
    vos_printf("����ˮ�߽߱�3���ô���                           %d\n",g_stAdsStats.stUlComStatsInfo.ulLevelThreeCnt);
    vos_printf("����ˮ�߽߱�4���ô���                           %d\n",g_stAdsStats.stUlComStatsInfo.ulLevelFourCnt);

    vos_printf("�����ް�����1                                   %d\n",g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold1);
    vos_printf("�����ް�����2                                   %d\n",g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold2);
    vos_printf("�����ް�����3                                   %d\n",g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold3);
    vos_printf("�����ް�����4                                   %d\n",g_stAdsCtx.stAdsIpfCtx.stUlAssemParmInfo.stThresholdLevel.ulThreshold4);
    vos_printf("��ǰ�ް�����ֵ                                  %d\n",g_stAdsCtx.stAdsIpfCtx.ulThredHoldNum);



    vos_printf("\r\n");

    return;
}


VOS_VOID ADS_ShowDLProcStats(VOS_VOID)
{
    VOS_UINT8                           i;

    /*GUģ����ͳ����*/
    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        vos_printf("********************ADS����ͳ����Ϣ, Instance is %d************************\n", i);
        vos_printf("ADS���͸�APP���ݵĸ���                          %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlSendPktNum);
        vos_printf("IPF���˴��������                               %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlIPFErrNum);
        vos_printf("��ȡ������MTU��IPV6������                       %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlIpv6BigPktum);
        vos_printf("RAB ID��������ݰ��ĸ���                        %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRabIdErrPktum);
        vos_printf("��Ҫת����NDClient���ݰ��ĸ���                  %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvNDClintPktum);
        vos_printf("�յ�DHCPV4V6��Ŀǰδ����İ�                    %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvDHCPV4V6Pktum);
        vos_printf("�յ�IPV6LinkLocalAddress ���ݸ���               %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlRecvIPV6LinkLocalAddressPktum);
        vos_printf("ת��IMMZCʧ�ܵĴ���                             %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlTransformImmZcErr);
        vos_printf("ADS�����ͷ��ڴ�Ĵ���                           %d\n",g_stAdsStats.astAdsSpecStatsInfo[i].ulDlFreeNum);
#if 0
        vos_printf("ADS��������ʹ�ܱ�ʶ                             %d\n",g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.stFcAssemInfo.ulEnableMask);
        vos_printf("ADS��������������ֵ                             %d\n",g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.stFcAssemInfo.ulRateUpLev);
        vos_printf("ADS�������ؽ����ֵ                             %d\n",g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.stFcAssemInfo.ulRateDownLev);
        vos_printf("ADS��������RD����ͳ������(ms)                   %d\n",g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.stFcAssemInfo.ulExpireTmrLen);
        vos_printf("ADS�������ؼ����ʶ                             %d\n",g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.stFcAssemInfo.ulFcActiveFlg);
        vos_printf("ADS��������ʱ�����                             %d\n",g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.stFcAssemInfo.ulTmrCnt);
        vos_printf("ADS��������RD����                               %d\n",g_stAdsCtx.astAdsSpecCtx[i].stAdsDlCtx.stFcAssemInfo.ulRdCnt);
#endif
    }

    vos_printf("********************ADS����ͳ����Ϣ, Common************************\n");
    vos_printf("ADS���л�ȡRD�ĸ���                             %d\n",g_stAdsStats.stDlComStatsInfo.ulDlRecvRDNum);
    vos_printf("ADS���л�ȡRDΪ0�Ĵ���                          %d\n",g_stAdsStats.stDlComStatsInfo.ulDlRecvRDZeroNum);
    vos_printf("ADS�����յ�IPF�жϵĴ���                        %d\n",g_stAdsStats.stDlComStatsInfo.ulDlRecvIPFBreakNum);
    vos_printf("ADS���п��жϴ���                               %d\n",g_stAdsStats.stDlComStatsInfo.ulDlRecvAdqEmptyBreakNum);
    vos_printf("ADS����ADQ0Ϊ�յĴ���                           %d\n",g_stAdsStats.stDlComStatsInfo.aulDlGetAdqEmptyNum[IPF_EMPTY_ADQ0] + g_stAdsStats.stDlComStatsInfo.aulDlGetAdqEmptyNum[IPF_EMPTY_ADQ]);
    vos_printf("ADS����ADQ1Ϊ�յĴ���                           %d\n",g_stAdsStats.stDlComStatsInfo.aulDlGetAdqEmptyNum[IPF_EMPTY_ADQ1] + g_stAdsStats.stDlComStatsInfo.aulDlGetAdqEmptyNum[IPF_EMPTY_ADQ]);
    vos_printf("ADS����ADQ�ձ�����ʱ����������                  %d\n",g_stAdsStats.stDlComStatsInfo.ulDlAdqStartEmptyTmrNum);
    vos_printf("ADS����ADQ�ձ�����ʱ����ʱ����                  %d\n",g_stAdsStats.stDlComStatsInfo.ulDlAdqEmptyTmrTimeoutNum);
    vos_printf("ADS��������ALL�¼�����                          %d\n",g_stAdsStats.stDlComStatsInfo.ulDlAllEvent);
    vos_printf("ADS��������RD�¼�����                           %d\n",g_stAdsStats.stDlComStatsInfo.ulDlRdEventNum);
    vos_printf("ADS��������ADQ EMPTY�¼�����                    %d\n",g_stAdsStats.stDlComStatsInfo.ulDlAdEmptyNum);
    vos_printf("ADS��������EMPTY�¼�����                        %d\n",g_stAdsStats.stDlComStatsInfo.ulDlEmptyEvent);

    vos_printf("ADS���л�ȡADʧ�ܴ���                           %d\n",g_stAdsStats.stDlComStatsInfo.ulDlGetAdFailNum);
    vos_printf("ADS��������AD0�ɹ�����                          %d\n",g_stAdsStats.stDlComStatsInfo.aulDlConfigAdSuccNum[IPF_AD_0]);
    vos_printf("ADS��������AD1�ɹ�����                          %d\n",g_stAdsStats.stDlComStatsInfo.aulDlConfigAdSuccNum[IPF_AD_1]);
    vos_printf("ADS��������AD0ʧ�ܴ���                          %d\n",g_stAdsStats.stDlComStatsInfo.aulDlConfigAdFailNum[IPF_AD_0]);
    vos_printf("ADS��������AD1ʧ�ܴ���                          %d\n",g_stAdsStats.stDlComStatsInfo.aulDlConfigAdFailNum[IPF_AD_1]);
    vos_printf("ADS��������AD0�ɹ��Ĵ���                        %d\n",g_stAdsStats.stDlComStatsInfo.aulDlAllocAdSuccNum[IPF_AD_0]);
    vos_printf("ADS��������AD1�ɹ��Ĵ���                        %d\n",g_stAdsStats.stDlComStatsInfo.aulDlAllocAdSuccNum[IPF_AD_1]);
    vos_printf("ADS��������AD0ʧ�ܵĴ���                        %d\n",g_stAdsStats.stDlComStatsInfo.aulDlAllocAdFailNum[IPF_AD_0]);
    vos_printf("ADS��������AD1ʧ�ܵĴ���                        %d\n",g_stAdsStats.stDlComStatsInfo.aulDlAllocAdFailNum[IPF_AD_1]);

    vos_printf("ADS���б�����ʱ����ʱ����                       %d\n",g_stAdsStats.stDlComStatsInfo.ulDlRdTiProtectExpiredNum);
    vos_printf("ADS���б�����ʱ����ʱ�¼�����                   %d\n",g_stAdsStats.stDlComStatsInfo.ulDlRdProctectEventNum);

    vos_printf("ADS�������س�ʱ����                             %d\n",g_stAdsStats.stDlComStatsInfo.ulDlFcTmrExpiredCnt);
    vos_printf("ADS�������ؼ������                             %d\n",g_stAdsStats.stDlComStatsInfo.ulDlFcActivateCnt);

    vos_printf("\r\n");

    return;
}
VOS_VOID ADS_ShowResetStats(VOS_VOID)
{
    vos_printf("ģ���ʼ����ʶ                              %d\n", g_stAdsStats.stResetStatsinfo.ulSemInitFlg);
    vos_printf("��ǰ�����ж������ź���                      %p\n", g_stAdsCtx.hULResetSem);
    vos_printf("��ǰ�����ж������ź���                      %p\n", g_stAdsCtx.hDLResetSem);
    vos_printf("���������ж������ź���                      %x\n", g_stAdsStats.stResetStatsinfo.hULBinarySemId);
    vos_printf("���������ж������ź���                      %x\n", g_stAdsStats.stResetStatsinfo.hDLBinarySemId);
    vos_printf("�������ж������ź���ʧ�ܴ���                %d\n", g_stAdsStats.stResetStatsinfo.ulULCreateBinarySemFailNum);
    vos_printf("�������ж������ź���ʧ�ܴ���                %d\n", g_stAdsStats.stResetStatsinfo.ulDLCreateBinarySemFailNum);
    vos_printf("�����ж������ź���ʧ�ܴ���                  %d\n", g_stAdsStats.stResetStatsinfo.ulULLockBinarySemFailNum);
    vos_printf("�����ж������ź���ʧ�ܴ���                  %d\n", g_stAdsStats.stResetStatsinfo.ulDLLockBinarySemFailNum);
    vos_printf("���һ�������ж������ź���ʧ��ԭ��          %x\n", g_stAdsStats.stResetStatsinfo.ulULLastBinarySemErrRslt);
    vos_printf("���һ�������ж������ź���ʧ��ԭ��          %x\n", g_stAdsStats.stResetStatsinfo.ulDLLastBinarySemErrRslt);
    vos_printf("���и�λ�ɹ��Ĵ���                          %d\n", g_stAdsStats.stResetStatsinfo.ulULResetSucessNum);
    vos_printf("���и�λ�ɹ��Ĵ���                          %d\n", g_stAdsStats.stResetStatsinfo.ulDLResetSucessNum);
}

VOS_VOID ADS_Help(VOS_VOID)
{

    vos_printf("********************ADS�����Ϣ************************\n");
    vos_printf("ADS_ShowEntityStats                      ��ʾADSʵ����Ϣ\n");
    vos_printf("ADS_ShowULProcStats                      ��ʾADS����ͳ����Ϣ\n");
    vos_printf("ADS_ShowDLProcStats                      ��ʾADS����ͳ����Ϣ\n");
    vos_printf("ADS_ShowResetStats                       ��ʾADS��λ״̬��Ϣ\n");

    return;
}


VOS_VOID ADS_ResetDebugInfo(VOS_VOID)
{
    VOS_UINT8                           i;

    for (i = 0; i < ADS_INSTANCE_MAX_NUM; i++)
    {
        PS_MEM_SET(&g_stAdsStats.astAdsSpecStatsInfo[i], 0, sizeof(ADS_SPEC_STATS_INFO_STRU));
    }

    PS_MEM_SET(&g_stAdsStats.stUlComStatsInfo, 0 , sizeof(ADS_UL_COM_STATS_INFO_STRU));
    PS_MEM_SET(&g_stAdsStats.stDlComStatsInfo, 0 , sizeof(ADS_DL_COM_STATS_INFO_STRU));

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_MNTN_OpenLatency
 ��������  : �����û�������׷�ٹ켣
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��19��
    ��    ��   : huibo
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_MNTN_OpenLatency(VOS_VOID)
{
    g_ulAdsLatencySwitch = 1;

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_MNTN_CloseLatency
 ��������  : �ر��û�������׷�ٹ켣
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��19��
    ��    ��   : huibo
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_MNTN_CloseLatency(VOS_VOID)
{
    g_ulAdsLatencySwitch = 0;

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_MNTN_TraceRcvUlData
 ��������  : ׷���û������н�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��19��
    ��    ��   : huibo
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_MNTN_TraceRcvUlData(VOS_VOID)
{
    if (1 == g_ulAdsLatencySwitch)
    {
        ADS_LATENCY_LOG(ACPU_PID_ADS_UL, "User plane latency trace: ADS Rcv UL data");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_MNTN_TraceSndUlData
 ��������  : ׷���û������з�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��19��
    ��    ��   : huibo
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_MNTN_TraceSndUlData(VOS_VOID)
{
    if (1 == g_ulAdsLatencySwitch)
    {
        ADS_LATENCY_LOG(ACPU_PID_ADS_UL, "User plane latency trace: ADS Send UL data");
    }

    return;
}

/*****************************************************************************
 �� �� ��  : ADS_MNTN_TraceRcvDlData
 ��������  : ׷���û������н�������
 �������  : VOS_VOID
 �������  : ��
 �� �� ֵ  : VOS_VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2012��6��19��
    ��    ��   : huibo
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID ADS_MNTN_TraceRcvDlData(VOS_VOID)
{
    if (1 == g_ulAdsLatencySwitch)
    {
        ADS_LATENCY_LOG(ACPU_PID_ADS_DL, "User plane latency trace: ADS Rcv DL data");
    }

    return;
}


VOS_VOID ADS_LATENCY_OM_LOG( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                           VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                           const VOS_CHAR  *pcString )
{
#if 0
    #if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32          ulRslt = 0;

    ulRslt = DIAG_PrintfV(DIAG_ID( ulModuleId,ulLevel ), (VOS_CHAR*)pcFileName, ulLineNum, (VOS_CHAR*)("%s"), pcString);
    if (PS_SUCC != ulRslt)
    {
        return;
    }
    #endif
#endif
    return;
}


VOS_VOID ADS_SetFlowDebugFlag(VOS_UINT32  ulFlowDebugFlag)
{
    switch (ulFlowDebugFlag)
    {
        case ADS_FLOW_DEBUG_DL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            break;

        case ADS_FLOW_DEBUG_UL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        case ADS_FLOW_DEBUG_ALL_ON:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_TRUE;
            g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ADS_FLOW_DL_DEFAULT_RPT_THRESHOLD;
            g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ADS_FLOW_UL_DEFAULT_RPT_THRESHOLD;
            break;

        default:
            g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag     = PS_FALSE;
            g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag     = PS_FALSE;
            break;
    }

    return;
}


VOS_VOID ADS_SetFlowDLRptThreshold(VOS_UINT32  ulFlowDLRptThreshold)
{
    g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold  = ulFlowDLRptThreshold;
    return;
}


VOS_VOID ADS_SetFlowULRptThreshold(VOS_UINT32  ulFlowULRptThreshold)
{
    g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold  = ulFlowULRptThreshold;
    return;
}


VOS_VOID ADS_DLFlowAdd(VOS_UINT8  ucIndex, VOS_UINT32  ulSduLen)
{
    ADS_SPEC_STATS_INFO_STRU           *pstAdsSpecStatsInfo;

    if (PS_TRUE == g_stAdsStats.stDlComStatsInfo.ulDLFlowDebugFlag)
    {
        pstAdsSpecStatsInfo = &(g_stAdsStats.astAdsSpecStatsInfo[ucIndex]);

        /* ����ͳ�� */
        pstAdsSpecStatsInfo->ulDLFlowInfo += ulSduLen;

        /* ����ͳ���ϱ� */
        if (pstAdsSpecStatsInfo->ulDLFlowInfo >= g_stAdsStats.stDlComStatsInfo.ulDLFlowRptThreshold)
        {
            pstAdsSpecStatsInfo->ulDLEndSlice   = VOS_GetSlice();

            vos_printf("ADS Index = %d, DL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                ucIndex, pstAdsSpecStatsInfo->ulDLFlowInfo,
                pstAdsSpecStatsInfo->ulDlSendPktNum, pstAdsSpecStatsInfo->ulDLEndSlice,
                (pstAdsSpecStatsInfo->ulDLEndSlice - pstAdsSpecStatsInfo->ulDLStartSlice));

            pstAdsSpecStatsInfo->ulDLStartSlice = pstAdsSpecStatsInfo->ulDLEndSlice;
            pstAdsSpecStatsInfo->ulDLFlowInfo   = 0;
        }
    }

    return;
}


VOS_VOID ADS_ULFlowAdd(VOS_UINT8  ucIndex, VOS_UINT32  ulSduLen)
{
    ADS_SPEC_STATS_INFO_STRU           *pstAdsSpecStatsInfo;

    if (PS_TRUE == g_stAdsStats.stUlComStatsInfo.ulULFlowDebugFlag)
    {
        pstAdsSpecStatsInfo = &(g_stAdsStats.astAdsSpecStatsInfo[ucIndex]);

        /* ����ͳ�� */
        pstAdsSpecStatsInfo->ulULFlowInfo += ulSduLen;

        /* ����ͳ���ϱ� */
        if (pstAdsSpecStatsInfo->ulULFlowInfo >= g_stAdsStats.stUlComStatsInfo.ulULFlowRptThreshold)
        {
            pstAdsSpecStatsInfo->ulULEndSlice   = VOS_GetSlice();

            vos_printf("ADS Index = %d, UL Flow Info = %10d, Pkt Num = %10d, Slice = %10d, Time = %10d\n",
                ucIndex, pstAdsSpecStatsInfo->ulULFlowInfo,
                pstAdsSpecStatsInfo->ulUlRecvPktNum, pstAdsSpecStatsInfo->ulULEndSlice,
                (pstAdsSpecStatsInfo->ulULEndSlice - pstAdsSpecStatsInfo->ulULStartSlice));

            pstAdsSpecStatsInfo->ulULStartSlice = pstAdsSpecStatsInfo->ulULEndSlice;
            pstAdsSpecStatsInfo->ulULFlowInfo   = 0;
        }
    }

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


