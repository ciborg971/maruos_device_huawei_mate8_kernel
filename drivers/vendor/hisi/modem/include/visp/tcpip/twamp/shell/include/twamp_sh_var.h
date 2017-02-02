/*******************************************************************************
*
*
*                Copyright 2012, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              twamp_sh_var.h
*
*  Project Code: VISPV300R001
*   Module Name: TWAMP
*  Date Created: 2013-02-25
*        Author: a00900872
*   Description: TWAMP variable include  file
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2013-02-25   a00900872       Create
*
*******************************************************************************/
#ifndef _TWAMP_SH_VAR_H_
#define _TWAMP_SH_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

extern ULONG g_ulTwampConfigMngTimerId;

extern VOID *g_pstTwampConfigMnglistHead;


extern TCPIP_HOOK_TWAMP_CTRL_FUNC g_pfnCtrlHook;

extern TCPIP_HOOK_TWAMP_SESS_FUNC g_pfnSessHook;



#ifdef __cplusplus
}
#endif

#endif

