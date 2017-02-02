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
#ifndef _TWAMP_CLIENT_H_
#define _TWAMP_CLIENT_H_

#ifdef __cplusplus
extern "C" {
#endif


/*******************************************************************************
*    Func Name: TWAMP_Client_TaskMain
* Date Created: 2013-03-20
*       Author: a00900872
*  Description: Twamp Client main task function     
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
*  2013-03-20      a00900361       Create first version
*
*******************************************************************************/
extern VOID TWAMP_Client_TaskMain(ULONG ulArg0, ULONG ulArg1, ULONG ulArg2, ULONG ulArg3);



/*******************************************************************************
*    Func Name: TWAMP_Del_Client
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Deletes the Client.
*        Input:  
*                  ULONG ulClientId
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
extern ULONG TWAMP_Del_Client(TWAMP_CLIENT_S *pstClient,ULONG ulEvent);

/*******************************************************************************
*    Func Name: TWAMP_Core_AddClient
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: create and connect for a control session.
*        Input:  
*                  ULONG ulClientId Contains the client Id[]
*                  TCPIP_TWAMP_CTRLCLIENT_CONFIG_S *pstCtrlConf Contains the client Configuration[]
*
*       Output: 
*       Return: 
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07     a00902361       Create first version
*******************************************************************************/
extern ULONG TWAMP_Core_AddClient(ULONG ulClientId, TCPIP_TWAMP_CTRLCLIENT_CONFIG_S *pstClientConf);

extern ULONG TWAMP_Core_DelClient(ULONG ulClientId);

/*******************************************************************************
*    Func Name: TWAMP_ProcClientConfig
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Process Client Config event
*        Input:  
*                  TWAMP_CLIENT_QUEUE_DATA_S *pstReflectorData
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
extern VOID TWAMP_ProcClientConfig(TWAMP_CLIENT_QUEUE_DATA_S *pstClientData);

/*******************************************************************************
*    Func Name: TWAMP_Add_Sender
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: ADD Sender  processing function.
*        Input:  
*                  TWAMP_CLIENT_QUEUE_DATA_S *pstReflectorData
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
extern ULONG TWAMP_Add_Sender(TWAMP_CLIENT_QUEUE_DATA_S *pstClientData);


/*******************************************************************************
*    Func Name: TWAMP_Get_Sender
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Get Sender
*        Input:  
*                  TWAMP_CLIENT_S *pstClient,ULONG ulSenderId
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
extern TWAMP_SENDER_S * TWAMP_Get_Sender(TWAMP_CLIENT_S *pstClient,ULONG ulSenderId);




/*******************************************************************************
*    Func Name: TWAMP_Del_Sender
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: Delete Sender  processing function.
*        Input:  
*                  TWAMP_SENDER_S *pstSender
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
extern VOID TWAMP_Del_Sender(TWAMP_SENDER_S *pstSender);


/*******************************************************************************
*    Func Name: TWAMP_Delete_Sender
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: ADD Sender  processing function.
*        Input:  
*                  TWAMP_CLIENT_QUEUE_DATA_S *pstReflectorData
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
extern ULONG TWAMP_Delete_Sender(TWAMP_CLIENT_QUEUE_DATA_S *pstClientData);


/*******************************************************************************
*    Func Name: TWAMP_Core_AddSender
* Date Created: 2013-03-07
*       Author: a00902361
*  Description: create Sender.
*        Input:  
*                  ULONG ulClientId,
*                  ULONG ulSenderId
*                  TCPIP_TWAMP_SENDER_CONF_S *pstSenderConf
*
*       Output: 
*       Return: 
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-07     a00902361       Create first version
*******************************************************************************/
extern  ULONG TWAMP_Core_AddSender(ULONG ulClientId,  ULONG ulSenderId,
    TCPIP_TWAMP_SENDER_CONF_S *pstSenderConf);


extern ULONG TWAMP_Core_Delete_Sender(ULONG ulClientId, ULONG ulSenderId);


#ifdef __cplusplus
}
#endif

#endif

