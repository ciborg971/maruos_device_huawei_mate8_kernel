/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_def.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: DHCP6Rģ��ĺ��ö�ٶ���
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME                DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-19     PBQ(RT24429)        Create the first version.
*
*******************************************************************************/

#ifndef _DHCP6R_DEF_H_
#define _DHCP6R_DEF_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* ʹ������ģʽ: 0 - �ӿ�ģʽ��1 - ȫ��ģʽ */
#define DHCP6R_ENABLE_INTERFACE     0
#define DHCP6R_ENABLE_GLOBAL        1

/* �ӿڼ������ */
#define DHCP6R_CHECKTYPE_INIF       0   /* 0 ʹ�ܽӿڼ��,֧�ֽӿ�������eth/ppp/mp*/
#define DHCP6R_CHECKTYPE_OUTIF      1   /* 1 ���ӿڼ��,֧�ֽӿ�������eth/ppp/mp/trunk/vlanif*/

/* Relay6�����˿ں� */
#define DHCP6R_LISTEN_PORT          547
/* Relay6Ŀ�Ķ˿ں� */
#define DHCP6R_SERVER_PORT          547
#define DHCP6R_CLIENT_PORT          546

/* ��ַ�궨�� */
#define IN6ADDR_UNSPECIFIED         "::"
#define IN6ADDR_All_AGENTS_SERVERS  "ff02::1:2"

/* ����м��������� */
#define DHCP6R_HOPS_MAX             255

/* �ಥĿ�ĵ�ַ�м�hop limit */
#define DHCP6R_IPV6MULTI_HOPLIMIT   32

/*�ӿ�������󳤶�*/
#define IFNAME_MAX_LEN              128

/* ���ӿ��� */
#define DHCP6R_INDEX_MAX            9999

/* ipv6��ַ�ĳ��� */
#define IPV6_ADDR_LEN               16

/* �洢ipv6��ַ�ַ�������󳤶� */
#define DHCP6R_IPV6_ADDR_STR_MAX_LEN       46

/* Relay forward ����ͷ���ĳ��� */
#define RELAY_FORWARD_HEAD_LEN      34
 
 /* ѡ��ͷ���ĳ��� */
#define OPT_HEAD_LEN                4

#define DHCP6R_HEAD_MIN_LEN         4

#define DHCP6C_HEAD_LEN             4

#define DHCP6R_INTERFACEID_LEN      4

/* ѡ��ͷ���������ֶεĳ��� ��type �� len�ֶ� */
#define OPT_HEADFIELD_LEN           2

/* �ӿ������ĳ��� */
#define IFINDEX_LEN                 4

/* ����������Ϣ(ʹ������ģʽ�����hops,�м̷�ʽ)��Ĭ��ֵ */
#define DHCP6R_ENABLE_DEFAULT       DHCP6R_ENABLE_INTERFACE
#define DHCP6R_HOPS_DEFAULT         32
#define DHCP6R_FORWORD_DEFAULT      DHCP6R_FORWORD_CYCLE

/* relay���շ��ͱ��Ļ��������� */
#define DHCP6R_UDPBUF_MAXLEN        16384

/* ��ӡDHCP���ĳ��� */
#define DHCP6R_PRINT_LEN_MIN        34
#define DHCP6R_PRINT_LEN_DEFAULT    128
#define DHCP6R_PRINT_LEN_MAX        16384

#define DHCP6R_DBG_CHK_PAKCET       0x1     /* ���Ա��ĵ��Կ��ؼ��ֵ */
#define DHCP6R_DBG_CHK_ERROR        0x2     /* ������Կ��ؼ��ֵ */
#define DHCP6R_DBG_CHK_DETAIL       0x4     /* ��ϸ���ĵ��Կ��ؼ��ֵ */

#define DHCP6R_FLAG_SET             0x1     /* ���ñ�ʶ */
#define DHCP6R_FLAG_UNSET           0x0     /* �����ñ�ʶ */

/* DHCP6Rģ���¼�λ */
/* ������Ϣʹ��ͬһ��������Ϣ���к���ͬ�¼�����ͨ����ͬ����Ϣ����������  */
#define DHCP6R_EV_CNTRL             0x1     /* ����ģ��֪ͨDHCP6R�¼�   */

#define DHCP6R_MSG_CRTSKT           0x2     /* ����relay socket��Ϣ     */

/* ��Ч������ֵ */
#define DHCP6R_INVALID_INDEX        0xffffffff

