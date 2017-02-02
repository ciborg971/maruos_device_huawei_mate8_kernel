/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              1ag_var.h
*
*  Project Code: VISPV100R007
*   Module Name: 1AG  
*  Date Created: 2008-3-3
*        Author: yebo(62007)
*   Description: 1AG����ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2008-3-3  yebo(62007)         Create the first version.
*
*******************************************************************************/
#ifndef _1AG_VAR_H
#define _1AG_VAR_H

#ifdef  __cplusplus
    extern "C"{
#endif

#include "tcpip/public/tcpip_basefun.h"

extern APP_INIT_INFO_S g_stOam1agAppInfo;

/*ȫ��1AG��������,Ĭ��Ϊ8902*/
extern USHORT g_usOam1agPktType;
/*ȫ��1AG�������ȼ�,Ĭ��Ϊ6*/
extern UCHAR g_ucOam1agPktPri;
/* ȫ��1AG�����Կ��� */
extern ULONG g_ulCompatibleSwitch;

extern ULONG g_ulMaxMdNum;
extern ULONG g_ulMaxMaNum;
extern ULONG g_ulMaxMepNum;
extern ULONG g_ulMaxRmepNum;

/*����ȫ��MD����*/
extern OAM_1AG_MDCHAIN_S *g_pstMdChainTable;
/*����ȫ��MA����*/
extern OAM_1AG_MACHAIN_S *g_pstMaChainTable;
/*����ȫ��MEP����*/
extern OAM_1AG_MEPCHAIN_S *g_pstMepChainTable;
/*����ȫ��RMEP����*/
extern OAM_1AG_RMEPCHAIN_S *g_pstRmepChainTable;

/*����MEP��ʱ��ʱ��IDֵ*/
extern ULONG g_ulMepTimerId;
/*����RMEP��ʱ��ʱ��IDֵ*/
extern ULONG g_ulRmepTimerId;

/*����Ltr��ʱ��ʱ��IDֵ*/
extern ULONG g_ulLtrTimerId;

/*����AIS��ʱ��ʱ��IDֵ*/
extern ULONG g_ulAISTimerId;


/*����MEP 100ms˫������*/
extern DLL_S g_stMep100msList;
/*����MEP 1s˫������*/
extern DLL_S g_stMep1sList;
/*����MEP 10˫������*/
extern DLL_S g_stMep10sList;

extern DLL_S *g_pstMepTimerList[3];

/*����RMEP 100ms˫������*/
extern DLL_S g_stRmep100msList;
/*����RMEP 1s˫������*/
extern DLL_S g_stRmep1sList;
/*����RMEP 10˫������*/
extern DLL_S g_stRmep10sList;

extern DLL_S *g_pstRmepTimerList[3];

/*LBr����*/
extern DLL_S g_stLbrList;
/*Ltr����*/
extern DLL_S g_stLtrList;

/*AIS  1s ����*/
extern DLL_S g_st1sAISList;

/*AIS  1min ����*/
extern DLL_S g_st1minAISList;

extern DLL_S *g_pstAISTimerList[2];

/*����LB����������*/
extern ULONG   g_ulTotalLBNum;
/*LB�������,ȫ��Ψһ*/
extern ULONG   g_ulLbSequence;
/* ��ΪLB������κ�ֵ���ǿ��ܵģ���������������Ϊ����ṹ */
extern DLL_S   g_stLBsequenceList;
/*1AG ���ĵ��Կ���*/
extern ULONG    g_ulDebugNormal1AGPktFlag;
/*1AG �����ĵ��Կ���*/
extern ULONG    g_ulDebugException1AGPktFlag;
/*1AG ������ϸ��Ϣ���Կ���*/
extern ULONG    g_ulDebug1AGVerboseFlag;
/*Verbose ��ӡ����*/
extern ULONG    g_ulDebug1AGVerbosePktNum;
/*Verbose ��ӡ�ֽ���*/
extern ULONG    g_ulDebug1AGVerbosePktOctets;

/*1AG ����ha���Կ���*/
extern ULONG    g_ulDebug1AGHAFlag;

/*1ag�����Ϣ*/
extern OAM_1AG_MOD_INFO_S g_stOam1agModInfo;
/*HAͳ����Ϣ*/
extern HA1AGSTAT_S   g_stHa1agStat; 
/*�û��Զ��屨�Ĵ�����*/
extern OAM_1AG_USERPINGPKTDEAL    g_pfUserPingPktDeal;
/*lt��lb�����Ϣ*/
extern OAM_1AG_OUTINFO_HOOK_FUNC  g_pfOAM1AGOutputInfo;
/*1agֹͣ����*/
extern OAM_1AG_STOP_HOOK_FUNC     g_pf1AGUserStop;
/*ע��ص�����*/
extern OAM_1AG_SHELL_CALLBACK_S g_stOam1agshellFunc;
/*���ܲ��Թ��Ӻ���*/
extern OAM_1AG_CAPTEST g_pfOam1agCapTest;
/* �յ�����VLAN��LB��LT����ʱ,���ڶ������VLAN��MEP��֪ͨ���Ӻ��� */
extern OAM_1AG_MORENOVLANNOTIFY_HOOK_FUNC g_pfOam1agMoreNoVlanNotifyFunc;

/* 1AGģ���IFNET����������ָ�� */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstOam1agIfnetFunTable;
/* 1AGģ���ETHARP����������ָ�� */
extern struct IIF_COMP_ETHERNET_ComIntCFGVtbl *g_pstOam1agEthCfgTable;
/* 1AGģ���Trunk����������ָ�� */
extern struct IIF_COMP_TRUNK_ComIntCFGVtbl *g_pstOam1agTrunkCfgTable;
/* 1AGģ���Trunk����������ָ�� */
extern struct IIF_COMP_TRUNK_ComIntFUNVtbl *g_pstOam1agTrunkFunTable;

/* 1AGģ������������ָ�� */
extern struct IIF_COMP_OAM1AG_ComIntCFGVtbl *g_pstOam1agCfgTable;
/* 1AGģ������������ָ�� */
extern struct IIF_COMP_OAM1AG_ComIntFUNVtbl *g_pstOam1agFuncTable;

/* 1AGģ��L2IF�������ָ�� */
extern struct IIF_COMP_L2IF_ComIntFUNVtbl *g_pst1AGL2ifIntFunTbl;
/* 1AGģ��VRRP�������ָ�� */
extern struct IIF_COMP_VRRP_ComIntCFGVtbl *g_pstOam1agVrrpCfgTable;


/* ȫ��LTM���� */
extern OAM_1AG_LTM_SENDOUTDATA_S *g_pstLtmSendOutData[OAM_1AG_MAX_LTMSEND];

/*LTM�������к�*/
extern ULONG g_ulLtmSendId;
/*CCM�������к�*/
extern ULONG g_ulCcmSendId;
/*��ǰMA��Ŀ,��ӦVLANֵ*/
extern ULONG g_ulCurrentMaNum;

/* ���������ϻ�ʱ�䣬��������ʹ�� */
extern ULONG g_ulRmepOldTime;


extern VOS_VOID   VOS_GetCpuTick(ULONG *plow,ULONG *phigh);
extern ULONG VOS_TaskLock(VOS_VOID);
extern ULONG VOS_TaskUnlock(VOS_VOID);
extern ULONG TCPIP_Free(VOID* pBuf);
extern VOID *TCPIP_Malloc(ULONG ulInfo, ULONG ulSize);
extern VOID OAM_1AG_DebugInfo(CHAR* pcString);


extern ULONG g_ulRmepCCDetectMode;
#ifdef  __cplusplus
}
#endif

#endif
