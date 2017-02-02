

/********************************************************************************/
/******************                  ͷ�ļ�����               *******************/
/********************************************************************************/
#include "dhcp_inc.h"

/* add by w00316385 start */
#include "dhcpc_def.h"
/* add by w00316385 end */

/* deleted by w00316385 start */
#if 0
#include "ipv6_api.h"
#include "ipv6.h"
#endif
/* deleted by w00316385 end */

#include "dhcpv6_def.h"
#include "dhcpv6_proc.h"
#include "dhcpv6s_comp.h"
#include "dhcpv6s_dbg.h"
/* deleted by w00316385 start */
#if 0
#include "gtp.h"
#endif
/* deleted by w00316385 end */

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6_PROC_C
/*lint +e767*/



/********************************************************************************/
/******************                  �궨��                 *******************/
/********************************************************************************/


/********************************************************************************/
/******************                  ȫ�ֱ���                 *******************/
/********************************************************************************/
extern ULONG g_ulGreProType;
extern in6_addr in6addr_ggsn;
DHCPV6_STAT_S  g_stDhcpv6Statistics = {0};         /*  IPv6����ͳ�� */

UCHAR* g_pucDhcpv6sSendBuff = VOS_NULL;        /*������Ϣ����*/
UCHAR* g_pucDhcpv6sRevBuff = VOS_NULL;        /*������Ϣ����*/


/********************************************************************************/
/******************                  �ڲ��ӿ�                 *******************/
/********************************************************************************/
#define __MSG_TRC__

VOID DHCPV6_MsgInterfaceTrc(UCHAR *pucMsg, USHORT usMsgLen, ULONG ulMsgType,
                                       ULONG ulDirection, RM_SOCKET_PATH_S *pstPath)
{
    ULONG ulMsgClass = 0;
    E_TRACE_TYPE enTraceType = TRC_TYPE_BUTT;
    E_TRACE_TYPE enExtTraceType = TRC_TYPE_BUTT;
    UGW_EXTERN_INTF_TRACE_S stTraceInfo = {0};

    if((NULL == pucMsg) || (NULL == pstPath))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_TRC_NULL);
        return;
    }

    /* ȷ���������� */
    DHCPV6S_GET_TRCTYPE_BY_DIR(ulDirection, enTraceType, enExtTraceType, ulMsgClass);
    if ((TRC_TYPE_BUTT == enTraceType) && (TRC_TYPE_BUTT == enExtTraceType))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_TRC_TYPE_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulDirection = %u", ulDirection);
        return;
    }

    /* �ڲ����� */
    UGW_OmAccessMsgTrc(pucMsg,
                        enTraceType,
                        ulMsgClass,
                        (ulMsgType + ulDirection),
                        pstPath->ulPeerAddr,
                        usMsgLen);

    /* �ⲿ���� */
    stTraceInfo.ulMsgClass      = ulMsgClass;
    stTraceInfo.ulGtpMsgType    = ulMsgType + ulDirection;
    stTraceInfo.ulLocalIpAddr   = pstPath->ulLocalAddr;
    stTraceInfo.ulVpnIndex      = pstPath->ulVrfIndex;
    stTraceInfo.ulPeerIpAddr    = pstPath->ulPeerAddr;
    stTraceInfo.usApnIndex      = pstPath->usApnIndex;
    stTraceInfo.ucAliaApnFlag   = pstPath->ucAliaApnFlag;
    stTraceInfo.ulMsgLen        = (ULONG)usMsgLen;
    GTPC_OmExternInterfaceTrcProcess(pucMsg, enExtTraceType, stTraceInfo);

    return;
}
VOID DHCPV6_MsgTraceProc(DHCPV6_MSG_S *pDhcpv6Msg,
                                     ULONG ulMsgLen,
                                     SDB_GSPU_CONTEXT_S *pstContext,
                                     UDPHDR_S *pstUdp,
                                     ULONG ulEmsTrcDir)
{
    RM_SOCKET_PATH_S stPath = {0};
    S_OM_EMS_TRC_PARA stTrcPara = {0};
    UCHAR ucMsgType = pDhcpv6Msg->ucMsgType;
    ULONG ulDirection = TRC_DIRECTION_LEFT_IN_PGW;

    /* ȷ����Ϣ���ٵķ��� */
    DHCPV6S_GET_TRCDIR_BY_ROLE(pstContext->ucUgwRole, ulEmsTrcDir, ulDirection);

    /* ȷ��ԴĿ�ĵ�ַ,�˿ں� */
    stPath.ulLocalAddr = pstContext->ulS5_Gn_LocDataIP;
    stPath.ulPeerAddr  = pstContext->ulS5_Gn_PeerDataIP;
    if ((E_NET_ELEMENT_ROLE_PGW != pstContext->ucUgwRole)
        && (E_NET_ELEMENT_ROLE_GGSN != pstContext->ucUgwRole))
    {
        stPath.ulLocalAddr = pstContext->ulSgwLeftLocDataIP;
        stPath.ulPeerAddr  = pstContext->ulSgwLeftPeerDataIP;
    }
    /* ��ȡVPN-id */
    Path_GetVpn(pstContext, &(stPath.ulVrfIndex));

    stPath.usLocalPort = VOS_NTOHS(pstUdp->uh_usSPort);
    stPath.usPeerPort  = VOS_NTOHS(pstUdp->uh_usDPort);

    AM_CtxApiGetReqApnIndexByPdpContext(pstContext, &(stPath.usApnIndex), &(stPath.ucAliaApnFlag));

    if (M_EMS_TRC_RECV_MSG == ulEmsTrcDir)
    {
        stPath.usLocalPort = VOS_NTOHS(pstUdp->uh_usDPort);
        stPath.usPeerPort  = VOS_NTOHS(pstUdp->uh_usSPort);
    }

    /* �ӿڸ��� */
    DHCPV6_MsgInterfaceTrc((UCHAR*)pDhcpv6Msg, (USHORT)ulMsgLen, (ULONG)ucMsgType, ulDirection, &stPath);

    UGW_OmUsrMsgTrace((UCHAR *)pDhcpv6Msg,
                        GUSER_MSGTYPE_DHCPV6,
                        (ULONG)ucMsgType + ulDirection,
                        (USHORT)(ulMsgLen),
                        (UCHAR *)&(pstContext->stImsi),
                        (UCHAR *)&(pstContext->stIMEI),
                        pstContext->szMsisdn,
                        pstContext->ucRandomNo);

    /* ȫ������ */
    stTrcPara.pucTrcMsg = (UCHAR *)pDhcpv6Msg;
    stTrcPara.ucMsgType = ucMsgType;
    stTrcPara.ucUgwRole = pstContext->ucUgwRole;
    stTrcPara.usMsgLen = (USHORT)ulMsgLen;
    stTrcPara.ulEmsTrcDir = ulEmsTrcDir;
    stTrcPara.ulUsrTrcDir = ulDirection;
    stTrcPara.usTraceId = pstContext->usTraceId;
    stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
    stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
    stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
    stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
    stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV6;
    stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
    stTrcPara.ucMsgSndFlg = 0;
    if((1 == stTrcPara.ucSgwTrcFlg) || (1 == stTrcPara.ucPgwTrcFlg))
    {
        UGW_OmEmsTrcMsgTrc(&stTrcPara, &stPath);
    }

    return;
}
VOID DHCPV6_MsgTraceProcForRelay(UCHAR *pucDateMsg,
                                                 ULONG ulMsgLen,
                                                 UCHAR ucMsgType,
                                                 SDB_GSPU_CONTEXT_S *pstContext,
                                                 ULONG ulEmsTrcDir)
{
    /*�˴�ֻ���Ǻ�һ������PGW�ϵ���Ϣ���ٺͽӿڸ���*/
    UDPHDR_S *pstUdp = NULL;
    RM_SOCKET_PATH_S stPath = {0};
    DHCPV6_MSG_S *pDhcpv6Msg = NULL;
    S_OM_EMS_TRC_PARA stTrcPara = {0};
    ULONG ulDirection = TRC_DIRECTION_LEFT_IN_PGW;

    pstUdp = (UDPHDR_S*)(pucDateMsg  + IPV6_HEADER_LEN);
    pDhcpv6Msg = (DHCPV6_MSG_S*)(pucDateMsg + IPV6_HEADER_LEN + UDP_HEADER_LENGTH);

    /* ������Ϣ����ȷ����Ϣ���ٵĲ��� */
    if (M_EMS_TRC_RECV_MSG == ulEmsTrcDir)
    {
        DHCPV6S_GET_TRCPARA_FOR_RELAY_REV(ucMsgType, ulDirection, stPath, pstUdp, pstContext);
    }
    else
    {
        DHCPV6S_GET_TRCPARA_FOR_RELAY_SEND(ucMsgType, ulDirection, stPath, pstContext);
    }

    AM_CtxApiGetReqApnIndexByPdpContext(pstContext, &(stPath.usApnIndex), &(stPath.ucAliaApnFlag));

    /* �ӿڸ��� */
    DHCPV6_MsgInterfaceTrc((UCHAR*)pDhcpv6Msg, (USHORT)ulMsgLen, (ULONG)ucMsgType, ulDirection, &stPath);

    UGW_OmUsrMsgTrace((UCHAR *)pDhcpv6Msg,
                 GUSER_MSGTYPE_DHCPV6,
                 (ULONG)ucMsgType + ulDirection,
                 (USHORT)(ulMsgLen),
                 (UCHAR *)&(pstContext->stImsi),
                 (UCHAR *)&(pstContext->stIMEI),
                 pstContext->szMsisdn,
                 pstContext->ucRandomNo);

    /* ȫ������ */
    stTrcPara.pucTrcMsg = (UCHAR *)pDhcpv6Msg;
    stTrcPara.ucMsgType = ucMsgType;
    stTrcPara.ucUgwRole = pstContext->ucUgwRole;
    stTrcPara.usMsgLen = (USHORT)ulMsgLen;
    stTrcPara.ulEmsTrcDir = ulEmsTrcDir;
    /* ͸��info-request��Ϣʱ,���ǽ������� */
    if (DHCPV6_MSG_TYPE_INFORMATION_REQUEST == ucMsgType)
    {
        stTrcPara.ulEmsTrcDir = M_EMS_TRC_RECV_MSG;
    }
    stTrcPara.ulUsrTrcDir = ulDirection;
    stTrcPara.usTraceId = pstContext->usTraceId;
    stTrcPara.ucSgwTrcFlg = pstContext->ucSgwIsTraceFlag;
    stTrcPara.ucPgwTrcFlg = pstContext->ucPgwIsTraceFlag;
    stTrcPara.ucSgwTrcIf = pstContext->ucSgwListOfInterfaces;
    stTrcPara.ucPgwTrcIf = pstContext->ucPgwListOfInterfaces;
    stTrcPara.ucProType = GTPC_GUSER_MSGTYPE_DHCPV6;
    stTrcPara.ucMsgIntf = VOS_NULL_BYTE;
    stTrcPara.ucMsgSndFlg = 0;
    if((1 == stTrcPara.ucSgwTrcFlg) || (1 == stTrcPara.ucPgwTrcFlg))
    {
        UGW_OmEmsTrcMsgTrc(&stTrcPara, &stPath);
    }

    return;
}

