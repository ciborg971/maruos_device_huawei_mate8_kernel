
#include "dhcp_inc.h"
#include "dhcpc_def.h"
#include "dhcpc.h"
#include "dhcpc_cdb.h"
#include "dhcpc_func.h"
#include "dhcpc_table.h"
#include "dhcpv6c_pkt.h"
#include "dhcpc_var.h"
#include "dhcpc_comp.h"
#include "dhcpc_dbg.h"

/*****************************************************************************
    Э��ջ��ӡ��㷽ʽ�µ�.C�ļ��궨��
*****************************************************************************/
/*lint -e767*/
#define    THIS_FILE_ID          PS_FILE_ID_DHCPC_COMP_C
/*lint +e767*/

ULONG ulDhcpcTaskStep = 0;
PTM_COMPONENT_INFO_S g_stDhcpcComInfo = { 0 };

ULONG ulDhcpcPerfInitFinish = VOS_FALSE;


#define __DHCPC_COMP_INIT__

ULONG DHCPC_OmInitial()
{
/* deleted by w00316385 start */
#if 0
    /* ע������ͳ�� */
    if ((g_PGWtoServer_ulDHCPV4DiscoveryNumAddr = PerfGetFamPerfCounterAddress(
            PERF_TYPE_PGW_S5,
            PERF_TYPE_PGW_SEND_DHCPV4_DIS_TO_SERVER_PKTS,
            VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPC_DebugPrint(PTM_LOG_INFO,
                     "PERF_TYPE_PGW_SEND_DHCPV4_DIS_TO_SERVER_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoServer_ulDHCPV4RequestNumAddr = PerfGetFamPerfCounterAddress(
            PERF_TYPE_PGW_S5,
            PERF_TYPE_PGW_SEND_DHCPV4_REQ_TO_SERVER_PKTS,
            VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPC_DebugPrint(PTM_LOG_INFO,
                     "PERF_TYPE_PGW_SEND_DHCPV4_REQ_TO_SERVER_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoServer_ulDHCPV4DeclineNumAddr = PerfGetFamPerfCounterAddress(
            PERF_TYPE_PGW_S5,
            PERF_TYPE_PGW_SEND_DHCPV4_DEC_TO_SERVER_PKTS,
            VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPC_DebugPrint(PTM_LOG_INFO,
                     "PERF_TYPE_PGW_SEND_DHCPV4_DEC_TO_SERVER_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_PGWtoServer_ulDHCPV4ReleaseNumAddr = PerfGetFamPerfCounterAddress(
            PERF_TYPE_PGW_S5,
            PERF_TYPE_PGW_SEND_DHCPV4_REL_TO_SERVER_PKTS,
            VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPC_DebugPrint(PTM_LOG_INFO,
                     "PERF_TYPE_PGW_SEND_DHCPV4_REL_TO_SERVER_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_ServertoPGW_ulDHCPV4OfferNumAddr = PerfGetFamPerfCounterAddress(
            PERF_TYPE_PGW_S5,
            PERF_TYPE_PGW_RCV_DHCPV4_OFFER_FROM_SERVER_PKTS,
            VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPC_DebugPrint(PTM_LOG_INFO,
                     "PERF_TYPE_PGW_RCV_DHCPV4_OFFER_FROM_SERVER_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_ServertoPGW_ulDHCPV4AckNumAddr = PerfGetFamPerfCounterAddress(
            PERF_TYPE_PGW_S5,
            PERF_TYPE_PGW_RCV_DHCPV4_ACK_FROM_SERVER_PKTS,
            VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPC_DebugPrint(PTM_LOG_INFO,
                     "PERF_TYPE_PGW_RCV_DHCPV4_ACK_FROM_SERVER_PKTS fail!");
        return VOS_ERR;
    }

    if ((g_ServertoPGW_ulDHCPV4akNumAddr = PerfGetFamPerfCounterAddress(
            PERF_TYPE_PGW_S5,
            PERF_TYPE_PGW_RCV_DHCPV4_NAK_FROM_SERVER_PKTS,
            VOS_NULL_PTR))
        == VOS_NULL_PTR)
    {
        /* д��־ */
        DHCPC_DebugPrint(PTM_LOG_INFO,
                 "PERF_TYPE_PGW_RCV_DHCPV4_NAK_FROM_SERVER_PKTS fail!");
        return VOS_ERR;
    }
#endif
/* deleted by w00316385 end */
    ulDhcpcPerfInitFinish = VOS_TRUE;

    return VOS_OK;
}


ULONG DHCPC_GlobalValInit()
{
    ULONG ulRet = VOS_OK;

    g_ulDhcpcTaskId       = 0;
    g_ulDhcpcTimerQid     = 0;
    g_ulDhcpcServerQid    = 0;
    g_ulDhcpcRenewTimerID = 0;
    g_ulDhcpcRetransTimerID = 0;
    g_ulDhcpcCtrlBlockAgingTimerID = 0;
    g_uldftDhcpcSendCBTimerID = 0;
    g_ulDhcpcSeqnumAgingTimerID = 0;
    g_ulDhcpCtrlBlockAgingFlag = 0;
    g_ulDhcpcCurrentScanPdpIndex = 0;
    g_ulDhcpcCurrentScanHashKey = 0;

    /*��ʱ������=��ʱ��ʱ��*/
    g_ulTimerRenewType    = DHCPC_RENEW_TIMER_LENGTH;
    g_ulTimerRetransType  = DHCPC_RETRANS_TIMER_LENGTH;
    g_ulCurrProcIndex     = 0;
    g_ulDHCPCTransId      = 1;
    g_stDhcpcGlobalUdpsSrvNo.ulGlobalSrvIp1 = 0;
    g_stDhcpcGlobalUdpsSrvNo.lGlobalUdpsSrvNo1 = DHCPC_INVALID_UDPSNO;
    g_stDhcpcGlobalUdpsSrvNo.ulGlobalSrvIp2 = 0;
    g_stDhcpcGlobalUdpsSrvNo.lGlobalUdpsSrvNo2 = DHCPC_INVALID_UDPSNO;
    g_ulDhcpcGlbLeaseTime = 0;
    g_ulDHCPCDbgPkt = 0;
    g_ulDhcpcAlarmTimerID = 0;

    /* ȷ��sequenceNum��� */
    ulRet = CRM_GetSelfGroupBoardType(&g_ulDhcpcBoardType);
    if (CRM_OK != ulRet)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "CRM_GetSelfGroupBoardType fail, ulRet = %x", ulRet);
        return VOS_ERR;
    }

    if (CRM_BOARD_TYPE_SPUF == g_ulDhcpcBoardType)
    {
        g_usDhcpv6cMaxSeqNum = DHCPV6C_MAX_SEQUENCE_NUM_F;
    }

    return VOS_OK;
}


/*****************************************************************************
 �� �� ��  : DHCPC_DftInit
 ��������  : DFT��ʼ������
 �������  : ��
 �������  : ��
 �� �� ֵ  :  VOID
 ���ú���  :
 ��������  :

 �޸���ʷ      :
  1.��    ��   : 2011��05��17��
    ��    ��   : ������
    �޸�����   : �����ɺ���

*****************************************************************************/
ULONG DHCPC_DftInit()
{
    /* DFT�ϱ����Ϳ��ƿ���Ŀ */
    g_DFT_pulDHCPSendCBNum = (ULONG *)PGP_ShrMemAllocByName("DHCPC_DFT_NAME", SERVICE_MEM_TYPE_SHARE_GLOBAL, MID_DHCPC, sizeof(ULONG));
    if (NULL == g_DFT_pulDHCPSendCBNum)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PGP_ShrMemAllocByName fail");
        return VOS_ERR;
    }

    return VOS_OK;
}

/*****************************************************************************
 �� �� ��  : DHCPC_RegisterDFTInfo
 ��������  : ��ƽ̨ע��DHCP���Ϳ��ƿ��ϱ���Դ
 �������  : ��
 �������  : ��
 �� �� ֵ  : ��
 ���ú���  :
 ��������  :
 �޸���ʷ     :
 1.��    ��   : 2011-05-16
   ��    ��   : ������
   �޸�����   : �½�����
*****************************************************************************/
VOID DHCPC_RegisterDFTInfo()
{
/* deleted by w00316385 start */
#if 0
    RMMC_RegisterCounterInfo(M_DHCPC_RMM_TBL_CTRLBLK_COUNTER,
                                g_DFT_pulDHCPSendCBNum,
                                1);
#endif
/* deleted by w00316385 end */
    return;
}


ULONG DHCPC_LocalMemInit()
{
    ULONG i = 0;
    ULONG ulRet = VOS_OK;

    /*��ʼ����ʱ������*/
    PGP_MemZero( g_astTimerLink, DHCPC_TMR_CIRCLE_TIME * sizeof( DLL_S ) );
    for ( i = 0; i < DHCPC_TMR_CIRCLE_TIME; i++ )
    {
        DLL_Init( &g_astTimerLink[i] );
        /*ʹ��ulHandle���־ͷ���*/
        ( g_astTimerLink[i].Head ).ulHandle = DHCPC_HEADNODE_TYPE;
    }
    g_pstDhcpCtrlBlkNodeArr = ( DHCPC_CTRLBLK_NODE* )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK_NODE )*DHCPC_MAX_CTRLBLKNUM );
    if ( NULL == g_pstDhcpCtrlBlkNodeArr )
    {
        VOS_Assert( 0 );
        return VOS_ERR;
    }
    PGP_MemZero( g_pstDhcpCtrlBlkNodeArr, sizeof( DHCPC_CTRLBLK_NODE ) * DHCPC_MAX_CTRLBLKNUM );

    g_pstDhcpcCtrlBlkRec = ( DHCPC_CTRLBLK** )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK* )*DHCPC_CTRLBLK_HASH_TABLE_SIZE );
    if ( NULL == g_pstDhcpcCtrlBlkRec )
    {
        DHCP_Free(DHCPC_HANDLE, g_pstDhcpCtrlBlkNodeArr);
        VOS_Assert( 0 );
        return VOS_ERR;
    }
    /* ��ʼ��DHCP���ƿ�ָ������ */
    PGP_MemZero( g_pstDhcpcCtrlBlkRec, sizeof( DHCPC_CTRLBLK * )*DHCPC_CTRLBLK_HASH_TABLE_SIZE );

    g_pucDhcpPktBuf = (UCHAR*)DHCP_Malloc(DHCPC_HANDLE, sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN);
    if (NULL == g_pucDhcpPktBuf)
    {
        DHCP_Free(DHCPC_HANDLE, g_pstDhcpCtrlBlkNodeArr);
        DHCP_Free(DHCPC_HANDLE, g_pstDhcpcCtrlBlkRec);
        VOS_Assert( 0 );
        return VOS_ERR;
    }
    PGP_MemZero(g_pucDhcpPktBuf, sizeof(UCHAR) * DHCP_PKT_ASSUME_MAX_LEN);
    /* END: Added by jixiaoming at 2011-11-28 for CR20110907018 */

    g_pstDhcpcIpv6CtrlBlkRec = ( DHCPC_CTRLBLK** )DHCP_Malloc( DHCPC_HANDLE, sizeof( DHCPC_CTRLBLK* )*DHCPC_CTRLBLK_HASH_TABLE_SIZE );
    if ( NULL == g_pstDhcpcIpv6CtrlBlkRec )
    {
        DHCP_Free(DHCPC_HANDLE, g_pstDhcpcIpv6CtrlBlkRec);
        DHCP_Free(DHCPC_HANDLE, g_pstDhcpcCtrlBlkRec);
        DHCP_Free(DHCPC_HANDLE, g_pucDhcpPktBuf);
        VOS_Assert( 0 );
        return VOS_ERR;
    }
    /* ��ʼ��DHCP���ƿ�ָ������ */
    DHCP_MemZero( g_pstDhcpcIpv6CtrlBlkRec, sizeof( DHCPC_CTRLBLK * )*DHCPC_CTRLBLK_HASH_TABLE_SIZE );

    /* ���뷢��Ϣ���� */
    g_pucDhcpv6cSendBuff = (UCHAR*)DHCP_Malloc(DHCPC_HANDLE, sizeof(UCHAR) * DHCPV6C_SEND_MSG_MAXLEN);
    if (NULL == g_pucDhcpv6cSendBuff)
    {
        return VOS_ERR;
    }
    DHCP_MemZero(g_pucDhcpv6cSendBuff, sizeof(UCHAR) * DHCPV6C_SEND_MSG_MAXLEN);

    /*����SequenceNum�ڴ�*/
    g_pstDhcpv6cSeqContext = (DHCPV6C_SEQNUM_CONTEXT_S *)DHCP_Malloc(DHCPC_HANDLE, sizeof(DHCPV6C_SEQNUM_CONTEXT_S) * (DHCPV6C_MAX_SEQUENCE_NUM + 1));
    if(VOS_NULL == g_pstDhcpv6cSeqContext)
    {
        return VOS_ERR;
    }
    DHCP_MemZero(g_pstDhcpv6cSeqContext, sizeof(DHCPV6C_SEQNUM_CONTEXT_S) * (DHCPV6C_MAX_SEQUENCE_NUM + 1));

    /*��ʼ��SequenceNum������*/
    ulRet = DHCPV6C_InitFreeLink(&g_stDhcpv6cSeqNumLink, (USHORT)DHCPV6C_MAX_SEQUENCE_NUM);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* ��ʼ��ʱ�������ͷ */
    ulRet = DHCPC_InitTimerList();
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /*��ʱ��debug������*/
    VOS_MemSet((VOID *)g_aulDHCPDbgCnt,0,(sizeof(ULONG) * DHCP_MAX_FAILURE_COUNTER));

    return VOS_OK;
}


