

#ifndef _BFD_EXT_SH_H_
#define _BFD_EXT_SH_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Begin:VISP1.7C03 VRF wangchengyang , 2009-02-09 */
#include "tcpip/vrf/include/vrf_api.h"
#include "tcpip/vrf/core/include/vrf_pub.h"
/* End: VISP1.7C03 VRF wangchengyang , 2009-02-09 */
extern ULONG g_ulBfdVrfSize;
extern ULONG BFD_GetVrfIndexByName(CHAR *pszVrfName,ULONG *pulVrfIndex);
/* wangjiaqi modify for ipv6 bfd 20131125 begin */
extern ULONG BFD6_GetVrfIndexByName(CHAR *pszVrfName,ULONG *pulVrfIndex);
extern ULONG BFD6_GetVrfIndexByInst(VRF_GET_INDEX_BY_INST_S *pVrfInfo);
extern ULONG BFD6_GetVrfNameByIndex(CHAR *pszVrfName,ULONG ulVrfIndex);
/* wangjiaqi modify for ipv6 bfd end */
extern ULONG BFD_GetVrfIndexByIfIndex(ULONG ulIfIndex,ULONG *pulVrfIndex);
extern ULONG BFD_GetVrfNameByIndex(CHAR *pszVrfName,ULONG ulVrfIndex);
extern ULONG BFD_GetVrfIndexByRmPro(ULONG ulRtType,ULONG ulInstance, ULONG *pulVrfIndex);
extern ULONG BFD_GetVrfIndexByInst(VRF_GET_INDEX_BY_INST_S *pVrfInfo);
extern CHAR * BFD6_Inet_ntop6(const CHAR *pSrcAddr,CHAR *pszDstAddr, ULONG ulAddrLen);

/*OSPF and RTM Info Registe, Need to Registed Info By Initail Process */
/*����BFD��DCL����ϣ���BFD��ʼ�����������ע�����,�����Ÿ��û�*/
extern ULONG Extern_BFD_GetNextRelationEntry(UINTPTR ulEntryWaitList,BFD_API_FOR_OSPF_RELATION_S *pstRelations);
extern ULONG Extern_BFD_OpenOspfRelationTable(UINTPTR *pulWaitListHandle,BFD_FOR_OSPF_FILTER_S *pFilter);
extern ULONG Extern_BFD_CloseOspfRelationTable(UINTPTR ulWaitListHandle);
extern VOID Extern_BFD_DelEntryWaitListNotify(BFD_OSPF_NODE_S *pstRelations);

extern ULONG Extern_BFD_GetNextRuleEntry(UINTPTR ulEntryWaitList,BFD_API_FOR_OSPF_RULE_S *pstRules);
extern ULONG Extern_BFD_OpenOspfRuleTable(UINTPTR *pulWaitListHandle,BFD_FOR_OSPF_FILTER_S *pFilter,ULONG ulNetworkType);
extern ULONG Extern_BFD_CloseOspfRuleTable(UINTPTR ulWaitListHandle);
extern VOID Extern_BFD_DelRuleWaitListNotify(BFD_OSPF_RULE_ENTRY_S *pstRule);

extern ULONG Extern_BFD_GetRtStaticRelationEntry(UINTPTR ulEntryWaitList,BFD_API_FOR_STATIC_RELATION_S *pstRelations);
extern ULONG Extern_BFD_OpenRtStaticRelationTable(UINTPTR *pulWaitListHandle,BFD_FOR_STATIC_FILTER_S *pFilter);
extern ULONG Extern_BFD_CloseRtStaticRelationTable(UINTPTR ulWaitListHandle);
extern VOID Extern_BFD_DelStaticWaitListNotify(BFD_STATIC_NODE_S *pstStaticRelation);

extern VOID Extern_BFD_Info_Output(CHAR * pInfoBuf);
extern VOID Extern_BFD_DebugOutput(CHAR * pDbgBuf);
extern ULONG Extern_BFD_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);
extern ULONG Extern_BFD_GetFullNameByIfIndex(ULONG ulIfIndex,CHAR *pszIfName);
extern ULONG Extern_BFD_CheckOspf(ULONG ulNetworkType,ULONG ulInstanceId);
extern ULONG Extern_BFD_OSPFRuleUpdate_SetStale(ULONG ulIpVer,BOOL_T bAllRule, ULONG ulVrfIndexInput);
extern ULONG Extern_BFD_OSPFRuleUpdate_DoUpdate(ULONG ulCurMsgCount);
extern ULONG Extern_BFD_OSPFRuleUpdate_ClearUp(ULONG ulIpVer, BOOL_T bAllRule, ULONG ulVrfIndexInput);

/*******************************************************************************
*    Func Name: Extern_BFD_OSPFV3RuleUpdate_DoUpdate
* Date Created: 2014-08-24
*       Author: guojianjun178934
*  Description: OSPFV3 BFD����������£�ˢ��ָ��VRF��BFD�Ự
*        Input: ULONG ulVrfIndex:
*       Output:
*       Return:
*      Caution:
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  ----------------------------------------------------------------------------
*  2014-08-24   guojianjun178934        Create
*
*******************************************************************************/
ULONG Extern_BFD_OSPFV3RuleUpdate_DoUpdate(BOOL_T bAllRule, ULONG ulVrfIndex);

/* wangjiaqi modify for ipv6 bfd 20131125 begin */
/*******************************************************************************
*    Func Name:    Extern_BFD6_GetNextStaticRelationEntry
*    Date Created: 
*    Author: 
*    Description:  ͨ��WaitList�������ȡ��һ�����������������ָ��
*    Input:        ulEntryWaitList: WaitList���
*    Output:       pstRelations:��ȡ��������
*    Return:       �ɹ�����       BFD_EXT_OK
*                  ʧ�ܷ���       ������
*                  BFD_EXT_ERR_GET_ENTRY_END �ӱ��л�ȡ�������Ϲ�����������ָ��
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG Extern_BFD6_GetRtStaticRelationEntry(UINTPTR ulEntryWaitList,BFD6_API_FOR_STATIC_RELATION_S *pstRelations);
/*******************************************************************************
*    Func Name:    Extern_BFD6_OpenRtStaticRelationTable
*    Date Created: 
*    Author: 
*    Description:  ��ȡBFD6��Ststic�Ự�������WaitList���
*    Input:        pFilter: ������
*                  ulSizeOfFilter: ����������
*    Output:       pulWaitListHandle: WaitList���
*    Return:       �ɹ�����       BFD_EXT_OK
*                  ʧ�ܷ���       ������
*                  BFD_EXT_ERR_GET_ENTRY_END �ӱ��л�ȡ�������Ϲ�����������ָ��
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi        Create
*******************************************************************************/
ULONG Extern_BFD6_OpenRtStaticRelationTable(UINTPTR *pulWaitListHandle,BFD6_FOR_STATIC_FILTER_S *pFilter);
/*******************************************************************************
*    Func Name:    Extern_BFD6_CloseRtStaticRelationTable
*    Date Created: 
*    Author: 
*    Description:  �ر�BFD6��Ststic�Ự�������WaitList���
*    Input:        ulWaitListHandle: WaitList���
*    Output:       
*    Return:       �ɹ�����       BFD_EXT_OK
*                  ʧ�ܷ���       ������
*    Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME         DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2013-11-25      wangjiaqi    create
*******************************************************************************/
ULONG Extern_BFD6_CloseRtStaticRelationTable(UINTPTR ulWaitListHandle);
/* wangjiaqi modify for ipv6 bfd end */

#ifdef __cplusplus
}
#endif

#endif


