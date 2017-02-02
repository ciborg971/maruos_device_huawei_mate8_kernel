/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              i3ah.h
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
#ifndef _I3AH_H_
#define _I3AH_H_

#ifdef __cplusplus
extern "C"{
#endif

/* 3AHģ����Ϣ */
typedef struct tagOam3ahModInfo
{
    ULONG ulModId;

    ULONG ulNpMode;     /* NPģʽ   */    
    ULONG ulFrmAct;     /* ��֡/��֡���¼�ʵ�ַ�ʽ */
    ULONG ulErrFrmPrdEventSetMode;  /* ��֡�����¼�����ֵ����ģʽ */
    ULONG ulErrSymPrdEventSetMode;  /* ������������¼�����ֵ����ģʽ */
}OAM3AH_MOD_INFO_S;

/* 3AHģ�鹦�������  */
DECLARE_INTERFACE (IIF_COMP_OAM3AH_ComIntFUN)
{
    IUNKNOWN_METHODS
        
    METHOD_(ULONG, pfOAM_3AH_RcvPkt)(IFNET_S* pIf, MBUF_S *pstMBuf);    /* 3ahģ�鱨�Ľ��պ���                      */
    METHOD_(ULONG, pfOAM_3AH_StartLbTest)(ULONG ulIfIndex, VOID * pBuffer, ULONG ulBufLen);    
    METHOD_(ULONG, pfOAM_3AH_IsEnabled)(ULONG ulIfIndex);               /* eth�ӿ��Ƿ�ʹ����3ah                     */
    METHOD_(ULONG, pfOAM_3AH_IsCanSndPkt)(ULONG ulIfIndex);             /* eth�ӿ��Ƿ���Է��ͱ���(3ah����̬Ӱ��)   */
    METHOD_(ULONG, pfOAM_3AH_NotifyCriticalLinkEvent)(ULONG ulIfIndex, ULONG ulCriticalLinkEventType, ULONG ulState);

    METHOD_(VOID , pfOAM_3AH_DealLinkCtrlMsg)(UINTPTR aulMsg[4]);  /* �ײ�(driver/np)��Ϣ֪ͨ������ */

    METHOD_(ULONG, pfOAM_3AH_GetSessionStatus)(ULONG ulIfIndex, ULONG* pulStatus); 

    /* ����ӿ�����UP/DOWN֪ͨ����  */
    METHOD_(ULONG,  pfOAM_3AH_SH_IfPhyStatus_Notify)(VOID* pulIfIndex, ULONG ulCmd, VOID* pData, VOID** ppInfo); 
    METHOD_(VOID,  pfOAM_3AH_IfPhyStatus_Notify)(ULONG ulIfIndex, ULONG ulCmd, CHAR * pData); /* �ӿ�����UP/DOWN֪ͨ����  */
    METHOD_(VOID,  pfOAM_3AH_IfDelete_Notify)(ULONG ulIfIndex);         /* �ӿ�ɾ��֪ͨ����     */
    METHOD_(ULONG, pfOAM_3AH_DealPktTimeTest_Hook_Register)(DEALPKT_TIMETEST__HOOK_FUNC pfTimeTest); 

    /* 3ah waitlist */
    METHOD_(ULONG, pfOAM_3AH_OpenWtLstObject)(UINTPTR *pulWaitListHandle); 
    METHOD_(ULONG, pfOAM_3AH_GetWtLstEntry)(UINTPTR ulWaitListHandle, OAM3AH_PORTINFO_S *pstOam3ahPortInfo); 
    METHOD_(ULONG, pfOAM_3AH_CloseWtLstObject)(UINTPTR ulWaitListHandle); 

    /* HA��� */
    METHOD_(ULONG, pfOAM_3AH_HA_BatchBackup)(VOID);
    METHOD_(ULONG, pfOAM_3AH_HA_RealTimePack)(ULONG ulBakType, VOID *pData);
    METHOD_(ULONG, pfOAM_3AH_HA_Input)(UCHAR *pucData, ULONG ulDataLen);
    METHOD_(ULONG, pfOAM_3AH_HA_Smooth)(VOID);
    METHOD_(ULONG, pfOAM_3AH_HA_Clean)(VOID);

    METHOD_(VOID, pfOAM_3AH_Health_BatchCheckup)(VOID);
};

/* 3AHģ����������� */
DECLARE_INTERFACE (IIF_COMP_OAM3AH_ComIntCFG)
{
    IUNKNOWN_METHODS
        
    /* ������ */
    METHOD_(ULONG, pfOAM_3AH_Init_Com)(const COM_ID_INFO_S *pstComInfo, ULONG ulComLen);
    METHOD_(ULONG, pfOAM_3AH_Active_Com)(VOID);
    METHOD_(ULONG, pfOAM_3AH_SetModuleInfo)(OAM3AH_MOD_INFO_S *pstMInfo);
    METHOD_(ULONG, pfOAM_3AH_RegShellApi)(OAM3AH_SHELL_CALLBACK_SET_S* pstShellApi);
    
    /* ������� */
    METHOD_(ULONG, pfOAM_3AH_GlobalDisable)(VOID);
    METHOD_(ULONG, pfOAM_3AH_Enable)(ULONG ulIfIndex, ULONG ul3AHEnable);
    METHOD_(ULONG, pfOAM_3AH_SetMode)(ULONG ulIfIndex, ULONG ul3AHMode);
    METHOD_(ULONG, pfOAM_3AH_SetDetect)(ULONG ulIfIndex, ULONG ulDetectInteval);
    METHOD_(ULONG, pfOAM_3AH_SetPduSize)(ULONG ulIfIndex, ULONG ulPduSize);
    METHOD_(ULONG, pfOAM_3AH_SetLbTestMode)(ULONG ulIfIndex, ULONG ulLbTestMode);
    METHOD_(ULONG, pfOAM_3AH_SetLoopback)(ULONG ulIfIndex, ULONG ulLoopbackCmd);
    METHOD_(ULONG, pfOAM_3AH_EventEnable)(ULONG ulIfIndex, ULONG ulEventEnable);
    METHOD_(ULONG, pfOAM_3AH_SetErroredWinThres)(ULONG ulIfIndex, ULONG ulLinkEventType, 
                                                 DULONG_S stdulErrWindow, DULONG_S stdulErrThres);
    METHOD_(ULONG, pfOAM_3AH_SetBoardState)(ULONG ulIfIndex, ULONG ulState);    
    METHOD_(ULONG, pfOAM_3AH_IoBoardSyncMainBoard)(OAM3AH_WARN_PARAM_S* pst3ahWarn);    

    METHOD_(ULONG, pfOAM_3AH_GetCfgInfo)(ULONG ulIfIndex, OAM3AH_CFG_INFO_S * pst3AHCfgInfo);
    METHOD_(ULONG, pfOAM_3AH_GetFSMInfo)(ULONG ulIfIndex, ULONG * pulState);
    METHOD_(ULONG, pfOAM_3AH_GetPacketStat)(ULONG ulIfIndex, OAM3AH_PDUSTAT_S * pstOampduStat);
    METHOD_(ULONG, pfOAM_3AH_ClearPacketStat)(ULONG ulIfIndex);
    METHOD_(ULONG, pfOAM_3AH_SetDbgSwitch)(ULONG ulIfIndex, ULONG ulDebugSwitche);
    METHOD_(ULONG, pfOAM_3AH_GetDbgSwitch)(ULONG ulIfIndex, ULONG * pulDugInfo);
    METHOD_(ULONG, pfOAM_3AH_Set_NegTimeoutWaring)(ULONG ulTime);
    METHOD_(ULONG, pfOAM_3AH_Get_NegTimeoutWaring)(ULONG *pulTime);
    METHOD_(ULONG, pfOAM_3AH_GetFaultWarnState)(ULONG ulIfIndex, OAM3AH_WARN_STATE_S* pst3ahWarnState);

    /* HA��� */
    METHOD_(ULONG, pfOAM_3AH_HA_SetDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfOAM_3AH_HA_GetDbg)(ULONG *pulDbg);
    METHOD_(ULONG, pfOAM_3AH_GetHaStat)(OAM3AH_HASTAT_S *pst3AHHaStat);
    METHOD_(ULONG, pfOAM_3AH_ClearHaStat)(VOID);
    METHOD_(ULONG, pfOAM_3AH_HA_SetVerboseDbg)(ULONG ulDbg);
    METHOD_(ULONG, pfOAM_3AH_HA_GetVerboseDbg)(ULONG *pulDbg);
    METHOD_(VOID,  pfOAM_3AH_HA_DebugOutPut)(UCHAR *pBuf,ULONG ulMsgLen,ULONG ulCmd); 

    METHOD_(ULONG, pfOAM_3AH_GetCfgInfoEx)(ULONG ulIfIndex, OAM3AH_CFG_INFO_EX_S * pst3AHCfgInfo);
    METHOD_(ULONG, pfOAM_3AH_SetDealPacketWithVlanSwitch)(ULONG ulSwitch);
    METHOD_(ULONG, pfOAM_3AH_GetDealPacketWithVlanSwitch)(ULONG *pulSwitch);
};

/* 3AHģ��SSA����� */
DECLARE_INTERFACE (IIF_COMP_OAM3AH_ComIntSSA)
{
    IUNKNOWN_METHODS
};

/* For implement of QuerfyInstance() */
typedef struct tagOAM3AH_IntObj
{
    struct IIF_COMP_OAM3AH_ComIntFUN    *pCompIntFUN;
    struct IIF_COMP_OAM3AH_ComIntCFG    *pCompIntCFG;
    struct IIF_COMP_OAM3AH_ComIntSSA    *pCompIntSSA;
}OAM3AH_INT_OBJ_S;

/*�����Ϣ*/
extern struct ComponentInfo m_CompOam3ahInfo;

/* Core��ʹ�õĻص������� */
extern OAM3AH_SHELL_CALLBACK_SET_S g_stOam3ahShellApi;

/* OAM3AH���������� */
extern struct IIF_COMP_OAM3AH_ComIntFUNVtbl *g_pstOAM3AHFunTable;

/* OAM3AH���������� */
extern struct IIF_COMP_OAM3AH_ComIntCFGVtbl *g_pstOAM3AHCfgTable;

/* OAM3AH���SSA��� */
extern struct IIF_COMP_OAM3AH_ComIntSSAVtbl *g_pstOAM3AHSsaTable;


#ifdef __cplusplus
}
#endif      /* end of __cplusplus   */

#endif      /* end of _I3AH_H_      */

