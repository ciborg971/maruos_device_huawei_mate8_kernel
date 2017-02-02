/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                               mp_var.h
 *
 *  Project Code: VISP1.5
 *   Module Name: MP
 *  Date Created: 2005-09-15
 *        Author: YaoChengliang
 *   Description: MP���˽��ȫ�ֱ���������˵��
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2005-09-15      YaoChengliang   Create
 *  2006-03-31      ZhuKun          Adjust for D00663
 *  2006-04-21      ZhuKun          Adjust for D00876
 *
 *************************************************************************/

#ifndef _MP_VAR_H_
#define _MP_VAR_H_

#ifdef  __cplusplus
extern "C"{
#endif


/* ������MP�û����� */
extern USHORT g_usMpUserNameNum;

/* �û���-��ģ���Ӧ��ͷ�ڵ� */
extern DLL_S *g_pstUserInfoList;

/* ����·��MP-GROUP�ӿڶ�Ӧ��ͷ�ڵ� */
extern DLL_S * g_pstMpgroupList;

/* MP���ı�־ */
extern CHAR *g_cMpFlag[] ;

/* MP debug print info */
extern CHAR *g_cMpDebugPrintInfo[];

/* Endpoint Discriminator for MP */
extern UCHAR g_pucdiscr_addr[MP_DISCRIMINATOR_MAX_LENGTH];

/* VT and VA's name provided by IFNET */
extern CHAR * VirtualTemplateName;
extern CHAR * VirtualAccessName;

/* MP module info structure */
extern MP_MOD_INFO_S        g_stMPModInfo;

/* MP register callback API structure for SHELL */
extern MP_SHELL_CALLBACK_S  g_stMPShellApi; 

/* Virtual table pointer of IFNET and PPP used by MP core */
extern struct IIF_IFNET_ComIntFUNVtbl       *g_pstMpCoreIfnetComFunTable;
extern struct IIF_COMP_PPP_ComIntFUNVtbl    *g_pstMpCorePppComFunTable;
extern struct IIF_PPPMUX_ComIntFUNVtbl      *g_pstMpCorePppMuxFunTable; /*add by wuhailan for SWID00213,2007-3-9.*/

extern ULONG g_ulMpReorderWindowTimes;

extern MPQOSQueInit_HOOK_FUNC g_pfMpGroupQueInit;
extern MPQOSCloneTemplateQue_HOOK_FUNC g_pfCloneTemplateQue;
extern MPQOSDelFatherFromQos_HOOK_FUNC g_pfDelFatherFromQos;
extern MPQOSChange_HOOK_FUNC g_pfQosChange;
extern MPQOSTransmitDone_HOOK_FUNC g_pfMPQOS_TransmitDone;
extern QOSTransmitDone_HOOK_FUNC  g_pfQOS_TransmitDone;
extern MPQOSIfCanSendPkt_HOOK_FUNC g_pfIfCanSendPkt;
extern QOSTransmit_HOOK_FUNC  g_pfQM_Transmit;

extern ULONG *g_pulMpChanNumCacheArray;

#ifdef  __cplusplus
}
#endif  /* end of __cplusplus */

#endif
