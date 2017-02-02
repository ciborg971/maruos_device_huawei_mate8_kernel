/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_intermediate.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: pp4_intermediate.cͷ�ļ�
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

#ifndef _PP4_INTERMEDIATE_H_
#define _PP4_INTERMEDIATE_H_


/* IP���Ĵ����� */
typedef struct tagIPPp4Intermediate {

    /* Determines the order of executing the function that is  registered. 
     * (Higher the value, higher is the priority level)
     */
    ULONG ulPriority;

    IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc;  /* The Registered Function Pointer */
    struct tagIPPp4Intermediate *pstNext;
} IP_PP4_INTERMEDIATE_HOOK_S;

/* IP���Ĵ����Ӻ������� */
extern IP_PP4_INTERMEDIATE_HOOK_S *g_pstInputAllPktIntermediateHook;
extern IP_PP4_INTERMEDIATE_HOOK_S *g_pstInputLocalPktIntermediateHook;
extern IP_PP4_INTERMEDIATE_HOOK_S *g_pstForwardPktIntermediateHook;
extern IP_PP4_INTERMEDIATE_HOOK_S *g_pstOutputLocalPktIntermediateHook;
extern IP_PP4_INTERMEDIATE_HOOK_S *g_pstOutputAllPktIntermediateHook;
/* Add for BC3D03018*/
extern IP_PP4_INTERMEDIATE_HOOK_S *g_pstInputReassPktIntermediateHook;

extern IP_PP4_DELEVERUP_POSITION_HOOK_FUNC g_pfDeliverUpPositionHook;
/*Add by Q62011 for vlan start*/
extern IP_PP4_ETHVLN_ICMPREDIRECT_HOOK_FUNC g_pfEthvlnIcmpRedirectHook;
/*Add by Q62011 for vlan end*/

/* IP���Ĵ����Ӻ������� */
extern ULONG IP_PP4_Inter_Process (MBUF_S *pstMBuf, IP_PP4_INTERMEDIATE_HOOK_S *psttmpInter);

/* IP���Ĵ����Ӻ���ע�� */
extern ULONG IP_PP4_Intermediate_Hook_Register (ULONG ulType, ULONG ulPriority, 
    IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);
extern ULONG IP_PP4_Intermediate_Hook_Register_PT(ULONG ulType, ULONG ulPriority,
    IP_PP4_INTERMEDIATE_HOOK_FUNC pfIpFwHookFunc);

extern ULONG IP_PP4_Intermediate_Hook_UnRegister(ULONG ulType, 
    IP_PP4_INTERMEDIATE_HOOK_FUNC  pfIpFwHookFunc);

extern ULONG IP_PP4_DeliverUp_Position_Hook_Register(IP_PP4_DELEVERUP_POSITION_HOOK_FUNC pfHookFunc);

extern IP4_SEND_WHOLE_PKT_HOOK g_pfIpSendWholePktHook;

/*Added by qinyun62011, (Distribute socket)�ֲ�ʽsocket�ü�2014/3/12 */
extern IP4_SEND_WHOLE_PKT_HOOK g_pfIpSendPktNoFibSearchHook;
/* End of Added by qinyun62011, 2014/3/12 */

/*Add by Q62011 for vlan start*/
extern ULONG IP_PP4_Ethvlan_IcmpRedirect_Hook_Register(IP_PP4_ETHVLN_ICMPREDIRECT_HOOK_FUNC pfHookFunc);
/*Add by Q62011 for vlan end*/

#endif  /* _PP4_INTERMEDIATE_H_  */

#ifdef  __cplusplus
}
#endif

