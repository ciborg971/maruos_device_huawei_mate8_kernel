
 
 
#ifndef _IPHC_PUB_H_
#define _IPHC_PUB_H_


#ifdef    __cplusplus
extern "C"{
#endif

extern struct tagIPHC_COMPRESSION_CONTEXT *IPHC_Initiate( ULONG ulIfIndex, 
                                                          ULONG CCOMPANY,
                                                          ULONG DELETE_UDP_CHECKSUM,
                                                          PPP_IPCP_OPTION_S *pstGotOption, 
                                                          PPP_IPCP_OPTION_S *pstHisOption);

extern struct tagIPHC_COMPRESSION_CONTEXT *IPHC_Release(struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context);
extern VOID IPHC_TimerCall(VOID* pArg);

extern USHORT IPHC_Compression(MBUF_S **ppMbuf,struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context,USHORT usIPHC_Type);
extern USHORT IPHC_Decompression(MBUF_S **ppMbuf,struct tagIPHC_COMPRESSION_CONTEXT *pIPHC_Context,USHORT usIPHC_Type);
extern VOID IPHC_Init ( VOID );
extern ULONG IPHC_BuildRun(CHAR* szSectionName, CHAR** pszBuildRunInfo);

#ifdef    __cplusplus
}
#endif    /* end of __cplusplus */


#endif
/* end of cfm_def.h */

