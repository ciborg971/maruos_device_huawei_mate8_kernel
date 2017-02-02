/*******************************************************************************
*
*
*                Copyright 2008, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              ptpv2_var.c
*
*  Project Code:
*   Module Name: PTPV2 var
*  Date Created: 2014-03-03
*        Author: luoagwoei
*   Description:
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE            NAME                DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-03-03    luoagwoei               Create
*******************************************************************************/

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/ptpv2/include/ptpv2_ext.h"
#include "tcpip/ptpv2/include/ptpv2_common.h"

/*����ֻ����һ�γ�ʼ��*/
ULONG g_ulPtpV2InitFlag = PTPV2_NO;

/*����PTPģ����ź���ȫ�ֱ���*/
ULONG g_ulPTPV2Sem = 0;

/*PTP ģʽ: OC ����BC��Ŀǰ��֧��TC*/
ULONG g_ulPtpV2ClockType = PTPV2_CLOCK_TYPE_NULL;

/*PTPV2��ʱ������ID*/
ULONG g_ulPtpV2TimerQId = 0;

/*PTPV2���Ķ��е�ID*/
ULONG g_ulPtpV2PktQId = 0;

/*PTPV2����ID*/
ULONG g_ulPtpV2TaskId = 0;

/*PTP����ʱ��ID��VOS��ʱ��,100ms*/
ULONG g_ulPtpV2BaseTimerId = 0;

/*PTP���Ľ��յ��¼�ID����ΧShell�ɸ�������������������*/
ULONG g_ulPtpV2PktRcvEventId = SE_ASYNC | PTPV2_IEEE8023MSG_EVENT_ID;


AVL3_TREE_INFO_S g_PtpV2TreeInfo =
{
    PTPV2_Port_Tree_Compare,
    0,
    PTPV2_Tree_offset(PTPV2_PORT_S, stPtpPortNode)
};


AVL3_TREE_S g_PtpV2Tree =
{
    NULL,
    NULL,
    NULL
}; /*ȫ��PTP �˿����ṹ*/


DLL_S  g_GlobalForeignMasterList; /*ȫ�ֵı���master*/

TCPIP_PTP_PPI_HOOK_FUNC g_pfPtpV2PpiHookFunc = NULL;

PTPV2_GLOBAL_INFO_S*  g_pstPtpGlobalInfo = NULL;/*Ĭ�ϰ�1588ѡԴ*/

PTPV2_PORT_MANAGE_S* g_pstPortManageInfo = NULL;

/*ȫ�ֵĶ�ʱ������*/
DLL_S  g_PtpV2TimerList; 

const UCHAR g_szMacPTPV2_E2E[PTPV2_MACADDRLEN] = {0x01, 0x1B, 0x19, 0x00, 0x00, 0x00};
const UCHAR g_szMacPTPV2_P2P[PTPV2_MACADDRLEN] = {0x01, 0x80, 0xC2, 0x00, 0x00, 0x0E};

PTPV2_PORT_SUB_INFO_S*  g_pstOCPortSubInfo = NULL;

/*����PTPж�ص�ͬ���ź���*/
ULONG g_ulSynsemId = 0;

/*��ǰѡ�е�ʱ��Դ*/
PTPV2_FOREIGN_MASTER_S *g_pstBmcEbest  = NULL; 

/*����D0 ��master*/
PTPV2_FOREIGN_MASTER_S  *g_pstVirtualD0 = NULL;

/*PTPѡ��ʱ��Դ�ı��*/
UCHAR g_ucPtpGotTimeSourceFlag = PTPV2_NO; 

/* 30��ѡ����Դ��һ���澯��ʱ��*/
ULONG g_ulPtpWarningTimerId = NULL;

/* �澯��Ϣ�������ָ�����Ͷ��� */
TCPIP_PTP_WARN_OUTPUT_FUNC g_pfPtpV2WarnOutput = NULL;

/*ȫ�ֱ��Ĳ�����ָ��*/
TCPIP_PTP_CAPTURE_PACKET_FUNC g_pfPtpV2CapturePktFunc = NULL;

/*ȫ�ֱ���ͳ��*/
TCPIP_PTP_PKT_STAT_S g_stGlobalPtpV2PktStat = {0};

/*���Կ���,����ά�� , Ĭ��ȫ�����عر�*/
ULONG g_ulPtpV2GlobalDbgSwitch = 0;

#ifdef __cplusplus
}
#endif   /* end of __cplusplus          */
