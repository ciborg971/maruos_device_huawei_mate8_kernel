/*******************************************************************************
*
*
*                Copyright 2012, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              twamp_ref.c
*
*  Project Code: VISPV300R001
*   Module Name: TWAMP
*  Date Created: 2013-03-07
*        Author: a00902361
*   Description: TWAMP reflector include  file
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-03-07   a00902361       Create
*
*******************************************************************************/
#ifndef _TWAMP_REF_H_
#define _TWAMP_REF_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
*    Func Name: TWAMP_REF_TaskMain
* Date Created: 2013-02-25
*       Author: a00900872
*  Description: Twamp reflector main task function
*        Input: ULONG ulArg0:
*               ULONG ulArg1:
*               ULONG ulArg2:
*               ULONG ulArg3:
*       Output: 
*       Return: VOID
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-02-25      a00900872       Create first version
*
*******************************************************************************/
extern VOID TWAMP_REF_TaskMain(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);



/*******************************************************************************
*    Func Name: TWAMP_GetReflectorById
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Gets the reflector from the Reflector Table based on ulReflectorId .
*        Input:
*                  ULONG ulReflectorId Reflector Identifier
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
extern TWAMP_REFLECTOR_S * TWAMP_GetReflectorById(ULONG ulReflectorId);



/*******************************************************************************
*    Func Name: TWAMP_GetReflectorByIPandVRF
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Gets the reflector from the Reflector Table based on address .
*        Input:
*                  ULONG ulIpaddr
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
extern TWAMP_REFLECTOR_S * TWAMP_GetReflectorByIPandVRF(ULONG ulIpaddr,ULONG ulVRF);



/*******************************************************************************
*    Func Name: TWAMP_AttachReflector
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Gets the reflector from the Reflector Table based on ulReflectorId .
*        Input:
*                  ULONG ulReflectorId Reflector Identifier
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
extern VOID  TWAMP_AttachReflector(TWAMP_REFLECTOR_S *pstReflector);


/*******************************************************************************
*    Func Name: TWAMP_CreateSessionIDQueue
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: ADD REFLECTOR Event processing function.
*        Input:
*                  TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflectorData
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
extern ULONG TWAMP_CreateSessionIDQueue(TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflectorData,TWAMP_REFLECTOR_S *pstReflector);


/*******************************************************************************
*    Func Name: TWAMP_Add_Reflector
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: ADD REFLECTOR Event processing function.
*        Input:
*                  TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflectorData
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
extern ULONG TWAMP_Add_Reflector(TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflectorData);

/*******************************************************************************
*    Func Name: TWAMP_Del_Reflector
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: ADD REFLECTOR Event processing function.
*        Input:
*                  ULONG ulReflectorID
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
extern ULONG TWAMP_Del_Reflector(ULONG ulReflectorId);

/*******************************************************************************
*    Func Name: TWAMP_ValidateReflectorConfig
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Validates the reflector Configuration provided by the user.
*        Input:
*                  TCPIP_TWAMP_REFL_CONFIG_S *pstReflConf Contains the Reflector Configuration[]
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
extern ULONG TWAMP_ValidateReflectorConfig(TWAMP_REFLECTOR_QUEUE_DATA_S *pstReflData);


/*******************************************************************************
*    Func Name: TWAMP_ProcessReflectorListenFDSet
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Reflector Listen FD Set .
*        Input:
*                  ULONG ulCount, No of Connection to be Processed
*                  fd_set * pstListenFDset pointer to the fd set
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
extern VOID TWAMP_ProcessReflectorListenFDSet(ULONG ulCount,fd_set * pstListenFDset);



/*******************************************************************************
*    Func Name: TWAMP_ProcessReflectorConnectionRequest
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Connection request for Reflector  .
*        Input:
*                  TWAMP_REFLECTOR_S *pstReflector
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
extern VOID TWAMP_ProcessReflectorConnectionRequest(TWAMP_REFLECTOR_S *pstReflector);


/*******************************************************************************
*    Func Name: TWAMP_CTRL_SessionTableInsert
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Inserts Control Session in Ctrl Session table  .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession
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
extern VOID TWAMP_CTRL_SessionTableInsert(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);

/*******************************************************************************
*    Func Name: TWAMP_DestroyReflectorCtrlSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the destroys the Ctrl Session .
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
extern VOID TWAMP_DestroyReflectorCtrlSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);


/*******************************************************************************
*    Func Name: TWAMP_UpdateSID
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Updates SID in the Test Session .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession
*                  TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession
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
extern VOID TWAMP_UpdateSID(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
                                                               TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession);


/*******************************************************************************
*    Func Name: TWAMP_AttachTestSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Attach test Session to the control session and to the Test Session Table .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession
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
extern VOID TWAMP_AttachTestSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
                                                               TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession);

/*******************************************************************************
*    Func Name: TWAMP_GetSessionIdFromQueue
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Get port from reflector .
*        Input:
*                  TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession,
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
extern USHORT TWAMP_GetSessionIdFromQueue(TWAMP_REFLECTOR_S *pstReflector);


/*******************************************************************************
*    Func Name: TWAMP_ReleaseSessionId
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Get port from reflector .
*        Input:
*                  TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession,
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
extern VOID TWAMP_ReleaseSessionId(TWAMP_REFLECTOR_S *pstReflector,USHORT usSessionId);


/*******************************************************************************
*    Func Name: TWAMP_GetPortFromPool
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Get port from reflector .
*        Input:
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
extern USHORT TWAMP_GetPortFromPool(TWAMP_REFLECTOR_S *pstReflector,ULONG ulPeerIP);


/*******************************************************************************
*    Func Name: TWAMP_GetSETSockID
* Date Created: 2013-03-07
*       Author: a00902361
*  Description:Gets the set Sock fd from the FD Set .
*        Input:
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
extern LONG TWAMP_GetSETSockFD(fd_set * pstFDset);

/*******************************************************************************
*    Func Name: TWAMP_DelTestSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Stops all the Test Session .
*        Input:
*                  TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession,
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
extern VOID TWAMP_DelTestSession(TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession);




/*******************************************************************************
*    Func Name: TWAMP_NotifyCtrlSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Sends rosa notification to the shell  .
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
extern VOID TWAMP_NotifyCtrlSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession , ULONG ulState);


/*******************************************************************************
*    Func Name: TWAMP_NotifyTestSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Sends rosa notification to the shell  .
*        Input:
*                  TWAMP_REFLECTOR_TEST_SESSION_S *pstCtrlSession,
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
extern VOID TWAMP_NotifyTestSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession,
            TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession , ULONG ulState);


/*******************************************************************************
* Func Name: TWAMP_RefOnTimeOut
* Date Created: 2013-04-02
* Author: m70989
* Description: Timer will invoke this on when the particular client times out
*        Input:  ulId Identifier
*       Output: 
*       Return:
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-04-02      m70989       Create first version
*******************************************************************************/
extern ULONG TWAMP_RefOnTimeOut(ULONG ulId);

