/************************************************************************
*                                                                      *
*                             Eap_dbug.c                               *
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2010/07/14                                      *
*  Author:             WANGYONG                                        *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           EAP模块的debug信息处理                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   这个文件包括了EAP模块debug信息处理的全部代码                       *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 头文件包含
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    协议栈打印打点方式下的.C文件宏定义
*****************************************************************************/

/*****************************************************************************
  2 全局变量定义
*****************************************************************************/

#if (VRP_MODULE_LINK_PPP_EAP == VRP_YES)

CHAR *cEap_Debug_Code[] =
{
    "Reserved",      /* 0 */
    "Request",    /* 1 */
    "Response",      /* 2 */
    "SUCCESS",      /* 3 */
    "FAILURE"      /* 4 */
};

CHAR *cEap_State[] =
{
    "Initial",
    "SendEAPReqforIdentity",
    "SendEAPReq",
    "EAPSuccess",
    "EAPFailed",
    "EAPWaittingAAA"
};

CHAR *cEap_Debug_Event[] =
{
    "Server Lower Up ",     /* 0 */
    "Client Lower Up",  /* 1 */
    "Lower Down ",      /* 2 */
    "Receive EAP Request from AAA",    /* 3 */
    "Receive EAP Response",     /* 4 */
    "Receive EAP Success from AAA",  /* 5 */
    "Receive EAP Failure from AAA",  /* 6 */
    "EAP Request for id TimeOut",     /* 7 */
    "EAP Request TimeOut",    /* 8 */
    "Initial",          /* 9 */
    "EAP REAUTH Begin",  /* 10 */
    "Code Reject",      /* 11 */
    "DIAM AAA Result",           /* 12 */
    "WAIT DIAM AAA Response TimeOut",   /* 13 */
    "Error Event"           /* 14 */
};

/*****************************************************************************
  3 函数实现
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ：2010/07/14                                                 *
* CREATED BY   ：wangyong                                                   *
* FUNCTION     ：输出关于报文的调试信息,只针对符合PPP状态机的控制协议       *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块                                       *
*                pPacket:报文头位置                                         *
*                ulLen:报文长度                                             *
*                ucIsInPacket:是否是输入报文                                *
*                usProtocol:报文协议号   1 :input 0:output                  *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：PPP_LCP_ReceivePacket等                                    *
****************************************************************************/
VOID EAP_Debug_Packet(PPPINFO_S* pstPppInfo,
                       UCHAR *    pPacket,
                       ULONG      ulLen,
                       USHORT     usProtocol,
                       UCHAR      ucIsInPacket)
{
    PPPEAPINFO_S *pstEapInfo = pstPppInfo->pstEapInfo;


    CHAR szDebugBuf[3000];
    CHAR *pBuf = szDebugBuf;
    ULONG ulTotalLen = ulLen + EAP_HEADERLEN;
    UCHAR ucCode, ucId;
    USHORT sFrameLen;
    LONG lLen = (LONG)ulLen;
    LONG lBufLen = 0;
    UCHAR ucType;

    szDebugBuf[0] = '\0';

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_EAP_Packet == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* eap 报文情况 */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    c227       |  code |  ID   |    frame len  |   ...     |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |------------- lLen / sFrameLen ------------|
                                    pPacket
     |-----------------------------  ulTotalLen	--------------------------------|
     */

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Packet: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s(%04x) Pkt, Len %lu ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        (ucIsInPacket == 1) ? "Input " : "Output",
                        PPP_Debug_GetProtocolName(usProtocol),
                        usProtocol,
                        ulTotalLen
            );

    /* 合法性检查 */
    if (lLen < 4)
    {
        pBuf += VOS_sprintf(pBuf, "\r\n Value: %s ",
                            PPP_Debug_GetValueStr(pPacket, (UCHAR)lLen)
                );
        pBuf += VOS_sprintf(pBuf, "\r\n Error: packet too short, discard.");
        lBufLen = pBuf - szDebugBuf;
        PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

        return;
    }

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(sFrameLen, pPacket);

    /* 显示当前状态,Code,id以及长度 */
    if ((ucCode == EAP_PACKET_CODE_RESPONSE)
        || (ucCode == EAP_PACKET_CODE_REQUEST)
        || (ucCode == EAP_PACKET_CODE_SUCCESS)
        || (ucCode == EAP_PACKET_CODE_FAILURE))
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                            cEap_State[pstEapInfo->ucState],
                            cEap_Debug_Code[ucCode],
                            ucCode,
                            ucId,
                            sFrameLen);
    }


    /* 报文情况 */

    /*
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     ...   |  code |  ID   |    frame len  |          ...          |
    -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |-------- lLen ---------|
     |------ sFrameLen ------|
                                           pPacket
     */
    switch (ucCode)
    {
        case EAP_PACKET_CODE_REQUEST:
        case EAP_PACKET_CODE_RESPONSE:
        case EAP_PACKET_CODE_SUCCESS:
        case EAP_PACKET_CODE_FAILURE:
            PPP_GETCHAR(ucType, pPacket);

            /*显示type */
            pBuf += VOS_sprintf(pBuf, "\r\n      Type: %d ", ucType);


            break;

        default:
            pBuf += VOS_sprintf(pBuf, "\r\n      UnKnown Code ");
            break;
    }

    lBufLen = pBuf - szDebugBuf;
    PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/14                                                 *
