/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_def.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: 1�����ͷ�ļ���DNSģ��Ķ���ȫ�ֺ��ͷ�ļ�
*                2��DNSģ���C�ļ���Ҫ������ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/

#ifndef _DNS_DEF_H_
#define _DNS_DEF_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif

#define DNS_DEFAULT_USERID   0Xffffffff

#define MAXDNSRCH       6   /* max # domains in search path */
#define DNS_MAXRESOLVSORT   10  /* number of net to sort on */
#define DNS_RES_TIMEOUT     5   /* min. seconds between retries, for function select() */
#define DNS_RES_RETRY       2   /* number of send retry time */

#define RES_INIT        0x00000001  /* ��ַ��ʼ�� *************************************************/
#define RES_DEBUG       0x00000002  /* ��ӡ������Ϣ ***********************************************/
#define RES_AAONLY      0x00000004  /* ǿ�ƻش�    authoritative answers only (!IMPL)**************/
#define RES_USEVC       0x00000008  /* ʹ�����· *************************************************/
#define RES_PRIMARY     0x00000010  /* ��ѯ��������  query primary server only (!IMPL) ************/
#define RES_IGNTC       0x00000020  /* ����ֹͣ����  ignore trucation errors **********************/
#define RES_RECURSE     0x00000040  /* ��Ҫ�ݹ�      recursion desired ****************************/
#define RES_DEFNAMES    0x00000080  /* ʹ��ȱʡ����  **********************************************/
#define RES_STAYOPEN    0x00000100  /* ����TCP�׽��ֿ��� ******************************************/
#define RES_DNSRCH      0x00000200  /* �������������� *********************************************/
#define RES_INSECURE1   0x00000400  /* ��������1��ȫ **********************************************/
#define RES_INSECURE2   0x00000800  /* ��������2��ȫ **********************************************/
#define RES_NOALIASES   0x00001000  /* �ر�HOSTALIASES���� ****************************************/
#define RES_USE_INET6   0x00002000  /* ʹ��map IPv6  **********************************************/

#define RES_DEFAULT     (RES_RECURSE | RES_DEFNAMES | RES_DNSRCH)
#define MAXADDRS                4
#define DNS_TIME_TIMOUT      3      /*dns time out */

/*Byte order commented by Suraj 04- Sept 2003 to take the byte order from platform.*/
/*#define BYTE_ORDER  _BIG_ENDIAN*/

