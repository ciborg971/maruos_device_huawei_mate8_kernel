/************************************************************************
 *                                                                      *
 *                             ppp_func.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/27                                      *
 *  Author:             Deng Yi Ou                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPP模块私有函数说明                             *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件包含了PPP模块所有私有函数的申明                            *
 *                                                                      *
 ************************************************************************/

#ifndef      _PPP_FUNC_H_
#define      _PPP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif    /* end of __cplusplus */

/****************外部函数声明******************/

/********** 初始化函数 ************/
ULONG PPP_CreateCB(ULONG, PPP_LUPPARA_S*) ;
ULONG PPP_DeleteCB(PPPINFO_S *) ;
ULONG PPP_InitCB(PPPINFO_S *) ;
ULONG PPP_InitConfigInfo(PPPINFO_S *) ;
ULONG PPP_ClearCB(PPPINFO_S *) ;
VOID PPP_ClearConfigInfo(PPPINFO_S *) ;
ULONG Ppp_UsmIoCtl(ULONG ulRPIndex, ULONG ulCmd, CHAR *pPara);
VOS_VOID PPPC_MsgTimerProc( struct MsgCB * pMsg );
VOS_VOID FWD_PppClearFreelist(VOS_UINT8 ucPppId);

VOID PPPGetPPPConfig(VOID);
#ifdef    __PRODUCT_TYPE_PDSN80
VOID PPPGetCompressConfig(VOID);
#endif
VOID PPP_L2tpUserNumAlarm(ULONG ulOldNum, ULONG ulNewNum);

extern VOID PPP_VSNCP_SetRenegoFlagForAllPDN(PPPINFO_S *pstPppInfo);
extern VOID A11_ReqNumSubProc(PPPINFO_S *pstPppInfo);
extern VOID PPP_ClearCB_IPCP(PPPIPCPINFO_S *pstIpcpInfo);
extern VOID PPP_ClearCB_IPV6CP(PPPIPV6CPINFO_S *pstPppIpv6cpInfo);
extern ULONG PPP_CompSelectDmpuDpe(UCHAR *pucDmpuId, UCHAR* pucDpeId);
extern VOS_VOID IPV6_PerfStatistic(ULONG ulMsgType);




extern UCHAR PPP_IPCP_IsSip(UCHAR *pPacket, ULONG *pulLen);
extern UCHAR PPP_IPV6CP_IsSip(UCHAR *pPacket, ULONG *pulLen);

extern ULONG PPP_CheckCcpLimit(VOID );
extern VOID PPP_Ipv4cp_Proc( PPPINFO_S *pstPppInfo );
extern VOID PPP_Ipv6cp_Proc(PPPINFO_S *pstPppInfo);
extern VOS_UINT32 PPP_GetConfigUserName
(
    VOS_UINT8                          *pucUserName
);

extern VOS_UINT32 PPP_GetConfigPassWord
(
    VOS_UINT8                          *pucPassWd
);
extern VOS_VOID *PPP_GetActPppHeadNode(VOS_VOID);

/********** 初始化函数 ************/

ULONG PPP_OmInitial(VOID);
VOID  PPP_OmMsgTrc(ULONG ulIndex, USHORT usProtocol, UCHAR* pMsg, ULONG ulLen, UCHAR ucflag, ULONG ulLnsIp, IMSI_S *pstImsi,  UCHAR ucEhrpdMode);

/********** 同异步转换 ************/
PMBUF_S *PPP_SynToAsy(PMBUF_S *pstSynMBuf, ULONG ulAsynAccm) ;
VOS_VOID PPP_AsyToSyn
(
    VOS_UINT32                          usLenToHandle,
    VOS_UINT8                          *pucAsynData,
    VOS_UINT8                          *ucIsFinished
);
VOS_UINT32 PPP_UlDataSynToAsy
(
    VOS_UINT8                          *pucDstData,
    VOS_UINT16                          usDstDataLen,
    VOS_UINT8                          *pucSrcData,
    VOS_UINT16                          usSrcDataLen,
    VOS_UINT32                          ulAccmValue
);

VOS_VOID FWD_PppRebuildIncompleteSliceStatInit();

/********** 同异步转换 ************/

/****************** 内核 *******************/
/* 与各部分接口函数 */
VOID PPP_Core_ReceiveEventFromProtocol (PPPINFO_S *, ULONG , CHAR *) ;
VOID PPP_Core_ReceiveEventFromShell(PPPINFO_S *, ULONG , CHAR *) ;
VOID PPP_Core_ReceivePacketFromShell(PPPINFO_S *, UCHAR *, UCHAR *, ULONG ) ;
VOID PPP_Core_RejectProtocol(VOID *, USHORT ) ;
VOID PPP_Core_ReceiveUnknownProtocol (PPPINFO_S *, UCHAR *, UCHAR *, ULONG, USHORT, UCHAR) ;
PPPFSM_S *PPP_Core_GetFsmByProtocol(VOID *, USHORT ) ;
ULONG PPP_SendUserInfo(PPPINFO_S* pstPppInfo, ULONG ulType);