#define __MSG_CHECK__
ULONG DHCPV6_CheckForReqDns(DHCPV6S_OPTION_INFO_S *pstOptionInfo)
{
    ULONG ulOROFlag = pstOptionInfo->ulOROFlag;
    ULONG ulOptionFlag = pstOptionInfo->ulOptionFlag;

    /* û������DNS */
    if(0 == (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_ORO)) &&
       0 == (ulOROFlag & (1 << DHCPV6_MSG_OPTION_DNS_SERVERS)))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_DNS);
        return VOS_ERR;
    }

    return VOS_OK;
}
ULONG DHCPV6_CheckForReqIaPd(DHCPV6S_OPTION_INFO_S *pstOptionInfo)
{
    ULONG ulOptionFlag = pstOptionInfo->ulOptionFlag;
    ULONG ulPdExcludeFlg = pstOptionInfo->ulPdExcludeFlg;

    /* û������IA_PD,������Ϣ */
    if(0 == (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_IAPD)))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_IAPD);
        return VOS_ERR;
    }

    /* û������PD_EXCLUDE,��������pd_exclude */
    if((0 == (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_ORO))) ||
       (VOS_FALSE == ulPdExcludeFlg))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_PDEXCLUDE);
    }

    return VOS_OK;
}


ULONG DHCPV6_CheckIpUdp(UCHAR *pucSrcMsg, ULONG ulMsgLen)
{
    ULONG ulFwdHdrLen = 0;
    //USHORT usCheckSumOri = 0;
    //USHORT usCheckSumFresh = 0;
    IPV6HDR_S *pIpv6Hdr = NULL;
    UDPHDR_S  *pUdpv6Hdr = NULL;
    //UCHAR *pucMsgCheckSum = NULL;

    if(NULL == pucSrcMsg)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NULL_MSG);
        return  VOS_ERR;
    }

    /* ת�����͵ı��İ���UDPͷ��IPͷ����������һ��ת��ͷ */
    pIpv6Hdr = (IPV6HDR_S*)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR));
    ulFwdHdrLen = sizeof(FWD_TO_CTRL_HDR);

    /* ���Դ��ַ */
    if (VOS_OK != IPV6_SrcAddrValidationCheck(pIpv6Hdr))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SRC_ADDR_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "stAddr = %08x;%08x;%08x;%08x",
        pIpv6Hdr->saddr.s6_addr32[0], pIpv6Hdr->saddr.s6_addr32[1],
        pIpv6Hdr->saddr.s6_addr32[2], pIpv6Hdr->saddr.s6_addr32[3]);
        return VOS_ERR;
    }

    if ((VOS_NTOHS(pIpv6Hdr->payload_len) + IPV6_HEADER_LEN + ulFwdHdrLen) != ulMsgLen)
    {
        g_stDhcpv6Statistics.ulLenErr++;
        return VOS_ERR;
    }

    if (pIpv6Hdr->hop_limit < 1)
    {
        g_stDhcpv6Statistics.ulHopLimitErr++;
        return VOS_ERR;
    }

    if (pIpv6Hdr->nexthdr != IPV6_UDP_PRO)
    {
        g_stDhcpv6Statistics.ulNextHeadErr++;
        return VOS_ERR;
    }

    pUdpv6Hdr = (UDPHDR_S *)((UCHAR*)pIpv6Hdr + IPV6_HEADER_LEN);
    if(DHCPV6_SERVER_UDP_PORT != VOS_NTOHS(pUdpv6Hdr->uh_usDPort))
    {
        g_stDhcpv6Statistics.ulDestPortErr++;
        return VOS_ERR;
    }


    return VOS_OK;
}


ULONG DHCPV6_CheckMsgLen(UCHAR *pucSrcMsg, ULONG ulMsgLen)
{
    ULONG ulDhcpMsgLen = 0;
    ULONG ulTotalMsgLen = 0;
    UCHAR *pucDhcpv6Msg = NULL;
    DHCPV6_OPT_S *pDhcpv6Opt = NULL;
    ULONG ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    /* ��Ϣ���ȼ�� */
    if(ulMsgLen < ulMsgHeadLen + DHCPV6_HEADER_LEN)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MSGLEN_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulMsgLen = %u", ulMsgLen);
        g_stDhcpv6Statistics.ulLenErr++;
        return VOS_ERR;
    }

    /* �����Ϣ���������ѡ��ĳ��Ⱥ��Ƿ�ƥ�� */
    ulDhcpMsgLen = ulMsgLen - ulMsgHeadLen;
    pucDhcpv6Msg = pucSrcMsg + ulMsgHeadLen;
    ulTotalMsgLen = ulMsgHeadLen + DHCPV6_HEADER_LEN;
    pDhcpv6Opt = (DHCPV6_OPT_S *) (pucDhcpv6Msg + DHCPV6_HEADER_LEN);/*ָ���һ��OPTION*/

    while((ULONG)( (UCHAR *)pDhcpv6Opt - pucDhcpv6Msg )< ulDhcpMsgLen)
    {
        ulTotalMsgLen += VOS_NTOHS(pDhcpv6Opt->usOptLen) + DHCPV6_OPT_HEADER_LEN;
        pDhcpv6Opt = (DHCPV6_OPT_S *) ((UCHAR*)pDhcpv6Opt + DHCPV6_OPT_HEADER_LEN + VOS_NTOHS(pDhcpv6Opt->usOptLen));
    }

    if(ulTotalMsgLen != ulMsgLen)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MSGLEN_ERR);
        g_stDhcpv6Statistics.ulOptionLenErr++;
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulTotalMsgLen = %u, ulMsgLen = %u", ulTotalMsgLen, ulMsgLen);
        return VOS_ERR;
    }

    return VOS_OK;
}

#define __MSG_DECODE__
ULONG DHCPV6_GetPdpIdxAndContext(FWD_TO_CTRL_HDR* pstCtrlHdr, ULONG *pulPdpIndex,
                                                SDB_GSPU_CONTEXT_S **ppstContext)
{
    ULONG ulRet = VOS_OK;
    ULONG ulPdpIndex = 0;
    ULONG ulTempIndex = 0;

    if (NULL == ppstContext)
    {
        return VOS_ERR;
    }

    ulTempIndex = (ULONG)fwd_get_ctrlhdr_pdpindex(pstCtrlHdr);
    ulPdpIndex = ulTempIndex - SDB_MAX_CONTEXT_NUM * DHCPV6S_SELF_CMPIDX_INSG;

    /* PDP INDEX��� */
    if ((ulPdpIndex > SDB_MAX_CONTEXT_NUM) || (0 == ulPdpIndex))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_PDP_INDEX_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ulPdpIndex = %u", ulPdpIndex);
        return VOS_ERR;
    }

    /*����PDP INDEX, ��ȡ������*/
    ulRet = (ULONG)SDB_GetContextByIndex(ulPdpIndex, (UCHAR**)ppstContext);
    if ((ulRet != VOS_OK) || (NULL == *ppstContext))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GET_CONTXT_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "no-context");
        return VOS_ERR;
    }

    *pulPdpIndex = ulPdpIndex;

    return VOS_OK;
}