/* ��Դ�Ͳ�ѯ������ֵ */
#define T_A         1        /* ������ַ   ********************************************************/
#define T_NS        2        /* ��Ȩ������ ********************************************************/
#define T_MD        3        /* �ʼ���ַ   ********************************************************/
#define T_MF        4        /* �ʼ�ת����  *******************************************************/
#define T_CNAME     5        /* �淶������  *******************************************************/
#define T_SOA       6        /* ��Ȩ�����ʼ ******************************************************/
#define T_MB        7        /* ��������   ********************************************************/
#define T_MG        8        /* �ʼ���Ա   ********************************************************/
#define T_MR        9        /* �ʼ������� ********************************************************/
#define T_NULL      10       /* NULL��Դ��¼  *****************************************************/
#define T_WKS       11       /* ֪������   ********************************************************/
#define T_PTR       12       /* ����ָ��  *********************************************************/
#define T_HINFO     13       /* ������Ϣ  *********************************************************/
#define T_MINFO     14       /* ������Ϣ   ********************************************************/
#define T_MX        15       /* �ʼ�·����Ϣ ******************************************************/
#define T_TXT       16       /* �ı��ַ���*********************************************************/
#define T_RP        17       /* ������    *********************************************************/
#define T_AFSDB     18       /* AFSԪ���ݿ� *******************************************************/
#define T_X25       19       /* X_25���е�ַ  *****************************************************/
#define T_ISDN      20       /* ISDN���е�ַ  *****************************************************/
#define T_RT        21       /* ·����   **********************************************************/
#define T_NSAP      22       /* NSAP��ַ **********************************************************/
#define T_NSAP_PTR  23      /* ����NSAP��ѯ (���Ƽ�) **********************************************/
#define T_SIG       24      /* ��ȫǩ��    ********************************************************/
#define T_KEY       25      /* ��ȫ��   ***********************************************************/
#define T_PX        26      /* X.400�ʼ�ӳ�� ******************************************************/
#define T_GPOS      27      /* ����λ��   *********************************************************/
#define T_AAAA      28      /* IP6��ַ    *********************************************************/
#define T_LOC       29      /* ��ַ��Ϣ  **********************************************************/
#define T_NXT       30      /* �����ڵ���һ���Ϸ�����  ********************************************/
#define T_EID       31      /* �˵��ʶ     *******************************************************/
#define T_NIMLOC    32      /* NImrod��λ��   *****************************************************/
#define T_SRV       33      /* ������ѡ��   *******************************************************/
#define T_ATMA      34      /* ATM��ַ    *********************************************************/
#define T_NAPTR     35      /* ������Ȩָ�� *******************************************************/
/* �Ǳ�׼  */
#define T_UINFO     100     /* �û�(��ָ)��Ϣ  ****************************************************/
#define T_UID       101     /* �û�ID  ************************************************************/
#define T_GID       102     /* ��ID    ************************************************************/
#define T_UNSPEC    103     /* Ϊָ����ʽ(����������) **********************************************/
/* ����������Դ��¼�еĲ�ѯ����ֵ   */
#define T_IXFR      251     /* ��������  ********************************************************/
#define T_AXFR      252     /* ������Ȩ��  ********************************************************/
#define T_MAILB     253     /* ���������¼ *******************************************************/
#define T_MAILA     254     /* �����ʼ������¼ ***************************************************/
#define T_ANY       255     /* ͨ���ƥ�� *********************************************************/

/*#if BYTE_ORDER == _LITTLE_ENDIAN*/
/* Changed by Suraj to make compatible for the VRP platform.*/
#if (VRP_YES == VRP_LITTLE_ENDIAN )
    #define HTONS(a)        (USHORT) ((((USHORT)(a) & 0x00FF)<<8)  | \
                             (((USHORT)(a) & 0xFF00)>>8))

    #define NTOHS(a)        HTONS(a)
#else
    #define HTONS(a)        a
    #define NTOHS(a)        a
#endif

#define TRY_AGAIN       11002


#define MAXPACKET   1024
#define INT16SZ     2       /* for systems without 16-bit ints */
#define INT32SZ     4       /* for systems without 32-bit ints */

#define DNSC_NON_BLOCKING 1

/*****************end of sunyanfeng added******************/
#define HOST_NOT_FOUND   11001
#define NO_DATA          11004
#define MAXTASK             15
#define DNSFREE              0  /*for multi-task environment*/
#define DNSBUSY              1

typedef unsigned int        u_int;

#define PERIOD 0x2e
#define hyphenchar(c) ((c) == 0x2d)
#define periodchar(c) ((c) == PERIOD)

/* Begin: Added for DNSC '_' requirement by r84019196 */
#define underscorechar(c) ((c) == 0x5f)
/* End: Added for DNSC '_' requirement by r84019196 */

#define alphachar(c) (((c) >= 0x41 && (c) <= 0x5a) \
           || ((c) >= 0x61 && (c) <= 0x7a))
#define digitchar(c) ((c) >= 0x30 && (c) <= 0x39)
#define borderchar(c) (alphachar(c) || digitchar(c))
#define middlechar(c) (borderchar(c) || hyphenchar(c))

/* Define constants based on rfc883*/
#define MAXLABEL    63      /* maximum length of domain label */
#define MAXDNAME    255     /* maximum presentation domain name */
#define HFIXEDSZ    12      /* #/bytes of fixed data in header */
#define QFIXEDSZ    4       /* #/bytes of fixed data in query */
#define INADDRSZ    4       /* IPv4 T_A */
#define RRFIXEDSZ   10      /* #/bytes of fixed data in r record */


/* Values for IPv6*/
#define IN6ADDRSZ    16       /* IPv6 T_AAAA */

