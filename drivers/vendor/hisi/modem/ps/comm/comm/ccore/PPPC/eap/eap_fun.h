/************************************************************************
 *                                                                      *
 *                             eap_fun.h                                *
 *                                                                      *
 *  Project Code:       VRP3.0                                          *
 *  Create Date:        2010/07/05                                      *
 *  Author:             WANGYONG                                        *
 *  Modify Date:                                                        *
 *  Document:                                                           *
 *  Function:           EAP模块私有函数说明                             *
 *  Others:                                                             *
 *----------------------------------------------------------------------*
 *                                                                      *
 * Copyright 2000-2010 VRP3.0 Team Beijing Institute HuaWei Tech, Inc.  *
 *                     ALL RIGHTS RESERVED                              *
 *                                                                      *
 *----------------------------------------------------------------------*
 *                                                                      *
 *   这个文件包含了EAP模块所有私有函数的申明                            *
 *                                                                      *
 ************************************************************************/

#if( VRP_MODULE_LINK_PPP == VRP_YES )

#ifndef      _EAP_FUNC_H_
#define      _EAP_FUNC_H_

#ifdef      __cplusplus
extern "C" {
#endif        /* end of __cplusplus */
VOID PPP_EAP_SendEAPFail(PPPEAPINFO_S *pstEapInfo, PPPINFO_S *pstPppInfo);
VOS_VOID PPP_EAP_WaitAuthRspTimeout(VOS_UINT32 ulPppId);
VOID PPP_EAP_DeleteTimer(PPPINFO_S *pstPppInfo);
VOS_VOID PPP_EAP_WaitEAPRspTimeout(VOS_UINT32 ulPppId);
VOID PPP_EAP_Init(PPPINFO_S *pstPppInfo);
VOID PPP_EAP_LowerDown(PPPINFO_S *pstPppInfo);
ULONG PPP_EAP_MallocEAP(PPPEAPINFO_S *pstEapInfo);
VOID PPP_EAP_ReAUTH(VOID *ulIndex);
VOID PPP_EAP_ReceiveDiamAAAResult(DIAM_AUTHRSP_S *pMsg);
VOID PPP_EAP_ReceiveEAPFailFromAAA(PPPINFO_S *pstPppInfo, 
                                        PPPEAPINFO_S *pstEapInfo, 
                                        DIAM_AUTHRSP_S *pMsg);
VOID PPP_EAP_ReceiveEAPRequestFromAAA(PPPINFO_S *pstPppInfo, 
                                        PPPEAPINFO_S *pstEapInfo, 
                                        DIAM_AUTHRSP_S *pMsg);
VOID PPP_EAP_ReceiveEAPResponse(PPPINFO_S *pstPppInfo, UCHAR *pPacket, UCHAR ucId, ULONG ulLen);
VOID PPP_EAP_ReceiveEAPSuccessFromAAA(PPPINFO_S *pstPppInfo, 
                                        PPPEAPINFO_S *pstEapInfo, 
                                        DIAM_AUTHRSP_S *pMsg);
VOID PPP_EAP_ReceiveEventFromCore (PPPINFO_S *pstPppInfo, ULONG ulCmd, CHAR *pPara);
VOID PPP_EAP_ReceivePacket(PPPINFO_S *pstPppInfo, UCHAR* pHead, UCHAR* pPacket, ULONG ulLen);
VOID PPP_EAP_SendAAAAuthReq(pstEapInfo, pstMsg, ulMsgLen);
VOID PPP_EAP_SendEAP(PPPINFO_S *pstPppInfo, UCHAR ucNewSeverStatus);
VOID PPP_EAP_ServerLowerUp(PPPINFO_S *pstPppInfo);


/*EAP 调试函数 */
VOID EAP_Debug_Error(PPPINFO_S *pstPppInfo, USHORT usLogLevel, CHAR *pString);
VOID EAP_Debug_Event(PPPINFO_S* pstPppInfo, UCHAR ucEvent);
VOID EAP_Debug_Packet(PPPINFO_S* pstPppInfo,
                                UCHAR *    pPacket,
                                ULONG      ulLen,
                                USHORT     usProtocol,
                                UCHAR      ucIsInPacket);
VOID EAP_Debug_StateChange(PPPINFO_S *pstPppInfo, UCHAR ucNewState, UCHAR ucType);

extern VOS_UINT32 g_ulDiamAuthPPPMsgQueId;         /* diam auth接收PPP消息的队列ID */
extern VOS_UINT32 g_ulDiamAuthMainTaskId;          /* diam auth 任务id */       
extern VOS_UINT32 g_ulDiamAuthPPPEvent;       /* DIAM AUTH任务事件位--PPP通知 */
VOID PPP_EAP_AlgoHmacSha(UCHAR *d, LONG ld, UCHAR *k, LONG lk, UCHAR *digest);
extern ULONG g_ulUserName256byteNum;
extern ULONG Diam_AUTHGetDynAAAInfoByIndex(USHORT usDynAAAIndex, UCHAR *pucHost, UCHAR *pucRealm, USHORT *pusDynPeerId);

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _EAP_FUNC_H_ */

#endif      /* #if( VRP_MODULE_LINK_PPP == VRP_YES ) */

