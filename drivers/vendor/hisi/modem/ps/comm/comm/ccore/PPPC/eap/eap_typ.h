/************************************************************************
 *                                                                      *
 *                             Eap_typ.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             wangyong                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP的eap协议模块私有数据结构                    *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件定义了eap协议模块的全部私有数据结构                        *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _EAPC_TYPE_H_
#define      _EAPC_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif     /* end of __cplusplus */

/* EAP ID/SUCCESS/FAIL公共结构 */
typedef struct tagPPP_EAPPAYLOAD_S
{
    UCHAR ucEAPCode;
    UCHAR ucEAPID;
    USHORT usEAPLen;
    UCHAR ucEAPType;
}VOS_PACKED PPP_EAPPAYLOAD_S;

/* EAP 控制块数据结构定义 */
typedef struct tagPppEAPInfo
{
    PPPINFO_S *pstPppInfo ;         /* PPP控制块指针 */
    UCHAR *pucEAP;
    RELTMR_T ulWaitAuthRspTimeID;      /* 等待AAA鉴权响应定时器id */
    RELTMR_T ulRspTimeoutID;           /* 等待EAP响应超时定时器 */
    RELTMR_T ulRaAUTHTimerID;          /* 重认证定时器ID */
    ULONG ulReqTransmits;           /* 已传送Request次数 */
    ULONG ulTimeOutTime;            /* 超时时间 */
    ULONG ulNowUTCInSec;
    USHORT usEAPLen;                /* EAP 长度 */
    UCHAR ucEapRequestID;           /* EAP 报文ID */
    UCHAR ucState;                  /* Server 状态 */
    UCHAR aucState[DIAM_AUTH_STATE_LEN];                  /* AAA的state信元 */
    UCHAR ucStateLen;                  /* state len */
    UCHAR ucRsv[2];
    UCHAR ucUsed : 1;                   /* EAP控制块使用标记*/
    UCHAR ucRequestforIdentity : 1;     /* 1:request for identity 0:request from aaa */
    UCHAR ucEAPFlag : 2;                /* EAP 标志位 0:request 1:Success  2:Fail   */
    UCHAR ucReAuthFlag : 1;
    UCHAR ucFirstFlag : 1;
} PPPEAPINFO_S ;

/* 计算MSK使用的结构体 */
typedef struct
{
    ULONG state[5];
    ULONG count[2];
    UCHAR buffer[64];
} SHA1_CTX;

typedef union
{
    UCHAR        ucCharDate[64];
    unsigned int uiIntData[16];
} CHAR64LONG16;


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _EAP_TYPE_H_ */

#endif  /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

