

/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "ppp_inc.h"
#include "v_int.h"
#include "AtPppInterface.h"
#include "PppInterface.h"
#include "fwd_ppp.h"
#include "pppc_ctrl.h"
#include "taf_aps_ppp_pif.h"
#include "TTFLink.h"
#include "VosTaskPrioDef.h"
#include "NVIM_Interface.h"
#include "siapppih.h"
#include "pppc_pa_agent.h"
#include "CdsPppInterface.h"

#include "TTFMem.h"
#include "cttf_1x_rrlp_data_pif.h"
#include "ppp_trans_data_pif.h"
#include "rlp_ppp_pub_pif.h"
#include "cttf_1x_ppp_data_pif.h"
#include "cttf_hrpd_pa_public_pif.h"

#include "TtfNvInterface.h"

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
#include "hdlc_hardware.h"
#endif



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_PPPC_CTRL_C
/*lint +e767*/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/
/* PPP的上下文信息 */
PPPC_CONTEXT_INFO_STRU                  g_stPppContext;

/* 下行积攒的报文达到16个时需要触发向PPPC发送Notify消息 */
VOS_UINT32                              g_ulMaxPktTrigerNtf = 0;

/* APS消息链表,目前需要挂入链表的只有激活和去激活消息,收到本地去激活IND直接清除资源无需链表管理 */
TTF_LINK_ST                             g_stApsCmdLink;

/* PPP上下行队列从空到非空的通知消息计数 */
PPPC_DATA_Q_NOTIFY_CNT_STRU             g_stDataQNotifyCnt;

/* 存放进行PPP封装之后的CDS上行数据 */
VOS_UINT8                               g_aucUlEncapData[PPPC_MAX_UL_DATA_LEN];

PPPC_DATA_UL_ENCAP_MEM_STRU             g_astUlEncapMem[2];

/* PPPC处理次数达到门限之后跳出PPPC任务唤醒定时器 */
volatile HTIMER                         g_hReachMaxProcTimer = VOS_NULL_PTR;


/* PPP报文上行链表 */
TTF_LINK_ST                             g_stPppUlLink;

/* PPP报文下行链表 */
TTF_LINK_ST                             g_stPppDlLink;

/* 下行报文重组分片缓存链表 */
extern TTF_LINK_ST                      g_stPppRebuildIncompleteSliceLink;

/* PPPC的数据队列统计信息结构体 */
PPP_DATA_Q_STAT_STRU                    g_stPppcDataQueueStats;

/* 当PPPC处理次数达到门限时会跳出任务并启动定时器处理,此标志位表示定时器是否超时 */
PS_BOOL_ENUM_UINT8                      g_enIsReachTimeout = PS_TRUE;

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

VOS_VOID PPPC_ShowPppContext(VOS_VOID)
{
    vos_printf("********************PPPC测试信息************************\n");
    vos_printf("enRatMode:            %d\n", g_stPppContext.enRatMode);
    vos_printf("enDialMode:           %d\n", g_stPppContext.enDialMode);
    vos_printf("enRatMode:            %d\n", g_stPppContext.enModemId);
    vos_printf("ulSendPid:            %d\n", g_stPppContext.ulSendPid);
    vos_printf("usMtu:                %d\n", g_stPppContext.usMru);
    vos_printf("ulPppIdBitMask:       %d\n", g_stPppContext.ulPppIdBitMask);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ShowDLProcStats
 功能描述  : 获取PPP下行数据信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ShowDLProcStats(VOS_VOID)
{
    vos_printf("\n");
    vos_printf("********************PPPC下行数据信息************************\n");
    vos_printf("PPPC收到的下行数据包总个数:            %d\n",
                g_stPppcDataQueueStats.ul1xDlFrameRcvCnt + g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt);
    vos_printf("其中  1X模式收到的下行数据包总个数:    %d\n", g_stPppcDataQueueStats.ul1xDlFrameRcvCnt);
    vos_printf("            收到的下行协商报文个数:    %d\n", g_stPppcDataQueueStats.ul1xDlNegoRcvCnt);
    vos_printf("            发送的下行IP包个数:        %d\n", g_stPppcDataQueueStats.ul1xDlIPDataSndCnt);
    vos_printf("      HRPD模式收到的下行数据包总个数:  %d\n", g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt);
    vos_printf("            收到的下行协商报文个数:    %d\n", g_stPppcDataQueueStats.ulHrpdDlNegoRcvCnt);
    vos_printf("            发送的下行IP包个数:        %d\n", g_stPppcDataQueueStats.ulHrpdDlIPDataSndCnt);
    vos_printf("PPPC的存储下行数据链表的最大节点数:    %d\n", g_stPppcDataQueueStats.ulDlDataQMaxCnt);
    vos_printf("PPPC的下行数据链表的当前节点数:        %d\n", g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt);
    vos_printf("PPPC的下行数据入队数:                  %d\n", g_stPppcDataQueueStats.ulDlDataQEnqueueMsgCnt);
    vos_printf("PPPC的下行数据出队处理数:              %d\n", g_stPppcDataQueueStats.ulDlDataQProcMsgCnt);

    vos_printf("HDLC下行内存申请次数:                  %d\n", g_stPppcDataQueueStats.ulMemAllocDownlinkCnt);
    vos_printf("HDLC下行内存申请失败次数:              %d\n", g_stPppcDataQueueStats.ulMemAllocDownlinkFailCnt);
    vos_printf("HDLC硬件解封装IP包数:                  %d\n", g_stPppcDataQueueStats.ulDownlinkSndDataCnt);

    vos_printf("PPPC下行队列节点个数:                  %d\n", g_stPppDlLink.ulCnt);
    vos_printf("\n");

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ShowULProcStats
 功能描述  : 获取PPP上行数据信息
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年01月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ShowULProcStats(VOS_VOID)
{
    vos_printf("\n");
    vos_printf("************************************************************\n");
    vos_printf("****当前文件FILE ID*****[%d]\n", PS_FILE_ID_PPPC_CTRL_C);
    vos_printf("********************PPPC上行数据信息************************\n");
    vos_printf("PPPC收到的上行数据包总个数:            %d\n",
                g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt + g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt);
    vos_printf("其中  1X模式收到的上行数据:            %d\n", g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt);
    vos_printf("            发送的上行协商报文个数:    %d\n", g_stPppcDataQueueStats.ul1xUlNegoSndCnt);
    vos_printf("            发送的上行IP包个数:        %d\n", g_stPppcDataQueueStats.ul1xUlIPDataSndCnt);
    vos_printf("      HRPD模式收到的上行数据:          %d\n", g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt);
    vos_printf("            发送的上行协商报文个数:    %d\n", g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt);
    vos_printf("            发送的上行IP包个数:        %d\n", g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt);
    vos_printf("PPPC的存储上行数据链表的最大节点数:    %d\n", g_stPppcDataQueueStats.ulUlDataQMaxCnt);
    vos_printf("PPPC的上行数据链表的当前节点数:        %d\n", g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt);
    vos_printf("PPPC的上行数据入队数:                  %d\n", g_stPppcDataQueueStats.ulUlDataQEnqueueMsgCnt);
    vos_printf("PPPC的上行数据出队处理数:              %d\n", g_stPppcDataQueueStats.ulUlDataQProcMsgCnt);

    vos_printf("HDLC上行内存申请次数:                  %d\n", g_stPppcDataQueueStats.ulMemAllocUplinkCnt);
    vos_printf("HDLC上行内存申请失败次数:              %d\n", g_stPppcDataQueueStats.ulMemAllocUplinkFailCnt);
    vos_printf("HDLC硬件封装有效帧数:                  %d\n", g_stPppcDataQueueStats.ulUplinkSndDataCnt);
    vos_printf("HDLC其他内存释放次数:                  %d\n", g_stPppcDataQueueStats.ulMemFreeCnt);

    vos_printf("PPPC上行队列节点个数:                  %d\n", g_stPppUlLink.ulCnt);

    vos_printf("\n");
    return;
}


VOS_UINT8 *PPP_GetUlEncapDataPtr(VOS_VOID)
{
    return g_aucUlEncapData;
}


VOS_VOID PPP_InitEncapDataPtr(VOS_VOID)
{
    PS_MEM_SET(g_aucUlEncapData, 0, sizeof(g_aucUlEncapData));
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_IncreaseNegoRcvCnt
 功能描述  : 收到的PPP协商报文数加一
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_1X_IncreaseNegoRcvCnt(VOS_VOID)
{
    g_stPppcDataQueueStats.ul1xDlNegoRcvCnt++;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_IncreaseNegoRcvCnt
 功能描述  : 收到的PPP协商报文数加一
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月18日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_HRPD_IncreaseNegoRcvCnt(VOS_VOID)
{
    g_stPppcDataQueueStats.ulHrpdDlNegoRcvCnt++;
    return;
}




VOS_VOID *PPP_GetActPppHeadNode()
{
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

    return (VOS_VOID *)pstApsCurrHeadNode;
}


VOS_UINT32 PPP_GetConfigUserName
(
    VOS_UINT8                          *pucUserName
)
{
    VOS_UINT32                          ulUserNameLen;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;


    if (VOS_NULL_PTR == pucUserName)
    {
        PPPC_WARNING_LOG("parameter is NULL.");

        return VOS_ERR;
    }

    pstPppCont  = &g_stPppContext;
    /* 判断当前是否正在进行接入鉴权 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        VOS_StrNCpy((VOS_INT8 *)pucUserName,
            (VOS_INT8 *)(pstPppCont->stHrpdContext.aucAccessAuthUserName),
            pstPppCont->stHrpdContext.ucAccessAuthLen);
        return VOS_OK;
    }

    ulUserNameLen = pstPppCont->ulUserNameLen;

    VOS_StrNCpy((VOS_INT8 *)pucUserName,
        (VOS_INT8 *)(pstPppCont->aucUserName),
        ulUserNameLen);
    *(VOS_UINT8 *)(pucUserName + ulUserNameLen) = '\0';

    return VOS_OK;
}
VOS_UINT32 PPP_GetConfigPassWord
(
    VOS_UINT8                          *pucPassWd
)
{
    VOS_UINT32                          ulPasswordLen;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;


    if (VOS_NULL_PTR == pucPassWd)
    {
        PPPC_WARNING_LOG("parameter is NULL.");

        return VOS_ERR;
    }

    pstPppCont  = &g_stPppContext;

    ulPasswordLen = pstPppCont->ulPasswordLen;

    VOS_StrNCpy((VOS_INT8 *)pucPassWd,
        (VOS_INT8 *)(pstPppCont->aucPassword),
        ulPasswordLen);
    *(VOS_UINT8 *)(pucPassWd + ulPasswordLen) = '\0';

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPP_GetDefaultMru
 功能描述  : 获取默认的MRU值
 输入参数  : 无
 输出参数  : 无
 返 回 值  :
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月29日
    作    者   : W00316385
    修改内容   :

*****************************************************************************/
VOS_UINT16 PPP_GetDefaultMru(VOS_VOID)
{
    return g_stPppContext.usMru;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_GetAppType
 功能描述  : 获取ApplicationType
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT16
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月20日
    作    者   : w00316385
    修改内容   :

*****************************************************************************/
VOS_UINT16 PPPC_HRPD_GetAppType(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.aenApplicationType[1];
}


VOS_UINT8 PPPC_HRPD_GetStreamNumber(VOS_VOID)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucStreamRN = 1;
    VOS_UINT8                           ucStreamSN = 2;
    VOS_UINT32                          ulSteamIndex;
    VOS_UINT32                          ulMaxSteamNum = 3;


    pstPppContext   = &g_stPppContext;

    /* 目前只支持DPA,EMPA场景待后续分析后再添加 */
    for (ulSteamIndex = 0; ulSteamIndex < ulMaxSteamNum; ulSteamIndex++)
    {
        /* stream number等于0为信令,实体中存储的流号从1开始 */
        if (CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_RN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
        {
            ucStreamRN = (VOS_UINT8)(ulSteamIndex + 1);
        }
        else if (CTTF_HRPD_PA_APPLICATION_TYPE_DEFAULT_PACKET_SN
            == pstPppContext->stHrpdContext.aenApplicationType[ulSteamIndex])
        {
            ucStreamSN = (VOS_UINT8)(ulSteamIndex + 1);
        }
        else
        {
            /* TODO: */
        }
    }

    /* 如果当前正在进行接入鉴权,返回RN的流号 */
    if (PS_TRUE == g_stPppContext.stHrpdContext.enIsDoingAcessAuth)
    {
        return ucStreamRN;
    }
    else
    {
        return ucStreamSN;
    }
}


VOS_UINT32 PPPC_FidInit(enum VOS_INIT_PHASE_DEFINE ip)
{
    VOS_UINT32  ulResult = PS_FAIL;


    switch (ip)
    {
        case   VOS_IP_LOAD_CONFIG:

            /*注册PPPC PID*/
            ulResult = VOS_RegisterPIDInfo(MSPS_PID_PPPC,
                                           PPPC_Init,
                                           PPPC_MsgProc);
            if (VOS_OK != ulResult)
            {
                vos_printf("PPPC_FidInit, register PPPC PID fail!\n");
                return VOS_ERR;
            }

            ulResult = VOS_RegisterTaskPrio(MSPS_FID_PPPC, PPPC_TASK_PRI);
            if( VOS_OK != ulResult )
            {
                vos_printf("PPPC_FidInit, register priority fail!\n");
                return VOS_ERR;
            }
            break;
        case   VOS_IP_FARMALLOC:
        case   VOS_IP_INITIAL:
        case   VOS_IP_ENROLLMENT:
        case   VOS_IP_LOAD_DATA:
        case   VOS_IP_FETCH_DATA:
        case   VOS_IP_STARTUP:
        case   VOS_IP_RIVAL:
        case   VOS_IP_KICKOFF:
        case   VOS_IP_STANDBY:
        case   VOS_IP_BROADCAST_STATE:
        case   VOS_IP_RESTART:
        case   VOS_IP_BUTT:
            break;
        default:
            break;
    }

    return VOS_OK;
}
VOS_VOID PPPC_QueueInit(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcDlDataQ;
    TTF_LINK_ST                        *pstPppcUlDataQ;


    /* 初始化下行队列 */
    pstPppcDlDataQ    = &g_stPppDlLink;
    PS_MEM_SET(&g_stPppDlLink, 0, sizeof(g_stPppDlLink));

    TTF_LinkInit(MSPS_PID_PPPC, pstPppcDlDataQ);

    /* 初始化上行队列 */
    pstPppcUlDataQ    = &(g_stPppUlLink);
    PS_MEM_SET(&g_stPppUlLink, 0, sizeof(g_stPppUlLink));

    TTF_LinkInit(MSPS_PID_PPPC, pstPppcUlDataQ);

    /* 初始化队列中待处理消息计数 */
    PS_MEM_SET(&g_stDataQNotifyCnt, 0, sizeof(g_stDataQNotifyCnt));

    return;
}
VOS_VOID PPPC_ClearDlDataQ(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcDlDataQ;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT32                          ulRemainCnt;


    pstPppcDlDataQ    = &g_stPppDlLink;

    /* 释放所有Tx Entity相关的数据、节点缓存 */
    while (TTF_LINK_IS_NOT_EMPTY(pstPppcDlDataQ))
    {
        pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstPppcDlDataQ, &ulRemainCnt);

        /*异常:链表和链表个数不一致时, 容错处理, 返回VOS_NULL_PTR*/
        if (VOS_NULL_PTR == pstDlDataNode)
        {
            return;
        }

        /* 已保证循环释放TTFMemory */
        TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

        pstDlDataNode->pstPduMem = VOS_NULL_PTR;

        /* 释放TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);
        pstDlDataNode = VOS_NULL_PTR;
    }

    PPPC_INFO_LOG("PPP, PPPC_ClearDlDataQ, NORMAL, Clear Stat Info\n");

    return;
}


VOS_VOID PPPC_ClearUlDataQ(VOS_VOID)
{
    TTF_LINK_ST                        *pstPppcUlDataQ;
    PPPC_DATA_LINK_NODE_STRU           *pstUlDataNode;
    VOS_UINT32                          ulRemainCnt;


    pstPppcUlDataQ    = &g_stPppUlLink;

    /* 释放所有Tx Entity相关的数据、节点缓存 */
    while (TTF_LINK_IS_NOT_EMPTY(pstPppcUlDataQ))
    {
        pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
            pstPppcUlDataQ, &ulRemainCnt);

        /*异常:链表和链表个数不一致时, 容错处理, 返回VOS_NULL_PTR*/
        if (VOS_NULL_PTR == pstUlDataNode)
        {
            return;
        }

        /* 释放TTFMemory,上行一个节点对应一块TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstUlDataNode->pstPduMem);
        pstUlDataNode->pstPduMem = VOS_NULL_PTR;

        /* Free memory allocated for trace */
        PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode->pstUlDataInfo);
        pstUlDataNode->pstUlDataInfo    = VOS_NULL_PTR;

        /* 释放TTFNode */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);
        pstUlDataNode = VOS_NULL_PTR;
    }

    PPPC_INFO_LOG("PPP, PPPC_ClearUlDataQ, NORMAL, Clear Stat Info\n");

    return;
}
VOS_VOID PPPC_QNotifyCntSubOper(VOS_VOID)
{
    VOS_INT32                          lLockKey;


    /* 队列中待处理消息减 */
    if (g_stDataQNotifyCnt.ulNotifyMsgCnt > 0)
    {
        /* 队列加锁 */
        lLockKey = VOS_SplIMP();

        g_stDataQNotifyCnt.ulNotifyMsgCnt--;

        /* 队列操作完成解锁 */
        VOS_Splx(lLockKey);
    }
    else
    {
        /* 待处理消息为0，异常 */
        PPPC_WARNING_LOG1("PPP Queue Notify Msg Cnt is NULL!\r\n",
            g_stDataQNotifyCnt.ulNotifyMsgCnt);
    }

    return;
}


PMBUF_S *PPPC_AdapterTtfMemorytoMBuf(TTF_MEM_ST *pstTtfMem)
{
    PMBUF_S                            *pstMBuf = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstCurrTtfMem = pstTtfMem;
    VOS_UINT32                          ulRet;
    VOS_UINT8                          *pucData = VOS_NULL_PTR;


    /* 内部调用保证入参非空 */

    pstMBuf = (PMBUF_S *)PMBUF_GetPMbuf(MID_PPPC, pstCurrTtfMem->usUsed);
    if (VOS_NULL_PTR == pstMBuf)
    {
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
        PPPC_WARNING_LOG("Get MBuf Memory fail!");
        PPP_DBG_ERR_CNT(PPP_PHERR_873);
        return VOS_NULL_PTR;
    }

    while(VOS_NULL_PTR != pstCurrTtfMem)
    {
        pucData     = pstCurrTtfMem->pData;
        if (VOS_NULL_PTR == pucData)
        {
            PPPC_WARNING_LOG1("TTFMemory to MBuf Get Data Ptr fail!", pstCurrTtfMem->usUsed);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

            /* 释放pstMBuf */
            PMBUF_Destroy(pstMBuf);
            PPP_DBG_ERR_CNT(PPP_PHERR_872);
            return VOS_NULL_PTR;
        }

        /* IP包长度不能超过1500字节算上转译字符也不会超过3K,
        每次拷贝都偏移ulTotalDataLength,ulTotalDataLength会在接口内部被刷新 */
        ulRet   = PMBUF_CopyDataFromBufferToPMBuf(pstMBuf,
                                             pstMBuf->ulTotalDataLength,
                                             pstCurrTtfMem->usUsed,
                                             pucData,
                                             MSPS_PID_PPPC);
        if (VOS_OK != ulRet)
        {
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
            PPPC_WARNING_LOG1("Copy Data to MBuf Memory fail!\r\n", ulRet);
            /* 释放pstMBuf */
            PMBUF_Destroy(pstMBuf);
            PPP_DBG_ERR_CNT(PPP_PHERR_874);
            return VOS_NULL_PTR;
        }

        pstCurrTtfMem   = pstCurrTtfMem->pNext;

    }

    TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);

    return pstMBuf;
}
TTF_MEM_ST *PPPC_AdapterMBuftoTtfMemory
(
    PMBUF_S                            *pstMBuf,
    VOS_UINT32                          ulMemPoolId,
    VOS_UINT32                          ulOffset,
    VOS_UINT32                          ulLength
)
{
    TTF_MEM_ST                         *pstTtfMem = VOS_NULL_PTR;
    VOS_UINT8                          *pucData;


    if (ulOffset > pstMBuf->ulTotalDataLength)
    {
        return VOS_NULL_PTR;
    }

    pucData     = pstMBuf->stDataBlockDescriptor.pucData + ulOffset;

    /* MBUF转为TTFMemory只可能是递交上行数据时可能需要用到 */
    pstTtfMem   = TTF_MemBlkCopyAlloc(MSPS_PID_PPPC,
                ulMemPoolId, pucData, (VOS_UINT16)ulLength);

    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPPC_WARNING_LOG1("Copy Data to TTFMemory fail!\r\n", ulLength);
        PPP_DBG_ERR_CNT(PPP_PHERR_875);
        return VOS_NULL_PTR;
    }

    return pstTtfMem;
}
VOS_VOID PPPC_RcvRlpDlFrame
(
    VOS_UINT16                          usSeqNr,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
)
{
    /* 内部调用保证入参非空 */


    /* 调用分片重组函数处理 */
    FWD_PppRebuild(usSeqNr, pstData, ucRatMode);

    return;
}


VOS_UINT32 PPPC_PrepareUlEncapMem(VOS_UINT16 usLen)
{
    VOS_UINT16                          usFrmedMaxLen;
    VOS_UINT16                          usFirstFragmentLen  = 0;
    VOS_UINT16                          usSecendFragmentLen = 0;

    /* 根据(2*原始数据长度+13B)计算 */
    VOS_UINT32                          ulMaxLen            = PPPC_MAX_UL_ENCAP_LEN - 7;


    if ((0 == usLen) || (usLen > ulMaxLen))
    {
        PPPC_WARNING_LOG1("Data len is invalid %d\r\n", usLen);
        return VOS_ERR;
    }

    /* 封装后可能的最大数据长度(2*原始数据长度+13B) */
    usFrmedMaxLen = (VOS_UINT16)(2 * usLen + 13);
    usFirstFragmentLen  = (usFrmedMaxLen >= PPPC_MAX_UL_ENCAP_LEN) ? PPPC_MAX_UL_ENCAP_LEN : usFrmedMaxLen;
    usSecendFragmentLen = (usFrmedMaxLen >= PPPC_MAX_UL_ENCAP_LEN) ? (usFrmedMaxLen - usFirstFragmentLen) : 0;

    /* 申请第一块内存 */
    if (PS_TRUE == g_astUlEncapMem[0].enPtrIsUsed)
    {
        TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[0].pstDataPtr);
        g_astUlEncapMem[0].pstDataPtr = VOS_NULL_PTR;
        g_astUlEncapMem[0].enPtrIsUsed = PS_FALSE;
    }

    g_astUlEncapMem[0].pstDataPtr  = TTF_MemBlkAlloc(MSPS_PID_PPPC,
        TTF_MEM_POOL_ID_UL_DATA, usFirstFragmentLen);

    /* 申请不到内存返回错误 */
    if (VOS_NULL_PTR == g_astUlEncapMem[0].pstDataPtr)
    {
        PPPC_INFO_LOG("Alloc Fail");
        return VOS_ERR;
    }
    g_astUlEncapMem[0].enPtrIsUsed = PS_TRUE;

    if (0 != usSecendFragmentLen)
    {
        /* 申请第二块内存 */
        if (PS_TRUE == g_astUlEncapMem[1].enPtrIsUsed)
        {
            TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[1].pstDataPtr);
            g_astUlEncapMem[1].pstDataPtr = VOS_NULL_PTR;
            g_astUlEncapMem[1].enPtrIsUsed = PS_FALSE;
        }

        g_astUlEncapMem[1].pstDataPtr  = TTF_MemBlkAlloc(MSPS_PID_PPPC,
            TTF_MEM_POOL_ID_UL_DATA, usSecendFragmentLen);

        /* 申请不到内存返回错误 */
        if (VOS_NULL_PTR == g_astUlEncapMem[1].pstDataPtr)
        {
            PPPC_INFO_LOG("Alloc Fail");
            return VOS_ERR;
        }
        g_astUlEncapMem[1].enPtrIsUsed = PS_TRUE;
    }

    return VOS_OK;
}


