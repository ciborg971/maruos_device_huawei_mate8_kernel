/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              iicmp.h
*
* Project Code: VISPV100R005
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: ����icmp�ṩ�ĵ�����������
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

#ifndef _I_PP4_H_
#define _I_PP4_H_

/* icmp����ṩ�������� */
extern IIF_IPV4_IP_ICMP_ComIntCFG g_IComInt_ICMP_CFG;
extern IIF_IPV4_IP_ICMP_ComIntFUN g_IComInt_ICMP_FUN;
extern IIF_IPV4_IP_ICMP_ComIntSSA g_IComInt_ICMP_SSA;

/* icmpģ����Ϣ */
extern ComponentInfo m_CompIcmpInfo;

#endif  /*  _I_PP4_H_  */

#ifdef  __cplusplus
}
#endif

