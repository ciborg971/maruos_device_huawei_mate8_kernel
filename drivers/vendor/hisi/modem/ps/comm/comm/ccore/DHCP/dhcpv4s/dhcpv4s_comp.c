
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
//#include "dhcps_hsgw_public.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPV4S_COMP_C
/*lint +e767*/


ULONG ulDhcpv4sTaskStep = 0;

PTM_COMPONENT_INFO_S g_stDhcpv4sComInfo = { 0 };

VOS_UINT64 g_ullDhcpv4sUsmCsi = 0;

ULONG ulDhcpv4sPerfInitFinish = VOS_FALSE;

#define __INNER_MSG__


ULONG DHCPS_SendRtMsg(VOS_UINT64 ullDstCsi, ULONG ulMsgType, ULONG ulMsgCode, UCHAR *pucMsg, ULONG ulMsgLen )
{
    ULONG ulReturn = VOS_OK;
    UCHAR *pucRtMsg = VOS_NULL;

    if ((VOS_NULL == pucMsg) || (0 == ulMsgLen))
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    pucRtMsg = (UCHAR*)DHCP_RTDistributeAllocMsg(DHCPS_HANDLE, ulMsgLen);
    if (VOS_NULL == pucRtMsg)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCP_RTDistributeAllocMsg fail");
        return VOS_ERR;
    }

    VOS_MemCpy(pucRtMsg, pucMsg, ulMsgLen);

    RTD_SET_MSGCODE(pucRtMsg, (USHORT)ulMsgCode);
    ulReturn = DHCP_RTDistributeSend(DHCPS_SELF_CSI,
                           ullDstCsi,
                           pucRtMsg,
                           ulMsgLen,
                           ulMsgType);

    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCP_RTDistributeSend fail, return = %x", ulReturn);
        DHCP_RTDistributeFreeMsg(pucRtMsg);
        return VOS_ERR;
    }

    return VOS_OK;
}


VOID DHCPS_SendLeaseTimeOutInnerMsg()
{
    ULONG ulReturn = 0;
    DHCPS_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPS_INNER_LEASE_TIMEOUT;

    ulReturn = DHCPS_SendRtMsg(DHCPS_SELF_CSI, DHCPS_MSG_TYPE_SELF,
                               DHCPS_INNER_LEASE_TIMEOUT, (UCHAR*)&stInnerMsg,
                               sizeof(DHCPS_INNER_MSG_S));
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        return;
    }

    return;
}


VOID DHCPS_SendStateTimeOutInnerMsg()
{
    ULONG ulReturn = 0;
    DHCPS_INNER_MSG_S stInnerMsg = {0};

    stInnerMsg.ulMsgCode = DHCPS_INNER_STATE_TIMEOUT;

    ulReturn = DHCPS_SendRtMsg(DHCPS_SELF_CSI, DHCPS_MSG_TYPE_SELF,
                               DHCPS_INNER_STATE_TIMEOUT, (UCHAR*)&stInnerMsg,
                               sizeof(DHCPS_INNER_MSG_S));
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        return;
    }

    return;
}


/*==========================================================
 *  ��������:              DHCPS_HA_BackupProc
 *  �������:              2009/03/17
 *  ��    ��       :          dongmingzhou 42828
 *  ��������:   ��DHCP��Լ������ȡ�������ݵ�DHCPS���ƿ飬
                               ��������뱸�ݽṹ��
 *  �������:              ����������Ϣ
 *  �������:
 *  ��������:              ��
 *  ����˵��:              ��
 *  ���ú���:
 *  ��������:              AM_USM_HA_EncapBackupMsgByContextRec
 *=========================================================*/
