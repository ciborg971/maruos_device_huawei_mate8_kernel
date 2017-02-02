/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              am4_common.h
*
*  Project Code: VISPV100R005
*   Module Name: AM4  
*  Date Created: 2006-01-04
*        Author: Li LiXiang
*   Description: ������Am4�в�Ʒ�ṩ�ĺ�������ģ�����
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2006-01-04   Li LiXiang              Create
*  2006-04-21   Jiangtao                ���ݱ�̹淶�����ļ����й淶������ 
*
*******************************************************************************/

#ifdef  __cplusplus
extern  "C"{
#endif

#ifndef _AM4_COMMON_H_
#define _AM4_COMMON_H_


#define SYSTRC_IP_AM4_BASE 102


#define IP_AM4_COM          ((SYSTRC_IP_AM4_BASE << 8) + 10) /* for ipp4.c */
#define IP_AM4_FAC          ((SYSTRC_IP_AM4_BASE << 8) + 11) /* for ipp4_fac.c */


/* product provided functions */
extern ULONG getSelfBoardId();
extern ULONG getMainboardId();

#endif  /*  _AM4_COMMON_H_  */


#ifdef  __cplusplus
}
#endif