VOS_UINT32 PPPC_DlEnqueueData
(
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode,
    TTF_LINK_ST                        *pstDataLink,
    VOS_UINT32                         *pulNonEmptyEvent
)
{
    VOS_UINT32                          ulTemporyEmptyEvent = PS_FALSE;
    VOS_UINT32                          ulRet;


    /* 将数据结点插入队列尾部 */
    ulRet = TTF_LinkSafeInsertTail(MSPS_PID_PPPC, pstDataLink,
            &(pstDlNode->stNode), &ulTemporyEmptyEvent);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Insert Fail", ulRet);

        return ulRet;
    }

    /* 成功插入下行队列一次就将计数加1 */
    g_ulMaxPktTrigerNtf++;

    /* 链表出现一次从空变为非空就设置非空到空变化标识为真 */
    if ((PS_TRUE == ulTemporyEmptyEvent) || (g_ulMaxPktTrigerNtf >= PPPC_MAX_NOTIFY_PPPC_PROC_CNT))
    {
        *pulNonEmptyEvent = PS_TRUE;
    }

    return VOS_OK;
}
VOS_VOID PPPC_SendDlDataNotifyCommon
(
    TTF_LINK_ST                        *pstDataLink,
    VOS_UINT32                          ulNonEmptyEvent,
    VOS_UINT32                          ulSendMsgCnt
)
{
    VOS_UINT8                           ucNeedToNotify = PS_FALSE;


    /* 只有当链表是从非空到空的变化时才需要通知PPPC去处理 */
    if ((0 == g_stDataQNotifyCnt.ulNotifyMsgCnt) && (PS_TRUE == ulNonEmptyEvent))
    {
        ucNeedToNotify = PS_TRUE;
    }

    g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt = TTF_LinkCnt(MSPS_PID_PPPC, pstDataLink);
    if (g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt > g_stPppcDataQueueStats.ulDlDataQMaxCnt)
    {
        /* 刷新下行队列中挂接的最大节点统计值 */
        g_stPppcDataQueueStats.ulDlDataQMaxCnt = g_stPppcDataQueueStats.ulDlDataQCurrentMsgCnt;
        PPPC_INFO_LOG1("The DL Quene max count is %d.\n", g_stPppcDataQueueStats.ulDlDataQMaxCnt);
    }

    if (PS_TRUE == ucNeedToNotify)
    {
        /*向PPP发送数据处理指示*/
        if (VOS_OK != PPPC_SndDlDataNotify())
        {
            /* 发送消息通知失败，需要清空整个队列 */
            PPPC_ClearDlDataQ();
            PPPC_WARNING_LOG("Send DL data notify fail.");
            return;
        }

        /* 发送Notify消息后将计数清零 */
        g_ulMaxPktTrigerNtf = 0;
    }

    g_stPppcDataQueueStats.ulDlDataQEnqueueMsgCnt += ulSendMsgCnt;

    return;
}
VOS_VOID PPPC_HRPD_DlEnqueueData(RLP_PPP_HRPD_TRANS_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;   /* 记录队列是否发生了由空到非空的转变 */
    VOS_UINT32                          ulRet;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;


    /* 申请节点 */
    pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstDlNode)
    {
        PPPC_WARNING_LOG("Alloc Fail");

        /* 释放RLP申请的TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstPackets->pstSdu);

        return;
    }

    PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstDlNode->ulPduCnt     = 1;
    pstDlNode->pstPduMem    = pstPackets->pstSdu;
    pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstDlNode->ucStreamNum  = pstPackets->ucStreamNumber;
    pstDlNode->usHigherLayerProtocol  = pstPackets->ucHigherLayerProtocol;

    /* TODO: aucReservLabel needs to copied
    pstDlNode->ucResvLabel  = pstPackets->ucReservationLabel;*/
    pstDlNode->enRatMode    = PPPC_RAT_MODE_HRPD;

    ulRet   = PPPC_DlEnqueueData(pstDlNode, &g_stPppDlLink, &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        /* 释放RLP申请的TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstPackets->pstSdu);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

    /* TODO:目前HRPD数据每次只发一个,后续需要跟PA一起修改为与1X一样一次发送16个 */
    PPPC_SendDlDataNotifyCommon(&g_stPppDlLink, ulNonEmptyEvent, 1);

    return;
}
VOS_VOID PPPC_FreePacketsTtmMem(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulLoop;


    /* 内部调用保证入参非空 */

    for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ulLoop++)
    {
        if (VOS_NULL_PTR != pstPackets->astDeliverSdus[ulLoop].pstSdu)
        {
            /* 释放RLP申请的TTF内存 */
            TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);
        }
    }

    return;
}


VOS_VOID PPPC_1X_DlEnqueueData(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    VOS_UINT32                          ulLoop;
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;   /* 记录队列是否发生了由空到非空的转变 */
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulPduIndex      = 0;
    TTF_LINK_ST                        *pstDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;
    TTF_MEM_ST                         *pstTtfMem       = VOS_NULL_PTR;
    TTF_MEM_ST                         *pstNextTtfMem   = VOS_NULL_PTR;



    pstDataLink    = &g_stPppDlLink;

    /* 申请节点 */
    pstDlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstDlNode)
    {
        PPPC_WARNING_LOG1("Alloc Fail", ulLoop);

        PPPC_FreePacketsTtmMem(pstPackets);

        return;
    }

    /* 节点初始化 */
    PPP_MemSet(pstDlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstDlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstDlNode->ucPdnId      = pstPackets->ucPdnId;
    pstDlNode->enRatMode    = PPPC_RAT_MODE_1X;
    pstDlNode->pstPduMem    = pstPackets->astDeliverSdus[ulPduIndex].pstSdu;

    pstTtfMem               = pstDlNode->pstPduMem;
    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPPC_WARNING_LOG("TTF Mem is null");

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

    pstTtfMem->usApp        = pstPackets->astDeliverSdus[ulPduIndex].usSeq;

    for (ulLoop = 1; ulLoop < pstPackets->ucSduCount; ++ulLoop)
    {
        pstTtfMem->pNext    = pstPackets->astDeliverSdus[ulLoop].pstSdu;
        pstNextTtfMem       = pstTtfMem->pNext;

        if (VOS_NULL_PTR == pstTtfMem->pNext)
        {
            PPPC_WARNING_LOG1("pstSdu is null. ulLoop:%d.", ulLoop);
            continue;
        }

        /* usApp用于存储序列号 */
        pstTtfMem->pNext->usApp = pstPackets->astDeliverSdus[ulLoop].usSeq;
        pstTtfMem               = pstNextTtfMem;
        ulPduIndex++;
    }
    pstTtfMem->pNext        = VOS_NULL_PTR;

    pstDlNode->ulPduCnt     = ulPduIndex + 1;
    /* 节点赋值完毕插入队列 */
    ulRet = PPPC_DlEnqueueData(pstDlNode, pstDataLink, &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG1("Insert Fail", ulLoop);

        PPPC_FreePacketsTtmMem(pstPackets);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlNode);

        return;
    }

    /* 通知PPPC处理下行链表 */
    PPPC_SendDlDataNotifyCommon(pstDataLink, ulNonEmptyEvent, pstPackets->ucSduCount);

    return;
}


VOS_VOID PPPC_UlEnqueueData(PPPC_DATA_LINK_NODE_STRU *pstUlNode)
{
    VOS_UINT32                          ulNonEmptyEvent = PS_FALSE;    /* 记录队列是否发生了由空到非空的转变 */
    VOS_UINT32                          ulRet;
    TTF_LINK_ST                        *pstUlDataLink;
    VOS_UINT8                           ucNeedToNotify = PS_FALSE;


    pstUlDataLink    = &g_stPppUlLink;

    /* 将数据结点插入队列尾部 */
    ulRet = TTF_LinkSafeInsertTail(MSPS_PID_PPPC, pstUlDataLink,
            &(pstUlNode->stNode), &ulNonEmptyEvent);
    if (VOS_OK != ulRet)
    {
        /* 释放TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstUlNode->pstPduMem);

        PS_MEM_FREE(MSPS_PID_PPPC, pstUlNode->pstUlDataInfo);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlNode);

        PPPC_WARNING_LOG("The UL data node is failed to insert!\n");
        return;
    }

    /* 只有当链表是从非空到空的变化时才需要通知PPPC去处理 */
    if ((PS_TRUE == ulNonEmptyEvent) && (0 == g_stDataQNotifyCnt.ulNotifyMsgCnt))
    {
        ucNeedToNotify = PS_TRUE;
    }

    g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt = TTF_LinkCnt(MSPS_PID_PPPC, pstUlDataLink);
    if (g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt > g_stPppcDataQueueStats.ulUlDataQMaxCnt)
    {
        /* 刷新上行队列中挂接的最大节点统计值 */
        g_stPppcDataQueueStats.ulUlDataQMaxCnt = g_stPppcDataQueueStats.ulUlDataQCurrentMsgCnt;
        PPPC_INFO_LOG1("The UL Quene max count is %d.\n", g_stPppcDataQueueStats.ulUlDataQMaxCnt);
    }

    if (PS_TRUE == ucNeedToNotify)
    {
        /*向PPP发送数据处理指示*/
        if (VOS_OK != PPPC_SndUlDataNotify())
        {
            PPPC_WARNING_LOG("Send UL data notify fail.\n");
            /* 发送消息通知失败，需要清空整个队列 */
            PPPC_ClearUlDataQ();
            return;
        }
    }

    g_stPppcDataQueueStats.ulUlDataQEnqueueMsgCnt++;

    return;
}


VOS_VOID PPPC_HRPD_UlEnqueueData(const CDS_CDMA_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    TTF_MEM_ST                         *pstTTFMem;


    /* 申请节点 */
    pstUlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstUlNode)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_INFO_LOG("Alloc mem fail.");
        return;
    }

    PPP_MemSet(pstUlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstUlNode->ulPduCnt     = 1;
    pstUlNode->pstPduMem    = pstPppSdu->pstSdu;
    pstUlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstUlNode->ucPdnId      = pstPppSdu->ucPdnId;
    pstUlNode->enRatMode    = PPPC_GetRatMode();
    TTF_NodeInit(&(pstUlNode->stNode));

    /* 上行节点在公共入队函数中释放 */
    PPPC_UlEnqueueData(pstUlNode);

    return;
}


VOS_VOID PPPC_1X_UlEnqueueData(const CDS_CDMA_1X_TRANS_DATA_STRU *pstPppSdu)
{
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    TTF_MEM_ST                         *pstTTFMem;


    /* 申请节点 */
    pstUlNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_NODE_MEM_ALLOC(MSPS_PID_PPPC, sizeof(PPPC_DATA_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstUlNode)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_INFO_LOG("Alloc mem fail.");
        return;
    }

    PPP_MemSet(pstUlNode, 0, sizeof(PPPC_DATA_LINK_NODE_STRU));
    pstUlNode->ulPduCnt     = 1;
    pstUlNode->pstPduMem    = pstPppSdu->pstSdu;
    pstUlNode->ulTimeStamp  = mdrv_timer_get_normal_timestamp();
    pstUlNode->ucPdnId      = pstPppSdu->ucPdnId;
    pstUlNode->enRatMode    = PPPC_RAT_MODE_1X;
    TTF_NodeInit(&(pstUlNode->stNode));

    /* enIpDataType 用于rrlp */
    pstUlNode->enIpDataType = TTF_ParseIpDataType(MSPS_PID_PPPC, pstPppSdu->pstSdu->pData,
        pstPppSdu->pstSdu->usUsed, pstPppSdu->pstSdu->ucDataPriority);

    /* pstUlDataInfo用于rrlp上行trace勾取 */
    pstUlNode->pstUlDataInfo    = (PS_DATA_EXT_INFO_STRU *)PS_MEM_ALLOC(
        MSPS_PID_PPPC, sizeof(PS_DATA_EXT_INFO_STRU));
    if (VOS_NULL_PTR == pstUlNode->pstUlDataInfo)
    {
        /* 释放TTF内存 */
        TTF_MemFree(MSPS_PID_PPPC, pstUlNode->pstPduMem);

        /* 释放节点 */
        TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlNode);

        PPPC_WARNING_LOG("pstUlDataInfo is failed to alloc!\n");
        return;
    }

    FWD_PppFillDataInfo(pstPppSdu->pstSdu->pData, pstUlNode->pstUlDataInfo);

    /* 上行节点在公共入队函数中释放 */
    PPPC_UlEnqueueData(pstUlNode);

    return;
}


VOS_VOID PPPC_DlDequeueProc()
{
    TTF_LINK_ST                        *pstDlDataLink;
    TTF_MEM_ST                         *pstTtfMem;
    TTF_MEM_ST                         *pstNextTtfMem;
    PPPC_DATA_LINK_NODE_STRU           *pstDlDataNode;
    VOS_UINT16                          usSeq;
    VOS_UINT32                          ulRemainCnt;
    VOS_UINT32                          ulPduIndex;
#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT32                          ulDealCnt = 0;
    VOS_UINT32                          ulRet;
#endif


    pstDlDataLink  = &g_stPppDlLink;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    ulRet = PPPC_HDLC_HARD_DefPacket(pstDlDataLink, &ulDealCnt);

    /* 下行报文出队统计 */
    g_stPppcDataQueueStats.ulDlDataQProcMsgCnt += ulDealCnt;

    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG("Def packet fail!\r\n");
        return;
    }

    return;

#else

    pstDlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
        pstDlDataLink, &ulRemainCnt);

    /* 队列为空的时候返回空指针 */
    if ( VOS_NULL_PTR == pstDlDataNode )
    {
        PPPC_WARNING_LOG("PPP DL Queue is Empty!\r\n");
        return;
    }

    pstTtfMem   = pstDlDataNode->pstPduMem;
    usSeq       = pstTtfMem->usApp;

    for (ulPduIndex = 0; ulPduIndex < pstDlDataNode->ulPduCnt; ulPduIndex++)
    {
        /* 入队时已保证所有的TTFMEM非空 */
        pstNextTtfMem   = pstTtfMem->pNext;

        /* 下行报文出队统计 */
        g_stPppcDataQueueStats.ulDlDataQProcMsgCnt++;

        /* 如果TTFMEM中的usUsed大于可能的最大分片报文长度,跳过此分片处理下一片报文 */
        if (pstTtfMem->usUsed > TTF_BIT2BYTE(PPPC_MAX_FRAGMENT_BIT_LEN))
        {
            PPPC_WARNING_LOG1("Ttf Mem used len is invalid:%d\r\n", pstTtfMem->usUsed);

            pstTtfMem   = pstNextTtfMem;
            usSeq       = pstNextTtfMem->usApp;

            continue;
        }

        PPPC_RcvRlpDlFrame(usSeq, pstTtfMem, pstDlDataNode->enRatMode);

        if (VOS_NULL_PTR != pstNextTtfMem)
        {
            pstTtfMem   = pstNextTtfMem;
            usSeq       = pstNextTtfMem->usApp;
        }
        else
        {
            break;
        }
    }

    TTF_MemFree(MSPS_PID_PPPC, pstDlDataNode->pstPduMem);

    /* 释放节点 */
    TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstDlDataNode);

    return;

#endif
}


VOS_VOID PPPC_UlDequeueProc()
{
    TTF_LINK_ST                        *pstUlDataLink;
    PPPC_DATA_LINK_NODE_STRU           *pstUlDataNode;
    VOS_UINT8                           ucPdnId;
    VOS_UINT32                          ulRemainCnt;
    VOS_UINT32                          ulRet;
#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    VOS_UINT8                           ucPppId = 0;
    VOS_UINT32                          ulDealCnt = 0;
#endif


    pstUlDataLink  = &g_stPppUlLink;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

    pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlDataLink);

    if(VOS_NULL_PTR == pstUlDataNode)
    {
        PPPC_WARNING_LOG("PPP UL Queue is Empty!\r\n");
        return;
    }

    ucPdnId     = pstUlDataNode->ucPdnId;

    ulRet   = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Get Ppp Id Fail! ucPdnId:[%d], ucPppId:[%d].\r\n", ucPdnId, ucPppId);
        return;
    }

    PPPC_HDLC_HARD_FrmPacket((VOS_UINT16)ucPppId, PPP_IP, pstUlDataLink, &ulDealCnt);

    /* 上行报文出队数统计 */
    g_stPppcDataQueueStats.ulUlDataQProcMsgCnt += ulDealCnt;
    return;

#else

    pstUlDataNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlDataLink);
    /* 队列为空的时候返回空指针 */
    if ( VOS_NULL_PTR == pstUlDataNode )
    {
        PPPC_WARNING_LOG("PPP UL Queue is Empty!\r\n");
        return;
    }

    if (VOS_NULL_PTR == pstUlDataNode->pstPduMem)
    {
        PPPC_WARNING_LOG("pstUlDataNode->pstPduMem is null!\r\n");
        return;
    }

    /* 准备上行数据内存 */
    ulRet   = PPPC_PrepareUlEncapMem(pstUlDataNode->pstPduMem->usUsed);
    if (VOS_OK != ulRet)
    {
        PPPC_INFO_LOG("Alloc ul mem fail!\r\n");

        return;
    }

    pstUlDataNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkSafeRemoveHead(MSPS_PID_PPPC,
        pstUlDataLink, &ulRemainCnt);


    /* 上行报文出队数统计 */
    g_stPppcDataQueueStats.ulUlDataQProcMsgCnt++;

    ucPdnId     = pstUlDataNode->ucPdnId;

    PPPC_RcvCdsUlFrame(ucPdnId, pstUlDataNode->pstPduMem,
        pstUlDataNode->enRatMode, pstUlDataNode->pstUlDataInfo);

    /* 释放节点 */
    TTF_NODE_MEM_FREE(MSPS_PID_PPPC, pstUlDataNode);

    return;

