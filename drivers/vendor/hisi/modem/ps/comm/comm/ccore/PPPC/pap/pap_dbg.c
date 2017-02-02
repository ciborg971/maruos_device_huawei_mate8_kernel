/************************************************************************
*                                                                      *
*                             pap_dbg.c								*
*                                                                      *
*  Project Code:       VRP3.0                                          *
*  Create Date:        2000/06/14                                      *
*  Author:             Zhu Feng Zhi                                    *
*  Modify Date:                                                        *
*  Document:                                                           *
*  Function:           PAPģ���debug��Ϣ����                          *
*  Others:                                                             *
*----------------------------------------------------------------------*
*                                                                      *
* Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
*                     ALL RIGHTS RESERVED                              *
*                                                                      *
*----------------------------------------------------------------------*
*                                                                      *
*   ����ļ�������PAPģ��debug��Ϣ�����ȫ������                       *
*                                                                      *
************************************************************************/



/*****************************************************************************
  1 ͷ�ļ�����
*****************************************************************************/
#include "ppp_inc.h"



#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif


/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
#define         THIS_FILE_ID            PS_FILE_ID_PPPC_PAP_DBG_C

/*****************************************************************************
  2 ȫ�ֱ�������
*****************************************************************************/

CHAR *cPap_Debug_Code[] =
{
    "Reserved",      /* 0 */
    "Request",       /* 1 */
    "Ack",           /* 2 */
    "Nak"            /* 3 */
};

CHAR *cPap_Client_State[] =
{
    "Initial",
    "SendRequest",
    "ClientSuccess",
    "ClientFailed",
    " "
};

CHAR *cPap_Server_State[] =
{
    "Initial",
    "ServerListen",
    "ServerSuccess",
    "ServerFailed",
    "WaitAAA"
};

CHAR *cPap_Debug_Event[] =
{
    "Initial ",             /* 0 */
    "Server Lower Up",  /* 1 */
    "Client Lower Up",  /* 2 */
    "Lower Down",           /* 3 */
    "Receive Request",  /* 4 */
    "AAA Result",           /* 5 */
    "Receive Ack",      /* 6 */
    "Receive Nak",      /* 7 */
    "Request TimeOut",  /* 8 */
    "Code Reject",      /* 9 */
    "Wait Request TimeOut",  /* 10 */
    "AAA Response TimeOut",   /* 11 */
    "Error Event"           /* 12 */
};

/*****************************************************************************
  3 ����ʵ��
*****************************************************************************/
/*lint -save -e958 */