/**********************************************************\ 
 * �û����ýӿ��д���Ľӿ�����ֵ�ڵ�ǰ����ģʽ���Ƿ���Ч *
 * �ӿ�����ģʽ(0),�ӿ��������� ��0                       *
 * ȫ������ģʽ(1),�ӿ��������� Ϊ0                       *
 * ��ֵΪ1��ʾ��������������ģʽ��ͻ                      *
\**********************************************************/
#define DHCP6R_MODE_NO_MATCH(ulMode, ulIfIndex) (((!(ulMode))&&(!(ulIfIndex))) || ((ulMode)&&(ulIfIndex)))

/************************************************************************
                  DHCP6R ADDR module defination
                  
 ���µ�ַ�����жϺ�ʹ��˵��:
 pAddress������һ��IPv6��ַ�ṹָ�룬����ṹ�е�����Ԫ����4�ֽڣ�ULONG����
 ����ֵ: 
      1 -- pAddress ��ַ�����������ͬ
      0 -- pAddress ��ַ�����������ͬ
*************************************************************************/
/* �жϵ�ַ�Ƿ�Ϊ"::" */
#define DHCP6R_IS_ADDR_UNSPECIFIED( pAddress ) \
        ((0 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (0 == ((pAddress)->s6_addr32[3])))
            
/* �жϵ�ַ�Ƿ���ͬ�ĺ� */
#define DHCP6R_ARE_ADDR_EQUAL(pDstAddr,pSrcAddr) \
        (((pDstAddr)->s6_addr32[0] == (pSrcAddr)->s6_addr32[0]) \
         && ((pDstAddr)->s6_addr32[1] == (pSrcAddr)->s6_addr32[1]) \
         && ((pDstAddr)->s6_addr32[2] == (pSrcAddr)->s6_addr32[2]) \
         && ((pDstAddr)->s6_addr32[3] == (pSrcAddr)->s6_addr32[3]))

/* ���ص�ַ�жϺ� */
#define DHCP6R_IS_ADDR_LOOPBACK( pAddress ) \
        ((0 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (1 == ((pAddress)->s6_addr32[3])))

/* ��·���ص�ַ�жϺ� */
#define DHCP6R_IS_ADDR_LINKLOCAL( pAddress ) \
        (0xFE800000 == (0xFFC00000&((pAddress)->s6_addr32[0])))

/* վ�㱾�ص�ַ�жϺ� */
#define DHCP6R_IS_ADDR_SITELOCAL( pAddress ) \
        (0xFEC00000 == (0xFFC00000&((pAddress)->s6_addr32[0])))

/* �鲥��ַ�жϺ� */
#define DHCP6R_IS_ADDR_MULTICAST( pAddress ) \
        (0xFF000000 == (0xFF000000&((pAddress)->s6_addr32[0])))
        
#define DHCP6R_IS_ADDR_LINKLOCAL_MULTICAST( pAddress )    \
        (0xFF020000 == (0xFFFF0000&((pAddress)->s6_addr32[0])))

/* All_DHCP_Relay_Agents_and_Servers��ַ�жϺ� */
#define DHCP6R_IS_ADDR_ALL_DHCP_RELAYS( pAddress ) \
        ((0xFF020000 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (0x00010002 == ((pAddress)->s6_addr32[3])))

/* All_DHCP_Servers��ַ�жϺ� */
#define DHCP6R_IS_ADDR_ALL_DHCP_SERVERS( pAddress ) \
        ((0xFF050000 == ((pAddress)->s6_addr32[0])) \
         && (0 == ((pAddress)->s6_addr32[1])) \
         && (0 == ((pAddress)->s6_addr32[2])) \
         && (0x00010003 == ((pAddress)->s6_addr32[3])))

/* ȫ�򵥲���ַ�жϺ� */
#define DHCP6R_IS_ADDR_GLOBAL( pAddress ) \
        (!((DHCP6R_IS_ADDR_MULTICAST(pAddress)) \
            ||(DHCP6R_IS_ADDR_LOOPBACK(pAddress)) \
            ||(DHCP6R_IS_ADDR_LINKLOCAL(pAddress)) \
            ||(DHCP6R_IS_ADDR_UNSPECIFIED(pAddress))))

/* IPV6��ַ������ */
#define DHCP6R_IPV6_ADDRESS_COPY( pDest, pSrc ) \
{\
    (pDest)->s6_addr32[0] = (pSrc)->s6_addr32[0];\
    (pDest)->s6_addr32[1] = (pSrc)->s6_addr32[1];\
    (pDest)->s6_addr32[2] = (pSrc)->s6_addr32[2];\
    (pDest)->s6_addr32[3] = (pSrc)->s6_addr32[3];\
}

/* IPv6��ַ�ֽ���ת���� */
#define DHCP6R_ADDRESS_NTOH(pAddress) \
{\
    (pAddress)->s6_addr32[0] = VOS_NTOHL((pAddress)->s6_addr32[0]);\
    (pAddress)->s6_addr32[1] = VOS_NTOHL((pAddress)->s6_addr32[1]);\
    (pAddress)->s6_addr32[2] = VOS_NTOHL((pAddress)->s6_addr32[2]);\
    (pAddress)->s6_addr32[3] = VOS_NTOHL((pAddress)->s6_addr32[3]);\
}
     
/* IPv6��ַ�ֽ���ת���� */
#define DHCP6R_ADDRESS_HTON(pAddress) \
{\
    (pAddress)->s6_addr32[0] = VOS_HTONL((pAddress)->s6_addr32[0]);\
    (pAddress)->s6_addr32[1] = VOS_HTONL((pAddress)->s6_addr32[1]);\
    (pAddress)->s6_addr32[2] = VOS_HTONL((pAddress)->s6_addr32[2]);\
    (pAddress)->s6_addr32[3] = VOS_HTONL((pAddress)->s6_addr32[3]);\
}

/*************************************************************************
                END DHCP6R ADDR module defination
*************************************************************************/

/* DHCPv6���ݱ������� */
enum enDHCP6R_MsgType
{
    DHCP6R_MSG_SOLICIT = 1,             /* 1  Solicit */
    DHCP6R_MSG_ADVERTISE,               /* 2  Advertise */
    DHCP6R_MSG_REQUEST,                 /* 3  Request */
    DHCP6R_MSG_CONFIRM,                 /* 4  Confirm */
    DHCP6R_MSG_RENEW,                   /* 5  Renew */
    DHCP6R_MSG_REBIND,                  /* 6  Rebind */
    DHCP6R_MSG_REPLY,                   /* 7  Reply */
    DHCP6R_MSG_RELEASE,                 /* 8  Release */
    DHCP6R_MSG_DECLINE,                 /* 9  Decline */
    DHCP6R_MSG_RECONFIGURE,             /* 10 Reconfigure */
    DHCP6R_MSG_INFORMATION_REQUEST,     /* 11 Information-Request */
    DHCP6R_MSG_RELAY_FORW,              /* 12 Relay-Forward */
    DHCP6R_MSG_RELAY_REPL,              /* 13 Relay-Reply */
    DHCP6R_MSG_MAX,
};

/* ����Ƿ�dhcp��Ϣ���ͺ� */
#define DHCP6R_BAD_MSG    0

/* ѡ�������*/
enum enDHCP6R_OPTTYPE
{
    DHCP6C_DUID               = 1,      /* DUID */
    DHCP6R_RELAY_MESSAGE      = 9,      /* Relay message */
    DHCP6R_INTERFACEID        = 18,     /* interfaceID */
};

/* ����dhcp���������� */
enum enDHCP6RTxRx
{
    DHCP6R_FROM_CLIENT        = 0,      /* 0 ��client���� */
    DHCP6R_TO_CLIENT,                   /* 1 ��client���� */
    DHCP6R_FROM_SERVER,                 /* 2 ��server���� */
    DHCP6R_TO_SERVER,                   /* 3 ��server���� */
    DHCP6R_TXRX_UNKNOWN,                /* 4 ���ķ���δ֪ */
};

/* DHCP6Rģ��ʹ�õ�SIDͳһ�ڴ˶��� */
#define SID_COMP_DHCP6R_DLL_S   1       /* DLL_S */
#define SID_COMP_DHCP6R_CFG_S   2       /* DHCP6R_CFG_NODE_S */
#define SID_COMP_DHCP6R_DBG_S   3       /* DHCP6R_DEBUG_NODE_S */

/* ���Դ�����Ϣ��ӡ�ļ����ͳ��������궨�� */
#define DHCP6R_DEBUGERROR(szErrInfo) \
{ \
    CHAR  szCurrentFileName[FILENAME_LEN] = {0}; \
    TCPIP_GetFileName(__FILE__, szCurrentFileName, FILENAME_LEN); \
    (VOID)DHCP6R_DebugErrorCheck(szCurrentFileName, __LINE__, szErrInfo); \
}

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif    /* end of _DHCP6R_DEF_H_ */

