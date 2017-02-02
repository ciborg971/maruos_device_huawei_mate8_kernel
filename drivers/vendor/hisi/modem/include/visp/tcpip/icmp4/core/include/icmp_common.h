/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              icmp_common.h
*
* Project Code: VISP1.5 
*  Module Name: ICMP4
* Date Created: 2006-01-24
*       Author: Li LiXiang
*  Description: ������Icmp�й����궨��,��������
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

#ifndef _ICMP_COMMON_H_
#define _ICMP_COMMON_H_

#define SYSTRC_IP_ICMP_BASE   100

#define IP_ICMP4_COM          ((SYSTRC_IP_ICMP_BASE << 8) + 10) /* for iicmp4.c */
#define IP_ICMP4_FAC          ((SYSTRC_IP_ICMP_BASE << 8) + 11) /* for iicmp_fac.c */
#define IP_ICMP_SH_CONFIG     ((SYSTRC_IP_ICMP_BASE << 8) + 12) /* for icmp_sh_cfg.c */

/* product provided functions */
extern ULONG getSelfBoardId();


#endif  /*  _ICMP_COMMON_H_  */

#ifdef  __cplusplus
}
#endif

