/*******************************************************************************
*
*
*                Copyright 2014, Huawei Technologies Co. Ltd.
*                            ALL RIGHTS RESERVED
*
*-------------------------------------------------------------------------------
*
*                              nd_dad.h
*
*  Project Code: Dopra V3R2
*   Module Name:   
*  Date Created: 2014-02-21
*        Author: guojianjun178934
*   Description: DAD�������ͷ�ļ�
*
*-------------------------------------------------------------------------------
*  Modification History
*  DATE         NAME                    DESCRIPTION
*  -----------------------------------------------------------------------------
*  2014-02-21   guojianjun178934        Create
*
*******************************************************************************/

#ifndef _ND_DAD_H
#define _ND_DAD_H

#ifdef  __cplusplus
extern "C"{
#endif  /* #ifdef  __cplusplus */

typedef struct tagND_DADExt_Timer_Node
{
    SLL_NODE_S stSLLNode;
    ULONG ulIfIndex;
    IN6ADDR_S stTgtAddr;  /*��ͻĿ���ַ*/
    IP6IFADDR_S *pstIp6IfAddr; /*���ڳ�ͻ�ĵ�����ַ*/
    ULONG ulDADExtInterval;
    ULONG ulDADExtAttempt; /*������DAD���ĵĴ���*/
    ULONG ulExpireHigh; /*��һ��DAD����Ԥ��ʱ��*/
    ULONG ulExpireLow;  /*��һ��DAD����Ԥ��ʱ��*/
    BOOL_T bFastDetect; /*�Ƿ����̽��DADExt*/
    UCHAR  ucpad[2];
}ND_DADEXT_TIMER_NODE;

#define IP6_ND_DADEXT_TIMER_EXPIRE(DADEXT_TIMER, CUR_MS_H, CUR_MS_L)  \
  IP6_ND_TIMER_EXPIRE_BY_MS(CUR_MS_H, CUR_MS_L, (DADEXT_TIMER)->ulExpireHigh, (DADEXT_TIMER)->ulExpireLow)

#ifdef  __cplusplus
}
#endif  /* #ifdef  __cplusplus */

#endif  /* _ND_DAD_H*/