#endif
}
VOS_VOID PPPC_ProcLinkNodeByDirection
(
    VOS_UINT32                              ulDlStamp,
    VOS_UINT32                              ulUlStamp,
    PPPC_PROC_LINK_DIRECTION_ENUM_UINT16    enProcDire
)
{
    switch (enProcDire)
    {
        case PPPC_PROC_DL_NODE:

            PPPC_DlDequeueProc();

            break;

        case PPPC_PROC_UL_NODE:

            PPPC_UlDequeueProc();

            break;

        case PPPC_PROC_BY_STAMP:

            /* stamp值越大表示入队越晚 */
            if (ulDlStamp >= ulUlStamp)
            {
                PPPC_UlDequeueProc();
            }
            else
            {
                PPPC_DlDequeueProc();
            }

            break;

        default:

            PPPC_WARNING_LOG3("Invalid direction!\r\n",
                enProcDire, ulDlStamp, ulUlStamp);

            break;
    }

    return;
}
VOS_VOID PPPC_DequeueProc(PPPC_PROC_LINK_DIRECTION_ENUM_UINT16 enProcDire)
{
    TTF_LINK_ST                        *pstDlLink;
    TTF_LINK_ST                        *pstUlLink;
    PPPC_DATA_LINK_NODE_STRU           *pstDlNode;
    PPPC_DATA_LINK_NODE_STRU           *pstUlNode;
    VOS_UINT32                          ulDlStamp;
    VOS_UINT32                          ulUlStamp;
    VOS_UINT32                          ulTimerLoop     = 0;
    VOS_UINT32                          ulDelayNoteLoop = 0;


    pstDlLink       = &g_stPppDlLink;
    pstUlLink       = &g_stPppUlLink;


    for (;;)
    {
        /* 处理次数达到门限时起定时器并退出PPPC任务 */
        if (ulTimerLoop >= PPPC_MAX_NOTIFY_PPPC_PROC_CNT)
        {
            if ((VOS_NULL_PTR == g_hReachMaxProcTimer) && (PS_TRUE == g_enIsReachTimeout))
            {
                (VOS_VOID)VOS_StartRelTimer((HTIMER *)&g_hReachMaxProcTimer, MSPS_PID_PPPC,
                    PPPC_REACH_MAX_PROC_TIMER_AWAKE_LEN, 0, PPPC_AWAKE_SELF_REACH_MAX_PROC_TIMER,
                    VOS_TIMER_NOLOOP, VOS_TIMER_PRECISION_0);
                g_enIsReachTimeout = PS_FALSE;
            }

            break;
        }

        /* 处理次数达到门限时做延时处理防止PPPC一直占着CPU */
        if (ulDelayNoteLoop >= PPPC_MAX_NOTIFY_PPPC_DELAY_CNT)
        {
            VOS_TaskDelay(1);
            ulDelayNoteLoop = 0;
        }

        ulTimerLoop++;
        ulDelayNoteLoop++;

        if (pstDlLink->ulCnt > PPPC_MAX_DL_NODE_CNT)
        {
            /* 下行队列深度大于门限时强制处理下行队列 */
            PPPC_DlDequeueProc();
            continue;
        }

        pstDlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstDlLink);
        pstUlNode   = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstUlLink);

        if ((VOS_NULL_PTR == pstDlNode) && (VOS_NULL_PTR == pstUlNode))
        {
            /* 上下行队列都为空的时候退出循环 */
            PPPC_INFO_LOG("PPP DL and UL Queue is Empty!\r\n");
            break;
        }
        else if ((VOS_NULL_PTR != pstDlNode) && (VOS_NULL_PTR != pstUlNode))
        {
            ulDlStamp   = pstDlNode->ulTimeStamp;
            ulUlStamp   = pstUlNode->ulTimeStamp;

            PPPC_ProcLinkNodeByDirection(ulDlStamp, ulUlStamp, enProcDire);
        }
        else if (VOS_NULL_PTR != pstDlNode)
        {
            /* 只有下行队列有节点 */
            PPPC_DlDequeueProc();
        }
        else
        {
            /* 只有上行队列有节点 */
            PPPC_UlDequeueProc();
        }
    }


    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TracePackets
 功能描述  : PPPC模块报文跟踪
 输入参数  : CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo
             TTF_MEM_ST                         *pstTtfMem
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_TracePackets
(
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo,
    TTF_MEM_ST                         *pstTtfMem
)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnTrace;
    VOS_UINT32                          ulDataLen;


    /* 可维可测 */
    if ((VOS_NULL_PTR != pstMntnInfo) && (VOS_NULL_PTR != pstTtfMem))
    {
        if (VOS_NULL_PTR != pstTtfMem->pData)
        {
            ulDataLen   = pstMntnInfo->ulLength;

            pstMntnTrace = (CTTF_PPPC_TRACE_DATA_STRU *)PPP_Malloc(
                           PPPC_OM_TRANS_DATA_OFFSET_LEN + ulDataLen);
            if (VOS_NULL_PTR != pstMntnTrace)
            {
                PS_MEM_SET(pstMntnTrace, 0, PPPC_OM_TRANS_DATA_OFFSET_LEN + ulDataLen);
                PS_MEM_CPY(pstMntnTrace, pstMntnInfo, PPPC_OM_TRANS_DATA_OFFSET_LEN);

                (VOID)PS_MEM_CPY(pstMntnTrace->aucValue, pstTtfMem->pData, ulDataLen);

                PPP_MNTN_TRACE_MSG(pstMntnTrace);

                PPP_Free(pstMntnTrace);

                pstMntnTrace = VOS_NULL_PTR;
            }
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckRlpPacketsAndFreeMem
 功能描述  : 1X模式检查PPPC模块收到RLP的下行报文队列有效性
 输入参数  : pstPackets          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月24日
    作    者   : c001114540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_1X_CheckRlpPacketsAndFreeMem
(
    CTTF_1X_RLP_PPP_DELIVER_DATA_STRU  *pstPackets
)
{
    VOS_UINT32                          ulLoop;

    /* 空指针检查 */
    if (VOS_NULL_PTR == pstPackets)
    {
        PPPC_WARNING_LOG("Null Pointer");

        return VOS_ERR;
    }

    /* 报文数量为0 */
    if (0 == pstPackets->ucSduCount)
    {
        PPPC_WARNING_LOG("SduCount is 0");

        return VOS_ERR;
    }

    /* 报文数量异常 */
    if (pstPackets->ucSduCount > CTTF_1X_RLP_PPP_MAX_SDU_COUNT)
    {
        PPPC_WARNING_LOG1("SduCount is %d", pstPackets->ucSduCount);

        for (ulLoop = 0; ulLoop < CTTF_1X_RLP_PPP_MAX_SDU_COUNT; ++ulLoop)
        {
            if (VOS_NULL_PTR != pstPackets->astDeliverSdus[ulLoop].pstSdu)
            {
                TTF_MemFree(MSPS_PID_PPPC, pstPackets->astDeliverSdus[ulLoop].pstSdu);
            }
        }

        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_PushRlpPacketsEvent
 功能描述  : 1X模式PPPC模块收到RLP的下行报文入队
 输入参数  : pstPackets          PPP报文
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年04月23日
    作    者   : c001114540
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_PushRlpPacketsEvent(CTTF_1X_RLP_PPP_DELIVER_DATA_STRU * pstPackets)
{
    CDS_CDMA_1X_TRANS_DATA_STRU         stPppSdu;
    VOS_UINT32                          ulLoop;


    if (VOS_OK != PPPC_1X_CheckRlpPacketsAndFreeMem(pstPackets))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return VOS_ERR;
    }

    /* 如果是中继模式则直接调用CDS接口透传报文 */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        stPppSdu.ucPdnId = pstPackets->ucPdnId;
        for (ulLoop = 0; ulLoop < pstPackets->ucSduCount; ++ulLoop)
        {
            /* 由CDS判断pstPackets->astDeliverSdus[ulLoop].pstSdu是否为VOS_NULL_PTR */
            stPppSdu.ulSduLen   = pstPackets->astDeliverSdus[ulLoop].ulSduLen;
            stPppSdu.pstSdu     = pstPackets->astDeliverSdus[ulLoop].pstSdu;
            CDS_CDMA_1X_DL_DataInd(&stPppSdu, g_stPppContext.enModemId);

        }
        CDS_CDMA_WakeupCds();

        return VOS_OK;
    }

    /* 将下行报文加入队列 */
    PPPC_1X_DlEnqueueData(pstPackets);

    g_stPppcDataQueueStats.ul1xDlFrameRcvCnt += pstPackets->ucSduCount;

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_CheckRpaPackets
 功能描述  : HRPD模式检查PPPC模块收到RPA的下行报文队列有效性
 输入参数  : pstPppSdu          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HRPD_CheckRpaPackets
(
    RLP_PPP_HRPD_TRANS_DATA_STRU       *pstPppSdu
)
{
    /* 空指针检查 */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* 下行TTF内存为空返回错误 */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* 下行帧长为0返回错误 */
    if (0 == pstPppSdu->ulSduLen)
    {
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID PPP_HRPD_DL_DataInd(RLP_PPP_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    CDS_CDMA_HRPD_TRANS_DATA_STRU       stPppData;
    VOS_UINT32                          ulMinPppMntnLen;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;


    if (VOS_OK != PPPC_HRPD_CheckRpaPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    /* 可维可测 */
    PS_MEM_SET(&g_stPppRlpMntnInfo, 0, sizeof(g_stPppRlpMntnInfo));
    pstMntnInfo     = &g_stPppRlpMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MAX_MNTN_INFO_LEN);

    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = CTTF_PID_HRPD_FPA;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_RCV_DL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucStreamNum     = pstPppSdu->ucStreamNumber;
    pstMntnInfo->usHigherLayerProtocol  = pstPppSdu->ucHigherLayerProtocol;
    pstMntnInfo->ucNumReservLabels      = pstPppSdu->ucNumReservLabels;
    PS_MEM_CPY(pstMntnInfo->aucReservLabel, pstPppSdu->aucReservLabel, CTTF_HRPD_PA_MAX_NUM_RESERV_LABELS);
    pstMntnInfo->enRatMode       = PPPC_GetRatMode();
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);
    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();

    /* 如果是中继模式则直接调用CDS接口透传报文 */
    if ((TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode()) && (PS_FALSE == enIsDoingAccessAuth))
    {
        stPppData.ucPdnId  = 1;
        stPppData.ulSduLen = pstPppSdu->ulSduLen;
        stPppData.pstSdu   = pstPppSdu->pstSdu;
        pstPppSdu->pstSdu  = VOS_NULL_PTR;
        CDS_CDMA_HRPD_DL_DataInd(&stPppData, g_stPppContext.enModemId);

        CDS_CDMA_WakeupCds();

        return;
    }

    /* 将下行报文加入队列 */
    PPPC_HRPD_DlEnqueueData(pstPppSdu);

    g_stPppcDataQueueStats.ulHrpdDlFrameRcvCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_CheckCdsPackets
 功能描述  : 1X模式检查PPPC模块收到CDS的上行报文队列有效性
 输入参数  : pstPppSdu          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_1X_CheckCdsPackets
(
    const CDS_CDMA_1X_TRANS_DATA_STRU  *pstPppSdu
)
{
    TTF_MEM_ST                         *pstTTFMem;


    /* 空指针检查 */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* 上行TTF内存为空返回错误 */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* 上行帧长为0返回错误 */
    if (0 == pstPppSdu->ulSduLen)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID PPPC_1X_PullPacketEvent(const CDS_CDMA_1X_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stTmpSdu;
    VOS_UINT32                          ulMinPppMntnLen;


    if (VOS_OK != PPPC_1X_CheckCdsPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    /* 可维可测 */
    /* 1X模式PPPC模块收到CDS的上行报文跟踪 */
    PS_MEM_SET(&g_stPppCdsMntnInfo, 0, sizeof(g_stPppCdsMntnInfo));
    pstMntnInfo     = &g_stPppCdsMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MAX_MNTN_INFO_LEN);
    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = UEPS_PID_CDS;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_FRAME_RCV_UL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucPdnId         = pstPppSdu->ucPdnId;
    pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);

    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    /* 如果是中继模式则直接调用RLP接口透传报文 */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        PS_MEM_SET(&stTmpSdu, 0, sizeof(PPP_RLP_1X_TRANS_DATA_STRU));
        stTmpSdu.ucPdnId            = pstPppSdu->ucPdnId;
        stTmpSdu.ulSduLen           = pstPppSdu->ulSduLen;
        stTmpSdu.pstSdu             = pstPppSdu->pstSdu;
        stTmpSdu.enIpDataType       = IP_DATA_TYPE_NULL;
        stTmpSdu.ucTotalPppFrgmt    = 1;
        stTmpSdu.ucCurrPppFrgmt     = 0;

        CTTF_1X_RLP_ReverseLink_DataReq(&stTmpSdu);

        CTTF_1X_RLP_ReverseLink_TriggerDataProc();

        PPPC_INFO_LOG("The Dial Mode is relay!\n");

        return;
    }

    /* TODO comment out for UT*/
#if 0
    /* 检查PdnId */
    if (pstPppSdu->ucPdnId != g_stPppContext.ucPdnId)
    {
        TTF_MemFree(MSPS_PID_PPPC, pstPppSdu->pstSdu);
        PPPC_WARNING_LOG("Pdn Id is error!");
        return;
    }
#endif

    /* 将上行报文加入队列 */
    PPPC_1X_UlEnqueueData(pstPppSdu);


    g_stPppcDataQueueStats.ul1xUlIPDataRcvCnt++;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_HRPD_CheckCdsPackets
 功能描述  : HRPD模式检查PPPC模块收到CDS的上行报文队列有效性
 输入参数  : pstPppSdu          PPP报文
 输出参数  : 无
 返 回 值  : VOS_ERR or VOS_OK
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月16日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_HRPD_CheckCdsPackets
(
    const CDS_CDMA_HRPD_TRANS_DATA_STRU    *pstPppSdu
)
{
    TTF_MEM_ST                         *pstTTFMem;


    /* 空指针检查 */
    if(VOS_NULL_PTR == pstPppSdu)
    {
        PPPC_WARNING_LOG("pstPppSdu is NULL!\r\n");
        return VOS_ERR;
    }

    /* 上行TTF内存为空返回错误 */
    if (VOS_NULL_PTR == pstPppSdu->pstSdu)
    {
        PPPC_WARNING_LOG("TTF Mem is null!\r\n");
        return VOS_ERR;
    }

    /* 上行帧长为0返回错误 */
    if (0 == pstPppSdu->ulSduLen)
    {
        pstTTFMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTTFMem);
        PPPC_WARNING_LOG("TTF Mem len is 0!\r\n");
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID PPPC_HRPD_PullPacketEvent(const CDS_CDMA_HRPD_TRANS_DATA_STRU *pstPppSdu)
{
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType;
    VOS_UINT32                          ulMinPppMntnLen;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;
    TTF_MEM_ST                         *pstTtfMem;


    if (VOS_OK != PPPC_HRPD_CheckCdsPackets(pstPppSdu))
    {
        PPPC_WARNING_LOG("Invalid Para");
        return;
    }

    /* 可维可测 */
    /* HRPD模式PPPC模块收到CDS的上行报文跟踪 */
    PS_MEM_SET(&g_stPppCdsMntnInfo, 0, sizeof(g_stPppCdsMntnInfo));
    pstMntnInfo     = &g_stPppCdsMntnInfo;
    ulMinPppMntnLen = (VOS_UINT32)PS_MIN(pstPppSdu->ulSduLen, PPP_MAX_MNTN_INFO_LEN);
    pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
    pstMntnInfo->ulSenderPid     = UEPS_PID_CDS;
    pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pstMntnInfo->ulReceiverPid   = MSPS_PID_PPPC;
    pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
    pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_RCV_UL;
    pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
    pstMntnInfo->ucPdnId         = pstPppSdu->ucPdnId;
    pstMntnInfo->enRatMode       = PPPC_GetRatMode();
    pstMntnInfo->ucStreamNum     = PPPC_HRPD_GetStreamNumber();
    /* 获取stream2的绑定应用信息 */
    enAppType                    = g_stPppContext.stHrpdContext.aenApplicationType[1];
    pstMntnInfo->ucNumReservLabels = 1;
    pstMntnInfo->aucReservLabel[0] = PPPC_HRPD_PaAgentGetResvLabel(enAppType);
    (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
    (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, pstPppSdu->pstSdu->pData, ulMinPppMntnLen);

    PPP_MNTN_TRACE_MSG(pstMntnInfo);

    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        pstTtfMem = pstPppSdu->pstSdu;
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
        PPPC_WARNING_LOG("It is now doing access authentication!");
        return;
    }

    /* 如果是中继模式则直接调用RLP接口透传报文 */
    if (TAF_APS_PPP_CDATA_DIAL_MODE_RELAY == PPPC_GetDialMode())
    {
        stHrpdSdu.ucReservationLabel    = PPPC_HRPD_PA_BEST_EFFORT;
        stHrpdSdu.ucStreamNumber        = PPPC_HRPD_GetStreamNumber();
        stHrpdSdu.ulSduLen              = pstPppSdu->ulSduLen;
        stHrpdSdu.pstSdu                = pstPppSdu->pstSdu;
        stHrpdSdu.enStreamMode          = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;

        CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

        return;
    }

    /* 将上行报文加入队列 */
    PPPC_HRPD_UlEnqueueData(pstPppSdu);


    g_stPppcDataQueueStats.ulHrpdUlIPDataRcvCnt++;

    return;
}
VOS_UINT32 PPPC_ULSendNegoFrame(PMBUF_S *pstMBuf, VOS_UINT32 ulRPIndex)
{
    TTF_MEM_ST                         *pstTtfMem;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulTotalLen;
    VOS_UINT32                          ulMinPppMntnLen;
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;
    VOS_UINT8                           ucPdnId = 0;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;


    /* 内部调用pstMBuf不为空 */

    ulTotalLen  = (VOS_UINT32)pstMBuf->ulTotalDataLength;

    /* 协商报文较短，无需多次拷贝，只需拷贝一次，字节数小于1500Byte */
    pstTtfMem = PPPC_AdapterMBuftoTtfMemory(pstMBuf, TTF_MEM_POOL_ID_UL_DATA, 0, pstMBuf->ulTotalDataLength);
    if (VOS_NULL_PTR == pstTtfMem)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_894);
        /* 数据拷贝到TtfMemory失败也需要释放MBUF */
        PMBUF_Destroy(pstMBuf);
        return VOS_ERR;
    }

    PMBUF_Destroy(pstMBuf);

    enRatMode   = PPPC_GetRatMode();

    if (PPPC_RAT_MODE_1X == enRatMode)
    {
        ulRet     = PPPC_1X_GetPdnId((VOS_UINT8)ulRPIndex, &ucPdnId);
        if (VOS_OK != ulRet)
        {
            PPPC_WARNING_LOG2("Get PDN Id Fail! ulRPIndex:%d, ucPdnId:%d\r\n", ulRPIndex, ucPdnId);
            PMBUF_Destroy(pstMBuf);
            TTF_MemFree(MSPS_PID_PPPC, pstTtfMem);
            return VOS_ERR;
        }

        /* 上行数据报文发送到RLP */
        stRlpSdu.ucPdnId            = ucPdnId;
        stRlpSdu.enIpDataType       = IP_DATA_TYPE_NULL;
        stRlpSdu.ucTotalPppFrgmt    = 1;
        stRlpSdu.ucCurrPppFrgmt     = 0;
        stRlpSdu.ulSduLen           = ulTotalLen;
        stRlpSdu.pstSdu             = pstTtfMem;

        /* 可维可测 */
        /* 1X模式PPPC模块发送到RLP的上行报文跟踪 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(ulTotalLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = MSPS_PID_1X_RRLP;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_NEGO_UL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stRlpSdu.ucPdnId;
        pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stRlpSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

        /* 触发RLP处理上行报文 */
        CTTF_1X_RLP_ReverseLink_TriggerDataProc();

        /* 上行协商报文计数加1 */
        g_stPppcDataQueueStats.ul1xUlNegoSndCnt++;
    }
    else
    {
        /* 获取stream2的应用绑定信息 */
        pstHrpdContext  = &g_stPppContext.stHrpdContext;
        enAppType       = pstHrpdContext->aenApplicationType[1];

        stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber();
        stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
        stHrpdSdu.ulSduLen          = ulTotalLen;
        stHrpdSdu.pstSdu            = pstTtfMem;
        stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;

        /* 可维可测 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(ulTotalLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = CTTF_PID_HRPD_RPA;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_NEGO_UL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucStreamNum     = stHrpdSdu.ucStreamNumber;
        pstMntnInfo->ucNumReservLabels = 1;
        pstMntnInfo->aucReservLabel[0] = stHrpdSdu.ucReservationLabel;
        pstMntnInfo->enRatMode       = PPPC_GetRatMode();
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stHrpdSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

        /* 上行协商报文计数加1 */
        g_stPppcDataQueueStats.ulHrpdUlNegoSndCnt++;
    }

    return VOS_OK;
}
VOS_UINT32 PPPC_RcvCdsUlFrame
(
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstTtfMemory,
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode,
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
)
{
    TTF_MEM_ST                         *pstData;
    VOS_INT32                           lTotalLen;
    VOS_UINT32                          ulRet;
    VOS_UINT32                          ulRlpSduLen = 0;
    VOS_UINT32                          ulAccmValue = 0;
    VOS_UINT32                          ulAsynDataLen = 0;
    VOS_UINT32                          ulIndex     = 0;
    VOS_UINT8                           ucPppId  = 0;
    PPPINFO_S                          *pstPppInfo;
    PPP_RLP_1X_TRANS_DATA_STRU          stRlpSdu;
    PPP_RLP_HRPD_TRANS_DATA_STRU        stHrpdSdu;
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16 enAppType;
    VOS_UINT8                          *pucDstDataPtr;
    IP_DATA_TYPE_ENUM_UINT8             enIpDataType;


    if (VOS_NULL_PTR == pstTtfMemory)
    {
        PPPC_WARNING_LOG2("Input para is null!\r\n", ucPdnId, enRatMode);
        return VOS_ERR;
    }

    ulRet       = PPPC_GetPppIdByPdn(ucPdnId, &ucPppId);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_895);
        PPPC_WARNING_LOG1("Get Ppp Id Fail!\r\n", ucPppId);
        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);
        return VOS_ERR;
    }

    /* 解析具体的Ip包的数据类型，供rlp使用 */
    enIpDataType    = TTF_ParseIpDataType(MSPS_PID_PPPC, pstTtfMemory->pData,
        pstTtfMemory->usUsed, pstTtfMemory->ucDataPriority);

    pstPppInfo                  = &g_astPppPool[ucPppId];
    ulAccmValue    = (pstPppInfo->ulLocalAccm | pstPppInfo->ulRemoteAccm);

    /* 调用解析函数数据和信令分别处理 */
    ulRet   = FWD_PppEncap(ucPdnId, pstTtfMemory->pData, pstTtfMemory->usUsed,
                ulAccmValue, &ulAsynDataLen);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_897);
        PPPC_WARNING_LOG2("Encap PPP Fail!\r\n", ulAsynDataLen, ulRet);

        TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);

        return VOS_ERR;
    }

    /* 数据已处理完毕可以释放内存 */
    TTF_MemFree(MSPS_PID_PPPC, pstTtfMemory);

    lTotalLen  = (VOS_INT32)ulAsynDataLen;
    pucDstDataPtr   = PPP_GetUlEncapDataPtr();

    /* TCP ACK 提前相关参数赋值 */
    stRlpSdu.enIpDataType       = enIpDataType;
    stRlpSdu.ucTotalPppFrgmt    = (VOS_UINT8)((lTotalLen / PPPC_MAX_UL_ENCAP_LEN) + 1);
    pstData   = g_astUlEncapMem[ulIndex].pstDataPtr;

    while ((lTotalLen > 0) && (ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM)
        && (pstData != VOS_NULL_PTR))
    {
        ulRlpSduLen     = (VOS_UINT32)PS_MIN(lTotalLen, PPPC_MAX_UL_ENCAP_LEN);

        (VOID)PS_MEM_CPY(pstData->pData, pucDstDataPtr, ulRlpSduLen);
        pstData->usUsed = (VOS_UINT16)ulRlpSduLen;

        if (PPPC_RAT_MODE_1X == enRatMode)
        {
            /* 上行数据报文发送到RLP */
            stRlpSdu.ucPdnId            = ucPdnId;
            stRlpSdu.ucCurrPppFrgmt     = (VOS_UINT8)ulIndex;
            stRlpSdu.ulSduLen           = ulRlpSduLen;
            stRlpSdu.pstSdu             = pstData;
            PS_MEM_CPY(&(stRlpSdu.stUlDataInfo), pstUlDataInfo, sizeof(PS_DATA_EXT_INFO_STRU));
            PS_MEM_FREE(MSPS_PID_PPPC, pstUlDataInfo);

            CTTF_1X_RLP_ReverseLink_DataReq(&stRlpSdu);

            /* 上行IP包报文计数加1 */
            g_stPppcDataQueueStats.ul1xUlIPDataSndCnt++;
        }
        else
        {
            /* 获取stream2的应用绑定信息 */
            pstHrpdContext  = &g_stPppContext.stHrpdContext;
            enAppType       = pstHrpdContext->aenApplicationType[1];

            stHrpdSdu.ucStreamNumber    = PPPC_HRPD_GetStreamNumber();
            stHrpdSdu.ucReservationLabel= PPPC_HRPD_PaAgentGetResvLabel(enAppType);
            stHrpdSdu.ulSduLen          = ulRlpSduLen;
            stHrpdSdu.pstSdu            = pstData;
            stHrpdSdu.enStreamMode      = PPP_RLP_HRPD_STREAM_MODE_OCTET_BASED;

            CTTF_HRPD_RPA_AddToRlpTxQueue(&stHrpdSdu);

            /* 上行IP包报文计数加1 */
            g_stPppcDataQueueStats.ulHrpdUlIPDataSndCnt++;
        }

        g_astUlEncapMem[ulIndex].enPtrIsUsed    = PS_FALSE;
        g_astUlEncapMem[ulIndex].pstDataPtr     = VOS_NULL_PTR;

        lTotalLen           -= (VOS_INT32)ulRlpSduLen;
        pucDstDataPtr       += ulRlpSduLen;
        ulIndex++;
        pstData   = g_astUlEncapMem[ulIndex].pstDataPtr;
    }

    if (PPPC_RAT_MODE_1X == enRatMode)
    {
        /* 触发RLP处理上行报文 */
        CTTF_1X_RLP_ReverseLink_TriggerDataProc();
    }

    return VOS_OK;
}

/** **************************************************************************
  Generate high layer data info trace msg and send it.

  @param[in]    pstUlDataInfo   Pointer to struct containing high layer data info.

  @return   VOS_VOID
*/
/*
  History        :
  1.Date         : 2015-06-24
    Author       : d00314740
    Modification : Created function

*****************************************************************************/
VOS_VOID PPP_TraceDlHighLayerInfo
(
    PS_DATA_EXT_INFO_STRU              *pstUlDataInfo
)
{
    PPPC_TRACE_HIGH_LAYER_INFO_STRU     stHighLayerInfoMsg;

    stHighLayerInfoMsg.ulSenderPid      = MSPS_PID_PPPC;
    stHighLayerInfoMsg.ulReceiverPid    = MSPS_PID_PPPC;
    stHighLayerInfoMsg.ulSenderCpuId    = VOS_LOCAL_CPUID;
    stHighLayerInfoMsg.ulReceiverCpuId  = VOS_LOCAL_CPUID;
    stHighLayerInfoMsg.ulLength         = sizeof(PPPC_TRACE_HIGH_LAYER_INFO_STRU) - VOS_MSG_HEAD_LENGTH;
    stHighLayerInfoMsg.enMsgId          = ID_CTTF_1X_PPPC_TRACE_HIGH_LAYER_INFO_DL;
    PS_MEM_CPY(&(stHighLayerInfoMsg.stUlDataInfo), pstUlDataInfo, sizeof(PS_DATA_EXT_INFO_STRU));

    TTF_TRACE_MSG(&stHighLayerInfoMsg);

    return;
}


VOS_VOID PPP_SendRlpDlDatatoCds
(
    VOS_UINT16                          usStartSeq,
    VOS_UINT16                          usEndSeq,
    VOS_UINT8                           ucPdnId,
    TTF_MEM_ST                         *pstData,
    PPPC_RAT_MODE_ENUM_UINT8            ucRatMode
)
{
    CDS_CDMA_1X_TRANS_DATA_STRU         stPppSdu;
    PS_DATA_EXT_INFO_STRU               stDataInfo;
    CDS_CDMA_HRPD_TRANS_DATA_STRU       stHrpdSdu;
    CTTF_PPPC_TRACE_DATA_STRU          *pstMntnInfo;
    VOS_UINT32                          ulMinPppMntnLen;


    PPP_MemSet(&stPppSdu, 0, sizeof(stPppSdu));
    PPP_MemSet(&stHrpdSdu, 0, sizeof(stHrpdSdu));

    if (PPPC_RAT_MODE_1X == ucRatMode)
    {
        stPppSdu.ucPdnId    = ucPdnId;
        stPppSdu.ulSduLen   = pstData->usUsed;
        stPppSdu.pstSdu     = pstData;

        /* 性能优化，勾取trace */
        FWD_PppFillDataInfo(pstData->pData, &(stDataInfo));
        stDataInfo.usStartSN    = usStartSeq;
        stDataInfo.usEndSN      = usEndSeq;
        PPP_TraceDlHighLayerInfo(&(stDataInfo));

        /* 可维可测 */
        /* 1X模式PPPC模块发送到CDS的下行报文跟踪 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(stPppSdu.ulSduLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = UEPS_PID_CDS;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_1X_PPPC_TRACE_DATA_FRAME_SEND_DL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stPppSdu.ucPdnId;
        pstMntnInfo->enRatMode       = PPPC_RAT_MODE_1X;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stPppSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CDS_CDMA_1X_DL_DataInd(&stPppSdu, g_stPppContext.enModemId);
        CDS_CDMA_WakeupCds();

        /* 下行发送IP包计数加1 */
        g_stPppcDataQueueStats.ul1xDlIPDataSndCnt++;
    }
    else
    {
        stHrpdSdu.ucPdnId    = ucPdnId;
        stHrpdSdu.ulSduLen   = pstData->usUsed;
        stHrpdSdu.pstSdu     = pstData;

        /* 可维可测 */
        /* HRPD模式PPPC模块发送到CDS的下行报文跟踪 */
        PS_MEM_SET(&g_stPppInterMntnInfo, 0, sizeof(g_stPppInterMntnInfo));
        pstMntnInfo     = &g_stPppInterMntnInfo;
        ulMinPppMntnLen = (VOS_UINT32)PS_MIN(stHrpdSdu.ulSduLen, PPP_MAX_MNTN_INFO_LEN);
        pstMntnInfo->ulSenderCpuId   = VOS_LOCAL_CPUID;
        pstMntnInfo->ulSenderPid     = MSPS_PID_PPPC;
        pstMntnInfo->ulReceiverCpuId = VOS_LOCAL_CPUID;
        pstMntnInfo->ulReceiverPid   = UEPS_PID_CDS;
        pstMntnInfo->ulLength        = ulMinPppMntnLen + PPPC_OM_TRANS_DATA_OFFSET_LEN - VOS_MSG_HEAD_LENGTH;
        pstMntnInfo->enMsgId         = ID_CTTF_HRPD_PPPC_TRACE_DATA_FRAME_SEND_DL;
        pstMntnInfo->usVersion       = CTTF_PPPC_TRACE_DATA_VERSION;
        pstMntnInfo->ucPdnId         = stHrpdSdu.ucPdnId;
        pstMntnInfo->enRatMode       = ucRatMode;
        (VOID)PS_MEM_CPY((VOS_UINT8 *)&pstMntnInfo->stDataStats, (VOS_UINT8 *)&g_stPppcDataQueueStats, sizeof(PPP_DATA_Q_STAT_STRU));
        (VOID)PS_MEM_CPY(pstMntnInfo->aucValue, stHrpdSdu.pstSdu->pData, ulMinPppMntnLen);
        PPP_MNTN_TRACE_MSG(pstMntnInfo);

        CDS_CDMA_HRPD_DL_DataInd(&stHrpdSdu, g_stPppContext.enModemId);
        CDS_CDMA_WakeupCds();

        /* 下行发送IP包计数加1 */
        g_stPppcDataQueueStats.ulHrpdDlIPDataSndCnt++;
    }

    return;
}


#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
VOS_VOID PPPC_ProcAsFrmDataInd(struct MsgCB * pMsg)
{
    HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU    *pstHdlcEnable;
    VOS_UINT16                               usPppId;
    VOS_UINT16                               usProtocol;
    TTF_MEM_ST                              *pstMem;


    pstHdlcEnable = (HDLC_PROC_AS_FRM_PACKET_IND_MSG_STRU*)pMsg;

    usPppId       = pstHdlcEnable->usPppId;
    usProtocol    = pstHdlcEnable->usProtocol;
    pstMem        = pstHdlcEnable->pstMem;


    PPPC_HDLC_HARD_ProcAsFrmPacket(usPppId, usProtocol, pstMem);

    return;
}

#endif



VOS_VOID PPPC_AwakeSelfReachMaxProcTimeoutProc(VOS_VOID)
{
    g_hReachMaxProcTimer = VOS_NULL_PTR;
    g_enIsReachTimeout   = PS_TRUE;
    PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

    return;
}


TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 PPPC_GetDialMode(VOS_VOID)
{
    return g_stPppContext.enDialMode;
}

/*****************************************************************************
 函 数 名  : PPPC_SetDialMode
 功能描述  : 设置拨号模式，只支持中继和网络模式
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年7月01日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_SetDialMode(TAF_APS_PPP_CDATA_DIAL_MODE_ENUM_UINT8 enDialMode)
{
    g_stPppContext.enDialMode = enDialMode;
    return;
}


PPPC_RAT_MODE_ENUM_UINT8 PPPC_GetRatMode(VOS_VOID)
{
    return g_stPppContext.enRatMode;
}


VOS_VOID PPPC_SetRatMode(PPPC_RAT_MODE_ENUM_UINT8 enRatMode)
{
    g_stPppContext.enRatMode = enRatMode;
    return;
}



VOS_UINT32 PPPC_GetCurrentPdnId(VOS_UINT8 *pucPdnId)
{
    PPPC_DATA_LINK_NODE_STRU           *pstApsCurrHeadNode  = VOS_NULL_PTR;
    PPPC_RAT_MODE_ENUM_UINT8            enRateMode          = PPPC_RAT_MODE_BUTT;

    enRateMode  = PPPC_GetRatMode();
    if (PPPC_RAT_MODE_BUTT >= enRateMode)
    {
        pstApsCurrHeadNode = (PPPC_DATA_LINK_NODE_STRU *)TTF_LinkPeekHead(
                    MSPS_PID_PPPC, &g_stApsCmdLink);

        if (VOS_NULL_PTR != pstApsCurrHeadNode)
        {
            *pucPdnId = pstApsCurrHeadNode->ucPdnId;

            return VOS_OK;
        }
        else
        {
            PPPC_WARNING_LOG("Node is null\r\n");
        }
    }
    else
    {
        /* Invalid rate mode */
        PPPC_WARNING_LOG1("Invalid rate mode!enRateMode\r\n", enRateMode);
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_1X_GetPdnId
 功能描述  : 1X模式获取当前的PDN ID
 输入参数  : VOS_UINT8 ucPppId
 输出参数  : VOS_UINT8 *pucPdnId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_1X_GetPdnId(VOS_UINT8 ucPppId, VOS_UINT8 *pucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucBit;


    pstPppContext   = &g_stPppContext;
    for (ucBit = 0; ucBit < A11_MAX_PDN_NUM; ++ucBit)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucBit))
        {
            *pucPdnId = ucBit;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_GetCurrentPppId
 功能描述  : 获取PPP Id
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年02月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT8 PPPC_GetCurrentPppId(VOS_VOID)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucBit;

    pstPppContext   = &g_stPppContext;

    /* 正在与BSC进行接入鉴权,PPP ID使用默认值0 */
    if (PS_TRUE == g_stPppContext.stHrpdContext.enIsDoingAcessAuth)
    {
        return PPPC_PPP_ID_FOR_ACCESS_AUTH;
    }

    for (ucBit = PPPC_PPP_ID_MIN; ucBit <= PPPC_PPP_ID_MAX; ++ucBit)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, ucBit))
        {
            break;
        }
    }

    if (PPPC_PPP_ID_MAX < ucBit)
    {
        return PPPC_PPP_ID_MIN;
    }

    return ucBit;
}
VOS_UINT32 PPPC_1XHrpdGetPdnId(VOS_UINT16 usPppId, VOS_UINT8 *pucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT32                          ulPdnIndex;


    pstPppContext   = &g_stPppContext;

    for (ulPdnIndex = 0; ulPdnIndex < A11_MAX_PDN_NUM; ulPdnIndex++)
    {
        if (0 != TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[usPppId], ulPdnIndex))
        {
            *pucPdnId = (VOS_UINT8)ulPdnIndex;

            return VOS_OK;
        }
    }

    PPP_DBG_ERR_CNT(PPP_PHERR_806);

    PPPC_WARNING_LOG1("Get Pdn Id Fail!ucPppId\r\n", usPppId);

    return VOS_ERR;
}


VOS_UINT32 PPPC_GetPppIdByPdn(VOS_UINT8 ucPdnId, VOS_UINT8 *pucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppIdIndex;


    /* 检查PDN id */
    pstPppContext   = &g_stPppContext;
    for (ucPppIdIndex = PPPC_PPP_ID_MIN; ucPppIdIndex <= PPPC_PPP_ID_MAX; ++ucPppIdIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppIdIndex], ucPdnId))
        {
            *pucPppId = ucPppIdIndex;
            if ((PPPC_PPP_ID_MIN != ucPppIdIndex) && (0 != ucPppIdIndex))
            {
                /* PPP ID不是1或0时都是异常的 */
                PPPC_WARNING_LOG4("ucPppId %d,ucPdnId %d,ppp1 %d ppp0 %d\r\n",
                    ucPppIdIndex, ucPdnId, pstPppContext->aulPppIdMapPdnId[1], pstPppContext->aulPppIdMapPdnId[0]);
            }
            return VOS_OK;
        }
    }

    PPPC_WARNING_LOG1("Get Ppp Id Fail!ucPdnId\r\n", ucPdnId);

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_IsPdnIdUnique
 功能描述  : 判断当前PDN ID是不是唯一的
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月05日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_IsPdnIdUnique(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppId;
    VOS_UINT8                           ucBit;
    VOS_UINT8                           ucPdnNum = 0;


    if (VOS_OK != PPPC_GetPppIdByPdn(ucPdnId, &ucPppId))
    {
        return VOS_ERR;
    }

    pstPppContext   = &g_stPppContext;
    for (ucBit = 0; ucBit < A11_MAX_PDN_NUM; ++ucBit)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucBit))
        {
            ++ucPdnNum;
        }
    }
    if (PPPC_PDN_ID_UNIQUE == ucPdnNum)
    {
        return VOS_OK;
    }
    return VOS_ERR;
}


VOS_VOID PPPC_MappingPppIdandPdnId(VOS_UINT8 ucPppId, VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* 记录PPP Id和Pdn Id的映射关系 */
    TTF_SET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucPdnId);

    return;
}
VOS_VOID PPPC_ClearMappingByPppId(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;

    pstPppContext   = &g_stPppContext;
    pstPppContext->aulPppIdMapPdnId[ucPppId] = 0;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearMappingByPdnId
 功能描述  : 根据Pdn Id清除PPP Id和Pdn Id之间的映射关系
 输入参数  :
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年05月27日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_VOID PPPC_ClearMappingByPdnId(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppId;


    pstPppContext   = &g_stPppContext;
    for (ucPppId = PPPC_PPP_ID_MIN; ucPppId <= PPPC_PPP_ID_MAX; ++ucPppId)
    {
        TTF_CLEAR_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppId], ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckPdnId
 功能描述  : 检查PDN id是否有效
 输入参数  : VOS_UINT8 ucPdnId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_CheckPdnId(VOS_UINT8 ucPdnId)
{
    /* PDN ID的取值范围为0~14 */
    if (ucPdnId >= A11_MAX_PDN_NUM)
    {
        PPPC_WARNING_LOG1("PDN id is error! PDN Id = %d\r\n", ucPdnId);
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckRateMode
 功能描述  : 检查Rate mode是否有效
 输入参数  : TAF_APS_PPP_RAT_MODE_ENUM_UINT8 enMode
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_CheckRateMode(TAF_APS_PPP_RAT_MODE_ENUM_UINT8 enMode)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    switch(enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
        case TAF_APS_PPP_RAT_MODE_HRPD:
            ulRet = VOS_OK;
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_CheckPdnType
 功能描述  : 检查Pdn Type是否有效
 输入参数  : TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_CheckPdnType(TAF_APS_PPP_ADDR_TYPE_ENUM_UINT8 enPdnType)
{
    VOS_UINT32                          ulRet = VOS_ERR;
    switch(enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            ulRet = VOS_OK;
            break;
        default:
            break;
    }

    return ulRet;
}

/*****************************************************************************
 函 数 名  : PPPC_IsPdnIdUsing
 功能描述  : 检查PDN id是否在使用中
 输入参数  : VOS_UINT8 ucPdnId
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsPdnIdUsing(VOS_UINT8 ucPdnId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppIdIndex;


    /* 检查PDN id */
    pstPppContext   = &g_stPppContext;
    for (ucPppIdIndex = PPPC_PPP_ID_MIN; ucPppIdIndex <= PPPC_PPP_ID_MAX; ++ucPppIdIndex)
    {
        if (PPPC_BIT_MASK_ON == TTF_GET_A_BIT(pstPppContext->aulPppIdMapPdnId[ucPppIdIndex], ucPdnId))
        {
            return PS_TRUE;
        }
    }
    return PS_FALSE;
}
PS_BOOL_ENUM_UINT8 PPPC_IsDoingAccessAuth(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.enIsDoingAcessAuth;
}


VOS_VOID PPPC_ChangeAccessAuthState(PS_BOOL_ENUM_UINT8 enIsDoingAcessAuth)
{
    g_stPppContext.stHrpdContext.enIsDoingAcessAuth = enIsDoingAcessAuth;
}

/*****************************************************************************
 函 数 名  : PPPC_AddPppId
 功能描述  : 新增一个PppId
 输入参数  : 无
 输出参数  : VOS_UINT8 *pucPppId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_AddPppId(VOS_UINT8 *pucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;
    VOS_UINT8                           ucPppIdBit;

    pstPppContext   = &g_stPppContext;
    for (ucPppIdBit = PPPC_PPP_ID_MIN; ucPppIdBit <= PPPC_PPP_ID_MAX; ++ucPppIdBit)
    {
        if (PPPC_BIT_MASK_EMPTY == TTF_GET_A_BIT(pstPppContext->ulPppIdBitMask, ucPppIdBit))
        {
            TTF_SET_A_BIT(pstPppContext->ulPppIdBitMask, ucPppIdBit);
            *pucPppId = ucPppIdBit;
            return VOS_OK;
        }
    }

    return VOS_ERR;
}

/*****************************************************************************
 函 数 名  : PPPC_DeletePppId
 功能描述  : 删除一个PppId
 输入参数  : 无
 输出参数  : VOS_UINT8 ucPppId
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_DeletePppId(VOS_UINT8 ucPppId)
{
    PPPC_CONTEXT_INFO_STRU             *pstPppContext;


    pstPppContext   = &g_stPppContext;

    /* 对PPP Id的有效性进行检查 */
    TTF_CLEAR_A_BIT(pstPppContext->ulPppIdBitMask, ucPppId);
    pstPppContext->aulPppIdMapPdnId[ucPppId] = 0;

    return VOS_OK;
}
VOS_UINT32 PPPC_SndUlDataNotify(VOS_VOID)
{
    PPPC_DATA_PROC_NOTIFY_MSG          *pMsg;
    VOS_INT32                           lLockKey;


    /*申请消息内存:*/
    pMsg = (PPPC_DATA_PROC_NOTIFY_MSG *) PS_ALLOC_MSG_WITH_HEADER_LEN(
                MSPS_PID_PPPC, sizeof(PPPC_DATA_PROC_NOTIFY_MSG));

    if (VOS_NULL_PTR == pMsg)
    {
        /*打印出错信息---申请消息包失败:*/
        PPPC_WARNING_LOG("PPPC_SndDlDataNotify:Alloc message FAIL!\r\n" );
        PPP_DBG_ERR_CNT(PPP_PHERR_793);
        return VOS_ERR;
    }

    /*填写消息内容:*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = MSPS_PID_PPPC;
    pMsg->enMsgType       = PPPC_UL_DATA_PROC_NOTIFY;

    /* 队列加锁 */
    lLockKey = VOS_SplIMP();

    g_stDataQNotifyCnt.ulNotifyMsgCnt++;

    /* 队列操作完成解锁 */
    VOS_Splx(lLockKey);

    /*发送消息:*/
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pMsg))
    {
        /*打印警告信息---发送消息失败:*/
        PPPC_WARNING_LOG("SEND PPP_DATA_PROC_NOTIFY msg FAIL!\r\n");

        /* 队列加锁 */
        lLockKey = VOS_SplIMP();

        g_stDataQNotifyCnt.ulNotifyMsgCnt = 0;

        /* 队列操作完成解锁 */
        VOS_Splx(lLockKey);
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_UINT32 PPPC_SndDlDataNotify(VOS_VOID)
{
    PPPC_DATA_PROC_NOTIFY_MSG          *pMsg;
    VOS_INT32                           lLockKey;


    /*申请消息内存:*/
    pMsg = (PPPC_DATA_PROC_NOTIFY_MSG *) PS_ALLOC_MSG_WITH_HEADER_LEN(
                MSPS_PID_PPPC, sizeof(PPPC_DATA_PROC_NOTIFY_MSG));

    if (VOS_NULL_PTR == pMsg)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_802);
        /*打印出错信息---申请消息包失败:*/
        PPPC_WARNING_LOG("PPPC_SndDlDataNotify:Alloc message FAIL!\r\n" );
        return VOS_ERR;
    }

    /*填写消息内容:*/
    pMsg->ulReceiverCpuId = VOS_LOCAL_CPUID;
    pMsg->ulReceiverPid   = MSPS_PID_PPPC;
    pMsg->enMsgType       = PPPC_DL_DATA_PROC_NOTIFY;

    /* 队列加锁 */
    lLockKey = VOS_SplIMP();

    g_stDataQNotifyCnt.ulNotifyMsgCnt++;

    /* 队列操作完成解锁 */
    VOS_Splx(lLockKey);

    /*发送消息:*/
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pMsg))
    {
        /*打印警告信息---发送消息失败:*/
        PPPC_WARNING_LOG("SEND PPP_DATA_PROC_NOTIFY msg FAIL!\r\n");

        /* 队列加锁 */
        lLockKey = VOS_SplIMP();

        g_stDataQNotifyCnt.ulNotifyMsgCnt = 0;

        /* 队列操作完成解锁 */
        VOS_Splx(lLockKey);
        return VOS_ERR;
    }

    return VOS_OK;
}
VOS_VOID PPPC_ApsCmdLinkInit(VOS_VOID)
{
    TTF_LinkInit(MSPS_PID_PPPC, &g_stApsCmdLink);

    return;
}