ULONG DHCPS_HA_BackupProc( char **ppbuff,  ULONG ulIndex )
{
    DHCPS_DebugPrint(PTM_LOG_DEBUG, " entry" );

    /*��ڲ������*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        VOS_Assert(0);
        return VOS_ERR;
    }

    /*ǰ��: ��������������DHCPS���ƿ�����*/
    if ( ( 0 == ulIndex )
        || ( ulIndex > SDB_MAX_CONTEXT_NUM ) )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " master the DHCPS lease index[%u] is error!", ulIndex);
        return VOS_ERR;
    }

    VOS_MemCpy( *ppbuff, &g_pstDhcpSLease[ulIndex], sizeof( DHCPS_LEASE_S ) );
    g_pstDhcpSLease[ulIndex].ucLeaseTimerOP = DHCPS_HA_LEASETIME_INVALID;

    *ppbuff += sizeof( DHCPS_LEASE_S );

    return VOS_OK;
}
/*==========================================================
 *  ��������:              DHCPS_HA_SLAVE_RestoreProc
 *  �������:              2009/03/17
 *  ��    ��       :          dongmingzhou 42828
 *  ��������:   DHCPSģ����ƿ��ڱ���ı��ݻָ��ؽ�����
                               �ӱ��ݽṹ��ȡ�������ݵ�DHCP���ƿ����ݣ�
                               ���������DHCP���ƿ�������
 *  �������:              ����������Ϣ
 *  �������:
 *  ��������:              ��
 *  ����˵��:              ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
ULONG DHCPS_HA_SLAVE_CreateProc( char **ppbuff,  ULONG ulIndex )
{
    DHCPS_LEASE_S *pstLease = NULL;
    ULONG ulTimerOutLength = 0;
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "entry" );


    /*��ڲ������*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_BackupRestoreProc : slave the point is NULL!" );
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_221);
        return VOS_ERR;
    }

    /*ǰ��: ��������������DHCPS���ƿ�����*/
    if ( 0 == ulIndex || ulIndex > SDB_MAX_CONTEXT_NUM )
    {
        /*ʧ�ܣ�ָ��ҲҪƫ��*/
        *ppbuff += sizeof( DHCPS_LEASE_S );
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_BackupRestoreProc : slave DHCPS lease index[%u] error!", ulIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_222);
        return VOS_ERR;
    }

    pstLease = &g_pstDhcpSLease[ulIndex];

    if ((0 < pstLease->ulIndex) && (pstLease->ulIndex < SDB_MAX_CONTEXT_NUM))
    {
        if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
        {
            enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;
            if ((VOS_TRUE == DHCPS_IsTimerOn(pstLease->ulIndex, enTimerType)) && (pstLease->ucLeaseTimerOP != DHCPS_HA_LEASETIME_INVALID))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_CreateProc : Slave is timer on ");

                if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, (ULONG)enTimerType))
                {
                    DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_CreateProc : stop timer err ");
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_327);
                }
            }
        }
    }

    VOS_MemCpy( pstLease,*ppbuff, sizeof( DHCPS_LEASE_S ) );
    pstLease->pstAnalyzedPacket = NULL;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_CreateProc : ucUsed = %u, ucLeaseState = %u, ucLeaseTimerOP = %u",
                        pstLease->ucUsed,
                        pstLease->ucLeaseState,
                        pstLease->ucLeaseTimerOP);

    if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
    {
        ulTimerOutLength = g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerOutLength;
        enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;

        /* ���ʱ����Ϊ0��������ʱ�� */
        if ((0 != ulTimerOutLength) && (pstLease->ucLeaseTimerOP & DHCPS_HA_LEASETIME_START))
        {
            if (VOS_OK != DHCPS_TIMER_StartTimer(pstLease, enTimerType, ulTimerOutLength))
            {
                DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_CreateProc : Lease Start Timer ERR ");
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_223);
            }
        }
    }

    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_INVALID;

    *ppbuff += sizeof( DHCPS_LEASE_S );

    return VOS_OK;
}
/*==========================================================
 *  ��������:              DHCPS_HA_SLAVE_UpdateProc
 *  �������:              2009/03/17
 *  ��    ��       :          dongmingzhou 42828
 *  ��������:   DHCPSģ����ƿ��ڱ���ı��ݸ��º���
                               �ӱ��ݽṹ��ȡ�������ݵ�DHCPS���ƿ����ݣ�
                               ���������DHCP���ƿ�������
 *  �������:              ����������Ϣ
 *  �������:
 *  ��������:              ��
 *  ����˵��:              ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
ULONG DHCPS_HA_SLAVE_UpdateProc( char **ppbuff,  ULONG ulIndex )
{
    DHCPS_LEASE_S *pstLease = NULL;
    ULONG ulTimerOutLength = 0;
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_UpdateProc : slave Enter. " );


    /*��ڲ������*/
    if ( NULL == ppbuff || NULL == *ppbuff )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : slave the point is NULL!" );
        return VOS_ERR;
    }

    /*ǰ��: ��������������dhcp���ƿ�����*/
    if ( (0 == ulIndex)
        || (ulIndex > SDB_MAX_CONTEXT_NUM) )  /* Modified by jixiaoming at 2011-05-10 for pclint */
    {
        /*ʧ�ܣ�ָ��ҲҪƫ��*/
        *ppbuff += sizeof( DHCPS_LEASE_S );
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : slave the index[%u]  is error!", ulIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_224);
        return VOS_ERR;
    }

    pstLease = &g_pstDhcpSLease[ulIndex];

    if ((0 < pstLease->ulIndex) && (pstLease->ulIndex < SDB_MAX_CONTEXT_NUM))
    {
        if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
        {
            enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;
            if ((VOS_TRUE == DHCPS_IsTimerOn(pstLease->ulIndex, enTimerType)) && (pstLease->ucLeaseTimerOP != DHCPS_HA_LEASETIME_INVALID))
            {
                DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_UpdateProc : Slave is timer on ");

                if (VOS_OK != DHCPS_TIMER_StopTimer(pstLease, (ULONG)enTimerType))
                {
                    DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : stop timer err ");
                    DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_328);
                }
            }
        }
    }

    VOS_MemCpy( pstLease ,*ppbuff, sizeof( DHCPS_LEASE_S ) );
    pstLease->pstAnalyzedPacket = NULL;

    if (VOS_TRUE == DHCPS_FSM_LeaseStateIsValid(ulIndex))
    {
        /* ��ʱ������ */
        ulTimerOutLength = g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerOutLength;
        enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[pstLease->ucLeaseState].ulTimerType;

        if ((0 != ulTimerOutLength) && (pstLease->ucLeaseTimerOP & DHCPS_HA_LEASETIME_START))
        {
            if (VOS_OK != DHCPS_TIMER_StartTimer(pstLease, enTimerType, ulTimerOutLength))
            {
                DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_HA_SLAVE_UpdateProc : Lease Start Timer ERR ");
                DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_226);
            }
        }
    }

    pstLease->ucLeaseTimerOP = DHCPS_HA_LEASETIME_INVALID;

    *ppbuff += sizeof( DHCPS_LEASE_S );

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_HA_SLAVE_UpdateProc : slave Exit. " );

    return VOS_OK;
}