/* 内部处理函数 */
VOID PPP_Core_Reset(VOID *) ;
ULONG PPP_Core_GetProtocol(PPPINFO_S *, UCHAR *, USHORT *) ;
VOID PPP_Core_NotifyUperLcpDown(PPPINFO_S *) ;
VOID PPP_Core_NotifyNcpDown(PPPINFO_S *pstPppInfo);
VOID PPP_Core_AuthUp(PPPINFO_S *pstPppInfo, UCHAR* pMsg) ;
LONG PPP_Core_NCPExist(ULONG  ulOriginIfindex,
                       USHORT usProtocol,
                       ULONG  ulIfIndex);
extern VOID ImsiToString( A11_IMSI_S stImsi ,UCHAR*szTemp);

/* 阶段转换函数 */
VOID PPP_Core_AuthenticatePhase(PPPINFO_S *) ;
VOID PPP_Core_DeadPhase(PPPINFO_S *) ;
VOID PPP_Core_EstablishPhase(PPPINFO_S *) ;
VOID PPP_Core_NetworkPhase(PPPINFO_S *pstPppInfo,UCHAR* pMsg) ;
VOID _PPP_Core_NetworkPhase(PPPINFO_S *) ;
VOID PPP_Core_TerminatePhase(PPPINFO_S *) ;
VOID ppp_Core_CcpInitiativeNego(PPPINFO_S *pstPppInfo);

/* 其他 */
ULONG PPP_GetMagicNumber(VOID) ;
ULONG PPP_SlaveBoardDiscardMsMsg(SDB_PDSN_RP_CONTEXT_S *pstRpContext, UCHAR ucSlaveReleaseFlg);
VOID PPP_CheckIsLcpTerminateMsg(PPPINFO_S *pstPppInfo, UCHAR *pucPacket, ULONG ulLen, UCHAR *pucLcpTerminateFlg);
VOID ShowCode(UCHAR *pucMsg, USHORT usLen);
PS_BOOL_ENUM_UINT8 PPP_VSNCP_IsPDNOpened(UCHAR ucPDNId);

/* 与L2TP接口函数 */
#if (VRP_MODULE_SEC_L2TP == VRP_YES)
VOID PPP_Core_L2tpPreNeg(PPPINFO_S *, CHAR *) ;
VOID PPP_Core_L2tpNeg(PPPINFO_S *pstPppInfo, CHAR *pOptionalPara);
LONG PPP_Core_L2tpPreNegLcp(UCHAR *, ULONG , UCHAR *, UCHAR *) ;
LONG PPP_Core_L2tpPreNegAuth(PPPINFO_S *, UCHAR *) ;
ULONG PPP_Shell_NotifyL2tpUp(ULONG ulIndex, L2TP_PPPPARA_S *pstPPPPara );
VOID PPP_L2tpUpPreProc(L2TP_PPPPARA_S * pstPPPPara, SDB_PDSN_RP_CONTEXT_S *pstContext,ULONG ulIndex);
ULONG PPP_SendMsgToL2tp( UCHAR ucMsgCode, UCHAR* pucMsg, ULONG ulMsgLen );

#endif

extern ULONG PDN_PDNGlobalIndexToPDNScIndex(ULONG ulPDNGlobalIndex);


/****************** 内核 *******************/

