/*******************************************************************************
*
*
*                Copyright 2006, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              Ping_ext.h
*
*  Project Code: VISP1.5
*   Module Name: ping  
*  Date Created: 2006-4-28
*        Author: luyao(60000758)
*   Description: ����pingģ����Ҫ���õ�����ģ��ĺ�������text�� 
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE        NAME             DESCRIPTION    
*  -----------------------------------------------------------------------------
*  2006-4-28   luyao(60000758)  Creat the first version.
*  2006-04-27  luyao            ���ݱ�̹淶�����ļ����й淶������
*
*******************************************************************************/


#ifndef _PING_EXT_H_
#define _PING_EXT_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "tcpip/public/tcpip_basefun.h"

/**************************************************************\
* �ⲿģ���ṩ�Ľӿں�������
\**************************************************************/
extern ULONG IF_GetIfIndexByFullName(CHAR *pszIfName, ULONG *pulIfIndex);
extern ULONG IF_HookForQuery(ULONG ulFunc, CHAR * szType, CHAR * szInput, ULONG pHelpVec);

#ifdef __cplusplus
}
#endif

#endif

