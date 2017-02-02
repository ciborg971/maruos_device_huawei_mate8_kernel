/************************************************************************
 *                                                                                *
 *                             DHCPV4S_TIMER.C                            *
 *                                                                               *
 *  Project Code:       DHCPV4S                                        *
 *  Create Date:        2008/12/1                                  *
 *  Author:                dongmingzhou 42828                    *
 *  Modify Date:                                                         *
 *  Document:                                                           *
 *                                                                           *
 *  Function:                                                            *
 *  Others:                                                              *
 *----------------------------------------------------------------------*
 *                                                                      *
 *             Copyright 2008 - 2028 HuaWei Tech, Inc.                  *
 *                      ALL RIGHTS RESERVED                             *
 *                                                                      *
 ***********************************************************************/
#include "dhcp_inc.h"
/* add by w00316385 start */
#include "dhcpc_def.h"
/* add by w00316385 end */
#include "dhcpv4s_def.h"
#include "dhcpv4s_type.h"
#include "dhcpv4s_var.h"
#include "dhcpv4s_fun.h"
#include "dhcpv4s_dbgcmd.h"
#include "dhcpv4s_comp.h"

/*****************************************************************************
     Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_TIMER_C
/*lint +e767*/

RELTMR_T g_ulDhcpsLeaseTimerID = 0;
RELTMR_T g_ulDhcpsStateTimerID = 0;

VOID DHCPS_TimerExpireProc(ULONG ulPdpIndex)
{
    DHCPS_PRE_RESULT_S stPreResult;

    PGP_MemZero ((VOID *)&stPreResult, sizeof(DHCPS_PRE_RESULT_S));

    stPreResult.ucMsgType = DHCPS_MSG_TIMER;
    stPreResult.ulPdpIndex = ulPdpIndex;

    DHCPS_FSM_Run(&stPreResult);
    return;
}

VOID DHCPS_LeaseTimerMsgProc()
{
    ULONG ulNodNum = 0;                  /* ��¼������ĳ�ʱ�ڵ�ĸ��� */
    ULONG ulCount = 0;
    UCHAR ucLogicSlot = 0;
    ULONG ulBoardStatus = 0;
    DHCPS_TIMER_LINKLIST_S *pstTmpTimerNode = NULL;

    /* �������г������������Ӧ������ */
    if( g_ulCurrentLeaseNode > g_ulLeaseTimerCount)
    {
        VOS_Assert(0);
        return;
    }

    /*ȡ�ñ�������״̬*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    ulBoardStatus  = CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot);

    /* ����ʱ����г�ʱ������ */
    ulCount = g_ulCurrentLeaseNode % DHCPS_MAX_LEASE_TIMER_LINKLIST;
    while (NULL != g_ppstLeaseTimerList[ulCount])
    {
        pstTmpTimerNode = g_ppstLeaseTimerList[ulCount];

        /* ��ʱ����,ֻ��������д���*/
        if ( E_CRM_ACTIVE == ulBoardStatus )
        {
            DHCPS_TimerExpireProc((g_ppstLeaseTimerList[ulCount])->ulPdpIndex);
        }

        if (pstTmpTimerNode == g_ppstLeaseTimerList[ulCount])
        {
            /* ɾ��ͷ�ڵ� */
            DHCPS_DelHeadNode(&g_ppstLeaseTimerList[ulCount]);
        }

        /* ��ǰ�����Ѵ�����,��λ����һ����Ϊ�յ����� */
        while((NULL == g_ppstLeaseTimerList[ulCount])
            && (g_ulCurrentLeaseNode < g_ulLeaseTimerCount))
        {
            g_ulCurrentLeaseNode++;
            ulCount = g_ulCurrentLeaseNode % DHCPS_MAX_LEASE_TIMER_LINKLIST;
        }

         /* ����,ÿ����50���˳�һ��*/
        ulNodNum ++;
        if (ulNodNum > 50)
        {
            DHCPS_SendLeaseTimeOutInnerMsg();
            break;
        }
    }

    return;
}

VOID DHCPS_StateTimerMsgProc()
{
    ULONG ulNodNum = 0;                 /* ��¼������ĳ�ʱ�ڵ�ĸ��� */
    ULONG ulCount = 0;
    UCHAR ucLogicSlot = 0;
    ULONG ulBoardStatus = 0;
    DHCPS_TIMER_LINKLIST_S *pstTmpTimerNode = NULL;

    /* �������г������������Ӧ������ */
    if( g_ulCurrentStateNode > g_ulStateTimerCount)
    {
        VOS_Assert(0);
        return;
    }

    /*ȡ�ñ�������״̬*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    ulBoardStatus  = CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot);

    /* ����ʱ����г�ʱ������ */
    ulCount = g_ulCurrentStateNode % DHCPS_MAX_STATE_TIMER_LINKLIST;
    while (NULL != g_ppstStateTimerList[ulCount])
    {
        pstTmpTimerNode = g_ppstStateTimerList[ulCount];

        /*��ʱ����*/
        /* ��ʱ����,ֻ��������д���*/
        if ( E_CRM_ACTIVE == ulBoardStatus )
        {
            DHCPS_TimerExpireProc((g_ppstStateTimerList[ulCount])->ulPdpIndex);
        }

        if (pstTmpTimerNode == g_ppstStateTimerList[ulCount])
        {
             /* ɾ��ͷ�ڵ� */
            DHCPS_DelHeadNode(&g_ppstStateTimerList[ulCount]);
        }

         /* ��ǰ�����Ѵ�����,��λ����һ����Ϊ�յ����� */
        while((NULL == g_ppstStateTimerList[ulCount])
            && (g_ulCurrentStateNode < g_ulStateTimerCount))
        {
            g_ulCurrentStateNode++;
            ulCount = g_ulCurrentStateNode % DHCPS_MAX_STATE_TIMER_LINKLIST;
        }

         /* ����,ÿ����50���˳�һ��*/
        ulNodNum ++;
        if (ulNodNum > 50)
        {
            DHCPS_SendStateTimeOutInnerMsg();
            break;
        }
    }

    return;
}

VOID DHCPS_Lease_TimerCallBack()
{
    ULONG ulCount = 0;

    /*����û�г�ʼ���ɹ�����ִ�ж�ʱ���������Ϣ*/
    if(ulDhcpv4sTaskStep < 7000)
    {
        return;
    }


    if (ulDhcpv4sPerfInitFinish != VOS_TRUE)
    {
        /* ���³�ʼ�� */
        (VOID)DHCPS_OmInitial();
    }

    g_ulLeaseTimerCount++;        /* �ۼ� */

    ulCount = g_ulCurrentLeaseNode % DHCPS_MAX_LEASE_TIMER_LINKLIST;

    /*Ҫ����һ�����ʱ��????*/
    if(g_ulLeaseTimerCount >= DHCPS_LEASE_TMR_TIME_OVERFLOW)
    {
        if(g_ppstLeaseTimerList[ulCount] != NULL)
        {
            g_ulLeaseTimerCount--;             /* ����ʱ�򻯴��� */
        }
        else
        {
            g_ulLeaseTimerCount = 0;           /* �ؾ� */
        }
    }

    /*
     * �ж��Ƿ������ǰδ������Ľ��
     * ��������ڣ������g_ulCurrentStateNode��Ϣ
     */
    if (NULL == g_ppstLeaseTimerList[ulCount])
    {
        g_ulCurrentLeaseNode = g_ulLeaseTimerCount;
    }

    DHCPS_SendLeaseTimeOutInnerMsg();

    return;
}