/***************** 状态机 ******************/
/* 对外接口 */
VOID PPP_FSM_ReceiveEvent (PPPFSM_S* pstFsm, ULONG ulCmd, CHAR *pPara) ;
VOID PPP_FSM_ReceivePacket (PPPFSM_S* pstFsm, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen,ULONG ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPP压缩移植 */
VOID PPP_FSM_Init(PPPFSM_S *pstFsm) ;

/* 外部事件处理 */
VOID PPP_FSM_Close(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_LowerDown(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_LowerUp(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_Open(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_TimeOut(VOID *pstFsm) ;
VOID PPP_FSM_VSTimeOut( VOID * );

/* 其他事件处理 */
VOID PPP_FSM_RXJ_Plus(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_RXJ_Sub(PPPFSM_S *pstFsm) ;

/* 报文处理 */
VOID PPP_FSM_ReceiveCodeRej(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, ULONG ulLen) ;
VOID PPP_FSM_ReceiveConfAck(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pPacket, ULONG ulLen) ;
VOID PPP_FSM_ReceiveConfNakRej(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR ucCode, UCHAR *pPacket, ULONG ulLen) ;
VOID PPP_FSM_ReceiveConfReq(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen) ;
VOID PPP_FSM_ReceiveProtocolRej(PPPFSM_S *pstFsm, UCHAR *pPacket, ULONG ulLen) ;
VOID PPP_FSM_ReceiveTermAck(PPPFSM_S *pstFsm, UCHAR ucId) ;
VOID PPP_FSM_ReceiveTermReq(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR ucPppId) ;
VOID PPP_FSM_ReceiveUnknownCode(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen) ;
VOID PPP_FSM_ReceiveVendorSpecific(PPPFSM_S *pstFsm, UCHAR ucId, UCHAR * pHead,UCHAR * pPacket,ULONG ulLen);

/* 报文发送 */
VOID PPP_FSM_SendConfigReq(PPPFSM_S *pstFsm) ;
VOID PPP_FSM_SendPacket(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen) ;
VOID PPP_FSM_SendPacketByCode(PPPFSM_S *pstFsm, UCHAR ucCode, UCHAR ucId) ;
VOID PPP_FSM_SendVendorSpecific(PPPFSM_S *pstFsm , UCHAR ucid,ULONG ulMagic, UCHAR ucKind);
/***************** 状态机 ******************/


/****************** 外壳 *******************/
/* 与内核接口函数 */
ULONG PPP_Shell_ReceiveEventFromCore(PPPINFO_S *, ULONG , CHAR *) ;
ULONG PPP_Shell_GetPacketFromCore(CHAR *, UCHAR *, UCHAR *, ULONG , USHORT ) ;
ULONG PPP_Shell_ReceiveNegoPacket(PMBUF_S *pMbuf, VOS_UINT8 ucPppId) ;
ULONG PPP_Shell_ReceiveStacPacket(PMBUF_S *pMbuf) ;
VOID PPP_Shell_ReceiveCompressPacket(PMBUF_S * pMbuf);
VOID PPP_Shell_ReceiveDecompressPacket(PMBUF_S * pMbuf);
ULONG PPP_Shell_SendDecompressPacket(PMBUF_S * pMbuf, USHORT usProtocol, ULONG ulIndex);
VOS_VOID PPP_CCP_Timeout(VOS_UINT32 ulPppId);  /* Added by heyajun kf1199 at 2004-08-05 V800R001C01B010 for BYHD03171 */

/* 与AAA接口 */
VOID PPP_Shell_ReceiveAAAResult(AAA_AUTHRSP_S *) ;

VOID PPP_Shell_GetPeerAddrTimeOut(VOID *pIfIndex);


/* 与上、下层的接口函数 */
ULONG PPP_Shell_ISLIoCtl(ULONG ulRPIndex, ULONG ulCmd, char *pPara);/* 提供给底层的控制函数接口 */


/* 内部处理函数 */
ULONG PPP_Shell_SendPacketToISL(PPPINFO_S *, PMBUF_S *, USHORT ) ;

/* 下发协商信息函数 */
VOID PPP_SendIpcpInfoProc(PPPINFO_S* pstPppInfo);


/***************** build run *******************/

/***************** Debug函数 ******************/
VOID PPP_Debug_FsmPacket(PPPINFO_S* , UCHAR * , ULONG , USHORT , UCHAR ) ;
VOID PPP_Debug_FsmEvent(PPPFSM_S*, ULONG ) ;
VOID PPP_Debug_FsmIllegalEvent(PPPFSM_S* , ULONG ) ;
VOID PPP_Debug_Error(PPPFSM_S *, USHORT , CHAR *) ;
VOID PPP_Debug_FsmStateChange(PPPFSM_S *, UCHAR ) ;
VOID PPP_Debug_CoreEvent(PPPINFO_S *pstPppInfo, USHORT usLogLevel,CHAR *pString) ;

CHAR *PPP_Debug_GetInterfaceName(PPPINFO_S *) ;
CHAR *PPP_Debug_GetTypeName(USHORT , UCHAR ) ;
CHAR *PPP_Debug_GetProtocolName(USHORT ) ;
CHAR *PPP_Debug_GetValueStr(UCHAR * , UCHAR ) ;
CHAR *PPP_Debug_GetProtoState(PPPINFO_S *, USHORT) ;
CHAR *PPP_Debug_GetCode(UCHAR ucCode) ;
CHAR *PPP_Debug_GetLcpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetIpcpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetCcpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetOsicpTypeName(UCHAR ) ;
CHAR *PPP_Debug_GetString(UCHAR *, UCHAR ) ;

VOID PPP_Debug_SetAllOptions( PPPDEBUGINFO_S *pstPppDebugInfo, UCHAR ucSet );
VOID PPP_Debug_SetOneOption( PPPDEBUGINFO_S *pstPppDebugInfo,
                             UCHAR ucSet,
                             ULONG ulType,
                             USHORT usProtocol) ;
UCHAR PPP_Debug_GetOption( PPPDEBUGINFO_S *pstPppDebugInfo,
                           ULONG ulType,
                           USHORT usProtocol) ;
/***************** Debug函数 ******************/

/***************** Mib 函数 ******************/
/*
#if(VRP_MODULE_SNMP == VRP_YES )
*/
ULONG PPP_MIB_LcpStatus( VOID * pMsgRcv, VOID **ppMsgSnd );
ULONG PPP_MIB_LcpConfig( VOID * pMsgRcv, VOID **ppMsgSnd );
ULONG PPP_MIB_IpcpStatus( VOID * pMsgRcv, VOID **ppMsgSnd );
ULONG PPP_MIB_IpcpConfig( VOID * pMsgRcv, VOID **ppMsgSnd );
ULONG PPP_MIB_Unsupport( VOID * pMsgRcv, VOID **ppMsgSnd );


/***************** Mib 函数 ******************/
ULONG PPP_NodeAdd(ULONG ulRpIndex, ULONG ulPDNIndex, UCHAR ucNodeType);
ULONG PPP_NodeDelete(ULONG ulRpIndex);
VOID PPP_NegoListProc(VOID* pPara);
ULONG PPP_PDNNodeAdd(ULONG ulRpIndex, ULONG ulPDNIndex, UCHAR ucNodeType);
ULONG PPP_PDNNodeDelete(ULONG ulPDNIndex);




extern VOS_VOID PPP_SubBoardDown( VOID );

extern ULONG PPP_CheckVjLimit(VOID);


extern ULONG PPP_CheckStacLimit(VOID );


extern VOS_VOID PPP_CompUserClear( VOID );
extern VOID PPP_CompUserNumAdd(PPPINFO_S *pstPppInfo, ULONG ulCompType);
extern VOID PPP_CompUserNumDel(PPPINFO_S *pstPppInfo, ULONG ulCompType);

extern VOS_VOID PPP_BkpCompUserSmooth( VOID );

extern LONG PPP_CompBinSelectDpe(LONG llow, LONG lhigh, ULONG ulSearchData);

//extern ULONG PPP_Shell_GetVpnIdByVpnName(UCHAR *pucVpnName, ULONG *pulVpnId);

VOID PPP_Core_IpcpV4FinProc( PPPINFO_S *pstPppInfo );
VOID PPP_Core_IpcpV6FinProc( PPPINFO_S *pstPppInfo );
ULONG PPP_GetUserTypeByIpv4cpReq(PPPINFO_S *pstPppInfo, UCHAR* pPacket,ULONG ulLen, ULONG* pulMsgType);
ULONG PPP_CopyIpv4cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, ULONG ulMsgLen);
ULONG PPP_CopyIpv6cpMsg(PPPINFO_S *pstPppInfo, UCHAR *pHead, UCHAR *pPacket, ULONG ulMsgLen);
VOID PPP_L2tpMsgProc(VOID *pstMsg, ULONG ulMsgCode);
extern ULONG Diam_AuthPPPRenegoRelCB(ULONG ulRPIndex);


extern VOID              SRPppCfgCompress( ULONG argc, CHAR * argv []   );
/* extern VOID              SRPppShowDebug( ULONG argc, CHAR * argv []   ); */
/* extern VOID              SRPppShowCBDetailInfo( ULONG argc, CHAR * argv []   ); */
/* extern VOID              SRPppShowCBInfo( ULONG argc, CHAR * argv []   ); */
/* extern VOID              SRPppShowInfo( ULONG argc, CHAR * argv []   ); */
extern VOID              StartPPPRego( ULONG argc, CHAR * argv []   );
extern VOID              PPP_PrintPerfVar( ULONG argc, CHAR * argv [] );
extern VOID              PPP_SetStubValue(ULONG argc, CHAR *argv[]);

extern VOID              PPP_ShowEcho( ULONG argc, CHAR * argv [] );
extern VOID              PPP_SetDebugInfo( ULONG argc, CHAR * argv [] );



extern ULONG PPP_VSNCP_FSM_DelRetransmitTimer(PPPFSM_S *pstFsm);
extern VOID PPP_VSNCP_FSM_SetRetransmitTimer(PPPFSM_S *pstFsm);

extern VOID PPP_EAP_NotifyDiamAuthReleaseForRenego(PPPINFO_S *pstPppInfo);


#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PPP_FUNC_H_ */





