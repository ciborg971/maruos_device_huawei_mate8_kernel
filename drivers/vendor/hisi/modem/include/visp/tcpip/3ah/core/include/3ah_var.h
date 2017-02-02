/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              3ah_var.h
*
*  Project Code: VISPV100R007
*   Module Name: ETH OAM 3AH  
*  Date Created: 2008-2-28
*        Author: LY(57500)
*   Description: 3AHģ���������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2008-2-28  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _3AH_VAR_H_
#define _3AH_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

/* ̽������Ĭ��ֵ,��λms,ʹ��ȫ�ֱ�����������Ǻ���Ҫ��Ϊ��ST���Է��� */
extern ULONG g_ulDefaultDetectIntervar;  

/* �Զ˳�ʱ���ʱ��,5��̽������             */
extern ULONG g_ulDefaultlostLinkTime;

/* ��������/��ֹ������Ӧ��ʱʱ��,��λms     */
extern ULONG g_ulLbWaitRspTime;

/* 3AHģ���IFNET����������ָ�� */
extern struct IIF_IFNET_ComIntFUNVtbl          *g_pstOam3ahIfnetFunTable;

/* 3AHģ���trunk����������ָ�� */
extern struct IIF_COMP_TRUNK_ComIntFUNVtbl     *g_pstOam3ahTrunkFunTable;

/* 3AHģ���etharp����������ָ�� */
extern struct IIF_COMP_ETHERNET_ComIntCFGVtbl  *g_pstOam3ahEthCfgTable;

/* 3AHģ��L2IF�������ָ�� */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl *g_pstoam3ahL2ifIntFunTbl;

/* 3AHģ��vrrp�������ָ�� */
extern struct IIF_COMP_VRRP_ComIntCFGVtbl *g_pstoam3ahVrrpCfgTbl;

/* 3AHģ���SyncE����������ָ�� */
extern struct IIF_COMP_SYNCE_ComIntFUNVtbl     *g_pstOam3ahSyncEFunTable;

/* ��ȡ�ײ��֡�ĺ���ָ�� */
extern GET_PHY_ERROR_FRAME_HOOK_FUNC g_pfGetPhyErrFrm;
    
/* �·������¼������ĺ���ָ�� */
extern SET_LINK_EVENT_WINTHRSH_HOOK_FUNC g_pfSetLinkEvtParam;

/* ֧��64λ�·������¼������ĺ���ָ�� */
extern SET_LINK_EVENT_WINTHRSH_EX_HOOK_FUNC g_pfSetLinkEvtParamEx;

/* ���ط���˱��Ľ��մ����� */
extern LBINPUT_HOOK_FUNC       g_pfLbRemoteInputFunc;

/* ������Ӧ�˱��Ľ��մ����� */
extern LBINPUT_HOOK_FUNC       g_pfLbLocalInputFunc;

extern OAM3AH_ORG_SPEC_NOTIFY_HOOK_FUNC g_pfOrgSpecNotify;

/* ��Э��ಥphysical��ַ */
extern UCHAR g_aucSlowProtocolMacAddr[MACADDRLEN];

/* 3AHģ����Ϣ */
extern OAM3AH_MOD_INFO_S g_stOam3ahModInfo;

/* 3AH�ӿڿ��ƿ�����   */
extern DLL_S *g_pst3ahPortInfoList;

/* ���Ĵ���ʱ�Ӳ���ע�ắ�� */
extern DEALPKT_TIMETEST__HOOK_FUNC g_pfDealPktTimeTest;

/* ��Ϊphysical��ַ��,��䵽��ϢTLV��OUI�ֶ���   */
extern UCHAR g_aucHuaweiOui[][3];

/* OAMPDU��verndor specific information �ֶγ�ʼֵ */
extern ULONG g_ulVendorSpecInfo;

/* 3ah���õ���̫�㲥��ַ */
extern UCHAR g_szEtherBroadcastAddr_3ah[MACADDRLEN];

/* ����3AH�״�Э�̲�ͨ������澯��ʱ�� */
extern ULONG g_ulOam3ahNegTime;

/* �״�Э�̲�ͨ������澯��ʱ��ID*/
extern ULONG g_ulOam3ahNegTimerId;

/* �״�Э�̲�ͨ������澯������ʱ������ 5s */
/* �û����õ�Э�̸澯ʱ�������5s�ı��� */
extern ULONG g_ulOam3ahNegPhyTimer;

extern ULONG g_ulOam3ahPktVlanSwitch;
/* End of Added by wangtong207740, 2012/10/22 */

/*Added by wangtong207740, MBSCҪ��3AH������ǲ�Ӱ��ӿ�����״̬, 2012/11/14 */
extern ULONG g_ulOam3ahBoardStateSwitch;
/* End of Added by wangtong207740, 2012/11/14 */

extern ULONG g_ulOam3ahWarnTraceFlag;

#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _3AH_VAR_H_   */

