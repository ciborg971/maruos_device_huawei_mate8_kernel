/*******************************************************************************
*
*
*                Copyright 2013, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              twamp_ppi.h
*
*  Project Code: VISPV300R001
*   Module Name: TWAMP PPI
*  Date Created: 2013-03-13
*        Author: a00900872
*   Description: Contains Utities required by TWAMP
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-03-13      a00900872       Create first version
*******************************************************************************/
#ifndef _TCPIP_TWAMP_PPI_H_
#define _TCPIP_TWAMP_PPI_H_

#ifdef __cplusplus
extern "C"
{
#endif



/*******************************************************************************
*    Func Name: TWAMP_SenderPpiUpdate
* Date Created:  2013-03-13
*       Author: a00900872 
*  Description: Download Session Info to NP
*        Input: TWAMP_CLIENT_S *pstClient, UCHAR *pucSessDscp, ULONG ulType
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-13      a00900872       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_SenderPpiUpdate(TWAMP_CLIENT_S *pstClient, TWAMP_SENDER_S *pstSender, UCHAR *pucSessDscp, ULONG ulType);


/*******************************************************************************
*    Func Name: TWAMP_SenderPpiUpdate
* Date Created:  2013-03-13
*       Author: a00900872 
*  Description: Download Session Info to NP
*        Input: TWAMP_CLIENT_S *pstClient, UCHAR *pucSessDscp, ULONG ulType
*       Output: 
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-03-13      a00900872       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_ResponderPpiUpdate(TWAMP_REFLECTOR_TEST_SESSION_S *pstTestSession, 
                                                                    UCHAR *pucSessDscp, 
                                                                    ULONG ulType);

#ifdef __cplusplus
}
#endif


#endif/* end of _TWAMP_PPI_H_*/