/*******************************************************************************
*    Func Name: TWAMP_DelAllTestSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Stops all the Test Session .
*        Input:
*                  TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession
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
extern VOID TWAMP_DelAllTestSession(TWAMP_REFLECTOR_CTRL_SESSION_S *pstCtrlSession);


/*******************************************************************************
*    Func Name: TWAMP_AddCTRLSession
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process the Add Connection request for Reflector  .
*        Input:
*                  TWAMP_REFLECTOR_S *pstReflector
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
extern ULONG TWAMP_AddCTRLSession(TWAMP_REFLECTOR_S *pstReflector,LONG lChildSock,
                                                                ULONG ulPeerIP,USHORT usPeerPort);


/*******************************************************************************
*    Func Name: TWAMP_CTRL_SessionTableSearch
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Search Control Session in Ctrl Session table  .
*        Input:
*                  LONG lSockfd
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
extern TWAMP_REFLECTOR_CTRL_SESSION_S * TWAMP_CTRL_SessionTableSearch(LONG lSockfd);


/*******************************************************************************
*    Func Name: TWAMP_Restart_Reflector
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: .
*        Input:
*                  ULONG ulReflectorID
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
extern ULONG TWAMP_Restart_Reflector(ULONG ulReflectorId);

extern VOID * TWAMP_GetNextSession( VOID *pParam,VOID **ppList);

extern VOID TWAMP_ProcessReflectorCtrlConnection(LONG lsockfd);

extern VOID TWAMP_FreeReflectorSockOpt(TCPIP_TWAMP_SOCK_OPTIONS_S *pstSockOptData,ULONG ulSockOptNum);

extern TCPIP_TWAMP_SOCK_OPTIONS_S * TWAMP_AllocateReflectorSockOpt(TCPIP_TWAMP_REFL_CONFIG_S *pstConf, ULONG *pulTotalSockOptionsSizeforHA);
/*******************************************************************************
*    Func Name: TWAMP_ProcessStopSessionFDSet
* Date Created: 2013-06-20
*       Author: a00902361
*  Description: Process the Stop Session FD Set .
*        Input:
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
*  2013-06-20      a00902361       Create first version
*******************************************************************************/
extern VOID TWAMP_ProcessStopSessionFDSet(void);




#ifdef __cplusplus
}
#endif

#endif

