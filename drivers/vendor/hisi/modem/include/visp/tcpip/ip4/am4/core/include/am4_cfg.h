/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_cfg.h
*
*  Project Code: VISPV100R005
*   Module Name: AM4  
*  Date Created: 2006-01-04
*        Author: Li LiXiang
*   Description: ������AM4�е����ú���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������ 
*
*******************************************************************************/
 
#ifdef __cplusplus
extern "C" {
#endif


#ifndef _AM4_CFG_H_
#define _AM4_CFG_H_


/***************************************************************
*        ���������Ϣ����                                     *
***************************************************************/
#define IP_DEBUG_ON                           0x0001
#define IP_DEBUG_OFF                          0x0000

/* ϵͳ�ָ��ص���������ָ��,buildrun����ʹ�� */
extern AM4_SHELL_SYS_RECOVER_CALLBACK_PTR g_pfAm4ShIsSysRecovering;


ULONG IP_AM4_CfgProcIpAddr(ULONG ulNo, IFNET_S *pstIf,
                           ULONG ulIpAddr, ULONG ulSubnetMask,
                           ULONG ulSecondary);
ULONG IP_AM4_CfgProcIpAddrUnnumber(ULONG ulNo, IFNET_S *pstIf, IFNET_S *pstIfOfLendIn);
ULONG IP_AM4_CfgProcIpAddrNego(ULONG ulNo, IFNET_S* pstIf);
ULONG IP_AM4_CfgProcIpAddrDhcp(ULONG ulNo, IFNET_S* pstIf);
ULONG IP_AM4_CfgProcIpAddrDhcpRmt(ULONG ulNo, struct tagIFNET* pstIf, ULONG ulOutIfIndex);
ULONG IP_AM4_DHCPC_SetAddress(ULONG ulNo, ULONG ulIfIndex, ULONG ulIPAddr, ULONG ulMask);

ULONG IP_AM4_RegShIsSysRecoverCallback(AM4_SHELL_SYS_RECOVER_CALLBACK_PTR pfCallback);
ULONG IP_AM4_RegShReplaceConfigCallback(AM4_SHELL_REPLACE_CONFIG_CALLBACK_PTR pfCallback);
ULONG IP_ArpProxy_IsValidIpAddr( IFNET_S *pstIfNet, ULONG ulSrcIpAddr, ULONG ulDstIpAddr, ULONG ulVrfIndex);

ULONG IP_SendIPCCmdMsg(IPIFNET_S *pstIpIf, ULONG ulIsChange);

VOID IP_AM4_FindSubnetAddr(ULONG ulIPAddr,ULONG ulMask,ULONG ulIfIndex );
IPIFADDR_S*  IP_AddrTableMatch( ULONG ulIfAddr, ULONG ulVrfIndex);
IPIFADDR_S*  IP_AddrTableGetFirst ( ULONG ulVrfIndex );
IPIFADDR_S*  IP_AddrTableGetNext( ULONG ulIfAddr, ULONG ulVrfIndex);

/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP_Addr_OpenTable(UINTPTR *pulAddrCacheHandle,IPIFNET_S *pstIpIf,ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP_Addr_CloseTable(UINTPTR ulAddrCacheHandle);
/* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP_AddrGet(UINTPTR ulAddrCacheHandle,IPIFADDR_S  *pIfa,IPIFNET_S *pstIpIf,ULONG ulVrfIndex);
ULONG IP_Addr_OpenTable_PT(UINTPTR *pulAddrCacheHandle,IPIFNET_S *pstIpIf,ULONG ulVrfIndex);
ULONG IP_AddrGet_PT(UINTPTR ulAddrCacheHandle,IPIFADDR_S  *pIfa,IPIFNET_S *pstIpIf,ULONG ulVrfIndex);
/* End: VISP1.7C03 VRF qinyun , 2009-01-20 */
ULONG IP_AM4_CfgProcIpAddr_PT(ULONG ulNo, IFNET_S *pstIf, ULONG ulIpAddr, ULONG ulSubnetMask, ULONG ulSecondary);
ULONG IP_AM4_CfgProcIpAddrUniform(ULONG ulOperate,ULONG ulIfIndex,ULONG ulIpAddr,ULONG ulSubnetMask); 
ULONG IP_AM4_CfgProcIpAddrUnnumber_PT(ULONG ulNo, IFNET_S *pstIf,IFNET_S *pstIfOfLendIn);
ULONG IP_AM4_CfgProcIpAddrNego_PT(ULONG ulNo, IFNET_S* pstIf);
ULONG IP_AM4_RegShSrmJudgeFun(AM4_SHELL_RM_FUNC_PTR  *pfShCallback);
ULONG IP_IF_IsBroadcast_PT( ULONG ulIpAddr, struct tagIFNET *pstIfNet );
ULONG IP_Get_IF_MainIpAddrByIndex(ULONG ulIfIndex);
/* Begin: Added by a00900892 for AR-IP-MCCP.003 on 2014-09-10 */
ULONG IP_AM4_CfgProcIpAddrUniformEx(ULONG ulOperate,ULONG ulIfIndex,ULONG ulIpAddr,ULONG ulSubnetMask); 
/* End: Added by a00900892 for AR-IP-MCCP.003 on 2014-09-10 */

#endif/* end of _AM4_CFG_H_ */ 


#ifdef __cplusplus
}
#endif/* end of __cplusplus */