/*==========================================================
 *  ��������:              DHCPS_HA_SLAVE_DeleteProc
 *  �������:              2009/03/17
 *  ��    ��       :          dongmingzhou 42828
 *  ��������:   DHCPSģ����ƿ��ڱ���ı���ɾ������
 *  �������:              ����������Ϣ
 *  �������:
 *  ��������:              ��
 *  ����˵��:              ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
ULONG DHCPS_HA_SLAVE_DeleteProc( ULONG ulIndex )
{
    DHCPS_TIMER_TYPE_E enTimerType = E_DHCPS_INVALID_TIMER;
    UCHAR ucLeaseState = 0;

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_BackupDeleteProc : slave Enter. " );

    /*ǰ��: ��������������DHCPS���ƿ�����*/
    if ( (0 == ulIndex)
        || (ulIndex > SDB_MAX_CONTEXT_NUM) )   /* Modified by jixiaoming at 2011-05-10 for pclint */
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_BackupDeleteProc : slave the index[%u]  is error!", ulIndex);
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_227);
        return VOS_ERR;
    }

    if (VOS_TRUE != DHCPS_FSM_LeaseStateIsValid(ulIndex))
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_BackupDeleteProc : slave the ucLeaseState is error!" );
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_320);
        return VOS_ERR;
    }

    enTimerType = (DHCPS_TIMER_TYPE_E)g_stDHCPSStateMachine[ucLeaseState].ulTimerType;

    if (VOS_TRUE == DHCPS_IsTimerOn(ulIndex, enTimerType))
    {
        (VOID)DHCPS_TIMER_StopTimer(&g_pstDhcpSLease[ulIndex] , enTimerType);
    }

    PGP_MemZero(&g_pstDhcpSLease[ulIndex], sizeof(DHCPS_LEASE_S));

    DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_BackupDeleteProc : slave Exit. " );

    return VOS_OK;
}

#define __DHCPS_COMP_INIT__


