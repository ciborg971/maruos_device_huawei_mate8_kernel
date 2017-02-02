/*************************************************************************
 *
 *              Copyright 2005, Huawei Technologies Co. Ltd.
 *                          ALL RIGHTS RESERVED
 * 
 *-----------------------------------------------------------------------*
 *
 *                              osicp_type.h
 *
 *  Project Code: VISPV1R6C03
 *   Module Name: osicp
 *  Date Created: 2007-07-11
 *        Author: Zhangchunyu
 *   Description:  PPP��OSICPЭ��ģ���������ݽṹ       
 *
 *-----------------------------------------------------------------------*
 *  Modification History
 *  DATE            NAME            DESCRIPTION
 *  2007-07-11      Zhangchunyu        Create
 *
 *************************************************************************/


#ifndef      _OSICP_TYPE_H_
#define      _OSICP_TYPE_H_

#ifdef      __cplusplus
extern "C" {
#endif		/* end of __cplusplus */



typedef struct tagPppOsicpInfo
{
    PPPINFO_S *pstPppInfo ;             /* PPP���ƿ�ָ�� */
    PPPFSM_S  stFsm;                    /* OSICPЭ��״̬�� */
    PPP_OSICP_OPTION_S stGotOptions;    /* �Ѿ�Э�̵����ҵ�ѡ�� */
    PPP_OSICP_OPTION_S stHisOptions;    /* �Ѿ�Э�̵��ĶԷ���ѡ�� */
    PPP_OSICP_OPTION_S stWantOptions;   /* ��ϣ����Է�Э�̵��ҵ�ѡ�� */
    PPP_OSICP_OPTION_S stAllowOptions;  /* ������Է�Э�̵��ҵ�ѡ�� */
} PPPOSICPINFO_S ;

typedef struct tagOSICP_ModInfo
{
    ULONG ulMID_OSICP;          /*ģ��ID*/
}OSICP_MOD_INFO_S;

#ifdef      __cplusplus
}
#endif      /* end of __cplusplus */

#endif      /* end of _OSICP_TYPE_H_ */



