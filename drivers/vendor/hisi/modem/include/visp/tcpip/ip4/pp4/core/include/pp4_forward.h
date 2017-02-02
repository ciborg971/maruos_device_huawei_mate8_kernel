/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              pp4_forward.h
*
*  Project Code: VISP1.5
*   Module Name: PP4  
*  Date Created: 2002-06-18
*        Author: chenshuanglong(28510)
*   Description: pp4_forward.cͷ�ļ�
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

#ifndef _PP4_FORWARD_H_
#define _PP4_FORWARD_H_

/* IP����ת�� */
extern ULONG IP_Forward(MBUF_S *pstMBuf, UCHAR ucbSrcRt, IFNET_S *pstIfNet);


#endif  /* _PP4_FORWARD_H_  */

#ifdef  __cplusplus
}
#endif


