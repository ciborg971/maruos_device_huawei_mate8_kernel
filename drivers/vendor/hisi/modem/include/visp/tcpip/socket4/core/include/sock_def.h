/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              sock_def.h
*
*  Project Code: VISP1.5
*   Module Name: socket4  
*  Date Created: 2006-11-14
*        Author: wangtao(60012929)
*   Description: the private macro
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-11-14   wangtao(60012929)       Create
*
*******************************************************************************/

#ifndef _SOCK_DEF_H
#define _SOCK_DEF_H

#ifdef    __cplusplus
extern    "C"{
#endif

/*****************************************************
* the macro fro socket, they are define in .c
*****************************************************/
#ifndef INADDR_NONE
#define  INADDR_NONE     0XFFFFFFFF    /* no address, used in tool.c */
#endif

/*****************************************************
* the macro fro tcp,udp, they are define in .c
*****************************************************/
/* used in TCPInput(), it is the second of 24 days */
#define TCP_PAWS_IDLE   (24 * 24 * 60 * 60 * PR_SLOWHZ)    
/* Comparisons of timestamps */
#define TSTMP_LT(a,b)   ((LONG)((a)-(b)) < 0)
#define TSTMP_GEQ(a,b)  ((LONG)((a)-(b)) >= 0)

/* 
 * ����tcp���������µ�ѡ��,ѡ����ܳ��ȿ��ܴﵽ40�ֽ�,
 * ��˶�����ַ��� ������32�޸�Ϊ41, TCP MD5 authentication, 
 * zhangfeng, 2002,07,20 
 */
#define MAX_TCPOPTLEN     /* 32 */ 41 /* max # bytes that go in options */

/* �ж��Ƿ�vrrp�Ķಥ��ַ��224.0.0.18 �����ֽ��� */
#define SOCK_IS_VRRPR_ADDR(MultiAddr)  (0xe0000012 == MultiAddr)   

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif

