/************************************************************************
 *                                                                      *
 *                             ccp_func.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        			                                    *
 *  Author:                         			                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PPPµÄCCPÐ­ÒéÄ£¿éË½ÓÐº¯Êý                        *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 *  Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc. *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *                                                                      *
 ************************************************************************/

#ifdef		__cplusplus
extern		"C"{
#endif

#ifndef _CCP_FUNC_H_
#define _CCP_FUNC_H_
/********************************************************************/
VOID PPP_CCP_ReceiveEventFromCore (VOID *pstCcpInfo, ULONG ulCmd, char *pPara);

VOID PPP_CCP_SendResetReq(PPPINFO_S* pstPppInfo) ;

VOID PPP_CCP_init (PPPINFO_S* pstPppInfo);


VOID PPP_CCP_ReceivePacket (VOID *pstCcpInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen,ULONG ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */

USHORT PPP_CCP_cilen(PPPFSM_S *);         /* Return length of our CI */
VOID PPP_CCP_addci(PPPFSM_S *,  UCHAR *); /* Add our CI */
USHORT PPP_CCP_ackci(PPPFSM_S *, UCHAR *, ULONG);    /* Peer ack'd our CI */
USHORT PPP_CCP_nakci(PPPFSM_S *, UCHAR *, ULONG);    /* Peer nak'd our CI */
USHORT PPP_CCP_rejci(PPPFSM_S *, UCHAR *, ULONG);    /* Peer rej'd our CI */
UCHAR PPP_CCP_reqci(PPPFSM_S *, UCHAR *, ULONG *); /* Rcv CI */
VOID PPP_CCP_up(PPPFSM_S *);     /* We're UP */
VOID PPP_CCP_down(PPPFSM_S *);       /* We're DOWN */
VOID PPP_CCP_finished(PPPFSM_S *);
USHORT PPP_CCP_extcode(PPPFSM_S *, UCHAR , UCHAR , UCHAR *, UCHAR *, ULONG, ULONG);/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */

VOID PPP_CCP_disabled( PPPFSM_S *f ); /* dyo 99.8.23 */


VOID PPP_CCP_rresetreq (PPPFSM_S *f, UCHAR id, UCHAR *pHead, UCHAR *pPacket, ULONG ulLen,ULONG ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */
VOID PPP_CCP_rresetack (PPPFSM_S *f, UCHAR id, UCHAR *pPacket, ULONG ulLen,ULONG ulRPIndex) ;/* Modified by liutao 38563 at 2004-09-22 V800R002 for PPPÑ¹ËõÒÆÖ² */

VOID PPP_CCP_resetci( PPPFSM_S * );

VOID PPP_CCP_SendResetReqTimeout(VOID *pPppInfo);/*WGGSN_B03_L2TP_PPPC_COMP*/
/********************************************************************/



#endif /* _CCP_FUNC_H_ */

#ifdef		__cplusplus
}
#endif
