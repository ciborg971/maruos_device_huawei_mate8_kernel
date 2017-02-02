
#ifndef _LLDP_SHELL_H_
#define _LLDP_SHELL_H_

#ifdef  __cplusplus
extern "C"{
#endif

/*SHELL�ж���Ĵ����룬ֵ��LLDP CBB����Ĵ�����ֵ����*/
#define LLDP_SHELL_TRUNK_NOT_CFG     (LLDP_ERR + 101)
#define LLDP_SHELL_TRUNK_CFG_ERR     (LLDP_ERR + 102)
#define LLDP_SHELL_TRUNK_GET_ERR     (LLDP_ERR + 103)

#define LLDP_SHELL_ETH_NOT_CFG       (LLDP_ERR + 104)
#define LLDP_SHELL_ETH_CFG_ERR       (LLDP_ERR + 105)
#define LLDP_SHELL_ETH_GET_ERR       (LLDP_ERR + 106)

#define LLDP_SHELL_IF_NOT_CFG        (LLDP_ERR + 107)
#define LLDP_SHELL_IF_CFG_ERR        (LLDP_ERR + 108)
#define LLDP_SHELL_IF_GET_ERR        (LLDP_ERR + 109)

#define LLDP_DEFALUT_TASK_PRIORITY   (100)

/* 2014-04-23 b71224: macro moved from core to shell */
#define MID_LLDP    MID_COMP_LLDP

/*Begin shell ������������Ҫ�û�����ʹ��*/
ULONG LLDP_Shell_Init(VOID);
ULONG LLDP_Shell_SendPacket(ULONG ulIfIndex,ULONG ulDataLen,  UCHAR *pucPkt);
ULONG LLDP_GetMac(ULONG ulIfIndex, UCHAR *pucMac);
ULONG LLDP_GetMtu(ULONG ulIfIndex, ULONG *pulMtu);
ULONG LLDP_GetTrunkId(ULONG ulIfIndex, ULONG *pulTrunkId);
ULONG LLDP_GetBridgeMac(ULONG ulIfIndex, UCHAR *pulBridgeMac);
ULONG LLDP_GetSysUpTime(ULONG *pulTimeValue);
VOID *LLDP_Malloc(ULONG ulMemInfo, ULONG ulMemSize);
ULONG LLDP_Free(VOID* pBuf);
ULONG LLDP_CreateMutex(CHAR *pMutexName, ULONG *pulMutexID);
ULONG LLDP_DeleteMutex(ULONG ulMutexID);
ULONG LLDP_Warning_OutPut(LLDP_REMOTE_TABLE_WARNING_S *pstWarning);
VOID LLDP_BeginPT();
VOID LLDP_EndPT();
VOID LLDP_InfoOutput(CHAR *pInfo);

VOID LLDP_DebugOutput(CHAR *pInfo);

ULONG LLDP_GetMacPhyCfgStatus(ULONG ulIfIndex, LLDP_MAC_PHY_CFG_INFO_S *stMacPhyCfg);


/*VOID LLDP_Log_Output(ULONG ulCode, ULONG ulLogLevel, ULONG ulLogType, VOID *ucMessage, 
                             ULONG ulPara1, ULONG ulPara2, ULONG ulPara3, ULONG ulPara4);*/

ULONG LLDP_GetIfIndexByName(CHAR *pszIfName);
ULONG LLDP_GetIfNameByIndex(ULONG ulIfIndex, CHAR *pszIfName);

/*End shell ������������Ҫ�û�����ʹ��*/


VOID LLDP_AddIfNotifyCallback(ULONG ulIfIndex);
VOID LLDP_DevMsgNotifyCallback(ULONG ulIfIndex, ULONG ulCmd, VOID *pData);
VOID LLDP_LinkMsgNotifyCallback(ULONG ulProtocol,ULONG ulIfIndex, ULONG ulCmd, CHAR *pcData);
VOID LLDP_DelIfNotifyCallback(ULONG ulIfIndex);
ULONG LLDP_IsL2IF(ULONG ulIfIndex);
ULONG LLDP_IsEthernetType(ULONG ulIndex);
ULONG LLDP_GetVlanHead(MBUF_S* pstMbuf, ULONG* pulVlanHead);
LONG LLDP_InetPToN(const CHAR *szSrcAddr, VOID *pDstAddr);
ULONG LLDP_Shell_TrunkReceivePacket(MBUF_S * pMBuf);
ULONG LLDP_PPI_MultiMac_Update(ULONG ulIfIndex, ULONG ulOptType, UCHAR *pszMacAddr, UCHAR *pszMacMask);
extern VOID VOS_T_Delay( ULONG ulMillisecond );

ULONG LLDP_GetPhyStatus(ULONG ulIfIndex, ULONG *pulPhyStatus);

ULONG LLDP_GetPreConfig(ULONG *pulTaskPri);

#ifdef  __cplusplus
}
#endif

#endif

