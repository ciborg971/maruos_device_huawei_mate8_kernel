/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4c_main.h
*
*  Project Code: VISP1.5
*   Module Name: DHCP client Module
*  Date Created: 2004-06-08
*        Author: tangcongfeng(36956)
*   Description: Header of dhcp_main.c
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                     DESCRIPTION
*  -----------------------------------------------------------------------------
*  2004-06-08  tangcongfeng(36956)     Creat the first version.
*
*******************************************************************************/

#ifndef _DHCP4C_MAIN_H_
#define _DHCP4C_MAIN_H_


#ifdef __cplusplus
extern "C"{
#endif /* __cplusplus */

extern ULONG VOS_Tm_Since1970(ULONG *pulRetTimeInSecHigh, ULONG *pulRetTimeInSecLow);
extern ULONG VOS_Tm_Now(ULONG *pulRetTimeInMillSecHigh, ULONG *pulRetTimeInMillSecLow);

extern DLL_S * g_pstDHCP4CSessionList;
extern DLL_S * g_pDHCP4CDebugFlagList;
extern DLL_S * g_pDHCP4CConfigList;

/* ȫ�ֵ��Կ��� */
extern ULONG g_ulDHCP4CDebugFlag;

extern LONG g_lDHCP4CSocket;

/* DHCP4Cģ��ȫ��tos */
extern UCHAR g_ucDhcpcTos;

/* ����dhpc4cģ���Ƿ���Խ���server���͹�����50/55/57ѡ��  */
extern ULONG g_ulDhcpcIgnoreOption;

/* DHCP4C ͳ����Ϣ */
extern DHCP4C_STATISTIC_S g_stDhcp4cStat;

VOID DHCP4C_ArpReq_TimeoutProc(ULONG ulIfIndex);
ULONG DHCP4C_BuildPacket(DHCP4C_SESSION_S *pstSession, ULONG ulMessgeType);
VOID DHCP4C_Discover_TimeoutProc(ULONG ulIfIndex);
LONG DHCP4C_fnValCmp(VOID * val, DLL_NODE_S * pNode);
LONG DHCP4C_fnXidCmp(VOID * val, DLL_NODE_S * pNode);
LONG DHCP4C_fnValFlagCmp(VOID * val, DLL_NODE_S * pNode);
LONG DHCP4C_fnConfigCmp(VOID * val, DLL_NODE_S * pNode);
VOID  DHCP4C_FSM_IPCnflctProc(DHCP4C_SESSION_S * pstSession);
ULONG DHCP4C_FSM_ProcBound(DHCP4C_SESSION_S * pstSession, ULONG ulFlag);
VOID DHCP4C_FSM_ProcAck(DHCP4C_SESSION_S * pstSession);
VOID DHCP4C_FSM_ProcIfPhyChange(DHCP4C_SESSION_S *pstSession, ULONG ulstatus);
ULONG DHCP4C_FSM_ProcInit(DHCP4C_SESSION_S * pstSession);
ULONG DHCP4C_FSM_ProcInitReboot(DHCP4C_SESSION_S * pstSession);
VOID DHCP4C_FSM_ProcNak(DHCP4C_SESSION_S * pstSession);
ULONG DHCP4C_FSM_ProcOffer(DHCP4C_SESSION_S * pstSession);
VOID DHCP4C_FSM_ProcStart(ULONG ulIfIndex, DHCP4C_SESSION_S * pstSession, ULONG ulOutIfIndex);
VOID DHCP4C_FSM_ProcStop(DHCP4C_SESSION_S * pstSession);
VOID DHCP4C_FSM_Receive(UINTPTR ulMsg[4]);
ULONG DHCP4C_FSM_Release(ULONG ulIfIndex);
ULONG DHCP4C_GetDhcpShowInfo(DHCP4C_DISPLAYINFO_S *pstDhcp4cInfo, ULONG ulIfIndex);
ULONG DHCP4C_GetDhcpShowInfo_PT(DHCP4C_DISPLAYINFO_S *pstDhcp4cInfo, ULONG ulIfIndex);
ULONG DHCP4C_FSM_Renew(ULONG ulIfIndex);
ULONG DHCP4C_GetXid(VOID);
VOID DHCP4C_ProcLeaseFromBak(DHCP4C_LEASE_S *stLease);
VOID DHCP4C_Lease_TimeoutProc(ULONG ulIfIndex);
DHCP4C_SESSION_S * DHCP4C_CreateSessionNode(ULONG ulIfIndex);
ULONG DHCP4C_CreateSocket(LONG *plOutputSocket);
ULONG DHCP4C_NotifyIfChange(ULONG ulIfIndex, ULONG ulEvent);
VOID DHCP4C_PKT_Decode(UCHAR *pucUdpBuf, ULONG usUdpBufLen, USHORT usVlanInfo);
ULONG DHCP4C_PKT_ParseOption(DHCP4C_PACKETINFO_S *stPacketInfo, UCHAR * pucBuf, ULONG ulLen);
ULONG DHCP4C_PKT_SendDecline(DHCP4C_SESSION_S *pstSession);
ULONG DHCP4C_PKT_SendDiscover(DHCP4C_SESSION_S *pstSession);
ULONG DHCP4C_PKT_SendPacket(DHCP4C_SESSION_S *pstSession);

ULONG DHCP4C_PKT_SendRelease(DHCP4C_SESSION_S *pstSession);
ULONG DHCP4C_PKT_SendRequest(DHCP4C_SESSION_S *pstSession);
VOID DHCP4C_Rebinding_TimeoutProc(ULONG ulIfIndex);
VOID DHCP4C_Renew_TimeoutProc(ULONG ulIfIndex);
VOID DHCP4C_Request_TimeoutProc(ULONG ulIfIndex);
ULONG DHCP4C_SetAddressStatus(ULONG ulIfIndex, ULONG ulTargetIPAddr);
ULONG DHCP4C_Enable_PT(ULONG ulIfIndex, ULONG ulFlag);
ULONG DHCP4C_EnableRmt_PT(ULONG ulLoopbackIfIndex, ULONG ulOutIfIndex);
ULONG DHCP4C_Disable_PT(ULONG ulIfIndex);
ULONG DHCP4C_Enable(ULONG ulIfIndex, ULONG ulFlag, ULONG ulOutIfIndex);
ULONG DHCP4C_EnableRmt(ULONG ulLoopbackIfIndex, ULONG ulOutIfIndex);
ULONG DHCP4C_Disable(ULONG ulIfIndex);
ULONG DHCP4C_Core_SetDhcpcCiaddr(ULONG ulIfIndex, ULONG ulCiaddr);
ULONG DHCP4C_SetDhcpcCiaddr(ULONG ulIfIndex, ULONG ulCiaddr);
ULONG DHCP4C_Core_SetDhcpcOptionsItem(ULONG ulIfIndex, UCHAR ucCode, UCHAR ucLen, UCHAR *pucValue);
ULONG DHCP4C_SetDhcpcOptionsItem(ULONG ulIfIndex, UCHAR ucCode, UCHAR ucLen, UCHAR *pucValue);
ULONG DHCP4C_Start(ULONG ulIfIndex);
ULONG DHCP4C_StartRmt(ULONG ulIfIndex, ULONG ulOutIfIndex);
ULONG DHCP4C_Stop(ULONG ulIfIndex);
ULONG DHCP4C_Renew_PT(ULONG ulIfIndex);
ULONG DHCP4C_Renew(ULONG ulIfIndex);
ULONG DHCP4C_Release(ULONG ulIfIndex);
ULONG DHCP4C_ProDbugFilter_PT(ULONG ulIfIndex,
                                ULONG ulDHCP4CDebugNo,
                                ULONG ulDHCP4CDebugType);
ULONG DHCP4C_ProDbugFilter(ULONG ulIfIndex,
                                ULONG ulDHCP4CDebugNo,
                                ULONG ulDHCP4CDebugType);
VOID DHCP4C_DeleteFromList(ULONG ulIfIndex);
VOID DHCP4C_ProcIfDeleted (ULONG ulIfIndex);
ULONG DHCP4C_SetDefaultAddr(ULONG ulIfIndex, ULONG ulIpAddr,ULONG ulSubnetMask);
ULONG DHCP4C_DelDefaultAddr(ULONG ulIfIndex);
ULONG DHCP4C_GetDefaultAddr(ULONG ulIfIndex, ULONG *pulIpAddr,ULONG *pulSubnetMask);
ULONG DHCP4C_GetDhcpcOptionsInfo(ULONG ulIfIndex, struct tagDHCP4C_OPTIONINFO *pstDhcpOptions);

ULONG DHCP4C_IsRecvUnicastBeforeCfgIP ( ULONG ulIfIndex );

extern TCPIP_PROCDHCP_HOOK_FUNC g_pstProcDhcpcPacketHook;
ULONG DHCP4C_ProcDhcpPacket_For_InterMediate(UCHAR *pucUdpBuf, ULONG ulRecvLen, USHORT usVlanInfo);

ULONG DHCP4C_SetTos(UCHAR ucTos);
ULONG DHCP4C_GetTos(UCHAR *pucTos);
ULONG DHCP4C_SetIgnoreOption(ULONG ulSetYes);
ULONG DHCP4C_GetIgnoreOption(ULONG *pulSetYes);
ULONG DHCP4C_BuildSendReleasePacket(ULONG ulIfIndex);
ULONG DHCP4C_GetArpByIpAddr(ULONG ulIfIndex);

/* дDHCP�����ļ��Ĺ��Ӻ��� */
extern LEASE_WRITE_HOOK g_pfDhcpLeaseWriteHook;
/* ��ȡDHCP�����ļ��Ĺ��Ӻ��� */
extern LEASE_READ_HOOK g_pfDhcpLeaseReadHook;

extern DLL_S * g_pstDHCP4CLeaseList;

VOID DHCP4C_UserCheckResult_TimeoutProc(ULONG ulIfIndex);
VOID DHCP4C_FSM_CfgConflictProc(DHCP4C_SESSION_S *pstSession);
ULONG DHCP4C_ProCfgCheck(DHCP4C_SESSION_S *pstSession);
ULONG DHCP4C_GetSessionIfIndexByPkt(UCHAR *pucUdpBuf, ULONG usUdpBufLen, ULONG *pulIfIndex);
ULONG DHCP4C_GetSessionIfIndexByPkt_PT(UCHAR *pucUdpBuf, ULONG usUdpBufLen, ULONG *pulIfIndex);

/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning Begin */
ULONG DHCP4C_SetDHCPVlanScanning(ULONG ulIfIndex, ULONG ulEnable, ULONG ulDelayTime);
ULONG DHCP4C_Core_SetDHCPVlanScanning(ULONG ulIfIndex, ULONG ulEnable, ULONG ulDelayTime);
ULONG DHCP4C_GetDHCPVlanScanning(ULONG ulIfIndex, ULONG *pulEnable, ULONG *pulDelayTime);
/* Added by y171195(z171897) 2010-11-03 for DHCP Vlan Scanning End */
ULONG DHCP4C_GetDhcp4cStatistic(DHCP4C_STATISTIC_S *pstStat);
ULONG DHCP4C_ClrDhcp4cStatistic(VOID);

/*******************************************************************************
*    Func Name: DHCP4C_GetSessionByIfIndex
* Date Created: 2012-08-17
*       Author: zhongyu206043
*  Description: ͨ��ulIfIndex��ȡ����Ӧ��DHCP4C_SESSION_S
*        Input: ULONG ulIfIndex:
*       Output: 
*       Return: �ɹ�  DHCP4C_SESSION_S��ַ
*               ʧ��  NULL
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2012-08-17   zhongyu206043           Create
*
*******************************************************************************/
DHCP4C_SESSION_S *DHCP4C_GetSessionByIfIndex(ULONG ulIfIndex);

extern ULONG  DHCP4C_DoFsmSelecting(UCHAR *pucUdpBuf, ULONG usUdpBufLen);

/*Added by guojianjun178934, ֧��DHCP46 68�˿ڶ�̬�����رչ���, 2014/11/21   ���ⵥ��:S-IP-C20-005-DHCP.001 */
ULONG DHCP4C_CloseSocket(LONG lSocket);
ULONG DHCP4C_Get_SessionCount(VOID);
ULONG DHCP4C_Check_CreateSocket(VOID);
VOID DHCP4C_Check_CloseSocket(VOID);
VOID DHCP4C_Delete_Session(VOID *pstSess);
VOID DHCP4C_Delete_AllSession(VOID);
/* End of Added by guojianjun178934, 2014/11/21   ���ⵥ��:S-IP-C20-005-DHCP.001 */

#ifdef __cplusplus
}
#endif /* __cplusplus */


#endif