VOID DHCPV6_OrOptionDecode(DHCPV6S_OPTION_INFO_S *pstOptionInfo,
                                       DHCPV6_OPT_S *pDhcpv6Opt)
{
    ULONG ulOROFlag = 0;
    USHORT usOROptLen = 0;
    USHORT *pusOptType = (USHORT *)pDhcpv6Opt->opt;

    usOROptLen = VOS_NTOHS(pDhcpv6Opt->usOptLen);
    while(usOROptLen > 0)
    {
        if (DHCPV6_MSG_OPTION_PDEXCLUDE == VOS_HTONS(*pusOptType))
        {
            pstOptionInfo->ulPdExcludeFlg = VOS_TRUE;
        }

        /*lint -e504*/
        ulOROFlag |= (ULONG)1 << (VOS_HTONS(*pusOptType));
        /*lint +e504*/
        pusOptType++;
        usOROptLen -= 2;
    }
    pstOptionInfo->ulOROFlag = ulOROFlag;

    return;
}


VOID DHCPV6_MsgDecode(DHCPV6S_MSG_INFO_S *pstMsgInfo)
{
    ULONG ulOptionFlag = 0;
    DHCPV6_OPT_S *pDhcpv6Opt = NULL;
    pDhcpv6Opt = (DHCPV6_OPT_S *)(pstMsgInfo->pucMsg + DHCPV6_HEADER_LEN);/*ָ���һ��OPTION*/

    /*lint -e574*/
    while((UCHAR *)pDhcpv6Opt - pstMsgInfo->pucMsg < pstMsgInfo->ulMsgLen)
    {
        switch (VOS_NTOHS(pDhcpv6Opt->usOptType))
        {
            case DHCPV6_MSG_OPTION_ORO:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_ORO;
                if(VOS_NTOHS(pDhcpv6Opt->usOptLen) % 2 != 0)
                {
                    g_stDhcpv6Statistics.ulOptionLenOddErr++;
                    break;
                }

                /* ����Option-Request Option */
                DHCPV6_OrOptionDecode(&(pstMsgInfo->stDhcpOptionInfo), pDhcpv6Opt);
                break;

            case DHCPV6_MSG_OPTION_CLIENTID:
                pstMsgInfo->stDhcpOptionInfo.pstCiOption = pDhcpv6Opt;
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_CLIENTID;
                break;

            case DHCPV6_MSG_OPTION_SERVERID:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_SERVERID;
                break;

            case DHCPV6_MSG_OPTION_IA_NA:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IA_NA;
                break;

            case DHCPV6_MSG_OPTION_IA_TA:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IA_TA;
                break;

            case DHCPV6_MSG_OPTION_IAADDR:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IAADDR;
                break;

            case DHCPV6_MSG_OPTION_PREFERENCE:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_PREFERENCE;
                break;

            case DHCPV6_MSG_OPTION_ELAPSED_TIME:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_ELAPSED_TIME;
                break;

            case DHCPV6_MSG_OPTION_RELAY_MSG:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RELAY_MSG;
                break;

            case DHCPV6_MSG_OPTION_AUTH:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_AUTH;
                break;

            case DHCPV6_MSG_OPTION_UNICAST:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_UNICAST;
                break;

            case DHCPV6_MSG_OPTION_STATUS_CODE:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_STATUS_CODE;
                break;

            case DHCPV6_MSG_OPTION_RAPID_COMMIT:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RAPID_COMMIT;
                break;

            case DHCPV6_MSG_OPTION_USER_CLASS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_USER_CLASS;
                break;

            case DHCPV6_MSG_OPTION_VENDOR_CLASS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_VENDOR_CLASS;
                break;

            case DHCPV6_MSG_OPTION_VENDOR_OPTS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_VENDOR_OPTS;
                break;

            case DHCPV6_MSG_OPTION_INTERFACE_ID:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_INTERFACE_ID;
                break;

            case DHCPV6_MSG_OPTION_RECONF_MSG:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RECONF_MSG;
                break;

            case DHCPV6_MSG_OPTION_RECONF_ACCEPT:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_RECONF_ACCEPT;
                break;

            case DHCPV6_MSG_OPTION_DNS_SERVERS:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_DNS_SERVERS;
                break;

            case DHCPV6_MSG_OPTION_DOMAIN_LIST:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_DOMAIN_LIST;
                break;

            case DHCPV6_MSG_OPTION_IAPD:
                ulOptionFlag |= 1<<DHCPV6_MSG_OPTION_IAPD;
                break;

            default:
                g_stDhcpv6Statistics.ulUnknownOptErr++;
                break;
        }

        pDhcpv6Opt = (DHCPV6_OPT_S *) ((UCHAR*)pDhcpv6Opt + DHCPV6_OPT_HEADER_LEN + VOS_NTOHS(pDhcpv6Opt->usOptLen));
    }
    pstMsgInfo->stDhcpOptionInfo.ulOptionFlag = ulOptionFlag;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulOptionFlag = 0x%x, ulOROFlag = 0x%x, ulPdExcludeFlg = 0x%x",
                        pstMsgInfo->stDhcpOptionInfo.ulOptionFlag,
                        pstMsgInfo->stDhcpOptionInfo.ulOROFlag,
                        pstMsgInfo->stDhcpOptionInfo.ulPdExcludeFlg);
    return;
}
VOID DHCPV6_MsgUnpacket(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                    UCHAR *pucSrcMsg, ULONG ulMsgLen)
{
    ULONG ulMsgHeadLen = 0;
    UDPHDR_S *pstUdpv6Hdr = NULL;
    IPV6HDR_S *pstIpv6Hdr = NULL;

    pstIpv6Hdr = (IPV6HDR_S *)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR));
    pstUdpv6Hdr = (UDPHDR_S *)((UCHAR *)pstIpv6Hdr + IPV6_HEADER_LEN);
    ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    /* ȷ����Ϣ���Ⱥ���Ϣ���� */
    pstMsgInfo->pucMsg = pucSrcMsg + ulMsgHeadLen;
    pstMsgInfo->ulMsgLen = ulMsgLen - ulMsgHeadLen;
    pstMsgInfo->ucMsgType = ((DHCPV6_MSG_S*)pstMsgInfo->pucMsg)->ucMsgType;
    VOS_MemCpy(&(pstMsgInfo->stSrcAddr), &(pstIpv6Hdr->saddr), sizeof(in6_addr));
    VOS_MemCpy(&(pstMsgInfo->stDstAddr), &(pstIpv6Hdr->daddr), sizeof(in6_addr));
    /* ���淢����Ϣʱֱ��ʹ��,��˲������ֽ���ת�� */
    pstMsgInfo->usSrcPort = pstUdpv6Hdr->uh_usSPort;
    pstMsgInfo->usDstPort = pstUdpv6Hdr->uh_usDPort;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG,
            "srcPort = %u, srcAddr = 0x%x:%x:%x:%x, dstPort = %u, dstAddr = 0x%x:%x:%x:%x",
            VOS_NTOHS(pstMsgInfo->usSrcPort),
            pstMsgInfo->stSrcAddr.s6_addr32[0], pstMsgInfo->stSrcAddr.s6_addr32[1],
            pstMsgInfo->stSrcAddr.s6_addr32[2], pstMsgInfo->stSrcAddr.s6_addr32[3],
            VOS_NTOHS(pstMsgInfo->usDstPort),
            pstMsgInfo->stDstAddr.s6_addr32[0], pstMsgInfo->stDstAddr.s6_addr32[1],
            pstMsgInfo->stDstAddr.s6_addr32[2], pstMsgInfo->stDstAddr.s6_addr32[3]);

    return;
}

#define __MSG_ENCODE__

