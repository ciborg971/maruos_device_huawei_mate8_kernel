
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

extern VOID DHCPS_ProcPfMsg(PMBUF_S *pstMsgBuf);

#define __INIT__



ULONG DHCPS_CreateQueue()
{
    ULONG ulResult = VOS_OK;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = DHCPS_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulDhcpServerTaskId;

    /* ����USM��Ϣ���� */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_USM;
    stQueInfo.ulQueLen      = DHCPS_QUEUE_LENGTH;
    stQueInfo.ulEvent       = DHCPS_USM_EV;
    VOS_sprintf(stQueInfo.szQueName, "DHCPS_USM");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDHCPSUSMQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /* ��ʱ������ */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_TIMER;
    stQueInfo.ulQueLen      = 1024;
    stQueInfo.ulEvent       = VOS_TIMER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DST");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpsTimerQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /* �����ڲ����� */
    stQueInfo.ulQueType     = MSG_QUETYPE_VOSQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_SELF;
    stQueInfo.ulQueLen      = 256;
    stQueInfo.ulEvent       = DHCPS_INNER_EVENT;
    VOS_sprintf(stQueInfo.szQueName, "DHCI");

    ulResult = PTM_CreateQueue(&stQueInfo, &g_ulDhcpsInnerQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    /* ����������Ϣ */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPS_MSG_TYPE_PF;
    stQueInfo.ulQueLen      = DHCPS_DFT_QUEUE_LENGTH;
    stQueInfo.ulEvent       = DHCPS_PF_EV;
    VOS_sprintf(stQueInfo.szQueName, "S%luDHCPv4S", DHCPS_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pDHCPSRcvDhcpMsgQueId);
    if (VOS_OK != ulResult)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


ULONG DHCPS_Init()
{
    ULONG ulReturn = 0;

    /* ��ʼ��������� */
    g_stDhcpv4sComInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DSV4);
    g_stDhcpv4sComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();
    g_stDhcpv4sComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpv4sComInfo.ullSelfCsi);
    g_stDhcpv4sComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpv4sComInfo.ullSelfCsi);
    g_stDhcpv4sComInfo.ulHandle     = MID_DHCPS;

    ulDhcpv4sTaskStep = 100;

    /* ��һ�׶γ�ʼ�� */
    ulReturn = DHCPS_CommInit1();
    if (VOS_OK != ulReturn)
    {
        return VOS_ERR;
    }

    ulDhcpv4sTaskStep = 200;

#ifndef __WIN32_PLATFORM__
    ulReturn = CLAP_TaskInit(g_stDhcpv4sComInfo.ullSelfCsi, g_stDhcpv4sComInfo.ulHandle);
    if (VOS_OK != ulReturn)
    {
        return ulReturn;
    }
#endif

    ulDhcpv4sTaskStep = 2000;

    return VOS_OK;
}

#define __TASK__
/*==========================================================
 *  ��������: DHCPS_RecvMsgFromUSM
 *  �������:
 *  ��    ��:
 *  ��������: ����USM��Ϣ������

 *  �������:
 *  �������:
 *  ��������: ��
 *  ����˵��: ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
VOID DHCPS_RecvMsgFromUSM()
{
    ULONG aulMsgBuf[4];            /* ��Ϣ����Ԫ�� */
    ULONG ulFlowCounter = 0;
    UCHAR *pucMsg = NULL;

    for (;;)
    {
        aulMsgBuf[1] = 0;

        if (VOS_OK == VOS_Que_Read( g_ulDHCPSUSMQueId,
                                    aulMsgBuf,
                                    VOS_NO_WAIT,
                                    0 ))
        {
            if (NULL != aulMsgBuf[1])
            {
                pucMsg = (UCHAR*)aulMsgBuf[1];
                g_ulDhcpStatisc[DHCPS_RECEIVE_USM]++;

                DHCPS_FSM_PreMsgFromUSM(pucMsg);
                DHCP_RTDistributeFreeMsg(pucMsg);
            }
        }
        else
        {
            break;
        }

        ulFlowCounter++;
        if (ulFlowCounter >= 50)
        {
            /* ����δ�������Ϣ,д�¼�λ,�´μ������� */
            (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, DHCPS_USM_EV);
            break;
        }
    }

}




VOS_VOID DHCPS_InnerMsgProc()
{
    ULONG ulFlowControl = 0;
    ULONG ulMsg[4] = {0};
    UCHAR *pucMsg = NULL;

    while (VOS_OK == VOS_Que_Read(g_ulDhcpsInnerQueId, ulMsg, VOS_NO_WAIT, 0))
    {
        pucMsg = (UCHAR*)ulMsg[1];
        if ( NULL == pucMsg )
        {
            VOS_Assert(0);
            continue;
        }

        DHCPS_ProcSelfMsg(pucMsg);

        DHCP_RTDistributeFreeMsg(pucMsg);
        ulFlowControl++;
        if (ulFlowControl >= 2)
        {
            (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, DHCPS_INNER_EVENT);
            break;
        }
    }

    return;
}


