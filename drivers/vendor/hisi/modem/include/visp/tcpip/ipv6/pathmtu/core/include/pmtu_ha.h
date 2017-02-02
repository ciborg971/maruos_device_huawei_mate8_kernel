/******************************************************************************
 *
 *        Copyright 2003-2006  Huawei Technologies India Private Limited
 *                          All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *                            pmtu_ha.h
 *    Project Code :  VRP5.0
 *    Module Name  :  IP6 PMTU
 *    Version      :  Initial Draft
 *    Create Date  :  2003/06/10
 *         Author  :  Surya PC
 *     Description :  HA related header file
 *------------------------------------------------------------------------------
 *  Modification History
 *  DATE          NAME             DESCRIPTION
 *  ----------------------------------------------------------------------------
 *  2003-06-10   Surya               Create
 *  2006-09-14   Sandeep             Modify           IPBIRV1R2
 ******************************************************************************/
#ifndef _IP6_PMTUHA_H
#define _IP6_PMTUHA_H

#ifdef  __cplusplus
extern "C"{
#endif

ULONG IP6_PMTU_HA_RealtimeBackup (UCHAR *pData, ULONG ulLen);
ULONG IP6_PMTU_HA_SetBackupData (UCHAR *pData, ULONG ulEventType);
VOID  IP6_PMTU_HA_DataSmoothOutside (VOID);
VOID  IP6_PMTU_HA_DataSmoothInside (VOID);
VOID  IP6_PMTU_HA_StateChange(ULONG ulHAState);
ULONG IP6_PMTU_HA_SendBackupData (VOID);


#ifdef  __cplusplus
}
#endif

#endif