VOID DHCPS_State_TimerCallBack()
{
#ifndef __WIN32_PLATFORM__
    ULONG ulCount = 0;

    /*����û�г�ʼ���ɹ�����ִ�ж�ʱ���������Ϣ*/
    if(ulDhcpv4sTaskStep < 7000)
    {
        return;
    }

    g_ulStateTimerCount++;

    ulCount = g_ulCurrentStateNode % DHCPS_MAX_STATE_TIMER_LINKLIST;

    /*Ҫ����һ�����ʱ��????*/
    /*lint -e685*/
    if(g_ulStateTimerCount >= DHCPS_STATE_TMR_TIME_OVERFLOW)
    /*lint +e685*/
    {
        if(g_ppstStateTimerList[ulCount] != NULL)
        {
            g_ulStateTimerCount--;             /* ����ʱ�򻯴��� */
        }
        else
        {
            g_ulStateTimerCount = 0;           /* �ؾ� */
        }
    }

    /*
     * �ж��Ƿ������ǰδ������Ľ��
     * ��������ڣ������g_ulCurrentStateNode��Ϣ
     */
    if (NULL == g_ppstStateTimerList[ulCount])
    {
        g_ulCurrentStateNode = g_ulStateTimerCount;
    }

    DHCPS_SendStateTimeOutInnerMsg();
#endif
    return;
}

ULONG DHCPS_Tmr_Init()
{
    ULONG ulReturn = VOS_OK;

#ifndef PRODUCT_TYPE_HSGW
    ulReturn = PGP_Timer_Create( DHCPS_SELF_CSI,
                                 DHCPS_MSG_TYPE_TIMER,
                                 DHCPS_LEASE_TIMER_PACE,
                                 ( VOID ( * )( VOID * ) )DHCPS_Lease_TimerCallBack,
                                 NULL,
                                 &g_ulDhcpsLeaseTimerID,
                                 VOS_TIMER_LOOP );
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert( 0 );
        return ulReturn;
    }
#endif
    ulReturn = PGP_Timer_Create( DHCPS_SELF_CSI,
                                 DHCPS_MSG_TYPE_TIMER,
                                 DHCPS_STATE_TIMER_PACE,
                                 ( VOID ( * )( VOID * ) )DHCPS_State_TimerCallBack,
                                 NULL,
                                 &g_ulDhcpsStateTimerID,
                                 VOS_TIMER_LOOP );
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert( 0 );
        return ulReturn;
    }

    return VOS_OK;
}

VOID DHCPS_AddLinkNode(DHCPS_TIMER_LINKLIST_S** ppstHead, DHCPS_TIMER_LINKLIST_S* pstNode)
{
    DHCPS_TIMER_LINKLIST_S* pstHeadTemp = *ppstHead;

    if (NULL == pstNode)
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_202);
        return;
    }

    if (NULL == pstHeadTemp) /* ��������û�нڵ㣬pstNode��Ϊͷ�ڵ� */
    {
        pstHeadTemp = pstNode;

        pstHeadTemp->prev = pstHeadTemp->next = NULL;
    }

    else     /* ��pstNode ���뵽�����ͷ�� */
    {
        pstNode->next = pstHeadTemp;

        pstHeadTemp->prev = pstNode;

        pstHeadTemp = pstNode;
    }

    *ppstHead = pstHeadTemp;

    return;

}

/* BEGIN: Added by jixiaoming at 2011-05-04 */
VOID DHCPS_DelHeadNode(DHCPS_TIMER_LINKLIST_S** ppstHead)
{
    DHCPS_DelLinkNode(ppstHead, *ppstHead);
}
/* END: Added by jixiaoming at 2011-05-04 */

