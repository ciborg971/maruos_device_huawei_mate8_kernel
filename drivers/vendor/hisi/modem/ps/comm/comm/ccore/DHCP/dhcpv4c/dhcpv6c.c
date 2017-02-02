#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpv6_def.h"
#include "dhcpc_comp.h"
#include "dhcpc.h"
#include "dhcpc_dbg.h"
#include "dhcpc_table.h"
#include "dhcpc_var.h"
#include "dhcpv6c_pkt.h"
#include "dhcpv6c_fsm.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6C_C
/*lint +e767*/

DHCPC_EMS_INFO_S g_stDhcpcEmsInfo[DHCPV6C_CAUSE_BUFF] =
{
    /* NULL */
    {
        0,
        "N/A.",
        "N/A."
    },

    /* ��Լ���� */
    {
        EMS_CODE_DHCPV6C_LEASE_EXPIRE,
        "Lease of DHCPv6 server-assigned IP addresses expired.",
        "Check the DHCPv6 server status and the status of the link between the UGW9811 and the DHCPv6 server."
    },

    /* DHCPv6����������Ӧ */
    {
        EMS_CODE_DHCPV6C_SERVER_NO_RSP,
        "No response from the DHCP server.",
        "Check the DHCPv6 server status and the status of the link between the UGW9811 and the DHCPv6 server."
    },

    /* DHCPv6��������Ϣ�쳣 */
    {
        EMS_CODE_DHCPV6C_SERVER_MSG_EXCEPTION,
        "Abnormal messages sent by the DHCPv6 server.",
        "Check whether the DHCPv6 server is functioning properly and whether the messages sent by the DHCPv6 server are correct."
    },

    /* DHCPv6�������޵�ַ���� */
    {
        EMS_CODE_DHCPV6C_SERVER_NO_AVAILABLE_ADDR,
        "No available IP addresses for the DHCPv6 server.",
        "Check whether the DHCPv6 server has sufficient available IP addresses."
    },

    /* DHCPV6C Transaction Id�ľ� */
    {
        EMS_CODE_DHCPV6C_TID_EXHAUST,
        "DHCPv6 transaction IDs exhausted.",
        "Check whether the subscriber activation rate is at a peak and whether the link between the UGW9811 and the DHCPv6 server is functioning properly."
    }
};

ULONG DHCPC_PickUpDhcp(UDPS_PACKET_INFO_S * pstUdp, PMBUF_S *pstMbuf)
{
    UCHAR ucIpUdpHeadLen = IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    if (pstMbuf->stDataBlockDescriptor.ulDataLength <= ucIpUdpHeadLen)
    {
        return VOS_ERR;
    }

    pstMbuf->stDataBlockDescriptor.pucData      += ucIpUdpHeadLen;
    pstMbuf->stDataBlockDescriptor.ulDataLength -= ucIpUdpHeadLen;
    pstMbuf->ulTotalDataLength                  -= ucIpUdpHeadLen;

    return VOS_OK;
}