ULONG DHCPS_OmInitial()
{
/* BEGIN: Modified by jixiaoming at 2011-03-02 */
    /* ע������ͳ�� for pgw */
    if ((g_UEtoPGW_ulDHCPV4DiscoveryNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_DIS_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_DIS_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4RequestNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_REQ_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4DeclineNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_DEC_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_DEC_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4ReleaseNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_REL_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_REL_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoPGW_ulDHCPV4InformNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_RCV_DHCPV4_INFORM_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_RCV_DHCPV4_INFORM_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV4OfferNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_SEND_DHCPV4_OFFER_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV4_OFFER_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV4AckNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_SEND_DHCPV4_ACK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV4_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoUE_ulDHCPV4NakNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_PGW_S5,
             PERF_TYPE_PGW_SEND_DHCPV4_NAK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_PGW_SEND_DHCPV4_NAK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    /*����ͳ�� for sgw*/
    if ((g_UEtoSGW_ulDHCPV4DiscoveryNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_DIS_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_DIS_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4RequestNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_REQ_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_REQ_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4DeclineNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_DEC_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_DEC_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4ReleaseNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_REL_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_REL_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_UEtoSGW_ulDHCPV4InformNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_RCV_DHCPV4_INFO_FROM_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_RCV_DHCPV4_INFO_FROM_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV4OfferNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV4_OFFER_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV4_OFFER_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV4AckNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV4_ACK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV4_ACK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_SGWtoUE_ulDHCPV4NakNumAddr = PerfGetFamPerfCounterAddress(
             PERF_TYPE_SGW_SM,
             PERF_TYPE_SGW_SM_SEND_DHCPV4_NAK_TO_UE_PKTS,
             VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial GetAddress of  PERF_TYPE_SGW_SM_SEND_DHCPV4_NAK_TO_UE_PKTS fail!");
        return VOS_ERR;
    }
/* END: Modified by jixiaoming at 2011-03-02 */

    ulDhcpv4sPerfInitFinish = VOS_TRUE;

    return VOS_OK;
}

/*==========================================================
 *  ��������: DHCPS_OM_QueryIpinuseProc
 *  �������:
 *  ��    ��:
 *  ��������: dhcpserver��ѯʹ�õ�IP��������

 *  �������:
 *  �������:
 *  ��������: ��
 *  ����˵��: ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
VOID DHCPS_OM_QueryIpinuseProc( UCHAR * pucMsg,
                                                                   ULONG ulMsgLen ,
                                                                   VOS_VOID ** ppSendData,
                                                                   ULONG *pulSendDataLen)
{
    DHCPS_IPINUSE_MSG_S *pstReplyMsg = NULL;

    ULONG ulReqMsgLen = sizeof(DHCPS_IPINUSE_MSG_S);
    ULONG ulReplyMsgLen = sizeof(DHCPS_IPINUSE_MSG_S);

    if ((VOS_NULL_PTR == pucMsg)
        ||(VOS_NULL_PTR == ppSendData)
        || (ulReqMsgLen != ulMsgLen))
    {
        VOS_DBGASSERT(VOS_FALSE);
        return;
    }

    DHCPS_DebugPrint(PTM_LOG_DEBUG, "entry");

    /* ������Ϣ����������ڴ� */
    pstReplyMsg = (DHCPS_IPINUSE_MSG_S *)IPC_RPC_AllocMsg(ulReplyMsgLen, MID_DHCPS);
    if (NULL == pstReplyMsg)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " IPC_RPC_AllocMsg fail !");
        return;
    }

    (VOID)VOS_MemSet((VOID *)(pstReplyMsg), 0, sizeof(DHCPS_IPINUSE_MSG_S));

    pstReplyMsg->usMsgType = VOS_HTONS(MSG_ACK);
    pstReplyMsg->ucResult = VOS_OK;
    pstReplyMsg->ucScId = (UCHAR)DHCPS_SELF_CMPIDX_INSG;
    pstReplyMsg->ulIpNum = VOS_HTONL(g_ulDHCPSIpnum);

    *ppSendData = (VOS_VOID *)pstReplyMsg;
    *pulSendDataLen = ulReplyMsgLen;

    return;
}

/*==========================================================
 *  ��������: DHCPS_IpcCallback
 *  �������:
 *  ��    ��:
 *  ��������: dhcpserverIPC�ص�������

 *  �������:
 *  �������:
 *  ��������: ��
 *  ����˵��: ��
 *  ���ú���:
 *  ��������:
 *=========================================================*/
VOID DHCPS_IpcCallback( ULONG ulSrcNode, ULONG ulSrcModuleID,
                        VOID *pReceiveData, ULONG ulReceiveDataLen,
                        VOID **ppSendData, ULONG *pulSendDataLen )
{
    USHORT usMsgCode = 0;
    UCHAR * pucMsg = NULL;
    ULONG ulMsgLen = NULL;

    /* ������� */
   if((NULL == pReceiveData) || (NULL == ppSendData) || (NULL == pulSendDataLen))
   {
       VOS_Assert(VOS_FALSE);
       return;
   }
   /*���ݳ��ȵ��ж�*/
   if( sizeof(MSG_HDR_S) >= ulReceiveDataLen)
   {
       VOS_Assert(VOS_FALSE);

       return;
   }

   usMsgCode = VOS_HTONS(((MSG_HDR_S *)pReceiveData)->usMsgCode);

   pucMsg = (UCHAR *)pReceiveData;
   ulMsgLen = ulReceiveDataLen;

   switch(usMsgCode)
   {
        case DHCPS_IPNUM_REQ :
            DHCPS_OM_QueryIpinuseProc(pucMsg , ulMsgLen , ppSendData, pulSendDataLen);

            break;

        default:
            DHCPS_DebugPrint(PTM_LOG_DEBUG, " DHCPS_IpcCallback: Exceptional IPC-RPC Msg!ucMsgCode = %d\n",usMsgCode);

        break;
   }
   return;
}


ULONG DHCPS_MallocNode(UCHAR **ppucNode,ULONG ulLength)
{

    /* ���뷢����Ϣ�Ļ������ռ�*/
    *ppucNode = (UCHAR *) DHCP_Malloc(DHCPS_HANDLE, ulLength);
    if( NULL == *ppucNode )
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(*ppucNode , ulLength);
    return VOS_OK;
}
VOID DHCPS_FreeNode(UCHAR **ppucNode)
{

    if(NULL != *ppucNode)
    {
        DHCP_Free(DHCPS_HANDLE, *ppucNode);
        *ppucNode = NULL;
    }
    return;
}



ULONG DHCPS_InitRecvBuff()
{
    UCHAR *pucBuf = NULL;

    /* ���뷢����Ϣ�Ļ������ռ�*/
    pucBuf = (UCHAR *) DHCP_Malloc(DHCPS_HANDLE, DHCPS_RECV_MSG_MAXLEN);
    if( NULL == pucBuf)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(pucBuf, DHCPS_RECV_MSG_MAXLEN);
    g_pucDHCPSRecvMsgBuff = pucBuf;
    return VOS_OK;
}
ULONG DHCPS_InitDHCPMsgDelayBuff()
{
    g_pstDHCPMsgBuffList = (DHCPS_MSG_BUFFLIST_HEAD *) DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_MSG_BUFFLIST_HEAD));
    if( NULL == g_pstDHCPMsgBuffList)
    {
        VOS_Assert(0);
        return VOS_ERR;
    }
    DHCP_MemZero(g_pstDHCPMsgBuffList, sizeof(DHCPS_MSG_BUFFLIST_HEAD));

    g_pstDHCPMsgBuffList->ulNodeNum = 0;
    g_pstDHCPMsgBuffList->stFistNode.pPre = NULL;
    g_pstDHCPMsgBuffList->stFistNode.pNext = &(g_pstDHCPMsgBuffList->stEndNode);
    g_pstDHCPMsgBuffList->stFistNode.pucMsgData = NULL;
    g_pstDHCPMsgBuffList->stFistNode.ulMsgLen = 0;
    g_pstDHCPMsgBuffList->stFistNode.ulPdnIndex = VOS_NULL_DWORD;
    g_pstDHCPMsgBuffList->stEndNode.pNext = NULL;
    g_pstDHCPMsgBuffList->stEndNode.pPre = &(g_pstDHCPMsgBuffList->stFistNode);
    g_pstDHCPMsgBuffList->stEndNode.pucMsgData = NULL;
    g_pstDHCPMsgBuffList->stEndNode.ulMsgLen = 0;
    g_pstDHCPMsgBuffList->stEndNode.ulPdnIndex = VOS_NULL_DWORD;

    return VOS_OK;
}


ULONG DHCPS_GetMbufData(PMBUF_S* pstMsgBuf, UCHAR **ppMsg, ULONG *pulMsgLen)
{
    ULONG ulMsgLen = 0;

    if (NULL == pstMsgBuf)
    {
        return VOS_ERR;
    }


    /*��ȡ���ĳ��Ⱥ͵�ַ*/
    ulMsgLen = PMBUF_GET_TOTAL_DATA_LENGTH(pstMsgBuf);
    if (DHCPS_RECV_MSG_MAXLEN < ulMsgLen)
    {
        return VOS_ERR;
    }

    *pulMsgLen = ulMsgLen;
    DHCP_MemZero(g_pucDHCPSRecvMsgBuff, DHCPS_RECV_MSG_MAXLEN);

    /* û�з�Ƭ BLOCK_NUMBERΪ 1 */
    if (1 == PMBUF_GET_DATA_BLOCK_NUMBER(pstMsgBuf))
    {
        *ppMsg = PMBUF_MTOD(pstMsgBuf, UCHAR*);
    }
    else
    {
        /* �з�Ƭ����Ҫ���Ƶ������ڴ� , ��MBUF���ݸ��Ƶ����������ڴ��� */
        if (VOS_OK != PMBUF_CopyDataFromPMBufToBuffer(pstMsgBuf, 0, ulMsgLen, g_pucDHCPSRecvMsgBuff))
        {
            return VOS_ERR;
        }
        *ppMsg = g_pucDHCPSRecvMsgBuff;
    }

    return VOS_OK;
}
VOID DHCPS_ProcPfMsg(PMBUF_S *pstMsgBuf)
{
    ULONG ulMsgLen = 0;
    ULONG ulRet = VOS_OK;
    UCHAR *pucMsg = NULL;

    if ( NULL == pstMsgBuf )
    {
        VOS_Assert(0);
        return;
    }

    /*��ȡ���ݵ�ַ�ͳ���*/
    ulRet = DHCPS_GetMbufData(pstMsgBuf, &pucMsg, &ulMsgLen);
    if (VOS_OK != ulRet)
    {
        return;
    }

    ulRet = DHCPS_DPEDhcpMsgProc(pucMsg, ulMsgLen);
    if (VOS_OK != ulRet)
    {
        DHCPS_InternalBranchCounter(DHCPS_INTERNAL_BRANCH_319);
    }

    return;
}
ULONG DHCPS_LocalMemInit()
{
    USHORT i = 0;
    ULONG ulRet = VOS_OK;

    g_ulDhcpStatisc = DHCP_Malloc(DHCPS_HANDLE, sizeof(ULONG) * DHCPS_MAX_STATISC);
    if(NULL == g_ulDhcpStatisc )
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_ulDhcpStatisc,  sizeof(ULONG) * DHCPS_MAX_STATISC);

    g_pstDhcpSLease = (DHCPS_LEASE_S *)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_LEASE_S)*(SDB_MAX_CONTEXT_NUM+1));
    if(NULL == g_pstDhcpSLease)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstDhcpSLease, sizeof(DHCPS_LEASE_S)*(SDB_MAX_CONTEXT_NUM+1));

    g_pstOption = (DHCPS_CFG_OPTION_S *)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_CFG_OPTION_S) * 256);
    if(NULL == g_pstOption)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstOption, sizeof(DHCPS_CFG_OPTION_S)*256);

    /*�������ݳ�ʼ��*/
    VOS_MemSet((VOID *)g_aulDHCPSDbgCnt,0,
                           (sizeof(ULONG) * DHCPS_MAX_FAILURE_COUNTER));

    g_pstExpiredInfor = ( DHCPS_EXPIRED_REC_S * )DHCP_Malloc(DHCPS_HANDLE, sizeof( DHCPS_EXPIRED_REC_S )*( MAX_APN_NUM+1 ) );
    if ( NULL == g_pstExpiredInfor )
    {
        DHCPS_DebugPrint(PTM_LOG_INFO, " DHCPS_InitCDBConfig: g_astExpiredInfor Error" );
        return VOS_ERR;
    }

    PGP_MemZero( g_pstExpiredInfor, sizeof( DHCPS_EXPIRED_REC_S )*( MAX_APN_NUM+1 ) );

    for ( i = 0;i <= MAX_APN_NUM;i++)
    {
        g_pstExpiredInfor[i].usApnIndex = i;
        g_pstExpiredInfor[i].usDay  = 1;
        g_pstExpiredInfor[i].ucHour = 0;
        g_pstExpiredInfor[i].ucMinute = 0;
        g_pstExpiredInfor[i].usUnlimited = 0;
    }

    g_ppstStateTimerList = (DHCPS_TIMER_LINKLIST_S**)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_STATE_TIMER_LINKLIST);
    if (NULL == g_ppstStateTimerList)
    {
        return VOS_ERR;
    }
    PGP_MemZero((VOID*)g_ppstStateTimerList, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_STATE_TIMER_LINKLIST);

    g_ppstLeaseTimerList = (DHCPS_TIMER_LINKLIST_S**)DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_LEASE_TIMER_LINKLIST);
    if (NULL == g_ppstLeaseTimerList)
    {
        return VOS_ERR;
    }
    PGP_MemZero((VOID*)g_ppstLeaseTimerList, sizeof(DHCPS_TIMER_LINKLIST_S*) * DHCPS_MAX_LEASE_TIMER_LINKLIST);

    g_pstLeaseTimer = DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));
    if(NULL == g_pstLeaseTimer)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstLeaseTimer, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));

    g_pstStateTimer = DHCP_Malloc(DHCPS_HANDLE, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));
    if(NULL == g_pstStateTimer)
    {
        return VOS_ERR;
    }
    PGP_MemZero(g_pstStateTimer, sizeof(DHCPS_TIMER_LINKLIST_S)*(SDB_MAX_CONTEXT_NUM+1));


    ulRet = DHCPS_InitRecvBuff();
    if(VOS_OK != ulRet)
    {
        return ulRet;
    }

    ulRet = DHCPS_InitDHCPMsgDelayBuff();
    if(VOS_OK != ulRet)
    {
        return ulRet;
    }
    return VOS_OK;
}
VOID DHCPS_GetOtherCompInfo()
{
    g_ullDhcpv4sUsmCsi = PSM_Inf_GetCSIBySGIDCmpTypeAndCmpInstId(DHCPS_SELF_SGID,
                                                                 E_COMP_TYPE_USM,
                                                                 DHCPS_SELF_CMPIDX_INSG);
    return;
}