VOID DHCPV6_FillServerIdOption(UCHAR *pucMsgBuff,
                                         ULONG *pulOffset,
                                         SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulServerIP = 0;
    USHORT usOptionLen = 0;
    UCHAR ucUgwRole = pstContext->ucUgwRole;
    DHCPV6_OPT_S *pstServerIdOption = (DHCPV6_OPT_S *)pucMsgBuff;
    DHCPV6_DUID_EN_OPTION_S *pstDuidEn = (DHCPV6_DUID_EN_OPTION_S *)pstServerIdOption->opt;

    /* ȷ����������IP */
    if (E_NET_ELEMENT_ROLE_PGW_AND_SGW == ucUgwRole)
    {
        ulServerIP = pstContext->ulSgwLeftLocSigIP;
    }
    else
    {
        ulServerIP = pstContext->ulS5_Gn_LocSigIP;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucUgwRole = %u, ulServerIP = 0x%x",
                        ucUgwRole, ulServerIP);

    pstServerIdOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_SERVERID);
    pstDuidEn->usType = VOS_HTONS(DHCPV6_MSG_OPTION_DUID_EN);
    pstDuidEn->ulEnterpriseNum = VOS_HTONL(DHCPV6_HUAWEI_ENTERPRISENUM);
    usOptionLen += sizeof(DHCPV6_DUID_EN_OPTION_S);
    *(ULONG*)pstDuidEn->ucData = ulServerIP;
    usOptionLen += sizeof(ULONG);
    pstServerIdOption->usOptLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "usOptionLen = %u", usOptionLen);
    return;
}
VOID DHCPV6_FillDnsOption(UCHAR *pucMsgBuff,
                                     ULONG *pulOffset,
                                     SDB_GSPU_CONTEXT_S *pstContext)
{
    in6_addr stMainDnsIp;
    in6_addr stSecdDnsIp;
    USHORT usOptionLen = 0;
    DHCPV6_OPT_S *pstDnsOption = (DHCPV6_OPT_S *)pucMsgBuff;

    VOS_MemCpy(&stMainDnsIp, &(pstContext->stMainDnsIp), sizeof(in6_addr));
    VOS_MemCpy(&stSecdDnsIp, &(pstContext->stBackupDnsIp), sizeof(in6_addr));

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "stMainDnsIp = 0x%x:%x:%x:%x, stSecdDnsIp = 0x%x:%x:%x:%x",
            stMainDnsIp.s6_addr32[0], stMainDnsIp.s6_addr32[1],
            stMainDnsIp.s6_addr32[2], stMainDnsIp.s6_addr32[3],
            stSecdDnsIp.s6_addr32[0], stSecdDnsIp.s6_addr32[1],
            stSecdDnsIp.s6_addr32[2], stSecdDnsIp.s6_addr32[3]);

    if(VOS_FALSE == DHCPV6S_IPV6_ADDR_INVALID(&stMainDnsIp))
    {
        pstDnsOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_DNS_SERVERS);
//        DHCPV6_HTONL_IPV6_ADDR(stMainDnsIp);
        VOS_MemCpy(pstDnsOption->opt, &stMainDnsIp, sizeof(in6_addr));
        usOptionLen += sizeof(in6_addr);
        if(VOS_FALSE == DHCPV6S_IPV6_ADDR_INVALID(&stSecdDnsIp))
        {
//            DHCPV6_HTONL_IPV6_ADDR(stSecdDnsIp);
            VOS_MemCpy(pstDnsOption->opt + sizeof(in6_addr), &stSecdDnsIp, sizeof(in6_addr));
            usOptionLen += sizeof(in6_addr);
        }
        pstDnsOption->usOptLen = VOS_HTONS(usOptionLen);
        *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "usOptionLen = %u", usOptionLen);
    return;
}


VOID DHCPV6_FillStatusCodeOption(UCHAR *pucMsgBuff,
                                              ULONG *pulOffset,
                                              USHORT usStatusCode)
{
    DHCPV6_OPT_S *pstStatusCodeOption = (DHCPV6_OPT_S *)pucMsgBuff;

    pstStatusCodeOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_STATUS_CODE);
    *(USHORT*)pstStatusCodeOption->opt = VOS_HTONS(usStatusCode);
    pstStatusCodeOption->usOptLen = VOS_HTONS(sizeof(USHORT));

    *pulOffset += (DHCPV6_OPT_HEADER_LEN + sizeof(USHORT));
    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulOffset = %u", *pulOffset);
    return;
}


VOID DHCPV6_GetSubnetByPrefixAddr(ULONG aulPrefixAddr[],
                                                UCHAR ucPrefixLength,
                                                ULONG *pulSubnetId,
                                                UCHAR *pucByteNum)
{
    UCHAR ucMoveBitNum = 0;
    ULONG ulTempIp= 0;
	ULONG ulTmpAddr[4] = {0};

    if ((NULL == pulSubnetId) || (NULL == pucByteNum))
    {
        VOS_Assert(NULL != pulSubnetId);
        VOS_Assert(NULL != pucByteNum);
        return;
    }

	/*�������ip��ַת����������֮�������*/
	ulTmpAddr[0] = VOS_NTOHL(aulPrefixAddr[0]);
	ulTmpAddr[1] = VOS_NTOHL(aulPrefixAddr[1]);
	ulTmpAddr[2] = VOS_NTOHL(aulPrefixAddr[2]);
	ulTmpAddr[3] = VOS_NTOHL(aulPrefixAddr[3]);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "PrefixAddr = 0x%x:%x:%x:%x, PrefixLength = %u",
            ulTmpAddr[0], ulTmpAddr[1],
            ulTmpAddr[2], ulTmpAddr[3], ucPrefixLength);

    /* ����ܵ�����ŵ���ǰ�棬Ŀǰֻ������һ��if */
    if ((ucPrefixLength > 32) && (ucPrefixLength <= 64))
    {
        ucMoveBitNum = (64 - ucPrefixLength);
        ulTempIp = ulTmpAddr[1] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }
    else if ((ucPrefixLength > 0) && (ucPrefixLength <= 32))
    {
        ucMoveBitNum = (32 - ucPrefixLength);
        ulTempIp = ulTmpAddr[0] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }
    else if ((ucPrefixLength > 64) && (ucPrefixLength <= 96))
    {
        ucMoveBitNum = (96 - ucPrefixLength);
        ulTempIp = ulTmpAddr[2] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }
    else if ((ucPrefixLength > 96) && (ucPrefixLength <= 128))
    {
        ucMoveBitNum = (128 - ucPrefixLength);
        ulTempIp = ulTmpAddr[3] & (VOS_NULL_LONG >> (LAP_ULONG_BIT_NUM - ucMoveBitNum));
    }

    *pulSubnetId = ulTempIp << (LAP_ULONG_BIT_NUM - ucMoveBitNum);
    *pucByteNum = (ucMoveBitNum / 8) + (0 == (ucMoveBitNum % 8) ? 0: 1);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulSubnetId = 0x%x, ucByteNum = %u",
                        *pulSubnetId, *pucByteNum);

    return;
}


VOID DHCPV6_FillPdExcludeOption(UCHAR *pucMsgBuff,
                                            ULONG *pulOffset,
                                            in6_addr *pstIPv6Prefix,
                                            UCHAR ucIpv6PrefixLength)
{
    UCHAR ucByteNum = 0;
    ULONG ulSubnetId = 0;
    USHORT usOptionLen = 0;
    DHCPV6_PDEXCLUDE_OPTION_S *pstPdExcludeOption = (DHCPV6_PDEXCLUDE_OPTION_S *)pucMsgBuff;

    pstPdExcludeOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_PDEXCLUDE);
    pstPdExcludeOption->ucPrefixLen = DHCPV6S_PREFIX_LEN;
    usOptionLen += sizeof(UCHAR);

    /* ��ȡsubnetId */
    DHCPV6_GetSubnetByPrefixAddr((ULONG *)pstIPv6Prefix, ucIpv6PrefixLength, &ulSubnetId, &ucByteNum);
    /* ulSubnetId�����Ǵ��ֽ���,����windows��x86����,��Ҫ�����ֽ���ת��������ȷȡֵ */
    ulSubnetId = VOS_HTONL(ulSubnetId);
    VOS_MemCpy(pstPdExcludeOption->ucData, (UCHAR*)&ulSubnetId, ucByteNum);
    usOptionLen += ucByteNum;
    pstPdExcludeOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucByteNum = %u, usOptionLen = %u", ucByteNum, usOptionLen);
    return;
}


ULONG DHCPV6_FillIaPrefixOption(UCHAR *pucMsgBuff,
                                        ULONG *pulOffset,
                                        in6_addr *pstIPv6Prefix,
                                        UCHAR ucIpv6PrefixLength)
{
    in6_addr stIpv6Addr;
    UCHAR ucPos = 0;
    UCHAR ucMoveBitNum = 0;
    USHORT usOptionLen = 0;
    ULONG ulPdExcludeLen = 0;
    DHCPV6_IAPREFIX_OPTION_S *pstIaPrefixOption = (DHCPV6_IAPREFIX_OPTION_S *)pucMsgBuff;

    /* ǰ׺���Ȳ��Ϸ� */
    if ((ucIpv6PrefixLength > DHCPV6S_PD_PREFIX_MAX_LEN)
        || (ucIpv6PrefixLength < DHCPV6S_PD_PREFIX_MIN_LEN))
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ucIpv6PrefixLength = %u", ucIpv6PrefixLength);
        return VOS_ERR;
    }

    /* ǰ׺���Ϸ� */
    if (VOS_TRUE == DHCPV6S_IPV6_ADDR_INVALID(pstIPv6Prefix))
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "IPv6Prefix = 0x%x:%x:%x:%x",
            pstIPv6Prefix->s6_addr32[0], pstIPv6Prefix->s6_addr32[1],
            pstIPv6Prefix->s6_addr32[2], pstIPv6Prefix->s6_addr32[3]);
        return VOS_ERR;
    }

    VOS_MemCpy(&(stIpv6Addr), pstIPv6Prefix, sizeof(in6_addr));
    DHCPV6_NTOHL_IPV6_ADDR(stIpv6Addr);
    pstIaPrefixOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_IAPREFIX);
    pstIaPrefixOption->ulPreTime = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);
    pstIaPrefixOption->ulValidTime = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);
    pstIaPrefixOption->ucPrefixLen = ucIpv6PrefixLength;
    usOptionLen += sizeof(UCHAR);

    /* ȷ��PDǰ׺ */
    LAP_SetPrefixLengthIp((ULONG *)&stIpv6Addr, ucIpv6PrefixLength, (ULONG *)&stIpv6Addr, &ucPos, &ucMoveBitNum);
    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "PdPrefix = 0x%x:%x:%x:%x, ucPos = %u, ucMoveBitNum = %u",
            stIpv6Addr.s6_addr32[0], stIpv6Addr.s6_addr32[1],
            stIpv6Addr.s6_addr32[2], stIpv6Addr.s6_addr32[3],
            ucPos, ucMoveBitNum);
    DHCPV6_HTONL_IPV6_ADDR(stIpv6Addr);
    VOS_MemCpy(&(pstIaPrefixOption->stIpv6Prefix), &stIpv6Addr, sizeof(in6_addr));
    usOptionLen += sizeof(in6_addr);

    /* ���pd-exclude-option */
    DHCPV6_FillPdExcludeOption(pstIaPrefixOption->ucData, &ulPdExcludeLen, pstIPv6Prefix, ucIpv6PrefixLength);
    usOptionLen += (USHORT)ulPdExcludeLen;
    pstIaPrefixOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "OptionLen = %u", usOptionLen);
    return VOS_OK;
}


VOID DHCPV6_FillIaPdOption(UCHAR *pucMsgBuff,
                                      ULONG *pulOffset,
                                      DHCPV6_OPT_S *pstDhcpv6Opt,
                                      SDB_GSPU_CONTEXT_S *pstContext,
                                      UCHAR ucIsFirstFlg)
{
    ULONG ulRet = VOS_OK;
    USHORT usOptionLen = 0;
    ULONG ulIaPrefixOptionLen = 0;
    ULONG ulStatusCodeOptionLen = 0;
    DHCPV6_IAPD_OPTION_S *pstIaPdOption = (DHCPV6_IAPD_OPTION_S *)pucMsgBuff;
    DHCPV6_IAPD_OPTION_S *pstSrcIaPdOption = (DHCPV6_IAPD_OPTION_S *)pstDhcpv6Opt;

    pstIaPdOption->usType = VOS_HTONS(DHCPV6_MSG_OPTION_IAPD);
    VOS_MemCpy(&(pstIaPdOption->ulId), &(pstSrcIaPdOption->ulId), sizeof(ULONG));
    usOptionLen += sizeof(ULONG);
    pstIaPdOption->ulT1 = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);
    pstIaPdOption->ulT2 = DHCP_INVALID_ULONG;
    usOptionLen += sizeof(ULONG);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucIpv6PrefixLength = %u, ucIsFirstFlg = %u",
                         pstContext->ucIpv6PrefixLength, ucIsFirstFlg);

    /* ����ǰ׺���Ȳ���49~63֮��,���߲��ǵ�һ��ia-pd-optionʱ,���code=6��status-code-option */
    if (((pstContext->ucIpv6PrefixLength > DHCPV6S_PD_PREFIX_MAX_LEN)
        || (pstContext->ucIpv6PrefixLength < DHCPV6S_PD_PREFIX_MIN_LEN))
        || (VOS_FALSE == ucIsFirstFlg))
    {
        /* ���status-code-option */
        DHCPV6_FillStatusCodeOption(pstIaPdOption->ucData, &ulStatusCodeOptionLen, DHCPV6C_STATUS_CODE_NOPREFIX);
        usOptionLen += (USHORT)ulStatusCodeOptionLen;
    }
    /* ǰ׺������49~63֮�䣬���ǵ�һ��ia-pd-optionʱ,���ia-prefix-option */
    else
    {
        /* ���ia-prefix-option */
        ulRet = DHCPV6_FillIaPrefixOption(pstIaPdOption->ucData, &ulIaPrefixOptionLen,
                            &(pstContext->stIPv6Addr), pstContext->ucIpv6PrefixLength);
        if (VOS_OK != ulRet)
        {
            /* ���ʧ��ʱ,���code=6��status-code-option */
            DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "call DHCPV6_FillIaPrefixOption fail");
            DHCPV6_FillStatusCodeOption(pstIaPdOption->ucData, &ulStatusCodeOptionLen, DHCPV6C_STATUS_CODE_NOPREFIX);
            usOptionLen += (USHORT)ulStatusCodeOptionLen;
        }
        else
        {
            usOptionLen += (USHORT)ulIaPrefixOptionLen;
        }
    }
    pstIaPdOption->usLen = VOS_HTONS(usOptionLen);
    *pulOffset += (DHCPV6_OPT_HEADER_LEN + usOptionLen);

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "OptionLen = %u", usOptionLen);
    return;
}
ULONG DHCPV6_FillIaPdOptionForMsg(UCHAR *pucMsgBuff,
                                               ULONG *pulOffset,
                                               DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                               SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulIaPdNum = 0;
    ULONG ulOptionLen = 0;
    USHORT usIaPdMinLen = 0;
    UCHAR ucIsFirstFlg = VOS_TRUE; /* �����ʼ��ΪVOS_TRUE */
    DHCPV6_OPT_S *pstDhcpv6Opt = NULL;

    /* IA-PD����С����,С�ڸó���ʱ�ᵼ�¹̶�����ȡֵ���� */
    usIaPdMinLen = sizeof(DHCPV6_IAPD_OPTION_S) - sizeof(DHCPV6_OPT_S);

    /*ָ���һ��OPTION*/
    pstDhcpv6Opt = (DHCPV6_OPT_S *)(pstMsgInfo->pucMsg + DHCPV6_HEADER_LEN);

    /* Ϊÿһ����Ч��ia-pd�����Ӧ��Ϣ */
    while((UCHAR *)pstDhcpv6Opt - pstMsgInfo->pucMsg < pstMsgInfo->ulMsgLen)
    {
        if ((DHCPV6_MSG_OPTION_IAPD == VOS_NTOHS(pstDhcpv6Opt->usOptType))
            && (VOS_NTOHS(pstDhcpv6Opt->usOptLen) >= usIaPdMinLen))
        {
            if (VOS_TRUE == ucIsFirstFlg)
            {
                DHCPV6_FillIaPdOption(&(pucMsgBuff[*pulOffset]), pulOffset,
                    pstDhcpv6Opt, pstContext, VOS_TRUE);
                ucIsFirstFlg = VOS_FALSE;
            }
            else
            {
                DHCPV6_FillIaPdOption(&(pucMsgBuff[*pulOffset]), pulOffset,
                    pstDhcpv6Opt, pstContext, VOS_FALSE);
            }
            ulIaPdNum ++;
        }

        ulOptionLen = DHCPV6_OPT_HEADER_LEN + VOS_NTOHS(pstDhcpv6Opt->usOptLen);
        pstDhcpv6Opt = (DHCPV6_OPT_S *)((UCHAR*)pstDhcpv6Opt + ulOptionLen);
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "IaPdNum = %u", ulIaPdNum);

    /* ��������Ч��ia-pd�򷵻�VOS_ERR,������Ϣ */
    if (0 == ulIaPdNum)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NO_VALID_IAPD);
        return VOS_ERR;
    }
    return VOS_OK;
}
VOID DHCPV6_FillRapidComOption(UCHAR *pucMsgBuff, ULONG *pulOffset)
{
    DHCPV6_OPT_S *pstRapidComOption = (DHCPV6_OPT_S *)pucMsgBuff;

    pstRapidComOption->usOptType = VOS_HTONS(DHCPV6_MSG_OPTION_RAPID_COMMIT);
    pstRapidComOption->usOptLen = 0;
    *pulOffset += DHCPV6_OPT_HEADER_LEN ;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "exit");
    return;
}


ULONG DHCPV6_FillMsg(UCHAR *pucMsgBuff,
                           ULONG *pulMsgLen,
                           DHCPV6S_MSG_INFO_S *pstMsgInfo,
                           SDB_GSPU_CONTEXT_S *pstContext,
                           UCHAR ucMsgType)
{
    ULONG ulRet = VOS_OK;
    ULONG ulCiOptionLen = 0;
    DHCPV6_OPT_S *pstCiOption = NULL;
    DHCPV6_MSG_S *pstDhcpv6Msg = NULL;

    /* �����Ϣͷ */
    pstDhcpv6Msg = (DHCPV6_MSG_S *)pucMsgBuff;
    VOS_MemCpy((UCHAR*)pstDhcpv6Msg, pstMsgInfo->pucMsg, sizeof(ULONG));
    pstDhcpv6Msg->ucMsgType = ucMsgType;
    *pulMsgLen += sizeof(ULONG);

    /* ���Я��CI,��copy */
    pstCiOption = pstMsgInfo->stDhcpOptionInfo.pstCiOption;
    if (NULL != pstCiOption)
    {
        ulCiOptionLen = DHCPV6_HEADER_LEN + VOS_NTOHS(pstCiOption->usOptLen);
        VOS_MemCpy(&pucMsgBuff[*pulMsgLen], pstCiOption, ulCiOptionLen);
        *pulMsgLen += ulCiOptionLen;
    }

    /* ���SI */
    DHCPV6_FillServerIdOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstContext);

    /* ���DNS */
    if (VOS_TRUE == pstMsgInfo->ucReqDnsFlg)
    {
        DHCPV6_FillDnsOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen, pstContext);
    }

    /* ���IaPd */
    if (VOS_TRUE == pstMsgInfo->ucReqPdFlg)
    {
        ulRet = DHCPV6_FillIaPdOptionForMsg(pucMsgBuff, pulMsgLen, pstMsgInfo, pstContext);
        if (VOS_OK != ulRet)
        {
            return VOS_ERR;
        }
    }

    /* ���Rapid-commit */
    if (VOS_TRUE == pstMsgInfo->ucReqRapidFlg)
    {
        DHCPV6_FillRapidComOption(&(pucMsgBuff[*pulMsgLen]), pulMsgLen);
    }

    return VOS_OK;
}

#define __MSG_SEND__

VOID DHCPV6_CalcSuccSendPacketNum(UCHAR ucMsgType)
{
    /* ��Ϣ���� */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_ADVERTISE :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_ADVERTISE_SUCC);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_REPLY_SUCC);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_OTHER_SUCC);
            break;
    }

    return;
}
VOID DHCPV6_CalcFailSendPacketNum(UCHAR ucMsgType)
{
    /* ��Ϣ���� */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_ADVERTISE :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_ADVERTISE_FAIL);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_REPLY_FAIL);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_SEND_OTHER_FAIL);
            break;
    }

    return;
}
ULONG DHCPV6_SendMsgOut(UCHAR *pMbuf, ULONG ulPdpIndex,
                               UCHAR ucLeftEncapType)
{
    /* ����ͨ�÷�װGTPͷ�ĺ�������װGTPͷ�����ͱ��� */
    if(DHCP_ENCAP_PMIP_GRE == ucLeftEncapType)
    {
        g_ulGreProType = 1;
        DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "gre-encape");
        if (VOS_OK != UGW_GRE_Encap((PMBUF_S *)pMbuf, ulPdpIndex))
        {
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GRE_SEND_ERR);
            return VOS_ERR;
        }
    }
    else
    {
        DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "gtp-encape");
        if (VOS_OK != UGW_GtpEncap((PMBUF_S *)pMbuf, ulPdpIndex))
        {
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GTP_SEND_ERR);
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
ULONG DHCPV6_SendMsgToClient(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                          SDB_GSPU_CONTEXT_S *pstContext,
                                          UCHAR ucMsgType)
{
    in6_addr stDstAddr;    /* Ŀ�ĵ�ַ */
    ULONG ulMsgLen = 0;    /* dhcp��Ϣ�ܳ��� */
    ULONG ulRet = VOS_OK;
    USHORT usUdpMsgLen = 0;
    PMBUF_S *pstMbuf = NULL;
    ULONG ulDhcpMsgLen = 0;    /* dhcp��Ϣ�峤�� */
    USHORT usCheckSumFresh = 0;
    IPV6HDR_S *pstIpv6Hdr = NULL;
    UDPHDR_S *pstUdpv6Hdr = NULL;

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucMsgType = %u", ucMsgType);
    DHCP_MemZero(g_pucDhcpv6sSendBuff, DHCPV6S_SEND_MSG_MAXLEN);

    /* �����Ϣ Ԥ����ipͷ��udpͷ */
    pstIpv6Hdr = (IPV6HDR_S *)g_pucDhcpv6sSendBuff;
    pstUdpv6Hdr = (UDPHDR_S *)&g_pucDhcpv6sSendBuff[IPV6_HEADER_LEN];
    ulRet = DHCPV6_FillMsg(&g_pucDhcpv6sSendBuff[IPV6_HEADER_LEN + UDPV6_HEADER_LEN],
                            &ulDhcpMsgLen, pstMsgInfo, pstContext, ucMsgType);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    usUdpMsgLen= (USHORT)(ulDhcpMsgLen + UDPV6_HEADER_LEN);
    pstUdpv6Hdr->uh_sULen = (SHORT)VOS_HTONS(usUdpMsgLen);
    pstUdpv6Hdr->uh_usDPort = pstMsgInfo->usSrcPort;
    pstUdpv6Hdr->uh_usSPort = pstMsgInfo->usDstPort;

    if(ipv6_addr_any(&pstMsgInfo->stSrcAddr))
    {
        ipv6_addr_all_nodes(&stDstAddr);
    }
    else
    {
        ipv6_addr_copy(&stDstAddr, &pstMsgInfo->stSrcAddr);
    }

    if (VOS_OK != ICMPv6_CheckSum((UCHAR *)pstIpv6Hdr, in6addr_ggsn, stDstAddr, (UCHAR *)pstUdpv6Hdr,
                                    usUdpMsgLen, &usCheckSumFresh, IPV6_UDP_PRO))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_CHECKSUM_ERR);
        return VOS_ERR;
    }
    pstUdpv6Hdr->uh_usSum = usCheckSumFresh;

    /* ��дIPͷ���� */
    *(ULONG*)pstIpv6Hdr = VOS_HTONL(0x60000000); /* version and etc */
    pstIpv6Hdr->payload_len = VOS_HTONS(usUdpMsgLen);
    pstIpv6Hdr->nexthdr = IPV6_UDP_PRO;
    pstIpv6Hdr->hop_limit = 255;
    ipv6_addr_copy(&(pstIpv6Hdr->saddr), &in6addr_ggsn);
    ipv6_addr_copy(&(pstIpv6Hdr->daddr), &stDstAddr);

    /* ��Ϣ�ܳ��� */
    ulMsgLen = IPV6_HEADER_LEN + usUdpMsgLen;

    /* modify by w00316385 start */
    /* ����MBUF */
#if 0
    pstMbuf = PMBUF_CreateByCopyBuffer(0, ulMsgLen, g_pucDhcpv6sSendBuff,
                                          MBUF_TYPE_DATA, MID_DHCPSV6);
#endif
    pstMbuf = PMBUF_GetPMbuf(MID_DHCPC, ulMsgLen);
    /* modify by w00316385 end */

    if (NULL == pstMbuf)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MALLOC_BUFF_FAIL);
        return VOS_ERR;
    }

    ulRet = DHCPV6_SendMsgOut((UCHAR *)pstMbuf, pstMsgInfo->ulPdpIndex, pstContext->ucLeftEncapType);
    if (VOS_OK != ulRet)
    {
        /* ����ʧ���ͷ�buf */
        (VOID)PMBUF_Destroy(pstMbuf);

        /* ������Ϣʧ�ܼ��� */
        DHCPV6_CalcFailSendPacketNum(ucMsgType);
        return VOS_ERR;
    }

    /* ������Ϣ�ɹ����� */
    DHCPV6_CalcSuccSendPacketNum(ucMsgType);

    /* ֻ��information-reques�Ž�������ͳ�� */
    if (DHCPV6_MSG_TYPE_INFORMATION_REQUEST == pstMsgInfo->ucMsgType)
    {
        if (VOS_NULL_PTR != g_PGWtoUE_ulDHCPV6AckNumAddr)
        {
            (VOID)PerfSetFamPerfCounterByAddress(g_PGWtoUE_ulDHCPV6AckNumAddr, E_PERF_OBJECT_ADD, 1);
        }
    }

    /* ��Ϣ���� */
    DHCPV6_MsgTraceProc((DHCPV6_MSG_S*)(&g_pucDhcpv6sSendBuff[IPV6_HEADER_LEN + UDPV6_HEADER_LEN]),
                        ulDhcpMsgLen, pstContext, pstUdpv6Hdr, M_EMS_TRC_SEND_MSG);

    return VOS_OK;
}
VOID DHCPV6_CalcSuccRelayPacketNum(UCHAR ucMsgType)
{
    /* ��Ϣ���� */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_INFO_SUCC);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_REPLY_SUCC);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_OTHER_SUCC);
            break;
    }

    return;
}
VOID DHCPV6_CalcFailRelayPacketNum(UCHAR ucMsgType)
{
    /* ��Ϣ���� */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_INFO_FAIL);
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_REPLY_FAIL);
            break;

        default:
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_RELAY_OTHER_FAIL);
            break;
    }

    return;
}
ULONG DHCPv6_RelaySendMsg(PMBUF_S *pMbuf, UCHAR ucMsgType, ULONG ulPdpIndex)
{
    /*���IP��ַ��UDP�˿ںţ�������GTP����GRE�ķ�ʽ���ͳ�ȥ */
    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST :
            DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "info-request");
            g_ulGreProType = 1;
            if (VOS_OK != UGW_GRE_Encap(pMbuf, ulPdpIndex))
            {
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GRE_RELAY_ERR);
                return VOS_ERR;
            }
            break;

        case DHCPV6_MSG_TYPE_REPLY :
            DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "reply");
            if (VOS_OK != UGW_GtpEncap(pMbuf, ulPdpIndex))
            {
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_GTP_RELAY_ERR);
                return VOS_ERR;
            }
            break;

        default:
            return VOS_ERR;
    }

    return VOS_OK;
}
ULONG DHCPv6_RelayMsg(UCHAR *pucDateMsg, ULONG ulIpPacketLen,
                               ULONG ulPdpIndex, SDB_GSPU_CONTEXT_S *pstContext)
{
    UCHAR ucMsgType = 0;
    ULONG ulRet = VOS_OK;
    PMBUF_S *pMbuf = NULL;
    DHCPV6_MSG_S *pstDhcpPacket = NULL;
    ULONG ulMsgHeadLen = IPV6_HEADER_LEN + UDPV6_HEADER_LEN;
    ULONG ulDhcpMsgLen = ulIpPacketLen - ulMsgHeadLen;

    /*����ж�*/
    if((NULL == pucDateMsg) || (NULL == pstContext))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NULL_MSG);
        return VOS_ERR;
    }

    pstDhcpPacket = (DHCPV6_MSG_S*)(pucDateMsg + IPV6_HEADER_LEN + UDP_HEADER_LENGTH);
    ucMsgType = pstDhcpPacket->ucMsgType;

    /* �յ���Ϣ, �ϱ���Ϣ���� */
    DHCPV6_MsgTraceProcForRelay(pucDateMsg, ulDhcpMsgLen, ucMsgType, pstContext,
                                   M_EMS_TRC_RECV_MSG);

    /* �ж���Ϣ���� */
    if ((DHCPV6_MSG_TYPE_INFORMATION_REQUEST != ucMsgType)
        && (DHCPV6_MSG_TYPE_REPLY != ucMsgType))
    {
        return VOS_ERR;
    }

    /*����MBUF*/
    /* modify by w00316385 start */
