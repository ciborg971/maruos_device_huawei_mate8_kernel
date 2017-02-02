/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              atk_var.c
*
*  Project Code: VISPV3R2
*   Module Name: ATK Module  
*  Date Created: 2014-08-07
*        Author: a00900892
*   Description: Defines global variables used by ATK module.
*                module VISP
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                 DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2014-08-07  a00900892            Create
*
*******************************************************************************/

#ifdef    __cplusplus
extern "C"{
#endif

#include "tcpip/atk/include/atk_ext.h"

/* ifnet Vtable*/
struct IIF_IFNET_ComIntFUNVtbl  *g_pstAtkIfFunVtbl = NULL;

/* Times used to check if the IP attack crosses the threshold to raise or end
    aram. */
ULONG  g_ulATK_Timer;

/* This structure stores the status of global malfomed packet counter, it is
    queried and cleared every malformed packet warning timer expires. */
ATTACK_WARNING_S g_stAttackWarningStatus;

/* This global variable stores all configurations. */
ATTACK_CFG_INFO_S g_stAttackCfg;

/* Pointer to a dynamically allocated array of structures that stores IP Attack 
   statistics for all interfaces. The array is indexed using a hash of the
   interface index. A list will be present in case of conflict in hash. */
ATTACKSTAT_BY_IF_S **g_pstAttackStatsList;

TCPIP_ATTACKSTAT_S g_stGlobalAttackStats;


#ifdef __cplusplus
}
#endif

