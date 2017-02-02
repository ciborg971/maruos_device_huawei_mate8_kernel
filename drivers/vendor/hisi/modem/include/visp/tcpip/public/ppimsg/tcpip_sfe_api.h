/*******************************************************************************
*
*
*                Copyright 2009, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              tcpip_sfe_api.h
*
*  Project Code: VISPV100R008C02
*   Module Name: 
*  Date Created: 2009-8-20
*        Author: zhangchunyu(62474)
*   Description: �����浽������API
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME                                   DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2009-8-20  zhangchunyu(62474)         Create the first version.
*
*******************************************************************************/
#ifndef _TCPIP_SFE_API_H_
#define _TCPIP_SFE_API_H_

#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/public/ppimsg/tcpip_sfe_share_api.h"
#include "tcpip/bfd/include/bfd_cbb_api.h"

typedef UINT32 (*g_pfSendMsgToSFE)(VOID * pMsg, UINT32 u32Len);
typedef UINT32 (*g_pfRecvMsgFromSFE)(VOID *pMsgBuf, UINT32 *u32Len);
typedef VOID * (*g_pfAllocMsg)(UINT32 ulLength);
typedef UINT32 (*g_pfFreeMsg)(VOID *pMsg);

typedef UINT32 (*PF_FILTER_ROUTE4)(PPI_RTMSG4_S *pstPpiRoute);

