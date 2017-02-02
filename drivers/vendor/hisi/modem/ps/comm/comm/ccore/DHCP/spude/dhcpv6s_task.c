/******************************************************************************

                  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

 ******************************************************************************
  �� �� ��   : dhcpv6_proc.c
  �� �� ��   : ����
  ��    ��   : zhoujunping
  ��������   : 2008��12��12��
  ����޸�   :
  ��������   : DHCPV6
  �����б�   :
  �޸���ʷ   :
  1.��    ��   : 2008��12��12��
    ��    ��   : zhoujunping
    �޸�����   : ����

******************************************************************************/
#include "dhcp_inc.h"
/* add by w00316385 start */
#include "dhcpc_def.h"
#include "dhcpv6_def.h"
/* add by w00316385 end */
#include "dhcpv6_proc.h"
#include "dhcpv6s_comp.h"
#include "dhcpv6s_dbg.h"

VOS_VOID *g_pDHCPSv6RcvDhcpMsgQueId = VOS_NULL;
ULONG g_ulDhcpV6ServerTaskId = 0;
ULONG g_ulDhcpV6TaskStep = 0;


#define __INIT__


ULONG DHCPV6S_CreateQueue()
{
    ULONG ulResult = VOS_OK;
    PTM_QUEUE_INFO_S stQueInfo = { 0 };

    stQueInfo.ullSelfCsi    = DHCPV6S_SELF_CSI;
    stQueInfo.ulTaskId      = g_ulDhcpV6ServerTaskId;

    /* ����������Ϣ */
    stQueInfo.ulQueType     = MSG_QUETYPE_MCQ;
    stQueInfo.ulMsgType     = DHCPV6S_MSG_TYPE_PF;
    stQueInfo.ulQueLen      = DHCPV6_DFT_QUEUE_LENGTH;
    stQueInfo.ulEvent       = DHCPV6S_DHCP_MSG_EV;
    VOS_sprintf(stQueInfo.szQueName, "S%luDHCPv6SR", DHCPV6S_SELF_CMPIDX);

    ulResult = PTM_CreateQueue(&stQueInfo, (ULONG *)&g_pDHCPSv6RcvDhcpMsgQueId);
    if (VOS_OK != ulResult)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "PTM_CreateQueue %s fail, ulReturn = %x",
                           stQueInfo.szQueName, ulResult);
        return VOS_ERR;
    }

    return VOS_OK;
}
ULONG DHCPV6S_Init()
{
    ULONG ulReturn = 0;

    g_ulDhcpV6TaskStep = 100;

    /* ��ʼ��������� */
    g_stDhcpv6sComInfo.ullSelfCsi   = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DSV6);
    g_stDhcpv6sComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();
    g_stDhcpv6sComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpv6sComInfo.ullSelfCsi);
    g_stDhcpv6sComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpv6sComInfo.ullSelfCsi);
    g_stDhcpv6sComInfo.ulHandle     = MID_DHCPSV6;

    g_ulDhcpV6TaskStep = 300;

    /* ��һ�׶γ�ʼ�� */
    ulReturn = DHCPV6S_CommInit1();
    if (VOS_OK != ulReturn)
    {
        return VOS_ERR;
    }

    g_ulDhcpV6TaskStep = 1000;

    return VOS_OK;
}

#define __TASK__
/*****************************************************************************
 �� �� ��  : DHCPV6S_RecvMsgHandle
 ��������  :��DHCPV6�Ķ����ж�ȡ���ģ�������
 �������  : ��
 �������  : ��
 �� �� ֵ  : VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2008��12��12��
    ��    ��   : zhoujunping
    �޸�����   : �����ɺ���

*****************************************************************************/
VOS_VOID  DHCPV6S_RecvMsgHandle(VOID)
{
    PMBUF_S  *pstMsgBuf = NULL;
    ULONG ulMsgLen = 0;
    ULONG ulLoop = 0;

    for(ulLoop = 0; ulLoop < DHCPV6_FLOWCONTROL_MAX; ulLoop++)
    {
        if( VOS_OK != VOS_MCReadQue(g_pDHCPSv6RcvDhcpMsgQueId,
                                    &pstMsgBuf,
                                    &ulMsgLen,
                                    VOS_MCQUEUE_NO_WAIT,
                                    0))
        {
            return;
        }

        if(NULL == pstMsgBuf)
        {
            DHCPV6S_DebugPrint(PTM_LOG_INFO, " Null Msg!");
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_NULL_BUF);
            continue;
        }

        /* �յ���Ϣ����*/
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_MS_MSG);

        /* ��Ϣ���� */
        if (VOS_OK != DHCPV6_MsgProc(pstMsgBuf))
        {
            DHCPV6S_DBGCNT_ADD(E_DHCPV6S_PROC_ERR);
        }

        (VOID)PMBUF_Destroy(pstMsgBuf);
    }

    /* ��Ϣ��δ������,дʱ��λ,�´μ������� */
    (VOID)VOS_Ev_Write( g_ulDhcpV6ServerTaskId, DHCPV6S_DHCP_MSG_EV);

    return;
}
VOID DHCPV6S_TaskEntry()
{
    ULONG ulRet = 0;
    ULONG ulEvent = 0;

    g_ulDhcpV6TaskStep = 2000;

    /* �������� */
    ulRet = DHCPV6S_CreateQueue();
    if (VOS_OK != ulRet)
    {
        return;
    }

    g_ulDhcpV6TaskStep = 2100;

    /*�ȴ�PGP ready*/
    PGP_Ready();

    g_ulDhcpV6TaskStep = 2200;

    ulRet = DHCPV6S_CommInit3();
    if (VOS_OK != ulRet)
    {
        return;
    }

    g_ulDhcpV6TaskStep = 2500;

    /* DHCPV6Sû�ж�ʱ�� */

    /* Added by jixiaoming for  CR20120830015 at 2013-1-17 */
    (VOID)DHCPV6S_RegLogCnt();

    (VOID)PGP_SetTaskRunConfirm();

    g_ulDhcpV6TaskStep = 2600;

    for (;;)
    {
        /* ��ת������Ϣ�Ķ��б�������,ת��Ŀǰû��д�¼�λ */
        DHCPV6S_RecvMsgHandle();

        if (VOS_OK == VOS_Ev_Read(DHCPV6S_DHCP_MSG_EV, &ulEvent, VOS_EV_ANY|VOS_WAIT, 100))
        {
            /* ���¼�λ��ʽΪwait,��ֹ������������,�������� */
            if (DHCPV6S_DHCP_MSG_EV & ulEvent)
            {
                DHCPV6S_RecvMsgHandle();
            }
        }

        VOS_T_Delay(10);
        g_ulDhcpV6TaskStep = 8888;
    }

    //return;
}

