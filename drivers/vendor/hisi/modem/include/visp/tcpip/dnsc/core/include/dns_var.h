/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dns_var.h
*
*  Project Code: VISP1.5
*   Module Name: DNSC Module  
*  Date Created: 2002-11-25
*        Author: yanghua/sunyanfeng/songweiwei
*   Description: Define global variable of DNS 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-11-25  Sun Yanfeng(32084)         Creat the first version.
*
*******************************************************************************/

#ifndef _DNS_VAR_H_
#define _DNS_VAR_H_

/*In case of the C++.*/
#ifdef  __cplusplus
extern "C" {
#endif

/***************yanghua  added************************/

/* ��̬��������ȫ�ֿ��� */
extern ULONG g_ulDomaincLookupEnable;

/*DNS server info for new dns framework*/
extern DNSC_Serv_Info_S g_stDomainServer[DNS_DOMAIN_SERVER_NUM];

/* Ĭ�������б� */
extern CHAR g_szDomaincList[DNS_DOMAIN_LIST_NUM][DNS_DOMAIN_LIST_NAME_LENGTH + 1];


extern struct DNS_Total_Cache   g_stDNSC_Cache; /* DNS Cache */
extern USHORT g_usDNSC_ResID[MAXTASK];     /* ����ʹ��DNS�������� */
extern LONG   g_lDNSC_SocketID[MAXTASK];     /* socket used for communications */
extern ULONG  g_ulDNSC_Connected[MAXTASK];   /* is the socket connected */
extern LONG g_lDNSC_Socket6ID[MAXTASK];      /* socket for ipv6 communication*/
extern DNS_Res_State_S  *g_stDNSC_Res[MAXTASK]; /* ÿ�������µ�DNS��Ϣ�� */
extern struct hostentdns *dnsc_host[MAXTASK];
extern CHAR *dnsc_hostbuf[MAXTASK];
extern ULONG  g_ulDNSC_Timer;  /* �����Ķ�ʱ����ID */ 
extern ULONG  g_ulDNSCUserID;  /* �û�����ID */ 
    

/***************end of sunyanfeng added************************/
/* ���ĳ������DNS��صĴ����� */
extern LONG errnodnsc[MAXTASK];

extern ULONG g_ulDomaincDebugFlag;

/* dnsģ��ȫ��tosֵ */
extern UCHAR  g_ucDnsTos;

/*==========================================================================*/
/*                           End of Standard Tail                           */
/*==========================================================================*/

/*In case of the C++.*/
#ifdef  __cplusplus
}
#endif
#endif

