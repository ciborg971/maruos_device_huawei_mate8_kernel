/*******************************************************************************
*
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              dhcp4r_var.h
*
*  Project Code: VISPV1R6
*   Module Name: DHCP4R  
*  Date Created: 2007-7-10
*        Author: LY(57500)
*   Description: ��������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*-------------------------------------------------------------------------------
*  2007-7-10  LY(57500)     Create the first version.
*
*******************************************************************************/
#ifndef _DHCP4R_VAR_H_
#define _DHCP4R_VAR_H_

#ifdef __cplusplus
extern "C"{
#endif

extern ULONG g_ulDHCP4RSocketQId;  /* Relay�첽socket��ϢID    */
extern ULONG g_ulDHCP4RCntrlQId;   /* Relay����ģ��֪ͨ��ϢID  */
extern ULONG g_ulDHCP4RSm;         /* Relayģ�鹲�����ݻ����ź��� */

/* RELAY���ڱ�����յ�DHCP���ĵĻ�����    */
extern UCHAR g_aucDHCP4RUdpBuf[DHCP4R_UDPBUF_MAXLEN]; 

/* (UDP 67)����DHCP Relay��Client���ջ�����Client����DHCP����  */
extern LONG  g_lDHCP4RSocket; 

/* �м̷�ʽ     */
extern ULONG g_ulDHCP4RFwdMode;     

/* ���RELAY����    */
extern ULONG g_ulDHCP4RMaxHops;     

/* Ҫ���õ�TOS      */
extern UCHAR g_ucDHCP4RTos;    

/* DHCP4Rģ����Ϣ */
extern DHCP4R_MOD_INFO_S g_stDHCP4RModInfo;

/* Core��ʹ�õĻص������� */
extern DHCP4R_SHELL_CALLBACK_SET_S g_stDHCP4RShellApi;

/* DHCP4Rģ��ͳ����Ϣ */
extern DHCP4R_STATINFO_S g_stDhcp4rStat;
    
/* DHCP4Rģ���IFNET����������ָ�� */
extern struct IIF_IFNET_ComIntFUNVtbl    *g_pstDHCP4RIfnetFunTable;

/* DHCP4Rģ���AM4����������ָ�� */
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstDHCP4RAm4FunTable;

/* DHCP4Rģ���UDP4����������ָ�� */
extern struct IIF_IP4_UDP4_ComIntCfgVtbl *g_pstDHCP4RUdp4FunTable;

/* dhcp4r���������� */
extern struct IIF_COMP_DHCP4R_ComIntCFGVtbl *g_pstDHCP4RCfgTable;

/* dhcp4rģ���Sfib���������� */
extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl *g_pstDHCP4RSfibAComFUNTable;


/* dhcp4r ha */
extern ULONG g_ulDHCP4RHaDbg;           /* DHCP4R ha���Կ���״̬, 0-�ر�, 1-��       */
extern ULONG g_ulDHCP4RHaVerboseDbg;    /* DHCP4R ha��ϸ���Կ���״̬, 0-�ر�, 1-��   */

/* �ⲿģ�鶨����� */
/* VISP����ģ��ȫ�ֻ����ź��� */
extern ULONG g_ulSemForTightMods;

/* dhcp4r debug status */
extern CHAR *g_aszDhcp4rDbgStatus[];

/* dhcp������Ϣ�����ַ��� */
extern CHAR *g_aszDhcp4rPkt[]; 

/* �û��������Ӧ�������ַ��� */
extern CHAR *g_aszDhcp4rErrInfo[];

/* ��ȡDHCP Relay�����ĵ�Դ��ַ�ص�����ָ�� */
extern DHCP4R_GET_SRCADDR_HOOK g_pfDhcp4rGetSrcAddrHook;

extern ULONG g_ulDhcp4rMaxVrfIndex;

extern DHCP4R_CFG_VRF_S **g_ppstDhcp4rCfgVrf;

extern DHCP4R_DBG_VRF_S **g_ppstDhcp4rDbgVrf;

extern DHCP4R_PROC_REQUEST_HOOK g_pfDhcp4rProcRequestHook;

extern DHCP4R_GET_GIADDR_HOOK g_pfDhcp4rGetGiaddrHook;

/* ע��DHCP Relayģ�鱨��Ԥ�����ӣ��ɲ�Ʒ������յ���DHCP Reply���ĵ�Ԥ������̡�
   (����XID���޸�Giaddr�ֶ�) */
extern DHCP4R_PROC_REPLY_HOOK  g_pfDhcp4rProcReplyHook;

/* �����յ���Server���ĵ�Giaddr��ȡת���Ĺ㲥�ӿ������Լ�Դ��ַ */
extern DHCP4R_GET_CLIENTIF_HOOK g_pfDhcp4rProcGetClientIfHook;

/* �����յ���Server���Ļ�ȡת���Ĺ㲥�ӿ������Լ�Դ��ַ �����Giaddr�Ѿ���VRRP IP(�ǽӿ�IP)�ĳ���*/
extern DHCP4R_GET_CLIENTIF_BYVRF_HOOK g_pfDhcp4rProcGetClientIfByVrfHook;

extern DHCP4R_OPTION82_HOOK g_pfDhcp4rOption82Hook;

/* Modified by likaikun00213099 for secondary Relay Src IP at 2014-04-16 */
/* ͨ��Server IP��ȡDHCP Relay�����ĵ�Դ��ַ�ص�����ָ�� */
extern DHCP4R_GET_SRCADDR_BY_SVRIP_HOOK g_pfDhcp4rGetSrcAddrBySvrIpHook;
/* End of Modified by likaikun00213099 for secondary Relay Src IP at 2014-04-16 */

extern ULONG g_ulDR4TaskScheduleSwitch;
extern ULONG g_ulDR4PacketProCount;
extern ULONG g_ulDR4TaskDelayTime;

/* Added by likaikun00213099 at 20140806 for dhcp4r port security,dhcp4rʹ�ܼ��� */
extern ULONG g_ulDhcp4rEnableCount;
/* End of added by likaikun at 20140806 */

#ifdef __cplusplus
}
#endif      /* end of _cplusplus        */

#endif      /* end of _DHCP4R_VAR_H_    */

