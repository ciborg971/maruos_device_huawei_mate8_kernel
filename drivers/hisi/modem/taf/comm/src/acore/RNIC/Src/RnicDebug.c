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
  1 头文件包含
*****************************************************************************/
#include "RnicDebug.h"
#include "RnicCtx.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

/*****************************************************************************
  2 外部函数声明
*****************************************************************************/


/******************************************************************************
   3 私有定义
******************************************************************************/


/******************************************************************************
   4 全局变量定义
******************************************************************************/

RNIC_MNTN_STATS_STRU                    g_stRnicMntnStats = {0};
RNIC_STATS_INFO_STRU                    g_astRnicStats[RNIC_NET_ID_MAX_NUM];
RNIC_RMNET_CONFIG_CHECK_INFO_STRU       g_stRnicRmnetConfigCheckInfo;
VOS_UINT32                              g_ulRnicPrintUlDataFlg = VOS_FALSE;
VOS_UINT32                              g_ulRnicPrintDlDataFlg = VOS_FALSE;


/******************************************************************************
   5 函数实现
******************************************************************************/

VOS_VOID RNIC_SetPrintUlDataFlg(VOS_UINT32 ulFlg)
{
    g_ulRnicPrintUlDataFlg = ulFlg;
}


VOS_VOID RNIC_ShowRnicPdpStats(VOS_UINT8 ucRmNetId)
{
    RNIC_PDP_CTX_STRU                  *pstPdpCtx;

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowRnicPdpStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    pstPdpCtx                           = RNIC_GetPdpCtxAddr(ucRmNetId);

    vos_printf("RNIC %d IPV4 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV4 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV4 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV4 PDP IPV4ADDR                   %d\n\n", ucRmNetId, pstPdpCtx->stIpv4PdpInfo.ulIpv4Addr);

    vos_printf("RNIC %d IPV6 PDP STATUS                     %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV6 PDP RABID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV6 PDP PDNID                      %d\n",   ucRmNetId, pstPdpCtx->stIpv6PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV6 PDP IPV6ADDR                   %s\n\n", ucRmNetId, pstPdpCtx->stIpv6PdpInfo.aucIpv6Addr);

    vos_printf("RNIC %d IPV4V6 PDP STATUS                   %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.enRegStatus);
    vos_printf("RNIC %d IPV4V6 PDP RABID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucRabId);
    vos_printf("RNIC %d IPV4V6 PDP PDNID                    %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ucPdnId);
    vos_printf("RNIC %d IPV4V6 PDP IPV4ADDR                 %d\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.ulIpv4Addr);
    vos_printf("RNIC %d IPV4V6 PDP IPV6ADDR                 %s\n", ucRmNetId, pstPdpCtx->stIpv4v6PdpInfo.aucIpv6Addr);
}


VOS_VOID RNIC_ShowUlProcStats(VOS_UINT8 ucRmNetId)
{
    vos_printf("NET TX RMNETID ERR NUM                                 %d\n", g_stRnicMntnStats.ulNetTxRmNetIdErrNum);
    vos_printf("SPE TX PORTID ERR NUM                                  %d\n", g_stRnicMntnStats.ulSpeTxPortIdErrNum);

    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowUlProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* 上行统计量 */
    vos_printf("RNIC %d流控状态                                        %d\n", ucRmNetId, g_stRnicCtx.astSpecCtx[ucRmNetId].enFlowCtrlStatus);
    vos_printf("RNIC %d收到上行IPV4数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4PktNum);
    vos_printf("RNIC %d收到上行IPV6数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv6PktNum);
    vos_printf("IPV4V6类型激活时RNIC %d收到上行数据的个数IPV4IPV6      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvIpv4v6PktNum);
    vos_printf("RNIC %d未激活时收到上行数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvUndiaPktNum);
    vos_printf("RNIC %d上行发送给ADS数据的个数                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktNum);
    vos_printf("RNIC %d调ADS发送上行数据失败的个数                     %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendPktFailNum);
    vos_printf("RNIC %d未拨上号前上行收到IPV4广播包的个数              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlIpv4BrdcstPktNum);
    vos_printf("RNIC %d上行转换为IMM_ZC失败的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlImmzcFailPktNum);
    vos_printf("RNIC %d上行去除MAC头失败的个数                         %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRmvMacHdrFailPktNum);
    vos_printf("RNIC %d网卡私有数据错误丢掉上行数据包的个数            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetCardDiscardNum);
    vos_printf("RNIC %d网卡ID错误丢掉上行数据包的个数                  %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlNetIdDiscardNum);
    vos_printf("RNIC %dModem ID错误丢掉上行数据包的个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlModemIdDiscardNum);
    vos_printf("RNIC %d流控丢掉上行数据包的个数                        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlFlowCtrlDiscardNum);
    vos_printf("RNIC %d收到错误数据包的个数非ipv4ipv6包                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRecvErrPktNum);
    vos_printf("RNIC %d成功上报APP按需拨号                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpSucc);
    vos_printf("RNIC %d上报APP按需拨号失败                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialUpFail);
    vos_printf("RNIC %d成功上报APP断开拨号                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownSucc);
    vos_printf("RNIC %d上报APP断开拨号失败                             %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlSendAppDialDownFail);

    if (RNIC_RMNET_ID_0 == ucRmNetId)
    {
        vos_printf("拨号模式                                           %d\n", g_stRnicCtx.stDialMode.enDialMode);
        vos_printf("按需拨号是否上报事件                               %d\n", g_stRnicCtx.stDialMode.enEventReportFlag);
        vos_printf("按需拨号断开时间                                   %d\n", g_stRnicCtx.stDialMode.ulIdleTime);
    }

    vos_printf("RNIC %d RAB ID错误，RNIC丢弃的数据包个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlRabIdErr);
    vos_printf("RNIC %d PDN ID错误，RNIC丢弃的数据包个数                %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulUlPdnIdErr);

    vos_printf("\r\n");

    return;
}
VOS_VOID RNIC_ShowDLProcStats(VOS_UINT8 ucRmNetId)
{
    if (ucRmNetId >= RNIC_NET_ID_MAX_NUM)
    {
        vos_printf("RNIC_ShowDLProcStats: NetId overtop, ucRmNetId = %d\n", ucRmNetId);
        return;
    }

    /* 下行统计量 */
    vos_printf("RNIC %d收到下行IPV4数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv4PktNum);
    vos_printf("RNIC %d收到下行IPV6数据的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvIpv6PktNum);
    vos_printf("RNIC %d发送下行数据的个数                          %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktNum);
    vos_printf("RNIC %d发送下行数据失败的个数                      %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlSendPktFailNum);
    vos_printf("RNIC %d收到下行数据包大于MTU的个数                 %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvBigPktNum);
    vos_printf("RNIC %d网卡未激活丢弃的数据个数                    %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlDiscardPktNum);
    vos_printf("RNIC %d下行加MAC头失败的个数                       %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlAddMacHdFailNum);
    vos_printf("RNIC %d网卡私有数据错误丢掉下行数据包的个数        %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetCardDiscardNum);
    vos_printf("RNIC %d网卡ID错误丢掉下行数据包的个数              %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlNetIdDiscardNum);
    vos_printf("RNIC %d收到错误数据包的个数非ipv4ipv6包            %d\n", ucRmNetId, g_astRnicStats[ucRmNetId].ulDlRecvErrPktNum);
    vos_printf("\r\n");

    return;
}
VOS_VOID RNIC_ShowResetStats(VOS_VOID)
{
    vos_printf("模块初始化标识                              %d\n", g_astRnicStats[0].ulSemInitFlg);
    vos_printf("当前的二进制信号量                          %p\n", g_stRnicCtx.hResetSem);
    vos_printf("创建的二进制信号量                          %p\n", g_astRnicStats[0].hBinarySemId);
    vos_printf("创建二进制信号量失败次数                    %d\n", g_astRnicStats[0].ulCreateBinarySemFailNum);
    vos_printf("锁二进制信号量失败次数                      %d\n", g_astRnicStats[0].ulLockBinarySemFailNum);
    vos_printf("最后一次锁二进制信号量失败原因              %x\n", g_astRnicStats[0].ulLastBinarySemErrRslt);
    vos_printf("复位成功的次数                              %d\n", g_astRnicStats[0].ulResetSucessNum);
}


VOS_VOID RNIC_ShowRmnetConfigCheckInfo(VOS_VOID)
{
    vos_printf("Totla req                           %d\n", g_stRnicRmnetConfigCheckInfo.ucTotlaCnt);
    vos_printf("Modem type err                      %d\n", g_stRnicRmnetConfigCheckInfo.ucModemTypeErrCnt);
    vos_printf("Rmnet id err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucRmNetIdErrCnt);
    vos_printf("Modem ID err                        %d\n", g_stRnicRmnetConfigCheckInfo.ucModemIdErrCnt);
    vos_printf("Pdn ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucPdnIdErrCnt);
    vos_printf("Rab ID err                          %d\n", g_stRnicRmnetConfigCheckInfo.ucRabIdErrCnt);
    vos_printf("Rmnet status err                    %d\n", g_stRnicRmnetConfigCheckInfo.ucRmnetStatusErrCnt);
    vos_printf("IP type err                         %d\n", g_stRnicRmnetConfigCheckInfo.ucIpTypeErrCnt);
    vos_printf("Send err                            %d\n", g_stRnicRmnetConfigCheckInfo.ucSendErrCnt);
    vos_printf("Success                             %d\n", g_stRnicRmnetConfigCheckInfo.ucSuccCnt);
}


VOS_VOID RNIC_Help(VOS_VOID)
{

    vos_printf("********************RNIC调试信息************************\n");
    vos_printf("RNIC_ShowUlProcStats  ucRmNetId                 显示指定RNIC网卡上行统计信息\n");
    vos_printf("RNIC_ShowDLProcStats  ucRmNetId                 显示指定RNIC网卡下行统计信息\n");
    vos_printf("RNIC_ShowRnicPdpStats ucRmNetId                 显示指定RNIC网卡PDP激活信息\n");
    vos_printf("RNIC_ShowResetStats                             显示指定RNIC复位状态信息\n");

    return;
}


VOS_VOID RNIC_LATENCY_OM_LOG( const VOS_CHAR  *pcFileName,  VOS_UINT32  ulLineNum,
                           VOS_UINT32      ulModuleId,   VOS_UINT32 ulLevel,
                           const VOS_CHAR  *pcString )
{
#if 0
#if (FEATURE_ON == FEATURE_LTE)
    VOS_UINT32          ulRslt = 0;

    ulRslt = DIAG_PrintfV(DIAG_ID(ulModuleId, ulLevel), (VOS_CHAR*)pcFileName, ulLineNum, (VOS_CHAR*)("%s"), pcString);
    if (PS_SUCC != ulRslt)
    {
        return;
    }
#endif
#endif
    return;
}

/*****************************************************************************
 函 数 名  : RNIC_ShowDataFromIpStack
 功能描述  : 打印收到IP协议栈的数据
 输入参数  : pstSkb   :SKBUF数据首地址
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
 1.日    期   : 2013年04月25日
   作    者   : 范晶
   修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID RNIC_ShowDataFromIpStack(
    struct sk_buff                     *pstSkb
)
{
    VOS_UINT32                          i;

    vos_printf("RNIC_ShowDataFromIpStack: data len is %d. \r\n", pstSkb->len);

    vos_printf("RNIC_ShowDataFromIpStack: data content is: \r\n");

    for (i = 0; i < pstSkb->len; i++)
    {
        if (pstSkb->data[i] > 0xf)
        {
            vos_printf("%x", pstSkb->data[i]);
        }
        else
        {
            vos_printf("0%x", pstSkb->data[i]);
        }
    }

    vos_printf("\r\n");

    return;
}

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif



