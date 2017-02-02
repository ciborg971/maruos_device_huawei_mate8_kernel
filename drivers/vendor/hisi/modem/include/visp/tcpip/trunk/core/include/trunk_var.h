/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              trunk_var.h
*
*  Project Code: VISP V100R006
*   Module Name: Trunk  
*  Date Created: 2006-11-27
*        Author: sunmo(44939)
*   Description: Trunkģ��ȫ�ֱ���������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2006-11-27  sunmo(44939)     Create the first version.
*
*******************************************************************************/

#ifndef _TRUNK_VAR_H_
#define _TRUNK_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/* ȫ��Trunk��Ϣ������ */
extern TRUNK_INFO_TBL_S *g_stTrunkInfoTbl;

/* TrunkϵͳMAC, ��¼Trunkģ���ϵͳMAC, ��LACPЭ��ʹ�� */
extern UCHAR g_ucSysMacAddress[6];

/* Trunkϵͳ���ȼ�, ��¼Trunkģ���ϵͳ���ȼ�, ��LACPЭ��ʹ�� */
extern USHORT g_usSysPri;

extern UCHAR g_ucWarningForPortRemove;
extern ULONG g_ulWarningForLacpDisable;


/* eth����macһ��Ԥ���� */
extern ULONG g_ulEthBakMac;

/* Trunkģ��LACP���Ĵ�����Կ���(0-�ر�, 1-��) */
extern ULONG g_ulDebugLacpPkt;
/* Trunkģ���������Ĵ�����Կ���(0-�ر�, 1-��) */
extern ULONG g_ulDebugOtherPkt;
/* Trunkģ��״̬����Ǩ��Ϣ���Կ���(0-�ر�, 1-��) */
extern ULONG g_ulDebugFsm;

/* Trunkģ������ʱ��ID */
extern ULONG g_ulTrunkGlobalTimerId;

/* Trunkģ����Ϣ */
extern TRUNK_MOD_INFO_S g_stTrunkModInfo;

/* Core��ʹ�õĻص������� */
extern TRUNK_SHELL_CALLBACK_SET_S g_stTrunkShellApi;

/* Trunkģ���IFNET����������ָ�� */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstTrunkIfnetFunTable;

/* Trunkģ���ETHARP����������ָ�� */
extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl *g_pstTrunkEthFunTable;

/* Trunkģ���AM4����������ָ�� */
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstTrunkAm4FunTable;

/* Trunkģ���DHCP4R����������ָ�� */
extern struct IIF_COMP_DHCP4R_ComIntCFGVtbl *g_pstTrunkDhcp4rCfgTable;

/* Trunkģ��OAM3AH ���������� */
extern struct IIF_COMP_OAM3AH_ComIntFUNVtbl *g_pstTrunkOam3ahFuncTable;

/* Trunkģ��OAM1AG ���������� */
extern struct IIF_COMP_OAM1AG_ComIntFUNVtbl *g_pstTrunkOam1agFuncTable;

/* Trunkģ��OAM1AG ���������� */
extern struct IIF_COMP_OAM1AG_ComIntCFGVtbl *g_pstTrunkOam1agCfgTable;

/* Trunkģ��L2IF ���������� */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl *g_pstTrunkL2ifFuncTable;

/* Trunk���������� */
extern struct IIF_COMP_TRUNK_ComIntCFGVtbl *g_pstTrunkCfgTable;

/*����SyncE������*/
extern struct IIF_COMP_SYNCE_ComIntFUNVtbl *g_pstTrunkSyncEFunVtbl;

extern struct IIF_COMP_NSR_ComIntFUNVtbl *g_pstNsrTrunkFunTable;

/* ȫ�ַַ����Թ��Ӻ���  */
extern TRUNK_DISTRIBUTE_HOOK_FUNC g_pfUserDistributeHookFunc;

extern TRUNK_VLANCHECK_HOOK_FUNC g_pfVlanCheckHookFunc;

/* ��Э��ಥphysical��ַ */
extern UCHAR g_ucSlowProtocolMacAddr[TRUNK_MACADDR_LEN];

/* ������Ϣ����ַ��� */
extern CHAR* g_pcFsmType[];
extern CHAR* g_pcTranStateReason[];
extern CHAR* g_pcFsmState[][7];

/* �ӿ����ӻ��Ƴ�trunkʱ֪ͨbfd,���и澯��� */
extern ULONG (*g_pfTrunkPortChangeNotifyBfd)(ULONG, ULONG);

/* �û�ע���ȡϵͳMAC��trunk MAC���� */
extern TRUNK_GETMACADDRRESS_HOOK_FUNC g_pfTrunkGetMacAddress;

/* �û�ע���ͷ�ϵͳMAC��trunk MAC���� */
extern TRUNK_FREEMACADDRRESS_HOOK_FUNC g_pfTrunkFreeMacAddress;

/* �û�ע��ĸ�����άֵ��ȡPort Id�Ĺ��Ӻ��� */
extern TRUNK_GETLACPPORTID_HOOK_FUNC g_pfLacpPortIdHook;

/* ��̫ȫ0��ַ */
extern UCHAR g_szEtherAllZeroAddr_trunk[MACADDRLEN];

/* ����Trunk�״�Э�̲�ͨ������澯��ʱ�� */
extern ULONG g_ulTrunkNegTime;

/* �״�Э�̲�ͨ������澯��ʱ��ID*/
extern ULONG g_ulTrunkNegTimerId;

/* �״�Э�̲�ͨ������澯������ʱ������ 5s */
/* �û����õ�Э�̸澯ʱ�������5s�ı��� */
extern ULONG g_ulTrunkNegPhyTimer;

/* TURNK LACP״̬�仯֪ͨ���Ӻ���*/
extern TrunkLacpChangeNotify g_pfTrunkLacpNotify;

extern ULONG g_ulTrunkNPMode ;
/* Add end */

extern ULONG g_ulTkParnterMacRefreshDropSwitch;

/*Added by wangtong207740, Trunk link loop back Lacp pdu, 2012/11/17 */
extern ULONG g_ulDealTrunkLinkLB;                  /* Trunk����·����LACP������ǿ���� */
/* End of Added by wangtong207740, 2012/11/17 */

extern ULONG g_ulTrunkMaxIfNums ;
extern ULONG g_ulDropNoLacpPkt ;

/* ����PTPV2���Ĳ��ͷ� */
extern ULONG (*g_pfETH_PTPV2_HOOK)(MBUF_S*);

#ifdef __cplusplus
}
#endif  /* end of __cplusplus */

#endif  /* end of _TRUNK_VAR_H_ */

