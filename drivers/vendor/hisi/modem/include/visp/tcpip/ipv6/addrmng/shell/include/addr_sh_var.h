/******************************************************************************

  Copyright (C), 2001-2011, Huawei Tech. Co., Ltd.

 ******************************************************************************
  File Name     : addr_sh_var.h
  Version       : IPBIRV100R003.IPv6.E001
  Author        : Rajat Phull
  Created       : 2006/9/18
  Last Modified :
  Description   : Contains extern declaration of all global variables ued
                  in Shell
  Function List :
  History       :
  1.Date        : 2006/9/18
    Author      : Rajat Phull
    Modification: Created file
  2.Problem Number: AC4D01246     Author:KLSrini,   Date:2006/12/4
    Description   :  Exception with router restart when change Controller
                    interface mode with IPv6 debug
******************************************************************************/
#ifndef _ADDR_SH_VAR_H_
#define _ADDR_SH_VAR_H_


#ifdef __cplusplus
extern "C" {
#endif

extern ULONG g_ulIP6AddrMemShortageFlag;

extern ULONG g_ulAddrCliState;


extern struct  IIF_IP6_ADDR_GENERIC_INTVtbl        *g_pstADDRInitTable;
extern struct  IIF_IP6_ADDR_GENERIC_CFGVtbl        *g_pstADDRCfgTable;
extern struct  IIF_IP6_ADDR_GENERIC_FUNVtbl        *g_pstADDRFunTable;
extern struct  IIF_IP6_ADDR_GENERIC_IR_FUNVtbl     *g_pstADDRIRFunTable;
extern struct  IIF_IP6_ADDR_GENERIC_INT_INITVtbl   *g_pstADDRINTInitTable;
extern struct  IIF_IP6_ADDR_GENERIC_INT_FUNVtbl    *g_pstADDRINTFunTable;
#if (VRP_NO == IP6_NDHOST)
extern struct  IIF_IP6_ADDR_GENERIC_INT_HSBVtbl    *g_pstADDRINTHSBTable;
#endif
extern struct  IIF_IP6_ADDR_GENERIC_INT_SSAVtbl    *g_pstADDRINTSSATable;

/* Begin  : Defect ID: D01006, Modifier:Rajesh, Date:2004/9/13
   Reason : Initial, Max Mtu change for Pos, GE interfaces*/
extern SPECS_RES_VALUE_S  g_stShMtuPosVal;
extern SPECS_RES_VALUE_S  g_stShMtuGEVal;
extern SPECS_RES_VALUE_S  g_stShAddrNum;

extern ULONG g_ulAddrExecIndex;

extern IP6_ADDR_MOD_INFO_S g_stADDRShellModInfo;

extern CHAR *Msg_Router_En[];
extern CHAR *Inf_Addr_Ch[];
extern CHAR *Inf_Addr_En[];
extern ULONG ulSOCKTmrQueID;

extern VOID IP6_Addr_SH_IfnetHotNotifyCB (ULONG ulEvent, ULONG ulSlot,
                                        VOID *pstIfnet, ULONG ulIfIndex);
extern ULONG IP6_Addr_SH_NotifyCliChange(ULONG ulCliState);
extern VOID IP6_Addr_SH_ProcTimerEvents (IP6_Addr_TIMER_S *pstTimerMsg);
extern ULONG IP6_Addr_SH_BuildRun(CHAR *pszSectionName, CHAR **pszBuildRunInfo);

/* BEGIN: Modified by KLSrini, 2006/12/4   PN:AC4D01246*/
/* extern VOID IP6_Log_Text(enum LOG_LEVEL enLevel, CHAR *pMessage, ...);*/
ULONG IP6_SH_CheckDebug(ULONG ulLevel);

/* END:   Modified by KLSrini, 2006/12/4 */
extern ULONG IP6_Addr_RegPPNotifyCallBack (ULONG ulRoutingFlag);

extern ULONG IP6_Addr_SH_TimerCreate(ULONG ulTaskID, ULONG ulMsgQueID,
                                ULONG ulMillSec,
                                VOID (*pfTimerFunc)(VOID *), VOID  *pArg,
                                ULONG *pulRetTimerID, ULONG ulFlag);
extern ULONG IP6_Addr_SH_TimerCreate_SockRun(ULONG ulMillSec,
                                VOID (*pfTimerFunc)(VOID *), VOID  *pArg,
                                ULONG *pulRetTimerID, ULONG ulFlag);
extern ULONG IP6_Addr_SH_Tm_Now(ULONG *pulRetTimeInMillSecHigh,
                                     ULONG *pulRetTimeInMillSecLow);
extern VOID IP6_Addr_SH_ReplaceBuildRunInfo (CHAR *, ULONG, CHAR*);

/*extern ULONG VOS_Que_Write(ULONG ulQueID, ULONG ulMsg [IP6_QUEUE_WRITE_MSG_LEN],
                        ULONG ulFlags, ULONG ulTimeOutInMillSec);*/

#if (VRP_YES == VRP_CENTERALIZATION)
#if (TCPIP_IN_VRP == VRP_NO)
/* Begin:VISP V3R2C10 VRF chandra , 2014-03-18 */  
/* extern ULONG SFIB6_Item_IsAvailable(VOID); */
extern ULONG SFIB6_Item_IsAvailable(USHORT usZoneId);
/* End:VISP V3R2C10 VRF chandra , 2014-03-18 */  
extern ULONG SFIB6_Update_InterfaceAddress(IP6_ADDR_NOTIFY_MSG_S*);
extern ULONG TCPIP_IPV6AddrChangeProc(IP6_ADDR_NOTIFY_MSG_S *pMsg);
#endif
#endif

extern ULONG ulSOCKTmrQueID;
extern ULONG ulVRPTID_SOCK;


/* Begin: Added by Santhosh 71702, 2008/1/8 */
extern ULONG g_ulADDR_Sh_IsIAS;

/* End: Added by Santhosh 71702, 2008/1/8 */

#if (VRP_YES == IP6_NDHOST)

/* Added For ND Host */
extern ULONG IP6_ND_SH_StopTimer(ULONG ulTimerID);

extern ULONG IP6_ND_SH_CreateNonPeriodTimer(ULONG ulTimeValue,
                    ULONG (*pfIP6_TimeOutHandler)(UINTPTR aulPara[]),
                    UINTPTR ulPara[TWL_MAX_USE_PARA_LEN], ULONG *pulTimerid);

extern ULONG IP6_ND_SH_GetTimerMsg(ULONG ulTimerID,
                                        UINTPTR aulPara[TWL_MAX_USE_PARA_LEN]);

extern ULONG IP6_ND_SH_RefreshTimer(ULONG ulTimerID,ULONG ulNewTimeValue);

extern ULONG IP6_ND_SH_GetRestTimeValue(ULONG ulTimerID,ULONG *pulRestTimeValue);

#endif

/* Begin : Added by Suraj_R for NP Support */
#if (IPBIR_IPV6_NP_SUPPORT == VRP_YES)
extern IPV6_PPI_HOOK_S * g_pstNPCallBack;
#endif

extern USHORT  g_usMaxAddrVrf;

/* End : Added by Suraj_R for NP Support */

#ifdef __cplusplus
}
#endif/* end of __cplusplus */

#endif/* end of _ADDR_SH_VAR_H_ */