ULONG DHCPC_UnpackDhcpMsgFromMbuf(PMBUF_S *pstMsgBuf, UDPS_PACKET_INFO_S *pstPtkInf,
                                    UCHAR **ppucDhcpMsg, ULONG *pulMsgLen)
{
    ULONG ulRet = VOS_ERR;
    ULONG ulMsgLen = 0;

#if 0

    ulRet = (ULONG)UDPS_PickUpExt( pstPtkInf, pstMsgBuf );
    if ( VOS_OK != ulRet )
    {
        DHCPC_DebugPrint(PTM_LOG_WARNING, "call UDPS_PickUpExt fail! ulRet=%u", ulRet);
        return ulRet;
    }
#endif

    ulRet = DHCPC_PickUpDhcp(pstPtkInf, pstMsgBuf);
    if ( VOS_OK != ulRet )
    {
        DHCPC_DebugPrint(PTM_LOG_WARNING, "call DHCPC_PickUpDhcp fail! ulRet=%u", ulRet);
        return ulRet;
    }

    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (ulMsgLen > DHCP_PKT_ASSUME_MAX_LEN)
    {
        DHCPC_DebugPrint(PTM_LOG_WARNING, "receive malformed Packet. length=%u", ulMsgLen);
        return VOS_ERR;
    }

    /* ���Mbuf�Ƿ����Ϣ�����˷�Ƭ */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        /* û�з�Ƭ */
        *ppucDhcpMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        PGP_MemZero(g_pucDhcpPktBuf, sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN);
        ulRet = PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf,
                                            0,
                                            ulMsgLen,
                                            g_pucDhcpPktBuf);
        if (VOS_OK != ulRet)
        {
            DHCPC_DebugPrint(PTM_LOG_WARNING,
                "call PMBUF_CopyDataFromPMBufToBuffer fail. ulRet=%u", ulRet);
            return VOS_ERR;
        }

        *ppucDhcpMsg = g_pucDhcpPktBuf;
    }

    *pulMsgLen = ulMsgLen;
    return VOS_OK;
}


