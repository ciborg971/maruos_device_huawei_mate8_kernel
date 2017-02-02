/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                         IF_SH_FUN.H  
 *
 *  Project Code: VISP1.5
 *   Module Name: IFNET
 *  Date Created: 2004/03/08
 *        Author: luohanjun
 *   Description: 
 *               
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2004/03/08      luohanjun       Create File
 *  2006/03/30      liai            Adjust for D00654
 *  2006/04/21      liai            Adjust for D00878
 *
 ************************************************************************/

#ifndef _IF_SH_FUN_H_
#define _IF_SH_FUN_H_

#ifdef __cplusplus
extern "C"{
#endif

#define IF_IPC_QUE_LENGTH               9000    /* IPC��Ϣ���г��� */


/********************IF_SH_INIT�ļ���������begin *********************/
ULONG IF_Sh_RegApp();
ULONG IF_Init(VOID);
ULONG IF_Sh_RegIFClass();
VOID IF_Sh_RegNotify();

extern struct IIF_IFNET_ComIntFUNVtbl* g_pstIfFunVtbl;
extern struct IIF_IFNET_ComIntCFGVtbl* g_pstIfCfgVtbl;

extern struct IIF_MP_ComIntFUNVtbl* g_pstIfMPFunVtbl;
extern struct IIF_PPPOE_CLIENT_ComIntFUNVtbl* g_pstIfPOECFunVtbl;

extern struct IIF_COMP_POES_ComIntFUNVtbl* g_pstIfPoesFunVtbl;  /* POES���������� */
extern struct IIF_COMP_POES_ComIntCFGVtbl* g_pstIfPoesCfgVtbl;  /* POES���������� */
extern struct IIF_COMP_PPP_ComIntFUNVtbl* g_pstIfPppFunVtbl;    /* PPP���������� */
extern struct IIF_IPV4_DHCP4C_ComIntFunVtbl *g_pstIfnetDHCP4CFunVtable; /* DHCP4C���������� */

/* L2IF FUN VTBL */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl  *g_pstIfnetL2ifFunVtbl;

extern struct IIF_COMP_TRUNK_ComIntFUNVtbl* g_pstIfTRUNKFunVtbl;   /* Trunk���������� */
extern struct IIF_COMP_TRUNK_ComIntCFGVtbl*  g_pstIfTrunkCfgVtbl ;

extern struct IIF_COMP_ETHERNET_ComIntFUNVtbl  *g_pstIfEthFUNTable ;
extern struct IIF_COMP_ETHERNET_ComIntCFGVtbl  *g_pstIfEthCFGTable;

extern struct IIF_COMP_L2IF_ComIntFUNVtbl  *g_pstIfnetL2ifFunVtbl;/* L2IF ģ�麯����� */

/* IFNETģ���1ag����������ָ�� */
extern struct IIF_COMP_OAM1AG_ComIntFUNVtbl *g_pstIfnetOam1agFunTable ;

/********************IF_SH_INIT�ļ���������end *********************/


/********************IF_SH_FUN�ļ�����begin *********************/
ULONG IF_Sh_RegCallCenter();

CHAR* IF_Sh_GetMsg_Router_En(ULONG ulIndex);

ULONG IF_Sh_OutStringWait( ULONG ulExecID, CHAR * szOutString, ULONG * ulCurLine );

ULONG KRT_Link_Msg_Send (VLINKSTATUS_S *pstIFNETMsg);
ULONG KRT_Link_Msg6_Send (IFVLINKENTRY6_S *pstIFNETMsg);

ULONG IF_Sh_LinkIOCtl(ULONG ulIfIndex, ULONG ulCmd, CHAR * pData );

ULONG IF_Sh_LinkUpIOCtl(ULONG ulProtocol,ULONG ulIfIndex,ULONG ulCmd,CHAR * pData);

VOID IF_ShowInterface();
ULONG IF_ShowInterfacebyIfindex(ULONG ulIfIndex);

ULONG IF_NotifyMPDeleteIf(ULONG ulIfIndex); /*֪ͨMP�ӿ�ɾ��*/
ULONG IF_GetInterfacebyIfindex(ULONG ulIfIndex, ULONG ulBufLen, CHAR *szBuf, ULONG *pulLen);

ULONG IF_NotifyBfdDeleteIf(ULONG ulIfIndex);

/********************* IF_SH_FUN�ļ�����end *********************/


/*����ΪIfnet ShellҪ�õ����ⲿ����*/
extern ULONG TCPIP_Link_Msg_Send(VLINKSTATUS_S *pstIFNETMsg); /*���亯��*/
extern ULONG TCPIP_GetATMLinkIntVTable(VOID** ppstLinkInt); /*��ȡATM�ӿڳ�ʼ���ӿڵ����亯��*/
extern ULONG TCPIP_Link_Msg6_Send(IFVLINKENTRY6_S *pstIFNETMsg6);

#ifdef __cplusplus
}
#endif

#endif /* _IF_SH_FUN_H_*/

