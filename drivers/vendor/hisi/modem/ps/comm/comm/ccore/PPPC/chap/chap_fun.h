/************************************************************************
 *                                                                      *
 *                             chap_fun.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/05                                      *
 *  Author:             Zhu Fengzhi                                     *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           CHAPģ��˽�к���˵��                            *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������CHAPģ������˽�к���������                           *
 *                                                                      *
 ************************************************************************/


#ifndef      _CHAP_FUNC_H_
#define      _CHAP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

VOID PPP_CHAP_Init(PPPINFO_S *);
VOS_VOID PPP_CHAP_ChallengeTimeout(VOS_UINT32 ulPppId);
VOS_VOID PPP_CHAP_ResponseTimeout(VOS_UINT32 ulPppId);
VOID PPP_CHAP_AuthRspTimeout(VOID *);
VOID PPP_CHAP_Rechallenge(VOID *) ;
VOID PPP_CHAP_ClientLowerUp(PPPINFO_S *);
VOID PPP_CHAP_ServerLowerUp(PPPINFO_S *);
VOID PPP_CHAP_ReceiveEventFromCore (PPPINFO_S *, ULONG , CHAR *);
VOID PPP_CHAP_LowerDown(PPPINFO_S *);
VOID PPP_CHAP_ReceivePacket (PPPINFO_S *, UCHAR* , UCHAR* , ULONG );
VOID PPP_CHAP_ReceiveChallenge(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_CHAP_ReceiveResponse(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_CHAP_ReceiveAAAResult(AAA_AUTHRSP_S *);
VOID PPP_CHAP_ReceiveSuccess(PPPINFO_S *, UCHAR);
VOID PPP_CHAP_ReceiveFailure(PPPINFO_S *);
VOID PPP_CHAP_SendChallenge(PPPINFO_S *);
VOID PPP_CHAP_SendAAAAuthReq(PPPCHAPINFO_S *);
VOID PPP_CHAP_SendStatus(PPPINFO_S *, UCHAR);
VOID PPP_CHAP_GenChallenge(PPPCHAPINFO_S *);
VOID PPP_CHAP_SendResponse(PPPINFO_S *);
VOID PPP_CHAP_ReceiveUnknownCode(PPPINFO_S *);
SHORT PPP_CHAP_GenResponse(PPPAUTHMSG_S *);
VOID PPP_CHAP_DeleteTimer(PPPINFO_S *);

/*CHAP ���Ժ��� */
VOID CHAP_Debug_Packet(PPPINFO_S* , UCHAR *, ULONG , USHORT , UCHAR );
VOID CHAP_Debug_StateChange(PPPINFO_S *, UCHAR ,UCHAR );
VOID CHAP_Debug_Event(PPPINFO_S* , UCHAR );
VOID CHAP_Debug_Error(PPPINFO_S *, USHORT , CHAR *);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PAP_FUNC_H_ */