ULONG DHCPS_CommInit1(  )
{
    ULONG ulReturn = VOS_OK;

    DBG_LogRecordReg(M_PTM_SYSTEM_NAME, "DHCP", "DHCPV4S", &g_ulDhcpv4sLogRecordRegId);

    PTM_Dbg_RegMemoryPrint(DHCPS_SELF_CSI);

    ulDhcpv4sTaskStep = 200;

    DHCPS_GetOtherCompInfo();

    ulDhcpv4sTaskStep = 300;

    /* ����˽���ڴ� */
    ulReturn = DHCPS_LocalMemInit();
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_LocalMemInit fail" );
        return ulReturn;
    }

    ulDhcpv4sTaskStep = 400;

    ulReturn = IPC_RPC_Register(MID_DHCPS, DHCPS_IpcCallback);
    if ( VOS_OK != ulReturn )
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, " DHCPS_Init: IPC_Create Failed!~!!" );
        return ulReturn;
    }

    ulDhcpv4sTaskStep = 500;

    DHCPV4S_DebugCmdInit(DHCPS_SELF_CSI);

    DHCPS_FSM_Register();

    ulDhcpv4sTaskStep = 1800;

    return VOS_OK;
}
ULONG DHCPS_CommInit2(  )
{
    return VOS_OK;
}


ULONG DHCPS_CommInit3( )
{
    ULONG ulReturn = 0;

    ulDhcpv4sTaskStep = 4100;

#ifndef PRODUCT_TYPE_HSGW

    DHCPS_V4_CallBackReg();

    /* ���ó�ʼ�� */
    DHCPS_GetConfig();

    ulDhcpv4sTaskStep = 4200;

    /* ��ʼ������ͳ�� */
    ulReturn = DHCPS_OmInitial();
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "DHCPS_OmInitial fail" );
        /* ���ɷ���ʧ�� */
    }
#endif
    ulDhcpv4sTaskStep = 6100;

    return VOS_OK;
}


#define __DHCPS_COMP_MSG_PROC___________

ULONG DHCPS_StartWorkProc( )
{
    ULONG ulReturn = VOS_OK;

    ulReturn = DHCPS_Tmr_Init();
    if ( VOS_OK != ulReturn )
    {
        return ulReturn;
    }

    /* Added by jixiaoming for  CR20120830015 at 2013-1-17 */
    ulReturn = DHCPS_RegLogCnt();
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "call DHCPS_RegLogCnt fail! ulReturn=%u", ulReturn);
    }

    ulDhcpv4sTaskStep = 6200;

    return VOS_OK;
}


VOID DHCPS_ProcSelfMsg(VOID* pMsg)
{
    DHCPS_INNER_MSG_S *pstInnerMsg = NULL;

    if ( NULL == pMsg )
    {
        VOS_Assert(0);
        return;
    }

    pstInnerMsg = (DHCPS_INNER_MSG_S *)pMsg;

    switch ( pstInnerMsg->ulMsgCode )
    {
        case DHCPS_INNER_LEASE_TIMEOUT :
            DHCPS_LeaseTimerMsgProc();
            break;

        case DHCPS_INNER_STATE_TIMEOUT :
            DHCPS_StateTimerMsgProc();
            break;

        default:
            VOS_Assert(0);
            break;
    }

    return;
}

#ifdef __LINUX_PLATFORM__


ULONG DHCPS_GetSelfCompInfo(DMS_COMMID_T myCSI )
{
    g_stDhcpv4sComInfo.ullSelfCsi = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DSV4);
    g_stDhcpv4sComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();

    g_stDhcpv4sComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpv4sComInfo.ullSelfCsi);
    g_stDhcpv4sComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpv4sComInfo.ullSelfCsi);

    (VOID)VOS_HandleInitialize("mid_dhcps", &g_stDhcpv4sComInfo.ulHandle);

    return VOS_OK;
}


VOID DHCPS_ScheduleInit( DMS_COMMID_T ullCpi )
{
    ULONG i = 0;
    ULONG ulReturn = VOS_OK;
    COMP_MSGSTM_ATTR_S astMsgQueAttr[DHCPS_MSG_TYPE_BULT] = {0};
    ULONG aulScheduleTlb[DHCPS_MSG_TYPE_BULT] = { 0 };
    ULONG ulNum = 0;

    /* ��ʼ��ÿ�����е�������� */
    aulScheduleTlb[DHCPS_MSG_TYPE_PF]        = 50;
    aulScheduleTlb[DHCPS_MSG_TYPE_USM]         = 50;
    aulScheduleTlb[DHCPS_MSG_TYPE_TIMER]         = 50;
    aulScheduleTlb[DHCPS_MSG_TYPE_SELF]         = 2;

    for (i = DHCPS_MSG_TYPE_PF; i < DHCPS_MSG_TYPE_BULT; i++)
    {
        if ( 0 == aulScheduleTlb[i] )
        {
            continue;
        }

        astMsgQueAttr[ulNum].uiMsgNum = aulScheduleTlb[i];
        astMsgQueAttr[ulNum].uiStreamId = i;
        astMsgQueAttr[ulNum].uiFcmQue = 0;
        astMsgQueAttr[ulNum].uiMaxAppMsgNum = DHCPV4S_DEFAULT_MAX_APP_MSG_NUM;
        ulNum++;
    }

    ulReturn = (ULONG)PGP_ScmCompMsgStmAttribSet(ullCpi, ulNum, astMsgQueAttr);
    if (VOS_OK != ulReturn)
    {
        DHCPS_DebugPrint(PTM_LOG_ERR, "\r\n PGP_ScmCompMsgStmAttribSet fail, Ret = %u", ulReturn);
    }

    return;
}
ULONG DHCPS_CompInitPhase1(DMS_COMMID_T myCSI)
{
    ULONG ulRet = VOS_OK;

    /* ��ʼ��������� */
    ulRet = DHCPS_GetSelfCompInfo(myCSI);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    ulRet = DHCPS_CommInit1();
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}
ULONG DHCPS_CompInitPhase2()
{
    return VOS_OK;
}


