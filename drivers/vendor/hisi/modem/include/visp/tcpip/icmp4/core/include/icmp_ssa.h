/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_ssa.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: ����Icmp�лص��������ϱ����ͻص�����ע�ắ��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-24   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _ICMP_SSA_H_
#define _ICMP_SSA_H_

/* �ص��������� */
extern IP_ICMP_IC_CALLBACK_SES_S g_stIcCallbackSet;

/* ע��ص����� */
ULONG IP_ICMP_RegisterIcCallbacks(IP_ICMP_IC_CALLBACK_SES_S *pstCallbackSet);

extern IP6_ICMP6_SH_CALLBACUP_SET_S  g_stPingICMP6CallbackFun;
ULONG PING6_PING_Register(IP6_ICMP6_SH_CALLBACUP_SET_S *pstICMP6CallBack);


#endif  /*  _ICMP_SSA_H_  */

#ifdef  __cplusplus
}
#endif

