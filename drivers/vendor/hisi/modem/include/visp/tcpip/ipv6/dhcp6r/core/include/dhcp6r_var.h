/*******************************************************************************
*
*
*                Copyright 2011, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp6r_var.h
*
*  Project Code: VISP V2R3C06
*   Module Name: DHCP6R  
*  Date Created: 2011-7-19
*        Author: PBQ(RT24429)
*   Description: ��������
*
*-------------------------------------------------------------------------------
*  Modification  History
*  DATE          NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2011-7-27     PBQ(RT24429)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP6R_VAR_H_
#define _DHCP6R_VAR_H_

#ifdef __cplusplus
    extern "C"{
#endif  /* end of __cplusplus */

/* DHCP6R����๤����� */
extern IComponentFactory m_DHCP6R_CompFactory;

/* DHCP6Rģ��������ܺ�������� */
extern IIF_COMP_DHCP6R_ComIntFUN g_IComInt_DHCP6R_FUN;
extern IIF_COMP_DHCP6R_ComIntCFG g_IComInt_DHCP6R_CFG;

/* DHCP6Rģ�������Ϣ */
extern struct ComponentInfo m_CompDHCP6RInfo;

/* ���ע����Ϣ */
extern APP_INIT_INFO_S g_stDHCP6RAppInfo;

/* ȫ�ֿ��ƿ� */
extern DHCP6R_CFG_HEAD_S g_stDHCP6RCfgHead;
extern DHCP6R_DBG_S g_stDHCP6RDbg;

/* Relay�첽socket��ϢID */
extern ULONG g_ulDHCP6RSocketQId;

/* Relay����ģ��֪ͨ��ϢID  */
extern ULONG g_ulDHCP6RCntrlQId;

/* Relayģ�鹲�����ݻ����ź��� */
extern ULONG g_ulDHCP6RSm;

/* ָ��RELAY���ڱ�����յ�DHCP���ĵĻ�������ָ�� */
extern UCHAR *g_pucDHCP6RUdpBuf; 

/* Relayȫ��socket */
extern LONG  g_lDHCP6RSocket; 

/* ���Ĵ��������б��汨�Ľ��սӿ� */
extern ULONG g_ulInIfIndex;

/* DHCP6Rģ����Ϣ */
extern DHCP6R_MOD_INFO_S g_stDHCP6RModInfo;

/* Core��ʹ�õĻص������� */
extern DHCP6R_SHELL_CALLBACK_SET_S g_stDHCP6RShellApi;
    
/* DHCP6Rģ���IFNET����������ָ�� */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstDHCP6RIfnetFunTable;

/* DHCP6Rģ���IPV6����������ָ�� */
extern struct IIF_IP6_ADDR_HOST_CFGVtbl *g_pstDHCP6RIp6CfgTable;

/* DHCP6Rģ���IPV6����������ָ�� */
extern struct IIF_IP6_ADDR_HOST_FUNVtbl *g_pstDHCP6RIp6FunTable;

/* DHCP6Rģ���SOCKET6����������ָ�� */
extern struct IIF_IP6_SOCK_ComIntFUNVtbl *g_pstDHCP6RSock6FunTable;

/* dhcp6r���������� */
extern struct IIF_COMP_DHCP6R_ComIntFUNVtbl *g_pstDHCP6RFunTable;

/* dhcp6r���������� */
extern struct IIF_COMP_DHCP6R_ComIntCFGVtbl *g_pstDHCP6RCfgTable;

/* �ⲿģ�鶨����� */
/* VISP����ģ��ȫ�ֻ����ź��� */
extern ULONG g_ulSemForTightMods;

/* dhcp6r debug status */
extern CHAR *g_aszDHCP6RDbgStatus[];

/* dhcp������Ϣ�����ַ��� */
extern CHAR *g_aszDHCP6RPkt[]; 

/* dhcp6r�ӿ�ʹ��״̬�ַ��� */
extern CHAR *g_aszDHCP6REnableStatus[]; 

/* DHCP6Rʹ��ģʽ��Ӧ�������ַ��� */
extern CHAR *g_aszDHCP6RCfgMode[];

/* DHCP6R�м�ģʽ��Ӧ�������ַ��� */
extern CHAR *g_aszDHCP6RFwdMode[];

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _DHCP6R_VAR_H_ */