ULONG DHCPS_CompInitPhase3(DMS_COMMID_T myCPI)
{
    ULONG ulRet = VOS_OK;

    ulRet = DHCPS_CommInit3();
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* ע�����س�ʼ������*/
    DHCPS_ScheduleInit(myCPI);

    return VOS_OK;
}
ULONG DHCPS_CompMsgDistribute(ULONG ulMsgType, VOID* pMsg )
{
    switch(ulMsgType)
    {
        case DHCPS_MSG_TYPE_PF:
        {
            DHCPS_ProcPfMsg(pMsg);

            /* MBUF��Ҫ����Լ��ͷ� */
            (VOID)PMBUF_Destroy((PMBUF_S *)pMsg);
            break;
        }
        case DHCPS_MSG_TYPE_USM:
        {
            DHCPS_FSM_PreMsgFromUSM(pMsg);

            break;
        }
        case DHCPS_MSG_TYPE_SELF:
        {
            DHCPS_ProcSelfMsg(pMsg);

            break;
        }
        default:
        {
            break;
        }
    }

    return VOS_OK;
}

#define __DHCPS_COMP_FRAME____________
ULONG DHCPS_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
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

            ulRet = DHCPS_CompInitPhase1( myCSI );
            break;

        case RTF_COMP_CONSTRUCT_STAGE2:
            /* �ڶ��׶� PGPReady*/
            /* CDB���á�License����� */
            /* RDB ��ص�ҵ���ʼ���������ڴ棬IFA �ӿڻ�ȡ���߼����� */
            ulRet = DHCPS_CompInitPhase2( );
            break;

        case RTF_COMP_CONSTRUCT_STAGE3:
            /* �����׶�: ���enable, ��ƽ̨��Confirm */
            /* Timer��ʼ�� */
            ulRet = DHCPS_CompInitPhase3( myCPI);
            break;

        default:
            /*������*/
            ulRet = VOS_ERR;
            break;
    }

    vos_printf("DHCPS_CompConstruct stage %u, ret %u", eConstructStage, ulRet);

    return ulRet;
}


ULONG DHCPS_CompDestruct( DMS_COMMID_T myPid, VOID* pThis )
{
    vos_printf("Destruct Component DHCPS\r\n");
    return VOS_OK;
}


ULONG DHCPS_CompMsgProc(VOID* pMsg, VOID* pThis)
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
         ulRet = DHCPS_StartWorkProc();
         if (VOS_OK == ulRet)
         {
            (VOID)HAF_SendStartWorkRsp(((COMP_LOCAL_COMMON_S*)pThis)->selfDopraCpi, VOS_OK);
         }

         return VOS_OK;
    }

    /* ��ʱ����Ϣ����*/
    recvIId = DMS_MSG_RECV_IID_GET(pMsg);
    if( VOS_IID_TMR_TIMEOUT == recvIId )
    {
        /* ����ƽ̨��װ�Ķ�ʱ����������������ҵ��ע��Ļص����� */
        PGP_CompRelTimeoutProc((VOS_MSG_TMR_RELTMR_S*)pMsg);
        return VOS_OK;
    }

    /* ��ȡDMSQ��Ϣ�� */
    pMsgBody = PGP_CompGetMsgBody(pMsg) ;

    ulMsgType = DMS_MSG_STREAMID_GET(pMsg);
    if ( ulMsgType < M_PS_MSG_TYPE_BASE ) /*������PGP����*/
    {
        /* ƽ̨��Ϣ����*/
        (VOID)PGP_CompMsgProc(pMsgBody);
    }
    else
    {
        ulDhcpv4sTaskStep= 7000;
        /* ����������Ϣ�ַ����� */
        ulRet = DHCPS_CompMsgDistribute(ulMsgType, pMsgBody);
    }

    /* ƽ̨��Ϣ�ͷŴ���*/
    PGP_CompMsgRelease();

    return ulRet;
}

#endif

