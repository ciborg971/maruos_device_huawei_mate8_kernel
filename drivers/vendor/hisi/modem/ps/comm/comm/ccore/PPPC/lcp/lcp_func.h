
/************************************************************************
 *                                                                      *
 *                             lcp_func.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/03/27                                      *
 *  Author:             Deng Yi Ou                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           LCPģ��˽�к���˵��                             *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������LCPģ������˽�к���������                            *
 *                                                                      *
 ************************************************************************/

#ifndef      _LCP_FUNC_H_
#define      _LCP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

/* �ӿں��� */
VOID PPP_LCP_Init(PPPINFO_S *) ;
VOID PPP_LCP_ReceiveEventFromCore (VOID *pstLcpInfo, ULONG ulCmd, char *pPara) ;
VOID PPP_LCP_ReceivePacket (VOID *pstLcpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen) ;

/* �ص����� */
VOID PPP_LCP_resetci(PPPFSM_S *f) ;
USHORT PPP_LCP_cilen(PPPFSM_S *) ;
VOID PPP_LCP_addci(PPPFSM_S *, UCHAR *) ;
USHORT PPP_LCP_ackci(PPPFSM_S *, UCHAR *, ULONG) ;
USHORT PPP_LCP_nakci(PPPFSM_S *, UCHAR *, ULONG) ;
USHORT PPP_LCP_rejci(PPPFSM_S *, UCHAR *, ULONG) ;
UCHAR PPP_LCP_reqci(PPPFSM_S *, UCHAR *, ULONG *) ;
USHORT PPP_LCP_extcode(PPPFSM_S *, UCHAR , UCHAR , UCHAR *, UCHAR *, ULONG,ULONG ) ;/* Added by liutao 38563 at 2004-10-08 V800R002 for PPPѹ����ֲ */
VOID PPP_LCP_up(PPPFSM_S *) ;
VOID PPP_LCP_down(PPPFSM_S *) ;
VOID PPP_LCP_finished(PPPFSM_S *) ;
VOID PPP_LCP_starting(PPPFSM_S *) ;

/* �ڲ������� */
VOID PPP_LCP_SendEchoRequest(PPPFSM_S *) ;
VOID PPP_LCP_ReceiveEchoReply(PPPFSM_S *, UCHAR, UCHAR *, ULONG) ;
VOID PPP_LCP_EchoTimeOut(VOID *) ;
ULONG PPP_LCP_UpResetCi(PPPINFO_S *) ;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _LCP_FUNC_H_ */




