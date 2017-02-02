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
/* add by w00316385 end */
#include "dhcpv6_proc.h"
#include "dhcpv6s_comp.h"
#include "dhcpv6s_dbg.h"

/*****************************************************************************
     Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV6S_COMP_C
/*lint +e767*/

PTM_COMPONENT_INFO_S g_stDhcpv6sComInfo = { 0 };

/*����ͳ��PGW���յ�UEʼ����DHCPV6 Inform Request��Ϣ����*/
VOS_SIZE_T g_UEtoPGW_ulDHCPV6InformRequestNumAddr =  VOS_NULL_PTR ;

/*����ͳ��PGW���͸�UE��DHCPV6 Ack��Ϣ����*/
VOS_SIZE_T g_PGWtoUE_ulDHCPV6AckNumAddr =  VOS_NULL_PTR ;

/*����ͳ��SGW���յ�UEʼ����DHCPV6 Inform Request��Ϣ����*/
VOS_SIZE_T g_UEtoSGW_ulDHCPV6InformRequestNumAddr =  VOS_NULL_PTR ;

/*����ͳ��SGW���͸�UE��DHCPV6 Ack��Ϣ����*/
VOS_SIZE_T g_SGWtoUE_ulDHCPV6AckNumAddr =  VOS_NULL_PTR ;

ULONG ulDhcpv6sPerfInitFinish = VOS_FALSE;

#define __DHCPV6S_COMP_INIT__

ULONG DHCPV6S_OmInitial()
{
    if ((g_UEtoPGW_ulDHCPV6InformRequestNumAddr = PerfGetFamPerfCounterAddress(
         PERF_TYPE_PGW_S5,
         PERF_TYPE_PGW_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
         VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV6AckNumAddr = PerfGetFamPerfCounterAddress(
         PERF_TYPE_PGW_S5,
         PERF_TYPE_PGW_SEND_DHCPV6_ACK_TO_UE_PKTS,
         VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV6_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    /*����ͳ�� for sgw*/
    if ((g_UEtoSGW_ulDHCPV6InformRequestNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV6_INFO_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV6AckNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV6_ACK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPV6S_DebugPrint(PTM_LOG_INFO, "IPV6_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV6_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    ulDhcpv6sPerfInitFinish = VOS_TRUE;

    return VOS_OK;
}
ULONG DHCPV6S_LocalMemInit()
{
    /* ��������Ϣ���� */
    g_pucDhcpv6sRevBuff = (UCHAR*)DHCP_Malloc(DHCPV6S_HANDLE, sizeof(UCHAR) * DHCPV6S_REV_MSG_MAXLEN);
    if (NULL == g_pucDhcpv6sRevBuff)
    {
        return VOS_ERR;
    }
    DHCP_MemZero(g_pucDhcpv6sRevBuff, sizeof(UCHAR) * DHCPV6S_REV_MSG_MAXLEN);


    /* ���뷢��Ϣ���� */
    g_pucDhcpv6sSendBuff = (UCHAR*)DHCP_Malloc(DHCPV6S_HANDLE, sizeof(UCHAR) * DHCPV6S_SEND_MSG_MAXLEN);
    if (NULL == g_pucDhcpv6sSendBuff)
    {
        return VOS_ERR;
    }
    DHCP_MemZero(g_pucDhcpv6sSendBuff, sizeof(UCHAR) * DHCPV6S_SEND_MSG_MAXLEN);

    return VOS_OK;
}

#ifdef __LINUX_PLATFORM__


ULONG DHCPV6S_GetSelfCompInfo(DMS_COMMID_T myCSI )
{
    g_stDhcpv6sComInfo.ullSelfCsi = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DSV6);
    g_stDhcpv6sComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();
    g_stDhcpv6sComInfo.ulHandle = PGP_CompGetDopraHandle();

    g_stDhcpv6sComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpv6sComInfo.ullSelfCsi);
    g_stDhcpv6sComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpv6sComInfo.ullSelfCsi);

    return VOS_OK;
}


VOID DHCPV6S_ScheduleInit( DMS_COMMID_T ullCpi )
{
    ULONG i = 0;
    ULONG ulReturn = VOS_OK;
    COMP_MSGSTM_ATTR_S astMsgQueAttr[DHCPV6S_MSG_TYPE_BULT] = {0};
    ULONG aulScheduleTlb[DHCPV6S_MSG_TYPE_BULT] = { 0 };
    ULONG ulNum = 0;

    /* ��ʼ��ÿ�����е�������� */
    aulScheduleTlb[DHCPV6S_MSG_TYPE_PF]        = DHCPV6_FLOWCONTROL_MAX;

    for (i = M_PS_MSG_TYPE_BASE; i < DHCPV6S_MSG_TYPE_BULT; i++)
    {
        if ( 0 == aulScheduleTlb[i] )
        {
            continue;
        }

        astMsgQueAttr[ulNum].uiMsgNum = aulScheduleTlb[i];
        astMsgQueAttr[ulNum].uiStreamId = i;
        astMsgQueAttr[ulNum].uiFcmQue = 0;
        astMsgQueAttr[ulNum].uiMaxAppMsgNum = DHCPV6S_DEFAULT_MAX_APP_MSG_NUM;
        ulNum++;
    }

    ulReturn = (ULONG)PGP_ScmCompMsgStmAttribSet(ullCpi, ulNum, astMsgQueAttr);
    if (VOS_OK != ulReturn)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "\r\n PGP_ScmCompMsgStmAttribSet fail, Ret = %u", ulReturn);
    }

    return;
}

#endif
ULONG DHCPV6S_CommInit1(  )
{
    ULONG ulRet = VOS_OK;

    DBG_LogRecordReg(M_PTM_SYSTEM_NAME, "DHCP", "DSV6", &g_ulDhcpv6sLogRecordRegId);

    DHCPV6S_InitCounter();

    DHCPV6S_DebugCmdInit(DHCPV6S_SELF_CSI);

    /* ����˽���ڴ� */
    ulRet = DHCPV6S_LocalMemInit();
    if (VOS_OK != ulRet)
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "DHCPS_LocalMemInit fail");
        return ulRet;
    }

    PTM_Dbg_RegMemoryPrint(DHCPV6S_SELF_CSI);

    return VOS_OK;
}
ULONG DHCPV6S_CommInit2(  )
{
    return VOS_OK;
}


ULONG DHCPV6S_CommInit3( )
{
    ULONG ulReturn = 0;

    ulReturn = DHCPV6S_OmInitial();
    if ( VOS_OK != ulReturn )
    {
        DHCPV6S_DebugPrint(PTM_LOG_ERR, "DHCPV6S_OmInitial fail, ulReturn = %x", ulReturn);
    }

    return VOS_OK;
}

#define __DHCPV6S_COMP_MSG_PROC___________


VOID DHCPV6S_ProcPfMsg(VOID* pMsg)
{
    PMBUF_S *pstMBuf = NULL;

    if ( NULL == pMsg )
    {
        VOS_Assert(0);
        return;
    }

    pstMBuf = (PMBUF_S *)pMsg;

    /* �յ���Ϣ����*/
    DHCPV6S_DBGCNT_ADD(E_DHCPV6S_REV_MS_MSG);

    /* ��Ϣ���� */
    if (VOS_OK != DHCPV6_MsgProc(pstMBuf))
    {
        DHCPV6S_DBGCNT_ADD(E_DHCPV6S_PROC_ERR);
    }

    return;
}

#ifdef __LINUX_PLATFORM__


ULONG DHCPV6S_CompMsgDistribute(ULONG ulMsgType, VOID* pMsg )
{
    if ( NULL == pMsg )
    {
        return VOS_ERR;
    }

    switch(ulMsgType)
    {
        case DHCPV6S_MSG_TYPE_PF:
        {
            DHCPV6S_ProcPfMsg(pMsg);

            /* MBUF��Ҫ����Լ��ͷ� */
            (VOID)PMBUF_Destroy((PMBUF_S *)pMsg);
            break;
        }
        default:
        {
            break;
        }
    }

    return VOS_OK;
}

