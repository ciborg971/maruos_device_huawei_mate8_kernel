#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc_dbg.h"
#include "dhcpc_cdb.h"

extern SDB_GSPU_CONTEXT_S * DHCPC_GetOneContextByteidc(ULONG ulTeidc);
extern ULONG DHCPCv6_Get_MsgDirection(UCHAR MsgDirection,UCHAR ucUgwRole);

ULONG DHCPC_GetVifName(UCHAR aucVIfName[DHCPC_V_INTERFACE_NAME_MAX_LEN+1])
{
    ULONG ulRet = VOS_ERR;
    ULONG ulGroupId = 0;
    ULONG ulInstanceId = 0;
    CRM_SPU_BOARD_TYPE_ENUM enumSpuType = CRM_BOARD_TYPE_MAX;

    /* ��ȡ���,������ƴV�ӿ����� */
    ulGroupId = CRM_GetSelfGroupId();
    if (0 == ulGroupId)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    ulRet = CRM_GetSelfGroupBoardType(&enumSpuType);
    if (CRM_OK != ulRet)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /* ��ȡinstance��,������ƴV�ӿ����� */
    if (CRM_BOARD_TYPE_SPUD == enumSpuType)
    {
        ulInstanceId = INST_GetSelfInstanceId() >> DHCPC_GROUP_BITSIZE;
    }
    else
    {
        ulInstanceId = 0;
    }

    /* ��ƴvif������ */
    VOS_sprintf((CHAR *)aucVIfName, "vif%u/%u/%d", ulGroupId, ulInstanceId, 0);

    return VOS_OK;
}
VOID DHCPC_OmVIfMsgTrc(ULONG  ulDhcpMsgType,
                                ULONG ulDirection,
                                UCHAR  *pMsg,
                                USHORT usMsgLen,
                                UCHAR  ucIpType,
                                ULONG  *pulPeerIp)
{
    ULONG ulTrcMsgType = 0;
    ULONG ulMillSecs = 0;
    ULONG ulMsgType = 0;
    ULONG ulPeerIpTypeOp = 0;
    DHCPC_IFTRC_V_FILTER stVTrcFiler = {0};
    S_FAM_BAM_TRC_TIME_DATA stTrcTime = {0};

    /* ��ȡV�ӿ����� */
    if (VOS_OK != DHCPC_GetVifName(stVTrcFiler.aucIfName))
    {
        return ;
    }

    if (LAP_IPV4 == ucIpType)
    {
        stVTrcFiler.ulPeerIp = *pulPeerIp;
        ulMsgType = V_MSGTYPE_DHCPV4;
        ulPeerIpTypeOp = V_ADDRTYPE_DHCPV4;
    }
    else
    {
        /* ipv6ʹ���ַ�������ʽ���и��٣���Ҫ����������ӡ */
        VOS_sprintf(stVTrcFiler.aulPeerIPv6, "%x%x%x%x", VOS_NTOHL(pulPeerIp[0]), VOS_NTOHL(pulPeerIp[1]), VOS_NTOHL(pulPeerIp[2]), VOS_NTOHL(pulPeerIp[3]));
        ulMsgType = V_MSGTYPE_DHCPV6;
        ulPeerIpTypeOp = V_ADDRTYPE_DHCPV6;
    }

    stVTrcFiler.ulMsgType = ulMsgType;   /* ���������� */
    stVTrcFiler.ulPeerIpTypeOp = ulPeerIpTypeOp;     
    ulTrcMsgType = ulDhcpMsgType + ulDirection + (ulMsgType << 24); /* ��ƴ������Ϣ���� */

    if (VOS_OK != VOS_TmGet(&(stTrcTime.stDate), &(stTrcTime.stTime), &ulMillSecs))
    {
        DHCPC_DebugPrint(PTM_LOG_DEBUG, 
                        "\r\nDHCPC_OmVIfMsgTrc: VOS_TmGet failed.");
    }
    stTrcTime.ulTick = (ULONG)PGP_getTimeByTicksInMisc();
    FamTrcSendTrcMsgWithTime(TRC_TYPE_V,
                  (VOS_UINT8 *)&stVTrcFiler,
                   ulTrcMsgType,
                   usMsgLen,
                   pMsg,
                   stTrcTime);

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_OmEmsTrcMsgTrc
 ��������  : ȫ������
 �������  : UCHAR ucMsgType                 
             ULONG ulDirection               
             UCHAR *pucMsg                   
             ULONG ulMsgLen                  
             SDB_GSPU_CONTEXT_S *pstContext  
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  : 
 ��������  : 
 
 �޸���ʷ      :
  1.��    ��   : 2012��9��11��
    ��    ��   : 
    �޸�����   : �����ɺ���

*****************************************************************************/
VOID DHCPC_OmEmsTrcMsgTrc(UCHAR ucMsgType, ULONG ulDirection, UCHAR *pucMsg,
                                    ULONG ulMsgLen, SDB_GSPU_CONTEXT_S *pstContext)
{
    RM_SOCKET_PATH_S stPath = {0};
    S_OM_EMS_TRC_PARA stTrcPara = {0};

    if (NULL == pstContext)
    {
        VOS_Assert(0);
        return;
    }

    if ((E_NET_ELEMENT_ROLE_PGW == pstContext->ucUgwRole)||(E_NET_ELEMENT_ROLE_GGSN == pstContext->ucUgwRole))
    {
        stPath.ulLocalAddr = pstContext->ulS5_Gn_LocDataIP;
        stPath.ulPeerAddr  = pstContext->ulS5_Gn_PeerDataIP; 
    }
    else
    {
        stPath.ulLocalAddr = pstContext->ulSgwLeftLocDataIP;
        stPath.ulPeerAddr  = pstContext->ulSgwLeftPeerDataIP;
    }  

    /*ȫ������*/
    stTrcPara.pucTrcMsg = (UCHAR *)pucMsg;
    stTrcPara.ucMsgType = ucMsgType;
    stTrcPara.ucUgwRole = pstContext->ucUgwRole;
    stTrcPara.usMsgLen = (USHORT)ulMsgLen;
    stTrcPara.ulEmsTrcDir = M_EMS_TRC_RECV_MSG;
    stTrcPara.ulUsrTrcDir = ulDirection;
    stTrcPara.usTraceId = pstContext->usTraceId;
    stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
    stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
    stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
    stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
    stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV6;
    stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
    stTrcPara.ucMsgSndFlg = 0;
    
    if((1 == stTrcPara.ucSgwTrcFlg)
        || (1 == stTrcPara.ucPgwTrcFlg))
    {
        UGW_OmEmsTrcMsgTrc(&stTrcPara, &stPath);
    }

    return;
}
VOID DHCPCv6_OmMsgTrc(UCHAR *pucDhcpv6Msg,DHCPC_CTRLBLK *pstDhcpcContext, UCHAR ucMsgType,ULONG ulMsgLen, UCHAR MsgDirection)
{
    ULONG ulDirection = TRC_DIRECTION_LEFT_IN_PGW;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;

    if( NULL == pucDhcpv6Msg ||NULL == pstDhcpcContext)
    {
        return;
    }

    ulDirection = DHCPCv6_Get_MsgDirection(MsgDirection, (UCHAR)(pstDhcpcContext->ucRole)); 

    /*����Teidc, ��ȡ1��������*/
    pstContext = DHCPC_GetOneContextByteidc(pstDhcpcContext->ulTEIDC);
    if (NULL != pstContext)
    {
        /* ȫ������ */
        DHCPC_OmEmsTrcMsgTrc(ucMsgType, ulDirection, pucDhcpv6Msg, ulMsgLen, pstContext);
    }

    UGW_OmUsrMsgTrace(pucDhcpv6Msg,
        GUSER_MSGTYPE_DHCPV6,
        (ULONG)ucMsgType + ulDirection,
        (USHORT)ulMsgLen,
        (UCHAR *)(pstDhcpcContext->aulIMSI),
        (UCHAR *)(pstDhcpcContext->aulIMEI),
        (UCHAR *)(pstDhcpcContext->aulMSISDN),
        pstDhcpcContext->ucRandomNo);

    /* V�ӿڸ��� */
    if (VOS_TRUE == TrcGetTraceFlag(TRC_TYPE_V))
    {
        DHCPC_OmVIfMsgTrc(ucMsgType, ulDirection, pucDhcpv6Msg, (USHORT)ulMsgLen, LAP_IPV6, pstDhcpcContext->aulSrvIp);
    }

    return;
}

