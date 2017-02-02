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
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
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
 �� �� ��      : DHCPS_FSM_IDEL_ReceiveDiscover
 ��������   : �����Լ��Ϣ���ͷ���Դ
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_IDLE_ReceiveRelease(
                                                                             DHCPS_PRE_RESULT_S *pstPreResult,
                                                                             DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_REQUESTIP_ReceiveRelease
 ��������   : �յ�Release��Ϣ(��˵��Ӧ���յ���)��
                            ����Ӧ��Ӧ��Ϣ��UE  ��
                            ״̬�л���IDEL��
                            REQUESTIP-->IDLE��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_ReceiveRelease(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_REQUESTIP_AddressAllocateSuccess
 ��������   : ����OFFER��Ϣ��SGW��
                           �����ȴ�Request��Ϣ�Ķ�ʱ��2��
                           ״̬��REQUESTIP����>OFFERED��
                           ���ر����ַ��¼��Ϣ��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_FSM_REQUESTIP_AddressAllocateSuccess(
                                                                          DHCPS_PRE_RESULT_S *pstPreResult,
                                                                          DHCPS_STATE_RET *pstStateChangeRet)
{
    return VOS_OK;
}

/*=======================================================================
 *  ��������:  ICMPv6_CheckSum
 *  �������:  2004/07/30
 *  ��    ��:    ����
 *  ��������:  ����ICMPv6���ĵ�У���
 *                           ptr����ָ��ı��Ļᱻ���ǣ���ע����Ҫ���ȱ���
 *  �������:
 *  �������:  ��
 *  ��������:
 *  ȫ�ֱ���:
 *  ����˵��:  ��
 *  ���ú���:
 *  ��������:   IPV6_TimerOutProc
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
 �� �� ��      : DHCPS_FSM_PreMsgFromUSM
 ��������   : Ԥ�����USM�յ�����Ϣ������:�����ַ�ɹ���
                            �����ַʧ�ܣ�ȡ���û���
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��12��5��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

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


