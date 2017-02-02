/******************************************************************************

   Copyright(C)2008,Hisilicon Co. LTD.

 ******************************************************************************
  File Name       : dhcpv4s_pub.c
  Description     :
  History         :
     1.w00316385       2015-04-15   Draft Enact

******************************************************************************/


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
  1 Include HeadFile
*****************************************************************************/
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_fun.h"



/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_PUB_C
/*lint +e767*/


ULONG DHCPS_FSM_REQUESTIP_AddressAllocateFailed(
          DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}


ULONG DHCPS_FSM_REQUESTIP_Deactive(  DHCPS_PRE_RESULT_S *pstPreResult,
                                                  DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}


ULONG DHCPS_FSM_REQUESTIP_USMTimerOut(
          DHCPS_PRE_RESULT_S *pstPreResult,DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_OFFERED_ReceiveDiscover(DHCPS_PRE_RESULT_S *pstPreResult,
                                        DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_OFFERED_ReceiveRequest(DHCPS_PRE_RESULT_S *pstPreResult,
                                  DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_Deactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_OFFERED_ClientTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_ReceiveDiscover(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_ReceiveRequest(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveInform(DHCPS_PRE_RESULT_S *pstPreResult,
                                       DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
ULONG DHCPS_FSM_COMMITED_ReceiveDeactive(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

ULONG DHCPS_FSM_COMMITED_LeaseTimerOut(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}


ULONG DHCPS_FSM_RELAY_ReceiveRelease(
              DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}


ULONG DHCPS_FSM_RELAY_ReceiveDecline(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}


ULONG DHCPS_FSM_RELAY_ReceiveDeactive(
            DHCPS_PRE_RESULT_S *pstPreResult, DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}


ULONG DHCPS_FSM_IDLE_ReceiveDiscover(DHCPS_PRE_RESULT_S *pstPreResult,
                                     DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}


ULONG DHCPS_FSM_IDEL_ReceiveRequest(DHCPS_PRE_RESULT_S *pstPreResult,
                                    DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}
/*****************************************************************************
 函 数 名      : DHCPS_FSM_IDEL_ReceiveDiscover
 功能描述   : 清除租约信息，释放资源
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_IDLE_ReceiveRelease(
                                                                             DHCPS_PRE_RESULT_S *pstPreResult,
                                                                             DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_REQUESTIP_ReceiveRelease
 功能描述   : 收到Release消息(按说不应该收到的)，
                            不回应响应消息给UE  ，
                            状态切换到IDEL，
                            REQUESTIP-->IDLE。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_REQUESTIP_AddressAllocateSuccess
 功能描述   : 发送OFFER消息给SGW，
                           启动等待Request消息的定时器2，
                           状态由REQUESTIP－－>OFFERED。
                           本地保存地址记录信息，
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年11月27日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_AddressAllocateSuccess(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*=======================================================================
 *  函数名称:  ICMPv6_CheckSum
 *  初稿完成:  2004/07/30
 *  作    者:    屈琴
 *  函数功能:  计算ICMPv6报文的校验和
 *                           ptr参数指向的报文会被覆盖，请注意需要事先保存
 *  输入参数:
 *  输出参数:  无
 *  返回类型:
 *  全局变量:
 *  其他说明:  无
 *  调用函数:
 *  主调函数:   IPV6_TimerOutProc
 *=======================================================================*/
USHORT ICMPv6_CheckSum(UCHAR *ptr, const in6_addr src, const in6_addr des, const UCHAR *msg,
                                                    USHORT usLen, USHORT *pusCheckSum, UCHAR ucPro)
{
    return VOS_OK;
}

ULONG UGW_GtpEncap( PMBUF_S *pMbuf, ULONG ulPdpIndex )
{
    return 0;
}


ULONG UGW_GRE_Encap(PMBUF_S *pMbuf, ULONG ulPdpIndex )
{
    return VOS_OK;
}


ULONG AM_CtxApiGetApnInfo( ULONG ulPdnIndex, AM_CTX_APN_INFO_S *pstApnInfo)
{
    return VOS_OK;
}

VOID UGW_OmAccessMsgTrc(UCHAR *pMsg,
                      E_TRACE_TYPE enTraceType,
                      ULONG  ulMsgClass,
                      ULONG  ulGtpMsgType,
                      ULONG  ulPeerIpAddr,
                      USHORT usMsgLen)
{
    return;
}

VOID GTPC_OmExternInterfaceTrcProcess(UCHAR *pMsg, E_TRACE_TYPE enTraceType, UGW_EXTERN_INTF_TRACE_S stTraceInfo)
{
    return;
}


VOID AM_CtxApiGetReqApnIndexByPdpContext(SDB_GSPU_CONTEXT_S *pstContext,USHORT *pusRequestIndex,UCHAR *pucAliaApnFlag)
{
    return;
}


ULONG IPV6_SrcAddrValidationCheck(IPV6HDR_S *pstIpv6Hdr)
{
    return VOS_OK;
}

PF_ULONG fwd_get_ctrlhdr_pdpindex(FWD_TO_CTRL_HDR* pstCtrlHdr)
{
    return pstCtrlHdr->ulPdpIndex;
}


VOID LAP_SetPrefixLengthIp(ULONG aulOldIp[], UCHAR ucPrefixLength, ULONG aulNewIp[],
                            UCHAR *pucPos, UCHAR *pucMoveBitNum)
{
    return;
}


ULONG PTM_DebugBatchSProcDebugCmdRspMsg(UCHAR *pucMsg)
{
    return VOS_OK;
}


VOS_UINT32 CLAP_TaskInit(VOS_UINT64 ullCsi, ULONG ulHandle)
{
    return VOS_OK;
}

/*****************************************************************************
 函 数 名      : DHCPS_FSM_PreMsgFromUSM
 功能描述   : 预处理从USM收到的消息，包括:申请地址成功，
                            申请地址失败，取活用户。
 输入参数   : 无
 输出参数   : 无
 返 回 值      : VOS_OK    成功; VOS_ERR    失败
 调用函数   :
 被调函数   :

 修改历史   :
  1.日    期      : 2008年12月5日
    作    者       : dongmingzhou 42828
    修改内容: 新生成函数

*****************************************************************************/
VOID DHCPS_FSM_PreMsgFromUSM(UCHAR *pucRspMsg)
{
    return;
}


ULONG CLAP_TaskConfirm(ULONG ulTaskID)
{
    return VOS_OK;
}


VOID CLAP_TaskProcess()
{
    return;
}


VOID Path_GetVpn(SDB_GSPU_CONTEXT_S *pstContext, ULONG *pulVpnId)
{
    return;
}




#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif


