/*************************************************************************************
 *                                                                                   *
 *                         DHCPv6_PROC.H                                                  *
 *                                                                                   *
 *  ��Ŀ���룺       UGW V900R001C01                                             *
 *  �������ڣ�       2008/12/12                                                         *
 *  ���ߣ�          �ܾ�ƽ 38085                                               *
 *  �޸���ʷ�б�                                                                   *
 *  ���ܣ�
 *  ������                                            *
 *                                                                                     *
 *-----------------------------------------------------------------------------------*
 *                                                                                   *
 *  Copyright 2001-2002 GGSN80 Team BEIJING Institute HuaWei Tech, Inc.           *
 *                     ALL RIGHTS RESERVED                                           *
 *                                                                                     *
 *************************************************************************************/
#ifndef __DHCPV6_PROC_H__
#define __DHCPV6_PROC_H__


#ifdef   __WIN32_PLATFORM__
#pragma pack(push, 1)
#endif


/*  DHCP �Ķಥ��ַ

      All_DHCP_Relay_Agents_and_Servers address:   FF02::1:2
      All_DHCP_Servers address:                    FF05::1:3

     Clients listen for DHCP messages on UDP port 546.
     Servers and relay agents listen for DHCP messages on UDP port 547.

*/
/********************************************************************************/
/******************                  ȫ�ֱ���                 *******************/
/********************************************************************************/

extern UCHAR* g_pucDhcpv6sSendBuff;        /*������Ϣ����*/
extern UCHAR* g_pucDhcpv6sRevBuff;        /*������Ϣ����*/

/********************************************************************************/
/******************                  �궨��                 *******************/
/********************************************************************************/

#define    DHCPSV6_MAX_SHARE_QUE_ATTACH_NUM  100
#define    DHCPV6_DFT_QUEUE_LENGTH                      128
#define    DHCPV6_FLOWCONTROL_MAX                       20

/* �յ�DHCP��Ϣ��ʱ��λ */
#define     DHCPV6S_DHCP_MSG_EV   1

#define DHCPV6S_REV_MSG_MAXLEN 4096  /* ������Ϣ��󳤶� */
#define DHCPV6S_SEND_MSG_MAXLEN 8192  /* ������Ϣ��󳤶� */

#define DHCPV6S_PREFIX_LEN  64 /* ǰ׺���� */
#define DHCPV6S_PD_PREFIX_MAX_LEN  63  /* ǰ׺��󳤶� */
#define DHCPV6S_PD_PREFIX_MIN_LEN  49  /* ǰ׺��С���� */

extern ULONG ipv6_addr_any(in6_addr *a);
extern ULONG ipv6_addr_all_one(in6_addr *a);
/* IPV6��ַ��Ч */
#define DHCPV6S_IPV6_ADDR_INVALID(pstIpv6Addr)\
(                                                 \
    (ipv6_addr_any((pstIpv6Addr)) || ipv6_addr_all_one((pstIpv6Addr))) ? \
    VOS_TRUE : VOS_FALSE \
)

