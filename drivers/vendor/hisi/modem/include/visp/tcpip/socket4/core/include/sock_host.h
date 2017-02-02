/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_host.h
*
*  Project Code: VISPV100R007
*   Module Name: socket
*  Date Created: 2008-04-11
*        Author: zhoutong(43740)
*   Description: ���������sock_pub.h�и�����һ�ݣ�������sock_api.c��sock6_api.h����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2008-04-11   zhoutong(43740)         Create
*
*******************************************************************************/

#ifndef _SOCK_HOST_H_
#define _SOCK_HOST_H_

#ifdef __cplusplus
extern "C"{
#endif

#define IP_HOSTNAME_LEN    254                  /* Modify by tianli29125, 2005/1/8, BYDD11168 */
#define HostNameLen        (IP_HOSTNAME_LEN+1)

typedef struct tagSOCKHOST
{
    CHAR  HostName[HostNameLen];
    UCHAR ucPadding_1[4-((HostNameLen)%4)];
    CHAR  HostIP[MAXHOSTADDRNO][IPADDRMAXLEN];
    UCHAR ucPadding_2[4-(((MAXHOSTADDRNO)*(IPADDRMAXLEN))%4)];
    LONG  AddrNo;
    ULONG ulAge;
    CHAR  Flags;
    CHAR  type;
    UCHAR ucPadding_3[2];
}SOCKHOST_S;

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */

#endif