/* Values for class field */
#define C_IN        1       /* the arpa internet */
#define C_CHAOS     3       /* for chaos net (MIT) */
#define C_HS        4       /* for Hesiod name server (MIT) (XXX) */
/* Query class values which do not appear in resource records */
#define C_ANY       255     /* wildcard match */

/* Currently defined opcodes */
#define QUERY           0x0     /* standard query */
#define NS_NOTIFY_OP    0x4     /* notify secondary of SOA change */

/* Currently defined response codes */
#define NOERROR     0       /* no error */
#define FORMERR     1       /* format error */
#define SERVFAIL    2       /* server failure */
#define NXDOMAIN    3       /* non existent domain */
#define NOTIMP      4       /* not implemented */
#define REFUSED     5       /* query refused */

/* Internet nameserver port number*/
#define NAMESERVER_PORT 53

/* Defines for handling compressed domain names */
#define INDIR_MASK  0xc0

/* Inline versions of get/put short/long.  Pointer is advanced.

 * These macros demonstrate the property of C whereby it can be
 * portable or it can be elegant but rarely both.
 */
#define GETSHORT(s, cp) { \
    UCHAR *t_cp = (UCHAR *)(cp); \
    (s) = (USHORT)( ((USHORT)t_cp[0] << 8) \
        | ((USHORT)t_cp[1]) )\
        ; \
    (cp) += INT16SZ; \
}

#define GETLONG(l, cp) { \
    UCHAR *t_cp = (UCHAR *)(cp); \
    (l) = ((ULONG)t_cp[0] << 24) \
        | ((ULONG)t_cp[1] << 16) \
        | ((ULONG)t_cp[2] << 8) \
        | ((ULONG)t_cp[3]) \
        ; \
    (cp) += INT32SZ; \
}

#define PUTSHORT(s, cp) { \
    USHORT t_s = (USHORT)(s); \
    UCHAR *t_cp = (UCHAR *)(cp); \
    *t_cp++ = (UCHAR)(t_s >> 8); \
    *t_cp   = (UCHAR)t_s; \
    (cp) += INT16SZ; \
}

#define PUTLONG(l, cp) { \
    ULONG t_l = (ULONG)(l); \
    UCHAR *t_cp = (UCHAR *)(cp); \
    *t_cp++ = (UCHAR)(t_l >> 24); \
    *t_cp++ = (UCHAR)(t_l >> 16); \
    *t_cp++ = (UCHAR)(t_l >> 8); \
    *t_cp   = (UCHAR)t_l; \
    (cp) += INT32SZ; \
}


#define NETDB_INTERNAL  -1  /* see errno */
#define NETDB_SUCCESS   0   /* no problem */
#define NO_RECOVERY 3 /* Non recoverable errors, FORMERR, REFUSED, NOTIMP */

/*
 * Global defines and variables for resolver stub.
 */
#define MAXNS           6   /* max # name servers we'll track */

/* change this to "0"
 * if you talk to a lot
 * of multi-homed SunOS
 * ("broken") name servers.
 */
#define CHECK_SRVR_ADDR  1  /* XXX - should be in options.h */


#define NFDBITS       0x20

#define CAN_RECONNECT 1

#define DNS_INVALID_IFINDEX 0    /*invalid interface index.*/
#define DNS_MAX_IFINDEX_NUM 20   /*Max Length of Interface index string defect 3595*/

/* DNSCģ��ʹ�õ�SIDͳһ�ڴ˶��� */

#define SID_COMP_DNSC_HOST_S              1  /* struct hostent */
#define SID_COMP_DNSC_CACHE_ENTRY_S       2  /* DNS_CACHE_S */
#define SID_COMP_DNSC_UDP_BUFFER_S        3  /* DNS response buffer over UDP*/
#define SID_COMP_DNSC_TCP_BUFFER_S        4  /* DNS response buffer over TCP*/
#define SID_COMP_DNSC_TCP6_BUFFER_S       5  /* DNS response buffer over TCP ipv6*/

/* end of SID */

/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif

#endif

