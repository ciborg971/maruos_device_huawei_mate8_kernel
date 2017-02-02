/*******************************************************************************
*
*                Copyright 2007, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              poes_var.h
*
* Project Code: VISPV100R006C02
*  Module Name: POES
* Date Created: 2007-07-18
*       Author: lijing(52889)
*  Description: POESģ���ȫ�ֱ�������
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2007-07-18   lijing(52889)           Create
*
*******************************************************************************/

#ifndef  _POES_VAR_H_
#define  _POES_VAR_H_

#if __cplusplus
extern "C"{
#endif

/* POESģ����Ϣ */
extern POES_MOD_INFO_S g_stPoesModInfo;

/* Core��ʹ�õĻص������� */
extern POES_SHELL_CALLBACK_SET_S g_stPoesShellApi; 

/* POESģ������ʱ��ID */
extern ULONG g_ulPoesGlobalTimerId;

/* POESģ���IFNET����������ָ�� */
extern struct IIF_IFNET_ComIntFUNVtbl *g_pstPoesIfnetFunTable;

/* ACName */
extern UCHAR g_szACName[POES_ACNAME_MAX_LEN];

/* ȫ��session�� */
extern USHORT g_usSessionNum;

/* ȫ��session������ */
extern USHORT g_usMaxSession;

/* ����MAC session������ */
extern USHORT g_usMaxSessionPerOurMac;

/* �Զ�MAC session������ */
extern USHORT g_usMaxSessionPerHisMac;

/* ȫ�ֵ�����Ϣ���� */
extern POES_DEBUG_INFO_S g_stPoesDbgInfo;

/* PPPoE����LCP/IPCP UP/DOWN�澯���� */
extern ULONG g_ulPoesWarningSw;

/* POES���ƿ������׽ڵ� */
extern DLL_S g_stPoesCbList;

/* POES�Զ�MAC���ƿ������׽ڵ� */
extern DLL_S g_stPoesHisMacList;

/* ��ȡACName�Ĺ��Ӻ���ָ�� */
extern GetACName_HOOK_FUNC g_pfGetACName_HOOK_FUNC;

#if __cplusplus
}
#endif

#endif 