/* ������Ϣ����ȷ���������� */
#define DHCPV6S_GET_TRCTYPE_BY_DIR(ulDirection, enTraceType, enExtTraceType, ulMsgClass)\
{\
    if((TRC_DIRECTION_LEFT_IN_SGW == (ulDirection))||(TRC_DIRECTION_LEFT_OUT_SGW == (ulDirection)))\
    {\
        (enTraceType) = TRC_TYPE_SGW_S4S11S12S1U;\
        (enExtTraceType) = TRC_TYPE_EXTERN_SGW_S4S11S12S1U; \
        (ulMsgClass) = S4S11_MSGTYPE_DHCPV6;\
    }\
    else if((TRC_DIRECTION_RIGHT_IN_SGW == (ulDirection))||(TRC_DIRECTION_RIGHT_OUT_SGW == (ulDirection)))\
    {\
        (enTraceType) = TRC_TYPE_SGW_S5S8;\
        (enExtTraceType) = TRC_TYPE_EXTERN_SGW_S5S8;        \
        (ulMsgClass) = S5S8_MSGTYPE_DHCPV6;\
    }\
    else if((TRC_DIRECTION_LEFT_IN_PGW == (ulDirection))||(TRC_DIRECTION_LEFT_OUT_PGW == (ulDirection))\
        || (TRC_DIRECTION_IN_GGSN == (ulDirection))||(TRC_DIRECTION_OUT_GGSN == (ulDirection)))\
    {\
        (enTraceType) = TRC_TYPE_PGW_S5S8S2AGNGP;\
        (enExtTraceType) = TRC_TYPE_EXTERN_PGW_S5S8S2AS2BGNGP;       \
        (ulMsgClass) = S5S8S2A_MSGTYPE_DHCPV6;\
    }\
    else\
    {\
        (enTraceType) = TRC_TYPE_BUTT;\
        (enExtTraceType) = TRC_TYPE_BUTT;                \
    }\
}

/* ���ݽ�ɫ����Ϣ����ȷ����Ϣ���ٵķ��� */
#define DHCPV6S_GET_TRCDIR_BY_ROLE(ucUgwRole, ulEmsTrcDir, ulDirection)\
{\
    if (E_NET_ELEMENT_ROLE_PGW == (ucUgwRole))\
    {\
        if (M_EMS_TRC_RECV_MSG == (ulEmsTrcDir))\
        {\
            (ulDirection) = TRC_DIRECTION_LEFT_IN_PGW;\
        }\
        else\
        {\
            (ulDirection) = TRC_DIRECTION_LEFT_OUT_PGW;\
        }\
    }\
    else if (E_NET_ELEMENT_ROLE_GGSN == (ucUgwRole))\
    {\
        if (M_EMS_TRC_RECV_MSG == (ulEmsTrcDir))\
        {\
            (ulDirection) = TRC_DIRECTION_IN_GGSN;\
        }\
        else\
        {\
            (ulDirection) = TRC_DIRECTION_OUT_GGSN;\
        }\
    }\
    else\
    {\
        if (M_EMS_TRC_RECV_MSG == (ulEmsTrcDir))\
        {\
            (ulDirection) = TRC_DIRECTION_LEFT_IN_SGW;\
        }\
        else\
        {\
            (ulDirection) = TRC_DIRECTION_LEFT_OUT_SGW;\
        }\
    }\
}

/* relay��Ϣʱ������Ϣ����ȷ��������Ϣ�ĸ��ٲ��� */
#define DHCPV6S_GET_TRCPARA_FOR_RELAY_REV(ucMsgType, ulDirection, stPath, pstUdp, pstContext)\
{\
    switch((ucMsgType))\
    {\
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST:\
            (ulDirection) = TRC_DIRECTION_LEFT_IN_SGW;\
            ((stPath).ulLocalAddr) = (pstContext)->ulSgwLeftLocDataIP;\
            ((stPath).ulPeerAddr)  = (pstContext)->ulSgwLeftPeerDataIP;\
            break;\
        case DHCPV6_MSG_TYPE_REPLY:\
            (ulDirection) = TRC_DIRECTION_RIGHT_IN_SGW;\
            ((stPath).ulLocalAddr) = (pstContext)->ulS5_Gn_LocDataIP;\
            ((stPath).ulPeerAddr)  = (pstContext)->ulS5_Gn_PeerDataIP;\
            break;\
        default :\
            break;\
    }\
    ((stPath).usLocalPort) = VOS_NTOHS((pstUdp)->uh_usDPort);\
    ((stPath.usPeerPort))  = VOS_NTOHS((pstUdp)->uh_usSPort);\
}