ULONG DHCPC_CommInit1(  )
{
    ULONG ulReturn = VOS_OK;

/* deleted by w00316385 start */
#if 0
    DBG_LogRecordReg(M_PTM_SYSTEM_NAME, "DHCP", "DHCPC", &g_ulDhcpcLogRecordRegId);
#endif
/* deleted by w00316385 end */

    /*ע���������*/
    (VOID)PTM_CommandsRegister(&DHCPDebugCommandGroup, "dhcp","dhcp debug command", DHCPC_SELF_CSI );

    PTM_Dbg_RegMemoryPrint(DHCPC_SELF_CSI);

    ulReturn = CRM_GetSelfGroupBoardType(&g_ulDhcpcSpuType);
    if ( VOS_OK != ulReturn )
    {
        VOS_Assert(0);
        DHCPC_DebugPrint(PTM_LOG_ERR, "CRM_GetSelfGroupBoardType fail, ulReturn = %x", ulReturn);
        return ulReturn;
    }

    ( VOID )DHCPC_GlobalValInit();

    ulDhcpcTaskStep = 200;

    /* ����˽���ڴ� */
    ulReturn = DHCPC_LocalMemInit();
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_LocalMemInit fail");
        return ulReturn;
    }

    ulDhcpcTaskStep = 250;

