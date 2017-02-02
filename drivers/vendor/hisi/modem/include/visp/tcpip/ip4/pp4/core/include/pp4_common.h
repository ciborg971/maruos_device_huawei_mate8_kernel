/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_common.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: ���ú궨��
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2002-06-18   chenshuanglong(28510)   Create
*  2006-11-01   zhoutong(43740)         �淶������
*
*******************************************************************************/


#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _PP4_COMMON_H_
#define _PP4_COMMON_H_

/* �ļ���� */
#define SYSTRC_IP_PP4_BASE 101

#define IP_PP4_COM          ((SYSTRC_IP_PP4_BASE << 8) + 10) /* for ipp4.c */
#define IP_PP4_FAC          ((SYSTRC_IP_PP4_BASE << 8) + 11) /* for ipp4_fac.c */

/* ��Ϣ���� */
#define IP_PP4_INFO_REASFULL    1
#define IP_PP4_INFO_REASPAFULL  2

/* ��Ϣ��ʽ */
#define  MSG_FMT_NONE           1 /* û�в��� */
#define  MSG_FMT_ONE            7 /* one ULONG */

/* ��ȡ������ */
extern ULONG getSelfBoardId();
extern VOID IP_PP4_DropPkt_Stat(MBUF_S *pstMbuf, UCHAR ucInOrOut);

#endif  /*  _PP4_COMMON_H_  */

#ifdef  __cplusplus
}
#endif



