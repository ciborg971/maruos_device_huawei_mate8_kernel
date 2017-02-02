

#ifndef _TCPIP_IIFNET_H
#define _TCPIP_IIFNET_H

#ifdef __cplusplus
extern "C"{
#endif
                 
DECLARE_INTERFACE(IIF_IFNET_ComIntFUN)
{
    IUNKNOWN_METHODS
    /**********************�ӿڴ�����ɾ���෽��**************************/
    METHOD_( IFNET_S*, pfIF_CreateByDev) (DEVLINK_S * pstDev,ULONG ulIndex);    /*�����豸�����ӿ�*/
    METHOD_( ULONG, pfIF_Delete)( IFNET_S *pIf );
    METHOD_( ULONG, pfIF_Shutdown)( IFNET_S *pIf );
    METHOD_( ULONG, pfIF_NoShutdown)( IFNET_S *pIf );
    METHOD_( ULONG, pfIF_LinkIoCtl)(ULONG ulIfIndex, ULONG ulCmdIndex, CHAR *pData);
    METHOD_( ULONG, pfIF_LinkReceived)( ULONG ulIfIndex, MBUF_S * pMBuf);
    METHOD_( IFNET_S*, pfIF_DynamicCreateIfNet) (CHAR * szFullName, ULONG ulSubType); /*�������ơ����������ӿ�*/

    METHOD_( IFNET_S*, pfIF_DynamicCreateL2IfNet) (CHAR * szFullName, ULONG ulSubType); /*�������ơ����������ӿ�*/
    
    METHOD_( IFNET_S*, pfIF_CreateSubIf) (CHAR * szSubName , ULONG ulIndex, ULONG ulSubType, IFNET_S * pMain); 

    METHOD_( IFNET_S*, pfIF_CreateVA) (ULONG ulVTIndex,ULONG ulClassID,ULONG ulIfIndex, ULONG ulChannelId);
    METHOD_( ULONG, pfIF_InitIfByLayer) (IFNET_S *pIf,ULONG ulPos);  /*����ָ����ĳ�ʼ��*/
    METHOD_( ULONG, pfIF_BuildrunByLayer) (IFNET_S *pIf,ULONG ulPos);  /*����ָ�����buildrun����*/
    METHOD_( ULONG, pfIF_CmdHideByLayer) (IFNET_S *pIf,ULONG ulPos); 
    
    /**********************��λ�෽��**************************/
    METHOD_( IFNET_S*, pfIF_GetIfByIndex) (ULONG ulIfIndex); /*����������ȡ�ӿ�ָ��*/
    METHOD_( ULONG, pfIF_GetSlotByIndex) (ULONG ulIfIndex); /*����������ȡ�ӿ����ڲۺ�*/
    METHOD_( ULONG, pfIF_GetLineProtoByIndex) (ULONG ulIfIndex);  /*����������ȡ�ӿ���·��Э��*/
    METHOD_( ULONG, pfIF_BoardIsUp) (ULONG ulSlot ); /*�жϰ��Ƿ�UP*/
    METHOD_( ULONG, pfIF_IsVisible) ( IFNET_S * pIf ); /*�жϽӿ��Ƿ�ɼ�*/
    METHOD_( ULONG, pfIF_IsConfigure) ( IFNET_S * pIf ); 
    METHOD_( ULONG, pfIF_IsTempIf) ( ULONG ulIndex); 
    METHOD_( ULONG, pfIF_IsTempIfByPtr) ( IFNET_S * pIf );  /*�жϽӿ��Ƿ�����ʱ�ӿ�  ����ʹ�ñ�����---luohanjun*/
    METHOD_( LONG, pfIF_IsSameBoard) ( ULONG ulIndex);  /*�жϽӿ��Ƿ��ڱ���*/
    METHOD_( LONG, pfIF_JudgeNameOrder) ( CHAR * Sour,CHAR * if_pName);
    METHOD_( ULONG, pfIF_GetNextUpBoardID) (ULONG ulSlot );
    METHOD_( IFNET_S*, pfIF_GetConfigHead) ( );
    METHOD_( IFNET_S*, pfIF_GetIfByFullName) (CHAR * szFull );
    METHOD_( IFNET_S*, pfIF_GetMainIf) ( IFNET_S* pIf);
    METHOD_( ULONG, pfIF_GetFirstIfIndex) ( ULONG * pIndex);
    METHOD_( ULONG, pfIF_GetNextIfIndex) ( ULONG ulIndex, ULONG * pNextIndex);
    METHOD_( IFNET_S*, pfIF_FindFirstSubIfnet) ( IFNET_S* pMain);
    METHOD_( IFNET_S*, pfIF_FindNextSubIfnet) ( IFNET_S* pSub);
    METHOD_( IFNET_S*, pfIF_FindSubIfWithName) (CHAR * if_pName);        /*�����ӽӿ��������ӽӿ�*/
    METHOD_( IFNET_S*, pfIF_FindWithMainName) (CHAR * if_pName); /*�������ӿ������ҽӿ�*/
    METHOD_( IFNET_S*, pfIF_FindWithSubIndex) (IFNET_S * pIf, ULONG ulSubIndex ); 
    METHOD_( IFNET_S*, pfIF_SearchIfFromChain) ( IFNET_S* pIf , ULONG ulSearch);
    METHOD_( IFNET_S*, pfIF_SearchIfFromChainFun) ( IFNET_S* pIf , ULONG ulSearch);
    /* Begin:VISP1.7C03 VRF qinyun , 2009-01-20 */
    METHOD_( ULONG, pfIF_GetVrfByIfIndex) ( ULONG ulIndex, ULONG * pVrfIndex);
    /* End: VISP1.7C03 VRF qinyun , 2009-01-20 */

    /**********************���Ĵ����ຯ��**************************/
    METHOD_( ULONG, pfIF_Output) ( MBUF_S * pMbuf);
    
    /**********************����ά���ຯ��**************************/

    /*��װǰԤ����*/
    METHOD_( ULONG, pfIF_BeforeEncap) ( IFNET_S *pIf , ULONG *ulShutdown, ULONG ulExecID, ULONG ulNewProtocol);
    METHOD_( ULONG, pfIF_AfterEncap) ( IFNET_S *pIf , ULONG ulShutdown ); /*��װ����*/
    METHOD_( VOID, pfIF_SetLastChangeTime) ( IFNET_S * pIf ); 

    METHOD_( ULONG, pfIF_GetConfigMTU) ( IFNET_S * pIf ); 
    METHOD_( VOID , pfIF_SelectMtu) (IFNET_S * pIf, ULONG * pMin, ULONG * pMax ); 
    METHOD_( ULONG, pfIF_GetMTU)( IFNET_S* pIf );
    METHOD_( ULONG, pfIF_SetMTU)( IFNET_S* pMtuIf, ULONG ulMTU );

    METHOD_(ULONG, pfIF_SetBandWidthValue)(ULONG ulSlot, IFNET_S* pIf, ULONG ulValue);
    METHOD_(ULONG, pfIF_SetDescript)( IFNET_S* pIf, CHAR * pDescript );

    METHOD_( ULONG, pfIF_GetKeepAliveValue)(IFNET_S* pIf, ULONG* pValue);
    METHOD_( ULONG, pfIF_SetKeepAliveValue)(IFNET_S* pIf, ULONG ulValue);

    /**********************HOOK�෽��**************************/
    METHOD_( ULONG, pfIF_AnalyseIfName)( IFNAME_S * pstIfName,CHAR * szName );

    METHOD_( ULONG, pfIF_HookForQuery)(ULONG ulFunc, CHAR * szType, CHAR * szInput, ULONG pHelpVec);

    METHOD_( ULONG, pfIF_VLINK_IoCtl)(VOID * pVLinkStatus, VOID * pCB);
    METHOD_( ULONG, pfIF_VLINK6_IoCtl)(VOID * pVLinkStatus, VOID * pCB);
    METHOD_( VOID*, pfIF_VLINK_GetCB)(ULONG ulVlinkIndex);              /* VLINK_GetCB */
    METHOD_( ULONG, pfIF_VLINK_SetCB)(ULONG ulVlinkIndex, VOID * pCB);    /* VLINK_SetCB */

    /**********************֪ͨ����ע����**************************/
    METHOD_( ULONG, pfIF_RegisterNotifyFn)(/*ULONG ulModule,*/ULONG ulType, ULONG ulPriority, void* pfNotifyFn); 
    METHOD_(ULONG, pfIF_UnRegisterNotifyFn)(/*ULONG ulModule,*/ULONG ulType,void* pfNotifyFn);

    METHOD_(ULONG, pfIF_OpenIfConfigEntry)(UINTPTR *pulWaitListHandle);
    METHOD_(ULONG, pfIF_GetIfConfigEntry)(UINTPTR ulEntryWaitList, IFNET_S * pstIfConfig);
    METHOD_(ULONG, pfIF_CloseIfConfigEntry)(UINTPTR ulWaitListHandle);

    METHOD_(ULONG, pfIF_IsTrunkPort)(IFNET_S* pIf);
    METHOD_(ULONG, pfIF_VTIsBinded)(IFNET_S *pstIf, ULONG *pulEthIfIndex);
    METHOD_(ULONG, pfIF_HA_BatchBackup)();
    METHOD_(ULONG, pfIF_HA_Input)(UCHAR *pBuf, ULONG ulMsgLen);
    METHOD_(ULONG, pfIF_HA_Smooth)();
    METHOD_(ULONG, pfTCPIP_HA_VerifyInterface)(ULONG ulIfIndex); 
    METHOD_(ULONG, pfIF_GetIfFullNameByIndex)(ULONG ulIfIndex, CHAR *pszIfName);
    METHOD_(ULONG, pfIF_GetIfIndexByFullName)(CHAR *pszIfName, ULONG *pulIfIndex);
    METHOD_(IFNET_S*, pfIF_GetIfByTypeNum)(ULONG ulIfType, ULONG ulFirstDim, ULONG ulSecondDim, ULONG ulThirdDim);
    METHOD_(ULONG, pfIF_HA_Clean)();
    METHOD_(VOID, pfIF_DealIoCtlMsgs)();

    METHOD_(ULONG, pfIF_SetIsisFlag)( ULONG ulIfIndex ,ULONG ulFlag );
    METHOD_(ULONG, pfIF_GetIsisFlag)( ULONG ulIfIndex ,ULONG *pulFlag );

    METHOD_(ULONG, pfIF_RegisterVlanCheckFnc)(IF_VLANCHECKFN pfIfHookFunc);
    
    /* ��������˿� */
    METHOD_( IFNET_S *, pfIF_CreateByDevForPort)(DEVLINK_S * pstDev ,ULONG ulIndex, ULONG ulL2Flag);

    METHOD_( VOID, pfIF_Health_BatchCheckup)();
    METHOD_(DEVLINK_S *, pfIF_FindDevByIfIndex)(DEVLINK_S *pstDevLink, ULONG ulIfIndex);
    METHOD_(ULONG, pfIF_SetDevLink)(DEVLINK_S *pstDevLink);
    METHOD_(ULONG, pfIF_GetDevLink)(ULONG ulIfIndex, DEVLINK_S *pstDevLink);

    METHOD_(ULONG, pfIF_SetIfEventDebugSwitch)(ULONG ulValue);
    METHOD_(ULONG, pfIF_GetIfEventDebugSwitch)(ULONG *pulValue);

    METHOD_(ULONG, pfIF_GetISIStatus)(ULONG ulIfIndex, ULONG *pulIfState);    
    METHOD_(ULONG, pfIF_GetAllIfIndex)(ULONG *pulIfNum, ULONG *pulIfIndex);    
    METHOD_(ULONG, pfIF_GetIfNum)(ULONG *pulIfNum);    

    METHOD_(IFNET_S*, pfIF_GetIfByTypeNumSub)(ULONG ulIfType, ULONG ulFirstDim, ULONG ulSecondDim, ULONG ulThirdDim,ULONG ulSubPort);

    /*Added by apurba for VRF6*/
    METHOD_( ULONG, pfIF_GetVrf6ByIfIndex) ( ULONG ulIndex, ULONG * pVrfIndex);
    /*End of Added by apurba for VRF6*/
    METHOD_( ULONG, pfIF_Tunn_SetTunnelPara) (ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnelPPI);
    METHOD_( ULONG, pfIF_Tunn_DelTunnelPara) (ULONG ulIfIndex);
    METHOD_( ULONG, pfIF_Tunn_GetIfInfoByIfIndex) (ULONG ulIfIndex, TCPIP_TUNNEL_IF_PPI_S *pstTunnelPPI);
    METHOD_( ULONG, pfIF_Tunn_ShowIfByName) (CHAR *szIfName);
};


/*�����ӿ�����*/

/*
 * ע��: -----add by luohanjun
 * ����һ�����������Ϊ�ӿڵ��ϲ㡢��·�㡢�豸�㣬������ulPosition����
 * ���в���ulPosition��Ҫ�����¶�������ж�
 * 0: �ϲ�,һ��ָIPv4��ֻ��ִ���ϲ������
 * 1: �ϲ�,һ��ָIPv6��ֻ��ִ��IPv6������
 * 2: ��·�㣬ֻ��ִ����·��Ĳ�����
 * 3: �豸�㣬ֻ��ִ���豸��Ĳ�����
 */
DECLARE_INTERFACE(IIF_IFS_IntFun) /*�ⲿ���IFNET�����ӿ�*/
{
    IUNKNOWN_METHODS

    /* ���������������ݣ�����ʼ�� */
    METHOD_(ULONG , pfIF_InitIF) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);

    /* �������㣬����UP�¼���ִ�и��������buildrun��ͨ�����ƺ��������¼����ݵȲ��������Բ�ִ���κβ�����*/
    METHOD_(ULONG , pfIF_BuildrunIF) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

    /* �ӿ��������Σ���Ҫ�������·�㣬����������ṩ�պ�����*/
    METHOD_(ULONG , pfIF_HideCommand) (IFNET_S* pIf, ULONG ulPosition, ULONG* pulRet);

    /*�ͷ�ָ������ƿ顣*/
    METHOD_(ULONG , pfIF_FreeControlBlock) (IFNET_S* pIf,ULONG ulPosition, ULONG* pulRet);

};
ULONG IF_QueryInterface(IUnknown * This, COMP_IID iid, VOID **ndvObj);


#ifdef __cplusplus
}
#endif

#endif /* _TCPIP_IIFNET_H */

