

#ifndef _MP_SH_INIT_H
#define _MP_SH_INIT_H

#ifdef  __cplusplus
extern  "C"{
#endif


ULONG MP_SH_Init();
ULONG MP_SH_DeInit();
ULONG MP_DDR_GetFatherIfIndex(IFNET_S *pstIfnet);
VOID  MP_DDR_ResetIdleTimeout(IFNET_S *pstSonIf);
ULONG MP_DDR_IoCtl(IFNET_S * pstIf, ULONG sCommand, CHAR * pszDataLink);
ULONG MP_QUE_EnDropQue(MBUF_S *pMBuf);

extern VOID PPP_ShowDebugInfo( char *szString, ULONG ulLen);

extern struct ComponentInfo m_CompMPInfo;

#ifdef  __cplusplus
}
#endif

#endif/*#ifndef _MP_SH_INIT_H*/

