/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_init.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: ������Icmp�еĳ�ʼ��������ȫ�ֱ���
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������ 
*  2006-11-08   zhoutong(43740)         �淶������
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _ICMP_INIT_H_
#define _ICMP_INIT_H_

/* ICMP4ģ����Ϣ */
extern IP_ICMP_MOD_INFO_S g_stIPIcmpModInfo;

/* ICMP4ģ����Կ���*/ 
extern ULONG   ulDebugIcmpFlag;

extern ULONG g_ulPingForbidFlag;

/* ������Ӧ��ַ���������Ŀ��� */
extern UCHAR   g_ucbIcmpMaskNotReply;

/* Դ��ַ��Ŀ�ĵ�ַ */
extern SOCKADDRIN_S g_stIcmpSrc;
extern SOCKADDRIN_S g_stIcmpDst;

/* ICMP������������ָ����� */
extern struct IIF_IPV4_IP_PP4_ComIntFUNVtbl *g_pstIcmpPp4Vtbl;
extern struct IIF_IP4_RIP4_ComIntFunVtbl    *g_pstIcmpRip4Vtbl;
extern struct IIF_IPV4_IP_AM4_ComIntFUNVtbl *g_pstIcmpAm4Vtbl;

#define ICMP_VRF_MID 0x00000003

/* �����ʼ������ */
ULONG IP_ICMP_Init_Com(COM_ID_INFO_S *pstComInfo, ULONG  ulComLen) ;
ULONG IP_ICMP_Activate_Com();
ULONG IP_ICMP_SetModuleInfo(IP_ICMP_MOD_INFO_S *pstModInfo );

#endif  /*  _ICMP_INIT_H_  */

#ifdef  __cplusplus
}
#endif

