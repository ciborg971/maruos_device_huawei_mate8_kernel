

#ifndef __OM_SOCKET_PPM_H__
#define __OM_SOCKET_PPM_H__

/*****************************************************************************
  1 其他头文件包含
*****************************************************************************/
#include "vos.h"
#include "omnvinterface.h"


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif

#pragma pack(4)

/*****************************************************************************
  2 宏定义
*****************************************************************************/

#define SOCKET_NUM_MAX          (1)                   /* OM、AT在各自的端口上只监听接收一个链接 */

#define SOCK_WIFI_ADDR_LEN      (16)                  /*WIFI网关的地址的最大长度*/

#define SOCK_WIFI_DEFAULT_ADDR  ("127.0.0.1")         /*WIFI通信的默认IP地址*/

#define SOCK_OM_IND_SRC_PORT_NUM    (20253)           /* OM IND源端口号，UDP */

#define SOCK_OM_CFG_SRC_PORT_NUM    (3000)            /* OM CFG源端口号，TCP */
#define SOCK_AT_SRC_PORT_NUM        (20249)           /* AT源端口号，TCP */


#define SOCK_OM_MSG_LEN             (1000)


#if  (VOS_LINUX == VOS_OS_VER)
#define SOCK_NULL               (-1)

#define INVALID_SOCKET  VOS_ERROR
#define SOCKET_ERROR    VOS_ERROR
#define closesocket(s)  shutdown(s, SHUT_RDWR)

#define IP_NULL         0
#define Ip_sockaddr     sockaddr
#define Ip_socklen_t    int
#define Ip_fd           int
#define Ip_fd_set       hi_fd_set
#define Ip_timeval      timeval

#define SOCK_FD_ISSET(d, set)     (HI_FD_ISSET(d, set))
#define SOCK_FD_SET(d, set)       (HI_FD_SET(d, set))
#define SOCK_FD_CLR(d, set)       (HI_FD_CLR(d, set))
#define SOCK_FD_ZERO(set)         (HI_FD_ZERO(set))

#define socket(domain,type,protocol)        hi_socket(domain, type, protocol)
#define shutdown(fd,how)                    do{\
                                                hi_shutdown((Ip_fd)fd, how);\
                                                hi_close((Ip_fd)fd);\
                                            }while(0)
#define bind(fd,addr,addrlen)               hi_bind((Ip_fd)fd, (struct Ip_sockaddr *)addr, (Ip_socklen_t)addrlen)
#define accept(fd,addr,addrlenp)            hi_accept((Ip_fd)fd, (struct Ip_sockaddr *)addr, (Ip_socklen_t *)addrlenp)
#define listen(fd,backlog)                  hi_listen((Ip_fd)fd, backlog)
#define select(nfds,rf,wf,ef,t)             hi_select(nfds, (Ip_fd_set *)rf, (Ip_fd_set *)wf, IP_NULL, t)
#define recv(fd,buf,len,flags)              hi_recv((Ip_fd)fd, (void *)buf, len, flags)
#define send(fd,msg,len,flags)              hi_send((Ip_fd)fd, (void *)msg, len, flags)
#define sendto(fd,msg,len,flags,addr,alen)  hi_sendto((Ip_fd)fd, (void *)msg, len, flags, (struct sockaddr *)addr, alen)
#define getpeername(fd,addr,addrlenp)       hi_getpeername((Ip_fd)fd, (struct Ip_sockaddr *)addr, (Ip_socklen_t *)addrlenp)
#define inet_addr(cp)                       hi_inet_addr(cp)

#else
#define SOCK_NULL               (0)

#define Ip_fd_set       fd_set

#define SOCK_FD_ZERO(set)         FD_ZERO(set)
#define SOCK_FD_ISSET(d, set)     FD_ISSET(d, set)
#define SOCK_FD_SET(d, set)       FD_SET(d, set)
#define SOCK_FD_CLR(d, set)       FD_CLR(d, set)

#endif

/*****************************************************************************
  3 枚举定义
*****************************************************************************/

enum
{
    SOCK_OK = 0,
    SOCK_NO_START,
    SOCK_START,
    SOCK_UDP_INIT_ERR,
    SOCK_TCP_INIT_ERR,
    SOCK_BIND_ERR,
    SOCK_LISTEN_ERR,
    SOCK_SELECT_ERR,
    SOCK_ACCEPT_ERR,
    SOCK_SEND_ERR,
    SOCK_BUTT
};

enum OM_SOCKET_TYPE_ENUM
{
    SOCKET_OM_IND,
    SOCKET_OM_CFG,
    SOCKET_AT,
    SOCKET_BUTT
};

typedef VOS_UINT32 OM_SOCKET_TYPE_ENUM_U32;

/*****************************************************************************
  4 全局变量声明
*****************************************************************************/


/*****************************************************************************
  5 消息头定义
*****************************************************************************/


/*****************************************************************************
  6 消息定义
*****************************************************************************/


/*****************************************************************************
  7 STRUCT定义
*****************************************************************************/

#if (VOS_LINUX == VOS_OS_VER)

typedef int    SOCKET;

#else

typedef unsigned int    SOCKET;

#endif

typedef struct
{
    SOCKET                              socket;
    SOCKET                              listener;
    VOS_SEM                             SmClose;
    CPM_PHY_PORT_ENUM_UINT32            enPhyPort;
    VOS_UINT32                          usPort;
    VOS_CHAR                            aucBuf[SOCK_OM_MSG_LEN];
}COMM_SOCKET_CTRL_INFO_STRU;

typedef struct
{
    VOS_BOOL            bStatus;
    struct sockaddr_in  stAddr;
}SOCKET_UDP_INFO_STRU;

/*****************************************************************************
  8 UNION定义
*****************************************************************************/




/*****************************************************************************
  9 OTHERS定义
*****************************************************************************/


/*****************************************************************************
  10 函数声明
*****************************************************************************/


extern VOS_VOID  Sock_ShutdownAll(VOS_VOID);
extern VOS_UINT32 PPM_SockUdpInit(VOS_VOID);
extern VOS_BOOL PPM_SockIsEnable(VOS_VOID);

#if ((VOS_OS_VER == VOS_WIN32) || (VOS_OS_VER == VOS_NUCLEUS))
#pragma pack()
#else
#pragma pack(0)
#endif

#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif

#endif /* end of OmCommonPpm.h */