VOID DHCPS_DelLinkNode(DHCPS_TIMER_LINKLIST_S** ppstHead, DHCPS_TIMER_LINKLIST_S* pstNode)
{
    DHCPS_TIMER_LINKLIST_S* pstHeadTemp = *ppstHead;

    if (NULL == pstNode)
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_198);
        return;
    }

    if (pstNode == pstHeadTemp)     /* ��ɾ������ͷ�ڵ㣬ͷ�ڵ�ָ��ָ����һ���ڵ� */
    {
        pstHeadTemp = pstHeadTemp->next;

        if (pstHeadTemp != NULL)
        {
            pstHeadTemp->prev = NULL;
        }
    }

    else   /* ���ڵ��������ɾ�� */
    {
        if (pstNode->prev != NULL)
        {
            pstNode->prev->next = pstNode->next;
        }

        if (pstNode->next != NULL)
        {
            pstNode->next->prev = pstNode->prev;
        }
    }

    *ppstHead = pstHeadTemp;

    PGP_MemZero(pstNode,sizeof(DHCPS_TIMER_LINKLIST_S));

    return;

}

/*****************************************************************************
 �� �� ��      : DHCPS_TIMER_StartTimer
 ��������   : ����DHCPS�Ķ�ʱ��
 �������   : ��
 �������   : ��
 �� �� ֵ      : ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��12��1��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_TIMER_StartTimer(DHCPS_LEASE_S *pstLease, DHCPS_TIMER_TYPE_E enTimerType, ULONG ulTimerLen)
{
    ULONG ulPdpIndex = 0;
    ULONG ulTimer = 0;
    ULONG ulTmpTime = 0;
    /* Added start by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
    ULONG ulBoardStatus = 0;
    /* Added end by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
    UCHAR ucLogicSlot = 0;
    if (NULL == pstLease)
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_199);
        return VOS_ERR;
    }


    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StartTimer Enter: "
                                 "pstLease->ulIndex : %u, enTimerType %u, ulTimerLen %u",
                                 pstLease->ulIndex, enTimerType, ulTimerLen);


    if ((0 == pstLease->ulIndex)
        || (pstLease->ulIndex > SDB_MAX_CONTEXT_NUM))
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_200);
        return VOS_ERR;
    }
    /* Added start by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
    /*ȡ�ñ�������״̬*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    ulBoardStatus  = CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot);
    /* Added end by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */

    ulPdpIndex = pstLease->ulIndex;
    switch (enTimerType)
    {
        case E_DHCPS_FSM_TIMER:
            {
                if ( 1 == g_pstStateTimer[ulPdpIndex].ucState )
                {
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StartTimer:  E_DHCPS_FSM_TIMER Err.");
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_201);

                    return VOS_ERR;
                }
                /*��ȡ��ʱ��ʱ������λ����ں����д�״̬���л��*/
                ulTmpTime = ulTimerLen;/*��λӦ��Ϊ��*/
                if (0 != ulTmpTime)
                {
                    ulTimer = (g_ulStateTimerCount + (ulTmpTime * 2)) % DHCPS_MAX_STATE_TIMER_LINKLIST;
                    g_pstStateTimer[ulPdpIndex].ulPdpIndex = ulPdpIndex;
                    g_pstStateTimer[ulPdpIndex].enTimerType = enTimerType;
                    g_pstStateTimer[ulPdpIndex].ulNodeTimerCount = ulTimer;
                    DHCPS_AddLinkNode(&g_ppstStateTimerList[ulTimer], &g_pstStateTimer[ulPdpIndex]);
                    g_pstStateTimer[ulPdpIndex].ucState = 1;
                    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_START;
                    if(E_CRM_ACTIVE == ulBoardStatus)
                    {
                        if (VOS_OK != AM_USM_NotifyBackupByIndex(ulPdpIndex, SDB_UPDATEVERNOTCHANGE_BACKUP))
                        {

                            /* д��־ */
                            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_TIMER_StartTimer:  The %u PdpContext \
                                calls AM_USM_NotifyBackupByIndex() failed. ",
                                ulPdpIndex);
                        }
                    }
                }
                break;
            }

        case E_DHCPS_LEASE_TIMER:
            {
                if ( 1 == g_pstLeaseTimer[ulPdpIndex].ucState )
                {
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StartTimer:  E_DHCPS_LEASE_TIMER Err.");
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_204);
                    return VOS_ERR;
                }

                if (VOS_OK != DHCPS_GetLeaseTime(ulPdpIndex, &ulTmpTime))
                {
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StartTimer:  DHCPS_GetLeaseTime Err.");
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_207);
                    return VOS_ERR;
                }

                if ((0 != ulTmpTime)
                    && (DHCPS_MAX_LEASE_TIMER_LEN > ulTmpTime))
                {
                    ulTimer = (g_ulLeaseTimerCount + (ulTmpTime * 2)) % DHCPS_MAX_LEASE_TIMER_LINKLIST;
                    g_pstLeaseTimer[ulPdpIndex].ulPdpIndex = ulPdpIndex;
                    g_pstLeaseTimer[ulPdpIndex].enTimerType = enTimerType;
                    g_pstLeaseTimer[ulPdpIndex].ulNodeTimerCount = ulTimer;
                    DHCPS_AddLinkNode(&g_ppstLeaseTimerList[ulTimer], &g_pstLeaseTimer[ulPdpIndex]);
                    g_pstLeaseTimer[ulPdpIndex].ucState = 1;
                    /* Added start by dongmingzhou 42828 at 2009-04-15 UGWV9R1C1 for ���� */
                    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_START;
                    /* Added end by dongmingzhou 42828 at 2009-04-15 UGWV9R1C1 for ���� */
                    /* Added start by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
                    if(E_CRM_ACTIVE == ulBoardStatus)
                    {
                        if (VOS_OK != AM_USM_NotifyBackupByIndex(ulPdpIndex, SDB_UPDATEVERNOTCHANGE_BACKUP))
                        {
                            /* д��־ */
                            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_TIMER_StartTimer:  The %u PdpContext \
                                calls AM_USM_NotifyBackupByIndex() failed. ",
                                ulPdpIndex);
                        }
                    }
                    /* Added end by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
                }
                break;
            }
            default:
                return VOS_ERR;
    }

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StartTimer Success.");
    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_TIMER_StopTimer
 ��������   : ֹͣDHCPS�Ķ�ʱ��
 �������   : ��
 �������   : ��
 �� �� ֵ      : ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��12��1��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG DHCPS_TIMER_StopTimer(DHCPS_LEASE_S *pstLease, DHCPS_TIMER_TYPE_E enTimerType)
{
    ULONG ulNodeTimerCount = 0;
    ULONG ulPdpIndex = 0;
    /* Added start by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
    ULONG ulBoardStatus = 0;
    /* Added end by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
    UCHAR ucLogicSlot = 0;

    if (NULL == pstLease)
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_195);
        return VOS_ERR;
    }


    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StopTimer Enter: "
                                 "pstLease->ulIndex : %u, enTimerType %u",
                                 pstLease->ulIndex, enTimerType);


    if ((0 == pstLease->ulIndex)
        || (pstLease->ulIndex > SDB_MAX_CONTEXT_NUM))
    {

        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StopTimer: pstLease->ulIndex : %u",
                                     pstLease->ulIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_196);
        return VOS_ERR;
    }
    /* Added start by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
    /*ȡ�ñ�������״̬*/
    ucLogicSlot = (UCHAR)CRM_GetSelfLogicSlotID();
    ulBoardStatus  = CRM_GetSlotPrimaryInfoOfSelfGroup(ucLogicSlot);
    /* Added end by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */

    ulPdpIndex = pstLease->ulIndex;
    switch (enTimerType)
    {
        case E_DHCPS_FSM_TIMER:
                if ( 0 != g_pstStateTimer[ulPdpIndex].ucState )
                {
                    ulNodeTimerCount = g_pstStateTimer[ulPdpIndex].ulNodeTimerCount;

                    DHCPS_DelLinkNode(&g_ppstStateTimerList[ulNodeTimerCount], &g_pstStateTimer[ulPdpIndex]);

                    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_STOP;
                    if(E_CRM_ACTIVE == ulBoardStatus)
                    {
                        if (VOS_OK != AM_USM_NotifyBackupByIndex(ulPdpIndex, SDB_UPDATEVERNOTCHANGE_BACKUP))
                        {

                            /* д��־ */
                            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_TIMER_StopTimer:  The %u PdpContext \
                                calls AM_USM_NotifyBackupByIndex() failed. ",
                                ulPdpIndex);
                        }
                    }
                }

                break;

        case E_DHCPS_LEASE_TIMER:
                if ( 0 != g_pstLeaseTimer[ulPdpIndex].ucState )
                {
                    ulNodeTimerCount = g_pstLeaseTimer[ulPdpIndex].ulNodeTimerCount;

                    DHCPS_DelLinkNode(&g_ppstLeaseTimerList[ulNodeTimerCount], &g_pstLeaseTimer[ulPdpIndex]);
                    /* Added start by dongmingzhou 42828 at 2009-04-15 UGWV9R1C1 for ���� */
                    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_STOP;
                    /* Added end by dongmingzhou 42828 at 2009-04-15 UGWV9R1C1 for ���� */
                    /* Added start by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
                    if(E_CRM_ACTIVE == ulBoardStatus)
                    {
                        if (VOS_OK != AM_USM_NotifyBackupByIndex(ulPdpIndex, SDB_UPDATEVERNOTCHANGE_BACKUP))
                        {

                            /* д��־ */
                            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_TIMER_StopTimer:  The %u PdpContext \
                                calls AM_USM_NotifyBackupByIndex() failed. ",
                                ulPdpIndex);
                        }
                    }
                    /* Added end by dongmingzhou 42828 at 2009-04-14 UGWV9R1C1 for ���� */
                }

                break;
        default:
            DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StopTimer: enTimerType : %u",
                                         enTimerType);
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_197);
            return VOS_ERR;
    }

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_TIMER_StopTimer Success.");


    return VOS_OK;

}
VOID DHCPS_ChangeTimerNode(ULONG ulOldIndex, ULONG ulNewIndex)
{
    DHCPS_TIMER_LINKLIST_S *pstTmpOldTimerNode = NULL;
    DHCPS_TIMER_LINKLIST_S *pstTmpNewTimerNode = NULL;
    DHCPS_TIMER_LINKLIST_S **ppstTmpTimerList = NULL;
    ULONG ulNodeTimerCount = VOS_NULL_DWORD;
    UCHAR ucState = VOS_NULL_BYTE;
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_ChangeTimerNode Enter: ulOldIndex = %u ,ulNewIndex = %u", ulOldIndex, ulNewIndex);

    ucState = g_pstDhcpSLease[ulOldIndex].ucLeaseState;

    /*�ж�״̬����Ч��*/
    if (ucState >= DHCPS_STATE_MAX)
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_ChangeTimerNode : ERROR ! ucState = %u", ucState);
        return;
    }

    enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[ucState].ulTimerType;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_ChangeTimerNode : ucState = %u ,TimerType = %u", ucState, enTimerType);

    if (E_DHCPS_FSM_TIMER == enTimerType)
    {
        pstTmpOldTimerNode = &(g_pstStateTimer[ulOldIndex]);
        pstTmpNewTimerNode = &(g_pstStateTimer[ulNewIndex]);
        ppstTmpTimerList = g_ppstStateTimerList;
    }
    else if (E_DHCPS_LEASE_TIMER == enTimerType)
    {
        pstTmpOldTimerNode = &(g_pstLeaseTimer[ulOldIndex]);
        pstTmpNewTimerNode = &(g_pstLeaseTimer[ulNewIndex]);
        ppstTmpTimerList = g_ppstLeaseTimerList;
    }
    else
    {
        return;
    }

    VOS_MemCpy(pstTmpNewTimerNode, pstTmpOldTimerNode, sizeof(DHCPS_TIMER_LINKLIST_S));
    pstTmpNewTimerNode->ulPdpIndex = ulNewIndex;
    pstTmpNewTimerNode->prev = NULL;
    pstTmpNewTimerNode->next = NULL;

    if (0 != pstTmpOldTimerNode->ucState)
    {
        ulNodeTimerCount = pstTmpOldTimerNode->ulNodeTimerCount;
        DHCPS_DelLinkNode(&ppstTmpTimerList[ulNodeTimerCount], pstTmpOldTimerNode);
        DHCPS_AddLinkNode(&ppstTmpTimerList[ulNodeTimerCount], pstTmpNewTimerNode);
    }

    return;
}