* CREATED BY   ：wangyong                                                   *
* FUNCTION     ：输出子协议状态转换的调试信息                               *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                 *
*                ucNewState:状态机新状态                                    *
*                ucType: Client状态或Server状态                             *
* OUTPUT       ：                                                           *
* RETURN       ：0                                                          *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID EAP_Debug_StateChange(PPPINFO_S *pstPppInfo, UCHAR ucNewState, UCHAR ucType)
{
    PPPEAPINFO_S *pstEapInfo = pstPppInfo->pstEapInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    CHAR cState[20], cNewState[20];
    LONG lBufLen = 0;
    szDebugBuf[0] = '\0';
    cState[0] = 0;
    cNewState[0] = 0;

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_EAP_StateChange == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* Server 状态转换 */
    if (pstEapInfo->ucState == ucNewState)
    {
        return;
    }
    else
    {
        if (pstEapInfo->ucState > EAP_STATE_WAITING_AAA)
        {
            /* 错误的状态 */
            (VOID)VOS_sprintf(cState, "%s", "Error-State");
        }
        else
        {
            (VOID)VOS_sprintf(cState, "%s", cEap_State[pstEapInfo->ucState]);
        }

        if (ucNewState > EAP_STATE_WAITING_AAA)
        {
            /* 错误的状态 */
            (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
        }
        else
        {
            (VOID)VOS_sprintf(cNewState, "%s", cEap_State[ucNewState]);
        }

        pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");
        pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                            PPP_Debug_GetInterfaceName(pstPppInfo),
                            PPP_Debug_GetProtocolName(PPP_EAP),
                            cState,
                            cNewState);
    }

    lBufLen = pBuf - szDebugBuf;
    PPP_DebugOutString(szDebugBuf, lBufLen, pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/14                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：输出EAP子协议发生外部事件的调试信息                        *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo: PPP控制块指针                                  *
*                ulEvent:状态机事件                                         *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：                                                           *
****************************************************************************/
VOID EAP_Debug_Event(PPPINFO_S* pstPppInfo, UCHAR ucEvent)
{
    PPPEAPINFO_S *pstEapInfo = pstPppInfo->pstEapInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    CHAR cServerState[20], cEvent[100];

    szDebugBuf[0]   = 0;
    cServerState[0] = 0;
    cEvent[0] = 0;

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_EAP_Event == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }

    /* 取得 Server 状态 */
    if (pstEapInfo->ucState > EAP_STATE_WAITING_AAA)
    {
        /* 错误的状态 */
        (VOID)VOS_sprintf(cServerState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cServerState, "%s", cEap_State[pstEapInfo->ucState]);
    }

    if (ucEvent >= EAP_ERROREVENT)
    {
        /* 错误的事件 */
        (VOID)VOS_sprintf(cEvent, "%s", "Error-Event");
    }
    else
    {
        (VOID)VOS_sprintf(cEvent, "%s", cEap_Debug_Event[ucEvent]);
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Event: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s Event ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_EAP),
                        cEvent);

    pBuf += VOS_sprintf(pBuf, "\r\n      state %s ", cServerState);


    /* response timeout 事件:显示retransmit计数器值 */
    if ((ucEvent == EAP_REQUESTTIMEOUT_FORID)
           ||(ucEvent == EAP_REQUESTTIMEOUT))
    {
        pBuf += VOS_sprintf(pBuf, ", Retransmit %lu ", pstEapInfo->ulReqTransmits);
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ：2010/07/14                                                 *
* CREATED BY   ：WANGYONG                                                   *
* FUNCTION     ：输出子协议EAP的错误信息                                    *
* MODIFY DATE  ：                                                           *
* INPUT        ：pstPppInfo:PPP控制块指针                                   *
*                usLogLevel:LOG级别                                         *
*                pString   :要输出的字串                                    *
* OUTPUT       ：                                                           *
* RETURN       ：                                                           *
* CALLED BY    ：EAP 各处理函数                                             *
****************************************************************************/
VOID EAP_Debug_Error(PPPINFO_S *pstPppInfo, USHORT usLogLevel, CHAR *pString)
{
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    szDebugBuf[0] = '\0';

    /* 根据IMSI输出调试信息 */
    DEBUGBYIMSI();

    if (pstPppInfo->stPppDebugInfo.bDebug_EAP_Error == VRP_NO)
    {
        /*DEBUG 开关未打开,返回*/
        return;
    }


    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Error: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_EAP),
                        pString);
    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

#endif  /* #if( VRP_MODULE_LINK_PPP_EAP == VRP_YES ) */

/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