VOS_VOID PPPC_ClearApsCmdLinkNode(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    while (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ClearEhsmPdnCmdLinkNode
 功能描述  : 清除EHSM发给PPP的PDN消息链表
 输入参数  :
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ClearEhsmPdnCmdLinkNode(VOS_UINT8 ucPdnId)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstNextNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    while (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        pstNextNode         = VOS_NULL_PTR;
        TTF_LinkPeekNext(MSPS_PID_PPPC, pstEhsmPppCmdLink, (TTF_NODE_ST *)pstCurrentHeadNode, (TTF_NODE_ST **)&pstNextNode);

        if (pstCurrentHeadNode->ucPdnId == ucPdnId)
        {
            TTF_LinkRemoveNode(MSPS_PID_PPPC, pstEhsmPppCmdLink, (TTF_NODE_ST *)pstCurrentHeadNode);
            PPP_Free(pstCurrentHeadNode);
        }
        pstCurrentHeadNode  = pstNextNode;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SetIpCapability
 功能描述  : 设置IP地址类型
 输入参数  : VOS_UINT8 ucPdnType
 输出参数  : PPPINFO_S *pstPppInfo
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-12
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SetIpCapability(VOS_UINT8 ucPdnType, PPPINFO_S *pstPppInfo)
{
    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is NULL.");
        return;
    }

    switch(ucPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV4;
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_IPV6;
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            pstPppInfo->ucIpCapability = PDSN_PPP_IPTYE_ALL;
            break;
        default:
            PPPC_WARNING_LOG1("ucPdnType is error. %d", ucPdnType);
            break;
    }

    return;
}


VOS_VOID PPPC_ClearUlEncapMem(VOS_VOID)
{
    VOS_UINT32                          ulIndex;


    for (ulIndex = 0; ulIndex < PPPC_MAX_UL_ENCAP_MEM_NUM; ulIndex++)
    {
        if (VOS_NULL_PTR != g_astUlEncapMem[ulIndex].pstDataPtr)
        {
            TTF_MemFree(MSPS_PID_PPPC, g_astUlEncapMem[ulIndex].pstDataPtr);
        }
    }

    PS_MEM_SET(&g_astUlEncapMem[0], 0, sizeof(g_astUlEncapMem));

    return;
}


VOS_VOID PPPC_SetupPpp(VOS_UINT8 ucPppId)
{
    PPP_LUPPARA_S                       stPPPMsg;
    VOS_UINT32                          ulRet;


    ulRet = PPP_StartNegoTimer();
    if (VOS_OK != ulRet)
    {
        PPPC_WARNING_LOG2("Start timer fail!\r\n", ucPppId, ulRet);
    }

    PPP_MemSet(&stPPPMsg, 0, sizeof(PPP_LUPPARA_S));

    /* ulRPIndex指示PPP Id,从1开始才是合法的,当前只能是1,后面需要从TAF传过来 */
    ulRet = Ppp_UsmIoCtl(ucPppId, PPP_ISLUP, (CHAR *)&stPPPMsg);
    if (VOS_OK != ulRet)
    {
        PPP_DBG_ERR_CNT(PPP_PHERR_811);
        PPPC_WARNING_LOG2("notify ppp fail,ulRpIndex, ulRet", ucPppId, ulRet);
    }

    return;
}
VOS_VOID PPPC_LinkDown
(
    VOS_UINT8                           ucPppId,
    VOS_UINT32                          ulLcpSendFlag
)
{
    PPPINFO_S                              *pstPppInfo;


    pstPppInfo                  = &g_astPppPool[ucPppId];

    if(VOS_TRUE == ulLcpSendFlag)
    {
        PPP_DBG_OK_CNT(PPP_PHOK_948);
        PPPC_INFO_LOG("[ppp]PPP_A11MsgProc: (VOS_TRUE == pstA11Msg->ucLcpSendFlag)\r\n ");

        PPP_DBG_OK_CNT(PPP_PHOK_949);
        pstPppInfo->bFailFlag = PPPA11DOWN;
        PPP_LCP_NegotiationDown(pstPppInfo->pstLcpInfo);
        return;
    }
    else
    {
        PPP_DBG_OK_CNT(PPP_PHOK_951);
        pstPppInfo->bFailFlag = PPPA11DOWNNOLCPTER;

        (VOID)PPP_Shell_ISLIoCtl(ucPppId, PPP_ISLDOWN, (CHAR *)VOS_NULL_PTR);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_FillPdnInfo
 功能描述  : 拷贝信息到PDN context
 输入参数  : PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-05
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_FillPdnInfo
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode
)
{
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    ulRet = PPP_GetPDNContextByPDNID(pstCurrentHeadNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstCurrentHeadNode->ucPdnId);
        return;
    }

    pstPDNContext->stEhrpd.ucPdnId      = pstCurrentHeadNode->ucPdnId;
    pstPDNContext->stEhrpd.enAttachType = pstCurrentHeadNode->stEhsmCmdNode.enAttachType;
    pstPDNContext->stEhrpd.enPdnType    = pstCurrentHeadNode->stEhsmCmdNode.enPdnType;
    pstPDNContext->stEhrpd.ucAddressAllocCause    = pstCurrentHeadNode->stEhsmCmdNode.ucAddressAllocCause;

    /* 拷贝APN */
    VOS_StrNCpy((VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝PDN Address */
    VOS_StrNCpy((VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    VOS_StrNCpy((VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco),
        (VOS_INT8 *)&(pstCurrentHeadNode->stEhsmCmdNode.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    VOS_StrNCpy((VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstCurrentHeadNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_AttachReqMsgNodeProc
 功能描述  : PPPC模块Attach Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_AttachReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 存储收到激活消息时APS的PID和接入模式 */
    g_stPppContext.ulSendPid = pstCurrentHeadNode->ulSenderPid;
    PPPC_SetRatMode(PPPC_RAT_MODE_EHRPD);

    /* 考虑对冲场景，必须保证串行处理 */
    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        PPP_HDLC_HARD_SetUp(pstCurrentHeadNode->ucPppId);

#endif
        PPPC_FillPdnInfo(pstCurrentHeadNode);
        /* PPP发起建链 */
        PPPC_SetupPpp(pstCurrentHeadNode->ucPppId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_DetachReqMsgNodeProc
 功能描述  : PPPC模块Detach Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_DetachReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    VOS_UINT32                              ulLcpSendFlag;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    /* 考虑对冲场景，必须保证串行处理 */
    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }


    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

        /* 此时需要发送ppp terminate协商报文 */
        ulLcpSendFlag                    = 1;

        /* PPP发起PPP去激活 */
        PPPC_LinkDown(pstCurrentHeadNode->ucPppId, ulLcpSendFlag);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_PdnConnectReqMsgNodeProc
 功能描述  : PPPC模块PDN Connect Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_PdnConnectReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstCurrentHeadNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                  enIsHandling    = PS_FALSE;
    PS_BOOL_ENUM_UINT8                  enIsPdnOpen     = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }


    /* 查询当前PDN ID状态是否已经连接上 */
    enIsPdnOpen = PPP_VSNCP_IsPDNOpened(pstCurrentHeadNode->ucPdnId);
    if (PS_TRUE == enIsPdnOpen)
    {
        pstCurrentHeadNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                                MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPPC_SendPdnConnectCnf(pstCurrentHeadNode, VOS_OK);

        PPP_Free(pstCurrentHeadNode);

        return;
    }

    /* 存储收到激活消息时APS的PID */
    g_stPppContext.ulSendPid = pstCurrentHeadNode->ulSenderPid;

    /* 考虑对冲场景，必须保证串行处理 */
    enIsHandling    = pstCurrentHeadNode->enIsHandling;
    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

        PPPC_FillPdnInfo(pstCurrentHeadNode);
        /* PPP发起VSNCP协商 */
        PPP_VSNCP_NotifyVSNCPStart(&g_astPppPool[pstCurrentHeadNode->ucPppId], pstCurrentHeadNode->ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_PdnDisconnectReqMsgNodeProc
 功能描述  : PPPC模块PDN Disconnect Request消息节点处理(为保证串行处理将消息按节点入队)
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_PdnDisconnectReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;


    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    /* 考虑对冲场景，必须保证串行处理 */
    if (VOS_NULL_PTR != pstCurrentHeadNode)
    {
        enIsHandling    = pstCurrentHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }


    if (PS_FALSE == enIsHandling)
    {
        pstCurrentHeadNode->enIsHandling = PS_TRUE;

        /* PPP发起VSNCP去激活 */
        PPP_VSNCP_NotifyVSNCPStop(&g_astPppPool[pstCurrentHeadNode->ucPppId], pstCurrentHeadNode->ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmMsgNodeProc
 功能描述  : PPPC模块消息节点处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmMsgNodeProc(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstEhsmPppCmdLink;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    PS_BOOL_ENUM_UINT8                      enIsDoingAccessAuth = PS_FALSE;


    /* 如果当前正在进行接入鉴权,不能同时做PPP的业务协商 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        PPPC_WARNING_LOG("It is now doing access authentication!\r\n");
        return;
    }

    pstEhsmPppCmdLink   = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("EHSM PPP Cmd Link is Null!\r\n");
        return;
    }

    enMsgType           = pstCurrentHeadNode->stEhsmCmdNode.enMsgType;
    switch(enMsgType)
    {
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            PPPC_AttachReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            PPPC_DetachReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            PPPC_PdnConnectReqMsgNodeProc();

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            PPPC_PdnDisconnectReqMsgNodeProc();

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmAttachReqProc
 功能描述  : PPPC模块处理Ehsm的Attach请求
 输入参数  : CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmAttachReqProc
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    PPPINFO_S                          *pstPppInfo;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;


    /* 内部调用保证指针入参非空 */

    /* 检查PDN id */
    if (VOS_ERR == PPPC_CheckPdnId(pstAttachReq->ucPdnId))
    {
        PPPC_RespEhsmAttachFail(pstAttachReq);
        PPPC_WARNING_LOG1("Pdn Id is too large! PdnId = %d.", pstAttachReq->ucPdnId);
        return;
    }

    /* 收到EHSM发给PPP的Attach消息直接入队 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid                = pstAttachReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType    = pstAttachReq->enMsgId;
    pstEhsmMsgNode->usOpId                     = pstAttachReq->usOpId;
    pstEhsmMsgNode->ucPdnId                    = pstAttachReq->ucPdnId;
    pstEhsmMsgNode->stEhsmCmdNode.enPdnType    = pstAttachReq->enPdnType;
    pstEhsmMsgNode->stEhsmCmdNode.enAttachType = pstAttachReq->enAttachType;
    pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause = pstAttachReq->ucAddressAllocCause;
    pstEhsmMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_AddPppId(&pstEhsmMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Add Ppp Id fail!");
        PPP_Free(pstEhsmMsgNode);
        PPPC_RespEhsmAttachFail(pstAttachReq);
        return;
    }

    pstPppCont  = &g_stPppContext;

    /* 拷贝用户名 */
    ulUserNameLen    = VOS_StrNLen((VOS_INT8 *)pstAttachReq->aucUserName,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_INT8 *)pstPppCont->aucUserName,
        (VOS_INT8 *)pstAttachReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* 拷贝密码 */
    ulPasswordLen    = VOS_StrNLen((VOS_INT8 *)pstAttachReq->aucPassword,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_INT8 *)pstPppCont->aucPassword,
        (VOS_INT8 *)pstAttachReq->aucPassword, ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    /* 拷贝APN */
    PS_MEM_CPY(&(pstEhsmMsgNode->stEhsmCmdNode.stApn),
        &(pstAttachReq->stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝PDN Address */
    VOS_StrNCpy((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPdnAddress),
        (VOS_INT8 *)&(pstAttachReq->stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    VOS_StrNCpy((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPco),
        (VOS_INT8 *)&(pstAttachReq->stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    VOS_StrNCpy((VOS_INT8 *)pstEhsmMsgNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstAttachReq->aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    pstEhsmPppCmdLink           = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    /* 存储modem id */
    g_stPppContext.enModemId    = pstAttachReq->enModemId;

    /* 映射ppp id和Pdn id */
    PPPC_MappingPppIdandPdnId(pstEhsmMsgNode->ucPppId, pstAttachReq->ucPdnId);

    PPPC_EhsmMsgNodeProc();

    pstPppInfo                  = &g_astPppPool[pstEhsmMsgNode->ucPppId];

    pstPppInfo->bEhrpdUser      = VOS_TRUE;

    /* ppp id映射到PPP内部需要自增 */
    pstPppInfo->ulRPIndex   = pstEhsmMsgNode->ucPppId;

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmDetachReqProc
 功能描述  : PPPC模块处理Ehsm的Detach请求
 输入参数  : pstDetachReq    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmDetachReqProc
(
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstDetachReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;


    /* 内部调用保证指针入参非空 */

    /* 收到APS发给PPP的去激活消息直接入队 */
    pstEhsmMsgNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid             = pstDetachReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType = pstDetachReq->enMsgId;
    pstEhsmMsgNode->usOpId                  = pstDetachReq->usOpId;
    pstEhsmMsgNode->enIsHandling            = PS_FALSE;

    pstEhsmMsgNode->ucPppId                 = PPPC_GetCurrentPppId();

    pstEhsmPppCmdLink                       = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmPdnConnectReqProc
 功能描述  : PPPC模块处理Ehsm的PDN Connect请求
 输入参数  : pstPdnConnectReq    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnConnectReqProc
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstPdnConnectReq->ucPdnId))
    {
        PPPC_RespEhsmPdnConnectFail(pstPdnConnectReq);
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    /* 收到APS发给PPP的激活消息直接入队 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc EHSM Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid                = pstPdnConnectReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType    = pstPdnConnectReq->enMsgId;
    pstEhsmMsgNode->usOpId                     = pstPdnConnectReq->usOpId;
    pstEhsmMsgNode->ucPdnId                    = pstPdnConnectReq->ucPdnId;
    pstEhsmMsgNode->stEhsmCmdNode.enAttachType = pstPdnConnectReq->enAttachType;
    pstEhsmMsgNode->stEhsmCmdNode.enPdnType    = pstPdnConnectReq->enPdnType;
    pstEhsmMsgNode->stEhsmCmdNode.ucAddressAllocCause    = pstPdnConnectReq->ucAddressAllocCause;
    pstEhsmMsgNode->enIsHandling               = PS_FALSE;

    pstPppCont = &g_stPppContext;

    /* 拷贝用户名 */
    ulUserNameLen    = VOS_StrNLen((VOS_INT8 *)pstPdnConnectReq->aucUserName,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_INT8 *)pstPppCont->aucUserName,
        (VOS_INT8 *)pstPdnConnectReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* 拷贝密码 */
    ulPasswordLen    = VOS_StrNLen((VOS_INT8 *)pstPdnConnectReq->aucPassword,
                            CNAS_CTTF_EHRPD_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_INT8 *)pstPppCont->aucPassword,
        (VOS_INT8 *)pstPdnConnectReq->aucPassword, ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    /* 拷贝APN */
    PS_MEM_CPY(&(pstEhsmMsgNode->stEhsmCmdNode.stApn),
        &(pstPdnConnectReq->stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝PDN Address */
    VOS_StrNCpy((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPdnAddress),
        (VOS_INT8 *)&(pstPdnConnectReq->stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    VOS_StrNCpy((VOS_INT8 *)&(pstEhsmMsgNode->stEhsmCmdNode.stPco),
        (VOS_INT8 *)&(pstPdnConnectReq->stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    VOS_StrNCpy((VOS_INT8 *)pstEhsmMsgNode->stEhsmCmdNode.aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPdnConnectReq->aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);


    pstEhsmMsgNode->ucPppId      = PPPC_GetCurrentPppId();

    pstEhsmPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    /* 映射ppp id和Pdn id */
    PPPC_MappingPppIdandPdnId(pstEhsmMsgNode->ucPppId, pstPdnConnectReq->ucPdnId);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmPdnDisconnectReqProc
 功能描述  : PPPC模块处理Ehsm的PDN Disconnect请求
 输入参数  : pMsg    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnDisconnectReqProc
(
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstPdnDisconnectReq->ucPdnId))
    {
        PPPC_RespEhsmPdnDisconnectFail(pstPdnDisconnectReq);
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    /* 收到APS发给PPP的去激活消息直接入队 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstEhsmMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstEhsmMsgNode->stNode));

    pstEhsmMsgNode->ulSenderPid             = pstPdnDisconnectReq->ulSenderPid;
    pstEhsmMsgNode->stEhsmCmdNode.enMsgType = pstPdnDisconnectReq->enMsgId;
    pstEhsmMsgNode->usOpId                  = pstPdnDisconnectReq->usOpId;
    pstEhsmMsgNode->ucPdnId                 = pstPdnDisconnectReq->ucPdnId;
    pstEhsmMsgNode->enIsHandling            = PS_FALSE;

    if (VOS_OK != PPPC_GetPppIdByPdn(pstEhsmMsgNode->ucPdnId, &pstEhsmMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Get Ppp Id fail!");
        PPP_Free(pstEhsmMsgNode);
        PPPC_RespEhsmPdnDisconnectFail(pstPdnDisconnectReq);
        return;
    }

    pstEhsmPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstEhsmPppCmdLink, &(pstEhsmMsgNode->stNode));

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmPdnDisconnectIndProc
 功能描述  : PPPC模块处理EHSM的本地去激活命令
 输入参数  : pstDeActInd    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmPdnDisconnectIndProc
(
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU *pstPdnDisconnectInd
)
{
    VOS_UINT8                               ucPppId;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstPdnDisconnectInd->ucPdnId))
    {
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    if (VOS_OK != PPPC_GetPppIdByPdn(pstPdnDisconnectInd->ucPdnId, &ucPppId))
    {
        PPPC_WARNING_LOG("Get Ppp Id fail!\r\n");
        return;
    }

    PPPC_ClearEhsmPdnCmdLinkNode(pstPdnDisconnectInd->ucPdnId);
    PPPC_ClearMappingByPdnId(pstPdnDisconnectInd->ucPdnId);

    /* 全局变量 PDN相关信息的清除 */
    PPP_VSNCP_ClearPdnContext(pstPdnDisconnectInd->ucPdnId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_EhsmDetachIndProc
 功能描述  : PPPC模块处理EHSM的本地去激活命令
 输入参数  : pstDetachInd    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_EhsmDetachIndProc(CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU *pstDetachInd)
{
    PPPINFO_S                              *pstPppInfo;
    VOS_UINT8                               ucPppId;


    /* 内部调用保证指针入参非空 */

    ucPppId                 = PPPC_GetCurrentPppId();
    pstPppInfo              = &g_astPppPool[ucPppId];

    /* 必须无条件清除本地资源 */
    PPPC_ClearApsCmdLinkNode();
    PPP_DeleteCB(pstPppInfo);

    PPPC_DeletePppId(ucPppId);

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgEhsmProc
 功能描述  : PPPC模块处理EHSM命令
 输入参数  : pMsg    EHSM命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgEhsmProc(struct MsgCB * pMsg)
{
    Cnas_cttf_ehrpd_ehsm_ppp_pif_MSG       *pstEhsmPppPublicInfo;
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU        *pstAttachReq;
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU        *pstDetachReq;
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU      *pstPdnConnectReq;
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU      *pstPdnDisconnectReq;
    CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU  *pstPdnDiscconectInd;
    CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU    *pstDetachInd;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;


    /* 前面已经保证pMsg非空 */

    pstEhsmPppPublicInfo        = (Cnas_cttf_ehrpd_ehsm_ppp_pif_MSG *)pMsg;
    enMsgType                   = pstEhsmPppPublicInfo->stMsgReq.ulMsgId;

    switch(enMsgType)
    {
        /* Attach请求 */
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            pstAttachReq         = (CNAS_CTTF_EHRPD_ATTACH_REQ_STRU *)pMsg;

            PPPC_EhsmAttachReqProc(pstAttachReq);

            break;
        /* Detach请求 */
        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            pstDetachReq         = (CNAS_CTTF_EHRPD_DETACH_REQ_STRU *)pMsg;

            PPPC_EhsmDetachReqProc(pstDetachReq);

            break;
        /* PDN Connect请求 */
        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            pstPdnConnectReq        = (CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU *)pMsg;

            PPPC_EhsmPdnConnectReqProc(pstPdnConnectReq);

            break;
        /* PDN Disconnect请求 */
        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            pstPdnDisconnectReq     = (CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU *)pMsg;

            PPPC_EhsmPdnDisconnectReqProc(pstPdnDisconnectReq);

            break;

        /* 本地PDN断开 */
        case ID_CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND:

            pstPdnDiscconectInd     = (CNAS_CTTF_EHRPD_PDN_LOC_DISC_IND_STRU *)pMsg;

            PPPC_EhsmPdnDisconnectIndProc(pstPdnDiscconectInd);

            break;

        /* 本地去激活 */
        case ID_CNAS_CTTF_EHRPD_LOC_DETACH_IND:

            pstDetachInd            = (CNAS_CTTF_EHRPD_LOC_DETACH_IND_STRU *)pMsg;

            PPPC_EhsmDetachIndProc(pstDetachInd);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}
VOS_VOID PPPC_ActReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    if (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        enIsHandling    = pstApsCurrHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    /* 存储收到激活消息时APS的PID和接入模式 */
    g_stPppContext.ulSendPid = pstApsCurrHeadNode->ulSenderPid;

    switch(pstApsCurrHeadNode->stApsCmdNode.enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
            PPPC_SetRatMode(PPPC_RAT_MODE_1X);
            break;
        case TAF_APS_PPP_RAT_MODE_HRPD:
            PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Rate Mode is %d.\r\n", pstApsCurrHeadNode->stApsCmdNode.enMode);
            break;
    }

    /* 考虑对冲场景，必须保证串行处理 */
    if (PS_FALSE == enIsHandling)
    {
        pstApsCurrHeadNode->enIsHandling = PS_TRUE;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        PPP_HDLC_HARD_SetUp(pstApsCurrHeadNode->ucPppId);

#endif
        /* PPP发起建链 */
        PPPC_SetupPpp(pstApsCurrHeadNode->ucPppId);
    }

    return;
}
VOS_VOID PPPC_DeActReqMsgNodeProc()
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsCurrHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PS_BOOL_ENUM_UINT8                      enIsHandling = PS_FALSE;
    VOS_UINT32                              ulLcpSendFlag;


    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstApsCurrHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    /* 考虑对冲场景，必须保证串行处理 */
    if (VOS_NULL_PTR != pstApsCurrHeadNode)
    {
        enIsHandling    = pstApsCurrHeadNode->enIsHandling;
    }
    else
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }


    if (PS_FALSE == enIsHandling)
    {
        pstApsCurrHeadNode->enIsHandling = PS_TRUE;

        /* 此时需要发送ppp terminate协商报文 */
        ulLcpSendFlag                    = 1;

        /* PPP发起PPP去激活 */
        PPPC_LinkDown(pstApsCurrHeadNode->ucPppId, ulLcpSendFlag);
    }

    return;
}


/*****************************************************************************
 函 数 名  : PPPC_TafMsgNodeProc
 功能描述  : PPPC模块消息节点处理
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafMsgNodeProc(VOS_VOID)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstCurrentHeadNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    PS_BOOL_ENUM_UINT8                      enIsDoingAccessAuth = PS_FALSE;


    /* 如果当前正在进行接入鉴权,不能同时做PPP的业务协商 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
    if (PS_TRUE == enIsDoingAccessAuth)
    {
        PPPC_WARNING_LOG("It is now doing access authentication!\r\n");
        return;
    }

    pstApsPppCmdLink    = &g_stApsCmdLink;

    pstCurrentHeadNode  = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);

    if (VOS_NULL_PTR == pstCurrentHeadNode)
    {
        PPPC_INFO_LOG("APS PPP Cmd Link is Null!\r\n");
        return;
    }

    enMsgType           = pstCurrentHeadNode->stApsCmdNode.enMsgType;
    switch(enMsgType)
    {
        case ID_APS_PPP_ACT_REQ:

            PPPC_ActReqMsgNodeProc();

            break;

        case ID_APS_PPP_DEACT_REQ:

            PPPC_DeActReqMsgNodeProc();

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Aps Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
函 数 名  : PPPC_RespApsPdnIsActived
功能描述  : 成功建立1X连接后，以重复的PdnId再次激活，PPP回复成功激活的消息
输入参数  :    APS_PPP_ACT_REQ_STRU    *pApsActReq,
                VOS_VOID               *pPppInfo,
                VOS_UINT32              ulResult
输出参数  : 无
返 回 值  : VOID
调用函数  :
被调函数  :

修改历史      :
1.日    期   : 2015-07-28
作    者   : zWX297122
修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsPdnIsActived
(
    APS_PPP_ACT_REQ_STRU               *pApsActReq,
    VOS_VOID                           *pPppInfo,
    VOS_UINT32                          ulResult
)
{
    PPPINFO_S                          *pstPppInfo;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;


    /* 申请响应消息内存 */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET(&(pstApsActCnf->enMsgId), 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - PPPC_OM_ACT_CNF_OFFSET_LEN);
    pstApsActCnf->ulReceiverPid         = pApsActReq->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pApsActReq->usOpId;
    pstApsActCnf->ulResult              = ulResult;
    pstApsActCnf->ucPdnId               = pApsActReq->ucPdnId;
    pstApsActCnf->enPdnType             = pApsActReq->enPdnType;

    pstApsActCnf->usMtu                 = PPPC_MAX_FRAME_LEN;

    if (VOS_NULL_PTR != pPppInfo)
    {
        /* 非空说明应该是激活成功，需要把DNS和IP地址填入 */
        pstPppInfo                                = (PPPINFO_S *)pPppInfo;
        pstLcpInfo                                = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
        pstIpcpInfo                               = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
        pstIpv6cpInfo                             = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

        if (VOS_NULL_PTR != pstLcpInfo)
        {
            pstApsActCnf->usMtu                   = pstLcpInfo->stHisOptions.mru;
        }

        if (VOS_NULL_PTR != pstIpcpInfo)
        {
            pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
            pstApsActCnf->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
            pstApsActCnf->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
            PS_MEM_CPY(pstApsActCnf->aucIpv4Addr, &(pstIpcpOption->ouraddr),
                sizeof(pstApsActCnf->aucIpv4Addr));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS));
        }

        if (VOS_NULL_PTR != pstIpv6cpInfo)
        {
            pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);
            PS_MEM_CPY(pstApsActCnf->aucIpv6Addr, pstIpv6cpOption->OurV6InId,
                sizeof(pstIpv6cpOption->OurV6InId));
        }
    }

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    return ;
}
VOS_VOID PPPC_TafActReqProc
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    VOS_UINT32                          ulUserNameLen;
    VOS_UINT32                          ulPasswordLen;
    VOS_UINT8                           ucPppId;
    VOS_UINT32                          ulRetVal;
    PPPC_CONTEXT_INFO_STRU             *pstPppCont;


    /* 内部调用保证指针入参非空 */

    /* 对ucPdnId进行检查 */
    if (VOS_OK != PPPC_CheckPdnId(pstPppActReq->ucPdnId))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input PdnId is too large! %d\r\n", pstPppActReq->ucPdnId);
        return;
    }

    /* 对enMode进行检查 */
    if (VOS_OK != PPPC_CheckRateMode(pstPppActReq->enMode))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input Rate mode is error! %d\r\n", pstPppActReq->enMode);
        return;
    }

    /* 对enPdnType进行检查 */
    if (VOS_OK != PPPC_CheckPdnType(pstPppActReq->enPdnType))
    {
        PPPC_RespApsActFail(pstPppActReq);
        PPPC_WARNING_LOG1("Input Pdn type is error! %d\r\n", pstPppActReq->enPdnType);
        return;
    }

    /* 1X模式下一个PppId只与一个PdnId对应，需要检查重复的PdnId*/
    ulRetVal = PPPC_GetPppIdByPdn(pstPppActReq->ucPdnId, &ucPppId);
    if (VOS_OK == ulRetVal)
    {
        pstPppInfo = &g_astPppPool[ucPppId];

        /* 入参中的PdnId已成功建立连接 */
        if ((PPP_STATE_SUCCESS == pstPppInfo->bPppStateFlg)
            &&  (1 == pstPppInfo->bPppSuccess))
        {
            /* PPP发送激活成功的消息 */
            PPPC_RespApsPdnIsActived(pstPppActReq, pstPppInfo, VOS_OK);

            PPPC_WARNING_LOG2("The PDN has been actived! %d\r\n",
                ucPppId, pstPppActReq->ucPdnId);

            return ;
        }
    }


    /* 收到APS发给PPP的激活消息直接入队 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstApsMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstApsMsgNode->stNode));

    pstApsMsgNode->ulSenderPid               = pstPppActReq->ulSenderPid;
    pstApsMsgNode->stApsCmdNode.enMsgType    = pstPppActReq->enMsgId;
    pstApsMsgNode->usOpId                    = pstPppActReq->usOpId;
    pstApsMsgNode->ucPdnId                   = pstPppActReq->ucPdnId;
    pstApsMsgNode->stApsCmdNode.enMode       = pstPppActReq->enMode;
    pstApsMsgNode->stApsCmdNode.enPdnType    = pstPppActReq->enPdnType;
    pstApsMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_AddPppId(&pstApsMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG("Add Ppp Id fail!");
        PPP_Free(pstApsMsgNode);
        PPPC_RespApsActFail(pstPppActReq);
        return;
    }

    pstPppCont       = &g_stPppContext;

    /* 拷贝用户名 */
    ulUserNameLen    = VOS_StrNLen((VOS_INT8 *)pstPppActReq->aucUserName,
                            TAF_APS_PPP_MAX_AUTHDATA_USERNAME_LEN);
    pstPppCont->ulUserNameLen   = ulUserNameLen;
    VOS_StrNCpy((VOS_INT8 *)pstPppCont->aucUserName,
        (VOS_INT8 *)pstPppActReq->aucUserName, ulUserNameLen);
    pstPppCont->aucUserName[ulUserNameLen] = '\0';

    /* 拷贝密码 */
    ulPasswordLen    = VOS_StrNLen((VOS_INT8 *)pstPppActReq->aucPassword,
                            TAF_APS_PPP_MAX_AUTHDATA_PASSWORD_LEN);
    pstPppCont->ulPasswordLen   = ulPasswordLen;
    VOS_StrNCpy((VOS_INT8 *)pstPppCont->aucPassword,
        (VOS_INT8 *)pstPppActReq->aucPassword, ulPasswordLen);
    pstPppCont->aucPassword[ulPasswordLen] = '\0';

    pstApsPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstApsPppCmdLink, &(pstApsMsgNode->stNode));


    /* 存储modem id */
    g_stPppContext.enModemId    = VOS_GetModemIDFromPid(pstPppActReq->ulSenderPid);

    /* 映射Pdn id和ppp id */
    PPPC_MappingPppIdandPdnId(pstApsMsgNode->ucPppId, pstPppActReq->ucPdnId);

    PPPC_TafMsgNodeProc();

    pstPppInfo                  = &g_astPppPool[pstApsMsgNode->ucPppId];
    PPPC_SetIpCapability(pstPppActReq->enPdnType, pstPppInfo);

    pstPppInfo->bEhrpdUser      = VOS_FALSE;

    /* ppp id映射到PPP内部需要自增 */
    pstPppInfo->ulRPIndex       = pstApsMsgNode->ucPppId;

    return;
}
VOS_VOID PPPC_TafDeActReqProc(APS_PPP_DEACT_REQ_STRU *pstPppDeActReq)
{
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TTF_LINK_ST                            *pstApsPppCmdLink;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstPppDeActReq->ucPdnId))
    {
        PPPC_RespApsDeActFail(pstPppDeActReq);
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    /* 收到APS发给PPP的去激活消息直接入队 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_Malloc(
                        sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_ERROR_LOG("Alloc APS Msg Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(pstApsMsgNode, 0, sizeof(PPPC_APS_MSG_LINK_NODE_STRU));
    TTF_NodeInit(&(pstApsMsgNode->stNode));

    pstApsMsgNode->ulSenderPid               = pstPppDeActReq->ulSenderPid;
    pstApsMsgNode->stApsCmdNode.enMsgType    = pstPppDeActReq->enMsgId;
    pstApsMsgNode->usOpId                    = pstPppDeActReq->usOpId;
    pstApsMsgNode->ucPdnId                   = pstPppDeActReq->ucPdnId;
    pstApsMsgNode->stApsCmdNode.enMode       = pstPppDeActReq->enMode;
    pstApsMsgNode->enIsHandling = PS_FALSE;

    if (VOS_OK != PPPC_GetPppIdByPdn(pstApsMsgNode->ucPdnId, &pstApsMsgNode->ucPppId))
    {
        PPPC_WARNING_LOG1("Get Ppp Id fail! ucPdnID:%d.\n", pstApsMsgNode->ucPdnId);
        PPP_Free(pstApsMsgNode);
        PPPC_RespApsDeActFail(pstPppDeActReq);
        return;
    }

    pstApsPppCmdLink            = &g_stApsCmdLink;

    TTF_LinkInsertTail(MSPS_PID_PPPC, pstApsPppCmdLink, &(pstApsMsgNode->stNode));

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafDeActIndProc
 功能描述  : PPPC模块处理TAF的本地去激活命令
 输入参数  : pstDeActInd    TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafDeActIndProc(APS_PPP_DEACT_IND_STRU *pstDeActInd)
{
    PPPINFO_S                              *pstPppInfo;
    VOS_UINT8                               ucPppId;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstDeActInd->ucPdnId))
    {
        PPPC_WARNING_LOG1("Input PdnId is too large! ucPdnId:%d\r\n", pstDeActInd->ucPdnId);
        return;
    }

    if (VOS_OK != PPPC_GetPppIdByPdn(pstDeActInd->ucPdnId, &ucPppId))
    {
        PPPC_WARNING_LOG1("Get Ppp Id fail! ucPdnId:%d\r\n", pstDeActInd->ucPdnId);
        return;
    }


    pstPppInfo              = &g_astPppPool[ucPppId];

    /* 必须无条件清除本地资源 */
    PPPC_ClearApsCmdLinkNode();
    PPP_DeleteCB(pstPppInfo);

    PPPC_DeletePppId(ucPppId);

    /* 对PDN信息进行清除 */
    /* todo */

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafModeChangeNtfProc
 功能描述  : PPPC模块处理TAF的模式切换命令
 输入参数  : pstModeChangeNtf   TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-04
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafModeChangeNtfProc(APS_PPP_MODE_CHANGE_NTF_STRU *pstModeChangeNtf)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;


    /* 内部调用保证指针入参非空 */

    if (VOS_OK != PPPC_CheckPdnId(pstModeChangeNtf->ucPdnId))
    {
        PPPC_WARNING_LOG("Input PdnId is too large!\r\n");
        return;
    }

    enRatMode = PPPC_GetRatMode();
    if (PPPC_RAT_MODE_EHRPD == enRatMode)
    {
        PPPC_WARNING_LOG("Rat mode is eHRPD!\r\n");
        return;
    }

    switch(pstModeChangeNtf->enMode)
    {
        case TAF_APS_PPP_RAT_MODE_1X:
            PPPC_SetRatMode(PPPC_RAT_MODE_1X);
            break;
        case TAF_APS_PPP_RAT_MODE_HRPD:
            PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Rate Mode is %d.\r\n", pstModeChangeNtf->enMode);
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_TafDialModeNtfProc
 功能描述  : PPPC模块处理TAF的拨号模式切换命令
 输入参数  : pstDialModeNtf   TAF命令
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-07-01
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_TafDialModeNtfProc(APS_PPP_DIAL_MODE_NTF_STRU *pstDialModeNtf)
{
    /* 内部调用保证指针入参非空 */

    switch(pstDialModeNtf->enDialMode)
    {
        case TAF_APS_PPP_CDATA_DIAL_MODE_RELAY:
        case TAF_APS_PPP_CDATA_DIAL_MODE_NETWORK:
            PPPC_SetDialMode(pstDialModeNtf->enDialMode);
            break;
        default:
            PPPC_WARNING_LOG1("warning: Dial Mode is %d.\r\n", pstDialModeNtf->enDialMode);
            break;
    }

    return;
}
VOS_VOID PPPC_HRPD_RcvCommittedIndProc(struct MsgCB * pMsg)
{
    CTTF_PPP_HRPD_COMMITTED_IND_STRU   *pstCommttedInd;
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    VOS_UINT32                          ulIndex;


    pstCommttedInd  = (CTTF_PPP_HRPD_COMMITTED_IND_STRU*)pMsg;

    pstHrpdContext  = &(g_stPppContext.stHrpdContext);

    for (ulIndex = 0; ulIndex < PPPC_MAX_PA_BINDING_APP_NUM; ulIndex++)
    {
        /* 分别存放Stream1,2,3 */
        pstHrpdContext->aenApplicationType[ulIndex]
            = pstCommttedInd->enApplicationType[ulIndex];
    }

    pstHrpdContext->enIsSendOpenFlag = PS_FALSE;

    return;
}
VOS_VOID PPPC_HRPD_RcvReservationsIndProc(struct MsgCB * pMsg)
{
    CTTF_PPP_HRPD_RESERVATIONS_IND_STRU    *pstReservationsInd;


    pstReservationsInd  = (CTTF_PPP_HRPD_RESERVATIONS_IND_STRU*)pMsg;

    PA_AGENT_HRPD_SetMaxReservNum(pstReservationsInd);

    return;
}


VOS_VOID PPPC_HRPD_SendOpenStreamReq(VOS_VOID)
{
    PPPC_HRPD_CONTEXT_STRU                 *pstHrpdContext;
    PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU  *pstPppOpenStreamReq;


    pstHrpdContext      = &(g_stPppContext.stHrpdContext);

    /* 如果已经发过，不需要发送打开流的请求消息 */
    if (PS_TRUE == pstHrpdContext->enIsSendOpenFlag)
    {
        PPPC_WARNING_LOG("No need to send open stream request!\r\n");
        return;
    }
    pstHrpdContext->enIsSendOpenFlag = PS_TRUE;

    pstPppOpenStreamReq = (PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ_STRU));
    if (VOS_NULL_PTR == pstPppOpenStreamReq)
    {
        PPPC_ERROR_LOG("Alloc Ppp Open Stream Mem Fail!\r\n");
        return;
    }

    pstPppOpenStreamReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppOpenStreamReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppOpenStreamReq->enMsgId        = ID_PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ;
    pstPppOpenStreamReq->usOpId         = 0;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppOpenStreamReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_PA_OPEN_STREAM_REQ msg fail!");
    }

    return;
}


VOS_VOID PPPC_HRPD_SendCloseStreamReq(VOS_VOID)
{
        PPPC_HRPD_CONTEXT_STRU              *pstHrpdContext;
    PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU  *pstPppCloseStreamReq;


    pstHrpdContext      = &(g_stPppContext.stHrpdContext);
    pstHrpdContext->enIsSendOpenFlag = PS_FALSE;

    pstPppCloseStreamReq = (PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ_STRU));
    if (VOS_NULL_PTR == pstPppCloseStreamReq)
    {
        PPPC_ERROR_LOG("Alloc ppp close stream mem fail!\r\n");
        return;
    }

    pstPppCloseStreamReq->ulReceiverPid  = CTTF_PID_HRPD_RPA;
    pstPppCloseStreamReq->ulReceiverCpuId= VOS_LOCAL_CPUID;
    pstPppCloseStreamReq->enMsgId        = ID_PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ;
    pstPppCloseStreamReq->usOpId         = 0;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPppCloseStreamReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_PA_CLOSE_STREAM_REQ msg fail!");
    }

    return;
}
VOS_UINT32 PPPC_HRPD_GetStreamNumByAppType
(
    CTTF_HRPD_PA_APPLICATION_TYPE_ENUM_UINT16   enAppType,
    VOS_UINT8                                  *pucStreamNum
)
{
    PPPC_HRPD_CONTEXT_STRU             *pstHrpdContext;
    VOS_UINT32                          ulIndex;


    pstHrpdContext  = &(g_stPppContext.stHrpdContext);
    for (ulIndex = 0; ulIndex < PPPC_MAX_PA_BINDING_APP_NUM; ulIndex++)
    {
        if (enAppType == pstHrpdContext->aenApplicationType[ulIndex])
        {
            *pucStreamNum   = (VOS_UINT8)ulIndex + 1;
            return VOS_OK;
        }
    }

    PPPC_WARNING_LOG1("Warning:Do not have this app info!", enAppType);

    return VOS_ERR;
}


VOS_VOID PPPC_HRPD_SendOpenQoSReq(PPPC_HRPD_RESERVATION_QOS_INFO_STRU *pstQoSInfo)
{
    PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU    *pstQoSReq;
    VOS_UINT32                          ulRet;
    VOS_UINT8                           ucStreamNum;


    if (VOS_NULL_PTR == pstQoSInfo)
    {
        PPPC_WARNING_LOG("Warning:Input parameter is null!");
        return;
    }

    ulRet   = PPPC_HRPD_GetStreamNumByAppType(pstQoSInfo->enApplicationType, &ucStreamNum);
    if (VOS_OK != ulRet)
    {
        return;
    }

    pstQoSReq   = (PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU));
    if (VOS_NULL_PTR == pstQoSReq)
    {
        PPPC_ERROR_LOG("Alloc ppp open qos mem fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstQoSReq->enMsgId), 0,
        sizeof(PPP_CTTF_HRPD_MFPA_QOS_REQ_STRU) - PPPC_OM_QOS_REQ_OFFSET_LEN);

    pstQoSReq->ulReceiverPid    = CTTF_PID_HRPD_RPA;
    pstQoSReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQoSReq->enMsgId          = ID_PPP_CTTF_HRPD_MFPA_QOS_REQ;
    pstQoSReq->usOpId           = 0;
    pstQoSReq->ucStreamNumber   = ucStreamNum;
    pstQoSReq->ucNumFwdReservations = pstQoSInfo->ucNumFwdReservations;
    pstQoSReq->ucNumRevReservations = pstQoSInfo->ucNumRevReservations;
    PS_MEM_CPY(pstQoSReq->astFwdReservations, pstQoSInfo->astFwdReservations,
                sizeof(pstQoSReq->astFwdReservations));
    PS_MEM_CPY(pstQoSReq->astRevReservations, pstQoSInfo->astRevReservations,
                sizeof(pstQoSReq->astRevReservations));

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstQoSReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_MFPA_QOS_REQ msg fail!");
    }

    return;
}
VOS_VOID PPPC_HRPD_SendCloseQoSReq
(
    PPPC_HRPD_RESERVATION_QOS_CLOSE_INFO_STRU *pstQoSCloseInfo
)
{
    PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU  *pstQoSCloseReq;


    if (VOS_NULL_PTR == pstQoSCloseInfo)
    {
        PPPC_WARNING_LOG("Warning:Input parameter is null!");
        return;
    }

    pstQoSCloseReq   = (PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU));
    if (VOS_NULL_PTR == pstQoSCloseReq)
    {
        PPPC_ERROR_LOG("Alloc ppp close qos mem fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstQoSCloseReq->enMsgId), 0,
        sizeof(PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ_STRU) - PPPC_OM_QOS_CLOSE_REQ_OFFSET_LEN);

    pstQoSCloseReq->ulReceiverPid    = CTTF_PID_HRPD_RPA;
    pstQoSCloseReq->ulReceiverCpuId  = VOS_LOCAL_CPUID;
    pstQoSCloseReq->enMsgId          = ID_PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ;
    pstQoSCloseReq->usOpId           = 0;
    pstQoSCloseReq->ucNumFwdReservations = pstQoSCloseInfo->ucNumFwdReservations;
    pstQoSCloseReq->ucNumRevReservations = pstQoSCloseInfo->ucNumRevReservations;

    PS_MEM_CPY(pstQoSCloseReq->aucFwdReservationLabels, pstQoSCloseInfo->aucFwdReservationLabels,
                sizeof(pstQoSCloseReq->aucFwdReservationLabels));
    PS_MEM_CPY(pstQoSCloseReq->aucRevReservationLabels, pstQoSCloseInfo->aucRevReservationLabels,
                sizeof(pstQoSCloseReq->aucRevReservationLabels));

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstQoSCloseReq))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_CTTF_HRPD_MFPA_QOS_CLOSE_REQ msg fail!");
    }

    return;
}
VOS_UINT32 PPPC_HRPD_GetFileReq(USIMM_DEF_FILEID_ENUM_UINT32 enFileID)
{
    USIMM_READFILE_REQ_STRU            *pstMsg;
    VOS_CHAR                           *pcFilePath;


    if (VOS_ERR == USIMM_ChangeDefFileToPath(enFileID, &pcFilePath))
    {
        /*返回函数错误信息*/
        return VOS_ERR;
    }

    /* 申请消息内存 */
    pstMsg   = (USIMM_READFILE_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_READFILE_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*填充消息内容*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_READFILE_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pstMsg->stMsgHeader.ulReceiverPid         = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_READFILE_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_CDMA_APP;

    pstMsg->stFilePath.ulPathLen              = VOS_StrLen(pcFilePath);
    VOS_MemCpy(pstMsg->stFilePath.acPath, pcFilePath, pstMsg->stFilePath.ulPathLen);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_READFILE_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 函 数 名  : PPPC_IsCaveAlgorithmEnable
 功能描述  : HRPD模式接入鉴权是否支持CAVE算法
 输入参数  : 无
 输出参数  : 无
 返 回 值  : PS_BOOL_ENUM_UINT8 PS_FALSE不支持，PS_TRUE支持
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年09月01日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
PS_BOOL_ENUM_UINT8 PPPC_IsCaveAlgorithmEnable(VOS_VOID)
{
    return g_stPppContext.enCaveEnable;
}


VOS_VOID PPPC_SaveAccessAuthUserNameInfo(VOS_UINT8 *pstMsg)
{
    VOS_UINT8                          *pucTemp = pstMsg;
    VOS_UINT8                           ucDataLen;


    /* refer to 3GPP2 C.S0016-D v2.0 Section 3.5.8.5 */
    /* MsgLen | DataLen | Access Auth User Name |
         8bit     8bit        1~127Butes         */
    pucTemp++;
    ucDataLen   = *pucTemp;
    pucTemp++;

    if (ucDataLen <= CNAS_CTTF_EHRPD_MAX_AUTHDATA_USERNAME_LEN)
    {
        PS_MEM_CPY(g_stPppContext.stHrpdContext.aucAccessAuthUserName, pucTemp, ucDataLen);
        g_stPppContext.stHrpdContext.aucAccessAuthUserName[ucDataLen] = '\0';
        g_stPppContext.stHrpdContext.ucAccessAuthLen    = ucDataLen;
    }
    else
    {
        PPPC_WARNING_LOG1("the length of access auth user name is error. MsgLen:%d, TotalLen:%d.\n", ucDataLen);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SaveRunCaveRandu
 功能描述  : 保存RAND
 输入参数  : VOS_UINT32 ulRandu
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SaveRunCaveRandu(VOS_UINT32 ulRandu)
{
    g_stPppContext.stHrpdContext.ulRandu = ulRandu;
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_GetRunCaveRandu
 功能描述  : 保存RAND
 输入参数  : 无
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_GetRunCaveRandu(VOS_VOID)
{
    return g_stPppContext.stHrpdContext.ulRandu;
}

/*****************************************************************************
 函 数 名  : PPPC_UsimmCdmaSpecAuthProc
 功能描述  : CHAP鉴权MD5算法计算回复处理函数
 输入参数  : pstMsg:消息内容
 输出参数  : 无
 返 回 值  : 无
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年06月29日
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_UsimmCdmaSpecAuthProc(USIMM_CDMASPECAUTH_CNF_STRU *pstMsg)
{
    PPPC_APS_MSG_LINK_NODE_STRU        *pstActPppNode = VOS_NULL_PTR;
    PPPINFO_S                          *pstPppInfo;
    PPPCHAPINFO_S                      *pstChapInfo;
    PS_BOOL_ENUM_UINT8                  enIsDoingAccessAuth;
    PS_BOOL_ENUM_UINT8                  enIsCaveAlgorithmEnable;
    VOS_UINT32                          ulRandu;


    /* 停止定时器 */

    if (USIMM_CDMASPEC_COMPUTEIP != pstMsg->enAuthType)
    {
        PPPC_WARNING_LOG("enAuthType isn't USIMM_CDMASPEC_COMPUTEIP.\n");
        return;
    }

    if (USIMM_COMPUTEIP_HRPD != pstMsg->uAuthCnf.stComputeIPCnf.enComputeIPType)
    {
        PPPC_WARNING_LOG("enComputeIPType isn't USIMM_COMPUTEIP_CHAP.\n");
        return;
    }

    if (VOS_OK == pstMsg->stCmdResult.ulResult)
    {
        /* 接入鉴权不需要从节点获取密码 */
        enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
        if (PS_TRUE != enIsDoingAccessAuth)
        {
            pstActPppNode = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_GetActPppHeadNode();

            if (VOS_NULL_PTR == pstActPppNode)
            {
                PPPC_WARNING_LOG("pstActPppNode is NULL.\n");
                return;
            }

            pstPppInfo = &g_astPppPool[pstActPppNode->ucPppId];
        }
        else
        {
            pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];
        }

        pstChapInfo = pstPppInfo->pstChapInfo;
        if (VOS_NULL_PTR == pstChapInfo)
        {
            PPPC_WARNING_LOG("pstChapInfo is NULL.\n");
            return;
        }

        /*保存Response 及长度*/
        PS_MEM_CPY(pstChapInfo->szResponse, pstMsg->uAuthCnf.stComputeIPCnf.aucRspData,
            pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen);
        pstChapInfo->szResponse[pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen] = 0;
        pstChapInfo->ucRespLen = (VOS_UINT8)pstMsg->uAuthCnf.stComputeIPCnf.ulDataLen;
        PPP_CHAP_SendResponse(pstPppInfo);
    }
    else
    {
        PPPC_WARNING_LOG1("The result of MD5 CHAP AUTH error. ErrorCode:%d.\n", pstMsg->stCmdResult.ulErrorCode);
        /* 在支持CAVE算法的情况下，使用MD5算法接入鉴权失败时，再使用CAVE算法鉴权 */
        enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
        enIsCaveAlgorithmEnable = PPPC_IsCaveAlgorithmEnable();
        if ((PS_TRUE == enIsDoingAccessAuth) && (PS_TRUE == enIsCaveAlgorithmEnable))
        {
            ulRandu = PPPC_GetRunCaveRandu();
            PPPC_UIM_RunCaveAuthReq(ulRandu);
        }
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_UsimmAuthenticationCnfProc
 功能描述  : 收到CAVE鉴权结果消息的处理
 输入参数  : USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015年08月08日
    作    者   : w00316385
    修改内容   : 新生成函数

*****************************************************************************/
VOS_UINT32 PPPC_UsimmAuthenticationCnfProc(USIMM_AUTHENTICATION_CNF_STRU  *pUsimAuthCnf)
{
    PS_BOOL_ENUM_UINT8                      enIsDoingAccessAuth;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstActPppNode = VOS_NULL_PTR;
    PPPINFO_S                              *pstPppInfo;
    PPPCHAPINFO_S                          *pstChapInfo;
    USIMM_RUNCAVE_AUTH_CNF_STRU            *pstUsimmRuncaveAuthCnf;


    /* 鉴权失败，不用给BS回复响应，BS超时处理 */
    if (USIMM_AUTH_CDMA_SUCCESS != pUsimAuthCnf->enResult)
    {
        PPPC_WARNING_LOG1("PPPC_UsimAuthenticationCnfProc: Auth fail", pUsimAuthCnf->enResult);
        return VOS_ERR;
    }

    if (USIMM_RUNCAVE_AUTH != pUsimAuthCnf->enAuthType)
    {
        /* 其他类型，这里不用处理 */
        PPPC_WARNING_LOG1("PPPC_UsimAuthenticationCnfProc: enAuthType", pUsimAuthCnf->enAuthType);

        return VOS_ERR;
    }

    /* 取AUTHU值 */
    pstUsimmRuncaveAuthCnf          = &(pUsimAuthCnf->uCnfData.stRunCaveCnf);

    /* 接入鉴权不需要从节点获取密码 */
    enIsDoingAccessAuth = PPPC_IsDoingAccessAuth();
    if (PS_TRUE != enIsDoingAccessAuth)
    {
        pstActPppNode = (PPPC_APS_MSG_LINK_NODE_STRU *)PPP_GetActPppHeadNode();

        if (VOS_NULL_PTR == pstActPppNode)
        {
            PPPC_WARNING_LOG("pstActPppNode is NULL.\n");
            return VOS_ERR;
        }

        pstPppInfo = &g_astPppPool[pstActPppNode->ucPppId];
    }
    else
    {
        pstPppInfo = &g_astPppPool[PPPC_PPP_ID_FOR_ACCESS_AUTH];
    }

    pstChapInfo = pstPppInfo->pstChapInfo;
    if (VOS_NULL_PTR == pstChapInfo)
    {
        PPPC_WARNING_LOG("pstChapInfo is NULL.\n");
        return VOS_ERR;
    }

    /*保存Response 及长度*/
    PS_MEM_SET(pstChapInfo->szResponse, 0, sizeof(pstChapInfo->szResponse));
    pstChapInfo->szResponse[0] = pstUsimmRuncaveAuthCnf->aucAuthr[0];
    pstChapInfo->szResponse[1] = pstUsimmRuncaveAuthCnf->aucAuthr[1];
    pstChapInfo->szResponse[2] = pstUsimmRuncaveAuthCnf->aucAuthr[2];
    pstChapInfo->ucRespLen = CHAP_MAX_RESPONSE_LENGTH;
    PPP_CHAP_SendResponse(pstPppInfo);

    return VOS_OK;
}
VOS_VOID PPPC_MsgTafProc(struct MsgCB * pMsg)
{
    Taf_aps_ppp_pif_MSG                    *pstApsPppPublicInfo;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;
    APS_PPP_ACT_REQ_STRU                   *pstPppActReq;
    APS_PPP_DEACT_REQ_STRU                 *pstPppDeActReq;
    APS_PPP_DEACT_IND_STRU                 *pstPppDeActInd;
    APS_PPP_MODE_CHANGE_NTF_STRU           *pstModeChangeNtf;
    APS_PPP_DIAL_MODE_NTF_STRU             *pstDialModeNtf;


    /* 前面已经保证pMsg非空 */

    pstApsPppPublicInfo         = (Taf_aps_ppp_pif_MSG *)pMsg;
    enMsgType                   = pstApsPppPublicInfo->stMsgData.enMsgId;

    /*如果是接收到从TE发送来的数据帧*/
    switch(enMsgType)
    {
        /* PPP激活去激活消息在同一个地方break */
        case ID_APS_PPP_ACT_REQ:

            pstPppActReq            = (APS_PPP_ACT_REQ_STRU *)pMsg;

            PPPC_TafActReqProc(pstPppActReq);

            break;

        case ID_APS_PPP_DEACT_REQ:

            pstPppDeActReq          = (APS_PPP_DEACT_REQ_STRU *)pMsg;

            PPPC_TafDeActReqProc(pstPppDeActReq);

            break;

        case ID_APS_PPP_DEACT_IND:

            pstPppDeActInd          = (APS_PPP_DEACT_IND_STRU *)pMsg;

            PPPC_TafDeActIndProc(pstPppDeActInd);

            break;

        case ID_APS_PPP_MODE_CHANGE_NTF:

            pstModeChangeNtf        = (APS_PPP_MODE_CHANGE_NTF_STRU *)pMsg;

            PPPC_TafModeChangeNtfProc(pstModeChangeNtf);

            break;

        case ID_APS_PPP_DIAL_MODE_NTF:

            pstDialModeNtf          = (APS_PPP_DIAL_MODE_NTF_STRU *)pMsg;

            PPPC_TafDialModeNtfProc(pstDialModeNtf);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Aps Cmd", enMsgType);

            break;
    }

    return;
}
VOS_VOID PPPC_MsgPppcProc(struct MsgCB * pMsg)
{
    PPPC_INNER_MSG_TYPE_ENUM_UINT16     enPppcMsgType;


    enPppcMsgType   = *(PPPC_INNER_MSG_TYPE_ENUM_UINT16 *)(pMsg->aucValue);

    switch (enPppcMsgType)
    {
        case PPPC_DL_DATA_PROC_NOTIFY:
        case PPPC_UL_DATA_PROC_NOTIFY:

            PPPC_DequeueProc(PPPC_PROC_BY_STAMP);

            VOS_TaskLock();
            PPPC_QNotifyCntSubOper();
            VOS_TaskUnlock();

            break;

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        case PPPC_HDLC_PROC_AS_FRM_PACKET_IND:

            PPPC_ProcAsFrmDataInd(pMsg);

            break;

#endif
        default:

            PPP_DBG_ERR_CNT(PPP_PHERR_817);

            PPPC_WARNING_LOG1("Rcv Invalid PPPC Cmd!\r\n", enPppcMsgType);

            break;
    }

    return;
}


VOS_VOID PPPC_HRPD_ActPppAccessAuth(struct MsgCB * pMsg)
{
    PPPC_ChangeAccessAuthState(PS_TRUE);

    /* 初始化数据 */
    (VOS_VOID)PPPC_InitFixedData();

    /* 需要接入鉴权,必然是HRPD模式,此时没有人通知,只能自己设置 */
    PPPC_SetRatMode(PPPC_RAT_MODE_HRPD);

    PPPC_SetupPpp(PPPC_PPP_ID_FOR_ACCESS_AUTH);
    return;
}


VOS_VOID PPPC_HRPD_MsgRpaProc(struct MsgCB * pMsg)
{
    CTTF_HRPD_PA_PPP_PIF_MSG_TYPE_ENUM_UINT16     enMsgType;


    enMsgType   = *(CTTF_HRPD_PA_PPP_PIF_MSG_TYPE_ENUM_UINT16 *)(pMsg->aucValue);

    switch (enMsgType)
    {
        case ID_CTTF_PPP_HRPD_COMMITTED_IND:

            PPPC_HRPD_RcvCommittedIndProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_RESERVATIONS_IND:

            PPPC_HRPD_RcvReservationsIndProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_OPEN_RESERVATION_IND:

            PPPC_HrpdPaAgentRcvOpenReservProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_CLOSE_RESERVATIONS_IND:

            PPPC_HrpdPaAgentRcvCloseReservProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_RESERVATION_DL_MSG:

            PPPC_HRPD_PaAgentRcvReservDlMsgProc(pMsg);

            break;

        case ID_CTTF_PPP_HRPD_ACCESS_AUTH_IND:

            PPPC_HRPD_ActPppAccessAuth(pMsg);

            break;

        default:

            PPPC_WARNING_LOG1("Rcv invalid PA message!\r\n", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgUsimmProc
 功能描述  : PPPC模块收到WUEPS_PID_USIM任务发来消息的处理
 输入参数  : PPPC_UIM_MSG_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-29
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgUsimmProc(PPPC_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case USIMM_CDMASPECAUTH_CNF:
            PPPC_UsimmCdmaSpecAuthProc((USIMM_CDMASPECAUTH_CNF_STRU *)pstMsg);
            break;

        /* RUN CAVE鉴权响应 */
        case USIMM_AUTHENTICATION_CNF:
            PPPC_UsimmAuthenticationCnfProc((USIMM_AUTHENTICATION_CNF_STRU *)pstMsg);
            break;

        /* 读取文件请求CNF */
        case USIMM_READFILE_CNF:
            PPPC_UsimmReadFileCnfProc((USIMM_READFILE_CNF_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_MsgPihProc
 功能描述  : PPPC模块收到MAPS_PIH_PID任务发来消息的处理
 输入参数  : PPPC_UIM_MSG_STRU *pstMsg
 输出参数  : 无
 返 回 值  : VOS_VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-08-13
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_MsgPihProc(PPPC_UIM_MSG_STRU *pstMsg)
{
    switch (pstMsg->ulMsgName)
    {
        case USIMM_CARDSTATUS_IND:
            PPPC_PihUsimStatusIndProc((USIMM_CARDSTATUS_IND_STRU *)pstMsg);
            break;

        default:
            break;
    }

    return;
}


VOS_UINT32 PPPC_Init(enum VOS_INIT_PHASE_DEFINE enPhase )
{
    TTF_PPPC_NVIM_NEGO_OPTIONS_STRU     stNvNegoOptions;


    switch (enPhase)
    {
        case VOS_IP_LOAD_CONFIG:

        /* 初始化PPP上下文 */
        PS_MEM_SET(&g_stPppContext, 0, sizeof(g_stPppContext));

        if (NV_OK != NV_Read(en_NV_Item_TTF_PPPC_NEGO_OPTIONS, &stNvNegoOptions, sizeof(TTF_PPPC_NVIM_NEGO_OPTIONS_STRU)))
        {
            g_stPppContext.usMru                = PPPC_MAX_FRAME_LEN;
            g_stPppContext.enCaveEnable         = PS_FALSE;
        }
        else
        {
            g_stPppContext.usMru                = stNvNegoOptions.usMru;
            g_stPppContext.enCaveEnable         = (stNvNegoOptions.ucCaveEnable > 0) ? PS_TRUE : PS_FALSE;

            if ((g_stPppContext.usMru < PPPC_MIN_FRAME_LEN)
                || (g_stPppContext.usMru > PPPC_MAX_FRAME_LEN))
            {
                g_stPppContext.usMru = PPPC_MAX_FRAME_LEN;
            }
        }

        PPP_TaskInit();
        PPP_TaskEntry();

        /* 初始化上下行队列 */
        PPPC_QueueInit();

        /* 初始化APS消息链表 */
        PPPC_ApsCmdLinkInit();

        /* 初始化PA AGENT上下文 */
        PPPC_HRPD_PaAgentInit();

        /* 初始化上行数据内存 */
        PS_MEM_SET(&g_astUlEncapMem[0], 0, sizeof(g_astUlEncapMem));


#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)

        /* 初始化HDLC */
        if (VOS_OK != PPP_HDLC_HARD_Init())
        {
            return VOS_ERR;
        }

#endif

        /* 注册到PIH，准备接收卡状态消息 */
        PIH_RegUsimCardStatusIndMsg(MSPS_PID_PPPC);
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
        case VOS_IP_BUTT:
            break;

        default:
            vos_printf("1X RMAC, ERROR, INIT_PHASE = %d \r", enPhase);
            break;
    }

    return VOS_OK;
}
VOS_VOID PPPC_MsgProc(struct MsgCB * pMsg)
{
    if(VOS_NULL_PTR == pMsg)
    {
        PPPC_WARNING_LOG("PPPC_MsgProc pMsg is NULL!\r\n");
        return;
    }

#if defined (CTTF_PC_ST_SWITCH)
    CTTF_HookMsg(pMsg);
#endif

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
    PPP_HDLC_HARD_PeriphClkOpen();
#endif

    switch (pMsg->ulSenderPid)
    {
        /*如果是定时器发来的消息*/
        case VOS_PID_TIMER:

            PPPC_MsgTimerProc((VOS_VOID *)pMsg);

            break;

        case I0_WUEPS_PID_TAF:
        case I1_WUEPS_PID_TAF:
        case I2_WUEPS_PID_TAF:

            PPPC_MsgTafProc((VOS_VOID *)pMsg);

            break;

        case UEPS_PID_EHSM:

            PPPC_MsgEhsmProc((VOS_VOID *)pMsg);

            break;

        case MSPS_PID_PPPC:

            PPPC_MsgPppcProc((VOS_VOID *)pMsg);

            break;

        case CTTF_PID_HRPD_RPA:

            PPPC_HRPD_MsgRpaProc((VOS_VOID *)pMsg);

            break;

        case WUEPS_PID_USIM:

            PPPC_MsgUsimmProc((PPPC_UIM_MSG_STRU *)pMsg);

            break;

        case MAPS_PIH_PID:

            PPPC_MsgPihProc((PPPC_UIM_MSG_STRU *)pMsg);

            break;

        default:

            PPPC_WARNING_LOG1("PPPC_MsgProc Sender Pid is Invalid!\r\n", pMsg->ulSenderPid);

            break;
    }

#if (FEATURE_ON == FEATURE_HARDWARE_HDLC_ON_CCPU)
        PPP_HDLC_HARD_PeriphClkClose();
#endif

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsActFail
 功能描述  : PPP回复APS Act失败
 输入参数  : pstPppActReq   APS_PPP_ACT_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsActFail
(
    APS_PPP_ACT_REQ_STRU               *pstPppActReq
)
{
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;


    /* 申请响应消息内存 */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_ERROR_LOG("Alloc Ppp Act Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstApsActCnf->enMsgId), 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - PPPC_OM_ACT_CNF_OFFSET_LEN);
    pstApsActCnf->ulReceiverPid         = pstPppActReq->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pstPppActReq->usOpId;
    pstApsActCnf->ulResult              = VOS_ERR;
    pstApsActCnf->ucPdnId               = pstPppActReq->ucPdnId;
    pstApsActCnf->enPdnType             = pstPppActReq->enPdnType;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_PPP_APS_ACT_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsDeActFail
 功能描述  : PPP回复APS DeAct失败
 输入参数  : pstPppDeActReq   APS_PPP_DEACT_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsDeActFail
(
    APS_PPP_DEACT_REQ_STRU             *pstPppDeActReq
)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;


    /* 申请响应消息内存 */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_ERROR_LOG("Alloc Ppp DeAct Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstApsDeActCnf->enMsgId), 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - PPPC_OM_DEACT_CNF_OFFSET_LEN);
    pstApsDeActCnf->ulReceiverPid         = pstPppDeActReq->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId               = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId                = pstPppDeActReq->usOpId;
    pstApsDeActCnf->ulResult              = VOS_ERR;
    pstApsDeActCnf->ucPdnId               = pstPppDeActReq->ucPdnId;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_PPP_APS_DEACT_CNF!!!\n");
    return;
}


VOS_VOID PPPC_RespApsActCmd(VOS_VOID* pPppInfo, VOS_UINT32 ulResult)
{
    PPPINFO_S                          *pstPppInfo;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    PPP_APS_ACT_CNF_STRU               *pstApsActCnf;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_WARNING_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    if (VOS_OK != ulResult)
    {
        PPPC_DeletePppId(pstApsMsgNode->ucPppId);
    }

    /* 申请响应消息内存 */
    pstApsActCnf    = (PPP_APS_ACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_ACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        return;
    }

    PS_MEM_SET(&(pstApsActCnf->enMsgId), 0,
        sizeof(PPP_APS_ACT_CNF_STRU) - PPPC_OM_ACT_CNF_OFFSET_LEN);
    pstApsActCnf->ulReceiverPid         = pstApsMsgNode->ulSenderPid;
    pstApsActCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstApsActCnf->enMsgId               = ID_PPP_APS_ACT_CNF;
    pstApsActCnf->usOpId                = pstApsMsgNode->usOpId;
    pstApsActCnf->ulResult              = ulResult;
    pstApsActCnf->ucPdnId               = pstApsMsgNode->ucPdnId;
    pstApsActCnf->enPdnType             = pstApsMsgNode->stApsCmdNode.enPdnType;

    pstApsActCnf->usMtu                 = PPPC_MAX_FRAME_LEN;

    if (VOS_NULL_PTR != pPppInfo)
    {
        /* 非空说明应该是激活成功，需要把DNS和IP地址填入 */
        pstPppInfo                                = (PPPINFO_S *)pPppInfo;
        pstLcpInfo                                = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
        pstIpcpInfo                               = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
        pstIpv6cpInfo                             = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

        if (VOS_NULL_PTR != pstLcpInfo)
        {
            pstApsActCnf->usMtu                   = pstLcpInfo->stHisOptions.mru;
        }

        if (VOS_NULL_PTR != pstIpcpInfo)
        {
            pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
            pstApsActCnf->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
            pstApsActCnf->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
            PS_MEM_CPY(pstApsActCnf->aucIpv4Addr, &(pstIpcpOption->ouraddr),
                sizeof(pstApsActCnf->aucIpv4Addr));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4PrimDNS));
            PS_MEM_CPY(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
                sizeof(pstApsActCnf->stIpv4Dns.aucIpv4SecDNS));
        }

        if (VOS_NULL_PTR != pstIpv6cpInfo)
        {
            pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);
            PS_MEM_CPY(pstApsActCnf->aucIpv6Addr, pstIpv6cpOption->OurV6InId,
                sizeof(pstIpv6cpOption->OurV6InId));
        }
    }

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_ACT_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstApsPppCmdLink);

    PPP_Free(pstApsMsgNode);

    PPPC_TafMsgNodeProc();

    return;
}


VOS_VOID PPPC_RespApsDeActCmd(VOS_UINT32 ulResult)
{
    PPP_APS_DEACT_CNF_STRU             *pstApsDeActCnf;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_WARNING_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    PPPC_DeletePppId(pstApsMsgNode->ucPppId);

    /* 申请响应消息内存 */
    pstApsDeActCnf    = (PPP_APS_DEACT_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_CNF_STRU));
    if (VOS_NULL_PTR == pstApsDeActCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp DeAct Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstApsPppCmdLink);

        PPP_Free(pstApsMsgNode);

        return;
    }

    PS_MEM_SET(&(pstApsDeActCnf->enMsgId), 0,
        sizeof(PPP_APS_DEACT_CNF_STRU) - PPPC_OM_DEACT_CNF_OFFSET_LEN);
    pstApsDeActCnf->ulReceiverPid       = pstApsMsgNode->ulSenderPid;
    pstApsDeActCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsDeActCnf->enMsgId             = ID_PPP_APS_DEACT_CNF;
    pstApsDeActCnf->usOpId              = pstApsMsgNode->usOpId;
    pstApsDeActCnf->ulResult            = ulResult;
    pstApsDeActCnf->ucPdnId             = pstApsMsgNode->ucPdnId;

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsDeActCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_DEACT_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstApsMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstApsPppCmdLink);

    PPP_Free(pstApsMsgNode);

    PPPC_TafMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespApsModifyIndCmd
 功能描述  : 回复APS IP地址修改消息
 输入参数  : pstPppInfo
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-08-31
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespApsModifyIndCmd(PPPINFO_S* pstPppInfo)
{
    PPP_APS_MODIFY_IND_STRU            *pstApsModifyInd;
    PPP_IPCP_OPTION_S                  *pstIpcpOption;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPIPCPINFO_S                      *pstIpcpInfo;
    PPPIPV6CPINFO_S                    *pstIpv6cpInfo;
    PPP_IPV6CP_OPTION_S                *pstIpv6cpOption;
    VOS_UINT8                           ucPdnId = 0;
    VOS_UINT32                          ulRet = VOS_ERR;


    if (VOS_NULL_PTR == pstPppInfo)
    {
        PPPC_WARNING_LOG("pstPppInfo is null!\r\n");
        return;
    }

    switch(g_stPppContext.enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            if (pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            if (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            if ((pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
                && (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS))
            {
                ulRet = VOS_OK;
            }
            break;
        default:
            break;
    }

    if (VOS_OK != ulRet)
    {
        return;
    }

    if (VOS_OK != PPPC_1X_GetPdnId((VOS_UINT8)pstPppInfo->ulRPIndex, &ucPdnId))
    {
        PPPC_WARNING_LOG1("Get Pdn Id failed, ucPppId:[%d]\n", pstPppInfo->ulRPIndex);
        return;
    }

    /* 申请响应消息内存 */
    pstApsModifyInd    = (PPP_APS_MODIFY_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(PPP_APS_MODIFY_IND_STRU));
    if (VOS_NULL_PTR == pstApsModifyInd)
    {
        PPPC_WARNING_LOG("Alloc Ppp Modify Ind Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET((VOS_UINT8 *)pstApsModifyInd + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(PPP_APS_MODIFY_IND_STRU) - VOS_MSG_HEAD_LENGTH);
    pstApsModifyInd->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstApsModifyInd->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstApsModifyInd->enMsgId             = ID_PPP_APS_MODIFY_IND;
    pstApsModifyInd->usOpId              = 0;
    pstApsModifyInd->ucPdnId             = ucPdnId;
    pstApsModifyInd->enPdnType           = g_stPppContext.enPdnType;

    pstLcpInfo                           = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;
    pstIpcpInfo                          = (PPPIPCPINFO_S *)pstPppInfo->pstIpcpInfo;
    pstIpv6cpInfo                        = (PPPIPV6CPINFO_S *)pstPppInfo->pstIpV6cpInfo;

    if (VOS_NULL_PTR != pstLcpInfo)
    {
        pstApsModifyInd->usMtu           = pstLcpInfo->stHisOptions.mru;
    }
    else
    {
        pstApsModifyInd->usMtu           = PPPC_MAX_FRAME_LEN;
    }

    if (VOS_NULL_PTR != pstIpcpInfo)
    {
        pstIpcpOption                             = &(pstIpcpInfo->stGotOptions);
        pstApsModifyInd->stIpv4Dns.bitOpIpv4PrimDNS  = pstIpcpOption->req_dnsaddr0;
        pstApsModifyInd->stIpv4Dns.bitOpIpv4SecDNS   = pstIpcpOption->req_dnsaddr1;
        PS_MEM_CPY(pstApsModifyInd->aucIpv4Addr, &(pstIpcpOption->ouraddr),
            sizeof(pstApsModifyInd->aucIpv4Addr));
        PS_MEM_CPY(pstApsModifyInd->stIpv4Dns.aucIpv4PrimDNS, &(pstIpcpOption->dnsaddr0),
            sizeof(pstApsModifyInd->stIpv4Dns.aucIpv4PrimDNS));
        PS_MEM_CPY(pstApsModifyInd->stIpv4Dns.aucIpv4SecDNS, &(pstIpcpOption->dnsaddr1),
            sizeof(pstApsModifyInd->stIpv4Dns.aucIpv4SecDNS));
    }

    if (VOS_NULL_PTR != pstIpv6cpInfo)
    {
        pstIpv6cpOption                           = &(pstIpv6cpInfo->stGotOptions);
        PS_MEM_CPY(pstApsModifyInd->aucIpv6Addr, pstIpv6cpOption->HisV6InId,
            sizeof(pstIpv6cpOption->HisV6InId));
    }

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstApsModifyInd))
    {
        PPPC_WARNING_LOG("Warning:Send ID_PPP_APS_MODIFY_IND msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_IsReadyToRespActCmd
 功能描述  : 网络协商完成后，根据PDNType来判断是否通知APS
 输入参数  : pPppInfo       PPP信息，激活失败时填VOS_NULL_PTR,否则非空
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_IsReadyToRespActCmd(VOS_VOID* pPppInfo)
{
    PPPINFO_S                          *pstPppInfo;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstApsMsgNode;
    TTF_LINK_ST                        *pstApsPppCmdLink;
    VOS_UINT32                          ulRet = VOS_ERR;


    if (VOS_NULL_PTR == pPppInfo)
    {
        return;
    }

    pstPppInfo        = (PPPINFO_S *)pPppInfo;

    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_RespApsModifyIndCmd(pstPppInfo);
        return;
    }

    switch(pstApsMsgNode->stApsCmdNode.enPdnType)
    {
        case TAF_APS_PPP_ADDR_TYPE_IPV4:
            if (pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV6:
            if (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS)
            {
                ulRet = VOS_OK;
            }
            break;
        case TAF_APS_PPP_ADDR_TYPE_IPV4V6:
            if ((pstPppInfo->bPppStateFlg == PPP_STATE_SUCCESS)
                && (pstPppInfo->bPppStateFlgV6 == PPP_STATE_SUCCESS))
            {
                ulRet = VOS_OK;
            }
            break;
        default:
            break;
    }

    if (VOS_OK == ulRet)
    {
        g_stPppContext.enPdnType = pstApsMsgNode->stApsCmdNode.enPdnType;
        PPPC_RespApsActCmd(pPppInfo, VOS_OK);
    }

}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmAttachFail
 功能描述  : PPP回复Ehsm Attach失败
 输入参数  : pstAttachReq   CNAS_CTTF_EHRPD_ATTACH_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmAttachFail
(
    CNAS_CTTF_EHRPD_ATTACH_REQ_STRU    *pstAttachReq
)
{
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pstAttachCnf;


    /* 申请响应消息内存 */
    pstAttachCnf    = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnf)
    {
        PPPC_ERROR_LOG("Alloc Ehsm Attach Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstAttachCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU) - PPPC_OM_ATTACH_CNF_OFFSET_LEN);
    pstAttachCnf->ulReceiverPid         = pstAttachReq->ulSenderPid;
    pstAttachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstAttachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_ATTACH_CNF;
    pstAttachCnf->usOpId                = pstAttachReq->usOpId;
    pstAttachCnf->ucPdnId               = pstAttachReq->ucPdnId;
    pstAttachCnf->enAttachRslt          = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    pstAttachCnf->enErrorCode           = CNAS_CTTF_EHRPD_ERROR_CODE_PARA_ERROR;
    pstAttachCnf->enAttachType          = pstAttachReq->enAttachType;
    pstAttachCnf->enPdnType             = pstAttachReq->enPdnType;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstAttachCnf))
    {
        PPPC_WARNING_LOG("Error:Send ID_CTTF_CNAS_EHRPD_ATTACH_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_ATTACH_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmDetachFail
 功能描述  : PPP回复Ehsm Detach失败
 输入参数  : pstDetachReq   CNAS_CTTF_EHRPD_DETACH_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmDetachFail
(
    CNAS_CTTF_EHRPD_DETACH_REQ_STRU    *pstDetachReq
)
{
    CTTF_CNAS_EHRPD_DETACH_CNF_STRU    *pstDetachCnf;


    /* 申请响应消息内存 */
    pstDetachCnf    = (CTTF_CNAS_EHRPD_DETACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU));
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        PPPC_ERROR_LOG("Alloc Ehsm Detach Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstDetachCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU) - PPPC_OM_DETACH_CNF_OFFSET_LEN);
    pstDetachCnf->ulReceiverPid         = pstDetachReq->ulSenderPid;
    pstDetachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstDetachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_DETACH_CNF;
    pstDetachCnf->usOpId                = pstDetachReq->usOpId;
    pstDetachCnf->enDetachRslt          = CNAS_CTTF_EHRPD_RSLT_FAILURE;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachCnf))
    {
        PPPC_WARNING_LOG("Error:Send ID_CTTF_CNAS_EHRPD_DETACH_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_DETACH_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnConnectFail
 功能描述  : PPP回复PDN Connect失败
 输入参数  : pstPdnConnectReq   CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnConnectFail
(
    CNAS_CTTF_EHRPD_PDN_CONN_REQ_STRU  *pstPdnConnectReq
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnConnectCnf;


    /* 申请响应消息内存 */
    pstPdnConnectCnf = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnConnectCnf)
    {
        PPPC_WARNING_LOG("Alloc PDN Connect Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstPdnConnectCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU) - PPPC_OM_PDN_CONN_CNF_OFFSET_LEN);
    pstPdnConnectCnf->ulReceiverPid         = pstPdnConnectReq->ulSenderPid;
    pstPdnConnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnConnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF;
    pstPdnConnectCnf->usOpId                = pstPdnConnectReq->usOpId;
    pstPdnConnectCnf->enPdnConnRslt         = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    pstPdnConnectCnf->ucPdnId               = pstPdnConnectReq->ucPdnId;
    pstPdnConnectCnf->enErrorCode           = CNAS_CTTF_EHRPD_ERROR_CODE_PARA_ERROR;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnConnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnDisconnectFail
 功能描述  : PPP回复Ehsm PDN Disconnect失败
 输入参数  : pstPdnDisconnectReq   CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnDisconnectFail
(
    CNAS_CTTF_EHRPD_PDN_DISC_REQ_STRU  *pstPdnDisconnectReq
)
{
    CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU  *pstPdnDisconnectCnf;


    /* 申请响应消息内存 */
    pstPdnDisconnectCnf  = (CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnDisconnectCnf)
    {
        PPPC_WARNING_LOG("Alloc PDN Disconnect Cnf Mem Fail!\r\n");
        return;
    }

    PS_MEM_SET(&(pstPdnDisconnectCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU) - PPPC_OM_PDN_DISC_CNF_OFFSET_LEN);
    pstPdnDisconnectCnf->ulReceiverPid         = pstPdnDisconnectReq->ulSenderPid;
    pstPdnDisconnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnDisconnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF;
    pstPdnDisconnectCnf->usOpId                = pstPdnDisconnectReq->usOpId;
    pstPdnDisconnectCnf->enDiscRslt            = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    pstPdnDisconnectCnf->ucPdnId               = pstPdnDisconnectReq->ucPdnId;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDisconnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF msg fail!");
    }

    PPPC_INFO_LOG("Succeed to send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF!!!\n");
    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmAttachCmd
 功能描述  : PPP回复Ehsm激活PPP命令
 输入参数  : pIpcpInfo      IPCP信息，激活失败时填VOS_NULL_PTR,否则非空
             ulResult       VOS_OK/VOS_ERR
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmAttachCmd(VOS_VOID* pVsncpInfo, VOS_UINT32 ulResult)
{
    PPPINFO_S                          *pstPppInfo;
    PPPLCPINFO_S                       *pstLcpInfo;
    PPPVSNCPINFO_S                     *pstVsncpInfo;
    CTTF_CNAS_EHRPD_ATTACH_CNF_STRU    *pstAttachCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    ulRet = PPP_GetPDNContextByPDNID(pstEhsmMsgNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstEhsmMsgNode->ucPdnId);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);
        return;
    }

    /* 申请响应消息内存 */
    pstAttachCnf    = (CTTF_CNAS_EHRPD_ATTACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU));
    if (VOS_NULL_PTR == pstAttachCnf)
    {
        PPPC_WARNING_LOG1("Alloc Attach Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET(&(pstAttachCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_ATTACH_CNF_STRU) - PPPC_OM_ATTACH_CNF_OFFSET_LEN);
    pstAttachCnf->ulReceiverPid         = pstEhsmMsgNode->ulSenderPid;
    pstAttachCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstAttachCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_ATTACH_CNF;
    pstAttachCnf->usOpId                = pstEhsmMsgNode->usOpId;
    pstAttachCnf->ucPdnId               = pstEhsmMsgNode->ucPdnId;

    if (VOS_OK == ulResult)
    {
        pstAttachCnf->enAttachRslt      = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
        pstAttachCnf->enErrorCode       = CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_BUTT;
    }
    else
    {
        pstAttachCnf->enAttachRslt      = CNAS_CTTF_EHRPD_RSLT_FAILURE;
        pstAttachCnf->enErrorCode       = pstPDNContext->stEhrpd.enErrorCode;

        PPPC_ClearMappingByPppId(pstEhsmMsgNode->ucPppId);
        PPPC_DeletePppId(pstEhsmMsgNode->ucPppId);
    }

    pstAttachCnf->enAttachType          = pstPDNContext->stEhrpd.enAttachType;
    pstAttachCnf->enPdnType             = pstPDNContext->stEhrpd.enPdnType;
    pstAttachCnf->ucAddressAllocCause   = pstPDNContext->stEhrpd.ucAddressAllocCause;
    pstAttachCnf->usMtu                 = PPPC_MAX_FRAME_LEN;

    if (VOS_NULL_PTR != pVsncpInfo)
    {
        pstVsncpInfo                    = (PPPVSNCPINFO_S *)pVsncpInfo;
        pstPppInfo                      = (PPPINFO_S *)(pstVsncpInfo->pstPppInfo);

        if (VOS_NULL_PTR != pstPppInfo)
        {
            pstLcpInfo                  = (PPPLCPINFO_S *)pstPppInfo->pstLcpInfo;

            if (VOS_NULL_PTR != pstLcpInfo)
            {
                pstAttachCnf->usMtu     = pstLcpInfo->stHisOptions.mru;
            }
        }
    }

    /* 拷贝APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstAttachCnf->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstAttachCnf->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstAttachCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_ATTACH_CNF msg fail!");
    }
    else
    {
        if (VOS_OK == ulResult)
        {
            /* 此时可以收发数据，通知PA open stream */
            PPPC_HRPD_SendOpenStreamReq();
        }
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmDetachCmd
 功能描述  : 回复去激活消息
 输入参数  : ulResult   去激活结果
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmDetachCmd(VOS_UINT32 ulResult)
{
    CTTF_CNAS_EHRPD_DETACH_CNF_STRU    *pstDetachCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (VOS_OK == ulResult)
    {
        /* 此时没有PDN连接不能收发数据，通知PA close stream */
        PPPC_HRPD_SendCloseStreamReq();
    }

    PPPC_DeletePppId(pstEhsmMsgNode->ucPppId);

    /* 申请响应消息内存 */
    pstDetachCnf    = (CTTF_CNAS_EHRPD_DETACH_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU));
    if (VOS_NULL_PTR == pstDetachCnf)
    {
        PPPC_WARNING_LOG1("Alloc PPP Detach Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET(&(pstDetachCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_DETACH_CNF_STRU) - PPPC_OM_DETACH_CNF_OFFSET_LEN);
    pstDetachCnf->ulReceiverPid       = pstEhsmMsgNode->ulSenderPid;
    pstDetachCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDetachCnf->enMsgId             = ID_CTTF_CNAS_EHRPD_DETACH_CNF;
    pstDetachCnf->usOpId              = pstEhsmMsgNode->usOpId;

    if (VOS_OK == ulResult)
    {
        pstDetachCnf->enDetachRslt    = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
    }
    else
    {
        pstDetachCnf->enDetachRslt    = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    }

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_DETACH_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    return;
}


VOS_VOID PPPC_SendPdnConnectCnf
(
    PPPC_APS_MSG_LINK_NODE_STRU        *pstMsgLinkNode,
    VOS_UINT32                          ulResult
)
{
    CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU  *pstPdnConnectCnf;
    PDN_CONTEXT_S                      *pstPDNContext;
    VOS_UINT32                          ulRet;


    ulRet = PPP_GetPDNContextByPDNID(pstMsgLinkNode->ucPdnId, &pstPDNContext);
    if ((VOS_OK != ulRet) || (VOS_NULL_PTR == pstPDNContext))
    {
        PPPC_WARNING_LOG1("Get PDN Context failed. PDNId:%d.", pstMsgLinkNode->ucPdnId);

        return;
    }

    /* 申请响应消息内存 */
    pstPdnConnectCnf    = (CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnConnectCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Act Cnf Mem Fail!\r\n", ulResult);

        return;
    }

    PS_MEM_SET(&(pstPdnConnectCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_CONN_CNF_STRU) - PPPC_OM_PDN_CONN_CNF_OFFSET_LEN);
    pstPdnConnectCnf->ulReceiverPid         = pstMsgLinkNode->ulSenderPid;
    pstPdnConnectCnf->ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstPdnConnectCnf->enMsgId               = ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF;
    pstPdnConnectCnf->usOpId                = pstMsgLinkNode->usOpId;

    if (VOS_OK == ulResult)
    {
        pstPdnConnectCnf->enPdnConnRslt     = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
        pstPdnConnectCnf->enErrorCode       = CNAS_CTTF_EHRPD_ERROR_CODE_ENUM_BUTT;
    }
    else
    {
        pstPdnConnectCnf->enPdnConnRslt     = CNAS_CTTF_EHRPD_RSLT_FAILURE;
        pstPdnConnectCnf->enErrorCode       = pstPDNContext->stEhrpd.enErrorCode;

        PPPC_ClearMappingByPdnId(pstMsgLinkNode->ucPdnId);
    }
    pstPdnConnectCnf->ucPdnId               = pstMsgLinkNode->ucPdnId;
    pstPdnConnectCnf->enAttachType          = pstPDNContext->stEhrpd.enAttachType;
    pstPdnConnectCnf->enPdnType             = pstPDNContext->stEhrpd.enPdnType;
    pstPdnConnectCnf->ucAddressAllocCause   = pstPDNContext->stEhrpd.ucAddressAllocCause;

    /* 拷贝APN */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stApn),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApn), sizeof(CNAS_CTTF_EHRPD_APN_STRU));
    /* 拷贝AMBR */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stApnAmbr),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stApnAmbr), sizeof(CNAS_CTTF_EHRPD_APN_AMBR_STRU));
    /* 拷贝PDN Address */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stPdnAddress),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPdnAddress), sizeof(CNAS_CTTF_EHRPD_PDN_ADDRESS_STRU));
    /* 拷贝PCO */
    PS_MEM_CPY((VOS_INT8 *)&(pstPdnConnectCnf->stPco),
        (VOS_INT8 *)&(pstPDNContext->stEhrpd.stPco), sizeof(CNAS_CTTF_EHRPD_PCO_STRU));
    /* 拷贝Ipv4 router address */
    PS_MEM_CPY((VOS_INT8 *)pstPdnConnectCnf->aucIpv4DefaultRouterAddress,
        (VOS_INT8 *)pstPDNContext->stEhrpd.aucIpv4DefaultRouterAddress, CNAS_CTTF_EHRPD_IPV4_ADDRESS_LEN);

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnConnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_CONN_CNF msg fail!");
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnConnectCmd
 功能描述  : PPP回复Ehsm PDN Connect Request消息
 输入参数  : pIpcpInfo      IPCP信息，激活失败时填VOS_NULL_PTR,否则非空
             ulResult       VOS_OK/VOS_ERR
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnConnectCmd
(
    VOS_VOID                           *pVsncpInfo,
    VOS_UINT32                          ulResult
)
{
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    if (VOS_OK == PPPC_IsPdnIdUnique(pstEhsmMsgNode->ucPdnId))
    {
        PPPC_INFO_LOG("The PDN Id is unique!\r\n");
        PPPC_RespEhsmAttachCmd(pVsncpInfo, ulResult);
        return;
    }

    /* 发送PDN Connect Cnf消息 */
    PPPC_SendPdnConnectCnf(pstEhsmMsgNode, ulResult);

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    if (VOS_OK == ulResult)
    {
        /* 此时可以收发数据，通知PA open stream */
        PPPC_HRPD_SendOpenStreamReq();
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_RespEhsmPdnDisconnectCmd
 功能描述  : 回复Ehsm PDN Disconnect Request消息
 输入参数  : ulResult   PDN Disconnect结果
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_RespEhsmPdnDisconnectCmd(VOS_UINT32 ulResult)
{
    CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU  *pstPdnDisconnectCnf;
    TTF_LINK_ST                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU        *pstEhsmMsgNode;


    pstEhsmPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstEhsmMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_WARNING_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    PPPC_ClearMappingByPdnId(pstEhsmMsgNode->ucPdnId);

    /* 申请响应消息内存 */
    pstPdnDisconnectCnf    = (CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU));
    if (VOS_NULL_PTR == pstPdnDisconnectCnf)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Disconnect Cnf Mem Fail!\r\n", ulResult);

        /* 发送响应消息失败也要删除节点 */
        pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                            MSPS_PID_PPPC, pstEhsmPppCmdLink);

        PPP_Free(pstEhsmMsgNode);

        return;
    }

    PS_MEM_SET(&(pstPdnDisconnectCnf->enMsgId), 0,
        sizeof(CTTF_CNAS_EHRPD_PDN_DISC_CNF_STRU) - PPPC_OM_PDN_DISC_CNF_OFFSET_LEN);
    pstPdnDisconnectCnf->ulReceiverPid       = pstEhsmMsgNode->ulSenderPid;
    pstPdnDisconnectCnf->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPdnDisconnectCnf->enMsgId             = ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF;
    pstPdnDisconnectCnf->usOpId              = pstEhsmMsgNode->usOpId;
    pstPdnDisconnectCnf->ucPdnId             = pstEhsmMsgNode->ucPdnId;

    if (VOS_OK == ulResult)
    {
        pstPdnDisconnectCnf->enDiscRslt      = CNAS_CTTF_EHRPD_RSLT_SUCCESS;
    }
    else
    {
        pstPdnDisconnectCnf->enDiscRslt      = CNAS_CTTF_EHRPD_RSLT_FAILURE;
    }

    /* 发送去激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDisconnectCnf))
    {
        PPPC_WARNING_LOG("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_CNF msg fail!");
    }

    /* 处理完毕，从链表中删除节点并释放内存 */
    pstEhsmMsgNode   = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkRemoveHead(
                        MSPS_PID_PPPC, pstEhsmPppCmdLink);

    PPP_Free(pstEhsmMsgNode);

    PPPC_EhsmMsgNodeProc();

    return;
}
VOS_VOID PPPC_JudgeApsCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    TTF_LINK_ST                            *pstApsPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU            *pstApsMsgNode;
    TAF_APS_PPP_PIF_MSG_TYPE_ENUM_UINT16    enMsgType;


    pstApsPppCmdLink  = &g_stApsCmdLink;

    /* 在APS命令链表中取头节点 */
    pstApsMsgNode     = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstApsPppCmdLink);
    if (VOS_NULL_PTR == pstApsMsgNode)
    {
        PPPC_INFO_LOG("APS Cmd Link is Empty!\r\n");
        return;
    }

    enMsgType   = pstApsMsgNode->stApsCmdNode.enMsgType;
    if (ID_APS_PPP_ACT_REQ == enMsgType)
    {
        /* 如果节点中的消息类型是PPP激活消息，此时却删除PPP控制块说明协商失败 */
        PPPC_RespApsActCmd(VOS_NULL_PTR, VOS_ERR);
    }
    else if (ID_APS_PPP_DEACT_REQ == enMsgType)
    {
        /* 如果节点中的消息类型是PPP去激活消息，此时已达到目的，回复成功 */
        PPPC_RespApsDeActCmd(VOS_OK);
    }
    else
    {
        /* nothing */
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_JudgeEhsmCmdRseultWhenDeleteCB
 功能描述  : 判断当删除PPP控制块时是否需要及填写什么响应消息和结果,如果是去激活
             消息,即使协商失败也会删除PPP控制块因此可以直接回复成功
 输入参数  : ucPppId
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_JudgeEhsmCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    TTF_LINK_ST                                        *pstEhsmPppCmdLink;
    PPPC_APS_MSG_LINK_NODE_STRU                        *pstEhsmMsgNode;
    CNAS_CTTF_EHRPD_PIF_MSG_TYPE_ENUM_UINT16            enMsgType;


    /* 由网侧断开所有PDN连接导致PPP释放链路 */
    if (PS_TRUE == g_astPppPool[ucPppId].enServerTermReq)
    {
        PPPC_SendEhsmDetachNotify(ucPppId);
        return;
    }

    pstEhsmPppCmdLink = &g_stApsCmdLink;

    /* 在EHSM命令链表中取头节点 */
    pstEhsmMsgNode    = (PPPC_APS_MSG_LINK_NODE_STRU *)TTF_LinkPeekHead(MSPS_PID_PPPC, pstEhsmPppCmdLink);
    if (VOS_NULL_PTR == pstEhsmMsgNode)
    {
        PPPC_INFO_LOG("EHSM Cmd Link is Empty!\r\n");
        return;
    }

    enMsgType   = pstEhsmMsgNode->stEhsmCmdNode.enMsgType;

    switch(enMsgType)
    {
        case ID_CNAS_CTTF_EHRPD_ATTACH_REQ:

            /* 如果节点中的消息类型是激活消息，此时却删除PPP控制块说明协商失败 */
            PPPC_RespEhsmAttachCmd(VOS_NULL_PTR, VOS_ERR);

            break;

        case ID_CNAS_CTTF_EHRPD_DETACH_REQ:

            /* 如果节点中的消息类型是去激活消息，此时已达到目的，回复成功 */
            PPPC_RespEhsmDetachCmd(VOS_OK);

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_CONN_REQ:

            PPPC_RespEhsmPdnConnectCmd(VOS_NULL_PTR, VOS_ERR);

            break;

        case ID_CNAS_CTTF_EHRPD_PDN_DISC_REQ:

            PPPC_RespEhsmPdnDisconnectCmd(VOS_OK);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Ehsm Cmd", enMsgType);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_JudgeCmdRseultWhenDeleteCB
 功能描述  : 判断当删除PPP控制块时是否需要及填写什么响应消息和结果,如果是去激活
             消息,即使协商失败也会删除PPP控制块因此可以直接回复成功
 输入参数  : ucPppId
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_JudgeCmdRseultWhenDeleteCB(VOS_UINT8 ucPppId)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;


    enRatMode = PPPC_GetRatMode();
    switch(enRatMode)
    {
        case PPPC_RAT_MODE_1X:
        case PPPC_RAT_MODE_HRPD:

            PPPC_JudgeApsCmdRseultWhenDeleteCB(ucPppId);

            break;

        case PPPC_RAT_MODE_EHRPD:

            PPPC_JudgeEhsmCmdRseultWhenDeleteCB(ucPppId);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Rat mode", enRatMode);

            break;
    }

    return;
}


VOS_VOID PPPC_SendApsDeactNotify(VOS_UINT8 ucPppId)
{
    PPP_APS_DEACT_NTF_STRU             *pstDeactNotify;
    VOS_UINT8                           ucPdnId = 0;


    if (VOS_OK != PPPC_1X_GetPdnId(ucPppId, &ucPdnId))
    {
        PPPC_WARNING_LOG1("Get Pdn Id failed, ucPppId:[%d]\n", ucPppId);
        PPPC_DeletePppId(ucPppId);
        return;
    }

    PPPC_DeletePppId(ucPppId);

    pstDeactNotify  = (PPP_APS_DEACT_NTF_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(PPP_APS_DEACT_NTF_STRU));
    if (VOS_NULL_PTR == pstDeactNotify)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Deact Notify Mem Fail! PppId:%d\n", ucPppId);
        return;
    }

    PS_MEM_SET(&(pstDeactNotify->enMsgId), 0, (sizeof(PPP_APS_DEACT_NTF_STRU) - PPPC_OM_DEACT_NOTIFY_OFFSET_LEN));
    pstDeactNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstDeactNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDeactNotify->enMsgId             = ID_PPP_APS_DEACT_NTF;
    pstDeactNotify->usOpId              = 0;
    pstDeactNotify->ucPdnId             = ucPdnId;
    pstDeactNotify->enMode              = PPPC_GetRatMode();

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDeactNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_PPP_APS_DEACT_NOTIFY msg fail! PppId:%d\n", ucPppId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendEhsmPdnDisconnectNotify
 功能描述  : 给EHSM发送PDN Disconnect通知
 输入参数  : ucPdnId    PDN ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendEhsmPdnDisconnectNotify(VOS_UINT8 ucPdnId)
{
    CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU  *pstPdnDiscNotify;
    VOS_UINT8                           ucPppId;
    VOS_UINT32                          ulLcpSendFlag;


    if (VOS_OK == PPPC_IsPdnIdUnique(ucPdnId))
    {
        PPPC_INFO_LOG("The pdn Id is unique!\r\n");
        if (VOS_OK == PPPC_GetPppIdByPdn(ucPdnId, &ucPppId))
        {
            PPPC_INFO_LOG("Get PppId successed!\r\n");

            g_astPppPool[ucPppId].enServerTermReq = PS_TRUE;

            /* 此时需要发送ppp terminate协商报文 */
            ulLcpSendFlag                    = 1;

            /* PPP发起PPP去激活 */
            PPPC_LinkDown(ucPppId, ulLcpSendFlag);
        }
        else
        {
            PPPC_WARNING_LOG1("Get PppId failed! PdnId:%d\n", ucPdnId);
        }
        return;
    }

    PPPC_ClearMappingByPdnId(ucPdnId);

    pstPdnDiscNotify  = (CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU));
    if (VOS_NULL_PTR == pstPdnDiscNotify)
    {
        PPPC_WARNING_LOG("Alloc Ppp Pdn Disconnect Notify Mem Fail!\r\n");

        return;
    }

    PS_MEM_SET(&(pstPdnDiscNotify->enMsgId), 0,
                (sizeof(CTTF_CNAS_EHRPD_PDN_DISC_IND_STRU) - PPPC_OM_PDN_DISC_IND_OFFSET_LEN));
    pstPdnDiscNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstPdnDiscNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstPdnDiscNotify->enMsgId             = ID_CTTF_CNAS_EHRPD_PDN_DISC_IND;
    pstPdnDiscNotify->usOpId              = 0;
    pstPdnDiscNotify->ucPdnId             = ucPdnId;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstPdnDiscNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_CTTF_CNAS_EHRPD_PDN_DISC_IND msg fail! PdnID:%d\n", ucPdnId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_SendEhsmDetachNotify
 功能描述  : 给EHSM发送去激活通知
 输入参数  : ucPppId    PPP ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_SendEhsmDetachNotify(VOS_UINT8 ucPppId)
{
    CTTF_CNAS_EHRPD_DETACH_IND_STRU    *pstDetachNotify;


    /* 此时PPPC不能发送数据,通知PA关闭流 */
    PPPC_HRPD_SendCloseStreamReq();

    PPPC_DeletePppId(ucPppId);

    pstDetachNotify  = (CTTF_CNAS_EHRPD_DETACH_IND_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                            MSPS_PID_PPPC, sizeof(CTTF_CNAS_EHRPD_DETACH_IND_STRU));
    if (VOS_NULL_PTR == pstDetachNotify)
    {
        PPPC_WARNING_LOG1("Alloc Ppp Detach Notify Mem Fail! PppId:%d\n", ucPppId);

        return;
    }

    PS_MEM_SET(&(pstDetachNotify->enMsgId), 0,
                (sizeof(CTTF_CNAS_EHRPD_DETACH_IND_STRU) - PPPC_OM_DETACH_IND_OFFSET_LEN));
    pstDetachNotify->ulReceiverPid       = g_stPppContext.ulSendPid;
    pstDetachNotify->ulReceiverCpuId     = VOS_LOCAL_CPUID;
    pstDetachNotify->enMsgId             = ID_CTTF_CNAS_EHRPD_DETACH_IND;
    pstDetachNotify->usOpId              = 0;

    /* 发送激活响应消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstDetachNotify))
    {
        PPPC_WARNING_LOG1("Warning:Send ID_CTTF_CNAS_EHRPD_DETACH_IND msg fail! PppId:%d\n", ucPppId);
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_ReceiveLCPTermReq
 功能描述  : 收到网侧去激活通知
 输入参数  : ucPppId    PPP ID
 输出参数  : 无
 返 回 值  : VOID
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-05-24
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_VOID PPPC_ReceiveLCPTermReq(VOS_UINT8 ucPppId)
{
    PPPC_RAT_MODE_ENUM_UINT8            enRatMode;


    enRatMode = PPPC_GetRatMode();
    switch(enRatMode)
    {
        case PPPC_RAT_MODE_1X:
        case PPPC_RAT_MODE_HRPD:

            PPPC_SendApsDeactNotify(ucPppId);

            break;

        case PPPC_RAT_MODE_EHRPD:

            PPPC_SendEhsmDetachNotify(ucPppId);

            break;

        default:

            PPPC_WARNING_LOG1("Invalid Rat mode", enRatMode);

            break;
    }

    return;
}

/*****************************************************************************
 函 数 名  : PPPC_UIM_MD5ChapAuthReq
 功能描述  : HRPD模式，CHAP鉴权，由UIM卡使用MD5算法计算，由SIM卡产生Response
 输入参数  : PPPINFO_S *pstPppInfo, PPPAUTHMSG_S *pstAuthMsg
 输出参数  : 无
 返 回 值  : VOS_UINT32
 调用函数  :
 被调函数  :

 修改历史      :
  1.日    期   : 2015-06-29
    作    者   : w00316385
    修改内容   : 新生成函数
*****************************************************************************/
VOS_UINT32 PPPC_UIM_MD5ChapAuthReq(PPPINFO_S *pstPppInfo, PPPAUTHMSG_S *pstAuthMsg)
{
    USIMM_CDMASPECAUTH_REQ_STRU        *pstMsg;


    /* 内部调用，保证入参非空 */

    /* 申请消息内存 */
    pstMsg   = (USIMM_CDMASPECAUTH_REQ_STRU *)PS_ALLOC_MSG_WITH_HEADER_LEN(
                        MSPS_PID_PPPC, sizeof(USIMM_CDMASPECAUTH_REQ_STRU));
    if (VOS_NULL_PTR == pstMsg)
    {
        PPPC_ERROR_LOG("Alloc pstMsg Mem Fail!\r\n");
        return VOS_ERR;
    }

    /*填充消息内容*/
    PS_MEM_SET((VOS_UINT8 *)pstMsg + VOS_MSG_HEAD_LENGTH, 0,
        sizeof(USIMM_CDMASPECAUTH_REQ_STRU) - VOS_MSG_HEAD_LENGTH);
    pstMsg->stMsgHeader.ulReceiverPid         = WUEPS_PID_USIM;
    pstMsg->stMsgHeader.ulReceiverCpuId       = VOS_LOCAL_CPUID;
    pstMsg->stMsgHeader.enMsgName             = USIMM_CDMASPECAUTH_REQ;
    pstMsg->stMsgHeader.enAppType             = USIMM_CDMA_APP;

    pstMsg->enAuthType                        = USIMM_CDMASPEC_COMPUTEIP;
    pstMsg->uAuthData.stComputeIP.enComputeIPType = USIMM_COMPUTEIP_HRPD;
    pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.ucCHAPID = pstAuthMsg->ucPktID;
    pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.stChapChallenge.ucDataLen = pstAuthMsg->ucPwdLen;


    PS_MEM_CPY(pstMsg->uAuthData.stComputeIP.uComputeIPData.stHRPDData.stChapChallenge.aucData,
                pstAuthMsg->szPwd, pstAuthMsg->ucPwdLen);

    /* 发送消息 */
    if (VOS_OK != PS_SEND_MSG(MSPS_PID_PPPC, pstMsg))
    {
        PPPC_WARNING_LOG("Warning:Send USIMM_CDMASPECAUTH_REQ msg fail!");
        return VOS_ERR;
    }

    return VOS_OK;
}


/*lint -restore */

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