/* relay��Ϣʱ������Ϣ����ȷ��������Ϣ�ĸ��ٲ��� */
#define DHCPV6S_GET_TRCPARA_FOR_RELAY_SEND(ucMsgType, ulDirection, stPath, pstContext)\
{\
    switch((ucMsgType))\
    {\
        case DHCPV6_MSG_TYPE_INFORMATION_REQUEST:\
            (ulDirection) = TRC_DIRECTION_RIGHT_IN_SGW;\
            ((stPath).ulLocalAddr) = pstContext->ulS5_Gn_LocDataIP;\
            ((stPath).ulPeerAddr)  = pstContext->ulS5_Gn_PeerDataIP;\
            ((stPath).usLocalPort) = DHCPV6_SERVER_UDP_PORT;\
            ((stPath.usPeerPort))  = DHCPV6_RELAY_UDP_PORT;\
            break;\
        case DHCPV6_MSG_TYPE_REPLY:\
            (ulDirection) = TRC_DIRECTION_LEFT_OUT_SGW;\
            ((stPath).ulLocalAddr) = pstContext->ulSgwLeftLocDataIP;\
            ((stPath).ulPeerAddr)  = pstContext->ulSgwLeftPeerDataIP;\
            ((stPath).usLocalPort) = DHCPV6_RELAY_UDP_PORT;\
            ((stPath.usPeerPort))  = DHCPV6_CLIENT_UDP_PORT;\
            break;\
        default :\
            break;\
    }\
}

/********************************************************************************/
/******************                  �ṹ��                 *******************/
/********************************************************************************/

/*�����ȫ����չ���� 1�ֽڶ���*/
#pragma pack(1)
/* DUID-EN */
typedef struct tagDHCPV6_DUID_EN_OPTION_S
{
    USHORT usType;    /* Type */
    ULONG  ulEnterpriseNum;     /* EnterpriseNum */
    UCHAR ucData[0];  /* value */
}DHCPV6_DUID_EN_OPTION_S;

/* IA-PD */
typedef struct tagDHCPV6_IAPD_OPTION_S
{
    USHORT usType;    /* Type */
    USHORT usLen;     /* Length */
    ULONG ulId;     /* IA-ID */
    ULONG ulT1;       /* t1 */
    ULONG ulT2;       /* t2 */
    UCHAR ucData[0];  /* IA_PD-options */
}DHCPV6_IAPD_OPTION_S;

/* IA-PREFIX */
typedef struct tagDHCPV6_IAPREFIX_OPTION_S
{
    USHORT usType;             /* Type */
    USHORT usLen;              /* Length */
    ULONG ulPreTime;          /* preferred-lifetime */
    ULONG ulValidTime;        /* valid-lifetime */
    UCHAR ucPrefixLen;
    in6_addr stIpv6Prefix;      /* IPv6 address */
    UCHAR ucData[0];  /* IA_PREFIX-options */
}DHCPV6_IAPREFIX_OPTION_S;

/* pd-exclude */
typedef struct tagDHCPV6_PDEXCLUDE_OPTION_S
{
    USHORT usType;             /* Type */
    USHORT usLen;              /* Length */
    UCHAR ucPrefixLen;
    UCHAR ucData[0];
}DHCPV6_PDEXCLUDE_OPTION_S;

/* dhcpv6 option struct */
typedef struct tag_opt_dhcpv6 {
    USHORT    usOptType;
    USHORT    usOptLen;
    UCHAR      opt[0];
}VOS_PACKED DHCPV6_OPT_S;

/* dhcpv6 msg struct */
typedef struct tag_msg_dhcpv6 {
    UCHAR           ucMsgType;
    ULONG           ulTransId:24;
    DHCPV6_OPT_S    stOption;
}DHCPV6_MSG_S;

/* ������Ϣ��Я����option���� */
typedef struct tagDHCPV6S_OPTION_INFO_S
{
    DHCPV6_OPT_S *pstCiOption;
    ULONG ulOptionFlag;
    ULONG ulOROFlag;
    ULONG ulPdExcludeFlg;
}DHCPV6S_OPTION_INFO_S;