#if 0
    pMbuf = PMBUF_CreateByCopyBuffer (0, ulIpPacketLen, pucDateMsg,
                                         MBUF_TYPE_DATA, MID_DHCPSV6);
#endif
    pMbuf = PMBUF_GetPMbuf(MID_DHCPC, ulIpPacketLen);
    /* modify by w00316385 end */

    if (NULL == pMbuf)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_MALLOC_BUFF_FAIL);
        return VOS_ERR;
    }

    /* relay ������Ϣ */
    ulRet = DHCPv6_RelaySendMsg(pMbuf, ucMsgType, ulPdpIndex);
    if (ulRet != VOS_OK)
    {
        /* ����Ϣʧ�ܼ��� */
        DHCPV6_CalcFailRelayPacketNum(ucMsgType);
        (VOID)PMBUF_Destroy(pMbuf);
        return VOS_ERR;
    }

    /* ����Ϣ�ɹ����� */
    DHCPV6_CalcSuccRelayPacketNum(ucMsgType);

    /* �ϱ���Ϣ���� */
    DHCPV6_MsgTraceProcForRelay(pucDateMsg, ulDhcpMsgLen, ucMsgType, pstContext,
                                   M_EMS_TRC_SEND_MSG);

    return VOS_OK;
}


#define __MSG_PROCESS__

ULONG DHCPV6_MsgPreProcForNotRelay(UCHAR *pucSrcMsg, ULONG ulMsgLen,
                                                   SDB_GSPU_CONTEXT_S *pstContext,
                                                   DHCPV6S_MSG_INFO_S *pstMsgInfo)
{
    /* ���IP-UDPͷ, �ڲ��м�������Ҫ��� */
    if(VOS_OK != DHCPV6_CheckIpUdp(pucSrcMsg, ulMsgLen))
    {
        return VOS_ERR;
    }

    /* ��Ϣ���ȼ�� */
    if (VOS_OK != DHCPV6_CheckMsgLen(pucSrcMsg, ulMsgLen))
    {
        return VOS_ERR;
    }

    /* ��Ϣ���װ */
    DHCPV6_MsgUnpacket(pstMsgInfo, pucSrcMsg, ulMsgLen);

    /* ��Ϣ���� */
    DHCPV6_MsgDecode(pstMsgInfo);

    return VOS_OK;
}


ULONG DHCPV6_InfoReqProc(UCHAR *pucSrcMsg, ULONG ulMsgLen,
                                    ULONG ulPdpIndex,
                                    SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    ULONG ulOptionFlag = 0;
    UDPHDR_S *pstUdp = NULL;
    ULONG ulMsgHeadLen = 0;
    DHCPV6S_MSG_INFO_S stMsgInfo = {0};

    /* ��Ϣ���� */
    ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;
    pstUdp = (UDPHDR_S *)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN);
    DHCPV6_MsgTraceProc((DHCPV6_MSG_S*)(pucSrcMsg + ulMsgHeadLen),
            ulMsgLen - ulMsgHeadLen, pstContext, pstUdp, M_EMS_TRC_RECV_MSG);

    /* ��ϢԤ����----��Ϣ���,���װ,���� */
    ulRet = DHCPV6_MsgPreProcForNotRelay(pucSrcMsg, ulMsgLen, pstContext, &stMsgInfo);
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /*  RFC3315
    15.12. Information-request Message

       Clients MUST discard any received Information-request messages.

       Servers MUST discard any received Information-request message that
       meets any of the following conditions:

       -  The message includes a Server Identifier option and the DUID in
          the option does not match the server's DUID.

       -  The message includes an IA option.
    */
    ulOptionFlag = stMsgInfo.stDhcpOptionInfo.ulOptionFlag ;
    if(0 != (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_IA_NA)) ||
        0 != (ulOptionFlag & (1 << DHCPV6_MSG_OPTION_IA_TA)))
    {
        g_stDhcpv6Statistics.ulInfoReqWithIAErr++;
        return VOS_ERR;
    }

    /* ��Ϣ����Ƿ�����DNS */
    ulRet = DHCPV6_CheckForReqDns(&(stMsgInfo.stDhcpOptionInfo));
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }
    stMsgInfo.ucReqDnsFlg = VOS_TRUE;
    stMsgInfo.ulPdpIndex = ulPdpIndex;

    /* �ظ�reply��Ϣ */
    ulRet = DHCPV6_SendMsgToClient(&stMsgInfo, pstContext, DHCPV6_MSG_TYPE_REPLY);
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}