/*******************************************************************************
*    Func Name: TCPIP_RegRecvMsgFromSFE
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ��Ʒע�������������������ݽӿ�
*        Input: g_pfRecvMsgFromSFE *pfFunc:  ע�ắ�� 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegRecvMsgFromSFE(g_pfRecvMsgFromSFE pstFun);

/*******************************************************************************
*    Func Name: TCPIP_RegSendMsgToSFE
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ��Ʒע������浽�����淢�ͽӿ�
*        Input: g_pfSendMsgToSFE *pfFunc: ע�ắ�� 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegSendMsgToSFE(g_pfSendMsgToSFE pstFun);

/*******************************************************************************
*    Func Name: TCPIP_RegFreeMsg
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: �ͷ�������������ڴ�
*        Input: g_pfFreeMsg pfFunc: �ص�����
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegFreeMsg(g_pfFreeMsg pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegAllocMsg
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ע�����������浽�������ڴ�
*        Input: g_pfAllocMsg pfFunc: 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_COM_SUCCESS ����: ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegAllocMsg(g_pfAllocMsg pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RegFilterFib4
* Date Created: 2009-8-29
*       Author: zhangchunyu(62474)
*  Description: ·�ɹ��˻ص��ӿ�
*        Input: PF_FILTER_ROUTE4 pfFunc: ע��ص�����
*       Output: pfFunc�������ؽ��:1��ʾ���·�,0��ʾ�·�
*       Return: TCPIP_RT_SUCCESS:�ɹ� ����:ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-29    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RegFilterFib4(PF_FILTER_ROUTE4 pfFunc);

/*******************************************************************************
*    Func Name: TCPIP_RecvEvent
* Date Created: 2009-8-21
*       Author: zhangchunyu(62474)
*  Description: �����������������Ϣ�ַ�����
*        Input: VOID *pMsg: ��Ϣ
*               UINT32 u32MsgLen:��Ϣ���� 
*       Output: 
*       Return: �ɹ�:TCPIP_SFE_COM_SUCCESS ����:ʧ��
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-21    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_RecvEvent(VOID *pMsg, UINT32 u32MsgLen);


extern UINT32 TCPIP_SFE_OperARP(UINT32 u32OperType, TCPIP_SFE_ARP_S *pstArp);

/*******************************************************************************
*    Func Name: TCPIP_SFE_OperFIB4
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: �û����ò���·�ɽӿ�
*        Input: ULONG ulOperType: ��������
*               TCPIP_SFE_ROUTE_S *pstRtMsg: ·����Ϣ
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_RT_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OperFIB4(UINT32 u32OperType, TCPIP_SFE_ROUTE_S *pstRtMsg);


extern UINT32 TCPIP_SFE_OperIf(UINT32 u32OperType,TCPIP_SFE_INTF_S *pstIntfInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_PPI_FIB4_Update
* Date Created: 2009-8-20
*       Author: zhangchunyu(62474)
*  Description: ������PPI�·��ӿ�
*        Input: UINT32 ulOprType: PPI����
*               PPI_RTMSG4_S *pstPpiRoute:��Ϣ�ṹ 
*       Output: 
*       Return: �ɹ�: TCPIP_SFE_RT_SUCCESS
*               ʧ��: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-20    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_PPI_FIB4_Update(UINT32 u32OprType, PPI_RTMSG4_S *pstPpiRoute);


extern UINT32  TCPIP_SFE_PPI_ARP_Update(UINT32 u32OperType, PPI_ARP_S *pstArpMsg);


extern UINT32 TCPIP_SFE_PPI_IF_Update(UINT32 u32IfIndex, UINT32 u32Cmd, VOID *pData);


extern UINT32 TCPIP_SFE_PPI_VRF_Update(UINT32 u32Cmd, VRF_PPI_S *pstVrfPpi);


extern UINT32 TCPIP_SFE_PPI_BFD4_Update(UINT32 u32OperType, UINT32 u32SessionID, BFD_PPI_S *pstBfdPpiInfo);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetFIBInfo
* Date Created: 2009-8-29
*       Author: zhangchunyu(62474)
*  Description: ��ȡָ��VRF��ָ��IP��Ӧ��·�ɱ�����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32IpAddr: ��ַ(������)
*               TCPIP_SFE_ROUTE_S *pstRouteInfo: ��ȡ��·����Ϣ
*       Output: *pstRouteInfo: ��ȡ��·����Ϣ
*       Return: TCPIP_SFE_COM_SUCCESS:�ɹ� ����:ʧ��
*      Caution: �ú�����������ֻ�ܻ�ȡһ��·����Ϣ,�����ƽ��·��,�������ȡһ��ƽ��·��
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-29    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetFIBInfo(UINT32 u32VrfIndex, UINT32 u32IpAddr, TCPIP_SFE_ROUTE_S *pstRouteInfo);


extern UINT32 TCPIP_SFE_GetArpInfo(UINT32 u32VrfIndex, UINT32 u32IpAddr, TCPIP_SFE_ARP_S *pstArp);


extern UINT32 TCPIP_SFE_GetIfInfoByID(TCPIP_SFE_IFID *pstIntfID,TCPIP_SFE_INTF_S *pstIntfInfo);


extern UINT32 TCPIP_SFE_GetBfdSessionInfo(UINT32 u32VrfIndex, UINT32 u32SessionId,
                                                    TCPIP_SFE_BFD_SESS_INFO_S *pstBfdSessInfo);
                                             
/*******************************************************************************
*    Func Name: TCPIP_SFE_OpenTable
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: ��ָ�������ݱ�
*        Input: UINT32  u32TableType: ���ݱ�, ȡֵ��enumTableType
*               UINT32  u32VrfIndex:  VRFʵ����
*       Output: UINT32 *pu32Handle:   ���ݱ�������, ����get��close
*       Return: TCPIP_SFE_TABLE_SUCCESS �ɹ� / ���� ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_OpenTable(UINT32 u32TableType, UINT32 u32VrfIndex, UINT32 *pu32Handle);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetTableData
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: 
*        Input: UINT32  u32Handle:  ���ݱ�������, openʱ���
*               UINT32 *pu32GetNum: �����ȡ�ı������
*               UINT32 *pu32BufLen: ���������� 
*       Output: 
*               UINT32 *pu32GetNum: ʵ�ʻ�ȡ�ı������
*               UINT8  *pu8Buf:     ��������ַ
*               UINT32 *pu32BufLen: ʵ�ʿ����ĳ��� 
*       Return: TCPIP_SFE_TABLE_SUCCESS: �ɹ�
*               TCPIP_SFE_TABLE_GET_OVER: ��ȡ�������
*               ����: ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetTableData(UINT32  u32Handle,
                              UINT32 *pu32GetNum,
                              UINT8  *pu8Buf,
                              UINT32 *pu32BufLen);

/*******************************************************************************
*    Func Name: TCPIP_SFE_CloseTable
* Date Created: 2009-8-22
*       Author: zhangchunyu(62474)
*  Description: �ر�ָ�������ݱ�
*        Input: UINT32 u32Handle: ���ݱ�������, openʱ���
*       Output: 
*       Return: TCPIP_SFE_TABLE_SUCCESS �ɹ� / ���� ������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                   DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-8-22    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_CloseTable(UINT32 u32Handle);


extern UINT32 TCPIP_SFE_SetSendIcmpErrSwitch(UINT32 u32Switch);


extern UINT32 TCPIP_SFE_GetSendIcmpErrSwitch(UINT32 *pu32Switch);


extern UINT32 TCPIP_SFE_IF_SetEthArpMissSwitch(TCPIP_SFE_IFID *pstIfId, UINT32 u32Switch);


extern UINT32 TCPIP_SFE_IF_SetReduceTTLSwitch(TCPIP_SFE_IFID *pstIfId, UINT32 u32Switch);


extern UINT32 TCPIP_SFE_SetSrcIpAddr(UINT32 u32VrfIndex, UINT32 u32SrcIpAddr);


extern UINT32 TCPIP_SFE_GetSrcIpAddr(UINT32 u32VrfIndex, UINT32 *pu32SrcIpAddr);


extern UINT32 TCPIP_SFE_BFD_SetDebugSwitch(UINT32 u32VrfIndex, UINT32 u32SessionId, UINT32 u32IsDebug);


extern UINT32 TCPIP_SFE_BFD_GetDebugSwitch(UINT32 u32VrfIndex, 
                                                UINT32 u32SessionId, UINT32 *pu32IsDebug);


extern UINT32 TCPIP_SFE_SetDebugTypeSwitch(UINT32 u32DebugTypeSwitch);


extern UINT32 TCPIP_SFE_SetDebugVcpuSwitch (UINT32 u32DebugVcpuSwitch);


extern UINT32 TCPIP_SFE_SetDebugModuleSwitch (UINT32 u32DebugModuleSwitch);


extern UINT32 TCPIP_SFE_GetDebugSwitch(UINT32* pu32DebugTypeSwitch, 
                                                UINT32* pu32DebugVcpuSwitch, 
                                                UINT32* pu32DebugModuleSwitch);


extern VOID TCPIP_SFE_ShowDebugSwitch(VOID);


extern UINT32 TCPIP_SFE_SetMsgOrEvent_DebugSwitch(UINT32 u32Switch);


extern UINT32 TCPIP_SFE_GetMsgOrEvent_DebugSwitch(UINT32 *pu32CtlDbgSwitch,
                                           UINT32 *pu32SfeDbgSwitch);


extern UINT32 TCPIP_SFE_SetVerboseDebug_CntAndLen(UINT32 u32PktNum, UINT32 u32Length);


extern UINT32 TCPIP_SFE_GetVerboseDebug_CntAndLen(UINT32 *pu32PktNum, UINT32 *pu32Length);


extern UINT32 TCPIP_SFE_GetAllStatistic(SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo,
                                        UINT32 pu32StaisticAutoInfo[SFE_STAT_IPFWD_MAX]);


extern UINT32 TCPIP_SFE_GetManualStatisticByVcpu(UINT32 u32VcpuId, SFE_IPSFE_STATISTIC_S *pstStatisticManualInfo);


extern VOID TCPIP_SFE_ShowAllStatistic();


extern VOID TCPIP_SFE_ShowAutoStatistic();


extern VOID TCPIP_SFE_ShowManualStatistic();


extern VOID TCPIP_SFE_ShowManualStatisticByVCPU(UINT32 u32VCPUID);


extern UINT32 TCPIP_SFE_SetFlowStatisticSwitch(UINT32 u32FlowStatSwitch);


extern UINT32 TCPIP_SFE_GetFlowStatisticSwitch(UINT32 *pu32FlowStatSwitch);


extern VOID TCPIP_SFE_ShowFlowStatisticSwitch(VOID);


extern UINT32 TCPIP_SFE_ConfigFlowStatisticRule(UINT32 u32OperType, TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);


extern UINT32 TCPIP_SFE_GetFlowStatisticRuleNum(UINT32 *pu32FlowStatisticRuleNum);


extern UINT32 TCPIP_SFE_GetFlowStatisticRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule,
                                               UINT32 *pu32FlowRuleNum);


extern UINT32 TCPIP_SFE_GetFlowStatisticInfoByRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule,
                                                       SFE_IPSFE_FLOWSTATISTIC_S *pstFlowStatisticManualInfo,
                                                       UINT32 pu32FlowStaisticAutoInfo[SFE_STAT_IPFWD_MAX]);


extern VOID TCPIP_SFE_ShowAllFlowStatisticRule(VOID);


extern VOID TCPIP_SFE_ShowFlowStatisticRuleByFlowId(UINT32 u32FlowId);


extern VOID TCPIP_SFE_ShowAllFlowStatistic(VOID);


extern VOID TCPIP_SFE_ShowFlowStatisticByFlowRule(TCPIP_SFE_FLOWSTATISTIC_RULE_S *pstFlowStatisticRule);


extern VOID TCPIP_SFE_ShowFlowStatisticByFlowId(UINT32 u32FlowId);


extern UINT32 TCPIP_SFE_SetLogLevel(UINT32 u32LogLevel);


extern UINT32 TCPIP_SFE_SetLogType(UINT32 ul32WarningLogEnable, UINT32 u32CfgLogEnable, UINT32 u32RunLogEnable);


extern VOID TCPIP_SFE_ShowLogSwitch(VOID);


extern VOID TCPIP_SFE_ShowVersion(VOID);


extern VOID TCPIP_SFE_Show_PreConfigPara(VOID);


extern VOID TCPIP_SFE_Show_ShareMemoryID(VOID);


extern VOID TCPIP_SFE_Show_StubDeleteModule(VOID);


extern UINT32 TCPIP_SFE_SetAclNeedFakeReassSwitch(UINT32 u32Switch);


extern UINT32 TCPIP_SFE_GetAclNeedFakeReassSwitch(UINT32 *pu32Switch);


extern VOID TCPIP_SFE_ShowAclNeedFakeReassSwitch(VOID);


extern VOID TCPIP_Show_MsgSeq(VOID);


extern VOID TCPIP_SFE_Show_MsgSeq(VOID);


extern VOID TCPIP_SFE_OutputToCOMSwitch(UINT32 u32Switch);


extern UINT32 TCPIP_SFE_ClearAllStatistic(VOID);


extern UINT32 TCPIP_SFE_ClearAllFlowStatistic(VOID);


extern VOID TCPIP_SFE_ShowAllArpInfo(VOID);


extern VOID TCPIP_SFE_ShowArpInfoByVrf(UINT32 u32VrfIndex);


extern VOID TCPIP_SFE_ShowOneArpInfo(UINT32 u32VrfIndex, CHAR *pcIpAddr);


extern VOID TCPIP_SFE_ShowAllIfInfo(VOID);


extern VOID TCPIP_SFE_ShowIfInfoByID(TCPIP_SFE_IFID *pstIfID);


extern VOID TCPIP_SFE_ShowAllBfdInfo(VOID);


extern VOID TCPIP_SFE_ShowBfdInfoByVrf(UINT32 u32VrfIndex);


extern VOID TCPIP_SFE_ShowBfdInfoByID(UINT32 u32VrfIndex, UINT32 u32SessionId);


extern VOID TCPIP_SFE_ShowAllFibInfo(VOID);


extern VOID TCPIP_SFE_ShowFibInfoByIP(UINT32 u32VrfIndex, CHAR *pi8IpAddr);

/*******************************************************************************
*    Func Name: TCPIP_SFE_GetBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: ��ȡָ��VRF��ĳһBFD�Ựͳ����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32SessionId: �ỰID
*               SFE_BFD_SESS_STATISTIC_S *pstStat:�������, ͳ����Ϣ
*       Output: 
*       Return: �ɹ� TCPIP_SFE_COM_SUCCESS
*               ʧ�� ����������
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_GetBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId, SFE_BFD_SESS_STATISTIC_S *pstStat);

/*******************************************************************************
*    Func Name: TCPIP_SFE_ClearBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: ��0ָ��VRF��ĳһBFD�Ựͳ����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32SessionId: �ỰID
*       Output: 
*       Return: �ɹ� TCPIP_SFE_COM_SUCCESS
*               ʧ�� ����������
*      Caution: �������Ƕ��,���ڶ��ͬʱ��д����ֶ�,��������0��,��������ֶο��ܲ���0�ĸ���
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern UINT32 TCPIP_SFE_ClearBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId);


/*******************************************************************************
*    Func Name: TCPIP_SFE_ShowBfdStatistic
* Date Created: 2009-12-3
*       Author: zhangchunyu(62474)
*  Description: ��ʾָ��VRF��ĳһBFD�Ựͳ����Ϣ
*        Input: UINT32 u32VrfIndex: VRF����
*               UINT32 u32SessionId: �ỰID
*       Output: ��ʾ�Ự��Ϣ
*       Return: VOID
*      Caution: 
*------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME             DESCRIPTION    
*  ----------------------------------------------------------------------------
*  2009-12-3    zhangchunyu(62474)     Creat the first version.
*
*******************************************************************************/
extern VOID TCPIP_SFE_ShowBfdStatistic(UINT32 u32VrfIndex, UINT32 u32SessionId);


#ifdef  __cplusplus
}
#endif
#endif

