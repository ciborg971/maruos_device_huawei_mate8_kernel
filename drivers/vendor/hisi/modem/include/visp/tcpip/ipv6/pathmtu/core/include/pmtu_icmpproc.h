/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            pmtu_icmpproc.h
 *    Project Code :  VRP5.0
 *    Module Name  :  IP6 PMTU
 *    Version      :  Initial Draft
 *    Create Date  :  2003/06/10
 *         Author  :  Surya PC
 *     Description :  icmp handling related header file
 *------------------------------------------------------------------------------
 *  Modification History
 *  DATE          NAME             DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2003-06-10    Surya            Create
 *  2006-09-14    Sandeep          Modify           IPBIRV1R2
 *
 ******************************************************************************/
#ifndef _IP6_PMTUICMPPROC_H
#define _IP6_PMTUICMPPROC_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG  IP6_PMTU_ICMP_Input (IP6_CTLPARAM_S *pstTooBigNotify);
VOID IP6_PMTU_IncreaseAccessCount (PMTU_ENTRY_S *pstPmtuEntry);

/* Defect ID: BYAD011814,Reason   : Component issues*/
ULONG IP6_PMTU_TooBigHandler (TOO_BIG_INFO_S *pstTooBigInfo);

VOID IP6_PMTU_NotifySocketsPMTUChange (PMTU_ENTRY_S *pstPmtuEntry,
                    ULONG ulPmtuChanged, LONG lSocketid, ULONG ulTaskid);

#ifdef  __cplusplus
}
#endif

#endif