/****************************************************************************
* CREATE DATE  ��2000/06/14                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     ��������ڱ��ĵĵ�����Ϣ,ֻ��Է���PPP״̬���Ŀ���Э��       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�                                       *
*                pPacket:����ͷλ��                                         *
*                ulLen:���ĳ���                                             *
*                ucIsInPacket:�Ƿ������뱨��                                *
*                usProtocol:����Э���                                      *
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��PPP_LCP_ReceivePacket��                                    *
****************************************************************************/
VOID PAP_Debug_Packet(PPPINFO_S* pstPppInfo, UCHAR *pPacket, ULONG ulLen, USHORT usProtocol, UCHAR ucIsInPacket)
{
    PPPPAPINFO_S *pstPapInfo   = pstPppInfo->pstPapInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    ULONG ulTotalLen = ulLen + PAP_HEADERLEN;
    UCHAR ucCode, ucId;
    USHORT sFrameLen;
    LONG lLen = (LONG)ulLen;
    UCHAR ucLen;

    szDebugBuf[0] = '\0';

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_Packet == VRP_NO)
    {
        /*DEBUG ����δ��,����*/
        return;
    }

    /* pap ������� */

    /*
     |--------PPP Head(bytes) -------|
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |  ff   |  03   |    c223       |  code |  ID   |    frame len  |   ...     |
     +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
     |------------- lLen / sFrameLen ------------|
                                    pPacket
     |-----------------------------  ulTotalLen	--------------------------------|
     */

    /* VOS_DBGASSERT(pstPppInfo) ;
     VOS_DBGASSERT(pPacket) ;
     */
    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Packet: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s(%04x) Pkt, Len %lu ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        (ucIsInPacket == 1) ? "Input " : "Output",
                        PPP_Debug_GetProtocolName(usProtocol),
                        usProtocol,
                        ulTotalLen
            );

    /* �Ϸ��Լ�� */
    if (lLen < 4)
    {
        pBuf += VOS_sprintf(pBuf, "\r\n Value: %s ",
                            PPP_Debug_GetValueStr(pPacket, (UCHAR)lLen)
                );
        pBuf += VOS_sprintf(pBuf, "\r\n Error: packet too short, discard.");
        PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);
        return;
    }

    PPP_GETCHAR(ucCode, pPacket);
    PPP_GETCHAR(ucId, pPacket);
    PPP_GETSHORT(sFrameLen, pPacket);

    /* ��ʾ��ǰ״̬,Code,id�Լ����� */
    /*������server״̬����client״̬ added by guoning 20021022 D7169*/
    if (((ucIsInPacket == 1) && (ucCode == PAP_AUTHREQ))
       || ((ucIsInPacket != 1) && (ucCode == PAP_AUTHACK))
       || ((ucIsInPacket != 1) && (ucCode == PAP_AUTHNAK)))
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                            cPap_Server_State[pstPapInfo->ucServerState],
                            cPap_Debug_Code[ucCode],
                            ucCode,
                            ucId,
                            sFrameLen
                );
    }
    else if (((ucIsInPacket != 1) && (ucCode == PAP_AUTHREQ))
       || ((ucIsInPacket == 1) && (ucCode == PAP_AUTHACK))
       || ((ucIsInPacket == 1) && (ucCode == PAP_AUTHNAK)))
    {
        pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
                            cPap_Server_State[pstPapInfo->ucClientState],
                            cPap_Debug_Code[ucCode],
                            ucCode,
                            ucId,
                            sFrameLen
                );
    }/*end of add*/

    /*pBuf += VOS_sprintf(pBuf, "\r\n      State %s, code %s(%02x), id %x, len %d ",
        (pstConfig->bAuthRmtPap)?
        cPap_Server_State[pstPapInfo->ucServerState]:cPap_Client_State[pstPapInfo->ucClientState],
        cPap_Debug_Code[ucCode],
        ucCode,
        ucId,
        sFrameLen
        );*/


    /* ������� */

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
        case PAP_AUTHREQ:

            /*��ʾId_Len �� Id*/
            PPP_GETCHAR(ucLen, pPacket);

            pBuf += VOS_sprintf(pBuf, "\r\n      Host Len:%3d  Name:%s ", ucLen,
                                PPP_Debug_GetString(pPacket, ucLen));
            PPP_INCPTR(ucLen, pPacket);

            /* ��ʾPassword Length �� Pwd*/
            PPP_GETCHAR(ucLen, pPacket);
            pBuf += VOS_sprintf(pBuf, "\r\n      Pwd Len:%3d  Pwd:%s", ucLen,
                                PPP_Debug_GetString(pPacket, ucLen));
            break;
        case PAP_AUTHACK:
        case PAP_AUTHNAK:

            /*��ʾMessage_Len �� Msg*/
            PPP_GETCHAR(ucLen, pPacket);
            pBuf += VOS_sprintf(pBuf, "\r\n      Msg Len:%3d  Msg:%s", ucLen,
                                PPP_Debug_GetString(pPacket, ucLen));
            break;
        default:
            pBuf += VOS_sprintf(pBuf, "\r\n	   UnKnown Code ");
            break;
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/14                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     �������Э��״̬ת���ĵ�����Ϣ                               *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPapInfo:PAP���ƿ�ָ��                                 *
*                ucNewState:״̬����״̬                                    *
*				 ucType: Client״̬��Server״̬								*
* OUTPUT       ��                                                           *
* RETURN       ��0                                                          *
* CALLED BY    ��					                                        *
****************************************************************************/
VOID PAP_Debug_StateChange(PPPINFO_S *pstPppInfo, UCHAR ucNewState, UCHAR ucType)
{
    PPPPAPINFO_S *pstPapInfo = pstPppInfo->pstPapInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;
    CHAR cState[20], cNewState[20];

    szDebugBuf[0] = 0;
    cState[0] = 0;
    cNewState[0] = 0;

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_StateChange == VRP_NO)
    {
        /*DEBUG ����δ��,����*/
        return;
    }

    if (ucType == CLIENT_STATE)
    {
        /* Client ״̬ת�� */
        if (pstPapInfo->ucClientState == ucNewState)
        {
            return;
        }
        else
        {
            if (pstPapInfo->ucClientState > PAP_STATE_CLIENT_FAILED)
            {
                /* �����״̬ */
                (VOID)VOS_sprintf(cState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cState, "%s", cPap_Client_State[pstPapInfo->ucClientState]);
            }

            if (ucNewState >= PAP_STATE_WAIT_AAA)
            {
                /* �����״̬ */
                (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cNewState, "%s", cPap_Client_State[ucNewState]);
            }

            pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");
            pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                                PPP_Debug_GetInterfaceName(pstPppInfo),
                                PPP_Debug_GetProtocolName(PPP_PAP),
                                cState,
                                cNewState);
        }
    }
    else
    {
        /* Server ״̬ת�� */
        if (pstPapInfo->ucServerState == ucNewState)
        {
            return;
        }
        else
        {
            if (pstPapInfo->ucServerState > PAP_STATE_WAIT_AAA)
            {
                /* �����״̬ */
                (VOID)VOS_sprintf(cState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cState, "%s", cPap_Server_State[pstPapInfo->ucServerState]);
            }

            if (ucNewState > PAP_STATE_WAIT_AAA)
            {
                /* �����״̬ */
                (VOID)VOS_sprintf(cNewState, "%s", "Error-State");
            }
            else
            {
                (VOID)VOS_sprintf(cNewState, "%s", cPap_Server_State[ucNewState]);
            }

            pBuf += VOS_sprintf(pBuf, "\r\n  PPP State Change: ");
            pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s --> %s ",
                                PPP_Debug_GetInterfaceName(pstPppInfo),
                                PPP_Debug_GetProtocolName(PPP_PAP),
                                cState,
                                cNewState);
        }
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/14                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     �����PAP��Э�鷢���ⲿ�¼��ĵ�����Ϣ                       *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPapInfo: PAP���ƿ�ָ��                                *
*                ulEvent:״̬���¼�                                         *
* OUTPUT       ��                                                           *
* RETURN       ��					                                        *
* CALLED BY    ��						                                    *
****************************************************************************/
VOID PAP_Debug_Event(PPPINFO_S* pstPppInfo, UCHAR ucEvent)
{
    PPPPAPINFO_S *pstPapInfo   = pstPppInfo->pstPapInfo;
    PPPCONFIGINFO_S *pstConfig = pstPppInfo->pstConfigInfo;
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    CHAR cClientState[20], cServerState[20], cEvent[100];

    szDebugBuf[0]   = 0;
    cClientState[0] = 0;
    cServerState[0] = 0;
    cEvent[0] = 0;

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_Event == VRP_NO)
    {
        /*DEBUG ����δ��,����*/
        return;
    }

    /* ȡ�� Client ״̬ */
    if (pstPapInfo->ucClientState > PAP_STATE_WAIT_AAA)
    {
        /* �����״̬ */
        (VOID)VOS_sprintf(cClientState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cClientState, "%s", cPap_Client_State[pstPapInfo->ucClientState]);
    }

    /* ȡ�� Server ״̬ */
    if (pstPapInfo->ucServerState > PAP_STATE_WAIT_AAA)
    {
        /* �����״̬ */
        (VOID)VOS_sprintf(cServerState, "%s", "Error-State");
    }
    else
    {
        (VOID)VOS_sprintf(cServerState, "%s", cPap_Server_State[pstPapInfo->ucServerState]);
    }

    if (ucEvent >= PAP_ERROREVENT)
    {
        /* ������¼� */
        (VOID)VOS_sprintf(cEvent, "%s", "Error-Event");
    }
    else
    {
        (VOID)VOS_sprintf(cEvent, "%s", cPap_Debug_Event[ucEvent]);
    }

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Event: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s %s Event ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_PAP),
                        cEvent);

    /*added by guoning for D17169 20021021*/
    switch (ucEvent)
    {
        case PAP_INITIALIZATION:
        case PAP_LOWERDOWN:
        case PAP_CODEREJECT:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ",
                                (pstConfig->bAuthRmtPap) ? cServerState : cClientState);
            break;

        case PAP_CLIENTLOWERUP:
        case PAP_RECEIVEACK:
        case PAP_RECEIVENAK:
        case PAP_REQUESTTIMEOUT:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ", cClientState);
            break;

        case PAP_SERVERLOWERUP:
        case PAP_RECEIVEREQUEST:
        case PAP_AAARESULT:
        case PAP_WAITREQTIMEOUT:
            pBuf += VOS_sprintf(pBuf, "\r\n      state %s ", cServerState);
            break;

        default:
            break;
    }

    /*end of add*/

    /*pBuf += VOS_sprintf(pBuf, "\r\n      state %s ",
                (pstConfig->bAuthRmtPap)?cServerState:cClientState) ;*/

    /* request timeout �¼�:��ʾretransmit������ֵ */
    if (ucEvent == PAP_REQUESTTIMEOUT)
    {
        pBuf += VOS_sprintf(pBuf, ", Retransmit %d ", pstPapInfo->ucTransmits);
    }

    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}