/*==========================================================
 *  ��������: DHCPS_RecvMsgHandle
 *  �������:
 *  ��    ��:
 *  ��������: ������Ϣ������

 *  �������:
 *  �������:
 *  ��������: ��
 *  ����˵��: ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
VOS_VOID  DHCPS_RecvMsgHandle(VOID)
{
    PMBUF_S * pstMsgBuf = VOS_NULL_PTR;
    ULONG   ulMsgLen = 0;
    ULONG   ulLoopi = 0;

    for(ulLoopi = 0; ulLoopi < DHCPS_FLOWCONTROL_MAX; ulLoopi++)
    {
        ulMsgLen = 0;

        /*ע��: ���ǹ�����еĶ�ȡ��ʽ*/
        if( VOS_OK != VOS_MCReadQue(g_pDHCPSRcvDhcpMsgQueId,
                                    &pstMsgBuf,
                                    &ulMsgLen,
                                    VOS_MCQUEUE_NO_WAIT,
                                    0))
        {
            /* ��ȡʧ��ֱ�ӷ��� */
            return;
        }

        /* �ж���Ϣ�Ϸ��� */
        if( VOS_NULL_PTR == pstMsgBuf)
        {
            /* ��¼�쳣��Ϣ */
            DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_RecvMsgHandle: Null Msg!\n");
            continue;
        }

        g_ulDhcpStatisc[DHCPS_RECEIVE_DPE]++;

        DHCPS_ProcPfMsg(pstMsgBuf);


        (VOID)PMBUF_Destroy(pstMsgBuf);
    }

    /* �����л�����Ϣ, дʱ��λ,����������� */
    (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, DHCPS_PF_EV);

    return;
}
VOID  DHCPS_TimerOut(VOID)
{
    ULONG aulMsgBuf[4];            /* ��Ϣ����Ԫ�� */
    ULONG ulFlowCounter = 0;

    /* ѭ�����ڲ���Ϣ��ʱ���� */
    for (;;)
    {
        /* ��ʼ��  */
        aulMsgBuf[2] = 0;
        aulMsgBuf[3] = 0;

        if (VOS_OK == VOS_Que_Read( g_ulDhcpsTimerQueId,
                                    aulMsgBuf,
                                    VOS_NO_WAIT,
                                    0 ))
        {
            if (NULL != aulMsgBuf[2])
            {
                /* ״̬����ʱ������ */
                /*lint -e{746}*/
                ((VOID(*) ())(aulMsgBuf[2]))((VOID *)(aulMsgBuf[3]));
            }
        }
        else
        {
            break;
        }

        ulFlowCounter++;
        if (ulFlowCounter >= 50)
        {
            /* ��δ������,дʱ��λ,�´μ������� */
            (VOID)VOS_Ev_Write(g_ulDhcpServerTaskId, VOS_TIMER_EVENT);
            break;
        }
    }

    return;
}

/*==========================================================
 *  ��������: DHCPS_MainEntry
 *  �������:
 *  ��    ��:
 *  ��������: ��������

 *  �������:
 *  �������:
 *  ��������: ��
 *  ����˵��: ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
VOID DHCPS_MainEntry()
{
    ULONG ulRet = 0;
    ULONG ulEvent = 0;

    ulDhcpv4sTaskStep = 2100;

    /* �������� */
    ulRet = DHCPS_CreateQueue();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpv4sTaskStep = 3000;

    /*�ȴ�PGP ready*/
    PGP_Ready();

    ulDhcpv4sTaskStep = 4000;

    ulRet = DHCPS_CommInit3();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpv4sTaskStep = 6200;

    ulRet = DHCPS_StartWorkProc();
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulDhcpv4sTaskStep = 6400;

#ifndef __WIN32_PLATFORM__
    ulRet = CLAP_TaskConfirm(g_ulDhcpServerTaskId);
    if (VOS_OK != ulRet)
    {
        return;
    }
#endif

    ulDhcpv4sTaskStep = 6600;

    (VOID)PGP_SetTaskRunConfirm();

    ulDhcpv4sTaskStep = 7000;

    for(;;)
    {
        /* ��ת������Ϣ�Ķ��б�������,ת��Ŀǰû��д�¼�λ */
        DHCPS_RecvMsgHandle();

        /*���¼�λ*/
        if (VOS_OK == VOS_Ev_Read( VOS_TIMER_EVENT
                                 | DHCPS_INNER_EVENT
                                 | DHCPS_PF_EV
                                 | DHCPS_USM_EV,
                                 &ulEvent, VOS_EV_ANY|VOS_WAIT, 100 ) )
        {
            /*����ʱ���¼�*/
            if (VOS_TIMER_EVENT & ulEvent)
            {
                DHCPS_TimerOut();
            }

            /* ���¼�λ��ʽ�޸�ΪWAIT,��ֹ������������,�˴��������� */
            if (DHCPS_PF_EV & ulEvent)
            {
                /* ��ת�������� */
                DHCPS_RecvMsgHandle();
            }

            /*����USM���͵���Ϣ*/
            if (DHCPS_USM_EV & ulEvent)
            {
                DHCPS_RecvMsgFromUSM();
            }

            /* �����ڲ���Ϣ */
            if (DHCPS_INNER_EVENT & ulEvent)
            {
                DHCPS_InnerMsgProc();
            }
        }

#ifndef __WIN32_PLATFORM__
        CLAP_TaskProcess();
#endif

        VOS_T_Delay(1);
        ulDhcpv4sTaskStep = 8888;
    }
}