#if 0
    ulReturn = DHCPC_DftInit();
    if ( VOS_OK != ulReturn )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_DftInit fail");
        return ulReturn;
    }
#endif

    ulDhcpcTaskStep = 300;

    ulReturn = DHCPM_RegDhcpServer();
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_LocalMemInit fail");
        return ulReturn;
    }

    ulDhcpcTaskStep = 400;

    DHCPV6C_FSM_Register();

    ulDhcpcTaskStep = 500;

/* deleted by w00316385 start */
#if 0
    ulReturn = CRM_StateOfBoardChangeCallbackReg((CRM_SPU_STATE_CALLBACK)DHCPC_StateOfBoardChgCallback);
    if (VOS_OK != ulReturn)
    {
        VOS_Assert(0);
        return ulReturn;
    }

    ulDhcpcTaskStep = 600;

    ulReturn = PGP_RTCreate ( DHCPC_SELF_CSI, IPC_NOTI_VIA_FUNC,
                              0, (IPC_RTNOTIFY_FUNC)PGP_RTDistributeCallback);
    if ( VOS_OK != ulReturn )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "PGP_RTCreate fail, ulReturn = %x", ulReturn);
        return ulReturn;
    }
#endif
/* deleted by w00316385 end */

    ulDhcpcTaskStep = 700;

    return VOS_OK;
}