/****************************************************************************
* CREATE DATE  ��2000/06/14                                                 *
* CREATED BY   ��Zhu Feng Zhi                                               *
* FUNCTION     �������Э��PAP�Ĵ�����Ϣ		                            *
* MODIFY DATE  ��                                                           *
* INPUT        ��pstPppInfo:PPP���ƿ�ָ��                                   *
*                usLogLevel:LOG����                                         *
*                pString   :Ҫ������ִ�                                    *
* OUTPUT       ��                                                           *
* RETURN       ��                                                           *
* CALLED BY    ��PAP ��������                                            *
****************************************************************************/
VOID PAP_Debug_Error(PPPINFO_S *pstPppInfo, USHORT usLogLevel, CHAR *pString)
{
    CHAR szDebugBuf[1024];
    CHAR *pBuf = szDebugBuf;

    szDebugBuf[0] = 0;

    /* Begin Added by hyj for B02 */
    /* ����IMSI���������Ϣ */
    DEBUGBYIMSI();
    /* End Added by hyj for B02 */

    if (pstPppInfo->stPppDebugInfo.bDebug_Pap_Error == VRP_NO)
    {
        /*DEBUG ����δ��,����*/
        return;
    }

    /* VOS_DBGASSERT(pstPppInfo) ;*/

    pBuf += VOS_sprintf(pBuf, "\r\n  PPP Error: ");

    pBuf += VOS_sprintf(pBuf, "\r\n      %s %s : %s ",
                        PPP_Debug_GetInterfaceName(pstPppInfo),
                        PPP_Debug_GetProtocolName(PPP_PAP),
                        pString);
    PPP_DebugOutString(szDebugBuf, (pBuf - szDebugBuf), pstPppInfo);

    return;
}


/*lint -restore */


#ifdef __cplusplus
    #if __cplusplus
        }
    #endif
#endif