ULONG DHCPV6C_ProcDhcpMsg(UCHAR *pucDhcpv6Msg, UCHAR ucMsgType, ULONG ulMsgLen , ULONG *pulSrvIpAddr)
{
    ULONG ulReturn = VOS_ERR;
    DHCPV6C_MSG_INFO_S stMsgInfo = {0};
    DHCPC_CTRLBLK *pstDhcpcContext = NULL;
    DHCPV6C_PRE_RESULT_S stPreResult = {0};

    DHCPC_FUNC_ENTRY();

    stMsgInfo.pucMsg = pucDhcpv6Msg;
    stMsgInfo.ulMsgLen = ulMsgLen;

    /* ������Ϣ��ȡteidc,SequnceNum */
    DHCPV6C_GetSeqNumByMsg(&(stMsgInfo.usSeqNum), stMsgInfo.pucMsg);

    /* ����dhcp���ƿ� */
    ulReturn = DHCPV6C_QueryDhcpBlockBySeq(stMsgInfo.usSeqNum, &pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
        {
            DHCPC_OmVIfMsgTrc((ULONG)(ucMsgType),
                                TRC_DIRECTION_DHCPV6_IN_GGSN,
                                pucDhcpv6Msg,
                                (USHORT)ulMsgLen,
                                LAP_IPV6,
                                pulSrvIpAddr);
        }
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "Dhcpcontext not exist!");
        return ulReturn;
    }

    /* ��Ϣ���� */
    DHCPCv6_OmMsgTrc(pucDhcpv6Msg, pstDhcpcContext, ucMsgType, ulMsgLen, DHCPV6_MSG_DIRECTION_RECEIVE);

    ulReturn = DHCPV6C_MsgDecode(&stMsgInfo);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6C_MsgDecode fail!");
        return ulReturn;
    }

    DHCPC_UpdateServerGroupStatusNormal(pstDhcpcContext->usServerGrpIndex, pstDhcpcContext->ucCurrentServer);

    /* ����ԭ��ֵΪȱʡ */
    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;

    stPreResult.pstDhcpcContext = pstDhcpcContext;
    stPreResult.pMsg = &(stMsgInfo.stDhcpv6cOptionInfo);
    stPreResult.ucDhcpServerMsg = ucMsgType;

    ulReturn = DHCPV6C_CheckOption(&(stMsgInfo.stDhcpv6cOptionInfo), pstDhcpcContext);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n call DHCPV6C_CheckOption fail!");
        if (DHCPC_RET_DROP_MSG == ulReturn)
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n [dhcpv6c err:]drop msg!");
            return ulReturn;
        }
        pstDhcpcContext->ucCause = DHCPV6C_CAUSE_SERVER_MSG_EXCEPTION;
        stPreResult.enEvent = DHCPV6C_EV_DHPCS_MSG_CHECK_ERR;
    }
    else
    {
        ulReturn = DHCPV6C_FSM_PreProc_ServerMsg(&(stPreResult));
        if (DHCPC_RET_DROP_MSG == ulReturn)
        {
            DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n [dhcpv6c err:]drop msg!");
            return ulReturn;
        }
    }

    /* ��Ϊ�յ�����Ե���Ϣ,���ÿ��ƿ��ۼƷ��͵�����Ϣ����0 */
    pstDhcpcContext->ucCurSvrSendCount = 0;
    pstDhcpcContext->ucTotalSendCount = 0;

    DHCPV6C_RunFsm(&stPreResult);
    return VOS_OK;
}
ULONG DHCPV6C_CheckServerMsgType(UCHAR ucMsgType)
{
    ULONG ulRet = VOS_OK;

    /* ��Ϣ���� */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_ADVERTISE :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_ADVERTISE_MSG);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_REPLY_MSG);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_SERVER_OTHER_MSG);
            ulRet = VOS_ERR;
            break;
    }

    return ulRet;
}
VOID DHCPV6C_ProcMbufMsg(PMBUF_S *pstMsgBuf)
{
    UCHAR   ucMsgType = 0;
    ULONG   ulReturn = VOS_ERR;
    UCHAR   ucLogicSlot = 0;
    UCHAR   *pucDhcpv6Msg = NULL;
    ULONG   ulMsgLen = 0;
    ULONG   aulSrvIp[4] = {0};
    UDPS_PACKET_INFO_S stPtkInf = {0};

    DHCPC_FUNC_ENTRY();

    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    if (E_CRM_ACTIVE != CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "not active board!");
        return;
    }

    ulReturn = DHCPC_UnpackDhcpMsgFromMbuf(pstMsgBuf, &stPtkInf, &pucDhcpv6Msg, &ulMsgLen);
    if (VOS_OK != ulReturn)
    {
        DHCPV6C_DBGCNT_ADD(E_DHCPV6C_UNPACKET_FAIL);
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "call DHCPC_UnpackDhcpMsgFromMbuf fail!");
        return;
    }

    /* ͳ����V6-SERVER��Ϣ���� ֻ����advertise��reply��Ϣ */
    DHCPV6C_DBGCNT_ADD(E_DHCPV6C_REV_SERVER_MSG);
    ucMsgType = DHCPV6C_GET_MSG_TYPE(pucDhcpv6Msg);
    ulReturn = DHCPV6C_CheckServerMsgType(ucMsgType);
    if (VOS_OK != ulReturn)
    {
        return;
    }

    VOS_MemCpy(&(stPtkInf.uaddrSrc.stAddr6Src.stSin6_addr), aulSrvIp, 4*sizeof(ULONG));
    ulReturn = DHCPV6C_ProcDhcpMsg(pucDhcpv6Msg, ucMsgType, ulMsgLen, aulSrvIp);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n call DHCPV6C_ProcDhcpMsg fail!");
    }
    return;
}
VOID DHCPV6C_ProcSDMsg(UCHAR *pucMsg)
{
    PMBUF_S *pstMsgBuf = NULL;

    pstMsgBuf = *((PMBUF_S **)pucMsg);
    if ( NULL == pstMsgBuf )
    {
        VOS_Assert(0);
        return;
    }

    DHCPV6C_ProcMbufMsg(pstMsgBuf);

    (VOS_VOID)PMBUF_Destroy(pstMsgBuf);
    *((PMBUF_S **)pucMsg) = NULL;

    return;
}