ULONG DHCPC_CommInit2(  )
{
    return VOS_OK;
}


ULONG DHCPC_CommInit3( )
{
    ULONG ulReturn = 0;

    /* ��ʼ������ͳ�� */
    ulReturn = DHCPC_OmInitial();
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_OmInitial fail");
        /* ���ɷ���ʧ�� */
    }

    /* ע���ϱ�������DFT */
    DHCPC_RegisterDFTInfo();

    return VOS_OK;
}

ULONG DHCPC_StartWorkProc( )
{
    ULONG ulReturn = VOS_OK;

    ulReturn = DHCPC_Tmr_Init();
    if ( VOS_OK != ulReturn )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_Tmr_Init fail! ulReturn=%u", ulReturn);
        return ulReturn;
    }

    ulReturn = DHCPC_RegLogCnt();
    if ( VOS_OK != ulReturn )
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "DHCPC_RegLogCnt fail! ulReturn=%u", ulReturn);
    }

    return VOS_OK;
}

#ifdef __LINUX_PLATFORM__

#define __DHCPC_COMP_MSG_PROC___________
ULONG DHCPC_GetSelfCompInfo(DMS_COMMID_T myCSI )
{
    g_stDhcpcComInfo.ullSelfCsi = PSM_Inf_GetSelfCSI(E_COMP_TYPE_DHCPC);
    g_stDhcpcComInfo.ullSelfSgId = PSM_Inf_GetSelfSGID();

    g_stDhcpcComInfo.ulSelfCmpIdx = PSM_Inf_GetCmpIndexInOSByCSI(g_stDhcpcComInfo.ullSelfCsi);
    g_stDhcpcComInfo.ulSelfCmpIdxInSG = PSM_Inf_GetCmpSameTIndexInSGByCSI(g_stDhcpcComInfo.ullSelfCsi);

    (VOID)VOS_HandleInitialize("mid_dhcpc", &g_stDhcpcComInfo.ulHandle);

    return VOS_OK;
}

