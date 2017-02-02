/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_var.h
*
*  Project Code:
*   Module Name: PTPV2 var
*  Date Created: 2014-03-03
*        Author: luoagwoei & dutianyi
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03  luoagwoei & dutianyi      Create
*******************************************************************************/

#ifndef _PTPV2_VAR_H_
#define _PTPV2_VAR_H_

#ifdef __cplusplus
extern "C" {
#endif

/*����ֻ����һ�γ�ʼ��*/
extern ULONG g_ulPtpV2InitFlag;

/*����PTPģ����ź���ȫ�ֱ���*/
extern ULONG g_ulPTPV2Sem;

/*PTP ģʽ: OC ����BC��Ŀǰ��֧��TC*/
extern ULONG g_ulPtpV2ClockType;

/*PTPV2��ʱ������ID*/
extern ULONG g_ulPtpV2TimerQId;

/*PTPV2���Ķ��е�ID*/
extern ULONG g_ulPtpV2PktQId;

/*PTPV2����ID*/
extern ULONG g_ulPtpV2TaskId;

/*PTP����ʱ��ID��VOS��ʱ��,100ms*/
extern ULONG g_ulPtpV2BaseTimerId;

#define PTPV2_INVALID_SOCKEID  (-1)

/*PTP���Ľ��յ��¼�ID����ΧShell�ɸ�������������������*/
extern ULONG g_ulPtpV2PktRcvEventId;


extern AVL3_TREE_INFO_S g_PtpV2TreeInfo;


extern AVL3_TREE_S g_PtpV2Tree; /*ȫ��PTP �˿����ṹ*/


extern DLL_S  g_GlobalForeignMasterList; /*ȫ�ֵı���master*/


extern PTPV2_GLOBAL_INFO_S  *g_pstPtpGlobalInfo;/*Ĭ�ϰ�1588ѡԴ*/

extern PTPV2_PORT_MANAGE_S *g_pstPortManageInfo;

extern DLL_S  g_PtpV2TimerList; /*ȫ�ֵĶ�ʱ������*/

extern const UCHAR g_szMacPTPV2_E2E[PTPV2_MACADDRLEN];
extern const UCHAR g_szMacPTPV2_P2P[PTPV2_MACADDRLEN];

extern PTPV2_PORT_SUB_INFO_S  *g_pstOCPortSubInfo;

/* ����PTP���Ĳ��ͷ� */
extern ULONG (*g_pfETH_PTPV2_HOOK)(MBUF_S*);

/*����PTPж�ص�ͬ���ź���*/
extern ULONG g_ulSynsemId;

extern TCPIP_PTP_PPI_HOOK_FUNC g_pfPtpV2PpiHookFunc;

/*��ǰѡ�е�ʱ��Դ*/
extern PTPV2_FOREIGN_MASTER_S *g_pstBmcEbest; 

extern ULONG g_ulPtpCompVersion;

/* �澯��Ϣ�������ָ�����Ͷ��� */
extern TCPIP_PTP_WARN_OUTPUT_FUNC  g_pfPtpV2WarnOutput;

/*ȫ�ֱ��Ĳ�����ָ��*/
extern TCPIP_PTP_CAPTURE_PACKET_FUNC g_pfPtpV2CapturePktFunc;

/*ȫ�ֱ���ͳ��*/
extern TCPIP_PTP_PKT_STAT_S g_stGlobalPtpV2PktStat;

/*PTPѡ��ʱ��Դ�ı��*/
extern UCHAR g_ucPtpGotTimeSourceFlag;

/* 30��ѡ����Դ��һ���澯��ʱ��*/
extern ULONG g_ulPtpWarningTimerId;

/*���Կ���,����ά�� , Ĭ��ȫ�����عر�*/
extern ULONG g_ulPtpV2GlobalDbgSwitch;

/*����D0 ��master*/
extern PTPV2_FOREIGN_MASTER_S  *g_pstVirtualD0;

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */

#endif   /* end of _PTPV2_VAR_h_   */
