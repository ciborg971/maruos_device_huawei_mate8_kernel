/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptp_shell.h
*
*  Project Code: IPCLOCK SERVER V100R002
*   Module Name: PTP SHELL
*  Date Created: 2008-06-02
*        Author: Wangchengyang
*   Description: PTP shellģ�麯��ͷ�ļ�����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-06-02      Wangchengyang       Create
*
*******************************************************************************/
#ifndef _PTP_SHELL_H_
#define _PTP_SHELL_H_

#ifdef __cplusplus
extern "C" {
#endif

extern UCHAR g_ucDscpPriority;
 
/* Added by dutianyi00217007, MANAGEMENT MESSAGE�ص������� */
extern PTP_GetInManagePkt_Func g_pfPtpManagePkt;
/* End of adding by dutianyi00217007, MANAGEMENT MESSAGE�ص������� */

ULONG PTP_Socket_Init (ULONG ulEventFlag);

ULONG PTP_Shell_GetPreConfig(ULONG *pulClockType, ULONG *pulSoftMode, ULONG *pulTaskPri);

ULONG PTP_Shell_SocketProcess (UINTPTR *pAsynMsg);

ULONG PTP_Shell_SndEventMsg (UCHAR *pucBuffer, ULONG ulPacketLength, ULONG ulPtpMsgType, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_Shell_RcvEventMsg (UCHAR *pBuffer, ULONG packetLen);

ULONG PTP_Shell_RcvGeneralMsg (PTP_VRF_NODE_S *pstVrfNode, UCHAR *pBuffer, ULONG ulPacketLen);

ULONG PTP_Shell_SndGeneralMsg (UCHAR *pucBuffer, ULONG ulPacketLength, ULONG ulPtpMsgType, PTP_ADDRINFO_S *pstAddrInfo);

ULONG PTP_SetSocketMultiCast (ULONG ulPortNumber);

ULONG PTP_SetSocketTos (PTP_VRF_NODE_S *pstVrfNode, UCHAR ucDscp);

ULONG PTP_SetSocketSrcAddr (USHORT usPtpPortNumber,PTP_PORT_ADDR_S *pstPortAddr);

ULONG PTP_SetSocketSrcAddrCommon(USHORT usPtpPortNumber, PTP_PORT_ADDR_S *pstPortAddr, ULONG ulVrfIndex);

/*Added by xujun-wangchengyang57575-62830 for VISPV1R8C01, 2009/3/19 */
ULONG PTP_Shell_RcvMsgWithMAC (MBUF_S *pstMBuf);

ULONG PTP_Que_Write(PTP_TMSG_S* pstPtpMsg);

ULONG PTP_Que_Read(PTP_TMSG_S * pstPtpMsg);

VOID PTP_AddrToStr(PTP_PORT_ADDR_S *pstPortAddr,CHAR *pszBuf);

VOID PTP_Que_Free(ULONG ulQueId);


ULONG PTP_Shell_RcvGeneralMsgWithMAC(UCHAR *pBuffer, ULONG ulPacketLen,ULONG ulIfIndex);
/*Mod End*/
/* End of Added by xujun-wangchengyang57575-62830, 2009/3/19 */

ULONG PTP_InetAddr(CHAR *pIpChar);
ULONG PTP_Shell_SndMsgWithMAC(UCHAR *pucBuffer, ULONG ulPacketLength);

/*�����ಥ���ַ*/
ULONG PTP_GetAllInterfaceIndex();
LONG PTP_SetSocketOption(ULONG ifindex,ULONG ulSrcAddr);
/* End of Added by zhangbo146309, 2010/8/28 */
/*Added by zhangbo146309, ����ಥ���ַ, 2010/9/8 */
/*qinyun&luogaowei 0��ַ���� 2011-12-12 start*/
/*TCIP.SafeModify.Delete, Modify by guojianjun178934, 2014/5/21*/
/*qinyun&luogaowei 0��ַ���� 2011-12-12 end*/

ULONG PTP_IP_GetIfindexbyIpAddr(ULONG ulIpAddr,ULONG *pulIfIndex, ULONG ulVrfIndex);
ULONG PTP_GetMainIpAddr(ULONG ulIfIndex,ULONG *pulMainAddr, ULONG *pulMainMask);
ULONG PTP_GetEtharpMac(ULONG ulIfIndex, UCHAR *pucMac);


/* End of Added by zhangbo146309, 2010/9/8 */
extern VOID PTP_InfoOutput(CHAR *pInfo);
extern ULONG PTP_GetPortInfo(ULONG ulIfIndex, ULONG *pulPortType, ULONG *pulPortNo);

extern ULONG IF_OpenIfConfigEntry(UINTPTR *pulWaitListHandle);
extern ULONG IF_GetIfConfigEntry(UINTPTR ulEntryWaitList, IFNET_S * pstIfConfig);
extern ULONG IF_CloseIfConfigEntry(UINTPTR ulWaitListHandle);
/* End added */

/* ����Ԥ����:�Ƿ�ʹ��ȫ��socket, ȡ�õ�ǰӦ��ʹ�õ�socketFd */
LONG PTP_GetShareSocketFd(PTP_VRF_NODE_S *pstVrfNode);
/* If the socket is a share socket( created by copysocket API ), close it  */
LONG PTP_FreeShareSocket(PTP_VRF_NODE_S *pstVrfNode);

/* �ж��Ƿ񱾵ص�ַ */
ULONG PTP_IPIsLocalAddr(ULONG ulSrcIp);

/* ����vrf��socket */
ULONG PTP_CreatSocketByVrf(ULONG ulVrfIndex, PTP_VRF_NODE_S *pstVrfNode);
ULONG PTP_CloseSocket(LONG lSocketFd);

ULONG PTP_SetDSCPPriorityByVrf(UCHAR ucPriority, CHAR *pcVrfName);

ULONG PTP_SetDSCPPriorityCommon(UCHAR ucPriority, ULONG ulVrfIndex);

#ifdef __cplusplus 
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTP_SHELL_H_    */ 