VOID DHCPC_ScheduleInit( DMS_COMMID_T ullCpi )
{
    ULONG i = 0;
    ULONG ulReturn = VOS_OK;
    COMP_MSGSTM_ATTR_S astMsgQueAttr[DHCPC_MSG_TYPE_BULT] = {0};
    ULONG aulScheduleTlb[DHCPC_MSG_TYPE_BULT] = { 0 };
    ULONG ulNum = 0;

    /* ��ʼ��ÿ�����е�������� */
    aulScheduleTlb[DHCPC_MSG_TYPE_FCM]        = DHCPC_MAXMSGS_PEREVENT;
    aulScheduleTlb[DHCPC_MSG_TYPE_SERVER]         = DHCPC_MAXMSGS_PEREVENT;
    aulScheduleTlb[DHCPC_MSG_TYPE_LAP]         = 0;
    aulScheduleTlb[DHCPC_MSG_TYPE_TIMER]         = DHCPC_MAXMSGS_PEREVENT;
    aulScheduleTlb[DHCPC_MSG_TYPE_SELF]      = 1;

    for (i = M_PS_MSG_TYPE_BASE; i < DHCPC_MSG_TYPE_BULT; i++)
    {
        if ( 0 == aulScheduleTlb[i] )
        {
            continue;
        }

        if (DHCPC_MSG_TYPE_TIMER == i)
        {
            /* ��ʱ����ϢΪ�����ȼ���Ϣ��uiPrio����Ϊ1������ϢidΪ0��uiStreamId����Ϊ0��
               ��ͨ��ϢΪ�����ȼ���Ϣ��uiPrio����Ϊ0������ϢidΪʵ�ʶ������ϢId */
            astMsgQueAttr[ulNum].uiStreamId = 0;
            astMsgQueAttr[ulNum].uiPrio     = 1;
        }
        else
        {
            astMsgQueAttr[ulNum].uiStreamId = i;
        }

        astMsgQueAttr[ulNum].uiMsgNum = aulScheduleTlb[i];
        astMsgQueAttr[ulNum].uiFcmQue = 0;
        astMsgQueAttr[ulNum].uiMaxAppMsgNum = DHCPC_DEFAULT_MAX_APP_MSG_NUM;
        ulNum++;
    }

    ulReturn = (ULONG)PGP_ScmCompMsgStmAttribSet(ullCpi, ulNum, astMsgQueAttr);
    if (VOS_OK != ulReturn)
    {
        DHCPC_DebugPrint(PTM_LOG_ERR, "\r\n PGP_ScmCompMsgStmAttribSet fail, Ret = %u", ulReturn);
    }

    return;
}