ULONG DHCPV6_InfoMsgProc(UCHAR *pucSrcMsg, ULONG ulMsgLen, ULONG ulPdpIndex,
                                    SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    ULONG ulIpPacketLen = ulMsgLen - sizeof(FWD_TO_CTRL_HDR);
    UCHAR *pucDateMsg = pucSrcMsg + sizeof(FWD_TO_CTRL_HDR);

    if((E_NET_ELEMENT_ROLE_SGW == pstContext->ucUgwRole)
        && (DHCP_ENCAP_PMIP_GRE == pstContext->ucRightEncapType))
    {
        if (VOS_NULL_PTR != g_UEtoSGW_ulDHCPV6InformRequestNumAddr)
        {
            (VOID)PerfSetFamPerfCounterByAddress(g_UEtoSGW_ulDHCPV6InformRequestNumAddr, E_PERF_OBJECT_ADD, 1);
        }

        /*����͸����PGW*/
        if (VOS_OK != DHCPv6_RelayMsg(pucDateMsg, ulIpPacketLen, ulPdpIndex, pstContext))
        {
            g_stDhcpv6Statistics.ulRelayStateInfoNum++;
            return VOS_ERR;
        }
        return VOS_OK;
    }

     /* Ŀǰֻ������һ����Ϣ */
    if (VOS_NULL_PTR != g_UEtoPGW_ulDHCPV6InformRequestNumAddr)
    {
        (VOID)PerfSetFamPerfCounterByAddress(g_UEtoPGW_ulDHCPV6InformRequestNumAddr, E_PERF_OBJECT_ADD, 1);
    }

    /* ����info-request��Ϣ */
    ulRet = DHCPV6_InfoReqProc(pucSrcMsg, ulMsgLen, ulPdpIndex, pstContext);
    return ulRet;
}
ULONG DHCPV6_ReplyMsgProc(UCHAR *pucSrcMsg, ULONG ulMsgLen, ULONG ulPdpIndex,
                                      SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulIpPacketLen = ulMsgLen - sizeof(FWD_TO_CTRL_HDR);
    UCHAR *pucDateMsg = pucSrcMsg + sizeof(FWD_TO_CTRL_HDR);

    if((E_NET_ELEMENT_ROLE_SGW == pstContext->ucUgwRole)
        && (DHCP_ENCAP_PMIP_GRE == pstContext->ucRightEncapType))
    {
        if (VOS_NULL_PTR != g_SGWtoUE_ulDHCPV6AckNumAddr)
        {
            (VOID)PerfSetFamPerfCounterByAddress(g_SGWtoUE_ulDHCPV6AckNumAddr, E_PERF_OBJECT_ADD, 1);
        }

        /*����͸�����ֻ�*/
        if (VOS_OK != DHCPv6_RelayMsg(pucDateMsg, ulIpPacketLen, ulPdpIndex, pstContext))
        {
            g_stDhcpv6Statistics.ulRelayStateReplyNum++;
            return VOS_ERR;
        }
    }

    return VOS_OK;
}
ULONG DHCPV6_SolicitMsgProc(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                       SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;

    /* ����Ƿ�Я��rapid-commit*/
    if (0 != (pstMsgInfo->stDhcpOptionInfo.ulOptionFlag & (1 << DHCPV6_MSG_OPTION_RAPID_COMMIT)))
    {
        pstMsgInfo->ucReqRapidFlg = VOS_TRUE;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucReqRapidFlg = %u", pstMsgInfo->ucReqRapidFlg);

    /* �ظ�reply��Ϣ */
    if (VOS_TRUE == pstMsgInfo->ucReqRapidFlg)
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_2_STEP);
        ulRet = DHCPV6_SendMsgToClient(pstMsgInfo, pstContext, DHCPV6_MSG_TYPE_REPLY);
    }
    else    /* �ظ�advertise��Ϣ */
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_4_STEP);
        ulRet = DHCPV6_SendMsgToClient(pstMsgInfo, pstContext, DHCPV6_MSG_TYPE_ADVERTISE);
    }

    return ulRet;
}
ULONG DHCPV6_RequstMsgProc(DHCPV6S_MSG_INFO_S *pstMsgInfo,
                                       SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;

    /* �ظ�reply��Ϣ */
    ulRet = DHCPV6_SendMsgToClient(pstMsgInfo, pstContext, DHCPV6_MSG_TYPE_REPLY);

    return ulRet;
}
ULONG DHCPV6_SolicitReqMsgProc(UCHAR *pucSrcMsg, ULONG ulMsgLen,
                                            UCHAR ucMsgType, ULONG ulPdpIndex,
                                            SDB_GSPU_CONTEXT_S *pstContext)
{
    ULONG ulRet = VOS_OK;
    UDPHDR_S *pstUdp = NULL;
    ULONG ulMsgHeadLen = 0;
    DHCPV6S_MSG_INFO_S stMsgInfo = {0};

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucMsgType = %u", ucMsgType);

    /* ��Ϣ���� */
    ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;
    pstUdp = (UDPHDR_S *)(pucSrcMsg + sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN);
    DHCPV6_MsgTraceProc((DHCPV6_MSG_S*)(pucSrcMsg + ulMsgHeadLen),
            ulMsgLen - ulMsgHeadLen, pstContext, pstUdp, M_EMS_TRC_RECV_MSG);

    /* ��ɫ���װ��ʽ�ж� */
    if ((E_NET_ELEMENT_ROLE_SGW == pstContext->ucUgwRole)
        || (DHCP_ENCAP_PMIP_GRE == pstContext->ucRightEncapType))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_ROLE_ENCAPE_ERR);
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "ucUgwRole = %u, ucRightEncapType = %u",
                             pstContext->ucUgwRole, pstContext->ucRightEncapType);
        return VOS_ERR;
    }

    /* ��ϢԤ����----��Ϣ���,���װ,���� */
    ulRet = DHCPV6_MsgPreProcForNotRelay(pucSrcMsg, ulMsgLen, pstContext, &stMsgInfo);
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* ����Ƿ�����IA_PD,PD_EXCLUDE */
    ulRet = DHCPV6_CheckForReqIaPd(&(stMsgInfo.stDhcpOptionInfo));
    if(VOS_OK != ulRet)
    {
        return VOS_ERR;
    }
    stMsgInfo.ucReqPdFlg = VOS_TRUE;
    stMsgInfo.ulPdpIndex = ulPdpIndex;

    switch (ucMsgType)
    {
        case DHCPV6_MSG_TYPE_SOLICIT :
            ulRet = DHCPV6_SolicitMsgProc(&stMsgInfo, pstContext);
            break;

        case DHCPV6_MSG_TYPE_REQUEST :
            ulRet = DHCPV6_RequstMsgProc(&stMsgInfo, pstContext);
            break;

        default:
            ulRet = VOS_ERR;
            break;
    }
    return ulRet;
}


ULONG DHCPV6_GetMbufData(PMBUF_S* pstMsgBuf, UCHAR **ppMsg, ULONG *pulMsgLen)
{
    ULONG ulMsgLen = 0;

    if (NULL == pstMsgBuf)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "pstMBuf = NULL!");
        return VOS_ERR;
    }

    /*��ȡ���ĳ��Ⱥ͵�ַ*/
    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (DHCPV6S_REV_MSG_MAXLEN < ulMsgLen)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "length(%u) > 4096!", ulMsgLen);
        return VOS_ERR;
    }

    *pulMsgLen = ulMsgLen;
    DHCP_MemZero(g_pucDhcpv6sRevBuff, DHCPV6S_REV_MSG_MAXLEN);

    /* û�з�Ƭ BLOCK_NUMBERΪ 1 */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        *ppMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        /* �з�Ƭ����Ҫ���Ƶ������ڴ� , ��MBUF���ݸ��Ƶ����������ڴ��� */
        if (VOS_OK != PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf, 0, ulMsgLen, g_pucDhcpv6sRevBuff))
        {
            DHCPV6S_DebugPrint(PTM_LOG_ERR, "copy buf from mbuf fail!");
            return VOS_ERR;
        }
        *ppMsg = g_pucDhcpv6sRevBuff;
    }

    return VOS_OK;
}
ULONG DHCPV6_MsgProc(PMBUF_S *pstMsgBuf)
{
    ULONG ulMsgLen = 0;
    ULONG ulRet = VOS_OK;
    ULONG ulPdpIndex = 0;
    UCHAR *pucSrcMsg = NULL;
    DHCPV6_MSG_S *pDhcpv6Msg = NULL;
    SDB_GSPU_CONTEXT_S *pstContext = VOS_NULL_PTR;
    ULONG ulMsgHeadLen = sizeof(FWD_TO_CTRL_HDR) + IPV6_HEADER_LEN + UDPV6_HEADER_LEN;

    if (ulDhcpv6sPerfInitFinish != VOS_TRUE)
    {
        (VOID)DHCPV6S_OmInitial();
    }

    /* ��buff��ȡ����Ϣ�ͳ��� */
    (VOID)DHCPV6_GetMbufData(pstMsgBuf, &pucSrcMsg, &ulMsgLen);
    if (NULL == pucSrcMsg)
    {
        return VOS_ERR;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulMsgLen = %u", ulMsgLen);

    g_stDhcpv6Statistics.ulTotal++;

    /* ��Ϊ���ipv4ͷ�Ѿ���ת������,��˲����������нӿڸ���,������������� */
    /* ��ȡPDP-index�������� */
    (VOID)DHCPV6_GetPdpIdxAndContext((FWD_TO_CTRL_HDR*)pucSrcMsg, &ulPdpIndex, &pstContext);
    if (NULL == pstContext)
    {
        return VOS_ERR;
    }

    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ulPdpIndex = %u, ucUgwRole = %u", ulPdpIndex, pstContext->ucUgwRole);

    /* ת�����͵ı��İ���UDPͷ��IPͷ����������һ��ת��ͷ */
    pDhcpv6Msg = (DHCPV6_MSG_S*)(pucSrcMsg + ulMsgHeadLen);
    DHCPV6S_DebugPrint(PTM_LOG_DEBUG, "ucMsgType = %u", pDhcpv6Msg->ucMsgType);

    switch(pDhcpv6Msg->ucMsgType)
    {
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_INFO);
                ulRet = DHCPV6_InfoMsgProc(pucSrcMsg, ulMsgLen, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_REPLY:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_REPLY);
                ulRet = DHCPV6_ReplyMsgProc(pucSrcMsg, ulMsgLen, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_SOLICIT:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_SOLICIT);
                ulRet = DHCPV6_SolicitReqMsgProc(pucSrcMsg, ulMsgLen, pDhcpv6Msg->ucMsgType, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_REQUEST:
                DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_REQUEST);
                ulRet = DHCPV6_SolicitReqMsgProc(pucSrcMsg, ulMsgLen, pDhcpv6Msg->ucMsgType, ulPdpIndex, pstContext);
                break;
        case DHCPV6_MSG_TYPE_ADVERTISE:
        case DHCPV6_MSG_TYPE_CONFIRM:
        case DHCPV6_MSG_TYPE_RENEW:
        case DHCPV6_MSG_TYPE_REBIND:
        case DHCPV6_MSG_TYPE_RELEASE:
        case DHCPV6_MSG_TYPE_DECLINE:
        case DHCPV6_MSG_TYPE_RECONFIGURE:
        case DHCPV6_MSG_TYPE_RELAY_FORW:
        case DHCPV6_MSG_TYPE_RELAY_REPL:
                g_stDhcpv6Statistics.ulUnsupportMsgErr++;
                return VOS_ERR;
        default:
                g_stDhcpv6Statistics.ulUnknownMsgErr++;
                return VOS_ERR;
    }

    return ulRet;
}

