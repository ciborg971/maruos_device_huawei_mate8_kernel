/*******************************************************************************
*
*
*                Copyright 2012, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              twamp_pkt.c
*
*  Project Code: VISPV300R001
*   Module Name: TWAMP
*  Date Created: 2013-03-07
*        Author: a00902361
*   Description: TWAMP packet include  file
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-03-07   a00902361       Create
*
*******************************************************************************/
#ifndef _TWAMP_PKT_H_
#define _TWAMP_PKT_H_

#ifdef __cplusplus
extern "C" {
#endif



typedef struct tagTwampServerGreetingPkt
{
    ULONG ulUnused[3];
    ULONG ulModes;
    ULONG ulChallange[4];
    ULONG ulSalt[4];
    ULONG ulCount;
    ULONG ulMBZ[3];

} TWAMP_SERVER_GREETING_PKT;

typedef struct tagTwampClientGreetingAck
{
    ULONG ulModes;
    ULONG ulKeyId[20];
    ULONG ulTocken[16];
    ULONG ulClient_IV[4];
} TWAMP_CLIENT_GREETING_ACK;

typedef struct tagTwampSetupResponsePkt
{
    ULONG ulModes;
    ULONG ulKeyID[20];
    ULONG ulToken[16];
    ULONG ulClientIV[4];

} TWAMP_SETUP_RESPONSE_PKT;


typedef struct tagTwampServerStartPkt
{
    UCHAR ucMBZ[15];
    UCHAR ucAccept;
    ULONG ulServerIV[4];
    ULONG ulStartTimeHigh;
    ULONG ulStartTimeLow;
    ULONG ulMBZ[2];

} TWAMP_SERVER_START_PKT;



typedef struct tagTwampSessionStartPkt
{
    UCHAR ucCmdid;
    UCHAR ucMBZ[15];
    ULONG ulHMAC[4];

} TWAMP_SESSION_START_PKT;

typedef struct tagTwampSessionStartAckPkt
{
    UCHAR ucAccept;
    UCHAR ucMBZ[15];
    ULONG ulHMAC[4];

} TWAMP_SESSION_START_ACK_PKT;

typedef struct tagTwampSessionStopPkt
{
    UCHAR ucCmdid;
    UCHAR ucAccept;
    UCHAR ucMBZ[2];
    ULONG ulSessionCount;
    ULONG ulMBZ[2];
    ULONG ulHMAC[4];

} TWAMP_SESSION_STOP_PKT;



typedef struct tagTwampReqSessionPkt
{
    UCHAR ucCmdid;
#if VRP_LITTLE_ENDIAN == VRP_YES
    UCHAR ucIPVN : 4;
    UCHAR ucMBZ : 4;
#else
    UCHAR ucMBZ : 4;
    UCHAR ucIPVN : 4;
#endif
    UCHAR ucConfSender;
    UCHAR ucConfReceiver;
    ULONG ulScheduleSlot;
    ULONG ulPacketNum;
    USHORT usSenderPort;
    USHORT usReceiverPort;
    ULONG aulSenderAddr[4];
    ULONG aulReceiveraddr[4];
    ULONG aulSID[4];
    ULONG ulPadLen;
    ULONG aulStartTime[2];
    ULONG aulTimeOut[2];
    ULONG ulTypeP;
    ULONG ulMBZ[2];
    ULONG ulHMAC[4];
}TWAMP_REQUEST_SESSION_PKT;

typedef struct tagTwampAcceptSession
{
    UCHAR ucAccept;
    UCHAR ucMBZ;
    USHORT usPort;
    ULONG aulSID[4];
    ULONG ulMBZ[3];
    ULONG ulHMAC[4];

} TWAMP_SESSION_ACCEPT_PKT;



/*******************************************************************************
*    Func Name: TWAMP_SendServerGreetings
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Sends the Server Greetings Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
ULONG TWAMP_SendServerGreetings(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);


/*******************************************************************************
*    Func Name: TWAMP_SendServerGreetingsWithZEROMode
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Sends the Server Greetings Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_SendServerGreetingsWithZEROMode(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);

/*******************************************************************************
*    Func Name: TWAMP_RecvSetupResponse
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process theSetup Response Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvSetupResponse(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);



/*******************************************************************************
*    Func Name: TWAMP_SendRejectTestSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Send accept session Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_SendRejectTestSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstSession,ULONG ulAccept);





/*******************************************************************************
*    Func Name: TWAMP_SendAcceptSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Send accept session Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_SendAcceptSession(TWAMP_REFLECTOR_TEST_SESSION_S *pstSession,ULONG ulAccept);

/*******************************************************************************
*    Func Name: TWAMP_RecvServerGreeting
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Server Greeting message .
*        Input:  TWAMP_CLIENT_S *pstClient
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvServerGreeting(TWAMP_CLIENT_S *pstClient);

/*******************************************************************************
*    Func Name: TWAMP_RecvServerStart
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Server Greeting message .
*        Input:  TWAMP_CLIENT_S *pstClient
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvServerStart(TWAMP_CLIENT_S *pstClient);



/*******************************************************************************
*    Func Name: TWAMP_SendSessionRequest
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Send accept session Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_SendSessionRequest(TWAMP_CLIENT_S *pstClient);



/*******************************************************************************
*    Func Name: TWAMP_SendStartSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Sends the Start Session Message  .
*        Input:
*                  TWAMP_CLIENT_S *pstClient,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_SendStartSession(TWAMP_CLIENT_S *pstClient);




/*******************************************************************************
*    Func Name: TWAMP_SendStartSessionACK
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Sends the Server Start Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_SendStartSessionACK(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,UCHAR ucAccept);





/*******************************************************************************
*    Func Name: TWAMP_SendSessionStop
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Sends the Stop Session Message  .
*        Input:
*
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_SendSessionStop(TWAMP_CLIENT_S *pstClient ,UCHAR ucAccept);



/*******************************************************************************
*    Func Name: TWAMP_RecvStartSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process theSetup Response Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvStartSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,TWAMP_SESSION_START_PKT *pstStartSessionPkt);



/*******************************************************************************
*    Func Name: TWAMP_RecvStopSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process theSetup Response Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvStopSession(TWAMP_REFLECTOR_CTRL_SESSION_S **pstCtrlSession,TWAMP_SESSION_STOP_PKT *pstStopSessionPkt);

/*******************************************************************************
*    Func Name: TWAMP_RecvCmd
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process theSetup Response Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvCmd(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);



/*******************************************************************************
*    Func Name: TWAMP_RecvAcceptSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Accept session message .
*        Input:  TWAMP_CLIENT_S *pstClient
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvAcceptSession(TWAMP_CLIENT_S *pstClient);

/*******************************************************************************
*    Func Name: TWAMP_RecvStartSessionAck
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Accept session message .
*        Input:  TWAMP_CLIENT_S *pstClient
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
VOID TWAMP_RecvStartSessionAck(TWAMP_CLIENT_S *pstClient);


/*******************************************************************************
*    Func Name: TWAMP_ProcSetupResponse
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process theSetup Response Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
extern VOID TWAMP_ProcSetupResponse(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
                                        TWAMP_SETUP_RESPONSE_PKT     *pstSetupResponse);


/*******************************************************************************
*    Func Name: TWAMP_RecvSessionRequest
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process theSetup Response Message  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
*
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
extern VOID TWAMP_RecvSessionRequest(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
                                                                                TWAMP_REQUEST_SESSION_PKT *pstSessionReq);



/*******************************************************************************
*    Func Name: TWAMP_ReadData
* Date Created: 2013-04-27
*       Author: a00902361
*  Description: Read and Reassamble TWAMP_Fragments for reflector  .
*        Input:
*                 TWAMP_REFLECTOR_CTRL_SESSION_S
*
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07      a00902361       Create first version
*******************************************************************************/
extern ULONG TWAMP_ReadClientData(TWAMP_CLIENT_S *pstClient);




#endif

