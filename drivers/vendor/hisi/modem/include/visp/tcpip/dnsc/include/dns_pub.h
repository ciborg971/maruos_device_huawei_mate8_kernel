/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_pub.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: Sun Yanfeng(32084)
*   Description: ���ͷ�ļ�����VISP��DNSģ������ݽṹ  
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)   Creat the first version.
*  2006-05-10  lu yao(60000758)     Ϊ֧��ARM CPU�ֽڶ������ԣ��޸Ľṹ��
*
*******************************************************************************/

#ifndef _DNS_PUB_H_
#define _DNS_PUB_H_

#ifdef  __cplusplus
extern "C" {
#endif

/* add by yanghua on 2003/05/14 for d15270 */
#define DNS_HOSTBUF_LEN 8192
/* end add */

/* ������������CASHE��������*/
#define DNS_DOMAIN_CACHE_NUM    50

extern ULONG g_ulDnscExecInforIndex;


#define pDnsInfo Inf_Dnsc_En

/* check if user press Ctrl+C */
#define   TRRT_CTRL_C                      1
#define   TRRT_NO_BREAK                    0

typedef struct tagDnscOutString
{
   ULONG ulErrNo;   
   CHAR  szIPAddrBuf[50] ; 
   UCHAR ucPadding[2]; 
}DnscOutString;

typedef struct tagDNSCCallbackSet
{ 
    ULONG (*pfDNS_OutputResult)(ULONG ulExecID, DnscOutString *pstOutput);
    ULONG (*pfDNS_Isstop)(ULONG ulExecID);
}DNSC_CALLBACK_SET_S;

typedef  VOID (*tagDNS_SendICDebugInfo)(CHAR* szString );

typedef struct tagDnsComModuleInfo
{
    ULONG  ulModID;
    ULONG ulSubModID;    
}DNS_MOD_INFO_S;

typedef struct tagSetServer_S
{
    ULONG  ulNoFlag;           /* 0:��������������  ��0:ɾ������������ */
    ULONG  ulServerIpFlag ;    /* �Ƿ�ָ����������������ַ: ��ulNoFlag=1,�Ҵ˴�Ϊ������ɾ�����е����������� */
    ULONG  ulIpv6Flag;                     
    union
    {
        ULONG  ulServerIp;                        /* Ipv4��ַ */
        struct tagDns6
        {
            IN6ADDR_S stServerIp6;                /* Ipv6��ַ */
            CHAR szIfName[MAX_IF_NAME_LENGTH + 1];/* �ӿ��� */
        }Dns6;
    }Dns_Un;

#define Dns6_stServerIp6    Dns_Un.Dns6.stServerIp6
#define Dns6_szIfName       Dns_Un.Dns6.szIfName
#define Dns4_ulServerIp     Dns_Un.ulServerIp
}SetServer_S ;


/*************sunyanfeng added*************/
/* add from sock_pub.h */
typedef struct  DNS_CACHE 
{
    CHAR    szHostName[IP_HOSTNAME_LEN+ 1];         /* official name of host */ /* 10->21 by mayun 20010608 */
    UCHAR   ucPadding[4-((IP_HOSTNAME_LEN+ 1)%4)];
    CHAR    h_aliases[4][IP_HOSTNAME_LEN+1];        /* alias list */
    LONG    laddrtype;                              /* indicates the address type stored in szaddr*/
    CHAR    szAddr[20];                             /* list of addresses */
    struct  DNS_CACHE *pstPrev;     
    struct  DNS_CACHE *pstNext; 
    ULONG   ulTTL;          /*the number of the TTL,which mean what time should hold the list */        
}DNS_CACHE_S;              

typedef struct  DNS_Total_Cache 
{
    ULONG   ulTotalCacheNum;                               /* the number of the cache */
    struct  DNS_CACHE  *pstDNS_CaEntryHead;  
    struct  DNS_CACHE  *pstDNS_CaEntryTail;
}DNS_Total_Cache_S;

/*************end of sunyanfeng added*************/
typedef struct tagIPV6_DNS_SERVADDRINFO
{   
    IN6ADDR_S stIpAddr;
    ULONG     ulIfIndex;
    CHAR      szInterfaceName[DNS_MAX_INTERFACE_NAME_LEN + 1];   
}IPV6_DNS_SERVADDRINFO_S;

/*dns������Ϣ�ṹ*/
typedef struct  tagDomainInfo
{
     ULONG  ulDomainServer[DNS_DOMAIN_SERVER_NUM];
     IPV6_DNS_SERVADDRINFO_S stDomainServer6[DNS_DOMAIN_SERVER_NUM];
     CHAR   szDomainList[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH + 1];
     UCHAR  ucPadding[2]; 
}DomainInfo_S;

typedef struct DNSC_Serv_Info
{
UCHAR                   ucIPType;   /* ipv4 or ipv6 */ 
union {
    ULONG ulIP4Addr;
    IPV6_DNS_SERVADDRINFO_S stIP6ServInfo;
}servAddr;
} DNSC_Serv_Info_S;

#ifdef  __cplusplus
}
#endif

#endif

