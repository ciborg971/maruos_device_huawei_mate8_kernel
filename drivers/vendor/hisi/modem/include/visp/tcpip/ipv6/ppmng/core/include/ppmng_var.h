/**********************************************************************
*        Copyright 2003-2006  Huawei Technologies India Private Limited        
*                          All Rights Reserved                                 
*----------------------------------------------------------------------
*                              ppmng.h                                            
*    Project Code:  VRP5.0                                                     
*    Module Name:  IP6 PP                                                     
*    Create Date:  2003/06/09                                               
*    Author:       Arun H S
*    Description:  To define data structure for PP component     
*-----------------------------------------------------------------------
*  Modification History                                                        
*  DATE        NAME             DESCRIPTION                                    
*  ----------------------------------------------------------------------
*  2003-06-09  Arun H S         Create                                         
*************************************************************************/ 
#ifndef _IP6_PPMNG_VAR_H
#define _IP6_PPMNG_VAR_H

#ifdef __cplusplus
extern "C"{
#endif

extern ULONG g_ulIP6UniqueID;
extern ULONG g_ulNewIp6Id;
extern UCHAR g_ucIP6SlowTimeoutCount;
/* End of Added by wangbin, 2015/10/24 */

extern ULONG g_ulIP6FragPacketsNum;

/* ·������Ŀǰ�ķ�Ƭ��������� */
extern ULONG g_ulIP6ReassQueNum;

/* �������ñ���ȱʡHop Limit��ȫ�ֱ��� */
extern ULONG g_ulIP6_Default_Hoplimit;
extern LONG g_lPPMaxLinkHdr;

/* �������ñ���ȱʡFlow Label��ȫ�ֱ��� */
extern ULONG g_ulIP6_Default_Flowlabel;

/* This flag is to indicate whether the PAF/Licence
* is enabled for IPv6 stack or not. If this is disabled,
* the CLI wont show up
*/
extern ULONG g_ulIP6FunFlag;

/* This flag is to indicate that the "ipv6" CLI is performed or not. This flag will enable/disable forwarding. */
extern ULONG g_ulIP6RoutingFlag;

/* This flag is for redirect enable/disable functionality */
extern ULONG g_ulIP6RedirectFlag;

/* Current index indicator for the protocol switch table */
extern UCHAR     g_ucProtoTableCurrentIndex;

extern ULONG  g_ulFastTimerId;
extern ULONG  g_ulSlowTimerId;


/* �����˸������Э����IPv6Э�鿪�ر��������±� */
extern UCHAR  g_chIp6ProtoX[IPPROTO_MAX];

extern IP6_PP_IntermediateFunction *g_pstIntermediate;

/* IPv6����ͳ����Ϣ�ı��� */
extern IP6STAT_S g_stIP6Stat;

extern struct IIF_IP6_ICMP6_ComIntFunVtbl      *g_pstPPICMPVtbl;
extern struct IIF_IP6_ICMP6_ComIntCFGVtbl      *g_pstPPICMPCFGVtbl; /*Add for vispv1r6*/
extern struct IIF_IP6_ADDR_ComIntFunVtbl       *g_pstPPADDRVtbl;
extern struct IIF_IP6_ADDR_ComIntFunVtbl       *g_pstPPADDRVtbl;


extern struct IIF_IP6_PMTU_ComIntFunVtbl       *g_pstPPPMTUVtbl;
extern struct IIF_IP6_PMTU_ComIntCFGVtbl       *g_pstPPPMTUCFGVtbl;/*Add for vispv1r6*/
extern struct IIF_IP6_ND_ComIntFunVtbl           *g_pstPPNDVtbl;

extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl  *g_pstPPFIBVtbl;
extern struct IIF_IPV6_FIBCONTR_ComIntFUNVtbl  *g_pstPPFIBCVtbl; 

extern struct IIF_IP6_ND_COMMONVtbl            *g_pstPPNDCommonVtbl; 
extern struct IIF_IP6_ND_HOST_FUNVtbl          *g_pstPPNDHostFunVtbl;
extern struct IIF_IP6_ND_ComIntFunVtbl         *g_pstPPNDFunVtbl;

extern IP6_PP_MOD_INFO_S               g_stPPModInfo;
extern IP6_PP_SH_CALLBACUP_SET_S       g_stPPCallbackFun;

extern const IN6ADDR_S g_stTmpAnyAddr;
extern const UCHAR g_ucAlwaysZero;

extern SOSB6_CALLBACUP_SET_S g_stPPSOSB6Callback;
extern IN6PCB_CALLBACUP_SET_S g_stPPIN6PCBCallBack;

/* IPv6����������е�ͷָ�� */
extern IP6REASSQUEUE_S g_stIP6ReassQueue;
 
extern IP6_PP_Register_Notify g_pstNotifyList[IP6_PP_MAX_NOTIFY_REGISTER];
extern ULONG g_ulNotifyCount;

extern ULONG g_ulIP6PPCoreDebugFlag;
/*added by zhangyaping for IP6_FMEF*/
extern ULONG g_ulIP6PPCoreDebugErrpktFlag;
/*end of added by zhangyaping*/

extern ULONG g_ulIP6PPEnable_LocalFragOnMainboard;

/* Modified by Rajesh for Product support Defect id BYAD11615 */
extern ULONG g_ulGSRProduct;
 /* Begin : Defect ID: BYAD12096,     Modifier:Rajesh,   Date:2004/10/15 
      Reason   : To provide generic function pointer registration*/
extern GSR_FUNC_REGISTER_S  g_stGsrFuncPointers;
 
/* NE5000 macro remove */
extern ULONG                        g_ulIP6PPPPI ;
extern IP6_PP_PPI_FUNC_REGISTER_S   g_stIP6PPPPIFuncPointers;

extern ULONG g_ulIP6PPIsHostNode ;

/* ��ƷICMPV6���Ĵ����Ӻ��� */
extern TCPIP_IP6_PROC_ICMP6_PKT_HOOK_S g_stPpmngProcIcmpv6PktHook;
#define  g_pfTCPIPIp6ProcSndIcmp6PktHook    g_stPpmngProcIcmpv6PktHook.pfTCPIPIp6ProcSndIcmp6PktHook
#define  g_pfTCPIPIp6ProcRcvIcmp6PktHook    g_stPpmngProcIcmpv6PktHook.pfTCPIPIp6ProcRcvIcmp6PktHook

extern TCPIP_PP6_PKT_STAT_S *g_pstPP6PktStat;


#ifdef __cplusplus
}
#endif

#endif

