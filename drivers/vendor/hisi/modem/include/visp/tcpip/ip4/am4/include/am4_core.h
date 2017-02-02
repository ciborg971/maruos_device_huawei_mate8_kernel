/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_core.h
*
* Project Code: VISPV100R005
*  Module Name: AM4  
* Date Created: 2006-01-04
*       Author: Li LiXiang
*  Description: AM4��core�ĺ�������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������
*  2006-11-07   zhoutong(43740)         �淶������
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _AM4_CORE_H_
#define _AM4_CORE_H_


/* ��ַ��־λ�ĺ꣬��ʶ��ͬ���͵ĵ�ַ���ڵ�ַ��ipif_ulAddrFlag�б���
 * ��ַ���͵ı�־
 */
#define IP_NO              0    /* δ���õ�ַ */ 
#define IP_OWN          0x01    /* ���Լ�������ַ */
#define IP_NEGOTIATE    0x02    /* ����ַ��Э�̵��� */
#define IP_BORROW       0x04    /* ����ַ�ǽ��õ� */
#define IP_LEND         0x08    /* ������˵�ַ */
#define IP_LENDANDOWN   (IP_OWN|IP_LEND)
#define IP_LENDANDNEGO  (IP_LEND|IP_NEGOTIATE)
#define IP_DHCP         0x10    /* �ӿ�����DHCP��õĵ�ַ */ 
#define IP_NODHCPFLAG   0x10    /* DHCP��ַ�����ȼ����ڽӿڵ�ַ��ʽʹ��DHCP�ı�־λ */ 
#define IP_NODHCP       0x20    /* �ӿڲ�����DHCP��õĵ�ַ */ 


/* Start of ��̫���Ĺ�����������ֵ */
#define IP_ARP_IPIFNET_ERR      1
#define IP_ARP_ONESEFIP         14
#define IP_ARP_DSTIP_NOTSAMENET 15
#define IP_ARP_SRCIP_BROADCAST  16
#define IP_ARP_INVALIDADDR      17
#define IP_ARP_DSTIPISNET       18
#define IP_ARP_SRCIP_NOTSAMENET 19
#define IP_ARP_DSTADD_NOTMY     20
/* End of ��̫���Ĺ�����������ֵ */

typedef ULONG(*AM4_SHELL_HA_CALLBACK_FUNC_PTR)();


typedef struct tagIP_AM4_MOD_INFO
{
    ULONG ulModID;
    ULONG ulModSubId;
    ULONG ulAddrCmdRpcChannel;
    ULONG ulVlinkFlag ;
    ULONG ulDhcpAddrCfgMode;
} IP_AM4_MOD_INFO_S; 


typedef struct tagAM4_SHELL_HA_CALLBACK_FUNC_SET
{
    AM4_SHELL_HA_CALLBACK_FUNC_PTR   pfGetBoardType;
    AM4_SHELL_HA_CALLBACK_FUNC_PTR   pfGetMainBoardId;
    AM4_SHELL_HA_CALLBACK_FUNC_PTR   pfGetSlaveBoardId;
} AM4_SHELL_HA_CALLBACK_FUNC_SET_S;


typedef struct tagAm4ICCallbackSet
{
    ULONG (*pfIP_AM4_SH_SendDebugInfoToIC)(CHAR *szBuf);
}IP_AM4_IC_CALLBACK_SET_S;



#endif  /* _AM4_CORE_H_  */


#ifdef  __cplusplus
}
#endif
