/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : raw_ip6_type.h
  Version       : Initial Draft
  Author        : Mayun
  Project Code  : VRP3.0
  Created       : 2002/8/20
  Last Modified :
  Description   : Raw IP6 definitions
  Function List :

  History       :
  1.Date        : 2002/8/20
    Author      : Mayun
    Modification: Created file

******************************************************************************/

#ifndef _RAW_IP6_TYPE_H_
#define _RAW_IP6_TYPE_H_


#ifdef  __cplusplus
extern "C"{
#endif

#define    RIPV6SNDQ    8192
#define    RIPV6RCVQ    8192


#define IP6_RIP6_SOCK_SET_PARAM  (g_pfRIP6SocketAPI->pfIP6_Socket_SetParameter)
#define IP6_RIP6_SOCK_GET_PARAM  (g_pfRIP6SocketAPI->pfIP6_Socket_GetParameter)

#if (RAWIP6_VRP_MODULE_IPV6_VPN == VRP_YES)
/* KLSRINI : Added for supporting SOCKIP interface change */
#define IP6_RIP6_SOCKET_GET_EXTOPTS(ulSocket, pulExtOpts) \
    IP6_RIP6_SOCK_GET_PARAM((ulSocket), IP6_SOCKET_EXTOPTIONS, (pulExtOpts))
#endif

#define  RIP6_ASYNRECALL  (g_pfRIP6SocketAPI->pfSO6_AsynReCall)
#define  RIP6_SOWAKEUP  (g_pfRIP6SocketAPI->pfSo6WakeUp)
#define  RIP6_ASYNWAKEUP  (g_pfRIP6SocketAPI->pfSO6_AsynWakeUp)
#define  RIP6_SB_APPENDADDR  (g_pfRIP6SocketAPI->pfSB6_AppendAddr)
#define  RIP6_SOCANTSENDMORE  (g_pfRIP6SocketAPI->pfSO6_CantSendMore)
#define  RIP6_SOISCONNECTED  (g_pfRIP6SocketAPI->pfSO6_IsConnected)
#define  RIP6_SOISDISCONNECTED  (g_pfRIP6SocketAPI->pfSO6_IsDisconnected)
#define  RIP6_SO_RESERVE  (g_pfRIP6SocketAPI->pfSO6_Reserve)

/* For VISP LOG Framework */
#define IP6_NULL_LOGID     0
#define IP6_NULL_PARA      0

/* Begin: Add by wan for RawIP6 performance, 2006-11-05; It is valid only for
VISP; IPOS it is defined as nothing for compilation purpose */
#define RIP6_SRCCACHE_SEARCH  (g_pfRIP6SocketAPI->pfHeadCache6_LookUpSrcAddr)

/*End of Add by wan for RawIP6 performance*/


#define IP6_RIP6_IN6PCB_SET_PARAM   \
                        g_pfRIP6In6PCBCallBack->pfIP6_IN6PCB_SetParameter
#define IP6_RIP6_IN6PCB_GET_PARAM   \
                        g_pfRIP6In6PCBCallBack->pfIP6_IN6PCB_GetParameter

/*yinyuanbin add for ARM CPU TEST 2006-08-01*/
/* Modified by Guru, since this is not the proper macro to be used
#if ((CPU_FAMILY == MIPS)||(ARM_SUPPORT == VRP_YES))  */
#if (ARM_SUPPORT == VRP_YES)
#define RIP6_CHECK_MEMORYADDRESS(pstPointer)   \
{\
    if (0 != ((UINTPTR)pstPointer % 4))\
    {\
        VOS_DBGASSERT(0);\
    }\
}
#else
#define RIP6_CHECK_MEMORYADDRESS(pstPointer)
#endif

#define RIP6_SOCKBUFTYPE_RCV   2
#define RIP6_SOCKBUFTYPE_SND   1

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _RAW_IP6_TYPE_H_ */

