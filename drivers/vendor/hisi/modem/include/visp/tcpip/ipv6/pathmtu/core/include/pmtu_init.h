/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            pmtu_init.h
 *    Project Code :  IPBIR
 *    Module Name  :  IP6 PMTU
 *    Version      :  Initial Draft
 *    Create Date  :  2006/08/24
 *         Author  :  Sandeep P A
 *     Description :  interface - INIT related header file
 *------------------------------------------------------------------------------
 *  Modification History
 *  DATE          NAME             DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2006-08-24   Sandeep            Create
 *  2006-09-14   Sandeep             Modify           IPBIRV1R2
 *
 ******************************************************************************/
#ifndef _IP6_PMTUINIT_H
#define _IP6_PMTUINIT_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG IP6_PMTU_HA_RegisterCallBack
                        (PMTU_SHELL_HA_BACUP_SET_S *pstCallBackSet);
ULONG IP6_PMTU_Init_Com_NEW (IPB_IR_PMTU_COM_ID_INFO_S *pstComInfo,
                                                                ULONG ulComLen);
ULONG IP6_PMTU_SetModuleInfo (PMTU_MOD_INFO_S *pMInfo);
ULONG IP6_PMTU_Activate_Com (VOID);
ULONG IP6_PMTU_RegDebugCallBack (PMTU_SHELL_DEBUG_CALLBACK_SET_S
                                                            *pstCallBackSet);
ULONG IP6_PMTU_RegTimeoutCallBack (PMTU_SHELL_TIMEOUT_CALLBACUP_SET_S
                                                            *pstCallBackSet);
ULONG IP6_PMTU_Notification_Register (SOCKADDR_IN6_S *pstsAD, LONG lSockid,
                                      ULONG ulTaskId, ULONG ulIfindex);
ULONG IP6_PMTU_Notification_Unregister (LONG lSockid, ULONG ulTaskId);
ULONG IP6_PMTU_RegSocketCallBack(PMTU_CALLBACKUP_SET_S *pstCallBackSet);
ULONG IP6_PMTU_RegShellCallbackFunc (IP6_PMTU_SH_CALLBACK_FUNC_S
                                                            *pstCallBackSet);

/* Begin : Added by Suraj_R for NP Support */
ULONG IP6_PMTU_RegNPCallback(IPV6_PPI_HOOK_S *pstCallbackFunc);

/* End : Added by Suraj_R for NP Support */

extern IComponentFactory m_PMTUFactory;

extern IIF_IP6_PMTU_INIT         g_stPMTU_INIT;
extern IIF_IP6_PMTU_INT_INIT     g_stPMTU_INT_INIT;
extern IIF_IP6_PMTU_CFG          g_stPMTU_CFG;
extern IIF_IP6_PMTU_INT_SSA      g_stPMTU_INT_SSA;
extern IIF_IP6_PMTU_FUN          g_stPMTU_FUN;
extern IIF_IP6_PMTU_IR_FUN       g_stPMTU_IR_FUN;
extern IIF_IP6_PMTU_INT_HSB      g_stPMTU_INT_HSB;

#ifdef  __cplusplus
}
#endif

#endif