/* DHCPV6��Ϣ */
typedef struct tagDHCPV6S_MSG_INFO_S
{
    UCHAR *pucMsg;          /* ��Ϣ��ָ�� */
    ULONG ulMsgLen;        /* ��Ϣ���� */
    ULONG ulPdpIndex;
    in6_addr stSrcAddr;    /* Դ��ַ */
    in6_addr stDstAddr;    /* Ŀ�ĵ�ַ */
    USHORT usSrcPort;      /* Դ�˿� */
    USHORT usDstPort;      /* Ŀ�Ķ˿� */
    UCHAR ucMsgType;
    UCHAR ucReqDnsFlg;
    UCHAR ucReqPdFlg;
    UCHAR ucReqRapidFlg;
    DHCPV6S_OPTION_INFO_S stDhcpOptionInfo;  /* ��Ϣ��չͷ��Ϣ */
} DHCPV6S_MSG_INFO_S;

#pragma pack()

/* dhcpv6 msg statistics */
typedef struct tagDhcpv6Stat {
    ULONG ulTotal;                   /* �ܱ����� */
    ULONG ulLenErr;                 /* ���ȴ������� */
    ULONG ulHopLimitErr;         /* ������������ */
    ULONG ulNextHeadErr;       /* ͷ���ʹ������� */
    ULONG ulCheckSumErr;      /* У��ʹ������� */
    ULONG ulDestPortErr;         /* Ŀ�Ķ˿ڴ������� */
    ULONG ulUnsupportMsgErr; /* ��֧�ֱ������ʹ������� */
    ULONG ulUnknownMsgErr;   /* ������������ */
    ULONG ulOptionLenErr;         /* ѡ��ȴ������� */
    ULONG ulOptionLenOddErr;   /* ѡ���Ϊ������������ */
    ULONG ulUnknownOptErr;      /* ����ѡ�����ͱ����� */
    ULONG ulInfoReqWithIAErr;  /* ��Ϣ��ѯ��Ϣ����IA�ı����� */
    ULONG ulRelayStateInfoNum; /*RELAY״̬���յ�INFO��Ϣ�ļ���*/
    ULONG ulRelayStateReplyNum;/*RELAY״̬���յ�REPLY��Ϣ�ļ���*/
}DHCPV6_STAT_S;

typedef struct tagDhcpv6_Anaalyzedpacket
{
    UCHAR aucDhcpv6ClientID[20];
    UCHAR aucDhcpv6ServerID[20];
}VOS_PACKED DHCPV6_ANALYZEDPACKET_S;

/********************************************************************************/
/******************                  �ⲿ��������                 *******************/
/********************************************************************************/
extern USHORT ICMPv6_CheckSum(UCHAR *ptr, const in6_addr src, const in6_addr des, const UCHAR *msg, USHORT usLen, USHORT *pusCheckSum, UCHAR ucPro);
extern ULONG UGW_GRE_Encap(PMBUF_S *pMbuf, ULONG ulPdpIndex);
extern ULONG UGW_GtpEncap( PMBUF_S *pMbuf, ULONG ulPdpIndex );
extern VOID LAP_SetPrefixLengthIp(ULONG aulOldIp[], UCHAR ucPrefixLength, ULONG aulNewIp[],
                            UCHAR *pucPos, UCHAR *pucMoveBitNum);
extern VOID Path_GetVpn(SDB_GSPU_CONTEXT_S * pstContext, ULONG * ulVpnId);

/********************************************************************************/
/******************         �ṩ�������ļ�ʹ�õĺ�������      *******************/
/********************************************************************************/
extern ULONG DHCPV6_MsgProc(PMBUF_S *pstMsgBuf);

#ifdef   __WIN32_PLATFORM__
#pragma pack(pop)
#endif

#endif /* end of __DHCPV6_PROC_H__ */