ULONG DHCPS_IsTimerOn(ULONG ulIndex, ULONG ulTimerType)
{
    DHCPS_TIMER_LINKLIST_S *pstTmpTimerNode = NULL;
    if ( 0 == ulIndex || ulIndex > SDB_MAX_CONTEXT_NUM )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_BackupRestoreProc : slave DHCPS lease index error!" );
        return VOS_FALSE;
    }

    if (E_DHCPS_LEASE_TIMER == ulTimerType)
    {
        pstTmpTimerNode = &g_pstLeaseTimer[ulIndex];
    }
    else if (E_DHCPS_FSM_TIMER == ulTimerType)
    {
        pstTmpTimerNode = &g_pstStateTimer[ulIndex];
    }
    else
    {
        return VOS_FALSE;
    }

    if (1 == pstTmpTimerNode->ucState)
    {
        return VOS_TRUE;
    }
    else
    {
        return VOS_FALSE;
    }
}

/*����PDPindex ��ȡ��Լʱ��, ����ֵ��λΪ��*/
ULONG DHCPS_GetLeaseTime(ULONG ulPdpIndex, ULONG *pulTimerLen)
{
    ULONG ulRet = 0;
    USHORT usApnIndex = 0;
    USHORT usDay = 0;
    UCHAR  ucHour = 0;
    UCHAR ucMinute = 0;
    USHORT usUnlimited = 0;
    AM_CTX_APN_INFO_S stApnInfo = { 0 };


    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_GetLeaseTime: Enter :ulPdpIndex = %u",
                          ulPdpIndex);

    if (NULL == pulTimerLen)
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_GetLeaseTime: pulTimerLen NULL");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_213);
        return VOS_ERR;
    }

    if ((0 == ulPdpIndex)
        || (ulPdpIndex > SDB_MAX_CONTEXT_NUM))
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_205);
        return VOS_ERR;
    }

    ulRet = AM_CtxApiGetApnInfo(ulPdpIndex, &stApnInfo);
    if (ulRet != VOS_OK )
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_GetLeaseTime: AM_CtxApiGetApnInfo Err");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_206);
        return VOS_ERR;
    }

    usApnIndex = stApnInfo.usApnIndex;
    if (usApnIndex >= MAX_APN_NUM)
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_GetLeaseTime: usApnIndex %d",
                                      usApnIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_214);
        return VOS_ERR;
    }
    usDay = g_pstExpiredInfor[usApnIndex].usDay;
    ucHour = g_pstExpiredInfor[usApnIndex].ucHour;
    ucMinute= g_pstExpiredInfor[usApnIndex].ucMinute;
    usUnlimited = g_pstExpiredInfor[usApnIndex].usUnlimited;

    if (0xff == usUnlimited)
    {
        *pulTimerLen = DHCPS_TIMER_LEN_UNLIMITED;
    }
    else
    {
        *pulTimerLen = 24*60*usDay + 60*ucHour + ucMinute;/*��λӦ��Ϊ��*/
    }

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_GetLeaseTime: DHCPS_GetLeaseTime : %u",
                                     (*pulTimerLen));


    return VOS_OK;
}

