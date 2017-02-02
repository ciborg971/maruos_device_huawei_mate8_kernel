/************************************************************************
 *                                                                                *
 *                             DHCPV4S_FSM.C                            *
 *                                                                               *
 *  Project Code:       DHCPV4S                                        *
 *  Create Date:        2008/11/22                                  *
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
#include "dhcpv4s_comp.h"
#include "dhcpv4s_dbgcmd.h"


/*****************************************************************************
 �� �� ��      : DHCPS_FSM_Run
 ��������   : DHCPS��״̬����ں���
 �������   : ��
 �������   : ��
 �� �� ֵ      : ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
VOID DHCPS_FSM_Run(DHCPS_PRE_RESULT_S *pstPreResult)
{
    UCHAR                    ucMsgType             = 0xff;
    UCHAR                    ucStateMachine       = 0xff;
    DHCPS_STATE_RET    stStateChangeRet;
    DHCPS_LEASE_S        *pstLease               = NULL;
    PF_DHCPS_FSM         pFuncStateMachine  = NULL;
    ULONG                    ulRet                       = VOS_OK;
    ULONG                    ulCount                    =0;
    ULONG                    ulPDPContextIndex   = 0;
    ULONG ulTimerOutLength = 0;
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Enter");

    if (NULL == pstPreResult)
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : ERROR parameter is NULL");
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_000);
        VOS_Assert(0);
        return;
    }

    DHCPV4S_ShowCode((UCHAR*)pstPreResult, sizeof(DHCPS_PRE_RESULT_S));

    PGP_MemZero((VOID *)&stStateChangeRet, sizeof(DHCPS_STATE_RET));

    /*ȡ���������*/
    ucMsgType = pstPreResult->ucMsgType;
    ulPDPContextIndex   = pstPreResult->ulPdpIndex;
    if ( (0 == ulPDPContextIndex)
        ||(ulPDPContextIndex > SDB_MAX_CONTEXT_NUM))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : ERROR ulPDPContextIndex is %d",
                                    ulPDPContextIndex);
        /* ��˳���޸ļ�������ͬ*/
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_001);
        VOS_Assert(0);
        return;
    }

    /*��ʱ����Լ = ȫ�ֱ�������Լ����ʱӦ����ΪNULL��*/
    pstLease = &g_pstDhcpSLease[ulPDPContextIndex];

    pstPreResult->pstLease = pstLease;

    ucStateMachine = pstLease->ucLeaseState;

    /*�ж���Ϣ��״̬����Ч��*/
    if ((ucMsgType >= DHCPS_MSG_MAX ) || (ucStateMachine >= DHCPS_STATE_MAX))
    {
        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : ERROR ! ucMsgType = %d , ucStateMachine = %d",ucMsgType,ucStateMachine);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_002);
        return;
    }

    /*ȡ���ض���Ϣ�µĻص�����*/
    pFuncStateMachine = g_stDHCPSStateMachine[ucStateMachine].pFuncStateMachine[ucMsgType];
    if(NULL == pFuncStateMachine)
    {
        /*ĳ״̬�յ���û��ע�����Ϣ��ֱ�ӷ���*/
        g_stDHCPSStateMachine[ucStateMachine].ErrMsgCount[ucMsgType]++;
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_003);
        return;
    }

    /*ȡ��ʱ���Ͷ�ʱ������*/
    enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[ucStateMachine].ulTimerType;

    /*ֻҪ��Ϣ���ͺͻص�������Ϊ�գ�����ִ��*/
    /*lint -e716*/
    while (1)
    /*lint +e716*/
    {
        /*�����������ѭ��������
        �����Ƿ������쳣��ֱ��������������ѭ��*/
        ulCount ++;
        if(ulCount > DHCPS_FSM_MAX_STEP)
        {
            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine Run times = %u",ulCount);
            DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine Run times = %u",ulCount);
            //VOS_Assert(0);
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_004);
            return;
        }

        /*ֹͣ״̬����ʱ��*/
        if (1 == g_pstStateTimer[ulPDPContextIndex].ucState)
        {
            if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, enTimerType))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : DHCPS_TIMER_StopTimer g_pstStateTimer Err : "
                                             "ulPDPContextIndex= %u, enTimerType %u",
                                             ulPDPContextIndex,
                                             enTimerType);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_005);
            }
        }

        /*Todo:��INFORM��Ϣ��������Ϣ��Ҫɾ����Լ��ʱ��*/
        if ((1 == g_pstLeaseTimer[ulPDPContextIndex].ucState)
            && ( DHCPS_MSG_RECIVE_INFORM != ucMsgType))
        {
            if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, enTimerType))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : DHCPS_TIMER_StopTimer g_pstLeaseTimer Err : "
                                             "ulPDPContextIndex= %u, enTimerType %u",
                                             ulPDPContextIndex,
                                             enTimerType);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_006);
            }
        }

        /*����״̬������*/
        ulRet = (*pFuncStateMachine)(pstPreResult, &stStateChangeRet);
        if(ulRet != VOS_OK)
        {
            DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_007);
        }

        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Change Result = %d, ulNewState = %d, ulMessageType %d",
                                    stStateChangeRet.ulResult,
                                    stStateChangeRet.ulNewState,
                                    stStateChangeRet.ulMessageType);

        switch (stStateChangeRet.ulResult)
        {
            /*״̬Ǩ�Ƴɹ���Ǩ�Ƶ��µ�״̬*/
            case DHCPS_STATE_CHANGE_OK:
            {
                if (stStateChangeRet.ulNewState >= DHCPS_STATE_MAX)
                {
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, ulNewState = %u",
                                                    ucStateMachine,
                                                    stStateChangeRet.ulNewState);
                    DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, ulNewState = %u",
                                                            ucStateMachine,
                                                            stStateChangeRet.ulNewState);
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_008);
                    return;
                }

                /*ͳ����Ϣ*/
                g_stDHCPSStateMachine[ucStateMachine].StateChangeOKCount[ucMsgType][stStateChangeRet.ulNewState]++;

                /*�л�״̬*/
                pstLease->ucLeaseState = (UCHAR)stStateChangeRet.ulNewState;

                ulTimerOutLength = g_stDHCPSStateMachine[stStateChangeRet.ulNewState].ulTimerOutLength;
                enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[stStateChangeRet.ulNewState].ulTimerType;

                /*״̬ת���ɹ������ע���˶�ʱ������������ʱ��*/
                if ((0 != g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerOutLength)
                    && (DHCPS_MSG_RECIVE_INFORM != ucMsgType))
                {
                    /*���Ӷ�ʱ������*/
                    if (VOS_OK != DHCPS_TIMER_StartTimer(pstLease, enTimerType, ulTimerOutLength))
                    {
                        DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Lease Start Timer ERR ");
                    }

                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Lease Start Timer OK");
                }


                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Change OK From %u To  %u",
                                                ucStateMachine,
                                                stStateChangeRet.ulNewState);
                return;
            }

            /*״̬��û��Ǩ�ƣ����������������ܺ���û�д���
            Ҳ�п��ܼ��������Ĵ���������Ϣ�·��ص��ڲ���Ϣ��
            �ж�*/
            case DHCPS_STATE_NO_CHANGE:
            {
                g_stDHCPSStateMachine[ucStateMachine].MsgNOChangeCount[ucMsgType]++;
                ucMsgType = (UCHAR)stStateChangeRet.ulMessageType;
                if (ucMsgType >= DHCPS_MSG_MAX)
                {
                    DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, NO_CHANGE ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, NO_CHANGE ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_009);
                    return;
                }

                /*��ȡ�µĴ�����*/
                pFuncStateMachine = g_stDHCPSStateMachine[ucStateMachine].pFuncStateMachine[ucMsgType];
                if(NULL != pFuncStateMachine)
                {
                    continue;
                }

                /*ĳ״̬�յ���û��ע�����Ϣ��ֱ�ӷ���*/
                g_stDHCPSStateMachine[ucStateMachine].ErrMsgCount[ucMsgType]++;

                return;
            }

            /*״̬��Ǩ�Ʒ������󣬼�¼����
            ������ɴ�����Ϣ�룬��������*/
            case DHCPS_STATE_CHANGE_ERR:
            {
                g_stDHCPSStateMachine[ucStateMachine].MsgChangeERRCount[ucMsgType]++;

                ucMsgType = (UCHAR)stStateChangeRet.ulMessageType;

                if (ucMsgType >= DHCPS_MSG_MAX)
                {
                    DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, CHANGE_ERR ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : ucStateMachine = %u, CHANGE_ERR ucMsgType = %u",
                    ucStateMachine, ucMsgType);
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_010);
                    return;
                }

                /*��ȡ�µĴ�����������ʧ�ܴ���*/
                pFuncStateMachine = g_stDHCPSStateMachine[ucStateMachine].pFuncStateMachine[ucMsgType];
                g_stDHCPSStateMachine[ucStateMachine].MsgNOChangeCount[ucMsgType]++;
                if(NULL != pFuncStateMachine)
                {
                    continue;
                }

                /*ĳ״̬�յ���û��ע�����Ϣ��ֱ�ӷ���*/
                g_stDHCPSStateMachine[ucStateMachine].ErrMsgCount[ucMsgType]++;
                return;
            }

            /*����ָ��Ϊ�յ�ϵͳ���󣬷��ظ���Ϣ�룬
            ֱ������״̬������*/
            case DHCPS_STATE_SYSTEM_ERR:
            {
                g_stDHCPSStateMachine[ucStateMachine].MsgSysERRCount[ucMsgType]++;
                DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : SYSTEM ERROR ucStateMachine = %u",
                ucStateMachine);
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine : SYSTEM ERROR ucStateMachine = %u",
                ucStateMachine);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_011);
                return;
            }

            /*�쳣�ķ��ؽ������¼����*/
            default:
            {
                g_stDHCPSStateMachine[ucStateMachine].StateChangeUNKNOWCount[ucMsgType]++;
                DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_FSM_Run : Finite State Machine : UNKNOW result ucStateMachine = %u",
                ucStateMachine);
                DHCPS_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPS_FSM_Run : Finite State Machine: UNKNOW result ucStateMachine = %u",
                ucStateMachine);
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_012);
                return;
            }
        }
    }
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_Register
 ��������   : ע��DHCPS״̬���Ĵ�����
 �������   : ��
 �������   : ��
 �� �� ֵ      : ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��11��27��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
VOID DHCPS_FSM_Register()
{

    /*��ʼ��Ϊ0*/
    PGP_MemZero(g_stDHCPSStateMachine, (DHCPS_STATE_MAX + 1) * sizeof(DHCPS_STATE_MACHINE_NODE));
    PGP_MemZero(g_stDHCPSMsgNode, DHCPS_MSG_MAX*sizeof(DHCPS_STATE_MESSAGE_NODE));

    /*ע�����״̬��ʱ����ʱ��*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].ulTimerOutLength            = 0;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].ulTimerOutLength   = DHCPS_TIMER_LENGTH_WAITUSM;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].ulTimerOutLength      = DHCPS_TIMER_LENGTH_WAITREAUESTMSG;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].ulTimerOutLength   = 0XFFFFFFFF;

    /*ע�����״̬��ʱ����ʱ�����Ϣ,����Ϣ����״̬���Ĵ�����Ϊ��ʱ����!!!*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].ulTimerOutMsg          = 0XFFFFFFFF;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].ulTimerOutMsg = DHCPS_MSG_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].ulTimerOutMsg    = DHCPS_MSG_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].ulTimerOutMsg = DHCPS_MSG_TIMER;

    /*ע�����״̬��ʱ��������*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].ulTimerType            = E_DHCPS_INVALID_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].ulTimerType   = E_DHCPS_FSM_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].ulTimerType      = E_DHCPS_FSM_TIMER;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].ulTimerType   = E_DHCPS_LEASE_TIMER;


    /*ע��ΪNULL��ʾ����Ҫ���д���*/

    /*idel̬��״̬��������ע��*/
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]                   = DHCPS_FSM_IDLE_ReceiveDiscover;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]                    = DHCPS_FSM_IDEL_ReceiveRequest;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]                     = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]                     = DHCPS_FSM_IDLE_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]                      = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]          = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]           = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]                       = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_TIMER]                                    = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_IDEL].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;


    /*�����ַ̬��״̬��������ע��*/
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]          = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]           = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]            = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]            = DHCPS_FSM_REQUESTIP_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]             = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS] = DHCPS_FSM_REQUESTIP_AddressAllocateSuccess;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]  = DHCPS_FSM_REQUESTIP_AddressAllocateFailed;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]              = DHCPS_FSM_REQUESTIP_Deactive;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_TIMER]                           = DHCPS_FSM_REQUESTIP_USMTimerOut;
    g_stDHCPSStateMachine[DHCPS_STATE_REQUESTIP].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;

    /*offer̬��״̬��������ע��*/
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]             = DHCPS_FSM_OFFERED_ReceiveDiscover;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]              = DHCPS_FSM_OFFERED_ReceiveRequest;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]               = DHCPS_FSM_OFFERED_ReceiveDecline;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]               = DHCPS_FSM_OFFERED_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]                = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]    = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]     = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]                 = DHCPS_FSM_OFFERED_Deactive;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_TIMER]                              = DHCPS_FSM_OFFERED_ClientTimerOut;
    g_stDHCPSStateMachine[DHCPS_STATE_OFFERED].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;


    /*commit̬��״̬��������ע��*/
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]          = DHCPS_FSM_COMMITED_ReceiveDiscover;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]            = DHCPS_FSM_COMMITED_ReceiveRequest;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]             = DHCPS_FSM_COMMITED_ReceiveDecline;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]             = DHCPS_FSM_COMMITED_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]              = DHCPS_FSM_COMMITED_ReceiveInform;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]  = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]   = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]               = DHCPS_FSM_COMMITED_ReceiveDeactive;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_TIMER]                            = DHCPS_FSM_COMMITED_LeaseTimerOut;
    g_stDHCPSStateMachine[DHCPS_STATE_COMMITED].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]                     = NULL;

    /*relay̬��״̬��������ע��*/
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_DISCOVER]          = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_REQUEST]            = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_DECLINE]             = DHCPS_FSM_RELAY_ReceiveDecline;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_RELEASE]             = DHCPS_FSM_RELAY_ReceiveRelease;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RECIVE_INFORM]              = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_SUCCESS]  = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_USM_ADDRESS_FAILURE]   = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_USM_DEACTIVE]               = DHCPS_FSM_RELAY_ReceiveDeactive;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_TIMER]                     = NULL;
    g_stDHCPSStateMachine[DHCPS_STATE_RELAY].pFuncStateMachine[DHCPS_MSG_RELAY_SERVER_NAK]           = DHCPS_FSM_RELAY_ReceiveDecline;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_ReleaseResource
 ��������   : �ͷ���Լ��ص�������Դ
                            1.�ͷű����ڴ档
                            2.ͣ��ʱ����
                            3.�ͷ�IP��ַ��
                            ������״̬��
                            ������ʹ�ñ�־��
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��12��2��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG   DHCPS_FSM_ReleaseResource(DHCPS_LEASE_S *pstLease)
{
    /*����ж�*/
    DHCPS_CHECKLEASEPOINT(pstLease,DHCPS_INTERNAL_BRANCH_124)

    /*�ͷű����ڴ�*/
    if ((pstLease->pstAnalyzedPacket != NULL)
        && (pstLease->pstAnalyzedPacket != &g_stAnalyzPacket))
    {
        DHCP_Free(DHCPS_HANDLE, pstLease->pstAnalyzedPacket);
    }

    pstLease->pstAnalyzedPacket = NULL;

    /*Todo:ֹͣ���ж�ʱ��*/
    (VOID)DHCPS_TIMER_StopTimer(pstLease , E_DHCPS_FSM_TIMER);

    (VOID)DHCPS_TIMER_StopTimer(pstLease , E_DHCPS_LEASE_TIMER);

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��      : DHCPS_FSM_InitLease
 ��������   : ��ʼ����Լ���ݡ�
 �������   : ��
 �������   : ��
 �� �� ֵ      : VOS_OK    �ɹ�; VOS_ERR    ʧ��
 ���ú���   :
 ��������   :

 �޸���ʷ   :
  1.��    ��      : 2008��12��2��
    ��    ��       : dongmingzhou 42828
    �޸�����: �����ɺ���

*****************************************************************************/
ULONG   DHCPS_FSM_InitLease(DHCPS_LEASE_S *pstLease)
{

    /*����ж�*/
    DHCPS_CHECKLEASEPOINT(pstLease,DHCPS_INTERNAL_BRANCH_125)

    if(1 == pstLease->ucUserNumFlag)
    {
        if (g_ulDHCPSIpnum >0)
        {
            g_ulDHCPSIpnum--;
        }
    }

    pstLease->ucUsed                = DHCPS_LEASE_NOTUSED;
    pstLease->ucLeaseState        = DHCPS_STATE_IDEL;
    pstLease->ucUserNumFlag = 0;
    pstLease->ucRole = DHCPS_GET_ROLE_INVALID;
    pstLease->ucPmipFlag              = 0;
    pstLease->ulAddr                  = 0;
    pstLease->ulIndex                = 0;
    pstLease->pstAnalyzedPacket = NULL;
    pstLease->ucFirstRequestMsgFlag = 0;

    return VOS_OK;
}


ULONG DHCPS_FSM_LeaseStateIsValid(ULONG ulIndex)
{
    if ( (0 == ulIndex)
        || (ulIndex > SDB_MAX_CONTEXT_NUM) )   /* Modified by jixiaoming at 2011-05-10 for pclint */
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_FSM_LeaseStateIsValid : ulIndex = %u is error!", ulIndex);
        return VOS_FALSE;
    }

    if(DHCPS_STATE_MAX <= g_pstDhcpSLease[ulIndex].ucLeaseState)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_BackupDeleteProc : slave the ucLeaseState = %u is error!", g_pstDhcpSLease[ulIndex].ucLeaseState);
        return VOS_FALSE;
    }

    return VOS_TRUE;
}
