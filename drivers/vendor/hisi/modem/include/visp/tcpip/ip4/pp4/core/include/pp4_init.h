/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_init.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: pp4_init.cͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-01   zhoutong(43740)         �淶������
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_INIT_H_
#define _PP4_INIT_H_


/* PP4ģ����Ϣ���ƿ� */
extern IP_PP4_MOD_INFO_S    g_stIPPp4ModInfo;


extern LONG nMaxLinkHdr;    /* largest link-level header */
extern LONG nMaxProtoHdr;   /* largest protocol header */
extern LONG g_lMaxHdr;      /* largest link+protocol header */

/* PP4ģ��ʹ�õ��������� */
extern struct IIF_IPV4_IP_ICMP_ComIntFUNVtbl      *g_pstPp4ICMPVtbl;
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl       *g_pstPp4Am4Vtbl;
extern struct IIF_COMP_FIBAGENT_ComIntFUNVtbl     *g_pstPp4SfibVtbl;
extern struct IIF_IPV4_FIBCONTR_ComIntCFGVtbl     *g_pstPP4Fib4CCfgTable;

extern struct IIF_IPV6_NATPT_ComINTF_V4STKVtbl *g_pstPp4NatptV4Stk;

/* DHCP4C����ӿں����� */
extern struct IIF_IPV4_DHCP4C_ComIntFunVtbl *g_pstPp4Dhcp4cFunVtbl;

/* PP4��������ܺ��� */
extern ULONG IP_PP4_Init_Com(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen);
extern ULONG IP_PP4_Activate_Com();
extern ULONG IP_PP4_SetModuleInfo(IP_PP4_MOD_INFO_S *pstMInfo );

extern UCHAR  g_ucLandAttckSwitch ;

#endif  /* _PP4_INIT_H_  */

#ifdef  __cplusplus
}
#endif


