/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_type.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: ����DNS����Ҫ���ݽṹ
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)   Creat the first version.
*  2006-05-10  lu yao(60000758)     Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
*
*******************************************************************************/

#ifndef _DNS_TYPE_H_
#define _DNS_TYPE_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif


/* New structure to maintain ipv4 and ipv6 server address */
typedef struct DNSC_Serv_IP
{
    UCHAR                   ucIPType;   /* ipv4 or ipv6 */
    union {
        struct sockaddr_in stAddr4;
        SOCKADDR_IN6_S      stAddr6;
    } serverIP;
} DNSC_Serv_IP_S;


typedef struct DNS_Res_State 
{
    LONG    retrans;        /* retransmition time interval */
    LONG    retry;          /* number of times to retransmit */
    ULONG   options;        /* option flags - see below. */

    LONG    nscount;        /* number of name servers */
    
    DNSC_Serv_IP_S      stServaddr_list[DNS_DOMAIN_SERVER_NUM]; /* address of name server */

    ULONG ulNsIfIndex[DNS_DOMAIN_SERVER_NUM];   /* store the interface index in case the ipv6 address is Link local.
                                                   Not used by other address types*/
    USHORT  id;         /* current message id */
    CHAR    dnsrch[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH+1]; /* components of domain to search */
    USHORT  usdnsrch_count;
    UCHAR   ucPadding_1[2]; 
    ULONG   pfcode;         /* RES_PRF_ flags - see below. */
    unsigned ndots:4;       /* threshold for initial abs. query */
    unsigned nsort:4;       /* number of elements in sort_list[] */
    CHAR    unused[2];
    struct {
            struct in_addr  addr;
            ULONG   mask;
    } sort_list[DNS_MAXRESOLVSORT];
    ULONG ulDNS_ExecId;
    ULONG ulUSER_CtrlFlag; 
}DNS_Res_State_S;


/* �������������ĸ�ʽ*/
typedef struct 
{
    unsigned    id :16;     /* query identification number */
/*#if BYTE_ORDER == _BIG_ENDIAN*/
#if (VRP_YES == VRP_BIG_ENDIAN )
    /* fields in third byte */
    unsigned    qr: 1;      /* response flag : Ϊ0--��ѯ��Ϊ1--��Ӧ*/
    unsigned    opcode: 4;  /* ��ѯ���� */
    unsigned    aa: 1;      /* authoritive answer ���ش�����Ȩ������λΪ1 */
    unsigned    tc: 1;      /* truncated message �����ı��ضϣ�����λΪ1*/
    unsigned    rd: 1;      /* recursion desired ����Ҫ�ݹ�����λΪ1*/
    /* fields in fourth byte */
    unsigned    ra: 1;      /* recursion available ���еݹ飬����λΪ1*/
    unsigned    unused :1;  /* unused bits (MBZ as of 4.9.3a3) */

    unsigned    ad: 1;      /* �������Ŀɿ�����  authentic data from named */
    unsigned    cd: 1;      /* ��Ч���  checking disabled by resolver */
    unsigned    rcode :4;   /* ��Ӧ����  response code 0��1��2��3��ͬ����*/
#else
    unsigned    rd :1;      /* �ݹ�ʽҪ��  recursion desired */
    unsigned    tc :1;      /* �ض���Ϣ  truncated message */
    unsigned    aa :1;      /* Ȩ���ش�  authoritive answer */
    unsigned    opcode :4;  /* ��ϢĿ��  purpose of message */
    unsigned    qr :1;      /* Ӧ���־  response flag */
    /* ���ֽ���  fields in fourth byte */
    unsigned    rcode :4;   /* Ӧ�����  response code */
    unsigned    cd: 1;      /* ��Ч�Լ��  checking disabled by resolver */
    unsigned    ad: 1;      /* �������Ŀɿ�����  authentic data from named */
    unsigned    unused :1;  /* δ�ñ���  unused bits (MBZ as of 4.9.3a3) */
    unsigned    ra :1;      /* �����õݹ�ʽ  recursion available */
#endif
    /* �����ֽ�  remaining bytes */
    unsigned    qdcount :16;    /* number of question entries ����������*/
    unsigned    ancount :16;    /* number of answer entries �ش���*/
    unsigned    nscount :16;    /* number of authority entries ���������*/
    unsigned    arcount :16;    /* number of resource entries ������Ϣ��*/
} HEADER;



typedef union 
{
    LONG  al;
    CHAR ac;
} align;


typedef struct  hostentdns  /*WXP MODIFIED ON 1997.12.16,it is different from "socket/inc/socket.h"*/
{
    CHAR    *h_name;            /* official name of host */
    CHAR    h_aliases[4][MAXDNAME]; /* alias list */
    short   h_addrtype;         /* host address type */
    short   h_length;           /* length of address */
    CHAR    h_addr_list[4][20]; /* list of addresses from name server */
#define h_addr  h_addr_list[0]  /* address, for backward compatiblity */
    ULONG  ulTTL[4];
}hostentdns_s;  

typedef struct  hostenthw 
{
    char    h_name[MAXDNAME];         /* official name of host */
    UCHAR   ucPadding;
    char    h_aliases[4][MAXDNAME];   /* alias list ���� */
    short   h_addrtype;               /* host address type */
    short   h_length;                 /* length of address */
    char    h_addr_list[4][20];       /* list of addresses */
#define h_addr  h_addr_list[0]        /* address, for backward compat */
    ULONG   ulTTL;                    /* the time can cache the entry */
}hostenthw_s;
/*In case of the C++.*/

#ifdef  __cplusplus
}
#endif
#endif


