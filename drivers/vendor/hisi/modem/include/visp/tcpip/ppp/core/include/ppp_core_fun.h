

#ifndef _PPP_CORE_FUNC_H_
#define _PPP_CORE_FUNC_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_basefun.h"

/********** ��ʼ������ ************/
ULONG PPP_CreateCB(IFNET_S *);
ULONG PPP_DeleteCB(IFNET_S *pstIfnet);
ULONG PPP_FreeBlock(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
ULONG PPP_InitCB(PPPINFO_S *, IFNET_S * );
ULONG PPP_InitConfigInfo(PPPINFO_S *);
ULONG PPP_ClearCB(PPPINFO_S *pstPppInfo);
ULONG PPP_ClearCBOnSlave(PPPINFO_S *pstPppInfo);

VOID PPP_ClearConfigInfo(PPPINFO_S *);
VOID PPP_Timer_Out( VOID *pArg );
ULONG PPP_Timer_Init(PPPTIMERNODE_S *pstTimerMem, ULONG ulTimerNum);
ULONG PPP_Timer_Create(ULONG ulOutTime, PppTimeoutCall pCallBackFunc, VOID * pArg, ULONG * pulTimerId);
ULONG PPP_Timer_Delete(ULONG ulTimerId);
/********** ��ʼ������ ************/


/********** ͬ�첽ת�� ************/
MBUF_S *PPP_SynToAsy(MBUF_S *pstSynMBuf, ULONG ulAsynAccm);
MBUF_S *PPP_AsyToSyn(MBUF_S *pstAsyMBuf);
/********** ͬ�첽ת�� ************/


/****************** �ں� *******************/
/* ������ֽӿں��� */
ULONG PPP_Ppi_GetBitFromOprType(ULONG ulOprType);
ULONG PPP_PpiRepeateCallback(ULONG aulArgs[]);


VOID PPP_Core_ReceiveEventFromProtocol (PPPINFO_S *, ULONG , CHAR *);
VOID PPP_Core_ReceiveEventFromShell(PPPINFO_S *, ULONG , CHAR *);
VOID PPP_Core_ReceivePacketFromShell(PPPINFO_S *, UCHAR *, UCHAR *, ULONG );
VOID PPP_Core_RejectProtocol(VOID *, USHORT );
VOID PPP_Core_ReceiveUnknownProtocol (PPPINFO_S *, UCHAR *, UCHAR *, ULONG, USHORT);
PPPFSM_S *PPP_Core_GetFsmByProtocol(VOID *, USHORT );

/* �ڲ������� */
VOID PPP_Core_Reset(VOID *);
ULONG PPP_Core_GetProtocol(PPPINFO_S *, UCHAR *, USHORT *);
ULONG PPP_Core_GetProtocolId(UCHAR *pszPacket, USHORT *pusProtocol);
/* End of addition */
VOID PPP_Core_NotifyUperLcpDown(PPPINFO_S *);
void PPP_Core_NotifyNcpDown(PPPINFO_S *pstPppInfo);
VOID PPP_Core_AuthUp(PPPINFO_S *pstPppInfo);
LONG PPP_Core_NCPExist (  ULONG  ulOriginIfindex,
                                    USHORT usProtocol,
                                    ULONG  ulIfIndex                                                                
                                 );
VOID PPP_Ncp_Reset_Timer(PPPFSM_S *pstFsm);

ULONG IPHC_InputCRTPPkt( PPPINFO_S *pstPppInfo, MBUF_S *pstMbuf,USHORT usProtocol);
ULONG IPHC_InputCRTPContextPkt( PPPINFO_S *pstPppInfo, MBUF_S *pstMbuf,USHORT usProtocol);

/* �׶�ת������ */
VOID PPP_Core_AuthenticatePhase(PPPINFO_S *);
VOID PPP_Core_DeadPhase(PPPINFO_S *);
VOID PPP_Core_EstablishPhase(PPPINFO_S *);
VOID PPP_Core_NetworkPhase(PPPINFO_S *pstPppInfo, ULONG ulNegoFlag);
VOID PPP_Core_TerminatePhase(PPPINFO_S *);

/* ���� */
ULONG PPP_GetMagicNumber(VOID);

VOID PPP_Core_UpdateUsedConfigInfo( PPPINFO_S * pstPppInfo );

/****************** �ں� *******************/


/***************** ״̬�� ******************/
/* ����ӿ� */
VOID PPP_FSM_ReceiveEvent (PPPFSM_S* pstFsm, ULONG ulCmd, CHAR *pPara);
VOID PPP_FSM_ReceivePacket (PPPFSM_S* pstFsm, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen);
VOID PPP_FSM_Init(PPPFSM_S *pstFsm);

/* �ⲿ�¼����� */
VOID PPP_FSM_Close(PPPFSM_S *pstFsm);
VOID PPP_FSM_LowerDown(PPPFSM_S *pstFsm);
VOID PPP_FSM_LowerUp(PPPFSM_S *pstFsm);
VOID PPP_FSM_Open(PPPFSM_S *pstFsm);
VOID PPP_FSM_TimeOut(VOID *pstFsm);

/* �����¼����� */
VOID PPP_FSM_RXJ_Plus(PPPFSM_S *pstFsm);
VOID PPP_FSM_RXJ_Sub(PPPFSM_S *pstFsm);

/* ���Ĵ��� */
VOID PPP_FSM_ReceiveCodeRej(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, ULONG ulLen);
VOID PPP_FSM_ReceiveConfAck(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, ULONG ulLen);
VOID PPP_FSM_ReceiveConfNakRej(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR ucCode, UCHAR *pPacket, ULONG ulLen);
VOID PPP_FSM_ReceiveConfReq(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen);
VOID PPP_FSM_ReceiveProtocolRej(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen);
VOID PPP_FSM_ReceiveTermAck(PPPFSM_S *pstFsm, UCHAR ucId);
VOID PPP_FSM_ReceiveTermReq(PPPFSM_S *pstFsm, UCHAR ucId);
VOID PPP_FSM_ReceiveUnknownCode(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen);

/* ���ķ��� */
VOID PPP_FSM_SendConfigReq(PPPFSM_S *pstFsm);
VOID PPP_FSM_SendPacket(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen);
VOID PPP_FSM_SendPacketByCode(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId);
VOID PPP_FSM_SendDiscReq(PPPFSM_S* pstFsm);

/* ���� */
VOID PPP_FSM_DirectUp(PPPFSM_S *pstFsm);
ULONG PPP_FSM_RebuildRejPacket(UCHAR* pPacketNak, LONG lLenNak, UCHAR* pPacketOri, LONG lLenOri);
VOID PPP_FSM_ChangeState(PPPFSM_S *pstFsm, UCHAR ucNewState);
VOID PPP_FSM_RejLOG(PPPFSM_S *pstFsm, UCHAR *pPacket, UCHAR *szPacketBuf, ULONG ulLen, ULONG ulPacketLen);
/***************** ״̬�� ******************/


/****************** ��� *******************/
/* ���ں˽ӿں��� */
VOID  PPP_Shell_ReceiveEventFromCore(PPPINFO_S *, ULONG , CHAR *);
ULONG PPP_Shell_GetPacketFromCore(CHAR *, UCHAR *, UCHAR *, ULONG , USHORT );
ULONG PPP_Shell_ReceiveNegoPacket(MBUF_S *);
ULONG PPP_Shell_ReceiveAsyPacket(MBUF_S *pMbuf);
VOID  PPP_Shell_AuthRequest(ULONG , PPPAUTHMSG_S *);

/* ����֤����ģ��Ľӿ� */
ULONG PPP_Shell_GetDataStatistic(ULONG ulIfnetIndex, PPPSTATISTIC_S *pstPppDataFlow);
ULONG  PPP_Shell_ReceiveAuthResult(PPPAUTHRESULT_S *pstAuthResult);

/* ���ϡ��²�Ľӿں��� */
ULONG PPP_Shell_NiOutput(MBUF_S *);
ENQUEUE_PF PPP_Shell_ISLInput(IFNET_S *, MBUF_S *);
ULONG PPP_Shell_ISLIoCtl(IFNET_S *, ULONG , CHAR *);
ULONG PPP_Shell_NiIoCtl(IFNET_S *, ULONG , CHAR *);
ULONG PPP_Shell_DropPacket(MBUF_S *, ULONG , CHAR *);

ULONG PPP_Shell_GetMtu(IFNET_S *pstIfnet);

ULONG IPHC_InputCRTPPkt( PPPINFO_S *pstPppInfo, MBUF_S *pstMbuf,USHORT usProtocol);
ULONG IPHC_InputCRTPContextPkt( PPPINFO_S *pstPppInfo, MBUF_S *pstMbuf,USHORT usProtocol);

/* �ڲ������� */
ULONG PPP_Shell_SendPacketToISL(PPPINFO_S *, MBUF_S *, USHORT );
ENQUEUE_PF PPP_Shell_DealInputPacket(IFNET_S*  pstIfnet, 
                                     PPPINFO_S *pstPppInfo ,                                      
                                     MBUF_S *pMbuf);
                                     

/* ������Ϣ������ */
ULONG PPP_ProcessCompress( ULONG ulIfIndex,  ULONG ulCompress, ULONG ulSetYes);
ULONG PPP_ProcessNegotiateTimeout(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulTimeoutTime);

ULONG PPP_ProcessDebug(ULONG ulIfIndex, 
                       ULONG ulDebugAll, 
                       ULONG ulSetYes, 
                       ULONG ulType,
                       USHORT usProtocol, 
                       ULONG ulPacketNum, 
                       ULONG ulPacketOctets);

ULONG PPP_ProcessAuthenticationType(ULONG ulIfIndex, ULONG ulSetYes, ULONG usPap, ULONG usChap, ULONG usCallin);
ULONG PPP_GetAuthenticationType(ULONG ulIfIndex, ULONG *pulType, ULONG *pulCallInAuth);
ULONG PPP_ProcessIPCPDNSAccept(ULONG ulIfIndex , ULONG ulNo);

ULONG PPP_ProcessIPCPDNSAddr(ULONG ulIfIndex, ULONG ulNo, ULONG ulNum_Pri, ULONG ulNum_Sec);

ULONG PPP_ProcessChapHostname(ULONG ulIfIndex, ULONG ulSetYes, CHAR *pcHostname);

ULONG PPP_ProcessChapPassword(ULONG ulIfIndex,ULONG ulSetYes, ULONG usEncrypt, UCHAR *pcPassword);

ULONG PPP_ProcessPapNamePwd(ULONG ulIfIndex,ULONG ulSetYes,  ULONG usEncrypt, UCHAR *pcPassword, UCHAR *pcUsername);
ULONG PPP_ProcessCallbackAcceptMsg(ULONG ulIfIndex, ULONG ulNo);

ULONG PPP_ProcessCallbackRequest(ULONG ulIfIndex, ULONG ulNo);

ULONG PPP_SetVjcompBeEnable(ULONG ulIfIndex, ULONG ulSetYes);

ULONG PPP_ProcessIPHCEnable(ULONG ulIfIndex, ULONG ulEnable, ULONG ulCCompany);
ULONG PPP_ProcessTcpSpace(ULONG ulIfIndex, ULONG ulTcpSpace, ULONG ulReset);
ULONG PPP_ProcessNonTcpSpace(ULONG ulIfIndex, ULONG ulNonTcpSpace, ULONG ulReset);
ULONG PPP_ProcessFMaxPeriod(ULONG ulIfIndex, ULONG ulFMaxPeriod, ULONG ulReset);
ULONG PPP_ProcessFMaxTime(ULONG ulIfIndex, ULONG ulFMaxTime, ULONG ulReset);
ULONG PPP_ProcessMaxHeader(ULONG ulIfIndex, ULONG ulMaxHeader, ULONG ulReset);
ULONG PPP_ProcessNegoSubOptions(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPP_ProcessRtpCompression (ULONG ulIfIndex, ULONG ulRtpCompression, ULONG ulReset);
ULONG PPP_ProcessCompressType(ULONG ulIfIndex, ULONG ulCompressType, ULONG ulReset);
ULONG PPP_ProcessClearIfIPHCContext (ULONG ulIfIndex);

/*�������Ľӿں���*/
ULONG PPP_ProcessIPHCEnable_PT(ULONG ulIfIndex, ULONG ulEnable, ULONG ulCCompany);
ULONG PPP_ProcessTcpSpace_PT(ULONG ulIfIndex, ULONG ulTcpSpace, ULONG ulReset);
ULONG PPP_ProcessNonTcpSpace_PT(ULONG ulIfIndex, ULONG ulNonTcpSpace, ULONG ulReset);
ULONG PPP_ProcessFMaxPeriod_PT(ULONG ulIfIndex, ULONG ulFMaxPeriod, ULONG ulReset);
ULONG PPP_ProcessFMaxTime_PT(ULONG ulIfIndex, ULONG ulFMaxTime, ULONG ulReset);
ULONG PPP_ProcessMaxHeader_PT(ULONG ulIfIndex, ULONG ulMaxHeader, ULONG ulReset);
ULONG PPP_ProcessNegoSubOptions_PT(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPP_ProcessRtpCompression_PT(ULONG ulIfIndex, ULONG ulRtpCompression, ULONG ulReset);
ULONG PPP_ProcessCompressType_PT(ULONG ulIfIndex, ULONG ulCompressType, ULONG ulReset);
ULONG PPP_ProcessClearIfIPHCContext_PT(ULONG ulIfIndex);

ULONG PPP_ProcessClearIfIPHCStat(ULONG ulIfIndex);
ULONG PPP_ProcessClearIfIPHCStat_PT(ULONG ulIfIndex);
/* Added by Sunmo(44939) for A82D02217, 2006-06-15; and Modified by Sunmo for A82D03499, 2006-07-12 */
ULONG PPP_ProcessDeleteUdpChkSum(ULONG ulIfIndex, ULONG ulDeleteUdpChkSum);
ULONG PPP_ProcessDeleteUdpChkSum_PT(ULONG ulIfIndex, ULONG ulDeleteUdpChkSum);
/*End of addition for IPHC,2005/09/20*/

ULONG PPP_ProcessPFCEnable(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPP_ProcessACFCEnable(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPP_ProcessPFCEnable_PT(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPP_ProcessACFCEnable_PT(ULONG ulIfIndex, ULONG ulSetYes);
/* End of addition */
/*****************************���ܺ���***************************/
ULONG PPP_GetDebugInfo(ULONG ulIfIndex, PPPDEBUGINFO_S *pstPppDebugInfo);
ULONG PPP_GetConfigInfo(ULONG ulIfIndex, PPPCONFIGINFO_S **pstPppConfigs);
ULONG PPP_GetPppByIndex(ULONG ulIfIndex, PPPINFO_S **pstPppInfo);

ULONG PPP_GetPppFsmState(ULONG ulIfIndex, ULONG * pulPppPhase, 
                         ULONG * pulPppNegoType, ULONG * pulPppFsmState);
ULONG PPP_GetPppFsmState_PT(ULONG ulIfIndex, ULONG * pulPppPhase, 
                            ULONG * pulPppNegoType, ULONG * pulPppFsmState);

ULONG PPP_GetFsmState(ULONG ulIfIndex, USHORT usProtocol, ULONG* pulFsmState);
ULONG PPP_GetFsmState_PT(ULONG ulIfIndex, USHORT usProtocol, ULONG* pulFsmState);
ULONG PPP_GetPppPhase(ULONG ulIfIndex, ULONG *pulPhase);
ULONG PPP_GetPppPhase_PT(ULONG ulIfIndex, ULONG *pulPhase);
/* End of addition */

ULONG PPP_ResetLinkByPeerIp(ULONG ulIfIndex, ULONG ulPeerIpaddr);
ULONG PPP_GetInterfaceNego(ULONG ulIfIndex, ULONG* pulNegoLCP,ULONG* pulNegoNCP);
ULONG PPP_SetInterfaceNego(ULONG ulIfIndex,ULONG ulNegoLCP,ULONG ulNegoNCP);

/* v1r6��ӵ����ȼ������ӿ� */
ULONG PPP_SetInterfaceNego_PT(ULONG ulIfIndex, ULONG ulNegoLCP, ULONG ulNegoNCP);
ULONG PPP_GetInterfaceNego_PT(ULONG ulIfIndex, ULONG *pulNegoLCP, ULONG *pulNegoNCP);
ULONG PPP_ProcessAuthenticationType_PT(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulPap, ULONG ulChap, ULONG ulCallin);
ULONG PPP_ProcessChapHostname_PT(ULONG ulIfIndex, ULONG ulSetYes, CHAR *pcHostname);
ULONG PPP_ProcessChapPassword_PT(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulEncrypt, UCHAR *pcPassword);
ULONG PPP_ProcessPapNamePwd_PT(ULONG ulIfIndex, ULONG ulSetYes, ULONG ulEncrypt, UCHAR *pcPassword, UCHAR *pcUsername);
ULONG PPP_SetVjcompBeEnable_PT(ULONG ulIfIndex, ULONG ulSetYes);


/***************** Debug���� ******************/
VOID PPP_Debug_FsmPacket(PPPINFO_S* , UCHAR * , ULONG , USHORT , UCHAR );
VOID PPP_Debug_FsmEvent(PPPFSM_S*, ULONG );
VOID PPP_Debug_FsmIllegalEvent(PPPFSM_S* , ULONG );
VOID PPP_Debug_Error(PPPFSM_S *, USHORT , CHAR *);
VOID PPP_Debug_FsmStateChange(PPPFSM_S *, UCHAR );
VOID PPP_Debug_CoreEvent(PPPINFO_S *pstPppInfo, USHORT usLogLevel,CHAR *pString);
VOID PPP_Debug_PacketVerbose(MBUF_S * pstMBuf ,PPPDEBUGINFO_S *pstPppDebugInfo,ULONG ulMBufLen, UCHAR ucIsPacketIn);
CHAR *PPP_Debug_GetInterfaceName(PPPINFO_S *, CHAR*);
CHAR *PPP_Debug_GetTypeName(USHORT , UCHAR, CHAR* );
CHAR *PPP_Debug_GetProtocolName(USHORT );
CHAR *PPP_Debug_GetValueStr(UCHAR * , ULONG, CHAR* );
CHAR *PPP_Debug_GetProtoState(PPPINFO_S *, USHORT);
CHAR *PPP_Debug_GetCode(UCHAR ucCode);
CHAR *PPP_Debug_GetLcpTypeName(UCHAR );
CHAR *PPP_Debug_GetIpcpTypeName(UCHAR );

CHAR *PPP_Debug_GetMuxcpTypeName(UCHAR ) ;

CHAR *PPP_Debug_GetOsicpTypeName(UCHAR );
CHAR *PPP_Debug_GetString(UCHAR *, ULONG, CHAR* );

VOID PPP_Debug_LinkPhaseChange(PPPINFO_S * pstPppInfo, UCHAR ucNewPhase);
VOID PPP_Debug_SetAllOptions( PPPDEBUGINFO_S *pstPppDebugInfo, UCHAR ucSet );
ULONG PPP_Debug_SetOneOption( PPPDEBUGINFO_S *pstPppDebugInfo, 
                             UCHAR ucSet, 
                             ULONG ulType, 
                             USHORT usProtocol,
                             ULONG ulPacketNum,
                             ULONG ulPacketOctets);

UCHAR PPP_Debug_GetOption( PPPDEBUGINFO_S *pstPppDebugInfo, 
                           ULONG ulType, 
                           USHORT usProtocol);

VOID PPP_Debug_FsmAction(PPPFSM_S* pstFsm, ULONG ulAction);

ULONG PPP_Debug_FsmPrefixE (UCHAR *pPacket, CHAR *szBuf, UCHAR ucCiLen, INT32 i32BufLen, INT32 i32InputOffset);
/* End of addition */

/***************** Debug���� ******************/

/************************����ӿں���****************************/
ULONG PPP_InitIf(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
ULONG PPP_StartIf(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
ULONG PPP_LinkHideCmd(IFNET_S *pIf, ULONG ulPosition, ULONG *pulRet);
ULONG PPP_Init_Com(COM_ID_INFO_S *pComInfo, ULONG  ulComLen);
ULONG PPP_Activate_Com(VOID);
ULONG PPP_SetModuleInfo(PPP_MOD_INFO_S *pstMInfo);
ULONG PPP_CopyCBInfo(ULONG ulIfIndex, VOID *pstPppCBInfo, ULONG ulFlag);
ULONG PPP_SetDebugSwitch(ULONG ulPppDebugInfoFlag);
ULONG PPP_RegShellApi ( PPP_SHELL_CALLBACK_SET_S *pstCallBkSet);
ULONG PPP_Shell_GetUserName(IFNET_S* pstIfnet, CHAR *szName);
ULONG PPP_Shell_GetPeerIPAddr(IFNET_S* pstIfnet, ULONG *ulIpAddr);
VOID  PPP_GetInterfaceID(IFNET_S* pstIfnet, UCHAR * pInterfaceID);

/************************����ӿں���****************************/

/*********************�����غ���**********************************/
ULONG PPP_QueryInterface (IUnknown *This, COMP_IID iid, LPVOID *ppvObj);
ULONG ImplPPPFactoryQueryInterface(IUnknown *This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplPPPFactoryCreateInstance (IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );
/*********************�����غ���**********************************/

/**************************�ⲿ����**********************************/
//extern LONG rand(VOID);
//extern VOID  srand(ULONG seed);
extern ULONG VOS_Tm_Now(ULONG *pulRetTimeInMillSecHigh, ULONG *pulRetTimeInMillSecLow);
extern VOID VOS_T_Delay(ULONG ulMillisecond);
extern LONG VOS_strcmp (const CHAR *, const CHAR *);
extern ENQUEUE_PF L2TP_Input(IFNET_S *pstIf, MBUF_S *pstMbuf);
extern VOID L2TP_Down(IFNET_S *pstIf);
extern ULONG EXEC_OutString(ULONG ulLineIndex, CHAR * szOutString);
extern ULONG TCPIP_ADP_NotifyPppDns(ULONG ulIfIndex, ULONG ulSetYes,ULONG ulPriDns, ULONG ulSecDns);

/**************************�ⲿ����**********************************/

ULONG PPP_SetDebugSwitch_PT(ULONG ulPppDebugFlag);
ULONG PPP_OpenPPPEntry(UINTPTR *pulWaitListHandle);
ULONG PPP_GetPPPEntry (UINTPTR ulEntryWaitList, PPPINFO_S *pstPppInfo);
ULONG PPP_ClosePPPEntry ( UINTPTR ulWaitListHandle );
ULONG PPP_OpenPPPEntry_PT(UINTPTR *pulWaitListHandle);
ULONG PPP_GetPPPEntry_PT (UINTPTR ulEntryWaitList, PPPINFO_S *pstPppInfo);

/* xiehuaguo add for support np 2006-05-08 */
VOID PPP_PPI_DownLoadNegoInfo(PPPFSM_S *pstFsm);
VOID PPP_PPI_DownLoadConfigInfo(PPPINFO_S *pstPppInfo);

ULONG PPP_GetHcNegoResult(PPPINFO_S* pstPppInfo,ULONG* pulNegAcfc,ULONG *pulNegPfc);
UCHAR PPP_GetHeaderLen(ULONG ulNegAcfc, ULONG ulNegPfc, USHORT usProtocol);

ULONG PPP_SetDiscrSpecial (ULONG ulSet);

/*(ͬ�����ⵥA82D17438)add by wuhailan, 2007-7-5.����PPP��λ��ʱ��*/
ULONG PPP_SetPPPResetTime(ULONG ulTime);

/*add by wuhailan for SWID00213,2007-3-9.*/
ULONG PPP_DealNothing(MBUF_S *pMBuf); 

/* ADD by ybo for enhance ppp debug 2007/7/26 */
ULONG PPP_SetVerboseSwitch(PPPDEBUGINFO_S *pstPppDebugInfo,
                           UCHAR ucSet,
                           ULONG ulType,
                           USHORT usProtocol,
                           ULONG ulPacketNum,
                           ULONG ulPacketOctets );

ULONG PPP_GetVerboseSwitch(PPPDEBUGINFO_S *pstPppDebugInfo,USHORT usProtocol);

VOID PPP_Debug_LQMPacket(PPPINFO_S* pstPppInfo, 
                         UCHAR *pucPacket, 
                         ULONG ulLen,
                         USHORT usProtocol, 
                         UCHAR ucIsInPacket);
/* ����LQM�ӿ���Ϣ */
ULONG PPP_ProcessLQMNeg(ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPP_ProcessLQMPeriod(ULONG ulIfIndex, USHORT usLqrPeriod);
ULONG PPP_ProcessLQMLimit(ULONG ulIfIndex, ULONG ulCloseValue,ULONG ulResumeValue);

ULONG PPP_SetIpcpNegoDns (ULONG ulIfIndex, ULONG ulSetYes);
ULONG PPP_AddrCheck(ULONG ulAddr);

/*add by wuhailan for A82D18512, 2007-8-2.����MP�ն�������һ���Լ�⿪��*/
ULONG PPP_SetMpEDConsistent(ULONG ulSetYes);
ULONG PPP_GetMpEDConsistent(VOID);

ULONG PPP_SetInterfaceNegoOsicp_PT(ULONG ulIfIndex, ULONG ulNegoOSICP);
ULONG PPP_GetInterfaceNegoOsicp_PT(ULONG ulIfIndex, ULONG *pulNegoOSICP);

ULONG PPP_ResetIPCP (ULONG ulIfIndex);
/* Added by hanna55555, VISPV1R8C01 for ppp-link support ipv6, 2009/3/20 */
ULONG PPP_ResetIP6CP (ULONG ulIfIndex);
/*End of Added by hanna55555, 2009/3/20 */
ULONG PPP_ResetOSICP (ULONG ulIfIndex);

extern VOID PPP_RemoveWarning(PPPINFO_S *pstPppInfo, USHORT ulMsgType);

extern ULONG PPP_ProcessIPHCUniDirection(ULONG ulIfIndex, ULONG ulEnable);
ULONG PPP_PPI_SetVerifySwitch(ULONG ulSwitch, ULONG ulPeriod, ULONG ulIfNum);
extern ULONG PPP_Set_NegTimeoutWaring(ULONG ulTime);
extern ULONG PPP_Get_NegTime(ULONG *pulTime);

VOID PPP_PPI_VerifyInfo();
ULONG PPP_PPI_VerifyInfobyIndex(ULONG ulIfIndex);
ULONG PPP_PPI_GetVerifySwitch (PPPVERIFYSWITCH_S *pstPppVerifySwitch);
VOID PPP_InsertArray(ULONG ulArray[], ULONG ulArrayCurNUM, ULONG ulValue);

VOID PPP_RecordDownReason(PPPINFO_S *pstPppInfo, USHORT usProtoType, USHORT usDownReason);
extern ULONG PPP_SetNegoMagicNum(ULONG ulIfIndex, ULONG ulSetYes);
extern ULONG PPP_GetNegoMagicNum(ULONG ulIfIndex, ULONG *pulSetYes);
extern ULONG PPP_SetPppSelfLoop(ULONG ulIfIndex, ULONG ulSetYes);
extern ULONG PPP_GetPppSelfLoop(ULONG ulIfIndex, ULONG *pulSetYes);

ULONG PPP_SetNcpResendTime(ULONG ulIfIndex, ULONG ulTime);
ULONG PPP_GetNcpResendTime(ULONG ulIfIndex, ULONG *pulTime);

ULONG PPP_SetMaxLoopbackDetectTime(ULONG ulTime);
ULONG PPP_GetMaxLoopbackDetectTime(ULONG *pulTime);

VOID PPP_DelNcpResendTimer(PPPINFO_S *pstPppInfo);
VOID PPP_NcpResendPkt(PPPFSM_S *pstFsm);
VOID PPP_ProcNcpResendTimeOut(ULONG ulIfIndex);
VOID PPP_ShowConfigInfo(CHAR *szName,ULONG ulFlag);

ULONG PPP_EchoInfo_DownLoad2Phy(PPPFSM_S *pstFsm, USHORT usCmd, VOID *pData);
ULONG PPP_HandleEchoEvent(PPPINFO_S *pstPppInfo, ULONG ulCmd);
ULONG PPP_GetLcpEchoInfo(ULONG ulIfIndex, ULONG ulCmd, VOID  *pData);
ULONG PPP_SetDealAcfcPfcFlag(ULONG ulIfIndex, ULONG ulFlag);
ULONG PPP_GetDealAcfcPfcFlag(ULONG ulIfIndex, ULONG *pulFlag);
ULONG PPP_GetPapUserName(ULONG ulIfIndex, UCHAR *pucUserName);
ULONG PPP_GetChapUserName(ULONG ulIfIndex, UCHAR *pucUserName);
ULONG PPP_GetPppDownInfo(ULONG ulIfIndex, ULONG ulProtocolType, PPPDOWNINFO_S *pstPppDownInfo);

#ifdef __cplusplus
}
#endif

#endif      /* end of _PPP_FUNC_H_ */

