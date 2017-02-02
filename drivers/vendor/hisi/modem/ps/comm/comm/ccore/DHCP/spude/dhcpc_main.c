
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"
/* deleted by w00316385 start */
#if 0
#include "dhcpm_interface.h"
#endif
/* deleted by w00316385 end */

extern ULONG ulDhcpcTaskStep;

extern VOS_UINT32 LAP2_McQue_IsEmpty( VOS_VOID *pvMCQueId );

#define __INIT__


ULONG DHCPC_CreateQueue()
{
    ULONG ulResult = VOS_OK;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = DHCPC_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulDhcpcTaskId;

    /* ��ʱ������ */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_TIMER;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = VOS_TIMER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DTMR");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpcTimerQid);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);
        return VOS_ERR;
    }

    /* �����ڲ����� */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_SELF;
    stQueInfo.ulQueLen      = 256;
    stQueInfo.ulEvent       = DHCPC_INNER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DHCI");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpcInnerQid);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);
        return VOS_ERR;
    }

    /*����LAP��������Ϣ*/
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_LAP;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = DHCPC_LAP_MSG_EV;
    VOS_sprintf(stQueInfo.szQueName, "SC%02u_DHCPC_QUE", DHCPC_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pulDHCP_LAP2_REQQueID);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);

        return VOS_ERR;
    }

    /*�ҽӸ�lap������Ϣ�Ķ���*/
    ulResult = DHCPC_AttachLapQueue();
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue call DHCPC_AttachLapQueue, return = %x",
                            ulResult);
        return VOS_ERR;
    }

    /*����SD��������Server��Ӧ��Ϣ*/
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_SERVER;
    stQueInfo.ulQueLen      = 512;
    stQueInfo.ulEvent       = DHCPC_V4_SVR_EV;
    VOS_sprintf(stQueInfo.szQueName, "DHCPSC%02u", DHCPC_SELF_CMPIDX );

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pulSDDhcpMCQueID);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);

        return VOS_ERR;
    }

    /* BEGIN: Modified by jixiaoming for dhcpv6c at 2012-7-10 */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPC_MSG_TYPE_DHCPV6_SERVER;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = DHCPC_V6_SVR_EV;
    VOS_sprintf(stQueInfo.szQueName, "DHCPV6SC%02u", DHCPC_SELF_CMPIDX );

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pulSDDhcpv6cMcQueId);
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, return = %x",
                            stQueInfo.szQueName, ulResult);

        return VOS_ERR;
    }
    /* END: Modified by jixiaoming for dhcpv6c at 2012-7-10 */

/* deleted by w00316385 start */
#if 0
    /*ע��FCMͨ��*/
    ulResult = FCM_CreateFwdChannel(E_COMP_TYPE_DHCPC,
                                    DHCPC_MSG_TYPE_FCM,
                                    DHCPC_SELF_CMPIDX);
#endif
/* deleted by w00316385 end */
    if (VOS_OK != ulResult)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "FCM_CreateFwdChannel fail, return = %x", ulResult);

        return VOS_ERR;
    }

    return VOS_OK;
}



VOS_UINT32 DHCPC_AttachLapQueue()
{
    MC_QUE_ID pstQueId = NULL;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };
    ULONG ulRet = 0;

    stQueInfo.ulQueType = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType = E_AM_USM_QUE_SC_LAP_MSG;
    stQueInfo.ulQueLen = 1024;
    stQueInfo.ulEvent = M_AM_USM_EV_LAP2_MSG;

    VOS_StrNCpy(stQueInfo.szQueName, "LAP2_DHCPC_QUE", M_PTM_QUE_NAME_LEN);
    ulRet = PTM_CreateMcQueue(&stQueInfo, (ULONG *)&pstQueId);

    return ulRet;
}




ULONG DHCPC_TaskInit(VOID)
{
    ULONG ulReturn = 0;

    ulDhcpcTaskStep = 100;

    /* ��ʼ��������� */
    g_stDhcpcComInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DHCPC);
    g_stDhcpcComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();
    g_stDhcpcComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpcComInfo.ullSelfCsi);
    g_stDhcpcComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpcComInfo.ullSelfCsi);
    g_stDhcpcComInfo.ulHandle     = MID_DHCPC;

    /* ��һ�׶γ�ʼ�� */
    ulReturn = DHCPC_CommInit1();
    if (VOS_OK != ulReturn)
    {
        return VOS_ERR;
    }

    ulDhcpcTaskStep = 1000;

    return VOS_OK;
}

#define __TASK__

/*****************************************************************************
 �� �� ��  : DHCPC_TimerMsgQuePro
 ��������  :dhcpcģ�鴦��ʱ����Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :
 �޸���ʷ       :
  1.��      ��   : 2011��01��05��
    ��      ��   : jiahuidong00142544
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID DHCPC_TimerMsgQuePro()
{
    ULONG ulFlowControl = 0;            /* ���岢��ʼ�����ر���   */
    ULONG ulMsgBuf[4] = {0};              /* ������Ϣ������         */

    while ( VOS_OK ==( VOS_Que_Read( g_ulDhcpcTimerQid,
                                     ulMsgBuf,VOS_NO_WAIT,0 ) ) )
    {
        /*��ʱ����ʱ����*/
        if ( ulMsgBuf[2] == NULL )
        {
            continue;
        }
        /*lint -e{746}*/
        ( ( VOID( * )() )( ulMsgBuf[2] ) )( ( VOID * )( ulMsgBuf[3] ) );

        /* ����*/
        ulFlowControl++;
        if ( DHCPC_MAXMSGS_PEREVENT < ulFlowControl )
        {
            ( VOID )VOS_Ev_Write( g_ulDhcpcTaskId, VOS_TIMER_EVENT );
            break;
        }
    }

    return;
}
VOID DHCPC_InnerMsgQuePro()
{
    ULONG ulFlowControl = 0;            /* ���岢��ʼ�����ر���   */
    ULONG aulMsgBuf[4] = {0};              /* ������Ϣ������         */
    UCHAR *pucMsg = NULL;

    while ( VOS_OK == ( VOS_Que_Read( g_ulDhcpcInnerQid,
                                     aulMsgBuf,VOS_NO_WAIT,0 ) ) )
    {
        pucMsg = (UCHAR *)aulMsgBuf[1];
        if ( NULL == pucMsg )
        {
            continue;
        }

        DHCPC_SelfMsgProc(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        /* ����*/
        ulFlowControl++;
        if ( 2 < ulFlowControl )
        {
            ( VOID )VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_INNER_EVENT);
            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_LAPMsgQuePro
 ��������  :dhcpcģ�鴦��lap��Ϣ�ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :
 �޸���ʷ       :
  1.��      ��   : 2011��01��05��
    ��      ��   : jiahuidong00142544
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID DHCPC_LAPMsgQuePro()
{
    ULONG ulFlowControl = 0;
    UCHAR *pucMsg = NULL;
    ULONG ulMsgCode = 0;

    if (VOS_OK != LAP2_McQue_IsEmpty(g_pulDHCP_LAP2_REQQueID))
    {
        return;
    }

    while ( VOS_OK == ( VOS_MCReadQue( g_pulDHCP_LAP2_REQQueID,
                                       &pucMsg, &ulMsgCode, VOS_MCQUEUE_NO_WAIT, 0 ) ) )
    {
        /*ע���ͷ���Ϣ��*/
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_000);

        if ( NULL == pucMsg )
        {
            VOS_DBGASSERT( 0 );
            continue;
        }

        ( VOID )DHCPC_ReceiveLAP2Msg (pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        /* ����*/
        ulFlowControl++;
        if ( DHCPC_MAXMSGS_PEREVENT < ulFlowControl )
        {
            (VOID)VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_LAP_MSG_EV);
            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_SDMsgQuePro
 ��������  :dhcpcģ�鴦��dhcp server���ص���Ϣ��
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :
 �޸���ʷ       :
  1.��      ��   : 2011��01��05��
    ��      ��   : jiahuidong00142544
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID DHCPC_SDMsgQuePro()
{
    ULONG ulFlowControl = 0;
    ULONG ulMsfCode = 0;
    UCHAR *pucMsg = NULL;

    if (VOS_OK != LAP2_McQue_IsEmpty(g_pulSDDhcpMCQueID))
    {
        return;
    }

    /* �˴���ȡ��SD֮��Ĺ������ */
    while (VOS_OK == (VOS_MCReadQue (g_pulSDDhcpMCQueID, &pucMsg, &ulMsfCode, VOS_MCQUEUE_NO_WAIT,0)))
    {
        /* ��SD�յ�DHCP���� */
        DHCP_InternalBranchCounter(DCHP_INTERNAL_BRANCH_002);
        if (NULL == pucMsg)
        {
            VOS_DBGASSERT(0);
            continue;
        }

        DHCPC_ReceiveServerMsg(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        /* ����*/
        ulFlowControl++;
        if (DHCPC_MAXMSGS_PEREVENT < ulFlowControl)
        {
            (VOID)VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_V4_SVR_EV);
            break;
        }
    }

    return;
}
VOID DHCPC_SDDhcpv6MsgQueProc()
{
    UCHAR *pucMsg = NULL;
    ULONG ulMsfCode = 0;
    ULONG ulCounter = 0;

    if (VOS_OK != LAP2_McQue_IsEmpty(g_pulSDDhcpv6cMcQueId))
    {
        return;
    }

    while (VOS_OK == (VOS_MCReadQue (g_pulSDDhcpv6cMcQueId, &pucMsg, &ulMsfCode, VOS_MCQUEUE_NO_WAIT,0)))
    {
        if (NULL == pucMsg)
        {
            VOS_Assert(0);
            continue;
        }

        DHCPC_DebugPrint(PTM_LOG_DEBUG, "\r\n DHCPC_SDDhcpv6MsgQueProc get dhcpv6 msg!");

        DHCPV6C_ProcSDMsg(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);

        ulCounter++;
        if (ulCounter > DHCPC_MAXMSGS_PEREVENT)
        {
            (VOID)VOS_Ev_Write( g_ulDhcpcTaskId, DHCPC_V6_SVR_EV);
            break;
        }
    }

    return;
}

/*****************************************************************************
 �� �� ��  : DHCPC_ProFcmMsg
 ��������  :dhcpcģ�鴦��fcmͨ����Ϣ�ĺ���
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :
 �޸���ʷ       :
  1.��      ��   : 2011��01��05��
    ��      ��   : jiahuidong00142544
    �޸�����   : �����ɺ���
*****************************************************************************/
VOID DHCPC_ProFcmMsg()
{
    PMBUF_S * pMBuf = NULL;
    ULONG  ulTemp = 0;

    while (VOS_OK == FCM_ReadMCQue(E_COMP_TYPE_DHCPC, DHCPC_MSG_TYPE_FCM, DHCPC_SELF_CMPIDX, &pMBuf))
    {
        /*��ȡ���ĳ��Ⱥ͵�ַ*/
        if (NULL == pMBuf)
        {
            return;
        }

        DHCPC_ReceiveLap2MbufMsg(pMBuf);

        (VOID)PMBUF_Destroy(pMBuf);

        /* ÿ�δ���256����Ϣ */
        ulTemp++;
        if (ulTemp >= DHCPC_MAXMSGS_PEREVENT)
        {
            break;
        }
    }
    return;
}


VOID DHCPC_TaskEntry()
{
    ULONG ulRet = 0;
    ULONG ulEvent = 0;

    ulDhcpcTaskStep = 2000;

    /* �������� */
    ulRet = DHCPC_CreateQueue();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpcTaskStep = 2100;

    /*�ȴ�PGP ready*/
    PGP_Ready();

    ulDhcpcTaskStep = 2200;

    ulRet = DHCPC_CommInit3();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpcTaskStep = 2400;

    ulRet = DHCPC_StartWorkProc();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpcTaskStep = 2600;

    (VOID)PGP_SetTaskRunConfirm();

    ulDhcpcTaskStep = 2800;

    for (;;)
    {
        if (CRM_BOARD_TYPE_SPUE == g_ulDhcpcSpuType)
        {
            /*��ȡ����ͨ������Ϣ*/
            DHCPC_ProFcmMsg();
        }

        if (VOS_OK == VOS_Ev_Read(DHCPC_INNER_EVENT
                                | VOS_TIMER_EVENT
                                | DHCPC_LAP_MSG_EV
                                | DHCPC_V4_SVR_EV
                                | DHCPC_V6_SVR_EV,
                                 &ulEvent, (VOS_EV_ANY | VOS_WAIT), 50))
        {
            if (ulEvent & DHCPC_LAP_MSG_EV)
            {
                /*LAP���͵���Ϣ����*/
                DHCPC_LAPMsgQuePro();
            }

            if (ulEvent & DHCPC_V4_SVR_EV)
            {
                /*DHCPV4 Server���ص���Ϣ����*/
                DHCPC_SDMsgQuePro();
            }

            if (ulEvent & DHCPC_V6_SVR_EV)
            {
               /*DHCPV6 Server���ص���Ϣ����*/
               DHCPC_SDDhcpv6MsgQueProc();
            }

            if (ulEvent & VOS_TIMER_EVENT)
            {
                /*��ʱ����Ϣ����*/
                DHCPC_TimerMsgQuePro();
            }

            if (ulEvent & DHCPC_INNER_EVENT)
            {
                /*��ʱ����Ϣ����*/
                DHCPC_InnerMsgQuePro();
            }
        }

        /*�����ͷ�CPU*/
        VOS_T_Delay(10);

        ulDhcpcTaskStep = 8888;
    }

    //return;
}


