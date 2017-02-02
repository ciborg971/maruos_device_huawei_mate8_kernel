/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            pmtu_fun.h
 *    Project Code : VRP5.0
 *    Module Name  : IP6 PMTU
 *    Version      : Initial Draft
 *    Create Date  : 2003/06/10
 *         Author  : Surya PC
 *     Description : interface - functional related header file
 *------------------------------------------------------------------------------
 *  Modification History
 *  DATE        NAME             DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2003-06-10  Surya         Create
 *  2006-09-14     Sandeep          Modify           IPBIRV1R2
 ******************************************************************************/
#ifndef _IP6_PMTUFUNC_H
#define _IP6_PMTUFUNC_H

#ifdef  __cplusplus
extern "C"{
#endif

VOID  IP6_PMTU_NotifyMTU (IN6ADDR_S *pstDA, ULONG ulZoneid, ULONG ulMtu);

/* Begin : Added by Suraj_R for NP Support */
#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
ULONG IP6_PMTU_Notify_PPI(ULONG ulOper, VOID *pvPMTUInfo);
#endif

/* End : Added by Suraj_R for NP Support */

#ifdef  __cplusplus
}
#endif

#endif