VOID DHCPC_CalcSuccSendLapNum(UCHAR ucMsgType)
{
    /* ��Ϣ���� */
    switch (ucMsgType)
    {
        case DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SUCCESS_OK);
            break;

        case DHCPC_SND2_LAP2_ADDR_FAILED_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_FAIL_OK);
            break;

        case DHCPC_SND2_LAP2_ADDR_REL_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_REL_OK);
            break;

        case DHCPC_SND2_LAP2_NO_RSP_MSG:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SVR_NO_RSP_OK);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_OTHER_OK);
            break;
    }

    return;
}
VOID DHCPC_CalcFailSendLapNum(UCHAR ucMsgType)
{
    /* ��Ϣ���� */
    switch (ucMsgType)
    {
        case DHCPC_SND2_LAP2_ADDR_SUCCESS_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SUCCESS_ERR);
            break;

        case DHCPC_SND2_LAP2_ADDR_FAILED_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_FAIL_ERR);
            break;

        case DHCPC_SND2_LAP2_ADDR_REL_MSG :
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_REL_ERR);
            break;

        case DHCPC_SND2_LAP2_NO_RSP_MSG:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_SVR_NO_RSP_ERR);
            break;

        default:
            DHCPV6C_DBGCNT_ADD(E_DHCPV6C_SEND_LAP_OTHER_ERR);
            break;
    }

    return;
}
ULONG DHCPC_SendMsgToLAP2ByContext(DHCPC_CTRLBLK *pstDhcpcContext, UCHAR MsgType)
{
    ULONG ulReturn = VOS_ERR;
    LAP2_DHCPC_MSG_S stLapDhcpcMsg = {0};

    DHCPC_FUNC_ENTRY();

    /* �����Ϣ���� */
    stLapDhcpcMsg.usVpnId = pstDhcpcContext->usVPNIndex;
    VOS_MemCpy(stLapDhcpcMsg.aulPdpAddr, pstDhcpcContext->aulUserIpAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    stLapDhcpcMsg.ucAddressType = pstDhcpcContext->ucIpType;
    stLapDhcpcMsg.usPoolIndex = pstDhcpcContext->usPoolIndex;
    stLapDhcpcMsg.ucSCID = PSM_Inf_GetCmpSameTIndexInSGByCSI(DHCPC_SELF_CSI);
    VOS_MemCpy(stLapDhcpcMsg.aulAgentIP, pstDhcpcContext->aulAgentIpAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    stLapDhcpcMsg.ulIndex = pstDhcpcContext->ulPDPIndex;
    stLapDhcpcMsg.usDhcpGroupIndex = pstDhcpcContext->usServerGrpIndex;
    stLapDhcpcMsg.ucMsgType = MsgType;
    stLapDhcpcMsg.usApnIndex = pstDhcpcContext->usApnIndex;
    VOS_MemCpy(stLapDhcpcMsg.aulPrimaryDNS, pstDhcpcContext->aulMainDnsAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    VOS_MemCpy(stLapDhcpcMsg.aulSecondaryDNS, pstDhcpcContext->aulSecdDnsAddr, sizeof(ULONG) * LAP_IP_ULONG_NUM);
    stLapDhcpcMsg.ucUserType = pstDhcpcContext->ucUserType;
    stLapDhcpcMsg.ucGtpVer = pstDhcpcContext->ucUser;
    stLapDhcpcMsg.ulTeidc = pstDhcpcContext->ulTEIDC;
    stLapDhcpcMsg.ucStaticIpRouteType = 0;
    stLapDhcpcMsg.aulMSISDN[0] = pstDhcpcContext->aulMSISDN[0];
    stLapDhcpcMsg.aulMSISDN[1] = pstDhcpcContext->aulMSISDN[1];
    stLapDhcpcMsg.ucLAPNo = pstDhcpcContext->ucLAPNo;

    DHCPC_PRINT_LAP_MSG(&stLapDhcpcMsg);

    ulReturn = DHCPC_SendAddrMsgToLAP(&stLapDhcpcMsg,
                                           sizeof(LAP2_DHCPC_MSG_S),
                                           pstDhcpcContext->aulUserIpAddr[2],    // TODO:��ʱ����
                                           pstDhcpcContext->ucLAPNo);
    /* ͳ�Ʒ���Ϣ���� */
    if (VOS_OK == ulReturn)
    {
        DHCPC_CalcSuccSendLapNum(MsgType);
    }
    else
    {
        DHCPC_CalcFailSendLapNum(MsgType);
    }
    return ulReturn;
}


VOID DHCPC_EmsReportAndCleanCause(DHCPC_CTRLBLK *pstDhcpcContext)
{
    UCHAR ucCause = 0;
    DHCPC_EMS_INFO_S *pstEmsInfo = NULL;
    SDB_GSPU_CONTEXT_S * pstContext = NULL;

    if (NULL == pstDhcpcContext)
    {
        VOS_Assert(0);
        return;
    }
    ucCause = pstDhcpcContext->ucCause;

    if ((ucCause > DHCPV6C_CAUSE_DEFAULT) && (ucCause < DHCPV6C_CAUSE_BUFF))
    {
        pstContext = DHCPC_GetOneContextByteidc(pstDhcpcContext->ulTEIDC);
        if (NULL == pstContext)
        {
            return;
        }

        pstEmsInfo = &g_stDhcpcEmsInfo[ucCause];

        EMS_DebugTrace(pstContext->ulGspuBdIndex, EMS_MODULE_TYPE_AM_DHCP,
                        pstEmsInfo->usMsgCode,pstEmsInfo->aucReason, pstEmsInfo->aucsuggestion);
    }

    pstDhcpcContext->ucCause = DHCPV6C_CAUSE_DEFAULT;
    return;
}


ULONG DHCPC_NotifyLapFail(DHCPC_CTRLBLK *pstDhcpcContext)
{
    UCHAR ucMsgType = 0;
    ULONG ulReturn = 0;

    DHCPC_FUNC_ENTRY();

    if (NULL == pstDhcpcContext)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n Cause=%u", pstDhcpcContext->ucCause);

    if (DHCPV6C_CAUSE_SERVER_NOT_RSP == pstDhcpcContext->ucCause)
    {
        ucMsgType = DHCPC_SND2_LAP2_NO_RSP_MSG;
    }
    else
    {
        ucMsgType = DHCPC_SND2_LAP2_ADDR_FAILED_MSG;
    }

    DHCPC_EmsReportAndCleanCause(pstDhcpcContext);

    ulReturn = DHCPC_SendMsgToLAP2ByContext(pstDhcpcContext, ucMsgType);

    DHCPC_FUNC_EXIT(ulReturn);
    return ulReturn;
}


ULONG DHCPCv6_Get_MsgDirection(UCHAR MsgDirection,UCHAR ucUgwRole)
{
    ULONG ulDirection = TRC_DIRECTION_LEFT_IN_SGW;

    if ( DHCPV6_MSG_DIRECTION_RECEIVE ==  MsgDirection )
    {
        if ( E_NET_ELEMENT_ROLE_PGW == ucUgwRole )
        {
            ulDirection = TRC_DIRECTION_DHCPV6_IN_PGW;
        }
        else if(E_NET_ELEMENT_ROLE_GGSN == ucUgwRole)
        {
            ulDirection = TRC_DIRECTION_DHCPV6_IN_GGSN;
        }
        else
        {
            ulDirection = TRC_DIRECTION_DHCPV6_IN_SGW;
        }
    }
    else
    {
        if ( E_NET_ELEMENT_ROLE_PGW == ucUgwRole )
        {
            ulDirection = TRC_DIRECTION_DHCPV6_OUT_PGW;
        }
        else if(E_NET_ELEMENT_ROLE_GGSN == ucUgwRole)
        {
            ulDirection = TRC_DIRECTION_DHCPV6_OUT_GGSN;
        }
        else
        {
            ulDirection = TRC_DIRECTION_DHCPV6_OUT_SGW;
        }
    }

    return ulDirection;

}

