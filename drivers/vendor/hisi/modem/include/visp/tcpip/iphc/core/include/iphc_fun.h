
 
#ifndef _IPHC_FUN_H_
#define _IPHC_FUN_H_


#ifdef  __cplusplus
extern "C"{
#endif

/* Added by Sun Mo 44939 2005-09-21 */
/*----------------    �����غ���    ----------*/
ULONG IPHC_QueryInterface (IUnknown *This, COMP_IID iid, LPVOID *ppvObj);

ULONG IPHC_Init_Com(VOID);
ULONG IPHC_Activate_Com(VOID);
ULONG IPHC_SetModuleInfo(struct tagIPHC_Mod_Info *pstMInfo);

ULONG IPHC_RegShellApi(struct tagIPHC_SHELL_CALLBACK_SET *pstCallBkSet);

ULONG ImplIPHCFactoryQueryInterface(IUnknown *This, COMP_IID iid, LPVOID * ppvObj);
ULONG ImplIPHCFactoryCreateInstance(IComponentFactory *This,  COMP_IID iid, VOID **ppvObj );

/*----------------    ���������ú���    -------*/
ULONG IPHC_ProcessTcpDebug(ULONG ulSetYes);
ULONG IPHC_ProcessNonTcpDebug(ULONG ulSetYes);
/* End of add of Sun Mo 44939 2005-09-21 */

struct tagIPHC_COMPRESSION_CONTEXT *IPHC_Initiate( ULONG ulIfIndex, 
                                                   ULONG CCOMPANY,
                                                   ULONG DELETE_UDP_CHECKSUM,
                                                   PPP_IPCP_OPTION_S *pstGotOption, 
                                                   PPP_IPCP_OPTION_S *pstHisOption);


VOID IPHC_TCPRelease(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
/* Modified by Sun Mo 44939 2005-10-08 */
/* VOID IPHC_RTPRelease(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context); */
VOID IPHC_NonTCPRelease(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
/* End of modify of Sun Mo 44939 2005-10-08 */
struct tagIPHC_COMPRESSION_CONTEXT *IPHC_Release(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);

VOID IPHC_TimerCall(VOID *pArg);
/* End of modification */

 /* Modified by Sunmo(44939) for A82D02325, 2006-06-19 */
 /* ����������ֵ��VOID��ΪULONG */
ULONG IPHC_TCPCidCheck(struct tagIPHC_COMPRESSION_CONTEXT *pContext);
UCHAR IPHC_TCPCidRequest(struct tagIPHC_COMPRESSION_CONTEXT *pContext,struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *pContest_Struct);
VOID IPHC_RTPCidCheck(struct tagIPHC_COMPRESSION_CONTEXT *pContext);
USHORT IPHC_RTPCidRequest(struct tagIPHC_COMPRESSION_CONTEXT *pContext,struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *pContest_Struct);
struct tagIPHC_TCP_CONTEXT_TABLE_STRUCT *IPHC_SearchTCPContext(struct tagIP *pIP,struct tagTCPHDR *pTCP,struct tagIPHC_COMPRESSION_CONTEXT *pContext,UCHAR *pFind);
struct tagIPHC_NON_TCP_CONTEXT_TABLE_STRUCT *IPHC_SearchRTPContext(struct tagIP *pIP,struct tagUDPHDR *pUDP,struct tagRtp_Hdr_t *pRTP,struct tagIPHC_COMPRESSION_CONTEXT *pContext,UCHAR *pFind);
USHORT IPHC_Compression(MBUF_S **ppMbuf,struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context,USHORT usIPHC_Type);
USHORT IPHC_Decompression(MBUF_S **ppMbuf,struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context,USHORT usIPHC_Type);
LONG IPHC_DebugAll(VOID);
LONG IPHC_NoDebug(VOID);
LONG IPHC_ShowDebug(CHAR *pszStatusStr, ULONG ulMaxLen, ULONG ulIfIndex, 
                      ULONG *pulWaitListIndex, ULONG ulInterface);
VOID IPHC_DebugOutString (CHAR * szStr);
ULONG IPHC_RegToIC (VOID);
VOID IPHC_Init ( VOID );
/* Added by Sunmo 44939 2006-04-26 */
ULONG IPHC_ProcessNonTcpContextRefreshTime(ULONG ulTime);

VOID IPHC_TcpStatClear(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
VOID IPHC_NonTcpStatClear(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
ULONG IPHC_GetIfIPHCStatistics(ULONG ulIfIndex, TCPIP_IPHC_STATISTICS_S *pstIPHCStatistics);

/* End of addition */


#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */


#endif
/* end of iphc_fun.h */