ULONG DHCPC_CompMsgDistribute(ULONG ulMsgType, VOID* pMsg )
{
    switch(ulMsgType)
    {
        case DHCPC_MSG_TYPE_FCM:
        {
            DHCPC_ReceiveLap2MbufMsg((PMBUF_S *)pMsg);

            (VOID)PMBUF_Destroy((PMBUF_S *)pMsg);

            break;
        }
        case DHCPC_MSG_TYPE_SERVER:
        {
            DHCPC_ReceiveServerMsg(pMsg);

            break;
        }
        case DHCPC_MSG_TYPE_DHCPV6_SERVER:
        {
            DHCPV6C_ProcSDMsg(pMsg);
            break;
        }
        case DHCPC_MSG_TYPE_SELF:
        {
            DHCPC_SelfMsgProc(pMsg);
            break;
        }
        case DHCPC_MSG_TYPE_BATCH_CMD_REQ:
        {
            (VOID)PTM_DebugBatchCProcCmdRequestMsg(pMsg);
            break;
        }

        default:
        {
            break;
        }
    }

    return VOS_OK;
}



ULONG DHCPC_CompInitPhase1(DMS_COMMID_T myCSI)
{
    ULONG ulRet = VOS_OK;

    /* ��ʼ��������� */
    ulRet = DHCPC_GetSelfCompInfo(myCSI);
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    /* �����ֻ��Ҫ��������Ϣ��LAP���, ��LAPͳһ�ڷ��ͽӿ��л�ȡ */

    ulRet = DHCPC_CommInit1();
    if (VOS_OK != ulRet)
    {
        return VOS_ERR;
    }

    return VOS_OK;
}


ULONG DHCPC_CompInitPhase2()
{
    return VOS_OK;
}


ULONG DHCPC_CompInitPhase3(DMS_COMMID_T myCPI)
{
    ULONG ulRet = VOS_OK;

    ulRet = DHCPC_CommInit3();
    if (VOS_OK != ulRet)
    {
        return ulRet;
    }

    /* ע�����س�ʼ������*/
    DHCPC_ScheduleInit(myCPI);

    return VOS_OK;
}
ULONG DHCPC_CompConstruct( RTF_COMP_CONSTRUCT_STAGE_E eConstructStage,
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

            ulRet = DHCPC_CompInitPhase1( myCSI );
            break;

        case RTF_COMP_CONSTRUCT_STAGE2:
            /* �ڶ��׶� PGPReady*/
            /* CDB���á�License����� */
            /* RDB ��ص�ҵ���ʼ���������ڴ棬IFA �ӿڻ�ȡ���߼����� */
            ulRet = DHCPC_CompInitPhase2( );
            break;

        case RTF_COMP_CONSTRUCT_STAGE3:
            /* �����׶�: ���enable, ��ƽ̨��Confirm */
            /* Timer��ʼ�� */
            ulRet = DHCPC_CompInitPhase3(myCPI);
            break;

        default:
            /*������*/
            ulRet = VOS_ERR;
            break;
    }

    DHCPC_DebugPrint(PTM_LOG_INFO, "success");

    return ulRet;
}


ULONG DHCPC_CompDestruct( DMS_COMMID_T myPid, VOID* pThis )
{
    DHCPC_DebugPrint(PTM_LOG_INFO, "entry");
    return VOS_OK;
}


ULONG DHCPC_CompMsgProc(VOID* pMsg, VOID* pThis)
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
         ulRet = DHCPC_StartWorkProc();
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
        ulRet = DHCPC_CompMsgDistribute(ulMsgType, pMsgBody);
    }

    /* ƽ̨��Ϣ�ͷŴ���*/
    PGP_CompMsgRelease();

    return ulRet;
}

#endif


