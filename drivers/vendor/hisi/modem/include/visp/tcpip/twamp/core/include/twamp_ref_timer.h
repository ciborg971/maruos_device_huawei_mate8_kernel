/*******************************************************************************
*
*
*                Copyright 2012, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              twamp_ref_timer.h
*
*  Project Code: VISPV300R001
*   Module Name: TWAMP
*  Date Created: 2013-02-25
*        Author: a00900872
*   Description: TWAMP Reflector Timer includer file 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-04-3   m70989              Create
*
*******************************************************************************/
#ifndef __TWAMP_REF_TIMER_H__
#define __TWAMP_REF_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
*    Func Name: TWAMP_TimerInit
* Date Created: 2013-04-03
*       Author: m70989
*  Description: Twamp Timer Intialization
*        Input: ulTableSize , Timer Table Size
*                  pfTimerExpiry Timer Expiry function   
*       Output: 
*       Return: TWAMP_OK  on Success, Non Zero value on error.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-02-25      m70989       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_TimerInit(ULONG ulTableSize, TWAMP_TIMER_EXPIRY_FUN pfTimerExpiry);


/*******************************************************************************
*    Func Name: TWAMP_TimerAdd
* Date Created: 2013-04-03
*       Author: m70989
*  Description: Adding timer to the timer list
*        Input: VOID
*       Output: 
*       Return: TWAMP_OK  on Success, Non Zero value on error.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-02-25      m70989       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_TimerAdd(ULONG ulId, ULONG ulTimeOut, UINTPTR *pulTimerId);


/*******************************************************************************
*    Func Name: TWAMP_TimerDel
* Date Created: 2013-04-03
*       Author: m70989
*  Description: Deleting the timer from the timer list
*        Input: VOID
*       Output: 
*       Return: TWAMP_OK  on Success, Non Zero value on error.
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE                 NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-02-25      m70989       Create first version
*
*******************************************************************************/
extern ULONG TWAMP_TimerDel(UINTPTR  ulTimerId);


/*******************************************************************************
*    Func Name: TWAMP_RefTimer
* Date Created: 2013-04-02
*       Author: a00902361
*  Description: Reflector Timer 
*        Input:  
*
*       Output: 
*       Return: 
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE                NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-04-02      m70989       Create first version
******************************************************************************/
extern VOID TWAMP_RefTimer(VOID *pArg);


/*******************************************************************************
*    Func Name: TWAMP_ProcessTimer
* Date Created: 2013-04-02
*       Author: a00902361
*  Description: Process the timer event 
*        Input:  
*
*       Output: 
*       Return: 
*
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE                NAME             DESCRIPTION
*  ----------------------------------------------------------------------------
*  2013-04-02      m70989       Create first version
******************************************************************************/
extern ULONG TWAMP_ProcessTimer(VOID);


#ifdef __cplusplus
}
#endif

#endif /*__TWAMP_REF_TIMER_H__*/