#define __DHCPV6S_COMP_FRAME____________
ULONG DHCPV6S_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
                            DMS_COMMID_T myCSI, DMS_COMMID_T myCPI, VOID* pThis )
{
    ULONG ulRet = 0;

    switch (eConstructStage)
    {
        case RTF_COMP_CONSTRUCT_STAGE1:
            /* ��һ�׶�*/
            /* ��ʼ�������Ϣ(self csi, handle) */
            /* �����ڴ��ʼ�� */
            /* �����ڴ�/��������ʼ��, ����SG�ں�SG�� */
            /* ���г�ʼ�� */
            /* ��������/��������ڴ��ʼ�� */
            /* CRM /INST/ HAA /DVM /RMM�ص�����ע�� */

            /* �ȴ������LOCAL�� */
            ulRet = PGP_CompConstruct(myCSI, myCPI, &pThis);
            if (VOS_OK != ulRet)
            {
                return ulRet;
            }

            ulRet = DHCPV6S_GetSelfCompInfo(myCSI);
            if (VOS_OK != ulRet)
            {
                return ulRet;
            }

            ulRet = DHCPV6S_CommInit1();

            break;

        case RTF_COMP_CONSTRUCT_STAGE2:
            /* �ڶ��׶� PGPReady*/
            /* CDB���á�License����� */
            /* RDB ��ص�ҵ���ʼ���������ڴ棬IFA �ӿڻ�ȡ���߼����� */
            ulRet = DHCPV6S_CommInit2();
            break;

        case RTF_COMP_CONSTRUCT_STAGE3:
            /* �����׶�: ���enable, ��ƽ̨��Confirm */
            /* Timer��ʼ�� */
            ulRet = DHCPV6S_CommInit3();
            if (VOS_OK != ulRet)
            {
                return ulRet;
            }

            /* ע�����س�ʼ������*/
            DHCPV6S_ScheduleInit(myCPI);
            break;

        default:
            /*������*/
            ulRet = VOS_ERR;
            break;
    }

    vos_printf("DHCPV6S_CompConstruct stage %u, ret %u", eConstructStage, ulRet);

    return ulRet;
}
ULONG DHCPV6S_CompDestruct( DMS_COMMID_T myPid, VOID* pThis )
{
    vos_printf("Destruct Component DHCPS\r\n");
    return VOS_OK;
}


ULONG DHCPV6S_CompMsgProc(VOID* pMsg, VOID* pThis)
{
    DMS_IID_T recvIId;
    ULONG ulRet = VOS_OK;
    VOID *pMsgBody = NULL;
    ULONG ulMsgType = 0;

    if( NULL == pMsg )
    {
        return VOS_ERR;
    }

    /* ������Ϣ���� */
    if ((INTF_SSP == VRP_MSG_GET_INTF_ID(pMsg))
        && (SSP_SUB_INTF_HA == VRP_MSG_GET_SUBINTF_ID(pMsg))
        && (MSG_HA_START_WORK == VRP_MSG_GET_TYPE(pMsg)))
    {
        (VOID)HAF_SendStartWorkRsp(((COMP_LOCAL_COMMON_S*)pThis)->selfDopraCpi, VOS_OK);

         return VOS_OK;
    }

    /* ��ʱ����Ϣ����*/
    recvIId = DMS_MSG_RECV_IID_GET(pMsg);
    if( VOS_IID_TMR_TIMEOUT == recvIId )
    {
        /* û�ж�ʱ���ص� */
        VOS_Assert(0);
        return VOS_OK;
    }

    /* ��ȡDMSQ��Ϣ�� */
    pMsgBody = PGP_CompGetMsgBody(pMsg);

    ulMsgType = DMS_MSG_STREAMID_GET(pMsg);
    if ( ulMsgType < M_PS_MSG_TYPE_BASE ) /*������PGP����*/
    {
        /* ƽ̨��Ϣ����*/
        (VOID)PGP_CompMsgProc(pMsgBody);
    }
    else
    {
        /* ����������Ϣ�ַ����� */
        ulRet = DHCPV6S_CompMsgDistribute(ulMsgType, pMsgBody);
    }

    /* ƽ̨��Ϣ�ͷŴ���*/
    PGP_CompMsgRelease();

    return ulRet;
}

#endif


