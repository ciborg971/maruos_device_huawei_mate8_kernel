/************************************************************************
 *                                                                      *
 *                             pap_func.h                               *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2000/06/01                                      *
 *  Author:             Zhu Fengzhi                                      *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           PAPģ��˽�к���˵��                            *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2002 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   ����ļ�������PAPģ������˽�к���������                           *
 *                                                                      *
 ************************************************************************/

#ifndef      _PAP_FUNC_H_
#define      _PAP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */

VOS_VOID PPP_PAP_SendAuthReqTimeout(VOS_UINT32 ulPppId);
VOID PPP_PAP_ReceiveAuthReq(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_PAP_ReceiveAuthAck(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_PAP_SendAuthReq(PPPINFO_S *);
VOID PPP_PAP_ReceiveAuthNak(PPPINFO_S *, UCHAR *, UCHAR, ULONG);
VOID PPP_PAP_SendAAAAuthReq(PPPPAPINFO_S *);
VOID PPP_PAP_SendResponse(PPPINFO_S *, UCHAR, UCHAR, char *, USHORT);
/* �ӿں��� */
VOID PPP_PAP_Init(PPPINFO_S *);
VOID PPP_PAP_ReceiveEventFromCore (PPPINFO_S *, ULONG , char *);
VOID PPP_PAP_ReceivePacket (PPPINFO_S *, UCHAR* , UCHAR* , ULONG );

/*�ڲ�������*/
VOID PPP_PAP_ClientLowerUp(PPPINFO_S *);
VOID PPP_PAP_ServerLowerUp(PPPINFO_S *);
VOID PPP_PAP_LowerDown(PPPINFO_S *);
VOID PPP_PAP_ReceiveUnknownCode(PPPINFO_S *);
VOID PPP_PAP_ReceiveAAAResult(AAA_AUTHRSP_S *);
VOS_VOID PPP_PAP_WaitReqTimeout(VOS_UINT32 ulPppId);
VOID PPP_PAP_DeleteTimer(PPPINFO_S *);
VOID PPP_PAP_AuthRspTimeout(VOID *);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _PAP_FUNC_H_ */


